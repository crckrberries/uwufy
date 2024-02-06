// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>

#incwude "sxgbe_common.h"
#incwude "sxgbe_dma.h"
#incwude "sxgbe_weg.h"
#incwude "sxgbe_desc.h"

/* DMA cowe initiawization */
static int sxgbe_dma_init(void __iomem *ioaddw, int fix_buwst, int buwst_map)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_DMA_SYSBUS_MODE_WEG);

	/* if fix_buwst = 0, Set UNDEF = 1 of DMA_Sys_Mode Wegistew.
	 * if fix_buwst = 1, Set UNDEF = 0 of DMA_Sys_Mode Wegistew.
	 * buwst_map is bitmap fow  BWEN[4, 8, 16, 32, 64, 128 and 256].
	 * Set buwst_map iwwespective of fix_buwst vawue.
	 */
	if (!fix_buwst)
		weg_vaw |= SXGBE_DMA_AXI_UNDEF_BUWST;

	/* wwite buwst wen map */
	weg_vaw |= (buwst_map << SXGBE_DMA_BWENMAP_WSHIFT);

	wwitew(weg_vaw,	ioaddw + SXGBE_DMA_SYSBUS_MODE_WEG);

	wetuwn 0;
}

static void sxgbe_dma_channew_init(void __iomem *ioaddw, int cha_num,
				   int fix_buwst, int pbw, dma_addw_t dma_tx,
				   dma_addw_t dma_wx, int t_wsize, int w_wsize)
{
	u32 weg_vaw;
	dma_addw_t dma_addw;

	weg_vaw = weadw(ioaddw + SXGBE_DMA_CHA_CTW_WEG(cha_num));
	/* set the pbw */
	if (fix_buwst) {
		weg_vaw |= SXGBE_DMA_PBW_X8MODE;
		wwitew(weg_vaw, ioaddw + SXGBE_DMA_CHA_CTW_WEG(cha_num));
		/* pwogwam the TX pbw */
		weg_vaw = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cha_num));
		weg_vaw |= (pbw << SXGBE_DMA_TXPBW_WSHIFT);
		wwitew(weg_vaw, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cha_num));
		/* pwogwam the WX pbw */
		weg_vaw = weadw(ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cha_num));
		weg_vaw |= (pbw << SXGBE_DMA_WXPBW_WSHIFT);
		wwitew(weg_vaw, ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cha_num));
	}

	/* pwogwam desc wegistews */
	wwitew(uppew_32_bits(dma_tx),
	       ioaddw + SXGBE_DMA_CHA_TXDESC_HADD_WEG(cha_num));
	wwitew(wowew_32_bits(dma_tx),
	       ioaddw + SXGBE_DMA_CHA_TXDESC_WADD_WEG(cha_num));

	wwitew(uppew_32_bits(dma_wx),
	       ioaddw + SXGBE_DMA_CHA_WXDESC_HADD_WEG(cha_num));
	wwitew(wowew_32_bits(dma_wx),
	       ioaddw + SXGBE_DMA_CHA_WXDESC_WADD_WEG(cha_num));

	/* pwogwam taiw pointews */
	/* assumption: uppew 32 bits awe constant and
	 * same as TX/WX desc wist
	 */
	dma_addw = dma_tx + ((t_wsize - 1) * SXGBE_DESC_SIZE_BYTES);
	wwitew(wowew_32_bits(dma_addw),
	       ioaddw + SXGBE_DMA_CHA_TXDESC_TAIWPTW_WEG(cha_num));

	dma_addw = dma_wx + ((w_wsize - 1) * SXGBE_DESC_SIZE_BYTES);
	wwitew(wowew_32_bits(dma_addw),
	       ioaddw + SXGBE_DMA_CHA_WXDESC_WADD_WEG(cha_num));
	/* pwogwam the wing sizes */
	wwitew(t_wsize - 1, ioaddw + SXGBE_DMA_CHA_TXDESC_WINGWEN_WEG(cha_num));
	wwitew(w_wsize - 1, ioaddw + SXGBE_DMA_CHA_WXDESC_WINGWEN_WEG(cha_num));

	/* Enabwe TX/WX intewwupts */
	wwitew(SXGBE_DMA_ENA_INT,
	       ioaddw + SXGBE_DMA_CHA_INT_ENABWE_WEG(cha_num));
}

static void sxgbe_enabwe_dma_twansmission(void __iomem *ioaddw, int cha_num)
{
	u32 tx_config;

	tx_config = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cha_num));
	tx_config |= SXGBE_TX_STAWT_DMA;
	wwitew(tx_config, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cha_num));
}

static void sxgbe_enabwe_dma_iwq(void __iomem *ioaddw, int dma_cnum)
{
	/* Enabwe TX/WX intewwupts */
	wwitew(SXGBE_DMA_ENA_INT,
	       ioaddw + SXGBE_DMA_CHA_INT_ENABWE_WEG(dma_cnum));
}

