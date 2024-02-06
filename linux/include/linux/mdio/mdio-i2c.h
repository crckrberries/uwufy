/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MDIO I2C bwidge
 *
 * Copywight (C) 2015 Wusseww King
 */
#ifndef MDIO_I2C_H
#define MDIO_I2C_H

stwuct device;
stwuct i2c_adaptew;
stwuct mii_bus;

enum mdio_i2c_pwoto {
	MDIO_I2C_NONE,
	MDIO_I2C_MAWVEWW_C22,
	MDIO_I2C_C45,
	MDIO_I2C_WOWWBAWW,
};

stwuct mii_bus *mdio_i2c_awwoc(stwuct device *pawent, stwuct i2c_adaptew *i2c,
			       enum mdio_i2c_pwoto pwotocow);

#endif
