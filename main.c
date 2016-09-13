#include "includeall.h"

int main(){
  char string1[] = "This is a string";
  int string1Length = 15;
  char string2[] = "some NUMmbers12345";
  int string2Length = 17;
  char string3[] = "Does it reverse \n\0\t correctly?";
  int string3Length = 29;
  printf("%s\n", string1);
  Reverse( string1, string1Length );
  printf( "%s\n", string1 );
  Reverse( string2,  string2Length );
  printf( "%s\n", string2 );
  Reverse( string3, string3Length );

for(int i = 0; i < string3Length+1; i++ )
  printf( "%c", string3[i] );

puts("\n");

  return 0;
}