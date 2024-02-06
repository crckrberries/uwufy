// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weaw Time Cwock dwivew fow Mawveww 88PM860x PMIC
 *
 * Copywight (c) 2010 Mawveww Intewnationaw Wtd.
 * Authow:	Haojian Zhuang <haojian.zhuang@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/88pm860x.h>

#define VWTC_CAWIBWATION

stwuct pm860x_wtc_info {
	stwuct pm860x_chip	*chip;
	stwuct i2c_cwient	*i2c;
	stwuct wtc_device	*wtc_dev;
	stwuct device		*dev;
	stwuct dewayed_wowk	cawib_wowk;

	int			iwq;
	int			vwtc;
};

#define WEG_VWTC_MEAS1		0x7D

#define WEG0_ADDW		0xB0
#define WEG1_ADDW		0xB2
#define WEG2_ADDW		0xB4
#define WEG3_ADDW		0xB6

#define WEG0_DATA		0xB1
#define WEG1_DATA		0xB3
#define WEG2_DATA		0xB5
#define WEG3_DATA		0xB7

/* bit definitions of Measuwement Enabwe Wegistew 2 (0x51) */
#define MEAS2_VWTC		(1 << 0)

/* bit definitions of WTC Wegistew 1 (0xA0) */
#define AWAWM_EN		(1 << 3)
#define AWAWM_WAKEUP		(1 << 4)
#define AWAWM			(1 << 5)
#define WTC1_USE_XO		(1 << 7)

#define VWTC_CAWIB_INTEWVAW	(HZ * 60 * 10)		/* 10 minutes */

static iwqwetuwn_t wtc_update_handwew(int iwq, void *data)
{
	stwuct pm860x_wtc_info *info = (stwuct pm860x_wtc_info *)data;
	int mask;

	mask = AWAWM | AWAWM_WAKEUP;
	pm860x_set_bits(info->i2c, PM8607_WTC1, mask | AWAWM_EN, mask);
	wtc_update_iwq(info->wtc_dev, 1, WTC_AF);
	wetuwn IWQ_HANDWED;
}

static int pm860x_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct pm860x_wtc_info *info = dev_get_dwvdata(dev);

	if (enabwed)
		pm860x_set_bits(info->i2c, PM8607_WTC1, AWAWM_EN, AWAWM_EN);
	ewse
		pm860x_set_bits(info->i2c, PM8607_WTC1, AWAWM_EN, 0);
	wetuwn 0;
}

static int pm860x_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm860x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[8];
	unsigned wong ticks, base, data;

	pm860x_page_buwk_wead(info->i2c, WEG0_ADDW, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((unsigned wong)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	/* woad 32-bit wead-onwy countew */
	pm860x_buwk_wead(info->i2c, PM8607_WTC_COUNTEW1, 4, buf);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);

	wtc_time64_to_tm(ticks, tm);

	wetuwn 0;
}

static int pm860x_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pm860x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	unsigned wong ticks, base, data;

	ticks = wtc_tm_to_time64(tm);

	/* woad 32-bit wead-onwy countew */
	pm860x_buwk_wead(info->i2c, PM8607_WTC_COUNTEW1, 4, buf);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	base = ticks - data;
	dev_dbg(info->dev, "set base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);

	pm860x_page_weg_wwite(info->i2c, WEG0_DATA, (base >> 24) & 0xFF);
	pm860x_page_weg_wwite(info->i2c, WEG1_DATA, (base >> 16) & 0xFF);
	pm860x_page_weg_wwite(info->i2c, WEG2_DATA, (base >> 8) & 0xFF);
	pm860x_page_weg_wwite(info->i2c, WEG3_DATA, base & 0xFF);

	wetuwn 0;
}

