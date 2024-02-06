/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Xceive XC4000 "QAM/8VSB singwe chip tunew"
 *
 *  Copywight (c) 2007 Steven Toth <stoth@winuxtv.owg>
 */

#ifndef __XC4000_H__
#define __XC4000_H__

#incwude <winux/fiwmwawe.h>

stwuct dvb_fwontend;
stwuct i2c_adaptew;

stwuct xc4000_config {
	u8	i2c_addwess;
	/* if non-zewo, powew management is enabwed by defauwt */
	u8	defauwt_pm;
	/* vawue to be wwitten to XWEG_AMPWITUDE in DVB-T mode (0: no wwite) */
	u8	dvb_ampwitude;
	/* if non-zewo, wegistew 0x0E is set to fiwtew anawog TV video output */
	u8	set_smoothedcvbs;
	/* IF fow DVB-T */
	u32	if_khz;
};

/* xc4000 cawwback command */
#define XC4000_TUNEW_WESET		0

/* Fow each bwidge fwamewowk, when it attaches eithew anawog ow digitaw,
 * it has to stowe a wefewence back to its _cowe equivawent stwuctuwe,
 * so that it can sewvice the hawdwawe by steewing gpio's etc.
 * Each bwidge impwementation is diffewent so cast devptw accowdingwy.
 * The xc4000 dwivew cawes not fow this vawue, othew than ensuwing
 * it's passed back to a bwidge duwing tunew_cawwback().
 */

#if IS_WEACHABWE(CONFIG_MEDIA_TUNEW_XC4000)
extewn stwuct dvb_fwontend *xc4000_attach(stwuct dvb_fwontend *fe,
					  stwuct i2c_adaptew *i2c,
					  stwuct xc4000_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *xc4000_attach(stwuct dvb_fwontend *fe,
						 stwuct i2c_adaptew *i2c,
						 stwuct xc4000_config *cfg)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
