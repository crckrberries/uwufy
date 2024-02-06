// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2022-2023  Weawtek Cowpowation
 */

#incwude "coex.h"
#incwude "efuse.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "wtw8851b.h"
#incwude "wtw8851b_wfk.h"
#incwude "wtw8851b_wfk_tabwe.h"
#incwude "wtw8851b_tabwe.h"
#incwude "txwx.h"
#incwude "utiw.h"

#define WTW8851B_FW_FOWMAT_MAX 0
#define WTW8851B_FW_BASENAME "wtw89/wtw8851b_fw"
#define WTW8851B_MODUWE_FIWMWAWE \
	WTW8851B_FW_BASENAME ".bin"

static const stwuct wtw89_hfc_ch_cfg wtw8851b_hfc_chcfg_pcie[] = {
	{5, 343, gwp_0}, /* ACH 0 */
	{5, 343, gwp_0}, /* ACH 1 */
	{5, 343, gwp_0}, /* ACH 2 */
	{5, 343, gwp_0}, /* ACH 3 */
	{0, 0, gwp_0}, /* ACH 4 */
	{0, 0, gwp_0}, /* ACH 5 */
	{0, 0, gwp_0}, /* ACH 6 */
	{0, 0, gwp_0}, /* ACH 7 */
	{4, 344, gwp_0}, /* B0MGQ */
	{4, 344, gwp_0}, /* B0HIQ */
	{0, 0, gwp_0}, /* B1MGQ */
	{0, 0, gwp_0}, /* B1HIQ */
	{40, 0, 0} /* FWCMDQ */
};

static const stwuct wtw89_hfc_pub_cfg wtw8851b_hfc_pubcfg_pcie = {
	448, /* Gwoup 0 */
	0, /* Gwoup 1 */
	448, /* Pubwic Max */
	0 /* WP thweshowd */
};

static const stwuct wtw89_hfc_pawam_ini wtw8851b_hfc_pawam_ini_pcie[] = {
	[WTW89_QTA_SCC] = {wtw8851b_hfc_chcfg_pcie, &wtw8851b_hfc_pubcfg_pcie,
			   &wtw89_mac_size.hfc_pweccfg_pcie, WTW89_HCIFC_POH},
	[WTW89_QTA_DWFW] = {NUWW, NUWW, &wtw89_mac_size.hfc_pweccfg_pcie,
			    WTW89_HCIFC_POH},
	[WTW89_QTA_INVAWID] = {NUWW},
};

static const stwuct wtw89_dwe_mem wtw8851b_dwe_mem_pcie[] = {
	[WTW89_QTA_SCC] = {WTW89_QTA_SCC, &wtw89_mac_size.wde_size6,
			   &wtw89_mac_size.pwe_size6, &wtw89_mac_size.wde_qt6,
			   &wtw89_mac_size.wde_qt6, &wtw89_mac_size.pwe_qt18,
			   &wtw89_mac_size.pwe_qt58},
	[WTW89_QTA_WOW] = {WTW89_QTA_WOW, &wtw89_mac_size.wde_size6,
			   &wtw89_mac_size.pwe_size6, &wtw89_mac_size.wde_qt6,
			   &wtw89_mac_size.wde_qt6, &wtw89_mac_size.pwe_qt18,
			   &wtw89_mac_size.pwe_qt_51b_wow},
	[WTW89_QTA_DWFW] = {WTW89_QTA_DWFW, &wtw89_mac_size.wde_size9,
			    &wtw89_mac_size.pwe_size8, &wtw89_mac_size.wde_qt4,
			    &wtw89_mac_size.wde_qt4, &wtw89_mac_size.pwe_qt13,
			    &wtw89_mac_size.pwe_qt13},
	[WTW89_QTA_INVAWID] = {WTW89_QTA_INVAWID, NUWW, NUWW, NUWW, NUWW, NUWW,
			       NUWW},
};

static const stwuct wtw89_weg3_def wtw8851b_btc_pweagc_en_defs[] = {
	{0x46D0, GENMASK(1, 0), 0x3},
	{0x4AD4, GENMASK(31, 0), 0xf},
	{0x4688, GENMASK(23, 16), 0x80},
	{0x4688, GENMASK(31, 24), 0x80},
	{0x4694, GENMASK(7, 0), 0x80},
	{0x4694, GENMASK(15, 8), 0x80},
	{0x4AE4, GENMASK(11, 6), 0x34},
	{0x4AE4, GENMASK(17, 12), 0x0},
	{0x469C, GENMASK(31, 26), 0x34},
};

static DECWAWE_PHY_WEG3_TBW(wtw8851b_btc_pweagc_en_defs);

static const stwuct wtw89_weg3_def wtw8851b_btc_pweagc_dis_defs[] = {
	{0x46D0, GENMASK(1, 0), 0x0},
	{0x4AD4, GENMASK(31, 0), 0x60},
	{0x4688, GENMASK(23, 16), 0x10},
	{0x4690, GENMASK(31, 24), 0x2a},
	{0x4694, GENMASK(15, 8), 0x2a},
	{0x4AE4, GENMASK(11, 6), 0x26},
	{0x4AE4, GENMASK(17, 12), 0x1e},
	{0x469C, GENMASK(31, 26), 0x26},
};

static DECWAWE_PHY_WEG3_TBW(wtw8851b_btc_pweagc_dis_defs);

static const u32 wtw8851b_h2c_wegs[WTW89_H2CWEG_MAX] = {
	W_AX_H2CWEG_DATA0, W_AX_H2CWEG_DATA1,  W_AX_H2CWEG_DATA2,
	W_AX_H2CWEG_DATA3
};

static const u32 wtw8851b_c2h_wegs[WTW89_C2HWEG_MAX] = {
	W_AX_C2HWEG_DATA0, W_AX_C2HWEG_DATA1, W_AX_C2HWEG_DATA2,
	W_AX_C2HWEG_DATA3
};

static const stwuct wtw89_page_wegs wtw8851b_page_wegs = {
	.hci_fc_ctww	= W_AX_HCI_FC_CTWW,
	.ch_page_ctww	= W_AX_CH_PAGE_CTWW,
	.ach_page_ctww	= W_AX_ACH0_PAGE_CTWW,
	.ach_page_info	= W_AX_ACH0_PAGE_INFO,
	.pub_page_info3	= W_AX_PUB_PAGE_INFO3,
	.pub_page_ctww1	= W_AX_PUB_PAGE_CTWW1,
	.pub_page_ctww2	= W_AX_PUB_PAGE_CTWW2,
	.pub_page_info1	= W_AX_PUB_PAGE_INFO1,
	.pub_page_info2 = W_AX_PUB_PAGE_INFO2,
	.wp_page_ctww1	= W_AX_WP_PAGE_CTWW1,
	.wp_page_ctww2	= W_AX_WP_PAGE_CTWW2,
	.wp_page_info1	= W_AX_WP_PAGE_INFO1,
};

static const stwuct wtw89_weg_def wtw8851b_dcfo_comp = {
	W_DCFO_COMP_S0_V2, B_DCFO_COMP_S0_MSK_V2
};

static const stwuct wtw89_imw_info wtw8851b_imw_info = {
	.wdwws_imw_set		= B_AX_WDWWS_IMW_SET,
	.wsec_imw_weg		= W_AX_SEC_DEBUG,
	.wsec_imw_set		= B_AX_IMW_EWWOW,
	.mpdu_tx_imw_set	= 0,
	.mpdu_wx_imw_set	= 0,
	.sta_sch_imw_set	= B_AX_STA_SCHEDUWEW_IMW_SET,
	.txpktctw_imw_b0_weg	= W_AX_TXPKTCTW_EWW_IMW_ISW,
	.txpktctw_imw_b0_cww	= B_AX_TXPKTCTW_IMW_B0_CWW,
	.txpktctw_imw_b0_set	= B_AX_TXPKTCTW_IMW_B0_SET,
	.txpktctw_imw_b1_weg	= W_AX_TXPKTCTW_EWW_IMW_ISW_B1,
	.txpktctw_imw_b1_cww	= B_AX_TXPKTCTW_IMW_B1_CWW,
	.txpktctw_imw_b1_set	= B_AX_TXPKTCTW_IMW_B1_SET,
	.wde_imw_cww		= B_AX_WDE_IMW_CWW,
	.wde_imw_set		= B_AX_WDE_IMW_SET,
	.pwe_imw_cww		= B_AX_PWE_IMW_CWW,
	.pwe_imw_set		= B_AX_PWE_IMW_SET,
	.host_disp_imw_cww	= B_AX_HOST_DISP_IMW_CWW,
	.host_disp_imw_set	= B_AX_HOST_DISP_IMW_SET,
	.cpu_disp_imw_cww	= B_AX_CPU_DISP_IMW_CWW,
	.cpu_disp_imw_set	= B_AX_CPU_DISP_IMW_SET,
	.othew_disp_imw_cww	= B_AX_OTHEW_DISP_IMW_CWW,
	.othew_disp_imw_set	= 0,
	.bbwpt_com_eww_imw_weg	= W_AX_BBWPT_COM_EWW_IMW_ISW,
	.bbwpt_chinfo_eww_imw_weg = W_AX_BBWPT_CHINFO_EWW_IMW_ISW,
	.bbwpt_eww_imw_set	= 0,
	.bbwpt_dfs_eww_imw_weg	= W_AX_BBWPT_DFS_EWW_IMW_ISW,
	.ptcw_imw_cww		= B_AX_PTCW_IMW_CWW_AWW,
	.ptcw_imw_set		= B_AX_PTCW_IMW_SET,
	.cdma_imw_0_weg		= W_AX_DWE_CTWW,
	.cdma_imw_0_cww		= B_AX_DWE_IMW_CWW,
	.cdma_imw_0_set		= B_AX_DWE_IMW_SET,
	.cdma_imw_1_weg		= 0,
	.cdma_imw_1_cww		= 0,
	.cdma_imw_1_set		= 0,
	.phy_intf_imw_weg	= W_AX_PHYINFO_EWW_IMW,
	.phy_intf_imw_cww	= 0,
	.phy_intf_imw_set	= 0,
	.wmac_imw_weg		= W_AX_WMAC_EWW_ISW,
	.wmac_imw_cww		= B_AX_WMAC_IMW_CWW,
	.wmac_imw_set		= B_AX_WMAC_IMW_SET,
	.tmac_imw_weg		= W_AX_TMAC_EWW_IMW_ISW,
	.tmac_imw_cww		= B_AX_TMAC_IMW_CWW,
	.tmac_imw_set		= B_AX_TMAC_IMW_SET,
};

static const stwuct wtw89_xtaw_info wtw8851b_xtaw_info = {
	.xcap_weg		= W_AX_XTAW_ON_CTWW3,
	.sc_xo_mask		= B_AX_XTAW_SC_XO_A_BWOCK_MASK,
	.sc_xi_mask		= B_AX_XTAW_SC_XI_A_BWOCK_MASK,
};

static const stwuct wtw89_wwsw_cfgs wtw8851b_wwsw_cfgs = {
	.wef_wate = {W_AX_TWXPTCW_WWSW_CTW_0, B_AX_WMAC_WESP_WEF_WATE_SEW, 0},
	.wsc = {W_AX_TWXPTCW_WWSW_CTW_0, B_AX_WMAC_WESP_WSC_MASK, 2},
};

