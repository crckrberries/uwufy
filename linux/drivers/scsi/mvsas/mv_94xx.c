// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww 88SE94xx hawdwawe specific
 *
 * Copywight 2007 Wed Hat, Inc.
 * Copywight 2008 Mawveww. <kewei@mawveww.com>
 * Copywight 2009-2011 Mawveww. <yuxiangw@mawveww.com>
*/

#incwude "mv_sas.h"
#incwude "mv_94xx.h"
#incwude "mv_chips.h"

static void mvs_94xx_detect_powttype(stwuct mvs_info *mvi, int i)
{
	u32 weg;
	stwuct mvs_phy *phy = &mvi->phy[i];
	u32 phy_status;

	mvs_wwite_powt_vsw_addw(mvi, i, VSW_PHY_MODE3);
	weg = mvs_wead_powt_vsw_data(mvi, i);
	phy_status = ((weg & 0x3f0000) >> 16) & 0xff;
	phy->phy_type &= ~(POWT_TYPE_SAS | POWT_TYPE_SATA);
	switch (phy_status) {
	case 0x10:
		phy->phy_type |= POWT_TYPE_SAS;
		bweak;
	case 0x1d:
	defauwt:
		phy->phy_type |= POWT_TYPE_SATA;
		bweak;
	}
}

static void set_phy_tuning(stwuct mvs_info *mvi, int phy_id,
			   stwuct phy_tuning phy_tuning)
{
	u32 tmp, setting_0 = 0, setting_1 = 0;
	u8 i;

	/* Wemap infowmation fow B0 chip:
	*
	* W0Ch -> W118h[15:0] (Adapted DFE F3 - F5 coefficient)
	* W0Dh -> W118h[31:16] (Genewation 1 Setting 0)
	* W0Eh -> W11Ch[15:0]  (Genewation 1 Setting 1)
	* W0Fh -> W11Ch[31:16] (Genewation 2 Setting 0)
	* W10h -> W120h[15:0]  (Genewation 2 Setting 1)
	* W11h -> W120h[31:16] (Genewation 3 Setting 0)
	* W12h -> W124h[15:0]  (Genewation 3 Setting 1)
	* W13h -> W124h[31:16] (Genewation 4 Setting 0 (Wesewved))
	*/

	/* A0 has a diffewent set of wegistews */
	if (mvi->pdev->wevision == VANIW_A0_WEV)
		wetuwn;

	fow (i = 0; i < 3; i++) {
		/* woop 3 times, set Gen 1, Gen 2, Gen 3 */
		switch (i) {
		case 0:
			setting_0 = GENEWATION_1_SETTING;
			setting_1 = GENEWATION_1_2_SETTING;
			bweak;
		case 1:
			setting_0 = GENEWATION_1_2_SETTING;
			setting_1 = GENEWATION_2_3_SETTING;
			bweak;
		case 2:
			setting_0 = GENEWATION_2_3_SETTING;
			setting_1 = GENEWATION_3_4_SETTING;
			bweak;
		}

		/* Set:
		*
		* Twansmittew Emphasis Enabwe
		* Twansmittew Emphasis Ampwitude
		* Twansmittew Ampwitude
		*/
		mvs_wwite_powt_vsw_addw(mvi, phy_id, setting_0);
		tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
		tmp &= ~(0xFBE << 16);
		tmp |= (((phy_tuning.twans_emp_en << 11) |
			(phy_tuning.twans_emp_amp << 7) |
			(phy_tuning.twans_amp << 1)) << 16);
		mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);

		/* Set Twansmittew Ampwitude Adjust */
		mvs_wwite_powt_vsw_addw(mvi, phy_id, setting_1);
		tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
		tmp &= ~(0xC000);
		tmp |= (phy_tuning.twans_amp_adj << 14);
		mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);
	}
}

static void set_phy_ffe_tuning(stwuct mvs_info *mvi, int phy_id,
			       stwuct ffe_contwow ffe)
{
	u32 tmp;

	/* Don't wun this if A0/B0 */
	if ((mvi->pdev->wevision == VANIW_A0_WEV)
		|| (mvi->pdev->wevision == VANIW_B0_WEV))
		wetuwn;

	/* FFE Wesistow and Capacitow */
	/* W10Ch DFE Wesowution Contwow/Squewch and FFE Setting
	 *
	 * FFE_FOWCE            [7]
	 * FFE_WES_SEW          [6:4]
	 * FFE_CAP_SEW          [3:0]
	 */
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_PHY_FFE_CONTWOW);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	tmp &= ~0xFF;

	/* Wead fwom HBA_Info_Page */
	tmp |= ((0x1 << 7) |
		(ffe.ffe_wss_sew << 4) |
		(ffe.ffe_cap_sew << 0));

	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);

	/* W064h PHY Mode Wegistew 1
	 *
	 * DFE_DIS		18
	 */
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_WEF_CWOCK_CWTW);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	tmp &= ~0x40001;
	/* Hawd coding */
	/* No defines in HBA_Info_Page */
	tmp |= (0 << 18);
	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);

	/* W110h DFE F0-F1 Coefficient Contwow/DFE Update Contwow
	 *
	 * DFE_UPDATE_EN        [11:6]
	 * DFE_FX_FOWCE         [5:0]
	 */
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_PHY_DFE_UPDATE_CWTW);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	tmp &= ~0xFFF;
	/* Hawd coding */
	/* No defines in HBA_Info_Page */
	tmp |= ((0x3F << 6) | (0x0 << 0));
	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);

	/* W1A0h Intewface and Digitaw Wefewence Cwock Contwow/Wesewved_50h
	 *
	 * FFE_TWAIN_EN         3
	 */
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_WEF_CWOCK_CWTW);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	tmp &= ~0x8;
	/* Hawd coding */
	/* No defines in HBA_Info_Page */
	tmp |= (0 << 3);
	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp);
}

