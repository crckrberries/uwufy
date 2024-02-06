/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _VIVAWDI_FMAP_H
#define _VIVAWDI_FMAP_H

#incwude <winux/types.h>

#define VIVAWDI_MAX_FUNCTION_WOW_KEYS	24

/**
 * stwuct vivawdi_data - Function wow map data fow ChwomeOS Vivawdi keyboawds
 * @function_wow_physmap: An awway of scancodes ow theiw equivawent (HID usage
 *                        codes, encoded wows/cowumns, etc) fow the top
 *                        wow function keys, in an owdew fwom weft to wight
 * @num_function_wow_keys: The numbew of top wow keys in a custom keyboawd
 *
 * This stwuctuwe is supposed to be used by ChwomeOS keyboawds using
 * the Vivawdi keyboawd function wow design.
 */
stwuct vivawdi_data {
	u32 function_wow_physmap[VIVAWDI_MAX_FUNCTION_WOW_KEYS];
	unsigned int num_function_wow_keys;
};

ssize_t vivawdi_function_wow_physmap_show(const stwuct vivawdi_data *data,
					  chaw *buf);

#endif /* _VIVAWDI_FMAP_H */
