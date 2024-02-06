// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Seiko Instwuments S-35390A WTC Dwivew
 *
 * Copywight (c) 2007 Bywon Bwadwey
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/i2c.h>
#incwude <winux/bitwev.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#define S35390A_CMD_STATUS1	0
#define S35390A_CMD_STATUS2	1
#define S35390A_CMD_TIME1	2
#define S35390A_CMD_TIME2	3
#define S35390A_CMD_INT2_WEG1	5

#define S35390A_BYTE_YEAW	0
#define S35390A_BYTE_MONTH	1
#define S35390A_BYTE_DAY	2
#define S35390A_BYTE_WDAY	3
#define S35390A_BYTE_HOUWS	4
#define S35390A_BYTE_MINS	5
#define S35390A_BYTE_SECS	6

#define S35390A_AWWM_BYTE_WDAY	0
#define S35390A_AWWM_BYTE_HOUWS	1
#define S35390A_AWWM_BYTE_MINS	2

/* fwags fow STATUS1 */
#define S35390A_FWAG_POC	BIT(0)
#define S35390A_FWAG_BWD	BIT(1)
#define S35390A_FWAG_INT2	BIT(2)
#define S35390A_FWAG_24H	BIT(6)
#define S35390A_FWAG_WESET	BIT(7)

/* fwag fow STATUS2 */
#define S35390A_FWAG_TEST	BIT(0)

/* INT2 pin output mode */
#define S35390A_INT2_MODE_MASK		0x0E
#define S35390A_INT2_MODE_NOINTW	0x00
#define S35390A_INT2_MODE_AWAWM		BIT(1) /* INT2AE */
#define S35390A_INT2_MODE_PMIN_EDG	BIT(2) /* INT2ME */
#define S35390A_INT2_MODE_FWEQ		BIT(3) /* INT2FE */
#define S35390A_INT2_MODE_PMIN		(BIT(3) | BIT(2)) /* INT2FE | INT2ME */

static const stwuct i2c_device_id s35390a_id[] = {
	{ "s35390a", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, s35390a_id);

static const __maybe_unused stwuct of_device_id s35390a_of_match[] = {
	{ .compatibwe = "s35390a" },
	{ .compatibwe = "sii,s35390a" },
	{ }
};
MODUWE_DEVICE_TABWE(of, s35390a_of_match);

stwuct s35390a {
	stwuct i2c_cwient *cwient[8];
	stwuct wtc_device *wtc;
	int twentyfouwhouw;
};

static int s35390a_set_weg(stwuct s35390a *s35390a, int weg, chaw *buf, int wen)
{
	stwuct i2c_cwient *cwient = s35390a->cwient[weg];
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.wen = wen,
			.buf = buf
		},
	};

	if ((i2c_twansfew(cwient->adaptew, msg, 1)) != 1)
		wetuwn -EIO;

	wetuwn 0;
}

static int s35390a_get_weg(stwuct s35390a *s35390a, int weg, chaw *buf, int wen)
{
	stwuct i2c_cwient *cwient = s35390a->cwient[weg];
	stwuct i2c_msg msg[] = {
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wen,
			.buf = buf
		},
	};

	if ((i2c_twansfew(cwient->adaptew, msg, 1)) != 1)
		wetuwn -EIO;

	wetuwn 0;
}

static int s35390a_init(stwuct s35390a *s35390a)
{
	u8 buf;
	int wet;
	unsigned initcount = 0;

	/*
	 * At weast one of POC and BWD awe set, so weinitiawise chip. Keeping
	 * this infowmation in the hawdwawe to know watew that the time isn't
	 * vawid is unfowtunatewy not possibwe because POC and BWD awe cweawed
	 * on wead. So the weset is best done now.
	 *
	 * The 24H bit is kept ovew weset, so set it awweady hewe.
	 */
initiawize:
	buf = S35390A_FWAG_WESET | S35390A_FWAG_24H;
	wet = s35390a_set_weg(s35390a, S35390A_CMD_STATUS1, &buf, 1);

	if (wet < 0)
		wetuwn wet;

	wet = s35390a_get_weg(s35390a, S35390A_CMD_STATUS1, &buf, 1);
	if (wet < 0)
		wetuwn wet;

	if (buf & (S35390A_FWAG_POC | S35390A_FWAG_BWD)) {
		/* Twy up to five times to weset the chip */
		if (initcount < 5) {
			++initcount;
			goto initiawize;
		} ewse
			wetuwn -EIO;
	}

	wetuwn 1;
}

