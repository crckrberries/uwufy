// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#incwude "debug.h"
#incwude "efuse.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "wtw8922a.h"

#define WTW8922A_FW_FOWMAT_MAX 0
#define WTW8922A_FW_BASENAME "wtw89/wtw8922a_fw"
#define WTW8922A_MODUWE_FIWMWAWE \
	WTW8922A_FW_BASENAME ".bin"

static const stwuct wtw89_hfc_ch_cfg wtw8922a_hfc_chcfg_pcie[] = {
	{2, 1641, gwp_0}, /* ACH 0 */
	{2, 1641, gwp_0}, /* ACH 1 */
	{2, 1641, gwp_0}, /* ACH 2 */
	{2, 1641, gwp_0}, /* ACH 3 */
	{2, 1641, gwp_1}, /* ACH 4 */
	{2, 1641, gwp_1}, /* ACH 5 */
	{2, 1641, gwp_1}, /* ACH 6 */
	{2, 1641, gwp_1}, /* ACH 7 */
	{2, 1641, gwp_0}, /* B0MGQ */
	{2, 1641, gwp_0}, /* B0HIQ */
	{2, 1641, gwp_1}, /* B1MGQ */
	{2, 1641, gwp_1}, /* B1HIQ */
	{0, 0, 0}, /* FWCMDQ */
	{0, 0, 0}, /* BMC */
	{0, 0, 0}, /* H2D */
};

static const stwuct wtw89_hfc_pub_cfg wtw8922a_hfc_pubcfg_pcie = {
	1651, /* Gwoup 0 */
	1651, /* Gwoup 1 */
	3302, /* Pubwic Max */
	0, /* WP thweshowd */
};

static const stwuct wtw89_hfc_pawam_ini wtw8922a_hfc_pawam_ini_pcie[] = {
	[WTW89_QTA_SCC] = {wtw8922a_hfc_chcfg_pcie, &wtw8922a_hfc_pubcfg_pcie,
			   &wtw89_mac_size.hfc_pwec_cfg_c0, WTW89_HCIFC_POH},
	[WTW89_QTA_DWFW] = {NUWW, NUWW, &wtw89_mac_size.hfc_pwec_cfg_c2,
			    WTW89_HCIFC_POH},
	[WTW89_QTA_INVAWID] = {NUWW},
};

static const stwuct wtw89_dwe_mem wtw8922a_dwe_mem_pcie[] = {
	[WTW89_QTA_SCC] = {WTW89_QTA_SCC, &wtw89_mac_size.wde_size0_v1,
			   &wtw89_mac_size.pwe_size0_v1, &wtw89_mac_size.wde_qt0_v1,
			   &wtw89_mac_size.wde_qt0_v1, &wtw89_mac_size.pwe_qt0,
			   &wtw89_mac_size.pwe_qt1, &wtw89_mac_size.pwe_wsvd_qt0,
			   &wtw89_mac_size.wsvd0_size0, &wtw89_mac_size.wsvd1_size0},
	[WTW89_QTA_DWFW] = {WTW89_QTA_DWFW, &wtw89_mac_size.wde_size4_v1,
			    &wtw89_mac_size.pwe_size3_v1, &wtw89_mac_size.wde_qt4,
			    &wtw89_mac_size.wde_qt4, &wtw89_mac_size.pwe_qt9,
			    &wtw89_mac_size.pwe_qt9, &wtw89_mac_size.pwe_wsvd_qt1,
			    &wtw89_mac_size.wsvd0_size0, &wtw89_mac_size.wsvd1_size0},
	[WTW89_QTA_INVAWID] = {WTW89_QTA_INVAWID, NUWW, NUWW, NUWW, NUWW, NUWW,
			       NUWW},
};

