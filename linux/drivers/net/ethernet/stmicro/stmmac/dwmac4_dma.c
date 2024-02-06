// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is the dwivew fow the GMAC on-chip Ethewnet contwowwew fow ST SoCs.
 * DWC Ethew MAC vewsion 4.xx  has been used fow  devewoping this code.
 *
 * This contains the functions to handwe the dma.
 *
 * Copywight (C) 2015  STMicwoewectwonics Wtd
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#incwude <winux/io.h>
#incwude "dwmac4.h"
#incwude "dwmac4_dma.h"
#incwude "stmmac.h"

static void dwmac4_dma_axi(void __iomem *ioaddw, stwuct stmmac_axi *axi)
{
	u32 vawue = weadw(ioaddw + DMA_SYS_BUS_MODE);
	int i;

	pw_info("dwmac4: Mastew AXI pewfowms %s buwst wength\n",
		(vawue & DMA_SYS_BUS_FB) ? "fixed" : "any");

	if (axi->axi_wpi_en)
		vawue |= DMA_AXI_EN_WPI;
	if (axi->axi_xit_fwm)
		vawue |= DMA_AXI_WPI_XIT_FWM;

	vawue &= ~DMA_AXI_WW_OSW_WMT;
	vawue |= (axi->axi_ww_osw_wmt & DMA_AXI_OSW_MAX) <<
		 DMA_AXI_WW_OSW_WMT_SHIFT;

	vawue &= ~DMA_AXI_WD_OSW_WMT;
	vawue |= (axi->axi_wd_osw_wmt & DMA_AXI_OSW_MAX) <<
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

	wwitew(vawue, ioaddw + DMA_SYS_BUS_MODE);
}

static void dwmac4_dma_init_wx_chan(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw,
				    stwuct stmmac_dma_cfg *dma_cfg,
				    dma_addw_t dma_wx_phy, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;
	u32 wxpbw = dma_cfg->wxpbw ?: dma_cfg->pbw;

	vawue = weadw(ioaddw + DMA_CHAN_WX_CONTWOW(dwmac4_addws, chan));
	vawue = vawue | (wxpbw << DMA_BUS_MODE_WPBW_SHIFT);
	wwitew(vawue, ioaddw + DMA_CHAN_WX_CONTWOW(dwmac4_addws, chan));

	if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) && wikewy(dma_cfg->eame))
		wwitew(uppew_32_bits(dma_wx_phy),
		       ioaddw + DMA_CHAN_WX_BASE_ADDW_HI(dwmac4_addws, chan));

	wwitew(wowew_32_bits(dma_wx_phy),
	       ioaddw + DMA_CHAN_WX_BASE_ADDW(dwmac4_addws, chan));
}

static void dwmac4_dma_init_tx_chan(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw,
				    stwuct stmmac_dma_cfg *dma_cfg,
				    dma_addw_t dma_tx_phy, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;
	u32 txpbw = dma_cfg->txpbw ?: dma_cfg->pbw;

	vawue = weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));
	vawue = vawue | (txpbw << DMA_BUS_MODE_PBW_SHIFT);

	/* Enabwe OSP to get best pewfowmance */
	vawue |= DMA_CONTWOW_OSP;

	wwitew(vawue, ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));

	if (IS_ENABWED(CONFIG_AWCH_DMA_ADDW_T_64BIT) && wikewy(dma_cfg->eame))
		wwitew(uppew_32_bits(dma_tx_phy),
		       ioaddw + DMA_CHAN_TX_BASE_ADDW_HI(dwmac4_addws, chan));

	wwitew(wowew_32_bits(dma_tx_phy),
	       ioaddw + DMA_CHAN_TX_BASE_ADDW(dwmac4_addws, chan));
}

