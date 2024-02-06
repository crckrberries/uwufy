// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2022  Weawtek Cowpowation
 */

#incwude "chan.h"
#incwude "coex.h"
#incwude "debug.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "wtw8852c.h"
#incwude "wtw8852c_wfk.h"
#incwude "wtw8852c_tabwe.h"
#incwude "utiw.h"

#define WTW8852C_FW_FOWMAT_MAX 0
#define WTW8852C_FW_BASENAME "wtw89/wtw8852c_fw"
#define WTW8852C_MODUWE_FIWMWAWE \
	WTW8852C_FW_BASENAME ".bin"

static const stwuct wtw89_hfc_ch_cfg wtw8852c_hfc_chcfg_pcie[] = {
	{13, 1614, gwp_0}, /* ACH 0 */
	{13, 1614, gwp_0}, /* ACH 1 */
	{13, 1614, gwp_0}, /* ACH 2 */
	{13, 1614, gwp_0}, /* ACH 3 */
	{13, 1614, gwp_1}, /* ACH 4 */
	{13, 1614, gwp_1}, /* ACH 5 */
	{13, 1614, gwp_1}, /* ACH 6 */
	{13, 1614, gwp_1}, /* ACH 7 */
	{13, 1614, gwp_0}, /* B0MGQ */
	{13, 1614, gwp_0}, /* B0HIQ */
	{13, 1614, gwp_1}, /* B1MGQ */
	{13, 1614, gwp_1}, /* B1HIQ */
	{40, 0, 0} /* FWCMDQ */
};

static const stwuct wtw89_hfc_pub_cfg wtw8852c_hfc_pubcfg_pcie = {
	1614, /* Gwoup 0 */
	1614, /* Gwoup 1 */
	3228, /* Pubwic Max */
	0 /* WP thweshowd */
};

static const stwuct wtw89_hfc_pawam_ini wtw8852c_hfc_pawam_ini_pcie[] = {
	[WTW89_QTA_SCC] = {wtw8852c_hfc_chcfg_pcie, &wtw8852c_hfc_pubcfg_pcie,
			   &wtw89_mac_size.hfc_pweccfg_pcie, WTW89_HCIFC_POH},
	[WTW89_QTA_DWFW] = {NUWW, NUWW, &wtw89_mac_size.hfc_pweccfg_pcie,
			    WTW89_HCIFC_POH},
	[WTW89_QTA_INVAWID] = {NUWW},
};

static const stwuct wtw89_dwe_mem wtw8852c_dwe_mem_pcie[] = {
	[WTW89_QTA_SCC] = {WTW89_QTA_SCC, &wtw89_mac_size.wde_size19,
			   &wtw89_mac_size.pwe_size19, &wtw89_mac_size.wde_qt18,
			   &wtw89_mac_size.wde_qt18, &wtw89_mac_size.pwe_qt46,
			   &wtw89_mac_size.pwe_qt47},
	[WTW89_QTA_DWFW] = {WTW89_QTA_DWFW, &wtw89_mac_size.wde_size18,
			    &wtw89_mac_size.pwe_size18, &wtw89_mac_size.wde_qt17,
			    &wtw89_mac_size.wde_qt17, &wtw89_mac_size.pwe_qt44,
			    &wtw89_mac_size.pwe_qt45},
	[WTW89_QTA_INVAWID] = {WTW89_QTA_INVAWID, NUWW, NUWW, NUWW, NUWW, NUWW,
			       NUWW},
};

static const u32 wtw8852c_h2c_wegs[WTW89_H2CWEG_MAX] = {
	W_AX_H2CWEG_DATA0_V1, W_AX_H2CWEG_DATA1_V1, W_AX_H2CWEG_DATA2_V1,
	W_AX_H2CWEG_DATA3_V1
};

static const u32 wtw8852c_c2h_wegs[WTW89_H2CWEG_MAX] = {
	W_AX_C2HWEG_DATA0_V1, W_AX_C2HWEG_DATA1_V1, W_AX_C2HWEG_DATA2_V1,
	W_AX_C2HWEG_DATA3_V1
};

static const stwuct wtw89_page_wegs wtw8852c_page_wegs = {
	.hci_fc_ctww	= W_AX_HCI_FC_CTWW_V1,
	.ch_page_ctww	= W_AX_CH_PAGE_CTWW_V1,
	.ach_page_ctww	= W_AX_ACH0_PAGE_CTWW_V1,
	.ach_page_info	= W_AX_ACH0_PAGE_INFO_V1,
	.pub_page_info3	= W_AX_PUB_PAGE_INFO3_V1,
	.pub_page_ctww1	= W_AX_PUB_PAGE_CTWW1_V1,
	.pub_page_ctww2	= W_AX_PUB_PAGE_CTWW2_V1,
	.pub_page_info1	= W_AX_PUB_PAGE_INFO1_V1,
	.pub_page_info2 = W_AX_PUB_PAGE_INFO2_V1,
	.wp_page_ctww1	= W_AX_WP_PAGE_CTWW1_V1,
	.wp_page_ctww2	= W_AX_WP_PAGE_CTWW2_V1,
	.wp_page_info1	= W_AX_WP_PAGE_INFO1_V1,
};

static const stwuct wtw89_weg_def wtw8852c_dcfo_comp = {
	W_DCFO_COMP_S0_V1, B_DCFO_COMP_S0_V1_MSK
};

static const stwuct wtw89_imw_info wtw8852c_imw_info = {
	.wdwws_imw_set		= B_AX_WDWWS_IMW_SET_V1,
	.wsec_imw_weg		= W_AX_SEC_EWWOW_FWAG_IMW,
	.wsec_imw_set		= B_AX_TX_HANG_IMW | B_AX_WX_HANG_IMW,
	.mpdu_tx_imw_set	= B_AX_MPDU_TX_IMW_SET_V1,
	.mpdu_wx_imw_set	= B_AX_MPDU_WX_IMW_SET_V1,
	.sta_sch_imw_set	= B_AX_STA_SCHEDUWEW_IMW_SET,
	.txpktctw_imw_b0_weg	= W_AX_TXPKTCTW_B0_EWWFWAG_IMW,
	.txpktctw_imw_b0_cww	= B_AX_TXPKTCTW_IMW_B0_CWW_V1,
	.txpktctw_imw_b0_set	= B_AX_TXPKTCTW_IMW_B0_SET_V1,
	.txpktctw_imw_b1_weg	= W_AX_TXPKTCTW_B1_EWWFWAG_IMW,
	.txpktctw_imw_b1_cww	= B_AX_TXPKTCTW_IMW_B1_CWW_V1,
	.txpktctw_imw_b1_set	= B_AX_TXPKTCTW_IMW_B1_SET_V1,
	.wde_imw_cww		= B_AX_WDE_IMW_CWW_V1,
	.wde_imw_set		= B_AX_WDE_IMW_SET_V1,
	.pwe_imw_cww		= B_AX_PWE_IMW_CWW_V1,
	.pwe_imw_set		= B_AX_PWE_IMW_SET_V1,
	.host_disp_imw_cww	= B_AX_HOST_DISP_IMW_CWW_V1,
	.host_disp_imw_set	= B_AX_HOST_DISP_IMW_SET_V1,
	.cpu_disp_imw_cww	= B_AX_CPU_DISP_IMW_CWW_V1,
	.cpu_disp_imw_set	= B_AX_CPU_DISP_IMW_SET_V1,
	.othew_disp_imw_cww	= B_AX_OTHEW_DISP_IMW_CWW_V1,
	.othew_disp_imw_set	= B_AX_OTHEW_DISP_IMW_SET_V1,
	.bbwpt_com_eww_imw_weg	= W_AX_BBWPT_COM_EWW_IMW,
	.bbwpt_chinfo_eww_imw_weg = W_AX_BBWPT_CHINFO_EWW_IMW,
	.bbwpt_eww_imw_set	= W_AX_BBWPT_CHINFO_IMW_SET_V1,
	.bbwpt_dfs_eww_imw_weg	= W_AX_BBWPT_DFS_EWW_IMW,
	.ptcw_imw_cww		= B_AX_PTCW_IMW_CWW_V1,
	.ptcw_imw_set		= B_AX_PTCW_IMW_SET_V1,
	.cdma_imw_0_weg		= W_AX_WX_EWW_FWAG_IMW,
	.cdma_imw_0_cww		= B_AX_WX_EWW_IMW_CWW_V1,
	.cdma_imw_0_set		= B_AX_WX_EWW_IMW_SET_V1,
	.cdma_imw_1_weg		= W_AX_TX_EWW_FWAG_IMW,
	.cdma_imw_1_cww		= B_AX_TX_EWW_IMW_CWW_V1,
	.cdma_imw_1_set		= B_AX_TX_EWW_IMW_SET_V1,
	.phy_intf_imw_weg	= W_AX_PHYINFO_EWW_IMW_V1,
	.phy_intf_imw_cww	= B_AX_PHYINFO_IMW_CWW_V1,
	.phy_intf_imw_set	= B_AX_PHYINFO_IMW_SET_V1,
	.wmac_imw_weg		= W_AX_WX_EWW_IMW,
	.wmac_imw_cww		= B_AX_WMAC_IMW_CWW_V1,
	.wmac_imw_set		= B_AX_WMAC_IMW_SET_V1,
	.tmac_imw_weg		= W_AX_TWXPTCW_EWWOW_INDICA_MASK,
	.tmac_imw_cww		= B_AX_TMAC_IMW_CWW_V1,
	.tmac_imw_set		= B_AX_TMAC_IMW_SET_V1,
};

static const stwuct wtw89_wwsw_cfgs wtw8852c_wwsw_cfgs = {
	.wef_wate = {W_AX_TWXPTCW_WWSW_CTW_0, B_AX_WMAC_WESP_WEF_WATE_SEW, 0},
	.wsc = {W_AX_PTCW_WWSW1, B_AX_WSC_MASK, 2},
};

static const stwuct wtw89_dig_wegs wtw8852c_dig_wegs = {
	.seg0_pd_weg = W_SEG0W_PD,
	.pd_wowew_bound_mask = B_SEG0W_PD_WOWEW_BOUND_MSK,
	.pd_spatiaw_weuse_en = B_SEG0W_PD_SPATIAW_WEUSE_EN_MSK,
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
	.p0_p20_pagcugc_en = {W_PATH0_P20_FOWWOW_BY_PAGCUGC_V1,
			      B_PATH0_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p0_s20_pagcugc_en = {W_PATH0_S20_FOWWOW_BY_PAGCUGC_V1,
			      B_PATH0_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_p20_pagcugc_en = {W_PATH1_P20_FOWWOW_BY_PAGCUGC_V1,
			      B_PATH1_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_s20_pagcugc_en = {W_PATH1_S20_FOWWOW_BY_PAGCUGC_V1,
			      B_PATH1_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
};

static const stwuct wtw89_edcca_wegs wtw8852c_edcca_wegs = {
	.edcca_wevew			= W_SEG0W_EDCCA_WVW,
	.edcca_mask			= B_EDCCA_WVW_MSK0,
	.edcca_p_mask			= B_EDCCA_WVW_MSK1,
	.ppdu_wevew			= W_SEG0W_EDCCA_WVW,
	.ppdu_mask			= B_EDCCA_WVW_MSK3,
	.wpt_a				= W_EDCCA_WPT_A,
	.wpt_b				= W_EDCCA_WPT_B,
	.wpt_sew			= W_EDCCA_WPT_SEW,
	.wpt_sew_mask			= B_EDCCA_WPT_SEW_MSK,
	.tx_cowwision_t2w_st		= W_TX_COWWISION_T2W_ST,
	.tx_cowwision_t2w_st_mask	= B_TX_COWWISION_T2W_ST_M,
};

static void wtw8852c_ctww_btg_bt_wx(stwuct wtw89_dev *wtwdev, boow en,
				    enum wtw89_phy_idx phy_idx);

static void wtw8852c_ctww_tx_path_tmac(stwuct wtw89_dev *wtwdev, u8 tx_path,
				       enum wtw89_mac_idx mac_idx);

static int wtw8852c_pww_on_func(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	u32 wet;

	vaw32 = wtw89_wead32_mask(wtwdev, W_AX_SYS_STATUS1, B_AX_PAD_HCI_SEW_V2_MASK);
	if (vaw32 == MAC_AX_HCI_SEW_PCIE_USB)
		wtw89_wwite32_set(wtwdev, W_AX_WDO_AON_CTWW0, B_AX_PD_WEGU_W);

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

	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW_EXTEND, B_AX_CMAC1_FEN);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_ISO_CTWW_EXTEND, B_AX_W_SYM_ISO_CMAC12PP);
	wtw89_wwite32_cww(wtwdev, W_AX_AFE_CTWW1, B_AX_W_SYM_WWCMAC1_P4_PC_EN |
						  B_AX_W_SYM_WWCMAC1_P3_PC_EN |
						  B_AX_W_SYM_WWCMAC1_P2_PC_EN |
						  B_AX_W_SYM_WWCMAC1_P1_PC_EN |
						  B_AX_W_SYM_WWCMAC1_PC_EN);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_ADIE_PAD_PWW_CTWW, B_AX_SYM_PADPDN_WW_PTA_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW,
				      XTAW_SI_GND_SHDN_WW, XTAW_SI_GND_SHDN_WW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_SYS_ADIE_PAD_PWW_CTWW, B_AX_SYM_PADPDN_WW_WFC_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW,
				      XTAW_SI_SHDN_WW, XTAW_SI_SHDN_WW);
	if (wet)
		wetuwn wet;
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
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XTAW_XMD_2, 0, XTAW_SI_WDO_WPS);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XTAW_XMD_4, 0, XTAW_SI_WPS_CAP);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_PMC_DBG_CTWW2, B_AX_SYSON_DIS_PMCW_AX_WWMSK);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_ISO_EB2COWE);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_PWC_EV2EF_B15);

	fsweep(1000);

	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW, B_AX_PWC_EV2EF_B14);
	wtw89_wwite32_cww(wtwdev, W_AX_PMC_DBG_CTWW2, B_AX_SYSON_DIS_PMCW_AX_WWMSK);
	wtw89_wwite32_set(wtwdev, W_AX_GPIO0_15_EECS_EESK_WED1_PUWW_WOW_EN,
			  B_AX_EECS_PUWW_WOW_EN | B_AX_EESK_PUWW_WOW_EN |
			  B_AX_WED1_PUWW_WOW_EN);

	wtw89_wwite32_set(wtwdev, W_AX_DMAC_FUNC_EN,
			  B_AX_MAC_FUNC_EN | B_AX_DMAC_FUNC_EN | B_AX_MPDU_PWOC_EN |
			  B_AX_WD_WWS_EN | B_AX_DWE_WDE_EN | B_AX_TXPKT_CTWW_EN |
			  B_AX_STA_SCH_EN | B_AX_DWE_PWE_EN | B_AX_PKT_BUF_EN |
			  B_AX_DMAC_TBW_EN | B_AX_PKT_IN_EN | B_AX_DWE_CPUIO_EN |
			  B_AX_DISPATCHEW_EN | B_AX_BBWPT_EN | B_AX_MAC_SEC_EN |
			  B_AX_MAC_UN_EN | B_AX_H_AXIDMA_EN);

	wtw89_wwite32_set(wtwdev, W_AX_CMAC_FUNC_EN,
			  B_AX_CMAC_EN | B_AX_CMAC_TXEN | B_AX_CMAC_WXEN |
			  B_AX_FOWCE_CMACWEG_GCKEN | B_AX_PHYINTF_EN |
			  B_AX_CMAC_DMA_EN | B_AX_PTCWTOP_EN | B_AX_SCHEDUWEW_EN |
			  B_AX_TMAC_EN | B_AX_WMAC_EN);

	wtw89_wwite32_mask(wtwdev, W_AX_WED1_FUNC_SEW, B_AX_PINMUX_EESK_FUNC_SEW_V1_MASK,
			   PINMUX_EESK_FUNC_SEW_BT_WOG);

	wetuwn 0;
}

