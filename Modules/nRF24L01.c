#include "nRF24L01.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];
uint8_t readRegComplete;

void nRF24L01_Activate( uint8_t SPI_ch )
{
   nRF24L01_SPIMessage_t msg;
   msg.command = ACTIVATE;
   msg.spiCh = SPI_ch;
   msg.data[ 0 ] = ACTIVATE_KEY;
   msg.bytesToSend = 1;

   nRF24L01_TXData( &msg );
}

void nRF24L01_ReadReg( uint8_t SPI_ch, nRF24L01_Registers_e reg )
{
   nRF24L01_SPIMessage_t msg;

   msg.spiCh = SPI_ch;
   msg.command = READ_REG( reg );

   switch( reg )
   {
      // These three addresses are 5 bytes wide,
      // so 1 byte is sent to read register, then
      // 5 nops are sent to read back register. All other
      // registers are a single byte.
      case RX_ADDR_P0:
      case RX_ADDR_P1:
      case TX_ADDR:
         msg.bytesToSend = 5;
         for( int8_t i = 0; i < msg.bytesToSend - 1; i++ )
         {
            msg.data[ i ] = msg.command;
         }
         break;
      default:
         msg.bytesToSend = 1;
         msg.data[ 0 ] = NOP;
   }

   nRF24L01_TXData( &msg );
}

void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite )
{
   nRF24L01_SPIMessage_t msg;

   msg.spiCh = SPI_ch;
   msg.command = WRITE_REG( reg );
   msg.bytesToSend = 1;
   msg.data[ 0 ] = dataToWrite;

   nRF24L01_TXData( &msg );
}

void nRF24L01_TXData( nRF24L01_SPIMessage_t * msg )
{
   uint8_t data;

   data = msg->command;
   CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data );

   for( int8_t i = 0; i < msg->bytesToSend; i++ )
   {
      data = msg->data[ i ];
      CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data );
   }

#ifdef FRDM
   SPI_Type * SPI_reg = msg->spiCh == 0 ? SPI0 : SPI1;
   msg->spiCh == 0 ? SET_BIT_IN_REG( GPIOC_PCOR, SPI0_CS_PIN ) :
                     SET_BIT_IN_REG( GPIOE_PCOR, SPI1_CS_PIN );
   SET_BIT_IN_REG( SPI_C1_REG( SPI_reg ), SPI_C1_SPTIE_MASK );
#endif

#ifdef BBB
   SPI_TransmitData( msg->spiCh, msg->bytesToSend + 1 );
#endif

}

void nRF24L01_FlushTXFifo( )
{

}
