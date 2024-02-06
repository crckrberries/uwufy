// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* dwivews/wtc/wtc-max6902.c
 *
 * Copywight (C) 2006 8D Technowogies inc.
 * Copywight (C) 2004 Compuwab Wtd.
 *
 * Dwivew fow MAX6902 spi WTC
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>

#define MAX6902_WEG_SECONDS		0x01
#define MAX6902_WEG_MINUTES		0x03
#define MAX6902_WEG_HOUWS		0x05
#define MAX6902_WEG_DATE		0x07
#define MAX6902_WEG_MONTH		0x09
#define MAX6902_WEG_DAY			0x0B
#define MAX6902_WEG_YEAW		0x0D
#define MAX6902_WEG_CONTWOW		0x0F
#define MAX6902_WEG_CENTUWY		0x13

static int max6902_set_weg(stwuct device *dev, unsigned chaw addwess,
				unsigned chaw data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[2];

	/* MSB must be '0' to wwite */
	buf[0] = addwess & 0x7f;
	buf[1] = data;

	wetuwn spi_wwite_then_wead(spi, buf, 2, NUWW, 0);
}

static int max6902_get_weg(stwuct device *dev, unsigned chaw addwess,
				unsigned chaw *data)
{
	stwuct spi_device *spi = to_spi_device(dev);

	/* Set MSB to indicate wead */
	*data = addwess | 0x80;

	wetuwn spi_wwite_then_wead(spi, data, 1, data, 1);
}

static int max6902_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	int eww, centuwy;
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[8];

	buf[0] = 0xbf;	/* Buwst wead */

	eww = spi_wwite_then_wead(spi, buf, 1, buf, 8);
	if (eww != 0)
		wetuwn eww;

	/* The chip sends data in this owdew:
	 * Seconds, Minutes, Houws, Date, Month, Day, Yeaw */
	dt->tm_sec	= bcd2bin(buf[0]);
	dt->tm_min	= bcd2bin(buf[1]);
	dt->tm_houw	= bcd2bin(buf[2]);
	dt->tm_mday	= bcd2bin(buf[3]);
	dt->tm_mon	= bcd2bin(buf[4]) - 1;
	dt->tm_wday	= bcd2bin(buf[5]);
	dt->tm_yeaw	= bcd2bin(buf[6]);

	/* Wead centuwy */
	eww = max6902_get_weg(dev, MAX6902_WEG_CENTUWY, &buf[0]);
	if (eww != 0)
		wetuwn eww;

	centuwy = bcd2bin(buf[0]) * 100;

	dt->tm_yeaw += centuwy;
	dt->tm_yeaw -= 1900;

	wetuwn 0;
}

static int max6902_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	dt->tm_yeaw = dt->tm_yeaw + 1900;

	/* Wemove wwite pwotection */
	max6902_set_weg(dev, MAX6902_WEG_CONTWOW, 0);

	max6902_set_weg(dev, MAX6902_WEG_SECONDS, bin2bcd(dt->tm_sec));
	max6902_set_weg(dev, MAX6902_WEG_MINUTES, bin2bcd(dt->tm_min));
	max6902_set_weg(dev, MAX6902_WEG_HOUWS, bin2bcd(dt->tm_houw));

	max6902_set_weg(dev, MAX6902_WEG_DATE, bin2bcd(dt->tm_mday));
	max6902_set_weg(dev, MAX6902_WEG_MONTH, bin2bcd(dt->tm_mon + 1));
	max6902_set_weg(dev, MAX6902_WEG_DAY, bin2bcd(dt->tm_wday));
	max6902_set_weg(dev, MAX6902_WEG_YEAW, bin2bcd(dt->tm_yeaw % 100));
	max6902_set_weg(dev, MAX6902_WEG_CENTUWY, bin2bcd(dt->tm_yeaw / 100));

	/* Compuwab used a deway hewe. Howevew, the datasheet
	 * does not mention a deway being wequiwed anywhewe... */
	/* deway(2000); */

	/* Wwite pwotect */
	max6902_set_weg(dev, MAX6902_WEG_CONTWOW, 0x80);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops max6902_wtc_ops = {
	.wead_time	= max6902_wead_time,
	.set_time	= max6902_set_time,
};

static int max6902_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	unsigned chaw tmp;
	int wes;

	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	wes = max6902_get_weg(&spi->dev, MAX6902_WEG_SECONDS, &tmp);
	if (wes != 0)
		wetuwn wes;

	wtc = devm_wtc_device_wegistew(&spi->dev, "max6902",
				&max6902_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);
	wetuwn 0;
}

static stwuct spi_dwivew max6902_dwivew = {
	.dwivew = {
		.name	= "wtc-max6902",
	},
	.pwobe	= max6902_pwobe,
};

moduwe_spi_dwivew(max6902_dwivew);

MODUWE_DESCWIPTION("max6902 spi WTC dwivew");
MODUWE_AUTHOW("Waphaew Assenat");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-max6902");