static int wtw8852c_pww_off_func(stwuct wtw89_dev *wtwdev)
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
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, 0, XTAW_SI_WF10);
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

	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_EN_WWON);
	wtw89_wwite8_cww(wtwdev, W_AX_SYS_FUNC_EN, B_AX_FEN_BB_GWB_WSTN | B_AX_FEN_BBWSTB);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ISO_CTWW_EXTEND,
			  B_AX_W_SYM_FEN_WWBBGWB_1 | B_AX_W_SYM_FEN_WWBBFUN_1);
	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ADIE_PAD_PWW_CTWW, B_AX_SYM_PADPDN_WW_WFC_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_SHDN_WW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_AX_SYS_ADIE_PAD_PWW_CTWW, B_AX_SYM_PADPDN_WW_PTA_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, XTAW_SI_GND_SHDN_WW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFM_OFFMAC);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_AX_APFM_OFFMAC),
				1000, 20000, fawse, wtwdev, W_AX_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32(wtwdev, W_AX_WWWPS_CTWW, 0x0001A0B0);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_XTAW_OFF_A_DIE);
	wtw89_wwite32_set(wtwdev, W_AX_SYS_PW_CTWW, B_AX_APFM_SWWPS);

	wetuwn 0;
}

static void wtw8852c_e_efuse_pawsing(stwuct wtw89_efuse *efuse,
				     stwuct wtw8852c_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->e.mac_addw);
	efuse->wfe_type = map->wfe_type;
	efuse->xtaw_cap = map->xtaw_k;
}

static void wtw8852c_efuse_pawsing_tssi(stwuct wtw89_dev *wtwdev,
					stwuct wtw8852c_efuse *map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	stwuct wtw8852c_tssi_offset *ofst[] = {&map->path_a_tssi, &map->path_b_tssi};
	u8 *bw40_1s_tssi_6g_ofst[] = {map->bw40_1s_tssi_6g_a, map->bw40_1s_tssi_6g_b};
	u8 i, j;

	tssi->thewmaw[WF_PATH_A] = map->path_a_thewm;
	tssi->thewmaw[WF_PATH_B] = map->path_b_thewm;

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
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
		memcpy(tssi->tssi_6g_mcs[i], bw40_1s_tssi_6g_ofst[i],
		       sizeof(tssi->tssi_6g_mcs[i]));

		fow (j = 0; j < TSSI_MCS_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI][EFUSE] path=%d mcs[%d]=0x%x\n",
				    i, j, tssi->tssi_mcs[i][j]);
	}
}

static boow _decode_efuse_gain(u8 data, s8 *high, s8 *wow)
{
	if (high)
		*high = sign_extend32(FIEWD_GET(GENMASK(7,  4), data), 3);
	if (wow)
		*wow = sign_extend32(FIEWD_GET(GENMASK(3,  0), data), 3);

	wetuwn data != 0xff;
}

static void wtw8852c_efuse_pawsing_gain_offset(stwuct wtw89_dev *wtwdev,
					       stwuct wtw8852c_efuse *map)
{
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;
	boow vawid = fawse;

	vawid |= _decode_efuse_gain(map->wx_gain_2g_cck,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_CCK],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_2G_CCK]);
	vawid |= _decode_efuse_gain(map->wx_gain_2g_ofdm,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_OFDM],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_2G_OFDM]);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_wow,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_WOW],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_WOW]);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_mid,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_MID],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_MID]);
	vawid |= _decode_efuse_gain(map->wx_gain_5g_high,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_HIGH],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_HIGH]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_w0,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_W0],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_W0]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_w1,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_W1],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_W1]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_m0,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_M0],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_M0]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_m1,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_M1],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_M1]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_h0,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_H0],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_H0]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_h1,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_H1],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_H1]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_uh0,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_UH0],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_UH0]);
	vawid |= _decode_efuse_gain(map->wx_gain_6g_uh1,
				    &gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_UH1],
				    &gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_UH1]);

	gain->offset_vawid = vawid;
}

static int wtw8852c_wead_efuse(stwuct wtw89_dev *wtwdev, u8 *wog_map,
			       enum wtw89_efuse_bwock bwock)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	stwuct wtw8852c_efuse *map;

	map = (stwuct wtw8852c_efuse *)wog_map;

	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	wtw8852c_efuse_pawsing_tssi(wtwdev, map);
	wtw8852c_efuse_pawsing_gain_offset(wtwdev, map);

	switch (wtwdev->hci.type) {
	case WTW89_HCI_TYPE_PCIE:
		wtw8852c_e_efuse_pawsing(efuse, map);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wtw89_info(wtwdev, "chip wfe_type is %d\n", efuse->wfe_type);

	wetuwn 0;
}

static void wtw8852c_phycap_pawsing_tssi(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	static const u32 tssi_twim_addw[WF_PATH_NUM_8852C] = {0x5D6, 0x5AB};
	static const u32 tssi_twim_addw_6g[WF_PATH_NUM_8852C] = {0x5CE, 0x5A3};
	u32 addw = wtwdev->chip->phycap_addw;
	boow pg = fawse;
	u32 ofst;
	u8 i, j;

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM; j++) {
			/* addws awe in decweasing owdew */
			ofst = tssi_twim_addw[i] - addw - j;
			tssi->tssi_twim[i][j] = phycap_map[ofst];

			if (phycap_map[ofst] != 0xff)
				pg = twue;
		}

		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM_6G; j++) {
			/* addws awe in decweasing owdew */
			ofst = tssi_twim_addw_6g[i] - addw - j;
			tssi->tssi_twim_6g[i][j] = phycap_map[ofst];

			if (phycap_map[ofst] != 0xff)
				pg = twue;
		}
	}

	if (!pg) {
		memset(tssi->tssi_twim, 0, sizeof(tssi->tssi_twim));
		memset(tssi->tssi_twim_6g, 0, sizeof(tssi->tssi_twim_6g));
		wtw89_debug(wtwdev, WTW89_DBG_TSSI,
			    "[TSSI][TWIM] no PG, set aww twim info to 0\n");
	}

	fow (i = 0; i < WF_PATH_NUM_8852C; i++)
		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI] path=%d idx=%d twim=0x%x addw=0x%x\n",
				    i, j, tssi->tssi_twim[i][j],
				    tssi_twim_addw[i] - j);
}

static void wtw8852c_phycap_pawsing_thewmaw_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 thm_twim_addw[WF_PATH_NUM_8852C] = {0x5DF, 0x5DC};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
		info->thewmaw_twim[i] = phycap_map[thm_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_twim=0x%x\n",
			    i, info->thewmaw_twim[i]);

		if (info->thewmaw_twim[i] != 0xff)
			info->pg_thewmaw_twim = twue;
	}
}

static void wtw8852c_thewmaw_twim(stwuct wtw89_dev *wtwdev)
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

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
		vaw = __thm_setting(info->thewmaw_twim[i]);
		wtw89_wwite_wf(wtwdev, i, WW_TM2, WW_TM2_OFF, vaw);

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_setting=0x%x\n",
			    i, vaw);
	}
#undef __thm_setting
}

static void wtw8852c_phycap_pawsing_pa_bias_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 pabias_twim_addw[WF_PATH_NUM_8852C] = {0x5DE, 0x5DB};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
		info->pa_bias_twim[i] = phycap_map[pabias_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d pa_bias_twim=0x%x\n",
			    i, info->pa_bias_twim[i]);

		if (info->pa_bias_twim[i] != 0xff)
			info->pg_pa_bias_twim = twue;
	}
}

static void wtw8852c_pa_bias_twim(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u8 pabias_2g, pabias_5g;
	u8 i;

	if (!info->pg_pa_bias_twim) {
		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] no PG, do nothing\n");

		wetuwn;
	}

	fow (i = 0; i < WF_PATH_NUM_8852C; i++) {
		pabias_2g = FIEWD_GET(GENMASK(3, 0), info->pa_bias_twim[i]);
		pabias_5g = FIEWD_GET(GENMASK(7, 4), info->pa_bias_twim[i]);

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d 2G=0x%x 5G=0x%x\n",
			    i, pabias_2g, pabias_5g);

		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXG, pabias_2g);
		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXA, pabias_5g);
	}
}

static int wtw8852c_wead_phycap(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	wtw8852c_phycap_pawsing_tssi(wtwdev, phycap_map);
	wtw8852c_phycap_pawsing_thewmaw_twim(wtwdev, phycap_map);
	wtw8852c_phycap_pawsing_pa_bias_twim(wtwdev, phycap_map);

	wetuwn 0;
}

static void wtw8852c_powew_twim(stwuct wtw89_dev *wtwdev)
{
	wtw8852c_thewmaw_twim(wtwdev);
	wtw8852c_pa_bias_twim(wtwdev);
}

static void wtw8852c_set_channew_mac(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_chan *chan,
				     u8 mac_idx)
{
	u32 wf_mod = wtw89_mac_weg_by_idx(wtwdev, W_AX_WMAC_WFMOD, mac_idx);
	u32 sub_caww = wtw89_mac_weg_by_idx(wtwdev, W_AX_TX_SUB_CAWWIEW_VAWUE, mac_idx);
	u32 chk_wate = wtw89_mac_weg_by_idx(wtwdev, W_AX_TXWATE_CHK, mac_idx);
	u8 txsc20 = 0, txsc40 = 0, txsc80 = 0;
	u8 wf_mod_vaw = 0, chk_wate_mask = 0;
	u32 txsc;

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_160:
		txsc80 = wtw89_phy_get_txsc(wtwdev, chan,
					    WTW89_CHANNEW_WIDTH_80);
		fawwthwough;
	case WTW89_CHANNEW_WIDTH_80:
		txsc40 = wtw89_phy_get_txsc(wtwdev, chan,
					    WTW89_CHANNEW_WIDTH_40);
		fawwthwough;
	case WTW89_CHANNEW_WIDTH_40:
		txsc20 = wtw89_phy_get_txsc(wtwdev, chan,
					    WTW89_CHANNEW_WIDTH_20);
		bweak;
	defauwt:
		bweak;
	}

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_160:
		wf_mod_vaw = AX_WMAC_WFMOD_160M;
		txsc = FIEWD_PWEP(B_AX_TXSC_20M_MASK, txsc20) |
		       FIEWD_PWEP(B_AX_TXSC_40M_MASK, txsc40) |
		       FIEWD_PWEP(B_AX_TXSC_80M_MASK, txsc80);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wf_mod_vaw = AX_WMAC_WFMOD_80M;
		txsc = FIEWD_PWEP(B_AX_TXSC_20M_MASK, txsc20) |
		       FIEWD_PWEP(B_AX_TXSC_40M_MASK, txsc40);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wf_mod_vaw = AX_WMAC_WFMOD_40M;
		txsc = FIEWD_PWEP(B_AX_TXSC_20M_MASK, txsc20);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
	defauwt:
		wf_mod_vaw = AX_WMAC_WFMOD_20M;
		txsc = 0;
		bweak;
	}
	wtw89_wwite8_mask(wtwdev, wf_mod, B_AX_WMAC_WFMOD_MASK, wf_mod_vaw);
	wtw89_wwite32(wtwdev, sub_caww, txsc);

	switch (chan->band_type) {
	case WTW89_BAND_2G:
		chk_wate_mask = B_AX_BAND_MODE;
		bweak;
	case WTW89_BAND_5G:
	case WTW89_BAND_6G:
		chk_wate_mask = B_AX_CHECK_CCK_EN | B_AX_WTS_WIMIT_IN_OFDM6;
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Invawid band_type:%d\n", chan->band_type);
		wetuwn;
	}
	wtw89_wwite8_cww(wtwdev, chk_wate, B_AX_BAND_MODE | B_AX_CHECK_CCK_EN |
					   B_AX_WTS_WIMIT_IN_OFDM6);
	wtw89_wwite8_set(wtwdev, chk_wate, chk_wate_mask);
}

static const u32 wtw8852c_sco_bawkew_thweshowd[14] = {
	0x1fe4f, 0x1ff5e, 0x2006c, 0x2017b, 0x2028a, 0x20399, 0x204a8, 0x205b6,
	0x206c5, 0x207d4, 0x208e3, 0x209f2, 0x20b00, 0x20d8a
};

static const u32 wtw8852c_sco_cck_thweshowd[14] = {
	0x2bdac, 0x2bf21, 0x2c095, 0x2c209, 0x2c37e, 0x2c4f2, 0x2c666, 0x2c7db,
	0x2c94f, 0x2cac3, 0x2cc38, 0x2cdac, 0x2cf21, 0x2d29e
};

static int wtw8852c_ctww_sco_cck(stwuct wtw89_dev *wtwdev, u8 centwaw_ch,
				 u8 pwimawy_ch, enum wtw89_bandwidth bw)
{
	u8 ch_ewement;

	if (bw == WTW89_CHANNEW_WIDTH_20) {
		ch_ewement = centwaw_ch - 1;
	} ewse if (bw == WTW89_CHANNEW_WIDTH_40) {
		if (pwimawy_ch == 1)
			ch_ewement = centwaw_ch - 1 + 2;
		ewse
			ch_ewement = centwaw_ch - 1 - 2;
	} ewse {
		wtw89_wawn(wtwdev, "Invawid BW:%d fow CCK\n", bw);
		wetuwn -EINVAW;
	}
	wtw89_phy_wwite32_mask(wtwdev, W_BK_FC0_INV_V1, B_BK_FC0_INV_MSK_V1,
			       wtw8852c_sco_bawkew_thweshowd[ch_ewement]);
	wtw89_phy_wwite32_mask(wtwdev, W_CCK_FC0_INV_V1, B_CCK_FC0_INV_MSK_V1,
			       wtw8852c_sco_cck_thweshowd[ch_ewement]);

	wetuwn 0;
}

stwuct wtw8852c_bb_gain {
	u32 gain_g[BB_PATH_NUM_8852C];
	u32 gain_a[BB_PATH_NUM_8852C];
	u32 gain_mask;
};

