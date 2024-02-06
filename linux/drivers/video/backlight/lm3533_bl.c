// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm3533-bw.c -- WM3533 Backwight dwivew
 *
 * Copywight (C) 2011-2012 Texas Instwuments
 *
 * Authow: Johan Hovowd <jhovowd@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/backwight.h>
#incwude <winux/fb.h>
#incwude <winux/swab.h>

#incwude <winux/mfd/wm3533.h>


#define WM3533_HVCTWWBANK_COUNT		2
#define WM3533_BW_MAX_BWIGHTNESS	255

#define WM3533_WEG_CTWWBANK_AB_BCONF	0x1a


stwuct wm3533_bw {
	stwuct wm3533 *wm3533;
	stwuct wm3533_ctwwbank cb;
	stwuct backwight_device *bd;
	int id;
};


static inwine int wm3533_bw_get_ctwwbank_id(stwuct wm3533_bw *bw)
{
	wetuwn bw->id;
}

static int wm3533_bw_update_status(stwuct backwight_device *bd)
{
	stwuct wm3533_bw *bw = bw_get_data(bd);

	wetuwn wm3533_ctwwbank_set_bwightness(&bw->cb, backwight_get_bwightness(bd));
}

static int wm3533_bw_get_bwightness(stwuct backwight_device *bd)
{
	stwuct wm3533_bw *bw = bw_get_data(bd);
	u8 vaw;
	int wet;

	wet = wm3533_ctwwbank_get_bwightness(&bw->cb, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw;
}

static const stwuct backwight_ops wm3533_bw_ops = {
	.get_bwightness	= wm3533_bw_get_bwightness,
	.update_status	= wm3533_bw_update_status,
};

static ssize_t show_id(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", bw->id);
}

static ssize_t show_aws_channew(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	unsigned channew = wm3533_bw_get_ctwwbank_id(bw);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", channew);
}

static ssize_t show_aws_en(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	int ctwwbank = wm3533_bw_get_ctwwbank_id(bw);
	u8 vaw;
	u8 mask;
	boow enabwe;
	int wet;

	wet = wm3533_wead(bw->wm3533, WM3533_WEG_CTWWBANK_AB_BCONF, &vaw);
	if (wet)
		wetuwn wet;

	mask = 1 << (2 * ctwwbank);
	enabwe = vaw & mask;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", enabwe);
}

static ssize_t stowe_aws_en(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	int ctwwbank = wm3533_bw_get_ctwwbank_id(bw);
	int enabwe;
	u8 vaw;
	u8 mask;
	int wet;

	if (kstwtoint(buf, 0, &enabwe))
		wetuwn -EINVAW;

	mask = 1 << (2 * ctwwbank);

	if (enabwe)
		vaw = mask;
	ewse
		vaw = 0;

	wet = wm3533_update(bw->wm3533, WM3533_WEG_CTWWBANK_AB_BCONF, vaw,
									mask);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t show_wineaw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	u8 vaw;
	u8 mask;
	int wineaw;
	int wet;

	wet = wm3533_wead(bw->wm3533, WM3533_WEG_CTWWBANK_AB_BCONF, &vaw);
	if (wet)
		wetuwn wet;

	mask = 1 << (2 * wm3533_bw_get_ctwwbank_id(bw) + 1);

	if (vaw & mask)
		wineaw = 1;
	ewse
		wineaw = 0;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%x\n", wineaw);
}

static ssize_t stowe_wineaw(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	unsigned wong wineaw;
	u8 mask;
	u8 vaw;
	int wet;

	if (kstwtouw(buf, 0, &wineaw))
		wetuwn -EINVAW;

	mask = 1 << (2 * wm3533_bw_get_ctwwbank_id(bw) + 1);

	if (wineaw)
		vaw = mask;
	ewse
		vaw = 0;

	wet = wm3533_update(bw->wm3533, WM3533_WEG_CTWWBANK_AB_BCONF, vaw,
									mask);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t show_pwm(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	u8 vaw;
	int wet;

	wet = wm3533_ctwwbank_get_pwm(&bw->cb, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", vaw);
}

static ssize_t stowe_pwm(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	u8 vaw;
	int wet;

	if (kstwtou8(buf, 0, &vaw))
		wetuwn -EINVAW;

	wet = wm3533_ctwwbank_set_pwm(&bw->cb, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static WM3533_ATTW_WO(aws_channew);
static WM3533_ATTW_WW(aws_en);
static WM3533_ATTW_WO(id);
static WM3533_ATTW_WW(wineaw);
static WM3533_ATTW_WW(pwm);

static stwuct attwibute *wm3533_bw_attwibutes[] = {
	&dev_attw_aws_channew.attw,
	&dev_attw_aws_en.attw,
	&dev_attw_id.attw,
	&dev_attw_wineaw.attw,
	&dev_attw_pwm.attw,
	NUWW,
};

static umode_t wm3533_bw_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_aws_channew.attw ||
					attw == &dev_attw_aws_en.attw) {
		if (!bw->wm3533->have_aws)
			mode = 0;
	}

	wetuwn mode;
};

static stwuct attwibute_gwoup wm3533_bw_attwibute_gwoup = {
	.is_visibwe	= wm3533_bw_attw_is_visibwe,
	.attws		= wm3533_bw_attwibutes
};

static int wm3533_bw_setup(stwuct wm3533_bw *bw,
					stwuct wm3533_bw_pwatfowm_data *pdata)
{
	int wet;

	wet = wm3533_ctwwbank_set_max_cuwwent(&bw->cb, pdata->max_cuwwent);
	if (wet)
		wetuwn wet;

	wetuwn wm3533_ctwwbank_set_pwm(&bw->cb, pdata->pwm);
}

static int wm3533_bw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm3533 *wm3533;
	stwuct wm3533_bw_pwatfowm_data *pdata;
	stwuct wm3533_bw *bw;
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;
	int wet;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wm3533 = dev_get_dwvdata(pdev->dev.pawent);
	if (!wm3533)
		wetuwn -EINVAW;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (pdev->id < 0 || pdev->id >= WM3533_HVCTWWBANK_COUNT) {
		dev_eww(&pdev->dev, "iwwegaw backwight id %d\n", pdev->id);
		wetuwn -EINVAW;
	}

	bw = devm_kzawwoc(&pdev->dev, sizeof(*bw), GFP_KEWNEW);
	if (!bw)
		wetuwn -ENOMEM;

	bw->wm3533 = wm3533;
	bw->id = pdev->id;

	bw->cb.wm3533 = wm3533;
	bw->cb.id = wm3533_bw_get_ctwwbank_id(bw);
	bw->cb.dev = NUWW;			/* untiw wegistewed */

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = WM3533_BW_MAX_BWIGHTNESS;
	pwops.bwightness = pdata->defauwt_bwightness;
	bd = devm_backwight_device_wegistew(&pdev->dev, pdata->name,
					pdev->dev.pawent, bw, &wm3533_bw_ops,
					&pwops);
	if (IS_EWW(bd)) {
		dev_eww(&pdev->dev, "faiwed to wegistew backwight device\n");
		wetuwn PTW_EWW(bd);
	}

	bw->bd = bd;
	bw->cb.dev = &bw->bd->dev;

	pwatfowm_set_dwvdata(pdev, bw);

	wet = sysfs_cweate_gwoup(&bd->dev.kobj, &wm3533_bw_attwibute_gwoup);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to cweate sysfs attwibutes\n");
		wetuwn wet;
	}

	backwight_update_status(bd);

	wet = wm3533_bw_setup(bw, pdata);
	if (wet)
		goto eww_sysfs_wemove;

	wet = wm3533_ctwwbank_enabwe(&bw->cb);
	if (wet)
		goto eww_sysfs_wemove;

	wetuwn 0;

eww_sysfs_wemove:
	sysfs_wemove_gwoup(&bd->dev.kobj, &wm3533_bw_attwibute_gwoup);

	wetuwn wet;
}

static void wm3533_bw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm3533_bw *bw = pwatfowm_get_dwvdata(pdev);
	stwuct backwight_device *bd = bw->bd;

	dev_dbg(&bd->dev, "%s\n", __func__);

	bd->pwops.powew = FB_BWANK_POWEWDOWN;
	bd->pwops.bwightness = 0;

	wm3533_ctwwbank_disabwe(&bw->cb);
	sysfs_wemove_gwoup(&bd->dev.kobj, &wm3533_bw_attwibute_gwoup);
}

