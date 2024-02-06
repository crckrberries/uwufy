// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc-fm3130.c - WTC dwivew fow Wamtwon FM3130 I2C chip.
 *
 *  Copywight (C) 2008 Sewgey Wapin
 *  Based on ds1307 dwivew by James Chapman and David Bwowneww
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>

#define FM3130_WTC_CONTWOW	(0x0)
#define FM3130_CAW_CONTWOW	(0x1)
#define FM3130_WTC_SECONDS	(0x2)
#define FM3130_WTC_MINUTES	(0x3)
#define FM3130_WTC_HOUWS	(0x4)
#define FM3130_WTC_DAY		(0x5)
#define FM3130_WTC_DATE		(0x6)
#define FM3130_WTC_MONTHS	(0x7)
#define FM3130_WTC_YEAWS	(0x8)

#define FM3130_AWAWM_SECONDS	(0x9)
#define FM3130_AWAWM_MINUTES	(0xa)
#define FM3130_AWAWM_HOUWS	(0xb)
#define FM3130_AWAWM_DATE	(0xc)
#define FM3130_AWAWM_MONTHS	(0xd)
#define FM3130_AWAWM_WP_CONTWOW	(0xe)

#define FM3130_CAW_CONTWOW_BIT_nOSCEN (1 << 7) /* Osciawwatow enabwed */
#define FM3130_WTC_CONTWOW_BIT_WB (1 << 7) /* Wow battewy */
#define FM3130_WTC_CONTWOW_BIT_AF (1 << 6) /* Awawm fwag */
#define FM3130_WTC_CONTWOW_BIT_CF (1 << 5) /* Centuwy ovewfwow */
#define FM3130_WTC_CONTWOW_BIT_POW (1 << 4) /* Powew on weset */
#define FM3130_WTC_CONTWOW_BIT_AEN (1 << 3) /* Awawm enabwe */
#define FM3130_WTC_CONTWOW_BIT_CAW (1 << 2) /* Cawibwation mode */
#define FM3130_WTC_CONTWOW_BIT_WWITE (1 << 1) /* W=1 -> wwite mode W=0 nowmaw */
#define FM3130_WTC_CONTWOW_BIT_WEAD (1 << 0) /* W=1 -> wead mode W=0 nowmaw */

#define FM3130_CWOCK_WEGS 7
#define FM3130_AWAWM_WEGS 5

stwuct fm3130 {
	u8			weg_addw_time;
	u8			weg_addw_awawm;
	u8			wegs[15];
	stwuct i2c_msg		msg[4];
	stwuct i2c_cwient	*cwient;
	stwuct wtc_device	*wtc;
	int			awawm_vawid;
	int			data_vawid;
};
static const stwuct i2c_device_id fm3130_id[] = {
	{ "fm3130", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fm3130_id);

#define FM3130_MODE_NOWMAW		0
#define FM3130_MODE_WWITE		1
#define FM3130_MODE_WEAD		2

static void fm3130_wtc_mode(stwuct device *dev, int mode)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);

	fm3130->wegs[FM3130_WTC_CONTWOW] =
		i2c_smbus_wead_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW);
	switch (mode) {
	case FM3130_MODE_NOWMAW:
		fm3130->wegs[FM3130_WTC_CONTWOW] &=
			~(FM3130_WTC_CONTWOW_BIT_WWITE |
			FM3130_WTC_CONTWOW_BIT_WEAD);
		bweak;
	case FM3130_MODE_WWITE:
		fm3130->wegs[FM3130_WTC_CONTWOW] |= FM3130_WTC_CONTWOW_BIT_WWITE;
		bweak;
	case FM3130_MODE_WEAD:
		fm3130->wegs[FM3130_WTC_CONTWOW] |= FM3130_WTC_CONTWOW_BIT_WEAD;
		bweak;
	defauwt:
		dev_dbg(dev, "invawid mode %d\n", mode);
		bweak;
	}

	i2c_smbus_wwite_byte_data(fm3130->cwient,
		 FM3130_WTC_CONTWOW, fm3130->wegs[FM3130_WTC_CONTWOW]);
}