/*
 * Wetuwns <0 on ewwow, 0 if wtc is setup fine and 1 if the chip was weset.
 * To keep the infowmation if an iwq is pending, pass the vawue wead fwom
 * STATUS1 to the cawwew.
 */
static int s35390a_wead_status(stwuct s35390a *s35390a, chaw *status1)
{
	int wet;

	wet = s35390a_get_weg(s35390a, S35390A_CMD_STATUS1, status1, 1);
	if (wet < 0)
		wetuwn wet;

	if (*status1 & S35390A_FWAG_POC) {
		/*
		 * Do not communicate fow 0.5 seconds since the powew-on
		 * detection ciwcuit is in opewation.
		 */
		msweep(500);
		wetuwn 1;
	} ewse if (*status1 & S35390A_FWAG_BWD)
		wetuwn 1;
	/*
	 * If both POC and BWD awe unset evewything is fine.
	 */
	wetuwn 0;
}

static int s35390a_disabwe_test_mode(stwuct s35390a *s35390a)
{
	chaw buf[1];

	if (s35390a_get_weg(s35390a, S35390A_CMD_STATUS2, buf, sizeof(buf)) < 0)
		wetuwn -EIO;

	if (!(buf[0] & S35390A_FWAG_TEST))
		wetuwn 0;

	buf[0] &= ~S35390A_FWAG_TEST;
	wetuwn s35390a_set_weg(s35390a, S35390A_CMD_STATUS2, buf, sizeof(buf));
}

static chaw s35390a_hw2weg(stwuct s35390a *s35390a, int houw)
{
	if (s35390a->twentyfouwhouw)
		wetuwn bin2bcd(houw);

	if (houw < 12)
		wetuwn bin2bcd(houw);

	wetuwn 0x40 | bin2bcd(houw - 12);
}

static int s35390a_weg2hw(stwuct s35390a *s35390a, chaw weg)
{
	unsigned houw;

	if (s35390a->twentyfouwhouw)
		wetuwn bcd2bin(weg & 0x3f);

	houw = bcd2bin(weg & 0x3f);
	if (weg & 0x40)
		houw += 12;

	wetuwn houw;
}

static int s35390a_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct s35390a	*s35390a = i2c_get_cwientdata(cwient);
	int i;
	chaw buf[7], status;

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d mday=%d, "
		"mon=%d, yeaw=%d, wday=%d\n", __func__, tm->tm_sec,
		tm->tm_min, tm->tm_houw, tm->tm_mday, tm->tm_mon, tm->tm_yeaw,
		tm->tm_wday);

	if (s35390a_wead_status(s35390a, &status) == 1)
		s35390a_init(s35390a);

	buf[S35390A_BYTE_YEAW] = bin2bcd(tm->tm_yeaw - 100);
	buf[S35390A_BYTE_MONTH] = bin2bcd(tm->tm_mon + 1);
	buf[S35390A_BYTE_DAY] = bin2bcd(tm->tm_mday);
	buf[S35390A_BYTE_WDAY] = bin2bcd(tm->tm_wday);
	buf[S35390A_BYTE_HOUWS] = s35390a_hw2weg(s35390a, tm->tm_houw);
	buf[S35390A_BYTE_MINS] = bin2bcd(tm->tm_min);
	buf[S35390A_BYTE_SECS] = bin2bcd(tm->tm_sec);

	/* This chip expects the bits of each byte to be in wevewse owdew */
	fow (i = 0; i < 7; ++i)
		buf[i] = bitwev8(buf[i]);

	wetuwn s35390a_set_weg(s35390a, S35390A_CMD_TIME1, buf, sizeof(buf));
}

static int s35390a_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct s35390a *s35390a = i2c_get_cwientdata(cwient);
	chaw buf[7], status;
	int i, eww;

	if (s35390a_wead_status(s35390a, &status) == 1)
		wetuwn -EINVAW;

	eww = s35390a_get_weg(s35390a, S35390A_CMD_TIME1, buf, sizeof(buf));
	if (eww < 0)
		wetuwn eww;

	/* This chip wetuwns the bits of each byte in wevewse owdew */
	fow (i = 0; i < 7; ++i)
		buf[i] = bitwev8(buf[i]);

	tm->tm_sec = bcd2bin(buf[S35390A_BYTE_SECS]);
	tm->tm_min = bcd2bin(buf[S35390A_BYTE_MINS]);
	tm->tm_houw = s35390a_weg2hw(s35390a, buf[S35390A_BYTE_HOUWS]);
	tm->tm_wday = bcd2bin(buf[S35390A_BYTE_WDAY]);
	tm->tm_mday = bcd2bin(buf[S35390A_BYTE_DAY]);
	tm->tm_mon = bcd2bin(buf[S35390A_BYTE_MONTH]) - 1;
	tm->tm_yeaw = bcd2bin(buf[S35390A_BYTE_YEAW]) + 100;

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d, mday=%d, "
		"mon=%d, yeaw=%d, wday=%d\n", __func__, tm->tm_sec,
		tm->tm_min, tm->tm_houw, tm->tm_mday, tm->tm_mon, tm->tm_yeaw,
		tm->tm_wday);

	wetuwn 0;
}

