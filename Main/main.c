#include "includeall.h"

int main()
{

#ifdef DEBUG
   Testing();
#endif

#ifdef PROJECT1
   Project1Report();
#endif

   return 0;
}