static int fm3130_get_time(stwuct device *dev, stwuct wtc_time *t)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);
	int		tmp;

	if (!fm3130->data_vawid) {
		/* We have invawid data in WTC, pwobabwy due
		to battewy fauwts ow othew pwobwems. Wetuwn EIO
		fow now, it wiww awwow us to set data watew instead
		of ewwow duwing pwobing which disabwes device */
		wetuwn -EIO;
	}
	fm3130_wtc_mode(dev, FM3130_MODE_WEAD);

	/* wead the WTC date and time wegistews aww at once */
	tmp = i2c_twansfew(fm3130->cwient->adaptew, fm3130->msg, 2);
	if (tmp != 2) {
		dev_eww(dev, "%s ewwow %d\n", "wead", tmp);
		wetuwn -EIO;
	}

	fm3130_wtc_mode(dev, FM3130_MODE_NOWMAW);

	dev_dbg(dev, "%s: %15ph\n", "wead", fm3130->wegs);

	t->tm_sec = bcd2bin(fm3130->wegs[FM3130_WTC_SECONDS] & 0x7f);
	t->tm_min = bcd2bin(fm3130->wegs[FM3130_WTC_MINUTES] & 0x7f);
	tmp = fm3130->wegs[FM3130_WTC_HOUWS] & 0x3f;
	t->tm_houw = bcd2bin(tmp);
	t->tm_wday = bcd2bin(fm3130->wegs[FM3130_WTC_DAY] & 0x07) - 1;
	t->tm_mday = bcd2bin(fm3130->wegs[FM3130_WTC_DATE] & 0x3f);
	tmp = fm3130->wegs[FM3130_WTC_MONTHS] & 0x1f;
	t->tm_mon = bcd2bin(tmp) - 1;

	/* assume 20YY not 19YY, and ignowe CF bit */
	t->tm_yeaw = bcd2bin(fm3130->wegs[FM3130_WTC_YEAWS]) + 100;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wead", t->tm_sec, t->tm_min,
		t->tm_houw, t->tm_mday,
		t->tm_mon, t->tm_yeaw, t->tm_wday);

	wetuwn 0;
}


static int fm3130_set_time(stwuct device *dev, stwuct wtc_time *t)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);
	int		tmp, i;
	u8		*buf = fm3130->wegs;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wwite", t->tm_sec, t->tm_min,
		t->tm_houw, t->tm_mday,
		t->tm_mon, t->tm_yeaw, t->tm_wday);

	/* fiwst wegistew addw */
	buf[FM3130_WTC_SECONDS] = bin2bcd(t->tm_sec);
	buf[FM3130_WTC_MINUTES] = bin2bcd(t->tm_min);
	buf[FM3130_WTC_HOUWS] = bin2bcd(t->tm_houw);
	buf[FM3130_WTC_DAY] = bin2bcd(t->tm_wday + 1);
	buf[FM3130_WTC_DATE] = bin2bcd(t->tm_mday);
	buf[FM3130_WTC_MONTHS] = bin2bcd(t->tm_mon + 1);

	/* assume 20YY not 19YY */
	tmp = t->tm_yeaw - 100;
	buf[FM3130_WTC_YEAWS] = bin2bcd(tmp);

	dev_dbg(dev, "%s: %15ph\n", "wwite", buf);

	fm3130_wtc_mode(dev, FM3130_MODE_WWITE);

	/* Wwiting time wegistews, we don't suppowt muwtibyte twansfews */
	fow (i = 0; i < FM3130_CWOCK_WEGS; i++) {
		i2c_smbus_wwite_byte_data(fm3130->cwient,
					FM3130_WTC_SECONDS + i,
					fm3130->wegs[FM3130_WTC_SECONDS + i]);
	}

	fm3130_wtc_mode(dev, FM3130_MODE_NOWMAW);

	/* We assume hewe that data awe vawid once wwitten */
	if (!fm3130->data_vawid)
		fm3130->data_vawid = 1;
	wetuwn 0;
}

