#include "uart.h"

void Uart0Setup( uint32_t requestedBuadRate, uint8_t parity )
{
   uint32_t uart0Clk = 0;
   uint32_t calcBaudRate = 0;
   uint32_t mcgClk = 0;
   uint32_t prdiv = 0;
   uint32_t vdiv = 0;
   uint8_t osr = 0;
   // Determining msgCLK
   prdiv = ((MCG_C5 & MCG_C5_PRDIV0_MASK) + 1);
   vdiv = ((MCG_C6 & MCG_C6_VDIV0_MASK) + 24);
   mcgClk = (( CPU_XTAL_CLK_HZ / prdiv ) * vdiv );
   // Enable Port A
   SET_BITS_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   // Enables PortA PCR1 for UART0_TXD functionality.
   SET_BITS_IN_REG( PORTA_PCR1, PORT_PCR_MUX( 0X2 ) );
   // Enables PortA PCR2 for UART0_TXD functionality.
   SET_BITS_IN_REG( PORTA_PCR2, PORT_PCR_MUX( 0X2 ) );
   // Selects the PLLFLLClk as the source for UART0
   SET_BITS_IN_REG( SIM_SOPT2, SIM_SOPT2_UART0SRC( 1 ) );
   //SET_BITS_IN_REG( SIM_SOPT2, SIM_SOPT2_PLLFLLSEL( 1 ) );
   //Calculates the clk value for UART0.
   uart0Clk = ( mcgClk / 2 );
   // Enables the clock gate for UART0
   SET_BITS_IN_REG( SIM_SCGC4, SIM_SCGC4_UART0_MASK );
   // Disables the UART0 TX/RX before setting other registers.
   CLEAR_BITS_IN_REG( UART0_C2, ( UART0_C2_TE_MASK | UART0_C2_RE_MASK ) );
   // Needs to calculate the baud rate mod that is placed into registers.
   calcBaudRate = uart0Clk / ( ( OSR ) * requestedBuadRate );

#if ( OSR >= 4 && OSR <= 8 )
   // If the over sampling rate is between 4 and 8, then both edge sampling needs to
   // be enabled.
   SET_BITS_IN_REG( UART0_C5, UART0_C5_BOTHEDGE_MASK );
#endif
   // Setting the OSR value in registers.
   SET_BITS_IN_REG( UART0_C4, UART0_C4_OSR( ( OSR - 1) ) );
   // Inputting the calculated baud rate mod into registers
   SET_BITS_IN_REG( UART0_BDH, UART0_BDH_SBR( ( calcBaudRate & 0x1F00 ) >> 8 ) );
   SET_BITS_IN_REG( UART0_BDL, UART0_BDL_SBR( (uint8_t) ( calcBaudRate & 0xFF ) ) );
   // Enables the TX/RX pins.
   SET_BITS_IN_REG( UART0_C2, ( UART0_C2_TE_MASK | UART0_C2_RE_MASK ) );
}

void Uart0TX( uint8_t * data, uint32_t length )
{
   //The transmitter then remains idle until data is available in the xmit data buffer.
   //The S1[TDRE] status flag is set to indicate when the next character may be
   //   wrtitten to the data buffer.
   for( uint32_t i = 0; i < length; i++ )
   {
      WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_TDRE_MASK );
      UART0_D = *( data + i );
   }

   //Transfer is complete, send break character then disable the transmiter.
   WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_TDRE_MASK );
   SET_BITS_IN_REG( UART0_C2, UART0_C2_SBK_MASK );
   CLEAR_BITS_IN_REG( UART0_C2, UART0_C2_SBK_MASK );
   //CLEAR_BITS_IN_REG( UART0_C2, UART0_C2_TE( 1 ) );
}

uint8_t Uart0RX( void )
{
   WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_RDRF_MASK );
   return UART0_D;
}

void PutChar( uint8_t data )
{
   WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_TDRE_MASK );
   UART0_D = data;
}

void ParseSetString( uint8_t * buffer )
{
   if( strstr( buffer, "color" ) )
   {
      Color_t color = NONE;
      if( strstr( buffer, "red" ) )
      {
         color = RED;
      }
      else if( strstr( buffer, "green" ) )
      {
         color = GREEN;
      }
      else if( strstr( buffer, "blue" ) )
      {
         color = BLUE;
      }
      else if( strstr( buffer, "purple" ) )
      {
         color = PURPLE;
      }
      else if( strstr( buffer, "yellow" ) )
      {
         color = YELLOW;
      }
      else if( strstr( buffer, "cyan") )
      {
         color = CYAN;  
      }
      else if( strstr( buffer, "white" ) )
      {
         color = WHITE;
      }
      else if( strstr( buffer, "off" ) )
      {
         color = OFF;
      }

      SwitchLEDs( color );
   }
   else if ( strstr( buffer, "power" ) )
   {
      uint16_t pulseWidth = 0;
      sscanf( buffer, "set power %d", &pulseWidth );
      ChangePW( pulseWidth );
   }
}