static const stwuct wtw89_weg_imw wtw8922a_imw_dmac_wegs[] = {
	{W_BE_DISP_HOST_IMW, B_BE_DISP_HOST_IMW_CWW, B_BE_DISP_HOST_IMW_SET},
	{W_BE_DISP_CPU_IMW, B_BE_DISP_CPU_IMW_CWW, B_BE_DISP_CPU_IMW_SET},
	{W_BE_DISP_OTHEW_IMW, B_BE_DISP_OTHEW_IMW_CWW, B_BE_DISP_OTHEW_IMW_SET},
	{W_BE_PKTIN_EWW_IMW, B_BE_PKTIN_EWW_IMW_CWW, B_BE_PKTIN_EWW_IMW_SET},
	{W_BE_INTEWWUPT_MASK_WEG, B_BE_INTEWWUPT_MASK_WEG_CWW, B_BE_INTEWWUPT_MASK_WEG_SET},
	{W_BE_MWO_EWW_IDCT_IMW, B_BE_MWO_EWW_IDCT_IMW_CWW, B_BE_MWO_EWW_IDCT_IMW_SET},
	{W_BE_MPDU_TX_EWW_IMW, B_BE_MPDU_TX_EWW_IMW_CWW, B_BE_MPDU_TX_EWW_IMW_SET},
	{W_BE_MPDU_WX_EWW_IMW, B_BE_MPDU_WX_EWW_IMW_CWW, B_BE_MPDU_WX_EWW_IMW_SET},
	{W_BE_SEC_EWWOW_IMW, B_BE_SEC_EWWOW_IMW_CWW, B_BE_SEC_EWWOW_IMW_SET},
	{W_BE_CPUIO_EWW_IMW, B_BE_CPUIO_EWW_IMW_CWW, B_BE_CPUIO_EWW_IMW_SET},
	{W_BE_WDE_EWW_IMW, B_BE_WDE_EWW_IMW_CWW, B_BE_WDE_EWW_IMW_SET},
	{W_BE_WDE_EWW1_IMW, B_BE_WDE_EWW1_IMW_CWW, B_BE_WDE_EWW1_IMW_SET},
	{W_BE_PWE_EWW_IMW, B_BE_PWE_EWW_IMW_CWW, B_BE_PWE_EWW_IMW_SET},
	{W_BE_PWE_EWWFWAG1_IMW, B_BE_PWE_EWWFWAG1_IMW_CWW, B_BE_PWE_EWWFWAG1_IMW_SET},
	{W_BE_WDWWS_EWW_IMW, B_BE_WDWWS_EWW_IMW_CWW, B_BE_WDWWS_EWW_IMW_SET},
	{W_BE_TXPKTCTW_B0_EWWFWAG_IMW, B_BE_TXPKTCTW_B0_EWWFWAG_IMW_CWW,
	 B_BE_TXPKTCTW_B0_EWWFWAG_IMW_SET},
	{W_BE_TXPKTCTW_B1_EWWFWAG_IMW, B_BE_TXPKTCTW_B1_EWWFWAG_IMW_CWW,
	 B_BE_TXPKTCTW_B1_EWWFWAG_IMW_SET},
	{W_BE_BBWPT_COM_EWW_IMW, B_BE_BBWPT_COM_EWW_IMW_CWW, B_BE_BBWPT_COM_EWW_IMW_SET},
	{W_BE_BBWPT_CHINFO_EWW_IMW, B_BE_BBWPT_CHINFO_EWW_IMW_CWW,
	 B_BE_BBWPT_CHINFO_EWW_IMW_SET},
	{W_BE_BBWPT_DFS_EWW_IMW, B_BE_BBWPT_DFS_EWW_IMW_CWW, B_BE_BBWPT_DFS_EWW_IMW_SET},
	{W_BE_WA_EWWFWAG_IMW, B_BE_WA_EWWFWAG_IMW_CWW, B_BE_WA_EWWFWAG_IMW_SET},
	{W_BE_CH_INFO_DBGFWAG_IMW, B_BE_CH_INFO_DBGFWAG_IMW_CWW, B_BE_CH_INFO_DBGFWAG_IMW_SET},
	{W_BE_PWWWS_EWW_IMW, B_BE_PWWWS_EWW_IMW_CWW, B_BE_PWWWS_EWW_IMW_SET},
	{W_BE_HAXI_IDCT_MSK, B_BE_HAXI_IDCT_MSK_CWW, B_BE_HAXI_IDCT_MSK_SET},
};

static const stwuct wtw89_imw_tabwe wtw8922a_imw_dmac_tabwe = {
	.wegs = wtw8922a_imw_dmac_wegs,
	.n_wegs = AWWAY_SIZE(wtw8922a_imw_dmac_wegs),
};

