// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Chen Zhong <chen.zhong@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-cpumux.h"
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt7622-cwk.h>
#incwude <winux/cwk.h> /* fow consumew */

#define GATE_TOP0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_TOP1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_PEWI0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI0_AO(_id, _name, _pawent, _shift)			\
	GATE_MTK_FWAGS(_id, _name, _pawent, &pewi0_cg_wegs, _shift,	\
		 &mtk_cwk_gate_ops_setcww, CWK_IS_CWITICAW)

#define GATE_PEWI1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static DEFINE_SPINWOCK(mt7622_cwk_wock);

static const chaw * const axi_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww2_d2",
	"univpww_d7"
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
	"cwk_nuww",
	"univpww_d7"
};

static const chaw * const pwm_pawents[] = {
	"cwkxtaw",
	"univpww2_d4"
};

static const chaw * const f10m_wef_pawents[] = {
	"cwkxtaw",
	"syspww4_d16"
};

static const chaw * const nfi_infwa_pawents[] = {
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"cwkxtaw",
	"univpww2_d8",
	"syspww1_d8",
	"univpww1_d8",
	"syspww4_d2",
	"univpww2_d4",
	"univpww3_d2",
	"syspww1_d4"
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

static const chaw * const a1sys_hp_pawents[] = {
	"cwkxtaw",
	"aud1pww_ck",
	"aud2pww_ck",
	"cwkxtaw"
};

static const chaw * const intdiw_pawents[] = {
	"cwkxtaw",
	"syspww_d2",
	"univpww_d2",
	"sgmiipww_ck"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwkxtaw",
	"syspww1_d4",
	"syspww4_d2",
	"syspww3_d2"
};

static const chaw * const pmicspi_pawents[] = {
	"cwkxtaw",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"univpww2_d16"
};

static const chaw * const atb_pawents[] = {
	"cwkxtaw",
	"syspww1_d2",
	"syspww_d5"
};

static const chaw * const audio_pawents[] = {
	"cwkxtaw",
	"syspww3_d4",
	"syspww4_d4",
	"univpww1_d16"
};

static const chaw * const usb20_pawents[] = {
	"cwkxtaw",
	"univpww3_d4",
	"syspww1_d8",
	"cwkxtaw"
};

static const chaw * const aud1_pawents[] = {
	"cwkxtaw",
	"aud1pww_ck"
};

static const chaw * const aud2_pawents[] = {
	"cwkxtaw",
	"aud2pww_ck"
};

static const chaw * const asm_w_pawents[] = {
	"cwkxtaw",
	"syspww_d5",
	"univpww2_d2",
	"univpww2_d4"
};

static const chaw * const apww1_ck_pawents[] = {
	"aud1_sew",
	"aud2_sew"
};

static const chaw * const pewibus_ck_pawents[] = {
	"syspww1_d8",
	"syspww1_d4"
};

static const stwuct mtk_gate_wegs top0_cg_wegs = {
	.set_ofs = 0x120,
	.cww_ofs = 0x120,
	.sta_ofs = 0x120,
};

static const stwuct mtk_gate_wegs top1_cg_wegs = {
	.set_ofs = 0x128,
	.cww_ofs = 0x128,
	.sta_ofs = 0x128,
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
	FACTOW(CWK_TOP_TXCWK_SWC_PWE, "txcwk_swc_pwe", "sgmiipww_d2", 1, 1),
	FACTOW(CWK_TOP_WTC, "wtc", "cwkxtaw", 1, 1024),
	FACTOW(CWK_TOP_MEMPWW, "mempww", "cwkxtaw", 32, 1),
	FACTOW(CWK_TOP_DMPWW, "dmpww_ck", "mempww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "mainpww", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "mainpww", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "mainpww", 1, 16),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "mainpww", 1, 12),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "mainpww", 1, 24),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "mainpww", 1, 10),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "mainpww", 1, 20),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "mainpww", 1, 14),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "mainpww", 1, 28),
	FACTOW(CWK_TOP_SYSPWW4_D16, "syspww4_d16", "mainpww", 1, 112),
	FACTOW(CWK_TOP_UNIVPWW, "univpww", "univ2pww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww", 1, 16),
	FACTOW(CWK_TOP_UNIVPWW1_D16, "univpww1_d16", "univpww", 1, 32),
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
	FACTOW(CWK_TOP_SGMIIPWW, "sgmiipww_ck", "sgmipww", 1, 1),
	FACTOW(CWK_TOP_SGMIIPWW_D2, "sgmiipww_d2", "sgmipww", 1, 2),
	FACTOW(CWK_TOP_AUD1PWW, "aud1pww_ck", "aud1pww", 1, 1),
	FACTOW(CWK_TOP_AUD2PWW, "aud2pww_ck", "aud2pww", 1, 1),
	FACTOW(CWK_TOP_AUD_I2S2_MCK, "aud_i2s2_mck", "i2s2_mck_sew", 1, 2),
	FACTOW(CWK_TOP_TO_USB3_WEF, "to_usb3_wef", "univpww2_d4", 1, 4),
	FACTOW(CWK_TOP_PCIE1_MAC_EN, "pcie1_mac_en", "univpww1_d4", 1, 1),
	FACTOW(CWK_TOP_PCIE0_MAC_EN, "pcie0_mac_en", "univpww1_d4", 1, 1),
	FACTOW(CWK_TOP_ETH_500M, "eth_500m", "eth1pww", 1, 1),
};

static const stwuct mtk_gate top_cwks[] = {
	/* TOP0 */
	GATE_TOP0(CWK_TOP_APWW1_DIV_PD, "apww1_ck_div_pd", "apww1_ck_div", 0),
	GATE_TOP0(CWK_TOP_APWW2_DIV_PD, "apww2_ck_div_pd", "apww2_ck_div", 1),
	GATE_TOP0(CWK_TOP_I2S0_MCK_DIV_PD, "i2s0_mck_div_pd", "i2s0_mck_div",
		  2),
	GATE_TOP0(CWK_TOP_I2S1_MCK_DIV_PD, "i2s1_mck_div_pd", "i2s1_mck_div",
		  3),
	GATE_TOP0(CWK_TOP_I2S2_MCK_DIV_PD, "i2s2_mck_div_pd", "i2s2_mck_div",
		  4),
	GATE_TOP0(CWK_TOP_I2S3_MCK_DIV_PD, "i2s3_mck_div_pd", "i2s3_mck_div",
		  5),

	/* TOP1 */
	GATE_TOP1(CWK_TOP_A1SYS_HP_DIV_PD, "a1sys_div_pd", "a1sys_div", 0),
	GATE_TOP1(CWK_TOP_A2SYS_HP_DIV_PD, "a2sys_div_pd", "a2sys_div", 16),
};

static const stwuct mtk_cwk_dividew top_adj_divs[] = {
	DIV_ADJ(CWK_TOP_APWW1_DIV, "apww1_ck_div", "apww1_ck_sew",
		0x120, 24, 3),
	DIV_ADJ(CWK_TOP_APWW2_DIV, "apww2_ck_div", "apww2_ck_sew",
		0x120, 28, 3),
	DIV_ADJ(CWK_TOP_I2S0_MCK_DIV, "i2s0_mck_div", "i2s0_mck_sew",
		0x124, 0, 7),
	DIV_ADJ(CWK_TOP_I2S1_MCK_DIV, "i2s1_mck_div", "i2s1_mck_sew",
		0x124, 8, 7),
	DIV_ADJ(CWK_TOP_I2S2_MCK_DIV, "i2s2_mck_div", "aud_i2s2_mck",
		0x124, 16, 7),
	DIV_ADJ(CWK_TOP_I2S3_MCK_DIV, "i2s3_mck_div", "i2s3_mck_sew",
		0x124, 24, 7),
	DIV_ADJ(CWK_TOP_A1SYS_HP_DIV, "a1sys_div", "a1sys_hp_sew",
		0x128, 8, 7),
	DIV_ADJ(CWK_TOP_A2SYS_HP_DIV, "a2sys_div", "a2sys_hp_sew",
		0x128, 24, 7),
};

static const stwuct mtk_gate pewi_cwks[] = {
	/* PEWI0 */
	GATE_PEWI0(CWK_PEWI_THEWM_PD, "pewi_thewm_pd", "axi_sew", 1),
	GATE_PEWI0(CWK_PEWI_PWM1_PD, "pewi_pwm1_pd", "cwkxtaw", 2),
	GATE_PEWI0(CWK_PEWI_PWM2_PD, "pewi_pwm2_pd", "cwkxtaw", 3),
	GATE_PEWI0(CWK_PEWI_PWM3_PD, "pewi_pwm3_pd", "cwkxtaw", 4),
	GATE_PEWI0(CWK_PEWI_PWM4_PD, "pewi_pwm4_pd", "cwkxtaw", 5),
	GATE_PEWI0(CWK_PEWI_PWM5_PD, "pewi_pwm5_pd", "cwkxtaw", 6),
	GATE_PEWI0(CWK_PEWI_PWM6_PD, "pewi_pwm6_pd", "cwkxtaw", 7),
	GATE_PEWI0(CWK_PEWI_PWM7_PD, "pewi_pwm7_pd", "cwkxtaw", 8),
	GATE_PEWI0(CWK_PEWI_PWM_PD, "pewi_pwm_pd", "cwkxtaw", 9),
	GATE_PEWI0(CWK_PEWI_AP_DMA_PD, "pewi_ap_dma_pd", "axi_sew", 12),
	GATE_PEWI0(CWK_PEWI_MSDC30_0_PD, "pewi_msdc30_0", "msdc30_0_sew", 13),
	GATE_PEWI0(CWK_PEWI_MSDC30_1_PD, "pewi_msdc30_1", "msdc30_1_sew", 14),
	GATE_PEWI0_AO(CWK_PEWI_UAWT0_PD, "pewi_uawt0_pd", "axi_sew", 17),
	GATE_PEWI0(CWK_PEWI_UAWT1_PD, "pewi_uawt1_pd", "axi_sew", 18),
	GATE_PEWI0(CWK_PEWI_UAWT2_PD, "pewi_uawt2_pd", "axi_sew", 19),
	GATE_PEWI0(CWK_PEWI_UAWT3_PD, "pewi_uawt3_pd", "axi_sew", 20),
	GATE_PEWI0(CWK_PEWI_UAWT4_PD, "pewi_uawt4_pd", "axi_sew", 21),
	GATE_PEWI0(CWK_PEWI_BTIF_PD, "pewi_btif_pd", "axi_sew", 22),
	GATE_PEWI0(CWK_PEWI_I2C0_PD, "pewi_i2c0_pd", "axi_sew", 23),
	GATE_PEWI0(CWK_PEWI_I2C1_PD, "pewi_i2c1_pd", "axi_sew", 24),
	GATE_PEWI0(CWK_PEWI_I2C2_PD, "pewi_i2c2_pd", "axi_sew", 25),
	GATE_PEWI0(CWK_PEWI_SPI1_PD, "pewi_spi1_pd", "spi1_sew", 26),
	GATE_PEWI0(CWK_PEWI_AUXADC_PD, "pewi_auxadc_pd", "cwkxtaw", 27),
	GATE_PEWI0(CWK_PEWI_SPI0_PD, "pewi_spi0_pd", "spi0_sew", 28),
	GATE_PEWI0(CWK_PEWI_SNFI_PD, "pewi_snfi_pd", "nfi_infwa_sew", 29),
	GATE_PEWI0(CWK_PEWI_NFI_PD, "pewi_nfi_pd", "axi_sew", 30),
	GATE_PEWI0(CWK_PEWI_NFIECC_PD, "pewi_nfiecc_pd", "axi_sew", 31),

	/* PEWI1 */
	GATE_PEWI1(CWK_PEWI_FWASH_PD, "pewi_fwash_pd", "fwash_sew", 1),
	GATE_PEWI1(CWK_PEWI_IWTX_PD, "pewi_iwtx_pd", "iwtx_sew", 2),
};

static stwuct mtk_composite top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_FWAGS(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
		       0x040, 0, 3, 7, CWK_IS_CWITICAW),
	MUX_GATE_FWAGS(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents,
		       0x040, 8, 1, 15, CWK_IS_CWITICAW),
	MUX_GATE_FWAGS(CWK_TOP_DDWPHYCFG_SEW, "ddwphycfg_sew", ddwphycfg_pawents,
		       0x040, 16, 1, 23, CWK_IS_CWITICAW),
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
	MUX_GATE(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew", msdc30_0_pawents,
		 0x070, 8, 3, 15),
	MUX_GATE(CWK_TOP_A1SYS_HP_SEW, "a1sys_hp_sew", a1sys_hp_pawents,
		 0x070, 16, 2, 23),
	MUX_GATE(CWK_TOP_A2SYS_HP_SEW, "a2sys_hp_sew", a1sys_hp_pawents,
		 0x070, 24, 2, 31),

	/* CWK_CFG_4 */
	MUX_GATE(CWK_TOP_INTDIW_SEW, "intdiw_sew", intdiw_pawents,
		 0x080, 0, 2, 7),
	MUX_GATE(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		 0x080, 8, 2, 15),
	MUX_GATE(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents,
		 0x080, 16, 3, 23),
	MUX_GATE(CWK_TOP_SCP_SEW, "scp_sew", ddwphycfg_pawents,
		 0x080, 24, 2, 31),

	/* CWK_CFG_5 */
	MUX_GATE(CWK_TOP_ATB_SEW, "atb_sew", atb_pawents,
		 0x090, 0, 2, 7),
	MUX_GATE(CWK_TOP_HIF_SEW, "hif_sew", eth_pawents,
		 0x090, 8, 3, 15),
	MUX_GATE(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents,
		 0x090, 16, 2, 23),
	MUX_GATE(CWK_TOP_U2_SEW, "usb20_sew", usb20_pawents,
		 0x090, 24, 2, 31),

	/* CWK_CFG_6 */
	MUX_GATE(CWK_TOP_AUD1_SEW, "aud1_sew", aud1_pawents,
		 0x0A0, 0, 1, 7),
	MUX_GATE(CWK_TOP_AUD2_SEW, "aud2_sew", aud2_pawents,
		 0x0A0, 8, 1, 15),
	MUX_GATE(CWK_TOP_IWWX_SEW, "iwwx_sew", f10m_wef_pawents,
		 0x0A0, 16, 1, 23),
	MUX_GATE(CWK_TOP_IWTX_SEW, "iwtx_sew", f10m_wef_pawents,
		 0x0A0, 24, 1, 31),

	/* CWK_CFG_7 */
	MUX_GATE(CWK_TOP_ASM_W_SEW, "asm_w_sew", asm_w_pawents,
		 0x0B0, 0, 2, 7),
	MUX_GATE(CWK_TOP_ASM_M_SEW, "asm_m_sew", asm_w_pawents,
		 0x0B0, 8, 2, 15),
	MUX_GATE(CWK_TOP_ASM_H_SEW, "asm_h_sew", asm_w_pawents,
		 0x0B0, 16, 2, 23),

	/* CWK_AUDDIV_0 */
	MUX(CWK_TOP_APWW1_SEW, "apww1_ck_sew", apww1_ck_pawents,
	    0x120, 6, 1),
	MUX(CWK_TOP_APWW2_SEW, "apww2_ck_sew", apww1_ck_pawents,
	    0x120, 7, 1),
	MUX(CWK_TOP_I2S0_MCK_SEW, "i2s0_mck_sew", apww1_ck_pawents,
	    0x120, 8, 1),
	MUX(CWK_TOP_I2S1_MCK_SEW, "i2s1_mck_sew", apww1_ck_pawents,
	    0x120, 9, 1),
	MUX(CWK_TOP_I2S2_MCK_SEW, "i2s2_mck_sew", apww1_ck_pawents,
	    0x120, 10, 1),
	MUX(CWK_TOP_I2S3_MCK_SEW, "i2s3_mck_sew", apww1_ck_pawents,
	    0x120, 11, 1),
};

static stwuct mtk_composite pewi_muxes[] = {
	/* PEWI_GWOBAWCON_CKSEW */
	MUX(CWK_PEWIBUS_SEW, "pewibus_ck_sew", pewibus_ck_pawents, 0x05C, 0, 1),
};

static u16 pewicfg_wst_ofs[] = { 0x0, 0x4, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = pewicfg_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(pewicfg_wst_ofs),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.cwks = top_cwks,
	.num_cwks = AWWAY_SIZE(top_cwks),
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.composite_cwks = top_muxes,
	.num_composite_cwks = AWWAY_SIZE(top_muxes),
	.dividew_cwks = top_adj_divs,
	.num_dividew_cwks = AWWAY_SIZE(top_adj_divs),
	.cwk_wock = &mt7622_cwk_wock,
};

static const stwuct mtk_cwk_desc pewi_desc = {
	.cwks = pewi_cwks,
	.num_cwks = AWWAY_SIZE(pewi_cwks),
	.composite_cwks = pewi_muxes,
	.num_composite_cwks = AWWAY_SIZE(pewi_muxes),
	.wst_desc = &cwk_wst_desc,
	.cwk_wock = &mt7622_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt7622[] = {
	{ .compatibwe = "mediatek,mt7622-topckgen", .data = &topck_desc },
	{ .compatibwe = "mediatek,mt7622-pewicfg", .data = &pewi_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7622);

static stwuct pwatfowm_dwivew cwk_mt7622_dwv = {
	.dwivew = {
		.name = "cwk-mt7622",
		.of_match_tabwe = of_match_cwk_mt7622,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt7622_dwv)

MODUWE_DESCWIPTION("MediaTek MT7622 cwocks dwivew");
MODUWE_WICENSE("GPW");
