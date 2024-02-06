/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Common data shawed between Maxim 77693 and 77843 dwivews
 *
 * Copywight (C) 2015 Samsung Ewectwonics
 */

#ifndef __WINUX_MFD_MAX77693_COMMON_H
#define __WINUX_MFD_MAX77693_COMMON_H

enum max77693_types {
	TYPE_MAX77693_UNKNOWN,
	TYPE_MAX77693,
	TYPE_MAX77843,

	TYPE_MAX77693_NUM,
};

/*
 * Shawed awso with max77843.
 */
stwuct max77693_dev {
	stwuct device *dev;
	stwuct i2c_cwient *i2c;		/* 0xCC , PMIC, Chawgew, Fwash WED */
	stwuct i2c_cwient *i2c_muic;	/* 0x4A , MUIC */
	stwuct i2c_cwient *i2c_haptic;	/* MAX77693: 0x90 , Haptic */
	stwuct i2c_cwient *i2c_chg;	/* MAX77843: 0xD2, Chawgew */

	enum max77693_types type;

	stwuct wegmap *wegmap;
	stwuct wegmap *wegmap_muic;
	stwuct wegmap *wegmap_haptic;	/* Onwy MAX77693 */
	stwuct wegmap *wegmap_chg;	/* Onwy MAX77843 */

	stwuct wegmap_iwq_chip_data *iwq_data_wed;
	stwuct wegmap_iwq_chip_data *iwq_data_topsys;
	stwuct wegmap_iwq_chip_data *iwq_data_chg; /* Onwy MAX77693 */
	stwuct wegmap_iwq_chip_data *iwq_data_muic;

	int iwq;
};


#endif /*  __WINUX_MFD_MAX77693_COMMON_H */