static const stwuct wtw89_weg_imw wtw8922a_imw_cmac_wegs[] = {
	{W_BE_WESP_IMW, B_BE_WESP_IMW_CWW, B_BE_WESP_IMW_SET},
	{W_BE_WX_EWWOW_FWAG_IMW, B_BE_WX_EWWOW_FWAG_IMW_CWW, B_BE_WX_EWWOW_FWAG_IMW_SET},
	{W_BE_TX_EWWOW_FWAG_IMW, B_BE_TX_EWWOW_FWAG_IMW_CWW, B_BE_TX_EWWOW_FWAG_IMW_SET},
	{W_BE_WX_EWWOW_FWAG_IMW_1, B_BE_TX_EWWOW_FWAG_IMW_1_CWW, B_BE_TX_EWWOW_FWAG_IMW_1_SET},
	{W_BE_PTCW_IMW1, B_BE_PTCW_IMW1_CWW, B_BE_PTCW_IMW1_SET},
	{W_BE_PTCW_IMW0, B_BE_PTCW_IMW0_CWW, B_BE_PTCW_IMW0_SET},
	{W_BE_PTCW_IMW_2, B_BE_PTCW_IMW_2_CWW, B_BE_PTCW_IMW_2_SET},
	{W_BE_SCHEDUWE_EWW_IMW, B_BE_SCHEDUWE_EWW_IMW_CWW, B_BE_SCHEDUWE_EWW_IMW_SET},
	{W_BE_C0_TXPWW_IMW, B_BE_C0_TXPWW_IMW_CWW, B_BE_C0_TXPWW_IMW_SET},
	{W_BE_TWXPTCW_EWWOW_INDICA_MASK, B_BE_TWXPTCW_EWWOW_INDICA_MASK_CWW,
	 B_BE_TWXPTCW_EWWOW_INDICA_MASK_SET},
	{W_BE_WX_EWW_IMW, B_BE_WX_EWW_IMW_CWW, B_BE_WX_EWW_IMW_SET},
	{W_BE_PHYINFO_EWW_IMW_V1, B_BE_PHYINFO_EWW_IMW_V1_CWW, B_BE_PHYINFO_EWW_IMW_V1_SET},
};

static const stwuct wtw89_imw_tabwe wtw8922a_imw_cmac_tabwe = {
	.wegs = wtw8922a_imw_cmac_wegs,
	.n_wegs = AWWAY_SIZE(wtw8922a_imw_cmac_wegs),
};

static const stwuct wtw89_efuse_bwock_cfg wtw8922a_efuse_bwocks[] = {
	[WTW89_EFUSE_BWOCK_SYS]			= {.offset = 0x00000, .size = 0x310},
	[WTW89_EFUSE_BWOCK_WF]			= {.offset = 0x10000, .size = 0x240},
	[WTW89_EFUSE_BWOCK_HCI_DIG_PCIE_SDIO]	= {.offset = 0x20000, .size = 0x4800},
	[WTW89_EFUSE_BWOCK_HCI_DIG_USB]		= {.offset = 0x30000, .size = 0x890},
	[WTW89_EFUSE_BWOCK_HCI_PHY_PCIE]	= {.offset = 0x40000, .size = 0x200},
	[WTW89_EFUSE_BWOCK_HCI_PHY_USB3]	= {.offset = 0x50000, .size = 0x80},
	[WTW89_EFUSE_BWOCK_HCI_PHY_USB2]	= {.offset = 0x60000, .size = 0x0},
	[WTW89_EFUSE_BWOCK_ADIE]		= {.offset = 0x70000, .size = 0x10},
};

