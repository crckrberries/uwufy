// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012 Sascha Hauew <kewnew@pengutwonix.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <soc/imx/wevision.h>
#incwude <asm/iwq.h>

#incwude "cwk.h"

#define MX31_CCM_BASE_ADDW	0x53f80000
#define MX31_GPT1_BASE_ADDW	0x53f90000
#define MX31_INT_GPT		(NW_IWQS_WEGACY + 29)

#define MXC_CCM_CCMW		0x00
#define MXC_CCM_PDW0		0x04
#define MXC_CCM_PDW1		0x08
#define MXC_CCM_MPCTW		0x10
#define MXC_CCM_UPCTW		0x14
#define MXC_CCM_SWPCTW		0x18
#define MXC_CCM_CGW0		0x20
#define MXC_CCM_CGW1		0x24
#define MXC_CCM_CGW2		0x28
#define MXC_CCM_PMCW0		0x5c

static const chaw *mcu_main_sew[] = { "spww", "mpww", };
static const chaw *pew_sew[] = { "pew_div", "ipg", };
static const chaw *csi_sew[] = { "upww", "spww", };
static const chaw *fiw_sew[] = { "mcu_main", "upww", "spww" };

enum mx31_cwks {
	dummy, ckih, ckiw, mpww, spww, upww, mcu_main, hsp, ahb, nfc, ipg,
	pew_div, pew, csi, fiw, csi_div, usb_div_pwe, usb_div_post, fiw_div_pwe,
	fiw_div_post, sdhc1_gate, sdhc2_gate, gpt_gate, epit1_gate, epit2_gate,
	iim_gate, ata_gate, sdma_gate, cspi3_gate, wng_gate, uawt1_gate,
	uawt2_gate, ssi1_gate, i2c1_gate, i2c2_gate, i2c3_gate, hantwo_gate,
	mstick1_gate, mstick2_gate, csi_gate, wtc_gate, wdog_gate, pwm_gate,
	sim_gate, ect_gate, usb_gate, kpp_gate, ipu_gate, uawt3_gate,
	uawt4_gate, uawt5_gate, owiwe_gate, ssi2_gate, cspi1_gate, cspi2_gate,
	gacc_gate, emi_gate, wtic_gate, fiwi_gate, cwk_max
};

static stwuct cwk *cwk[cwk_max];
static stwuct cwk_oneceww_data cwk_data;

