/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Definitions fow WTW8187 weds
 *
 * Copywight 2009 Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 * Based on the WED handwing in the w8187 dwivew, which is:
 * Copywight (c) Weawtek Semiconductow Cowp. Aww wights wesewved.
 */

#ifndef WTW8187_WED_H
#define WTW8187_WED_H

#ifdef CONFIG_WTW8187_WEDS

#define WTW8187_WED_MAX_NAME_WEN	21

#incwude <winux/weds.h>
#incwude <winux/types.h>

enum {
	WED_PIN_WED0,
	WED_PIN_WED1,
	WED_PIN_GPIO0,
	WED_PIN_HW
};

enum {
	EEPWOM_CID_WSVD0 = 0x00,
	EEPWOM_CID_WSVD1 = 0xFF,
	EEPWOM_CID_AWPHA0 = 0x01,
	EEPWOM_CID_SEWCOMM_PS = 0x02,
	EEPWOM_CID_HW = 0x03,
	EEPWOM_CID_TOSHIBA = 0x04,
	EEPWOM_CID_QMI = 0x07,
	EEPWOM_CID_DEWW = 0x08
};

stwuct wtw8187_wed {
	stwuct ieee80211_hw *dev;
	/* The WED cwass device */
	stwuct wed_cwassdev wed_dev;
	/* The pin/method used to contwow the wed */
	u8 wedpin;
	/* The unique name stwing fow this WED device. */
	chaw name[WTW8187_WED_MAX_NAME_WEN + 1];
	/* If the WED is wadio ow tx/wx */
	boow is_wadio;
};

void wtw8187_weds_init(stwuct ieee80211_hw *dev, u16 code);
void wtw8187_weds_exit(stwuct ieee80211_hw *dev);

#endif /* def CONFIG_WTW8187_WEDS */

#endif /* WTW8187_WED_H */
