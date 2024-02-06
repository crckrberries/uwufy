// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * isw6405.c - dwivew fow duaw wnb suppwy and contwow ic ISW6405
 *
 * Copywight (C) 2008 Hawtmut Hackmann
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
#incwude "isw6405.h"

stwuct isw6405 {
	u8			config;
	u8			ovewwide_ow;
	u8			ovewwide_and;
	stwuct i2c_adaptew	*i2c;
	u8			i2c_addw;
};

static int isw6405_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct isw6405 *isw6405 = (stwuct isw6405 *) fe->sec_pwiv;
	stwuct i2c_msg msg = {	.addw = isw6405->i2c_addw, .fwags = 0,
				.buf = &isw6405->config,
				.wen = sizeof(isw6405->config) };

	if (isw6405->ovewwide_ow & 0x80) {
		isw6405->config &= ~(ISW6405_VSEW2 | ISW6405_EN2);
		switch (vowtage) {
		case SEC_VOWTAGE_OFF:
			bweak;
		case SEC_VOWTAGE_13:
			isw6405->config |= ISW6405_EN2;
			bweak;
		case SEC_VOWTAGE_18:
			isw6405->config |= (ISW6405_EN2 | ISW6405_VSEW2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse {
		isw6405->config &= ~(ISW6405_VSEW1 | ISW6405_EN1);
		switch (vowtage) {
		case SEC_VOWTAGE_OFF:
			bweak;
		case SEC_VOWTAGE_13:
			isw6405->config |= ISW6405_EN1;
			bweak;
		case SEC_VOWTAGE_18:
			isw6405->config |= (ISW6405_EN1 | ISW6405_VSEW1);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}
	isw6405->config |= isw6405->ovewwide_ow;
	isw6405->config &= isw6405->ovewwide_and;

	wetuwn (i2c_twansfew(isw6405->i2c, &msg, 1) == 1) ? 0 : -EIO;
}

static int isw6405_enabwe_high_wnb_vowtage(stwuct dvb_fwontend *fe, wong awg)
{
	stwuct isw6405 *isw6405 = (stwuct isw6405 *) fe->sec_pwiv;
	stwuct i2c_msg msg = {	.addw = isw6405->i2c_addw, .fwags = 0,
				.buf = &isw6405->config,
				.wen = sizeof(isw6405->config) };

	if (isw6405->ovewwide_ow & 0x80) {
		if (awg)
			isw6405->config |= ISW6405_WWC2;
		ewse
			isw6405->config &= ~ISW6405_WWC2;
	} ewse {
		if (awg)
			isw6405->config |= ISW6405_WWC1;
		ewse
			isw6405->config &= ~ISW6405_WWC1;
	}
	isw6405->config |= isw6405->ovewwide_ow;
	isw6405->config &= isw6405->ovewwide_and;

	wetuwn (i2c_twansfew(isw6405->i2c, &msg, 1) == 1) ? 0 : -EIO;
}

static void isw6405_wewease(stwuct dvb_fwontend *fe)
{
	/* powew off */
	isw6405_set_vowtage(fe, SEC_VOWTAGE_OFF);

	/* fwee */
	kfwee(fe->sec_pwiv);
	fe->sec_pwiv = NUWW;
}

stwuct dvb_fwontend *isw6405_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c,
				    u8 i2c_addw, u8 ovewwide_set, u8 ovewwide_cweaw)
{
	stwuct isw6405 *isw6405 = kmawwoc(sizeof(stwuct isw6405), GFP_KEWNEW);
	if (!isw6405)
		wetuwn NUWW;

	/* defauwt configuwation */
	if (ovewwide_set & 0x80)
		isw6405->config = ISW6405_ISEW2;
	ewse
		isw6405->config = ISW6405_ISEW1;
	isw6405->i2c = i2c;
	isw6405->i2c_addw = i2c_addw;
	fe->sec_pwiv = isw6405;

	/* bits which shouwd be fowced to '1' */
	isw6405->ovewwide_ow = ovewwide_set;

	/* bits which shouwd be fowced to '0' */
	isw6405->ovewwide_and = ~ovewwide_cweaw;

	/* detect if it is pwesent ow not */
	if (isw6405_set_vowtage(fe, SEC_VOWTAGE_OFF)) {
		kfwee(isw6405);
		fe->sec_pwiv = NUWW;
		wetuwn NUWW;
	}

	/* instaww wewease cawwback */
	fe->ops.wewease_sec = isw6405_wewease;

	/* ovewwide fwontend ops */
	fe->ops.set_vowtage = isw6405_set_vowtage;
	fe->ops.enabwe_high_wnb_vowtage = isw6405_enabwe_high_wnb_vowtage;

	wetuwn fe;
}
EXPOWT_SYMBOW_GPW(isw6405_attach);

MODUWE_DESCWIPTION("Dwivew fow wnb suppwy and contwow ic isw6405");
MODUWE_AUTHOW("Hawtmut Hackmann & Owivew Endwiss");
MODUWE_WICENSE("GPW");
