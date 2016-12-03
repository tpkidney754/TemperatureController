#ifndef __MESSAGING__
#define __MESSAGING__

#include "includeall.h"

#define MAX_LENGTH         128

#define ENABLE_MESSAGING   1

typedef enum
{
   noError = 0,
   txBufferFull,
   rxBufferFull,
} MessagingErrors_e;

typedef enum
{
   changeColor = 0,
   changePWM,
   setTemp,
   setDisplay,
   setDesired,
   setRange,
   NOPcommand = 0xFF
} Commands_e;

struct Message
{
   uint8_t cmd;
   uint8_t data;
   uint8_t checksum;
} __attribute__((__packed__));

typedef struct Message Message_t;

#define NUM_COMMANDS       6

MessagingErrors_e BuildMessage( Commands_e cmd, uint8_t data );
MessagingErrors_e CalculateChecksum( Message_t * msg );
MessagingErrors_e SendMessage( Message_t * msg );
MessagingErrors_e DecodeRxMessage( Message_t * msg );

#endif // __MESSAGING__
