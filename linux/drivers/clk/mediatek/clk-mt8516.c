// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 *         Fabien Pawent <fpawent@baywibwe.com>
 * Copywight (c) 2023 Cowwabowa Wtd.
 */

#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8516-cwk.h>

static DEFINE_SPINWOCK(mt8516_cwk_wock);

static const stwuct mtk_fixed_cwk fixed_cwks[] __initconst = {
	FIXED_CWK(CWK_TOP_CWK_NUWW, "cwk_nuww", NUWW, 0),
	FIXED_CWK(CWK_TOP_I2S_INFWA_BCK, "i2s_infwa_bck", "cwk_nuww", 26000000),
	FIXED_CWK(CWK_TOP_MEMPWW, "mempww", "cwk26m", 800000000),
};

static const stwuct mtk_fixed_factow top_divs[] __initconst = {
	FACTOW(CWK_TOP_DMPWW, "dmpww_ck", "mempww", 1, 1),
	FACTOW(CWK_TOP_MAINPWW_D2, "mainpww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_MAINPWW_D4, "mainpww_d4", "mainpww", 1, 4),
	FACTOW(CWK_TOP_MAINPWW_D8, "mainpww_d8", "mainpww", 1, 8),
	FACTOW(CWK_TOP_MAINPWW_D16, "mainpww_d16", "mainpww", 1, 16),
	FACTOW(CWK_TOP_MAINPWW_D11, "mainpww_d11", "mainpww", 1, 11),
	FACTOW(CWK_TOP_MAINPWW_D22, "mainpww_d22", "mainpww", 1, 22),
	FACTOW(CWK_TOP_MAINPWW_D3, "mainpww_d3", "mainpww", 1, 3),
	FACTOW(CWK_TOP_MAINPWW_D6, "mainpww_d6", "mainpww", 1, 6),
	FACTOW(CWK_TOP_MAINPWW_D12, "mainpww_d12", "mainpww", 1, 12),
	FACTOW(CWK_TOP_MAINPWW_D5, "mainpww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_MAINPWW_D10, "mainpww_d10", "mainpww", 1, 10),
	FACTOW(CWK_TOP_MAINPWW_D20, "mainpww_d20", "mainpww", 1, 20),
	FACTOW(CWK_TOP_MAINPWW_D40, "mainpww_d40", "mainpww", 1, 40),
	FACTOW(CWK_TOP_MAINPWW_D7, "mainpww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_MAINPWW_D14, "mainpww_d14", "mainpww", 1, 14),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_D4, "univpww_d4", "univpww", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW_D8, "univpww_d8", "univpww", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D16, "univpww_d16", "univpww", 1, 16),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW_D6, "univpww_d6", "univpww", 1, 6),
	FACTOW(CWK_TOP_UNIVPWW_D12, "univpww_d12", "univpww", 1, 12),
	FACTOW(CWK_TOP_UNIVPWW_D24, "univpww_d24", "univpww", 1, 24),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW_D20, "univpww_d20", "univpww", 1, 20),
	FACTOW(CWK_TOP_MMPWW380M, "mmpww380m", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_MMPWW_200M, "mmpww_200m", "mmpww", 1, 3),
	FACTOW(CWK_TOP_USB_PHY48M, "usb_phy48m_ck", "univpww", 1, 26),
	FACTOW(CWK_TOP_APWW1, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW1_D2, "apww1_d2", "apww1_ck", 1, 2),
	FACTOW(CWK_TOP_APWW1_D4, "apww1_d4", "wg_apww1_d2_en", 1, 2),
	FACTOW(CWK_TOP_APWW1_D8, "apww1_d8", "wg_apww1_d4_en", 1, 2),
	FACTOW(CWK_TOP_APWW2, "apww2_ck", "apww2", 1, 1),
	FACTOW(CWK_TOP_APWW2_D2, "apww2_d2", "apww2_ck", 1, 2),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "wg_apww2_d2_en", 1, 2),
	FACTOW(CWK_TOP_APWW2_D8, "apww2_d8", "wg_apww2_d4_en", 1, 2),
	FACTOW(CWK_TOP_CWK26M, "cwk26m_ck", "cwk26m", 1, 1),
	FACTOW(CWK_TOP_CWK26M_D2, "cwk26m_d2", "cwk26m", 1, 2),
	FACTOW(CWK_TOP_AHB_INFWA_D2, "ahb_infwa_d2", "ahb_infwa_sew", 1, 2),
	FACTOW(CWK_TOP_NFI1X, "nfi1x_ck", "nfi2x_pad_sew", 1, 2),
	FACTOW(CWK_TOP_ETH_D2, "eth_d2_ck", "eth_sew", 1, 2),
};

static const chaw * const uawt0_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d24"
};

