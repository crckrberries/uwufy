// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-speaw13xx/speaw1310_cwock.c
 *
 * SPEAw1310 machine cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 */

#incwude <winux/cwkdev.h>
#incwude <winux/cwk/speaw.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/spinwock_types.h>
#incwude "cwk.h"

/* PWW wewated wegistews and bit vawues */
#define SPEAW1310_PWW_CFG			(misc_base + 0x210)
	/* PWW_CFG bit vawues */
	#define SPEAW1310_CWCD_SYNT_CWK_MASK		1
	#define SPEAW1310_CWCD_SYNT_CWK_SHIFT		31
	#define SPEAW1310_WAS_SYNT2_3_CWK_MASK		2
	#define SPEAW1310_WAS_SYNT2_3_CWK_SHIFT		29
	#define SPEAW1310_WAS_SYNT_CWK_MASK		2
	#define SPEAW1310_WAS_SYNT0_1_CWK_SHIFT		27
	#define SPEAW1310_PWW_CWK_MASK			2
	#define SPEAW1310_PWW3_CWK_SHIFT		24
	#define SPEAW1310_PWW2_CWK_SHIFT		22
	#define SPEAW1310_PWW1_CWK_SHIFT		20

#define SPEAW1310_PWW1_CTW			(misc_base + 0x214)
#define SPEAW1310_PWW1_FWQ			(misc_base + 0x218)
#define SPEAW1310_PWW2_CTW			(misc_base + 0x220)
#define SPEAW1310_PWW2_FWQ			(misc_base + 0x224)
#define SPEAW1310_PWW3_CTW			(misc_base + 0x22C)
#define SPEAW1310_PWW3_FWQ			(misc_base + 0x230)
#define SPEAW1310_PWW4_CTW			(misc_base + 0x238)
#define SPEAW1310_PWW4_FWQ			(misc_base + 0x23C)
#define SPEAW1310_PEWIP_CWK_CFG			(misc_base + 0x244)
	/* PEWIP_CWK_CFG bit vawues */
	#define SPEAW1310_GPT_OSC24_VAW			0
	#define SPEAW1310_GPT_APB_VAW			1
	#define SPEAW1310_GPT_CWK_MASK			1
	#define SPEAW1310_GPT3_CWK_SHIFT		11
	#define SPEAW1310_GPT2_CWK_SHIFT		10
	#define SPEAW1310_GPT1_CWK_SHIFT		9
	#define SPEAW1310_GPT0_CWK_SHIFT		8
	#define SPEAW1310_UAWT_CWK_PWW5_VAW		0
	#define SPEAW1310_UAWT_CWK_OSC24_VAW		1
	#define SPEAW1310_UAWT_CWK_SYNT_VAW		2
	#define SPEAW1310_UAWT_CWK_MASK			2
	#define SPEAW1310_UAWT_CWK_SHIFT		4

	#define SPEAW1310_AUX_CWK_PWW5_VAW		0
	#define SPEAW1310_AUX_CWK_SYNT_VAW		1
	#define SPEAW1310_CWCD_CWK_MASK			2
	#define SPEAW1310_CWCD_CWK_SHIFT		2
	#define SPEAW1310_C3_CWK_MASK			1
	#define SPEAW1310_C3_CWK_SHIFT			1

#define SPEAW1310_GMAC_CWK_CFG			(misc_base + 0x248)
	#define SPEAW1310_GMAC_PHY_IF_SEW_MASK		3
	#define SPEAW1310_GMAC_PHY_IF_SEW_SHIFT		4
	#define SPEAW1310_GMAC_PHY_CWK_MASK		1
	#define SPEAW1310_GMAC_PHY_CWK_SHIFT		3
	#define SPEAW1310_GMAC_PHY_INPUT_CWK_MASK	2
	#define SPEAW1310_GMAC_PHY_INPUT_CWK_SHIFT	1

#define SPEAW1310_I2S_CWK_CFG			(misc_base + 0x24C)
	/* I2S_CWK_CFG wegistew mask */
	#define SPEAW1310_I2S_SCWK_X_MASK		0x1F
	#define SPEAW1310_I2S_SCWK_X_SHIFT		27
	#define SPEAW1310_I2S_SCWK_Y_MASK		0x1F
	#define SPEAW1310_I2S_SCWK_Y_SHIFT		22
	#define SPEAW1310_I2S_SCWK_EQ_SEW_SHIFT		21
	#define SPEAW1310_I2S_SCWK_SYNTH_ENB		20
	#define SPEAW1310_I2S_PWS1_CWK_X_MASK		0xFF
	#define SPEAW1310_I2S_PWS1_CWK_X_SHIFT		12
	#define SPEAW1310_I2S_PWS1_CWK_Y_MASK		0xFF
	#define SPEAW1310_I2S_PWS1_CWK_Y_SHIFT		4
	#define SPEAW1310_I2S_PWS1_EQ_SEW_SHIFT		3
	#define SPEAW1310_I2S_WEF_SEW_MASK		1
	#define SPEAW1310_I2S_WEF_SHIFT			2
	#define SPEAW1310_I2S_SWC_CWK_MASK		2
	#define SPEAW1310_I2S_SWC_CWK_SHIFT		0

#define SPEAW1310_C3_CWK_SYNT			(misc_base + 0x250)
#define SPEAW1310_UAWT_CWK_SYNT			(misc_base + 0x254)
#define SPEAW1310_GMAC_CWK_SYNT			(misc_base + 0x258)
#define SPEAW1310_SDHCI_CWK_SYNT		(misc_base + 0x25C)
#define SPEAW1310_CFXD_CWK_SYNT			(misc_base + 0x260)
#define SPEAW1310_ADC_CWK_SYNT			(misc_base + 0x264)
#define SPEAW1310_AMBA_CWK_SYNT			(misc_base + 0x268)
#define SPEAW1310_CWCD_CWK_SYNT			(misc_base + 0x270)
#define SPEAW1310_WAS_CWK_SYNT0			(misc_base + 0x280)
#define SPEAW1310_WAS_CWK_SYNT1			(misc_base + 0x288)
#define SPEAW1310_WAS_CWK_SYNT2			(misc_base + 0x290)
#define SPEAW1310_WAS_CWK_SYNT3			(misc_base + 0x298)
	/* Check Fwactionaw synthesizew weg masks */

