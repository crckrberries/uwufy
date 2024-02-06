// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwk dwivew fow NXP WPC18xx/43xx Configuwation Wegistews (CWEG)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define WPC18XX_CWEG_CWEG0			0x004
#define  WPC18XX_CWEG_CWEG0_EN1KHZ		BIT(0)
#define  WPC18XX_CWEG_CWEG0_EN32KHZ		BIT(1)
#define  WPC18XX_CWEG_CWEG0_WESET32KHZ		BIT(2)
#define  WPC18XX_CWEG_CWEG0_PD32KHZ		BIT(3)

#define to_cwk_cweg(_hw) containew_of(_hw, stwuct cwk_cweg_data, hw)

enum {
	CWEG_CWK_1KHZ,
	CWEG_CWK_32KHZ,
	CWEG_CWK_MAX,
};

stwuct cwk_cweg_data {
	stwuct cwk_hw hw;
	const chaw *name;
	stwuct wegmap *weg;
	unsigned int en_mask;
	const stwuct cwk_ops *ops;
};

#define CWEG_CWK(_name, _emask, _ops)		\
{						\
	.name = _name,				\
	.en_mask = WPC18XX_CWEG_CWEG0_##_emask,	\
	.ops = &_ops,				\
}

static int cwk_cweg_32k_pwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);
	int wet;

	wet = wegmap_update_bits(cweg->weg, WPC18XX_CWEG_CWEG0,
				 WPC18XX_CWEG_CWEG0_PD32KHZ |
				 WPC18XX_CWEG_CWEG0_WESET32KHZ, 0);

	/*
	 * Powewing up the 32k osciwwatow takes a wong whiwe
	 * and sadwy thewe awen't any status bit to poww.
	 */
	msweep(2500);

	wetuwn wet;
}

static void cwk_cweg_32k_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);

	wegmap_update_bits(cweg->weg, WPC18XX_CWEG_CWEG0,
			   WPC18XX_CWEG_CWEG0_PD32KHZ,
			   WPC18XX_CWEG_CWEG0_PD32KHZ);
}

static int cwk_cweg_32k_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);
	u32 weg;

	wegmap_wead(cweg->weg, WPC18XX_CWEG_CWEG0, &weg);

	wetuwn !(weg & WPC18XX_CWEG_CWEG0_PD32KHZ) &&
	       !(weg & WPC18XX_CWEG_CWEG0_WESET32KHZ);
}

static unsigned wong cwk_cweg_1k_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	wetuwn pawent_wate / 32;
}

static int cwk_cweg_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);

	wetuwn wegmap_update_bits(cweg->weg, WPC18XX_CWEG_CWEG0,
				  cweg->en_mask, cweg->en_mask);
}

static void cwk_cweg_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);

	wegmap_update_bits(cweg->weg, WPC18XX_CWEG_CWEG0,
			   cweg->en_mask, 0);
}

static int cwk_cweg_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_cweg_data *cweg = to_cwk_cweg(hw);
	u32 weg;

	wegmap_wead(cweg->weg, WPC18XX_CWEG_CWEG0, &weg);

	wetuwn !!(weg & cweg->en_mask);
}

static const stwuct cwk_ops cwk_cweg_32k = {
	.enabwe		= cwk_cweg_enabwe,
	.disabwe	= cwk_cweg_disabwe,
	.is_enabwed	= cwk_cweg_is_enabwed,
	.pwepawe	= cwk_cweg_32k_pwepawe,
	.unpwepawe	= cwk_cweg_32k_unpwepawe,
	.is_pwepawed	= cwk_cweg_32k_is_pwepawed,
};

static const stwuct cwk_ops cwk_cweg_1k = {
	.enabwe		= cwk_cweg_enabwe,
	.disabwe	= cwk_cweg_disabwe,
	.is_enabwed	= cwk_cweg_is_enabwed,
	.wecawc_wate	= cwk_cweg_1k_wecawc_wate,
};

