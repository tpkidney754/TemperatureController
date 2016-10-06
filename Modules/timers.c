#include "timers.h"

//*************************************************************************
// Function:  SetupPWM                                                    *
//                                                                        *
// Description: Sets up a PWM timers                                      *
//                                                                        *
// Parameters: uint8_t tpm: desired timer module                          *
//             uint8_t ch: desire tpm modules channel                     *
//             uint16_t modulus: desired modulus, or how man clk cycle    *
//                               before the counter increments            *
//             uint8_t prescaler: desired prescaler, divides modulus.     *
//             uint16_t pulseWidth: desired pulseWidth percentage, or     *
//                                  what percentage of the period is the  *
//                                  the signal is high.                   *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void SetupPWM( uint8_t tpm, uint8_t ch, uint16_t modulus, uint8_t prescaler, uint16_t pulseWidth )
{
   switch( tpm )
   {
      case 0:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM0_MASK );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM0_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM0_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM0_CNT = TPM_CNT_COUNT_MASK;
         TPM0_MOD = modulus;
         SET_BIT_IN_REG( TPM0_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM0_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
      case 1:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM1_MASK );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM1_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM1_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM1_CNT = TPM_CNT_COUNT_MASK;
         TPM1_MOD = modulus;
         SET_BIT_IN_REG( TPM1_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM1_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
      case 2:
         SET_BIT_IN_REG( SIM_SCGC6, SIM_SCGC6_TPM2_MASK );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_TRGSEL( 0xA ) );
         SET_BIT_IN_REG( TPM2_CONF, TPM_CONF_CROT_MASK );
         SET_BIT_IN_REG( TPM2_SC, TPM_SC_CMOD( 1 ) | TPM_SC_PS( prescaler ) );
         TPM2_CNT = TPM_CNT_COUNT_MASK;
         TPM2_MOD = modulus;
         SET_BIT_IN_REG( TPM2_CnSC( ch ), TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK );
         TPM2_CnV( ch ) = (uint16_t) modulus * ( pulseWidth / 100.0 );
         break;
   }
}

//*************************************************************************
// Function:  ChangeLEDPW                                                 *
//                                                                        *
// Description: Targets the TPM and CHs that drive the three LEDs to      *
//              change the PW of the signal that will in turn modify the  *
//              intensity of the light.                                   *
//                                                                        *
// Parameters: uint16_t pulseWidth: The new desired PW percentage.        *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void ChangeLEDPW( uint16_t pulseWidth )
{
   uint16_t valueToTPM0CnV = (uint16_t) TPM0_MOD * ( pulseWidth / 100.0 );
   uint16_t valueToTPM2CnV = (uint16_t) TPM2_MOD * ( pulseWidth / 100.0 );
   TPM2_C0V = valueToTPM2CnV;
   TPM2_C1V = valueToTPM2CnV;
   TPM0_C1V = valueToTPM0CnV;
}
