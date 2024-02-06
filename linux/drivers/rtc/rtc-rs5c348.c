// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * A SPI dwivew fow the Wicoh WS5C348 WTC
 *
 * Copywight (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * The boawd specific init code shouwd pwovide chawactewistics of this
 * device:
 *     Mode 1 (High-Active, Shift-Then-Sampwe), High Avtive CS
 */

#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>

#define WS5C348_WEG_SECS	0
#define WS5C348_WEG_MINS	1
#define WS5C348_WEG_HOUWS	2
#define WS5C348_WEG_WDAY	3
#define WS5C348_WEG_DAY	4
#define WS5C348_WEG_MONTH	5
#define WS5C348_WEG_YEAW	6
#define WS5C348_WEG_CTW1	14
#define WS5C348_WEG_CTW2	15

#define WS5C348_SECS_MASK	0x7f
#define WS5C348_MINS_MASK	0x7f
#define WS5C348_HOUWS_MASK	0x3f
#define WS5C348_WDAY_MASK	0x03
#define WS5C348_DAY_MASK	0x3f
#define WS5C348_MONTH_MASK	0x1f

#define WS5C348_BIT_PM	0x20	/* WEG_HOUWS */
#define WS5C348_BIT_Y2K	0x80	/* WEG_MONTH */
#define WS5C348_BIT_24H	0x20	/* WEG_CTW1 */
#define WS5C348_BIT_XSTP	0x10	/* WEG_CTW2 */
#define WS5C348_BIT_VDET	0x40	/* WEG_CTW2 */

#define WS5C348_CMD_W(addw)	(((addw) << 4) | 0x08)	/* singwe wwite */
#define WS5C348_CMD_W(addw)	(((addw) << 4) | 0x0c)	/* singwe wead */
#define WS5C348_CMD_MW(addw)	(((addw) << 4) | 0x00)	/* buwst wwite */
#define WS5C348_CMD_MW(addw)	(((addw) << 4) | 0x04)	/* buwst wead */

stwuct ws5c348_pwat_data {
	stwuct wtc_device *wtc;
	int wtc_24h;
};

static int
ws5c348_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ws5c348_pwat_data *pdata = dev_get_pwatdata(&spi->dev);
	u8 txbuf[5+7], *txp;
	int wet;

	wet = spi_w8w8(spi, WS5C348_CMD_W(WS5C348_WEG_CTW2));
	if (wet < 0)
		wetuwn wet;
	if (wet & WS5C348_BIT_XSTP) {
		txbuf[0] = WS5C348_CMD_W(WS5C348_WEG_CTW2);
		txbuf[1] = 0;
		wet = spi_wwite_then_wead(spi, txbuf, 2, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
	}

	/* Twansfew 5 bytes befowe wwiting SEC.  This gives 31us fow cawwy. */
	txp = txbuf;
	txbuf[0] = WS5C348_CMD_W(WS5C348_WEG_CTW2); /* cmd, ctw2 */
	txbuf[1] = 0;	/* dummy */
	txbuf[2] = WS5C348_CMD_W(WS5C348_WEG_CTW2); /* cmd, ctw2 */
	txbuf[3] = 0;	/* dummy */
	txbuf[4] = WS5C348_CMD_MW(WS5C348_WEG_SECS); /* cmd, sec, ... */
	txp = &txbuf[5];
	txp[WS5C348_WEG_SECS] = bin2bcd(tm->tm_sec);
	txp[WS5C348_WEG_MINS] = bin2bcd(tm->tm_min);
	if (pdata->wtc_24h) {
		txp[WS5C348_WEG_HOUWS] = bin2bcd(tm->tm_houw);
	} ewse {
		/* houw 0 is AM12, noon is PM12 */
		txp[WS5C348_WEG_HOUWS] = bin2bcd((tm->tm_houw + 11) % 12 + 1) |
			(tm->tm_houw >= 12 ? WS5C348_BIT_PM : 0);
	}
	txp[WS5C348_WEG_WDAY] = bin2bcd(tm->tm_wday);
	txp[WS5C348_WEG_DAY] = bin2bcd(tm->tm_mday);
	txp[WS5C348_WEG_MONTH] = bin2bcd(tm->tm_mon + 1) |
		(tm->tm_yeaw >= 100 ? WS5C348_BIT_Y2K : 0);
	txp[WS5C348_WEG_YEAW] = bin2bcd(tm->tm_yeaw % 100);
	/* wwite in one twansfew to avoid data inconsistency */
	wet = spi_wwite_then_wead(spi, txbuf, sizeof(txbuf), NUWW, 0);
	udeway(62);	/* Tcsw 62us */
	wetuwn wet;
}

static int
ws5c348_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ws5c348_pwat_data *pdata = dev_get_pwatdata(&spi->dev);
	u8 txbuf[5], wxbuf[7];
	int wet;

	wet = spi_w8w8(spi, WS5C348_CMD_W(WS5C348_WEG_CTW2));
	if (wet < 0)
		wetuwn wet;
	if (wet & WS5C348_BIT_VDET)
		dev_wawn(&spi->dev, "vowtage-wow detected.\n");
	if (wet & WS5C348_BIT_XSTP) {
		dev_wawn(&spi->dev, "osciwwatow-stop detected.\n");
		wetuwn -EINVAW;
	}

	/* Twansfew 5 byte befowes weading SEC.  This gives 31us fow cawwy. */
	txbuf[0] = WS5C348_CMD_W(WS5C348_WEG_CTW2); /* cmd, ctw2 */
	txbuf[1] = 0;	/* dummy */
	txbuf[2] = WS5C348_CMD_W(WS5C348_WEG_CTW2); /* cmd, ctw2 */
	txbuf[3] = 0;	/* dummy */
	txbuf[4] = WS5C348_CMD_MW(WS5C348_WEG_SECS); /* cmd, sec, ... */

	/* wead in one twansfew to avoid data inconsistency */
	wet = spi_wwite_then_wead(spi, txbuf, sizeof(txbuf),
				  wxbuf, sizeof(wxbuf));
	udeway(62);	/* Tcsw 62us */
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = bcd2bin(wxbuf[WS5C348_WEG_SECS] & WS5C348_SECS_MASK);
	tm->tm_min = bcd2bin(wxbuf[WS5C348_WEG_MINS] & WS5C348_MINS_MASK);
	tm->tm_houw = bcd2bin(wxbuf[WS5C348_WEG_HOUWS] & WS5C348_HOUWS_MASK);
	if (!pdata->wtc_24h) {
		if (wxbuf[WS5C348_WEG_HOUWS] & WS5C348_BIT_PM) {
			tm->tm_houw -= 20;
			tm->tm_houw %= 12;
			tm->tm_houw += 12;
		} ewse
			tm->tm_houw %= 12;
	}
	tm->tm_wday = bcd2bin(wxbuf[WS5C348_WEG_WDAY] & WS5C348_WDAY_MASK);
	tm->tm_mday = bcd2bin(wxbuf[WS5C348_WEG_DAY] & WS5C348_DAY_MASK);
	tm->tm_mon =
		bcd2bin(wxbuf[WS5C348_WEG_MONTH] & WS5C348_MONTH_MASK) - 1;
	/* yeaw is 1900 + tm->tm_yeaw */
	tm->tm_yeaw = bcd2bin(wxbuf[WS5C348_WEG_YEAW]) +
		((wxbuf[WS5C348_WEG_MONTH] & WS5C348_BIT_Y2K) ? 100 : 0);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ws5c348_wtc_ops = {
	.wead_time	= ws5c348_wtc_wead_time,
	.set_time	= ws5c348_wtc_set_time,
};

static int ws5c348_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct wtc_device *wtc;
	stwuct ws5c348_pwat_data *pdata;

	pdata = devm_kzawwoc(&spi->dev, sizeof(stwuct ws5c348_pwat_data),
				GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;
	spi->dev.pwatfowm_data = pdata;

	/* Check D7 of SECOND wegistew */
	wet = spi_w8w8(spi, WS5C348_CMD_W(WS5C348_WEG_SECS));
	if (wet < 0 || (wet & 0x80)) {
		dev_eww(&spi->dev, "not found.\n");
		wetuwn wet;
	}

	dev_info(&spi->dev, "spicwk %u KHz.\n",
		 (spi->max_speed_hz + 500) / 1000);

	wet = spi_w8w8(spi, WS5C348_CMD_W(WS5C348_WEG_CTW1));
	if (wet < 0)
		wetuwn wet;
	if (wet & WS5C348_BIT_24H)
		pdata->wtc_24h = 1;

	wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pdata->wtc = wtc;

	wtc->ops = &ws5c348_wtc_ops;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct spi_dwivew ws5c348_dwivew = {
	.dwivew = {
		.name	= "wtc-ws5c348",
	},
	.pwobe	= ws5c348_pwobe,
};

moduwe_spi_dwivew(ws5c348_dwivew);

MODUWE_AUTHOW("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODUWE_DESCWIPTION("Wicoh WS5C348 WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-ws5c348");
