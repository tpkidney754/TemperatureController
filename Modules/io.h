
#ifdef FRDM
#ifndef __IO__
#define __IO__

#include "includeall.h"

#define PIN_DISABLE        0
#define PIN_GPIO           1
#define ALTERNATIVE_2      2
#define ALTERNATIVE_3      3
#define ALTERNATIVE_4      4
#define ALTERNATIVE_5      5
#define ALTERNATIVE_6      6
#define ALTERNATIVE_7      7


#define WAIT_FOR_BIT_SET( BIT ) while( ( BIT ) == 0 )
#define WAIT_FOR_BIT_CLEAR( BIT ) while( ( BIT ) )
#define CLEAR_BITS_IN_REG( REG, BITS ) ( ( REG ) &= ~( BITS ) )
#define SET_BIT_IN_REG( REG, BIT ) ( ( REG ) |= ( BIT ) )
// If a value in a reg is more than one bit, this will clear those bits and then set those
// bits without disturbing any of the other bits in the register.
#define SET_REG_VALUE( REG, MASK, VALUE )  CLEAR_BITS_IN_REG( ( REG ), ( MASK ) ); \
                                           SET_BIT_IN_REG( ( REG ), ( VALUE ) )
#define READ_BITS_FROM_REG( REG, BIT_MASK, BIT_SHIFT ) ( ( ( REG ) & ( BIT_MASK ) ) >> ( BIT_SHIFT ) )

#endif // __IO__
#endif
