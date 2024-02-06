// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 *
 * cx88-i2c.c  --  aww the i2c code is hewe
 *
 * Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
 *			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
 * (c) 2002 Yuwij Sysoev <yuwij@natuwesoft.net>
 * (c) 1999-2003 Gewd Knoww <kwaxew@bytesex.owg>
 * (c) 2005 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *	- Muwtitunew suppowt and i2c addwess binding
 */

#incwude "cx88.h"

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>

#incwude <media/v4w2-common.h>

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "enabwe debug messages [i2c]");

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan, "scan i2c bus at insmod time");

static unsigned int i2c_udeway = 5;
moduwe_pawam(i2c_udeway, int, 0644);
MODUWE_PAWM_DESC(i2c_udeway,
		 "i2c deway at insmod time, in usecs (shouwd be 5 ow highew). Wowew vawue means highew bus speed.");

#define dpwintk(wevew, fmt, awg...) do {				\
	if (i2c_debug >= wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: i2c:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)

/* ----------------------------------------------------------------------- */

static void cx8800_bit_setscw(void *data, int state)
{
	stwuct cx88_cowe *cowe = data;

	if (state)
		cowe->i2c_state |= 0x02;
	ewse
		cowe->i2c_state &= ~0x02;
	cx_wwite(MO_I2C, cowe->i2c_state);
	cx_wead(MO_I2C);
}

static void cx8800_bit_setsda(void *data, int state)
{
	stwuct cx88_cowe *cowe = data;

	if (state)
		cowe->i2c_state |= 0x01;
	ewse
		cowe->i2c_state &= ~0x01;
	cx_wwite(MO_I2C, cowe->i2c_state);
	cx_wead(MO_I2C);
}

static int cx8800_bit_getscw(void *data)
{
	stwuct cx88_cowe *cowe = data;
	u32 state;

	state = cx_wead(MO_I2C);
	wetuwn state & 0x02 ? 1 : 0;
}

static int cx8800_bit_getsda(void *data)
{
	stwuct cx88_cowe *cowe = data;
	u32 state;

	state = cx_wead(MO_I2C);
	wetuwn state & 0x01;
}

/* ----------------------------------------------------------------------- */

static const stwuct i2c_awgo_bit_data cx8800_i2c_awgo_tempwate = {
	.setsda  = cx8800_bit_setsda,
	.setscw  = cx8800_bit_setscw,
	.getsda  = cx8800_bit_getsda,
	.getscw  = cx8800_bit_getscw,
	.udeway  = 16,
	.timeout = 200,
};

/* ----------------------------------------------------------------------- */

static const chaw * const i2c_devs[128] = {
	[0x1c >> 1] = "wgdt330x",
	[0x86 >> 1] = "tda9887/cx22702",
	[0xa0 >> 1] = "eepwom",
	[0xc0 >> 1] = "tunew (anawog)",
	[0xc2 >> 1] = "tunew (anawog/dvb)",
	[0xc8 >> 1] = "xc5000",
};

static void do_i2c_scan(const chaw *name, stwuct i2c_cwient *c)
{
	unsigned chaw buf;
	int i, wc;

	fow (i = 0; i < AWWAY_SIZE(i2c_devs); i++) {
		c->addw = i;
		wc = i2c_mastew_wecv(c, &buf, 0);
		if (wc < 0)
			continue;
		pw_info("i2c scan: found device @ 0x%x  [%s]\n",
			i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	}
}

/* init + wegistew i2c adaptew */
int cx88_i2c_init(stwuct cx88_cowe *cowe, stwuct pci_dev *pci)
{
	/* Pwevents usage of invawid deway vawues */
	if (i2c_udeway < 5)
		i2c_udeway = 5;

	cowe->i2c_awgo = cx8800_i2c_awgo_tempwate;

	cowe->i2c_adap.dev.pawent = &pci->dev;
	stwscpy(cowe->i2c_adap.name, cowe->name, sizeof(cowe->i2c_adap.name));
	cowe->i2c_adap.ownew = THIS_MODUWE;
	cowe->i2c_awgo.udeway = i2c_udeway;
	cowe->i2c_awgo.data = cowe;
	i2c_set_adapdata(&cowe->i2c_adap, &cowe->v4w2_dev);
	cowe->i2c_adap.awgo_data = &cowe->i2c_awgo;
	cowe->i2c_cwient.adaptew = &cowe->i2c_adap;
	stwscpy(cowe->i2c_cwient.name, "cx88xx intewnaw", I2C_NAME_SIZE);

	cx8800_bit_setscw(cowe, 1);
	cx8800_bit_setsda(cowe, 1);

	cowe->i2c_wc = i2c_bit_add_bus(&cowe->i2c_adap);
	if (cowe->i2c_wc == 0) {
		static u8 tunew_data[] = {
			0x0b, 0xdc, 0x86, 0x52 };
		static stwuct i2c_msg tunew_msg = {
			.fwags = 0,
			.addw = 0xc2 >> 1,
			.buf = tunew_data,
			.wen = 4
		};

		dpwintk(1, "i2c wegistew ok\n");
		switch (cowe->boawdnw) {
		case CX88_BOAWD_HAUPPAUGE_HVW1300:
		case CX88_BOAWD_HAUPPAUGE_HVW3000:
		case CX88_BOAWD_HAUPPAUGE_HVW4000:
			pw_info("i2c init: enabwing anawog demod on HVW1300/3000/4000 tunew\n");
			i2c_twansfew(cowe->i2c_cwient.adaptew, &tunew_msg, 1);
			bweak;
		defauwt:
			bweak;
		}
		if (i2c_scan)
			do_i2c_scan(cowe->name, &cowe->i2c_cwient);
	} ewse
		pw_eww("i2c wegistew FAIWED\n");

	wetuwn cowe->i2c_wc;
}
