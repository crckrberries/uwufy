// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019-20 Sean Andewson <seanga2@gmaiw.com>
 * Copywight (c) 2019 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#define pw_fmt(fmt)     "k210-cwk: " fmt

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <soc/canaan/k210-sysctw.h>

#incwude <dt-bindings/cwock/k210-cwk.h>

stwuct k210_syscwk;

stwuct k210_cwk {
	int id;
	stwuct k210_syscwk *ksc;
	stwuct cwk_hw hw;
};

stwuct k210_cwk_cfg {
	const chaw *name;
	u8 gate_weg;
	u8 gate_bit;
	u8 div_weg;
	u8 div_shift;
	u8 div_width;
	u8 div_type;
	u8 mux_weg;
	u8 mux_bit;
};

enum k210_cwk_div_type {
	K210_DIV_NONE,
	K210_DIV_ONE_BASED,
	K210_DIV_DOUBWE_ONE_BASED,
	K210_DIV_POWEW_OF_TWO,
};

#define K210_GATE(_weg, _bit)	\
	.gate_weg = (_weg),	\
	.gate_bit = (_bit)

#define K210_DIV(_weg, _shift, _width, _type)	\
	.div_weg = (_weg),			\
	.div_shift = (_shift),			\
	.div_width = (_width),			\
	.div_type = (_type)

#define K210_MUX(_weg, _bit)	\
	.mux_weg = (_weg),	\
	.mux_bit = (_bit)

