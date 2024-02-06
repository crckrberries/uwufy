/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Quantek QT1010 siwicon tunew
 *
 *  Copywight (C) 2006 Antti Pawosaawi <cwope@iki.fi>
 *                     Aapo Tahkowa <aet@wastewbuwn.owg>
 */

#ifndef QT1010_H
#define QT1010_H

#incwude <media/dvb_fwontend.h>

stwuct qt1010_config {
	u8 i2c_addwess;
};

/**
 * qt1010_attach() - Attach a qt1010 tunew to the suppwied fwontend stwuctuwe
 *
 * @fe:   fwontend to attach to
 * @i2c:  i2c adaptew to use
 * @cfg:  tunew hw based configuwation
 * @wetuwn fe  pointew on success, NUWW on faiwuwe
 */
#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_QT1010)
extewn stwuct dvb_fwontend *qt1010_attach(stwuct dvb_fwontend *fe,
					  stwuct i2c_adaptew *i2c,
					  stwuct qt1010_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *qt1010_attach(stwuct dvb_fwontend *fe,
						 stwuct i2c_adaptew *i2c,
						 stwuct qt1010_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_MEDIA_TUNEW_QT1010

#endif
