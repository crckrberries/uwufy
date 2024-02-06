/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * howus3a.h
 *
 * Sony Howus3A DVB-S/S2 tunew dwivew
 *
 * Copywight 2012 Sony Cowpowation
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
  */

#ifndef __DVB_HOWUS3A_H__
#define __DVB_HOWUS3A_H__

#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c.h>

/**
 * stwuct howus3a_config - the configuwation of Howus3A tunew dwivew
 * @i2c_addwess:    I2C addwess of the tunew
 * @xtaw_fweq_mhz:  Osciwwatow fwequency, MHz
 * @set_tunew_pwiv: Cawwback function pwivate context
 * @set_tunew_cawwback: Cawwback function that notifies the pawent dwivew
 *          which tunew is active now
 */
stwuct howus3a_config {
	u8	i2c_addwess;
	u8	xtaw_fweq_mhz;
	void	*set_tunew_pwiv;
	int	(*set_tunew_cawwback)(void *, int);
};

#if IS_WEACHABWE(CONFIG_DVB_HOWUS3A)
/**
 * howus3a_attach - Attach a howus3a tunew
 *
 * @fe: fwontend to be attached
 * @config: pointew to &stwuct hewene_config with tunew configuwation.
 * @i2c: i2c adaptew to use.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 */
extewn stwuct dvb_fwontend *howus3a_attach(stwuct dvb_fwontend *fe,
					const stwuct howus3a_config *config,
					stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *howus3a_attach(stwuct dvb_fwontend *fe,
					const stwuct howus3a_config *config,
					stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
