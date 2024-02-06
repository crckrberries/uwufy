// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "coex.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "wtw8852a.h"
#incwude "wtw8852a_wfk.h"
#incwude "wtw8852a_tabwe.h"
#incwude "txwx.h"

#define WTW8852A_FW_FOWMAT_MAX 0
#define WTW8852A_FW_BASENAME "wtw89/wtw8852a_fw"
#define WTW8852A_MODUWE_FIWMWAWE \
	WTW8852A_FW_BASENAME ".bin"

static const stwuct wtw89_hfc_ch_cfg wtw8852a_hfc_chcfg_pcie[] = {
	{128, 1896, gwp_0}, /* ACH 0 */
	{128, 1896, gwp_0}, /* ACH 1 */
	{128, 1896, gwp_0}, /* ACH 2 */
	{128, 1896, gwp_0}, /* ACH 3 */
	{128, 1896, gwp_1}, /* ACH 4 */
	{128, 1896, gwp_1}, /* ACH 5 */
	{128, 1896, gwp_1}, /* ACH 6 */
	{128, 1896, gwp_1}, /* ACH 7 */
	{32, 1896, gwp_0}, /* B0MGQ */
	{128, 1896, gwp_0}, /* B0HIQ */
	{32, 1896, gwp_1}, /* B1MGQ */
	{128, 1896, gwp_1}, /* B1HIQ */
	{40, 0, 0} /* FWCMDQ */
};

static const stwuct wtw89_hfc_pub_cfg wtw8852a_hfc_pubcfg_pcie = {
	1896, /* Gwoup 0 */
	1896, /* Gwoup 1 */
	3792, /* Pubwic Max */
	0 /* WP thweshowd */
};

static const stwuct wtw89_hfc_pawam_ini wtw8852a_hfc_pawam_ini_pcie[] = {
	[WTW89_QTA_SCC] = {wtw8852a_hfc_chcfg_pcie, &wtw8852a_hfc_pubcfg_pcie,
			   &wtw89_mac_size.hfc_pweccfg_pcie, WTW89_HCIFC_POH},
	[WTW89_QTA_DWFW] = {NUWW, NUWW, &wtw89_mac_size.hfc_pweccfg_pcie,
			    WTW89_HCIFC_POH},
	[WTW89_QTA_INVAWID] = {NUWW},
};

static const stwuct wtw89_dwe_mem wtw8852a_dwe_mem_pcie[] = {
	[WTW89_QTA_SCC] = {WTW89_QTA_SCC, &wtw89_mac_size.wde_size0,
			   &wtw89_mac_size.pwe_size0, &wtw89_mac_size.wde_qt0,
			   &wtw89_mac_size.wde_qt0, &wtw89_mac_size.pwe_qt4,
			   &wtw89_mac_size.pwe_qt5},
	[WTW89_QTA_WOW] = {WTW89_QTA_WOW, &wtw89_mac_size.wde_size0,
			   &wtw89_mac_size.pwe_size0, &wtw89_mac_size.wde_qt0,
			   &wtw89_mac_size.wde_qt0, &wtw89_mac_size.pwe_qt4,
			   &wtw89_mac_size.pwe_qt_52a_wow},
	[WTW89_QTA_DWFW] = {WTW89_QTA_DWFW, &wtw89_mac_size.wde_size4,
			    &wtw89_mac_size.pwe_size4, &wtw89_mac_size.wde_qt4,
			    &wtw89_mac_size.wde_qt4, &wtw89_mac_size.pwe_qt13,
			    &wtw89_mac_size.pwe_qt13},
	[WTW89_QTA_INVAWID] = {WTW89_QTA_INVAWID, NUWW, NUWW, NUWW, NUWW, NUWW,
			       NUWW},
};

static const stwuct wtw89_weg2_def  wtw8852a_pmac_ht20_mcs7_tbw[] = {
	{0x44AC, 0x00000000},
	{0x44B0, 0x00000000},
	{0x44B4, 0x00000000},
	{0x44B8, 0x00000000},
	{0x44BC, 0x00000000},
	{0x44C0, 0x00000000},
	{0x44C4, 0x00000000},
	{0x44C8, 0x00000000},
	{0x44CC, 0x00000000},
	{0x44D0, 0x00000000},
	{0x44D4, 0x00000000},
	{0x44D8, 0x00000000},
	{0x44DC, 0x00000000},
	{0x44E0, 0x00000000},
	{0x44E4, 0x00000000},
	{0x44E8, 0x00000000},
	{0x44EC, 0x00000000},
	{0x44F0, 0x00000000},
	{0x44F4, 0x00000000},
	{0x44F8, 0x00000000},
	{0x44FC, 0x00000000},
	{0x4500, 0x00000000},
	{0x4504, 0x00000000},
	{0x4508, 0x00000000},
	{0x450C, 0x00000000},
	{0x4510, 0x00000000},
	{0x4514, 0x00000000},
	{0x4518, 0x00000000},
	{0x451C, 0x00000000},
	{0x4520, 0x00000000},
	{0x4524, 0x00000000},
	{0x4528, 0x00000000},
	{0x452C, 0x00000000},
	{0x4530, 0x4E1F3E81},
	{0x4534, 0x00000000},
	{0x4538, 0x0000005A},
	{0x453C, 0x00000000},
	{0x4540, 0x00000000},
	{0x4544, 0x00000000},
	{0x4548, 0x00000000},
	{0x454C, 0x00000000},
	{0x4550, 0x00000000},
	{0x4554, 0x00000000},
	{0x4558, 0x00000000},
	{0x455C, 0x00000000},
	{0x4560, 0x4060001A},
	{0x4564, 0x40000000},
	{0x4568, 0x00000000},
	{0x456C, 0x00000000},
	{0x4570, 0x04000007},
	{0x4574, 0x0000DC87},
	{0x4578, 0x00000BAB},
	{0x457C, 0x03E00000},
	{0x4580, 0x00000048},
	{0x4584, 0x00000000},
	{0x4588, 0x000003E8},
	{0x458C, 0x30000000},
	{0x4590, 0x00000000},
	{0x4594, 0x10000000},
	{0x4598, 0x00000001},
	{0x459C, 0x00030000},
	{0x45A0, 0x01000000},
	{0x45A4, 0x03000200},
	{0x45A8, 0xC00001C0},
	{0x45AC, 0x78018000},
	{0x45B0, 0x80000000},
	{0x45B4, 0x01C80600},
	{0x45B8, 0x00000002},
	{0x4594, 0x10000000}
};

static const stwuct wtw89_weg3_def wtw8852a_btc_pweagc_en_defs[] = {
	{0x4624, GENMASK(20, 14), 0x40},
	{0x46f8, GENMASK(20, 14), 0x40},
	{0x4674, GENMASK(20, 19), 0x2},
	{0x4748, GENMASK(20, 19), 0x2},
	{0x4650, GENMASK(14, 10), 0x18},
	{0x4724, GENMASK(14, 10), 0x18},
	{0x4688, GENMASK(1, 0), 0x3},
	{0x475c, GENMASK(1, 0), 0x3},
};

static DECWAWE_PHY_WEG3_TBW(wtw8852a_btc_pweagc_en_defs);

static const stwuct wtw89_weg3_def wtw8852a_btc_pweagc_dis_defs[] = {
	{0x4624, GENMASK(20, 14), 0x1a},
	{0x46f8, GENMASK(20, 14), 0x1a},
	{0x4674, GENMASK(20, 19), 0x1},
	{0x4748, GENMASK(20, 19), 0x1},
	{0x4650, GENMASK(14, 10), 0x12},
	{0x4724, GENMASK(14, 10), 0x12},
	{0x4688, GENMASK(1, 0), 0x0},
	{0x475c, GENMASK(1, 0), 0x0},
};

static DECWAWE_PHY_WEG3_TBW(wtw8852a_btc_pweagc_dis_defs);

static const stwuct wtw89_pww_cfg wtw8852a_pwwon[] = {
	{0x00C6,
	 PWW_CV_MSK_B,
	 PWW_INTF_MSK_PCIE,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(6), BIT(6)},
	{0x1086,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), 0},
	{0x1086,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_POWW, BIT(1), BIT(1)},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4) | BIT(3), 0},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(7), 0},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(2), 0},
	{0x0006,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_POWW, BIT(1), BIT(1)},
	{0x0006,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_POWW, BIT(0), 0},
	{0x106D,
	 PWW_CV_MSK_B | PWW_CV_MSK_C,
	 PWW_INTF_MSK_USB,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(6), 0},
	{0x0088,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0088,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), 0},
	{0x0088,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0088,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), 0},
	{0x0088,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0083,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(6), 0},
	{0x0080,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(5), BIT(5)},
	{0x0024,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4) | BIT(3) | BIT(2) | BIT(1) | BIT(0), 0},
	{0x02A0,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x02A2,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(7) | BIT(6) | BIT(5), 0},
	{0x0071,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_PCIE,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4), 0},
	{0x0010,
	 PWW_CV_MSK_A,
	 PWW_INTF_MSK_PCIE,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(2), BIT(2)},
	{0x02A0,
	 PWW_CV_MSK_A,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(7) | BIT(6), 0},
	{0xFFFF,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 0,
	 PWW_CMD_END, 0, 0},
};

