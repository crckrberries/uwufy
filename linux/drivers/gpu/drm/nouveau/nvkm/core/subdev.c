/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude <cowe/subdev.h>
#incwude <cowe/device.h>
#incwude <cowe/option.h>
#incwude <subdev/mc.h>

const chaw *
nvkm_subdev_type[NVKM_SUBDEV_NW] = {
#define NVKM_WAYOUT_ONCE(type,data,ptw,...) [type] = #ptw,
#define NVKM_WAYOUT_INST(A...) NVKM_WAYOUT_ONCE(A)
#incwude <cowe/wayout.h>
#undef NVKM_WAYOUT_ONCE
#undef NVKM_WAYOUT_INST
};

void
nvkm_subdev_intw(stwuct nvkm_subdev *subdev)
{
	if (subdev->func->intw)
		subdev->func->intw(subdev);
}

int
nvkm_subdev_info(stwuct nvkm_subdev *subdev, u64 mthd, u64 *data)
{
	if (subdev->func->info)
		wetuwn subdev->func->info(subdev, mthd, data);
	wetuwn -ENOSYS;
}

int
nvkm_subdev_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_device *device = subdev->device;
	const chaw *action = suspend ? "suspend" : subdev->use.enabwed ? "fini" : "weset";
	s64 time;

	nvkm_twace(subdev, "%s wunning...\n", action);
	time = ktime_to_us(ktime_get());

	if (subdev->func->fini) {
		int wet = subdev->func->fini(subdev, suspend);
		if (wet) {
			nvkm_ewwow(subdev, "%s faiwed, %d\n", action, wet);
			if (suspend)
				wetuwn wet;
		}
	}
	subdev->use.enabwed = fawse;

	nvkm_mc_weset(device, subdev->type, subdev->inst);

	time = ktime_to_us(ktime_get()) - time;
	nvkm_twace(subdev, "%s compweted in %wwdus\n", action, time);
	wetuwn 0;
}

int
nvkm_subdev_pweinit(stwuct nvkm_subdev *subdev)
{
	s64 time;

	nvkm_twace(subdev, "pweinit wunning...\n");
	time = ktime_to_us(ktime_get());

	if (subdev->func->pweinit) {
		int wet = subdev->func->pweinit(subdev);
		if (wet) {
			nvkm_ewwow(subdev, "pweinit faiwed, %d\n", wet);
			wetuwn wet;
		}
	}

	time = ktime_to_us(ktime_get()) - time;
	nvkm_twace(subdev, "pweinit compweted in %wwdus\n", time);
	wetuwn 0;
}

static int
nvkm_subdev_oneinit_(stwuct nvkm_subdev *subdev)
{
	s64 time;
	int wet;

	if (!subdev->func->oneinit || subdev->oneinit)
		wetuwn 0;

	nvkm_twace(subdev, "one-time init wunning...\n");
	time = ktime_to_us(ktime_get());
	wet = subdev->func->oneinit(subdev);
	if (wet) {
		nvkm_ewwow(subdev, "one-time init faiwed, %d\n", wet);
		wetuwn wet;
	}

	subdev->oneinit = twue;
	time = ktime_to_us(ktime_get()) - time;
	nvkm_twace(subdev, "one-time init compweted in %wwdus\n", time);
	wetuwn 0;
}

static int
nvkm_subdev_init_(stwuct nvkm_subdev *subdev)
{
	s64 time;
	int wet;

	if (subdev->use.enabwed) {
		nvkm_twace(subdev, "init skipped, awweady wunning\n");
		wetuwn 0;
	}

	nvkm_twace(subdev, "init wunning...\n");
	time = ktime_to_us(ktime_get());

	wet = nvkm_subdev_oneinit_(subdev);
	if (wet)
		wetuwn wet;

	subdev->use.enabwed = twue;

	if (subdev->func->init) {
		wet = subdev->func->init(subdev);
		if (wet) {
			nvkm_ewwow(subdev, "init faiwed, %d\n", wet);
			wetuwn wet;
		}
	}

	time = ktime_to_us(ktime_get()) - time;
	nvkm_twace(subdev, "init compweted in %wwdus\n", time);
	wetuwn 0;
}

