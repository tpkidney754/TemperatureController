#include "ds18b20.h"

/*  All transactions must follow these steps
 *  1. Initialization/reset
 *  2. ROM Command followed by any required data exchange
 *  3. Function Command followed by any required data exchange
 */

uint8_t TransactionStepOne( )
{
   return SWC_ResetAndPresencePulses( );
}

void TransactionStepTwo( )
{
   DS8B20_ROMCode romCode;
   SWC_SendByte( READ_ROM );
   SWC_ReadData( ROM_BYTES, ( uint8_t * ) &romCode );
   uint8_t buffer[ 50 ];
   sprintf( buffer, "ROM Data\n" );
   LOG0( buffer );
   for( uint8_t i = 0; i < ROM_BYTES; i++ )
   {
      sprintf( buffer, "Byte %d: 0x%X\n", i, romCode.romBytes[ i ] );
      LOG0( buffer );
   }
}

float ReadTemp( )
{
   DS8B20_Scratchpad scratchpadData;
   uint8_t devicePresent = TransactionStepOne( );

   //if( devicePresent == 0 )
   //{
   //   return 0x0;
   //}

   TransactionStepTwo ( );
   // Send the CONVERT_T command byte
   SWC_SendByte( CONVERT_T );
   // The DS18B20 will transmit a 0 while the conversion
   // is in progress and a 1 when the conversion is complete.
   // The master can issue a read time slot to read the status
   // of the conversion.
   SWC_ReadStatusAndWait( );

   TransactionStepOne( );
   TransactionStepTwo( );
   SWC_SendByte( READ_SCRATCHPAD );
   SWC_ReadData( SCRATCPAD_BYTES, ( uint8_t * ) &scratchpadData );

   uint8_t buffer[ 50 ];
   sprintf( buffer, "Scratch Pad Data\n" );
   LOG0( buffer );
   for( uint8_t i = 0; i < SCRATCPAD_BYTES; i++ )
   {
      sprintf( buffer, "Byte %d: 0x%X\n", i, scratchpadData.scratchpadBytes[ i ] );
      LOG0( buffer );
   }

   uint16_t rawTemperatureData = scratchpadData.temperatureRawLSB;
   rawTemperatureData |= scratchpadData.temperatureRawMSB << 8;

   sprintf( buffer, "rawTemperatureData = 0x%X\n", rawTemperatureData );
   LOG0( buffer );
   return ConvertRawTemperatureData( rawTemperatureData );
}

float ConvertRawTemperatureData( uint16_t rawTemperatureData )
{
   float temperature;

   temperature = ( rawTemperatureData & 0x07F0 ) >> 4;

   if( ( rawTemperatureData & 0x000F ) >> 3 )
   {
      temperature += 0.5;
   }

   if( ( rawTemperatureData & 0xF000 ) >> 15 )
   {
      temperature *= -1;
   }

   return temperature;
}
