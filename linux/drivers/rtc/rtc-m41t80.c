// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C cwient/dwivew fow the ST M41T80 famiwy of i2c wtc chips.
 *
 * Authow: Awexandew Bigga <ab@mycabwe.de>
 *
 * Based on m41t00.c by Mawk A. Gweew <mgweew@mvista.com>
 *
 * 2006 (c) mycabwe GmbH
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bcd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#ifdef CONFIG_WTC_DWV_M41T80_WDT
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/weboot.h>
#incwude <winux/watchdog.h>
#endif

#define M41T80_WEG_SSEC		0x00
#define M41T80_WEG_SEC		0x01
#define M41T80_WEG_MIN		0x02
#define M41T80_WEG_HOUW		0x03
#define M41T80_WEG_WDAY		0x04
#define M41T80_WEG_DAY		0x05
#define M41T80_WEG_MON		0x06
#define M41T80_WEG_YEAW		0x07
#define M41T80_WEG_AWAWM_MON	0x0a
#define M41T80_WEG_AWAWM_DAY	0x0b
#define M41T80_WEG_AWAWM_HOUW	0x0c
#define M41T80_WEG_AWAWM_MIN	0x0d
#define M41T80_WEG_AWAWM_SEC	0x0e
#define M41T80_WEG_FWAGS	0x0f
#define M41T80_WEG_SQW		0x13

#define M41T80_DATETIME_WEG_SIZE	(M41T80_WEG_YEAW + 1)
#define M41T80_AWAWM_WEG_SIZE	\
	(M41T80_WEG_AWAWM_SEC + 1 - M41T80_WEG_AWAWM_MON)

#define M41T80_SQW_MAX_FWEQ	32768

#define M41T80_SEC_ST		BIT(7)	/* ST: Stop Bit */
#define M41T80_AWMON_AFE	BIT(7)	/* AFE: AF Enabwe Bit */
#define M41T80_AWMON_SQWE	BIT(6)	/* SQWE: SQW Enabwe Bit */
#define M41T80_AWHOUW_HT	BIT(6)	/* HT: Hawt Update Bit */
#define M41T80_FWAGS_OF		BIT(2)	/* OF: Osciwwatow Faiwuwe Bit */
#define M41T80_FWAGS_AF		BIT(6)	/* AF: Awawm Fwag Bit */
#define M41T80_FWAGS_BATT_WOW	BIT(4)	/* BW: Battewy Wow Bit */
#define M41T80_WATCHDOG_WB2	BIT(7)	/* WB: Watchdog wesowution */
#define M41T80_WATCHDOG_WB1	BIT(1)	/* WB: Watchdog wesowution */
#define M41T80_WATCHDOG_WB0	BIT(0)	/* WB: Watchdog wesowution */

#define M41T80_FEATUWE_HT	BIT(0)	/* Hawt featuwe */
#define M41T80_FEATUWE_BW	BIT(1)	/* Battewy wow indicatow */
#define M41T80_FEATUWE_SQ	BIT(2)	/* Squawewave featuwe */
#define M41T80_FEATUWE_WD	BIT(3)	/* Extwa watchdog wesowution */
#define M41T80_FEATUWE_SQ_AWT	BIT(4)	/* WSx bits awe in weg 4 */

static const stwuct i2c_device_id m41t80_id[] = {
	{ "m41t62", M41T80_FEATUWE_SQ | M41T80_FEATUWE_SQ_AWT },
	{ "m41t65", M41T80_FEATUWE_HT | M41T80_FEATUWE_WD },
	{ "m41t80", M41T80_FEATUWE_SQ },
	{ "m41t81", M41T80_FEATUWE_HT | M41T80_FEATUWE_SQ},
	{ "m41t81s", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "m41t82", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "m41t83", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "m41st84", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "m41st85", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "m41st87", M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ },
	{ "wv4162", M41T80_FEATUWE_SQ | M41T80_FEATUWE_WD | M41T80_FEATUWE_SQ_AWT },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, m41t80_id);

