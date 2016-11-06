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
#endif

#if ( defined( FRDM ) ||  defined( BBB ) )
   InitSPI( 0, 1 );
#endif

#ifdef BBB
   //SPI_Test( 0 );
   for( uint8_t i = 0; i < FIFO_STATUS; i++ )
   {
      nRF24L01_ReadReg( 0, i );
   }
#endif

#ifdef TESTING
   Testing();
#endif

   uint8_t buffer[ 100 ];
   uint8_t * head = buffer;
   uint8_t data;
while( 1 )
{
#ifdef FRDM
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
#endif
   if( SPI_RXBuffer[ 0 ]->numItems )
   {
      LOG0( "Received data from SPI0: " );
      CBufferRemove( SPI_RXBuffer[ 0 ], &data );
      DumpMemory( &data, 1 );
      LOG0( "\n" );
   }
   /*
   if( SPI_RXBuffer[ 1 ]->numItems )
   {
      LOG0( "Receiving data from SPI1: " );
      CBufferRemove( SPI_RXBuffer[ 1 ], &data );
      DumpMemory( &data, 1 );
      LOG0( "\n" );
   }
   */
}

return 0;
}