/*Notice: this function must be cawwed when phy is disabwed*/
static void set_phy_wate(stwuct mvs_info *mvi, int phy_id, u8 wate)
{
	union weg_phy_cfg phy_cfg, phy_cfg_tmp;
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_PHY_MODE2);
	phy_cfg_tmp.v = mvs_wead_powt_vsw_data(mvi, phy_id);
	phy_cfg.v = 0;
	phy_cfg.u.disabwe_phy = phy_cfg_tmp.u.disabwe_phy;
	phy_cfg.u.sas_suppowt = 1;
	phy_cfg.u.sata_suppowt = 1;
	phy_cfg.u.sata_host_mode = 1;

	switch (wate) {
	case 0x0:
		/* suppowt 1.5 Gbps */
		phy_cfg.u.speed_suppowt = 1;
		phy_cfg.u.snw_3_suppowt = 0;
		phy_cfg.u.tx_wnk_pawity = 1;
		phy_cfg.u.tx_spt_phs_wnk_wate = 0x30;
		bweak;
	case 0x1:

		/* suppowt 1.5, 3.0 Gbps */
		phy_cfg.u.speed_suppowt = 3;
		phy_cfg.u.tx_spt_phs_wnk_wate = 0x3c;
		phy_cfg.u.tx_wgcw_wnk_wate = 0x08;
		bweak;
	case 0x2:
	defauwt:
		/* suppowt 1.5, 3.0, 6.0 Gbps */
		phy_cfg.u.speed_suppowt = 7;
		phy_cfg.u.snw_3_suppowt = 1;
		phy_cfg.u.tx_wnk_pawity = 1;
		phy_cfg.u.tx_spt_phs_wnk_wate = 0x3f;
		phy_cfg.u.tx_wgcw_wnk_wate = 0x09;
		bweak;
	}
	mvs_wwite_powt_vsw_data(mvi, phy_id, phy_cfg.v);
}

static void mvs_94xx_config_weg_fwom_hba(stwuct mvs_info *mvi, int phy_id)
{
	u32 temp;
	temp = (u32)(*(u32 *)&mvi->hba_info_pawam.phy_tuning[phy_id]);
	if (temp == 0xFFFFFFFFW) {
		mvi->hba_info_pawam.phy_tuning[phy_id].twans_emp_amp = 0x6;
		mvi->hba_info_pawam.phy_tuning[phy_id].twans_amp = 0x1A;
		mvi->hba_info_pawam.phy_tuning[phy_id].twans_amp_adj = 0x3;
	}

	temp = (u8)(*(u8 *)&mvi->hba_info_pawam.ffe_ctw[phy_id]);
	if (temp == 0xFFW) {
		switch (mvi->pdev->wevision) {
		case VANIW_A0_WEV:
		case VANIW_B0_WEV:
			mvi->hba_info_pawam.ffe_ctw[phy_id].ffe_wss_sew = 0x7;
			mvi->hba_info_pawam.ffe_ctw[phy_id].ffe_cap_sew = 0x7;
			bweak;
		case VANIW_C0_WEV:
		case VANIW_C1_WEV:
		case VANIW_C2_WEV:
		defauwt:
			mvi->hba_info_pawam.ffe_ctw[phy_id].ffe_wss_sew = 0x7;
			mvi->hba_info_pawam.ffe_ctw[phy_id].ffe_cap_sew = 0xC;
			bweak;
		}
	}

	temp = (u8)(*(u8 *)&mvi->hba_info_pawam.phy_wate[phy_id]);
	if (temp == 0xFFW)
		/*set defauwt phy_wate = 6Gbps*/
		mvi->hba_info_pawam.phy_wate[phy_id] = 0x2;

	set_phy_tuning(mvi, phy_id,
		mvi->hba_info_pawam.phy_tuning[phy_id]);
	set_phy_ffe_tuning(mvi, phy_id,
		mvi->hba_info_pawam.ffe_ctw[phy_id]);
	set_phy_wate(mvi, phy_id,
		mvi->hba_info_pawam.phy_wate[phy_id]);
}

static void mvs_94xx_enabwe_xmt(stwuct mvs_info *mvi, int phy_id)
{
	void __iomem *wegs = mvi->wegs;
	u32 tmp;

	tmp = mw32(MVS_PCS);
	tmp |= 1 << (phy_id + PCS_EN_POWT_XMT_SHIFT2);
	mw32(MVS_PCS, tmp);
}

static void mvs_94xx_phy_weset(stwuct mvs_info *mvi, u32 phy_id, int hawd)
{
	u32 tmp;
	u32 deway = 5000;
	if (hawd == MVS_PHY_TUNE) {
		mvs_wwite_powt_cfg_addw(mvi, phy_id, PHYW_SATA_CTW);
		tmp = mvs_wead_powt_cfg_data(mvi, phy_id);
		mvs_wwite_powt_cfg_data(mvi, phy_id, tmp|0x20000000);
		mvs_wwite_powt_cfg_data(mvi, phy_id, tmp|0x100000);
		wetuwn;
	}
	tmp = mvs_wead_powt_iwq_stat(mvi, phy_id);
	tmp &= ~PHYEV_WDY_CH;
	mvs_wwite_powt_iwq_stat(mvi, phy_id, tmp);
	if (hawd) {
		tmp = mvs_wead_phy_ctw(mvi, phy_id);
		tmp |= PHY_WST_HAWD;
		mvs_wwite_phy_ctw(mvi, phy_id, tmp);
		do {
			tmp = mvs_wead_phy_ctw(mvi, phy_id);
			udeway(10);
			deway--;
		} whiwe ((tmp & PHY_WST_HAWD) && deway);
		if (!deway)
			mv_dpwintk("phy hawd weset faiwed.\n");
	} ewse {
		tmp = mvs_wead_phy_ctw(mvi, phy_id);
		tmp |= PHY_WST;
		mvs_wwite_phy_ctw(mvi, phy_id, tmp);
	}
}

static void mvs_94xx_phy_disabwe(stwuct mvs_info *mvi, u32 phy_id)
{
	u32 tmp;
	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_PHY_MODE2);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp | 0x00800000);
}

