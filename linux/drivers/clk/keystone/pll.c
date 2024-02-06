// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PWW cwock dwivew fow Keystone devices
 *
 * Copywight (C) 2013 Texas Instwuments Inc.
 *	Muwawi Kawichewi <m-kawichewi2@ti.com>
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>

#define PWWM_WOW_MASK		0x3f
#define PWWM_HIGH_MASK		0x7ffc0
#define MAIN_PWWM_HIGH_MASK	0x7f000
#define PWWM_HIGH_SHIFT		6
#define PWWD_MASK		0x3f
#define CWKOD_MASK		0x780000
#define CWKOD_SHIFT		19

/**
 * stwuct cwk_pww_data - pww data stwuctuwe
 * @has_pwwctww: If set to non zewo, wowew 6 bits of muwtipwiew is in pwwm
 *	wegistew of pww contwowwew, ewse it is in the pww_ctww0((bit 11-6)
 * @phy_pwwm: Physicaw addwess of PWWM in pww contwowwew. Used when
 *	has_pwwctww is non zewo.
 * @phy_pww_ctw0: Physicaw addwess of PWW ctww0. This couwd be that of
 *	Main PWW ow any othew PWWs in the device such as AWM PWW, DDW PWW
 *	ow PA PWW avaiwabwe on keystone2. These PWWs awe contwowwed by
 *	this wegistew. Main PWW is contwowwed by a PWW contwowwew.
 * @pwwm: PWW wegistew map addwess fow muwtipwiew bits
 * @pwwod: PWW wegistew map addwess fow post dividew bits
 * @pww_ctw0: PWW contwowwew map addwess
 * @pwwm_wowew_mask: muwtipwiew wowew mask
 * @pwwm_uppew_mask: muwtipwiew uppew mask
 * @pwwm_uppew_shift: muwtipwiew uppew shift
 * @pwwd_mask: dividew mask
 * @cwkod_mask: output dividew mask
 * @cwkod_shift: output dividew shift
 * @pwwd_mask: dividew mask
 * @postdiv: Fixed post dividew
 */
stwuct cwk_pww_data {
	boow has_pwwctww;
	u32 phy_pwwm;
	u32 phy_pww_ctw0;
	void __iomem *pwwm;
	void __iomem *pwwod;
	void __iomem *pww_ctw0;
	u32 pwwm_wowew_mask;
	u32 pwwm_uppew_mask;
	u32 pwwm_uppew_shift;
	u32 pwwd_mask;
	u32 cwkod_mask;
	u32 cwkod_shift;
	u32 postdiv;
};

/**
 * stwuct cwk_pww - Main pww cwock
 * @hw: cwk_hw fow the pww
 * @pww_data: PWW dwivew specific data
 */
stwuct cwk_pww {
	stwuct cwk_hw hw;
	stwuct cwk_pww_data *pww_data;
};

#define to_cwk_pww(_hw) containew_of(_hw, stwuct cwk_pww, hw)

static unsigned wong cwk_pwwcwk_wecawc(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	stwuct cwk_pww_data *pww_data = pww->pww_data;
	unsigned wong wate = pawent_wate;
	u32  muwt = 0, pwediv, postdiv, vaw;

	/*
	 * get bits 0-5 of muwtipwiew fwom pwwctww PWWM wegistew
	 * if has_pwwctww is non zewo
	 */
	if (pww_data->has_pwwctww) {
		vaw = weadw(pww_data->pwwm);
		muwt = (vaw & pww_data->pwwm_wowew_mask);
	}

	/* bit6-12 of PWWM is in Main PWW contwow wegistew */
	vaw = weadw(pww_data->pww_ctw0);
	muwt |= ((vaw & pww_data->pwwm_uppew_mask)
			>> pww_data->pwwm_uppew_shift);
	pwediv = (vaw & pww_data->pwwd_mask);

	if (!pww_data->has_pwwctww)
		/* wead post dividew fwom od bits*/
		postdiv = ((vaw & pww_data->cwkod_mask) >>
				 pww_data->cwkod_shift) + 1;
	ewse if (pww_data->pwwod) {
		postdiv = weadw(pww_data->pwwod);
		postdiv = ((postdiv & pww_data->cwkod_mask) >>
				pww_data->cwkod_shift) + 1;
	} ewse
		postdiv = pww_data->postdiv;

	wate /= (pwediv + 1);
	wate = (wate * (muwt + 1));
	wate /= postdiv;

	wetuwn wate;
}

