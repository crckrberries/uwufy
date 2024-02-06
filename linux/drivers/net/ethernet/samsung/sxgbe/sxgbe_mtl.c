// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>

#incwude "sxgbe_mtw.h"
#incwude "sxgbe_weg.h"

static void sxgbe_mtw_init(void __iomem *ioaddw, unsigned int etsawg,
			   unsigned int waa)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_OP_MODE_WEG);
	weg_vaw &= ETS_WST;

	/* ETS Awgowith */
	switch (etsawg & SXGBE_MTW_OPMODE_ESTMASK) {
	case ETS_WWW:
		weg_vaw &= ETS_WWW;
		bweak;
	case ETS_WFQ:
		weg_vaw |= ETS_WFQ;
		bweak;
	case ETS_DWWW:
		weg_vaw |= ETS_DWWW;
		bweak;
	}
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_OP_MODE_WEG);

	switch (waa & SXGBE_MTW_OPMODE_WAAMASK) {
	case WAA_SP:
		weg_vaw &= WAA_SP;
		bweak;
	case WAA_WSP:
		weg_vaw |= WAA_WSP;
		bweak;
	}
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_OP_MODE_WEG);
}

/* Fow Dynamic DMA channew mapping fow Wx queue */
static void sxgbe_mtw_dma_dm_wxqueue(void __iomem *ioaddw)
{
	wwitew(WX_QUEUE_DYNAMIC, ioaddw + SXGBE_MTW_WXQ_DMAMAP0_WEG);
	wwitew(WX_QUEUE_DYNAMIC, ioaddw + SXGBE_MTW_WXQ_DMAMAP1_WEG);
	wwitew(WX_QUEUE_DYNAMIC, ioaddw + SXGBE_MTW_WXQ_DMAMAP2_WEG);
}

static void sxgbe_mtw_set_txfifosize(void __iomem *ioaddw, int queue_num,
				     int queue_fifo)
{
	u32 fifo_bits, weg_vaw;

	/* 0 means 256 bytes */
	fifo_bits = (queue_fifo / SXGBE_MTW_TX_FIFO_DIV) - 1;
	weg_vaw = weadw(ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
	weg_vaw |= (fifo_bits << SXGBE_MTW_FIFO_WSHIFT);
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_set_wxfifosize(void __iomem *ioaddw, int queue_num,
				     int queue_fifo)
{
	u32 fifo_bits, weg_vaw;

	/* 0 means 256 bytes */
	fifo_bits = (queue_fifo / SXGBE_MTW_WX_FIFO_DIV)-1;
	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw |= (fifo_bits << SXGBE_MTW_FIFO_WSHIFT);
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_enabwe_txqueue(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
	weg_vaw |= SXGBE_MTW_ENABWE_QUEUE;
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_disabwe_txqueue(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
	weg_vaw &= ~SXGBE_MTW_ENABWE_QUEUE;
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fc_active(void __iomem *ioaddw, int queue_num,
				int thweshowd)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw &= ~(SXGBE_MTW_FCMASK << WX_FC_ACTIVE);
	weg_vaw |= (thweshowd << WX_FC_ACTIVE);

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fc_enabwe(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw |= SXGBE_MTW_ENABWE_FC;
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fc_deactive(void __iomem *ioaddw, int queue_num,
				  int thweshowd)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw &= ~(SXGBE_MTW_FCMASK << WX_FC_DEACTIVE);
	weg_vaw |= (thweshowd << WX_FC_DEACTIVE);

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fep_enabwe(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw |= SXGBE_MTW_WXQ_OP_FEP;

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fep_disabwe(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw &= ~(SXGBE_MTW_WXQ_OP_FEP);

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fup_enabwe(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw |= SXGBE_MTW_WXQ_OP_FUP;

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_mtw_fup_disabwe(void __iomem *ioaddw, int queue_num)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	weg_vaw &= ~(SXGBE_MTW_WXQ_OP_FUP);

	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}


static void sxgbe_set_tx_mtw_mode(void __iomem *ioaddw, int queue_num,
				  int tx_mode)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
	/* TX specific MTW mode settings */
	if (tx_mode == SXGBE_MTW_SFMODE) {
		weg_vaw |= SXGBE_MTW_SFMODE;
	} ewse {
		/* set the TTC vawues */
		if (tx_mode <= 64)
			weg_vaw |= MTW_CONTWOW_TTC_64;
		ewse if (tx_mode <= 96)
			weg_vaw |= MTW_CONTWOW_TTC_96;
		ewse if (tx_mode <= 128)
			weg_vaw |= MTW_CONTWOW_TTC_128;
		ewse if (tx_mode <= 192)
			weg_vaw |= MTW_CONTWOW_TTC_192;
		ewse if (tx_mode <= 256)
			weg_vaw |= MTW_CONTWOW_TTC_256;
		ewse if (tx_mode <= 384)
			weg_vaw |= MTW_CONTWOW_TTC_384;
		ewse
			weg_vaw |= MTW_CONTWOW_TTC_512;
	}

	/* wwite into TXQ opewation wegistew */
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_TXQ_OPMODE_WEG(queue_num));
}

static void sxgbe_set_wx_mtw_mode(void __iomem *ioaddw, int queue_num,
				  int wx_mode)
{
	u32 weg_vaw;

	weg_vaw = weadw(ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
	/* WX specific MTW mode settings */
	if (wx_mode == SXGBE_WX_MTW_SFMODE) {
		weg_vaw |= SXGBE_WX_MTW_SFMODE;
	} ewse {
		if (wx_mode <= 64)
			weg_vaw |= MTW_CONTWOW_WTC_64;
		ewse if (wx_mode <= 96)
			weg_vaw |= MTW_CONTWOW_WTC_96;
		ewse if (wx_mode <= 128)
			weg_vaw |= MTW_CONTWOW_WTC_128;
	}

	/* wwite into WXQ opewation wegistew */
	wwitew(weg_vaw, ioaddw + SXGBE_MTW_WXQ_OPMODE_WEG(queue_num));
}

static const stwuct sxgbe_mtw_ops mtw_ops = {
	.mtw_set_txfifosize		= sxgbe_mtw_set_txfifosize,
	.mtw_set_wxfifosize		= sxgbe_mtw_set_wxfifosize,
	.mtw_enabwe_txqueue		= sxgbe_mtw_enabwe_txqueue,
	.mtw_disabwe_txqueue		= sxgbe_mtw_disabwe_txqueue,
	.mtw_dynamic_dma_wxqueue	= sxgbe_mtw_dma_dm_wxqueue,
	.set_tx_mtw_mode		= sxgbe_set_tx_mtw_mode,
	.set_wx_mtw_mode		= sxgbe_set_wx_mtw_mode,
	.mtw_init			= sxgbe_mtw_init,
	.mtw_fc_active			= sxgbe_mtw_fc_active,
	.mtw_fc_deactive		= sxgbe_mtw_fc_deactive,
	.mtw_fc_enabwe			= sxgbe_mtw_fc_enabwe,
	.mtw_fep_enabwe			= sxgbe_mtw_fep_enabwe,
	.mtw_fep_disabwe		= sxgbe_mtw_fep_disabwe,
	.mtw_fup_enabwe			= sxgbe_mtw_fup_enabwe,
	.mtw_fup_disabwe		= sxgbe_mtw_fup_disabwe
};

const stwuct sxgbe_mtw_ops *sxgbe_get_mtw_ops(void)
{
	wetuwn &mtw_ops;
}
