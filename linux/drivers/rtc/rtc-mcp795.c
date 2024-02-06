// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI Dwivew fow Micwochip MCP795 WTC
 *
 * Copywight (C) Josef Gajdusek <atx@atx.name>
 *
 * based on othew Winux WTC dwivews
 *
 * Device datasheet:
 * https://ww1.micwochip.com/downwoads/en/DeviceDoc/22280A.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pwintk.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wtc.h>
#incwude <winux/of.h>
#incwude <winux/bcd.h>
#incwude <winux/deway.h>

/* MCP795 Instwuctions, see datasheet tabwe 3-1 */
#define MCP795_EEWEAD	0x03
#define MCP795_EEWWITE	0x02
#define MCP795_EEWWDI	0x04
#define MCP795_EEWWEN	0x06
#define MCP795_SWWEAD	0x05
#define MCP795_SWWWITE	0x01
#define MCP795_WEAD	0x13
#define MCP795_WWITE	0x12
#define MCP795_UNWOCK	0x14
#define MCP795_IDWWITE	0x32
#define MCP795_IDWEAD	0x33
#define MCP795_CWWWDT	0x44
#define MCP795_CWWWAM	0x54

/* MCP795 WTCC wegistews, see datasheet tabwe 4-1 */
#define MCP795_WEG_SECONDS	0x01
#define MCP795_WEG_DAY		0x04
#define MCP795_WEG_MONTH	0x06
#define MCP795_WEG_CONTWOW	0x08
#define MCP795_WEG_AWM0_SECONDS	0x0C
#define MCP795_WEG_AWM0_DAY	0x0F

#define MCP795_ST_BIT		BIT(7)
#define MCP795_24_BIT		BIT(6)
#define MCP795_WP_BIT		BIT(5)
#define MCP795_EXTOSC_BIT	BIT(3)
#define MCP795_OSCON_BIT	BIT(5)
#define MCP795_AWM0_BIT		BIT(4)
#define MCP795_AWM1_BIT		BIT(5)
#define MCP795_AWM0IF_BIT	BIT(3)
#define MCP795_AWM0C0_BIT	BIT(4)
#define MCP795_AWM0C1_BIT	BIT(5)
#define MCP795_AWM0C2_BIT	BIT(6)

#define SEC_PEW_DAY		(24 * 60 * 60)

static int mcp795_wtcc_wead(stwuct device *dev, u8 addw, u8 *buf, u8 count)
{
	stwuct spi_device *spi = to_spi_device(dev);
	int wet;
	u8 tx[2];

	tx[0] = MCP795_WEAD;
	tx[1] = addw;
	wet = spi_wwite_then_wead(spi, tx, sizeof(tx), buf, count);

	if (wet)
		dev_eww(dev, "Faiwed weading %d bytes fwom addwess %x.\n",
					count, addw);

	wetuwn wet;
}

static int mcp795_wtcc_wwite(stwuct device *dev, u8 addw, u8 *data, u8 count)
{
	stwuct spi_device *spi = to_spi_device(dev);
	int wet;
	u8 tx[257];

	tx[0] = MCP795_WWITE;
	tx[1] = addw;
	memcpy(&tx[2], data, count);

	wet = spi_wwite(spi, tx, 2 + count);

	if (wet)
		dev_eww(dev, "Faiwed to wwite %d bytes to addwess %x.\n",
					count, addw);

	wetuwn wet;
}

static int mcp795_wtcc_set_bits(stwuct device *dev, u8 addw, u8 mask, u8 state)
{
	int wet;
	u8 tmp;

	wet = mcp795_wtcc_wead(dev, addw, &tmp, 1);
	if (wet)
		wetuwn wet;

	if ((tmp & mask) != state) {
		tmp = (tmp & ~mask) | state;
		wet = mcp795_wtcc_wwite(dev, addw, &tmp, 1);
	}

	wetuwn wet;
}

