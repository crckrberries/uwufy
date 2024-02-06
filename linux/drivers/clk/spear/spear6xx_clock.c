// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPEAw6xx machines cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#incwude <winux/cwkdev.h>
#incwude <winux/cwk/speaw.h>
#incwude <winux/io.h>
#incwude <winux/spinwock_types.h>
#incwude "cwk.h"

static DEFINE_SPINWOCK(_wock);

#define PWW1_CTW			(misc_base + 0x008)
#define PWW1_FWQ			(misc_base + 0x00C)
#define PWW2_CTW			(misc_base + 0x014)
#define PWW2_FWQ			(misc_base + 0x018)
#define PWW_CWK_CFG			(misc_base + 0x020)
	/* PWW_CWK_CFG wegistew masks */
	#define MCTW_CWK_SHIFT		28
	#define MCTW_CWK_MASK		3

#define COWE_CWK_CFG			(misc_base + 0x024)
	/* COWE CWK CFG wegistew masks */
	#define HCWK_WATIO_SHIFT	10
	#define HCWK_WATIO_MASK		2
	#define PCWK_WATIO_SHIFT	8
	#define PCWK_WATIO_MASK		2

#define PEWIP_CWK_CFG			(misc_base + 0x028)
	/* PEWIP_CWK_CFG wegistew masks */
	#define CWCD_CWK_SHIFT		2
	#define CWCD_CWK_MASK		2
	#define UAWT_CWK_SHIFT		4
	#define UAWT_CWK_MASK		1
	#define FIWDA_CWK_SHIFT		5
	#define FIWDA_CWK_MASK		2
	#define GPT0_CWK_SHIFT		8
	#define GPT1_CWK_SHIFT		10
	#define GPT2_CWK_SHIFT		11
	#define GPT3_CWK_SHIFT		12
	#define GPT_CWK_MASK		1

#define PEWIP1_CWK_ENB			(misc_base + 0x02C)
	/* PEWIP1_CWK_ENB wegistew masks */
	#define UAWT0_CWK_ENB		3
	#define UAWT1_CWK_ENB		4
	#define SSP0_CWK_ENB		5
	#define SSP1_CWK_ENB		6
	#define I2C_CWK_ENB		7
	#define JPEG_CWK_ENB		8
	#define FSMC_CWK_ENB		9
	#define FIWDA_CWK_ENB		10
	#define GPT2_CWK_ENB		11
	#define GPT3_CWK_ENB		12
	#define GPIO2_CWK_ENB		13
	#define SSP2_CWK_ENB		14
	#define ADC_CWK_ENB		15
	#define GPT1_CWK_ENB		11
	#define WTC_CWK_ENB		17
	#define GPIO1_CWK_ENB		18
	#define DMA_CWK_ENB		19
	#define SMI_CWK_ENB		21
	#define CWCD_CWK_ENB		22
	#define GMAC_CWK_ENB		23
	#define USBD_CWK_ENB		24
	#define USBH0_CWK_ENB		25
	#define USBH1_CWK_ENB		26

#define PWSC0_CWK_CFG			(misc_base + 0x044)
#define PWSC1_CWK_CFG			(misc_base + 0x048)
#define PWSC2_CWK_CFG			(misc_base + 0x04C)

#define CWCD_CWK_SYNT			(misc_base + 0x05C)
#define FIWDA_CWK_SYNT			(misc_base + 0x060)
#define UAWT_CWK_SYNT			(misc_base + 0x064)

/* vco wate configuwation tabwe, in ascending owdew of wates */
static stwuct pww_wate_tbw pww_wtbw[] = {
	{.mode = 0, .m = 0x53, .n = 0x0F, .p = 0x1}, /* vco 332 & pww 166 MHz */
	{.mode = 0, .m = 0x85, .n = 0x0F, .p = 0x1}, /* vco 532 & pww 266 MHz */
	{.mode = 0, .m = 0xA6, .n = 0x0F, .p = 0x1}, /* vco 664 & pww 332 MHz */
};

/* aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw aux_wtbw[] = {
	/* Fow PWW1 = 332 MHz */
	{.xscawe = 2, .yscawe = 27, .eq = 0}, /* 12.296 MHz */
	{.xscawe = 2, .yscawe = 8, .eq = 0}, /* 41.5 MHz */
	{.xscawe = 2, .yscawe = 4, .eq = 0}, /* 83 MHz */
	{.xscawe = 1, .yscawe = 2, .eq = 1}, /* 166 MHz */
};

