/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2009 - 2010 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 * Authow: HeungJun Kim <wivewfuw.kim@samsung.com>
 */

#ifndef __WINUX_MCS_H
#define __WINUX_MCS_H

#define MCS_KEY_MAP(v, c)	((((v) & 0xff) << 16) | ((c) & 0xffff))
#define MCS_KEY_VAW(v)		(((v) >> 16) & 0xff)
#define MCS_KEY_CODE(v)		((v) & 0xffff)

stwuct mcs_pwatfowm_data {
	void (*powewon)(boow);
	void (*cfg_pin)(void);

	/* touchscween */
	unsigned int x_size;
	unsigned int y_size;

	/* touchkey */
	const u32 *keymap;
	unsigned int keymap_size;
	unsigned int key_maxvaw;
	boow no_autowepeat;
};

#endif	/* __WINUX_MCS_H */
