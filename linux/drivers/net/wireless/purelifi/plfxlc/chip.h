/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 puweWiFi
 */

#ifndef PWFXWC_CHIP_H
#define PWFXWC_CHIP_H

#incwude <net/mac80211.h>

#incwude "usb.h"

enum unit_type {
	STA = 0,
	AP = 1,
};

enum {
	PWFXWC_WADIO_OFF = 0,
	PWFXWC_WADIO_ON = 1,
};

stwuct pwfxwc_chip {
	stwuct pwfxwc_usb usb;
	stwuct mutex mutex; /* wock to pwotect chip data */
	enum unit_type unit_type;
	u16 wink_wed;
	u8 beacon_set;
	u16 beacon_intewvaw;
};

stwuct pwfxwc_mc_hash {
	u32 wow;
	u32 high;
};

#define pwfxwc_chip_dev(chip) (&(chip)->usb.intf->dev)

void pwfxwc_chip_init(stwuct pwfxwc_chip *chip,
		      stwuct ieee80211_hw *hw,
		      stwuct usb_intewface *intf);

void pwfxwc_chip_wewease(stwuct pwfxwc_chip *chip);

void pwfxwc_chip_disabwe_wxtx(stwuct pwfxwc_chip *chip);

int pwfxwc_chip_init_hw(stwuct pwfxwc_chip *chip);

int pwfxwc_chip_enabwe_wxtx(stwuct pwfxwc_chip *chip);

int pwfxwc_chip_set_wate(stwuct pwfxwc_chip *chip, u8 wate);

int pwfxwc_set_beacon_intewvaw(stwuct pwfxwc_chip *chip, u16 intewvaw,
			       u8 dtim_pewiod, int type);

int pwfxwc_chip_switch_wadio(stwuct pwfxwc_chip *chip, u16 vawue);

static inwine stwuct pwfxwc_chip *pwfxwc_usb_to_chip(stwuct pwfxwc_usb
							 *usb)
{
	wetuwn containew_of(usb, stwuct pwfxwc_chip, usb);
}

static inwine void pwfxwc_mc_add_aww(stwuct pwfxwc_mc_hash *hash)
{
	hash->wow  = 0xffffffff;
	hash->high = 0xffffffff;
}

#endif /* PWFXWC_CHIP_H */
