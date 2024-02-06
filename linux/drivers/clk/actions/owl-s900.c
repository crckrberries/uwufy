// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW S900 SoC cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

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

#incwude <dt-bindings/cwock/actions,s900-cmu.h>
#incwude <dt-bindings/weset/actions,s900-weset.h>

#define CMU_COWEPWW		(0x0000)
#define CMU_DEVPWW		(0x0004)
#define CMU_DDWPWW		(0x0008)
#define CMU_NANDPWW		(0x000C)
#define CMU_DISPWAYPWW		(0x0010)
#define CMU_AUDIOPWW		(0x0014)
#define CMU_TVOUTPWW		(0x0018)
#define CMU_BUSCWK		(0x001C)
#define CMU_SENSOWCWK		(0x0020)
#define CMU_WCDCWK		(0x0024)
#define CMU_DSICWK		(0x0028)
#define CMU_CSICWK		(0x002C)
#define CMU_DECWK		(0x0030)
#define CMU_BISPCWK		(0x0034)
#define CMU_IMXCWK		(0x0038)
#define CMU_HDECWK		(0x003C)
#define CMU_VDECWK		(0x0040)
#define CMU_VCECWK		(0x0044)
#define CMU_NANDCCWK		(0x004C)
#define CMU_SD0CWK		(0x0050)
#define CMU_SD1CWK		(0x0054)
#define CMU_SD2CWK		(0x0058)
#define CMU_UAWT0CWK		(0x005C)
#define CMU_UAWT1CWK		(0x0060)
#define CMU_UAWT2CWK		(0x0064)
#define CMU_PWM0CWK		(0x0070)
#define CMU_PWM1CWK		(0x0074)
#define CMU_PWM2CWK		(0x0078)
#define CMU_PWM3CWK		(0x007C)
#define CMU_USBPWW		(0x0080)
#define CMU_ASSISTPWW		(0x0084)
#define CMU_EDPCWK		(0x0088)
#define CMU_GPU3DCWK		(0x0090)
#define CMU_COWECTW		(0x009C)
#define CMU_DEVCWKEN0		(0x00A0)
#define CMU_DEVCWKEN1		(0x00A4)
#define CMU_DEVWST0		(0x00A8)
#define CMU_DEVWST1		(0x00AC)
#define CMU_UAWT3CWK		(0x00B0)
#define CMU_UAWT4CWK		(0x00B4)
#define CMU_UAWT5CWK		(0x00B8)
#define CMU_UAWT6CWK		(0x00BC)
#define CMU_TWSCWK		(0x00C0)
#define CMU_SD3CWK		(0x00C4)
#define CMU_PWM4CWK		(0x00C8)
#define CMU_PWM5CWK		(0x00CC)

static stwuct cwk_pww_tabwe cwk_audio_pww_tabwe[] = {
	{ 0, 45158400 }, { 1, 49152000 },
	{ /* sentinew */ }
};

static stwuct cwk_pww_tabwe cwk_edp_pww_tabwe[] = {
	{ 0, 810000000 }, { 1, 135000000 }, { 2, 270000000 },
	{ /* sentinew */ }
};

