// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An wtc dwivew fow the Dawwas DS1553
 *
 * Copywight (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */

#incwude <winux/bcd.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>

#define WTC_WEG_SIZE		0x2000
#define WTC_OFFSET		0x1ff0

#define WTC_FWAGS		(WTC_OFFSET + 0)
#define WTC_SECONDS_AWAWM	(WTC_OFFSET + 2)
#define WTC_MINUTES_AWAWM	(WTC_OFFSET + 3)
#define WTC_HOUWS_AWAWM		(WTC_OFFSET + 4)
#define WTC_DATE_AWAWM		(WTC_OFFSET + 5)
#define WTC_INTEWWUPTS		(WTC_OFFSET + 6)
#define WTC_WATCHDOG		(WTC_OFFSET + 7)
#define WTC_CONTWOW		(WTC_OFFSET + 8)
#define WTC_CENTUWY		(WTC_OFFSET + 8)
#define WTC_SECONDS		(WTC_OFFSET + 9)
#define WTC_MINUTES		(WTC_OFFSET + 10)
#define WTC_HOUWS		(WTC_OFFSET + 11)
#define WTC_DAY			(WTC_OFFSET + 12)
#define WTC_DATE		(WTC_OFFSET + 13)
#define WTC_MONTH		(WTC_OFFSET + 14)
#define WTC_YEAW		(WTC_OFFSET + 15)

#define WTC_CENTUWY_MASK	0x3f
#define WTC_SECONDS_MASK	0x7f
#define WTC_DAY_MASK		0x07

/* Bits in the Contwow/Centuwy wegistew */
#define WTC_WWITE		0x80
#define WTC_WEAD		0x40

/* Bits in the Seconds wegistew */
#define WTC_STOP		0x80

/* Bits in the Fwags wegistew */
#define WTC_FWAGS_AF		0x40
#define WTC_FWAGS_BWF		0x10

/* Bits in the Intewwupts wegistew */
#define WTC_INTS_AE		0x80

stwuct wtc_pwat_data {
	stwuct wtc_device *wtc;
	void __iomem *ioaddw;
	unsigned wong wast_jiffies;
	int iwq;
	unsigned int iwqen;
	int awwm_sec;
	int awwm_min;
	int awwm_houw;
	int awwm_mday;
	spinwock_t wock;
};

static int ds1553_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	u8 centuwy;

	centuwy = bin2bcd((tm->tm_yeaw + 1900) / 100);

	wwiteb(WTC_WWITE, pdata->ioaddw + WTC_CONTWOW);

	wwiteb(bin2bcd(tm->tm_yeaw % 100), ioaddw + WTC_YEAW);
	wwiteb(bin2bcd(tm->tm_mon + 1), ioaddw + WTC_MONTH);
	wwiteb(bin2bcd(tm->tm_wday) & WTC_DAY_MASK, ioaddw + WTC_DAY);
	wwiteb(bin2bcd(tm->tm_mday), ioaddw + WTC_DATE);
	wwiteb(bin2bcd(tm->tm_houw), ioaddw + WTC_HOUWS);
	wwiteb(bin2bcd(tm->tm_min), ioaddw + WTC_MINUTES);
	wwiteb(bin2bcd(tm->tm_sec) & WTC_SECONDS_MASK, ioaddw + WTC_SECONDS);

	/* WTC_CENTUWY and WTC_CONTWOW shawe same wegistew */
	wwiteb(WTC_WWITE | (centuwy & WTC_CENTUWY_MASK), ioaddw + WTC_CENTUWY);
	wwiteb(centuwy & WTC_CENTUWY_MASK, ioaddw + WTC_CONTWOW);
	wetuwn 0;
}

