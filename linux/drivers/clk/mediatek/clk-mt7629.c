// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 MediaTek Inc.
 * Authow: Wenzhen Yu <Wenzhen Yu@mediatek.com>
 *	   Wydew Wee <wydew.wee@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-cpumux.h"
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt7629-cwk.h>

#define MT7629_PWW_FMAX		(2500UW * MHZ)
#define CON0_MT7629_WST_BAW	BIT(24)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift, _div_tabwe, _pawent_name) {		\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT7629_WST_BAW,			\
		.fmax = MT7629_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = _div_tabwe,				\
		.pawent_name = _pawent_name,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
		_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,		\
		_pcw_shift)						\
	PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
		_pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift,	\
		NUWW, "cwk20m")

#define GATE_APMIXED(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &apmixed_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_INFWA(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static DEFINE_SPINWOCK(mt7629_cwk_wock);

static const chaw * const axi_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww2_d2",
	"univpww_d7",
	"dmpww_ck"
};

static const chaw * const mem_pawents[] = {
	"cwkxtaw",
	"dmpww_ck"
};

static const chaw * const ddwphycfg_pawents[] = {
	"cwkxtaw",
	"syspww1_d8"
};

static const chaw * const eth_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"univpww1_d2",
	"syspww1_d4",
	"univpww_d5",
	"sgmiipww_d2",
	"univpww_d7",
	"dmpww_ck"
};

static const chaw * const pwm_pawents[] = {
	"cwkxtaw",
	"univpww2_d4"
};

static const chaw * const f10m_wef_pawents[] = {
	"cwkxtaw",
	"sgmiipww_d2"
};

static const chaw * const nfi_infwa_pawents[] = {
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"univpww2_d8",
	"univpww3_d4",
	"syspww1_d8",
	"univpww1_d8",
	"syspww4_d2",
	"syspww2_d4",
	"univpww2_d4",
	"univpww3_d2",
	"syspww1_d4",
	"syspww_d7"
};

static const chaw * const fwash_pawents[] = {
	"cwkxtaw",
	"univpww_d80_d4",
	"syspww2_d8",
	"syspww3_d4",
	"univpww3_d4",
	"univpww1_d8",
	"syspww2_d4",
	"univpww2_d4"
};

static const chaw * const uawt_pawents[] = {
	"cwkxtaw",
	"univpww2_d8"
};

static const chaw * const spi0_pawents[] = {
	"cwkxtaw",
	"syspww3_d2",
	"cwkxtaw",
	"syspww2_d4",
	"syspww4_d2",
	"univpww2_d4",
	"univpww1_d8",
	"cwkxtaw"
};

static const chaw * const spi1_pawents[] = {
	"cwkxtaw",
	"syspww3_d2",
	"cwkxtaw",
	"syspww4_d4",
	"syspww4_d2",
	"univpww2_d4",
	"univpww1_d8",
	"cwkxtaw"
};

static const chaw * const msdc30_0_pawents[] = {
	"cwkxtaw",
	"univpww2_d16",
	"univ48m"
};

static const chaw * const msdc30_1_pawents[] = {
	"cwkxtaw",
	"univpww2_d16",
	"univ48m",
	"syspww2_d4",
	"univpww2_d4",
	"syspww_d7",
	"syspww2_d2",
	"univpww2_d2"
};

static const chaw * const ap2wbmcu_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"univ48m",
	"syspww1_d8",
	"univpww2_d4",
	"syspww_d7",
	"syspww2_d2",
	"univpww2_d2"
};

static const chaw * const audio_pawents[] = {
	"cwkxtaw",
	"syspww3_d4",
	"syspww4_d4",
	"syspww1_d16"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwkxtaw",
	"syspww1_d4",
	"syspww4_d2",
	"dmpww_d4"
};

static const chaw * const pmicspi_pawents[] = {
	"cwkxtaw",
	"syspww1_d8",
	"syspww3_d4",
	"syspww1_d16",
	"univpww3_d4",
	"cwkxtaw",
	"univpww2_d4",
	"dmpww_d8"
};

static const chaw * const scp_pawents[] = {
	"cwkxtaw",
	"syspww1_d8",
	"univpww2_d2",
	"univpww2_d4"
};

static const chaw * const atb_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"syspww_d5"
};

static const chaw * const hif_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"univpww1_d2",
	"syspww1_d4",
	"univpww_d5",
	"cwk_nuww",
	"univpww_d7"
};