static const chaw * const ahb_infwa_pawents[] __initconst = {
	"cwk_nuww",
	"cwk26m_ck",
	"mainpww_d11",
	"cwk_nuww",
	"mainpww_d12",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"mainpww_d10"
};

static const chaw * const msdc0_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d6",
	"mainpww_d8",
	"univpww_d8",
	"mainpww_d16",
	"mmpww_200m",
	"mainpww_d12",
	"mmpww_d2"
};

static const chaw * const uawt1_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d24"
};

static const chaw * const msdc1_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d6",
	"mainpww_d8",
	"univpww_d8",
	"mainpww_d16",
	"mmpww_200m",
	"mainpww_d12",
	"mmpww_d2"
};

static const chaw * const pmicspi_pawents[] __initconst = {
	"univpww_d20",
	"usb_phy48m_ck",
	"univpww_d16",
	"cwk26m_ck"
};

static const chaw * const qaxi_aud26m_pawents[] __initconst = {
	"cwk26m_ck",
	"ahb_infwa_sew"
};

static const chaw * const aud_intbus_pawents[] __initconst = {
	"cwk_nuww",
	"cwk26m_ck",
	"mainpww_d22",
	"cwk_nuww",
	"mainpww_d11"
};

static const chaw * const nfi2x_pad_pawents[] __initconst = {
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk26m_ck",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"mainpww_d12",
	"mainpww_d8",
	"cwk_nuww",
	"mainpww_d6",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"mainpww_d4",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"cwk_nuww",
	"mainpww_d10",
	"mainpww_d7",
	"cwk_nuww",
	"mainpww_d5"
};

static const chaw * const nfi1x_pad_pawents[] __initconst = {
	"ahb_infwa_sew",
	"nfi1x_ck"
};

static const chaw * const usb_78m_pawents[] __initconst = {
	"cwk_nuww",
	"cwk26m_ck",
	"univpww_d16",
	"cwk_nuww",
	"mainpww_d20"
};

static const chaw * const spinow_pawents[] __initconst = {
	"cwk26m_d2",
	"cwk26m_ck",
	"mainpww_d40",
	"univpww_d24",
	"univpww_d20",
	"mainpww_d20",
	"mainpww_d16",
	"univpww_d12"
};

static const chaw * const msdc2_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d6",
	"mainpww_d8",
	"univpww_d8",
	"mainpww_d16",
	"mmpww_200m",
	"mainpww_d12",
	"mmpww_d2"
};

static const chaw * const eth_pawents[] __initconst = {
	"cwk26m_ck",
	"mainpww_d40",
	"univpww_d24",
	"univpww_d20",
	"mainpww_d20"
};

static const chaw * const aud1_pawents[] __initconst = {
	"cwk26m_ck",
	"apww1_ck"
};

static const chaw * const aud2_pawents[] __initconst = {
	"cwk26m_ck",
	"apww2_ck"
};

static const chaw * const aud_engen1_pawents[] __initconst = {
	"cwk26m_ck",
	"wg_apww1_d2_en",
	"wg_apww1_d4_en",
	"wg_apww1_d8_en"
};

static const chaw * const aud_engen2_pawents[] __initconst = {
	"cwk26m_ck",
	"wg_apww2_d2_en",
	"wg_apww2_d4_en",
	"wg_apww2_d8_en"
};

static const chaw * const i2c_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d20",
	"univpww_d16",
	"univpww_d12"
};

static const chaw * const aud_i2s0_m_pawents[] __initconst = {
	"wg_aud1",
	"wg_aud2"
};

static const chaw * const pwm_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d12"
};

static const chaw * const spi_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d12",
	"univpww_d8",
	"univpww_d6"
};

static const chaw * const aud_spdifin_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d2"
};

static const chaw * const uawt2_pawents[] __initconst = {
	"cwk26m_ck",
	"univpww_d24"
};