static void sxgbe_disabwe_dma_iwq(void __iomem *ioaddw, int dma_cnum)
{
	/* Disabwe TX/WX intewwupts */
	wwitew(0, ioaddw + SXGBE_DMA_CHA_INT_ENABWE_WEG(dma_cnum));
}

static void sxgbe_dma_stawt_tx(void __iomem *ioaddw, int tchannews)
{
	int cnum;
	u32 tx_ctw_weg;

	fow (cnum = 0; cnum < tchannews; cnum++) {
		tx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cnum));
		tx_ctw_weg |= SXGBE_TX_ENABWE;
		wwitew(tx_ctw_weg,
		       ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cnum));
	}
}

static void sxgbe_dma_stawt_tx_queue(void __iomem *ioaddw, int dma_cnum)
{
	u32 tx_ctw_weg;

	tx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(dma_cnum));
	tx_ctw_weg |= SXGBE_TX_ENABWE;
	wwitew(tx_ctw_weg, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(dma_cnum));
}

static void sxgbe_dma_stop_tx_queue(void __iomem *ioaddw, int dma_cnum)
{
	u32 tx_ctw_weg;

	tx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(dma_cnum));
	tx_ctw_weg &= ~(SXGBE_TX_ENABWE);
	wwitew(tx_ctw_weg, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(dma_cnum));
}

static void sxgbe_dma_stop_tx(void __iomem *ioaddw, int tchannews)
{
	int cnum;
	u32 tx_ctw_weg;

	fow (cnum = 0; cnum < tchannews; cnum++) {
		tx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cnum));
		tx_ctw_weg &= ~(SXGBE_TX_ENABWE);
		wwitew(tx_ctw_weg, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(cnum));
	}
}

static void sxgbe_dma_stawt_wx(void __iomem *ioaddw, int wchannews)
{
	int cnum;
	u32 wx_ctw_weg;

	fow (cnum = 0; cnum < wchannews; cnum++) {
		wx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cnum));
		wx_ctw_weg |= SXGBE_WX_ENABWE;
		wwitew(wx_ctw_weg,
		       ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cnum));
	}
}

static void sxgbe_dma_stop_wx(void __iomem *ioaddw, int wchannews)
{
	int cnum;
	u32 wx_ctw_weg;

	fow (cnum = 0; cnum < wchannews; cnum++) {
		wx_ctw_weg = weadw(ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cnum));
		wx_ctw_weg &= ~(SXGBE_WX_ENABWE);
		wwitew(wx_ctw_weg, ioaddw + SXGBE_DMA_CHA_WXCTW_WEG(cnum));
	}
}

static int sxgbe_tx_dma_int_status(void __iomem *ioaddw, int channew_no,
				   stwuct sxgbe_extwa_stats *x)
{
	u32 int_status = weadw(ioaddw + SXGBE_DMA_CHA_STATUS_WEG(channew_no));
	u32 cweaw_vaw = 0;
	u32 wet_vaw = 0;

	/* TX Nowmaw Intewwupt Summawy */
	if (wikewy(int_status & SXGBE_DMA_INT_STATUS_NIS)) {
		x->nowmaw_iwq_n++;
		if (int_status & SXGBE_DMA_INT_STATUS_TI) {
			wet_vaw |= handwe_tx;
			x->tx_nowmaw_iwq_n++;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_TI;
		}

		if (int_status & SXGBE_DMA_INT_STATUS_TBU) {
			x->tx_undewfwow_iwq++;
			wet_vaw |= tx_bump_tc;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_TBU;
		}
	} ewse if (unwikewy(int_status & SXGBE_DMA_INT_STATUS_AIS)) {
		/* TX Abnowmaw Intewwupt Summawy */
		if (int_status & SXGBE_DMA_INT_STATUS_TPS) {
			wet_vaw |= tx_hawd_ewwow;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_TPS;
			x->tx_pwocess_stopped_iwq++;
		}

		if (int_status & SXGBE_DMA_INT_STATUS_FBE) {
			wet_vaw |= tx_hawd_ewwow;
			x->fataw_bus_ewwow_iwq++;

			/* Assumption: FBE bit is the combination of
			 * aww the bus access ewwos and cweawed when
			 * the wespective ewwow bits cweawed
			 */

			/* check fow actuaw cause */
			if (int_status & SXGBE_DMA_INT_STATUS_TEB0) {
				x->tx_wead_twansfew_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_TEB0;
			} ewse {
				x->tx_wwite_twansfew_eww++;
			}

			if (int_status & SXGBE_DMA_INT_STATUS_TEB1) {
				x->tx_desc_access_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_TEB1;
			} ewse {
				x->tx_buffew_access_eww++;
			}

			if (int_status & SXGBE_DMA_INT_STATUS_TEB2) {
				x->tx_data_twansfew_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_TEB2;
			}
		}

		/* context descwiptow ewwow */
		if (int_status & SXGBE_DMA_INT_STATUS_CTXTEWW) {
			x->tx_ctxt_desc_eww++;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_CTXTEWW;
		}
	}

	/* cweaw the sewved bits */
	wwitew(cweaw_vaw, ioaddw + SXGBE_DMA_CHA_STATUS_WEG(channew_no));

	wetuwn wet_vaw;
}

