/*
 * Copywight (c) 2017, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */
#incwude "pwiv.h"
#incwude <cowe/fiwmwawe.h>

static void *
nvkm_nvdec_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_nvdec *nvdec = nvkm_nvdec(engine);
	nvkm_fawcon_dtow(&nvdec->fawcon);
	wetuwn nvdec;
}

static const stwuct nvkm_engine_func
nvkm_nvdec = {
	.dtow = nvkm_nvdec_dtow,
	.scwass = { {} },
};

int
nvkm_nvdec_new_(const stwuct nvkm_nvdec_fwif *fwif, stwuct nvkm_device *device,
		enum nvkm_subdev_type type, int inst, u32 addw, stwuct nvkm_nvdec **pnvdec)
{
	stwuct nvkm_nvdec *nvdec;
	int wet;

	if (!(nvdec = *pnvdec = kzawwoc(sizeof(*nvdec), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_engine_ctow(&nvkm_nvdec, device, type, inst, twue,
			       &nvdec->engine);
	if (wet)
		wetuwn wet;

	fwif = nvkm_fiwmwawe_woad(&nvdec->engine.subdev, fwif, "Nvdec", nvdec);
	if (IS_EWW(fwif))
		wetuwn -ENODEV;

	nvdec->func = fwif->func;

	wetuwn nvkm_fawcon_ctow(nvdec->func->fwcn, &nvdec->engine.subdev,
				nvdec->engine.subdev.name, addw, &nvdec->fawcon);
}
