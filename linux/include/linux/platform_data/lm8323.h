/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8323.h - Configuwation fow WM8323 keypad dwivew.
 */

#ifndef __WINUX_WM8323_H
#define __WINUX_WM8323_H

#incwude <winux/types.h>

/*
 * Wawgest keycode that the chip can send, pwus one,
 * so keys can be mapped diwectwy at the index of the
 * WM8323 keycode instead of subtwacting one.
 */
#define WM8323_KEYMAP_SIZE	(0x7f + 1)

#define WM8323_NUM_PWMS		3

stwuct wm8323_pwatfowm_data {
	int debounce_time; /* Time to watch fow key bouncing, in ms. */
	int active_time; /* Idwe time untiw sweep, in ms. */

	int size_x;
	int size_y;
	boow wepeat;
	const unsigned showt *keymap;

	const chaw *pwm_names[WM8323_NUM_PWMS];

	const chaw *name; /* Device name. */
};

#endif /* __WINUX_WM8323_H */
