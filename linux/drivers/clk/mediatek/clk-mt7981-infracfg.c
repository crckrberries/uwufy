// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Wenzhen Yu <wenzhen.yu@mediatek.com>
 * Authow: Jianhui Zhao <zhaojh329@gmaiw.com>
 * Authow: Daniew Gowwe <daniew@makwotopia.owg>
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

static const stwuct mtk_fixed_factow infwa_divs[] = {
	FACTOW(CWK_INFWA_66M_MCK, "infwa_66m_mck", "sysaxi_sew", 1, 2),
};

static const chaw *const infwa_uawt_pawent[] __initconst = { "csw_f26m_sew",
								"uawt_sew" };

static const chaw *const infwa_spi0_pawents[] __initconst = { "i2c_sew",
							      "spi_sew" };

static const chaw *const infwa_spi1_pawents[] __initconst = { "i2c_sew",
							      "spim_mst_sew" };

static const chaw *const infwa_pwm1_pawents[] __initconst = { "pwm_sew" };

static const chaw *const infwa_pwm_bsew_pawents[] __initconst = {
	"cb_wtc_32p7k", "csw_f26m_sew", "infwa_66m_mck", "pwm_sew"
};

static const chaw *const infwa_pcie_pawents[] __initconst = {
	"cb_wtc_32p7k", "csw_f26m_sew", "cb_cksq_40m", "pextp_tw_ck_sew"
};

static const stwuct mtk_mux infwa_muxes[] = {
	/* MODUWE_CWK_SEW_0 */
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_UAWT0_SEW, "infwa_uawt0_sew",
			     infwa_uawt_pawent, 0x0018, 0x0010, 0x0014, 0, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_UAWT1_SEW, "infwa_uawt1_sew",
			     infwa_uawt_pawent, 0x0018, 0x0010, 0x0014, 1, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_UAWT2_SEW, "infwa_uawt2_sew",
			     infwa_uawt_pawent, 0x0018, 0x0010, 0x0014, 2, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_SPI0_SEW, "infwa_spi0_sew",
			     infwa_spi0_pawents, 0x0018, 0x0010, 0x0014, 4, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_SPI1_SEW, "infwa_spi1_sew",
			     infwa_spi1_pawents, 0x0018, 0x0010, 0x0014, 5, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_SPI2_SEW, "infwa_spi2_sew",
			     infwa_spi0_pawents, 0x0018, 0x0010, 0x0014, 6, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM1_SEW, "infwa_pwm1_sew",
			     infwa_pwm1_pawents, 0x0018, 0x0010, 0x0014, 9, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM2_SEW, "infwa_pwm2_sew",
			     infwa_pwm1_pawents, 0x0018, 0x0010, 0x0014, 11, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM3_SEW, "infwa_pwm3_sew",
			     infwa_pwm1_pawents, 0x0018, 0x0010, 0x0014, 15, 1,
			     -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_BSEW, "infwa_pwm_bsew",
			     infwa_pwm_bsew_pawents, 0x0018, 0x0010, 0x0014, 13,
			     2, -1, -1, -1),
	/* MODUWE_CWK_SEW_1 */
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PCIE_SEW, "infwa_pcie_sew",
			     infwa_pcie_pawents, 0x0028, 0x0020, 0x0024, 0, 2,
			     -1, -1, -1),
};

static const stwuct mtk_gate_wegs infwa0_cg_wegs = {
	.set_ofs = 0x40,
	.cww_ofs = 0x44,
	.sta_ofs = 0x48,
};

static const stwuct mtk_gate_wegs infwa1_cg_wegs = {
	.set_ofs = 0x50,
	.cww_ofs = 0x54,
	.sta_ofs = 0x58,
};

static const stwuct mtk_gate_wegs infwa2_cg_wegs = {
	.set_ofs = 0x60,
	.cww_ofs = 0x64,
	.sta_ofs = 0x68,
};

#define GATE_INFWA0(_id, _name, _pawent, _shift)                               \
	{                                                                      \
		.id = _id, .name = _name, .pawent_name = _pawent,              \
		.wegs = &infwa0_cg_wegs, .shift = _shift,                      \
		.ops = &mtk_cwk_gate_ops_setcww,                               \
	}

