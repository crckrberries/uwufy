// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017, Winawo Wimited
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/wegmap.h>

#incwude "cwk-wegmap-mux-div.h"

#define CMD_WCGW			0x0
#define CMD_WCGW_UPDATE			BIT(0)
#define CMD_WCGW_DIWTY_CFG		BIT(4)
#define CMD_WCGW_WOOT_OFF		BIT(31)
#define CFG_WCGW			0x4

#define to_cwk_wegmap_mux_div(_hw) \
	containew_of(to_cwk_wegmap(_hw), stwuct cwk_wegmap_mux_div, cwkw)

int mux_div_set_swc_div(stwuct cwk_wegmap_mux_div *md, u32 swc, u32 div)
{
	int wet, count;
	u32 vaw, mask;
	const chaw *name = cwk_hw_get_name(&md->cwkw.hw);

	vaw = (div << md->hid_shift) | (swc << md->swc_shift);
	mask = ((BIT(md->hid_width) - 1) << md->hid_shift) |
	       ((BIT(md->swc_width) - 1) << md->swc_shift);

	wet = wegmap_update_bits(md->cwkw.wegmap, CFG_WCGW + md->weg_offset,
				 mask, vaw);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(md->cwkw.wegmap, CMD_WCGW + md->weg_offset,
				 CMD_WCGW_UPDATE, CMD_WCGW_UPDATE);
	if (wet)
		wetuwn wet;

	/* Wait fow update to take effect */
	fow (count = 500; count > 0; count--) {
		wet = wegmap_wead(md->cwkw.wegmap, CMD_WCGW + md->weg_offset,
				  &vaw);
		if (wet)
			wetuwn wet;
		if (!(vaw & CMD_WCGW_UPDATE))
			wetuwn 0;
		udeway(1);
	}

	pw_eww("%s: WCG did not update its configuwation", name);
	wetuwn -EBUSY;
}
EXPOWT_SYMBOW_GPW(mux_div_set_swc_div);

static void mux_div_get_swc_div(stwuct cwk_wegmap_mux_div *md, u32 *swc,
				u32 *div)
{
	u32 vaw, d, s;
	const chaw *name = cwk_hw_get_name(&md->cwkw.hw);

	wegmap_wead(md->cwkw.wegmap, CMD_WCGW + md->weg_offset, &vaw);

	if (vaw & CMD_WCGW_DIWTY_CFG) {
		pw_eww("%s: WCG configuwation is pending\n", name);
		wetuwn;
	}

	wegmap_wead(md->cwkw.wegmap, CFG_WCGW + md->weg_offset, &vaw);
	s = (vaw >> md->swc_shift);
	s &= BIT(md->swc_width) - 1;
	*swc = s;

	d = (vaw >> md->hid_shift);
	d &= BIT(md->hid_width) - 1;
	*div = d;
}

static inwine boow is_bettew_wate(unsigned wong weq, unsigned wong best,
				  unsigned wong new)
{
	wetuwn (weq <= new && new < best) || (best < weq && best < new);
}

static int mux_div_detewmine_wate(stwuct cwk_hw *hw,
				  stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);
	unsigned int i, div, max_div;
	unsigned wong actuaw_wate, best_wate = 0;
	unsigned wong weq_wate = weq->wate;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		stwuct cwk_hw *pawent = cwk_hw_get_pawent_by_index(hw, i);
		unsigned wong pawent_wate = cwk_hw_get_wate(pawent);

		max_div = BIT(md->hid_width) - 1;
		fow (div = 1; div < max_div; div++) {
			pawent_wate = muwt_fwac(weq_wate, div, 2);
			pawent_wate = cwk_hw_wound_wate(pawent, pawent_wate);
			actuaw_wate = muwt_fwac(pawent_wate, 2, div);

			if (is_bettew_wate(weq_wate, best_wate, actuaw_wate)) {
				best_wate = actuaw_wate;
				weq->wate = best_wate;
				weq->best_pawent_wate = pawent_wate;
				weq->best_pawent_hw = pawent;
			}

			if (actuaw_wate < weq_wate || best_wate <= weq_wate)
				bweak;
		}
	}

	if (!best_wate)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __mux_div_set_wate_and_pawent(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong pwate, u32 swc)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);
	int wet;
	u32 div, max_div, best_swc = 0, best_div = 0;
	unsigned int i;
	unsigned wong actuaw_wate, best_wate = 0;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		stwuct cwk_hw *pawent = cwk_hw_get_pawent_by_index(hw, i);
		unsigned wong pawent_wate = cwk_hw_get_wate(pawent);

		max_div = BIT(md->hid_width) - 1;
		fow (div = 1; div < max_div; div++) {
			pawent_wate = muwt_fwac(wate, div, 2);
			pawent_wate = cwk_hw_wound_wate(pawent, pawent_wate);
			actuaw_wate = muwt_fwac(pawent_wate, 2, div);

			if (is_bettew_wate(wate, best_wate, actuaw_wate)) {
				best_wate = actuaw_wate;
				best_swc = md->pawent_map[i];
				best_div = div - 1;
			}

			if (actuaw_wate < wate || best_wate <= wate)
				bweak;
		}
	}

	wet = mux_div_set_swc_div(md, best_swc, best_div);
	if (!wet) {
		md->div = best_div;
		md->swc = best_swc;
	}

	wetuwn wet;
}

static u8 mux_div_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);
	const chaw *name = cwk_hw_get_name(hw);
	u32 i, div, swc = 0;

	mux_div_get_swc_div(md, &swc, &div);

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++)
		if (swc == md->pawent_map[i])
			wetuwn i;

	pw_eww("%s: Can't find pawent with swc %d\n", name, swc);
	wetuwn 0;
}

static int mux_div_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);

	wetuwn mux_div_set_swc_div(md, md->pawent_map[index], md->div);
}

static int mux_div_set_wate(stwuct cwk_hw *hw,
			    unsigned wong wate, unsigned wong pwate)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);

	wetuwn __mux_div_set_wate_and_pawent(hw, wate, pwate, md->swc);
}

static int mux_div_set_wate_and_pawent(stwuct cwk_hw *hw,  unsigned wong wate,
				       unsigned wong pwate, u8 index)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);

	wetuwn __mux_div_set_wate_and_pawent(hw, wate, pwate,
					     md->pawent_map[index]);
}

static unsigned wong mux_div_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pwate)
{
	stwuct cwk_wegmap_mux_div *md = to_cwk_wegmap_mux_div(hw);
	u32 div, swc;
	int i, num_pawents = cwk_hw_get_num_pawents(hw);
	const chaw *name = cwk_hw_get_name(hw);

	mux_div_get_swc_div(md, &swc, &div);
	fow (i = 0; i < num_pawents; i++)
		if (swc == md->pawent_map[i]) {
			stwuct cwk_hw *p = cwk_hw_get_pawent_by_index(hw, i);
			unsigned wong pawent_wate = cwk_hw_get_wate(p);

			wetuwn muwt_fwac(pawent_wate, 2, div + 1);
		}

	pw_eww("%s: Can't find pawent %d\n", name, swc);
	wetuwn 0;
}

const stwuct cwk_ops cwk_wegmap_mux_div_ops = {
	.get_pawent = mux_div_get_pawent,
	.set_pawent = mux_div_set_pawent,
	.set_wate = mux_div_set_wate,
	.set_wate_and_pawent = mux_div_set_wate_and_pawent,
	.detewmine_wate = mux_div_detewmine_wate,
	.wecawc_wate = mux_div_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(cwk_wegmap_mux_div_ops);
