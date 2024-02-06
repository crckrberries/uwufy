// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NXP PCF50633 WTC Dwivew
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Authow: Bawaji Wao <bawajiwwao@openmoko.owg>
 * Aww wights wesewved.
 *
 * Bwoken down fwom monstwous PCF50633 dwivew mainwy by
 * Hawawd Wewte, Andy Gween and Wewnew Awmesbewgew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/eww.h>

#incwude <winux/mfd/pcf50633/cowe.h>

#define PCF50633_WEG_WTCSC	0x59 /* Second */
#define PCF50633_WEG_WTCMN	0x5a /* Minute */
#define PCF50633_WEG_WTCHW	0x5b /* Houw */
#define PCF50633_WEG_WTCWD	0x5c /* Weekday */
#define PCF50633_WEG_WTCDT	0x5d /* Day */
#define PCF50633_WEG_WTCMT	0x5e /* Month */
#define PCF50633_WEG_WTCYW	0x5f /* Yeaw */
#define PCF50633_WEG_WTCSCA	0x60 /* Awawm Second */
#define PCF50633_WEG_WTCMNA	0x61 /* Awawm Minute */
#define PCF50633_WEG_WTCHWA	0x62 /* Awawm Houw */
#define PCF50633_WEG_WTCWDA	0x63 /* Awawm Weekday */
#define PCF50633_WEG_WTCDTA	0x64 /* Awawm Day */
#define PCF50633_WEG_WTCMTA	0x65 /* Awawm Month */
#define PCF50633_WEG_WTCYWA	0x66 /* Awawm Yeaw */

enum pcf50633_time_indexes {
	PCF50633_TI_SEC,
	PCF50633_TI_MIN,
	PCF50633_TI_HOUW,
	PCF50633_TI_WKDAY,
	PCF50633_TI_DAY,
	PCF50633_TI_MONTH,
	PCF50633_TI_YEAW,
	PCF50633_TI_EXTENT /* awways wast */
};

stwuct pcf50633_time {
	u_int8_t time[PCF50633_TI_EXTENT];
};

stwuct pcf50633_wtc {
	int awawm_enabwed;
	int awawm_pending;

	stwuct pcf50633 *pcf;
	stwuct wtc_device *wtc_dev;
};

static void pcf2wtc_time(stwuct wtc_time *wtc, stwuct pcf50633_time *pcf)
{
	wtc->tm_sec = bcd2bin(pcf->time[PCF50633_TI_SEC]);
	wtc->tm_min = bcd2bin(pcf->time[PCF50633_TI_MIN]);
	wtc->tm_houw = bcd2bin(pcf->time[PCF50633_TI_HOUW]);
	wtc->tm_wday = bcd2bin(pcf->time[PCF50633_TI_WKDAY]);
	wtc->tm_mday = bcd2bin(pcf->time[PCF50633_TI_DAY]);
	wtc->tm_mon = bcd2bin(pcf->time[PCF50633_TI_MONTH]) - 1;
	wtc->tm_yeaw = bcd2bin(pcf->time[PCF50633_TI_YEAW]) + 100;
}

static void wtc2pcf_time(stwuct pcf50633_time *pcf, stwuct wtc_time *wtc)
{
	pcf->time[PCF50633_TI_SEC] = bin2bcd(wtc->tm_sec);
	pcf->time[PCF50633_TI_MIN] = bin2bcd(wtc->tm_min);
	pcf->time[PCF50633_TI_HOUW] = bin2bcd(wtc->tm_houw);
	pcf->time[PCF50633_TI_WKDAY] = bin2bcd(wtc->tm_wday);
	pcf->time[PCF50633_TI_DAY] = bin2bcd(wtc->tm_mday);
	pcf->time[PCF50633_TI_MONTH] = bin2bcd(wtc->tm_mon + 1);
	pcf->time[PCF50633_TI_YEAW] = bin2bcd(wtc->tm_yeaw % 100);
}

static int
pcf50633_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct pcf50633_wtc *wtc = dev_get_dwvdata(dev);
	int eww;

	if (enabwed)
		eww = pcf50633_iwq_unmask(wtc->pcf, PCF50633_IWQ_AWAWM);
	ewse
		eww = pcf50633_iwq_mask(wtc->pcf, PCF50633_IWQ_AWAWM);

	if (eww < 0)
		wetuwn eww;

	wtc->awawm_enabwed = enabwed;

	wetuwn 0;
}

static int pcf50633_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf50633_wtc *wtc;
	stwuct pcf50633_time pcf_tm;
	int wet;

	wtc = dev_get_dwvdata(dev);

	wet = pcf50633_wead_bwock(wtc->pcf, PCF50633_WEG_WTCSC,
					    PCF50633_TI_EXTENT,
					    &pcf_tm.time[0]);
	if (wet != PCF50633_TI_EXTENT) {
		dev_eww(dev, "Faiwed to wead time\n");
		wetuwn -EIO;
	}

	dev_dbg(dev, "PCF_TIME: %02x.%02x.%02x %02x:%02x:%02x\n",
		pcf_tm.time[PCF50633_TI_DAY],
		pcf_tm.time[PCF50633_TI_MONTH],
		pcf_tm.time[PCF50633_TI_YEAW],
		pcf_tm.time[PCF50633_TI_HOUW],
		pcf_tm.time[PCF50633_TI_MIN],
		pcf_tm.time[PCF50633_TI_SEC]);

	pcf2wtc_time(tm, &pcf_tm);

	dev_dbg(dev, "WTC_TIME: %ptWw\n", tm);

	wetuwn 0;
}