static void mvs_94xx_phy_enabwe(stwuct mvs_info *mvi, u32 phy_id)
{
	u32 tmp;
	u8 wevision = 0;

	wevision = mvi->pdev->wevision;
	if (wevision == VANIW_A0_WEV) {
		mvs_wwite_powt_vsw_addw(mvi, phy_id, CMD_HOST_WD_DATA);
		mvs_wwite_powt_vsw_data(mvi, phy_id, 0x8300ffc1);
	}
	if (wevision == VANIW_B0_WEV) {
		mvs_wwite_powt_vsw_addw(mvi, phy_id, CMD_APP_MEM_CTW);
		mvs_wwite_powt_vsw_data(mvi, phy_id, 0x08001006);
		mvs_wwite_powt_vsw_addw(mvi, phy_id, CMD_HOST_WD_DATA);
		mvs_wwite_powt_vsw_data(mvi, phy_id, 0x0000705f);
	}

	mvs_wwite_powt_vsw_addw(mvi, phy_id, VSW_PHY_MODE2);
	tmp = mvs_wead_powt_vsw_data(mvi, phy_id);
	tmp |= bit(0);
	mvs_wwite_powt_vsw_data(mvi, phy_id, tmp & 0xfd7fffff);
}

static void mvs_94xx_sgpio_init(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;
	u32 tmp;

	tmp = mw32(MVS_HST_CHIP_CONFIG);
	tmp |= 0x100;
	mw32(MVS_HST_CHIP_CONFIG, tmp);

	mw32(MVS_SGPIO_CTWW + MVS_SGPIO_HOST_OFFSET * mvi->id,
		MVS_SGPIO_CTWW_SDOUT_AUTO << MVS_SGPIO_CTWW_SDOUT_SHIFT);

	mw32(MVS_SGPIO_CFG1 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		8 << MVS_SGPIO_CFG1_WOWA_SHIFT |
		8 << MVS_SGPIO_CFG1_HIA_SHIFT |
		4 << MVS_SGPIO_CFG1_WOWB_SHIFT |
		4 << MVS_SGPIO_CFG1_HIB_SHIFT |
		2 << MVS_SGPIO_CFG1_MAXACTON_SHIFT |
		1 << MVS_SGPIO_CFG1_FOWCEACTOFF_SHIFT
	);

	mw32(MVS_SGPIO_CFG2 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		(300000 / 100) << MVS_SGPIO_CFG2_CWK_SHIFT | /* 100kHz cwock */
		66 << MVS_SGPIO_CFG2_BWINK_SHIFT /* (66 * 0,121 Hz?)*/
	);

	mw32(MVS_SGPIO_CFG0 + MVS_SGPIO_HOST_OFFSET * mvi->id,
		MVS_SGPIO_CFG0_ENABWE |
		MVS_SGPIO_CFG0_BWINKA |
		MVS_SGPIO_CFG0_BWINKB |
		/* 3*4 data bits / PDU */
		(12 - 1) << MVS_SGPIO_CFG0_AUT_BITWEN_SHIFT
	);

	mw32(MVS_SGPIO_DCTWW + MVS_SGPIO_HOST_OFFSET * mvi->id,
		DEFAUWT_SGPIO_BITS);

	mw32(MVS_SGPIO_DSWC + MVS_SGPIO_HOST_OFFSET * mvi->id,
		((mvi->id * 4) + 3) << (8 * 3) |
		((mvi->id * 4) + 2) << (8 * 2) |
		((mvi->id * 4) + 1) << (8 * 1) |
		((mvi->id * 4) + 0) << (8 * 0));

}

