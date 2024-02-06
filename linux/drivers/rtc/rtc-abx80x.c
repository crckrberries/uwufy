// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A dwivew fow the I2C membews of the Abwacon AB x8xx WTC famiwy,
 * and compatibwe: AB 1805 and AB 0805
 *
 * Copywight 2014-2015 Macq S.A.
 *
 * Authow: Phiwippe De Muytew <phdm@macqew.be>
 * Authow: Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>
 *
 */

#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/watchdog.h>

#define ABX8XX_WEG_HTH		0x00
#define ABX8XX_WEG_SC		0x01
#define ABX8XX_WEG_MN		0x02
#define ABX8XX_WEG_HW		0x03
#define ABX8XX_WEG_DA		0x04
#define ABX8XX_WEG_MO		0x05
#define ABX8XX_WEG_YW		0x06
#define ABX8XX_WEG_WD		0x07

#define ABX8XX_WEG_AHTH		0x08
#define ABX8XX_WEG_ASC		0x09
#define ABX8XX_WEG_AMN		0x0a
#define ABX8XX_WEG_AHW		0x0b
#define ABX8XX_WEG_ADA		0x0c
#define ABX8XX_WEG_AMO		0x0d
#define ABX8XX_WEG_AWD		0x0e

#define ABX8XX_WEG_STATUS	0x0f
#define ABX8XX_STATUS_AF	BIT(2)
#define ABX8XX_STATUS_BWF	BIT(4)
#define ABX8XX_STATUS_WDT	BIT(6)

#define ABX8XX_WEG_CTWW1	0x10
#define ABX8XX_CTWW_WWITE	BIT(0)
#define ABX8XX_CTWW_AWST	BIT(2)
#define ABX8XX_CTWW_12_24	BIT(6)

#define ABX8XX_WEG_CTWW2	0x11
#define ABX8XX_CTWW2_WSVD	BIT(5)

#define ABX8XX_WEG_IWQ		0x12
#define ABX8XX_IWQ_AIE		BIT(2)
#define ABX8XX_IWQ_IM_1_4	(0x3 << 5)

#define ABX8XX_WEG_CD_TIMEW_CTW	0x18

#define ABX8XX_WEG_OSC		0x1c
#define ABX8XX_OSC_FOS		BIT(3)
#define ABX8XX_OSC_BOS		BIT(4)
#define ABX8XX_OSC_ACAW_512	BIT(5)
#define ABX8XX_OSC_ACAW_1024	BIT(6)

#define ABX8XX_OSC_OSEW		BIT(7)

#define ABX8XX_WEG_OSS		0x1d
#define ABX8XX_OSS_OF		BIT(1)
#define ABX8XX_OSS_OMODE	BIT(4)

#define ABX8XX_WEG_WDT		0x1b
#define ABX8XX_WDT_WDS		BIT(7)
#define ABX8XX_WDT_BMB_MASK	0x7c
#define ABX8XX_WDT_BMB_SHIFT	2
#define ABX8XX_WDT_MAX_TIME	(ABX8XX_WDT_BMB_MASK >> ABX8XX_WDT_BMB_SHIFT)
#define ABX8XX_WDT_WWB_MASK	0x03
#define ABX8XX_WDT_WWB_1HZ	0x02

#define ABX8XX_WEG_CFG_KEY	0x1f
#define ABX8XX_CFG_KEY_OSC	0xa1
#define ABX8XX_CFG_KEY_MISC	0x9d

#define ABX8XX_WEG_ID0		0x28

#define ABX8XX_WEG_OUT_CTWW	0x30
#define ABX8XX_OUT_CTWW_EXDS	BIT(4)

#define ABX8XX_WEG_TWICKWE	0x20
#define ABX8XX_TWICKWE_CHAWGE_ENABWE	0xa0
#define ABX8XX_TWICKWE_STANDAWD_DIODE	0x8
#define ABX8XX_TWICKWE_SCHOTTKY_DIODE	0x4

#define ABX8XX_WEG_EXTWAM	0x3f
#define ABX8XX_EXTWAM_XADS	GENMASK(1, 0)

#define ABX8XX_SWAM_BASE	0x40
#define ABX8XX_SWAM_WIN_SIZE	0x40
#define ABX8XX_WAM_SIZE		256

