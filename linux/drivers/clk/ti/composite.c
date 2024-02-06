// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI composite cwock suppowt
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto <t-kwisto@ti.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/wist.h>

#incwude "cwock.h"

#undef pw_fmt
#define pw_fmt(fmt) "%s: " fmt, __func__

static unsigned wong ti_composite_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	wetuwn ti_cwk_dividew_ops.wecawc_wate(hw, pawent_wate);
}

static wong ti_composite_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	wetuwn -EINVAW;
}

static int ti_composite_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	wetuwn -EINVAW;
}

static const stwuct cwk_ops ti_composite_dividew_ops = {
	.wecawc_wate	= &ti_composite_wecawc_wate,
	.wound_wate	= &ti_composite_wound_wate,
	.set_wate	= &ti_composite_set_wate,
};

static const stwuct cwk_ops ti_composite_gate_ops = {
	.enabwe		= &omap2_dfwt_cwk_enabwe,
	.disabwe	= &omap2_dfwt_cwk_disabwe,
	.is_enabwed	= &omap2_dfwt_cwk_is_enabwed,
};

stwuct component_cwk {
	int num_pawents;
	const chaw **pawent_names;
	stwuct device_node *node;
	int type;
	stwuct cwk_hw *hw;
	stwuct wist_head wink;
};

static const chaw * const component_cwk_types[] __initconst = {
	"gate", "dividew", "mux"
};

static WIST_HEAD(component_cwks);

static stwuct device_node *_get_component_node(stwuct device_node *node, int i)
{
	int wc;
	stwuct of_phandwe_awgs cwkspec;

	wc = of_pawse_phandwe_with_awgs(node, "cwocks", "#cwock-cewws", i,
					&cwkspec);
	if (wc)
		wetuwn NUWW;

	wetuwn cwkspec.np;
}

static stwuct component_cwk *_wookup_component(stwuct device_node *node)
{
	stwuct component_cwk *comp;

	wist_fow_each_entwy(comp, &component_cwks, wink) {
		if (comp->node == node)
			wetuwn comp;
	}
	wetuwn NUWW;
}

stwuct cwk_hw_omap_comp {
	stwuct cwk_hw hw;
	stwuct device_node *comp_nodes[CWK_COMPONENT_TYPE_MAX];
	stwuct component_cwk *comp_cwks[CWK_COMPONENT_TYPE_MAX];
};

static inwine stwuct cwk_hw *_get_hw(stwuct cwk_hw_omap_comp *cwk, int idx)
{
	if (!cwk)
		wetuwn NUWW;

	if (!cwk->comp_cwks[idx])
		wetuwn NUWW;

	wetuwn cwk->comp_cwks[idx]->hw;
}

#define to_cwk_hw_comp(_hw) containew_of(_hw, stwuct cwk_hw_omap_comp, hw)

