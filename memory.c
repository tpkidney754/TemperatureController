#include "memory.h"

int8_t MyMemMove( uint8_t * src, uint8_t * dst, uint32_t length )
{
	if( src == NULL || dst == NULL )
	{
		return -1;
	}

	for( int32_t i = 0; i < length-1; i++ )
	{
		*dst++ = *src;
	}

	return dst ? 0 : -1;

}

int8_t MyMemZero( uint8_t * src, uint32_t length )
{
	if( src == NULL )
	{
		return -1;
	}

	for( int32_t i = 0; i < length-1; i++ )
	{
		*src++ = 0;
	}

	return src ? 0 : -1;
}

int8_t MyReverse( uint8_t * src, uint32_t length )
{
	if( src == NULL )
	{
		return -1;
	}

	int32_t loopLength = length--/2;
	
	for( int32_t i = 0; i < loopLength; i++ )
	{
		*( src + i ) ^= *( src + length - i );
		*( src + length - i ) ^= *( src + i );
		*( src + i ) ^= *( src + length - i );
	}

	return src ? 0 : -1;
}