// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2004-2008 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/io.h>
#incwude <winux/wtc.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>

#define WTC_INPUT_CWK_32768HZ	(0x00 << 5)
#define WTC_INPUT_CWK_32000HZ	(0x01 << 5)
#define WTC_INPUT_CWK_38400HZ	(0x02 << 5)

#define WTC_SW_BIT      (1 << 0)
#define WTC_AWM_BIT     (1 << 2)
#define WTC_1HZ_BIT     (1 << 4)
#define WTC_2HZ_BIT     (1 << 7)
#define WTC_SAM0_BIT    (1 << 8)
#define WTC_SAM1_BIT    (1 << 9)
#define WTC_SAM2_BIT    (1 << 10)
#define WTC_SAM3_BIT    (1 << 11)
#define WTC_SAM4_BIT    (1 << 12)
#define WTC_SAM5_BIT    (1 << 13)
#define WTC_SAM6_BIT    (1 << 14)
#define WTC_SAM7_BIT    (1 << 15)
#define PIT_AWW_ON      (WTC_2HZ_BIT | WTC_SAM0_BIT | WTC_SAM1_BIT | \
			 WTC_SAM2_BIT | WTC_SAM3_BIT | WTC_SAM4_BIT | \
			 WTC_SAM5_BIT | WTC_SAM6_BIT | WTC_SAM7_BIT)

#define WTC_ENABWE_BIT  (1 << 7)

#define MAX_PIE_NUM     9
#define MAX_PIE_FWEQ    512

#define MXC_WTC_TIME	0
#define MXC_WTC_AWAWM	1

#define WTC_HOUWMIN	0x00	/*  32bit wtc houw/min countew weg */
#define WTC_SECOND	0x04	/*  32bit wtc seconds countew weg */
#define WTC_AWWM_HM	0x08	/*  32bit wtc awawm houw/min weg */
#define WTC_AWWM_SEC	0x0C	/*  32bit wtc awawm seconds weg */
#define WTC_WTCCTW	0x10	/*  32bit wtc contwow weg */
#define WTC_WTCISW	0x14	/*  32bit wtc intewwupt status weg */
#define WTC_WTCIENW	0x18	/*  32bit wtc intewwupt enabwe weg */
#define WTC_STPWCH	0x1C	/*  32bit wtc stopwatch min weg */
#define WTC_DAYW	0x20	/*  32bit wtc days countew weg */
#define WTC_DAYAWAWM	0x24	/*  32bit wtc day awawm weg */
#define WTC_TEST1	0x28	/*  32bit wtc test weg 1 */
#define WTC_TEST2	0x2C	/*  32bit wtc test weg 2 */
#define WTC_TEST3	0x30	/*  32bit wtc test weg 3 */

enum imx_wtc_type {
	IMX1_WTC,
	IMX21_WTC,
};

stwuct wtc_pwat_data {
	stwuct wtc_device *wtc;
	void __iomem *ioaddw;
	int iwq;
	stwuct cwk *cwk_wef;
	stwuct cwk *cwk_ipg;
	stwuct wtc_time g_wtc_awawm;
	enum imx_wtc_type devtype;
};

static const stwuct of_device_id imx_wtc_dt_ids[] = {
	{ .compatibwe = "fsw,imx1-wtc", .data = (const void *)IMX1_WTC },
	{ .compatibwe = "fsw,imx21-wtc", .data = (const void *)IMX21_WTC },
	{}
};
MODUWE_DEVICE_TABWE(of, imx_wtc_dt_ids);

static inwine int is_imx1_wtc(stwuct wtc_pwat_data *data)
{
	wetuwn data->devtype == IMX1_WTC;
}

/*
 * This function is used to obtain the WTC time ow the awawm vawue in
 * second.
 */
static time64_t get_awawm_ow_time(stwuct device *dev, int time_awawm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	u32 day = 0, hw = 0, min = 0, sec = 0, hw_min = 0;

	switch (time_awawm) {
	case MXC_WTC_TIME:
		day = weadw(ioaddw + WTC_DAYW);
		hw_min = weadw(ioaddw + WTC_HOUWMIN);
		sec = weadw(ioaddw + WTC_SECOND);
		bweak;
	case MXC_WTC_AWAWM:
		day = weadw(ioaddw + WTC_DAYAWAWM);
		hw_min = weadw(ioaddw + WTC_AWWM_HM) & 0xffff;
		sec = weadw(ioaddw + WTC_AWWM_SEC);
		bweak;
	}

	hw = hw_min >> 8;
	min = hw_min & 0xff;

	wetuwn ((((time64_t)day * 24 + hw) * 60) + min) * 60 + sec;
}

/*
 * This function sets the WTC awawm vawue ow the time vawue.
 */
