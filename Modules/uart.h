#ifdef FRDM
#ifndef __UART__
#define __UART__

#include "includeall.h"
//#include "circularbuffer.h"

#define OSR                16
#define CR                 13
#define LF                 10

#define RXBUFFER_SIZE      128
#define TXBUFFER_SIZE      1024
#define DMA_RXBUFFER_SIZE  _128Bytes
#define DMA_TXBUFFER_SIZE  _1kBytes
#define DMACH_UART0RX      0
#define DMACH_UART0TX      1
#define DMA_TRANSFER_SIZE  _8bit

extern uint8_t parseDiag;

void Uart0Setup( uint32_t buadRate, uint8_t parity );
void Uart0TX( uint32_t length );
uint8_t Uart0RX( void );
void PutChar( uint8_t data );
void ParseSetString( uint8_t * buffer );
void UART0_IRQHandler( void );

#endif
#endif