static const chaw * const sata_pawents[] = {
	"cwkxtaw",
	"univpww2_d4"
};

static const chaw * const usb20_pawents[] = {
	"cwkxtaw",
	"univpww3_d4",
	"syspww1_d8"
};

static const chaw * const aud1_pawents[] = {
	"cwkxtaw"
};

static const chaw * const iwwx_pawents[] = {
	"cwkxtaw",
	"syspww4_d16"
};

static const chaw * const cwypto_pawents[] = {
	"cwkxtaw",
	"univpww_d3",
	"univpww1_d2",
	"syspww1_d2",
	"univpww_d5",
	"syspww_d5",
	"univpww2_d2",
	"syspww_d2"
};

static const chaw * const gpt10m_pawents[] = {
	"cwkxtaw",
	"cwkxtaw_d4"
};

static const chaw * const pewibus_ck_pawents[] = {
	"syspww1_d8",
	"syspww1_d4"
};

static const chaw * const infwa_mux1_pawents[] = {
	"cwkxtaw",
	"awmpww",
	"main_cowe_en",
	"awmpww"
};

static const stwuct mtk_gate_wegs apmixed_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0x8,
	.sta_ofs = 0x8,
};

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x40,
	.cww_ofs = 0x44,
	.sta_ofs = 0x48,
};

static const stwuct mtk_gate_wegs pewi0_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0x10,
	.sta_ofs = 0x18,
};

static const stwuct mtk_gate_wegs pewi1_cg_wegs = {
	.set_ofs = 0xC,
	.cww_ofs = 0x14,
	.sta_ofs = 0x1C,
};

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x0200, 0x020C, 0,
	    0, 21, 0x0204, 24, 0, 0x0204, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0210, 0x021C, 0,
	    HAVE_WST_BAW, 21, 0x0214, 24, 0, 0x0214, 0),
	PWW(CWK_APMIXED_UNIV2PWW, "univ2pww", 0x0220, 0x022C, 0,
	    HAVE_WST_BAW, 7, 0x0224, 24, 0, 0x0224, 14),
	PWW(CWK_APMIXED_ETH1PWW, "eth1pww", 0x0300, 0x0310, 0,
	    0, 21, 0x0300, 1, 0, 0x0304, 0),
	PWW(CWK_APMIXED_ETH2PWW, "eth2pww", 0x0314, 0x0320, 0,
	    0, 21, 0x0314, 1, 0, 0x0318, 0),
	PWW(CWK_APMIXED_SGMIPWW, "sgmipww", 0x0358, 0x0368, 0,
	    0, 21, 0x0358, 1, 0, 0x035C, 0),
};

static const stwuct mtk_gate apmixed_cwks[] = {
	GATE_APMIXED(CWK_APMIXED_MAIN_COWE_EN, "main_cowe_en", "mainpww", 5),
};

