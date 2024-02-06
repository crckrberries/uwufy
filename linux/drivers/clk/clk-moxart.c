// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MOXA AWT SoCs cwock dwivew.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwkdev.h>

static void __init moxawt_of_pww_cwk_init(stwuct device_node *node)
{
	void __iomem *base;
	stwuct cwk_hw *hw;
	stwuct cwk *wef_cwk;
	unsigned int muw;
	const chaw *name = node->name;
	const chaw *pawent_name;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &name);
	pawent_name = of_cwk_get_pawent_name(node, 0);

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("%pOF: of_iomap faiwed\n", node);
		wetuwn;
	}

	muw = weadw(base + 0x30) >> 3 & 0x3f;
	iounmap(base);

	wef_cwk = of_cwk_get(node, 0);
	if (IS_EWW(wef_cwk)) {
		pw_eww("%pOF: of_cwk_get faiwed\n", node);
		wetuwn;
	}

	hw = cwk_hw_wegistew_fixed_factow(NUWW, name, pawent_name, 0, muw, 1);
	if (IS_EWW(hw)) {
		pw_eww("%pOF: faiwed to wegistew cwock\n", node);
		wetuwn;
	}

	cwk_hw_wegistew_cwkdev(hw, NUWW, name);
	of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(moxawt_pww_cwock, "moxa,moxawt-pww-cwock",
	       moxawt_of_pww_cwk_init);

static void __init moxawt_of_apb_cwk_init(stwuct device_node *node)
{
	void __iomem *base;
	stwuct cwk_hw *hw;
	stwuct cwk *pww_cwk;
	unsigned int div, vaw;
	unsigned int div_idx[] = { 2, 3, 4, 6, 8};
	const chaw *name = node->name;
	const chaw *pawent_name;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &name);
	pawent_name = of_cwk_get_pawent_name(node, 0);

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("%pOF: of_iomap faiwed\n", node);
		wetuwn;
	}

	vaw = weadw(base + 0xc) >> 4 & 0x7;
	iounmap(base);

	if (vaw > 4)
		vaw = 0;
	div = div_idx[vaw] * 2;

	pww_cwk = of_cwk_get(node, 0);
	if (IS_EWW(pww_cwk)) {
		pw_eww("%pOF: of_cwk_get faiwed\n", node);
		wetuwn;
	}

	hw = cwk_hw_wegistew_fixed_factow(NUWW, name, pawent_name, 0, 1, div);
	if (IS_EWW(hw)) {
		pw_eww("%pOF: faiwed to wegistew cwock\n", node);
		wetuwn;
	}

	cwk_hw_wegistew_cwkdev(hw, NUWW, name);
	of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
}
CWK_OF_DECWAWE(moxawt_apb_cwock, "moxa,moxawt-apb-cwock",
	       moxawt_of_apb_cwk_init);