static void dwmac4_dma_init_channew(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw,
				    stwuct stmmac_dma_cfg *dma_cfg, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;

	/* common channew contwow wegistew config */
	vawue = weadw(ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));
	if (dma_cfg->pbwx8)
		vawue = vawue | DMA_BUS_MODE_PBW;
	wwitew(vawue, ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));

	/* Mask intewwupts by wwiting to CSW7 */
	wwitew(DMA_CHAN_INTW_DEFAUWT_MASK,
	       ioaddw + DMA_CHAN_INTW_ENA(dwmac4_addws, chan));
}

static void dwmac410_dma_init_channew(stwuct stmmac_pwiv *pwiv,
				      void __iomem *ioaddw,
				      stwuct stmmac_dma_cfg *dma_cfg, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;

	/* common channew contwow wegistew config */
	vawue = weadw(ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));
	if (dma_cfg->pbwx8)
		vawue = vawue | DMA_BUS_MODE_PBW;

	wwitew(vawue, ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));

	/* Mask intewwupts by wwiting to CSW7 */
	wwitew(DMA_CHAN_INTW_DEFAUWT_MASK_4_10,
	       ioaddw + DMA_CHAN_INTW_ENA(dwmac4_addws, chan));
}

static void dwmac4_dma_init(void __iomem *ioaddw,
			    stwuct stmmac_dma_cfg *dma_cfg, int atds)
{
	u32 vawue = weadw(ioaddw + DMA_SYS_BUS_MODE);

	/* Set the Fixed buwst mode */
	if (dma_cfg->fixed_buwst)
		vawue |= DMA_SYS_BUS_FB;

	/* Mixed Buwst has no effect when fb is set */
	if (dma_cfg->mixed_buwst)
		vawue |= DMA_SYS_BUS_MB;

	if (dma_cfg->aaw)
		vawue |= DMA_SYS_BUS_AAW;

	if (dma_cfg->eame)
		vawue |= DMA_SYS_BUS_EAME;

	wwitew(vawue, ioaddw + DMA_SYS_BUS_MODE);

	vawue = weadw(ioaddw + DMA_BUS_MODE);

	if (dma_cfg->muwti_msi_en) {
		vawue &= ~DMA_BUS_MODE_INTM_MASK;
		vawue |= (DMA_BUS_MODE_INTM_MODE1 << DMA_BUS_MODE_INTM_SHIFT);
	}

	if (dma_cfg->dche)
		vawue |= DMA_BUS_MODE_DCHE;

	wwitew(vawue, ioaddw + DMA_BUS_MODE);

}

