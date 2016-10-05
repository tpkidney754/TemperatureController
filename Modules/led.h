#ifndef __LED__
#define __LED__

#include "includeall.h"
//#include "MKL25Z4.h"
#define RED_PIN    1 << 18
#define GREEN_PIN  1 << 19
#define BLUE_PIN   1 << 1


typedef enum Color_t
{
	RED = 0,
	GREEN,
	BLUE,
	PURPLE,
	YELLOW,
	WHITE,
	OFF,
	NONE
} Color_t;

void LEDSetup( void );
void SwitchLEDs( Color_t color );

#endif // __LED__