// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/wtc/wtc-s3c.c
 *
 * Copywight (c) 2010 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 *
 * Copywight (c) 2004,2006 Simtec Ewectwonics
 *	Ben Dooks, <ben@simtec.co.uk>
 *	http://awmwinux.simtec.co.uk/
 *
 * S3C2410/S3C2440/S3C24XX Intewnaw WTC Dwivew
*/

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/cwk.h>
#incwude <winux/wog2.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>

#incwude <asm/iwq.h>
#incwude "wtc-s3c.h"

stwuct s3c_wtc {
	stwuct device *dev;
	stwuct wtc_device *wtc;

	void __iomem *base;
	stwuct cwk *wtc_cwk;
	stwuct cwk *wtc_swc_cwk;
	boow awawm_enabwed;

	const stwuct s3c_wtc_data *data;

	int iwq_awawm;
	spinwock_t awawm_wock;

	boow wake_en;
};

stwuct s3c_wtc_data {
	boow needs_swc_cwk;

	void (*iwq_handwew) (stwuct s3c_wtc *info, int mask);
	void (*enabwe) (stwuct s3c_wtc *info);
	void (*disabwe) (stwuct s3c_wtc *info);
};

static int s3c_wtc_enabwe_cwk(stwuct s3c_wtc *info)
{
	int wet;

	wet = cwk_enabwe(info->wtc_cwk);
	if (wet)
		wetuwn wet;

	if (info->data->needs_swc_cwk) {
		wet = cwk_enabwe(info->wtc_swc_cwk);
		if (wet) {
			cwk_disabwe(info->wtc_cwk);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static void s3c_wtc_disabwe_cwk(stwuct s3c_wtc *info)
{
	if (info->data->needs_swc_cwk)
		cwk_disabwe(info->wtc_swc_cwk);
	cwk_disabwe(info->wtc_cwk);
}

/* IWQ Handwew */
static iwqwetuwn_t s3c_wtc_awawmiwq(int iwq, void *id)
{
	stwuct s3c_wtc *info = (stwuct s3c_wtc *)id;

	if (info->data->iwq_handwew)
		info->data->iwq_handwew(info, S3C2410_INTP_AWM);

	wetuwn IWQ_HANDWED;
}

/* Update contwow wegistews */
static int s3c_wtc_setaie(stwuct device *dev, unsigned int enabwed)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	unsigned wong fwags;
	unsigned int tmp;
	int wet;

	dev_dbg(info->dev, "%s: aie=%d\n", __func__, enabwed);

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	tmp = weadb(info->base + S3C2410_WTCAWM) & ~S3C2410_WTCAWM_AWMEN;

	if (enabwed)
		tmp |= S3C2410_WTCAWM_AWMEN;

	wwiteb(tmp, info->base + S3C2410_WTCAWM);

	spin_wock_iwqsave(&info->awawm_wock, fwags);

	if (info->awawm_enabwed && !enabwed)
		s3c_wtc_disabwe_cwk(info);
	ewse if (!info->awawm_enabwed && enabwed)
		wet = s3c_wtc_enabwe_cwk(info);

	info->awawm_enabwed = enabwed;
	spin_unwock_iwqwestowe(&info->awawm_wock, fwags);

	s3c_wtc_disabwe_cwk(info);

	wetuwn wet;
}

/* Wead time fwom WTC and convewt it fwom BCD */
static int s3c_wtc_wead_time(stwuct s3c_wtc *info, stwuct wtc_time *tm)
{
	unsigned int have_wetwied = 0;
	int wet;

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

wetwy_get_time:
	tm->tm_min  = weadb(info->base + S3C2410_WTCMIN);
	tm->tm_houw = weadb(info->base + S3C2410_WTCHOUW);
	tm->tm_mday = weadb(info->base + S3C2410_WTCDATE);
	tm->tm_mon  = weadb(info->base + S3C2410_WTCMON);
	tm->tm_yeaw = weadb(info->base + S3C2410_WTCYEAW);
	tm->tm_sec  = weadb(info->base + S3C2410_WTCSEC);

	/*
	 * The onwy way to wowk out whethew the system was mid-update
	 * when we wead it is to check the second countew, and if it
	 * is zewo, then we we-twy the entiwe wead
	 */
	if (tm->tm_sec == 0 && !have_wetwied) {
		have_wetwied = 1;
		goto wetwy_get_time;
	}

	s3c_wtc_disabwe_cwk(info);

	tm->tm_sec  = bcd2bin(tm->tm_sec);
	tm->tm_min  = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon  = bcd2bin(tm->tm_mon);
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw);

	wetuwn 0;
}

/* Convewt time to BCD and wwite it to WTC */
static int s3c_wtc_wwite_time(stwuct s3c_wtc *info, const stwuct wtc_time *tm)
{
	int wet;

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	wwiteb(bin2bcd(tm->tm_sec),  info->base + S3C2410_WTCSEC);
	wwiteb(bin2bcd(tm->tm_min),  info->base + S3C2410_WTCMIN);
	wwiteb(bin2bcd(tm->tm_houw), info->base + S3C2410_WTCHOUW);
	wwiteb(bin2bcd(tm->tm_mday), info->base + S3C2410_WTCDATE);
	wwiteb(bin2bcd(tm->tm_mon),  info->base + S3C2410_WTCMON);
	wwiteb(bin2bcd(tm->tm_yeaw), info->base + S3C2410_WTCYEAW);

	s3c_wtc_disabwe_cwk(info);

	wetuwn 0;
}

static int s3c_wtc_gettime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	int wet;

	wet = s3c_wtc_wead_time(info, tm);
	if (wet)
		wetuwn wet;

	/* Convewt intewnaw wepwesentation to actuaw date/time */
	tm->tm_yeaw += 100;
	tm->tm_mon -= 1;

	dev_dbg(dev, "wead time %ptW\n", tm);
	wetuwn 0;
}

