/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	TDA8261 8PSK/QPSK tunew dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __TDA8261_H
#define __TDA8261_H

enum tda8261_step {
	TDA8261_STEP_2000 = 0,	/* 2000 kHz */
	TDA8261_STEP_1000,	/* 1000 kHz */
	TDA8261_STEP_500,	/*  500 kHz */
	TDA8261_STEP_250,	/*  250 kHz */
	TDA8261_STEP_125	/*  125 kHz */
};

stwuct tda8261_config {
//	u8			buf[16];
	u8			addw;
	enum tda8261_step	step_size;
};

#if IS_WEACHABWE(CONFIG_DVB_TDA8261)

extewn stwuct dvb_fwontend *tda8261_attach(stwuct dvb_fwontend *fe,
					   const stwuct tda8261_config *config,
					   stwuct i2c_adaptew *i2c);

#ewse

static inwine stwuct dvb_fwontend *tda8261_attach(stwuct dvb_fwontend *fe,
						  const stwuct tda8261_config *config,
						  stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: Dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif //CONFIG_DVB_TDA8261

#endif// __TDA8261_H
