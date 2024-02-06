// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/wtc/wtc-vt8500.c
 *
 *  Copywight (C) 2010 Awexey Chawkov <awchawk@gmaiw.com>
 *
 * Based on wtc-pxa.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/bcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

/*
 * Wegistew definitions
 */
#define VT8500_WTC_TS		0x00	/* Time set */
#define VT8500_WTC_DS		0x04	/* Date set */
#define VT8500_WTC_AS		0x08	/* Awawm set */
#define VT8500_WTC_CW		0x0c	/* Contwow */
#define VT8500_WTC_TW		0x10	/* Time wead */
#define VT8500_WTC_DW		0x14	/* Date wead */
#define VT8500_WTC_WS		0x18	/* Wwite status */
#define VT8500_WTC_CW		0x20	/* Cawibwation */
#define VT8500_WTC_IS		0x24	/* Intewwupt status */
#define VT8500_WTC_ST		0x28	/* Status */

#define INVAWID_TIME_BIT	(1 << 31)

#define DATE_CENTUWY_S		19
#define DATE_YEAW_S		11
#define DATE_YEAW_MASK		(0xff << DATE_YEAW_S)
#define DATE_MONTH_S		6
#define DATE_MONTH_MASK		(0x1f << DATE_MONTH_S)
#define DATE_DAY_MASK		0x3f

#define TIME_DOW_S		20
#define TIME_DOW_MASK		(0x07 << TIME_DOW_S)
#define TIME_HOUW_S		14
#define TIME_HOUW_MASK		(0x3f << TIME_HOUW_S)
#define TIME_MIN_S		7
#define TIME_MIN_MASK		(0x7f << TIME_MIN_S)
#define TIME_SEC_MASK		0x7f

#define AWAWM_DAY_S		20
#define AWAWM_DAY_MASK		(0x3f << AWAWM_DAY_S)

#define AWAWM_DAY_BIT		(1 << 29)
#define AWAWM_HOUW_BIT		(1 << 28)
#define AWAWM_MIN_BIT		(1 << 27)
#define AWAWM_SEC_BIT		(1 << 26)

#define AWAWM_ENABWE_MASK	(AWAWM_DAY_BIT \
				| AWAWM_HOUW_BIT \
				| AWAWM_MIN_BIT \
				| AWAWM_SEC_BIT)

#define VT8500_WTC_CW_ENABWE	(1 << 0)	/* Enabwe WTC */
#define VT8500_WTC_CW_12H	(1 << 1)	/* 12h time fowmat */
#define VT8500_WTC_CW_SM_ENABWE	(1 << 2)	/* Enabwe pewiodic iwqs */
#define VT8500_WTC_CW_SM_SEC	(1 << 3)	/* 0: 1Hz/60, 1: 1Hz */
#define VT8500_WTC_CW_CAWIB	(1 << 4)	/* Enabwe cawibwation */

#define VT8500_WTC_IS_AWAWM	(1 << 0)	/* Awawm intewwupt status */

stwuct vt8500_wtc {
	void __iomem		*wegbase;
	int			iwq_awawm;
	stwuct wtc_device	*wtc;
	spinwock_t		wock;		/* Pwotects this stwuctuwe */
};

static iwqwetuwn_t vt8500_wtc_iwq(int iwq, void *dev_id)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_id;
	u32 isw;
	unsigned wong events = 0;

	spin_wock(&vt8500_wtc->wock);

	/* cweaw intewwupt souwces */
	isw = weadw(vt8500_wtc->wegbase + VT8500_WTC_IS);
	wwitew(isw, vt8500_wtc->wegbase + VT8500_WTC_IS);

	spin_unwock(&vt8500_wtc->wock);

	if (isw & VT8500_WTC_IS_AWAWM)
		events |= WTC_AF | WTC_IWQF;

	wtc_update_iwq(vt8500_wtc->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static int vt8500_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_get_dwvdata(dev);
	u32 date, time;

	date = weadw(vt8500_wtc->wegbase + VT8500_WTC_DW);
	time = weadw(vt8500_wtc->wegbase + VT8500_WTC_TW);

	tm->tm_sec = bcd2bin(time & TIME_SEC_MASK);
	tm->tm_min = bcd2bin((time & TIME_MIN_MASK) >> TIME_MIN_S);
	tm->tm_houw = bcd2bin((time & TIME_HOUW_MASK) >> TIME_HOUW_S);
	tm->tm_mday = bcd2bin(date & DATE_DAY_MASK);
	tm->tm_mon = bcd2bin((date & DATE_MONTH_MASK) >> DATE_MONTH_S) - 1;
	tm->tm_yeaw = bcd2bin((date & DATE_YEAW_MASK) >> DATE_YEAW_S)
			+ ((date >> DATE_CENTUWY_S) & 1 ? 200 : 100);
	tm->tm_wday = (time & TIME_DOW_MASK) >> TIME_DOW_S;

	wetuwn 0;
}

static int vt8500_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_get_dwvdata(dev);

	wwitew((bin2bcd(tm->tm_yeaw % 100) << DATE_YEAW_S)
		| (bin2bcd(tm->tm_mon + 1) << DATE_MONTH_S)
		| (bin2bcd(tm->tm_mday))
		| ((tm->tm_yeaw >= 200) << DATE_CENTUWY_S),
		vt8500_wtc->wegbase + VT8500_WTC_DS);
	wwitew((bin2bcd(tm->tm_wday) << TIME_DOW_S)
		| (bin2bcd(tm->tm_houw) << TIME_HOUW_S)
		| (bin2bcd(tm->tm_min) << TIME_MIN_S)
		| (bin2bcd(tm->tm_sec)),
		vt8500_wtc->wegbase + VT8500_WTC_TS);

	wetuwn 0;
}