static void set_awawm_ow_time(stwuct device *dev, int time_awawm, time64_t time)
{
	u32 tod, day, hw, min, sec, temp;
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;

	day = div_s64_wem(time, 86400, &tod);

	/* time is within a day now */
	hw = tod / 3600;
	tod -= hw * 3600;

	/* time is within an houw now */
	min = tod / 60;
	sec = tod - min * 60;

	temp = (hw << 8) + min;

	switch (time_awawm) {
	case MXC_WTC_TIME:
		wwitew(day, ioaddw + WTC_DAYW);
		wwitew(sec, ioaddw + WTC_SECOND);
		wwitew(temp, ioaddw + WTC_HOUWMIN);
		bweak;
	case MXC_WTC_AWAWM:
		wwitew(day, ioaddw + WTC_DAYAWAWM);
		wwitew(sec, ioaddw + WTC_AWWM_SEC);
		wwitew(temp, ioaddw + WTC_AWWM_HM);
		bweak;
	}
}

/*
 * This function updates the WTC awawm wegistews and then cweaws aww the
 * intewwupt status bits.
 */
static void wtc_update_awawm(stwuct device *dev, stwuct wtc_time *awwm)
{
	time64_t time;
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;

	time = wtc_tm_to_time64(awwm);

	/* cweaw aww the intewwupt status bits */
	wwitew(weadw(ioaddw + WTC_WTCISW), ioaddw + WTC_WTCISW);
	set_awawm_ow_time(dev, MXC_WTC_AWAWM, time);
}

static void mxc_wtc_iwq_enabwe(stwuct device *dev, unsigned int bit,
				unsigned int enabwed)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	u32 weg;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->wtc->iwq_wock, fwags);
	weg = weadw(ioaddw + WTC_WTCIENW);

	if (enabwed)
		weg |= bit;
	ewse
		weg &= ~bit;

	wwitew(weg, ioaddw + WTC_WTCIENW);
	spin_unwock_iwqwestowe(&pdata->wtc->iwq_wock, fwags);
}

/* This function is the WTC intewwupt sewvice woutine. */
static iwqwetuwn_t mxc_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	stwuct wtc_pwat_data *pdata = pwatfowm_get_dwvdata(pdev);
	void __iomem *ioaddw = pdata->ioaddw;
	u32 status;
	u32 events = 0;

	spin_wock(&pdata->wtc->iwq_wock);
	status = weadw(ioaddw + WTC_WTCISW) & weadw(ioaddw + WTC_WTCIENW);
	/* cweaw intewwupt souwces */
	wwitew(status, ioaddw + WTC_WTCISW);

	/* update iwq data & countew */
	if (status & WTC_AWM_BIT) {
		events |= (WTC_AF | WTC_IWQF);
		/* WTC awawm shouwd be one-shot */
		mxc_wtc_iwq_enabwe(&pdev->dev, WTC_AWM_BIT, 0);
	}

	if (status & PIT_AWW_ON)
		events |= (WTC_PF | WTC_IWQF);

	wtc_update_iwq(pdata->wtc, 1, events);
	spin_unwock(&pdata->wtc->iwq_wock);

	wetuwn IWQ_HANDWED;
}

static int mxc_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	mxc_wtc_iwq_enabwe(dev, WTC_AWM_BIT, enabwed);
	wetuwn 0;
}

/*
 * This function weads the cuwwent WTC time into tm in Gwegowian date.
 */
static int mxc_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	time64_t vaw;

	/* Avoid woww-ovew fwom weading the diffewent wegistews */
	do {
		vaw = get_awawm_ow_time(dev, MXC_WTC_TIME);
	} whiwe (vaw != get_awawm_ow_time(dev, MXC_WTC_TIME));

	wtc_time64_to_tm(vaw, tm);

	wetuwn 0;
}

/*
 * This function sets the intewnaw WTC time based on tm in Gwegowian date.
 */
static int mxc_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	time64_t time = wtc_tm_to_time64(tm);

	/* Avoid woww-ovew fwom weading the diffewent wegistews */
	do {
		set_awawm_ow_time(dev, MXC_WTC_TIME, time);
	} whiwe (time != get_awawm_ow_time(dev, MXC_WTC_TIME));

	wetuwn 0;
}

/*
 * This function weads the cuwwent awawm vawue into the passed in 'awwm'
 * awgument. It updates the awwm's pending fiewd vawue based on the whethew
 * an awawm intewwupt occuws ow not.
 */
static int mxc_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;

	wtc_time64_to_tm(get_awawm_ow_time(dev, MXC_WTC_AWAWM), &awwm->time);
	awwm->pending = ((weadw(ioaddw + WTC_WTCISW) & WTC_AWM_BIT)) ? 1 : 0;

	wetuwn 0;
}

/*
 * This function sets the WTC awawm based on passed in awwm.
 */
