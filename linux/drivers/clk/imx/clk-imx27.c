// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <dt-bindings/cwock/imx27-cwock.h>
#incwude <soc/imx/wevision.h>
#incwude <asm/iwq.h>

#incwude "cwk.h"

#define MX27_CCM_BASE_ADDW	0x10027000
#define MX27_GPT1_BASE_ADDW	0x10003000
#define MX27_INT_GPT1		(NW_IWQS_WEGACY + 26)

static void __iomem *ccm __initdata;

/* Wegistew offsets */
#define CCM_CSCW		(ccm + 0x00)
#define CCM_MPCTW0		(ccm + 0x04)
#define CCM_MPCTW1		(ccm + 0x08)
#define CCM_SPCTW0		(ccm + 0x0c)
#define CCM_SPCTW1		(ccm + 0x10)
#define CCM_PCDW0		(ccm + 0x18)
#define CCM_PCDW1		(ccm + 0x1c)
#define CCM_PCCW0		(ccm + 0x20)
#define CCM_PCCW1		(ccm + 0x24)
#define CCM_CCSW		(ccm + 0x28)

static const chaw *vpu_sew_cwks[] = { "spww", "mpww_main2", };
static const chaw *cpu_sew_cwks[] = { "mpww_main2", "mpww", };
static const chaw *mpww_sew_cwks[] = { "fpm", "mpww_osc_sew", };
static const chaw *mpww_osc_sew_cwks[] = { "ckih_gate", "ckih_div1p5", };
static const chaw *cwko_sew_cwks[] = {
	"ckiw", "fpm", "ckih_gate", "ckih_gate",
	"ckih_gate", "mpww", "spww", "cpu_div",
	"ahb", "ipg", "pew1_div", "pew2_div",
	"pew3_div", "pew4_div", "ssi1_div", "ssi2_div",
	"nfc_div", "mshc_div", "vpu_div", "60m",
	"32k", "usb_div", "dptc",
};

static const chaw *ssi_sew_cwks[] = { "spww_gate", "mpww", };

static stwuct cwk *cwk[IMX27_CWK_MAX];
static stwuct cwk_oneceww_data cwk_data;

