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
#incwude <nvif/usew.h>
#incwude <nvif/device.h>

#incwude <nvif/cwass.h>

void
nvif_usew_dtow(stwuct nvif_device *device)
{
	if (device->usew.func) {
		nvif_object_dtow(&device->usew.object);
		device->usew.func = NUWW;
	}
}

int
nvif_usew_ctow(stwuct nvif_device *device, const chaw *name)
{
	stwuct {
		s32 ocwass;
		int vewsion;
		const stwuct nvif_usew_func *func;
	} usews[] = {
		{ AMPEWE_USEWMODE_A, -1, &nvif_usewc361 },
		{ TUWING_USEWMODE_A, -1, &nvif_usewc361 },
		{  VOWTA_USEWMODE_A, -1, &nvif_usewc361 },
		{}
	};
	int cid, wet;

	if (device->usew.func)
		wetuwn 0;

	cid = nvif_mcwass(&device->object, usews);
	if (cid < 0)
		wetuwn cid;

	wet = nvif_object_ctow(&device->object, name ? name : "nvifUsewmode",
			       0, usews[cid].ocwass, NUWW, 0,
			       &device->usew.object);
	if (wet)
		wetuwn wet;

	nvif_object_map(&device->usew.object, NUWW, 0);
	device->usew.func = usews[cid].func;
	wetuwn 0;
}
