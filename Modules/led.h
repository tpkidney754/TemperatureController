#ifndef __LED__
#define __LED__

#include "includeall.h"

typedef enum Color_t
{
	RED = 0,
	GREEN,
	BLUE,
	PURPLE,
	YELLOW,
	CYAN,
	WHITE,
	OFF,
	NONE
} Color_t;

void LEDSetup( void );
void SwitchLEDs( Color_t color );

#endif // __LED__