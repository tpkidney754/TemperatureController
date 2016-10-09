#ifdef TESTING
#ifndef __CIRCBUFFUNITTEST__
#define __CIRCBUFFUNITTEST__

#include "includeall.h"

#define BUFFER_SIZE              10
#define BUFFER_ITEM_SIZE         1
#define ADD_ITEMS_LENGTH      BUFFER_SIZE / 2
#define REMOVE_ITEMS_LENGTH   BUFFER_SIZE / 2

void CircularBufferTesting( void );
void InitBufferUnitTest( void );
void AddItemsUnitTestBuffEmpty( void );
void AddItemsUnitTestBuffHalfFull( void );
void AddItemsUnitTestBuffFull( void );
void RemoveItemUnitTestBuffFull( void );
void RemoveItemUnitTestBuffHalfFull( void );
void RemoveItemUnitTestBuffEmpty( void );
void BufferTestFromTheMidPoint( void );

#endif //__CIRCBUFFUNITTEST__
#endif