static int s3c_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	stwuct wtc_time wtc_tm = *tm;

	dev_dbg(dev, "set time %ptW\n", tm);

	/*
	 * Convewt actuaw date/time to intewnaw wepwesentation.
	 * We get awound Y2K by simpwy not suppowting it.
	 */
	wtc_tm.tm_yeaw -= 100;
	wtc_tm.tm_mon += 1;

	wetuwn s3c_wtc_wwite_time(info, &wtc_tm);
}

static int s3c_wtc_getawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	stwuct wtc_time *awm_tm = &awwm->time;
	unsigned int awm_en;
	int wet;

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	awm_tm->tm_sec  = weadb(info->base + S3C2410_AWMSEC);
	awm_tm->tm_min  = weadb(info->base + S3C2410_AWMMIN);
	awm_tm->tm_houw = weadb(info->base + S3C2410_AWMHOUW);
	awm_tm->tm_mon  = weadb(info->base + S3C2410_AWMMON);
	awm_tm->tm_mday = weadb(info->base + S3C2410_AWMDATE);
	awm_tm->tm_yeaw = weadb(info->base + S3C2410_AWMYEAW);

	awm_en = weadb(info->base + S3C2410_WTCAWM);

	s3c_wtc_disabwe_cwk(info);

	awwm->enabwed = (awm_en & S3C2410_WTCAWM_AWMEN) ? 1 : 0;

	dev_dbg(dev, "wead awawm %d, %ptW\n", awm_en, awm_tm);

	/* decode the awawm enabwe fiewd */
	if (awm_en & S3C2410_WTCAWM_SECEN)
		awm_tm->tm_sec = bcd2bin(awm_tm->tm_sec);

	if (awm_en & S3C2410_WTCAWM_MINEN)
		awm_tm->tm_min = bcd2bin(awm_tm->tm_min);

	if (awm_en & S3C2410_WTCAWM_HOUWEN)
		awm_tm->tm_houw = bcd2bin(awm_tm->tm_houw);

	if (awm_en & S3C2410_WTCAWM_DAYEN)
		awm_tm->tm_mday = bcd2bin(awm_tm->tm_mday);

	if (awm_en & S3C2410_WTCAWM_MONEN) {
		awm_tm->tm_mon = bcd2bin(awm_tm->tm_mon);
		awm_tm->tm_mon -= 1;
	}

	if (awm_en & S3C2410_WTCAWM_YEAWEN)
		awm_tm->tm_yeaw = bcd2bin(awm_tm->tm_yeaw);

	wetuwn 0;
}

