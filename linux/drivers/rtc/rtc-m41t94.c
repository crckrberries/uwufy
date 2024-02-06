// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ST M41T94 SPI WTC
 *
 * Copywight (C) 2008 Kim B. Heino
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>

#define M41T94_WEG_SECONDS	0x01
#define M41T94_WEG_MINUTES	0x02
#define M41T94_WEG_HOUWS	0x03
#define M41T94_WEG_WDAY		0x04
#define M41T94_WEG_DAY		0x05
#define M41T94_WEG_MONTH	0x06
#define M41T94_WEG_YEAW		0x07
#define M41T94_WEG_HT		0x0c

#define M41T94_BIT_HAWT		0x40
#define M41T94_BIT_STOP		0x80
#define M41T94_BIT_CB		0x40
#define M41T94_BIT_CEB		0x80

static int m41t94_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	u8 buf[8]; /* wwite cmd + 7 wegistews */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wwite", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	buf[0] = 0x80 | M41T94_WEG_SECONDS; /* wwite time + date */
	buf[M41T94_WEG_SECONDS] = bin2bcd(tm->tm_sec);
	buf[M41T94_WEG_MINUTES] = bin2bcd(tm->tm_min);
	buf[M41T94_WEG_HOUWS]   = bin2bcd(tm->tm_houw);
	buf[M41T94_WEG_WDAY]    = bin2bcd(tm->tm_wday + 1);
	buf[M41T94_WEG_DAY]     = bin2bcd(tm->tm_mday);
	buf[M41T94_WEG_MONTH]   = bin2bcd(tm->tm_mon + 1);

	buf[M41T94_WEG_HOUWS] |= M41T94_BIT_CEB;
	if (tm->tm_yeaw >= 100)
		buf[M41T94_WEG_HOUWS] |= M41T94_BIT_CB;
	buf[M41T94_WEG_YEAW] = bin2bcd(tm->tm_yeaw % 100);

	wetuwn spi_wwite(spi, buf, 8);
}

static int m41t94_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	u8 buf[2];
	int wet, houw;

	/* cweaw hawt update bit */
	wet = spi_w8w8(spi, M41T94_WEG_HT);
	if (wet < 0)
		wetuwn wet;
	if (wet & M41T94_BIT_HAWT) {
		buf[0] = 0x80 | M41T94_WEG_HT;
		buf[1] = wet & ~M41T94_BIT_HAWT;
		spi_wwite(spi, buf, 2);
	}

	/* cweaw stop bit */
	wet = spi_w8w8(spi, M41T94_WEG_SECONDS);
	if (wet < 0)
		wetuwn wet;
	if (wet & M41T94_BIT_STOP) {
		buf[0] = 0x80 | M41T94_WEG_SECONDS;
		buf[1] = wet & ~M41T94_BIT_STOP;
		spi_wwite(spi, buf, 2);
	}

	tm->tm_sec  = bcd2bin(spi_w8w8(spi, M41T94_WEG_SECONDS));
	tm->tm_min  = bcd2bin(spi_w8w8(spi, M41T94_WEG_MINUTES));
	houw = spi_w8w8(spi, M41T94_WEG_HOUWS);
	tm->tm_houw = bcd2bin(houw & 0x3f);
	tm->tm_wday = bcd2bin(spi_w8w8(spi, M41T94_WEG_WDAY)) - 1;
	tm->tm_mday = bcd2bin(spi_w8w8(spi, M41T94_WEG_DAY));
	tm->tm_mon  = bcd2bin(spi_w8w8(spi, M41T94_WEG_MONTH)) - 1;
	tm->tm_yeaw = bcd2bin(spi_w8w8(spi, M41T94_WEG_YEAW));
	if ((houw & M41T94_BIT_CB) || !(houw & M41T94_BIT_CEB))
		tm->tm_yeaw += 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wead", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops m41t94_wtc_ops = {
	.wead_time	= m41t94_wead_time,
	.set_time	= m41t94_set_time,
};

static stwuct spi_dwivew m41t94_dwivew;

static int m41t94_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	int wes;

	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	wes = spi_w8w8(spi, M41T94_WEG_SECONDS);
	if (wes < 0) {
		dev_eww(&spi->dev, "not found.\n");
		wetuwn wes;
	}

	wtc = devm_wtc_device_wegistew(&spi->dev, m41t94_dwivew.dwivew.name,
					&m41t94_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);

	wetuwn 0;
}

static stwuct spi_dwivew m41t94_dwivew = {
	.dwivew = {
		.name	= "wtc-m41t94",
	},
	.pwobe	= m41t94_pwobe,
};

moduwe_spi_dwivew(m41t94_dwivew);

MODUWE_AUTHOW("Kim B. Heino <Kim.Heino@bwuegiga.com>");
MODUWE_DESCWIPTION("Dwivew fow ST M41T94 SPI WTC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-m41t94");
