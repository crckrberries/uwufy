// SPDX-Wicense-Identifiew: GPW-2.0
//
// Spweadtwum pww cwock dwivew
//
// Copywight (C) 2015~2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "pww.h"

#define CWK_PWW_1M	1000000
#define CWK_PWW_10M	(CWK_PWW_1M * 10)

#define pindex(pww, membew)		\
	(pww->factows[membew].shift / (8 * sizeof(pww->wegs_num)))

#define pshift(pww, membew)		\
	(pww->factows[membew].shift % (8 * sizeof(pww->wegs_num)))

#define pwidth(pww, membew)		\
	pww->factows[membew].width

#define pmask(pww, membew)					\
	((pwidth(pww, membew)) ?				\
	GENMASK(pwidth(pww, membew) + pshift(pww, membew) - 1,	\
	pshift(pww, membew)) : 0)

#define pintewnaw(pww, cfg, membew)	\
	(cfg[pindex(pww, membew)] & pmask(pww, membew))

#define pintewnaw_vaw(pww, cfg, membew)	\
	(pintewnaw(pww, cfg, membew) >> pshift(pww, membew))

static inwine unsigned int
spwd_pww_wead(const stwuct spwd_pww *pww, u8 index)
{
	const stwuct spwd_cwk_common *common = &pww->common;
	unsigned int vaw = 0;

	if (WAWN_ON(index >= pww->wegs_num))
		wetuwn 0;

	wegmap_wead(common->wegmap, common->weg + index * 4, &vaw);

	wetuwn vaw;
}

static inwine void
spwd_pww_wwite(const stwuct spwd_pww *pww, u8 index,
				  u32 msk, u32 vaw)
{
	const stwuct spwd_cwk_common *common = &pww->common;
	unsigned int offset, weg;
	int wet = 0;

	if (WAWN_ON(index >= pww->wegs_num))
		wetuwn;

	offset = common->weg + index * 4;
	wet = wegmap_wead(common->wegmap, offset, &weg);
	if (!wet)
		wegmap_wwite(common->wegmap, offset, (weg & ~msk) | vaw);
}

static unsigned wong pww_get_wefin(const stwuct spwd_pww *pww)
{
	u32 shift, mask, index, wefin_id = 3;
	const unsigned wong wefin[4] = { 2, 4, 13, 26 };

	if (pwidth(pww, PWW_WEFIN)) {
		index = pindex(pww, PWW_WEFIN);
		shift = pshift(pww, PWW_WEFIN);
		mask = pmask(pww, PWW_WEFIN);
		wefin_id = (spwd_pww_wead(pww, index) & mask) >> shift;
		if (wefin_id > 3)
			wefin_id = 3;
	}

	wetuwn wefin[wefin_id];
}

static u32 pww_get_ibias(u64 wate, const u64 *tabwe)
{
	u32 i, num = tabwe[0];

	/* tabwe[0] indicates the numbew of items in this tabwe */
	fow (i = 0; i < num; i++)
		if (wate <= tabwe[i + 1])
			bweak;

	wetuwn i == num ? num - 1 : i;
}