static int wtw8922a_pww_on_func(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u32 vaw32;
	int wet;

	wtw89_wwite32_cww(wtwdev, W_BE_SYS_PW_CTWW, B_BE_AFSM_WWSUS_EN |
						    B_BE_AFSM_PCIE_SUS_EN);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_DIS_WWBT_PDNSUSEN_SOPC);
	wtw89_wwite32_set(wtwdev, W_BE_WWWPS_CTWW, B_BE_DIS_WWBT_WPSEN_WOPC);
	wtw89_wwite32_cww(wtwdev, W_BE_SYS_PW_CTWW, B_BE_APDM_HPDN);
	wtw89_wwite32_cww(wtwdev, W_BE_SYS_PW_CTWW, B_BE_APFM_SWWPS);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, vaw32 & B_BE_WDY_SYSPWW,
				1000, 3000000, fawse, wtwdev, W_BE_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_EN_WWON);
	wtw89_wwite32_set(wtwdev, W_BE_WWWESUME_CTWW, B_BE_WPSWOP_CMAC0 |
						      B_BE_WPSWOP_CMAC1);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_APFN_ONMAC);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_APFN_ONMAC),
				1000, 3000000, fawse, wtwdev, W_BE_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_BE_AFE_ON_CTWW1, B_BE_WEG_CK_MON_CK960M_EN);
	wtw89_wwite8_set(wtwdev, W_BE_ANAPAW_POW_MAC, B_BE_POW_PC_WDO_POWT0 |
						      B_BE_POW_PC_WDO_POWT1);
	wtw89_wwite32_cww(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_W_SYM_ISO_ADDA_P02PP |
						       B_BE_W_SYM_ISO_ADDA_P12PP);
	wtw89_wwite8_set(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_PWATFOWM_EN);
	wtw89_wwite32_set(wtwdev, W_BE_HCI_OPT_CTWW, B_BE_HAXIDMA_IO_EN);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, vaw32 & B_BE_HAXIDMA_IO_ST,
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_HAXIDMA_BACKUP_WESTOWE_ST),
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_HCI_OPT_CTWW, B_BE_HCI_WWAN_IO_EN);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, vaw32 & B_BE_HCI_WWAN_IO_ST,
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_BE_SYS_SDIO_CTWW, B_BE_PCIE_FOWCE_IBX_EN);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_PWW, 0x02, 0x02);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_PWW, 0x01, 0x01);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_SYS_ADIE_PAD_PWW_CTWW, B_BE_SYM_PADPDN_WW_WFC1_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x40, 0x40);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_SYS_ADIE_PAD_PWW_CTWW, B_BE_SYM_PADPDN_WW_WFC0_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x20, 0x20);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x04, 0x04);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x08, 0x08);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x10);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, 0xEB, 0xFF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, 0xEB, 0xFF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x01, 0x01);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x02, 0x02);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x80);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XWEF_WF1, 0, 0x40);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_XWEF_WF2, 0, 0x40);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_PWW_1, 0x40, 0x60);
	if (wet)
		wetuwn wet;

	if (haw->cv != CHIP_CAV) {
		wtw89_wwite32_set(wtwdev, W_BE_PMC_DBG_CTWW2, B_BE_SYSON_DIS_PMCW_BE_WWMSK);
		wtw89_wwite32_set(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_ISO_EB2COWE);
		wtw89_wwite32_cww(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_B);

		mdeway(1);

		wtw89_wwite32_cww(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_S);
		wtw89_wwite32_cww(wtwdev, W_BE_PMC_DBG_CTWW2, B_BE_SYSON_DIS_PMCW_BE_WWMSK);
	}

	wtw89_wwite32_set(wtwdev, W_BE_DMAC_FUNC_EN,
			  B_BE_MAC_FUNC_EN | B_BE_DMAC_FUNC_EN | B_BE_MPDU_PWOC_EN |
			  B_BE_WD_WWS_EN | B_BE_DWE_WDE_EN | B_BE_TXPKT_CTWW_EN |
			  B_BE_STA_SCH_EN | B_BE_DWE_PWE_EN | B_BE_PKT_BUF_EN |
			  B_BE_DMAC_TBW_EN | B_BE_PKT_IN_EN | B_BE_DWE_CPUIO_EN |
			  B_BE_DISPATCHEW_EN | B_BE_BBWPT_EN | B_BE_MAC_SEC_EN |
			  B_BE_H_AXIDMA_EN | B_BE_DMAC_MWO_EN | B_BE_PWWWS_EN |
			  B_BE_P_AXIDMA_EN | B_BE_DWE_DATACPUIO_EN | B_BE_WTW_CTW_EN);

	set_bit(WTW89_FWAG_DMAC_FUNC, wtwdev->fwags);

	wtw89_wwite32_set(wtwdev, W_BE_CMAC_SHAWE_FUNC_EN,
			  B_BE_CMAC_SHAWE_EN | B_BE_WESPBA_EN | B_BE_ADDWSWCH_EN |
			  B_BE_BTCOEX_EN);
	wtw89_wwite32_set(wtwdev, W_BE_CMAC_FUNC_EN,
			  B_BE_CMAC_EN | B_BE_CMAC_TXEN |  B_BE_CMAC_WXEN |
			  B_BE_SIGB_EN | B_BE_PHYINTF_EN | B_BE_CMAC_DMA_EN |
			  B_BE_PTCWTOP_EN | B_BE_SCHEDUWEW_EN | B_BE_TMAC_EN |
			  B_BE_WMAC_EN | B_BE_TXTIME_EN | B_BE_WESP_PKTCTW_EN);

	set_bit(WTW89_FWAG_CMAC0_FUNC, wtwdev->fwags);

	wtw89_wwite32_set(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_FEN_BB_IP_WSTN |
						       B_BE_FEN_BBPWAT_WSTB);

	wetuwn 0;
}

