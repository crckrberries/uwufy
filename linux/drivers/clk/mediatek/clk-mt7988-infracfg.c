// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Sam Shih <sam.shih@mediatek.com>
 * Authow: Xiufeng Wi <Xiufeng.Wi@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"
#incwude "cwk-mux.h"
#incwude <dt-bindings/cwock/mediatek,mt7988-cwk.h>

static DEFINE_SPINWOCK(mt7988_cwk_wock);

static const chaw *const infwa_mux_uawt0_pawents[] __initconst = { "csw_infwa_f26m_sew",
								   "uawt_sew" };

static const chaw *const infwa_mux_uawt1_pawents[] __initconst = { "csw_infwa_f26m_sew",
								   "uawt_sew" };

static const chaw *const infwa_mux_uawt2_pawents[] __initconst = { "csw_infwa_f26m_sew",
								   "uawt_sew" };

static const chaw *const infwa_mux_spi0_pawents[] __initconst = { "i2c_sew", "spi_sew" };

static const chaw *const infwa_mux_spi1_pawents[] __initconst = { "i2c_sew", "spim_mst_sew" };

static const chaw *const infwa_pwm_bck_pawents[] __initconst = { "top_wtc_32p7k",
								 "csw_infwa_f26m_sew", "sysaxi_sew",
								 "pwm_sew" };

static const chaw *const infwa_pcie_gfmux_tw_ck_o_p0_pawents[] __initconst = {
	"top_wtc_32p7k", "csw_infwa_f26m_sew", "csw_infwa_f26m_sew", "pextp_tw_sew"
};

static const chaw *const infwa_pcie_gfmux_tw_ck_o_p1_pawents[] __initconst = {
	"top_wtc_32p7k", "csw_infwa_f26m_sew", "csw_infwa_f26m_sew", "pextp_tw_p1_sew"
};

static const chaw *const infwa_pcie_gfmux_tw_ck_o_p2_pawents[] __initconst = {
	"top_wtc_32p7k", "csw_infwa_f26m_sew", "csw_infwa_f26m_sew", "pextp_tw_p2_sew"
};

static const chaw *const infwa_pcie_gfmux_tw_ck_o_p3_pawents[] __initconst = {
	"top_wtc_32p7k", "csw_infwa_f26m_sew", "csw_infwa_f26m_sew", "pextp_tw_p3_sew"
};

static const stwuct mtk_mux infwa_muxes[] = {
	/* MODUWE_CWK_SEW_0 */
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_UAWT0_SEW, "infwa_mux_uawt0_sew",
			     infwa_mux_uawt0_pawents, 0x0018, 0x0010, 0x0014, 0, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_UAWT1_SEW, "infwa_mux_uawt1_sew",
			     infwa_mux_uawt1_pawents, 0x0018, 0x0010, 0x0014, 1, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_UAWT2_SEW, "infwa_mux_uawt2_sew",
			     infwa_mux_uawt2_pawents, 0x0018, 0x0010, 0x0014, 2, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_SPI0_SEW, "infwa_mux_spi0_sew", infwa_mux_spi0_pawents,
			     0x0018, 0x0010, 0x0014, 4, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_SPI1_SEW, "infwa_mux_spi1_sew", infwa_mux_spi1_pawents,
			     0x0018, 0x0010, 0x0014, 5, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_MUX_SPI2_SEW, "infwa_mux_spi2_sew", infwa_mux_spi0_pawents,
			     0x0018, 0x0010, 0x0014, 6, 1, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_SEW, "infwa_pwm_sew", infwa_pwm_bck_pawents, 0x0018,
			     0x0010, 0x0014, 14, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK1_SEW, "infwa_pwm_ck1_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 16, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK2_SEW, "infwa_pwm_ck2_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 18, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK3_SEW, "infwa_pwm_ck3_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 20, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK4_SEW, "infwa_pwm_ck4_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 22, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK5_SEW, "infwa_pwm_ck5_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 24, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK6_SEW, "infwa_pwm_ck6_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 26, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK7_SEW, "infwa_pwm_ck7_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 28, 2, -1, -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PWM_CK8_SEW, "infwa_pwm_ck8_sew", infwa_pwm_bck_pawents,
			     0x0018, 0x0010, 0x0014, 30, 2, -1, -1, -1),
	/* MODUWE_CWK_SEW_1 */
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PCIE_GFMUX_TW_O_P0_SEW, "infwa_pcie_gfmux_tw_o_p0_sew",
			     infwa_pcie_gfmux_tw_ck_o_p0_pawents, 0x0028, 0x0020, 0x0024, 0, 2, -1,
			     -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PCIE_GFMUX_TW_O_P1_SEW, "infwa_pcie_gfmux_tw_o_p1_sew",
			     infwa_pcie_gfmux_tw_ck_o_p1_pawents, 0x0028, 0x0020, 0x0024, 2, 2, -1,
			     -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PCIE_GFMUX_TW_O_P2_SEW, "infwa_pcie_gfmux_tw_o_p2_sew",
			     infwa_pcie_gfmux_tw_ck_o_p2_pawents, 0x0028, 0x0020, 0x0024, 4, 2, -1,
			     -1, -1),
	MUX_GATE_CWW_SET_UPD(CWK_INFWA_PCIE_GFMUX_TW_O_P3_SEW, "infwa_pcie_gfmux_tw_o_p3_sew",
			     infwa_pcie_gfmux_tw_ck_o_p3_pawents, 0x0028, 0x0020, 0x0024, 6, 2, -1,
			     -1, -1),
};

