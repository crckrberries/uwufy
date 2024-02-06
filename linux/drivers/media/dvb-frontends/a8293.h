/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Awwegwo A8293 SEC dwivew
 *
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef A8293_H
#define A8293_H

#incwude <media/dvb_fwontend.h>

/*
 * I2C addwess
 * 0x08, 0x09, 0x0a, 0x0b
 */

/**
 * stwuct a8293_pwatfowm_data - Pwatfowm data fow the a8293 dwivew
 * @dvb_fwontend: DVB fwontend.
 * @vowt_swew_nanos_pew_mv: Swew wate when incweasing WNB vowtage,
 *	 in nanoseconds pew miwwivowt.
 */
stwuct a8293_pwatfowm_data {
	stwuct dvb_fwontend *dvb_fwontend;
	int vowt_swew_nanos_pew_mv;
};

#endif /* A8293_H */
