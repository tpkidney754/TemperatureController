#include "includeall.h"

int main()
{

#ifdef FRDM
   SystemInit();
   Uart0Setup( 57600, 0 );
   SetupPWM();
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
   do
   {
      *buffer = Uart0RX();
      PutChar( *buffer++ );
   } while( *( buffer - 1 ) != 13 );
   *buffer = 10;
   PutChar( *buffer++ );
   *buffer = '\0';
   buffer = head;
   if( strstr( buffer, "set" ) )
   {
      ParseSetString( buffer );
   }
}
#endif

return 0;
}
