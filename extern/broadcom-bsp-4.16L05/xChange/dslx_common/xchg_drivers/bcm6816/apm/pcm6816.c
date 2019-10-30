/***************************************************************************
*    Copyright � 2008 Broadcom Corporation
*
*    This program is the proprietary software of Broadcom Corporation and/or
*    its licensors, and may only be used, duplicated, modified or
*    distributed pursuant to the terms and conditions of a separate, written
*    license agreement executed between you and Broadcom (an "Authorized
*    License").  Except as set forth in an Authorized License, Broadcom
*    grants no license (express or implied), right to use, or waiver of any
*    kind with respect to the Software, and Broadcom expressly reserves all
*    rights in and to the Software and all intellectual property rights
*    therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO
*    USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM
*    AND DISCONTINUE ALL USE OF THE SOFTWARE.
*
*
*    Except as expressly set forth in the Authorized License,
*
*    1.     This program, including its structure, sequence and
*    organization, constitutes the valuable trade secrets of Broadcom, and
*    you shall use all reasonable efforts to protect the confidentiality
*    thereof, and to use this information only in connection with your use
*    of Broadcom integrated circuit products.
*
*    2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED
*    "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
*    REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR
*    OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
*    DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
*    NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
*    ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
*    CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT
*    OF USE OR PERFORMANCE OF THE SOFTWARE.
*
*    3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
*    BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL,
*    SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN
*    ANY WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN
*    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; OR
*    (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE
*    ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY
*    NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
*
****************************************************************************
*
*    Filename: pcm6816.c
*
****************************************************************************
*
*    Description:  PCM device driver for BCM6816
*
****************************************************************************/

/* ---- Include Files ---------------------------------------- */
/*
** Always include this file before any other include files
** to avoid conflicts with remapped printf command
*/
#include <kernelMainWrapper.h>
#include <linux/dma-mapping.h>

#include <xdrvTypes.h>
#include <xdrvLog.h>
#include <pcm.h>
#include <dma.h>
#include "pcm6816.h"
#include "apm6816.h"
#include "dma6816.h"
#include <bcm6816.h>
#include <xdrvCache.h>

/* DMA descriptor or DMA data handle */
typedef dma_addr_t      DMA_HANDLE;

#define P_NCO_FCW_MISC 0xa7c5ac47  // 0xa7c5ac47 for DPLL, 0x53e2d624 for MISC
#define P_NCO_SCALE  0x40000000    // 0x40000000 for DPLL/MISC
#define P_PCM_NCO_SHIFT  0x0       // 0x0 for DPLL, 0x1 for MISC
#define P_PCM_NCO_MUX_CNTL_DPLL 0x2    /* 0x2 for DPLL */
#define P_PCM_NCO_MUX_CNTL_MISC 0x1    /* 0x1 for MISC */

/* ---- Public Variables ------------------------------------ */
extern int gPllClockFailed;
extern int Print(char *f, ...);

/* DMA buffers for APM Rx/Tx data */
static PCM6816_DMA_BUFFER dmaRxData[PCM6816_NUM_CHANNELS*DMA_RX_NUM_BUFFERS];
static PCM6816_DMA_BUFFER dmaTxData[PCM6816_NUM_CHANNELS*DMA_TX_NUM_BUFFERS];

/* DMA Channel info (simplex - one way) for easy access to DMA channels */
typedef struct PCM6816_DMA_SIMPLEX_CHANNEL_INFO
{
   int                  iuChanNum;     /* IUDMA channel number assosiated with this APM channel */
   BCM6816_IUDMA_DESC   *dmaDescp;     /* Where are the descriptors for this channel? */
   DMA_HANDLE           dmaDescHandle;
   PCM6816_DMA_BUFFER   *dmaDatap;     /* Where are the DMA buffers to store/fetch the data to/from for each channel */
   DMA_HANDLE           dmaBufHandle;
} PCM6816_DMA_SIMPLEX_CHANNEL_INFO;

/* DMA Channel info (duplex - both ways) for easy access to DMA channels */
typedef struct PCM6816_DMA_DUPLEX_CHANNEL_INFO
{
   PCM6816_DMA_SIMPLEX_CHANNEL_INFO rxChan;  /* RX channel */
   PCM6816_DMA_SIMPLEX_CHANNEL_INFO txChan;  /* TX channel */
} PCM6816_DMA_DUPLEX_CHANNEL_INFO;

/* Initialized DMA channel info */
static PCM6816_DMA_DUPLEX_CHANNEL_INFO gPcmDmaInfo[PCM6816_NUM_CHANNELS] =
{
   {
      /* RX Channel 0 */
      {
         BCM6816_APM_IUDMA_PCM_RX,
         NULL,    /* Will be filled with dynamically allocated value for dmaRxDesc_c */
         (DMA_HANDLE)&dmaRxData[0],
       },

      /* TX Channel 0 */
      {
         BCM6816_APM_IUDMA_PCM_TX,
         NULL,    /* Will be filled with dynamically allocated value for dmaTxDesc_c */
         (DMA_HANDLE)&dmaTxData[0],
      }
   }
};

