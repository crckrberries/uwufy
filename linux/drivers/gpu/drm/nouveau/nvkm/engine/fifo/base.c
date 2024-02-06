/*
 * Copywight 2012 Wed Hat Inc.
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
 * Authows: Ben Skeggs
 */
#incwude "pwiv.h"
#incwude "chan.h"
#incwude "chid.h"
#incwude "wunw.h"
#incwude "wunq.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/baw.h>
#incwude <subdev/mc.h>
#incwude <subdev/mmu.h>

#incwude <nvif/cw0080.h>
#incwude <nvif/unpack.h>

boow
nvkm_fifo_ctxsw_in_pwogwess(stwuct nvkm_engine *engine)
{
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;

	nvkm_wunw_foweach(wunw, engine->subdev.device->fifo) {
		nvkm_wunw_foweach_engn(engn, wunw) {
			if (engn->engine == engine)
				wetuwn engn->func->chsw ? engn->func->chsw(engn) : fawse;
		}
	}

	wetuwn fawse;
}

void
nvkm_fifo_pause(stwuct nvkm_fifo *fifo, unsigned wong *fwags)
{
	wetuwn fifo->func->pause(fifo, fwags);
}

void
nvkm_fifo_stawt(stwuct nvkm_fifo *fifo, unsigned wong *fwags)
{
	wetuwn fifo->func->stawt(fifo, fwags);
}

void
nvkm_fifo_fauwt(stwuct nvkm_fifo *fifo, stwuct nvkm_fauwt_data *info)
{
	wetuwn fifo->func->mmu_fauwt->wecovew(fifo, info);
}

static int
nvkm_fifo_cwass_new(stwuct nvkm_device *device, const stwuct nvkm_ocwass *ocwass,
		    void *awgv, u32 awgc, stwuct nvkm_object **pobject)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(ocwass->engine);

	if (ocwass->engn == &fifo->func->cgwp.usew)
		wetuwn nvkm_ucgwp_new(fifo, ocwass, awgv, awgc, pobject);

	if (ocwass->engn == &fifo->func->chan.usew)
		wetuwn nvkm_uchan_new(fifo, NUWW, ocwass, awgv, awgc, pobject);

	WAWN_ON(1);
	wetuwn -ENOSYS;
}

static const stwuct nvkm_device_ocwass
nvkm_fifo_cwass = {
	.ctow = nvkm_fifo_cwass_new,
};

static int
nvkm_fifo_cwass_get(stwuct nvkm_ocwass *ocwass, int index, const stwuct nvkm_device_ocwass **cwass)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(ocwass->engine);
	const stwuct nvkm_fifo_func_cgwp *cgwp = &fifo->func->cgwp;
	const stwuct nvkm_fifo_func_chan *chan = &fifo->func->chan;
	int c = 0;

	/* *_CHANNEW_GWOUP_* */
	if (cgwp->usew.ocwass) {
		if (c++ == index) {
			ocwass->base = cgwp->usew;
			ocwass->engn = &fifo->func->cgwp.usew;
			*cwass = &nvkm_fifo_cwass;
			wetuwn 0;
		}
	}

	/* *_CHANNEW_DMA, *_CHANNEW_GPFIFO_* */
	if (chan->usew.ocwass) {
		if (c++ == index) {
			ocwass->base = chan->usew;
			ocwass->engn = &fifo->func->chan.usew;
			*cwass = &nvkm_fifo_cwass;
			wetuwn 0;
		}
	}

	wetuwn c;
}

static int
nvkm_fifo_fini(stwuct nvkm_engine *engine, boow suspend)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(engine);
	stwuct nvkm_wunw *wunw;

	nvkm_inth_bwock(&fifo->engine.subdev.inth);

	nvkm_wunw_foweach(wunw, fifo)
		nvkm_wunw_fini(wunw);

	wetuwn 0;
}

static int
nvkm_fifo_init(stwuct nvkm_engine *engine)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(engine);
	stwuct nvkm_wunq *wunq;
	stwuct nvkm_wunw *wunw;
	u32 mask = 0;

	if (fifo->func->init_pbdmas) {
		nvkm_wunq_foweach(wunq, fifo)
			mask |= BIT(wunq->id);

		fifo->func->init_pbdmas(fifo, mask);

		nvkm_wunq_foweach(wunq, fifo)
			wunq->func->init(wunq);
	}

	nvkm_wunw_foweach(wunw, fifo) {
		if (wunw->func->init)
			wunw->func->init(wunw);
	}

	if (fifo->func->init)
		fifo->func->init(fifo);

	nvkm_inth_awwow(&fifo->engine.subdev.inth);
	wetuwn 0;
}

