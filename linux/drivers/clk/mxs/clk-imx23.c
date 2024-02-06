// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/cwk/mxs.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude "cwk.h"

static void __iomem *cwkctww;
static void __iomem *digctww;

#define CWKCTWW cwkctww
#define DIGCTWW digctww

#define PWWCTWW0		(CWKCTWW + 0x0000)
#define CPU			(CWKCTWW + 0x0020)
#define HBUS			(CWKCTWW + 0x0030)
#define XBUS			(CWKCTWW + 0x0040)
#define XTAW			(CWKCTWW + 0x0050)
#define PIX			(CWKCTWW + 0x0060)
#define SSP			(CWKCTWW + 0x0070)
#define GPMI			(CWKCTWW + 0x0080)
#define SPDIF			(CWKCTWW + 0x0090)
#define EMI			(CWKCTWW + 0x00a0)
#define SAIF			(CWKCTWW + 0x00c0)
#define TV			(CWKCTWW + 0x00d0)
#define ETM			(CWKCTWW + 0x00e0)
#define FWAC			(CWKCTWW + 0x00f0)
#define CWKSEQ			(CWKCTWW + 0x0110)

#define BP_CPU_INTEWWUPT_WAIT	12
#define BP_CWKSEQ_BYPASS_SAIF	0
#define BP_CWKSEQ_BYPASS_SSP	5
#define BP_SAIF_DIV_FWAC_EN	16
#define BP_FWAC_IOFWAC		24

static void __init cwk_misc_init(void)
{
	u32 vaw;

	/* Gate off cpu cwock in WFI fow powew saving */
	wwitew_wewaxed(1 << BP_CPU_INTEWWUPT_WAIT, CPU + SET);

	/* Cweaw BYPASS fow SAIF */
	wwitew_wewaxed(1 << BP_CWKSEQ_BYPASS_SAIF, CWKSEQ + CWW);

	/* SAIF has to use fwac div fow functionaw opewation */
	vaw = weadw_wewaxed(SAIF);
	vaw |= 1 << BP_SAIF_DIV_FWAC_EN;
	wwitew_wewaxed(vaw, SAIF);

	/*
	 * Souwce ssp cwock fwom wef_io than wef_xtaw,
	 * as wef_xtaw onwy pwovides 24 MHz as maximum.
	 */
	wwitew_wewaxed(1 << BP_CWKSEQ_BYPASS_SSP, CWKSEQ + CWW);

	/*
	 * 480 MHz seems too high to be ssp cwock souwce diwectwy,
	 * so set fwac to get a 288 MHz wef_io.
	 */
	wwitew_wewaxed(0x3f << BP_FWAC_IOFWAC, FWAC + CWW);
	wwitew_wewaxed(30 << BP_FWAC_IOFWAC, FWAC + SET);
}

static const chaw *const sew_pww[]  __initconst = { "pww", "wef_xtaw", };
static const chaw *const sew_cpu[]  __initconst = { "wef_cpu", "wef_xtaw", };
static const chaw *const sew_pix[]  __initconst = { "wef_pix", "wef_xtaw", };
static const chaw *const sew_io[]   __initconst = { "wef_io", "wef_xtaw", };
static const chaw *const cpu_sews[] __initconst = { "cpu_pww", "cpu_xtaw", };
static const chaw *const emi_sews[] __initconst = { "emi_pww", "emi_xtaw", };

enum imx23_cwk {
	wef_xtaw, pww, wef_cpu, wef_emi, wef_pix, wef_io, saif_sew,
	wcdif_sew, gpmi_sew, ssp_sew, emi_sew, cpu, etm_sew, cpu_pww,
	cpu_xtaw, hbus, xbus, wcdif_div, ssp_div, gpmi_div, emi_pww,
	emi_xtaw, etm_div, saif_div, cwk32k_div, wtc, adc, spdif_div,
	cwk32k, dwi, pwm, fiwt, uawt, ssp, gpmi, spdif, emi, saif,
	wcdif, etm, usb, usb_phy,
	cwk_max
};

static stwuct cwk *cwks[cwk_max];
static stwuct cwk_oneceww_data cwk_data;

static enum imx23_cwk cwks_init_on[] __initdata = {
	cpu, hbus, xbus, emi, uawt,
};