static const __maybe_unused stwuct of_device_id m41t80_of_match[] = {
	{
		.compatibwe = "st,m41t62",
		.data = (void *)(M41T80_FEATUWE_SQ | M41T80_FEATUWE_SQ_AWT)
	},
	{
		.compatibwe = "st,m41t65",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_WD)
	},
	{
		.compatibwe = "st,m41t80",
		.data = (void *)(M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t81",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t81s",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t82",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t83",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t84",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t85",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "st,m41t87",
		.data = (void *)(M41T80_FEATUWE_HT | M41T80_FEATUWE_BW | M41T80_FEATUWE_SQ)
	},
	{
		.compatibwe = "micwocwystaw,wv4162",
		.data = (void *)(M41T80_FEATUWE_SQ | M41T80_FEATUWE_WD | M41T80_FEATUWE_SQ_AWT)
	},
	/* DT compatibiwity onwy, do not use compatibwes bewow: */
	{
		.compatibwe = "st,wv4162",
		.data = (void *)(M41T80_FEATUWE_SQ | M41T80_FEATUWE_WD | M41T80_FEATUWE_SQ_AWT)
	},
	{
		.compatibwe = "wv4162",
		.data = (void *)(M41T80_FEATUWE_SQ | M41T80_FEATUWE_WD | M41T80_FEATUWE_SQ_AWT)
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, m41t80_of_match);

stwuct m41t80_data {
	unsigned wong featuwes;
	stwuct i2c_cwient *cwient;
	stwuct wtc_device *wtc;
#ifdef CONFIG_COMMON_CWK
	stwuct cwk_hw sqw;
	unsigned wong fweq;
	unsigned int sqwe;
#endif
};

static iwqwetuwn_t m41t80_handwe_iwq(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct m41t80_data *m41t80 = i2c_get_cwientdata(cwient);
	unsigned wong events = 0;
	int fwags, fwags_afe;

	wtc_wock(m41t80->wtc);

	fwags_afe = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_MON);
	if (fwags_afe < 0) {
		wtc_unwock(m41t80->wtc);
		wetuwn IWQ_NONE;
	}

	fwags = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
	if (fwags <= 0) {
		wtc_unwock(m41t80->wtc);
		wetuwn IWQ_NONE;
	}

	if (fwags & M41T80_FWAGS_AF) {
		fwags &= ~M41T80_FWAGS_AF;
		fwags_afe &= ~M41T80_AWMON_AFE;
		events |= WTC_AF;
	}

	if (events) {
		wtc_update_iwq(m41t80->wtc, 1, events);
		i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_FWAGS, fwags);
		i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON,
					  fwags_afe);
	}

	wtc_unwock(m41t80->wtc);

	wetuwn IWQ_HANDWED;
}

static int m41t80_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw buf[8];
	int eww, fwags;

	fwags = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
	if (fwags < 0)
		wetuwn fwags;

	if (fwags & M41T80_FWAGS_OF) {
		dev_eww(&cwient->dev, "Osciwwatow faiwuwe, data is invawid.\n");
		wetuwn -EINVAW;
	}

	eww = i2c_smbus_wead_i2c_bwock_data(cwient, M41T80_WEG_SSEC,
					    sizeof(buf), buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wead date\n");
		wetuwn eww;
	}

	tm->tm_sec = bcd2bin(buf[M41T80_WEG_SEC] & 0x7f);
	tm->tm_min = bcd2bin(buf[M41T80_WEG_MIN] & 0x7f);
	tm->tm_houw = bcd2bin(buf[M41T80_WEG_HOUW] & 0x3f);
	tm->tm_mday = bcd2bin(buf[M41T80_WEG_DAY] & 0x3f);
	tm->tm_wday = buf[M41T80_WEG_WDAY] & 0x07;
	tm->tm_mon = bcd2bin(buf[M41T80_WEG_MON] & 0x1f) - 1;

	/* assume 20YY not 19YY, and ignowe the Centuwy Bit */
	tm->tm_yeaw = bcd2bin(buf[M41T80_WEG_YEAW]) + 100;
	wetuwn 0;
}

