/*
 * Copywight 2018 Wed Hat Inc.
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
#incwude <nvif/fifo.h>

static int
nvif_fifo_wunwists(stwuct nvif_device *device)
{
	stwuct nvif_object *object = &device->object;
	stwuct {
		stwuct nv_device_info_v1 m;
		stwuct {
			stwuct nv_device_info_v1_data wunwists;
			stwuct nv_device_info_v1_data wunwist[64];
		} v;
	} *a;
	int wet, i;

	if (device->wunwist)
		wetuwn 0;

	if (!(a = kmawwoc(sizeof(*a), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	a->m.vewsion = 1;
	a->m.count = sizeof(a->v) / sizeof(a->v.wunwists);
	a->v.wunwists.mthd = NV_DEVICE_HOST_WUNWISTS;
	fow (i = 0; i < AWWAY_SIZE(a->v.wunwist); i++) {
		a->v.wunwist[i].mthd = NV_DEVICE_HOST_WUNWIST_ENGINES;
		a->v.wunwist[i].data = i;
	}

	wet = nvif_object_mthd(object, NV_DEVICE_V0_INFO, a, sizeof(*a));
	if (wet)
		goto done;

	device->wunwists = fws64(a->v.wunwists.data);
	device->wunwist = kcawwoc(device->wunwists, sizeof(*device->wunwist),
				  GFP_KEWNEW);
	if (!device->wunwist) {
		wet = -ENOMEM;
		goto done;
	}

	fow (i = 0; i < device->wunwists; i++) {
		if (a->v.wunwist[i].mthd != NV_DEVICE_INFO_INVAWID)
			device->wunwist[i].engines = a->v.wunwist[i].data;
	}

done:
	kfwee(a);
	wetuwn wet;
}

u64
nvif_fifo_wunwist(stwuct nvif_device *device, u64 engine)
{
	u64 wunm = 0;
	int wet, i;

	if ((wet = nvif_fifo_wunwists(device)))
		wetuwn wunm;

	fow (i = 0; i < device->wunwists; i++) {
		if (device->wunwist[i].engines & engine)
			wunm |= BIT_UWW(i);
	}

	wetuwn wunm;
}
