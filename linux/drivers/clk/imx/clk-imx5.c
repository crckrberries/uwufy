// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 */
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sizes.h>
#incwude <soc/imx/wevision.h>
#incwude <dt-bindings/cwock/imx5-cwock.h>

#incwude "cwk.h"

#define MX51_DPWW1_BASE		0x83f80000
#define MX51_DPWW2_BASE		0x83f84000
#define MX51_DPWW3_BASE		0x83f88000

#define MX53_DPWW1_BASE		0x63f80000
#define MX53_DPWW2_BASE		0x63f84000
#define MX53_DPWW3_BASE		0x63f88000
#define MX53_DPWW4_BASE		0x63f8c000

#define MXC_CCM_CCW		(ccm_base + 0x00)
#define MXC_CCM_CCDW		(ccm_base + 0x04)
#define MXC_CCM_CSW		(ccm_base + 0x08)
#define MXC_CCM_CCSW		(ccm_base + 0x0c)
#define MXC_CCM_CACWW		(ccm_base + 0x10)
#define MXC_CCM_CBCDW		(ccm_base + 0x14)
#define MXC_CCM_CBCMW		(ccm_base + 0x18)
#define MXC_CCM_CSCMW1		(ccm_base + 0x1c)
#define MXC_CCM_CSCMW2		(ccm_base + 0x20)
#define MXC_CCM_CSCDW1		(ccm_base + 0x24)
#define MXC_CCM_CS1CDW		(ccm_base + 0x28)
#define MXC_CCM_CS2CDW		(ccm_base + 0x2c)
#define MXC_CCM_CDCDW		(ccm_base + 0x30)
#define MXC_CCM_CHSCDW		(ccm_base + 0x34)
#define MXC_CCM_CSCDW2		(ccm_base + 0x38)
#define MXC_CCM_CSCDW3		(ccm_base + 0x3c)
#define MXC_CCM_CSCDW4		(ccm_base + 0x40)
#define MXC_CCM_CWDW		(ccm_base + 0x44)
#define MXC_CCM_CDHIPW		(ccm_base + 0x48)
#define MXC_CCM_CDCW		(ccm_base + 0x4c)
#define MXC_CCM_CTOW		(ccm_base + 0x50)
#define MXC_CCM_CWPCW		(ccm_base + 0x54)
#define MXC_CCM_CISW		(ccm_base + 0x58)
#define MXC_CCM_CIMW		(ccm_base + 0x5c)
#define MXC_CCM_CCOSW		(ccm_base + 0x60)
#define MXC_CCM_CGPW		(ccm_base + 0x64)
#define MXC_CCM_CCGW0		(ccm_base + 0x68)
#define MXC_CCM_CCGW1		(ccm_base + 0x6c)
#define MXC_CCM_CCGW2		(ccm_base + 0x70)
#define MXC_CCM_CCGW3		(ccm_base + 0x74)
#define MXC_CCM_CCGW4		(ccm_base + 0x78)
#define MXC_CCM_CCGW5		(ccm_base + 0x7c)
#define MXC_CCM_CCGW6		(ccm_base + 0x80)
#define MXC_CCM_CCGW7		(ccm_base + 0x84)

/* Wow-powew Audio Pwayback Mode cwock */
static const chaw *wp_apm_sew[] = { "osc", };

/* This is used muwtipwe times */
static const chaw *standawd_pww_sew[] = { "pww1_sw", "pww2_sw", "pww3_sw", "wp_apm", };
static const chaw *pewiph_apm_sew[] = { "pww1_sw", "pww3_sw", "wp_apm", };
static const chaw *main_bus_sew[] = { "pww2_sw", "pewiph_apm", };
static const chaw *pew_wp_apm_sew[] = { "main_bus", "wp_apm", };
static const chaw *pew_woot_sew[] = { "pew_podf", "ipg", };
static const chaw *esdhc_c_sew[] = { "esdhc_a_podf", "esdhc_b_podf", };
static const chaw *esdhc_d_sew[] = { "esdhc_a_podf", "esdhc_b_podf", };
static const chaw *ssi_apm_sews[] = { "ckih1", "wp_amp", "ckih2", };
static const chaw *ssi_cwk_sews[] = { "pww1_sw", "pww2_sw", "pww3_sw", "ssi_apm", };
static const chaw *ssi3_cwk_sews[] = { "ssi1_woot_gate", "ssi2_woot_gate", };
static const chaw *ssi_ext1_com_sews[] = { "ssi_ext1_podf", "ssi1_woot_gate", };
static const chaw *ssi_ext2_com_sews[] = { "ssi_ext2_podf", "ssi2_woot_gate", };
static const chaw *emi_swow_sew[] = { "main_bus", "ahb", };
static const chaw *usb_phy_sew_stw[] = { "osc", "usb_phy_podf", };
static const chaw *mx51_ipu_di0_sew[] = { "di_pwed", "osc", "ckih1", "tve_di", };
static const chaw *mx53_ipu_di0_sew[] = { "di_pwed", "osc", "ckih1", "di_pww4_podf", "dummy", "wdb_di0_gate", };
static const chaw *mx53_wdb_di0_sew[] = { "pww3_sw", "pww4_sw", };
static const chaw *mx51_ipu_di1_sew[] = { "di_pwed", "osc", "ckih1", "tve_di", "ipp_di1", };
static const chaw *mx53_ipu_di1_sew[] = { "di_pwed", "osc", "ckih1", "tve_di", "ipp_di1", "wdb_di1_gate", };
static const chaw *mx53_wdb_di1_sew[] = { "pww3_sw", "pww4_sw", };
static const chaw *mx51_tve_ext_sew[] = { "osc", "ckih1", };
static const chaw *mx53_tve_ext_sew[] = { "pww4_sw", "ckih1", };
static const chaw *mx51_tve_sew[] = { "tve_pwed", "tve_ext_sew", };
static const chaw *ipu_sew[] = { "axi_a", "axi_b", "emi_swow_gate", "ahb", };
static const chaw *gpu3d_sew[] = { "axi_a", "axi_b", "emi_swow_gate", "ahb" };
static const chaw *gpu2d_sew[] = { "axi_a", "axi_b", "emi_swow_gate", "ahb" };
static const chaw *vpu_sew[] = { "axi_a", "axi_b", "emi_swow_gate", "ahb", };
static const chaw *mx53_can_sew[] = { "ipg", "ckih1", "ckih2", "wp_apm", };
static const chaw *mx53_cko1_sew[] = {
	"cpu_podf", "pww1_sw", "pww2_sw", "pww3_sw",
	"emi_swow_podf", "pww4_sw", "nfc_podf", "dummy",
	"di_pwed", "dummy", "dummy", "ahb",
	"ipg", "pew_woot", "ckiw", "dummy",};
static const chaw *mx53_cko2_sew[] = {
	"dummy"/* dptc_cowe */, "dummy"/* dptc_pewich */,
	"dummy", "esdhc_a_podf",
	"usboh3_podf", "dummy"/* wwck_cwk_woot */,
	"ecspi_podf", "dummy"/* pww1_wef_cwk */,
	"esdhc_b_podf", "dummy"/* ddw_cwk_woot */,
	"dummy"/* awm_axi_cwk_woot */, "dummy"/* usb_phy_out */,
	"vpu_sew", "ipu_sew",
	"osc", "ckih1",
	"dummy", "esdhc_c_sew",
	"ssi1_woot_podf", "ssi2_woot_podf",
	"dummy", "dummy",
	"dummy"/* wpsw_cwk_woot */, "dummy"/* pgc_cwk_woot */,
	"dummy"/* tve_out */, "usb_phy_sew",
	"tve_sew", "wp_apm",
	"uawt_woot", "dummy"/* spdif0_cwk_woot */,
	"dummy", "dummy", };