static const stwuct wtw8852c_bb_gain bb_gain_wna[WNA_GAIN_NUM] = {
	{ .gain_g = {0x4678, 0x475C}, .gain_a = {0x45DC, 0x4740},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x4678, 0x475C}, .gain_a = {0x45DC, 0x4740},
	  .gain_mask = 0xff000000 },
	{ .gain_g = {0x467C, 0x4760}, .gain_a = {0x4660, 0x4744},
	  .gain_mask = 0x000000ff },
	{ .gain_g = {0x467C, 0x4760}, .gain_a = {0x4660, 0x4744},
	  .gain_mask = 0x0000ff00 },
	{ .gain_g = {0x467C, 0x4760}, .gain_a = {0x4660, 0x4744},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x467C, 0x4760}, .gain_a = {0x4660, 0x4744},
	  .gain_mask = 0xff000000 },
	{ .gain_g = {0x4680, 0x4764}, .gain_a = {0x4664, 0x4748},
	  .gain_mask = 0x000000ff },
};

static const stwuct wtw8852c_bb_gain bb_gain_tia[TIA_GAIN_NUM] = {
	{ .gain_g = {0x4680, 0x4764}, .gain_a = {0x4664, 0x4748},
	  .gain_mask = 0x00ff0000 },
	{ .gain_g = {0x4680, 0x4764}, .gain_a = {0x4664, 0x4748},
	  .gain_mask = 0xff000000 },
};

stwuct wtw8852c_bb_gain_bypass {
	u32 gain_g[BB_PATH_NUM_8852C];
	u32 gain_a[BB_PATH_NUM_8852C];
	u32 gain_mask_g;
	u32 gain_mask_a;
};

static
const stwuct wtw8852c_bb_gain_bypass bb_gain_bypass_wna[WNA_GAIN_NUM] = {
	{ .gain_g = {0x4BB8, 0x4C7C}, .gain_a = {0x4BB4, 0x4C78},
	  .gain_mask_g = 0xff000000, .gain_mask_a = 0xff},
	{ .gain_g = {0x4BBC, 0x4C80}, .gain_a = {0x4BB4, 0x4C78},
	  .gain_mask_g = 0xff, .gain_mask_a = 0xff00},
	{ .gain_g = {0x4BBC, 0x4C80}, .gain_a = {0x4BB4, 0x4C78},
	  .gain_mask_g = 0xff00, .gain_mask_a = 0xff0000},
	{ .gain_g = {0x4BBC, 0x4C80}, .gain_a = {0x4BB4, 0x4C78},
	  .gain_mask_g = 0xff0000, .gain_mask_a = 0xff000000},
	{ .gain_g = {0x4BBC, 0x4C80}, .gain_a = {0x4BB8, 0x4C7C},
	  .gain_mask_g = 0xff000000, .gain_mask_a = 0xff},
	{ .gain_g = {0x4BC0, 0x4C84}, .gain_a = {0x4BB8, 0x4C7C},
	  .gain_mask_g = 0xff, .gain_mask_a = 0xff00},
	{ .gain_g = {0x4BC0, 0x4C84}, .gain_a = {0x4BB8, 0x4C7C},
	  .gain_mask_g = 0xff00, .gain_mask_a = 0xff0000},
};

stwuct wtw8852c_bb_gain_op1db {
	stwuct {
		u32 wna[BB_PATH_NUM_8852C];
		u32 tia_wna[BB_PATH_NUM_8852C];
		u32 mask;
	} weg[WNA_GAIN_NUM];
	u32 weg_tia0_wna6[BB_PATH_NUM_8852C];
	u32 mask_tia0_wna6;
};

static const stwuct wtw8852c_bb_gain_op1db bb_gain_op1db_a = {
	.weg = {
		{ .wna = {0x4668, 0x474c}, .tia_wna = {0x4670, 0x4754},
		  .mask = 0xff},
		{ .wna = {0x4668, 0x474c}, .tia_wna = {0x4670, 0x4754},
		  .mask = 0xff00},
		{ .wna = {0x4668, 0x474c}, .tia_wna = {0x4670, 0x4754},
		  .mask = 0xff0000},
		{ .wna = {0x4668, 0x474c}, .tia_wna = {0x4670, 0x4754},
		  .mask = 0xff000000},
		{ .wna = {0x466c, 0x4750}, .tia_wna = {0x4674, 0x4758},
		  .mask = 0xff},
		{ .wna = {0x466c, 0x4750}, .tia_wna = {0x4674, 0x4758},
		  .mask = 0xff00},
		{ .wna = {0x466c, 0x4750}, .tia_wna = {0x4674, 0x4758},
		  .mask = 0xff0000},
	},
	.weg_tia0_wna6 = {0x4674, 0x4758},
	.mask_tia0_wna6 = 0xff000000,
};

static void wtw8852c_set_gain_ewwow(stwuct wtw89_dev *wtwdev,
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

		if (subband == WTW89_CH_2G) {
			weg = bb_gain_bypass_wna[i].gain_g[path];
			mask = bb_gain_bypass_wna[i].gain_mask_g;
		} ewse {
			weg = bb_gain_bypass_wna[i].gain_a[path];
			mask = bb_gain_bypass_wna[i].gain_mask_a;
		}

		vaw = gain->wna_gain_bypass[gain_band][path][i];
		wtw89_phy_wwite32_mask(wtwdev, weg, mask, vaw);

		if (subband != WTW89_CH_2G) {
			weg = bb_gain_op1db_a.weg[i].wna[path];
			mask = bb_gain_op1db_a.weg[i].mask;
			vaw = gain->wna_op1db[gain_band][path][i];
			wtw89_phy_wwite32_mask(wtwdev, weg, mask, vaw);

			weg = bb_gain_op1db_a.weg[i].tia_wna[path];
			mask = bb_gain_op1db_a.weg[i].mask;
			vaw = gain->tia_wna_op1db[gain_band][path][i];
			wtw89_phy_wwite32_mask(wtwdev, weg, mask, vaw);
		}
	}

	if (subband != WTW89_CH_2G) {
		weg = bb_gain_op1db_a.weg_tia0_wna6[path];
		mask = bb_gain_op1db_a.mask_tia0_wna6;
		vaw = gain->tia_wna_op1db[gain_band][path][7];
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

static void wtw8852c_set_gain_offset(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_chan *chan,
				     enum wtw89_phy_idx phy_idx,
				     enum wtw89_wf_path path)
{
	static const u32 wssi_ofst_addw[2] = {W_PATH0_G_TIA0_WNA6_OP1DB_V1,
					      W_PATH1_G_TIA0_WNA6_OP1DB_V1};
	static const u32 wpw_mask[2] = {B_WPW_PATHA_MASK, B_WPW_PATHB_MASK};
	static const u32 wpw_tb_mask[2] = {B_WSSI_M_PATHA_MASK, B_WSSI_M_PATHB_MASK};
	stwuct wtw89_phy_efuse_gain *efuse_gain = &wtwdev->efuse_gain;
	enum wtw89_gain_offset gain_band;
	s32 offset_q0, offset_base_q4;
	s32 tmp = 0;

	if (!efuse_gain->offset_vawid)
		wetuwn;

	if (wtwdev->dbcc_en && path == WF_PATH_B)
		phy_idx = WTW89_PHY_1;

	if (chan->band_type == WTW89_BAND_2G) {
		offset_q0 = efuse_gain->offset[path][WTW89_GAIN_OFFSET_2G_CCK];
		offset_base_q4 = efuse_gain->offset_base[phy_idx];

		tmp = cwamp_t(s32, (-offset_q0 << 3) + (offset_base_q4 >> 1),
			      S8_MIN >> 1, S8_MAX >> 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WPW_OFST, B_WPW_OFST_MASK, tmp & 0x7f);
	}

	gain_band = wtw89_subband_to_gain_offset_band_of_ofdm(chan->subband_type);

	offset_q0 = -efuse_gain->offset[path][gain_band];
	offset_base_q4 = efuse_gain->offset_base[phy_idx];

	tmp = (offset_q0 << 2) + (offset_base_q4 >> 2);
	tmp = cwamp_t(s32, -tmp, S8_MIN, S8_MAX);
	wtw89_phy_wwite32_mask(wtwdev, wssi_ofst_addw[path], B_PATH0_W_G_OFST_MASK, tmp & 0xff);

	tmp = cwamp_t(s32, offset_q0 << 4, S8_MIN, S8_MAX);
	wtw89_phy_wwite32_idx(wtwdev, W_WPW_PATHAB, wpw_mask[path], tmp & 0xff, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSSI_M_PATHAB, wpw_tb_mask[path], tmp & 0xff, phy_idx);
}

static void wtw8852c_ctww_ch(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx)
{
	u8 sco;
	u16 centwaw_fweq = chan->fweq;
	u8 centwaw_ch = chan->channew;
	u8 band = chan->band_type;
	u8 subband = chan->subband_type;
	boow is_2g = band == WTW89_BAND_2G;
	u8 chan_idx;

	if (!centwaw_fweq) {
		wtw89_wawn(wtwdev, "Invawid centwaw_fweq\n");
		wetuwn;
	}

	if (phy_idx == WTW89_PHY_0) {
		/* Path A */
		wtw8852c_set_gain_ewwow(wtwdev, subband, WF_PATH_A);
		wtw8852c_set_gain_offset(wtwdev, chan, phy_idx, WF_PATH_A);

		if (is_2g)
			wtw89_phy_wwite32_idx(wtwdev, W_PATH0_BAND_SEW_V1,
					      B_PATH0_BAND_SEW_MSK_V1, 1,
					      phy_idx);
		ewse
			wtw89_phy_wwite32_idx(wtwdev, W_PATH0_BAND_SEW_V1,
					      B_PATH0_BAND_SEW_MSK_V1, 0,
					      phy_idx);
		/* Path B */
		if (!wtwdev->dbcc_en) {
			wtw8852c_set_gain_ewwow(wtwdev, subband, WF_PATH_B);
			wtw8852c_set_gain_offset(wtwdev, chan, phy_idx, WF_PATH_B);

			if (is_2g)
				wtw89_phy_wwite32_idx(wtwdev,
						      W_PATH1_BAND_SEW_V1,
						      B_PATH1_BAND_SEW_MSK_V1,
						      1, phy_idx);
			ewse
				wtw89_phy_wwite32_idx(wtwdev,
						      W_PATH1_BAND_SEW_V1,
						      B_PATH1_BAND_SEW_MSK_V1,
						      0, phy_idx);
			wtw89_phy_wwite32_cww(wtwdev, W_2P4G_BAND, B_2P4G_BAND_SEW);
		} ewse {
			if (is_2g)
				wtw89_phy_wwite32_cww(wtwdev, W_2P4G_BAND, B_2P4G_BAND_SEW);
			ewse
				wtw89_phy_wwite32_set(wtwdev, W_2P4G_BAND, B_2P4G_BAND_SEW);
		}
		/* SCO compensate FC setting */
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_V1, B_FC0_MSK_V1,
				      centwaw_fweq, phy_idx);
		/* wound_up((1/fc0)*pow(2,18)) */
		sco = DIV_WOUND_CWOSEST(1 << 18, centwaw_fweq);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_INV, sco,
				      phy_idx);
	} ewse {
		/* Path B */
		wtw8852c_set_gain_ewwow(wtwdev, subband, WF_PATH_B);
		wtw8852c_set_gain_offset(wtwdev, chan, phy_idx, WF_PATH_B);

		if (is_2g)
			wtw89_phy_wwite32_idx(wtwdev, W_PATH1_BAND_SEW_V1,
					      B_PATH1_BAND_SEW_MSK_V1,
					      1, phy_idx);
		ewse
			wtw89_phy_wwite32_idx(wtwdev, W_PATH1_BAND_SEW_V1,
					      B_PATH1_BAND_SEW_MSK_V1,
					      0, phy_idx);
		/* SCO compensate FC setting */
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_V1, B_FC0_MSK_V1,
				      centwaw_fweq, phy_idx);
		/* wound_up((1/fc0)*pow(2,18)) */
		sco = DIV_WOUND_CWOSEST(1 << 18, centwaw_fweq);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_INV, sco,
				      phy_idx);
	}
	/* CCK pawametews */
	if (band == WTW89_BAND_2G) {
		if (centwaw_ch == 14) {
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF0_V1,
					       B_PCOEFF01_MSK_V1, 0x3b13ff);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF2_V1,
					       B_PCOEFF23_MSK_V1, 0x1c42de);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF4_V1,
					       B_PCOEFF45_MSK_V1, 0xfdb0ad);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF6_V1,
					       B_PCOEFF67_MSK_V1, 0xf60f6e);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF8_V1,
					       B_PCOEFF89_MSK_V1, 0xfd8f92);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFA_V1,
					       B_PCOEFFAB_MSK_V1, 0x2d011);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFC_V1,
					       B_PCOEFFCD_MSK_V1, 0x1c02c);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFE_V1,
					       B_PCOEFFEF_MSK_V1, 0xfff00a);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF0_V1,
					       B_PCOEFF01_MSK_V1, 0x3d23ff);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF2_V1,
					       B_PCOEFF23_MSK_V1, 0x29b354);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF4_V1,
					       B_PCOEFF45_MSK_V1, 0xfc1c8);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF6_V1,
					       B_PCOEFF67_MSK_V1, 0xfdb053);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFF8_V1,
					       B_PCOEFF89_MSK_V1, 0xf86f9a);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFA_V1,
					       B_PCOEFFAB_MSK_V1, 0xfaef92);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFC_V1,
					       B_PCOEFFCD_MSK_V1, 0xfe5fcc);
			wtw89_phy_wwite32_mask(wtwdev, W_PCOEFFE_V1,
					       B_PCOEFFEF_MSK_V1, 0xffdff5);
		}
	}

	chan_idx = wtw89_encode_chan_idx(wtwdev, chan->pwimawy_channew, band);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_PIN_SEW, B_CH_IDX_SEG0, chan_idx, phy_idx);
}

static void wtw8852c_bw_setting(stwuct wtw89_dev *wtwdev, u8 bw, u8 path)
{
	static const u32 adc_sew[2] = {0xC0EC, 0xC1EC};
	static const u32 wbadc_sew[2] = {0xC0E4, 0xC1E4};

	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x0);
		bweak;
	case WTW89_CHANNEW_WIDTH_10:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x1);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
	case WTW89_CHANNEW_WIDTH_40:
	case WTW89_CHANNEW_WIDTH_80:
	case WTW89_CHANNEW_WIDTH_160:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x2);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to set ADC\n");
	}
}

static void wtw8852c_edcca_pew20_bitmap_sifs(stwuct wtw89_dev *wtwdev, u8 bw,
					     enum wtw89_phy_idx phy_idx)
{
	if (bw == WTW89_CHANNEW_WIDTH_20) {
		wtw89_phy_wwite32_idx(wtwdev, W_SNDCCA_A1, B_SNDCCA_A1_EN, 0xff, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_SNDCCA_A2, B_SNDCCA_A2_VAW, 0, phy_idx);
	} ewse {
		wtw89_phy_wwite32_idx(wtwdev, W_SNDCCA_A1, B_SNDCCA_A1_EN, 0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_SNDCCA_A2, B_SNDCCA_A2_VAW, 0, phy_idx);
	}
}

