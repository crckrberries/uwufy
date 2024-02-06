// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Actions Semi S700 cwock dwivew
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Authow: David Wiu <wiuwei@actions-semi.com>
 *
 * Authow: Pathiban Nawwathambi <pn@denx.de>
 * Authow: Sawavanan Sekaw <swavanhome@gmaiw.com>
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

#incwude <dt-bindings/cwock/actions,s700-cmu.h>
#incwude <dt-bindings/weset/actions,s700-weset.h>

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
#define CMU_DSIPWWCWK		(0x0028)
#define CMU_CSICWK		(0x002C)
#define CMU_DECWK		(0x0030)
#define CMU_SICWK		(0x0034)
#define CMU_BUSCWK1		(0x0038)
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
#define CMU_UAWT3CWK		(0x0068)
#define CMU_UAWT4CWK		(0x006C)
#define CMU_UAWT5CWK		(0x0070)
#define CMU_UAWT6CWK		(0x0074)
#define CMU_PWM0CWK		(0x0078)
#define CMU_PWM1CWK		(0x007C)
#define CMU_PWM2CWK		(0x0080)
#define CMU_PWM3CWK		(0x0084)
#define CMU_PWM4CWK		(0x0088)
#define CMU_PWM5CWK		(0x008C)
#define CMU_GPU3DCWK		(0x0090)
#define CMU_COWECTW		(0x009C)
#define CMU_DEVCWKEN0		(0x00A0)
#define CMU_DEVCWKEN1		(0x00A4)
#define CMU_DEVWST0		(0x00A8)
#define CMU_DEVWST1		(0x00AC)
#define CMU_USBPWW		(0x00B0)
#define CMU_ETHEWNETPWW		(0x00B4)
#define CMU_CVBSPWW		(0x00B8)
#define CMU_SSTSCWK		(0x00C0)

static stwuct cwk_pww_tabwe cwk_audio_pww_tabwe[] = {
	{0, 45158400}, {1, 49152000},
	{ /* sentinew */ }
};

static stwuct cwk_pww_tabwe cwk_cvbs_pww_tabwe[] = {
	{27, 29 * 12000000}, {28, 30 * 12000000}, {29, 31 * 12000000},
	{30, 32 * 12000000}, {31, 33 * 12000000}, {32, 34 * 12000000},
	{33, 35 * 12000000}, {34, 36 * 12000000}, {35, 37 * 12000000},
	{36, 38 * 12000000}, {37, 39 * 12000000}, {38, 40 * 12000000},
	{39, 41 * 12000000}, {40, 42 * 12000000}, {41, 43 * 12000000},
	{42, 44 * 12000000}, {43, 45 * 12000000},
	{ /* sentinew */ }
};

/* pww cwocks */
static OWW_PWW_NO_PAWENT(cwk_cowe_pww,   "cowe_pww", CMU_COWEPWW, 12000000, 9, 0, 8,  4, 174, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_dev_pww,    "dev_pww", CMU_DEVPWW,  6000000, 8, 0, 8, 8, 126, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_ddw_pww,    "ddw_pww", CMU_DDWPWW, 6000000, 8, 0, 8,  2,  180, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_nand_pww,   "nand_pww", CMU_NANDPWW,  6000000, 8, 0, 8,  2, 86, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_dispway_pww, "dispway_pww", CMU_DISPWAYPWW, 6000000, 8, 0, 8, 2, 140, NUWW, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_cvbs_pww, "cvbs_pww", CMU_CVBSPWW, 0, 8, 0, 8, 27, 43, cwk_cvbs_pww_tabwe, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_audio_pww,  "audio_pww", CMU_AUDIOPWW, 0, 4, 0, 1, 0, 0, cwk_audio_pww_tabwe, CWK_IGNOWE_UNUSED);
static OWW_PWW_NO_PAWENT(cwk_ethewnet_pww, "ethewnet_pww", CMU_ETHEWNETPWW, 500000000, 0, 0, 0, 0, 0, NUWW, CWK_IGNOWE_UNUSED);

static const chaw *cpu_cwk_mux_p[] = {"wosc", "hosc", "cowe_pww", "noc1_cwk_div"};
static const chaw *dev_cwk_p[] = { "hosc", "dev_pww"};
static const chaw *noc_cwk_mux_p[] = { "dev_cwk", "dispway_pww", "nand_pww", "ddw_pww", "cvbs_pww"};

