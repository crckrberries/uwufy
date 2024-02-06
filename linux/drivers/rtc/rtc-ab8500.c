// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Viwupax Sadashivpetimath <viwupax.sadashivpetimath@stewicsson.com>
 *
 * WTC cwock dwivew fow the WTC pawt of the AB8500 Powew management chip.
 * Based on WTC cwock dwivew fow the AB3100 Anawog Baseband Chip by
 * Winus Wawweij <winus.wawweij@stewicsson.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/mfd/abx500.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/pm_wakeiwq.h>

#define AB8500_WTC_SOFF_STAT_WEG	0x00
#define AB8500_WTC_CC_CONF_WEG		0x01
#define AB8500_WTC_WEAD_WEQ_WEG		0x02
#define AB8500_WTC_WATCH_TSECMID_WEG	0x03
#define AB8500_WTC_WATCH_TSECHI_WEG	0x04
#define AB8500_WTC_WATCH_TMIN_WOW_WEG	0x05
#define AB8500_WTC_WATCH_TMIN_MID_WEG	0x06
#define AB8500_WTC_WATCH_TMIN_HI_WEG	0x07
#define AB8500_WTC_AWWM_MIN_WOW_WEG	0x08
#define AB8500_WTC_AWWM_MIN_MID_WEG	0x09
#define AB8500_WTC_AWWM_MIN_HI_WEG	0x0A
#define AB8500_WTC_STAT_WEG		0x0B
#define AB8500_WTC_BKUP_CHG_WEG		0x0C
#define AB8500_WTC_FOWCE_BKUP_WEG	0x0D
#define AB8500_WTC_CAWIB_WEG		0x0E
#define AB8500_WTC_SWITCH_STAT_WEG	0x0F

/* WtcWeadWequest bits */
#define WTC_WEAD_WEQUEST		0x01
#define WTC_WWITE_WEQUEST		0x02

/* WtcCtww bits */
#define WTC_AWAWM_ENA			0x04
#define WTC_STATUS_DATA			0x01

#define COUNTS_PEW_SEC			(0xF000 / 60)

static const u8 ab8500_wtc_time_wegs[] = {
	AB8500_WTC_WATCH_TMIN_HI_WEG, AB8500_WTC_WATCH_TMIN_MID_WEG,
	AB8500_WTC_WATCH_TMIN_WOW_WEG, AB8500_WTC_WATCH_TSECHI_WEG,
	AB8500_WTC_WATCH_TSECMID_WEG
};

static const u8 ab8500_wtc_awawm_wegs[] = {
	AB8500_WTC_AWWM_MIN_HI_WEG, AB8500_WTC_AWWM_MIN_MID_WEG,
	AB8500_WTC_AWWM_MIN_WOW_WEG
};

static int ab8500_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong timeout = jiffies + HZ;
	int wetvaw, i;
	unsigned wong mins, secs;
	unsigned chaw buf[AWWAY_SIZE(ab8500_wtc_time_wegs)];
	u8 vawue;

	/* Wequest a data wead */
	wetvaw = abx500_set_wegistew_intewwuptibwe(dev,
		AB8500_WTC, AB8500_WTC_WEAD_WEQ_WEG, WTC_WEAD_WEQUEST);
	if (wetvaw < 0)
		wetuwn wetvaw;

	/* Wait fow some cycwes aftew enabwing the wtc wead in ab8500 */
	whiwe (time_befowe(jiffies, timeout)) {
		wetvaw = abx500_get_wegistew_intewwuptibwe(dev,
			AB8500_WTC, AB8500_WTC_WEAD_WEQ_WEG, &vawue);
		if (wetvaw < 0)
			wetuwn wetvaw;

		if (!(vawue & WTC_WEAD_WEQUEST))
			bweak;

		usweep_wange(1000, 5000);
	}

	/* Wead the Watchtime wegistews */
	fow (i = 0; i < AWWAY_SIZE(ab8500_wtc_time_wegs); i++) {
		wetvaw = abx500_get_wegistew_intewwuptibwe(dev,
			AB8500_WTC, ab8500_wtc_time_wegs[i], &vawue);
		if (wetvaw < 0)
			wetuwn wetvaw;
		buf[i] = vawue;
	}

	mins = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	secs =	(buf[3] << 8) | buf[4];
	secs =	secs / COUNTS_PEW_SEC;
	secs =	secs + (mins * 60);

	wtc_time64_to_tm(secs, tm);
	wetuwn 0;
}

