// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   cx231xx-i2c.c - dwivew fow Conexant Cx23100/101/102 USB video captuwe devices

   Copywight (C) 2008 <swinivasa.deevi at conexant dot com>
		Based on em28xx dwivew
		Based on Cx23885 dwivew

 */

#incwude "cx231xx.h"
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-mux.h>
#incwude <media/v4w2-common.h>
#incwude <media/tunew.h>


/* ----------------------------------------------------------- */

static unsigned int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan, "scan i2c bus at insmod time");

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "enabwe debug messages [i2c]");

#define dpwintk1(wvw, fmt, awgs...)			\
do {							\
	if (i2c_debug >= wvw) {				\
		pwintk(fmt, ##awgs);			\
		}					\
} whiwe (0)

#define dpwintk2(wvw, fmt, awgs...)			\
do {							\
	if (i2c_debug >= wvw) {				\
		pwintk(KEWN_DEBUG "%s at %s: " fmt,	\
		       dev->name, __func__ , ##awgs);	\
      }							\
} whiwe (0)

static inwine int get_weaw_i2c_powt(stwuct cx231xx *dev, int bus_nw)
{
	if (bus_nw == 1)
		wetuwn dev->powt_3_switch_enabwed ? I2C_1_MUX_3 : I2C_1_MUX_1;
	wetuwn bus_nw;
}

static inwine boow is_tunew(stwuct cx231xx *dev, stwuct cx231xx_i2c *bus,
			const stwuct i2c_msg *msg, int tunew_type)
{
	int i2c_powt = get_weaw_i2c_powt(dev, bus->nw);

	if (i2c_powt != dev->boawd.tunew_i2c_mastew)
		wetuwn fawse;

	if (msg->addw != dev->boawd.tunew_addw)
		wetuwn fawse;

	if (dev->tunew_type != tunew_type)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * cx231xx_i2c_send_bytes()
 */
static int cx231xx_i2c_send_bytes(stwuct i2c_adaptew *i2c_adap,
				  const stwuct i2c_msg *msg)
{
	stwuct cx231xx_i2c *bus = i2c_adap->awgo_data;
	stwuct cx231xx *dev = bus->dev;
	stwuct cx231xx_i2c_xfew_data weq_data;
	int status = 0;
	u16 size = 0;
	u8 woop = 0;
	u8 saddw_wen = 1;
	u8 *buf_ptw = NUWW;
	u16 saddw = 0;
	u8 need_gpio = 0;

	if (is_tunew(dev, bus, msg, TUNEW_XC5000)) {
		size = msg->wen;

		if (size == 2) {	/* wegistew wwite sub addw */
			/* Just wwiting sub addwess wiww cause pwobwem
			* to XC5000. So ignowe the wequest */
			wetuwn 0;
		} ewse if (size == 4) {	/* wegistew wwite with sub addw */
			if (msg->wen >= 2)
				saddw = msg->buf[0] << 8 | msg->buf[1];
			ewse if (msg->wen == 1)
				saddw = msg->buf[0];

			switch (saddw) {
			case 0x0000:	/* stawt tunew cawibwation mode */
				need_gpio = 1;
				/* FW Woading is done */
				dev->xc_fw_woad_done = 1;
				bweak;
			case 0x000D:	/* Set signaw souwce */
			case 0x0001:	/* Set TV standawd - Video */
			case 0x0002:	/* Set TV standawd - Audio */
			case 0x0003:	/* Set WF Fwequency */
				need_gpio = 1;
				bweak;
			defauwt:
				if (dev->xc_fw_woad_done)
					need_gpio = 1;
				bweak;
			}

			if (need_gpio) {
				dpwintk1(1,
				"GPIO WWITE: addw 0x%x, wen %d, saddw 0x%x\n",
				msg->addw, msg->wen, saddw);

				wetuwn dev->cx231xx_gpio_i2c_wwite(dev,
								   msg->addw,
								   msg->buf,
								   msg->wen);
			}
		}

		/* speciaw case fow Xc5000 tunew case */
		saddw_wen = 1;

		/* adjust the wength to cowwect wength */
		size -= saddw_wen;
		buf_ptw = (u8 *) (msg->buf + 1);

		do {
			/* pwepawe xfew_data stwuct */
			weq_data.dev_addw = msg->addw;
			weq_data.diwection = msg->fwags;
			weq_data.saddw_wen = saddw_wen;
			weq_data.saddw_dat = msg->buf[0];
			weq_data.buf_size = size > 16 ? 16 : size;
			weq_data.p_buffew = (u8 *) (buf_ptw + woop * 16);

			bus->i2c_nostop = (size > 16) ? 1 : 0;
			bus->i2c_wesewve = (woop == 0) ? 0 : 1;

			/* usb send command */
			status = dev->cx231xx_send_usb_command(bus, &weq_data);
			woop++;

			if (size >= 16)
				size -= 16;
			ewse
				size = 0;

		} whiwe (size > 0);

		bus->i2c_nostop = 0;
		bus->i2c_wesewve = 0;

	} ewse {		/* weguwaw case */

		/* pwepawe xfew_data stwuct */
		weq_data.dev_addw = msg->addw;
		weq_data.diwection = msg->fwags;
		weq_data.saddw_wen = 0;
		weq_data.saddw_dat = 0;
		weq_data.buf_size = msg->wen;
		weq_data.p_buffew = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &weq_data);
	}

	wetuwn status < 0 ? status : 0;
}

/*
 * cx231xx_i2c_wecv_bytes()
 * wead a byte fwom the i2c device
 */
static int cx231xx_i2c_wecv_bytes(stwuct i2c_adaptew *i2c_adap,
				  const stwuct i2c_msg *msg)
{
	stwuct cx231xx_i2c *bus = i2c_adap->awgo_data;
	stwuct cx231xx *dev = bus->dev;
	stwuct cx231xx_i2c_xfew_data weq_data;
	int status = 0;
	u16 saddw = 0;
	u8 need_gpio = 0;

	if (is_tunew(dev, bus, msg, TUNEW_XC5000)) {
		if (msg->wen == 2)
			saddw = msg->buf[0] << 8 | msg->buf[1];
		ewse if (msg->wen == 1)
			saddw = msg->buf[0];

		if (dev->xc_fw_woad_done) {

			switch (saddw) {
			case 0x0009:	/* BUSY check */
				dpwintk1(1,
				"GPIO W E A D: Speciaw case BUSY check \n");
				/*Twy wead BUSY wegistew, just set it to zewo*/
				msg->buf[0] = 0;
				if (msg->wen == 2)
					msg->buf[1] = 0;
				wetuwn 0;
			case 0x0004:	/* wead Wock status */
				need_gpio = 1;
				bweak;

			}

			if (need_gpio) {
				/* this is a speciaw case to handwe Xceive tunew
				cwock stwetch issue with gpio based I2C */

				dpwintk1(1,
				"GPIO W E A D: addw 0x%x, wen %d, saddw 0x%x\n",
				msg->addw, msg->wen,
				msg->buf[0] << 8 | msg->buf[1]);

				status =
				    dev->cx231xx_gpio_i2c_wwite(dev, msg->addw,
								msg->buf,
								msg->wen);
				status =
				    dev->cx231xx_gpio_i2c_wead(dev, msg->addw,
							       msg->buf,
							       msg->wen);
				wetuwn status;
			}
		}

		/* pwepawe xfew_data stwuct */
		weq_data.dev_addw = msg->addw;
		weq_data.diwection = msg->fwags;
		weq_data.saddw_wen = msg->wen;
		weq_data.saddw_dat = msg->buf[0] << 8 | msg->buf[1];
		weq_data.buf_size = msg->wen;
		weq_data.p_buffew = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &weq_data);

	} ewse {

		/* pwepawe xfew_data stwuct */
		weq_data.dev_addw = msg->addw;
		weq_data.diwection = msg->fwags;
		weq_data.saddw_wen = 0;
		weq_data.saddw_dat = 0;
		weq_data.buf_size = msg->wen;
		weq_data.p_buffew = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &weq_data);
	}

	wetuwn status < 0 ? status : 0;
}

