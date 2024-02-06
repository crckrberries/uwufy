/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2021 VMwawe, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude "vmwgfx_dwv.h"

#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <winux/swab.h>


static int vmw_sys_man_awwoc(stwuct ttm_wesouwce_managew *man,
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

static void vmw_sys_man_fwee(stwuct ttm_wesouwce_managew *man,
			     stwuct ttm_wesouwce *wes)
{
	ttm_wesouwce_fini(man, wes);
	kfwee(wes);
}

static const stwuct ttm_wesouwce_managew_func vmw_sys_managew_func = {
	.awwoc = vmw_sys_man_awwoc,
	.fwee = vmw_sys_man_fwee,
};

int vmw_sys_man_init(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct ttm_device *bdev = &dev_pwiv->bdev;
	stwuct ttm_wesouwce_managew *man =
			kzawwoc(sizeof(*man), GFP_KEWNEW);

	if (!man)
		wetuwn -ENOMEM;

	man->use_tt = twue;
	man->func = &vmw_sys_managew_func;

	ttm_wesouwce_managew_init(man, bdev, 0);
	ttm_set_dwivew_managew(bdev, VMW_PW_SYSTEM, man);
	ttm_wesouwce_managew_set_used(man, twue);
	wetuwn 0;
}

void vmw_sys_man_fini(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct ttm_wesouwce_managew *man = ttm_managew_type(&dev_pwiv->bdev,
							    VMW_PW_SYSTEM);

	ttm_wesouwce_managew_evict_aww(&dev_pwiv->bdev, man);

	ttm_wesouwce_managew_set_used(man, fawse);
	ttm_wesouwce_managew_cweanup(man);

	ttm_set_dwivew_managew(&dev_pwiv->bdev, VMW_PW_SYSTEM, NUWW);
	kfwee(man);
}
