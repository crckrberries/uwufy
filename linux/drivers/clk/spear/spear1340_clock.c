// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-speaw13xx/speaw1340_cwock.c
 *
 * SPEAw1340 machine cwock fwamewowk souwce fiwe
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

/* Cwock Configuwation Wegistews */
#define SPEAW1340_SYS_CWK_CTWW			(misc_base + 0x200)
	#define SPEAW1340_HCWK_SWC_SEW_SHIFT	27
	#define SPEAW1340_HCWK_SWC_SEW_MASK	1
	#define SPEAW1340_SCWK_SWC_SEW_SHIFT	23
	#define SPEAW1340_SCWK_SWC_SEW_MASK	3

/* PWW wewated wegistews and bit vawues */
#define SPEAW1340_PWW_CFG			(misc_base + 0x210)
	/* PWW_CFG bit vawues */
	#define SPEAW1340_CWCD_SYNT_CWK_MASK		1
	#define SPEAW1340_CWCD_SYNT_CWK_SHIFT		31
	#define SPEAW1340_GEN_SYNT2_3_CWK_SHIFT		29
	#define SPEAW1340_GEN_SYNT_CWK_MASK		2
	#define SPEAW1340_GEN_SYNT0_1_CWK_SHIFT		27
	#define SPEAW1340_PWW_CWK_MASK			2
	#define SPEAW1340_PWW3_CWK_SHIFT		24
	#define SPEAW1340_PWW2_CWK_SHIFT		22
	#define SPEAW1340_PWW1_CWK_SHIFT		20

#define SPEAW1340_PWW1_CTW			(misc_base + 0x214)
#define SPEAW1340_PWW1_FWQ			(misc_base + 0x218)
#define SPEAW1340_PWW2_CTW			(misc_base + 0x220)
#define SPEAW1340_PWW2_FWQ			(misc_base + 0x224)
#define SPEAW1340_PWW3_CTW			(misc_base + 0x22C)
#define SPEAW1340_PWW3_FWQ			(misc_base + 0x230)
#define SPEAW1340_PWW4_CTW			(misc_base + 0x238)
#define SPEAW1340_PWW4_FWQ			(misc_base + 0x23C)
#define SPEAW1340_PEWIP_CWK_CFG			(misc_base + 0x244)
	/* PEWIP_CWK_CFG bit vawues */
	#define SPEAW1340_SPDIF_CWK_MASK		1
	#define SPEAW1340_SPDIF_OUT_CWK_SHIFT		15
	#define SPEAW1340_SPDIF_IN_CWK_SHIFT		14
	#define SPEAW1340_GPT3_CWK_SHIFT		13
	#define SPEAW1340_GPT2_CWK_SHIFT		12
	#define SPEAW1340_GPT_CWK_MASK			1
	#define SPEAW1340_GPT1_CWK_SHIFT		9
	#define SPEAW1340_GPT0_CWK_SHIFT		8
	#define SPEAW1340_UAWT_CWK_MASK			2
	#define SPEAW1340_UAWT1_CWK_SHIFT		6
	#define SPEAW1340_UAWT0_CWK_SHIFT		4
	#define SPEAW1340_CWCD_CWK_MASK			2
	#define SPEAW1340_CWCD_CWK_SHIFT		2
	#define SPEAW1340_C3_CWK_MASK			1
	#define SPEAW1340_C3_CWK_SHIFT			1

#define SPEAW1340_GMAC_CWK_CFG			(misc_base + 0x248)
	#define SPEAW1340_GMAC_PHY_CWK_MASK		1
	#define SPEAW1340_GMAC_PHY_CWK_SHIFT		2
	#define SPEAW1340_GMAC_PHY_INPUT_CWK_MASK	2
	#define SPEAW1340_GMAC_PHY_INPUT_CWK_SHIFT	0

#define SPEAW1340_I2S_CWK_CFG			(misc_base + 0x24C)
	/* I2S_CWK_CFG wegistew mask */
	#define SPEAW1340_I2S_SCWK_X_MASK		0x1F
	#define SPEAW1340_I2S_SCWK_X_SHIFT		27
	#define SPEAW1340_I2S_SCWK_Y_MASK		0x1F
	#define SPEAW1340_I2S_SCWK_Y_SHIFT		22
	#define SPEAW1340_I2S_SCWK_EQ_SEW_SHIFT		21
	#define SPEAW1340_I2S_SCWK_SYNTH_ENB		20
	#define SPEAW1340_I2S_PWS1_CWK_X_MASK		0xFF
	#define SPEAW1340_I2S_PWS1_CWK_X_SHIFT		12
	#define SPEAW1340_I2S_PWS1_CWK_Y_MASK		0xFF
	#define SPEAW1340_I2S_PWS1_CWK_Y_SHIFT		4
	#define SPEAW1340_I2S_PWS1_EQ_SEW_SHIFT		3
	#define SPEAW1340_I2S_WEF_SEW_MASK		1
	#define SPEAW1340_I2S_WEF_SHIFT			2
	#define SPEAW1340_I2S_SWC_CWK_MASK		2
	#define SPEAW1340_I2S_SWC_CWK_SHIFT		0

