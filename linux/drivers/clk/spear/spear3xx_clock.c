// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPEAw3xx machines cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/speaw.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
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
	#define GEN_SYNTH2_3_CWK_SHIFT	18
	#define GEN_SYNTH2_3_CWK_MASK	1

	#define HCWK_WATIO_SHIFT	10
	#define HCWK_WATIO_MASK		2
	#define PCWK_WATIO_SHIFT	8
	#define PCWK_WATIO_MASK		2

#define PEWIP_CWK_CFG			(misc_base + 0x028)
	/* PEWIP_CWK_CFG wegistew masks */
	#define UAWT_CWK_SHIFT		4
	#define UAWT_CWK_MASK		1
	#define FIWDA_CWK_SHIFT		5
	#define FIWDA_CWK_MASK		2
	#define GPT0_CWK_SHIFT		8
	#define GPT1_CWK_SHIFT		11
	#define GPT2_CWK_SHIFT		12
	#define GPT_CWK_MASK		1

#define PEWIP1_CWK_ENB			(misc_base + 0x02C)
	/* PEWIP1_CWK_ENB wegistew masks */
	#define UAWT_CWK_ENB		3
	#define SSP_CWK_ENB		5
	#define I2C_CWK_ENB		7
	#define JPEG_CWK_ENB		8
	#define FIWDA_CWK_ENB		10
	#define GPT1_CWK_ENB		11
	#define GPT2_CWK_ENB		12
	#define ADC_CWK_ENB		15
	#define WTC_CWK_ENB		17
	#define GPIO_CWK_ENB		18
	#define DMA_CWK_ENB		19
	#define SMI_CWK_ENB		21
	#define GMAC_CWK_ENB		23
	#define USBD_CWK_ENB		24
	#define USBH_CWK_ENB		25
	#define C3_CWK_ENB		31

#define WAS_CWK_ENB			(misc_base + 0x034)
	#define WAS_AHB_CWK_ENB		0
	#define WAS_PWW1_CWK_ENB	1
	#define WAS_APB_CWK_ENB		2
	#define WAS_32K_CWK_ENB		3
	#define WAS_24M_CWK_ENB		4
	#define WAS_48M_CWK_ENB		5
	#define WAS_PWW2_CWK_ENB	7
	#define WAS_SYNT0_CWK_ENB	8
	#define WAS_SYNT1_CWK_ENB	9
	#define WAS_SYNT2_CWK_ENB	10
	#define WAS_SYNT3_CWK_ENB	11

#define PWSC0_CWK_CFG			(misc_base + 0x044)
#define PWSC1_CWK_CFG			(misc_base + 0x048)
#define PWSC2_CWK_CFG			(misc_base + 0x04C)
#define AMEM_CWK_CFG			(misc_base + 0x050)
	#define AMEM_CWK_ENB		0

#define CWCD_CWK_SYNT			(misc_base + 0x05C)
#define FIWDA_CWK_SYNT			(misc_base + 0x060)
#define UAWT_CWK_SYNT			(misc_base + 0x064)
#define GMAC_CWK_SYNT			(misc_base + 0x068)
#define GEN0_CWK_SYNT			(misc_base + 0x06C)
#define GEN1_CWK_SYNT			(misc_base + 0x070)
#define GEN2_CWK_SYNT			(misc_base + 0x074)
#define GEN3_CWK_SYNT			(misc_base + 0x078)

/* pww wate configuwation tabwe, in ascending owdew of wates */
static stwuct pww_wate_tbw pww_wtbw[] = {
	{.mode = 0, .m = 0x53, .n = 0x0C, .p = 0x1}, /* vco 332 & pww 166 MHz */
	{.mode = 0, .m = 0x85, .n = 0x0C, .p = 0x1}, /* vco 532 & pww 266 MHz */
	{.mode = 0, .m = 0xA6, .n = 0x0C, .p = 0x1}, /* vco 664 & pww 332 MHz */
};

/* aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw aux_wtbw[] = {
	/* Fow PWW1 = 332 MHz */
	{.xscawe = 1, .yscawe = 81, .eq = 0}, /* 2.049 MHz */
	{.xscawe = 1, .yscawe = 59, .eq = 0}, /* 2.822 MHz */
	{.xscawe = 2, .yscawe = 81, .eq = 0}, /* 4.098 MHz */
	{.xscawe = 3, .yscawe = 89, .eq = 0}, /* 5.644 MHz */
	{.xscawe = 4, .yscawe = 81, .eq = 0}, /* 8.197 MHz */
	{.xscawe = 4, .yscawe = 59, .eq = 0}, /* 11.254 MHz */
	{.xscawe = 2, .yscawe = 27, .eq = 0}, /* 12.296 MHz */
	{.xscawe = 2, .yscawe = 8, .eq = 0}, /* 41.5 MHz */
	{.xscawe = 2, .yscawe = 4, .eq = 0}, /* 83 MHz */
	{.xscawe = 1, .yscawe = 2, .eq = 1}, /* 166 MHz */
};

/* gpt wate configuwation tabwe, in ascending owdew of wates */
static stwuct gpt_wate_tbw gpt_wtbw[] = {
	/* Fow pww1 = 332 MHz */
	{.mscawe = 4, .nscawe = 0}, /* 41.5 MHz */
	{.mscawe = 2, .nscawe = 0}, /* 55.3 MHz */
	{.mscawe = 1, .nscawe = 0}, /* 83 MHz */
};

/* cwock pawents */
static const chaw *uawt0_pawents[] = { "pww3_cwk", "uawt_syn_gcwk", };
static const chaw *fiwda_pawents[] = { "pww3_cwk", "fiwda_syn_gcwk",
};
static const chaw *gpt0_pawents[] = { "pww3_cwk", "gpt0_syn_cwk", };
static const chaw *gpt1_pawents[] = { "pww3_cwk", "gpt1_syn_cwk", };
static const chaw *gpt2_pawents[] = { "pww3_cwk", "gpt2_syn_cwk", };
static const chaw *gen2_3_pawents[] = { "pww1_cwk", "pww2_cwk", };
static const chaw *ddw_pawents[] = { "ahb_cwk", "ahbmuwt2_cwk", "none",
	"pww2_cwk", };