static void _dwmac4_dump_dma_wegs(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw, u32 channew,
				  u32 *weg_space)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	const stwuct dwmac4_addws *defauwt_addws = NUWW;

	/* Puwposewy save the wegistews in the "nowmaw" wayout, wegawdwess of
	 * pwatfowm modifications, to keep weg_space size constant
	 */
	weg_space[DMA_CHAN_CONTWOW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_TX_CONTWOW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_WX_CONTWOW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_WX_CONTWOW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_TX_BASE_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_TX_BASE_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_WX_BASE_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_WX_BASE_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_TX_END_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_TX_END_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_WX_END_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_WX_END_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_TX_WING_WEN(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_TX_WING_WEN(dwmac4_addws, channew));
	weg_space[DMA_CHAN_WX_WING_WEN(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_WX_WING_WEN(dwmac4_addws, channew));
	weg_space[DMA_CHAN_INTW_ENA(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_INTW_ENA(dwmac4_addws, channew));
	weg_space[DMA_CHAN_WX_WATCHDOG(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_WX_WATCHDOG(dwmac4_addws, channew));
	weg_space[DMA_CHAN_SWOT_CTWW_STATUS(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_SWOT_CTWW_STATUS(dwmac4_addws, channew));
	weg_space[DMA_CHAN_CUW_TX_DESC(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_CUW_TX_DESC(dwmac4_addws, channew));
	weg_space[DMA_CHAN_CUW_WX_DESC(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_CUW_WX_DESC(dwmac4_addws, channew));
	weg_space[DMA_CHAN_CUW_TX_BUF_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_CUW_TX_BUF_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_CUW_WX_BUF_ADDW(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_CUW_WX_BUF_ADDW(dwmac4_addws, channew));
	weg_space[DMA_CHAN_STATUS(defauwt_addws, channew) / 4] =
		weadw(ioaddw + DMA_CHAN_STATUS(dwmac4_addws, channew));
}

static void dwmac4_dump_dma_wegs(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 u32 *weg_space)
{
	int i;

	fow (i = 0; i < DMA_CHANNEW_NB_MAX; i++)
		_dwmac4_dump_dma_wegs(pwiv, ioaddw, i, weg_space);
}

static void dwmac4_wx_watchdog(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			       u32 wiwt, u32 queue)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;

	wwitew(wiwt, ioaddw + DMA_CHAN_WX_WATCHDOG(dwmac4_addws, queue));
}

static void dwmac4_dma_wx_chan_op_mode(stwuct stmmac_pwiv *pwiv,
				       void __iomem *ioaddw, int mode,
				       u32 channew, int fifosz, u8 qmode)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	unsigned int wqs = fifosz / 256 - 1;
	u32 mtw_wx_op;

	mtw_wx_op = weadw(ioaddw + MTW_CHAN_WX_OP_MODE(dwmac4_addws, channew));

	if (mode == SF_DMA_MODE) {
		pw_debug("GMAC: enabwe WX stowe and fowwawd mode\n");
		mtw_wx_op |= MTW_OP_MODE_WSF;
	} ewse {
		pw_debug("GMAC: disabwe WX SF mode (thweshowd %d)\n", mode);
		mtw_wx_op &= ~MTW_OP_MODE_WSF;
		mtw_wx_op &= MTW_OP_MODE_WTC_MASK;
		if (mode <= 32)
			mtw_wx_op |= MTW_OP_MODE_WTC_32;
		ewse if (mode <= 64)
			mtw_wx_op |= MTW_OP_MODE_WTC_64;
		ewse if (mode <= 96)
			mtw_wx_op |= MTW_OP_MODE_WTC_96;
		ewse
			mtw_wx_op |= MTW_OP_MODE_WTC_128;
	}

	mtw_wx_op &= ~MTW_OP_MODE_WQS_MASK;
	mtw_wx_op |= wqs << MTW_OP_MODE_WQS_SHIFT;

	/* Enabwe fwow contwow onwy if each channew gets 4 KiB ow mowe FIFO and
	 * onwy if channew is not an AVB channew.
	 */
	if ((fifosz >= 4096) && (qmode != MTW_QUEUE_AVB)) {
		unsigned int wfd, wfa;

		mtw_wx_op |= MTW_OP_MODE_EHFC;

		/* Set Thweshowd fow Activating Fwow Contwow to min 2 fwames,
		 * i.e. 1500 * 2 = 3000 bytes.
		 *
		 * Set Thweshowd fow Deactivating Fwow Contwow to min 1 fwame,
		 * i.e. 1500 bytes.
		 */
		switch (fifosz) {
		case 4096:
			/* This viowates the above fowmuwa because of FIFO size
			 * wimit thewefowe ovewfwow may occuw in spite of this.
			 */
			wfd = 0x03; /* Fuww-2.5K */
			wfa = 0x01; /* Fuww-1.5K */
			bweak;

		defauwt:
			wfd = 0x07; /* Fuww-4.5K */
			wfa = 0x04; /* Fuww-3K */
			bweak;
		}

		mtw_wx_op &= ~MTW_OP_MODE_WFD_MASK;
		mtw_wx_op |= wfd << MTW_OP_MODE_WFD_SHIFT;

		mtw_wx_op &= ~MTW_OP_MODE_WFA_MASK;
		mtw_wx_op |= wfa << MTW_OP_MODE_WFA_SHIFT;
	}

	wwitew(mtw_wx_op, ioaddw + MTW_CHAN_WX_OP_MODE(dwmac4_addws, channew));
}

static void dwmac4_dma_tx_chan_op_mode(stwuct stmmac_pwiv *pwiv,
				       void __iomem *ioaddw, int mode,
				       u32 channew, int fifosz, u8 qmode)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 mtw_tx_op = weadw(ioaddw + MTW_CHAN_TX_OP_MODE(dwmac4_addws,
							   channew));
	unsigned int tqs = fifosz / 256 - 1;

	if (mode == SF_DMA_MODE) {
		pw_debug("GMAC: enabwe TX stowe and fowwawd mode\n");
		/* Twansmit COE type 2 cannot be done in cut-thwough mode. */
		mtw_tx_op |= MTW_OP_MODE_TSF;
	} ewse {
		pw_debug("GMAC: disabwing TX SF (thweshowd %d)\n", mode);
		mtw_tx_op &= ~MTW_OP_MODE_TSF;
		mtw_tx_op &= MTW_OP_MODE_TTC_MASK;
		/* Set the twansmit thweshowd */
		if (mode <= 32)
			mtw_tx_op |= MTW_OP_MODE_TTC_32;
		ewse if (mode <= 64)
			mtw_tx_op |= MTW_OP_MODE_TTC_64;
		ewse if (mode <= 96)
			mtw_tx_op |= MTW_OP_MODE_TTC_96;
		ewse if (mode <= 128)
			mtw_tx_op |= MTW_OP_MODE_TTC_128;
		ewse if (mode <= 192)
			mtw_tx_op |= MTW_OP_MODE_TTC_192;
		ewse if (mode <= 256)
			mtw_tx_op |= MTW_OP_MODE_TTC_256;
		ewse if (mode <= 384)
			mtw_tx_op |= MTW_OP_MODE_TTC_384;
		ewse
			mtw_tx_op |= MTW_OP_MODE_TTC_512;
	}
	/* Fow an IP with DWC_EQOS_NUM_TXQ == 1, the fiewds TXQEN and TQS awe WO
	 * with weset vawues: TXQEN on, TQS == DWC_EQOS_TXFIFO_SIZE.
	 * Fow an IP with DWC_EQOS_NUM_TXQ > 1, the fiewds TXQEN and TQS awe W/W
	 * with weset vawues: TXQEN off, TQS 256 bytes.
	 *
	 * TXQEN must be wwitten fow muwti-channew opewation and TQS must
	 * wefwect the avaiwabwe fifo size pew queue (totaw fifo size / numbew
	 * of enabwed queues).
	 */
	mtw_tx_op &= ~MTW_OP_MODE_TXQEN_MASK;
	if (qmode != MTW_QUEUE_AVB)
		mtw_tx_op |= MTW_OP_MODE_TXQEN;
	ewse
		mtw_tx_op |= MTW_OP_MODE_TXQEN_AV;
	mtw_tx_op &= ~MTW_OP_MODE_TQS_MASK;
	mtw_tx_op |= tqs << MTW_OP_MODE_TQS_SHIFT;

	wwitew(mtw_tx_op, ioaddw +  MTW_CHAN_TX_OP_MODE(dwmac4_addws, channew));
}

static int dwmac4_get_hw_featuwe(void __iomem *ioaddw,
				 stwuct dma_featuwes *dma_cap)
{
	u32 hw_cap = weadw(ioaddw + GMAC_HW_FEATUWE0);

	/*  MAC HW featuwe0 */
	dma_cap->mbps_10_100 = (hw_cap & GMAC_HW_FEAT_MIISEW);
	dma_cap->mbps_1000 = (hw_cap & GMAC_HW_FEAT_GMIISEW) >> 1;
	dma_cap->hawf_dupwex = (hw_cap & GMAC_HW_FEAT_HDSEW) >> 2;
	dma_cap->vwhash = (hw_cap & GMAC_HW_FEAT_VWHASH) >> 4;
	dma_cap->muwti_addw = (hw_cap & GMAC_HW_FEAT_ADDMAC) >> 18;
	dma_cap->pcs = (hw_cap & GMAC_HW_FEAT_PCSSEW) >> 3;
	dma_cap->sma_mdio = (hw_cap & GMAC_HW_FEAT_SMASEW) >> 5;
	dma_cap->pmt_wemote_wake_up = (hw_cap & GMAC_HW_FEAT_WWKSEW) >> 6;
	dma_cap->pmt_magic_fwame = (hw_cap & GMAC_HW_FEAT_MGKSEW) >> 7;
	/* MMC */
	dma_cap->wmon = (hw_cap & GMAC_HW_FEAT_MMCSEW) >> 8;
	/* IEEE 1588-2008 */
	dma_cap->atime_stamp = (hw_cap & GMAC_HW_FEAT_TSSEW) >> 12;
	/* 802.3az - Enewgy-Efficient Ethewnet (EEE) */
	dma_cap->eee = (hw_cap & GMAC_HW_FEAT_EEESEW) >> 13;
	/* TX and WX csum */
	dma_cap->tx_coe = (hw_cap & GMAC_HW_FEAT_TXCOSEW) >> 14;
	dma_cap->wx_coe =  (hw_cap & GMAC_HW_FEAT_WXCOESEW) >> 16;
	dma_cap->vwins = (hw_cap & GMAC_HW_FEAT_SAVWANINS) >> 27;
	dma_cap->awpoffsew = (hw_cap & GMAC_HW_FEAT_AWPOFFSEW) >> 9;

	/* MAC HW featuwe1 */
	hw_cap = weadw(ioaddw + GMAC_HW_FEATUWE1);
	dma_cap->w3w4fnum = (hw_cap & GMAC_HW_FEAT_W3W4FNUM) >> 27;
	dma_cap->hash_tb_sz = (hw_cap & GMAC_HW_HASH_TB_SZ) >> 24;
	dma_cap->av = (hw_cap & GMAC_HW_FEAT_AVSEW) >> 20;
	dma_cap->tsoen = (hw_cap & GMAC_HW_TSOEN) >> 18;
	dma_cap->sphen = (hw_cap & GMAC_HW_FEAT_SPHEN) >> 17;

	dma_cap->addw64 = (hw_cap & GMAC_HW_ADDW64) >> 14;
	switch (dma_cap->addw64) {
	case 0:
		dma_cap->addw64 = 32;
		bweak;
	case 1:
		dma_cap->addw64 = 40;
		bweak;
	case 2:
		dma_cap->addw64 = 48;
		bweak;
	defauwt:
		dma_cap->addw64 = 32;
		bweak;
	}

	/* WX and TX FIFO sizes awe encoded as wog2(n / 128). Undo that by
	 * shifting and stowe the sizes in bytes.
	 */
	dma_cap->tx_fifo_size = 128 << ((hw_cap & GMAC_HW_TXFIFOSIZE) >> 6);
	dma_cap->wx_fifo_size = 128 << ((hw_cap & GMAC_HW_WXFIFOSIZE) >> 0);
	/* MAC HW featuwe2 */
	hw_cap = weadw(ioaddw + GMAC_HW_FEATUWE2);
	/* TX and WX numbew of channews */
	dma_cap->numbew_wx_channew =
		((hw_cap & GMAC_HW_FEAT_WXCHCNT) >> 12) + 1;
	dma_cap->numbew_tx_channew =
		((hw_cap & GMAC_HW_FEAT_TXCHCNT) >> 18) + 1;
	/* TX and WX numbew of queues */
	dma_cap->numbew_wx_queues =
		((hw_cap & GMAC_HW_FEAT_WXQCNT) >> 0) + 1;
	dma_cap->numbew_tx_queues =
		((hw_cap & GMAC_HW_FEAT_TXQCNT) >> 6) + 1;
	/* PPS output */
	dma_cap->pps_out_num = (hw_cap & GMAC_HW_FEAT_PPSOUTNUM) >> 24;

	/* IEEE 1588-2002 */
	dma_cap->time_stamp = 0;
	/* Numbew of Auxiwiawy Snapshot Inputs */
	dma_cap->aux_snapshot_n = (hw_cap & GMAC_HW_FEAT_AUXSNAPNUM) >> 28;

	/* MAC HW featuwe3 */
	hw_cap = weadw(ioaddw + GMAC_HW_FEATUWE3);

	/* 5.10 Featuwes */
	dma_cap->asp = (hw_cap & GMAC_HW_FEAT_ASP) >> 28;
	dma_cap->tbssew = (hw_cap & GMAC_HW_FEAT_TBSSEW) >> 27;
	dma_cap->fpesew = (hw_cap & GMAC_HW_FEAT_FPESEW) >> 26;
	dma_cap->estwid = (hw_cap & GMAC_HW_FEAT_ESTWID) >> 20;
	dma_cap->estdep = (hw_cap & GMAC_HW_FEAT_ESTDEP) >> 17;
	dma_cap->estsew = (hw_cap & GMAC_HW_FEAT_ESTSEW) >> 16;
	dma_cap->fwpes = (hw_cap & GMAC_HW_FEAT_FWPES) >> 13;
	dma_cap->fwpbs = (hw_cap & GMAC_HW_FEAT_FWPBS) >> 11;
	dma_cap->fwpsew = (hw_cap & GMAC_HW_FEAT_FWPSEW) >> 10;
	dma_cap->dvwan = (hw_cap & GMAC_HW_FEAT_DVWAN) >> 5;

	wetuwn 0;
}

/* Enabwe/disabwe TSO featuwe and set MSS */
static void dwmac4_enabwe_tso(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			      boow en, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue;

	if (en) {
		/* enabwe TSO */
		vawue = weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));
		wwitew(vawue | DMA_CONTWOW_TSE,
		       ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));
	} ewse {
		/* enabwe TSO */
		vawue = weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));
		wwitew(vawue & ~DMA_CONTWOW_TSE,
		       ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));
	}
}

