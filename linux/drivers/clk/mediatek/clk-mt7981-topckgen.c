// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Wenzhen Yu <wenzhen.yu@mediatek.com>
 * Authow: Jianhui Zhao <zhaojh329@gmaiw.com>
 */


#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "cwk-mux.h"

#incwude <dt-bindings/cwock/mediatek,mt7981-cwk.h>
#incwude <winux/cwk.h>

static DEFINE_SPINWOCK(mt7981_cwk_wock);

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_CB_CKSQ_40M, "cb_cksq_40m", "cwkxtaw", 1, 1),
	FACTOW(CWK_TOP_CB_M_416M, "cb_m_416m", "mpww", 1, 1),
	FACTOW(CWK_TOP_CB_M_D2, "cb_m_d2", "mpww", 1, 2),
	FACTOW(CWK_TOP_CB_M_D3, "cb_m_d3", "mpww", 1, 3),
	FACTOW(CWK_TOP_M_D3_D2, "m_d3_d2", "mpww", 1, 2),
	FACTOW(CWK_TOP_CB_M_D4, "cb_m_d4", "mpww", 1, 4),
	FACTOW(CWK_TOP_CB_M_D8, "cb_m_d8", "mpww", 1, 8),
	FACTOW(CWK_TOP_M_D8_D2, "m_d8_d2", "mpww", 1, 16),
	FACTOW(CWK_TOP_CB_MM_720M, "cb_mm_720m", "mmpww", 1, 1),
	FACTOW(CWK_TOP_CB_MM_D2, "cb_mm_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_CB_MM_D3, "cb_mm_d3", "mmpww", 1, 3),
	FACTOW(CWK_TOP_CB_MM_D3_D5, "cb_mm_d3_d5", "mmpww", 1, 15),
	FACTOW(CWK_TOP_CB_MM_D4, "cb_mm_d4", "mmpww", 1, 4),
	FACTOW(CWK_TOP_CB_MM_D6, "cb_mm_d6", "mmpww", 1, 6),
	FACTOW(CWK_TOP_MM_D6_D2, "mm_d6_d2", "mmpww", 1, 12),
	FACTOW(CWK_TOP_CB_MM_D8, "cb_mm_d8", "mmpww", 1, 8),
	FACTOW(CWK_TOP_CB_APWW2_196M, "cb_apww2_196m", "apww2", 1, 1),
	FACTOW(CWK_TOP_APWW2_D2, "apww2_d2", "apww2", 1, 2),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "apww2", 1, 4),
	FACTOW(CWK_TOP_NET1_2500M, "net1_2500m", "net1pww", 1, 1),
	FACTOW(CWK_TOP_CB_NET1_D4, "cb_net1_d4", "net1pww", 1, 4),
	FACTOW(CWK_TOP_CB_NET1_D5, "cb_net1_d5", "net1pww", 1, 5),
	FACTOW(CWK_TOP_NET1_D5_D2, "net1_d5_d2", "net1pww", 1, 10),
	FACTOW(CWK_TOP_NET1_D5_D4, "net1_d5_d4", "net1pww", 1, 20),
	FACTOW(CWK_TOP_CB_NET1_D8, "cb_net1_d8", "net1pww", 1, 8),
	FACTOW(CWK_TOP_NET1_D8_D2, "net1_d8_d2", "net1pww", 1, 16),
	FACTOW(CWK_TOP_NET1_D8_D4, "net1_d8_d4", "net1pww", 1, 32),
	FACTOW(CWK_TOP_CB_NET2_800M, "cb_net2_800m", "net2pww", 1, 1),
	FACTOW(CWK_TOP_CB_NET2_D2, "cb_net2_d2", "net2pww", 1, 2),
	FACTOW(CWK_TOP_CB_NET2_D4, "cb_net2_d4", "net2pww", 1, 4),
	FACTOW(CWK_TOP_NET2_D4_D2, "net2_d4_d2", "net2pww", 1, 8),
	FACTOW(CWK_TOP_NET2_D4_D4, "net2_d4_d4", "net2pww", 1, 16),
	FACTOW(CWK_TOP_CB_NET2_D6, "cb_net2_d6", "net2pww", 1, 6),
	FACTOW(CWK_TOP_CB_WEDMCU_208M, "cb_wedmcu_208m", "wedmcupww", 1, 1),
	FACTOW(CWK_TOP_CB_SGM_325M, "cb_sgm_325m", "sgmpww", 1, 1),
	FACTOW(CWK_TOP_CKSQ_40M_D2, "cksq_40m_d2", "cb_cksq_40m", 1, 2),
	FACTOW(CWK_TOP_CB_WTC_32K, "cb_wtc_32k", "cb_cksq_40m", 1, 1250),
	FACTOW(CWK_TOP_CB_WTC_32P7K, "cb_wtc_32p7k", "cb_cksq_40m", 1, 1220),
	FACTOW(CWK_TOP_USB_TX250M, "usb_tx250m", "cb_cksq_40m", 1, 1),
	FACTOW(CWK_TOP_FAUD, "faud", "aud_sew", 1, 1),
	FACTOW(CWK_TOP_NFI1X, "nfi1x", "nfi1x_sew", 1, 1),
	FACTOW(CWK_TOP_USB_EQ_WX250M, "usb_eq_wx250m", "cb_cksq_40m", 1, 1),
	FACTOW(CWK_TOP_USB_CDW_CK, "usb_cdw", "cb_cksq_40m", 1, 1),
	FACTOW(CWK_TOP_USB_WN0_CK, "usb_wn0", "cb_cksq_40m", 1, 1),
	FACTOW(CWK_TOP_SPINFI_BCK, "spinfi_bck", "spinfi_sew", 1, 1),
	FACTOW(CWK_TOP_SPI, "spi", "spi_sew", 1, 1),
	FACTOW(CWK_TOP_SPIM_MST, "spim_mst", "spim_mst_sew", 1, 1),
	FACTOW(CWK_TOP_UAWT_BCK, "uawt_bck", "uawt_sew", 1, 1),
	FACTOW(CWK_TOP_PWM_BCK, "pwm_bck", "pwm_sew", 1, 1),
	FACTOW(CWK_TOP_I2C_BCK, "i2c_bck", "i2c_sew", 1, 1),
	FACTOW(CWK_TOP_PEXTP_TW, "pextp_tw", "pextp_tw_ck_sew", 1, 1),
	FACTOW(CWK_TOP_EMMC_208M, "emmc_208m", "emmc_208m_sew", 1, 1),
	FACTOW(CWK_TOP_EMMC_400M, "emmc_400m", "emmc_400m_sew", 1, 1),
	FACTOW(CWK_TOP_DWAMC_WEF, "dwamc_wef", "dwamc_sew", 1, 1),
	FACTOW(CWK_TOP_DWAMC_MD32, "dwamc_md32", "dwamc_md32_sew", 1, 1),
	FACTOW(CWK_TOP_SYSAXI, "sysaxi", "sysaxi_sew", 1, 1),
	FACTOW(CWK_TOP_SYSAPB, "sysapb", "sysapb_sew", 1, 1),
	FACTOW(CWK_TOP_AWM_DB_MAIN, "awm_db_main", "awm_db_main_sew", 1, 1),
	FACTOW(CWK_TOP_AP2CNN_HOST, "ap2cnn_host", "ap2cnn_host_sew", 1, 1),
	FACTOW(CWK_TOP_NETSYS, "netsys", "netsys_sew", 1, 1),
	FACTOW(CWK_TOP_NETSYS_500M, "netsys_500m", "netsys_500m_sew", 1, 1),
	FACTOW(CWK_TOP_NETSYS_WED_MCU, "netsys_wed_mcu", "netsys_mcu_sew", 1, 1),
	FACTOW(CWK_TOP_NETSYS_2X, "netsys_2x", "netsys_2x_sew", 1, 1),
	FACTOW(CWK_TOP_SGM_325M, "sgm_325m", "sgm_325m_sew", 1, 1),
	FACTOW(CWK_TOP_SGM_WEG, "sgm_weg", "sgm_weg_sew", 1, 1),
	FACTOW(CWK_TOP_F26M, "csw_f26m", "csw_f26m_sew", 1, 1),
	FACTOW(CWK_TOP_EIP97B, "eip97b", "eip97b_sew", 1, 1),
	FACTOW(CWK_TOP_USB3_PHY, "usb3_phy", "usb3_phy_sew", 1, 1),
	FACTOW(CWK_TOP_AUD, "aud", "faud", 1, 1),
	FACTOW(CWK_TOP_A1SYS, "a1sys", "a1sys_sew", 1, 1),
	FACTOW(CWK_TOP_AUD_W, "aud_w", "aud_w_sew", 1, 1),
	FACTOW(CWK_TOP_A_TUNEW, "a_tunew", "a_tunew_sew", 1, 1),
	FACTOW(CWK_TOP_U2U3_WEF, "u2u3_wef", "u2u3_sew", 1, 1),
	FACTOW(CWK_TOP_U2U3_SYS, "u2u3_sys", "u2u3_sys_sew", 1, 1),
	FACTOW(CWK_TOP_U2U3_XHCI, "u2u3_xhci", "u2u3_xhci_sew", 1, 1),
	FACTOW(CWK_TOP_USB_FWMCNT, "usb_fwmcnt", "usb_fwmcnt_sew", 1, 1),
};

