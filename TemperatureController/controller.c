#include "controller.h"

static uint8_t currentTemp;
static uint8_t desiredTemp;
static uint8_t tempRange;
static ControllerState_e controllerState;

void ControllerInit( )
{
   currentTemp = 75;
   desiredTemp = 75;
   tempRange = 10;
   controllerState = noChange;
}

void ControllerState( )
{
   switch( controllerState )
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
              desiredTemp = ADC_GetCurrentValue( );
              ChnageDisplay( desiredTemp );
              ADC_StartConversion( ADC_CHANNEL );
           }
           break;
      case changeTempRange:
           SwitchLEDs( PURPLE );
           if( !( ADC0_SC2 & ADC_SC2_ADACT_MASK ) )
           {
              tempRange = ADC_GetCurrentValue( );
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

void ChangeState( )
{
   controllerState == printSettings ? controllerState = noChange : controllerState++;
}

void SetCurrentTemp( uint8_t newTemp )
{
   currentTemp = newTemp;
}

void ChnageDisplay( uint8_t value )
{
   UpdateDisplay( 0, value / 10 );
   UpdateDisplay( 1, value % 10 );
}
