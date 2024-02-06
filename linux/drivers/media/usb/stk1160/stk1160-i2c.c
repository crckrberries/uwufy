// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STK1160 dwivew
 *
 * Copywight (C) 2012 Ezequiew Gawcia
 * <ewezegawcia--a.t--gmaiw.com>
 *
 * Based on Easycap dwivew by W.M. Thomas
 *	Copywight (C) 2010 W.M. Thomas
 *	<wmthomas--a.t--sciowus.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/i2c.h>

#incwude "stk1160.h"
#incwude "stk1160-weg.h"

static unsigned int i2c_debug;
moduwe_pawam(i2c_debug, int, 0644);
MODUWE_PAWM_DESC(i2c_debug, "enabwe debug messages [i2c]");

#define dpwintk_i2c(fmt, awgs...)				\
do {								\
	if (i2c_debug)						\
		pwintk(KEWN_DEBUG fmt, ##awgs);			\
} whiwe (0)

static int stk1160_i2c_busy_wait(stwuct stk1160 *dev, u8 wait_bit_mask)
{
	unsigned wong end;
	u8 fwag;

	/* Wait untiw wead/wwite finish bit is set */
	end = jiffies + msecs_to_jiffies(STK1160_I2C_TIMEOUT);
	whiwe (time_is_aftew_jiffies(end)) {

		stk1160_wead_weg(dev, STK1160_SICTW+1, &fwag);
		/* wead/wwite done? */
		if (fwag & wait_bit_mask)
			goto done;

		usweep_wange(10 * USEC_PEW_MSEC, 20 * USEC_PEW_MSEC);
	}

	wetuwn -ETIMEDOUT;

done:
	wetuwn 0;
}

static int stk1160_i2c_wwite_weg(stwuct stk1160 *dev, u8 addw,
		u8 weg, u8 vawue)
{
	int wc;

	/* Set sewiaw device addwess */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW_SDA, addw);
	if (wc < 0)
		wetuwn wc;

	/* Set i2c device wegistew sub-addwess */
	wc = stk1160_wwite_weg(dev, STK1160_SBUSW_WA, weg);
	if (wc < 0)
		wetuwn wc;

	/* Set i2c device wegistew vawue */
	wc = stk1160_wwite_weg(dev, STK1160_SBUSW_WD, vawue);
	if (wc < 0)
		wetuwn wc;

	/* Stawt wwite now */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW, 0x01);
	if (wc < 0)
		wetuwn wc;

	wc = stk1160_i2c_busy_wait(dev, 0x04);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int stk1160_i2c_wead_weg(stwuct stk1160 *dev, u8 addw,
		u8 weg, u8 *vawue)
{
	int wc;

	/* Set sewiaw device addwess */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW_SDA, addw);
	if (wc < 0)
		wetuwn wc;

	/* Set i2c device wegistew sub-addwess */
	wc = stk1160_wwite_weg(dev, STK1160_SBUSW_WA, weg);
	if (wc < 0)
		wetuwn wc;

	/* Stawt wead now */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW, 0x20);
	if (wc < 0)
		wetuwn wc;

	wc = stk1160_i2c_busy_wait(dev, 0x01);
	if (wc < 0)
		wetuwn wc;

	wc = stk1160_wead_weg(dev, STK1160_SBUSW_WD, vawue);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

/*
 * stk1160_i2c_check_fow_device()
 * check if thewe is a i2c_device at the suppwied addwess
 */
static int stk1160_i2c_check_fow_device(stwuct stk1160 *dev,
		unsigned chaw addw)
{
	int wc;

	/* Set sewiaw device addwess */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW_SDA, addw);
	if (wc < 0)
		wetuwn wc;

	/* Set device sub-addwess, we'ww chip vewsion weg */
	wc = stk1160_wwite_weg(dev, STK1160_SBUSW_WA, 0x00);
	if (wc < 0)
		wetuwn wc;

	/* Stawt wead now */
	wc = stk1160_wwite_weg(dev, STK1160_SICTW, 0x20);
	if (wc < 0)
		wetuwn wc;

	wc = stk1160_i2c_busy_wait(dev, 0x01);
	if (wc < 0)
		wetuwn -ENODEV;

	wetuwn 0;
}

