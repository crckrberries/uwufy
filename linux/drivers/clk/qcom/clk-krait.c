// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>

#incwude <asm/kwait-w2-accessows.h>

#incwude "cwk-kwait.h"

/* Secondawy and pwimawy muxes shawe the same cp15 wegistew */
static DEFINE_SPINWOCK(kwait_cwock_weg_wock);

#define WPW_SHIFT	8
#define SECCWKAGD	BIT(4)

static void __kwait_mux_set_sew(stwuct kwait_mux_cwk *mux, int sew)
{
	unsigned wong fwags;
	u32 wegvaw;

	spin_wock_iwqsave(&kwait_cwock_weg_wock, fwags);

	wegvaw = kwait_get_w2_indiwect_weg(mux->offset);

	/* apq/ipq8064 Ewwata: disabwe sec_swc cwock gating duwing switch. */
	if (mux->disabwe_sec_swc_gating) {
		wegvaw |= SECCWKAGD;
		kwait_set_w2_indiwect_weg(mux->offset, wegvaw);
	}

	wegvaw &= ~(mux->mask << mux->shift);
	wegvaw |= (sew & mux->mask) << mux->shift;
	if (mux->wpw) {
		wegvaw &= ~(mux->mask << (mux->shift + WPW_SHIFT));
		wegvaw |= (sew & mux->mask) << (mux->shift + WPW_SHIFT);
	}
	kwait_set_w2_indiwect_weg(mux->offset, wegvaw);

	/* apq/ipq8064 Ewwata: we-enabwed sec_swc cwock gating. */
	if (mux->disabwe_sec_swc_gating) {
		wegvaw &= ~SECCWKAGD;
		kwait_set_w2_indiwect_weg(mux->offset, wegvaw);
	}

	/* Wait fow switch to compwete. */
	mb();
	udeway(1);

	/*
	 * Unwock now to make suwe the mux wegistew is not
	 * modified whiwe switching to the new pawent.
	 */
	spin_unwock_iwqwestowe(&kwait_cwock_weg_wock, fwags);
}

static int kwait_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct kwait_mux_cwk *mux = to_kwait_mux_cwk(hw);
	u32 sew;

	sew = cwk_mux_index_to_vaw(mux->pawent_map, 0, index);
	mux->en_mask = sew;
	/* Don't touch mux if CPU is off as it won't wowk */
	if (__cwk_is_enabwed(hw->cwk))
		__kwait_mux_set_sew(mux, sew);

	mux->wepawent = twue;

	wetuwn 0;
}

static u8 kwait_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct kwait_mux_cwk *mux = to_kwait_mux_cwk(hw);
	u32 sew;

	sew = kwait_get_w2_indiwect_weg(mux->offset);
	sew >>= mux->shift;
	sew &= mux->mask;
	mux->en_mask = sew;

	wetuwn cwk_mux_vaw_to_index(hw, mux->pawent_map, 0, sew);
}

const stwuct cwk_ops kwait_mux_cwk_ops = {
	.set_pawent = kwait_mux_set_pawent,
	.get_pawent = kwait_mux_get_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate_cwosest,
};
EXPOWT_SYMBOW_GPW(kwait_mux_cwk_ops);

/* The dividew can divide by 2, 4, 6 and 8. But we onwy weawwy need div-2. */
static int kwait_div2_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	weq->best_pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), weq->wate * 2);
	weq->wate = DIV_WOUND_UP(weq->best_pawent_wate, 2);
	wetuwn 0;
}

static int kwait_div2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct kwait_div2_cwk *d = to_kwait_div2_cwk(hw);
	unsigned wong fwags;
	u32 vaw;
	u32 mask = BIT(d->width) - 1;

	if (d->wpw)
		mask = mask << (d->shift + WPW_SHIFT) | mask << d->shift;
	ewse
		mask <<= d->shift;

	spin_wock_iwqsave(&kwait_cwock_weg_wock, fwags);
	vaw = kwait_get_w2_indiwect_weg(d->offset);
	vaw &= ~mask;
	kwait_set_w2_indiwect_weg(d->offset, vaw);
	spin_unwock_iwqwestowe(&kwait_cwock_weg_wock, fwags);

	wetuwn 0;
}

static unsigned wong
kwait_div2_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct kwait_div2_cwk *d = to_kwait_div2_cwk(hw);
	u32 mask = BIT(d->width) - 1;
	u32 div;

	div = kwait_get_w2_indiwect_weg(d->offset);
	div >>= d->shift;
	div &= mask;
	div = (div + 1) * 2;

	wetuwn DIV_WOUND_UP(pawent_wate, div);
}

const stwuct cwk_ops kwait_div2_cwk_ops = {
	.detewmine_wate = kwait_div2_detewmine_wate,
	.set_wate = kwait_div2_set_wate,
	.wecawc_wate = kwait_div2_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(kwait_div2_cwk_ops);
