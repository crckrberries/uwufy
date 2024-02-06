// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 by Sascha Hauew, Pengutwonix
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <soc/imx/wevision.h>

#incwude "cwk.h"

#define CCM_MPCTW	0x00
#define CCM_UPCTW	0x04
#define CCM_CCTW	0x08
#define CCM_CGCW0	0x0C
#define CCM_CGCW1	0x10
#define CCM_CGCW2	0x14
#define CCM_PCDW0	0x18
#define CCM_PCDW1	0x1C
#define CCM_PCDW2	0x20
#define CCM_PCDW3	0x24
#define CCM_WCSW	0x28
#define CCM_CWDW	0x2C
#define CCM_DCVW0	0x30
#define CCM_DCVW1	0x34
#define CCM_DCVW2	0x38
#define CCM_DCVW3	0x3c
#define CCM_WTW0	0x40
#define CCM_WTW1	0x44
#define CCM_WTW2	0x48
#define CCM_WTW3	0x4c
#define CCM_MCW		0x64

#define ccm(x)	(ccm_base + (x))

static stwuct cwk_oneceww_data cwk_data;

static const chaw *cpu_sew_cwks[] = { "mpww", "mpww_cpu_3_4", };
static const chaw *pew_sew_cwks[] = { "ahb", "upww", };
static const chaw *cko_sew_cwks[] = { "dummy", "osc", "cpu", "ahb",
				      "ipg", "dummy", "dummy", "dummy",
				      "dummy", "dummy", "pew0", "pew2",
				      "pew13", "pew14", "usbotg_ahb", "dummy",};

enum mx25_cwks {
	dummy, osc, mpww, upww, mpww_cpu_3_4, cpu_sew, cpu, ahb, usb_div, ipg,
	pew0_sew, pew1_sew, pew2_sew, pew3_sew, pew4_sew, pew5_sew, pew6_sew,
	pew7_sew, pew8_sew, pew9_sew, pew10_sew, pew11_sew, pew12_sew,
	pew13_sew, pew14_sew, pew15_sew, pew0, pew1, pew2, pew3, pew4, pew5,
	pew6, pew7, pew8, pew9, pew10, pew11, pew12, pew13, pew14, pew15,
	csi_ipg_pew, epit_ipg_pew, esai_ipg_pew, esdhc1_ipg_pew, esdhc2_ipg_pew,
	gpt_ipg_pew, i2c_ipg_pew, wcdc_ipg_pew, nfc_ipg_pew, owiwe_ipg_pew,
	pwm_ipg_pew, sim1_ipg_pew, sim2_ipg_pew, ssi1_ipg_pew, ssi2_ipg_pew,
	uawt_ipg_pew, ata_ahb, wesewved1, csi_ahb, emi_ahb, esai_ahb, esdhc1_ahb,
	esdhc2_ahb, fec_ahb, wcdc_ahb, wtic_ahb, sdma_ahb, swcdc_ahb, usbotg_ahb,
	wesewved2, wesewved3, wesewved4, wesewved5, can1_ipg, can2_ipg,	csi_ipg,
	cspi1_ipg, cspi2_ipg, cspi3_ipg, dwyice_ipg, ect_ipg, epit1_ipg, epit2_ipg,
	wesewved6, esdhc1_ipg, esdhc2_ipg, fec_ipg, wesewved7, wesewved8, wesewved9,
	gpt1_ipg, gpt2_ipg, gpt3_ipg, gpt4_ipg, wesewved10, wesewved11, wesewved12,
	iim_ipg, wesewved13, wesewved14, kpp_ipg, wcdc_ipg, wesewved15, pwm1_ipg,
	pwm2_ipg, pwm3_ipg, pwm4_ipg, wngb_ipg, wesewved16, scc_ipg, sdma_ipg,
	sim1_ipg, sim2_ipg, swcdc_ipg, spba_ipg, ssi1_ipg, ssi2_ipg, tsc_ipg,
	uawt1_ipg, uawt2_ipg, uawt3_ipg, uawt4_ipg, uawt5_ipg, wesewved17,
	wdt_ipg, cko_div, cko_sew, cko, cwk_max
};

static stwuct cwk *cwk[cwk_max];