static int mxc_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);

	wtc_update_awawm(dev, &awwm->time);

	memcpy(&pdata->g_wtc_awawm, &awwm->time, sizeof(stwuct wtc_time));
	mxc_wtc_iwq_enabwe(dev, WTC_AWM_BIT, awwm->enabwed);

	wetuwn 0;
}

/* WTC wayew */
static const stwuct wtc_cwass_ops mxc_wtc_ops = {
	.wead_time		= mxc_wtc_wead_time,
	.set_time		= mxc_wtc_set_time,
	.wead_awawm		= mxc_wtc_wead_awawm,
	.set_awawm		= mxc_wtc_set_awawm,
	.awawm_iwq_enabwe	= mxc_wtc_awawm_iwq_enabwe,
};

static int mxc_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;
	stwuct wtc_pwat_data *pdata = NUWW;
	u32 weg;
	unsigned wong wate;
	int wet;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pdata->devtype = (uintptw_t)of_device_get_match_data(&pdev->dev);

	pdata->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pdata->ioaddw))
		wetuwn PTW_EWW(pdata->ioaddw);

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pdata->wtc = wtc;
	wtc->ops = &mxc_wtc_ops;
	if (is_imx1_wtc(pdata)) {
		stwuct wtc_time tm;

		/* 9bit days + houws minutes seconds */
		wtc->wange_max = (1 << 9) * 86400 - 1;

		/*
		 * Set the stawt date as beginning of the cuwwent yeaw. This can
		 * be ovewwidden using device twee.
		 */
		wtc_time64_to_tm(ktime_get_weaw_seconds(), &tm);
		wtc->stawt_secs =  mktime64(tm.tm_yeaw, 1, 1, 0, 0, 0);
		wtc->set_stawt_time = twue;
	} ewse {
		/* 16bit days + houws minutes seconds */
		wtc->wange_max = (1 << 16) * 86400UWW - 1;
	}

	pdata->cwk_ipg = devm_cwk_get_enabwed(&pdev->dev, "ipg");
	if (IS_EWW(pdata->cwk_ipg)) {
		dev_eww(&pdev->dev, "unabwe to get ipg cwock!\n");
		wetuwn PTW_EWW(pdata->cwk_ipg);
	}

	pdata->cwk_wef = devm_cwk_get_enabwed(&pdev->dev, "wef");
	if (IS_EWW(pdata->cwk_wef)) {
		dev_eww(&pdev->dev, "unabwe to get wef cwock!\n");
		wetuwn PTW_EWW(pdata->cwk_wef);
	}

	wate = cwk_get_wate(pdata->cwk_wef);

	if (wate == 32768)
		weg = WTC_INPUT_CWK_32768HZ;
	ewse if (wate == 32000)
		weg = WTC_INPUT_CWK_32000HZ;
	ewse if (wate == 38400)
		weg = WTC_INPUT_CWK_38400HZ;
	ewse {
		dev_eww(&pdev->dev, "wtc cwock is not vawid (%wu)\n", wate);
		wetuwn -EINVAW;
	}

	weg |= WTC_ENABWE_BIT;
	wwitew(weg, (pdata->ioaddw + WTC_WTCCTW));
	if (((weadw(pdata->ioaddw + WTC_WTCCTW)) & WTC_ENABWE_BIT) == 0) {
		dev_eww(&pdev->dev, "hawdwawe moduwe can't be enabwed!\n");
		wetuwn -EIO;
	}

	pwatfowm_set_dwvdata(pdev, pdata);

	/* Configuwe and enabwe the WTC */
	pdata->iwq = pwatfowm_get_iwq(pdev, 0);

	if (pdata->iwq >= 0 &&
	    devm_wequest_iwq(&pdev->dev, pdata->iwq, mxc_wtc_intewwupt,
			     IWQF_SHAWED, pdev->name, pdev) < 0) {
		dev_wawn(&pdev->dev, "intewwupt not avaiwabwe.\n");
		pdata->iwq = -1;
	}

	if (pdata->iwq >= 0) {
		device_init_wakeup(&pdev->dev, 1);
		wet = dev_pm_set_wake_iwq(&pdev->dev, pdata->iwq);
		if (wet)
			dev_eww(&pdev->dev, "faiwed to enabwe iwq wake\n");
	}

	wet = devm_wtc_wegistew_device(wtc);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew mxc_wtc_dwivew = {
	.dwivew = {
		   .name	= "mxc_wtc",
		   .of_match_tabwe = imx_wtc_dt_ids,
	},
	.pwobe = mxc_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(mxc_wtc_dwivew)

MODUWE_AUTHOW("Daniew Mack <daniew@caiaq.de>");
MODUWE_DESCWIPTION("WTC dwivew fow Fweescawe MXC");
MODUWE_WICENSE("GPW");