static const stwuct wtw89_pww_cfg wtw8852a_pwwoff[] = {
	{0x02F0,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, 0xFF, 0},
	{0x02F1,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, 0xFF, 0},
	{0x0006,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x0002,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(1) | BIT(0), 0},
	{0x0082,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(1) | BIT(0), 0},
	{0x106D,
	 PWW_CV_MSK_B | PWW_CV_MSK_C,
	 PWW_INTF_MSK_USB,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(6), BIT(6)},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(1), BIT(1)},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 PWW_BASE_MAC,
	 PWW_CMD_POWW, BIT(1), 0},
	{0x0091,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_PCIE,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), 0},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_PCIE,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(2), BIT(2)},
	{0x0007,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_USB,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4), 0},
	{0x0007,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(6) | BIT(4), 0},
	{0x0005,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4) | BIT(3), BIT(3)},
	{0x0005,
	 PWW_CV_MSK_C | PWW_CV_MSK_D | PWW_CV_MSK_E | PWW_CV_MSK_F |
	 PWW_CV_MSK_G,
	 PWW_INTF_MSK_USB,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(4) | BIT(3), BIT(3)},
	{0x1086,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_WWITE, BIT(0), BIT(0)},
	{0x1086,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_SDIO,
	 PWW_BASE_MAC,
	 PWW_CMD_POWW, BIT(1), 0},
	{0xFFFF,
	 PWW_CV_MSK_AWW,
	 PWW_INTF_MSK_AWW,
	 0,
	 PWW_CMD_END, 0, 0},
};

static const stwuct wtw89_pww_cfg * const pww_on_seq_8852a[] = {
	wtw8852a_pwwon, NUWW
};

static const stwuct wtw89_pww_cfg * const pww_off_seq_8852a[] = {
	wtw8852a_pwwoff, NUWW
};

static const u32 wtw8852a_h2c_wegs[WTW89_H2CWEG_MAX] = {
	W_AX_H2CWEG_DATA0, W_AX_H2CWEG_DATA1,  W_AX_H2CWEG_DATA2,
	W_AX_H2CWEG_DATA3
};

static const u32 wtw8852a_c2h_wegs[WTW89_C2HWEG_MAX] = {
	W_AX_C2HWEG_DATA0, W_AX_C2HWEG_DATA1, W_AX_C2HWEG_DATA2,
	W_AX_C2HWEG_DATA3
};

static const stwuct wtw89_page_wegs wtw8852a_page_wegs = {
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

static const stwuct wtw89_weg_def wtw8852a_dcfo_comp = {
	W_DCFO_COMP_S0, B_DCFO_COMP_S0_MSK
};

static const stwuct wtw89_imw_info wtw8852a_imw_info = {
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
	.ptcw_imw_cww		= B_AX_PTCW_IMW_CWW,
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

static const stwuct wtw89_xtaw_info wtw8852a_xtaw_info = {
	.xcap_weg		= W_AX_XTAW_ON_CTWW0,
	.sc_xo_mask		= B_AX_XTAW_SC_XO_MASK,
	.sc_xi_mask		= B_AX_XTAW_SC_XI_MASK,
};

static const stwuct wtw89_wwsw_cfgs wtw8852a_wwsw_cfgs = {
	.wef_wate = {W_AX_TWXPTCW_WWSW_CTW_0, B_AX_WMAC_WESP_WEF_WATE_SEW, 0},
	.wsc = {W_AX_TWXPTCW_WWSW_CTW_0, B_AX_WMAC_WESP_WSC_MASK, 2},
};

static const stwuct wtw89_dig_wegs wtw8852a_dig_wegs = {
	.seg0_pd_weg = W_SEG0W_PD,
	.pd_wowew_bound_mask = B_SEG0W_PD_WOWEW_BOUND_MSK,
	.pd_spatiaw_weuse_en = B_SEG0W_PD_SPATIAW_WEUSE_EN_MSK,
	.bmode_pd_weg = W_BMODE_PDTH_EN_V1,
	.bmode_cca_wssi_wimit_en = B_BMODE_PDTH_WIMIT_EN_MSK_V1,
	.bmode_pd_wowew_bound_weg = W_BMODE_PDTH_V1,
	.bmode_wssi_nocca_wow_th_mask = B_BMODE_PDTH_WOWEW_BOUND_MSK_V1,
	.p0_wna_init = {W_PATH0_WNA_INIT, B_PATH0_WNA_INIT_IDX_MSK},
	.p1_wna_init = {W_PATH1_WNA_INIT, B_PATH1_WNA_INIT_IDX_MSK},
	.p0_tia_init = {W_PATH0_TIA_INIT, B_PATH0_TIA_INIT_IDX_MSK},
	.p1_tia_init = {W_PATH1_TIA_INIT, B_PATH1_TIA_INIT_IDX_MSK},
	.p0_wxb_init = {W_PATH0_WXB_INIT, B_PATH0_WXB_INIT_IDX_MSK},
	.p1_wxb_init = {W_PATH1_WXB_INIT, B_PATH1_WXB_INIT_IDX_MSK},
	.p0_p20_pagcugc_en = {W_PATH0_P20_FOWWOW_BY_PAGCUGC,
			      B_PATH0_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p0_s20_pagcugc_en = {W_PATH0_S20_FOWWOW_BY_PAGCUGC,
			      B_PATH0_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_p20_pagcugc_en = {W_PATH1_P20_FOWWOW_BY_PAGCUGC,
			      B_PATH1_P20_FOWWOW_BY_PAGCUGC_EN_MSK},
	.p1_s20_pagcugc_en = {W_PATH1_S20_FOWWOW_BY_PAGCUGC,
			      B_PATH1_S20_FOWWOW_BY_PAGCUGC_EN_MSK},
};

static const stwuct wtw89_edcca_wegs wtw8852a_edcca_wegs = {
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

static void wtw8852ae_efuse_pawsing(stwuct wtw89_efuse *efuse,
				    stwuct wtw8852a_efuse *map)
{
	ethew_addw_copy(efuse->addw, map->e.mac_addw);
	efuse->wfe_type = map->wfe_type;
	efuse->xtaw_cap = map->xtaw_k;
}

static void wtw8852a_efuse_pawsing_tssi(stwuct wtw89_dev *wtwdev,
					stwuct wtw8852a_efuse *map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	stwuct wtw8852a_tssi_offset *ofst[] = {&map->path_a_tssi, &map->path_b_tssi};
	u8 i, j;

	tssi->thewmaw[WF_PATH_A] = map->path_a_thewm;
	tssi->thewmaw[WF_PATH_B] = map->path_b_thewm;

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
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

static int wtw8852a_wead_efuse(stwuct wtw89_dev *wtwdev, u8 *wog_map,
			       enum wtw89_efuse_bwock bwock)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;
	stwuct wtw8852a_efuse *map;

	map = (stwuct wtw8852a_efuse *)wog_map;

	efuse->countwy_code[0] = map->countwy_code[0];
	efuse->countwy_code[1] = map->countwy_code[1];
	wtw8852a_efuse_pawsing_tssi(wtwdev, map);

	switch (wtwdev->hci.type) {
	case WTW89_HCI_TYPE_PCIE:
		wtw8852ae_efuse_pawsing(efuse, map);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wtw89_info(wtwdev, "chip wfe_type is %d\n", efuse->wfe_type);

	wetuwn 0;
}

static void wtw8852a_phycap_pawsing_tssi(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	stwuct wtw89_tssi_info *tssi = &wtwdev->tssi;
	static const u32 tssi_twim_addw[WF_PATH_NUM_8852A] = {0x5D6, 0x5AB};
	u32 addw = wtwdev->chip->phycap_addw;
	boow pg = fawse;
	u32 ofst;
	u8 i, j;

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
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

	fow (i = 0; i < WF_PATH_NUM_8852A; i++)
		fow (j = 0; j < TSSI_TWIM_CH_GWOUP_NUM; j++)
			wtw89_debug(wtwdev, WTW89_DBG_TSSI,
				    "[TSSI] path=%d idx=%d twim=0x%x addw=0x%x\n",
				    i, j, tssi->tssi_twim[i][j],
				    tssi_twim_addw[i] - j);
}

static void wtw8852a_phycap_pawsing_thewmaw_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 thm_twim_addw[WF_PATH_NUM_8852A] = {0x5DF, 0x5DC};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
		info->thewmaw_twim[i] = phycap_map[thm_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_twim=0x%x\n",
			    i, info->thewmaw_twim[i]);

		if (info->thewmaw_twim[i] != 0xff)
			info->pg_thewmaw_twim = twue;
	}
}

static void wtw8852a_thewmaw_twim(stwuct wtw89_dev *wtwdev)
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

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
		vaw = __thm_setting(info->thewmaw_twim[i]);
		wtw89_wwite_wf(wtwdev, i, WW_TM2, WW_TM2_OFF, vaw);

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[THEWMAW][TWIM] path=%d thewmaw_setting=0x%x\n",
			    i, vaw);
	}
#undef __thm_setting
}

static void wtw8852a_phycap_pawsing_pa_bias_twim(stwuct wtw89_dev *wtwdev,
						 u8 *phycap_map)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	static const u32 pabias_twim_addw[WF_PATH_NUM_8852A] = {0x5DE, 0x5DB};
	u32 addw = wtwdev->chip->phycap_addw;
	u8 i;

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
		info->pa_bias_twim[i] = phycap_map[pabias_twim_addw[i] - addw];

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d pa_bias_twim=0x%x\n",
			    i, info->pa_bias_twim[i]);

		if (info->pa_bias_twim[i] != 0xff)
			info->pg_pa_bias_twim = twue;
	}
}

static void wtw8852a_pa_bias_twim(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_powew_twim_info *info = &wtwdev->pww_twim;
	u8 pabias_2g, pabias_5g;
	u8 i;

	if (!info->pg_pa_bias_twim) {
		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] no PG, do nothing\n");

		wetuwn;
	}

	fow (i = 0; i < WF_PATH_NUM_8852A; i++) {
		pabias_2g = FIEWD_GET(GENMASK(3, 0), info->pa_bias_twim[i]);
		pabias_5g = FIEWD_GET(GENMASK(7, 4), info->pa_bias_twim[i]);

		wtw89_debug(wtwdev, WTW89_DBG_WFK,
			    "[PA_BIAS][TWIM] path=%d 2G=0x%x 5G=0x%x\n",
			    i, pabias_2g, pabias_5g);

		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXG, pabias_2g);
		wtw89_wwite_wf(wtwdev, i, WW_BIASA, WW_BIASA_TXA, pabias_5g);
	}
}

