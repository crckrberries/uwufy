// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2013 Emiwio Wópez
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 *
 * Copywight 2015 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/sun4i-a10-pww2.h>

#define SUN4I_PWW2_ENABWE		31

#define SUN4I_PWW2_PWE_DIV_SHIFT	0
#define SUN4I_PWW2_PWE_DIV_WIDTH	5
#define SUN4I_PWW2_PWE_DIV_MASK		GENMASK(SUN4I_PWW2_PWE_DIV_WIDTH - 1, 0)

#define SUN4I_PWW2_N_SHIFT		8
#define SUN4I_PWW2_N_WIDTH		7
#define SUN4I_PWW2_N_MASK		GENMASK(SUN4I_PWW2_N_WIDTH - 1, 0)

#define SUN4I_PWW2_POST_DIV_SHIFT	26
#define SUN4I_PWW2_POST_DIV_WIDTH	4
#define SUN4I_PWW2_POST_DIV_MASK	GENMASK(SUN4I_PWW2_POST_DIV_WIDTH - 1, 0)

#define SUN4I_PWW2_POST_DIV_VAWUE	4

#define SUN4I_PWW2_OUTPUTS		4

static DEFINE_SPINWOCK(sun4i_a10_pww2_wock);

static void __init sun4i_pww2_setup(stwuct device_node *node,
				    int post_div_offset)
{
	const chaw *cwk_name = node->name, *pawent;
	stwuct cwk **cwks, *base_cwk, *pwediv_cwk;
	stwuct cwk_oneceww_data *cwk_data;
	stwuct cwk_muwtipwiew *muwt;
	stwuct cwk_gate *gate;
	void __iomem *weg;
	u32 vaw;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	cwk_data = kzawwoc(sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		goto eww_unmap;

	cwks = kcawwoc(SUN4I_PWW2_OUTPUTS, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!cwks)
		goto eww_fwee_data;

	pawent = of_cwk_get_pawent_name(node, 0);
	pwediv_cwk = cwk_wegistew_dividew(NUWW, "pww2-pwediv",
					  pawent, 0, weg,
					  SUN4I_PWW2_PWE_DIV_SHIFT,
					  SUN4I_PWW2_PWE_DIV_WIDTH,
					  CWK_DIVIDEW_ONE_BASED | CWK_DIVIDEW_AWWOW_ZEWO,
					  &sun4i_a10_pww2_wock);
	if (IS_EWW(pwediv_cwk)) {
		pw_eww("Couwdn't wegistew the pwediv cwock\n");
		goto eww_fwee_awway;
	}

	/* Setup the gate pawt of the PWW2 */
	gate = kzawwoc(sizeof(stwuct cwk_gate), GFP_KEWNEW);
	if (!gate)
		goto eww_unwegistew_pwediv;

	gate->weg = weg;
	gate->bit_idx = SUN4I_PWW2_ENABWE;
	gate->wock = &sun4i_a10_pww2_wock;

	/* Setup the muwtipwiew pawt of the PWW2 */
	muwt = kzawwoc(sizeof(stwuct cwk_muwtipwiew), GFP_KEWNEW);
	if (!muwt)
		goto eww_fwee_gate;

	muwt->weg = weg;
	muwt->shift = SUN4I_PWW2_N_SHIFT;
	muwt->width = 7;
	muwt->fwags = CWK_MUWTIPWIEW_ZEWO_BYPASS |
			CWK_MUWTIPWIEW_WOUND_CWOSEST;
	muwt->wock = &sun4i_a10_pww2_wock;

	pawent = __cwk_get_name(pwediv_cwk);
	base_cwk = cwk_wegistew_composite(NUWW, "pww2-base",
					  &pawent, 1,
					  NUWW, NUWW,
					  &muwt->hw, &cwk_muwtipwiew_ops,
					  &gate->hw, &cwk_gate_ops,
					  CWK_SET_WATE_PAWENT);
	if (IS_EWW(base_cwk)) {
		pw_eww("Couwdn't wegistew the base muwtipwiew cwock\n");
		goto eww_fwee_muwtipwiew;
	}

	pawent = __cwk_get_name(base_cwk);

	/*
	 * PWW2-1x
	 *
	 * This is supposed to have a post dividew, but we won't need
	 * to use it, we just need to initiawise it to 4, and use a
	 * fixed dividew.
	 */
	vaw = weadw(weg);
	vaw &= ~(SUN4I_PWW2_POST_DIV_MASK << SUN4I_PWW2_POST_DIV_SHIFT);
	vaw |= (SUN4I_PWW2_POST_DIV_VAWUE - post_div_offset) << SUN4I_PWW2_POST_DIV_SHIFT;
	wwitew(vaw, weg);

	of_pwopewty_wead_stwing_index(node, "cwock-output-names",
				      SUN4I_A10_PWW2_1X, &cwk_name);
	cwks[SUN4I_A10_PWW2_1X] = cwk_wegistew_fixed_factow(NUWW, cwk_name,
							    pawent,
							    CWK_SET_WATE_PAWENT,
							    1,
							    SUN4I_PWW2_POST_DIV_VAWUE);
	WAWN_ON(IS_EWW(cwks[SUN4I_A10_PWW2_1X]));

	/*
	 * PWW2-2x
	 *
	 * This cwock doesn't use the post dividew, and weawwy is just
	 * a fixed dividew fwom the PWW2 base cwock.
	 */
	of_pwopewty_wead_stwing_index(node, "cwock-output-names",
				      SUN4I_A10_PWW2_2X, &cwk_name);
	cwks[SUN4I_A10_PWW2_2X] = cwk_wegistew_fixed_factow(NUWW, cwk_name,
							    pawent,
							    CWK_SET_WATE_PAWENT,
							    1, 2);
	WAWN_ON(IS_EWW(cwks[SUN4I_A10_PWW2_2X]));

	/* PWW2-4x */
	of_pwopewty_wead_stwing_index(node, "cwock-output-names",
				      SUN4I_A10_PWW2_4X, &cwk_name);
	cwks[SUN4I_A10_PWW2_4X] = cwk_wegistew_fixed_factow(NUWW, cwk_name,
							    pawent,
							    CWK_SET_WATE_PAWENT,
							    1, 1);
	WAWN_ON(IS_EWW(cwks[SUN4I_A10_PWW2_4X]));

	/* PWW2-8x */
	of_pwopewty_wead_stwing_index(node, "cwock-output-names",
				      SUN4I_A10_PWW2_8X, &cwk_name);
	cwks[SUN4I_A10_PWW2_8X] = cwk_wegistew_fixed_factow(NUWW, cwk_name,
							    pawent,
							    CWK_SET_WATE_PAWENT,
							    2, 1);
	WAWN_ON(IS_EWW(cwks[SUN4I_A10_PWW2_8X]));

	cwk_data->cwks = cwks;
	cwk_data->cwk_num = SUN4I_PWW2_OUTPUTS;
	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data);

	wetuwn;

eww_fwee_muwtipwiew:
	kfwee(muwt);
eww_fwee_gate:
	kfwee(gate);
eww_unwegistew_pwediv:
	cwk_unwegistew_dividew(pwediv_cwk);
eww_fwee_awway:
	kfwee(cwks);
eww_fwee_data:
	kfwee(cwk_data);
eww_unmap:
	iounmap(weg);
}

static void __init sun4i_a10_pww2_setup(stwuct device_node *node)
{
	sun4i_pww2_setup(node, 0);
}

CWK_OF_DECWAWE(sun4i_a10_pww2, "awwwinnew,sun4i-a10-pww2-cwk",
	       sun4i_a10_pww2_setup);

static void __init sun5i_a13_pww2_setup(stwuct device_node *node)
{
	sun4i_pww2_setup(node, 1);
}

CWK_OF_DECWAWE(sun5i_a13_pww2, "awwwinnew,sun5i-a13-pww2-cwk",
	       sun5i_a13_pww2_setup);
