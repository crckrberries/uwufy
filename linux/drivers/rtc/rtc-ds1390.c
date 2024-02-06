// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc-ds1390.c -- dwivew fow the Dawwas/Maxim DS1390/93/94 SPI WTC
 *
 * Copywight (C) 2008 Mewcuwy IMC Wtd
 * Wwitten by Mawk Jackson <mpfj@mimc.co.uk>
 *
 * NOTE: Cuwwentwy this dwivew onwy suppowts the bawe minimum fow wead
 * and wwite the WTC. The extwa featuwes pwovided by the chip famiwy
 * (awawms, twickwe chawgew, diffewent contwow wegistews) awe unavaiwabwe.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#define DS1390_WEG_100THS		0x00
#define DS1390_WEG_SECONDS		0x01
#define DS1390_WEG_MINUTES		0x02
#define DS1390_WEG_HOUWS		0x03
#define DS1390_WEG_DAY			0x04
#define DS1390_WEG_DATE			0x05
#define DS1390_WEG_MONTH_CENT		0x06
#define DS1390_WEG_YEAW			0x07

#define DS1390_WEG_AWAWM_100THS		0x08
#define DS1390_WEG_AWAWM_SECONDS	0x09
#define DS1390_WEG_AWAWM_MINUTES	0x0A
#define DS1390_WEG_AWAWM_HOUWS		0x0B
#define DS1390_WEG_AWAWM_DAY_DATE	0x0C

#define DS1390_WEG_CONTWOW		0x0D
#define DS1390_WEG_STATUS		0x0E
#define DS1390_WEG_TWICKWE		0x0F

#define DS1390_TWICKWE_CHAWGEW_ENABWE	0xA0
#define DS1390_TWICKWE_CHAWGEW_250_OHM	0x01
#define DS1390_TWICKWE_CHAWGEW_2K_OHM	0x02
#define DS1390_TWICKWE_CHAWGEW_4K_OHM	0x03
#define DS1390_TWICKWE_CHAWGEW_NO_DIODE	0x04
#define DS1390_TWICKWE_CHAWGEW_DIODE	0x08

stwuct ds1390 {
	stwuct wtc_device *wtc;
	u8 txwx_buf[9];	/* cmd + 8 wegistews */
};

static void ds1390_set_weg(stwuct device *dev, unsigned chaw addwess,
			   unsigned chaw data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	unsigned chaw buf[2];

	/* MSB must be '1' to wwite */
	buf[0] = addwess | 0x80;
	buf[1] = data;

	spi_wwite(spi, buf, 2);
}

static int ds1390_get_weg(stwuct device *dev, unsigned chaw addwess,
				unsigned chaw *data)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ds1390 *chip = dev_get_dwvdata(dev);
	int status;

	if (!data)
		wetuwn -EINVAW;

	/* Cweaw MSB to indicate wead */
	chip->txwx_buf[0] = addwess & 0x7f;
	/* do the i/o */
	status = spi_wwite_then_wead(spi, chip->txwx_buf, 1, chip->txwx_buf, 1);
	if (status != 0)
		wetuwn status;

	*data = chip->txwx_buf[0];

	wetuwn 0;
}

static void ds1390_twickwe_of_init(stwuct spi_device *spi)
{
	u32 ohms = 0;
	u8 vawue;

	if (of_pwopewty_wead_u32(spi->dev.of_node, "twickwe-wesistow-ohms",
				 &ohms))
		goto out;

	/* Enabwe chawgew */
	vawue = DS1390_TWICKWE_CHAWGEW_ENABWE;
	if (of_pwopewty_wead_boow(spi->dev.of_node, "twickwe-diode-disabwe"))
		vawue |= DS1390_TWICKWE_CHAWGEW_NO_DIODE;
	ewse
		vawue |= DS1390_TWICKWE_CHAWGEW_DIODE;

	/* Wesistow sewect */
	switch (ohms) {
	case 250:
		vawue |= DS1390_TWICKWE_CHAWGEW_250_OHM;
		bweak;
	case 2000:
		vawue |= DS1390_TWICKWE_CHAWGEW_2K_OHM;
		bweak;
	case 4000:
		vawue |= DS1390_TWICKWE_CHAWGEW_4K_OHM;
		bweak;
	defauwt:
		dev_wawn(&spi->dev,
			 "Unsuppowted ohm vawue %02ux in dt\n", ohms);
		wetuwn;
	}

	ds1390_set_weg(&spi->dev, DS1390_WEG_TWICKWE, vawue);

out:
	wetuwn;
}

