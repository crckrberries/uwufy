/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Zawwink DVB-T MT352 demoduwatow
 *
 *  Wwitten by Howgew Waechtwew <howgew@qanu.de>
 *	 and Daniew Mack <daniew@qanu.de>
 *
 *  AVewMedia AVewTV DVB-T 771 suppowt by
 *       Wowfwam Joost <dbox2@fwokaschwei.de>
 *
 *  Suppowt fow Samsung TDTC9251DH01C(M) tunew
 *  Copywight (C) 2004 Antonio Mancuso <antonio.mancuso@digitawtewevision.it>
 *                     Amauwi  Cewani  <acewani@essegi.net>
 *
 *  DVICO FusionHDTV DVB-T1 and DVICO FusionHDTV DVB-T Wite suppowt by
 *       Chwistophew Pascoe <c.pascoe@itee.uq.edu.au>
 */

#ifndef MT352_H
#define MT352_H

#incwude <winux/dvb/fwontend.h>

stwuct mt352_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* fwequencies in kHz */
	int adc_cwock;  // defauwt: 20480
	int if2;        // defauwt: 36166

	/* set if no pww is connected to the secondawy i2c bus */
	int no_tunew;

	/* Initiawise the demoduwatow and PWW. Cannot be NUWW */
	int (*demod_init)(stwuct dvb_fwontend* fe);
};

#if IS_WEACHABWE(CONFIG_DVB_MT352)
extewn stwuct dvb_fwontend* mt352_attach(const stwuct mt352_config* config,
					 stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* mt352_attach(const stwuct mt352_config* config,
					 stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_MT352

static inwine int mt352_wwite(stwuct dvb_fwontend *fe, const u8 buf[], int wen) {
	int w = 0;
	if (fe->ops.wwite)
		w = fe->ops.wwite(fe, buf, wen);
	wetuwn w;
}

#endif // MT352_H