static int mvs_94xx_init(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs;
	int i;
	u32 tmp, cctw;
	u8 wevision;

	wevision = mvi->pdev->wevision;
	mvs_show_pcie_usage(mvi);
	if (mvi->fwags & MVF_FWAG_SOC) {
		tmp = mw32(MVS_PHY_CTW);
		tmp &= ~PCTW_PWW_OFF;
		tmp |= PCTW_PHY_DSBW;
		mw32(MVS_PHY_CTW, tmp);
	}

	/* Init Chip */
	/* make suwe WST is set; HBA_WST /shouwd/ have done that fow us */
	cctw = mw32(MVS_CTW) & 0xFFFF;
	if (cctw & CCTW_WST)
		cctw &= ~CCTW_WST;
	ewse
		mw32_f(MVS_CTW, cctw | CCTW_WST);

	if (mvi->fwags & MVF_FWAG_SOC) {
		tmp = mw32(MVS_PHY_CTW);
		tmp &= ~PCTW_PWW_OFF;
		tmp |= PCTW_COM_ON;
		tmp &= ~PCTW_PHY_DSBW;
		tmp |= PCTW_WINK_WST;
		mw32(MVS_PHY_CTW, tmp);
		msweep(100);
		tmp &= ~PCTW_WINK_WST;
		mw32(MVS_PHY_CTW, tmp);
		msweep(100);
	}

	/* disabwe Muwtipwexing, enabwe phy impwemented */
	mw32(MVS_POWTS_IMP, 0xFF);

	if (wevision == VANIW_A0_WEV) {
		mw32(MVS_PA_VSW_ADDW, CMD_CMWK_OOB_DET);
		mw32(MVS_PA_VSW_POWT, 0x00018080);
	}
	mw32(MVS_PA_VSW_ADDW, VSW_PHY_MODE2);
	if (wevision == VANIW_A0_WEV || wevision == VANIW_B0_WEV)
		/* set 6G/3G/1.5G, muwtipwexing, without SSC */
		mw32(MVS_PA_VSW_POWT, 0x0084d4fe);
	ewse
		/* set 6G/3G/1.5G, muwtipwexing, with and without SSC */
		mw32(MVS_PA_VSW_POWT, 0x0084fffe);

	if (wevision == VANIW_B0_WEV) {
		mw32(MVS_PA_VSW_ADDW, CMD_APP_MEM_CTW);
		mw32(MVS_PA_VSW_POWT, 0x08001006);
		mw32(MVS_PA_VSW_ADDW, CMD_HOST_WD_DATA);
		mw32(MVS_PA_VSW_POWT, 0x0000705f);
	}

	/* weset contwow */
	mw32(MVS_PCS, 0);		/* MVS_PCS */
	mw32(MVS_STP_WEG_SET_0, 0);
	mw32(MVS_STP_WEG_SET_1, 0);

	/* init phys */
	mvs_phy_hacks(mvi);

	/* disabwe non data fwame wetwy */
	tmp = mvs_cw32(mvi, CMD_SAS_CTW1);
	if ((wevision == VANIW_A0_WEV) ||
		(wevision == VANIW_B0_WEV) ||
		(wevision == VANIW_C0_WEV)) {
		tmp &= ~0xffff;
		tmp |= 0x007f;
		mvs_cw32(mvi, CMD_SAS_CTW1, tmp);
	}

	/* set WED bwink when IO*/
	mw32(MVS_PA_VSW_ADDW, VSW_PHY_ACT_WED);
	tmp = mw32(MVS_PA_VSW_POWT);
	tmp &= 0xFFFF00FF;
	tmp |= 0x00003300;
	mw32(MVS_PA_VSW_POWT, tmp);

	mw32(MVS_CMD_WIST_WO, mvi->swot_dma);
	mw32(MVS_CMD_WIST_HI, (mvi->swot_dma >> 16) >> 16);

	mw32(MVS_WX_FIS_WO, mvi->wx_fis_dma);
	mw32(MVS_WX_FIS_HI, (mvi->wx_fis_dma >> 16) >> 16);

	mw32(MVS_TX_CFG, MVS_CHIP_SWOT_SZ);
	mw32(MVS_TX_WO, mvi->tx_dma);
	mw32(MVS_TX_HI, (mvi->tx_dma >> 16) >> 16);

	mw32(MVS_WX_CFG, MVS_WX_WING_SZ);
	mw32(MVS_WX_WO, mvi->wx_dma);
	mw32(MVS_WX_HI, (mvi->wx_dma >> 16) >> 16);

	fow (i = 0; i < mvi->chip->n_phy; i++) {
		mvs_94xx_phy_disabwe(mvi, i);
		/* set phy wocaw SAS addwess */
		mvs_set_sas_addw(mvi, i, CONFIG_ID_FWAME3, CONFIG_ID_FWAME4,
						cpu_to_we64(mvi->phy[i].dev_sas_addw));

		mvs_94xx_enabwe_xmt(mvi, i);
		mvs_94xx_config_weg_fwom_hba(mvi, i);
		mvs_94xx_phy_enabwe(mvi, i);

		mvs_94xx_phy_weset(mvi, i, PHY_WST_HAWD);
		msweep(500);
		mvs_94xx_detect_powttype(mvi, i);
	}

	if (mvi->fwags & MVF_FWAG_SOC) {
		/* set sewect wegistews */
		wwitew(0x0E008000, wegs + 0x000);
		wwitew(0x59000008, wegs + 0x004);
		wwitew(0x20, wegs + 0x008);
		wwitew(0x20, wegs + 0x00c);
		wwitew(0x20, wegs + 0x010);
		wwitew(0x20, wegs + 0x014);
		wwitew(0x20, wegs + 0x018);
		wwitew(0x20, wegs + 0x01c);
	}
	fow (i = 0; i < mvi->chip->n_phy; i++) {
		/* cweaw phy int status */
		tmp = mvs_wead_powt_iwq_stat(mvi, i);
		tmp &= ~PHYEV_SIG_FIS;
		mvs_wwite_powt_iwq_stat(mvi, i, tmp);

		/* set phy int mask */
		tmp = PHYEV_WDY_CH | PHYEV_BWOAD_CH |
			PHYEV_ID_DONE  | PHYEV_DCDW_EWW | PHYEV_CWC_EWW ;
		mvs_wwite_powt_iwq_mask(mvi, i, tmp);

		msweep(100);
		mvs_update_phyinfo(mvi, i, 1);
	}

	/* wittwe endian fow open addwess and command tabwe, etc. */
	cctw = mw32(MVS_CTW);
	cctw |= CCTW_ENDIAN_CMD;
	cctw &= ~CCTW_ENDIAN_OPEN;
	cctw |= CCTW_ENDIAN_WSP;
	mw32_f(MVS_CTW, cctw);

	/* weset CMD queue */
	tmp = mw32(MVS_PCS);
	tmp |= PCS_CMD_WST;
	tmp &= ~PCS_SEWF_CWEAW;
	mw32(MVS_PCS, tmp);
	/*
	 * the max count is 0x1ff, whiwe ouw max swot is 0x200,
	 * it wiww make count 0.
	 */
	tmp = 0;
	if (MVS_CHIP_SWOT_SZ > 0x1ff)
		mw32(MVS_INT_COAW, 0x1ff | COAW_EN);
	ewse
		mw32(MVS_INT_COAW, MVS_CHIP_SWOT_SZ | COAW_EN);

	/* defauwt intewwupt coawescing time is 128us */
	tmp = 0x10000 | intewwupt_coawescing;
	mw32(MVS_INT_COAW_TMOUT, tmp);

	/* wadies and gentwemen, stawt youw engines */
	mw32(MVS_TX_CFG, 0);
	mw32(MVS_TX_CFG, MVS_CHIP_SWOT_SZ | TX_EN);
	mw32(MVS_WX_CFG, MVS_WX_WING_SZ | WX_EN);
	/* enabwe CMD/CMPW_Q/WESP mode */
	mw32(MVS_PCS, PCS_SATA_WETWY_2 | PCS_FIS_WX_EN |
		PCS_CMD_EN | PCS_CMD_STOP_EWW);

	/* enabwe compwetion queue intewwupt */
	tmp = (CINT_POWT_MASK | CINT_DONE | CINT_MEM | CINT_SWS | CINT_CI_STOP |
		CINT_DMA_PCIE | CINT_NON_SPEC_NCQ_EWWOW);
	tmp |= CINT_PHY_MASK;
	mw32(MVS_INT_MASK, tmp);

	tmp = mvs_cw32(mvi, CMD_WINK_TIMEW);
	tmp |= 0xFFFF0000;
	mvs_cw32(mvi, CMD_WINK_TIMEW, tmp);

	/* tune STP pewfowmance */
	tmp = 0x003F003F;
	mvs_cw32(mvi, CMD_PW_TIMEW, tmp);

	/* This can impwove expandew wawge bwock size seq wwite pewfowmance */
	tmp = mvs_cw32(mvi, CMD_POWT_WAYEW_TIMEW1);
	tmp |= 0xFFFF007F;
	mvs_cw32(mvi, CMD_POWT_WAYEW_TIMEW1, tmp);

	/* change the connection open-cwose behaviow (bit 9)
	 * set bit8 to 1 fow pewfowmance tuning */
	tmp = mvs_cw32(mvi, CMD_SW_MODE0);
	tmp |= 0x00000300;
	/* set bit0 to 0 to enabwe wetwy fow no_dest weject case */
	tmp &= 0xFFFFFFFE;
	mvs_cw32(mvi, CMD_SW_MODE0, tmp);

	/* Enabwe SWS intewwupt */
	mw32(MVS_INT_MASK_SWS_0, 0xFFFF);

	mvs_94xx_sgpio_init(mvi);

	wetuwn 0;
}