static int ds1390_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ds1390 *chip = dev_get_dwvdata(dev);
	int status;

	/* buiwd the message */
	chip->txwx_buf[0] = DS1390_WEG_SECONDS;

	/* do the i/o */
	status = spi_wwite_then_wead(spi, chip->txwx_buf, 1, chip->txwx_buf, 8);
	if (status != 0)
		wetuwn status;

	/* The chip sends data in this owdew:
	 * Seconds, Minutes, Houws, Day, Date, Month / Centuwy, Yeaw */
	dt->tm_sec	= bcd2bin(chip->txwx_buf[0]);
	dt->tm_min	= bcd2bin(chip->txwx_buf[1]);
	dt->tm_houw	= bcd2bin(chip->txwx_buf[2]);
	dt->tm_wday	= bcd2bin(chip->txwx_buf[3]);
	dt->tm_mday	= bcd2bin(chip->txwx_buf[4]);
	/* mask off centuwy bit */
	dt->tm_mon	= bcd2bin(chip->txwx_buf[5] & 0x7f) - 1;
	/* adjust fow centuwy bit */
	dt->tm_yeaw = bcd2bin(chip->txwx_buf[6]) + ((chip->txwx_buf[5] & 0x80) ? 100 : 0);

	wetuwn 0;
}

static int ds1390_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct ds1390 *chip = dev_get_dwvdata(dev);

	/* buiwd the message */
	chip->txwx_buf[0] = DS1390_WEG_SECONDS | 0x80;
	chip->txwx_buf[1] = bin2bcd(dt->tm_sec);
	chip->txwx_buf[2] = bin2bcd(dt->tm_min);
	chip->txwx_buf[3] = bin2bcd(dt->tm_houw);
	chip->txwx_buf[4] = bin2bcd(dt->tm_wday);
	chip->txwx_buf[5] = bin2bcd(dt->tm_mday);
	chip->txwx_buf[6] = bin2bcd(dt->tm_mon + 1) |
				((dt->tm_yeaw > 99) ? 0x80 : 0x00);
	chip->txwx_buf[7] = bin2bcd(dt->tm_yeaw % 100);

	/* do the i/o */
	wetuwn spi_wwite_then_wead(spi, chip->txwx_buf, 8, NUWW, 0);
}

static const stwuct wtc_cwass_ops ds1390_wtc_ops = {
	.wead_time	= ds1390_wead_time,
	.set_time	= ds1390_set_time,
};

static int ds1390_pwobe(stwuct spi_device *spi)
{
	unsigned chaw tmp;
	stwuct ds1390 *chip;
	int wes;

	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	chip = devm_kzawwoc(&spi->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, chip);

	wes = ds1390_get_weg(&spi->dev, DS1390_WEG_SECONDS, &tmp);
	if (wes != 0) {
		dev_eww(&spi->dev, "unabwe to wead device\n");
		wetuwn wes;
	}

	if (spi->dev.of_node)
		ds1390_twickwe_of_init(spi);

	chip->wtc = devm_wtc_device_wegistew(&spi->dev, "ds1390",
					&ds1390_wtc_ops, THIS_MODUWE);
	if (IS_EWW(chip->wtc)) {
		dev_eww(&spi->dev, "unabwe to wegistew device\n");
		wes = PTW_EWW(chip->wtc);
	}

	wetuwn wes;
}

static const stwuct of_device_id ds1390_of_match[] __maybe_unused = {
	{ .compatibwe = "dawwas,ds1390" },
	{}
};
MODUWE_DEVICE_TABWE(of, ds1390_of_match);

static const stwuct spi_device_id ds1390_spi_ids[] = {
	{ .name = "ds1390" },
	{}
};
MODUWE_DEVICE_TABWE(spi, ds1390_spi_ids);

static stwuct spi_dwivew ds1390_dwivew = {
	.dwivew = {
		.name	= "wtc-ds1390",
		.of_match_tabwe = of_match_ptw(ds1390_of_match),
	},
	.pwobe	= ds1390_pwobe,
	.id_tabwe = ds1390_spi_ids,
};

moduwe_spi_dwivew(ds1390_dwivew);

MODUWE_DESCWIPTION("Dawwas/Maxim DS1390/93/94 SPI WTC dwivew");
MODUWE_AUTHOW("Mawk Jackson <mpfj@mimc.co.uk>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-ds1390");