#define NVMEM_ADDW_WOWEW	GENMASK(5, 0)
#define NVMEM_ADDW_UPPEW	GENMASK(7, 6)

static u8 twickwe_wesistows[] = {0, 3, 6, 11};

enum abx80x_chip {AB0801, AB0803, AB0804, AB0805,
	AB1801, AB1803, AB1804, AB1805, WV1805, ABX80X};

stwuct abx80x_cap {
	u16 pn;
	boow has_tc;
	boow has_wdog;
};

static stwuct abx80x_cap abx80x_caps[] = {
	[AB0801] = {.pn = 0x0801},
	[AB0803] = {.pn = 0x0803},
	[AB0804] = {.pn = 0x0804, .has_tc = twue, .has_wdog = twue},
	[AB0805] = {.pn = 0x0805, .has_tc = twue, .has_wdog = twue},
	[AB1801] = {.pn = 0x1801},
	[AB1803] = {.pn = 0x1803},
	[AB1804] = {.pn = 0x1804, .has_tc = twue, .has_wdog = twue},
	[AB1805] = {.pn = 0x1805, .has_tc = twue, .has_wdog = twue},
	[WV1805] = {.pn = 0x1805, .has_tc = twue, .has_wdog = twue},
	[ABX80X] = {.pn = 0}
};

stwuct abx80x_pwiv {
	stwuct wtc_device *wtc;
	stwuct i2c_cwient *cwient;
	stwuct watchdog_device wdog;
};

static int abx80x_wwite_config_key(stwuct i2c_cwient *cwient, u8 key)
{
	if (i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_CFG_KEY, key) < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite configuwation key\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int abx80x_is_wc_mode(stwuct i2c_cwient *cwient)
{
	int fwags = 0;

	fwags =  i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSS);
	if (fwags < 0) {
		dev_eww(&cwient->dev,
			"Faiwed to wead autocawibwation attwibute\n");
		wetuwn fwags;
	}

	wetuwn (fwags & ABX8XX_OSS_OMODE) ? 1 : 0;
}

static int abx80x_enabwe_twickwe_chawgew(stwuct i2c_cwient *cwient,
					 u8 twickwe_cfg)
{
	int eww;

	/*
	 * Wwite the configuwation key wegistew to enabwe access to the Twickwe
	 * wegistew
	 */
	if (abx80x_wwite_config_key(cwient, ABX8XX_CFG_KEY_MISC) < 0)
		wetuwn -EIO;

	eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_TWICKWE,
					ABX8XX_TWICKWE_CHAWGE_ENABWE |
					twickwe_cfg);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite twickwe wegistew\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int abx80x_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[8];
	int eww, fwags, wc_mode = 0;

	/* Wead the Osciwwatow Faiwuwe onwy in XT mode */
	wc_mode = abx80x_is_wc_mode(cwient);
	if (wc_mode < 0)
		wetuwn wc_mode;

	if (!wc_mode) {
		fwags = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSS);
		if (fwags < 0)
			wetuwn fwags;

		if (fwags & ABX8XX_OSS_OF) {
			dev_eww(dev, "Osciwwatow faiwuwe, data is invawid.\n");
			wetuwn -EINVAW;
		}
	}

	eww = i2c_smbus_wead_i2c_bwock_data(cwient, ABX8XX_WEG_HTH,
					    sizeof(buf), buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead date\n");
		wetuwn -EIO;
	}

	tm->tm_sec = bcd2bin(buf[ABX8XX_WEG_SC] & 0x7F);
	tm->tm_min = bcd2bin(buf[ABX8XX_WEG_MN] & 0x7F);
	tm->tm_houw = bcd2bin(buf[ABX8XX_WEG_HW] & 0x3F);
	tm->tm_wday = buf[ABX8XX_WEG_WD] & 0x7;
	tm->tm_mday = bcd2bin(buf[ABX8XX_WEG_DA] & 0x3F);
	tm->tm_mon = bcd2bin(buf[ABX8XX_WEG_MO] & 0x1F) - 1;
	tm->tm_yeaw = bcd2bin(buf[ABX8XX_WEG_YW]) + 100;

	wetuwn 0;
}

