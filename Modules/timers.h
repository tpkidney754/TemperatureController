#ifndef __TIMERS__
#define __TIMERS__

#include "includeall.h"

#define MAX_MODULUS 	   0xFFFF
#define MAX_PRESCALER 	0x7

#define NS_PER_SEC         1000000000
#define _10US_PER_SEC      10000000
#define UNITS_US           1000000
#define NS_PER_US          1000

#define PROFILER_TPM             1
#define PROFILER_CH              1
#define PROFILER_PERIOD_IN_US    10

#ifdef FRDM
void SetupPWM( uint8_t tpm, uint8_t ch, uint16_t modulus, uint8_t prescaler, uint16_t pulseWidth );
void ChangeLEDPW( uint16_t pulseWidth );
void InitProfilerTimer( uint8_t tpm, uint8_t ch, uint32_t intervalInUS );
#endif

uint32_t GetTime( );
uint32_t GetElapsedTime( uint32_t start, uint32_t end );

#endif //__TIMERS__
