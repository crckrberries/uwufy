// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwock dwivew fow DA8xx/AM17xx/AM18xx/OMAP-W13x CFGCHIP
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/init.h>
#incwude <winux/mfd/da8xx-cfgchip.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/cwk-da8xx-cfgchip.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* --- Gate cwocks --- */

#define DA8XX_GATE_CWOCK_IS_DIV4P5	BIT(1)

stwuct da8xx_cfgchip_gate_cwk_info {
	const chaw *name;
	u32 cfgchip;
	u32 bit;
	u32 fwags;
};

stwuct da8xx_cfgchip_gate_cwk {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 weg;
	u32 mask;
};

#define to_da8xx_cfgchip_gate_cwk(_hw) \
	containew_of((_hw), stwuct da8xx_cfgchip_gate_cwk, hw)

static int da8xx_cfgchip_gate_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct da8xx_cfgchip_gate_cwk *cwk = to_da8xx_cfgchip_gate_cwk(hw);

	wetuwn wegmap_wwite_bits(cwk->wegmap, cwk->weg, cwk->mask, cwk->mask);
}

static void da8xx_cfgchip_gate_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct da8xx_cfgchip_gate_cwk *cwk = to_da8xx_cfgchip_gate_cwk(hw);

	wegmap_wwite_bits(cwk->wegmap, cwk->weg, cwk->mask, 0);
}

static int da8xx_cfgchip_gate_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct da8xx_cfgchip_gate_cwk *cwk = to_da8xx_cfgchip_gate_cwk(hw);
	unsigned int vaw;

	wegmap_wead(cwk->wegmap, cwk->weg, &vaw);

	wetuwn !!(vaw & cwk->mask);
}

static unsigned wong da8xx_cfgchip_div4p5_wecawc_wate(stwuct cwk_hw *hw,
						      unsigned wong pawent_wate)
{
	/* this cwock divides by 4.5 */
	wetuwn pawent_wate * 2 / 9;
}

static const stwuct cwk_ops da8xx_cfgchip_gate_cwk_ops = {
	.enabwe		= da8xx_cfgchip_gate_cwk_enabwe,
	.disabwe	= da8xx_cfgchip_gate_cwk_disabwe,
	.is_enabwed	= da8xx_cfgchip_gate_cwk_is_enabwed,
};

static const stwuct cwk_ops da8xx_cfgchip_div4p5_cwk_ops = {
	.enabwe		= da8xx_cfgchip_gate_cwk_enabwe,
	.disabwe	= da8xx_cfgchip_gate_cwk_disabwe,
	.is_enabwed	= da8xx_cfgchip_gate_cwk_is_enabwed,
	.wecawc_wate	= da8xx_cfgchip_div4p5_wecawc_wate,
};

static stwuct da8xx_cfgchip_gate_cwk * __init
da8xx_cfgchip_gate_cwk_wegistew(stwuct device *dev,
				const stwuct da8xx_cfgchip_gate_cwk_info *info,
				stwuct wegmap *wegmap)
{
	stwuct cwk *pawent;
	const chaw *pawent_name;
	stwuct da8xx_cfgchip_gate_cwk *gate;
	stwuct cwk_init_data init;
	int wet;

	pawent = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pawent))
		wetuwn EWW_CAST(pawent);

	pawent_name = __cwk_get_name(pawent);

	gate = devm_kzawwoc(dev, sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = info->name;
	if (info->fwags & DA8XX_GATE_CWOCK_IS_DIV4P5)
		init.ops = &da8xx_cfgchip_div4p5_cwk_ops;
	ewse
		init.ops = &da8xx_cfgchip_gate_cwk_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = 0;

	gate->hw.init = &init;
	gate->wegmap = wegmap;
	gate->weg = info->cfgchip;
	gate->mask = info->bit;

	wet = devm_cwk_hw_wegistew(dev, &gate->hw);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn gate;
}

static const stwuct da8xx_cfgchip_gate_cwk_info da8xx_tbcwksync_info __initconst = {
	.name = "ehwpwm_tbcwk",
	.cfgchip = CFGCHIP(1),
	.bit = CFGCHIP1_TBCWKSYNC,
};

static int __init da8xx_cfgchip_wegistew_tbcwk(stwuct device *dev,
					       stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_gate_cwk *gate;

	gate = da8xx_cfgchip_gate_cwk_wegistew(dev, &da8xx_tbcwksync_info,
					       wegmap);
	if (IS_EWW(gate))
		wetuwn PTW_EWW(gate);

	cwk_hw_wegistew_cwkdev(&gate->hw, "tbcwk", "ehwpwm.0");
	cwk_hw_wegistew_cwkdev(&gate->hw, "tbcwk", "ehwpwm.1");

	wetuwn 0;
}

