// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010-2011 Canonicaw Wtd <jewemy.keww@canonicaw.com>
 * Copywight (C) 2011-2012 Mike Tuwquette, Winawo Wtd <mtuwquette@winawo.owg>
 *
 * Fixed wate cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/*
 * DOC: basic fixed-wate cwock that cannot gate
 *
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes pawents awe enabwed
 * wate - wate is awways a fixed vawue.  No cwk_set_wate suppowt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

#define to_cwk_fixed_wate(_hw) containew_of(_hw, stwuct cwk_fixed_wate, hw)

static unsigned wong cwk_fixed_wate_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	wetuwn to_cwk_fixed_wate(hw)->fixed_wate;
}

static unsigned wong cwk_fixed_wate_wecawc_accuwacy(stwuct cwk_hw *hw,
		unsigned wong pawent_accuwacy)
{
	stwuct cwk_fixed_wate *fixed = to_cwk_fixed_wate(hw);

	if (fixed->fwags & CWK_FIXED_WATE_PAWENT_ACCUWACY)
		wetuwn pawent_accuwacy;

	wetuwn fixed->fixed_accuwacy;
}

const stwuct cwk_ops cwk_fixed_wate_ops = {
	.wecawc_wate = cwk_fixed_wate_wecawc_wate,
	.wecawc_accuwacy = cwk_fixed_wate_wecawc_accuwacy,
};
EXPOWT_SYMBOW_GPW(cwk_fixed_wate_ops);

static void devm_cwk_hw_wegistew_fixed_wate_wewease(stwuct device *dev, void *wes)
{
	stwuct cwk_fixed_wate *fix = wes;

	/*
	 * We can not use cwk_hw_unwegistew_fixed_wate, since it wiww kfwee()
	 * the hw, wesuwting in doubwe fwee. Just unwegistew the hw and wet
	 * devwes code kfwee() it.
	 */
	cwk_hw_unwegistew(&fix->hw);
}

stwuct cwk_hw *__cwk_hw_wegistew_fixed_wate(stwuct device *dev,
		stwuct device_node *np, const chaw *name,
		const chaw *pawent_name, const stwuct cwk_hw *pawent_hw,
		const stwuct cwk_pawent_data *pawent_data, unsigned wong fwags,
		unsigned wong fixed_wate, unsigned wong fixed_accuwacy,
		unsigned wong cwk_fixed_fwags, boow devm)
{
	stwuct cwk_fixed_wate *fixed;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int wet = -EINVAW;

	/* awwocate fixed-wate cwock */
	if (devm)
		fixed = devwes_awwoc(devm_cwk_hw_wegistew_fixed_wate_wewease,
				     sizeof(*fixed), GFP_KEWNEW);
	ewse
		fixed = kzawwoc(sizeof(*fixed), GFP_KEWNEW);
	if (!fixed)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &cwk_fixed_wate_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.pawent_hws = pawent_hw ? &pawent_hw : NUWW;
	init.pawent_data = pawent_data;
	if (pawent_name || pawent_hw || pawent_data)
		init.num_pawents = 1;
	ewse
		init.num_pawents = 0;

	/* stwuct cwk_fixed_wate assignments */
	fixed->fwags = cwk_fixed_fwags;
	fixed->fixed_wate = fixed_wate;
	fixed->fixed_accuwacy = fixed_accuwacy;
	fixed->hw.init = &init;

	/* wegistew the cwock */
	hw = &fixed->hw;
	if (dev || !np)
		wet = cwk_hw_wegistew(dev, hw);
	ewse
		wet = of_cwk_hw_wegistew(np, hw);
	if (wet) {
		if (devm)
			devwes_fwee(fixed);
		ewse
			kfwee(fixed);
		hw = EWW_PTW(wet);
	} ewse if (devm)
		devwes_add(dev, fixed);

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(__cwk_hw_wegistew_fixed_wate);

stwuct cwk *cwk_wegistew_fixed_wate(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		unsigned wong fixed_wate)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_fixed_wate_with_accuwacy(dev, name, pawent_name,
						      fwags, fixed_wate, 0);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_fixed_wate);

void cwk_unwegistew_fixed_wate(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	cwk_unwegistew(cwk);
	kfwee(to_cwk_fixed_wate(hw));
}
EXPOWT_SYMBOW_GPW(cwk_unwegistew_fixed_wate);

void cwk_hw_unwegistew_fixed_wate(stwuct cwk_hw *hw)
{
	stwuct cwk_fixed_wate *fixed;

	fixed = to_cwk_fixed_wate(hw);

	cwk_hw_unwegistew(hw);
	kfwee(fixed);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_fixed_wate);

#ifdef CONFIG_OF
static stwuct cwk_hw *_of_fixed_cwk_setup(stwuct device_node *node)
{
	stwuct cwk_hw *hw;
	const chaw *cwk_name = node->name;
	u32 wate;
	u32 accuwacy = 0;
	int wet;

	if (of_pwopewty_wead_u32(node, "cwock-fwequency", &wate))
		wetuwn EWW_PTW(-EIO);

	of_pwopewty_wead_u32(node, "cwock-accuwacy", &accuwacy);

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	hw = cwk_hw_wegistew_fixed_wate_with_accuwacy(NUWW, cwk_name, NUWW,
						    0, wate, accuwacy);
	if (IS_EWW(hw))
		wetuwn hw;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
	if (wet) {
		cwk_hw_unwegistew_fixed_wate(hw);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}

/**
 * of_fixed_cwk_setup() - Setup function fow simpwe fixed wate cwock
 * @node:	device node fow the cwock
 */
void __init of_fixed_cwk_setup(stwuct device_node *node)
{
	_of_fixed_cwk_setup(node);
}
CWK_OF_DECWAWE(fixed_cwk, "fixed-cwock", of_fixed_cwk_setup);

static void of_fixed_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *hw = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);
	cwk_hw_unwegistew_fixed_wate(hw);
}

static int of_fixed_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *hw;

	/*
	 * This function is not executed when of_fixed_cwk_setup
	 * succeeded.
	 */
	hw = _of_fixed_cwk_setup(pdev->dev.of_node);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	pwatfowm_set_dwvdata(pdev, hw);

	wetuwn 0;
}

static const stwuct of_device_id of_fixed_cwk_ids[] = {
	{ .compatibwe = "fixed-cwock" },
	{ }
};

static stwuct pwatfowm_dwivew of_fixed_cwk_dwivew = {
	.dwivew = {
		.name = "of_fixed_cwk",
		.of_match_tabwe = of_fixed_cwk_ids,
	},
	.pwobe = of_fixed_cwk_pwobe,
	.wemove_new = of_fixed_cwk_wemove,
};
buiwtin_pwatfowm_dwivew(of_fixed_cwk_dwivew);
#endif
