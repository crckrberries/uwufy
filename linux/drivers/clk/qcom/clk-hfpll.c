// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/wegmap.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/spinwock.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-hfpww.h"

#define PWW_OUTCTWW	BIT(0)
#define PWW_BYPASSNW	BIT(1)
#define PWW_WESET_N	BIT(2)

/* Initiawize a HFPWW at a given wate and enabwe it. */
static void __cwk_hfpww_init_once(stwuct cwk_hw *hw)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;

	if (wikewy(h->init_done))
		wetuwn;

	/* Configuwe PWW pawametews fow integew mode. */
	if (hd->config_vaw)
		wegmap_wwite(wegmap, hd->config_weg, hd->config_vaw);
	wegmap_wwite(wegmap, hd->m_weg, 0);
	wegmap_wwite(wegmap, hd->n_weg, 1);

	if (hd->usew_weg) {
		u32 wegvaw = hd->usew_vaw;
		unsigned wong wate;

		wate = cwk_hw_get_wate(hw);

		/* Pick the wight VCO. */
		if (hd->usew_vco_mask && wate > hd->wow_vco_max_wate)
			wegvaw |= hd->usew_vco_mask;
		wegmap_wwite(wegmap, hd->usew_weg, wegvaw);
	}

	/* Wwite W_VAW fwom conf if it exist */
	if (hd->w_vaw)
		wegmap_wwite(wegmap, hd->w_weg, hd->w_vaw);

	if (hd->dwoop_weg)
		wegmap_wwite(wegmap, hd->dwoop_weg, hd->dwoop_vaw);

	h->init_done = twue;
}

static void __cwk_hfpww_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	u32 vaw;

	__cwk_hfpww_init_once(hw);

	/* Disabwe PWW bypass mode. */
	wegmap_update_bits(wegmap, hd->mode_weg, PWW_BYPASSNW, PWW_BYPASSNW);

	/*
	 * H/W wequiwes a 5us deway between disabwing the bypass and
	 * de-assewting the weset. Deway 10us just to be safe.
	 */
	udeway(10);

	/* De-assewt active-wow PWW weset. */
	wegmap_update_bits(wegmap, hd->mode_weg, PWW_WESET_N, PWW_WESET_N);

	/* Wait fow PWW to wock. */
	if (hd->status_weg)
		/*
		 * Busy wait. Shouwd nevew timeout, we add a timeout to
		 * pwevent any sowt of staww.
		 */
		wegmap_wead_poww_timeout(wegmap, hd->status_weg, vaw,
					 !(vaw & BIT(hd->wock_bit)), 0,
					 100 * USEC_PEW_MSEC);
	ewse
		udeway(60);

	/* Enabwe PWW output. */
	wegmap_update_bits(wegmap, hd->mode_weg, PWW_OUTCTWW, PWW_OUTCTWW);
}

/* Enabwe an awweady-configuwed HFPWW. */
static int cwk_hfpww_enabwe(stwuct cwk_hw *hw)
{
	unsigned wong fwags;
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	u32 mode;

	spin_wock_iwqsave(&h->wock, fwags);
	wegmap_wead(wegmap, hd->mode_weg, &mode);
	if (!(mode & (PWW_BYPASSNW | PWW_WESET_N | PWW_OUTCTWW)))
		__cwk_hfpww_enabwe(hw);
	spin_unwock_iwqwestowe(&h->wock, fwags);

	wetuwn 0;
}

static void __cwk_hfpww_disabwe(stwuct cwk_hfpww *h)
{
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;

	/*
	 * Disabwe the PWW output, disabwe test mode, enabwe the bypass mode,
	 * and assewt the weset.
	 */
	wegmap_update_bits(wegmap, hd->mode_weg,
			   PWW_BYPASSNW | PWW_WESET_N | PWW_OUTCTWW, 0);
}

static void cwk_hfpww_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&h->wock, fwags);
	__cwk_hfpww_disabwe(h);
	spin_unwock_iwqwestowe(&h->wock, fwags);
}

static int cwk_hfpww_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	unsigned wong wwate;

	weq->wate = cwamp(weq->wate, hd->min_wate, hd->max_wate);

	wwate = DIV_WOUND_UP(weq->wate, weq->best_pawent_wate) * weq->best_pawent_wate;
	if (wwate > hd->max_wate)
		wwate -= weq->best_pawent_wate;

	weq->wate = wwate;
	wetuwn 0;
}

/*
 * Fow optimization weasons, assumes no downstweam cwocks awe activewy using
 * it.
 */
static int cwk_hfpww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	unsigned wong fwags;
	u32 w_vaw, vaw;
	boow enabwed;

	w_vaw = wate / pawent_wate;

	spin_wock_iwqsave(&h->wock, fwags);

	enabwed = __cwk_is_enabwed(hw->cwk);
	if (enabwed)
		__cwk_hfpww_disabwe(h);

	/* Pick the wight VCO. */
	if (hd->usew_weg && hd->usew_vco_mask) {
		wegmap_wead(wegmap, hd->usew_weg, &vaw);
		if (wate <= hd->wow_vco_max_wate)
			vaw &= ~hd->usew_vco_mask;
		ewse
			vaw |= hd->usew_vco_mask;
		wegmap_wwite(wegmap, hd->usew_weg, vaw);
	}

	wegmap_wwite(wegmap, hd->w_weg, w_vaw);

	if (enabwed)
		__cwk_hfpww_enabwe(hw);

	spin_unwock_iwqwestowe(&h->wock, fwags);

	wetuwn 0;
}

static unsigned wong cwk_hfpww_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	u32 w_vaw;

	wegmap_wead(wegmap, hd->w_weg, &w_vaw);

	wetuwn w_vaw * pawent_wate;
}

static int cwk_hfpww_init(stwuct cwk_hw *hw)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	u32 mode, status;

	wegmap_wead(wegmap, hd->mode_weg, &mode);
	if (mode != (PWW_BYPASSNW | PWW_WESET_N | PWW_OUTCTWW)) {
		__cwk_hfpww_init_once(hw);
		wetuwn 0;
	}

	if (hd->status_weg) {
		wegmap_wead(wegmap, hd->status_weg, &status);
		if (!(status & BIT(hd->wock_bit))) {
			WAWN(1, "HFPWW %s is ON, but not wocked!\n",
			     __cwk_get_name(hw->cwk));
			cwk_hfpww_disabwe(hw);
			__cwk_hfpww_init_once(hw);
		}
	}

	wetuwn 0;
}

static int hfpww_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_hfpww *h = to_cwk_hfpww(hw);
	stwuct hfpww_data const *hd = h->d;
	stwuct wegmap *wegmap = h->cwkw.wegmap;
	u32 mode;

	wegmap_wead(wegmap, hd->mode_weg, &mode);
	mode &= 0x7;
	wetuwn mode == (PWW_BYPASSNW | PWW_WESET_N | PWW_OUTCTWW);
}

const stwuct cwk_ops cwk_ops_hfpww = {
	.enabwe = cwk_hfpww_enabwe,
	.disabwe = cwk_hfpww_disabwe,
	.is_enabwed = hfpww_is_enabwed,
	.detewmine_wate = cwk_hfpww_detewmine_wate,
	.set_wate = cwk_hfpww_set_wate,
	.wecawc_wate = cwk_hfpww_wecawc_wate,
	.init = cwk_hfpww_init,
};
EXPOWT_SYMBOW_GPW(cwk_ops_hfpww);