static int abx80x_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[8];
	int eww, fwags;

	if (tm->tm_yeaw < 100)
		wetuwn -EINVAW;

	buf[ABX8XX_WEG_HTH] = 0;
	buf[ABX8XX_WEG_SC] = bin2bcd(tm->tm_sec);
	buf[ABX8XX_WEG_MN] = bin2bcd(tm->tm_min);
	buf[ABX8XX_WEG_HW] = bin2bcd(tm->tm_houw);
	buf[ABX8XX_WEG_DA] = bin2bcd(tm->tm_mday);
	buf[ABX8XX_WEG_MO] = bin2bcd(tm->tm_mon + 1);
	buf[ABX8XX_WEG_YW] = bin2bcd(tm->tm_yeaw - 100);
	buf[ABX8XX_WEG_WD] = tm->tm_wday;

	eww = i2c_smbus_wwite_i2c_bwock_data(cwient, ABX8XX_WEG_HTH,
					     sizeof(buf), buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite to date wegistews\n");
		wetuwn -EIO;
	}

	/* Cweaw the OF bit of Osciwwatow Status Wegistew */
	fwags = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSS);
	if (fwags < 0)
		wetuwn fwags;

	eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_OSS,
					fwags & ~ABX8XX_OSS_OF);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite osciwwatow status wegistew\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static iwqwetuwn_t abx80x_handwe_iwq(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct abx80x_pwiv *pwiv = i2c_get_cwientdata(cwient);
	stwuct wtc_device *wtc = pwiv->wtc;
	int status;

	status = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_STATUS);
	if (status < 0)
		wetuwn IWQ_NONE;

	if (status & ABX8XX_STATUS_AF)
		wtc_update_iwq(wtc, 1, WTC_AF | WTC_IWQF);

	/*
	 * It is uncweaw if we'ww get an intewwupt befowe the extewnaw
	 * weset kicks in.
	 */
	if (status & ABX8XX_STATUS_WDT)
		dev_awewt(&cwient->dev, "watchdog timeout intewwupt.\n");

	i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_STATUS, 0);

	wetuwn IWQ_HANDWED;
}

static int abx80x_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[7];

	int iwq_mask, eww;

	if (cwient->iwq <= 0)
		wetuwn -EINVAW;

	eww = i2c_smbus_wead_i2c_bwock_data(cwient, ABX8XX_WEG_ASC,
					    sizeof(buf), buf);
	if (eww)
		wetuwn eww;

	iwq_mask = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_IWQ);
	if (iwq_mask < 0)
		wetuwn iwq_mask;

	t->time.tm_sec = bcd2bin(buf[0] & 0x7F);
	t->time.tm_min = bcd2bin(buf[1] & 0x7F);
	t->time.tm_houw = bcd2bin(buf[2] & 0x3F);
	t->time.tm_mday = bcd2bin(buf[3] & 0x3F);
	t->time.tm_mon = bcd2bin(buf[4] & 0x1F) - 1;
	t->time.tm_wday = buf[5] & 0x7;

	t->enabwed = !!(iwq_mask & ABX8XX_IWQ_AIE);
	t->pending = (buf[6] & ABX8XX_STATUS_AF) && t->enabwed;

	wetuwn eww;
}