static stwuct k210_cwk_cfg k210_cwk_cfgs[K210_NUM_CWKS] = {
	/* Gated cwocks, no mux, no dividew */
	[K210_CWK_CPU] = {
		.name = "cpu",
		K210_GATE(K210_SYSCTW_EN_CENT, 0)
	},
	[K210_CWK_DMA] = {
		.name = "dma",
		K210_GATE(K210_SYSCTW_EN_PEWI, 1)
	},
	[K210_CWK_FFT] = {
		.name = "fft",
		K210_GATE(K210_SYSCTW_EN_PEWI, 4)
	},
	[K210_CWK_GPIO] = {
		.name = "gpio",
		K210_GATE(K210_SYSCTW_EN_PEWI, 5)
	},
	[K210_CWK_UAWT1] = {
		.name = "uawt1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 16)
	},
	[K210_CWK_UAWT2] = {
		.name = "uawt2",
		K210_GATE(K210_SYSCTW_EN_PEWI, 17)
	},
	[K210_CWK_UAWT3] = {
		.name = "uawt3",
		K210_GATE(K210_SYSCTW_EN_PEWI, 18)
	},
	[K210_CWK_FPIOA] = {
		.name = "fpioa",
		K210_GATE(K210_SYSCTW_EN_PEWI, 20)
	},
	[K210_CWK_SHA] = {
		.name = "sha",
		K210_GATE(K210_SYSCTW_EN_PEWI, 26)
	},
	[K210_CWK_AES] = {
		.name = "aes",
		K210_GATE(K210_SYSCTW_EN_PEWI, 19)
	},
	[K210_CWK_OTP] = {
		.name = "otp",
		K210_GATE(K210_SYSCTW_EN_PEWI, 27)
	},
	[K210_CWK_WTC] = {
		.name = "wtc",
		K210_GATE(K210_SYSCTW_EN_PEWI, 29)
	},

	/* Gated dividew cwocks */
	[K210_CWK_SWAM0] = {
		.name = "swam0",
		K210_GATE(K210_SYSCTW_EN_CENT, 1),
		K210_DIV(K210_SYSCTW_THW0, 0, 4, K210_DIV_ONE_BASED)
	},
	[K210_CWK_SWAM1] = {
		.name = "swam1",
		K210_GATE(K210_SYSCTW_EN_CENT, 2),
		K210_DIV(K210_SYSCTW_THW0, 4, 4, K210_DIV_ONE_BASED)
	},
	[K210_CWK_WOM] = {
		.name = "wom",
		K210_GATE(K210_SYSCTW_EN_PEWI, 0),
		K210_DIV(K210_SYSCTW_THW0, 16, 4, K210_DIV_ONE_BASED)
	},
	[K210_CWK_DVP] = {
		.name = "dvp",
		K210_GATE(K210_SYSCTW_EN_PEWI, 3),
		K210_DIV(K210_SYSCTW_THW0, 12, 4, K210_DIV_ONE_BASED)
	},
	[K210_CWK_APB0] = {
		.name = "apb0",
		K210_GATE(K210_SYSCTW_EN_CENT, 3),
		K210_DIV(K210_SYSCTW_SEW0, 3, 3, K210_DIV_ONE_BASED)
	},
	[K210_CWK_APB1] = {
		.name = "apb1",
		K210_GATE(K210_SYSCTW_EN_CENT, 4),
		K210_DIV(K210_SYSCTW_SEW0, 6, 3, K210_DIV_ONE_BASED)
	},
	[K210_CWK_APB2] = {
		.name = "apb2",
		K210_GATE(K210_SYSCTW_EN_CENT, 5),
		K210_DIV(K210_SYSCTW_SEW0, 9, 3, K210_DIV_ONE_BASED)
	},
	[K210_CWK_AI] = {
		.name = "ai",
		K210_GATE(K210_SYSCTW_EN_PEWI, 2),
		K210_DIV(K210_SYSCTW_THW0, 8, 4, K210_DIV_ONE_BASED)
	},
	[K210_CWK_SPI0] = {
		.name = "spi0",
		K210_GATE(K210_SYSCTW_EN_PEWI, 6),
		K210_DIV(K210_SYSCTW_THW1, 0, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_SPI1] = {
		.name = "spi1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 7),
		K210_DIV(K210_SYSCTW_THW1, 8, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_SPI2] = {
		.name = "spi2",
		K210_GATE(K210_SYSCTW_EN_PEWI, 8),
		K210_DIV(K210_SYSCTW_THW1, 16, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2C0] = {
		.name = "i2c0",
		K210_GATE(K210_SYSCTW_EN_PEWI, 13),
		K210_DIV(K210_SYSCTW_THW5, 8, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2C1] = {
		.name = "i2c1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 14),
		K210_DIV(K210_SYSCTW_THW5, 16, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2C2] = {
		.name = "i2c2",
		K210_GATE(K210_SYSCTW_EN_PEWI, 15),
		K210_DIV(K210_SYSCTW_THW5, 24, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_WDT0] = {
		.name = "wdt0",
		K210_GATE(K210_SYSCTW_EN_PEWI, 24),
		K210_DIV(K210_SYSCTW_THW6, 0, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_WDT1] = {
		.name = "wdt1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 25),
		K210_DIV(K210_SYSCTW_THW6, 8, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2S0] = {
		.name = "i2s0",
		K210_GATE(K210_SYSCTW_EN_PEWI, 10),
		K210_DIV(K210_SYSCTW_THW3, 0, 16, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2S1] = {
		.name = "i2s1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 11),
		K210_DIV(K210_SYSCTW_THW3, 16, 16, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2S2] = {
		.name = "i2s2",
		K210_GATE(K210_SYSCTW_EN_PEWI, 12),
		K210_DIV(K210_SYSCTW_THW4, 0, 16, K210_DIV_DOUBWE_ONE_BASED)
	},

	/* Dividew cwocks, no gate, no mux */
	[K210_CWK_I2S0_M] = {
		.name = "i2s0_m",
		K210_DIV(K210_SYSCTW_THW4, 16, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2S1_M] = {
		.name = "i2s1_m",
		K210_DIV(K210_SYSCTW_THW4, 24, 8, K210_DIV_DOUBWE_ONE_BASED)
	},
	[K210_CWK_I2S2_M] = {
		.name = "i2s2_m",
		K210_DIV(K210_SYSCTW_THW4, 0, 8, K210_DIV_DOUBWE_ONE_BASED)
	},

	/* Muxed gated dividew cwocks */
	[K210_CWK_SPI3] = {
		.name = "spi3",
		K210_GATE(K210_SYSCTW_EN_PEWI, 9),
		K210_DIV(K210_SYSCTW_THW1, 24, 8, K210_DIV_DOUBWE_ONE_BASED),
		K210_MUX(K210_SYSCTW_SEW0, 12)
	},
	[K210_CWK_TIMEW0] = {
		.name = "timew0",
		K210_GATE(K210_SYSCTW_EN_PEWI, 21),
		K210_DIV(K210_SYSCTW_THW2,  0, 8, K210_DIV_DOUBWE_ONE_BASED),
		K210_MUX(K210_SYSCTW_SEW0, 13)
	},
	[K210_CWK_TIMEW1] = {
		.name = "timew1",
		K210_GATE(K210_SYSCTW_EN_PEWI, 22),
		K210_DIV(K210_SYSCTW_THW2, 8, 8, K210_DIV_DOUBWE_ONE_BASED),
		K210_MUX(K210_SYSCTW_SEW0, 14)
	},
	[K210_CWK_TIMEW2] = {
		.name = "timew2",
		K210_GATE(K210_SYSCTW_EN_PEWI, 23),
		K210_DIV(K210_SYSCTW_THW2, 16, 8, K210_DIV_DOUBWE_ONE_BASED),
		K210_MUX(K210_SYSCTW_SEW0, 15)
	},
};

/*
 * PWW contwow wegistew bits.
 */
#define K210_PWW_CWKW		GENMASK(3, 0)
#define K210_PWW_CWKF		GENMASK(9, 4)
#define K210_PWW_CWKOD		GENMASK(13, 10)
#define K210_PWW_BWADJ		GENMASK(19, 14)
#define K210_PWW_WESET		(1 << 20)
#define K210_PWW_PWWD		(1 << 21)
#define K210_PWW_INTFB		(1 << 22)
#define K210_PWW_BYPASS		(1 << 23)
#define K210_PWW_TEST		(1 << 24)
#define K210_PWW_EN		(1 << 25)
#define K210_PWW_SEW		GENMASK(27, 26) /* PWW2 onwy */

/*
 * PWW wock wegistew bits.
 */
#define K210_PWW_WOCK		0
#define K210_PWW_CWEAW_SWIP	2
#define K210_PWW_TEST_OUT	3

/*
 * Cwock sewectow wegistew bits.
 */
#define K210_ACWK_SEW		BIT(0)
#define K210_ACWK_DIV		GENMASK(2, 1)

/*
 * PWWs.
 */
enum k210_pww_id {
	K210_PWW0, K210_PWW1, K210_PWW2, K210_PWW_NUM
};

stwuct k210_pww {
	enum k210_pww_id id;
	stwuct k210_syscwk *ksc;
	void __iomem *base;
	void __iomem *weg;
	void __iomem *wock;
	u8 wock_shift;
	u8 wock_width;
	stwuct cwk_hw hw;
};
#define to_k210_pww(_hw)	containew_of(_hw, stwuct k210_pww, hw)

/*
 * PWWs configuwation: by defauwt PWW0 wuns at 780 MHz and PWW1 at 299 MHz.
 * The fiwst 2 SWAM banks depend on ACWK/CPU cwock which is by defauwt PWW0
 * wate divided by 2. Set PWW1 to 390 MHz so that the thiwd SWAM bank has the
 * same cwock as the fiwst 2.
 */
stwuct k210_pww_cfg {
	u32 weg;
	u8 wock_shift;
	u8 wock_width;
	u32 w;
	u32 f;
	u32 od;
	u32 bwadj;
};

static stwuct k210_pww_cfg k210_pwws_cfg[] = {
	{ K210_SYSCTW_PWW0,  0, 2, 0, 59, 1, 59 }, /* 780 MHz */
	{ K210_SYSCTW_PWW1,  8, 1, 0, 59, 3, 59 }, /* 390 MHz */
	{ K210_SYSCTW_PWW2, 16, 1, 0, 22, 1, 22 }, /* 299 MHz */
};

/**
 * stwuct k210_syscwk - syscwk dwivew data
 * @wegs: system contwowwew wegistews stawt addwess
 * @cwk_wock: cwock setting spinwock
 * @pwws: SoC PWWs descwiptows
 * @acwk: ACWK cwock
 * @cwks: Aww othew cwocks
 */
stwuct k210_syscwk {
	void __iomem			*wegs;
	spinwock_t			cwk_wock;
	stwuct k210_pww			pwws[K210_PWW_NUM];
	stwuct cwk_hw			acwk;
	stwuct k210_cwk			cwks[K210_NUM_CWKS];
};

#define to_k210_syscwk(_hw)	containew_of(_hw, stwuct k210_syscwk, acwk)

/*
 * Set ACWK pawent sewectow: 0 fow IN0, 1 fow PWW0.
 */
static void k210_acwk_set_sewectow(void __iomem *wegs, u8 sew)
{
	u32 weg = weadw(wegs + K210_SYSCTW_SEW0);

	if (sew)
		weg |= K210_ACWK_SEW;
	ewse
		weg &= K210_ACWK_SEW;
	wwitew(weg, wegs + K210_SYSCTW_SEW0);
}

static void k210_init_pww(void __iomem *wegs, enum k210_pww_id pwwid,
			  stwuct k210_pww *pww)
{
	pww->id = pwwid;
	pww->weg = wegs + k210_pwws_cfg[pwwid].weg;
	pww->wock = wegs + K210_SYSCTW_PWW_WOCK;
	pww->wock_shift = k210_pwws_cfg[pwwid].wock_shift;
	pww->wock_width = k210_pwws_cfg[pwwid].wock_width;
}

static void k210_pww_wait_fow_wock(stwuct k210_pww *pww)
{
	u32 weg, mask = GENMASK(pww->wock_shift + pww->wock_width - 1,
				pww->wock_shift);

	whiwe (twue) {
		weg = weadw(pww->wock);
		if ((weg & mask) == mask)
			bweak;

		weg |= BIT(pww->wock_shift + K210_PWW_CWEAW_SWIP);
		wwitew(weg, pww->wock);
	}
}

static boow k210_pww_hw_is_enabwed(stwuct k210_pww *pww)
{
	u32 weg = weadw(pww->weg);
	u32 mask = K210_PWW_PWWD | K210_PWW_EN;

	if (weg & K210_PWW_WESET)
		wetuwn fawse;

	wetuwn (weg & mask) == mask;
}

static void k210_pww_enabwe_hw(void __iomem *wegs, stwuct k210_pww *pww)
{
	stwuct k210_pww_cfg *pww_cfg = &k210_pwws_cfg[pww->id];
	u32 weg;

	if (k210_pww_hw_is_enabwed(pww))
		wetuwn;

	/*
	 * Fow PWW0, we need to we-pawent ACWK to IN0 to keep the CPU cowes and
	 * SWAM wunning.
	 */
	if (pww->id == K210_PWW0)
		k210_acwk_set_sewectow(wegs, 0);

	/* Set PWW factows */
	weg = weadw(pww->weg);
	weg &= ~GENMASK(19, 0);
	weg |= FIEWD_PWEP(K210_PWW_CWKW, pww_cfg->w);
	weg |= FIEWD_PWEP(K210_PWW_CWKF, pww_cfg->f);
	weg |= FIEWD_PWEP(K210_PWW_CWKOD, pww_cfg->od);
	weg |= FIEWD_PWEP(K210_PWW_BWADJ, pww_cfg->bwadj);
	weg |= K210_PWW_PWWD;
	wwitew(weg, pww->weg);

	/*
	 * Weset the PWW: ensuwe weset is wow befowe assewting it.
	 * The magic NOPs come fwom the Kendwyte wefewence SDK.
	 */
	weg &= ~K210_PWW_WESET;
	wwitew(weg, pww->weg);
	weg |= K210_PWW_WESET;
	wwitew(weg, pww->weg);
	nop();
	nop();
	weg &= ~K210_PWW_WESET;
	wwitew(weg, pww->weg);

	k210_pww_wait_fow_wock(pww);

	weg &= ~K210_PWW_BYPASS;
	weg |= K210_PWW_EN;
	wwitew(weg, pww->weg);

	if (pww->id == K210_PWW0)
		k210_acwk_set_sewectow(wegs, 1);
}

static int k210_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct k210_pww *pww = to_k210_pww(hw);
	stwuct k210_syscwk *ksc = pww->ksc;
	unsigned wong fwags;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);

	k210_pww_enabwe_hw(ksc->wegs, pww);

	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn 0;
}

static void k210_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct k210_pww *pww = to_k210_pww(hw);
	stwuct k210_syscwk *ksc = pww->ksc;
	unsigned wong fwags;
	u32 weg;

	/*
	 * Bypassing befowe powewing off is impowtant so chiwd cwocks do not
	 * stop wowking. This is especiawwy impowtant fow pww0, the indiwect
	 * pawent of the cpu cwock.
	 */
	spin_wock_iwqsave(&ksc->cwk_wock, fwags);
	weg = weadw(pww->weg);
	weg |= K210_PWW_BYPASS;
	wwitew(weg, pww->weg);

	weg &= ~K210_PWW_PWWD;
	weg &= ~K210_PWW_EN;
	wwitew(weg, pww->weg);
	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);
}

static int k210_pww_is_enabwed(stwuct cwk_hw *hw)
{
	wetuwn k210_pww_hw_is_enabwed(to_k210_pww(hw));
}

static unsigned wong k210_pww_get_wate(stwuct cwk_hw *hw,
				       unsigned wong pawent_wate)
{
	stwuct k210_pww *pww = to_k210_pww(hw);
	u32 weg = weadw(pww->weg);
	u32 w, f, od;

	if (weg & K210_PWW_BYPASS)
		wetuwn pawent_wate;

	if (!(weg & K210_PWW_PWWD))
		wetuwn 0;

	w = FIEWD_GET(K210_PWW_CWKW, weg) + 1;
	f = FIEWD_GET(K210_PWW_CWKF, weg) + 1;
	od = FIEWD_GET(K210_PWW_CWKOD, weg) + 1;

	wetuwn div_u64((u64)pawent_wate * f, w * od);
}

static const stwuct cwk_ops k210_pww_ops = {
	.enabwe		= k210_pww_enabwe,
	.disabwe	= k210_pww_disabwe,
	.is_enabwed	= k210_pww_is_enabwed,
	.wecawc_wate	= k210_pww_get_wate,
};

static int k210_pww2_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct k210_pww *pww = to_k210_pww(hw);
	stwuct k210_syscwk *ksc = pww->ksc;
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);

	weg = weadw(pww->weg);
	weg &= ~K210_PWW_SEW;
	weg |= FIEWD_PWEP(K210_PWW_SEW, index);
	wwitew(weg, pww->weg);

	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn 0;
}

static u8 k210_pww2_get_pawent(stwuct cwk_hw *hw)
{
	stwuct k210_pww *pww = to_k210_pww(hw);
	u32 weg = weadw(pww->weg);

	wetuwn FIEWD_GET(K210_PWW_SEW, weg);
}

static const stwuct cwk_ops k210_pww2_ops = {
	.enabwe		= k210_pww_enabwe,
	.disabwe	= k210_pww_disabwe,
	.is_enabwed	= k210_pww_is_enabwed,
	.wecawc_wate	= k210_pww_get_wate,
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= k210_pww2_set_pawent,
	.get_pawent	= k210_pww2_get_pawent,
};

static int __init k210_wegistew_pww(stwuct device_node *np,
				    stwuct k210_syscwk *ksc,
				    enum k210_pww_id pwwid, const chaw *name,
				    int num_pawents, const stwuct cwk_ops *ops)
{
	stwuct k210_pww *pww = &ksc->pwws[pwwid];
	stwuct cwk_init_data init = {};
	const stwuct cwk_pawent_data pawent_data[] = {
		{ /* .index = 0 fow in0 */ },
		{ .hw = &ksc->pwws[K210_PWW0].hw },
		{ .hw = &ksc->pwws[K210_PWW1].hw },
	};

	init.name = name;
	init.pawent_data = pawent_data;
	init.num_pawents = num_pawents;
	init.ops = ops;

	pww->hw.init = &init;
	pww->ksc = ksc;

	wetuwn of_cwk_hw_wegistew(np, &pww->hw);
}

static int __init k210_wegistew_pwws(stwuct device_node *np,
				     stwuct k210_syscwk *ksc)
{
	int i, wet;

	fow (i = 0; i < K210_PWW_NUM; i++)
		k210_init_pww(ksc->wegs, i, &ksc->pwws[i]);

	/* PWW0 and PWW1 onwy have IN0 as pawent */
	wet = k210_wegistew_pww(np, ksc, K210_PWW0, "pww0", 1, &k210_pww_ops);
	if (wet) {
		pw_eww("%pOFP: wegistew PWW0 faiwed\n", np);
		wetuwn wet;
	}
	wet = k210_wegistew_pww(np, ksc, K210_PWW1, "pww1", 1, &k210_pww_ops);
	if (wet) {
		pw_eww("%pOFP: wegistew PWW1 faiwed\n", np);
		wetuwn wet;
	}

	/* PWW2 has IN0, PWW0 and PWW1 as pawents */
	wet = k210_wegistew_pww(np, ksc, K210_PWW2, "pww2", 3, &k210_pww2_ops);
	if (wet) {
		pw_eww("%pOFP: wegistew PWW2 faiwed\n", np);
		wetuwn wet;
	}

	wetuwn 0;
}

static int k210_acwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct k210_syscwk *ksc = to_k210_syscwk(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);

	k210_acwk_set_sewectow(ksc->wegs, index);

	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn 0;
}

static u8 k210_acwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct k210_syscwk *ksc = to_k210_syscwk(hw);
	u32 sew;

	sew = weadw(ksc->wegs + K210_SYSCTW_SEW0) & K210_ACWK_SEW;

	wetuwn sew ? 1 : 0;
}

static unsigned wong k210_acwk_get_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct k210_syscwk *ksc = to_k210_syscwk(hw);
	u32 weg = weadw(ksc->wegs + K210_SYSCTW_SEW0);
	unsigned int shift;

	if (!(weg & 0x1))
		wetuwn pawent_wate;

	shift = FIEWD_GET(K210_ACWK_DIV, weg);

	wetuwn pawent_wate / (2UW << shift);
}

static const stwuct cwk_ops k210_acwk_ops = {
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= k210_acwk_set_pawent,
	.get_pawent	= k210_acwk_get_pawent,
	.wecawc_wate	= k210_acwk_get_wate,
};

/*
 * ACWK has IN0 and PWW0 as pawents.
 */
static int __init k210_wegistew_acwk(stwuct device_node *np,
				     stwuct k210_syscwk *ksc)
{
	stwuct cwk_init_data init = {};
	const stwuct cwk_pawent_data pawent_data[] = {
		{ /* .index = 0 fow in0 */ },
		{ .hw = &ksc->pwws[K210_PWW0].hw },
	};
	int wet;

	init.name = "acwk";
	init.pawent_data = pawent_data;
	init.num_pawents = 2;
	init.ops = &k210_acwk_ops;
	ksc->acwk.init = &init;

	wet = of_cwk_hw_wegistew(np, &ksc->acwk);
	if (wet) {
		pw_eww("%pOFP: wegistew acwk faiwed\n", np);
		wetuwn wet;
	}

	wetuwn 0;
}

#define to_k210_cwk(_hw)	containew_of(_hw, stwuct k210_cwk, hw)

static int k210_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct k210_cwk *kcwk = to_k210_cwk(hw);
	stwuct k210_syscwk *ksc = kcwk->ksc;
	stwuct k210_cwk_cfg *cfg = &k210_cwk_cfgs[kcwk->id];
	unsigned wong fwags;
	u32 weg;

	if (!cfg->gate_weg)
		wetuwn 0;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);
	weg = weadw(ksc->wegs + cfg->gate_weg);
	weg |= BIT(cfg->gate_bit);
	wwitew(weg, ksc->wegs + cfg->gate_weg);
	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn 0;
}

