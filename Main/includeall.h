#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "memory.h"
#include "data.h"
#include "project1.h"
#include "diags.h"
//#include "circularbuffer.h"

#ifdef TESTING
#define UART_LOGGING
#include "testing.h"
#endif

#ifdef FRDM
#define printf( ... ) (0)
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "io.h"
#include "uart.h"
#include "led.h"
#include "timers.h"
#include "uartlogging.h"
#endif