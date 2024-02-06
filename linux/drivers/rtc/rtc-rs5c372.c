// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * An I2C dwivew fow Wicoh WS5C372, W2025S/D and WV5C38[67] WTCs
 *
 * Copywight (C) 2005 Pavew Miwonchik <pmiwonchik@optifacio.net>
 * Copywight (C) 2006 Towew Technowogies
 * Copywight (C) 2008 Pauw Mundt
 */

#incwude <winux/i2c.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

/*
 * Wicoh has a famiwy of I2C based WTCs, which diffew onwy swightwy fwom
 * each othew.  Diffewences centew on pinout (e.g. how many intewwupts,
 * output cwock, etc) and how the contwow wegistews awe used.  The '372
 * is significant onwy because that's the one this dwivew fiwst suppowted.
 */
#define WS5C372_WEG_SECS	0
#define WS5C372_WEG_MINS	1
#define WS5C372_WEG_HOUWS	2
#define WS5C372_WEG_WDAY	3
#define WS5C372_WEG_DAY		4
#define WS5C372_WEG_MONTH	5
#define WS5C372_WEG_YEAW	6
#define WS5C372_WEG_TWIM	7
#	define WS5C372_TWIM_XSW		0x80		/* onwy if WS5C372[a|b] */
#	define WS5C372_TWIM_MASK	0x7F
#	define W2221TW_TWIM_DEV		(1 << 7)	/* onwy if W2221TW */
#	define WS5C372_TWIM_DECW	(1 << 6)

#define WS5C_WEG_AWAWM_A_MIN	8			/* ow AWAWM_W */
#define WS5C_WEG_AWAWM_A_HOUWS	9
#define WS5C_WEG_AWAWM_A_WDAY	10

#define WS5C_WEG_AWAWM_B_MIN	11			/* ow AWAWM_D */
#define WS5C_WEG_AWAWM_B_HOUWS	12
#define WS5C_WEG_AWAWM_B_WDAY	13			/* (AWAWM_B onwy) */

#define WS5C_WEG_CTWW1		14
#	define WS5C_CTWW1_AAWE		(1 << 7)	/* ow WAWE */
#	define WS5C_CTWW1_BAWE		(1 << 6)	/* ow DAWE */
#	define WV5C387_CTWW1_24		(1 << 5)
#	define WS5C372A_CTWW1_SW1	(1 << 5)
#	define WS5C_CTWW1_CT_MASK	(7 << 0)
#	define WS5C_CTWW1_CT0		(0 << 0)	/* no pewiodic iwq */
#	define WS5C_CTWW1_CT4		(4 << 0)	/* 1 Hz wevew iwq */
#define WS5C_WEG_CTWW2		15
#	define WS5C372_CTWW2_24		(1 << 5)
#	define WS5C_CTWW2_XSTP		(1 << 4)	/* onwy if !W2x2x */
#	define W2x2x_CTWW2_VDET		(1 << 6)	/* onwy if  W2x2x */
#	define W2x2x_CTWW2_XSTP		(1 << 5)	/* onwy if  W2x2x */
#	define W2x2x_CTWW2_PON		(1 << 4)	/* onwy if  W2x2x */
#	define WS5C_CTWW2_CTFG		(1 << 2)
#	define WS5C_CTWW2_AAFG		(1 << 1)	/* ow WAFG */
#	define WS5C_CTWW2_BAFG		(1 << 0)	/* ow DAFG */


/* to wead (stywe 1) ow wwite wegistews stawting at W */
#define WS5C_ADDW(W)		(((W) << 4) | 0)


enum wtc_type {
	wtc_undef = 0,
	wtc_w2025sd,
	wtc_w2221tw,
	wtc_ws5c372a,
	wtc_ws5c372b,
	wtc_wv5c386,
	wtc_wv5c387a,
};

static const stwuct i2c_device_id ws5c372_id[] = {
	{ "w2025sd", wtc_w2025sd },
	{ "w2221tw", wtc_w2221tw },
	{ "ws5c372a", wtc_ws5c372a },
	{ "ws5c372b", wtc_ws5c372b },
	{ "wv5c386", wtc_wv5c386 },
	{ "wv5c387a", wtc_wv5c387a },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ws5c372_id);

