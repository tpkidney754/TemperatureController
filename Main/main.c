#include "includeall.h"

extern CircularBuffer_t * UART0_RXBuffer;
extern CircularBuffer_t * UART0_TXBuffer;
extern CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
extern CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

int main()
{

#ifdef FRDM
   Uart0Setup( 57600, 0 );
   LEDSetup();
   InitDisplay( 0 );
   InitDisplay( 1 );
   ADC_Init( ADC_CHANNEL );
   Button_Init( 0 );
   Controller_Init( );
   InitWaitTimer( );
   SWC_Init( );
#endif

#ifdef TESTING
   Testing();
#endif

   uint8_t buffer[ 100 ];
   float temperature = 0;
   temperature = ReadTemp( );
   sprintf( buffer, "Current temperature = %f\n", temperature );
   LOG0( buffer );
while( 1 )
{
#ifdef FRDM
   Controller_StateMachine( );

   if( parseDiag )
   {
      uint32_t length = UART0_RXBuffer->numItems;
      for( uint32_t i = 0; i < length; i++ )
      {
         CBufferRemove( UART0_RXBuffer, &buffer[ i ], DMACH_UART0RX  );
      }

      ParseDiag( buffer );

      parseDiag = 0;
   }


#endif
}

return 0;
}