static const stwuct wtw89_dig_wegs wtw8851b_dig_wegs = {
	.seg0_pd_weg = W_SEG0W_PD_V1,
	.pd_wowew_bound_mask = B_SEG0W_PD_WOWEW_BOUND_MSK,
	.pd_spatiaw_weuse_en = B_SEG0W_PD_SPATIAW_WEUSE_EN_MSK_V1,
	.bmode_pd_weg = W_BMODE_PDTH_EN_V1,
	.bmode_cca_wssi_wimit_en = B_BMODE_PDTH_WIMIT_EN_MSK_V1,
	.bmode_pd_wowew_bound_weg = W_BMODE_PDTH_V1,
	.bmode_wssi_nocca_wow_th_mask = B_BMODE_PDTH_WOWEW_BOUND_MSK_V1,
	.p0_wna_init = {W_PATH0_WNA_INIT_V1, B_PATH0_WNA_INIT_IDX_MSK},
	.p1_wna_init = {W_PATH1_WNA_INIT_V1, B_PATH1_WNA_INIT_IDX_MSK},
	.p0_tia_init = {W_PATH0_TIA_INIT_V1, B_PATH0_TIA_INIT_IDX_MSK_V1},
	.p1_tia_init = {W_PATH1_TIA_INIT_V1, B_PATH1_TIA_INIT_IDX_MSK_V1},
	.p0_wxb_init = {W_PATH0_WXB_INIT_V1, B_PATH0_WXB_INIT_IDX_MSK_V1},
	.p1_wxb_init = {W_PATH1_WXB_INIT_V1, B_PATH1_WXB_INIT_IDX_MSK_V1},
	.p0_p20_pagcugc_en = {W_PATH0_P20_FOWWOW_BY_PAGCUGC_V2,
			      B_PATH0_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p0_s20_pagcugc_en = {W_PATH0_S20_FOWWOW_BY_PAGCUGC_V2,
			      B_PATH0_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_p20_pagcugc_en = {W_PATH1_P20_FOWWOW_BY_PAGCUGC_V2,
			      B_PATH1_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_s20_pagcugc_en = {W_PATH1_S20_FOWWOW_BY_PAGCUGC_V2,
			      B_PATH1_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
};

static const stwuct wtw89_edcca_wegs wtw8851b_edcca_wegs = {
	.edcca_wevew			= W_SEG0W_EDCCA_WVW_V1,
	.edcca_mask			= B_EDCCA_WVW_MSK0,
	.edcca_p_mask			= B_EDCCA_WVW_MSK1,
	.ppdu_wevew			= W_SEG0W_EDCCA_WVW_V1,
	.ppdu_mask			= B_EDCCA_WVW_MSK3,
	.wpt_a				= W_EDCCA_WPT_A,
	.wpt_b				= W_EDCCA_WPT_B,
	.wpt_sew			= W_EDCCA_WPT_SEW,
	.wpt_sew_mask			= B_EDCCA_WPT_SEW_MSK,
	.tx_cowwision_t2w_st		= W_TX_COWWISION_T2W_ST,
	.tx_cowwision_t2w_st_mask	= B_TX_COWWISION_T2W_ST_M,
};

static const stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8851b_wf_uw[] = {
	{255, 0, 0, 7}, /* 0 -> owiginaw */
	{255, 2, 0, 7}, /* 1 -> fow BT-connected ACI issue && BTG co-wx */
	{255, 0, 0, 7}, /* 2 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 3- >wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 4 ->wesewved fow shawed-antenna */
	{255, 1, 0, 7}, /* the bewow id is fow non-shawed-antenna fwee-wun */
	{6, 1, 0, 7},
	{13, 1, 0, 7},
	{13, 1, 0, 7}
};

static const stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8851b_wf_dw[] = {
	{255, 0, 0, 7}, /* 0 -> owiginaw */
	{255, 2, 0, 7}, /* 1 -> wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 2 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 3- >wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 4 ->wesewved fow shawed-antenna */
	{255, 1, 0, 7}, /* the bewow id is fow non-shawed-antenna fwee-wun */
	{255, 1, 0, 7},
	{255, 1, 0, 7},
	{255, 1, 0, 7}
};

static const stwuct wtw89_btc_fbtc_mweg wtw89_btc_8851b_mon_weg[] = {
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda24),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda28),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda2c),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda30),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda4c),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda10),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda20),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda34),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xcef4),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0x8424),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xd200),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xd220),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x980),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x4738),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x4688),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x4694),
};

static const u8 wtw89_btc_8851b_ww_wssi_thwes[BTC_WW_WSSI_THMAX] = {70, 60, 50, 40};
static const u8 wtw89_btc_8851b_bt_wssi_thwes[BTC_BT_WSSI_THMAX] = {50, 40, 30, 20};

static int wtw8851b_pww_on_func(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	u8 vaw8;
	u32 wet;

	wtw89_wwite32_cww(wtwdev, W_AX_SYS_PW_CTWW, B_AX_AFSM_WWSUS_EN |
						    B_AX_AFSM_PCIE_SUS_EN);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_DIS_WWBT_PDNSUSEN_SOPC);
	wtw89_wwite32_set(wtwdev, W_AX_WWWPS_CTWW, B_AX_DIS_WWBT_WPSEN_WOPC);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APDM_HPDN);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFM_SWWPS);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, vaw32 & B_AX_WDY_SYSPWW,
				1000, 20000, fawse, wtwdev, W_AX_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_EN_WWON);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFN_ONMAC);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_AX_APFN_ONMAC),
				1000, 20000, fawse, wtwdev, W_AX_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite8_set(wtwdev, W_AX_PWATFOWM_ENABWE, B_AX_PWATFOWM_EN);
	wtw89_wwite8_cww(wtwdev, W_AX_PWATFOWM_ENABWE, B_AX_PWATFOWM_EN);
	wtw89_wwite8_set(wtwdev, W_AX_PWATFOWM_ENABWE, B_AX_PWATFOWM_EN);
	wtw89_wwite8_cww(wtwdev, W_AX_PWATFOWM_ENABWE, B_AX_PWATFOWM_EN);

	wtw89_wwite8_set(wtwdev, W_AX_PWATFOWM_ENABWE, B_AX_PWATFOWM_EN);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_SDIO_CTWW, B_AX_PCIE_CAWIB_EN_V1);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_OFF_WEI,
				      XTAW_SI_OFF_WEI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_OFF_EI,
				      XTAW_SI_OFF_EI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_WFC2WF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_PON_WEI,
				      XTAW_SI_PON_WEI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_PON_EI,
				      XTAW_SI_PON_EI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_SWAM2WFC);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_SWAM_CTWW, 0, XTAW_SI_SWAM_DIS);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XTAW_XMD_2, 0, XTAW_SI_WDO_WPS);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XTAW_XMD_4, 0, XTAW_SI_WPS_CAP);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XTAW_DWV, 0, XTAW_SI_DWV_WATCH);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_PMC_DBG_CTWW2, B_AX_SYSON_DIS_PMCW_AX_WWMSK);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_ISO_EB2COWE);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_PWC_EV2EF_B15);

	fsweep(1000);

	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_PWC_EV2EF_B14);
	wtw89_wwite32_cww(wtwdev, W_AX_PMC_DBG_CTWW2, B_AX_SYSON_DIS_PMCW_AX_WWMSK);
	wtw89_wwite32_set(wtwdev, W_AX_GPIO0_16_EECS_EESK_WED1_PUWW_WOW_EN,
			  B_AX_GPIO10_PUWW_WOW_EN | B_AX_GPIO16_PUWW_WOW_EN_V1);

	if (wtwdev->haw.cv == CHIP_CAV) {
		wet = wtw89_wead_efuse_vew(wtwdev, &vaw8);
		if (!wet)
			wtwdev->haw.cv = vaw8;
	}

	wtw89_wwite32_cww(wtwdev, W_AX_WWAN_XTAW_SI_CONFIG,
			  B_AX_XTAW_SI_ADDW_NOT_CHK);
	if (wtwdev->haw.cv != CHIP_CAV) {
		wtw89_wwite32_set(wtwdev, W_AX_SPSWDO_ON_CTWW1, B_AX_FPWMDEWAY);
		wtw89_wwite32_set(wtwdev, W_AX_SPSANA_ON_CTWW1, B_AX_FPWMDEWAY);
	}

	wtw89_wwite32_set(wtwdev, W_AX_DMAC_FUNC_EN,
			  B_AX_MAC_FUNC_EN | B_AX_DMAC_FUNC_EN | B_AX_MPDU_PWOC_EN |
			  B_AX_WD_WWS_EN | B_AX_DWE_WDE_EN | B_AX_TXPKT_CTWW_EN |
			  B_AX_STA_SCH_EN | B_AX_DWE_PWE_EN | B_AX_PKT_BUF_EN |
			  B_AX_DMAC_TBW_EN | B_AX_PKT_IN_EN | B_AX_DWE_CPUIO_EN |
			  B_AX_DISPATCHEW_EN | B_AX_BBWPT_EN | B_AX_MAC_SEC_EN |
			  B_AX_DMACWEG_GCKEN);
	wtw89_wwite32_set(wtwdev, W_AX_CMAC_FUNC_EN,
			  B_AX_CMAC_EN | B_AX_CMAC_TXEN | B_AX_CMAC_WXEN |
			  B_AX_FOWCE_CMACWEG_GCKEN | B_AX_PHYINTF_EN | B_AX_CMAC_DMA_EN |
			  B_AX_PTCWTOP_EN | B_AX_SCHEDUWEW_EN | B_AX_TMAC_EN |
			  B_AX_WMAC_EN);

	wtw89_wwite32_mask(wtwdev, W_AX_EECS_EESK_FUNC_SEW, B_AX_PINMUX_EESK_FUNC_SEW_MASK,
			   PINMUX_EESK_FUNC_SEW_BT_WOG);

	wetuwn 0;
}

static void wtw8851b_patch_sww_pfm2pwm(stwuct wtw89_dev *wtwdev)
{
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_SOP_PWMM_DSWW);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_SOP_ASWWM);
	wtw89_wwite32_set(wtwdev, W_AX_WWWPS_CTWW, B_AX_WPSOP_DSWWM);
	wtw89_wwite32_set(wtwdev, W_AX_WWWPS_CTWW, B_AX_WPSOP_ASWWM);
}

static int wtw8851b_pww_off_func(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	u32 wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_WFC2WF,
				      XTAW_SI_WFC2WF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_OFF_EI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_OFF_WEI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, 0, XTAW_SI_WF00);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, XTAW_SI_SWAM2WFC,
				      XTAW_SI_SWAM2WFC);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_PON_EI);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_PON_WEI);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_WWAN_XTAW_SI_CONFIG,
			  B_AX_XTAW_SI_ADDW_NOT_CHK);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_EN_WWON);
	wtw89_wwite32_cww(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);
	wtw89_wwite8_cww(wtwdev, W_AX_SYS_FUNC_EN, B_AX_FEN_BB_GWB_WSTN | B_AX_FEN_BBWSTB);

	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFM_OFFMAC);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_AX_APFM_OFFMAC),
				1000, 20000, fawse, wtwdev, W_AX_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32(wtwdev, W_AX_WWWPS_CTWW, SW_WPS_OPTION);

	if (wtwdev->haw.cv == CHIP_CAV) {
		wtw8851b_patch_sww_pfm2pwm(wtwdev);
	} ewse {
		wtw89_wwite32_set(wtwdev, W_AX_SPSWDO_ON_CTWW1, B_AX_FPWMDEWAY);
		wtw89_wwite32_set(wtwdev, W_AX_SPSANA_ON_CTWW1, B_AX_FPWMDEWAY);
	}

	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFM_SWWPS);

	wetuwn 0;
}

static void wtw8851b_efuse_pawsing(stwuct wtw89_efuse *efuse,
				   stwuct wtw8851b_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->e.mac_addw);
	efuse->wfe_type = map->wfe_type;
	efuse->xtaw_cap = map->xtaw_k;
}

static void wtw8851b_efuse_pawsing_tssi(stwuct wtw89_dev *wtwdev,
					stwuct wtw8851b_efuse *map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	stwuct wtw8851b_tssi_offset *ofst[] = {&map->path_a_tssi};
	u8 i, j;

	tssi->thewmaw[WF_PATH_A] = map->path_a_thewm;

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		memcpy(tssi->tssi_cck[i], ofst[i]->cck_tssi,
		       sizeof(ofst[i]->cck_tssi));

		fow (j = 0; j < TSSI_CCK_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI][EFUSE] path=%d cck[%d]=0x%x\n",
				    i, j, tssi->tssi_cck[i][j]);

		memcpy(tssi->tssi_mcs[i], ofst[i]->bw40_tssi,
		       sizeof(ofst[i]->bw40_tssi));
		memcpy(tssi->tssi_mcs[i] + TSSI_MCS_2G_CH_GWOUP_NUM,
		       ofst[i]->bw40_1s_tssi_5g, sizeof(ofst[i]->bw40_1s_tssi_5g));

		fow (j = 0; j < TSSI_MCS_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI][EFUSE] path=%d mcs[%d]=0x%x\n",
				    i, j, tssi->tssi_mcs[i][j]);
	}
}

static boow _decode_efuse_gain(u8 data, s8 *high, s8 *wow)
{
	if (high)
		*high = sign_extend32(u8_get_bits(data, GENMASK(7,  4)), 3);
	if (wow)
		*wow = sign_extend32(u8_get_bits(data, GENMASK(3,  0)), 3);

	wetuwn data != 0xff;
}

static void wtw8851b_efuse_pawsing_gain_offset(stwuct wtw89_dev *wtwdev,
					       stwuct wtw8851b_efuse *map)
{
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;
	boow vawid = fawse;

	vawid |= _decode_efuse_gain(map->wx_gain_2g_cck,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_CCK],
				    NUWW);
	vawid |= _decode_efuse_gain(map->wx_gain_2g_ofdm,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_OFDM],
				    NUWW);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_wow,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_WOW],
				    NUWW);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_mid,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_MID],
				   NUWW);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_high,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_HIGH],
				    NUWW);

	gain->offset_vawid = vawid;
}

static int wtw8851b_wead_efuse(stwuct wtw89_dev *wtwdev, u8 *wog_map,
			       enum wtw89_efuse_bwock bwock)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	stwuct wtw8851b_efuse *map;

	map = (stwuct wtw8851b_efuse *)wog_map;

	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	wtw8851b_efuse_pawsing_tssi(wtwdev, map);
	wtw8851b_efuse_pawsing_gain_offset(wtwdev, map);

	switch (wtwdev->hci.type) {
	case WTW89_HCI_TYPE_PCIE:
		wtw8851b_efuse_pawsing(efuse, map);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wtw89_info(wtwdev, "chip wfe_type is %d\n", efuse->wfe_type);

	wetuwn 0;
}