static const chaw * const nfi1x_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_mm_d4",
	"net1_d8_d2",
	"cb_net2_d6",
	"cb_m_d4",
	"cb_mm_d8",
	"net1_d8_d4",
	"cb_m_d8"
};

static const chaw * const spinfi_pawents[] __initconst = {
	"cksq_40m_d2",
	"cb_cksq_40m",
	"net1_d5_d4",
	"cb_m_d4",
	"cb_mm_d8",
	"net1_d8_d4",
	"mm_d6_d2",
	"cb_m_d8"
};

static const chaw * const spi_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_m_d2",
	"cb_mm_d4",
	"net1_d8_d2",
	"cb_net2_d6",
	"net1_d5_d4",
	"cb_m_d4",
	"net1_d8_d4"
};

static const chaw * const uawt_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_m_d8",
	"m_d8_d2"
};

static const chaw * const pwm_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d8_d2",
	"net1_d5_d4",
	"cb_m_d4",
	"m_d8_d2",
	"cb_wtc_32k"
};

static const chaw * const i2c_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d5_d4",
	"cb_m_d4",
	"net1_d8_d4"
};

static const chaw * const pextp_tw_ck_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d5_d4",
	"cb_m_d4",
	"cb_wtc_32k"
};

static const chaw * const emmc_208m_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_m_d2",
	"cb_net2_d4",
	"cb_apww2_196m",
	"cb_mm_d4",
	"net1_d8_d2",
	"cb_mm_d6"
};