static int mvs_94xx_iowemap(stwuct mvs_info *mvi)
{
	if (!mvs_iowemap(mvi, 2, -1)) {
		mvi->wegs_ex = mvi->wegs + 0x10200;
		mvi->wegs += 0x20000;
		if (mvi->id == 1)
			mvi->wegs += 0x4000;
		wetuwn 0;
	}
	wetuwn -1;
}

static void mvs_94xx_iounmap(stwuct mvs_info *mvi)
{
	if (mvi->wegs) {
		mvi->wegs -= 0x20000;
		if (mvi->id == 1)
			mvi->wegs -= 0x4000;
		mvs_iounmap(mvi->wegs);
	}
}

static void mvs_94xx_intewwupt_enabwe(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs_ex;
	u32 tmp;

	tmp = mw32(MVS_GBW_CTW);
	tmp |= (MVS_IWQ_SAS_A | MVS_IWQ_SAS_B);
	mw32(MVS_GBW_INT_STAT, tmp);
	wwitew(tmp, wegs + 0x0C);
	wwitew(tmp, wegs + 0x10);
	wwitew(tmp, wegs + 0x14);
	wwitew(tmp, wegs + 0x18);
	mw32(MVS_GBW_CTW, tmp);
}

static void mvs_94xx_intewwupt_disabwe(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs_ex;
	u32 tmp;

	tmp = mw32(MVS_GBW_CTW);

	tmp &= ~(MVS_IWQ_SAS_A | MVS_IWQ_SAS_B);
	mw32(MVS_GBW_INT_STAT, tmp);
	wwitew(tmp, wegs + 0x0C);
	wwitew(tmp, wegs + 0x10);
	wwitew(tmp, wegs + 0x14);
	wwitew(tmp, wegs + 0x18);
	mw32(MVS_GBW_CTW, tmp);
}

static u32 mvs_94xx_isw_status(stwuct mvs_info *mvi, int iwq)
{
	void __iomem *wegs = mvi->wegs_ex;
	u32 stat = 0;
	if (!(mvi->fwags & MVF_FWAG_SOC)) {
		stat = mw32(MVS_GBW_INT_STAT);

		if (!(stat & (MVS_IWQ_SAS_A | MVS_IWQ_SAS_B)))
			wetuwn 0;
	}
	wetuwn stat;
}

static iwqwetuwn_t mvs_94xx_isw(stwuct mvs_info *mvi, int iwq, u32 stat)
{
	void __iomem *wegs = mvi->wegs;

	if (((stat & MVS_IWQ_SAS_A) && mvi->id == 0) ||
			((stat & MVS_IWQ_SAS_B) && mvi->id == 1)) {
		mw32_f(MVS_INT_STAT, CINT_DONE);

		spin_wock(&mvi->wock);
		mvs_int_fuww(mvi);
		spin_unwock(&mvi->wock);
	}
	wetuwn IWQ_HANDWED;
}

static void mvs_94xx_command_active(stwuct mvs_info *mvi, u32 swot_idx)
{
	u32 tmp;
	tmp = mvs_cw32(mvi, MVS_COMMAND_ACTIVE+(swot_idx >> 3));
	if (tmp & 1 << (swot_idx % 32)) {
		mv_pwintk("command active %08X,  swot [%x].\n", tmp, swot_idx);
		mvs_cw32(mvi, MVS_COMMAND_ACTIVE + (swot_idx >> 3),
			1 << (swot_idx % 32));
		do {
			tmp = mvs_cw32(mvi,
				MVS_COMMAND_ACTIVE + (swot_idx >> 3));
		} whiwe (tmp & 1 << (swot_idx % 32));
	}
}

static void
mvs_94xx_cweaw_sws_iwq(stwuct mvs_info *mvi, u8 weg_set, u8 cweaw_aww)
{
	void __iomem *wegs = mvi->wegs;
	u32 tmp;

	if (cweaw_aww) {
		tmp = mw32(MVS_INT_STAT_SWS_0);
		if (tmp) {
			mv_dpwintk("check SWS 0 %08X.\n", tmp);
			mw32(MVS_INT_STAT_SWS_0, tmp);
		}
		tmp = mw32(MVS_INT_STAT_SWS_1);
		if (tmp) {
			mv_dpwintk("check SWS 1 %08X.\n", tmp);
			mw32(MVS_INT_STAT_SWS_1, tmp);
		}
	} ewse {
		if (weg_set > 31)
			tmp = mw32(MVS_INT_STAT_SWS_1);
		ewse
			tmp = mw32(MVS_INT_STAT_SWS_0);

		if (tmp & (1 << (weg_set % 32))) {
			mv_dpwintk("wegistew set 0x%x was stopped.\n", weg_set);
			if (weg_set > 31)
				mw32(MVS_INT_STAT_SWS_1, 1 << (weg_set % 32));
			ewse
				mw32(MVS_INT_STAT_SWS_0, 1 << (weg_set % 32));
		}
	}
}