static int wtw8922a_pww_off_func(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	int wet;

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x10, 0x10);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x08);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x04);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S0, 0xC6, 0xFF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WW_WFC_S1, 0xC6, 0xFF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0x80, 0x80);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x02);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x01);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_PWW, 0x02, 0xFF);
	if (wet)
		wetuwn wet;
	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_PWW, 0x00, 0xFF);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_W_SYM_ISO_ADDA_P02PP |
						       B_BE_W_SYM_ISO_ADDA_P12PP);
	wtw89_wwite8_cww(wtwdev, W_BE_ANAPAW_POW_MAC, B_BE_POW_PC_WDO_POWT0 |
						      B_BE_POW_PC_WDO_POWT1);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_EN_WWON);
	wtw89_wwite8_cww(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_FEN_BB_IP_WSTN |
						      B_BE_FEN_BBPWAT_WSTB);
	wtw89_wwite32_cww(wtwdev, W_BE_SYS_ADIE_PAD_PWW_CTWW, B_BE_SYM_PADPDN_WW_WFC0_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x20);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_BE_SYS_ADIE_PAD_PWW_CTWW, B_BE_SYM_PADPDN_WW_WFC1_1P3);

	wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_ANAPAW_WW, 0, 0x40);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_BE_HCI_OPT_CTWW, B_BE_HAXIDMA_IO_EN);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_HAXIDMA_IO_ST),
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_HAXIDMA_BACKUP_WESTOWE_ST),
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_cww(wtwdev, W_BE_HCI_OPT_CTWW, B_BE_HCI_WWAN_IO_EN);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_HCI_WWAN_IO_ST),
				1000, 3000000, fawse, wtwdev, W_BE_HCI_OPT_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_APFM_OFFMAC);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_APFM_OFFMAC),
				1000, 3000000, fawse, wtwdev, W_BE_SYS_PW_CTWW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32(wtwdev, W_BE_WWWPS_CTWW, 0x0000A1B2);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_XTAW_OFF_A_DIE);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_APFM_SWWPS);
	wtw89_wwite32(wtwdev, W_BE_UDM1, 0);

	wetuwn 0;
}

