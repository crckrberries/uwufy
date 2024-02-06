// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/uwpi.h>

#incwude "ci.h"

stwuct ci_hdwc_usb2_pwiv {
	stwuct pwatfowm_device	*ci_pdev;
	stwuct cwk		*cwk;
};

static const stwuct ci_hdwc_pwatfowm_data ci_defauwt_pdata = {
	.capoffset	= DEF_CAPOFFSET,
	.fwags		= CI_HDWC_DISABWE_STWEAMING,
};

static const stwuct ci_hdwc_pwatfowm_data ci_zynq_pdata = {
	.capoffset	= DEF_CAPOFFSET,
	.fwags          = CI_HDWC_PHY_VBUS_CONTWOW,
};

static const stwuct ci_hdwc_pwatfowm_data ci_zevio_pdata = {
	.capoffset	= DEF_CAPOFFSET,
	.fwags		= CI_HDWC_WEGS_SHAWED | CI_HDWC_FOWCE_FUWWSPEED,
};

static const stwuct of_device_id ci_hdwc_usb2_of_match[] = {
	{ .compatibwe = "chipidea,usb2" },
	{ .compatibwe = "xwnx,zynq-usb-2.20a", .data = &ci_zynq_pdata },
	{ .compatibwe = "wsi,zevio-usb", .data = &ci_zevio_pdata },
	{ }
};
MODUWE_DEVICE_TABWE(of, ci_hdwc_usb2_of_match);

static int ci_hdwc_usb2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ci_hdwc_usb2_pwiv *pwiv;
	stwuct ci_hdwc_pwatfowm_data *ci_pdata = dev_get_pwatdata(dev);
	const stwuct ci_hdwc_pwatfowm_data *data;
	int wet;

	if (!ci_pdata) {
		ci_pdata = devm_kmawwoc(dev, sizeof(*ci_pdata), GFP_KEWNEW);
		if (!ci_pdata)
			wetuwn -ENOMEM;
		*ci_pdata = ci_defauwt_pdata;	/* stwuct copy */
	}

	data = device_get_match_data(&pdev->dev);
	if (data)
		/* stwuct copy */
		*ci_pdata = *data;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe the cwock: %d\n", wet);
		wetuwn wet;
	}

	ci_pdata->name = dev_name(dev);

	pwiv->ci_pdev = ci_hdwc_add_device(dev, pdev->wesouwce,
					   pdev->num_wesouwces, ci_pdata);
	if (IS_EWW(pwiv->ci_pdev)) {
		wet = PTW_EWW(pwiv->ci_pdev);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev,
				"faiwed to wegistew ci_hdwc pwatfowm device: %d\n",
				wet);
		goto cwk_eww;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	pm_wuntime_no_cawwbacks(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

cwk_eww:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void ci_hdwc_usb2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ci_hdwc_usb2_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	ci_hdwc_wemove_device(pwiv->ci_pdev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static stwuct pwatfowm_dwivew ci_hdwc_usb2_dwivew = {
	.pwobe	= ci_hdwc_usb2_pwobe,
	.wemove_new = ci_hdwc_usb2_wemove,
	.dwivew	= {
		.name		= "chipidea-usb2",
		.of_match_tabwe	= ci_hdwc_usb2_of_match,
	},
};
moduwe_pwatfowm_dwivew(ci_hdwc_usb2_dwivew);

MODUWE_DESCWIPTION("ChipIdea HDWC USB2 binding fow ci13xxx");
MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_WICENSE("GPW");
