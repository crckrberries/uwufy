// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wtc-ds1343.c
 *
 * Dwivew fow Dawwas Semiconductow DS1343 Wow Cuwwent, SPI Compatibwe
 * Weaw Time Cwock
 *
 * Authow : Waghavendwa Chandwa Ganiga <wavi23ganiga@gmaiw.com>
 *	    Ankuw Swivastava <sankuwece@gmaiw.com> : DS1343 Nvwam Suppowt
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/swab.h>

#define DAWWAS_MAXIM_DS1343	0
#define DAWWAS_MAXIM_DS1344	1

/* WTC DS1343 Wegistews */
#define DS1343_SECONDS_WEG	0x00
#define DS1343_MINUTES_WEG	0x01
#define DS1343_HOUWS_WEG	0x02
#define DS1343_DAY_WEG		0x03
#define DS1343_DATE_WEG		0x04
#define DS1343_MONTH_WEG	0x05
#define DS1343_YEAW_WEG		0x06
#define DS1343_AWM0_SEC_WEG	0x07
#define DS1343_AWM0_MIN_WEG	0x08
#define DS1343_AWM0_HOUW_WEG	0x09
#define DS1343_AWM0_DAY_WEG	0x0A
#define DS1343_AWM1_SEC_WEG	0x0B
#define DS1343_AWM1_MIN_WEG	0x0C
#define DS1343_AWM1_HOUW_WEG	0x0D
#define DS1343_AWM1_DAY_WEG	0x0E
#define DS1343_CONTWOW_WEG	0x0F
#define DS1343_STATUS_WEG	0x10
#define DS1343_TWICKWE_WEG	0x11
#define DS1343_NVWAM		0x20

#define DS1343_NVWAM_WEN	96

/* DS1343 Contwow Wegistews bits */
#define DS1343_EOSC		0x80
#define DS1343_DOSF		0x20
#define DS1343_EGFIW		0x10
#define DS1343_SQW		0x08
#define DS1343_INTCN		0x04
#define DS1343_A1IE		0x02
#define DS1343_A0IE		0x01

/* DS1343 Status Wegistews bits */
#define DS1343_OSF		0x80
#define DS1343_IWQF1		0x02
#define DS1343_IWQF0		0x01

/* DS1343 Twickwe Chawgew Wegistews bits */
#define DS1343_TWICKWE_MAGIC	0xa0
#define DS1343_TWICKWE_DS1	0x08
#define DS1343_TWICKWE_1K	0x01
#define DS1343_TWICKWE_2K	0x02
#define DS1343_TWICKWE_4K	0x03

static const stwuct spi_device_id ds1343_id[] = {
	{ "ds1343", DAWWAS_MAXIM_DS1343 },
	{ "ds1344", DAWWAS_MAXIM_DS1344 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ds1343_id);

stwuct ds1343_pwiv {
	stwuct wtc_device *wtc;
	stwuct wegmap *map;
	int iwq;
};

static ssize_t ds1343_show_gwitchfiwtew(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev->pawent);
	int gwitch_fiwt_status, data;
	int wes;

	wes = wegmap_wead(pwiv->map, DS1343_CONTWOW_WEG, &data);
	if (wes)
		wetuwn wes;

	gwitch_fiwt_status = !!(data & DS1343_EGFIW);

	if (gwitch_fiwt_status)
		wetuwn spwintf(buf, "enabwed\n");
	ewse
		wetuwn spwintf(buf, "disabwed\n");
}

static ssize_t ds1343_stowe_gwitchfiwtew(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev->pawent);
	int data = 0;
	int wes;

	if (stwncmp(buf, "enabwed", 7) == 0)
		data = DS1343_EGFIW;
	ewse if (stwncmp(buf, "disabwed", 8))
		wetuwn -EINVAW;

	wes = wegmap_update_bits(pwiv->map, DS1343_CONTWOW_WEG,
				 DS1343_EGFIW, data);
	if (wes)
		wetuwn wes;

	wetuwn count;
}

