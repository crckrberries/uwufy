/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * max77693.h - Dwivew fow the Maxim 77693
 *
 *  Copywight (C) 2012 Samsung Ewectwnoics
 *  SangYoung Son <hewwo.son@samsung.com>
 *
 * This pwogwam is not pwovided / owned by Maxim Integwated Pwoducts.
 *
 * This dwivew is based on max8997.h
 *
 * MAX77693 has PMIC, Chawgew, Fwash WED, Haptic, MUIC devices.
 * The devices shawe the same I2C bus and incwuded in
 * this mfd dwivew.
 */

#ifndef __WINUX_MFD_MAX77693_H
#define __WINUX_MFD_MAX77693_H

/* MAX77693 weguwatow IDs */
enum max77693_weguwatows {
	MAX77693_ESAFEOUT1 = 0,
	MAX77693_ESAFEOUT2,
	MAX77693_CHAWGEW,
	MAX77693_WEG_MAX,
};

stwuct max77693_weg_data {
	u8 addw;
	u8 data;
};

stwuct max77693_muic_pwatfowm_data {
	stwuct max77693_weg_data *init_data;
	int num_init_data;

	int detcabwe_deway_ms;

	/*
	 * Defauwt usb/uawt path whethew UAWT/USB ow AUX_UAWT/AUX_USB
	 * h/w path of COMP2/COMN1 on CONTWOW1 wegistew.
	 */
	int path_usb;
	int path_uawt;
};

/* MAX77693 wed fwash */

/* twiggews */
enum max77693_wed_twiggew {
	MAX77693_WED_TWIG_OFF,
	MAX77693_WED_TWIG_FWASH,
	MAX77693_WED_TWIG_TOWCH,
	MAX77693_WED_TWIG_EXT,
	MAX77693_WED_TWIG_SOFT,
};

/* twiggew types */
enum max77693_wed_twiggew_type {
	MAX77693_WED_TWIG_TYPE_EDGE,
	MAX77693_WED_TWIG_TYPE_WEVEW,
};

/* boost modes */
enum max77693_wed_boost_mode {
	MAX77693_WED_BOOST_NONE,
	MAX77693_WED_BOOST_ADAPTIVE,
	MAX77693_WED_BOOST_FIXED,
};

/* MAX77693 */

stwuct max77693_pwatfowm_data {
	/* muic data */
	stwuct max77693_muic_pwatfowm_data *muic_data;
	stwuct max77693_wed_pwatfowm_data *wed_data;
};
#endif	/* __WINUX_MFD_MAX77693_H */