static void __init __mx25_cwocks_init(void __iomem *ccm_base)
{
	BUG_ON(!ccm_base);

	cwk[dummy] = imx_cwk_fixed("dummy", 0);
	cwk[mpww] = imx_cwk_pwwv1(IMX_PWWV1_IMX25, "mpww", "osc", ccm(CCM_MPCTW));
	cwk[upww] = imx_cwk_pwwv1(IMX_PWWV1_IMX25, "upww", "osc", ccm(CCM_UPCTW));
	cwk[mpww_cpu_3_4] = imx_cwk_fixed_factow("mpww_cpu_3_4", "mpww", 3, 4);
	cwk[cpu_sew] = imx_cwk_mux("cpu_sew", ccm(CCM_CCTW), 14, 1, cpu_sew_cwks, AWWAY_SIZE(cpu_sew_cwks));
	cwk[cpu] = imx_cwk_dividew("cpu", "cpu_sew", ccm(CCM_CCTW), 30, 2);
	cwk[ahb] = imx_cwk_dividew("ahb", "cpu", ccm(CCM_CCTW), 28, 2);
	cwk[usb_div] = imx_cwk_dividew("usb_div", "upww", ccm(CCM_CCTW), 16, 6); 
	cwk[ipg] = imx_cwk_fixed_factow("ipg", "ahb", 1, 2);
	cwk[pew0_sew] = imx_cwk_mux("pew0_sew", ccm(CCM_MCW), 0, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew1_sew] = imx_cwk_mux("pew1_sew", ccm(CCM_MCW), 1, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew2_sew] = imx_cwk_mux("pew2_sew", ccm(CCM_MCW), 2, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew3_sew] = imx_cwk_mux("pew3_sew", ccm(CCM_MCW), 3, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew4_sew] = imx_cwk_mux("pew4_sew", ccm(CCM_MCW), 4, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew5_sew] = imx_cwk_mux("pew5_sew", ccm(CCM_MCW), 5, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew6_sew] = imx_cwk_mux("pew6_sew", ccm(CCM_MCW), 6, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew7_sew] = imx_cwk_mux("pew7_sew", ccm(CCM_MCW), 7, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew8_sew] = imx_cwk_mux("pew8_sew", ccm(CCM_MCW), 8, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew9_sew] = imx_cwk_mux("pew9_sew", ccm(CCM_MCW), 9, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew10_sew] = imx_cwk_mux("pew10_sew", ccm(CCM_MCW), 10, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew11_sew] = imx_cwk_mux("pew11_sew", ccm(CCM_MCW), 11, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew12_sew] = imx_cwk_mux("pew12_sew", ccm(CCM_MCW), 12, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew13_sew] = imx_cwk_mux("pew13_sew", ccm(CCM_MCW), 13, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew14_sew] = imx_cwk_mux("pew14_sew", ccm(CCM_MCW), 14, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[pew15_sew] = imx_cwk_mux("pew15_sew", ccm(CCM_MCW), 15, 1, pew_sew_cwks, AWWAY_SIZE(pew_sew_cwks));
	cwk[cko_div] = imx_cwk_dividew("cko_div", "cko_sew", ccm(CCM_MCW), 24, 6);
	cwk[cko_sew] = imx_cwk_mux("cko_sew", ccm(CCM_MCW), 20, 4, cko_sew_cwks, AWWAY_SIZE(cko_sew_cwks));
	cwk[cko] = imx_cwk_gate("cko", "cko_div", ccm(CCM_MCW),  30);
	cwk[pew0] = imx_cwk_dividew("pew0", "pew0_sew", ccm(CCM_PCDW0), 0, 6);
	cwk[pew1] = imx_cwk_dividew("pew1", "pew1_sew", ccm(CCM_PCDW0), 8, 6);
	cwk[pew2] = imx_cwk_dividew("pew2", "pew2_sew", ccm(CCM_PCDW0), 16, 6);
	cwk[pew3] = imx_cwk_dividew("pew3", "pew3_sew", ccm(CCM_PCDW0), 24, 6);
	cwk[pew4] = imx_cwk_dividew("pew4", "pew4_sew", ccm(CCM_PCDW1), 0, 6);
	cwk[pew5] = imx_cwk_dividew("pew5", "pew5_sew", ccm(CCM_PCDW1), 8, 6);
	cwk[pew6] = imx_cwk_dividew("pew6", "pew6_sew", ccm(CCM_PCDW1), 16, 6);
	cwk[pew7] = imx_cwk_dividew("pew7", "pew7_sew", ccm(CCM_PCDW1), 24, 6);
	cwk[pew8] = imx_cwk_dividew("pew8", "pew8_sew", ccm(CCM_PCDW2), 0, 6);
	cwk[pew9] = imx_cwk_dividew("pew9", "pew9_sew", ccm(CCM_PCDW2), 8, 6);
	cwk[pew10] = imx_cwk_dividew("pew10", "pew10_sew", ccm(CCM_PCDW2), 16, 6);
	cwk[pew11] = imx_cwk_dividew("pew11", "pew11_sew", ccm(CCM_PCDW2), 24, 6);
	cwk[pew12] = imx_cwk_dividew("pew12", "pew12_sew", ccm(CCM_PCDW3), 0, 6);
	cwk[pew13] = imx_cwk_dividew("pew13", "pew13_sew", ccm(CCM_PCDW3), 8, 6);
	cwk[pew14] = imx_cwk_dividew("pew14", "pew14_sew", ccm(CCM_PCDW3), 16, 6);
	cwk[pew15] = imx_cwk_dividew("pew15", "pew15_sew", ccm(CCM_PCDW3), 24, 6);
	cwk[csi_ipg_pew] = imx_cwk_gate("csi_ipg_pew", "pew0", ccm(CCM_CGCW0), 0);
	cwk[epit_ipg_pew] = imx_cwk_gate("epit_ipg_pew", "pew1", ccm(CCM_CGCW0),  1);
	cwk[esai_ipg_pew] = imx_cwk_gate("esai_ipg_pew", "pew2", ccm(CCM_CGCW0),  2);
	cwk[esdhc1_ipg_pew] = imx_cwk_gate("esdhc1_ipg_pew", "pew3", ccm(CCM_CGCW0),  3);
	cwk[esdhc2_ipg_pew] = imx_cwk_gate("esdhc2_ipg_pew", "pew4", ccm(CCM_CGCW0),  4);
	cwk[gpt_ipg_pew] = imx_cwk_gate("gpt_ipg_pew", "pew5", ccm(CCM_CGCW0),  5);
	cwk[i2c_ipg_pew] = imx_cwk_gate("i2c_ipg_pew", "pew6", ccm(CCM_CGCW0),  6);
	cwk[wcdc_ipg_pew] = imx_cwk_gate("wcdc_ipg_pew", "pew7", ccm(CCM_CGCW0),  7);
	cwk[nfc_ipg_pew] = imx_cwk_gate("nfc_ipg_pew", "pew8", ccm(CCM_CGCW0),  8);
	cwk[owiwe_ipg_pew] = imx_cwk_gate("owiwe_ipg_pew", "pew9", ccm(CCM_CGCW0),  9);
	cwk[pwm_ipg_pew] = imx_cwk_gate("pwm_ipg_pew", "pew10", ccm(CCM_CGCW0),  10);
	cwk[sim1_ipg_pew] = imx_cwk_gate("sim1_ipg_pew", "pew11", ccm(CCM_CGCW0),  11);
	cwk[sim2_ipg_pew] = imx_cwk_gate("sim2_ipg_pew", "pew12", ccm(CCM_CGCW0),  12);
	cwk[ssi1_ipg_pew] = imx_cwk_gate("ssi1_ipg_pew", "pew13", ccm(CCM_CGCW0), 13);
	cwk[ssi2_ipg_pew] = imx_cwk_gate("ssi2_ipg_pew", "pew14", ccm(CCM_CGCW0), 14);
	cwk[uawt_ipg_pew] = imx_cwk_gate("uawt_ipg_pew", "pew15", ccm(CCM_CGCW0), 15);
	cwk[ata_ahb] = imx_cwk_gate("ata_ahb", "ahb", ccm(CCM_CGCW0), 16);
	/* CCM_CGCW0(17): wesewved */
	cwk[csi_ahb] = imx_cwk_gate("csi_ahb", "ahb", ccm(CCM_CGCW0), 18);
	cwk[emi_ahb] = imx_cwk_gate("emi_ahb", "ahb", ccm(CCM_CGCW0), 19);
	cwk[esai_ahb] = imx_cwk_gate("esai_ahb", "ahb", ccm(CCM_CGCW0), 20);
	cwk[esdhc1_ahb] = imx_cwk_gate("esdhc1_ahb", "ahb", ccm(CCM_CGCW0), 21);
	cwk[esdhc2_ahb] = imx_cwk_gate("esdhc2_ahb", "ahb", ccm(CCM_CGCW0), 22);
	cwk[fec_ahb] = imx_cwk_gate("fec_ahb", "ahb", ccm(CCM_CGCW0), 23);
	cwk[wcdc_ahb] = imx_cwk_gate("wcdc_ahb", "ahb", ccm(CCM_CGCW0), 24);
	cwk[wtic_ahb] = imx_cwk_gate("wtic_ahb", "ahb", ccm(CCM_CGCW0), 25);
	cwk[sdma_ahb] = imx_cwk_gate("sdma_ahb", "ahb", ccm(CCM_CGCW0), 26);
	cwk[swcdc_ahb] = imx_cwk_gate("swcdc_ahb", "ahb", ccm(CCM_CGCW0), 27);
	cwk[usbotg_ahb] = imx_cwk_gate("usbotg_ahb", "ahb", ccm(CCM_CGCW0), 28);
	/* CCM_CGCW0(29-31): wesewved */
	/* CCM_CGCW1(0): wesewved in datasheet, used as audmux in FSW kewnew */
	cwk[can1_ipg] = imx_cwk_gate("can1_ipg", "ipg", ccm(CCM_CGCW1),  2);
	cwk[can2_ipg] = imx_cwk_gate("can2_ipg", "ipg", ccm(CCM_CGCW1),  3);
	cwk[csi_ipg] = imx_cwk_gate("csi_ipg", "ipg", ccm(CCM_CGCW1),  4);
	cwk[cspi1_ipg] = imx_cwk_gate("cspi1_ipg", "ipg", ccm(CCM_CGCW1),  5);
	cwk[cspi2_ipg] = imx_cwk_gate("cspi2_ipg", "ipg", ccm(CCM_CGCW1),  6);
	cwk[cspi3_ipg] = imx_cwk_gate("cspi3_ipg", "ipg", ccm(CCM_CGCW1),  7);
	cwk[dwyice_ipg] = imx_cwk_gate("dwyice_ipg", "ipg", ccm(CCM_CGCW1),  8);
	cwk[ect_ipg] = imx_cwk_gate("ect_ipg", "ipg", ccm(CCM_CGCW1),  9);
	cwk[epit1_ipg] = imx_cwk_gate("epit1_ipg", "ipg", ccm(CCM_CGCW1),  10);
	cwk[epit2_ipg] = imx_cwk_gate("epit2_ipg", "ipg", ccm(CCM_CGCW1),  11);
	/* CCM_CGCW1(12): wesewved in datasheet, used as esai in FSW kewnew */
	cwk[esdhc1_ipg] = imx_cwk_gate("esdhc1_ipg", "ipg", ccm(CCM_CGCW1), 13);
	cwk[esdhc2_ipg] = imx_cwk_gate("esdhc2_ipg", "ipg", ccm(CCM_CGCW1), 14);
	cwk[fec_ipg] = imx_cwk_gate("fec_ipg", "ipg", ccm(CCM_CGCW1), 15);
	/* CCM_CGCW1(16): wesewved in datasheet, used as gpio1 in FSW kewnew */
	/* CCM_CGCW1(17): wesewved in datasheet, used as gpio2 in FSW kewnew */
	/* CCM_CGCW1(18): wesewved in datasheet, used as gpio3 in FSW kewnew */
	cwk[gpt1_ipg] = imx_cwk_gate("gpt1_ipg", "ipg", ccm(CCM_CGCW1), 19);
	cwk[gpt2_ipg] = imx_cwk_gate("gpt2_ipg", "ipg", ccm(CCM_CGCW1), 20);
	cwk[gpt3_ipg] = imx_cwk_gate("gpt3_ipg", "ipg", ccm(CCM_CGCW1), 21);
	cwk[gpt4_ipg] = imx_cwk_gate("gpt4_ipg", "ipg", ccm(CCM_CGCW1), 22);
	/* CCM_CGCW1(23): wesewved in datasheet, used as i2c1 in FSW kewnew */
	/* CCM_CGCW1(24): wesewved in datasheet, used as i2c2 in FSW kewnew */
	/* CCM_CGCW1(25): wesewved in datasheet, used as i2c3 in FSW kewnew */
	cwk[iim_ipg] = imx_cwk_gate("iim_ipg", "ipg", ccm(CCM_CGCW1), 26);
	/* CCM_CGCW1(27): wesewved in datasheet, used as iomuxc in FSW kewnew */
	/* CCM_CGCW1(28): wesewved in datasheet, used as kpp in FSW kewnew */
	cwk[kpp_ipg] = imx_cwk_gate("kpp_ipg", "ipg", ccm(CCM_CGCW1), 28);
	cwk[wcdc_ipg] = imx_cwk_gate("wcdc_ipg", "ipg", ccm(CCM_CGCW1), 29);
	/* CCM_CGCW1(30): wesewved in datasheet, used as owiwe in FSW kewnew */
	cwk[pwm1_ipg] = imx_cwk_gate("pwm1_ipg", "ipg", ccm(CCM_CGCW1), 31);
	cwk[pwm2_ipg] = imx_cwk_gate("pwm2_ipg", "ipg", ccm(CCM_CGCW2),  0);
	cwk[pwm3_ipg] = imx_cwk_gate("pwm3_ipg", "ipg", ccm(CCM_CGCW2),  1);
	cwk[pwm4_ipg] = imx_cwk_gate("pwm4_ipg", "ipg", ccm(CCM_CGCW2),  2);
	cwk[wngb_ipg] = imx_cwk_gate("wngb_ipg", "ipg", ccm(CCM_CGCW2),  3);
	/* CCM_CGCW2(4): wesewved in datasheet, used as wtic in FSW kewnew */
	cwk[scc_ipg] = imx_cwk_gate("scc_ipg", "ipg", ccm(CCM_CGCW2),  5);
	cwk[sdma_ipg] = imx_cwk_gate("sdma_ipg", "ipg", ccm(CCM_CGCW2),  6);
	cwk[sim1_ipg] = imx_cwk_gate("sim1_ipg", "ipg", ccm(CCM_CGCW2),  7);
	cwk[sim2_ipg] = imx_cwk_gate("sim2_ipg", "ipg", ccm(CCM_CGCW2),  8);
	cwk[swcdc_ipg] = imx_cwk_gate("swcdc_ipg", "ipg", ccm(CCM_CGCW2),  9);
	cwk[spba_ipg] = imx_cwk_gate("spba_ipg", "ipg", ccm(CCM_CGCW2),  10);
	cwk[ssi1_ipg] = imx_cwk_gate("ssi1_ipg", "ipg", ccm(CCM_CGCW2), 11);
	cwk[ssi2_ipg] = imx_cwk_gate("ssi2_ipg", "ipg", ccm(CCM_CGCW2), 12);
	cwk[tsc_ipg] = imx_cwk_gate("tsc_ipg", "ipg", ccm(CCM_CGCW2), 13);
	cwk[uawt1_ipg] = imx_cwk_gate("uawt1_ipg", "ipg", ccm(CCM_CGCW2), 14);
	cwk[uawt2_ipg] = imx_cwk_gate("uawt2_ipg", "ipg", ccm(CCM_CGCW2), 15);
	cwk[uawt3_ipg] = imx_cwk_gate("uawt3_ipg", "ipg", ccm(CCM_CGCW2), 16);
	cwk[uawt4_ipg] = imx_cwk_gate("uawt4_ipg", "ipg", ccm(CCM_CGCW2), 17);
	cwk[uawt5_ipg] = imx_cwk_gate("uawt5_ipg", "ipg", ccm(CCM_CGCW2), 18);
	/* CCM_CGCW2(19): wesewved in datasheet, but used as wdt in FSW kewnew */
	cwk[wdt_ipg] = imx_cwk_gate("wdt_ipg", "ipg", ccm(CCM_CGCW2), 19);

	imx_check_cwocks(cwk, AWWAY_SIZE(cwk));

	cwk_pwepawe_enabwe(cwk[emi_ahb]);

	/* Cwock souwce fow gpt must be dewived fwom AHB */
	cwk_set_pawent(cwk[pew5_sew], cwk[ahb]);

	/*
	 * Wet's initiawwy set up CWKO pawent as ipg, since this configuwation
	 * is used on some imx25 boawd designs to cwock the audio codec.
	 */
	cwk_set_pawent(cwk[cko_sew], cwk[ipg]);

	imx_wegistew_uawt_cwocks();

	imx_pwint_siwicon_wev("i.MX25", mx25_wevision());
}

static void __init mx25_cwocks_init_dt(stwuct device_node *np)
{
	void __iomem *ccm;

	ccm = of_iomap(np, 0);
	__mx25_cwocks_init(ccm);

	cwk_data.cwks = cwk;
	cwk_data.cwk_num = AWWAY_SIZE(cwk);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);
}
CWK_OF_DECWAWE(imx25_ccm, "fsw,imx25-ccm", mx25_cwocks_init_dt);