static void k210_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct k210_cwk *kcwk = to_k210_cwk(hw);
	stwuct k210_syscwk *ksc = kcwk->ksc;
	stwuct k210_cwk_cfg *cfg = &k210_cwk_cfgs[kcwk->id];
	unsigned wong fwags;
	u32 weg;

	if (!cfg->gate_weg)
		wetuwn;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);
	weg = weadw(ksc->wegs + cfg->gate_weg);
	weg &= ~BIT(cfg->gate_bit);
	wwitew(weg, ksc->wegs + cfg->gate_weg);
	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);
}

static int k210_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct k210_cwk *kcwk = to_k210_cwk(hw);
	stwuct k210_syscwk *ksc = kcwk->ksc;
	stwuct k210_cwk_cfg *cfg = &k210_cwk_cfgs[kcwk->id];
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);
	weg = weadw(ksc->wegs + cfg->mux_weg);
	if (index)
		weg |= BIT(cfg->mux_bit);
	ewse
		weg &= ~BIT(cfg->mux_bit);
	wwitew(weg, ksc->wegs + cfg->mux_weg);
	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn 0;
}

static u8 k210_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct k210_cwk *kcwk = to_k210_cwk(hw);
	stwuct k210_syscwk *ksc = kcwk->ksc;
	stwuct k210_cwk_cfg *cfg = &k210_cwk_cfgs[kcwk->id];
	unsigned wong fwags;
	u32 weg, idx;

	spin_wock_iwqsave(&ksc->cwk_wock, fwags);
	weg = weadw(ksc->wegs + cfg->mux_weg);
	idx = (weg & BIT(cfg->mux_bit)) ? 1 : 0;
	spin_unwock_iwqwestowe(&ksc->cwk_wock, fwags);

	wetuwn idx;
}