static int pcm6816_clkInit( void );
static int pcm6816_regInit( PCM_CHANNEL_TIMESLOT_MAP* chanTsMap );
static int pcm6816_regDeinit ( void );
static void PcmTsAllocate( int chnum, int ts);
static int pcm6816_iudmaInit( void );
static int pcm6816_iudmaDeinit( void );
static int pcm6816_dmaDescrInit( void );
static int  pcm6816_dmaDescrDeinit(void);
static int pcm6816_enable( int chan_mask );
static int pcm6816_disable( void );

void printRegs( void )
{
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM: Interrupt Masks"));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "---------------"));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "IrqMask                    = 0x%016llX ", (unsigned long long)(PERF->IrqControl[0].IrqMask)));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "IrqMask1                   = 0x%016llX ", (unsigned long long)(PERF->IrqControl[1].IrqMask)));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[4].intMask = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[4].intMask));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[5].intMask = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[5].intMask));

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM: Interrupt Status"));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "-----------------"));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "IrqStatus                  = 0x%016llX ", (unsigned long long)(PERF->IrqControl[0].IrqStatus)));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "IrqStatus1                 = 0x%016llX ", (unsigned long long)(PERF->IrqControl[1].IrqStatus)));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[4].intStat = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[4].intStat));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[5].intStat = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[5].intStat));

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->reg_pcm_clk_cntl_0         = 0x%08X ", (unsigned int)PCM->reg_pcm_clk_cntl_0));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->reg_pcm_clk_cntl_1         = 0x%08X ", (unsigned int)PCM->reg_pcm_clk_cntl_1));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->reg_pcm_clk_cntl_2         = 0x%08X ", (unsigned int)PCM->reg_pcm_clk_cntl_2));

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->pcm_int_pending       = 0x%08X ", (unsigned int)PCM->pcm_int_pending));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->pcm_int_mask          = 0x%08X ", (unsigned int)PCM->pcm_int_mask   ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->pcm_ctrl              = 0x%08X ", (unsigned int)PCM->pcm_ctrl       ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "PCM->pcm_chan_ctrl         = 0x%08X ", (unsigned int)PCM->pcm_chan_ctrl  ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->regs.ctrlConfig = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->regs.ctrlConfig));

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[4].maxBurst                  = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[4].maxBurst                 ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[4].config                    = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[4].config                   ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[4].baseDescPointer          = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[4].baseDescPointer         ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[4].stateBytesDoneRingOffset = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[4].stateBytesDoneRingOffset));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[4].flagsLengthStatus        = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[4].flagsLengthStatus       ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[4].currentBufferPointer     = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[4].currentBufferPointer    ));

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[5].maxBurst                  = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[5].maxBurst                 ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->ctrl[5].config                    = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->ctrl[5].config                   ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[5].baseDescPointer          = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[5].baseDescPointer         ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[5].stateBytesDoneRingOffset = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[5].stateBytesDoneRingOffset));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[5].flagsLengthStatus        = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[5].flagsLengthStatus       ));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "BCM6816_APM_IUDMA_PTR->stram[5].currentBufferPointer     = 0x%08X ", (unsigned int)BCM6816_APM_IUDMA_PTR->stram[5].currentBufferPointer    ));
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_init
*
*  PURPOSE:
*      Intialize 6816 PCM Module
*
*  PARAMETERS: channelMask - Mask to enable specific TX/RX pcm timeslots
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
int pcm6816_init( PCM_CHANNEL_TIMESLOT_MAP* chanTsMap, XDRV_UINT32 channelMask, XDRV_UINT8 supportMode  )
{
   (void)supportMode;

   XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "------------------ PCM CONFIGURATION START ------------------ "));

   /* Enable clocks for PCM block.  Note: NTP_CLK MUST be enabled as well. */
   PERF->blkEnables |= APM_CLK_EN | ACP_A_CLK_EN | ACP_B_CLK_EN;
   PERF->blkEnables |= PCM_CLK_EN | NTP_CLK_EN;


   /* Setup GPIO 25:22 for PCM functionality on 6816 */
   GPIO->GPIOMode |= GPIO_MODE_APM_CLK | GPIO_MODE_APM_SDIN | GPIO_MODE_APM_SDOUT | GPIO_MODE_APM_FRAME_SYNC;

   /* Initialize PCM clock */
   pcm6816_clkInit();

   /* Initialize PCM registers */
   pcm6816_regInit( chanTsMap );

   pcm6816_enable( channelMask );

   pcm6816_dmaDescrInit();

   pcm6816_iudmaInit();


   printRegs();

   XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "------------------ PCM CONFIGURATION END ------------------ "));

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_deinit
*
*  PURPOSE:
*      Deintialize 6816 PCM Module
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
int pcm6816_deinit( void )
{
   pcm6816_disable();

   pcm6816_iudmaDeinit();

   pcm6816_dmaDescrDeinit();

   pcm6816_regDeinit();

   printRegs();

   PERF->blkEnables &= ~PCM_CLK_EN;

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_clkInit
*
*  PURPOSE:
*      Set up APM registers to generate PCM clock.
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
static int pcm6816_clkInit( void )
{
   volatile BCM6816_APM *pApm = BCM6816_APM_PTR;
   int muxControl = 0;

   XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "Set up PCM registers to generate PCM clock"));

   pApm->dpll_control &= ~(DPLL_SOFT_INIT | DPLL_FORCE_ACQ | DPLL_OPEN_LOOP | DPLL_CONST_K);
   pApm->dpll_control &= ~0xF;
   pApm->dpll_control |= ( (5 << DPLL_PHS_THSHLD_SHIFT) | 12 );
   pApm->dpll_nom_freq = 0xa7c5ac47;
   pApm->dpll_div = (31 << DPLL_REF_DIV_SHIFT) | 8191;

   pApm->dpll_control |= DPLL_FORCE_ACQ;
   pApm->dpll_control &= ~DPLL_FORCE_ACQ;


   /* Setup Diagbus to route internal PCM signals to APM core IO */
   GPIO->DiagSelControl = 0x00001010;
   PERF->diagControl = 0x00005280;

   PCM->reg_pcm_clk_cntl_0 = P_NCO_FCW_MISC;
   PCM->reg_pcm_clk_cntl_1 = P_NCO_SCALE;

   if ( gPllClockFailed ) 
   {
     muxControl = P_PCM_NCO_MUX_CNTL_MISC;
   }
   else
   {
     muxControl = P_PCM_NCO_MUX_CNTL_DPLL;
   }

   PCM->reg_pcm_clk_cntl_2 = ((P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
                              | ((muxControl << 4) & PCM_NCO_MUX_CNTL)
                              |  (PCM_NCO_SOFT_INIT));
   PCM->reg_pcm_clk_cntl_2 = ((P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
                              | ((muxControl << 4) & PCM_NCO_MUX_CNTL));
   PCM->reg_pcm_clk_cntl_2 = ((P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
                              | ((muxControl << 4) & PCM_NCO_MUX_CNTL)
                              |  (PCM_NCO_LOAD_MISC));
   PCM->reg_pcm_clk_cntl_2 = ((P_PCM_NCO_SHIFT & PCM_NCO_SHIFT)
                              | ((muxControl << 4) & PCM_NCO_MUX_CNTL));

  return(0);
}



/*****************************************************************************
*
*  FUNCTION: pcm6816_regInit
*
*  PURPOSE:
*      Intialize 6816 PCM Module Registers
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
static int pcm6816_regInit( PCM_CHANNEL_TIMESLOT_MAP* chanTsMap )
{
   volatile BCM6816_APM *pApm = BCM6816_APM_PTR;

   XDRV_UINT32 i;

   XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "Set up PCM registers"));

  // PCM Control
   PCM->pcm_ctrl = ((PCM_AP_SEL)  |
                           (0 << PCM_SLAVE_SEL_SHIFT) |
                           (1 << PCM_CLOCK_INV_SHIFT) |
                           (0 << PCM_FS_INVERT_SHIFT)  |
                           (0 << PCM_FS_FREQ_16_8_SHIFT)  |
                           (0 << PCM_FS_LONG_SHIFT)  |
                           (1 << PCM_FS_TRIG_SHIFT)  |
                           (1 << PCM_DATA_OFF_SHIFT)  |
#ifndef PCM_ALAW
#  ifndef PCM_ULAW
                           (1 << PCM_DATA_16_8_SHIFT)  |
#  endif
#endif
                           (0 << PCM_LSB_FIRST_SHIFT)  |
                           (0 << PCM_LOOPBACK_SHIFT)  |
                           (0 << PCM_EXTCLK_SEL_SHIFT)  |
                           (PCM_BITS_PER_FRAME_256) |
                           ((2 << PCM_CLOCK_SEL_SHIFT) & PCM_CLOCK_SEL));
   XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "reg_pcm_control = 0x%lx", PCM->pcm_ctrl));

   PCM->pcm_chan_ctrl = 0;


   // clear time slot allocation table
   for (i=0; i < PCM_MAX_TIMESLOT_REGS; i++)
   {
      PCM->pcm_slot_alloc_tbl[i] = 0;
   }

   for ( i = 0; i < PCM_MAX_CHANNELS; i++ )
   {
      if ( chanTsMap[i].chan == PCM_CHAN_INVALID )
      {
         break;
      }
      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM,  "PCM: Channel/Line %lu Timeslot %d ", i, (int)chanTsMap[i].txTimeslot ));
      PcmTsAllocate( i, chanTsMap[i].txTimeslot );
   }

   /* Clear PCM interrupts at the APM device */
   pApm->apm_dev_irq_pend |= DMA_PCM_RX | DMA_PCM_TX;

   /* Enable PCM interrupts  - This setting actual MASKS the interrupt.*/
   pApm->apm_dev_irq_mask |= DMA_PCM_RX | DMA_PCM_TX;

   /* Clear overflow/underflow PCM interrupts at the PCM level */
   PCM->pcm_int_pending |=  PCM_TX_UNDERFLOW | PCM_RX_OVERFLOW;

   /* Enable PCM over/underflow conditions */
   PCM->pcm_int_mask |=  PCM_TX_UNDERFLOW | PCM_RX_OVERFLOW;

  return( 0 );
}

static int pcm6816_regDeinit( void )
{
   XDRV_UINT32 i;

   // clear time slot allocation table
   for (i=0; i < PCM_MAX_TIMESLOT_REGS; i++)
   {
      PCM->pcm_slot_alloc_tbl[i] = 0;
   }

   return( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_enable
*
*  PURPOSE:
*      Enable 6816 PCM Module
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
int pcm6816_enable( int chan_mask )
{
   // Enable PCM operation
   PCM->pcm_ctrl |= PCM_ENABLE ;

   // Enable receive/transmit channels
   PCM->pcm_chan_ctrl |= chan_mask & PCM_TX_CHANNELS;
   PCM->pcm_chan_ctrl |= chan_mask & PCM_RX_CHANNELS;

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_disable
*
*  PURPOSE:
*      Disable 6816 PCM Module
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
int pcm6816_disable( void )
{
   // Disable receive/transmit channels
   PCM->pcm_chan_ctrl = 0;

   // Disable PCM operation
   PCM->pcm_ctrl &= ~PCM_ENABLE ;

   PCM->pcm_ctrl = 0;

   PCM->pcm_int_pending |=  PCM->pcm_int_pending;

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_iudmaInit
*
*  PURPOSE:
*      Intialize 6816 IUDMA registers.
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES: IUDMA is shared with APM. PCM is channels 5 and 6.
*
*****************************************************************************/
static int pcm6816_iudmaInit( void )
{
   int chnum;
   volatile BCM6816_IUDMA *iuDmap = BCM6816_APM_IUDMA_PTR;

   /* Initialize the Rx/Tx IUDMA pair for PCM channel */
   for (chnum=0; chnum < PCM6816_NUM_CHANNELS; chnum++)
   {
      XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "initIudma: chan %d, descBase 0x%x, descBaseIudma 0x%x",
                        gPcmDmaInfo[chnum].rxChan.iuChanNum,
                        (unsigned int)gPcmDmaInfo[chnum].rxChan.dmaDescp,
                        CacheVirtToPhyAddress(gPcmDmaInfo[chnum].rxChan.dmaDescp)
                        ));

       /* Init RX side */
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].maxBurst = 4; /* in 32-bit words */
      iuDmap->stram[gPcmDmaInfo[chnum].rxChan.iuChanNum].baseDescPointer = CacheVirtToPhyAddress(gPcmDmaInfo[chnum].rxChan.dmaDescp);
      iuDmap->stram[gPcmDmaInfo[chnum].rxChan.iuChanNum].stateBytesDoneRingOffset = 0;
      iuDmap->stram[gPcmDmaInfo[chnum].rxChan.iuChanNum].flagsLengthStatus = 0;
      iuDmap->stram[gPcmDmaInfo[chnum].rxChan.iuChanNum].currentBufferPointer = 0;
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intStat |= iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intStat;
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intMask = BCM6816_IUDMA_INTMASK_BDONE | BCM6816_IUDMA_INTMASK_NOTVLD;
      iuDmap->regs.intMask |= ( 1 << gPcmDmaInfo[chnum].rxChan.iuChanNum );  /* Global Int Mask */

      XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "initIudma: chan %d, descBase 0x%x, descBaseIudma 0x%x",
                        gPcmDmaInfo[chnum].txChan.iuChanNum,
                        (unsigned int)gPcmDmaInfo[chnum].txChan.dmaDescp,
                        CacheVirtToPhyAddress(gPcmDmaInfo[chnum].txChan.dmaDescp)
                        ));
      /* Init TX side */
      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].maxBurst = 4; /* in 32-bit words */
      iuDmap->stram[gPcmDmaInfo[chnum].txChan.iuChanNum].baseDescPointer = CacheVirtToPhyAddress(gPcmDmaInfo[chnum].txChan.dmaDescp);
      iuDmap->stram[gPcmDmaInfo[chnum].txChan.iuChanNum].stateBytesDoneRingOffset = 0;
      iuDmap->stram[gPcmDmaInfo[chnum].txChan.iuChanNum].flagsLengthStatus = 0;
      iuDmap->stram[gPcmDmaInfo[chnum].txChan.iuChanNum].currentBufferPointer = 0;
      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intStat |= iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intStat;
      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intMask = BCM6816_IUDMA_INTMASK_BDONE | BCM6816_IUDMA_INTMASK_NOTVLD;
      iuDmap->regs.intMask |= ( 1 << gPcmDmaInfo[chnum].txChan.iuChanNum );  /* Global Int Mask */
   }

   /* Enable the IUDMA master */
   iuDmap->regs.ctrlConfig = BCM6816_IUDMA_REGS_CTRLCONFIG_MASTER_EN;

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_iudmaDeinit
*
*  PURPOSE:
*      De-intialize 6816 IUDMA registers.
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES: IUDMA is shared with APM. PCM is channels 5 and 6.
*
*****************************************************************************/
static int pcm6816_iudmaDeinit( void)
{
   int chnum;
   volatile BCM6816_IUDMA *iuDmap = BCM6816_APM_IUDMA_PTR;
   int i=0;

   /* Halt individual channels first */
   for (chnum=0; chnum < PCM6816_NUM_CHANNELS; chnum++)
   {

      /* Deinit RX side */
      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "RX DMA STATUS (1=busy 0=IDLE) : 0x%08x", (unsigned int)iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].config));
      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "HALTING RX DMA...."));

      /* Set the burstHalt bit while clearing endma bit */
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].config = ( BCM6816_IUDMA_CONFIG_BURSTHALT );

      while( (iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].config & BCM6816_IUDMA_CONFIG_ENDMA) != 0x00000000 )
      {
         /* Set the burstHalt bit while clearing endma bit */
         iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].config = ( BCM6816_IUDMA_CONFIG_BURSTHALT );
         XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "RX DMA HALT Waiting, iteration:%d",i));
         i++;
      }

      i=0;

      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "RX DMA IDLE"));
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intMask = 0;
      iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intStat |= iuDmap->ctrl[gPcmDmaInfo[chnum].rxChan.iuChanNum].intStat;

      /* Deinit TX side */

      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "TX DMA STATUS (1=busy 0=IDLE) : 0x%08x", (unsigned int)iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].config));
      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "HALTING TX DMA...."));

      /* Set the burstHalt bit while clearing endma bit */
      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].config = ( BCM6816_IUDMA_CONFIG_BURSTHALT );

      while( (iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].config & BCM6816_IUDMA_CONFIG_ENDMA) != 0x00000000 )
      {
         /* Set the burstHalt bit while clearing endma bit */
         iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].config = ( BCM6816_IUDMA_CONFIG_BURSTHALT );
         XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "TX DMA HALT Waiting, iteration:%d",i));
         i++;
      }
      XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "TX DMA IDLE"));

      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intMask = 0;
      iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intStat |= iuDmap->ctrl[gPcmDmaInfo[chnum].txChan.iuChanNum].intStat;
   }

   /* Disable pcm iudma controller */
   iuDmap->regs.ctrlConfig &= ~BCM6816_IUDMA_REGS_CTRLCONFIG_MASTER_EN;


   return( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_dmaDescrInit
*
*  PURPOSE:
*      Intialize 6816 DMA descriptors.
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
static int pcm6816_dmaDescrInit( void )
{
   XDRV_UINT8                       i,chnum;
   volatile BCM6816_IUDMA_DESC*     dmaTxDesc;
   volatile BCM6816_IUDMA_DESC*     dmaRxDesc;
   volatile BCM6816_IUDMA_DESC*     dmaTxDesc_c;
   volatile BCM6816_IUDMA_DESC*     dmaRxDesc_c;
   volatile PCM6816_DMA_BUFFER*     dmaRxData;
   volatile PCM6816_DMA_BUFFER*     dmaTxData;
   PCM6816_DMA_SIMPLEX_CHANNEL_INFO *dmaChanInfop;
   unsigned                         bufferSizeBytes = 0;
   XDRV_UINT32                      rxDescriptorArea;
   XDRV_UINT32                      txDescriptorArea;
   XDRV_UINT32                      rxBufferArea;
   XDRV_UINT32                      txBufferArea;
   volatile XDRV_UINT32             *dmaDatap;

   rxDescriptorArea = sizeof(BCM6816_IUDMA_DESC) * PCM6816_NUM_CHANNELS * DMA_RX_NUM_BUFFERS + sizeof(XDRV_UINT8) * BCM6816_DMA_UBUS_BYTES;
   txDescriptorArea = sizeof(BCM6816_IUDMA_DESC) * PCM6816_NUM_CHANNELS * DMA_TX_NUM_BUFFERS + sizeof(XDRV_UINT8) * BCM6816_DMA_UBUS_BYTES;

   /* Allocate receive and transmit descriptors */
   dmaRxDesc_c = dma_alloc_coherent( NULL, rxDescriptorArea, &gPcmDmaInfo[0].rxChan.dmaDescHandle, GFP_KERNEL );
   dmaTxDesc_c = dma_alloc_coherent( NULL, txDescriptorArea, &gPcmDmaInfo[0].txChan.dmaDescHandle, GFP_KERNEL );
   if ( (dmaRxDesc_c == NULL) || (dmaTxDesc_c == NULL) )
   {
      XDRV_LOG_ERROR((XDRV_LOG_MOD_PCM, "Could not allocate memory for DMA descriptors !!! "));
      return( -1 );
   }

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "rxDescriptorArea       = %d ", (int)rxDescriptorArea));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "txDescriptorArea       = %d ", (int)txDescriptorArea));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "Unaligned dmaRxDesc_c  = 0x%08X ", (unsigned int)dmaRxDesc_c));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "Unaligned dmaTxDesc_c  = 0x%08X ", (unsigned int)dmaTxDesc_c));

   /* Fill in the global PCM DMA structure with the allocated pointers to descriptors */
   for (i=0; i < PCM6816_NUM_CHANNELS; i++)
   {
      /* Align DMA descriptior to 64Bit Ubus */
      dmaRxDesc_c = (volatile BCM6816_IUDMA_DESC *) ALIGN_DATA( (unsigned int) dmaRxDesc_c, BCM6816_DMA_UBUS_BYTES );
      dmaTxDesc_c = (volatile BCM6816_IUDMA_DESC *) ALIGN_DATA( (unsigned int) dmaTxDesc_c, BCM6816_DMA_UBUS_BYTES );

      gPcmDmaInfo[i].rxChan.dmaDescp = (BCM6816_IUDMA_DESC*)(dmaRxDesc_c + i * DMA_RX_NUM_BUFFERS);
      gPcmDmaInfo[i].txChan.dmaDescp = (BCM6816_IUDMA_DESC*)(dmaTxDesc_c + i * DMA_TX_NUM_BUFFERS);
   }

   /* Clear the descriptors */
   memset( (void *) CacheToNonCacheVirtAddress( dmaRxDesc_c ), 0, rxDescriptorArea );
   memset( (void *) CacheToNonCacheVirtAddress( dmaTxDesc_c ), 0, txDescriptorArea );
   xdrvDCacheClearByAddress( XDRV_CACHE_INVALIDATE, (void*)dmaTxDesc_c, sizeof( dmaTxDesc_c ) );
   xdrvDCacheClearByAddress( XDRV_CACHE_INVALIDATE, (void*)dmaRxDesc_c, sizeof( dmaRxDesc_c ) );

   /* Allocate data buffers */
   rxBufferArea = sizeof(XDRV_UINT32) * (PCM6816_DMA_MAX_BUFFER_SIZE + DMA_PADDING_WORD32) * PCM6816_NUM_CHANNELS * DMA_RX_NUM_BUFFERS;
   txBufferArea = sizeof(XDRV_UINT32) * (PCM6816_DMA_MAX_BUFFER_SIZE + DMA_PADDING_WORD32) * PCM6816_NUM_CHANNELS * DMA_TX_NUM_BUFFERS;
   dmaRxData = dma_alloc_coherent( NULL, rxBufferArea, &gPcmDmaInfo[0].rxChan.dmaBufHandle, GFP_KERNEL );
   dmaTxData = dma_alloc_coherent( NULL, txBufferArea, &gPcmDmaInfo[0].txChan.dmaBufHandle, GFP_KERNEL );

   if ( (dmaRxData == NULL) || (dmaTxData == NULL ) )
   {
      XDRV_LOG_ERROR((XDRV_LOG_MOD_PCM, "Could not allocate memory for DMA data buffers !!! "));
      return( -1 );
   }

   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "rxBufferArea          = %d ", (int)rxBufferArea));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "txBufferArea          = %d ", (int)txBufferArea));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "Unaligned dmaRxData   = 0x%08X ", (unsigned int)dmaRxData));
   XDRV_LOG_DBG((XDRV_LOG_MOD_PCM, "Unaligned dmaTxData   = 0x%08X ", (unsigned int)dmaTxData));

   /* Fill in the global PCM DMA structure with the allocated pointers to descriptors */
   for (i=0; i < PCM6816_NUM_CHANNELS; i++)
   {
      gPcmDmaInfo[i].rxChan.dmaDatap = (PCM6816_DMA_BUFFER*)(dmaRxData + i * DMA_RX_NUM_BUFFERS);
      gPcmDmaInfo[i].txChan.dmaDatap = (PCM6816_DMA_BUFFER*)(dmaTxData + i * DMA_TX_NUM_BUFFERS);
   }

   /* Reset the data buffers */
   memset( (void*) dmaRxData, 0, rxBufferArea);
   memset( (void*) dmaTxData, 0, txBufferArea);

   for (chnum=0; chnum < PCM6816_NUM_CHANNELS; chnum++)
   {
      /* Get the pointer to TX DMA channel info */
      dmaChanInfop = &gPcmDmaInfo[chnum].txChan;

      /* Get the pointer to Tx descriptors for this channel. Convert to non-cached addresses */
      dmaTxDesc = (volatile BCM6816_IUDMA_DESC *)CacheToNonCacheVirtAddress((XDRV_UINT32)dmaChanInfop->dmaDescp);

      /* Init Tx DMA descriptor table */
      for( i = 0; i < DMA_TX_NUM_BUFFERS; i++ )
      {
         /* TX descriptor buffers should be enough to hold packetRate ms worth of sampleRate data */
         bufferSizeBytes = PCM6816_DMA_MAX_BUFFER_SIZE_BYTES;

         /* Each buffer is a complete packet */
         dmaTxDesc[i].flagsLengthStatus.status = BCM6816_IUDMA_DESC_STATUS_SOP |
                                                 BCM6816_IUDMA_DESC_STATUS_EOP;

         if( i == 0 )
         {
            /* First buffer - prime the TX fifo */
            dmaTxDesc[i].flagsLengthStatus.status |= BCM6816_IUDMA_DESC_STATUS_OWN;

            /* Prime with packetRate + 1ms for processing head room from the start of the ISR
            to allow us time to provide another packetRate worth of data to the TX APM DMA. */
            bufferSizeBytes = PCM6816_DMA_MAX_BUFFER_SIZE_BYTES;
         }

         if( i == ( DMA_TX_NUM_BUFFERS - 1 ) )
         {
            /* Last buffer - set the WRAP bit */
            dmaTxDesc[i].flagsLengthStatus.status |= BCM6816_IUDMA_DESC_STATUS_WRAP;
         }

         /* Check if we can accomodate the desired buffer size */
         if (bufferSizeBytes <= PCM6816_DMA_MAX_BUFFER_SIZE_BYTES)
         {
            dmaTxDesc[i].flagsLengthStatus.length = bufferSizeBytes;
         }
         else
         {
            /* Sorry, the allocated buffer size is smaller than what
            ** you want the buffer size configured to, so I can not do this.
            ** You can either increase the compile time buffer size (PCM6816_DMA_MAX_BUFFER_SIZE),
            ** or decrease the buffer size via packetRate/sampleRate */
            XDRV_LOG_ERROR((XDRV_LOG_MOD_PCM, "XDRV_PCM: ERROR - Can not accomodate configured buffer size (%d) ", bufferSizeBytes));
            return ( -1 );
         }


         /* Cache operations (invalidate and write-back) are performed on these
         ** buffers before and after DMA operations. Since cache operations
         ** operate on the entire cache-line, it is necessary to make the
         ** buffers aligned on the cache-line size (16-bytes for the 3368).
         ** Failure to do so may result in corruption of data that shares the
         ** same cache-line as the DMA buffer. */
         dmaDatap = dmaChanInfop->dmaDatap[i].dmaBuff;
         dmaDatap = (volatile XDRV_UINT32 *) ALIGN_DATA( (unsigned int) dmaDatap, DCACHE_LINE_SIZE_BYTES );

         /*  Use physical address */
         dmaTxDesc[i].addr.addr32 = CacheVirtToPhyAddress( (XDRV_UINT32)dmaDatap );

         XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "Tx Desc: chan %d, buf %d, sts 0x%x, len %d, bufp 0x%x ",
                         chnum, i, dmaTxDesc[i].flagsLengthStatus.status,  dmaTxDesc[i].flagsLengthStatus.length,  (unsigned int)dmaTxDesc[i].addr.addr32 ));
      }

      /* Get the pointer to RX DMA channel info */
      dmaChanInfop=&gPcmDmaInfo[chnum].rxChan;

      /* Get the pointer to Rx descriptors for this channel. Convert to non-cached addresses */
      dmaRxDesc = (volatile BCM6816_IUDMA_DESC *)CacheToNonCacheVirtAddress((XDRV_UINT32)dmaChanInfop->dmaDescp);

      /* Init Rx DMA descriptor table */
      for( i = 0; i < DMA_RX_NUM_BUFFERS; i++ )
      {
         /* RX descriptor buffers should be enough to hold packetRate ms worth of sampleRate data */
         bufferSizeBytes = PCM6816_DMA_MAX_BUFFER_SIZE_BYTES;

         /* Give ownership of all descriptors to RX DMA */
         dmaRxDesc[i].flagsLengthStatus.status = BCM6816_IUDMA_DESC_STATUS_OWN;

         if( i == ( DMA_RX_NUM_BUFFERS - 1 ) )
         {
            /* Last descriptor - set the wrap bit */
            dmaRxDesc[i].flagsLengthStatus.status |= BCM6816_IUDMA_DESC_STATUS_WRAP;
         }

         /* Check if we can accomodate the desired buffer size */
         if (bufferSizeBytes <= PCM6816_DMA_MAX_BUFFER_SIZE_BYTES)
         {
            /* Buffer size in bytes */
            dmaRxDesc[i].flagsLengthStatus.length = bufferSizeBytes;
         }
         else
         {
            /* Sorry, the allocated buffer size is smaller than what
            ** you want the buffer size configured to, so I can not do this.
            ** You can either increase the compile time buffer size (PCM6816_DMA_MAX_BUFFER_SIZE),
            ** or decrease the buffer size via packetRate/sampleRate */
            XDRV_LOG_ERROR((XDRV_LOG_MOD_PCM, "XDRV_PCM: ERROR - Can not accomodate configured buffer size (%d) ", bufferSizeBytes));
            return ( -1 );
         }

         /* Cache operations (invalidate and write-back) are performed on these
         ** buffers before and after DMA operations. Since cache operations
         ** operate on the entire cache-line, it is necessary to make the
         ** buffers aligned on the cache-line size (16-bytes for the 6816).
         ** Failure to do so may result in corruption of data that shares the
         ** same cache-line as the DMA buffer. */
         dmaDatap = dmaChanInfop->dmaDatap[i].dmaBuff;
         dmaDatap = (volatile XDRV_UINT32 *) ALIGN_DATA( (unsigned int) dmaDatap, DCACHE_LINE_SIZE_BYTES );

         /* Use physical address */
         dmaRxDesc[i].addr.addr32 = CacheVirtToPhyAddress( (XDRV_UINT32)dmaDatap );

         XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "Rx Desc: chan %d, buf %d, sts 0x%x, len %d, bufp 0x%x ",
                     chnum, i, dmaRxDesc[i].flagsLengthStatus.status, dmaRxDesc[i].flagsLengthStatus.length, (unsigned int)dmaRxDesc[i].addr.addr32 ));
      } /* for */

   } /* for */

   return ( 0 );
}