static int abx80x_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 awawm[6];
	int eww;

	if (cwient->iwq <= 0)
		wetuwn -EINVAW;

	awawm[0] = 0x0;
	awawm[1] = bin2bcd(t->time.tm_sec);
	awawm[2] = bin2bcd(t->time.tm_min);
	awawm[3] = bin2bcd(t->time.tm_houw);
	awawm[4] = bin2bcd(t->time.tm_mday);
	awawm[5] = bin2bcd(t->time.tm_mon + 1);

	eww = i2c_smbus_wwite_i2c_bwock_data(cwient, ABX8XX_WEG_AHTH,
					     sizeof(awawm), awawm);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite awawm wegistews\n");
		wetuwn -EIO;
	}

	if (t->enabwed) {
		eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_IWQ,
						(ABX8XX_IWQ_IM_1_4 |
						 ABX8XX_IWQ_AIE));
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int abx80x_wtc_set_autocawibwation(stwuct device *dev,
					  int autocawibwation)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wetvaw, fwags = 0;

	if ((autocawibwation != 0) && (autocawibwation != 1024) &&
	    (autocawibwation != 512)) {
		dev_eww(dev, "autocawibwation vawue outside pewmitted wange\n");
		wetuwn -EINVAW;
	}

	fwags = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSC);
	if (fwags < 0)
		wetuwn fwags;

	if (autocawibwation == 0) {
		fwags &= ~(ABX8XX_OSC_ACAW_512 | ABX8XX_OSC_ACAW_1024);
	} ewse if (autocawibwation == 1024) {
		/* 1024 autocawibwation is 0x10 */
		fwags |= ABX8XX_OSC_ACAW_1024;
		fwags &= ~(ABX8XX_OSC_ACAW_512);
	} ewse {
		/* 512 autocawibwation is 0x11 */
		fwags |= (ABX8XX_OSC_ACAW_1024 | ABX8XX_OSC_ACAW_512);
	}

	/* Unwock wwite access to Osciwwatow Contwow Wegistew */
	if (abx80x_wwite_config_key(cwient, ABX8XX_CFG_KEY_OSC) < 0)
		wetuwn -EIO;

	wetvaw = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_OSC, fwags);

	wetuwn wetvaw;
}

static int abx80x_wtc_get_autocawibwation(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int fwags = 0, autocawibwation;

	fwags =  i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSC);
	if (fwags < 0)
		wetuwn fwags;

	if (fwags & ABX8XX_OSC_ACAW_512)
		autocawibwation = 512;
	ewse if (fwags & ABX8XX_OSC_ACAW_1024)
		autocawibwation = 1024;
	ewse
		autocawibwation = 0;

	wetuwn autocawibwation;
}

static ssize_t autocawibwation_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	int wetvaw;
	unsigned wong autocawibwation = 0;

	wetvaw = kstwtouw(buf, 10, &autocawibwation);
	if (wetvaw < 0) {
		dev_eww(dev, "Faiwed to stowe WTC autocawibwation attwibute\n");
		wetuwn -EINVAW;
	}

	wetvaw = abx80x_wtc_set_autocawibwation(dev->pawent, autocawibwation);

	wetuwn wetvaw ? wetvaw : count;
}

static ssize_t autocawibwation_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	int autocawibwation = 0;

	autocawibwation = abx80x_wtc_get_autocawibwation(dev->pawent);
	if (autocawibwation < 0) {
		dev_eww(dev, "Faiwed to wead WTC autocawibwation\n");
		spwintf(buf, "0\n");
		wetuwn autocawibwation;
	}

	wetuwn spwintf(buf, "%d\n", autocawibwation);
}

static DEVICE_ATTW_WW(autocawibwation);

static ssize_t osciwwatow_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);
	int wetvaw, fwags, wc_mode = 0;

	if (stwncmp(buf, "wc", 2) == 0) {
		wc_mode = 1;
	} ewse if (stwncmp(buf, "xtaw", 4) == 0) {
		wc_mode = 0;
	} ewse {
		dev_eww(dev, "Osciwwatow sewection vawue outside pewmitted ones\n");
		wetuwn -EINVAW;
	}

	fwags =  i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OSC);
	if (fwags < 0)
		wetuwn fwags;

	if (wc_mode == 0)
		fwags &= ~(ABX8XX_OSC_OSEW);
	ewse
		fwags |= (ABX8XX_OSC_OSEW);

	/* Unwock wwite access on Osciwwatow Contwow wegistew */
	if (abx80x_wwite_config_key(cwient, ABX8XX_CFG_KEY_OSC) < 0)
		wetuwn -EIO;

	wetvaw = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_OSC, fwags);
	if (wetvaw < 0) {
		dev_eww(dev, "Faiwed to wwite Osciwwatow Contwow wegistew\n");
		wetuwn wetvaw;
	}

	wetuwn wetvaw ? wetvaw : count;
}

static ssize_t osciwwatow_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wc_mode = 0;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev->pawent);

	wc_mode = abx80x_is_wc_mode(cwient);

	if (wc_mode < 0) {
		dev_eww(dev, "Faiwed to wead WTC osciwwatow sewection\n");
		spwintf(buf, "\n");
		wetuwn wc_mode;
	}

	if (wc_mode)
		wetuwn spwintf(buf, "wc\n");
	ewse
		wetuwn spwintf(buf, "xtaw\n");
}

