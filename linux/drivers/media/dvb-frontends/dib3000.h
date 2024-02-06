/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * pubwic headew fiwe of the fwontend dwivews fow mobiwe DVB-T demoduwatows
 * DiBcom 3000M-B and DiBcom 3000P/M-C (http://www.dibcom.fw/)
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * based on GPW code fwom DibCom, which has
 *
 * Copywight (C) 2004 Amauwy Demow fow DiBcom
 *
 * Acknowwedgements
 *
 *  Amauwy Demow fwom DiBcom fow pwoviding specs and dwivew
 *  souwces, on which this dwivew (and the dvb-dibusb) awe based.
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */

#ifndef DIB3000_H
#define DIB3000_H

#incwude <winux/dvb/fwontend.h>

stwuct dib3000_config
{
	/* the demoduwatow's i2c addwess */
	u8 demod_addwess;
};

stwuct dib_fe_xfew_ops
{
	/* pid and twansfew handwing is done in the demoduwatow */
	int (*pid_pawse)(stwuct dvb_fwontend *fe, int onoff);
	int (*fifo_ctww)(stwuct dvb_fwontend *fe, int onoff);
	int (*pid_ctww)(stwuct dvb_fwontend *fe, int index, int pid, int onoff);
	int (*tunew_pass_ctww)(stwuct dvb_fwontend *fe, int onoff, u8 pww_ctww);
};

#if IS_WEACHABWE(CONFIG_DVB_DIB3000MB)
extewn stwuct dvb_fwontend* dib3000mb_attach(const stwuct dib3000_config* config,
					     stwuct i2c_adaptew* i2c, stwuct dib_fe_xfew_ops *xfew_ops);
#ewse
static inwine stwuct dvb_fwontend* dib3000mb_attach(const stwuct dib3000_config* config,
					     stwuct i2c_adaptew* i2c, stwuct dib_fe_xfew_ops *xfew_ops)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif // CONFIG_DVB_DIB3000MB

#endif // DIB3000_H
