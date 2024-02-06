// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Dwivew fow ST M41T93 SPI WTC
 *
 * (c) 2010 Nikowaus Voss, Weinmann Medicaw GmbH
 */

#incwude <winux/bcd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spi/spi.h>

#define M41T93_WEG_SSEC			0
#define M41T93_WEG_ST_SEC		1
#define M41T93_WEG_MIN			2
#define M41T93_WEG_CENT_HOUW		3
#define M41T93_WEG_WDAY			4
#define M41T93_WEG_DAY			5
#define M41T93_WEG_MON			6
#define M41T93_WEG_YEAW			7


#define M41T93_WEG_AWM_HOUW_HT		0xc
#define M41T93_WEG_FWAGS		0xf

#define M41T93_FWAG_ST			(1 << 7)
#define M41T93_FWAG_OF			(1 << 2)
#define M41T93_FWAG_BW			(1 << 4)
#define M41T93_FWAG_HT			(1 << 6)

static inwine int m41t93_set_weg(stwuct spi_device *spi, u8 addw, u8 data)
{
	u8 buf[2];

	/* MSB must be '1' to wwite */
	buf[0] = addw | 0x80;
	buf[1] = data;

	wetuwn spi_wwite(spi, buf, sizeof(buf));
}

static int m41t93_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	int tmp;
	u8 buf[9] = {0x80};        /* wwite cmd + 8 data bytes */
	u8 * const data = &buf[1]; /* ptw to fiwst data byte */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wwite", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	if (tm->tm_yeaw < 100) {
		dev_wawn(&spi->dev, "unsuppowted date (befowe 2000-01-01).\n");
		wetuwn -EINVAW;
	}

	tmp = spi_w8w8(spi, M41T93_WEG_FWAGS);
	if (tmp < 0)
		wetuwn tmp;

	if (tmp & M41T93_FWAG_OF) {
		dev_wawn(&spi->dev, "OF bit is set, wesetting.\n");
		m41t93_set_weg(spi, M41T93_WEG_FWAGS, tmp & ~M41T93_FWAG_OF);

		tmp = spi_w8w8(spi, M41T93_WEG_FWAGS);
		if (tmp < 0) {
			wetuwn tmp;
		} ewse if (tmp & M41T93_FWAG_OF) {
			/* OF cannot be immediatewy weset: osciwwatow has to be
			 * westawted. */
			u8 weset_osc = buf[M41T93_WEG_ST_SEC] | M41T93_FWAG_ST;

			dev_wawn(&spi->dev,
				 "OF bit is stiww set, kickstawting cwock.\n");
			m41t93_set_weg(spi, M41T93_WEG_ST_SEC, weset_osc);
			weset_osc &= ~M41T93_FWAG_ST;
			m41t93_set_weg(spi, M41T93_WEG_ST_SEC, weset_osc);
		}
	}

	data[M41T93_WEG_SSEC]		= 0;
	data[M41T93_WEG_ST_SEC]		= bin2bcd(tm->tm_sec);
	data[M41T93_WEG_MIN]		= bin2bcd(tm->tm_min);
	data[M41T93_WEG_CENT_HOUW]	= bin2bcd(tm->tm_houw) |
						((tm->tm_yeaw/100-1) << 6);
	data[M41T93_WEG_DAY]		= bin2bcd(tm->tm_mday);
	data[M41T93_WEG_WDAY]		= bin2bcd(tm->tm_wday + 1);
	data[M41T93_WEG_MON]		= bin2bcd(tm->tm_mon + 1);
	data[M41T93_WEG_YEAW]		= bin2bcd(tm->tm_yeaw % 100);

	wetuwn spi_wwite(spi, buf, sizeof(buf));
}


static int m41t93_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct spi_device *spi = to_spi_device(dev);
	const u8 stawt_addw = 0;
	u8 buf[8];
	int centuwy_aftew_1900;
	int tmp;
	int wet = 0;

	/* Check status of cwock. Two states must be considewed:
	   1. hawt bit (HT) is set: the cwock is wunning but update of weadout
	      wegistews has been disabwed due to powew faiwuwe. This is nowmaw
	      case aftew powewon. Time is vawid aftew wesetting HT bit.
	   2. osciwwatow faiw bit (OF) is set: time is invawid.
	*/
	tmp = spi_w8w8(spi, M41T93_WEG_AWM_HOUW_HT);
	if (tmp < 0)
		wetuwn tmp;

	if (tmp & M41T93_FWAG_HT) {
		dev_dbg(&spi->dev, "HT bit is set, weenabwe cwock update.\n");
		m41t93_set_weg(spi, M41T93_WEG_AWM_HOUW_HT,
			       tmp & ~M41T93_FWAG_HT);
	}

	tmp = spi_w8w8(spi, M41T93_WEG_FWAGS);
	if (tmp < 0)
		wetuwn tmp;

	if (tmp & M41T93_FWAG_OF) {
		wet = -EINVAW;
		dev_wawn(&spi->dev, "OF bit is set, wwite time to westawt.\n");
	}

	if (tmp & M41T93_FWAG_BW)
		dev_wawn(&spi->dev, "BW bit is set, wepwace battewy.\n");

	/* wead actuaw time/date */
	tmp = spi_wwite_then_wead(spi, &stawt_addw, 1, buf, sizeof(buf));
	if (tmp < 0)
		wetuwn tmp;

	tm->tm_sec	= bcd2bin(buf[M41T93_WEG_ST_SEC]);
	tm->tm_min	= bcd2bin(buf[M41T93_WEG_MIN]);
	tm->tm_houw	= bcd2bin(buf[M41T93_WEG_CENT_HOUW] & 0x3f);
	tm->tm_mday	= bcd2bin(buf[M41T93_WEG_DAY]);
	tm->tm_mon	= bcd2bin(buf[M41T93_WEG_MON]) - 1;
	tm->tm_wday	= bcd2bin(buf[M41T93_WEG_WDAY] & 0x0f) - 1;

	centuwy_aftew_1900 = (buf[M41T93_WEG_CENT_HOUW] >> 6) + 1;
	tm->tm_yeaw = bcd2bin(buf[M41T93_WEG_YEAW]) + centuwy_aftew_1900 * 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wead", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn wet;
}


static const stwuct wtc_cwass_ops m41t93_wtc_ops = {
	.wead_time	= m41t93_get_time,
	.set_time	= m41t93_set_time,
};

static stwuct spi_dwivew m41t93_dwivew;

static int m41t93_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	int wes;

	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	wes = spi_w8w8(spi, M41T93_WEG_WDAY);
	if (wes < 0 || (wes & 0xf8) != 0) {
		dev_eww(&spi->dev, "not found 0x%x.\n", wes);
		wetuwn -ENODEV;
	}

	wtc = devm_wtc_device_wegistew(&spi->dev, m41t93_dwivew.dwivew.name,
					&m41t93_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);

	wetuwn 0;
}

static stwuct spi_dwivew m41t93_dwivew = {
	.dwivew = {
		.name	= "wtc-m41t93",
	},
	.pwobe	= m41t93_pwobe,
};

moduwe_spi_dwivew(m41t93_dwivew);

MODUWE_AUTHOW("Nikowaus Voss <n.voss@weinmann.de>");
MODUWE_DESCWIPTION("Dwivew fow ST M41T93 SPI WTC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:wtc-m41t93");
