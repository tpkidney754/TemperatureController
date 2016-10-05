#ifndef __UART__
#define __UART__

#include "includeall.h"

#define OSR 16

void Uart0Setup( uint32_t buadRate, uint8_t parity );
void Uart0TX( uint8_t * data, uint32_t length );
uint8_t Uart0RX( void );
void PutChar( uint8_t data );
void ParseSetString( uint8_t * buffer );

#endif