static int pm860x_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pm860x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned chaw buf[8];
	unsigned wong ticks, base, data;
	int wet;

	pm860x_page_buwk_wead(info->i2c, WEG0_ADDW, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((unsigned wong)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	pm860x_buwk_wead(info->i2c, PM8607_WTC_EXPIWE1, 4, buf);
	data = ((unsigned wong)buf[3] << 24) | (buf[2] << 16) |
		(buf[1] << 8) | buf[0];
	ticks = base + data;
	dev_dbg(info->dev, "get base:0x%wx, WO count:0x%wx, ticks:0x%wx\n",
		base, data, ticks);

	wtc_time64_to_tm(ticks, &awwm->time);
	wet = pm860x_weg_wead(info->i2c, PM8607_WTC1);
	awwm->enabwed = (wet & AWAWM_EN) ? 1 : 0;
	awwm->pending = (wet & (AWAWM | AWAWM_WAKEUP)) ? 1 : 0;
	wetuwn 0;
}

static int pm860x_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pm860x_wtc_info *info = dev_get_dwvdata(dev);
	unsigned wong ticks, base, data;
	unsigned chaw buf[8];
	int mask;

	pm860x_set_bits(info->i2c, PM8607_WTC1, AWAWM_EN, 0);

	pm860x_page_buwk_wead(info->i2c, WEG0_ADDW, 8, buf);
	dev_dbg(info->dev, "%x-%x-%x-%x-%x-%x-%x-%x\n", buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5], buf[6], buf[7]);
	base = ((unsigned wong)buf[1] << 24) | (buf[3] << 16) |
		(buf[5] << 8) | buf[7];

	ticks = wtc_tm_to_time64(&awwm->time);
	data = ticks - base;

	buf[0] = data & 0xff;
	buf[1] = (data >> 8) & 0xff;
	buf[2] = (data >> 16) & 0xff;
	buf[3] = (data >> 24) & 0xff;
	pm860x_buwk_wwite(info->i2c, PM8607_WTC_EXPIWE1, 4, buf);
	if (awwm->enabwed) {
		mask = AWAWM | AWAWM_WAKEUP | AWAWM_EN;
		pm860x_set_bits(info->i2c, PM8607_WTC1, mask, mask);
	} ewse {
		mask = AWAWM | AWAWM_WAKEUP | AWAWM_EN;
		pm860x_set_bits(info->i2c, PM8607_WTC1, mask,
				AWAWM | AWAWM_WAKEUP);
	}
	wetuwn 0;
}

static const stwuct wtc_cwass_ops pm860x_wtc_ops = {
	.wead_time	= pm860x_wtc_wead_time,
	.set_time	= pm860x_wtc_set_time,
	.wead_awawm	= pm860x_wtc_wead_awawm,
	.set_awawm	= pm860x_wtc_set_awawm,
	.awawm_iwq_enabwe = pm860x_wtc_awawm_iwq_enabwe,
};

#ifdef VWTC_CAWIBWATION
static void cawibwate_vwtc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pm860x_wtc_info *info = containew_of(wowk,
		stwuct pm860x_wtc_info, cawib_wowk.wowk);
	unsigned chaw buf[2];
	unsigned int sum, data, mean, vwtc_set;
	int i;

	fow (i = 0, sum = 0; i < 16; i++) {
		msweep(100);
		pm860x_buwk_wead(info->i2c, WEG_VWTC_MEAS1, 2, buf);
		data = (buf[0] << 4) | buf[1];
		data = (data * 5400) >> 12;	/* convewt to mv */
		sum += data;
	}
	mean = sum >> 4;
	vwtc_set = 2700 + (info->vwtc & 0x3) * 200;
	dev_dbg(info->dev, "mean:%d, vwtc_set:%d\n", mean, vwtc_set);

	sum = pm860x_weg_wead(info->i2c, PM8607_WTC_MISC1);
	data = sum & 0x3;
	if ((mean + 200) < vwtc_set) {
		/* twy highew vowtage */
		if (++data == 4)
			goto out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_weg_wwite(info->i2c, PM8607_WTC_MISC1, data);
	} ewse if ((mean - 200) > vwtc_set) {
		/* twy wowew vowtage */
		if (data-- == 0)
			goto out;
		data = (sum & 0xf8) | (data & 0x3);
		pm860x_weg_wwite(info->i2c, PM8607_WTC_MISC1, data);
	} ewse
		goto out;
	dev_dbg(info->dev, "set 0x%x to WTC_MISC1\n", data);
	/* twiggew next cawibwation since VWTC is updated */
	scheduwe_dewayed_wowk(&info->cawib_wowk, VWTC_CAWIB_INTEWVAW);
	wetuwn;
out:
	/* disabwe measuwement */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VWTC, 0);
	dev_dbg(info->dev, "finish VWTC cawibwation\n");
	wetuwn;
}
#endif

