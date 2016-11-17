#include "sevensegment.h"

void InitDisplay( uint8_t displayNum )
{
   switch( displayNum )
   {
      case 0: SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTE_MASK );
              SET_BIT_IN_REG( DISPLAY_A, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_B, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_C, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_D, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_E, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_F, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_G, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_H, PORT_PCR_MUX( PIN_GPIO ) );
              Display_Value[ 0 ][ 0 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN );

              Display_Value[ 0 ][ 1 ] = ( DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN );

              Display_Value[ 0 ][ 2 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 3 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 4 ] = ( DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 5 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 6 ] = ( DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 7 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN );

              Display_Value[ 0 ][ 8 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_D_PORTE_PIN |
                                          DISPLAY_E_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );

              Display_Value[ 0 ][ 9 ] = ( DISPLAY_A_PORTE_PIN |
                                          DISPLAY_B_PORTE_PIN |
                                          DISPLAY_C_PORTE_PIN |
                                          DISPLAY_F_PORTE_PIN |
                                          DISPLAY_G_PORTE_PIN );
              SET_BIT_IN_REG( GPIO_PDDR_REG( GPIOE ), Display_Value[ 0 ][ 8 ] );
              break;
   }
}

void UpdateDisplay( uint8_t displayNum, uint8_t value )
{
   Display_ClearAll( displayNum );
   SET_BIT_IN_REG( GPIO_PSOR_REG( GPIOE ), Display_Value[ displayNum ][ value ] );
}

void Display_ClearAll( uint32_t displayNum )
{
   SET_BIT_IN_REG( GPIO_PCOR_REG( GPIOE ), Display_Value[ displayNum ][ 8 ] );
}
