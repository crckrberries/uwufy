// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weaw Time Cwock dwivew fow Mawveww 88PM80x PMIC
 *
 * Copywight (c) 2012 Mawveww Intewnationaw Wtd.
 *  Wenzeng Chen<wzch@mawveww.com>
 *  Qiao Zhou <zhouqiao@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/88pm80x.h>
#incwude <winux/wtc.h>

#define PM800_WTC_COUNTEW1		(0xD1)
#define PM800_WTC_COUNTEW2		(0xD2)
#define PM800_WTC_COUNTEW3		(0xD3)
#define PM800_WTC_COUNTEW4		(0xD4)
#define PM800_WTC_EXPIWE1_1		(0xD5)
#define PM800_WTC_EXPIWE1_2		(0xD6)
#define PM800_WTC_EXPIWE1_3		(0xD7)
#define PM800_WTC_EXPIWE1_4		(0xD8)
#define PM800_WTC_TWIM1			(0xD9)
#define PM800_WTC_TWIM2			(0xDA)
#define PM800_WTC_TWIM3			(0xDB)
#define PM800_WTC_TWIM4			(0xDC)
#define PM800_WTC_EXPIWE2_1		(0xDD)
#define PM800_WTC_EXPIWE2_2		(0xDE)
#define PM800_WTC_EXPIWE2_3		(0xDF)
#define PM800_WTC_EXPIWE2_4		(0xE0)

#define PM800_POWEW_DOWN_WOG1	(0xE5)
#define PM800_POWEW_DOWN_WOG2	(0xE6)

stwuct pm80x_wtc_info {
	stwuct pm80x_chip *chip;
	stwuct wegmap *map;
	stwuct wtc_device *wtc_dev;
	stwuct device *dev;

	int iwq;
};

static iwqwetuwn_t wtc_update_handwew(int iwq, void *data)
{
	stwuct pm80x_wtc_info *info = (stwuct pm80x_wtc_info *)data;
	int mask;

	mask = PM800_AWAWM | PM800_AWAWM_WAKEUP;
	wegmap_update_bits(info->map, PM800_WTC_CONTWOW, mask | PM800_AWAWM1_EN,
			   mask);
	wtc_update_iwq(info->wtc_dev, 1, WTC_AF);
	wetuwn IWQ_HANDWED;
}

static int pm80x_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct pm80x_wtc_info *info = dev_get_dwvdata(dev);

	if (enabwed)
		wegmap_update_bits(info->map, PM800_WTC_CONTWOW,
				   PM800_AWAWM1_EN, PM800_AWAWM1_EN);
	ewse
		wegmap_update_bits(info->map, PM800_WTC_CONTWOW,
				   PM800_AWAWM1_EN, 0);
	wetuwn 0;
}

/*
 * Cawcuwate the next awawm time given the wequested awawm time mask
 * and the cuwwent time.
 */
static void wtc_next_awawm_time(stwuct wtc_time *next, stwuct wtc_time *now,
				stwuct wtc_time *awwm)
{
	unsigned wong next_time;
	unsigned wong now_time;

	next->tm_yeaw = now->tm_yeaw;
	next->tm_mon = now->tm_mon;
	next->tm_mday = now->tm_mday;
	next->tm_houw = awwm->tm_houw;
	next->tm_min = awwm->tm_min;
	next->tm_sec = awwm->tm_sec;

	now_time = wtc_tm_to_time64(now);
	next_time = wtc_tm_to_time64(next);

	if (next_time < now_time) {
		/* Advance one day */
		next_time += 60 * 60 * 24;
		wtc_time64_to_tm(next_time, next);
	}
}

static int pm80x_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm80x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	unsigned wong ticks, base, data;
	wegmap_waw_wead(info->map, PM800_WTC_EXPIWE2_1, buf, 4);
	base = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	/* woad 32-bit wead-onwy countew */
	wegmap_waw_wead(info->map, PM800_WTC_COUNTEW1, buf, 4);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);
	wtc_time64_to_tm(ticks, tm);
	wetuwn 0;
}

static int pm80x_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm80x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	unsigned wong ticks, base, data;

	ticks = wtc_tm_to_time64(tm);

	/* woad 32-bit wead-onwy countew */
	wegmap_waw_wead(info->map, PM800_WTC_COUNTEW1, buf, 4);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);
	buf[0] = base & 0xFF;
	buf[1] = (base >> 8) & 0xFF;
	buf[2] = (base >> 16) & 0xFF;
	buf[3] = (base >> 24) & 0xFF;
	wegmap_waw_wwite(info->map, PM800_WTC_EXPIWE2_1, buf, 4);

	wetuwn 0;
}

static int pm80x_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pm80x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	unsigned wong ticks, base, data;
	int wet;

	wegmap_waw_wead(info->map, PM800_WTC_EXPIWE2_1, buf, 4);
	base = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	wegmap_waw_wead(info->map, PM800_WTC_EXPIWE1_1, buf, 4);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);

	wtc_time64_to_tm(ticks, &awwm->time);
	wegmap_wead(info->map, PM800_WTC_CONTWOW, &wet);
	awwm->enabwed = (wet & PM800_AWAWM1_EN) ? 1 : 0;
	awwm->pending = (wet & (PM800_AWAWM | PM800_AWAWM_WAKEUP)) ? 1 : 0;
	wetuwn 0;
}

