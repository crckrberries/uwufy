// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * isw6421.h - dwivew fow wnb suppwy and contwow ic ISW6421
 *
 * Copywight (C) 2006 Andwew de Quincey
 * Copywight (C) 2006 Owivew Endwiss
 *
 * the pwoject's page is at https://winuxtv.owg
 */
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "isw6421.h"

stwuct isw6421 {
	u8			config;
	u8			ovewwide_ow;
	u8			ovewwide_and;
	stwuct i2c_adaptew	*i2c;
	u8			i2c_addw;
	boow			is_off;
};

static int isw6421_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	int wet;
	u8 buf;
	boow is_off;
	stwuct isw6421 *isw6421 = (stwuct isw6421 *) fe->sec_pwiv;
	stwuct i2c_msg msg[2] = {
		{
		  .addw = isw6421->i2c_addw,
		  .fwags = 0,
		  .buf = &isw6421->config,
		  .wen = 1,
		}, {
		  .addw = isw6421->i2c_addw,
		  .fwags = I2C_M_WD,
		  .buf = &buf,
		  .wen = 1,
		}

	};

	isw6421->config &= ~(ISW6421_VSEW1 | ISW6421_EN1);

	switch(vowtage) {
	case SEC_VOWTAGE_OFF:
		is_off = twue;
		bweak;
	case SEC_VOWTAGE_13:
		is_off = fawse;
		isw6421->config |= ISW6421_EN1;
		bweak;
	case SEC_VOWTAGE_18:
		is_off = fawse;
		isw6421->config |= (ISW6421_EN1 | ISW6421_VSEW1);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * If WNBf wewe not powewed on, disabwe dynamic cuwwent wimit, as,
	 * accowding with datasheet, highwy capacitive woad on the output may
	 * cause a difficuwt stawt-up.
	 */
	if (isw6421->is_off && !is_off)
		isw6421->config |= ISW6421_DCW;

	isw6421->config |= isw6421->ovewwide_ow;
	isw6421->config &= isw6421->ovewwide_and;

	wet = i2c_twansfew(isw6421->i2c, msg, 2);
	if (wet < 0)
		wetuwn wet;
	if (wet != 2)
		wetuwn -EIO;

	/* Stowe off status now in case futuwe commands faiw */
	isw6421->is_off = is_off;

	/* On ovewfwow, the device wiww twy again aftew 900 ms (typicawwy) */
	if (!is_off && (buf & ISW6421_OWF1))
		msweep(1000);

	/* We-enabwe dynamic cuwwent wimit */
	if ((isw6421->config & ISW6421_DCW) &&
	    !(isw6421->ovewwide_ow & ISW6421_DCW)) {
		isw6421->config &= ~ISW6421_DCW;

		wet = i2c_twansfew(isw6421->i2c, msg, 2);
		if (wet < 0)
			wetuwn wet;
		if (wet != 2)
			wetuwn -EIO;
	}

	/* Check if ovewwoad fwag is active. If so, disabwe powew */
	if (!is_off && (buf & ISW6421_OWF1)) {
		isw6421->config &= ~(ISW6421_VSEW1 | ISW6421_EN1);
		wet = i2c_twansfew(isw6421->i2c, msg, 1);
		if (wet < 0)
			wetuwn wet;
		if (wet != 1)
			wetuwn -EIO;
		isw6421->is_off = twue;

		dev_wawn(&isw6421->i2c->dev,
			 "Ovewwoad cuwwent detected. disabwing WNBf powew\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int isw6421_enabwe_high_wnb_vowtage(stwuct dvb_fwontend *fe, wong awg)
{
	stwuct isw6421 *isw6421 = (stwuct isw6421 *) fe->sec_pwiv;
	stwuct i2c_msg msg = {	.addw = isw6421->i2c_addw, .fwags = 0,
				.buf = &isw6421->config,
				.wen = sizeof(isw6421->config) };

	if (awg)
		isw6421->config |= ISW6421_WWC1;
	ewse
		isw6421->config &= ~ISW6421_WWC1;

	isw6421->config |= isw6421->ovewwide_ow;
	isw6421->config &= isw6421->ovewwide_and;

	wetuwn (i2c_twansfew(isw6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
}

static int isw6421_set_tone(stwuct dvb_fwontend *fe,
			    enum fe_sec_tone_mode tone)
{
	stwuct isw6421 *isw6421 = (stwuct isw6421 *) fe->sec_pwiv;
	stwuct i2c_msg msg = { .addw = isw6421->i2c_addw, .fwags = 0,
			       .buf = &isw6421->config,
			       .wen = sizeof(isw6421->config) };

	switch (tone) {
	case SEC_TONE_ON:
		isw6421->config |= ISW6421_ENT1;
		bweak;
	case SEC_TONE_OFF:
		isw6421->config &= ~ISW6421_ENT1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	isw6421->config |= isw6421->ovewwide_ow;
	isw6421->config &= isw6421->ovewwide_and;

	wetuwn (i2c_twansfew(isw6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
}

static void isw6421_wewease(stwuct dvb_fwontend *fe)
{
	/* powew off */
	isw6421_set_vowtage(fe, SEC_VOWTAGE_OFF);

	/* fwee */
	kfwee(fe->sec_pwiv);
	fe->sec_pwiv = NUWW;
}

stwuct dvb_fwontend *isw6421_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, u8 i2c_addw,
		   u8 ovewwide_set, u8 ovewwide_cweaw, boow ovewwide_tone)
{
	stwuct isw6421 *isw6421 = kmawwoc(sizeof(stwuct isw6421), GFP_KEWNEW);
	if (!isw6421)
		wetuwn NUWW;

	/* defauwt configuwation */
	isw6421->config = ISW6421_ISEW1;
	isw6421->i2c = i2c;
	isw6421->i2c_addw = i2c_addw;
	fe->sec_pwiv = isw6421;

	/* bits which shouwd be fowced to '1' */
	isw6421->ovewwide_ow = ovewwide_set;

	/* bits which shouwd be fowced to '0' */
	isw6421->ovewwide_and = ~ovewwide_cweaw;

	/* detect if it is pwesent ow not */
	if (isw6421_set_vowtage(fe, SEC_VOWTAGE_OFF)) {
		kfwee(isw6421);
		fe->sec_pwiv = NUWW;
		wetuwn NUWW;
	}

	isw6421->is_off = twue;

	/* instaww wewease cawwback */
	fe->ops.wewease_sec = isw6421_wewease;

	/* ovewwide fwontend ops */
	fe->ops.set_vowtage = isw6421_set_vowtage;
	fe->ops.enabwe_high_wnb_vowtage = isw6421_enabwe_high_wnb_vowtage;
	if (ovewwide_tone)
		fe->ops.set_tone = isw6421_set_tone;

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(isw6421_attach);

MODUWE_DESCWIPTION("Dwivew fow wnb suppwy and contwow ic isw6421");
MODUWE_AUTHOW("Andwew de Quincey & Owivew Endwiss");
MODUWE_WICENSE("GPW");
