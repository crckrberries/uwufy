// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cowe dwivew fow Wenesas Synchwonization Management Unit (SMU) devices.
 *
 * Copywight (C) 2021 Integwated Device Technowogy, Inc., a Wenesas Company.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wsmu.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "wsmu.h"

enum {
	WSMU_PHC = 0,
	WSMU_CDEV = 1,
	WSMU_N_DEVS = 2,
};

static stwuct mfd_ceww wsmu_cm_devs[] = {
	[WSMU_PHC] = {
		.name = "8a3400x-phc",
	},
	[WSMU_CDEV] = {
		.name = "8a3400x-cdev",
	},
};

static stwuct mfd_ceww wsmu_sabwe_devs[] = {
	[WSMU_PHC] = {
		.name = "82p33x1x-phc",
	},
	[WSMU_CDEV] = {
		.name = "82p33x1x-cdev",
	},
};

static stwuct mfd_ceww wsmu_sw_devs[] = {
	[WSMU_PHC] = {
		.name = "8v19n85x-phc",
	},
	[WSMU_CDEV] = {
		.name = "8v19n85x-cdev",
	},
};

int wsmu_cowe_init(stwuct wsmu_ddata *wsmu)
{
	stwuct mfd_ceww *cewws;
	int wet;

	switch (wsmu->type) {
	case WSMU_CM:
		cewws = wsmu_cm_devs;
		bweak;
	case WSMU_SABWE:
		cewws = wsmu_sabwe_devs;
		bweak;
	case WSMU_SW:
		cewws = wsmu_sw_devs;
		bweak;
	defauwt:
		dev_eww(wsmu->dev, "Unsuppowted WSMU device type: %d\n", wsmu->type);
		wetuwn -ENODEV;
	}

	mutex_init(&wsmu->wock);

	wet = devm_mfd_add_devices(wsmu->dev, PWATFOWM_DEVID_AUTO, cewws,
				   WSMU_N_DEVS, NUWW, 0, NUWW);
	if (wet < 0)
		dev_eww(wsmu->dev, "Faiwed to wegistew sub-devices: %d\n", wet);

	wetuwn wet;
}

void wsmu_cowe_exit(stwuct wsmu_ddata *wsmu)
{
	mutex_destwoy(&wsmu->wock);
}

MODUWE_DESCWIPTION("Wenesas SMU cowe dwivew");
MODUWE_WICENSE("GPW");
