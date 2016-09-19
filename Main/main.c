#include "includeall.h"

#ifdef DEBUG
#define PASS 0
void Testing();
#endif

int main()
{

#ifdef DEBUG
   Testing();
#endif
   
#ifdef PROJECT1
   Project1Report();
#endif

   return 0;
}

#ifdef DEBUG
void Testing()
{
   printf( "\n*****************  MyItoA Test  *********************** \n");

   int32_t data = 12345;
   int32_t base = 10;
   int8_t buffer[40];

   
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: %d, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 8;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: %o, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 16;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: 0x%X, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 2;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: 0x%X, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }

   data *= -1;
   printf( "\n*****************  MyItoA Test  *********************** \n");
   printf( "***************** Negative Num  *********************** \n");
   base = 10;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: %d, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 8;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: %o, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 16;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: 0x%X, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }
   base = 2;
   if( MyItoa( buffer, data, base ) == PASS )
   {
      printf( "\nData: 0x%X, Base: %d, Buffer: %s\n", data, base, buffer );
   }
   else
   {
      printf( "\nConversion Failed\n" );
   }

   printf( "\n***************** MyAtoi Test *********************** \n");
   int8_t str[] = "598403";
   data = MyAtoi( str );
   printf( "\nStr: %s, Data: %d \n", str, data );

   printf( "\n*****************  MyAtoi Test  *********************** \n");
   printf( "***************** Negative Num  *********************** \n");
   int8_t strneg[] = "-598403";
   data = MyAtoi( strneg );
   printf( "\nStr: %s, Data: %d \n", strneg, data );

   data = 0xDEADBEEF;
   uint8_t * pData = ( uint8_t * ) &data;
   printf( "\n***************** LittleToBig Test *********************** \n");
   printf( "Original Data\n");
   DumpMemory( pData, 4 );
   data = LittleToBig( data );
   printf( "After LittleToBig\n");
   DumpMemory( pData, 4 );
   printf( "\n***************** BigToLittle Test *********************** \n");
   data = BigToLittle( data );
   printf( "After BigToLittle\n");
   DumpMemory( pData, 4 );
   printf( "\n" );
}
#endif

