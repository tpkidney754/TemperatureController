#include <stdio.h>
#include <stdint.h>
#include "memory.h"
#include "data.h"
#include "project1.h"

#ifdef FRDM
#define printf( ... ) ( 0 )
#endif

#ifdef DEBUG
#include "testing.h"
#endif