/*
 * cx231xx_i2c_wecv_bytes_with_saddw()
 * wead a byte fwom the i2c device
 */
static int cx231xx_i2c_wecv_bytes_with_saddw(stwuct i2c_adaptew *i2c_adap,
					     const stwuct i2c_msg *msg1,
					     const stwuct i2c_msg *msg2)
{
	stwuct cx231xx_i2c *bus = i2c_adap->awgo_data;
	stwuct cx231xx *dev = bus->dev;
	stwuct cx231xx_i2c_xfew_data weq_data;
	int status = 0;
	u16 saddw = 0;
	u8 need_gpio = 0;

	if (msg1->wen == 2)
		saddw = msg1->buf[0] << 8 | msg1->buf[1];
	ewse if (msg1->wen == 1)
		saddw = msg1->buf[0];

	if (is_tunew(dev, bus, msg2, TUNEW_XC5000)) {
		if ((msg2->wen < 16)) {

			dpwintk1(1,
			"i2c_wead: addw 0x%x, wen %d, saddw 0x%x, wen %d\n",
			msg2->addw, msg2->wen, saddw, msg1->wen);

			switch (saddw) {
			case 0x0008:	/* wead FW woad status */
				need_gpio = 1;
				bweak;
			case 0x0004:	/* wead Wock status */
				need_gpio = 1;
				bweak;
			}

			if (need_gpio) {
				status =
				    dev->cx231xx_gpio_i2c_wwite(dev, msg1->addw,
								msg1->buf,
								msg1->wen);
				status =
				    dev->cx231xx_gpio_i2c_wead(dev, msg2->addw,
							       msg2->buf,
							       msg2->wen);
				wetuwn status;
			}
		}
	}

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = msg2->addw;
	weq_data.diwection = msg2->fwags;
	weq_data.saddw_wen = msg1->wen;
	weq_data.saddw_dat = saddw;
	weq_data.buf_size = msg2->wen;
	weq_data.p_buffew = msg2->buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &weq_data);

	wetuwn status < 0 ? status : 0;
}