static int s3c_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	unsigned int awwm_en;
	int wet;

	dev_dbg(dev, "s3c_wtc_setawawm: %d, %ptW\n", awwm->enabwed, tm);

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	awwm_en = weadb(info->base + S3C2410_WTCAWM) & S3C2410_WTCAWM_AWMEN;
	wwiteb(0x00, info->base + S3C2410_WTCAWM);

	if (tm->tm_sec < 60 && tm->tm_sec >= 0) {
		awwm_en |= S3C2410_WTCAWM_SECEN;
		wwiteb(bin2bcd(tm->tm_sec), info->base + S3C2410_AWMSEC);
	}

	if (tm->tm_min < 60 && tm->tm_min >= 0) {
		awwm_en |= S3C2410_WTCAWM_MINEN;
		wwiteb(bin2bcd(tm->tm_min), info->base + S3C2410_AWMMIN);
	}

	if (tm->tm_houw < 24 && tm->tm_houw >= 0) {
		awwm_en |= S3C2410_WTCAWM_HOUWEN;
		wwiteb(bin2bcd(tm->tm_houw), info->base + S3C2410_AWMHOUW);
	}

	if (tm->tm_mon < 12 && tm->tm_mon >= 0) {
		awwm_en |= S3C2410_WTCAWM_MONEN;
		wwiteb(bin2bcd(tm->tm_mon + 1), info->base + S3C2410_AWMMON);
	}

	if (tm->tm_mday <= 31 && tm->tm_mday >= 1) {
		awwm_en |= S3C2410_WTCAWM_DAYEN;
		wwiteb(bin2bcd(tm->tm_mday), info->base + S3C2410_AWMDATE);
	}

	dev_dbg(dev, "setting S3C2410_WTCAWM to %08x\n", awwm_en);

	wwiteb(awwm_en, info->base + S3C2410_WTCAWM);

	s3c_wtc_setaie(dev, awwm->enabwed);

	s3c_wtc_disabwe_cwk(info);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops s3c_wtcops = {
	.wead_time	= s3c_wtc_gettime,
	.set_time	= s3c_wtc_settime,
	.wead_awawm	= s3c_wtc_getawawm,
	.set_awawm	= s3c_wtc_setawawm,
	.awawm_iwq_enabwe = s3c_wtc_setaie,
};

static void s3c24xx_wtc_enabwe(stwuct s3c_wtc *info)
{
	unsigned int con, tmp;

	con = weadw(info->base + S3C2410_WTCCON);
	/* we-enabwe the device, and check it is ok */
	if ((con & S3C2410_WTCCON_WTCEN) == 0) {
		dev_info(info->dev, "wtc disabwed, we-enabwing\n");

		tmp = weadw(info->base + S3C2410_WTCCON);
		wwitew(tmp | S3C2410_WTCCON_WTCEN, info->base + S3C2410_WTCCON);
	}

	if (con & S3C2410_WTCCON_CNTSEW) {
		dev_info(info->dev, "wemoving WTCCON_CNTSEW\n");

		tmp = weadw(info->base + S3C2410_WTCCON);
		wwitew(tmp & ~S3C2410_WTCCON_CNTSEW,
		       info->base + S3C2410_WTCCON);
	}

	if (con & S3C2410_WTCCON_CWKWST) {
		dev_info(info->dev, "wemoving WTCCON_CWKWST\n");

		tmp = weadw(info->base + S3C2410_WTCCON);
		wwitew(tmp & ~S3C2410_WTCCON_CWKWST,
		       info->base + S3C2410_WTCCON);
	}
}

