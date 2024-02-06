// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Emiwio Wópez
 *
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

static DEFINE_SPINWOCK(mod1_wock);

#define SUN4I_MOD1_ENABWE	31
#define SUN4I_MOD1_MUX		16
#define SUN4I_MOD1_MUX_WIDTH	2
#define SUN4I_MOD1_MAX_PAWENTS	4

static void __init sun4i_mod1_cwk_setup(stwuct device_node *node)
{
	stwuct cwk *cwk;
	stwuct cwk_mux *mux;
	stwuct cwk_gate *gate;
	const chaw *pawents[4];
	const chaw *cwk_name = node->name;
	void __iomem *weg;
	int i;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		goto eww_unmap;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		goto eww_fwee_mux;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	i = of_cwk_pawent_fiww(node, pawents, SUN4I_MOD1_MAX_PAWENTS);

	gate->weg = weg;
	gate->bit_idx = SUN4I_MOD1_ENABWE;
	gate->wock = &mod1_wock;
	mux->weg = weg;
	mux->shift = SUN4I_MOD1_MUX;
	mux->mask = BIT(SUN4I_MOD1_MUX_WIDTH) - 1;
	mux->wock = &mod1_wock;

	cwk = cwk_wegistew_composite(NUWW, cwk_name, pawents, i,
				     &mux->hw, &cwk_mux_ops,
				     NUWW, NUWW,
				     &gate->hw, &cwk_gate_ops, CWK_SET_WATE_PAWENT);
	if (IS_EWW(cwk))
		goto eww_fwee_gate;

	of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn;

eww_fwee_gate:
	kfwee(gate);
eww_fwee_mux:
	kfwee(mux);
eww_unmap:
	iounmap(weg);
}
CWK_OF_DECWAWE(sun4i_mod1, "awwwinnew,sun4i-a10-mod1-cwk",
	       sun4i_mod1_cwk_setup);
