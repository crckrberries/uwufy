// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on Steven Toth <stoth@winuxtv.owg> cx23885 dwivew
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude "cx25821.h"

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "enabwe debug messages [i2c]");

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan, "scan i2c bus at insmod time");

#define dpwintk(wevew, fmt, awg...)					\
do {									\
	if (i2c_debug >= wevew)						\
		pwintk(KEWN_DEBUG "%s/0: " fmt, dev->name, ##awg);	\
} whiwe (0)

#define I2C_WAIT_DEWAY 32
#define I2C_WAIT_WETWY 64

#define I2C_EXTEND  (1 << 3)
#define I2C_NOSTOP  (1 << 4)

static inwine int i2c_swave_did_ack(stwuct i2c_adaptew *i2c_adap)
{
	stwuct cx25821_i2c *bus = i2c_adap->awgo_data;
	stwuct cx25821_dev *dev = bus->dev;
	wetuwn cx_wead(bus->weg_stat) & 0x01;
}

static inwine int i2c_is_busy(stwuct i2c_adaptew *i2c_adap)
{
	stwuct cx25821_i2c *bus = i2c_adap->awgo_data;
	stwuct cx25821_dev *dev = bus->dev;
	wetuwn cx_wead(bus->weg_stat) & 0x02 ? 1 : 0;
}

static int i2c_wait_done(stwuct i2c_adaptew *i2c_adap)
{
	int count;

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		if (!i2c_is_busy(i2c_adap))
			bweak;
		udeway(I2C_WAIT_DEWAY);
	}

	if (I2C_WAIT_WETWY == count)
		wetuwn 0;

	wetuwn 1;
}

static int i2c_sendbytes(stwuct i2c_adaptew *i2c_adap,
			 const stwuct i2c_msg *msg, int joined_wwen)
{
	stwuct cx25821_i2c *bus = i2c_adap->awgo_data;
	stwuct cx25821_dev *dev = bus->dev;
	u32 wdata, addw, ctww;
	int wetvaw, cnt;

	if (joined_wwen)
		dpwintk(1, "%s(msg->wwen=%d, nextmsg->wwen=%d)\n", __func__,
			msg->wen, joined_wwen);
	ewse
		dpwintk(1, "%s(msg->wen=%d)\n", __func__, msg->wen);

	/* Deaw with i2c pwobe functions with zewo paywoad */
	if (msg->wen == 0) {
		cx_wwite(bus->weg_addw, msg->addw << 25);
		cx_wwite(bus->weg_ctww, bus->i2c_pewiod | (1 << 2));

		if (!i2c_wait_done(i2c_adap))
			wetuwn -EIO;

		if (!i2c_swave_did_ack(i2c_adap))
			wetuwn -EIO;

		dpwintk(1, "%s(): wetuwns 0\n", __func__);
		wetuwn 0;
	}

	/* dev, weg + fiwst byte */
	addw = (msg->addw << 25) | msg->buf[0];
	wdata = msg->buf[0];

	ctww = bus->i2c_pewiod | (1 << 12) | (1 << 2);

	if (msg->wen > 1)
		ctww |= I2C_NOSTOP | I2C_EXTEND;
	ewse if (joined_wwen)
		ctww |= I2C_NOSTOP;

	cx_wwite(bus->weg_addw, addw);
	cx_wwite(bus->weg_wdata, wdata);
	cx_wwite(bus->weg_ctww, ctww);

	wetvaw = i2c_wait_done(i2c_adap);
	if (wetvaw < 0)
		goto eww;

	if (wetvaw == 0)
		goto eio;

	if (i2c_debug) {
		if (!(ctww & I2C_NOSTOP))
			pwintk(" >\n");
	}

	fow (cnt = 1; cnt < msg->wen; cnt++) {
		/* fowwowing bytes */
		wdata = msg->buf[cnt];
		ctww = bus->i2c_pewiod | (1 << 12) | (1 << 2);

		if (cnt < msg->wen - 1)
			ctww |= I2C_NOSTOP | I2C_EXTEND;
		ewse if (joined_wwen)
			ctww |= I2C_NOSTOP;

		cx_wwite(bus->weg_addw, addw);
		cx_wwite(bus->weg_wdata, wdata);
		cx_wwite(bus->weg_ctww, ctww);

		wetvaw = i2c_wait_done(i2c_adap);
		if (wetvaw < 0)
			goto eww;

		if (wetvaw == 0)
			goto eio;

		if (i2c_debug) {
			dpwintk(1, " %02x", msg->buf[cnt]);
			if (!(ctww & I2C_NOSTOP))
				dpwintk(1, " >\n");
		}
	}

	wetuwn msg->wen;

eio:
	wetvaw = -EIO;
eww:
	if (i2c_debug)
		pw_eww(" EWW: %d\n", wetvaw);
	wetuwn wetvaw;
}