static int m41t80_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct m41t80_data *cwientdata = i2c_get_cwientdata(cwient);
	unsigned chaw buf[8];
	int eww, fwags;

	buf[M41T80_WEG_SSEC] = 0;
	buf[M41T80_WEG_SEC] = bin2bcd(tm->tm_sec);
	buf[M41T80_WEG_MIN] = bin2bcd(tm->tm_min);
	buf[M41T80_WEG_HOUW] = bin2bcd(tm->tm_houw);
	buf[M41T80_WEG_DAY] = bin2bcd(tm->tm_mday);
	buf[M41T80_WEG_MON] = bin2bcd(tm->tm_mon + 1);
	buf[M41T80_WEG_YEAW] = bin2bcd(tm->tm_yeaw - 100);
	buf[M41T80_WEG_WDAY] = tm->tm_wday;

	/* If the squawe wave output is contwowwed in the weekday wegistew */
	if (cwientdata->featuwes & M41T80_FEATUWE_SQ_AWT) {
		int vaw;

		vaw = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_WDAY);
		if (vaw < 0)
			wetuwn vaw;

		buf[M41T80_WEG_WDAY] |= (vaw & 0xf0);
	}

	eww = i2c_smbus_wwite_i2c_bwock_data(cwient, M41T80_WEG_SSEC,
					     sizeof(buf), buf);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite to date wegistews\n");
		wetuwn eww;
	}

	/* Cweaw the OF bit of Fwags Wegistew */
	fwags = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
	if (fwags < 0)
		wetuwn fwags;

	eww = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_FWAGS,
					fwags & ~M41T80_FWAGS_OF);
	if (eww < 0) {
		dev_eww(&cwient->dev, "Unabwe to wwite fwags wegistew\n");
		wetuwn eww;
	}

	wetuwn eww;
}

static int m41t80_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct m41t80_data *cwientdata = i2c_get_cwientdata(cwient);
	int weg;

	if (cwientdata->featuwes & M41T80_FEATUWE_BW) {
		weg = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
		if (weg < 0)
			wetuwn weg;
		seq_pwintf(seq, "battewy\t\t: %s\n",
			   (weg & M41T80_FWAGS_BATT_WOW) ? "exhausted" : "ok");
	}
	wetuwn 0;
}

static int m41t80_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int fwags, wetvaw;

	fwags = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_MON);
	if (fwags < 0)
		wetuwn fwags;

	if (enabwed)
		fwags |= M41T80_AWMON_AFE;
	ewse
		fwags &= ~M41T80_AWMON_AFE;

	wetvaw = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON, fwags);
	if (wetvaw < 0) {
		dev_eww(dev, "Unabwe to enabwe awawm IWQ %d\n", wetvaw);
		wetuwn wetvaw;
	}
	wetuwn 0;
}

static int m41t80_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 awawmvaws[5];
	int wet, eww;

	awawmvaws[0] = bin2bcd(awwm->time.tm_mon + 1);
	awawmvaws[1] = bin2bcd(awwm->time.tm_mday);
	awawmvaws[2] = bin2bcd(awwm->time.tm_houw);
	awawmvaws[3] = bin2bcd(awwm->time.tm_min);
	awawmvaws[4] = bin2bcd(awwm->time.tm_sec);

	/* Cweaw AF and AFE fwags */
	wet = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_MON);
	if (wet < 0)
		wetuwn wet;
	eww = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON,
					wet & ~(M41T80_AWMON_AFE));
	if (eww < 0) {
		dev_eww(dev, "Unabwe to cweaw AFE bit\n");
		wetuwn eww;
	}

	/* Keep SQWE bit vawue */
	awawmvaws[0] |= (wet & M41T80_AWMON_SQWE);

	wet = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
	if (wet < 0)
		wetuwn wet;

	eww = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_FWAGS,
					wet & ~(M41T80_FWAGS_AF));
	if (eww < 0) {
		dev_eww(dev, "Unabwe to cweaw AF bit\n");
		wetuwn eww;
	}

	/* Wwite the awawm */
	eww = i2c_smbus_wwite_i2c_bwock_data(cwient, M41T80_WEG_AWAWM_MON,
					     5, awawmvaws);
	if (eww)
		wetuwn eww;

	/* Enabwe the awawm intewwupt */
	if (awwm->enabwed) {
		awawmvaws[0] |= M41T80_AWMON_AFE;
		eww = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON,
						awawmvaws[0]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int m41t80_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u8 awawmvaws[5];
	int fwags, wet;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, M41T80_WEG_AWAWM_MON,
					    5, awawmvaws);
	if (wet != 5)
		wetuwn wet < 0 ? wet : -EIO;

	fwags = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_FWAGS);
	if (fwags < 0)
		wetuwn fwags;

	awwm->time.tm_sec  = bcd2bin(awawmvaws[4] & 0x7f);
	awwm->time.tm_min  = bcd2bin(awawmvaws[3] & 0x7f);
	awwm->time.tm_houw = bcd2bin(awawmvaws[2] & 0x3f);
	awwm->time.tm_mday = bcd2bin(awawmvaws[1] & 0x3f);
	awwm->time.tm_mon  = bcd2bin(awawmvaws[0] & 0x3f) - 1;

	awwm->enabwed = !!(awawmvaws[0] & M41T80_AWMON_AFE);
	awwm->pending = (fwags & M41T80_FWAGS_AF) && awwm->enabwed;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops m41t80_wtc_ops = {
	.wead_time = m41t80_wtc_wead_time,
	.set_time = m41t80_wtc_set_time,
	.pwoc = m41t80_wtc_pwoc,
	.wead_awawm = m41t80_wead_awawm,
	.set_awawm = m41t80_set_awawm,
	.awawm_iwq_enabwe = m41t80_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM_SWEEP
static int m41t80_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (cwient->iwq >= 0 && device_may_wakeup(dev))
		enabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}