static void wtw8851b_phycap_pawsing_tssi(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	static const u32 tssi_twim_addw[WF_PATH_NUM_8851B] = {0x5D6};
	u32 addw = wtwdev->chip->phycap_addw;
	boow pg = fawse;
	u32 ofst;
	u8 i, j;

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM; j++) {
			/* addws awe in decweasing owdew */
			ofst = tssi_twim_addw[i] - addw - j;
			tssi->tssi_twim[i][j] = phycap_map[ofst];

			if (phycap_map[ofst] != 0xff)
				pg = twue;
		}
	}

	if (!pg) {
		memset(tssi->tssi_twim, 0, sizeof(tssi->tssi_twim));
		wtw89_debug(wtwdev, WTW89_DBG_TSSI,
			    "[TSSI][TWIM] no PG, set aww twim info to 0\n");
	}

	fow (i = 0; i < WF_PATH_NUM_8851B; i++)
		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI] path=%d idx=%d twim=0x%x addw=0x%x\n",
				    i, j, tssi->tssi_twim[i][j],
				    tssi_twim_addw[i] - j);
}

static void wtw8851b_phycap_pawsing_thewmaw_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 thm_twim_addw[WF_PATH_NUM_8851B] = {0x5DF};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		info->thewmaw_twim[i] = phycap_map[thm_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_twim=0x%x\n",
			    i, info->thewmaw_twim[i]);

		if (info->thewmaw_twim[i] != 0xff)
			info->pg_thewmaw_twim = twue;
	}
}

static void wtw8851b_thewmaw_twim(stwuct wtw89_dev *wtwdev)
{
#define __thm_setting(waw)				\
({							\
	u8 __v = (waw);					\
	((__v & 0x1) << 3) | ((__v & 0x1f) >> 1);	\
})
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u8 i, vaw;

	if (!info->pg_thewmaw_twim) {
		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] no PG, do nothing\n");

		wetuwn;
	}

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		vaw = __thm_setting(info->thewmaw_twim[i]);
		wtw89_wwite_wf(wtwdev, i, WW_TM2, WW_TM2_OFF, vaw);

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_setting=0x%x\n",
			    i, vaw);
	}
#undef __thm_setting
}

static void wtw8851b_phycap_pawsing_pa_bias_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 pabias_twim_addw[] = {0x5DE};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		info->pa_bias_twim[i] = phycap_map[pabias_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d pa_bias_twim=0x%x\n",
			    i, info->pa_bias_twim[i]);

		if (info->pa_bias_twim[i] != 0xff)
			info->pg_pa_bias_twim = twue;
	}
}

static void wtw8851b_pa_bias_twim(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u8 pabias_2g, pabias_5g;
	u8 i;

	if (!info->pg_pa_bias_twim) {
		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] no PG, do nothing\n");

		wetuwn;
	}

	fow (i = 0; i < WF_PATH_NUM_8851B; i++) {
		pabias_2g = u8_get_bits(info->pa_bias_twim[i], GENMASK(3, 0));
		pabias_5g = u8_get_bits(info->pa_bias_twim[i], GENMASK(7, 4));

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d 2G=0x%x 5G=0x%x\n",
			    i, pabias_2g, pabias_5g);

		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXG, pabias_2g);
		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXA, pabias_5g);
	}
}

static void wtw8851b_phycap_pawsing_gain_comp(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	static const u32 comp_addws[][WTW89_SUBBAND_2GHZ_5GHZ_NW] = {
		{0x5BB, 0x5BA, 0, 0x5B9, 0x5B8},
	};
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;
	u32 phycap_addw = wtwdev->chip->phycap_addw;
	boow vawid = fawse;
	int path, i;
	u8 data;

	fow (path = 0; path < BB_PATH_NUM_8851B; path++)
		fow (i = 0; i < WTW89_SUBBAND_2GHZ_5GHZ_NW; i++) {
			if (comp_addws[path][i] == 0)
				continue;

			data = phycap_map[comp_addws[path][i] - phycap_addw];
			vawid |= _decode_efuse_gain(data, NUWW,
						    &gain->comp[path][i]);
		}

	gain->comp_vawid = vawid;
}

static int wtw8851b_wead_phycap(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	wtw8851b_phycap_pawsing_tssi(wtwdev, phycap_map);
	wtw8851b_phycap_pawsing_thewmaw_twim(wtwdev, phycap_map);
	wtw8851b_phycap_pawsing_pa_bias_twim(wtwdev, phycap_map);
	wtw8851b_phycap_pawsing_gain_comp(wtwdev, phycap_map);

	wetuwn 0;
}

static void wtw8851b_set_bb_gpio(stwuct wtw89_dev *wtwdev, u8 gpio_idx, boow inv,
				 u8 swc_sew)
{
	u32 addw, mask;

	if (gpio_idx >= 32)
		wetuwn;

	/* 2 continuaw 32-bit wegistews fow 32 GPIOs, and each GPIO occupies 2 bits */
	addw = W_WFE_SEW0_A2 + (gpio_idx / 16) * sizeof(u32);
	mask = B_WFE_SEW0_MASK << (gpio_idx % 16) * 2;

	wtw89_phy_wwite32_mask(wtwdev, addw, mask, WF_PATH_A);
	wtw89_phy_wwite32_mask(wtwdev, W_WFE_INV0, BIT(gpio_idx), inv);

	/* 4 continuaw 32-bit wegistews fow 32 GPIOs, and each GPIO occupies 4 bits */
	addw = W_WFE_SEW0_BASE + (gpio_idx / 8) * sizeof(u32);
	mask = B_WFE_SEW0_SWC_MASK << (gpio_idx % 8) * 4;

	wtw89_phy_wwite32_mask(wtwdev, addw, mask, swc_sew);
}

static void wtw8851b_set_mac_gpio(stwuct wtw89_dev *wtwdev, u8 func)
{
	static const stwuct wtw89_weg3_def func16 = {
		W_AX_GPIO16_23_FUNC_SEW, B_AX_PINMUX_GPIO16_FUNC_SEW_MASK, BIT(3)
	};
	static const stwuct wtw89_weg3_def func17 = {
		W_AX_GPIO16_23_FUNC_SEW, B_AX_PINMUX_GPIO17_FUNC_SEW_MASK, BIT(7) >> 4,
	};
	const stwuct wtw89_weg3_def *def;

	switch (func) {
	case 16:
		def = &func16;
		bweak;
	case 17:
		def = &func17;
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "undefined gpio func %d\n", func);
		wetuwn;
	}

	wtw89_wwite8_mask(wtwdev, def->addw, def->mask, def->data);
}

static void wtw8851b_wfe_gpio(stwuct wtw89_dev *wtwdev)
{
	u8 wfe_type = wtwdev->efuse.wfe_type;

	if (wfe_type > 50)
		wetuwn;

	if (wfe_type % 3 == 2) {
		wtw8851b_set_bb_gpio(wtwdev, 16, twue, WFE_SEW0_SWC_ANTSEW_0);
		wtw8851b_set_bb_gpio(wtwdev, 17, fawse, WFE_SEW0_SWC_ANTSEW_0);

		wtw8851b_set_mac_gpio(wtwdev, 16);
		wtw8851b_set_mac_gpio(wtwdev, 17);
	}
}

static void wtw8851b_powew_twim(stwuct wtw89_dev *wtwdev)
{
	wtw8851b_thewmaw_twim(wtwdev);
	wtw8851b_pa_bias_twim(wtwdev);
}

static void wtw8851b_set_channew_mac(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_chan *chan,
				     u8 mac_idx)
{
	u32 sub_caww = wtw89_mac_weg_by_idx(wtwdev, W_AX_TX_SUB_CAWWIEW_VAWUE, mac_idx);
	u32 chk_wate = wtw89_mac_weg_by_idx(wtwdev, W_AX_TXWATE_CHK, mac_idx);
	u32 wf_mod = wtw89_mac_weg_by_idx(wtwdev, W_AX_WMAC_WFMOD, mac_idx);
	u8 txsc20 = 0, txsc40 = 0;

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_80:
		txsc40 = wtw89_phy_get_txsc(wtwdev, chan, WTW89_CHANNEW_WIDTH_40);
		fawwthwough;
	case WTW89_CHANNEW_WIDTH_40:
		txsc20 = wtw89_phy_get_txsc(wtwdev, chan, WTW89_CHANNEW_WIDTH_20);
		bweak;
	defauwt:
		bweak;
	}

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_wwite8_mask(wtwdev, wf_mod, B_AX_WMAC_WFMOD_MASK, BIT(1));
		wtw89_wwite32(wtwdev, sub_caww, txsc20 | (txsc40 << 4));
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_wwite8_mask(wtwdev, wf_mod, B_AX_WMAC_WFMOD_MASK, BIT(0));
		wtw89_wwite32(wtwdev, sub_caww, txsc20);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
		wtw89_wwite8_cww(wtwdev, wf_mod, B_AX_WMAC_WFMOD_MASK);
		wtw89_wwite32(wtwdev, sub_caww, 0);
		bweak;
	defauwt:
		bweak;
	}

	if (chan->channew > 14) {
		wtw89_wwite8_cww(wtwdev, chk_wate, B_AX_BAND_MODE);
		wtw89_wwite8_set(wtwdev, chk_wate,
				 B_AX_CHECK_CCK_EN | B_AX_WTS_WIMIT_IN_OFDM6);
	} ewse {
		wtw89_wwite8_set(wtwdev, chk_wate, B_AX_BAND_MODE);
		wtw89_wwite8_cww(wtwdev, chk_wate,
				 B_AX_CHECK_CCK_EN | B_AX_WTS_WIMIT_IN_OFDM6);
	}
}

static const u32 wtw8851b_sco_bawkew_thweshowd[14] = {
	0x1cfea, 0x1d0e1, 0x1d1d7, 0x1d2cd, 0x1d3c3, 0x1d4b9, 0x1d5b0, 0x1d6a6,
	0x1d79c, 0x1d892, 0x1d988, 0x1da7f, 0x1db75, 0x1ddc4
};

static const u32 wtw8851b_sco_cck_thweshowd[14] = {
	0x27de3, 0x27f35, 0x28088, 0x281da, 0x2832d, 0x2847f, 0x285d2, 0x28724,
	0x28877, 0x289c9, 0x28b1c, 0x28c6e, 0x28dc1, 0x290ed
};

static void wtw8851b_ctww_sco_cck(stwuct wtw89_dev *wtwdev, u8 pwimawy_ch)
{
	u8 ch_ewement = pwimawy_ch - 1;

	wtw89_phy_wwite32_mask(wtwdev, W_WXSCOBC, B_WXSCOBC_TH,
			       wtw8851b_sco_bawkew_thweshowd[ch_ewement]);
	wtw89_phy_wwite32_mask(wtwdev, W_WXSCOCCK, B_WXSCOCCK_TH,
			       wtw8851b_sco_cck_thweshowd[ch_ewement]);
}

static u8 wtw8851b_sco_mapping(u8 centwaw_ch)
{
	if (centwaw_ch == 1)
		wetuwn 109;
	ewse if (centwaw_ch >= 2 && centwaw_ch <= 6)
		wetuwn 108;
	ewse if (centwaw_ch >= 7 && centwaw_ch <= 10)
		wetuwn 107;
	ewse if (centwaw_ch >= 11 && centwaw_ch <= 14)
		wetuwn 106;
	ewse if (centwaw_ch == 36 || centwaw_ch == 38)
		wetuwn 51;
	ewse if (centwaw_ch >= 40 && centwaw_ch <= 58)
		wetuwn 50;
	ewse if (centwaw_ch >= 60 && centwaw_ch <= 64)
		wetuwn 49;
	ewse if (centwaw_ch == 100 || centwaw_ch == 102)
		wetuwn 48;
	ewse if (centwaw_ch >= 104 && centwaw_ch <= 126)
		wetuwn 47;
	ewse if (centwaw_ch >= 128 && centwaw_ch <= 151)
		wetuwn 46;
	ewse if (centwaw_ch >= 153 && centwaw_ch <= 177)
		wetuwn 45;
	ewse
		wetuwn 0;
}

stwuct wtw8851b_bb_gain {
	u32 gain_g[BB_PATH_NUM_8851B];
	u32 gain_a[BB_PATH_NUM_8851B];
	u32 gain_mask;
};

static const stwuct wtw8851b_bb_gain bb_gain_wna[WNA_GAIN_NUM] = {
	{ .gain_g = {0x4678}, .gain_a = {0x45DC},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x4678}, .gain_a = {0x45DC},
	  .gain_mask = 0xff000000 },
	{ .gain_g = {0x467C}, .gain_a = {0x4660},
	  .gain_mask = 0x000000ff },
	{ .gain_g = {0x467C}, .gain_a = {0x4660},
	  .gain_mask = 0x0000ff00 },
	{ .gain_g = {0x467C}, .gain_a = {0x4660},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x467C}, .gain_a = {0x4660},
	  .gain_mask = 0xff000000 },
	{ .gain_g = {0x4680}, .gain_a = {0x4664},
	  .gain_mask = 0x000000ff },
};

static const stwuct wtw8851b_bb_gain bb_gain_tia[TIA_GAIN_NUM] = {
	{ .gain_g = {0x4680}, .gain_a = {0x4664},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x4680}, .gain_a = {0x4664},
	  .gain_mask = 0xff000000 },
};

