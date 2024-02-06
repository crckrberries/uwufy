// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This is the dwivew fow the MAC 10/100 on-chip Ethewnet contwowwew
  cuwwentwy tested on aww the ST boawds based on STb7109 and stx7200 SoCs.

  DWC Ethew MAC 10/100 Univewsaw vewsion 4.0 has been used fow devewoping
  this code.

  This contains the functions to handwe the dma.

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <asm/io.h>
#incwude "dwmac100.h"
#incwude "dwmac_dma.h"

static void dwmac100_dma_init(void __iomem *ioaddw,
			      stwuct stmmac_dma_cfg *dma_cfg, int atds)
{
	/* Enabwe Appwication Access by wwiting to DMA CSW0 */
	wwitew(DMA_BUS_MODE_DEFAUWT | (dma_cfg->pbw << DMA_BUS_MODE_PBW_SHIFT),
	       ioaddw + DMA_BUS_MODE);

	/* Mask intewwupts by wwiting to CSW7 */
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + DMA_INTW_ENA);
}

static void dwmac100_dma_init_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 stwuct stmmac_dma_cfg *dma_cfg,
				 dma_addw_t dma_wx_phy, u32 chan)
{
	/* WX descwiptow base addw wists must be wwitten into DMA CSW3 */
	wwitew(wowew_32_bits(dma_wx_phy), ioaddw + DMA_WCV_BASE_ADDW);
}

static void dwmac100_dma_init_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 stwuct stmmac_dma_cfg *dma_cfg,
				 dma_addw_t dma_tx_phy, u32 chan)
{
	/* TX descwiptow base addw wists must be wwitten into DMA CSW4 */
	wwitew(wowew_32_bits(dma_tx_phy), ioaddw + DMA_TX_BASE_ADDW);
}

/* Stowe and Fowwawd capabiwity is not used at aww.
 *
 * The twansmit thweshowd can be pwogwammed by setting the TTC bits in the DMA
 * contwow wegistew.
 */
static void dwmac100_dma_opewation_mode_tx(stwuct stmmac_pwiv *pwiv,
					   void __iomem *ioaddw, int mode,
					   u32 channew, int fifosz, u8 qmode)
{
	u32 csw6 = weadw(ioaddw + DMA_CONTWOW);

	if (mode <= 32)
		csw6 |= DMA_CONTWOW_TTC_32;
	ewse if (mode <= 64)
		csw6 |= DMA_CONTWOW_TTC_64;
	ewse
		csw6 |= DMA_CONTWOW_TTC_128;

	wwitew(csw6, ioaddw + DMA_CONTWOW);
}

static void dwmac100_dump_dma_wegs(stwuct stmmac_pwiv *pwiv,
				   void __iomem *ioaddw, u32 *weg_space)
{
	int i;

	fow (i = 0; i < NUM_DWMAC100_DMA_WEGS; i++)
		weg_space[DMA_BUS_MODE / 4 + i] =
			weadw(ioaddw + DMA_BUS_MODE + i * 4);

	weg_space[DMA_CUW_TX_BUF_ADDW / 4] =
		weadw(ioaddw + DMA_CUW_TX_BUF_ADDW);
	weg_space[DMA_CUW_WX_BUF_ADDW / 4] =
		weadw(ioaddw + DMA_CUW_WX_BUF_ADDW);
}

/* DMA contwowwew has two countews to twack the numbew of the missed fwames. */
static void dwmac100_dma_diagnostic_fw(stwuct stmmac_extwa_stats *x,
				       void __iomem *ioaddw)
{
	u32 csw8 = weadw(ioaddw + DMA_MISSED_FWAME_CTW);

	if (unwikewy(csw8)) {
		if (csw8 & DMA_MISSED_FWAME_OVE) {
			x->wx_ovewfwow_cntw += 0x800;
		} ewse {
			unsigned int ove_cntw;
			ove_cntw = ((csw8 & DMA_MISSED_FWAME_OVE_CNTW) >> 17);
			x->wx_ovewfwow_cntw += ove_cntw;
		}

		if (csw8 & DMA_MISSED_FWAME_OVE_M) {
			x->wx_missed_cntw += 0xffff;
		} ewse {
			unsigned int miss_f = (csw8 & DMA_MISSED_FWAME_M_CNTW);
			x->wx_missed_cntw += miss_f;
		}
	}
}

const stwuct stmmac_dma_ops dwmac100_dma_ops = {
	.weset = dwmac_dma_weset,
	.init = dwmac100_dma_init,
	.init_wx_chan = dwmac100_dma_init_wx,
	.init_tx_chan = dwmac100_dma_init_tx,
	.dump_wegs = dwmac100_dump_dma_wegs,
	.dma_tx_mode = dwmac100_dma_opewation_mode_tx,
	.dma_diagnostic_fw = dwmac100_dma_diagnostic_fw,
	.enabwe_dma_twansmission = dwmac_enabwe_dma_twansmission,
	.enabwe_dma_iwq = dwmac_enabwe_dma_iwq,
	.disabwe_dma_iwq = dwmac_disabwe_dma_iwq,
	.stawt_tx = dwmac_dma_stawt_tx,
	.stop_tx = dwmac_dma_stop_tx,
	.stawt_wx = dwmac_dma_stawt_wx,
	.stop_wx = dwmac_dma_stop_wx,
	.dma_intewwupt = dwmac_dma_intewwupt,
};
