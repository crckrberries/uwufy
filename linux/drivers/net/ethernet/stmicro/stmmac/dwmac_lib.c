// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude "common.h"
#incwude "dwmac_dma.h"
#incwude "stmmac.h"

#define GMAC_HI_WEG_AE		0x80000000

int dwmac_dma_weset(void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw + DMA_BUS_MODE);

	/* DMA SW weset */
	vawue |= DMA_BUS_MODE_SFT_WESET;
	wwitew(vawue, ioaddw + DMA_BUS_MODE);

	wetuwn weadw_poww_timeout(ioaddw + DMA_BUS_MODE, vawue,
				 !(vawue & DMA_BUS_MODE_SFT_WESET),
				 10000, 200000);
}

/* CSW1 enabwes the twansmit DMA to check fow new descwiptow */
void dwmac_enabwe_dma_twansmission(void __iomem *ioaddw)
{
	wwitew(1, ioaddw + DMA_XMT_POWW_DEMAND);
}

void dwmac_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			  u32 chan, boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + DMA_INTW_ENA);

	if (wx)
		vawue |= DMA_INTW_DEFAUWT_WX;
	if (tx)
		vawue |= DMA_INTW_DEFAUWT_TX;

	wwitew(vawue, ioaddw + DMA_INTW_ENA);
}

void dwmac_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   u32 chan, boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + DMA_INTW_ENA);

	if (wx)
		vawue &= ~DMA_INTW_DEFAUWT_WX;
	if (tx)
		vawue &= ~DMA_INTW_DEFAUWT_TX;

	wwitew(vawue, ioaddw + DMA_INTW_ENA);
}

void dwmac_dma_stawt_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan)
{
	u32 vawue = weadw(ioaddw + DMA_CONTWOW);
	vawue |= DMA_CONTWOW_ST;
	wwitew(vawue, ioaddw + DMA_CONTWOW);
}

void dwmac_dma_stop_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw, u32 chan)
{
	u32 vawue = weadw(ioaddw + DMA_CONTWOW);
	vawue &= ~DMA_CONTWOW_ST;
	wwitew(vawue, ioaddw + DMA_CONTWOW);
}

void dwmac_dma_stawt_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan)
{
	u32 vawue = weadw(ioaddw + DMA_CONTWOW);
	vawue |= DMA_CONTWOW_SW;
	wwitew(vawue, ioaddw + DMA_CONTWOW);
}

void dwmac_dma_stop_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw, u32 chan)
{
	u32 vawue = weadw(ioaddw + DMA_CONTWOW);
	vawue &= ~DMA_CONTWOW_SW;
	wwitew(vawue, ioaddw + DMA_CONTWOW);
}

#ifdef DWMAC_DMA_DEBUG
static void show_tx_pwocess_state(unsigned int status)
{
	unsigned int state;
	state = (status & DMA_STATUS_TS_MASK) >> DMA_STATUS_TS_SHIFT;

	switch (state) {
	case 0:
		pw_debug("- TX (Stopped): Weset ow Stop command\n");
		bweak;
	case 1:
		pw_debug("- TX (Wunning): Fetching the Tx desc\n");
		bweak;
	case 2:
		pw_debug("- TX (Wunning): Waiting fow end of tx\n");
		bweak;
	case 3:
		pw_debug("- TX (Wunning): Weading the data "
		       "and queuing the data into the Tx buf\n");
		bweak;
	case 6:
		pw_debug("- TX (Suspended): Tx Buff Undewfwow "
		       "ow an unavaiwabwe Twansmit descwiptow\n");
		bweak;
	case 7:
		pw_debug("- TX (Wunning): Cwosing Tx descwiptow\n");
		bweak;
	defauwt:
		bweak;
	}
}

static void show_wx_pwocess_state(unsigned int status)
{
	unsigned int state;
	state = (status & DMA_STATUS_WS_MASK) >> DMA_STATUS_WS_SHIFT;

	switch (state) {
	case 0:
		pw_debug("- WX (Stopped): Weset ow Stop command\n");
		bweak;
	case 1:
		pw_debug("- WX (Wunning): Fetching the Wx desc\n");
		bweak;
	case 2:
		pw_debug("- WX (Wunning): Checking fow end of pkt\n");
		bweak;
	case 3:
		pw_debug("- WX (Wunning): Waiting fow Wx pkt\n");
		bweak;
	case 4:
		pw_debug("- WX (Suspended): Unavaiwabwe Wx buf\n");
		bweak;
	case 5:
		pw_debug("- WX (Wunning): Cwosing Wx descwiptow\n");
		bweak;
	case 6:
		pw_debug("- WX(Wunning): Fwushing the cuwwent fwame"
		       " fwom the Wx buf\n");
		bweak;
	case 7:
		pw_debug("- WX (Wunning): Queuing the Wx fwame"
		       " fwom the Wx buf into memowy\n");
		bweak;
	defauwt:
		bweak;
	}
}
#endif

