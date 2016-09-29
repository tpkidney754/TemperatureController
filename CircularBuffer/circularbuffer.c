#include "circularbuffer.h"

enum BufferState BufferFull( CircularBuffer * cb )
{
   // Simple check to see if the number of items placed in the buffer
   // that have not been read is the same as the size of the buffer.
   return ( cb->numItems == cb->size ) ? BUFFER_FULL : BUFFER_NOT_FULL;
}

enum BufferState BufferEmpty( CircularBuffer * cb )
{
   // Simple check to see if anything has been written to the buffer
   // that has not been read.
   return ( cb->head == 0 ) ? BUFFER_EMPTY : BUFFER_NOT_EMPTY;
}

enum BufferState CBufferWrite( CircularBuffer * cb, uint8_t * data )
{
   if( BufferFull( cb ) )
   {
      return BUFFER_FULL;
   }

   // Adding an item to the buffer. The head is index into the buffer,
   // and cb->buffer is pointing to the start of the buffer.
   *( cb->buffer + cb->head ) = *data;
   // Incrementing the buffer is simple and easy as long as the size
   // of the buffer is a power of 2. As an example, lets say size = 8,
   // and the head is currently = 7 before the write comes in. After the
   // write we increment the head and now it equals 8 and then we mask the
   // head by size-1 which would 7. 0x8 = 0b1000 and 0x7 = 0b0111. 
   // Therefore 0b1000 & 0b0111 = 0b0000. Now the head is pointed back at the
   // start of the buffer as you would expect for a circular buffer.
   cb->head = ( cb->head + 1 ) & ( cb->size - 1 );
   cb->numItems++;
}

enum BufferState CBufferRead( CircularBuffer * cb, uint8_t * data )
{
   if( BufferEmpty( cb ) )
   {
      return BUFFER_EMPTY;
   }
   // Now we retrieve data, and tail will be the location of the buffer
   // after the last data that was read.
   *data =  *( cb->buffer+ cb->tail );
   // The tail will be updated in a similar fashion of updating the head.
   cb->tail = ( cb->tail + 1 ) & ( cb->size - 1 );
   cb->numItems--;
}
