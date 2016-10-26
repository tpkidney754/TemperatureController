#ifdef FRDM
#include "spi.h"

CircularBuffer_t * SPI0_RXBuffer;
CircularBuffer_t * SPI0_TXBuffer;
CircularBuffer_t * SPI1_RXBuffer;
CircularBuffer_t * SPI1_TXBuffer;

void InitSPI( uint8_t SPI_ch )
{
   // start with SPRF and SPTEF flags and then move to DMA
   if( SPI_ch == 0 )
   {
      SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
      SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_SPI0_MASK );
      SET_BIT_IN_REG( SPI0_MOSI, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI0_SCK, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI0_MISO, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI0_CS, PORT_PCR_MUX( 0X2 ) );
      SET_BIT_IN_REG( SPI0_C1, SPI_C1_SPIE_MASK | SPI_C1_SPE_MASK | SPI_C1_MSTR_MASK );
      // Starting off with 1Mbps to reduce errors. Max for nRF24L01 is 2 Mbps
      SET_BIT_IN_REG( SPI0_BR, SPI_BR_SPPR( SPI_1Mbps_PRESCALER ) | SPI_BR_SPR( SPI_1Mbps_BRD ) );

      SPI0_RXBuffer = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI0_TXBuffer = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );

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

      SPI1_RXBuffer = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI1_TXBuffer = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );
      
      NVIC_EnableIRQ( SPI1_IRQn );
      NVIC_ClearPendingIRQ( SPI1_IRQn );
      NVIC_SetPriority( SPI1_IRQn, 2 );
   }
}

void ReadRegisterSPI( CircularBuffer_t * cb, size_t registerToRead, uint8_t SPI_ch )
{
   // Command value macro
   uint8_t data = READ_REG( registerToRead );
   // Add command to buffer
   CBufferAdd( cb, &data );
   // Transmit
   SPI_TransmitData( cb, SPI_ch, 1 );
}

void SPI_TransmitData( CircularBuffer_t * cb, uint8_t SPI_ch, size_t numBytes )
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
      CBufferRemove( cb, &data );
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
      CBufferAdd( SPI0_RXBuffer, &data );
   }

   if( SPI0_S & SPI_S_SPTEF_MASK )
   {
      // TX buffer empty
   }
}

void SPI1_IRQHandler( )
{
   if( SPI1_S & SPI_S_SPRF_MASK )
   {
      // Data available in the RX data buffer
      uint8_t data = SPI1_D;
      CBufferAdd( SPI0_RXBuffer, &data );
   }

   if( SPI1_S & SPI_S_SPTEF_MASK )
   {
      // TX buffer empty
   }
}
#endif // FRDM