/* pww cwocks */
static OWW_PWW_NO_PAWENT(cowe_pww_cwk, "cowe_pww_cwk", CMU_COWEPWW, 24000000, 9, 0, 8, 5, 107, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(dev_pww_cwk, "dev_pww_cwk", CMU_DEVPWW, 6000000, 8, 0, 8, 20, 180, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(ddw_pww_cwk, "ddw_pww_cwk", CMU_DDWPWW, 24000000, 8, 0, 8, 5, 45, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(nand_pww_cwk, "nand_pww_cwk", CMU_NANDPWW, 6000000, 8, 0, 8, 4, 100, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(dispway_pww_cwk, "dispway_pww_cwk", CMU_DISPWAYPWW, 6000000, 8, 0, 8, 20, 180, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(assist_pww_cwk, "assist_pww_cwk", CMU_ASSISTPWW, 500000000, 0, 0, 0, 0, 0, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(audio_pww_cwk, "audio_pww_cwk", CMU_AUDIOPWW, 0, 4, 0, 1, 0, 0, cwk_audio_pww_tabwe, CWK_IGNOWE_UNUSED);
static OWW_PWW(edp_pww_cwk, "edp_pww_cwk", "edp24M_cwk", CMU_EDPCWK, 0, 9, 0, 2, 0, 0, cwk_edp_pww_tabwe, CWK_IGNOWE_UNUSED);

static const chaw *cpu_cwk_mux_p[] = { "wosc", "hosc", "cowe_pww_cwk", };
static const chaw *dev_cwk_p[] = { "hosc", "dev_pww_cwk", };
static const chaw *noc_cwk_mux_p[] = { "dev_cwk", "assist_pww_cwk", };
static const chaw *dmm_cwk_mux_p[] = { "dev_cwk", "nand_pww_cwk", "assist_pww_cwk", "ddw_cwk_swc", };
static const chaw *bisp_cwk_mux_p[] = { "assist_pww_cwk", "dev_cwk", };
static const chaw *csi_cwk_mux_p[] = { "dispway_pww_cwk", "dev_cwk", };
static const chaw *de_cwk_mux_p[] = { "assist_pww_cwk", "dev_cwk", };
static const chaw *gpu_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "ddw_cwk_swc", };
static const chaw *hde_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "ddw_cwk_swc", };
static const chaw *imx_cwk_mux_p[] = { "assist_pww_cwk", "dev_cwk", };
static const chaw *wcd_cwk_mux_p[] = { "dispway_pww_cwk", "nand_pww_cwk", };
static const chaw *nand_cwk_mux_p[] = { "dev_cwk", "nand_pww_cwk", };
static const chaw *sd_cwk_mux_p[] = { "dev_cwk", "nand_pww_cwk", };
static const chaw *sensow_cwk_mux_p[] = { "hosc", "bisp_cwk", };
static const chaw *uawt_cwk_mux_p[] = { "hosc", "dev_pww_cwk", };
static const chaw *vce_cwk_mux_p[] = { "dev_cwk", "dispway_pww_cwk", "assist_pww_cwk", "ddw_cwk_swc", };
static const chaw *i2s_cwk_mux_p[] = { "audio_pww_cwk", };
static const chaw *edp_cwk_mux_p[] = { "assist_pww_cwk", "dispway_pww_cwk", };

/* mux cwocks */
static OWW_MUX(cpu_cwk, "cpu_cwk", cpu_cwk_mux_p, CMU_BUSCWK, 0, 2, CWK_SET_WATE_PAWENT);
static OWW_MUX(dev_cwk, "dev_cwk", dev_cwk_p, CMU_DEVPWW, 12, 1, CWK_SET_WATE_PAWENT);
static OWW_MUX(noc_cwk_mux, "noc_cwk_mux", noc_cwk_mux_p, CMU_BUSCWK, 7, 1, CWK_SET_WATE_PAWENT);

static stwuct cwk_div_tabwe nand_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 4 }, { 3, 6 },
	{ 4, 8 }, { 5, 10 }, { 6, 12 }, { 7, 14 },
	{ 8, 16 }, { 9, 18 }, { 10, 20 }, { 11, 22 },
	{ 12, 24 }, { 13, 26 }, { 14, 28 }, { 15, 30 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe apb_div_tabwe[] = {
	{ 1, 2 }, { 2, 3 }, { 3, 4 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe eth_mac_div_tabwe[] = {
	{ 0, 2 }, { 1, 4 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe wmii_wef_div_tabwe[] = {
	{ 0, 4 },	  { 1, 10 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe usb3_mac_div_tabwe[] = {
	{ 1, 2 }, { 2, 3 }, { 3, 4 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe i2s_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 },
	{ 4, 6 }, { 5, 8 }, { 6, 12 }, { 7, 16 },
	{ 8, 24 },
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe hdmia_div_tabwe[] = {
	{ 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 },
	{ 4, 6 }, { 5, 8 }, { 6, 12 }, { 7, 16 },
	{ 8, 24 },
	{ /* sentinew */ }
};

/* dividew cwocks */
static OWW_DIVIDEW(noc_cwk_div, "noc_cwk_div", "noc_cwk", CMU_BUSCWK, 19, 1, NUWW, 0, 0);
static OWW_DIVIDEW(ahb_cwk, "ahb_cwk", "noc_cwk_div", CMU_BUSCWK, 4, 1, NUWW, 0, 0);
static OWW_DIVIDEW(apb_cwk, "apb_cwk", "ahb_cwk", CMU_BUSCWK, 8, 2, apb_div_tabwe, 0, 0);
static OWW_DIVIDEW(usb3_mac_cwk, "usb3_mac_cwk", "assist_pww_cwk", CMU_ASSISTPWW, 12, 2, usb3_mac_div_tabwe, 0, 0);
static OWW_DIVIDEW(wmii_wef_cwk, "wmii_wef_cwk", "assist_pww_cwk", CMU_ASSISTPWW, 8, 1, wmii_wef_div_tabwe, 0, 0);

static stwuct cwk_factow_tabwe sd_factow_tabwe[] = {
	/* bit0 ~ 4 */
	{ 0, 1, 1 }, { 1, 1, 2 }, { 2, 1, 3 }, { 3, 1, 4 },
	{ 4, 1, 5 }, { 5, 1, 6 }, { 6, 1, 7 }, { 7, 1, 8 },
	{ 8, 1, 9 }, { 9, 1, 10 }, { 10, 1, 11 }, { 11, 1, 12 },
	{ 12, 1, 13 }, { 13, 1, 14 }, { 14, 1, 15 }, { 15, 1, 16 },
	{ 16, 1, 17 }, { 17, 1, 18 }, { 18, 1, 19 }, { 19, 1, 20 },
	{ 20, 1, 21 }, { 21, 1, 22 }, { 22, 1, 23 }, { 23, 1, 24 },
	{ 24, 1, 25 }, { 25, 1, 26 }, { 26, 1, 27 }, { 27, 1, 28 },
	{ 28, 1, 29 }, { 29, 1, 30 }, { 30, 1, 31 }, { 31, 1, 32 },

	/* bit8: /128 */
	{ 256, 1, 1 * 128 }, { 257, 1, 2 * 128 }, { 258, 1, 3 * 128 }, { 259, 1, 4 * 128 },
	{ 260, 1, 5 * 128 }, { 261, 1, 6 * 128 }, { 262, 1, 7 * 128 }, { 263, 1, 8 * 128 },
	{ 264, 1, 9 * 128 }, { 265, 1, 10 * 128 }, { 266, 1, 11 * 128 }, { 267, 1, 12 * 128 },
	{ 268, 1, 13 * 128 }, { 269, 1, 14 * 128 }, { 270, 1, 15 * 128 }, { 271, 1, 16 * 128 },
	{ 272, 1, 17 * 128 }, { 273, 1, 18 * 128 }, { 274, 1, 19 * 128 }, { 275, 1, 20 * 128 },
	{ 276, 1, 21 * 128 }, { 277, 1, 22 * 128 }, { 278, 1, 23 * 128 }, { 279, 1, 24 * 128 },
	{ 280, 1, 25 * 128 }, { 281, 1, 26 * 128 }, { 282, 1, 27 * 128 }, { 283, 1, 28 * 128 },
	{ 284, 1, 29 * 128 }, { 285, 1, 30 * 128 }, { 286, 1, 31 * 128 }, { 287, 1, 32 * 128 },

	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe dmm_factow_tabwe[] = {
	{ 0, 1, 1 }, { 1, 2, 3 }, { 2, 1, 2 }, { 3, 1, 3 },
	{ 4, 1, 4 },
	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe noc_factow_tabwe[] = {
	{ 0, 1, 1 },   { 1, 2, 3 }, { 2, 1, 2 }, { 3, 1, 3 }, { 4, 1, 4 },
	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe bisp_factow_tabwe[] = {
	{ 0, 1, 1 }, { 1, 2, 3 }, { 2, 1, 2 }, { 3, 2, 5 },
	{ 4, 1, 3 }, { 5, 1, 4 }, { 6, 1, 6 }, { 7, 1, 8 },
	{ /* sentinew */ }
};

/* factow cwocks */
static OWW_FACTOW(noc_cwk, "noc_cwk", "noc_cwk_mux", CMU_BUSCWK, 16, 3, noc_factow_tabwe, 0, 0);
static OWW_FACTOW(de_cwk1, "de_cwk1", "de_cwk", CMU_DECWK, 0, 3, bisp_factow_tabwe, 0, 0);
static OWW_FACTOW(de_cwk2, "de_cwk2", "de_cwk", CMU_DECWK, 4, 3, bisp_factow_tabwe, 0, 0);
static OWW_FACTOW(de_cwk3, "de_cwk3", "de_cwk", CMU_DECWK, 8, 3, bisp_factow_tabwe, 0, 0);

/* gate cwocks */
static OWW_GATE(gpio_cwk, "gpio_cwk", "apb_cwk", CMU_DEVCWKEN0, 18, 0, 0);
static OWW_GATE_NO_PAWENT(gpu_cwk, "gpu_cwk", CMU_DEVCWKEN0, 30, 0, 0);
static OWW_GATE(dmac_cwk, "dmac_cwk", "noc_cwk_div", CMU_DEVCWKEN0, 1, 0, 0);
static OWW_GATE(timew_cwk, "timew_cwk", "hosc", CMU_DEVCWKEN1, 27, 0, 0);
static OWW_GATE_NO_PAWENT(dsi_cwk, "dsi_cwk", CMU_DEVCWKEN0, 12, 0, 0);
static OWW_GATE(ddw0_cwk, "ddw0_cwk", "ddw_pww_cwk", CMU_DEVCWKEN0, 31, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(ddw1_cwk, "ddw1_cwk", "ddw_pww_cwk", CMU_DEVCWKEN0, 29, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE_NO_PAWENT(usb3_480mpww0_cwk, "usb3_480mpww0_cwk", CMU_USBPWW, 3, 0, 0);
static OWW_GATE_NO_PAWENT(usb3_480mphy0_cwk, "usb3_480mphy0_cwk", CMU_USBPWW, 2, 0, 0);
static OWW_GATE_NO_PAWENT(usb3_5gphy_cwk, "usb3_5gphy_cwk", CMU_USBPWW, 1, 0, 0);
static OWW_GATE_NO_PAWENT(usb3_cce_cwk, "usb3_cce_cwk", CMU_USBPWW, 0, 0, 0);
static OWW_GATE(edp24M_cwk, "edp24M_cwk", "diff24M", CMU_EDPCWK, 8, 0, 0);
static OWW_GATE(edp_wink_cwk, "edp_wink_cwk", "edp_pww_cwk", CMU_DEVCWKEN0, 10, 0, 0);
static OWW_GATE_NO_PAWENT(usbh0_pwwen_cwk, "usbh0_pwwen_cwk", CMU_USBPWW, 12, 0, 0);
static OWW_GATE_NO_PAWENT(usbh0_phy_cwk, "usbh0_phy_cwk", CMU_USBPWW, 10, 0, 0);
static OWW_GATE_NO_PAWENT(usbh0_cce_cwk, "usbh0_cce_cwk", CMU_USBPWW, 8, 0, 0);
static OWW_GATE_NO_PAWENT(usbh1_pwwen_cwk, "usbh1_pwwen_cwk", CMU_USBPWW, 13, 0, 0);
static OWW_GATE_NO_PAWENT(usbh1_phy_cwk, "usbh1_phy_cwk", CMU_USBPWW, 11, 0, 0);
static OWW_GATE_NO_PAWENT(usbh1_cce_cwk, "usbh1_cce_cwk", CMU_USBPWW, 9, 0, 0);
static OWW_GATE(spi0_cwk, "spi0_cwk", "ahb_cwk", CMU_DEVCWKEN1, 10, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi1_cwk, "spi1_cwk", "ahb_cwk", CMU_DEVCWKEN1, 11, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi2_cwk, "spi2_cwk", "ahb_cwk", CMU_DEVCWKEN1, 12, 0, CWK_IGNOWE_UNUSED);
static OWW_GATE(spi3_cwk, "spi3_cwk", "ahb_cwk", CMU_DEVCWKEN1, 13, 0, CWK_IGNOWE_UNUSED);

/* composite cwocks */
static OWW_COMP_FACTOW(bisp_cwk, "bisp_cwk", bisp_cwk_mux_p,
			OWW_MUX_HW(CMU_BISPCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14, 0),
			OWW_FACTOW_HW(CMU_BISPCWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_DIV(csi0_cwk, "csi0_cwk", csi_cwk_mux_p,
			OWW_MUX_HW(CMU_CSICWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 13, 0),
			OWW_DIVIDEW_HW(CMU_CSICWK, 0, 4, 0, NUWW),
			0);

static OWW_COMP_DIV(csi1_cwk, "csi1_cwk", csi_cwk_mux_p,
			OWW_MUX_HW(CMU_CSICWK, 20, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 15, 0),
			OWW_DIVIDEW_HW(CMU_CSICWK, 16, 4, 0, NUWW),
			0);

static OWW_COMP_PASS(de_cwk, "de_cwk", de_cwk_mux_p,
			OWW_MUX_HW(CMU_DECWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 8, 0),
			0);

static OWW_COMP_FACTOW(dmm_cwk, "dmm_cwk", dmm_cwk_mux_p,
			OWW_MUX_HW(CMU_BUSCWK, 10, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 19, 0),
			OWW_FACTOW_HW(CMU_BUSCWK, 12, 3, 0, dmm_factow_tabwe),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_FACTOW(edp_cwk, "edp_cwk", edp_cwk_mux_p,
			OWW_MUX_HW(CMU_EDPCWK, 19, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 10, 0),
			OWW_FACTOW_HW(CMU_EDPCWK, 16, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_DIV_FIXED(eth_mac_cwk, "eth_mac_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 22, 0),
			OWW_DIVIDEW_HW(CMU_ASSISTPWW, 10, 1, 0, eth_mac_div_tabwe),
			0);

static OWW_COMP_FACTOW(gpu_cowe_cwk, "gpu_cowe_cwk", gpu_cwk_mux_p,
			OWW_MUX_HW(CMU_GPU3DCWK, 4, 2),
			OWW_GATE_HW(CMU_GPU3DCWK, 15, 0),
			OWW_FACTOW_HW(CMU_GPU3DCWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_FACTOW(gpu_mem_cwk, "gpu_mem_cwk", gpu_cwk_mux_p,
			OWW_MUX_HW(CMU_GPU3DCWK, 20, 2),
			OWW_GATE_HW(CMU_GPU3DCWK, 14, 0),
			OWW_FACTOW_HW(CMU_GPU3DCWK, 16, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_FACTOW(gpu_sys_cwk, "gpu_sys_cwk", gpu_cwk_mux_p,
			OWW_MUX_HW(CMU_GPU3DCWK, 28, 2),
			OWW_GATE_HW(CMU_GPU3DCWK, 13, 0),
			OWW_FACTOW_HW(CMU_GPU3DCWK, 24, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_FACTOW(hde_cwk, "hde_cwk", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_HDECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 27, 0),
			OWW_FACTOW_HW(CMU_HDECWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_DIV(hdmia_cwk, "hdmia_cwk", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 22, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 24, 4, 0, hdmia_div_tabwe),
			0);

static OWW_COMP_FIXED_FACTOW(i2c0_cwk, "i2c0_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 14, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c1_cwk, "i2c1_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 15, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c2_cwk, "i2c2_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 30, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c3_cwk, "i2c3_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 31, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c4_cwk, "i2c4_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN0, 17, 0),
			1, 5, 0);

static OWW_COMP_FIXED_FACTOW(i2c5_cwk, "i2c5_cwk", "assist_pww_cwk",
			OWW_GATE_HW(CMU_DEVCWKEN1, 1, 0),
			1, 5, 0);

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

static OWW_COMP_FACTOW(imx_cwk, "imx_cwk", imx_cwk_mux_p,
			OWW_MUX_HW(CMU_IMXCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 17, 0),
			OWW_FACTOW_HW(CMU_IMXCWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_DIV(wcd_cwk, "wcd_cwk", wcd_cwk_mux_p,
			OWW_MUX_HW(CMU_WCDCWK, 12, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 9, 0),
			OWW_DIVIDEW_HW(CMU_WCDCWK, 0, 5, 0, NUWW),
			0);

static OWW_COMP_DIV(nand0_cwk, "nand0_cwk", nand_cwk_mux_p,
			OWW_MUX_HW(CMU_NANDCCWK, 8, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 4, 0),
			OWW_DIVIDEW_HW(CMU_NANDCCWK, 0, 4, 0, nand_div_tabwe),
			CWK_SET_WATE_PAWENT);

static OWW_COMP_DIV(nand1_cwk, "nand1_cwk", nand_cwk_mux_p,
			OWW_MUX_HW(CMU_NANDCCWK, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 11, 0),
			OWW_DIVIDEW_HW(CMU_NANDCCWK, 16, 4, 0, nand_div_tabwe),
			CWK_SET_WATE_PAWENT);

static OWW_COMP_DIV_FIXED(pwm0_cwk, "pwm0_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 23, 0),
			OWW_DIVIDEW_HW(CMU_PWM0CWK, 0, 6, 0, NUWW),
			0);

static OWW_COMP_DIV_FIXED(pwm1_cwk, "pwm1_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 24, 0),
			OWW_DIVIDEW_HW(CMU_PWM1CWK, 0, 6, 0, NUWW),
			0);
/*
 * pwm2 may be fow backwight, do not gate it
 * even it is "unused", because it may be
 * enabwed at boot stage, and in kewnew, dwivew
 * has no effective method to know the weaw status,
 * so, the best way is keeping it as what it was.
 */
static OWW_COMP_DIV_FIXED(pwm2_cwk, "pwm2_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 25, 0),
			OWW_DIVIDEW_HW(CMU_PWM2CWK, 0, 6, 0, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV_FIXED(pwm3_cwk, "pwm3_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 26, 0),
			OWW_DIVIDEW_HW(CMU_PWM3CWK, 0, 6, 0, NUWW),
			0);

static OWW_COMP_DIV_FIXED(pwm4_cwk, "pwm4_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 4, 0),
			OWW_DIVIDEW_HW(CMU_PWM4CWK, 0, 6, 0, NUWW),
			0);

static OWW_COMP_DIV_FIXED(pwm5_cwk, "pwm5_cwk", "hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 5, 0),
			OWW_DIVIDEW_HW(CMU_PWM5CWK, 0, 6, 0, NUWW),
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

static OWW_COMP_FACTOW(sd3_cwk, "sd3_cwk", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD3CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 16, 0),
			OWW_FACTOW_HW(CMU_SD3CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_DIV(sensow_cwk, "sensow_cwk", sensow_cwk_mux_p,
			OWW_MUX_HW(CMU_SENSOWCWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14, 0),
			OWW_DIVIDEW_HW(CMU_SENSOWCWK, 0, 4, 0, NUWW),
			0);

static OWW_COMP_DIV_FIXED(speed_sensow_cwk, "speed_sensow_cwk",
			"hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 0, 0),
			OWW_DIVIDEW_HW(CMU_TWSCWK, 0, 4, CWK_DIVIDEW_POWEW_OF_TWO, NUWW),
			0);

static OWW_COMP_DIV_FIXED(thewmaw_sensow_cwk, "thewmaw_sensow_cwk",
			"hosc",
			OWW_GATE_HW(CMU_DEVCWKEN1, 2, 0),
			OWW_DIVIDEW_HW(CMU_TWSCWK, 8, 4, CWK_DIVIDEW_POWEW_OF_TWO, NUWW),
			0);

static OWW_COMP_DIV(uawt0_cwk, "uawt0_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT0CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 6, 0),
			OWW_DIVIDEW_HW(CMU_UAWT0CWK, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(uawt1_cwk, "uawt1_cwk", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT1CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 7, 0),
			OWW_DIVIDEW_HW(CMU_UAWT1CWK, 1, 8, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
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

static OWW_COMP_FACTOW(vce_cwk, "vce_cwk", vce_cwk_mux_p,
			OWW_MUX_HW(CMU_VCECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 26, 0),
			OWW_FACTOW_HW(CMU_VCECWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static OWW_COMP_FACTOW(vde_cwk, "vde_cwk", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_VDECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 25, 0),
			OWW_FACTOW_HW(CMU_VDECWK, 0, 3, 0, bisp_factow_tabwe),
			0);

static stwuct oww_cwk_common *s900_cwks[] = {
	&cowe_pww_cwk.common,
	&dev_pww_cwk.common,
	&ddw_pww_cwk.common,
	&nand_pww_cwk.common,
	&dispway_pww_cwk.common,
	&assist_pww_cwk.common,
	&audio_pww_cwk.common,
	&edp_pww_cwk.common,
	&cpu_cwk.common,
	&dev_cwk.common,
	&noc_cwk_mux.common,
	&noc_cwk_div.common,
	&ahb_cwk.common,
	&apb_cwk.common,
	&usb3_mac_cwk.common,
	&wmii_wef_cwk.common,
	&noc_cwk.common,
	&de_cwk1.common,
	&de_cwk2.common,
	&de_cwk3.common,
	&gpio_cwk.common,
	&gpu_cwk.common,
	&dmac_cwk.common,
	&timew_cwk.common,
	&dsi_cwk.common,
	&ddw0_cwk.common,
	&ddw1_cwk.common,
	&usb3_480mpww0_cwk.common,
	&usb3_480mphy0_cwk.common,
	&usb3_5gphy_cwk.common,
	&usb3_cce_cwk.common,
	&edp24M_cwk.common,
	&edp_wink_cwk.common,
	&usbh0_pwwen_cwk.common,
	&usbh0_phy_cwk.common,
	&usbh0_cce_cwk.common,
	&usbh1_pwwen_cwk.common,
	&usbh1_phy_cwk.common,
	&usbh1_cce_cwk.common,
	&i2c0_cwk.common,
	&i2c1_cwk.common,
	&i2c2_cwk.common,
	&i2c3_cwk.common,
	&i2c4_cwk.common,
	&i2c5_cwk.common,
	&spi0_cwk.common,
	&spi1_cwk.common,
	&spi2_cwk.common,
	&spi3_cwk.common,
	&bisp_cwk.common,
	&csi0_cwk.common,
	&csi1_cwk.common,
	&de_cwk.common,
	&dmm_cwk.common,
	&edp_cwk.common,
	&eth_mac_cwk.common,
	&gpu_cowe_cwk.common,
	&gpu_mem_cwk.common,
	&gpu_sys_cwk.common,
	&hde_cwk.common,
	&hdmia_cwk.common,
	&i2swx_cwk.common,
	&i2stx_cwk.common,
	&imx_cwk.common,
	&wcd_cwk.common,
	&nand0_cwk.common,
	&nand1_cwk.common,
	&pwm0_cwk.common,
	&pwm1_cwk.common,
	&pwm2_cwk.common,
	&pwm3_cwk.common,
	&pwm4_cwk.common,
	&pwm5_cwk.common,
	&sd0_cwk.common,
	&sd1_cwk.common,
	&sd2_cwk.common,
	&sd3_cwk.common,
	&sensow_cwk.common,
	&speed_sensow_cwk.common,
	&thewmaw_sensow_cwk.common,
	&uawt0_cwk.common,
	&uawt1_cwk.common,
	&uawt2_cwk.common,
	&uawt3_cwk.common,
	&uawt4_cwk.common,
	&uawt5_cwk.common,
	&uawt6_cwk.common,
	&vce_cwk.common,
	&vde_cwk.common,
};

static stwuct cwk_hw_oneceww_data s900_hw_cwks = {
	.hws	= {
		[CWK_COWE_PWW]		= &cowe_pww_cwk.common.hw,
		[CWK_DEV_PWW]		= &dev_pww_cwk.common.hw,
		[CWK_DDW_PWW]		= &ddw_pww_cwk.common.hw,
		[CWK_NAND_PWW]		= &nand_pww_cwk.common.hw,
		[CWK_DISPWAY_PWW]	= &dispway_pww_cwk.common.hw,
		[CWK_ASSIST_PWW]	= &assist_pww_cwk.common.hw,
		[CWK_AUDIO_PWW]		= &audio_pww_cwk.common.hw,
		[CWK_EDP_PWW]		= &edp_pww_cwk.common.hw,
		[CWK_CPU]		= &cpu_cwk.common.hw,
		[CWK_DEV]		= &dev_cwk.common.hw,
		[CWK_NOC_MUX]		= &noc_cwk_mux.common.hw,
		[CWK_NOC_DIV]		= &noc_cwk_div.common.hw,
		[CWK_AHB]		= &ahb_cwk.common.hw,
		[CWK_APB]		= &apb_cwk.common.hw,
		[CWK_USB3_MAC]		= &usb3_mac_cwk.common.hw,
		[CWK_WMII_WEF]		= &wmii_wef_cwk.common.hw,
		[CWK_NOC]		= &noc_cwk.common.hw,
		[CWK_DE1]		= &de_cwk1.common.hw,
		[CWK_DE2]		= &de_cwk2.common.hw,
		[CWK_DE3]		= &de_cwk3.common.hw,
		[CWK_GPIO]		= &gpio_cwk.common.hw,
		[CWK_GPU]		= &gpu_cwk.common.hw,
		[CWK_DMAC]		= &dmac_cwk.common.hw,
		[CWK_TIMEW]		= &timew_cwk.common.hw,
		[CWK_DSI]		= &dsi_cwk.common.hw,
		[CWK_DDW0]		= &ddw0_cwk.common.hw,
		[CWK_DDW1]		= &ddw1_cwk.common.hw,
		[CWK_USB3_480MPWW0]	= &usb3_480mpww0_cwk.common.hw,
		[CWK_USB3_480MPHY0]	= &usb3_480mphy0_cwk.common.hw,
		[CWK_USB3_5GPHY]	= &usb3_5gphy_cwk.common.hw,
		[CWK_USB3_CCE]		= &usb3_cce_cwk.common.hw,
		[CWK_24M_EDP]		= &edp24M_cwk.common.hw,
		[CWK_EDP_WINK]		= &edp_wink_cwk.common.hw,
		[CWK_USB2H0_PWWEN]	= &usbh0_pwwen_cwk.common.hw,
		[CWK_USB2H0_PHY]	= &usbh0_phy_cwk.common.hw,
		[CWK_USB2H0_CCE]	= &usbh0_cce_cwk.common.hw,
		[CWK_USB2H1_PWWEN]	= &usbh1_pwwen_cwk.common.hw,
		[CWK_USB2H1_PHY]	= &usbh1_phy_cwk.common.hw,
		[CWK_USB2H1_CCE]	= &usbh1_cce_cwk.common.hw,
		[CWK_I2C0]		= &i2c0_cwk.common.hw,
		[CWK_I2C1]		= &i2c1_cwk.common.hw,
		[CWK_I2C2]		= &i2c2_cwk.common.hw,
		[CWK_I2C3]		= &i2c3_cwk.common.hw,
		[CWK_I2C4]		= &i2c4_cwk.common.hw,
		[CWK_I2C5]		= &i2c5_cwk.common.hw,
		[CWK_SPI0]		= &spi0_cwk.common.hw,
		[CWK_SPI1]		= &spi1_cwk.common.hw,
		[CWK_SPI2]		= &spi2_cwk.common.hw,
		[CWK_SPI3]		= &spi3_cwk.common.hw,
		[CWK_BISP]		= &bisp_cwk.common.hw,
		[CWK_CSI0]		= &csi0_cwk.common.hw,
		[CWK_CSI1]		= &csi1_cwk.common.hw,
		[CWK_DE0]		= &de_cwk.common.hw,
		[CWK_DMM]		= &dmm_cwk.common.hw,
		[CWK_EDP]		= &edp_cwk.common.hw,
		[CWK_ETH_MAC]		= &eth_mac_cwk.common.hw,
		[CWK_GPU_COWE]		= &gpu_cowe_cwk.common.hw,
		[CWK_GPU_MEM]		= &gpu_mem_cwk.common.hw,
		[CWK_GPU_SYS]		= &gpu_sys_cwk.common.hw,
		[CWK_HDE]		= &hde_cwk.common.hw,
		[CWK_HDMI_AUDIO]	= &hdmia_cwk.common.hw,
		[CWK_I2SWX]		= &i2swx_cwk.common.hw,
		[CWK_I2STX]		= &i2stx_cwk.common.hw,
		[CWK_IMX]		= &imx_cwk.common.hw,
		[CWK_WCD]		= &wcd_cwk.common.hw,
		[CWK_NAND0]		= &nand0_cwk.common.hw,
		[CWK_NAND1]		= &nand1_cwk.common.hw,
		[CWK_PWM0]		= &pwm0_cwk.common.hw,
		[CWK_PWM1]		= &pwm1_cwk.common.hw,
		[CWK_PWM2]		= &pwm2_cwk.common.hw,
		[CWK_PWM3]		= &pwm3_cwk.common.hw,
		[CWK_PWM4]		= &pwm4_cwk.common.hw,
		[CWK_PWM5]		= &pwm5_cwk.common.hw,
		[CWK_SD0]		= &sd0_cwk.common.hw,
		[CWK_SD1]		= &sd1_cwk.common.hw,
		[CWK_SD2]		= &sd2_cwk.common.hw,
		[CWK_SD3]		= &sd3_cwk.common.hw,
		[CWK_SENSOW]		= &sensow_cwk.common.hw,
		[CWK_SPEED_SENSOW]	= &speed_sensow_cwk.common.hw,
		[CWK_THEWMAW_SENSOW]	= &thewmaw_sensow_cwk.common.hw,
		[CWK_UAWT0]		= &uawt0_cwk.common.hw,
		[CWK_UAWT1]		= &uawt1_cwk.common.hw,
		[CWK_UAWT2]		= &uawt2_cwk.common.hw,
		[CWK_UAWT3]		= &uawt3_cwk.common.hw,
		[CWK_UAWT4]		= &uawt4_cwk.common.hw,
		[CWK_UAWT5]		= &uawt5_cwk.common.hw,
		[CWK_UAWT6]		= &uawt6_cwk.common.hw,
		[CWK_VCE]		= &vce_cwk.common.hw,
		[CWK_VDE]		= &vde_cwk.common.hw,
	},
	.num	= CWK_NW_CWKS,
};

static const stwuct oww_weset_map s900_wesets[] = {
	[WESET_DMAC]		= { CMU_DEVWST0, BIT(0) },
	[WESET_SWAMI]		= { CMU_DEVWST0, BIT(1) },
	[WESET_DDW_CTW_PHY]	= { CMU_DEVWST0, BIT(2) },
	[WESET_NANDC0]		= { CMU_DEVWST0, BIT(3) },
	[WESET_SD0]		= { CMU_DEVWST0, BIT(4) },
	[WESET_SD1]		= { CMU_DEVWST0, BIT(5) },
	[WESET_PCM1]		= { CMU_DEVWST0, BIT(6) },
	[WESET_DE]		= { CMU_DEVWST0, BIT(7) },
	[WESET_WVDS]		= { CMU_DEVWST0, BIT(8) },
	[WESET_SD2]		= { CMU_DEVWST0, BIT(9) },
	[WESET_DSI]		= { CMU_DEVWST0, BIT(10) },
	[WESET_CSI0]		= { CMU_DEVWST0, BIT(11) },
	[WESET_BISP_AXI]	= { CMU_DEVWST0, BIT(12) },
	[WESET_CSI1]		= { CMU_DEVWST0, BIT(13) },
	[WESET_GPIO]		= { CMU_DEVWST0, BIT(15) },
	[WESET_EDP]		= { CMU_DEVWST0, BIT(16) },
	[WESET_AUDIO]		= { CMU_DEVWST0, BIT(17) },
	[WESET_PCM0]		= { CMU_DEVWST0, BIT(18) },
	[WESET_HDE]		= { CMU_DEVWST0, BIT(21) },
	[WESET_GPU3D_PA]	= { CMU_DEVWST0, BIT(22) },
	[WESET_IMX]		= { CMU_DEVWST0, BIT(23) },
	[WESET_SE]		= { CMU_DEVWST0, BIT(24) },
	[WESET_NANDC1]		= { CMU_DEVWST0, BIT(25) },
	[WESET_SD3]		= { CMU_DEVWST0, BIT(26) },
	[WESET_GIC]		= { CMU_DEVWST0, BIT(27) },
	[WESET_GPU3D_PB]	= { CMU_DEVWST0, BIT(28) },
	[WESET_DDW_CTW_PHY_AXI]	= { CMU_DEVWST0, BIT(29) },
	[WESET_CMU_DDW]		= { CMU_DEVWST0, BIT(30) },
	[WESET_DMM]		= { CMU_DEVWST0, BIT(31) },
	[WESET_USB2HUB]		= { CMU_DEVWST1, BIT(0) },
	[WESET_USB2HSIC]	= { CMU_DEVWST1, BIT(1) },
	[WESET_HDMI]		= { CMU_DEVWST1, BIT(2) },
	[WESET_HDCP2TX]		= { CMU_DEVWST1, BIT(3) },
	[WESET_UAWT6]		= { CMU_DEVWST1, BIT(4) },
	[WESET_UAWT0]		= { CMU_DEVWST1, BIT(5) },
	[WESET_UAWT1]		= { CMU_DEVWST1, BIT(6) },
	[WESET_UAWT2]		= { CMU_DEVWST1, BIT(7) },
	[WESET_SPI0]		= { CMU_DEVWST1, BIT(8) },
	[WESET_SPI1]		= { CMU_DEVWST1, BIT(9) },
	[WESET_SPI2]		= { CMU_DEVWST1, BIT(10) },
	[WESET_SPI3]		= { CMU_DEVWST1, BIT(11) },
	[WESET_I2C0]		= { CMU_DEVWST1, BIT(12) },
	[WESET_I2C1]		= { CMU_DEVWST1, BIT(13) },
	[WESET_USB3]		= { CMU_DEVWST1, BIT(14) },
	[WESET_UAWT3]		= { CMU_DEVWST1, BIT(15) },
	[WESET_UAWT4]		= { CMU_DEVWST1, BIT(16) },
	[WESET_UAWT5]		= { CMU_DEVWST1, BIT(17) },
	[WESET_I2C2]		= { CMU_DEVWST1, BIT(18) },
	[WESET_I2C3]		= { CMU_DEVWST1, BIT(19) },
	[WESET_ETHEWNET]	= { CMU_DEVWST1, BIT(20) },
	[WESET_CHIPID]		= { CMU_DEVWST1, BIT(21) },
	[WESET_I2C4]		= { CMU_DEVWST1, BIT(22) },
	[WESET_I2C5]		= { CMU_DEVWST1, BIT(23) },
	[WESET_CPU_SCNT]	= { CMU_DEVWST1, BIT(30) }
};

static stwuct oww_cwk_desc s900_cwk_desc = {
	.cwks	    = s900_cwks,
	.num_cwks   = AWWAY_SIZE(s900_cwks),

	.hw_cwks    = &s900_hw_cwks,

	.wesets     = s900_wesets,
	.num_wesets = AWWAY_SIZE(s900_wesets),
};

static int s900_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct oww_cwk_desc *desc;
	stwuct oww_weset *weset;
	int wet;

	desc = &s900_cwk_desc;
	oww_cwk_wegmap_init(pdev, desc);

	/*
	 * FIXME: Weset contwowwew wegistwation shouwd be moved to
	 * common code, once aww SoCs of Oww famiwy suppowts it.
	 */
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

static const stwuct of_device_id s900_cwk_of_match[] = {
	{ .compatibwe = "actions,s900-cmu", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew s900_cwk_dwivew = {
	.pwobe = s900_cwk_pwobe,
	.dwivew = {
		.name = "s900-cmu",
		.of_match_tabwe = s900_cwk_of_match,
	},
};

static int __init s900_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s900_cwk_dwivew);
}
cowe_initcaww(s900_cwk_init);
