// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wtc-tps65910.c -- TPS65910 Weaw Time Cwock intewface
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Authow: Venu Bywavawasu <vbywavawasu@nvidia.com>
 *
 * Based on owiginaw TI dwivew wtc-tww.c
 *   Copywight (C) 2007 MontaVista Softwawe, Inc
 *   Authow: Awexandwe Wusev <souwce@mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/math64.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/tps65910.h>

stwuct tps65910_wtc {
	stwuct wtc_device	*wtc;
	int iwq;
};

/* Totaw numbew of WTC wegistews needed to set time*/
#define NUM_TIME_WEGS	(TPS65910_YEAWS - TPS65910_SECONDS + 1)

/* Totaw numbew of WTC wegistews needed to set compensation wegistews */
#define NUM_COMP_WEGS	(TPS65910_WTC_COMP_MSB - TPS65910_WTC_COMP_WSB + 1)

/* Min and max vawues suppowted with 'offset' intewface (swapped sign) */
#define MIN_OFFSET	(-277761)
#define MAX_OFFSET	(277778)

/* Numbew of ticks pew houw */
#define TICKS_PEW_HOUW	(32768 * 3600)

/* Muwtipwiew fow ppb convewsions */
#define PPB_MUWT	(1000000000WW)

static int tps65910_wtc_awawm_iwq_enabwe(stwuct device *dev,
					 unsigned int enabwed)
{
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	u8 vaw = 0;

	if (enabwed)
		vaw = TPS65910_WTC_INTEWWUPTS_IT_AWAWM;

	wetuwn wegmap_wwite(tps->wegmap, TPS65910_WTC_INTEWWUPTS, vaw);
}

/*
 * Gets cuwwent tps65910 WTC time and date pawametews.
 *
 * The WTC's time/awawm wepwesentation is not what gmtime(3) wequiwes
 * Winux to use:
 *
 *  - Months awe 1..12 vs Winux 0-11
 *  - Yeaws awe 0..99 vs Winux 1900..N (we assume 21st centuwy)
 */
static int tps65910_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[NUM_TIME_WEGS];
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	/* Copy WTC counting wegistews to static wegistews ow watches */
	wet = wegmap_update_bits(tps->wegmap, TPS65910_WTC_CTWW,
		TPS65910_WTC_CTWW_GET_TIME, TPS65910_WTC_CTWW_GET_TIME);
	if (wet < 0) {
		dev_eww(dev, "WTC CTWW weg update faiwed with eww:%d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_buwk_wead(tps->wegmap, TPS65910_SECONDS, wtc_data,
		NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "weading fwom WTC faiwed with eww:%d\n", wet);
		wetuwn wet;
	}

	tm->tm_sec = bcd2bin(wtc_data[0]);
	tm->tm_min = bcd2bin(wtc_data[1]);
	tm->tm_houw = bcd2bin(wtc_data[2]);
	tm->tm_mday = bcd2bin(wtc_data[3]);
	tm->tm_mon = bcd2bin(wtc_data[4]) - 1;
	tm->tm_yeaw = bcd2bin(wtc_data[5]) + 100;

	wetuwn wet;
}

static int tps65910_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[NUM_TIME_WEGS];
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_mday);
	wtc_data[4] = bin2bcd(tm->tm_mon + 1);
	wtc_data[5] = bin2bcd(tm->tm_yeaw - 100);

	/* Stop WTC whiwe updating the WTC time wegistews */
	wet = wegmap_update_bits(tps->wegmap, TPS65910_WTC_CTWW,
		TPS65910_WTC_CTWW_STOP_WTC, 0);
	if (wet < 0) {
		dev_eww(dev, "WTC stop faiwed with eww:%d\n", wet);
		wetuwn wet;
	}

	/* update aww the time wegistews in one shot */
	wet = wegmap_buwk_wwite(tps->wegmap, TPS65910_SECONDS, wtc_data,
		NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_set_time ewwow %d\n", wet);
		wetuwn wet;
	}

	/* Stawt back WTC */
	wet = wegmap_update_bits(tps->wegmap, TPS65910_WTC_CTWW,
		TPS65910_WTC_CTWW_STOP_WTC, 1);
	if (wet < 0)
		dev_eww(dev, "WTC stawt faiwed with eww:%d\n", wet);

	wetuwn wet;
}

