#include "led.h"


void LEDSetup( void )
{
   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
   PORTB_PCR18 = PORT_PCR_MUX(0);
   PORTB_PCR19 = PORT_PCR_MUX(0);
   PORTD_PCR1 = PORT_PCR_MUX(0);
   SET_BITS_IN_REG( GPIOB_PDDR, RED_PIN  );
   //GPIOB_PDOR |= ( RED_PIN );
   GPIOB_PDDR |= ( GREEN_PIN );
   //GPIOB_PDOR |= ( GREEN_PIN );
   GPIOD_PDDR |= ( BLUE_PIN );
   //GPIOD_PDOR |= ( BLUE_PIN );
}

void SwitchLEDs( Color_t color )
{
   switch( color )
   {
      case RED: 
            PORTB_PCR18 = PORT_PCR_MUX(3);
            PORTB_PCR19 = PORT_PCR_MUX(0);
            PORTD_PCR1 =  PORT_PCR_MUX(0);
            break;
      case GREEN: 
            PORTB_PCR18 = PORT_PCR_MUX(0);
            PORTB_PCR19 = PORT_PCR_MUX(3);
            PORTD_PCR1 =  PORT_PCR_MUX(0);
            break;
      case BLUE:
            PORTB_PCR18 = PORT_PCR_MUX(0);
            PORTB_PCR19 = PORT_PCR_MUX(0);
            PORTD_PCR1 =  PORT_PCR_MUX(4);
            break;
      case PURPLE:
            PORTB_PCR18 = PORT_PCR_MUX(3);
            PORTB_PCR19 = PORT_PCR_MUX(0);
            PORTD_PCR1 =  PORT_PCR_MUX(4);
            break;
      case YELLOW:
            PORTB_PCR18 = PORT_PCR_MUX(3);
            PORTB_PCR19 = PORT_PCR_MUX(3);
            PORTD_PCR1 =  PORT_PCR_MUX(0);
            break;
      case CYAN:
            PORTB_PCR18 = PORT_PCR_MUX(0);
            PORTB_PCR19 = PORT_PCR_MUX(3);
            PORTD_PCR1 =  PORT_PCR_MUX(4);
            break;
      case WHITE:
            PORTB_PCR18 = PORT_PCR_MUX(3);
            PORTB_PCR19 = PORT_PCR_MUX(3);
            PORTD_PCR1 =  PORT_PCR_MUX(4);
            break;
      case OFF:
            PORTB_PCR18 = PORT_PCR_MUX(0);
            PORTB_PCR19 = PORT_PCR_MUX(0);
            PORTD_PCR1 =  PORT_PCR_MUX(0);
            break;
      case NONE:
      default:
            break;

   }
}
