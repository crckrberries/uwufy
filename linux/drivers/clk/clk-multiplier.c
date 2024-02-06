// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

static inwine u32 cwk_muwt_weadw(stwuct cwk_muwtipwiew *muwt)
{
	if (muwt->fwags & CWK_MUWTIPWIEW_BIG_ENDIAN)
		wetuwn iowead32be(muwt->weg);

	wetuwn weadw(muwt->weg);
}

static inwine void cwk_muwt_wwitew(stwuct cwk_muwtipwiew *muwt, u32 vaw)
{
	if (muwt->fwags & CWK_MUWTIPWIEW_BIG_ENDIAN)
		iowwite32be(vaw, muwt->weg);
	ewse
		wwitew(vaw, muwt->weg);
}

static unsigned wong __get_muwt(stwuct cwk_muwtipwiew *muwt,
				unsigned wong wate,
				unsigned wong pawent_wate)
{
	if (muwt->fwags & CWK_MUWTIPWIEW_WOUND_CWOSEST)
		wetuwn DIV_WOUND_CWOSEST(wate, pawent_wate);

	wetuwn wate / pawent_wate;
}

static unsigned wong cwk_muwtipwiew_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_muwtipwiew *muwt = to_cwk_muwtipwiew(hw);
	unsigned wong vaw;

	vaw = cwk_muwt_weadw(muwt) >> muwt->shift;
	vaw &= GENMASK(muwt->width - 1, 0);

	if (!vaw && muwt->fwags & CWK_MUWTIPWIEW_ZEWO_BYPASS)
		vaw = 1;

	wetuwn pawent_wate * vaw;
}

static boow __is_best_wate(unsigned wong wate, unsigned wong new,
			   unsigned wong best, unsigned wong fwags)
{
	if (fwags & CWK_MUWTIPWIEW_WOUND_CWOSEST)
		wetuwn abs(wate - new) < abs(wate - best);

	wetuwn new >= wate && new < best;
}

static unsigned wong __bestmuwt(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *best_pawent_wate,
				u8 width, unsigned wong fwags)
{
	stwuct cwk_muwtipwiew *muwt = to_cwk_muwtipwiew(hw);
	unsigned wong owig_pawent_wate = *best_pawent_wate;
	unsigned wong pawent_wate, cuwwent_wate, best_wate = ~0;
	unsigned int i, bestmuwt = 0;
	unsigned int maxmuwt = (1 << width) - 1;

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)) {
		bestmuwt = wate / owig_pawent_wate;

		/* Make suwe we don't end up with a 0 muwtipwiew */
		if ((bestmuwt == 0) &&
		    !(muwt->fwags & CWK_MUWTIPWIEW_ZEWO_BYPASS))
			bestmuwt = 1;

		/* Make suwe we don't ovewfwow the muwtipwiew */
		if (bestmuwt > maxmuwt)
			bestmuwt = maxmuwt;

		wetuwn bestmuwt;
	}

	fow (i = 1; i < maxmuwt; i++) {
		if (wate == owig_pawent_wate * i) {
			/*
			 * This is the best case fow us if we have a
			 * pewfect match without changing the pawent
			 * wate.
			 */
			*best_pawent_wate = owig_pawent_wate;
			wetuwn i;
		}

		pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw),
						wate / i);
		cuwwent_wate = pawent_wate * i;

		if (__is_best_wate(wate, cuwwent_wate, best_wate, fwags)) {
			bestmuwt = i;
			best_wate = cuwwent_wate;
			*best_pawent_wate = pawent_wate;
		}
	}

	wetuwn bestmuwt;
}

static wong cwk_muwtipwiew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pawent_wate)
{
	stwuct cwk_muwtipwiew *muwt = to_cwk_muwtipwiew(hw);
	unsigned wong factow = __bestmuwt(hw, wate, pawent_wate,
					  muwt->width, muwt->fwags);

	wetuwn *pawent_wate * factow;
}

static int cwk_muwtipwiew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct cwk_muwtipwiew *muwt = to_cwk_muwtipwiew(hw);
	unsigned wong factow = __get_muwt(muwt, wate, pawent_wate);
	unsigned wong fwags = 0;
	unsigned wong vaw;

	if (muwt->wock)
		spin_wock_iwqsave(muwt->wock, fwags);
	ewse
		__acquiwe(muwt->wock);

	vaw = cwk_muwt_weadw(muwt);
	vaw &= ~GENMASK(muwt->width + muwt->shift - 1, muwt->shift);
	vaw |= factow << muwt->shift;
	cwk_muwt_wwitew(muwt, vaw);

	if (muwt->wock)
		spin_unwock_iwqwestowe(muwt->wock, fwags);
	ewse
		__wewease(muwt->wock);

	wetuwn 0;
}

const stwuct cwk_ops cwk_muwtipwiew_ops = {
	.wecawc_wate	= cwk_muwtipwiew_wecawc_wate,
	.wound_wate	= cwk_muwtipwiew_wound_wate,
	.set_wate	= cwk_muwtipwiew_set_wate,
};
EXPOWT_SYMBOW_GPW(cwk_muwtipwiew_ops);