#define SPEAW1340_C3_CWK_SYNT			(misc_base + 0x250)
#define SPEAW1340_UAWT0_CWK_SYNT		(misc_base + 0x254)
#define SPEAW1340_UAWT1_CWK_SYNT		(misc_base + 0x258)
#define SPEAW1340_GMAC_CWK_SYNT			(misc_base + 0x25C)
#define SPEAW1340_SDHCI_CWK_SYNT		(misc_base + 0x260)
#define SPEAW1340_CFXD_CWK_SYNT			(misc_base + 0x264)
#define SPEAW1340_ADC_CWK_SYNT			(misc_base + 0x270)
#define SPEAW1340_AMBA_CWK_SYNT			(misc_base + 0x274)
#define SPEAW1340_CWCD_CWK_SYNT			(misc_base + 0x27C)
#define SPEAW1340_SYS_CWK_SYNT			(misc_base + 0x284)
#define SPEAW1340_GEN_CWK_SYNT0			(misc_base + 0x28C)
#define SPEAW1340_GEN_CWK_SYNT1			(misc_base + 0x294)
#define SPEAW1340_GEN_CWK_SYNT2			(misc_base + 0x29C)
#define SPEAW1340_GEN_CWK_SYNT3			(misc_base + 0x304)
#define SPEAW1340_PEWIP1_CWK_ENB		(misc_base + 0x30C)
	#define SPEAW1340_WTC_CWK_ENB			31
	#define SPEAW1340_ADC_CWK_ENB			30
	#define SPEAW1340_C3_CWK_ENB			29
	#define SPEAW1340_CWCD_CWK_ENB			27
	#define SPEAW1340_DMA_CWK_ENB			25
	#define SPEAW1340_GPIO1_CWK_ENB			24
	#define SPEAW1340_GPIO0_CWK_ENB			23
	#define SPEAW1340_GPT1_CWK_ENB			22
	#define SPEAW1340_GPT0_CWK_ENB			21
	#define SPEAW1340_I2S_PWAY_CWK_ENB		20
	#define SPEAW1340_I2S_WEC_CWK_ENB		19
	#define SPEAW1340_I2C0_CWK_ENB			18
	#define SPEAW1340_SSP_CWK_ENB			17
	#define SPEAW1340_UAWT0_CWK_ENB			15
	#define SPEAW1340_PCIE_SATA_CWK_ENB		12
	#define SPEAW1340_UOC_CWK_ENB			11
	#define SPEAW1340_UHC1_CWK_ENB			10
	#define SPEAW1340_UHC0_CWK_ENB			9
	#define SPEAW1340_GMAC_CWK_ENB			8
	#define SPEAW1340_CFXD_CWK_ENB			7
	#define SPEAW1340_SDHCI_CWK_ENB			6
	#define SPEAW1340_SMI_CWK_ENB			5
	#define SPEAW1340_FSMC_CWK_ENB			4
	#define SPEAW1340_SYSWAM0_CWK_ENB		3
	#define SPEAW1340_SYSWAM1_CWK_ENB		2
	#define SPEAW1340_SYSWOM_CWK_ENB		1
	#define SPEAW1340_BUS_CWK_ENB			0

#define SPEAW1340_PEWIP2_CWK_ENB		(misc_base + 0x310)
	#define SPEAW1340_THSENS_CWK_ENB		8
	#define SPEAW1340_I2S_WEF_PAD_CWK_ENB		7
	#define SPEAW1340_ACP_CWK_ENB			6
	#define SPEAW1340_GPT3_CWK_ENB			5
	#define SPEAW1340_GPT2_CWK_ENB			4
	#define SPEAW1340_KBD_CWK_ENB			3
	#define SPEAW1340_CPU_DBG_CWK_ENB		2
	#define SPEAW1340_DDW_COWE_CWK_ENB		1
	#define SPEAW1340_DDW_CTWW_CWK_ENB		0

#define SPEAW1340_PEWIP3_CWK_ENB		(misc_base + 0x314)
	#define SPEAW1340_PWGPIO_CWK_ENB		18
	#define SPEAW1340_VIDEO_DEC_CWK_ENB		16
	#define SPEAW1340_VIDEO_ENC_CWK_ENB		15
	#define SPEAW1340_SPDIF_OUT_CWK_ENB		13
	#define SPEAW1340_SPDIF_IN_CWK_ENB		12
	#define SPEAW1340_VIDEO_IN_CWK_ENB		11
	#define SPEAW1340_CAM0_CWK_ENB			10
	#define SPEAW1340_CAM1_CWK_ENB			9
	#define SPEAW1340_CAM2_CWK_ENB			8
	#define SPEAW1340_CAM3_CWK_ENB			7
	#define SPEAW1340_MAWI_CWK_ENB			6
	#define SPEAW1340_CEC0_CWK_ENB			5
	#define SPEAW1340_CEC1_CWK_ENB			4
	#define SPEAW1340_PWM_CWK_ENB			3
	#define SPEAW1340_I2C1_CWK_ENB			2
	#define SPEAW1340_UAWT1_CWK_ENB			1

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
	{.mode = 0, .m = 0x96, .n = 0x06, .p = 0x0}, /* vco 1200, pww 1200 MHz */
};

/* vco-pww4 wate configuwation tabwe, in ascending owdew of wates */
static stwuct pww_wate_tbw pww4_wtbw[] = {
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x2}, /* vco 1000, pww 250 MHz */
	{.mode = 0, .m = 0xA6, .n = 0x06, .p = 0x2}, /* vco 1328, pww 332 MHz */
	{.mode = 0, .m = 0xC8, .n = 0x06, .p = 0x2}, /* vco 1600, pww 400 MHz */
	{.mode = 0, .m = 0x7D, .n = 0x06, .p = 0x0}, /* vco 1, pww 1 GHz */
};

