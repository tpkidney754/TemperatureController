#include "messaging.h"

void BuildMessage( Commands_e cmd, uint8_t numBytes, uint8_t * data )
{
   Message_t msg;
   msg.cmd = cmd;
   msg.numBytes = numBytes;
   msg.data = data;

   CalculateChecksum( &msg );
}

void CalculateChecksum( Message_t * msg )
{
   // The checksum is all the values of the struct XORed with eachother.
   // On the receiving end, the checksum received will be run through the same calculations.
   // If the data was received correctly then the resulting calculation will be zero.
   // A ^ B ^ C ^ A ^ B ^ C == 0
   // If the value is not zero then an error was detected.
   
   uint8_t checksum = 0;
   checksum = msg->cmd;
   checksum ^= msg->numBytes;

   for( uint8_t i = 0; i < numBytes; i++ )
   {
      checksum ^= data[ i ];
   }
   
   msg->checksum = checksum;
}

void SendMessage( Message_t * msg )
{
   if( CBufferAdd( TXBuffer, &(msg->cmd) , DMACH_UART0TX ) == BUFFER_FULL )
   {
      return Error;
   }

   if( CBufferAdd( TXBuffer, &(msg->numBytes) , DMACH_UART0TX ) == BUFFER_FULL )
   {
      return Error;
   }

   for( uint8_t i = 0; i < numBytes; i++ )
   {
      if( CBufferAdd( TXBuffer, ( msg->data + i ), DMACH_UART0TX ) == BUFFER_FULL )
      {
         return Error;
      }
   }

#ifdef FRDM
   SET_BIT_IN_REG( UART0_C2, UART0_C2_TIE_MASK );
#endif
}

void DecodeRxMessage( Message_t * msg )
{
   // This is an excellent oppurtunity for implementing function pointers
   // when I get the time.
   switch( msg->cmd )
   {
      case changeColor: SwitchLEDs( msg->data[ 0 ] ); break;
      case changePWM: ChangeLEDPW( msg->data[ 0 ] ); break;
      case cycleLEDs: //cycleLEDs( ); break;
   }
}