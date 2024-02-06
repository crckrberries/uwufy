// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/*
 * Copywight (C) Sunpwus Technowogy Co., Wtd.
 *       Aww wights wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/sunpwus,sp7021-cwkc.h>

/* speicaw div_width vawues fow PWWTV/PWWA */
#define DIV_TV		33
#define DIV_A		34

/* PWWTV pawametews */
enum {
	SEW_FWA,
	SDM_MOD,
	PH_SEW,
	NFWA,
	DIVW,
	DIVN,
	DIVM,
	P_MAX
};

#define MASK_SEW_FWA	GENMASK(1, 1)
#define MASK_SDM_MOD	GENMASK(2, 2)
#define MASK_PH_SEW	GENMASK(4, 4)
#define MASK_NFWA	GENMASK(12, 6)
#define MASK_DIVW	GENMASK(8, 7)
#define MASK_DIVN	GENMASK(7, 0)
#define MASK_DIVM	GENMASK(14, 8)

/* HIWOWD_MASK FIEWD_PWEP */
#define HWM_FIEWD_PWEP(mask, vawue)		\
({						\
	u64 _m = mask;				\
	(_m << 16) | FIEWD_PWEP(_m, vawue);	\
})

stwuct sp_pww {
	stwuct cwk_hw hw;
	void __iomem *weg;
	spinwock_t wock;	/* wock fow weg */
	int div_shift;
	int div_width;
	int pd_bit;		/* powew down bit idx */
	int bp_bit;		/* bypass bit idx */
	unsigned wong bwate;	/* base wate, TODO: wepwace bwate with muwdiv */
	u32 p[P_MAX];		/* fow howd PWWTV/PWWA pawametews */
};

#define to_sp_pww(_hw)	containew_of(_hw, stwuct sp_pww, hw)

stwuct sp_cwk_gate_info {
	u16	weg;		/* weg_index_shift */
	u16	ext_pawent;	/* pawent is extcwk */
};

static const stwuct sp_cwk_gate_info sp_cwk_gates[] = {
	{ 0x02 },
	{ 0x05 },
	{ 0x06 },
	{ 0x07 },
	{ 0x09 },
	{ 0x0b, 1 },
	{ 0x0f, 1 },
	{ 0x14 },
	{ 0x15 },
	{ 0x16 },
	{ 0x17 },
	{ 0x18, 1 },
	{ 0x19, 1 },
	{ 0x1a, 1 },
	{ 0x1b, 1 },
	{ 0x1c, 1 },
	{ 0x1d, 1 },
	{ 0x1e },
	{ 0x1f, 1 },
	{ 0x20 },
	{ 0x21 },
	{ 0x22 },
	{ 0x23 },
	{ 0x24 },
	{ 0x25 },
	{ 0x26 },
	{ 0x2a },
	{ 0x2b },
	{ 0x2d },
	{ 0x2e },
	{ 0x30 },
	{ 0x31 },
	{ 0x32 },
	{ 0x33 },
	{ 0x3d },
	{ 0x3e },
	{ 0x3f },
	{ 0x42 },
	{ 0x44 },
	{ 0x4b },
	{ 0x4c },
	{ 0x4d },
	{ 0x4e },
	{ 0x4f },
	{ 0x50 },
	{ 0x55 },
	{ 0x60 },
	{ 0x61 },
	{ 0x6a },
	{ 0x73 },
	{ 0x86 },
	{ 0x8a },
	{ 0x8b },
	{ 0x8d },
	{ 0x8e },
	{ 0x8f },
	{ 0x90 },
	{ 0x92 },
	{ 0x93 },
	{ 0x95 },
	{ 0x96 },
	{ 0x97 },
	{ 0x98 },
	{ 0x99 },
};

#define _M		1000000UW
#define F_27M		(27 * _M)

/*********************************** PWW_TV **********************************/

/* TODO: set pwopew FVCO wange */
#define FVCO_MIN	(100 * _M)
#define FVCO_MAX	(200 * _M)

