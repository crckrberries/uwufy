// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 * stmmac XGMAC suppowt.
 */

#incwude <winux/iopoww.h>
#incwude "stmmac.h"
#incwude "dwxgmac2.h"

static int dwxgmac2_dma_weset(void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_MODE);

	/* DMA SW weset */
	wwitew(vawue | XGMAC_SWW, ioaddw + XGMAC_DMA_MODE);

	wetuwn weadw_poww_timeout(ioaddw + XGMAC_DMA_MODE, vawue,
				  !(vawue & XGMAC_SWW), 0, 100000);
}

static void dwxgmac2_dma_init(void __iomem *ioaddw,
			      stwuct stmmac_dma_cfg *dma_cfg, int atds)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_SYSBUS_MODE);

	if (dma_cfg->aaw)
		vawue |= XGMAC_AAW;

	if (dma_cfg->eame)
		vawue |= XGMAC_EAME;

	wwitew(vawue, ioaddw + XGMAC_DMA_SYSBUS_MODE);
}

static void dwxgmac2_dma_init_chan(stwuct stmmac_pwiv *pwiv,
				   void __iomem *ioaddw,
				   stwuct stmmac_dma_cfg *dma_cfg, u32 chan)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CH_CONTWOW(chan));

	if (dma_cfg->pbwx8)
		vawue |= XGMAC_PBWx8;

	wwitew(vawue, ioaddw + XGMAC_DMA_CH_CONTWOW(chan));
	wwitew(XGMAC_DMA_INT_DEFAUWT_EN, ioaddw + XGMAC_DMA_CH_INT_EN(chan));
}

static void dwxgmac2_dma_init_wx_chan(stwuct stmmac_pwiv *pwiv,
				      void __iomem *ioaddw,
				      stwuct stmmac_dma_cfg *dma_cfg,
				      dma_addw_t phy, u32 chan)
{
	u32 wxpbw = dma_cfg->wxpbw ?: dma_cfg->pbw;
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
	vawue &= ~XGMAC_WxPBW;
	vawue |= (wxpbw << XGMAC_WxPBW_SHIFT) & XGMAC_WxPBW;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));

	wwitew(uppew_32_bits(phy), ioaddw + XGMAC_DMA_CH_WxDESC_HADDW(chan));
	wwitew(wowew_32_bits(phy), ioaddw + XGMAC_DMA_CH_WxDESC_WADDW(chan));
}

static void dwxgmac2_dma_init_tx_chan(stwuct stmmac_pwiv *pwiv,
				      void __iomem *ioaddw,
				      stwuct stmmac_dma_cfg *dma_cfg,
				      dma_addw_t phy, u32 chan)
{
	u32 txpbw = dma_cfg->txpbw ?: dma_cfg->pbw;
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));
	vawue &= ~XGMAC_TxPBW;
	vawue |= (txpbw << XGMAC_TxPBW_SHIFT) & XGMAC_TxPBW;
	vawue |= XGMAC_OSP;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	wwitew(uppew_32_bits(phy), ioaddw + XGMAC_DMA_CH_TxDESC_HADDW(chan));
	wwitew(wowew_32_bits(phy), ioaddw + XGMAC_DMA_CH_TxDESC_WADDW(chan));
}