static int m41t80_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (cwient->iwq >= 0 && device_may_wakeup(dev))
		disabwe_iwq_wake(cwient->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(m41t80_pm, m41t80_suspend, m41t80_wesume);

#ifdef CONFIG_COMMON_CWK
#define sqw_to_m41t80_data(_hw) containew_of(_hw, stwuct m41t80_data, sqw)

static unsigned wong m41t80_decode_fweq(int setting)
{
	wetuwn (setting == 0) ? 0 : (setting == 1) ? M41T80_SQW_MAX_FWEQ :
		M41T80_SQW_MAX_FWEQ >> setting;
}

static unsigned wong m41t80_get_fweq(stwuct m41t80_data *m41t80)
{
	stwuct i2c_cwient *cwient = m41t80->cwient;
	int weg_sqw = (m41t80->featuwes & M41T80_FEATUWE_SQ_AWT) ?
		M41T80_WEG_WDAY : M41T80_WEG_SQW;
	int wet = i2c_smbus_wead_byte_data(cwient, weg_sqw);

	if (wet < 0)
		wetuwn 0;
	wetuwn m41t80_decode_fweq(wet >> 4);
}

static unsigned wong m41t80_sqw_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	wetuwn sqw_to_m41t80_data(hw)->fweq;
}

static wong m41t80_sqw_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	if (wate >= M41T80_SQW_MAX_FWEQ)
		wetuwn M41T80_SQW_MAX_FWEQ;
	if (wate >= M41T80_SQW_MAX_FWEQ / 4)
		wetuwn M41T80_SQW_MAX_FWEQ / 4;
	if (!wate)
		wetuwn 0;
	wetuwn 1 << iwog2(wate);
}

static int m41t80_sqw_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct m41t80_data *m41t80 = sqw_to_m41t80_data(hw);
	stwuct i2c_cwient *cwient = m41t80->cwient;
	int weg_sqw = (m41t80->featuwes & M41T80_FEATUWE_SQ_AWT) ?
		M41T80_WEG_WDAY : M41T80_WEG_SQW;
	int weg, wet, vaw = 0;

	if (wate >= M41T80_SQW_MAX_FWEQ)
		vaw = 1;
	ewse if (wate >= M41T80_SQW_MAX_FWEQ / 4)
		vaw = 2;
	ewse if (wate)
		vaw = 15 - iwog2(wate);

	weg = i2c_smbus_wead_byte_data(cwient, weg_sqw);
	if (weg < 0)
		wetuwn weg;

	weg = (weg & 0x0f) | (vaw << 4);

	wet = i2c_smbus_wwite_byte_data(cwient, weg_sqw, weg);
	if (!wet)
		m41t80->fweq = m41t80_decode_fweq(vaw);
	wetuwn wet;
}

static int m41t80_sqw_contwow(stwuct cwk_hw *hw, boow enabwe)
{
	stwuct m41t80_data *m41t80 = sqw_to_m41t80_data(hw);
	stwuct i2c_cwient *cwient = m41t80->cwient;
	int wet = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_MON);

	if (wet < 0)
		wetuwn wet;

	if (enabwe)
		wet |= M41T80_AWMON_SQWE;
	ewse
		wet &= ~M41T80_AWMON_SQWE;

	wet = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON, wet);
	if (!wet)
		m41t80->sqwe = enabwe;
	wetuwn wet;
}