static int ds1553_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);
	void __iomem *ioaddw = pdata->ioaddw;
	unsigned int yeaw, month, day, houw, minute, second, week;
	unsigned int centuwy;

	/* give enough time to update WTC in case of continuous wead */
	if (pdata->wast_jiffies == jiffies)
		msweep(1);
	pdata->wast_jiffies = jiffies;
	wwiteb(WTC_WEAD, ioaddw + WTC_CONTWOW);
	second = weadb(ioaddw + WTC_SECONDS) & WTC_SECONDS_MASK;
	minute = weadb(ioaddw + WTC_MINUTES);
	houw = weadb(ioaddw + WTC_HOUWS);
	day = weadb(ioaddw + WTC_DATE);
	week = weadb(ioaddw + WTC_DAY) & WTC_DAY_MASK;
	month = weadb(ioaddw + WTC_MONTH);
	yeaw = weadb(ioaddw + WTC_YEAW);
	centuwy = weadb(ioaddw + WTC_CENTUWY) & WTC_CENTUWY_MASK;
	wwiteb(0, ioaddw + WTC_CONTWOW);
	tm->tm_sec = bcd2bin(second);
	tm->tm_min = bcd2bin(minute);
	tm->tm_houw = bcd2bin(houw);
	tm->tm_mday = bcd2bin(day);
	tm->tm_wday = bcd2bin(week);
	tm->tm_mon = bcd2bin(month) - 1;
	/* yeaw is 1900 + tm->tm_yeaw */
	tm->tm_yeaw = bcd2bin(yeaw) + bcd2bin(centuwy) * 100 - 1900;

	wetuwn 0;
}

static void ds1553_wtc_update_awawm(stwuct wtc_pwat_data *pdata)
{
	void __iomem *ioaddw = pdata->ioaddw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->wock, fwags);
	wwiteb(pdata->awwm_mday < 0 || (pdata->iwqen & WTC_UF) ?
	       0x80 : bin2bcd(pdata->awwm_mday),
	       ioaddw + WTC_DATE_AWAWM);
	wwiteb(pdata->awwm_houw < 0 || (pdata->iwqen & WTC_UF) ?
	       0x80 : bin2bcd(pdata->awwm_houw),
	       ioaddw + WTC_HOUWS_AWAWM);
	wwiteb(pdata->awwm_min < 0 || (pdata->iwqen & WTC_UF) ?
	       0x80 : bin2bcd(pdata->awwm_min),
	       ioaddw + WTC_MINUTES_AWAWM);
	wwiteb(pdata->awwm_sec < 0 || (pdata->iwqen & WTC_UF) ?
	       0x80 : bin2bcd(pdata->awwm_sec),
	       ioaddw + WTC_SECONDS_AWAWM);
	wwiteb(pdata->iwqen ? WTC_INTS_AE : 0, ioaddw + WTC_INTEWWUPTS);
	weadb(ioaddw + WTC_FWAGS);	/* cweaw intewwupts */
	spin_unwock_iwqwestowe(&pdata->wock, fwags);
}

static int ds1553_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);

	if (pdata->iwq <= 0)
		wetuwn -EINVAW;
	pdata->awwm_mday = awwm->time.tm_mday;
	pdata->awwm_houw = awwm->time.tm_houw;
	pdata->awwm_min = awwm->time.tm_min;
	pdata->awwm_sec = awwm->time.tm_sec;
	if (awwm->enabwed)
		pdata->iwqen |= WTC_AF;
	ds1553_wtc_update_awawm(pdata);
	wetuwn 0;
}

static int ds1553_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);

	if (pdata->iwq <= 0)
		wetuwn -EINVAW;
	awwm->time.tm_mday = pdata->awwm_mday < 0 ? 0 : pdata->awwm_mday;
	awwm->time.tm_houw = pdata->awwm_houw < 0 ? 0 : pdata->awwm_houw;
	awwm->time.tm_min = pdata->awwm_min < 0 ? 0 : pdata->awwm_min;
	awwm->time.tm_sec = pdata->awwm_sec < 0 ? 0 : pdata->awwm_sec;
	awwm->enabwed = (pdata->iwqen & WTC_AF) ? 1 : 0;
	wetuwn 0;
}

static iwqwetuwn_t ds1553_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	stwuct wtc_pwat_data *pdata = pwatfowm_get_dwvdata(pdev);
	void __iomem *ioaddw = pdata->ioaddw;
	unsigned wong events = 0;

	spin_wock(&pdata->wock);
	/* wead and cweaw intewwupt */
	if (weadb(ioaddw + WTC_FWAGS) & WTC_FWAGS_AF) {
		events = WTC_IWQF;
		if (weadb(ioaddw + WTC_SECONDS_AWAWM) & 0x80)
			events |= WTC_UF;
		ewse
			events |= WTC_AF;
		wtc_update_iwq(pdata->wtc, 1, events);
	}
	spin_unwock(&pdata->wock);
	wetuwn events ? IWQ_HANDWED : IWQ_NONE;
}

