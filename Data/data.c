#include "data.h"

#define ASCIINUMBASE    0x30
#define ASCIILETTERBASE 0X37

int8_t * MyItoa( uint8_t * str, int32_t data, int32_t base )
{
	uint8_t negative = 0;
	uint32_t i = 0;
	if( data < 0 )
	{
		data *= -1;
		negative = 1;
	}
	uint8_t r = 0;
	do
	{
		r = ( uint8_t ) data % base;
		r += ( r > 9 ) ? ASCIILETTERBASE : ASCIINUMBASE;
		*( str + i++ ) = r;
	}while( ( data /= base ) > 0 );
	
	//*( str + i++ ) = ( uint8_t ) ( data % base + ASCINUMBASE );
	if( negative )
	{ 
		*( str + i++ ) = '-';
	}
	MyReverse( str, i );
	*(str + i ) = '\0';
	return 0;
}

int32_t MyAtoi( uint8_t * str )
{
	int32_t num = 0;
	uint8_t negative = 0;
	uint8_t * start = NULL;
	uint32_t length = 0;
	uint32_t i = 0;
	uint32_t temp = 0;
	
	if( *str == '-' )
	{
		negative = 1;
		str++;
	}

	start = str;

	while( *str++ )
	{
		length++;
	}

	i = length-1;
	str = start;
	while( (temp = *str++) != '\0' )
	{
		temp -= ASCIINUMBASE;
		for( int j = 0; j < i; j++ )
		{
			temp *= 10;
		}
		i--;
		num += temp;
	}


	return negative ? -num : num;
}

void DumpMemory( uint8_t * start, uint32_t length )
{
	for(uint32_t i = 0; i < length; i ++ )
	{
		printf( "%X ", *(start + i ) );
	}

	printf("\n");
}

int32_t BigToLittle( int32_t data )
{
	uint8_t byte0 = ( uint8_t ) ( ( data & BYTE3_MASK ) >> BYTE3_SHIFT );
	uint8_t	byte1 = ( uint8_t ) ( ( data & BYTE2_MASK ) >> BYTE2_SHIFT );
	uint8_t byte2 = ( uint8_t ) ( ( data & BYTE1_MASK ) >> BYTE1_SHIFT );
	uint8_t byte3 = ( uint8_t ) ( ( data & BYTE0_MASK ) >> BYTE0_SHIFT );

	uint32_t returnData = byte0 << BYTE0_SHIFT | byte1 << BYTE1_SHIFT | 
						  byte2 << BYTE2_SHIFT | byte3 << BYTE3_SHIFT;

	return returnData;


}

int32_t LittleToBig( int32_t data )
{
	uint8_t byte3 = ( uint8_t ) ( ( data & BYTE3_MASK ) >> BYTE3_SHIFT );
	uint8_t	byte2 = ( uint8_t ) ( ( data & BYTE2_MASK ) >> BYTE2_SHIFT );
	uint8_t byte1 = ( uint8_t ) ( ( data & BYTE1_MASK ) >> BYTE1_SHIFT );
	uint8_t byte0 = ( uint8_t ) ( ( data & BYTE0_MASK ) >> BYTE0_SHIFT );

	uint32_t returnData = byte0 << BYTE3_SHIFT | byte1 << BYTE2_SHIFT | 
						  byte2 << BYTE1_SHIFT | byte3 << BYTE0_SHIFT;

	return returnData;
}