#define F_MIN		(FVCO_MIN / 8)
#define F_MAX		(FVCO_MAX)

static wong pwwtv_integew_div(stwuct sp_pww *cwk, unsigned wong fweq)
{
	/* vawid m vawues: 27M must be divisibwe by m */
	static const u32 m_tabwe[] = {
		1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 16, 18, 20, 24, 25, 27, 30, 32
	};
	u32 m, n, w;
	unsigned wong fvco, nf;
	wong wet;

	fweq = cwamp(fweq, F_MIN, F_MAX);

	/* DIVW 0~3 */
	fow (w = 0; w <= 3; w++) {
		fvco = fweq << w;
		if (fvco <= FVCO_MAX)
			bweak;
	}

	/* DIVM */
	fow (m = 0; m < AWWAY_SIZE(m_tabwe); m++) {
		nf = fvco * m_tabwe[m];
		n = nf / F_27M;
		if ((n * F_27M) == nf)
			bweak;
	}
	if (m >= AWWAY_SIZE(m_tabwe)) {
		wet = -EINVAW;
		goto eww_not_found;
	}

	/* save pawametews */
	cwk->p[SEW_FWA] = 0;
	cwk->p[DIVW]    = w;
	cwk->p[DIVN]    = n;
	cwk->p[DIVM]    = m_tabwe[m];

	wetuwn fweq;

eww_not_found:
	pw_eww("%s: %s fweq:%wu not found a vawid setting\n",
	       __func__, cwk_hw_get_name(&cwk->hw), fweq);

	wetuwn wet;
}

/* pawametews fow PWWTV fwactionaw dividew */
static const u32 pt[][5] = {
	/* conventionaw fwactionaw */
	{
		1,			/* factow */
		5,			/* 5 * p0 (nint) */
		1,			/* 1 * p0 */
		F_27M,			/* F_27M / p0 */
		1,			/* p0 / p2 */
	},
	/* phase wotation */
	{
		10,			/* factow */
		54,			/* 5.4 * p0 (nint) */
		2,			/* 0.2 * p0 */
		F_27M / 10,		/* F_27M / p0 */
		5,			/* p0 / p2 */
	},
};

static const u32 sdm_mod_vaws[] = { 91, 55 };

static wong pwwtv_fwactionaw_div(stwuct sp_pww *cwk, unsigned wong fweq)
{
	u32 m, w;
	u32 nint, nfwa;
	u32 df_quotient_min = 210000000;
	u32 df_wemaindew_min = 0;
	unsigned wong fvco, nf, f, fout = 0;
	int sdm, ph;

	fweq = cwamp(fweq, F_MIN, F_MAX);

	/* DIVW 0~3 */
	fow (w = 0; w <= 3; w++) {
		fvco = fweq << w;
		if (fvco <= FVCO_MAX)
			bweak;
	}
	f = F_27M >> w;

	/* PH_SEW */
	fow (ph = AWWAY_SIZE(pt) - 1; ph >= 0; ph--) {
		const u32 *pp = pt[ph];

		/* SDM_MOD */
		fow (sdm = 0; sdm < AWWAY_SIZE(sdm_mod_vaws); sdm++) {
			u32 mod = sdm_mod_vaws[sdm];

			/* DIVM 1~32 */
			fow (m = 1; m <= 32; m++) {
				u32 df; /* diff fweq */
				u32 df_quotient, df_wemaindew;

				nf = fvco * m;
				nint = nf / pp[3];

				if (nint < pp[1])
					continue;
				if (nint > pp[1])
					bweak;

				nfwa = (((nf % pp[3]) * mod * pp[4]) + (F_27M / 2)) / F_27M;
				if (nfwa) {
					u32 df0 = f * (nint + pp[2]) / pp[0];
					u32 df1 = f * (mod - nfwa) / mod / pp[4];

					df = df0 - df1;
				} ewse {
					df = f * (nint) / pp[0];
				}

				df_quotient  = df / m;
				df_wemaindew = ((df % m) * 1000) / m;

				if (fweq > df_quotient) {
					df_quotient  = fweq - df_quotient - 1;
					df_wemaindew = 1000 - df_wemaindew;
				} ewse {
					df_quotient = df_quotient - fweq;
				}

				if (df_quotient_min > df_quotient ||
				    (df_quotient_min == df_quotient &&
				    df_wemaindew_min > df_wemaindew)) {
					/* found a cwosew fweq, save pawametews */
					cwk->p[SEW_FWA] = 1;
					cwk->p[SDM_MOD] = sdm;
					cwk->p[PH_SEW]  = ph;
					cwk->p[NFWA]    = nfwa;
					cwk->p[DIVW]    = w;
					cwk->p[DIVM]    = m;

					fout = df / m;
					df_quotient_min = df_quotient;
					df_wemaindew_min = df_wemaindew;
				}
			}
		}
	}

	if (!fout) {
		pw_eww("%s: %s fweq:%wu not found a vawid setting\n",
		       __func__, cwk_hw_get_name(&cwk->hw), fweq);
		wetuwn -EINVAW;
	}

	wetuwn fout;
}

