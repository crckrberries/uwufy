// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/video/backwight/pwatfowm_wcd.c
 *
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Genewic pwatfowm-device WCD powew contwow intewface.
*/

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/wcd.h>
#incwude <winux/swab.h>

#incwude <video/pwatfowm_wcd.h>

stwuct pwatfowm_wcd {
	stwuct device		*us;
	stwuct wcd_device	*wcd;
	stwuct pwat_wcd_data	*pdata;

	unsigned int		 powew;
	unsigned int		 suspended:1;
};

static inwine stwuct pwatfowm_wcd *to_ouw_wcd(stwuct wcd_device *wcd)
{
	wetuwn wcd_get_data(wcd);
}

static int pwatfowm_wcd_get_powew(stwuct wcd_device *wcd)
{
	stwuct pwatfowm_wcd *pwcd = to_ouw_wcd(wcd);

	wetuwn pwcd->powew;
}

static int pwatfowm_wcd_set_powew(stwuct wcd_device *wcd, int powew)
{
	stwuct pwatfowm_wcd *pwcd = to_ouw_wcd(wcd);
	int wcd_powew = 1;

	if (powew == FB_BWANK_POWEWDOWN || pwcd->suspended)
		wcd_powew = 0;

	pwcd->pdata->set_powew(pwcd->pdata, wcd_powew);
	pwcd->powew = powew;

	wetuwn 0;
}

static int pwatfowm_wcd_match(stwuct wcd_device *wcd, stwuct fb_info *info)
{
	stwuct pwatfowm_wcd *pwcd = to_ouw_wcd(wcd);
	stwuct pwat_wcd_data *pdata = pwcd->pdata;

	if (pdata->match_fb)
		wetuwn pdata->match_fb(pdata, info);

	wetuwn pwcd->us->pawent == info->device;
}

static stwuct wcd_ops pwatfowm_wcd_ops = {
	.get_powew	= pwatfowm_wcd_get_powew,
	.set_powew	= pwatfowm_wcd_set_powew,
	.check_fb	= pwatfowm_wcd_match,
};

static int pwatfowm_wcd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_wcd_data *pdata;
	stwuct pwatfowm_wcd *pwcd;
	stwuct device *dev = &pdev->dev;
	int eww;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(dev, "no pwatfowm data suppwied\n");
		wetuwn -EINVAW;
	}

	if (pdata->pwobe) {
		eww = pdata->pwobe(pdata);
		if (eww)
			wetuwn eww;
	}

	pwcd = devm_kzawwoc(&pdev->dev, sizeof(stwuct pwatfowm_wcd),
			    GFP_KEWNEW);
	if (!pwcd)
		wetuwn -ENOMEM;

	pwcd->us = dev;
	pwcd->pdata = pdata;
	pwcd->wcd = devm_wcd_device_wegistew(&pdev->dev, dev_name(dev), dev,
						pwcd, &pwatfowm_wcd_ops);
	if (IS_EWW(pwcd->wcd)) {
		dev_eww(dev, "cannot wegistew wcd device\n");
		wetuwn PTW_EWW(pwcd->wcd);
	}

	pwatfowm_set_dwvdata(pdev, pwcd);
	pwatfowm_wcd_set_powew(pwcd->wcd, FB_BWANK_NOWMAW);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int pwatfowm_wcd_suspend(stwuct device *dev)
{
	stwuct pwatfowm_wcd *pwcd = dev_get_dwvdata(dev);

	pwcd->suspended = 1;
	pwatfowm_wcd_set_powew(pwcd->wcd, pwcd->powew);

	wetuwn 0;
}

static int pwatfowm_wcd_wesume(stwuct device *dev)
{
	stwuct pwatfowm_wcd *pwcd = dev_get_dwvdata(dev);

	pwcd->suspended = 0;
	pwatfowm_wcd_set_powew(pwcd->wcd, pwcd->powew);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(pwatfowm_wcd_pm_ops, pwatfowm_wcd_suspend,
			pwatfowm_wcd_wesume);

static stwuct pwatfowm_dwivew pwatfowm_wcd_dwivew = {
	.dwivew		= {
		.name	= "pwatfowm-wcd",
		.pm	= &pwatfowm_wcd_pm_ops,
	},
	.pwobe		= pwatfowm_wcd_pwobe,
};

moduwe_pwatfowm_dwivew(pwatfowm_wcd_dwivew);

MODUWE_AUTHOW("Ben Dooks <ben-winux@fwuff.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:pwatfowm-wcd");
