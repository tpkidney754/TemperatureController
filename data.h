#ifndef __DATA__
#define __DATA__ 

#include "includeall.h"

int8_t * MyItoa( uint8_t * str, int32_t data, int32_t base );
int32_t MyAtoi( uint8_t * str );
void DumpMemory( uint8_t * start, uint32_t length );
int32_t BigToLittle( int32_t data );
int32_t LittleToBig( int32_t data );

#endif