#ifndef __MEMORYUNITTEST__
#define __MEMORYUNITTEST__

#include "includeall.h"

#define MEM_MOVE_SIZE      23
#define TESTSTRING         "This is my test string"
#define MY_MEM_ZERO_SIZE   50
#define MY_REVERSE_INPUTS  3
#define MY_STR_LEN_INPUTS  2
#define MAIN_HEADER        2

#define TESTING_DMA_CH     3

void MemoryTesting( void );
void MyMemMoveUnitTest( void );
void MyMemZeroUnitTest( void );
void MyReverseUnitTest( void );
void MyStrLenUnitTest( void );

#endif //__MEMORYUNITTEST__