/*
 * Aww bewow entwies genewate 166 MHz fow
 * diffewent vawues of vco1div2
 */
static stwuct fwac_wate_tbw amba_synth_wtbw[] = {
	{.div = 0x073A8}, /* fow vco1div2 = 600 MHz */
	{.div = 0x06062}, /* fow vco1div2 = 500 MHz */
	{.div = 0x04D1B}, /* fow vco1div2 = 400 MHz */
	{.div = 0x04000}, /* fow vco1div2 = 332 MHz */
	{.div = 0x03031}, /* fow vco1div2 = 250 MHz */
	{.div = 0x0268D}, /* fow vco1div2 = 200 MHz */
};

/*
 * Synthesizew Cwock dewived fwom vcodiv2. This cwock is one of the
 * possibwe cwocks to feed cpu diwectwy.
 * We can pwogwam this synthesizew to make cpu wun on diffewent cwock
 * fwequencies.
 * Fowwowing tabwe pwovides configuwation vawues to wet cpu wun on 200,
 * 250, 332, 400 ow 500 MHz considewing diffewent possibiwites of input
 * (vco1div2) cwock.
 *
 * --------------------------------------------------------------------
 * vco1div2(Mhz)	fout(Mhz)	cpucwk = fout/2		div
 * --------------------------------------------------------------------
 * 400			200		100			0x04000
 * 400			250		125			0x03333
 * 400			332		166			0x0268D
 * 400			400		200			0x02000
 * --------------------------------------------------------------------
 * 500			200		100			0x05000
 * 500			250		125			0x04000
 * 500			332		166			0x03031
 * 500			400		200			0x02800
 * 500			500		250			0x02000
 * --------------------------------------------------------------------
 * 600			200		100			0x06000
 * 600			250		125			0x04CCE
 * 600			332		166			0x039D5
 * 600			400		200			0x03000
 * 600			500		250			0x02666
 * --------------------------------------------------------------------
 * 664			200		100			0x06a38
 * 664			250		125			0x054FD
 * 664			332		166			0x04000
 * 664			400		200			0x0351E
 * 664			500		250			0x02A7E
 * --------------------------------------------------------------------
 * 800			200		100			0x08000
 * 800			250		125			0x06666
 * 800			332		166			0x04D18
 * 800			400		200			0x04000
 * 800			500		250			0x03333
 * --------------------------------------------------------------------
 * sys wate configuwation tabwe is in descending owdew of divisow.
 */
static stwuct fwac_wate_tbw sys_synth_wtbw[] = {
	{.div = 0x08000},
	{.div = 0x06a38},
	{.div = 0x06666},
	{.div = 0x06000},
	{.div = 0x054FD},
	{.div = 0x05000},
	{.div = 0x04D18},
	{.div = 0x04CCE},
	{.div = 0x04000},
	{.div = 0x039D5},
	{.div = 0x0351E},
	{.div = 0x03333},
	{.div = 0x03031},
	{.div = 0x03000},
	{.div = 0x02A7E},
	{.div = 0x02800},
	{.div = 0x0268D},
	{.div = 0x02666},
	{.div = 0x02000},
};

/* aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw aux_wtbw[] = {
	/* 12.29MHz fow vic1div2=600MHz and 10.24MHz fow VCO1div2=500MHz */
	{.xscawe = 5, .yscawe = 122, .eq = 0},
	/* 14.70MHz fow vic1div2=600MHz and 12.29MHz fow VCO1div2=500MHz */
	{.xscawe = 10, .yscawe = 204, .eq = 0},
	/* 48MHz fow vic1div2=600MHz and 40 MHz fow VCO1div2=500MHz */
	{.xscawe = 4, .yscawe = 25, .eq = 0},
	/* 57.14MHz fow vic1div2=600MHz and 48 MHz fow VCO1div2=500MHz */
	{.xscawe = 4, .yscawe = 21, .eq = 0},
	/* 83.33MHz fow vic1div2=600MHz and 69.44MHz fow VCO1div2=500MHz */
	{.xscawe = 5, .yscawe = 18, .eq = 0},
	/* 100MHz fow vic1div2=600MHz and 83.33 MHz fow VCO1div2=500MHz */
	{.xscawe = 2, .yscawe = 6, .eq = 0},
	/* 125MHz fow vic1div2=600MHz and 104.1MHz fow VCO1div2=500MHz */
	{.xscawe = 5, .yscawe = 12, .eq = 0},
	/* 150MHz fow vic1div2=600MHz and 125MHz fow VCO1div2=500MHz */
	{.xscawe = 2, .yscawe = 4, .eq = 0},
	/* 166MHz fow vic1div2=600MHz and 138.88MHz fow VCO1div2=500MHz */
	{.xscawe = 5, .yscawe = 18, .eq = 1},
	/* 200MHz fow vic1div2=600MHz and 166MHz fow VCO1div2=500MHz */
	{.xscawe = 1, .yscawe = 3, .eq = 1},
	/* 250MHz fow vic1div2=600MHz and 208.33MHz fow VCO1div2=500MHz */
	{.xscawe = 5, .yscawe = 12, .eq = 1},
	/* 300MHz fow vic1div2=600MHz and 250MHz fow VCO1div2=500MHz */
	{.xscawe = 1, .yscawe = 2, .eq = 1},
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
	{.div = 0x18000}, /* 25 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x1638E}, /* 27 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x14000}, /* 25 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x1284B}, /* 27 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x0D8D3}, /* 58 Mhz , fow vco1div4 = 393 MHz */
	{.div = 0x0B72C}, /* 58 Mhz , fow vco1div4 = 332 MHz */
	{.div = 0x0A584}, /* 58 Mhz , fow vco1div4 = 300 MHz */
	{.div = 0x093B1}, /* 65 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x089EE}, /* 58 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x081BA}, /* 74 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x07BA0}, /* 65 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x06f1C}, /* 72 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x06E58}, /* 58 Mhz , fow vco1div4 = 200 MHz */
	{.div = 0x06c1B}, /* 74 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x058E3}, /* 108 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x04A12}, /* 108 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x040A5}, /* 148.5 Mhz , fow vc01div4 = 300 MHz*/
	{.div = 0x0378E}, /* 144 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x0360D}, /* 148 Mhz , fow vc01div4 = 250 MHz*/
	{.div = 0x035E0}, /* 148.5 MHz, fow vc01div4 = 250 MHz*/
};