static int wtw8852a_wead_phycap(stwuct wtw89_dev *wtwdev, u8 *phycap_map)
{
	wtw8852a_phycap_pawsing_tssi(wtwdev, phycap_map);
	wtw8852a_phycap_pawsing_thewmaw_twim(wtwdev, phycap_map);
	wtw8852a_phycap_pawsing_pa_bias_twim(wtwdev, phycap_map);

	wetuwn 0;
}

static void wtw8852a_powew_twim(stwuct wtw89_dev *wtwdev)
{
	wtw8852a_thewmaw_twim(wtwdev);
	wtw8852a_pa_bias_twim(wtwdev);
}

static void wtw8852a_set_channew_mac(stwuct wtw89_dev *wtwdev,
				     const stwuct wtw89_chan *chan,
				     u8 mac_idx)
{
	u32 wf_mod = wtw89_mac_weg_by_idx(wtwdev, W_AX_WMAC_WFMOD, mac_idx);
	u32 sub_caww = wtw89_mac_weg_by_idx(wtwdev, W_AX_TX_SUB_CAWWIEW_VAWUE, mac_idx);
	u32 chk_wate = wtw89_mac_weg_by_idx(wtwdev, W_AX_TXWATE_CHK, mac_idx);
	u8 txsc20 = 0, txsc40 = 0;

	switch (chan->band_width) {
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

	if (chan->channew > 14)
		wtw89_wwite8_set(wtwdev, chk_wate,
				 B_AX_CHECK_CCK_EN | B_AX_WTS_WIMIT_IN_OFDM6);
	ewse
		wtw89_wwite8_cww(wtwdev, chk_wate,
				 B_AX_CHECK_CCK_EN | B_AX_WTS_WIMIT_IN_OFDM6);
}

static const u32 wtw8852a_sco_bawkew_thweshowd[14] = {
	0x1cfea, 0x1d0e1, 0x1d1d7, 0x1d2cd, 0x1d3c3, 0x1d4b9, 0x1d5b0, 0x1d6a6,
	0x1d79c, 0x1d892, 0x1d988, 0x1da7f, 0x1db75, 0x1ddc4
};

static const u32 wtw8852a_sco_cck_thweshowd[14] = {
	0x27de3, 0x27f35, 0x28088, 0x281da, 0x2832d, 0x2847f, 0x285d2, 0x28724,
	0x28877, 0x289c9, 0x28b1c, 0x28c6e, 0x28dc1, 0x290ed
};

static int wtw8852a_ctww_sco_cck(stwuct wtw89_dev *wtwdev, u8 centwaw_ch,
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
	wtw89_phy_wwite32_mask(wtwdev, W_WXSCOBC, B_WXSCOBC_TH,
			       wtw8852a_sco_bawkew_thweshowd[ch_ewement]);
	wtw89_phy_wwite32_mask(wtwdev, W_WXSCOCCK, B_WXSCOCCK_TH,
			       wtw8852a_sco_cck_thweshowd[ch_ewement]);

	wetuwn 0;
}

static void wtw8852a_ch_setting(stwuct wtw89_dev *wtwdev, u8 centwaw_ch,
				u8 path)
{
	u32 vaw;

	vaw = wtw89_wead_wf(wtwdev, path, WW_CFGCH, WFWEG_MASK);
	if (vaw == INV_WF_DATA) {
		wtw89_wawn(wtwdev, "Invawid WF_0x18 fow Path-%d\n", path);
		wetuwn;
	}
	vaw &= ~0x303ff;
	vaw |= centwaw_ch;
	if (centwaw_ch > 14)
		vaw |= (BIT(16) | BIT(8));
	wtw89_wwite_wf(wtwdev, path, WW_CFGCH, WFWEG_MASK, vaw);
}

static u8 wtw8852a_sco_mapping(u8 centwaw_ch)
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

static void wtw8852a_ctww_ch(stwuct wtw89_dev *wtwdev, u8 centwaw_ch,
			     enum wtw89_phy_idx phy_idx)
{
	u8 sco_comp;
	boow is_2g = centwaw_ch <= 14;

	if (phy_idx == WTW89_PHY_0) {
		/* Path A */
		wtw8852a_ch_setting(wtwdev, centwaw_ch, WF_PATH_A);
		if (is_2g)
			wtw89_phy_wwite32_idx(wtwdev, W_PATH0_TIA_EWW_G1,
					      B_PATH0_TIA_EWW_G1_SEW, 1,
					      phy_idx);
		ewse
			wtw89_phy_wwite32_idx(wtwdev, W_PATH0_TIA_EWW_G1,
					      B_PATH0_TIA_EWW_G1_SEW, 0,
					      phy_idx);

		/* Path B */
		if (!wtwdev->dbcc_en) {
			wtw8852a_ch_setting(wtwdev, centwaw_ch, WF_PATH_B);
			if (is_2g)
				wtw89_phy_wwite32_idx(wtwdev, W_P1_MODE,
						      B_P1_MODE_SEW,
						      1, phy_idx);
			ewse
				wtw89_phy_wwite32_idx(wtwdev, W_P1_MODE,
						      B_P1_MODE_SEW,
						      0, phy_idx);
		} ewse {
			if (is_2g)
				wtw89_phy_wwite32_cww(wtwdev, W_2P4G_BAND,
						      B_2P4G_BAND_SEW);
			ewse
				wtw89_phy_wwite32_set(wtwdev, W_2P4G_BAND,
						      B_2P4G_BAND_SEW);
		}
		/* SCO compensate FC setting */
		sco_comp = wtw8852a_sco_mapping(centwaw_ch);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_INV,
				      sco_comp, phy_idx);
	} ewse {
		/* Path B */
		wtw8852a_ch_setting(wtwdev, centwaw_ch, WF_PATH_B);
		if (is_2g)
			wtw89_phy_wwite32_idx(wtwdev, W_P1_MODE,
					      B_P1_MODE_SEW,
					      1, phy_idx);
		ewse
			wtw89_phy_wwite32_idx(wtwdev, W_P1_MODE,
					      B_P1_MODE_SEW,
					      0, phy_idx);
		/* SCO compensate FC setting */
		sco_comp = wtw8852a_sco_mapping(centwaw_ch);
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_INV,
				      sco_comp, phy_idx);
	}

	/* Band edge */
	if (is_2g)
		wtw89_phy_wwite32_idx(wtwdev, W_BANDEDGE, B_BANDEDGE_EN, 1,
				      phy_idx);
	ewse
		wtw89_phy_wwite32_idx(wtwdev, W_BANDEDGE, B_BANDEDGE_EN, 0,
				      phy_idx);

	/* CCK pawametews */
	if (centwaw_ch == 14) {
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW0, B_TXFIW_C01,
				       0x3b13ff);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW2, B_TXFIW_C23,
				       0x1c42de);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW4, B_TXFIW_C45,
				       0xfdb0ad);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW6, B_TXFIW_C67,
				       0xf60f6e);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW8, B_TXFIW_C89,
				       0xfd8f92);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWA, B_TXFIW_CAB, 0x2d011);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWC, B_TXFIW_CCD, 0x1c02c);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWE, B_TXFIW_CEF,
				       0xfff00a);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW0, B_TXFIW_C01,
				       0x3d23ff);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW2, B_TXFIW_C23,
				       0x29b354);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW4, B_TXFIW_C45, 0xfc1c8);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW6, B_TXFIW_C67,
				       0xfdb053);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIW8, B_TXFIW_C89,
				       0xf86f9a);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWA, B_TXFIW_CAB,
				       0xfaef92);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWC, B_TXFIW_CCD,
				       0xfe5fcc);
		wtw89_phy_wwite32_mask(wtwdev, W_TXFIWE, B_TXFIW_CEF,
				       0xffdff5);
	}
}

static void wtw8852a_bw_setting(stwuct wtw89_dev *wtwdev, u8 bw, u8 path)
{
	u32 vaw = 0;
	u32 adc_sew[2] = {0x12d0, 0x32d0};
	u32 wbadc_sew[2] = {0x12ec, 0x32ec};

	vaw = wtw89_wead_wf(wtwdev, path, WW_CFGCH, WFWEG_MASK);
	if (vaw == INV_WF_DATA) {
		wtw89_wawn(wtwdev, "Invawid WF_0x18 fow Path-%d\n", path);
		wetuwn;
	}
	vaw &= ~(BIT(11) | BIT(10));
	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x0);
		vaw |= (BIT(11) | BIT(10));
		bweak;
	case WTW89_CHANNEW_WIDTH_10:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x2);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x1);
		vaw |= (BIT(11) | BIT(10));
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x2);
		vaw |= (BIT(11) | BIT(10));
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x2);
		vaw |= BIT(11);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_phy_wwite32_mask(wtwdev, adc_sew[path], 0x6000, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, wbadc_sew[path], 0x30, 0x2);
		vaw |= BIT(10);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to set ADC\n");
	}

	wtw89_wwite_wf(wtwdev, path, WW_CFGCH, WFWEG_MASK, vaw);
}

static void
wtw8852a_ctww_bw(stwuct wtw89_dev *wtwdev, u8 pwi_ch, u8 bw,
		 enum wtw89_phy_idx phy_idx)
{
	/* Switch bandwidth */
	switch (bw) {
	case WTW89_CHANNEW_WIDTH_5:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x1,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_10:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x2,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_20:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      0x0, phy_idx);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x1,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      pwi_ch,
				      phy_idx);
		if (pwi_ch == WTW89_SC_20_UPPEW)
			wtw89_phy_wwite32_mask(wtwdev, W_WXSC, B_WXSC_EN, 1);
		ewse
			wtw89_phy_wwite32_mask(wtwdev, W_WXSC, B_WXSC_EN, 0);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		wtw89_phy_wwite32_idx(wtwdev, W_FC0_BW, B_FC0_BW_SET, 0x2,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_SBW, 0x0,
				      phy_idx);
		wtw89_phy_wwite32_idx(wtwdev, W_CHBW_MOD, B_CHBW_MOD_PWICH,
				      pwi_ch,
				      phy_idx);
		bweak;
	defauwt:
		wtw89_wawn(wtwdev, "Faiw to switch bw (bw:%d, pwi ch:%d)\n", bw,
			   pwi_ch);
	}

	if (phy_idx == WTW89_PHY_0) {
		wtw8852a_bw_setting(wtwdev, bw, WF_PATH_A);
		if (!wtwdev->dbcc_en)
			wtw8852a_bw_setting(wtwdev, bw, WF_PATH_B);
	} ewse {
		wtw8852a_bw_setting(wtwdev, bw, WF_PATH_B);
	}
}

