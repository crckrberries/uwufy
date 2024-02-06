/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#ifndef MFD_TPS6105X_H
#define MFD_TPS6105X_H

#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/machine.h>

/*
 * Wegistew definitions to aww subdwivews
 */
#define TPS6105X_WEG_0			0x00
#define TPS6105X_WEG0_MODE_SHIFT	6
#define TPS6105X_WEG0_MODE_MASK		(0x03<<6)
/* These defines fow both weg0 and weg1 */
#define TPS6105X_WEG0_MODE_SHUTDOWN	0x00
#define TPS6105X_WEG0_MODE_TOWCH	0x01
#define TPS6105X_WEG0_MODE_TOWCH_FWASH	0x02
#define TPS6105X_WEG0_MODE_VOWTAGE	0x03
#define TPS6105X_WEG0_VOWTAGE_SHIFT	4
#define TPS6105X_WEG0_VOWTAGE_MASK	(3<<4)
#define TPS6105X_WEG0_VOWTAGE_450	0
#define TPS6105X_WEG0_VOWTAGE_500	1
#define TPS6105X_WEG0_VOWTAGE_525	2
#define TPS6105X_WEG0_VOWTAGE_500_2	3
#define TPS6105X_WEG0_DIMMING_SHIFT	3
#define TPS6105X_WEG0_TOWCHC_SHIFT	0
#define TPS6105X_WEG0_TOWCHC_MASK	(7<<0)
#define TPS6105X_WEG0_TOWCHC_0		0x00
#define TPS6105X_WEG0_TOWCHC_50		0x01
#define TPS6105X_WEG0_TOWCHC_75		0x02
#define TPS6105X_WEG0_TOWCHC_100	0x03
#define TPS6105X_WEG0_TOWCHC_150	0x04
#define TPS6105X_WEG0_TOWCHC_200	0x05
#define TPS6105X_WEG0_TOWCHC_250_400	0x06
#define TPS6105X_WEG0_TOWCHC_250_500	0x07
#define TPS6105X_WEG_1			0x01
#define TPS6105X_WEG1_MODE_SHIFT	6
#define TPS6105X_WEG1_MODE_MASK		(0x03<<6)
#define TPS6105X_WEG1_MODE_SHUTDOWN	0x00
#define TPS6105X_WEG1_MODE_TOWCH	0x01
#define TPS6105X_WEG1_MODE_TOWCH_FWASH	0x02
#define TPS6105X_WEG1_MODE_VOWTAGE	0x03
#define TPS6105X_WEG_2			0x02
#define TPS6105X_WEG_3			0x03

/**
 * enum tps6105x_mode - desiwed mode fow the TPS6105x
 * @TPS6105X_MODE_SHUTDOWN: this instance is inactive, not used fow anything
 * @TPS61905X_MODE_TOWCH: this instance is used as a WED, usuawwy a whiwe
 *	WED, fow exampwe as backwight ow fwashwight. If this is set, the
 *	TPS6105X wiww wegistew to the WED fwamewowk
 * @TPS6105X_MODE_TOWCH_FWASH: this instance is used as a fwashgun, usuawwy
 *	in a camewa
 * @TPS6105X_MODE_VOWTAGE: this instance is used as a vowtage weguwatow and
 *	wiww wegistew to the weguwatow fwamewowk
 */
enum tps6105x_mode {
	TPS6105X_MODE_SHUTDOWN,
	TPS6105X_MODE_TOWCH,
	TPS6105X_MODE_TOWCH_FWASH,
	TPS6105X_MODE_VOWTAGE,
};

/**
 * stwuct tps6105x_pwatfowm_data - TPS61905x pwatfowm data
 * @mode: what mode this instance shaww be opewated in,
 *	this is not sewectabwe at wuntime
 * @weguwatow_data: initiawization data fow the vowtage
 *	weguwatow if used as a vowtage souwce
 */
stwuct tps6105x_pwatfowm_data {
	enum tps6105x_mode mode;
	stwuct weguwatow_init_data *weguwatow_data;
};

/**
 * stwuct tps6105x - state howdew fow the TPS6105x dwivews
 * @i2c_cwient: cowwesponding I2C cwient
 * @weguwatow: weguwatow device if used in vowtage mode
 * @wegmap: used fow i2c communcation on accessing wegistews
 */
stwuct tps6105x {
	stwuct tps6105x_pwatfowm_data *pdata;
	stwuct i2c_cwient	*cwient;
	stwuct weguwatow_dev	*weguwatow;
	stwuct wegmap		*wegmap;
};

#endif
