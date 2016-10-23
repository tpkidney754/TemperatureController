#ifdef FRDM
#include "dma.h"

extern uint8_t dmaComplete[ 4 ];
CircularBuffer_t * RXBuffer;
CircularBuffer_t * TXBuffer;

void InitDMA( uint8_t ch )
{
   SET_BIT_IN_REG( SIM_SCGC7, SIM_SCGC7_DMA_MASK );
   dmaComplete[ ch ] = 1;
}

DMAErrors_e StartTransfer32bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   if( numBytes % 4 != 0 )
   {
      return DMANot32bitTransferSize;
   }

   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _32bit ) |
                    DMA_DCR_DSIZE( _32bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   return DMANoError;
}

DMAErrors_e StartTransfer16bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   if( numBytes % 2 != 0 )
   {
      return DMANot16bitTransferSize;
   }

   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;
   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _16bit ) |
                    DMA_DCR_DSIZE( _16bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   return DMANoError;
   return DMANoError;
}

DMAErrors_e StartTransfer8bitMoves( uint8_t ch, uint8_t * src, uint8_t * dst, uint32_t numBytes )
{
   DMA_SAR( ch ) = ( uint32_t ) src;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK |
                    DMA_DCR_SINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   return DMANoError;
}

DMAErrors_e MemSet8bit( uint8_t ch, uint8_t data, uint8_t * dst, uint32_t numBytes )
{
   DMA_SAR( ch ) = ( uint32_t ) &data;
   DMA_DAR( ch ) = ( uint32_t ) dst;

   SET_REG_VALUE( DMA_DCR( ch ),
                  // These values are multiple bits and need to be cleared first
                  ( DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK | DMA_DCR_SINC_MASK ),
                  ( DMA_DCR_EINT_MASK |
                    DMA_DCR_SSIZE( _8bit ) |
                    DMA_DCR_DSIZE( _8bit ) |
                    DMA_DCR_DINC_MASK ) );

   SET_REG_VALUE( DMA_DSR_BCR( ch ), DMA_DSR_BCR_BCR_MASK, numBytes );
   dmaComplete[ ch ] = 0;
   SET_BIT_IN_REG( DMA_DCR( ch ), DMA_DCR_START_MASK );

   return DMANoError;

}

void DMA0_IRQHandler( )
{
   if( DMA_DSR0 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 0 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 0 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA1_IRQHandler( )
{
   if( DMA_DSR1 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 1 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 1 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA2_IRQHandler( )
{
   if( DMA_DSR2 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 2 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 2 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}

void DMA3_IRQHandler( )
{
   if( DMA_DSR3 & DMA_DSR_BCR_DONE_MASK )
   {
      SET_BIT_IN_REG( DMA_DSR_BCR( 3 ), DMA_DSR_BCR_DONE_MASK );
      dmaComplete[ 3 ] = 1;
   }
   else
   {
      LOG0( "DMA0 interrupt occured but DONE bit is not set!\n" );
   }
}
#endif //FRDM