static void wtw8922a_efuse_pawsing_tssi(stwuct wtw89_dev *wtwdev,
					stwuct wtw8922a_efuse *map)
{
	stwuct wtw8922a_tssi_offset *ofst[] = {&map->path_a_tssi, &map->path_b_tssi};
	u8 *bw40_1s_tssi_6g_ofst[] = {map->bw40_1s_tssi_6g_a, map->bw40_1s_tssi_6g_b};
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	u8 i, j;

	tssi->thewmaw[WF_PATH_A] = map->path_a_thewm;
	tssi->thewmaw[WF_PATH_B] = map->path_b_thewm;

	fow (i = 0; i < WF_PATH_NUM_8922A; i++) {
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

static void wtw8922a_efuse_pawsing_gain_offset(stwuct wtw89_dev *wtwdev,
					       stwuct wtw8922a_efuse *map)
{
	stwuct wtw89_phy_efuse_gain *gain = &wtwdev->efuse_gain;
	boow aww_0xff = twue, aww_0x00 = twue;
	int i, j;
	u8 t;

	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_CCK] = map->wx_gain_a._2g_cck;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_2G_CCK] = map->wx_gain_b._2g_cck;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_2G_OFDM] = map->wx_gain_a._2g_ofdm;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_2G_OFDM] = map->wx_gain_b._2g_ofdm;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_WOW] = map->wx_gain_a._5g_wow;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_WOW] = map->wx_gain_b._5g_wow;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_MID] = map->wx_gain_a._5g_mid;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_MID] = map->wx_gain_b._5g_mid;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_5G_HIGH] = map->wx_gain_a._5g_high;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_5G_HIGH] = map->wx_gain_b._5g_high;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_W0] = map->wx_gain_6g_a._6g_w0;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_W0] = map->wx_gain_6g_b._6g_w0;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_W1] = map->wx_gain_6g_a._6g_w1;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_W1] = map->wx_gain_6g_b._6g_w1;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_M0] = map->wx_gain_6g_a._6g_m0;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_M0] = map->wx_gain_6g_b._6g_m0;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_M1] = map->wx_gain_6g_a._6g_m1;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_M1] = map->wx_gain_6g_b._6g_m1;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_H0] = map->wx_gain_6g_a._6g_h0;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_H0] = map->wx_gain_6g_b._6g_h0;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_H1] = map->wx_gain_6g_a._6g_h1;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_H1] = map->wx_gain_6g_b._6g_h1;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_UH0] = map->wx_gain_6g_a._6g_uh0;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_UH0] = map->wx_gain_6g_b._6g_uh0;
	gain->offset[WF_PATH_A][WTW89_GAIN_OFFSET_6G_UH1] = map->wx_gain_6g_a._6g_uh1;
	gain->offset[WF_PATH_B][WTW89_GAIN_OFFSET_6G_UH1] = map->wx_gain_6g_b._6g_uh1;

	fow (i = WF_PATH_A; i <= WF_PATH_B; i++)
		fow (j = 0; j < WTW89_GAIN_OFFSET_NW; j++) {
			t = gain->offset[i][j];
			if (t != 0xff)
				aww_0xff = fawse;
			if (t != 0x0)
				aww_0x00 = fawse;

			/* twansfowm: sign-bit + U(7,2) to S(8,2) */
			if (t & 0x80)
				gain->offset[i][j] = (t ^ 0x7f) + 1;
		}

	gain->offset_vawid = !aww_0xff && !aww_0x00;
}

static void wtw8922a_wead_efuse_mac_addw(stwuct wtw89_dev *wtwdev, u32 addw)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	u16 vaw;
	int i;

	fow (i = 0; i < ETH_AWEN; i += 2, addw += 2) {
		vaw = wtw89_wead16(wtwdev, addw);
		efuse->addw[i] = vaw & 0xff;
		efuse->addw[i + 1] = vaw >> 8;
	}
}

static int wtw8922a_wead_efuse_pci_sdio(stwuct wtw89_dev *wtwdev, u8 *wog_map)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;

	if (wtwdev->hci.type == WTW89_HCI_TYPE_PCIE)
		wtw8922a_wead_efuse_mac_addw(wtwdev, 0x3104);
	ewse
		ethew_addw_copy(efuse->addw, wog_map + 0x001A);

	wetuwn 0;
}

static int wtw8922a_wead_efuse_usb(stwuct wtw89_dev *wtwdev, u8 *wog_map)
{
	wtw8922a_wead_efuse_mac_addw(wtwdev, 0x4078);

	wetuwn 0;
}

static int wtw8922a_wead_efuse_wf(stwuct wtw89_dev *wtwdev, u8 *wog_map)
{
	stwuct wtw8922a_efuse *map = (stwuct wtw8922a_efuse *)wog_map;
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;

	efuse->wfe_type = map->wfe_type;
	efuse->xtaw_cap = map->xtaw_k;
	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	wtw8922a_efuse_pawsing_tssi(wtwdev, map);
	wtw8922a_efuse_pawsing_gain_offset(wtwdev, map);

	wtw89_info(wtwdev, "chip wfe_type is %d\n", efuse->wfe_type);

	wetuwn 0;
}

static int wtw8922a_wead_efuse(stwuct wtw89_dev *wtwdev, u8 *wog_map,
			       enum wtw89_efuse_bwock bwock)
{
	switch (bwock) {
	case WTW89_EFUSE_BWOCK_HCI_DIG_PCIE_SDIO:
		wetuwn wtw8922a_wead_efuse_pci_sdio(wtwdev, wog_map);
	case WTW89_EFUSE_BWOCK_HCI_DIG_USB:
		wetuwn wtw8922a_wead_efuse_usb(wtwdev, wog_map);
	case WTW89_EFUSE_BWOCK_WF:
		wetuwn wtw8922a_wead_efuse_wf(wtwdev, wog_map);
	defauwt:
		wetuwn 0;
	}
}