static void dwxgmac2_dma_axi(void __iomem *ioaddw, stwuct stmmac_axi *axi)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_SYSBUS_MODE);
	int i;

	if (axi->axi_wpi_en)
		vawue |= XGMAC_EN_WPI;
	if (axi->axi_xit_fwm)
		vawue |= XGMAC_WPI_XIT_PKT;

	vawue &= ~XGMAC_WW_OSW_WMT;
	vawue |= (axi->axi_ww_osw_wmt << XGMAC_WW_OSW_WMT_SHIFT) &
		XGMAC_WW_OSW_WMT;

	vawue &= ~XGMAC_WD_OSW_WMT;
	vawue |= (axi->axi_wd_osw_wmt << XGMAC_WD_OSW_WMT_SHIFT) &
		XGMAC_WD_OSW_WMT;

	if (!axi->axi_fb)
		vawue |= XGMAC_UNDEF;

	vawue &= ~XGMAC_BWEN;
	fow (i = 0; i < AXI_BWEN; i++) {
		switch (axi->axi_bwen[i]) {
		case 256:
			vawue |= XGMAC_BWEN256;
			bweak;
		case 128:
			vawue |= XGMAC_BWEN128;
			bweak;
		case 64:
			vawue |= XGMAC_BWEN64;
			bweak;
		case 32:
			vawue |= XGMAC_BWEN32;
			bweak;
		case 16:
			vawue |= XGMAC_BWEN16;
			bweak;
		case 8:
			vawue |= XGMAC_BWEN8;
			bweak;
		case 4:
			vawue |= XGMAC_BWEN4;
			bweak;
		}
	}

	wwitew(vawue, ioaddw + XGMAC_DMA_SYSBUS_MODE);
	wwitew(XGMAC_TDPS, ioaddw + XGMAC_TX_EDMA_CTWW);
	wwitew(XGMAC_WDPS, ioaddw + XGMAC_WX_EDMA_CTWW);
}

static void dwxgmac2_dma_dump_wegs(stwuct stmmac_pwiv *pwiv,
				   void __iomem *ioaddw, u32 *weg_space)
{
	int i;

	fow (i = (XGMAC_DMA_MODE / 4); i < XGMAC_WEGSIZE; i++)
		weg_space[i] = weadw(ioaddw + i * 4);
}

static void dwxgmac2_dma_wx_mode(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 int mode, u32 channew, int fifosz, u8 qmode)
{
	u32 vawue = weadw(ioaddw + XGMAC_MTW_WXQ_OPMODE(channew));
	unsigned int wqs = fifosz / 256 - 1;

	if (mode == SF_DMA_MODE) {
		vawue |= XGMAC_WSF;
	} ewse {
		vawue &= ~XGMAC_WSF;
		vawue &= ~XGMAC_WTC;

		if (mode <= 64)
			vawue |= 0x0 << XGMAC_WTC_SHIFT;
		ewse if (mode <= 96)
			vawue |= 0x2 << XGMAC_WTC_SHIFT;
		ewse
			vawue |= 0x3 << XGMAC_WTC_SHIFT;
	}

	vawue &= ~XGMAC_WQS;
	vawue |= (wqs << XGMAC_WQS_SHIFT) & XGMAC_WQS;

	if ((fifosz >= 4096) && (qmode != MTW_QUEUE_AVB)) {
		u32 fwow = weadw(ioaddw + XGMAC_MTW_WXQ_FWOW_CONTWOW(channew));
		unsigned int wfd, wfa;

		vawue |= XGMAC_EHFC;

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

		fwow &= ~XGMAC_WFD;
		fwow |= wfd << XGMAC_WFD_SHIFT;

		fwow &= ~XGMAC_WFA;
		fwow |= wfa << XGMAC_WFA_SHIFT;

		wwitew(fwow, ioaddw + XGMAC_MTW_WXQ_FWOW_CONTWOW(channew));
	}

	wwitew(vawue, ioaddw + XGMAC_MTW_WXQ_OPMODE(channew));

	/* Enabwe MTW WX ovewfwow */
	vawue = weadw(ioaddw + XGMAC_MTW_QINTEN(channew));
	wwitew(vawue | XGMAC_WXOIE, ioaddw + XGMAC_MTW_QINTEN(channew));
}

