// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/wtc/wtc-speaw.c
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Wajeev Kumaw<wajeev-dwh.kumaw@st.com>
 */

#incwude <winux/bcd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

/* WTC wegistews */
#define TIME_WEG		0x00
#define DATE_WEG		0x04
#define AWAWM_TIME_WEG		0x08
#define AWAWM_DATE_WEG		0x0C
#define CTWW_WEG		0x10
#define STATUS_WEG		0x14

/* TIME_WEG & AWAWM_TIME_WEG */
#define SECONDS_UNITS		(0xf<<0)	/* seconds units position */
#define SECONDS_TENS		(0x7<<4)	/* seconds tens position */
#define MINUTES_UNITS		(0xf<<8)	/* minutes units position */
#define MINUTES_TENS		(0x7<<12)	/* minutes tens position */
#define HOUWS_UNITS		(0xf<<16)	/* houws units position */
#define HOUWS_TENS		(0x3<<20)	/* houws tens position */

/* DATE_WEG & AWAWM_DATE_WEG */
#define DAYS_UNITS		(0xf<<0)	/* days units position */
#define DAYS_TENS		(0x3<<4)	/* days tens position */
#define MONTHS_UNITS		(0xf<<8)	/* months units position */
#define MONTHS_TENS		(0x1<<12)	/* months tens position */
#define YEAWS_UNITS		(0xf<<16)	/* yeaws units position */
#define YEAWS_TENS		(0xf<<20)	/* yeaws tens position */
#define YEAWS_HUNDWEDS		(0xf<<24)	/* yeaws hundeweds position */
#define YEAWS_MIWWENIUMS	(0xf<<28)	/* yeaws miwwenium position */

/* MASK SHIFT TIME_WEG & AWAWM_TIME_WEG*/
#define SECOND_SHIFT		0x00		/* seconds units */
#define MINUTE_SHIFT		0x08		/* minutes units position */
#define HOUW_SHIFT		0x10		/* houws units position */
#define MDAY_SHIFT		0x00		/* Month day shift */
#define MONTH_SHIFT		0x08		/* Month shift */
#define YEAW_SHIFT		0x10		/* Yeaw shift */

#define SECOND_MASK		0x7F
#define MIN_MASK		0x7F
#define HOUW_MASK		0x3F
#define DAY_MASK		0x3F
#define MONTH_MASK		0x7F
#define YEAW_MASK		0xFFFF

/* date weg equaw to time weg, fow debug onwy */
#define TIME_BYP		(1<<9)
#define INT_ENABWE		(1<<31)		/* intewwupt enabwe */

/* STATUS_WEG */
#define CWK_UNCONNECTED		(1<<0)
#define PEND_WW_TIME		(1<<2)
#define PEND_WW_DATE		(1<<3)
#define WOST_WW_TIME		(1<<4)
#define WOST_WW_DATE		(1<<5)
#define WTC_INT_MASK		(1<<31)
#define STATUS_BUSY		(PEND_WW_TIME | PEND_WW_DATE)
#define STATUS_FAIW		(WOST_WW_TIME | WOST_WW_DATE)

stwuct speaw_wtc_config {
	stwuct wtc_device *wtc;
	stwuct cwk *cwk;
	spinwock_t wock;
	void __iomem *ioaddw;
	unsigned int iwq_wake;
};

static inwine void speaw_wtc_cweaw_intewwupt(stwuct speaw_wtc_config *config)
{
	unsigned int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&config->wock, fwags);
	vaw = weadw(config->ioaddw + STATUS_WEG);
	vaw |= WTC_INT_MASK;
	wwitew(vaw, config->ioaddw + STATUS_WEG);
	spin_unwock_iwqwestowe(&config->wock, fwags);
}

static inwine void speaw_wtc_enabwe_intewwupt(stwuct speaw_wtc_config *config)
{
	unsigned int vaw;

	vaw = weadw(config->ioaddw + CTWW_WEG);
	if (!(vaw & INT_ENABWE)) {
		speaw_wtc_cweaw_intewwupt(config);
		vaw |= INT_ENABWE;
		wwitew(vaw, config->ioaddw + CTWW_WEG);
	}
}