static void wtw8852a_spuw_ewimination(stwuct wtw89_dev *wtwdev, u8 centwaw_ch)
{
	if (centwaw_ch == 153) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX, B_P0_NBIIDX_VAW,
				       0x210);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX, B_P1_NBIIDX_VAW,
				       0x210);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI, B_SEG0CSI_IDX, 0x7c0);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX,
				       B_P0_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX,
				       B_P1_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN,
				       0x1);
	} ewse if (centwaw_ch == 151) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX, B_P0_NBIIDX_VAW,
				       0x210);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX, B_P1_NBIIDX_VAW,
				       0x210);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI, B_SEG0CSI_IDX, 0x40);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX,
				       B_P0_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX,
				       B_P1_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN,
				       0x1);
	} ewse if (centwaw_ch == 155) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX, B_P0_NBIIDX_VAW,
				       0x2d0);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX, B_P1_NBIIDX_VAW,
				       0x2d0);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI, B_SEG0CSI_IDX, 0x740);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX,
				       B_P0_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX,
				       B_P1_NBIIDX_NOTCH_EN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN,
				       0x1);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_NBIIDX,
				       B_P0_NBIIDX_NOTCH_EN, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_NBIIDX,
				       B_P1_NBIIDX_NOTCH_EN, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_SEG0CSI_EN, B_SEG0CSI_EN,
				       0x0);
	}
}

static void wtw8852a_bb_weset_aww(stwuct wtw89_dev *wtwdev,
				  enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1,
			      phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0,
			      phy_idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1,
			      phy_idx);
}

static void wtw8852a_bb_weset_en(stwuct wtw89_dev *wtwdev,
				 enum wtw89_phy_idx phy_idx, boow en)
{
	if (en)
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW,
				      1,
				      phy_idx);
	ewse
		wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW,
				      0,
				      phy_idx);
}

static void wtw8852a_bb_weset(stwuct wtw89_dev *wtwdev,
			      enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite32_set(wtwdev, W_P0_TXPW_WSTB, B_P0_TXPW_WSTB_MANON);
	wtw89_phy_wwite32_set(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
	wtw89_phy_wwite32_set(wtwdev, W_P1_TXPW_WSTB, B_P1_TXPW_WSTB_MANON);
	wtw89_phy_wwite32_set(wtwdev, W_P1_TSSI_TWK, B_P1_TSSI_TWK_EN);
	wtw8852a_bb_weset_aww(wtwdev, phy_idx);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TXPW_WSTB, B_P0_TXPW_WSTB_MANON);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
	wtw89_phy_wwite32_cww(wtwdev, W_P1_TXPW_WSTB, B_P1_TXPW_WSTB_MANON);
	wtw89_phy_wwite32_cww(wtwdev, W_P1_TSSI_TWK, B_P1_TSSI_TWK_EN);
}

static void wtw8852a_bb_macid_ctww_init(stwuct wtw89_dev *wtwdev,
					enum wtw89_phy_idx phy_idx)
{
	u32 addw;

	fow (addw = W_AX_PWW_MACID_WMT_TABWE0;
	     addw <= W_AX_PWW_MACID_WMT_TABWE127; addw += 4)
		wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, 0);
}

static void wtw8852a_bb_sethw(stwuct wtw89_dev *wtwdev)
{
	wtw89_phy_wwite32_cww(wtwdev, W_P0_EN_SOUND_WO_NDP, B_P0_EN_SOUND_WO_NDP);
	wtw89_phy_wwite32_cww(wtwdev, W_P1_EN_SOUND_WO_NDP, B_P1_EN_SOUND_WO_NDP);

	if (wtwdev->haw.cv <= CHIP_CCV) {
		wtw89_phy_wwite32_set(wtwdev, W_WSTB_WATCH_DOG, B_P0_WSTB_WATCH_DOG);
		wtw89_phy_wwite32(wtwdev, W_BWK_ASYNC_WST_EN_1, 0x864FA000);
		wtw89_phy_wwite32(wtwdev, W_BWK_ASYNC_WST_EN_2, 0x43F);
		wtw89_phy_wwite32(wtwdev, W_BWK_ASYNC_WST_EN_3, 0x7FFF);
		wtw89_phy_wwite32_set(wtwdev, W_SPOOF_ASYNC_WST, B_SPOOF_ASYNC_WST);
		wtw89_phy_wwite32_set(wtwdev, W_P0_TXPW_WSTB, B_P0_TXPW_WSTB_MANON);
		wtw89_phy_wwite32_set(wtwdev, W_P1_TXPW_WSTB, B_P1_TXPW_WSTB_MANON);
		wtw89_phy_wwite32_set(wtwdev, W_PWCP_HISTOGWAM, B_STS_PAWSING_TIME);
	}
	wtw89_phy_wwite32_mask(wtwdev, W_CFO_TWK0, B_CFO_TWK_MSK, 0x1f);
	wtw89_phy_wwite32_mask(wtwdev, W_CFO_TWK1, B_CFO_TWK_MSK, 0x0c);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0x0, WTW89_PHY_0);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0x0, WTW89_PHY_1);
	wtw89_phy_wwite32_cww(wtwdev, W_NDP_BWK0, B_NDP_WU_BWK);
	wtw89_phy_wwite32_set(wtwdev, W_NDP_BWK1, B_NDP_WU_BWK);

	wtw8852a_bb_macid_ctww_init(wtwdev, WTW89_PHY_0);
}

static void wtw8852a_bbwst_fow_wfk(stwuct wtw89_dev *wtwdev,
				   enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite32_set(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
	wtw89_phy_wwite32_set(wtwdev, W_P1_TSSI_TWK, B_P1_TSSI_TWK_EN);
	wtw8852a_bb_weset_aww(wtwdev, phy_idx);
	wtw89_phy_wwite32_cww(wtwdev, W_P0_TSSI_TWK, B_P0_TSSI_TWK_EN);
	wtw89_phy_wwite32_cww(wtwdev, W_P1_TSSI_TWK, B_P1_TSSI_TWK_EN);
	udeway(1);
}

static void wtw8852a_set_channew_bb(stwuct wtw89_dev *wtwdev,
				    const stwuct wtw89_chan *chan,
				    enum wtw89_phy_idx phy_idx)
{
	boow cck_en = chan->channew <= 14;
	u8 pwi_ch_idx = chan->pwi_ch_idx;

	if (cck_en)
		wtw8852a_ctww_sco_cck(wtwdev, chan->channew,
				      chan->pwimawy_channew,
				      chan->band_width);

	wtw8852a_ctww_ch(wtwdev, chan->channew, phy_idx);
	wtw8852a_ctww_bw(wtwdev, pwi_ch_idx, chan->band_width, phy_idx);
	if (cck_en) {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_WXCCA, B_WXCCA_DIS, 1);
		wtw8852a_bbwst_fow_wfk(wtwdev, phy_idx);
	}
	wtw8852a_spuw_ewimination(wtwdev, chan->channew);
	wtw89_phy_wwite32_mask(wtwdev, W_MAC_PIN_SEW, B_CH_IDX_SEG0,
			       chan->pwimawy_channew);
	wtw8852a_bb_weset_aww(wtwdev, phy_idx);
}

static void wtw8852a_set_channew(stwuct wtw89_dev *wtwdev,
				 const stwuct wtw89_chan *chan,
				 enum wtw89_mac_idx mac_idx,
				 enum wtw89_phy_idx phy_idx)
{
	wtw8852a_set_channew_mac(wtwdev, chan, mac_idx);
	wtw8852a_set_channew_bb(wtwdev, chan, phy_idx);
}

static void wtw8852a_dfs_en(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_P0, B_UPD_P0_EN, 1);
	ewse
		wtw89_phy_wwite32_mask(wtwdev, W_UPD_P0, B_UPD_P0_EN, 0);
}

static void wtw8852a_tssi_cont_en(stwuct wtw89_dev *wtwdev, boow en,
				  enum wtw89_wf_path path)
{
	static const u32 tssi_twk[2] = {0x5818, 0x7818};
	static const u32 ctww_bbwst[2] = {0x58dc, 0x78dc};

	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, ctww_bbwst[path], BIT(30), 0x0);
		wtw89_phy_wwite32_mask(wtwdev, tssi_twk[path], BIT(30), 0x0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, ctww_bbwst[path], BIT(30), 0x1);
		wtw89_phy_wwite32_mask(wtwdev, tssi_twk[path], BIT(30), 0x1);
	}
}

static void wtw8852a_tssi_cont_en_phyidx(stwuct wtw89_dev *wtwdev, boow en,
					 u8 phy_idx)
{
	if (!wtwdev->dbcc_en) {
		wtw8852a_tssi_cont_en(wtwdev, en, WF_PATH_A);
		wtw8852a_tssi_cont_en(wtwdev, en, WF_PATH_B);
	} ewse {
		if (phy_idx == WTW89_PHY_0)
			wtw8852a_tssi_cont_en(wtwdev, en, WF_PATH_A);
		ewse
			wtw8852a_tssi_cont_en(wtwdev, en, WF_PATH_B);
	}
}

static void wtw8852a_adc_en(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST,
				       0x0);
	ewse
		wtw89_phy_wwite32_mask(wtwdev, W_ADC_FIFO, B_ADC_FIFO_WST,
				       0xf);
}

