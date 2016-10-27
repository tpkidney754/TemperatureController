#include "nRF24L01.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

void nRF24L01_Config( uint8_t SPI_ch )
{
   uint8_t dataToWrite = 0x3;
   nRF24L01_WriteReg( SPI_ch, CONFIG, dataToWrite );
}

void nRF24L01_ReadReg( uint8_t SPI_ch, uint8_t registerToRead )
{
   // Command value macro
   uint8_t data = READ_REG( registerToRead );
   // Add command to buffer
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   // Transmit
   SPI_TransmitData( SPI_ch, 1 );
}

void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite )
{
   uint8_t data = WRITE_REG( reg );
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   data = dataToWrite;
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   SPI_TransmitData( SPI_ch, 2 );
}

void nRF24L01_TXData( )
{

}

void nRF24L01_FlushTXFifo( )
{

}
