#ifndef __ADC__
#define __ADC__

#include "includeall.h"

#define ADC_PORT        SIM_SCGC5_PORTD_MASK;

typedef enum
{
   DADP0 = 0,
   DADP1,
   DADP2,
   DADP3,
   AD4,
   AD5,
   AD6,
   AD7,
   AD8,
   AD9,
   AD10,
   AD11,
   AD12,
   AD13,
   AD14,
   AD15,
   AD16,
   AD17,
   AD18,
   AD19,
   AD20,
   AD21,
   AD22,
   AD23,
   RESERVED0,
   RESERVED1,
   TEMP_SENSOR,
   BANDGAP
   RESERVED2,
   VREFSH,
   VREFSL,
   DISABLED,
} ADC_InputChannel;
#endif //__ADC__