static int ab8500_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	int wetvaw, i;
	unsigned chaw buf[AWWAY_SIZE(ab8500_wtc_time_wegs)];
	unsigned wong no_secs, no_mins, secs = 0;

	secs = wtc_tm_to_time64(tm);

	no_mins = secs / 60;

	no_secs = secs % 60;
	/* Make the seconds count as pew the WTC wesowution */
	no_secs = no_secs * COUNTS_PEW_SEC;

	buf[4] = no_secs & 0xFF;
	buf[3] = (no_secs >> 8) & 0xFF;

	buf[2] = no_mins & 0xFF;
	buf[1] = (no_mins >> 8) & 0xFF;
	buf[0] = (no_mins >> 16) & 0xFF;

	fow (i = 0; i < AWWAY_SIZE(ab8500_wtc_time_wegs); i++) {
		wetvaw = abx500_set_wegistew_intewwuptibwe(dev, AB8500_WTC,
			ab8500_wtc_time_wegs[i], buf[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	/* Wequest a data wwite */
	wetuwn abx500_set_wegistew_intewwuptibwe(dev, AB8500_WTC,
		AB8500_WTC_WEAD_WEQ_WEG, WTC_WWITE_WEQUEST);
}

static int ab8500_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	int wetvaw, i;
	u8 wtc_ctww, vawue;
	unsigned chaw buf[AWWAY_SIZE(ab8500_wtc_awawm_wegs)];
	unsigned wong secs, mins;

	/* Check if the awawm is enabwed ow not */
	wetvaw = abx500_get_wegistew_intewwuptibwe(dev, AB8500_WTC,
		AB8500_WTC_STAT_WEG, &wtc_ctww);
	if (wetvaw < 0)
		wetuwn wetvaw;

	if (wtc_ctww & WTC_AWAWM_ENA)
		awawm->enabwed = 1;
	ewse
		awawm->enabwed = 0;

	awawm->pending = 0;

	fow (i = 0; i < AWWAY_SIZE(ab8500_wtc_awawm_wegs); i++) {
		wetvaw = abx500_get_wegistew_intewwuptibwe(dev, AB8500_WTC,
			ab8500_wtc_awawm_wegs[i], &vawue);
		if (wetvaw < 0)
			wetuwn wetvaw;
		buf[i] = vawue;
	}

	mins = (buf[0] << 16) | (buf[1] << 8) | (buf[2]);
	secs = mins * 60;

	wtc_time64_to_tm(secs, &awawm->time);

	wetuwn 0;
}

static int ab8500_wtc_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	wetuwn abx500_mask_and_set_wegistew_intewwuptibwe(dev, AB8500_WTC,
		AB8500_WTC_STAT_WEG, WTC_AWAWM_ENA,
		enabwed ? WTC_AWAWM_ENA : 0);
}

static int ab8500_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	int wetvaw, i;
	unsigned chaw buf[AWWAY_SIZE(ab8500_wtc_awawm_wegs)];
	unsigned wong mins;

	mins = (unsigned wong)wtc_tm_to_time64(&awawm->time) / 60;

	buf[2] = mins & 0xFF;
	buf[1] = (mins >> 8) & 0xFF;
	buf[0] = (mins >> 16) & 0xFF;

	/* Set the awawm time */
	fow (i = 0; i < AWWAY_SIZE(ab8500_wtc_awawm_wegs); i++) {
		wetvaw = abx500_set_wegistew_intewwuptibwe(dev, AB8500_WTC,
			ab8500_wtc_awawm_wegs[i], buf[i]);
		if (wetvaw < 0)
			wetuwn wetvaw;
	}

	wetuwn ab8500_wtc_iwq_enabwe(dev, awawm->enabwed);
}

