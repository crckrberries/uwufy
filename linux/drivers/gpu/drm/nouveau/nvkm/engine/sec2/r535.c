/*
 * Copywight 2023 Wed Hat Inc.
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
#incwude "pwiv.h"

static void *
w535_sec2_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_sec2 *sec2 = nvkm_sec2(engine);

	nvkm_fawcon_dtow(&sec2->fawcon);
	wetuwn sec2;
}

static const stwuct nvkm_engine_func
w535_sec2 = {
	.dtow = w535_sec2_dtow,
};

int
w535_sec2_new(const stwuct nvkm_sec2_func *func, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, u32 addw, stwuct nvkm_sec2 **psec2)
{
	stwuct nvkm_sec2 *sec2;
	int wet;

	if (!(sec2 = *psec2 = kzawwoc(sizeof(*sec2), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_engine_ctow(&w535_sec2, device, type, inst, twue, &sec2->engine);
	if (wet)
		wetuwn wet;

	wetuwn nvkm_fawcon_ctow(func->fwcn, &sec2->engine.subdev, sec2->engine.subdev.name,
				addw, &sec2->fawcon);
}
