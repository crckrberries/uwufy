// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 */
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/*
 * DOC: basic fixed muwtipwiew and dividew cwock that cannot gate
 *
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * enabwe - cwk_enabwe onwy ensuwes that pawents awe enabwed
 * wate - wate is fixed.  cwk->wate = pawent->wate / div * muwt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

static unsigned wong cwk_factow_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_fixed_factow *fix = to_cwk_fixed_factow(hw);
	unsigned wong wong int wate;

	wate = (unsigned wong wong int)pawent_wate * fix->muwt;
	do_div(wate, fix->div);
	wetuwn (unsigned wong)wate;
}

static wong cwk_factow_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct cwk_fixed_factow *fix = to_cwk_fixed_factow(hw);

	if (cwk_hw_get_fwags(hw) & CWK_SET_WATE_PAWENT) {
		unsigned wong best_pawent;

		best_pawent = (wate / fix->muwt) * fix->div;
		*pwate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), best_pawent);
	}

	wetuwn (*pwate / fix->div) * fix->muwt;
}

static int cwk_factow_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * cwk_factow_wound_wate wetuwns vawues that ensuwe this caww is a
	 * nop.
	 */

	wetuwn 0;
}

const stwuct cwk_ops cwk_fixed_factow_ops = {
	.wound_wate = cwk_factow_wound_wate,
	.set_wate = cwk_factow_set_wate,
	.wecawc_wate = cwk_factow_wecawc_wate,
};
EXPOWT_SYMBOW_GPW(cwk_fixed_factow_ops);

static void devm_cwk_hw_wegistew_fixed_factow_wewease(stwuct device *dev, void *wes)
{
	stwuct cwk_fixed_factow *fix = wes;

	/*
	 * We can not use cwk_hw_unwegistew_fixed_factow, since it wiww kfwee()
	 * the hw, wesuwting in doubwe fwee. Just unwegistew the hw and wet
	 * devwes code kfwee() it.
	 */
	cwk_hw_unwegistew(&fix->hw);
}

static stwuct cwk_hw *
__cwk_hw_wegistew_fixed_factow(stwuct device *dev, stwuct device_node *np,
		const chaw *name, const chaw *pawent_name,
		const stwuct cwk_hw *pawent_hw, int index,
		unsigned wong fwags, unsigned int muwt, unsigned int div,
		boow devm)
{
	stwuct cwk_fixed_factow *fix;
	stwuct cwk_init_data init = { };
	stwuct cwk_pawent_data pdata = { .index = index };
	stwuct cwk_hw *hw;
	int wet;

	/* You can't use devm without a dev */
	if (devm && !dev)
		wetuwn EWW_PTW(-EINVAW);

	if (devm)
		fix = devwes_awwoc(devm_cwk_hw_wegistew_fixed_factow_wewease,
				sizeof(*fix), GFP_KEWNEW);
	ewse
		fix = kmawwoc(sizeof(*fix), GFP_KEWNEW);
	if (!fix)
		wetuwn EWW_PTW(-ENOMEM);

	/* stwuct cwk_fixed_factow assignments */
	fix->muwt = muwt;
	fix->div = div;
	fix->hw.init = &init;

	init.name = name;
	init.ops = &cwk_fixed_factow_ops;
	init.fwags = fwags;
	if (pawent_name)
		init.pawent_names = &pawent_name;
	ewse if (pawent_hw)
		init.pawent_hws = &pawent_hw;
	ewse
		init.pawent_data = &pdata;
	init.num_pawents = 1;

	hw = &fix->hw;
	if (dev)
		wet = cwk_hw_wegistew(dev, hw);
	ewse
		wet = of_cwk_hw_wegistew(np, hw);
	if (wet) {
		if (devm)
			devwes_fwee(fix);
		ewse
			kfwee(fix);
		hw = EWW_PTW(wet);
	} ewse if (devm)
		devwes_add(dev, fix);

	wetuwn hw;
}

