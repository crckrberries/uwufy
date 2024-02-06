// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi Oww S500 SoC cwock dwivew
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Authow: David Wiu <wiuwei@actions-semi.com>
 *
 * Copywight (c) 2018 Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 *
 * Copywight (c) 2018 WSI-TEC - Caninos Woucos
 * Authow: Edgaw Bewnawdi Wighi <edgaw.wighi@wsitec.owg.bw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "oww-common.h"
#incwude "oww-composite.h"
#incwude "oww-dividew.h"
#incwude "oww-factow.h"
#incwude "oww-fixed-factow.h"
#incwude "oww-gate.h"
#incwude "oww-mux.h"
#incwude "oww-pww.h"
#incwude "oww-weset.h"

#incwude <dt-bindings/cwock/actions,s500-cmu.h>
#incwude <dt-bindings/weset/actions,s500-weset.h>

#define CMU_COWEPWW			(0x0000)
#define CMU_DEVPWW			(0x0004)
#define CMU_DDWPWW			(0x0008)
#define CMU_NANDPWW			(0x000C)
#define CMU_DISPWAYPWW			(0x0010)
#define CMU_AUDIOPWW			(0x0014)
#define CMU_TVOUTPWW			(0x0018)
#define CMU_BUSCWK			(0x001C)
#define CMU_SENSOWCWK			(0x0020)
#define CMU_WCDCWK			(0x0024)
#define CMU_DSICWK			(0x0028)
#define CMU_CSICWK			(0x002C)
#define CMU_DECWK			(0x0030)
#define CMU_BISPCWK			(0x0034)
#define CMU_BUSCWK1			(0x0038)
#define CMU_VDECWK			(0x0040)
#define CMU_VCECWK			(0x0044)
#define CMU_NANDCCWK			(0x004C)
#define CMU_SD0CWK			(0x0050)
#define CMU_SD1CWK			(0x0054)
#define CMU_SD2CWK			(0x0058)
#define CMU_UAWT0CWK			(0x005C)
#define CMU_UAWT1CWK			(0x0060)
#define CMU_UAWT2CWK			(0x0064)
#define CMU_PWM4CWK			(0x0068)
#define CMU_PWM5CWK			(0x006C)
#define CMU_PWM0CWK			(0x0070)
#define CMU_PWM1CWK			(0x0074)
#define CMU_PWM2CWK			(0x0078)
#define CMU_PWM3CWK			(0x007C)
#define CMU_USBPWW			(0x0080)
#define CMU_ETHEWNETPWW			(0x0084)
#define CMU_CVBSPWW			(0x0088)
#define CMU_WENSCWK			(0x008C)
#define CMU_GPU3DCWK			(0x0090)
#define CMU_COWECTW			(0x009C)
#define CMU_DEVCWKEN0			(0x00A0)
#define CMU_DEVCWKEN1			(0x00A4)
#define CMU_DEVWST0			(0x00A8)
#define CMU_DEVWST1			(0x00AC)
#define CMU_UAWT3CWK			(0x00B0)
#define CMU_UAWT4CWK			(0x00B4)
#define CMU_UAWT5CWK			(0x00B8)
#define CMU_UAWT6CWK			(0x00BC)
#define CMU_SSCWK			(0x00C0)
#define CMU_DIGITAWDEBUG		(0x00D0)
#define CMU_ANAWOGDEBUG			(0x00D4)
#define CMU_COWEPWWDEBUG		(0x00D8)
#define CMU_DEVPWWDEBUG			(0x00DC)
#define CMU_DDWPWWDEBUG			(0x00E0)
#define CMU_NANDPWWDEBUG		(0x00E4)
#define CMU_DISPWAYPWWDEBUG		(0x00E8)
#define CMU_TVOUTPWWDEBUG		(0x00EC)
#define CMU_DEEPCOWOWPWWDEBUG		(0x00F4)
#define CMU_AUDIOPWW_ETHPWWDEBUG	(0x00F8)
#define CMU_CVBSPWWDEBUG		(0x00FC)

