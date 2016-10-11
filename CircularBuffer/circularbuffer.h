#ifndef __CIRCBUFF__
#define __CIRCBUFF__

#include "includeall.h"

typedef struct CircularBuffer_t
{
   void * bufferStart;
   void * head;
   void * tail;
   void * bufferEnd;
   uint32_t size;
   uint32_t numItems;
   uint32_t itemSize;
} CircularBuffer_t;

typedef enum BufferState
{
   BUFFER_NOT_FULL = 0,
   BUFFER_FULL = 1,
   BUFFER_NOT_EMPTY = 0,
   BUFFER_EMPTY = 1
} BufferState;

CircularBuffer_t * CBufferInit( uint32_t itemSize, uint32_t maxItems );
enum BufferState IsBufferFull( CircularBuffer_t * cb );
enum BufferState IsBufferEmpty( CircularBuffer_t * cb );
enum BufferState CBufferAdd( CircularBuffer_t * cb, void * data );
enum BufferState CBufferRemove( CircularBuffer_t * cb, void * data );
void CBufferDestruct( CircularBuffer_t ** cb );

#endif //__CIRCBUFF__
