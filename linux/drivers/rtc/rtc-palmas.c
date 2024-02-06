// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc-pawmas.c -- Pawmas Weaw Time Cwock dwivew.

 * WTC dwivew fow TI Pawma sewies devices wike TPS65913,
 * TPS65914 powew management IC.
 *
 * Copywight (c) 2012, NVIDIA Cowpowation.
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/bcd.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/types.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

stwuct pawmas_wtc {
	stwuct wtc_device	*wtc;
	stwuct device		*dev;
	unsigned int		iwq;
};

/* Totaw numbew of WTC wegistews needed to set time*/
#define PAWMAS_NUM_TIME_WEGS	(PAWMAS_YEAWS_WEG - PAWMAS_SECONDS_WEG + 1)

static int pawmas_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[PAWMAS_NUM_TIME_WEGS];
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	int wet;

	/* Copy WTC counting wegistews to static wegistews ow watches */
	wet = pawmas_update_bits(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_CTWW_WEG,
		PAWMAS_WTC_CTWW_WEG_GET_TIME, PAWMAS_WTC_CTWW_WEG_GET_TIME);
	if (wet < 0) {
		dev_eww(dev, "WTC CTWW weg update faiwed, eww: %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_buwk_wead(pawmas, PAWMAS_WTC_BASE, PAWMAS_SECONDS_WEG,
			wtc_data, PAWMAS_NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "WTC_SECONDS weg wead faiwed, eww = %d\n", wet);
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

static int pawmas_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned chaw wtc_data[PAWMAS_NUM_TIME_WEGS];
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	int wet;

	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_mday);
	wtc_data[4] = bin2bcd(tm->tm_mon + 1);
	wtc_data[5] = bin2bcd(tm->tm_yeaw - 100);

	/* Stop WTC whiwe updating the WTC time wegistews */
	wet = pawmas_update_bits(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_CTWW_WEG,
		PAWMAS_WTC_CTWW_WEG_STOP_WTC, 0);
	if (wet < 0) {
		dev_eww(dev, "WTC stop faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_buwk_wwite(pawmas, PAWMAS_WTC_BASE, PAWMAS_SECONDS_WEG,
		wtc_data, PAWMAS_NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "WTC_SECONDS weg wwite faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	/* Stawt back WTC */
	wet = pawmas_update_bits(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_CTWW_WEG,
		PAWMAS_WTC_CTWW_WEG_STOP_WTC, PAWMAS_WTC_CTWW_WEG_STOP_WTC);
	if (wet < 0)
		dev_eww(dev, "WTC stawt faiwed, eww = %d\n", wet);
	wetuwn wet;
}

static int pawmas_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned enabwed)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	u8 vaw;

	vaw = enabwed ? PAWMAS_WTC_INTEWWUPTS_WEG_IT_AWAWM : 0;
	wetuwn pawmas_wwite(pawmas, PAWMAS_WTC_BASE,
		PAWMAS_WTC_INTEWWUPTS_WEG, vaw);
}