static void wtw8851b_set_gain_ewwow(stwuct wtw89_dev *wtwdev,
				    enum wtw89_subband subband,
				    enum wtw89_wf_path path)
{
	const stwuct wtw89_phy_bb_gain_info *gain = &wtwdev->bb_gain;
	u8 gain_band = wtw89_subband_to_bb_gain_band(subband);
	s32 vaw;
	u32 weg;
	u32 mask;
	int i;

	fow (i = 0; i < WNA_GAIN_NUM; i++) {
		if (subband == WTW89_CH_2G)
			weg = bb_gain_wna[i].gain_g[path];
		ewse
			weg = bb_gain_wna[i].gain_a[path];

		mask = bb_gain_wna[i].gain_mask;
		vaw = gain->wna_gain[gain_band][path][i];
		wtw89_phy_wwite32_mask(wtwdev, weg, mask, vaw);
	}

	fow (i = 0; i < TIA_GAIN_NUM; i++) {
		if (subband == WTW89_CH_2G)
			weg = bb_gain_tia[i].gain_g[path];
		ewse
			weg = bb_gain_tia[i].gain_a[path];

		mask = bb_gain_tia[i].gain_mask;
		vaw = gain->tia_gain[gain_band][path][i];
		wtw89_phy_wwite32_mask(wtwdev, weg, mask, vaw);
	}
}

static void wtw8851b_set_gain_offset(stwuct wtw89_dev *wtwdev,
				     enum wtw89_subband subband,
				     enum wtw89_phy_idx phy_idx)
{
	static const u32 wssi_ofst_addw[] = {W_PATH0_G_TIA1_WNA6_OP1DB_V1};
	static const u32 gain_eww_addw[] = {W_P0_AGC_WSVD};
	stwuct wtw89_phy_efuse_gain *efuse_gain = &wtwdev->efuse_gain;
	enum wtw89_gain_offset gain_ofdm_band;
	s32 offset_ofdm, offset_cck;
	s32 offset_a;
	s32 tmp;
	u8 path;

	if (!efuse_gain->comp_vawid)
		goto next;

	fow (path = WF_PATH_A; path < BB_PATH_NUM_8851B; path++) {
		tmp = efuse_gain->comp[path][subband];
		tmp = cwamp_t(s32, tmp << 2, S8_MIN, S8_MAX);
		wtw89_phy_wwite32_mask(wtwdev, gain_eww_addw[path], MASKBYTE0, tmp);
	}

next:
	if (!efuse_gain->offset_vawid)
		wetuwn;

	gain_ofdm_band = wtw89_subband_to_gain_offset_band_of_ofdm(subband);

	offset_a = -efuse_gain->offset[WF_PATH_A][gain_ofdm_band];

	tmp = -((offset_a << 2) + (efuse_gain->offset_base[WTW89_PHY_0] >> 2));
	tmp = cwamp_t(s32, tmp, S8_MIN, S8_MAX);
	wtw89_phy_wwite32_mask(wtwdev, wssi_ofst_addw[WF_PATH_A], B_PATH0_W_G_OFST_MASK, tmp);

	offset_ofdm = -efuse_gain->offset[WF_PATH_A][gain_ofdm_band];
	offset_cck = -efuse_gain->offset[WF_PATH_A][0];

	tmp = (offset_ofdm << 4) + efuse_gain->offset_base[WTW89_PHY_0];
	tmp = cwamp_t(s32, tmp, S8_MIN, S8_MAX);
	wtw89_phy_wwite32_idx(wtwdev, W_P0_WPW1, B_P0_WPW1_BIAS_MASK, tmp, phy_idx);

	tmp = (offset_ofdm << 4) + efuse_gain->wssi_base[WTW89_PHY_0];
	tmp = cwamp_t(s32, tmp, S8_MIN, S8_MAX);
	wtw89_phy_wwite32_idx(wtwdev, W_P1_WPW1, B_P0_WPW1_BIAS_MASK, tmp, phy_idx);

	if (subband == WTW89_CH_2G) {
		tmp = (offset_cck << 3) + (efuse_gain->offset_base[WTW89_PHY_0] >> 1);
		tmp = cwamp_t(s32, tmp, S8_MIN >> 1, S8_MAX >> 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WX_WPW_OFST,
				       B_WX_WPW_OFST_CCK_MASK, tmp);
	}
}

static
void wtw8851b_set_wxsc_wpw_comp(stwuct wtw89_dev *wtwdev, enum wtw89_subband subband)
{
	const stwuct wtw89_phy_bb_gain_info *gain = &wtwdev->bb_gain;
	u8 band = wtw89_subband_to_bb_gain_band(subband);
	u32 vaw;

	vaw = u32_encode_bits(gain->wpw_ofst_20[band][WF_PATH_A], B_P0_WPW1_20_MASK) |
	      u32_encode_bits(gain->wpw_ofst_40[band][WF_PATH_A][0], B_P0_WPW1_40_MASK) |
	      u32_encode_bits(gain->wpw_ofst_40[band][WF_PATH_A][1], B_P0_WPW1_41_MASK);
	vaw >>= B_P0_WPW1_SHIFT;
	wtw89_phy_wwite32_mask(wtwdev, W_P0_WPW1, B_P0_WPW1_MASK, vaw);
	wtw89_phy_wwite32_mask(wtwdev, W_P1_WPW1, B_P0_WPW1_MASK, vaw);

	vaw = u32_encode_bits(gain->wpw_ofst_40[band][WF_PATH_A][2], B_P0_WTW2_42_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][0], B_P0_WTW2_80_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][1], B_P0_WTW2_81_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][10], B_P0_WTW2_8A_MASK);
	wtw89_phy_wwite32(wtwdev, W_P0_WPW2, vaw);
	wtw89_phy_wwite32(wtwdev, W_P1_WPW2, vaw);

	vaw = u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][2], B_P0_WTW3_82_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][3], B_P0_WTW3_83_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][4], B_P0_WTW3_84_MASK) |
	      u32_encode_bits(gain->wpw_ofst_80[band][WF_PATH_A][9], B_P0_WTW3_89_MASK);
	wtw89_phy_wwite32(wtwdev, W_P0_WPW3, vaw);
	wtw89_phy_wwite32(wtwdev, W_P1_WPW3, vaw);
}

static void wtw8851b_ctww_ch(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx)
{
	u8 subband = chan->subband_type;
	u8 centwaw_ch = chan->channew;
	boow is_2g = centwaw_ch <= 14;
	u8 sco_comp;

	if (is_2g)
		wtw89_phy_wwite32_idx(wtwdev, W_PATH0_BAND_SEW_V1,
				      B_PATH0_BAND_SEW_MSK_V1, 1, phy_idx);
	ewse
		wtw89_phy_wwite32_idx(wtwdev, W_PATH0_BAND_SEW_V1,
				      B_PATH0_BAND_SEW_MSK_V1, 0, phy_idx);
	/* SCO compensate FC setting */
	sco_comp = wtw8851b_sco_mapping(centwaw_ch);
	wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_INV, sco_comp, phy_idx);

	if (chan->band_type == WTW89_BAND_6G)
		wetuwn;

	/* CCK pawametews */
	if (centwaw_ch == 14) {
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW0, B_TXFIW_C01, 0x3b13ff);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW2, B_TXFIW_C23, 0x1c42de);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW4, B_TXFIW_C45, 0xfdb0ad);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW6, B_TXFIW_C67, 0xf60f6e);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW8, B_TXFIW_C89, 0xfd8f92);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWA, B_TXFIW_CAB, 0x2d011);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWC, B_TXFIW_CCD, 0x1c02c);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWE, B_TXFIW_CEF, 0xfff00a);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW0, B_TXFIW_C01, 0x3d23ff);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW2, B_TXFIW_C23, 0x29b354);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW4, B_TXFIW_C45, 0xfc1c8);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW6, B_TXFIW_C67, 0xfdb053);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW8, B_TXFIW_C89, 0xf86f9a);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWA, B_TXFIW_CAB, 0xfaef92);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWC, B_TXFIW_CCD, 0xfe5fcc);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWE, B_TXFIW_CEF, 0xffdff5);
	}

	wtw8851b_set_gain_ewwow(wtwdev, subband, WF_PATH_A);
	wtw8851b_set_gain_offset(wtwdev, subband, phy_idx);
	wtw8851b_set_wxsc_wpw_comp(wtwdev, subband);
}

static void wtw8851b_bw_setting(stwuct wtw89_dev *wtwdev, u8 bw)
{
	wtw89_phy_wwite32_mask(wtwdev, W_P0_CFCH_BW0, B_P0_CFCH_CTW, 0x8);
	wtw89_phy_wwite32_mask(wtwdev, W_P0_CFCH_BW0, B_P0_CFCH_EN, 0x2);
	wtw89_phy_wwite32_mask(wtwdev, W_P0_CFCH_BW0, B_P0_CFCH_BW0, 0x2);
	wtw89_phy_wwite32_mask(wtwdev, W_P0_CFCH_BW1, B_P0_CFCH_BW1, 0x4);
	wtw89_phy_wwite32_mask(wtwdev, W_DWCK, B_DWCK_MUW, 0xf);
	wtw89_phy_wwite32_mask(wtwdev, W_ADCMOD, B_ADCMOD_WP, 0xa);
	wtw89_phy_wwite32_mask(wtwdev, W_P0_WXCK, B_P0_WXCK_ADJ, 0x92);

	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
		wtw89_phy_wwite32_mask(wtwdev, W_DCIM, B_DCIM_FW, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_WDADC, B_WDADC_SEW, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_ADDCK0D, B_ADDCK_DS, 0x1);
		bweak;
	case WTW89_CHANNEW_WIDTH_10:
		wtw89_phy_wwite32_mask(wtwdev, W_DCIM, B_DCIM_FW, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_WDADC, B_WDADC_SEW, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_ADDCK0D, B_ADDCK_DS, 0x0);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
		wtw89_phy_wwite32_mask(wtwdev, W_DCIM, B_DCIM_FW, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_WDADC, B_WDADC_SEW, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_ADDCK0D, B_ADDCK_DS, 0x0);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_phy_wwite32_mask(wtwdev, W_DCIM, B_DCIM_FW, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_WDADC, B_WDADC_SEW, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_ADDCK0D, B_ADDCK_DS, 0x0);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_phy_wwite32_mask(wtwdev, W_DCIM, B_DCIM_FW, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_WDADC, B_WDADC_SEW, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_ADDCK0D, B_ADDCK_DS, 0x0);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to set ADC\n");
	}
}

static void wtw8851b_ctww_bw(stwuct wtw89_dev *wtwdev, u8 pwi_ch, u8 bw,
			     enum wtw89_phy_idx phy_idx)
{
	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_SET, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_SBW, 0x1, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_PWICH, 0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_10:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_SET, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_SBW, 0x2, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_PWICH, 0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_SET, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_SBW, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_PWICH, 0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_SET, 0x1, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_SBW, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_PWICH,
				      pwi_ch, phy_idx);
		/* CCK pwimawy channew */
		if (pwi_ch == WTW89_SC_20_UPPEW)
			wtw89_phy_wwite32_mask(wtwdev, W_WXSC, B_WXSC_EN, 1);
		ewse
			wtw89_phy_wwite32_mask(wtwdev, W_WXSC, B_WXSC_EN, 0);

		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW_V1, B_FC0_BW_SET, 0x2, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_SBW, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD_V1, B_CHBW_MOD_PWICH,
				      pwi_ch, phy_idx);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to switch bw (bw:%d, pwi ch:%d)\n", bw,
			   pwi_ch);
	}

	wtw8851b_bw_setting(wtwdev, bw);
}

static void wtw8851b_ctww_cck_en(stwuct wtw89_dev *wtwdev, boow cck_en)
{
	if (cck_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_AWBITEW_OFF,
				       B_PD_AWBITEW_OFF, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_CWK_ADC, B_ENABWE_CCK, 1);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_AWBITEW_OFF,
				       B_PD_AWBITEW_OFF, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_CWK_ADC, B_ENABWE_CCK, 0);
	}
}

static u32 wtw8851b_spuw_fweq(stwuct wtw89_dev *wtwdev,
			      const stwuct wtw89_chan *chan)
{
	u8 centew_chan = chan->channew;

	switch (chan->band_type) {
	case WTW89_BAND_5G:
		if (centew_chan == 151 || centew_chan == 153 ||
		    centew_chan == 155 || centew_chan == 163)
			wetuwn 5760;
		ewse if (centew_chan == 54 || centew_chan == 58)
			wetuwn 5280;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

#define CAWWIEW_SPACING_312_5 312500 /* 312.5 kHz */
#define CAWWIEW_SPACING_78_125 78125 /* 78.125 kHz */
#define MAX_TONE_NUM 2048

static void wtw8851b_set_csi_tone_idx(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_phy_idx phy_idx)
{
	u32 spuw_fweq;
	s32 fweq_diff, csi_idx, csi_tone_idx;

	spuw_fweq = wtw8851b_spuw_fweq(wtwdev, chan);
	if (spuw_fweq == 0) {
		wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI_EN_V1, B_SEG0CSI_EN,
				      0, phy_idx);
		wetuwn;
	}

	fweq_diff = (spuw_fweq - chan->fweq) * 1000000;
	csi_idx = s32_div_u32_wound_cwosest(fweq_diff, CAWWIEW_SPACING_78_125);
	s32_div_u32_wound_down(csi_idx, MAX_TONE_NUM, &csi_tone_idx);

	wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI_V1, B_SEG0CSI_IDX,
			      csi_tone_idx, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI_EN_V1, B_SEG0CSI_EN, 1, phy_idx);
}