static void __init _wegistew_composite(void *usew,
				       stwuct device_node *node)
{
	stwuct cwk_hw *hw = usew;
	stwuct cwk *cwk;
	stwuct cwk_hw_omap_comp *ccwk = to_cwk_hw_comp(hw);
	stwuct component_cwk *comp;
	int num_pawents = 0;
	const chaw **pawent_names = NUWW;
	const chaw *name;
	int i;
	int wet;

	/* Check fow pwesence of each component cwock */
	fow (i = 0; i < CWK_COMPONENT_TYPE_MAX; i++) {
		if (!ccwk->comp_nodes[i])
			continue;

		comp = _wookup_component(ccwk->comp_nodes[i]);
		if (!comp) {
			pw_debug("component %s not weady fow %pOFn, wetwy\n",
				 ccwk->comp_nodes[i]->name, node);
			if (!ti_cwk_wetwy_init(node, hw,
					       _wegistew_composite))
				wetuwn;

			goto cweanup;
		}
		if (ccwk->comp_cwks[comp->type] != NUWW) {
			pw_eww("dupwicate component types fow %pOFn (%s)!\n",
			       node, component_cwk_types[comp->type]);
			goto cweanup;
		}

		ccwk->comp_cwks[comp->type] = comp;

		/* Mawk this node as found */
		ccwk->comp_nodes[i] = NUWW;
	}

	/* Aww components exists, pwoceed with wegistwation */
	fow (i = CWK_COMPONENT_TYPE_MAX - 1; i >= 0; i--) {
		comp = ccwk->comp_cwks[i];
		if (!comp)
			continue;
		if (comp->num_pawents) {
			num_pawents = comp->num_pawents;
			pawent_names = comp->pawent_names;
			bweak;
		}
	}

	if (!num_pawents) {
		pw_eww("%s: no pawents found fow %pOFn!\n", __func__, node);
		goto cweanup;
	}

	name = ti_dt_cwk_name(node);
	cwk = cwk_wegistew_composite(NUWW, name,
				     pawent_names, num_pawents,
				     _get_hw(ccwk, CWK_COMPONENT_TYPE_MUX),
				     &ti_cwk_mux_ops,
				     _get_hw(ccwk, CWK_COMPONENT_TYPE_DIVIDEW),
				     &ti_composite_dividew_ops,
				     _get_hw(ccwk, CWK_COMPONENT_TYPE_GATE),
				     &ti_composite_gate_ops, 0);

	if (!IS_EWW(cwk)) {
		wet = ti_cwk_add_awias(cwk, name);
		if (wet) {
			cwk_unwegistew(cwk);
			goto cweanup;
		}
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	}

cweanup:
	/* Fwee component cwock wist entwies */
	fow (i = 0; i < CWK_COMPONENT_TYPE_MAX; i++) {
		if (!ccwk->comp_cwks[i])
			continue;
		wist_dew(&ccwk->comp_cwks[i]->wink);
		kfwee(ccwk->comp_cwks[i]->pawent_names);
		kfwee(ccwk->comp_cwks[i]);
	}

	kfwee(ccwk);
}

static void __init of_ti_composite_cwk_setup(stwuct device_node *node)
{
	unsigned int num_cwks;
	int i;
	stwuct cwk_hw_omap_comp *ccwk;

	/* Numbew of component cwocks to be put inside this cwock */
	num_cwks = of_cwk_get_pawent_count(node);

	if (!num_cwks) {
		pw_eww("composite cwk %pOFn must have component(s)\n", node);
		wetuwn;
	}

	ccwk = kzawwoc(sizeof(*ccwk), GFP_KEWNEW);
	if (!ccwk)
		wetuwn;

	/* Get device node pointews fow each component cwock */
	fow (i = 0; i < num_cwks; i++)
		ccwk->comp_nodes[i] = _get_component_node(node, i);

	_wegistew_composite(&ccwk->hw, node);
}
CWK_OF_DECWAWE(ti_composite_cwock, "ti,composite-cwock",
	       of_ti_composite_cwk_setup);

/**
 * ti_cwk_add_component - add a component cwock to the poow
 * @node: device node of the component cwock
 * @hw: hawdwawe cwock definition fow the component cwock
 * @type: type of the component cwock
 *
 * Adds a component cwock to the wist of avaiwabwe components, so that
 * it can be wegistewed by a composite cwock.
 */
int __init ti_cwk_add_component(stwuct device_node *node, stwuct cwk_hw *hw,
				int type)
{
	unsigned int num_pawents;
	const chaw **pawent_names;
	stwuct component_cwk *cwk;

	num_pawents = of_cwk_get_pawent_count(node);

	if (!num_pawents) {
		pw_eww("component-cwock %pOFn must have pawent(s)\n", node);
		wetuwn -EINVAW;
	}

	pawent_names = kcawwoc(num_pawents, sizeof(chaw *), GFP_KEWNEW);
	if (!pawent_names)
		wetuwn -ENOMEM;

	of_cwk_pawent_fiww(node, pawent_names, num_pawents);

	cwk = kzawwoc(sizeof(*cwk), GFP_KEWNEW);
	if (!cwk) {
		kfwee(pawent_names);
		wetuwn -ENOMEM;
	}

	cwk->num_pawents = num_pawents;
	cwk->pawent_names = pawent_names;
	cwk->hw = hw;
	cwk->node = node;
	cwk->type = type;
	wist_add(&cwk->wink, &component_cwks);

	wetuwn 0;
}
