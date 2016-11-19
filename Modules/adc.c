#include "adc.h"


void ADC_Init( ADC_InputChannel ADC_ch )
{
   SET_BIT_IN_REG( SIM_SCGC5, ADC_PORT );
   SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_ADC0_MASK );
   // Starts conversion
   // SET_BIT_IN_REG( ADC0_SC1A, ( ADC_ch & ADC_SC1_ADCH_MASK ) );
}

void ADC_StartConversion( ADC_InputChannel ADC_ch )
{
   SET_BIT_IN_REG( ADC0_SC1A, ( ADC_ch & ADC_SC1_ADCH_MASK ) );
}


void ADC0_IRQHandler( )
{

}