static const stwuct wtw89_nbi_weg_def wtw8851b_nbi_weg_def = {
	.notch1_idx = {0x46E4, 0xFF},
	.notch1_fwac_idx = {0x46E4, 0xC00},
	.notch1_en = {0x46E4, 0x1000},
	.notch2_idx = {0x47A4, 0xFF},
	.notch2_fwac_idx = {0x47A4, 0xC00},
	.notch2_en = {0x47A4, 0x1000},
};

static void wtw8851b_set_nbi_tone_idx(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_chan *chan)
{
	const stwuct wtw89_nbi_weg_def *nbi = &wtw8851b_nbi_weg_def;
	s32 nbi_fwac_idx, nbi_fwac_tone_idx;
	s32 nbi_idx, nbi_tone_idx;
	boow notch2_chk = fawse;
	u32 spuw_fweq, fc;
	s32 fweq_diff;

	spuw_fweq = wtw8851b_spuw_fweq(wtwdev, chan);
	if (spuw_fweq == 0) {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw,
				       nbi->notch1_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw,
				       nbi->notch2_en.mask, 0);
		wetuwn;
	}

	fc = chan->fweq;
	if (chan->band_width == WTW89_CHANNEW_WIDTH_160) {
		fc = (spuw_fweq > fc) ? fc + 40 : fc - 40;
		if ((fc > spuw_fweq &&
		     chan->channew < chan->pwimawy_channew) ||
		    (fc < spuw_fweq &&
		     chan->channew > chan->pwimawy_channew))
			notch2_chk = twue;
	}

	fweq_diff = (spuw_fweq - fc) * 1000000;
	nbi_idx = s32_div_u32_wound_down(fweq_diff, CAWWIEW_SPACING_312_5,
					 &nbi_fwac_idx);

	if (chan->band_width == WTW89_CHANNEW_WIDTH_20) {
		s32_div_u32_wound_down(nbi_idx + 32, 64, &nbi_tone_idx);
	} ewse {
		u16 tone_pawa = (chan->band_width == WTW89_CHANNEW_WIDTH_40) ?
				128 : 256;

		s32_div_u32_wound_down(nbi_idx, tone_pawa, &nbi_tone_idx);
	}
	nbi_fwac_tone_idx = s32_div_u32_wound_cwosest(nbi_fwac_idx,
						      CAWWIEW_SPACING_78_125);

	if (chan->band_width == WTW89_CHANNEW_WIDTH_160 && notch2_chk) {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_idx.addw,
				       nbi->notch2_idx.mask, nbi_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_fwac_idx.addw,
				       nbi->notch2_fwac_idx.mask, nbi_fwac_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw,
				       nbi->notch2_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw,
				       nbi->notch2_en.mask, 1);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw,
				       nbi->notch1_en.mask, 0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_idx.addw,
				       nbi->notch1_idx.mask, nbi_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_fwac_idx.addw,
				       nbi->notch1_fwac_idx.mask, nbi_fwac_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw,
				       nbi->notch1_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw,
				       nbi->notch1_en.mask, 1);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw,
				       nbi->notch2_en.mask, 0);
	}
}

static void wtw8851b_set_cfw(stwuct wtw89_dev *wtwdev, const stwuct wtw89_chan *chan)
{
	if (chan->band_type == WTW89_BAND_2G &&
	    chan->band_width == WTW89_CHANNEW_WIDTH_20 &&
	    (chan->channew == 1 || chan->channew == 13)) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_CFW,
				       B_PATH0_TX_CFW_WGC0, 0xf8);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_CFW,
				       B_PATH0_TX_CFW_WGC1, 0x120);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_POWAW_CWIPPING,
				       B_PATH0_TX_POWAW_CWIPPING_WGC0, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_POWAW_CWIPPING,
				       B_PATH0_TX_POWAW_CWIPPING_WGC1, 0x3);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_CFW,
				       B_PATH0_TX_CFW_WGC0, 0x120);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_CFW,
				       B_PATH0_TX_CFW_WGC1, 0x3ff);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_POWAW_CWIPPING,
				       B_PATH0_TX_POWAW_CWIPPING_WGC0, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_TX_POWAW_CWIPPING,
				       B_PATH0_TX_POWAW_CWIPPING_WGC1, 0x7);
	}
}

static void wtw8851b_5m_mask(stwuct wtw89_dev *wtwdev, const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx)
{
	u8 pwi_ch = chan->pwi_ch_idx;
	boow mask_5m_wow;
	boow mask_5m_en;

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_40:
		/* Pwich=1: Mask 5M High, Pwich=2: Mask 5M Wow */
		mask_5m_en = twue;
		mask_5m_wow = pwi_ch == WTW89_SC_20_WOWEW;
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		/* Pwich=3: Mask 5M High, Pwich=4: Mask 5M Wow, Ewse: Disabwe */
		mask_5m_en = pwi_ch == WTW89_SC_20_UPMOST ||
			     pwi_ch == WTW89_SC_20_WOWEST;
		mask_5m_wow = pwi_ch == WTW89_SC_20_WOWEST;
		bweak;
	defauwt:
		mask_5m_en = fawse;
		bweak;
	}

	if (!mask_5m_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_EN, 0x0);
		wtw89_phy_wwite32_idx(wtwdev, W_ASSIGN_SBD_OPT_V1,
				      B_ASSIGN_SBD_OPT_EN_V1, 0x0, phy_idx);
		wetuwn;
	}

	if (mask_5m_wow) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_TH, 0x5);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_SB2, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_SB0, 0x1);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_TH, 0x5);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_SB2, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET_V1, B_PATH0_5MDET_SB0, 0x0);
	}
	wtw89_phy_wwite32_idx(wtwdev, W_ASSIGN_SBD_OPT_V1,
			      B_ASSIGN_SBD_OPT_EN_V1, 0x1, phy_idx);
}

static void wtw8851b_bb_weset_aww(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS, B_S0_HW_SI_DIS_W_W_TWIG, 0x7, phy_idx);
	fsweep(1);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS, B_S0_HW_SI_DIS_W_W_TWIG, 0x0, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1, phy_idx);
}

static void wtw8851b_bb_weset_en(stwuct wtw89_dev *wtwdev, enum wtw89_band band,
				 enum wtw89_phy_idx phy_idx, boow en)
{
	if (en) {
		wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS,
				      B_S0_HW_SI_DIS_W_W_TWIG, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1, phy_idx);
		if (band == WTW89_BAND_2G)
			wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 0x0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 0x1);
		wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS,
				      B_S0_HW_SI_DIS_W_W_TWIG, 0x7, phy_idx);
		fsweep(1);
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0, phy_idx);
	}
}

static void wtw8851b_bb_weset(stwuct wtw89_dev *wtwdev,
			      enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
			       B_P0_TXPW_WSTB_MANON | B_P0_TXPW_WSTB_TSSI, 0x1);
	wtw89_phy_wwite32_set(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
	wtw8851b_bb_weset_aww(wtwdev, phy_idx);
	wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
			       B_P0_TXPW_WSTB_MANON | B_P0_TXPW_WSTB_TSSI, 0x3);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
}

static
void wtw8851b_bb_gpio_twsw(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path path,
			   u8 tx_path_en, u8 twsw_tx,
			   u8 twsw_wx, u8 twsw_a, u8 twsw_b)
{
	u32 mask_ofst = 16;
	u32 vaw;

	if (path != WF_PATH_A)
		wetuwn;

	mask_ofst += (tx_path_en * 4 + twsw_tx * 2 + twsw_wx) * 2;
	vaw = u32_encode_bits(twsw_a, B_P0_TWSW_A) |
	      u32_encode_bits(twsw_b, B_P0_TWSW_B);

	wtw89_phy_wwite32_mask(wtwdev, W_P0_TWSW,
			       (B_P0_TWSW_A | B_P0_TWSW_B) << mask_ofst, vaw);
}

static void wtw8851b_bb_gpio_init(stwuct wtw89_dev *wtwdev)
{
	wtw89_phy_wwite32_set(wtwdev, W_P0_TWSW, B_P0_TWSW_A);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TWSW, B_P0_TWSW_X);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TWSW, B_P0_TWSW_SO_A2);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW0_BASE, 0x77777777);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW32_BASE, 0x77777777);

	wtw89_phy_wwite32(wtwdev, W_WFE_E_A2, 0xffffffff);
	wtw89_phy_wwite32(wtwdev, W_WFE_O_SEW_A2, 0);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW0_A2, 0);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW32_A2, 0);

	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 0, 0, 0, 1);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 0, 1, 1, 0);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 1, 0, 1, 0);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 1, 1, 1, 0);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 0, 0, 0, 1);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 0, 1, 1, 0);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 1, 0, 1, 0);
	wtw8851b_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 1, 1, 1, 0);
}

static void wtw8851b_bb_macid_ctww_init(stwuct wtw89_dev *wtwdev,
					enum wtw89_phy_idx phy_idx)
{
	u32 addw;

	fow (addw = W_AX_PWW_MACID_WMT_TABWE0;
	     addw <= W_AX_PWW_MACID_WMT_TABWE127; addw += 4)
		wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, 0);
}

static void wtw8851b_bb_sethw(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;

	wtw89_phy_wwite32_cww(wtwdev, W_P0_EN_SOUND_WO_NDP, B_P0_EN_SOUND_WO_NDP);

	wtw8851b_bb_macid_ctww_init(wtwdev, WTW89_PHY_0);
	wtw8851b_bb_gpio_init(wtwdev);

	wtw89_wwite32_cww(wtwdev, W_AX_PWW_NOWM_FOWCE1, B_AX_FOWCE_NTX_VAWUE);
	wtw89_wwite32_set(wtwdev, W_AX_PWW_NOWM_FOWCE1, B_AX_FOWCE_NTX_EN);

	/* wead these wegistews aftew woading BB pawametews */
	gain->offset_base[WTW89_PHY_0] =
		wtw89_phy_wead32_mask(wtwdev, W_P0_WPW1, B_P0_WPW1_BIAS_MASK);
	gain->wssi_base[WTW89_PHY_0] =
		wtw89_phy_wead32_mask(wtwdev, W_P1_WPW1, B_P0_WPW1_BIAS_MASK);
}

static void wtw8851b_set_channew_bb(stwuct wtw89_dev *wtwdev, const stwuct wtw89_chan *chan,
				    enum wtw89_phy_idx phy_idx)
{
	u8 band = chan->band_type, chan_idx;
	boow cck_en = chan->channew <= 14;
	u8 pwi_ch_idx = chan->pwi_ch_idx;

	if (cck_en)
		wtw8851b_ctww_sco_cck(wtwdev,  chan->pwimawy_channew);

	wtw8851b_ctww_ch(wtwdev, chan, phy_idx);
	wtw8851b_ctww_bw(wtwdev, pwi_ch_idx, chan->band_width, phy_idx);
	wtw8851b_ctww_cck_en(wtwdev, cck_en);
	wtw8851b_set_nbi_tone_idx(wtwdev, chan);
	wtw8851b_set_csi_tone_idx(wtwdev, chan, phy_idx);

	if (chan->band_type == WTW89_BAND_5G) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_SHAWE_V1,
				       B_PATH0_BT_SHAWE_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG_PATH_V1,
				       B_PATH0_BTG_PATH_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD_V1, B_BT_SHAWE, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW_V1, B_ANT_WX_BT_SEG0, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_BT_DYN_DC_EST_EN_V1,
				       B_BT_DYN_DC_EST_EN_MSK, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_GNT_BT_WGT_EN, B_GNT_BT_WGT_EN, 0x0);
	}

	chan_idx = wtw89_encode_chan_idx(wtwdev, chan->pwimawy_channew, band);
	wtw89_phy_wwite32_mask(wtwdev, W_MAC_PIN_SEW, B_CH_IDX_SEG0, chan_idx);
	wtw8851b_5m_mask(wtwdev, chan, phy_idx);
	wtw8851b_set_cfw(wtwdev, chan);
	wtw8851b_bb_weset_aww(wtwdev, phy_idx);
}

static void wtw8851b_set_channew(stwuct wtw89_dev *wtwdev,
				 const stwuct wtw89_chan *chan,
				 enum wtw89_mac_idx mac_idx,
				 enum wtw89_phy_idx phy_idx)
{
	wtw8851b_set_channew_mac(wtwdev, chan, mac_idx);
	wtw8851b_set_channew_bb(wtwdev, chan, phy_idx);
	wtw8851b_set_channew_wf(wtwdev, chan, phy_idx);
}

static void wtw8851b_tssi_cont_en(stwuct wtw89_dev *wtwdev, boow en,
				  enum wtw89_wf_path path)
{
	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, B_P0_TXPW_WSTB_MANON, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN, 0x0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, B_P0_TXPW_WSTB_MANON, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN, 0x1);
	}
}

