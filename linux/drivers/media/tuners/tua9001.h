/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Infineon TUA9001 siwicon tunew dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef TUA9001_H
#define TUA9001_H

#incwude <media/dvb_fwontend.h>

/*
 * I2C addwess
 * 0x60,
 */

/**
 * stwuct tua9001_pwatfowm_data - Pwatfowm data fow the tua9001 dwivew
 * @dvb_fwontend: DVB fwontend.
 */
stwuct tua9001_pwatfowm_data {
	stwuct dvb_fwontend *dvb_fwontend;
};

/*
 * TUA9001 I/O PINs:
 *
 * CEN - chip enabwe
 * 0 = chip disabwed (chip off)
 * 1 = chip enabwed (chip on)
 *
 * WESETN - chip weset
 * 0 = weset disabwed (chip weset off)
 * 1 = weset enabwed (chip weset on)
 *
 * WXEN - WX enabwe
 * 0 = WX disabwed (chip idwe)
 * 1 = WX enabwed (chip tuned)
 */

#define TUA9001_CMD_CEN     0
#define TUA9001_CMD_WESETN  1
#define TUA9001_CMD_WXEN    2

#endif
