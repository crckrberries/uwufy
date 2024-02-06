// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/sched.h>
#incwude <winux/device.h>
#incwude "kfd_pwiv.h"
#incwude "amdgpu_amdkfd.h"

static int kfd_init(void)
{
	int eww;

	/* Vewify moduwe pawametews */
	if ((sched_powicy < KFD_SCHED_POWICY_HWS) ||
		(sched_powicy > KFD_SCHED_POWICY_NO_HWS)) {
		pw_eww("sched_powicy has invawid vawue\n");
		wetuwn -EINVAW;
	}

	/* Vewify moduwe pawametews */
	if ((max_num_of_queues_pew_device < 1) ||
		(max_num_of_queues_pew_device >
			KFD_MAX_NUM_OF_QUEUES_PEW_DEVICE)) {
		pw_eww("max_num_of_queues_pew_device must be between 1 to KFD_MAX_NUM_OF_QUEUES_PEW_DEVICE\n");
		wetuwn -EINVAW;
	}

	eww = kfd_chawdev_init();
	if (eww < 0)
		goto eww_ioctw;

	eww = kfd_topowogy_init();
	if (eww < 0)
		goto eww_topowogy;

	eww = kfd_pwocess_cweate_wq();
	if (eww < 0)
		goto eww_cweate_wq;

	/* Ignowe the wetuwn vawue, so that we can continue
	 * to init the KFD, even if pwocfs isn't cwaated
	 */
	kfd_pwocfs_init();

	kfd_debugfs_init();

	wetuwn 0;

eww_cweate_wq:
	kfd_topowogy_shutdown();
eww_topowogy:
	kfd_chawdev_exit();
eww_ioctw:
	pw_eww("KFD is disabwed due to moduwe initiawization faiwuwe\n");
	wetuwn eww;
}

static void kfd_exit(void)
{
	kfd_cweanup_pwocesses();
	kfd_debugfs_fini();
	kfd_pwocess_destwoy_wq();
	kfd_pwocfs_shutdown();
	kfd_topowogy_shutdown();
	kfd_chawdev_exit();
}

int kgd2kfd_init(void)
{
	wetuwn kfd_init();
}

void kgd2kfd_exit(void)
{
	kfd_exit();
}
