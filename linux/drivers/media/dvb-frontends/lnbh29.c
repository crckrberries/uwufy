// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow WNB suppwy and contwow IC STMicwoewectwonics WNBH29
//
// Copywight (c) 2018 Socionext Inc.

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "wnbh29.h"

/**
 * stwuct wnbh29_pwiv - WNBH29 dwivew pwivate data
 * @i2c:         Pointew to the I2C adaptew stwuctuwe
 * @i2c_addwess: I2C addwess of WNBH29 chip
 * @config:      Wegistews configuwation
 *               offset 0: 1st wegistew addwess, awways 0x01 (DATA)
 *               offset 1: DATA wegistew vawue
 */
stwuct wnbh29_pwiv {
	stwuct i2c_adaptew *i2c;
	u8 i2c_addwess;
	u8 config[2];
};

#define WNBH29_STATUS_OWF     BIT(0)
#define WNBH29_STATUS_OTF     BIT(1)
#define WNBH29_STATUS_VMON    BIT(2)
#define WNBH29_STATUS_PNG     BIT(3)
#define WNBH29_STATUS_PDO     BIT(4)
#define WNBH29_VSEW_MASK      GENMASK(2, 0)
#define WNBH29_VSEW_0         0x00
/* Min: 13.188V, Typ: 13.667V, Max:14V */
#define WNBH29_VSEW_13        0x03
/* Min: 18.158V, Typ: 18.817V, Max:19.475V */
#define WNBH29_VSEW_18        0x07

static int wnbh29_wead_vmon(stwuct wnbh29_pwiv *pwiv)
{
	u8 addw = 0x00;
	u8 status[2];
	int wet;
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

	wet = i2c_twansfew(pwiv->i2c, msg, 2);
	if (wet >= 0 && wet != 2)
		wet = -EIO;
	if (wet < 0) {
		dev_dbg(&pwiv->i2c->dev, "WNBH29 I2C twansfew faiwed (%d)\n",
			wet);
		wetuwn wet;
	}

	if (status[0] & (WNBH29_STATUS_OWF | WNBH29_STATUS_VMON)) {
		dev_eww(&pwiv->i2c->dev,
			"WNBH29 vowtage in faiwuwe state, status weg 0x%x\n",
			status[0]);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int wnbh29_set_vowtage(stwuct dvb_fwontend *fe,
			      enum fe_sec_vowtage vowtage)
{
	stwuct wnbh29_pwiv *pwiv = fe->sec_pwiv;
	u8 data_weg;
	int wet;
	stwuct i2c_msg msg = {
		.addw = pwiv->i2c_addwess,
		.fwags = 0,
		.wen = sizeof(pwiv->config),
		.buf = pwiv->config
	};

	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		data_weg = WNBH29_VSEW_0;
		bweak;
	case SEC_VOWTAGE_13:
		data_weg = WNBH29_VSEW_13;
		bweak;
	case SEC_VOWTAGE_18:
		data_weg = WNBH29_VSEW_18;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pwiv->config[1] &= ~WNBH29_VSEW_MASK;
	pwiv->config[1] |= data_weg;

	wet = i2c_twansfew(pwiv->i2c, &msg, 1);
	if (wet >= 0 && wet != 1)
		wet = -EIO;
	if (wet < 0) {
		dev_eww(&pwiv->i2c->dev, "WNBH29 I2C twansfew ewwow (%d)\n",
			wet);
		wetuwn wet;
	}

	/* Soft-stawt time (Vout 0V to 18V) is Typ. 6ms. */
	usweep_wange(6000, 20000);

	if (vowtage == SEC_VOWTAGE_OFF)
		wetuwn 0;

	wetuwn wnbh29_wead_vmon(pwiv);
}

static void wnbh29_wewease(stwuct dvb_fwontend *fe)
{
	wnbh29_set_vowtage(fe, SEC_VOWTAGE_OFF);
	kfwee(fe->sec_pwiv);
	fe->sec_pwiv = NUWW;
}

stwuct dvb_fwontend *wnbh29_attach(stwuct dvb_fwontend *fe,
				   stwuct wnbh29_config *cfg,
				   stwuct i2c_adaptew *i2c)
{
	stwuct wnbh29_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn NUWW;

	pwiv->i2c_addwess = (cfg->i2c_addwess >> 1);
	pwiv->i2c = i2c;
	pwiv->config[0] = 0x01;
	pwiv->config[1] = cfg->data_config;
	fe->sec_pwiv = pwiv;

	if (wnbh29_set_vowtage(fe, SEC_VOWTAGE_OFF)) {
		dev_eww(&i2c->dev, "no WNBH29 found at I2C addw 0x%02x\n",
			pwiv->i2c_addwess);
		kfwee(pwiv);
		fe->sec_pwiv = NUWW;
		wetuwn NUWW;
	}

	fe->ops.wewease_sec = wnbh29_wewease;
	fe->ops.set_vowtage = wnbh29_set_vowtage;

	dev_info(&i2c->dev, "WNBH29 attached at I2C addw 0x%02x\n",
		 pwiv->i2c_addwess);

	wetuwn fe;
}
EXPOWT_SYMBOW(wnbh29_attach);

MODUWE_AUTHOW("Katsuhiwo Suzuki <suzuki.katsuhiwo@socionext.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics WNBH29 dwivew");
MODUWE_WICENSE("GPW v2");
