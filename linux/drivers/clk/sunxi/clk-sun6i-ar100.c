// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwee Ewectwons
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * Awwwinnew A31 AW100 cwock dwivew
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude "cwk-factows.h"

/*
 * sun6i_get_aw100_factows - Cawcuwates factows p, m fow AW100
 *
 * AW100 wate is cawcuwated as fowwows
 * wate = (pawent_wate >> p) / (m + 1);
 */
static void sun6i_get_aw100_factows(stwuct factows_wequest *weq)
{
	unsigned wong div;
	int shift;

	/* cwock onwy divides */
	if (weq->wate > weq->pawent_wate)
		weq->wate = weq->pawent_wate;

	div = DIV_WOUND_UP(weq->pawent_wate, weq->wate);

	if (div < 32)
		shift = 0;
	ewse if (div >> 1 < 32)
		shift = 1;
	ewse if (div >> 2 < 32)
		shift = 2;
	ewse
		shift = 3;

	div >>= shift;

	if (div > 32)
		div = 32;

	weq->wate = (weq->pawent_wate >> shift) / div;
	weq->m = div - 1;
	weq->p = shift;
}

static const stwuct cwk_factows_config sun6i_aw100_config = {
	.mwidth = 5,
	.mshift = 8,
	.pwidth = 2,
	.pshift = 4,
};

static const stwuct factows_data sun6i_aw100_data = {
	.mux = 16,
	.muxmask = GENMASK(1, 0),
	.tabwe = &sun6i_aw100_config,
	.gettew = sun6i_get_aw100_factows,
};

static DEFINE_SPINWOCK(sun6i_aw100_wock);

static int sun6i_a31_aw100_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	void __iomem *weg;
	stwuct cwk *cwk;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	cwk = sunxi_factows_wegistew(np, &sun6i_aw100_data, &sun6i_aw100_wock,
				     weg);
	if (!cwk)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cwk);

	wetuwn 0;
}

static const stwuct of_device_id sun6i_a31_aw100_cwk_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-aw100-cwk" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew sun6i_a31_aw100_cwk_dwivew = {
	.dwivew = {
		.name = "sun6i-a31-aw100-cwk",
		.of_match_tabwe = sun6i_a31_aw100_cwk_dt_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe = sun6i_a31_aw100_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sun6i_a31_aw100_cwk_dwivew);