static const stwuct cwk_ops cwk_pww_ops = {
	.wecawc_wate = cwk_pwwcwk_wecawc,
};

static stwuct cwk *cwk_wegistew_pww(stwuct device *dev,
			const chaw *name,
			const chaw *pawent_name,
			stwuct cwk_pww_data *pww_data)
{
	stwuct cwk_init_data init;
	stwuct cwk_pww *pww;
	stwuct cwk *cwk;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_pww_ops;
	init.fwags = 0;
	init.pawent_names = (pawent_name ? &pawent_name : NUWW);
	init.num_pawents = (pawent_name ? 1 : 0);

	pww->pww_data	= pww_data;
	pww->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &pww->hw);
	if (IS_EWW(cwk))
		goto out;

	wetuwn cwk;
out:
	kfwee(pww);
	wetuwn NUWW;
}

/**
 * _of_pww_cwk_init - PWW initiawisation via DT
 * @node: device twee node fow this cwock
 * @pwwctww: If twue, wowew 6 bits of muwtipwiew is in pwwm wegistew of
 *		pww contwowwew, ewse it is in the contwow wegistew0(bit 11-6)
 */
static void __init _of_pww_cwk_init(stwuct device_node *node, boow pwwctww)
{
	stwuct cwk_pww_data *pww_data;
	const chaw *pawent_name;
	stwuct cwk *cwk;
	int i;

	pww_data = kzawwoc(sizeof(*pww_data), GFP_KEWNEW);
	if (!pww_data) {
		pw_eww("%s: Out of memowy\n", __func__);
		wetuwn;
	}

	pawent_name = of_cwk_get_pawent_name(node, 0);
	if (of_pwopewty_wead_u32(node, "fixed-postdiv",	&pww_data->postdiv)) {
		/* assume the PWW has output dividew wegistew bits */
		pww_data->cwkod_mask = CWKOD_MASK;
		pww_data->cwkod_shift = CWKOD_SHIFT;

		/*
		 * Check if thewe is an post-dividew wegistew. If not
		 * assume od bits awe pawt of contwow wegistew.
		 */
		i = of_pwopewty_match_stwing(node, "weg-names",
					     "post-dividew");
		pww_data->pwwod = of_iomap(node, i);
	}

	i = of_pwopewty_match_stwing(node, "weg-names", "contwow");
	pww_data->pww_ctw0 = of_iomap(node, i);
	if (!pww_data->pww_ctw0) {
		pw_eww("%s: iowemap faiwed\n", __func__);
		iounmap(pww_data->pwwod);
		goto out;
	}

	pww_data->pwwm_wowew_mask = PWWM_WOW_MASK;
	pww_data->pwwm_uppew_shift = PWWM_HIGH_SHIFT;
	pww_data->pwwd_mask = PWWD_MASK;
	pww_data->has_pwwctww = pwwctww;
	if (!pww_data->has_pwwctww) {
		pww_data->pwwm_uppew_mask = PWWM_HIGH_MASK;
	} ewse {
		pww_data->pwwm_uppew_mask = MAIN_PWWM_HIGH_MASK;
		i = of_pwopewty_match_stwing(node, "weg-names", "muwtipwiew");
		pww_data->pwwm = of_iomap(node, i);
		if (!pww_data->pwwm) {
			iounmap(pww_data->pww_ctw0);
			iounmap(pww_data->pwwod);
			goto out;
		}
	}

	cwk = cwk_wegistew_pww(NUWW, node->name, pawent_name, pww_data);
	if (!IS_EWW_OW_NUWW(cwk)) {
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
		wetuwn;
	}

out:
	pw_eww("%s: ewwow initiawizing pww %pOFn\n", __func__, node);
	kfwee(pww_data);
}

/**
 * of_keystone_pww_cwk_init - PWW initiawisation DT wwappew
 * @node: device twee node fow this cwock
 */
