#include "pushbutton.h"

static Color_t color;
void Button_Init( uint8_t buttonNum )
{
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   SET_BIT_IN_REG( BUTTON0, PORT_PCR_IRQC( ActiveHighIRQ ) |
                            PORT_PCR_MUX( PIN_GPIO ) |
                            PORT_PCR_PE_MASK |
                            PORT_PCR_PS_MASK );
   //SET_BIT_IN_REG( GPIOC_PDDR, BUTTON0_PIN );
   NVIC_ClearPendingIRQ( PORTA_IRQn );
   NVIC_EnableIRQ( PORTA_IRQn );
   NVIC_SetPriority( PORTA_IRQn, 2 );
   color = RED;
}

void PORTA_IRQHandler( )
{
   NVIC_DisableIRQ( PORTA_IRQn );
   if( BUTTON0 & PORT_PCR_ISF_MASK )
   {
      SET_BIT_IN_REG( BUTTON0, PORT_PCR_ISF_MASK );
      SwitchLEDs( color++ );
      if( color == OFF )
      {
         color = RED;
      }
   }
   NVIC_EnableIRQ( PORTA_IRQn );
}