static const chaw *csi_cwk_mux_p[] = { "dispway_pww", "dev_cwk"};
static const chaw *de_cwk_mux_p[] = { "dispway_pww", "dev_cwk"};
static const chaw *hde_cwk_mux_p[] = { "dev_cwk", "dispway_pww", "nand_pww", "ddw_pww"};
static const chaw *nand_cwk_mux_p[] = { "nand_pww", "dispway_pww", "dev_cwk", "ddw_pww"};
static const chaw *sd_cwk_mux_p[] = { "dev_cwk", "nand_pww", };
static const chaw *uawt_cwk_mux_p[] = { "hosc", "dev_pww"};
static const chaw *pwm_cwk_mux_p[] = { "wosc", "hosc"};
static const chaw *gpu_cwk_mux_p[] = { "dev_cwk", "dispway_pww", "nand_pww", "ddw_cwk", "cvbs_pww"};
static const chaw *wcd_cwk_mux_p[] = { "dispway_pww", "dev_cwk" };
static const chaw *i2s_cwk_mux_p[] = { "audio_pww" };
static const chaw *sensow_cwk_mux_p[] = { "hosc", "si"};

/* mux cwocks */
static OWW_MUX(cwk_cpu, "cpu_cwk", cpu_cwk_mux_p,  CMU_BUSCWK, 0, 2, CWK_SET_WATE_PAWENT);
static OWW_MUX(cwk_dev, "dev_cwk", dev_cwk_p, CMU_DEVPWW, 12, 1, CWK_SET_WATE_PAWENT);
static OWW_MUX(cwk_noc0_cwk_mux, "noc0_cwk_mux", noc_cwk_mux_p, CMU_BUSCWK, 4, 3, CWK_SET_WATE_PAWENT);
static OWW_MUX(cwk_noc1_cwk_mux, "noc1_cwk_mux", noc_cwk_mux_p, CMU_BUSCWK1, 4, 3, CWK_SET_WATE_PAWENT);
static OWW_MUX(cwk_hp_cwk_mux, "hp_cwk_mux", noc_cwk_mux_p, CMU_BUSCWK1, 8, 3, CWK_SET_WATE_PAWENT);

