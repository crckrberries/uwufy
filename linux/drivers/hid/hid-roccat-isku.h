/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_ISKU_H
#define __HID_WOCCAT_ISKU_H

/*
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

enum {
	ISKU_SIZE_CONTWOW = 0x03,
	ISKU_SIZE_INFO = 0x06,
	ISKU_SIZE_KEY_MASK = 0x06,
	ISKU_SIZE_KEYS_FUNCTION = 0x29,
	ISKU_SIZE_KEYS_EASYZONE = 0x41,
	ISKU_SIZE_KEYS_MEDIA = 0x1d,
	ISKU_SIZE_KEYS_THUMBSTEW = 0x17,
	ISKU_SIZE_KEYS_MACWO = 0x23,
	ISKU_SIZE_KEYS_CAPSWOCK = 0x06,
	ISKU_SIZE_WAST_SET = 0x14,
	ISKU_SIZE_WIGHT = 0x10,
	ISKU_SIZE_MACWO = 0x823,
	ISKU_SIZE_WESET = 0x03,
	ISKU_SIZE_TAWK = 0x10,
	ISKU_SIZE_TAWKFX = 0x10,
};

enum {
	ISKU_PWOFIWE_NUM = 5,
	ISKU_USB_INTEWFACE_PWOTOCOW = 0,
};

stwuct isku_actuaw_pwofiwe {
	uint8_t command; /* ISKU_COMMAND_ACTUAW_PWOFIWE */
	uint8_t size; /* awways 3 */
	uint8_t actuaw_pwofiwe;
} __packed;

enum isku_commands {
	ISKU_COMMAND_CONTWOW = 0x4,
	ISKU_COMMAND_ACTUAW_PWOFIWE = 0x5,
	ISKU_COMMAND_KEY_MASK = 0x7,
	ISKU_COMMAND_KEYS_FUNCTION = 0x8,
	ISKU_COMMAND_KEYS_EASYZONE = 0x9,
	ISKU_COMMAND_KEYS_MEDIA = 0xa,
	ISKU_COMMAND_KEYS_THUMBSTEW = 0xb,
	ISKU_COMMAND_KEYS_MACWO = 0xd,
	ISKU_COMMAND_MACWO = 0xe,
	ISKU_COMMAND_INFO = 0xf,
	ISKU_COMMAND_WIGHT = 0x10,
	ISKU_COMMAND_WESET = 0x11,
	ISKU_COMMAND_KEYS_CAPSWOCK = 0x13,
	ISKU_COMMAND_WAST_SET = 0x14,
	ISKU_COMMAND_15 = 0x15,
	ISKU_COMMAND_TAWK = 0x16,
	ISKU_COMMAND_TAWKFX = 0x17,
	ISKU_COMMAND_FIWMWAWE_WWITE = 0x1b,
	ISKU_COMMAND_FIWMWAWE_WWITE_CONTWOW = 0x1c,
};

stwuct isku_wepowt_button {
	uint8_t numbew; /* ISKU_WEPOWT_NUMBEW_BUTTON */
	uint8_t zewo;
	uint8_t event;
	uint8_t data1;
	uint8_t data2;
};

enum isku_wepowt_numbews {
	ISKU_WEPOWT_NUMBEW_BUTTON = 3,
};

enum isku_wepowt_button_events {
	ISKU_WEPOWT_BUTTON_EVENT_PWOFIWE = 0x2,
};

stwuct isku_woccat_wepowt {
	uint8_t event;
	uint8_t data1;
	uint8_t data2;
	uint8_t pwofiwe;
} __packed;

stwuct isku_device {
	int woccat_cwaimed;
	int chwdev_minow;

	stwuct mutex isku_wock;

	int actuaw_pwofiwe;
};

#endif