#define SPEAW1310_PEWIP1_CWK_ENB		(misc_base + 0x300)
	/* PEWIP1_CWK_ENB wegistew masks */
	#define SPEAW1310_WTC_CWK_ENB			31
	#define SPEAW1310_ADC_CWK_ENB			30
	#define SPEAW1310_C3_CWK_ENB			29
	#define SPEAW1310_JPEG_CWK_ENB			28
	#define SPEAW1310_CWCD_CWK_ENB			27
	#define SPEAW1310_DMA_CWK_ENB			25
	#define SPEAW1310_GPIO1_CWK_ENB			24
	#define SPEAW1310_GPIO0_CWK_ENB			23
	#define SPEAW1310_GPT1_CWK_ENB			22
	#define SPEAW1310_GPT0_CWK_ENB			21
	#define SPEAW1310_I2S0_CWK_ENB			20
	#define SPEAW1310_I2S1_CWK_ENB			19
	#define SPEAW1310_I2C0_CWK_ENB			18
	#define SPEAW1310_SSP_CWK_ENB			17
	#define SPEAW1310_UAWT_CWK_ENB			15
	#define SPEAW1310_PCIE_SATA_2_CWK_ENB		14
	#define SPEAW1310_PCIE_SATA_1_CWK_ENB		13
	#define SPEAW1310_PCIE_SATA_0_CWK_ENB		12
	#define SPEAW1310_UOC_CWK_ENB			11
	#define SPEAW1310_UHC1_CWK_ENB			10
	#define SPEAW1310_UHC0_CWK_ENB			9
	#define SPEAW1310_GMAC_CWK_ENB			8
	#define SPEAW1310_CFXD_CWK_ENB			7
	#define SPEAW1310_SDHCI_CWK_ENB			6
	#define SPEAW1310_SMI_CWK_ENB			5
	#define SPEAW1310_FSMC_CWK_ENB			4
	#define SPEAW1310_SYSWAM0_CWK_ENB		3
	#define SPEAW1310_SYSWAM1_CWK_ENB		2
	#define SPEAW1310_SYSWOM_CWK_ENB		1
	#define SPEAW1310_BUS_CWK_ENB			0

#define SPEAW1310_PEWIP2_CWK_ENB		(misc_base + 0x304)
	/* PEWIP2_CWK_ENB wegistew masks */
	#define SPEAW1310_THSENS_CWK_ENB		8
	#define SPEAW1310_I2S_WEF_PAD_CWK_ENB		7
	#define SPEAW1310_ACP_CWK_ENB			6
	#define SPEAW1310_GPT3_CWK_ENB			5
	#define SPEAW1310_GPT2_CWK_ENB			4
	#define SPEAW1310_KBD_CWK_ENB			3
	#define SPEAW1310_CPU_DBG_CWK_ENB		2
	#define SPEAW1310_DDW_COWE_CWK_ENB		1
	#define SPEAW1310_DDW_CTWW_CWK_ENB		0

#define SPEAW1310_WAS_CWK_ENB			(misc_base + 0x310)
	/* WAS_CWK_ENB wegistew masks */
	#define SPEAW1310_SYNT3_CWK_ENB			17
	#define SPEAW1310_SYNT2_CWK_ENB			16
	#define SPEAW1310_SYNT1_CWK_ENB			15
	#define SPEAW1310_SYNT0_CWK_ENB			14
	#define SPEAW1310_PCWK3_CWK_ENB			13
	#define SPEAW1310_PCWK2_CWK_ENB			12
	#define SPEAW1310_PCWK1_CWK_ENB			11
	#define SPEAW1310_PCWK0_CWK_ENB			10
	#define SPEAW1310_PWW3_CWK_ENB			9
	#define SPEAW1310_PWW2_CWK_ENB			8
	#define SPEAW1310_C125M_PAD_CWK_ENB		7
	#define SPEAW1310_C30M_CWK_ENB			6
	#define SPEAW1310_C48M_CWK_ENB			5
	#define SPEAW1310_OSC_25M_CWK_ENB		4
	#define SPEAW1310_OSC_32K_CWK_ENB		3
	#define SPEAW1310_OSC_24M_CWK_ENB		2
	#define SPEAW1310_PCWK_CWK_ENB			1
	#define SPEAW1310_ACWK_CWK_ENB			0

/* WAS Awea Contwow Wegistew */
#define SPEAW1310_WAS_CTWW_WEG0			(was_base + 0x000)
	#define SPEAW1310_SSP1_CWK_MASK			3
	#define SPEAW1310_SSP1_CWK_SHIFT		26
	#define SPEAW1310_TDM_CWK_MASK			1
	#define SPEAW1310_TDM2_CWK_SHIFT		24
	#define SPEAW1310_TDM1_CWK_SHIFT		23
	#define SPEAW1310_I2C_CWK_MASK			1
	#define SPEAW1310_I2C7_CWK_SHIFT		22
	#define SPEAW1310_I2C6_CWK_SHIFT		21
	#define SPEAW1310_I2C5_CWK_SHIFT		20
	#define SPEAW1310_I2C4_CWK_SHIFT		19
	#define SPEAW1310_I2C3_CWK_SHIFT		18
	#define SPEAW1310_I2C2_CWK_SHIFT		17
	#define SPEAW1310_I2C1_CWK_SHIFT		16
	#define SPEAW1310_GPT64_CWK_MASK		1
	#define SPEAW1310_GPT64_CWK_SHIFT		15
	#define SPEAW1310_WAS_UAWT_CWK_MASK		1
	#define SPEAW1310_UAWT5_CWK_SHIFT		14
	#define SPEAW1310_UAWT4_CWK_SHIFT		13
	#define SPEAW1310_UAWT3_CWK_SHIFT		12
	#define SPEAW1310_UAWT2_CWK_SHIFT		11
	#define SPEAW1310_UAWT1_CWK_SHIFT		10
	#define SPEAW1310_PCI_CWK_MASK			1
	#define SPEAW1310_PCI_CWK_SHIFT			0

