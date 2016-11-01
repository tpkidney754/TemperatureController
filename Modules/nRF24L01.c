#include "nRF24L01.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];
uint8_t readRegComplete;

void nRF24L01_Config( uint8_t SPI_ch )
{
   uint8_t dataToWrite = 0x3;
   nRF24L01_WriteReg( SPI_ch, CONFIG, dataToWrite );
}

void nRF24L01_ReadReg( uint8_t SPI_ch, uint8_t registerToRead )
{
   SPI_Type * SPI_reg;
   SPI_reg = SPI_ch == 0 ? SPI0 : SPI1;
   // Command value macro
   uint8_t data = READ_REG( registerToRead );
   // Add command to buffer
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   data = NOP;
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   // Transmit
   //SET_BIT_IN_REG( GPIOC_PCOR, SPI0_CS_PIN );
   SET_BIT_IN_REG( SPI_C1_REG( SPI_reg ), SPI_C1_SPTIE_MASK );
   readRegComplete = 0;
   //SPI_TransmitData( SPI_ch, 3 );
   //while( readRegComplete == 0 );
   //SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
}

void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite )
{
   SPI_Type * SPI_reg;
   SPI_reg = SPI_ch == 0 ? SPI0 : SPI1;
   uint8_t data = WRITE_REG( reg );
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   data = dataToWrite;
   //SET_BIT_IN_REG( GPIOC_PCOR, SPI0_CS_PIN );
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &data );
   SET_BIT_IN_REG( SPI_C1_REG( SPI_reg ), SPI_C1_SPTIE_MASK );
   //SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
}

void nRF24L01_SendCommand( uint8_t SPI_ch, uint8_t command )
{
   CBufferAdd( SPI_TXBuffer[ SPI_ch ], &command );
   //SET_BIT_IN_REG( GPIOC_PCOR, SPI0_CS_PIN );
   SPI_TransmitData( SPI_ch, 1 );
   //SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
}

void nRF24L01_TXData( )
{

}

void nRF24L01_FlushTXFifo( )
{

}
