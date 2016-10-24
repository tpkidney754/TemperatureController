#ifndef __SPI__
#define __SPI__

#include "includeall.h"

#define SPI0_MOSI       PORTA_PCR16
#define SPI0_SCK        PORTA_PCR15
#define SPI0_MISO       PORTA_PCR17
#define SPI0_CS         PORTA_PCR14

#define SPI1_MOSI       PORTE_PCR1
#define SPI1_SCK        PORTE_PCR2
#define SPI1_MISO       PORTE_PCR3
#define SPI1_CS         PORTE_PCR4

void InitSPI( uint8_t spiCh );

#endif // __SPI__
