// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Wenzhen Yu <wenzhen.yu@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "cwk-mux.h"

#incwude <dt-bindings/cwock/mt7986-cwk.h>
#incwude <winux/cwk.h>

static DEFINE_SPINWOCK(mt7986_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_XTAW, "top_xtaw", "cwkxtaw", 40000000),
	FIXED_CWK(CWK_TOP_JTAG, "top_jtag", "cwkxtaw", 50000000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	/* XTAW */
	FACTOW(CWK_TOP_XTAW_D2, "top_xtaw_d2", "top_xtaw", 1, 2),
	FACTOW(CWK_TOP_WTC_32K, "top_wtc_32k", "top_xtaw", 1, 1250),
	FACTOW(CWK_TOP_WTC_32P7K, "top_wtc_32p7k", "top_xtaw", 1, 1220),
	/* MPWW */
	FACTOW(CWK_TOP_MPWW_D2, "top_mpww_d2", "mpww", 1, 2),
	FACTOW(CWK_TOP_MPWW_D4, "top_mpww_d4", "mpww", 1, 4),
	FACTOW(CWK_TOP_MPWW_D8, "top_mpww_d8", "mpww", 1, 8),
	FACTOW(CWK_TOP_MPWW_D8_D2, "top_mpww_d8_d2", "mpww", 1, 16),
	FACTOW(CWK_TOP_MPWW_D3_D2, "top_mpww_d3_d2", "mpww", 1, 6),
	/* MMPWW */
	FACTOW(CWK_TOP_MMPWW_D2, "top_mmpww_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D4, "top_mmpww_d4", "mmpww", 1, 4),
	FACTOW(CWK_TOP_MMPWW_D8, "top_mmpww_d8", "mmpww", 1, 8),
	FACTOW(CWK_TOP_MMPWW_D8_D2, "top_mmpww_d8_d2", "mmpww", 1, 16),
	FACTOW(CWK_TOP_MMPWW_D3_D8, "top_mmpww_d3_d8", "mmpww", 1, 24),
	FACTOW(CWK_TOP_MMPWW_U2PHY, "top_mmpww_u2phy", "mmpww", 1, 30),
	/* APWW2 */
	FACTOW(CWK_TOP_APWW2_D4, "top_apww2_d4", "apww2", 1, 4),
	/* NET1PWW */
	FACTOW(CWK_TOP_NET1PWW_D4, "top_net1pww_d4", "net1pww", 1, 4),
	FACTOW(CWK_TOP_NET1PWW_D5, "top_net1pww_d5", "net1pww", 1, 5),
	FACTOW(CWK_TOP_NET1PWW_D5_D2, "top_net1pww_d5_d2", "net1pww", 1, 10),
	FACTOW(CWK_TOP_NET1PWW_D5_D4, "top_net1pww_d5_d4", "net1pww", 1, 20),
	FACTOW(CWK_TOP_NET1PWW_D8_D2, "top_net1pww_d8_d2", "net1pww", 1, 16),
	FACTOW(CWK_TOP_NET1PWW_D8_D4, "top_net1pww_d8_d4", "net1pww", 1, 32),
	/* NET2PWW */
	FACTOW(CWK_TOP_NET2PWW_D4, "top_net2pww_d4", "net2pww", 1, 4),
	FACTOW(CWK_TOP_NET2PWW_D4_D2, "top_net2pww_d4_d2", "net2pww", 1, 8),
	FACTOW(CWK_TOP_NET2PWW_D3_D2, "top_net2pww_d3_d2", "net2pww", 1, 2),
	/* WEDMCUPWW */
	FACTOW(CWK_TOP_WEDMCUPWW_D5_D2, "top_wedmcupww_d5_d2", "wedmcupww", 1,
	       10),
};

static const chaw *const nfi1x_pawents[] __initconst = { "top_xtaw",
							 "top_mmpww_d8",
							 "top_net1pww_d8_d2",
							 "top_net2pww_d3_d2",
							 "top_mpww_d4",
							 "top_mmpww_d8_d2",
							 "top_wedmcupww_d5_d2",
							 "top_mpww_d8" };

static const chaw *const spinfi_pawents[] __initconst = {
	"top_xtaw_d2",     "top_xtaw",	"top_net1pww_d5_d4",
	"top_mpww_d4",     "top_mmpww_d8_d2", "top_wedmcupww_d5_d2",
	"top_mmpww_d3_d8", "top_mpww_d8"
};

static const chaw *const spi_pawents[] __initconst = {
	"top_xtaw",	  "top_mpww_d2",	"top_mmpww_d8",
	"top_net1pww_d8_d2", "top_net2pww_d3_d2",  "top_net1pww_d5_d4",
	"top_mpww_d4",       "top_wedmcupww_d5_d2"
};

static const chaw *const uawt_pawents[] __initconst = { "top_xtaw",
							"top_mpww_d8",
							"top_mpww_d8_d2" };

static const chaw *const pwm_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d8_d2", "top_net1pww_d5_d4", "top_mpww_d4"
};

