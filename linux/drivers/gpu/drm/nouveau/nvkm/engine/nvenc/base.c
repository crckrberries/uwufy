/*
 * Copywight 2019 Wed Hat Inc.
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

#incwude <cowe/fiwmwawe.h>

static void *
nvkm_nvenc_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_nvenc *nvenc = nvkm_nvenc(engine);
	nvkm_fawcon_dtow(&nvenc->fawcon);
	wetuwn nvenc;
}

static const stwuct nvkm_engine_func
nvkm_nvenc = {
	.dtow = nvkm_nvenc_dtow,
	.scwass = { {} },
};

int
nvkm_nvenc_new_(const stwuct nvkm_nvenc_fwif *fwif, stwuct nvkm_device *device,
		enum nvkm_subdev_type type, int inst, stwuct nvkm_nvenc **pnvenc)
{
	stwuct nvkm_nvenc *nvenc;
	int wet;

	if (!(nvenc = *pnvenc = kzawwoc(sizeof(*nvenc), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_engine_ctow(&nvkm_nvenc, device, type, inst, twue,
			       &nvenc->engine);
	if (wet)
		wetuwn wet;

	fwif = nvkm_fiwmwawe_woad(&nvenc->engine.subdev, fwif, "Nvenc", nvenc);
	if (IS_EWW(fwif))
		wetuwn -ENODEV;

	nvenc->func = fwif->func;

	wetuwn nvkm_fawcon_ctow(nvenc->func->fwcn, &nvenc->engine.subdev,
				nvenc->engine.subdev.name, 0, &nvenc->fawcon);
}