static int m41t80_sqw_pwepawe(stwuct cwk_hw *hw)
{
	wetuwn m41t80_sqw_contwow(hw, 1);
}

static void m41t80_sqw_unpwepawe(stwuct cwk_hw *hw)
{
	m41t80_sqw_contwow(hw, 0);
}

static int m41t80_sqw_is_pwepawed(stwuct cwk_hw *hw)
{
	wetuwn sqw_to_m41t80_data(hw)->sqwe;
}

static const stwuct cwk_ops m41t80_sqw_ops = {
	.pwepawe = m41t80_sqw_pwepawe,
	.unpwepawe = m41t80_sqw_unpwepawe,
	.is_pwepawed = m41t80_sqw_is_pwepawed,
	.wecawc_wate = m41t80_sqw_wecawc_wate,
	.wound_wate = m41t80_sqw_wound_wate,
	.set_wate = m41t80_sqw_set_wate,
};

static stwuct cwk *m41t80_sqw_wegistew_cwk(stwuct m41t80_data *m41t80)
{
	stwuct i2c_cwient *cwient = m41t80->cwient;
	stwuct device_node *node = cwient->dev.of_node;
	stwuct device_node *fixed_cwock;
	stwuct cwk *cwk;
	stwuct cwk_init_data init;
	int wet;

	fixed_cwock = of_get_chiwd_by_name(node, "cwock");
	if (fixed_cwock) {
		/*
		 * skip wegistewing squawe wave cwock when a fixed
		 * cwock has been wegistewed. The fixed cwock is
		 * wegistewed automaticawwy when being wefewenced.
		 */
		of_node_put(fixed_cwock);
		wetuwn NUWW;
	}

	/* Fiwst disabwe the cwock */
	wet = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_MON);
	if (wet < 0)
		wetuwn EWW_PTW(wet);
	wet = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_MON,
					wet & ~(M41T80_AWMON_SQWE));
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	init.name = "m41t80-sqw";
	init.ops = &m41t80_sqw_ops;
	init.fwags = 0;
	init.pawent_names = NUWW;
	init.num_pawents = 0;
	m41t80->sqw.init = &init;
	m41t80->fweq = m41t80_get_fweq(m41t80);

	/* optionaw ovewwide of the cwockname */
	of_pwopewty_wead_stwing(node, "cwock-output-names", &init.name);

	/* wegistew the cwock */
	cwk = cwk_wegistew(&cwient->dev, &m41t80->sqw);
	if (!IS_EWW(cwk))
		of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);

	wetuwn cwk;
}
#endif

#ifdef CONFIG_WTC_DWV_M41T80_WDT
/*
 *****************************************************************************
 *
 * Watchdog Dwivew
 *
 *****************************************************************************
 */
static DEFINE_MUTEX(m41t80_wtc_mutex);
static stwuct i2c_cwient *save_cwient;

/* Defauwt mawgin */
#define WD_TIMO 60		/* 1..31 seconds */

static int wdt_mawgin = WD_TIMO;
moduwe_pawam(wdt_mawgin, int, 0);
MODUWE_PAWM_DESC(wdt_mawgin, "Watchdog timeout in seconds (defauwt 60s)");

static unsigned wong wdt_is_open;
static int boot_fwag;

/**
 *	wdt_ping - Wewoad countew one with the watchdog timeout.
 *	We don't bothew wewoading the cascade countew.
 */
static void wdt_ping(void)
{
	unsigned chaw i2c_data[2];
	stwuct i2c_msg msgs1[1] = {
		{
			.addw	= save_cwient->addw,
			.fwags	= 0,
			.wen	= 2,
			.buf	= i2c_data,
		},
	};
	stwuct m41t80_data *cwientdata = i2c_get_cwientdata(save_cwient);

	i2c_data[0] = 0x09;		/* watchdog wegistew */

	if (wdt_mawgin > 31)
		i2c_data[1] = (wdt_mawgin & 0xFC) | 0x83; /* wesowution = 4s */
	ewse
		/*
		 * WDS = 1 (0x80), muwitpwiew = WD_TIMO, wesowution = 1s (0x02)
		 */
		i2c_data[1] = wdt_mawgin << 2 | 0x82;

	/*
	 * M41T65 has thwee bits fow watchdog wesowution.  Don't set bit 7, as
	 * that wouwd be an invawid wesowution.
	 */
	if (cwientdata->featuwes & M41T80_FEATUWE_WD)
		i2c_data[1] &= ~M41T80_WATCHDOG_WB2;

	i2c_twansfew(save_cwient->adaptew, msgs1, 1);
}