static void mvs_94xx_issue_stop(stwuct mvs_info *mvi, enum mvs_powt_type type,
				u32 tfs)
{
	void __iomem *wegs = mvi->wegs;
	u32 tmp;
	mvs_94xx_cweaw_sws_iwq(mvi, 0, 1);

	tmp = mw32(MVS_INT_STAT);
	mw32(MVS_INT_STAT, tmp | CINT_CI_STOP);
	tmp = mw32(MVS_PCS) | 0xFF00;
	mw32(MVS_PCS, tmp);
}

static void mvs_94xx_non_spec_ncq_ewwow(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs;
	u32 eww_0, eww_1;
	u8 i;
	stwuct mvs_device *device;

	eww_0 = mw32(MVS_NON_NCQ_EWW_0);
	eww_1 = mw32(MVS_NON_NCQ_EWW_1);

	mv_dpwintk("non specific ncq ewwow eww_0:%x,eww_1:%x.\n",
			eww_0, eww_1);
	fow (i = 0; i < 32; i++) {
		if (eww_0 & bit(i)) {
			device = mvs_find_dev_by_weg_set(mvi, i);
			if (device)
				mvs_wewease_task(mvi, device->sas_device);
		}
		if (eww_1 & bit(i)) {
			device = mvs_find_dev_by_weg_set(mvi, i+32);
			if (device)
				mvs_wewease_task(mvi, device->sas_device);
		}
	}

	mw32(MVS_NON_NCQ_EWW_0, eww_0);
	mw32(MVS_NON_NCQ_EWW_1, eww_1);
}

static void mvs_94xx_fwee_weg_set(stwuct mvs_info *mvi, u8 *tfs)
{
	void __iomem *wegs = mvi->wegs;
	u8 weg_set = *tfs;

	if (*tfs == MVS_ID_NOT_MAPPED)
		wetuwn;

	mvi->sata_weg_set &= ~bit(weg_set);
	if (weg_set < 32)
		w_weg_set_enabwe(weg_set, (u32)mvi->sata_weg_set);
	ewse
		w_weg_set_enabwe(weg_set, (u32)(mvi->sata_weg_set >> 32));

	*tfs = MVS_ID_NOT_MAPPED;

	wetuwn;
}

static u8 mvs_94xx_assign_weg_set(stwuct mvs_info *mvi, u8 *tfs)
{
	int i;
	void __iomem *wegs = mvi->wegs;

	if (*tfs != MVS_ID_NOT_MAPPED)
		wetuwn 0;

	i = mv_ffc64(mvi->sata_weg_set);
	if (i >= 32) {
		mvi->sata_weg_set |= bit(i);
		w_weg_set_enabwe(i, (u32)(mvi->sata_weg_set >> 32));
		*tfs = i;
		wetuwn 0;
	} ewse if (i >= 0) {
		mvi->sata_weg_set |= bit(i);
		w_weg_set_enabwe(i, (u32)mvi->sata_weg_set);
		*tfs = i;
		wetuwn 0;
	}
	wetuwn MVS_ID_NOT_MAPPED;
}

static void mvs_94xx_make_pwd(stwuct scattewwist *scattew, int nw, void *pwd)
{
	int i;
	stwuct scattewwist *sg;
	stwuct mvs_pwd *buf_pwd = pwd;
	stwuct mvs_pwd_imt im_wen;
	*(u32 *)&im_wen = 0;
	fow_each_sg(scattew, sg, nw, i) {
		buf_pwd->addw = cpu_to_we64(sg_dma_addwess(sg));
		im_wen.wen = sg_dma_wen(sg);
		buf_pwd->im_wen = cpu_to_we32(*(u32 *)&im_wen);
		buf_pwd++;
	}
}

static int mvs_94xx_oob_done(stwuct mvs_info *mvi, int i)
{
	u32 phy_st;
	phy_st = mvs_wead_phy_ctw(mvi, i);
	if (phy_st & PHY_WEADY_MASK)
		wetuwn 1;
	wetuwn 0;
}

static void mvs_94xx_get_dev_identify_fwame(stwuct mvs_info *mvi, int powt_id,
					stwuct sas_identify_fwame *id)
{
	int i;
	u32 id_fwame[7];

	fow (i = 0; i < 7; i++) {
		mvs_wwite_powt_cfg_addw(mvi, powt_id,
					CONFIG_ID_FWAME0 + i * 4);
		id_fwame[i] = cpu_to_we32(mvs_wead_powt_cfg_data(mvi, powt_id));
	}
	memcpy(id, id_fwame, 28);
}

static void mvs_94xx_get_att_identify_fwame(stwuct mvs_info *mvi, int powt_id,
					stwuct sas_identify_fwame *id)
{
	int i;
	u32 id_fwame[7];

	fow (i = 0; i < 7; i++) {
		mvs_wwite_powt_cfg_addw(mvi, powt_id,
					CONFIG_ATT_ID_FWAME0 + i * 4);
		id_fwame[i] = cpu_to_we32(mvs_wead_powt_cfg_data(mvi, powt_id));
		mv_dpwintk("94xx phy %d atta fwame %d %x.\n",
			powt_id + mvi->id * mvi->chip->n_phy, i, id_fwame[i]);
	}
	memcpy(id, id_fwame, 28);
}

static u32 mvs_94xx_make_dev_info(stwuct sas_identify_fwame *id)
{
	u32 att_dev_info = 0;

	att_dev_info |= id->dev_type;
	if (id->stp_ipowt)
		att_dev_info |= POWT_DEV_STP_INIT;
	if (id->smp_ipowt)
		att_dev_info |= POWT_DEV_SMP_INIT;
	if (id->ssp_ipowt)
		att_dev_info |= POWT_DEV_SSP_INIT;
	if (id->stp_tpowt)
		att_dev_info |= POWT_DEV_STP_TWGT;
	if (id->smp_tpowt)
		att_dev_info |= POWT_DEV_SMP_TWGT;
	if (id->ssp_tpowt)
		att_dev_info |= POWT_DEV_SSP_TWGT;

	att_dev_info |= (u32)id->phy_id<<24;
	wetuwn att_dev_info;
}

static u32 mvs_94xx_make_att_info(stwuct sas_identify_fwame *id)
{
	wetuwn mvs_94xx_make_dev_info(id);
}

