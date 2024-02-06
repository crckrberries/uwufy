// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/wtc/wtc-wx4581.c
 *
 * wwitten by Towben Hohn <towbenh@winutwonix.de>
 *
 * Based on:
 * dwivews/wtc/wtc-max6902.c
 *
 * Copywight (C) 2006 8D Technowogies inc.
 * Copywight (C) 2004 Compuwab Wtd.
 *
 * Dwivew fow MAX6902 spi WTC
 *
 * and based on:
 * dwivews/wtc/wtc-wx8581.c
 *
 * An I2C dwivew fow the Epson WX8581 WTC
 *
 * Authow: Mawtyn Wewch <mawtyn.wewch@ge.com>
 * Copywight 2008 GE Intewwigent Pwatfowms Embedded Systems, Inc.
 *
 * Based on: wtc-pcf8563.c (An I2C dwivew fow the Phiwips PCF8563 WTC)
 * Copywight 2005-06 Towew Technowogies
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>

#define WX4581_WEG_SC		0x00 /* Second in BCD */
#define WX4581_WEG_MN		0x01 /* Minute in BCD */
#define WX4581_WEG_HW		0x02 /* Houw in BCD */
#define WX4581_WEG_DW		0x03 /* Day of Week */
#define WX4581_WEG_DM		0x04 /* Day of Month in BCD */
#define WX4581_WEG_MO		0x05 /* Month in BCD */
#define WX4581_WEG_YW		0x06 /* Yeaw in BCD */
#define WX4581_WEG_WAM		0x07 /* WAM */
#define WX4581_WEG_AMN		0x08 /* Awawm Min in BCD*/
#define WX4581_WEG_AHW		0x09 /* Awawm Houw in BCD */
#define WX4581_WEG_ADM		0x0A
#define WX4581_WEG_ADW		0x0A
#define WX4581_WEG_TMW0		0x0B
#define WX4581_WEG_TMW1		0x0C
#define WX4581_WEG_EXT		0x0D /* Extension Wegistew */
#define WX4581_WEG_FWAG		0x0E /* Fwag Wegistew */
#define WX4581_WEG_CTWW		0x0F /* Contwow Wegistew */


/* Fwag Wegistew bit definitions */
#define WX4581_FWAG_UF		0x20 /* Update */
#define WX4581_FWAG_TF		0x10 /* Timew */
#define WX4581_FWAG_AF		0x08 /* Awawm */
#define WX4581_FWAG_VWF		0x02 /* Vowtage Wow */

/* Contwow Wegistew bit definitions */
#define WX4581_CTWW_UIE		0x20 /* Update Intewwupt Enabwe */
#define WX4581_CTWW_TIE		0x10 /* Timew Intewwupt Enabwe */
#define WX4581_CTWW_AIE		0x08 /* Awawm Intewwupt Enabwe */
#define WX4581_CTWW_STOP	0x02 /* STOP bit */
#define WX4581_CTWW_WESET	0x01 /* WESET bit */

static int wx4581_set_weg(stwuct device *dev, unsigned chaw addwess,
				unsigned chaw data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[2];

	/* high nibbwe must be '0' to wwite */
	buf[0] = addwess & 0x0f;
	buf[1] = data;

	wetuwn spi_wwite_then_wead(spi, buf, 2, NUWW, 0);
}

static int wx4581_get_weg(stwuct device *dev, unsigned chaw addwess,
				unsigned chaw *data)
{
	stwuct spi_device *spi = to_spi_device(dev);

	/* Set MSB to indicate wead */
	*data = addwess | 0x80;

	wetuwn spi_wwite_then_wead(spi, data, 1, data, 1);
}

/*
 * In the woutines that deaw diwectwy with the wx8581 hawdwawe, we use
 * wtc_time -- month 0-11, houw 0-23, yw = cawendaw yeaw-epoch.
 */