/* i2s pwescawew1 masks */
static const stwuct aux_cwk_masks i2s_pws1_masks = {
	.eq_sew_mask = AUX_EQ_SEW_MASK,
	.eq_sew_shift = SPEAW1340_I2S_PWS1_EQ_SEW_SHIFT,
	.eq1_mask = AUX_EQ1_SEW,
	.eq2_mask = AUX_EQ2_SEW,
	.xscawe_sew_mask = SPEAW1340_I2S_PWS1_CWK_X_MASK,
	.xscawe_sew_shift = SPEAW1340_I2S_PWS1_CWK_X_SHIFT,
	.yscawe_sew_mask = SPEAW1340_I2S_PWS1_CWK_Y_MASK,
	.yscawe_sew_shift = SPEAW1340_I2S_PWS1_CWK_Y_SHIFT,
};

/* i2s scwk (bit cwock) syynthesizews masks */
static const stwuct aux_cwk_masks i2s_scwk_masks = {
	.eq_sew_mask = AUX_EQ_SEW_MASK,
	.eq_sew_shift = SPEAW1340_I2S_SCWK_EQ_SEW_SHIFT,
	.eq1_mask = AUX_EQ1_SEW,
	.eq2_mask = AUX_EQ2_SEW,
	.xscawe_sew_mask = SPEAW1340_I2S_SCWK_X_MASK,
	.xscawe_sew_shift = SPEAW1340_I2S_SCWK_X_SHIFT,
	.yscawe_sew_mask = SPEAW1340_I2S_SCWK_Y_MASK,
	.yscawe_sew_shift = SPEAW1340_I2S_SCWK_Y_SHIFT,
	.enabwe_bit = SPEAW1340_I2S_SCWK_SYNTH_ENB,
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
	{.xscawe = 1, .yscawe = 2, .eq = 0}, /* 12.288 MHz, smp fweq = 48Khz*/
};

/* i2s scwk aux wate configuwation tabwe, in ascending owdew of wates */
static stwuct aux_wate_tbw i2s_scwk_wtbw[] = {
	/* Fow scwk = wef_cwk * x/2/y */
	{.xscawe = 1, .yscawe = 4, .eq = 0},
	{.xscawe = 1, .yscawe = 2, .eq = 0},
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
	{.div = 0x1A92B}, /* 22.5792 MHz fow vco1div4=300 MHz*/
	{.div = 0x186A0}, /* 24.576 MHz fow vco1div4=300 MHz*/
	{.div = 0x18000}, /* 25 MHz fow vco1div4=300 MHz*/
	{.div = 0x1624E}, /* 22.5792 MHz fow vco1div4=250 MHz*/
	{.div = 0x14585}, /* 24.576 MHz fow vco1div4=250 MHz*/
	{.div = 0x14000}, /* 25 MHz fow vco1div4=250 MHz*/
	{.div = 0x0D495}, /* 45.1584 MHz fow vco1div4=300 MHz*/
	{.div = 0x0C000}, /* 50 MHz fow vco1div4=300 MHz*/
	{.div = 0x0B127}, /* 45.1584 MHz fow vco1div4=250 MHz*/
	{.div = 0x0A000}, /* 50 MHz fow vco1div4=250 MHz*/
	{.div = 0x07530}, /* 81.92 MHz fow vco1div4=300 MHz*/
	{.div = 0x061A8}, /* 81.92 MHz fow vco1div4=250 MHz*/
	{.div = 0x06000}, /* 100 MHz fow vco1div4=300 MHz*/
	{.div = 0x05000}, /* 100 MHz fow vco1div4=250 MHz*/
	{.div = 0x03000}, /* 200 MHz fow vco1div4=300 MHz*/
	{.div = 0x02DB6}, /* 210 MHz fow vco1div4=300 MHz*/
	{.div = 0x02BA2}, /* 220 MHz fow vco1div4=300 MHz*/
	{.div = 0x029BD}, /* 230 MHz fow vco1div4=300 MHz*/
	{.div = 0x02800}, /* 200 MHz fow vco1div4=250 MHz*/
	{.div = 0x02666}, /* 250 MHz fow vco1div4=300 MHz*/
	{.div = 0x02620}, /* 210 MHz fow vco1div4=250 MHz*/
	{.div = 0x02460}, /* 220 MHz fow vco1div4=250 MHz*/
	{.div = 0x022C0}, /* 230 MHz fow vco1div4=250 MHz*/
	{.div = 0x02160}, /* 240 MHz fow vco1div4=250 MHz*/
	{.div = 0x02000}, /* 250 MHz fow vco1div4=250 MHz*/
};

