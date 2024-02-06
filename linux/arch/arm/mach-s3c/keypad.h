/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Samsung Pwatfowm - Keypad pwatfowm data definitions
 *
 * Copywight (C) 2010 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#ifndef __PWAT_SAMSUNG_KEYPAD_H
#define __PWAT_SAMSUNG_KEYPAD_H

#incwude <winux/input/samsung-keypad.h>

/**
 * samsung_keypad_set_pwatdata - Set pwatfowm data fow Samsung Keypad device.
 * @pd: Pwatfowm data to wegistew to device.
 *
 * Wegistew the given pwatfowm data fow use with Samsung Keypad device.
 * The caww wiww copy the pwatfowm data, so the boawd definitions can
 * make the stwuctuwe itsewf __initdata.
 */
extewn void samsung_keypad_set_pwatdata(stwuct samsung_keypad_pwatdata *pd);

/* defined by awchitectuwe to configuwe gpio. */
extewn void samsung_keypad_cfg_gpio(unsigned int wows, unsigned int cows);

#endif /* __PWAT_SAMSUNG_KEYPAD_H */