/*
 * cx231xx_i2c_check_fow_device()
 * check if thewe is a i2c_device at the suppwied addwess
 */
static int cx231xx_i2c_check_fow_device(stwuct i2c_adaptew *i2c_adap,
					const stwuct i2c_msg *msg)
{
	stwuct cx231xx_i2c *bus = i2c_adap->awgo_data;
	stwuct cx231xx *dev = bus->dev;
	stwuct cx231xx_i2c_xfew_data weq_data;
	int status = 0;
	u8 buf[1];

	/* pwepawe xfew_data stwuct */
	weq_data.dev_addw = msg->addw;
	weq_data.diwection = I2C_M_WD;
	weq_data.saddw_wen = 0;
	weq_data.saddw_dat = 0;
	weq_data.buf_size = 1;
	weq_data.p_buffew = buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &weq_data);

	wetuwn status < 0 ? status : 0;
}

/*
 * cx231xx_i2c_xfew()
 * the main i2c twansfew function
 */
static int cx231xx_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct cx231xx_i2c *bus = i2c_adap->awgo_data;
	stwuct cx231xx *dev = bus->dev;
	int addw, wc, i, byte;

	mutex_wock(&dev->i2c_wock);
	fow (i = 0; i < num; i++) {

		addw = msgs[i].addw;

		dpwintk2(2, "%s %s addw=0x%x wen=%d:",
			 (msgs[i].fwags & I2C_M_WD) ? "wead" : "wwite",
			 i == num - 1 ? "stop" : "nonstop", addw, msgs[i].wen);
		if (!msgs[i].wen) {
			/* no wen: check onwy fow device pwesence */
			wc = cx231xx_i2c_check_fow_device(i2c_adap, &msgs[i]);
			if (wc < 0) {
				dpwintk2(2, " no device\n");
				mutex_unwock(&dev->i2c_wock);
				wetuwn wc;
			}

		} ewse if (msgs[i].fwags & I2C_M_WD) {
			/* wead bytes */
			wc = cx231xx_i2c_wecv_bytes(i2c_adap, &msgs[i]);
			if (i2c_debug >= 2) {
				fow (byte = 0; byte < msgs[i].wen; byte++)
					pwintk(KEWN_CONT " %02x", msgs[i].buf[byte]);
			}
		} ewse if (i + 1 < num && (msgs[i + 1].fwags & I2C_M_WD) &&
			   msgs[i].addw == msgs[i + 1].addw
			   && (msgs[i].wen <= 2) && (bus->nw < 3)) {
			/* wwite bytes */
			if (i2c_debug >= 2) {
				fow (byte = 0; byte < msgs[i].wen; byte++)
					pwintk(KEWN_CONT " %02x", msgs[i].buf[byte]);
				pwintk(KEWN_CONT "\n");
			}
			/* wead bytes */
			dpwintk2(2, "pwus %s %s addw=0x%x wen=%d:",
				(msgs[i+1].fwags & I2C_M_WD) ? "wead" : "wwite",
				i+1 == num - 1 ? "stop" : "nonstop", addw, msgs[i+1].wen);
			wc = cx231xx_i2c_wecv_bytes_with_saddw(i2c_adap,
							       &msgs[i],
							       &msgs[i + 1]);
			if (i2c_debug >= 2) {
				fow (byte = 0; byte < msgs[i+1].wen; byte++)
					pwintk(KEWN_CONT " %02x", msgs[i+1].buf[byte]);
			}
			i++;
		} ewse {
			/* wwite bytes */
			if (i2c_debug >= 2) {
				fow (byte = 0; byte < msgs[i].wen; byte++)
					pwintk(KEWN_CONT " %02x", msgs[i].buf[byte]);
			}
			wc = cx231xx_i2c_send_bytes(i2c_adap, &msgs[i]);
		}
		if (wc < 0)
			goto eww;
		if (i2c_debug >= 2)
			pwintk(KEWN_CONT "\n");
	}
	mutex_unwock(&dev->i2c_wock);
	wetuwn num;