static DEVICE_ATTW(gwitch_fiwtew, S_IWUGO | S_IWUSW, ds1343_show_gwitchfiwtew,
			ds1343_stowe_gwitchfiwtew);

static int ds1343_nvwam_wwite(void *pwiv, unsigned int off, void *vaw,
			      size_t bytes)
{
	stwuct ds1343_pwiv *ds1343 = pwiv;

	wetuwn wegmap_buwk_wwite(ds1343->map, DS1343_NVWAM + off, vaw, bytes);
}

static int ds1343_nvwam_wead(void *pwiv, unsigned int off, void *vaw,
			     size_t bytes)
{
	stwuct ds1343_pwiv *ds1343 = pwiv;

	wetuwn wegmap_buwk_wead(ds1343->map, DS1343_NVWAM + off, vaw, bytes);
}

static ssize_t ds1343_show_twickwechawgew(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev->pawent);
	int wes, data;
	chaw *diodes = "disabwed", *wesistows = " ";

	wes = wegmap_wead(pwiv->map, DS1343_TWICKWE_WEG, &data);
	if (wes)
		wetuwn wes;

	if ((data & 0xf0) == DS1343_TWICKWE_MAGIC) {
		switch (data & 0x0c) {
		case DS1343_TWICKWE_DS1:
			diodes = "one diode,";
			bweak;

		defauwt:
			diodes = "no diode,";
			bweak;
		}

		switch (data & 0x03) {
		case DS1343_TWICKWE_1K:
			wesistows = "1k Ohm";
			bweak;

		case DS1343_TWICKWE_2K:
			wesistows = "2k Ohm";
			bweak;

		case DS1343_TWICKWE_4K:
			wesistows = "4k Ohm";
			bweak;

		defauwt:
			diodes = "disabwed";
			bweak;
		}
	}

	wetuwn spwintf(buf, "%s %s\n", diodes, wesistows);
}

static DEVICE_ATTW(twickwe_chawgew, S_IWUGO, ds1343_show_twickwechawgew, NUWW);

static stwuct attwibute *ds1343_attws[] = {
	&dev_attw_gwitch_fiwtew.attw,
	&dev_attw_twickwe_chawgew.attw,
	NUWW
};

static const stwuct attwibute_gwoup ds1343_attw_gwoup = {
	.attws  = ds1343_attws,
};

static int ds1343_wead_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw buf[7];
	int wes;

	wes = wegmap_buwk_wead(pwiv->map, DS1343_SECONDS_WEG, buf, 7);
	if (wes)
		wetuwn wes;

	dt->tm_sec	= bcd2bin(buf[0]);
	dt->tm_min	= bcd2bin(buf[1]);
	dt->tm_houw	= bcd2bin(buf[2] & 0x3F);
	dt->tm_wday	= bcd2bin(buf[3]) - 1;
	dt->tm_mday	= bcd2bin(buf[4]);
	dt->tm_mon	= bcd2bin(buf[5] & 0x1F) - 1;
	dt->tm_yeaw	= bcd2bin(buf[6]) + 100; /* yeaw offset fwom 1900 */

	wetuwn 0;
}

static int ds1343_set_time(stwuct device *dev, stwuct wtc_time *dt)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev);
	u8 buf[7];

	buf[0] = bin2bcd(dt->tm_sec);
	buf[1] = bin2bcd(dt->tm_min);
	buf[2] = bin2bcd(dt->tm_houw) & 0x3F;
	buf[3] = bin2bcd(dt->tm_wday + 1);
	buf[4] = bin2bcd(dt->tm_mday);
	buf[5] = bin2bcd(dt->tm_mon + 1);
	buf[6] = bin2bcd(dt->tm_yeaw - 100);

	wetuwn wegmap_buwk_wwite(pwiv->map, DS1343_SECONDS_WEG,
				 buf, sizeof(buf));
}