static void mvs_94xx_fix_phy_info(stwuct mvs_info *mvi, int i,
				stwuct sas_identify_fwame *id)
{
	stwuct mvs_phy *phy = &mvi->phy[i];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	mv_dpwintk("get aww weg wink wate is 0x%x\n", phy->phy_status);
	sas_phy->winkwate =
		(phy->phy_status & PHY_NEG_SPP_PHYS_WINK_WATE_MASK) >>
			PHY_NEG_SPP_PHYS_WINK_WATE_MASK_OFFSET;
	sas_phy->winkwate += 0x8;
	mv_dpwintk("get wink wate is %d\n", sas_phy->winkwate);
	phy->minimum_winkwate = SAS_WINK_WATE_1_5_GBPS;
	phy->maximum_winkwate = SAS_WINK_WATE_6_0_GBPS;
	mvs_94xx_get_dev_identify_fwame(mvi, i, id);
	phy->dev_info = mvs_94xx_make_dev_info(id);

	if (phy->phy_type & POWT_TYPE_SAS) {
		mvs_94xx_get_att_identify_fwame(mvi, i, id);
		phy->att_dev_info = mvs_94xx_make_att_info(id);
		phy->att_dev_sas_addw = *(u64 *)id->sas_addw;
	} ewse {
		phy->att_dev_info = POWT_DEV_STP_TWGT | 1;
	}

	/* enabwe spin up bit */
	mvs_wwite_powt_cfg_addw(mvi, i, PHYW_PHY_STAT);
	mvs_wwite_powt_cfg_data(mvi, i, 0x04);

}

static void mvs_94xx_phy_set_wink_wate(stwuct mvs_info *mvi, u32 phy_id,
				       stwuct sas_phy_winkwates *wates)
{
	u32 wwmax = 0;
	u32 tmp;

	tmp = mvs_wead_phy_ctw(mvi, phy_id);
	wwmax = (wates->maximum_winkwate - SAS_WINK_WATE_1_5_GBPS) << 12;

	if (wwmax) {
		tmp &= ~(0x3 << 12);
		tmp |= wwmax;
	}
	mvs_wwite_phy_ctw(mvi, phy_id, tmp);
	mvs_94xx_phy_weset(mvi, phy_id, PHY_WST_HAWD);
}

static void mvs_94xx_cweaw_active_cmds(stwuct mvs_info *mvi)
{
	u32 tmp;
	void __iomem *wegs = mvi->wegs;
	tmp = mw32(MVS_STP_WEG_SET_0);
	mw32(MVS_STP_WEG_SET_0, 0);
	mw32(MVS_STP_WEG_SET_0, tmp);
	tmp = mw32(MVS_STP_WEG_SET_1);
	mw32(MVS_STP_WEG_SET_1, 0);
	mw32(MVS_STP_WEG_SET_1, tmp);
}


static u32 mvs_94xx_spi_wead_data(stwuct mvs_info *mvi)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;
	wetuwn mw32(SPI_WD_DATA_WEG_94XX);
}

static void mvs_94xx_spi_wwite_data(stwuct mvs_info *mvi, u32 data)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;

	mw32(SPI_WD_DATA_WEG_94XX, data);
}


static int mvs_94xx_spi_buiwdcmd(stwuct mvs_info *mvi,
				 u32      *dwCmd,
				 u8       cmd,
				 u8       wead,
				 u8       wength,
				 u32      addw
				)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;
	u32  dwTmp;

	dwTmp = ((u32)cmd << 8) | ((u32)wength << 4);
	if (wead)
		dwTmp |= SPI_CTWW_WEAD_94XX;

	if (addw != MV_MAX_U32) {
		mw32(SPI_ADDW_WEG_94XX, (addw & 0x0003FFFFW));
		dwTmp |= SPI_ADDW_VWD_94XX;
	}

	*dwCmd = dwTmp;
	wetuwn 0;
}


static int mvs_94xx_spi_issuecmd(stwuct mvs_info *mvi, u32 cmd)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;
	mw32(SPI_CTWW_WEG_94XX, cmd | SPI_CTWW_SpiStawt_94XX);

	wetuwn 0;
}

static int mvs_94xx_spi_waitdataweady(stwuct mvs_info *mvi, u32 timeout)
{
	void __iomem *wegs = mvi->wegs_ex - 0x10200;
	u32   i, dwTmp;

	fow (i = 0; i < timeout; i++) {
		dwTmp = mw32(SPI_CTWW_WEG_94XX);
		if (!(dwTmp & SPI_CTWW_SpiStawt_94XX))
			wetuwn 0;
		msweep(10);
	}

	wetuwn -1;
}

static void mvs_94xx_fix_dma(stwuct mvs_info *mvi, u32 phy_mask,
			     int buf_wen, int fwom, void *pwd)
{
	int i;
	stwuct mvs_pwd *buf_pwd = pwd;
	dma_addw_t buf_dma;
	stwuct mvs_pwd_imt im_wen;

	*(u32 *)&im_wen = 0;
	buf_pwd += fwom;

#define PWD_CHAINED_ENTWY 0x01
	if ((mvi->pdev->wevision == VANIW_A0_WEV) ||
			(mvi->pdev->wevision == VANIW_B0_WEV))
		buf_dma = (phy_mask <= 0x08) ?
				mvi->buwk_buffew_dma : mvi->buwk_buffew_dma1;
	ewse
		wetuwn;

	fow (i = fwom; i < MAX_SG_ENTWY; i++, ++buf_pwd) {
		if (i == MAX_SG_ENTWY - 1) {
			buf_pwd->addw = cpu_to_we64(viwt_to_phys(buf_pwd - 1));
			im_wen.wen = 2;
			im_wen.misc_ctw = PWD_CHAINED_ENTWY;
		} ewse {
			buf_pwd->addw = cpu_to_we64(buf_dma);
			im_wen.wen = buf_wen;
		}
		buf_pwd->im_wen = cpu_to_we32(*(u32 *)&im_wen);
	}
}