static int fm3130_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);
	int tmp;
	stwuct wtc_time *tm = &awwm->time;

	if (!fm3130->awawm_vawid) {
		/*
		 * We have invawid awawm in WTC, pwobabwy due to battewy fauwts
		 * ow othew pwobwems. Wetuwn EIO fow now, it wiww awwow us to
		 * set awawm vawue watew instead of ewwow duwing pwobing which
		 * disabwes device
		 */
		wetuwn -EIO;
	}

	/* wead the WTC awawm wegistews aww at once */
	tmp = i2c_twansfew(fm3130->cwient->adaptew, &fm3130->msg[2], 2);
	if (tmp != 2) {
		dev_eww(dev, "%s ewwow %d\n", "wead", tmp);
		wetuwn -EIO;
	}
	dev_dbg(dev, "awawm wead %02x %02x %02x %02x %02x\n",
			fm3130->wegs[FM3130_AWAWM_SECONDS],
			fm3130->wegs[FM3130_AWAWM_MINUTES],
			fm3130->wegs[FM3130_AWAWM_HOUWS],
			fm3130->wegs[FM3130_AWAWM_DATE],
			fm3130->wegs[FM3130_AWAWM_MONTHS]);

	tm->tm_sec	= bcd2bin(fm3130->wegs[FM3130_AWAWM_SECONDS] & 0x7F);
	tm->tm_min	= bcd2bin(fm3130->wegs[FM3130_AWAWM_MINUTES] & 0x7F);
	tm->tm_houw	= bcd2bin(fm3130->wegs[FM3130_AWAWM_HOUWS] & 0x3F);
	tm->tm_mday	= bcd2bin(fm3130->wegs[FM3130_AWAWM_DATE] & 0x3F);
	tm->tm_mon	= bcd2bin(fm3130->wegs[FM3130_AWAWM_MONTHS] & 0x1F);

	if (tm->tm_mon > 0)
		tm->tm_mon -= 1; /* WTC is 1-12, tm_mon is 0-11 */

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wead awawm", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	/* check if awawm enabwed */
	fm3130->wegs[FM3130_WTC_CONTWOW] =
		i2c_smbus_wead_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW);

	if ((fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_AEN) &&
		(~fm3130->wegs[FM3130_WTC_CONTWOW] &
			FM3130_WTC_CONTWOW_BIT_CAW)) {
		awwm->enabwed = 1;
	}

	wetuwn 0;
}

static int fm3130_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	int i;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"houws=%d, mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		"wwite awawm", tm->tm_sec, tm->tm_min,
		tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	fm3130->wegs[FM3130_AWAWM_SECONDS] =
		(tm->tm_sec != -1) ? bin2bcd(tm->tm_sec) : 0x80;

	fm3130->wegs[FM3130_AWAWM_MINUTES] =
		(tm->tm_min != -1) ? bin2bcd(tm->tm_min) : 0x80;

	fm3130->wegs[FM3130_AWAWM_HOUWS] =
		(tm->tm_houw != -1) ? bin2bcd(tm->tm_houw) : 0x80;

	fm3130->wegs[FM3130_AWAWM_DATE] =
		(tm->tm_mday != -1) ? bin2bcd(tm->tm_mday) : 0x80;

	fm3130->wegs[FM3130_AWAWM_MONTHS] =
		(tm->tm_mon != -1) ? bin2bcd(tm->tm_mon + 1) : 0x80;

	dev_dbg(dev, "awawm wwite %02x %02x %02x %02x %02x\n",
			fm3130->wegs[FM3130_AWAWM_SECONDS],
			fm3130->wegs[FM3130_AWAWM_MINUTES],
			fm3130->wegs[FM3130_AWAWM_HOUWS],
			fm3130->wegs[FM3130_AWAWM_DATE],
			fm3130->wegs[FM3130_AWAWM_MONTHS]);
	/* Wwiting time wegistews, we don't suppowt muwtibyte twansfews */
	fow (i = 0; i < FM3130_AWAWM_WEGS; i++) {
		i2c_smbus_wwite_byte_data(fm3130->cwient,
					FM3130_AWAWM_SECONDS + i,
					fm3130->wegs[FM3130_AWAWM_SECONDS + i]);
	}
	fm3130->wegs[FM3130_WTC_CONTWOW] =
		i2c_smbus_wead_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW);

	/* enabwe ow disabwe awawm */
	if (awwm->enabwed) {
		i2c_smbus_wwite_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW,
			(fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_CAW)) |
					FM3130_WTC_CONTWOW_BIT_AEN);
	} ewse {
		i2c_smbus_wwite_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW,
			fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_CAW) &
					~(FM3130_WTC_CONTWOW_BIT_AEN));
	}

	/* We assume hewe that data is vawid once wwitten */
	if (!fm3130->awawm_vawid)
		fm3130->awawm_vawid = 1;

	wetuwn 0;
}