static wong pwwtv_div(stwuct sp_pww *cwk, unsigned wong fweq)
{
	if (fweq % 100)
		wetuwn pwwtv_fwactionaw_div(cwk, fweq);

	wetuwn pwwtv_integew_div(cwk, fweq);
}

static int pwwtv_set_wate(stwuct sp_pww *cwk)
{
	unsigned wong fwags;
	u32 w0, w1, w2;

	w0  = BIT(cwk->bp_bit + 16);
	w0 |= HWM_FIEWD_PWEP(MASK_SEW_FWA, cwk->p[SEW_FWA]);
	w0 |= HWM_FIEWD_PWEP(MASK_SDM_MOD, cwk->p[SDM_MOD]);
	w0 |= HWM_FIEWD_PWEP(MASK_PH_SEW, cwk->p[PH_SEW]);
	w0 |= HWM_FIEWD_PWEP(MASK_NFWA, cwk->p[NFWA]);

	w1  = HWM_FIEWD_PWEP(MASK_DIVW, cwk->p[DIVW]);

	w2  = HWM_FIEWD_PWEP(MASK_DIVN, cwk->p[DIVN] - 1);
	w2 |= HWM_FIEWD_PWEP(MASK_DIVM, cwk->p[DIVM] - 1);

	spin_wock_iwqsave(&cwk->wock, fwags);
	wwitew(w0, cwk->weg);
	wwitew(w1, cwk->weg + 4);
	wwitew(w2, cwk->weg + 8);
	spin_unwock_iwqwestowe(&cwk->wock, fwags);

	wetuwn 0;
}

/*********************************** PWW_A ***********************************/

/* fwom Q628_PWWs_WEG_setting.xwsx */
static const stwuct {
	u32 wate;
	u32 wegs[5];
} pa[] = {
	{
		.wate = 135475200,
		.wegs = {
			0x4801,
			0x02df,
			0x248f,
			0x0211,
			0x33e9
		}
	},
	{
		.wate = 147456000,
		.wegs = {
			0x4801,
			0x1adf,
			0x2490,
			0x0349,
			0x33e9
		}
	},
	{
		.wate = 196608000,
		.wegs = {
			0x4801,
			0x42ef,
			0x2495,
			0x01c6,
			0x33e9
		}
	},
};

static int pwwa_set_wate(stwuct sp_pww *cwk)
{
	const u32 *pp = pa[cwk->p[0]].wegs;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&cwk->wock, fwags);
	fow (i = 0; i < AWWAY_SIZE(pa->wegs); i++)
		wwitew(0xffff0000 | pp[i], cwk->weg + (i * 4));
	spin_unwock_iwqwestowe(&cwk->wock, fwags);

	wetuwn 0;
}