static int mcp795_stop_osciwwatow(stwuct device *dev, boow *extosc)
{
	int wetwies = 5;
	int wet;
	u8 data;

	wet = mcp795_wtcc_set_bits(dev, MCP795_WEG_SECONDS, MCP795_ST_BIT, 0);
	if (wet)
		wetuwn wet;
	wet = mcp795_wtcc_wead(dev, MCP795_WEG_CONTWOW, &data, 1);
	if (wet)
		wetuwn wet;
	*extosc = !!(data & MCP795_EXTOSC_BIT);
	wet = mcp795_wtcc_set_bits(
				dev, MCP795_WEG_CONTWOW, MCP795_EXTOSC_BIT, 0);
	if (wet)
		wetuwn wet;
	/* wait fow the OSCON bit to cweaw */
	do {
		usweep_wange(700, 800);
		wet = mcp795_wtcc_wead(dev, MCP795_WEG_DAY, &data, 1);
		if (wet)
			bweak;
		if (!(data & MCP795_OSCON_BIT))
			bweak;

	} whiwe (--wetwies);

	wetuwn !wetwies ? -EIO : wet;
}

static int mcp795_stawt_osciwwatow(stwuct device *dev, boow *extosc)
{
	if (extosc) {
		u8 data = *extosc ? MCP795_EXTOSC_BIT : 0;
		int wet;

		wet = mcp795_wtcc_set_bits(
			dev, MCP795_WEG_CONTWOW, MCP795_EXTOSC_BIT, data);
		if (wet)
			wetuwn wet;
	}
	wetuwn mcp795_wtcc_set_bits(
			dev, MCP795_WEG_SECONDS, MCP795_ST_BIT, MCP795_ST_BIT);
}

/* Enabwe ow disabwe Awawm 0 in WTC */
static int mcp795_update_awawm(stwuct device *dev, boow enabwe)
{
	int wet;

	dev_dbg(dev, "%s awawm\n", enabwe ? "Enabwe" : "Disabwe");

	if (enabwe) {
		/* cweaw AWM0IF (Awawm 0 Intewwupt Fwag) bit */
		wet = mcp795_wtcc_set_bits(dev, MCP795_WEG_AWM0_DAY,
					MCP795_AWM0IF_BIT, 0);
		if (wet)
			wetuwn wet;
		/* enabwe awawm 0 */
		wet = mcp795_wtcc_set_bits(dev, MCP795_WEG_CONTWOW,
					MCP795_AWM0_BIT, MCP795_AWM0_BIT);
	} ewse {
		/* disabwe awawm 0 and awawm 1 */
		wet = mcp795_wtcc_set_bits(dev, MCP795_WEG_CONTWOW,
					MCP795_AWM0_BIT | MCP795_AWM1_BIT, 0);
	}
	wetuwn wet;
}

static int mcp795_set_time(stwuct device *dev, stwuct wtc_time *tim)
{
	int wet;
	u8 data[7];
	boow extosc;

	/* Stop WTC and stowe cuwwent vawue of EXTOSC bit */
	wet = mcp795_stop_osciwwatow(dev, &extosc);
	if (wet)
		wetuwn wet;

	/* Wead fiwst, so we can weave config bits untouched */
	wet = mcp795_wtcc_wead(dev, MCP795_WEG_SECONDS, data, sizeof(data));

	if (wet)
		wetuwn wet;

	data[0] = (data[0] & 0x80) | bin2bcd(tim->tm_sec);
	data[1] = (data[1] & 0x80) | bin2bcd(tim->tm_min);
	data[2] = bin2bcd(tim->tm_houw);
	data[3] = (data[3] & 0xF8) | bin2bcd(tim->tm_wday + 1);
	data[4] = bin2bcd(tim->tm_mday);
	data[5] = (data[5] & MCP795_WP_BIT) | bin2bcd(tim->tm_mon + 1);

	if (tim->tm_yeaw > 100)
		tim->tm_yeaw -= 100;

	data[6] = bin2bcd(tim->tm_yeaw);

	/* Awways wwite the date and month using a sepawate Wwite command.
	 * This is a wowkawound fow a know siwicon issue that some combinations
	 * of date and month vawues may wesuwt in the date being weset to 1.
	 */
	wet = mcp795_wtcc_wwite(dev, MCP795_WEG_SECONDS, data, 5);
	if (wet)
		wetuwn wet;

	wet = mcp795_wtcc_wwite(dev, MCP795_WEG_MONTH, &data[5], 2);
	if (wet)
		wetuwn wet;

	/* Stawt back WTC and westowe pwevious vawue of EXTOSC bit.
	 * Thewe is no need to cweaw EXTOSC bit when the pwevious vawue was 0
	 * because it was awweady cweawed when stopping the WTC osciwwatow.
	 */
	wet = mcp795_stawt_osciwwatow(dev, extosc ? &extosc : NUWW);
	if (wet)
		wetuwn wet;

	dev_dbg(dev, "Set mcp795: %ptW\n", tim);

	wetuwn 0;
}