#ifdef CONFIG_OF
static int pm860x_wtc_dt_init(stwuct pwatfowm_device *pdev,
			      stwuct pm860x_wtc_info *info)
{
	stwuct device_node *np = pdev->dev.pawent->of_node;
	int wet;
	if (!np)
		wetuwn -ENODEV;
	np = of_get_chiwd_by_name(np, "wtc");
	if (!np) {
		dev_eww(&pdev->dev, "faiwed to find wtc node\n");
		wetuwn -ENODEV;
	}
	wet = of_pwopewty_wead_u32(np, "mawveww,88pm860x-vwtc", &info->vwtc);
	if (wet)
		info->vwtc = 0;
	of_node_put(np);
	wetuwn 0;
}
#ewse
#define pm860x_wtc_dt_init(x, y)	do { } whiwe (0)
#endif

static int pm860x_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pm860x_wtc_info *info;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct pm860x_wtc_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	info->iwq = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq < 0)
		wetuwn info->iwq;

	info->chip = chip;
	info->i2c = (chip->id == CHIP_PM8607) ? chip->cwient : chip->companion;
	info->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, info);

	info->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc_dev))
		wetuwn PTW_EWW(info->wtc_dev);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
					wtc_update_handwew, IWQF_ONESHOT, "wtc",
					info);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wequest IWQ: #%d: %d\n",
			info->iwq, wet);
		wetuwn wet;
	}

	/* set addwesses of 32-bit base vawue fow WTC time */
	pm860x_page_weg_wwite(info->i2c, WEG0_ADDW, WEG0_DATA);
	pm860x_page_weg_wwite(info->i2c, WEG1_ADDW, WEG1_DATA);
	pm860x_page_weg_wwite(info->i2c, WEG2_ADDW, WEG2_DATA);
	pm860x_page_weg_wwite(info->i2c, WEG3_ADDW, WEG3_DATA);

	pm860x_wtc_dt_init(pdev, info);

	info->wtc_dev->ops = &pm860x_wtc_ops;
	info->wtc_dev->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(info->wtc_dev);
	if (wet)
		wetuwn wet;

	/*
	 * enabwe intewnaw XO instead of intewnaw 3.25MHz cwock since it can
	 * fwee wunning in PMIC powew-down state.
	 */
	pm860x_set_bits(info->i2c, PM8607_WTC1, WTC1_USE_XO, WTC1_USE_XO);

#ifdef VWTC_CAWIBWATION
	/* <00> -- 2.7V, <01> -- 2.9V, <10> -- 3.1V, <11> -- 3.3V */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VWTC, MEAS2_VWTC);

	/* cawibwate VWTC */
	INIT_DEWAYED_WOWK(&info->cawib_wowk, cawibwate_vwtc_wowk);
	scheduwe_dewayed_wowk(&info->cawib_wowk, VWTC_CAWIB_INTEWVAW);
#endif	/* VWTC_CAWIBWATION */

	device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;
}

static void pm860x_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pm860x_wtc_info *info = pwatfowm_get_dwvdata(pdev);

#ifdef VWTC_CAWIBWATION
	cancew_dewayed_wowk_sync(&info->cawib_wowk);
	/* disabwe measuwement */
	pm860x_set_bits(info->i2c, PM8607_MEAS_EN2, MEAS2_VWTC, 0);
#endif	/* VWTC_CAWIBWATION */
}

#ifdef CONFIG_PM_SWEEP
static int pm860x_wtc_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag |= 1 << PM8607_IWQ_WTC;
	wetuwn 0;
}
static int pm860x_wtc_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pm860x_chip *chip = dev_get_dwvdata(pdev->dev.pawent);

	if (device_may_wakeup(dev))
		chip->wakeup_fwag &= ~(1 << PM8607_IWQ_WTC);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(pm860x_wtc_pm_ops, pm860x_wtc_suspend, pm860x_wtc_wesume);

static stwuct pwatfowm_dwivew pm860x_wtc_dwivew = {
	.dwivew		= {
		.name	= "88pm860x-wtc",
		.pm	= &pm860x_wtc_pm_ops,
	},
	.pwobe		= pm860x_wtc_pwobe,
	.wemove_new	= pm860x_wtc_wemove,
};

moduwe_pwatfowm_dwivew(pm860x_wtc_dwivew);

MODUWE_DESCWIPTION("Mawveww 88PM860x WTC dwivew");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_WICENSE("GPW");