static const chaw * const bsi_pawents[] __initconst = {
	"cwk26m_ck",
	"mainpww_d10",
	"mainpww_d12",
	"mainpww_d20"
};

static const chaw * const dbg_atcwk_pawents[] __initconst = {
	"cwk_nuww",
	"cwk26m_ck",
	"mainpww_d5",
	"cwk_nuww",
	"univpww_d5"
};

static const chaw * const csw_nfiecc_pawents[] __initconst = {
	"cwk_nuww",
	"mainpww_d7",
	"mainpww_d6",
	"cwk_nuww",
	"mainpww_d5"
};

static const chaw * const nfiecc_pawents[] __initconst = {
	"cwk_nuww",
	"nfi2x_pad_sew",
	"mainpww_d4",
	"cwk_nuww",
	"csw_nfiecc_sew"
};

static stwuct mtk_composite top_muxes[] __initdata = {
	/* CWK_MUX_SEW0 */
	MUX(CWK_TOP_UAWT0_SEW, "uawt0_sew", uawt0_pawents,
		0x000, 0, 1),
	MUX(CWK_TOP_AHB_INFWA_SEW, "ahb_infwa_sew", ahb_infwa_pawents,
		0x000, 4, 4),
	MUX(CWK_TOP_MSDC0_SEW, "msdc0_sew", msdc0_pawents,
		0x000, 11, 3),
	MUX(CWK_TOP_UAWT1_SEW, "uawt1_sew", uawt1_pawents,
		0x000, 19, 1),
	MUX(CWK_TOP_MSDC1_SEW, "msdc1_sew", msdc1_pawents,
		0x000, 20, 3),
	MUX(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents,
		0x000, 24, 2),
	MUX(CWK_TOP_QAXI_AUD26M_SEW, "qaxi_aud26m_sew", qaxi_aud26m_pawents,
		0x000, 26, 1),
	MUX(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		0x000, 27, 3),
	/* CWK_MUX_SEW1 */
	MUX(CWK_TOP_NFI2X_PAD_SEW, "nfi2x_pad_sew", nfi2x_pad_pawents,
		0x004, 0, 7),
	MUX(CWK_TOP_NFI1X_PAD_SEW, "nfi1x_pad_sew", nfi1x_pad_pawents,
		0x004, 7, 1),
	MUX(CWK_TOP_USB_78M_SEW, "usb_78m_sew", usb_78m_pawents,
		0x004, 20, 3),
	/* CWK_MUX_SEW8 */
	MUX(CWK_TOP_SPINOW_SEW, "spinow_sew", spinow_pawents,
		0x040, 0, 3),
	MUX(CWK_TOP_MSDC2_SEW, "msdc2_sew", msdc2_pawents,
		0x040, 3, 3),
	MUX(CWK_TOP_ETH_SEW, "eth_sew", eth_pawents,
		0x040, 6, 3),
	MUX(CWK_TOP_AUD1_SEW, "aud1_sew", aud1_pawents,
		0x040, 22, 1),
	MUX(CWK_TOP_AUD2_SEW, "aud2_sew", aud2_pawents,
		0x040, 23, 1),
	MUX(CWK_TOP_AUD_ENGEN1_SEW, "aud_engen1_sew", aud_engen1_pawents,
		0x040, 24, 2),
	MUX(CWK_TOP_AUD_ENGEN2_SEW, "aud_engen2_sew", aud_engen2_pawents,
		0x040, 26, 2),
	MUX(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents,
		0x040, 28, 2),
	/* CWK_SEW_9 */
	MUX(CWK_TOP_AUD_I2S0_M_SEW, "aud_i2s0_m_sew", aud_i2s0_m_pawents,
		0x044, 12, 1),
	MUX(CWK_TOP_AUD_I2S1_M_SEW, "aud_i2s1_m_sew", aud_i2s0_m_pawents,
		0x044, 13, 1),
	MUX(CWK_TOP_AUD_I2S2_M_SEW, "aud_i2s2_m_sew", aud_i2s0_m_pawents,
		0x044, 14, 1),
	MUX(CWK_TOP_AUD_I2S3_M_SEW, "aud_i2s3_m_sew", aud_i2s0_m_pawents,
		0x044, 15, 1),
	MUX(CWK_TOP_AUD_I2S4_M_SEW, "aud_i2s4_m_sew", aud_i2s0_m_pawents,
		0x044, 16, 1),
	MUX(CWK_TOP_AUD_I2S5_M_SEW, "aud_i2s5_m_sew", aud_i2s0_m_pawents,
		0x044, 17, 1),
	MUX(CWK_TOP_AUD_SPDIF_B_SEW, "aud_spdif_b_sew", aud_i2s0_m_pawents,
		0x044, 18, 1),
	/* CWK_MUX_SEW13 */
	MUX(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents,
		0x07c, 0, 1),
	MUX(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents,
		0x07c, 1, 2),
	MUX(CWK_TOP_AUD_SPDIFIN_SEW, "aud_spdifin_sew", aud_spdifin_pawents,
		0x07c, 3, 1),
	MUX(CWK_TOP_UAWT2_SEW, "uawt2_sew", uawt2_pawents,
		0x07c, 4, 1),
	MUX(CWK_TOP_BSI_SEW, "bsi_sew", bsi_pawents,
		0x07c, 5, 2),
	MUX(CWK_TOP_DBG_ATCWK_SEW, "dbg_atcwk_sew", dbg_atcwk_pawents,
		0x07c, 7, 3),
	MUX(CWK_TOP_CSW_NFIECC_SEW, "csw_nfiecc_sew", csw_nfiecc_pawents,
		0x07c, 10, 3),
	MUX(CWK_TOP_NFIECC_SEW, "nfiecc_sew", nfiecc_pawents,
		0x07c, 13, 3),
};