static void wtw8852a_set_channew_hewp(stwuct wtw89_dev *wtwdev, boow entew,
				      stwuct wtw89_channew_hewp_pawams *p,
				      const stwuct wtw89_chan *chan,
				      enum wtw89_mac_idx mac_idx,
				      enum wtw89_phy_idx phy_idx)
{
	if (entew) {
		wtw89_chip_stop_sch_tx(wtwdev, mac_idx, &p->tx_en,
				       WTW89_SCH_TX_SEW_AWW);
		wtw89_mac_cfg_ppdu_status(wtwdev, mac_idx, fawse);
		wtw8852a_dfs_en(wtwdev, fawse);
		wtw8852a_tssi_cont_en_phyidx(wtwdev, fawse, phy_idx);
		wtw8852a_adc_en(wtwdev, fawse);
		fsweep(40);
		wtw8852a_bb_weset_en(wtwdev, phy_idx, fawse);
	} ewse {
		wtw89_mac_cfg_ppdu_status(wtwdev, mac_idx, twue);
		wtw8852a_adc_en(wtwdev, twue);
		wtw8852a_dfs_en(wtwdev, twue);
		wtw8852a_tssi_cont_en_phyidx(wtwdev, twue, phy_idx);
		wtw8852a_bb_weset_en(wtwdev, phy_idx, twue);
		wtw89_chip_wesume_sch_tx(wtwdev, mac_idx, p->tx_en);
	}
}

static void wtw8852a_fem_setup(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_efuse *efuse = &wtwdev->efuse;

	switch (efuse->wfe_type) {
	case 11:
	case 12:
	case 17:
	case 18:
	case 51:
	case 53:
		wtwdev->fem.epa_2g = twue;
		wtwdev->fem.ewna_2g = twue;
		fawwthwough;
	case 9:
	case 10:
	case 15:
	case 16:
		wtwdev->fem.epa_5g = twue;
		wtwdev->fem.ewna_5g = twue;
		bweak;
	defauwt:
		bweak;
	}
}

static void wtw8852a_wfk_init(stwuct wtw89_dev *wtwdev)
{
	wtwdev->is_tssi_mode[WF_PATH_A] = fawse;
	wtwdev->is_tssi_mode[WF_PATH_B] = fawse;

	wtw8852a_wck(wtwdev);
	wtw8852a_dack(wtwdev);
	wtw8852a_wx_dck(wtwdev, WTW89_PHY_0, twue);
}

static void wtw8852a_wfk_channew(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_phy_idx phy_idx = WTW89_PHY_0;

	wtw8852a_wx_dck(wtwdev, phy_idx, twue);
	wtw8852a_iqk(wtwdev, phy_idx);
	wtw8852a_tssi(wtwdev, phy_idx);
	wtw8852a_dpk(wtwdev, phy_idx);
}

static void wtw8852a_wfk_band_changed(stwuct wtw89_dev *wtwdev,
				      enum wtw89_phy_idx phy_idx)
{
	wtw8852a_tssi_scan(wtwdev, phy_idx);
}

static void wtw8852a_wfk_scan(stwuct wtw89_dev *wtwdev, boow stawt)
{
	wtw8852a_wifi_scan_notify(wtwdev, stawt, WTW89_PHY_0);
}

static void wtw8852a_wfk_twack(stwuct wtw89_dev *wtwdev)
{
	wtw8852a_dpk_twack(wtwdev);
	wtw8852a_tssi_twack(wtwdev);
}

static u32 wtw8852a_bb_caw_txpww_wef(stwuct wtw89_dev *wtwdev,
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
void wtw8852a_set_txpww_uw_tb_offset(stwuct wtw89_dev *wtwdev,
				     s8 pw_ofst, enum wtw89_mac_idx mac_idx)
{
	s8 vaw_1t = 0;
	s8 vaw_2t = 0;
	u32 weg;

	if (pw_ofst < -16 || pw_ofst > 15) {
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[UWTB] Eww pww_offset=%d\n",
			    pw_ofst);
		wetuwn;
	}
	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_CTWW, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_AX_PWW_UW_TB_CTWW_EN);
	vaw_1t = pw_ofst;
	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_1T, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_AX_PWW_UW_TB_1T_MASK, vaw_1t);
	vaw_2t = max(vaw_1t - 3, -16);
	weg = wtw89_mac_weg_by_idx(wtwdev, W_AX_PWW_UW_TB_2T, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_AX_PWW_UW_TB_2T_MASK, vaw_2t);
	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[UWTB] Set TB pww_offset=(%d, %d)\n",
		    vaw_1t, vaw_2t);
}

static void wtw8852a_set_txpww_wef(stwuct wtw89_dev *wtwdev,
				   enum wtw89_phy_idx phy_idx)
{
	static const u32 addw[WF_PATH_NUM_8852A] = {0x5800, 0x7800};
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
	vaw = wtw8852a_bb_caw_txpww_wef(wtwdev, phy_idx, wef_ofdm);

	fow (i = 0; i < WF_PATH_NUM_8852A; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_ofdm, mask, vaw,
				      phy_idx);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW, "[TXPWW] set bb cck txpww wef\n");
	vaw = wtw8852a_bb_caw_txpww_wef(wtwdev, phy_idx, wef_cck);

	fow (i = 0; i < WF_PATH_NUM_8852A; i++)
		wtw89_phy_wwite32_idx(wtwdev, addw[i] + ofst_cck, mask, vaw,
				      phy_idx);
}

static void wtw8852a_set_txpww(stwuct wtw89_dev *wtwdev,
			       const stwuct wtw89_chan *chan,
			       enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_set_txpww_bywate(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_offset(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit(wtwdev, chan, phy_idx);
	wtw89_phy_set_txpww_wimit_wu(wtwdev, chan, phy_idx);
}

static void wtw8852a_set_txpww_ctww(stwuct wtw89_dev *wtwdev,
				    enum wtw89_phy_idx phy_idx)
{
	wtw8852a_set_txpww_wef(wtwdev, phy_idx);
}

static int
wtw8852a_init_txpww_unit(stwuct wtw89_dev *wtwdev, enum wtw89_phy_idx phy_idx)
{
	int wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_UW_CTWW2, 0x07763333);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_COEXT_CTWW, 0x01ebf004);
	if (wet)
		wetuwn wet;

	wet = wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_AX_PWW_UW_CTWW0, 0x0002f8ff);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void wtw8852a_bb_set_pwcp_tx(stwuct wtw89_dev *wtwdev)
{
	u8 i = 0;
	u32 addw, vaw;

	fow (i = 0; i < AWWAY_SIZE(wtw8852a_pmac_ht20_mcs7_tbw); i++) {
		addw = wtw8852a_pmac_ht20_mcs7_tbw[i].addw;
		vaw = wtw8852a_pmac_ht20_mcs7_tbw[i].data;
		wtw89_phy_wwite32(wtwdev, addw, vaw);
	}
}

static void wtw8852a_stop_pmac_tx(stwuct wtw89_dev *wtwdev,
				  stwuct wtw8852a_bb_pmac_info *tx_info,
				  enum wtw89_phy_idx idx)
{
	wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC Stop Tx");
	if (tx_info->mode == CONT_TX)
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_PWD, B_PMAC_CTX_EN, 0,
				      idx);
	ewse if (tx_info->mode == PKTS_TX)
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_PWD, B_PMAC_PTX_EN, 0,
				      idx);
}

static void wtw8852a_stawt_pmac_tx(stwuct wtw89_dev *wtwdev,
				   stwuct wtw8852a_bb_pmac_info *tx_info,
				   enum wtw89_phy_idx idx)
{
	enum wtw8852a_pmac_mode mode = tx_info->mode;
	u32 pkt_cnt = tx_info->tx_cnt;
	u16 pewiod = tx_info->pewiod;

	if (mode == CONT_TX && !tx_info->is_cck) {
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_PWD, B_PMAC_CTX_EN, 1,
				      idx);
		wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC CTx Stawt");
	} ewse if (mode == PKTS_TX) {
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_PWD, B_PMAC_PTX_EN, 1,
				      idx);
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_PWD,
				      B_PMAC_TX_PWD_MSK, pewiod, idx);
		wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_CNT, B_PMAC_TX_CNT_MSK,
				      pkt_cnt, idx);
		wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC PTx Stawt");
	}
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_CTWW, B_PMAC_TXEN_DIS, 1, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_TX_CTWW, B_PMAC_TXEN_DIS, 0, idx);
}

void wtw8852a_bb_set_pmac_tx(stwuct wtw89_dev *wtwdev,
			     stwuct wtw8852a_bb_pmac_info *tx_info,
			     enum wtw89_phy_idx idx)
{
	const stwuct wtw89_chan *chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);

	if (!tx_info->en_pmac_tx) {
		wtw8852a_stop_pmac_tx(wtwdev, tx_info, idx);
		wtw89_phy_wwite32_idx(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 0, idx);
		if (chan->band_type == WTW89_BAND_2G)
			wtw89_phy_wwite32_cww(wtwdev, W_WXCCA, B_WXCCA_DIS);
		wetuwn;
	}
	wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC Tx Enabwe");
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_GNT, B_PMAC_GNT_TXEN, 1, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_GNT, B_PMAC_GNT_WXEN, 1, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_WX_CFG1, B_PMAC_OPT1_MSK, 0x3f,
			      idx);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PD_CTWW, B_PD_HIT_DIS, 1, idx);
	wtw89_phy_wwite32_set(wtwdev, W_WXCCA, B_WXCCA_DIS);
	wtw89_phy_wwite32_idx(wtwdev, W_WSTB_ASYNC, B_WSTB_ASYNC_AWW, 1, idx);
	wtw8852a_stawt_pmac_tx(wtwdev, tx_info, idx);
}

void wtw8852a_bb_set_pmac_pkt_tx(stwuct wtw89_dev *wtwdev, u8 enabwe,
				 u16 tx_cnt, u16 pewiod, u16 tx_time,
				 enum wtw89_phy_idx idx)
{
	stwuct wtw8852a_bb_pmac_info tx_info = {0};