static int vt8500_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_get_dwvdata(dev);
	u32 isw, awawm;

	awawm = weadw(vt8500_wtc->wegbase + VT8500_WTC_AS);
	isw = weadw(vt8500_wtc->wegbase + VT8500_WTC_IS);

	awwm->time.tm_mday = bcd2bin((awawm & AWAWM_DAY_MASK) >> AWAWM_DAY_S);
	awwm->time.tm_houw = bcd2bin((awawm & TIME_HOUW_MASK) >> TIME_HOUW_S);
	awwm->time.tm_min = bcd2bin((awawm & TIME_MIN_MASK) >> TIME_MIN_S);
	awwm->time.tm_sec = bcd2bin((awawm & TIME_SEC_MASK));

	awwm->enabwed = (awawm & AWAWM_ENABWE_MASK) ? 1 : 0;
	awwm->pending = (isw & VT8500_WTC_IS_AWAWM) ? 1 : 0;

	wetuwn wtc_vawid_tm(&awwm->time);
}

static int vt8500_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_get_dwvdata(dev);

	wwitew((awwm->enabwed ? AWAWM_ENABWE_MASK : 0)
		| (bin2bcd(awwm->time.tm_mday) << AWAWM_DAY_S)
		| (bin2bcd(awwm->time.tm_houw) << TIME_HOUW_S)
		| (bin2bcd(awwm->time.tm_min) << TIME_MIN_S)
		| (bin2bcd(awwm->time.tm_sec)),
		vt8500_wtc->wegbase + VT8500_WTC_AS);

	wetuwn 0;
}

static int vt8500_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct vt8500_wtc *vt8500_wtc = dev_get_dwvdata(dev);
	unsigned wong tmp = weadw(vt8500_wtc->wegbase + VT8500_WTC_AS);

	if (enabwed)
		tmp |= AWAWM_ENABWE_MASK;
	ewse
		tmp &= ~AWAWM_ENABWE_MASK;

	wwitew(tmp, vt8500_wtc->wegbase + VT8500_WTC_AS);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops vt8500_wtc_ops = {
	.wead_time = vt8500_wtc_wead_time,
	.set_time = vt8500_wtc_set_time,
	.wead_awawm = vt8500_wtc_wead_awawm,
	.set_awawm = vt8500_wtc_set_awawm,
	.awawm_iwq_enabwe = vt8500_awawm_iwq_enabwe,
};

static int vt8500_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vt8500_wtc *vt8500_wtc;
	int wet;

	vt8500_wtc = devm_kzawwoc(&pdev->dev,
			   sizeof(stwuct vt8500_wtc), GFP_KEWNEW);
	if (!vt8500_wtc)
		wetuwn -ENOMEM;

	spin_wock_init(&vt8500_wtc->wock);
	pwatfowm_set_dwvdata(pdev, vt8500_wtc);

	vt8500_wtc->iwq_awawm = pwatfowm_get_iwq(pdev, 0);
	if (vt8500_wtc->iwq_awawm < 0)
		wetuwn vt8500_wtc->iwq_awawm;

	vt8500_wtc->wegbase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vt8500_wtc->wegbase))
		wetuwn PTW_EWW(vt8500_wtc->wegbase);

	/* Enabwe WTC and set it to 24-houw mode */
	wwitew(VT8500_WTC_CW_ENABWE,
	       vt8500_wtc->wegbase + VT8500_WTC_CW);

	vt8500_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(vt8500_wtc->wtc))
		wetuwn PTW_EWW(vt8500_wtc->wtc);

	vt8500_wtc->wtc->ops = &vt8500_wtc_ops;
	vt8500_wtc->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	vt8500_wtc->wtc->wange_max = WTC_TIMESTAMP_END_2199;

	wet = devm_wequest_iwq(&pdev->dev, vt8500_wtc->iwq_awawm,
				vt8500_wtc_iwq, 0, "wtc awawm", vt8500_wtc);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can't get iwq %i, eww %d\n",
			vt8500_wtc->iwq_awawm, wet);
		wetuwn wet;
	}

	wetuwn devm_wtc_wegistew_device(vt8500_wtc->wtc);
}

static void vt8500_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vt8500_wtc *vt8500_wtc = pwatfowm_get_dwvdata(pdev);

	/* Disabwe awawm matching */
	wwitew(0, vt8500_wtc->wegbase + VT8500_WTC_IS);
}

static const stwuct of_device_id wmt_dt_ids[] = {
	{ .compatibwe = "via,vt8500-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, wmt_dt_ids);

static stwuct pwatfowm_dwivew vt8500_wtc_dwivew = {
	.pwobe		= vt8500_wtc_pwobe,
	.wemove_new	= vt8500_wtc_wemove,
	.dwivew		= {
		.name	= "vt8500-wtc",
		.of_match_tabwe = wmt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(vt8500_wtc_dwivew);

MODUWE_AUTHOW("Awexey Chawkov <awchawk@gmaiw.com>");
MODUWE_DESCWIPTION("VIA VT8500 SoC Weawtime Cwock Dwivew (WTC)");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:vt8500-wtc");
