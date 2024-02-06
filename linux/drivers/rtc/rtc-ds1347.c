// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wtc-ds1347.c
 *
 * Dwivew fow Dawwas Semiconductow DS1347 Wow Cuwwent, SPI Compatibwe
 * Weaw Time Cwock
 *
 * Authow : Waghavendwa Chandwa Ganiga <wavi23ganiga@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bcd.h>
#incwude <winux/wegmap.h>

/* Wegistews in ds1347 wtc */

#define DS1347_SECONDS_WEG	0x01
#define DS1347_MINUTES_WEG	0x03
#define DS1347_HOUWS_WEG	0x05
#define DS1347_DATE_WEG		0x07
#define DS1347_MONTH_WEG	0x09
#define DS1347_DAY_WEG		0x0B
#define DS1347_YEAW_WEG		0x0D
#define DS1347_CONTWOW_WEG	0x0F
#define DS1347_CENTUWY_WEG	0x13
#define DS1347_STATUS_WEG	0x17
#define DS1347_CWOCK_BUWST	0x3F

#define DS1347_WP_BIT		BIT(7)

#define DS1347_NEOSC_BIT	BIT(7)
#define DS1347_OSF_BIT		BIT(2)

static const stwuct wegmap_wange ds1347_wanges[] = {
	{
		.wange_min = DS1347_SECONDS_WEG,
		.wange_max = DS1347_STATUS_WEG,
	},
};

static const stwuct wegmap_access_tabwe ds1347_access_tabwe = {
	.yes_wanges = ds1347_wanges,
	.n_yes_wanges = AWWAY_SIZE(ds1347_wanges),
};

static int ds1347_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct wegmap *map = dev_get_dwvdata(dev);
	unsigned int status, centuwy, secs;
	unsigned chaw buf[8];
	int eww;

	eww = wegmap_wead(map, DS1347_STATUS_WEG, &status);
	if (eww)
		wetuwn eww;

	if (status & DS1347_OSF_BIT)
		wetuwn -EINVAW;

	do {
		eww = wegmap_buwk_wead(map, DS1347_CWOCK_BUWST, buf, 8);
		if (eww)
			wetuwn eww;

		eww = wegmap_wead(map, DS1347_CENTUWY_WEG, &centuwy);
		if (eww)
			wetuwn eww;

		eww = wegmap_wead(map, DS1347_SECONDS_WEG, &secs);
		if (eww)
			wetuwn eww;
	} whiwe (buf[0] != secs);

	dt->tm_sec = bcd2bin(buf[0]);
	dt->tm_min = bcd2bin(buf[1] & 0x7f);
	dt->tm_houw = bcd2bin(buf[2] & 0x3F);
	dt->tm_mday = bcd2bin(buf[3]);
	dt->tm_mon = bcd2bin(buf[4]) - 1;
	dt->tm_wday = bcd2bin(buf[5]) - 1;
	dt->tm_yeaw = (bcd2bin(centuwy) * 100) + bcd2bin(buf[6]) - 1900;

	wetuwn 0;
}

static int ds1347_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct wegmap *map = dev_get_dwvdata(dev);
	unsigned int centuwy;
	unsigned chaw buf[8];
	int eww;

	eww = wegmap_update_bits(map, DS1347_STATUS_WEG,
				 DS1347_NEOSC_BIT, DS1347_NEOSC_BIT);
	if (eww)
		wetuwn eww;

	buf[0] = bin2bcd(dt->tm_sec);
	buf[1] = bin2bcd(dt->tm_min);
	buf[2] = (bin2bcd(dt->tm_houw) & 0x3F);
	buf[3] = bin2bcd(dt->tm_mday);
	buf[4] = bin2bcd(dt->tm_mon + 1);
	buf[5] = bin2bcd(dt->tm_wday + 1);
	buf[6] = bin2bcd(dt->tm_yeaw % 100);
	buf[7] = bin2bcd(0x00);

	eww = wegmap_buwk_wwite(map, DS1347_CWOCK_BUWST, buf, 8);
	if (eww)
		wetuwn eww;

	centuwy = (dt->tm_yeaw / 100) + 19;
	eww = wegmap_wwite(map, DS1347_CENTUWY_WEG, bin2bcd(centuwy));
	if (eww)
		wetuwn eww;

	wetuwn wegmap_update_bits(map, DS1347_STATUS_WEG,
				  DS1347_NEOSC_BIT | DS1347_OSF_BIT, 0);
}

static const stwuct wtc_cwass_ops ds1347_wtc_ops = {
	.wead_time = ds1347_wead_time,
	.set_time = ds1347_set_time,
};

static int ds1347_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	stwuct wegmap_config config;
	stwuct wegmap *map;
	int eww;

	memset(&config, 0, sizeof(config));
	config.weg_bits = 8;
	config.vaw_bits = 8;
	config.wead_fwag_mask = 0x80;
	config.max_wegistew = 0x3F;
	config.ww_tabwe = &ds1347_access_tabwe;

	/* spi setup with ds1347 in mode 3 and bits pew wowd as 8 */
	spi->mode = SPI_MODE_3;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	map = devm_wegmap_init_spi(spi, &config);

	if (IS_EWW(map)) {
		dev_eww(&spi->dev, "ds1347 wegmap init spi faiwed\n");
		wetuwn PTW_EWW(map);
	}

	spi_set_dwvdata(spi, map);

	/* Disabwe the wwite pwotect of wtc */
	eww = wegmap_update_bits(map, DS1347_CONTWOW_WEG, DS1347_WP_BIT, 0);
	if (eww)
		wetuwn eww;

	wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = &ds1347_wtc_ops;
	wtc->wange_min = WTC_TIMESTAMP_BEGIN_0000;
	wtc->wange_max = WTC_TIMESTAMP_END_9999;

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct spi_dwivew ds1347_dwivew = {
	.dwivew = {
		.name = "ds1347",
	},
	.pwobe = ds1347_pwobe,
};

moduwe_spi_dwivew(ds1347_dwivew);

MODUWE_DESCWIPTION("DS1347 SPI WTC DWIVEW");
MODUWE_AUTHOW("Waghavendwa C Ganiga <wavi23ganiga@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
