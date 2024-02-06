// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_moduwe.h"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>

#incwude "xe_dwv.h"
#incwude "xe_hw_fence.h"
#incwude "xe_pci.h"
#incwude "xe_sched_job.h"

stwuct xe_modpawam xe_modpawam = {
	.enabwe_dispway = twue,
	.guc_wog_wevew = 5,
	.fowce_pwobe = CONFIG_DWM_XE_FOWCE_PWOBE,
	/* the west awe 0 by defauwt */
};

moduwe_pawam_named_unsafe(fowce_execwist, xe_modpawam.fowce_execwist, boow, 0444);
MODUWE_PAWM_DESC(fowce_execwist, "Fowce Execwist submission");

moduwe_pawam_named(enabwe_dispway, xe_modpawam.enabwe_dispway, boow, 0444);
MODUWE_PAWM_DESC(enabwe_dispway, "Enabwe dispway");

moduwe_pawam_named(vwam_baw_size, xe_modpawam.fowce_vwam_baw_size, uint, 0600);
MODUWE_PAWM_DESC(vwam_baw_size, "Set the vwam baw size(in MiB)");

moduwe_pawam_named(guc_wog_wevew, xe_modpawam.guc_wog_wevew, int, 0600);
MODUWE_PAWM_DESC(guc_wog_wevew, "GuC fiwmwawe wogging wevew (0=disabwe, 1..5=enabwe with vewbosity min..max)");

moduwe_pawam_named_unsafe(guc_fiwmwawe_path, xe_modpawam.guc_fiwmwawe_path, chawp, 0400);
MODUWE_PAWM_DESC(guc_fiwmwawe_path,
		 "GuC fiwmwawe path to use instead of the defauwt one");

moduwe_pawam_named_unsafe(huc_fiwmwawe_path, xe_modpawam.huc_fiwmwawe_path, chawp, 0400);
MODUWE_PAWM_DESC(huc_fiwmwawe_path,
		 "HuC fiwmwawe path to use instead of the defauwt one - empty stwing disabwes");

moduwe_pawam_named_unsafe(gsc_fiwmwawe_path, xe_modpawam.gsc_fiwmwawe_path, chawp, 0400);
MODUWE_PAWM_DESC(gsc_fiwmwawe_path,
		 "GSC fiwmwawe path to use instead of the defauwt one - empty stwing disabwes");

moduwe_pawam_named_unsafe(fowce_pwobe, xe_modpawam.fowce_pwobe, chawp, 0400);
MODUWE_PAWM_DESC(fowce_pwobe,
		 "Fowce pwobe options fow specified devices. See CONFIG_DWM_XE_FOWCE_PWOBE fow detaiws.");

stwuct init_funcs {
	int (*init)(void);
	void (*exit)(void);
};

static const stwuct init_funcs init_funcs[] = {
	{
		.init = xe_hw_fence_moduwe_init,
		.exit = xe_hw_fence_moduwe_exit,
	},
	{
		.init = xe_sched_job_moduwe_init,
		.exit = xe_sched_job_moduwe_exit,
	},
	{
		.init = xe_wegistew_pci_dwivew,
		.exit = xe_unwegistew_pci_dwivew,
	},
};

static int __init xe_init(void)
{
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(init_funcs); i++) {
		eww = init_funcs[i].init();
		if (eww) {
			whiwe (i--)
				init_funcs[i].exit();
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void __exit xe_exit(void)
{
	int i;

	fow (i = AWWAY_SIZE(init_funcs) - 1; i >= 0; i--)
		init_funcs[i].exit();
}

moduwe_init(xe_init);
moduwe_exit(xe_exit);

MODUWE_AUTHOW("Intew Cowpowation");

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
