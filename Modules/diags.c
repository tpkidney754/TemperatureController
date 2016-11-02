#ifdef FRDM
#include "diags.h"

//*************************************************************************
// Function:  ParseDiag                                                   *
//                                                                        *
// Description: Receives a string signifying a diag command from          *
//              the serial port.                                          *
//                                                                        *
// Parameters: uint8_t * buffer: pointer to a string buffer.              *
//                                                                        *
// Return Value:  NONE                                                    *
//*************************************************************************
void ParseDiag( uint8_t * buffer )
{
   // Support up to four commands with 10 characters each.
   uint8_t commands[ 4 ][ 10 ];
   size_t length;
   size_t i = 0;
   uint8_t * currentCommand;

   currentCommand = strtok( buffer, "\n " );

   while( currentCommand != NULL )
   {
      strcpy( commands[ i++ ], currentCommand );
      currentCommand = strtok( NULL, "\n " );
   }

   length = MyStrLen( commands[ i - 1 ] );
   commands[ i - 1 ][ length - 1 ] = '\0';

   i = 0;

   if( strstr( commands[ i ], "set" ) )
   {
      i++;
      if( strstr( commands[ i ], "color" ) )
      {
         i++;
         Color_t color = NONE;
         if( strstr( commands[ i ], "red" ) )
         {
            color = RED;
         }
         else if( strstr( commands[ i ], "green" ) )
         {
            color = GREEN;
         }
         else if( strstr( commands[ i ], "blue" ) )
         {
            color = BLUE;
         }
         else if( strstr( commands[ i ], "purple" ) )
         {
            color = PURPLE;
         }
         else if( strstr( commands[ i ], "yellow" ) )
         {
            color = YELLOW;
         }
         else if( strstr( commands[ i ], "cyan") )
         {
            color = CYAN;
         }
         else if( strstr( commands[ i ], "white" ) )
         {
            color = WHITE;
         }
         else if( strstr( commands[ i ], "off" ) )
         {
            color = OFF;
         }
         else
         {
            LOG0( "Invalid color given\n" );
         }

         SwitchLEDs( color );
      }
      else if ( strstr( commands[ i ], "power" ) )
      {
         i++;
         uint32_t pulseWidth;
         pulseWidth = MyAtoi( commands[ i ] );
         ChangeLEDPW( pulseWidth );
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
   else if( strstr( commands[ i ], "read" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint32_t reg = MyAtoi( commands[ i ] );
         nRF24L01_ReadReg( 0, reg );
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
   else if( strstr( commands[ i ], "send" ) )
   {
      i++;
      if( strstr( commands[ i ], "nop" ) )
      {
         nRF24L01_SPIMessage_t msg;
         msg.command = NOP;
         msg.bytesToSend = 0;
         msg.spiCh = 0;

         nRF24L01_TXData( &msg );
      }
      else
      {
         LOG0( "Invalid subcommand\n" );
      }
   }
   else if( strstr( commands[ i ], "write" ) )
   {
      i++;
      if( strstr( commands[ i ], "reg" ) )
      {
         i++;
         uint32_t reg = MyAtoi( commands[ i++ ] );
         uint32_t value = MyAtoi( commands[ i ] );
         nRF24L01_WriteReg( 0, reg, value );

      }
   }
}

#endif