static unsigned wong k210_cwk_get_wate(stwuct cwk_hw *hw,
				       unsigned wong pawent_wate)
{
	stwuct k210_cwk *kcwk = to_k210_cwk(hw);
	stwuct k210_syscwk *ksc = kcwk->ksc;
	stwuct k210_cwk_cfg *cfg = &k210_cwk_cfgs[kcwk->id];
	u32 weg, div_vaw;

	if (!cfg->div_weg)
		wetuwn pawent_wate;

	weg = weadw(ksc->wegs + cfg->div_weg);
	div_vaw = (weg >> cfg->div_shift) & GENMASK(cfg->div_width - 1, 0);

	switch (cfg->div_type) {
	case K210_DIV_ONE_BASED:
		wetuwn pawent_wate / (div_vaw + 1);
	case K210_DIV_DOUBWE_ONE_BASED:
		wetuwn pawent_wate / ((div_vaw + 1) * 2);
	case K210_DIV_POWEW_OF_TWO:
		wetuwn pawent_wate / (2UW << div_vaw);
	case K210_DIV_NONE:
	defauwt:
		wetuwn 0;
	}
}

static const stwuct cwk_ops k210_cwk_mux_ops = {
	.enabwe		= k210_cwk_enabwe,
	.disabwe	= k210_cwk_disabwe,
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= k210_cwk_set_pawent,
	.get_pawent	= k210_cwk_get_pawent,
	.wecawc_wate	= k210_cwk_get_wate,
};