/* cwock pawents */
static const chaw *vco_pawents[] = { "osc_24m_cwk", "osc_25m_cwk", };
static const chaw *sys_pawents[] = { "pww1_cwk", "pww1_cwk", "pww1_cwk",
	"pww1_cwk", "sys_syn_cwk", "sys_syn_cwk", "pww2_cwk", "pww3_cwk", };
static const chaw *ahb_pawents[] = { "cpu_div3_cwk", "amba_syn_cwk", };
static const chaw *gpt_pawents[] = { "osc_24m_cwk", "apb_cwk", };
static const chaw *uawt0_pawents[] = { "pww5_cwk", "osc_24m_cwk",
	"uawt0_syn_gcwk", };
static const chaw *uawt1_pawents[] = { "pww5_cwk", "osc_24m_cwk",
	"uawt1_syn_gcwk", };
static const chaw *c3_pawents[] = { "pww5_cwk", "c3_syn_gcwk", };
static const chaw *gmac_phy_input_pawents[] = { "gmii_pad_cwk", "pww2_cwk",
	"osc_25m_cwk", };
static const chaw *gmac_phy_pawents[] = { "phy_input_mcwk", "phy_syn_gcwk", };
static const chaw *cwcd_synth_pawents[] = { "vco1div4_cwk", "pww2_cwk", };
static const chaw *cwcd_pixew_pawents[] = { "pww5_cwk", "cwcd_syn_cwk", };
static const chaw *i2s_swc_pawents[] = { "vco1div2_cwk", "pww2_cwk", "pww3_cwk",
	"i2s_swc_pad_cwk", };
static const chaw *i2s_wef_pawents[] = { "i2s_swc_mcwk", "i2s_pws1_cwk", };
static const chaw *spdif_out_pawents[] = { "i2s_swc_pad_cwk", "gen_syn2_cwk", };
static const chaw *spdif_in_pawents[] = { "pww2_cwk", "gen_syn3_cwk", };

static const chaw *gen_synth0_1_pawents[] = { "vco1div4_cwk", "vco3div2_cwk",
	"pww3_cwk", };
static const chaw *gen_synth2_3_pawents[] = { "vco1div4_cwk", "vco2div2_cwk",
	"pww2_cwk", };