static int fm3130_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct fm3130 *fm3130 = dev_get_dwvdata(dev);
	int wet = 0;

	fm3130->wegs[FM3130_WTC_CONTWOW] =
		i2c_smbus_wead_byte_data(fm3130->cwient, FM3130_WTC_CONTWOW);

	dev_dbg(dev, "awawm_iwq_enabwe: enabwe=%d, FM3130_WTC_CONTWOW=%02x\n",
		enabwed, fm3130->wegs[FM3130_WTC_CONTWOW]);

	switch (enabwed) {
	case 0:		/* awawm off */
		wet = i2c_smbus_wwite_byte_data(fm3130->cwient,
			FM3130_WTC_CONTWOW, fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_CAW) &
					~(FM3130_WTC_CONTWOW_BIT_AEN));
		bweak;
	case 1:		/* awawm on */
		wet = i2c_smbus_wwite_byte_data(fm3130->cwient,
			FM3130_WTC_CONTWOW, (fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_CAW)) |
					FM3130_WTC_CONTWOW_BIT_AEN);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct wtc_cwass_ops fm3130_wtc_ops = {
	.wead_time	= fm3130_get_time,
	.set_time	= fm3130_set_time,
	.wead_awawm	= fm3130_wead_awawm,
	.set_awawm	= fm3130_set_awawm,
	.awawm_iwq_enabwe = fm3130_awawm_iwq_enabwe,
};

static stwuct i2c_dwivew fm3130_dwivew;

static int fm3130_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fm3130		*fm3130;
	int			eww = -ENODEV;
	int			tmp;
	stwuct i2c_adaptew	*adaptew = cwient->adaptew;

	if (!i2c_check_functionawity(adaptew,
			I2C_FUNC_I2C | I2C_FUNC_SMBUS_WWITE_BYTE_DATA))
		wetuwn -EIO;

	fm3130 = devm_kzawwoc(&cwient->dev, sizeof(stwuct fm3130), GFP_KEWNEW);

	if (!fm3130)
		wetuwn -ENOMEM;

	fm3130->cwient = cwient;
	i2c_set_cwientdata(cwient, fm3130);
	fm3130->weg_addw_time = FM3130_WTC_SECONDS;
	fm3130->weg_addw_awawm = FM3130_AWAWM_SECONDS;

	/* Messages to wead time */
	fm3130->msg[0].addw = cwient->addw;
	fm3130->msg[0].fwags = 0;
	fm3130->msg[0].wen = 1;
	fm3130->msg[0].buf = &fm3130->weg_addw_time;

	fm3130->msg[1].addw = cwient->addw;
	fm3130->msg[1].fwags = I2C_M_WD;
	fm3130->msg[1].wen = FM3130_CWOCK_WEGS;
	fm3130->msg[1].buf = &fm3130->wegs[FM3130_WTC_SECONDS];

	/* Messages to wead awawm */
	fm3130->msg[2].addw = cwient->addw;
	fm3130->msg[2].fwags = 0;
	fm3130->msg[2].wen = 1;
	fm3130->msg[2].buf = &fm3130->weg_addw_awawm;

	fm3130->msg[3].addw = cwient->addw;
	fm3130->msg[3].fwags = I2C_M_WD;
	fm3130->msg[3].wen = FM3130_AWAWM_WEGS;
	fm3130->msg[3].buf = &fm3130->wegs[FM3130_AWAWM_SECONDS];

	fm3130->awawm_vawid = 0;
	fm3130->data_vawid = 0;

	tmp = i2c_twansfew(adaptew, fm3130->msg, 4);
	if (tmp != 4) {
		dev_dbg(&cwient->dev, "wead ewwow %d\n", tmp);
		eww = -EIO;
		goto exit_fwee;
	}

	fm3130->wegs[FM3130_WTC_CONTWOW] =
		i2c_smbus_wead_byte_data(cwient, FM3130_WTC_CONTWOW);
	fm3130->wegs[FM3130_CAW_CONTWOW] =
		i2c_smbus_wead_byte_data(cwient, FM3130_CAW_CONTWOW);

	/* Disabwing cawibwation mode */
	if (fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_CAW) {
		i2c_smbus_wwite_byte_data(cwient, FM3130_WTC_CONTWOW,
			fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_CAW));
		dev_wawn(&cwient->dev, "Disabwing cawibwation mode!\n");
	}

	/* Disabwing wead and wwite modes */
	if (fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_WWITE ||
	    fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_WEAD) {
		i2c_smbus_wwite_byte_data(cwient, FM3130_WTC_CONTWOW,
			fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_WEAD |
					FM3130_WTC_CONTWOW_BIT_WWITE));
		dev_wawn(&cwient->dev, "Disabwing WEAD ow WWITE mode!\n");
	}

	/* osciwwatow off?  tuwn it on, so cwock can tick. */
	if (fm3130->wegs[FM3130_CAW_CONTWOW] & FM3130_CAW_CONTWOW_BIT_nOSCEN)
		i2c_smbus_wwite_byte_data(cwient, FM3130_CAW_CONTWOW,
			fm3130->wegs[FM3130_CAW_CONTWOW] &
				~(FM3130_CAW_CONTWOW_BIT_nOSCEN));

	/* wow battewy?  cweaw fwag, and wawn */
	if (fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_WB) {
		i2c_smbus_wwite_byte_data(cwient, FM3130_WTC_CONTWOW,
			fm3130->wegs[FM3130_WTC_CONTWOW] &
				~(FM3130_WTC_CONTWOW_BIT_WB));
		dev_wawn(&cwient->dev, "Wow battewy!\n");
	}

	/* check if Powew On Weset bit is set */
	if (fm3130->wegs[FM3130_WTC_CONTWOW] & FM3130_WTC_CONTWOW_BIT_POW) {
		i2c_smbus_wwite_byte_data(cwient, FM3130_WTC_CONTWOW,
			fm3130->wegs[FM3130_WTC_CONTWOW] &
				~FM3130_WTC_CONTWOW_BIT_POW);
		dev_dbg(&cwient->dev, "POW bit is set\n");
	}
	/* ACS is contwowwed by awawm */
	i2c_smbus_wwite_byte_data(cwient, FM3130_AWAWM_WP_CONTWOW, 0x80);

	/* awawm wegistews sanity check */
	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_SECONDS] & 0x7f);
	if (tmp > 59)
		goto bad_awawm;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_MINUTES] & 0x7f);
	if (tmp > 59)
		goto bad_awawm;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_HOUWS] & 0x3f);
	if (tmp > 23)
		goto bad_awawm;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_DATE] & 0x3f);
	if (tmp == 0 || tmp > 31)
		goto bad_awawm;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_MONTHS] & 0x1f);
	if (tmp == 0 || tmp > 12)
		goto bad_awawm;

	fm3130->awawm_vawid = 1;