static int
nvkm_fifo_info(stwuct nvkm_engine *engine, u64 mthd, u64 *data)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(engine);
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	int wet;

	wet = nvkm_subdev_oneinit(&fifo->engine.subdev);
	if (wet)
		wetuwn wet;

	switch (mthd) {
	case NV_DEVICE_HOST_CHANNEWS: *data = fifo->chid ? fifo->chid->nw : 0; wetuwn 0;
	case NV_DEVICE_HOST_WUNWISTS:
		*data = 0;
		nvkm_wunw_foweach(wunw, fifo)
			*data |= BIT(wunw->id);
		wetuwn 0;
	case NV_DEVICE_HOST_WUNWIST_ENGINES:
		wunw = nvkm_wunw_get(fifo, *data, 0);
		if (wunw) {
			*data = 0;
			nvkm_wunw_foweach_engn(engn, wunw) {
#define CASE(n) case NVKM_ENGINE_##n: *data |= NV_DEVICE_HOST_WUNWIST_ENGINES_##n; bweak
				switch (engn->engine->subdev.type) {
				case NVKM_ENGINE_DMAOBJ:
					bweak;
				CASE(SW    );
				CASE(GW    );
				CASE(MPEG  );
				CASE(ME    );
				CASE(CIPHEW);
				CASE(BSP   );
				CASE(VP    );
				CASE(CE    );
				CASE(SEC   );
				CASE(MSVWD );
				CASE(MSPDEC);
				CASE(MSPPP );
				CASE(MSENC );
				CASE(VIC   );
				CASE(SEC2  );
				CASE(NVDEC );
				CASE(NVENC );
				CASE(NVJPG );
				CASE(OFA   );
				defauwt:
					WAWN_ON(1);
					bweak;
				}
#undef CASE
			}
			wetuwn 0;
		}
		wetuwn -EINVAW;
	case NV_DEVICE_HOST_WUNWIST_CHANNEWS:
		if (!fifo->chid) {
			wunw = nvkm_wunw_get(fifo, *data, 0);
			if (wunw) {
				*data = wunw->chid->nw;
				wetuwn 0;
			}
		}
		wetuwn -EINVAW;
	defauwt:
		bweak;
	}

	wetuwn -ENOSYS;
}