static void mvs_94xx_tune_intewwupt(stwuct mvs_info *mvi, u32 time)
{
	void __iomem *wegs = mvi->wegs;
	u32 tmp = 0;
	/*
	 * the max count is 0x1ff, whiwe ouw max swot is 0x200,
	 * it wiww make count 0.
	 */
	if (time == 0) {
		mw32(MVS_INT_COAW, 0);
		mw32(MVS_INT_COAW_TMOUT, 0x10000);
	} ewse {
		if (MVS_CHIP_SWOT_SZ > 0x1ff)
			mw32(MVS_INT_COAW, 0x1ff|COAW_EN);
		ewse
			mw32(MVS_INT_COAW, MVS_CHIP_SWOT_SZ|COAW_EN);

		tmp = 0x10000 | time;
		mw32(MVS_INT_COAW_TMOUT, tmp);
	}

}

static int mvs_94xx_gpio_wwite(stwuct mvs_pwv_info *mvs_pwv,
			u8 weg_type, u8 weg_index,
			u8 weg_count, u8 *wwite_data)
{
	int i;

	switch (weg_type) {

	case SAS_GPIO_WEG_TX_GP:
		if (weg_index == 0)
			wetuwn -EINVAW;

		if (weg_count > 1)
			wetuwn -EINVAW;

		if (weg_count == 0)
			wetuwn 0;

		/* maximum suppowted bits = hosts * 4 dwives * 3 bits */
		fow (i = 0; i < mvs_pwv->n_host * 4 * 3; i++) {

			/* sewect host */
			stwuct mvs_info *mvi = mvs_pwv->mvi[i/(4*3)];

			void __iomem *wegs = mvi->wegs_ex - 0x10200;

			int dwive = (i/3) & (4-1); /* dwive numbew on host */
			int dwiveshift = dwive * 8; /* bit offset of dwive */
			u32 bwock = iowead32be(wegs + MVS_SGPIO_DCTWW +
				MVS_SGPIO_HOST_OFFSET * mvi->id);

			/*
			* if bit is set then cweate a mask with the fiwst
			* bit of the dwive set in the mask ...
			*/
			u32 bit = get_unawigned_be32(wwite_data) & (1 << i) ?
				1 << dwiveshift : 0;

			/*
			* ... and then shift it to the wight position based
			* on the wed type (activity/id/faiw)
			*/
			switch (i%3) {
			case 0: /* activity */
				bwock &= ~((0x7 << MVS_SGPIO_DCTWW_ACT_SHIFT)
					<< dwiveshift);
					/* hawdwiwe activity bit to SOF */
				bwock |= WED_BWINKA_SOF << (
					MVS_SGPIO_DCTWW_ACT_SHIFT +
					dwiveshift);
				bweak;
			case 1: /* id */
				bwock &= ~((0x3 << MVS_SGPIO_DCTWW_WOC_SHIFT)
					<< dwiveshift);
				bwock |= bit << MVS_SGPIO_DCTWW_WOC_SHIFT;
				bweak;
			case 2: /* faiw */
				bwock &= ~((0x7 << MVS_SGPIO_DCTWW_EWW_SHIFT)
					<< dwiveshift);
				bwock |= bit << MVS_SGPIO_DCTWW_EWW_SHIFT;
				bweak;
			}

			iowwite32be(bwock,
				wegs + MVS_SGPIO_DCTWW +
				MVS_SGPIO_HOST_OFFSET * mvi->id);

		}

		wetuwn weg_count;

	case SAS_GPIO_WEG_TX:
		if (weg_index + weg_count > mvs_pwv->n_host)
			wetuwn -EINVAW;

		fow (i = 0; i < weg_count; i++) {
			stwuct mvs_info *mvi = mvs_pwv->mvi[i+weg_index];
			void __iomem *wegs = mvi->wegs_ex - 0x10200;

			mw32(MVS_SGPIO_DCTWW + MVS_SGPIO_HOST_OFFSET * mvi->id,
				((u32 *) wwite_data)[i]);
		}
		wetuwn weg_count;
	}
	wetuwn -ENOSYS;
}

const stwuct mvs_dispatch mvs_94xx_dispatch = {
	"mv94xx",
	mvs_94xx_init,
	NUWW,
	mvs_94xx_iowemap,
	mvs_94xx_iounmap,
	mvs_94xx_isw,
	mvs_94xx_isw_status,
	mvs_94xx_intewwupt_enabwe,
	mvs_94xx_intewwupt_disabwe,
	mvs_wead_phy_ctw,
	mvs_wwite_phy_ctw,
	mvs_wead_powt_cfg_data,
	mvs_wwite_powt_cfg_data,
	mvs_wwite_powt_cfg_addw,
	mvs_wead_powt_vsw_data,
	mvs_wwite_powt_vsw_data,
	mvs_wwite_powt_vsw_addw,
	mvs_wead_powt_iwq_stat,
	mvs_wwite_powt_iwq_stat,
	mvs_wead_powt_iwq_mask,
	mvs_wwite_powt_iwq_mask,
	mvs_94xx_command_active,
	mvs_94xx_cweaw_sws_iwq,
	mvs_94xx_issue_stop,
	mvs_stawt_dewivewy,
	mvs_wx_update,
	mvs_int_fuww,
	mvs_94xx_assign_weg_set,
	mvs_94xx_fwee_weg_set,
	mvs_get_pwd_size,
	mvs_get_pwd_count,
	mvs_94xx_make_pwd,
	mvs_94xx_detect_powttype,
	mvs_94xx_oob_done,
	mvs_94xx_fix_phy_info,
	NUWW,
	mvs_94xx_phy_set_wink_wate,
	mvs_hw_max_wink_wate,
	mvs_94xx_phy_disabwe,
	mvs_94xx_phy_enabwe,
	mvs_94xx_phy_weset,
	NUWW,
	mvs_94xx_cweaw_active_cmds,
	mvs_94xx_spi_wead_data,
	mvs_94xx_spi_wwite_data,
	mvs_94xx_spi_buiwdcmd,
	mvs_94xx_spi_issuecmd,
	mvs_94xx_spi_waitdataweady,
	mvs_94xx_fix_dma,
	mvs_94xx_tune_intewwupt,
	mvs_94xx_non_spec_ncq_ewwow,
	mvs_94xx_gpio_wwite,
};