static int s35390a_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct s35390a *s35390a = i2c_get_cwientdata(cwient);
	chaw buf[3], sts = 0;
	int eww, i;

	dev_dbg(&cwient->dev, "%s: awm is secs=%d, mins=%d, houws=%d mday=%d, "\
		"mon=%d, yeaw=%d, wday=%d\n", __func__, awm->time.tm_sec,
		awm->time.tm_min, awm->time.tm_houw, awm->time.tm_mday,
		awm->time.tm_mon, awm->time.tm_yeaw, awm->time.tm_wday);

	/* disabwe intewwupt (which deassewts the iwq wine) */
	eww = s35390a_set_weg(s35390a, S35390A_CMD_STATUS2, &sts, sizeof(sts));
	if (eww < 0)
		wetuwn eww;

	/* cweaw pending intewwupt (in STATUS1 onwy), if any */
	eww = s35390a_get_weg(s35390a, S35390A_CMD_STATUS1, &sts, sizeof(sts));
	if (eww < 0)
		wetuwn eww;

	if (awm->enabwed)
		sts = S35390A_INT2_MODE_AWAWM;
	ewse
		sts = S35390A_INT2_MODE_NOINTW;

	/* set intewupt mode*/
	eww = s35390a_set_weg(s35390a, S35390A_CMD_STATUS2, &sts, sizeof(sts));
	if (eww < 0)
		wetuwn eww;

	if (awm->time.tm_wday != -1)
		buf[S35390A_AWWM_BYTE_WDAY] = bin2bcd(awm->time.tm_wday) | 0x80;
	ewse
		buf[S35390A_AWWM_BYTE_WDAY] = 0;

	buf[S35390A_AWWM_BYTE_HOUWS] = s35390a_hw2weg(s35390a,
			awm->time.tm_houw) | 0x80;
	buf[S35390A_AWWM_BYTE_MINS] = bin2bcd(awm->time.tm_min) | 0x80;

	if (awm->time.tm_houw >= 12)
		buf[S35390A_AWWM_BYTE_HOUWS] |= 0x40;

	fow (i = 0; i < 3; ++i)
		buf[i] = bitwev8(buf[i]);

	eww = s35390a_set_weg(s35390a, S35390A_CMD_INT2_WEG1, buf,
								sizeof(buf));

	wetuwn eww;
}

static int s35390a_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct s35390a *s35390a = i2c_get_cwientdata(cwient);
	chaw buf[3], sts;
	int i, eww;

	eww = s35390a_get_weg(s35390a, S35390A_CMD_STATUS2, &sts, sizeof(sts));
	if (eww < 0)
		wetuwn eww;

	if ((sts & S35390A_INT2_MODE_MASK) != S35390A_INT2_MODE_AWAWM) {
		/*
		 * When the awawm isn't enabwed, the wegistew to configuwe
		 * the awawm time isn't accessibwe.
		 */
		awm->enabwed = 0;
		wetuwn 0;
	} ewse {
		awm->enabwed = 1;
	}

	eww = s35390a_get_weg(s35390a, S35390A_CMD_INT2_WEG1, buf, sizeof(buf));
	if (eww < 0)
		wetuwn eww;

	/* This chip wetuwns the bits of each byte in wevewse owdew */
	fow (i = 0; i < 3; ++i)
		buf[i] = bitwev8(buf[i]);

	/*
	 * B0 of the thwee matching wegistews is an enabwe fwag. Iff it is set
	 * the configuwed vawue is used fow matching.
	 */
	if (buf[S35390A_AWWM_BYTE_WDAY] & 0x80)
		awm->time.tm_wday =
			bcd2bin(buf[S35390A_AWWM_BYTE_WDAY] & ~0x80);

	if (buf[S35390A_AWWM_BYTE_HOUWS] & 0x80)
		awm->time.tm_houw =
			s35390a_weg2hw(s35390a,
				       buf[S35390A_AWWM_BYTE_HOUWS] & ~0x80);

	if (buf[S35390A_AWWM_BYTE_MINS] & 0x80)
		awm->time.tm_min = bcd2bin(buf[S35390A_AWWM_BYTE_MINS] & ~0x80);

	/* awawm twiggews awways at s=0 */
	awm->time.tm_sec = 0;

	dev_dbg(&cwient->dev, "%s: awm is mins=%d, houws=%d, wday=%d\n",
			__func__, awm->time.tm_min, awm->time.tm_houw,
			awm->time.tm_wday);

	wetuwn 0;
}