/*****************************************************************************
*
*  FUNCTION: pcm6816_dmaDescrDeinit
*
*  PURPOSE:
*      Deintialize 6816 DMA descriptors.
*
*  PARAMETERS:
*
*  RETURNS: 0 on SUCCESS
*
*  NOTES:
*
*****************************************************************************/
static int pcm6816_dmaDescrDeinit( void )
{
   XDRV_UINT8                       i;
   XDRV_UINT32                      rxDescriptorArea;
   XDRV_UINT32                      txDescriptorArea;
   XDRV_UINT32                      rxBufferArea;
   XDRV_UINT32                      txBufferArea;

   rxDescriptorArea = sizeof(BCM6816_IUDMA_DESC) * PCM6816_NUM_CHANNELS * DMA_RX_NUM_BUFFERS;
   txDescriptorArea = sizeof(BCM6816_IUDMA_DESC) * PCM6816_NUM_CHANNELS * DMA_TX_NUM_BUFFERS;

   /* Clear the descriptors */
   memset( (void *) CacheToNonCacheVirtAddress( gPcmDmaInfo[0].rxChan.dmaDescp ), 0, rxDescriptorArea);
   memset( (void *) CacheToNonCacheVirtAddress( gPcmDmaInfo[0].txChan.dmaDescp ), 0, txDescriptorArea);

   /* Free receive and transmit descriptors */
   dma_free_coherent(NULL, rxDescriptorArea, gPcmDmaInfo[0].rxChan.dmaDescp, gPcmDmaInfo[0].rxChan.dmaDescHandle);
   dma_free_coherent(NULL, txDescriptorArea, gPcmDmaInfo[0].txChan.dmaDescp, gPcmDmaInfo[0].txChan.dmaDescHandle);

   for (i=0; i < PCM6816_NUM_CHANNELS; i++)
   {
      gPcmDmaInfo[i].rxChan.dmaDescp = NULL;
      gPcmDmaInfo[i].txChan.dmaDescp = NULL;
   }


   rxBufferArea = sizeof(XDRV_UINT32) * (PCM6816_DMA_MAX_BUFFER_SIZE + DMA_PADDING_WORD32) * PCM6816_NUM_CHANNELS * DMA_RX_NUM_BUFFERS;
   txBufferArea = sizeof(XDRV_UINT32) * (PCM6816_DMA_MAX_BUFFER_SIZE + DMA_PADDING_WORD32) * PCM6816_NUM_CHANNELS * DMA_TX_NUM_BUFFERS;

   /* Clear the data buffers */
   memset( (void*) gPcmDmaInfo[0].rxChan.dmaDatap, 0, rxBufferArea);
   memset( (void*) gPcmDmaInfo[0].txChan.dmaDatap, 0, txBufferArea);

   /* Free data buffers */
   dma_free_coherent(NULL, rxBufferArea, gPcmDmaInfo[0].rxChan.dmaDatap, gPcmDmaInfo[0].rxChan.dmaBufHandle);
   dma_free_coherent(NULL, txBufferArea, gPcmDmaInfo[0].txChan.dmaDatap, gPcmDmaInfo[0].txChan.dmaBufHandle);

   /* Fill in the global PCM DMA structure with the allocated pointers to descriptors */
   for (i=0; i < PCM6816_NUM_CHANNELS; i++)
   {
      gPcmDmaInfo[i].rxChan.dmaDatap = NULL;
      gPcmDmaInfo[i].txChan.dmaDatap = NULL;
   }

   return ( 0 );
}