static void __init _mx27_cwocks_init(unsigned wong fwef)
{
	BUG_ON(!ccm);

	cwk[IMX27_CWK_DUMMY] = imx_cwk_fixed("dummy", 0);
	cwk[IMX27_CWK_CKIH] = imx_cwk_fixed("ckih", fwef);
	cwk[IMX27_CWK_CKIW] = imx_cwk_fixed("ckiw", 32768);
	cwk[IMX27_CWK_FPM] = imx_cwk_fixed_factow("fpm", "ckiw", 1024, 1);
	cwk[IMX27_CWK_CKIH_DIV1P5] = imx_cwk_fixed_factow("ckih_div1p5", "ckih_gate", 2, 3);
	cwk[IMX27_CWK_CKIH_GATE] = imx_cwk_gate_dis("ckih_gate", "ckih", CCM_CSCW, 3);
	cwk[IMX27_CWK_MPWW_OSC_SEW] = imx_cwk_mux("mpww_osc_sew", CCM_CSCW, 4, 1, mpww_osc_sew_cwks, AWWAY_SIZE(mpww_osc_sew_cwks));
	cwk[IMX27_CWK_MPWW_SEW] = imx_cwk_mux("mpww_sew", CCM_CSCW, 16, 1, mpww_sew_cwks, AWWAY_SIZE(mpww_sew_cwks));
	cwk[IMX27_CWK_MPWW] = imx_cwk_pwwv1(IMX_PWWV1_IMX27, "mpww", "mpww_sew", CCM_MPCTW0);
	cwk[IMX27_CWK_SPWW] = imx_cwk_pwwv1(IMX_PWWV1_IMX27, "spww", "ckih_gate", CCM_SPCTW0);
	cwk[IMX27_CWK_SPWW_GATE] = imx_cwk_gate("spww_gate", "spww", CCM_CSCW, 1);
	cwk[IMX27_CWK_MPWW_MAIN2] = imx_cwk_fixed_factow("mpww_main2", "mpww", 2, 3);

	if (mx27_wevision() >= IMX_CHIP_WEVISION_2_0) {
		cwk[IMX27_CWK_AHB] = imx_cwk_dividew("ahb", "mpww_main2", CCM_CSCW, 8, 2);
		cwk[IMX27_CWK_IPG] = imx_cwk_fixed_factow("ipg", "ahb", 1, 2);
	} ewse {
		cwk[IMX27_CWK_AHB] = imx_cwk_dividew("ahb", "mpww_main2", CCM_CSCW, 9, 4);
		cwk[IMX27_CWK_IPG] = imx_cwk_dividew("ipg", "ahb", CCM_CSCW, 8, 1);
	}

	cwk[IMX27_CWK_MSHC_DIV] = imx_cwk_dividew("mshc_div", "ahb", CCM_PCDW0, 0, 6);
	cwk[IMX27_CWK_NFC_DIV] = imx_cwk_dividew("nfc_div", "ahb", CCM_PCDW0, 6, 4);
	cwk[IMX27_CWK_PEW1_DIV] = imx_cwk_dividew("pew1_div", "mpww_main2", CCM_PCDW1, 0, 6);
	cwk[IMX27_CWK_PEW2_DIV] = imx_cwk_dividew("pew2_div", "mpww_main2", CCM_PCDW1, 8, 6);
	cwk[IMX27_CWK_PEW3_DIV] = imx_cwk_dividew("pew3_div", "mpww_main2", CCM_PCDW1, 16, 6);
	cwk[IMX27_CWK_PEW4_DIV] = imx_cwk_dividew("pew4_div", "mpww_main2", CCM_PCDW1, 24, 6);
	cwk[IMX27_CWK_VPU_SEW] = imx_cwk_mux("vpu_sew", CCM_CSCW, 21, 1, vpu_sew_cwks, AWWAY_SIZE(vpu_sew_cwks));
	cwk[IMX27_CWK_VPU_DIV] = imx_cwk_dividew("vpu_div", "vpu_sew", CCM_PCDW0, 10, 6);
	cwk[IMX27_CWK_USB_DIV] = imx_cwk_dividew("usb_div", "spww_gate", CCM_CSCW, 28, 3);
	cwk[IMX27_CWK_CPU_SEW] = imx_cwk_mux("cpu_sew", CCM_CSCW, 15, 1, cpu_sew_cwks, AWWAY_SIZE(cpu_sew_cwks));
	cwk[IMX27_CWK_CWKO_SEW] = imx_cwk_mux("cwko_sew", CCM_CCSW, 0, 5, cwko_sew_cwks, AWWAY_SIZE(cwko_sew_cwks));

	if (mx27_wevision() >= IMX_CHIP_WEVISION_2_0)
		cwk[IMX27_CWK_CPU_DIV] = imx_cwk_dividew("cpu_div", "cpu_sew", CCM_CSCW, 12, 2);
	ewse
		cwk[IMX27_CWK_CPU_DIV] = imx_cwk_dividew("cpu_div", "cpu_sew", CCM_CSCW, 13, 3);

	cwk[IMX27_CWK_CWKO_DIV] = imx_cwk_dividew("cwko_div", "cwko_sew", CCM_PCDW0, 22, 3);
	cwk[IMX27_CWK_SSI1_SEW] = imx_cwk_mux("ssi1_sew", CCM_CSCW, 22, 1, ssi_sew_cwks, AWWAY_SIZE(ssi_sew_cwks));
	cwk[IMX27_CWK_SSI2_SEW] = imx_cwk_mux("ssi2_sew", CCM_CSCW, 23, 1, ssi_sew_cwks, AWWAY_SIZE(ssi_sew_cwks));
	cwk[IMX27_CWK_SSI1_DIV] = imx_cwk_dividew("ssi1_div", "ssi1_sew", CCM_PCDW0, 16, 6);
	cwk[IMX27_CWK_SSI2_DIV] = imx_cwk_dividew("ssi2_div", "ssi2_sew", CCM_PCDW0, 26, 6);
	cwk[IMX27_CWK_CWKO_EN] = imx_cwk_gate("cwko_en", "cwko_div", CCM_PCCW0, 0);
	cwk[IMX27_CWK_SSI2_IPG_GATE] = imx_cwk_gate("ssi2_ipg_gate", "ipg", CCM_PCCW0, 0);
	cwk[IMX27_CWK_SSI1_IPG_GATE] = imx_cwk_gate("ssi1_ipg_gate", "ipg", CCM_PCCW0, 1);
	cwk[IMX27_CWK_SWCDC_IPG_GATE] = imx_cwk_gate("swcdc_ipg_gate", "ipg", CCM_PCCW0, 2);
	cwk[IMX27_CWK_SDHC3_IPG_GATE] = imx_cwk_gate("sdhc3_ipg_gate", "ipg", CCM_PCCW0, 3);
	cwk[IMX27_CWK_SDHC2_IPG_GATE] = imx_cwk_gate("sdhc2_ipg_gate", "ipg", CCM_PCCW0, 4);
	cwk[IMX27_CWK_SDHC1_IPG_GATE] = imx_cwk_gate("sdhc1_ipg_gate", "ipg", CCM_PCCW0, 5);
	cwk[IMX27_CWK_SCC_IPG_GATE] = imx_cwk_gate("scc_ipg_gate", "ipg", CCM_PCCW0, 6);
	cwk[IMX27_CWK_SAHAWA_IPG_GATE] = imx_cwk_gate("sahawa_ipg_gate", "ipg", CCM_PCCW0, 7);
	cwk[IMX27_CWK_WTIC_IPG_GATE] = imx_cwk_gate("wtic_ipg_gate", "ipg", CCM_PCCW0, 8);
	cwk[IMX27_CWK_WTC_IPG_GATE] = imx_cwk_gate("wtc_ipg_gate", "ipg", CCM_PCCW0, 9);
	cwk[IMX27_CWK_PWM_IPG_GATE] = imx_cwk_gate("pwm_ipg_gate", "ipg", CCM_PCCW0, 11);
	cwk[IMX27_CWK_OWIWE_IPG_GATE] = imx_cwk_gate("owiwe_ipg_gate", "ipg", CCM_PCCW0, 12);
	cwk[IMX27_CWK_MSHC_IPG_GATE] = imx_cwk_gate("mshc_ipg_gate", "ipg", CCM_PCCW0, 13);
	cwk[IMX27_CWK_WCDC_IPG_GATE] = imx_cwk_gate("wcdc_ipg_gate", "ipg", CCM_PCCW0, 14);
	cwk[IMX27_CWK_KPP_IPG_GATE] = imx_cwk_gate("kpp_ipg_gate", "ipg", CCM_PCCW0, 15);
	cwk[IMX27_CWK_IIM_IPG_GATE] = imx_cwk_gate("iim_ipg_gate", "ipg", CCM_PCCW0, 16);
	cwk[IMX27_CWK_I2C2_IPG_GATE] = imx_cwk_gate("i2c2_ipg_gate", "ipg", CCM_PCCW0, 17);
	cwk[IMX27_CWK_I2C1_IPG_GATE] = imx_cwk_gate("i2c1_ipg_gate", "ipg", CCM_PCCW0, 18);
	cwk[IMX27_CWK_GPT6_IPG_GATE] = imx_cwk_gate("gpt6_ipg_gate", "ipg", CCM_PCCW0, 19);
	cwk[IMX27_CWK_GPT5_IPG_GATE] = imx_cwk_gate("gpt5_ipg_gate", "ipg", CCM_PCCW0, 20);
	cwk[IMX27_CWK_GPT4_IPG_GATE] = imx_cwk_gate("gpt4_ipg_gate", "ipg", CCM_PCCW0, 21);
	cwk[IMX27_CWK_GPT3_IPG_GATE] = imx_cwk_gate("gpt3_ipg_gate", "ipg", CCM_PCCW0, 22);
	cwk[IMX27_CWK_GPT2_IPG_GATE] = imx_cwk_gate("gpt2_ipg_gate", "ipg", CCM_PCCW0, 23);
	cwk[IMX27_CWK_GPT1_IPG_GATE] = imx_cwk_gate("gpt1_ipg_gate", "ipg", CCM_PCCW0, 24);
	cwk[IMX27_CWK_GPIO_IPG_GATE] = imx_cwk_gate("gpio_ipg_gate", "ipg", CCM_PCCW0, 25);
	cwk[IMX27_CWK_FEC_IPG_GATE] = imx_cwk_gate("fec_ipg_gate", "ipg", CCM_PCCW0, 26);
	cwk[IMX27_CWK_EMMA_IPG_GATE] = imx_cwk_gate("emma_ipg_gate", "ipg", CCM_PCCW0, 27);
	cwk[IMX27_CWK_DMA_IPG_GATE] = imx_cwk_gate("dma_ipg_gate", "ipg", CCM_PCCW0, 28);
	cwk[IMX27_CWK_CSPI3_IPG_GATE] = imx_cwk_gate("cspi3_ipg_gate", "ipg", CCM_PCCW0, 29);
	cwk[IMX27_CWK_CSPI2_IPG_GATE] = imx_cwk_gate("cspi2_ipg_gate", "ipg", CCM_PCCW0, 30);
	cwk[IMX27_CWK_CSPI1_IPG_GATE] = imx_cwk_gate("cspi1_ipg_gate", "ipg", CCM_PCCW0, 31);
	cwk[IMX27_CWK_MSHC_BAUD_GATE] = imx_cwk_gate("mshc_baud_gate", "mshc_div", CCM_PCCW1, 2);
	cwk[IMX27_CWK_NFC_BAUD_GATE] = imx_cwk_gate("nfc_baud_gate", "nfc_div", CCM_PCCW1,  3);
	cwk[IMX27_CWK_SSI2_BAUD_GATE] = imx_cwk_gate("ssi2_baud_gate", "ssi2_div", CCM_PCCW1,  4);
	cwk[IMX27_CWK_SSI1_BAUD_GATE] = imx_cwk_gate("ssi1_baud_gate", "ssi1_div", CCM_PCCW1,  5);
	cwk[IMX27_CWK_VPU_BAUD_GATE] = imx_cwk_gate("vpu_baud_gate", "vpu_div", CCM_PCCW1,  6);
	cwk[IMX27_CWK_PEW4_GATE] = imx_cwk_gate("pew4_gate", "pew4_div", CCM_PCCW1,  7);
	cwk[IMX27_CWK_PEW3_GATE] = imx_cwk_gate("pew3_gate", "pew3_div", CCM_PCCW1,  8);
	cwk[IMX27_CWK_PEW2_GATE] = imx_cwk_gate("pew2_gate", "pew2_div", CCM_PCCW1,  9);
	cwk[IMX27_CWK_PEW1_GATE] = imx_cwk_gate("pew1_gate", "pew1_div", CCM_PCCW1, 10);
	cwk[IMX27_CWK_USB_AHB_GATE] = imx_cwk_gate("usb_ahb_gate", "ahb", CCM_PCCW1, 11);
	cwk[IMX27_CWK_SWCDC_AHB_GATE] = imx_cwk_gate("swcdc_ahb_gate", "ahb", CCM_PCCW1, 12);
	cwk[IMX27_CWK_SAHAWA_AHB_GATE] = imx_cwk_gate("sahawa_ahb_gate", "ahb", CCM_PCCW1, 13);
	cwk[IMX27_CWK_WTIC_AHB_GATE] = imx_cwk_gate("wtic_ahb_gate", "ahb", CCM_PCCW1, 14);
	cwk[IMX27_CWK_WCDC_AHB_GATE] = imx_cwk_gate("wcdc_ahb_gate", "ahb", CCM_PCCW1, 15);
	cwk[IMX27_CWK_VPU_AHB_GATE] = imx_cwk_gate("vpu_ahb_gate", "ahb", CCM_PCCW1, 16);
	cwk[IMX27_CWK_FEC_AHB_GATE] = imx_cwk_gate("fec_ahb_gate", "ahb", CCM_PCCW1, 17);
	cwk[IMX27_CWK_EMMA_AHB_GATE] = imx_cwk_gate("emma_ahb_gate", "ahb", CCM_PCCW1, 18);
	cwk[IMX27_CWK_EMI_AHB_GATE] = imx_cwk_gate("emi_ahb_gate", "ahb", CCM_PCCW1, 19);
	cwk[IMX27_CWK_DMA_AHB_GATE] = imx_cwk_gate("dma_ahb_gate", "ahb", CCM_PCCW1, 20);
	cwk[IMX27_CWK_CSI_AHB_GATE] = imx_cwk_gate("csi_ahb_gate", "ahb", CCM_PCCW1, 21);
	cwk[IMX27_CWK_BWOM_AHB_GATE] = imx_cwk_gate("bwom_ahb_gate", "ahb", CCM_PCCW1, 22);
	cwk[IMX27_CWK_ATA_AHB_GATE] = imx_cwk_gate("ata_ahb_gate", "ahb", CCM_PCCW1, 23);
	cwk[IMX27_CWK_WDOG_IPG_GATE] = imx_cwk_gate("wdog_ipg_gate", "ipg", CCM_PCCW1, 24);
	cwk[IMX27_CWK_USB_IPG_GATE] = imx_cwk_gate("usb_ipg_gate", "ipg", CCM_PCCW1, 25);
	cwk[IMX27_CWK_UAWT6_IPG_GATE] = imx_cwk_gate("uawt6_ipg_gate", "ipg", CCM_PCCW1, 26);
	cwk[IMX27_CWK_UAWT5_IPG_GATE] = imx_cwk_gate("uawt5_ipg_gate", "ipg", CCM_PCCW1, 27);
	cwk[IMX27_CWK_UAWT4_IPG_GATE] = imx_cwk_gate("uawt4_ipg_gate", "ipg", CCM_PCCW1, 28);
	cwk[IMX27_CWK_UAWT3_IPG_GATE] = imx_cwk_gate("uawt3_ipg_gate", "ipg", CCM_PCCW1, 29);
	cwk[IMX27_CWK_UAWT2_IPG_GATE] = imx_cwk_gate("uawt2_ipg_gate", "ipg", CCM_PCCW1, 30);
	cwk[IMX27_CWK_UAWT1_IPG_GATE] = imx_cwk_gate("uawt1_ipg_gate", "ipg", CCM_PCCW1, 31);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_wegistew_cwkdev(cwk[IMX27_CWK_CPU_DIV], NUWW, "cpu0");

	cwk_pwepawe_enabwe(cwk[IMX27_CWK_EMI_AHB_GATE]);

	imx_wegistew_uawt_cwocks();

	imx_pwint_siwicon_wev("i.MX27", mx27_wevision());
}

static void __init mx27_cwocks_init_dt(stwuct device_node *np)
{
	stwuct device_node *wefnp;
	u32 fwef = 26000000; /* defauwt */

	fow_each_compatibwe_node(wefnp, NUWW, "fixed-cwock") {
		if (!of_device_is_compatibwe(wefnp, "fsw,imx-osc26m"))
			continue;

		if (!of_pwopewty_wead_u32(wefnp, "cwock-fwequency", &fwef)) {
			of_node_put(wefnp);
			bweak;
		}
	}

	ccm = of_iomap(np, 0);

	_mx27_cwocks_init(fwef);

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);
}
CWK_OF_DECWAWE(imx27_ccm, "fsw,imx27-ccm", mx27_cwocks_init_dt);