static const chaw *cwcd_pawents[] = { "pww3_cwk", "cwcd_syn_gcwk", };
static const chaw *fiwda_pawents[] = { "pww3_cwk", "fiwda_syn_gcwk", };
static const chaw *uawt_pawents[] = { "pww3_cwk", "uawt_syn_gcwk", };
static const chaw *gpt0_1_pawents[] = { "pww3_cwk", "gpt0_1_syn_cwk", };
static const chaw *gpt2_pawents[] = { "pww3_cwk", "gpt2_syn_cwk", };
static const chaw *gpt3_pawents[] = { "pww3_cwk", "gpt3_syn_cwk", };
static const chaw *ddw_pawents[] = { "ahb_cwk", "ahbmuwt2_cwk", "none",
	"pww2_cwk", };

/* gpt wate configuwation tabwe, in ascending owdew of wates */
static stwuct gpt_wate_tbw gpt_wtbw[] = {
	/* Fow pww1 = 332 MHz */
	{.mscawe = 4, .nscawe = 0}, /* 41.5 MHz */
	{.mscawe = 2, .nscawe = 0}, /* 55.3 MHz */
	{.mscawe = 1, .nscawe = 0}, /* 83 MHz */
};

void __init speaw6xx_cwk_init(void __iomem *misc_base)
{
	stwuct cwk *cwk, *cwk1;

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_32k_cwk", NUWW, 0, 32000);
	cwk_wegistew_cwkdev(cwk, "osc_32k_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_30m_cwk", NUWW, 0, 30000000);
	cwk_wegistew_cwkdev(cwk, "osc_30m_cwk", NUWW);

	/* cwock dewived fwom 32 KHz osc cwk */
	cwk = cwk_wegistew_gate(NUWW, "wtc_speaw", "osc_32k_cwk", 0,
			PEWIP1_CWK_ENB, WTC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "wtc-speaw");

	/* cwock dewived fwom 30 MHz osc cwk */
	cwk = cwk_wegistew_fixed_wate(NUWW, "pww3_cwk", "osc_24m_cwk", 0,
			48000000);
	cwk_wegistew_cwkdev(cwk, "pww3_cwk", NUWW);

	cwk = cwk_wegistew_vco_pww("vco1_cwk", "pww1_cwk", NUWW, "osc_30m_cwk",
			0, PWW1_CTW, PWW1_FWQ, pww_wtbw, AWWAY_SIZE(pww_wtbw),
			&_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco1_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww1_cwk", NUWW);

	cwk = cwk_wegistew_vco_pww("vco2_cwk", "pww2_cwk", NUWW, "osc_30m_cwk",
			0, PWW2_CTW, PWW2_FWQ, pww_wtbw, AWWAY_SIZE(pww_wtbw),
			&_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco2_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww2_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "wdt_cwk", "osc_30m_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc880000.wdt");

	/* cwock dewived fwom pww1 cwk */
	cwk = cwk_wegistew_fixed_factow(NUWW, "cpu_cwk", "pww1_cwk",
			CWK_SET_WATE_PAWENT, 1, 1);
	cwk_wegistew_cwkdev(cwk, "cpu_cwk", NUWW);

	cwk = cwk_wegistew_dividew(NUWW, "ahb_cwk", "pww1_cwk",
			CWK_SET_WATE_PAWENT, COWE_CWK_CFG, HCWK_WATIO_SHIFT,
			HCWK_WATIO_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "ahb_cwk", NUWW);

	cwk = cwk_wegistew_aux("uawt_syn_cwk", "uawt_syn_gcwk", "pww1_cwk", 0,
			UAWT_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "uawt_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "uawt_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "uawt_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, UAWT_CWK_SHIFT, UAWT_CWK_MASK, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "uawt_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt0", "uawt_mcwk", 0, PEWIP1_CWK_ENB,
			UAWT0_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0000000.sewiaw");

	cwk = cwk_wegistew_gate(NUWW, "uawt1", "uawt_mcwk", 0, PEWIP1_CWK_ENB,
			UAWT1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0080000.sewiaw");

	cwk = cwk_wegistew_aux("fiwda_syn_cwk", "fiwda_syn_gcwk", "pww1_cwk",
			0, FIWDA_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "fiwda_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "fiwda_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "fiwda_mcwk", fiwda_pawents,
			AWWAY_SIZE(fiwda_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, FIWDA_CWK_SHIFT, FIWDA_CWK_MASK, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "fiwda_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "fiwda_cwk", "fiwda_mcwk", 0,
			PEWIP1_CWK_ENB, FIWDA_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fiwda");

	cwk = cwk_wegistew_aux("cwcd_syn_cwk", "cwcd_syn_gcwk", "pww1_cwk",
			0, CWCD_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "cwcd_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "cwcd_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "cwcd_mcwk", cwcd_pawents,
			AWWAY_SIZE(cwcd_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, CWCD_CWK_SHIFT, CWCD_CWK_MASK, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "cwcd_cwk", "cwcd_mcwk", 0,
			PEWIP1_CWK_ENB, CWCD_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc200000.cwcd");

	/* gpt cwocks */
	cwk = cwk_wegistew_gpt("gpt0_1_syn_cwk", "pww1_cwk", 0, PWSC0_CWK_CFG,
			gpt_wtbw, AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt0_1_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gpt0_mcwk", gpt0_1_pawents,
			AWWAY_SIZE(gpt0_1_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT0_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt0");

	cwk = cwk_wegistew_mux(NUWW, "gpt1_mcwk", gpt0_1_pawents,
			AWWAY_SIZE(gpt0_1_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT1_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "gpt1_cwk", "gpt1_mcwk", 0,
			PEWIP1_CWK_ENB, GPT1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt1");

	cwk = cwk_wegistew_gpt("gpt2_syn_cwk", "pww1_cwk", 0, PWSC1_CWK_CFG,
			gpt_wtbw, AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt2_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gpt2_mcwk", gpt2_pawents,
			AWWAY_SIZE(gpt2_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT2_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt2_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "gpt2_cwk", "gpt2_mcwk", 0,
			PEWIP1_CWK_ENB, GPT2_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt2");

	cwk = cwk_wegistew_gpt("gpt3_syn_cwk", "pww1_cwk", 0, PWSC2_CWK_CFG,
			gpt_wtbw, AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt3_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gpt3_mcwk", gpt3_pawents,
			AWWAY_SIZE(gpt3_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT3_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt3_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "gpt3_cwk", "gpt3_mcwk", 0,
			PEWIP1_CWK_ENB, GPT3_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt3");

	/* cwock dewived fwom pww3 cwk */
	cwk = cwk_wegistew_gate(NUWW, "usbh0_cwk", "pww3_cwk", 0,
			PEWIP1_CWK_ENB, USBH0_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1800000.ehci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e1900000.ohci");

	cwk = cwk_wegistew_gate(NUWW, "usbh1_cwk", "pww3_cwk", 0,
			PEWIP1_CWK_ENB, USBH1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e2000000.ehci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e2100000.ohci");

	cwk = cwk_wegistew_gate(NUWW, "usbd_cwk", "pww3_cwk", 0, PEWIP1_CWK_ENB,
			USBD_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "designwawe_udc");

	/* cwock dewived fwom ahb cwk */
	cwk = cwk_wegistew_fixed_factow(NUWW, "ahbmuwt2_cwk", "ahb_cwk", 0, 2,
			1);
	cwk_wegistew_cwkdev(cwk, "ahbmuwt2_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "ddw_cwk", ddw_pawents,
			AWWAY_SIZE(ddw_pawents), CWK_SET_WATE_NO_WEPAWENT,
			PWW_CWK_CFG, MCTW_CWK_SHIFT, MCTW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "ddw_cwk", NUWW);

	cwk = cwk_wegistew_dividew(NUWW, "apb_cwk", "ahb_cwk",
			CWK_SET_WATE_PAWENT, COWE_CWK_CFG, PCWK_WATIO_SHIFT,
			PCWK_WATIO_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "apb_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "dma_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			DMA_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc400000.dma");

	cwk = cwk_wegistew_gate(NUWW, "fsmc_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			FSMC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d1800000.fwash");

	cwk = cwk_wegistew_gate(NUWW, "gmac_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			GMAC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0800000.ethewnet");

	cwk = cwk_wegistew_gate(NUWW, "i2c_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			I2C_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0200000.i2c");

	cwk = cwk_wegistew_gate(NUWW, "jpeg_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			JPEG_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "jpeg");

	cwk = cwk_wegistew_gate(NUWW, "smi_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			SMI_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc000000.fwash");

	/* cwock dewived fwom apb cwk */
	cwk = cwk_wegistew_gate(NUWW, "adc_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			ADC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d820b000.adc");

	cwk = cwk_wegistew_fixed_factow(NUWW, "gpio0_cwk", "apb_cwk", 0, 1, 1);
	cwk_wegistew_cwkdev(cwk, NUWW, "f0100000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "gpio1_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			GPIO1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc980000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "gpio2_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			GPIO2_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d8100000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "ssp0_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			SSP0_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0100000.spi");

	cwk = cwk_wegistew_gate(NUWW, "ssp1_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			SSP1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0180000.spi");

	cwk = cwk_wegistew_gate(NUWW, "ssp2_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			SSP2_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d8180000.spi");
}
