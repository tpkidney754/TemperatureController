#ifndef __PUSHBUTTON__
#define __PUSHBUTTON__

#include "includeall.h"

#define NUM_BUTTONS     1

#define BUTTON0_PIN     0x00000002
#define BUTTON0         PORTA_PCR1

void Button_Init( uint8_t buttonNum );
#endif // __PUSHBUTTON__