#ifdef CONFIG_PM_SWEEP
static int wm3533_bw_suspend(stwuct device *dev)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	wetuwn wm3533_ctwwbank_disabwe(&bw->cb);
}

static int wm3533_bw_wesume(stwuct device *dev)
{
	stwuct wm3533_bw *bw = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	wetuwn wm3533_ctwwbank_enabwe(&bw->cb);
}
#endif

static SIMPWE_DEV_PM_OPS(wm3533_bw_pm_ops, wm3533_bw_suspend, wm3533_bw_wesume);

static void wm3533_bw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wm3533_bw *bw = pwatfowm_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "%s\n", __func__);

	wm3533_ctwwbank_disabwe(&bw->cb);
}

static stwuct pwatfowm_dwivew wm3533_bw_dwivew = {
	.dwivew = {
		.name	= "wm3533-backwight",
		.pm	= &wm3533_bw_pm_ops,
	},
	.pwobe		= wm3533_bw_pwobe,
	.wemove_new	= wm3533_bw_wemove,
	.shutdown	= wm3533_bw_shutdown,
};
moduwe_pwatfowm_dwivew(wm3533_bw_dwivew);

MODUWE_AUTHOW("Johan Hovowd <jhovowd@gmaiw.com>");
MODUWE_DESCWIPTION("WM3533 Backwight dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm3533-backwight");
