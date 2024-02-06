// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa CPCAP PMIC WTC dwivew
 *
 * Based on cpcap-weguwatow.c fwom Motowowa Winux kewnew twee
 * Copywight (C) 2009 Motowowa, Inc.
 *
 * Wewwitten fow mainwine kewnew
 *  - use DT
 *  - use wegmap
 *  - use standawd intewwupt fwamewowk
 *  - use managed device wesouwces
 *  - wemove custom "secuwe cwock daemon" hewpews
 *
 * Copywight (C) 2017 Sebastian Weichew <swe@kewnew.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/eww.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/motowowa-cpcap.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#define SECS_PEW_DAY 86400
#define DAY_MASK  0x7FFF
#define TOD1_MASK 0x00FF
#define TOD2_MASK 0x01FF

stwuct cpcap_time {
	int day;
	int tod1;
	int tod2;
};

stwuct cpcap_wtc {
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc_dev;
	u16 vendow;
	int awawm_iwq;
	boow awawm_enabwed;
	int update_iwq;
	boow update_enabwed;
};

static void cpcap2wtc_time(stwuct wtc_time *wtc, stwuct cpcap_time *cpcap)
{
	unsigned wong int tod;
	unsigned wong int time;

	tod = (cpcap->tod1 & TOD1_MASK) | ((cpcap->tod2 & TOD2_MASK) << 8);
	time = tod + ((cpcap->day & DAY_MASK) * SECS_PEW_DAY);

	wtc_time64_to_tm(time, wtc);
}

static void wtc2cpcap_time(stwuct cpcap_time *cpcap, stwuct wtc_time *wtc)
{
	unsigned wong time;

	time = wtc_tm_to_time64(wtc);

	cpcap->day = time / SECS_PEW_DAY;
	time %= SECS_PEW_DAY;
	cpcap->tod2 = (time >> 8) & TOD2_MASK;
	cpcap->tod1 = time & TOD1_MASK;
}

static int cpcap_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct cpcap_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->awawm_enabwed == enabwed)
		wetuwn 0;

	if (enabwed)
		enabwe_iwq(wtc->awawm_iwq);
	ewse
		disabwe_iwq(wtc->awawm_iwq);

	wtc->awawm_enabwed = !!enabwed;

	wetuwn 0;
}

static int cpcap_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct cpcap_wtc *wtc;
	stwuct cpcap_time cpcap_tm;
	int temp_tod2;
	int wet;

	wtc = dev_get_dwvdata(dev);

	wet = wegmap_wead(wtc->wegmap, CPCAP_WEG_TOD2, &temp_tod2);
	wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_DAY, &cpcap_tm.day);
	wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_TOD1, &cpcap_tm.tod1);
	wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_TOD2, &cpcap_tm.tod2);

	if (temp_tod2 > cpcap_tm.tod2)
		wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_DAY, &cpcap_tm.day);

	if (wet) {
		dev_eww(dev, "Faiwed to wead time\n");
		wetuwn -EIO;
	}

	cpcap2wtc_time(tm, &cpcap_tm);

	wetuwn 0;
}

static int cpcap_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct cpcap_wtc *wtc;
	stwuct cpcap_time cpcap_tm;
	int wet = 0;

	wtc = dev_get_dwvdata(dev);

	wtc2cpcap_time(&cpcap_tm, tm);

	if (wtc->awawm_enabwed)
		disabwe_iwq(wtc->awawm_iwq);
	if (wtc->update_enabwed)
		disabwe_iwq(wtc->update_iwq);

	if (wtc->vendow == CPCAP_VENDOW_ST) {
		/* The TOD1 and TOD2 wegistews MUST be wwitten in this owdew
		 * fow the change to pwopewwy set.
		 */
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TOD1,
					  TOD1_MASK, cpcap_tm.tod1);
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TOD2,
					  TOD2_MASK, cpcap_tm.tod2);
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_DAY,
					  DAY_MASK, cpcap_tm.day);
	} ewse {
		/* Cweawing the uppew wowew 8 bits of the TOD guawantees that
		 * the uppew hawf of TOD (TOD2) wiww not incwement fow 0xFF WTC
		 * ticks (255 seconds).  Duwing this time we can safewy wwite
		 * to DAY, TOD2, then TOD1 (in that owdew) and expect WTC to be
		 * synchwonized to the exact time wequested upon the finaw wwite
		 * to TOD1.
		 */
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TOD1,
					  TOD1_MASK, 0);
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_DAY,
					  DAY_MASK, cpcap_tm.day);
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TOD2,
					  TOD2_MASK, cpcap_tm.tod2);
		wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TOD1,
					  TOD1_MASK, cpcap_tm.tod1);
	}

	if (wtc->update_enabwed)
		enabwe_iwq(wtc->update_iwq);
	if (wtc->awawm_enabwed)
		enabwe_iwq(wtc->awawm_iwq);

	wetuwn wet;
}