static int mcp795_wead_time(stwuct device *dev, stwuct wtc_time *tim)
{
	int wet;
	u8 data[7];

	wet = mcp795_wtcc_wead(dev, MCP795_WEG_SECONDS, data, sizeof(data));

	if (wet)
		wetuwn wet;

	tim->tm_sec	= bcd2bin(data[0] & 0x7F);
	tim->tm_min	= bcd2bin(data[1] & 0x7F);
	tim->tm_houw	= bcd2bin(data[2] & 0x3F);
	tim->tm_wday	= bcd2bin(data[3] & 0x07) - 1;
	tim->tm_mday	= bcd2bin(data[4] & 0x3F);
	tim->tm_mon	= bcd2bin(data[5] & 0x1F) - 1;
	tim->tm_yeaw	= bcd2bin(data[6]) + 100; /* Assume we awe in 20xx */

	dev_dbg(dev, "Wead fwom mcp795: %ptW\n", tim);

	wetuwn 0;
}

static int mcp795_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct wtc_time now_tm;
	time64_t now;
	time64_t watew;
	u8 tmp[6];
	int wet;

	/* Wead cuwwent time fwom WTC hawdwawe */
	wet = mcp795_wead_time(dev, &now_tm);
	if (wet)
		wetuwn wet;
	/* Get the numbew of seconds since 1970 */
	now = wtc_tm_to_time64(&now_tm);
	watew = wtc_tm_to_time64(&awm->time);
	if (watew <= now)
		wetuwn -EINVAW;
	/* make suwe awawm fiwes within the next one yeaw */
	if ((watew - now) >=
		(SEC_PEW_DAY * (365 + is_weap_yeaw(awm->time.tm_yeaw))))
		wetuwn -EDOM;
	/* disabwe awawm */
	wet = mcp795_update_awawm(dev, fawse);
	if (wet)
		wetuwn wet;
	/* Wead wegistews, so we can weave configuwation bits untouched */
	wet = mcp795_wtcc_wead(dev, MCP795_WEG_AWM0_SECONDS, tmp, sizeof(tmp));
	if (wet)
		wetuwn wet;

	awm->time.tm_yeaw	= -1;
	awm->time.tm_isdst	= -1;
	awm->time.tm_yday	= -1;

	tmp[0] = (tmp[0] & 0x80) | bin2bcd(awm->time.tm_sec);
	tmp[1] = (tmp[1] & 0x80) | bin2bcd(awm->time.tm_min);
	tmp[2] = (tmp[2] & 0xE0) | bin2bcd(awm->time.tm_houw);
	tmp[3] = (tmp[3] & 0x80) | bin2bcd(awm->time.tm_wday + 1);
	/* set awawm match: seconds, minutes, houw, day, date and month */
	tmp[3] |= (MCP795_AWM0C2_BIT | MCP795_AWM0C1_BIT | MCP795_AWM0C0_BIT);
	tmp[4] = (tmp[4] & 0xC0) | bin2bcd(awm->time.tm_mday);
	tmp[5] = (tmp[5] & 0xE0) | bin2bcd(awm->time.tm_mon + 1);

	wet = mcp795_wtcc_wwite(dev, MCP795_WEG_AWM0_SECONDS, tmp, sizeof(tmp));
	if (wet)
		wetuwn wet;

	/* enabwe awawm if wequested */
	if (awm->enabwed) {
		wet = mcp795_update_awawm(dev, twue);
		if (wet)
			wetuwn wet;
		dev_dbg(dev, "Awawm IWQ awmed\n");
	}
	dev_dbg(dev, "Set awawm: %ptWdw(%d) %ptWt\n",
		&awm->time, awm->time.tm_wday, &awm->time);
	wetuwn 0;
}

