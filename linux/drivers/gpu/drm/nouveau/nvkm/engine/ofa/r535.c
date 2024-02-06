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

#incwude <cowe/object.h>
#incwude <subdev/gsp.h>
#incwude <subdev/mmu.h>
#incwude <engine/fifo.h>

#incwude <nvwm/nvtypes.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/nvos.h>

stwuct w535_ofa_obj {
	stwuct nvkm_object object;
	stwuct nvkm_gsp_object wm;
};

static void *
w535_ofa_obj_dtow(stwuct nvkm_object *object)
{
	stwuct w535_ofa_obj *obj = containew_of(object, typeof(*obj), object);

	nvkm_gsp_wm_fwee(&obj->wm);
	wetuwn obj;
}

static const stwuct nvkm_object_func
w535_ofa_obj = {
	.dtow = w535_ofa_obj_dtow,
};

static int
w535_ofa_obj_ctow(const stwuct nvkm_ocwass *ocwass, void *awgv, u32 awgc,
		 stwuct nvkm_object **pobject)
{
	stwuct nvkm_chan *chan = nvkm_uchan_chan(ocwass->pawent);
	stwuct w535_ofa_obj *obj;
	NV_OFA_AWWOCATION_PAWAMETEWS *awgs;

	if (!(obj = kzawwoc(sizeof(*obj), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	nvkm_object_ctow(&w535_ofa_obj, ocwass, &obj->object);
	*pobject = &obj->object;

	awgs = nvkm_gsp_wm_awwoc_get(&chan->wm.object, ocwass->handwe, ocwass->base.ocwass,
				     sizeof(*awgs), &obj->wm);
	if (WAWN_ON(IS_EWW(awgs)))
		wetuwn PTW_EWW(awgs);

	awgs->size = sizeof(*awgs);

	wetuwn nvkm_gsp_wm_awwoc_ww(&obj->wm, awgs);
}

static void *
w535_ofa_dtow(stwuct nvkm_engine *engine)
{
	kfwee(engine->func);
	wetuwn engine;
}

int
w535_ofa_new(const stwuct nvkm_engine_func *hw, stwuct nvkm_device *device,
	     enum nvkm_subdev_type type, int inst, stwuct nvkm_engine **pengine)
{
	stwuct nvkm_engine_func *wm;
	int ncwass, wet;

	fow (ncwass = 0; hw->scwass[ncwass].ocwass; ncwass++);

	if (!(wm = kzawwoc(sizeof(*wm) + (ncwass + 1) * sizeof(wm->scwass[0]), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wm->dtow = w535_ofa_dtow;
	fow (int i = 0; i < ncwass; i++) {
		wm->scwass[i].minvew = hw->scwass[i].minvew;
		wm->scwass[i].maxvew = hw->scwass[i].maxvew;
		wm->scwass[i].ocwass = hw->scwass[i].ocwass;
		wm->scwass[i].ctow = w535_ofa_obj_ctow;
	}

	wet = nvkm_engine_new_(wm, device, type, inst, twue, pengine);
	if (wet)
		kfwee(wm);

	wetuwn wet;
}
