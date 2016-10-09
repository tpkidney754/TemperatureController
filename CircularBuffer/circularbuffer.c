#include "circularbuffer.h"

uint32_t CBufferInit( CircularBuffer_t * cb, uint32_t itemSize, uint32_t maxItems )
{
   cb->bufferStart = malloc( itemSize * maxItems );
   cb->head = cb->bufferStart;
   cb->tail = cb->bufferStart;
   cb->bufferEnd = cb->bufferStart + ( maxItems * itemSize );
   cb->numItems = 0;
   cb->itemSize = itemSize;
   cb->size = maxItems;

   return cb == NULL ? 0 : -1;
}

enum BufferState IsBufferFull( CircularBuffer_t * cb )
{
   // Simple check to see if the number of items placed in the buffer
   // that have not been read is the same as the size of the buffer.
   return ( cb->numItems == cb->size ) ? BUFFER_FULL : BUFFER_NOT_FULL;
}

enum BufferState IsBufferEmpty( CircularBuffer_t * cb )
{
   // Simple check to see if anything has been written to the buffer
   // that has not been read.
   return ( cb->numItems == 0 ) ? BUFFER_EMPTY : BUFFER_NOT_EMPTY;
}

enum BufferState CBufferAdd( CircularBuffer_t * cb, void * data )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, cb->itemSize );
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart : ( uint8_t * ) cb->head + cb->itemSize;
   cb->numItems++;
}

enum BufferState CBufferRemove( CircularBuffer_t * cb, void * data )
{
   if( IsBufferEmpty( cb ) )
   {
      return BUFFER_EMPTY;
   }

   MyMemMove( ( uint8_t *) cb->tail, ( uint8_t *) data, cb->itemSize );
   cb->tail = ( cb->tail == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart : ( uint8_t * ) cb->tail + cb->itemSize;
   cb->numItems--;
}