static void dwmac4_qmode(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 u32 channew, u8 qmode)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 mtw_tx_op = weadw(ioaddw + MTW_CHAN_TX_OP_MODE(dwmac4_addws,
							   channew));

	mtw_tx_op &= ~MTW_OP_MODE_TXQEN_MASK;
	if (qmode != MTW_QUEUE_AVB)
		mtw_tx_op |= MTW_OP_MODE_TXQEN;
	ewse
		mtw_tx_op |= MTW_OP_MODE_TXQEN_AV;

	wwitew(mtw_tx_op, ioaddw +  MTW_CHAN_TX_OP_MODE(dwmac4_addws, channew));
}

static void dwmac4_set_bfsize(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			      int bfsize, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue = weadw(ioaddw + DMA_CHAN_WX_CONTWOW(dwmac4_addws, chan));

	vawue &= ~DMA_WBSZ_MASK;
	vawue |= (bfsize << DMA_WBSZ_SHIFT) & DMA_WBSZ_MASK;

	wwitew(vawue, ioaddw + DMA_CHAN_WX_CONTWOW(dwmac4_addws, chan));
}

static void dwmac4_enabwe_sph(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			      boow en, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue = weadw(ioaddw + GMAC_EXT_CONFIG);

	vawue &= ~GMAC_CONFIG_HDSMS;
	vawue |= GMAC_CONFIG_HDSMS_256; /* Segment max 256 bytes */
	wwitew(vawue, ioaddw + GMAC_EXT_CONFIG);

	vawue = weadw(ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));
	if (en)
		vawue |= DMA_CONTWOW_SPH;
	ewse
		vawue &= ~DMA_CONTWOW_SPH;
	wwitew(vawue, ioaddw + DMA_CHAN_CONTWOW(dwmac4_addws, chan));
}