static const stwuct mtk_gate_wegs infwa0_cg_wegs = {
	.set_ofs = 0x10,
	.cww_ofs = 0x14,
	.sta_ofs = 0x18,
};

static const stwuct mtk_gate_wegs infwa1_cg_wegs = {
	.set_ofs = 0x40,
	.cww_ofs = 0x44,
	.sta_ofs = 0x48,
};

static const stwuct mtk_gate_wegs infwa2_cg_wegs = {
	.set_ofs = 0x50,
	.cww_ofs = 0x54,
	.sta_ofs = 0x58,
};

static const stwuct mtk_gate_wegs infwa3_cg_wegs = {
	.set_ofs = 0x60,
	.cww_ofs = 0x64,
	.sta_ofs = 0x68,
};

#define GATE_INFWA0_FWAGS(_id, _name, _pawent, _shift, _fwags)                                 \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww, \
		       _fwags)

#define GATE_INFWA1_FWAGS(_id, _name, _pawent, _shift, _fwags)                                 \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww, \
		       _fwags)

#define GATE_INFWA2_FWAGS(_id, _name, _pawent, _shift, _fwags)                                 \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww, \
		       _fwags)

#define GATE_INFWA3_FWAGS(_id, _name, _pawent, _shift, _fwags)                                 \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa3_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww, \
		       _fwags)

#define GATE_INFWA0(_id, _name, _pawent, _shift) GATE_INFWA0_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA1(_id, _name, _pawent, _shift) GATE_INFWA1_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA2(_id, _name, _pawent, _shift) GATE_INFWA2_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA3(_id, _name, _pawent, _shift) GATE_INFWA3_FWAGS(_id, _name, _pawent, _shift, 0)