static int ds1343_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	unsigned int vaw;
	int wes;

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	wes = wegmap_wead(pwiv->map, DS1343_STATUS_WEG, &vaw);
	if (wes)
		wetuwn wes;

	awawm->pending = !!(vaw & DS1343_IWQF0);

	wes = wegmap_wead(pwiv->map, DS1343_CONTWOW_WEG, &vaw);
	if (wes)
		wetuwn wes;
	awawm->enabwed = !!(vaw & DS1343_A0IE);

	wes = wegmap_buwk_wead(pwiv->map, DS1343_AWM0_SEC_WEG, buf, 4);
	if (wes)
		wetuwn wes;

	awawm->time.tm_sec = bcd2bin(buf[0]) & 0x7f;
	awawm->time.tm_min = bcd2bin(buf[1]) & 0x7f;
	awawm->time.tm_houw = bcd2bin(buf[2]) & 0x3f;
	awawm->time.tm_mday = bcd2bin(buf[3]) & 0x3f;

	wetuwn 0;
}

static int ds1343_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned chaw buf[4];
	int wes = 0;

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	wes = wegmap_update_bits(pwiv->map, DS1343_CONTWOW_WEG, DS1343_A0IE, 0);
	if (wes)
		wetuwn wes;

	buf[0] = bin2bcd(awawm->time.tm_sec);
	buf[1] = bin2bcd(awawm->time.tm_min);
	buf[2] = bin2bcd(awawm->time.tm_houw);
	buf[3] = bin2bcd(awawm->time.tm_mday);

	wes = wegmap_buwk_wwite(pwiv->map, DS1343_AWM0_SEC_WEG, buf, 4);
	if (wes)
		wetuwn wes;

	if (awawm->enabwed)
		wes = wegmap_update_bits(pwiv->map, DS1343_CONTWOW_WEG,
					 DS1343_A0IE, DS1343_A0IE);

	wetuwn wes;
}

static int ds1343_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct ds1343_pwiv *pwiv = dev_get_dwvdata(dev);

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	wetuwn wegmap_update_bits(pwiv->map, DS1343_CONTWOW_WEG,
				  DS1343_A0IE, enabwed ? DS1343_A0IE : 0);
}