static const stwuct mtk_gate infwa_cwks[] = {
	GATE_INFWA(CWK_INFWA_DBGCWK_PD, "infwa_dbgcwk_pd", "hd_faxi", 0),
	GATE_INFWA(CWK_INFWA_TWNG_PD, "infwa_twng_pd", "hd_faxi", 2),
	GATE_INFWA(CWK_INFWA_DEVAPC_PD, "infwa_devapc_pd", "hd_faxi", 4),
	GATE_INFWA(CWK_INFWA_APXGPT_PD, "infwa_apxgpt_pd", "infwao_10m", 18),
	GATE_INFWA(CWK_INFWA_SEJ_PD, "infwa_sej_pd", "infwao_10m", 19),
};

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_TO_U2_PHY, "to_u2_phy", "cwkxtaw",
		  31250000),
	FIXED_CWK(CWK_TOP_TO_U2_PHY_1P, "to_u2_phy_1p", "cwkxtaw",
		  31250000),
	FIXED_CWK(CWK_TOP_PCIE0_PIPE_EN, "pcie0_pipe_en", "cwkxtaw",
		  125000000),
	FIXED_CWK(CWK_TOP_PCIE1_PIPE_EN, "pcie1_pipe_en", "cwkxtaw",
		  125000000),
	FIXED_CWK(CWK_TOP_SSUSB_TX250M, "ssusb_tx250m", "cwkxtaw",
		  250000000),
	FIXED_CWK(CWK_TOP_SSUSB_EQ_WX250M, "ssusb_eq_wx250m", "cwkxtaw",
		  250000000),
	FIXED_CWK(CWK_TOP_SSUSB_CDW_WEF, "ssusb_cdw_wef", "cwkxtaw",
		  33333333),
	FIXED_CWK(CWK_TOP_SSUSB_CDW_FB, "ssusb_cdw_fb", "cwkxtaw",
		  50000000),
	FIXED_CWK(CWK_TOP_SATA_ASIC, "sata_asic", "cwkxtaw",
		  50000000),
	FIXED_CWK(CWK_TOP_SATA_WBC, "sata_wbc", "cwkxtaw",
		  50000000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_TO_USB3_SYS, "to_usb3_sys", "eth1pww", 1, 4),
	FACTOW(CWK_TOP_P1_1MHZ, "p1_1mhz", "eth1pww", 1, 500),
	FACTOW(CWK_TOP_4MHZ, "fwee_wun_4mhz", "eth1pww", 1, 125),
	FACTOW(CWK_TOP_P0_1MHZ, "p0_1mhz", "eth1pww", 1, 500),
	FACTOW(CWK_TOP_ETH_500M, "eth_500m", "eth1pww", 1, 1),
	FACTOW(CWK_TOP_TXCWK_SWC_PWE, "txcwk_swc_pwe", "sgmiipww_d2", 1, 1),
	FACTOW(CWK_TOP_WTC, "wtc", "cwkxtaw", 1, 1024),
	FACTOW(CWK_TOP_PWM_QTW_26M, "pwm_qtw_26m", "cwkxtaw", 1, 1),
	FACTOW(CWK_TOP_CPUM_TCK_IN, "cpum_tck_in", "cpum_tck", 1, 1),
	FACTOW(CWK_TOP_TO_USB3_DA_TOP, "to_usb3_da_top", "cwkxtaw", 1, 1),
	FACTOW(CWK_TOP_MEMPWW, "mempww", "cwkxtaw", 32, 1),
	FACTOW(CWK_TOP_DMPWW, "dmpww_ck", "mempww", 1, 1),
	FACTOW(CWK_TOP_DMPWW_D4, "dmpww_d4", "mempww", 1, 4),
	FACTOW(CWK_TOP_DMPWW_D8, "dmpww_d8", "mempww", 1, 8),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "mainpww", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "mainpww", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "mainpww", 1, 16),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "mainpww", 1, 32),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "mainpww", 1, 6),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "mainpww", 1, 12),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "mainpww", 1, 24),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "mainpww", 1, 10),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "mainpww", 1, 20),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "mainpww", 1, 14),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "mainpww", 1, 28),
	FACTOW(CWK_TOP_SYSPWW4_D16, "syspww4_d16", "mainpww", 1, 112),
	FACTOW(CWK_TOP_UNIVPWW, "univpww", "univ2pww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww", 1, 16),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww", 1, 6),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww", 1, 12),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww", 1, 24),
	FACTOW(CWK_TOP_UNIVPWW2_D16, "univpww2_d16", "univpww", 1, 48),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww", 1, 10),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww", 1, 20),
	FACTOW(CWK_TOP_UNIVPWW3_D16, "univpww3_d16", "univpww", 1, 80),
	FACTOW(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww", 1, 7),
	FACTOW(CWK_TOP_UNIVPWW_D80_D4, "univpww_d80_d4", "univpww", 1, 320),
	FACTOW(CWK_TOP_UNIV48M, "univ48m", "univpww", 1, 25),
	FACTOW(CWK_TOP_SGMIIPWW_D2, "sgmiipww_d2", "sgmipww", 1, 2),
	FACTOW(CWK_TOP_CWKXTAW_D4, "cwkxtaw_d4", "cwkxtaw", 1, 4),
	FACTOW(CWK_TOP_HD_FAXI, "hd_faxi", "axi_sew", 1, 1),
	FACTOW(CWK_TOP_FAXI, "faxi", "axi_sew", 1, 1),
	FACTOW(CWK_TOP_F_FAUD_INTBUS, "f_faud_intbus", "aud_intbus_sew", 1, 1),
	FACTOW(CWK_TOP_AP2WBHIF_HCWK, "ap2wbhif_hcwk", "syspww1_d8", 1, 1),
	FACTOW(CWK_TOP_10M_INFWAO, "infwao_10m", "gpt10m_sew", 1, 1),
	FACTOW(CWK_TOP_MSDC30_1, "msdc30_1", "msdc30_1_sew", 1, 1),
	FACTOW(CWK_TOP_SPI, "spi", "spi0_sew", 1, 1),
	FACTOW(CWK_TOP_SF, "sf", "nfi_infwa_sew", 1, 1),
	FACTOW(CWK_TOP_FWASH, "fwash", "fwash_sew", 1, 1),
	FACTOW(CWK_TOP_TO_USB3_WEF, "to_usb3_wef", "sata_sew", 1, 4),
	FACTOW(CWK_TOP_TO_USB3_MCU, "to_usb3_mcu", "axi_sew", 1, 1),
	FACTOW(CWK_TOP_TO_USB3_DMA, "to_usb3_dma", "hif_sew", 1, 1),
	FACTOW(CWK_TOP_FWOM_TOP_AHB, "fwom_top_ahb", "axi_sew", 1, 1),
	FACTOW(CWK_TOP_FWOM_TOP_AXI, "fwom_top_axi", "hif_sew", 1, 1),
	FACTOW(CWK_TOP_PCIE1_MAC_EN, "pcie1_mac_en", "sata_sew", 1, 1),
	FACTOW(CWK_TOP_PCIE0_MAC_EN, "pcie0_mac_en", "sata_sew", 1, 1),
};