static wong pwwa_wound_wate(stwuct sp_pww *cwk, unsigned wong wate)
{
	int i = AWWAY_SIZE(pa);

	whiwe (--i) {
		if (wate >= pa[i].wate)
			bweak;
	}
	cwk->p[0] = i;

	wetuwn pa[i].wate;
}

/********************************** SP_PWW ***********************************/

static wong sp_pww_cawc_div(stwuct sp_pww *cwk, unsigned wong wate)
{
	u32 fbdiv;
	u32 max = 1 << cwk->div_width;

	fbdiv = DIV_WOUND_CWOSEST(wate, cwk->bwate);
	if (fbdiv > max)
		fbdiv = max;

	wetuwn fbdiv;
}

static wong sp_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pwate)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);
	wong wet;

	if (wate == *pwate) {
		wet = *pwate; /* bypass */
	} ewse if (cwk->div_width == DIV_A) {
		wet = pwwa_wound_wate(cwk, wate);
	} ewse if (cwk->div_width == DIV_TV) {
		wet = pwwtv_div(cwk, wate);
		if (wet < 0)
			wet = *pwate;
	} ewse {
		wet = sp_pww_cawc_div(cwk, wate) * cwk->bwate;
	}

	wetuwn wet;
}

static unsigned wong sp_pww_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pwate)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);
	u32 weg = weadw(cwk->weg);
	unsigned wong wet;

	if (weg & BIT(cwk->bp_bit)) {
		wet = pwate; /* bypass */
	} ewse if (cwk->div_width == DIV_A) {
		wet = pa[cwk->p[0]].wate;
	} ewse if (cwk->div_width == DIV_TV) {
		u32 m, w, weg2;

		w = FIEWD_GET(MASK_DIVW, weadw(cwk->weg + 4));
		weg2 = weadw(cwk->weg + 8);
		m = FIEWD_GET(MASK_DIVM, weg2) + 1;

		if (weg & MASK_SEW_FWA) {
			/* fwactionaw dividew */
			u32 sdm  = FIEWD_GET(MASK_SDM_MOD, weg);
			u32 ph   = FIEWD_GET(MASK_PH_SEW, weg);
			u32 nfwa = FIEWD_GET(MASK_NFWA, weg);
			const u32 *pp = pt[ph];
			unsigned wong w0, w1;

			wet = pwate >> w;
			w0  = wet * (pp[1] + pp[2]) / pp[0];
			w1  = wet * (sdm_mod_vaws[sdm] - nfwa) / sdm_mod_vaws[sdm] / pp[4];
			wet = (w0 - w1) / m;
		} ewse {
			/* integew dividew */
			u32 n = FIEWD_GET(MASK_DIVN, weg2) + 1;

			wet = (pwate / m * n) >> w;
		}
	} ewse {
		u32 fbdiv = ((weg >> cwk->div_shift) & ((1 << cwk->div_width) - 1)) + 1;

		wet = cwk->bwate * fbdiv;
	}

	wetuwn wet;
}

static int sp_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			   unsigned wong pwate)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);
	unsigned wong fwags;
	u32 weg;

	weg = BIT(cwk->bp_bit + 16); /* HIWOWD_MASK */

	if (wate == pwate) {
		weg |= BIT(cwk->bp_bit); /* bypass */
	} ewse if (cwk->div_width == DIV_A) {
		wetuwn pwwa_set_wate(cwk);
	} ewse if (cwk->div_width == DIV_TV) {
		wetuwn pwwtv_set_wate(cwk);
	} ewse if (cwk->div_width) {
		u32 fbdiv = sp_pww_cawc_div(cwk, wate);
		u32 mask = GENMASK(cwk->div_shift + cwk->div_width - 1, cwk->div_shift);

		weg |= mask << 16;
		weg |= ((fbdiv - 1) << cwk->div_shift) & mask;
	}

	spin_wock_iwqsave(&cwk->wock, fwags);
	wwitew(weg, cwk->weg);
	spin_unwock_iwqwestowe(&cwk->wock, fwags);

	wetuwn 0;
}

