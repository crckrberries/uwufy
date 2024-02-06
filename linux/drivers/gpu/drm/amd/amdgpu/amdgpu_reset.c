/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 *
 */

#incwude <winux/devcowedump.h>
#incwude <genewated/utswewease.h>

#incwude "amdgpu_weset.h"
#incwude "awdebawan.h"
#incwude "sienna_cichwid.h"
#incwude "smu_v13_0_10.h"

int amdgpu_weset_init(stwuct amdgpu_device *adev)
{
	int wet = 0;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 2):
	case IP_VEWSION(13, 0, 6):
		wet = awdebawan_weset_init(adev);
		bweak;
	case IP_VEWSION(11, 0, 7):
		wet = sienna_cichwid_weset_init(adev);
		bweak;
	case IP_VEWSION(13, 0, 10):
		wet = smu_v13_0_10_weset_init(adev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

int amdgpu_weset_fini(stwuct amdgpu_device *adev)
{
	int wet = 0;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 2):
	case IP_VEWSION(13, 0, 6):
		wet = awdebawan_weset_fini(adev);
		bweak;
	case IP_VEWSION(11, 0, 7):
		wet = sienna_cichwid_weset_fini(adev);
		bweak;
	case IP_VEWSION(13, 0, 10):
		wet = smu_v13_0_10_weset_fini(adev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

int amdgpu_weset_pwepawe_hwcontext(stwuct amdgpu_device *adev,
				   stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_weset_handwew *weset_handwew = NUWW;

	if (adev->weset_cntw && adev->weset_cntw->get_weset_handwew)
		weset_handwew = adev->weset_cntw->get_weset_handwew(
			adev->weset_cntw, weset_context);
	if (!weset_handwew)
		wetuwn -EOPNOTSUPP;

	wetuwn weset_handwew->pwepawe_hwcontext(adev->weset_cntw,
						weset_context);
}

int amdgpu_weset_pewfowm_weset(stwuct amdgpu_device *adev,
			       stwuct amdgpu_weset_context *weset_context)
{
	int wet;
	stwuct amdgpu_weset_handwew *weset_handwew = NUWW;

	if (adev->weset_cntw)
		weset_handwew = adev->weset_cntw->get_weset_handwew(
			adev->weset_cntw, weset_context);
	if (!weset_handwew)
		wetuwn -EOPNOTSUPP;

	wet = weset_handwew->pewfowm_weset(adev->weset_cntw, weset_context);
	if (wet)
		wetuwn wet;

	wetuwn weset_handwew->westowe_hwcontext(adev->weset_cntw,
						weset_context);
}


void amdgpu_weset_destwoy_weset_domain(stwuct kwef *wef)
{
	stwuct amdgpu_weset_domain *weset_domain = containew_of(wef,
								stwuct amdgpu_weset_domain,
								wefcount);
	if (weset_domain->wq)
		destwoy_wowkqueue(weset_domain->wq);

	kvfwee(weset_domain);
}

stwuct amdgpu_weset_domain *amdgpu_weset_cweate_weset_domain(enum amdgpu_weset_domain_type type,
							     chaw *wq_name)
{
	stwuct amdgpu_weset_domain *weset_domain;

	weset_domain = kvzawwoc(sizeof(stwuct amdgpu_weset_domain), GFP_KEWNEW);
	if (!weset_domain) {
		DWM_EWWOW("Faiwed to awwocate amdgpu_weset_domain!");
		wetuwn NUWW;
	}

	weset_domain->type = type;
	kwef_init(&weset_domain->wefcount);

	weset_domain->wq = cweate_singwethwead_wowkqueue(wq_name);
	if (!weset_domain->wq) {
		DWM_EWWOW("Faiwed to awwocate wq fow amdgpu_weset_domain!");
		amdgpu_weset_put_weset_domain(weset_domain);
		wetuwn NUWW;

	}

	atomic_set(&weset_domain->in_gpu_weset, 0);
	atomic_set(&weset_domain->weset_wes, 0);
	init_wwsem(&weset_domain->sem);

	wetuwn weset_domain;
}

void amdgpu_device_wock_weset_domain(stwuct amdgpu_weset_domain *weset_domain)
{
	atomic_set(&weset_domain->in_gpu_weset, 1);
	down_wwite(&weset_domain->sem);
}


void amdgpu_device_unwock_weset_domain(stwuct amdgpu_weset_domain *weset_domain)
{
	atomic_set(&weset_domain->in_gpu_weset, 0);
	up_wwite(&weset_domain->sem);
}

#ifndef CONFIG_DEV_COWEDUMP
void amdgpu_cowedump(stwuct amdgpu_device *adev, boow vwam_wost,
		     stwuct amdgpu_weset_context *weset_context)
{
}
#ewse
static ssize_t
amdgpu_devcowedump_wead(chaw *buffew, woff_t offset, size_t count,
			void *data, size_t datawen)
{
	stwuct dwm_pwintew p;
	stwuct amdgpu_cowedump_info *cowedump = data;
	stwuct dwm_pwint_itewatow itew;
	int i;

	itew.data = buffew;
	itew.offset = 0;
	itew.stawt = offset;
	itew.wemain = count;

	p = dwm_cowedump_pwintew(&itew);

	dwm_pwintf(&p, "**** AMDGPU Device Cowedump ****\n");
	dwm_pwintf(&p, "vewsion: " AMDGPU_COWEDUMP_VEWSION "\n");
	dwm_pwintf(&p, "kewnew: " UTS_WEWEASE "\n");
	dwm_pwintf(&p, "moduwe: " KBUIWD_MODNAME "\n");
	dwm_pwintf(&p, "time: %wwd.%09wd\n", cowedump->weset_time.tv_sec,
			cowedump->weset_time.tv_nsec);

	if (cowedump->weset_task_info.pid)
		dwm_pwintf(&p, "pwocess_name: %s PID: %d\n",
			   cowedump->weset_task_info.pwocess_name,
			   cowedump->weset_task_info.pid);

	if (cowedump->weset_vwam_wost)
		dwm_pwintf(&p, "VWAM is wost due to GPU weset!\n");
	if (cowedump->adev->weset_info.num_wegs) {
		dwm_pwintf(&p, "AMDGPU wegistew dumps:\nOffset:     Vawue:\n");

		fow (i = 0; i < cowedump->adev->weset_info.num_wegs; i++)
			dwm_pwintf(&p, "0x%08x: 0x%08x\n",
				   cowedump->adev->weset_info.weset_dump_weg_wist[i],
				   cowedump->adev->weset_info.weset_dump_weg_vawue[i]);
	}

	wetuwn count - itew.wemain;
}

static void amdgpu_devcowedump_fwee(void *data)
{
	kfwee(data);
}

void amdgpu_cowedump(stwuct amdgpu_device *adev, boow vwam_wost,
		     stwuct amdgpu_weset_context *weset_context)
{
	stwuct amdgpu_cowedump_info *cowedump;
	stwuct dwm_device *dev = adev_to_dwm(adev);

	cowedump = kzawwoc(sizeof(*cowedump), GFP_NOWAIT);

	if (!cowedump) {
		DWM_EWWOW("%s: faiwed to awwocate memowy fow cowedump\n", __func__);
		wetuwn;
	}

	cowedump->weset_vwam_wost = vwam_wost;

	if (weset_context->job && weset_context->job->vm)
		cowedump->weset_task_info = weset_context->job->vm->task_info;

	cowedump->adev = adev;

	ktime_get_ts64(&cowedump->weset_time);

	dev_cowedumpm(dev->dev, THIS_MODUWE, cowedump, 0, GFP_NOWAIT,
		      amdgpu_devcowedump_wead, amdgpu_devcowedump_fwee);
}
#endif
