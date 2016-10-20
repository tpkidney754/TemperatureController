#include "circularbuffer.h"

CircularBuffer_t * CBufferInit( uint32_t itemSize, uint32_t maxItems )
{
   CircularBuffer_t cb;
   cb.bufferStart = malloc( itemSize * maxItems );
   cb.head = cb.bufferStart;
   cb.tail = cb.bufferStart;
   cb.bufferEnd = cb.bufferStart + ( maxItems * itemSize ) - 1;
   cb.numItems = 0;
   cb.itemSize = itemSize;
   cb.size = maxItems;
   CircularBuffer_t * pcb = malloc( sizeof( cb ) );

   pcb->bufferStart = malloc( itemSize * maxItems );
   pcb->head = pcb->bufferStart;
   pcb->tail = pcb->bufferStart;
   pcb->bufferEnd = pcb->bufferStart + ( maxItems * itemSize ) - 1;
   pcb->numItems = 0;
   pcb->itemSize = itemSize;
   pcb->size = maxItems;

   return pcb;
}

inline enum BufferState IsBufferFull( CircularBuffer_t * cb )
{
   // Simple check to see if the number of items placed in the buffer
   // that have not been read is the same as the size of the buffer.
   return ( cb->numItems == cb->size ) ? BUFFER_FULL : BUFFER_NOT_FULL;
}

inline enum BufferState IsBufferEmpty( CircularBuffer_t * cb )
{
   // Simple check to see if anything has been written to the buffer
   // that has not been read.
   return ( cb->numItems == 0 ) ? BUFFER_EMPTY : BUFFER_NOT_EMPTY;
}

inline enum BufferState CBufferAdd( CircularBuffer_t * cb, void * data )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, cb->itemSize );
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart : ( uint8_t * ) ( cb->head + cb->itemSize );
   cb->numItems++;
}

inline enum BufferState CBufferRemove( CircularBuffer_t * cb, void * data )
{
   if( IsBufferEmpty( cb ) )
   {
      return BUFFER_EMPTY;
   }

   MyMemMove( ( uint8_t *) cb->tail, ( uint8_t *) data, cb->itemSize );
   cb->tail = ( cb->tail == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart : ( uint8_t * ) ( cb->tail + cb->itemSize );
   cb->numItems--;
}

void CBufferDestruct( CircularBuffer_t ** pcb )
{
   CircularBuffer_t * cb = *pcb;
   free( cb->bufferStart );
   free( *pcb );
   *pcb = NULL;

}
