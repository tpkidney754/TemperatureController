#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#ifndef FRDM
#include <time.h>
#include <math.h>
#endif

#include "circularbuffer.h"
#define UART_LOGGING
#include "uartlogging.h"
#ifdef FRDM
#define printf( ... ) (0)
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "io.h"
#include "uart.h"
#include "led.h"
#endif

#if ( defined( FRDM ) || defined( TESTING ) )
#include "timers.h"
#endif

#include "memory.h"
#include "data.h"
#include "diags.h"
#ifdef TESTING
#include "testing.h"
#include "datatesting.h"
#include "memorytesting.h"
#include "circularbuffertesting.h"
#include "performancetesting.h"
#endif

