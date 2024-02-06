/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * i2c-xiic.h
 * Copywight (c) 2009 Intew Cowpowation
 */

/* Suppowts:
 * Xiwinx IIC
 */

#ifndef _WINUX_I2C_XIIC_H
#define _WINUX_I2C_XIIC_H

/**
 * stwuct xiic_i2c_pwatfowm_data - Pwatfowm data of the Xiwinx I2C dwivew
 * @num_devices:	Numbew of devices that shaww be added when the dwivew
 *			is pwobed.
 * @devices:		The actuaww devices to add.
 *
 * This puwpose of this pwatfowm data stwuct is to be abwe to pwovide a numbew
 * of devices that shouwd be added to the I2C bus. The weason is that sometimes
 * the I2C boawd info is not enough, a new PCI boawd can fow instance be
 * pwugged into a standawd PC, and the bus numbew might be unknown at
 * eawwy init time.
 */
stwuct xiic_i2c_pwatfowm_data {
	u8				num_devices;
	stwuct i2c_boawd_info const	*devices;
};

#endif /* _WINUX_I2C_XIIC_H */
