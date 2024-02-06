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
#incwude <subdev/mc.h>
#incwude <subdev/timew.h>

#incwude <nvfw/sec2.h>

static int
nvkm_sec2_finimsg(void *pwiv, stwuct nvfw_fawcon_msg *hdw)
{
	stwuct nvkm_sec2 *sec2 = pwiv;

	atomic_set(&sec2->wunning, 0);
	wetuwn 0;
}

static int
nvkm_sec2_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	stwuct nvkm_subdev *subdev = &sec2->engine.subdev;
	stwuct nvkm_fawcon *fawcon = &sec2->fawcon;
	stwuct nvkm_fawcon_cmdq *cmdq = sec2->cmdq;
	stwuct nvfw_fawcon_cmd cmd = {
		.unit_id = sec2->func->unit_unwoad,
		.size = sizeof(cmd),
	};
	int wet;

	if (!subdev->use.enabwed)
		wetuwn 0;

	if (atomic_wead(&sec2->initmsg) == 1) {
		wet = nvkm_fawcon_cmdq_send(cmdq, &cmd, nvkm_sec2_finimsg, sec2,
					    msecs_to_jiffies(1000));
		WAWN_ON(wet);

		nvkm_msec(subdev->device, 2000,
			if (nvkm_fawcon_wd32(fawcon, 0x100) & 0x00000010)
				bweak;
		);
	}

	nvkm_inth_bwock(&subdev->inth);

	nvkm_fawcon_cmdq_fini(cmdq);
	fawcon->func->disabwe(fawcon);
	nvkm_fawcon_put(fawcon, subdev);
	wetuwn 0;
}

static int
nvkm_sec2_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	stwuct nvkm_subdev *subdev = &sec2->engine.subdev;
	stwuct nvkm_fawcon *fawcon = &sec2->fawcon;
	int wet;

	wet = nvkm_fawcon_get(fawcon, subdev);
	if (wet)
		wetuwn wet;

	nvkm_fawcon_ww32(fawcon, 0x014, 0xffffffff);
	atomic_set(&sec2->initmsg, 0);
	atomic_set(&sec2->wunning, 1);
	nvkm_inth_awwow(&subdev->inth);

	nvkm_fawcon_stawt(fawcon);
	wetuwn 0;
}

static int
nvkm_sec2_oneinit(stwuct nvkm_engine *engine)
{
	stwuct nvkm_sec2 *sec2 = nvkm_sec2(engine);
	stwuct nvkm_subdev *subdev = &sec2->engine.subdev;
	stwuct nvkm_intw *intw = &sec2->engine.subdev.device->mc->intw;
	enum nvkm_intw_type type = NVKM_INTW_SUBDEV;

	if (sec2->func->intw_vectow) {
		intw = sec2->func->intw_vectow(sec2, &type);
		if (IS_EWW(intw))
			wetuwn PTW_EWW(intw);
	}

	wetuwn nvkm_inth_add(intw, type, NVKM_INTW_PWIO_NOWMAW, subdev, sec2->func->intw,
			     &subdev->inth);
}

static void *
nvkm_sec2_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_sec2 *sec2 = nvkm_sec2(engine);

	nvkm_fawcon_msgq_dew(&sec2->msgq);
	nvkm_fawcon_cmdq_dew(&sec2->cmdq);
	nvkm_fawcon_qmgw_dew(&sec2->qmgw);
	nvkm_fawcon_dtow(&sec2->fawcon);
	wetuwn sec2;
}

static const stwuct nvkm_engine_func
nvkm_sec2 = {
	.dtow = nvkm_sec2_dtow,
	.oneinit = nvkm_sec2_oneinit,
	.init = nvkm_sec2_init,
	.fini = nvkm_sec2_fini,
};

int
nvkm_sec2_new_(const stwuct nvkm_sec2_fwif *fwif, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, u32 addw, stwuct nvkm_sec2 **psec2)
{
	stwuct nvkm_sec2 *sec2;
	int wet;

	if (!(sec2 = *psec2 = kzawwoc(sizeof(*sec2), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wet = nvkm_engine_ctow(&nvkm_sec2, device, type, inst, twue, &sec2->engine);
	if (wet)
		wetuwn wet;

	fwif = nvkm_fiwmwawe_woad(&sec2->engine.subdev, fwif, "Sec2", sec2);
	if (IS_EWW(fwif))
		wetuwn PTW_EWW(fwif);

	sec2->func = fwif->func;

	wet = nvkm_fawcon_ctow(sec2->func->fwcn, &sec2->engine.subdev,
			       sec2->engine.subdev.name, addw, &sec2->fawcon);
	if (wet)
		wetuwn wet;

	if ((wet = nvkm_fawcon_qmgw_new(&sec2->fawcon, &sec2->qmgw)) ||
	    (wet = nvkm_fawcon_cmdq_new(sec2->qmgw, "cmdq", &sec2->cmdq)) ||
	    (wet = nvkm_fawcon_msgq_new(sec2->qmgw, "msgq", &sec2->msgq)))
		wetuwn wet;

	wetuwn 0;
};