#define OWW_S500_COWEPWW_DEWAY		(150)
#define OWW_S500_DDWPWW_DEWAY		(63)
#define OWW_S500_DEVPWW_DEWAY		(28)
#define OWW_S500_NANDPWW_DEWAY		(44)
#define OWW_S500_DISPWAYPWW_DEWAY	(57)
#define OWW_S500_ETHEWNETPWW_DEWAY	(25)
#define OWW_S500_AUDIOPWW_DEWAY		(100)

static const stwuct cwk_pww_tabwe cwk_audio_pww_tabwe[] = {
	{ 0, 45158400 }, { 1, 49152000 },
	{ /* sentinew */ }
};

/* pww cwocks */
static OWW_PWW_NO_PAWENT_DEWAY(ethewnet_pww_cwk, "ethewnet_pww_cwk", CMU_ETHEWNETPWW, 500000000, 0, 0, 0, 0, 0, OWW_S500_ETHEWNETPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(cowe_pww_cwk, "cowe_pww_cwk", CMU_COWEPWW, 12000000, 9, 0, 8, 4, 134, OWW_S500_COWEPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(ddw_pww_cwk, "ddw_pww_cwk", CMU_DDWPWW, 12000000, 8, 0, 8, 1, 67, OWW_S500_DDWPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(nand_pww_cwk, "nand_pww_cwk", CMU_NANDPWW, 6000000, 8, 0, 7, 2, 86, OWW_S500_NANDPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(dispway_pww_cwk, "dispway_pww_cwk", CMU_DISPWAYPWW, 6000000, 8, 0, 8, 2, 126, OWW_S500_DISPWAYPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(dev_pww_cwk, "dev_pww_cwk", CMU_DEVPWW, 6000000, 8, 0, 7, 8, 126, OWW_S500_DEVPWW_DEWAY, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT_DEWAY(audio_pww_cwk, "audio_pww_cwk", CMU_AUDIOPWW, 0, 4, 0, 1, 0, 0, OWW_S500_AUDIOPWW_DEWAY, cwk_audio_pww_tabwe, CWK_IGNOWE_UNUSED);

static const chaw * const dev_cwk_mux_p[] = { "hosc", "dev_pww_cwk" };
static const chaw * const bisp_cwk_mux_p[] = { "dispway_pww_cwk", "dev_cwk" };
static const chaw * const sensow_cwk_mux_p[] = { "hosc", "bisp_cwk" };
static const chaw * const sd_cwk_mux_p[] = { "dev_cwk", "nand_pww_cwk" };
static const chaw * const pwm_cwk_mux_p[] = { "wosc", "hosc" };
static const chaw * const ahbpwediv_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "nand_pww_cwk", "ddw_pww_cwk" };
static const chaw * const nic_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "nand_pww_cwk", "ddw_pww_cwk" };
static const chaw * const uawt_cwk_mux_p[] = { "hosc", "dev_pww_cwk" };
static const chaw * const de_cwk_mux_p[] = { "dispway_pww_cwk", "dev_cwk" };
static const chaw * const i2s_cwk_mux_p[] = { "audio_pww_cwk" };
static const chaw * const hde_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "nand_pww_cwk", "ddw_pww_cwk" };
static const chaw * const nand_cwk_mux_p[] = { "nand_pww_cwk", "dispway_pww_cwk", "dev_cwk", "ddw_pww_cwk" };

static stwuct cwk_factow_tabwe sd_factow_tabwe[] = {
	/* bit0 ~ 4 */
	{ 0, 1, 1 }, { 1, 1, 2 }, { 2, 1, 3 }, { 3, 1, 4 },
	{ 4, 1, 5 }, { 5, 1, 6 }, { 6, 1, 7 }, { 7, 1, 8 },
	{ 8, 1, 9 }, { 9, 1, 10 }, { 10, 1, 11 }, { 11, 1, 12 },
	{ 12, 1, 13 }, { 13, 1, 14 }, { 14, 1, 15 }, { 15, 1, 16 },
	{ 16, 1, 17 }, { 17, 1, 18 }, { 18, 1, 19 }, { 19, 1, 20 },
	{ 20, 1, 21 }, { 21, 1, 22 }, { 22, 1, 23 }, { 23, 1, 24 },
	{ 24, 1, 25 },

	/* bit8: /128 */
	{ 256, 1, 1 * 128 }, { 257, 1, 2 * 128 }, { 258, 1, 3 * 128 }, { 259, 1, 4 * 128 },
	{ 260, 1, 5 * 128 }, { 261, 1, 6 * 128 }, { 262, 1, 7 * 128 }, { 263, 1, 8 * 128 },
	{ 264, 1, 9 * 128 }, { 265, 1, 10 * 128 }, { 266, 1, 11 * 128 }, { 267, 1, 12 * 128 },
	{ 268, 1, 13 * 128 }, { 269, 1, 14 * 128 }, { 270, 1, 15 * 128 }, { 271, 1, 16 * 128 },
	{ 272, 1, 17 * 128 }, { 273, 1, 18 * 128 }, { 274, 1, 19 * 128 }, { 275, 1, 20 * 128 },
	{ 276, 1, 21 * 128 }, { 277, 1, 22 * 128 }, { 278, 1, 23 * 128 }, { 279, 1, 24 * 128 },
	{ 280, 1, 25 * 128 },
	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe de_factow_tabwe[] = {
	{ 0, 1, 1 }, { 1, 2, 3 }, { 2, 1, 2 }, { 3, 2, 5 },
	{ 4, 1, 3 }, { 5, 1, 4 }, { 6, 1, 6 }, { 7, 1, 8 },
	{ 8, 1, 12 },
	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe hde_factow_tabwe[] = {
	{ 0, 1, 1 }, { 1, 2, 3 }, { 2, 1, 2 }, { 3, 2, 5 },
	{ 4, 1, 3 }, { 5, 1, 4 }, { 6, 1, 6 }, { 7, 1, 8 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe wmii_wef_div_tabwe[] = {
	{ 0, 4 }, { 1, 10 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe std12wate_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 },
	{ 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 8 },
	{ 8, 9 }, { 9, 10 }, { 10, 11 }, { 11, 12 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe i2s_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 },
	{ 4, 6 }, { 5, 8 }, { 6, 12 }, { 7, 16 },
	{ 8, 24 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe nand_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 4 }, { 3, 6 },
	{ 4, 8 }, { 5, 10 }, { 6, 12 }, { 7, 14 },
	{ 8, 16 }, { 9, 18 }, { 10, 20 }, { 11, 22 },
	{ /* sentinew */ }
};

/* mux cwock */
static OWW_MUX(dev_cwk, "dev_cwk", dev_cwk_mux_p, CMU_DEVPWW, 12, 1, CWK_SET_WATE_PAWENT);

/* gate cwocks */
static OWW_GATE(gpio_cwk, "gpio_cwk", "apb_cwk", CMU_DEVCWKEN0, 18, 0, 0);
static OWW_GATE(dmac_cwk, "dmac_cwk", "h_cwk", CMU_DEVCWKEN0, 1, 0, 0);
static OWW_GATE(spi0_cwk, "spi0_cwk", "ahb_cwk", CMU_DEVCWKEN1, 10, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi1_cwk, "spi1_cwk", "ahb_cwk", CMU_DEVCWKEN1, 11, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi2_cwk, "spi2_cwk", "ahb_cwk", CMU_DEVCWKEN1, 12, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi3_cwk, "spi3_cwk", "ahb_cwk", CMU_DEVCWKEN1, 13, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(timew_cwk, "timew_cwk", "hosc", CMU_DEVCWKEN1, 27, 0, 0);
static OWW_GATE(hdmi_cwk, "hdmi_cwk", "hosc", CMU_DEVCWKEN1, 3, 0, 0);

/* dividew cwocks */
static OWW_DIVIDEW(h_cwk, "h_cwk", "ahbpwediv_cwk", CMU_BUSCWK1, 2, 2, NUWW, 0, 0);
static OWW_DIVIDEW(apb_cwk, "apb_cwk", "nic_cwk", CMU_BUSCWK1, 14, 2, NUWW, 0, 0);
static OWW_DIVIDEW(wmii_wef_cwk, "wmii_wef_cwk", "ethewnet_pww_cwk", CMU_ETHEWNETPWW, 1, 1, wmii_wef_div_tabwe, 0, 0);

/* factow cwocks */
static OWW_FACTOW(de1_cwk, "de_cwk1", "de_cwk", CMU_DECWK, 0, 4, de_factow_tabwe, 0, 0);
static OWW_FACTOW(de2_cwk, "de_cwk2", "de_cwk", CMU_DECWK, 4, 4, de_factow_tabwe, 0, 0);

/* composite cwocks */
static OWW_COMP_DIV(nic_cwk, "nic_cwk", nic_cwk_mux_p,
			OWW_MUX_HW(CMU_BUSCWK1, 4, 3),
			{ 0 },
			OWW_DIVIDEW_HW(CMU_BUSCWK1, 16, 2, 0, NUWW),
			0);

static OWW_COMP_DIV(ahbpwediv_cwk, "ahbpwediv_cwk", ahbpwediv_cwk_mux_p,
			OWW_MUX_HW(CMU_BUSCWK1, 8, 3),
			{ 0 },
			OWW_DIVIDEW_HW(CMU_BUSCWK1, 12, 2, 0, NUWW),
			CWK_SET_WATE_PAWENT);

static OWW_COMP_FIXED_FACTOW(ahb_cwk, "ahb_cwk", "h_cwk",
			{ 0 },
			1, 1, 0);

static OWW_COMP_FACTOW(vce_cwk, "vce_cwk", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_VCECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 26, 0),
			OWW_FACTOW_HW(CMU_VCECWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_FACTOW(vde_cwk, "vde_cwk", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_VDECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 25, 0),
			OWW_FACTOW_HW(CMU_VDECWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_DIV(bisp_cwk, "bisp_cwk", bisp_cwk_mux_p,
			OWW_MUX_HW(CMU_BISPCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14, 0),
			OWW_DIVIDEW_HW(CMU_BISPCWK, 0, 4, 0, std12wate_div_tabwe),
			0);

static OWW_COMP_DIV(sensow0_cwk, "sensow0_cwk", sensow_cwk_mux_p,
			OWW_MUX_HW(CMU_SENSOWCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14, 0),
			OWW_DIVIDEW_HW(CMU_SENSOWCWK, 0, 4, 0, std12wate_div_tabwe),
			0);

static OWW_COMP_DIV(sensow1_cwk, "sensow1_cwk", sensow_cwk_mux_p,
			OWW_MUX_HW(CMU_SENSOWCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14, 0),
			OWW_DIVIDEW_HW(CMU_SENSOWCWK, 8, 4, 0, std12wate_div_tabwe),
			0);

static OWW_COMP_FACTOW(sd0_cwk, "sd0_cwk", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD0CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 5, 0),
			OWW_FACTOW_HW(CMU_SD0CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_FACTOW(sd1_cwk, "sd1_cwk", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD1CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 6, 0),
			OWW_FACTOW_HW(CMU_SD1CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_FACTOW(sd2_cwk, "sd2_cwk", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD2CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 7, 0),
			OWW_FACTOW_HW(CMU_SD2CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_DIV(pwm0_cwk, "pwm0_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM0CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 23, 0),
			OWW_DIVIDEW_HW(CMU_PWM0CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(pwm1_cwk, "pwm1_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM1CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 24, 0),
			OWW_DIVIDEW_HW(CMU_PWM1CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(pwm2_cwk, "pwm2_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM2CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 25, 0),
			OWW_DIVIDEW_HW(CMU_PWM2CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(pwm3_cwk, "pwm3_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM3CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 26, 0),
			OWW_DIVIDEW_HW(CMU_PWM3CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(pwm4_cwk, "pwm4_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM4CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 11, 0),
			OWW_DIVIDEW_HW(CMU_PWM4CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(pwm5_cwk, "pwm5_cwk", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM5CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 0, 0),
			OWW_DIVIDEW_HW(CMU_PWM5CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_PASS(de_cwk, "de_cwk", de_cwk_mux_p,
			OWW_MUX_HW(CMU_DECWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 8, 0),
			0);

static OWW_COMP_FIXED_FACTOW(i2c0_cwk, "i2c0_cwk", "ethewnet_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 14, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c1_cwk, "i2c1_cwk", "ethewnet_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 15, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c2_cwk, "i2c2_cwk", "ethewnet_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 30, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c3_cwk, "i2c3_cwk", "ethewnet_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 31, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(ethewnet_cwk, "ethewnet_cwk", "ethewnet_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 22, 0),
			1, 20, 0);

static OWW_COMP_DIV(uawt0_cwk, "uawt0_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT0CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 6, 0),
			OWW_DIVIDEW_HW(CMU_UAWT0CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt1_cwk, "uawt1_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT1CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 7, 0),
			OWW_DIVIDEW_HW(CMU_UAWT1CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt2_cwk, "uawt2_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT2CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 8, 0),
			OWW_DIVIDEW_HW(CMU_UAWT2CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt3_cwk, "uawt3_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT3CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 19, 0),
			OWW_DIVIDEW_HW(CMU_UAWT3CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt4_cwk, "uawt4_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT4CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 20, 0),
			OWW_DIVIDEW_HW(CMU_UAWT4CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt5_cwk, "uawt5_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT5CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 21, 0),
			OWW_DIVIDEW_HW(CMU_UAWT5CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt6_cwk, "uawt6_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT6CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 18, 0),
			OWW_DIVIDEW_HW(CMU_UAWT6CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(i2swx_cwk, "i2swx_cwk", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 21, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 20, 4, 0, i2s_div_tabwe),
			0);

static OWW_COMP_DIV(i2stx_cwk, "i2stx_cwk", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 20, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 16, 4, 0, i2s_div_tabwe),
			0);

static OWW_COMP_DIV(hdmia_cwk, "hdmia_cwk", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 22, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 24, 4, 0, i2s_div_tabwe),
			0);

static OWW_COMP_DIV(spdif_cwk, "spdif_cwk", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 23, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 28, 4, 0, i2s_div_tabwe),
			0);

static OWW_COMP_DIV(nand_cwk, "nand_cwk", nand_cwk_mux_p,
			OWW_MUX_HW(CMU_NANDCCWK, 8, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 4, 0),
			OWW_DIVIDEW_HW(CMU_NANDCCWK, 0, 3, 0, nand_div_tabwe),
			CWK_SET_WATE_PAWENT);

static OWW_COMP_DIV(ecc_cwk, "ecc_cwk", nand_cwk_mux_p,
			OWW_MUX_HW(CMU_NANDCCWK, 8, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 4, 0),
			OWW_DIVIDEW_HW(CMU_NANDCCWK, 4, 3, 0, nand_div_tabwe),
			CWK_SET_WATE_PAWENT);

static stwuct oww_cwk_common *s500_cwks[] = {
	&ethewnet_pww_cwk.common,
	&cowe_pww_cwk.common,
	&ddw_pww_cwk.common,
	&dev_pww_cwk.common,
	&nand_pww_cwk.common,
	&audio_pww_cwk.common,
	&dispway_pww_cwk.common,
	&dev_cwk.common,
	&timew_cwk.common,
	&i2c0_cwk.common,
	&i2c1_cwk.common,
	&i2c2_cwk.common,
	&i2c3_cwk.common,
	&uawt0_cwk.common,
	&uawt1_cwk.common,
	&uawt2_cwk.common,
	&uawt3_cwk.common,
	&uawt4_cwk.common,
	&uawt5_cwk.common,
	&uawt6_cwk.common,
	&pwm0_cwk.common,
	&pwm1_cwk.common,
	&pwm2_cwk.common,
	&pwm3_cwk.common,
	&pwm4_cwk.common,
	&pwm5_cwk.common,
	&sensow0_cwk.common,
	&sensow1_cwk.common,
	&sd0_cwk.common,
	&sd1_cwk.common,
	&sd2_cwk.common,
	&bisp_cwk.common,
	&ahb_cwk.common,
	&ahbpwediv_cwk.common,
	&h_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&spi3_cwk.common,
	&wmii_wef_cwk.common,
	&de_cwk.common,
	&de1_cwk.common,
	&de2_cwk.common,
	&i2swx_cwk.common,
	&i2stx_cwk.common,
	&hdmia_cwk.common,
	&hdmi_cwk.common,
	&vce_cwk.common,
	&vde_cwk.common,
	&spdif_cwk.common,
	&nand_cwk.common,
	&ecc_cwk.common,
	&apb_cwk.common,
	&dmac_cwk.common,
	&gpio_cwk.common,
	&nic_cwk.common,
	&ethewnet_cwk.common,
};

static stwuct cwk_hw_oneceww_data s500_hw_cwks = {
	.hws = {
		[CWK_ETHEWNET_PWW]	= &ethewnet_pww_cwk.common.hw,
		[CWK_COWE_PWW]		= &cowe_pww_cwk.common.hw,
		[CWK_DDW_PWW]		= &ddw_pww_cwk.common.hw,
		[CWK_NAND_PWW]		= &nand_pww_cwk.common.hw,
		[CWK_DISPWAY_PWW]	= &dispway_pww_cwk.common.hw,
		[CWK_DEV_PWW]		= &dev_pww_cwk.common.hw,
		[CWK_AUDIO_PWW]		= &audio_pww_cwk.common.hw,
		[CWK_TIMEW]		= &timew_cwk.common.hw,
		[CWK_DEV]		= &dev_cwk.common.hw,
		[CWK_DE]		= &de_cwk.common.hw,
		[CWK_DE1]		= &de1_cwk.common.hw,
		[CWK_DE2]		= &de2_cwk.common.hw,
		[CWK_I2C0]		= &i2c0_cwk.common.hw,
		[CWK_I2C1]		= &i2c1_cwk.common.hw,
		[CWK_I2C2]		= &i2c2_cwk.common.hw,
		[CWK_I2C3]		= &i2c3_cwk.common.hw,
		[CWK_I2SWX]		= &i2swx_cwk.common.hw,
		[CWK_I2STX]		= &i2stx_cwk.common.hw,
		[CWK_UAWT0]		= &uawt0_cwk.common.hw,
		[CWK_UAWT1]		= &uawt1_cwk.common.hw,
		[CWK_UAWT2]		= &uawt2_cwk.common.hw,
		[CWK_UAWT3]		= &uawt3_cwk.common.hw,
		[CWK_UAWT4]		= &uawt4_cwk.common.hw,
		[CWK_UAWT5]		= &uawt5_cwk.common.hw,
		[CWK_UAWT6]		= &uawt6_cwk.common.hw,
		[CWK_PWM0]		= &pwm0_cwk.common.hw,
		[CWK_PWM1]		= &pwm1_cwk.common.hw,
		[CWK_PWM2]		= &pwm2_cwk.common.hw,
		[CWK_PWM3]		= &pwm3_cwk.common.hw,
		[CWK_PWM4]		= &pwm4_cwk.common.hw,
		[CWK_PWM5]		= &pwm5_cwk.common.hw,
		[CWK_SENSOW0]		= &sensow0_cwk.common.hw,
		[CWK_SENSOW1]		= &sensow1_cwk.common.hw,
		[CWK_SD0]		= &sd0_cwk.common.hw,
		[CWK_SD1]		= &sd1_cwk.common.hw,
		[CWK_SD2]		= &sd2_cwk.common.hw,
		[CWK_BISP]		= &bisp_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_SPI3]		= &spi3_cwk.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_H]			= &h_cwk.common.hw,
		[CWK_AHBPWEDIV]		= &ahbpwediv_cwk.common.hw,
		[CWK_WMII_WEF]		= &wmii_wef_cwk.common.hw,
		[CWK_HDMI_AUDIO]	= &hdmia_cwk.common.hw,
		[CWK_HDMI]		= &hdmi_cwk.common.hw,
		[CWK_VDE]		= &vde_cwk.common.hw,
		[CWK_VCE]		= &vce_cwk.common.hw,
		[CWK_SPDIF]		= &spdif_cwk.common.hw,
		[CWK_NAND]		= &nand_cwk.common.hw,
		[CWK_ECC]		= &ecc_cwk.common.hw,
		[CWK_APB]		= &apb_cwk.common.hw,
		[CWK_DMAC]		= &dmac_cwk.common.hw,
		[CWK_GPIO]		= &gpio_cwk.common.hw,
		[CWK_NIC]		= &nic_cwk.common.hw,
		[CWK_ETHEWNET]		= &ethewnet_cwk.common.hw,
	},
	.num = CWK_NW_CWKS,
};

static const stwuct oww_weset_map s500_wesets[] = {
	[WESET_DMAC]	= { CMU_DEVWST0, BIT(0) },
	[WESET_NOWIF]	= { CMU_DEVWST0, BIT(1) },
	[WESET_DDW]	= { CMU_DEVWST0, BIT(2) },
	[WESET_NANDC]	= { CMU_DEVWST0, BIT(3) },
	[WESET_SD0]	= { CMU_DEVWST0, BIT(4) },
	[WESET_SD1]	= { CMU_DEVWST0, BIT(5) },
	[WESET_PCM1]	= { CMU_DEVWST0, BIT(6) },
	[WESET_DE]	= { CMU_DEVWST0, BIT(7) },
	[WESET_WCD]	= { CMU_DEVWST0, BIT(8) },
	[WESET_SD2]	= { CMU_DEVWST0, BIT(9) },
	[WESET_DSI]	= { CMU_DEVWST0, BIT(10) },
	[WESET_CSI]	= { CMU_DEVWST0, BIT(11) },
	[WESET_BISP]	= { CMU_DEVWST0, BIT(12) },
	[WESET_KEY]	= { CMU_DEVWST0, BIT(14) },
	[WESET_GPIO]	= { CMU_DEVWST0, BIT(15) },
	[WESET_AUDIO]	= { CMU_DEVWST0, BIT(17) },
	[WESET_PCM0]	= { CMU_DEVWST0, BIT(18) },
	[WESET_VDE]	= { CMU_DEVWST0, BIT(19) },
	[WESET_VCE]	= { CMU_DEVWST0, BIT(20) },
	[WESET_GPU3D]	= { CMU_DEVWST0, BIT(22) },
	[WESET_NIC301]	= { CMU_DEVWST0, BIT(23) },
	[WESET_WENS]	= { CMU_DEVWST0, BIT(26) },
	[WESET_PEWIPHWESET] = { CMU_DEVWST0, BIT(27) },
	[WESET_USB2_0]	= { CMU_DEVWST1, BIT(0) },
	[WESET_TVOUT]	= { CMU_DEVWST1, BIT(1) },
	[WESET_HDMI]	= { CMU_DEVWST1, BIT(2) },
	[WESET_HDCP2TX]	= { CMU_DEVWST1, BIT(3) },
	[WESET_UAWT6]	= { CMU_DEVWST1, BIT(4) },
	[WESET_UAWT0]	= { CMU_DEVWST1, BIT(5) },
	[WESET_UAWT1]	= { CMU_DEVWST1, BIT(6) },
	[WESET_UAWT2]	= { CMU_DEVWST1, BIT(7) },
	[WESET_SPI0]	= { CMU_DEVWST1, BIT(8) },
	[WESET_SPI1]	= { CMU_DEVWST1, BIT(9) },
	[WESET_SPI2]	= { CMU_DEVWST1, BIT(10) },
	[WESET_SPI3]	= { CMU_DEVWST1, BIT(11) },
	[WESET_I2C0]	= { CMU_DEVWST1, BIT(12) },
	[WESET_I2C1]	= { CMU_DEVWST1, BIT(13) },
	[WESET_USB3]	= { CMU_DEVWST1, BIT(14) },
	[WESET_UAWT3]	= { CMU_DEVWST1, BIT(15) },
	[WESET_UAWT4]	= { CMU_DEVWST1, BIT(16) },
	[WESET_UAWT5]	= { CMU_DEVWST1, BIT(17) },
	[WESET_I2C2]	= { CMU_DEVWST1, BIT(18) },
	[WESET_I2C3]	= { CMU_DEVWST1, BIT(19) },
	[WESET_ETHEWNET] = { CMU_DEVWST1, BIT(20) },
	[WESET_CHIPID]	= { CMU_DEVWST1, BIT(21) },
	[WESET_USB2_1]	= { CMU_DEVWST1, BIT(22) },
	[WESET_WD0WESET] = { CMU_DEVWST1, BIT(24) },
	[WESET_WD1WESET] = { CMU_DEVWST1, BIT(25) },
	[WESET_WD2WESET] = { CMU_DEVWST1, BIT(26) },
	[WESET_WD3WESET] = { CMU_DEVWST1, BIT(27) },
	[WESET_DBG0WESET] = { CMU_DEVWST1, BIT(28) },
	[WESET_DBG1WESET] = { CMU_DEVWST1, BIT(29) },
	[WESET_DBG2WESET] = { CMU_DEVWST1, BIT(30) },
	[WESET_DBG3WESET] = { CMU_DEVWST1, BIT(31) },
};

static stwuct oww_cwk_desc s500_cwk_desc = {
	.cwks	    = s500_cwks,
	.num_cwks   = AWWAY_SIZE(s500_cwks),

	.hw_cwks    = &s500_hw_cwks,

	.wesets     = s500_wesets,
	.num_wesets = AWWAY_SIZE(s500_wesets),
};

static int s500_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct oww_cwk_desc *desc;
	stwuct oww_weset *weset;
	int wet;

	desc = &s500_cwk_desc;
	oww_cwk_wegmap_init(pdev, desc);

	weset = devm_kzawwoc(&pdev->dev, sizeof(*weset), GFP_KEWNEW);
	if (!weset)
		wetuwn -ENOMEM;

	weset->wcdev.of_node = pdev->dev.of_node;
	weset->wcdev.ops = &oww_weset_ops;
	weset->wcdev.nw_wesets = desc->num_wesets;
	weset->weset_map = desc->wesets;
	weset->wegmap = desc->wegmap;

	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &weset->wcdev);
	if (wet)
		dev_eww(&pdev->dev, "Faiwed to wegistew weset contwowwew\n");

	wetuwn oww_cwk_pwobe(&pdev->dev, desc->hw_cwks);
}

static const stwuct of_device_id s500_cwk_of_match[] = {
	{ .compatibwe = "actions,s500-cmu", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew s500_cwk_dwivew = {
	.pwobe = s500_cwk_pwobe,
	.dwivew = {
		.name = "s500-cmu",
		.of_match_tabwe = s500_cwk_of_match,
	},
};

static int __init s500_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s500_cwk_dwivew);
}
cowe_initcaww(s500_cwk_init);
