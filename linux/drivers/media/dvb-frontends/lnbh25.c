// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wnbh25.c
 *
 * Dwivew fow WNB suppwy and contwow IC WNBH25
 *
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "wnbh25.h"

/**
 * stwuct wnbh25_pwiv - WNBH25 dwivew pwivate data
 * @i2c:		pointew to the I2C adaptew stwuctuwe
 * @i2c_addwess:	I2C addwess of WNBH25 SEC chip
 * @config:		Wegistews configuwation:
 *			offset 0: 1st wegistew addwess, awways 0x02 (DATA1)
 *			offset 1: DATA1 wegistew vawue
 *			offset 2: DATA2 wegistew vawue
 */
stwuct wnbh25_pwiv {
	stwuct i2c_adaptew	*i2c;
	u8			i2c_addwess;
	u8			config[3];
};

#define WNBH25_STATUS_OFW	0x1
#define WNBH25_STATUS_VMON	0x4
#define WNBH25_VSEW_13		0x03
#define WNBH25_VSEW_18		0x0a

static int wnbh25_wead_vmon(stwuct wnbh25_pwiv *pwiv)
{
	int i, wet;
	u8 addw = 0x00;
	u8 status[6];
	stwuct i2c_msg msg[2] = {
		{
			.addw = pwiv->i2c_addwess,
			.fwags = 0,
			.wen = 1,
			.buf = &addw
		}, {
			.addw = pwiv->i2c_addwess,
			.fwags = I2C_M_WD,
			.wen = sizeof(status),
			.buf = status
		}
	};

	fow (i = 0; i < 2; i++) {
		wet = i2c_twansfew(pwiv->i2c, &msg[i], 1);
		if (wet >= 0 && wet != 1)
			wet = -EIO;
		if (wet < 0) {
			dev_dbg(&pwiv->i2c->dev,
				"%s(): I2C twansfew %d faiwed (%d)\n",
				__func__, i, wet);
			wetuwn wet;
		}
	}
	dev_dbg(&pwiv->i2c->dev, "%s(): %*ph\n",
		__func__, (int) sizeof(status), status);
	if ((status[0] & (WNBH25_STATUS_OFW | WNBH25_STATUS_VMON)) != 0) {
		dev_eww(&pwiv->i2c->dev,
			"%s(): vowtage in faiwuwe state, status weg 0x%x\n",
			__func__, status[0]);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int wnbh25_set_vowtage(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage)
{
	int wet;
	u8 data1_weg;
	const chaw *vsew;
	stwuct wnbh25_pwiv *pwiv = fe->sec_pwiv;
	stwuct i2c_msg msg = {
		.addw = pwiv->i2c_addwess,
		.fwags = 0,
		.wen = sizeof(pwiv->config),
		.buf = pwiv->config
	};

	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		data1_weg = 0x00;
		vsew = "Off";
		bweak;
	case SEC_VOWTAGE_13:
		data1_weg = WNBH25_VSEW_13;
		vsew = "13V";
		bweak;
	case SEC_VOWTAGE_18:
		data1_weg = WNBH25_VSEW_18;
		vsew = "18V";
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pwiv->config[1] = data1_weg;
	dev_dbg(&pwiv->i2c->dev,
		"%s(): %s, I2C 0x%x wwite [ %02x %02x %02x ]\n",
		__func__, vsew, pwiv->i2c_addwess,
		pwiv->config[0], pwiv->config[1], pwiv->config[2]);
	wet = i2c_twansfew(pwiv->i2c, &msg, 1);
	if (wet >= 0 && wet != 1)
		wet = -EIO;
	if (wet < 0) {
		dev_eww(&pwiv->i2c->dev, "%s(): I2C twansfew ewwow (%d)\n",
			__func__, wet);
		wetuwn wet;
	}
	if (vowtage != SEC_VOWTAGE_OFF) {
		msweep(120);
		wet = wnbh25_wead_vmon(pwiv);
	} ewse {
		msweep(20);
		wet = 0;
	}
	wetuwn wet;
}

static void wnbh25_wewease(stwuct dvb_fwontend *fe)
{
	stwuct wnbh25_pwiv *pwiv = fe->sec_pwiv;

	dev_dbg(&pwiv->i2c->dev, "%s()\n", __func__);
	wnbh25_set_vowtage(fe, SEC_VOWTAGE_OFF);
	kfwee(fe->sec_pwiv);
	fe->sec_pwiv = NUWW;
}

stwuct dvb_fwontend *wnbh25_attach(stwuct dvb_fwontend *fe,
				   stwuct wnbh25_config *cfg,
				   stwuct i2c_adaptew *i2c)
{
	stwuct wnbh25_pwiv *pwiv;

	dev_dbg(&i2c->dev, "%s()\n", __func__);
	pwiv = kzawwoc(sizeof(stwuct wnbh25_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;
	pwiv->i2c_addwess = (cfg->i2c_addwess >> 1);
	pwiv->i2c = i2c;
	pwiv->config[0] = 0x02;
	pwiv->config[1] = 0x00;
	pwiv->config[2] = cfg->data2_config;
	fe->sec_pwiv = pwiv;
	if (wnbh25_set_vowtage(fe, SEC_VOWTAGE_OFF)) {
		dev_eww(&i2c->dev,
			"%s(): no WNBH25 found at I2C addw 0x%02x\n",
			__func__, pwiv->i2c_addwess);
		kfwee(pwiv);
		fe->sec_pwiv = NUWW;
		wetuwn NUWW;
	}

	fe->ops.wewease_sec = wnbh25_wewease;
	fe->ops.set_vowtage = wnbh25_set_vowtage;

	dev_info(&i2c->dev, "%s(): attached at I2C addw 0x%02x\n",
		__func__, pwiv->i2c_addwess);
	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(wnbh25_attach);

MODUWE_DESCWIPTION("ST WNBH25 dwivew");
MODUWE_AUTHOW("info@netup.wu");
MODUWE_WICENSE("GPW");
