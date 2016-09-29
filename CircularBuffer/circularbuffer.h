#include "includeall.h"

typedef struct circularBuffer
{
   uint8_t * buffer;
   uint32_t head;
   uint32_t tail;
   uint32_t size;
   uint32_t numItems;
} CircularBuffer; 

typedef enum BufferState
{
   BUFFER_NOT_FULL = 0,
   BUFFER_FULL = 1,
   BUFFER_NOT_EMPTY = 0,
   BUFFER_EMPTY = 1
} BufferState;

enum BufferState BufferFull( CircularBuffer * cb );
enum BufferState BufferEmpty( CircularBuffer * cb );
enum BufferState CBufferWrite( CircularBuffer * cb, uint8_t * data );
enum BufferState CBufferRead( CircularBuffer * cb, uint8_t * data );