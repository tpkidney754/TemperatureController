#ifdef FRDM
#ifndef __UART__
#define __UART__

#include "includeall.h"

#define OSR 16
#define CR  13
#define LF  10

extern uint8_t * RXBuffer;
extern uint8_t * RXBufferHead;
extern uint8_t parseDiag;

void Uart0Setup( uint32_t buadRate, uint8_t parity );
void Uart0TX( uint8_t * data, uint32_t length );
uint8_t Uart0RX( void );
void PutChar( uint8_t data );
void ParseSetString( uint8_t * buffer );
void UART0_IRQHandler( void );

#endif
#endif
