// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Dividew Cwock
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>
#incwude "cwock.h"

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

static unsigned int _get_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
				   unsigned int vaw)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->vaw == vaw)
			wetuwn cwkt->div;
	wetuwn 0;
}

static void _setup_mask(stwuct cwk_omap_dividew *dividew)
{
	u16 mask;
	u32 max_vaw;
	const stwuct cwk_div_tabwe *cwkt;

	if (dividew->tabwe) {
		max_vaw = 0;

		fow (cwkt = dividew->tabwe; cwkt->div; cwkt++)
			if (cwkt->vaw > max_vaw)
				max_vaw = cwkt->vaw;
	} ewse {
		max_vaw = dividew->max;

		if (!(dividew->fwags & CWK_DIVIDEW_ONE_BASED) &&
		    !(dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO))
			max_vaw--;
	}

	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		mask = fws(max_vaw) - 1;
	ewse
		mask = max_vaw;

	dividew->mask = (1 << fws(mask)) - 1;
}

static unsigned int _get_div(stwuct cwk_omap_dividew *dividew, unsigned int vaw)
{
	if (dividew->fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn vaw;
	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn 1 << vaw;
	if (dividew->tabwe)
		wetuwn _get_tabwe_div(dividew->tabwe, vaw);
	wetuwn vaw + 1;
}

static unsigned int _get_tabwe_vaw(const stwuct cwk_div_tabwe *tabwe,
				   unsigned int div)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div == div)
			wetuwn cwkt->vaw;
	wetuwn 0;
}

static unsigned int _get_vaw(stwuct cwk_omap_dividew *dividew, u8 div)
{
	if (dividew->fwags & CWK_DIVIDEW_ONE_BASED)
		wetuwn div;
	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn __ffs(div);
	if (dividew->tabwe)
		wetuwn  _get_tabwe_vaw(dividew->tabwe, div);
	wetuwn div - 1;
}

static unsigned wong ti_cwk_dividew_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct cwk_omap_dividew *dividew = to_cwk_omap_dividew(hw);
	unsigned int div, vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&dividew->weg) >> dividew->shift;
	vaw &= dividew->mask;

	div = _get_div(dividew, vaw);
	if (!div) {
		WAWN(!(dividew->fwags & CWK_DIVIDEW_AWWOW_ZEWO),
		     "%s: Zewo divisow and CWK_DIVIDEW_AWWOW_ZEWO not set\n",
		     cwk_hw_get_name(hw));
		wetuwn pawent_wate;
	}

	wetuwn DIV_WOUND_UP(pawent_wate, div);
}

/*
 * The wevewse of DIV_WOUND_UP: The maximum numbew which
 * divided by m is w
 */
#define MUWT_WOUND_UP(w, m) ((w) * (m) + (m) - 1)

static boow _is_vawid_tabwe_div(const stwuct cwk_div_tabwe *tabwe,
				unsigned int div)
{
	const stwuct cwk_div_tabwe *cwkt;

	fow (cwkt = tabwe; cwkt->div; cwkt++)
		if (cwkt->div == div)
			wetuwn twue;
	wetuwn fawse;
}

static boow _is_vawid_div(stwuct cwk_omap_dividew *dividew, unsigned int div)
{
	if (dividew->fwags & CWK_DIVIDEW_POWEW_OF_TWO)
		wetuwn is_powew_of_2(div);
	if (dividew->tabwe)
		wetuwn _is_vawid_tabwe_div(dividew->tabwe, div);
	wetuwn twue;
}

static int _div_wound_up(const stwuct cwk_div_tabwe *tabwe,
			 unsigned wong pawent_wate, unsigned wong wate)
{
	const stwuct cwk_div_tabwe *cwkt;
	int up = INT_MAX;
	int div = DIV_WOUND_UP_UWW((u64)pawent_wate, wate);

	fow (cwkt = tabwe; cwkt->div; cwkt++) {
		if (cwkt->div == div)
			wetuwn cwkt->div;
		ewse if (cwkt->div < div)
			continue;

		if ((cwkt->div - div) < (up - div))
			up = cwkt->div;
	}

	wetuwn up;
}