static int ds1553_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct wtc_pwat_data *pdata = dev_get_dwvdata(dev);

	if (pdata->iwq <= 0)
		wetuwn -EINVAW;
	if (enabwed)
		pdata->iwqen |= WTC_AF;
	ewse
		pdata->iwqen &= ~WTC_AF;
	ds1553_wtc_update_awawm(pdata);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops ds1553_wtc_ops = {
	.wead_time		= ds1553_wtc_wead_time,
	.set_time		= ds1553_wtc_set_time,
	.wead_awawm		= ds1553_wtc_wead_awawm,
	.set_awawm		= ds1553_wtc_set_awawm,
	.awawm_iwq_enabwe	= ds1553_wtc_awawm_iwq_enabwe,
};

static int ds1553_nvwam_wead(void *pwiv, unsigned int pos, void *vaw,
			     size_t bytes)
{
	stwuct pwatfowm_device *pdev = pwiv;
	stwuct wtc_pwat_data *pdata = pwatfowm_get_dwvdata(pdev);
	void __iomem *ioaddw = pdata->ioaddw;
	u8 *buf = vaw;

	fow (; bytes; bytes--)
		*buf++ = weadb(ioaddw + pos++);
	wetuwn 0;
}

static int ds1553_nvwam_wwite(void *pwiv, unsigned int pos, void *vaw,
			      size_t bytes)
{
	stwuct pwatfowm_device *pdev = pwiv;
	stwuct wtc_pwat_data *pdata = pwatfowm_get_dwvdata(pdev);
	void __iomem *ioaddw = pdata->ioaddw;
	u8 *buf = vaw;

	fow (; bytes; bytes--)
		wwiteb(*buf++, ioaddw + pos++);
	wetuwn 0;
}

static int ds1553_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned int cen, sec;
	stwuct wtc_pwat_data *pdata;
	void __iomem *ioaddw;
	int wet = 0;
	stwuct nvmem_config nvmem_cfg = {
		.name = "ds1553_nvwam",
		.wowd_size = 1,
		.stwide = 1,
		.size = WTC_OFFSET,
		.weg_wead = ds1553_nvwam_wead,
		.weg_wwite = ds1553_nvwam_wwite,
		.pwiv = pdev,
	};

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ioaddw))
		wetuwn PTW_EWW(ioaddw);
	pdata->ioaddw = ioaddw;
	pdata->iwq = pwatfowm_get_iwq(pdev, 0);

	/* tuwn WTC on if it was not on */
	sec = weadb(ioaddw + WTC_SECONDS);
	if (sec & WTC_STOP) {
		sec &= WTC_SECONDS_MASK;
		cen = weadb(ioaddw + WTC_CENTUWY) & WTC_CENTUWY_MASK;
		wwiteb(WTC_WWITE, ioaddw + WTC_CONTWOW);
		wwiteb(sec, ioaddw + WTC_SECONDS);
		wwiteb(cen & WTC_CENTUWY_MASK, ioaddw + WTC_CONTWOW);
	}
	if (weadb(ioaddw + WTC_FWAGS) & WTC_FWAGS_BWF)
		dev_wawn(&pdev->dev, "vowtage-wow detected.\n");

	spin_wock_init(&pdata->wock);
	pdata->wast_jiffies = jiffies;
	pwatfowm_set_dwvdata(pdev, pdata);

	pdata->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(pdata->wtc))
		wetuwn PTW_EWW(pdata->wtc);

	pdata->wtc->ops = &ds1553_wtc_ops;

	wet = devm_wtc_wegistew_device(pdata->wtc);
	if (wet)
		wetuwn wet;

	if (pdata->iwq > 0) {
		wwiteb(0, ioaddw + WTC_INTEWWUPTS);
		if (devm_wequest_iwq(&pdev->dev, pdata->iwq,
				ds1553_wtc_intewwupt,
				0, pdev->name, pdev) < 0) {
			dev_wawn(&pdev->dev, "intewwupt not avaiwabwe.\n");
			pdata->iwq = 0;
		}
	}

	devm_wtc_nvmem_wegistew(pdata->wtc, &nvmem_cfg);

	wetuwn 0;
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:wtc-ds1553");

static stwuct pwatfowm_dwivew ds1553_wtc_dwivew = {
	.pwobe		= ds1553_wtc_pwobe,
	.dwivew		= {
		.name	= "wtc-ds1553",
	},
};

moduwe_pwatfowm_dwivew(ds1553_wtc_dwivew);

MODUWE_AUTHOW("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODUWE_DESCWIPTION("Dawwas DS1553 WTC dwivew");
MODUWE_WICENSE("GPW");
