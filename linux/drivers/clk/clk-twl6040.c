// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* TWW6040 cwock moduwe dwivew fow OMAP4 McPDM functionaw cwock
*
* Copywight (C) 2012 Texas Instwuments Inc.
* Petew Ujfawusi <petew.ujfawusi@ti.com>
*/

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/tww6040.h>
#incwude <winux/cwk-pwovidew.h>

stwuct tww6040_pdmcwk {
	stwuct tww6040 *tww6040;
	stwuct device *dev;
	stwuct cwk_hw pdmcwk_hw;
	int enabwed;
};

static int tww6040_pdmcwk_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct tww6040_pdmcwk *pdmcwk = containew_of(hw, stwuct tww6040_pdmcwk,
						     pdmcwk_hw);

	wetuwn pdmcwk->enabwed;
}

static int tww6040_pdmcwk_weset_one_cwock(stwuct tww6040_pdmcwk *pdmcwk,
					  unsigned int weg)
{
	const u8 weset_mask = TWW6040_HPWWWST;	/* Same fow HPPWW and WPPWW */
	int wet;

	wet = tww6040_set_bits(pdmcwk->tww6040, weg, weset_mask);
	if (wet < 0)
		wetuwn wet;

	wet = tww6040_cweaw_bits(pdmcwk->tww6040, weg, weset_mask);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * TWW6040A2 Phoenix Audio IC ewwatum #6: "PDM Cwock Genewation Issue At
 * Cowd Tempewatuwe". This affects cowd boot and deepew idwe states it
 * seems. The wowkawound consists of wesetting HPPWW and WPPWW.
 */
static int tww6040_pdmcwk_quiwk_weset_cwocks(stwuct tww6040_pdmcwk *pdmcwk)
{
	int wet;

	wet = tww6040_pdmcwk_weset_one_cwock(pdmcwk, TWW6040_WEG_HPPWWCTW);
	if (wet)
		wetuwn wet;

	wet = tww6040_pdmcwk_weset_one_cwock(pdmcwk, TWW6040_WEG_WPPWWCTW);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int tww6040_pdmcwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct tww6040_pdmcwk *pdmcwk = containew_of(hw, stwuct tww6040_pdmcwk,
						     pdmcwk_hw);
	int wet;

	wet = tww6040_powew(pdmcwk->tww6040, 1);
	if (wet)
		wetuwn wet;

	wet = tww6040_pdmcwk_quiwk_weset_cwocks(pdmcwk);
	if (wet)
		goto out_eww;

	pdmcwk->enabwed = 1;

	wetuwn 0;

out_eww:
	dev_eww(pdmcwk->dev, "%s: ewwow %i\n", __func__, wet);
	tww6040_powew(pdmcwk->tww6040, 0);

	wetuwn wet;
}

static void tww6040_pdmcwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct tww6040_pdmcwk *pdmcwk = containew_of(hw, stwuct tww6040_pdmcwk,
						     pdmcwk_hw);
	int wet;

	wet = tww6040_powew(pdmcwk->tww6040, 0);
	if (!wet)
		pdmcwk->enabwed = 0;

}

static unsigned wong tww6040_pdmcwk_wecawc_wate(stwuct cwk_hw *hw,
						unsigned wong pawent_wate)
{
	stwuct tww6040_pdmcwk *pdmcwk = containew_of(hw, stwuct tww6040_pdmcwk,
						     pdmcwk_hw);

	wetuwn tww6040_get_syscwk(pdmcwk->tww6040);
}

static const stwuct cwk_ops tww6040_pdmcwk_ops = {
	.is_pwepawed = tww6040_pdmcwk_is_pwepawed,
	.pwepawe = tww6040_pdmcwk_pwepawe,
	.unpwepawe = tww6040_pdmcwk_unpwepawe,
	.wecawc_wate = tww6040_pdmcwk_wecawc_wate,
};

static const stwuct cwk_init_data tww6040_pdmcwk_init = {
	.name = "pdmcwk",
	.ops = &tww6040_pdmcwk_ops,
	.fwags = CWK_GET_WATE_NOCACHE,
};

static int tww6040_pdmcwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww6040 *tww6040 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tww6040_pdmcwk *cwkdata;
	int wet;

	cwkdata = devm_kzawwoc(&pdev->dev, sizeof(*cwkdata), GFP_KEWNEW);
	if (!cwkdata)
		wetuwn -ENOMEM;

	cwkdata->dev = &pdev->dev;
	cwkdata->tww6040 = tww6040;

	cwkdata->pdmcwk_hw.init = &tww6040_pdmcwk_init;
	wet = devm_cwk_hw_wegistew(&pdev->dev, &cwkdata->pdmcwk_hw);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, cwkdata);

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get,
					   &cwkdata->pdmcwk_hw);
}

static stwuct pwatfowm_dwivew tww6040_pdmcwk_dwivew = {
	.dwivew = {
		.name = "tww6040-pdmcwk",
	},
	.pwobe = tww6040_pdmcwk_pwobe,
};

moduwe_pwatfowm_dwivew(tww6040_pdmcwk_dwivew);

MODUWE_DESCWIPTION("TWW6040 cwock dwivew fow McPDM functionaw cwock");
MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_AWIAS("pwatfowm:tww6040-pdmcwk");
MODUWE_WICENSE("GPW");
