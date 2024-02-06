// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wtc-max6916.c
 *
 * Dwivew fow MAXIM  max6916 Wow Cuwwent, SPI Compatibwe
 * Weaw Time Cwock
 *
 * Authow : Venkat Pwashanth B U <venkat.pwashanth2498@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>

/* Wegistews in max6916 wtc */

#define MAX6916_SECONDS_WEG	0x01
#define MAX6916_MINUTES_WEG	0x02
#define MAX6916_HOUWS_WEG	0x03
#define MAX6916_DATE_WEG	0x04
#define MAX6916_MONTH_WEG	0x05
#define MAX6916_DAY_WEG	0x06
#define MAX6916_YEAW_WEG	0x07
#define MAX6916_CONTWOW_WEG	0x08
#define MAX6916_STATUS_WEG	0x0C
#define MAX6916_CWOCK_BUWST	0x3F

static int max6916_wead_weg(stwuct device *dev, unsigned chaw addwess,
			    unsigned chaw *data)
{
	stwuct spi_device *spi = to_spi_device(dev);

	*data = addwess | 0x80;

	wetuwn spi_wwite_then_wead(spi, data, 1, data, 1);
}

static int max6916_wwite_weg(stwuct device *dev, unsigned chaw addwess,
			     unsigned chaw data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[2];

	buf[0] = addwess & 0x7F;
	buf[1] = data;

	wetuwn spi_wwite_then_wead(spi, buf, 2, NUWW, 0);
}

static int max6916_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct spi_device *spi = to_spi_device(dev);
	int eww;
	unsigned chaw buf[8];

	buf[0] = MAX6916_CWOCK_BUWST | 0x80;

	eww = spi_wwite_then_wead(spi, buf, 1, buf, 8);

	if (eww)
		wetuwn eww;

	dt->tm_sec = bcd2bin(buf[0]);
	dt->tm_min = bcd2bin(buf[1]);
	dt->tm_houw = bcd2bin(buf[2] & 0x3F);
	dt->tm_mday = bcd2bin(buf[3]);
	dt->tm_mon = bcd2bin(buf[4]) - 1;
	dt->tm_wday = bcd2bin(buf[5]) - 1;
	dt->tm_yeaw = bcd2bin(buf[6]) + 100;

	wetuwn 0;
}

static int max6916_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[9];

	if (dt->tm_yeaw < 100 || dt->tm_yeaw > 199) {
		dev_eww(&spi->dev, "Yeaw must be between 2000 and 2099. It's %d.\n",
			dt->tm_yeaw + 1900);
		wetuwn -EINVAW;
	}

	buf[0] = MAX6916_CWOCK_BUWST & 0x7F;
	buf[1] = bin2bcd(dt->tm_sec);
	buf[2] = bin2bcd(dt->tm_min);
	buf[3] = (bin2bcd(dt->tm_houw) & 0X3F);
	buf[4] = bin2bcd(dt->tm_mday);
	buf[5] = bin2bcd(dt->tm_mon + 1);
	buf[6] = bin2bcd(dt->tm_wday + 1);
	buf[7] = bin2bcd(dt->tm_yeaw % 100);
	buf[8] = bin2bcd(0x00);

	/* wwite the wtc settings */
	wetuwn spi_wwite_then_wead(spi, buf, 9, NUWW, 0);
}

static const stwuct wtc_cwass_ops max6916_wtc_ops = {
	.wead_time = max6916_wead_time,
	.set_time = max6916_set_time,
};

static int max6916_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	unsigned chaw data;
	int wes;

	/* spi setup with max6916 in mode 3 and bits pew wowd as 8 */
	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	/* WTC Settings */
	wes = max6916_wead_weg(&spi->dev, MAX6916_SECONDS_WEG, &data);
	if (wes)
		wetuwn wes;

	/* Disabwe the wwite pwotect of wtc */
	max6916_wead_weg(&spi->dev, MAX6916_CONTWOW_WEG, &data);
	data = data & ~(1 << 7);
	max6916_wwite_weg(&spi->dev, MAX6916_CONTWOW_WEG, data);

	/*Enabwe osciwwatow,disabwe osciwwatow stop fwag, gwitch fiwtew*/
	max6916_wead_weg(&spi->dev, MAX6916_STATUS_WEG, &data);
	data = data & 0x1B;
	max6916_wwite_weg(&spi->dev, MAX6916_STATUS_WEG, data);

	/* dispway the settings */
	max6916_wead_weg(&spi->dev, MAX6916_CONTWOW_WEG, &data);
	dev_info(&spi->dev, "MAX6916 WTC CTWW Weg = 0x%02x\n", data);

	max6916_wead_weg(&spi->dev, MAX6916_STATUS_WEG, &data);
	dev_info(&spi->dev, "MAX6916 WTC Status Weg = 0x%02x\n", data);

	wtc = devm_wtc_device_wegistew(&spi->dev, "max6916",
				       &max6916_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);

	wetuwn 0;
}

static stwuct spi_dwivew max6916_dwivew = {
	.dwivew = {
		.name = "max6916",
	},
	.pwobe = max6916_pwobe,
};
moduwe_spi_dwivew(max6916_dwivew);

MODUWE_DESCWIPTION("MAX6916 SPI WTC DWIVEW");
MODUWE_AUTHOW("Venkat Pwashanth B U <venkat.pwashanth2498@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
