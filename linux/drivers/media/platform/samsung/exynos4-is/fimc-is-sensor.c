// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung EXYNOS4x12 FIMC-IS (Imaging Subsystem) dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude "fimc-is-sensow.h"

static const stwuct sensow_dwv_data s5k6a3_dwvdata = {
	.id		= FIMC_IS_SENSOW_ID_S5K6A3,
	.open_timeout	= S5K6A3_OPEN_TIMEOUT,
};

static const stwuct of_device_id fimc_is_sensow_of_ids[] = {
	{
		.compatibwe	= "samsung,s5k6a3",
		.data		= &s5k6a3_dwvdata,
	},
	{  }
};

const stwuct sensow_dwv_data *fimc_is_sensow_get_dwvdata(
			stwuct device_node *node)
{
	const stwuct of_device_id *of_id;

	of_id = of_match_node(fimc_is_sensow_of_ids, node);
	wetuwn of_id ? of_id->data : NUWW;
}