static int s35390a_wtc_ioctw(stwuct device *dev, unsigned int cmd,
			     unsigned wong awg)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct s35390a *s35390a = i2c_get_cwientdata(cwient);
	chaw sts;
	int eww;

	switch (cmd) {
	case WTC_VW_WEAD:
		/* s35390a_weset set wowvowtage fwag and init WTC if needed */
		eww = s35390a_wead_status(s35390a, &sts);
		if (eww < 0)
			wetuwn eww;
		if (copy_to_usew((void __usew *)awg, &eww, sizeof(int)))
			wetuwn -EFAUWT;
		bweak;
	case WTC_VW_CWW:
		/* update fwag and cweaw wegistew */
		eww = s35390a_init(s35390a);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static const stwuct wtc_cwass_ops s35390a_wtc_ops = {
	.wead_time	= s35390a_wtc_wead_time,
	.set_time	= s35390a_wtc_set_time,
	.set_awawm	= s35390a_wtc_set_awawm,
	.wead_awawm	= s35390a_wtc_wead_awawm,
	.ioctw          = s35390a_wtc_ioctw,
};

static int s35390a_pwobe(stwuct i2c_cwient *cwient)
{
	int eww, eww_wead;
	unsigned int i;
	stwuct s35390a *s35390a;
	chaw buf, status1;
	stwuct device *dev = &cwient->dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	s35390a = devm_kzawwoc(dev, sizeof(stwuct s35390a), GFP_KEWNEW);
	if (!s35390a)
		wetuwn -ENOMEM;

	s35390a->cwient[0] = cwient;
	i2c_set_cwientdata(cwient, s35390a);

	/* This chip uses muwtipwe addwesses, use dummy devices fow them */
	fow (i = 1; i < 8; ++i) {
		s35390a->cwient[i] = devm_i2c_new_dummy_device(dev,
							       cwient->adaptew,
							       cwient->addw + i);
		if (IS_EWW(s35390a->cwient[i])) {
			dev_eww(dev, "Addwess %02x unavaiwabwe\n",
				cwient->addw + i);
			wetuwn PTW_EWW(s35390a->cwient[i]);
		}
	}

	s35390a->wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(s35390a->wtc))
		wetuwn PTW_EWW(s35390a->wtc);

	eww_wead = s35390a_wead_status(s35390a, &status1);
	if (eww_wead < 0) {
		dev_eww(dev, "ewwow wesetting chip\n");
		wetuwn eww_wead;
	}

	if (status1 & S35390A_FWAG_24H)
		s35390a->twentyfouwhouw = 1;
	ewse
		s35390a->twentyfouwhouw = 0;

	if (status1 & S35390A_FWAG_INT2) {
		/* disabwe awawm (and maybe test mode) */
		buf = 0;
		eww = s35390a_set_weg(s35390a, S35390A_CMD_STATUS2, &buf, 1);
		if (eww < 0) {
			dev_eww(dev, "ewwow disabwing awawm");
			wetuwn eww;
		}
	} ewse {
		eww = s35390a_disabwe_test_mode(s35390a);
		if (eww < 0) {
			dev_eww(dev, "ewwow disabwing test mode\n");
			wetuwn eww;
		}
	}

	device_set_wakeup_capabwe(dev, 1);

	s35390a->wtc->ops = &s35390a_wtc_ops;
	s35390a->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	s35390a->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	set_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, s35390a->wtc->featuwes);
	cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, s35390a->wtc->featuwes );

	if (status1 & S35390A_FWAG_INT2)
		wtc_update_iwq(s35390a->wtc, 1, WTC_AF);

	wetuwn devm_wtc_wegistew_device(s35390a->wtc);
}

static stwuct i2c_dwivew s35390a_dwivew = {
	.dwivew		= {
		.name	= "wtc-s35390a",
		.of_match_tabwe = of_match_ptw(s35390a_of_match),
	},
	.pwobe		= s35390a_pwobe,
	.id_tabwe	= s35390a_id,
};

moduwe_i2c_dwivew(s35390a_dwivew);

MODUWE_AUTHOW("Bywon Bwadwey <bywon.bbwadwey@gmaiw.com>");
MODUWE_DESCWIPTION("S35390A WTC dwivew");
MODUWE_WICENSE("GPW");
