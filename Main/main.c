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
   InitSPI( 0 );
   nRF24L01_Config( 0 );
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

      ParseDiag( buffer );

      parseDiag = 0;
   }

   if( SPI_RXBuffer[0]->numItems )
   {
      LOG0( "Receiving data from SPI0: " );
      CBufferRemove( SPI_RXBuffer[0], &data );
      DumpMemory( &data, 1 );
      LOG0( "\n" );
   }
}
#endif

return 0;
}