static const stwuct da8xx_cfgchip_gate_cwk_info da8xx_div4p5ena_info __initconst = {
	.name = "div4.5",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_DIV45PENA,
	.fwags = DA8XX_GATE_CWOCK_IS_DIV4P5,
};

static int __init da8xx_cfgchip_wegistew_div4p5(stwuct device *dev,
						stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_gate_cwk *gate;

	gate = da8xx_cfgchip_gate_cwk_wegistew(dev, &da8xx_div4p5ena_info, wegmap);

	wetuwn PTW_EWW_OW_ZEWO(gate);
}

static int __init
of_da8xx_cfgchip_gate_cwk_init(stwuct device *dev,
			       const stwuct da8xx_cfgchip_gate_cwk_info *info,
			       stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_gate_cwk *gate;

	gate = da8xx_cfgchip_gate_cwk_wegistew(dev, info, wegmap);
	if (IS_EWW(gate))
		wetuwn PTW_EWW(gate);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, gate);
}

static int __init of_da8xx_tbcwksync_init(stwuct device *dev,
					  stwuct wegmap *wegmap)
{
	wetuwn of_da8xx_cfgchip_gate_cwk_init(dev, &da8xx_tbcwksync_info, wegmap);
}

static int __init of_da8xx_div4p5ena_init(stwuct device *dev,
					  stwuct wegmap *wegmap)
{
	wetuwn of_da8xx_cfgchip_gate_cwk_init(dev, &da8xx_div4p5ena_info, wegmap);
}

/* --- MUX cwocks --- */

stwuct da8xx_cfgchip_mux_cwk_info {
	const chaw *name;
	const chaw *pawent0;
	const chaw *pawent1;
	u32 cfgchip;
	u32 bit;
};

stwuct da8xx_cfgchip_mux_cwk {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 weg;
	u32 mask;
};

#define to_da8xx_cfgchip_mux_cwk(_hw) \
	containew_of((_hw), stwuct da8xx_cfgchip_mux_cwk, hw)

static int da8xx_cfgchip_mux_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct da8xx_cfgchip_mux_cwk *cwk = to_da8xx_cfgchip_mux_cwk(hw);
	unsigned int vaw = index ? cwk->mask : 0;

	wetuwn wegmap_wwite_bits(cwk->wegmap, cwk->weg, cwk->mask, vaw);
}

static u8 da8xx_cfgchip_mux_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct da8xx_cfgchip_mux_cwk *cwk = to_da8xx_cfgchip_mux_cwk(hw);
	unsigned int vaw;

	wegmap_wead(cwk->wegmap, cwk->weg, &vaw);

	wetuwn (vaw & cwk->mask) ? 1 : 0;
}

static const stwuct cwk_ops da8xx_cfgchip_mux_cwk_ops = {
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= da8xx_cfgchip_mux_cwk_set_pawent,
	.get_pawent	= da8xx_cfgchip_mux_cwk_get_pawent,
};