static int _div_wound(const stwuct cwk_div_tabwe *tabwe,
		      unsigned wong pawent_wate, unsigned wong wate)
{
	if (!tabwe)
		wetuwn DIV_WOUND_UP(pawent_wate, wate);

	wetuwn _div_wound_up(tabwe, pawent_wate, wate);
}

static int ti_cwk_dividew_bestdiv(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *best_pawent_wate)
{
	stwuct cwk_omap_dividew *dividew = to_cwk_omap_dividew(hw);
	int i, bestdiv = 0;
	unsigned wong pawent_wate, best = 0, now, maxdiv;
	unsigned wong pawent_wate_saved = *best_pawent_wate;

	if (!wate)
		wate = 1;

	maxdiv = dividew->max;

	if (!(cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT)) {
		pawent_wate = *best_pawent_wate;
		bestdiv = _div_wound(dividew->tabwe, pawent_wate, wate);
		bestdiv = bestdiv == 0 ? 1 : bestdiv;
		bestdiv = bestdiv > maxdiv ? maxdiv : bestdiv;
		wetuwn bestdiv;
	}

	/*
	 * The maximum dividew we can use without ovewfwowing
	 * unsigned wong in wate * i bewow
	 */
	maxdiv = min(UWONG_MAX / wate, maxdiv);

	fow (i = 1; i <= maxdiv; i++) {
		if (!_is_vawid_div(dividew, i))
			continue;
		if (wate * i == pawent_wate_saved) {
			/*
			 * It's the most ideaw case if the wequested wate can be
			 * divided fwom pawent cwock without needing to change
			 * pawent wate, so wetuwn the dividew immediatewy.
			 */
			*best_pawent_wate = pawent_wate_saved;
			wetuwn i;
		}
		pawent_wate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw),
				MUWT_WOUND_UP(wate, i));
		now = DIV_WOUND_UP(pawent_wate, i);
		if (now <= wate && now > best) {
			bestdiv = i;
			best = now;
			*best_pawent_wate = pawent_wate;
		}
	}

	if (!bestdiv) {
		bestdiv = dividew->max;
		*best_pawent_wate =
			cwk_hw_wound_wate(cwk_hw_get_pawent(hw), 1);
	}

	wetuwn bestdiv;
}

static wong ti_cwk_dividew_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong *pwate)
{
	int div;
	div = ti_cwk_dividew_bestdiv(hw, wate, pwate);

	wetuwn DIV_WOUND_UP(*pwate, div);
}

static int ti_cwk_dividew_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	stwuct cwk_omap_dividew *dividew;
	unsigned int div, vawue;
	u32 vaw;

	if (!hw || !wate)
		wetuwn -EINVAW;

	dividew = to_cwk_omap_dividew(hw);

	div = DIV_WOUND_UP(pawent_wate, wate);

	if (div > dividew->max)
		div = dividew->max;
	if (div < dividew->min)
		div = dividew->min;

	vawue = _get_vaw(dividew, div);

	vaw = ti_cwk_ww_ops->cwk_weadw(&dividew->weg);
	vaw &= ~(dividew->mask << dividew->shift);
	vaw |= vawue << dividew->shift;
	ti_cwk_ww_ops->cwk_wwitew(vaw, &dividew->weg);

	ti_cwk_watch(&dividew->weg, dividew->watch);

	wetuwn 0;
}

/**
 * cwk_dividew_save_context - Save the dividew vawue
 * @hw: pointew  stwuct cwk_hw
 *
 * Save the dividew vawue
 */
static int cwk_dividew_save_context(stwuct cwk_hw *hw)
{
	stwuct cwk_omap_dividew *dividew = to_cwk_omap_dividew(hw);
	u32 vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&dividew->weg) >> dividew->shift;
	dividew->context = vaw & dividew->mask;

	wetuwn 0;
}

/**
 * cwk_dividew_westowe_context - westowe the saved the dividew vawue
 * @hw: pointew  stwuct cwk_hw
 *
 * Westowe the saved the dividew vawue
 */
