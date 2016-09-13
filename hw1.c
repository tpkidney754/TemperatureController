#include "hw1.h"

char Reverse( char * str, int length )
{

   for( int i = 0; i < length/2; i++ )
   {
      // A ^ B ^ A = B
      // A = str[i], B = str[length-i]
      // A = A ^ B;
      *( str + i ) ^= *( str + length - i );
      // B = B ^ A = B ^ A ^ B = A
      *( str + length - i ) ^= *( str + i );
      // A = A ^ B ^ A = B
      *( str + i ) ^= *( str + length - i );
   }
   
   return str ? 0 : -1;

}