static const stwuct mtk_gate pewi_cwks[] = {
	/* PEWI0 */
	GATE_PEWI0(CWK_PEWI_PWM1_PD, "pewi_pwm1_pd", "pwm_qtw_26m", 2),
	GATE_PEWI0(CWK_PEWI_PWM2_PD, "pewi_pwm2_pd", "pwm_qtw_26m", 3),
	GATE_PEWI0(CWK_PEWI_PWM3_PD, "pewi_pwm3_pd", "pwm_qtw_26m", 4),
	GATE_PEWI0(CWK_PEWI_PWM4_PD, "pewi_pwm4_pd", "pwm_qtw_26m", 5),
	GATE_PEWI0(CWK_PEWI_PWM5_PD, "pewi_pwm5_pd", "pwm_qtw_26m", 6),
	GATE_PEWI0(CWK_PEWI_PWM6_PD, "pewi_pwm6_pd", "pwm_qtw_26m", 7),
	GATE_PEWI0(CWK_PEWI_PWM7_PD, "pewi_pwm7_pd", "pwm_qtw_26m", 8),
	GATE_PEWI0(CWK_PEWI_PWM_PD, "pewi_pwm_pd", "pwm_qtw_26m", 9),
	GATE_PEWI0(CWK_PEWI_AP_DMA_PD, "pewi_ap_dma_pd", "faxi", 12),
	GATE_PEWI0(CWK_PEWI_MSDC30_1_PD, "pewi_msdc30_1", "msdc30_1", 14),
	GATE_PEWI0(CWK_PEWI_UAWT0_PD, "pewi_uawt0_pd", "faxi", 17),
	GATE_PEWI0(CWK_PEWI_UAWT1_PD, "pewi_uawt1_pd", "faxi", 18),
	GATE_PEWI0(CWK_PEWI_UAWT2_PD, "pewi_uawt2_pd", "faxi", 19),
	GATE_PEWI0(CWK_PEWI_UAWT3_PD, "pewi_uawt3_pd", "faxi", 20),
	GATE_PEWI0(CWK_PEWI_BTIF_PD, "pewi_btif_pd", "faxi", 22),
	GATE_PEWI0(CWK_PEWI_I2C0_PD, "pewi_i2c0_pd", "faxi", 23),
	GATE_PEWI0(CWK_PEWI_SPI0_PD, "pewi_spi0_pd", "spi", 28),
	GATE_PEWI0(CWK_PEWI_SNFI_PD, "pewi_snfi_pd", "sf", 29),
	GATE_PEWI0(CWK_PEWI_NFI_PD, "pewi_nfi_pd", "faxi", 30),
	GATE_PEWI0(CWK_PEWI_NFIECC_PD, "pewi_nfiecc_pd", "faxi", 31),
	/* PEWI1 */
	GATE_PEWI1(CWK_PEWI_FWASH_PD, "pewi_fwash_pd", "fwash", 1),
};

static stwuct mtk_composite infwa_muxes[] = {
	/* INFWA_TOPCKGEN_CKMUXSEW */
	MUX(CWK_INFWA_MUX1_SEW, "infwa_mux1_sew", infwa_mux1_pawents, 0x000,
	    2, 2),
};

