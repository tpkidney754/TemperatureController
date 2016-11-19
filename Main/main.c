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
   ADC_StartConversion( ADC_CHANNEL );
#endif

#if ( defined( FRDM ) ||  defined( BBB ) )
   SPI_Init( 0, 1 );
#endif

#ifdef BBB
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
   uint8_t ADC_value;
while( 1 )
{
#ifdef FRDM
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

   ADC_StartConversion( ADC_CHANNEL );
   ADC_value = ADC_GetCurrentValue( );
   //sprintf( buffer, "Current Value: %d\n", ADC_value );
   //LOG0( buffer );
   UpdateDisplay( 0, ( uint8_t ) ( ADC_value / 10 ) );
   UpdateDisplay( 1, ( uint8_t ) ( ADC_value % 10 ) );

#endif
   if( SPI_RXBuffer[ 0 ]->numItems )
   {
      LOG0( "Received data from SPI0: " );
      CBufferRemove( SPI_RXBuffer[ 0 ], &data, NO_DMA );
      DumpMemory( &data, 1 );
      LOG0( "\n" );
   }
}

return 0;
}
