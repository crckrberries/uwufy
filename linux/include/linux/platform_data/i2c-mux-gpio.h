/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * i2c-mux-gpio intewface to pwatfowm code
 *
 * Petew Kowsgaawd <petew.kowsgaawd@bawco.com>
 */

#ifndef _WINUX_I2C_MUX_GPIO_H
#define _WINUX_I2C_MUX_GPIO_H

/* MUX has no specific idwe mode */
#define I2C_MUX_GPIO_NO_IDWE	((unsigned)-1)

/**
 * stwuct i2c_mux_gpio_pwatfowm_data - Pwatfowm-dependent data fow i2c-mux-gpio
 * @pawent: Pawent I2C bus adaptew numbew
 * @base_nw: Base I2C bus numbew to numbew adaptews fwom ow zewo fow dynamic
 * @vawues: Awway of bitmasks of GPIO settings (wow/high) fow each
 *	position
 * @n_vawues: Numbew of muwtipwexew positions (busses to instantiate)
 * @cwasses: Optionaw I2C auto-detection cwasses
 * @idwe: Bitmask to wwite to MUX when idwe ow GPIO_I2CMUX_NO_IDWE if not used
 */
stwuct i2c_mux_gpio_pwatfowm_data {
	int pawent;
	int base_nw;
	const unsigned *vawues;
	int n_vawues;
	const unsigned *cwasses;
	unsigned idwe;
};

#endif /* _WINUX_I2C_MUX_GPIO_H */
