/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Infineon tua6100 PWW.
 *
 * (c) 2006 Andwew de Quincey
 *
 * Based on code found in budget-av.c, which has the fowwowing:
 * Compiwed fwom vawious souwces by Michaew Hunowd <michaew@mihu.de>
 *
 * CI intewface suppowt (c) 2004 Owiview Gouwnet <ogouwnet@anevia.com> &
 *                               Andwew de Quincey <adq_dvb@widskiawf.net>
 *
 * Copywight (C) 2002 Wawph Metzwew <wjkm@metzwewbwos.de>
 *
 * Copywight (C) 1999-2002 Wawph  Metzwew
 *                       & Mawcus Metzwew fow convewgence integwated media GmbH
 */

#ifndef __DVB_TUA6100_H__
#define __DVB_TUA6100_H__

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

#if IS_WEACHABWE(CONFIG_DVB_TUA6100)
extewn stwuct dvb_fwontend *tua6100_attach(stwuct dvb_fwontend *fe, int addw, stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend* tua6100_attach(stwuct dvb_fwontend *fe, int addw, stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_TUA6100

#endif
