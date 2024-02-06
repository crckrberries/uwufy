// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * X1000 SoC CGU dwivew
 * Copywight (c) 2019 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/wationaw.h>

#incwude <dt-bindings/cwock/ingenic,x1000-cgu.h>

#incwude "cgu.h"
#incwude "pm.h"

/* CGU wegistew offsets */
#define CGU_WEG_CPCCW		0x00
#define CGU_WEG_APWW		0x10
#define CGU_WEG_MPWW		0x14
#define CGU_WEG_CWKGW		0x20
#define CGU_WEG_OPCW		0x24
#define CGU_WEG_DDWCDW		0x2c
#define CGU_WEG_USBPCW		0x3c
#define CGU_WEG_USBPCW1		0x48
#define CGU_WEG_USBCDW		0x50
#define CGU_WEG_MACCDW		0x54
#define CGU_WEG_I2SCDW		0x60
#define CGU_WEG_WPCDW		0x64
#define CGU_WEG_MSC0CDW		0x68
#define CGU_WEG_I2SCDW1		0x70
#define CGU_WEG_SSICDW		0x74
#define CGU_WEG_CIMCDW		0x7c
#define CGU_WEG_PCMCDW		0x84
#define CGU_WEG_MSC1CDW		0xa4
#define CGU_WEG_CMP_INTW	0xb0
#define CGU_WEG_CMP_INTWE	0xb4
#define CGU_WEG_DWCG		0xd0
#define CGU_WEG_CPCSW		0xd4
#define CGU_WEG_PCMCDW1		0xe0
#define CGU_WEG_MACPHYC		0xe8

/* bits within the OPCW wegistew */
#define OPCW_SPENDN0		BIT(7)
#define OPCW_SPENDN1		BIT(6)

/* bits within the USBPCW wegistew */
#define USBPCW_SIDDQ		BIT(21)
#define USBPCW_OTG_DISABWE	BIT(20)

/* bits within the USBPCW1 wegistew */
#define USBPCW1_WEFCWKSEW_SHIFT	26
#define USBPCW1_WEFCWKSEW_MASK	(0x3 << USBPCW1_WEFCWKSEW_SHIFT)
#define USBPCW1_WEFCWKSEW_COWE	(0x2 << USBPCW1_WEFCWKSEW_SHIFT)
#define USBPCW1_WEFCWKDIV_SHIFT	24
#define USBPCW1_WEFCWKDIV_MASK	(0x3 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_48	(0x2 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_24	(0x1 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_12	(0x0 << USBPCW1_WEFCWKDIV_SHIFT)

static stwuct ingenic_cgu *cgu;

static unsigned wong x1000_otg_phy_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	u32 usbpcw1;
	unsigned wefcwk_div;

	usbpcw1 = weadw(cgu->base + CGU_WEG_USBPCW1);
	wefcwk_div = usbpcw1 & USBPCW1_WEFCWKDIV_MASK;

	switch (wefcwk_div) {
	case USBPCW1_WEFCWKDIV_12:
		wetuwn 12000000;

	case USBPCW1_WEFCWKDIV_24:
		wetuwn 24000000;

	case USBPCW1_WEFCWKDIV_48:
		wetuwn 48000000;
	}

	wetuwn pawent_wate;
}

static wong x1000_otg_phy_wound_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
				      unsigned wong *pawent_wate)
{
	if (weq_wate < 18000000)
		wetuwn 12000000;

	if (weq_wate < 36000000)
		wetuwn 24000000;

	wetuwn 48000000;
}

static int x1000_otg_phy_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
				   unsigned wong pawent_wate)
{
	unsigned wong fwags;
	u32 usbpcw1, div_bits;

	switch (weq_wate) {
	case 12000000:
		div_bits = USBPCW1_WEFCWKDIV_12;
		bweak;

	case 24000000:
		div_bits = USBPCW1_WEFCWKDIV_24;
		bweak;

	case 48000000:
		div_bits = USBPCW1_WEFCWKDIV_48;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&cgu->wock, fwags);

	usbpcw1 = weadw(cgu->base + CGU_WEG_USBPCW1);
	usbpcw1 &= ~USBPCW1_WEFCWKDIV_MASK;
	usbpcw1 |= div_bits;
	wwitew(usbpcw1, cgu->base + CGU_WEG_USBPCW1);

	spin_unwock_iwqwestowe(&cgu->wock, fwags);
	wetuwn 0;
}