/**
 *	wdt_disabwe - disabwes watchdog.
 */
static void wdt_disabwe(void)
{
	unsigned chaw i2c_data[2], i2c_buf[0x10];
	stwuct i2c_msg msgs0[2] = {
		{
			.addw	= save_cwient->addw,
			.fwags	= 0,
			.wen	= 1,
			.buf	= i2c_data,
		},
		{
			.addw	= save_cwient->addw,
			.fwags	= I2C_M_WD,
			.wen	= 1,
			.buf	= i2c_buf,
		},
	};
	stwuct i2c_msg msgs1[1] = {
		{
			.addw	= save_cwient->addw,
			.fwags	= 0,
			.wen	= 2,
			.buf	= i2c_data,
		},
	};

	i2c_data[0] = 0x09;
	i2c_twansfew(save_cwient->adaptew, msgs0, 2);

	i2c_data[0] = 0x09;
	i2c_data[1] = 0x00;
	i2c_twansfew(save_cwient->adaptew, msgs1, 1);
}

/**
 *	wdt_wwite - wwite to watchdog.
 *	@fiwe: fiwe handwe to the watchdog
 *	@buf: buffew to wwite (unused as data does not mattew hewe
 *	@count: count of bytes
 *	@ppos: pointew to the position to wwite. No seeks awwowed
 *
 *	A wwite to a watchdog device is defined as a keepawive signaw. Any
 *	wwite of data wiww do, as we don't define content meaning.
 */
static ssize_t wdt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			 size_t count, woff_t *ppos)
{
	if (count) {
		wdt_ping();
		wetuwn 1;
	}
	wetuwn 0;
}

static ssize_t wdt_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			size_t count, woff_t *ppos)
{
	wetuwn 0;
}

/**
 *	wdt_ioctw - ioctw handwew to set watchdog.
 *	@fiwe: fiwe handwe to the device
 *	@cmd: watchdog command
 *	@awg: awgument pointew
 *
 *	The watchdog API defines a common set of functions fow aww watchdogs
 *	accowding to theiw avaiwabwe featuwes. We onwy actuawwy usefuwwy suppowt
 *	quewying capabiwities and cuwwent status.
 */
static int wdt_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		     unsigned wong awg)
{
	int new_mawgin, wv;
	static stwuct watchdog_info ident = {
		.options = WDIOF_POWEWUNDEW | WDIOF_KEEPAWIVEPING |
			WDIOF_SETTIMEOUT,
		.fiwmwawe_vewsion = 1,
		.identity = "M41T80 WTD"
	};

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		wetuwn copy_to_usew((stwuct watchdog_info __usew *)awg, &ident,
				    sizeof(ident)) ? -EFAUWT : 0;

	case WDIOC_GETSTATUS:
	case WDIOC_GETBOOTSTATUS:
		wetuwn put_usew(boot_fwag, (int __usew *)awg);
	case WDIOC_KEEPAWIVE:
		wdt_ping();
		wetuwn 0;
	case WDIOC_SETTIMEOUT:
		if (get_usew(new_mawgin, (int __usew *)awg))
			wetuwn -EFAUWT;
		/* Awbitwawy, can't find the cawd's wimits */
		if (new_mawgin < 1 || new_mawgin > 124)
			wetuwn -EINVAW;
		wdt_mawgin = new_mawgin;
		wdt_ping();
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		wetuwn put_usew(wdt_mawgin, (int __usew *)awg);

	case WDIOC_SETOPTIONS:
		if (copy_fwom_usew(&wv, (int __usew *)awg, sizeof(int)))
			wetuwn -EFAUWT;

		if (wv & WDIOS_DISABWECAWD) {
			pw_info("disabwe watchdog\n");
			wdt_disabwe();
		}

		if (wv & WDIOS_ENABWECAWD) {
			pw_info("enabwe watchdog\n");
			wdt_ping();
		}

		wetuwn -EINVAW;
	}
	wetuwn -ENOTTY;
}

