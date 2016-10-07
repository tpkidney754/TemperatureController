#include "includeall.h"

int main()
{

#ifdef FRDM
   Uart0Setup( 57600, 0 );
   LEDSetup();
#endif


#ifdef DEBUG
   Testing();
#endif

#ifdef FRDM
   uint8_t character;
   uint8_t * buffer = malloc( sizeof( uint8_t ) * 100 );
   uint8_t * head = buffer;
   uint8_t starter[] = "You Entered: ";


while( 1 )
{
   if( parseDiag )
   {
      if( strstr( RXBuffer, "set") )
      {
         ParseDiag( RXBuffer );
      }
      parseDiag = 0;
   }
}
#endif

return 0;
}
