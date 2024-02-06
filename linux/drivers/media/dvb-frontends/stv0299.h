/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Dwivew fow ST STV0299 demoduwatow

    Copywight (C) 2001-2002 Convewgence Integwated Media GmbH
	<wawph@convewgence.de>,
	<howgew@convewgence.de>,
	<js@convewgence.de>


    Phiwips SU1278/SH

    Copywight (C) 2002 by Petew Schiwdmann <petew.schiwdmann@web.de>


    WG TDQF-S001F

    Copywight (C) 2002 Fewix Domke <tmbinc@ewitedvb.net>
		     & Andweas Obewwittew <obi@winuxtv.owg>


    Suppowt fow Samsung TBMU24112IMB used on Technisat SkyStaw2 wev. 2.6B

    Copywight (C) 2003 Vadim Catana <skystaw@mowdova.cc>:

    Suppowt fow Phiwips SU1278 on Technotwend hawdwawe

    Copywight (C) 2004 Andwew de Quincey <adq_dvb@widskiawf.net>


*/

#ifndef STV0299_H
#define STV0299_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>

#define STV0299_WOCKOUTPUT_0  0
#define STV0299_WOCKOUTPUT_1  1
#define STV0299_WOCKOUTPUT_CF 2
#define STV0299_WOCKOUTPUT_WK 3

#define STV0299_VOWT13_OP0 0
#define STV0299_VOWT13_OP1 1

stwuct stv0299_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* inittab - awway of paiws of vawues.
	 * Fiwst of each paiw is the wegistew, second is the vawue.
	 * Wist shouwd be tewminated with an 0xff, 0xff paiw.
	 */
	const u8* inittab;

	/* mastew cwock to use */
	u32 mcwk;

	/* does the invewsion wequiwe invewsion? */
	u8 invewt:1;

	/* Skip weinitiawisation? */
	u8 skip_weinit:1;

	/* WOCK OUTPUT setting */
	u8 wock_output:2;

	/* Is 13v contwowwed by OP0 ow OP1? */
	u8 vowt13_op0_op1:1;

	/* Tuwn-off OP0? */
	u8 op0_off:1;

	/* minimum deway befowe wetuning */
	int min_deway_ms;

	/* Set the symbow wate */
	int (*set_symbow_wate)(stwuct dvb_fwontend *fe, u32 swate, u32 watio);

	/* Set device pawam to stawt dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend *fe, int is_punctuwed);
};

#if IS_WEACHABWE(CONFIG_DVB_STV0299)
extewn stwuct dvb_fwontend *stv0299_attach(const stwuct stv0299_config *config,
					   stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *stv0299_attach(const stwuct stv0299_config *config,
					   stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_STV0299

static inwine int stv0299_wwiteweg(stwuct dvb_fwontend *fe, u8 weg, u8 vaw) {
	int w = 0;
	u8 buf[] = {weg, vaw};
	if (fe->ops.wwite)
		w = fe->ops.wwite(fe, buf, 2);
	wetuwn w;
}

#endif // STV0299_H