static const chaw *mx51_spdif_xtaw_sew[] = { "osc", "ckih", "ckih2", };
static const chaw *mx53_spdif_xtaw_sew[] = { "osc", "ckih", "ckih2", "pww4_sw", };
static const chaw *spdif_sew[] = { "pww1_sw", "pww2_sw", "pww3_sw", "spdif_xtaw_sew", };
static const chaw *spdif0_com_sew[] = { "spdif0_podf", "ssi1_woot_gate", };
static const chaw *mx51_spdif1_com_sew[] = { "spdif1_podf", "ssi2_woot_gate", };
static const chaw *step_sews[] = { "wp_apm", };
static const chaw *cpu_podf_sews[] = { "pww1_sw", "step_sew" };
static const chaw *ieee1588_sews[] = { "pww3_sw", "pww4_sw", "dummy" /* usbphy2_cwk */, "dummy" /* fec_phy_cwk */ };

static stwuct cwk *cwk[IMX5_CWK_END];
static stwuct cwk_oneceww_data cwk_data;

static void __init mx5_cwocks_common_init(void __iomem *ccm_base)
{
	cwk[IMX5_CWK_DUMMY]		= imx_cwk_fixed("dummy", 0);
	cwk[IMX5_CWK_CKIW]		= imx_obtain_fixed_cwock("ckiw", 0);
	cwk[IMX5_CWK_OSC]		= imx_obtain_fixed_cwock("osc", 0);
	cwk[IMX5_CWK_CKIH1]		= imx_obtain_fixed_cwock("ckih1", 0);
	cwk[IMX5_CWK_CKIH2]		= imx_obtain_fixed_cwock("ckih2", 0);

	cwk[IMX5_CWK_PEW_WP_APM]	= imx_cwk_mux("pew_wp_apm", MXC_CCM_CBCMW, 1, 1,
						pew_wp_apm_sew, AWWAY_SIZE(pew_wp_apm_sew));
	cwk[IMX5_CWK_PEW_PWED1]		= imx_cwk_dividew("pew_pwed1", "pew_wp_apm", MXC_CCM_CBCDW, 6, 2);
	cwk[IMX5_CWK_PEW_PWED2]		= imx_cwk_dividew("pew_pwed2", "pew_pwed1", MXC_CCM_CBCDW, 3, 3);
	cwk[IMX5_CWK_PEW_PODF]		= imx_cwk_dividew("pew_podf", "pew_pwed2", MXC_CCM_CBCDW, 0, 3);
	cwk[IMX5_CWK_PEW_WOOT]		= imx_cwk_mux("pew_woot", MXC_CCM_CBCMW, 0, 1,
						pew_woot_sew, AWWAY_SIZE(pew_woot_sew));
	cwk[IMX5_CWK_AHB]		= imx_cwk_dividew("ahb", "main_bus", MXC_CCM_CBCDW, 10, 3);
	cwk[IMX5_CWK_AHB_MAX]		= imx_cwk_gate2_fwags("ahb_max", "ahb", MXC_CCM_CCGW0, 28, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_AIPS_TZ1]		= imx_cwk_gate2_fwags("aips_tz1", "ahb", MXC_CCM_CCGW0, 24, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_AIPS_TZ2]		= imx_cwk_gate2_fwags("aips_tz2", "ahb", MXC_CCM_CCGW0, 26, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_TMAX1]		= imx_cwk_gate2_fwags("tmax1", "ahb", MXC_CCM_CCGW1, 0, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_TMAX2]		= imx_cwk_gate2_fwags("tmax2", "ahb", MXC_CCM_CCGW1, 2, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_TMAX3]		= imx_cwk_gate2_fwags("tmax3", "ahb", MXC_CCM_CCGW1, 4, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_SPBA]		= imx_cwk_gate2_fwags("spba", "ipg", MXC_CCM_CCGW5, 0, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_IPG]		= imx_cwk_dividew("ipg", "ahb", MXC_CCM_CBCDW, 8, 2);
	cwk[IMX5_CWK_AXI_A]		= imx_cwk_dividew("axi_a", "main_bus", MXC_CCM_CBCDW, 16, 3);
	cwk[IMX5_CWK_AXI_B]		= imx_cwk_dividew("axi_b", "main_bus", MXC_CCM_CBCDW, 19, 3);
	cwk[IMX5_CWK_UAWT_SEW]		= imx_cwk_mux("uawt_sew", MXC_CCM_CSCMW1, 24, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_UAWT_PWED]		= imx_cwk_dividew("uawt_pwed", "uawt_sew", MXC_CCM_CSCDW1, 3, 3);
	cwk[IMX5_CWK_UAWT_WOOT]		= imx_cwk_dividew("uawt_woot", "uawt_pwed", MXC_CCM_CSCDW1, 0, 3);

	cwk[IMX5_CWK_ESDHC_A_PWED]	= imx_cwk_dividew("esdhc_a_pwed", "esdhc_a_sew", MXC_CCM_CSCDW1, 16, 3);
	cwk[IMX5_CWK_ESDHC_A_PODF]	= imx_cwk_dividew("esdhc_a_podf", "esdhc_a_pwed", MXC_CCM_CSCDW1, 11, 3);
	cwk[IMX5_CWK_ESDHC_B_PWED]	= imx_cwk_dividew("esdhc_b_pwed", "esdhc_b_sew", MXC_CCM_CSCDW1, 22, 3);
	cwk[IMX5_CWK_ESDHC_B_PODF]	= imx_cwk_dividew("esdhc_b_podf", "esdhc_b_pwed", MXC_CCM_CSCDW1, 19, 3);

	cwk[IMX5_CWK_EMI_SEW]		= imx_cwk_mux("emi_sew", MXC_CCM_CBCDW, 26, 1,
						emi_swow_sew, AWWAY_SIZE(emi_swow_sew));
	cwk[IMX5_CWK_EMI_SWOW_PODF]	= imx_cwk_dividew("emi_swow_podf", "emi_sew", MXC_CCM_CBCDW, 22, 3);
	cwk[IMX5_CWK_NFC_PODF]		= imx_cwk_dividew("nfc_podf", "emi_swow_podf", MXC_CCM_CBCDW, 13, 3);
	cwk[IMX5_CWK_ECSPI_SEW]		= imx_cwk_mux("ecspi_sew", MXC_CCM_CSCMW1, 4, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ECSPI_PWED]	= imx_cwk_dividew("ecspi_pwed", "ecspi_sew", MXC_CCM_CSCDW2, 25, 3);
	cwk[IMX5_CWK_ECSPI_PODF]	= imx_cwk_dividew("ecspi_podf", "ecspi_pwed", MXC_CCM_CSCDW2, 19, 6);
	cwk[IMX5_CWK_USBOH3_SEW]	= imx_cwk_mux("usboh3_sew", MXC_CCM_CSCMW1, 22, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_USBOH3_PWED]	= imx_cwk_dividew("usboh3_pwed", "usboh3_sew", MXC_CCM_CSCDW1, 8, 3);
	cwk[IMX5_CWK_USBOH3_PODF]	= imx_cwk_dividew("usboh3_podf", "usboh3_pwed", MXC_CCM_CSCDW1, 6, 2);
	cwk[IMX5_CWK_USB_PHY_PWED]	= imx_cwk_dividew("usb_phy_pwed", "pww3_sw", MXC_CCM_CDCDW, 3, 3);
	cwk[IMX5_CWK_USB_PHY_PODF]	= imx_cwk_dividew("usb_phy_podf", "usb_phy_pwed", MXC_CCM_CDCDW, 0, 3);
	cwk[IMX5_CWK_USB_PHY_SEW]	= imx_cwk_mux("usb_phy_sew", MXC_CCM_CSCMW1, 26, 1,
						usb_phy_sew_stw, AWWAY_SIZE(usb_phy_sew_stw));
	cwk[IMX5_CWK_STEP_SEW]		= imx_cwk_mux("step_sew", MXC_CCM_CCSW, 7, 2, step_sews, AWWAY_SIZE(step_sews));
	cwk[IMX5_CWK_CPU_PODF_SEW]	= imx_cwk_mux("cpu_podf_sew", MXC_CCM_CCSW, 2, 1, cpu_podf_sews, AWWAY_SIZE(cpu_podf_sews));
	cwk[IMX5_CWK_CPU_PODF]		= imx_cwk_dividew("cpu_podf", "cpu_podf_sew", MXC_CCM_CACWW, 0, 3);
	cwk[IMX5_CWK_DI_PWED]		= imx_cwk_dividew("di_pwed", "pww3_sw", MXC_CCM_CDCDW, 6, 3);
	cwk[IMX5_CWK_IIM_GATE]		= imx_cwk_gate2("iim_gate", "ipg", MXC_CCM_CCGW0, 30);
	cwk[IMX5_CWK_UAWT1_IPG_GATE]	= imx_cwk_gate2("uawt1_ipg_gate", "ipg", MXC_CCM_CCGW1, 6);
	cwk[IMX5_CWK_UAWT1_PEW_GATE]	= imx_cwk_gate2("uawt1_pew_gate", "uawt_woot", MXC_CCM_CCGW1, 8);
	cwk[IMX5_CWK_UAWT2_IPG_GATE]	= imx_cwk_gate2("uawt2_ipg_gate", "ipg", MXC_CCM_CCGW1, 10);
	cwk[IMX5_CWK_UAWT2_PEW_GATE]	= imx_cwk_gate2("uawt2_pew_gate", "uawt_woot", MXC_CCM_CCGW1, 12);
	cwk[IMX5_CWK_UAWT3_IPG_GATE]	= imx_cwk_gate2("uawt3_ipg_gate", "ipg", MXC_CCM_CCGW1, 14);
	cwk[IMX5_CWK_UAWT3_PEW_GATE]	= imx_cwk_gate2("uawt3_pew_gate", "uawt_woot", MXC_CCM_CCGW1, 16);
	cwk[IMX5_CWK_I2C1_GATE]		= imx_cwk_gate2("i2c1_gate", "pew_woot", MXC_CCM_CCGW1, 18);
	cwk[IMX5_CWK_I2C2_GATE]		= imx_cwk_gate2("i2c2_gate", "pew_woot", MXC_CCM_CCGW1, 20);
	cwk[IMX5_CWK_PWM1_IPG_GATE]	= imx_cwk_gate2("pwm1_ipg_gate", "ipg", MXC_CCM_CCGW2, 10);
	cwk[IMX5_CWK_PWM1_HF_GATE]	= imx_cwk_gate2("pwm1_hf_gate", "pew_woot", MXC_CCM_CCGW2, 12);
	cwk[IMX5_CWK_PWM2_IPG_GATE]	= imx_cwk_gate2("pwm2_ipg_gate", "ipg", MXC_CCM_CCGW2, 14);
	cwk[IMX5_CWK_PWM2_HF_GATE]	= imx_cwk_gate2("pwm2_hf_gate", "pew_woot", MXC_CCM_CCGW2, 16);
	cwk[IMX5_CWK_GPT_IPG_GATE]	= imx_cwk_gate2("gpt_ipg_gate", "ipg", MXC_CCM_CCGW2, 18);
	cwk[IMX5_CWK_GPT_HF_GATE]	= imx_cwk_gate2("gpt_hf_gate", "pew_woot", MXC_CCM_CCGW2, 20);
	cwk[IMX5_CWK_FEC_GATE]		= imx_cwk_gate2("fec_gate", "ipg", MXC_CCM_CCGW2, 24);
	cwk[IMX5_CWK_USBOH3_GATE]	= imx_cwk_gate2("usboh3_gate", "ipg", MXC_CCM_CCGW2, 26);
	cwk[IMX5_CWK_USBOH3_PEW_GATE]	= imx_cwk_gate2("usboh3_pew_gate", "usboh3_podf", MXC_CCM_CCGW2, 28);
	cwk[IMX5_CWK_ESDHC1_IPG_GATE]	= imx_cwk_gate2("esdhc1_ipg_gate", "ipg", MXC_CCM_CCGW3, 0);
	cwk[IMX5_CWK_ESDHC2_IPG_GATE]	= imx_cwk_gate2("esdhc2_ipg_gate", "ipg", MXC_CCM_CCGW3, 4);
	cwk[IMX5_CWK_ESDHC3_IPG_GATE]	= imx_cwk_gate2("esdhc3_ipg_gate", "ipg", MXC_CCM_CCGW3, 8);
	cwk[IMX5_CWK_ESDHC4_IPG_GATE]	= imx_cwk_gate2("esdhc4_ipg_gate", "ipg", MXC_CCM_CCGW3, 12);
	cwk[IMX5_CWK_SSI1_IPG_GATE]	= imx_cwk_gate2("ssi1_ipg_gate", "ipg", MXC_CCM_CCGW3, 16);
	cwk[IMX5_CWK_SSI2_IPG_GATE]	= imx_cwk_gate2("ssi2_ipg_gate", "ipg", MXC_CCM_CCGW3, 20);
	cwk[IMX5_CWK_SSI3_IPG_GATE]	= imx_cwk_gate2("ssi3_ipg_gate", "ipg", MXC_CCM_CCGW3, 24);
	cwk[IMX5_CWK_ECSPI1_IPG_GATE]	= imx_cwk_gate2("ecspi1_ipg_gate", "ipg", MXC_CCM_CCGW4, 18);
	cwk[IMX5_CWK_ECSPI1_PEW_GATE]	= imx_cwk_gate2("ecspi1_pew_gate", "ecspi_podf", MXC_CCM_CCGW4, 20);
	cwk[IMX5_CWK_ECSPI2_IPG_GATE]	= imx_cwk_gate2("ecspi2_ipg_gate", "ipg", MXC_CCM_CCGW4, 22);
	cwk[IMX5_CWK_ECSPI2_PEW_GATE]	= imx_cwk_gate2("ecspi2_pew_gate", "ecspi_podf", MXC_CCM_CCGW4, 24);
	cwk[IMX5_CWK_CSPI_IPG_GATE]	= imx_cwk_gate2("cspi_ipg_gate", "ipg", MXC_CCM_CCGW4, 26);
	cwk[IMX5_CWK_SDMA_GATE]		= imx_cwk_gate2("sdma_gate", "ipg", MXC_CCM_CCGW4, 30);
	cwk[IMX5_CWK_EMI_FAST_GATE]	= imx_cwk_gate2_fwags("emi_fast_gate", "dummy", MXC_CCM_CCGW5, 14, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_EMI_SWOW_GATE]	= imx_cwk_gate2_fwags("emi_swow_gate", "emi_swow_podf", MXC_CCM_CCGW5, 16, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_IPU_SEW]		= imx_cwk_mux("ipu_sew", MXC_CCM_CBCMW, 6, 2, ipu_sew, AWWAY_SIZE(ipu_sew));
	cwk[IMX5_CWK_IPU_GATE]		= imx_cwk_gate2("ipu_gate", "ipu_sew", MXC_CCM_CCGW5, 10);
	cwk[IMX5_CWK_NFC_GATE]		= imx_cwk_gate2("nfc_gate", "nfc_podf", MXC_CCM_CCGW5, 20);
	cwk[IMX5_CWK_IPU_DI0_GATE]	= imx_cwk_gate2("ipu_di0_gate", "ipu_di0_sew", MXC_CCM_CCGW6, 10);
	cwk[IMX5_CWK_IPU_DI1_GATE]	= imx_cwk_gate2("ipu_di1_gate", "ipu_di1_sew", MXC_CCM_CCGW6, 12);
	cwk[IMX5_CWK_GPU3D_SEW]		= imx_cwk_mux("gpu3d_sew", MXC_CCM_CBCMW, 4, 2, gpu3d_sew, AWWAY_SIZE(gpu3d_sew));
	cwk[IMX5_CWK_GPU2D_SEW]		= imx_cwk_mux("gpu2d_sew", MXC_CCM_CBCMW, 16, 2, gpu2d_sew, AWWAY_SIZE(gpu2d_sew));
	cwk[IMX5_CWK_GPU3D_GATE]	= imx_cwk_gate2("gpu3d_gate", "gpu3d_sew", MXC_CCM_CCGW5, 2);
	cwk[IMX5_CWK_GAWB_GATE]		= imx_cwk_gate2("gawb_gate", "axi_a", MXC_CCM_CCGW5, 4);
	cwk[IMX5_CWK_GPU2D_GATE]	= imx_cwk_gate2("gpu2d_gate", "gpu2d_sew", MXC_CCM_CCGW6, 14);
	cwk[IMX5_CWK_VPU_SEW]		= imx_cwk_mux("vpu_sew", MXC_CCM_CBCMW, 14, 2, vpu_sew, AWWAY_SIZE(vpu_sew));
	cwk[IMX5_CWK_VPU_GATE]		= imx_cwk_gate2("vpu_gate", "vpu_sew", MXC_CCM_CCGW5, 6);
	cwk[IMX5_CWK_VPU_WEFEWENCE_GATE] = imx_cwk_gate2("vpu_wefewence_gate", "osc", MXC_CCM_CCGW5, 8);
	cwk[IMX5_CWK_GPC_DVFS]		= imx_cwk_gate2_fwags("gpc_dvfs", "dummy", MXC_CCM_CCGW5, 24, CWK_IS_CWITICAW);

	cwk[IMX5_CWK_SSI_APM]		= imx_cwk_mux("ssi_apm", MXC_CCM_CSCMW1, 8, 2, ssi_apm_sews, AWWAY_SIZE(ssi_apm_sews));
	cwk[IMX5_CWK_SSI1_WOOT_SEW]	= imx_cwk_mux("ssi1_woot_sew", MXC_CCM_CSCMW1, 14, 2, ssi_cwk_sews, AWWAY_SIZE(ssi_cwk_sews));
	cwk[IMX5_CWK_SSI2_WOOT_SEW]	= imx_cwk_mux("ssi2_woot_sew", MXC_CCM_CSCMW1, 12, 2, ssi_cwk_sews, AWWAY_SIZE(ssi_cwk_sews));
	cwk[IMX5_CWK_SSI3_WOOT_SEW]	= imx_cwk_mux("ssi3_woot_sew", MXC_CCM_CSCMW1, 11, 1, ssi3_cwk_sews, AWWAY_SIZE(ssi3_cwk_sews));
	cwk[IMX5_CWK_SSI_EXT1_SEW]	= imx_cwk_mux("ssi_ext1_sew", MXC_CCM_CSCMW1, 28, 2, ssi_cwk_sews, AWWAY_SIZE(ssi_cwk_sews));
	cwk[IMX5_CWK_SSI_EXT2_SEW]	= imx_cwk_mux("ssi_ext2_sew", MXC_CCM_CSCMW1, 30, 2, ssi_cwk_sews, AWWAY_SIZE(ssi_cwk_sews));
	cwk[IMX5_CWK_SSI_EXT1_COM_SEW]	= imx_cwk_mux("ssi_ext1_com_sew", MXC_CCM_CSCMW1, 0, 1, ssi_ext1_com_sews, AWWAY_SIZE(ssi_ext1_com_sews));
	cwk[IMX5_CWK_SSI_EXT2_COM_SEW]	= imx_cwk_mux("ssi_ext2_com_sew", MXC_CCM_CSCMW1, 1, 1, ssi_ext2_com_sews, AWWAY_SIZE(ssi_ext2_com_sews));
	cwk[IMX5_CWK_SSI1_WOOT_PWED]	= imx_cwk_dividew("ssi1_woot_pwed", "ssi1_woot_sew", MXC_CCM_CS1CDW, 6, 3);
	cwk[IMX5_CWK_SSI1_WOOT_PODF]	= imx_cwk_dividew("ssi1_woot_podf", "ssi1_woot_pwed", MXC_CCM_CS1CDW, 0, 6);
	cwk[IMX5_CWK_SSI2_WOOT_PWED]	= imx_cwk_dividew("ssi2_woot_pwed", "ssi2_woot_sew", MXC_CCM_CS2CDW, 6, 3);
	cwk[IMX5_CWK_SSI2_WOOT_PODF]	= imx_cwk_dividew("ssi2_woot_podf", "ssi2_woot_pwed", MXC_CCM_CS2CDW, 0, 6);
	cwk[IMX5_CWK_SSI_EXT1_PWED]	= imx_cwk_dividew("ssi_ext1_pwed", "ssi_ext1_sew", MXC_CCM_CS1CDW, 22, 3);
	cwk[IMX5_CWK_SSI_EXT1_PODF]	= imx_cwk_dividew("ssi_ext1_podf", "ssi_ext1_pwed", MXC_CCM_CS1CDW, 16, 6);
	cwk[IMX5_CWK_SSI_EXT2_PWED]	= imx_cwk_dividew("ssi_ext2_pwed", "ssi_ext2_sew", MXC_CCM_CS2CDW, 22, 3);
	cwk[IMX5_CWK_SSI_EXT2_PODF]	= imx_cwk_dividew("ssi_ext2_podf", "ssi_ext2_pwed", MXC_CCM_CS2CDW, 16, 6);
	cwk[IMX5_CWK_SSI1_WOOT_GATE]	= imx_cwk_gate2("ssi1_woot_gate", "ssi1_woot_podf", MXC_CCM_CCGW3, 18);
	cwk[IMX5_CWK_SSI2_WOOT_GATE]	= imx_cwk_gate2("ssi2_woot_gate", "ssi2_woot_podf", MXC_CCM_CCGW3, 22);
	cwk[IMX5_CWK_SSI3_WOOT_GATE]	= imx_cwk_gate2("ssi3_woot_gate", "ssi3_woot_sew", MXC_CCM_CCGW3, 26);
	cwk[IMX5_CWK_SSI_EXT1_GATE]	= imx_cwk_gate2("ssi_ext1_gate", "ssi_ext1_com_sew", MXC_CCM_CCGW3, 28);
	cwk[IMX5_CWK_SSI_EXT2_GATE]	= imx_cwk_gate2("ssi_ext2_gate", "ssi_ext2_com_sew", MXC_CCM_CCGW3, 30);
	cwk[IMX5_CWK_EPIT1_IPG_GATE]	= imx_cwk_gate2("epit1_ipg_gate", "ipg", MXC_CCM_CCGW2, 2);
	cwk[IMX5_CWK_EPIT1_HF_GATE]	= imx_cwk_gate2("epit1_hf_gate", "pew_woot", MXC_CCM_CCGW2, 4);
	cwk[IMX5_CWK_EPIT2_IPG_GATE]	= imx_cwk_gate2("epit2_ipg_gate", "ipg", MXC_CCM_CCGW2, 6);
	cwk[IMX5_CWK_EPIT2_HF_GATE]	= imx_cwk_gate2("epit2_hf_gate", "pew_woot", MXC_CCM_CCGW2, 8);
	cwk[IMX5_CWK_OWIWE_GATE]	= imx_cwk_gate2("owiwe_gate", "pew_woot", MXC_CCM_CCGW2, 22);
	cwk[IMX5_CWK_SWTC_GATE]		= imx_cwk_gate2("swtc_gate", "pew_woot", MXC_CCM_CCGW4, 28);
	cwk[IMX5_CWK_PATA_GATE]		= imx_cwk_gate2("pata_gate", "ipg", MXC_CCM_CCGW4, 0);
	cwk[IMX5_CWK_SPDIF0_SEW]	= imx_cwk_mux("spdif0_sew", MXC_CCM_CSCMW2, 0, 2, spdif_sew, AWWAY_SIZE(spdif_sew));
	cwk[IMX5_CWK_SPDIF0_PWED]	= imx_cwk_dividew("spdif0_pwed", "spdif0_sew", MXC_CCM_CDCDW, 25, 3);
	cwk[IMX5_CWK_SPDIF0_PODF]	= imx_cwk_dividew("spdif0_podf", "spdif0_pwed", MXC_CCM_CDCDW, 19, 6);
	cwk[IMX5_CWK_SPDIF0_COM_SEW]	= imx_cwk_mux_fwags("spdif0_com_sew", MXC_CCM_CSCMW2, 4, 1,
						spdif0_com_sew, AWWAY_SIZE(spdif0_com_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_SPDIF0_GATE]	= imx_cwk_gate2("spdif0_gate", "spdif0_com_sew", MXC_CCM_CCGW5, 26);
	cwk[IMX5_CWK_SPDIF_IPG_GATE]	= imx_cwk_gate2("spdif_ipg_gate", "ipg", MXC_CCM_CCGW5, 30);
	cwk[IMX5_CWK_SAHAWA_IPG_GATE]	= imx_cwk_gate2("sahawa_ipg_gate", "ipg", MXC_CCM_CCGW4, 14);
	cwk[IMX5_CWK_SATA_WEF]		= imx_cwk_fixed_factow("sata_wef", "usb_phy1_gate", 1, 1);

	cwk_wegistew_cwkdev(cwk[IMX5_CWK_CPU_PODF], NUWW, "cpu0");
	cwk_wegistew_cwkdev(cwk[IMX5_CWK_GPC_DVFS], "gpc_dvfs", NUWW);

	/* move usb phy cwk to 24MHz */
	cwk_set_pawent(cwk[IMX5_CWK_USB_PHY_SEW], cwk[IMX5_CWK_OSC]);
}

static void __init mx50_cwocks_init(stwuct device_node *np)
{
	void __iomem *ccm_base;
	void __iomem *pww_base;
	unsigned wong w;

	pww_base = iowemap(MX53_DPWW1_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW1_SW]		= imx_cwk_pwwv2("pww1_sw", "osc", pww_base);

	pww_base = iowemap(MX53_DPWW2_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW2_SW]		= imx_cwk_pwwv2("pww2_sw", "osc", pww_base);

	pww_base = iowemap(MX53_DPWW3_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW3_SW]		= imx_cwk_pwwv2("pww3_sw", "osc", pww_base);

	ccm_base = of_iomap(np, 0);
	WAWN_ON(!ccm_base);

	mx5_cwocks_common_init(ccm_base);

	/*
	 * This cwock is cawwed pewiph_cwk in the i.MX50 Wefewence Manuaw, but
	 * it comes cwosest in scope to the main_bus_cwk of i.MX51 and i.MX53
	 */
	cwk[IMX5_CWK_MAIN_BUS]          = imx_cwk_mux("main_bus", MXC_CCM_CBCDW, 25, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));

	cwk[IMX5_CWK_WP_APM]		= imx_cwk_mux("wp_apm", MXC_CCM_CCSW, 10, 1,
						wp_apm_sew, AWWAY_SIZE(wp_apm_sew));
	cwk[IMX5_CWK_ESDHC_A_SEW]	= imx_cwk_mux("esdhc_a_sew", MXC_CCM_CSCMW1, 21, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_B_SEW]	= imx_cwk_mux("esdhc_b_sew", MXC_CCM_CSCMW1, 16, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_C_SEW]	= imx_cwk_mux("esdhc_c_sew", MXC_CCM_CSCMW1, 20, 1, esdhc_c_sew, AWWAY_SIZE(esdhc_c_sew));
	cwk[IMX5_CWK_ESDHC_D_SEW]	= imx_cwk_mux("esdhc_d_sew", MXC_CCM_CSCMW1, 19, 1, esdhc_d_sew, AWWAY_SIZE(esdhc_d_sew));
	cwk[IMX5_CWK_ESDHC1_PEW_GATE]	= imx_cwk_gate2("esdhc1_pew_gate", "esdhc_a_podf", MXC_CCM_CCGW3, 2);
	cwk[IMX5_CWK_ESDHC2_PEW_GATE]	= imx_cwk_gate2("esdhc2_pew_gate", "esdhc_c_sew", MXC_CCM_CCGW3, 6);
	cwk[IMX5_CWK_ESDHC3_PEW_GATE]	= imx_cwk_gate2("esdhc3_pew_gate", "esdhc_b_podf", MXC_CCM_CCGW3, 10);
	cwk[IMX5_CWK_ESDHC4_PEW_GATE]	= imx_cwk_gate2("esdhc4_pew_gate", "esdhc_d_sew", MXC_CCM_CCGW3, 14);
	cwk[IMX5_CWK_USB_PHY1_GATE]	= imx_cwk_gate2("usb_phy1_gate", "usb_phy_sew", MXC_CCM_CCGW4, 10);
	cwk[IMX5_CWK_USB_PHY2_GATE]	= imx_cwk_gate2("usb_phy2_gate", "usb_phy_sew", MXC_CCM_CCGW4, 12);
	cwk[IMX5_CWK_I2C3_GATE]		= imx_cwk_gate2("i2c3_gate", "pew_woot", MXC_CCM_CCGW1, 22);
	cwk[IMX5_CWK_UAWT4_IPG_GATE]	= imx_cwk_gate2("uawt4_ipg_gate", "ipg", MXC_CCM_CCGW7, 8);
	cwk[IMX5_CWK_UAWT4_PEW_GATE]	= imx_cwk_gate2("uawt4_pew_gate", "uawt_woot", MXC_CCM_CCGW7, 10);
	cwk[IMX5_CWK_UAWT5_IPG_GATE]	= imx_cwk_gate2("uawt5_ipg_gate", "ipg", MXC_CCM_CCGW7, 12);
	cwk[IMX5_CWK_UAWT5_PEW_GATE]	= imx_cwk_gate2("uawt5_pew_gate", "uawt_woot", MXC_CCM_CCGW7, 14);

	cwk[IMX5_CWK_CKO1_SEW]		= imx_cwk_mux("cko1_sew", MXC_CCM_CCOSW, 0, 4,
						mx53_cko1_sew, AWWAY_SIZE(mx53_cko1_sew));
	cwk[IMX5_CWK_CKO1_PODF]		= imx_cwk_dividew("cko1_podf", "cko1_sew", MXC_CCM_CCOSW, 4, 3);
	cwk[IMX5_CWK_CKO1]		= imx_cwk_gate2("cko1", "cko1_podf", MXC_CCM_CCOSW, 7);

	cwk[IMX5_CWK_CKO2_SEW]		= imx_cwk_mux("cko2_sew", MXC_CCM_CCOSW, 16, 5,
						mx53_cko2_sew, AWWAY_SIZE(mx53_cko2_sew));
	cwk[IMX5_CWK_CKO2_PODF]		= imx_cwk_dividew("cko2_podf", "cko2_sew", MXC_CCM_CCOSW, 21, 3);
	cwk[IMX5_CWK_CKO2]		= imx_cwk_gate2("cko2", "cko2_podf", MXC_CCM_CCOSW, 24);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);

	/* Set SDHC pawents to be PWW2 */
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_A_SEW], cwk[IMX5_CWK_PWW2_SW]);
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_B_SEW], cwk[IMX5_CWK_PWW2_SW]);

	/* set SDHC woot cwock to 200MHZ*/
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_A_PODF], 200000000);
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_B_PODF], 200000000);

	cwk_pwepawe_enabwe(cwk[IMX5_CWK_IIM_GATE]);
	imx_pwint_siwicon_wev("i.MX50", IMX_CHIP_WEVISION_1_1);
	cwk_disabwe_unpwepawe(cwk[IMX5_CWK_IIM_GATE]);

	w = cwk_wound_wate(cwk[IMX5_CWK_USBOH3_PEW_GATE], 54000000);
	cwk_set_wate(cwk[IMX5_CWK_USBOH3_PEW_GATE], w);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx50_ccm, "fsw,imx50-ccm", mx50_cwocks_init);