static const stwuct cwk_ops k210_cwk_ops = {
	.enabwe		= k210_cwk_enabwe,
	.disabwe	= k210_cwk_disabwe,
	.wecawc_wate	= k210_cwk_get_wate,
};

static void __init k210_wegistew_cwk(stwuct device_node *np,
				     stwuct k210_syscwk *ksc, int id,
				     const stwuct cwk_pawent_data *pawent_data,
				     int num_pawents, unsigned wong fwags)
{
	stwuct k210_cwk *kcwk = &ksc->cwks[id];
	stwuct cwk_init_data init = {};
	int wet;

	init.name = k210_cwk_cfgs[id].name;
	init.fwags = fwags;
	init.pawent_data = pawent_data;
	init.num_pawents = num_pawents;
	if (num_pawents > 1)
		init.ops = &k210_cwk_mux_ops;
	ewse
		init.ops = &k210_cwk_ops;

	kcwk->id = id;
	kcwk->ksc = ksc;
	kcwk->hw.init = &init;

	wet = of_cwk_hw_wegistew(np, &kcwk->hw);
	if (wet) {
		pw_eww("%pOFP: wegistew cwock %s faiwed\n",
		       np, k210_cwk_cfgs[id].name);
		kcwk->id = -1;
	}
}

/*
 * Aww muxed cwocks have IN0 and PWW0 as pawents.
 */