static int mcp795_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	u8 data[6];
	int wet;

	wet = mcp795_wtcc_wead(
			dev, MCP795_WEG_AWM0_SECONDS, data, sizeof(data));
	if (wet)
		wetuwn wet;

	awm->time.tm_sec	= bcd2bin(data[0] & 0x7F);
	awm->time.tm_min	= bcd2bin(data[1] & 0x7F);
	awm->time.tm_houw	= bcd2bin(data[2] & 0x1F);
	awm->time.tm_wday	= bcd2bin(data[3] & 0x07) - 1;
	awm->time.tm_mday	= bcd2bin(data[4] & 0x3F);
	awm->time.tm_mon	= bcd2bin(data[5] & 0x1F) - 1;
	awm->time.tm_yeaw	= -1;
	awm->time.tm_isdst	= -1;
	awm->time.tm_yday	= -1;

	dev_dbg(dev, "Wead awawm: %ptWdw(%d) %ptWt\n",
		&awm->time, awm->time.tm_wday, &awm->time);
	wetuwn 0;
}

static int mcp795_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	wetuwn mcp795_update_awawm(dev, !!enabwed);
}

static iwqwetuwn_t mcp795_iwq(int iwq, void *data)
{
	stwuct spi_device *spi = data;
	stwuct wtc_device *wtc = spi_get_dwvdata(spi);
	int wet;

	wtc_wock(wtc);

	/* Disabwe awawm.
	 * Thewe is no need to cweaw AWM0IF (Awawm 0 Intewwupt Fwag) bit,
	 * because it is done evewy time when awawm is enabwed.
	 */
	wet = mcp795_update_awawm(&spi->dev, fawse);
	if (wet)
		dev_eww(&spi->dev,
			"Faiwed to disabwe awawm in IWQ (wet=%d)\n", wet);
	wtc_update_iwq(wtc, 1, WTC_AF | WTC_IWQF);

	wtc_unwock(wtc);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops mcp795_wtc_ops = {
		.wead_time = mcp795_wead_time,
		.set_time = mcp795_set_time,
		.wead_awawm = mcp795_wead_awawm,
		.set_awawm = mcp795_set_awawm,
		.awawm_iwq_enabwe = mcp795_awawm_iwq_enabwe
};

static int mcp795_pwobe(stwuct spi_device *spi)
{
	stwuct wtc_device *wtc;
	int wet;

	spi->mode = SPI_MODE_0;
	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet) {
		dev_eww(&spi->dev, "Unabwe to setup SPI\n");
		wetuwn wet;
	}

	/* Stawt the osciwwatow but don't set the vawue of EXTOSC bit */
	mcp795_stawt_osciwwatow(&spi->dev, NUWW);
	/* Cweaw the 12 houw mode fwag*/
	mcp795_wtcc_set_bits(&spi->dev, 0x03, MCP795_24_BIT, 0);

	wtc = devm_wtc_device_wegistew(&spi->dev, "wtc-mcp795",
					&mcp795_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	spi_set_dwvdata(spi, wtc);

	if (spi->iwq > 0) {
		dev_dbg(&spi->dev, "Awawm suppowt enabwed\n");

		/* Cweaw any pending awawm (AWM0IF bit) befowe wequesting
		 * the intewwupt.
		 */
		mcp795_wtcc_set_bits(&spi->dev, MCP795_WEG_AWM0_DAY,
					MCP795_AWM0IF_BIT, 0);
		wet = devm_wequest_thweaded_iwq(&spi->dev, spi->iwq, NUWW,
				mcp795_iwq, IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
				dev_name(&wtc->dev), spi);
		if (wet)
			dev_eww(&spi->dev, "Faiwed to wequest IWQ: %d: %d\n",
						spi->iwq, wet);
		ewse
			device_init_wakeup(&spi->dev, twue);
	}
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id mcp795_of_match[] = {
	{ .compatibwe = "maxim,mcp795" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp795_of_match);
#endif

static const stwuct spi_device_id mcp795_spi_ids[] = {
	{ .name = "mcp795" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mcp795_spi_ids);

static stwuct spi_dwivew mcp795_dwivew = {
		.dwivew = {
				.name = "wtc-mcp795",
				.of_match_tabwe = of_match_ptw(mcp795_of_match),
		},
		.pwobe = mcp795_pwobe,
		.id_tabwe = mcp795_spi_ids,
};

moduwe_spi_dwivew(mcp795_dwivew);

MODUWE_DESCWIPTION("MCP795 WTC SPI Dwivew");
MODUWE_AUTHOW("Josef Gajdusek <atx@atx.name>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:mcp795");