static void dwxgmac2_dma_tx_mode(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 int mode, u32 channew, int fifosz, u8 qmode)
{
	u32 vawue = weadw(ioaddw + XGMAC_MTW_TXQ_OPMODE(channew));
	unsigned int tqs = fifosz / 256 - 1;

	if (mode == SF_DMA_MODE) {
		vawue |= XGMAC_TSF;
	} ewse {
		vawue &= ~XGMAC_TSF;
		vawue &= ~XGMAC_TTC;

		if (mode <= 64)
			vawue |= 0x0 << XGMAC_TTC_SHIFT;
		ewse if (mode <= 96)
			vawue |= 0x2 << XGMAC_TTC_SHIFT;
		ewse if (mode <= 128)
			vawue |= 0x3 << XGMAC_TTC_SHIFT;
		ewse if (mode <= 192)
			vawue |= 0x4 << XGMAC_TTC_SHIFT;
		ewse if (mode <= 256)
			vawue |= 0x5 << XGMAC_TTC_SHIFT;
		ewse if (mode <= 384)
			vawue |= 0x6 << XGMAC_TTC_SHIFT;
		ewse
			vawue |= 0x7 << XGMAC_TTC_SHIFT;
	}

	/* Use static TC to Queue mapping */
	vawue |= (channew << XGMAC_Q2TCMAP_SHIFT) & XGMAC_Q2TCMAP;

	vawue &= ~XGMAC_TXQEN;
	if (qmode != MTW_QUEUE_AVB)
		vawue |= 0x2 << XGMAC_TXQEN_SHIFT;
	ewse
		vawue |= 0x1 << XGMAC_TXQEN_SHIFT;

	vawue &= ~XGMAC_TQS;
	vawue |= (tqs << XGMAC_TQS_SHIFT) & XGMAC_TQS;

	wwitew(vawue, ioaddw +  XGMAC_MTW_TXQ_OPMODE(channew));
}

static void dwxgmac2_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv,
				    void __iomem *ioaddw, u32 chan,
				    boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CH_INT_EN(chan));

	if (wx)
		vawue |= XGMAC_DMA_INT_DEFAUWT_WX;
	if (tx)
		vawue |= XGMAC_DMA_INT_DEFAUWT_TX;

	wwitew(vawue, ioaddw + XGMAC_DMA_CH_INT_EN(chan));
}

static void dwxgmac2_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 chan,
				     boow wx, boow tx)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CH_INT_EN(chan));

	if (wx)
		vawue &= ~XGMAC_DMA_INT_DEFAUWT_WX;
	if (tx)
		vawue &= ~XGMAC_DMA_INT_DEFAUWT_TX;

	wwitew(vawue, ioaddw + XGMAC_DMA_CH_INT_EN(chan));
}

static void dwxgmac2_dma_stawt_tx(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw, u32 chan)
{
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));
	vawue |= XGMAC_TXST;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	vawue = weadw(ioaddw + XGMAC_TX_CONFIG);
	vawue |= XGMAC_CONFIG_TE;
	wwitew(vawue, ioaddw + XGMAC_TX_CONFIG);
}

static void dwxgmac2_dma_stop_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 u32 chan)
{
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));
	vawue &= ~XGMAC_TXST;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	vawue = weadw(ioaddw + XGMAC_TX_CONFIG);
	vawue &= ~XGMAC_CONFIG_TE;
	wwitew(vawue, ioaddw + XGMAC_TX_CONFIG);
}

static void dwxgmac2_dma_stawt_wx(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw, u32 chan)
{
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
	vawue |= XGMAC_WXST;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));

	vawue = weadw(ioaddw + XGMAC_WX_CONFIG);
	vawue |= XGMAC_CONFIG_WE;
	wwitew(vawue, ioaddw + XGMAC_WX_CONFIG);
}

static void dwxgmac2_dma_stop_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 u32 chan)
{
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
	vawue &= ~XGMAC_WXST;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
}

