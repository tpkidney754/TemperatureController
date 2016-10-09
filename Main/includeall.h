#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "memory.h"
#include "data.h"
#include "diags.h"
#include "circularbuffer.h"

#ifdef TESTING
#define UART_LOGGING
#include "uartlogging.h"
#endif

#ifdef FRDM
#define printf( ... ) (0)
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "io.h"
#include "uart.h"
#include "led.h"
#include "timers.h"
#endif

#ifdef TESTING
#include "testing.h"
#include "datatesting.h"
#include "memorytesting.h"
#include "circularbuffertesting.h"
#endif
