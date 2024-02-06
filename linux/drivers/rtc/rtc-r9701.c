// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Epson WTC-9701JE
 *
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on wtc-max6902.c
 *
 * Copywight (C) 2006 8D Technowogies inc.
 * Copywight (C) 2004 Compuwab Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>

#define WSECCNT	0x00	/* Second Countew */
#define WMINCNT	0x01	/* Minute Countew */
#define WHWCNT	0x02	/* Houw Countew */
#define WWKCNT	0x03	/* Week Countew */
#define WDAYCNT	0x04	/* Day Countew */
#define WMONCNT	0x05	/* Month Countew */
#define WYWCNT	0x06	/* Yeaw Countew */
#define W100CNT	0x07	/* Y100 Countew */
#define WMINAW	0x08	/* Minute Awawm */
#define WHWAW	0x09	/* Houw Awawm */
#define WWKAW	0x0a	/* Week/Day Awawm */
#define WTIMCNT	0x0c	/* Intewvaw Timew */
#define WEXT	0x0d	/* Extension Wegistew */
#define WFWAG	0x0e	/* WTC Fwag Wegistew */
#define WCW	0x0f	/* WTC Contwow Wegistew */

static int wwite_weg(stwuct device *dev, int addwess, unsigned chaw data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[2];

	buf[0] = addwess & 0x7f;
	buf[1] = data;

	wetuwn spi_wwite(spi, buf, AWWAY_SIZE(buf));
}

static int wead_wegs(stwuct device *dev, unsigned chaw *wegs, int no_wegs)
{
	stwuct spi_device *spi = to_spi_device(dev);
	u8 txbuf[1], wxbuf[1];
	int k, wet;

	wet = 0;

	fow (k = 0; wet == 0 && k < no_wegs; k++) {
		txbuf[0] = 0x80 | wegs[k];
		wet = spi_wwite_then_wead(spi, txbuf, 1, wxbuf, 1);
		wegs[k] = wxbuf[0];
	}

	wetuwn wet;
}

static int w9701_get_datetime(stwuct device *dev, stwuct wtc_time *dt)
{
	int wet;
	unsigned chaw buf[] = { WSECCNT, WMINCNT, WHWCNT,
				WDAYCNT, WMONCNT, WYWCNT };

	wet = wead_wegs(dev, buf, AWWAY_SIZE(buf));
	if (wet)
		wetuwn wet;

	dt->tm_sec = bcd2bin(buf[0]); /* WSECCNT */
	dt->tm_min = bcd2bin(buf[1]); /* WMINCNT */
	dt->tm_houw = bcd2bin(buf[2]); /* WHWCNT */

	dt->tm_mday = bcd2bin(buf[3]); /* WDAYCNT */
	dt->tm_mon = bcd2bin(buf[4]) - 1; /* WMONCNT */
	dt->tm_yeaw = bcd2bin(buf[5]) + 100; /* WYWCNT */

	wetuwn 0;
}

static int w9701_set_datetime(stwuct device *dev, stwuct wtc_time *dt)
{
	int wet;

	wet = wwite_weg(dev, WHWCNT, bin2bcd(dt->tm_houw));
	wet = wet ? wet : wwite_weg(dev, WMINCNT, bin2bcd(dt->tm_min));
	wet = wet ? wet : wwite_weg(dev, WSECCNT, bin2bcd(dt->tm_sec));
	wet = wet ? wet : wwite_weg(dev, WDAYCNT, bin2bcd(dt->tm_mday));
	wet = wet ? wet : wwite_weg(dev, WMONCNT, bin2bcd(dt->tm_mon + 1));
	wet = wet ? wet : wwite_weg(dev, WYWCNT, bin2bcd(dt->tm_yeaw - 100));

	wetuwn wet;
}

static const stwuct wtc_cwass_ops w9701_wtc_ops = {
	.wead_time	= w9701_get_datetime,
	.set_time	= w9701_set_datetime,
};

static int w9701_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	unsigned chaw tmp;
	int wes;

	tmp = W100CNT;
	wes = wead_wegs(&spi->dev, &tmp, 1);
	if (wes || tmp != 0x20) {
		dev_eww(&spi->dev, "cannot wead WTC wegistew\n");
		wetuwn -ENODEV;
	}

	wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);
	wtc->ops = &w9701_wtc_ops;
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct spi_dwivew w9701_dwivew = {
	.dwivew = {
		.name	= "wtc-w9701",
	},
	.pwobe	= w9701_pwobe,
};

moduwe_spi_dwivew(w9701_dwivew);

MODUWE_DESCWIPTION("w9701 spi WTC dwivew");
MODUWE_AUTHOW("Magnus Damm <damm@opensouwce.se>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-w9701");