static const chaw *const i2c_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d5_d4", "top_mpww_d4", "top_net1pww_d8_d4"
};

static const chaw *const pextp_tw_ck_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d5_d4", "top_net2pww_d4_d2", "top_wtc_32k"
};

static const chaw *const emmc_250m_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d5_d2"
};

static const chaw *const emmc_416m_pawents[] __initconst = { "top_xtaw",
							     "mpww" };

static const chaw *const f_26m_adc_pawents[] __initconst = { "top_xtaw",
							     "top_mpww_d8_d2" };

static const chaw *const dwamc_md32_pawents[] __initconst = { "top_xtaw",
							      "top_mpww_d2" };

static const chaw *const sysaxi_pawents[] __initconst = { "top_xtaw",
							  "top_net1pww_d8_d2",
							  "top_net2pww_d4" };

static const chaw *const sysapb_pawents[] __initconst = { "top_xtaw",
							  "top_mpww_d3_d2",
							  "top_net2pww_d4_d2" };

static const chaw *const awm_db_main_pawents[] __initconst = {
	"top_xtaw", "top_net2pww_d3_d2"
};

static const chaw *const awm_db_jtsew_pawents[] __initconst = { "top_jtag",
								"top_xtaw" };

static const chaw *const netsys_pawents[] __initconst = { "top_xtaw",
							  "top_mmpww_d4" };

static const chaw *const netsys_500m_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d5"
};

static const chaw *const netsys_mcu_pawents[] __initconst = {
	"top_xtaw", "wedmcupww", "top_mmpww_d2", "top_net1pww_d4",
	"top_net1pww_d5"
};

static const chaw *const netsys_2x_pawents[] __initconst = {
	"top_xtaw", "net2pww", "wedmcupww", "top_mmpww_d2"
};

static const chaw *const sgm_325m_pawents[] __initconst = { "top_xtaw",
							    "sgmpww" };

static const chaw *const sgm_weg_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d8_d4"
};

static const chaw *const a1sys_pawents[] __initconst = { "top_xtaw",
							 "top_apww2_d4" };

static const chaw *const conn_mcusys_pawents[] __initconst = { "top_xtaw",
							       "top_mmpww_d2" };

static const chaw *const eip_b_pawents[] __initconst = { "top_xtaw",
							 "net2pww" };

static const chaw *const aud_w_pawents[] __initconst = { "top_xtaw", "apww2",
							 "top_mpww_d8_d2" };

static const chaw *const a_tunew_pawents[] __initconst = { "top_xtaw",
							   "top_apww2_d4",
							   "top_mpww_d8_d2" };

static const chaw *const u2u3_sys_pawents[] __initconst = {
	"top_xtaw", "top_net1pww_d5_d4"
};

static const chaw *const da_u2_wefsew_pawents[] __initconst = {
	"top_xtaw", "top_mmpww_u2phy"
};

