#include "memory.h"

uint8_t dmaComplete[ 4 ];
//*************************************************************************
// Function:  MyMemMove                                                   *
//                                                                        *
// Description: Moves a portion of memory to another location in memory.  *
//                                                                        *
// Parameters: uint8_t * src: Start of memory to be moved.                *
//             uint8_t * dst: Start of memory to be copied to.            *
//             int32_t length: Number of bytes to be moved.               *
//                                                                        *
// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
//                        values are a failure.                           *
//*************************************************************************
int8_t MyMemMove( uint8_t * src, uint8_t * dst, uint32_t numBytes, uint8_t DMAch )
{
   if( src == NULL || dst == NULL )
   {
      return -1;
   }
   // Can use DMA for overlapping regions like this. So using slow method.
   if( ( dst > src ) && ( dst <= ( src + numBytes ) ) )
   {
      dst += numBytes;
      src += numBytes;
      for( int32_t i = numBytes; i >= 0; i-- )
      {
         *dst-- = *src--;
      }

      return dst ? 0 : -1;
   }

   uint8_t remainder = numBytes % 4;
   if( remainder )
   {
      numBytes -= remainder;
      StartTransfer32bitMoves( DMAch, src, dst, numBytes );
      // Have to wait until first transfer is complete.
      while( dmaComplete[ DMAch ] == 0 );
      StartTransfer8bitMoves( DMAch, src, dst, remainder );

      return 0;
   }

   StartTransfer32bitMoves( DMAch, src, dst, numBytes );

   return 0;

}

//*************************************************************************
// Function:  MyMemZero                                                   *
//                                                                        *
// Description: Moves the value zero to a number of bytes in memory.      *
//                                                                        *
// Parameters: uint8_t * src: Start of memory to be zeroed                *
//             int32_t length: Number of bytes to be zeroed               *
//                                                                        *
// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
//                        values are a failure.                           *
//*************************************************************************
int8_t MyMemZero( uint8_t * src, uint32_t length )
{
   if( src == NULL )
   {
      return -1;
   }

   for( int32_t i = 0; i < length; i++ )
   {
      *src++ = 0;
   }

   return src ? 0 : -1;
}

//*************************************************************************
// Function:  MyMemZero                                                   *
//                                                                        *
// Description: Reverses the bytes starting at a location given           *
//                                                                        *
// Parameters: uint8_t * src: Start of memory to be reversed              *
//             int32_t length: Number of bytes to be revversed            *
//                                                                        *
// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
//                        values are a failure.                           *
//*************************************************************************
int8_t MyReverse( uint8_t * src, uint32_t length )
{
   if( src == NULL )
   {
      return -1;
   }

   int32_t loopLength = length--/2;

   for( int32_t i = 0; i < loopLength; i++ )
   {
      // A XOR B XOR A = B
      // A = *( src + i )
      // B = *( src + length - i )

      // A = A ^ B;
      *( src + i ) ^= *( src + length - i );
      // B = B ^ A = B ^ A ^ B = A
      *( src + length - i ) ^= *( src + i );
      // A = A ^ B = A ^ B ^ A = B
      *( src + i ) ^= *( src + length - i );
   }

   return src ? 0 : -1;
}

//*************************************************************************
// Function:  MyStringLength                                              *
//                                                                        *
// Description: Reverses the bytes starting at a location given           *
//                                                                        *
// Parameters: uint8_t * src: Start of memory to be reversed              *
//             int32_t length: Number of bytes to be revversed            *
//                                                                        *
// Return Value:  int8_t: pass/fail value. Success is a 0 value, all      *
//                        values are a failure.                           *
//*************************************************************************
int32_t MyStrLen( uint8_t * str )
{
   if( str == NULL )
   {
      return -1;
   }

   int32_t length = 0;

   while( *str++ != '\0' )
   {
      length++;
   }

   return length;
}