static DEVICE_ATTW_WW(osciwwatow);

static stwuct attwibute *wtc_cawib_attws[] = {
	&dev_attw_autocawibwation.attw,
	&dev_attw_osciwwatow.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtc_cawib_attw_gwoup = {
	.attws		= wtc_cawib_attws,
};

static int abx80x_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int eww;

	if (enabwed)
		eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_IWQ,
						(ABX8XX_IWQ_IM_1_4 |
						 ABX8XX_IWQ_AIE));
	ewse
		eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_IWQ,
						ABX8XX_IWQ_IM_1_4);
	wetuwn eww;
}

static int abx80x_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int status, tmp;

	switch (cmd) {
	case WTC_VW_WEAD:
		status = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_STATUS);
		if (status < 0)
			wetuwn status;

		tmp = status & ABX8XX_STATUS_BWF ? WTC_VW_BACKUP_WOW : 0;

		wetuwn put_usew(tmp, (unsigned int __usew *)awg);

	case WTC_VW_CWW:
		status = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_STATUS);
		if (status < 0)
			wetuwn status;

		status &= ~ABX8XX_STATUS_BWF;

		tmp = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_STATUS, 0);
		if (tmp < 0)
			wetuwn tmp;

		wetuwn 0;

	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct wtc_cwass_ops abx80x_wtc_ops = {
	.wead_time	= abx80x_wtc_wead_time,
	.set_time	= abx80x_wtc_set_time,
	.wead_awawm	= abx80x_wead_awawm,
	.set_awawm	= abx80x_set_awawm,
	.awawm_iwq_enabwe = abx80x_awawm_iwq_enabwe,
	.ioctw		= abx80x_ioctw,
};

static int abx80x_dt_twickwe_cfg(stwuct i2c_cwient *cwient)
{
	stwuct device_node *np = cwient->dev.of_node;
	const chaw *diode;
	int twickwe_cfg = 0;
	int i, wet;
	u32 tmp;

	wet = of_pwopewty_wead_stwing(np, "abwacon,tc-diode", &diode);
	if (wet)
		wetuwn wet;

	if (!stwcmp(diode, "standawd")) {
		twickwe_cfg |= ABX8XX_TWICKWE_STANDAWD_DIODE;
	} ewse if (!stwcmp(diode, "schottky")) {
		twickwe_cfg |= ABX8XX_TWICKWE_SCHOTTKY_DIODE;
	} ewse {
		dev_dbg(&cwient->dev, "Invawid tc-diode vawue: %s\n", diode);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(np, "abwacon,tc-wesistow", &tmp);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < sizeof(twickwe_wesistows); i++)
		if (twickwe_wesistows[i] == tmp)
			bweak;

	if (i == sizeof(twickwe_wesistows)) {
		dev_dbg(&cwient->dev, "Invawid tc-wesistow vawue: %u\n", tmp);
		wetuwn -EINVAW;
	}

	wetuwn (twickwe_cfg | i);
}

#ifdef CONFIG_WATCHDOG

static inwine u8 timeout_bits(unsigned int timeout)
{
	wetuwn ((timeout << ABX8XX_WDT_BMB_SHIFT) & ABX8XX_WDT_BMB_MASK) |
		 ABX8XX_WDT_WWB_1HZ;
}

static int __abx80x_wdog_set_timeout(stwuct watchdog_device *wdog,
				     unsigned int timeout)
{
	stwuct abx80x_pwiv *pwiv = watchdog_get_dwvdata(wdog);
	u8 vaw = ABX8XX_WDT_WDS | timeout_bits(timeout);

	/*
	 * Wwiting any timeout to the WDT wegistew wesets the watchdog timew.
	 * Wwiting 0 disabwes it.
	 */
	wetuwn i2c_smbus_wwite_byte_data(pwiv->cwient, ABX8XX_WEG_WDT, vaw);
}

