#ifndef __NRF24L01__
#define __NRF24L01__

#include "includeall.h"

// SPI Commands to nRF24L01
#define READ_REG( reg )       ( uint8_t ) ( ( reg ) & 0x1F )
#define WRITE_REG( reg )      ( uint8_t ) ( 0x20 | ( reg ) & 0x1F )
#define R_RX_PAYLOAD            0x61
#define W_TX_PAYLOAD            0xA0
#define FLUSH_TX                0xE1
#define FLUSH_RX                0xE2
#define REUSE_TX_PL             0xE3
#define ACTIVATE                0x50
#define R_RX_PL_WID             0x60
#define W_ACK_PAYLOAD( ppp )  ( 0xA8 | ( ( ppp ) & 0x7 ) )
#define W_TX_PAYLOAD_NO_ACK     0xB0
#define NOP                     0xFF

// Registers
typedef enum
{
   CONFIG = 0x0,
   EN_AA,
   EN_RXADDR,
   SETUP_AW,
   SETUP_RETR,
   RF_CH,
   RF_SETUP,
   STATUS,
   OBSERVE_TX,
   CD,
   RX_ADDR_P0,
   RX_ADDR_P1,
   RX_ADDR_P2,
   RX_ADDR_P3,
   RX_ADDR_P4,
   RX_ADDR_P5,
   TX_ADDR,
   RX_PW_P0,
   RX_PW_P1,
   RX_PW_P2,
   RX_PW_P3,
   RX_PW_P4,
   RX_PW_P5,
   FIFO_STATUS,
   DYNPD = 0x1C,
   FEATURE,
} nRF24L01_Registers_e;

typedef union
{
   struct
   {
      uint8_t primRx    :1;
      uint8_t pwrUp     :1;
      uint8_t crco      :1;
      uint8_t enCRC     :1;
      uint8_t maskMaxRt :1;
      uint8_t maskTxDs  :1;
      uint8_t maskRxDr  :1;
      uint8_t reserved  :1;
   } b;
   uint8_t B;
} nRF24L01_CONFIG_t;

typedef union
{
   struct
   {
      uint8_t enaaP0    :1;
      uint8_t enaaP1    :1;
      uint8_t enaaP2    :1;
      uint8_t enaaP3    :1;
      uint8_t enaaP4    :1;
      uint8_t enaaP5    :1;
      uint8_t reserved :2;
   } b;
   uint8_t B;
} nRF24L01_ENAA_t;

typedef union
{
   struct
   {
      uint8_t erxP0    :1;
      uint8_t erxP1    :1;
      uint8_t erxP2    :1;
      uint8_t erxP3    :1;
      uint8_t erxP4    :1;
      uint8_t erxP5    :1;
      uint8_t reserved :2;
   } b;
   uint8_t B;
} nRF24L01_EN_RXADDR_t;

typedef union
{
   struct
   {
      uint8_t aw       :2;
      uint8_t reserved :6;
   } b;
   uint8_t B;
} nRF24L01_SETUP_AW_t;

typedef union
{
   struct
   {
      uint8_t arc      :4;
      uint8_t ard      :4;
   } b;
   uint8_t B;
} nRF24L01_SETUP_RETR_t;

typedef union
{
   struct
   {
      uint8_t rfch     :7;
      uint8_t reserved :1;
   } b;
   uint8_t B;
} nRF24L01_RF_CH_t;

typedef union
{
   struct
   {
      uint8_t lnaHCURR    :1;
      uint8_t rfPWR       :2;
      uint8_t rfDR        :1;
      uint8_t pllLock     :1;
      uint8_t reserved    :3;
   } b;
   uint8_t B;
} nRF24L01_RF_SETUP_t;

typedef union
{
   struct
   {
      uint8_t txFull         :1;
      uint8_t rxPno          :3;
      uint8_t maxRT          :1;
      uint8_t txDS           :1;
      uint8_t rxDR           :1;
      uint8_t reserved       :1;
   } b;
   uint8_t B;
} nRF24L01_STATUS_t;

typedef union
{
   struct
   {
      uint8_t arcCNT  :4;
      uint8_t plosCNT :4;
   } b;
   uint8_t B;
} nRF24L01_OBSERVE_TX_t;

typedef union
{
   struct
   {
      uint8_t rxPwP0    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P0_t;

typedef union
{
   struct
   {
      uint8_t rxPwP1    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P1_t;

typedef union
{
   struct
   {
      uint8_t rxPwP2    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P2_t;

typedef union
{
   struct
   {
      uint8_t rxPwP3    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P3_t;

typedef union
{
   struct
   {
      uint8_t rxPwP4    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P4_t;

typedef union
{
   struct
   {
      uint8_t rxPwP5    :6;
      uint8_t reserved  :2;
   } b;
   uint8_t B;
} nRF24L01_RX_PW_P5_t;

typedef union
{
   struct
   {
      uint8_t rxEmpty   :1;
      uint8_t rxFull    :1;
      uint8_t reserved0 :2;
      uint8_t txEmpty   :1;
      uint8_t txFull    :1;
      uint8_t txReuse   :1;
      uint8_t reserved1 :1;
   }b;
   uint8_t B;
} nRF24L01_FIFO_STATUS_t;

typedef union
{
   struct
   {
      uint8_t dplP0       :1;
      uint8_t dplP1       :1;
      uint8_t dplP2       :1;
      uint8_t dplP3       :1;
      uint8_t dplP4       :1;
      uint8_t dplP5       :1;
      uint8_t reserved    :1;
   }b;
   uint8_t B;
} nRF24L01_DYNPD_t;

typedef union
{
   struct
   {
      uint8_t enDynAck          :1;
      uint8_t enAckPay          :1;
      uint8_t enDpl             :1;
      uint8_t reserved          :5;
   }b;
   uint8_t B;
} nRF24L01_FEATURE_t;

void nRF24L01_Config( uint8_t SPI_ch );
void nRF24L01_ReadReg( uint8_t SPI_ch, uint8_t registerToRead );
void nRF24L01_WriteReg( uint8_t SPI_ch, nRF24L01_Registers_e reg, uint8_t dataToWrite );
void nRF24L01_SendCommand( uint8_t SPI_ch, uint8_t command );
void nRF24L01_TXData( );
void nRF24L01_FlushTXFifo( );

#endif // __NRF24L01__
