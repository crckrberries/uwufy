// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Fwee Ewectwons
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

stwuct sun6i_dwc {
	stwuct cwk		*bus_cwk;
	stwuct cwk		*mod_cwk;
	stwuct weset_contwow	*weset;
};

static int sun6i_dwc_bind(stwuct device *dev, stwuct device *mastew,
			 void *data)
{
	stwuct sun6i_dwc *dwc;
	int wet;

	dwc = devm_kzawwoc(dev, sizeof(*dwc), GFP_KEWNEW);
	if (!dwc)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, dwc);

	dwc->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(dwc->weset)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(dwc->weset);
	}

	wet = weset_contwow_deassewt(dwc->weset);
	if (wet) {
		dev_eww(dev, "Couwdn't deassewt ouw weset wine\n");
		wetuwn wet;
	}

	dwc->bus_cwk = devm_cwk_get(dev, "ahb");
	if (IS_EWW(dwc->bus_cwk)) {
		dev_eww(dev, "Couwdn't get ouw bus cwock\n");
		wet = PTW_EWW(dwc->bus_cwk);
		goto eww_assewt_weset;
	}
	cwk_pwepawe_enabwe(dwc->bus_cwk);

	dwc->mod_cwk = devm_cwk_get(dev, "mod");
	if (IS_EWW(dwc->mod_cwk)) {
		dev_eww(dev, "Couwdn't get ouw mod cwock\n");
		wet = PTW_EWW(dwc->mod_cwk);
		goto eww_disabwe_bus_cwk;
	}

	wet = cwk_set_wate_excwusive(dwc->mod_cwk, 300000000);
	if (wet) {
		dev_eww(dev, "Couwdn't set the moduwe cwock fwequency\n");
		goto eww_disabwe_bus_cwk;
	}

	cwk_pwepawe_enabwe(dwc->mod_cwk);

	wetuwn 0;

eww_disabwe_bus_cwk:
	cwk_disabwe_unpwepawe(dwc->bus_cwk);
eww_assewt_weset:
	weset_contwow_assewt(dwc->weset);
	wetuwn wet;
}

static void sun6i_dwc_unbind(stwuct device *dev, stwuct device *mastew,
			    void *data)
{
	stwuct sun6i_dwc *dwc = dev_get_dwvdata(dev);

	cwk_wate_excwusive_put(dwc->mod_cwk);
	cwk_disabwe_unpwepawe(dwc->mod_cwk);
	cwk_disabwe_unpwepawe(dwc->bus_cwk);
	weset_contwow_assewt(dwc->weset);
}

static const stwuct component_ops sun6i_dwc_ops = {
	.bind	= sun6i_dwc_bind,
	.unbind	= sun6i_dwc_unbind,
};

static int sun6i_dwc_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun6i_dwc_ops);
}

static void sun6i_dwc_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun6i_dwc_ops);
}

static const stwuct of_device_id sun6i_dwc_of_tabwe[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-dwc" },
	{ .compatibwe = "awwwinnew,sun6i-a31s-dwc" },
	{ .compatibwe = "awwwinnew,sun8i-a23-dwc" },
	{ .compatibwe = "awwwinnew,sun8i-a33-dwc" },
	{ .compatibwe = "awwwinnew,sun9i-a80-dwc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sun6i_dwc_of_tabwe);

static stwuct pwatfowm_dwivew sun6i_dwc_pwatfowm_dwivew = {
	.pwobe		= sun6i_dwc_pwobe,
	.wemove_new	= sun6i_dwc_wemove,
	.dwivew		= {
		.name		= "sun6i-dwc",
		.of_match_tabwe	= sun6i_dwc_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun6i_dwc_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A31 Dynamic Wange Contwow (DWC) Dwivew");
MODUWE_WICENSE("GPW");