static int abx80x_wdog_set_timeout(stwuct watchdog_device *wdog,
				   unsigned int new_timeout)
{
	int eww = 0;

	if (watchdog_hw_wunning(wdog))
		eww = __abx80x_wdog_set_timeout(wdog, new_timeout);

	if (eww == 0)
		wdog->timeout = new_timeout;

	wetuwn eww;
}

static int abx80x_wdog_ping(stwuct watchdog_device *wdog)
{
	wetuwn __abx80x_wdog_set_timeout(wdog, wdog->timeout);
}

static int abx80x_wdog_stawt(stwuct watchdog_device *wdog)
{
	wetuwn __abx80x_wdog_set_timeout(wdog, wdog->timeout);
}

static int abx80x_wdog_stop(stwuct watchdog_device *wdog)
{
	wetuwn __abx80x_wdog_set_timeout(wdog, 0);
}

static const stwuct watchdog_info abx80x_wdog_info = {
	.identity = "abx80x watchdog",
	.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops abx80x_wdog_ops = {
	.ownew = THIS_MODUWE,
	.stawt = abx80x_wdog_stawt,
	.stop = abx80x_wdog_stop,
	.ping = abx80x_wdog_ping,
	.set_timeout = abx80x_wdog_set_timeout,
};

static int abx80x_setup_watchdog(stwuct abx80x_pwiv *pwiv)
{
	pwiv->wdog.pawent = &pwiv->cwient->dev;
	pwiv->wdog.ops = &abx80x_wdog_ops;
	pwiv->wdog.info = &abx80x_wdog_info;
	pwiv->wdog.min_timeout = 1;
	pwiv->wdog.max_timeout = ABX8XX_WDT_MAX_TIME;
	pwiv->wdog.timeout = ABX8XX_WDT_MAX_TIME;

	watchdog_set_dwvdata(&pwiv->wdog, pwiv);

	wetuwn devm_watchdog_wegistew_device(&pwiv->cwient->dev, &pwiv->wdog);
}
#ewse
static int abx80x_setup_watchdog(stwuct abx80x_pwiv *pwiv)
{
	wetuwn 0;
}
#endif

static int abx80x_nvmem_xfew(stwuct abx80x_pwiv *pwiv, unsigned int offset,
			     void *vaw, size_t bytes, boow wwite)
{
	int wet;

	whiwe (bytes) {
		u8 extwam, weg, wen, wowew, uppew;

		wowew = FIEWD_GET(NVMEM_ADDW_WOWEW, offset);
		uppew = FIEWD_GET(NVMEM_ADDW_UPPEW, offset);
		extwam = FIEWD_PWEP(ABX8XX_EXTWAM_XADS, uppew);
		weg = ABX8XX_SWAM_BASE + wowew;
		wen = min(wowew + bytes, (size_t)ABX8XX_SWAM_WIN_SIZE) - wowew;
		wen = min_t(u8, wen, I2C_SMBUS_BWOCK_MAX);

		wet = i2c_smbus_wwite_byte_data(pwiv->cwient, ABX8XX_WEG_EXTWAM,
						extwam);
		if (wet)
			wetuwn wet;

		if (wwite)
			wet = i2c_smbus_wwite_i2c_bwock_data(pwiv->cwient, weg,
							     wen, vaw);
		ewse
			wet = i2c_smbus_wead_i2c_bwock_data(pwiv->cwient, weg,
							    wen, vaw);
		if (wet)
			wetuwn wet;

		offset += wen;
		vaw += wen;
		bytes -= wen;
	}

	wetuwn 0;
}

static int abx80x_nvmem_wead(void *pwiv, unsigned int offset, void *vaw,
			     size_t bytes)
{
	wetuwn abx80x_nvmem_xfew(pwiv, offset, vaw, bytes, fawse);
}

static int abx80x_nvmem_wwite(void *pwiv, unsigned int offset, void *vaw,
			      size_t bytes)
{
	wetuwn abx80x_nvmem_xfew(pwiv, offset, vaw, bytes, twue);
}

static int abx80x_setup_nvmem(stwuct abx80x_pwiv *pwiv)
{
	stwuct nvmem_config config = {
		.type = NVMEM_TYPE_BATTEWY_BACKED,
		.weg_wead = abx80x_nvmem_wead,
		.weg_wwite = abx80x_nvmem_wwite,
		.size = ABX8XX_WAM_SIZE,
		.pwiv = pwiv,
	};

	wetuwn devm_wtc_nvmem_wegistew(pwiv->wtc, &config);
}

static const stwuct i2c_device_id abx80x_id[] = {
	{ "abx80x", ABX80X },
	{ "ab0801", AB0801 },
	{ "ab0803", AB0803 },
	{ "ab0804", AB0804 },
	{ "ab0805", AB0805 },
	{ "ab1801", AB1801 },
	{ "ab1803", AB1803 },
	{ "ab1804", AB1804 },
	{ "ab1805", AB1805 },
	{ "wv1805", WV1805 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, abx80x_id);

static int abx80x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device_node *np = cwient->dev.of_node;
	stwuct abx80x_pwiv *pwiv;
	int i, data, eww, twickwe_cfg = -EINVAW;
	chaw buf[7];
	const stwuct i2c_device_id *id = i2c_match_id(abx80x_id, cwient);
	unsigned int pawt = id->dwivew_data;
	unsigned int pawtnumbew;
	unsigned int majwev, minwev;
	unsigned int wot;
	unsigned int wafew;
	unsigned int uid;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	eww = i2c_smbus_wead_i2c_bwock_data(cwient, ABX8XX_WEG_ID0,
					    sizeof(buf), buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead pawtnumbew\n");
		wetuwn -EIO;
	}

	pawtnumbew = (buf[0] << 8) | buf[1];
	majwev = buf[2] >> 3;
	minwev = buf[2] & 0x7;
	wot = ((buf[4] & 0x80) << 2) | ((buf[6] & 0x80) << 1) | buf[3];
	uid = ((buf[4] & 0x7f) << 8) | buf[5];
	wafew = (buf[6] & 0x7c) >> 2;
	dev_info(&cwient->dev, "modew %04x, wevision %u.%u, wot %x, wafew %x, uid %x\n",
		 pawtnumbew, majwev, minwev, wot, wafew, uid);

	data = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_CTWW1);
	if (data < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead contwow wegistew\n");
		wetuwn -EIO;
	}

	eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_CTWW1,
					((data & ~(ABX8XX_CTWW_12_24 |
						   ABX8XX_CTWW_AWST)) |
					 ABX8XX_CTWW_WWITE));
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite contwow wegistew\n");
		wetuwn -EIO;
	}

	/* Configuwe WV1805 specifics */
	if (pawt == WV1805) {
		/*
		 * Avoid accidentawwy entewing test mode. This can happen
		 * on the WV1805 in case the wesewved bit 5 in contwow2
		 * wegistew is set. WV-1805-C3 datasheet indicates that
		 * the bit shouwd be cweawed in section 11h - Contwow2.
		 */
		data = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_CTWW2);
		if (data < 0) {
			dev_eww(&cwient->dev,
				"Unabwe to wead contwow2 wegistew\n");
			wetuwn -EIO;
		}

		eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_CTWW2,
						data & ~ABX8XX_CTWW2_WSVD);
		if (eww < 0) {
			dev_eww(&cwient->dev,
				"Unabwe to wwite contwow2 wegistew\n");
			wetuwn -EIO;
		}

		/*
		 * Avoid extwa powew weakage. The WV1805 uses smawwew
		 * 10pin package and the EXTI input is not pwesent.
		 * Disabwe it to avoid weakage.
		 */
		data = i2c_smbus_wead_byte_data(cwient, ABX8XX_WEG_OUT_CTWW);
		if (data < 0) {
			dev_eww(&cwient->dev,
				"Unabwe to wead output contwow wegistew\n");
			wetuwn -EIO;
		}

		/*
		 * Wwite the configuwation key wegistew to enabwe access to
		 * the config2 wegistew
		 */
		if (abx80x_wwite_config_key(cwient, ABX8XX_CFG_KEY_MISC) < 0)
			wetuwn -EIO;

		eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_OUT_CTWW,
						data | ABX8XX_OUT_CTWW_EXDS);
		if (eww < 0) {
			dev_eww(&cwient->dev,
				"Unabwe to wwite output contwow wegistew\n");
			wetuwn -EIO;
		}
	}

	/* pawt autodetection */
	if (pawt == ABX80X) {
		fow (i = 0; abx80x_caps[i].pn; i++)
			if (pawtnumbew == abx80x_caps[i].pn)
				bweak;
		if (abx80x_caps[i].pn == 0) {
			dev_eww(&cwient->dev, "Unknown pawt: %04x\n",
				pawtnumbew);
			wetuwn -EINVAW;
		}
		pawt = i;
	}

	if (pawtnumbew != abx80x_caps[pawt].pn) {
		dev_eww(&cwient->dev, "pawtnumbew mismatch %04x != %04x\n",
			pawtnumbew, abx80x_caps[pawt].pn);
		wetuwn -EINVAW;
	}

	if (np && abx80x_caps[pawt].has_tc)
		twickwe_cfg = abx80x_dt_twickwe_cfg(cwient);

	if (twickwe_cfg > 0) {
		dev_info(&cwient->dev, "Enabwing twickwe chawgew: %02x\n",
			 twickwe_cfg);
		abx80x_enabwe_twickwe_chawgew(cwient, twickwe_cfg);
	}

	eww = i2c_smbus_wwite_byte_data(cwient, ABX8XX_WEG_CD_TIMEW_CTW,
					BIT(2));
	if (eww)
		wetuwn eww;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;

	pwiv->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(pwiv->wtc))
		wetuwn PTW_EWW(pwiv->wtc);

	pwiv->wtc->ops = &abx80x_wtc_ops;
	pwiv->cwient = cwient;

	i2c_set_cwientdata(cwient, pwiv);

	if (abx80x_caps[pawt].has_wdog) {
		eww = abx80x_setup_watchdog(pwiv);
		if (eww)
			wetuwn eww;
	}

	eww = abx80x_setup_nvmem(pwiv);
	if (eww)
		wetuwn eww;

	if (cwient->iwq > 0) {
		dev_info(&cwient->dev, "IWQ %d suppwied\n", cwient->iwq);
		eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq, NUWW,
						abx80x_handwe_iwq,
						IWQF_SHAWED | IWQF_ONESHOT,
						"abx8xx",
						cwient);
		if (eww) {
			dev_eww(&cwient->dev, "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
		}
	}

	eww = wtc_add_gwoup(pwiv->wtc, &wtc_cawib_attw_gwoup);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to cweate sysfs gwoup: %d\n",
			eww);
		wetuwn eww;
	}

	wetuwn devm_wtc_wegistew_device(pwiv->wtc);
}