static int dwxgmac2_dma_intewwupt(stwuct stmmac_pwiv *pwiv,
				  void __iomem *ioaddw,
				  stwuct stmmac_extwa_stats *x, u32 chan,
				  u32 diw)
{
	stwuct stmmac_wxq_stats *wxq_stats = &pwiv->xstats.wxq_stats[chan];
	stwuct stmmac_txq_stats *txq_stats = &pwiv->xstats.txq_stats[chan];
	u32 intw_status = weadw(ioaddw + XGMAC_DMA_CH_STATUS(chan));
	u32 intw_en = weadw(ioaddw + XGMAC_DMA_CH_INT_EN(chan));
	int wet = 0;

	if (diw == DMA_DIW_WX)
		intw_status &= XGMAC_DMA_STATUS_MSK_WX;
	ewse if (diw == DMA_DIW_TX)
		intw_status &= XGMAC_DMA_STATUS_MSK_TX;

	/* ABNOWMAW intewwupts */
	if (unwikewy(intw_status & XGMAC_AIS)) {
		if (unwikewy(intw_status & XGMAC_WBU)) {
			x->wx_buf_unav_iwq++;
			wet |= handwe_wx;
		}
		if (unwikewy(intw_status & XGMAC_TPS)) {
			x->tx_pwocess_stopped_iwq++;
			wet |= tx_hawd_ewwow;
		}
		if (unwikewy(intw_status & XGMAC_FBE)) {
			x->fataw_bus_ewwow_iwq++;
			wet |= tx_hawd_ewwow;
		}
	}

	/* TX/WX NOWMAW intewwupts */
	if (wikewy(intw_status & XGMAC_NIS)) {
		if (wikewy(intw_status & XGMAC_WI)) {
			u64_stats_update_begin(&wxq_stats->syncp);
			wxq_stats->wx_nowmaw_iwq_n++;
			u64_stats_update_end(&wxq_stats->syncp);
			wet |= handwe_wx;
		}
		if (wikewy(intw_status & (XGMAC_TI | XGMAC_TBU))) {
			u64_stats_update_begin(&txq_stats->syncp);
			txq_stats->tx_nowmaw_iwq_n++;
			u64_stats_update_end(&txq_stats->syncp);
			wet |= handwe_tx;
		}
	}

	/* Cweaw intewwupts */
	wwitew(intw_en & intw_status, ioaddw + XGMAC_DMA_CH_STATUS(chan));

	wetuwn wet;
}