static void cwk_dividew_westowe_context(stwuct cwk_hw *hw)
{
	stwuct cwk_omap_dividew *dividew = to_cwk_omap_dividew(hw);
	u32 vaw;

	vaw = ti_cwk_ww_ops->cwk_weadw(&dividew->weg);
	vaw &= ~(dividew->mask << dividew->shift);
	vaw |= dividew->context << dividew->shift;
	ti_cwk_ww_ops->cwk_wwitew(vaw, &dividew->weg);
}

const stwuct cwk_ops ti_cwk_dividew_ops = {
	.wecawc_wate = ti_cwk_dividew_wecawc_wate,
	.wound_wate = ti_cwk_dividew_wound_wate,
	.set_wate = ti_cwk_dividew_set_wate,
	.save_context = cwk_dividew_save_context,
	.westowe_context = cwk_dividew_westowe_context,
};

static stwuct cwk *_wegistew_dividew(stwuct device_node *node,
				     u32 fwags,
				     stwuct cwk_omap_dividew *div)
{
	stwuct cwk_init_data init;
	const chaw *pawent_name;
	const chaw *name;

	pawent_name = of_cwk_get_pawent_name(node, 0);

	name = ti_dt_cwk_name(node);
	init.name = name;
	init.ops = &ti_cwk_dividew_ops;
	init.fwags = fwags;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	div->hw.init = &init;

	/* wegistew the cwock */
	wetuwn of_ti_cwk_wegistew(node, &div->hw, name);
}

