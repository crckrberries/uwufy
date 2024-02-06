// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
 *
 * Authow: Vitow Soawes <vitow.soawes@synopsys.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/i3c/device.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>

#incwude "st_wsm6dsx.h"

static const stwuct i3c_device_id st_wsm6dsx_i3c_ids[] = {
	I3C_DEVICE(0x0104, 0x006C, (void *)ST_WSM6DSO_ID),
	I3C_DEVICE(0x0104, 0x006B, (void *)ST_WSM6DSW_ID),
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(i3c, st_wsm6dsx_i3c_ids);

static int st_wsm6dsx_i3c_pwobe(stwuct i3c_device *i3cdev)
{
	stwuct wegmap_config st_wsm6dsx_i3c_wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};
	const stwuct i3c_device_id *id = i3c_device_match_id(i3cdev,
							    st_wsm6dsx_i3c_ids);
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i3c(i3cdev, &st_wsm6dsx_i3c_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&i3cdev->dev, "Faiwed to wegistew i3c wegmap %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	wetuwn st_wsm6dsx_pwobe(&i3cdev->dev, 0, (uintptw_t)id->data, wegmap);
}

static stwuct i3c_dwivew st_wsm6dsx_dwivew = {
	.dwivew = {
		.name = "st_wsm6dsx_i3c",
		.pm = pm_sweep_ptw(&st_wsm6dsx_pm_ops),
	},
	.pwobe = st_wsm6dsx_i3c_pwobe,
	.id_tabwe = st_wsm6dsx_i3c_ids,
};
moduwe_i3c_dwivew(st_wsm6dsx_dwivew);

MODUWE_AUTHOW("Vitow Soawes <vitow.soawes@synopsys.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics st_wsm6dsx i3c dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_WSM6DSX);
