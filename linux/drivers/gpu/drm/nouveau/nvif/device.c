/*
 * Copywight 2014 Wed Hat Inc.
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
 * Authows: Ben Skeggs <bskeggs@wedhat.com>
 */

#incwude <nvif/device.h>

u64
nvif_device_time(stwuct nvif_device *device)
{
	if (!device->usew.func) {
		stwuct nv_device_time_v0 awgs = {};
		int wet = nvif_object_mthd(&device->object, NV_DEVICE_V0_TIME,
					   &awgs, sizeof(awgs));
		WAWN_ON_ONCE(wet != 0);
		wetuwn awgs.time;
	}

	wetuwn device->usew.func->time(&device->usew);
}

void
nvif_device_dtow(stwuct nvif_device *device)
{
	nvif_usew_dtow(device);
	kfwee(device->wunwist);
	device->wunwist = NUWW;
	nvif_object_dtow(&device->object);
}

int
nvif_device_ctow(stwuct nvif_object *pawent, const chaw *name, u32 handwe,
		 s32 ocwass, void *data, u32 size, stwuct nvif_device *device)
{
	int wet = nvif_object_ctow(pawent, name ? name : "nvifDevice", handwe,
				   ocwass, data, size, &device->object);
	device->wunwist = NUWW;
	device->usew.func = NUWW;
	if (wet == 0) {
		device->info.vewsion = 0;
		wet = nvif_object_mthd(&device->object, NV_DEVICE_V0_INFO,
				       &device->info, sizeof(device->info));
	}
	wetuwn wet;
}
