#ifdef TESTING
#include "memorytesting.h"

void MemoryTesting( )
{
   MyMemMoveUnitTest( );
   MyMemZeroUnitTest( );
   MyReverseUnitTest( );
   MyStrLenUnitTest( );
}

void MyMemMoveUnitTest(  )
{
   sprintf( headerBuffer, "MyMemmove Unit Test" );
   uint8_t testString[ MEM_MOVE_SIZE ] = TESTSTRING;
   uint8_t * memloc1 = malloc( sizeof( uint8_t ) * MEM_MOVE_SIZE * 2 );
   uint8_t * memloc2 = memloc1 + ( sizeof( uint8_t ) * MEM_MOVE_SIZE );
   uint8_t fail = 0;

   strcpy( memloc1, testString );

   PrintHeader( headerBuffer, main_e );

   MyMemMove( memloc1, memloc2, MEM_MOVE_SIZE );
   if( strcmp( memloc2, testString ) != PASS )
   {
      sprintf( testPrintBuffer, "Direct copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2 );
      LOG0( testPrintBuffer );
      fail = 1;
   }

   // memloc2 overlaps memloc1
   memloc2 = memloc1 + 10;
   MyMemMove( memloc1, memloc2, MEM_MOVE_SIZE );
   if( strcmp( memloc2, testString ) != PASS )
   {
      sprintf( testPrintBuffer, "Oeverlap copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2 );
      LOG0( testPrintBuffer );
      fail = 1;
   }

   // memloc1 overlaps memloc2
   memloc2 = memloc1;
   memloc1 += 10;
   strcpy( memloc1, testString );
   MyMemMove( memloc1, memloc2, MEM_MOVE_SIZE );
   if( strcmp( memloc2, testString ) != PASS )
   {
      sprintf( testPrintBuffer, "Oeverlap copy failed! Expected %s, Copied Loc: %s\n", testString, memloc2 );
      LOG0( testPrintBuffer );
      fail = 1;
   }

   PrintHeader( headerBuffer, fail );

   memloc1 -= 10;
   free( memloc1 );

}

void MyMemZeroUnitTest( void )
{
   sprintf( headerBuffer, "MyMemZero Unit Test");
   PrintHeader( headerBuffer, main_e );

   uint8_t * memloc = malloc( sizeof( uint8_t ) * MY_MEM_ZERO_SIZE );
   uint8_t fail = 0;

   for( uint32_t i = 0; i < MY_MEM_ZERO_SIZE; i++ )
   {
      *( memloc + i ) = 0xA5;
   }

   MyMemZero( memloc, MY_MEM_ZERO_SIZE );

   for( uint32_t i = 0; i < MY_MEM_ZERO_SIZE; i++ )
   {
      if( *( memloc + i ) != 0 )
      {
         fail = 1;
      }
   }

   PrintHeader( headerBuffer, fail );
}

void MyReverseUnitTest( void )
{
   uint8_t fail = 0;
   sprintf( headerBuffer, "MyReverse Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t myReverseUnitTestInputs[ MY_REVERSE_INPUTS ][ 35 ] = { "This is a string",
                                                                  "some NUMbers12345",
                                                                  "Does it reverse \n\0\t correctly?"
                                                                };

   uint8_t myReverseUnitTestExpectedOutputs[ MY_REVERSE_INPUTS ][ 35 ] = { "gnirts a si sihT",
                                                                           "54321srebMUN emos",
                                                                           "?yltcerroc \t\0\n esrever ti seoD"
                                                                         };
   uint8_t myReverseUnitTestInputsLengths[ MY_REVERSE_INPUTS ] = { 16, 17, 30 };

   for( uint32_t i = 0; i < MY_REVERSE_INPUTS; i++ )
   {
      MyReverse( myReverseUnitTestInputs[ i ], myReverseUnitTestInputsLengths[ i ] );

      if( strcmp( myReverseUnitTestInputs[ i ], myReverseUnitTestExpectedOutputs[ i ] ) != PASS )
      {
         sprintf( testPrintBuffer, "Test Case Failed! Expected: %s, Observed: %s\n" ,
            myReverseUnitTestExpectedOutputs[ i ], myReverseUnitTestInputs[ i ] );
         LOG0( testPrintBuffer );
         fail = 1;
      }
   }

   PrintHeader( headerBuffer, fail );
}

void MyStrLenUnitTest( void )
{
   uint8_t fail = 0;
   uint32_t returnedLength = 0;
   uint8_t mystrLenUnitTestInputs[ MY_STR_LEN_INPUTS ][ 25 ] = { "This is a string",
                                                                  "some NUMbers12345" };

   uint8_t mystrLenUnitTestInputsLengths[ MY_STR_LEN_INPUTS ] = { 16, 17 };

   sprintf( headerBuffer, "MyStrLen Unit Test" );
   PrintHeader( headerBuffer, main_e );
   for( uint32_t i = 0; i < MY_STR_LEN_INPUTS; i++ )
   {
      returnedLength = MyStrLen( mystrLenUnitTestInputs[ i ] );
      if( returnedLength != mystrLenUnitTestInputsLengths[ i ] )
      {
         sprintf( testPrintBuffer, "Test Case Failed! Input: %s, Expected Length: %d, Observed: %d ",
                  mystrLenUnitTestInputs[ i ], mystrLenUnitTestInputsLengths[ i ], returnedLength );
         LOG0( testPrintBuffer );
         fail = 1;
      }
   }

   PrintHeader( headerBuffer, fail );
}

#endif // TESTING