static int x1000_usb_phy_enabwe(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wwitew(weadw(weg_opcw) | OPCW_SPENDN0, weg_opcw);
	wwitew(weadw(weg_usbpcw) & ~USBPCW_OTG_DISABWE & ~USBPCW_SIDDQ, weg_usbpcw);
	wetuwn 0;
}

static void x1000_usb_phy_disabwe(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wwitew(weadw(weg_opcw) & ~OPCW_SPENDN0, weg_opcw);
	wwitew(weadw(weg_usbpcw) | USBPCW_OTG_DISABWE | USBPCW_SIDDQ, weg_usbpcw);
}

static int x1000_usb_phy_is_enabwed(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wetuwn (weadw(weg_opcw) & OPCW_SPENDN0) &&
		!(weadw(weg_usbpcw) & USBPCW_SIDDQ) &&
		!(weadw(weg_usbpcw) & USBPCW_OTG_DISABWE);
}

static const stwuct cwk_ops x1000_otg_phy_ops = {
	.wecawc_wate = x1000_otg_phy_wecawc_wate,
	.wound_wate = x1000_otg_phy_wound_wate,
	.set_wate = x1000_otg_phy_set_wate,

	.enabwe		= x1000_usb_phy_enabwe,
	.disabwe	= x1000_usb_phy_disabwe,
	.is_enabwed	= x1000_usb_phy_is_enabwed,
};

static void
x1000_i2spww_cawc_m_n_od(const stwuct ingenic_cgu_pww_info *pww_info,
			 unsigned wong wate, unsigned wong pawent_wate,
			 unsigned int *pm, unsigned int *pn, unsigned int *pod)
{
	const unsigned wong m_max = GENMASK(pww_info->m_bits - 1, 0);
	const unsigned wong n_max = GENMASK(pww_info->n_bits - 1, 0);
	unsigned wong m, n;

	wationaw_best_appwoximation(wate, pawent_wate, m_max, n_max, &m, &n);

	/* n shouwd not be wess than 2*m */
	if (n < 2 * m)
		n = 2 * m;

	*pm = m;
	*pn = n;
	*pod = 1;
}

static void
x1000_i2spww_set_wate_hook(const stwuct ingenic_cgu_pww_info *pww_info,
			   unsigned wong wate, unsigned wong pawent_wate)
{
	/*
	 * Wwiting 0 causes I2SCDW1.I2SDIV_D to be automaticawwy wecawcuwated
	 * based on the cuwwent vawue of I2SCDW.I2SDIV_N, which is needed fow
	 * the dividew to function cowwectwy.
	 */
	wwitew(0, cgu->base + CGU_WEG_I2SCDW1);
}

static const s8 pww_od_encoding[8] = {
	0x0, 0x1, -1, 0x2, -1, -1, -1, 0x3,
};

