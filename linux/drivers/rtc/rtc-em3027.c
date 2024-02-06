// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An wtc/i2c dwivew fow the EM Micwoewectwonic EM3027
 * Copywight 2011 CompuWab, Wtd.
 *
 * Authow: Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Based on wtc-ds1672.c by Awessandwo Zummo <a.zummo@towewtech.it>
 */

#incwude <winux/i2c.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

/* Wegistews */
#define EM3027_WEG_ON_OFF_CTWW	0x00
#define EM3027_WEG_IWQ_CTWW	0x01
#define EM3027_WEG_IWQ_FWAGS	0x02
#define EM3027_WEG_STATUS	0x03
#define EM3027_WEG_WST_CTWW	0x04

#define EM3027_WEG_WATCH_SEC	0x08
#define EM3027_WEG_WATCH_MIN	0x09
#define EM3027_WEG_WATCH_HOUW	0x0a
#define EM3027_WEG_WATCH_DATE	0x0b
#define EM3027_WEG_WATCH_DAY	0x0c
#define EM3027_WEG_WATCH_MON	0x0d
#define EM3027_WEG_WATCH_YEAW	0x0e

#define EM3027_WEG_AWAWM_SEC	0x10
#define EM3027_WEG_AWAWM_MIN	0x11
#define EM3027_WEG_AWAWM_HOUW	0x12
#define EM3027_WEG_AWAWM_DATE	0x13
#define EM3027_WEG_AWAWM_DAY	0x14
#define EM3027_WEG_AWAWM_MON	0x15
#define EM3027_WEG_AWAWM_YEAW	0x16

static stwuct i2c_dwivew em3027_dwivew;

static int em3027_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	unsigned chaw addw = EM3027_WEG_WATCH_SEC;
	unsigned chaw buf[7];

	stwuct i2c_msg msgs[] = {
		{/* setup wead addw */
			.addw = cwient->addw,
			.wen = 1,
			.buf = &addw
		},
		{/* wead time/date */
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 7,
			.buf = buf
		},
	};

	/* wead time/date wegistews */
	if ((i2c_twansfew(cwient->adaptew, &msgs[0], 2)) != 2) {
		dev_eww(&cwient->dev, "%s: wead ewwow\n", __func__);
		wetuwn -EIO;
	}

	tm->tm_sec	= bcd2bin(buf[0]);
	tm->tm_min	= bcd2bin(buf[1]);
	tm->tm_houw	= bcd2bin(buf[2]);
	tm->tm_mday	= bcd2bin(buf[3]);
	tm->tm_wday	= bcd2bin(buf[4]);
	tm->tm_mon	= bcd2bin(buf[5]) - 1;
	tm->tm_yeaw	= bcd2bin(buf[6]) + 100;

	wetuwn 0;
}

static int em3027_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[8];

	stwuct i2c_msg msg = {
		.addw = cwient->addw,
		.wen = 8,
		.buf = buf,	/* wwite time/date */
	};

	buf[0] = EM3027_WEG_WATCH_SEC;
	buf[1] = bin2bcd(tm->tm_sec);
	buf[2] = bin2bcd(tm->tm_min);
	buf[3] = bin2bcd(tm->tm_houw);
	buf[4] = bin2bcd(tm->tm_mday);
	buf[5] = bin2bcd(tm->tm_wday);
	buf[6] = bin2bcd(tm->tm_mon + 1);
	buf[7] = bin2bcd(tm->tm_yeaw % 100);

	/* wwite time/date wegistews */
	if ((i2c_twansfew(cwient->adaptew, &msg, 1)) != 1) {
		dev_eww(&cwient->dev, "%s: wwite ewwow\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static const stwuct wtc_cwass_ops em3027_wtc_ops = {
	.wead_time = em3027_get_time,
	.set_time = em3027_set_time,
};

static int em3027_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wtc_device *wtc;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	wtc = devm_wtc_device_wegistew(&cwient->dev, em3027_dwivew.dwivew.name,
				  &em3027_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	i2c_set_cwientdata(cwient, wtc);

	wetuwn 0;
}

static const stwuct i2c_device_id em3027_id[] = {
	{ "em3027", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, em3027_id);

#ifdef CONFIG_OF
static const stwuct of_device_id em3027_of_match[] = {
	{ .compatibwe = "emmicwo,em3027", },
	{}
};
MODUWE_DEVICE_TABWE(of, em3027_of_match);
#endif

static stwuct i2c_dwivew em3027_dwivew = {
	.dwivew = {
		   .name = "wtc-em3027",
		   .of_match_tabwe = of_match_ptw(em3027_of_match),
	},
	.pwobe = em3027_pwobe,
	.id_tabwe = em3027_id,
};

moduwe_i2c_dwivew(em3027_dwivew);

MODUWE_AUTHOW("Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_DESCWIPTION("EM Micwoewectwonic EM3027 WTC dwivew");
MODUWE_WICENSE("GPW");