static void
wtw8852c_ctww_bw(stwuct wtw89_dev *wtwdev, u8 pwi_ch, u8 bw,
		 enum wtw89_phy_idx phy_idx)
{
	u8 mod_sbw = 0;

	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
	case WTW89_CHANNEW_WIDTH_10:
	case WTW89_CHANNEW_WIDTH_20:
		if (bw == WTW89_CHANNEW_WIDTH_5)
			mod_sbw = 0x1;
		ewse if (bw == WTW89_CHANNEW_WIDTH_10)
			mod_sbw = 0x2;
		ewse if (bw == WTW89_CHANNEW_WIDTH_20)
			mod_sbw = 0x0;
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW,
				      mod_sbw, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_SAMPW_DWY_T_V1,
				       B_PATH0_SAMPW_DWY_T_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_SAMPW_DWY_T_V1,
				       B_PATH1_SAMPW_DWY_T_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BW_SEW_V1,
				       B_PATH0_BW_SEW_MSK_V1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BW_SEW_V1,
				       B_PATH1_BW_SEW_MSK_V1, 0xf);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x1,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      pwi_ch,
				      phy_idx);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_SAMPW_DWY_T_V1,
				       B_PATH0_SAMPW_DWY_T_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_SAMPW_DWY_T_V1,
				       B_PATH1_SAMPW_DWY_T_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BW_SEW_V1,
				       B_PATH0_BW_SEW_MSK_V1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BW_SEW_V1,
				       B_PATH1_BW_SEW_MSK_V1, 0xf);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x2,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      pwi_ch,
				      phy_idx);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_SAMPW_DWY_T_V1,
				       B_PATH0_SAMPW_DWY_T_MSK_V1, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_SAMPW_DWY_T_V1,
				       B_PATH1_SAMPW_DWY_T_MSK_V1, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BW_SEW_V1,
				       B_PATH0_BW_SEW_MSK_V1, 0xd);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BW_SEW_V1,
				       B_PATH1_BW_SEW_MSK_V1, 0xd);
		bweak;
	case WTW89_CHANNEW_WIDTH_160:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x3,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      pwi_ch,
				      phy_idx);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_SAMPW_DWY_T_V1,
				       B_PATH0_SAMPW_DWY_T_MSK_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_SAMPW_DWY_T_V1,
				       B_PATH1_SAMPW_DWY_T_MSK_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BW_SEW_V1,
				       B_PATH0_BW_SEW_MSK_V1, 0xb);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BW_SEW_V1,
				       B_PATH1_BW_SEW_MSK_V1, 0xb);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to switch bw (bw:%d, pwi ch:%d)\n", bw,
			   pwi_ch);
	}

	if (bw == WTW89_CHANNEW_WIDTH_40) {
		wtw89_phy_wwite32_idx(wtwdev, W_WX_BW40_2XFFT_EN_V1,
				      B_WX_BW40_2XFFT_EN_MSK_V1, 0x1, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_T2F_GI_COMB, B_T2F_GI_COMB_EN, 1, phy_idx);
	} ewse {
		wtw89_phy_wwite32_idx(wtwdev, W_WX_BW40_2XFFT_EN_V1,
				      B_WX_BW40_2XFFT_EN_MSK_V1, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_T2F_GI_COMB, B_T2F_GI_COMB_EN, 0, phy_idx);
	}

	if (phy_idx == WTW89_PHY_0) {
		wtw8852c_bw_setting(wtwdev, bw, WF_PATH_A);
		if (!wtwdev->dbcc_en)
			wtw8852c_bw_setting(wtwdev, bw, WF_PATH_B);
	} ewse {
		wtw8852c_bw_setting(wtwdev, bw, WF_PATH_B);
	}

	wtw8852c_edcca_pew20_bitmap_sifs(wtwdev, bw, phy_idx);
}

static u32 wtw8852c_spuw_fweq(stwuct wtw89_dev *wtwdev,
			      const stwuct wtw89_chan *chan)
{
	u8 centew_chan = chan->channew;
	u8 bw = chan->band_width;

	switch (chan->band_type) {
	case WTW89_BAND_2G:
		if (bw == WTW89_CHANNEW_WIDTH_20) {
			if (centew_chan >= 5 && centew_chan <= 8)
				wetuwn 2440;
			if (centew_chan == 13)
				wetuwn 2480;
		} ewse if (bw == WTW89_CHANNEW_WIDTH_40) {
			if (centew_chan >= 3 && centew_chan <= 10)
				wetuwn 2440;
		}
		bweak;
	case WTW89_BAND_5G:
		if (centew_chan == 151 || centew_chan == 153 ||
		    centew_chan == 155 || centew_chan == 163)
			wetuwn 5760;
		bweak;
	case WTW89_BAND_6G:
		if (centew_chan == 195 || centew_chan == 197 ||
		    centew_chan == 199 || centew_chan == 207)
			wetuwn 6920;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

#define CAWWIEW_SPACING_312_5 312500 /* 312.5 kHz */
#define CAWWIEW_SPACING_78_125 78125 /* 78.125 kHz */
#define MAX_TONE_NUM 2048

static void wtw8852c_set_csi_tone_idx(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_phy_idx phy_idx)
{
	u32 spuw_fweq;
	s32 fweq_diff, csi_idx, csi_tone_idx;

	spuw_fweq = wtw8852c_spuw_fweq(wtwdev, chan);
	if (spuw_fweq == 0) {
		wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN, 0, phy_idx);
		wetuwn;
	}

	fweq_diff = (spuw_fweq - chan->fweq) * 1000000;
	csi_idx = s32_div_u32_wound_cwosest(fweq_diff, CAWWIEW_SPACING_78_125);
	s32_div_u32_wound_down(csi_idx, MAX_TONE_NUM, &csi_tone_idx);

	wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI, B_SEG0CSI_IDX, csi_tone_idx, phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN, 1, phy_idx);
}

static const stwuct wtw89_nbi_weg_def wtw8852c_nbi_weg_def[] = {
	[WF_PATH_A] = {
		.notch1_idx = {0x4C14, 0xFF},
		.notch1_fwac_idx = {0x4C14, 0xC00},
		.notch1_en = {0x4C14, 0x1000},
		.notch2_idx = {0x4C20, 0xFF},
		.notch2_fwac_idx = {0x4C20, 0xC00},
		.notch2_en = {0x4C20, 0x1000},
	},
	[WF_PATH_B] = {
		.notch1_idx = {0x4CD8, 0xFF},
		.notch1_fwac_idx = {0x4CD8, 0xC00},
		.notch1_en = {0x4CD8, 0x1000},
		.notch2_idx = {0x4CE4, 0xFF},
		.notch2_fwac_idx = {0x4CE4, 0xC00},
		.notch2_en = {0x4CE4, 0x1000},
	},
};

static void wtw8852c_set_nbi_tone_idx(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_wf_path path)
{
	const stwuct wtw89_nbi_weg_def *nbi = &wtw8852c_nbi_weg_def[path];
	u32 spuw_fweq, fc;
	s32 fweq_diff;
	s32 nbi_idx, nbi_tone_idx;
	s32 nbi_fwac_idx, nbi_fwac_tone_idx;
	boow notch2_chk = fawse;

	spuw_fweq = wtw8852c_spuw_fweq(wtwdev, chan);
	if (spuw_fweq == 0) {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw, nbi->notch1_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw, nbi->notch1_en.mask, 0);
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
	nbi_idx = s32_div_u32_wound_down(fweq_diff, CAWWIEW_SPACING_312_5, &nbi_fwac_idx);

	if (chan->band_width == WTW89_CHANNEW_WIDTH_20) {
		s32_div_u32_wound_down(nbi_idx + 32, 64, &nbi_tone_idx);
	} ewse {
		u16 tone_pawa = (chan->band_width == WTW89_CHANNEW_WIDTH_40) ?
				128 : 256;

		s32_div_u32_wound_down(nbi_idx, tone_pawa, &nbi_tone_idx);
	}
	nbi_fwac_tone_idx = s32_div_u32_wound_cwosest(nbi_fwac_idx, CAWWIEW_SPACING_78_125);

	if (chan->band_width == WTW89_CHANNEW_WIDTH_160 && notch2_chk) {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_idx.addw,
				       nbi->notch2_idx.mask, nbi_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_fwac_idx.addw,
				       nbi->notch2_fwac_idx.mask, nbi_fwac_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw, nbi->notch2_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw, nbi->notch2_en.mask, 1);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw, nbi->notch1_en.mask, 0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_idx.addw,
				       nbi->notch1_idx.mask, nbi_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_fwac_idx.addw,
				       nbi->notch1_fwac_idx.mask, nbi_fwac_tone_idx);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw, nbi->notch1_en.mask, 0);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch1_en.addw, nbi->notch1_en.mask, 1);
		wtw89_phy_wwite32_mask(wtwdev, nbi->notch2_en.addw, nbi->notch2_en.mask, 0);
	}
}

static void wtw8852c_spuw_notch(stwuct wtw89_dev *wtwdev, u32 vaw,
				enum wtw89_phy_idx phy_idx)
{
	u32 notch;
	u32 notch2;

	if (phy_idx == WTW89_PHY_0) {
		notch = W_PATH0_NOTCH;
		notch2 = W_PATH0_NOTCH2;
	} ewse {
		notch = W_PATH1_NOTCH;
		notch2 = W_PATH1_NOTCH2;
	}

	wtw89_phy_wwite32_mask(wtwdev, notch,
			       B_PATH0_NOTCH_VAW | B_PATH0_NOTCH_EN, vaw);
	wtw89_phy_wwite32_set(wtwdev, notch, B_PATH0_NOTCH_EN);
	wtw89_phy_wwite32_mask(wtwdev, notch2,
			       B_PATH0_NOTCH2_VAW | B_PATH0_NOTCH2_EN, vaw);
	wtw89_phy_wwite32_set(wtwdev, notch2, B_PATH0_NOTCH2_EN);
}

static void wtw8852c_spuw_ewimination(stwuct wtw89_dev *wtwdev,
				      const stwuct wtw89_chan *chan,
				      u8 pwi_ch_idx,
				      enum wtw89_phy_idx phy_idx)
{
	wtw8852c_set_csi_tone_idx(wtwdev, chan, phy_idx);

	if (phy_idx == WTW89_PHY_0) {
		if (chan->band_width == WTW89_CHANNEW_WIDTH_160 &&
		    (pwi_ch_idx == WTW89_SC_20_WOWEW ||
		     pwi_ch_idx == WTW89_SC_20_UP3X)) {
			wtw8852c_spuw_notch(wtwdev, 0xe7f, WTW89_PHY_0);
			if (!wtwdev->dbcc_en)
				wtw8852c_spuw_notch(wtwdev, 0xe7f, WTW89_PHY_1);
		} ewse if (chan->band_width == WTW89_CHANNEW_WIDTH_160 &&
			   (pwi_ch_idx == WTW89_SC_20_UPPEW ||
			    pwi_ch_idx == WTW89_SC_20_WOW3X)) {
			wtw8852c_spuw_notch(wtwdev, 0x280, WTW89_PHY_0);
			if (!wtwdev->dbcc_en)
				wtw8852c_spuw_notch(wtwdev, 0x280, WTW89_PHY_1);
		} ewse {
			wtw8852c_set_nbi_tone_idx(wtwdev, chan, WF_PATH_A);
			if (!wtwdev->dbcc_en)
				wtw8852c_set_nbi_tone_idx(wtwdev, chan,
							  WF_PATH_B);
		}
	} ewse {
		if (chan->band_width == WTW89_CHANNEW_WIDTH_160 &&
		    (pwi_ch_idx == WTW89_SC_20_WOWEW ||
		     pwi_ch_idx == WTW89_SC_20_UP3X)) {
			wtw8852c_spuw_notch(wtwdev, 0xe7f, WTW89_PHY_1);
		} ewse if (chan->band_width == WTW89_CHANNEW_WIDTH_160 &&
			   (pwi_ch_idx == WTW89_SC_20_UPPEW ||
			    pwi_ch_idx == WTW89_SC_20_WOW3X)) {
			wtw8852c_spuw_notch(wtwdev, 0x280, WTW89_PHY_1);
		} ewse {
			wtw8852c_set_nbi_tone_idx(wtwdev, chan, WF_PATH_B);
		}
	}

	if (pwi_ch_idx == WTW89_SC_20_UP3X || pwi_ch_idx == WTW89_SC_20_WOW3X)
		wtw89_phy_wwite32_idx(wtwdev, W_PD_BOOST_EN, B_PD_BOOST_EN, 0, phy_idx);
	ewse
		wtw89_phy_wwite32_idx(wtwdev, W_PD_BOOST_EN, B_PD_BOOST_EN, 1, phy_idx);
}

static void wtw8852c_5m_mask(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_chan *chan,
			     enum wtw89_phy_idx phy_idx)
{
	u8 pwi_ch = chan->pwi_ch_idx;
	boow mask_5m_wow;
	boow mask_5m_en;

	switch (chan->band_width) {
	case WTW89_CHANNEW_WIDTH_40:
		mask_5m_en = twue;
		mask_5m_wow = pwi_ch == WTW89_SC_20_WOWEW;
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		mask_5m_en = pwi_ch == WTW89_SC_20_UPMOST ||
			     pwi_ch == WTW89_SC_20_WOWEST;
		mask_5m_wow = pwi_ch == WTW89_SC_20_WOWEST;
		bweak;
	defauwt:
		mask_5m_en = fawse;
		mask_5m_wow = fawse;
		bweak;
	}

	if (!mask_5m_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_EN, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_EN, 0x0);
		wtw89_phy_wwite32_idx(wtwdev, W_ASSIGN_SBD_OPT,
				      B_ASSIGN_SBD_OPT_EN, 0x0, phy_idx);
	} ewse {
		if (mask_5m_wow) {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_TH, 0x4);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_EN, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_SB2, 0x0);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_SB0, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_TH, 0x4);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_EN, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_SB2, 0x0);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_SB0, 0x1);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_TH, 0x4);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_EN, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_SB2, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH0_5MDET, B_PATH0_5MDET_SB0, 0x0);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_TH, 0x4);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_EN, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_SB2, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_PATH1_5MDET, B_PATH1_5MDET_SB0, 0x0);
		}
		wtw89_phy_wwite32_idx(wtwdev, W_ASSIGN_SBD_OPT, B_ASSIGN_SBD_OPT_EN, 0x1, phy_idx);
	}
}

static void wtw8852c_bb_weset_aww(stwuct wtw89_dev *wtwdev,
				  enum wtw89_phy_idx phy_idx)
{
	/*HW SI weset*/
	wtw89_phy_wwite32_mask(wtwdev, W_S0_HW_SI_DIS, B_S0_HW_SI_DIS_W_W_TWIG,
			       0x7);
	wtw89_phy_wwite32_mask(wtwdev, W_S1_HW_SI_DIS, B_S1_HW_SI_DIS_W_W_TWIG,
			       0x7);

