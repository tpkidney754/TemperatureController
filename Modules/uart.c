#ifdef FRDM
#include "uart.h"

/* GLOBAL Variable */
uint8_t parseDiag;
CircularBuffer_t RXBuffer;
CircularBuffer_t TXBuffer;
//*************************************************************************
// Function:  Uart0Setup                                                  *
//                                                                        *
// Description: Sets up UART0 through SDA USB                             *
//                                                                        *
// Parameters: uint32_t requestedBaudRate: Desired baud rate              *
//             uint8_t parity: Used as boolean if parity is desired.      *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Uart0Setup( uint32_t requestedBuadRate, uint8_t parity )
{
   uint32_t uart0Clk = 0;
   uint32_t calcBaudRate = 0;
   uint32_t mcgClk = 0;
   uint32_t prdiv = 0;
   uint32_t vdiv = 0;
   parseDiag = 0;
   CBufferInit( &RXBuffer, sizeof( uint8_t ), RXBUFFER_SIZE );
   CBufferInit( &TXBuffer, sizeof( uint8_t ), TXBUFFER_SIZE );

   // Determining msgCLK
   prdiv = ((MCG_C5 & MCG_C5_PRDIV0_MASK) + 1);
   vdiv = ((MCG_C6 & MCG_C6_VDIV0_MASK) + 24);
   mcgClk = (( CPU_XTAL_CLK_HZ / prdiv ) * vdiv );
   // Enable Port A
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   // Enables PortA PCR1 for UART0_TXD functionality.
   SET_BIT_IN_REG( PORTA_PCR1, PORT_PCR_MUX( 0X2 ) );
   // Enables PortA PCR2 for UART0_TXD functionality.
   SET_BIT_IN_REG( PORTA_PCR2, PORT_PCR_MUX( 0X2 ) );
   // Selects the PLLFLLClk as the source for UART0
   SET_BIT_IN_REG( SIM_SOPT2, SIM_SOPT2_UART0SRC( 1 ) );
   //SET_BIT_IN_REG( SIM_SOPT2, SIM_SOPT2_PLLFLLSEL( 1 ) );
   //Calculates the clk value for UART0.
   uart0Clk = ( mcgClk / 2 );
   // Enables the clock gate for UART0
   SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_UART0_MASK );
   // Disables the UART0 TX/RX before setting other registers.
   CLEAR_BITS_IN_REG( UART0_C2, ( UART0_C2_TE_MASK | UART0_C2_RE_MASK ) );
   // Needs to calculate the baud rate mod that is placed into registers.
   calcBaudRate = uart0Clk / ( ( OSR ) * requestedBuadRate );

#if ( OSR >= 4 && OSR <= 8 )
   // If the over sampling rate is between 4 and 8, then both edge sampling needs to
   // be enabled.
   SET_BIT_IN_REG( UART0_C5, UART0_C5_BOTHEDGE_MASK );
#endif
   // Setting the OSR value in registers.
   SET_BIT_IN_REG( UART0_C4, UART0_C4_OSR( ( OSR - 1) ) );
   // Inputting the calculated baud rate mod into registers
   SET_BIT_IN_REG( UART0_BDH, UART0_BDH_SBR( ( calcBaudRate & 0x1F00 ) >> 8 ) );
   SET_BIT_IN_REG( UART0_BDL, UART0_BDL_SBR( (uint8_t) ( calcBaudRate & 0xFF ) ) );

   // Enable RX Interrupt
   SET_BIT_IN_REG( UART0_C2, UART0_C2_RIE_MASK );// | UART0_C2_TIE_MASK );
   //INTVEC_UART0 = (uint32_t ) UART0_IRQHandler;
   NVIC_EnableIRQ( UART0_IRQn );
   //NVIC_ClearPendingIRQ( UART0_IRQn );
   NVIC_SetPriority( UART0_IRQn, 2 );

   // Enables the TX/RX pins.
   SET_BIT_IN_REG( UART0_C2, ( UART0_C2_TE_MASK | UART0_C2_RE_MASK ) );
}

//*************************************************************************
// Function:  Uart0TX                                                     *
//                                                                        *
// Description: Uses the polling method to send data through UART0        *
//                                                                        *
// Parameters: uint8_t * data: pointer to an array of characters that are *
//                             to be transmitted through the UART0        *
//             uint32_t length: Num of characters to be sent through      *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Uart0TX( uint32_t length )
{
   //The transmitter then remains idle until data is available in the xmit data buffer.
   //The S1[TDRE] status flag is set to indicate when the next character may be
   //   wrtitten to the data buffer.
   uint8_t data;
   for( uint32_t i = 0; i < length; i++ )
   {
      WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_TDRE_MASK );
      CBufferRemove( &TXBuffer, &data );
      UART0_D = data;
   }
}

//*************************************************************************
// Function:  Uart0RX                                                     *
//                                                                        *
// Description: Uses the polling method to receive data through UART0     *
//                                                                        *
// Parameters: NONE                                                       *
//                                                                        *
// Return Value:  uint8_t: byte received from UART0                       *
//*************************************************************************
uint8_t Uart0RX( void )
{
   WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_RDRF_MASK );
   return UART0_D;
}

//*************************************************************************
// Function:  PutChar                                                     *
//                                                                        *
// Description: Transmits a single character through UART0                *
//                                                                        *
// Parameters: uint8_t data: character to be sent.                        *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void PutChar( uint8_t data )
{
   WAIT_FOR_BIT_SET( UART0_S1 & UART0_S1_TDRE_MASK );
   UART0_D = data;
}

//*************************************************************************
// Function:  UART0_IRQHandler                                            *
//                                                                        *
// Description: Interrupt Handler for UART0 for RX operations.            *
//              The handler checks the RDRF flag to verify it's a RX      *
//              then adds the character to buffer, then the character     *
//              is printed out to UART0TX. Once a CR is identified, a LF  *
//              and \0 character is added to buffer to terminate the      *
//              string and a boolean is set for main to start parsing the *
//              diag command.                                             *
//                                                                        *
// Parameters: uint8_t data: character to be sent.                        *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void UART0_IRQHandler( void )
{
   uint8_t data;
   if( UART0_S1 & UART0_S1_RDRF_MASK )
   {
      data = UART0_D;
      if( CBufferAdd( &RXBuffer, &data ) == BUFFER_FULL )
      {
         LOG0( "Buffer Is FULL during RX\n" );
      }
      PutChar( data );
      if( data == CR )
      {
         data = '\0';
         if( CBufferAdd( &RXBuffer, &data ) == BUFFER_FULL )
         {
            LOG0( "Buffer Is FULL during RX\n" );
         }
         parseDiag = 1;
      }
   }
   /*else if( UART0_S1 & UART0_S1_TDRE_MASK )
   {
      data = UART0_D;
      CBufferRemove( &TXBuffer, &data );
   }*/
}
#endif