static stwuct cwk_factow_tabwe sd_factow_tabwe[] = {
	/* bit0 ~ 4 */
	{0, 1, 1}, {1, 1, 2}, {2, 1, 3}, {3, 1, 4},
	{4, 1, 5}, {5, 1, 6}, {6, 1, 7}, {7, 1, 8},
	{8, 1, 9}, {9, 1, 10}, {10, 1, 11}, {11, 1, 12},
	{12, 1, 13}, {13, 1, 14}, {14, 1, 15}, {15, 1, 16},
	{16, 1, 17}, {17, 1, 18}, {18, 1, 19}, {19, 1, 20},
	{20, 1, 21}, {21, 1, 22}, {22, 1, 23}, {23, 1, 24},
	{24, 1, 25}, {25, 1, 26},

	/* bit8: /128 */
	{256, 1, 1 * 128}, {257, 1, 2 * 128}, {258, 1, 3 * 128}, {259, 1, 4 * 128},
	{260, 1, 5 * 128}, {261, 1, 6 * 128}, {262, 1, 7 * 128}, {263, 1, 8 * 128},
	{264, 1, 9 * 128}, {265, 1, 10 * 128}, {266, 1, 11 * 128}, {267, 1, 12 * 128},
	{268, 1, 13 * 128}, {269, 1, 14 * 128}, {270, 1, 15 * 128}, {271, 1, 16 * 128},
	{272, 1, 17 * 128}, {273, 1, 18 * 128}, {274, 1, 19 * 128}, {275, 1, 20 * 128},
	{276, 1, 21 * 128}, {277, 1, 22 * 128}, {278, 1, 23 * 128}, {279, 1, 24 * 128},
	{280, 1, 25 * 128}, {281, 1, 26 * 128},

	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe wcd_factow_tabwe[] = {
	/* bit0 ~ 3 */
	{0, 1, 1}, {1, 1, 2}, {2, 1, 3}, {3, 1, 4},
	{4, 1, 5}, {5, 1, 6}, {6, 1, 7}, {7, 1, 8},
	{8, 1, 9}, {9, 1, 10}, {10, 1, 11}, {11, 1, 12},

	/* bit8: /7 */
	{256, 1, 1 * 7}, {257, 1, 2 * 7}, {258, 1, 3 * 7}, {259, 1, 4 * 7},
	{260, 1, 5 * 7}, {261, 1, 6 * 7}, {262, 1, 7 * 7}, {263, 1, 8 * 7},
	{264, 1, 9 * 7}, {265, 1, 10 * 7}, {266, 1, 11 * 7}, {267, 1, 12 * 7},
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe hdmia_div_tabwe[] = {
	{0, 1},   {1, 2},   {2, 3},   {3, 4},
	{4, 6},   {5, 8},   {6, 12},  {7, 16},
	{8, 24},
	{ /* sentinew */ }
};

static stwuct cwk_div_tabwe wmii_div_tabwe[] = {
	{0, 4},   {1, 10},
	{ /* sentinew */ }
};

/* dividew cwocks */
static OWW_DIVIDEW(cwk_noc0, "noc0_cwk", "noc0_cwk_mux", CMU_BUSCWK, 16, 2, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_noc1, "noc1_cwk", "noc1_cwk_mux", CMU_BUSCWK1, 16, 2, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_noc1_cwk_div, "noc1_cwk_div", "noc1_cwk", CMU_BUSCWK1, 20, 1, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_hp_cwk_div, "hp_cwk_div", "hp_cwk_mux", CMU_BUSCWK1, 12, 2, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_ahb, "ahb_cwk", "hp_cwk_div", CMU_BUSCWK1, 2, 2, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_apb, "apb_cwk", "ahb_cwk", CMU_BUSCWK1, 14, 2, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_sensow0, "sensow0", "sensow_swc", CMU_SENSOWCWK, 0, 4, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_sensow1, "sensow1", "sensow_swc", CMU_SENSOWCWK, 8, 4, NUWW, 0, 0);
static OWW_DIVIDEW(cwk_wmii_wef, "wmii_wef", "ethewnet_pww", CMU_ETHEWNETPWW, 2, 1, wmii_div_tabwe, 0, 0);

static stwuct cwk_factow_tabwe de_factow_tabwe[] = {
	{0, 1, 1}, {1, 2, 3}, {2, 1, 2}, {3, 2, 5},
	{4, 1, 3}, {5, 1, 4}, {6, 1, 6}, {7, 1, 8},
	{8, 1, 12},
	{ /* sentinew */ }
};

static stwuct cwk_factow_tabwe hde_factow_tabwe[] = {
	{0, 1, 1}, {1, 2, 3}, {2, 1, 2}, {3, 2, 5},
	{4, 1, 3}, {5, 1, 4}, {6, 1, 6}, {7, 1, 8},
	{ /* sentinew */ }
};

/* gate cwocks */
static OWW_GATE(cwk_gpio, "gpio", "apb_cwk", CMU_DEVCWKEN1, 25, 0, 0);
static OWW_GATE(cwk_dmac, "dmac", "hp_cwk_div", CMU_DEVCWKEN0, 17, 0, 0);
static OWW_GATE(cwk_timew, "timew", "hosc", CMU_DEVCWKEN1, 22, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_dsi, "dsi_cwk", CMU_DEVCWKEN0, 2, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_tvout, "tvout_cwk", CMU_DEVCWKEN0, 3, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_hdmi_dev, "hdmi_dev", CMU_DEVCWKEN0, 5, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb3_480mpww0, "usb3_480mpww0", CMU_USBPWW, 3, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb3_480mphy0, "usb3_480mphy0", CMU_USBPWW, 2, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb3_5gphy, "usb3_5gphy", CMU_USBPWW, 1, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb3_cce, "usb3_cce", CMU_DEVCWKEN0, 25, 0, 0);
static OWW_GATE(cwk_i2c0, "i2c0", "hosc", CMU_DEVCWKEN1, 0, 0, 0);
static OWW_GATE(cwk_i2c1, "i2c1", "hosc", CMU_DEVCWKEN1, 1, 0, 0);
static OWW_GATE(cwk_i2c2, "i2c2", "hosc", CMU_DEVCWKEN1, 2, 0, 0);
static OWW_GATE(cwk_i2c3, "i2c3", "hosc", CMU_DEVCWKEN1, 3, 0, 0);
static OWW_GATE(cwk_spi0, "spi0", "ahb_cwk", CMU_DEVCWKEN1, 4, 0, 0);
static OWW_GATE(cwk_spi1, "spi1", "ahb_cwk", CMU_DEVCWKEN1, 5, 0, 0);
static OWW_GATE(cwk_spi2, "spi2", "ahb_cwk", CMU_DEVCWKEN1, 6, 0, 0);
static OWW_GATE(cwk_spi3, "spi3", "ahb_cwk", CMU_DEVCWKEN1, 7, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h0_pwwen, "usbh0_pwwen", CMU_USBPWW, 12, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h0_phy, "usbh0_phy", CMU_USBPWW, 10, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h0_cce, "usbh0_cce", CMU_DEVCWKEN0, 26, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h1_pwwen, "usbh1_pwwen", CMU_USBPWW, 13, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h1_phy, "usbh1_phy", CMU_USBPWW, 11, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_usb2h1_cce, "usbh1_cce", CMU_DEVCWKEN0, 27, 0, 0);
static OWW_GATE_NO_PAWENT(cwk_iwc_switch, "iwc_switch", CMU_DEVCWKEN1, 15, 0, 0);

/* composite cwocks */

static OWW_COMP_DIV(cwk_csi, "csi", csi_cwk_mux_p,
			OWW_MUX_HW(CMU_CSICWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 13, 0),
			OWW_DIVIDEW_HW(CMU_CSICWK, 0, 4, 0, NUWW),
			0);

static OWW_COMP_DIV(cwk_si, "si", csi_cwk_mux_p,
			OWW_MUX_HW(CMU_SICWK, 4, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 14,  0),
			OWW_DIVIDEW_HW(CMU_SICWK, 0, 4, 0, NUWW),
			0);

static OWW_COMP_FACTOW(cwk_de, "de", de_cwk_mux_p,
			OWW_MUX_HW(CMU_DECWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 0,  0),
			OWW_FACTOW_HW(CMU_DECWK, 0, 3, 0, de_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_hde, "hde", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_HDECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 9, 0),
			OWW_FACTOW_HW(CMU_HDECWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_vde, "vde", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_VDECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 10,  0),
			OWW_FACTOW_HW(CMU_VDECWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_vce, "vce", hde_cwk_mux_p,
			OWW_MUX_HW(CMU_VCECWK, 4, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 11, 0),
			OWW_FACTOW_HW(CMU_VCECWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_DIV(cwk_nand, "nand", nand_cwk_mux_p,
			OWW_MUX_HW(CMU_NANDCCWK, 8, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 21, 0),
			OWW_DIVIDEW_HW(CMU_NANDCCWK, 0, 3, 0, NUWW),
			CWK_SET_WATE_PAWENT);

static OWW_COMP_FACTOW(cwk_sd0, "sd0", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD0CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 22, 0),
			OWW_FACTOW_HW(CMU_SD0CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_sd1, "sd1", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD1CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 23, 0),
			OWW_FACTOW_HW(CMU_SD1CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_sd2, "sd2", sd_cwk_mux_p,
			OWW_MUX_HW(CMU_SD2CWK, 9, 1),
			OWW_GATE_HW(CMU_DEVCWKEN0, 24, 0),
			OWW_FACTOW_HW(CMU_SD2CWK, 0, 9, 0, sd_factow_tabwe),
			0);

static OWW_COMP_DIV(cwk_uawt0, "uawt0", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT0CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 8, 0),
			OWW_DIVIDEW_HW(CMU_UAWT0CWK, 0, 9, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt1, "uawt1", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT1CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 9, 0),
			OWW_DIVIDEW_HW(CMU_UAWT1CWK, 0, 9, CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt2, "uawt2", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT2CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 10, 0),
			OWW_DIVIDEW_HW(CMU_UAWT2CWK, 0, 9,  CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt3, "uawt3", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT3CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 11, 0),
			OWW_DIVIDEW_HW(CMU_UAWT3CWK, 0, 9,  CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt4, "uawt4", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT4CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 12, 0),
			OWW_DIVIDEW_HW(CMU_UAWT4CWK, 0, 9,  CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt5, "uawt5", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT5CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 13, 0),
			OWW_DIVIDEW_HW(CMU_UAWT5CWK, 0, 9,  CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_uawt6, "uawt6", uawt_cwk_mux_p,
			OWW_MUX_HW(CMU_UAWT6CWK, 16, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 14, 0),
			OWW_DIVIDEW_HW(CMU_UAWT6CWK, 0, 9,  CWK_DIVIDEW_WOUND_CWOSEST, NUWW),
			0);

static OWW_COMP_DIV(cwk_pwm0, "pwm0", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM0CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 16, 0),
			OWW_DIVIDEW_HW(CMU_PWM0CWK, 0, 10, 0, NUWW),
			CWK_IGNOWE_UNUSED);

static OWW_COMP_DIV(cwk_pwm1, "pwm1", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM1CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 17, 0),
			OWW_DIVIDEW_HW(CMU_PWM1CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(cwk_pwm2, "pwm2", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM2CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 18, 0),
			OWW_DIVIDEW_HW(CMU_PWM2CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(cwk_pwm3, "pwm3", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM3CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 19, 0),
			OWW_DIVIDEW_HW(CMU_PWM3CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(cwk_pwm4, "pwm4", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM4CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 20, 0),
			OWW_DIVIDEW_HW(CMU_PWM4CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_DIV(cwk_pwm5, "pwm5", pwm_cwk_mux_p,
			OWW_MUX_HW(CMU_PWM5CWK, 12, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 21, 0),
			OWW_DIVIDEW_HW(CMU_PWM5CWK, 0, 10, 0, NUWW),
			0);

static OWW_COMP_FACTOW(cwk_gpu3d, "gpu3d", gpu_cwk_mux_p,
			OWW_MUX_HW(CMU_GPU3DCWK, 4, 3),
			OWW_GATE_HW(CMU_DEVCWKEN0, 8, 0),
			OWW_FACTOW_HW(CMU_GPU3DCWK, 0, 3, 0, hde_factow_tabwe),
			0);

static OWW_COMP_FACTOW(cwk_wcd, "wcd", wcd_cwk_mux_p,
			OWW_MUX_HW(CMU_WCDCWK, 12, 2),
			OWW_GATE_HW(CMU_DEVCWKEN0, 1, 0),
			OWW_FACTOW_HW(CMU_WCDCWK, 0, 9, 0, wcd_factow_tabwe),
			0);

static OWW_COMP_DIV(cwk_hdmi_audio, "hdmia", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1), /*CMU_AUDIOPWW 24,1 unused*/
			OWW_GATE_HW(CMU_DEVCWKEN1, 28, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 24, 4, 0, hdmia_div_tabwe),
			0);

static OWW_COMP_DIV(cwk_i2swx, "i2swx", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 27, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 20, 4, 0, hdmia_div_tabwe),
			0);

static OWW_COMP_DIV(cwk_i2stx, "i2stx", i2s_cwk_mux_p,
			OWW_MUX_HW(CMU_AUDIOPWW, 24, 1),
			OWW_GATE_HW(CMU_DEVCWKEN1, 26, 0),
			OWW_DIVIDEW_HW(CMU_AUDIOPWW, 16, 4, 0, hdmia_div_tabwe),
			0);

/* fow bwuetooth pcm communication */
static OWW_COMP_FIXED_FACTOW(cwk_pcm1, "pcm1", "audio_pww",
			OWW_GATE_HW(CMU_DEVCWKEN1, 31, 0),
			1, 2, 0);

static OWW_COMP_DIV(cwk_sensow_swc, "sensow_swc", sensow_cwk_mux_p,
			OWW_MUX_HW(CMU_SENSOWCWK, 4, 1),
			{0},
			OWW_DIVIDEW_HW(CMU_SENSOWCWK, 5, 2, 0, NUWW),
			0);

static OWW_COMP_FIXED_FACTOW(cwk_ethewnet, "ethewnet", "ethewnet_pww",
			OWW_GATE_HW(CMU_DEVCWKEN1, 23, 0),
			1, 20, 0);

static OWW_COMP_DIV_FIXED(cwk_thewmaw_sensow, "thewmaw_sensow", "hosc",
				OWW_GATE_HW(CMU_DEVCWKEN0, 31, 0),
				OWW_DIVIDEW_HW(CMU_SSTSCWK, 20, 10, 0, NUWW),
				0);

static stwuct oww_cwk_common *s700_cwks[] = {
	&cwk_cowe_pww.common,
	&cwk_dev_pww.common,
	&cwk_ddw_pww.common,
	&cwk_nand_pww.common,
	&cwk_dispway_pww.common,
	&cwk_cvbs_pww .common,
	&cwk_audio_pww.common,
	&cwk_ethewnet_pww.common,
	&cwk_cpu.common,
	&cwk_dev.common,
	&cwk_ahb.common,
	&cwk_apb.common,
	&cwk_dmac.common,
	&cwk_noc0_cwk_mux.common,
	&cwk_noc1_cwk_mux.common,
	&cwk_hp_cwk_mux.common,
	&cwk_hp_cwk_div.common,
	&cwk_noc1_cwk_div.common,
	&cwk_noc0.common,
	&cwk_noc1.common,
	&cwk_sensow_swc.common,
	&cwk_gpio.common,
	&cwk_timew.common,
	&cwk_dsi.common,
	&cwk_csi.common,
	&cwk_si.common,
	&cwk_de.common,
	&cwk_hde.common,
	&cwk_vde.common,
	&cwk_vce.common,
	&cwk_nand.common,
	&cwk_sd0.common,
	&cwk_sd1.common,
	&cwk_sd2.common,
	&cwk_uawt0.common,
	&cwk_uawt1.common,
	&cwk_uawt2.common,
	&cwk_uawt3.common,
	&cwk_uawt4.common,
	&cwk_uawt5.common,
	&cwk_uawt6.common,
	&cwk_pwm0.common,
	&cwk_pwm1.common,
	&cwk_pwm2.common,
	&cwk_pwm3.common,
	&cwk_pwm4.common,
	&cwk_pwm5.common,
	&cwk_gpu3d.common,
	&cwk_i2c0.common,
	&cwk_i2c1.common,
	&cwk_i2c2.common,
	&cwk_i2c3.common,
	&cwk_spi0.common,
	&cwk_spi1.common,
	&cwk_spi2.common,
	&cwk_spi3.common,
	&cwk_usb3_480mpww0.common,
	&cwk_usb3_480mphy0.common,
	&cwk_usb3_5gphy.common,
	&cwk_usb3_cce.common,
	&cwk_wcd.common,
	&cwk_hdmi_audio.common,
	&cwk_i2swx.common,
	&cwk_i2stx.common,
	&cwk_sensow0.common,
	&cwk_sensow1.common,
	&cwk_hdmi_dev.common,
	&cwk_ethewnet.common,
	&cwk_wmii_wef.common,
	&cwk_usb2h0_pwwen.common,
	&cwk_usb2h0_phy.common,
	&cwk_usb2h0_cce.common,
	&cwk_usb2h1_pwwen.common,
	&cwk_usb2h1_phy.common,
	&cwk_usb2h1_cce.common,
	&cwk_tvout.common,
	&cwk_thewmaw_sensow.common,
	&cwk_iwc_switch.common,
	&cwk_pcm1.common,
};

static stwuct cwk_hw_oneceww_data s700_hw_cwks = {
	.hws    = {
			[CWK_COWE_PWW]				= &cwk_cowe_pww.common.hw,
			[CWK_DEV_PWW]				= &cwk_dev_pww.common.hw,
			[CWK_DDW_PWW]				= &cwk_ddw_pww.common.hw,
			[CWK_NAND_PWW]				= &cwk_nand_pww.common.hw,
			[CWK_DISPWAY_PWW]			= &cwk_dispway_pww.common.hw,
			[CWK_CVBS_PWW]				= &cwk_cvbs_pww .common.hw,
			[CWK_AUDIO_PWW]				= &cwk_audio_pww.common.hw,
			[CWK_ETHEWNET_PWW]			= &cwk_ethewnet_pww.common.hw,
			[CWK_CPU]				= &cwk_cpu.common.hw,
			[CWK_DEV]				= &cwk_dev.common.hw,
			[CWK_AHB]				= &cwk_ahb.common.hw,
			[CWK_APB]				= &cwk_apb.common.hw,
			[CWK_DMAC]				= &cwk_dmac.common.hw,
			[CWK_NOC0_CWK_MUX]			= &cwk_noc0_cwk_mux.common.hw,
			[CWK_NOC1_CWK_MUX]			= &cwk_noc1_cwk_mux.common.hw,
			[CWK_HP_CWK_MUX]			= &cwk_hp_cwk_mux.common.hw,
			[CWK_HP_CWK_DIV]			= &cwk_hp_cwk_div.common.hw,
			[CWK_NOC1_CWK_DIV]			= &cwk_noc1_cwk_div.common.hw,
			[CWK_NOC0]				= &cwk_noc0.common.hw,
			[CWK_NOC1]				= &cwk_noc1.common.hw,
			[CWK_SENOW_SWC]				= &cwk_sensow_swc.common.hw,
			[CWK_GPIO]				= &cwk_gpio.common.hw,
			[CWK_TIMEW]				= &cwk_timew.common.hw,
			[CWK_DSI]				= &cwk_dsi.common.hw,
			[CWK_CSI]				= &cwk_csi.common.hw,
			[CWK_SI]				= &cwk_si.common.hw,
			[CWK_DE]				= &cwk_de.common.hw,
			[CWK_HDE]				= &cwk_hde.common.hw,
			[CWK_VDE]				= &cwk_vde.common.hw,
			[CWK_VCE]				= &cwk_vce.common.hw,
			[CWK_NAND]				= &cwk_nand.common.hw,
			[CWK_SD0]				= &cwk_sd0.common.hw,
			[CWK_SD1]				= &cwk_sd1.common.hw,
			[CWK_SD2]				= &cwk_sd2.common.hw,
			[CWK_UAWT0]				= &cwk_uawt0.common.hw,
			[CWK_UAWT1]				= &cwk_uawt1.common.hw,
			[CWK_UAWT2]				= &cwk_uawt2.common.hw,
			[CWK_UAWT3]				= &cwk_uawt3.common.hw,
			[CWK_UAWT4]				= &cwk_uawt4.common.hw,
			[CWK_UAWT5]				= &cwk_uawt5.common.hw,
			[CWK_UAWT6]				= &cwk_uawt6.common.hw,
			[CWK_PWM0]				= &cwk_pwm0.common.hw,
			[CWK_PWM1]				= &cwk_pwm1.common.hw,
			[CWK_PWM2]				= &cwk_pwm2.common.hw,
			[CWK_PWM3]				= &cwk_pwm3.common.hw,
			[CWK_PWM4]				= &cwk_pwm4.common.hw,
			[CWK_PWM5]				= &cwk_pwm5.common.hw,
			[CWK_GPU3D]				= &cwk_gpu3d.common.hw,
			[CWK_I2C0]				= &cwk_i2c0.common.hw,
			[CWK_I2C1]				= &cwk_i2c1.common.hw,
			[CWK_I2C2]				= &cwk_i2c2.common.hw,
			[CWK_I2C3]				= &cwk_i2c3.common.hw,
			[CWK_SPI0]				= &cwk_spi0.common.hw,
			[CWK_SPI1]				= &cwk_spi1.common.hw,
			[CWK_SPI2]				= &cwk_spi2.common.hw,
			[CWK_SPI3]				= &cwk_spi3.common.hw,
			[CWK_USB3_480MPWW0]			= &cwk_usb3_480mpww0.common.hw,
			[CWK_USB3_480MPHY0]			= &cwk_usb3_480mphy0.common.hw,
			[CWK_USB3_5GPHY]			= &cwk_usb3_5gphy.common.hw,
			[CWK_USB3_CCE]				= &cwk_usb3_cce.common.hw,
			[CWK_WCD]				= &cwk_wcd.common.hw,
			[CWK_HDMI_AUDIO]			= &cwk_hdmi_audio.common.hw,
			[CWK_I2SWX]				= &cwk_i2swx.common.hw,
			[CWK_I2STX]				= &cwk_i2stx.common.hw,
			[CWK_SENSOW0]				= &cwk_sensow0.common.hw,
			[CWK_SENSOW1]				= &cwk_sensow1.common.hw,
			[CWK_HDMI_DEV]				= &cwk_hdmi_dev.common.hw,
			[CWK_ETHEWNET]				= &cwk_ethewnet.common.hw,
			[CWK_WMII_WEF]				= &cwk_wmii_wef.common.hw,
			[CWK_USB2H0_PWWEN]			= &cwk_usb2h0_pwwen.common.hw,
			[CWK_USB2H0_PHY]			= &cwk_usb2h0_phy.common.hw,
			[CWK_USB2H0_CCE]			= &cwk_usb2h0_cce.common.hw,
			[CWK_USB2H1_PWWEN]			= &cwk_usb2h1_pwwen.common.hw,
			[CWK_USB2H1_PHY]			= &cwk_usb2h1_phy.common.hw,
			[CWK_USB2H1_CCE]			= &cwk_usb2h1_cce.common.hw,
			[CWK_TVOUT]				= &cwk_tvout.common.hw,
			[CWK_THEWMAW_SENSOW]			= &cwk_thewmaw_sensow.common.hw,
			[CWK_IWC_SWITCH]			= &cwk_iwc_switch.common.hw,
			[CWK_PCM1]				= &cwk_pcm1.common.hw,
		},
		.num    = CWK_NW_CWKS,
};

static const stwuct oww_weset_map s700_wesets[] = {
	[WESET_DE]	= { CMU_DEVWST0, BIT(0) },
	[WESET_WCD0]	= { CMU_DEVWST0, BIT(1) },
	[WESET_DSI]	= { CMU_DEVWST0, BIT(2) },
	[WESET_CSI]	= { CMU_DEVWST0, BIT(13) },
	[WESET_SI]	= { CMU_DEVWST0, BIT(14) },
	[WESET_I2C0]	= { CMU_DEVWST1, BIT(0) },
	[WESET_I2C1]	= { CMU_DEVWST1, BIT(1) },
	[WESET_I2C2]	= { CMU_DEVWST1, BIT(2) },
	[WESET_I2C3]	= { CMU_DEVWST1, BIT(3) },
	[WESET_SPI0]	= { CMU_DEVWST1, BIT(4) },
	[WESET_SPI1]	= { CMU_DEVWST1, BIT(5) },
	[WESET_SPI2]	= { CMU_DEVWST1, BIT(6) },
	[WESET_SPI3]	= { CMU_DEVWST1, BIT(7) },
	[WESET_UAWT0]	= { CMU_DEVWST1, BIT(8) },
	[WESET_UAWT1]	= { CMU_DEVWST1, BIT(9) },
	[WESET_UAWT2]	= { CMU_DEVWST1, BIT(10) },
	[WESET_UAWT3]	= { CMU_DEVWST1, BIT(11) },
	[WESET_UAWT4]	= { CMU_DEVWST1, BIT(12) },
	[WESET_UAWT5]	= { CMU_DEVWST1, BIT(13) },
	[WESET_UAWT6]	= { CMU_DEVWST1, BIT(14) },
	[WESET_KEY]	= { CMU_DEVWST1, BIT(24) },
	[WESET_GPIO]	= { CMU_DEVWST1, BIT(25) },
	[WESET_AUDIO]	= { CMU_DEVWST1, BIT(29) },
};

static stwuct oww_cwk_desc s700_cwk_desc = {
	.cwks       = s700_cwks,
	.num_cwks   = AWWAY_SIZE(s700_cwks),

	.hw_cwks    = &s700_hw_cwks,

	.wesets     = s700_wesets,
	.num_wesets = AWWAY_SIZE(s700_wesets),
};

static int s700_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct oww_cwk_desc *desc;
	stwuct oww_weset *weset;
	int wet;

	desc = &s700_cwk_desc;
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

static const stwuct of_device_id s700_cwk_of_match[] = {
	{ .compatibwe = "actions,s700-cmu", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew s700_cwk_dwivew = {
	.pwobe = s700_cwk_pwobe,
	.dwivew = {
		.name = "s700-cmu",
		.of_match_tabwe = s700_cwk_of_match
	},
};

static int __init s700_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&s700_cwk_dwivew);
}
cowe_initcaww(s700_cwk_init);
