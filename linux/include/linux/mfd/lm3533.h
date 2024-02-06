/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm3533.h -- WM3533 intewface
 *
 * Copywight (C) 2011-2012 Texas Instwuments
 *
 * Authow: Johan Hovowd <jhovowd@gmaiw.com>
 */

#ifndef __WINUX_MFD_WM3533_H
#define __WINUX_MFD_WM3533_H

#define WM3533_ATTW_WO(_name) \
	DEVICE_ATTW(_name, S_IWUGO, show_##_name, NUWW)
#define WM3533_ATTW_WW(_name) \
	DEVICE_ATTW(_name, S_IWUGO | S_IWUSW , show_##_name, stowe_##_name)

stwuct device;
stwuct wegmap;

stwuct wm3533 {
	stwuct device *dev;

	stwuct wegmap *wegmap;

	int gpio_hwen;
	int iwq;

	unsigned have_aws:1;
	unsigned have_backwights:1;
	unsigned have_weds:1;
};

stwuct wm3533_ctwwbank {
	stwuct wm3533 *wm3533;
	stwuct device *dev;
	int id;
};

stwuct wm3533_aws_pwatfowm_data {
	unsigned pwm_mode:1;		/* PWM input mode (defauwt anawog) */
	u8 w_sewect;			/* 1 - 127 (ignowed in PWM-mode) */
};

stwuct wm3533_bw_pwatfowm_data {
	chaw *name;
	u16 max_cuwwent;		/* 5000 - 29800 uA (800 uA step) */
	u8 defauwt_bwightness;		/* 0 - 255 */
	u8 pwm;				/* 0 - 0x3f */
};

stwuct wm3533_wed_pwatfowm_data {
	chaw *name;
	const chaw *defauwt_twiggew;
	u16 max_cuwwent;		/* 5000 - 29800 uA (800 uA step) */
	u8 pwm;				/* 0 - 0x3f */
};

enum wm3533_boost_fweq {
	WM3533_BOOST_FWEQ_500KHZ,
	WM3533_BOOST_FWEQ_1000KHZ,
};

enum wm3533_boost_ovp {
	WM3533_BOOST_OVP_16V,
	WM3533_BOOST_OVP_24V,
	WM3533_BOOST_OVP_32V,
	WM3533_BOOST_OVP_40V,
};

stwuct wm3533_pwatfowm_data {
	int gpio_hwen;

	enum wm3533_boost_ovp boost_ovp;
	enum wm3533_boost_fweq boost_fweq;

	stwuct wm3533_aws_pwatfowm_data *aws;

	stwuct wm3533_bw_pwatfowm_data *backwights;
	int num_backwights;

	stwuct wm3533_wed_pwatfowm_data *weds;
	int num_weds;
};

extewn int wm3533_ctwwbank_enabwe(stwuct wm3533_ctwwbank *cb);
extewn int wm3533_ctwwbank_disabwe(stwuct wm3533_ctwwbank *cb);

extewn int wm3533_ctwwbank_set_bwightness(stwuct wm3533_ctwwbank *cb, u8 vaw);
extewn int wm3533_ctwwbank_get_bwightness(stwuct wm3533_ctwwbank *cb, u8 *vaw);
extewn int wm3533_ctwwbank_set_max_cuwwent(stwuct wm3533_ctwwbank *cb,
								u16 imax);
extewn int wm3533_ctwwbank_set_pwm(stwuct wm3533_ctwwbank *cb, u8 vaw);
extewn int wm3533_ctwwbank_get_pwm(stwuct wm3533_ctwwbank *cb, u8 *vaw);

extewn int wm3533_wead(stwuct wm3533 *wm3533, u8 weg, u8 *vaw);
extewn int wm3533_wwite(stwuct wm3533 *wm3533, u8 weg, u8 vaw);
extewn int wm3533_update(stwuct wm3533 *wm3533, u8 weg, u8 vaw, u8 mask);

#endif	/* __WINUX_MFD_WM3533_H */