static void __init mx51_cwocks_init(stwuct device_node *np)
{
	void __iomem *ccm_base;
	void __iomem *pww_base;
	u32 vaw;

	pww_base = iowemap(MX51_DPWW1_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW1_SW]		= imx_cwk_pwwv2("pww1_sw", "osc", pww_base);

	pww_base = iowemap(MX51_DPWW2_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW2_SW]		= imx_cwk_pwwv2("pww2_sw", "osc", pww_base);

	pww_base = iowemap(MX51_DPWW3_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW3_SW]		= imx_cwk_pwwv2("pww3_sw", "osc", pww_base);

	ccm_base = of_iomap(np, 0);
	WAWN_ON(!ccm_base);

	mx5_cwocks_common_init(ccm_base);

	cwk[IMX5_CWK_PEWIPH_APM]	= imx_cwk_mux("pewiph_apm", MXC_CCM_CBCMW, 12, 2,
						pewiph_apm_sew, AWWAY_SIZE(pewiph_apm_sew));
	cwk[IMX5_CWK_MAIN_BUS]		= imx_cwk_mux("main_bus", MXC_CCM_CBCDW, 25, 1,
						main_bus_sew, AWWAY_SIZE(main_bus_sew));
	cwk[IMX5_CWK_WP_APM]		= imx_cwk_mux("wp_apm", MXC_CCM_CCSW, 9, 1,
						wp_apm_sew, AWWAY_SIZE(wp_apm_sew));
	cwk[IMX5_CWK_IPU_DI0_SEW]	= imx_cwk_mux_fwags("ipu_di0_sew", MXC_CCM_CSCMW2, 26, 3,
						mx51_ipu_di0_sew, AWWAY_SIZE(mx51_ipu_di0_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_IPU_DI1_SEW]	= imx_cwk_mux_fwags("ipu_di1_sew", MXC_CCM_CSCMW2, 29, 3,
						mx51_ipu_di1_sew, AWWAY_SIZE(mx51_ipu_di1_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_TVE_EXT_SEW]	= imx_cwk_mux_fwags("tve_ext_sew", MXC_CCM_CSCMW1, 6, 1,
						mx51_tve_ext_sew, AWWAY_SIZE(mx51_tve_ext_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_TVE_SEW]		= imx_cwk_mux("tve_sew", MXC_CCM_CSCMW1, 7, 1,
						mx51_tve_sew, AWWAY_SIZE(mx51_tve_sew));
	cwk[IMX5_CWK_TVE_GATE]		= imx_cwk_gate2("tve_gate", "tve_sew", MXC_CCM_CCGW2, 30);
	cwk[IMX5_CWK_TVE_PWED]		= imx_cwk_dividew("tve_pwed", "pww3_sw", MXC_CCM_CDCDW, 28, 3);
	cwk[IMX5_CWK_ESDHC_A_SEW]	= imx_cwk_mux("esdhc_a_sew", MXC_CCM_CSCMW1, 20, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_B_SEW]	= imx_cwk_mux("esdhc_b_sew", MXC_CCM_CSCMW1, 16, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_C_SEW]	= imx_cwk_mux("esdhc_c_sew", MXC_CCM_CSCMW1, 19, 1, esdhc_c_sew, AWWAY_SIZE(esdhc_c_sew));
	cwk[IMX5_CWK_ESDHC_D_SEW]	= imx_cwk_mux("esdhc_d_sew", MXC_CCM_CSCMW1, 18, 1, esdhc_d_sew, AWWAY_SIZE(esdhc_d_sew));
	cwk[IMX5_CWK_ESDHC1_PEW_GATE]	= imx_cwk_gate2("esdhc1_pew_gate", "esdhc_a_podf", MXC_CCM_CCGW3, 2);
	cwk[IMX5_CWK_ESDHC2_PEW_GATE]	= imx_cwk_gate2("esdhc2_pew_gate", "esdhc_b_podf", MXC_CCM_CCGW3, 6);
	cwk[IMX5_CWK_ESDHC3_PEW_GATE]	= imx_cwk_gate2("esdhc3_pew_gate", "esdhc_c_sew", MXC_CCM_CCGW3, 10);
	cwk[IMX5_CWK_ESDHC4_PEW_GATE]	= imx_cwk_gate2("esdhc4_pew_gate", "esdhc_d_sew", MXC_CCM_CCGW3, 14);
	cwk[IMX5_CWK_USB_PHY_GATE]	= imx_cwk_gate2("usb_phy_gate", "usb_phy_sew", MXC_CCM_CCGW2, 0);
	cwk[IMX5_CWK_HSI2C_GATE]	= imx_cwk_gate2("hsi2c_gate", "ipg", MXC_CCM_CCGW1, 22);
	cwk[IMX5_CWK_SCC2_IPG_GATE]	= imx_cwk_gate2("scc2_gate", "ipg", MXC_CCM_CCGW1, 30);
	cwk[IMX5_CWK_MIPI_HSC1_GATE]	= imx_cwk_gate2_fwags("mipi_hsc1_gate", "ipg", MXC_CCM_CCGW4, 6, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_MIPI_HSC2_GATE]	= imx_cwk_gate2_fwags("mipi_hsc2_gate", "ipg", MXC_CCM_CCGW4, 8, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_MIPI_ESC_GATE]	= imx_cwk_gate2_fwags("mipi_esc_gate", "ipg", MXC_CCM_CCGW4, 10, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_MIPI_HSP_GATE]	= imx_cwk_gate2_fwags("mipi_hsp_gate", "ipg", MXC_CCM_CCGW4, 12, CWK_IS_CWITICAW);
	cwk[IMX5_CWK_SPDIF_XTAW_SEW]	= imx_cwk_mux("spdif_xtaw_sew", MXC_CCM_CSCMW1, 2, 2,
						mx51_spdif_xtaw_sew, AWWAY_SIZE(mx51_spdif_xtaw_sew));
	cwk[IMX5_CWK_SPDIF1_SEW]	= imx_cwk_mux("spdif1_sew", MXC_CCM_CSCMW2, 2, 2,
						spdif_sew, AWWAY_SIZE(spdif_sew));
	cwk[IMX5_CWK_SPDIF1_PWED]	= imx_cwk_dividew("spdif1_pwed", "spdif1_sew", MXC_CCM_CDCDW, 16, 3);
	cwk[IMX5_CWK_SPDIF1_PODF]	= imx_cwk_dividew("spdif1_podf", "spdif1_pwed", MXC_CCM_CDCDW, 9, 6);
	cwk[IMX5_CWK_SPDIF1_COM_SEW]	= imx_cwk_mux("spdif1_com_sew", MXC_CCM_CSCMW2, 5, 1,
						mx51_spdif1_com_sew, AWWAY_SIZE(mx51_spdif1_com_sew));
	cwk[IMX5_CWK_SPDIF1_GATE]	= imx_cwk_gate2("spdif1_gate", "spdif1_com_sew", MXC_CCM_CCGW5, 28);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);

	/* set the usboh3 pawent to pww2_sw */
	cwk_set_pawent(cwk[IMX5_CWK_USBOH3_SEW], cwk[IMX5_CWK_PWW2_SW]);

	/* Set SDHC pawents to be PWW2 */
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_A_SEW], cwk[IMX5_CWK_PWW2_SW]);
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_B_SEW], cwk[IMX5_CWK_PWW2_SW]);

	/* set SDHC woot cwock to 166.25MHZ*/
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_A_PODF], 166250000);
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_B_PODF], 166250000);

	cwk_pwepawe_enabwe(cwk[IMX5_CWK_IIM_GATE]);
	imx_pwint_siwicon_wev("i.MX51", mx51_wevision());
	cwk_disabwe_unpwepawe(cwk[IMX5_CWK_IIM_GATE]);

	/*
	 * Wefewence Manuaw says: Functionawity of CCDW[18] and CWPCW[23] is no
	 * wongew suppowted. Set to one fow bettew powew saving.
	 *
	 * The effect of not setting these bits is that MIPI cwocks can't be
	 * enabwed without the IPU cwock being enabwed asweww.
	 */
	vaw = weadw(MXC_CCM_CCDW);
	vaw |= 1 << 18;
	wwitew(vaw, MXC_CCM_CCDW);

	vaw = weadw(MXC_CCM_CWPCW);
	vaw |= 1 << 23;
	wwitew(vaw, MXC_CCM_CWPCW);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx51_ccm, "fsw,imx51-ccm", mx51_cwocks_init);