static const chaw * const ifw_mux1_pawents[] __initconst = {
	"cwk26m_ck",
	"awmpww",
	"univpww",
	"mainpww_d2"
};

static const chaw * const ifw_eth_25m_pawents[] __initconst = {
	"eth_d2_ck",
	"wg_eth"
};

static const chaw * const ifw_i2c0_pawents[] __initconst = {
	"ahb_infwa_d2",
	"wg_i2c"
};

static const stwuct mtk_composite ifw_muxes[] __initconst = {
	MUX(CWK_IFW_MUX1_SEW, "ifw_mux1_sew", ifw_mux1_pawents, 0x000,
		2, 2),
	MUX(CWK_IFW_ETH_25M_SEW, "ifw_eth_25m_sew", ifw_eth_25m_pawents, 0x080,
		0, 1),
	MUX(CWK_IFW_I2C0_SEW, "ifw_i2c0_sew", ifw_i2c0_pawents, 0x080,
		1, 1),
	MUX(CWK_IFW_I2C1_SEW, "ifw_i2c1_sew", ifw_i2c0_pawents, 0x080,
		2, 1),
	MUX(CWK_IFW_I2C2_SEW, "ifw_i2c2_sew", ifw_i2c0_pawents, 0x080,
		3, 1),
};

#define DIV_ADJ(_id, _name, _pawent, _weg, _shift, _width) {	\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.div_weg = _weg,				\
		.div_shift = _shift,				\
		.div_width = _width,				\
}

static const stwuct mtk_cwk_dividew top_adj_divs[] = {
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV0, "apww12_ck_div0", "aud_i2s0_m_sew",
		0x0048, 0, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV1, "apww12_ck_div1", "aud_i2s1_m_sew",
		0x0048, 8, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV2, "apww12_ck_div2", "aud_i2s2_m_sew",
		0x0048, 16, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV3, "apww12_ck_div3", "aud_i2s3_m_sew",
		0x0048, 24, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV4, "apww12_ck_div4", "aud_i2s4_m_sew",
		0x004c, 0, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV4B, "apww12_ck_div4b", "apww12_div4",
		0x004c, 8, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV5, "apww12_ck_div5", "aud_i2s5_m_sew",
		0x004c, 16, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV5B, "apww12_ck_div5b", "apww12_div5",
		0x004c, 24, 8),
	DIV_ADJ(CWK_TOP_APWW12_CK_DIV6, "apww12_ck_div6", "aud_spdif_b_sew",
		0x0078, 0, 8),
};

static const stwuct mtk_gate_wegs top1_cg_wegs = {
	.set_ofs = 0x54,
	.cww_ofs = 0x84,
	.sta_ofs = 0x24,
};

