#include "spi.h"

CircularBuffer_t * SPI_RXBuffer[ SPI_CHANNELS ];
CircularBuffer_t * SPI_TXBuffer[ SPI_CHANNELS ];

extern uint8_t readRegComplete;
static int spiDeviceLocation[ 2 ];

void InitSPI( uint8_t SPI_ch, uint8_t master )
{
#ifdef FRDM
   // start with SPRF and SPTEF flags and then move to DMA
   if( SPI_ch == 0 )
   {
      // Enable portc clock for I/O and the SPI0 clock.
      SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTC_MASK );
      SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_SPI0_MASK );
      // Set pins to the needed functionality.
      SET_BIT_IN_REG( SPI0_MOSI, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_SCK, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_MISO, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      master ? SET_BIT_IN_REG( SPI0_CS, PORT_PCR_MUX( PIN_GPIO ) ) :
               SET_BIT_IN_REG( SPI0_CS, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI0_CE, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( SPI0_IRQ, PORT_PCR_MUX( PIN_GPIO ) );
      // Setting up RX interrupt and SPI enable
      SET_BIT_IN_REG( SPI0_C1, SPI_C1_SPIE_MASK | SPI_C1_SPE_MASK );

      if( master )
      {
         SET_BIT_IN_REG( SPI0_C1, SPI_C1_MSTR_MASK );
         // When both the MODFEN and SSOE are clear the SS pin is set to be a GPIO.
         SET_BIT_IN_REG( GPIOC_PDDR, SPI0_CS_PIN );
         SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
         // Starting off with 1Mbps to reduce errors. Max for nRF24L01 is 2 Mbps
         SET_BIT_IN_REG( SPI0_BR, SPI_BR_SPPR( SPI_2Mbps_PRESCALER ) | SPI_BR_SPR( SPI_2Mbps_BRD ) );
      }

      // Enable CE as a GPIO
      //SET_BIT_IN_REG( GPIOC_PDDR, SPI0_CE_PIN );

      SPI_RXBuffer[ 0 ] = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI_TXBuffer[ 0 ] = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );

      NVIC_EnableIRQ( SPI0_IRQn );
      NVIC_ClearPendingIRQ( SPI0_IRQn );
      NVIC_SetPriority( SPI0_IRQn, 2 );
   }
   else
   {
      // Enable portc clock for I/O and the SPI0 clock.
      SET_BIT_IN_REG( SIM_SCGC5, SIM_SCGC5_PORTE_MASK );
      SET_BIT_IN_REG( SIM_SCGC4, SIM_SCGC4_SPI1_MASK );
      // Set pins to the needed functionality.
      SET_BIT_IN_REG( SPI1_MOSI, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI1_SCK, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI1_MISO, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      master ? SET_BIT_IN_REG( SPI1_CS, PORT_PCR_MUX( PIN_GPIO ) ) :
               SET_BIT_IN_REG( SPI1_CS, PORT_PCR_MUX( ALTERNATIVE_2 ) );
      SET_BIT_IN_REG( SPI1_CE, PORT_PCR_MUX( PIN_GPIO ) );
      SET_BIT_IN_REG( SPI1_IRQ, PORT_PCR_MUX( PIN_GPIO ) );
      // Setting up RX interrupt and SPI enable
      SET_BIT_IN_REG( SPI1_C1, SPI_C1_SPIE_MASK | SPI_C1_SPE_MASK );

      if( master )
      {
         SET_BIT_IN_REG( SPI0_C1, SPI_C1_MSTR_MASK );
         // When both the MODFEN and SSOE are clear the SS pin is set to be a GPIO.
         SET_BIT_IN_REG( GPIOE_PDDR, SPI1_CS_PIN );
         SET_BIT_IN_REG( GPIOE_PSOR, SPI1_CS_PIN );
         // Starting off with 1Mbps to reduce errors. Max for nRF24L01 is 2 Mbps
         SET_BIT_IN_REG( SPI1_BR, SPI_BR_SPPR( SPI_2Mbps_PRESCALER ) | SPI_BR_SPR( SPI_2Mbps_BRD ) );
      }

      // CE is a nRF functionality, not SPI, this should move.
      // Enable CE as a GPIO
      //SET_BIT_IN_REG( GPIOE_PDDR, SPI0_CE_PIN );

      SPI_RXBuffer[ 1 ] = CBufferInit( sizeof( uint8_t ), SPI0_RXBUFFER_SIZE );
      SPI_TXBuffer[ 1 ] = CBufferInit( sizeof( uint8_t ), SPI0_TXBUFFER_SIZE );

      NVIC_EnableIRQ( SPI1_IRQn );
      NVIC_ClearPendingIRQ( SPI1_IRQn );
      NVIC_SetPriority( SPI1_IRQn, 2 );
   }
#endif // FRDM

#if BBB
   int ret;
   uint8_t mode = MODE;
   uint8_t bits = BPW;
   uint32_t speed = BBB_SPI_SPEED;

   spiDeviceLocation[ SPI_ch ] = open( DEVICE_LOC, O_RDWR );
   if( spiDeviceLocation[ SPI_ch ] < 0 )
   {
      LOG0( "Unable to open SPIDEV1.0\n" );
   }

   ret = ioctl( spiDeviceLocation[ SPI_ch ], SPI_IOC_WR_MODE, &mode );
   if( ret == -1 )
   {
      LOG0( "Unable to set SPI0 Mode\n" );
   }

   ret = ioctl( spiDeviceLocation[ SPI_ch ], SPI_IOC_WR_BITS_PER_WORD, &bits );
   if( ret == -1 )
   {
      LOG0( "Unable to set bits per word\n" );
   }

   ret = ioctl( spiDeviceLocation[ SPI_ch ], SPI_IOC_WR_MAX_SPEED_HZ, &speed );
   if( ret == -1 )
   {
      LOG0( "Unable to set max speed\n" );
   }
#endif // BBB
}

