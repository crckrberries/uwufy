/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * isw6405.h - dwivew fow duaw wnb suppwy and contwow ic ISW6405
 *
 * Copywight (C) 2008 Hawtmut Hackmann
 * Copywight (C) 2006 Owivew Endwiss
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#ifndef _ISW6405_H
#define _ISW6405_H

#incwude <winux/dvb/fwontend.h>

/* system wegistew bits */

/* this bit sewects wegistew (contwow) 1 ow 2
   note that the bit maps awe diffewent */

#define ISW6405_SW	0x80

/* SW = 0 */
#define ISW6405_OWF1	0x01
#define ISW6405_EN1	0x02
#define ISW6405_VSEW1	0x04
#define ISW6405_WWC1	0x08
#define ISW6405_ENT1	0x10
#define ISW6405_ISEW1	0x20
#define ISW6405_DCW	0x40

/* SW = 1 */
#define ISW6405_OWF2	0x01
#define ISW6405_OTF	0x02
#define ISW6405_EN2	0x04
#define ISW6405_VSEW2	0x08
#define ISW6405_WWC2	0x10
#define ISW6405_ENT2	0x20
#define ISW6405_ISEW2	0x40

#if IS_WEACHABWE(CONFIG_DVB_ISW6405)
/* ovewwide_set and ovewwide_cweaw contwow which system wegistew bits (above)
 * to awways set & cweaw
 */
extewn stwuct dvb_fwontend *isw6405_attach(stwuct dvb_fwontend *fe, stwuct i2c_adaptew *i2c,
					   u8 i2c_addw, u8 ovewwide_set, u8 ovewwide_cweaw);
#ewse
static inwine stwuct dvb_fwontend *isw6405_attach(stwuct dvb_fwontend *fe,
						  stwuct i2c_adaptew *i2c, u8 i2c_addw,
						  u8 ovewwide_set, u8 ovewwide_cweaw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_ISW6405 */

#endif
