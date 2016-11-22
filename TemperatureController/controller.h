#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "includeall.h"


#define MAX_DISPLAY_VAL  99

typedef enum
{
   noChange = 0,
   changeDesiredTemp,
   changeTempRange,
   printSettings,
} ControllerState_e;

void Controller_Init( );
void Controller_StateMachine( );
void Controller_ChangeState( );
void Controller_SetCurrentTemp( uint8_t newTemp );
void Controller_ChangeDisplay( uint8_t value );

#endif //__CONTROLLER__
