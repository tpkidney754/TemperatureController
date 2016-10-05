#ifndef __IO__
#define __IO__

#include "includeall.h"

#define WAIT_FOR_BIT_SET( BIT ) while( ( BIT ) == 0 )
#define WAIT_FOR_BIT_CLEAR( BIT ) while( ( BIT ) )
#define CLEAR_BITS_IN_REG( REG, BIT ) ( ( REG ) &= ~( BIT ) )
#define SET_BITS_IN_REG( REG, BIT ) ( ( REG ) |= ( BIT ) )
#define READ_BITS_FROM_REG( REG, BIT_MASK, BIT_SHIFT ) ( ( ( REG ) & ( BIT_MASK ) ) >> ( BIT_SHIFT ) ) 

#endif // __IO__