	tx_info.en_pmac_tx = enabwe;
	tx_info.is_cck = 0;
	tx_info.mode = PKTS_TX;
	tx_info.tx_cnt = tx_cnt;
	tx_info.pewiod = pewiod;
	tx_info.tx_time = tx_time;
	wtw8852a_bb_set_pmac_tx(wtwdev, &tx_info, idx);
}

void wtw8852a_bb_set_powew(stwuct wtw89_dev *wtwdev, s16 pww_dbm,
			   enum wtw89_phy_idx idx)
{
	wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC CFG Tx PWW = %d", pww_dbm);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_PWW_EN, 1, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_TXPWW, B_TXPWW_MSK, pww_dbm, idx);
}

void wtw8852a_bb_cfg_tx_path(stwuct wtw89_dev *wtwdev, u8 tx_path)
{
	u32 wst_mask0 = 0;
	u32 wst_mask1 = 0;

	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 7, WTW89_PHY_0);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 7, WTW89_PHY_1);
	wtw89_debug(wtwdev, WTW89_DBG_TSSI, "PMAC CFG Tx Path = %d", tx_path);
	if (!wtwdev->dbcc_en) {
		if (tx_path == WF_PATH_A) {
			wtw89_phy_wwite32_mask(wtwdev, W_TXPATH_SEW,
					       B_TXPATH_SEW_MSK, 1);
			wtw89_phy_wwite32_mask(wtwdev, W_TXNSS_MAP,
					       B_TXNSS_MAP_MSK, 0);
		} ewse if (tx_path == WF_PATH_B) {
			wtw89_phy_wwite32_mask(wtwdev, W_TXPATH_SEW,
					       B_TXPATH_SEW_MSK, 2);
			wtw89_phy_wwite32_mask(wtwdev, W_TXNSS_MAP,
					       B_TXNSS_MAP_MSK, 0);
		} ewse if (tx_path == WF_PATH_AB) {
			wtw89_phy_wwite32_mask(wtwdev, W_TXPATH_SEW,
					       B_TXPATH_SEW_MSK, 3);
			wtw89_phy_wwite32_mask(wtwdev, W_TXNSS_MAP,
					       B_TXNSS_MAP_MSK, 4);
		} ewse {
			wtw89_debug(wtwdev, WTW89_DBG_TSSI, "Ewwow Tx Path");
		}
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_TXPATH_SEW, B_TXPATH_SEW_MSK,
				       1);
		wtw89_phy_wwite32_idx(wtwdev, W_TXPATH_SEW, B_TXPATH_SEW_MSK, 2,
				      WTW89_PHY_1);
		wtw89_phy_wwite32_mask(wtwdev, W_TXNSS_MAP, B_TXNSS_MAP_MSK,
				       0);
		wtw89_phy_wwite32_idx(wtwdev, W_TXNSS_MAP, B_TXNSS_MAP_MSK, 4,
				      WTW89_PHY_1);
	}
	wst_mask0 = B_P0_TXPW_WSTB_MANON | B_P0_TXPW_WSTB_TSSI;
	wst_mask1 = B_P1_TXPW_WSTB_MANON | B_P1_TXPW_WSTB_TSSI;
	if (tx_path == WF_PATH_A) {
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_P0_TXPW_WSTB, wst_mask0, 3);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, wst_mask1, 1);
		wtw89_phy_wwite32_mask(wtwdev, W_P1_TXPW_WSTB, wst_mask1, 3);
	}
}

void wtw8852a_bb_tx_mode_switch(stwuct wtw89_dev *wtwdev,
				enum wtw89_phy_idx idx, u8 mode)
{
	if (mode != 0)
		wetuwn;
	wtw89_debug(wtwdev, WTW89_DBG_TSSI, "Tx mode switch");
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_GNT, B_PMAC_GNT_TXEN, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_GNT, B_PMAC_GNT_WXEN, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_WX_CFG1, B_PMAC_OPT1_MSK, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_PMAC_WXMOD, B_PMAC_WXMOD_MSK, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_DPD_EN, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_MOD, 0, idx);
	wtw89_phy_wwite32_idx(wtwdev, W_MAC_SEW, B_MAC_SEW_PWW_EN, 0, idx);
}

static void wtw8852a_ctww_nbtg_bt_tx(stwuct wtw89_dev *wtwdev, boow en,
				     enum wtw89_phy_idx phy_idx)
{
	wtw89_phy_wwite_weg3_tbw(wtwdev, en ? &wtw8852a_btc_pweagc_en_defs_tbw :
						 &wtw8852a_btc_pweagc_dis_defs_tbw);
}

static u8 wtw8852a_get_thewmaw(stwuct wtw89_dev *wtwdev, enum wtw89_wf_path wf_path)
{
	if (wtwdev->is_tssi_mode[wf_path]) {
		u32 addw = 0x1c10 + (wf_path << 13);

		wetuwn (u8)wtw89_phy_wead32_mask(wtwdev, addw, 0x3F000000);
	}

	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x0);
	wtw89_wwite_wf(wtwdev, wf_path, WW_TM, WW_TM_TWI, 0x1);

	fsweep(200);

	wetuwn (u8)wtw89_wead_wf(wtwdev, wf_path, WW_TM, WW_TM_VAW);
}

static void wtw8852a_btc_set_wfe(stwuct wtw89_dev *wtwdev)
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

static
void wtw8852a_set_twx_mask(stwuct wtw89_dev *wtwdev, u8 path, u8 gwoup, u32 vaw)
{
	wtw89_wwite_wf(wtwdev, path, WW_WUTWE, 0xfffff, 0x20000);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWA, 0xfffff, gwoup);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWD0, 0xfffff, vaw);
	wtw89_wwite_wf(wtwdev, path, WW_WUTWE, 0xfffff, 0x0);
}

static void wtw8852a_ctww_btg_bt_wx(stwuct wtw89_dev *wtwdev, boow en,
				    enum wtw89_phy_idx phy_idx)
{
	if (en) {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG, B_PATH0_BTG_SHEN, 0x1);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BTG, B_PATH1_BTG_SHEN, 0x3);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0x0);
	} ewse {
		wtw89_phy_wwite32_mask(wtwdev, W_PATH0_BTG, B_PATH0_BTG_SHEN, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PATH1_BTG, B_PATH1_BTG_SHEN, 0x0);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P1, 0xf);
		wtw89_phy_wwite32_mask(wtwdev, W_PMAC_GNT, B_PMAC_GNT_P2, 0x4);
	}
}

static void wtw8852a_btc_init_cfg(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	stwuct wtw89_btc_moduwe *moduwe = &btc->mdinfo;
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_mac_ax_coex coex_pawams = {
		.pta_mode = WTW89_MAC_AX_COEX_WTK_MODE,
		.diwection = WTW89_MAC_AX_COEX_INNEW,
	};

	/* PTA init  */
	wtw89_mac_coex_init(wtwdev, &coex_pawams);

	/* set WW Tx wesponse = Hi-Pwi */
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_TX_WESP, twue);
	chip->ops->btc_set_ww_pwi(wtwdev, BTC_PWI_MASK_BEACON, twue);

	/* set wf gnt debug off */
	wtw89_wwite_wf(wtwdev, WF_PATH_A, WW_WWSEW, 0xfffff, 0x0);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WWSEW, 0xfffff, 0x0);

	/* set WW Tx thwu in TWX mask tabwe if GNT_WW = 0 && BT_S1 = ss gwoup */
	if (moduwe->ant.type == BTC_ANT_SHAWED) {
		wtw8852a_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_SS_GWOUP, 0x5ff);
		wtw8852a_set_twx_mask(wtwdev,
				      WF_PATH_B, BTC_BT_SS_GWOUP, 0x5ff);
		/* set path-A(S0) Tx/Wx no-mask if GNT_WW=0 && BT_S1=tx gwoup */
		wtw8852a_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_TX_GWOUP, 0x5ff);
	} ewse { /* set WW Tx stb if GNT_WW = 0 && BT_S1 = ss gwoup fow 3-ant */
		wtw8852a_set_twx_mask(wtwdev,
				      WF_PATH_A, BTC_BT_SS_GWOUP, 0x5df);
		wtw8852a_set_twx_mask(wtwdev,
				      WF_PATH_B, BTC_BT_SS_GWOUP, 0x5df);
	}

	/* set PTA bweak tabwe */
	wtw89_wwite32(wtwdev, W_BTC_BWEAK_TABWE, BTC_BWEAK_PAWAM);

	 /* enabwe BT countew 0xda40[16,2] = 2b'11 */
	wtw89_wwite32_set(wtwdev,
			  W_AX_CSW_MODE, B_AX_BT_CNT_WST | B_AX_STATIS_BT_EN);
	btc->cx.ww.status.map.init_ok = twue;
}

static
void wtw8852a_btc_set_ww_pwi(stwuct wtw89_dev *wtwdev, u8 map, boow state)
{
	u32 bitmap = 0;
	u32 weg = 0;

	switch (map) {
	case BTC_PWI_MASK_TX_WESP:
		weg = W_BTC_BT_COEX_MSK_TABWE;
		bitmap = B_BTC_PWI_MASK_TX_WESP_V1;
		bweak;
	case BTC_PWI_MASK_BEACON:
		weg = W_AX_WW_PWI_MSK;
		bitmap = B_AX_PTA_WW_PWI_MASK_BCNQ;
		bweak;
	defauwt:
		wetuwn;
	}

	if (state)
		wtw89_wwite32_set(wtwdev, weg, bitmap);
	ewse
		wtw89_wwite32_cww(wtwdev, weg, bitmap);
}

static inwine u32 __btc_ctww_vaw_aww_time(u32 ctww)
{
	wetuwn FIEWD_GET(GENMASK(15, 0), ctww);
}

static inwine u32 __btc_ctww_wst_aww_time(u32 cuw)
{
	wetuwn cuw & ~B_AX_FOWCE_PWW_BY_WATE_EN;
}

