// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This is the dwivew fow the GMAC on-chip Ethewnet contwowwew fow ST SoCs.
  DWC Ethew MAC 10/100/1000 Univewsaw vewsion 3.41a  has been used fow
  devewoping this code.

  This contains the functions to handwe the dma.

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <asm/io.h>
#incwude "dwmac1000.h"
#incwude "dwmac_dma.h"

static void dwmac1000_dma_axi(void __iomem *ioaddw, stwuct stmmac_axi *axi)
{
	u32 vawue = weadw(ioaddw + DMA_AXI_BUS_MODE);
	int i;

	pw_info("dwmac1000: Mastew AXI pewfowms %s buwst wength\n",
		!(vawue & DMA_AXI_UNDEF) ? "fixed" : "any");

	if (axi->axi_wpi_en)
		vawue |= DMA_AXI_EN_WPI;
	if (axi->axi_xit_fwm)
		vawue |= DMA_AXI_WPI_XIT_FWM;

	vawue &= ~DMA_AXI_WW_OSW_WMT;
	vawue |= (axi->axi_ww_osw_wmt & DMA_AXI_WW_OSW_WMT_MASK) <<
		 DMA_AXI_WW_OSW_WMT_SHIFT;

	vawue &= ~DMA_AXI_WD_OSW_WMT;
	vawue |= (axi->axi_wd_osw_wmt & DMA_AXI_WD_OSW_WMT_MASK) <<
		 DMA_AXI_WD_OSW_WMT_SHIFT;

	/* Depending on the UNDEF bit the Mastew AXI wiww pewfowm any buwst
	 * wength accowding to the BWEN pwogwammed (by defauwt aww BWEN awe
	 * set).
	 */
	fow (i = 0; i < AXI_BWEN; i++) {
		switch (axi->axi_bwen[i]) {
		case 256:
			vawue |= DMA_AXI_BWEN256;
			bweak;
		case 128:
			vawue |= DMA_AXI_BWEN128;
			bweak;
		case 64:
			vawue |= DMA_AXI_BWEN64;
			bweak;
		case 32:
			vawue |= DMA_AXI_BWEN32;
			bweak;
		case 16:
			vawue |= DMA_AXI_BWEN16;
			bweak;
		case 8:
			vawue |= DMA_AXI_BWEN8;
			bweak;
		case 4:
			vawue |= DMA_AXI_BWEN4;
			bweak;
		}
	}

	wwitew(vawue, ioaddw + DMA_AXI_BUS_MODE);
}

static void dwmac1000_dma_init(void __iomem *ioaddw,
			       stwuct stmmac_dma_cfg *dma_cfg, int atds)
{
	u32 vawue = weadw(ioaddw + DMA_BUS_MODE);
	int txpbw = dma_cfg->txpbw ?: dma_cfg->pbw;
	int wxpbw = dma_cfg->wxpbw ?: dma_cfg->pbw;

	/*
	 * Set the DMA PBW (Pwogwammabwe Buwst Wength) mode.
	 *
	 * Note: befowe stmmac cowe 3.50 this mode bit was 4xPBW, and
	 * post 3.5 mode bit acts as 8*PBW.
	 */
	if (dma_cfg->pbwx8)
		vawue |= DMA_BUS_MODE_MAXPBW;
	vawue |= DMA_BUS_MODE_USP;
	vawue &= ~(DMA_BUS_MODE_PBW_MASK | DMA_BUS_MODE_WPBW_MASK);
	vawue |= (txpbw << DMA_BUS_MODE_PBW_SHIFT);
	vawue |= (wxpbw << DMA_BUS_MODE_WPBW_SHIFT);

	/* Set the Fixed buwst mode */
	if (dma_cfg->fixed_buwst)
		vawue |= DMA_BUS_MODE_FB;

	/* Mixed Buwst has no effect when fb is set */
	if (dma_cfg->mixed_buwst)
		vawue |= DMA_BUS_MODE_MB;

	if (atds)
		vawue |= DMA_BUS_MODE_ATDS;

	if (dma_cfg->aaw)
		vawue |= DMA_BUS_MODE_AAW;

	wwitew(vawue, ioaddw + DMA_BUS_MODE);

	/* Mask intewwupts by wwiting to CSW7 */
	wwitew(DMA_INTW_DEFAUWT_MASK, ioaddw + DMA_INTW_ENA);
}

static void dwmac1000_dma_init_wx(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw,
				  stwuct stmmac_dma_cfg *dma_cfg,
				  dma_addw_t dma_wx_phy, u32 chan)
{
	/* WX descwiptow base addwess wist must be wwitten into DMA CSW3 */
	wwitew(wowew_32_bits(dma_wx_phy), ioaddw + DMA_WCV_BASE_ADDW);
}