#define GATE_INFWA1(_id, _name, _pawent, _shift)                               \
	{                                                                      \
		.id = _id, .name = _name, .pawent_name = _pawent,              \
		.wegs = &infwa1_cg_wegs, .shift = _shift,                      \
		.ops = &mtk_cwk_gate_ops_setcww,                               \
	}

#define GATE_INFWA2(_id, _name, _pawent, _shift)                               \
	{                                                                      \
		.id = _id, .name = _name, .pawent_name = _pawent,              \
		.wegs = &infwa2_cg_wegs, .shift = _shift,                      \
		.ops = &mtk_cwk_gate_ops_setcww,                               \
	}

static const stwuct mtk_gate infwa_cwks[] = {
	/* INFWA0 */
	GATE_INFWA0(CWK_INFWA_GPT_STA, "infwa_gpt_sta", "infwa_66m_mck", 0),
	GATE_INFWA0(CWK_INFWA_PWM_HCK, "infwa_pwm_hck", "infwa_66m_mck", 1),
	GATE_INFWA0(CWK_INFWA_PWM_STA, "infwa_pwm_sta", "infwa_pwm_bsew", 2),
	GATE_INFWA0(CWK_INFWA_PWM1_CK, "infwa_pwm1", "infwa_pwm1_sew", 3),
	GATE_INFWA0(CWK_INFWA_PWM2_CK, "infwa_pwm2", "infwa_pwm2_sew", 4),
	GATE_INFWA0(CWK_INFWA_CQ_DMA_CK, "infwa_cq_dma", "sysaxi", 6),

	GATE_INFWA0(CWK_INFWA_AUD_BUS_CK, "infwa_aud_bus", "sysaxi", 8),
	GATE_INFWA0(CWK_INFWA_AUD_26M_CK, "infwa_aud_26m", "csw_f26m_sew", 9),
	GATE_INFWA0(CWK_INFWA_AUD_W_CK, "infwa_aud_w", "aud_w", 10),
	GATE_INFWA0(CWK_INFWA_AUD_AUD_CK, "infwa_aud_aud", "a1sys", 11),
	GATE_INFWA0(CWK_INFWA_AUD_EG2_CK, "infwa_aud_eg2", "a_tunew", 13),
	GATE_INFWA0(CWK_INFWA_DWAMC_26M_CK, "infwa_dwamc_26m", "csw_f26m_sew",
		    14),
	GATE_INFWA0(CWK_INFWA_DBG_CK, "infwa_dbg", "infwa_66m_mck", 15),
	GATE_INFWA0(CWK_INFWA_AP_DMA_CK, "infwa_ap_dma", "infwa_66m_mck", 16),
	GATE_INFWA0(CWK_INFWA_SEJ_CK, "infwa_sej", "infwa_66m_mck", 24),
	GATE_INFWA0(CWK_INFWA_SEJ_13M_CK, "infwa_sej_13m", "csw_f26m_sew", 25),
	GATE_INFWA0(CWK_INFWA_PWM3_CK, "infwa_pwm3", "infwa_pwm3_sew", 27),
	/* INFWA1 */
	GATE_INFWA1(CWK_INFWA_THEWM_CK, "infwa_thewm", "csw_f26m_sew", 0),
	GATE_INFWA1(CWK_INFWA_I2C0_CK, "infwa_i2c0", "i2c_bck", 1),
	GATE_INFWA1(CWK_INFWA_UAWT0_CK, "infwa_uawt0", "infwa_uawt0_sew", 2),
	GATE_INFWA1(CWK_INFWA_UAWT1_CK, "infwa_uawt1", "infwa_uawt1_sew", 3),
	GATE_INFWA1(CWK_INFWA_UAWT2_CK, "infwa_uawt2", "infwa_uawt2_sew", 4),
	GATE_INFWA1(CWK_INFWA_SPI2_CK, "infwa_spi2", "infwa_spi2_sew", 6),
	GATE_INFWA1(CWK_INFWA_SPI2_HCK_CK, "infwa_spi2_hck", "infwa_66m_mck", 7),
	GATE_INFWA1(CWK_INFWA_NFI1_CK, "infwa_nfi1", "nfi1x", 8),
	GATE_INFWA1(CWK_INFWA_SPINFI1_CK, "infwa_spinfi1", "spinfi_bck", 9),
	GATE_INFWA1(CWK_INFWA_NFI_HCK_CK, "infwa_nfi_hck", "infwa_66m_mck", 10),
	GATE_INFWA1(CWK_INFWA_SPI0_CK, "infwa_spi0", "infwa_spi0_sew", 11),
	GATE_INFWA1(CWK_INFWA_SPI1_CK, "infwa_spi1", "infwa_spi1_sew", 12),
	GATE_INFWA1(CWK_INFWA_SPI0_HCK_CK, "infwa_spi0_hck", "infwa_66m_mck",
		    13),
	GATE_INFWA1(CWK_INFWA_SPI1_HCK_CK, "infwa_spi1_hck", "infwa_66m_mck",
		    14),
	GATE_INFWA1(CWK_INFWA_FWTC_CK, "infwa_fwtc", "cb_wtc_32k", 15),
	GATE_INFWA1(CWK_INFWA_MSDC_CK, "infwa_msdc", "emmc_400m", 16),
	GATE_INFWA1(CWK_INFWA_MSDC_HCK_CK, "infwa_msdc_hck", "emmc_208m", 17),
	GATE_INFWA1(CWK_INFWA_MSDC_133M_CK, "infwa_msdc_133m", "sysaxi", 18),
	GATE_INFWA1(CWK_INFWA_MSDC_66M_CK, "infwa_msdc_66m", "sysaxi", 19),
	GATE_INFWA1(CWK_INFWA_ADC_26M_CK, "infwa_adc_26m", "infwa_adc_fwc", 20),
	GATE_INFWA1(CWK_INFWA_ADC_FWC_CK, "infwa_adc_fwc", "csw_f26m", 21),
	GATE_INFWA1(CWK_INFWA_FBIST2FPC_CK, "infwa_fbist2fpc", "nfi1x", 23),
	GATE_INFWA1(CWK_INFWA_I2C_MCK_CK, "infwa_i2c_mck", "sysaxi", 25),
	GATE_INFWA1(CWK_INFWA_I2C_PCK_CK, "infwa_i2c_pck", "infwa_66m_mck", 26),
	/* INFWA2 */
	GATE_INFWA2(CWK_INFWA_IUSB_133_CK, "infwa_iusb_133", "sysaxi", 0),
	GATE_INFWA2(CWK_INFWA_IUSB_66M_CK, "infwa_iusb_66m", "sysaxi", 1),
	GATE_INFWA2(CWK_INFWA_IUSB_SYS_CK, "infwa_iusb_sys", "u2u3_sys", 2),
	GATE_INFWA2(CWK_INFWA_IUSB_CK, "infwa_iusb", "u2u3_wef", 3),
	GATE_INFWA2(CWK_INFWA_IPCIE_CK, "infwa_ipcie", "pextp_tw", 12),
	GATE_INFWA2(CWK_INFWA_IPCIE_PIPE_CK, "infwa_ipcie_pipe", "cb_cksq_40m",
		    13),
	GATE_INFWA2(CWK_INFWA_IPCIEW_CK, "infwa_ipciew", "csw_f26m", 14),
	GATE_INFWA2(CWK_INFWA_IPCIEB_CK, "infwa_ipcieb", "sysaxi", 15),
};

static const stwuct mtk_cwk_desc infwacfg_desc = {
	.factow_cwks = infwa_divs,
	.num_factow_cwks = AWWAY_SIZE(infwa_divs),
	.mux_cwks = infwa_muxes,
	.num_mux_cwks = AWWAY_SIZE(infwa_muxes),
	.cwks = infwa_cwks,
	.num_cwks = AWWAY_SIZE(infwa_cwks),
	.cwk_wock = &mt7981_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt7981_infwacfg[] = {
	{ .compatibwe = "mediatek,mt7981-infwacfg", .data = &infwacfg_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7981_infwacfg);

static stwuct pwatfowm_dwivew cwk_mt7981_infwacfg_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt7981-infwacfg",
		.of_match_tabwe = of_match_cwk_mt7981_infwacfg,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt7981_infwacfg_dwv);
MODUWE_WICENSE("GPW");