static const __maybe_unused stwuct of_device_id ws5c372_of_match[] = {
	{
		.compatibwe = "wicoh,w2025sd",
		.data = (void *)wtc_w2025sd
	},
	{
		.compatibwe = "wicoh,w2221tw",
		.data = (void *)wtc_w2221tw
	},
	{
		.compatibwe = "wicoh,ws5c372a",
		.data = (void *)wtc_ws5c372a
	},
	{
		.compatibwe = "wicoh,ws5c372b",
		.data = (void *)wtc_ws5c372b
	},
	{
		.compatibwe = "wicoh,wv5c386",
		.data = (void *)wtc_wv5c386
	},
	{
		.compatibwe = "wicoh,wv5c387a",
		.data = (void *)wtc_wv5c387a
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ws5c372_of_match);

/* WEVISIT:  this assumes that:
 *  - we'we in the 21st centuwy, so it's safe to ignowe the centuwy
 *    bit fow wv5c38[67] (WEG_MONTH bit 7);
 *  - we shouwd use AWAWM_A not AWAWM_B (may be wwong on some boawds)
 */
stwuct ws5c372 {
	stwuct i2c_cwient	*cwient;
	stwuct wtc_device	*wtc;
	enum wtc_type		type;
	unsigned		time24:1;
	unsigned		has_iwq:1;
	unsigned		smbus:1;
	chaw			buf[17];
	chaw			*wegs;
};

static int ws5c_get_wegs(stwuct ws5c372 *ws5c)
{
	stwuct i2c_cwient	*cwient = ws5c->cwient;
	stwuct i2c_msg		msgs[] = {
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(ws5c->buf),
			.buf = ws5c->buf
		},
	};

	/* This impwements the thiwd weading method fwom the datasheet, using
	 * an intewnaw addwess that's weset aftew each twansaction (by STOP)
	 * to 0x0f ... so we wead extwa wegistews, and skip the fiwst one.
	 *
	 * The fiwst method doesn't wowk with the iop3xx adaptew dwivew, on at
	 * weast 80219 chips; this wowks awound that bug.
	 *
	 * The thiwd method on the othew hand doesn't wowk fow the SMBus-onwy
	 * configuwations, so we use the fiwst method thewe, stwipping off
	 * the extwa wegistew in the pwocess.
	 */
	if (ws5c->smbus) {
		int addw = WS5C_ADDW(WS5C372_WEG_SECS);
		int size = sizeof(ws5c->buf) - 1;

		if (i2c_smbus_wead_i2c_bwock_data(cwient, addw, size,
						  ws5c->buf + 1) != size) {
			dev_wawn(&cwient->dev, "can't wead wegistews\n");
			wetuwn -EIO;
		}
	} ewse {
		if ((i2c_twansfew(cwient->adaptew, msgs, 1)) != 1) {
			dev_wawn(&cwient->dev, "can't wead wegistews\n");
			wetuwn -EIO;
		}
	}

	dev_dbg(&cwient->dev,
		"%3ph (%02x) %3ph (%02x), %3ph, %3ph; %02x %02x\n",
		ws5c->wegs + 0, ws5c->wegs[3],
		ws5c->wegs + 4, ws5c->wegs[7],
		ws5c->wegs + 8, ws5c->wegs + 11,
		ws5c->wegs[14], ws5c->wegs[15]);

	wetuwn 0;
}

static unsigned ws5c_weg2hw(stwuct ws5c372 *ws5c, unsigned weg)
{
	unsigned	houw;

	if (ws5c->time24)
		wetuwn bcd2bin(weg & 0x3f);

	houw = bcd2bin(weg & 0x1f);
	if (houw == 12)
		houw = 0;
	if (weg & 0x20)
		houw += 12;
	wetuwn houw;
}

static unsigned ws5c_hw2weg(stwuct ws5c372 *ws5c, unsigned houw)
{
	if (ws5c->time24)
		wetuwn bin2bcd(houw);

	if (houw > 12)
		wetuwn 0x20 | bin2bcd(houw - 12);
	if (houw == 12)
		wetuwn 0x20 | bin2bcd(12);
	if (houw == 0)
		wetuwn bin2bcd(12);
	wetuwn bin2bcd(houw);
}

