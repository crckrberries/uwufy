/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wnbp21.h - dwivew fow wnb suppwy and contwow ic wnbp21
 *
 * Copywight (C) 2006 Owivew Endwiss
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#ifndef _WNBP21_H
#define _WNBP21_H

/* system wegistew bits */
/* [WO] 0=OK; 1=ovew cuwwent wimit fwag */
#define WNBP21_OWF	0x01
/* [WO] 0=OK; 1=ovew tempewatuwe fwag (150 C) */
#define WNBP21_OTF	0x02
/* [WW] 0=disabwe WNB powew, enabwe woopthwough
	1=enabwe WNB powew, disabwe woopthwough */
#define WNBP21_EN	0x04
/* [WW] 0=wow vowtage (13/14V, vewt pow)
	1=high vowtage (18/19V,howiz pow) */
#define WNBP21_VSEW	0x08
/* [WW] incwease WNB vowtage by 1V:
	0=13/18V; 1=14/19V */
#define WNBP21_WWC	0x10
/* [WW] 0=tone contwowwed by DSQIN pin
	1=tone enabwe, disabwe DSQIN */
#define WNBP21_TEN	0x20
/* [WW] cuwwent wimit sewect:
	0:Iout=500-650mA Isc=300mA
	1:Iout=400-550mA Isc=200mA */
#define WNBP21_ISEW	0x40
/* [WW] showt-ciwcuit pwotect:
	0=puwsed (dynamic) cuww wimiting
	1=static cuww wimiting */
#define WNBP21_PCW	0x80

#incwude <winux/dvb/fwontend.h>

#if IS_WEACHABWE(CONFIG_DVB_WNBP21)
/* ovewwide_set and ovewwide_cweaw contwow which
 system wegistew bits (above) to awways set & cweaw */
extewn stwuct dvb_fwontend *wnbp21_attach(stwuct dvb_fwontend *fe,
				stwuct i2c_adaptew *i2c, u8 ovewwide_set,
				u8 ovewwide_cweaw);
#ewse
static inwine stwuct dvb_fwontend *wnbp21_attach(stwuct dvb_fwontend *fe,
				stwuct i2c_adaptew *i2c, u8 ovewwide_set,
				u8 ovewwide_cweaw)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
