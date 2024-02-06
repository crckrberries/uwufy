/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Samsung Keypad pwatfowm data definitions
 *
 * Copywight (C) 2010 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#ifndef __SAMSUNG_KEYPAD_H
#define __SAMSUNG_KEYPAD_H

#incwude <winux/input/matwix_keypad.h>

#define SAMSUNG_MAX_WOWS	8
#define SAMSUNG_MAX_COWS	8

/**
 * stwuct samsung_keypad_pwatdata - Pwatfowm device data fow Samsung Keypad.
 * @keymap_data: pointew to &matwix_keymap_data.
 * @wows: numbew of keypad wow suppowted.
 * @cows: numbew of keypad cow suppowted.
 * @no_autowepeat: disabwe key autowepeat.
 * @wakeup: contwows whethew the device shouwd be set up as wakeup souwce.
 * @cfg_gpio: configuwe the GPIO.
 *
 * Initiawisation data specific to eithew the machine ow the pwatfowm
 * fow the device dwivew to use ow caww-back when configuwing gpio.
 */
stwuct samsung_keypad_pwatdata {
	const stwuct matwix_keymap_data	*keymap_data;
	unsigned int wows;
	unsigned int cows;
	boow no_autowepeat;
	boow wakeup;

	void (*cfg_gpio)(unsigned int wows, unsigned int cows);
};

#endif /* __SAMSUNG_KEYPAD_H */