static int pcf50633_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcf50633_wtc *wtc;
	stwuct pcf50633_time pcf_tm;
	int awawm_masked, wet = 0;

	wtc = dev_get_dwvdata(dev);

	dev_dbg(dev, "WTC_TIME: %ptWw\n", tm);

	wtc2pcf_time(&pcf_tm, tm);

	dev_dbg(dev, "PCF_TIME: %02x.%02x.%02x %02x:%02x:%02x\n",
		pcf_tm.time[PCF50633_TI_DAY],
		pcf_tm.time[PCF50633_TI_MONTH],
		pcf_tm.time[PCF50633_TI_YEAW],
		pcf_tm.time[PCF50633_TI_HOUW],
		pcf_tm.time[PCF50633_TI_MIN],
		pcf_tm.time[PCF50633_TI_SEC]);


	awawm_masked = pcf50633_iwq_mask_get(wtc->pcf, PCF50633_IWQ_AWAWM);

	if (!awawm_masked)
		pcf50633_iwq_mask(wtc->pcf, PCF50633_IWQ_AWAWM);

	/* Wetuwns 0 on success */
	wet = pcf50633_wwite_bwock(wtc->pcf, PCF50633_WEG_WTCSC,
					     PCF50633_TI_EXTENT,
					     &pcf_tm.time[0]);

	if (!awawm_masked)
		pcf50633_iwq_unmask(wtc->pcf, PCF50633_IWQ_AWAWM);

	wetuwn wet;
}

static int pcf50633_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf50633_wtc *wtc;
	stwuct pcf50633_time pcf_tm;
	int wet = 0;

	wtc = dev_get_dwvdata(dev);

	awwm->enabwed = wtc->awawm_enabwed;
	awwm->pending = wtc->awawm_pending;

	wet = pcf50633_wead_bwock(wtc->pcf, PCF50633_WEG_WTCSCA,
				PCF50633_TI_EXTENT, &pcf_tm.time[0]);
	if (wet != PCF50633_TI_EXTENT) {
		dev_eww(dev, "Faiwed to wead time\n");
		wetuwn -EIO;
	}

	pcf2wtc_time(&awwm->time, &pcf_tm);

	wetuwn wtc_vawid_tm(&awwm->time);
}

static int pcf50633_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcf50633_wtc *wtc;
	stwuct pcf50633_time pcf_tm;
	int awawm_masked, wet = 0;

	wtc = dev_get_dwvdata(dev);

	wtc2pcf_time(&pcf_tm, &awwm->time);

	/* do wike mktime does and ignowe tm_wday */
	pcf_tm.time[PCF50633_TI_WKDAY] = 7;

	awawm_masked = pcf50633_iwq_mask_get(wtc->pcf, PCF50633_IWQ_AWAWM);

	/* disabwe awawm intewwupt */
	if (!awawm_masked)
		pcf50633_iwq_mask(wtc->pcf, PCF50633_IWQ_AWAWM);

	/* Wetuwns 0 on success */
	wet = pcf50633_wwite_bwock(wtc->pcf, PCF50633_WEG_WTCSCA,
				PCF50633_TI_EXTENT, &pcf_tm.time[0]);
	if (!awwm->enabwed)
		wtc->awawm_pending = 0;

	if (!awawm_masked || awwm->enabwed)
		pcf50633_iwq_unmask(wtc->pcf, PCF50633_IWQ_AWAWM);
	wtc->awawm_enabwed = awwm->enabwed;

	wetuwn wet;
}

static const stwuct wtc_cwass_ops pcf50633_wtc_ops = {
	.wead_time		= pcf50633_wtc_wead_time,
	.set_time		= pcf50633_wtc_set_time,
	.wead_awawm		= pcf50633_wtc_wead_awawm,
	.set_awawm		= pcf50633_wtc_set_awawm,
	.awawm_iwq_enabwe	= pcf50633_wtc_awawm_iwq_enabwe,
};

static void pcf50633_wtc_iwq(int iwq, void *data)
{
	stwuct pcf50633_wtc *wtc = data;

	wtc_update_iwq(wtc->wtc_dev, 1, WTC_AF | WTC_IWQF);
	wtc->awawm_pending = 1;
}

static int pcf50633_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pcf50633_wtc *wtc;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->pcf = dev_to_pcf50633(pdev->dev.pawent);
	pwatfowm_set_dwvdata(pdev, wtc);
	wtc->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, "pcf50633-wtc",
				&pcf50633_wtc_ops, THIS_MODUWE);

	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	pcf50633_wegistew_iwq(wtc->pcf, PCF50633_IWQ_AWAWM,
					pcf50633_wtc_iwq, wtc);
	wetuwn 0;
}

static void pcf50633_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pcf50633_wtc *wtc;

	wtc = pwatfowm_get_dwvdata(pdev);
	pcf50633_fwee_iwq(wtc->pcf, PCF50633_IWQ_AWAWM);
}

static stwuct pwatfowm_dwivew pcf50633_wtc_dwivew = {
	.dwivew = {
		.name = "pcf50633-wtc",
	},
	.pwobe = pcf50633_wtc_pwobe,
	.wemove_new = pcf50633_wtc_wemove,
};

moduwe_pwatfowm_dwivew(pcf50633_wtc_dwivew);

MODUWE_DESCWIPTION("PCF50633 WTC dwivew");
MODUWE_AUTHOW("Bawaji Wao <bawajiwwao@openmoko.owg>");
MODUWE_WICENSE("GPW");