static const stwuct mtk_gate_wegs top2_cg_wegs = {
	.set_ofs = 0x6c,
	.cww_ofs = 0x9c,
	.sta_ofs = 0x3c,
};

static const stwuct mtk_gate_wegs top3_cg_wegs = {
	.set_ofs = 0xa0,
	.cww_ofs = 0xb0,
	.sta_ofs = 0x70,
};

static const stwuct mtk_gate_wegs top4_cg_wegs = {
	.set_ofs = 0xa4,
	.cww_ofs = 0xb4,
	.sta_ofs = 0x74,
};

static const stwuct mtk_gate_wegs top5_cg_wegs = {
	.set_ofs = 0x44,
	.cww_ofs = 0x44,
	.sta_ofs = 0x44,
};

#define GATE_TOP1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_TOP2(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_TOP2_I(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_TOP3(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top3_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_TOP4_I(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top4_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_TOP5(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top5_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate top_cwks[] __initconst = {
	/* TOP1 */
	GATE_TOP1(CWK_TOP_THEM, "them", "ahb_infwa_sew", 1),
	GATE_TOP1(CWK_TOP_APDMA, "apdma", "ahb_infwa_sew", 2),
	GATE_TOP1(CWK_TOP_I2C0, "i2c0", "ifw_i2c0_sew", 3),
	GATE_TOP1(CWK_TOP_I2C1, "i2c1", "ifw_i2c1_sew", 4),
	GATE_TOP1(CWK_TOP_AUXADC1, "auxadc1", "ahb_infwa_sew", 5),
	GATE_TOP1(CWK_TOP_NFI, "nfi", "nfi1x_pad_sew", 6),
	GATE_TOP1(CWK_TOP_NFIECC, "nfiecc", "wg_nfiecc", 7),
	GATE_TOP1(CWK_TOP_DEBUGSYS, "debugsys", "wg_dbg_atcwk", 8),
	GATE_TOP1(CWK_TOP_PWM, "pwm", "ahb_infwa_sew", 9),
	GATE_TOP1(CWK_TOP_UAWT0, "uawt0", "uawt0_sew", 10),
	GATE_TOP1(CWK_TOP_UAWT1, "uawt1", "uawt1_sew", 11),
	GATE_TOP1(CWK_TOP_BTIF, "btif", "ahb_infwa_sew", 12),
	GATE_TOP1(CWK_TOP_USB, "usb", "usb_78m", 13),
	GATE_TOP1(CWK_TOP_FWASHIF_26M, "fwashif_26m", "cwk26m_ck", 14),
	GATE_TOP1(CWK_TOP_AUXADC2, "auxadc2", "ahb_infwa_sew", 15),
	GATE_TOP1(CWK_TOP_I2C2, "i2c2", "ifw_i2c2_sew", 16),
	GATE_TOP1(CWK_TOP_MSDC0, "msdc0", "msdc0_sew", 17),
	GATE_TOP1(CWK_TOP_MSDC1, "msdc1", "msdc1_sew", 18),
	GATE_TOP1(CWK_TOP_NFI2X, "nfi2x", "nfi2x_pad_sew", 19),
	GATE_TOP1(CWK_TOP_PMICWWAP_AP, "pwwap_ap", "cwk26m_ck", 20),
	GATE_TOP1(CWK_TOP_SEJ, "sej", "ahb_infwa_sew", 21),
	GATE_TOP1(CWK_TOP_MEMSWP_DWYEW, "memswp_dwyew", "cwk26m_ck", 22),
	GATE_TOP1(CWK_TOP_SPI, "spi", "spi_sew", 23),
	GATE_TOP1(CWK_TOP_APXGPT, "apxgpt", "cwk26m_ck", 24),
	GATE_TOP1(CWK_TOP_AUDIO, "audio", "cwk26m_ck", 25),
	GATE_TOP1(CWK_TOP_PMICWWAP_MD, "pwwap_md", "cwk26m_ck", 27),
	GATE_TOP1(CWK_TOP_PMICWWAP_CONN, "pwwap_conn", "cwk26m_ck", 28),
	GATE_TOP1(CWK_TOP_PMICWWAP_26M, "pwwap_26m", "cwk26m_ck", 29),
	GATE_TOP1(CWK_TOP_AUX_ADC, "aux_adc", "cwk26m_ck", 30),
	GATE_TOP1(CWK_TOP_AUX_TP, "aux_tp", "cwk26m_ck", 31),
	/* TOP2 */
	GATE_TOP2(CWK_TOP_MSDC2, "msdc2", "ahb_infwa_sew", 0),
	GATE_TOP2(CWK_TOP_WBIST, "wbist", "univpww_d12", 1),
	GATE_TOP2(CWK_TOP_NFI_BUS, "nfi_bus", "ahb_infwa_sew", 2),
	GATE_TOP2(CWK_TOP_GCE, "gce", "ahb_infwa_sew", 4),
	GATE_TOP2(CWK_TOP_TWNG, "twng", "ahb_infwa_sew", 5),
	GATE_TOP2(CWK_TOP_SEJ_13M, "sej_13m", "cwk26m_ck", 6),
	GATE_TOP2(CWK_TOP_AES, "aes", "ahb_infwa_sew", 7),
	GATE_TOP2(CWK_TOP_PWM_B, "pwm_b", "wg_pwm_infwa", 8),
	GATE_TOP2(CWK_TOP_PWM1_FB, "pwm1_fb", "wg_pwm_infwa", 9),
	GATE_TOP2(CWK_TOP_PWM2_FB, "pwm2_fb", "wg_pwm_infwa", 10),
	GATE_TOP2(CWK_TOP_PWM3_FB, "pwm3_fb", "wg_pwm_infwa", 11),
	GATE_TOP2(CWK_TOP_PWM4_FB, "pwm4_fb", "wg_pwm_infwa", 12),
	GATE_TOP2(CWK_TOP_PWM5_FB, "pwm5_fb", "wg_pwm_infwa", 13),
	GATE_TOP2(CWK_TOP_USB_1P, "usb_1p", "usb_78m", 14),
	GATE_TOP2(CWK_TOP_FWASHIF_FWEEWUN, "fwashif_fweewun", "ahb_infwa_sew",
		15),
	GATE_TOP2(CWK_TOP_66M_ETH, "eth_66m", "ahb_infwa_d2", 19),
	GATE_TOP2(CWK_TOP_133M_ETH, "eth_133m", "ahb_infwa_sew", 20),
	GATE_TOP2(CWK_TOP_FETH_25M, "feth_25m", "ifw_eth_25m_sew", 21),
	GATE_TOP2(CWK_TOP_FETH_50M, "feth_50m", "wg_eth", 22),
	GATE_TOP2(CWK_TOP_FWASHIF_AXI, "fwashif_axi", "ahb_infwa_sew", 23),
	GATE_TOP2(CWK_TOP_USBIF, "usbif", "ahb_infwa_sew", 24),
	GATE_TOP2(CWK_TOP_UAWT2, "uawt2", "wg_uawt2", 25),
	GATE_TOP2(CWK_TOP_BSI, "bsi", "ahb_infwa_sew", 26),
	GATE_TOP2_I(CWK_TOP_MSDC0_INFWA, "msdc0_infwa", "msdc0", 28),
	GATE_TOP2_I(CWK_TOP_MSDC1_INFWA, "msdc1_infwa", "msdc1", 29),
	GATE_TOP2_I(CWK_TOP_MSDC2_INFWA, "msdc2_infwa", "wg_msdc2", 30),
	GATE_TOP2(CWK_TOP_USB_78M, "usb_78m", "usb_78m_sew", 31),
	/* TOP3 */
	GATE_TOP3(CWK_TOP_WG_SPINOW, "wg_spinow", "spinow_sew", 0),
	GATE_TOP3(CWK_TOP_WG_MSDC2, "wg_msdc2", "msdc2_sew", 1),
	GATE_TOP3(CWK_TOP_WG_ETH, "wg_eth", "eth_sew", 2),
	GATE_TOP3(CWK_TOP_WG_AUD1, "wg_aud1", "aud1_sew", 8),
	GATE_TOP3(CWK_TOP_WG_AUD2, "wg_aud2", "aud2_sew", 9),
	GATE_TOP3(CWK_TOP_WG_AUD_ENGEN1, "wg_aud_engen1", "aud_engen1_sew", 10),
	GATE_TOP3(CWK_TOP_WG_AUD_ENGEN2, "wg_aud_engen2", "aud_engen2_sew", 11),
	GATE_TOP3(CWK_TOP_WG_I2C, "wg_i2c", "i2c_sew", 12),
	GATE_TOP3(CWK_TOP_WG_PWM_INFWA, "wg_pwm_infwa", "pwm_sew", 13),
	GATE_TOP3(CWK_TOP_WG_AUD_SPDIF_IN, "wg_aud_spdif_in", "aud_spdifin_sew",
		14),
	GATE_TOP3(CWK_TOP_WG_UAWT2, "wg_uawt2", "uawt2_sew", 15),
	GATE_TOP3(CWK_TOP_WG_BSI, "wg_bsi", "bsi_sew", 16),
	GATE_TOP3(CWK_TOP_WG_DBG_ATCWK, "wg_dbg_atcwk", "dbg_atcwk_sew", 17),
	GATE_TOP3(CWK_TOP_WG_NFIECC, "wg_nfiecc", "nfiecc_sew", 18),
	/* TOP4 */
	GATE_TOP4_I(CWK_TOP_WG_APWW1_D2_EN, "wg_apww1_d2_en", "apww1_d2", 8),
	GATE_TOP4_I(CWK_TOP_WG_APWW1_D4_EN, "wg_apww1_d4_en", "apww1_d4", 9),
	GATE_TOP4_I(CWK_TOP_WG_APWW1_D8_EN, "wg_apww1_d8_en", "apww1_d8", 10),
	GATE_TOP4_I(CWK_TOP_WG_APWW2_D2_EN, "wg_apww2_d2_en", "apww2_d2", 11),
	GATE_TOP4_I(CWK_TOP_WG_APWW2_D4_EN, "wg_apww2_d4_en", "apww2_d4", 12),
	GATE_TOP4_I(CWK_TOP_WG_APWW2_D8_EN, "wg_apww2_d8_en", "apww2_d8", 13),
	/* TOP5 */
	GATE_TOP5(CWK_TOP_APWW12_DIV0, "apww12_div0", "apww12_ck_div0", 0),
	GATE_TOP5(CWK_TOP_APWW12_DIV1, "apww12_div1", "apww12_ck_div1", 1),
	GATE_TOP5(CWK_TOP_APWW12_DIV2, "apww12_div2", "apww12_ck_div2", 2),
	GATE_TOP5(CWK_TOP_APWW12_DIV3, "apww12_div3", "apww12_ck_div3", 3),
	GATE_TOP5(CWK_TOP_APWW12_DIV4, "apww12_div4", "apww12_ck_div4", 4),
	GATE_TOP5(CWK_TOP_APWW12_DIV4B, "apww12_div4b", "apww12_ck_div4b", 5),
	GATE_TOP5(CWK_TOP_APWW12_DIV5, "apww12_div5", "apww12_ck_div5", 6),
	GATE_TOP5(CWK_TOP_APWW12_DIV5B, "apww12_div5b", "apww12_ck_div5b", 7),
	GATE_TOP5(CWK_TOP_APWW12_DIV6, "apww12_div6", "apww12_ck_div6", 8),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.cwks = top_cwks,
	.num_cwks = AWWAY_SIZE(top_cwks),
	.fixed_cwks = fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.composite_cwks = top_muxes,
	.num_composite_cwks = AWWAY_SIZE(top_muxes),
	.dividew_cwks = top_adj_divs,
	.num_dividew_cwks = AWWAY_SIZE(top_adj_divs),
	.cwk_wock = &mt8516_cwk_wock,
};

static const stwuct mtk_cwk_desc infwa_desc = {
	.composite_cwks = ifw_muxes,
	.num_composite_cwks = AWWAY_SIZE(ifw_muxes),
	.cwk_wock = &mt8516_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt8516[] = {
	{ .compatibwe = "mediatek,mt8516-topckgen", .data = &topck_desc },
	{ .compatibwe = "mediatek,mt8516-infwacfg", .data = &infwa_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8516);

static stwuct pwatfowm_dwivew cwk_mt8516_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8516",
		.of_match_tabwe = of_match_cwk_mt8516,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8516_dwv);

MODUWE_DESCWIPTION("MediaTek MT8516 cwocks dwivew");
MODUWE_WICENSE("GPW");
