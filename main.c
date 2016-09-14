#include "includeall.h"
#include <stdlib.h>
#define LEN 10

int main(){
  /*
  uint8_t array[LEN] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  char string1[] = "This is a string";
  int string1Length = 16;
  char string2[] = "some NUMbers12345";
  int string2Length = 17;
  char string3[] = "Does it reverse \n\0\t correctly?";
  int string3Length = 30;
  MyReverse( string1, string1Length );
  printf( "%s\n", string1 );
  MyReverse( string2,  string2Length );
  printf( "%s\n", string2 );
  MyReverse( string3, string3Length );

for(int i = 0; i < string3Length; i++)
  printf( "%c", string3[i] );

  puts("\n");
  MyReverse( array, LEN );

for(int i = 0; i < LEN; i++ )
  printf( "%d%s", array[i], i == LEN-1 ? ".\n" : ", " );

puts("\n");*/

  uint8_t str[] = "-12345";
  int32_t data = 0;
  data = MyAtoi( str );
  printf("%d\n", data);
  return 0;
}