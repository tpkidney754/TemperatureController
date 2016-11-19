#include "sevensegment.h"

void InitDisplay( uint8_t displayNum )
{
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

   switch( displayNum )
   {
      case 0: SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTE_MASK );
              SET_BIT_IN_REG( DISPLAY_PORTE_A, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_B, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_C, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_D, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_E, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_F, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_G, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTE_H, PORT_PCR_MUX( PIN_GPIO ) );
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
              Display_Port[ 0 ] = GPIOE;
              SET_BIT_IN_REG( GPIO_PDDR_REG( Display_Port[ 0 ] ), Display_Value[ 0 ][ 8 ] );
              break;
      case 1: SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTB_MASK );
              SET_BIT_IN_REG( DISPLAY_PORTB_A, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_B, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_C, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_D, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_E, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_F, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_G, PORT_PCR_MUX( PIN_GPIO ) );
              SET_BIT_IN_REG( DISPLAY_PORTB_H, PORT_PCR_MUX( PIN_GPIO ) );
              Display_Value[ 1 ][ 0 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN );

              Display_Value[ 1 ][ 1 ] = ( DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN );

              Display_Value[ 1 ][ 2 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 3 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 4 ] = ( DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 5 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 6 ] = ( DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 7 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN );

              Display_Value[ 1 ][ 8 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_D_PORTB_PIN |
                                          DISPLAY_E_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );

              Display_Value[ 1 ][ 9 ] = ( DISPLAY_A_PORTB_PIN |
                                          DISPLAY_B_PORTB_PIN |
                                          DISPLAY_C_PORTB_PIN |
                                          DISPLAY_F_PORTB_PIN |
                                          DISPLAY_G_PORTB_PIN );
              Display_Port[ 1 ] = GPIOB;
              SET_BIT_IN_REG( GPIO_PDDR_REG( Display_Port[ 1 ] ), Display_Value[ 1 ][ 8 ] );
              break;
   }
}

void UpdateDisplay( uint8_t displayNum, uint8_t value )
{
   Display_ClearAll( displayNum );
   SET_BIT_IN_REG( GPIO_PSOR_REG( Display_Port[ displayNum ] ), Display_Value[ displayNum ][ value ] );
}

void Display_ClearAll( uint32_t displayNum )
{
   SET_BIT_IN_REG( GPIO_PCOR_REG( Display_Port[ displayNum ] ), Display_Value[ displayNum ][ 8 ] );
}