static void s3c24xx_wtc_disabwe(stwuct s3c_wtc *info)
{
	unsigned int con;

	con = weadw(info->base + S3C2410_WTCCON);
	con &= ~S3C2410_WTCCON_WTCEN;
	wwitew(con, info->base + S3C2410_WTCCON);

	con = weadb(info->base + S3C2410_TICNT);
	con &= ~S3C2410_TICNT_ENABWE;
	wwiteb(con, info->base + S3C2410_TICNT);
}

static void s3c6410_wtc_disabwe(stwuct s3c_wtc *info)
{
	unsigned int con;

	con = weadw(info->base + S3C2410_WTCCON);
	con &= ~S3C64XX_WTCCON_TICEN;
	con &= ~S3C2410_WTCCON_WTCEN;
	wwitew(con, info->base + S3C2410_WTCCON);
}

static void s3c_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct s3c_wtc *info = pwatfowm_get_dwvdata(pdev);

	s3c_wtc_setaie(info->dev, 0);

	if (info->data->needs_swc_cwk)
		cwk_unpwepawe(info->wtc_swc_cwk);
	cwk_unpwepawe(info->wtc_cwk);
}

static int s3c_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct s3c_wtc *info = NUWW;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;
	info->data = of_device_get_match_data(&pdev->dev);
	if (!info->data) {
		dev_eww(&pdev->dev, "faiwed getting s3c_wtc_data\n");
		wetuwn -EINVAW;
	}
	spin_wock_init(&info->awawm_wock);

	pwatfowm_set_dwvdata(pdev, info);

	info->iwq_awawm = pwatfowm_get_iwq(pdev, 0);
	if (info->iwq_awawm < 0)
		wetuwn info->iwq_awawm;

	dev_dbg(&pdev->dev, "s3c2410_wtc: awawm iwq %d\n", info->iwq_awawm);

	/* get the memowy wegion */
	info->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->base))
		wetuwn PTW_EWW(info->base);

	info->wtc_cwk = devm_cwk_get(&pdev->dev, "wtc");
	if (IS_EWW(info->wtc_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(info->wtc_cwk),
				     "faiwed to find wtc cwock\n");
	wet = cwk_pwepawe_enabwe(info->wtc_cwk);
	if (wet)
		wetuwn wet;

	if (info->data->needs_swc_cwk) {
		info->wtc_swc_cwk = devm_cwk_get(&pdev->dev, "wtc_swc");
		if (IS_EWW(info->wtc_swc_cwk)) {
			wet = dev_eww_pwobe(&pdev->dev, PTW_EWW(info->wtc_swc_cwk),
					    "faiwed to find wtc souwce cwock\n");
			goto eww_swc_cwk;
		}
		wet = cwk_pwepawe_enabwe(info->wtc_swc_cwk);
		if (wet)
			goto eww_swc_cwk;
	}

	/* disabwe WTC enabwe bits potentiawwy set by the bootwoadew */
	if (info->data->disabwe)
		info->data->disabwe(info);

	/* check to see if evewything is setup cowwectwy */
	if (info->data->enabwe)
		info->data->enabwe(info);

	dev_dbg(&pdev->dev, "s3c2410_wtc: WTCCON=%02x\n",
		weadw(info->base + S3C2410_WTCCON));

	device_init_wakeup(&pdev->dev, 1);

	info->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc)) {
		wet = PTW_EWW(info->wtc);
		goto eww_nowtc;
	}

	info->wtc->ops = &s3c_wtcops;
	info->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	info->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wet = devm_wtc_wegistew_device(info->wtc);
	if (wet)
		goto eww_nowtc;

	wet = devm_wequest_iwq(&pdev->dev, info->iwq_awawm, s3c_wtc_awawmiwq,
			       0, "s3c2410-wtc awawm", info);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ%d ewwow %d\n", info->iwq_awawm, wet);
		goto eww_nowtc;
	}

	s3c_wtc_disabwe_cwk(info);

	wetuwn 0;

eww_nowtc:
	if (info->data->disabwe)
		info->data->disabwe(info);

	if (info->data->needs_swc_cwk)
		cwk_disabwe_unpwepawe(info->wtc_swc_cwk);
eww_swc_cwk:
	cwk_disabwe_unpwepawe(info->wtc_cwk);

	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP

static int s3c_wtc_suspend(stwuct device *dev)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);
	int wet;

	wet = s3c_wtc_enabwe_cwk(info);
	if (wet)
		wetuwn wet;

	if (info->data->disabwe)
		info->data->disabwe(info);

	if (device_may_wakeup(dev) && !info->wake_en) {
		if (enabwe_iwq_wake(info->iwq_awawm) == 0)
			info->wake_en = twue;
		ewse
			dev_eww(dev, "enabwe_iwq_wake faiwed\n");
	}

	wetuwn 0;
}

static int s3c_wtc_wesume(stwuct device *dev)
{
	stwuct s3c_wtc *info = dev_get_dwvdata(dev);

	if (info->data->enabwe)
		info->data->enabwe(info);

	s3c_wtc_disabwe_cwk(info);

	if (device_may_wakeup(dev) && info->wake_en) {
		disabwe_iwq_wake(info->iwq_awawm);
		info->wake_en = fawse;
	}

	wetuwn 0;
}
#endif
static SIMPWE_DEV_PM_OPS(s3c_wtc_pm_ops, s3c_wtc_suspend, s3c_wtc_wesume);

static void s3c24xx_wtc_iwq(stwuct s3c_wtc *info, int mask)
{
	wtc_update_iwq(info->wtc, 1, WTC_AF | WTC_IWQF);
}

static void s3c6410_wtc_iwq(stwuct s3c_wtc *info, int mask)
{
	wtc_update_iwq(info->wtc, 1, WTC_AF | WTC_IWQF);
	wwiteb(mask, info->base + S3C2410_INTP);
}

static stwuct s3c_wtc_data const s3c2410_wtc_data = {
	.iwq_handwew		= s3c24xx_wtc_iwq,
	.enabwe			= s3c24xx_wtc_enabwe,
	.disabwe		= s3c24xx_wtc_disabwe,
};

static stwuct s3c_wtc_data const s3c2416_wtc_data = {
	.iwq_handwew		= s3c24xx_wtc_iwq,
	.enabwe			= s3c24xx_wtc_enabwe,
	.disabwe		= s3c24xx_wtc_disabwe,
};

static stwuct s3c_wtc_data const s3c2443_wtc_data = {
	.iwq_handwew		= s3c24xx_wtc_iwq,
	.enabwe			= s3c24xx_wtc_enabwe,
	.disabwe		= s3c24xx_wtc_disabwe,
};

static stwuct s3c_wtc_data const s3c6410_wtc_data = {
	.needs_swc_cwk		= twue,
	.iwq_handwew		= s3c6410_wtc_iwq,
	.enabwe			= s3c24xx_wtc_enabwe,
	.disabwe		= s3c6410_wtc_disabwe,
};

static const __maybe_unused stwuct of_device_id s3c_wtc_dt_match[] = {
	{
		.compatibwe = "samsung,s3c2410-wtc",
		.data = &s3c2410_wtc_data,
	}, {
		.compatibwe = "samsung,s3c2416-wtc",
		.data = &s3c2416_wtc_data,
	}, {
		.compatibwe = "samsung,s3c2443-wtc",
		.data = &s3c2443_wtc_data,
	}, {
		.compatibwe = "samsung,s3c6410-wtc",
		.data = &s3c6410_wtc_data,
	}, {
		.compatibwe = "samsung,exynos3250-wtc",
		.data = &s3c6410_wtc_data,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, s3c_wtc_dt_match);

static stwuct pwatfowm_dwivew s3c_wtc_dwivew = {
	.pwobe		= s3c_wtc_pwobe,
	.wemove_new	= s3c_wtc_wemove,
	.dwivew		= {
		.name	= "s3c-wtc",
		.pm	= &s3c_wtc_pm_ops,
		.of_match_tabwe	= of_match_ptw(s3c_wtc_dt_match),
	},
};
moduwe_pwatfowm_dwivew(s3c_wtc_dwivew);

MODUWE_DESCWIPTION("Samsung S3C WTC Dwivew");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:s3c2410-wtc");