static inwine u32 __btc_ctww_gen_aww_time(u32 cuw, u32 vaw)
{
	u32 hv = cuw & ~B_AX_FOWCE_PWW_BY_WATE_VAWUE_MASK;
	u32 wv = vaw & B_AX_FOWCE_PWW_BY_WATE_VAWUE_MASK;

	wetuwn hv | wv | B_AX_FOWCE_PWW_BY_WATE_EN;
}

static inwine u32 __btc_ctww_vaw_gnt_bt(u32 ctww)
{
	wetuwn FIEWD_GET(GENMASK(31, 16), ctww);
}

static inwine u32 __btc_ctww_wst_gnt_bt(u32 cuw)
{
	wetuwn cuw & ~B_AX_TXAGC_BT_EN;
}

static inwine u32 __btc_ctww_gen_gnt_bt(u32 cuw, u32 vaw)
{
	u32 ov = cuw & ~B_AX_TXAGC_BT_MASK;
	u32 iv = FIEWD_PWEP(B_AX_TXAGC_BT_MASK, vaw);

	wetuwn ov | iv | B_AX_TXAGC_BT_EN;
}

static void
wtw8852a_btc_set_ww_txpww_ctww(stwuct wtw89_dev *wtwdev, u32 txpww_vaw)
{
	const u32 __btc_cw_aww_time = W_AX_PWW_WATE_CTWW;
	const u32 __btc_cw_gnt_bt = W_AX_PWW_COEXT_CTWW;

#define __do_cww(_chk) ((_chk) == GENMASK(15, 0))
#define __handwe(_case)							\
	do {								\
		const u32 _weg = __btc_cw_ ## _case;			\
		u32 _vaw = __btc_ctww_vaw_ ## _case(txpww_vaw);		\
		u32 _cuw, _wwt;						\
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW,			\
			    "btc ctww %s: 0x%x\n", #_case, _vaw);	\
		if (wtw89_mac_txpww_wead32(wtwdev, WTW89_PHY_0, _weg, &_cuw))\
			bweak;						\
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW,			\
			    "btc ctww owi 0x%x: 0x%x\n", _weg, _cuw);	\
		_wwt = __do_cww(_vaw) ?					\
			__btc_ctww_wst_ ## _case(_cuw) :		\
			__btc_ctww_gen_ ## _case(_cuw, _vaw);		\
		wtw89_mac_txpww_wwite32(wtwdev, WTW89_PHY_0, _weg, _wwt);\
		wtw89_debug(wtwdev, WTW89_DBG_TXPWW,			\
			    "btc ctww set 0x%x: 0x%x\n", _weg, _wwt);	\
	} whiwe (0)

	__handwe(aww_time);
	__handwe(gnt_bt);

#undef __handwe
#undef __do_cww
}

static
s8 wtw8852a_btc_get_bt_wssi(stwuct wtw89_dev *wtwdev, s8 vaw)
{
	/* +6 fow compensate offset */
	wetuwn cwamp_t(s8, vaw + 6, -100, 0) + 100;
}

static stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8852a_wf_uw[] = {
	{255, 0, 0, 7}, /* 0 -> owiginaw */
	{255, 2, 0, 7}, /* 1 -> fow BT-connected ACI issue && BTG co-wx */
	{255, 0, 0, 7}, /* 2 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 3- >wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 4 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* the bewow id is fow non-shawed-antenna fwee-wun */
	{6, 1, 0, 7},
	{13, 1, 0, 7},
	{13, 1, 0, 7}
};

static stwuct wtw89_btc_wf_twx_pawa wtw89_btc_8852a_wf_dw[] = {
	{255, 0, 0, 7}, /* 0 -> owiginaw */
	{255, 2, 0, 7}, /* 1 -> wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 2 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 3- >wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* 4 ->wesewved fow shawed-antenna */
	{255, 0, 0, 7}, /* the bewow id is fow non-shawed-antenna fwee-wun */
	{255, 1, 0, 7},
	{255, 1, 0, 7},
	{255, 1, 0, 7}
};

static const
u8 wtw89_btc_8852a_ww_wssi_thwes[BTC_WW_WSSI_THMAX] = {60, 50, 40, 30};
static const
u8 wtw89_btc_8852a_bt_wssi_thwes[BTC_BT_WSSI_THMAX] = {40, 36, 31, 28};

static stwuct wtw89_btc_fbtc_mweg wtw89_btc_8852a_mon_weg[] = {
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
	WTW89_DEF_FBTC_MWEG(WEG_BB, 4, 0x980),
	WTW89_DEF_FBTC_MWEG(WEG_BT_MODEM, 4, 0x178),
};

static
void wtw8852a_btc_update_bt_cnt(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;
	const stwuct wtw89_btc_vew *vew = btc->vew;
	stwuct wtw89_btc_cx *cx = &btc->cx;
	u32 vaw;

	if (vew->fcxbtcwpt != 1)
		wetuwn;

	vaw = wtw89_wead32(wtwdev, W_AX_BT_STAST_HIGH);
	cx->cnt_bt[BTC_BCNT_HIPWI_TX] = FIEWD_GET(B_AX_STATIS_BT_HI_TX_MASK, vaw);
	cx->cnt_bt[BTC_BCNT_HIPWI_WX] = FIEWD_GET(B_AX_STATIS_BT_HI_WX_MASK, vaw);

	vaw = wtw89_wead32(wtwdev, W_AX_BT_STAST_WOW);
	cx->cnt_bt[BTC_BCNT_WOPWI_TX] = FIEWD_GET(B_AX_STATIS_BT_WO_TX_1_MASK, vaw);
	cx->cnt_bt[BTC_BCNT_WOPWI_WX] = FIEWD_GET(B_AX_STATIS_BT_WO_WX_1_MASK, vaw);

	/* cwock-gate off befowe weset countew*/
	wtw89_wwite32_set(wtwdev, W_AX_BTC_CFG, B_AX_DIS_BTC_CWK_G);
	wtw89_wwite32_cww(wtwdev, W_AX_CSW_MODE, B_AX_BT_CNT_WST);
	wtw89_wwite32_set(wtwdev, W_AX_CSW_MODE, B_AX_BT_CNT_WST);
	wtw89_wwite32_cww(wtwdev, W_AX_BTC_CFG, B_AX_DIS_BTC_CWK_G);
}

static
void wtw8852a_btc_ww_s1_standby(stwuct wtw89_dev *wtwdev, boow state)
{
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x80000);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x1);
	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD1, WFWEG_MASK, 0x1);

	/* set WW standby = Wx fow GNT_BT_Tx = 1->0 settwe issue */
	if (state)
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0,
			       WFWEG_MASK, 0xa2d7c);
	ewse
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0,
			       WFWEG_MASK, 0xa2020);

	wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
}

static void wtw8852a_set_ww_wna2(stwuct wtw89_dev *wtwdev, u8 wevew)
{
	/* wevew=0 Defauwt:    TIA 1/0= (WNA2,TIAN6) = (7,1)/(5,1) = 21dB/12dB
	 * wevew=1 Fix WNA2=5: TIA 1/0= (WNA2,TIAN6) = (5,0)/(5,1) = 18dB/12dB
	 * To impwove BT ACI in co-wx
	 */

	switch (wevew) {
	case 0: /* defauwt */
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x1000);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x3);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x17);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x2);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
		bweak;
	case 1: /* Fix WNA2=5  */
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x1000);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x3);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x5);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWA, WFWEG_MASK, 0x2);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWD0, WFWEG_MASK, 0x15);
		wtw89_wwite_wf(wtwdev, WF_PATH_B, WW_WUTWE, WFWEG_MASK, 0x0);
		bweak;
	}
}

static void wtw8852a_btc_set_ww_wx_gain(stwuct wtw89_dev *wtwdev, u32 wevew)
{
	stwuct wtw89_btc *btc = &wtwdev->btc;

	switch (wevew) {
	case 0: /* owiginaw */
	defauwt:
		wtw8852a_ctww_nbtg_bt_tx(wtwdev, fawse, WTW89_PHY_0);
		btc->dm.ww_wna2 = 0;
		bweak;
	case 1: /* fow FDD fwee-wun */
		wtw8852a_ctww_nbtg_bt_tx(wtwdev, twue, WTW89_PHY_0);
		btc->dm.ww_wna2 = 0;
		bweak;
	case 2: /* fow BTG Co-Wx*/
		wtw8852a_ctww_nbtg_bt_tx(wtwdev, fawse, WTW89_PHY_0);
		btc->dm.ww_wna2 = 1;
		bweak;
	}

	wtw8852a_set_ww_wna2(wtwdev, btc->dm.ww_wna2);
}

static void wtw8852a_fiww_fweq_with_ppdu(stwuct wtw89_dev *wtwdev,
					 stwuct wtw89_wx_phy_ppdu *phy_ppdu,
					 stwuct ieee80211_wx_status *status)
{
	u16 chan = phy_ppdu->chan_idx;
	u8 band;

	if (chan == 0)
		wetuwn;

	band = chan <= 14 ? NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
	status->fweq = ieee80211_channew_to_fwequency(chan, band);
	status->band = band;
}

static void wtw8852a_quewy_ppdu(stwuct wtw89_dev *wtwdev,
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
		wtw8852a_fiww_fweq_with_ppdu(wtwdev, phy_ppdu, status);
}

#ifdef CONFIG_PM
static const stwuct wiphy_wowwan_suppowt wtw_wowwan_stub_8852a = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT,
	.n_pattewns = WTW89_MAX_PATTEWN_NUM,
	.pattewn_max_wen = WTW89_MAX_PATTEWN_SIZE,
	.pattewn_min_wen = 1,
};
#endif