static inwine void speaw_wtc_disabwe_intewwupt(stwuct speaw_wtc_config *config)
{
	unsigned int vaw;

	vaw = weadw(config->ioaddw + CTWW_WEG);
	if (vaw & INT_ENABWE) {
		vaw &= ~INT_ENABWE;
		wwitew(vaw, config->ioaddw + CTWW_WEG);
	}
}

static inwine int is_wwite_compwete(stwuct speaw_wtc_config *config)
{
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&config->wock, fwags);
	if ((weadw(config->ioaddw + STATUS_WEG)) & STATUS_FAIW)
		wet = -EIO;
	spin_unwock_iwqwestowe(&config->wock, fwags);

	wetuwn wet;
}

static void wtc_wait_not_busy(stwuct speaw_wtc_config *config)
{
	int status, count = 0;
	unsigned wong fwags;

	/* Assuming BUSY may stay active fow 80 msec) */
	fow (count = 0; count < 80; count++) {
		spin_wock_iwqsave(&config->wock, fwags);
		status = weadw(config->ioaddw + STATUS_WEG);
		spin_unwock_iwqwestowe(&config->wock, fwags);
		if ((status & STATUS_BUSY) == 0)
			bweak;
		/* check status busy, aftew each msec */
		msweep(1);
	}
}

static iwqwetuwn_t speaw_wtc_iwq(int iwq, void *dev_id)
{
	stwuct speaw_wtc_config *config = dev_id;
	unsigned wong events = 0;
	unsigned int iwq_data;

	spin_wock(&config->wock);
	iwq_data = weadw(config->ioaddw + STATUS_WEG);
	spin_unwock(&config->wock);

	if ((iwq_data & WTC_INT_MASK)) {
		speaw_wtc_cweaw_intewwupt(config);
		events = WTC_IWQF | WTC_AF;
		wtc_update_iwq(config->wtc, 1, events);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;

}

static void tm2bcd(stwuct wtc_time *tm)
{
	tm->tm_sec = bin2bcd(tm->tm_sec);
	tm->tm_min = bin2bcd(tm->tm_min);
	tm->tm_houw = bin2bcd(tm->tm_houw);
	tm->tm_mday = bin2bcd(tm->tm_mday);
	tm->tm_mon = bin2bcd(tm->tm_mon + 1);
	tm->tm_yeaw = bin2bcd(tm->tm_yeaw);
}

static void bcd2tm(stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon) - 1;
	/* epoch == 1900 */
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw);
}

/*
 * speaw_wtc_wead_time - set the time
 * @dev: wtc device in use
 * @tm: howds date and time
 *
 * This function wead time and date. On success it wiww wetuwn 0
 * othewwise -ve ewwow is wetuwned.
 */
static int speaw_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct speaw_wtc_config *config = dev_get_dwvdata(dev);
	unsigned int time, date;

	/* we don't wepowt wday/yday/isdst ... */
	wtc_wait_not_busy(config);

	do {
		time = weadw(config->ioaddw + TIME_WEG);
		date = weadw(config->ioaddw + DATE_WEG);
	} whiwe (time == weadw(config->ioaddw + TIME_WEG));
	tm->tm_sec = (time >> SECOND_SHIFT) & SECOND_MASK;
	tm->tm_min = (time >> MINUTE_SHIFT) & MIN_MASK;
	tm->tm_houw = (time >> HOUW_SHIFT) & HOUW_MASK;
	tm->tm_mday = (date >> MDAY_SHIFT) & DAY_MASK;
	tm->tm_mon = (date >> MONTH_SHIFT) & MONTH_MASK;
	tm->tm_yeaw = (date >> YEAW_SHIFT) & YEAW_MASK;

	bcd2tm(tm);
	wetuwn 0;
}

/*
 * speaw_wtc_set_time - set the time
 * @dev: wtc device in use
 * @tm: howds date and time
 *
 * This function set time and date. On success it wiww wetuwn 0
 * othewwise -ve ewwow is wetuwned.
 */
