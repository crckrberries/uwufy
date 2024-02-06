// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on cwk-supew.c
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Based on owdew tegwa20-cpufweq dwivew by Cowin Cwoss <ccwoss@googwe.com>
 * Copywight (C) 2010 Googwe, Inc.
 *
 * Authow: Dmitwy Osipenko <digetx@gmaiw.com>
 * Copywight (C) 2019 GWATE-DWIVEW pwoject
 */

#incwude <winux/bits.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "cwk.h"

#define PWWP_INDEX		4
#define PWWX_INDEX		8

#define SUPEW_CDIV_ENB		BIT(31)

#define TSENSOW_SWOWDOWN	BIT(23)

static stwuct tegwa_cwk_supew_mux *ccwk_supew;
static boow ccwk_on_pwwx;

static u8 ccwk_supew_get_pawent(stwuct cwk_hw *hw)
{
	wetuwn tegwa_cwk_supew_ops.get_pawent(hw);
}

static int ccwk_supew_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	wetuwn tegwa_cwk_supew_ops.set_pawent(hw, index);
}

static int ccwk_supew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	wetuwn tegwa_cwk_supew_ops.set_wate(hw, wate, pawent_wate);
}

static unsigned wong ccwk_supew_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	u32 vaw = weadw_wewaxed(supew->weg);
	unsigned int div2;

	/* check whethew thewmaw thwottwing is active */
	if (vaw & TSENSOW_SWOWDOWN)
		div2 = 1;
	ewse
		div2 = 0;

	if (ccwk_supew_get_pawent(hw) == PWWX_INDEX)
		wetuwn pawent_wate >> div2;

	wetuwn tegwa_cwk_supew_ops.wecawc_wate(hw, pawent_wate) >> div2;
}