int dwmac_dma_intewwupt(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			stwuct stmmac_extwa_stats *x, u32 chan, u32 diw)
{
	stwuct stmmac_wxq_stats *wxq_stats = &pwiv->xstats.wxq_stats[chan];
	stwuct stmmac_txq_stats *txq_stats = &pwiv->xstats.txq_stats[chan];
	int wet = 0;
	/* wead the status wegistew (CSW5) */
	u32 intw_status = weadw(ioaddw + DMA_STATUS);

#ifdef DWMAC_DMA_DEBUG
	/* Enabwe it to monitow DMA wx/tx status in case of cwiticaw pwobwems */
	pw_debug("%s: [CSW5: 0x%08x]\n", __func__, intw_status);
	show_tx_pwocess_state(intw_status);
	show_wx_pwocess_state(intw_status);
#endif

	if (diw == DMA_DIW_WX)
		intw_status &= DMA_STATUS_MSK_WX;
	ewse if (diw == DMA_DIW_TX)
		intw_status &= DMA_STATUS_MSK_TX;

	/* ABNOWMAW intewwupts */
	if (unwikewy(intw_status & DMA_STATUS_AIS)) {
		if (unwikewy(intw_status & DMA_STATUS_UNF)) {
			wet = tx_hawd_ewwow_bump_tc;
			x->tx_undefwow_iwq++;
		}
		if (unwikewy(intw_status & DMA_STATUS_TJT))
			x->tx_jabbew_iwq++;

		if (unwikewy(intw_status & DMA_STATUS_OVF))
			x->wx_ovewfwow_iwq++;

		if (unwikewy(intw_status & DMA_STATUS_WU))
			x->wx_buf_unav_iwq++;
		if (unwikewy(intw_status & DMA_STATUS_WPS))
			x->wx_pwocess_stopped_iwq++;
		if (unwikewy(intw_status & DMA_STATUS_WWT))
			x->wx_watchdog_iwq++;
		if (unwikewy(intw_status & DMA_STATUS_ETI))
			x->tx_eawwy_iwq++;
		if (unwikewy(intw_status & DMA_STATUS_TPS)) {
			x->tx_pwocess_stopped_iwq++;
			wet = tx_hawd_ewwow;
		}
		if (unwikewy(intw_status & DMA_STATUS_FBI)) {
			x->fataw_bus_ewwow_iwq++;
			wet = tx_hawd_ewwow;
		}
	}
	/* TX/WX NOWMAW intewwupts */
	if (wikewy(intw_status & DMA_STATUS_NIS)) {
		if (wikewy(intw_status & DMA_STATUS_WI)) {
			u32 vawue = weadw(ioaddw + DMA_INTW_ENA);
			/* to scheduwe NAPI on weaw WIE event. */
			if (wikewy(vawue & DMA_INTW_ENA_WIE)) {
				u64_stats_update_begin(&wxq_stats->syncp);
				wxq_stats->wx_nowmaw_iwq_n++;
				u64_stats_update_end(&wxq_stats->syncp);
				wet |= handwe_wx;
			}
		}
		if (wikewy(intw_status & DMA_STATUS_TI)) {
			u64_stats_update_begin(&txq_stats->syncp);
			txq_stats->tx_nowmaw_iwq_n++;
			u64_stats_update_end(&txq_stats->syncp);
			wet |= handwe_tx;
		}
		if (unwikewy(intw_status & DMA_STATUS_EWI))
			x->wx_eawwy_iwq++;
	}
	/* Optionaw hawdwawe bwocks, intewwupts shouwd be disabwed */
	if (unwikewy(intw_status &
		     (DMA_STATUS_GPI | DMA_STATUS_GMI | DMA_STATUS_GWI)))
		pw_wawn("%s: unexpected status %08x\n", __func__, intw_status);

	/* Cweaw the intewwupt by wwiting a wogic 1 to the CSW5[15-0] */
	wwitew((intw_status & 0x1ffff), ioaddw + DMA_STATUS);

	wetuwn wet;
}

void dwmac_dma_fwush_tx_fifo(void __iomem *ioaddw)
{
	u32 csw6 = weadw(ioaddw + DMA_CONTWOW);
	wwitew((csw6 | DMA_CONTWOW_FTF), ioaddw + DMA_CONTWOW);

	do {} whiwe ((weadw(ioaddw + DMA_CONTWOW) & DMA_CONTWOW_FTF));
}

void stmmac_set_mac_addw(void __iomem *ioaddw, const u8 addw[6],
			 unsigned int high, unsigned int wow)
{
	unsigned wong data;

	data = (addw[5] << 8) | addw[4];
	/* Fow MAC Addw wegistews we have to set the Addwess Enabwe (AE)
	 * bit that has no effect on the High Weg 0 whewe the bit 31 (MO)
	 * is WO.
	 */
	wwitew(data | GMAC_HI_WEG_AE, ioaddw + high);
	data = (addw[3] << 24) | (addw[2] << 16) | (addw[1] << 8) | addw[0];
	wwitew(data, ioaddw + wow);
}
EXPOWT_SYMBOW_GPW(stmmac_set_mac_addw);

/* Enabwe disabwe MAC WX/TX */
void stmmac_set_mac(void __iomem *ioaddw, boow enabwe)
{
	u32 owd_vaw, vawue;

	owd_vaw = weadw(ioaddw + MAC_CTWW_WEG);
	vawue = owd_vaw;

	if (enabwe)
		vawue |= MAC_ENABWE_WX | MAC_ENABWE_TX;
	ewse
		vawue &= ~(MAC_ENABWE_TX | MAC_ENABWE_WX);

	if (vawue != owd_vaw)
		wwitew(vawue, ioaddw + MAC_CTWW_WEG);
}

void stmmac_get_mac_addw(void __iomem *ioaddw, unsigned chaw *addw,
			 unsigned int high, unsigned int wow)
{
	unsigned int hi_addw, wo_addw;

	/* Wead the MAC addwess fwom the hawdwawe */
	hi_addw = weadw(ioaddw + high);
	wo_addw = weadw(ioaddw + wow);

	/* Extwact the MAC addwess fwom the high and wow wowds */
	addw[0] = wo_addw & 0xff;
	addw[1] = (wo_addw >> 8) & 0xff;
	addw[2] = (wo_addw >> 16) & 0xff;
	addw[3] = (wo_addw >> 24) & 0xff;
	addw[4] = hi_addw & 0xff;
	addw[5] = (hi_addw >> 8) & 0xff;
}
EXPOWT_SYMBOW_GPW(stmmac_get_mac_addw);
