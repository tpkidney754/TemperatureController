#ifdef TESTING
#include "testing.h"

static uint8_t fillerChar[ 3 ] = { '*', '@', '~' };

void Testing()
{
   DataTesting();
   MemoryTesting();
   CircularBufferTesting();
}

void PrintHeader( uint8_t * header, HeaderType_t headerType )
{
   if( headerType == pass_e )
   {
      strcat( header, "Passed Successfully!" );
   }
   else if( headerType == fail_e )
   {
      strcat( header, "Failed!" );
   }

   uint8_t fillerLength = HEADER_LENGTH - MyStrLen( header ) - 2;
   fillerLength /= 2;
   uint8_t * filler = malloc( sizeof( uint8_t ) * fillerLength + 1 );

   for( uint32_t i = 0; i < fillerLength; i++ )
   {
      filler[i] = fillerChar[ headerType ];
   }

   sprintf( testPrintBuffer, "\n%s %s %s\n", filler, header, filler );
   LOG0( testPrintBuffer );
}

#endif