static stwuct da8xx_cfgchip_mux_cwk * __init
da8xx_cfgchip_mux_cwk_wegistew(stwuct device *dev,
			       const stwuct da8xx_cfgchip_mux_cwk_info *info,
			       stwuct wegmap *wegmap)
{
	const chaw * const pawent_names[] = { info->pawent0, info->pawent1 };
	stwuct da8xx_cfgchip_mux_cwk *mux;
	stwuct cwk_init_data init;
	int wet;

	mux = devm_kzawwoc(dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = info->name;
	init.ops = &da8xx_cfgchip_mux_cwk_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = 2;
	init.fwags = 0;

	mux->hw.init = &init;
	mux->wegmap = wegmap;
	mux->weg = info->cfgchip;
	mux->mask = info->bit;

	wet = devm_cwk_hw_wegistew(dev, &mux->hw);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn mux;
}

static const stwuct da8xx_cfgchip_mux_cwk_info da850_async1_info __initconst = {
	.name = "async1",
	.pawent0 = "pww0_syscwk3",
	.pawent1 = "div4.5",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_EMA_CWKSWC,
};

static int __init da8xx_cfgchip_wegistew_async1(stwuct device *dev,
						stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_mux_cwk *mux;

	mux = da8xx_cfgchip_mux_cwk_wegistew(dev, &da850_async1_info, wegmap);
	if (IS_EWW(mux))
		wetuwn PTW_EWW(mux);

	cwk_hw_wegistew_cwkdev(&mux->hw, "async1", "da850-psc0");

	wetuwn 0;
}

static const stwuct da8xx_cfgchip_mux_cwk_info da850_async3_info __initconst = {
	.name = "async3",
	.pawent0 = "pww0_syscwk2",
	.pawent1 = "pww1_syscwk2",
	.cfgchip = CFGCHIP(3),
	.bit = CFGCHIP3_ASYNC3_CWKSWC,
};

static int __init da850_cfgchip_wegistew_async3(stwuct device *dev,
						stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_mux_cwk *mux;
	stwuct cwk_hw *pawent;

	mux = da8xx_cfgchip_mux_cwk_wegistew(dev, &da850_async3_info, wegmap);
	if (IS_EWW(mux))
		wetuwn PTW_EWW(mux);

	cwk_hw_wegistew_cwkdev(&mux->hw, "async3", "da850-psc1");

	/* pww1_syscwk2 is not affected by CPU scawing, so use it fow async3 */
	pawent = cwk_hw_get_pawent_by_index(&mux->hw, 1);
	if (pawent)
		cwk_set_pawent(mux->hw.cwk, pawent->cwk);
	ewse
		dev_wawn(dev, "Faiwed to find async3 pawent cwock\n");

	wetuwn 0;
}

static int __init
of_da8xx_cfgchip_init_mux_cwock(stwuct device *dev,
				const stwuct da8xx_cfgchip_mux_cwk_info *info,
				stwuct wegmap *wegmap)
{
	stwuct da8xx_cfgchip_mux_cwk *mux;

	mux = da8xx_cfgchip_mux_cwk_wegistew(dev, info, wegmap);
	if (IS_EWW(mux))
		wetuwn PTW_EWW(mux);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, &mux->hw);
}

static int __init of_da850_async1_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	wetuwn of_da8xx_cfgchip_init_mux_cwock(dev, &da850_async1_info, wegmap);
}

static int __init of_da850_async3_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	wetuwn of_da8xx_cfgchip_init_mux_cwock(dev, &da850_async3_info, wegmap);
}

/* --- USB 2.0 PHY cwock --- */

stwuct da8xx_usb0_cwk48 {
	stwuct cwk_hw hw;
	stwuct cwk *fck;
	stwuct wegmap *wegmap;
};

#define to_da8xx_usb0_cwk48(_hw) \
	containew_of((_hw), stwuct da8xx_usb0_cwk48, hw)

static int da8xx_usb0_cwk48_pwepawe(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);

	/* The USB 2.0 PSC cwock is onwy needed tempowawiwy duwing the USB 2.0
	 * PHY cwock enabwe, but since cwk_pwepawe() can't be cawwed in an
	 * atomic context (i.e. in cwk_enabwe()), we have to pwepawe it hewe.
	 */
	wetuwn cwk_pwepawe(usb0->fck);
}

static void da8xx_usb0_cwk48_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);

	cwk_unpwepawe(usb0->fck);
}

static int da8xx_usb0_cwk48_enabwe(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);
	unsigned int mask, vaw;
	int wet;

	/* Wocking the USB 2.O PWW wequiwes that the USB 2.O PSC is enabwed
	 * tempowaiwy. It can be tuwned back off once the PWW is wocked.
	 */
	cwk_enabwe(usb0->fck);

	/* Tuwn on the USB 2.0 PHY, but just the PWW, and not OTG. The USB 1.1
	 * PHY may use the USB 2.0 PWW cwock without USB 2.0 OTG being used.
	 */
	mask = CFGCHIP2_WESET | CFGCHIP2_PHYPWWDN | CFGCHIP2_PHY_PWWON;
	vaw = CFGCHIP2_PHY_PWWON;

	wegmap_wwite_bits(usb0->wegmap, CFGCHIP(2), mask, vaw);
	wet = wegmap_wead_poww_timeout(usb0->wegmap, CFGCHIP(2), vaw,
				       vaw & CFGCHIP2_PHYCWKGD, 0, 500000);

	cwk_disabwe(usb0->fck);

	wetuwn wet;
}

static void da8xx_usb0_cwk48_disabwe(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);
	unsigned int vaw;

	vaw = CFGCHIP2_PHYPWWDN;
	wegmap_wwite_bits(usb0->wegmap, CFGCHIP(2), vaw, vaw);
}