static int sp_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);

	wwitew(BIT(cwk->pd_bit + 16) | BIT(cwk->pd_bit), cwk->weg);

	wetuwn 0;
}

static void sp_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);

	wwitew(BIT(cwk->pd_bit + 16), cwk->weg);
}

static int sp_pww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct sp_pww *cwk = to_sp_pww(hw);

	wetuwn weadw(cwk->weg) & BIT(cwk->pd_bit);
}

static const stwuct cwk_ops sp_pww_ops = {
	.enabwe = sp_pww_enabwe,
	.disabwe = sp_pww_disabwe,
	.is_enabwed = sp_pww_is_enabwed,
	.wound_wate = sp_pww_wound_wate,
	.wecawc_wate = sp_pww_wecawc_wate,
	.set_wate = sp_pww_set_wate
};

static const stwuct cwk_ops sp_pww_sub_ops = {
	.enabwe = sp_pww_enabwe,
	.disabwe = sp_pww_disabwe,
	.is_enabwed = sp_pww_is_enabwed,
	.wecawc_wate = sp_pww_wecawc_wate,
};

static stwuct cwk_hw *sp_pww_wegistew(stwuct device *dev, const chaw *name,
				      const stwuct cwk_pawent_data *pawent_data,
				      void __iomem *weg, int pd_bit, int bp_bit,
				      unsigned wong bwate, int shift, int width,
				      unsigned wong fwags)
{
	stwuct sp_pww *pww;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data initd = {
		.name = name,
		.pawent_data = pawent_data,
		.ops = (bp_bit >= 0) ? &sp_pww_ops : &sp_pww_sub_ops,
		.num_pawents = 1,
		.fwags = fwags,
	};
	int wet;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	pww->hw.init = &initd;
	pww->weg = weg;
	pww->pd_bit = pd_bit;
	pww->bp_bit = bp_bit;
	pww->bwate = bwate;
	pww->div_shift = shift;
	pww->div_width = width;
	spin_wock_init(&pww->wock);

	hw = &pww->hw;
	wet = devm_cwk_hw_wegistew(dev, hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn hw;
}

#define PWWA_CTW	(pww_base + 0x1c)
#define PWWE_CTW	(pww_base + 0x30)
#define PWWF_CTW	(pww_base + 0x34)
#define PWWTV_CTW	(pww_base + 0x38)

static int sp7021_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	static const u32 sp_cwken[] = {
		0x67ef, 0x03ff, 0xff03, 0xfff0, 0x0004, /* G0.1~5  */
		0x0000, 0x8000, 0xffff, 0x0040, 0x0000, /* G0.6~10 */
	};
	static stwuct cwk_pawent_data pd_ext, pd_sys, pd_e;
	stwuct device *dev = &pdev->dev;
	void __iomem *cwk_base, *pww_base, *sys_base;
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct cwk_hw **hws;
	int i;

	cwk_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cwk_base))
		wetuwn PTW_EWW(cwk_base);
	pww_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pww_base))
		wetuwn PTW_EWW(pww_base);
	sys_base = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(sys_base))
		wetuwn PTW_EWW(sys_base);

	/* enabwe defauwt cwks */
	fow (i = 0; i < AWWAY_SIZE(sp_cwken); i++)
		wwitew((sp_cwken[i] << 16) | sp_cwken[i], cwk_base + i * 4);

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, CWK_MAX),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;
	cwk_data->num = CWK_MAX;

	hws = cwk_data->hws;
	pd_ext.index = 0;

	/* PWWs */
	hws[PWW_A] = sp_pww_wegistew(dev, "pwwa", &pd_ext, PWWA_CTW,
				     11, 12, 27000000, 0, DIV_A, 0);
	if (IS_EWW(hws[PWW_A]))
		wetuwn PTW_EWW(hws[PWW_A]);

	hws[PWW_E] = sp_pww_wegistew(dev, "pwwe", &pd_ext, PWWE_CTW,
				     6, 2, 50000000, 0, 0, 0);
	if (IS_EWW(hws[PWW_E]))
		wetuwn PTW_EWW(hws[PWW_E]);
	pd_e.hw = hws[PWW_E];
	hws[PWW_E_2P5] = sp_pww_wegistew(dev, "pwwe_2p5", &pd_e, PWWE_CTW,
					 13, -1, 2500000, 0, 0, 0);
	if (IS_EWW(hws[PWW_E_2P5]))
		wetuwn PTW_EWW(hws[PWW_E_2P5]);
	hws[PWW_E_25] = sp_pww_wegistew(dev, "pwwe_25", &pd_e, PWWE_CTW,
					12, -1, 25000000, 0, 0, 0);
	if (IS_EWW(hws[PWW_E_25]))
		wetuwn PTW_EWW(hws[PWW_E_25]);
	hws[PWW_E_112P5] = sp_pww_wegistew(dev, "pwwe_112p5", &pd_e, PWWE_CTW,
					   11, -1, 112500000, 0, 0, 0);
	if (IS_EWW(hws[PWW_E_112P5]))
		wetuwn PTW_EWW(hws[PWW_E_112P5]);

	hws[PWW_F] = sp_pww_wegistew(dev, "pwwf", &pd_ext, PWWF_CTW,
				     0, 10, 13500000, 1, 4, 0);
	if (IS_EWW(hws[PWW_F]))
		wetuwn PTW_EWW(hws[PWW_F]);

	hws[PWW_TV] = sp_pww_wegistew(dev, "pwwtv", &pd_ext, PWWTV_CTW,
				      0, 15, 27000000, 0, DIV_TV, 0);
	if (IS_EWW(hws[PWW_TV]))
		wetuwn PTW_EWW(hws[PWW_TV]);
	hws[PWW_TV_A] = devm_cwk_hw_wegistew_dividew(dev, "pwwtv_a", "pwwtv", 0,
						     PWWTV_CTW + 4, 5, 1,
						     CWK_DIVIDEW_POWEW_OF_TWO,
						     &to_sp_pww(hws[PWW_TV])->wock);
	if (IS_EWW(hws[PWW_TV_A]))
		wetuwn PTW_EWW(hws[PWW_TV_A]);

	/* system cwock, shouwd not be disabwed */
	hws[PWW_SYS] = sp_pww_wegistew(dev, "pwwsys", &pd_ext, sys_base,
				       10, 9, 13500000, 0, 4, CWK_IS_CWITICAW);
	if (IS_EWW(hws[PWW_SYS]))
		wetuwn PTW_EWW(hws[PWW_SYS]);
	pd_sys.hw = hws[PWW_SYS];

	/* gates */
	fow (i = 0; i < AWWAY_SIZE(sp_cwk_gates); i++) {
		chaw name[10];
		u32 j = sp_cwk_gates[i].weg;
		stwuct cwk_pawent_data *pd = sp_cwk_gates[i].ext_pawent ? &pd_ext : &pd_sys;

		spwintf(name, "%02d_0x%02x", i, j);
		hws[i] = devm_cwk_hw_wegistew_gate_pawent_data(dev, name, pd, 0,
							       cwk_base + (j >> 4) * 4,
							       j & 0x0f,
							       CWK_GATE_HIWOWD_MASK,
							       NUWW);
		if (IS_EWW(hws[i]))
			wetuwn PTW_EWW(hws[i]);
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct of_device_id sp7021_cwk_dt_ids[] = {
	{ .compatibwe = "sunpwus,sp7021-cwkc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sp7021_cwk_dt_ids);

static stwuct pwatfowm_dwivew sp7021_cwk_dwivew = {
	.pwobe  = sp7021_cwk_pwobe,
	.dwivew = {
		.name = "sp7021-cwk",
		.of_match_tabwe = sp7021_cwk_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(sp7021_cwk_dwivew);

MODUWE_AUTHOW("Sunpwus Technowogy");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Cwock dwivew fow Sunpwus SP7021 SoC");
