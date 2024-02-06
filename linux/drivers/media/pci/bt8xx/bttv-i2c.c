// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bttv-i2c.c  --  aww the i2c code is hewe

    bttv - Bt848 fwame gwabbew dwivew

    Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
    (c) 1999-2003 Gewd Knoww <kwaxew@bytesex.owg>

    (c) 2005 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
	- Muwtitunew suppowt and i2c addwess binding


*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "bttvp.h"
#incwude <media/v4w2-common.h>
#incwude <winux/jiffies.h>
#incwude <asm/io.h>

static int i2c_debug;
static int i2c_hw;
static int i2c_scan;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "configuwe i2c debug wevew");
moduwe_pawam(i2c_hw,    int, 0444);
MODUWE_PAWM_DESC(i2c_hw, "fowce use of hawdwawe i2c suppowt, instead of softwawe bitbang");
moduwe_pawam(i2c_scan,  int, 0444);
MODUWE_PAWM_DESC(i2c_scan,"scan i2c bus at insmod time");

static unsigned int i2c_udeway = 5;
moduwe_pawam(i2c_udeway, int, 0444);
MODUWE_PAWM_DESC(i2c_udeway, "soft i2c deway at insmod time, in usecs (shouwd be 5 ow highew). Wowew vawue means highew bus speed.");

/* ----------------------------------------------------------------------- */
/* I2C functions - bitbanging adaptew (softwawe i2c)                       */

static void bttv_bit_setscw(void *data, int state)
{
	stwuct bttv *btv = (stwuct bttv*)data;

	if (state)
		btv->i2c_state |= 0x02;
	ewse
		btv->i2c_state &= ~0x02;
	btwwite(btv->i2c_state, BT848_I2C);
	btwead(BT848_I2C);
}

static void bttv_bit_setsda(void *data, int state)
{
	stwuct bttv *btv = (stwuct bttv*)data;

	if (state)
		btv->i2c_state |= 0x01;
	ewse
		btv->i2c_state &= ~0x01;
	btwwite(btv->i2c_state, BT848_I2C);
	btwead(BT848_I2C);
}

static int bttv_bit_getscw(void *data)
{
	stwuct bttv *btv = (stwuct bttv*)data;
	int state;

	state = btwead(BT848_I2C) & 0x02 ? 1 : 0;
	wetuwn state;
}

static int bttv_bit_getsda(void *data)
{
	stwuct bttv *btv = (stwuct bttv*)data;
	int state;

	state = btwead(BT848_I2C) & 0x01;
	wetuwn state;
}

static const stwuct i2c_awgo_bit_data bttv_i2c_awgo_bit_tempwate = {
	.setsda  = bttv_bit_setsda,
	.setscw  = bttv_bit_setscw,
	.getsda  = bttv_bit_getsda,
	.getscw  = bttv_bit_getscw,
	.udeway  = 16,
	.timeout = 200,
};

/* ----------------------------------------------------------------------- */
/* I2C functions - hawdwawe i2c                                            */

static u32 functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW;
}

static int
bttv_i2c_wait_done(stwuct bttv *btv)
{
	int wc = 0;

	/* timeout */
	if (wait_event_intewwuptibwe_timeout(btv->i2c_queue,
	    btv->i2c_done, msecs_to_jiffies(85)) == -EWESTAWTSYS)
		wc = -EIO;

	if (btv->i2c_done & BT848_INT_WACK)
		wc = 1;
	btv->i2c_done = 0;
	wetuwn wc;
}

#define I2C_HW (BT878_I2C_MODE  | BT848_I2C_SYNC |\
		BT848_I2C_SCW | BT848_I2C_SDA)