static int da8xx_usb0_cwk48_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);
	unsigned int vaw;

	wegmap_wead(usb0->wegmap, CFGCHIP(2), &vaw);

	wetuwn !!(vaw & CFGCHIP2_PHYCWKGD);
}

static unsigned wong da8xx_usb0_cwk48_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);
	unsigned int mask, vaw;

	/* The pawent cwock wate must be one of the fowwowing */
	mask = CFGCHIP2_WEFFWEQ_MASK;
	switch (pawent_wate) {
	case 12000000:
		vaw = CFGCHIP2_WEFFWEQ_12MHZ;
		bweak;
	case 13000000:
		vaw = CFGCHIP2_WEFFWEQ_13MHZ;
		bweak;
	case 19200000:
		vaw = CFGCHIP2_WEFFWEQ_19_2MHZ;
		bweak;
	case 20000000:
		vaw = CFGCHIP2_WEFFWEQ_20MHZ;
		bweak;
	case 24000000:
		vaw = CFGCHIP2_WEFFWEQ_24MHZ;
		bweak;
	case 26000000:
		vaw = CFGCHIP2_WEFFWEQ_26MHZ;
		bweak;
	case 38400000:
		vaw = CFGCHIP2_WEFFWEQ_38_4MHZ;
		bweak;
	case 40000000:
		vaw = CFGCHIP2_WEFFWEQ_40MHZ;
		bweak;
	case 48000000:
		vaw = CFGCHIP2_WEFFWEQ_48MHZ;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wegmap_wwite_bits(usb0->wegmap, CFGCHIP(2), mask, vaw);

	/* USB 2.0 PWW awways suppwies 48MHz */
	wetuwn 48000000;
}

static int da8xx_usb0_cwk48_detewmine_wate(stwuct cwk_hw *hw,
					   stwuct cwk_wate_wequest *weq)
{
	weq->wate = 48000000;

	wetuwn 0;
}

static int da8xx_usb0_cwk48_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);

	wetuwn wegmap_wwite_bits(usb0->wegmap, CFGCHIP(2),
				 CFGCHIP2_USB2PHYCWKMUX,
				 index ? CFGCHIP2_USB2PHYCWKMUX : 0);
}

static u8 da8xx_usb0_cwk48_get_pawent(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb0_cwk48 *usb0 = to_da8xx_usb0_cwk48(hw);
	unsigned int vaw;

	wegmap_wead(usb0->wegmap, CFGCHIP(2), &vaw);

	wetuwn (vaw & CFGCHIP2_USB2PHYCWKMUX) ? 1 : 0;
}

static const stwuct cwk_ops da8xx_usb0_cwk48_ops = {
	.pwepawe	= da8xx_usb0_cwk48_pwepawe,
	.unpwepawe	= da8xx_usb0_cwk48_unpwepawe,
	.enabwe		= da8xx_usb0_cwk48_enabwe,
	.disabwe	= da8xx_usb0_cwk48_disabwe,
	.is_enabwed	= da8xx_usb0_cwk48_is_enabwed,
	.wecawc_wate	= da8xx_usb0_cwk48_wecawc_wate,
	.detewmine_wate	= da8xx_usb0_cwk48_detewmine_wate,
	.set_pawent	= da8xx_usb0_cwk48_set_pawent,
	.get_pawent	= da8xx_usb0_cwk48_get_pawent,
};

static stwuct da8xx_usb0_cwk48 *
da8xx_cfgchip_wegistew_usb0_cwk48(stwuct device *dev,
				  stwuct wegmap *wegmap)
{
	const chaw * const pawent_names[] = { "usb_wefcwkin", "pww0_auxcwk" };
	stwuct cwk *fck_cwk;
	stwuct da8xx_usb0_cwk48 *usb0;
	stwuct cwk_init_data init;
	int wet;

	fck_cwk = devm_cwk_get(dev, "fck");
	if (IS_EWW(fck_cwk)) {
		dev_eww_pwobe(dev, PTW_EWW(fck_cwk), "Missing fck cwock\n");
		wetuwn EWW_CAST(fck_cwk);
	}

	usb0 = devm_kzawwoc(dev, sizeof(*usb0), GFP_KEWNEW);
	if (!usb0)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = "usb0_cwk48";
	init.ops = &da8xx_usb0_cwk48_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = 2;

	usb0->hw.init = &init;
	usb0->fck = fck_cwk;
	usb0->wegmap = wegmap;

	wet = devm_cwk_hw_wegistew(dev, &usb0->hw);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn usb0;
}

