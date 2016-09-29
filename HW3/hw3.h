#include "includeall.h"

typedef union
{
   struct 
   {
      uint32_t ADC14SC        :1;
      uint32_t ADC14END       :1;
      uint32_t RESERVED0      :2;
      uint32_t ADC4ON         :1;
      uint32_t RESERVED1      :2;
      uint32_t ADC14MSC       :1;
      uint32_t ADC14SHT0x     :4;
      uint32_t ADC14SHT1x     :4;
      uint32_t ADC14BUSY      :1;
      uint32_t ADC14CONSEQx   :2;
      uint32_t ADC14SSELx     :3;
      uint32_t ADC14DIVx      :3;
      uint32_t ADC14ISSH      :1;
      uint32_t ADC14SHP       :1;
      uint32_t ADC14SHSx      :3;
      uint32_t ADC14PDIV      :2;
   } b;
   uint32_t w;
} ADC14CTL0Type, *pADC14CTL0Type;

#define ADC14CTL0_BASE              ( 0x3FFF4000 )

#define ADC14CTL0                   ( ( ADC14CTL0Type *)ADC14CTL0_BASE )
#define ADC14CTL0_BASE_PTR          ( ADC14CTL0 )
#define ADC14CTL0_BASE_ADDRESS      { ADC14CTL0_BASE }
#define ADC14CTL0_BASE_ADDRESS_PTR  { ADC14CTL0_BASE }

#define ADC14SC_REG(base)           ((base)->b.ADC14SC      )
#define ADC14END_REG(base)          ((base)->b.ADC14END     )
#define RESERVED0_REG(base)         ((base)->b.RESERVED0    )
#define ADC4ON_REG(base)            ((base)->b.ADC4ON       )
#define RESERVED1_REG(base)         ((base)->b.RESERVED1    )
#define ADC14MSC_REG(base)          ((base)->b.ADC14MSC     )
#define ADC14SHT0x_REG(base)        ((base)->b.ADC14SHT0x   )
#define ADC14SHT1x_REG(base)        ((base)->b.ADC14SHT1x   )
#define ADC14BUSY_REG(base)         ((base)->b.ADC14BUSY    )
#define ADC14CONSEQx_REG(base)      ((base)->b.ADC14CONSEQx )
#define ADC14SSELx_REG(base)        ((base)->b.ADC14SSELx   )
#define ADC14DIVx_REG(base)         ((base)->b.ADC14DIVx    )
#define ADC14ISSH_REG(base)         ((base)->b.ADC14ISSH    )
#define ADC14SHP_REG(base)          ((base)->b.ADC14SHP     )
#define ADC14SHSx_REG(base)         ((base)->b.ADC14SHSx    )
#define ADC14PDIV_REG(base)         ((base)->b.ADC14PDIV    )