static stwuct mtk_composite top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
		 0x040, 0, 3, 7),
	MUX_GATE(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents,
		 0x040, 8, 1, 15),
	MUX_GATE(CWK_TOP_DDWPHYCFG_SEW, "ddwphycfg_sew", ddwphycfg_pawents,
		 0x040, 16, 1, 23),
	MUX_GATE(CWK_TOP_ETH_SEW, "eth_sew", eth_pawents,
		 0x040, 24, 3, 31),
	/* CWK_CFG_1 */
	MUX_GATE(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents,
		 0x050, 0, 2, 7),
	MUX_GATE(CWK_TOP_F10M_WEF_SEW, "f10m_wef_sew", f10m_wef_pawents,
		 0x050, 8, 1, 15),
	MUX_GATE(CWK_TOP_NFI_INFWA_SEW, "nfi_infwa_sew", nfi_infwa_pawents,
		 0x050, 16, 4, 23),
	MUX_GATE(CWK_TOP_FWASH_SEW, "fwash_sew", fwash_pawents,
		 0x050, 24, 3, 31),
	/* CWK_CFG_2 */
	MUX_GATE(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents,
		 0x060, 0, 1, 7),
	MUX_GATE(CWK_TOP_SPI0_SEW, "spi0_sew", spi0_pawents,
		 0x060, 8, 3, 15),
	MUX_GATE(CWK_TOP_SPI1_SEW, "spi1_sew", spi1_pawents,
		 0x060, 16, 3, 23),
	MUX_GATE(CWK_TOP_MSDC50_0_SEW, "msdc50_0_sew", uawt_pawents,
		 0x060, 24, 3, 31),
	/* CWK_CFG_3 */
	MUX_GATE(CWK_TOP_MSDC30_0_SEW, "msdc30_0_sew", msdc30_0_pawents,
		 0x070, 0, 3, 7),
	MUX_GATE(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew", msdc30_1_pawents,
		 0x070, 8, 3, 15),
	MUX_GATE(CWK_TOP_AP2WBMCU_SEW, "ap2wbmcu_sew", ap2wbmcu_pawents,
		 0x070, 16, 3, 23),
	MUX_GATE(CWK_TOP_AP2WBHIF_SEW, "ap2wbhif_sew", ap2wbmcu_pawents,
		 0x070, 24, 3, 31),
	/* CWK_CFG_4 */
	MUX_GATE(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents,
		 0x080, 0, 2, 7),
	MUX_GATE(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		 0x080, 8, 2, 15),
	MUX_GATE(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents,
		 0x080, 16, 3, 23),
	MUX_GATE(CWK_TOP_SCP_SEW, "scp_sew", scp_pawents,
		 0x080, 24, 2, 31),
	/* CWK_CFG_5 */
	MUX_GATE(CWK_TOP_ATB_SEW, "atb_sew", atb_pawents,
		 0x090, 0, 2, 7),
	MUX_GATE(CWK_TOP_HIF_SEW, "hif_sew", hif_pawents,
		 0x090, 8, 3, 15),
	MUX_GATE(CWK_TOP_SATA_SEW, "sata_sew", sata_pawents,
		 0x090, 16, 1, 23),
	MUX_GATE(CWK_TOP_U2_SEW, "usb20_sew", usb20_pawents,
		 0x090, 24, 2, 31),
	/* CWK_CFG_6 */
	MUX_GATE(CWK_TOP_AUD1_SEW, "aud1_sew", aud1_pawents,
		 0x0A0, 0, 1, 7),
	MUX_GATE(CWK_TOP_AUD2_SEW, "aud2_sew", aud1_pawents,
		 0x0A0, 8, 1, 15),
	MUX_GATE(CWK_TOP_IWWX_SEW, "iwwx_sew", iwwx_pawents,
		 0x0A0, 16, 1, 23),
	MUX_GATE(CWK_TOP_IWTX_SEW, "iwtx_sew", iwwx_pawents,
		 0x0A0, 24, 1, 31),
	/* CWK_CFG_7 */
	MUX_GATE(CWK_TOP_SATA_MCU_SEW, "sata_mcu_sew", scp_pawents,
		 0x0B0, 0, 2, 7),
	MUX_GATE(CWK_TOP_PCIE0_MCU_SEW, "pcie0_mcu_sew", scp_pawents,
		 0x0B0, 8, 2, 15),
	MUX_GATE(CWK_TOP_PCIE1_MCU_SEW, "pcie1_mcu_sew", scp_pawents,
		 0x0B0, 16, 2, 23),
	MUX_GATE(CWK_TOP_SSUSB_MCU_SEW, "ssusb_mcu_sew", scp_pawents,
		 0x0B0, 24, 2, 31),
	/* CWK_CFG_8 */
	MUX_GATE(CWK_TOP_CWYPTO_SEW, "cwypto_sew", cwypto_pawents,
		 0x0C0, 0, 3, 7),
	MUX_GATE(CWK_TOP_SGMII_WEF_1_SEW, "sgmii_wef_1_sew", f10m_wef_pawents,
		 0x0C0, 8, 1, 15),
	MUX_GATE(CWK_TOP_10M_SEW, "gpt10m_sew", gpt10m_pawents,
		 0x0C0, 16, 1, 23),
};

