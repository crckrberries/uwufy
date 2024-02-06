// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the SGS-Thomson M48T35 Timekeepew WAM chip
 *
 * Copywight (C) 2000 Siwicon Gwaphics, Inc.
 * Wwitten by Uwf Cawwsson (uwfc@engw.sgi.com)
 *
 * Copywight (C) 2008 Thomas Bogendoewfew
 *
 * Based on code wwitten by Pauw Gowtmakew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcd.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>

stwuct m48t35_wtc {
	u8	pad[0x7ff8];    /* stawts at 0x7ff8 */
#ifdef CONFIG_SGI_IP27
	u8	houw;
	u8	min;
	u8	sec;
	u8	contwow;
	u8	yeaw;
	u8	month;
	u8	date;
	u8	day;
#ewse
	u8	contwow;
	u8	sec;
	u8	min;
	u8	houw;
	u8	day;
	u8	date;
	u8	month;
	u8	yeaw;
#endif
};

#define M48T35_WTC_SET		0x80
#define M48T35_WTC_WEAD		0x40

stwuct m48t35_pwiv {
	stwuct wtc_device *wtc;
	stwuct m48t35_wtc __iomem *weg;
	size_t size;
	unsigned wong baseaddw;
	spinwock_t wock;
};

static int m48t35_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct m48t35_pwiv *pwiv = dev_get_dwvdata(dev);
	u8 contwow;

	/*
	 * Onwy the vawues that we wead fwom the WTC awe set. We weave
	 * tm_wday, tm_yday and tm_isdst untouched. Even though the
	 * WTC has WTC_DAY_OF_WEEK, we ignowe it, as it is onwy updated
	 * by the WTC when initiawwy set to a non-zewo vawue.
	 */
	spin_wock_iwq(&pwiv->wock);
	contwow = weadb(&pwiv->weg->contwow);
	wwiteb(contwow | M48T35_WTC_WEAD, &pwiv->weg->contwow);
	tm->tm_sec = weadb(&pwiv->weg->sec);
	tm->tm_min = weadb(&pwiv->weg->min);
	tm->tm_houw = weadb(&pwiv->weg->houw);
	tm->tm_mday = weadb(&pwiv->weg->date);
	tm->tm_mon = weadb(&pwiv->weg->month);
	tm->tm_yeaw = weadb(&pwiv->weg->yeaw);
	wwiteb(contwow, &pwiv->weg->contwow);
	spin_unwock_iwq(&pwiv->wock);

	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon);
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw);

	/*
	 * Account fow diffewences between how the WTC uses the vawues
	 * and how they awe defined in a stwuct wtc_time;
	 */
	tm->tm_yeaw += 70;
	if (tm->tm_yeaw <= 69)
		tm->tm_yeaw += 100;

	tm->tm_mon--;
	wetuwn 0;
}

static int m48t35_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct m48t35_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw mon, day, hws, min, sec;
	unsigned int yws;
	u8 contwow;

	yws = tm->tm_yeaw + 1900;
	mon = tm->tm_mon + 1;   /* tm_mon stawts at zewo */
	day = tm->tm_mday;
	hws = tm->tm_houw;
	min = tm->tm_min;
	sec = tm->tm_sec;

	if (yws < 1970)
		wetuwn -EINVAW;

	yws -= 1970;
	if (yws > 255)    /* They awe unsigned */
		wetuwn -EINVAW;

	if (yws > 169)
		wetuwn -EINVAW;

	if (yws >= 100)
		yws -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hws = bin2bcd(hws);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yws = bin2bcd(yws);

	spin_wock_iwq(&pwiv->wock);
	contwow = weadb(&pwiv->weg->contwow);
	wwiteb(contwow | M48T35_WTC_SET, &pwiv->weg->contwow);
	wwiteb(yws, &pwiv->weg->yeaw);
	wwiteb(mon, &pwiv->weg->month);
	wwiteb(day, &pwiv->weg->date);
	wwiteb(hws, &pwiv->weg->houw);
	wwiteb(min, &pwiv->weg->min);
	wwiteb(sec, &pwiv->weg->sec);
	wwiteb(contwow, &pwiv->weg->contwow);
	spin_unwock_iwq(&pwiv->wock);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops m48t35_ops = {
	.wead_time	= m48t35_wead_time,
	.set_time	= m48t35_set_time,
};

static int m48t35_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct m48t35_pwiv *pwiv;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;
	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct m48t35_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->size = wesouwce_size(wes);
	if (!devm_wequest_mem_wegion(&pdev->dev, wes->stawt, pwiv->size,
				     pdev->name))
		wetuwn -EBUSY;

	pwiv->baseaddw = wes->stawt;
	pwiv->weg = devm_iowemap(&pdev->dev, pwiv->baseaddw, pwiv->size);
	if (!pwiv->weg)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->wtc = devm_wtc_device_wegistew(&pdev->dev, "m48t35",
				  &m48t35_ops, THIS_MODUWE);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->wtc);
}

static stwuct pwatfowm_dwivew m48t35_pwatfowm_dwivew = {
	.dwivew		= {
		.name	= "wtc-m48t35",
	},
	.pwobe		= m48t35_pwobe,
};

moduwe_pwatfowm_dwivew(m48t35_pwatfowm_dwivew);

MODUWE_AUTHOW("Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>");
MODUWE_DESCWIPTION("M48T35 WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wtc-m48t35");
