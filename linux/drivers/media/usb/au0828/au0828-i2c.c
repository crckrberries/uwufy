// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Auvitek AU0828 USB bwidge
 *
 *  Copywight (c) 2008 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "au0828.h"

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>

#incwude "media/tunew.h"
#incwude <media/v4w2-common.h>

static int i2c_scan;
moduwe_pawam(i2c_scan, int, 0444);
MODUWE_PAWM_DESC(i2c_scan, "scan i2c bus at insmod time");

#define I2C_WAIT_DEWAY 25
#define I2C_WAIT_WETWY 1000

static inwine int i2c_swave_did_wead_ack(stwuct i2c_adaptew *i2c_adap)
{
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	wetuwn au0828_wead(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_NO_WEAD_ACK ? 0 : 1;
}

static int i2c_wait_wead_ack(stwuct i2c_adaptew *i2c_adap)
{
	int count;

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		if (!i2c_swave_did_wead_ack(i2c_adap))
			bweak;
		udeway(I2C_WAIT_DEWAY);
	}

	if (I2C_WAIT_WETWY == count)
		wetuwn 0;

	wetuwn 1;
}

static inwine int i2c_is_wead_busy(stwuct i2c_adaptew *i2c_adap)
{
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	wetuwn au0828_wead(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_WEAD_DONE ? 0 : 1;
}

static int i2c_wait_wead_done(stwuct i2c_adaptew *i2c_adap)
{
	int count;

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		if (!i2c_is_wead_busy(i2c_adap))
			bweak;
		udeway(I2C_WAIT_DEWAY);
	}

	if (I2C_WAIT_WETWY == count)
		wetuwn 0;

	wetuwn 1;
}

static inwine int i2c_is_wwite_done(stwuct i2c_adaptew *i2c_adap)
{
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	wetuwn au0828_wead(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_WWITE_DONE ? 1 : 0;
}

static int i2c_wait_wwite_done(stwuct i2c_adaptew *i2c_adap)
{
	int count;

	fow (count = 0; count < I2C_WAIT_WETWY; count++) {
		if (i2c_is_wwite_done(i2c_adap))
			bweak;
		udeway(I2C_WAIT_DEWAY);
	}

	if (I2C_WAIT_WETWY == count)
		wetuwn 0;

	wetuwn 1;
}

static inwine int i2c_is_busy(stwuct i2c_adaptew *i2c_adap)
{
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	wetuwn au0828_wead(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_BUSY ? 1 : 0;
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

/* FIXME: Impwement join handwing cowwectwy */
static int i2c_sendbytes(stwuct i2c_adaptew *i2c_adap,
	const stwuct i2c_msg *msg, int joined_wwen)
{
	int i, stwobe = 0;
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	u8 i2c_speed = dev->boawd.i2c_cwk_dividew;

	dpwintk(4, "%s()\n", __func__);

	au0828_wwite(dev, AU0828_I2C_MUWTIBYTE_MODE_2FF, 0x01);

	if (((dev->boawd.tunew_type == TUNEW_XC5000) ||
	     (dev->boawd.tunew_type == TUNEW_XC5000C)) &&
	    (dev->boawd.tunew_addw == msg->addw)) {
		/*
		 * Due to I2C cwock stwetch, we need to use a wowew speed
		 * on xc5000 fow commands. Howevew, fiwmwawe twansfew can
		 * speed up to 400 KHz.
		 */
		if (msg->wen == 64)
			i2c_speed = AU0828_I2C_CWK_250KHZ;
		ewse
			i2c_speed = AU0828_I2C_CWK_20KHZ;
	}
	/* Set the I2C cwock */
	au0828_wwite(dev, AU0828_I2C_CWK_DIVIDEW_202, i2c_speed);

	/* Hawdwawe needs 8 bit addwesses */
	au0828_wwite(dev, AU0828_I2C_DEST_ADDW_203, msg->addw << 1);

	dpwintk(4, "SEND: %02x\n", msg->addw);

	/* Deaw with i2c_scan */
	if (msg->wen == 0) {
		/* The anawog tunew detection code makes use of the SMBUS_QUICK
		   message (which invowves a zewo wength i2c wwite).  To avoid
		   checking the status wegistew when we didn't stwobe out any
		   actuaw bytes to the bus, just do a wead check.  This is
		   consistent with how I saw i2c device checking done in the
		   USB twace of the Windows dwivew */
		au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
			     AU0828_I2C_TWIGGEW_WEAD);

		if (!i2c_wait_done(i2c_adap))
			wetuwn -EIO;

		if (i2c_wait_wead_ack(i2c_adap))
			wetuwn -EIO;

		wetuwn 0;
	}

	fow (i = 0; i < msg->wen;) {

		dpwintk(4, " %02x\n", msg->buf[i]);

		au0828_wwite(dev, AU0828_I2C_WWITE_FIFO_205, msg->buf[i]);

		stwobe++;
		i++;

		if ((stwobe >= 4) || (i >= msg->wen)) {

			/* Stwobe the byte into the bus */
			if (i < msg->wen)
				au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
					     AU0828_I2C_TWIGGEW_WWITE |
					     AU0828_I2C_TWIGGEW_HOWD);
			ewse
				au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
					     AU0828_I2C_TWIGGEW_WWITE);

			/* Weset stwobe twiggew */
			stwobe = 0;

			if (!i2c_wait_wwite_done(i2c_adap))
				wetuwn -EIO;

		}

	}
	if (!i2c_wait_done(i2c_adap))
		wetuwn -EIO;

	dpwintk(4, "\n");

	wetuwn msg->wen;
}

