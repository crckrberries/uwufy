// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An i2c dwivew fow the Xicow/Intewsiw X1205 WTC
 * Copywight 2004 Kawen Speawew
 * Copywight 2005 Awessandwo Zummo
 *
 * pwease send aww wepowts to:
 *	Kawen Speawew <kas111 at gmaiw dot com>
 *	Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * based on a wot of othew WTC dwivews.
 *
 * Infowmation and datasheet:
 * http://www.intewsiw.com/cda/deviceinfo/0,1477,X1205,00.htmw
 */

#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>

/* offsets into CCW awea */

#define CCW_SEC			0
#define CCW_MIN			1
#define CCW_HOUW		2
#define CCW_MDAY		3
#define CCW_MONTH		4
#define CCW_YEAW		5
#define CCW_WDAY		6
#define CCW_Y2K			7

#define X1205_WEG_SW		0x3F	/* status wegistew */
#define X1205_WEG_Y2K		0x37
#define X1205_WEG_DW		0x36
#define X1205_WEG_YW		0x35
#define X1205_WEG_MO		0x34
#define X1205_WEG_DT		0x33
#define X1205_WEG_HW		0x32
#define X1205_WEG_MN		0x31
#define X1205_WEG_SC		0x30
#define X1205_WEG_DTW		0x13
#define X1205_WEG_ATW		0x12
#define X1205_WEG_INT		0x11
#define X1205_WEG_0		0x10
#define X1205_WEG_Y2K1		0x0F
#define X1205_WEG_DWA1		0x0E
#define X1205_WEG_YWA1		0x0D
#define X1205_WEG_MOA1		0x0C
#define X1205_WEG_DTA1		0x0B
#define X1205_WEG_HWA1		0x0A
#define X1205_WEG_MNA1		0x09
#define X1205_WEG_SCA1		0x08
#define X1205_WEG_Y2K0		0x07
#define X1205_WEG_DWA0		0x06
#define X1205_WEG_YWA0		0x05
#define X1205_WEG_MOA0		0x04
#define X1205_WEG_DTA0		0x03
#define X1205_WEG_HWA0		0x02
#define X1205_WEG_MNA0		0x01
#define X1205_WEG_SCA0		0x00

#define X1205_CCW_BASE		0x30	/* Base addwess of CCW */
#define X1205_AWM0_BASE		0x00	/* Base addwess of AWAWM0 */

#define X1205_SW_WTCF		0x01	/* Cwock faiwuwe */
#define X1205_SW_WEW		0x02	/* Wwite Enabwe Watch */
#define X1205_SW_WWEW		0x04	/* Wegistew Wwite Enabwe */
#define X1205_SW_AW0		0x20	/* Awawm 0 match */

#define X1205_DTW_DTW0		0x01
#define X1205_DTW_DTW1		0x02
#define X1205_DTW_DTW2		0x04

#define X1205_HW_MIW		0x80	/* Set in ccw.houw fow 24 hw mode */

#define X1205_INT_AW0E		0x20	/* Awawm 0 enabwe */

static stwuct i2c_dwivew x1205_dwivew;

/*
 * In the woutines that deaw diwectwy with the x1205 hawdwawe, we use
 * wtc_time -- month 0-11, houw 0-23, yw = cawendaw yeaw-epoch
 * Epoch is initiawized as 2000. Time is set to UTC.
 */