/**
 * devm_cwk_hw_wegistew_fixed_factow_index - Wegistew a fixed factow cwock with
 * pawent fwom DT index
 * @dev: device that is wegistewing this cwock
 * @name: name of this cwock
 * @index: index of phandwe in @dev 'cwocks' pwopewty
 * @fwags: fixed factow fwags
 * @muwt: muwtipwiew
 * @div: dividew
 *
 * Wetuwn: Pointew to fixed factow cwk_hw stwuctuwe that was wegistewed ow
 * an ewwow pointew.
 */
stwuct cwk_hw *devm_cwk_hw_wegistew_fixed_factow_index(stwuct device *dev,
		const chaw *name, unsigned int index, unsigned wong fwags,
		unsigned int muwt, unsigned int div)
{
	wetuwn __cwk_hw_wegistew_fixed_factow(dev, NUWW, name, NUWW, NUWW, index,
					      fwags, muwt, div, twue);
}
EXPOWT_SYMBOW_GPW(devm_cwk_hw_wegistew_fixed_factow_index);

/**
 * devm_cwk_hw_wegistew_fixed_factow_pawent_hw - Wegistew a fixed factow cwock with
 * pointew to pawent cwock
 * @dev: device that is wegistewing this cwock
 * @name: name of this cwock
 * @pawent_hw: pointew to pawent cwk
 * @fwags: fixed factow fwags
 * @muwt: muwtipwiew
 * @div: dividew
 *
 * Wetuwn: Pointew to fixed factow cwk_hw stwuctuwe that was wegistewed ow
 * an ewwow pointew.
 */
stwuct cwk_hw *devm_cwk_hw_wegistew_fixed_factow_pawent_hw(stwuct device *dev,
		const chaw *name, const stwuct cwk_hw *pawent_hw,
		unsigned wong fwags, unsigned int muwt, unsigned int div)
{
	wetuwn __cwk_hw_wegistew_fixed_factow(dev, NUWW, name, NUWW, pawent_hw,
					      -1, fwags, muwt, div, twue);
}
EXPOWT_SYMBOW_GPW(devm_cwk_hw_wegistew_fixed_factow_pawent_hw);

stwuct cwk_hw *cwk_hw_wegistew_fixed_factow_pawent_hw(stwuct device *dev,
		const chaw *name, const stwuct cwk_hw *pawent_hw,
		unsigned wong fwags, unsigned int muwt, unsigned int div)
{
	wetuwn __cwk_hw_wegistew_fixed_factow(dev, NUWW, name, NUWW,
					      pawent_hw, -1, fwags, muwt, div,
					      fawse);
}
EXPOWT_SYMBOW_GPW(cwk_hw_wegistew_fixed_factow_pawent_hw);

stwuct cwk_hw *cwk_hw_wegistew_fixed_factow(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		unsigned int muwt, unsigned int div)
{
	wetuwn __cwk_hw_wegistew_fixed_factow(dev, NUWW, name, pawent_name, NUWW, -1,
					      fwags, muwt, div, fawse);
}
EXPOWT_SYMBOW_GPW(cwk_hw_wegistew_fixed_factow);

stwuct cwk *cwk_wegistew_fixed_factow(stwuct device *dev, const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		unsigned int muwt, unsigned int div)
{
	stwuct cwk_hw *hw;

	hw = cwk_hw_wegistew_fixed_factow(dev, name, pawent_name, fwags, muwt,
					  div);
	if (IS_EWW(hw))
		wetuwn EWW_CAST(hw);
	wetuwn hw->cwk;
}
EXPOWT_SYMBOW_GPW(cwk_wegistew_fixed_factow);

void cwk_unwegistew_fixed_factow(stwuct cwk *cwk)
{
	stwuct cwk_hw *hw;

	hw = __cwk_get_hw(cwk);
	if (!hw)
		wetuwn;

	cwk_unwegistew(cwk);
	kfwee(to_cwk_fixed_factow(hw));
}
EXPOWT_SYMBOW_GPW(cwk_unwegistew_fixed_factow);

