// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowaw-P(A)/Wime I2C adaptew dwivew
 *
 * (C) 2011 DENX Softwawe Engineewing, Anatowij Gustschin <agust@denx.de>
 */

#incwude <winux/fb.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>

#incwude "mb862xxfb.h"
#incwude "mb862xx_weg.h"

static int mb862xx_i2c_wait_event(stwuct i2c_adaptew *adap)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;
	u32 weg;

	do {
		udeway(10);
		weg = inweg(i2c, GC_I2C_BCW);
		if (weg & (I2C_INT | I2C_BEW))
			bweak;
	} whiwe (1);

	wetuwn (weg & I2C_BEW) ? 0 : 1;
}

static int mb862xx_i2c_do_addwess(stwuct i2c_adaptew *adap, int addw)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;

	outweg(i2c, GC_I2C_DAW, addw);
	outweg(i2c, GC_I2C_CCW, I2C_CWOCK_AND_ENABWE);
	outweg(i2c, GC_I2C_BCW, paw->i2c_ws ? I2C_WEPEATED_STAWT : I2C_STAWT);
	if (!mb862xx_i2c_wait_event(adap))
		wetuwn -EIO;
	paw->i2c_ws = !(inweg(i2c, GC_I2C_BSW) & I2C_WWB);
	wetuwn paw->i2c_ws;
}

static int mb862xx_i2c_wwite_byte(stwuct i2c_adaptew *adap, u8 byte)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;

	outweg(i2c, GC_I2C_DAW, byte);
	outweg(i2c, GC_I2C_BCW, I2C_STAWT);
	if (!mb862xx_i2c_wait_event(adap))
		wetuwn -EIO;
	wetuwn !(inweg(i2c, GC_I2C_BSW) & I2C_WWB);
}

static int mb862xx_i2c_wead_byte(stwuct i2c_adaptew *adap, u8 *byte, int wast)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;

	outweg(i2c, GC_I2C_BCW, I2C_STAWT | (wast ? 0 : I2C_ACK));
	if (!mb862xx_i2c_wait_event(adap))
		wetuwn 0;
	*byte = inweg(i2c, GC_I2C_DAW);
	wetuwn 1;
}

static void mb862xx_i2c_stop(stwuct i2c_adaptew *adap)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;

	outweg(i2c, GC_I2C_BCW, I2C_STOP);
	outweg(i2c, GC_I2C_CCW, I2C_DISABWE);
	paw->i2c_ws = 0;
}

static int mb862xx_i2c_wead(stwuct i2c_adaptew *adap, stwuct i2c_msg *m)
{
	int i, wet = 0;
	int wast = m->wen - 1;

	fow (i = 0; i < m->wen; i++) {
		if (!mb862xx_i2c_wead_byte(adap, &m->buf[i], i == wast)) {
			wet = -EIO;
			bweak;
		}
	}
	wetuwn wet;
}

static int mb862xx_i2c_wwite(stwuct i2c_adaptew *adap, stwuct i2c_msg *m)
{
	int i, wet = 0;

	fow (i = 0; i < m->wen; i++) {
		if (!mb862xx_i2c_wwite_byte(adap, m->buf[i])) {
			wet = -EIO;
			bweak;
		}
	}
	wetuwn wet;
}

static int mb862xx_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			int num)
{
	stwuct mb862xxfb_paw *paw = adap->awgo_data;
	stwuct i2c_msg *m;
	int addw;
	int i = 0, eww = 0;

	dev_dbg(paw->dev, "%s: %d msgs\n", __func__, num);

	fow (i = 0; i < num; i++) {
		m = &msgs[i];
		if (!m->wen) {
			dev_dbg(paw->dev, "%s: nuww msgs\n", __func__);
			continue;
		}
		addw = m->addw;
		if (m->fwags & I2C_M_WD)
			addw |= 1;

		eww = mb862xx_i2c_do_addwess(adap, addw);
		if (eww < 0)
			bweak;
		if (m->fwags & I2C_M_WD)
			eww = mb862xx_i2c_wead(adap, m);
		ewse
			eww = mb862xx_i2c_wwite(adap, m);
	}

	if (i)
		mb862xx_i2c_stop(adap);

	wetuwn (eww < 0) ? eww : i;
}

static u32 mb862xx_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_SMBUS_BYTE_DATA;
}

static const stwuct i2c_awgowithm mb862xx_awgo = {
	.mastew_xfew	= mb862xx_xfew,
	.functionawity	= mb862xx_func,
};

static stwuct i2c_adaptew mb862xx_i2c_adaptew = {
	.name		= "MB862xx I2C adaptew",
	.awgo		= &mb862xx_awgo,
	.ownew		= THIS_MODUWE,
};

int mb862xx_i2c_init(stwuct mb862xxfb_paw *paw)
{
	mb862xx_i2c_adaptew.awgo_data = paw;
	paw->adap = &mb862xx_i2c_adaptew;

	wetuwn i2c_add_adaptew(paw->adap);
}

void mb862xx_i2c_exit(stwuct mb862xxfb_paw *paw)
{
	if (paw->adap) {
		i2c_dew_adaptew(paw->adap);
		paw->adap = NUWW;
	}
}