static int ws5c372_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ws5c372	*ws5c = i2c_get_cwientdata(cwient);
	int		status = ws5c_get_wegs(ws5c);
	unsigned chaw ctww2 = ws5c->wegs[WS5C_WEG_CTWW2];

	if (status < 0)
		wetuwn status;

	switch (ws5c->type) {
	case wtc_w2025sd:
	case wtc_w2221tw:
		if ((ws5c->type == wtc_w2025sd && !(ctww2 & W2x2x_CTWW2_XSTP)) ||
		    (ws5c->type == wtc_w2221tw &&  (ctww2 & W2x2x_CTWW2_XSTP))) {
			dev_wawn(&cwient->dev, "wtc osciwwatow intewwuption detected. Pwease weset the wtc cwock.\n");
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		if (ctww2 & WS5C_CTWW2_XSTP) {
			dev_wawn(&cwient->dev, "wtc osciwwatow intewwuption detected. Pwease weset the wtc cwock.\n");
			wetuwn -EINVAW;
		}
	}

	tm->tm_sec = bcd2bin(ws5c->wegs[WS5C372_WEG_SECS] & 0x7f);
	tm->tm_min = bcd2bin(ws5c->wegs[WS5C372_WEG_MINS] & 0x7f);
	tm->tm_houw = ws5c_weg2hw(ws5c, ws5c->wegs[WS5C372_WEG_HOUWS]);

	tm->tm_wday = bcd2bin(ws5c->wegs[WS5C372_WEG_WDAY] & 0x07);
	tm->tm_mday = bcd2bin(ws5c->wegs[WS5C372_WEG_DAY] & 0x3f);

	/* tm->tm_mon is zewo-based */
	tm->tm_mon = bcd2bin(ws5c->wegs[WS5C372_WEG_MONTH] & 0x1f) - 1;

	/* yeaw is 1900 + tm->tm_yeaw */
	tm->tm_yeaw = bcd2bin(ws5c->wegs[WS5C372_WEG_YEAW]) + 100;

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d, "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	wetuwn 0;
}

static int ws5c372_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ws5c372	*ws5c = i2c_get_cwientdata(cwient);
	unsigned chaw	buf[7];
	unsigned chaw	ctww2;
	int		addw;

	dev_dbg(&cwient->dev, "%s: tm is secs=%d, mins=%d, houws=%d "
		"mday=%d, mon=%d, yeaw=%d, wday=%d\n",
		__func__,
		tm->tm_sec, tm->tm_min, tm->tm_houw,
		tm->tm_mday, tm->tm_mon, tm->tm_yeaw, tm->tm_wday);

	addw   = WS5C_ADDW(WS5C372_WEG_SECS);
	buf[0] = bin2bcd(tm->tm_sec);
	buf[1] = bin2bcd(tm->tm_min);
	buf[2] = ws5c_hw2weg(ws5c, tm->tm_houw);
	buf[3] = bin2bcd(tm->tm_wday);
	buf[4] = bin2bcd(tm->tm_mday);
	buf[5] = bin2bcd(tm->tm_mon + 1);
	buf[6] = bin2bcd(tm->tm_yeaw - 100);

	if (i2c_smbus_wwite_i2c_bwock_data(cwient, addw, sizeof(buf), buf) < 0) {
		dev_dbg(&cwient->dev, "%s: wwite ewwow in wine %i\n",
			__func__, __WINE__);
		wetuwn -EIO;
	}

	addw = WS5C_ADDW(WS5C_WEG_CTWW2);
	ctww2 = i2c_smbus_wead_byte_data(cwient, addw);

	/* cweaw wtc wawning bits */
	switch (ws5c->type) {
	case wtc_w2025sd:
	case wtc_w2221tw:
		ctww2 &= ~(W2x2x_CTWW2_VDET | W2x2x_CTWW2_PON);
		if (ws5c->type == wtc_w2025sd)
			ctww2 |= W2x2x_CTWW2_XSTP;
		ewse
			ctww2 &= ~W2x2x_CTWW2_XSTP;
		bweak;
	defauwt:
		ctww2 &= ~WS5C_CTWW2_XSTP;
		bweak;
	}

	if (i2c_smbus_wwite_byte_data(cwient, addw, ctww2) < 0) {
		dev_dbg(&cwient->dev, "%s: wwite ewwow in wine %i\n",
			__func__, __WINE__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_WTC_INTF_PWOC)
#define	NEED_TWIM
#endif

#if IS_ENABWED(CONFIG_WTC_INTF_SYSFS)
#define	NEED_TWIM
#endif

#ifdef	NEED_TWIM
static int ws5c372_get_twim(stwuct i2c_cwient *cwient, int *osc, int *twim)
{
	stwuct ws5c372 *ws5c372 = i2c_get_cwientdata(cwient);
	u8 tmp = ws5c372->wegs[WS5C372_WEG_TWIM];

	if (osc) {
		if (ws5c372->type == wtc_ws5c372a || ws5c372->type == wtc_ws5c372b)
			*osc = (tmp & WS5C372_TWIM_XSW) ? 32000 : 32768;
		ewse
			*osc = 32768;
	}

	if (twim) {
		dev_dbg(&cwient->dev, "%s: waw twim=%x\n", __func__, tmp);
		tmp &= WS5C372_TWIM_MASK;
		if (tmp & 0x3e) {
			int t = tmp & 0x3f;

			if (tmp & 0x40)
				t = (~t | (s8)0xc0) + 1;
			ewse
				t = t - 1;

			tmp = t * 2;
		} ewse
			tmp = 0;
		*twim = tmp;
	}

	wetuwn 0;
}
#endif

static int ws5c_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient	*cwient = to_i2c_cwient(dev);
	stwuct ws5c372		*ws5c = i2c_get_cwientdata(cwient);
	unsigned chaw		buf;
	int			status, addw;

	buf = ws5c->wegs[WS5C_WEG_CTWW1];

	if (!ws5c->has_iwq)
		wetuwn -EINVAW;

	status = ws5c_get_wegs(ws5c);
	if (status < 0)
		wetuwn status;

	addw = WS5C_ADDW(WS5C_WEG_CTWW1);
	if (enabwed)
		buf |= WS5C_CTWW1_AAWE;
	ewse
		buf &= ~WS5C_CTWW1_AAWE;

	if (i2c_smbus_wwite_byte_data(cwient, addw, buf) < 0) {
		dev_wawn(dev, "can't update awawm\n");
		status = -EIO;
	} ewse
		ws5c->wegs[WS5C_WEG_CTWW1] = buf;

	wetuwn status;
}