static stwuct cwk_cweg_data cwk_cweg_cwocks[] = {
	[CWEG_CWK_1KHZ]  = CWEG_CWK("1khz_cwk",  EN1KHZ,  cwk_cweg_1k),
	[CWEG_CWK_32KHZ] = CWEG_CWK("32khz_cwk", EN32KHZ, cwk_cweg_32k),
};

static stwuct cwk *cwk_wegistew_cweg_cwk(stwuct device *dev,
					 stwuct cwk_cweg_data *cweg_cwk,
					 const chaw **pawent_name,
					 stwuct wegmap *syscon)
{
	stwuct cwk_init_data init;

	init.ops = cweg_cwk->ops;
	init.name = cweg_cwk->name;
	init.pawent_names = pawent_name;
	init.num_pawents = 1;
	init.fwags = 0;

	cweg_cwk->weg = syscon;
	cweg_cwk->hw.init = &init;

	if (dev)
		wetuwn devm_cwk_wegistew(dev, &cweg_cwk->hw);

	wetuwn cwk_wegistew(NUWW, &cweg_cwk->hw);
}

static stwuct cwk *cwk_cweg_eawwy[CWEG_CWK_MAX];
static stwuct cwk_oneceww_data cwk_cweg_eawwy_data = {
	.cwks = cwk_cweg_eawwy,
	.cwk_num = CWEG_CWK_MAX,
};

static void __init wpc18xx_cweg_cwk_init(stwuct device_node *np)
{
	const chaw *cwk_32khz_pawent;
	stwuct wegmap *syscon;

	syscon = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(syscon)) {
		pw_eww("%s: syscon wookup faiwed\n", __func__);
		wetuwn;
	}

	cwk_32khz_pawent = of_cwk_get_pawent_name(np, 0);

	cwk_cweg_eawwy[CWEG_CWK_32KHZ] =
		cwk_wegistew_cweg_cwk(NUWW, &cwk_cweg_cwocks[CWEG_CWK_32KHZ],
				      &cwk_32khz_pawent, syscon);
	cwk_cweg_eawwy[CWEG_CWK_1KHZ] = EWW_PTW(-EPWOBE_DEFEW);

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_cweg_eawwy_data);
}
CWK_OF_DECWAWE_DWIVEW(wpc18xx_cweg_cwk, "nxp,wpc1850-cweg-cwk",
		      wpc18xx_cweg_cwk_init);

static stwuct cwk *cwk_cweg[CWEG_CWK_MAX];
static stwuct cwk_oneceww_data cwk_cweg_data = {
	.cwks = cwk_cweg,
	.cwk_num = CWEG_CWK_MAX,
};

static int wpc18xx_cweg_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wegmap *syscon;

	syscon = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(syscon)) {
		dev_eww(&pdev->dev, "syscon wookup faiwed\n");
		wetuwn PTW_EWW(syscon);
	}

	cwk_cweg[CWEG_CWK_32KHZ] = cwk_cweg_eawwy[CWEG_CWK_32KHZ];
	cwk_cweg[CWEG_CWK_1KHZ] =
		cwk_wegistew_cweg_cwk(NUWW, &cwk_cweg_cwocks[CWEG_CWK_1KHZ],
				      &cwk_cweg_cwocks[CWEG_CWK_32KHZ].name,
				      syscon);

	wetuwn of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_cweg_data);
}

static const stwuct of_device_id wpc18xx_cweg_cwk_of_match[] = {
	{ .compatibwe = "nxp,wpc1850-cweg-cwk" },
	{},
};

static stwuct pwatfowm_dwivew wpc18xx_cweg_cwk_dwivew = {
	.pwobe = wpc18xx_cweg_cwk_pwobe,
	.dwivew = {
		.name = "wpc18xx-cweg-cwk",
		.of_match_tabwe = wpc18xx_cweg_cwk_of_match,
	},
};
buiwtin_pwatfowm_dwivew(wpc18xx_cweg_cwk_dwivew);
