#include "circularbuffer.h"

uint8_t dmaComplete[ 4 ];

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

inline BufferState_e IsBufferFull( CircularBuffer_t * cb )
{
   // Simple check to see if the number of items placed in the buffer
   // that have not been read is the same as the size of the buffer.
   return ( cb->numItems == cb->size ) ? BUFFER_FULL : BUFFER_NOT_FULL;
}

inline BufferState_e IsBufferEmpty( CircularBuffer_t * cb )
{
   // Simple check to see if anything has been written to the buffer
   // that has not been read.
   return ( cb->numItems == 0 ) ? BUFFER_EMPTY : BUFFER_NOT_EMPTY;
}

inline BufferState_e CBufferAdd( CircularBuffer_t * cb, void * data, uint8_t DMAch )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, cb->itemSize, DMAch );
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->head + cb->itemSize );
   cb->numItems++;
}

// If the numToAdd > cb->numItems + cb->size then this function will not add the total numToAdd.
// If there is a need to make sure all items get added, then that checking needs to be done outside
// by the code that is calling this function.
BufferState_e CBufferAddItems( CircularBuffer_t * cb, void * data,
                               uint32_t numToAdd, uint8_t DMAch )
{
   if( IsBufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   // If the total items is going to wrap the buffer, first add items to the end of the buffer.
   if( (cb->head + ( cb->itemSize * numToAdd ) ) >= cb->bufferEnd )
   {
      // if the first move is going to fill up the buffer, add items that fill up the buffer.
      // otherwise, fill up the buffer to the end point before wrapping.
      uint32_t firstMove = ( cb->numItems + numToAdd ) >= cb->size ?
                                                          cb->size - cb->numItems :
                                                        ( cb->bufferEnd - cb->head ) / cb->itemSize;
      // Start first transfer
      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, firstMove * cb->itemSize, DMAch );

      // Set the head to current value of the DMA destination pointer.
      cb->head += firstMove * cb->itemSize;
      // Wrap if needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      // Increment numItems as needed.
      cb->numItems += firstMove;
      // If the first move filled up the buffer then return.
      if( IsBufferFull( cb ) )
      {
         return BUFFER_FULL;
      }
      // Wait until first transfer is complete.
      while( dmaComplete[ DMAch ] == 0 );

      numToAdd -= firstMove;
      uint32_t secondMove = ( cb->numItems + numToAdd ) >= cb->size ?
                                                           cb->size - cb->numItems :
                                                           numToAdd;
      // StartSecondTransfer
      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, secondMove * cb->itemSize, DMAch );
      // Increment head to the end of the second transfer.
      cb->head += secondMove * cb->itemSize;
      // Increment head as needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      cb->numItems += secondMove;

      return IsBufferFull( cb );
   }
   // No buffer wrap will take place
   // Now there is a need to make sure that the numItems wont overfill buffer
   if( numToAdd + cb->numItems >= cb->size )
   {
      numToAdd = cb->size - cb->numItems;

      MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, numToAdd * cb->itemSize, DMAch );
      // Increment head to the end of the second transfer.
      cb->head += numToAdd * cb->itemSize;
      // Increment head as needed.
      cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                                 ( uint8_t * ) ( cb->head + cb->itemSize );
      cb->numItems += numToAdd;

      return IsBufferFull( cb );
   }

   MyMemMove( ( uint8_t *) data, ( uint8_t *) cb->head, numToAdd * cb->itemSize, DMAch );
   cb->head += numToAdd * cb->itemSize;
   cb->head = ( cb->head == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->head + cb->itemSize );
   cb->numItems += numToAdd;

   return IsBufferFull( cb );
}

inline BufferState_e CBufferRemove( CircularBuffer_t * cb, void * data )
{
   if( IsBufferEmpty( cb ) )
   {
      return BUFFER_EMPTY;
   }

   MyMemMove( ( uint8_t *) cb->tail, ( uint8_t *) data, cb->itemSize, 0 );
   cb->tail = ( cb->tail == cb->bufferEnd ) ? ( uint8_t * ) cb->bufferStart :
                                              ( uint8_t * ) ( cb->tail + cb->itemSize );
   cb->numItems--;
}

void CBufferDestruct( CircularBuffer_t ** pcb )
{
   CircularBuffer_t * cb = *pcb;
   free( cb->bufferStart );
   free( *pcb );
   *pcb = NULL;

}