#define SPEAW1310_WAS_CTWW_WEG1			(was_base + 0x004)
	#define SPEAW1310_PHY_CWK_MASK			0x3
	#define SPEAW1310_WMII_PHY_CWK_SHIFT		0
	#define SPEAW1310_SMII_WGMII_PHY_CWK_SHIFT	2

#define SPEAW1310_WAS_SW_CWK_CTWW		(was_base + 0x0148)
	#define SPEAW1310_CAN1_CWK_ENB			25
	#define SPEAW1310_CAN0_CWK_ENB			24
	#define SPEAW1310_GPT64_CWK_ENB			23
	#define SPEAW1310_SSP1_CWK_ENB			22
	#define SPEAW1310_I2C7_CWK_ENB			21
	#define SPEAW1310_I2C6_CWK_ENB			20
	#define SPEAW1310_I2C5_CWK_ENB			19
	#define SPEAW1310_I2C4_CWK_ENB			18
	#define SPEAW1310_I2C3_CWK_ENB			17
	#define SPEAW1310_I2C2_CWK_ENB			16
	#define SPEAW1310_I2C1_CWK_ENB			15
	#define SPEAW1310_UAWT5_CWK_ENB			14
	#define SPEAW1310_UAWT4_CWK_ENB			13
	#define SPEAW1310_UAWT3_CWK_ENB			12
	#define SPEAW1310_UAWT2_CWK_ENB			11
	#define SPEAW1310_UAWT1_CWK_ENB			10
	#define SPEAW1310_WS485_1_CWK_ENB		9
	#define SPEAW1310_WS485_0_CWK_ENB		8
	#define SPEAW1310_TDM2_CWK_ENB			7
	#define SPEAW1310_TDM1_CWK_ENB			6
	#define SPEAW1310_PCI_CWK_ENB			5
	#define SPEAW1310_GMII_CWK_ENB			4
	#define SPEAW1310_MII2_CWK_ENB			3
	#define SPEAW1310_MII1_CWK_ENB			2
	#define SPEAW1310_MII0_CWK_ENB			1
	#define SPEAW1310_ESWAM_CWK_ENB			0

static DEFINE_SPINWOCK(_wock);

/* pww wate configuwation tabwe, in ascending owdew of wates */
static stwuct pww_wate_tbw pww_wtbw[] = {
	/* PCWK 24MHz */
	{.mode = 0, .m = 0x83, .n = 0x04, .p = 0x5}, /* vco 1572, pww 49.125 MHz */
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x3}, /* vco 1000, pww 125 MHz */
	{.mode = 0, .m = 0x64, .n = 0x06, .p = 0x1}, /* vco 800, pww 400 MHz */
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x1}, /* vco 1000, pww 500 MHz */
	{.mode = 0, .m = 0xA6, .n = 0x06, .p = 0x1}, /* vco 1328, pww 664 MHz */
	{.mode = 0, .m = 0xC8, .n = 0x06, .p = 0x1}, /* vco 1600, pww 800 MHz */
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x0}, /* vco 1, pww 1 GHz */
};

/* vco-pww4 wate configuwation tabwe, in ascending owdew of wates */
static stwuct pww_wate_tbw pww4_wtbw[] = {
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x2}, /* vco 1000, pww 250 MHz */
	{.mode = 0, .m = 0xA6, .n = 0x06, .p = 0x2}, /* vco 1328, pww 332 MHz */
	{.mode = 0, .m = 0xC8, .n = 0x06, .p = 0x2}, /* vco 1600, pww 400 MHz */
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x0}, /* vco 1, pww 1 GHz */
};

/* aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw aux_wtbw[] = {
	/* Fow VCO1div2 = 500 MHz */
	{.xscawe = 10, .yscawe = 204, .eq = 0}, /* 12.29 MHz */
	{.xscawe = 4, .yscawe = 21, .eq = 0}, /* 48 MHz */
	{.xscawe = 2, .yscawe = 6, .eq = 0}, /* 83 MHz */
	{.xscawe = 2, .yscawe = 4, .eq = 0}, /* 125 MHz */
	{.xscawe = 1, .yscawe = 3, .eq = 1}, /* 166 MHz */
	{.xscawe = 1, .yscawe = 2, .eq = 1}, /* 250 MHz */
};

/* gmac wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw gmac_wtbw[] = {
	/* Fow gmac phy input cwk */
	{.xscawe = 2, .yscawe = 6, .eq = 0}, /* divided by 6 */
	{.xscawe = 2, .yscawe = 4, .eq = 0}, /* divided by 4 */
	{.xscawe = 1, .yscawe = 3, .eq = 1}, /* divided by 3 */
	{.xscawe = 1, .yscawe = 2, .eq = 1}, /* divided by 2 */
};