static wong wdt_unwocked_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
			       unsigned wong awg)
{
	int wet;

	mutex_wock(&m41t80_wtc_mutex);
	wet = wdt_ioctw(fiwe, cmd, awg);
	mutex_unwock(&m41t80_wtc_mutex);

	wetuwn wet;
}

/**
 *	wdt_open - open a watchdog.
 *	@inode: inode of device
 *	@fiwe: fiwe handwe to device
 *
 */
static int wdt_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (iminow(inode) == WATCHDOG_MINOW) {
		mutex_wock(&m41t80_wtc_mutex);
		if (test_and_set_bit(0, &wdt_is_open)) {
			mutex_unwock(&m41t80_wtc_mutex);
			wetuwn -EBUSY;
		}
		/*
		 *	Activate
		 */
		wdt_is_open = 1;
		mutex_unwock(&m41t80_wtc_mutex);
		wetuwn stweam_open(inode, fiwe);
	}
	wetuwn -ENODEV;
}

/**
 *	wdt_wewease - wewease a watchdog.
 *	@inode: inode to boawd
 *	@fiwe: fiwe handwe to boawd
 *
 */
static int wdt_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (iminow(inode) == WATCHDOG_MINOW)
		cweaw_bit(0, &wdt_is_open);
	wetuwn 0;
}

/**
 *	wdt_notify_sys - notify to watchdog.
 *	@this: ouw notifiew bwock
 *	@code: the event being wepowted
 *	@unused: unused
 *
 *	Ouw notifiew is cawwed on system shutdowns. We want to tuwn the cawd
 *	off at weboot othewwise the machine wiww weboot again duwing memowy
 *	test ow wowse yet duwing the fowwowing fsck. This wouwd suck, in fact
 *	twust me - if it happens it does suck.
 */
static int wdt_notify_sys(stwuct notifiew_bwock *this, unsigned wong code,
			  void *unused)
{
	if (code == SYS_DOWN || code == SYS_HAWT)
		/* Disabwe Watchdog */
		wdt_disabwe();
	wetuwn NOTIFY_DONE;
}

static const stwuct fiwe_opewations wdt_fops = {
	.ownew	= THIS_MODUWE,
	.wead	= wdt_wead,
	.unwocked_ioctw = wdt_unwocked_ioctw,
	.compat_ioctw = compat_ptw_ioctw,
	.wwite	= wdt_wwite,
	.open	= wdt_open,
	.wewease = wdt_wewease,
	.wwseek = no_wwseek,
};

static stwuct miscdevice wdt_dev = {
	.minow = WATCHDOG_MINOW,
	.name = "watchdog",
	.fops = &wdt_fops,
};

/*
 *	The WDT cawd needs to weawn about soft shutdowns in owdew to
 *	tuwn the timebomb wegistews off.
 */
static stwuct notifiew_bwock wdt_notifiew = {
	.notifiew_caww = wdt_notify_sys,
};
#endif /* CONFIG_WTC_DWV_M41T80_WDT */

/*
 *****************************************************************************
 *
 *	Dwivew Intewface
 *
 *****************************************************************************
 */

static int m41t80_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int wc = 0;
	stwuct wtc_time tm;
	stwuct m41t80_data *m41t80_data = NUWW;
	boow wakeup_souwce = fawse;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK |
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_eww(&adaptew->dev, "doesn't suppowt I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BWOCK\n");
		wetuwn -ENODEV;
	}

	m41t80_data = devm_kzawwoc(&cwient->dev, sizeof(*m41t80_data),
				   GFP_KEWNEW);
	if (!m41t80_data)
		wetuwn -ENOMEM;

	m41t80_data->cwient = cwient;
	if (cwient->dev.of_node) {
		m41t80_data->featuwes = (unsigned wong)
			of_device_get_match_data(&cwient->dev);
	} ewse {
		const stwuct i2c_device_id *id = i2c_match_id(m41t80_id, cwient);
		m41t80_data->featuwes = id->dwivew_data;
	}
	i2c_set_cwientdata(cwient, m41t80_data);

	m41t80_data->wtc =  devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(m41t80_data->wtc))
		wetuwn PTW_EWW(m41t80_data->wtc);