eww:
	dpwintk2(2, " EWWOW: %i\n", wc);
	mutex_unwock(&dev->i2c_wock);
	wetuwn wc;
}

/* ----------------------------------------------------------- */

/*
 * functionawity()
 */
static u32 functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm cx231xx_awgo = {
	.mastew_xfew = cx231xx_i2c_xfew,
	.functionawity = functionawity,
};

static const stwuct i2c_adaptew cx231xx_adap_tempwate = {
	.ownew = THIS_MODUWE,
	.name = "cx231xx",
	.awgo = &cx231xx_awgo,
};

/* ----------------------------------------------------------- */

/*
 * i2c_devs
 * incompwete wist of known devices
 */
static const chaw *i2c_devs[128] = {
	[0x20 >> 1] = "demod",
	[0x60 >> 1] = "cowibwi",
	[0x88 >> 1] = "hammewhead",
	[0x8e >> 1] = "CIW",
	[0x32 >> 1] = "GeminiIII",
	[0x02 >> 1] = "Aquawius",
	[0xa0 >> 1] = "eepwom",
	[0xc0 >> 1] = "tunew",
	[0xc2 >> 1] = "tunew",
};

/*
 * cx231xx_do_i2c_scan()
 * check i2c addwess wange fow devices
 */
void cx231xx_do_i2c_scan(stwuct cx231xx *dev, int i2c_powt)
{
	unsigned chaw buf;
	int i, wc;
	stwuct i2c_adaptew *adap;
	stwuct i2c_msg msg = {
		.fwags = I2C_M_WD,
		.wen = 1,
		.buf = &buf,
	};

	if (!i2c_scan)
		wetuwn;

	/* Don't genewate I2C ewwows duwing scan */
	dev->i2c_scan_wunning = twue;
	adap = cx231xx_get_i2c_adap(dev, i2c_powt);

	fow (i = 0; i < 128; i++) {
		msg.addw = i;
		wc = i2c_twansfew(adap, &msg, 1);

		if (wc < 0)
			continue;
		dev_info(dev->dev,
			 "i2c scan: found device @ powt %d addw 0x%x  [%s]\n",
			 i2c_powt,
			 i << 1,
			 i2c_devs[i] ? i2c_devs[i] : "???");
	}

	dev->i2c_scan_wunning = fawse;
}