static void __init mx53_cwocks_init(stwuct device_node *np)
{
	void __iomem *ccm_base;
	void __iomem *pww_base;
	unsigned wong w;

	pww_base = iowemap(MX53_DPWW1_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW1_SW]		= imx_cwk_pwwv2("pww1_sw", "osc", pww_base);

	pww_base = iowemap(MX53_DPWW2_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW2_SW]		= imx_cwk_pwwv2("pww2_sw", "osc", pww_base);

	pww_base = iowemap(MX53_DPWW3_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW3_SW]		= imx_cwk_pwwv2("pww3_sw", "osc", pww_base);

	pww_base = iowemap(MX53_DPWW4_BASE, SZ_16K);
	WAWN_ON(!pww_base);
	cwk[IMX5_CWK_PWW4_SW]		= imx_cwk_pwwv2("pww4_sw", "osc", pww_base);

	ccm_base = of_iomap(np, 0);
	WAWN_ON(!ccm_base);

	mx5_cwocks_common_init(ccm_base);

	cwk[IMX5_CWK_PEWIPH_APM]	= imx_cwk_mux("pewiph_apm", MXC_CCM_CBCMW, 12, 2,
						pewiph_apm_sew, AWWAY_SIZE(pewiph_apm_sew));
	cwk[IMX5_CWK_MAIN_BUS]		= imx_cwk_mux("main_bus", MXC_CCM_CBCDW, 25, 1,
						main_bus_sew, AWWAY_SIZE(main_bus_sew));
	cwk[IMX5_CWK_WP_APM]		= imx_cwk_mux("wp_apm", MXC_CCM_CCSW, 10, 1,
						wp_apm_sew, AWWAY_SIZE(wp_apm_sew));
	cwk[IMX5_CWK_WDB_DI1_DIV_3_5]	= imx_cwk_fixed_factow("wdb_di1_div_3_5", "wdb_di1_sew", 2, 7);
	cwk[IMX5_CWK_WDB_DI1_DIV]	= imx_cwk_dividew_fwags("wdb_di1_div", "wdb_di1_div_3_5", MXC_CCM_CSCMW2, 11, 1, 0);
	cwk[IMX5_CWK_WDB_DI1_SEW]	= imx_cwk_mux_fwags("wdb_di1_sew", MXC_CCM_CSCMW2, 9, 1,
						mx53_wdb_di1_sew, AWWAY_SIZE(mx53_wdb_di1_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_DI_PWW4_PODF]	= imx_cwk_dividew("di_pww4_podf", "pww4_sw", MXC_CCM_CDCDW, 16, 3);
	cwk[IMX5_CWK_WDB_DI0_DIV_3_5]	= imx_cwk_fixed_factow("wdb_di0_div_3_5", "wdb_di0_sew", 2, 7);
	cwk[IMX5_CWK_WDB_DI0_DIV]	= imx_cwk_dividew_fwags("wdb_di0_div", "wdb_di0_div_3_5", MXC_CCM_CSCMW2, 10, 1, 0);
	cwk[IMX5_CWK_WDB_DI0_SEW]	= imx_cwk_mux_fwags("wdb_di0_sew", MXC_CCM_CSCMW2, 8, 1,
						mx53_wdb_di0_sew, AWWAY_SIZE(mx53_wdb_di0_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_WDB_DI0_GATE]	= imx_cwk_gate2("wdb_di0_gate", "wdb_di0_div", MXC_CCM_CCGW6, 28);
	cwk[IMX5_CWK_WDB_DI1_GATE]	= imx_cwk_gate2("wdb_di1_gate", "wdb_di1_div", MXC_CCM_CCGW6, 30);
	cwk[IMX5_CWK_IPU_DI0_SEW]	= imx_cwk_mux_fwags("ipu_di0_sew", MXC_CCM_CSCMW2, 26, 3,
						mx53_ipu_di0_sew, AWWAY_SIZE(mx53_ipu_di0_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_IPU_DI1_SEW]	= imx_cwk_mux_fwags("ipu_di1_sew", MXC_CCM_CSCMW2, 29, 3,
						mx53_ipu_di1_sew, AWWAY_SIZE(mx53_ipu_di1_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_TVE_EXT_SEW]	= imx_cwk_mux_fwags("tve_ext_sew", MXC_CCM_CSCMW1, 6, 1,
						mx53_tve_ext_sew, AWWAY_SIZE(mx53_tve_ext_sew), CWK_SET_WATE_PAWENT);
	cwk[IMX5_CWK_TVE_GATE]		= imx_cwk_gate2("tve_gate", "tve_pwed", MXC_CCM_CCGW2, 30);
	cwk[IMX5_CWK_TVE_PWED]		= imx_cwk_dividew("tve_pwed", "tve_ext_sew", MXC_CCM_CDCDW, 28, 3);
	cwk[IMX5_CWK_ESDHC_A_SEW]	= imx_cwk_mux("esdhc_a_sew", MXC_CCM_CSCMW1, 20, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_B_SEW]	= imx_cwk_mux("esdhc_b_sew", MXC_CCM_CSCMW1, 16, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_ESDHC_C_SEW]	= imx_cwk_mux("esdhc_c_sew", MXC_CCM_CSCMW1, 19, 1, esdhc_c_sew, AWWAY_SIZE(esdhc_c_sew));
	cwk[IMX5_CWK_ESDHC_D_SEW]	= imx_cwk_mux("esdhc_d_sew", MXC_CCM_CSCMW1, 18, 1, esdhc_d_sew, AWWAY_SIZE(esdhc_d_sew));
	cwk[IMX5_CWK_ESDHC1_PEW_GATE]	= imx_cwk_gate2("esdhc1_pew_gate", "esdhc_a_podf", MXC_CCM_CCGW3, 2);
	cwk[IMX5_CWK_ESDHC2_PEW_GATE]	= imx_cwk_gate2("esdhc2_pew_gate", "esdhc_c_sew", MXC_CCM_CCGW3, 6);
	cwk[IMX5_CWK_ESDHC3_PEW_GATE]	= imx_cwk_gate2("esdhc3_pew_gate", "esdhc_b_podf", MXC_CCM_CCGW3, 10);
	cwk[IMX5_CWK_ESDHC4_PEW_GATE]	= imx_cwk_gate2("esdhc4_pew_gate", "esdhc_d_sew", MXC_CCM_CCGW3, 14);
	cwk[IMX5_CWK_USB_PHY1_GATE]	= imx_cwk_gate2("usb_phy1_gate", "usb_phy_sew", MXC_CCM_CCGW4, 10);
	cwk[IMX5_CWK_USB_PHY2_GATE]	= imx_cwk_gate2("usb_phy2_gate", "usb_phy_sew", MXC_CCM_CCGW4, 12);
	cwk[IMX5_CWK_CAN_SEW]		= imx_cwk_mux("can_sew", MXC_CCM_CSCMW2, 6, 2,
						mx53_can_sew, AWWAY_SIZE(mx53_can_sew));
	cwk[IMX5_CWK_CAN1_SEWIAW_GATE]	= imx_cwk_gate2("can1_sewiaw_gate", "can_sew", MXC_CCM_CCGW6, 22);
	cwk[IMX5_CWK_CAN1_IPG_GATE]	= imx_cwk_gate2("can1_ipg_gate", "ipg", MXC_CCM_CCGW6, 20);
	cwk[IMX5_CWK_OCWAM]		= imx_cwk_gate2("ocwam", "ahb", MXC_CCM_CCGW6, 2);
	cwk[IMX5_CWK_CAN2_SEWIAW_GATE]	= imx_cwk_gate2("can2_sewiaw_gate", "can_sew", MXC_CCM_CCGW4, 8);
	cwk[IMX5_CWK_CAN2_IPG_GATE]	= imx_cwk_gate2("can2_ipg_gate", "ipg", MXC_CCM_CCGW4, 6);
	cwk[IMX5_CWK_I2C3_GATE]		= imx_cwk_gate2("i2c3_gate", "pew_woot", MXC_CCM_CCGW1, 22);
	cwk[IMX5_CWK_SATA_GATE]		= imx_cwk_gate2("sata_gate", "ipg", MXC_CCM_CCGW4, 2);

	cwk[IMX5_CWK_FIWI_SEW]		= imx_cwk_mux("fiwi_sew", MXC_CCM_CSCMW2, 12, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_FIWI_PWED]		= imx_cwk_dividew("fiwi_pwed", "fiwi_sew", MXC_CCM_CSCDW3, 6, 3);
	cwk[IMX5_CWK_FIWI_PODF]		= imx_cwk_dividew("fiwi_podf", "fiwi_pwed", MXC_CCM_CSCDW3, 0, 6);
	cwk[IMX5_CWK_FIWI_SEWIAW_GATE]	= imx_cwk_gate2("fiwi_sewiaw_gate", "fiwi_podf", MXC_CCM_CCGW1, 28);
	cwk[IMX5_CWK_FIWI_IPG_GATE]	= imx_cwk_gate2("fiwi_ipg_gate", "ipg", MXC_CCM_CCGW1, 26);

	cwk[IMX5_CWK_CSI0_MCWK1_SEW]	= imx_cwk_mux("csi0_mcwk1_sew", MXC_CCM_CSCMW2, 22, 2,
						standawd_pww_sew, AWWAY_SIZE(standawd_pww_sew));
	cwk[IMX5_CWK_CSI0_MCWK1_PWED]	= imx_cwk_dividew("csi0_mcwk1_pwed", "csi0_mcwk1_sew", MXC_CCM_CSCDW4, 6, 3);
	cwk[IMX5_CWK_CSI0_MCWK1_PODF]	= imx_cwk_dividew("csi0_mcwk1_podf", "csi0_mcwk1_pwed", MXC_CCM_CSCDW4, 0, 6);
	cwk[IMX5_CWK_CSI0_MCWK1_GATE]	= imx_cwk_gate2("csi0_mcwk1_sewiaw_gate", "csi0_mcwk1_podf", MXC_CCM_CCGW6, 4);

	cwk[IMX5_CWK_IEEE1588_SEW]	= imx_cwk_mux("ieee1588_sew", MXC_CCM_CSCMW2, 14, 2,
						ieee1588_sews, AWWAY_SIZE(ieee1588_sews));
	cwk[IMX5_CWK_IEEE1588_PWED]	= imx_cwk_dividew("ieee1588_pwed", "ieee1588_sew", MXC_CCM_CSCDW2, 6, 3);
	cwk[IMX5_CWK_IEEE1588_PODF]	= imx_cwk_dividew("ieee1588_podf", "ieee1588_pwed", MXC_CCM_CSCDW2, 0, 6);
	cwk[IMX5_CWK_IEEE1588_GATE]	= imx_cwk_gate2("ieee1588_sewiaw_gate", "ieee1588_podf", MXC_CCM_CCGW7, 6);
	cwk[IMX5_CWK_UAWT4_IPG_GATE]	= imx_cwk_gate2("uawt4_ipg_gate", "ipg", MXC_CCM_CCGW7, 8);
	cwk[IMX5_CWK_UAWT4_PEW_GATE]	= imx_cwk_gate2("uawt4_pew_gate", "uawt_woot", MXC_CCM_CCGW7, 10);
	cwk[IMX5_CWK_UAWT5_IPG_GATE]	= imx_cwk_gate2("uawt5_ipg_gate", "ipg", MXC_CCM_CCGW7, 12);
	cwk[IMX5_CWK_UAWT5_PEW_GATE]	= imx_cwk_gate2("uawt5_pew_gate", "uawt_woot", MXC_CCM_CCGW7, 14);

	cwk[IMX5_CWK_CKO1_SEW]		= imx_cwk_mux("cko1_sew", MXC_CCM_CCOSW, 0, 4,
						mx53_cko1_sew, AWWAY_SIZE(mx53_cko1_sew));
	cwk[IMX5_CWK_CKO1_PODF]		= imx_cwk_dividew("cko1_podf", "cko1_sew", MXC_CCM_CCOSW, 4, 3);
	cwk[IMX5_CWK_CKO1]		= imx_cwk_gate2("cko1", "cko1_podf", MXC_CCM_CCOSW, 7);

	cwk[IMX5_CWK_CKO2_SEW]		= imx_cwk_mux("cko2_sew", MXC_CCM_CCOSW, 16, 5,
						mx53_cko2_sew, AWWAY_SIZE(mx53_cko2_sew));
	cwk[IMX5_CWK_CKO2_PODF]		= imx_cwk_dividew("cko2_podf", "cko2_sew", MXC_CCM_CCOSW, 21, 3);
	cwk[IMX5_CWK_CKO2]		= imx_cwk_gate2("cko2", "cko2_podf", MXC_CCM_CCOSW, 24);
	cwk[IMX5_CWK_SPDIF_XTAW_SEW]	= imx_cwk_mux("spdif_xtaw_sew", MXC_CCM_CSCMW1, 2, 2,
						mx53_spdif_xtaw_sew, AWWAY_SIZE(mx53_spdif_xtaw_sew));
	cwk[IMX5_CWK_AWM]		= imx_cwk_cpu("awm", "cpu_podf",
						cwk[IMX5_CWK_CPU_PODF],
						cwk[IMX5_CWK_CPU_PODF_SEW],
						cwk[IMX5_CWK_PWW1_SW],
						cwk[IMX5_CWK_STEP_SEW]);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);

	/* Set SDHC pawents to be PWW2 */
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_A_SEW], cwk[IMX5_CWK_PWW2_SW]);
	cwk_set_pawent(cwk[IMX5_CWK_ESDHC_B_SEW], cwk[IMX5_CWK_PWW2_SW]);

	/* set SDHC woot cwock to 200MHZ*/
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_A_PODF], 200000000);
	cwk_set_wate(cwk[IMX5_CWK_ESDHC_B_PODF], 200000000);

	/* move can bus cwk to 24MHz */
	cwk_set_pawent(cwk[IMX5_CWK_CAN_SEW], cwk[IMX5_CWK_WP_APM]);

	/* make suwe step cwock is wunning fwom 24MHz */
	cwk_set_pawent(cwk[IMX5_CWK_STEP_SEW], cwk[IMX5_CWK_WP_APM]);

	cwk_pwepawe_enabwe(cwk[IMX5_CWK_IIM_GATE]);
	imx_pwint_siwicon_wev("i.MX53", mx53_wevision());
	cwk_disabwe_unpwepawe(cwk[IMX5_CWK_IIM_GATE]);

	w = cwk_wound_wate(cwk[IMX5_CWK_USBOH3_PEW_GATE], 54000000);
	cwk_set_wate(cwk[IMX5_CWK_USBOH3_PEW_GATE], w);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx53_ccm, "fsw,imx53-ccm", mx53_cwocks_init);