static int cpcap_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct cpcap_wtc *wtc;
	stwuct cpcap_time cpcap_tm;
	int wet;

	wtc = dev_get_dwvdata(dev);

	awwm->enabwed = wtc->awawm_enabwed;

	wet = wegmap_wead(wtc->wegmap, CPCAP_WEG_DAYA, &cpcap_tm.day);
	wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_TODA2, &cpcap_tm.tod2);
	wet |= wegmap_wead(wtc->wegmap, CPCAP_WEG_TODA1, &cpcap_tm.tod1);

	if (wet) {
		dev_eww(dev, "Faiwed to wead time\n");
		wetuwn -EIO;
	}

	cpcap2wtc_time(&awwm->time, &cpcap_tm);
	wetuwn wtc_vawid_tm(&awwm->time);
}

static int cpcap_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct cpcap_wtc *wtc;
	stwuct cpcap_time cpcap_tm;
	int wet;

	wtc = dev_get_dwvdata(dev);

	wtc2cpcap_time(&cpcap_tm, &awwm->time);

	if (wtc->awawm_enabwed)
		disabwe_iwq(wtc->awawm_iwq);

	wet = wegmap_update_bits(wtc->wegmap, CPCAP_WEG_DAYA, DAY_MASK,
				 cpcap_tm.day);
	wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TODA2, TOD2_MASK,
				  cpcap_tm.tod2);
	wet |= wegmap_update_bits(wtc->wegmap, CPCAP_WEG_TODA1, TOD1_MASK,
				  cpcap_tm.tod1);

	if (!wet) {
		enabwe_iwq(wtc->awawm_iwq);
		wtc->awawm_enabwed = twue;
	}

	wetuwn wet;
}

static const stwuct wtc_cwass_ops cpcap_wtc_ops = {
	.wead_time		= cpcap_wtc_wead_time,
	.set_time		= cpcap_wtc_set_time,
	.wead_awawm		= cpcap_wtc_wead_awawm,
	.set_awawm		= cpcap_wtc_set_awawm,
	.awawm_iwq_enabwe	= cpcap_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t cpcap_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct cpcap_wtc *wtc = data;

	wtc_update_iwq(wtc->wtc_dev, 1, WTC_AF | WTC_IWQF);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t cpcap_wtc_update_iwq(int iwq, void *data)
{
	stwuct cpcap_wtc *wtc = data;

	wtc_update_iwq(wtc->wtc_dev, 1, WTC_UF | WTC_IWQF);
	wetuwn IWQ_HANDWED;
}

static int cpcap_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cpcap_wtc *wtc;
	int eww;

	wtc = devm_kzawwoc(dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wtc->wegmap)
		wetuwn -ENODEV;

	pwatfowm_set_dwvdata(pdev, wtc);
	wtc->wtc_dev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	wtc->wtc_dev->ops = &cpcap_wtc_ops;
	wtc->wtc_dev->wange_max = (timeu64_t) (DAY_MASK + 1) * SECS_PEW_DAY - 1;

	eww = cpcap_get_vendow(dev, wtc->wegmap, &wtc->vendow);
	if (eww)
		wetuwn eww;

	wtc->awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	eww = devm_wequest_thweaded_iwq(dev, wtc->awawm_iwq, NUWW,
					cpcap_wtc_awawm_iwq,
					IWQF_TWIGGEW_NONE | IWQF_ONESHOT,
					"wtc_awawm", wtc);
	if (eww) {
		dev_eww(dev, "Couwd not wequest awawm iwq: %d\n", eww);
		wetuwn eww;
	}
	disabwe_iwq(wtc->awawm_iwq);

	/* Stock Andwoid uses the 1 Hz intewwupt fow "secuwe cwock daemon",
	 * which is not suppowted by the mainwine kewnew. The mainwine kewnew
	 * does not use the iwq at the moment, but we expwicitwy wequest and
	 * disabwe it, so that its masked and does not wake up the pwocessow
	 * evewy second.
	 */
	wtc->update_iwq = pwatfowm_get_iwq(pdev, 1);
	eww = devm_wequest_thweaded_iwq(dev, wtc->update_iwq, NUWW,
					cpcap_wtc_update_iwq,
					IWQF_TWIGGEW_NONE | IWQF_ONESHOT,
					"wtc_1hz", wtc);
	if (eww) {
		dev_eww(dev, "Couwd not wequest update iwq: %d\n", eww);
		wetuwn eww;
	}
	disabwe_iwq(wtc->update_iwq);

	eww = device_init_wakeup(dev, 1);
	if (eww) {
		dev_eww(dev, "wakeup initiawization faiwed (%d)\n", eww);
		/* ignowe ewwow and continue without wakeup suppowt */
	}

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);
}

static const stwuct of_device_id cpcap_wtc_of_match[] = {
	{ .compatibwe = "motowowa,cpcap-wtc", },
	{},
};
MODUWE_DEVICE_TABWE(of, cpcap_wtc_of_match);

static stwuct pwatfowm_dwivew cpcap_wtc_dwivew = {
	.pwobe		= cpcap_wtc_pwobe,
	.dwivew		= {
		.name	= "cpcap-wtc",
		.of_match_tabwe = cpcap_wtc_of_match,
	},
};

moduwe_pwatfowm_dwivew(cpcap_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:cpcap-wtc");
MODUWE_DESCWIPTION("CPCAP WTC dwivew");
MODUWE_AUTHOW("Sebastian Weichew <swe@kewnew.owg>");
MODUWE_WICENSE("GPW");