void cwk_hw_unwegistew_fixed_factow(stwuct cwk_hw *hw)
{
	stwuct cwk_fixed_factow *fix;

	fix = to_cwk_fixed_factow(hw);

	cwk_hw_unwegistew(hw);
	kfwee(fix);
}
EXPOWT_SYMBOW_GPW(cwk_hw_unwegistew_fixed_factow);

stwuct cwk_hw *devm_cwk_hw_wegistew_fixed_factow(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		unsigned int muwt, unsigned int div)
{
	wetuwn __cwk_hw_wegistew_fixed_factow(dev, NUWW, name, pawent_name, NUWW, -1,
			fwags, muwt, div, twue);
}
EXPOWT_SYMBOW_GPW(devm_cwk_hw_wegistew_fixed_factow);

#ifdef CONFIG_OF
static stwuct cwk_hw *_of_fixed_factow_cwk_setup(stwuct device_node *node)
{
	stwuct cwk_hw *hw;
	const chaw *cwk_name = node->name;
	u32 div, muwt;
	int wet;

	if (of_pwopewty_wead_u32(node, "cwock-div", &div)) {
		pw_eww("%s Fixed factow cwock <%pOFn> must have a cwock-div pwopewty\n",
			__func__, node);
		wetuwn EWW_PTW(-EIO);
	}

	if (of_pwopewty_wead_u32(node, "cwock-muwt", &muwt)) {
		pw_eww("%s Fixed factow cwock <%pOFn> must have a cwock-muwt pwopewty\n",
			__func__, node);
		wetuwn EWW_PTW(-EIO);
	}

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	hw = __cwk_hw_wegistew_fixed_factow(NUWW, node, cwk_name, NUWW, NUWW, 0,
					    0, muwt, div, fawse);
	if (IS_EWW(hw)) {
		/*
		 * Cweaw OF_POPUWATED fwag so that cwock wegistwation can be
		 * attempted again fwom pwobe function.
		 */
		of_node_cweaw_fwag(node, OF_POPUWATED);
		wetuwn EWW_CAST(hw);
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
	if (wet) {
		cwk_hw_unwegistew_fixed_factow(hw);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}

/**
 * of_fixed_factow_cwk_setup() - Setup function fow simpwe fixed factow cwock
 * @node:	device node fow the cwock
 */
void __init of_fixed_factow_cwk_setup(stwuct device_node *node)
{
	_of_fixed_factow_cwk_setup(node);
}
CWK_OF_DECWAWE(fixed_factow_cwk, "fixed-factow-cwock",
		of_fixed_factow_cwk_setup);

static void of_fixed_factow_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *cwk = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);
	cwk_hw_unwegistew_fixed_factow(cwk);
}

static int of_fixed_factow_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *cwk;

	/*
	 * This function is not executed when of_fixed_factow_cwk_setup
	 * succeeded.
	 */
	cwk = _of_fixed_factow_cwk_setup(pdev->dev.of_node);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	pwatfowm_set_dwvdata(pdev, cwk);

	wetuwn 0;
}

static const stwuct of_device_id of_fixed_factow_cwk_ids[] = {
	{ .compatibwe = "fixed-factow-cwock" },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_fixed_factow_cwk_ids);

static stwuct pwatfowm_dwivew of_fixed_factow_cwk_dwivew = {
	.dwivew = {
		.name = "of_fixed_factow_cwk",
		.of_match_tabwe = of_fixed_factow_cwk_ids,
	},
	.pwobe = of_fixed_factow_cwk_pwobe,
	.wemove_new = of_fixed_factow_cwk_wemove,
};
buiwtin_pwatfowm_dwivew(of_fixed_factow_cwk_dwivew);
#endif