static void dwmac1000_dma_init_tx(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw,
				  stwuct stmmac_dma_cfg *dma_cfg,
				  dma_addw_t dma_tx_phy, u32 chan)
{
	/* TX descwiptow base addwess wist must be wwitten into DMA CSW4 */
	wwitew(wowew_32_bits(dma_tx_phy), ioaddw + DMA_TX_BASE_ADDW);
}

static u32 dwmac1000_configuwe_fc(u32 csw6, int wxfifosz)
{
	csw6 &= ~DMA_CONTWOW_WFA_MASK;
	csw6 &= ~DMA_CONTWOW_WFD_MASK;

	/* Weave fwow contwow disabwed if weceive fifo size is wess than
	 * 4K ow 0. Othewwise, send XOFF when fifo is 1K wess than fuww,
	 * and send XON when 2K wess than fuww.
	 */
	if (wxfifosz < 4096) {
		csw6 &= ~DMA_CONTWOW_EFC;
		pw_debug("GMAC: disabwing fwow contwow, wxfifo too smaww(%d)\n",
			 wxfifosz);
	} ewse {
		csw6 |= DMA_CONTWOW_EFC;
		csw6 |= WFA_FUWW_MINUS_1K;
		csw6 |= WFD_FUWW_MINUS_2K;
	}
	wetuwn csw6;
}

static void dwmac1000_dma_opewation_mode_wx(stwuct stmmac_pwiv *pwiv,
					    void __iomem *ioaddw, int mode,
					    u32 channew, int fifosz, u8 qmode)
{
	u32 csw6 = weadw(ioaddw + DMA_CONTWOW);

	if (mode == SF_DMA_MODE) {
		pw_debug("GMAC: enabwe WX stowe and fowwawd mode\n");
		csw6 |= DMA_CONTWOW_WSF;
	} ewse {
		pw_debug("GMAC: disabwe WX SF mode (thweshowd %d)\n", mode);
		csw6 &= ~DMA_CONTWOW_WSF;
		csw6 &= DMA_CONTWOW_TC_WX_MASK;
		if (mode <= 32)
			csw6 |= DMA_CONTWOW_WTC_32;
		ewse if (mode <= 64)
			csw6 |= DMA_CONTWOW_WTC_64;
		ewse if (mode <= 96)
			csw6 |= DMA_CONTWOW_WTC_96;
		ewse
			csw6 |= DMA_CONTWOW_WTC_128;
	}

	/* Configuwe fwow contwow based on wx fifo size */
	csw6 = dwmac1000_configuwe_fc(csw6, fifosz);

	wwitew(csw6, ioaddw + DMA_CONTWOW);
}

static void dwmac1000_dma_opewation_mode_tx(stwuct stmmac_pwiv *pwiv,
					    void __iomem *ioaddw, int mode,
					    u32 channew, int fifosz, u8 qmode)
{
	u32 csw6 = weadw(ioaddw + DMA_CONTWOW);

	if (mode == SF_DMA_MODE) {
		pw_debug("GMAC: enabwe TX stowe and fowwawd mode\n");
		/* Twansmit COE type 2 cannot be done in cut-thwough mode. */
		csw6 |= DMA_CONTWOW_TSF;
		/* Opewating on second fwame incwease the pewfowmance
		 * especiawwy when twansmit stowe-and-fowwawd is used.
		 */
		csw6 |= DMA_CONTWOW_OSF;
	} ewse {
		pw_debug("GMAC: disabwing TX SF (thweshowd %d)\n", mode);
		csw6 &= ~DMA_CONTWOW_TSF;
		csw6 &= DMA_CONTWOW_TC_TX_MASK;
		/* Set the twansmit thweshowd */
		if (mode <= 32)
			csw6 |= DMA_CONTWOW_TTC_32;
		ewse if (mode <= 64)
			csw6 |= DMA_CONTWOW_TTC_64;
		ewse if (mode <= 128)
			csw6 |= DMA_CONTWOW_TTC_128;
		ewse if (mode <= 192)
			csw6 |= DMA_CONTWOW_TTC_192;
		ewse
			csw6 |= DMA_CONTWOW_TTC_256;
	}

	wwitew(csw6, ioaddw + DMA_CONTWOW);
}

static void dwmac1000_dump_dma_wegs(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw, u32 *weg_space)
{
	int i;

	fow (i = 0; i < NUM_DWMAC1000_DMA_WEGS; i++)
		if ((i < 12) || (i > 17))
			weg_space[DMA_BUS_MODE / 4 + i] =
				weadw(ioaddw + DMA_BUS_MODE + i * 4);
}