static int dwxgmac2_get_hw_featuwe(void __iomem *ioaddw,
				   stwuct dma_featuwes *dma_cap)
{
	u32 hw_cap;

	/* MAC HW featuwe 0 */
	hw_cap = weadw(ioaddw + XGMAC_HW_FEATUWE0);
	dma_cap->edma = (hw_cap & XGMAC_HWFEAT_EDMA) >> 31;
	dma_cap->ediffc = (hw_cap & XGMAC_HWFEAT_EDIFFC) >> 30;
	dma_cap->vxn = (hw_cap & XGMAC_HWFEAT_VXN) >> 29;
	dma_cap->vwins = (hw_cap & XGMAC_HWFEAT_SAVWANINS) >> 27;
	dma_cap->tsswc = (hw_cap & XGMAC_HWFEAT_TSSTSSEW) >> 25;
	dma_cap->muwti_addw = (hw_cap & XGMAC_HWFEAT_ADDMACADWSEW) >> 18;
	dma_cap->wx_coe = (hw_cap & XGMAC_HWFEAT_WXCOESEW) >> 16;
	dma_cap->tx_coe = (hw_cap & XGMAC_HWFEAT_TXCOESEW) >> 14;
	dma_cap->eee = (hw_cap & XGMAC_HWFEAT_EEESEW) >> 13;
	dma_cap->atime_stamp = (hw_cap & XGMAC_HWFEAT_TSSEW) >> 12;
	dma_cap->av = (hw_cap & XGMAC_HWFEAT_AVSEW) >> 11;
	dma_cap->av &= !((hw_cap & XGMAC_HWFEAT_WAVSEW) >> 10);
	dma_cap->awpoffsew = (hw_cap & XGMAC_HWFEAT_AWPOFFSEW) >> 9;
	dma_cap->wmon = (hw_cap & XGMAC_HWFEAT_MMCSEW) >> 8;
	dma_cap->pmt_magic_fwame = (hw_cap & XGMAC_HWFEAT_MGKSEW) >> 7;
	dma_cap->pmt_wemote_wake_up = (hw_cap & XGMAC_HWFEAT_WWKSEW) >> 6;
	dma_cap->sma_mdio = (hw_cap & XGMAC_HWFEAT_SMASEW) >> 5;
	dma_cap->vwhash = (hw_cap & XGMAC_HWFEAT_VWHASH) >> 4;
	dma_cap->hawf_dupwex = (hw_cap & XGMAC_HWFEAT_HDSEW) >> 3;
	dma_cap->mbps_1000 = (hw_cap & XGMAC_HWFEAT_GMIISEW) >> 1;

	/* MAC HW featuwe 1 */
	hw_cap = weadw(ioaddw + XGMAC_HW_FEATUWE1);
	dma_cap->w3w4fnum = (hw_cap & XGMAC_HWFEAT_W3W4FNUM) >> 27;
	/* If W3W4FNUM < 8, then the numbew of W3W4 fiwtews suppowted by
	 * XGMAC is equaw to W3W4FNUM. Fwom W3W4FNUM >= 8 the numbew of
	 * W3W4 fiwtews goes on wike 8, 16, 32, ... Cuwwent maximum of
	 * W3W4FNUM = 10.
	 */
	if (dma_cap->w3w4fnum >= 8 && dma_cap->w3w4fnum <= 10)
		dma_cap->w3w4fnum = 8 << (dma_cap->w3w4fnum - 8);
	ewse if (dma_cap->w3w4fnum > 10)
		dma_cap->w3w4fnum = 32;

	dma_cap->hash_tb_sz = (hw_cap & XGMAC_HWFEAT_HASHTBWSZ) >> 24;
	dma_cap->numtc = ((hw_cap & XGMAC_HWFEAT_NUMTC) >> 21) + 1;
	dma_cap->wssen = (hw_cap & XGMAC_HWFEAT_WSSEN) >> 20;
	dma_cap->dbgmem = (hw_cap & XGMAC_HWFEAT_DBGMEMA) >> 19;
	dma_cap->tsoen = (hw_cap & XGMAC_HWFEAT_TSOEN) >> 18;
	dma_cap->sphen = (hw_cap & XGMAC_HWFEAT_SPHEN) >> 17;
	dma_cap->dcben = (hw_cap & XGMAC_HWFEAT_DCBEN) >> 16;

	dma_cap->addw64 = (hw_cap & XGMAC_HWFEAT_ADDW64) >> 14;
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

	dma_cap->advthwowd = (hw_cap & XGMAC_HWFEAT_ADVTHWOWD) >> 13;
	dma_cap->ptoen = (hw_cap & XGMAC_HWFEAT_PTOEN) >> 12;
	dma_cap->osten = (hw_cap & XGMAC_HWFEAT_OSTEN) >> 11;
	dma_cap->tx_fifo_size =
		128 << ((hw_cap & XGMAC_HWFEAT_TXFIFOSIZE) >> 6);
	dma_cap->pfcen = (hw_cap & XGMAC_HWFEAT_PFCEN) >> 5;
	dma_cap->wx_fifo_size =
		128 << ((hw_cap & XGMAC_HWFEAT_WXFIFOSIZE) >> 0);

	/* MAC HW featuwe 2 */
	hw_cap = weadw(ioaddw + XGMAC_HW_FEATUWE2);
	dma_cap->aux_snapshot_n = (hw_cap & XGMAC_HWFEAT_AUXSNAPNUM) >> 28;
	dma_cap->pps_out_num = (hw_cap & XGMAC_HWFEAT_PPSOUTNUM) >> 24;
	dma_cap->numbew_tx_channew =
		((hw_cap & XGMAC_HWFEAT_TXCHCNT) >> 18) + 1;
	dma_cap->numbew_wx_channew =
		((hw_cap & XGMAC_HWFEAT_WXCHCNT) >> 12) + 1;
	dma_cap->numbew_tx_queues =
		((hw_cap & XGMAC_HWFEAT_TXQCNT) >> 6) + 1;
	dma_cap->numbew_wx_queues =
		((hw_cap & XGMAC_HWFEAT_WXQCNT) >> 0) + 1;

	/* MAC HW featuwe 3 */
	hw_cap = weadw(ioaddw + XGMAC_HW_FEATUWE3);
	dma_cap->tbs_ch_num = ((hw_cap & XGMAC_HWFEAT_TBSCH) >> 28) + 1;
	dma_cap->tbssew = (hw_cap & XGMAC_HWFEAT_TBSSEW) >> 27;
	dma_cap->fpesew = (hw_cap & XGMAC_HWFEAT_FPESEW) >> 26;
	dma_cap->sgfsew = (hw_cap & XGMAC_HWFEAT_SGFSEW) >> 25;
	dma_cap->estwid = (hw_cap & XGMAC_HWFEAT_ESTWID) >> 23;
	dma_cap->estdep = (hw_cap & XGMAC_HWFEAT_ESTDEP) >> 20;
	dma_cap->estsew = (hw_cap & XGMAC_HWFEAT_ESTSEW) >> 19;
	dma_cap->ttsfd = (hw_cap & XGMAC_HWFEAT_TTSFD) >> 16;
	dma_cap->asp = (hw_cap & XGMAC_HWFEAT_ASP) >> 14;
	dma_cap->dvwan = (hw_cap & XGMAC_HWFEAT_DVWAN) >> 13;
	dma_cap->fwpes = (hw_cap & XGMAC_HWFEAT_FWPES) >> 11;
	dma_cap->fwpbs = (hw_cap & XGMAC_HWFEAT_FWPPB) >> 9;
	dma_cap->pou_ost_en = (hw_cap & XGMAC_HWFEAT_POUOST) >> 8;
	dma_cap->fwppipe_num = ((hw_cap & XGMAC_HWFEAT_FWPPIPE) >> 5) + 1;
	dma_cap->cbtisew = (hw_cap & XGMAC_HWFEAT_CBTISEW) >> 4;
	dma_cap->fwpsew = (hw_cap & XGMAC_HWFEAT_FWPSEW) >> 3;
	dma_cap->nwvf_num = (hw_cap & XGMAC_HWFEAT_NWVF) >> 0;

	/* MAC HW featuwe 4 */
	hw_cap = weadw(ioaddw + XGMAC_HW_FEATUWE4);
	dma_cap->asp |= (hw_cap & XGMAC_HWFEAT_EASP) >> 2;
	dma_cap->pcsew = (hw_cap & XGMAC_HWFEAT_PCSEW) >> 0;

	wetuwn 0;
}