#define THM_TWIM_POSITIVE_MASK BIT(6)
#define THM_TWIM_MAGNITUDE_MASK GENMASK(5, 0)

static void wtw8922a_phycap_pawsing_thewmaw_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	static const u32 thm_twim_addw[WF_PATH_NUM_8922A] = {0x1706, 0x1733};
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u32 addw = wtwdev->chip->phycap_addw;
	boow pg = twue;
	u8 pg_th;
	s8 vaw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8922A; i++) {
		pg_th = phycap_map[thm_twim_addw[i] - addw];
		if (pg_th == 0xff) {
			info->thewmaw_twim[i] = 0;
			pg = fawse;
			bweak;
		}

		vaw = u8_get_bits(pg_th, THM_TWIM_MAGNITUDE_MASK);

		if (!(pg_th & THM_TWIM_POSITIVE_MASK))
			vaw *= -1;

		info->thewmaw_twim[i] = vaw;

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_twim=0x%x (%d)\n",
			    i, pg_th, vaw);
	}

	info->pg_thewmaw_twim = pg;
}

static void wtw8922a_phycap_pawsing_pa_bias_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	static const u32 pabias_twim_addw[WF_PATH_NUM_8922A] = {0x1707, 0x1734};
	static const u32 check_pa_pad_twim_addw = 0x1700;
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u32 addw = wtwdev->chip->phycap_addw;
	u8 vaw;
	u8 i;

	vaw = phycap_map[check_pa_pad_twim_addw - addw];
	if (vaw != 0xff)
		info->pg_pa_bias_twim = twue;

	fow (i = 0; i < WF_PATH_NUM_8922A; i++) {
		info->pa_bias_twim[i] = phycap_map[pabias_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d pa_bias_twim=0x%x\n",
			    i, info->pa_bias_twim[i]);
	}
}

static void wtw8922a_phycap_pawsing_pad_bias_twim(stwuct wtw89_dev *wtwdev,
						  u8 *phycap_map)
{
	static const u32 pad_bias_twim_addw[WF_PATH_NUM_8922A] = {0x1708, 0x1735};
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8922A; i++) {
		info->pad_bias_twim[i] = phycap_map[pad_bias_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PAD_BIAS][TWIM] path=%d pad_bias_twim=0x%x\n",
			    i, info->pad_bias_twim[i]);
	}
}

static int wtw8922a_wead_phycap(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	wtw8922a_phycap_pawsing_thewmaw_twim(wtwdev, phycap_map);
	wtw8922a_phycap_pawsing_pa_bias_twim(wtwdev, phycap_map);
	wtw8922a_phycap_pawsing_pad_bias_twim(wtwdev, phycap_map);

	wetuwn 0;
}

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt wtw_wowwan_stub_8922a = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = WTW89_MAX_PATTEWN_NUM,
	.pattewn_max_wen = WTW89_MAX_PATTEWN_SIZE,
	.pattewn_min_wen = 1,
};
#endif

static const stwuct wtw89_chip_ops wtw8922a_chip_ops = {
	.wead_efuse		= wtw8922a_wead_efuse,
	.wead_phycap		= wtw8922a_wead_phycap,
	.pww_on_func		= wtw8922a_pww_on_func,
	.pww_off_func		= wtw8922a_pww_off_func,
};

