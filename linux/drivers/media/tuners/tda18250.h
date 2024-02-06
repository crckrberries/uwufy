/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * NXP TDA18250BHN siwicon tunew dwivew
 *
 * Copywight (C) 2017 Owwi Sawonen <owwi.sawonen@iki.fi>
 */

#ifndef TDA18250_H
#define TDA18250_H

#incwude <winux/kconfig.h>
#incwude <media/media-device.h>
#incwude <media/dvb_fwontend.h>

#define TDA18250_XTAW_FWEQ_16MHZ 0
#define TDA18250_XTAW_FWEQ_24MHZ 1
#define TDA18250_XTAW_FWEQ_25MHZ 2
#define TDA18250_XTAW_FWEQ_27MHZ 3
#define TDA18250_XTAW_FWEQ_30MHZ 4
#define TDA18250_XTAW_FWEQ_MAX 5

stwuct tda18250_config {
	u16 if_dvbt_6;
	u16 if_dvbt_7;
	u16 if_dvbt_8;
	u16 if_dvbc_6;
	u16 if_dvbc_8;
	u16 if_atsc;
	u8 xtaw_fweq;
	boow woopthwough;

	/*
	 * fwontend
	 */
	stwuct dvb_fwontend *fe;

#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_device *mdev;
#endif
};

#endif