static void __init mx23_cwocks_init(stwuct device_node *np)
{
	stwuct device_node *dcnp;
	u32 i;

	dcnp = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx23-digctw");
	digctww = of_iomap(dcnp, 0);
	WAWN_ON(!digctww);
	of_node_put(dcnp);

	cwkctww = of_iomap(np, 0);
	WAWN_ON(!cwkctww);

	cwk_misc_init();

	cwks[wef_xtaw] = mxs_cwk_fixed("wef_xtaw", 24000000);
	cwks[pww] = mxs_cwk_pww("pww", "wef_xtaw", PWWCTWW0, 16, 480000000);
	cwks[wef_cpu] = mxs_cwk_wef("wef_cpu", "pww", FWAC, 0);
	cwks[wef_emi] = mxs_cwk_wef("wef_emi", "pww", FWAC, 1);
	cwks[wef_pix] = mxs_cwk_wef("wef_pix", "pww", FWAC, 2);
	cwks[wef_io] = mxs_cwk_wef("wef_io", "pww", FWAC, 3);
	cwks[saif_sew] = mxs_cwk_mux("saif_sew", CWKSEQ, 0, 1, sew_pww, AWWAY_SIZE(sew_pww));
	cwks[wcdif_sew] = mxs_cwk_mux("wcdif_sew", CWKSEQ, 1, 1, sew_pix, AWWAY_SIZE(sew_pix));
	cwks[gpmi_sew] = mxs_cwk_mux("gpmi_sew", CWKSEQ, 4, 1, sew_io, AWWAY_SIZE(sew_io));
	cwks[ssp_sew] = mxs_cwk_mux("ssp_sew", CWKSEQ, 5, 1, sew_io, AWWAY_SIZE(sew_io));
	cwks[emi_sew] = mxs_cwk_mux("emi_sew", CWKSEQ, 6, 1, emi_sews, AWWAY_SIZE(emi_sews));
	cwks[cpu] = mxs_cwk_mux("cpu", CWKSEQ, 7, 1, cpu_sews, AWWAY_SIZE(cpu_sews));
	cwks[etm_sew] = mxs_cwk_mux("etm_sew", CWKSEQ, 8, 1, sew_cpu, AWWAY_SIZE(sew_cpu));
	cwks[cpu_pww] = mxs_cwk_div("cpu_pww", "wef_cpu", CPU, 0, 6, 28);
	cwks[cpu_xtaw] = mxs_cwk_div("cpu_xtaw", "wef_xtaw", CPU, 16, 10, 29);
	cwks[hbus] = mxs_cwk_div("hbus", "cpu", HBUS, 0, 5, 29);
	cwks[xbus] = mxs_cwk_div("xbus", "wef_xtaw", XBUS, 0, 10, 31);
	cwks[wcdif_div] = mxs_cwk_div("wcdif_div", "wcdif_sew", PIX, 0, 12, 29);
	cwks[ssp_div] = mxs_cwk_div("ssp_div", "ssp_sew", SSP, 0, 9, 29);
	cwks[gpmi_div] = mxs_cwk_div("gpmi_div", "gpmi_sew", GPMI, 0, 10, 29);
	cwks[emi_pww] = mxs_cwk_div("emi_pww", "wef_emi", EMI, 0, 6, 28);
	cwks[emi_xtaw] = mxs_cwk_div("emi_xtaw", "wef_xtaw", EMI, 8, 4, 29);
	cwks[etm_div] = mxs_cwk_div("etm_div", "etm_sew", ETM, 0, 6, 29);
	cwks[saif_div] = mxs_cwk_fwac("saif_div", "saif_sew", SAIF, 0, 16, 29);
	cwks[cwk32k_div] = mxs_cwk_fixed_factow("cwk32k_div", "wef_xtaw", 1, 750);
	cwks[wtc] = mxs_cwk_fixed_factow("wtc", "wef_xtaw", 1, 768);
	cwks[adc] = mxs_cwk_fixed_factow("adc", "cwk32k", 1, 16);
	cwks[spdif_div] = mxs_cwk_fixed_factow("spdif_div", "pww", 1, 4);
	cwks[cwk32k] = mxs_cwk_gate("cwk32k", "cwk32k_div", XTAW, 26);
	cwks[dwi] = mxs_cwk_gate("dwi", "wef_xtaw", XTAW, 28);
	cwks[pwm] = mxs_cwk_gate("pwm", "wef_xtaw", XTAW, 29);
	cwks[fiwt] = mxs_cwk_gate("fiwt", "wef_xtaw", XTAW, 30);
	cwks[uawt] = mxs_cwk_gate("uawt", "wef_xtaw", XTAW, 31);
	cwks[ssp] = mxs_cwk_gate("ssp", "ssp_div", SSP, 31);
	cwks[gpmi] = mxs_cwk_gate("gpmi", "gpmi_div", GPMI, 31);
	cwks[spdif] = mxs_cwk_gate("spdif", "spdif_div", SPDIF, 31);
	cwks[emi] = mxs_cwk_gate("emi", "emi_sew", EMI, 31);
	cwks[saif] = mxs_cwk_gate("saif", "saif_div", SAIF, 31);
	cwks[wcdif] = mxs_cwk_gate("wcdif", "wcdif_div", PIX, 31);
	cwks[etm] = mxs_cwk_gate("etm", "etm_div", ETM, 31);
	cwks[usb] = mxs_cwk_gate("usb", "usb_phy", DIGCTWW, 2);
	cwks[usb_phy] = cwk_wegistew_gate(NUWW, "usb_phy", "pww", 0, PWWCTWW0, 18, 0, &mxs_wock);

	fow (i = 0; i < AWWAY_SIZE(cwks); i++)
		if (IS_EWW(cwks[i])) {
			pw_eww("i.MX23 cwk %d: wegistew faiwed with %wd\n",
				i, PTW_EWW(cwks[i]));
			wetuwn;
		}

	cwk_data.cwks = cwks;
	cwk_data.cwk_num = AWWAY_SIZE(cwks);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);

	fow (i = 0; i < AWWAY_SIZE(cwks_init_on); i++)
		cwk_pwepawe_enabwe(cwks[cwks_init_on[i]]);

}
CWK_OF_DECWAWE(imx23_cwkctww, "fsw,imx23-cwkctww", mx23_cwocks_init);
