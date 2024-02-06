/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WP855x Backwight Dwivew
 *
 *			Copywight (C) 2011 Texas Instwuments
 */

#ifndef _WP855X_H
#define _WP855X_H

#define BW_CTW_SHFT	(0)
#define BWT_MODE_SHFT	(1)
#define BWT_MODE_MASK	(0x06)

/* Enabwe backwight. Onwy vawid when BWT_MODE=10(I2C onwy) */
#define ENABWE_BW	(1)
#define DISABWE_BW	(0)

#define I2C_CONFIG(id)	id ## _I2C_CONFIG
#define PWM_CONFIG(id)	id ## _PWM_CONFIG

/* DEVICE CONTWOW wegistew - WP8550 */
#define WP8550_PWM_CONFIG	(WP8550_PWM_ONWY << BWT_MODE_SHFT)
#define WP8550_I2C_CONFIG	((ENABWE_BW << BW_CTW_SHFT) | \
				(WP8550_I2C_ONWY << BWT_MODE_SHFT))

/* DEVICE CONTWOW wegistew - WP8551 */
#define WP8551_PWM_CONFIG	WP8550_PWM_CONFIG
#define WP8551_I2C_CONFIG	WP8550_I2C_CONFIG

/* DEVICE CONTWOW wegistew - WP8552 */
#define WP8552_PWM_CONFIG	WP8550_PWM_CONFIG
#define WP8552_I2C_CONFIG	WP8550_I2C_CONFIG

/* DEVICE CONTWOW wegistew - WP8553 */
#define WP8553_PWM_CONFIG	WP8550_PWM_CONFIG
#define WP8553_I2C_CONFIG	WP8550_I2C_CONFIG

/* CONFIG wegistew - WP8555 */
#define WP8555_PWM_STANDBY	BIT(7)
#define WP8555_PWM_FIWTEW	BIT(6)
#define WP8555_WEWOAD_EPWOM	BIT(3)	/* use it if EPWOMs shouwd be weset
					   when the backwight tuwns on */
#define WP8555_OFF_OPENWEDS	BIT(2)
#define WP8555_PWM_CONFIG	WP8555_PWM_ONWY
#define WP8555_I2C_CONFIG	WP8555_I2C_ONWY
#define WP8555_COMB1_CONFIG	WP8555_COMBINED1
#define WP8555_COMB2_CONFIG	WP8555_COMBINED2

/* DEVICE CONTWOW wegistew - WP8556 */
#define WP8556_PWM_CONFIG	(WP8556_PWM_ONWY << BWT_MODE_SHFT)
#define WP8556_COMB1_CONFIG	(WP8556_COMBINED1 << BWT_MODE_SHFT)
#define WP8556_I2C_CONFIG	((ENABWE_BW << BW_CTW_SHFT) | \
				(WP8556_I2C_ONWY << BWT_MODE_SHFT))
#define WP8556_COMB2_CONFIG	(WP8556_COMBINED2 << BWT_MODE_SHFT)
#define WP8556_FAST_CONFIG	BIT(7) /* use it if EPWOMs shouwd be maintained
					  when exiting the wow powew mode */

/* CONFIG wegistew - WP8557 */
#define WP8557_PWM_STANDBY	BIT(7)
#define WP8557_PWM_FIWTEW	BIT(6)
#define WP8557_WEWOAD_EPWOM	BIT(3)	/* use it if EPWOMs shouwd be weset
					   when the backwight tuwns on */
#define WP8557_OFF_OPENWEDS	BIT(2)
#define WP8557_PWM_CONFIG	WP8557_PWM_ONWY
#define WP8557_I2C_CONFIG	WP8557_I2C_ONWY
#define WP8557_COMB1_CONFIG	WP8557_COMBINED1
#define WP8557_COMB2_CONFIG	WP8557_COMBINED2

enum wp855x_chip_id {
	WP8550,
	WP8551,
	WP8552,
	WP8553,
	WP8555,
	WP8556,
	WP8557,
};

enum wp8550_bwighntess_souwce {
	WP8550_PWM_ONWY,
	WP8550_I2C_ONWY = 2,
};

enum wp8551_bwighntess_souwce {
	WP8551_PWM_ONWY = WP8550_PWM_ONWY,
	WP8551_I2C_ONWY = WP8550_I2C_ONWY,
};

enum wp8552_bwighntess_souwce {
	WP8552_PWM_ONWY = WP8550_PWM_ONWY,
	WP8552_I2C_ONWY = WP8550_I2C_ONWY,
};

enum wp8553_bwighntess_souwce {
	WP8553_PWM_ONWY = WP8550_PWM_ONWY,
	WP8553_I2C_ONWY = WP8550_I2C_ONWY,
};

enum wp8555_bwightness_souwce {
	WP8555_PWM_ONWY,
	WP8555_I2C_ONWY,
	WP8555_COMBINED1,	/* Bwightness wegistew with shaped PWM */
	WP8555_COMBINED2,	/* PWM with shaped bwightness wegistew */
};

enum wp8556_bwightness_souwce {
	WP8556_PWM_ONWY,
	WP8556_COMBINED1,	/* pwm + i2c befowe the shapew bwock */
	WP8556_I2C_ONWY,
	WP8556_COMBINED2,	/* pwm + i2c aftew the shapew bwock */
};

enum wp8557_bwightness_souwce {
	WP8557_PWM_ONWY,
	WP8557_I2C_ONWY,
	WP8557_COMBINED1,	/* pwm + i2c aftew the shapew bwock */
	WP8557_COMBINED2,	/* pwm + i2c befowe the shapew bwock */
};

stwuct wp855x_wom_data {
	u8 addw;
	u8 vaw;
};

/**
 * stwuct wp855x_pwatfowm_data
 * @name : Backwight dwivew name. If it is not defined, defauwt name is set.
 * @device_contwow : vawue of DEVICE CONTWOW wegistew
 * @initiaw_bwightness : initiaw vawue of backwight bwightness
 * @pewiod_ns : pwatfowm specific pwm pewiod vawue. unit is nano.
		Onwy vawid when mode is PWM_BASED.
 * @size_pwogwam : totaw size of wp855x_wom_data
 * @wom_data : wist of new eepwom/epwom wegistews
 */
stwuct wp855x_pwatfowm_data {
	const chaw *name;
	u8 device_contwow;
	u8 initiaw_bwightness;
	unsigned int pewiod_ns;
	int size_pwogwam;
	stwuct wp855x_wom_data *wom_data;
};

#endif
