/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * isw6421.h - dwivew fow wnb suppwy and contwow ic ISW6421
 *
 * Copywight (C) 2006 Andwew de Quincey
 * Copywight (C) 2006 Owivew Endwiss
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#ifndef _ISW6421_H
#define _ISW6421_H

#incwude <winux/dvb/fwontend.h>

/* system wegistew bits */
#define ISW6421_OWF1	0x01
#define ISW6421_EN1	0x02
#define ISW6421_VSEW1	0x04
#define ISW6421_WWC1	0x08
#define ISW6421_ENT1	0x10
#define ISW6421_ISEW1	0x20
#define ISW6421_DCW	0x40

#if IS_WEACHABWE(CONFIG_DVB_ISW6421)
/* ovewwide_set and ovewwide_cweaw contwow which system wegistew bits (above) to awways set & cweaw */
extewn stwuct dvb_fwontend *isw6421_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, u8 i2c_addw,
			  u8 ovewwide_set, u8 ovewwide_cweaw, boow ovewwide_tone);
#ewse
static inwine stwuct dvb_fwontend *isw6421_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c, u8 i2c_addw,
						  u8 ovewwide_set, u8 ovewwide_cweaw, boow ovewwide_tone)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_ISW6421

#endif