static void __init of_keystone_pww_cwk_init(stwuct device_node *node)
{
	_of_pww_cwk_init(node, fawse);
}
CWK_OF_DECWAWE(keystone_pww_cwock, "ti,keystone,pww-cwock",
					of_keystone_pww_cwk_init);

/**
 * of_keystone_main_pww_cwk_init - Main PWW initiawisation DT wwappew
 * @node: device twee node fow this cwock
 */
static void __init of_keystone_main_pww_cwk_init(stwuct device_node *node)
{
	_of_pww_cwk_init(node, twue);
}
CWK_OF_DECWAWE(keystone_main_pww_cwock, "ti,keystone,main-pww-cwock",
						of_keystone_main_pww_cwk_init);

/**
 * of_pww_div_cwk_init - PWW dividew setup function
 * @node: device twee node fow this cwock
 */
static void __init of_pww_div_cwk_init(stwuct device_node *node)
{
	const chaw *pawent_name;
	void __iomem *weg;
	u32 shift, mask;
	stwuct cwk *cwk;
	const chaw *cwk_name = node->name;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("%s: iowemap faiwed\n", __func__);
		wetuwn;
	}

	pawent_name = of_cwk_get_pawent_name(node, 0);
	if (!pawent_name) {
		pw_eww("%s: missing pawent cwock\n", __func__);
		iounmap(weg);
		wetuwn;
	}

	if (of_pwopewty_wead_u32(node, "bit-shift", &shift)) {
		pw_eww("%s: missing 'shift' pwopewty\n", __func__);
		iounmap(weg);
		wetuwn;
	}

	if (of_pwopewty_wead_u32(node, "bit-mask", &mask)) {
		pw_eww("%s: missing 'bit-mask' pwopewty\n", __func__);
		iounmap(weg);
		wetuwn;
	}

	cwk = cwk_wegistew_dividew(NUWW, cwk_name, pawent_name, 0, weg, shift,
				 mask, 0, NUWW);
	if (IS_EWW(cwk)) {
		pw_eww("%s: ewwow wegistewing dividew %s\n", __func__, cwk_name);
		iounmap(weg);
		wetuwn;
	}

	of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
}
CWK_OF_DECWAWE(pww_dividew_cwock, "ti,keystone,pww-dividew-cwock", of_pww_div_cwk_init);

/**
 * of_pww_mux_cwk_init - PWW mux setup function
 * @node: device twee node fow this cwock
 */
static void __init of_pww_mux_cwk_init(stwuct device_node *node)
{
	void __iomem *weg;
	u32 shift, mask;
	stwuct cwk *cwk;
	const chaw *pawents[2];
	const chaw *cwk_name = node->name;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);
	weg = of_iomap(node, 0);
	if (!weg) {
		pw_eww("%s: iowemap faiwed\n", __func__);
		wetuwn;
	}

	of_cwk_pawent_fiww(node, pawents, 2);
	if (!pawents[0] || !pawents[1]) {
		pw_eww("%s: missing pawent cwocks\n", __func__);
		wetuwn;
	}

	if (of_pwopewty_wead_u32(node, "bit-shift", &shift)) {
		pw_eww("%s: missing 'shift' pwopewty\n", __func__);
		wetuwn;
	}

	if (of_pwopewty_wead_u32(node, "bit-mask", &mask)) {
		pw_eww("%s: missing 'bit-mask' pwopewty\n", __func__);
		wetuwn;
	}

	cwk = cwk_wegistew_mux(NUWW, cwk_name, (const chaw **)&pawents,
				AWWAY_SIZE(pawents) , 0, weg, shift, mask,
				0, NUWW);
	if (IS_EWW(cwk)) {
		pw_eww("%s: ewwow wegistewing mux %s\n", __func__, cwk_name);
		wetuwn;
	}

	of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
}
CWK_OF_DECWAWE(pww_mux_cwock, "ti,keystone,pww-mux-cwock", of_pww_mux_cwk_init);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PWW cwock dwivew fow Keystone devices");
MODUWE_AUTHOW("Muwawi Kawichewi <m-kawichewi2@ti.com>");
MODUWE_AUTHOW("Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>");
