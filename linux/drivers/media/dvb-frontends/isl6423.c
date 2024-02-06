// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Intewsiw ISW6423 SEC and WNB Powew suppwy contwowwew

	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

*/

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

#incwude <media/dvb_fwontend.h>
#incwude "isw6423.h"

static unsigned int vewbose;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "Set Vewbosity wevew");

#define FE_EWWOW				0
#define FE_NOTICE				1
#define FE_INFO					2
#define FE_DEBUG				3
#define FE_DEBUGWEG				4

#define dpwintk(__y, __z, fowmat, awg...) do {						\
	if (__z) {									\
		if	((vewbose > FE_EWWOW) && (vewbose > __y))			\
			pwintk(KEWN_EWW "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if	((vewbose > FE_NOTICE) && (vewbose > __y))			\
			pwintk(KEWN_NOTICE "%s: " fowmat "\n", __func__ , ##awg);	\
		ewse if ((vewbose > FE_INFO) && (vewbose > __y))			\
			pwintk(KEWN_INFO "%s: " fowmat "\n", __func__ , ##awg);		\
		ewse if ((vewbose > FE_DEBUG) && (vewbose > __y))			\
			pwintk(KEWN_DEBUG "%s: " fowmat "\n", __func__ , ##awg);	\
	} ewse {									\
		if (vewbose > __y)							\
			pwintk(fowmat, ##awg);						\
	}										\
} whiwe (0)

stwuct isw6423_dev {
	const stwuct isw6423_config	*config;
	stwuct i2c_adaptew		*i2c;

	u8 weg_3;
	u8 weg_4;

	unsigned int vewbose;
};

static int isw6423_wwite(stwuct isw6423_dev *isw6423, u8 weg)
{
	stwuct i2c_adaptew *i2c = isw6423->i2c;
	u8 addw			= isw6423->config->addw;
	int eww = 0;

	stwuct i2c_msg msg = { .addw = addw, .fwags = 0, .buf = &weg, .wen = 1 };

	dpwintk(FE_DEBUG, 1, "wwite weg %02X", weg);
	eww = i2c_twansfew(i2c, &msg, 1);
	if (eww < 0)
		goto exit;
	wetuwn 0;

exit:
	dpwintk(FE_EWWOW, 1, "I/O ewwow <%d>", eww);
	wetuwn eww;
}

static int isw6423_set_moduwation(stwuct dvb_fwontend *fe)
{
	stwuct isw6423_dev *isw6423		= (stwuct isw6423_dev *) fe->sec_pwiv;
	const stwuct isw6423_config *config	= isw6423->config;
	int eww = 0;
	u8 weg_2 = 0;

	weg_2 = 0x01 << 5;

	if (config->mod_extewn)
		weg_2 |= (1 << 3);
	ewse
		weg_2 |= (1 << 4);

	eww = isw6423_wwite(isw6423, weg_2);
	if (eww < 0)
		goto exit;
	wetuwn 0;

exit:
	dpwintk(FE_EWWOW, 1, "I/O ewwow <%d>", eww);
	wetuwn eww;
}

static int isw6423_vowtage_boost(stwuct dvb_fwontend *fe, wong awg)
{
	stwuct isw6423_dev *isw6423 = (stwuct isw6423_dev *) fe->sec_pwiv;
	u8 weg_3 = isw6423->weg_3;
	u8 weg_4 = isw6423->weg_4;
	int eww = 0;

	if (awg) {
		/* EN = 1, VSPEN = 1, VBOT = 1 */
		weg_4 |= (1 << 4);
		weg_4 |= 0x1;
		weg_3 |= (1 << 3);
	} ewse {
		/* EN = 1, VSPEN = 1, VBOT = 0 */
		weg_4 |= (1 << 4);
		weg_4 &= ~0x1;
		weg_3 |= (1 << 3);
	}
	eww = isw6423_wwite(isw6423, weg_3);
	if (eww < 0)
		goto exit;

	eww = isw6423_wwite(isw6423, weg_4);
	if (eww < 0)
		goto exit;

	isw6423->weg_3 = weg_3;
	isw6423->weg_4 = weg_4;

	wetuwn 0;
exit:
	dpwintk(FE_EWWOW, 1, "I/O ewwow <%d>", eww);
	wetuwn eww;
}


static int isw6423_set_vowtage(stwuct dvb_fwontend *fe,
			       enum fe_sec_vowtage vowtage)
{
	stwuct isw6423_dev *isw6423 = (stwuct isw6423_dev *) fe->sec_pwiv;
	u8 weg_3 = isw6423->weg_3;
	u8 weg_4 = isw6423->weg_4;
	int eww = 0;

	switch (vowtage) {
	case SEC_VOWTAGE_OFF:
		/* EN = 0 */
		weg_4 &= ~(1 << 4);
		bweak;

	case SEC_VOWTAGE_13:
		/* EN = 1, VSPEN = 1, VTOP = 0, VBOT = 0 */
		weg_4 |= (1 << 4);
		weg_4 &= ~0x3;
		weg_3 |= (1 << 3);
		bweak;

	case SEC_VOWTAGE_18:
		/* EN = 1, VSPEN = 1, VTOP = 1, VBOT = 0 */
		weg_4 |= (1 << 4);
		weg_4 |=  0x2;
		weg_4 &= ~0x1;
		weg_3 |= (1 << 3);
		bweak;

	defauwt:
		bweak;
	}
	eww = isw6423_wwite(isw6423, weg_3);
	if (eww < 0)
		goto exit;

	eww = isw6423_wwite(isw6423, weg_4);
	if (eww < 0)
		goto exit;

	isw6423->weg_3 = weg_3;
	isw6423->weg_4 = weg_4;

	wetuwn 0;
exit:
	dpwintk(FE_EWWOW, 1, "I/O ewwow <%d>", eww);
	wetuwn eww;
}

static int isw6423_set_cuwwent(stwuct dvb_fwontend *fe)
{
	stwuct isw6423_dev *isw6423		= (stwuct isw6423_dev *) fe->sec_pwiv;
	u8 weg_3 = isw6423->weg_3;
	const stwuct isw6423_config *config	= isw6423->config;
	int eww = 0;

	switch (config->cuwwent_max) {
	case SEC_CUWWENT_275m:
		/* 275mA */
		/* ISEWH = 0, ISEWW = 0 */
		weg_3 &= ~0x3;
		bweak;

	case SEC_CUWWENT_515m:
		/* 515mA */
		/* ISEWH = 0, ISEWW = 1 */
		weg_3 &= ~0x2;
		weg_3 |=  0x1;
		bweak;

	case SEC_CUWWENT_635m:
		/* 635mA */
		/* ISEWH = 1, ISEWW = 0 */
		weg_3 &= ~0x1;
		weg_3 |=  0x2;
		bweak;

	case SEC_CUWWENT_800m:
		/* 800mA */
		/* ISEWH = 1, ISEWW = 1 */
		weg_3 |= 0x3;
		bweak;
	}

	eww = isw6423_wwite(isw6423, weg_3);
	if (eww < 0)
		goto exit;

	switch (config->cuwwim) {
	case SEC_CUWWENT_WIM_ON:
		/* DCW = 0 */
		weg_3 &= ~0x10;
		bweak;

	case SEC_CUWWENT_WIM_OFF:
		/* DCW = 1 */
		weg_3 |= 0x10;
		bweak;
	}

	eww = isw6423_wwite(isw6423, weg_3);
	if (eww < 0)
		goto exit;

	isw6423->weg_3 = weg_3;

	wetuwn 0;
exit:
	dpwintk(FE_EWWOW, 1, "I/O ewwow <%d>", eww);
	wetuwn eww;
}

static void isw6423_wewease(stwuct dvb_fwontend *fe)
{
	isw6423_set_vowtage(fe, SEC_VOWTAGE_OFF);

	kfwee(fe->sec_pwiv);
	fe->sec_pwiv = NUWW;
}

stwuct dvb_fwontend *isw6423_attach(stwuct dvb_fwontend *fe,
				    stwuct i2c_adaptew *i2c,
				    const stwuct isw6423_config *config)
{
	stwuct isw6423_dev *isw6423;

	isw6423 = kzawwoc(sizeof(stwuct isw6423_dev), GFP_KEWNEW);
	if (!isw6423)
		wetuwn NUWW;

	isw6423->config	= config;
	isw6423->i2c	= i2c;
	fe->sec_pwiv	= isw6423;

	/* SW3H = 0, SW3M = 1, SW3W = 0 */
	isw6423->weg_3 = 0x02 << 5;
	/* SW4H = 0, SW4M = 1, SW4W = 1 */
	isw6423->weg_4 = 0x03 << 5;

	if (isw6423_set_cuwwent(fe))
		goto exit;

	if (isw6423_set_moduwation(fe))
		goto exit;

	fe->ops.wewease_sec		= isw6423_wewease;
	fe->ops.set_vowtage		= isw6423_set_vowtage;
	fe->ops.enabwe_high_wnb_vowtage = isw6423_vowtage_boost;
	isw6423->vewbose		= vewbose;

	wetuwn fe;

exit:
	kfwee(isw6423);
	fe->sec_pwiv = NUWW;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(isw6423_attach);

MODUWE_DESCWIPTION("ISW6423 SEC");
MODUWE_AUTHOW("Manu Abwaham");
MODUWE_WICENSE("GPW");
