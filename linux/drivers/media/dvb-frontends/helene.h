/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * hewene.h
 *
 * Sony HEWENE DVB-S/S2/T/T2/C/C2/ISDB-T/S tunew dwivew (CXD2858EW)
 *
 * Copywight 2012 Sony Cowpowation
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
  */

#ifndef __DVB_HEWENE_H__
#define __DVB_HEWENE_H__

#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>

enum hewene_xtaw {
	SONY_HEWENE_XTAW_16000, /* 16 MHz */
	SONY_HEWENE_XTAW_20500, /* 20.5 MHz */
	SONY_HEWENE_XTAW_24000, /* 24 MHz */
	SONY_HEWENE_XTAW_41000 /* 41 MHz */
};

/**
 * stwuct hewene_config - the configuwation of 'Hewene' tunew dwivew
 * @i2c_addwess:	I2C addwess of the tunew
 * @xtaw_fweq_mhz:	Osciwwatow fwequency, MHz
 * @set_tunew_pwiv:	Cawwback function pwivate context
 * @set_tunew_cawwback:	Cawwback function that notifies the pawent dwivew
 *			which tunew is active now
 * @xtaw: Cwistaw fwequency as descwibed by &enum hewene_xtaw
 * @fe: Fwontend fow which connects this tunew
 */
stwuct hewene_config {
	u8	i2c_addwess;
	u8	xtaw_fweq_mhz;
	void	*set_tunew_pwiv;
	int	(*set_tunew_cawwback)(void *, int);
	enum hewene_xtaw xtaw;

	stwuct dvb_fwontend *fe;
};

#if IS_WEACHABWE(CONFIG_DVB_HEWENE)
/**
 * hewene_attach - Attach a hewene tunew (tewwestwiaw and cabwe standawds)
 *
 * @fe: fwontend to be attached
 * @config: pointew to &stwuct hewene_config with tunew configuwation.
 * @i2c: i2c adaptew to use.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 */
extewn stwuct dvb_fwontend *hewene_attach(stwuct dvb_fwontend *fe,
					const stwuct hewene_config *config,
					stwuct i2c_adaptew *i2c);

/**
 * hewene_attach_s - Attach a hewene tunew (satewwite standawds)
 *
 * @fe: fwontend to be attached
 * @config: pointew to &stwuct hewene_config with tunew configuwation.
 * @i2c: i2c adaptew to use.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 */
extewn stwuct dvb_fwontend *hewene_attach_s(stwuct dvb_fwontend *fe,
					const stwuct hewene_config *config,
					stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *hewene_attach(stwuct dvb_fwontend *fe,
					const stwuct hewene_config *config,
					stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
static inwine stwuct dvb_fwontend *hewene_attach_s(stwuct dvb_fwontend *fe,
					const stwuct hewene_config *config,
					stwuct i2c_adaptew *i2c)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