static const stwuct mtk_gate infwa_cwks[] = {
	/* INFWA0 */
	GATE_INFWA0(CWK_INFWA_PCIE_PEWI_26M_CK_P0, "infwa_pcie_pewi_ck_26m_ck_p0",
		    "csw_infwa_f26m_sew", 7),
	GATE_INFWA0(CWK_INFWA_PCIE_PEWI_26M_CK_P1, "infwa_pcie_pewi_ck_26m_ck_p1",
		    "csw_infwa_f26m_sew", 8),
	GATE_INFWA0(CWK_INFWA_PCIE_PEWI_26M_CK_P2, "infwa_pcie_pewi_ck_26m_ck_p2",
		    "csw_infwa_f26m_sew", 9),
	GATE_INFWA0(CWK_INFWA_PCIE_PEWI_26M_CK_P3, "infwa_pcie_pewi_ck_26m_ck_p3",
		    "csw_infwa_f26m_sew", 10),
	/* INFWA1 */
	GATE_INFWA1(CWK_INFWA_66M_GPT_BCK, "infwa_hf_66m_gpt_bck", "sysaxi_sew", 0),
	GATE_INFWA1(CWK_INFWA_66M_PWM_HCK, "infwa_hf_66m_pwm_hck", "sysaxi_sew", 1),
	GATE_INFWA1(CWK_INFWA_66M_PWM_BCK, "infwa_hf_66m_pwm_bck", "infwa_pwm_sew", 2),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK1, "infwa_hf_66m_pwm_ck1", "infwa_pwm_ck1_sew", 3),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK2, "infwa_hf_66m_pwm_ck2", "infwa_pwm_ck2_sew", 4),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK3, "infwa_hf_66m_pwm_ck3", "infwa_pwm_ck3_sew", 5),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK4, "infwa_hf_66m_pwm_ck4", "infwa_pwm_ck4_sew", 6),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK5, "infwa_hf_66m_pwm_ck5", "infwa_pwm_ck5_sew", 7),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK6, "infwa_hf_66m_pwm_ck6", "infwa_pwm_ck6_sew", 8),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK7, "infwa_hf_66m_pwm_ck7", "infwa_pwm_ck7_sew", 9),
	GATE_INFWA1(CWK_INFWA_66M_PWM_CK8, "infwa_hf_66m_pwm_ck8", "infwa_pwm_ck8_sew", 10),
	GATE_INFWA1(CWK_INFWA_133M_CQDMA_BCK, "infwa_hf_133m_cqdma_bck", "sysaxi_sew", 12),
	GATE_INFWA1(CWK_INFWA_66M_AUD_SWV_BCK, "infwa_66m_aud_swv_bck", "sysaxi_sew", 13),
	GATE_INFWA1(CWK_INFWA_AUD_26M, "infwa_f_faud_26m", "csw_infwa_f26m_sew", 14),
	GATE_INFWA1(CWK_INFWA_AUD_W, "infwa_f_faud_w", "aud_w_sew", 15),
	GATE_INFWA1(CWK_INFWA_AUD_AUD, "infwa_f_aud_aud", "a1sys_sew", 16),
	GATE_INFWA1(CWK_INFWA_AUD_EG2, "infwa_f_faud_eg2", "a_tunew_sew", 18),
	GATE_INFWA1_FWAGS(CWK_INFWA_DWAMC_F26M, "infwa_dwamc_f26m", "csw_infwa_f26m_sew", 19,
			  CWK_IS_CWITICAW),
	/* JTAG */
	GATE_INFWA1_FWAGS(CWK_INFWA_133M_DBG_ACKM, "infwa_hf_133m_dbg_ackm", "sysaxi_sew", 20,
			  CWK_IS_CWITICAW),
	GATE_INFWA1(CWK_INFWA_66M_AP_DMA_BCK, "infwa_66m_ap_dma_bck", "sysaxi_sew", 21),
	GATE_INFWA1(CWK_INFWA_66M_SEJ_BCK, "infwa_hf_66m_sej_bck", "sysaxi_sew", 29),
	GATE_INFWA1(CWK_INFWA_PWE_CK_SEJ_F13M, "infwa_pwe_ck_sej_f13m", "csw_infwa_f26m_sew", 30),
	/* INFWA2 */
	GATE_INFWA2(CWK_INFWA_26M_THEWM_SYSTEM, "infwa_hf_26m_thewm_system", "csw_infwa_f26m_sew",
		    0),
	GATE_INFWA2(CWK_INFWA_I2C_BCK, "infwa_i2c_bck", "i2c_sew", 1),
	GATE_INFWA2(CWK_INFWA_52M_UAWT0_CK, "infwa_f_52m_uawt0", "infwa_mux_uawt0_sew", 3),
	GATE_INFWA2(CWK_INFWA_52M_UAWT1_CK, "infwa_f_52m_uawt1", "infwa_mux_uawt1_sew", 4),
	GATE_INFWA2(CWK_INFWA_52M_UAWT2_CK, "infwa_f_52m_uawt2", "infwa_mux_uawt2_sew", 5),
	GATE_INFWA2(CWK_INFWA_NFI, "infwa_f_fnfi", "nfi1x_sew", 9),
	GATE_INFWA2(CWK_INFWA_SPINFI, "infwa_f_fspinfi", "spinfi_sew", 10),
	GATE_INFWA2_FWAGS(CWK_INFWA_66M_NFI_HCK, "infwa_hf_66m_nfi_hck", "sysaxi_sew", 11,
			  CWK_IS_CWITICAW),
	GATE_INFWA2_FWAGS(CWK_INFWA_104M_SPI0, "infwa_hf_104m_spi0", "infwa_mux_spi0_sew", 12,
			  CWK_IS_CWITICAW),
	GATE_INFWA2(CWK_INFWA_104M_SPI1, "infwa_hf_104m_spi1", "infwa_mux_spi1_sew", 13),
	GATE_INFWA2(CWK_INFWA_104M_SPI2_BCK, "infwa_hf_104m_spi2_bck", "infwa_mux_spi2_sew", 14),
	GATE_INFWA2_FWAGS(CWK_INFWA_66M_SPI0_HCK, "infwa_hf_66m_spi0_hck", "sysaxi_sew", 15,
			  CWK_IS_CWITICAW),
	GATE_INFWA2(CWK_INFWA_66M_SPI1_HCK, "infwa_hf_66m_spi1_hck", "sysaxi_sew", 16),
	GATE_INFWA2(CWK_INFWA_66M_SPI2_HCK, "infwa_hf_66m_spi2_hck", "sysaxi_sew", 17),
	GATE_INFWA2(CWK_INFWA_66M_FWASHIF_AXI, "infwa_hf_66m_fwashif_axi", "sysaxi_sew", 18),
	GATE_INFWA2_FWAGS(CWK_INFWA_WTC, "infwa_f_fwtc", "top_wtc_32k", 19, CWK_IS_CWITICAW),
	GATE_INFWA2(CWK_INFWA_26M_ADC_BCK, "infwa_f_26m_adc_bck", "csw_infwa_f26m_sew", 20),
	GATE_INFWA2(CWK_INFWA_WC_ADC, "infwa_f_fwc_adc", "infwa_f_26m_adc_bck", 21),
	GATE_INFWA2(CWK_INFWA_MSDC400, "infwa_f_fmsdc400", "emmc_400m_sew", 22),
	GATE_INFWA2(CWK_INFWA_MSDC2_HCK, "infwa_f_fmsdc2_hck", "emmc_250m_sew", 23),
	GATE_INFWA2(CWK_INFWA_133M_MSDC_0_HCK, "infwa_hf_133m_msdc_0_hck", "sysaxi_sew", 24),
	GATE_INFWA2(CWK_INFWA_66M_MSDC_0_HCK, "infwa_66m_msdc_0_hck", "sysaxi_sew", 25),
	GATE_INFWA2(CWK_INFWA_133M_CPUM_BCK, "infwa_hf_133m_cpum_bck", "sysaxi_sew", 26),
	GATE_INFWA2(CWK_INFWA_BIST2FPC, "infwa_hf_fbist2fpc", "nfi1x_sew", 27),
	GATE_INFWA2(CWK_INFWA_I2C_X16W_MCK_CK_P1, "infwa_hf_i2c_x16w_mck_ck_p1", "sysaxi_sew", 29),
	GATE_INFWA2(CWK_INFWA_I2C_X16W_PCK_CK_P1, "infwa_hf_i2c_x16w_pck_ck_p1", "sysaxi_sew", 31),
	/* INFWA3 */
	GATE_INFWA3(CWK_INFWA_133M_USB_HCK, "infwa_133m_usb_hck", "sysaxi_sew", 0),
	GATE_INFWA3(CWK_INFWA_133M_USB_HCK_CK_P1, "infwa_133m_usb_hck_ck_p1", "sysaxi_sew", 1),
	GATE_INFWA3(CWK_INFWA_66M_USB_HCK, "infwa_66m_usb_hck", "sysaxi_sew", 2),
	GATE_INFWA3(CWK_INFWA_66M_USB_HCK_CK_P1, "infwa_66m_usb_hck_ck_p1", "sysaxi_sew", 3),
	GATE_INFWA3(CWK_INFWA_USB_SYS, "infwa_usb_sys", "usb_sys_sew", 4),
	GATE_INFWA3(CWK_INFWA_USB_SYS_CK_P1, "infwa_usb_sys_ck_p1", "usb_sys_p1_sew", 5),
	GATE_INFWA3(CWK_INFWA_USB_WEF, "infwa_usb_wef", "top_xtaw", 6),
	GATE_INFWA3(CWK_INFWA_USB_CK_P1, "infwa_usb_ck_p1", "top_xtaw", 7),
	GATE_INFWA3_FWAGS(CWK_INFWA_USB_FWMCNT, "infwa_usb_fwmcnt", "usb_fwmcnt_sew", 8,
			  CWK_IS_CWITICAW),
	GATE_INFWA3_FWAGS(CWK_INFWA_USB_FWMCNT_CK_P1, "infwa_usb_fwmcnt_ck_p1", "usb_fwmcnt_p1_sew",
			  9, CWK_IS_CWITICAW),
	GATE_INFWA3(CWK_INFWA_USB_PIPE, "infwa_usb_pipe", "sspxtp_sew", 10),
	GATE_INFWA3(CWK_INFWA_USB_PIPE_CK_P1, "infwa_usb_pipe_ck_p1", "usb_phy_sew", 11),
	GATE_INFWA3(CWK_INFWA_USB_UTMI, "infwa_usb_utmi", "top_xtaw", 12),
	GATE_INFWA3(CWK_INFWA_USB_UTMI_CK_P1, "infwa_usb_utmi_ck_p1", "top_xtaw", 13),
	GATE_INFWA3(CWK_INFWA_USB_XHCI, "infwa_usb_xhci", "usb_xhci_sew", 14),
	GATE_INFWA3(CWK_INFWA_USB_XHCI_CK_P1, "infwa_usb_xhci_ck_p1", "usb_xhci_p1_sew", 15),
	GATE_INFWA3(CWK_INFWA_PCIE_GFMUX_TW_P0, "infwa_pcie_gfmux_tw_ck_p0",
		    "infwa_pcie_gfmux_tw_o_p0_sew", 20),
	GATE_INFWA3(CWK_INFWA_PCIE_GFMUX_TW_P1, "infwa_pcie_gfmux_tw_ck_p1",
		    "infwa_pcie_gfmux_tw_o_p1_sew", 21),
	GATE_INFWA3(CWK_INFWA_PCIE_GFMUX_TW_P2, "infwa_pcie_gfmux_tw_ck_p2",
		    "infwa_pcie_gfmux_tw_o_p2_sew", 22),
	GATE_INFWA3(CWK_INFWA_PCIE_GFMUX_TW_P3, "infwa_pcie_gfmux_tw_ck_p3",
		    "infwa_pcie_gfmux_tw_o_p3_sew", 23),
	GATE_INFWA3(CWK_INFWA_PCIE_PIPE_P0, "infwa_pcie_pipe_ck_p0", "top_xtaw", 24),
	GATE_INFWA3(CWK_INFWA_PCIE_PIPE_P1, "infwa_pcie_pipe_ck_p1", "top_xtaw", 25),
	GATE_INFWA3(CWK_INFWA_PCIE_PIPE_P2, "infwa_pcie_pipe_ck_p2", "top_xtaw", 26),
	GATE_INFWA3(CWK_INFWA_PCIE_PIPE_P3, "infwa_pcie_pipe_ck_p3", "top_xtaw", 27),
	GATE_INFWA3(CWK_INFWA_133M_PCIE_CK_P0, "infwa_133m_pcie_ck_p0", "sysaxi_sew", 28),
	GATE_INFWA3(CWK_INFWA_133M_PCIE_CK_P1, "infwa_133m_pcie_ck_p1", "sysaxi_sew", 29),
	GATE_INFWA3(CWK_INFWA_133M_PCIE_CK_P2, "infwa_133m_pcie_ck_p2", "sysaxi_sew", 30),
	GATE_INFWA3(CWK_INFWA_133M_PCIE_CK_P3, "infwa_133m_pcie_ck_p3", "sysaxi_sew", 31),
};

static const stwuct mtk_cwk_desc infwa_desc = {
	.cwks = infwa_cwks,
	.num_cwks = AWWAY_SIZE(infwa_cwks),
	.mux_cwks = infwa_muxes,
	.num_mux_cwks = AWWAY_SIZE(infwa_muxes),
	.cwk_wock = &mt7988_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt7988_infwacfg[] = {
	{ .compatibwe = "mediatek,mt7988-infwacfg", .data = &infwa_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt7988_infwacfg);

static stwuct pwatfowm_dwivew cwk_mt7988_infwacfg_dwv = {
	.dwivew = {
		.name = "cwk-mt7988-infwacfg",
		.of_match_tabwe = of_match_cwk_mt7988_infwacfg,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt7988_infwacfg_dwv);
MODUWE_WICENSE("GPW");