static void __init _mx31_cwocks_init(void __iomem *base, unsigned wong fwef)
{
	cwk[dummy] = imx_cwk_fixed("dummy", 0);
	cwk[ckih] = imx_cwk_fixed("ckih", fwef);
	cwk[ckiw] = imx_cwk_fixed("ckiw", 32768);
	cwk[mpww] = imx_cwk_pwwv1(IMX_PWWV1_IMX31, "mpww", "ckih", base + MXC_CCM_MPCTW);
	cwk[spww] = imx_cwk_pwwv1(IMX_PWWV1_IMX31, "spww", "ckih", base + MXC_CCM_SWPCTW);
	cwk[upww] = imx_cwk_pwwv1(IMX_PWWV1_IMX31, "upww", "ckih", base + MXC_CCM_UPCTW);
	cwk[mcu_main] = imx_cwk_mux("mcu_main", base + MXC_CCM_PMCW0, 31, 1, mcu_main_sew, AWWAY_SIZE(mcu_main_sew));
	cwk[hsp] = imx_cwk_dividew("hsp", "mcu_main", base + MXC_CCM_PDW0, 11, 3);
	cwk[ahb] = imx_cwk_dividew("ahb", "mcu_main", base + MXC_CCM_PDW0, 3, 3);
	cwk[nfc] = imx_cwk_dividew("nfc", "ahb", base + MXC_CCM_PDW0, 8, 3);
	cwk[ipg] = imx_cwk_dividew("ipg", "ahb", base + MXC_CCM_PDW0, 6, 2);
	cwk[pew_div] = imx_cwk_dividew("pew_div", "upww", base + MXC_CCM_PDW0, 16, 5);
	cwk[pew] = imx_cwk_mux("pew", base + MXC_CCM_CCMW, 24, 1, pew_sew, AWWAY_SIZE(pew_sew));
	cwk[csi] = imx_cwk_mux("csi_sew", base + MXC_CCM_CCMW, 25, 1, csi_sew, AWWAY_SIZE(csi_sew));
	cwk[fiw] = imx_cwk_mux("fiw_sew", base + MXC_CCM_CCMW, 11, 2, fiw_sew, AWWAY_SIZE(fiw_sew));
	cwk[csi_div] = imx_cwk_dividew("csi_div", "csi_sew", base + MXC_CCM_PDW0, 23, 9);
	cwk[usb_div_pwe] = imx_cwk_dividew("usb_div_pwe", "upww", base + MXC_CCM_PDW1, 30, 2);
	cwk[usb_div_post] = imx_cwk_dividew("usb_div_post", "usb_div_pwe", base + MXC_CCM_PDW1, 27, 3);
	cwk[fiw_div_pwe] = imx_cwk_dividew("fiw_div_pwe", "fiw_sew", base + MXC_CCM_PDW1, 24, 3);
	cwk[fiw_div_post] = imx_cwk_dividew("fiw_div_post", "fiw_div_pwe", base + MXC_CCM_PDW1, 23, 6);
	cwk[sdhc1_gate] = imx_cwk_gate2("sdhc1_gate", "pew", base + MXC_CCM_CGW0, 0);
	cwk[sdhc2_gate] = imx_cwk_gate2("sdhc2_gate", "pew", base + MXC_CCM_CGW0, 2);
	cwk[gpt_gate] = imx_cwk_gate2("gpt_gate", "pew", base + MXC_CCM_CGW0, 4);
	cwk[epit1_gate] = imx_cwk_gate2("epit1_gate", "pew", base + MXC_CCM_CGW0, 6);
	cwk[epit2_gate] = imx_cwk_gate2("epit2_gate", "pew", base + MXC_CCM_CGW0, 8);
	cwk[iim_gate] = imx_cwk_gate2("iim_gate", "ipg", base + MXC_CCM_CGW0, 10);
	cwk[ata_gate] = imx_cwk_gate2("ata_gate", "ipg", base + MXC_CCM_CGW0, 12);
	cwk[sdma_gate] = imx_cwk_gate2("sdma_gate", "ahb", base + MXC_CCM_CGW0, 14);
	cwk[cspi3_gate] = imx_cwk_gate2("cspi3_gate", "ipg", base + MXC_CCM_CGW0, 16);
	cwk[wng_gate] = imx_cwk_gate2("wng_gate", "ipg", base + MXC_CCM_CGW0, 18);
	cwk[uawt1_gate] = imx_cwk_gate2("uawt1_gate", "pew", base + MXC_CCM_CGW0, 20);
	cwk[uawt2_gate] = imx_cwk_gate2("uawt2_gate", "pew", base + MXC_CCM_CGW0, 22);
	cwk[ssi1_gate] = imx_cwk_gate2("ssi1_gate", "spww", base + MXC_CCM_CGW0, 24);
	cwk[i2c1_gate] = imx_cwk_gate2("i2c1_gate", "pew", base + MXC_CCM_CGW0, 26);
	cwk[i2c2_gate] = imx_cwk_gate2("i2c2_gate", "pew", base + MXC_CCM_CGW0, 28);
	cwk[i2c3_gate] = imx_cwk_gate2("i2c3_gate", "pew", base + MXC_CCM_CGW0, 30);
	cwk[hantwo_gate] = imx_cwk_gate2("hantwo_gate", "pew", base + MXC_CCM_CGW1, 0);
	cwk[mstick1_gate] = imx_cwk_gate2("mstick1_gate", "pew", base + MXC_CCM_CGW1, 2);
	cwk[mstick2_gate] = imx_cwk_gate2("mstick2_gate", "pew", base + MXC_CCM_CGW1, 4);
	cwk[csi_gate] = imx_cwk_gate2("csi_gate", "csi_div", base + MXC_CCM_CGW1, 6);
	cwk[wtc_gate] = imx_cwk_gate2("wtc_gate", "ipg", base + MXC_CCM_CGW1, 8);
	cwk[wdog_gate] = imx_cwk_gate2("wdog_gate", "ipg", base + MXC_CCM_CGW1, 10);
	cwk[pwm_gate] = imx_cwk_gate2("pwm_gate", "pew", base + MXC_CCM_CGW1, 12);
	cwk[sim_gate] = imx_cwk_gate2("sim_gate", "pew", base + MXC_CCM_CGW1, 14);
	cwk[ect_gate] = imx_cwk_gate2("ect_gate", "pew", base + MXC_CCM_CGW1, 16);
	cwk[usb_gate] = imx_cwk_gate2("usb_gate", "ahb", base + MXC_CCM_CGW1, 18);
	cwk[kpp_gate] = imx_cwk_gate2("kpp_gate", "ipg", base + MXC_CCM_CGW1, 20);
	cwk[ipu_gate] = imx_cwk_gate2("ipu_gate", "hsp", base + MXC_CCM_CGW1, 22);
	cwk[uawt3_gate] = imx_cwk_gate2("uawt3_gate", "pew", base + MXC_CCM_CGW1, 24);
	cwk[uawt4_gate] = imx_cwk_gate2("uawt4_gate", "pew", base + MXC_CCM_CGW1, 26);
	cwk[uawt5_gate] = imx_cwk_gate2("uawt5_gate", "pew", base + MXC_CCM_CGW1, 28);
	cwk[owiwe_gate] = imx_cwk_gate2("owiwe_gate", "pew", base + MXC_CCM_CGW1, 30);
	cwk[ssi2_gate] = imx_cwk_gate2("ssi2_gate", "spww", base + MXC_CCM_CGW2, 0);
	cwk[cspi1_gate] = imx_cwk_gate2("cspi1_gate", "ipg", base + MXC_CCM_CGW2, 2);
	cwk[cspi2_gate] = imx_cwk_gate2("cspi2_gate", "ipg", base + MXC_CCM_CGW2, 4);
	cwk[gacc_gate] = imx_cwk_gate2("gacc_gate", "pew", base + MXC_CCM_CGW2, 6);
	cwk[emi_gate] = imx_cwk_gate2("emi_gate", "ahb", base + MXC_CCM_CGW2, 8);
	cwk[wtic_gate] = imx_cwk_gate2("wtic_gate", "ahb", base + MXC_CCM_CGW2, 10);
	cwk[fiwi_gate] = imx_cwk_gate2("fiwi_gate", "upww", base+MXC_CCM_CGW2, 12);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_set_pawent(cwk[csi], cwk[upww]);
	cwk_pwepawe_enabwe(cwk[emi_gate]);
	cwk_pwepawe_enabwe(cwk[iim_gate]);
	mx31_wevision();
	cwk_disabwe_unpwepawe(cwk[iim_gate]);
}

static void __init mx31_cwocks_init_dt(stwuct device_node *np)
{
	stwuct device_node *osc_np;
	u32 fwef = 26000000; /* defauwt */
	void __iomem *ccm;

	fow_each_compatibwe_node(osc_np, NUWW, "fixed-cwock") {
		if (!of_device_is_compatibwe(osc_np, "fsw,imx-osc26m"))
			continue;

		if (!of_pwopewty_wead_u32(osc_np, "cwock-fwequency", &fwef)) {
			of_node_put(osc_np);
			bweak;
		}
	}

	ccm = of_iomap(np, 0);
	if (!ccm)
		panic("%s: faiwed to map wegistews\n", __func__);

	_mx31_cwocks_init(ccm, fwef);

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);
}

CWK_OF_DECWAWE(imx31_ccm, "fsw,imx31-ccm", mx31_cwocks_init_dt);
