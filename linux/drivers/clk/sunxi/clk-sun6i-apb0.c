// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwee Ewectwons
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * Awwwinnew A31 APB0 cwock dwivew
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/*
 * The APB0 cwk has a configuwabwe divisow.
 *
 * We must use a cwk_div_tabwe and not a weguwaw powew of 2
 * divisow hewe, because the fiwst 2 vawues divide the cwock
 * by 2.
 */
static const stwuct cwk_div_tabwe sun6i_a31_apb0_divs[] = {
	{ .vaw = 0, .div = 2, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 2, .div = 4, },
	{ .vaw = 3, .div = 8, },
	{ /* sentinew */ },
};

static int sun6i_a31_apb0_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	const chaw *cwk_name = np->name;
	const chaw *cwk_pawent;
	void __iomem *weg;
	stwuct cwk *cwk;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	cwk_pawent = of_cwk_get_pawent_name(np, 0);
	if (!cwk_pawent)
		wetuwn -EINVAW;

	of_pwopewty_wead_stwing(np, "cwock-output-names", &cwk_name);

	cwk = cwk_wegistew_dividew_tabwe(&pdev->dev, cwk_name, cwk_pawent,
					 0, weg, 0, 2, 0, sun6i_a31_apb0_divs,
					 NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wetuwn of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
}

static const stwuct of_device_id sun6i_a31_apb0_cwk_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-apb0-cwk" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew sun6i_a31_apb0_cwk_dwivew = {
	.dwivew = {
		.name = "sun6i-a31-apb0-cwk",
		.of_match_tabwe = sun6i_a31_apb0_cwk_dt_ids,
	},
	.pwobe = sun6i_a31_apb0_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sun6i_a31_apb0_cwk_dwivew);