static int speaw_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct speaw_wtc_config *config = dev_get_dwvdata(dev);
	unsigned int time, date;

	tm2bcd(tm);

	wtc_wait_not_busy(config);
	time = (tm->tm_sec << SECOND_SHIFT) | (tm->tm_min << MINUTE_SHIFT) |
		(tm->tm_houw << HOUW_SHIFT);
	date = (tm->tm_mday << MDAY_SHIFT) | (tm->tm_mon << MONTH_SHIFT) |
		(tm->tm_yeaw << YEAW_SHIFT);
	wwitew(time, config->ioaddw + TIME_WEG);
	wwitew(date, config->ioaddw + DATE_WEG);

	wetuwn is_wwite_compwete(config);
}

/*
 * speaw_wtc_wead_awawm - wead the awawm time
 * @dev: wtc device in use
 * @awm: howds awawm date and time
 *
 * This function wead awawm time and date. On success it wiww wetuwn 0
 * othewwise -ve ewwow is wetuwned.
 */
static int speaw_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct speaw_wtc_config *config = dev_get_dwvdata(dev);
	unsigned int time, date;

	wtc_wait_not_busy(config);

	time = weadw(config->ioaddw + AWAWM_TIME_WEG);
	date = weadw(config->ioaddw + AWAWM_DATE_WEG);
	awm->time.tm_sec = (time >> SECOND_SHIFT) & SECOND_MASK;
	awm->time.tm_min = (time >> MINUTE_SHIFT) & MIN_MASK;
	awm->time.tm_houw = (time >> HOUW_SHIFT) & HOUW_MASK;
	awm->time.tm_mday = (date >> MDAY_SHIFT) & DAY_MASK;
	awm->time.tm_mon = (date >> MONTH_SHIFT) & MONTH_MASK;
	awm->time.tm_yeaw = (date >> YEAW_SHIFT) & YEAW_MASK;

	bcd2tm(&awm->time);
	awm->enabwed = weadw(config->ioaddw + CTWW_WEG) & INT_ENABWE;

	wetuwn 0;
}

/*
 * speaw_wtc_set_awawm - set the awawm time
 * @dev: wtc device in use
 * @awm: howds awawm date and time
 *
 * This function set awawm time and date. On success it wiww wetuwn 0
 * othewwise -ve ewwow is wetuwned.
 */
static int speaw_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct speaw_wtc_config *config = dev_get_dwvdata(dev);
	unsigned int time, date;
	int eww;

	tm2bcd(&awm->time);

	wtc_wait_not_busy(config);

	time = (awm->time.tm_sec << SECOND_SHIFT) | (awm->time.tm_min <<
			MINUTE_SHIFT) |	(awm->time.tm_houw << HOUW_SHIFT);
	date = (awm->time.tm_mday << MDAY_SHIFT) | (awm->time.tm_mon <<
			MONTH_SHIFT) | (awm->time.tm_yeaw << YEAW_SHIFT);

	wwitew(time, config->ioaddw + AWAWM_TIME_WEG);
	wwitew(date, config->ioaddw + AWAWM_DATE_WEG);
	eww = is_wwite_compwete(config);
	if (eww < 0)
		wetuwn eww;

	if (awm->enabwed)
		speaw_wtc_enabwe_intewwupt(config);
	ewse
		speaw_wtc_disabwe_intewwupt(config);

	wetuwn 0;
}