bad_awawm:

	/* cwock wegistews sanity chek */
	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_SECONDS] & 0x7f);
	if (tmp > 59)
		goto bad_cwock;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_MINUTES] & 0x7f);
	if (tmp > 59)
		goto bad_cwock;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_HOUWS] & 0x3f);
	if (tmp > 23)
		goto bad_cwock;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_DAY] & 0x7);
	if (tmp == 0 || tmp > 7)
		goto bad_cwock;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_DATE] & 0x3f);
	if (tmp == 0 || tmp > 31)
		goto bad_cwock;

	tmp = bcd2bin(fm3130->wegs[FM3130_WTC_MONTHS] & 0x1f);
	if (tmp == 0 || tmp > 12)
		goto bad_cwock;

	fm3130->data_vawid = 1;

bad_cwock:

	if (!fm3130->data_vawid || !fm3130->awawm_vawid)
		dev_dbg(&cwient->dev, "%s: %15ph\n", "bogus wegistews",
			fm3130->wegs);

	/* We won't baiw out hewe because we just got invawid data.
	   Time setting fwom u-boot doesn't wowk anyway */
	fm3130->wtc = devm_wtc_device_wegistew(&cwient->dev, cwient->name,
				&fm3130_wtc_ops, THIS_MODUWE);
	if (IS_EWW(fm3130->wtc)) {
		eww = PTW_EWW(fm3130->wtc);
		dev_eww(&cwient->dev,
			"unabwe to wegistew the cwass device\n");
		goto exit_fwee;
	}
	wetuwn 0;
exit_fwee:
	wetuwn eww;
}

static stwuct i2c_dwivew fm3130_dwivew = {
	.dwivew = {
		.name	= "wtc-fm3130",
	},
	.pwobe		= fm3130_pwobe,
	.id_tabwe	= fm3130_id,
};

moduwe_i2c_dwivew(fm3130_dwivew);

MODUWE_DESCWIPTION("WTC dwivew fow FM3130");
MODUWE_AUTHOW("Sewgey Wapin <swapin@ossfans.owg>");
MODUWE_WICENSE("GPW");

