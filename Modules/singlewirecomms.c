#include "singlewirecomms.h"

static SWC_rxData;

void SWC_Init( )
{
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   SET_BIT_IN_REG( PORTA_PCR5, PORT_PCR_MUX( PIN_GPIO ) );
   SWITCH_TO_OUTPUT;
}

uint8_t SWC_ResetAndPresencePulses( )
{
   SWITCH_TO_TX;
   PULL_LOW;
   //Wait 480 us
   RELEASE_LINE;
   SWITCH_TO_RX;
   //Wait 100 us
   // If the bus is low then slave present.
   return READ_LINE ? 0 : 1;
}

void SWC_SendByte( uint8 data )
{
   // SWC_ResetAndPresencePulses( );
   // SWITCH_TO_TX
   for( uint8_t i = 0; i < 8; i++ )
   {
      data =>> i;
      if( data & 0x1 )
      {
         PULL_LOW;
         // Wait15us
         RELEASE_LINE;
         // Wait45us
      }
      else
      {
         PULL_LOW;
         // Wait60us
      }

      // wait 1us
   }
}

void SWC_ReadData( uint8_t bytesToRead, uint8_t * data )
{
   uint8_t tempData[ MAX_BYTES ];
   SWITCH_TO_TX;
   PULL_LOW;
   // wait 1us
   RELEASE_LINE;
   SWITCH_TO_RX;

   //wait for 10 us
   for( uint8_t i = 0, i < bytesToRead; i++ )
   {
      for( uint8_t j = 0; j < 8; j++ )
      {
         tempData |= READ_LINE << j;
         //wait 60us
      }
      data[ i ] = tempData;
      tempData = 0;
   }
}

void SWC_ReadStatusAndWait( )
{
   SWITCH_TO_TX;
   PULL_LOW;
   // Wait 1us
   RELEASE_LINE;
   SWITCH_TO_RX;
   // wait 15us
   while( READ_LINE == 0 );
}
