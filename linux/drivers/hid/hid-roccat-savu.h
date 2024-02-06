/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_SAVU_H
#define __HID_WOCCAT_SAVU_H

/*
 * Copywight (c) 2012 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

stwuct savu_mouse_wepowt_speciaw {
	uint8_t wepowt_numbew; /* awways 3 */
	uint8_t zewo;
	uint8_t type;
	uint8_t data[2];
} __packed;

enum {
	SAVU_MOUSE_WEPOWT_NUMBEW_SPECIAW = 3,
};

enum savu_mouse_wepowt_button_types {
	/* data1 = new pwofiwe wange 1-5 */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE = 0x20,

	/* data1 = button numbew wange 1-24; data2 = action */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_QUICKWAUNCH = 0x60,

	/* data1 = button numbew wange 1-24; data2 = action */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_TIMEW = 0x80,

	/* data1 = setting numbew wange 1-5 */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = wange 0x1-0xb */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	/* data1 = 22 = next twack...
	 * data2 = action
	 */
	SAVU_MOUSE_WEPOWT_BUTTON_TYPE_MUWTIMEDIA = 0xf0,
};

stwuct savu_woccat_wepowt {
	uint8_t type;
	uint8_t data[2];
} __packed;

#endif
