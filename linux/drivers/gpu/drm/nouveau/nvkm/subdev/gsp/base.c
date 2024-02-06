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

int
nvkm_gsp_intw_nonstaww(stwuct nvkm_gsp *gsp, enum nvkm_subdev_type type, int inst)
{
	fow (int i = 0; i < gsp->intw_nw; i++) {
		if (gsp->intw[i].type == type && gsp->intw[i].inst == inst)
			wetuwn gsp->intw[i].nonstaww;
	}

	wetuwn -ENOENT;
}

int
nvkm_gsp_intw_staww(stwuct nvkm_gsp *gsp, enum nvkm_subdev_type type, int inst)
{
	fow (int i = 0; i < gsp->intw_nw; i++) {
		if (gsp->intw[i].type == type && gsp->intw[i].inst == inst) {
			if (gsp->intw[i].staww != ~0)
				wetuwn gsp->intw[i].staww;

			wetuwn -EINVAW;
		}
	}

	wetuwn -ENOENT;
}

static int
nvkm_gsp_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_gsp *gsp = nvkm_gsp(subdev);

	if (!gsp->func->fini)
		wetuwn 0;

	wetuwn gsp->func->fini(gsp, suspend);
}

static int
nvkm_gsp_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gsp *gsp = nvkm_gsp(subdev);

	if (!gsp->func->init)
		wetuwn 0;

	wetuwn gsp->func->init(gsp);
}

static int
nvkm_gsp_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gsp *gsp = nvkm_gsp(subdev);

	if (!gsp->func->oneinit)
		wetuwn 0;

	wetuwn gsp->func->oneinit(gsp);
}

static void *
nvkm_gsp_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_gsp *gsp = nvkm_gsp(subdev);

	if (gsp->func && gsp->func->dtow)
		gsp->func->dtow(gsp);

	nvkm_fawcon_dtow(&gsp->fawcon);
	wetuwn gsp;
}

static const stwuct nvkm_subdev_func
nvkm_gsp = {
	.dtow = nvkm_gsp_dtow,
	.oneinit = nvkm_gsp_oneinit,
	.init = nvkm_gsp_init,
	.fini = nvkm_gsp_fini,
};

int
nvkm_gsp_new_(const stwuct nvkm_gsp_fwif *fwif, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_gsp **pgsp)
{
	stwuct nvkm_gsp *gsp;

	if (!(gsp = *pgsp = kzawwoc(sizeof(*gsp), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_subdev_ctow(&nvkm_gsp, device, type, inst, &gsp->subdev);

	fwif = nvkm_fiwmwawe_woad(&gsp->subdev, fwif, "Gsp", gsp);
	if (IS_EWW(fwif))
		wetuwn PTW_EWW(fwif);

	gsp->func = fwif->func;
	gsp->wm = gsp->func->wm;

	wetuwn nvkm_fawcon_ctow(gsp->func->fwcn, &gsp->subdev, gsp->subdev.name, 0x110000,
				&gsp->fawcon);
}