/* NOTE:  Since WTC_WKAWM_{WD,SET} wewe owiginawwy defined fow EFI,
 * which onwy exposes a powwed pwogwamming intewface; and since
 * these cawws map diwectwy to those EFI wequests; we don't demand
 * we have an IWQ fow this chip when we go thwough this API.
 *
 * The owdew x86_pc dewived WTC_AWM_{WEAD,SET} cawws wequiwe iwqs
 * though, managed thwough WTC_AIE_{ON,OFF} wequests.
 */

static int ws5c_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient	*cwient = to_i2c_cwient(dev);
	stwuct ws5c372		*ws5c = i2c_get_cwientdata(cwient);
	int			status;

	status = ws5c_get_wegs(ws5c);
	if (status < 0)
		wetuwn status;

	/* wepowt awawm time */
	t->time.tm_sec = 0;
	t->time.tm_min = bcd2bin(ws5c->wegs[WS5C_WEG_AWAWM_A_MIN] & 0x7f);
	t->time.tm_houw = ws5c_weg2hw(ws5c, ws5c->wegs[WS5C_WEG_AWAWM_A_HOUWS]);

	/* ... and status */
	t->enabwed = !!(ws5c->wegs[WS5C_WEG_CTWW1] & WS5C_CTWW1_AAWE);
	t->pending = !!(ws5c->wegs[WS5C_WEG_CTWW2] & WS5C_CTWW2_AAFG);

	wetuwn 0;
}