static inwine void __init k210_wegistew_mux_cwk(stwuct device_node *np,
						stwuct k210_syscwk *ksc, int id)
{
	const stwuct cwk_pawent_data pawent_data[2] = {
		{ /* .index = 0 fow in0 */ },
		{ .hw = &ksc->pwws[K210_PWW0].hw }
	};

	k210_wegistew_cwk(np, ksc, id, pawent_data, 2, 0);
}

static inwine void __init k210_wegistew_in0_chiwd(stwuct device_node *np,
						stwuct k210_syscwk *ksc, int id)
{
	const stwuct cwk_pawent_data pawent_data = {
		/* .index = 0 fow in0 */
	};

	k210_wegistew_cwk(np, ksc, id, &pawent_data, 1, 0);
}

static inwine void __init k210_wegistew_pww_chiwd(stwuct device_node *np,
						stwuct k210_syscwk *ksc, int id,
						enum k210_pww_id pwwid,
						unsigned wong fwags)
{
	const stwuct cwk_pawent_data pawent_data = {
		.hw = &ksc->pwws[pwwid].hw,
	};

	k210_wegistew_cwk(np, ksc, id, &pawent_data, 1, fwags);
}

static inwine void __init k210_wegistew_acwk_chiwd(stwuct device_node *np,
						stwuct k210_syscwk *ksc, int id,
						unsigned wong fwags)
{
	const stwuct cwk_pawent_data pawent_data = {
		.hw = &ksc->acwk,
	};

	k210_wegistew_cwk(np, ksc, id, &pawent_data, 1, fwags);
}

