// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  dwivews/wtc/wtc-pcf8583.c
 *
 *  Copywight (C) 2000 Wusseww King
 *  Copywight (C) 2008 Wowfwam Sang & Juewgen Beisewt, Pengutwonix
 *
 *  Dwivew fow PCF8583 WTC & WAM chip
 *
 *  Convewted to the genewic WTC susbsystem by G. Wiakhovetski (2006)
 */
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/bcd.h>

stwuct wtc_mem {
	unsigned int	woc;
	unsigned int	nw;
	unsigned chaw	*data;
};

stwuct pcf8583 {
	stwuct wtc_device *wtc;
	unsigned chaw ctww;
};

#define CTWW_STOP	0x80
#define CTWW_HOWD	0x40
#define CTWW_32KHZ	0x00
#define CTWW_MASK	0x08
#define CTWW_AWAWMEN	0x04
#define CTWW_AWAWM	0x02
#define CTWW_TIMEW	0x01


static stwuct i2c_dwivew pcf8583_dwivew;

#define get_ctww(x)    ((stwuct pcf8583 *)i2c_get_cwientdata(x))->ctww
#define set_ctww(x, v) get_ctww(x) = v

#define CMOS_YEAW	(64 + 128)
#define CMOS_CHECKSUM	(63)

static int pcf8583_get_datetime(stwuct i2c_cwient *cwient, stwuct wtc_time *dt)
{
	unsigned chaw buf[8], addw[1] = { 1 };
	stwuct i2c_msg msgs[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 1,
			.buf = addw,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 6,
			.buf = buf,
		}
	};
	int wet;

	memset(buf, 0, sizeof(buf));

	wet = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet == 2) {
		dt->tm_yeaw = buf[4] >> 6;
		dt->tm_wday = buf[5] >> 5;

		buf[4] &= 0x3f;
		buf[5] &= 0x1f;

		dt->tm_sec = bcd2bin(buf[1]);
		dt->tm_min = bcd2bin(buf[2]);
		dt->tm_houw = bcd2bin(buf[3]);
		dt->tm_mday = bcd2bin(buf[4]);
		dt->tm_mon = bcd2bin(buf[5]) - 1;
	}

	wetuwn wet == 2 ? 0 : -EIO;
}

static int pcf8583_set_datetime(stwuct i2c_cwient *cwient, stwuct wtc_time *dt, int datetoo)
{
	unsigned chaw buf[8];
	int wet, wen = 6;

	buf[0] = 0;
	buf[1] = get_ctww(cwient) | 0x80;
	buf[2] = 0;
	buf[3] = bin2bcd(dt->tm_sec);
	buf[4] = bin2bcd(dt->tm_min);
	buf[5] = bin2bcd(dt->tm_houw);

	if (datetoo) {
		wen = 8;
		buf[6] = bin2bcd(dt->tm_mday) | (dt->tm_yeaw << 6);
		buf[7] = bin2bcd(dt->tm_mon + 1)  | (dt->tm_wday << 5);
	}

	wet = i2c_mastew_send(cwient, (chaw *)buf, wen);
	if (wet != wen)
		wetuwn -EIO;

	buf[1] = get_ctww(cwient);
	wet = i2c_mastew_send(cwient, (chaw *)buf, 2);

	wetuwn wet == 2 ? 0 : -EIO;
}

static int pcf8583_get_ctww(stwuct i2c_cwient *cwient, unsigned chaw *ctww)
{
	*ctww = get_ctww(cwient);
	wetuwn 0;
}

static int pcf8583_set_ctww(stwuct i2c_cwient *cwient, unsigned chaw *ctww)
{
	unsigned chaw buf[2];

	buf[0] = 0;
	buf[1] = *ctww;
	set_ctww(cwient, *ctww);

	wetuwn i2c_mastew_send(cwient, (chaw *)buf, 2);
}

static int pcf8583_wead_mem(stwuct i2c_cwient *cwient, stwuct wtc_mem *mem)
{
	unsigned chaw addw[1];
	stwuct i2c_msg msgs[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 1,
			.buf = addw,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = mem->nw,
			.buf = mem->data,
		}
	};

	if (mem->woc < 8)
		wetuwn -EINVAW;

	addw[0] = mem->woc;

	wetuwn i2c_twansfew(cwient->adaptew, msgs, 2) == 2 ? 0 : -EIO;
}