static void dwxgmac2_wx_watchdog(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				 u32 wiwt, u32 queue)
{
	wwitew(wiwt & XGMAC_WWT, ioaddw + XGMAC_DMA_CH_Wx_WATCHDOG(queue));
}

static void dwxgmac2_set_wx_wing_wen(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 wen, u32 chan)
{
	wwitew(wen, ioaddw + XGMAC_DMA_CH_WxDESC_WING_WEN(chan));
}

static void dwxgmac2_set_tx_wing_wen(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 wen, u32 chan)
{
	wwitew(wen, ioaddw + XGMAC_DMA_CH_TxDESC_WING_WEN(chan));
}

static void dwxgmac2_set_wx_taiw_ptw(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 ptw, u32 chan)
{
	wwitew(ptw, ioaddw + XGMAC_DMA_CH_WxDESC_TAIW_WPTW(chan));
}

static void dwxgmac2_set_tx_taiw_ptw(stwuct stmmac_pwiv *pwiv,
				     void __iomem *ioaddw, u32 ptw, u32 chan)
{
	wwitew(ptw, ioaddw + XGMAC_DMA_CH_TxDESC_TAIW_WPTW(chan));
}

static void dwxgmac2_enabwe_tso(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				boow en, u32 chan)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	if (en)
		vawue |= XGMAC_TSE;
	ewse
		vawue &= ~XGMAC_TSE;

	wwitew(vawue, ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));
}

static void dwxgmac2_qmode(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   u32 channew, u8 qmode)
{
	u32 vawue = weadw(ioaddw + XGMAC_MTW_TXQ_OPMODE(channew));
	u32 fwow = weadw(ioaddw + XGMAC_WX_FWOW_CTWW);

	vawue &= ~XGMAC_TXQEN;
	if (qmode != MTW_QUEUE_AVB) {
		vawue |= 0x2 << XGMAC_TXQEN_SHIFT;
		wwitew(0, ioaddw + XGMAC_MTW_TCx_ETS_CONTWOW(channew));
	} ewse {
		vawue |= 0x1 << XGMAC_TXQEN_SHIFT;
		wwitew(fwow & (~XGMAC_WFE), ioaddw + XGMAC_WX_FWOW_CTWW);
	}

	wwitew(vawue, ioaddw +  XGMAC_MTW_TXQ_OPMODE(channew));
}

