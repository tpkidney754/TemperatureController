#include "led.h"


void LEDSetup( void )
{
   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
   PORTB_PCR18 = PORT_PCR_MUX(3);
   PORTB_PCR19 = PORT_PCR_MUX(1);
   PORTD_PCR1 = PORT_PCR_MUX(1);
   GPIOB_PDDR |= ( RED_PIN );
   GPIOB_PDOR |= ( RED_PIN );
   GPIOB_PDDR |= ( GREEN_PIN );
   GPIOB_PDOR |= ( GREEN_PIN );
   GPIOD_PDDR |= ( BLUE_PIN );
   GPIOD_PDOR |= ( BLUE_PIN );
}

void SwitchLEDs( Color_t color )
{
   switch( color )
   {
      case RED: 
            GPIOB_PCOR |= ( RED_PIN );
            GPIOB_PSOR |= ( GREEN_PIN );
            GPIOD_PSOR |= ( BLUE_PIN );
            break;
      case GREEN: 
            GPIOB_PSOR |= ( RED_PIN );
            GPIOB_PCOR |= ( GREEN_PIN );
            GPIOD_PSOR |= ( BLUE_PIN );
            break;
      case BLUE:
            GPIOB_PSOR |= ( RED_PIN );
            GPIOB_PSOR |= ( GREEN_PIN );
            GPIOD_PCOR |= ( BLUE_PIN );
            break;
      case PURPLE:
            GPIOB_PCOR |= ( RED_PIN );
            GPIOB_PSOR |= ( GREEN_PIN );
            GPIOD_PCOR |= ( BLUE_PIN );     
            break;
      case YELLOW:
            GPIOB_PCOR |= ( RED_PIN );
            GPIOB_PCOR |= ( GREEN_PIN );
            GPIOD_PSOR |= ( BLUE_PIN ); 
            break;
      case WHITE:
            GPIOB_PCOR |= ( RED_PIN );
            GPIOB_PCOR |= ( GREEN_PIN );
            GPIOD_PCOR |= ( BLUE_PIN ); 
            break;
      case OFF:
            GPIOB_PSOR |= ( RED_PIN );
            GPIOB_PSOR |= ( GREEN_PIN );
            GPIOD_PSOR |= ( BLUE_PIN );   
            break;
      case NONE:
      default:
            break;

   }
}
