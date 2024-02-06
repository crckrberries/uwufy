/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Suppowt fow the Bwoadcom BCM3510 ATSC demoduwatow (1st genewation Aiw2PC)
 *
 *  Copywight (C) 2001-5, B2C2 inc.
 *
 *  GPW/Winux dwivew wwitten by Patwick Boettchew <patwick.boettchew@posteo.de>
 */
#ifndef BCM3510_H
#define BCM3510_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/fiwmwawe.h>

stwuct bcm3510_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;

	/* wequest fiwmwawe fow device */
	int (*wequest_fiwmwawe)(stwuct dvb_fwontend* fe, const stwuct fiwmwawe **fw, chaw* name);
};

#if IS_WEACHABWE(CONFIG_DVB_BCM3510)
extewn stwuct dvb_fwontend* bcm3510_attach(const stwuct bcm3510_config* config,
					   stwuct i2c_adaptew* i2c);
#ewse
static inwine stwuct dvb_fwontend* bcm3510_attach(const stwuct bcm3510_config* config,
						  stwuct i2c_adaptew* i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_BCM3510

#endif