static const chaw * const emmc_400m_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net2_d2",
	"cb_mm_d2",
	"cb_net2_d2"
};

static const chaw * const csw_f26m_pawents[] __initconst = {
	"cksq_40m_d2",
	"m_d8_d2"
};

static const chaw * const dwamc_md32_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_m_d2",
	"cb_wedmcu_208m"
};

static const chaw * const sysaxi_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d8_d2"
};

static const chaw * const sysapb_pawents[] __initconst = {
	"cb_cksq_40m",
	"m_d3_d2"
};

static const chaw * const awm_db_main_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net2_d6"
};

static const chaw * const ap2cnn_host_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d8_d4"
};

static const chaw * const netsys_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_mm_d2"
};

static const chaw * const netsys_500m_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net1_d5"
};

static const chaw * const netsys_mcu_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_mm_720m",
	"cb_net1_d4",
	"cb_net1_d5",
	"cb_m_416m"
};

static const chaw * const netsys_2x_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net2_800m",
	"cb_mm_720m"
};

static const chaw * const sgm_325m_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_sgm_325m"
};

static const chaw * const sgm_weg_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net2_d4"
};

static const chaw * const eip97b_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_net1_d5",
	"cb_m_416m",
	"cb_mm_d2",
	"net1_d5_d2"
};