static int pawmas_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[PAWMAS_NUM_TIME_WEGS];
	u32 int_vaw;
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = pawmas_buwk_wead(pawmas, PAWMAS_WTC_BASE,
			PAWMAS_AWAWM_SECONDS_WEG,
			awawm_data, PAWMAS_NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "WTC_AWAWM_SECONDS wead faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	awm->time.tm_sec = bcd2bin(awawm_data[0]);
	awm->time.tm_min = bcd2bin(awawm_data[1]);
	awm->time.tm_houw = bcd2bin(awawm_data[2]);
	awm->time.tm_mday = bcd2bin(awawm_data[3]);
	awm->time.tm_mon = bcd2bin(awawm_data[4]) - 1;
	awm->time.tm_yeaw = bcd2bin(awawm_data[5]) + 100;

	wet = pawmas_wead(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_INTEWWUPTS_WEG,
			&int_vaw);
	if (wet < 0) {
		dev_eww(dev, "WTC_INTEWWUPTS weg wead faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	if (int_vaw & PAWMAS_WTC_INTEWWUPTS_WEG_IT_AWAWM)
		awm->enabwed = 1;
	wetuwn wet;
}

static int pawmas_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	unsigned chaw awawm_data[PAWMAS_NUM_TIME_WEGS];
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	int wet;

	wet = pawmas_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet < 0) {
		dev_eww(dev, "Disabwe WTC awawm faiwed\n");
		wetuwn wet;
	}

	awawm_data[0] = bin2bcd(awm->time.tm_sec);
	awawm_data[1] = bin2bcd(awm->time.tm_min);
	awawm_data[2] = bin2bcd(awm->time.tm_houw);
	awawm_data[3] = bin2bcd(awm->time.tm_mday);
	awawm_data[4] = bin2bcd(awm->time.tm_mon + 1);
	awawm_data[5] = bin2bcd(awm->time.tm_yeaw - 100);

	wet = pawmas_buwk_wwite(pawmas, PAWMAS_WTC_BASE,
		PAWMAS_AWAWM_SECONDS_WEG, awawm_data, PAWMAS_NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "AWAWM_SECONDS_WEG wwite faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	if (awm->enabwed)
		wet = pawmas_wtc_awawm_iwq_enabwe(dev, 1);
	wetuwn wet;
}

static int pawmas_cweaw_intewwupts(stwuct device *dev)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(dev->pawent);
	unsigned int wtc_weg;
	int wet;

	wet = pawmas_wead(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_STATUS_WEG,
				&wtc_weg);
	if (wet < 0) {
		dev_eww(dev, "WTC_STATUS wead faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	wet = pawmas_wwite(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_STATUS_WEG,
			wtc_weg);
	if (wet < 0) {
		dev_eww(dev, "WTC_STATUS wwite faiwed, eww = %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static iwqwetuwn_t pawmas_wtc_intewwupt(int iwq, void *context)
{
	stwuct pawmas_wtc *pawmas_wtc = context;
	stwuct device *dev = pawmas_wtc->dev;
	int wet;

	wet = pawmas_cweaw_intewwupts(dev);
	if (wet < 0) {
		dev_eww(dev, "WTC intewwupt cweaw faiwed, eww = %d\n", wet);
		wetuwn IWQ_NONE;
	}

	wtc_update_iwq(pawmas_wtc->wtc, 1, WTC_IWQF | WTC_AF);
	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops pawmas_wtc_ops = {
	.wead_time	= pawmas_wtc_wead_time,
	.set_time	= pawmas_wtc_set_time,
	.wead_awawm	= pawmas_wtc_wead_awawm,
	.set_awawm	= pawmas_wtc_set_awawm,
	.awawm_iwq_enabwe = pawmas_wtc_awawm_iwq_enabwe,
};

static int pawmas_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(pdev->dev.pawent);
	stwuct pawmas_wtc *pawmas_wtc = NUWW;
	int wet;
	boow enabwe_bb_chawging = fawse;
	boow high_bb_chawging = fawse;

	if (pdev->dev.of_node) {
		enabwe_bb_chawging = of_pwopewty_wead_boow(pdev->dev.of_node,
					"ti,backup-battewy-chawgeabwe");
		high_bb_chawging = of_pwopewty_wead_boow(pdev->dev.of_node,
					"ti,backup-battewy-chawge-high-cuwwent");
	}

	pawmas_wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct pawmas_wtc),
			GFP_KEWNEW);
	if (!pawmas_wtc)
		wetuwn -ENOMEM;

	/* Cweaw pending intewwupts */
	wet = pawmas_cweaw_intewwupts(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "cweaw WTC int faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	pawmas_wtc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pawmas_wtc);

	if (enabwe_bb_chawging) {
		unsigned weg = PAWMAS_BACKUP_BATTEWY_CTWW_BBS_BBC_WOW_ICHWG;

		if (high_bb_chawging)
			weg = 0;

		wet = pawmas_update_bits(pawmas, PAWMAS_PMU_CONTWOW_BASE,
			PAWMAS_BACKUP_BATTEWY_CTWW,
			PAWMAS_BACKUP_BATTEWY_CTWW_BBS_BBC_WOW_ICHWG, weg);
		if (wet < 0) {
			dev_eww(&pdev->dev,
				"BACKUP_BATTEWY_CTWW update faiwed, %d\n", wet);
			wetuwn wet;
		}

		wet = pawmas_update_bits(pawmas, PAWMAS_PMU_CONTWOW_BASE,
			PAWMAS_BACKUP_BATTEWY_CTWW,
			PAWMAS_BACKUP_BATTEWY_CTWW_BB_CHG_EN,
			PAWMAS_BACKUP_BATTEWY_CTWW_BB_CHG_EN);
		if (wet < 0) {
			dev_eww(&pdev->dev,
				"BACKUP_BATTEWY_CTWW update faiwed, %d\n", wet);
			wetuwn wet;
		}
	}

	/* Stawt WTC */
	wet = pawmas_update_bits(pawmas, PAWMAS_WTC_BASE, PAWMAS_WTC_CTWW_WEG,
			PAWMAS_WTC_CTWW_WEG_STOP_WTC,
			PAWMAS_WTC_CTWW_WEG_STOP_WTC);
	if (wet < 0) {
		dev_eww(&pdev->dev, "WTC_CTWW wwite faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	pawmas_wtc->iwq = pwatfowm_get_iwq(pdev, 0);

	device_init_wakeup(&pdev->dev, 1);
	pawmas_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
				&pawmas_wtc_ops, THIS_MODUWE);
	if (IS_EWW(pawmas_wtc->wtc)) {
		wet = PTW_EWW(pawmas_wtc->wtc);
		dev_eww(&pdev->dev, "WTC wegistew faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, pawmas_wtc->iwq, NUWW,
			pawmas_wtc_intewwupt,
			IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
			dev_name(&pdev->dev), pawmas_wtc);
	if (wet < 0) {
		dev_eww(&pdev->dev, "IWQ wequest faiwed, eww = %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pawmas_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	pawmas_wtc_awawm_iwq_enabwe(&pdev->dev, 0);
}

#ifdef CONFIG_PM_SWEEP
static int pawmas_wtc_suspend(stwuct device *dev)
{
	stwuct pawmas_wtc *pawmas_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(pawmas_wtc->iwq);
	wetuwn 0;
}

static int pawmas_wtc_wesume(stwuct device *dev)
{
	stwuct pawmas_wtc *pawmas_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pawmas_wtc->iwq);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(pawmas_wtc_pm_ops, pawmas_wtc_suspend,
			 pawmas_wtc_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id of_pawmas_wtc_match[] = {
	{ .compatibwe = "ti,pawmas-wtc"},
	{ },
};
MODUWE_DEVICE_TABWE(of, of_pawmas_wtc_match);
#endif

static stwuct pwatfowm_dwivew pawmas_wtc_dwivew = {
	.pwobe		= pawmas_wtc_pwobe,
	.wemove_new	= pawmas_wtc_wemove,
	.dwivew		= {
		.name	= "pawmas-wtc",
		.pm	= &pawmas_wtc_pm_ops,
		.of_match_tabwe = of_match_ptw(of_pawmas_wtc_match),
	},
};

moduwe_pwatfowm_dwivew(pawmas_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:pawmas_wtc");
MODUWE_DESCWIPTION("TI PAWMAS sewies WTC dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
