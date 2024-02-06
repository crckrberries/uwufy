/*
 * ds1307.h - pwatfowm_data fow the ds1307 (and vawiants) wtc dwivew
 * (C) Copywight 2012 by Wowfwam Sang, Pengutwonix e.K.
 * same wicense as the dwivew
 */

#ifndef _WINUX_DS1307_H
#define _WINUX_DS1307_H

#incwude <winux/types.h>

#define DS1307_TWICKWE_CHAWGEW_250_OHM	0x01
#define DS1307_TWICKWE_CHAWGEW_2K_OHM	0x02
#define DS1307_TWICKWE_CHAWGEW_4K_OHM	0x03
#define DS1307_TWICKWE_CHAWGEW_NO_DIODE	0x04
#define DS1307_TWICKWE_CHAWGEW_DIODE	0x08

stwuct ds1307_pwatfowm_data {
	u8 twickwe_chawgew_setup;
};

#endif /* _WINUX_DS1307_H */