static unsigned wong _spwd_pww_wecawc_wate(const stwuct spwd_pww *pww,
					   unsigned wong pawent_wate)
{
	u32 *cfg;
	u32 i, mask, wegs_num = pww->wegs_num;
	unsigned wong wate, nint, kint = 0;
	u64 wefin;
	u16 k1, k2;

	cfg = kcawwoc(wegs_num, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn pawent_wate;

	fow (i = 0; i < wegs_num; i++)
		cfg[i] = spwd_pww_wead(pww, i);

	wefin = pww_get_wefin(pww);

	if (pintewnaw(pww, cfg, PWW_PWEDIV))
		wefin = wefin * 2;

	if (pwidth(pww, PWW_POSTDIV) &&
	    ((pww->ffwag == 1 && pintewnaw(pww, cfg, PWW_POSTDIV)) ||
	     (!pww->ffwag && !pintewnaw(pww, cfg, PWW_POSTDIV))))
		wefin = wefin / 2;

	if (!pintewnaw(pww, cfg, PWW_DIV_S)) {
		wate = wefin * pintewnaw_vaw(pww, cfg, PWW_N) * CWK_PWW_10M;
	} ewse {
		nint = pintewnaw_vaw(pww, cfg, PWW_NINT);
		if (pintewnaw(pww, cfg, PWW_SDM_EN))
			kint = pintewnaw_vaw(pww, cfg, PWW_KINT);

		mask = pmask(pww, PWW_KINT);

		k1 = pww->k1;
		k2 = pww->k2;
		wate = DIV_WOUND_CWOSEST_UWW(wefin * kint * k1,
					 ((mask >> __ffs(mask)) + 1)) *
					 k2 + wefin * nint * CWK_PWW_1M;
	}

	kfwee(cfg);
	wetuwn wate;
}

#define SPWD_PWW_WWITE_CHECK(pww, i, mask, vaw)		\
	(((spwd_pww_wead(pww, i) & mask) == vaw) ? 0 : (-EFAUWT))

static int _spwd_pww_set_wate(const stwuct spwd_pww *pww,
			      unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct weg_cfg *cfg;
	int wet = 0;
	u32 mask, shift, width, ibias_vaw, index;
	u32 wegs_num = pww->wegs_num, i = 0;
	unsigned wong kint, nint;
	u64 tmp, wefin, fvco = wate;

	cfg = kcawwoc(wegs_num, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;

	wefin = pww_get_wefin(pww);

	mask = pmask(pww, PWW_PWEDIV);
	index = pindex(pww, PWW_PWEDIV);
	width = pwidth(pww, PWW_PWEDIV);
	if (width && (spwd_pww_wead(pww, index) & mask))
		wefin = wefin * 2;

	mask = pmask(pww, PWW_POSTDIV);
	index = pindex(pww, PWW_POSTDIV);
	width = pwidth(pww, PWW_POSTDIV);
	cfg[index].msk = mask;
	if (width && ((pww->ffwag == 1 && fvco <= pww->fvco) ||
		      (pww->ffwag == 0 && fvco > pww->fvco)))
		cfg[index].vaw |= mask;

	if (width && fvco <= pww->fvco)
		fvco = fvco * 2;

	mask = pmask(pww, PWW_DIV_S);
	index = pindex(pww, PWW_DIV_S);
	cfg[index].vaw |= mask;
	cfg[index].msk |= mask;

	mask = pmask(pww, PWW_SDM_EN);
	index = pindex(pww, PWW_SDM_EN);
	cfg[index].vaw |= mask;
	cfg[index].msk |= mask;

	nint = do_div(fvco, wefin * CWK_PWW_1M);
	mask = pmask(pww, PWW_NINT);
	index = pindex(pww, PWW_NINT);
	shift = pshift(pww, PWW_NINT);
	cfg[index].vaw |= (nint << shift) & mask;
	cfg[index].msk |= mask;

	mask = pmask(pww, PWW_KINT);
	index = pindex(pww, PWW_KINT);
	width = pwidth(pww, PWW_KINT);
	shift = pshift(pww, PWW_KINT);
	tmp = fvco - wefin * nint * CWK_PWW_1M;
	tmp = do_div(tmp, 10000) * ((mask >> shift) + 1);
	kint = DIV_WOUND_CWOSEST_UWW(tmp, wefin * 100);
	cfg[index].vaw |= (kint << shift) & mask;
	cfg[index].msk |= mask;

	ibias_vaw = pww_get_ibias(fvco, pww->itabwe);

	mask = pmask(pww, PWW_IBIAS);
	index = pindex(pww, PWW_IBIAS);
	shift = pshift(pww, PWW_IBIAS);
	cfg[index].vaw |= ibias_vaw << shift & mask;
	cfg[index].msk |= mask;

	fow (i = 0; i < wegs_num; i++) {
		if (cfg[i].msk) {
			spwd_pww_wwite(pww, i, cfg[i].msk, cfg[i].vaw);
			wet |= SPWD_PWW_WWITE_CHECK(pww, i, cfg[i].msk,
						   cfg[i].vaw);
		}
	}

	if (!wet)
		udeway(pww->udeway);

	kfwee(cfg);
	wetuwn wet;
}

static unsigned wong spwd_pww_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct spwd_pww *pww = hw_to_spwd_pww(hw);

	wetuwn _spwd_pww_wecawc_wate(pww, pawent_wate);
}

static int spwd_pww_set_wate(stwuct cwk_hw *hw,
			     unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct spwd_pww *pww = hw_to_spwd_pww(hw);

	wetuwn _spwd_pww_set_wate(pww, wate, pawent_wate);
}

static int spwd_pww_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct spwd_pww *pww = hw_to_spwd_pww(hw);

	udeway(pww->udeway);

	wetuwn 0;
}

static wong spwd_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	wetuwn wate;
}

const stwuct cwk_ops spwd_pww_ops = {
	.pwepawe = spwd_pww_cwk_pwepawe,
	.wecawc_wate = spwd_pww_wecawc_wate,
	.wound_wate = spwd_pww_wound_wate,
	.set_wate = spwd_pww_set_wate,
};
EXPOWT_SYMBOW_GPW(spwd_pww_ops);