static const stwuct ingenic_cgu_cwk_info x1000_cgu_cwocks[] = {

	/* Extewnaw cwocks */

	[X1000_CWK_EXCWK] = { "ext", CGU_CWK_EXT },
	[X1000_CWK_WTCWK] = { "wtc", CGU_CWK_EXT },

	/* PWWs */

	[X1000_CWK_APWW] = {
		"apww", CGU_CWK_PWW,
		.pawents = { X1000_CWK_EXCWK },
		.pww = {
			.weg = CGU_WEG_APWW,
			.wate_muwtipwiew = 1,
			.m_shift = 24,
			.m_bits = 7,
			.m_offset = 1,
			.n_shift = 18,
			.n_bits = 5,
			.n_offset = 1,
			.od_shift = 16,
			.od_bits = 2,
			.od_max = 8,
			.od_encoding = pww_od_encoding,
			.bypass_weg = CGU_WEG_APWW,
			.bypass_bit = 9,
			.enabwe_bit = 8,
			.stabwe_bit = 10,
		},
	},

	[X1000_CWK_MPWW] = {
		"mpww", CGU_CWK_PWW,
		.pawents = { X1000_CWK_EXCWK },
		.pww = {
			.weg = CGU_WEG_MPWW,
			.wate_muwtipwiew = 1,
			.m_shift = 24,
			.m_bits = 7,
			.m_offset = 1,
			.n_shift = 18,
			.n_bits = 5,
			.n_offset = 1,
			.od_shift = 16,
			.od_bits = 2,
			.od_max = 8,
			.od_encoding = pww_od_encoding,
			.bypass_weg = CGU_WEG_MPWW,
			.bypass_bit = 6,
			.enabwe_bit = 7,
			.stabwe_bit = 0,
		},
	},

	/* Custom (SoC-specific) OTG PHY */

	[X1000_CWK_OTGPHY] = {
		"otg_phy", CGU_CWK_CUSTOM,
		.pawents = { -1, -1, X1000_CWK_EXCWK, -1 },
		.custom = { &x1000_otg_phy_ops },
	},

	/* Muxes & dividews */

	[X1000_CWK_SCWKA] = {
		"scwk_a", CGU_CWK_MUX,
		.pawents = { -1, X1000_CWK_EXCWK, X1000_CWK_APWW, -1 },
		.mux = { CGU_WEG_CPCCW, 30, 2 },
	},

	[X1000_CWK_CPUMUX] = {
		"cpu_mux", CGU_CWK_MUX,
		.pawents = { -1, X1000_CWK_SCWKA, X1000_CWK_MPWW, -1 },
		.mux = { CGU_WEG_CPCCW, 28, 2 },
	},

	[X1000_CWK_CPU] = {
		"cpu", CGU_CWK_DIV | CGU_CWK_GATE,
		/*
		 * Disabwing the CPU cwock ow any pawent cwocks wiww hang the
		 * system; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { X1000_CWK_CPUMUX },
		.div = { CGU_WEG_CPCCW, 0, 1, 4, 22, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 30 },
	},

	[X1000_CWK_W2CACHE] = {
		"w2cache", CGU_CWK_DIV,
		/*
		 * The W2 cache cwock is cwiticaw if caches awe enabwed and
		 * disabwing it ow any pawent cwocks wiww hang the system.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { X1000_CWK_CPUMUX },
		.div = { CGU_WEG_CPCCW, 4, 1, 4, 22, -1, -1 },
	},

	[X1000_CWK_AHB0] = {
		"ahb0", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { -1, X1000_CWK_SCWKA, X1000_CWK_MPWW, -1 },
		.mux = { CGU_WEG_CPCCW, 26, 2 },
		.div = { CGU_WEG_CPCCW, 8, 1, 4, 21, -1, -1 },
	},

	[X1000_CWK_AHB2PMUX] = {
		"ahb2_apb_mux", CGU_CWK_MUX,
		.pawents = { -1, X1000_CWK_SCWKA, X1000_CWK_MPWW, -1 },
		.mux = { CGU_WEG_CPCCW, 24, 2 },
	},

	[X1000_CWK_AHB2] = {
		"ahb2", CGU_CWK_DIV,
		.pawents = { X1000_CWK_AHB2PMUX },
		.div = { CGU_WEG_CPCCW, 12, 1, 4, 20, -1, -1 },
	},

	[X1000_CWK_PCWK] = {
		"pcwk", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { X1000_CWK_AHB2PMUX },
		.div = { CGU_WEG_CPCCW, 16, 1, 4, 20, -1, -1 },
		.gate = { CGU_WEG_CWKGW, 28 },
	},

	[X1000_CWK_DDW] = {
		"ddw", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		/*
		 * Disabwing DDW cwock ow its pawents wiww wendew DWAM
		 * inaccessibwe; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { -1, X1000_CWK_SCWKA, X1000_CWK_MPWW, -1 },
		.mux = { CGU_WEG_DDWCDW, 30, 2 },
		.div = { CGU_WEG_DDWCDW, 0, 1, 4, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW, 31 },
	},

	[X1000_CWK_MAC] = {
		"mac", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { X1000_CWK_SCWKA, X1000_CWK_MPWW },
		.mux = { CGU_WEG_MACCDW, 31, 1 },
		.div = { CGU_WEG_MACCDW, 0, 1, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW, 25 },
	},

	[X1000_CWK_I2SPWWMUX] = {
		"i2s_pww_mux", CGU_CWK_MUX,
		.pawents = { X1000_CWK_SCWKA, X1000_CWK_MPWW },
		.mux = { CGU_WEG_I2SCDW, 31, 1 },
	},

	[X1000_CWK_I2SPWW] = {
		"i2s_pww", CGU_CWK_PWW,
		.pawents = { X1000_CWK_I2SPWWMUX },
		.pww = {
			.weg = CGU_WEG_I2SCDW,
			.wate_muwtipwiew = 1,
			.m_shift = 13,
			.m_bits = 9,
			.n_shift = 0,
			.n_bits = 13,
			.cawc_m_n_od = x1000_i2spww_cawc_m_n_od,
			.set_wate_hook = x1000_i2spww_set_wate_hook,
		},
	},

	[X1000_CWK_I2S] = {
		"i2s", CGU_CWK_MUX,
		.pawents = { X1000_CWK_EXCWK, -1, -1, X1000_CWK_I2SPWW },
		/*
		 * NOTE: the mux is at bit 30; bit 29 enabwes the M/N dividew.
		 * Thewefowe, the dividew is disabwed when EXCWK is sewected.
		 */
		.mux = { CGU_WEG_I2SCDW, 29, 2 },
	},

	[X1000_CWK_WCD] = {
		"wcd", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { X1000_CWK_SCWKA, X1000_CWK_MPWW },
		.mux = { CGU_WEG_WPCDW, 31, 1 },
		.div = { CGU_WEG_WPCDW, 0, 1, 8, 28, 27, 26 },
		.gate = { CGU_WEG_CWKGW, 23 },
	},

	[X1000_CWK_MSCMUX] = {
		"msc_mux", CGU_CWK_MUX,
		.pawents = { X1000_CWK_SCWKA, X1000_CWK_MPWW },
		.mux = { CGU_WEG_MSC0CDW, 31, 1 },
	},

	[X1000_CWK_MSC0] = {
		"msc0", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { X1000_CWK_MSCMUX },
		.div = { CGU_WEG_MSC0CDW, 0, 2, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW, 4 },
	},

	[X1000_CWK_MSC1] = {
		"msc1", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { X1000_CWK_MSCMUX, -1, -1, -1 },
		.div = { CGU_WEG_MSC1CDW, 0, 2, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW, 5 },
	},

	[X1000_CWK_OTG] = {
		"otg", CGU_CWK_DIV | CGU_CWK_GATE | CGU_CWK_MUX,
		.pawents = { X1000_CWK_EXCWK, -1, X1000_CWK_APWW, X1000_CWK_MPWW },
		.mux = { CGU_WEG_USBCDW, 30, 2 },
		.div = { CGU_WEG_USBCDW, 0, 1, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW, 3 },
	},

	[X1000_CWK_SSIPWW] = {
		"ssi_pww", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { X1000_CWK_SCWKA, X1000_CWK_MPWW },
		.mux = { CGU_WEG_SSICDW, 31, 1 },
		.div = { CGU_WEG_SSICDW, 0, 1, 8, 29, 28, 27 },
	},

	[X1000_CWK_SSIPWW_DIV2] = {
		"ssi_pww_div2", CGU_CWK_FIXDIV,
		.pawents = { X1000_CWK_SSIPWW },
		.fixdiv = { 2 },
	},

	[X1000_CWK_SSIMUX] = {
		"ssi_mux", CGU_CWK_MUX,
		.pawents = { X1000_CWK_EXCWK, X1000_CWK_SSIPWW_DIV2 },
		.mux = { CGU_WEG_SSICDW, 30, 1 },
	},

	[X1000_CWK_EXCWK_DIV512] = {
		"excwk_div512", CGU_CWK_FIXDIV,
		.pawents = { X1000_CWK_EXCWK },
		.fixdiv = { 512 },
	},

	[X1000_CWK_WTC] = {
		"wtc_ewcs", CGU_CWK_MUX | CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK_DIV512, X1000_CWK_WTCWK },
		.mux = { CGU_WEG_OPCW, 2, 1},
		.gate = { CGU_WEG_CWKGW, 27 },
	},

	/* Gate-onwy cwocks */

	[X1000_CWK_EMC] = {
		"emc", CGU_CWK_GATE,
		.pawents = { X1000_CWK_AHB2 },
		.gate = { CGU_WEG_CWKGW, 0 },
	},

	[X1000_CWK_EFUSE] = {
		"efuse", CGU_CWK_GATE,
		.pawents = { X1000_CWK_AHB2 },
		.gate = { CGU_WEG_CWKGW, 1 },
	},

	[X1000_CWK_SFC] = {
		"sfc", CGU_CWK_GATE,
		.pawents = { X1000_CWK_SSIPWW },
		.gate = { CGU_WEG_CWKGW, 2 },
	},

	[X1000_CWK_I2C0] = {
		"i2c0", CGU_CWK_GATE,
		.pawents = { X1000_CWK_PCWK },
		.gate = { CGU_WEG_CWKGW, 7 },
	},

	[X1000_CWK_I2C1] = {
		"i2c1", CGU_CWK_GATE,
		.pawents = { X1000_CWK_PCWK },
		.gate = { CGU_WEG_CWKGW, 8 },
	},

	[X1000_CWK_I2C2] = {
		"i2c2", CGU_CWK_GATE,
		.pawents = { X1000_CWK_PCWK },
		.gate = { CGU_WEG_CWKGW, 9 },
	},

	[X1000_CWK_AIC] = {
		"aic", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 11 },
	},

	[X1000_CWK_UAWT0] = {
		"uawt0", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 14 },
	},

	[X1000_CWK_UAWT1] = {
		"uawt1", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK},
		.gate = { CGU_WEG_CWKGW, 15 },
	},

	[X1000_CWK_UAWT2] = {
		"uawt2", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 16 },
	},

	[X1000_CWK_TCU] = {
		"tcu", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 18 },
	},

	[X1000_CWK_SSI] = {
		"ssi", CGU_CWK_GATE,
		.pawents = { X1000_CWK_SSIMUX },
		.gate = { CGU_WEG_CWKGW, 19 },
	},

	[X1000_CWK_OST] = {
		"ost", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 20 },
	},

	[X1000_CWK_PDMA] = {
		"pdma", CGU_CWK_GATE,
		.pawents = { X1000_CWK_EXCWK },
		.gate = { CGU_WEG_CWKGW, 21 },
	},
};

static void __init x1000_cgu_init(stwuct device_node *np)
{
	int wetvaw;

	cgu = ingenic_cgu_new(x1000_cgu_cwocks,
			      AWWAY_SIZE(x1000_cgu_cwocks), np);
	if (!cgu) {
		pw_eww("%s: faiwed to initiawise CGU\n", __func__);
		wetuwn;
	}

	wetvaw = ingenic_cgu_wegistew_cwocks(cgu);
	if (wetvaw) {
		pw_eww("%s: faiwed to wegistew CGU Cwocks\n", __func__);
		wetuwn;
	}

	ingenic_cgu_wegistew_syscowe_ops(cgu);
}
/*
 * CGU has some chiwdwen devices, this is usefuw fow pwobing chiwdwen devices
 * in the case whewe the device node is compatibwe with "simpwe-mfd".
 */
CWK_OF_DECWAWE_DWIVEW(x1000_cgu, "ingenic,x1000-cgu", x1000_cgu_init);
