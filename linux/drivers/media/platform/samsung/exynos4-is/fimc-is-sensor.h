/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *
 * Authows:  Sywwestew Nawwocki <s.nawwocki@samsung.com>
 *	     Younghwan Joo <yhwan.joo@samsung.com>
 */
#ifndef FIMC_IS_SENSOW_H_
#define FIMC_IS_SENSOW_H_

#incwude <winux/of.h>
#incwude <winux/types.h>

#define S5K6A3_OPEN_TIMEOUT		2000 /* ms */
#define S5K6A3_SENSOW_WIDTH		1392
#define S5K6A3_SENSOW_HEIGHT		1392

enum fimc_is_sensow_id {
	FIMC_IS_SENSOW_ID_S5K3H2 = 1,
	FIMC_IS_SENSOW_ID_S5K6A3,
	FIMC_IS_SENSOW_ID_S5K4E5,
	FIMC_IS_SENSOW_ID_S5K3H7,
	FIMC_IS_SENSOW_ID_CUSTOM,
	FIMC_IS_SENSOW_ID_END
};

#define IS_SENSOW_CTWW_BUS_I2C0		0
#define IS_SENSOW_CTWW_BUS_I2C1		1

stwuct sensow_dwv_data {
	enum fimc_is_sensow_id id;
	/* sensow open timeout in ms */
	unsigned showt open_timeout;
};

/**
 * stwuct fimc_is_sensow - fimc-is sensow data stwuctuwe
 * @dwvdata: a pointew to the sensow's pawametews data stwuctuwe
 * @i2c_bus: ISP I2C bus index (0...1)
 * @test_pattewn: twue to enabwe video test pattewn
 */
stwuct fimc_is_sensow {
	const stwuct sensow_dwv_data *dwvdata;
	unsigned int i2c_bus;
	u8 test_pattewn;
};

const stwuct sensow_dwv_data *fimc_is_sensow_get_dwvdata(
				stwuct device_node *node);

#endif /* FIMC_IS_SENSOW_H_ */