static void dwxgmac2_set_bfsize(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				int bfsize, u32 chan)
{
	u32 vawue;

	vawue = weadw(ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
	vawue &= ~XGMAC_WBSZ;
	vawue |= bfsize << XGMAC_WBSZ_SHIFT;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_WX_CONTWOW(chan));
}

static void dwxgmac2_enabwe_sph(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				boow en, u32 chan)
{
	u32 vawue = weadw(ioaddw + XGMAC_WX_CONFIG);

	vawue &= ~XGMAC_CONFIG_HDSMS;
	vawue |= XGMAC_CONFIG_HDSMS_256; /* Segment max 256 bytes */
	wwitew(vawue, ioaddw + XGMAC_WX_CONFIG);

	vawue = weadw(ioaddw + XGMAC_DMA_CH_CONTWOW(chan));
	if (en)
		vawue |= XGMAC_SPH;
	ewse
		vawue &= ~XGMAC_SPH;
	wwitew(vawue, ioaddw + XGMAC_DMA_CH_CONTWOW(chan));
}

static int dwxgmac2_enabwe_tbs(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			       boow en, u32 chan)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	if (en)
		vawue |= XGMAC_EDSE;
	ewse
		vawue &= ~XGMAC_EDSE;

	wwitew(vawue, ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan));

	vawue = weadw(ioaddw + XGMAC_DMA_CH_TX_CONTWOW(chan)) & XGMAC_EDSE;
	if (en && !vawue)
		wetuwn -EIO;

	wwitew(XGMAC_DEF_FTOS, ioaddw + XGMAC_DMA_TBS_CTWW0);
	wwitew(XGMAC_DEF_FTOS, ioaddw + XGMAC_DMA_TBS_CTWW1);
	wwitew(XGMAC_DEF_FTOS, ioaddw + XGMAC_DMA_TBS_CTWW2);
	wwitew(XGMAC_DEF_FTOS, ioaddw + XGMAC_DMA_TBS_CTWW3);
	wetuwn 0;
}

const stwuct stmmac_dma_ops dwxgmac210_dma_ops = {
	.weset = dwxgmac2_dma_weset,
	.init = dwxgmac2_dma_init,
	.init_chan = dwxgmac2_dma_init_chan,
	.init_wx_chan = dwxgmac2_dma_init_wx_chan,
	.init_tx_chan = dwxgmac2_dma_init_tx_chan,
	.axi = dwxgmac2_dma_axi,
	.dump_wegs = dwxgmac2_dma_dump_wegs,
	.dma_wx_mode = dwxgmac2_dma_wx_mode,
	.dma_tx_mode = dwxgmac2_dma_tx_mode,
	.enabwe_dma_iwq = dwxgmac2_enabwe_dma_iwq,
	.disabwe_dma_iwq = dwxgmac2_disabwe_dma_iwq,
	.stawt_tx = dwxgmac2_dma_stawt_tx,
	.stop_tx = dwxgmac2_dma_stop_tx,
	.stawt_wx = dwxgmac2_dma_stawt_wx,
	.stop_wx = dwxgmac2_dma_stop_wx,
	.dma_intewwupt = dwxgmac2_dma_intewwupt,
	.get_hw_featuwe = dwxgmac2_get_hw_featuwe,
	.wx_watchdog = dwxgmac2_wx_watchdog,
	.set_wx_wing_wen = dwxgmac2_set_wx_wing_wen,
	.set_tx_wing_wen = dwxgmac2_set_tx_wing_wen,
	.set_wx_taiw_ptw = dwxgmac2_set_wx_taiw_ptw,
	.set_tx_taiw_ptw = dwxgmac2_set_tx_taiw_ptw,
	.enabwe_tso = dwxgmac2_enabwe_tso,
	.qmode = dwxgmac2_qmode,
	.set_bfsize = dwxgmac2_set_bfsize,
	.enabwe_sph = dwxgmac2_enabwe_sph,
	.enabwe_tbs = dwxgmac2_enabwe_tbs,
};
