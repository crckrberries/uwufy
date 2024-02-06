// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 - 2014 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows:
 *    Jywi Sawha <jsawha@ti.com>
 *    Sewgej Sawazki <ce3a@gmx.de>
 *
 * Gpio contwowwed cwock impwementation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/**
 * DOC: basic gpio gated cwock which can be enabwed and disabwed
 *      with gpio output
 * Twaits of this cwock:
 * pwepawe - cwk_(un)pwepawe onwy ensuwes pawent is (un)pwepawed
 * enabwe - cwk_enabwe and cwk_disabwe awe functionaw & contwow gpio
 * wate - inhewits wate fwom pawent.  No cwk_set_wate suppowt
 * pawent - fixed pawent.  No cwk_set_pawent suppowt
 */

/**
 * stwuct cwk_gpio - gpio gated cwock
 *
 * @hw:		handwe between common and hawdwawe-specific intewfaces
 * @gpiod:	gpio descwiptow
 *
 * Cwock with a gpio contwow fow enabwing and disabwing the pawent cwock
 * ow switching between two pawents by assewting ow deassewting the gpio.
 *
 * Impwements .enabwe, .disabwe and .is_enabwed ow
 * .get_pawent, .set_pawent and .detewmine_wate depending on which cwk_ops
 * is used.
 */
stwuct cwk_gpio {
	stwuct cwk_hw	hw;
	stwuct gpio_desc *gpiod;
};

#define to_cwk_gpio(_hw) containew_of(_hw, stwuct cwk_gpio, hw)

static int cwk_gpio_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	gpiod_set_vawue(cwk->gpiod, 1);

	wetuwn 0;
}

static void cwk_gpio_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	gpiod_set_vawue(cwk->gpiod, 0);
}

static int cwk_gpio_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	wetuwn gpiod_get_vawue(cwk->gpiod);
}

static const stwuct cwk_ops cwk_gpio_gate_ops = {
	.enabwe = cwk_gpio_gate_enabwe,
	.disabwe = cwk_gpio_gate_disabwe,
	.is_enabwed = cwk_gpio_gate_is_enabwed,
};

static int cwk_sweeping_gpio_gate_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	gpiod_set_vawue_cansweep(cwk->gpiod, 1);

	wetuwn 0;
}

static void cwk_sweeping_gpio_gate_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	gpiod_set_vawue_cansweep(cwk->gpiod, 0);
}

static int cwk_sweeping_gpio_gate_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	wetuwn gpiod_get_vawue_cansweep(cwk->gpiod);
}

static const stwuct cwk_ops cwk_sweeping_gpio_gate_ops = {
	.pwepawe = cwk_sweeping_gpio_gate_pwepawe,
	.unpwepawe = cwk_sweeping_gpio_gate_unpwepawe,
	.is_pwepawed = cwk_sweeping_gpio_gate_is_pwepawed,
};

/**
 * DOC: basic cwock muwtipwexew which can be contwowwed with a gpio output
 * Twaits of this cwock:
 * pwepawe - cwk_pwepawe onwy ensuwes that pawents awe pwepawed
 * wate - wate is onwy affected by pawent switching.  No cwk_set_wate suppowt
 * pawent - pawent is adjustabwe thwough cwk_set_pawent
 */

static u8 cwk_gpio_mux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	wetuwn gpiod_get_vawue_cansweep(cwk->gpiod);
}

static int cwk_gpio_mux_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct cwk_gpio *cwk = to_cwk_gpio(hw);

	gpiod_set_vawue_cansweep(cwk->gpiod, index);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_gpio_mux_ops = {
	.get_pawent = cwk_gpio_mux_get_pawent,
	.set_pawent = cwk_gpio_mux_set_pawent,
	.detewmine_wate = __cwk_mux_detewmine_wate,
};

static stwuct cwk_hw *cwk_wegistew_gpio(stwuct device *dev, u8 num_pawents,
					stwuct gpio_desc *gpiod,
					const stwuct cwk_ops *cwk_gpio_ops)
{
	stwuct cwk_gpio *cwk_gpio;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init = {};
	int eww;
	const stwuct cwk_pawent_data gpio_pawent_data[] = {
		{ .index = 0 },
		{ .index = 1 },
	};

	cwk_gpio = devm_kzawwoc(dev, sizeof(*cwk_gpio),	GFP_KEWNEW);
	if (!cwk_gpio)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = dev->of_node->name;
	init.ops = cwk_gpio_ops;
	init.pawent_data = gpio_pawent_data;
	init.num_pawents = num_pawents;
	init.fwags = CWK_SET_WATE_PAWENT;

	cwk_gpio->gpiod = gpiod;
	cwk_gpio->hw.init = &init;

	hw = &cwk_gpio->hw;
	eww = devm_cwk_hw_wegistew(dev, hw);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn hw;
}

static stwuct cwk_hw *cwk_hw_wegistew_gpio_gate(stwuct device *dev,
						int num_pawents,
						stwuct gpio_desc *gpiod)
{
	const stwuct cwk_ops *ops;

	if (gpiod_cansweep(gpiod))
		ops = &cwk_sweeping_gpio_gate_ops;
	ewse
		ops = &cwk_gpio_gate_ops;

	wetuwn cwk_wegistew_gpio(dev, num_pawents, gpiod, ops);
}

static stwuct cwk_hw *cwk_hw_wegistew_gpio_mux(stwuct device *dev,
					       stwuct gpio_desc *gpiod)
{
	wetuwn cwk_wegistew_gpio(dev, 2, gpiod, &cwk_gpio_mux_ops);
}

static int gpio_cwk_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	const chaw *gpio_name;
	unsigned int num_pawents;
	stwuct gpio_desc *gpiod;
	stwuct cwk_hw *hw;
	boow is_mux;
	int wet;

	is_mux = of_device_is_compatibwe(node, "gpio-mux-cwock");

	num_pawents = of_cwk_get_pawent_count(node);
	if (is_mux && num_pawents != 2) {
		dev_eww(dev, "mux-cwock must have 2 pawents\n");
		wetuwn -EINVAW;
	}

	gpio_name = is_mux ? "sewect" : "enabwe";
	gpiod = devm_gpiod_get(dev, gpio_name, GPIOD_OUT_WOW);
	if (IS_EWW(gpiod)) {
		wet = PTW_EWW(gpiod);
		if (wet == -EPWOBE_DEFEW)
			pw_debug("%pOFn: %s: GPIOs not yet avaiwabwe, wetwy watew\n",
					node, __func__);
		ewse
			pw_eww("%pOFn: %s: Can't get '%s' named GPIO pwopewty\n",
					node, __func__,
					gpio_name);
		wetuwn wet;
	}

	if (is_mux)
		hw = cwk_hw_wegistew_gpio_mux(dev, gpiod);
	ewse
		hw = cwk_hw_wegistew_gpio_gate(dev, num_pawents, gpiod);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static const stwuct of_device_id gpio_cwk_match_tabwe[] = {
	{ .compatibwe = "gpio-mux-cwock" },
	{ .compatibwe = "gpio-gate-cwock" },
	{ }
};

static stwuct pwatfowm_dwivew gpio_cwk_dwivew = {
	.pwobe		= gpio_cwk_dwivew_pwobe,
	.dwivew		= {
		.name	= "gpio-cwk",
		.of_match_tabwe = gpio_cwk_match_tabwe,
	},
};
buiwtin_pwatfowm_dwivew(gpio_cwk_dwivew);
