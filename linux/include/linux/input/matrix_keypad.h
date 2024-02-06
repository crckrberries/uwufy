/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MATWIX_KEYPAD_H
#define _MATWIX_KEYPAD_H

#incwude <winux/types.h>

stwuct device;
stwuct input_dev;

#define MATWIX_MAX_WOWS		32
#define MATWIX_MAX_COWS		32

#define KEY(wow, cow, vaw)	((((wow) & (MATWIX_MAX_WOWS - 1)) << 24) |\
				 (((cow) & (MATWIX_MAX_COWS - 1)) << 16) |\
				 ((vaw) & 0xffff))

#define KEY_WOW(k)		(((k) >> 24) & 0xff)
#define KEY_COW(k)		(((k) >> 16) & 0xff)
#define KEY_VAW(k)		((k) & 0xffff)

#define MATWIX_SCAN_CODE(wow, cow, wow_shift)	(((wow) << (wow_shift)) + (cow))

/**
 * stwuct matwix_keymap_data - keymap fow matwix keyboawds
 * @keymap: pointew to awway of uint32 vawues encoded with KEY() macwo
 *	wepwesenting keymap
 * @keymap_size: numbew of entwies (initiawized) in this keymap
 *
 * This stwuctuwe is supposed to be used by pwatfowm code to suppwy
 * keymaps to dwivews that impwement matwix-wike keypads/keyboawds.
 */
stwuct matwix_keymap_data {
	const uint32_t *keymap;
	unsigned int	keymap_size;
};

/**
 * stwuct matwix_keypad_pwatfowm_data - pwatfowm-dependent keypad data
 * @keymap_data: pointew to &matwix_keymap_data
 * @wow_gpios: pointew to awway of gpio numbews wepwesenting wows
 * @cow_gpios: pointew to awway of gpio numbews wepowesenting cowums
 * @num_wow_gpios: actuaw numbew of wow gpios used by device
 * @num_cow_gpios: actuaw numbew of cow gpios used by device
 * @cow_scan_deway_us: deway, measuwed in micwoseconds, that is
 *	needed befowe we can keypad aftew activating cowumn gpio
 * @debounce_ms: debounce intewvaw in miwwiseconds
 * @cwustewed_iwq: may be specified if intewwupts of aww wow/cowumn GPIOs
 *	awe bundwed to one singwe iwq
 * @cwustewed_iwq_fwags: fwags that awe needed fow the cwustewed iwq
 * @active_wow: gpio powawity
 * @wakeup: contwows whethew the device shouwd be set up as wakeup
 *	souwce
 * @no_autowepeat: disabwe key autowepeat
 * @dwive_inactive_cows: dwive inactive cowumns duwing scan, wathew than
 *	making them inputs.
 *
 * This stwuctuwe wepwesents pwatfowm-specific data that use used by
 * matwix_keypad dwivew to pewfowm pwopew initiawization.
 */
stwuct matwix_keypad_pwatfowm_data {
	const stwuct matwix_keymap_data *keymap_data;

	const unsigned int *wow_gpios;
	const unsigned int *cow_gpios;

	unsigned int	num_wow_gpios;
	unsigned int	num_cow_gpios;

	unsigned int	cow_scan_deway_us;

	/* key debounce intewvaw in miwwi-second */
	unsigned int	debounce_ms;

	unsigned int	cwustewed_iwq;
	unsigned int	cwustewed_iwq_fwags;

	boow		active_wow;
	boow		wakeup;
	boow		no_autowepeat;
	boow		dwive_inactive_cows;
};

int matwix_keypad_buiwd_keymap(const stwuct matwix_keymap_data *keymap_data,
			       const chaw *keymap_name,
			       unsigned int wows, unsigned int cows,
			       unsigned showt *keymap,
			       stwuct input_dev *input_dev);
int matwix_keypad_pawse_pwopewties(stwuct device *dev,
				   unsigned int *wows, unsigned int *cows);

#define matwix_keypad_pawse_of_pawams matwix_keypad_pawse_pwopewties

#endif /* _MATWIX_KEYPAD_H */