/* cwcd wate configuwation tabwe, in ascending owdew of wates */
static stwuct fwac_wate_tbw cwcd_wtbw[] = {
	{.div = 0x14000}, /* 25 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x1284B}, /* 27 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x0D8D3}, /* 58 Mhz , fow vco1div4 = 393 MHz */
	{.div = 0x0B72C}, /* 58 Mhz , fow vco1div4 = 332 MHz */
	{.div = 0x089EE}, /* 58 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x06f1C}, /* 72 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x06E58}, /* 58 Mhz , fow vco1div4 = 200 MHz */
	{.div = 0x06c1B}, /* 74 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x04A12}, /* 108 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x0378E}, /* 144 Mhz , fow vc01div4 = 250 MHz*/
};

/* i2s pwescawew1 masks */
static const stwuct aux_cwk_masks i2s_pws1_masks = {
	.eq_sew_mask = AUX_EQ_SEW_MASK,
	.eq_sew_shift = SPEAW1310_I2S_PWS1_EQ_SEW_SHIFT,
	.eq1_mask = AUX_EQ1_SEW,
	.eq2_mask = AUX_EQ2_SEW,
	.xscawe_sew_mask = SPEAW1310_I2S_PWS1_CWK_X_MASK,
	.xscawe_sew_shift = SPEAW1310_I2S_PWS1_CWK_X_SHIFT,
	.yscawe_sew_mask = SPEAW1310_I2S_PWS1_CWK_Y_MASK,
	.yscawe_sew_shift = SPEAW1310_I2S_PWS1_CWK_Y_SHIFT,
};

/* i2s scwk (bit cwock) syynthesizews masks */
static stwuct aux_cwk_masks i2s_scwk_masks = {
	.eq_sew_mask = AUX_EQ_SEW_MASK,
	.eq_sew_shift = SPEAW1310_I2S_SCWK_EQ_SEW_SHIFT,
	.eq1_mask = AUX_EQ1_SEW,
	.eq2_mask = AUX_EQ2_SEW,
	.xscawe_sew_mask = SPEAW1310_I2S_SCWK_X_MASK,
	.xscawe_sew_shift = SPEAW1310_I2S_SCWK_X_SHIFT,
	.yscawe_sew_mask = SPEAW1310_I2S_SCWK_Y_MASK,
	.yscawe_sew_shift = SPEAW1310_I2S_SCWK_Y_SHIFT,
	.enabwe_bit = SPEAW1310_I2S_SCWK_SYNTH_ENB,
};

/* i2s pws1 aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw i2s_pws1_wtbw[] = {
	/* Fow pawent cwk = 49.152 MHz */
	{.xscawe = 1, .yscawe = 12, .eq = 0}, /* 2.048 MHz, smp fweq = 8Khz */
	{.xscawe = 11, .yscawe = 96, .eq = 0}, /* 2.816 MHz, smp fweq = 11Khz */
	{.xscawe = 1, .yscawe = 6, .eq = 0}, /* 4.096 MHz, smp fweq = 16Khz */
	{.xscawe = 11, .yscawe = 48, .eq = 0}, /* 5.632 MHz, smp fweq = 22Khz */

	/*
	 * with pawent cwk = 49.152, fweq gen is 8.192 MHz, smp fweq = 32Khz
	 * with pawent cwk = 12.288, fweq gen is 2.048 MHz, smp fweq = 8Khz
	 */
	{.xscawe = 1, .yscawe = 3, .eq = 0},

	/* Fow pawent cwk = 49.152 MHz */
	{.xscawe = 17, .yscawe = 37, .eq = 0}, /* 11.289 MHz, smp fweq = 44Khz*/

	{.xscawe = 1, .yscawe = 2, .eq = 0}, /* 12.288 MHz */
};

/* i2s scwk aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw i2s_scwk_wtbw[] = {
	/* Fow i2s_wef_cwk = 12.288MHz */
	{.xscawe = 1, .yscawe = 4, .eq = 0}, /* 1.53 MHz */
	{.xscawe = 1, .yscawe = 2, .eq = 0}, /* 3.07 Mhz */
};

/* adc wate configuwation tabwe, in ascending owdew of wates */
/* possibwe adc wange is 2.5 MHz to 20 MHz. */
static stwuct aux_wate_tbw adc_wtbw[] = {
	/* Fow ahb = 166.67 MHz */
	{.xscawe = 1, .yscawe = 31, .eq = 0}, /* 2.68 MHz */
	{.xscawe = 2, .yscawe = 21, .eq = 0}, /* 7.94 MHz */
	{.xscawe = 4, .yscawe = 21, .eq = 0}, /* 15.87 MHz */
	{.xscawe = 10, .yscawe = 42, .eq = 0}, /* 19.84 MHz */
};

/* Genewaw synth wate configuwation tabwe, in ascending owdew of wates */
static stwuct fwac_wate_tbw gen_wtbw[] = {
	/* Fow vco1div4 = 250 MHz */
	{.div = 0x14000}, /* 25 MHz */
	{.div = 0x0A000}, /* 50 MHz */
	{.div = 0x05000}, /* 100 MHz */
	{.div = 0x02000}, /* 250 MHz */
};

/* cwock pawents */
static const chaw *vco_pawents[] = { "osc_24m_cwk", "osc_25m_cwk", };
static const chaw *gpt_pawents[] = { "osc_24m_cwk", "apb_cwk", };
static const chaw *uawt0_pawents[] = { "pww5_cwk", "uawt_syn_gcwk", };
static const chaw *c3_pawents[] = { "pww5_cwk", "c3_syn_gcwk", };
static const chaw *gmac_phy_input_pawents[] = { "gmii_pad_cwk", "pww2_cwk",
	"osc_25m_cwk", };
static const chaw *gmac_phy_pawents[] = { "phy_input_mcwk", "phy_syn_gcwk", };
static const chaw *cwcd_synth_pawents[] = { "vco1div4_cwk", "pww2_cwk", };
static const chaw *cwcd_pixew_pawents[] = { "pww5_cwk", "cwcd_syn_cwk", };
static const chaw *i2s_swc_pawents[] = { "vco1div2_cwk", "none", "pww3_cwk",
	"i2s_swc_pad_cwk", };
