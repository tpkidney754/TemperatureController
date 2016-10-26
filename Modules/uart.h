#ifdef FRDM
#ifndef __UART__
#define __UART__

#include "includeall.h"
//#include "circularbuffer.h"

#define OSR 16
#define CR  13
#define LF  10
#define UART0_RXBuffer_SIZE   128
#define UART0_TXBuffer_SIZE   1024

extern uint8_t parseDiag;


void Uart0Setup( uint32_t buadRate, uint8_t parity );
void Uart0TX( uint32_t length );
uint8_t Uart0RX( void );
void PutChar( uint8_t data );
void ParseSetString( uint8_t * buffer );
void UART0_IRQHandler( void );

#endif
#endif