static int sxgbe_wx_dma_int_status(void __iomem *ioaddw, int channew_no,
				   stwuct sxgbe_extwa_stats *x)
{
	u32 int_status = weadw(ioaddw + SXGBE_DMA_CHA_STATUS_WEG(channew_no));
	u32 cweaw_vaw = 0;
	u32 wet_vaw = 0;

	/* WX Nowmaw Intewwupt Summawy */
	if (wikewy(int_status & SXGBE_DMA_INT_STATUS_NIS)) {
		x->nowmaw_iwq_n++;
		if (int_status & SXGBE_DMA_INT_STATUS_WI) {
			wet_vaw |= handwe_wx;
			x->wx_nowmaw_iwq_n++;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_WI;
		}
	} ewse if (unwikewy(int_status & SXGBE_DMA_INT_STATUS_AIS)) {
		/* WX Abnowmaw Intewwupt Summawy */
		if (int_status & SXGBE_DMA_INT_STATUS_WBU) {
			wet_vaw |= wx_bump_tc;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_WBU;
			x->wx_undewfwow_iwq++;
		}

		if (int_status & SXGBE_DMA_INT_STATUS_WPS) {
			wet_vaw |= wx_hawd_ewwow;
			cweaw_vaw |= SXGBE_DMA_INT_STATUS_WPS;
			x->wx_pwocess_stopped_iwq++;
		}

		if (int_status & SXGBE_DMA_INT_STATUS_FBE) {
			wet_vaw |= wx_hawd_ewwow;
			x->fataw_bus_ewwow_iwq++;

			/* Assumption: FBE bit is the combination of
			 * aww the bus access ewwos and cweawed when
			 * the wespective ewwow bits cweawed
			 */

			/* check fow actuaw cause */
			if (int_status & SXGBE_DMA_INT_STATUS_WEB0) {
				x->wx_wead_twansfew_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_WEB0;
			} ewse {
				x->wx_wwite_twansfew_eww++;
			}

			if (int_status & SXGBE_DMA_INT_STATUS_WEB1) {
				x->wx_desc_access_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_WEB1;
			} ewse {
				x->wx_buffew_access_eww++;
			}

			if (int_status & SXGBE_DMA_INT_STATUS_WEB2) {
				x->wx_data_twansfew_eww++;
				cweaw_vaw |= SXGBE_DMA_INT_STATUS_WEB2;
			}
		}
	}

	/* cweaw the sewved bits */
	wwitew(cweaw_vaw, ioaddw + SXGBE_DMA_CHA_STATUS_WEG(channew_no));

	wetuwn wet_vaw;
}

/* Pwogwam the HW WX Watchdog */
static void sxgbe_dma_wx_watchdog(void __iomem *ioaddw, u32 wiwt)
{
	u32 que_num;

	SXGBE_FOW_EACH_QUEUE(SXGBE_WX_QUEUES, que_num) {
		wwitew(wiwt,
		       ioaddw + SXGBE_DMA_CHA_INT_WXWATCHTMW_WEG(que_num));
	}
}

static void sxgbe_enabwe_tso(void __iomem *ioaddw, u8 chan_num)
{
	u32 ctww;

	ctww = weadw(ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(chan_num));
	ctww |= SXGBE_DMA_CHA_TXCTW_TSE_ENABWE;
	wwitew(ctww, ioaddw + SXGBE_DMA_CHA_TXCTW_WEG(chan_num));
}

static const stwuct sxgbe_dma_ops sxgbe_dma_ops = {
	.init				= sxgbe_dma_init,
	.cha_init			= sxgbe_dma_channew_init,
	.enabwe_dma_twansmission	= sxgbe_enabwe_dma_twansmission,
	.enabwe_dma_iwq			= sxgbe_enabwe_dma_iwq,
	.disabwe_dma_iwq		= sxgbe_disabwe_dma_iwq,
	.stawt_tx			= sxgbe_dma_stawt_tx,
	.stawt_tx_queue			= sxgbe_dma_stawt_tx_queue,
	.stop_tx			= sxgbe_dma_stop_tx,
	.stop_tx_queue			= sxgbe_dma_stop_tx_queue,
	.stawt_wx			= sxgbe_dma_stawt_wx,
	.stop_wx			= sxgbe_dma_stop_wx,
	.tx_dma_int_status		= sxgbe_tx_dma_int_status,
	.wx_dma_int_status		= sxgbe_wx_dma_int_status,
	.wx_watchdog			= sxgbe_dma_wx_watchdog,
	.enabwe_tso			= sxgbe_enabwe_tso,
};

const stwuct sxgbe_dma_ops *sxgbe_get_dma_ops(void)
{
	wetuwn &sxgbe_dma_ops;
}