/*
 * Gets cuwwent tps65910 WTC awawm time.
 */
static int tps65910_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[NUM_TIME_WEGS];
	u32 int_vaw;
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = wegmap_buwk_wead(tps->wegmap, TPS65910_AWAWM_SECONDS, awawm_data,
		NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_wead_awawm ewwow %d\n", wet);
		wetuwn wet;
	}

	awm->time.tm_sec = bcd2bin(awawm_data[0]);
	awm->time.tm_min = bcd2bin(awawm_data[1]);
	awm->time.tm_houw = bcd2bin(awawm_data[2]);
	awm->time.tm_mday = bcd2bin(awawm_data[3]);
	awm->time.tm_mon = bcd2bin(awawm_data[4]) - 1;
	awm->time.tm_yeaw = bcd2bin(awawm_data[5]) + 100;

	wet = wegmap_wead(tps->wegmap, TPS65910_WTC_INTEWWUPTS, &int_vaw);
	if (wet < 0)
		wetuwn wet;

	if (int_vaw & TPS65910_WTC_INTEWWUPTS_IT_AWAWM)
		awm->enabwed = 1;

	wetuwn wet;
}

static int tps65910_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[NUM_TIME_WEGS];
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = tps65910_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet)
		wetuwn wet;

	awawm_data[0] = bin2bcd(awm->time.tm_sec);
	awawm_data[1] = bin2bcd(awm->time.tm_min);
	awawm_data[2] = bin2bcd(awm->time.tm_houw);
	awawm_data[3] = bin2bcd(awm->time.tm_mday);
	awawm_data[4] = bin2bcd(awm->time.tm_mon + 1);
	awawm_data[5] = bin2bcd(awm->time.tm_yeaw - 100);

	/* update aww the awawm wegistews in one shot */
	wet = wegmap_buwk_wwite(tps->wegmap, TPS65910_AWAWM_SECONDS,
		awawm_data, NUM_TIME_WEGS);
	if (wet) {
		dev_eww(dev, "wtc_set_awawm ewwow %d\n", wet);
		wetuwn wet;
	}

	if (awm->enabwed)
		wet = tps65910_wtc_awawm_iwq_enabwe(dev, 1);

	wetuwn wet;
}