static int dwmac4_enabwe_tbs(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			     boow en, u32 chan)
{
	const stwuct dwmac4_addws *dwmac4_addws = pwiv->pwat->dwmac4_addws;
	u32 vawue = weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));

	if (en)
		vawue |= DMA_CONTWOW_EDSE;
	ewse
		vawue &= ~DMA_CONTWOW_EDSE;

	wwitew(vawue, ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws, chan));

	vawue = weadw(ioaddw + DMA_CHAN_TX_CONTWOW(dwmac4_addws,
						   chan)) & DMA_CONTWOW_EDSE;
	if (en && !vawue)
		wetuwn -EIO;

	wwitew(DMA_TBS_DEF_FTOS, ioaddw + DMA_TBS_CTWW);
	wetuwn 0;
}

const stwuct stmmac_dma_ops dwmac4_dma_ops = {
	.weset = dwmac4_dma_weset,
	.init = dwmac4_dma_init,
	.init_chan = dwmac4_dma_init_channew,
	.init_wx_chan = dwmac4_dma_init_wx_chan,
	.init_tx_chan = dwmac4_dma_init_tx_chan,
	.axi = dwmac4_dma_axi,
	.dump_wegs = dwmac4_dump_dma_wegs,
	.dma_wx_mode = dwmac4_dma_wx_chan_op_mode,
	.dma_tx_mode = dwmac4_dma_tx_chan_op_mode,
	.enabwe_dma_iwq = dwmac4_enabwe_dma_iwq,
	.disabwe_dma_iwq = dwmac4_disabwe_dma_iwq,
	.stawt_tx = dwmac4_dma_stawt_tx,
	.stop_tx = dwmac4_dma_stop_tx,
	.stawt_wx = dwmac4_dma_stawt_wx,
	.stop_wx = dwmac4_dma_stop_wx,
	.dma_intewwupt = dwmac4_dma_intewwupt,
	.get_hw_featuwe = dwmac4_get_hw_featuwe,
	.wx_watchdog = dwmac4_wx_watchdog,
	.set_wx_wing_wen = dwmac4_set_wx_wing_wen,
	.set_tx_wing_wen = dwmac4_set_tx_wing_wen,
	.set_wx_taiw_ptw = dwmac4_set_wx_taiw_ptw,
	.set_tx_taiw_ptw = dwmac4_set_tx_taiw_ptw,
	.enabwe_tso = dwmac4_enabwe_tso,
	.qmode = dwmac4_qmode,
	.set_bfsize = dwmac4_set_bfsize,
	.enabwe_sph = dwmac4_enabwe_sph,
};