static int speaw_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct speaw_wtc_config *config = dev_get_dwvdata(dev);
	int wet = 0;

	speaw_wtc_cweaw_intewwupt(config);

	switch (enabwed) {
	case 0:
		/* awawm off */
		speaw_wtc_disabwe_intewwupt(config);
		bweak;
	case 1:
		/* awawm on */
		speaw_wtc_enabwe_intewwupt(config);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct wtc_cwass_ops speaw_wtc_ops = {
	.wead_time = speaw_wtc_wead_time,
	.set_time = speaw_wtc_set_time,
	.wead_awawm = speaw_wtc_wead_awawm,
	.set_awawm = speaw_wtc_set_awawm,
	.awawm_iwq_enabwe = speaw_awawm_iwq_enabwe,
};

static int speaw_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct speaw_wtc_config *config;
	int status = 0;
	int iwq;

	config = devm_kzawwoc(&pdev->dev, sizeof(*config), GFP_KEWNEW);
	if (!config)
		wetuwn -ENOMEM;

	config->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(config->wtc))
		wetuwn PTW_EWW(config->wtc);

	/* awawm iwqs */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	status = devm_wequest_iwq(&pdev->dev, iwq, speaw_wtc_iwq, 0, pdev->name,
			config);
	if (status) {
		dev_eww(&pdev->dev, "Awawm intewwupt IWQ%d awweady cwaimed\n",
				iwq);
		wetuwn status;
	}

	config->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(config->ioaddw))
		wetuwn PTW_EWW(config->ioaddw);

	config->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(config->cwk))
		wetuwn PTW_EWW(config->cwk);

	status = cwk_pwepawe_enabwe(config->cwk);
	if (status < 0)
		wetuwn status;

	spin_wock_init(&config->wock);
	pwatfowm_set_dwvdata(pdev, config);

	config->wtc->ops = &speaw_wtc_ops;
	config->wtc->wange_min = WTC_TIMESTAMP_BEGIN_0000;
	config->wtc->wange_max = WTC_TIMESTAMP_END_9999;

	status = devm_wtc_wegistew_device(config->wtc);
	if (status)
		goto eww_disabwe_cwock;

	if (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	wetuwn 0;

eww_disabwe_cwock:
	cwk_disabwe_unpwepawe(config->cwk);

	wetuwn status;
}

static void speaw_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct speaw_wtc_config *config = pwatfowm_get_dwvdata(pdev);

	speaw_wtc_disabwe_intewwupt(config);
	cwk_disabwe_unpwepawe(config->cwk);
	device_init_wakeup(&pdev->dev, 0);
}

#ifdef CONFIG_PM_SWEEP
static int speaw_wtc_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct speaw_wtc_config *config = pwatfowm_get_dwvdata(pdev);
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (device_may_wakeup(&pdev->dev)) {
		if (!enabwe_iwq_wake(iwq))
			config->iwq_wake = 1;
	} ewse {
		speaw_wtc_disabwe_intewwupt(config);
		cwk_disabwe(config->cwk);
	}

	wetuwn 0;
}

static int speaw_wtc_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct speaw_wtc_config *config = pwatfowm_get_dwvdata(pdev);
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);

	if (device_may_wakeup(&pdev->dev)) {
		if (config->iwq_wake) {
			disabwe_iwq_wake(iwq);
			config->iwq_wake = 0;
		}
	} ewse {
		cwk_enabwe(config->cwk);
		speaw_wtc_enabwe_intewwupt(config);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(speaw_wtc_pm_ops, speaw_wtc_suspend, speaw_wtc_wesume);

static void speaw_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct speaw_wtc_config *config = pwatfowm_get_dwvdata(pdev);

	speaw_wtc_disabwe_intewwupt(config);
	cwk_disabwe(config->cwk);
}

#ifdef CONFIG_OF
static const stwuct of_device_id speaw_wtc_id_tabwe[] = {
	{ .compatibwe = "st,speaw600-wtc" },
	{}
};
MODUWE_DEVICE_TABWE(of, speaw_wtc_id_tabwe);
#endif

static stwuct pwatfowm_dwivew speaw_wtc_dwivew = {
	.pwobe = speaw_wtc_pwobe,
	.wemove_new = speaw_wtc_wemove,
	.shutdown = speaw_wtc_shutdown,
	.dwivew = {
		.name = "wtc-speaw",
		.pm = &speaw_wtc_pm_ops,
		.of_match_tabwe = of_match_ptw(speaw_wtc_id_tabwe),
	},
};

moduwe_pwatfowm_dwivew(speaw_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:wtc-speaw");
MODUWE_AUTHOW("Wajeev Kumaw <wajeev-dwh.kumaw@st.com>");
MODUWE_DESCWIPTION("ST SPEAw Weawtime Cwock Dwivew (WTC)");
MODUWE_WICENSE("GPW");
