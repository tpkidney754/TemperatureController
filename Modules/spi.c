#ifdef FRDM
#include "spi.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

extern uint8_t readRegComplete;

void InitSPI( uint8_t SPI_ch )
{
   // start with SPRF and SPTEF flags and then move to DMA
   if( SPI_ch == 0 )
   {
      // Enable portc clock for I/O and the SPI0 clock.
      SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTC_MASK );
      SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_SPI0_MASK );
      // Set pins to the needed functionality.
      SET_BIT_IN_REG( SPI0_MOSI, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_SCK, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_MISO, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_CS, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_CE, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( SPI0_IRQ, PORT_PCR_MUX( PIN_GPIO ) );
      // Setting up RX interrupt, SPI enable, and SPI master
      SET_BIT_IN_REG( SPI0_C1, SPI_C1_SPIE_MASK | SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK );
      // When both the MODFEN and SSOE are clear the SS pin is set to be a GPIO.
      SET_BIT_IN_REG( GPIOC_PDDR, SPI0_CS_PIN );
      SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
      // Starting off with 1Mbps to reduce errors. Max for nRF24L01 is 2 Mbps
      SET_BIT_IN_REG( SPI0_BR, SPI_BR_SPPR( SPI_1Mbps_PRESCALER ) | SPI_BR_SPR( SPI_1Mbps_BRD ) );
      // Enable CE as a GPIO
      SET_BIT_IN_REG( GPIOC_PDDR, SPI0_CE_PIN );
      // Set CE high
      SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CE_PIN );

      SPI_RXBuffer[ 0 ] = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI_TXBuffer[ 0 ] = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );

      NVIC_EnableIRQ( SPI0_IRQn );
      NVIC_ClearPendingIRQ( SPI0_IRQn );
      NVIC_SetPriority( SPI0_IRQn, 2 );
   }
   else
   {
      SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTE_MASK );
      SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_SPI1_MASK );
      SET_BIT_IN_REG( SPI1_MOSI, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI1_SCK, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI1_MISO, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI1_CS, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI1_C1, SPI_C1_SPIE_MASK | SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK );
      // Starting off with 1Mbps to reduce errors. Max for nRF24L01 is 2 Mbps
      SET_BIT_IN_REG( SPI0_BR, SPI_BR_SPPR( SPI_1Mbps_PRESCALER ) | SPI_BR_SPR( SPI_1Mbps_BRD ) );

      SPI_RXBuffer[ 1 ] = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI_TXBuffer[ 1 ] = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );

      NVIC_EnableIRQ( SPI1_IRQn );
      NVIC_ClearPendingIRQ( SPI1_IRQn );
      NVIC_SetPriority( SPI1_IRQn, 2 );
   }
}

void SPI_TransmitData( uint8_t SPI_ch, size_t numBytes )
{
   SPI_Type * SPI_reg;
   uint8_t data;

   if( SPI_ch == 0 )
   {
      SPI_reg = SPI0;
   }
   else
   {
      SPI_reg = SPI1;
   }

   for( size_t i = 0; i < numBytes; i++ )
   {
      CBufferRemove( SPI_TXBuffer[ SPI_ch ], &data );
      WAIT_FOR_BIT_SET( SPI_S_REG( SPI_reg ) & SPI_S_SPTEF_MASK );
      SPI_D_REG( SPI_reg ) = data;
   }
}

void SPI0_IRQHandler( )
{
   if( SPI0_S & SPI_S_SPRF_MASK )
   {
      // Data available in the RX data buffer
      uint8_t data = SPI0_D;
      CBufferAdd( SPI_RXBuffer[ 0 ], &data );
   }

   if( SPI0_S & SPI_S_SPTEF_MASK )
   {
      // TX buffer empty
   }

   if( SPI0_S & SPI_S_MODF_MASK )
   {
      LOG0( "Master mode fault detected\n" );
   }
}

void SPI1_IRQHandler( )
{
   if( SPI1_S & SPI_S_SPRF_MASK )
   {
      // Data available in the RX data buffer
      uint8_t data = SPI1_D;
      CBufferAdd( SPI_RXBuffer[ 1 ], &data );
   }

   if( SPI1_S & SPI_S_SPTEF_MASK )
   {
      // TX buffer empty
   }
}
#endif // FRDM