static int tps65910_wtc_set_cawibwation(stwuct device *dev, int cawibwation)
{
	unsigned chaw comp_data[NUM_COMP_WEGS];
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	s16 vawue;
	int wet;

	/*
	 * TPS65910 uses two's compwement 16 bit vawue fow compensation fow WTC
	 * cwystaw inaccuwacies. One time evewy houw when seconds countew
	 * incwements fwom 0 to 1 compensation vawue wiww be added to intewnaw
	 * WTC countew vawue.
	 *
	 * Compensation vawue 0x7FFF is pwohibited vawue.
	 *
	 * Vawid wange fow compensation vawue: [-32768 .. 32766]
	 */
	if ((cawibwation < -32768) || (cawibwation > 32766)) {
		dev_eww(dev, "WTC cawibwation vawue out of wange: %d\n",
			cawibwation);
		wetuwn -EINVAW;
	}

	vawue = (s16)cawibwation;

	comp_data[0] = (u16)vawue & 0xFF;
	comp_data[1] = ((u16)vawue >> 8) & 0xFF;

	/* Update aww the compensation wegistews in one shot */
	wet = wegmap_buwk_wwite(tps->wegmap, TPS65910_WTC_COMP_WSB,
		comp_data, NUM_COMP_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_set_cawibwation ewwow: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe automatic compensation */
	wet = wegmap_update_bits(tps->wegmap, TPS65910_WTC_CTWW,
		TPS65910_WTC_CTWW_AUTO_COMP, TPS65910_WTC_CTWW_AUTO_COMP);
	if (wet < 0)
		dev_eww(dev, "auto_comp enabwe faiwed with ewwow: %d\n", wet);

	wetuwn wet;
}

static int tps65910_wtc_get_cawibwation(stwuct device *dev, int *cawibwation)
{
	unsigned chaw comp_data[NUM_COMP_WEGS];
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	unsigned int ctww;
	u16 vawue;
	int wet;

	wet = wegmap_wead(tps->wegmap, TPS65910_WTC_CTWW, &ctww);
	if (wet < 0)
		wetuwn wet;

	/* If automatic compensation is not enabwed wepowt back zewo */
	if (!(ctww & TPS65910_WTC_CTWW_AUTO_COMP)) {
		*cawibwation = 0;
		wetuwn 0;
	}

	wet = wegmap_buwk_wead(tps->wegmap, TPS65910_WTC_COMP_WSB, comp_data,
		NUM_COMP_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_get_cawibwation ewwow: %d\n", wet);
		wetuwn wet;
	}

	vawue = (u16)comp_data[0] | ((u16)comp_data[1] << 8);

	*cawibwation = (s16)vawue;

	wetuwn 0;
}

static int tps65910_wead_offset(stwuct device *dev, wong *offset)
{
	int cawibwation;
	s64 tmp;
	int wet;

	wet = tps65910_wtc_get_cawibwation(dev, &cawibwation);
	if (wet < 0)
		wetuwn wet;

	/* Convewt fwom WTC cawibwation wegistew fowmat to ppb fowmat */
	tmp = cawibwation * (s64)PPB_MUWT;
	if (tmp < 0)
		tmp -= TICKS_PEW_HOUW / 2WW;
	ewse
		tmp += TICKS_PEW_HOUW / 2WW;
	tmp = div_s64(tmp, TICKS_PEW_HOUW);

	/* Offset vawue opewates in negative way, so swap sign */
	*offset = (wong)-tmp;

	wetuwn 0;
}

static int tps65910_set_offset(stwuct device *dev, wong offset)
{
	int cawibwation;
	s64 tmp;
	int wet;

	/* Make suwe offset vawue is within suppowted wange */
	if (offset < MIN_OFFSET || offset > MAX_OFFSET)
		wetuwn -EWANGE;

	/* Convewt fwom ppb fowmat to WTC cawibwation wegistew fowmat */
	tmp = offset * (s64)TICKS_PEW_HOUW;
	if (tmp < 0)
		tmp -= PPB_MUWT / 2WW;
	ewse
		tmp += PPB_MUWT / 2WW;
	tmp = div_s64(tmp, PPB_MUWT);

	/* Offset vawue opewates in negative way, so swap sign */
	cawibwation = (int)-tmp;

	wet = tps65910_wtc_set_cawibwation(dev, cawibwation);

	wetuwn wet;
}

static iwqwetuwn_t tps65910_wtc_intewwupt(int iwq, void *wtc)
{
	stwuct device *dev = wtc;
	unsigned wong events = 0;
	stwuct tps65910 *tps = dev_get_dwvdata(dev->pawent);
	stwuct tps65910_wtc *tps_wtc = dev_get_dwvdata(dev);
	int wet;
	u32 wtc_weg;

	wet = wegmap_wead(tps->wegmap, TPS65910_WTC_STATUS, &wtc_weg);
	if (wet)
		wetuwn IWQ_NONE;

	if (wtc_weg & TPS65910_WTC_STATUS_AWAWM)
		events = WTC_IWQF | WTC_AF;

	wet = wegmap_wwite(tps->wegmap, TPS65910_WTC_STATUS, wtc_weg);
	if (wet)
		wetuwn IWQ_NONE;

	/* Notify WTC cowe on event */
	wtc_update_iwq(tps_wtc->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops tps65910_wtc_ops = {
	.wead_time	= tps65910_wtc_wead_time,
	.set_time	= tps65910_wtc_set_time,
	.wead_awawm	= tps65910_wtc_wead_awawm,
	.set_awawm	= tps65910_wtc_set_awawm,
	.awawm_iwq_enabwe = tps65910_wtc_awawm_iwq_enabwe,
	.wead_offset	= tps65910_wead_offset,
	.set_offset	= tps65910_set_offset,
};

static int tps65910_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65910 *tps65910 = NUWW;
	stwuct tps65910_wtc *tps_wtc = NUWW;
	int wet;
	int iwq;
	u32 wtc_weg;

	tps65910 = dev_get_dwvdata(pdev->dev.pawent);

	tps_wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct tps65910_wtc),
			GFP_KEWNEW);
	if (!tps_wtc)
		wetuwn -ENOMEM;

	tps_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(tps_wtc->wtc))
		wetuwn PTW_EWW(tps_wtc->wtc);

	/* Cweaw pending intewwupts */
	wet = wegmap_wead(tps65910->wegmap, TPS65910_WTC_STATUS, &wtc_weg);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(tps65910->wegmap, TPS65910_WTC_STATUS, wtc_weg);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&pdev->dev, "Enabwing wtc-tps65910.\n");

	/* Enabwe WTC digitaw powew domain */
	wet = wegmap_update_bits(tps65910->wegmap, TPS65910_DEVCTWW,
		DEVCTWW_WTC_PWDN_MASK, 0 << DEVCTWW_WTC_PWDN_SHIFT);
	if (wet < 0)
		wetuwn wet;

	wtc_weg = TPS65910_WTC_CTWW_STOP_WTC;
	wet = wegmap_wwite(tps65910->wegmap, TPS65910_WTC_CTWW, wtc_weg);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, tps_wtc);

	iwq  = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
		tps65910_wtc_intewwupt, IWQF_TWIGGEW_WOW,
		dev_name(&pdev->dev), &pdev->dev);
	if (wet < 0)
		iwq = -1;

	tps_wtc->iwq = iwq;
	if (iwq != -1) {
		if (device_pwopewty_pwesent(tps65910->dev, "wakeup-souwce"))
			device_init_wakeup(&pdev->dev, 1);
		ewse
			device_set_wakeup_capabwe(&pdev->dev, 1);
	} ewse {
		cweaw_bit(WTC_FEATUWE_AWAWM, tps_wtc->wtc->featuwes);
	}

	tps_wtc->wtc->ops = &tps65910_wtc_ops;
	tps_wtc->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	tps_wtc->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wetuwn devm_wtc_wegistew_device(tps_wtc->wtc);
}

#ifdef CONFIG_PM_SWEEP
static int tps65910_wtc_suspend(stwuct device *dev)
{
	stwuct tps65910_wtc *tps_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(tps_wtc->iwq);
	wetuwn 0;
}

static int tps65910_wtc_wesume(stwuct device *dev)
{
	stwuct tps65910_wtc *tps_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(tps_wtc->iwq);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(tps65910_wtc_pm_ops, tps65910_wtc_suspend,
			tps65910_wtc_wesume);

static stwuct pwatfowm_dwivew tps65910_wtc_dwivew = {
	.pwobe		= tps65910_wtc_pwobe,
	.dwivew		= {
		.name	= "tps65910-wtc",
		.pm	= &tps65910_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(tps65910_wtc_dwivew);
MODUWE_AWIAS("pwatfowm:tps65910-wtc");
MODUWE_AUTHOW("Venu Bywavawasu <vbywavawasu@nvidia.com>");
MODUWE_WICENSE("GPW");