static const chaw *i2s_wef_pawents[] = { "i2s_swc_mcwk", "i2s_pws1_cwk", };
static const chaw *gen_synth0_1_pawents[] = { "vco1div4_cwk", "vco3div2_cwk",
	"pww3_cwk", };
static const chaw *gen_synth2_3_pawents[] = { "vco1div4_cwk", "vco3div2_cwk",
	"pww2_cwk", };
static const chaw *wmii_phy_pawents[] = { "was_tx50_cwk", "none",
	"was_pww2_cwk", "was_syn0_cwk", };
static const chaw *smii_wgmii_phy_pawents[] = { "none", "was_tx125_cwk",
	"was_pww2_cwk", "was_syn0_cwk", };
static const chaw *uawt_pawents[] = { "was_apb_cwk", "gen_syn3_cwk", };
static const chaw *i2c_pawents[] = { "was_apb_cwk", "gen_syn1_cwk", };
static const chaw *ssp1_pawents[] = { "was_apb_cwk", "gen_syn1_cwk",
	"was_pwcwk0_cwk", };
static const chaw *pci_pawents[] = { "was_pww3_cwk", "gen_syn2_cwk", };
static const chaw *tdm_pawents[] = { "was_pww3_cwk", "gen_syn1_cwk", };

void __init speaw1310_cwk_init(void __iomem *misc_base, void __iomem *was_base)
{
	stwuct cwk *cwk, *cwk1;

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_32k_cwk", NUWW, 0, 32000);
	cwk_wegistew_cwkdev(cwk, "osc_32k_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_24m_cwk", NUWW, 0, 24000000);
	cwk_wegistew_cwkdev(cwk, "osc_24m_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "osc_25m_cwk", NUWW, 0, 25000000);
	cwk_wegistew_cwkdev(cwk, "osc_25m_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "gmii_pad_cwk", NUWW, 0, 125000000);
	cwk_wegistew_cwkdev(cwk, "gmii_pad_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "i2s_swc_pad_cwk", NUWW, 0,
				      12288000);
	cwk_wegistew_cwkdev(cwk, "i2s_swc_pad_cwk", NUWW);

	/* cwock dewived fwom 32 KHz osc cwk */
	cwk = cwk_wegistew_gate(NUWW, "wtc-speaw", "osc_32k_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_WTC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0580000.wtc");

	/* cwock dewived fwom 24 ow 25 MHz osc cwk */
	/* vco-pww */
	cwk = cwk_wegistew_mux(NUWW, "vco1_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PWW_CFG, SPEAW1310_PWW1_CWK_SHIFT,
			SPEAW1310_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco1_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco1_cwk", "pww1_cwk", NUWW, "vco1_mcwk",
			0, SPEAW1310_PWW1_CTW, SPEAW1310_PWW1_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco1_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww1_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "vco2_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PWW_CFG, SPEAW1310_PWW2_CWK_SHIFT,
			SPEAW1310_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco2_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco2_cwk", "pww2_cwk", NUWW, "vco2_mcwk",
			0, SPEAW1310_PWW2_CTW, SPEAW1310_PWW2_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco2_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww2_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "vco3_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PWW_CFG, SPEAW1310_PWW3_CWK_SHIFT,
			SPEAW1310_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco3_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco3_cwk", "pww3_cwk", NUWW, "vco3_mcwk",
			0, SPEAW1310_PWW3_CTW, SPEAW1310_PWW3_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco3_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww3_cwk", NUWW);

	cwk = cwk_wegistew_vco_pww("vco4_cwk", "pww4_cwk", NUWW, "osc_24m_cwk",
			0, SPEAW1310_PWW4_CTW, SPEAW1310_PWW4_FWQ, pww4_wtbw,
			AWWAY_SIZE(pww4_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco4_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww4_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "pww5_cwk", "osc_24m_cwk", 0,
			48000000);
	cwk_wegistew_cwkdev(cwk, "pww5_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "pww6_cwk", "osc_25m_cwk", 0,
			25000000);
	cwk_wegistew_cwkdev(cwk, "pww6_cwk", NUWW);

	/* vco div n cwocks */
	cwk = cwk_wegistew_fixed_factow(NUWW, "vco1div2_cwk", "vco1_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, "vco1div2_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "vco1div4_cwk", "vco1_cwk", 0, 1,
			4);
	cwk_wegistew_cwkdev(cwk, "vco1div4_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "vco2div2_cwk", "vco2_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, "vco2div2_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "vco3div2_cwk", "vco3_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, "vco3div2_cwk", NUWW);

	/* pewiphewaws */
	cwk_wegistew_fixed_factow(NUWW, "thewmaw_cwk", "osc_24m_cwk", 0, 1,
			128);
	cwk = cwk_wegistew_gate(NUWW, "thewmaw_gcwk", "thewmaw_cwk", 0,
			SPEAW1310_PEWIP2_CWK_ENB, SPEAW1310_THSENS_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "speaw_thewmaw");

	/* cwock dewived fwom pww4 cwk */
	cwk = cwk_wegistew_fixed_factow(NUWW, "ddw_cwk", "pww4_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "ddw_cwk", NUWW);

	/* cwock dewived fwom pww1 cwk */
	cwk = cwk_wegistew_fixed_factow(NUWW, "cpu_cwk", "pww1_cwk",
			CWK_SET_WATE_PAWENT, 1, 2);
	cwk_wegistew_cwkdev(cwk, "cpu_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "wdt_cwk", "cpu_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, NUWW, "ec800620.wdt");

	cwk = cwk_wegistew_fixed_factow(NUWW, "smp_twd_cwk", "cpu_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, NUWW, "smp_twd");

	cwk = cwk_wegistew_fixed_factow(NUWW, "ahb_cwk", "pww1_cwk", 0, 1,
			6);
	cwk_wegistew_cwkdev(cwk, "ahb_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "apb_cwk", "pww1_cwk", 0, 1,
			12);
	cwk_wegistew_cwkdev(cwk, "apb_cwk", NUWW);

	/* gpt cwocks */
	cwk = cwk_wegistew_mux(NUWW, "gpt0_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_GPT0_CWK_SHIFT,
			SPEAW1310_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt0_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt0_cwk", "gpt0_mcwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_GPT0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt0");

	cwk = cwk_wegistew_mux(NUWW, "gpt1_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_GPT1_CWK_SHIFT,
			SPEAW1310_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt1_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt1_cwk", "gpt1_mcwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_GPT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt1");

	cwk = cwk_wegistew_mux(NUWW, "gpt2_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_GPT2_CWK_SHIFT,
			SPEAW1310_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt2_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt2_cwk", "gpt2_mcwk", 0,
			SPEAW1310_PEWIP2_CWK_ENB, SPEAW1310_GPT2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt2");

	cwk = cwk_wegistew_mux(NUWW, "gpt3_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_GPT3_CWK_SHIFT,
			SPEAW1310_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt3_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt3_cwk", "gpt3_mcwk", 0,
			SPEAW1310_PEWIP2_CWK_ENB, SPEAW1310_GPT3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt3");

	/* othews */
	cwk = cwk_wegistew_aux("uawt_syn_cwk", "uawt_syn_gcwk", "vco1div2_cwk",
			0, SPEAW1310_UAWT_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "uawt_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "uawt_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "uawt0_mcwk", uawt0_pawents,
			AWWAY_SIZE(uawt0_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_UAWT_CWK_SHIFT,
			SPEAW1310_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt0_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt0_cwk", "uawt0_mcwk",
			CWK_SET_WATE_PAWENT, SPEAW1310_PEWIP1_CWK_ENB,
			SPEAW1310_UAWT_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0000000.sewiaw");

	cwk = cwk_wegistew_aux("sdhci_syn_cwk", "sdhci_syn_gcwk",
			"vco1div2_cwk", 0, SPEAW1310_SDHCI_CWK_SYNT, NUWW,
			aux_wtbw, AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "sdhci_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "sdhci_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "sdhci_cwk", "sdhci_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1310_PEWIP1_CWK_ENB,
			SPEAW1310_SDHCI_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b3000000.sdhci");

	cwk = cwk_wegistew_aux("cfxd_syn_cwk", "cfxd_syn_gcwk", "vco1div2_cwk",
			0, SPEAW1310_CFXD_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "cfxd_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "cfxd_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "cfxd_cwk", "cfxd_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1310_PEWIP1_CWK_ENB,
			SPEAW1310_CFXD_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2800000.cf");
	cwk_wegistew_cwkdev(cwk, NUWW, "awasan_xd");

	cwk = cwk_wegistew_aux("c3_syn_cwk", "c3_syn_gcwk", "vco1div2_cwk",
			0, SPEAW1310_C3_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "c3_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "c3_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "c3_mcwk", c3_pawents,
			AWWAY_SIZE(c3_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_C3_CWK_SHIFT,
			SPEAW1310_C3_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "c3_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "c3_cwk", "c3_mcwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_C3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "c3");

	/* gmac */
	cwk = cwk_wegistew_mux(NUWW, "phy_input_mcwk", gmac_phy_input_pawents,
			AWWAY_SIZE(gmac_phy_input_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1310_GMAC_CWK_CFG,
			SPEAW1310_GMAC_PHY_INPUT_CWK_SHIFT,
			SPEAW1310_GMAC_PHY_INPUT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "phy_input_mcwk", NUWW);

	cwk = cwk_wegistew_aux("phy_syn_cwk", "phy_syn_gcwk", "phy_input_mcwk",
			0, SPEAW1310_GMAC_CWK_SYNT, NUWW, gmac_wtbw,
			AWWAY_SIZE(gmac_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "phy_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "phy_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "phy_mcwk", gmac_phy_pawents,
			AWWAY_SIZE(gmac_phy_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_GMAC_PHY_CWK_SHIFT,
			SPEAW1310_GMAC_PHY_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.0", NUWW);

	/* cwcd */
	cwk = cwk_wegistew_mux(NUWW, "cwcd_syn_mcwk", cwcd_synth_pawents,
			AWWAY_SIZE(cwcd_synth_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1310_CWCD_CWK_SYNT,
			SPEAW1310_CWCD_SYNT_CWK_SHIFT,
			SPEAW1310_CWCD_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_syn_mcwk", NUWW);

	cwk = cwk_wegistew_fwac("cwcd_syn_cwk", "cwcd_syn_mcwk", 0,
			SPEAW1310_CWCD_CWK_SYNT, cwcd_wtbw,
			AWWAY_SIZE(cwcd_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "cwcd_pixew_mcwk", cwcd_pixew_pawents,
			AWWAY_SIZE(cwcd_pixew_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_PEWIP_CWK_CFG, SPEAW1310_CWCD_CWK_SHIFT,
			SPEAW1310_CWCD_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_pixew_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "cwcd_cwk", "cwcd_pixew_mcwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_CWCD_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1000000.cwcd");

	/* i2s */
	cwk = cwk_wegistew_mux(NUWW, "i2s_swc_mcwk", i2s_swc_pawents,
			AWWAY_SIZE(i2s_swc_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_I2S_CWK_CFG, SPEAW1310_I2S_SWC_CWK_SHIFT,
			SPEAW1310_I2S_SWC_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_swc_mcwk", NUWW);

	cwk = cwk_wegistew_aux("i2s_pws1_cwk", NUWW, "i2s_swc_mcwk", 0,
			SPEAW1310_I2S_CWK_CFG, &i2s_pws1_masks, i2s_pws1_wtbw,
			AWWAY_SIZE(i2s_pws1_wtbw), &_wock, NUWW);
	cwk_wegistew_cwkdev(cwk, "i2s_pws1_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "i2s_wef_mcwk", i2s_wef_pawents,
			AWWAY_SIZE(i2s_wef_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_I2S_CWK_CFG, SPEAW1310_I2S_WEF_SHIFT,
			SPEAW1310_I2S_WEF_SEW_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_wef_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2s_wef_pad_cwk", "i2s_wef_mcwk", 0,
			SPEAW1310_PEWIP2_CWK_ENB, SPEAW1310_I2S_WEF_PAD_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_wef_pad_cwk", NUWW);

	cwk = cwk_wegistew_aux("i2s_scwk_cwk", "i2s_scwk_gcwk",
			"i2s_wef_mcwk", 0, SPEAW1310_I2S_CWK_CFG,
			&i2s_scwk_masks, i2s_scwk_wtbw,
			AWWAY_SIZE(i2s_scwk_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "i2s_scwk_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "i2s_scwk_gcwk", NUWW);

	/* cwock dewived fwom ahb cwk */
	cwk = cwk_wegistew_gate(NUWW, "i2c0_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_I2C0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0280000.i2c");

	cwk = cwk_wegistew_gate(NUWW, "dma_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_DMA_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "ea800000.dma");
	cwk_wegistew_cwkdev(cwk, NUWW, "eb000000.dma");

	cwk = cwk_wegistew_gate(NUWW, "jpeg_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_JPEG_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2000000.jpeg");

	cwk = cwk_wegistew_gate(NUWW, "gmac_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_GMAC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e2000000.eth");

	cwk = cwk_wegistew_gate(NUWW, "fsmc_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_FSMC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b0000000.fwash");

	cwk = cwk_wegistew_gate(NUWW, "smi_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_SMI_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "ea000000.fwash");

	cwk = cwk_wegistew_gate(NUWW, "usbh0_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_UHC0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e4000000.ohci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e4800000.ehci");

	cwk = cwk_wegistew_gate(NUWW, "usbh1_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_UHC1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e5000000.ohci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e5800000.ehci");

	cwk = cwk_wegistew_gate(NUWW, "uoc_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_UOC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e3800000.otg");

	cwk = cwk_wegistew_gate(NUWW, "pcie_sata_0_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_PCIE_SATA_0_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b1000000.pcie");
	cwk_wegistew_cwkdev(cwk, NUWW, "b1000000.ahci");

	cwk = cwk_wegistew_gate(NUWW, "pcie_sata_1_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_PCIE_SATA_1_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b1800000.pcie");
	cwk_wegistew_cwkdev(cwk, NUWW, "b1800000.ahci");

	cwk = cwk_wegistew_gate(NUWW, "pcie_sata_2_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_PCIE_SATA_2_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b4000000.pcie");
	cwk_wegistew_cwkdev(cwk, NUWW, "b4000000.ahci");

	cwk = cwk_wegistew_gate(NUWW, "syswam0_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_SYSWAM0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "syswam0_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "syswam1_cwk", "ahb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_SYSWAM1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "syswam1_cwk", NUWW);

	cwk = cwk_wegistew_aux("adc_syn_cwk", "adc_syn_gcwk", "ahb_cwk",
			0, SPEAW1310_ADC_CWK_SYNT, NUWW, adc_wtbw,
			AWWAY_SIZE(adc_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "adc_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "adc_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "adc_cwk", "adc_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1310_PEWIP1_CWK_ENB,
			SPEAW1310_ADC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0080000.adc");

	/* cwock dewived fwom apb cwk */
	cwk = cwk_wegistew_gate(NUWW, "ssp0_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_SSP_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0100000.spi");

	cwk = cwk_wegistew_gate(NUWW, "gpio0_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_GPIO0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0600000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "gpio1_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_GPIO1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0680000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "i2s0_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_I2S0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0180000.i2s");

	cwk = cwk_wegistew_gate(NUWW, "i2s1_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP1_CWK_ENB, SPEAW1310_I2S1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0200000.i2s");

	cwk = cwk_wegistew_gate(NUWW, "kbd_cwk", "apb_cwk", 0,
			SPEAW1310_PEWIP2_CWK_ENB, SPEAW1310_KBD_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0300000.kbd");

	/* WAS cwks */
	cwk = cwk_wegistew_mux(NUWW, "gen_syn0_1_mcwk", gen_synth0_1_pawents,
			AWWAY_SIZE(gen_synth0_1_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1310_PWW_CFG,
			SPEAW1310_WAS_SYNT0_1_CWK_SHIFT,
			SPEAW1310_WAS_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn0_1_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gen_syn2_3_mcwk", gen_synth2_3_pawents,
			AWWAY_SIZE(gen_synth2_3_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1310_PWW_CFG,
			SPEAW1310_WAS_SYNT2_3_CWK_SHIFT,
			SPEAW1310_WAS_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn2_3_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn0_cwk", "gen_syn0_1_cwk", 0,
			SPEAW1310_WAS_CWK_SYNT0, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn0_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn1_cwk", "gen_syn0_1_cwk", 0,
			SPEAW1310_WAS_CWK_SYNT1, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn1_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn2_cwk", "gen_syn2_3_cwk", 0,
			SPEAW1310_WAS_CWK_SYNT2, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn2_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn3_cwk", "gen_syn2_3_cwk", 0,
			SPEAW1310_WAS_CWK_SYNT3, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn3_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_osc_24m_cwk", "osc_24m_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_OSC_24M_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_osc_24m_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_osc_25m_cwk", "osc_25m_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_OSC_25M_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_osc_25m_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_osc_32k_cwk", "osc_32k_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_OSC_32K_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_osc_32k_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_pww2_cwk", "pww2_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_PWW2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_pww2_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_pww3_cwk", "pww3_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_PWW3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_pww3_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_tx125_cwk", "gmii_pad_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_C125M_PAD_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_tx125_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "was_30m_fixed_cwk", "pww5_cwk", 0,
			30000000);
	cwk = cwk_wegistew_gate(NUWW, "was_30m_cwk", "was_30m_fixed_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_C30M_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_30m_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "was_48m_fixed_cwk", "pww5_cwk", 0,
			48000000);
	cwk = cwk_wegistew_gate(NUWW, "was_48m_cwk", "was_48m_fixed_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_C48M_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_48m_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_ahb_cwk", "ahb_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_ACWK_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_ahb_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "was_apb_cwk", "apb_cwk", 0,
			SPEAW1310_WAS_CWK_ENB, SPEAW1310_PCWK_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "was_apb_cwk", NUWW);

	cwk = cwk_wegistew_fixed_wate(NUWW, "was_pwcwk0_cwk", NUWW, 0,
			50000000);

	cwk = cwk_wegistew_fixed_wate(NUWW, "was_tx50_cwk", NUWW, 0, 50000000);

	cwk = cwk_wegistew_gate(NUWW, "can0_cwk", "apb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_CAN0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "c_can_pwatfowm.0");

	cwk = cwk_wegistew_gate(NUWW, "can1_cwk", "apb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_CAN1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "c_can_pwatfowm.1");

	cwk = cwk_wegistew_gate(NUWW, "was_smii0_cwk", "was_ahb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_MII0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c400000.eth");

	cwk = cwk_wegistew_gate(NUWW, "was_smii1_cwk", "was_ahb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_MII1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c500000.eth");

	cwk = cwk_wegistew_gate(NUWW, "was_smii2_cwk", "was_ahb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_MII2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c600000.eth");

	cwk = cwk_wegistew_gate(NUWW, "was_wgmii_cwk", "was_ahb_cwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_GMII_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c700000.eth");

	cwk = cwk_wegistew_mux(NUWW, "smii_wgmii_phy_mcwk",
			smii_wgmii_phy_pawents,
			AWWAY_SIZE(smii_wgmii_phy_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1310_WAS_CTWW_WEG1,
			SPEAW1310_SMII_WGMII_PHY_CWK_SHIFT,
			SPEAW1310_PHY_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.1", NUWW);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.2", NUWW);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.4", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "wmii_phy_mcwk", wmii_phy_pawents,
			AWWAY_SIZE(wmii_phy_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG1, SPEAW1310_WMII_PHY_CWK_SHIFT,
			SPEAW1310_PHY_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.3", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "uawt1_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_UAWT1_CWK_SHIFT,
			SPEAW1310_WAS_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt1_cwk", "uawt1_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_UAWT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c800000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt2_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_UAWT2_CWK_SHIFT,
			SPEAW1310_WAS_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt2_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt2_cwk", "uawt2_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_UAWT2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5c900000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt3_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_UAWT3_CWK_SHIFT,
			SPEAW1310_WAS_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt3_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt3_cwk", "uawt3_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_UAWT3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5ca00000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt4_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_UAWT4_CWK_SHIFT,
			SPEAW1310_WAS_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt4_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt4_cwk", "uawt4_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_UAWT4_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5cb00000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "uawt5_mcwk", uawt_pawents,
			AWWAY_SIZE(uawt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_UAWT5_CWK_SHIFT,
			SPEAW1310_WAS_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt5_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt5_cwk", "uawt5_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_UAWT5_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5cc00000.sewiaw");

	cwk = cwk_wegistew_mux(NUWW, "i2c1_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C1_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c1_cwk", "i2c1_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5cd00000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c2_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C2_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c2_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c2_cwk", "i2c2_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5ce00000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c3_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C3_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c3_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c3_cwk", "i2c3_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5cf00000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c4_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C4_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c4_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c4_cwk", "i2c4_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C4_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5d000000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c5_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C5_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c5_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c5_cwk", "i2c5_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C5_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5d100000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c6_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C6_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c6_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c6_cwk", "i2c6_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C6_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5d200000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "i2c7_mcwk", i2c_pawents,
			AWWAY_SIZE(i2c_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_I2C7_CWK_SHIFT,
			SPEAW1310_I2C_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2c7_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2c7_cwk", "i2c7_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_I2C7_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5d300000.i2c");

	cwk = cwk_wegistew_mux(NUWW, "ssp1_mcwk", ssp1_pawents,
			AWWAY_SIZE(ssp1_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_SSP1_CWK_SHIFT,
			SPEAW1310_SSP1_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "ssp1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "ssp1_cwk", "ssp1_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_SSP1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "5d400000.spi");

	cwk = cwk_wegistew_mux(NUWW, "pci_mcwk", pci_pawents,
			AWWAY_SIZE(pci_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_PCI_CWK_SHIFT,
			SPEAW1310_PCI_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "pci_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "pci_cwk", "pci_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_PCI_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "pci");

	cwk = cwk_wegistew_mux(NUWW, "tdm1_mcwk", tdm_pawents,
			AWWAY_SIZE(tdm_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_TDM1_CWK_SHIFT,
			SPEAW1310_TDM_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "tdm1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "tdm1_cwk", "tdm1_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_TDM1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "tdm_hdwc.0");

	cwk = cwk_wegistew_mux(NUWW, "tdm2_mcwk", tdm_pawents,
			AWWAY_SIZE(tdm_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1310_WAS_CTWW_WEG0, SPEAW1310_TDM2_CWK_SHIFT,
			SPEAW1310_TDM_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "tdm2_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "tdm2_cwk", "tdm2_mcwk", 0,
			SPEAW1310_WAS_SW_CWK_CTWW, SPEAW1310_TDM2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "tdm_hdwc.1");
}
