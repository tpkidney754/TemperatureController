#include "messaging.h"

CircularBuffer_t * TXBuffer;

#ifdef FRDM
static void (*commands[ NUM_COMMANDS ] )( uint8_t input ) =
             { SwitchLEDs,
               ChangeLEDPW,
               Controller_SetCurrentTemp,
               Controller_ChangeDisplay,
               Controller_SetDesiredTemp,
               Controller_SetTempRange };
#endif

MessagingErrors_e BuildMessage( Commands_e cmd, uint8_t numBytes, uint8_t * data )
{
   Message_t msg;
   msg.cmd = cmd;
   msg.numBytes = numBytes;

   for( uint8_t i = 0; i < numBytes; i++ )
   {
      msg.data[ i ] = *( data + i );
   }

   CalculateChecksum( &msg );

   return SendMessage( &msg );
}

MessagingErrors_e CalculateChecksum( Message_t * msg )
{
   // The checksum is all the values of the struct XORed with eachother.
   // On the receiving end, the checksum received will be run through the same calculations.
   // If the data was received correctly then the resulting calculation will be zero.
   // A ^ B ^ C ^ A ^ B ^ C == 0
   // If the value is not zero then an error was detected.

   uint8_t checksum = 0;
   checksum = msg->cmd;
   checksum ^= msg->numBytes;

   for( uint8_t i = 0; i < msg->numBytes; i++ )
   {
      checksum ^= msg->data[ i ];
   }

   msg->checksum = checksum;

   return noError;
}

MessagingErrors_e SendMessage( Message_t * msg )
{
   if( CBufferAdd( TXBuffer, &(msg->cmd) , DMACH_UART0TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   if( CBufferAdd( TXBuffer, &(msg->numBytes) , DMACH_UART0TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

   for( uint8_t i = 0; i < msg->numBytes; i++ )
   {
      if( CBufferAdd( TXBuffer, ( msg->data + i ), DMACH_UART0TX ) == BUFFER_FULL )
      {
         return txBufferFull;
      }
   }

   if( CBufferAdd( TXBuffer, &( msg->checksum ) , DMACH_UART0TX ) == BUFFER_FULL )
   {
      return txBufferFull;
   }

#ifdef FRDM
   SET_BIT_IN_REG( UART0_C2, UART0_C2_TIE_MASK );
#endif
}

MessagingErrors_e DecodeRxMessage( Message_t * msg )
{
   // This is an excellent oppurtunity for implementing function pointers
   // when I get the time.
#ifdef FRDM
   /*
   switch( msg->cmd )
   {
      case changeColor: SwitchLEDs( msg->data[ 0 ] ); break;
      case changePWM: ChangeLEDPW( msg->data[ 0 ] ); break;
      case setTemp: Controller_SetCurrentTemp( msg->data[ 0 ] ); break;
      case setDisplay: Controller_ChangeDisplay( msg->data[ 0 ] ); break;
   }
   */
   if( msg->cmd < NUM_COMMANDS )
   {
      commands[ msg->cmd ]( msg->data[ 0 ] );
   }
#endif
   return noError;
}
