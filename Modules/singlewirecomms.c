#include "singlewirecomms.h"

void SWC_Init( )
{
   SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTA_MASK );
   SET_BIT_IN_REG( PORTA_PCR5, PORT_PCR_MUX( PIN_GPIO ) );
   //SWITCH_TO_TX;
}

uint8_t SWC_ResetAndPresencePulses( )
{
   SWITCH_TO_TX;
   RELEASE_LINE;
   //Wait 480 us
   WaitInUs( 480 );
   RELEASE_LINE;
   SWITCH_TO_RX;
   // Once the slave detects the rising edge from the bus release,
   // it will wait 15-60 us and then pull the bus low itself.
   //Wait 60 us
   WaitInUs( 60 );
   // The bus will then pull the bus low for 60-240 us.
   for( uint8_t i = 0; i < 18; i++ )
   {
      if( READ_LINE == 0 )
      {
         return 1;
      }
      else
      {
         WaitInUs( 10 );
      }
   }

   return 0;
   // If the bus is low then slave present.

}

void SWC_SendByte( uint8_t data )
{
   SWITCH_TO_TX;

   for( uint8_t i = 0; i < 8; i++ )
   {
      data >>= i;
      if( data & 0x1 )
      {
         PULL_LOW;
         // Wait15us
         WaitInUs( 15 );
         RELEASE_LINE;
         // Wait45us
         WaitInUs( 45 );
      }
      else
      {
         PULL_LOW;
         // Wait60us
         WaitInUs( 60 );
      }

      // wait 1us
      WaitInUs( 1 );
   }
}

void SWC_ReadData( uint8_t bytesToRead, uint8_t * data )
{
   uint8_t tempData;
   SWITCH_TO_TX;
   PULL_LOW;
   // wait 1us
   WaitInUs( 480 );
   RELEASE_LINE;
   SWITCH_TO_RX;

   //wait for 10 us
   WaitInUs( 10 );
   for( uint8_t i = 0; i < bytesToRead; i++ )
   {
      for( uint8_t j = 0; j < 8; j++ )
      {
         if( READ_LINE )
         {
            tempData |= 1 << j;
         }
         //wait 60us
         WaitInUs( 60 );
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
   WaitInUs( 1 );
   RELEASE_LINE;
   SWITCH_TO_RX;
   // wait 15us
   WaitInUs( 15 );
   while( READ_LINE == 0 );
}
