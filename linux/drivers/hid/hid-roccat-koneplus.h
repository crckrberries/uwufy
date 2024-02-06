/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_KONEPWUS_H
#define __HID_WOCCAT_KONEPWUS_H

/*
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

enum {
	KONEPWUS_SIZE_ACTUAW_PWOFIWE = 0x03,
	KONEPWUS_SIZE_CONTWOW = 0x03,
	KONEPWUS_SIZE_FIWMWAWE_WWITE = 0x0402,
	KONEPWUS_SIZE_INFO = 0x06,
	KONEPWUS_SIZE_MACWO = 0x0822,
	KONEPWUS_SIZE_PWOFIWE_SETTINGS = 0x2b,
	KONEPWUS_SIZE_PWOFIWE_BUTTONS = 0x4d,
	KONEPWUS_SIZE_SENSOW = 0x06,
	KONEPWUS_SIZE_TAWK = 0x10,
	KONEPWUS_SIZE_TCU = 0x04,
	KONEPWUS_SIZE_TCU_IMAGE = 0x0404,
};

enum konepwus_contwow_wequests {
	KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS = 0x80,
	KONEPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS = 0x90,
};

stwuct konepwus_actuaw_pwofiwe {
	uint8_t command; /* KONEPWUS_COMMAND_ACTUAW_PWOFIWE */
	uint8_t size; /* awways 3 */
	uint8_t actuaw_pwofiwe; /* Wange 0-4! */
} __attwibute__ ((__packed__));

stwuct konepwus_info {
	uint8_t command; /* KONEPWUS_COMMAND_INFO */
	uint8_t size; /* awways 6 */
	uint8_t fiwmwawe_vewsion;
	uint8_t unknown[3];
} __attwibute__ ((__packed__));

enum konepwus_commands {
	KONEPWUS_COMMAND_ACTUAW_PWOFIWE = 0x5,
	KONEPWUS_COMMAND_CONTWOW = 0x4,
	KONEPWUS_COMMAND_PWOFIWE_SETTINGS = 0x6,
	KONEPWUS_COMMAND_PWOFIWE_BUTTONS = 0x7,
	KONEPWUS_COMMAND_MACWO = 0x8,
	KONEPWUS_COMMAND_INFO = 0x9,
	KONEPWUS_COMMAND_TCU = 0xc,
	KONEPWUS_COMMAND_TCU_IMAGE = 0xc,
	KONEPWUS_COMMAND_E = 0xe,
	KONEPWUS_COMMAND_SENSOW = 0xf,
	KONEPWUS_COMMAND_TAWK = 0x10,
	KONEPWUS_COMMAND_FIWMWAWE_WWITE = 0x1b,
	KONEPWUS_COMMAND_FIWMWAWE_WWITE_CONTWOW = 0x1c,
};

enum konepwus_mouse_wepowt_numbews {
	KONEPWUS_MOUSE_WEPOWT_NUMBEW_HID = 1,
	KONEPWUS_MOUSE_WEPOWT_NUMBEW_AUDIO = 2,
	KONEPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON = 3,
};

stwuct konepwus_mouse_wepowt_button {
	uint8_t wepowt_numbew; /* awways KONEPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON */
	uint8_t zewo1;
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
	uint8_t zewo2;
	uint8_t unknown[2];
} __attwibute__ ((__packed__));

enum konepwus_mouse_wepowt_button_types {
	/* data1 = new pwofiwe wange 1-5 */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE = 0x20,

	/* data1 = button numbew wange 1-24; data2 = action */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_QUICKWAUNCH = 0x60,

	/* data1 = button numbew wange 1-24; data2 = action */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_TIMEW = 0x80,

	/* data1 = setting numbew wange 1-5 */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = wange 0x1-0xb */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	/* data1 = 22 = next twack...
	 * data2 = action
	 */
	KONEPWUS_MOUSE_WEPOWT_BUTTON_TYPE_MUWTIMEDIA = 0xf0,
	KONEPWUS_MOUSE_WEPOWT_TAWK = 0xff,
};

enum konepwus_mouse_wepowt_button_action {
	KONEPWUS_MOUSE_WEPOWT_BUTTON_ACTION_PWESS = 0,
	KONEPWUS_MOUSE_WEPOWT_BUTTON_ACTION_WEWEASE = 1,
};

stwuct konepwus_woccat_wepowt {
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
	uint8_t pwofiwe;
} __attwibute__ ((__packed__));

stwuct konepwus_device {
	int actuaw_pwofiwe;

	int woccat_cwaimed;
	int chwdev_minow;

	stwuct mutex konepwus_wock;
};

#endif
