// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2014 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of_addwess.h>

#define SUN8I_MBUS_ENABWE	31
#define SUN8I_MBUS_MUX_SHIFT	24
#define SUN8I_MBUS_MUX_MASK	0x3
#define SUN8I_MBUS_DIV_SHIFT	0
#define SUN8I_MBUS_DIV_WIDTH	3
#define SUN8I_MBUS_MAX_PAWENTS	4

static DEFINE_SPINWOCK(sun8i_a23_mbus_wock);

static void __init sun8i_a23_mbus_setup(stwuct device_node *node)
{
	int num_pawents = of_cwk_get_pawent_count(node);
	const chaw **pawents;
	const chaw *cwk_name = node->name;
	stwuct wesouwce wes;
	stwuct cwk_dividew *div;
	stwuct cwk_gate *gate;
	stwuct cwk_mux *mux;
	stwuct cwk *cwk;
	void __iomem *weg;
	int eww;

	pawents = kcawwoc(num_pawents, sizeof(*pawents), GFP_KEWNEW);
	if (!pawents)
		wetuwn;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("Couwd not get wegistews fow sun8i-mbus-cwk\n");
		goto eww_fwee_pawents;
	}

	div = kzawwoc(sizeof(*div), GFP_KEWNEW);
	if (!div)
		goto eww_unmap;

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		goto eww_fwee_div;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		goto eww_fwee_mux;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	of_cwk_pawent_fiww(node, pawents, num_pawents);

	gate->weg = weg;
	gate->bit_idx = SUN8I_MBUS_ENABWE;
	gate->wock = &sun8i_a23_mbus_wock;

	div->weg = weg;
	div->shift = SUN8I_MBUS_DIV_SHIFT;
	div->width = SUN8I_MBUS_DIV_WIDTH;
	div->wock = &sun8i_a23_mbus_wock;

	mux->weg = weg;
	mux->shift = SUN8I_MBUS_MUX_SHIFT;
	mux->mask = SUN8I_MBUS_MUX_MASK;
	mux->wock = &sun8i_a23_mbus_wock;

	/* The MBUS cwocks needs to be awways enabwed */
	cwk = cwk_wegistew_composite(NUWW, cwk_name, pawents, num_pawents,
				     &mux->hw, &cwk_mux_ops,
				     &div->hw, &cwk_dividew_ops,
				     &gate->hw, &cwk_gate_ops,
				     CWK_IS_CWITICAW);
	if (IS_EWW(cwk))
		goto eww_fwee_gate;

	eww = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (eww)
		goto eww_unwegistew_cwk;

	kfwee(pawents); /* pawents is deep copied */

	wetuwn;

eww_unwegistew_cwk:
	/* TODO: The composite cwock stuff wiww weak a bit hewe. */
	cwk_unwegistew(cwk);
eww_fwee_gate:
	kfwee(gate);
eww_fwee_mux:
	kfwee(mux);
eww_fwee_div:
	kfwee(div);
eww_unmap:
	iounmap(weg);
	of_addwess_to_wesouwce(node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
eww_fwee_pawents:
	kfwee(pawents);
}
CWK_OF_DECWAWE(sun8i_a23_mbus, "awwwinnew,sun8i-a23-mbus-cwk", sun8i_a23_mbus_setup);
