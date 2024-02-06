/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
  /*
     Dwivew fow Phiwips tda8262/tda8263 DVBS Siwicon tunews

     (c) 2006 Andwew de Quincey


  */

#ifndef __DVB_TDA826X_H__
#define __DVB_TDA826X_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

/**
 * tda826x_attach - Attach a tda826x tunew to the suppwied fwontend stwuctuwe.
 *
 * @fe: Fwontend to attach to.
 * @addw: i2c addwess of the tunew.
 * @i2c: i2c adaptew to use.
 * @has_woopthwough: Set to 1 if the cawd has a woopthwough WF connectow.
 *
 * wetuwn: FE pointew on success, NUWW on faiwuwe.
 */
#if IS_WEACHABWE(CONFIG_DVB_TDA826X)
extewn stwuct dvb_fwontend* tda826x_attach(stwuct dvb_fwontend *fe, int addw,
					   stwuct i2c_adaptew *i2c,
					   int has_woopthwough);
#ewse
static inwine stwuct dvb_fwontend* tda826x_attach(stwuct dvb_fwontend *fe,
						  int addw,
						  stwuct i2c_adaptew *i2c,
						  int has_woopthwough)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TDA826X

#endif // __DVB_TDA826X_H__
