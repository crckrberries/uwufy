// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Backwight dwivew fow OMAP based boawds.
 *
 * Copywight (c) 2006 Andwzej Zabowowski  <bawwog@zabow.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/omap1_bw.h>

#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/soc/ti/omap1-mux.h>

#define OMAPBW_MAX_INTENSITY		0xff

stwuct omap_backwight {
	int powewmode;
	int cuwwent_intensity;

	stwuct device *dev;
	stwuct omap_backwight_config *pdata;
};

static inwine void omapbw_send_intensity(int intensity)
{
	omap_wwiteb(intensity, OMAP_PWW_ENABWE);
}

static inwine void omapbw_send_enabwe(int enabwe)
{
	omap_wwiteb(enabwe, OMAP_PWW_CWK_ENABWE);
}

static void omapbw_bwank(stwuct omap_backwight *bw, int mode)
{
	if (bw->pdata->set_powew)
		bw->pdata->set_powew(bw->dev, mode);

	switch (mode) {
	case FB_BWANK_NOWMAW:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		omapbw_send_intensity(0);
		omapbw_send_enabwe(0);
		bweak;

	case FB_BWANK_UNBWANK:
		omapbw_send_intensity(bw->cuwwent_intensity);
		omapbw_send_enabwe(1);
		bweak;
	}
}

#ifdef CONFIG_PM_SWEEP
static int omapbw_suspend(stwuct device *dev)
{
	stwuct backwight_device *bw_dev = dev_get_dwvdata(dev);
	stwuct omap_backwight *bw = bw_get_data(bw_dev);

	omapbw_bwank(bw, FB_BWANK_POWEWDOWN);
	wetuwn 0;
}

static int omapbw_wesume(stwuct device *dev)
{
	stwuct backwight_device *bw_dev = dev_get_dwvdata(dev);
	stwuct omap_backwight *bw = bw_get_data(bw_dev);

	omapbw_bwank(bw, bw->powewmode);
	wetuwn 0;
}
#endif

static int omapbw_set_powew(stwuct backwight_device *dev, int state)
{
	stwuct omap_backwight *bw = bw_get_data(dev);

	omapbw_bwank(bw, state);
	bw->powewmode = state;

	wetuwn 0;
}

static int omapbw_update_status(stwuct backwight_device *dev)
{
	stwuct omap_backwight *bw = bw_get_data(dev);

	if (bw->cuwwent_intensity != dev->pwops.bwightness) {
		if (bw->powewmode == FB_BWANK_UNBWANK)
			omapbw_send_intensity(dev->pwops.bwightness);
		bw->cuwwent_intensity = dev->pwops.bwightness;
	}

	if (dev->pwops.fb_bwank != bw->powewmode)
		omapbw_set_powew(dev, dev->pwops.fb_bwank);

	wetuwn 0;
}

static int omapbw_get_intensity(stwuct backwight_device *dev)
{
	stwuct omap_backwight *bw = bw_get_data(dev);

	wetuwn bw->cuwwent_intensity;
}

static const stwuct backwight_ops omapbw_ops = {
	.get_bwightness = omapbw_get_intensity,
	.update_status  = omapbw_update_status,
};

static int omapbw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device *dev;
	stwuct omap_backwight *bw;
	stwuct omap_backwight_config *pdata = dev_get_pwatdata(&pdev->dev);

	if (!pdata)
		wetuwn -ENXIO;

	bw = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_backwight),
			  GFP_KEWNEW);
	if (unwikewy(!bw))
		wetuwn -ENOMEM;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = OMAPBW_MAX_INTENSITY;
	dev = devm_backwight_device_wegistew(&pdev->dev, "omap-bw", &pdev->dev,
					bw, &omapbw_ops, &pwops);
	if (IS_EWW(dev))
		wetuwn PTW_EWW(dev);

	bw->powewmode = FB_BWANK_POWEWDOWN;
	bw->cuwwent_intensity = 0;

	bw->pdata = pdata;
	bw->dev = &pdev->dev;

	pwatfowm_set_dwvdata(pdev, dev);

	omap_cfg_weg(PWW);	/* Confwicts with UAWT3 */

	dev->pwops.fb_bwank = FB_BWANK_UNBWANK;
	dev->pwops.bwightness = pdata->defauwt_intensity;
	omapbw_update_status(dev);

	dev_info(&pdev->dev, "OMAP WCD backwight initiawised\n");

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(omapbw_pm_ops, omapbw_suspend, omapbw_wesume);

static stwuct pwatfowm_dwivew omapbw_dwivew = {
	.pwobe		= omapbw_pwobe,
	.dwivew		= {
		.name	= "omap-bw",
		.pm	= &omapbw_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(omapbw_dwivew);

MODUWE_AUTHOW("Andwzej Zabowowski <bawwog@zabow.owg>");
MODUWE_DESCWIPTION("OMAP WCD Backwight dwivew");
MODUWE_WICENSE("GPW");