/*****************************************************************************
*
*  FUNCTION: PcmTsAllocate
*
*  PURPOSE:
*      Allocate PCM timeslot
*
*  PARAMETERS:
*
*  RETURNS:
*
*  NOTES:
*
*****************************************************************************/
static void PcmTsAllocate( int chnum, int ts)
{
   int         byte_offset;
   int         bit_offset = 0;
   XDRV_UINT32 entry, mask;

   byte_offset = ts >> 3;
   switch (ts & 7)
   {
     case 0:  bit_offset = 28; break;
     case 1:  bit_offset = 24; break;
     case 2:  bit_offset = 20; break;
     case 3:  bit_offset = 16; break;
     case 4:  bit_offset = 12; break;
     case 5:  bit_offset = 8; break;
     case 6:  bit_offset = 4; break;
     case 7:  bit_offset = 0;
   }

   entry = PCM->pcm_slot_alloc_tbl[byte_offset];
   mask = ( (0xf << bit_offset) * (-1) ) - 1;
   entry &= mask;
   entry |= ( (PCM_TS_VALID | chnum) << bit_offset) ;

   PCM->pcm_slot_alloc_tbl[byte_offset] = entry;

  XDRV_LOG_INFO(( XDRV_LOG_MOD_PCM, "   Channel %d assigned to timeslot %d",chnum,ts));
}