	udeway(1);

	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1,
			      phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0,
			      phy_idx);
	/*HW SI weset*/
	wtw89_phy_wwite32_mask(wtwdev, W_S0_HW_SI_DIS, B_S0_HW_SI_DIS_W_W_TWIG,
			       0x0);
	wtw89_phy_wwite32_mask(wtwdev, W_S1_HW_SI_DIS, B_S1_HW_SI_DIS_W_W_TWIG,
			       0x0);

	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1,
			      phy_idx);
}

static void wtw8852c_bb_weset_en(stwuct wtw89_dev *wtwdev, enum wtw89_band band,
				 enum wtw89_phy_idx phy_idx, boow en)
{
	if (en) {
		wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS,
				      B_S0_HW_SI_DIS_W_W_TWIG, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_S1_HW_SI_DIS,
				      B_S1_HW_SI_DIS_W_W_TWIG, 0x0, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1,
				      phy_idx);
		if (band == WTW89_BAND_2G)
			wtw89_phy_wwite32_mask(wtwdev, W_WXCCA_V1, B_WXCCA_DIS_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 0x0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA_V1, B_WXCCA_DIS_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 0x1);
		wtw89_phy_wwite32_idx(wtwdev, W_S0_HW_SI_DIS,
				      B_S0_HW_SI_DIS_W_W_TWIG, 0x7, phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_S1_HW_SI_DIS,
				      B_S1_HW_SI_DIS_W_W_TWIG, 0x7, phy_idx);
		fsweep(1);
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0,
				      phy_idx);
	}
}

static void wtw8852c_bb_weset(stwuct wtw89_dev *wtwdev,
			      enum wtw89_phy_idx phy_idx)
{
	wtw8852c_bb_weset_aww(wtwdev, phy_idx);
}

static
void wtw8852c_bb_gpio_twsw(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path path,
			   u8 tx_path_en, u8 twsw_tx,
			   u8 twsw_wx, u8 twsw, u8 twsw_b)
{
	static const u32 path_cw_bases[] = {0x5868, 0x7868};
	u32 mask_ofst = 16;
	u32 cw;
	u32 vaw;

	if (path >= AWWAY_SIZE(path_cw_bases))
		wetuwn;

	cw = path_cw_bases[path];

	mask_ofst += (tx_path_en * 4 + twsw_tx * 2 + twsw_wx) * 2;
	vaw = FIEWD_PWEP(B_P0_TWSW_A, twsw) | FIEWD_PWEP(B_P0_TWSW_B, twsw_b);

	wtw89_phy_wwite32_mask(wtwdev, cw, (B_P0_TWSW_A | B_P0_TWSW_B) << mask_ofst, vaw);
}

enum wtw8852c_wfe_swc {
	PAPE_WFM,
	TWSW_WFM,
	WNAON_WFM,
};

static
void wtw8852c_bb_gpio_wfm(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path path,
			  enum wtw8852c_wfe_swc swc, u8 dis_tx_gnt_ww,
			  u8 active_tx_opt, u8 act_bt_en, u8 wfm_output_vaw)
{
	static const u32 path_cw_bases[] = {0x5894, 0x7894};
	static const u32 masks[] = {0, 8, 16};
	u32 mask, mask_ofst;
	u32 cw;
	u32 vaw;

	if (swc >= AWWAY_SIZE(masks) || path >= AWWAY_SIZE(path_cw_bases))
		wetuwn;

	mask_ofst = masks[swc];
	cw = path_cw_bases[path];

	vaw = FIEWD_PWEP(B_P0_WFM_DIS_WW, dis_tx_gnt_ww) |
	      FIEWD_PWEP(B_P0_WFM_TX_OPT, active_tx_opt) |
	      FIEWD_PWEP(B_P0_WFM_BT_EN, act_bt_en) |
	      FIEWD_PWEP(B_P0_WFM_OUT, wfm_output_vaw);
	mask = 0xff << mask_ofst;

	wtw89_phy_wwite32_mask(wtwdev, cw, mask, vaw);
}

static void wtw8852c_bb_gpio_init(stwuct wtw89_dev *wtwdev)
{
	static const u32 cw_bases[] = {0x5800, 0x7800};
	u32 addw;
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(cw_bases); i++) {
		addw = cw_bases[i];
		wtw89_phy_wwite32_set(wtwdev, (addw | 0x68), B_P0_TWSW_A);
		wtw89_phy_wwite32_cww(wtwdev, (addw | 0x68), B_P0_TWSW_X);
		wtw89_phy_wwite32_cww(wtwdev, (addw | 0x68), B_P0_TWSW_SO_A2);
		wtw89_phy_wwite32(wtwdev, (addw | 0x80), 0x77777777);
		wtw89_phy_wwite32(wtwdev, (addw | 0x84), 0x77777777);
	}

	wtw89_phy_wwite32(wtwdev, W_WFE_E_A2, 0xffffffff);
	wtw89_phy_wwite32(wtwdev, W_WFE_O_SEW_A2, 0);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW0_A2, 0);
	wtw89_phy_wwite32(wtwdev, W_WFE_SEW32_A2, 0);

	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 0, 0, 0, 1);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 0, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 1, 0, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 0, 1, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 0, 0, 0, 1);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 0, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 1, 0, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_A, 1, 1, 1, 1, 0);

	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 0, 0, 0, 0, 1);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 0, 0, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 0, 1, 0, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 0, 1, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 1, 0, 0, 0, 1);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 1, 0, 1, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 1, 1, 0, 1, 0);
	wtw8852c_bb_gpio_twsw(wtwdev, WF_PATH_B, 1, 1, 1, 1, 0);

	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_A, PAPE_WFM, 0, 0, 0, 0x0);
	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_A, TWSW_WFM, 0, 0, 0, 0x4);
	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_A, WNAON_WFM, 0, 0, 0, 0x8);

	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_B, PAPE_WFM, 0, 0, 0, 0x0);
	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_B, TWSW_WFM, 0, 0, 0, 0x4);
	wtw8852c_bb_gpio_wfm(wtwdev, WF_PATH_B, WNAON_WFM, 0, 0, 0, 0x8);
}

static void wtw8852c_bb_macid_ctww_init(stwuct wtw89_dev *wtwdev,
					enum wtw89_phy_idx phy_idx)
{
	u32 addw;

	fow (addw = W_AX_PWW_MACID_WMT_TABWE0;
	     addw <= W_AX_PWW_MACID_WMT_TABWE127; addw += 4)
		wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, 0);
}

static void wtw8852c_bb_sethw(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;

	wtw89_phy_wwite32_set(wtwdev, W_DBCC_80P80_SEW_EVM_WPT,
			      B_DBCC_80P80_SEW_EVM_WPT_EN);
	wtw89_phy_wwite32_set(wtwdev, W_DBCC_80P80_SEW_EVM_WPT2,
			      B_DBCC_80P80_SEW_EVM_WPT2_EN);

	wtw8852c_bb_macid_ctww_init(wtwdev, WTW89_PHY_0);
	wtw8852c_bb_gpio_init(wtwdev);

	/* wead these wegistews aftew woading BB pawametews */
	gain->offset_base[WTW89_PHY_0] =
		wtw89_phy_wead32_mask(wtwdev, W_WPW_BIAS_COMP, B_WPW_BIAS_COMP_MASK);
	gain->offset_base[WTW89_PHY_1] =
		wtw89_phy_wead32_mask(wtwdev, W_WPW_BIAS_COMP1, B_WPW_BIAS_COMP1_MASK);
}

static void wtw8852c_set_channew_bb(stwuct wtw89_dev *wtwdev,
				    const stwuct wtw89_chan *chan,
				    enum wtw89_phy_idx phy_idx)
{
	static const u32 wu_awwoc_msk[2] = {B_P80_AT_HIGH_FWEQ_WU_AWWOC_PHY0,
					    B_P80_AT_HIGH_FWEQ_WU_AWWOC_PHY1};
	stwuct wtw89_haw *haw = &wtwdev->haw;
	boow cck_en = chan->band_type == WTW89_BAND_2G;
	u8 pwi_ch_idx = chan->pwi_ch_idx;
	u32 mask, weg;
	u8 ntx_path;

	if (chan->band_type == WTW89_BAND_2G)
		wtw8852c_ctww_sco_cck(wtwdev, chan->channew,
				      chan->pwimawy_channew,
				      chan->band_width);

	wtw8852c_ctww_ch(wtwdev, chan, phy_idx);
	wtw8852c_ctww_bw(wtwdev, pwi_ch_idx, chan->band_width, phy_idx);
	if (cck_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_CWK_ADC, B_ENABWE_CCK, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA_V1, B_WXCCA_DIS_V1, 0);
		wtw89_phy_wwite32_idx(wtwdev, W_PD_AWBITEW_OFF,
				      B_PD_AWBITEW_OFF, 0x0, phy_idx);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_CWK_ADC, B_ENABWE_CCK, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA_V1, B_WXCCA_DIS_V1, 1);
		wtw89_phy_wwite32_idx(wtwdev, W_PD_AWBITEW_OFF,
				      B_PD_AWBITEW_OFF, 0x1, phy_idx);
	}

	wtw8852c_spuw_ewimination(wtwdev, chan, pwi_ch_idx, phy_idx);
	wtw8852c_ctww_btg_bt_wx(wtwdev, chan->band_type == WTW89_BAND_2G,
				WTW89_PHY_0);
	wtw8852c_5m_mask(wtwdev, chan, phy_idx);

	if (chan->band_width == WTW89_CHANNEW_WIDTH_160 &&
	    wtwdev->haw.cv != CHIP_CAV) {
		wtw89_phy_wwite32_idx(wtwdev, W_P80_AT_HIGH_FWEQ,
				      B_P80_AT_HIGH_FWEQ, 0x0, phy_idx);
		weg = wtw89_mac_weg_by_idx(wtwdev, W_P80_AT_HIGH_FWEQ_BB_WWP, phy_idx);
		if (chan->pwimawy_channew > chan->channew) {
			wtw89_phy_wwite32_mask(wtwdev,
					       W_P80_AT_HIGH_FWEQ_WU_AWWOC,
					       wu_awwoc_msk[phy_idx], 1);
			wtw89_wwite32_mask(wtwdev, weg,
					   B_P80_AT_HIGH_FWEQ_BB_WWP, 1);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev,
					       W_P80_AT_HIGH_FWEQ_WU_AWWOC,
					       wu_awwoc_msk[phy_idx], 0);
			wtw89_wwite32_mask(wtwdev, weg,
					   B_P80_AT_HIGH_FWEQ_BB_WWP, 0);
		}
	}

	if (chan->band_type == WTW89_BAND_6G &&
	    chan->band_width == WTW89_CHANNEW_WIDTH_160)
		wtw89_phy_wwite32_idx(wtwdev, W_CDD_EVM_CHK_EN,
				      B_CDD_EVM_CHK_EN, 0, phy_idx);
	ewse
		wtw89_phy_wwite32_idx(wtwdev, W_CDD_EVM_CHK_EN,
				      B_CDD_EVM_CHK_EN, 1, phy_idx);

	if (!wtwdev->dbcc_en) {
		mask = B_P0_TXPW_WSTB_TSSI | B_P0_TXPW_WSTB_MANON;
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, mask, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, mask, 0x3);
		mask = B_P1_TXPW_WSTB_TSSI | B_P1_TXPW_WSTB_MANON;
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, mask, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, mask, 0x3);
	} ewse {
		if (phy_idx == WTW89_PHY_0) {
			mask = B_P0_TXPW_WSTB_TSSI | B_P0_TXPW_WSTB_MANON;
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, mask, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, mask, 0x3);
		} ewse {
			mask = B_P1_TXPW_WSTB_TSSI | B_P1_TXPW_WSTB_MANON;
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, mask, 0x1);
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, mask, 0x3);
		}
	}

	if (chan->band_type == WTW89_BAND_6G)
		wtw89_phy_wwite32_set(wtwdev, W_MUIC, B_MUIC_EN);
	ewse
		wtw89_phy_wwite32_cww(wtwdev, W_MUIC, B_MUIC_EN);

	if (haw->antenna_tx)
		ntx_path = haw->antenna_tx;
	ewse
		ntx_path = chan->band_type == WTW89_BAND_6G ? WF_B : WF_AB;

	wtw8852c_ctww_tx_path_tmac(wtwdev, ntx_path, (enum wtw89_mac_idx)phy_idx);

	wtw8852c_bb_weset_aww(wtwdev, phy_idx);
}

static void wtw8852c_set_channew(stwuct wtw89_dev *wtwdev,
				 const stwuct wtw89_chan *chan,
				 enum wtw89_mac_idx mac_idx,
				 enum wtw89_phy_idx phy_idx)
{
	wtw8852c_set_channew_mac(wtwdev, chan, mac_idx);
	wtw8852c_set_channew_bb(wtwdev, chan, phy_idx);
	wtw8852c_set_channew_wf(wtwdev, chan, phy_idx);
}

static void wtw8852c_dfs_en(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_P0, B_UPD_P0_EN, 1);
	ewse
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_P0, B_UPD_P0_EN, 0);
}

static void wtw8852c_adc_en(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST,
				       0x0);
	ewse
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST,
				       0xf);
}

static void wtw8852c_set_channew_hewp(stwuct wtw89_dev *wtwdev, boow entew,
				      stwuct wtw89_channew_hewp_pawams *p,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_mac_idx mac_idx,
				      enum wtw89_phy_idx phy_idx)
{
	if (entew) {
		wtw89_chip_stop_sch_tx(wtwdev, mac_idx, &p->tx_en,
				       WTW89_SCH_TX_SEW_AWW);
		wtw89_mac_cfg_ppdu_status(wtwdev, mac_idx, fawse);
		wtw8852c_dfs_en(wtwdev, fawse);
		wtw8852c_tssi_cont_en_phyidx(wtwdev, fawse, phy_idx);
		wtw8852c_adc_en(wtwdev, fawse);
		fsweep(40);
		wtw8852c_bb_weset_en(wtwdev, chan->band_type, phy_idx, fawse);
	} ewse {
		wtw89_mac_cfg_ppdu_status(wtwdev, mac_idx, twue);
		wtw8852c_adc_en(wtwdev, twue);
		wtw8852c_dfs_en(wtwdev, twue);
		wtw8852c_tssi_cont_en_phyidx(wtwdev, twue, phy_idx);
		wtw8852c_bb_weset_en(wtwdev, chan->band_type, phy_idx, twue);
		wtw89_chip_wesume_sch_tx(wtwdev, mac_idx, p->tx_en);
	}
}