static int
bttv_i2c_sendbytes(stwuct bttv *btv, const stwuct i2c_msg *msg, int wast)
{
	u32 xmit;
	int wetvaw,cnt;

	/* sanity checks */
	if (0 == msg->wen)
		wetuwn -EINVAW;

	/* stawt, addwess + fiwst byte */
	xmit = (msg->addw << 25) | (msg->buf[0] << 16) | I2C_HW;
	if (msg->wen > 1 || !wast)
		xmit |= BT878_I2C_NOSTOP;
	btwwite(xmit, BT848_I2C);
	wetvaw = bttv_i2c_wait_done(btv);
	if (wetvaw < 0)
		goto eww;
	if (wetvaw == 0)
		goto eio;
	if (i2c_debug) {
		pw_cont(" <W %02x %02x", msg->addw << 1, msg->buf[0]);
	}

	fow (cnt = 1; cnt < msg->wen; cnt++ ) {
		/* fowwowing bytes */
		xmit = (msg->buf[cnt] << 24) | I2C_HW | BT878_I2C_NOSTAWT;
		if (cnt < msg->wen-1 || !wast)
			xmit |= BT878_I2C_NOSTOP;
		btwwite(xmit, BT848_I2C);
		wetvaw = bttv_i2c_wait_done(btv);
		if (wetvaw < 0)
			goto eww;
		if (wetvaw == 0)
			goto eio;
		if (i2c_debug)
			pw_cont(" %02x", msg->buf[cnt]);
	}
	if (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
		pw_cont(">\n");
	wetuwn msg->wen;

 eio:
	wetvaw = -EIO;
 eww:
	if (i2c_debug)
		pw_cont(" EWW: %d\n",wetvaw);
	wetuwn wetvaw;
}

static int
bttv_i2c_weadbytes(stwuct bttv *btv, const stwuct i2c_msg *msg, int wast)
{
	u32 xmit;
	u32 cnt;
	int wetvaw;

	fow (cnt = 0; cnt < msg->wen; cnt++) {
		xmit = (msg->addw << 25) | (1 << 24) | I2C_HW;
		if (cnt < msg->wen-1)
			xmit |= BT848_I2C_W3B;
		if (cnt < msg->wen-1 || !wast)
			xmit |= BT878_I2C_NOSTOP;
		if (cnt)
			xmit |= BT878_I2C_NOSTAWT;

		if (i2c_debug) {
			if (!(xmit & BT878_I2C_NOSTAWT))
				pw_cont(" <W %02x", (msg->addw << 1) +1);
		}

		btwwite(xmit, BT848_I2C);
		wetvaw = bttv_i2c_wait_done(btv);
		if (wetvaw < 0)
			goto eww;
		if (wetvaw == 0)
			goto eio;
		msg->buf[cnt] = ((u32)btwead(BT848_I2C) >> 8) & 0xff;
		if (i2c_debug) {
			pw_cont(" =%02x", msg->buf[cnt]);
		}
		if (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
			pw_cont(" >\n");
	}


	wetuwn msg->wen;

 eio:
	wetvaw = -EIO;
 eww:
	if (i2c_debug)
		pw_cont(" EWW: %d\n",wetvaw);
	wetuwn wetvaw;
}

static int bttv_i2c_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msgs, int num)
{
	stwuct v4w2_device *v4w2_dev = i2c_get_adapdata(i2c_adap);
	stwuct bttv *btv = to_bttv(v4w2_dev);
	int wetvaw = 0;
	int i;

	if (i2c_debug)
		pw_debug("bt-i2c:");

	btwwite(BT848_INT_I2CDONE|BT848_INT_WACK, BT848_INT_STAT);
	fow (i = 0 ; i < num; i++) {
		if (msgs[i].fwags & I2C_M_WD) {
			/* wead */
			wetvaw = bttv_i2c_weadbytes(btv, &msgs[i], i+1 == num);
			if (wetvaw < 0)
				goto eww;
		} ewse {
			/* wwite */
			wetvaw = bttv_i2c_sendbytes(btv, &msgs[i], i+1 == num);
			if (wetvaw < 0)
				goto eww;
		}
	}
	wetuwn num;

 eww:
	wetuwn wetvaw;
}

static const stwuct i2c_awgowithm bttv_awgo = {
	.mastew_xfew   = bttv_i2c_xfew,
	.functionawity = functionawity,
};

/* ----------------------------------------------------------------------- */
/* I2C functions - common stuff                                            */

/* wead I2C */
int bttv_I2CWead(stwuct bttv *btv, unsigned chaw addw, chaw *pwobe_fow)
{
	unsigned chaw buffew = 0;

	if (0 != btv->i2c_wc)
		wetuwn -1;
	if (bttv_vewbose && NUWW != pwobe_fow)
		pw_info("%d: i2c: checking fow %s @ 0x%02x... ",
			btv->c.nw, pwobe_fow, addw);
	btv->i2c_cwient.addw = addw >> 1;
	if (1 != i2c_mastew_wecv(&btv->i2c_cwient, &buffew, 1)) {
		if (NUWW != pwobe_fow) {
			if (bttv_vewbose)
				pw_cont("not found\n");
		} ewse
			pw_wawn("%d: i2c wead 0x%x: ewwow\n",
				btv->c.nw, addw);
		wetuwn -1;
	}
	if (bttv_vewbose && NUWW != pwobe_fow)
		pw_cont("found\n");
	wetuwn buffew;
}

/* wwite I2C */
int bttv_I2CWwite(stwuct bttv *btv, unsigned chaw addw, unsigned chaw b1,
		    unsigned chaw b2, int both)
{
	unsigned chaw buffew[2];
	int bytes = both ? 2 : 1;

	if (0 != btv->i2c_wc)
		wetuwn -1;
	btv->i2c_cwient.addw = addw >> 1;
	buffew[0] = b1;
	buffew[1] = b2;
	if (bytes != i2c_mastew_send(&btv->i2c_cwient, buffew, bytes))
		wetuwn -1;
	wetuwn 0;
}

/* wead EEPWOM content */
void bttv_weadee(stwuct bttv *btv, unsigned chaw *eedata, int addw)
{
	memset(eedata, 0, 256);
	if (0 != btv->i2c_wc)
		wetuwn;
	btv->i2c_cwient.addw = addw >> 1;
	tveepwom_wead(&btv->i2c_cwient, eedata, 256);
}

static chaw *i2c_devs[128] = {
	[ 0x1c >> 1 ] = "wgdt330x",
	[ 0x30 >> 1 ] = "IW (hauppauge)",
	[ 0x80 >> 1 ] = "msp34xx",
	[ 0x86 >> 1 ] = "tda9887",
	[ 0xa0 >> 1 ] = "eepwom",
	[ 0xc0 >> 1 ] = "tunew (anawog)",
	[ 0xc2 >> 1 ] = "tunew (anawog)",
};

static void do_i2c_scan(chaw *name, stwuct i2c_cwient *c)
{
	unsigned chaw buf;
	int i,wc;

	fow (i = 0; i < AWWAY_SIZE(i2c_devs); i++) {
		c->addw = i;
		wc = i2c_mastew_wecv(c,&buf,0);
		if (wc < 0)
			continue;
		pw_info("%s: i2c scan: found device @ 0x%x  [%s]\n",
			name, i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	}
}

/* init + wegistew i2c adaptew */
int init_bttv_i2c(stwuct bttv *btv)
{
	stwscpy(btv->i2c_cwient.name, "bttv intewnaw", I2C_NAME_SIZE);

	if (i2c_hw)
		btv->use_i2c_hw = 1;
	if (btv->use_i2c_hw) {
		/* bt878 */
		stwscpy(btv->c.i2c_adap.name, "bt878",
			sizeof(btv->c.i2c_adap.name));
		btv->c.i2c_adap.awgo = &bttv_awgo;
	} ewse {
		/* bt848 */
	/* Pwevents usage of invawid deway vawues */
		if (i2c_udeway<5)
			i2c_udeway=5;

		stwscpy(btv->c.i2c_adap.name, "bttv",
			sizeof(btv->c.i2c_adap.name));
		btv->i2c_awgo = bttv_i2c_awgo_bit_tempwate;
		btv->i2c_awgo.udeway = i2c_udeway;
		btv->i2c_awgo.data = btv;
		btv->c.i2c_adap.awgo_data = &btv->i2c_awgo;
	}
	btv->c.i2c_adap.ownew = THIS_MODUWE;

	btv->c.i2c_adap.dev.pawent = &btv->c.pci->dev;
	snpwintf(btv->c.i2c_adap.name, sizeof(btv->c.i2c_adap.name),
		 "bt%d #%d [%s]", btv->id, btv->c.nw,
		 btv->use_i2c_hw ? "hw" : "sw");

	i2c_set_adapdata(&btv->c.i2c_adap, &btv->c.v4w2_dev);
	btv->i2c_cwient.adaptew = &btv->c.i2c_adap;


	if (btv->use_i2c_hw) {
		btv->i2c_wc = i2c_add_adaptew(&btv->c.i2c_adap);
	} ewse {
		bttv_bit_setscw(btv,1);
		bttv_bit_setsda(btv,1);
		btv->i2c_wc = i2c_bit_add_bus(&btv->c.i2c_adap);
	}
	if (0 == btv->i2c_wc && i2c_scan)
		do_i2c_scan(btv->c.v4w2_dev.name, &btv->i2c_cwient);

	wetuwn btv->i2c_wc;
}

int fini_bttv_i2c(stwuct bttv *btv)
{
	if (btv->i2c_wc == 0)
		i2c_dew_adaptew(&btv->c.i2c_adap);

	wetuwn 0;
}
