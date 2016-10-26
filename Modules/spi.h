#ifdef FRDM
#ifndef __SPI__
#define __SPI__

#include "includeall.h"

#define SPI0_RXBUFFER_SIZE 128
#define SPI0_TXBUFFER_SIZE 128
#define SPI1_RXBUFFER_SIZE 128
#define SPI1_TXBUFFER_SIZE 128

typedef enum
{
   prescaler1 = 0,
   prescaler2,
   prescaler3,
   prescaler4,
   prescaler5,
   prescaler6,
   prescaler7,
   prescaler8,
} SPI_BRPrescaler;

typedef enum
{
   divisor2 = 0,
   divisor4,
   divisor8,
   divisor16,
   divisor32,
   divisor64,
   divisor128,
   divisor256,
   divisor512,
} SPI_BRDivisor;
// These prescalers and BRDs are based on a 
// bus clock of 24 MHz
#define SPI_1Mbps_PRESCALER      prescaler3 // 24/3 = 8
#define SPI_1Mbps_BRD            divisor8 // 8/8 = 1Mbps
#define SPI_2Mbps_PRESCALER      prescaler3
#define SPI_2Mbps_BRD            divisor4
#define SPI_0_5Mbps_PRESCALER    prescaler6
#define SPI_0_5Mbps_BRD          divisor8

#define SPI0_MOSI       PORTA_PCR16
#define SPI0_SCK        PORTA_PCR15
#define SPI0_MISO       PORTA_PCR17
#define SPI0_CS         PORTA_PCR14

#define SPI1_MOSI       PORTE_PCR1
#define SPI1_SCK        PORTE_PCR2
#define SPI1_MISO       PORTE_PCR3
#define SPI1_CS         PORTE_PCR4

void InitSPI( uint8_t spiCh );
void ReadRegisterSPI( CircularBuffer_t * cb, size_t registerToRead, uint8_t SPI_ch );
void SPI_TransmitData( CircularBuffer_t * cb, uint8_t SPI_ch, size_t numBytes );

#endif // __SPI__
#endif // FRDM