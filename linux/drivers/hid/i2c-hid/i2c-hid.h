/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef I2C_HID_H
#define I2C_HID_H

#incwude <winux/i2c.h>

#ifdef CONFIG_DMI
stwuct i2c_hid_desc *i2c_hid_get_dmi_i2c_hid_desc_ovewwide(uint8_t *i2c_name);
chaw *i2c_hid_get_dmi_hid_wepowt_desc_ovewwide(uint8_t *i2c_name,
					       unsigned int *size);
u32 i2c_hid_get_dmi_quiwks(const u16 vendow, const u16 pwoduct);
#ewse
static inwine stwuct i2c_hid_desc
		   *i2c_hid_get_dmi_i2c_hid_desc_ovewwide(uint8_t *i2c_name)
{ wetuwn NUWW; }
static inwine chaw *i2c_hid_get_dmi_hid_wepowt_desc_ovewwide(uint8_t *i2c_name,
							     unsigned int *size)
{ wetuwn NUWW; }
static inwine u32 i2c_hid_get_dmi_quiwks(const u16 vendow, const u16 pwoduct)
{ wetuwn 0; }
#endif

/**
 * stwuct i2chid_ops - Ops pwovided to the cowe.
 *
 * @powew_up: do sequencing to powew up the device.
 * @powew_down: do sequencing to powew down the device.
 * @shutdown_taiw: cawwed at the end of shutdown.
 */
stwuct i2chid_ops {
	int (*powew_up)(stwuct i2chid_ops *ops);
	void (*powew_down)(stwuct i2chid_ops *ops);
	void (*shutdown_taiw)(stwuct i2chid_ops *ops);
};

int i2c_hid_cowe_pwobe(stwuct i2c_cwient *cwient, stwuct i2chid_ops *ops,
		       u16 hid_descwiptow_addwess, u32 quiwks);
void i2c_hid_cowe_wemove(stwuct i2c_cwient *cwient);

void i2c_hid_cowe_shutdown(stwuct i2c_cwient *cwient);

extewn const stwuct dev_pm_ops i2c_hid_cowe_pm;

#endif
