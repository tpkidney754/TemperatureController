#ifdef TESTING
#include "circularbuffertesting.h"

CircularBuffer_t cb;
static uint8_t itemsToAdd[ BUFFER_SIZE ] = { 1, 2, 3, 4, 5, 6, 7 ,8, 9, 10 };
static uint8_t itemsRemoved[ REMOVE_ITEMS_LENGTH ];

void CircularBufferTesting( )
{
   InitBufferUnitTest( );
   AddItemsUnitTestBuffEmpty( );
   AddItemsUnitTestBuffHalfFull( );
   AddItemsUnitTestBuffFull( );
   RemoveItemUnitTestBuffFull( );
   RemoveItemUnitTestBuffHalfFull( );
   RemoveItemUnitTestBuffEmpty( );
   BufferTestFromTheMidPoint( );
}

void InitBufferUnitTest( )
{
   sprintf( headerBuffer, "InitBuffer Unit Test");
   PrintHeader( headerBuffer, main_e );
   CBufferInit( &cb, BUFFER_ITEM_SIZE, BUFFER_SIZE );
   sprintf( testPrintBuffer, "Initializing Circular Buffer\nSize: %d, ItemSize: %d, NumItems: %d\n",
            cb.size, cb.itemSize, cb.numItems );
   LOG0( testPrintBuffer );
}

void AddItemsUnitTestBuffEmpty( )
{
   sprintf( headerBuffer, "AddItems Buff Empty Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferEmpty( &cb ) != BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Not Empty!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < ADD_ITEMS_LENGTH; i++ )
   {
      if( CBufferAdd( &cb, &itemsToAdd[ i ] ) == BUFFER_FULL )
      {
         LOG0( "Buffer filled up while adding items!\n");
         fail = 1;
      }
   }

   LOG0( "Items Added, now dump the buffer\n" );
   DumpMemory( cb.bufferStart, cb.size );

   PrintHeader( headerBuffer, fail );
}

void AddItemsUnitTestBuffHalfFull( )
{
   sprintf( headerBuffer, "AddItems Half Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferEmpty( &cb ) == BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Empty!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < ADD_ITEMS_LENGTH; i++ )
   {
      if( ( CBufferAdd( &cb, &itemsToAdd[ i + ADD_ITEMS_LENGTH ] ) == BUFFER_FULL ) && ( i != ADD_ITEMS_LENGTH - 1 ) )
      {
         LOG0( "Buffer filled up while adding items!\n");
         fail = 1;
      }
   }
   LOG0( "Buffer should be full now verify: " );
   sprintf( testPrintBuffer, "Expecting: 1, Observed: %d\n", IsBufferFull( &cb ) );
   LOG0( testPrintBuffer );
   if( IsBufferFull( &cb ) != BUFFER_FULL)
   {
      fail = 1;
   }

   LOG0( testPrintBuffer );
   LOG0( "Items Added, now dump the buffer\n" );
   DumpMemory( cb.bufferStart, cb.size );

   PrintHeader( headerBuffer, fail );
}

void AddItemsUnitTestBuffFull( )
{
   sprintf( headerBuffer, "AddItems Buff Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferEmpty( &cb ) == BUFFER_EMPTY )
   {
      LOG0( "Buffer Was Empty!\n" );
      fail = 1;
   }

   if( CBufferAdd( &cb, &itemsToAdd[ 0 ] ) != BUFFER_FULL )
   {
      LOG0( "Buffer should be full but CBufferAdd did not return BUFFER_FULL!\n");
      fail = 1;
   }

   PrintHeader( headerBuffer, fail );
}

void RemoveItemUnitTestBuffFull( )
{
   sprintf( headerBuffer, "RemoveItems Buff Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferFull( &cb ) != BUFFER_FULL )
   {
      LOG0( "Buffer Was Not Full!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < REMOVE_ITEMS_LENGTH; i++ )
   {
      if( CBufferRemove( &cb, &itemsRemoved[ i ] ) == BUFFER_EMPTY )
      {
         LOG0( "Buffer emptied while adding items!\n");
         fail = 1;
      }
   }

   LOG0( "Items Removed, now dump the buffer\n" );
   DumpMemory( itemsRemoved, REMOVE_ITEMS_LENGTH );

   PrintHeader( headerBuffer, fail );
}

void RemoveItemUnitTestBuffHalfFull( )
{
   sprintf( headerBuffer, "Remove Items Buff Half Full Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferFull( &cb ) == BUFFER_FULL )
   {
      LOG0( "Buffer Is Still Full!\n" );
      fail = 1;
   }

   for( uint32_t i = 0; i < REMOVE_ITEMS_LENGTH; i++ )
   {
      if( ( CBufferRemove( &cb, &itemsRemoved[ i ] ) == BUFFER_EMPTY ) && ( i != REMOVE_ITEMS_LENGTH - 1 ) )
      {
         LOG0( "Buffer emptied while adding items!\n");
         fail = 1;
      }
   }

   sprintf( testPrintBuffer, "Verify the buffer is now empty: Expected 1, Observed: %d\n", IsBufferEmpty( &cb ) );
   LOG0( testPrintBuffer );
   if( IsBufferEmpty( &cb ) != BUFFER_EMPTY )
   {
      LOG0( "The Buffer Was Not Empty!\n" );
      fail = 1;
   }
   LOG0( "Items Removed, now dump the buffer\n" );
   DumpMemory( itemsRemoved, REMOVE_ITEMS_LENGTH );

   PrintHeader( headerBuffer, fail );
}

void RemoveItemUnitTestBuffEmpty( )
{
   sprintf( headerBuffer, "RemoveItems Buff Empty Unit Test" );
   PrintHeader( headerBuffer, main_e );
   uint8_t fail = 0;

   if( IsBufferFull( &cb ) == BUFFER_FULL )
   {
      LOG0( "Buffer Was Full!\n" );
      fail = 1;
   }

   if( CBufferRemove( &cb, &itemsRemoved[ 0 ] ) != BUFFER_EMPTY )
   {
      LOG0( "Buffer should be empty but CBufferAdd did not return BUFFER_EMPTY!\n");
      fail = 1;
   }

   PrintHeader( headerBuffer, fail );
}

void BufferTestFromTheMidPoint( )
{
   sprintf( headerBuffer, "Midpoint Buffer Test");
   PrintHeader( headerBuffer, main_e );
   LOG0( "Zero out buffer\n" );
   MyMemZero( cb.bufferStart, cb.size );
   DumpMemory( cb.bufferStart, cb.size );
   LOG0("\n");
   cb.head = cb.bufferStart;
   cb.tail = cb.bufferStart;
   cb.numItems = 0;
   LOG0("Adding items to fill half the buffer\n" );
   AddItemsUnitTestBuffEmpty( );
   LOG0("Removing items to empty the buffer, but place now the head is pointing to the midpoint\n" );
   RemoveItemUnitTestBuffHalfFull( );
   LOG0( "Fill buffer to the end.\n" );
   AddItemsUnitTestBuffEmpty( );
   LOG0( "Now buffer will wrap\n" );
   AddItemsUnitTestBuffHalfFull( );
   AddItemsUnitTestBuffFull( );
   RemoveItemUnitTestBuffFull( );
   RemoveItemUnitTestBuffHalfFull( );
   RemoveItemUnitTestBuffEmpty( );
}



#endif