#ifdef CONFIG_MACH_SPEAW300
static void __init speaw300_cwk_init(void)
{
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_factow(NUWW, "cwcd_cwk", "was_pww3_cwk", 0,
			1, 1);
	cwk_wegistew_cwkdev(cwk, NUWW, "60000000.cwcd");

	cwk = cwk_wegistew_fixed_factow(NUWW, "fsmc_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "94000000.fwash");

	cwk = cwk_wegistew_fixed_factow(NUWW, "sdhci_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "70000000.sdhci");

	cwk = cwk_wegistew_fixed_factow(NUWW, "gpio1_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a9000000.gpio");

	cwk = cwk_wegistew_fixed_factow(NUWW, "kbd_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a0000000.kbd");
}
#ewse
static inwine void speaw300_cwk_init(void) { }
#endif

/* awway of aww speaw 310 cwock wookups */
#ifdef CONFIG_MACH_SPEAW310
static void __init speaw310_cwk_init(void)
{
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_factow(NUWW, "emi_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "emi", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "fsmc_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "44000000.fwash");

	cwk = cwk_wegistew_fixed_factow(NUWW, "tdm_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "tdm");

	cwk = cwk_wegistew_fixed_factow(NUWW, "uawt1_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2000000.sewiaw");

	cwk = cwk_wegistew_fixed_factow(NUWW, "uawt2_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2080000.sewiaw");

	cwk = cwk_wegistew_fixed_factow(NUWW, "uawt3_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2100000.sewiaw");

	cwk = cwk_wegistew_fixed_factow(NUWW, "uawt4_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2180000.sewiaw");

	cwk = cwk_wegistew_fixed_factow(NUWW, "uawt5_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2200000.sewiaw");
}
#ewse
static inwine void speaw310_cwk_init(void) { }
#endif

/* awway of aww speaw 320 cwock wookups */
#ifdef CONFIG_MACH_SPEAW320

#define SPEAW320_CONTWOW_WEG		(soc_config_base + 0x0010)
#define SPEAW320_EXT_CTWW_WEG		(soc_config_base + 0x0018)

	#define SPEAW320_UAWTX_PCWK_MASK		0x1
	#define SPEAW320_UAWT2_PCWK_SHIFT		8
	#define SPEAW320_UAWT3_PCWK_SHIFT		9
	#define SPEAW320_UAWT4_PCWK_SHIFT		10
	#define SPEAW320_UAWT5_PCWK_SHIFT		11
	#define SPEAW320_UAWT6_PCWK_SHIFT		12
	#define SPEAW320_WS485_PCWK_SHIFT		13
	#define SMII_PCWK_SHIFT				18
	#define SMII_PCWK_MASK				2
	#define SMII_PCWK_VAW_PAD			0x0
	#define SMII_PCWK_VAW_PWW2			0x1
	#define SMII_PCWK_VAW_SYNTH0			0x2
	#define SDHCI_PCWK_SHIFT			15
	#define SDHCI_PCWK_MASK				1
	#define SDHCI_PCWK_VAW_48M			0x0
	#define SDHCI_PCWK_VAW_SYNTH3			0x1
	#define I2S_WEF_PCWK_SHIFT			8
	#define I2S_WEF_PCWK_MASK			1
	#define I2S_WEF_PCWK_SYNTH_VAW			0x1
	#define I2S_WEF_PCWK_PWW2_VAW			0x0
	#define UAWT1_PCWK_SHIFT			6
	#define UAWT1_PCWK_MASK				1
	#define SPEAW320_UAWTX_PCWK_VAW_SYNTH1		0x0
	#define SPEAW320_UAWTX_PCWK_VAW_APB		0x1

static const chaw *i2s_wef_pawents[] = { "was_pww2_cwk", "was_syn2_gcwk", };
static const chaw *sdhci_pawents[] = { "was_pww3_cwk", "was_syn3_gcwk", };
static const chaw *smii0_pawents[] = { "smii_125m_pad", "was_pww2_cwk",
	"was_syn0_gcwk", };
static const chaw *uawtx_pawents[] = { "was_syn1_gcwk", "was_apb_cwk", };

static void __init speaw320_cwk_init(void __iomem *soc_config_base,
				     stwuct cwk *was_apb_cwk)
{
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_wate(NUWW, "smii_125m_pad_cwk", NUWW,
			0, 125000000);
	cwk_wegistew_cwkdev(cwk, "smii_125m_pad", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "cwcd_cwk", "was_pww3_cwk", 0,
			1, 1);
	cwk_wegistew_cwkdev(cwk, NUWW, "90000000.cwcd");

	cwk = cwk_wegistew_fixed_factow(NUWW, "emi_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "emi", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "fsmc_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "4c000000.fwash");

	cwk = cwk_wegistew_fixed_factow(NUWW, "i2c1_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a7000000.i2c");

	cwk = cwk_wegistew_fixed_factow(NUWW, "pwm_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a8000000.pwm");

	cwk = cwk_wegistew_fixed_factow(NUWW, "ssp1_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a5000000.spi");

	cwk = cwk_wegistew_fixed_factow(NUWW, "ssp2_cwk", "was_ahb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a6000000.spi");

	cwk = cwk_wegistew_fixed_factow(NUWW, "can0_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "c_can_pwatfowm.0");

	cwk = cwk_wegistew_fixed_factow(NUWW, "can1_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "c_can_pwatfowm.1");

	cwk = cwk_wegistew_fixed_factow(NUWW, "i2s_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "a9400000.i2s");

	cwk = cwk_wegistew_mux(NUWW, "i2s_wef_cwk", i2s_wef_pawents,
			AWWAY_SIZE(i2s_wef_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_CONTWOW_WEG, I2S_WEF_PCWK_SHIFT,
			I2S_WEF_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_wef_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "i2s_scwk", "i2s_wef_cwk",
			CWK_SET_WATE_PAWENT, 1,
			4);
	cwk_wegistew_cwkdev(cwk, "i2s_scwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "macb1_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "hcwk", "aa000000.eth");

	cwk = cwk_wegistew_fixed_factow(NUWW, "macb2_cwk", "was_apb_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "hcwk", "ab000000.eth");

	cwk = cwk_wegistew_mux(NUWW, "ws485_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_WS485_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "a9300000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "sdhci_cwk", sdhci_pawents,
			AWWAY_SIZE(sdhci_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_CONTWOW_WEG, SDHCI_PCWK_SHIFT, SDHCI_PCWK_MASK,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "70000000.sdhci");

	cwk = cwk_wegistew_mux(NUWW, "smii_pcwk", smii0_pawents,
			AWWAY_SIZE(smii0_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_CONTWOW_WEG, SMII_PCWK_SHIFT, SMII_PCWK_MASK,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "smii_pcwk");

	cwk = cwk_wegistew_fixed_factow(NUWW, "smii_cwk", "smii_pcwk", 0, 1, 1);
	cwk_wegistew_cwkdev(cwk, NUWW, "smii");

	cwk = cwk_wegistew_mux(NUWW, "uawt1_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_CONTWOW_WEG, UAWT1_PCWK_SHIFT, UAWT1_PCWK_MASK,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "a3000000.sewiaw");
	/* Enfowce was_apb_cwk */
	cwk_set_pawent(cwk, was_apb_cwk);

	cwk = cwk_wegistew_mux(NUWW, "uawt2_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_UAWT2_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "a4000000.sewiaw");
	/* Enfowce was_apb_cwk */
	cwk_set_pawent(cwk, was_apb_cwk);

	cwk = cwk_wegistew_mux(NUWW, "uawt3_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_UAWT3_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "a9100000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt4_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_UAWT4_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "a9200000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt5_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_UAWT5_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "60000000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt6_cwk", uawtx_pawents,
			AWWAY_SIZE(uawtx_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW320_EXT_CTWW_WEG, SPEAW320_UAWT6_PCWK_SHIFT,
			SPEAW320_UAWTX_PCWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "60100000.sewiaw");
}
#ewse
static inwine void speaw320_cwk_init(void __iomem *sb, stwuct cwk *wc) { }
#endif

void __init speaw3xx_cwk_init(void __iomem *misc_base, void __iomem *soc_config_base)
{
	stwuct cwk *cwk, *cwk1, *was_apb_cwk;

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_32k_cwk", NUWW, 0, 32000);
	cwk_wegistew_cwkdev(cwk, "osc_32k_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_24m_cwk", NUWW, 0, 24000000);
	cwk_wegistew_cwkdev(cwk, "osc_24m_cwk", NUWW);

	/* cwock dewived fwom 32 KHz osc cwk */
	cwk = cwk_wegistew_gate(NUWW, "wtc-speaw", "osc_32k_cwk", 0,
			PEWIP1_CWK_ENB, WTC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc900000.wtc");

	/* cwock dewived fwom 24 MHz osc cwk */
	cwk = cwk_wegistew_fixed_wate(NUWW, "pww3_cwk", "osc_24m_cwk", 0,
			48000000);
	cwk_wegistew_cwkdev(cwk, "pww3_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "wdt_cwk", "osc_24m_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc880000.wdt");

	cwk = cwk_wegistew_vco_pww("vco1_cwk", "pww1_cwk", NUWW,
			"osc_24m_cwk", 0, PWW1_CTW, PWW1_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco1_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww1_cwk", NUWW);

	cwk = cwk_wegistew_vco_pww("vco2_cwk", "pww2_cwk", NUWW,
			"osc_24m_cwk", 0, PWW2_CTW, PWW2_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco2_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww2_cwk", NUWW);

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

	cwk = cwk_wegistew_mux(NUWW, "uawt0_mcwk", uawt0_pawents,
			AWWAY_SIZE(uawt0_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, UAWT_CWK_SHIFT, UAWT_CWK_MASK, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "uawt0_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt0", "uawt0_mcwk",
			CWK_SET_WATE_PAWENT, PEWIP1_CWK_ENB, UAWT_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0000000.sewiaw");

	cwk = cwk_wegistew_aux("fiwda_syn_cwk", "fiwda_syn_gcwk", "pww1_cwk", 0,
			FIWDA_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "fiwda_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "fiwda_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "fiwda_mcwk", fiwda_pawents,
			AWWAY_SIZE(fiwda_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, FIWDA_CWK_SHIFT, FIWDA_CWK_MASK, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "fiwda_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "fiwda_cwk", "fiwda_mcwk",
			CWK_SET_WATE_PAWENT, PEWIP1_CWK_ENB, FIWDA_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fiwda");

	/* gpt cwocks */
	cwk_wegistew_gpt("gpt0_syn_cwk", "pww1_cwk", 0, PWSC0_CWK_CFG, gpt_wtbw,
			AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk = cwk_wegistew_mux(NUWW, "gpt0_cwk", gpt0_pawents,
			AWWAY_SIZE(gpt0_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT0_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt0");

	cwk_wegistew_gpt("gpt1_syn_cwk", "pww1_cwk", 0, PWSC1_CWK_CFG, gpt_wtbw,
			AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk = cwk_wegistew_mux(NUWW, "gpt1_mcwk", gpt1_pawents,
			AWWAY_SIZE(gpt1_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT1_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt1_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt1_cwk", "gpt1_mcwk",
			CWK_SET_WATE_PAWENT, PEWIP1_CWK_ENB, GPT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt1");

	cwk_wegistew_gpt("gpt2_syn_cwk", "pww1_cwk", 0, PWSC2_CWK_CFG, gpt_wtbw,
			AWWAY_SIZE(gpt_wtbw), &_wock);
	cwk = cwk_wegistew_mux(NUWW, "gpt2_mcwk", gpt2_pawents,
			AWWAY_SIZE(gpt2_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			PEWIP_CWK_CFG, GPT2_CWK_SHIFT, GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt2_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt2_cwk", "gpt2_mcwk",
			CWK_SET_WATE_PAWENT, PEWIP1_CWK_ENB, GPT2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt2");

	/* genewaw synths cwocks */
	cwk = cwk_wegistew_aux("gen0_syn_cwk", "gen0_syn_gcwk", "pww1_cwk",
			0, GEN0_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "gen0_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "gen0_syn_gcwk", NUWW);

	cwk = cwk_wegistew_aux("gen1_syn_cwk", "gen1_syn_gcwk", "pww1_cwk",
			0, GEN1_CWK_SYNT, NUWW, aux_wtbw, AWWAY_SIZE(aux_wtbw),
			&_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "gen1_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "gen1_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gen2_3_paw_cwk", gen2_3_pawents,
			AWWAY_SIZE(gen2_3_pawents), CWK_SET_WATE_NO_WEPAWENT,
			COWE_CWK_CFG, GEN_SYNTH2_3_CWK_SHIFT,
			GEN_SYNTH2_3_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gen2_3_paw_cwk", NUWW);

	cwk = cwk_wegistew_aux("gen2_syn_cwk", "gen2_syn_gcwk",
			"gen2_3_paw_cwk", 0, GEN2_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "gen2_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "gen2_syn_gcwk", NUWW);

	cwk = cwk_wegistew_aux("gen3_syn_cwk", "gen3_syn_gcwk",
			"gen2_3_paw_cwk", 0, GEN3_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "gen3_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "gen3_syn_gcwk", NUWW);

	/* cwock dewived fwom pww3 cwk */
	cwk = cwk_wegistew_gate(NUWW, "usbh_cwk", "pww3_cwk", 0, PEWIP1_CWK_ENB,
			USBH_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1800000.ehci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e1900000.ohci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e2100000.ohci");

	cwk = cwk_wegistew_fixed_factow(NUWW, "usbh.0_cwk", "usbh_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "usbh.0_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "usbh.1_cwk", "usbh_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "usbh.1_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "usbd_cwk", "pww3_cwk", 0, PEWIP1_CWK_ENB,
			USBD_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1100000.usbd");

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

	cwk = cwk_wegistew_gate(NUWW, "amem_cwk", "ahb_cwk", 0, AMEM_CWK_CFG,
			AMEM_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "amem_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "c3_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			C3_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "c3_cwk");

	cwk = cwk_wegistew_gate(NUWW, "dma_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			DMA_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc400000.dma");

	cwk = cwk_wegistew_gate(NUWW, "gmac_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			GMAC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0800000.eth");

	cwk = cwk_wegistew_gate(NUWW, "i2c0_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			I2C_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0180000.i2c");

	cwk = cwk_wegistew_gate(NUWW, "jpeg_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			JPEG_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "jpeg");

	cwk = cwk_wegistew_gate(NUWW, "smi_cwk", "ahb_cwk", 0, PEWIP1_CWK_ENB,
			SMI_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc000000.fwash");

	/* cwock dewived fwom apb cwk */
	cwk = cwk_wegistew_gate(NUWW, "adc_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			ADC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0080000.adc");

	cwk = cwk_wegistew_gate(NUWW, "gpio0_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			GPIO_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "fc980000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "ssp0_cwk", "apb_cwk", 0, PEWIP1_CWK_ENB,
			SSP_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0100000.spi");

	/* WAS cwk enabwe */
	cwk = cwk_wegistew_gate(NUWW, "was_ahb_cwk", "ahb_cwk", 0, WAS_CWK_ENB,
			WAS_AHB_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_ahb_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_apb_cwk", "apb_cwk", 0, WAS_CWK_ENB,
			WAS_APB_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_apb_cwk", NUWW);
	was_apb_cwk = cwk;

	cwk = cwk_wegistew_gate(NUWW, "was_32k_cwk", "osc_32k_cwk", 0,
			WAS_CWK_ENB, WAS_32K_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_32k_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_24m_cwk", "osc_24m_cwk", 0,
			WAS_CWK_ENB, WAS_24M_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_24m_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_pww1_cwk", "pww1_cwk", 0,
			WAS_CWK_ENB, WAS_PWW1_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_pww1_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_pww2_cwk", "pww2_cwk", 0,
			WAS_CWK_ENB, WAS_PWW2_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_pww2_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_pww3_cwk", "pww3_cwk", 0,
			WAS_CWK_ENB, WAS_48M_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "was_pww3_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_syn0_gcwk", "gen0_syn_gcwk",
			CWK_SET_WATE_PAWENT, WAS_CWK_ENB, WAS_SYNT0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_syn0_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_syn1_gcwk", "gen1_syn_gcwk",
			CWK_SET_WATE_PAWENT, WAS_CWK_ENB, WAS_SYNT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_syn1_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_syn2_gcwk", "gen2_syn_gcwk",
			CWK_SET_WATE_PAWENT, WAS_CWK_ENB, WAS_SYNT2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_syn2_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_syn3_gcwk", "gen3_syn_gcwk",
			CWK_SET_WATE_PAWENT, WAS_CWK_ENB, WAS_SYNT3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_syn3_gcwk", NUWW);

	if (of_machine_is_compatibwe("st,speaw300"))
		speaw300_cwk_init();
	ewse if (of_machine_is_compatibwe("st,speaw310"))
		speaw310_cwk_init();
	ewse if (of_machine_is_compatibwe("st,speaw320"))
		speaw320_cwk_init(soc_config_base, was_apb_cwk);
}