static void wtw8852c_wfk_init(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_wfk_mcc_info *wfk_mcc = &wtwdev->wfk_mcc;

	wtwdev->is_tssi_mode[WF_PATH_A] = fawse;
	wtwdev->is_tssi_mode[WF_PATH_B] = fawse;
	memset(wfk_mcc, 0, sizeof(*wfk_mcc));
	wtw8852c_wck_init(wtwdev);
	wtw8852c_dpk_init(wtwdev);

	wtw8852c_wck(wtwdev);
	wtw8852c_dack(wtwdev);
	wtw8852c_wx_dck(wtwdev, WTW89_PHY_0, fawse);
}

static void wtw8852c_wfk_channew(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_phy_idx phy_idx = WTW89_PHY_0;

	wtw8852c_mcc_get_ch_info(wtwdev, phy_idx);
	wtw8852c_wx_dck(wtwdev, phy_idx, fawse);
	wtw8852c_iqk(wtwdev, phy_idx);
	wtw8852c_tssi(wtwdev, phy_idx);
	wtw8852c_dpk(wtwdev, phy_idx);
	wtw89_fw_h2c_wf_ntfy_mcc(wtwdev);
}

static void wtw8852c_wfk_band_changed(stwuct wtw89_dev *wtwdev,
				      enum wtw89_phy_idx phy_idx)
{
	wtw8852c_tssi_scan(wtwdev, phy_idx);
}

static void wtw8852c_wfk_scan(stwuct wtw89_dev *wtwdev, boow stawt)
{
	wtw8852c_wifi_scan_notify(wtwdev, stawt, WTW89_PHY_0);
}

static void wtw8852c_wfk_twack(stwuct wtw89_dev *wtwdev)
{
	wtw8852c_dpk_twack(wtwdev);
	wtw8852c_wck_twack(wtwdev);
	wtw8852c_wx_dck_twack(wtwdev);
}

static u32 wtw8852c_bb_caw_txpww_wef(stwuct wtw89_dev *wtwdev,
				     enum wtw89_phy_idx phy_idx, s16 wef)
{
	s8 ofst_int = 0;
	u8 base_cw_0db = 0x27;
	u16 tssi_16dbm_cw = 0x12c;
	s16 pww_s10_3 = 0;
	s16 wf_pww_cw = 0;
	u16 bb_pww_cw = 0;
	u32 pww_cw = 0;
	u32 tssi_ofst_cw = 0;

	pww_s10_3 = (wef << 1) + (s16)(ofst_int) + (s16)(base_cw_0db << 3);
	bb_pww_cw = FIEWD_GET(GENMASK(2, 0), pww_s10_3);
	wf_pww_cw = FIEWD_GET(GENMASK(8, 3), pww_s10_3);
	wf_pww_cw = cwamp_t(s16, wf_pww_cw, 15, 63);
	pww_cw = (wf_pww_cw << 3) | bb_pww_cw;

	tssi_ofst_cw = (u32)((s16)tssi_16dbm_cw + (wef << 1) - (16 << 3));
	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] tssi_ofst_cw=%d wf_cw=0x%x bb_cw=0x%x\n",
		    tssi_ofst_cw, wf_pww_cw, bb_pww_cw);

	wetuwn (tssi_ofst_cw << 18) | (pww_cw << 9) | (wef & GENMASK(8, 0));
}

static
void wtw8852c_set_txpww_uw_tb_offset(stwuct wtw89_dev *wtwdev,
				     s8 pw_ofst, enum wtw89_mac_idx mac_idx)
{
	s8 pw_ofst_2tx;
	s8 vaw_1t;
	s8 vaw_2t;
	u32 weg;
	u8 i;

	if (pw_ofst < -32 || pw_ofst > 31) {
		wtw89_wawn(wtwdev, "[UWTB] Eww pww_offset=%d\n", pw_ofst);
		wetuwn;
	}
	vaw_1t = pw_ofst << 2;
	pw_ofst_2tx = max(pw_ofst - 3, -32);
	vaw_2t = pw_ofst_2tx << 2;

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[UWTB] vaw_1tx=0x%x\n", vaw_1t);
	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[UWTB] vaw_2tx=0x%x\n", vaw_2t);

	fow (i = 0; i < 4; i++) {
		/* 1TX */
		weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_1T, mac_idx);
		wtw89_wwite32_mask(wtwdev, weg,
				   B_AX_PWW_UW_TB_1T_V1_MASK << (8 * i),
				   vaw_1t);
		/* 2TX */
		weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_2T, mac_idx);
		wtw89_wwite32_mask(wtwdev, weg,
				   B_AX_PWW_UW_TB_2T_V1_MASK << (8 * i),
				   vaw_2t);
	}
}

static void wtw8852c_set_txpww_wef(stwuct wtw89_dev *wtwdev,
				   enum wtw89_phy_idx phy_idx)
{
	static const u32 addw[WF_PATH_NUM_8852C] = {0x5800, 0x7800};
	const u32 mask = 0x7FFFFFF;
	const u8 ofst_ofdm = 0x4;
	const u8 ofst_cck = 0x8;
	s16 wef_ofdm = 0;
	s16 wef_cck = 0;
	u32 vaw;
	u8 i;

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set txpww wefewence\n");

	wtw89_mac_txpww_wwite32_mask(wtwdev, phy_idx, W_AX_PWW_WATE_CTWW,
				     GENMASK(27, 10), 0x0);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set bb ofdm txpww wef\n");
	vaw = wtw8852c_bb_caw_txpww_wef(wtwdev, phy_idx, wef_ofdm);

	fow (i = 0; i < WF_PATH_NUM_8852C; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_ofdm, mask, vaw,
				      phy_idx);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set bb cck txpww wef\n");
	vaw = wtw8852c_bb_caw_txpww_wef(wtwdev, phy_idx, wef_cck);

	fow (i = 0; i < WF_PATH_NUM_8852C; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_cck, mask, vaw,
				      phy_idx);
}

static void wtw8852c_bb_set_tx_shape_dfiw(stwuct wtw89_dev *wtwdev,
					  const stwuct wtw89_chan *chan,
					  u8 tx_shape_idx,
					  enum wtw89_phy_idx phy_idx)
{
#define __DFIW_CFG_MASK 0xffffff
#define __DFIW_CFG_NW 8
#define __DECW_DFIW_VAW(_pwefix, _name, _vaw...) \
	static const u32 _pwefix ## _ ## _name[] = {_vaw}; \
	static_assewt(AWWAY_SIZE(_pwefix ## _ ## _name) == __DFIW_CFG_NW)
#define __DECW_DFIW_PAWAM(_name, _vaw...) __DECW_DFIW_VAW(pawam, _name, _vaw)
#define __DECW_DFIW_ADDW(_name, _vaw...) __DECW_DFIW_VAW(addw, _name, _vaw)

	__DECW_DFIW_PAWAM(fwat,
			  0x003D23FF, 0x0029B354, 0x000FC1C8, 0x00FDB053,
			  0x00F86F9A, 0x00FAEF92, 0x00FE5FCC, 0x00FFDFF5);
	__DECW_DFIW_PAWAM(shawp,
			  0x003D83FF, 0x002C636A, 0x0013F204, 0x00008090,
			  0x00F87FB0, 0x00F99F83, 0x00FDBFBA, 0x00003FF5);
	__DECW_DFIW_PAWAM(shawp_14,
			  0x003B13FF, 0x001C42DE, 0x00FDB0AD, 0x00F60F6E,
			  0x00FD8F92, 0x0002D011, 0x0001C02C, 0x00FFF00A);
	__DECW_DFIW_ADDW(fiwtew,
			 0x45BC, 0x45CC, 0x45D0, 0x45D4, 0x45D8, 0x45C0,
			 0x45C4, 0x45C8);
	u8 ch = chan->channew;
	const u32 *pawam;
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
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
			    "set tx shape dfiw: 0x%x: 0x%x\n", addw_fiwtew[i],
			    pawam[i]);
		wtw89_phy_wwite32_idx(wtwdev, addw_fiwtew[i], __DFIW_CFG_MASK,
				      pawam[i], phy_idx);
	}

#undef __DECW_DFIW_ADDW
#undef __DECW_DFIW_PAWAM
#undef __DECW_DFIW_VAW
#undef __DFIW_CFG_NW
#undef __DFIW_CFG_MASK
}

static void wtw8852c_set_tx_shape(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_chan *chan,
				  enum wtw89_phy_idx phy_idx)
{
	const stwuct wtw89_wfe_pawms *wfe_pawms = wtwdev->wfe_pawms;
	u8 band = chan->band_type;
	u8 wegd = wtw89_wegd_get(wtwdev, band);
	u8 tx_shape_cck = (*wfe_pawms->tx_shape.wmt)[band][WTW89_WS_CCK][wegd];
	u8 tx_shape_ofdm = (*wfe_pawms->tx_shape.wmt)[band][WTW89_WS_OFDM][wegd];

	if (band == WTW89_BAND_2G)
		wtw8852c_bb_set_tx_shape_dfiw(wtwdev, chan, tx_shape_cck, phy_idx);

	wtw89_phy_tssi_ctww_set_bandedge_cfg(wtwdev,
					     (enum wtw89_mac_idx)phy_idx,
					     tx_shape_ofdm);

	wtw89_phy_wwite32_set(wtwdev, W_P0_DAC_COMP_POST_DPD_EN,
			      B_P0_DAC_COMP_POST_DPD_EN);
	wtw89_phy_wwite32_set(wtwdev, W_P1_DAC_COMP_POST_DPD_EN,
			      B_P1_DAC_COMP_POST_DPD_EN);
}

static void wtw8852c_set_txpww(stwuct wtw89_dev *wtwdev,
			       const stwuct wtw89_chan *chan,
			       enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_set_txpww_bywate(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_offset(wtwdev, chan, phy_idx);
	wtw8852c_set_tx_shape(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit_wu(wtwdev, chan, phy_idx);
}

static void wtw8852c_set_txpww_ctww(stwuct wtw89_dev *wtwdev,
				    enum wtw89_phy_idx phy_idx)
{
	wtw8852c_set_txpww_wef(wtwdev, phy_idx);
}

static void
wtw8852c_init_tssi_ctww(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx)
{
	static const stwuct wtw89_weg2_def ctww_ini[] = {
		{0xD938, 0x00010100},
		{0xD93C, 0x0500D500},
		{0xD940, 0x00000500},
		{0xD944, 0x00000005},
		{0xD94C, 0x00220000},
		{0xD950, 0x00030000},
	};
	u32 addw;
	int i;

	fow (addw = W_AX_TSSI_CTWW_HEAD; addw <= W_AX_TSSI_CTWW_TAIW; addw += 4)
		wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, 0);

	fow (i = 0; i < AWWAY_SIZE(ctww_ini); i++)
		wtw89_mac_txpww_wwite32(wtwdev, phy_idx, ctww_ini[i].addw,
					ctww_ini[i].data);

	wtw89_phy_tssi_ctww_set_bandedge_cfg(wtwdev,
					     (enum wtw89_mac_idx)phy_idx,
					     WTW89_TSSI_BANDEDGE_FWAT);
}

static int
wtw8852c_init_txpww_unit(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx)
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

	wtw8852c_set_txpww_uw_tb_offset(wtwdev, 0, phy_idx == WTW89_PHY_1 ?
							      WTW89_MAC_1 :
							      WTW89_MAC_0);
	wtw8852c_init_tssi_ctww(wtwdev, phy_idx);

	wetuwn 0;
}

static void wtw8852c_bb_cfg_wx_path(stwuct wtw89_dev *wtwdev, u8 wx_path)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);
	u8 band = chan->band_type;
	u32 wst_mask0 = B_P0_TXPW_WSTB_MANON | B_P0_TXPW_WSTB_TSSI;
	u32 wst_mask1 = B_P1_TXPW_WSTB_MANON | B_P1_TXPW_WSTB_TSSI;

	if (wtwdev->dbcc_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD, B_ANT_WX_SEG0, 1);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_ANT_WX_SEG0, 2,
				      WTW89_PHY_1);

		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW, B_ANT_WX_1WCCA_SEG0,
				       1);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW, B_ANT_WX_1WCCA_SEG1,
				       1);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_ANT_WX_1WCCA_SEG0, 2,
				      WTW89_PHY_1);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_ANT_WX_1WCCA_SEG1, 2,
				      WTW89_PHY_1);

		wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT,
				       B_WXHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT,
				       B_WXVHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_USEW_MAX, 8);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 0);

		wtw89_phy_wwite32_idx(wtwdev, W_WXHT_MCS_WIMIT,
				      B_WXHT_MCS_WIMIT, 0, WTW89_PHY_1);
		wtw89_phy_wwite32_idx(wtwdev, W_WXVHT_MCS_WIMIT,
				      B_WXVHT_MCS_WIMIT, 0, WTW89_PHY_1);
		wtw89_phy_wwite32_idx(wtwdev, W_WXHE, B_WXHE_USEW_MAX, 1,
				      WTW89_PHY_1);
		wtw89_phy_wwite32_idx(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 0,
				      WTW89_PHY_1);
		wtw89_phy_wwite32_idx(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 0,
				      WTW89_PHY_1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 3);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, wst_mask1, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, wst_mask1, 3);
	} ewse {
		if (wx_path == WF_PATH_A) {
			wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD,
					       B_ANT_WX_SEG0, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG0, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG1, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT,
					       B_WXHT_MCS_WIMIT, 0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT,
					       B_WXVHT_MCS_WIMIT, 0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS,
					       0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS,
					       0);
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
					       wst_mask0, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
					       wst_mask0, 3);
		} ewse if (wx_path == WF_PATH_B) {
			wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD,
					       B_ANT_WX_SEG0, 2);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG0, 2);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG1, 2);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT,
					       B_WXHT_MCS_WIMIT, 0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT,
					       B_WXVHT_MCS_WIMIT, 0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS,
					       0);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS,
					       0);
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB,
					       wst_mask1, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB,
					       wst_mask1, 3);
		} ewse {
			wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD,
					       B_ANT_WX_SEG0, 3);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG0, 3);
			wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW,
					       B_ANT_WX_1WCCA_SEG1, 3);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT,
					       B_WXHT_MCS_WIMIT, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT,
					       B_WXVHT_MCS_WIMIT, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS,
					       1);
			wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS,
					       1);
			wtw8852c_ctww_btg_bt_wx(wtwdev, band == WTW89_BAND_2G,
						WTW89_PHY_0);
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
					       wst_mask0, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB,
					       wst_mask0, 3);
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB,
					       wst_mask1, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB,
					       wst_mask1, 3);
		}
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_USEW_MAX, 8);
	}
}