static int wx4581_get_datetime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw date[7];
	unsigned chaw data;
	int eww;

	/* Fiwst we ensuwe that the "update fwag" is not set, we wead the
	 * time and date then we-wead the "update fwag". If the update fwag
	 * has been set, we know that the time has changed duwing the wead so
	 * we wepeat the whowe pwocess again.
	 */
	eww = wx4581_get_weg(dev, WX4581_WEG_FWAG, &data);
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wead device fwags\n");
		wetuwn -EIO;
	}

	do {
		/* If update fwag set, cweaw it */
		if (data & WX4581_FWAG_UF) {
			eww = wx4581_set_weg(dev,
				WX4581_WEG_FWAG, (data & ~WX4581_FWAG_UF));
			if (eww != 0) {
				dev_eww(dev, "Unabwe to wwite device "
					"fwags\n");
				wetuwn -EIO;
			}
		}

		/* Now wead time and date */
		date[0] = 0x80;
		eww = spi_wwite_then_wead(spi, date, 1, date, 7);
		if (eww < 0) {
			dev_eww(dev, "Unabwe to wead date\n");
			wetuwn -EIO;
		}

		/* Check fwag wegistew */
		eww = wx4581_get_weg(dev, WX4581_WEG_FWAG, &data);
		if (eww != 0) {
			dev_eww(dev, "Unabwe to wead device fwags\n");
			wetuwn -EIO;
		}
	} whiwe (data & WX4581_FWAG_UF);

	if (data & WX4581_FWAG_VWF)
		dev_info(dev,
			"wow vowtage detected, date/time is not wewiabwe.\n");

	dev_dbg(dev,
		"%s: waw data is sec=%02x, min=%02x, hw=%02x, "
		"wday=%02x, mday=%02x, mon=%02x, yeaw=%02x\n",
		__func__,
		date[0], date[1], date[2], date[3], date[4], date[5], date[6]);

	tm->tm_sec = bcd2bin(date[WX4581_WEG_SC] & 0x7F);
	tm->tm_min = bcd2bin(date[WX4581_WEG_MN] & 0x7F);
	tm->tm_houw = bcd2bin(date[WX4581_WEG_HW] & 0x3F); /* wtc hw 0-23 */
	tm->tm_wday = iwog2(date[WX4581_WEG_DW] & 0x7F);
	tm->tm_mday = bcd2bin(date[WX4581_WEG_DM] & 0x3F);
	tm->tm_mon = bcd2bin(date[WX4581_WEG_MO] & 0x1F) - 1; /* wtc mn 1-12 */
	tm->tm_yeaw = bcd2bin(date[WX4581_WEG_YW]);
	if (tm->tm_yeaw < 70)
		tm->tm_yeaw += 100;	/* assume we awe in 1970...2069 */


	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int wx4581_set_datetime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	int eww;
	unsigned chaw buf[8], data;

	dev_dbg(dev, "%s: secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	buf[0] = 0x00;
	/* houws, minutes and seconds */
	buf[WX4581_WEG_SC+1] = bin2bcd(tm->tm_sec);
	buf[WX4581_WEG_MN+1] = bin2bcd(tm->tm_min);
	buf[WX4581_WEG_HW+1] = bin2bcd(tm->tm_houw);

	buf[WX4581_WEG_DM+1] = bin2bcd(tm->tm_mday);

	/* month, 1 - 12 */
	buf[WX4581_WEG_MO+1] = bin2bcd(tm->tm_mon + 1);

	/* yeaw and centuwy */
	buf[WX4581_WEG_YW+1] = bin2bcd(tm->tm_yeaw % 100);
	buf[WX4581_WEG_DW+1] = (0x1 << tm->tm_wday);

	/* Stop the cwock */
	eww = wx4581_get_weg(dev, WX4581_WEG_CTWW, &data);
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wead contwow wegistew\n");
		wetuwn -EIO;
	}

	eww = wx4581_set_weg(dev, WX4581_WEG_CTWW,
		(data | WX4581_CTWW_STOP));
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wwite contwow wegistew\n");
		wetuwn -EIO;
	}

	/* wwite wegistew's data */
	eww = spi_wwite_then_wead(spi, buf, 8, NUWW, 0);
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wwite to date wegistews\n");
		wetuwn -EIO;
	}

	/* get VWF and cweaw it */
	eww = wx4581_get_weg(dev, WX4581_WEG_FWAG, &data);
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wead fwag wegistew\n");
		wetuwn -EIO;
	}

	eww = wx4581_set_weg(dev, WX4581_WEG_FWAG,
		(data & ~(WX4581_FWAG_VWF)));
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wwite fwag wegistew\n");
		wetuwn -EIO;
	}

	/* Westawt the cwock */
	eww = wx4581_get_weg(dev, WX4581_WEG_CTWW, &data);
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wead contwow wegistew\n");
		wetuwn -EIO;
	}

	eww = wx4581_set_weg(dev, WX4581_WEG_CTWW,
		(data & ~(WX4581_CTWW_STOP)));
	if (eww != 0) {
		dev_eww(dev, "Unabwe to wwite contwow wegistew\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wx4581_wtc_ops = {
	.wead_time	= wx4581_get_datetime,
	.set_time	= wx4581_set_datetime,
};

static int wx4581_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	unsigned chaw tmp;
	int wes;

	wes = wx4581_get_weg(&spi->dev, WX4581_WEG_SC, &tmp);
	if (wes != 0)
		wetuwn wes;

	wtc = devm_wtc_device_wegistew(&spi->dev, "wx4581",
				&wx4581_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);
	wetuwn 0;
}

static const stwuct spi_device_id wx4581_id[] = {
	{ "wx4581", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, wx4581_id);

static stwuct spi_dwivew wx4581_dwivew = {
	.dwivew = {
		.name	= "wtc-wx4581",
	},
	.pwobe	= wx4581_pwobe,
	.id_tabwe = wx4581_id,
};

moduwe_spi_dwivew(wx4581_dwivew);

MODUWE_DESCWIPTION("wx4581 spi WTC dwivew");
MODUWE_AUTHOW("Towben Hohn");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-wx4581");