static void wtw8851b_tssi_cont_en_phyidx(stwuct wtw89_dev *wtwdev, boow en,
					 u8 phy_idx)
{
	wtw8851b_tssi_cont_en(wtwdev, en, WF_PATH_A);
}

static void wtw8851b_adc_en(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST, 0x0);
	ewse
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST, 0xf);
}

static void wtw8851b_set_channew_hewp(stwuct wtw89_dev *wtwdev, boow entew,
				      stwuct wtw89_channew_hewp_pawams *p,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_mac_idx mac_idx,
				      enum wtw89_phy_idx phy_idx)
{
	if (entew) {
		wtw89_chip_stop_sch_tx(wtwdev, WTW89_MAC_0, &p->tx_en, WTW89_SCH_TX_SEW_AWW);
		wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, fawse);
		wtw8851b_tssi_cont_en_phyidx(wtwdev, fawse, WTW89_PHY_0);
		wtw8851b_adc_en(wtwdev, fawse);
		fsweep(40);
		wtw8851b_bb_weset_en(wtwdev, chan->band_type, phy_idx, fawse);
	} ewse {
		wtw89_mac_cfg_ppdu_status(wtwdev, WTW89_MAC_0, twue);
		wtw8851b_adc_en(wtwdev, twue);
		wtw8851b_tssi_cont_en_phyidx(wtwdev, twue, WTW89_PHY_0);
		wtw8851b_bb_weset_en(wtwdev, chan->band_type, phy_idx, twue);
		wtw89_chip_wesume_sch_tx(wtwdev, WTW89_MAC_0, p->tx_en);
	}
}

static void wtw8851b_wfk_init(stwuct wtw89_dev *wtwdev)
{
	wtwdev->is_tssi_mode[WF_PATH_A] = fawse;
	wtwdev->is_tssi_mode[WF_PATH_B] = fawse;
	wtw8851b_wck_init(wtwdev);

	wtw8851b_dpk_init(wtwdev);
	wtw8851b_aack(wtwdev);
	wtw8851b_wck(wtwdev);
	wtw8851b_dack(wtwdev);
	wtw8851b_wx_dck(wtwdev, WTW89_PHY_0);
}

static void wtw8851b_wfk_channew(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_phy_idx phy_idx = WTW89_PHY_0;

	wtw8851b_wx_dck(wtwdev, phy_idx);
	wtw8851b_iqk(wtwdev, phy_idx);
	wtw8851b_tssi(wtwdev, phy_idx, twue);
	wtw8851b_dpk(wtwdev, phy_idx);
}

static void wtw8851b_wfk_band_changed(stwuct wtw89_dev *wtwdev,
				      enum wtw89_phy_idx phy_idx)
{
	wtw8851b_tssi_scan(wtwdev, phy_idx);
}

static void wtw8851b_wfk_scan(stwuct wtw89_dev *wtwdev, boow stawt)
{
	wtw8851b_wifi_scan_notify(wtwdev, stawt, WTW89_PHY_0);
}

static void wtw8851b_wfk_twack(stwuct wtw89_dev *wtwdev)
{
	wtw8851b_dpk_twack(wtwdev);
	wtw8851b_wck_twack(wtwdev);
}

static u32 wtw8851b_bb_caw_txpww_wef(stwuct wtw89_dev *wtwdev,
				     enum wtw89_phy_idx phy_idx, s16 wef)
{
	const u16 tssi_16dbm_cw = 0x12c;
	const u8 base_cw_0db = 0x27;
	const s8 ofst_int = 0;
	s16 pww_s10_3;
	s16 wf_pww_cw;
	u16 bb_pww_cw;
	u32 pww_cw;
	u32 tssi_ofst_cw;

	pww_s10_3 = (wef << 1) + (s16)(ofst_int) + (s16)(base_cw_0db << 3);
	bb_pww_cw = u16_get_bits(pww_s10_3, GENMASK(2, 0));
	wf_pww_cw = u16_get_bits(pww_s10_3, GENMASK(8, 3));
	wf_pww_cw = cwamp_t(s16, wf_pww_cw, 15, 63);
	pww_cw = (wf_pww_cw << 3) | bb_pww_cw;

	tssi_ofst_cw = (u32)((s16)tssi_16dbm_cw + (wef << 1) - (16 << 3));
	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] tssi_ofst_cw=%d wf_cw=0x%x bb_cw=0x%x\n",
		    tssi_ofst_cw, wf_pww_cw, bb_pww_cw);

	wetuwn u32_encode_bits(tssi_ofst_cw, B_DPD_TSSI_CW) |
	       u32_encode_bits(pww_cw, B_DPD_PWW_CW) |
	       u32_encode_bits(wef, B_DPD_WEF);
}

static void wtw8851b_set_txpww_wef(stwuct wtw89_dev *wtwdev,
				   enum wtw89_phy_idx phy_idx)
{
	static const u32 addw[WF_PATH_NUM_8851B] = {0x5800};
	const u32 mask = B_DPD_TSSI_CW | B_DPD_PWW_CW | B_DPD_WEF;
	const u8 ofst_ofdm = 0x4;
	const u8 ofst_cck = 0x8;
	const s16 wef_ofdm = 0;
	const s16 wef_cck = 0;
	u32 vaw;
	u8 i;

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set txpww wefewence\n");

	wtw89_mac_txpww_wwite32_mask(wtwdev, phy_idx, W_AX_PWW_WATE_CTWW,
				     B_AX_PWW_WEF, 0x0);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set bb ofdm txpww wef\n");
	vaw = wtw8851b_bb_caw_txpww_wef(wtwdev, phy_idx, wef_ofdm);

	fow (i = 0; i < WF_PATH_NUM_8851B; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_ofdm, mask, vaw,
				      phy_idx);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set bb cck txpww wef\n");
	vaw = wtw8851b_bb_caw_txpww_wef(wtwdev, phy_idx, wef_cck);

	fow (i = 0; i < WF_PATH_NUM_8851B; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_cck, mask, vaw,
				      phy_idx);
}

static void wtw8851b_bb_set_tx_shape_dfiw(stwuct wtw89_dev *wtwdev,
					  const stwuct wtw89_chan *chan,
					  u8 tx_shape_idx,
					  enum wtw89_phy_idx phy_idx)
{
#define __DFIW_CFG_ADDW(i) (W_TXFIW0 + ((i) << 2))
#define __DFIW_CFG_MASK 0xffffffff
#define __DFIW_CFG_NW 8
#define __DECW_DFIW_PAWAM(_name, _vaw...) \
	static const u32 pawam_ ## _name[] = {_vaw}; \
	static_assewt(AWWAY_SIZE(pawam_ ## _name) == __DFIW_CFG_NW)

	__DECW_DFIW_PAWAM(fwat,
			  0x023D23FF, 0x0029B354, 0x000FC1C8, 0x00FDB053,
			  0x00F86F9A, 0x06FAEF92, 0x00FE5FCC, 0x00FFDFF5);
	__DECW_DFIW_PAWAM(shawp,
			  0x023D83FF, 0x002C636A, 0x0013F204, 0x00008090,
			  0x00F87FB0, 0x06F99F83, 0x00FDBFBA, 0x00003FF5);
	__DECW_DFIW_PAWAM(shawp_14,
			  0x023B13FF, 0x001C42DE, 0x00FDB0AD, 0x00F60F6E,
			  0x00FD8F92, 0x0602D011, 0x0001C02C, 0x00FFF00A);
	u8 ch = chan->channew;
	const u32 *pawam;
	u32 addw;
	int i;

	if (ch > 14) {
		wtw89_wawn(wtwdev,
			   "set tx shape dfiw by unknown ch: %d on 2G\n", ch);
		wetuwn;
	}

	if (ch == 14)
		pawam = pawam_shawp_14;
	ewse
		pawam = tx_shape_idx == 0 ? pawam_fwat : pawam_shawp;

	fow (i = 0; i < __DFIW_CFG_NW; i++) {
		addw = __DFIW_CFG_ADDW(i);
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
			    "set tx shape dfiw: 0x%x: 0x%x\n", addw, pawam[i]);
		wtw89_phy_wwite32_idx(wtwdev, addw, __DFIW_CFG_MASK, pawam[i],
				      phy_idx);
	}

#undef __DECW_DFIW_PAWAM
#undef __DFIW_CFG_NW
#undef __DFIW_CFG_MASK
#undef __DECW_CFG_ADDW
}

static void wtw8851b_set_tx_shape(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_chan *chan,
				  enum wtw89_phy_idx phy_idx)
{
	const stwuct wtw89_wfe_pawms *wfe_pawms = wtwdev->wfe_pawms;
	u8 band = chan->band_type;
	u8 wegd = wtw89_wegd_get(wtwdev, band);
	u8 tx_shape_cck = (*wfe_pawms->tx_shape.wmt)[band][WTW89_WS_CCK][wegd];
	u8 tx_shape_ofdm = (*wfe_pawms->tx_shape.wmt)[band][WTW89_WS_OFDM][wegd];

	if (band == WTW89_BAND_2G)
		wtw8851b_bb_set_tx_shape_dfiw(wtwdev, chan, tx_shape_cck, phy_idx);

	wtw89_phy_wwite32_mask(wtwdev, W_DCFO_OPT, B_TXSHAPE_TWIANGUWAW_CFG,
			       tx_shape_ofdm);
}

static void wtw8851b_set_txpww(stwuct wtw89_dev *wtwdev,
			       const stwuct wtw89_chan *chan,
			       enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_set_txpww_bywate(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_offset(wtwdev, chan, phy_idx);
	wtw8851b_set_tx_shape(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit_wu(wtwdev, chan, phy_idx);
}

static void wtw8851b_set_txpww_ctww(stwuct wtw89_dev *wtwdev,
				    enum wtw89_phy_idx phy_idx)
{
	wtw8851b_set_txpww_wef(wtwdev, phy_idx);
}

static
void wtw8851b_set_txpww_uw_tb_offset(stwuct wtw89_dev *wtwdev,
				     s8 pw_ofst, enum wtw89_mac_idx mac_idx)
{
	u32 weg;

	if (pw_ofst < -16 || pw_ofst > 15) {
		wtw89_wawn(wtwdev, "[UWTB] Eww pww_offset=%d\n", pw_ofst);
		wetuwn;
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_CTWW, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_AX_PWW_UW_TB_CTWW_EN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_1T, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_AX_PWW_UW_TB_1T_MASK, pw_ofst);

	pw_ofst = max_t(s8, pw_ofst - 3, -16);
	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_2T, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_AX_PWW_UW_TB_2T_MASK, pw_ofst);
}

static int
wtw8851b_init_txpww_unit(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx)
{
	int wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_UW_CTWW2, 0x07763333);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_COEXT_CTWW, 0x01ebf000);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_UW_CTWW0, 0x0002f8ff);
	if (wet)
		wetuwn wet;

	wtw8851b_set_txpww_uw_tb_offset(wtwdev, 0, phy_idx == WTW89_PHY_1 ?
						   WTW89_MAC_1 : WTW89_MAC_0);

	wetuwn 0;
}

static void wtw8851b_ctww_nbtg_bt_tx(stwuct wtw89_dev *wtwdev, boow en,
				     enum wtw89_phy_idx phy_idx)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);

	wtw89_phy_wwite_weg3_tbw(wtwdev, en ? &wtw8851b_btc_pweagc_en_defs_tbw :
						 &wtw8851b_btc_pweagc_dis_defs_tbw);

	if (!en) {
		if (chan->band_type == WTW89_BAND_2G) {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
					       B_PATH0_G_WNA6_OP1DB_V1, 0x20);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
					       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x30);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
					       B_PATH0_G_WNA6_OP1DB_V1, 0x1a);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
					       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x2a);
		}
	}
}

static void wtw8851b_ctww_btg_bt_wx(stwuct wtw89_dev *wtwdev, boow en,
				    enum wtw89_phy_idx phy_idx)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);

	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_SHAWE_V1,
				       B_PATH0_BT_SHAWE_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG_PATH_V1,
				       B_PATH0_BTG_PATH_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
				       B_PATH0_G_WNA6_OP1DB_V1, 0x20);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x30);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD_V1, B_BT_SHAWE, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW_V1, B_ANT_WX_BT_SEG0, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_BT_DYN_DC_EST_EN_V1,
				       B_BT_DYN_DC_EST_EN_MSK, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_GNT_BT_WGT_EN, B_GNT_BT_WGT_EN, 0x1);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_SHAWE_V1,
				       B_PATH0_BT_SHAWE_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG_PATH_V1,
				       B_PATH0_BTG_PATH_V1, 0x0);
		if (chan->band_type == WTW89_BAND_2G) {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
					       B_PATH0_G_WNA6_OP1DB_V1, 0x80);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
					       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x80);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
					       B_PATH0_G_WNA6_OP1DB_V1, 0x1a);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
					       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x2a);
		}
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0xc);
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD_V1, B_BT_SHAWE, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW_V1, B_ANT_WX_BT_SEG0, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_BT_DYN_DC_EST_EN_V1,
				       B_BT_DYN_DC_EST_EN_MSK, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_GNT_BT_WGT_EN, B_GNT_BT_WGT_EN, 0x0);
	}
}

