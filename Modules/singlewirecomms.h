#ifndef __SINGLE_WIRE__
#define __SINGLE_WIRE__

#include "includeall.h"

#define DATA_LINE          PORTA_PCR5
#define DATA_LINE_PIN      0x00000020

#define SWITCH_TO_RX       CLEAR_BITS_IN_REG( GPIOA_PDDR, DATA_LINE_PIN )
#define SWITCH_TO_TX       SET_BIT_IN_REG( GPIOA_PDDR, DATA_LINE_PIN )
#define WRITE_1            SET_BIT_IN_REG( GPIOCA_PCOR, DATA_LINE_PIN )
#define WRITE_0            SET_BIT_IN_REG( GPIOA_PSOR, DATA_LINE_PIN )
#define PULL_LOW           WRITE_0
#define RELEASE_LINE       WRITE_1
#define READ_LINE          ( GPIOA_PDIR & DATA_LINE_PIN ) >> 5

#define MAX_BYTES          8


void SWC_Init( );
void SWC_SendByte( uint8 data );
void SWC_ReadData( );
void SWC_ReadStatusAndWait( );
uint8_t SWC_ResetAndPresencePulses( );
void SWC_ROMCommandDataExchange( );

#endif // __SINGLE_WIRE__
