#include "adc.h"

static uint8_t ADC_value;

void ADC_Init( ADC_InputChannel ADC_ch )
{
   SET_BIT_IN_REG( SIM_SCGC5, ADC_PORT );
   SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_ADC0_MASK );
   SET_BIT_IN_REG( ADC_CH_PIN, PORT_PCR_MUX( 0 ) );
   SET_BIT_IN_REG( ADC0_CFG1, ADC_CFG1_ADLSMP_MASK );
   ADC_value = 0;
}

void ADC_StartConversion( ADC_InputChannel ADC_ch )
{
   NVIC_ClearPendingIRQ( ADC0_IRQn );
   NVIC_EnableIRQ( ADC0_IRQn );
   NVIC_SetPriority( ADC0_IRQn, 2 );
   SET_REG_VALUE( ADC0_SC1A, ADC_SC1_ADCH_MASK,
                             ADC_SC1_AIEN_MASK | ( ADC_ch & ADC_SC1_ADCH_MASK ) );
}

uint8_t ADC_GetCurrentValue( )
{
   return MAX_DISPLAY_VAL * ( ADC_value / MAX_VALUE );
}

void ADC0_IRQHandler( )
{
   NVIC_DisableIRQ( ADC0_IRQn );

   ADC_value = ( uint8_t ) ADC0_RA;
}