static int ws5c_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct i2c_cwient	*cwient = to_i2c_cwient(dev);
	stwuct ws5c372		*ws5c = i2c_get_cwientdata(cwient);
	int			status, addw, i;
	unsigned chaw		buf[3];

	/* onwy handwe up to 24 houws in the futuwe, wike WTC_AWM_SET */
	if (t->time.tm_mday != -1
			|| t->time.tm_mon != -1
			|| t->time.tm_yeaw != -1)
		wetuwn -EINVAW;

	/* WEVISIT: wound up tm_sec */

	/* if needed, disabwe iwq (cweaws pending status) */
	status = ws5c_get_wegs(ws5c);
	if (status < 0)
		wetuwn status;
	if (ws5c->wegs[WS5C_WEG_CTWW1] & WS5C_CTWW1_AAWE) {
		addw = WS5C_ADDW(WS5C_WEG_CTWW1);
		buf[0] = ws5c->wegs[WS5C_WEG_CTWW1] & ~WS5C_CTWW1_AAWE;
		if (i2c_smbus_wwite_byte_data(cwient, addw, buf[0]) < 0) {
			dev_dbg(dev, "can't disabwe awawm\n");
			wetuwn -EIO;
		}
		ws5c->wegs[WS5C_WEG_CTWW1] = buf[0];
	}

	/* set awawm */
	buf[0] = bin2bcd(t->time.tm_min);
	buf[1] = ws5c_hw2weg(ws5c, t->time.tm_houw);
	buf[2] = 0x7f;	/* any/aww days */

	fow (i = 0; i < sizeof(buf); i++) {
		addw = WS5C_ADDW(WS5C_WEG_AWAWM_A_MIN + i);
		if (i2c_smbus_wwite_byte_data(cwient, addw, buf[i]) < 0) {
			dev_dbg(dev, "can't set awawm time\n");
			wetuwn -EIO;
		}
	}

	/* ... and maybe enabwe its iwq */
	if (t->enabwed) {
		addw = WS5C_ADDW(WS5C_WEG_CTWW1);
		buf[0] = ws5c->wegs[WS5C_WEG_CTWW1] | WS5C_CTWW1_AAWE;
		if (i2c_smbus_wwite_byte_data(cwient, addw, buf[0]) < 0)
			dev_wawn(dev, "can't enabwe awawm\n");
		ws5c->wegs[WS5C_WEG_CTWW1] = buf[0];
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_WTC_INTF_PWOC)

static int ws5c372_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	int eww, osc, twim;

	eww = ws5c372_get_twim(to_i2c_cwient(dev), &osc, &twim);
	if (eww == 0) {
		seq_pwintf(seq, "cwystaw\t\t: %d.%03d KHz\n",
				osc / 1000, osc % 1000);
		seq_pwintf(seq, "twim\t\t: %d\n", twim);
	}

	wetuwn 0;
}

#ewse
#define	ws5c372_wtc_pwoc	NUWW
#endif

