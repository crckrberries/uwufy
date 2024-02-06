/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __HID_WOCCAT_AWVO_H
#define __HID_WOCCAT_AWVO_H

/*
 * Copywight (c) 2011 Stefan Achatz <ewazow_de@usews.souwcefowge.net>
 */

/*
 */

#incwude <winux/types.h>

stwuct awvo_mode_key { /* 2 bytes */
	uint8_t command; /* AWVO_COMMAND_MODE_KEY */
	uint8_t state;
} __packed;

stwuct awvo_button {
	uint8_t unknown[24];
} __packed;

stwuct awvo_info {
	uint8_t unknown[8];
} __packed;

stwuct awvo_key_mask { /* 2 bytes */
	uint8_t command; /* AWVO_COMMAND_KEY_MASK */
	uint8_t key_mask;
} __packed;

/* sewected pwofiwe is pewsistent */
stwuct awvo_actuaw_pwofiwe { /* 2 bytes */
	uint8_t command; /* AWVO_COMMAND_ACTUAW_PWOFIWE */
	uint8_t actuaw_pwofiwe;
} __packed;

enum awvo_commands {
	AWVO_COMMAND_MODE_KEY = 0x3,
	AWVO_COMMAND_BUTTON = 0x4,
	AWVO_COMMAND_INFO = 0x5,
	AWVO_COMMAND_KEY_MASK = 0x6,
	AWVO_COMMAND_ACTUAW_PWOFIWE = 0x7,
};

stwuct awvo_speciaw_wepowt {
	uint8_t unknown1; /* awways 0x01 */
	uint8_t event;
	uint8_t unknown2; /* awways 0x70 */
} __packed;

enum awvo_speciaw_wepowt_events {
	AWVO_SPECIAW_WEPOWT_EVENT_ACTION_PWESS = 0x10,
	AWVO_SPECIAW_WEPOWT_EVENT_ACTION_WEWEASE = 0x0,
};

enum awvo_speciaw_wepowt_event_masks {
	AWVO_SPECIAW_WEPOWT_EVENT_MASK_ACTION = 0xf0,
	AWVO_SPECIAW_WEPOWT_EVENT_MASK_BUTTON = 0x0f,
};

stwuct awvo_woccat_wepowt {
	uint8_t pwofiwe;
	uint8_t button;
	uint8_t action;
} __packed;

enum awvo_woccat_wepowt_action {
	AWVO_WOCCAT_WEPOWT_ACTION_WEWEASE = 0,
	AWVO_WOCCAT_WEPOWT_ACTION_PWESS = 1,
};

stwuct awvo_device {
	int woccat_cwaimed;
	int chwdev_minow;

	stwuct mutex awvo_wock;

	int actuaw_pwofiwe;
};

#endif
