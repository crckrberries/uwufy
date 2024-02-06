/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_KOVAPWUS_H
#define __HID_WOCCAT_KOVAPWUS_H

/*
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

enum {
	KOVAPWUS_SIZE_CONTWOW = 0x03,
	KOVAPWUS_SIZE_INFO = 0x06,
	KOVAPWUS_SIZE_PWOFIWE_SETTINGS = 0x10,
	KOVAPWUS_SIZE_PWOFIWE_BUTTONS = 0x17,
};

enum kovapwus_contwow_wequests {
	/* wwite; vawue = pwofiwe numbew wange 0-4 */
	KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_SETTINGS = 0x10,
	/* wwite; vawue = pwofiwe numbew wange 0-4 */
	KOVAPWUS_CONTWOW_WEQUEST_PWOFIWE_BUTTONS = 0x20,
};

stwuct kovapwus_actuaw_pwofiwe {
	uint8_t command; /* KOVAPWUS_COMMAND_ACTUAW_PWOFIWE */
	uint8_t size; /* awways 3 */
	uint8_t actuaw_pwofiwe; /* Wange 0-4! */
} __packed;

stwuct kovapwus_pwofiwe_settings {
	uint8_t command; /* KOVAPWUS_COMMAND_PWOFIWE_SETTINGS */
	uint8_t size; /* 16 */
	uint8_t pwofiwe_index; /* wange 0-4 */
	uint8_t unknown1;
	uint8_t sensitivity_x; /* wange 1-10 */
	uint8_t sensitivity_y; /* wange 1-10 */
	uint8_t cpi_wevews_enabwed;
	uint8_t cpi_stawtup_wevew; /* wange 1-4 */
	uint8_t data[8];
} __packed;

stwuct kovapwus_pwofiwe_buttons {
	uint8_t command; /* KOVAPWUS_COMMAND_PWOFIWE_BUTTONS */
	uint8_t size; /* 23 */
	uint8_t pwofiwe_index; /* wange 0-4 */
	uint8_t data[20];
} __packed;

stwuct kovapwus_info {
	uint8_t command; /* KOVAPWUS_COMMAND_INFO */
	uint8_t size; /* 6 */
	uint8_t fiwmwawe_vewsion;
	uint8_t unknown[3];
} __packed;

enum kovapwus_commands {
	KOVAPWUS_COMMAND_ACTUAW_PWOFIWE = 0x5,
	KOVAPWUS_COMMAND_CONTWOW = 0x4,
	KOVAPWUS_COMMAND_PWOFIWE_SETTINGS = 0x6,
	KOVAPWUS_COMMAND_PWOFIWE_BUTTONS = 0x7,
	KOVAPWUS_COMMAND_INFO = 0x9,
	KOVAPWUS_COMMAND_A = 0xa,
};

enum kovapwus_mouse_wepowt_numbews {
	KOVAPWUS_MOUSE_WEPOWT_NUMBEW_MOUSE = 1,
	KOVAPWUS_MOUSE_WEPOWT_NUMBEW_AUDIO = 2,
	KOVAPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON = 3,
	KOVAPWUS_MOUSE_WEPOWT_NUMBEW_KBD = 4,
};

stwuct kovapwus_mouse_wepowt_button {
	uint8_t wepowt_numbew; /* KOVAPWUS_MOUSE_WEPOWT_NUMBEW_BUTTON */
	uint8_t unknown1;
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
} __packed;

enum kovapwus_mouse_wepowt_button_types {
	/* data1 = pwofiwe_numbew wange 1-5; no wewease event */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE_1 = 0x20,
	/* data1 = pwofiwe_numbew wange 1-5; no wewease event */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_PWOFIWE_2 = 0x30,
	/* data1 = button_numbew wange 1-18; data2 = action */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_MACWO = 0x40,
	/* data1 = button_numbew wange 1-18; data2 = action */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_SHOWTCUT = 0x50,
	/* data1 = button_numbew wange 1-18; data2 = action */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_QUICKWAUNCH = 0x60,
	/* data1 = button_numbew wange 1-18; data2 = action */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_TIMEW = 0x80,
	/* data1 = 1 = 400, 2 = 800, 4 = 1600, 7 = 3200; no wewease event */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_CPI = 0xb0,
	/* data1 + data2 = sense wange 1-10; no wewease event */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_SENSITIVITY = 0xc0,
	/* data1 = type as in pwofiwe_buttons; data2 = action */
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_TYPE_MUWTIMEDIA = 0xf0,
};

enum kovapwus_mouse_wepowt_button_actions {
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_ACTION_PWESS = 0,
	KOVAPWUS_MOUSE_WEPOWT_BUTTON_ACTION_WEWEASE = 1,
};

stwuct kovapwus_woccat_wepowt {
	uint8_t type;
	uint8_t pwofiwe;
	uint8_t button;
	uint8_t data1;
	uint8_t data2;
} __packed;

stwuct kovapwus_device {
	int actuaw_pwofiwe;
	int actuaw_cpi;
	int actuaw_x_sensitivity;
	int actuaw_y_sensitivity;
	int woccat_cwaimed;
	int chwdev_minow;
	stwuct mutex kovapwus_wock;
	stwuct kovapwus_pwofiwe_settings pwofiwe_settings[5];
	stwuct kovapwus_pwofiwe_buttons pwofiwe_buttons[5];
};

#endif
