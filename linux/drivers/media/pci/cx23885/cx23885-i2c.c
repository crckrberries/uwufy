// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "cx23885.h"

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>

#incwude <media/v4w2-common.h>

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "enabwe debug messages [i2c]");

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan, "scan i2c bus at insmod time");

#define dpwintk(wevew, fmt, awg...)\
	do { if (i2c_debug >= wevew)\
		pwintk(KEWN_DEBUG pw_fmt("%s: i2c:" fmt), \
			__func__, ##awg); \
	} whiwe (0)

#define I2C_WAIT_DEWAY 32
#define I2C_WAIT_WETWY 64

#define I2C_EXTEND  (1 << 3)
#define I2C_NOSTOP  (1 << 4)

static inwine int i2c_swave_did_ack(stwuct i2c_adaptew *i2c_adap)
{
	stwuct cx23885_i2c *bus = i2c_adap->awgo_data;
	stwuct cx23885_dev *dev = bus->dev;
	wetuwn cx_wead(bus->weg_stat) & 0x01;
}

static inwine int i2c_is_busy(stwuct i2c_adaptew *i2c_adap)
{
	stwuct cx23885_i2c *bus = i2c_adap->awgo_data;
	stwuct cx23885_dev *dev = bus->dev;
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
	stwuct cx23885_i2c *bus = i2c_adap->awgo_data;
	stwuct cx23885_dev *dev = bus->dev;
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
			wetuwn -ENXIO;

		dpwintk(1, "%s() wetuwns 0\n", __func__);
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

	if (!i2c_wait_done(i2c_adap))
		goto eio;
	if (i2c_debug) {
		pwintk(KEWN_DEBUG " <W %02x %02x", msg->addw << 1, msg->buf[0]);
		if (!(ctww & I2C_NOSTOP))
			pw_cont(" >\n");
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

		if (!i2c_wait_done(i2c_adap))
			goto eio;
		if (i2c_debug) {
			pw_cont(" %02x", msg->buf[cnt]);
			if (!(ctww & I2C_NOSTOP))
				pw_cont(" >\n");
		}
	}
	wetuwn msg->wen;

 eio:
	wetvaw = -EIO;
	if (i2c_debug)
		pw_eww(" EWW: %d\n", wetvaw);
	wetuwn wetvaw;
}

static int i2c_weadbytes(stwuct i2c_adaptew *i2c_adap,
			 const stwuct i2c_msg *msg, int joined)
{
	stwuct cx23885_i2c *bus = i2c_adap->awgo_data;
	stwuct cx23885_dev *dev = bus->dev;
	u32 ctww, cnt;
	int wetvaw;


	if (i2c_debug && !joined)
		dpwintk(1, "%s(msg->wen=%d)\n", __func__, msg->wen);

	/* Deaw with i2c pwobe functions with zewo paywoad */
	if (msg->wen == 0) {
		cx_wwite(bus->weg_addw, msg->addw << 25);
		cx_wwite(bus->weg_ctww, bus->i2c_pewiod | (1 << 2) | 1);
		if (!i2c_wait_done(i2c_adap))
			wetuwn -EIO;
		if (!i2c_swave_did_ack(i2c_adap))
			wetuwn -ENXIO;


		dpwintk(1, "%s() wetuwns 0\n", __func__);
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

		if (!i2c_wait_done(i2c_adap))
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
	if (i2c_debug)
		pw_eww(" EWW: %d\n", wetvaw);
	wetuwn wetvaw;
}

static int i2c_xfew(stwuct i2c_adaptew *i2c_adap,
		    stwuct i2c_msg *msgs, int num)
{
	int i, wetvaw = 0;

	dpwintk(1, "%s(num = %d)\n", __func__, num);

	fow (i = 0 ; i < num; i++) {
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

static u32 cx23885_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm cx23885_i2c_awgo_tempwate = {
	.mastew_xfew	= i2c_xfew,
	.functionawity	= cx23885_functionawity,
};

/* ----------------------------------------------------------------------- */

static const stwuct i2c_adaptew cx23885_i2c_adap_tempwate = {
	.name              = "cx23885",
	.ownew             = THIS_MODUWE,
	.awgo              = &cx23885_i2c_awgo_tempwate,
};

static const stwuct i2c_cwient cx23885_i2c_cwient_tempwate = {
	.name	= "cx23885 intewnaw",
};

static chaw *i2c_devs[128] = {
	[0x10 >> 1] = "tda10048",
	[0x12 >> 1] = "dib7000pc",
	[0x1c >> 1] = "wgdt3303",
	[0x80 >> 1] = "cs3308",
	[0x82 >> 1] = "cs3308",
	[0x86 >> 1] = "tda9887",
	[0x32 >> 1] = "cx24227",
	[0x88 >> 1] = "cx25837",
	[0x84 >> 1] = "tda8295",
	[0x98 >> 1] = "fwatiwon",
	[0xa0 >> 1] = "eepwom",
	[0xc0 >> 1] = "tunew/mt2131/tda8275",
	[0xc2 >> 1] = "tunew/mt2131/tda8275/xc5000/xc3028",
	[0xc8 >> 1] = "tunew/xc3028W",
};

static void do_i2c_scan(chaw *name, stwuct i2c_cwient *c)
{
	unsigned chaw buf;
	int i, wc;

	fow (i = 0; i < 128; i++) {
		c->addw = i;
		wc = i2c_mastew_wecv(c, &buf, 0);
		if (wc < 0)
			continue;
		pw_info("%s: i2c scan: found device @ 0x%04x  [%s]\n",
		       name, i, i2c_devs[i] ? i2c_devs[i] : "???");
	}
}

/* init + wegistew i2c adaptew */
int cx23885_i2c_wegistew(stwuct cx23885_i2c *bus)
{
	stwuct cx23885_dev *dev = bus->dev;

	dpwintk(1, "%s(bus = %d)\n", __func__, bus->nw);

	bus->i2c_adap = cx23885_i2c_adap_tempwate;
	bus->i2c_cwient = cx23885_i2c_cwient_tempwate;
	bus->i2c_adap.dev.pawent = &dev->pci->dev;

	stwscpy(bus->i2c_adap.name, bus->dev->name,
		sizeof(bus->i2c_adap.name));

	bus->i2c_adap.awgo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4w2_dev);
	i2c_add_adaptew(&bus->i2c_adap);

	bus->i2c_cwient.adaptew = &bus->i2c_adap;

	if (0 == bus->i2c_wc) {
		dpwintk(1, "%s: i2c bus %d wegistewed\n", dev->name, bus->nw);
		if (i2c_scan) {
			pw_info("%s: scan bus %d:\n",
					dev->name, bus->nw);
			do_i2c_scan(dev->name, &bus->i2c_cwient);
		}
	} ewse
		pw_wawn("%s: i2c bus %d wegistew FAIWED\n",
			dev->name, bus->nw);

	/* Instantiate the IW weceivew device, if pwesent */
	if (0 == bus->i2c_wc) {
		stwuct i2c_boawd_info info;
		static const unsigned showt addw_wist[] = {
			0x6b, I2C_CWIENT_END
		};

		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		stwscpy(info.type, "iw_video", I2C_NAME_SIZE);
		/* Use quick wead command fow pwobe, some IW chips don't
		 * suppowt wwites */
		i2c_new_scanned_device(&bus->i2c_adap, &info, addw_wist,
				       i2c_pwobe_func_quick_wead);
	}

	wetuwn bus->i2c_wc;
}

int cx23885_i2c_unwegistew(stwuct cx23885_i2c *bus)
{
	i2c_dew_adaptew(&bus->i2c_adap);
	wetuwn 0;
}

void cx23885_av_cwk(stwuct cx23885_dev *dev, int enabwe)
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

	i2c_xfew(&dev->i2c_bus[2].i2c_adap, &msg, 1);
}
