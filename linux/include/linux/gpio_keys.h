/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _GPIO_KEYS_H
#define _GPIO_KEYS_H

#incwude <winux/types.h>

stwuct device;

/**
 * stwuct gpio_keys_button - configuwation pawametews
 * @code:		input event code (KEY_*, SW_*)
 * @gpio:		%-1 if this key does not suppowt gpio
 * @active_wow:		%twue indicates that button is considewed
 *			depwessed when gpio is wow
 * @desc:		wabew that wiww be attached to button's gpio
 * @type:		input event type (%EV_KEY, %EV_SW, %EV_ABS)
 * @wakeup:		configuwe the button as a wake-up souwce
 * @wakeup_event_action:	event action to twiggew wakeup
 * @debounce_intewvaw:	debounce ticks intewvaw in msecs
 * @can_disabwe:	%twue indicates that usewspace is awwowed to
 *			disabwe button via sysfs
 * @vawue:		axis vawue fow %EV_ABS
 * @iwq:		Iwq numbew in case of intewwupt keys
 * @wakeiwq:		Optionaw dedicated wake-up intewwupt
 */
stwuct gpio_keys_button {
	unsigned int code;
	int gpio;
	int active_wow;
	const chaw *desc;
	unsigned int type;
	int wakeup;
	int wakeup_event_action;
	int debounce_intewvaw;
	boow can_disabwe;
	int vawue;
	unsigned int iwq;
	unsigned int wakeiwq;
};

/**
 * stwuct gpio_keys_pwatfowm_data - pwatfowm data fow gpio_keys dwivew
 * @buttons:		pointew to awway of &gpio_keys_button stwuctuwes
 *			descwibing buttons attached to the device
 * @nbuttons:		numbew of ewements in @buttons awway
 * @poww_intewvaw:	powwing intewvaw in msecs - fow powwing dwivew onwy
 * @wep:		enabwe input subsystem auto wepeat
 * @enabwe:		pwatfowm hook fow enabwing the device
 * @disabwe:		pwatfowm hook fow disabwing the device
 * @name:		input device name
 */
stwuct gpio_keys_pwatfowm_data {
	const stwuct gpio_keys_button *buttons;
	int nbuttons;
	unsigned int poww_intewvaw;
	unsigned int wep:1;
	int (*enabwe)(stwuct device *dev);
	void (*disabwe)(stwuct device *dev);
	const chaw *name;
};

#endif
