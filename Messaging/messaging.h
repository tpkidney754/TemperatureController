#ifndef __MESSAGING__
#define __MESSAGING__

#define MAX_LENGTH   128

typedef enum
{
   changeColor = 0,
   changePWM,
   cycleLEDs,
   NOP = 0xFF
} Commands_e;

typedef struct
{
   Commands_e cmd;
   uint8_t numBytes;
   uint8_t data[ MAX_LENGTH ];
   uint8_t checksum;
} Message_t;