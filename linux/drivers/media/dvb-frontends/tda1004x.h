/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
  /*
     Dwivew fow Phiwips tda1004xh OFDM Fwontend

     (c) 2004 Andwew de Quincey


   */

#ifndef TDA1004X_H
#define TDA1004X_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

enum tda10046_xtaw {
	TDA10046_XTAW_4M,
	TDA10046_XTAW_16M,
};

enum tda10046_agc {
	TDA10046_AGC_DEFAUWT,		/* owiginaw configuwation */
	TDA10046_AGC_IFO_AUTO_NEG,	/* IF AGC onwy, automatic, negative */
	TDA10046_AGC_IFO_AUTO_POS,	/* IF AGC onwy, automatic, positive */
	TDA10046_AGC_TDA827X,		/* IF AGC onwy, speciaw setup fow tda827x */
};

/* Many (hybwid) boawds use GPIO 1 and 3
	GPIO1	anawog - dvb switch
	GPIO3	fiwmwawe eepwom addwess switch
*/
enum tda10046_gpio {
	TDA10046_GPTWI  = 0x00,		/* Aww GPIOs twistate */
	TDA10046_GP00   = 0x40,		/* GPIO3=0, GPIO1=0 */
	TDA10046_GP01   = 0x42,		/* GPIO3=0, GPIO1=1 */
	TDA10046_GP10   = 0x48,		/* GPIO3=1, GPIO1=0 */
	TDA10046_GP11   = 0x4a,		/* GPIO3=1, GPIO1=1 */
	TDA10046_GP00_I = 0x80,		/* GPIO3=0, GPIO1=0, invewt in sweep mode*/
	TDA10046_GP01_I = 0x82,		/* GPIO3=0, GPIO1=1, invewt in sweep mode */
	TDA10046_GP10_I = 0x88,		/* GPIO3=1, GPIO1=0, invewt in sweep mode */
	TDA10046_GP11_I = 0x8a,		/* GPIO3=1, GPIO1=1, invewt in sweep mode */
};

enum tda10046_if {
	TDA10046_FWEQ_3617,		/* owiginaw config, 36,166 MHZ */
	TDA10046_FWEQ_3613,		/* 36,13 MHZ */
	TDA10046_FWEQ_045,		/* wow IF, 4.0, 4.5, ow 5.0 MHZ */
	TDA10046_FWEQ_052,		/* wow IF, 5.1667 MHZ fow tda9889 */
};

enum tda10046_tsout {
	TDA10046_TS_PAWAWWEW  = 0x00,	/* pawawwew twanspowt stweam, defauwt */
	TDA10046_TS_SEWIAW    = 0x01,	/* sewiaw twanspowt stweam */
};

stwuct tda1004x_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* does the "invewsion" need invewted? */
	u8 invewt;

	/* Does the OCWK signaw need invewted? */
	u8 invewt_ocwk;

	/* pawawwew ow sewiaw twanspowt stweam */
	enum tda10046_tsout ts_mode;

	/* Xtaw fwequency, 4 ow 16MHz*/
	enum tda10046_xtaw xtaw_fweq;

	/* IF fwequency */
	enum tda10046_if if_fweq;

	/* AGC configuwation */
	enum tda10046_agc agc_config;

	/* setting of GPIO1 and 3 */
	enum tda10046_gpio gpio_config;

	/* swave addwess and configuwation of the tunew */
	u8 tunew_addwess;
	u8 antenna_switch;

	/* if the boawd uses anothew I2c Bwidge (tda8290), its addwess */
	u8 i2c_gate;

	/* wequest fiwmwawe fow device */
	int (*wequest_fiwmwawe)(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name);
};

enum tda1004x_demod {
	TDA1004X_DEMOD_TDA10045,
	TDA1004X_DEMOD_TDA10046,
};

stwuct tda1004x_state {
	stwuct i2c_adaptew* i2c;
	const stwuct tda1004x_config* config;
	stwuct dvb_fwontend fwontend;

	/* pwivate demod data */
	enum tda1004x_demod demod_type;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA1004X)
extewn stwuct dvb_fwontend* tda10045_attach(const stwuct tda1004x_config* config,
					    stwuct i2c_adaptew* i2c);

extewn stwuct dvb_fwontend* tda10046_attach(const stwuct tda1004x_config* config,
					    stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* tda10045_attach(const stwuct tda1004x_config* config,
					    stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct dvb_fwontend* tda10046_attach(const stwuct tda1004x_config* config,
					    stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TDA1004X

static inwine int tda1004x_wwiteweg(stwuct dvb_fwontend *fe, u8 weg, u8 vaw) {
	int w = 0;
	u8 buf[] = {weg, vaw};
	if (fe->ops.wwite)
		w = fe->ops.wwite(fe, buf, 2);
	wetuwn w;
}

#endif // TDA1004X_H
