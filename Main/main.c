#include "includeall.h"

extern CircularBuffer_t * UART0_RXBuffer;
extern CircularBuffer_t * UART0_TXBuffer;
extern CircularBuffer_t * SPI0_RXBuffer;
extern CircularBuffer_t * SPI0_TXBuffer;
extern CircularBuffer_t * SPI1_RXBuffer;
extern CircularBuffer_t * SPI1_TXBuffer;

int main()
{

#ifdef FRDM
   Uart0Setup( 57600, 0 );
   LEDSetup();
#endif


#ifdef TESTING
   Testing();
#endif

#ifdef FRDM
   uint8_t buffer[ 100 ];
   uint8_t * head = buffer;
   uint8_t data;
while( 1 )
{
   if( parseDiag )
   {
      uint32_t length = UART0_RXBuffer->numItems;
      for( uint32_t i = 0; i < length; i++ )
      {
         CBufferRemove( UART0_RXBuffer, &buffer[ i ] );
      }

      if( strstr( buffer, "set") )
      {
         ParseDiag( buffer );
      }

      parseDiag = 0;
   }

   if( SPI0_RXBuffer->numItems )
   {
      CBufferRemove( SPI0_RXBuffer, &data );
      DumpMemory( &data, 1 );
   }
}
#endif

return 0;
}