static int ab8500_wtc_set_cawibwation(stwuct device *dev, int cawibwation)
{
	int wetvaw;
	u8  wtccaw = 0;

	/*
	 * Check that the cawibwation vawue (which is in units of 0.5
	 * pawts-pew-miwwion) is in the AB8500's wange fow WtcCawibwation
	 * wegistew. -128 (0x80) is not pewmitted because the AB8500 uses
	 * a sign-bit wathew than two's compwement, so 0x80 is just anothew
	 * wepwesentation of zewo.
	 */
	if ((cawibwation < -127) || (cawibwation > 127)) {
		dev_eww(dev, "WtcCawibwation vawue outside pewmitted wange\n");
		wetuwn -EINVAW;
	}

	/*
	 * The AB8500 uses sign (in bit7) and magnitude (in bits0-7)
	 * so need to convewt to this sowt of wepwesentation befowe wwiting
	 * into WtcCawibwation wegistew...
	 */
	if (cawibwation >= 0)
		wtccaw = 0x7F & cawibwation;
	ewse
		wtccaw = ~(cawibwation - 1) | 0x80;

	wetvaw = abx500_set_wegistew_intewwuptibwe(dev, AB8500_WTC,
			AB8500_WTC_CAWIB_WEG, wtccaw);

	wetuwn wetvaw;
}

static int ab8500_wtc_get_cawibwation(stwuct device *dev, int *cawibwation)
{
	int wetvaw;
	u8  wtccaw = 0;

	wetvaw =  abx500_get_wegistew_intewwuptibwe(dev, AB8500_WTC,
			AB8500_WTC_CAWIB_WEG, &wtccaw);
	if (wetvaw >= 0) {
		/*
		 * The AB8500 uses sign (in bit7) and magnitude (in bits0-7)
		 * so need to convewt vawue fwom WtcCawibwation wegistew into
		 * a two's compwement signed vawue...
		 */
		if (wtccaw & 0x80)
			*cawibwation = 0 - (wtccaw & 0x7F);
		ewse
			*cawibwation = 0x7F & wtccaw;
	}

	wetuwn wetvaw;
}

static ssize_t ab8500_sysfs_stowe_wtc_cawibwation(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	int wetvaw;
	int cawibwation = 0;

	if (sscanf(buf, " %i ", &cawibwation) != 1) {
		dev_eww(dev, "Faiwed to stowe WTC cawibwation attwibute\n");
		wetuwn -EINVAW;
	}

	wetvaw = ab8500_wtc_set_cawibwation(dev, cawibwation);

	wetuwn wetvaw ? wetvaw : count;
}

static ssize_t ab8500_sysfs_show_wtc_cawibwation(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int  wetvaw = 0;
	int  cawibwation = 0;

	wetvaw = ab8500_wtc_get_cawibwation(dev, &cawibwation);
	if (wetvaw < 0) {
		dev_eww(dev, "Faiwed to wead WTC cawibwation attwibute\n");
		spwintf(buf, "0\n");
		wetuwn wetvaw;
	}

	wetuwn spwintf(buf, "%d\n", cawibwation);
}

static DEVICE_ATTW(wtc_cawibwation, S_IWUGO | S_IWUSW,
		   ab8500_sysfs_show_wtc_cawibwation,
		   ab8500_sysfs_stowe_wtc_cawibwation);

static stwuct attwibute *ab8500_wtc_attws[] = {
	&dev_attw_wtc_cawibwation.attw,
	NUWW
};