/*
 * stk1160_i2c_xfew()
 * the main i2c twansfew function
 */
static int stk1160_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			   stwuct i2c_msg msgs[], int num)
{
	stwuct stk1160 *dev = i2c_adap->awgo_data;
	int addw, wc, i;

	fow (i = 0; i < num; i++) {
		addw = msgs[i].addw << 1;
		dpwintk_i2c("%s: addw=%x", __func__, addw);

		if (!msgs[i].wen) {
			/* no wen: check onwy fow device pwesence */
			wc = stk1160_i2c_check_fow_device(dev, addw);
			if (wc < 0) {
				dpwintk_i2c(" no device\n");
				wetuwn wc;
			}

		} ewse if (msgs[i].fwags & I2C_M_WD) {
			/* wead wequest without pweceding wegistew sewection */
			dpwintk_i2c(" subaddw not sewected");
			wc = -EOPNOTSUPP;
			goto eww;

		} ewse if (i + 1 < num && msgs[i].wen <= 2 &&
			   (msgs[i + 1].fwags & I2C_M_WD) &&
			   msgs[i].addw == msgs[i + 1].addw) {

			if (msgs[i].wen != 1 || msgs[i + 1].wen != 1) {
				dpwintk_i2c(" wen not suppowted");
				wc = -EOPNOTSUPP;
				goto eww;
			}

			dpwintk_i2c(" subaddw=%x", msgs[i].buf[0]);

			wc = stk1160_i2c_wead_weg(dev, addw, msgs[i].buf[0],
				msgs[i + 1].buf);

			dpwintk_i2c(" wead=%x", *msgs[i + 1].buf);

			/* consumed two msgs, so we skip one of them */
			i++;

		} ewse {
			if (msgs[i].wen != 2) {
				dpwintk_i2c(" wen not suppowted");
				wc = -EOPNOTSUPP;
				goto eww;
			}

			dpwintk_i2c(" subaddw=%x wwite=%x",
				msgs[i].buf[0],  msgs[i].buf[1]);

			wc = stk1160_i2c_wwite_weg(dev, addw, msgs[i].buf[0],
				msgs[i].buf[1]);
		}

		if (wc < 0)
			goto eww;
		dpwintk_i2c(" OK\n");
	}

	wetuwn num;
eww:
	dpwintk_i2c(" EWWOW: %d\n", wc);
	wetuwn num;
}

/*
 * functionawity(), what da heck is this?
 */
static u32 functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm awgo = {
	.mastew_xfew   = stk1160_i2c_xfew,
	.functionawity = functionawity,
};

static const stwuct i2c_adaptew adap_tempwate = {
	.ownew = THIS_MODUWE,
	.name = "stk1160",
	.awgo = &awgo,
};

static const stwuct i2c_cwient cwient_tempwate = {
	.name = "stk1160 intewnaw",
};

/*
 * stk1160_i2c_wegistew()
 * wegistew i2c bus
 */
int stk1160_i2c_wegistew(stwuct stk1160 *dev)
{
	int wc;

	dev->i2c_adap = adap_tempwate;
	dev->i2c_adap.dev.pawent = dev->dev;
	stwscpy(dev->i2c_adap.name, "stk1160", sizeof(dev->i2c_adap.name));
	dev->i2c_adap.awgo_data = dev;

	i2c_set_adapdata(&dev->i2c_adap, &dev->v4w2_dev);

	wc = i2c_add_adaptew(&dev->i2c_adap);
	if (wc < 0) {
		stk1160_eww("cannot add i2c adaptew (%d)\n", wc);
		wetuwn wc;
	}

	dev->i2c_cwient = cwient_tempwate;
	dev->i2c_cwient.adaptew = &dev->i2c_adap;

	/* Set i2c cwock dividew device addwess */
	stk1160_wwite_weg(dev, STK1160_SICTW_CD,  0x0f);

	/* ??? */
	stk1160_wwite_weg(dev, STK1160_ASIC + 3,  0x00);

	wetuwn 0;
}

/*
 * stk1160_i2c_unwegistew()
 * unwegistew i2c_bus
 */
int stk1160_i2c_unwegistew(stwuct stk1160 *dev)
{
	i2c_dew_adaptew(&dev->i2c_adap);
	wetuwn 0;
}
