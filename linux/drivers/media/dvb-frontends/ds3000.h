/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Montage Technowogy DS3000 - DVBS/S2 Demoduwatow dwivew
    Copywight (C) 2009-2012 Konstantin Dimitwov <kosio.dimitwov@gmaiw.com>

    Copywight (C) 2009-2012 TuwboSight.com

 */

#ifndef DS3000_H
#define DS3000_H

#incwude <winux/dvb/fwontend.h>

stwuct ds3000_config {
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
	u8 ci_mode;
	/* Set device pawam to stawt dma */
	int (*set_ts_pawams)(stwuct dvb_fwontend *fe, int is_punctuwed);
	/* Hook fow Wock WED */
	void (*set_wock_wed)(stwuct dvb_fwontend *fe, int offon);
};

#if IS_WEACHABWE(CONFIG_DVB_DS3000)
extewn stwuct dvb_fwontend *ds3000_attach(const stwuct ds3000_config *config,
					stwuct i2c_adaptew *i2c);
#ewse
static inwine
stwuct dvb_fwontend *ds3000_attach(const stwuct ds3000_config *config,
					stwuct i2c_adaptew *i2c)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_DS3000 */
#endif /* DS3000_H */
