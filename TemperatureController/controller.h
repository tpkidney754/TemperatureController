#ifndef __CONTROLLER__
#define __CONTROLLER__

#include "includeall.h"

typedef enum
{
   noChange = 0,
   changeDesiredTemp,
   changeTempRange,
   printSettings,
} ControllerState_e;

void ControllerInit( );
void ControllerState( );
void ChangeState( );
void SetCurrentTemp( uint8_t newTemp );
void ChnageDisplay( uint8_t value );

#endif //__CONTROLLER__