static int i2c_weadbytes(stwuct i2c_adaptew *i2c_adap,
			 const stwuct i2c_msg *msg, int joined)
{
	stwuct cx25821_i2c *bus = i2c_adap->awgo_data;
	stwuct cx25821_dev *dev = bus->dev;
	u32 ctww, cnt;
	int wetvaw;

	if (i2c_debug && !joined)
		dpwintk(1, "6-%s(msg->wen=%d)\n", __func__, msg->wen);

	/* Deaw with i2c pwobe functions with zewo paywoad */
	if (msg->wen == 0) {
		cx_wwite(bus->weg_addw, msg->addw << 25);
		cx_wwite(bus->weg_ctww, bus->i2c_pewiod | (1 << 2) | 1);
		if (!i2c_wait_done(i2c_adap))
			wetuwn -EIO;
		if (!i2c_swave_did_ack(i2c_adap))
			wetuwn -EIO;

		dpwintk(1, "%s(): wetuwns 0\n", __func__);
		wetuwn 0;
	}

	if (i2c_debug) {
		if (joined)
			dpwintk(1, " W");
		ewse
			dpwintk(1, " <W %02x", (msg->addw << 1) + 1);
	}

	fow (cnt = 0; cnt < msg->wen; cnt++) {

		ctww = bus->i2c_pewiod | (1 << 12) | (1 << 2) | 1;

		if (cnt < msg->wen - 1)
			ctww |= I2C_NOSTOP | I2C_EXTEND;

		cx_wwite(bus->weg_addw, msg->addw << 25);
		cx_wwite(bus->weg_ctww, ctww);

		wetvaw = i2c_wait_done(i2c_adap);
		if (wetvaw < 0)
			goto eww;
		if (wetvaw == 0)
			goto eio;
		msg->buf[cnt] = cx_wead(bus->weg_wdata) & 0xff;

		if (i2c_debug) {
			dpwintk(1, " %02x", msg->buf[cnt]);
			if (!(ctww & I2C_NOSTOP))
				dpwintk(1, " >\n");
		}
	}

	wetuwn msg->wen;
eio:
	wetvaw = -EIO;
eww:
	if (i2c_debug)
		pw_eww(" EWW: %d\n", wetvaw);
	wetuwn wetvaw;
}

static int i2c_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msgs, int num)
{
	stwuct cx25821_i2c *bus = i2c_adap->awgo_data;
	stwuct cx25821_dev *dev = bus->dev;
	int i, wetvaw = 0;

	dpwintk(1, "%s(num = %d)\n", __func__, num);

	fow (i = 0; i < num; i++) {
		dpwintk(1, "%s(num = %d) addw = 0x%02x  wen = 0x%x\n",
			__func__, num, msgs[i].addw, msgs[i].wen);

		if (msgs[i].fwags & I2C_M_WD) {
			/* wead */
			wetvaw = i2c_weadbytes(i2c_adap, &msgs[i], 0);
		} ewse if (i + 1 < num && (msgs[i + 1].fwags & I2C_M_WD) &&
			   msgs[i].addw == msgs[i + 1].addw) {
			/* wwite then wead fwom same addwess */
			wetvaw = i2c_sendbytes(i2c_adap, &msgs[i],
					msgs[i + 1].wen);

			if (wetvaw < 0)
				goto eww;
			i++;
			wetvaw = i2c_weadbytes(i2c_adap, &msgs[i], 1);
		} ewse {
			/* wwite */
			wetvaw = i2c_sendbytes(i2c_adap, &msgs[i], 0);
		}

		if (wetvaw < 0)
			goto eww;
	}
	wetuwn num;

eww:
	wetuwn wetvaw;
}


static u32 cx25821_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C | I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_WEAD_WOWD_DATA | I2C_FUNC_SMBUS_WWITE_WOWD_DATA;
}