static const stwuct wtw89_chip_ops wtw8852a_chip_ops = {
	.enabwe_bb_wf		= wtw89_mac_enabwe_bb_wf,
	.disabwe_bb_wf		= wtw89_mac_disabwe_bb_wf,
	.bb_pweinit		= NUWW,
	.bb_weset		= wtw8852a_bb_weset,
	.bb_sethw		= wtw8852a_bb_sethw,
	.wead_wf		= wtw89_phy_wead_wf,
	.wwite_wf		= wtw89_phy_wwite_wf,
	.set_channew		= wtw8852a_set_channew,
	.set_channew_hewp	= wtw8852a_set_channew_hewp,
	.wead_efuse		= wtw8852a_wead_efuse,
	.wead_phycap		= wtw8852a_wead_phycap,
	.fem_setup		= wtw8852a_fem_setup,
	.wfe_gpio		= NUWW,
	.wfk_init		= wtw8852a_wfk_init,
	.wfk_channew		= wtw8852a_wfk_channew,
	.wfk_band_changed	= wtw8852a_wfk_band_changed,
	.wfk_scan		= wtw8852a_wfk_scan,
	.wfk_twack		= wtw8852a_wfk_twack,
	.powew_twim		= wtw8852a_powew_twim,
	.set_txpww		= wtw8852a_set_txpww,
	.set_txpww_ctww		= wtw8852a_set_txpww_ctww,
	.init_txpww_unit	= wtw8852a_init_txpww_unit,
	.get_thewmaw		= wtw8852a_get_thewmaw,
	.ctww_btg_bt_wx		= wtw8852a_ctww_btg_bt_wx,
	.quewy_ppdu		= wtw8852a_quewy_ppdu,
	.ctww_nbtg_bt_tx	= wtw8852a_ctww_nbtg_bt_tx,
	.cfg_txwx_path		= NUWW,
	.set_txpww_uw_tb_offset	= wtw8852a_set_txpww_uw_tb_offset,
	.pww_on_func		= NUWW,
	.pww_off_func		= NUWW,
	.quewy_wxdesc		= wtw89_cowe_quewy_wxdesc,
	.fiww_txdesc		= wtw89_cowe_fiww_txdesc,
	.fiww_txdesc_fwcmd	= wtw89_cowe_fiww_txdesc,
	.cfg_ctww_path		= wtw89_mac_cfg_ctww_path,
	.mac_cfg_gnt		= wtw89_mac_cfg_gnt,
	.stop_sch_tx		= wtw89_mac_stop_sch_tx,
	.wesume_sch_tx		= wtw89_mac_wesume_sch_tx,
	.h2c_dctw_sec_cam	= NUWW,

	.btc_set_wfe		= wtw8852a_btc_set_wfe,
	.btc_init_cfg		= wtw8852a_btc_init_cfg,
	.btc_set_ww_pwi		= wtw8852a_btc_set_ww_pwi,
	.btc_set_ww_txpww_ctww	= wtw8852a_btc_set_ww_txpww_ctww,
	.btc_get_bt_wssi	= wtw8852a_btc_get_bt_wssi,
	.btc_update_bt_cnt	= wtw8852a_btc_update_bt_cnt,
	.btc_ww_s1_standby	= wtw8852a_btc_ww_s1_standby,
	.btc_set_ww_wx_gain	= wtw8852a_btc_set_ww_wx_gain,
	.btc_set_powicy		= wtw89_btc_set_powicy,
};

const stwuct wtw89_chip_info wtw8852a_chip_info = {
	.chip_id		= WTW8852A,
	.chip_gen		= WTW89_CHIP_AX,
	.ops			= &wtw8852a_chip_ops,
	.mac_def		= &wtw89_mac_gen_ax,
	.phy_def		= &wtw89_phy_gen_ax,
	.fw_basename		= WTW8852A_FW_BASENAME,
	.fw_fowmat_max		= WTW8852A_FW_FOWMAT_MAX,
	.twy_ce_fw		= fawse,
	.bbmcu_nw		= 0,
	.needed_fw_ewms		= 0,
	.fifo_size		= 458752,
	.smaww_fifo_size	= fawse,
	.dwe_scc_wsvd_size	= 0,
	.max_amsdu_wimit	= 3500,
	.dis_2g_40m_uw_ofdma	= twue,
	.wsvd_pwe_ofst		= 0x6f800,
	.hfc_pawam_ini		= wtw8852a_hfc_pawam_ini_pcie,
	.dwe_mem		= wtw8852a_dwe_mem_pcie,
	.wde_qempty_acq_gwpnum	= 16,
	.wde_qempty_mgq_gwpsew	= 16,
	.wf_base_addw		= {0xc000, 0xd000},
	.pww_on_seq		= pww_on_seq_8852a,
	.pww_off_seq		= pww_off_seq_8852a,
	.bb_tabwe		= &wtw89_8852a_phy_bb_tabwe,
	.bb_gain_tabwe		= NUWW,
	.wf_tabwe		= {&wtw89_8852a_phy_wadioa_tabwe,
				   &wtw89_8852a_phy_wadiob_tabwe,},
	.nctw_tabwe		= &wtw89_8852a_phy_nctw_tabwe,
	.nctw_post_tabwe	= NUWW,
	.dfwt_pawms		= &wtw89_8852a_dfwt_pawms,
	.wfe_pawms_conf		= NUWW,
	.txpww_factow_wf	= 2,
	.txpww_factow_mac	= 1,
	.dig_tabwe		= &wtw89_8852a_phy_dig_tabwe,
	.dig_wegs		= &wtw8852a_dig_wegs,
	.tssi_dbw_tabwe		= NUWW,
	.suppowt_chanctx_num	= 1,
	.suppowt_bands		= BIT(NW80211_BAND_2GHZ) |
				  BIT(NW80211_BAND_5GHZ),
	.suppowt_bw160		= fawse,
	.suppowt_unii4		= fawse,
	.uw_tb_wavefowm_ctww	= fawse,
	.uw_tb_pww_diff		= fawse,
	.hw_sec_hdw		= fawse,
	.wf_path_num		= 2,
	.tx_nss			= 2,
	.wx_nss			= 2,
	.acam_num		= 128,
	.bcam_num		= 10,
	.scam_num		= 128,
	.bacam_num		= 2,
	.bacam_dynamic_num	= 4,
	.bacam_vew		= WTW89_BACAM_V0,
	.ppdu_max_usw		= 4,
	.sec_ctww_efuse_size	= 4,
	.physicaw_efuse_size	= 1216,
	.wogicaw_efuse_size	= 1536,
	.wimit_efuse_size	= 1152,
	.dav_phy_efuse_size	= 0,
	.dav_wog_efuse_size	= 0,
	.efuse_bwocks		= NUWW,
	.phycap_addw		= 0x580,
	.phycap_size		= 128,
	.pawa_vew		= 0x0,
	.wwcx_desiwed		= 0x06000000,
	.btcx_desiwed		= 0x7,
	.scbd			= 0x1,
	.maiwbox		= 0x1,

	.afh_guawd_ch		= 6,
	.ww_wssi_thwes		= wtw89_btc_8852a_ww_wssi_thwes,
	.bt_wssi_thwes		= wtw89_btc_8852a_bt_wssi_thwes,
	.wssi_tow		= 2,
	.mon_weg_num		= AWWAY_SIZE(wtw89_btc_8852a_mon_weg),
	.mon_weg		= wtw89_btc_8852a_mon_weg,
	.wf_pawa_uwink_num	= AWWAY_SIZE(wtw89_btc_8852a_wf_uw),
	.wf_pawa_uwink		= wtw89_btc_8852a_wf_uw,
	.wf_pawa_dwink_num	= AWWAY_SIZE(wtw89_btc_8852a_wf_dw),
	.wf_pawa_dwink		= wtw89_btc_8852a_wf_dw,
	.ps_mode_suppowted	= BIT(WTW89_PS_MODE_WFOFF) |
				  BIT(WTW89_PS_MODE_CWK_GATED) |
				  BIT(WTW89_PS_MODE_PWW_GATED),
	.wow_powew_hci_modes	= 0,
	.h2c_cctw_func_id	= H2C_FUNC_MAC_CCTWINFO_UD,
	.hci_func_en_addw	= W_AX_HCI_FUNC_EN,
	.h2c_desc_size		= sizeof(stwuct wtw89_txwd_body),
	.txwd_body_size		= sizeof(stwuct wtw89_txwd_body),
	.txwd_info_size		= sizeof(stwuct wtw89_txwd_info),
	.h2c_ctww_weg		= W_AX_H2CWEG_CTWW,
	.h2c_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_H2C_DEQ_CNT_MASK >> 8},
	.h2c_wegs		= wtw8852a_h2c_wegs,
	.c2h_ctww_weg		= W_AX_C2HWEG_CTWW,
	.c2h_wegs		= wtw8852a_c2h_wegs,
	.c2h_countew_weg	= {W_AX_UDM1 + 1, B_AX_UDM1_HAWMAC_C2H_ENQ_CNT_MASK >> 8},
	.page_wegs		= &wtw8852a_page_wegs,
	.cfo_swc_fd		= fawse,
	.cfo_hw_comp            = fawse,
	.dcfo_comp		= &wtw8852a_dcfo_comp,
	.dcfo_comp_sft		= 10,
	.imw_info		= &wtw8852a_imw_info,
	.imw_dmac_tabwe		= NUWW,
	.imw_cmac_tabwe		= NUWW,
	.wwsw_cfgs		= &wtw8852a_wwsw_cfgs,
	.bss_cww_vwd		= {W_BSS_CWW_MAP, B_BSS_CWW_MAP_VWD0},
	.bss_cww_map_weg	= W_BSS_CWW_MAP,
	.dma_ch_mask		= 0,
	.edcca_wegs		= &wtw8852a_edcca_wegs,
#ifdef CONFIG_PM
	.wowwan_stub		= &wtw_wowwan_stub_8852a,
#endif
	.xtaw_info		= &wtw8852a_xtaw_info,
};
EXPOWT_SYMBOW(wtw8852a_chip_info);

MODUWE_FIWMWAWE(WTW8852A_MODUWE_FIWMWAWE);
MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ax wiwewess 8852A dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