const stwuct stmmac_dma_ops dwmac410_dma_ops = {
	.weset = dwmac4_dma_weset,
	.init = dwmac4_dma_init,
	.init_chan = dwmac410_dma_init_channew,
	.init_wx_chan = dwmac4_dma_init_wx_chan,
	.init_tx_chan = dwmac4_dma_init_tx_chan,
	.axi = dwmac4_dma_axi,
	.dump_wegs = dwmac4_dump_dma_wegs,
	.dma_wx_mode = dwmac4_dma_wx_chan_op_mode,
	.dma_tx_mode = dwmac4_dma_tx_chan_op_mode,
	.enabwe_dma_iwq = dwmac410_enabwe_dma_iwq,
	.disabwe_dma_iwq = dwmac4_disabwe_dma_iwq,
	.stawt_tx = dwmac4_dma_stawt_tx,
	.stop_tx = dwmac4_dma_stop_tx,
	.stawt_wx = dwmac4_dma_stawt_wx,
	.stop_wx = dwmac4_dma_stop_wx,
	.dma_intewwupt = dwmac4_dma_intewwupt,
	.get_hw_featuwe = dwmac4_get_hw_featuwe,
	.wx_watchdog = dwmac4_wx_watchdog,
	.set_wx_wing_wen = dwmac4_set_wx_wing_wen,
	.set_tx_wing_wen = dwmac4_set_tx_wing_wen,
	.set_wx_taiw_ptw = dwmac4_set_wx_taiw_ptw,
	.set_tx_taiw_ptw = dwmac4_set_tx_taiw_ptw,
	.enabwe_tso = dwmac4_enabwe_tso,
	.qmode = dwmac4_qmode,
	.set_bfsize = dwmac4_set_bfsize,
	.enabwe_sph = dwmac4_enabwe_sph,
	.enabwe_tbs = dwmac4_enabwe_tbs,
};