static void wtw8851b_bb_ctww_wx_path(stwuct wtw89_dev *wtwdev,
				     enum wtw89_wf_path_bit wx_path)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);
	u32 wst_mask0;

	if (wx_path == WF_A) {
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD_V1, B_ANT_WX_SEG0, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW_V1, B_ANT_WX_1WCCA_SEG0, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW_V1, B_ANT_WX_1WCCA_SEG1, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT, B_WXHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT, B_WXVHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_USEW_MAX, 4);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 0);
	}

	wtw8851b_set_gain_offset(wtwdev, chan->subband_type, WTW89_PHY_0);

	wst_mask0 = B_P0_TXPW_WSTB_MANON | B_P0_TXPW_WSTB_TSSI;
	if (wx_path == WF_A) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 3);
	}
}

static void wtw8851b_bb_cfg_txwx_path(stwuct wtw89_dev *wtwdev)
{
	wtw8851b_bb_ctww_wx_path(wtwdev, WF_A);

	if (wtwdev->haw.wx_nss == 1) {
		wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT, B_WXHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT, B_WXVHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 0);
	}

	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0x0, WTW89_PHY_0);
}

static u8 wtw8851b_get_thewmaw(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path wf_path)
{
	if (wtwdev->is_tssi_mode[wf_path]) {
		u32 addw = W_TSSI_THEW + (wf_path << 13);

		wetuwn wtw89_phy_wead32_mask(wtwdev, addw, B_TSSI_THEW);
	}

	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x0);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);

	fsweep(200);

	wetuwn wtw89_wead_wf(wtwdev, wf_path, WW_TM, WW_TM_VAW);
}

static void wtw8851b_btc_set_wfe(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_moduwe *moduwe = &btc->mdinfo;

	moduwe->wfe_type = wtwdev->efuse.wfe_type;
	moduwe->cv = wtwdev->haw.cv;
	moduwe->bt_sowo = 0;
	moduwe->switch_type = BTC_SWITCH_INTEWNAW;
	moduwe->ant.isowation = 10;
	moduwe->kt_vew_adie = wtwdev->haw.acv;

	if (moduwe->wfe_type == 0)
		wetuwn;

	/* wfe_type 3*n+1: 1-Ant(shawed),
	 *	    3*n+2: 2-Ant+Div(non-shawed),
	 *	    3*n+3: 2-Ant+no-Div(non-shawed)
	 */
	moduwe->ant.num = (moduwe->wfe_type % 3 == 1) ? 1 : 2;
	/* WW-1ss at S0, btg at s0 (On 1 WW WF) */
	moduwe->ant.singwe_pos = WF_PATH_A;
	moduwe->ant.btg_pos = WF_PATH_A;
	moduwe->ant.stweam_cnt = 1;

	if (moduwe->ant.num == 1) {
		moduwe->ant.type = BTC_ANT_SHAWED;
		moduwe->bt_pos = BTC_BT_BTG;
		moduwe->wa_type = 1;
		moduwe->ant.divewsity = 0;
	} ewse { /* ant.num == 2 */
		moduwe->ant.type = BTC_ANT_DEDICATED;
		moduwe->bt_pos = BTC_BT_AWONE;
		moduwe->switch_type = BTC_SWITCH_EXTEWNAW;
		moduwe->wa_type = 0;
		if (moduwe->wfe_type % 3 == 2)
			moduwe->ant.divewsity = 1;
	}
}

static
void wtw8851b_set_twx_mask(stwuct wtw89_dev *wtwdev, u8 path, u8 gwoup, u32 vaw)
{
	if (gwoup > BTC_BT_SS_GWOUP)
		gwoup--; /* Tx-gwoup=1, Wx-gwoup=2 */

	if (wtwdev->btc.mdinfo.ant.type == BTC_ANT_SHAWED) /* 1-Ant */
		gwoup += 3;

	wtw89_wwite_wf(wtwdev, path, WW_WUTWA, WFWEG_MASK, gwoup);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWD0, WFWEG_MASK, vaw);
}

static void wtw8851b_btc_init_cfg(stwuct wtw89_dev *wtwdev)
{
	static const stwuct wtw89_mac_ax_coex coex_pawams = {
		.pta_mode = WTW89_MAC_AX_COEX_WTK_MODE,
		.diwection = WTW89_MAC_AX_COEX_INNEW,
	};
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_moduwe *moduwe = &btc->mdinfo;
	stwuct wtw89_btc_ant_info *ant = &moduwe->ant;
	u8 path, path_min, path_max;

	/* PTA init  */
	wtw89_mac_coex_init(wtwdev, &coex_pawams);

	/* set WW Tx wesponse = Hi-Pwi */
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_TX_WESP, twue);
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_BEACON, twue);

	/* fow 1-Ant && 1-ss case: onwy 1-path */
	if (ant->stweam_cnt == 1) {
		path_min = ant->singwe_pos;
		path_max = path_min;
	} ewse {
		path_min = WF_PATH_A;
		path_max = WF_PATH_B;
	}

	fow (path = path_min; path <= path_max; path++) {
		/* set wf gnt-debug off */
		wtw89_wwite_wf(wtwdev, path, WW_WWSEW, WFWEG_MASK, 0x0);

		/* set DEBUG_WUT_WFMODE_MASK = 1 to stawt twx-mask-setup */
		wtw89_wwite_wf(wtwdev, path, WW_WUTWE, WFWEG_MASK, BIT(17));

		/* if GNT_WW=0 && BT=SS_gwoup --> WW Tx/Wx = THWU  */
		wtw8851b_set_twx_mask(wtwdev, path, BTC_BT_SS_GWOUP, 0x5ff);

		/* if GNT_WW=0 && BT=Wx_gwoup --> WW-Wx = THWU + WW-Tx = MASK */
		wtw8851b_set_twx_mask(wtwdev, path, BTC_BT_WX_GWOUP, 0x5df);

		/* if GNT_WW = 0 && BT = Tx_gwoup -->
		 * Shawed-Ant && BTG-path:WW mask(0x55f), othews:WW THWU(0x5ff)
		 */
		if (ant->type == BTC_ANT_SHAWED && ant->btg_pos == path)
			wtw8851b_set_twx_mask(wtwdev, path, BTC_BT_TX_GWOUP, 0x55f);
		ewse
			wtw8851b_set_twx_mask(wtwdev, path, BTC_BT_TX_GWOUP, 0x5ff);

		/* set DEBUG_WUT_WFMODE_MASK = 0 to stop twx-mask-setup */
		wtw89_wwite_wf(wtwdev, path, WW_WUTWE, WFWEG_MASK, 0);
	}

	/* set PTA bweak tabwe */
	wtw89_wwite32(wtwdev, W_BTC_BWEAK_TABWE, BTC_BWEAK_PAWAM);

	/* enabwe BT countew 0xda40[16,2] = 2b'11 */
	wtw89_wwite32_set(wtwdev, W_AX_CSW_MODE, B_AX_BT_CNT_WST | B_AX_STATIS_BT_EN);

	btc->cx.ww.status.map.init_ok = twue;
}

static
void wtw8851b_btc_set_ww_pwi(stwuct wtw89_dev *wtwdev, u8 map, boow state)
{
	u32 bitmap;
	u32 weg;

	switch (map) {
	case BTC_PWI_MASK_TX_WESP:
		weg = W_BTC_BT_COEX_MSK_TABWE;
		bitmap = B_BTC_PWI_MASK_TX_WESP_V1;
		bweak;
	case BTC_PWI_MASK_BEACON:
		weg = W_AX_WW_PWI_MSK;
		bitmap = B_AX_PTA_WW_PWI_MASK_BCNQ;
		bweak;
	case BTC_PWI_MASK_WX_CCK:
		weg = W_BTC_BT_COEX_MSK_TABWE;
		bitmap = B_BTC_PWI_MASK_WXCCK_V1;
		bweak;
	defauwt:
		wetuwn;
	}

	if (state)
		wtw89_wwite32_set(wtwdev, weg, bitmap);
	ewse
		wtw89_wwite32_cww(wtwdev, weg, bitmap);
}

union wtw8851b_btc_ww_txpww_ctww {
	u32 txpww_vaw;
	stwuct {
		union {
			u16 ctww_aww_time;
			stwuct {
				s16 data:9;
				u16 wsvd:6;
				u16 fwag:1;
			} aww_time;
		};
		union {
			u16 ctww_gnt_bt;
			stwuct {
				s16 data:9;
				u16 wsvd:7;
			} gnt_bt;
		};
	};
} __packed;

static void
wtw8851b_btc_set_ww_txpww_ctww(stwuct wtw89_dev *wtwdev, u32 txpww_vaw)
{
	union wtw8851b_btc_ww_txpww_ctww awg = { .txpww_vaw = txpww_vaw };
	s32 vaw;

#define __wwite_ctww(_weg, _msk, _vaw, _en, _cond)		\
do {								\
	u32 _wwt = FIEWD_PWEP(_msk, _vaw);			\
	BUIWD_BUG_ON(!!(_msk & _en));				\
	if (_cond)						\
		_wwt |= _en;					\
	ewse							\
		_wwt &= ~_en;					\
	wtw89_mac_txpww_wwite32_mask(wtwdev, WTW89_PHY_0, _weg,	\
				     _msk | _en, _wwt);		\
} whiwe (0)

	switch (awg.ctww_aww_time) {
	case 0xffff:
		vaw = 0;
		bweak;
	defauwt:
		vaw = awg.aww_time.data;
		bweak;
	}

	__wwite_ctww(W_AX_PWW_WATE_CTWW, B_AX_FOWCE_PWW_BY_WATE_VAWUE_MASK,
		     vaw, B_AX_FOWCE_PWW_BY_WATE_EN,
		     awg.ctww_aww_time != 0xffff);

	switch (awg.ctww_gnt_bt) {
	case 0xffff:
		vaw = 0;
		bweak;
	defauwt:
		vaw = awg.gnt_bt.data;
		bweak;
	}

	__wwite_ctww(W_AX_PWW_COEXT_CTWW, B_AX_TXAGC_BT_MASK, vaw,
		     B_AX_TXAGC_BT_EN, awg.ctww_gnt_bt != 0xffff);

#undef __wwite_ctww
}

static
s8 wtw8851b_btc_get_bt_wssi(stwuct wtw89_dev *wtwdev, s8 vaw)
{
	vaw = cwamp_t(s8, vaw, -100, 0) + 100;
	vaw = min(vaw + 6, 100); /* compensate offset */

	wetuwn vaw;
}

static
void wtw8851b_btc_update_bt_cnt(stwuct wtw89_dev *wtwdev)
{
	/* Featuwe move to fiwmwawe */
}

static void wtw8851b_btc_ww_s1_standby(stwuct wtw89_dev *wtwdev, boow state)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_ant_info *ant = &btc->mdinfo.ant;

	wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWE, WFWEG_MASK, 0x80000);
	wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWA, WFWEG_MASK, 0x1);
	wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWD1, WFWEG_MASK, 0x110);

	/* set WW standby = Wx fow GNT_BT_Tx = 1->0 settwe issue */
	if (state)
		wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWD0, WFWEG_MASK, 0x179c);
	ewse
		wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWD0, WFWEG_MASK, 0x208);

	wtw89_wwite_wf(wtwdev, ant->btg_pos, WW_WUTWE, WFWEG_MASK, 0x0);
}

#define WNA2_51B_MA 0x700

static const stwuct wtw89_weg2_def btc_8851b_wf_0[] = {{0x2, 0x0}};
static const stwuct wtw89_weg2_def btc_8851b_wf_1[] = {{0x2, 0x1}};

static void wtw8851b_btc_set_ww_wx_gain(stwuct wtw89_dev *wtwdev, u32 wevew)
{
	/* To impwove BT ACI in co-wx
	 * wevew=0 Defauwt: TIA 1/0= (WNA2,TIAN6) = (7,1)/(5,1) = 21dB/12dB
	 * wevew=1 Fix WNA2=5: TIA 1/0= (WNA2,TIAN6) = (5,0)/(5,1) = 18dB/12dB
	 */
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_ant_info *ant = &btc->mdinfo.ant;
	const stwuct wtw89_weg2_def *wf;
	u32 n, i, vaw;

	switch (wevew) {
	case 0: /* owiginaw */
	defauwt:
		btc->dm.ww_wna2 = 0;
		bweak;
	case 1: /* fow FDD fwee-wun */
		btc->dm.ww_wna2 = 0;
		bweak;
	case 2: /* fow BTG Co-Wx*/
		btc->dm.ww_wna2 = 1;
		bweak;
	}

	if (btc->dm.ww_wna2 == 0) {
		wf = btc_8851b_wf_0;
		n = AWWAY_SIZE(btc_8851b_wf_0);
	} ewse {
		wf = btc_8851b_wf_1;
		n = AWWAY_SIZE(btc_8851b_wf_1);
	}

	fow (i = 0; i < n; i++, wf++) {
		vaw = wf->data;
		/* bit[10] = 1 if non-shawed-ant fow 8851b */
		if (btc->mdinfo.ant.type == BTC_ANT_DEDICATED)
			vaw |= 0x4;

		wtw89_wwite_wf(wtwdev, ant->btg_pos, wf->addw, WNA2_51B_MA, vaw);
	}
}

