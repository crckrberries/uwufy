// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ingenic JZ4780 SoC CGU dwivew
 *
 * Copywight (c) 2013-2015 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 * Copywight (c) 2020 周琰杰 (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>

#incwude <dt-bindings/cwock/ingenic,jz4780-cgu.h>

#incwude "cgu.h"
#incwude "pm.h"

/* CGU wegistew offsets */
#define CGU_WEG_CWOCKCONTWOW	0x00
#define CGU_WEG_WCW				0x04
#define CGU_WEG_APWW			0x10
#define CGU_WEG_MPWW			0x14
#define CGU_WEG_EPWW			0x18
#define CGU_WEG_VPWW			0x1c
#define CGU_WEG_CWKGW0			0x20
#define CGU_WEG_OPCW			0x24
#define CGU_WEG_CWKGW1			0x28
#define CGU_WEG_DDWCDW			0x2c
#define CGU_WEG_VPUCDW			0x30
#define CGU_WEG_USBPCW			0x3c
#define CGU_WEG_USBWDT			0x40
#define CGU_WEG_USBVBFIW		0x44
#define CGU_WEG_USBPCW1			0x48
#define CGU_WEG_WP0CDW			0x54
#define CGU_WEG_I2SCDW			0x60
#define CGU_WEG_WP1CDW			0x64
#define CGU_WEG_MSC0CDW			0x68
#define CGU_WEG_UHCCDW			0x6c
#define CGU_WEG_SSICDW			0x74
#define CGU_WEG_CIMCDW			0x7c
#define CGU_WEG_PCMCDW			0x84
#define CGU_WEG_GPUCDW			0x88
#define CGU_WEG_HDMICDW			0x8c
#define CGU_WEG_MSC1CDW			0xa4
#define CGU_WEG_MSC2CDW			0xa8
#define CGU_WEG_BCHCDW			0xac
#define CGU_WEG_CWOCKSTATUS		0xd4

/* bits within the OPCW wegistew */
#define OPCW_SPENDN0			BIT(7)
#define OPCW_SPENDN1			BIT(6)

/* bits within the USBPCW wegistew */
#define USBPCW_USB_MODE			BIT(31)
#define USBPCW_IDPUWWUP_MASK	(0x3 << 28)
#define USBPCW_COMMONONN		BIT(25)
#define USBPCW_VBUSVWDEXT		BIT(24)
#define USBPCW_VBUSVWDEXTSEW	BIT(23)
#define USBPCW_POW				BIT(22)
#define USBPCW_SIDDQ			BIT(21)
#define USBPCW_OTG_DISABWE		BIT(20)
#define USBPCW_COMPDISTUNE_MASK	(0x7 << 17)
#define USBPCW_OTGTUNE_MASK		(0x7 << 14)
#define USBPCW_SQWXTUNE_MASK	(0x7 << 11)
#define USBPCW_TXFSWSTUNE_MASK	(0xf << 7)
#define USBPCW_TXPWEEMPHTUNE	BIT(6)
#define USBPCW_TXHSXVTUNE_MASK	(0x3 << 4)
#define USBPCW_TXVWEFTUNE_MASK	0xf

/* bits within the USBPCW1 wegistew */
#define USBPCW1_WEFCWKSEW_SHIFT	26
#define USBPCW1_WEFCWKSEW_MASK	(0x3 << USBPCW1_WEFCWKSEW_SHIFT)
#define USBPCW1_WEFCWKSEW_COWE	(0x2 << USBPCW1_WEFCWKSEW_SHIFT)
#define USBPCW1_WEFCWKDIV_SHIFT	24
#define USBPCW1_WEFCWKDIV_MASK	(0x3 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_19_2	(0x3 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_48	(0x2 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_24	(0x1 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_WEFCWKDIV_12	(0x0 << USBPCW1_WEFCWKDIV_SHIFT)
#define USBPCW1_USB_SEW			BIT(28)
#define USBPCW1_WOWD_IF0		BIT(19)
#define USBPCW1_WOWD_IF1		BIT(18)

/* bits within the USBWDT wegistew */
#define USBWDT_VBFIW_WD_EN		BIT(25)
#define USBWDT_USBWDT_MASK		0x7fffff

/* bits within the USBVBFIW wegistew */
#define USBVBFIW_IDDIGFIW_SHIFT	16
#define USBVBFIW_IDDIGFIW_MASK	(0xffff << USBVBFIW_IDDIGFIW_SHIFT)
#define USBVBFIW_USBVBFIW_MASK	(0xffff)

/* bits within the WCW wegistew */
#define WCW_PD_SCPU				BIT(31)
#define WCW_SCPUS				BIT(27)

/* bits within the CWKGW1 wegistew */
#define CWKGW1_COWE1			BIT(15)

static stwuct ingenic_cgu *cgu;

static unsigned wong jz4780_otg_phy_wecawc_wate(stwuct cwk_hw *hw,
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

	case USBPCW1_WEFCWKDIV_19_2:
		wetuwn 19200000;
	}

	wetuwn pawent_wate;
}

