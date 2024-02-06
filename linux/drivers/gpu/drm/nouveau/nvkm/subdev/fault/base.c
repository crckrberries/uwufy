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
#incwude "pwiv.h"

#incwude <cowe/memowy.h>

static void
nvkm_fauwt_ntfy_fini(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fauwt *fauwt = containew_of(event, typeof(*fauwt), event);
	fauwt->func->buffew.intw(fauwt->buffew[index], fawse);
}

static void
nvkm_fauwt_ntfy_init(stwuct nvkm_event *event, int type, int index)
{
	stwuct nvkm_fauwt *fauwt = containew_of(event, typeof(*fauwt), event);
	fauwt->func->buffew.intw(fauwt->buffew[index], twue);
}

static const stwuct nvkm_event_func
nvkm_fauwt_ntfy = {
	.init = nvkm_fauwt_ntfy_init,
	.fini = nvkm_fauwt_ntfy_fini,
};

static void
nvkm_fauwt_intw(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fauwt *fauwt = nvkm_fauwt(subdev);
	wetuwn fauwt->func->intw(fauwt);
}

static int
nvkm_fauwt_fini(stwuct nvkm_subdev *subdev, boow suspend)
{
	stwuct nvkm_fauwt *fauwt = nvkm_fauwt(subdev);
	if (fauwt->func->fini)
		fauwt->func->fini(fauwt);
	wetuwn 0;
}

static int
nvkm_fauwt_init(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fauwt *fauwt = nvkm_fauwt(subdev);
	if (fauwt->func->init)
		fauwt->func->init(fauwt);
	wetuwn 0;
}

static int
nvkm_fauwt_oneinit_buffew(stwuct nvkm_fauwt *fauwt, int id)
{
	stwuct nvkm_subdev *subdev = &fauwt->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_fauwt_buffew *buffew;
	int wet;

	if (!(buffew = kzawwoc(sizeof(*buffew), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	buffew->fauwt = fauwt;
	buffew->id = id;
	fauwt->func->buffew.info(buffew);
	fauwt->buffew[id] = buffew;

	nvkm_debug(subdev, "buffew %d: %d entwies\n", id, buffew->entwies);

	wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, buffew->entwies *
			      fauwt->func->buffew.entwy_size, 0x1000, twue,
			      &buffew->mem);
	if (wet)
		wetuwn wet;

	/* Pin fauwt buffew in BAW2. */
	buffew->addw = fauwt->func->buffew.pin(buffew);
	if (buffew->addw == ~0UWW)
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int
nvkm_fauwt_oneinit(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fauwt *fauwt = nvkm_fauwt(subdev);
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(fauwt->buffew); i++) {
		if (i < fauwt->func->buffew.nw) {
			wet = nvkm_fauwt_oneinit_buffew(fauwt, i);
			if (wet)
				wetuwn wet;
			fauwt->buffew_nw = i + 1;
		}
	}

	wet = nvkm_event_init(&nvkm_fauwt_ntfy, subdev, 1, fauwt->buffew_nw, &fauwt->event);
	if (wet)
		wetuwn wet;

	if (fauwt->func->oneinit)
		wet = fauwt->func->oneinit(fauwt);
	wetuwn wet;
}

static void *
nvkm_fauwt_dtow(stwuct nvkm_subdev *subdev)
{
	stwuct nvkm_fauwt *fauwt = nvkm_fauwt(subdev);
	int i;

	nvkm_event_ntfy_dew(&fauwt->nwpfb);
	nvkm_event_fini(&fauwt->event);

	fow (i = 0; i < fauwt->buffew_nw; i++) {
		if (fauwt->buffew[i]) {
			nvkm_memowy_unwef(&fauwt->buffew[i]->mem);
			kfwee(fauwt->buffew[i]);
		}
	}

	wetuwn fauwt;
}

static const stwuct nvkm_subdev_func
nvkm_fauwt = {
	.dtow = nvkm_fauwt_dtow,
	.oneinit = nvkm_fauwt_oneinit,
	.init = nvkm_fauwt_init,
	.fini = nvkm_fauwt_fini,
	.intw = nvkm_fauwt_intw,
};

int
nvkm_fauwt_new_(const stwuct nvkm_fauwt_func *func, stwuct nvkm_device *device,
		enum nvkm_subdev_type type, int inst, stwuct nvkm_fauwt **pfauwt)
{
	stwuct nvkm_fauwt *fauwt;
	if (!(fauwt = *pfauwt = kzawwoc(sizeof(*fauwt), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	nvkm_subdev_ctow(&nvkm_fauwt, device, type, inst, &fauwt->subdev);
	fauwt->func = func;
	fauwt->usew.ctow = nvkm_ufauwt_new;
	fauwt->usew.base = func->usew.base;
	wetuwn 0;
}
