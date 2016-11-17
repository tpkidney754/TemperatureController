#ifndef __SEVENSEGMENT__
#define __SEVENSEGMENT__

#include "includeall.h"

#define NUM_DISPLAYS    3
#define NUM_SEGMENTS    8
#define NUM_DIGITS      10
#define DISPLAY_CLEAR   0
#define DISPLAY_SET     1

//GPIO_Type Display_Port[ NUM_DISPLAYS ][ 2 ];
uint32_t Display_Value[ NUM_DISPLAYS ][ NUM_DIGITS ];

//Display_Port[ 0 ] = GPIOE;

#define DISPLAY_A             PORTE_PCR30
#define DISPLAY_B             PORTE_PCR29
#define DISPLAY_C             PORTE_PCR23
#define DISPLAY_D             PORTE_PCR22
#define DISPLAY_E             PORTE_PCR21
#define DISPLAY_F             PORTE_PCR20
#define DISPLAY_G             PORTE_PCR5
#define DISPLAY_H             PORTE_PCR2

#define DISPLAY_A_PORTE_PIN   0x40000000
#define DISPLAY_B_PORTE_PIN   0x20000000
#define DISPLAY_C_PORTE_PIN   0x00800000
#define DISPLAY_D_PORTE_PIN   0x00400000
#define DISPLAY_E_PORTE_PIN   0x00200000
#define DISPLAY_F_PORTE_PIN   0x00100000
#define DISPLAY_G_PORTE_PIN   0x00000020
#define DISPLAY_H_PORTE_PIN   0x00000002

// 0: A, B, C, D, E, F
// 1: B, C
// 2: A, B, G, E, D
// 3: A, B, G, C, D
// 4: F, B, G, C
// 5: A, F, G, C, D
// 6: F, G, C, D, E
// 7: A, B, C
// 8: A, B, C, D, E, F, G
// 9: A, B, C, F, G


typedef enum
{
   Display_NoError = 0,
   Display_NotSingleDigit,
} Display_Errors;

void InitDisplay( uint8_t Display_num );
void UpdateDisplay( uint8_t Display_num, uint8_t value );
void Display_ClearAll( uint32_t displayNum );

#endif // __SEVENSEGMENT__