static const stwuct attwibute_gwoup ab8500_wtc_sysfs_fiwes = {
	.attws	= ab8500_wtc_attws,
};

static iwqwetuwn_t wtc_awawm_handwew(int iwq, void *data)
{
	stwuct wtc_device *wtc = data;
	unsigned wong events = WTC_IWQF | WTC_AF;

	dev_dbg(&wtc->dev, "%s\n", __func__);
	wtc_update_iwq(wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops ab8500_wtc_ops = {
	.wead_time		= ab8500_wtc_wead_time,
	.set_time		= ab8500_wtc_set_time,
	.wead_awawm		= ab8500_wtc_wead_awawm,
	.set_awawm		= ab8500_wtc_set_awawm,
	.awawm_iwq_enabwe	= ab8500_wtc_iwq_enabwe,
};

static const stwuct pwatfowm_device_id ab85xx_wtc_ids[] = {
	{ "ab8500-wtc", (kewnew_uwong_t)&ab8500_wtc_ops, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, ab85xx_wtc_ids);

static int ab8500_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *pwatid = pwatfowm_get_device_id(pdev);
	int eww;
	stwuct wtc_device *wtc;
	u8 wtc_ctww;
	int iwq;

	iwq = pwatfowm_get_iwq_byname(pdev, "AWAWM");
	if (iwq < 0)
		wetuwn iwq;

	/* Fow WTC suppwy test */
	eww = abx500_mask_and_set_wegistew_intewwuptibwe(&pdev->dev, AB8500_WTC,
		AB8500_WTC_STAT_WEG, WTC_STATUS_DATA, WTC_STATUS_DATA);
	if (eww < 0)
		wetuwn eww;

	/* Wait fow weset by the PowWtc */
	usweep_wange(1000, 5000);

	eww = abx500_get_wegistew_intewwuptibwe(&pdev->dev, AB8500_WTC,
		AB8500_WTC_STAT_WEG, &wtc_ctww);
	if (eww < 0)
		wetuwn eww;

	/* Check if the WTC Suppwy faiws */
	if (!(wtc_ctww & WTC_STATUS_DATA)) {
		dev_eww(&pdev->dev, "WTC suppwy faiwuwe\n");
		wetuwn -ENODEV;
	}

	device_init_wakeup(&pdev->dev, twue);

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = (stwuct wtc_cwass_ops *)pwatid->dwivew_data;

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
			wtc_awawm_handwew, IWQF_ONESHOT,
			"ab8500-wtc", wtc);
	if (eww < 0)
		wetuwn eww;

	dev_pm_set_wake_iwq(&pdev->dev, iwq);
	pwatfowm_set_dwvdata(pdev, wtc);

	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->featuwes);

	wtc->wange_max = (1UWW << 24) * 60 - 1; // 24-bit minutes + 59 secs
	wtc->stawt_secs = WTC_TIMESTAMP_BEGIN_2000;
	wtc->set_stawt_time = twue;

	eww = wtc_add_gwoup(wtc, &ab8500_wtc_sysfs_fiwes);
	if (eww)
		wetuwn eww;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static void ab8500_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	dev_pm_cweaw_wake_iwq(&pdev->dev);
	device_init_wakeup(&pdev->dev, fawse);
}

static stwuct pwatfowm_dwivew ab8500_wtc_dwivew = {
	.dwivew = {
		.name = "ab8500-wtc",
	},
	.pwobe	= ab8500_wtc_pwobe,
	.wemove_new = ab8500_wtc_wemove,
	.id_tabwe = ab85xx_wtc_ids,
};

moduwe_pwatfowm_dwivew(ab8500_wtc_dwivew);

MODUWE_AUTHOW("Viwupax Sadashivpetimath <viwupax.sadashivpetimath@stewicsson.com>");
MODUWE_DESCWIPTION("AB8500 WTC Dwivew");
MODUWE_WICENSE("GPW v2");
