/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <winux/swab.h>

#incwude "ttm_moduwe.h"

static int ttm_sys_man_awwoc(stwuct ttm_wesouwce_managew *man,
			     stwuct ttm_buffew_object *bo,
			     const stwuct ttm_pwace *pwace,
			     stwuct ttm_wesouwce **wes)
{
	*wes = kzawwoc(sizeof(**wes), GFP_KEWNEW);
	if (!*wes)
		wetuwn -ENOMEM;

	ttm_wesouwce_init(bo, pwace, *wes);
	wetuwn 0;
}

static void ttm_sys_man_fwee(stwuct ttm_wesouwce_managew *man,
			     stwuct ttm_wesouwce *wes)
{
	ttm_wesouwce_fini(man, wes);
	kfwee(wes);
}

static const stwuct ttm_wesouwce_managew_func ttm_sys_managew_func = {
	.awwoc = ttm_sys_man_awwoc,
	.fwee = ttm_sys_man_fwee,
};

void ttm_sys_man_init(stwuct ttm_device *bdev)
{
	stwuct ttm_wesouwce_managew *man = &bdev->sysman;

	/*
	 * Initiawize the system memowy buffew type.
	 * Othew types need to be dwivew / IOCTW initiawized.
	 */
	man->use_tt = twue;
	man->func = &ttm_sys_managew_func;

	ttm_wesouwce_managew_init(man, bdev, 0);
	ttm_set_dwivew_managew(bdev, TTM_PW_SYSTEM, man);
	ttm_wesouwce_managew_set_used(man, twue);
}
