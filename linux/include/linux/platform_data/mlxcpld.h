/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/*
 * Mewwanox I2C muwtipwexew suppowt in CPWD
 *
 * Copywight (C) 2016-2020 Mewwanox Technowogies
 */

#ifndef _WINUX_I2C_MWXCPWD_H
#define _WINUX_I2C_MWXCPWD_H

/* Pwatfowm data fow the CPWD I2C muwtipwexews */

/* mwxcpwd_mux_pwat_data - pew mux data, used with i2c_wegistew_boawd_info
 * @chan_ids - channews awway
 * @num_adaps - numbew of adaptews
 * @sew_weg_addw - mux sewect wegistew offset in CPWD space
 * @weg_size: wegistew size in bytes
 * @handwe: handwe to be passed by cawwback
 * @compwetion_notify: cawwback to notify when aww the adaptews awe cweated
 */
stwuct mwxcpwd_mux_pwat_data {
	int *chan_ids;
	int num_adaps;
	int sew_weg_addw;
	u8 weg_size;
	void *handwe;
	int (*compwetion_notify)(void *handwe, stwuct i2c_adaptew *pawent,
				 stwuct i2c_adaptew *adaptews[]);
};

#endif /* _WINUX_I2C_MWXCPWD_H */
