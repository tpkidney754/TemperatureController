#include "dma.h"

extern uint8_t dmaComplete[ 4 ];
CircularBuffer_t * RXBuffer;
CircularBuffer_t * TXBuffer;

void InitDMA( )
{
   SET_BITS_IN_REG( SIM_SCGC7, SIM_SCGC7_DMA_MASK )
   dmaComplete[ ch ] = 1;
}

void StartTransfer32bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t items )
{
   if( items % 4 != 0 )
   {
      return DMANot32bitTransferSize;
   }

   DMA_SAR( ch ) = src;
   DMA_SAR( ch ) = dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _32bit ) |
                    DMA_DCR_DSIZE( _32bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, items );

   SET_BITS_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK )

   return DMANoError;
}

DMAErrors_e StartTransfer16bitMoves( uint8_t * src, uint8_t * dst, uint32_t items )
{
   if( items % 2 != 0 )
   {
      return DMANot16bitTransferSize;
   }

   DMA_SAR( ch ) = src;
   DMA_SAR( ch ) = dst;
   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _16bit ) |
                    DMA_DCR_DSIZE( _16bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   return DMANoError;
}

void StartTransfer8bitMoves( uint8_t * src, uint8_t * dst, uint32_t items )
{
   DMA_SAR( ch ) = src;
   DMA_SAR( ch ) = dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   return DMANoError;
}

void DMA0_IRQHandler( )
{
   if( DMA_DSR0 & DMA_DSR_DONE_MASK )
   {
      dmaComplete[ 0 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA1_IRQHandler( )
{
   if( DMA_DSR1 & DMA_DSR_DONE_MASK )
   {
      dmaComplete[ 1 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA2_IRQHandler( )
{
   if( DMA_DSR2 & DMA_DSR_DONE_MASK )
   {
      dmaComplete[ 2 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA3_IRQHandler( )
{
   if( DMA_DSR3 & DMA_DSR_DONE_MASK )
   {
      dmaComplete[ 3 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}