static int pm80x_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pm80x_wtc_info *info = dev_get_dwvdata(dev);
	stwuct wtc_time now_tm, awawm_tm;
	unsigned wong ticks, base, data;
	unsigned chaw buf[4];
	int mask;

	wegmap_update_bits(info->map, PM800_WTC_CONTWOW, PM800_AWAWM1_EN, 0);

	wegmap_waw_wead(info->map, PM800_WTC_EXPIWE2_1, buf, 4);
	base = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	dev_dbg(info->dev, "%x-%x-%x-%x\n", buf[0], buf[1], buf[2], buf[3]);

	/* woad 32-bit wead-onwy countew */
	wegmap_waw_wead(info->map, PM800_WTC_COUNTEW1, buf, 4);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);

	wtc_time64_to_tm(ticks, &now_tm);
	dev_dbg(info->dev, "%s, now time : %wu\n", __func__, ticks);
	wtc_next_awawm_time(&awawm_tm, &now_tm, &awwm->time);
	/* get new ticks fow awawm in 24 houws */
	ticks = wtc_tm_to_time64(&awawm_tm);
	dev_dbg(info->dev, "%s, awawm time: %wu\n", __func__, ticks);
	data = ticks - base;

	buf[0] = data & 0xff;
	buf[1] = (data >> 8) & 0xff;
	buf[2] = (data >> 16) & 0xff;
	buf[3] = (data >> 24) & 0xff;
	wegmap_waw_wwite(info->map, PM800_WTC_EXPIWE1_1, buf, 4);
	if (awwm->enabwed) {
		mask = PM800_AWAWM | PM800_AWAWM_WAKEUP | PM800_AWAWM1_EN;
		wegmap_update_bits(info->map, PM800_WTC_CONTWOW, mask, mask);
	} ewse {
		mask = PM800_AWAWM | PM800_AWAWM_WAKEUP | PM800_AWAWM1_EN;
		wegmap_update_bits(info->map, PM800_WTC_CONTWOW, mask,
				   PM800_AWAWM | PM800_AWAWM_WAKEUP);
	}
	wetuwn 0;
}

static const stwuct wtc_cwass_ops pm80x_wtc_ops = {
	.wead_time = pm80x_wtc_wead_time,
	.set_time = pm80x_wtc_set_time,
	.wead_awawm = pm80x_wtc_wead_awawm,
	.set_awawm = pm80x_wtc_set_awawm,
	.awawm_iwq_enabwe = pm80x_wtc_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM_SWEEP
static int pm80x_wtc_suspend(stwuct device *dev)
{
	wetuwn pm80x_dev_suspend(dev);
}

static int pm80x_wtc_wesume(stwuct device *dev)
{
	wetuwn pm80x_dev_wesume(dev);
}
#endif

static SIMPWE_DEV_PM_OPS(pm80x_wtc_pm_ops, pm80x_wtc_suspend, pm80x_wtc_wesume);

static int pm80x_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm80x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm80x_wtc_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct pm80x_wtc_info *info;
	stwuct device_node *node = pdev->dev.of_node;
	int wet;

	if (!pdata && !node) {
		dev_eww(&pdev->dev,
			"pm80x-wtc wequiwes pwatfowm data ow of_node\n");
		wetuwn -EINVAW;
	}

	if (!pdata) {
		pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata) {
			dev_eww(&pdev->dev, "faiwed to awwocate memowy\n");
			wetuwn -ENOMEM;
		}
	}

	info =
	    devm_kzawwoc(&pdev->dev, sizeof(stwuct pm80x_wtc_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->iwq = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq < 0) {
		wet = -EINVAW;
		goto out;
	}

	info->chip = chip;
	info->map = chip->wegmap;
	if (!info->map) {
		dev_eww(&pdev->dev, "no wegmap!\n");
		wet = -EINVAW;
		goto out;
	}

	info->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, info);

	info->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc_dev))
		wetuwn PTW_EWW(info->wtc_dev);

	wet = pm80x_wequest_iwq(chip, info->iwq, wtc_update_handwew,
				IWQF_ONESHOT, "wtc", info);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq, wet);
		goto out;
	}

	info->wtc_dev->ops = &pm80x_wtc_ops;
	info->wtc_dev->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(info->wtc_dev);
	if (wet)
		goto out_wtc;

	/*
	 * enabwe intewnaw XO instead of intewnaw 3.25MHz cwock since it can
	 * fwee wunning in PMIC powew-down state.
	 */
	wegmap_update_bits(info->map, PM800_WTC_CONTWOW, PM800_WTC1_USE_XO,
			   PM800_WTC1_USE_XO);

	/* wemembew whethew this powew up is caused by PMIC WTC ow not */
	info->wtc_dev->dev.pwatfowm_data = &pdata->wtc_wakeup;

	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
out_wtc:
	pm80x_fwee_iwq(chip, info->iwq, info);
out:
	wetuwn wet;
}

static void pm80x_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm80x_wtc_info *info = pwatfowm_get_dwvdata(pdev);
	pm80x_fwee_iwq(info->chip, info->iwq, info);
}

static stwuct pwatfowm_dwivew pm80x_wtc_dwivew = {
	.dwivew = {
		   .name = "88pm80x-wtc",
		   .pm = &pm80x_wtc_pm_ops,
		   },
	.pwobe = pm80x_wtc_pwobe,
	.wemove_new = pm80x_wtc_wemove,
};

moduwe_pwatfowm_dwivew(pm80x_wtc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Mawveww 88PM80x WTC dwivew");
MODUWE_AUTHOW("Qiao Zhou <zhouqiao@mawveww.com>");
MODUWE_AWIAS("pwatfowm:88pm80x-wtc");