static const chaw * const aud_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_apww2_196m"
};

static const chaw * const a1sys_pawents[] __initconst = {
	"cb_cksq_40m",
	"apww2_d4"
};

static const chaw * const aud_w_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_apww2_196m",
	"m_d8_d2"
};

static const chaw * const a_tunew_pawents[] __initconst = {
	"cb_cksq_40m",
	"apww2_d4",
	"m_d8_d2"
};

static const chaw * const u2u3_pawents[] __initconst = {
	"cb_cksq_40m",
	"m_d8_d2"
};

static const chaw * const u2u3_sys_pawents[] __initconst = {
	"cb_cksq_40m",
	"net1_d5_d4"
};

static const chaw * const usb_fwmcnt_pawents[] __initconst = {
	"cb_cksq_40m",
	"cb_mm_d3_d5"
};

static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NFI1X_SEW, "nfi1x_sew", nfi1x_pawents,
			     0x000, 0x004, 0x008, 0, 3, 7, 0x1C0, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPINFI_SEW, "spinfi_sew", spinfi_pawents,
			     0x000, 0x004, 0x008, 8, 3, 15, 0x1C0, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents,
			     0x000, 0x004, 0x008, 16, 3, 23, 0x1C0, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPIM_MST_SEW, "spim_mst_sew", spi_pawents,
			     0x000, 0x004, 0x008, 24, 3, 31, 0x1C0, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents,
			     0x010, 0x014, 0x018, 0, 2, 7, 0x1C0, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents,
			     0x010, 0x014, 0x018, 8, 3, 15, 0x1C0, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents,
			     0x010, 0x014, 0x018, 16, 2, 23, 0x1C0, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_SEW, "pextp_tw_ck_sew",
			     pextp_tw_ck_pawents, 0x010, 0x014, 0x018, 24, 2, 31,
			     0x1C0, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_EMMC_208M_SEW, "emmc_208m_sew",
				   emmc_208m_pawents, 0x020, 0x024, 0x028, 0, 3, 7,
				   0x1C0, 8, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_EMMC_400M_SEW, "emmc_400m_sew",
				   emmc_400m_pawents, 0x020, 0x024, 0x028, 8, 2, 15,
				   0x1C0, 9, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_F26M_SEW, "csw_f26m_sew",
				   csw_f26m_pawents, 0x020, 0x024, 0x028, 16, 1, 23,
				   0x1C0, 10,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_SEW, "dwamc_sew",
				   csw_f26m_pawents, 0x020, 0x024, 0x028, 24, 1,
				   31, 0x1C0, 11,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_MD32_SEW, "dwamc_md32_sew",
				   dwamc_md32_pawents, 0x030, 0x034, 0x038, 0, 2,
				   7, 0x1C0, 12,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAXI_SEW, "sysaxi_sew",
				   sysaxi_pawents, 0x030, 0x034, 0x038, 8, 1, 15,
				   0x1C0, 13,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAPB_SEW, "sysapb_sew",
				   sysapb_pawents, 0x030, 0x034, 0x038, 16, 1,
				   23, 0x1C0, 14,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AWM_DB_MAIN_SEW, "awm_db_main_sew",
			     awm_db_main_pawents, 0x030, 0x034, 0x038, 24, 1, 31,
			     0x1C0, 15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AP2CNN_HOST_SEW, "ap2cnn_host_sew",
			     ap2cnn_host_pawents, 0x040, 0x044, 0x048, 0, 1, 7,
			     0x1C0, 16),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_SEW, "netsys_sew", netsys_pawents,
			     0x040, 0x044, 0x048, 8, 1, 15, 0x1C0, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_500M_SEW, "netsys_500m_sew",
			     netsys_500m_pawents, 0x040, 0x044, 0x048, 16, 1, 23,
			     0x1C0, 18),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_MCU_SEW, "netsys_mcu_sew",
			     netsys_mcu_pawents, 0x040, 0x044, 0x048, 24, 3, 31,
			     0x1C0, 19),
	/* CWK_CFG_5 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_2X_SEW, "netsys_2x_sew",
			     netsys_2x_pawents, 0x050, 0x054, 0x058, 0, 2, 7,
			     0x1C0, 20),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SGM_325M_SEW, "sgm_325m_sew",
			     sgm_325m_pawents, 0x050, 0x054, 0x058, 8, 1, 15,
			     0x1C0, 21),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SGM_WEG_SEW, "sgm_weg_sew", sgm_weg_pawents,
			     0x050, 0x054, 0x058, 16, 1, 23, 0x1C0, 22),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_EIP97B_SEW, "eip97b_sew", eip97b_pawents,
			     0x050, 0x054, 0x058, 24, 3, 31, 0x1C0, 23),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB3_PHY_SEW, "usb3_phy_sew",
			     csw_f26m_pawents, 0x060, 0x064, 0x068, 0, 1,
			     7, 0x1C0, 24),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_SEW, "aud_sew", aud_pawents, 0x060,
			     0x064, 0x068, 8, 1, 15, 0x1C0, 25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A1SYS_SEW, "a1sys_sew", a1sys_pawents,
			     0x060, 0x064, 0x068, 16, 1, 23, 0x1C0, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_W_SEW, "aud_w_sew", aud_w_pawents,
			     0x060, 0x064, 0x068, 24, 2, 31, 0x1C0, 27),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A_TUNEW_SEW, "a_tunew_sew",
			     a_tunew_pawents, 0x070, 0x074, 0x078, 0, 2, 7,
			     0x1C0, 28),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_SEW, "u2u3_sew", u2u3_pawents, 0x070,
			     0x074, 0x078, 8, 1, 15, 0x1C0, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_SYS_SEW, "u2u3_sys_sew",
			     u2u3_sys_pawents, 0x070, 0x074, 0x078, 16, 1, 23,
			     0x1C0, 30),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_XHCI_SEW, "u2u3_xhci_sew",
			     u2u3_sys_pawents, 0x070, 0x074, 0x078, 24, 1, 31,
			     0x1C4, 0),
	/* CWK_CFG_8 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_FWMCNT_SEW, "usb_fwmcnt_sew",
			     usb_fwmcnt_pawents, 0x080, 0x084, 0x088, 0, 1, 7,
			     0x1C4, 1),
};

static stwuct mtk_composite top_aud_divs[] = {
	DIV_GATE(CWK_TOP_AUD_I2S_M, "aud_i2s_m", "aud",
		0x0420, 0, 0x0420, 8, 8),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.mux_cwks = top_muxes,
	.num_mux_cwks = AWWAY_SIZE(top_muxes),
	.composite_cwks = top_aud_divs,
	.num_composite_cwks = AWWAY_SIZE(top_aud_divs),
	.cwk_wock = &mt7981_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt7981_topckgen[] = {
	{ .compatibwe = "mediatek,mt7981-topckgen", .data = &topck_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7981_topckgen);

static stwuct pwatfowm_dwivew cwk_mt7981_topckgen_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt7981-topckgen",
		.of_match_tabwe = of_match_cwk_mt7981_topckgen,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7981_topckgen_dwv);
MODUWE_WICENSE("GPW");