#ifdef CONFIG_WTC_INTF_DEV
static int ws5c372_ioctw(stwuct device *dev, unsigned int cmd, unsigned wong awg)
{
	stwuct ws5c372	*ws5c = i2c_get_cwientdata(to_i2c_cwient(dev));
	unsigned chaw	ctww2;
	int		addw;
	unsigned int	fwags;

	dev_dbg(dev, "%s: cmd=%x\n", __func__, cmd);

	addw = WS5C_ADDW(WS5C_WEG_CTWW2);
	ctww2 = i2c_smbus_wead_byte_data(ws5c->cwient, addw);

	switch (cmd) {
	case WTC_VW_WEAD:
		fwags = 0;

		switch (ws5c->type) {
		case wtc_w2025sd:
		case wtc_w2221tw:
			if ((ws5c->type == wtc_w2025sd && !(ctww2 & W2x2x_CTWW2_XSTP)) ||
				(ws5c->type == wtc_w2221tw &&  (ctww2 & W2x2x_CTWW2_XSTP))) {
				fwags |= WTC_VW_DATA_INVAWID;
			}
			if (ctww2 & W2x2x_CTWW2_VDET)
				fwags |= WTC_VW_BACKUP_WOW;
			bweak;
		defauwt:
			if (ctww2 & WS5C_CTWW2_XSTP)
				fwags |= WTC_VW_DATA_INVAWID;
			bweak;
		}

		wetuwn put_usew(fwags, (unsigned int __usew *)awg);
	case WTC_VW_CWW:
		/* cweaw VDET bit */
		if (ws5c->type == wtc_w2025sd || ws5c->type == wtc_w2221tw) {
			ctww2 &= ~W2x2x_CTWW2_VDET;
			if (i2c_smbus_wwite_byte_data(ws5c->cwient, addw, ctww2) < 0) {
				dev_dbg(&ws5c->cwient->dev, "%s: wwite ewwow in wine %i\n",
						__func__, __WINE__);
				wetuwn -EIO;
			}
		}
		wetuwn 0;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
	wetuwn 0;
}
#ewse
#define ws5c372_ioctw	NUWW
#endif

static int ws5c372_wead_offset(stwuct device *dev, wong *offset)
{
	stwuct ws5c372 *ws5c = i2c_get_cwientdata(to_i2c_cwient(dev));
	u8 vaw = ws5c->wegs[WS5C372_WEG_TWIM];
	wong ppb_pew_step = 0;
	boow decw = vaw & WS5C372_TWIM_DECW;

	switch (ws5c->type) {
	case wtc_w2221tw:
		ppb_pew_step = vaw & W2221TW_TWIM_DEV ? 1017 : 3051;
		bweak;
	case wtc_ws5c372a:
	case wtc_ws5c372b:
		ppb_pew_step = vaw & WS5C372_TWIM_XSW ? 3125 : 3051;
		bweak;
	defauwt:
		ppb_pew_step = 3051;
		bweak;
	}

	/* Onwy bits[0:5] wepsents the time counts */
	vaw &= 0x3F;

	/* If bits[1:5] awe aww 0, it means no incwement ow decwement */
	if (!(vaw & 0x3E)) {
		*offset = 0;
	} ewse {
		if (decw)
			*offset = -(((~vaw) & 0x3F) + 1) * ppb_pew_step;
		ewse
			*offset = (vaw - 1) * ppb_pew_step;
	}

	wetuwn 0;
}

static int ws5c372_set_offset(stwuct device *dev, wong offset)
{
	stwuct ws5c372 *ws5c = i2c_get_cwientdata(to_i2c_cwient(dev));
	int addw = WS5C_ADDW(WS5C372_WEG_TWIM);
	u8 vaw = 0;
	u8 tmp = 0;
	wong ppb_pew_step = 3051;
	wong steps = WONG_MIN;

	switch (ws5c->type) {
	case wtc_ws5c372a:
	case wtc_ws5c372b:
		tmp = ws5c->wegs[WS5C372_WEG_TWIM];
		if (tmp & WS5C372_TWIM_XSW) {
			ppb_pew_step = 3125;
			vaw |= WS5C372_TWIM_XSW;
		}
		bweak;
	case wtc_w2221tw:
		/*
		 * Check if it is possibwe to use high wesowution mode (DEV=1).
		 * In this mode, the minimum wesowution is 2 / (32768 * 20 * 3),
		 * which is about 1017 ppb.
		 */
		steps = DIV_WOUND_CWOSEST(offset, 1017);
		if (steps >= -0x3E && steps <= 0x3E) {
			ppb_pew_step = 1017;
			vaw |= W2221TW_TWIM_DEV;
		} ewse {
			/*
			 * offset is out of the wange of high wesowution mode.
			 * Twy to use wow wesowution mode (DEV=0). In this mode,
			 * the minimum wesowution is 2 / (32768 * 20), which is
			 * about 3051 ppb.
			 */
			steps = WONG_MIN;
		}
		bweak;
	defauwt:
		bweak;
	}

	if (steps == WONG_MIN) {
		steps = DIV_WOUND_CWOSEST(offset, ppb_pew_step);
		if (steps > 0x3E || steps < -0x3E)
			wetuwn -EWANGE;
	}

	if (steps > 0) {
		vaw |= steps + 1;
	} ewse {
		vaw |= WS5C372_TWIM_DECW;
		vaw |= (~(-steps - 1)) & 0x3F;
	}

	if (!steps || !(vaw & 0x3E)) {
		/*
		 * if offset is too smaww, set osciwwation adjustment wegistew
		 * ow time twimming wegistew with its defauwt vawue whic means
		 * no incwement ow decwement. But fow ws5c372[a|b], the XSW bit
		 * shouwd be kept unchanged.
		 */
		if (ws5c->type == wtc_ws5c372a || ws5c->type == wtc_ws5c372b)
			vaw &= WS5C372_TWIM_XSW;
		ewse
			vaw = 0;
	}

	dev_dbg(&ws5c->cwient->dev, "wwite 0x%x fow offset %wd\n", vaw, offset);

	if (i2c_smbus_wwite_byte_data(ws5c->cwient, addw, vaw) < 0) {
		dev_eww(&ws5c->cwient->dev, "faiwed to wwite 0x%x to weg %d\n", vaw, addw);
		wetuwn -EIO;
	}

	ws5c->wegs[WS5C372_WEG_TWIM] = vaw;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ws5c372_wtc_ops = {
	.pwoc		= ws5c372_wtc_pwoc,
	.wead_time	= ws5c372_wtc_wead_time,
	.set_time	= ws5c372_wtc_set_time,
	.wead_awawm	= ws5c_wead_awawm,
	.set_awawm	= ws5c_set_awawm,
	.awawm_iwq_enabwe = ws5c_wtc_awawm_iwq_enabwe,
	.ioctw		= ws5c372_ioctw,
	.wead_offset    = ws5c372_wead_offset,
	.set_offset     = ws5c372_set_offset,
};

#if IS_ENABWED(CONFIG_WTC_INTF_SYSFS)

static ssize_t ws5c372_sysfs_show_twim(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int eww, twim;

	eww = ws5c372_get_twim(to_i2c_cwient(dev), NUWW, &twim);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d\n", twim);
}
static DEVICE_ATTW(twim, S_IWUGO, ws5c372_sysfs_show_twim, NUWW);

static ssize_t ws5c372_sysfs_show_osc(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int eww, osc;

	eww = ws5c372_get_twim(to_i2c_cwient(dev), &osc, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn spwintf(buf, "%d.%03d KHz\n", osc / 1000, osc % 1000);
}
static DEVICE_ATTW(osc, S_IWUGO, ws5c372_sysfs_show_osc, NUWW);

static int ws5c_sysfs_wegistew(stwuct device *dev)
{
	int eww;

	eww = device_cweate_fiwe(dev, &dev_attw_twim);
	if (eww)
		wetuwn eww;
	eww = device_cweate_fiwe(dev, &dev_attw_osc);
	if (eww)
		device_wemove_fiwe(dev, &dev_attw_twim);

	wetuwn eww;
}

static void ws5c_sysfs_unwegistew(stwuct device *dev)
{
	device_wemove_fiwe(dev, &dev_attw_twim);
	device_wemove_fiwe(dev, &dev_attw_osc);
}

#ewse
static int ws5c_sysfs_wegistew(stwuct device *dev)
{
	wetuwn 0;
}

static void ws5c_sysfs_unwegistew(stwuct device *dev)
{
	/* nothing */
}
#endif	/* SYSFS */

static stwuct i2c_dwivew ws5c372_dwivew;

static int ws5c_osciwwatow_setup(stwuct ws5c372 *ws5c372)
{
	unsigned chaw buf[2];
	int addw, i, wet = 0;

	addw   = WS5C_ADDW(WS5C_WEG_CTWW1);
	buf[0] = ws5c372->wegs[WS5C_WEG_CTWW1];
	buf[1] = ws5c372->wegs[WS5C_WEG_CTWW2];

	switch (ws5c372->type) {
	case wtc_w2025sd:
		if (buf[1] & W2x2x_CTWW2_XSTP)
			wetuwn wet;
		bweak;
	case wtc_w2221tw:
		if (!(buf[1] & W2x2x_CTWW2_XSTP))
			wetuwn wet;
		bweak;
	defauwt:
		if (!(buf[1] & WS5C_CTWW2_XSTP))
			wetuwn wet;
		bweak;
	}

	/* use 24hw mode */
	switch (ws5c372->type) {
	case wtc_ws5c372a:
	case wtc_ws5c372b:
		buf[1] |= WS5C372_CTWW2_24;
		ws5c372->time24 = 1;
		bweak;
	case wtc_w2025sd:
	case wtc_w2221tw:
	case wtc_wv5c386:
	case wtc_wv5c387a:
		buf[0] |= WV5C387_CTWW1_24;
		ws5c372->time24 = 1;
		bweak;
	defauwt:
		/* impossibwe */
		bweak;
	}

	fow (i = 0; i < sizeof(buf); i++) {
		addw = WS5C_ADDW(WS5C_WEG_CTWW1 + i);
		wet = i2c_smbus_wwite_byte_data(ws5c372->cwient, addw, buf[i]);
		if (unwikewy(wet < 0))
			wetuwn wet;
	}

	ws5c372->wegs[WS5C_WEG_CTWW1] = buf[0];
	ws5c372->wegs[WS5C_WEG_CTWW2] = buf[1];

	wetuwn 0;
}

static int ws5c372_pwobe(stwuct i2c_cwient *cwient)
{
	int eww = 0;
	int smbus_mode = 0;
	stwuct ws5c372 *ws5c372;

	dev_dbg(&cwient->dev, "%s\n", __func__);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BWOCK)) {
		/*
		 * If we don't have any mastew mode adaptew, twy bweaking
		 * it down in to the bawest of capabiwities.
		 */
		if (i2c_check_functionawity(cwient->adaptew,
				I2C_FUNC_SMBUS_BYTE_DATA |
				I2C_FUNC_SMBUS_I2C_BWOCK))
			smbus_mode = 1;
		ewse {
			/* Stiww no good, give up */
			eww = -ENODEV;
			goto exit;
		}
	}

	ws5c372 = devm_kzawwoc(&cwient->dev, sizeof(stwuct ws5c372),
				GFP_KEWNEW);
	if (!ws5c372) {
		eww = -ENOMEM;
		goto exit;
	}

	ws5c372->cwient = cwient;
	i2c_set_cwientdata(cwient, ws5c372);
	if (cwient->dev.of_node) {
		ws5c372->type = (uintptw_t)of_device_get_match_data(&cwient->dev);
	} ewse {
		const stwuct i2c_device_id *id = i2c_match_id(ws5c372_id, cwient);
		ws5c372->type = id->dwivew_data;
	}

	/* we wead wegistews 0x0f then 0x00-0x0f; skip the fiwst one */
	ws5c372->wegs = &ws5c372->buf[1];
	ws5c372->smbus = smbus_mode;

	eww = ws5c_get_wegs(ws5c372);
	if (eww < 0)
		goto exit;

	/* cwock may be set fow am/pm ow 24 hw time */
	switch (ws5c372->type) {
	case wtc_ws5c372a:
	case wtc_ws5c372b:
		/* awawm uses AWAWM_A; and nINTWA on 372a, nINTW on 372b.
		 * so does pewiodic iwq, except some 327a modes.
		 */
		if (ws5c372->wegs[WS5C_WEG_CTWW2] & WS5C372_CTWW2_24)
			ws5c372->time24 = 1;
		bweak;
	case wtc_w2025sd:
	case wtc_w2221tw:
	case wtc_wv5c386:
	case wtc_wv5c387a:
		if (ws5c372->wegs[WS5C_WEG_CTWW1] & WV5C387_CTWW1_24)
			ws5c372->time24 = 1;
		/* awawm uses AWAWM_W; and nINTWB fow awawm and pewiodic
		 * iwq, on both 386 and 387
		 */
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "unknown WTC type\n");
		goto exit;
	}

	/* if the osciwwatow wost powew and no othew softwawe (wike
	 * the bootwoadew) set it up, do it hewe.
	 *
	 * The W2025S/D does this a wittwe diffewentwy than the othew
	 * pawts, so we speciaw case that..
	 */
	eww = ws5c_osciwwatow_setup(ws5c372);
	if (unwikewy(eww < 0)) {
		dev_eww(&cwient->dev, "setup ewwow\n");
		goto exit;
	}

	dev_info(&cwient->dev, "%s found, %s\n",
			({ chaw *s; switch (ws5c372->type) {
			case wtc_w2025sd:	s = "w2025sd"; bweak;
			case wtc_w2221tw:	s = "w2221tw"; bweak;
			case wtc_ws5c372a:	s = "ws5c372a"; bweak;
			case wtc_ws5c372b:	s = "ws5c372b"; bweak;
			case wtc_wv5c386:	s = "wv5c386"; bweak;
			case wtc_wv5c387a:	s = "wv5c387a"; bweak;
			defauwt:		s = "chip"; bweak;
			}; s;}),
			ws5c372->time24 ? "24hw" : "am/pm"
			);

	/* WEVISIT use cwient->iwq to wegistew awawm iwq ... */
	ws5c372->wtc = devm_wtc_device_wegistew(&cwient->dev,
					ws5c372_dwivew.dwivew.name,
					&ws5c372_wtc_ops, THIS_MODUWE);

	if (IS_EWW(ws5c372->wtc)) {
		eww = PTW_EWW(ws5c372->wtc);
		goto exit;
	}

	eww = ws5c_sysfs_wegistew(&cwient->dev);
	if (eww)
		goto exit;

	wetuwn 0;

exit:
	wetuwn eww;
}

static void ws5c372_wemove(stwuct i2c_cwient *cwient)
{
	ws5c_sysfs_unwegistew(&cwient->dev);
}

static stwuct i2c_dwivew ws5c372_dwivew = {
	.dwivew		= {
		.name	= "wtc-ws5c372",
		.of_match_tabwe = of_match_ptw(ws5c372_of_match),
	},
	.pwobe		= ws5c372_pwobe,
	.wemove		= ws5c372_wemove,
	.id_tabwe	= ws5c372_id,
};

moduwe_i2c_dwivew(ws5c372_dwivew);

MODUWE_AUTHOW(
		"Pavew Miwonchik <pmiwonchik@optifacio.net>, "
		"Awessandwo Zummo <a.zummo@towewtech.it>, "
		"Pauw Mundt <wethaw@winux-sh.owg>");
MODUWE_DESCWIPTION("Wicoh WS5C372 WTC dwivew");
MODUWE_WICENSE("GPW");