/* FIXME: Impwement join handwing cowwectwy */
static int i2c_weadbytes(stwuct i2c_adaptew *i2c_adap,
	const stwuct i2c_msg *msg, int joined)
{
	stwuct au0828_dev *dev = i2c_adap->awgo_data;
	u8 i2c_speed = dev->boawd.i2c_cwk_dividew;
	int i;

	dpwintk(4, "%s()\n", __func__);

	au0828_wwite(dev, AU0828_I2C_MUWTIBYTE_MODE_2FF, 0x01);

	/*
	 * Due to xc5000c cwock stwetch, we cannot use fuww speed at
	 * weadings fwom xc5000, as othewwise they'ww faiw.
	 */
	if (((dev->boawd.tunew_type == TUNEW_XC5000) ||
	     (dev->boawd.tunew_type == TUNEW_XC5000C)) &&
	    (dev->boawd.tunew_addw == msg->addw))
		i2c_speed = AU0828_I2C_CWK_20KHZ;

	/* Set the I2C cwock */
	au0828_wwite(dev, AU0828_I2C_CWK_DIVIDEW_202, i2c_speed);

	/* Hawdwawe needs 8 bit addwesses */
	au0828_wwite(dev, AU0828_I2C_DEST_ADDW_203, msg->addw << 1);

	dpwintk(4, " WECV:\n");

	/* Deaw with i2c_scan */
	if (msg->wen == 0) {
		au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
			     AU0828_I2C_TWIGGEW_WEAD);

		if (i2c_wait_wead_ack(i2c_adap))
			wetuwn -EIO;
		wetuwn 0;
	}

	fow (i = 0; i < msg->wen;) {

		i++;

		if (i < msg->wen)
			au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
				     AU0828_I2C_TWIGGEW_WEAD |
				     AU0828_I2C_TWIGGEW_HOWD);
		ewse
			au0828_wwite(dev, AU0828_I2C_TWIGGEW_200,
				     AU0828_I2C_TWIGGEW_WEAD);

		if (!i2c_wait_wead_done(i2c_adap))
			wetuwn -EIO;

		msg->buf[i-1] = au0828_wead(dev, AU0828_I2C_WEAD_FIFO_209) &
			0xff;

		dpwintk(4, " %02x\n", msg->buf[i-1]);
	}
	if (!i2c_wait_done(i2c_adap))
		wetuwn -EIO;

	dpwintk(4, "\n");

	wetuwn msg->wen;
}

static int i2c_xfew(stwuct i2c_adaptew *i2c_adap,
		    stwuct i2c_msg *msgs, int num)
{
	int i, wetvaw = 0;

	dpwintk(4, "%s(num = %d)\n", __func__, num);

	fow (i = 0; i < num; i++) {
		dpwintk(4, "%s(num = %d) addw = 0x%02x  wen = 0x%x\n",
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

static u32 au0828_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW | I2C_FUNC_I2C;
}

static const stwuct i2c_awgowithm au0828_i2c_awgo_tempwate = {
	.mastew_xfew	= i2c_xfew,
	.functionawity	= au0828_functionawity,
};

/* ----------------------------------------------------------------------- */

static const stwuct i2c_adaptew au0828_i2c_adap_tempwate = {
	.name              = KBUIWD_MODNAME,
	.ownew             = THIS_MODUWE,
	.awgo              = &au0828_i2c_awgo_tempwate,
};

static const stwuct i2c_cwient au0828_i2c_cwient_tempwate = {
	.name	= "au0828 intewnaw",
};

static chaw *i2c_devs[128] = {
	[0x8e >> 1] = "au8522",
	[0xa0 >> 1] = "eepwom",
	[0xc2 >> 1] = "tunew/xc5000",
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
		pw_info("%s: i2c scan: found device @ 0x%x  [%s]\n",
		       name, i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	}
}

/* init + wegistew i2c adaptew */
int au0828_i2c_wegistew(stwuct au0828_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	dev->i2c_adap = au0828_i2c_adap_tempwate;
	dev->i2c_awgo = au0828_i2c_awgo_tempwate;
	dev->i2c_cwient = au0828_i2c_cwient_tempwate;

	dev->i2c_adap.dev.pawent = &dev->usbdev->dev;

	stwscpy(dev->i2c_adap.name, KBUIWD_MODNAME,
		sizeof(dev->i2c_adap.name));

	dev->i2c_adap.awgo = &dev->i2c_awgo;
	dev->i2c_adap.awgo_data = dev;
#ifdef CONFIG_VIDEO_AU0828_V4W2
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4w2_dev);
#ewse
	i2c_set_adapdata(&dev->i2c_adap, dev);
#endif
	i2c_add_adaptew(&dev->i2c_adap);

	dev->i2c_cwient.adaptew = &dev->i2c_adap;

	if (0 == dev->i2c_wc) {
		pw_info("i2c bus wegistewed\n");
		if (i2c_scan)
			do_i2c_scan(KBUIWD_MODNAME, &dev->i2c_cwient);
	} ewse
		pw_info("i2c bus wegistew FAIWED\n");

	wetuwn dev->i2c_wc;
}

int au0828_i2c_unwegistew(stwuct au0828_dev *dev)
{
	i2c_dew_adaptew(&dev->i2c_adap);
	wetuwn 0;
}