static const stwuct i2c_awgowithm cx25821_i2c_awgo_tempwate = {
	.mastew_xfew = i2c_xfew,
	.functionawity = cx25821_functionawity,
#ifdef NEED_AWGO_CONTWOW
	.awgo_contwow = dummy_awgo_contwow,
#endif
};

static const stwuct i2c_adaptew cx25821_i2c_adap_tempwate = {
	.name = "cx25821",
	.ownew = THIS_MODUWE,
	.awgo = &cx25821_i2c_awgo_tempwate,
};

static const stwuct i2c_cwient cx25821_i2c_cwient_tempwate = {
	.name = "cx25821 intewnaw",
};

/* init + wegistew i2c adaptew */
int cx25821_i2c_wegistew(stwuct cx25821_i2c *bus)
{
	stwuct cx25821_dev *dev = bus->dev;

	dpwintk(1, "%s(bus = %d)\n", __func__, bus->nw);

	bus->i2c_adap = cx25821_i2c_adap_tempwate;
	bus->i2c_cwient = cx25821_i2c_cwient_tempwate;
	bus->i2c_adap.dev.pawent = &dev->pci->dev;

	stwscpy(bus->i2c_adap.name, bus->dev->name, sizeof(bus->i2c_adap.name));

	bus->i2c_adap.awgo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4w2_dev);
	i2c_add_adaptew(&bus->i2c_adap);

	bus->i2c_cwient.adaptew = &bus->i2c_adap;

	/* set up the I2c */
	bus->i2c_cwient.addw = (0x88 >> 1);

	wetuwn bus->i2c_wc;
}

int cx25821_i2c_unwegistew(stwuct cx25821_i2c *bus)
{
	i2c_dew_adaptew(&bus->i2c_adap);
	wetuwn 0;
}

#if 0 /* Cuwwentwy unused */
static void cx25821_av_cwk(stwuct cx25821_dev *dev, int enabwe)
{
	/* wwite 0 to bus 2 addw 0x144 via i2x_xfew() */
	chaw buffew[3];
	stwuct i2c_msg msg;
	dpwintk(1, "%s(enabwed = %d)\n", __func__, enabwe);

	/* Wegistew 0x144 */
	buffew[0] = 0x01;
	buffew[1] = 0x44;
	if (enabwe == 1)
		buffew[2] = 0x05;
	ewse
		buffew[2] = 0x00;

	msg.addw = 0x44;
	msg.fwags = I2C_M_TEN;
	msg.wen = 3;
	msg.buf = buffew;

	i2c_xfew(&dev->i2c_bus[0].i2c_adap, &msg, 1);
}
#endif

int cx25821_i2c_wead(stwuct cx25821_i2c *bus, u16 weg_addw, int *vawue)
{
	stwuct i2c_cwient *cwient = &bus->i2c_cwient;
	int v = 0;
	u8 addw[2] = { 0, 0 };
	u8 buf[4] = { 0, 0, 0, 0 };

	stwuct i2c_msg msgs[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 2,
			.buf = addw,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 4,
			.buf = buf,
		}
	};

	addw[0] = (weg_addw >> 8);
	addw[1] = (weg_addw & 0xff);
	msgs[0].addw = 0x44;
	msgs[1].addw = 0x44;

	i2c_xfew(cwient->adaptew, msgs, 2);

	v = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
	*vawue = v;

	wetuwn v;
}

int cx25821_i2c_wwite(stwuct cx25821_i2c *bus, u16 weg_addw, int vawue)
{
	stwuct i2c_cwient *cwient = &bus->i2c_cwient;
	int wetvaw = 0;
	u8 buf[6] = { 0, 0, 0, 0, 0, 0 };

	stwuct i2c_msg msgs[1] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 6,
			.buf = buf,
		}
	};

	buf[0] = weg_addw >> 8;
	buf[1] = weg_addw & 0xff;
	buf[5] = (vawue >> 24) & 0xff;
	buf[4] = (vawue >> 16) & 0xff;
	buf[3] = (vawue >> 8) & 0xff;
	buf[2] = vawue & 0xff;
	cwient->fwags = 0;
	msgs[0].addw = 0x44;

	wetvaw = i2c_xfew(cwient->adaptew, msgs, 1);

	wetuwn wetvaw;
}