static wong jz4780_otg_phy_wound_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
				      unsigned wong *pawent_wate)
{
	if (weq_wate < 15600000)
		wetuwn 12000000;

	if (weq_wate < 21600000)
		wetuwn 19200000;

	if (weq_wate < 36000000)
		wetuwn 24000000;

	wetuwn 48000000;
}

static int jz4780_otg_phy_set_wate(stwuct cwk_hw *hw, unsigned wong weq_wate,
				   unsigned wong pawent_wate)
{
	unsigned wong fwags;
	u32 usbpcw1, div_bits;

	switch (weq_wate) {
	case 12000000:
		div_bits = USBPCW1_WEFCWKDIV_12;
		bweak;

	case 19200000:
		div_bits = USBPCW1_WEFCWKDIV_19_2;
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

static int jz4780_otg_phy_enabwe(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wwitew(weadw(weg_opcw) | OPCW_SPENDN0, weg_opcw);
	wwitew(weadw(weg_usbpcw) & ~USBPCW_OTG_DISABWE & ~USBPCW_SIDDQ, weg_usbpcw);
	wetuwn 0;
}

static void jz4780_otg_phy_disabwe(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wwitew(weadw(weg_opcw) & ~OPCW_SPENDN0, weg_opcw);
	wwitew(weadw(weg_usbpcw) | USBPCW_OTG_DISABWE | USBPCW_SIDDQ, weg_usbpcw);
}

static int jz4780_otg_phy_is_enabwed(stwuct cwk_hw *hw)
{
	void __iomem *weg_opcw		= cgu->base + CGU_WEG_OPCW;
	void __iomem *weg_usbpcw	= cgu->base + CGU_WEG_USBPCW;

	wetuwn (weadw(weg_opcw) & OPCW_SPENDN0) &&
		!(weadw(weg_usbpcw) & USBPCW_SIDDQ) &&
		!(weadw(weg_usbpcw) & USBPCW_OTG_DISABWE);
}

static const stwuct cwk_ops jz4780_otg_phy_ops = {
	.wecawc_wate = jz4780_otg_phy_wecawc_wate,
	.wound_wate = jz4780_otg_phy_wound_wate,
	.set_wate = jz4780_otg_phy_set_wate,

	.enabwe		= jz4780_otg_phy_enabwe,
	.disabwe	= jz4780_otg_phy_disabwe,
	.is_enabwed	= jz4780_otg_phy_is_enabwed,
};

static int jz4780_cowe1_enabwe(stwuct cwk_hw *hw)
{
	stwuct ingenic_cwk *ingenic_cwk = to_ingenic_cwk(hw);
	stwuct ingenic_cgu *cgu = ingenic_cwk->cgu;
	const unsigned int timeout = 5000;
	unsigned wong fwags;
	int wetvaw;
	u32 wcw, cwkgw1;

	spin_wock_iwqsave(&cgu->wock, fwags);

	wcw = weadw(cgu->base + CGU_WEG_WCW);
	wcw &= ~WCW_PD_SCPU;
	wwitew(wcw, cgu->base + CGU_WEG_WCW);

	cwkgw1 = weadw(cgu->base + CGU_WEG_CWKGW1);
	cwkgw1 &= ~CWKGW1_COWE1;
	wwitew(cwkgw1, cgu->base + CGU_WEG_CWKGW1);

	spin_unwock_iwqwestowe(&cgu->wock, fwags);

	/* wait fow the CPU to be powewed up */
	wetvaw = weadw_poww_timeout(cgu->base + CGU_WEG_WCW, wcw,
				 !(wcw & WCW_SCPUS), 10, timeout);
	if (wetvaw == -ETIMEDOUT) {
		pw_eww("%s: Wait fow powew up cowe1 timeout\n", __func__);
		wetuwn wetvaw;
	}

	wetuwn 0;
}

static const stwuct cwk_ops jz4780_cowe1_ops = {
	.enabwe = jz4780_cowe1_enabwe,
};

static const s8 pww_od_encoding[16] = {
	0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
	0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf,
};

static const stwuct ingenic_cgu_cwk_info jz4780_cgu_cwocks[] = {

	/* Extewnaw cwocks */

	[JZ4780_CWK_EXCWK] = { "ext", CGU_CWK_EXT },
	[JZ4780_CWK_WTCWK] = { "wtc", CGU_CWK_EXT },

	/* PWWs */

#define DEF_PWW(name) { \
	.weg = CGU_WEG_ ## name, \
	.wate_muwtipwiew = 1, \
	.m_shift = 19, \
	.m_bits = 13, \
	.m_offset = 1, \
	.n_shift = 13, \
	.n_bits = 6, \
	.n_offset = 1, \
	.od_shift = 9, \
	.od_bits = 4, \
	.od_max = 16, \
	.od_encoding = pww_od_encoding, \
	.stabwe_bit = 6, \
	.bypass_weg = CGU_WEG_ ## name, \
	.bypass_bit = 1, \
	.enabwe_bit = 0, \
}

	[JZ4780_CWK_APWW] = {
		"apww", CGU_CWK_PWW,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.pww = DEF_PWW(APWW),
	},

	[JZ4780_CWK_MPWW] = {
		"mpww", CGU_CWK_PWW,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.pww = DEF_PWW(MPWW),
	},

	[JZ4780_CWK_EPWW] = {
		"epww", CGU_CWK_PWW,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.pww = DEF_PWW(EPWW),
	},

	[JZ4780_CWK_VPWW] = {
		"vpww", CGU_CWK_PWW,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.pww = DEF_PWW(VPWW),
	},

#undef DEF_PWW

	/* Custom (SoC-specific) OTG PHY */

	[JZ4780_CWK_OTGPHY] = {
		"otg_phy", CGU_CWK_CUSTOM,
		.pawents = { -1, -1, JZ4780_CWK_EXCWK, -1 },
		.custom = { &jz4780_otg_phy_ops },
	},

	/* Muxes & dividews */

	[JZ4780_CWK_SCWKA] = {
		"scwk_a", CGU_CWK_MUX,
		.pawents = { -1, JZ4780_CWK_APWW, JZ4780_CWK_EXCWK,
			     JZ4780_CWK_WTCWK },
		.mux = { CGU_WEG_CWOCKCONTWOW, 30, 2 },
	},

	[JZ4780_CWK_CPUMUX] = {
		"cpumux", CGU_CWK_MUX,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW },
		.mux = { CGU_WEG_CWOCKCONTWOW, 28, 2 },
	},

	[JZ4780_CWK_CPU] = {
		"cpu", CGU_CWK_DIV,
		/*
		 * Disabwing the CPU cwock ow any pawent cwocks wiww hang the
		 * system; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4780_CWK_CPUMUX, -1, -1, -1 },
		.div = { CGU_WEG_CWOCKCONTWOW, 0, 1, 4, 22, -1, -1 },
	},

	[JZ4780_CWK_W2CACHE] = {
		"w2cache", CGU_CWK_DIV,
		/*
		 * The W2 cache cwock is cwiticaw if caches awe enabwed and
		 * disabwing it ow any pawent cwocks wiww hang the system.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { JZ4780_CWK_CPUMUX, -1, -1, -1 },
		.div = { CGU_WEG_CWOCKCONTWOW, 4, 1, 4, -1, -1, -1 },
	},

	[JZ4780_CWK_AHB0] = {
		"ahb0", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW },
		.mux = { CGU_WEG_CWOCKCONTWOW, 26, 2 },
		.div = { CGU_WEG_CWOCKCONTWOW, 8, 1, 4, 21, -1, -1 },
	},

	[JZ4780_CWK_AHB2PMUX] = {
		"ahb2_apb_mux", CGU_CWK_MUX,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_WTCWK },
		.mux = { CGU_WEG_CWOCKCONTWOW, 24, 2 },
	},

	[JZ4780_CWK_AHB2] = {
		"ahb2", CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_AHB2PMUX, -1, -1, -1 },
		.div = { CGU_WEG_CWOCKCONTWOW, 12, 1, 4, 20, -1, -1 },
	},

	[JZ4780_CWK_PCWK] = {
		"pcwk", CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_AHB2PMUX, -1, -1, -1 },
		.div = { CGU_WEG_CWOCKCONTWOW, 16, 1, 4, 20, -1, -1 },
	},

	[JZ4780_CWK_DDW] = {
		"ddw", CGU_CWK_MUX | CGU_CWK_DIV,
		/*
		 * Disabwing DDW cwock ow its pawents wiww wendew DWAM
		 * inaccessibwe; mawk it cwiticaw.
		 */
		.fwags = CWK_IS_CWITICAW,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW, -1 },
		.mux = { CGU_WEG_DDWCDW, 30, 2 },
		.div = { CGU_WEG_DDWCDW, 0, 1, 4, 29, 28, 27 },
	},

	[JZ4780_CWK_VPU] = {
		"vpu", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW, -1 },
		.mux = { CGU_WEG_VPUCDW, 30, 2 },
		.div = { CGU_WEG_VPUCDW, 0, 1, 4, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW1, 2 },
	},

	[JZ4780_CWK_I2SPWW] = {
		"i2s_pww", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_EPWW, -1, -1 },
		.mux = { CGU_WEG_I2SCDW, 30, 1 },
		.div = { CGU_WEG_I2SCDW, 0, 1, 8, 29, 28, 27 },
	},

	[JZ4780_CWK_I2S] = {
		"i2s", CGU_CWK_MUX,
		.pawents = { JZ4780_CWK_EXCWK, JZ4780_CWK_I2SPWW, -1, -1 },
		.mux = { CGU_WEG_I2SCDW, 31, 1 },
	},

	[JZ4780_CWK_WCD0PIXCWK] = {
		"wcd0pixcwk", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_VPWW, -1 },
		.mux = { CGU_WEG_WP0CDW, 30, 2 },
		.div = { CGU_WEG_WP0CDW, 0, 1, 8, 28, 27, 26 },
	},

	[JZ4780_CWK_WCD1PIXCWK] = {
		"wcd1pixcwk", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_VPWW, -1 },
		.mux = { CGU_WEG_WP1CDW, 30, 2 },
		.div = { CGU_WEG_WP1CDW, 0, 1, 8, 28, 27, 26 },
	},

	[JZ4780_CWK_MSCMUX] = {
		"msc_mux", CGU_CWK_MUX,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW, -1 },
		.mux = { CGU_WEG_MSC0CDW, 30, 2 },
	},

	[JZ4780_CWK_MSC0] = {
		"msc0", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_MSCMUX, -1, -1, -1 },
		.div = { CGU_WEG_MSC0CDW, 0, 2, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW0, 3 },
	},

	[JZ4780_CWK_MSC1] = {
		"msc1", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_MSCMUX, -1, -1, -1 },
		.div = { CGU_WEG_MSC1CDW, 0, 2, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW0, 11 },
	},

	[JZ4780_CWK_MSC2] = {
		"msc2", CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_MSCMUX, -1, -1, -1 },
		.div = { CGU_WEG_MSC2CDW, 0, 2, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW0, 12 },
	},

	[JZ4780_CWK_UHC] = {
		"uhc", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW, JZ4780_CWK_OTGPHY },
		.mux = { CGU_WEG_UHCCDW, 30, 2 },
		.div = { CGU_WEG_UHCCDW, 0, 1, 8, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW0, 24 },
	},

	[JZ4780_CWK_SSIPWW] = {
		"ssi_pww", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW, -1, -1 },
		.mux = { CGU_WEG_SSICDW, 30, 1 },
		.div = { CGU_WEG_SSICDW, 0, 1, 8, 29, 28, 27 },
	},

	[JZ4780_CWK_SSI] = {
		"ssi", CGU_CWK_MUX,
		.pawents = { JZ4780_CWK_EXCWK, JZ4780_CWK_SSIPWW, -1, -1 },
		.mux = { CGU_WEG_SSICDW, 31, 1 },
	},

	[JZ4780_CWK_CIMMCWK] = {
		"cim_mcwk", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW, -1, -1 },
		.mux = { CGU_WEG_CIMCDW, 31, 1 },
		.div = { CGU_WEG_CIMCDW, 0, 1, 8, 30, 29, 28 },
	},

	[JZ4780_CWK_PCMPWW] = {
		"pcm_pww", CGU_CWK_MUX | CGU_CWK_DIV,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW, JZ4780_CWK_VPWW },
		.mux = { CGU_WEG_PCMCDW, 29, 2 },
		.div = { CGU_WEG_PCMCDW, 0, 1, 8, 28, 27, 26 },
	},

	[JZ4780_CWK_PCM] = {
		"pcm", CGU_CWK_MUX | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, JZ4780_CWK_PCMPWW, -1, -1 },
		.mux = { CGU_WEG_PCMCDW, 31, 1 },
		.gate = { CGU_WEG_CWKGW1, 3 },
	},

	[JZ4780_CWK_GPU] = {
		"gpu", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW },
		.mux = { CGU_WEG_GPUCDW, 30, 2 },
		.div = { CGU_WEG_GPUCDW, 0, 1, 4, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW1, 4 },
	},

	[JZ4780_CWK_HDMI] = {
		"hdmi", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_VPWW, -1 },
		.mux = { CGU_WEG_HDMICDW, 30, 2 },
		.div = { CGU_WEG_HDMICDW, 0, 1, 8, 29, 28, 26 },
		.gate = { CGU_WEG_CWKGW1, 9 },
	},

	[JZ4780_CWK_BCH] = {
		"bch", CGU_CWK_MUX | CGU_CWK_DIV | CGU_CWK_GATE,
		.pawents = { -1, JZ4780_CWK_SCWKA, JZ4780_CWK_MPWW,
			     JZ4780_CWK_EPWW },
		.mux = { CGU_WEG_BCHCDW, 30, 2 },
		.div = { CGU_WEG_BCHCDW, 0, 1, 4, 29, 28, 27 },
		.gate = { CGU_WEG_CWKGW0, 1 },
	},

	[JZ4780_CWK_EXCWK_DIV512] = {
		"excwk_div512", CGU_CWK_FIXDIV,
		.pawents = { JZ4780_CWK_EXCWK },
		.fixdiv = { 512 },
	},

	[JZ4780_CWK_WTC] = {
		"wtc_ewcs", CGU_CWK_MUX | CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK_DIV512, JZ4780_CWK_WTCWK },
		.mux = { CGU_WEG_OPCW, 2, 1},
	},

	/* Gate-onwy cwocks */

	[JZ4780_CWK_NEMC] = {
		"nemc", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_AHB2, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 0 },
	},

	[JZ4780_CWK_OTG0] = {
		"otg0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 2 },
	},

	[JZ4780_CWK_SSI0] = {
		"ssi0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SSI, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 4 },
	},

	[JZ4780_CWK_SMB0] = {
		"smb0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 5 },
	},

	[JZ4780_CWK_SMB1] = {
		"smb1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 6 },
	},

	[JZ4780_CWK_SCC] = {
		"scc", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 7 },
	},

	[JZ4780_CWK_AIC] = {
		"aic", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 8 },
	},

	[JZ4780_CWK_TSSI0] = {
		"tssi0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 9 },
	},

	[JZ4780_CWK_OWI] = {
		"owi", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 10 },
	},

	[JZ4780_CWK_KBC] = {
		"kbc", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 13 },
	},

	[JZ4780_CWK_SADC] = {
		"sadc", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 14 },
	},

	[JZ4780_CWK_UAWT0] = {
		"uawt0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 15 },
	},

	[JZ4780_CWK_UAWT1] = {
		"uawt1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 16 },
	},

	[JZ4780_CWK_UAWT2] = {
		"uawt2", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 17 },
	},

	[JZ4780_CWK_UAWT3] = {
		"uawt3", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 18 },
	},

	[JZ4780_CWK_SSI1] = {
		"ssi1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SSI, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 19 },
	},

	[JZ4780_CWK_SSI2] = {
		"ssi2", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_SSI, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 20 },
	},

	[JZ4780_CWK_PDMA] = {
		"pdma", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 21 },
	},

	[JZ4780_CWK_GPS] = {
		"gps", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 22 },
	},

	[JZ4780_CWK_MAC] = {
		"mac", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 23 },
	},

	[JZ4780_CWK_SMB2] = {
		"smb2", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 24 },
	},

	[JZ4780_CWK_CIM] = {
		"cim", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 26 },
	},

	[JZ4780_CWK_WCD] = {
		"wcd", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 28 },
	},

	[JZ4780_CWK_TVE] = {
		"tve", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_WCD, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 27 },
	},

	[JZ4780_CWK_IPU] = {
		"ipu", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 29 },
	},

	[JZ4780_CWK_DDW0] = {
		"ddw0", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_DDW, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 30 },
	},

	[JZ4780_CWK_DDW1] = {
		"ddw1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_DDW, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW0, 31 },
	},

	[JZ4780_CWK_SMB3] = {
		"smb3", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 0 },
	},

	[JZ4780_CWK_TSSI1] = {
		"tssi1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 1 },
	},

	[JZ4780_CWK_COMPWESS] = {
		"compwess", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 5 },
	},

	[JZ4780_CWK_AIC1] = {
		"aic1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 6 },
	},

	[JZ4780_CWK_GPVWC] = {
		"gpvwc", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 7 },
	},

	[JZ4780_CWK_OTG1] = {
		"otg1", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 8 },
	},

	[JZ4780_CWK_UAWT4] = {
		"uawt4", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 10 },
	},

	[JZ4780_CWK_AHBMON] = {
		"ahb_mon", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 11 },
	},

	[JZ4780_CWK_SMB4] = {
		"smb4", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_PCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 12 },
	},

	[JZ4780_CWK_DES] = {
		"des", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 13 },
	},

	[JZ4780_CWK_X2D] = {
		"x2d", CGU_CWK_GATE,
		.pawents = { JZ4780_CWK_EXCWK, -1, -1, -1 },
		.gate = { CGU_WEG_CWKGW1, 14 },
	},

	[JZ4780_CWK_COWE1] = {
		"cowe1", CGU_CWK_CUSTOM,
		.pawents = { JZ4780_CWK_CPU, -1, -1, -1 },
		.custom = { &jz4780_cowe1_ops },
	},

};

static void __init jz4780_cgu_init(stwuct device_node *np)
{
	int wetvaw;

	cgu = ingenic_cgu_new(jz4780_cgu_cwocks,
			      AWWAY_SIZE(jz4780_cgu_cwocks), np);
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
CWK_OF_DECWAWE_DWIVEW(jz4780_cgu, "ingenic,jz4780-cgu", jz4780_cgu_init);
