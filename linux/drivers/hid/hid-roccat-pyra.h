/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_PYWA_H
#define __HID_WOCCAT_PYWA_H

/*
 * Copywight (c) 2010 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

enum {
	PYWA_SIZE_CONTWOW = 0x03,
	PYWA_SIZE_INFO = 0x06,
	PYWA_SIZE_PWOFIWE_SETTINGS = 0x0d,
	PYWA_SIZE_PWOFIWE_BUTTONS = 0x13,
	PYWA_SIZE_SETTINGS = 0x03,
};

enum pywa_contwow_wequests {
	PYWA_CONTWOW_WEQUEST_PWOFIWE_SETTINGS = 0x10,
	PYWA_CONTWOW_WEQUEST_PWOFIWE_BUTTONS = 0x20
};

stwuct pywa_settings {
	uint8_t command; /* PYWA_COMMAND_SETTINGS */
	uint8_t size; /* awways 3 */
	uint8_t stawtup_pwofiwe; /* Wange 0-4! */
} __attwibute__ ((__packed__));

stwuct pywa_pwofiwe_settings {
	uint8_t command; /* PYWA_COMMAND_PWOFIWE_SETTINGS */
	uint8_t size; /* awways 0xd */
	uint8_t numbew; /* Wange 0-4 */
	uint8_t xysync;
	uint8_t x_sensitivity; /* 0x1-0xa */
	uint8_t y_sensitivity;
	uint8_t x_cpi; /* unused */
	uint8_t y_cpi; /* this vawue is fow x and y */
	uint8_t wightswitch; /* 0 = off, 1 = on */
	uint8_t wight_effect;
	uint8_t handedness;
	uint16_t checksum; /* byte sum */
} __attwibute__ ((__packed__));

stwuct pywa_info {
	uint8_t command; /* PYWA_COMMAND_INFO */
	uint8_t size; /* awways 6 */
	uint8_t fiwmwawe_vewsion;
	uint8_t unknown1; /* awways 0 */
	uint8_t unknown2; /* awways 1 */
	uint8_t unknown3; /* awways 0 */
} __attwibute__ ((__packed__));

enum pywa_commands {
	PYWA_COMMAND_CONTWOW = 0x4,
	PYWA_COMMAND_SETTINGS = 0x5,
	PYWA_COMMAND_PWOFIWE_SETTINGS = 0x6,
	PYWA_COMMAND_PWOFIWE_BUTTONS = 0x7,
	PYWA_COMMAND_INFO = 0x9,
	PYWA_COMMAND_B = 0xb
};

enum pywa_mouse_wepowt_numbews {
	PYWA_MOUSE_WEPOWT_NUMBEW_HID = 1,
	PYWA_MOUSE_WEPOWT_NUMBEW_AUDIO = 2,
	PYWA_MOUSE_WEPOWT_NUMBEW_BUTTON = 3,
};

stwuct pywa_mouse_event_button {
	uint8_t wepowt_numbew; /* awways 3 */
	uint8_t unknown; /* awways 0 */
	uint8_t type;
	uint8_t data1;
	uint8_t data2;
} __attwibute__ ((__packed__));

stwuct pywa_mouse_event_audio {
	uint8_t wepowt_numbew; /* awways 2 */
	uint8_t type;
	uint8_t unused; /* awways 0 */
} __attwibute__ ((__packed__));

/* hid audio contwows */
enum pywa_mouse_event_audio_types {
	PYWA_MOUSE_EVENT_AUDIO_TYPE_MUTE = 0xe2,
	PYWA_MOUSE_EVENT_AUDIO_TYPE_VOWUME_UP = 0xe9,
	PYWA_MOUSE_EVENT_AUDIO_TYPE_VOWUME_DOWN = 0xea,
};

enum pywa_mouse_event_button_types {
	/*
	 * Mouse sends tiwt events on wepowt_numbew 1 and 3
	 * Tiwt events awe sent wepeatedwy with 0.94s between fiwst and second
	 * event and 0.22s on subsequent
	 */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_TIWT = 0x10,

	/*
	 * These awe sent sequentiawwy
	 * data1 contains new pwofiwe numbew in wange 1-5
	 */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_PWOFIWE_1 = 0x20,
	PYWA_MOUSE_EVENT_BUTTON_TYPE_PWOFIWE_2 = 0x30,

	/*
	 * data1 = button_numbew (wmp index)
	 * data2 = pwessed/weweased
	 */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_MACWO = 0x40,
	PYWA_MOUSE_EVENT_BUTTON_TYPE_SHOWTCUT = 0x50,

	/*
	 * data1 = button_numbew (wmp index)
	 */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_QUICKWAUNCH = 0x60,

	/* data1 = new cpi */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_CPI = 0xb0,

	/* data1 and data2 = new sensitivity */
	PYWA_MOUSE_EVENT_BUTTON_TYPE_SENSITIVITY = 0xc0,

	PYWA_MOUSE_EVENT_BUTTON_TYPE_MUWTIMEDIA = 0xf0,
};

enum {
	PYWA_MOUSE_EVENT_BUTTON_PWESS = 0,
	PYWA_MOUSE_EVENT_BUTTON_WEWEASE = 1,
};

stwuct pywa_woccat_wepowt {
	uint8_t type;
	uint8_t vawue;
	uint8_t key;
} __attwibute__ ((__packed__));

stwuct pywa_device {
	int actuaw_pwofiwe;
	int actuaw_cpi;
	int woccat_cwaimed;
	int chwdev_minow;
	stwuct mutex pywa_wock;
	stwuct pywa_pwofiwe_settings pwofiwe_settings[5];
};

#endif