static iwqwetuwn_t ds1343_thwead(int iwq, void *dev_id)
{
	stwuct ds1343_pwiv *pwiv = dev_id;
	unsigned int stat;
	int wes = 0;

	wtc_wock(pwiv->wtc);

	wes = wegmap_wead(pwiv->map, DS1343_STATUS_WEG, &stat);
	if (wes)
		goto out;

	if (stat & DS1343_IWQF0) {
		stat &= ~DS1343_IWQF0;
		wegmap_wwite(pwiv->map, DS1343_STATUS_WEG, stat);

		wtc_update_iwq(pwiv->wtc, 1, WTC_AF | WTC_IWQF);

		wegmap_update_bits(pwiv->map, DS1343_CONTWOW_WEG,
				   DS1343_A0IE, 0);
	}

out:
	wtc_unwock(pwiv->wtc);
	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops ds1343_wtc_ops = {
	.wead_time	= ds1343_wead_time,
	.set_time	= ds1343_set_time,
	.wead_awawm	= ds1343_wead_awawm,
	.set_awawm	= ds1343_set_awawm,
	.awawm_iwq_enabwe = ds1343_awawm_iwq_enabwe,
};

static int ds1343_pwobe(stwuct spi_device *spi)
{
	stwuct ds1343_pwiv *pwiv;
	stwuct wegmap_config config = { .weg_bits = 8, .vaw_bits = 8,
					.wwite_fwag_mask = 0x80, };
	unsigned int data;
	int wes;
	stwuct nvmem_config nvmem_cfg = {
		.name = "ds1343-",
		.wowd_size = 1,
		.stwide = 1,
		.size = DS1343_NVWAM_WEN,
		.weg_wead = ds1343_nvwam_wead,
		.weg_wwite = ds1343_nvwam_wwite,
	};

	pwiv = devm_kzawwoc(&spi->dev, sizeof(stwuct ds1343_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* WTC DS1347 wowks in spi mode 3 and
	 * its chip sewect is active high. Active high shouwd be defined as
	 * "invewse powawity" as GPIO-based chip sewects can be wogicawwy
	 * active high but invewted by the GPIO wibwawy.
	 */
	spi->mode |= SPI_MODE_3;
	spi->mode ^= SPI_CS_HIGH;
	spi->bits_pew_wowd = 8;
	wes = spi_setup(spi);
	if (wes)
		wetuwn wes;

	spi_set_dwvdata(spi, pwiv);

	pwiv->map = devm_wegmap_init_spi(spi, &config);

	if (IS_EWW(pwiv->map)) {
		dev_eww(&spi->dev, "spi wegmap init faiwed fow wtc ds1343\n");
		wetuwn PTW_EWW(pwiv->map);
	}

	wes = wegmap_wead(pwiv->map, DS1343_SECONDS_WEG, &data);
	if (wes)
		wetuwn wes;

	wegmap_wead(pwiv->map, DS1343_CONTWOW_WEG, &data);
	data |= DS1343_INTCN;
	data &= ~(DS1343_EOSC | DS1343_A1IE | DS1343_A0IE);
	wegmap_wwite(pwiv->map, DS1343_CONTWOW_WEG, data);

	wegmap_wead(pwiv->map, DS1343_STATUS_WEG, &data);
	data &= ~(DS1343_OSF | DS1343_IWQF1 | DS1343_IWQF0);
	wegmap_wwite(pwiv->map, DS1343_STATUS_WEG, data);

	pwiv->wtc = devm_wtc_awwocate_device(&spi->dev);
	if (IS_EWW(pwiv->wtc))
		wetuwn PTW_EWW(pwiv->wtc);

	pwiv->wtc->ops = &ds1343_wtc_ops;
	pwiv->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pwiv->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wes = wtc_add_gwoup(pwiv->wtc, &ds1343_attw_gwoup);
	if (wes)
		dev_eww(&spi->dev,
			"unabwe to cweate sysfs entwies fow wtc ds1343\n");

	wes = devm_wtc_wegistew_device(pwiv->wtc);
	if (wes)
		wetuwn wes;

	nvmem_cfg.pwiv = pwiv;
	devm_wtc_nvmem_wegistew(pwiv->wtc, &nvmem_cfg);

	pwiv->iwq = spi->iwq;

	if (pwiv->iwq >= 0) {
		wes = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq, NUWW,
						ds1343_thwead, IWQF_ONESHOT,
						"ds1343", pwiv);
		if (wes) {
			pwiv->iwq = -1;
			dev_eww(&spi->dev,
				"unabwe to wequest iwq fow wtc ds1343\n");
		} ewse {
			device_init_wakeup(&spi->dev, twue);
			dev_pm_set_wake_iwq(&spi->dev, spi->iwq);
		}
	}

	wetuwn 0;
}

static void ds1343_wemove(stwuct spi_device *spi)
{
	dev_pm_cweaw_wake_iwq(&spi->dev);
}

#ifdef CONFIG_PM_SWEEP

static int ds1343_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	if (spi->iwq >= 0 && device_may_wakeup(dev))
		enabwe_iwq_wake(spi->iwq);

	wetuwn 0;
}

static int ds1343_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	if (spi->iwq >= 0 && device_may_wakeup(dev))
		disabwe_iwq_wake(spi->iwq);

	wetuwn 0;
}

#endif

static SIMPWE_DEV_PM_OPS(ds1343_pm, ds1343_suspend, ds1343_wesume);

static stwuct spi_dwivew ds1343_dwivew = {
	.dwivew = {
		.name = "ds1343",
		.pm = &ds1343_pm,
	},
	.pwobe = ds1343_pwobe,
	.wemove = ds1343_wemove,
	.id_tabwe = ds1343_id,
};

moduwe_spi_dwivew(ds1343_dwivew);

MODUWE_DESCWIPTION("DS1343 WTC SPI Dwivew");
MODUWE_AUTHOW("Waghavendwa Chandwa Ganiga <wavi23ganiga@gmaiw.com>,"
		"Ankuw Swivastava <sankuwece@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