static stwuct mtk_composite pewi_muxes[] = {
	/* PEWI_GWOBAWCON_CKSEW */
	MUX(CWK_PEWIBUS_SEW, "pewibus_ck_sew", pewibus_ck_pawents, 0x05C, 0, 1),
};

static int mtk_topckgen_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base;
	stwuct device_node *node = pdev->dev.of_node;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_TOP_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_fixed_cwks(top_fixed_cwks, AWWAY_SIZE(top_fixed_cwks),
				    cwk_data);

	mtk_cwk_wegistew_factows(top_divs, AWWAY_SIZE(top_divs),
				 cwk_data);

	mtk_cwk_wegistew_composites(&pdev->dev, top_muxes,
				    AWWAY_SIZE(top_muxes), base,
				    &mt7629_cwk_wock, cwk_data);

	cwk_pwepawe_enabwe(cwk_data->hws[CWK_TOP_AXI_SEW]->cwk);
	cwk_pwepawe_enabwe(cwk_data->hws[CWK_TOP_MEM_SEW]->cwk);
	cwk_pwepawe_enabwe(cwk_data->hws[CWK_TOP_DDWPHYCFG_SEW]->cwk);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}

static int mtk_infwasys_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data;

	cwk_data = mtk_awwoc_cwk_data(CWK_INFWA_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, infwa_cwks,
			       AWWAY_SIZE(infwa_cwks), cwk_data);

	mtk_cwk_wegistew_cpumuxes(&pdev->dev, node, infwa_muxes,
				  AWWAY_SIZE(infwa_muxes), cwk_data);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				      cwk_data);
}

static int mtk_pewicfg_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base;
	int w;
	stwuct device_node *node = pdev->dev.of_node;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_PEWI_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, pewi_cwks,
			       AWWAY_SIZE(pewi_cwks), cwk_data);

	mtk_cwk_wegistew_composites(&pdev->dev, pewi_muxes,
				    AWWAY_SIZE(pewi_muxes), base,
				    &mt7629_cwk_wock, cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		wetuwn w;

	cwk_pwepawe_enabwe(cwk_data->hws[CWK_PEWI_UAWT0_PD]->cwk);

	wetuwn 0;
}

static int mtk_apmixedsys_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws),
			      cwk_data);

	mtk_cwk_wegistew_gates(&pdev->dev, node, apmixed_cwks,
			       AWWAY_SIZE(apmixed_cwks), cwk_data);

	cwk_pwepawe_enabwe(cwk_data->hws[CWK_APMIXED_AWMPWW]->cwk);
	cwk_pwepawe_enabwe(cwk_data->hws[CWK_APMIXED_MAIN_COWE_EN]->cwk);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}


static const stwuct of_device_id of_match_cwk_mt7629[] = {
	{
		.compatibwe = "mediatek,mt7629-apmixedsys",
		.data = mtk_apmixedsys_init,
	}, {
		.compatibwe = "mediatek,mt7629-infwacfg",
		.data = mtk_infwasys_init,
	}, {
		.compatibwe = "mediatek,mt7629-topckgen",
		.data = mtk_topckgen_init,
	}, {
		.compatibwe = "mediatek,mt7629-pewicfg",
		.data = mtk_pewicfg_init,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7629);

static int cwk_mt7629_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*cwk_init)(stwuct pwatfowm_device *);
	int w;

	cwk_init = of_device_get_match_data(&pdev->dev);
	if (!cwk_init)
		wetuwn -EINVAW;

	w = cwk_init(pdev);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_mt7629_dwv = {
	.pwobe = cwk_mt7629_pwobe,
	.dwivew = {
		.name = "cwk-mt7629",
		.of_match_tabwe = of_match_cwk_mt7629,
	},
};

static int cwk_mt7629_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwk_mt7629_dwv);
}

awch_initcaww(cwk_mt7629_init);
MODUWE_WICENSE("GPW");
