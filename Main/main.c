#include "includeall.h"

extern CircularBuffer_t * RXBuffer;
extern CircularBuffer_t * TXBuffer;

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
while( 1 )
{
   if( parseDiag )
   {
      uint32_t length = RXBuffer->numItems;
      for( uint32_t i = 0; i < length; i++ )
      {
         CBufferRemove( RXBuffer, &buffer[ i ] );
      }

      if( strstr( buffer, "set") )
      {
         ParseDiag( buffer );
      }

      parseDiag = 0;
   }
}
#endif

return 0;
}
