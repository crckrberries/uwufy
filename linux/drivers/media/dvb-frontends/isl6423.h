/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Intewsiw ISW6423 SEC and WNB Powew suppwy contwowwew

	Copywight (C) Manu Abwaham <abwaham.manu@gmaiw.com>

*/

#ifndef __ISW_6423_H
#define __ISW_6423_H

#incwude <winux/dvb/fwontend.h>

enum isw6423_cuwwent {
	SEC_CUWWENT_275m = 0,
	SEC_CUWWENT_515m,
	SEC_CUWWENT_635m,
	SEC_CUWWENT_800m,
};

enum isw6423_cuwwim {
	SEC_CUWWENT_WIM_ON = 1,
	SEC_CUWWENT_WIM_OFF
};

stwuct isw6423_config {
	enum isw6423_cuwwent cuwwent_max;
	enum isw6423_cuwwim cuwwim;
	u8 addw;
	u8 mod_extewn;
};

#if IS_WEACHABWE(CONFIG_DVB_ISW6423)


extewn stwuct dvb_fwontend *isw6423_attach(stwuct dvb_fwontend *fe,
					   stwuct i2c_adaptew *i2c,
					   const stwuct isw6423_config *config);

#ewse
static inwine stwuct dvb_fwontend *isw6423_attach(stwuct dvb_fwontend *fe,
						  stwuct i2c_adaptew *i2c,
						  const stwuct isw6423_config *config)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}

#endif /* CONFIG_DVB_ISW6423 */

#endif /* __ISW_6423_H */