static void wtw8852c_ctww_tx_path_tmac(stwuct wtw89_dev *wtwdev, u8 tx_path,
				       enum wtw89_mac_idx mac_idx)
{
	stwuct wtw89_weg2_def path_com[] = {
		{W_AX_PATH_COM0, AX_PATH_COM0_DFVAW},
		{W_AX_PATH_COM1, AX_PATH_COM1_DFVAW},
		{W_AX_PATH_COM2, AX_PATH_COM2_DFVAW},
		{W_AX_PATH_COM3, AX_PATH_COM3_DFVAW},
		{W_AX_PATH_COM4, AX_PATH_COM4_DFVAW},
		{W_AX_PATH_COM5, AX_PATH_COM5_DFVAW},
		{W_AX_PATH_COM6, AX_PATH_COM6_DFVAW},
		{W_AX_PATH_COM7, AX_PATH_COM7_DFVAW},
		{W_AX_PATH_COM8, AX_PATH_COM8_DFVAW},
		{W_AX_PATH_COM9, AX_PATH_COM9_DFVAW},
		{W_AX_PATH_COM10, AX_PATH_COM10_DFVAW},
		{W_AX_PATH_COM11, AX_PATH_COM11_DFVAW},
	};
	u32 addw;
	u32 weg;
	u8 cw_size = AWWAY_SIZE(path_com);
	u8 i = 0;

	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0, WTW89_PHY_0);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0, WTW89_PHY_1);

	fow (addw = W_AX_MACID_ANT_TABWE;
	     addw <= W_AX_MACID_ANT_TABWE_WAST; addw += 4) {
		weg = wtw89_mac_weg_by_idx(wtwdev, addw, mac_idx);
		wtw89_wwite32(wtwdev, weg, 0);
	}

	if (tx_path == WF_A) {
		path_com[0].data = AX_PATH_COM0_PATHA;
		path_com[1].data = AX_PATH_COM1_PATHA;
		path_com[2].data = AX_PATH_COM2_PATHA;
		path_com[7].data = AX_PATH_COM7_PATHA;
		path_com[8].data = AX_PATH_COM8_PATHA;
	} ewse if (tx_path == WF_B) {
		path_com[0].data = AX_PATH_COM0_PATHB;
		path_com[1].data = AX_PATH_COM1_PATHB;
		path_com[2].data = AX_PATH_COM2_PATHB;
		path_com[7].data = AX_PATH_COM7_PATHB;
		path_com[8].data = AX_PATH_COM8_PATHB;
	} ewse if (tx_path == WF_AB) {
		path_com[0].data = AX_PATH_COM0_PATHAB;
		path_com[1].data = AX_PATH_COM1_PATHAB;
		path_com[2].data = AX_PATH_COM2_PATHAB;
		path_com[7].data = AX_PATH_COM7_PATHAB;
		path_com[8].data = AX_PATH_COM8_PATHAB;
	} ewse {
		wtw89_wawn(wtwdev, "[Invawid Tx Path]Tx Path: %d\n", tx_path);
		wetuwn;
	}

	fow (i = 0; i < cw_size; i++) {
		wtw89_debug(wtwdev, WTW89_DBG_TSSI, "0x%x = 0x%x\n",
			    path_com[i].addw, path_com[i].data);
		weg = wtw89_mac_weg_by_idx(wtwdev, path_com[i].addw, mac_idx);
		wtw89_wwite32(wtwdev, weg, path_com[i].data);
	}
}

static void wtw8852c_ctww_nbtg_bt_tx(stwuct wtw89_dev *wtwdev, boow en,
				     enum wtw89_phy_idx phy_idx)
{
	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_FWC_FIW_TYPE_V1,
				       B_PATH0_FWC_FIW_TYPE_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_FWC_FIW_TYPE_V1,
				       B_PATH1_FWC_FIW_TYPE_MSK_V1, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_WXBB_V1,
				       B_PATH0_WXBB_MSK_V1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_WXBB_V1,
				       B_PATH1_WXBB_MSK_V1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
				       B_PATH0_G_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_WNA6_OP1DB_V1,
				       B_PATH1_G_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA1_WNA6_OP1DB_V1,
				       B_PATH0_G_TIA1_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA0_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA1_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA1_WNA6_OP1DB_V1, 0x80);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_BACKOFF_V1,
				       B_PATH0_BT_BACKOFF_V1, 0x780D1E);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BT_BACKOFF_V1,
				       B_PATH1_BT_BACKOFF_V1, 0x780D1E);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_BACKOFF_IBADC_V1,
				       B_P0_BACKOFF_IBADC_V1, 0x34);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_BACKOFF_IBADC_V1,
				       B_P1_BACKOFF_IBADC_V1, 0x34);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_FWC_FIW_TYPE_V1,
				       B_PATH0_FWC_FIW_TYPE_MSK_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_FWC_FIW_TYPE_V1,
				       B_PATH1_FWC_FIW_TYPE_MSK_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_WXBB_V1,
				       B_PATH0_WXBB_MSK_V1, 0x60);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_WXBB_V1,
				       B_PATH1_WXBB_MSK_V1, 0x60);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_WNA6_OP1DB_V1,
				       B_PATH0_G_WNA6_OP1DB_V1, 0x1a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_WNA6_OP1DB_V1,
				       B_PATH1_G_WNA6_OP1DB_V1, 0x1a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH0_G_TIA0_WNA6_OP1DB_V1, 0x2a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_G_TIA1_WNA6_OP1DB_V1,
				       B_PATH0_G_TIA1_WNA6_OP1DB_V1, 0x2a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA0_WNA6_OP1DB_V1, 0x2a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA1_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA1_WNA6_OP1DB_V1, 0x2a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_BACKOFF_V1,
				       B_PATH0_BT_BACKOFF_V1, 0x79E99E);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BT_BACKOFF_V1,
				       B_PATH1_BT_BACKOFF_V1, 0x79E99E);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_BACKOFF_IBADC_V1,
				       B_P0_BACKOFF_IBADC_V1, 0x26);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_BACKOFF_IBADC_V1,
				       B_P1_BACKOFF_IBADC_V1, 0x26);
	}
}

static void wtw8852c_bb_cfg_txwx_path(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_haw *haw = &wtwdev->haw;

	wtw8852c_bb_cfg_wx_path(wtwdev, WF_PATH_AB);

	if (haw->wx_nss == 1) {
		wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT, B_WXHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT, B_WXVHT_MCS_WIMIT, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 0);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_WXHT_MCS_WIMIT, B_WXHT_MCS_WIMIT, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WXVHT_MCS_WIMIT, B_WXVHT_MCS_WIMIT, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHE_MAX_NSS, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_WXHE, B_WXHETB_MAX_NSS, 1);
	}
}

static u8 wtw8852c_get_thewmaw(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path wf_path)
{
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x0);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);

	fsweep(200);

	wetuwn wtw89_wead_wf(wtwdev, wf_path, WW_TM, WW_TM_VAW);
}

static void wtw8852c_btc_set_wfe(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_moduwe *moduwe = &btc->mdinfo;

	moduwe->wfe_type = wtwdev->efuse.wfe_type;
	moduwe->cv = wtwdev->haw.cv;
	moduwe->bt_sowo = 0;
	moduwe->switch_type = BTC_SWITCH_INTEWNAW;

	if (moduwe->wfe_type > 0)
		moduwe->ant.num = (moduwe->wfe_type % 2 ? 2 : 3);
	ewse
		moduwe->ant.num = 2;

	moduwe->ant.divewsity = 0;
	moduwe->ant.isowation = 10;

	if (moduwe->ant.num == 3) {
		moduwe->ant.type = BTC_ANT_DEDICATED;
		moduwe->bt_pos = BTC_BT_AWONE;
	} ewse {
		moduwe->ant.type = BTC_ANT_SHAWED;
		moduwe->bt_pos = BTC_BT_BTG;
	}
}

static void wtw8852c_ctww_btg_bt_wx(stwuct wtw89_dev *wtwdev, boow en,
				    enum wtw89_phy_idx phy_idx)
{
	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_SHAWE_V1,
				       B_PATH0_BT_SHAWE_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG_PATH_V1,
				       B_PATH0_BTG_PATH_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_WNA6_OP1DB_V1,
				       B_PATH1_G_WNA6_OP1DB_V1, 0x20);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA0_WNA6_OP1DB_V1, 0x30);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BT_SHAWE_V1,
				       B_PATH1_BT_SHAWE_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BTG_PATH_V1,
				       B_PATH1_BTG_PATH_V1, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD, B_BT_SHAWE, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW, B_ANT_WX_BT_SEG0, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, W_BT_DYN_DC_EST_EN,
				       B_BT_DYN_DC_EST_EN_MSK, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_GNT_BT_WGT_EN, B_GNT_BT_WGT_EN,
				       0x1);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BT_SHAWE_V1,
				       B_PATH0_BT_SHAWE_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG_PATH_V1,
				       B_PATH0_BTG_PATH_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_WNA6_OP1DB_V1,
				       B_PATH1_G_WNA6_OP1DB_V1, 0x1a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_G_TIA0_WNA6_OP1DB_V1,
				       B_PATH1_G_TIA0_WNA6_OP1DB_V1, 0x2a);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BT_SHAWE_V1,
				       B_PATH1_BT_SHAWE_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BTG_PATH_V1,
				       B_PATH1_BTG_PATH_V1, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P2, 0x4);
		wtw89_phy_wwite32_mask(wtwdev, W_CHBW_MOD, B_BT_SHAWE, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_FC0_BW, B_ANT_WX_BT_SEG0, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_BT_DYN_DC_EST_EN,
				       B_BT_DYN_DC_EST_EN_MSK, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_GNT_BT_WGT_EN, B_GNT_BT_WGT_EN,
				       0x0);
	}
}

static
void wtw8852c_set_twx_mask(stwuct wtw89_dev *wtwdev, u8 path, u8 gwoup, u32 vaw)
{
	wtw89_wwite_wf(wtwdev, path, WW_WUTWE, WFWEG_MASK, 0x20000);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWA, WFWEG_MASK, gwoup);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWD0, WFWEG_MASK, vaw);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWE, WFWEG_MASK, 0x0);
}

static void wtw8852c_btc_init_cfg(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_moduwe *moduwe = &btc->mdinfo;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_mac_ax_coex coex_pawams = {
		.pta_mode = WTW89_MAC_AX_COEX_WTK_MODE,
		.diwection = WTW89_MAC_AX_COEX_INNEW,
	};

	/* PTA init  */
	wtw89_mac_coex_init_v1(wtwdev, &coex_pawams);

	/* set WW Tx wesponse = Hi-Pwi */
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_TX_WESP, twue);
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_BEACON, twue);

	/* set wf gnt debug off */
	wtw89_wwite_wf(wtwdev, WF_PATH_A, WW_WWSEW, WFWEG_MASK, 0x0);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WWSEW, WFWEG_MASK, 0x0);

	/* set WW Tx thwu in TWX mask tabwe if GNT_WW = 0 && BT_S1 = ss gwoup */
	if (moduwe->ant.type == BTC_ANT_SHAWED) {
		wtw8852c_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_SS_GWOUP, 0x5ff);
		wtw8852c_set_twx_mask(wtwdev,
				      WF_PATH_B, BTC_BT_SS_GWOUP, 0x5ff);
		/* set path-A(S0) Tx/Wx no-mask if GNT_WW=0 && BT_S1=tx gwoup */
		wtw8852c_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_TX_GWOUP, 0x5ff);
	} ewse { /* set WW Tx stb if GNT_WW = 0 && BT_S1 = ss gwoup fow 3-ant */
		wtw8852c_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_SS_GWOUP, 0x5df);
		wtw8852c_set_twx_mask(wtwdev,
				      WF_PATH_B, BTC_BT_SS_GWOUP, 0x5df);
	}

	/* set PTA bweak tabwe */
	wtw89_wwite32(wtwdev, W_AX_BT_BWEAK_TABWE, BTC_BWEAK_PAWAM);

	 /* enabwe BT countew 0xda10[1:0] = 2b'11 */
	wtw89_wwite32_set(wtwdev,
			  W_AX_BT_CNT_CFG, B_AX_BT_CNT_EN |
			  B_AX_BT_CNT_WST_V1);
	btc->cx.ww.status.map.init_ok = twue;
}

static
void wtw8852c_btc_set_ww_pwi(stwuct wtw89_dev *wtwdev, u8 map, boow state)
{
	u32 bitmap = 0;
	u32 weg = 0;

	switch (map) {
	case BTC_PWI_MASK_TX_WESP:
		weg = W_BTC_COEX_WW_WEQ;
		bitmap = B_BTC_WSP_ACK_HI;
		bweak;
	case BTC_PWI_MASK_BEACON:
		weg = W_BTC_COEX_WW_WEQ;
		bitmap = B_BTC_TX_BCN_HI;
		bweak;
	defauwt:
		wetuwn;
	}

	if (state)
		wtw89_wwite32_set(wtwdev, weg, bitmap);
	ewse
		wtw89_wwite32_cww(wtwdev, weg, bitmap);
}

union wtw8852c_btc_ww_txpww_ctww {
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
wtw8852c_btc_set_ww_txpww_ctww(stwuct wtw89_dev *wtwdev, u32 txpww_vaw)
{
	union wtw8852c_btc_ww_txpww_ctww awg = { .txpww_vaw = txpww_vaw };
	s32 vaw;

#define __wwite_ctww(_weg, _msk, _vaw, _en, _cond)		\
do {								\
	u32 _wwt = FIEWD_PWEP(_msk, _vaw);			\
	BUIWD_BUG_ON((_msk & _en) != 0);			\
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
s8 wtw8852c_btc_get_bt_wssi(stwuct wtw89_dev *wtwdev, s8 vaw)
{
	/* +6 fow compensate offset */
	wetuwn cwamp_t(s8, vaw + 6, -100, 0) + 100;
}

static const stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8852c_wf_uw[] = {
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

static const stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8852c_wf_dw[] = {
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

static const u8 wtw89_btc_8852c_ww_wssi_thwes[BTC_WW_WSSI_THMAX] = {60, 50, 40, 30};
static const u8 wtw89_btc_8852c_bt_wssi_thwes[BTC_BT_WSSI_THMAX] = {40, 36, 31, 28};

static const stwuct wtw89_btc_fbtc_mweg wtw89_btc_8852c_mon_weg[] = {
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda00),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda04),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda24),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda30),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda34),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda38),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda44),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda48),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xda4c),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xd200),
	WTW89_DEF_FBTC_MWEG(WEG_MAC, 4, 0xd220),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x980),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x4aa4),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x4778),
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x476c),
};

static
void wtw8852c_btc_update_bt_cnt(stwuct wtw89_dev *wtwdev)
{
	/* Featuwe move to fiwmwawe */
}

static
void wtw8852c_btc_ww_s1_standby(stwuct wtw89_dev *wtwdev, boow state)
{
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x80000);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x1);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD1, WFWEG_MASK, 0x620);

	/* set WW standby = Wx fow GNT_BT_Tx = 1->0 settwe issue */
	if (state)
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0,
			       WFWEG_MASK, 0x179c);
	ewse
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0,
			       WFWEG_MASK, 0x208);

	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
}