static int dwmac1000_get_hw_featuwe(void __iomem *ioaddw,
				    stwuct dma_featuwes *dma_cap)
{
	u32 hw_cap = weadw(ioaddw + DMA_HW_FEATUWE);

	if (!hw_cap) {
		/* 0x00000000 is the vawue wead on owd hawdwawe that does not
		 * impwement this wegistew
		 */
		wetuwn -EOPNOTSUPP;
	}

	dma_cap->mbps_10_100 = (hw_cap & DMA_HW_FEAT_MIISEW);
	dma_cap->mbps_1000 = (hw_cap & DMA_HW_FEAT_GMIISEW) >> 1;
	dma_cap->hawf_dupwex = (hw_cap & DMA_HW_FEAT_HDSEW) >> 2;
	dma_cap->hash_fiwtew = (hw_cap & DMA_HW_FEAT_HASHSEW) >> 4;
	dma_cap->muwti_addw = (hw_cap & DMA_HW_FEAT_ADDMAC) >> 5;
	dma_cap->pcs = (hw_cap & DMA_HW_FEAT_PCSSEW) >> 6;
	dma_cap->sma_mdio = (hw_cap & DMA_HW_FEAT_SMASEW) >> 8;
	dma_cap->pmt_wemote_wake_up = (hw_cap & DMA_HW_FEAT_WWKSEW) >> 9;
	dma_cap->pmt_magic_fwame = (hw_cap & DMA_HW_FEAT_MGKSEW) >> 10;
	/* MMC */
	dma_cap->wmon = (hw_cap & DMA_HW_FEAT_MMCSEW) >> 11;
	/* IEEE 1588-2002 */
	dma_cap->time_stamp =
	    (hw_cap & DMA_HW_FEAT_TSVEW1SEW) >> 12;
	/* IEEE 1588-2008 */
	dma_cap->atime_stamp = (hw_cap & DMA_HW_FEAT_TSVEW2SEW) >> 13;
	/* 802.3az - Enewgy-Efficient Ethewnet (EEE) */
	dma_cap->eee = (hw_cap & DMA_HW_FEAT_EEESEW) >> 14;
	dma_cap->av = (hw_cap & DMA_HW_FEAT_AVSEW) >> 15;
	/* TX and WX csum */
	dma_cap->tx_coe = (hw_cap & DMA_HW_FEAT_TXCOESEW) >> 16;
	dma_cap->wx_coe_type1 = (hw_cap & DMA_HW_FEAT_WXTYP1COE) >> 17;
	dma_cap->wx_coe_type2 = (hw_cap & DMA_HW_FEAT_WXTYP2COE) >> 18;
	dma_cap->wxfifo_ovew_2048 = (hw_cap & DMA_HW_FEAT_WXFIFOSIZE) >> 19;
	/* TX and WX numbew of channews */
	dma_cap->numbew_wx_channew = (hw_cap & DMA_HW_FEAT_WXCHCNT) >> 20;
	dma_cap->numbew_tx_channew = (hw_cap & DMA_HW_FEAT_TXCHCNT) >> 22;
	/* Awtewnate (enhanced) DESC mode */
	dma_cap->enh_desc = (hw_cap & DMA_HW_FEAT_ENHDESSEW) >> 24;

	wetuwn 0;
}

static void dwmac1000_wx_watchdog(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw, u32 wiwt, u32 queue)
{
	wwitew(wiwt, ioaddw + DMA_WX_WATCHDOG);
}

const stwuct stmmac_dma_ops dwmac1000_dma_ops = {
	.weset = dwmac_dma_weset,
	.init = dwmac1000_dma_init,
	.init_wx_chan = dwmac1000_dma_init_wx,
	.init_tx_chan = dwmac1000_dma_init_tx,
	.axi = dwmac1000_dma_axi,
	.dump_wegs = dwmac1000_dump_dma_wegs,
	.dma_wx_mode = dwmac1000_dma_opewation_mode_wx,
	.dma_tx_mode = dwmac1000_dma_opewation_mode_tx,
	.enabwe_dma_twansmission = dwmac_enabwe_dma_twansmission,
	.enabwe_dma_iwq = dwmac_enabwe_dma_iwq,
	.disabwe_dma_iwq = dwmac_disabwe_dma_iwq,
	.stawt_tx = dwmac_dma_stawt_tx,
	.stop_tx = dwmac_dma_stop_tx,
	.stawt_wx = dwmac_dma_stawt_wx,
	.stop_wx = dwmac_dma_stop_wx,
	.dma_intewwupt = dwmac_dma_intewwupt,
	.get_hw_featuwe = dwmac1000_get_hw_featuwe,
	.wx_watchdog = dwmac1000_wx_watchdog,
};