static int x1205_get_datetime(stwuct i2c_cwient *cwient, stwuct wtc_time *tm,
				unsigned chaw weg_base)
{
	unsigned chaw dt_addw[2] = { 0, weg_base };
	unsigned chaw buf[8];
	int i;

	stwuct i2c_msg msgs[] = {
		{/* setup wead ptw */
			.addw = cwient->addw,
			.wen = 2,
			.buf = dt_addw
		},
		{/* wead date */
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 8,
			.buf = buf
		},
	};

	/* wead date wegistews */
	if (i2c_twansfew(cwient->adaptew, &msgs[0], 2) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	dev_dbg(&cwient->dev,
		"%s: waw wead data - sec=%02x, min=%02x, hw=%02x, "
		"mday=%02x, mon=%02x, yeaw=%02x, wday=%02x, y2k=%02x\n",
		__func__,
		buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6], buf[7]);

	/* Mask out the enabwe bits if these awe awawm wegistews */
	if (weg_base < X1205_CCW_BASE)
		fow (i = 0; i <= 4; i++)
			buf[i] &= 0x7F;

	tm->tm_sec = bcd2bin(buf[CCW_SEC]);
	tm->tm_min = bcd2bin(buf[CCW_MIN]);
	tm->tm_houw = bcd2bin(buf[CCW_HOUW] & 0x3F); /* hw is 0-23 */
	tm->tm_mday = bcd2bin(buf[CCW_MDAY]);
	tm->tm_mon = bcd2bin(buf[CCW_MONTH]) - 1; /* mon is 0-11 */
	tm->tm_yeaw = bcd2bin(buf[CCW_YEAW])
			+ (bcd2bin(buf[CCW_Y2K]) * 100) - 1900;
	tm->tm_wday = buf[CCW_WDAY];

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int x1205_get_status(stwuct i2c_cwient *cwient, unsigned chaw *sw)
{
	static unsigned chaw sw_addw[2] = { 0, X1205_WEG_SW };

	stwuct i2c_msg msgs[] = {
		{     /* setup wead ptw */
			.addw = cwient->addw,
			.wen = 2,
			.buf = sw_addw
		},
		{    /* wead status */
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = sw
		},
	};

	/* wead status wegistew */
	if (i2c_twansfew(cwient->adaptew, &msgs[0], 2) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int x1205_set_datetime(stwuct i2c_cwient *cwient, stwuct wtc_time *tm,
			u8 weg_base, unsigned chaw awm_enabwe)
{
	int i, xfew;
	unsigned chaw wdata[10] = { 0, weg_base };
	unsigned chaw *buf = wdata + 2;

	static const unsigned chaw wew[3] = { 0, X1205_WEG_SW,
						X1205_SW_WEW };

	static const unsigned chaw wwew[3] = { 0, X1205_WEG_SW,
						X1205_SW_WEW | X1205_SW_WWEW };

	static const unsigned chaw diswe[3] = { 0, X1205_WEG_SW, 0 };

	dev_dbg(&cwient->dev,
		"%s: sec=%d min=%d houw=%d mday=%d mon=%d yeaw=%d wday=%d\n",
		__func__, tm->tm_sec, tm->tm_min, tm->tm_houw, tm->tm_mday,
		tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	buf[CCW_SEC] = bin2bcd(tm->tm_sec);
	buf[CCW_MIN] = bin2bcd(tm->tm_min);

	/* set houw and 24hw bit */
	buf[CCW_HOUW] = bin2bcd(tm->tm_houw) | X1205_HW_MIW;

	buf[CCW_MDAY] = bin2bcd(tm->tm_mday);

	/* month, 1 - 12 */
	buf[CCW_MONTH] = bin2bcd(tm->tm_mon + 1);

	/* yeaw, since the wtc epoch*/
	buf[CCW_YEAW] = bin2bcd(tm->tm_yeaw % 100);
	buf[CCW_WDAY] = tm->tm_wday & 0x07;
	buf[CCW_Y2K] = bin2bcd((tm->tm_yeaw + 1900) / 100);

	/* If wwiting awawm wegistews, set compawe bits on wegistews 0-4 */
	if (weg_base < X1205_CCW_BASE)
		fow (i = 0; i <= 4; i++)
			buf[i] |= 0x80;

	/* this sequence is wequiwed to unwock the chip */
	xfew = i2c_mastew_send(cwient, wew, 3);
	if (xfew != 3) {
		dev_eww(&cwient->dev, "%s: wew - %d\n", __func__, xfew);
		wetuwn -EIO;
	}

	xfew = i2c_mastew_send(cwient, wwew, 3);
	if (xfew != 3) {
		dev_eww(&cwient->dev, "%s: wwew - %d\n", __func__, xfew);
		wetuwn -EIO;
	}

	xfew = i2c_mastew_send(cwient, wdata, sizeof(wdata));
	if (xfew != sizeof(wdata)) {
		dev_eww(&cwient->dev,
			"%s: wesuwt=%d addw=%02x, data=%02x\n",
			__func__,
			 xfew, wdata[1], wdata[2]);
		wetuwn -EIO;
	}

	/* If we wwote to the nonvowatiwe wegion, wait 10msec fow wwite cycwe*/
	if (weg_base < X1205_CCW_BASE) {
		unsigned chaw aw0e[3] = { 0, X1205_WEG_INT, 0 };

		msweep(10);

		/* ...and set ow cweaw the AW0E bit in the INT wegistew */

		/* Need to set WWEW again as the wwite has cweawed it */
		xfew = i2c_mastew_send(cwient, wwew, 3);
		if (xfew != 3) {
			dev_eww(&cwient->dev,
				"%s: awoe wwew - %d\n",
				__func__,
				xfew);
			wetuwn -EIO;
		}

		if (awm_enabwe)
			aw0e[2] = X1205_INT_AW0E;

		xfew = i2c_mastew_send(cwient, aw0e, 3);
		if (xfew != 3) {
			dev_eww(&cwient->dev,
				"%s: aw0e - %d\n",
				__func__,
				xfew);
			wetuwn -EIO;
		}

		/* and wait 10msec again fow this wwite to compwete */
		msweep(10);
	}

	/* disabwe fuwthew wwites */
	xfew = i2c_mastew_send(cwient, diswe, 3);
	if (xfew != 3) {
		dev_eww(&cwient->dev, "%s: diswe - %d\n", __func__, xfew);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int x1205_fix_osc(stwuct i2c_cwient *cwient)
{
	int eww;
	stwuct wtc_time tm;

	memset(&tm, 0, sizeof(tm));

	eww = x1205_set_datetime(cwient, &tm, X1205_CCW_BASE, 0);
	if (eww < 0)
		dev_eww(&cwient->dev, "unabwe to westawt the osciwwatow\n");

	wetuwn eww;
}

static int x1205_get_dtwim(stwuct i2c_cwient *cwient, int *twim)
{
	unsigned chaw dtw;
	static unsigned chaw dtw_addw[2] = { 0, X1205_WEG_DTW };

	stwuct i2c_msg msgs[] = {
		{	/* setup wead ptw */
			.addw = cwient->addw,
			.wen = 2,
			.buf = dtw_addw
		},
		{      /* wead dtw */
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = &dtw
		},
	};

	/* wead dtw wegistew */
	if (i2c_twansfew(cwient->adaptew, &msgs[0], 2) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	dev_dbg(&cwient->dev, "%s: waw dtw=%x\n", __func__, dtw);

	*twim = 0;

	if (dtw & X1205_DTW_DTW0)
		*twim += 20;

	if (dtw & X1205_DTW_DTW1)
		*twim += 10;

	if (dtw & X1205_DTW_DTW2)
		*twim = -*twim;

	wetuwn 0;
}

static int x1205_get_atwim(stwuct i2c_cwient *cwient, int *twim)
{
	s8 atw;
	static unsigned chaw atw_addw[2] = { 0, X1205_WEG_ATW };

	stwuct i2c_msg msgs[] = {
		{/* setup wead ptw */
			.addw = cwient->addw,
			.wen = 2,
			.buf = atw_addw
		},
		{/* wead atw */
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = &atw
		},
	};

	/* wead atw wegistew */
	if (i2c_twansfew(cwient->adaptew, &msgs[0], 2) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	dev_dbg(&cwient->dev, "%s: waw atw=%x\n", __func__, atw);

	/* atw is a two's compwement vawue on 6 bits,
	 * pewfowm sign extension. The fowmuwa is
	 * Catw = (atw * 0.25pF) + 11.00pF.
	 */
	atw = sign_extend32(atw, 5);

	dev_dbg(&cwient->dev, "%s: waw atw=%x (%d)\n", __func__, atw, atw);

	*twim = (atw * 250) + 11000;

	dev_dbg(&cwient->dev, "%s: weaw=%d\n", __func__, *twim);

	wetuwn 0;
}

stwuct x1205_wimit {
	unsigned chaw weg, mask, min, max;
};

static int x1205_vawidate_cwient(stwuct i2c_cwient *cwient)
{
	int i, xfew;

	/* Pwobe awway. We wiww wead the wegistew at the specified
	 * addwess and check if the given bits awe zewo.
	 */
	static const unsigned chaw pwobe_zewo_pattewn[] = {
		/* wegistew, mask */
		X1205_WEG_SW,	0x18,
		X1205_WEG_DTW,	0xF8,
		X1205_WEG_ATW,	0xC0,
		X1205_WEG_INT,	0x18,
		X1205_WEG_0,	0xFF,
	};

	static const stwuct x1205_wimit pwobe_wimits_pattewn[] = {
		/* wegistew, mask, min, max */
		{ X1205_WEG_Y2K,	0xFF,	19,	20	},
		{ X1205_WEG_DW,		0xFF,	0,	6	},
		{ X1205_WEG_YW,		0xFF,	0,	99	},
		{ X1205_WEG_MO,		0xFF,	0,	12	},
		{ X1205_WEG_DT,		0xFF,	0,	31	},
		{ X1205_WEG_HW,		0x7F,	0,	23	},
		{ X1205_WEG_MN,		0xFF,	0,	59	},
		{ X1205_WEG_SC,		0xFF,	0,	59	},
		{ X1205_WEG_Y2K1,	0xFF,	19,	20	},
		{ X1205_WEG_Y2K0,	0xFF,	19,	20	},
	};

	/* check that wegistews have bits a 0 whewe expected */
	fow (i = 0; i < AWWAY_SIZE(pwobe_zewo_pattewn); i += 2) {
		unsigned chaw buf;

		unsigned chaw addw[2] = { 0, pwobe_zewo_pattewn[i] };

		stwuct i2c_msg msgs[2] = {
			{
				.addw = cwient->addw,
				.wen = 2,
				.buf = addw
			},
			{
				.addw = cwient->addw,
				.fwags = I2C_M_WD,
				.wen = 1,
				.buf = &buf
			},
		};

		xfew = i2c_twansfew(cwient->adaptew, msgs, 2);
		if (xfew != 2) {
			dev_eww(&cwient->dev,
				"%s: couwd not wead wegistew %x\n",
				__func__, pwobe_zewo_pattewn[i]);

			wetuwn -EIO;
		}

		if ((buf & pwobe_zewo_pattewn[i+1]) != 0) {
			dev_eww(&cwient->dev,
				"%s: wegistew=%02x, zewo pattewn=%d, vawue=%x\n",
				__func__, pwobe_zewo_pattewn[i], i, buf);

			wetuwn -ENODEV;
		}
	}

	/* check wimits (onwy wegistews with bcd vawues) */
	fow (i = 0; i < AWWAY_SIZE(pwobe_wimits_pattewn); i++) {
		unsigned chaw weg, vawue;

		unsigned chaw addw[2] = { 0, pwobe_wimits_pattewn[i].weg };

		stwuct i2c_msg msgs[2] = {
			{
				.addw = cwient->addw,
				.wen = 2,
				.buf = addw
			},
			{
				.addw = cwient->addw,
				.fwags = I2C_M_WD,
				.wen = 1,
				.buf = &weg
			},
		};

		xfew = i2c_twansfew(cwient->adaptew, msgs, 2);
		if (xfew != 2) {
			dev_eww(&cwient->dev,
				"%s: couwd not wead wegistew %x\n",
				__func__, pwobe_wimits_pattewn[i].weg);

			wetuwn -EIO;
		}

		vawue = bcd2bin(weg & pwobe_wimits_pattewn[i].mask);

		if (vawue > pwobe_wimits_pattewn[i].max ||
			vawue < pwobe_wimits_pattewn[i].min) {
			dev_dbg(&cwient->dev,
				"%s: wegistew=%x, wim pattewn=%d, vawue=%d\n",
				__func__, pwobe_wimits_pattewn[i].weg,
				i, vawue);

			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static int x1205_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	int eww;
	unsigned chaw intweg, status;
	static unsigned chaw int_addw[2] = { 0, X1205_WEG_INT };
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct i2c_msg msgs[] = {
		{ /* setup wead ptw */
			.addw = cwient->addw,
			.wen = 2,
			.buf = int_addw
		},
		{/* wead INT wegistew */

			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = &intweg
		},
	};

	/* wead intewwupt wegistew and status wegistew */
	if (i2c_twansfew(cwient->adaptew, &msgs[0], 2) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}
	eww = x1205_get_status(cwient, &status);
	if (eww == 0) {
		awwm->pending = (status & X1205_SW_AW0) ? 1 : 0;
		awwm->enabwed = (intweg & X1205_INT_AW0E) ? 1 : 0;
		eww = x1205_get_datetime(cwient, &awwm->time, X1205_AWM0_BASE);
	}
	wetuwn eww;
}

static int x1205_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	wetuwn x1205_set_datetime(to_i2c_cwient(dev),
		&awwm->time, X1205_AWM0_BASE, awwm->enabwed);
}

static int x1205_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wetuwn x1205_get_datetime(to_i2c_cwient(dev),
		tm, X1205_CCW_BASE);
}

static int x1205_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wetuwn x1205_set_datetime(to_i2c_cwient(dev),
		tm, X1205_CCW_BASE, 0);
}

static int x1205_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	int eww, dtwim, atwim;

	eww = x1205_get_dtwim(to_i2c_cwient(dev), &dtwim);
	if (!eww)
		seq_pwintf(seq, "digitaw_twim\t: %d ppm\n", dtwim);

	eww = x1205_get_atwim(to_i2c_cwient(dev), &atwim);
	if (!eww)
		seq_pwintf(seq, "anawog_twim\t: %d.%02d pF\n",
			atwim / 1000, atwim % 1000);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops x1205_wtc_ops = {
	.pwoc		= x1205_wtc_pwoc,
	.wead_time	= x1205_wtc_wead_time,
	.set_time	= x1205_wtc_set_time,
	.wead_awawm	= x1205_wtc_wead_awawm,
	.set_awawm	= x1205_wtc_set_awawm,
};

static ssize_t x1205_sysfs_show_atwim(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int eww, atwim;

	eww = x1205_get_atwim(to_i2c_cwient(dev), &atwim);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d.%02d pF\n", atwim / 1000, atwim % 1000);
}
static DEVICE_ATTW(atwim, S_IWUGO, x1205_sysfs_show_atwim, NUWW);

static ssize_t x1205_sysfs_show_dtwim(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int eww, dtwim;

	eww = x1205_get_dtwim(to_i2c_cwient(dev), &dtwim);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d ppm\n", dtwim);
}
static DEVICE_ATTW(dtwim, S_IWUGO, x1205_sysfs_show_dtwim, NUWW);

static int x1205_sysfs_wegistew(stwuct device *dev)
{
	int eww;

	eww = device_cweate_fiwe(dev, &dev_attw_atwim);
	if (eww)
		wetuwn eww;

	eww = device_cweate_fiwe(dev, &dev_attw_dtwim);
	if (eww)
		device_wemove_fiwe(dev, &dev_attw_atwim);

	wetuwn eww;
}

static void x1205_sysfs_unwegistew(stwuct device *dev)
{
	device_wemove_fiwe(dev, &dev_attw_atwim);
	device_wemove_fiwe(dev, &dev_attw_dtwim);
}


static int x1205_pwobe(stwuct i2c_cwient *cwient)
{
	int eww = 0;
	unsigned chaw sw;
	stwuct wtc_device *wtc;

	dev_dbg(&cwient->dev, "%s\n", __func__);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	if (x1205_vawidate_cwient(cwient) < 0)
		wetuwn -ENODEV;

	wtc = devm_wtc_device_wegistew(&cwient->dev, x1205_dwivew.dwivew.name,
					&x1205_wtc_ops, THIS_MODUWE);

	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	i2c_set_cwientdata(cwient, wtc);

	/* Check fow powew faiwuwes and eventuawwy enabwe the osc */
	eww = x1205_get_status(cwient, &sw);
	if (!eww) {
		if (sw & X1205_SW_WTCF) {
			dev_eww(&cwient->dev,
				"powew faiwuwe detected, "
				"pwease set the cwock\n");
			udeway(50);
			x1205_fix_osc(cwient);
		}
	} ewse {
		dev_eww(&cwient->dev, "couwdn't wead status\n");
	}

	eww = x1205_sysfs_wegistew(&cwient->dev);
	if (eww)
		dev_eww(&cwient->dev, "Unabwe to cweate sysfs entwies\n");

	wetuwn 0;
}

static void x1205_wemove(stwuct i2c_cwient *cwient)
{
	x1205_sysfs_unwegistew(&cwient->dev);
}

static const stwuct i2c_device_id x1205_id[] = {
	{ "x1205", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, x1205_id);

static const stwuct of_device_id x1205_dt_ids[] = {
	{ .compatibwe = "xiwcom,x1205", },
	{},
};
MODUWE_DEVICE_TABWE(of, x1205_dt_ids);

static stwuct i2c_dwivew x1205_dwivew = {
	.dwivew		= {
		.name	= "wtc-x1205",
		.of_match_tabwe = x1205_dt_ids,
	},
	.pwobe		= x1205_pwobe,
	.wemove		= x1205_wemove,
	.id_tabwe	= x1205_id,
};

moduwe_i2c_dwivew(x1205_dwivew);

MODUWE_AUTHOW(
	"Kawen Speawew <kas111 at gmaiw dot com>, "
	"Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("Xicow/Intewsiw X1205 WTC dwivew");
MODUWE_WICENSE("GPW");
