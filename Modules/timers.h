#ifndef __TIMERS__
#define __TIMERS__

#include "includeall.h"

#define MODULUS 65535

void SetupPWM( void );
void ChangePW( uint16_t pulseWidth );

#endif //__TIMERS__