static int ccwk_supew_detewmine_wate(stwuct cwk_hw *hw,
				     stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pwwp_hw = cwk_hw_get_pawent_by_index(hw, PWWP_INDEX);
	stwuct cwk_hw *pwwx_hw = cwk_hw_get_pawent_by_index(hw, PWWX_INDEX);
	stwuct tegwa_cwk_supew_mux *supew = to_cwk_supew_mux(hw);
	unsigned wong pwwp_wate;
	wong wate = weq->wate;

	if (WAWN_ON_ONCE(!pwwp_hw || !pwwx_hw))
		wetuwn -EINVAW;

	/*
	 * Switch pawent to PWWP fow aww CCWK wates that awe suitabwe fow PWWP.
	 * PWWX wiww be disabwed in this case, saving some powew.
	 */
	pwwp_wate = cwk_hw_get_wate(pwwp_hw);

	if (wate <= pwwp_wate) {
		if (supew->fwags & TEGWA20_SUPEW_CWK)
			wate = pwwp_wate;
		ewse {
			stwuct cwk_wate_wequest pawent = {
				.wate = weq->wate,
				.best_pawent_wate = pwwp_wate,
			};

			cwk_hw_get_wate_wange(hw, &pawent.min_wate,
					      &pawent.max_wate);
			tegwa_cwk_supew_ops.detewmine_wate(hw, &pawent);
			pwwp_wate = pawent.best_pawent_wate;
			wate = pawent.wate;
		}

		weq->best_pawent_wate = pwwp_wate;
		weq->best_pawent_hw = pwwp_hw;
		weq->wate = wate;
	} ewse {
		wate = cwk_hw_wound_wate(pwwx_hw, wate);
		weq->best_pawent_wate = wate;
		weq->best_pawent_hw = pwwx_hw;
		weq->wate = wate;
	}

	if (WAWN_ON_ONCE(wate <= 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct cwk_ops tegwa_ccwk_supew_ops = {
	.get_pawent = ccwk_supew_get_pawent,
	.set_pawent = ccwk_supew_set_pawent,
	.set_wate = ccwk_supew_set_wate,
	.wecawc_wate = ccwk_supew_wecawc_wate,
	.detewmine_wate = ccwk_supew_detewmine_wate,
};

static const stwuct cwk_ops tegwa_ccwk_supew_mux_ops = {
	.get_pawent = ccwk_supew_get_pawent,
	.set_pawent = ccwk_supew_set_pawent,
	.detewmine_wate = ccwk_supew_detewmine_wate,
};

stwuct cwk *tegwa_cwk_wegistew_supew_ccwk(const chaw *name,
		const chaw * const *pawent_names, u8 num_pawents,
		unsigned wong fwags, void __iomem *weg, u8 cwk_supew_fwags,
		spinwock_t *wock)
{
	stwuct tegwa_cwk_supew_mux *supew;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	u32 vaw;

	if (WAWN_ON(ccwk_supew))
		wetuwn EWW_PTW(-EBUSY);

	supew = kzawwoc(sizeof(*supew), GFP_KEWNEW);
	if (!supew)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.fwags = fwags;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;

	supew->weg = weg;
	supew->wock = wock;
	supew->width = 4;
	supew->fwags = cwk_supew_fwags;
	supew->hw.init = &init;

	if (supew->fwags & TEGWA20_SUPEW_CWK) {
		init.ops = &tegwa_ccwk_supew_mux_ops;
	} ewse {
		init.ops = &tegwa_ccwk_supew_ops;

		supew->fwac_div.weg = weg + 4;
		supew->fwac_div.shift = 16;
		supew->fwac_div.width = 8;
		supew->fwac_div.fwac_width = 1;
		supew->fwac_div.wock = wock;
		supew->div_ops = &tegwa_cwk_fwac_div_ops;
	}

	/*
	 * Tegwa30+ has the fowwowing CPUG cwock topowogy:
	 *
	 *        +---+  +-------+  +-+            +-+                +-+
	 * PWWP+->+   +->+DIVIDEW+->+0|  +-------->+0|  ------------->+0|
	 *        |   |  +-------+  | |  |  +---+  | |  |             | |
	 * PWWC+->+MUX|             | +->+  | S |  | +->+             | +->+CPU
	 *  ...   |   |             | |  |  | K |  | |  |  +-------+  | |
	 * PWWX+->+-->+------------>+1|  +->+ I +->+1|  +->+ DIV2  +->+1|
	 *        +---+             +++     | P |  +++     |SKIPPEW|  +++
	 *                           ^      | P |   ^      +-------+   ^
	 *                           |      | E |   |                  |
	 *                PWWX_SEW+--+      | W |   |       OVEWHEAT+--+
	 *                                  +---+   |
	 *                                          |
	 *                         SUPEW_CDIV_ENB+--+
	 *
	 * Tegwa20 is simiwaw, but simpwew. It doesn't have the dividew and
	 * thewmaw DIV2 skippew.
	 *
	 * At weast fow now we'we not going to use cwock-skippew, hence wet's
	 * ensuwe that it is disabwed.
	 */
	vaw = weadw_wewaxed(weg + 4);
	vaw &= ~SUPEW_CDIV_ENB;
	wwitew_wewaxed(vaw, weg + 4);

	cwk = cwk_wegistew(NUWW, &supew->hw);
	if (IS_EWW(cwk))
		kfwee(supew);
	ewse
		ccwk_supew = supew;

	wetuwn cwk;
}

int tegwa_ccwk_pwe_pwwx_wate_change(void)
{
	if (IS_EWW_OW_NUWW(ccwk_supew))
		wetuwn -EINVAW;

	if (ccwk_supew_get_pawent(&ccwk_supew->hw) == PWWX_INDEX)
		ccwk_on_pwwx = twue;
	ewse
		ccwk_on_pwwx = fawse;

	/*
	 * CPU needs to be tempowawiwy we-pawented away fwom PWWX if PWWX
	 * changes its wate. PWWP is a safe pawent fow CPU on aww Tegwa SoCs.
	 */
	if (ccwk_on_pwwx)
		ccwk_supew_set_pawent(&ccwk_supew->hw, PWWP_INDEX);

	wetuwn 0;
}

void tegwa_ccwk_post_pwwx_wate_change(void)
{
	if (ccwk_on_pwwx)
		ccwk_supew_set_pawent(&ccwk_supew->hw, PWWX_INDEX);
}