void SPI_TransmitData( uint8_t SPI_ch, size_t numBytes )
{
#ifdef FRDM
   SPI_Type * SPI_reg;
   uint8_t data;
   SPI_reg = SPI_ch == 0 ? SPI0 : SPI1;

   for( size_t i = 0; i < numBytes; i++ )
   {
      CBufferRemove( SPI_TXBuffer[ SPI_ch ], &data );
      WAIT_FOR_BIT_SET( SPI_S_REG( SPI_reg ) & SPI_S_SPTEF_MASK );
      SPI_D_REG( SPI_reg ) = data;
   }
#endif // FRDM

#ifdef BBB
   uint8_t * tx = malloc( sizeof( uint8_t ) * numBytes );
   uint8_t * rx;
   int ret;

   for( size_t i = 0; i < numBytes; i++ )
   {
      CBufferRemove( SPI_TXBuffer[ SPI_ch ], tx++ );
   }

   struct spi_ioc_transfer tr =
   {
    .tx_buf = (unsigned long)tx,
    .rx_buf = (unsigned long)rx,
    .len = numBytes,
    .delay_usecs = 0,
    .speed_hz = BBB_SPI_SPEED,
    .bits_per_word = BPW,
  };

   ret = ioctl( spiDeviceLocation[ SPI_ch ], SPI_IOC_MESSAGE( 1 ), &tr );
   if( ret < 1 )
   {
      LOG0( "Unable to send SPI message\n" );
   }
#endif // BBB
}

#ifdef BBB
void SPI_Test( uint8_t SPI_ch )
{
   LOG0( "Testing SPI0\n" );
   int ret;
   uint8_t tx[] =
   {
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
      0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
      0xF0, 0x0D,
   };
   uint8_t rx[ARRAY_SIZE(tx)] = {0, };
   struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)tx,
    .rx_buf = (unsigned long)rx,
    .len = ARRAY_SIZE(tx),
    .delay_usecs = 0,
    .speed_hz = BBB_SPI_SPEED,
    .bits_per_word = BPW,
   };

   ret = ioctl( spiDeviceLocation[ SPI_ch ], SPI_IOC_MESSAGE(1), &tr );
   if (ret < 1)
      LOG0( "can't send spi message\n" );

   for (ret = 0; ret < ARRAY_SIZE(tx); ret++)
   {
      if (!(ret % 6))
         puts("");
      printf("%.2X ", rx[ret]);
   }

   puts("");
}
#endif // BBB

#ifdef FRDM
void SPI0_IRQHandler( )
{
   NVIC_DisableIRQ( SPI0_IRQn );
   if( SPI0_S & SPI_S_SPRF_MASK )
   {
      // Data available in the RX data buffer
      uint8_t data = SPI0_D;
      CBufferAdd( SPI_RXBuffer[ 0 ], &data);
   }

   if( ( SPI0_S & SPI_S_SPTEF_MASK ) && ( SPI0_C1 & SPI_C1_SPTIE_MASK ) )
   {
      uint8_t data;
      if( CBufferRemove( SPI_TXBuffer[ 0 ], &data ) == BUFFER_EMPTY )
      {
         CLEAR_BITS_IN_REG( SPI0_C1, SPI_C1_SPTIE_MASK );
         SET_BIT_IN_REG( GPIOC_PSOR, SPI0_CS_PIN );
      }
      else
      {
         SPI0_D = data;
      }
   }

   NVIC_EnableIRQ( SPI0_IRQn );
}

void SPI1_IRQHandler( )
{
   NVIC_DisableIRQ( SPI1_IRQn );
   if( SPI1_S & SPI_S_SPRF_MASK )
   {
      // Data available in the RX data buffer
      uint8_t data = SPI1_D;
      CBufferAdd( SPI_RXBuffer[ 1 ], &data);
   }

   if( ( SPI1_S & SPI_S_SPTEF_MASK ) && ( SPI1_C1 & SPI_C1_SPTIE_MASK ) )
   {
      uint8_t data;
      if( CBufferRemove( SPI_TXBuffer[ 1 ], &data ) == BUFFER_EMPTY )
      {
         CLEAR_BITS_IN_REG( SPI0_C1, SPI_C1_SPTIE_MASK );
         SET_BIT_IN_REG( GPIOE_PSOR, SPI1_CS_PIN );
      }
      else
      {
         SPI1_D = data;
      }
   }

   NVIC_EnableIRQ( SPI1_IRQn );
}
#endif // FRDM