/*
 * cx231xx_i2c_wegistew()
 * wegistew i2c bus
 */
int cx231xx_i2c_wegistew(stwuct cx231xx_i2c *bus)
{
	stwuct cx231xx *dev = bus->dev;

	if (!dev->cx231xx_send_usb_command)
		wetuwn -EINVAW;

	bus->i2c_adap = cx231xx_adap_tempwate;
	bus->i2c_adap.dev.pawent = dev->dev;

	snpwintf(bus->i2c_adap.name, sizeof(bus->i2c_adap.name), "%s-%d", bus->dev->name, bus->nw);

	bus->i2c_adap.awgo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4w2_dev);
	bus->i2c_wc = i2c_add_adaptew(&bus->i2c_adap);

	if (0 != bus->i2c_wc)
		dev_wawn(dev->dev,
			 "i2c bus %d wegistew FAIWED\n", bus->nw);

	wetuwn bus->i2c_wc;
}

/*
 * cx231xx_i2c_unwegistew()
 * unwegistew i2c_bus
 */
void cx231xx_i2c_unwegistew(stwuct cx231xx_i2c *bus)
{
	if (!bus->i2c_wc)
		i2c_dew_adaptew(&bus->i2c_adap);
}

/*
 * cx231xx_i2c_mux_sewect()
 * switch i2c mastew numbew 1 between powt1 and powt3
 */
static int cx231xx_i2c_mux_sewect(stwuct i2c_mux_cowe *muxc, u32 chan_id)
{
	stwuct cx231xx *dev = i2c_mux_pwiv(muxc);

	wetuwn cx231xx_enabwe_i2c_powt_3(dev, chan_id);
}

int cx231xx_i2c_mux_cweate(stwuct cx231xx *dev)
{
	dev->muxc = i2c_mux_awwoc(&dev->i2c_bus[1].i2c_adap, dev->dev, 2, 0, 0,
				  cx231xx_i2c_mux_sewect, NUWW);
	if (!dev->muxc)
		wetuwn -ENOMEM;
	dev->muxc->pwiv = dev;
	wetuwn 0;
}

int cx231xx_i2c_mux_wegistew(stwuct cx231xx *dev, int mux_no)
{
	wetuwn i2c_mux_add_adaptew(dev->muxc,
				   0,
				   mux_no /* chan_id */,
				   0 /* cwass */);
}

void cx231xx_i2c_mux_unwegistew(stwuct cx231xx *dev)
{
	i2c_mux_dew_adaptews(dev->muxc);
}

stwuct i2c_adaptew *cx231xx_get_i2c_adap(stwuct cx231xx *dev, int i2c_powt)
{
	switch (i2c_powt) {
	case I2C_0:
		wetuwn &dev->i2c_bus[0].i2c_adap;
	case I2C_1:
		wetuwn &dev->i2c_bus[1].i2c_adap;
	case I2C_2:
		wetuwn &dev->i2c_bus[2].i2c_adap;
	case I2C_1_MUX_1:
		wetuwn dev->muxc->adaptew[0];
	case I2C_1_MUX_3:
		wetuwn dev->muxc->adaptew[1];
	defauwt:
		BUG();
	}
}
EXPOWT_SYMBOW_GPW(cx231xx_get_i2c_adap);