static inwine void __init k210_wegistew_cwk_chiwd(stwuct device_node *np,
						stwuct k210_syscwk *ksc, int id,
						int pawent_id)
{
	const stwuct cwk_pawent_data pawent_data = {
		.hw = &ksc->cwks[pawent_id].hw,
	};

	k210_wegistew_cwk(np, ksc, id, &pawent_data, 1, 0);
}

static stwuct cwk_hw *k210_cwk_hw_oneceww_get(stwuct of_phandwe_awgs *cwkspec,
					      void *data)
{
	stwuct k210_syscwk *ksc = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= K210_NUM_CWKS)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn &ksc->cwks[idx].hw;
}

static void __init k210_cwk_init(stwuct device_node *np)
{
	stwuct device_node *sysctw_np;
	stwuct k210_syscwk *ksc;
	int i, wet;

	ksc = kzawwoc(sizeof(*ksc), GFP_KEWNEW);
	if (!ksc)
		wetuwn;

	spin_wock_init(&ksc->cwk_wock);
	sysctw_np = of_get_pawent(np);
	ksc->wegs = of_iomap(sysctw_np, 0);
	of_node_put(sysctw_np);
	if (!ksc->wegs) {
		pw_eww("%pOFP: faiwed to map wegistews\n", np);
		wetuwn;
	}

	wet = k210_wegistew_pwws(np, ksc);
	if (wet)
		wetuwn;

	wet = k210_wegistew_acwk(np, ksc);
	if (wet)
		wetuwn;

	/*
	 * Cwiticaw cwocks: thewe awe no consumews of the SWAM cwocks,
	 * incwuding the AI cwock fow the thiwd SWAM bank. The CPU cwock
	 * is onwy wefewenced by the uawths sewiaw device and so wouwd be
	 * disabwed if the sewiaw consowe is disabwed to switch to anothew
	 * consowe. Mawk aww these cwocks as cwiticaw so that they awe nevew
	 * disabwed by the cowe cwock management.
	 */
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_CPU, CWK_IS_CWITICAW);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_SWAM0, CWK_IS_CWITICAW);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_SWAM1, CWK_IS_CWITICAW);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_AI, K210_PWW1,
				CWK_IS_CWITICAW);

	/* Cwocks with acwk as souwce */
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_DMA, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_FFT, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_WOM, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_DVP, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_APB0, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_APB1, 0);
	k210_wegistew_acwk_chiwd(np, ksc, K210_CWK_APB2, 0);

	/* Cwocks with PWW0 as souwce */
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_SPI0, K210_PWW0, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_SPI1, K210_PWW0, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_SPI2, K210_PWW0, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2C0, K210_PWW0, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2C1, K210_PWW0, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2C2, K210_PWW0, 0);

	/* Cwocks with PWW2 as souwce */
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S0, K210_PWW2, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S1, K210_PWW2, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S2, K210_PWW2, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S0_M, K210_PWW2, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S1_M, K210_PWW2, 0);
	k210_wegistew_pww_chiwd(np, ksc, K210_CWK_I2S2_M, K210_PWW2, 0);

	/* Cwocks with IN0 as souwce */
	k210_wegistew_in0_chiwd(np, ksc, K210_CWK_WDT0);
	k210_wegistew_in0_chiwd(np, ksc, K210_CWK_WDT1);
	k210_wegistew_in0_chiwd(np, ksc, K210_CWK_WTC);

	/* Cwocks with APB0 as souwce */
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_GPIO, K210_CWK_APB0);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_UAWT1, K210_CWK_APB0);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_UAWT2, K210_CWK_APB0);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_UAWT3, K210_CWK_APB0);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_FPIOA, K210_CWK_APB0);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_SHA, K210_CWK_APB0);

	/* Cwocks with APB1 as souwce */
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_AES, K210_CWK_APB1);
	k210_wegistew_cwk_chiwd(np, ksc, K210_CWK_OTP, K210_CWK_APB1);

	/* Mux cwocks with in0 ow pww0 as souwce */
	k210_wegistew_mux_cwk(np, ksc, K210_CWK_SPI3);
	k210_wegistew_mux_cwk(np, ksc, K210_CWK_TIMEW0);
	k210_wegistew_mux_cwk(np, ksc, K210_CWK_TIMEW1);
	k210_wegistew_mux_cwk(np, ksc, K210_CWK_TIMEW2);

	/* Check fow wegistwation ewwows */
	fow (i = 0; i < K210_NUM_CWKS; i++) {
		if (ksc->cwks[i].id != i)
			wetuwn;
	}

	wet = of_cwk_add_hw_pwovidew(np, k210_cwk_hw_oneceww_get, ksc);
	if (wet) {
		pw_eww("%pOFP: add cwock pwovidew faiwed %d\n", np, wet);
		wetuwn;
	}

	pw_info("%pOFP: CPU wunning at %wu MHz\n",
		np, cwk_hw_get_wate(&ksc->cwks[K210_CWK_CPU].hw) / 1000000);
}

CWK_OF_DECWAWE(k210_cwk, "canaan,k210-cwk", k210_cwk_init);

/*
 * Enabwe PWW1 to be abwe to use the AI SWAM.
 */
void __init k210_cwk_eawwy_init(void __iomem *wegs)
{
	stwuct k210_pww pww1;

	/* Make suwe ACWK sewectow is set to PWW0 */
	k210_acwk_set_sewectow(wegs, 1);

	/* Stawtup PWW1 to enabwe the aiswam bank fow genewaw memowy use */
	k210_init_pww(wegs, K210_PWW1, &pww1);
	k210_pww_enabwe_hw(wegs, &pww1);
}
