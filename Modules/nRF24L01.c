#include "nRF24L01.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];
uint8_t readRegComplete;

//*************************************************************************
// Function:  nRF24L01_Activate                                           *
//                                                                        *
// Description: Sets up a msg that will be sent to the nRF24L01 module    *
//              that will activate the device. The command sets the       *
//              R_RX_PL_WID, W_ACK_PAYLOAD, and W_TX_PAYLOAD_NOACK        *
//              features.                                                 *
//                                                                        *
// Parameters: uint8_t SPI_ch: The spi channel being used.                *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void nRF24L01_Activate( uint8_t SPI_ch )
{
   nRF24L01_SPIMessage_t msg;
   msg.command = ACTIVATE;
   msg.spiCh = SPI_ch;
   msg.data[ 0 ] = ACTIVATE_KEY;
   msg.bytesToSend = 1;

   nRF24L01_SendData( &msg );
}

//*************************************************************************
// Function:  nRF24L01_ReadReg                                            *
//                                                                        *
// Description: Sets up a msg that will be sent to the nRF24L01 module    *
//              that will read a register on the device.                  *
//                                                                        *
// Parameters: uint8_t SPI_ch: The spi channel being used.                *
//             nRF24L01_Registers_e reg: Register to be read.             *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
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

   nRF24L01_SendData( &msg );
}

//*************************************************************************
// Function:  nRF24L01_WriteReg                                           *
//                                                                        *
// Description: Sets up a msg that will be sent to the nRF24L01 module    *
//              that will write a value to a register on the device.      *
//                                                                        *
// Parameters: uint8_t SPI_ch: The spi channel being used.                *
//             nRF24L01_Registers_e reg: Register to be written to.       *
//             uint8_t dataToWrite: value to be written to register       *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite )
{
   nRF24L01_SPIMessage_t msg;

   msg.spiCh = SPI_ch;
   msg.command = WRITE_REG( reg );
   msg.bytesToSend = 1;
   msg.data[ 0 ] = dataToWrite;

   nRF24L01_TXData( &msg );
}

//*************************************************************************
// Function:  nRF24L01_SendData                                           *
//                                                                        *
// Description: Receives a msg structure and then adds that msg to the    *
//              circular buffer used for SPI transmissions.               *
//                                                                        *
// Parameters: nRF24L01_SPIMessage_t * msg: pointer to the message struct *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void nRF24L01_SendData( nRF24L01_SPIMessage_t * msg )
{
   uint8_t data;

   data = msg->command;
   CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data );

   for( int8_t i = 0; i < msg->bytesToSend; i++ )
   {
      data = msg->data[ i ];
      CBufferAdd( SPI_TXBuffer[ msg->spiCh ], &data );
   }

   SPI_TransmitData( msg->spiCh, msg->bytesToSend + 1 );
}

void nRF24L01_FlushTXFifo( )
{

}