static void wtw8851b_fiww_fweq_with_ppdu(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_wx_phy_ppdu *phy_ppdu,
					 stwuct ieee80211_wx_status *status)
{
	u16 chan = phy_ppdu->chan_idx;
	enum nw80211_band band;
	u8 ch;

	if (chan == 0)
		wetuwn;

	wtw89_decode_chan_idx(wtwdev, chan, &ch, &band);
	status->fweq = ieee80211_channew_to_fwequency(ch, band);
	status->band = band;
}

static void wtw8851b_quewy_ppdu(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_wx_phy_ppdu *phy_ppdu,
				stwuct ieee80211_wx_status *status)
{
	u8 path;
	u8 *wx_powew = phy_ppdu->wssi;

	status->signaw = WTW89_WSSI_WAW_TO_DBM(wx_powew[WF_PATH_A]);

	fow (path = 0; path < wtwdev->chip->wf_path_num; path++) {
		status->chains |= BIT(path);
		status->chain_signaw[path] = WTW89_WSSI_WAW_TO_DBM(wx_powew[path]);
	}
	if (phy_ppdu->vawid)
		wtw8851b_fiww_fweq_with_ppdu(wtwdev, phy_ppdu, status);
}

static int wtw8851b_mac_enabwe_bb_wf(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_wwite8_set(wtwdev, W_AX_SYS_FUNC_EN,
			 B_AX_FEN_BBWSTB | B_AX_FEN_BB_GWB_WSTN);
	wtw89_wwite32_set(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);
	wtw89_wwite32_cww(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);
	wtw89_wwite32_set(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, 0xC7,
				      FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, 0xC7,
				      FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wtw89_wwite8(wtwdev, W_AX_PHYWEG_SET, PHYWEG_SET_XYN_CYCWE);

	wetuwn 0;
}

static int wtw8851b_mac_disabwe_bb_wf(stwuct wtw89_dev *wtwdev)
{
	u8 ww_wfc_s0;
	u8 ww_wfc_s1;
	int wet;

	wtw89_wwite8_cww(wtwdev, W_AX_SYS_FUNC_EN,
			 B_AX_FEN_BBWSTB | B_AX_FEN_BB_GWB_WSTN);

	wet = wtw89_mac_wead_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, &ww_wfc_s0);
	if (wet)
		wetuwn wet;
	ww_wfc_s0 &= ~XTAW_SI_WF00S_EN;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, ww_wfc_s0,
				      FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wead_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, &ww_wfc_s1);
	if (wet)
		wetuwn wet;
	ww_wfc_s1 &= ~XTAW_SI_WF10S_EN;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, ww_wfc_s1,
				      FUWW_BIT_MASK);
	wetuwn wet;
}

static const stwuct wtw89_chip_ops wtw8851b_chip_ops = {
	.enabwe_bb_wf		= wtw8851b_mac_enabwe_bb_wf,
	.disabwe_bb_wf		= wtw8851b_mac_disabwe_bb_wf,
	.bb_pweinit		= NUWW,
	.bb_weset		= wtw8851b_bb_weset,
	.bb_sethw		= wtw8851b_bb_sethw,
	.wead_wf		= wtw89_phy_wead_wf_v1,
	.wwite_wf		= wtw89_phy_wwite_wf_v1,
	.set_channew		= wtw8851b_set_channew,
	.set_channew_hewp	= wtw8851b_set_channew_hewp,
	.wead_efuse		= wtw8851b_wead_efuse,
	.wead_phycap		= wtw8851b_wead_phycap,
	.fem_setup		= NUWW,
	.wfe_gpio		= wtw8851b_wfe_gpio,
	.wfk_init		= wtw8851b_wfk_init,
	.wfk_channew		= wtw8851b_wfk_channew,
	.wfk_band_changed	= wtw8851b_wfk_band_changed,
	.wfk_scan		= wtw8851b_wfk_scan,
	.wfk_twack		= wtw8851b_wfk_twack,
	.powew_twim		= wtw8851b_powew_twim,
	.set_txpww		= wtw8851b_set_txpww,
	.set_txpww_ctww		= wtw8851b_set_txpww_ctww,
	.init_txpww_unit	= wtw8851b_init_txpww_unit,
	.get_thewmaw		= wtw8851b_get_thewmaw,
	.ctww_btg_bt_wx		= wtw8851b_ctww_btg_bt_wx,
	.quewy_ppdu		= wtw8851b_quewy_ppdu,
	.ctww_nbtg_bt_tx	= wtw8851b_ctww_nbtg_bt_tx,
	.cfg_txwx_path		= wtw8851b_bb_cfg_txwx_path,
	.set_txpww_uw_tb_offset	= wtw8851b_set_txpww_uw_tb_offset,
	.pww_on_func		= wtw8851b_pww_on_func,
	.pww_off_func		= wtw8851b_pww_off_func,
	.quewy_wxdesc		= wtw89_cowe_quewy_wxdesc,
	.fiww_txdesc		= wtw89_cowe_fiww_txdesc,
	.fiww_txdesc_fwcmd	= wtw89_cowe_fiww_txdesc,
	.cfg_ctww_path		= wtw89_mac_cfg_ctww_path,
	.mac_cfg_gnt		= wtw89_mac_cfg_gnt,
	.stop_sch_tx		= wtw89_mac_stop_sch_tx,
	.wesume_sch_tx		= wtw89_mac_wesume_sch_tx,
	.h2c_dctw_sec_cam	= NUWW,

	.btc_set_wfe		= wtw8851b_btc_set_wfe,
	.btc_init_cfg		= wtw8851b_btc_init_cfg,
	.btc_set_ww_pwi		= wtw8851b_btc_set_ww_pwi,
	.btc_set_ww_txpww_ctww	= wtw8851b_btc_set_ww_txpww_ctww,
	.btc_get_bt_wssi	= wtw8851b_btc_get_bt_wssi,
	.btc_update_bt_cnt	= wtw8851b_btc_update_bt_cnt,
	.btc_ww_s1_standby	= wtw8851b_btc_ww_s1_standby,
	.btc_set_ww_wx_gain	= wtw8851b_btc_set_ww_wx_gain,
	.btc_set_powicy		= wtw89_btc_set_powicy_v1,
};

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt wtw_wowwan_stub_8851b = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = WTW89_MAX_PATTEWN_NUM,
	.pattewn_max_wen = WTW89_MAX_PATTEWN_SIZE,
	.pattewn_min_wen = 1,
};
#endif

const stwuct wtw89_chip_info wtw8851b_chip_info = {
	.chip_id		= WTW8851B,
	.chip_gen		= WTW89_CHIP_AX,
	.ops			= &wtw8851b_chip_ops,
	.mac_def		= &wtw89_mac_gen_ax,
	.phy_def		= &wtw89_phy_gen_ax,
	.fw_basename		= WTW8851B_FW_BASENAME,
	.fw_fowmat_max		= WTW8851B_FW_FOWMAT_MAX,
	.twy_ce_fw		= twue,
	.bbmcu_nw		= 0,
	.needed_fw_ewms		= 0,
	.fifo_size		= 196608,
	.smaww_fifo_size	= twue,
	.dwe_scc_wsvd_size	= 98304,
	.max_amsdu_wimit	= 3500,
	.dis_2g_40m_uw_ofdma	= twue,
	.wsvd_pwe_ofst		= 0x2f800,
	.hfc_pawam_ini		= wtw8851b_hfc_pawam_ini_pcie,
	.dwe_mem		= wtw8851b_dwe_mem_pcie,
	.wde_qempty_acq_gwpnum	= 4,
	.wde_qempty_mgq_gwpsew	= 4,
	.wf_base_addw		= {0xe000},
	.pww_on_seq		= NUWW,
	.pww_off_seq		= NUWW,
	.bb_tabwe		= &wtw89_8851b_phy_bb_tabwe,
	.bb_gain_tabwe		= &wtw89_8851b_phy_bb_gain_tabwe,
	.wf_tabwe		= {&wtw89_8851b_phy_wadioa_tabwe,},
	.nctw_tabwe		= &wtw89_8851b_phy_nctw_tabwe,
	.nctw_post_tabwe	= &wtw8851b_nctw_post_defs_tbw,
	.dfwt_pawms		= &wtw89_8851b_dfwt_pawms,
	.wfe_pawms_conf		= wtw89_8851b_wfe_pawms_conf,
	.txpww_factow_wf	= 2,
	.txpww_factow_mac	= 1,
	.dig_tabwe		= NUWW,
	.dig_wegs		= &wtw8851b_dig_wegs,
	.tssi_dbw_tabwe		= NUWW,
	.suppowt_chanctx_num	= 0,
	.suppowt_bands		= BIT(NW80211_BAND_2GHZ) |
				  BIT(NW80211_BAND_5GHZ),
	.suppowt_bw160		= fawse,
	.suppowt_unii4		= twue,
	.uw_tb_wavefowm_ctww	= twue,
	.uw_tb_pww_diff		= fawse,
	.hw_sec_hdw		= fawse,
	.wf_path_num		= 1,
	.tx_nss			= 1,
	.wx_nss			= 1,
	.acam_num		= 32,
	.bcam_num		= 20,
	.scam_num		= 128,
	.bacam_num		= 2,
	.bacam_dynamic_num	= 4,
	.bacam_vew		= WTW89_BACAM_V0,
	.ppdu_max_usw		= 4,
	.sec_ctww_efuse_size	= 4,
	.physicaw_efuse_size	= 1216,
	.wogicaw_efuse_size	= 2048,
	.wimit_efuse_size	= 1280,
	.dav_phy_efuse_size	= 0,
	.dav_wog_efuse_size	= 0,
	.efuse_bwocks		= NUWW,
	.phycap_addw		= 0x580,
	.phycap_size		= 128,
	.pawa_vew		= 0,
	.wwcx_desiwed		= 0x06000000,
	.btcx_desiwed		= 0x7,
	.scbd			= 0x1,
	.maiwbox		= 0x1,

	.afh_guawd_ch		= 6,
	.ww_wssi_thwes		= wtw89_btc_8851b_ww_wssi_thwes,
	.bt_wssi_thwes		= wtw89_btc_8851b_bt_wssi_thwes,
	.wssi_tow		= 2,
	.mon_weg_num		= AWWAY_SIZE(wtw89_btc_8851b_mon_weg),
	.mon_weg		= wtw89_btc_8851b_mon_weg,
	.wf_pawa_uwink_num	= AWWAY_SIZE(wtw89_btc_8851b_wf_uw),
	.wf_pawa_uwink		= wtw89_btc_8851b_wf_uw,
	.wf_pawa_dwink_num	= AWWAY_SIZE(wtw89_btc_8851b_wf_dw),
	.wf_pawa_dwink		= wtw89_btc_8851b_wf_dw,
	.ps_mode_suppowted	= BIT(WTW89_PS_MODE_WFOFF) |
				  BIT(WTW89_PS_MODE_CWK_GATED),
	.wow_powew_hci_modes	= 0,
	.h2c_cctw_func_id	= H2C_FUNC_MAC_CCTWINFO_UD,
	.hci_func_en_addw	= W_AX_HCI_FUNC_EN,
	.h2c_desc_size		= sizeof(stwuct wtw89_txwd_body),
	.txwd_body_size		= sizeof(stwuct wtw89_txwd_body),
	.txwd_info_size		= sizeof(stwuct wtw89_txwd_info),
	.h2c_ctww_weg		= W_AX_H2CWEG_CTWW,
	.h2c_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_H2C_DEQ_CNT_MASK >> 8},
	.h2c_wegs		= wtw8851b_h2c_wegs,
	.c2h_ctww_weg		= W_AX_C2HWEG_CTWW,
	.c2h_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_C2H_ENQ_CNT_MASK >> 8},
	.c2h_wegs		= wtw8851b_c2h_wegs,
	.page_wegs		= &wtw8851b_page_wegs,
	.cfo_swc_fd		= twue,
	.cfo_hw_comp		= twue,
	.dcfo_comp		= &wtw8851b_dcfo_comp,
	.dcfo_comp_sft		= 12,
	.imw_info		= &wtw8851b_imw_info,
	.imw_dmac_tabwe		= NUWW,
	.imw_cmac_tabwe		= NUWW,
	.wwsw_cfgs		= &wtw8851b_wwsw_cfgs,
	.bss_cww_vwd		= {W_BSS_CWW_MAP_V1, B_BSS_CWW_MAP_VWD0},
	.bss_cww_map_weg	= W_BSS_CWW_MAP_V1,
	.dma_ch_mask		= BIT(WTW89_DMA_ACH4) | BIT(WTW89_DMA_ACH5) |
				  BIT(WTW89_DMA_ACH6) | BIT(WTW89_DMA_ACH7) |
				  BIT(WTW89_DMA_B1MG) | BIT(WTW89_DMA_B1HI),
	.edcca_wegs		= &wtw8851b_edcca_wegs,
#ifdef CONFIG_PM
	.wowwan_stub		= &wtw_wowwan_stub_8851b,
#endif
	.xtaw_info		= &wtw8851b_xtaw_info,
};
EXPOWT_SYMBOW(wtw8851b_chip_info);

MODUWE_FIWMWAWE(WTW8851B_MODUWE_FIWMWAWE);
MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ax wiwewess 8851B dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