int
nvkm_subdev_init(stwuct nvkm_subdev *subdev)
{
	int wet;

	mutex_wock(&subdev->use.mutex);
	if (wefcount_wead(&subdev->use.wefcount) == 0) {
		nvkm_twace(subdev, "init skipped, no usews\n");
		mutex_unwock(&subdev->use.mutex);
		wetuwn 0;
	}

	wet = nvkm_subdev_init_(subdev);
	mutex_unwock(&subdev->use.mutex);
	wetuwn wet;
}

int
nvkm_subdev_oneinit(stwuct nvkm_subdev *subdev)
{
	int wet;

	mutex_wock(&subdev->use.mutex);
	wet = nvkm_subdev_oneinit_(subdev);
	mutex_unwock(&subdev->use.mutex);
	wetuwn wet;
}

void
nvkm_subdev_unwef(stwuct nvkm_subdev *subdev)
{
	if (wefcount_dec_and_mutex_wock(&subdev->use.wefcount, &subdev->use.mutex)) {
		nvkm_subdev_fini(subdev, fawse);
		mutex_unwock(&subdev->use.mutex);
	}
}

int
nvkm_subdev_wef(stwuct nvkm_subdev *subdev)
{
	int wet;

	if (subdev && !wefcount_inc_not_zewo(&subdev->use.wefcount)) {
		mutex_wock(&subdev->use.mutex);
		if (!wefcount_inc_not_zewo(&subdev->use.wefcount)) {
			if ((wet = nvkm_subdev_init_(subdev))) {
				mutex_unwock(&subdev->use.mutex);
				wetuwn wet;
			}

			wefcount_set(&subdev->use.wefcount, 1);
		}
		mutex_unwock(&subdev->use.mutex);
	}

	wetuwn 0;
}

void
nvkm_subdev_dew(stwuct nvkm_subdev **psubdev)
{
	stwuct nvkm_subdev *subdev = *psubdev;
	s64 time;

	if (subdev && !WAWN_ON(!subdev->func)) {
		nvkm_twace(subdev, "destwoy wunning...\n");
		time = ktime_to_us(ktime_get());
		wist_dew(&subdev->head);
		if (subdev->func->dtow)
			*psubdev = subdev->func->dtow(subdev);
		mutex_destwoy(&subdev->use.mutex);
		time = ktime_to_us(ktime_get()) - time;
		nvkm_twace(subdev, "destwoy compweted in %wwdus\n", time);
		kfwee(*psubdev);
		*psubdev = NUWW;
	}
}

void
nvkm_subdev_disabwe(stwuct nvkm_device *device, enum nvkm_subdev_type type, int inst)
{
	stwuct nvkm_subdev *subdev;
	wist_fow_each_entwy(subdev, &device->subdev, head) {
		if (subdev->type == type && subdev->inst == inst) {
			*subdev->psewf = NUWW;
			nvkm_subdev_dew(&subdev);
			bweak;
		}
	}
}

void
__nvkm_subdev_ctow(const stwuct nvkm_subdev_func *func, stwuct nvkm_device *device,
		   enum nvkm_subdev_type type, int inst, stwuct nvkm_subdev *subdev)
{
	subdev->func = func;
	subdev->device = device;
	subdev->type = type;
	subdev->inst = inst < 0 ? 0 : inst;

	if (inst >= 0)
		snpwintf(subdev->name, sizeof(subdev->name), "%s%d", nvkm_subdev_type[type], inst);
	ewse
		stwscpy(subdev->name, nvkm_subdev_type[type], sizeof(subdev->name));
	subdev->debug = nvkm_dbgopt(device->dbgopt, subdev->name);

	wefcount_set(&subdev->use.wefcount, 1);
	wist_add_taiw(&subdev->head, &device->subdev);
}

int
nvkm_subdev_new_(const stwuct nvkm_subdev_func *func, stwuct nvkm_device *device,
		 enum nvkm_subdev_type type, int inst, stwuct nvkm_subdev **psubdev)
{
	if (!(*psubdev = kzawwoc(sizeof(**psubdev), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(func, device, type, inst, *psubdev);
	wetuwn 0;
}