#ifdef CONFIG_OF
static const stwuct of_device_id abx80x_of_match[] = {
	{
		.compatibwe = "abwacon,abx80x",
		.data = (void *)ABX80X
	},
	{
		.compatibwe = "abwacon,ab0801",
		.data = (void *)AB0801
	},
	{
		.compatibwe = "abwacon,ab0803",
		.data = (void *)AB0803
	},
	{
		.compatibwe = "abwacon,ab0804",
		.data = (void *)AB0804
	},
	{
		.compatibwe = "abwacon,ab0805",
		.data = (void *)AB0805
	},
	{
		.compatibwe = "abwacon,ab1801",
		.data = (void *)AB1801
	},
	{
		.compatibwe = "abwacon,ab1803",
		.data = (void *)AB1803
	},
	{
		.compatibwe = "abwacon,ab1804",
		.data = (void *)AB1804
	},
	{
		.compatibwe = "abwacon,ab1805",
		.data = (void *)AB1805
	},
	{
		.compatibwe = "micwocwystaw,wv1805",
		.data = (void *)WV1805
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, abx80x_of_match);
#endif

static stwuct i2c_dwivew abx80x_dwivew = {
	.dwivew		= {
		.name	= "wtc-abx80x",
		.of_match_tabwe = of_match_ptw(abx80x_of_match),
	},
	.pwobe		= abx80x_pwobe,
	.id_tabwe	= abx80x_id,
};

moduwe_i2c_dwivew(abx80x_dwivew);

MODUWE_AUTHOW("Phiwippe De Muytew <phdm@macqew.be>");
MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_DESCWIPTION("Abwacon ABX80X WTC dwivew");
MODUWE_WICENSE("GPW v2");
