#ifdef FRDM
#ifndef __SPI__
#define __SPI__

#include "includeall.h"

#define SPI0_RXBUFFER_SIZE 128
#define SPI0_TXBUFFER_SIZE 128
#define SPI1_RXBUFFER_SIZE 128
#define SPI1_TXBUFFER_SIZE 128

#define SPI_CHANNELS 2

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

#define SPI0_MOSI       PORTC_PCR6
#define SPI0_SCK        PORTC_PCR5
#define SPI0_MISO       PORTC_PCR7
#define SPI0_CS         PORTC_PCR4
#define SPI0_CS_PIN     1 << 4
#define SPI0_CE         PORTC_PCR0
#define SPI0_CE_PIN     1 << 0
#define SPI0_IRQ        PORTC_PCR3
#define SPI0_IRQ_PIN    1 << 3

#define SPI1_MOSI       PORTE_PCR1
#define SPI1_SCK        PORTE_PCR2
#define SPI1_MISO       PORTE_PCR3
#define SPI1_CS         PORTE_PCR4

void InitSPI( uint8_t SPI_ch );
void ReadRegisterSPI( uint8_t SPI_ch, size_t registerToRead );
void SPI_TransmitData( uint8_t SPI_ch, size_t numBytes );

#endif // __SPI__
#endif // FRDM