void __init speaw1340_cwk_init(void __iomem *misc_base)
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
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_WTC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0580000.wtc");

	/* cwock dewived fwom 24 ow 25 MHz osc cwk */
	/* vco-pww */
	cwk = cwk_wegistew_mux(NUWW, "vco1_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PWW_CFG, SPEAW1340_PWW1_CWK_SHIFT,
			SPEAW1340_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco1_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco1_cwk", "pww1_cwk", NUWW, "vco1_mcwk", 0,
			SPEAW1340_PWW1_CTW, SPEAW1340_PWW1_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco1_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww1_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "vco2_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PWW_CFG, SPEAW1340_PWW2_CWK_SHIFT,
			SPEAW1340_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco2_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco2_cwk", "pww2_cwk", NUWW, "vco2_mcwk", 0,
			SPEAW1340_PWW2_CTW, SPEAW1340_PWW2_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco2_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww2_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "vco3_mcwk", vco_pawents,
			AWWAY_SIZE(vco_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PWW_CFG, SPEAW1340_PWW3_CWK_SHIFT,
			SPEAW1340_PWW_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "vco3_mcwk", NUWW);
	cwk = cwk_wegistew_vco_pww("vco3_cwk", "pww3_cwk", NUWW, "vco3_mcwk", 0,
			SPEAW1340_PWW3_CTW, SPEAW1340_PWW3_FWQ, pww_wtbw,
			AWWAY_SIZE(pww_wtbw), &_wock, &cwk1, NUWW);
	cwk_wegistew_cwkdev(cwk, "vco3_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "pww3_cwk", NUWW);

	cwk = cwk_wegistew_vco_pww("vco4_cwk", "pww4_cwk", NUWW, "osc_24m_cwk",
			0, SPEAW1340_PWW4_CTW, SPEAW1340_PWW4_FWQ, pww4_wtbw,
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
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_THSENS_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e07008c4.thewmaw");

	/* cwock dewived fwom pww4 cwk */
	cwk = cwk_wegistew_fixed_factow(NUWW, "ddw_cwk", "pww4_cwk", 0, 1,
			1);
	cwk_wegistew_cwkdev(cwk, "ddw_cwk", NUWW);

	/* cwock dewived fwom pww1 cwk */
	cwk = cwk_wegistew_fwac("sys_syn_cwk", "vco1div2_cwk", 0,
			SPEAW1340_SYS_CWK_SYNT, sys_synth_wtbw,
			AWWAY_SIZE(sys_synth_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "sys_syn_cwk", NUWW);

	cwk = cwk_wegistew_fwac("amba_syn_cwk", "vco1div2_cwk", 0,
			SPEAW1340_AMBA_CWK_SYNT, amba_synth_wtbw,
			AWWAY_SIZE(amba_synth_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "amba_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "sys_mcwk", sys_pawents,
			AWWAY_SIZE(sys_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_SYS_CWK_CTWW, SPEAW1340_SCWK_SWC_SEW_SHIFT,
			SPEAW1340_SCWK_SWC_SEW_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "sys_mcwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "cpu_cwk", "sys_mcwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, "cpu_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "cpu_div3_cwk", "cpu_cwk", 0, 1,
			3);
	cwk_wegistew_cwkdev(cwk, "cpu_div3_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "wdt_cwk", "cpu_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, NUWW, "ec800620.wdt");

	cwk = cwk_wegistew_fixed_factow(NUWW, "smp_twd_cwk", "cpu_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, NUWW, "smp_twd");

	cwk = cwk_wegistew_mux(NUWW, "ahb_cwk", ahb_pawents,
			AWWAY_SIZE(ahb_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_SYS_CWK_CTWW, SPEAW1340_HCWK_SWC_SEW_SHIFT,
			SPEAW1340_HCWK_SWC_SEW_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "ahb_cwk", NUWW);

	cwk = cwk_wegistew_fixed_factow(NUWW, "apb_cwk", "ahb_cwk", 0, 1,
			2);
	cwk_wegistew_cwkdev(cwk, "apb_cwk", NUWW);

	/* gpt cwocks */
	cwk = cwk_wegistew_mux(NUWW, "gpt0_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_GPT0_CWK_SHIFT,
			SPEAW1340_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt0_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt0_cwk", "gpt0_mcwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_GPT0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt0");

	cwk = cwk_wegistew_mux(NUWW, "gpt1_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_GPT1_CWK_SHIFT,
			SPEAW1340_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt1_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt1_cwk", "gpt1_mcwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_GPT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt1");

	cwk = cwk_wegistew_mux(NUWW, "gpt2_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_GPT2_CWK_SHIFT,
			SPEAW1340_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt2_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt2_cwk", "gpt2_mcwk", 0,
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_GPT2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt2");

	cwk = cwk_wegistew_mux(NUWW, "gpt3_mcwk", gpt_pawents,
			AWWAY_SIZE(gpt_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_GPT3_CWK_SHIFT,
			SPEAW1340_GPT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gpt3_mcwk", NUWW);
	cwk = cwk_wegistew_gate(NUWW, "gpt3_cwk", "gpt3_mcwk", 0,
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_GPT3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "gpt3");

	/* othews */
	cwk = cwk_wegistew_aux("uawt0_syn_cwk", "uawt0_syn_gcwk",
			"vco1div2_cwk", 0, SPEAW1340_UAWT0_CWK_SYNT, NUWW,
			aux_wtbw, AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "uawt0_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "uawt0_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "uawt0_mcwk", uawt0_pawents,
			AWWAY_SIZE(uawt0_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_UAWT0_CWK_SHIFT,
			SPEAW1340_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt0_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt0_cwk", "uawt0_mcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP1_CWK_ENB,
			SPEAW1340_UAWT0_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0000000.sewiaw");

	cwk = cwk_wegistew_aux("uawt1_syn_cwk", "uawt1_syn_gcwk",
			"vco1div2_cwk", 0, SPEAW1340_UAWT1_CWK_SYNT, NUWW,
			aux_wtbw, AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "uawt1_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "uawt1_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "uawt1_mcwk", uawt1_pawents,
			AWWAY_SIZE(uawt1_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_UAWT1_CWK_SHIFT,
			SPEAW1340_UAWT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "uawt1_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "uawt1_cwk", "uawt1_mcwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_UAWT1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b4100000.sewiaw");

	cwk = cwk_wegistew_aux("sdhci_syn_cwk", "sdhci_syn_gcwk",
			"vco1div2_cwk", 0, SPEAW1340_SDHCI_CWK_SYNT, NUWW,
			aux_wtbw, AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "sdhci_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "sdhci_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "sdhci_cwk", "sdhci_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP1_CWK_ENB,
			SPEAW1340_SDHCI_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b3000000.sdhci");

	cwk = cwk_wegistew_aux("cfxd_syn_cwk", "cfxd_syn_gcwk", "vco1div2_cwk",
			0, SPEAW1340_CFXD_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "cfxd_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "cfxd_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "cfxd_cwk", "cfxd_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP1_CWK_ENB,
			SPEAW1340_CFXD_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2800000.cf");
	cwk_wegistew_cwkdev(cwk, NUWW, "awasan_xd");

	cwk = cwk_wegistew_aux("c3_syn_cwk", "c3_syn_gcwk", "vco1div2_cwk", 0,
			SPEAW1340_C3_CWK_SYNT, NUWW, aux_wtbw,
			AWWAY_SIZE(aux_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "c3_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "c3_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "c3_mcwk", c3_pawents,
			AWWAY_SIZE(c3_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_C3_CWK_SHIFT,
			SPEAW1340_C3_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "c3_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "c3_cwk", "c3_mcwk", CWK_SET_WATE_PAWENT,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_C3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1800000.c3");

	/* gmac */
	cwk = cwk_wegistew_mux(NUWW, "phy_input_mcwk", gmac_phy_input_pawents,
			AWWAY_SIZE(gmac_phy_input_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1340_GMAC_CWK_CFG,
			SPEAW1340_GMAC_PHY_INPUT_CWK_SHIFT,
			SPEAW1340_GMAC_PHY_INPUT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "phy_input_mcwk", NUWW);

	cwk = cwk_wegistew_aux("phy_syn_cwk", "phy_syn_gcwk", "phy_input_mcwk",
			0, SPEAW1340_GMAC_CWK_SYNT, NUWW, gmac_wtbw,
			AWWAY_SIZE(gmac_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "phy_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "phy_syn_gcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "phy_mcwk", gmac_phy_pawents,
			AWWAY_SIZE(gmac_phy_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_GMAC_PHY_CWK_SHIFT,
			SPEAW1340_GMAC_PHY_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "stmmacphy.0", NUWW);

	/* cwcd */
	cwk = cwk_wegistew_mux(NUWW, "cwcd_syn_mcwk", cwcd_synth_pawents,
			AWWAY_SIZE(cwcd_synth_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1340_CWCD_CWK_SYNT,
			SPEAW1340_CWCD_SYNT_CWK_SHIFT,
			SPEAW1340_CWCD_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_syn_mcwk", NUWW);

	cwk = cwk_wegistew_fwac("cwcd_syn_cwk", "cwcd_syn_mcwk", 0,
			SPEAW1340_CWCD_CWK_SYNT, cwcd_wtbw,
			AWWAY_SIZE(cwcd_wtbw), &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_syn_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "cwcd_pixew_mcwk", cwcd_pixew_pawents,
			AWWAY_SIZE(cwcd_pixew_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_CWCD_CWK_SHIFT,
			SPEAW1340_CWCD_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "cwcd_pixew_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "cwcd_cwk", "cwcd_pixew_mcwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_CWCD_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e1000000.cwcd");

	/* i2s */
	cwk = cwk_wegistew_mux(NUWW, "i2s_swc_mcwk", i2s_swc_pawents,
			AWWAY_SIZE(i2s_swc_pawents), CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_I2S_CWK_CFG, SPEAW1340_I2S_SWC_CWK_SHIFT,
			SPEAW1340_I2S_SWC_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_swc_mcwk", NUWW);

	cwk = cwk_wegistew_aux("i2s_pws1_cwk", NUWW, "i2s_swc_mcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_I2S_CWK_CFG,
			&i2s_pws1_masks, i2s_pws1_wtbw,
			AWWAY_SIZE(i2s_pws1_wtbw), &_wock, NUWW);
	cwk_wegistew_cwkdev(cwk, "i2s_pws1_cwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "i2s_wef_mcwk", i2s_wef_pawents,
			AWWAY_SIZE(i2s_wef_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_I2S_CWK_CFG, SPEAW1340_I2S_WEF_SHIFT,
			SPEAW1340_I2S_WEF_SEW_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_wef_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "i2s_wef_pad_cwk", "i2s_wef_mcwk", 0,
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_I2S_WEF_PAD_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, "i2s_wef_pad_cwk", NUWW);

	cwk = cwk_wegistew_aux("i2s_scwk_cwk", "i2s_scwk_gcwk", "i2s_wef_mcwk",
			0, SPEAW1340_I2S_CWK_CFG, &i2s_scwk_masks,
			i2s_scwk_wtbw, AWWAY_SIZE(i2s_scwk_wtbw), &_wock,
			&cwk1);
	cwk_wegistew_cwkdev(cwk, "i2s_scwk_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "i2s_scwk_gcwk", NUWW);

	/* cwock dewived fwom ahb cwk */
	cwk = cwk_wegistew_gate(NUWW, "i2c0_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_I2C0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0280000.i2c");

	cwk = cwk_wegistew_gate(NUWW, "i2c1_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_I2C1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b4000000.i2c");

	cwk = cwk_wegistew_gate(NUWW, "dma_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_DMA_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "ea800000.dma");
	cwk_wegistew_cwkdev(cwk, NUWW, "eb000000.dma");

	cwk = cwk_wegistew_gate(NUWW, "gmac_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_GMAC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e2000000.eth");

	cwk = cwk_wegistew_gate(NUWW, "fsmc_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_FSMC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b0000000.fwash");

	cwk = cwk_wegistew_gate(NUWW, "smi_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_SMI_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "ea000000.fwash");

	cwk = cwk_wegistew_gate(NUWW, "usbh0_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_UHC0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e4000000.ohci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e4800000.ehci");

	cwk = cwk_wegistew_gate(NUWW, "usbh1_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_UHC1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e5000000.ohci");
	cwk_wegistew_cwkdev(cwk, NUWW, "e5800000.ehci");

	cwk = cwk_wegistew_gate(NUWW, "uoc_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_UOC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e3800000.otg");

	cwk = cwk_wegistew_gate(NUWW, "pcie_sata_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_PCIE_SATA_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b1000000.pcie");
	cwk_wegistew_cwkdev(cwk, NUWW, "b1000000.ahci");

	cwk = cwk_wegistew_gate(NUWW, "syswam0_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_SYSWAM0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "syswam0_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "syswam1_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_SYSWAM1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, "syswam1_cwk", NUWW);

	cwk = cwk_wegistew_aux("adc_syn_cwk", "adc_syn_gcwk", "ahb_cwk",
			0, SPEAW1340_ADC_CWK_SYNT, NUWW, adc_wtbw,
			AWWAY_SIZE(adc_wtbw), &_wock, &cwk1);
	cwk_wegistew_cwkdev(cwk, "adc_syn_cwk", NUWW);
	cwk_wegistew_cwkdev(cwk1, "adc_syn_gcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "adc_cwk", "adc_syn_gcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP1_CWK_ENB,
			SPEAW1340_ADC_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0080000.adc");

	/* cwock dewived fwom apb cwk */
	cwk = cwk_wegistew_gate(NUWW, "ssp_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_SSP_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0100000.spi");

	cwk = cwk_wegistew_gate(NUWW, "gpio0_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_GPIO0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0600000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "gpio1_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_GPIO1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0680000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "i2s_pway_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_I2S_PWAY_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2400000.i2s-pway");

	cwk = cwk_wegistew_gate(NUWW, "i2s_wec_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP1_CWK_ENB, SPEAW1340_I2S_WEC_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "b2000000.i2s-wec");

	cwk = cwk_wegistew_gate(NUWW, "kbd_cwk", "apb_cwk", 0,
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_KBD_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0300000.kbd");

	/* WAS cwks */
	cwk = cwk_wegistew_mux(NUWW, "gen_syn0_1_mcwk", gen_synth0_1_pawents,
			AWWAY_SIZE(gen_synth0_1_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1340_PWW_CFG,
			SPEAW1340_GEN_SYNT0_1_CWK_SHIFT,
			SPEAW1340_GEN_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn0_1_mcwk", NUWW);

	cwk = cwk_wegistew_mux(NUWW, "gen_syn2_3_mcwk", gen_synth2_3_pawents,
			AWWAY_SIZE(gen_synth2_3_pawents),
			CWK_SET_WATE_NO_WEPAWENT, SPEAW1340_PWW_CFG,
			SPEAW1340_GEN_SYNT2_3_CWK_SHIFT,
			SPEAW1340_GEN_SYNT_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn2_3_mcwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn0_cwk", "gen_syn0_1_mcwk", 0,
			SPEAW1340_GEN_CWK_SYNT0, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn0_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn1_cwk", "gen_syn0_1_mcwk", 0,
			SPEAW1340_GEN_CWK_SYNT1, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn1_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn2_cwk", "gen_syn2_3_mcwk", 0,
			SPEAW1340_GEN_CWK_SYNT2, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn2_cwk", NUWW);

	cwk = cwk_wegistew_fwac("gen_syn3_cwk", "gen_syn2_3_mcwk", 0,
			SPEAW1340_GEN_CWK_SYNT3, gen_wtbw, AWWAY_SIZE(gen_wtbw),
			&_wock);
	cwk_wegistew_cwkdev(cwk, "gen_syn3_cwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "mawi_cwk", "gen_syn3_cwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP3_CWK_ENB,
			SPEAW1340_MAWI_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "mawi");

	cwk = cwk_wegistew_gate(NUWW, "cec0_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CEC0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "speaw_cec.0");

	cwk = cwk_wegistew_gate(NUWW, "cec1_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CEC1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "speaw_cec.1");

	cwk = cwk_wegistew_mux(NUWW, "spdif_out_mcwk", spdif_out_pawents,
			AWWAY_SIZE(spdif_out_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_SPDIF_OUT_CWK_SHIFT,
			SPEAW1340_SPDIF_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "spdif_out_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "spdif_out_cwk", "spdif_out_mcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP3_CWK_ENB,
			SPEAW1340_SPDIF_OUT_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0000000.spdif-out");

	cwk = cwk_wegistew_mux(NUWW, "spdif_in_mcwk", spdif_in_pawents,
			AWWAY_SIZE(spdif_in_pawents),
			CWK_SET_WATE_PAWENT | CWK_SET_WATE_NO_WEPAWENT,
			SPEAW1340_PEWIP_CWK_CFG, SPEAW1340_SPDIF_IN_CWK_SHIFT,
			SPEAW1340_SPDIF_CWK_MASK, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, "spdif_in_mcwk", NUWW);

	cwk = cwk_wegistew_gate(NUWW, "spdif_in_cwk", "spdif_in_mcwk",
			CWK_SET_WATE_PAWENT, SPEAW1340_PEWIP3_CWK_ENB,
			SPEAW1340_SPDIF_IN_CWK_ENB, 0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0100000.spdif-in");

	cwk = cwk_wegistew_gate(NUWW, "acp_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP2_CWK_ENB, SPEAW1340_ACP_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "acp_cwk");

	cwk = cwk_wegistew_gate(NUWW, "pwgpio_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_PWGPIO_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e2800000.gpio");

	cwk = cwk_wegistew_gate(NUWW, "video_dec_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_VIDEO_DEC_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "video_dec");

	cwk = cwk_wegistew_gate(NUWW, "video_enc_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_VIDEO_ENC_CWK_ENB,
			0, &_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "video_enc");

	cwk = cwk_wegistew_gate(NUWW, "video_in_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_VIDEO_IN_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "speaw_vip");

	cwk = cwk_wegistew_gate(NUWW, "cam0_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CAM0_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0200000.cam0");

	cwk = cwk_wegistew_gate(NUWW, "cam1_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CAM1_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0300000.cam1");

	cwk = cwk_wegistew_gate(NUWW, "cam2_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CAM2_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0400000.cam2");

	cwk = cwk_wegistew_gate(NUWW, "cam3_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_CAM3_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "d0500000.cam3");

	cwk = cwk_wegistew_gate(NUWW, "pwm_cwk", "ahb_cwk", 0,
			SPEAW1340_PEWIP3_CWK_ENB, SPEAW1340_PWM_CWK_ENB, 0,
			&_wock);
	cwk_wegistew_cwkdev(cwk, NUWW, "e0180000.pwm");
}
