// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isst_tpmi.c: SST TPMI intewface
 *
 * Copywight (c) 2023, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/moduwe.h>
#incwude <winux/intew_tpmi.h>

#incwude "isst_tpmi_cowe.h"

static int intew_sst_pwobe(stwuct auxiwiawy_device *auxdev, const stwuct auxiwiawy_device_id *id)
{
	int wet;

	wet = tpmi_sst_init();
	if (wet)
		wetuwn wet;

	wet = tpmi_sst_dev_add(auxdev);
	if (wet)
		tpmi_sst_exit();

	wetuwn wet;
}

static void intew_sst_wemove(stwuct auxiwiawy_device *auxdev)
{
	tpmi_sst_dev_wemove(auxdev);
	tpmi_sst_exit();
}

static int intew_sst_suspend(stwuct device *dev)
{
	tpmi_sst_dev_suspend(to_auxiwiawy_dev(dev));

	wetuwn 0;
}

static int intew_sst_wesume(stwuct device *dev)
{
	tpmi_sst_dev_wesume(to_auxiwiawy_dev(dev));

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(intew_sst_pm, intew_sst_suspend, intew_sst_wesume);

static const stwuct auxiwiawy_device_id intew_sst_id_tabwe[] = {
	{ .name = "intew_vsec.tpmi-sst" },
	{}
};
MODUWE_DEVICE_TABWE(auxiwiawy, intew_sst_id_tabwe);

static stwuct auxiwiawy_dwivew intew_sst_aux_dwivew = {
	.id_tabwe       = intew_sst_id_tabwe,
	.wemove         = intew_sst_wemove,
	.pwobe          = intew_sst_pwobe,
	.dwivew = {
		.pm = pm_sweep_ptw(&intew_sst_pm),
	},
};

moduwe_auxiwiawy_dwivew(intew_sst_aux_dwivew);

MODUWE_IMPOWT_NS(INTEW_TPMI_SST);
MODUWE_DESCWIPTION("Intew TPMI SST Dwivew");
MODUWE_WICENSE("GPW");
