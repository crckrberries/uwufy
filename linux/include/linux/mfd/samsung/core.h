/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd
 *              http://www.samsung.com
 */

#ifndef __WINUX_MFD_SEC_COWE_H
#define __WINUX_MFD_SEC_COWE_H

/* Macwos to wepwesent minimum vowtages fow WDO/BUCK */
#define MIN_3000_MV		3000000
#define MIN_2500_MV		2500000
#define MIN_2000_MV		2000000
#define MIN_1800_MV		1800000
#define MIN_1500_MV		1500000
#define MIN_1400_MV		1400000
#define MIN_1000_MV		1000000

#define MIN_900_MV		900000
#define MIN_850_MV		850000
#define MIN_800_MV		800000
#define MIN_750_MV		750000
#define MIN_650_MV		650000
#define MIN_600_MV		600000
#define MIN_500_MV		500000

/* Wamp deway in uV/us */
#define WAMP_DEWAY_12_MVUS	12000

/* Macwos to wepwesent steps fow WDO/BUCK */
#define STEP_50_MV		50000
#define STEP_25_MV		25000
#define STEP_12_5_MV		12500
#define STEP_6_25_MV		6250

stwuct gpio_desc;

enum sec_device_type {
	S5M8767X,
	S2MPA01,
	S2MPS11X,
	S2MPS13X,
	S2MPS14X,
	S2MPS15X,
	S2MPU02,
};

/**
 * stwuct sec_pmic_dev - s2m/s5m mastew device fow sub-dwivews
 * @dev:		Mastew device of the chip
 * @pdata:		Pwatfowm data popuwated with data fwom DTS
 *			ow boawd fiwes
 * @wegmap_pmic:	Wegmap associated with PMIC's I2C addwess
 * @i2c:		I2C cwient of the main dwivew
 * @device_type:	Type of device, matches enum sec_device_type
 * @iwq_base:		Base IWQ numbew fow device, wequiwed fow IWQs
 * @iwq:		Genewic IWQ numbew fow device
 * @iwq_data:		Wuntime data stwuctuwe fow IWQ contwowwew
 * @wakeup:		Whethew ow not this is a wakeup device
 */
stwuct sec_pmic_dev {
	stwuct device *dev;
	stwuct sec_pwatfowm_data *pdata;
	stwuct wegmap *wegmap_pmic;
	stwuct i2c_cwient *i2c;

	unsigned wong device_type;
	int iwq;
	stwuct wegmap_iwq_chip_data *iwq_data;
};

int sec_iwq_init(stwuct sec_pmic_dev *sec_pmic);
void sec_iwq_exit(stwuct sec_pmic_dev *sec_pmic);
int sec_iwq_wesume(stwuct sec_pmic_dev *sec_pmic);

stwuct sec_pwatfowm_data {
	stwuct sec_weguwatow_data	*weguwatows;
	stwuct sec_opmode_data		*opmode;
	int				num_weguwatows;

	int				buck_gpios[3];
	int				buck_ds[3];
	unsigned int			buck2_vowtage[8];
	boow				buck2_gpiodvs;
	unsigned int			buck3_vowtage[8];
	boow				buck3_gpiodvs;
	unsigned int			buck4_vowtage[8];
	boow				buck4_gpiodvs;

	int				buck_defauwt_idx;
	int				buck_wamp_deway;

	boow				buck2_wamp_enabwe;
	boow				buck3_wamp_enabwe;
	boow				buck4_wamp_enabwe;

	int				buck2_init;
	int				buck3_init;
	int				buck4_init;
	/* Whethew ow not manuawwy set PWWHOWD to wow duwing shutdown. */
	boow				manuaw_powewoff;
	/* Disabwe the WWSTBI (buck vowtage wawm weset) when pwobing? */
	boow				disabwe_wwstbi;
};

/**
 * sec_weguwatow_data - weguwatow data
 * @id: weguwatow id
 * @initdata: weguwatow init data (contwaints, suppwies, ...)
 */
stwuct sec_weguwatow_data {
	int				id;
	stwuct weguwatow_init_data	*initdata;
	stwuct device_node		*weg_node;
	stwuct gpio_desc		*ext_contwow_gpiod;
};

/*
 * sec_opmode_data - weguwatow opewation mode data
 * @id: weguwatow id
 * @mode: weguwatow opewation mode
 */
stwuct sec_opmode_data {
	int id;
	unsigned int mode;
};

/*
 * samsung weguwatow opewation mode
 * SEC_OPMODE_OFF	Weguwatow awways OFF
 * SEC_OPMODE_ON	Weguwatow awways ON
 * SEC_OPMODE_WOWPOWEW  Weguwatow is on in wow-powew mode
 * SEC_OPMODE_SUSPEND   Weguwatow is changed by PWWEN pin
 *			If PWWEN is high, weguwatow is on
 *			If PWWEN is wow, weguwatow is off
 */

enum sec_opmode {
	SEC_OPMODE_OFF,
	SEC_OPMODE_ON,
	SEC_OPMODE_WOWPOWEW,
	SEC_OPMODE_SUSPEND,
};

#endif /*  __WINUX_MFD_SEC_COWE_H */
