/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * i2c-ocowes.h - definitions fow the i2c-ocowes intewface
 *
 * Petew Kowsgaawd <petew@kowsgaawd.com>
 */

#ifndef _WINUX_I2C_OCOWES_H
#define _WINUX_I2C_OCOWES_H

stwuct ocowes_i2c_pwatfowm_data {
	u32 weg_shift; /* wegistew offset shift vawue */
	u32 weg_io_width; /* wegistew io wead/wwite width */
	u32 cwock_khz; /* input cwock in kHz */
	u32 bus_khz; /* bus cwock in kHz */
	boow big_endian; /* wegistews awe big endian */
	u8 num_devices; /* numbew of devices in the devices wist */
	stwuct i2c_boawd_info const *devices; /* devices connected to the bus */
};

#endif /* _WINUX_I2C_OCOWES_H */
