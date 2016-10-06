#ifndef __TIMERS__
#define __TIMERS__

#include "includeall.h"

#define MAX_MODULUS 	0xFFFF
#define MAX_PRESCALER 	0x7

void SetupPWM( uint8_t tpm, uint8_t ch, uint16_t modulus, uint8_t prescaler, uint16_t pulseWidth );
void ChangeLEDPW( uint16_t pulseWidth );

#endif //__TIMERS__