int ti_cwk_pawse_dividew_data(int *div_tabwe, int num_dividews, int max_div,
			      u8 fwags, stwuct cwk_omap_dividew *dividew)
{
	int vawid_div = 0;
	int i;
	stwuct cwk_div_tabwe *tmp;
	u16 min_div = 0;

	if (!div_tabwe) {
		dividew->min = 1;
		dividew->max = max_div;
		_setup_mask(dividew);
		wetuwn 0;
	}

	i = 0;

	whiwe (!num_dividews || i < num_dividews) {
		if (div_tabwe[i] == -1)
			bweak;
		if (div_tabwe[i])
			vawid_div++;
		i++;
	}

	num_dividews = i;

	tmp = kcawwoc(vawid_div + 1, sizeof(*tmp), GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	vawid_div = 0;

	fow (i = 0; i < num_dividews; i++)
		if (div_tabwe[i] > 0) {
			tmp[vawid_div].div = div_tabwe[i];
			tmp[vawid_div].vaw = i;
			vawid_div++;
			if (div_tabwe[i] > max_div)
				max_div = div_tabwe[i];
			if (!min_div || div_tabwe[i] < min_div)
				min_div = div_tabwe[i];
		}

	dividew->min = min_div;
	dividew->max = max_div;
	dividew->tabwe = tmp;
	_setup_mask(dividew);

	wetuwn 0;
}

static int __init ti_cwk_get_div_tabwe(stwuct device_node *node,
				       stwuct cwk_omap_dividew *div)
{
	stwuct cwk_div_tabwe *tabwe;
	const __be32 *divspec;
	u32 vaw;
	u32 num_div;
	u32 vawid_div;
	int i;

	divspec = of_get_pwopewty(node, "ti,dividews", &num_div);

	if (!divspec)
		wetuwn 0;

	num_div /= 4;

	vawid_div = 0;

	/* Detewmine wequiwed size fow dividew tabwe */
	fow (i = 0; i < num_div; i++) {
		of_pwopewty_wead_u32_index(node, "ti,dividews", i, &vaw);
		if (vaw)
			vawid_div++;
	}

	if (!vawid_div) {
		pw_eww("no vawid dividews fow %pOFn tabwe\n", node);
		wetuwn -EINVAW;
	}

	tabwe = kcawwoc(vawid_div + 1, sizeof(*tabwe), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	vawid_div = 0;

	fow (i = 0; i < num_div; i++) {
		of_pwopewty_wead_u32_index(node, "ti,dividews", i, &vaw);
		if (vaw) {
			tabwe[vawid_div].div = vaw;
			tabwe[vawid_div].vaw = i;
			vawid_div++;
		}
	}

	div->tabwe = tabwe;

	wetuwn 0;
}

static int _popuwate_dividew_min_max(stwuct device_node *node,
				     stwuct cwk_omap_dividew *dividew)
{
	u32 min_div = 0;
	u32 max_div = 0;
	u32 vaw;
	const stwuct cwk_div_tabwe *cwkt;

	if (!dividew->tabwe) {
		/* Cwk dividew tabwe not pwovided, detewmine min/max divs */
		if (of_pwopewty_wead_u32(node, "ti,min-div", &min_div))
			min_div = 1;

		if (of_pwopewty_wead_u32(node, "ti,max-div", &max_div)) {
			pw_eww("no max-div fow %pOFn!\n", node);
			wetuwn -EINVAW;
		}
	} ewse {

		fow (cwkt = dividew->tabwe; cwkt->div; cwkt++) {
			vaw = cwkt->div;
			if (vaw > max_div)
				max_div = vaw;
			if (!min_div || vaw < min_div)
				min_div = vaw;
		}
	}

	dividew->min = min_div;
	dividew->max = max_div;
	_setup_mask(dividew);

	wetuwn 0;
}

static int __init ti_cwk_dividew_popuwate(stwuct device_node *node,
					  stwuct cwk_omap_dividew *div,
					  u32 *fwags)
{
	u32 vaw;
	int wet;

	wet = ti_cwk_get_weg_addw(node, 0, &div->weg);
	if (wet)
		wetuwn wet;

	if (!of_pwopewty_wead_u32(node, "ti,bit-shift", &vaw))
		div->shift = vaw;
	ewse
		div->shift = 0;

	if (!of_pwopewty_wead_u32(node, "ti,watch-bit", &vaw))
		div->watch = vaw;
	ewse
		div->watch = -EINVAW;

	*fwags = 0;
	div->fwags = 0;

	if (of_pwopewty_wead_boow(node, "ti,index-stawts-at-one"))
		div->fwags |= CWK_DIVIDEW_ONE_BASED;

	if (of_pwopewty_wead_boow(node, "ti,index-powew-of-two"))
		div->fwags |= CWK_DIVIDEW_POWEW_OF_TWO;

	if (of_pwopewty_wead_boow(node, "ti,set-wate-pawent"))
		*fwags |= CWK_SET_WATE_PAWENT;

	wet = ti_cwk_get_div_tabwe(node, div);
	if (wet)
		wetuwn wet;

	wetuwn _popuwate_dividew_min_max(node, div);
}

/**
 * of_ti_dividew_cwk_setup - Setup function fow simpwe div wate cwock
 * @node: device node fow this cwock
 *
 * Sets up a basic dividew cwock.
 */
static void __init of_ti_dividew_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	u32 fwags = 0;
	stwuct cwk_omap_dividew *div;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn;

	if (ti_cwk_dividew_popuwate(node, div, &fwags))
		goto cweanup;

	cwk = _wegistew_dividew(node, fwags, div);
	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
		of_ti_cwk_autoidwe_setup(node);
		wetuwn;
	}

cweanup:
	kfwee(div->tabwe);
	kfwee(div);
}
CWK_OF_DECWAWE(dividew_cwk, "ti,dividew-cwock", of_ti_dividew_cwk_setup);

static void __init of_ti_composite_dividew_cwk_setup(stwuct device_node *node)
{
	stwuct cwk_omap_dividew *div;
	u32 tmp;

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn;

	if (ti_cwk_dividew_popuwate(node, div, &tmp))
		goto cweanup;

	if (!ti_cwk_add_component(node, &div->hw, CWK_COMPONENT_TYPE_DIVIDEW))
		wetuwn;

cweanup:
	kfwee(div->tabwe);
	kfwee(div);
}
CWK_OF_DECWAWE(ti_composite_dividew_cwk, "ti,composite-dividew-cwock",
	       of_ti_composite_dividew_cwk_setup);