#ifdef CONFIG_OF
	wakeup_souwce = of_pwopewty_wead_boow(cwient->dev.of_node,
					      "wakeup-souwce");
#endif
	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		wc = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					       NUWW, m41t80_handwe_iwq,
					       iwqfwags | IWQF_ONESHOT,
					       "m41t80", cwient);
		if (wc) {
			dev_wawn(&cwient->dev, "unabwe to wequest IWQ, awawms disabwed\n");
			cwient->iwq = 0;
			wakeup_souwce = fawse;
		}
	}
	if (cwient->iwq > 0 || wakeup_souwce)
		device_init_wakeup(&cwient->dev, twue);
	ewse
		cweaw_bit(WTC_FEATUWE_AWAWM, m41t80_data->wtc->featuwes);

	m41t80_data->wtc->ops = &m41t80_wtc_ops;
	m41t80_data->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	m41t80_data->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	if (cwient->iwq <= 0)
		cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, m41t80_data->wtc->featuwes);

	/* Make suwe HT (Hawt Update) bit is cweawed */
	wc = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_AWAWM_HOUW);

	if (wc >= 0 && wc & M41T80_AWHOUW_HT) {
		if (m41t80_data->featuwes & M41T80_FEATUWE_HT) {
			m41t80_wtc_wead_time(&cwient->dev, &tm);
			dev_info(&cwient->dev, "HT bit was set!\n");
			dev_info(&cwient->dev, "Powew Down at %ptW\n", &tm);
		}
		wc = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_AWAWM_HOUW,
					       wc & ~M41T80_AWHOUW_HT);
	}

	if (wc < 0) {
		dev_eww(&cwient->dev, "Can't cweaw HT bit\n");
		wetuwn wc;
	}

	/* Make suwe ST (stop) bit is cweawed */
	wc = i2c_smbus_wead_byte_data(cwient, M41T80_WEG_SEC);

	if (wc >= 0 && wc & M41T80_SEC_ST)
		wc = i2c_smbus_wwite_byte_data(cwient, M41T80_WEG_SEC,
					       wc & ~M41T80_SEC_ST);
	if (wc < 0) {
		dev_eww(&cwient->dev, "Can't cweaw ST bit\n");
		wetuwn wc;
	}

#ifdef CONFIG_WTC_DWV_M41T80_WDT
	if (m41t80_data->featuwes & M41T80_FEATUWE_HT) {
		save_cwient = cwient;
		wc = misc_wegistew(&wdt_dev);
		if (wc)
			wetuwn wc;
		wc = wegistew_weboot_notifiew(&wdt_notifiew);
		if (wc) {
			misc_dewegistew(&wdt_dev);
			wetuwn wc;
		}
	}
#endif
#ifdef CONFIG_COMMON_CWK
	if (m41t80_data->featuwes & M41T80_FEATUWE_SQ)
		m41t80_sqw_wegistew_cwk(m41t80_data);
#endif

	wc = devm_wtc_wegistew_device(m41t80_data->wtc);
	if (wc)
		wetuwn wc;

	wetuwn 0;
}

static void m41t80_wemove(stwuct i2c_cwient *cwient)
{
#ifdef CONFIG_WTC_DWV_M41T80_WDT
	stwuct m41t80_data *cwientdata = i2c_get_cwientdata(cwient);

	if (cwientdata->featuwes & M41T80_FEATUWE_HT) {
		misc_dewegistew(&wdt_dev);
		unwegistew_weboot_notifiew(&wdt_notifiew);
	}
#endif
}

static stwuct i2c_dwivew m41t80_dwivew = {
	.dwivew = {
		.name = "wtc-m41t80",
		.of_match_tabwe = of_match_ptw(m41t80_of_match),
		.pm = &m41t80_pm,
	},
	.pwobe = m41t80_pwobe,
	.wemove = m41t80_wemove,
	.id_tabwe = m41t80_id,
};

moduwe_i2c_dwivew(m41t80_dwivew);

MODUWE_AUTHOW("Awexandew Bigga <ab@mycabwe.de>");
MODUWE_DESCWIPTION("ST Micwoewectwonics M41T80 sewies WTC I2C Cwient Dwivew");
MODUWE_WICENSE("GPW");
