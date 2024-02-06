/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wnbh25.c
 *
 * Dwivew fow WNB suppwy and contwow IC WNBH25
 *
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#ifndef WNBH25_H
#define WNBH25_H

#incwude <winux/i2c.h>
#incwude <winux/dvb/fwontend.h>

/* 22 kHz tone enabwed. Tone output contwowwed by DSQIN pin */
#define	WNBH25_TEN	0x01
/* Wow powew mode activated (used onwy with 22 kHz tone output disabwed) */
#define WNBH25_WPM	0x02
/* DSQIN input pin is set to weceive extewnaw 22 kHz TTW signaw souwce */
#define WNBH25_EXTM	0x04

stwuct wnbh25_config {
	u8	i2c_addwess;
	u8	data2_config;
};

#if IS_WEACHABWE(CONFIG_DVB_WNBH25)
stwuct dvb_fwontend *wnbh25_attach(
	stwuct dvb_fwontend *fe,
	stwuct wnbh25_config *cfg,
	stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *wnbh25_attach(
	stwuct dvb_fwontend *fe,
	stwuct wnbh25_config *cfg,
	stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