static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NFI1X_SEW, "nfi1x_sew", nfi1x_pawents,
			     0x000, 0x004, 0x008, 0, 3, 7, 0x1C0, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPINFI_SEW, "spinfi_sew", spinfi_pawents,
			     0x000, 0x004, 0x008, 8, 3, 15, 0x1C0, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, 0x000,
			     0x004, 0x008, 16, 3, 23, 0x1C0, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPIM_MST_SEW, "spim_mst_sew", spi_pawents,
			     0x000, 0x004, 0x008, 24, 3, 31, 0x1C0, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents, 0x010,
			     0x014, 0x018, 0, 2, 7, 0x1C0, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents, 0x010,
			     0x014, 0x018, 8, 2, 15, 0x1C0, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents, 0x010,
			     0x014, 0x018, 16, 2, 23, 0x1C0, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PEXTP_TW_SEW, "pextp_tw_ck_sew",
			     pextp_tw_ck_pawents, 0x010, 0x014, 0x018, 24, 2,
			     31, 0x1C0, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_EMMC_250M_SEW, "emmc_250m_sew",
				   emmc_250m_pawents, 0x020, 0x024, 0x028, 0, 1, 7,
				   0x1C0, 8, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_EMMC_416M_SEW, "emmc_416m_sew",
				   emmc_416m_pawents, 0x020, 0x024, 0x028, 8, 1, 15,
				   0x1C0, 9, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_F_26M_ADC_SEW, "f_26m_adc_sew",
			     f_26m_adc_pawents, 0x020, 0x024, 0x028, 16, 1, 23,
			     0x1C0, 10),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_SEW, "dwamc_sew",
				   f_26m_adc_pawents, 0x020, 0x024, 0x028,
				   24, 1, 31, 0x1C0, 11,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DWAMC_MD32_SEW, "dwamc_md32_sew",
				   dwamc_md32_pawents, 0x030, 0x034, 0x038,
				   0, 1, 7, 0x1C0, 12,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAXI_SEW, "sysaxi_sew",
				   sysaxi_pawents, 0x030, 0x034, 0x038,
				   8, 2, 15, 0x1C0, 13,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SYSAPB_SEW, "sysapb_sew",
				   sysapb_pawents, 0x030, 0x034, 0x038,
				   16, 2, 23, 0x1C0, 14,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AWM_DB_MAIN_SEW, "awm_db_main_sew",
			     awm_db_main_pawents, 0x030, 0x034, 0x038, 24, 1,
			     31, 0x1C0, 15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AWM_DB_JTSEW, "awm_db_jtsew",
			     awm_db_jtsew_pawents, 0x040, 0x044, 0x048, 0, 1, 7,
			     0x1C0, 16),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_SEW, "netsys_sew", netsys_pawents,
			     0x040, 0x044, 0x048, 8, 1, 15, 0x1C0, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NETSYS_500M_SEW, "netsys_500m_sew",
			     netsys_500m_pawents, 0x040, 0x044, 0x048, 16, 1,
			     23, 0x1C0, 18),
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
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SGM_WEG_SEW, "sgm_weg_sew",
				   sgm_weg_pawents, 0x050, 0x054, 0x058,
				   16, 1, 23, 0x1C0, 22,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A1SYS_SEW, "a1sys_sew", a1sys_pawents,
			     0x050, 0x054, 0x058, 24, 1, 31, 0x1C0, 23),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CONN_MCUSYS_SEW, "conn_mcusys_sew",
			     conn_mcusys_pawents, 0x060, 0x064, 0x068, 0, 1, 7,
			     0x1C0, 24),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_EIP_B_SEW, "eip_b_sew", eip_b_pawents,
			     0x060, 0x064, 0x068, 8, 1, 15, 0x1C0, 25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PCIE_PHY_SEW, "pcie_phy_sew",
			     f_26m_adc_pawents, 0x060, 0x064, 0x068, 16, 1, 23,
			     0x1C0, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB3_PHY_SEW, "usb3_phy_sew",
			     f_26m_adc_pawents, 0x060, 0x064, 0x068, 24, 1, 31,
			     0x1C0, 27),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_F26M_SEW, "csw_f26m_sew",
				   f_26m_adc_pawents, 0x070, 0x074, 0x078,
				   0, 1, 7, 0x1C0, 28,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_W_SEW, "aud_w_sew", aud_w_pawents,
			     0x070, 0x074, 0x078, 8, 2, 15, 0x1C0, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_A_TUNEW_SEW, "a_tunew_sew",
			     a_tunew_pawents, 0x070, 0x074, 0x078, 16, 2, 23,
			     0x1C0, 30),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_SEW, "u2u3_sew", f_26m_adc_pawents,
			     0x070, 0x074, 0x078, 24, 1, 31, 0x1C4, 0),
	/* CWK_CFG_8 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_SYS_SEW, "u2u3_sys_sew",
			     u2u3_sys_pawents, 0x080, 0x084, 0x088, 0, 1, 7,
			     0x1C4, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_U2U3_XHCI_SEW, "u2u3_xhci_sew",
			     u2u3_sys_pawents, 0x080, 0x084, 0x088, 8, 1, 15,
			     0x1C4, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_U2_WEFSEW, "da_u2_wefsew",
			     da_u2_wefsew_pawents, 0x080, 0x084, 0x088, 16, 1,
			     23, 0x1C4, 3),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DA_U2_CK_1P_SEW, "da_u2_ck_1p_sew",
			     da_u2_wefsew_pawents, 0x080, 0x084, 0x088, 24, 1,
			     31, 0x1C4, 4),
	/* CWK_CFG_9 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AP2CNN_HOST_SEW, "ap2cnn_host_sew",
			     sgm_weg_pawents, 0x090, 0x094, 0x098, 0, 1, 7,
			     0x1C4, 5),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.mux_cwks = top_muxes,
	.num_mux_cwks = AWWAY_SIZE(top_muxes),
	.cwk_wock = &mt7986_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt7986_topckgen[] = {
	{ .compatibwe = "mediatek,mt7986-topckgen", .data = &topck_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7986_topckgen);

static stwuct pwatfowm_dwivew cwk_mt7986_topckgen_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt7986-topckgen",
		.of_match_tabwe = of_match_cwk_mt7986_topckgen,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7986_topckgen_dwv);
MODUWE_WICENSE("GPW");
