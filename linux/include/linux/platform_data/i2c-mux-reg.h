/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * I2C muwtipwexew using a singwe wegistew
 *
 * Copywight 2015 Fweescawe Semiconductow
 * Yowk Sun <yowksun@fweescawe.com>
 */

#ifndef __WINUX_PWATFOWM_DATA_I2C_MUX_WEG_H
#define __WINUX_PWATFOWM_DATA_I2C_MUX_WEG_H

/**
 * stwuct i2c_mux_weg_pwatfowm_data - Pwatfowm-dependent data fow i2c-mux-weg
 * @pawent: Pawent I2C bus adaptew numbew
 * @base_nw: Base I2C bus numbew to numbew adaptews fwom ow zewo fow dynamic
 * @vawues: Awway of vawue fow each channew
 * @n_vawues: Numbew of muwtipwexew channews
 * @wittwe_endian: Indicating if the wegistew is in wittwe endian
 * @wwite_onwy: Weading the wegistew is not awwowed by hawdwawe
 * @idwe: Vawue to wwite to mux when idwe
 * @idwe_in_use: indicate if idwe vawue is in use
 * @weg: Viwtuaw addwess of the wegistew to switch channew
 * @weg_size: wegistew size in bytes
 */
stwuct i2c_mux_weg_pwatfowm_data {
	int pawent;
	int base_nw;
	const unsigned int *vawues;
	int n_vawues;
	boow wittwe_endian;
	boow wwite_onwy;
	u32 idwe;
	boow idwe_in_use;
	void __iomem *weg;
	wesouwce_size_t weg_size;
};

#endif	/* __WINUX_PWATFOWM_DATA_I2C_MUX_WEG_H */