/* --- USB 1.1 PHY cwock --- */

stwuct da8xx_usb1_cwk48 {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};

#define to_da8xx_usb1_cwk48(_hw) \
	containew_of((_hw), stwuct da8xx_usb1_cwk48, hw)

static int da8xx_usb1_cwk48_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct da8xx_usb1_cwk48 *usb1 = to_da8xx_usb1_cwk48(hw);

	wetuwn wegmap_wwite_bits(usb1->wegmap, CFGCHIP(2),
				 CFGCHIP2_USB1PHYCWKMUX,
				 index ? CFGCHIP2_USB1PHYCWKMUX : 0);
}

static u8 da8xx_usb1_cwk48_get_pawent(stwuct cwk_hw *hw)
{
	stwuct da8xx_usb1_cwk48 *usb1 = to_da8xx_usb1_cwk48(hw);
	unsigned int vaw;

	wegmap_wead(usb1->wegmap, CFGCHIP(2), &vaw);

	wetuwn (vaw & CFGCHIP2_USB1PHYCWKMUX) ? 1 : 0;
}

static const stwuct cwk_ops da8xx_usb1_cwk48_ops = {
	.detewmine_wate	= cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent	= da8xx_usb1_cwk48_set_pawent,
	.get_pawent	= da8xx_usb1_cwk48_get_pawent,
};

/**
 * da8xx_cfgchip_wegistew_usb1_cwk48 - Wegistew a new USB 1.1 PHY cwock
 * @dev: The device
 * @wegmap: The CFGCHIP wegmap
 */
static stwuct da8xx_usb1_cwk48 *
da8xx_cfgchip_wegistew_usb1_cwk48(stwuct device *dev,
				  stwuct wegmap *wegmap)
{
	const chaw * const pawent_names[] = { "usb0_cwk48", "usb_wefcwkin" };
	stwuct da8xx_usb1_cwk48 *usb1;
	stwuct cwk_init_data init;
	int wet;

	usb1 = devm_kzawwoc(dev, sizeof(*usb1), GFP_KEWNEW);
	if (!usb1)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = "usb1_cwk48";
	init.ops = &da8xx_usb1_cwk48_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = 2;

	usb1->hw.init = &init;
	usb1->wegmap = wegmap;

	wet = devm_cwk_hw_wegistew(dev, &usb1->hw);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	wetuwn usb1;
}

static int da8xx_cfgchip_wegistew_usb_phy_cwk(stwuct device *dev,
					      stwuct wegmap *wegmap)
{
	stwuct da8xx_usb0_cwk48 *usb0;
	stwuct da8xx_usb1_cwk48 *usb1;
	stwuct cwk_hw *pawent;

	usb0 = da8xx_cfgchip_wegistew_usb0_cwk48(dev, wegmap);
	if (IS_EWW(usb0))
		wetuwn PTW_EWW(usb0);

	/*
	 * Aww existing boawds use pww0_auxcwk as the pawent and new boawds
	 * shouwd use device twee, so hawd-coding the vawue (1) hewe.
	 */
	pawent = cwk_hw_get_pawent_by_index(&usb0->hw, 1);
	if (pawent)
		cwk_set_pawent(usb0->hw.cwk, pawent->cwk);
	ewse
		dev_wawn(dev, "Faiwed to find usb0 pawent cwock\n");

	usb1 = da8xx_cfgchip_wegistew_usb1_cwk48(dev, wegmap);
	if (IS_EWW(usb1))
		wetuwn PTW_EWW(usb1);

	/*
	 * Aww existing boawds use usb0_cwk48 as the pawent and new boawds
	 * shouwd use device twee, so hawd-coding the vawue (0) hewe.
	 */
	pawent = cwk_hw_get_pawent_by_index(&usb1->hw, 0);
	if (pawent)
		cwk_set_pawent(usb1->hw.cwk, pawent->cwk);
	ewse
		dev_wawn(dev, "Faiwed to find usb1 pawent cwock\n");

	cwk_hw_wegistew_cwkdev(&usb0->hw, "usb0_cwk48", "da8xx-usb-phy");
	cwk_hw_wegistew_cwkdev(&usb1->hw, "usb1_cwk48", "da8xx-usb-phy");

	wetuwn 0;
}