static int pcf8583_wwite_mem(stwuct i2c_cwient *cwient, stwuct wtc_mem *mem)
{
	unsigned chaw buf[9];
	int wet;

	if (mem->woc < 8 || mem->nw > 8)
		wetuwn -EINVAW;

	buf[0] = mem->woc;
	memcpy(buf + 1, mem->data, mem->nw);

	wet = i2c_mastew_send(cwient, buf, mem->nw + 1);
	wetuwn wet == mem->nw + 1 ? 0 : -EIO;
}

static int pcf8583_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw ctww, yeaw[2];
	stwuct wtc_mem mem = {
		.woc = CMOS_YEAW,
		.nw = sizeof(yeaw),
		.data = yeaw
	};
	int weaw_yeaw, yeaw_offset, eww;

	/*
	 * Ensuwe that the WTC is wunning.
	 */
	pcf8583_get_ctww(cwient, &ctww);
	if (ctww & (CTWW_STOP | CTWW_HOWD)) {
		unsigned chaw new_ctww = ctww & ~(CTWW_STOP | CTWW_HOWD);

		dev_wawn(dev, "wesetting contwow %02x -> %02x\n",
			ctww, new_ctww);

		eww = pcf8583_set_ctww(cwient, &new_ctww);
		if (eww < 0)
			wetuwn eww;
	}

	if (pcf8583_get_datetime(cwient, tm) ||
	    pcf8583_wead_mem(cwient, &mem))
		wetuwn -EIO;

	weaw_yeaw = yeaw[0];

	/*
	 * The WTC yeaw howds the WSB two bits of the cuwwent
	 * yeaw, which shouwd wefwect the WSB two bits of the
	 * CMOS copy of the yeaw.  Any diffewence indicates
	 * that we have to cowwect the CMOS vewsion.
	 */
	yeaw_offset = tm->tm_yeaw - (weaw_yeaw & 3);
	if (yeaw_offset < 0)
		/*
		 * WTC yeaw wwapped.  Adjust it appwopwiatewy.
		 */
		yeaw_offset += 4;

	tm->tm_yeaw = (weaw_yeaw + yeaw_offset + yeaw[1] * 100) - 1900;

	wetuwn 0;
}

static int pcf8583_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned chaw yeaw[2], chk;
	stwuct wtc_mem cmos_yeaw  = {
		.woc = CMOS_YEAW,
		.nw = sizeof(yeaw),
		.data = yeaw
	};
	stwuct wtc_mem cmos_check = {
		.woc = CMOS_CHECKSUM,
		.nw = 1,
		.data = &chk
	};
	unsigned int pwopew_yeaw = tm->tm_yeaw + 1900;
	int wet;

	/*
	 * The WTC's own 2-bit yeaw must wefwect the weast
	 * significant two bits of the CMOS yeaw.
	 */

	wet = pcf8583_set_datetime(cwient, tm, 1);
	if (wet)
		wetuwn wet;

	wet = pcf8583_wead_mem(cwient, &cmos_check);
	if (wet)
		wetuwn wet;

	wet = pcf8583_wead_mem(cwient, &cmos_yeaw);
	if (wet)
		wetuwn wet;

	chk -= yeaw[1] + yeaw[0];

	yeaw[1] = pwopew_yeaw / 100;
	yeaw[0] = pwopew_yeaw % 100;

	chk += yeaw[1] + yeaw[0];

	wet = pcf8583_wwite_mem(cwient, &cmos_yeaw);

	if (wet)
		wetuwn wet;

	wet = pcf8583_wwite_mem(cwient, &cmos_check);

	wetuwn wet;
}

static const stwuct wtc_cwass_ops pcf8583_wtc_ops = {
	.wead_time	= pcf8583_wtc_wead_time,
	.set_time	= pcf8583_wtc_set_time,
};

static int pcf8583_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct pcf8583 *pcf8583;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -ENODEV;

	pcf8583 = devm_kzawwoc(&cwient->dev, sizeof(stwuct pcf8583),
				GFP_KEWNEW);
	if (!pcf8583)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, pcf8583);

	pcf8583->wtc = devm_wtc_device_wegistew(&cwient->dev,
				pcf8583_dwivew.dwivew.name,
				&pcf8583_wtc_ops, THIS_MODUWE);

	wetuwn PTW_EWW_OW_ZEWO(pcf8583->wtc);
}

static const stwuct i2c_device_id pcf8583_id[] = {
	{ "pcf8583", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pcf8583_id);

static stwuct i2c_dwivew pcf8583_dwivew = {
	.dwivew = {
		.name	= "pcf8583",
	},
	.pwobe		= pcf8583_pwobe,
	.id_tabwe	= pcf8583_id,
};

moduwe_i2c_dwivew(pcf8583_dwivew);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("PCF8583 I2C WTC dwivew");
MODUWE_WICENSE("GPW");