const stwuct wtw89_chip_info wtw8922a_chip_info = {
	.chip_id		= WTW8922A,
	.chip_gen		= WTW89_CHIP_BE,
	.ops			= &wtw8922a_chip_ops,
	.mac_def		= &wtw89_mac_gen_be,
	.phy_def		= &wtw89_phy_gen_be,
	.fw_basename		= WTW8922A_FW_BASENAME,
	.fw_fowmat_max		= WTW8922A_FW_FOWMAT_MAX,
	.twy_ce_fw		= fawse,
	.bbmcu_nw		= 1,
	.needed_fw_ewms		= WTW89_BE_GEN_DEF_NEEDED_FW_EWEMENTS,
	.fifo_size		= 589824,
	.smaww_fifo_size	= fawse,
	.dwe_scc_wsvd_size	= 0,
	.max_amsdu_wimit	= 8000,
	.dis_2g_40m_uw_ofdma	= fawse,
	.wsvd_pwe_ofst		= 0x8f800,
	.hfc_pawam_ini		= wtw8922a_hfc_pawam_ini_pcie,
	.dwe_mem		= wtw8922a_dwe_mem_pcie,
	.wde_qempty_acq_gwpnum	= 4,
	.wde_qempty_mgq_gwpsew	= 4,
	.wf_base_addw		= {0xe000, 0xf000},
	.pww_on_seq		= NUWW,
	.pww_off_seq		= NUWW,
	.bb_tabwe		= NUWW,
	.bb_gain_tabwe		= NUWW,
	.wf_tabwe		= {},
	.nctw_tabwe		= NUWW,
	.nctw_post_tabwe	= NUWW,
	.dfwt_pawms		= NUWW, /* woad pawm fwom fw */
	.wfe_pawms_conf		= NUWW, /* woad pawm fwom fw */
	.txpww_factow_wf	= 2,
	.txpww_factow_mac	= 1,
	.dig_tabwe		= NUWW,
	.tssi_dbw_tabwe		= NUWW,
	.suppowt_chanctx_num	= 1,
	.suppowt_bands		= BIT(NW80211_BAND_2GHZ) |
				  BIT(NW80211_BAND_5GHZ) |
				  BIT(NW80211_BAND_6GHZ),
	.suppowt_unii4		= twue,
	.uw_tb_wavefowm_ctww	= fawse,
	.uw_tb_pww_diff		= fawse,
	.hw_sec_hdw		= twue,
	.wf_path_num		= 2,
	.tx_nss			= 2,
	.wx_nss			= 2,
	.acam_num		= 128,
	.bcam_num		= 20,
	.scam_num		= 32,
	.bacam_num		= 8,
	.bacam_dynamic_num	= 8,
	.bacam_vew		= WTW89_BACAM_V1,
	.ppdu_max_usw		= 16,
	.sec_ctww_efuse_size	= 4,
	.physicaw_efuse_size	= 0x1300,
	.wogicaw_efuse_size	= 0x70000,
	.wimit_efuse_size	= 0x40000,
	.dav_phy_efuse_size	= 0,
	.dav_wog_efuse_size	= 0,
	.efuse_bwocks		= wtw8922a_efuse_bwocks,
	.phycap_addw		= 0x1700,
	.phycap_size		= 0x38,

	.ps_mode_suppowted	= BIT(WTW89_PS_MODE_WFOFF) |
				  BIT(WTW89_PS_MODE_CWK_GATED) |
				  BIT(WTW89_PS_MODE_PWW_GATED),
	.wow_powew_hci_modes	= 0,
	.hci_func_en_addw	= W_BE_HCI_FUNC_EN,
	.h2c_desc_size		= sizeof(stwuct wtw89_wxdesc_showt_v2),
	.txwd_body_size		= sizeof(stwuct wtw89_txwd_body_v2),
	.txwd_info_size		= sizeof(stwuct wtw89_txwd_info_v2),
	.cfo_swc_fd		= twue,
	.cfo_hw_comp            = twue,
	.dcfo_comp		= NUWW,
	.dcfo_comp_sft		= 0,
	.imw_info		= NUWW,
	.imw_dmac_tabwe		= &wtw8922a_imw_dmac_tabwe,
	.imw_cmac_tabwe		= &wtw8922a_imw_cmac_tabwe,
	.bss_cww_vwd		= {W_BSS_CWW_VWD_V2, B_BSS_CWW_VWD0_V2},
	.bss_cww_map_weg	= W_BSS_CWW_MAP_V2,
	.dma_ch_mask		= 0,
#ifdef CONFIG_PM
	.wowwan_stub		= &wtw_wowwan_stub_8922a,
#endif
	.xtaw_info		= NUWW,
};
EXPOWT_SYMBOW(wtw8922a_chip_info);

MODUWE_FIWMWAWE(WTW8922A_MODUWE_FIWMWAWE);
MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11be wiwewess 8922A dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
