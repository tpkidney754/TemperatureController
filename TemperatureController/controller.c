#include "controller.h"

static uint8_t currentTemp;
static uint8_t desiredTemp;
static uint8_t tempRange;
static ControllerState_e state;

//*************************************************************************
// Function:  Controller_Init                                             *
//                                                                        *
// Description: Initializes the the static variables                      *
//                                                                        *
// Parameters:  NONE                                                      *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Controller_Init( )
{
   currentTemp = 75;
   desiredTemp = 75;
   tempRange = 10;
   state = noChange;
}

//*************************************************************************
// Function:  Controller_StateMachine                                     *
//                                                                        *
// Description: Initializes the the static variables                      *
//                                                                        *
// Parameters:  NONE                                                      *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Controller_StateMachine( )
{
   switch( state )
   {
      case noChange:
           currentTemp > desiredTemp ? SwitchLEDs( RED ) :
                                       SwitchLEDs( BLUE );
           ChnageDisplay( currentTemp );
           break;
      case changeDesiredTemp:
           SwitchLEDs( YELLOW );
           if( !( ADC0_SC2 & ADC_SC2_ADACT_MASK ) )
           {
              desiredTemp = ( uint8_t ) MAX_DISPLAY_VAL * ADC_GetCurrentValue( );
              ChnageDisplay( desiredTemp );
              ADC_StartConversion( ADC_CHANNEL );
           }
           break;
      case changeTempRange:
           SwitchLEDs( PURPLE );
           if( !( ADC0_SC2 & ADC_SC2_ADACT_MASK ) )
           {
              tempRange = ( uint8_t ) MAX_DISPLAY_VAL * ADC_GetCurrentValue( );
              ChnageDisplay( tempRange );
              ADC_StartConversion( ADC_CHANNEL );
           }
           break;
      case printSettings:
           SwitchLEDs( GREEN );
           uint8_t buffer[ 50 ];
           sprintf( buffer, "Desired Temp: %d, Temp Range: %d\n", desiredTemp, tempRange );
           LOG0( buffer );
           for( uint32_t i = 0; i < 1000000; i++ );
           controllerState = noChange;
           break;
   }
}

//*************************************************************************
// Function:  Controller_ChangeState                                      *
//                                                                        *
// Description: Updates the state the next state or to the start          *
//                                                                        *
// Parameters:  NONE                                                      *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Controller_ChangeState( )
{
   state == printSettings ? state = noChange : state++;
}

//*************************************************************************
// Function:  Controller_SetCurrentTemp                                   *
//                                                                        *
// Description: Updates the curernt temperature value to a new value      *
//                                                                        *
// Parameters:  uint8_t newTemp: New value of the current temperature.    *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Controller_SetCurrentTemp( uint8_t newTemp )
{
   currentTemp = newTemp;
}

//*************************************************************************
// Function:  Controller_ChangeDisplay                                    *
//                                                                        *
// Description: Updates the displays with the input value                 *
//                                                                        *
// Parameters:  uint8_t value: New value sent to the diplays              *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void Controller_ChnageDisplay( uint8_t value )
{
   UpdateDisplay( Display_Tens, value / 10 );
   UpdateDisplay( Display_Ones, value % 10 );
}
