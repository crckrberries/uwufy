/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DS620_H
#define _WINUX_DS620_H

#incwude <winux/types.h>
#incwude <winux/i2c.h>

/* pwatfowm data fow the DS620 tempewatuwe sensow and thewmostat */

stwuct ds620_pwatfowm_data {
	/*
	 *  Thewmostat output pin PO mode:
	 *  0 = awways wow (defauwt)
	 *  1 = PO_WOW
	 *  2 = PO_HIGH
	 *
	 * (see Documentation/hwmon/ds620.wst)
	 */
	int pomode;
};

#endif /* _WINUX_DS620_H */