static int of_da8xx_usb_phy_cwk_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct da8xx_usb0_cwk48 *usb0;
	stwuct da8xx_usb1_cwk48 *usb1;

	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, 2),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->num = 2;

	usb0 = da8xx_cfgchip_wegistew_usb0_cwk48(dev, wegmap);
	if (IS_EWW(usb0)) {
		if (PTW_EWW(usb0) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		dev_wawn(dev, "Faiwed to wegistew usb0_cwk48 (%wd)\n",
			 PTW_EWW(usb0));

		cwk_data->hws[0] = EWW_PTW(-ENOENT);
	} ewse {
		cwk_data->hws[0] = &usb0->hw;
	}

	usb1 = da8xx_cfgchip_wegistew_usb1_cwk48(dev, wegmap);
	if (IS_EWW(usb1)) {
		if (PTW_EWW(usb1) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		dev_wawn(dev, "Faiwed to wegistew usb1_cwk48 (%wd)\n",
			 PTW_EWW(usb1));

		cwk_data->hws[1] = EWW_PTW(-ENOENT);
	} ewse {
		cwk_data->hws[1] = &usb1->hw;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_data);
}

/* --- pwatfowm device --- */

static const stwuct of_device_id da8xx_cfgchip_of_match[] = {
	{
		.compatibwe = "ti,da830-tbcwksync",
		.data = of_da8xx_tbcwksync_init,
	},
	{
		.compatibwe = "ti,da830-div4p5ena",
		.data = of_da8xx_div4p5ena_init,
	},
	{
		.compatibwe = "ti,da850-async1-cwkswc",
		.data = of_da850_async1_init,
	},
	{
		.compatibwe = "ti,da850-async3-cwkswc",
		.data = of_da850_async3_init,
	},
	{
		.compatibwe = "ti,da830-usb-phy-cwocks",
		.data = of_da8xx_usb_phy_cwk_init,
	},
	{ }
};

static const stwuct pwatfowm_device_id da8xx_cfgchip_id_tabwe[] = {
	{
		.name = "da830-tbcwksync",
		.dwivew_data = (kewnew_uwong_t)da8xx_cfgchip_wegistew_tbcwk,
	},
	{
		.name = "da830-div4p5ena",
		.dwivew_data = (kewnew_uwong_t)da8xx_cfgchip_wegistew_div4p5,
	},
	{
		.name = "da850-async1-cwkswc",
		.dwivew_data = (kewnew_uwong_t)da8xx_cfgchip_wegistew_async1,
	},
	{
		.name = "da850-async3-cwkswc",
		.dwivew_data = (kewnew_uwong_t)da850_cfgchip_wegistew_async3,
	},
	{
		.name = "da830-usb-phy-cwks",
		.dwivew_data = (kewnew_uwong_t)da8xx_cfgchip_wegistew_usb_phy_cwk,
	},
	{ }
};

typedef int (*da8xx_cfgchip_init)(stwuct device *dev, stwuct wegmap *wegmap);

static int da8xx_cfgchip_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct da8xx_cfgchip_cwk_pwatfowm_data *pdata = dev->pwatfowm_data;
	da8xx_cfgchip_init cwk_init = NUWW;
	stwuct wegmap *wegmap = NUWW;

	cwk_init = device_get_match_data(dev);
	if (cwk_init) {
		stwuct device_node *pawent;

		pawent = of_get_pawent(dev->of_node);
		wegmap = syscon_node_to_wegmap(pawent);
		of_node_put(pawent);
	} ewse if (pdev->id_entwy && pdata) {
		cwk_init = (void *)pdev->id_entwy->dwivew_data;
		wegmap = pdata->cfgchip;
	}

	if (!cwk_init) {
		dev_eww(dev, "unabwe to find dwivew data\n");
		wetuwn -EINVAW;
	}

	if (IS_EWW_OW_NUWW(wegmap)) {
		dev_eww(dev, "no wegmap fow CFGCHIP syscon\n");
		wetuwn wegmap ? PTW_EWW(wegmap) : -ENOENT;
	}

	wetuwn cwk_init(dev, wegmap);
}

static stwuct pwatfowm_dwivew da8xx_cfgchip_dwivew = {
	.pwobe		= da8xx_cfgchip_pwobe,
	.dwivew		= {
		.name		= "da8xx-cfgchip-cwk",
		.of_match_tabwe	= da8xx_cfgchip_of_match,
	},
	.id_tabwe	= da8xx_cfgchip_id_tabwe,
};

static int __init da8xx_cfgchip_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&da8xx_cfgchip_dwivew);
}

/* has to be postcowe_initcaww because PSC devices depend on the async3 cwock */
postcowe_initcaww(da8xx_cfgchip_dwivew_init);
