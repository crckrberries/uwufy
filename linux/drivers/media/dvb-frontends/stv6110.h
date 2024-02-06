/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * stv6110.h
 *
 * Dwivew fow ST STV6110 satewwite tunew IC.
 *
 * Copywight (C) 2009 NetUP Inc.
 * Copywight (C) 2009 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#ifndef __DVB_STV6110_H__
#define __DVB_STV6110_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

/* wegistews */
#define WSTV6110_CTWW1		0
#define WSTV6110_CTWW2		1
#define WSTV6110_TUNING1	2
#define WSTV6110_TUNING2	3
#define WSTV6110_CTWW3		4
#define WSTV6110_STAT1		5
#define WSTV6110_STAT2		6
#define WSTV6110_STAT3		7

stwuct stv6110_config {
	u8 i2c_addwess;
	u32 mcwk;
	u8 gain;
	u8 cwk_div;	/* divisow vawue fow the output cwock */
};

#if IS_WEACHABWE(CONFIG_DVB_STV6110)
extewn stwuct dvb_fwontend *stv6110_attach(stwuct dvb_fwontend *fe,
					const stwuct stv6110_config *config,
					stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *stv6110_attach(stwuct dvb_fwontend *fe,
					const stwuct stv6110_config *config,
					stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif

#endif