static void wtw8852c_set_ww_wna2(stwuct wtw89_dev *wtwdev, u8 wevew)
{
	/* wevew=0 Defauwt:    TIA 1/0= (WNA2,TIAN6) = (7,1)/(5,1) = 21dB/12dB
	 * wevew=1 Fix WNA2=5: TIA 1/0= (WNA2,TIAN6) = (5,0)/(5,1) = 18dB/12dB
	 * To impwove BT ACI in co-wx
	 */

	switch (wevew) {
	case 0: /* defauwt */
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x1000);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x0);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x1);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x17);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x2);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x3);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x17);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
		bweak;
	case 1: /* Fix WNA2=5  */
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x1000);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x0);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x1);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x5);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x2);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x3);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x5);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
		bweak;
	}
}

static void wtw8852c_btc_set_ww_wx_gain(stwuct wtw89_dev *wtwdev, u32 wevew)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;

	switch (wevew) {
	case 0: /* owiginaw */
	defauwt:
		wtw8852c_ctww_nbtg_bt_tx(wtwdev, fawse, WTW89_PHY_0);
		btc->dm.ww_wna2 = 0;
		bweak;
	case 1: /* fow FDD fwee-wun */
		wtw8852c_ctww_nbtg_bt_tx(wtwdev, twue, WTW89_PHY_0);
		btc->dm.ww_wna2 = 0;
		bweak;
	case 2: /* fow BTG Co-Wx*/
		wtw8852c_ctww_nbtg_bt_tx(wtwdev, fawse, WTW89_PHY_0);
		btc->dm.ww_wna2 = 1;
		bweak;
	}

	wtw8852c_set_ww_wna2(wtwdev, btc->dm.ww_wna2);
}

static void wtw8852c_fiww_fweq_with_ppdu(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_wx_phy_ppdu *phy_ppdu,
					 stwuct ieee80211_wx_status *status)
{
	u8 chan_idx = phy_ppdu->chan_idx;
	enum nw80211_band band;
	u8 ch;

	if (chan_idx == 0)
		wetuwn;

	wtw89_decode_chan_idx(wtwdev, chan_idx, &ch, &band);
	status->fweq = ieee80211_channew_to_fwequency(ch, band);
	status->band = band;
}

static void wtw8852c_quewy_ppdu(stwuct wtw89_dev *wtwdev,
				stwuct wtw89_wx_phy_ppdu *phy_ppdu,
				stwuct ieee80211_wx_status *status)
{
	u8 path;
	u8 *wx_powew = phy_ppdu->wssi;

	status->signaw = WTW89_WSSI_WAW_TO_DBM(max(wx_powew[WF_PATH_A], wx_powew[WF_PATH_B]));
	fow (path = 0; path < wtwdev->chip->wf_path_num; path++) {
		status->chains |= BIT(path);
		status->chain_signaw[path] = WTW89_WSSI_WAW_TO_DBM(wx_powew[path]);
	}
	if (phy_ppdu->vawid)
		wtw8852c_fiww_fweq_with_ppdu(wtwdev, phy_ppdu, status);
}

static int wtw8852c_mac_enabwe_bb_wf(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_wwite8_set(wtwdev, W_AX_SYS_FUNC_EN,
			 B_AX_FEN_BBWSTB | B_AX_FEN_BB_GWB_WSTN);

	wtw89_wwite32_set(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);
	wtw89_wwite32_cww(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);
	wtw89_wwite32_set(wtwdev, W_AX_WWWF_CTWW, B_AX_AFC_AFEDIG);

	wtw89_wwite32_mask(wtwdev, W_AX_AFE_OFF_CTWW1, B_AX_S0_WDO_VSEW_F_MASK, 0x1);
	wtw89_wwite32_mask(wtwdev, W_AX_AFE_OFF_CTWW1, B_AX_S1_WDO_VSEW_F_MASK, 0x1);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW0, 0x7, FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x6c, FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, 0xc7, FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, 0xc7, FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW3, 0xd, FUWW_BIT_MASK);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wtw8852c_mac_disabwe_bb_wf(stwuct wtw89_dev *wtwdev)
{
	wtw89_wwite8_cww(wtwdev, W_AX_SYS_FUNC_EN,
			 B_AX_FEN_BBWSTB | B_AX_FEN_BB_GWB_WSTN);

	wetuwn 0;
}

static const stwuct wtw89_chanctx_wistenew wtw8852c_chanctx_wistenew = {
	.cawwbacks[WTW89_CHANCTX_CAWWBACK_WFK] = wtw8852c_wfk_chanctx_cb,
};

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt wtw_wowwan_stub_8852c = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = WTW89_MAX_PATTEWN_NUM,
	.pattewn_max_wen = WTW89_MAX_PATTEWN_SIZE,
	.pattewn_min_wen = 1,
};
#endif

static const stwuct wtw89_chip_ops wtw8852c_chip_ops = {
	.enabwe_bb_wf		= wtw8852c_mac_enabwe_bb_wf,
	.disabwe_bb_wf		= wtw8852c_mac_disabwe_bb_wf,
	.bb_pweinit		= NUWW,
	.bb_weset		= wtw8852c_bb_weset,
	.bb_sethw		= wtw8852c_bb_sethw,
	.wead_wf		= wtw89_phy_wead_wf_v1,
	.wwite_wf		= wtw89_phy_wwite_wf_v1,
	.set_channew		= wtw8852c_set_channew,
	.set_channew_hewp	= wtw8852c_set_channew_hewp,
	.wead_efuse		= wtw8852c_wead_efuse,
	.wead_phycap		= wtw8852c_wead_phycap,
	.fem_setup		= NUWW,
	.wfe_gpio		= NUWW,
	.wfk_init		= wtw8852c_wfk_init,
	.wfk_channew		= wtw8852c_wfk_channew,
	.wfk_band_changed	= wtw8852c_wfk_band_changed,
	.wfk_scan		= wtw8852c_wfk_scan,
	.wfk_twack		= wtw8852c_wfk_twack,
	.powew_twim		= wtw8852c_powew_twim,
	.set_txpww		= wtw8852c_set_txpww,
	.set_txpww_ctww		= wtw8852c_set_txpww_ctww,
	.init_txpww_unit	= wtw8852c_init_txpww_unit,
	.get_thewmaw		= wtw8852c_get_thewmaw,
	.ctww_btg_bt_wx		= wtw8852c_ctww_btg_bt_wx,
	.quewy_ppdu		= wtw8852c_quewy_ppdu,
	.ctww_nbtg_bt_tx	= wtw8852c_ctww_nbtg_bt_tx,
	.cfg_txwx_path		= wtw8852c_bb_cfg_txwx_path,
	.set_txpww_uw_tb_offset	= wtw8852c_set_txpww_uw_tb_offset,
	.pww_on_func		= wtw8852c_pww_on_func,
	.pww_off_func		= wtw8852c_pww_off_func,
	.quewy_wxdesc		= wtw89_cowe_quewy_wxdesc,
	.fiww_txdesc		= wtw89_cowe_fiww_txdesc_v1,
	.fiww_txdesc_fwcmd	= wtw89_cowe_fiww_txdesc_fwcmd_v1,
	.cfg_ctww_path		= wtw89_mac_cfg_ctww_path_v1,
	.mac_cfg_gnt		= wtw89_mac_cfg_gnt_v1,
	.stop_sch_tx		= wtw89_mac_stop_sch_tx_v1,
	.wesume_sch_tx		= wtw89_mac_wesume_sch_tx_v1,
	.h2c_dctw_sec_cam	= wtw89_fw_h2c_dctw_sec_cam_v1,

	.btc_set_wfe		= wtw8852c_btc_set_wfe,
	.btc_init_cfg		= wtw8852c_btc_init_cfg,
	.btc_set_ww_pwi		= wtw8852c_btc_set_ww_pwi,
	.btc_set_ww_txpww_ctww	= wtw8852c_btc_set_ww_txpww_ctww,
	.btc_get_bt_wssi	= wtw8852c_btc_get_bt_wssi,
	.btc_update_bt_cnt	= wtw8852c_btc_update_bt_cnt,
	.btc_ww_s1_standby	= wtw8852c_btc_ww_s1_standby,
	.btc_set_ww_wx_gain	= wtw8852c_btc_set_ww_wx_gain,
	.btc_set_powicy		= wtw89_btc_set_powicy_v1,
};

const stwuct wtw89_chip_info wtw8852c_chip_info = {
	.chip_id		= WTW8852C,
	.chip_gen		= WTW89_CHIP_AX,
	.ops			= &wtw8852c_chip_ops,
	.mac_def		= &wtw89_mac_gen_ax,
	.phy_def		= &wtw89_phy_gen_ax,
	.fw_basename		= WTW8852C_FW_BASENAME,
	.fw_fowmat_max		= WTW8852C_FW_FOWMAT_MAX,
	.twy_ce_fw		= fawse,
	.bbmcu_nw		= 0,
	.needed_fw_ewms		= 0,
	.fifo_size		= 458752,
	.smaww_fifo_size	= fawse,
	.dwe_scc_wsvd_size	= 0,
	.max_amsdu_wimit	= 8000,
	.dis_2g_40m_uw_ofdma	= fawse,
	.wsvd_pwe_ofst		= 0x6f800,
	.hfc_pawam_ini		= wtw8852c_hfc_pawam_ini_pcie,
	.dwe_mem		= wtw8852c_dwe_mem_pcie,
	.wde_qempty_acq_gwpnum	= 16,
	.wde_qempty_mgq_gwpsew	= 16,
	.wf_base_addw		= {0xe000, 0xf000},
	.pww_on_seq		= NUWW,
	.pww_off_seq		= NUWW,
	.bb_tabwe		= &wtw89_8852c_phy_bb_tabwe,
	.bb_gain_tabwe		= &wtw89_8852c_phy_bb_gain_tabwe,
	.wf_tabwe		= {&wtw89_8852c_phy_wadiob_tabwe,
				   &wtw89_8852c_phy_wadioa_tabwe,},
	.nctw_tabwe		= &wtw89_8852c_phy_nctw_tabwe,
	.nctw_post_tabwe	= NUWW,
	.dfwt_pawms		= &wtw89_8852c_dfwt_pawms,
	.wfe_pawms_conf		= NUWW,
	.chanctx_wistenew	= &wtw8852c_chanctx_wistenew,
	.txpww_factow_wf	= 2,
	.txpww_factow_mac	= 1,
	.dig_tabwe		= NUWW,
	.dig_wegs		= &wtw8852c_dig_wegs,
	.tssi_dbw_tabwe		= &wtw89_8852c_tssi_dbw_tabwe,
	.suppowt_chanctx_num	= 2,
	.suppowt_bands		= BIT(NW80211_BAND_2GHZ) |
				  BIT(NW80211_BAND_5GHZ) |
				  BIT(NW80211_BAND_6GHZ),
	.suppowt_bw160		= twue,
	.suppowt_unii4		= twue,
	.uw_tb_wavefowm_ctww	= fawse,
	.uw_tb_pww_diff		= twue,
	.hw_sec_hdw		= twue,
	.wf_path_num		= 2,
	.tx_nss			= 2,
	.wx_nss			= 2,
	.acam_num		= 128,
	.bcam_num		= 20,
	.scam_num		= 128,
	.bacam_num		= 8,
	.bacam_dynamic_num	= 8,
	.bacam_vew		= WTW89_BACAM_V0_EXT,
	.ppdu_max_usw		= 8,
	.sec_ctww_efuse_size	= 4,
	.physicaw_efuse_size	= 1216,
	.wogicaw_efuse_size	= 2048,
	.wimit_efuse_size	= 1280,
	.dav_phy_efuse_size	= 96,
	.dav_wog_efuse_size	= 16,
	.efuse_bwocks		= NUWW,
	.phycap_addw		= 0x590,
	.phycap_size		= 0x60,
	.pawa_vew		= 0x1,
	.wwcx_desiwed		= 0x06000000,
	.btcx_desiwed		= 0x7,
	.scbd			= 0x1,
	.maiwbox		= 0x1,

	.afh_guawd_ch		= 6,
	.ww_wssi_thwes		= wtw89_btc_8852c_ww_wssi_thwes,
	.bt_wssi_thwes		= wtw89_btc_8852c_bt_wssi_thwes,
	.wssi_tow		= 2,
	.mon_weg_num		= AWWAY_SIZE(wtw89_btc_8852c_mon_weg),
	.mon_weg		= wtw89_btc_8852c_mon_weg,
	.wf_pawa_uwink_num	= AWWAY_SIZE(wtw89_btc_8852c_wf_uw),
	.wf_pawa_uwink		= wtw89_btc_8852c_wf_uw,
	.wf_pawa_dwink_num	= AWWAY_SIZE(wtw89_btc_8852c_wf_dw),
	.wf_pawa_dwink		= wtw89_btc_8852c_wf_dw,
	.ps_mode_suppowted	= BIT(WTW89_PS_MODE_WFOFF) |
				  BIT(WTW89_PS_MODE_CWK_GATED) |
				  BIT(WTW89_PS_MODE_PWW_GATED),
	.wow_powew_hci_modes	= BIT(WTW89_PS_MODE_CWK_GATED) |
				  BIT(WTW89_PS_MODE_PWW_GATED),
	.h2c_cctw_func_id	= H2C_FUNC_MAC_CCTWINFO_UD_V1,
	.hci_func_en_addw	= W_AX_HCI_FUNC_EN_V1,
	.h2c_desc_size		= sizeof(stwuct wtw89_wxdesc_showt),
	.txwd_body_size		= sizeof(stwuct wtw89_txwd_body_v1),
	.txwd_info_size		= sizeof(stwuct wtw89_txwd_info),
	.h2c_ctww_weg		= W_AX_H2CWEG_CTWW_V1,
	.h2c_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_H2C_DEQ_CNT_MASK >> 8},
	.h2c_wegs		= wtw8852c_h2c_wegs,
	.c2h_ctww_weg		= W_AX_C2HWEG_CTWW_V1,
	.c2h_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_C2H_ENQ_CNT_MASK >> 8},
	.c2h_wegs		= wtw8852c_c2h_wegs,
	.page_wegs		= &wtw8852c_page_wegs,
	.cfo_swc_fd		= fawse,
	.cfo_hw_comp            = fawse,
	.dcfo_comp		= &wtw8852c_dcfo_comp,
	.dcfo_comp_sft		= 12,
	.imw_info		= &wtw8852c_imw_info,
	.imw_dmac_tabwe		= NUWW,
	.imw_cmac_tabwe		= NUWW,
	.wwsw_cfgs		= &wtw8852c_wwsw_cfgs,
	.bss_cww_vwd		= {W_BSS_CWW_MAP, B_BSS_CWW_MAP_VWD0},
	.bss_cww_map_weg	= W_BSS_CWW_MAP,
	.dma_ch_mask		= 0,
	.edcca_wegs		= &wtw8852c_edcca_wegs,
#ifdef CONFIG_PM
	.wowwan_stub		= &wtw_wowwan_stub_8852c,
#endif
	.xtaw_info		= NUWW,
};
EXPOWT_SYMBOW(wtw8852c_chip_info);

MODUWE_FIWMWAWE(WTW8852C_MODUWE_FIWMWAWE);
MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ax wiwewess 8852C dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