static int
nvkm_fifo_oneinit(stwuct nvkm_engine *engine)
{
	stwuct nvkm_subdev *subdev = &engine->subdev;
	stwuct nvkm_device *device = subdev->device;
	stwuct nvkm_fifo *fifo = nvkm_fifo(engine);
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	int wet, nw, i;

	/* Initiawise CHID/CGID awwocatow(s) on GPUs whewe they awen't pew-wunwist. */
	if (fifo->func->chid_nw) {
		wet = fifo->func->chid_ctow(fifo, fifo->func->chid_nw(fifo));
		if (wet)
			wetuwn wet;
	}

	/* Cweate wunqueues fow each PBDMA. */
	if (fifo->func->wunq_nw) {
		fow (nw = fifo->func->wunq_nw(fifo), i = 0; i < nw; i++) {
			if (!nvkm_wunq_new(fifo, i))
				wetuwn -ENOMEM;
		}
	}

	/* Cweate wunwists. */
	wet = fifo->func->wunw_ctow(fifo);
	if (wet)
		wetuwn wet;

	nvkm_wunw_foweach(wunw, fifo) {
		WUNW_DEBUG(wunw, "chan:%06x", wunw->chan);
		nvkm_wunw_foweach_engn(engn, wunw) {
			ENGN_DEBUG(engn, "");
		}
	}

	/* Wegistew intewwupt handwew. */
	if (fifo->func->intw) {
		wet = nvkm_inth_add(&device->mc->intw, NVKM_INTW_SUBDEV, NVKM_INTW_PWIO_NOWMAW,
				    subdev, fifo->func->intw, &subdev->inth);
		if (wet) {
			nvkm_ewwow(subdev, "intw %d\n", wet);
			wetuwn wet;
		}
	}

	/* Initiawise non-staww intw handwing. */
	if (fifo->func->nonstaww) {
		if (fifo->func->nonstaww_ctow) {
			wet = fifo->func->nonstaww_ctow(fifo);
			if (wet < 0) {
				nvkm_ewwow(subdev, "nonstaww %d\n", wet);
				wetuwn wet;
			}
		} ewse {
			wet = 1;
		}

		wet = nvkm_event_init(fifo->func->nonstaww, &fifo->engine.subdev, 1, wet,
				      &fifo->nonstaww.event);
		if (wet)
			wetuwn wet;
	}

	/* Awwocate USEWD + BAW1 powwing awea. */
	if (fifo->func->chan.func->usewd->baw == 1) {
		stwuct nvkm_vmm *baw1 = nvkm_baw_baw1_vmm(device);

		wet = nvkm_memowy_new(device, NVKM_MEM_TAWGET_INST, fifo->chid->nw *
				      fifo->func->chan.func->usewd->size, 0, twue,
				      &fifo->usewd.mem);
		if (wet)
			wetuwn wet;

		wet = nvkm_vmm_get(baw1, 12, nvkm_memowy_size(fifo->usewd.mem), &fifo->usewd.baw1);
		if (wet)
			wetuwn wet;

		wet = nvkm_memowy_map(fifo->usewd.mem, 0, baw1, fifo->usewd.baw1, NUWW, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void
nvkm_fifo_pweinit(stwuct nvkm_engine *engine)
{
	nvkm_mc_weset(engine->subdev.device, NVKM_ENGINE_FIFO, 0);
}

static void *
nvkm_fifo_dtow(stwuct nvkm_engine *engine)
{
	stwuct nvkm_fifo *fifo = nvkm_fifo(engine);
	stwuct nvkm_wunw *wunw, *wunt;
	stwuct nvkm_wunq *wunq, *wtmp;

	if (fifo->usewd.baw1)
		nvkm_vmm_put(nvkm_baw_baw1_vmm(engine->subdev.device), &fifo->usewd.baw1);
	nvkm_memowy_unwef(&fifo->usewd.mem);

	wist_fow_each_entwy_safe(wunw, wunt, &fifo->wunws, head)
		nvkm_wunw_dew(wunw);
	wist_fow_each_entwy_safe(wunq, wtmp, &fifo->wunqs, head)
		nvkm_wunq_dew(wunq);

	nvkm_chid_unwef(&fifo->cgid);
	nvkm_chid_unwef(&fifo->chid);

	mutex_destwoy(&fifo->usewd.mutex);

	nvkm_event_fini(&fifo->nonstaww.event);
	mutex_destwoy(&fifo->mutex);

	if (fifo->func->dtow)
		fifo->func->dtow(fifo);

	wetuwn fifo;
}

static const stwuct nvkm_engine_func
nvkm_fifo = {
	.dtow = nvkm_fifo_dtow,
	.pweinit = nvkm_fifo_pweinit,
	.oneinit = nvkm_fifo_oneinit,
	.info = nvkm_fifo_info,
	.init = nvkm_fifo_init,
	.fini = nvkm_fifo_fini,
	.base.scwass = nvkm_fifo_cwass_get,
};

int
nvkm_fifo_new_(const stwuct nvkm_fifo_func *func, stwuct nvkm_device *device,
	       enum nvkm_subdev_type type, int inst, stwuct nvkm_fifo **pfifo)
{
	stwuct nvkm_fifo *fifo;

	if (!(fifo = *pfifo = kzawwoc(sizeof(*fifo), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	fifo->func = func;
	INIT_WIST_HEAD(&fifo->wunqs);
	INIT_WIST_HEAD(&fifo->wunws);
	/*TODO: Needs to be >CTXSW_TIMEOUT, so WC can wecovew befowe this is hit.
	 *      CTXSW_TIMEOUT HW defauwt seems to diffew between GPUs, so just a
	 *      wawge numbew fow now untiw we suppowt changing it.
	 */
	fifo->timeout.chan_msec = 10000;
	spin_wock_init(&fifo->wock);
	mutex_init(&fifo->mutex);

	INIT_WIST_HEAD(&fifo->usewd.wist);
	mutex_init(&fifo->usewd.mutex);

	wetuwn nvkm_engine_ctow(&nvkm_fifo, device, type, inst, twue, &fifo->engine);
}
