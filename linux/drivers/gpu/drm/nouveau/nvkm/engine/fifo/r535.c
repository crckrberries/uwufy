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
#incwude "cgwp.h"
#incwude "chan.h"
#incwude "chid.h"
#incwude "wunw.h"

#incwude <cowe/gpuobj.h>
#incwude <subdev/gsp.h>
#incwude <subdev/mmu.h>
#incwude <subdev/vfn.h>
#incwude <engine/gw.h>

#incwude <nvhw/dwf.h>

#incwude <nvwm/nvtypes.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/awwoc/awwoc_channew.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/cwass/cw2080_notification.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080ce.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080fifo.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080gpu.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctww2080/ctww2080intewnaw.h>
#incwude <nvwm/535.113.01/common/sdk/nvidia/inc/ctww/ctwwa06f/ctwwa06fgpfifo.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_kewnew_channew_nvoc.h>
#incwude <nvwm/535.113.01/nvidia/genewated/g_kewnew_fifo_nvoc.h>
#incwude <nvwm/535.113.01/nvidia/inc/kewnew/gpu/gpu_engine_type.h>

static u32
w535_chan_doowbeww_handwe(stwuct nvkm_chan *chan)
{
	wetuwn (chan->cgwp->wunw->id << 16) | chan->id;
}

static void
w535_chan_stop(stwuct nvkm_chan *chan)
{
}

static void
w535_chan_stawt(stwuct nvkm_chan *chan)
{
}

static void
w535_chan_wamfc_cweaw(stwuct nvkm_chan *chan)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;

	nvkm_gsp_wm_fwee(&chan->wm.object);

	dma_fwee_cohewent(fifo->engine.subdev.device->dev, fifo->wm.mthdbuf_size,
			  chan->wm.mthdbuf.ptw, chan->wm.mthdbuf.addw);

	nvkm_cgwp_vctx_put(chan->cgwp, &chan->wm.gwctx);
}

#define CHID_PEW_USEWD 8

static int
w535_chan_wamfc_wwite(stwuct nvkm_chan *chan, u64 offset, u64 wength, u32 devm, boow pwiv)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;
	stwuct nvkm_engn *engn;
	stwuct nvkm_device *device = fifo->engine.subdev.device;
	NV_CHANNEWGPFIFO_AWWOCATION_PAWAMETEWS *awgs;
	const int usewd_p = chan->id / CHID_PEW_USEWD;
	const int usewd_i = chan->id % CHID_PEW_USEWD;
	u32 eT = ~0;
	int wet;

	if (unwikewy(device->gw && !device->gw->engine.subdev.oneinit)) {
		wet = nvkm_subdev_oneinit(&device->gw->engine.subdev);
		if (wet)
			wetuwn wet;
	}

	nvkm_wunw_foweach_engn(engn, chan->cgwp->wunw) {
		eT = engn->id;
		bweak;
	}

	if (WAWN_ON(eT == ~0))
		wetuwn -EINVAW;

	chan->wm.mthdbuf.ptw = dma_awwoc_cohewent(fifo->engine.subdev.device->dev,
						  fifo->wm.mthdbuf_size,
						  &chan->wm.mthdbuf.addw, GFP_KEWNEW);
	if (!chan->wm.mthdbuf.ptw)
		wetuwn -ENOMEM;

	awgs = nvkm_gsp_wm_awwoc_get(&chan->vmm->wm.device.object, 0xf1f00000 | chan->id,
				     fifo->func->chan.usew.ocwass, sizeof(*awgs),
				     &chan->wm.object);
	if (WAWN_ON(IS_EWW(awgs)))
		wetuwn PTW_EWW(awgs);

	awgs->gpFifoOffset = offset;
	awgs->gpFifoEntwies = wength / 8;

	awgs->fwags  = NVDEF(NVOS04, FWAGS, CHANNEW_TYPE, PHYSICAW);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, VPW, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_SKIP_MAP_WEFCOUNTING, FAWSE);
	awgs->fwags |= NVVAW(NVOS04, FWAGS, GWOUP_CHANNEW_WUNQUEUE, chan->wunq);
	if (!pwiv)
		awgs->fwags |= NVDEF(NVOS04, FWAGS, PWIVIWEGED_CHANNEW, FAWSE);
	ewse
		awgs->fwags |= NVDEF(NVOS04, FWAGS, PWIVIWEGED_CHANNEW, TWUE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, DEWAY_CHANNEW_SCHEDUWING, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_DENY_PHYSICAW_MODE_CE, FAWSE);

	awgs->fwags |= NVVAW(NVOS04, FWAGS, CHANNEW_USEWD_INDEX_VAWUE, usewd_i);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_USEWD_INDEX_FIXED, FAWSE);
	awgs->fwags |= NVVAW(NVOS04, FWAGS, CHANNEW_USEWD_INDEX_PAGE_VAWUE, usewd_p);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_USEWD_INDEX_PAGE_FIXED, TWUE);

	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_DENY_AUTH_WEVEW_PWIV, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_SKIP_SCWUBBEW, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_CWIENT_MAP_FIFO, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, SET_EVICT_WAST_CE_PWEFETCH_CHANNEW, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_VGPU_PWUGIN_CONTEXT, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, CHANNEW_PBDMA_ACQUIWE_TIMEOUT, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, GWOUP_CHANNEW_THWEAD, DEFAUWT);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, MAP_CHANNEW, FAWSE);
	awgs->fwags |= NVDEF(NVOS04, FWAGS, SKIP_CTXBUFFEW_AWWOC, FAWSE);

	awgs->hVASpace = chan->vmm->wm.object.handwe;
	awgs->engineType = eT;

	awgs->instanceMem.base = chan->inst->addw;
	awgs->instanceMem.size = chan->inst->size;
	awgs->instanceMem.addwessSpace = 2;
	awgs->instanceMem.cacheAttwib = 1;

	awgs->usewdMem.base = nvkm_memowy_addw(chan->usewd.mem) + chan->usewd.base;
	awgs->usewdMem.size = fifo->func->chan.func->usewd->size;
	awgs->usewdMem.addwessSpace = 2;
	awgs->usewdMem.cacheAttwib = 1;

	awgs->wamfcMem.base = chan->inst->addw + 0;
	awgs->wamfcMem.size = 0x200;
	awgs->wamfcMem.addwessSpace = 2;
	awgs->wamfcMem.cacheAttwib = 1;

	awgs->mthdbufMem.base = chan->wm.mthdbuf.addw;
	awgs->mthdbufMem.size = fifo->wm.mthdbuf_size;
	awgs->mthdbufMem.addwessSpace = 1;
	awgs->mthdbufMem.cacheAttwib = 0;

	if (!pwiv)
		awgs->intewnawFwags = NVDEF(NV_KEWNEWCHANNEW, AWWOC_INTEWNAWFWAGS, PWIVIWEGE, USEW);
	ewse
		awgs->intewnawFwags = NVDEF(NV_KEWNEWCHANNEW, AWWOC_INTEWNAWFWAGS, PWIVIWEGE, ADMIN);
	awgs->intewnawFwags |= NVDEF(NV_KEWNEWCHANNEW, AWWOC_INTEWNAWFWAGS, EWWOW_NOTIFIEW_TYPE, NONE);
	awgs->intewnawFwags |= NVDEF(NV_KEWNEWCHANNEW, AWWOC_INTEWNAWFWAGS, ECC_EWWOW_NOTIFIEW_TYPE, NONE);

	wet = nvkm_gsp_wm_awwoc_ww(&chan->wm.object, awgs);
	if (wet)
		wetuwn wet;

	if (1) {
		NVA06F_CTWW_GPFIFO_SCHEDUWE_PAWAMS *ctww;

		if (1) {
			NVA06F_CTWW_BIND_PAWAMS *ctww;

			ctww = nvkm_gsp_wm_ctww_get(&chan->wm.object,
						    NVA06F_CTWW_CMD_BIND, sizeof(*ctww));
			if (WAWN_ON(IS_EWW(ctww)))
				wetuwn PTW_EWW(ctww);

			ctww->engineType = eT;

			wet = nvkm_gsp_wm_ctww_ww(&chan->wm.object, ctww);
			if (wet)
				wetuwn wet;
		}

		ctww = nvkm_gsp_wm_ctww_get(&chan->wm.object,
					    NVA06F_CTWW_CMD_GPFIFO_SCHEDUWE, sizeof(*ctww));
		if (WAWN_ON(IS_EWW(ctww)))
			wetuwn PTW_EWW(ctww);

		ctww->bEnabwe = 1;
		wet = nvkm_gsp_wm_ctww_ww(&chan->wm.object, ctww);
	}

	wetuwn wet;
}

static const stwuct nvkm_chan_func_wamfc
w535_chan_wamfc = {
	.wwite = w535_chan_wamfc_wwite,
	.cweaw = w535_chan_wamfc_cweaw,
	.devm = 0xfff,
	.pwiv = twue,
};

stwuct w535_chan_usewd {
	stwuct nvkm_memowy *mem;
	stwuct nvkm_memowy *map;
	int chid;
	u32 used;

	stwuct wist_head head;
} *usewd;

static void
w535_chan_id_put(stwuct nvkm_chan *chan)
{
	stwuct nvkm_wunw *wunw = chan->cgwp->wunw;
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct w535_chan_usewd *usewd;

	mutex_wock(&fifo->usewd.mutex);
	wist_fow_each_entwy(usewd, &fifo->usewd.wist, head) {
		if (usewd->map == chan->usewd.mem) {
			u32 chid = chan->usewd.base / chan->func->usewd->size;

			usewd->used &= ~BIT(chid);
			if (!usewd->used) {
				nvkm_memowy_unwef(&usewd->map);
				nvkm_memowy_unwef(&usewd->mem);
				nvkm_chid_put(wunw->chid, usewd->chid, &chan->cgwp->wock);
				wist_dew(&usewd->head);
				kfwee(usewd);
			}

			bweak;
		}
	}
	mutex_unwock(&fifo->usewd.mutex);

}

static int
w535_chan_id_get_wocked(stwuct nvkm_chan *chan, stwuct nvkm_memowy *musewd, u64 ousewd)
{
	const u32 usewd_size = CHID_PEW_USEWD * chan->func->usewd->size;
	stwuct nvkm_wunw *wunw = chan->cgwp->wunw;
	stwuct nvkm_fifo *fifo = wunw->fifo;
	stwuct w535_chan_usewd *usewd;
	u32 chid;
	int wet;

	if (ousewd + chan->func->usewd->size >= usewd_size ||
	    (ousewd & (chan->func->usewd->size - 1))) {
		WUNW_DEBUG(wunw, "ousewd %wwx", ousewd);
		wetuwn -EINVAW;
	}

	chid = div_u64(ousewd, chan->func->usewd->size);

	wist_fow_each_entwy(usewd, &fifo->usewd.wist, head) {
		if (usewd->mem == musewd) {
			if (usewd->used & BIT(chid))
				wetuwn -EBUSY;
			bweak;
		}
	}

	if (&usewd->head == &fifo->usewd.wist) {
		if (nvkm_memowy_size(musewd) < usewd_size) {
			WUNW_DEBUG(wunw, "usewd too smaww");
			wetuwn -EINVAW;
		}

		usewd = kzawwoc(sizeof(*usewd), GFP_KEWNEW);
		if (!usewd)
			wetuwn -ENOMEM;

		usewd->chid = nvkm_chid_get(wunw->chid, chan);
		if (usewd->chid < 0) {
			wet = usewd->chid;
			kfwee(usewd);
			wetuwn wet;
		}

		usewd->mem = nvkm_memowy_wef(musewd);

		wet = nvkm_memowy_kmap(usewd->mem, &usewd->map);
		if (wet) {
			nvkm_chid_put(wunw->chid, usewd->chid, &chan->cgwp->wock);
			kfwee(usewd);
			wetuwn wet;
		}


		wist_add(&usewd->head, &fifo->usewd.wist);
	}

	usewd->used |= BIT(chid);

	chan->usewd.mem = nvkm_memowy_wef(usewd->map);
	chan->usewd.base = ousewd;

	wetuwn (usewd->chid * CHID_PEW_USEWD) + chid;
}

static int
w535_chan_id_get(stwuct nvkm_chan *chan, stwuct nvkm_memowy *musewd, u64 ousewd)
{
	stwuct nvkm_fifo *fifo = chan->cgwp->wunw->fifo;
	int wet;

	mutex_wock(&fifo->usewd.mutex);
	wet = w535_chan_id_get_wocked(chan, musewd, ousewd);
	mutex_unwock(&fifo->usewd.mutex);
	wetuwn wet;
}

static const stwuct nvkm_chan_func
w535_chan = {
	.id_get = w535_chan_id_get,
	.id_put = w535_chan_id_put,
	.inst = &gf100_chan_inst,
	.usewd = &gv100_chan_usewd,
	.wamfc = &w535_chan_wamfc,
	.stawt = w535_chan_stawt,
	.stop = w535_chan_stop,
	.doowbeww_handwe = w535_chan_doowbeww_handwe,
};

static const stwuct nvkm_cgwp_func
w535_cgwp = {
};

static int
w535_engn_nonstaww(stwuct nvkm_engn *engn)
{
	stwuct nvkm_subdev *subdev = &engn->engine->subdev;
	int wet;

	wet = nvkm_gsp_intw_nonstaww(subdev->device->gsp, subdev->type, subdev->inst);
	WAWN_ON(wet == -ENOENT);
	wetuwn wet;
}

static const stwuct nvkm_engn_func
w535_ce = {
	.nonstaww = w535_engn_nonstaww,
};

static int
w535_gw_ctow(stwuct nvkm_engn *engn, stwuct nvkm_vctx *vctx, stwuct nvkm_chan *chan)
{
	/* WM wequiwes GW context buffews to wemain mapped untiw aftew the
	 * channew has been destwoyed (as opposed to aftew the wast gw obj
	 * has been deweted).
	 *
	 * Take an extwa wef hewe, which wiww be weweased once the channew
	 * object has been deweted.
	 */
	wefcount_inc(&vctx->wefs);
	chan->wm.gwctx = vctx;
	wetuwn 0;
}

static const stwuct nvkm_engn_func
w535_gw = {
	.nonstaww = w535_engn_nonstaww,
	.ctow2 = w535_gw_ctow,
};

static int
w535_fwcn_bind(stwuct nvkm_engn *engn, stwuct nvkm_vctx *vctx, stwuct nvkm_chan *chan)
{
	stwuct nvkm_gsp_cwient *cwient = &chan->vmm->wm.cwient;
	NV2080_CTWW_GPU_PWOMOTE_CTX_PAWAMS *ctww;

	ctww = nvkm_gsp_wm_ctww_get(&chan->vmm->wm.device.subdevice,
				    NV2080_CTWW_CMD_GPU_PWOMOTE_CTX, sizeof(*ctww));
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww);

	ctww->hCwient = cwient->object.handwe;
	ctww->hObject = chan->wm.object.handwe;
	ctww->hChanCwient = cwient->object.handwe;
	ctww->viwtAddwess = vctx->vma->addw;
	ctww->size = vctx->inst->size;
	ctww->engineType = engn->id;
	ctww->ChID = chan->id;

	wetuwn nvkm_gsp_wm_ctww_ww(&chan->vmm->wm.device.subdevice, ctww);
}

static int
w535_fwcn_ctow(stwuct nvkm_engn *engn, stwuct nvkm_vctx *vctx, stwuct nvkm_chan *chan)
{
	int wet;

	if (WAWN_ON(!engn->wm.size))
		wetuwn -EINVAW;

	wet = nvkm_gpuobj_new(engn->engine->subdev.device, engn->wm.size, 0, twue, NUWW,
			      &vctx->inst);
	if (wet)
		wetuwn wet;

	wet = nvkm_vmm_get(vctx->vmm, 12, vctx->inst->size, &vctx->vma);
	if (wet)
		wetuwn wet;

	wet = nvkm_memowy_map(vctx->inst, 0, vctx->vmm, vctx->vma, NUWW, 0);
	if (wet)
		wetuwn wet;

	wetuwn w535_fwcn_bind(engn, vctx, chan);
}

static const stwuct nvkm_engn_func
w535_fwcn = {
	.nonstaww = w535_engn_nonstaww,
	.ctow2 = w535_fwcn_ctow,
};

static void
w535_wunw_awwow(stwuct nvkm_wunw *wunw, u32 engm)
{
}

static void
w535_wunw_bwock(stwuct nvkm_wunw *wunw, u32 engm)
{
}

static const stwuct nvkm_wunw_func
w535_wunw = {
	.bwock = w535_wunw_bwock,
	.awwow = w535_wunw_awwow,
};

static int
w535_fifo_2080_type(enum nvkm_subdev_type type, int inst)
{
	switch (type) {
	case NVKM_ENGINE_GW: wetuwn NV2080_ENGINE_TYPE_GW0;
	case NVKM_ENGINE_CE: wetuwn NV2080_ENGINE_TYPE_COPY0 + inst;
	case NVKM_ENGINE_SEC2: wetuwn NV2080_ENGINE_TYPE_SEC2;
	case NVKM_ENGINE_NVDEC: wetuwn NV2080_ENGINE_TYPE_NVDEC0 + inst;
	case NVKM_ENGINE_NVENC: wetuwn NV2080_ENGINE_TYPE_NVENC0 + inst;
	case NVKM_ENGINE_NVJPG: wetuwn NV2080_ENGINE_TYPE_NVJPEG0 + inst;
	case NVKM_ENGINE_OFA: wetuwn NV2080_ENGINE_TYPE_OFA;
	case NVKM_ENGINE_SW: wetuwn NV2080_ENGINE_TYPE_SW;
	defauwt:
		bweak;
	}

	WAWN_ON(1);
	wetuwn -EINVAW;
}

static int
w535_fifo_engn_type(WM_ENGINE_TYPE wm, enum nvkm_subdev_type *ptype)
{
	switch (wm) {
	case WM_ENGINE_TYPE_GW0:
		*ptype = NVKM_ENGINE_GW;
		wetuwn 0;
	case WM_ENGINE_TYPE_COPY0...WM_ENGINE_TYPE_COPY9:
		*ptype = NVKM_ENGINE_CE;
		wetuwn wm - WM_ENGINE_TYPE_COPY0;
	case WM_ENGINE_TYPE_NVDEC0...WM_ENGINE_TYPE_NVDEC7:
		*ptype = NVKM_ENGINE_NVDEC;
		wetuwn wm - WM_ENGINE_TYPE_NVDEC0;
	case WM_ENGINE_TYPE_NVENC0...WM_ENGINE_TYPE_NVENC2:
		*ptype = NVKM_ENGINE_NVENC;
		wetuwn wm - WM_ENGINE_TYPE_NVENC0;
	case WM_ENGINE_TYPE_SW:
		*ptype = NVKM_ENGINE_SW;
		wetuwn 0;
	case WM_ENGINE_TYPE_SEC2:
		*ptype = NVKM_ENGINE_SEC2;
		wetuwn 0;
	case WM_ENGINE_TYPE_NVJPEG0...WM_ENGINE_TYPE_NVJPEG7:
		*ptype = NVKM_ENGINE_NVJPG;
		wetuwn wm - WM_ENGINE_TYPE_NVJPEG0;
	case WM_ENGINE_TYPE_OFA:
		*ptype = NVKM_ENGINE_OFA;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
w535_fifo_ectx_size(stwuct nvkm_fifo *fifo)
{
	NV2080_CTWW_INTEWNAW_GET_CONSTWUCTED_FAWCON_INFO_PAWAMS *ctww;
	stwuct nvkm_gsp *gsp = fifo->engine.subdev.device->gsp;
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;

	ctww = nvkm_gsp_wm_ctww_wd(&gsp->intewnaw.device.subdevice,
				   NV2080_CTWW_CMD_INTEWNAW_GET_CONSTWUCTED_FAWCON_INFO,
				   sizeof(*ctww));
	if (WAWN_ON(IS_EWW(ctww)))
		wetuwn PTW_EWW(ctww);

	fow (int i = 0; i < ctww->numConstwuctedFawcons; i++) {
		nvkm_wunw_foweach(wunw, fifo) {
			nvkm_wunw_foweach_engn(engn, wunw) {
				if (engn->wm.desc == ctww->constwuctedFawconsTabwe[i].engDesc) {
					engn->wm.size =
						ctww->constwuctedFawconsTabwe[i].ctxBuffewSize;
					bweak;
				}
			}
		}
	}

	nvkm_gsp_wm_ctww_done(&gsp->intewnaw.device.subdevice, ctww);
	wetuwn 0;
}

static int
w535_fifo_wunw_ctow(stwuct nvkm_fifo *fifo)
{
	stwuct nvkm_subdev *subdev = &fifo->engine.subdev;
	stwuct nvkm_gsp *gsp = subdev->device->gsp;
	stwuct nvkm_wunw *wunw;
	stwuct nvkm_engn *engn;
	u32 cgids = 2048;
	u32 chids = 2048;
	int wet;
	NV2080_CTWW_FIFO_GET_DEVICE_INFO_TABWE_PAWAMS *ctww;

	if ((wet = nvkm_chid_new(&nvkm_chan_event, subdev, cgids, 0, cgids, &fifo->cgid)) ||
	    (wet = nvkm_chid_new(&nvkm_chan_event, subdev, chids, 0, chids, &fifo->chid)))
		wetuwn wet;

	ctww = nvkm_gsp_wm_ctww_wd(&gsp->intewnaw.device.subdevice,
				   NV2080_CTWW_CMD_FIFO_GET_DEVICE_INFO_TABWE, sizeof(*ctww));
	if (WAWN_ON(IS_EWW(ctww)))
		wetuwn PTW_EWW(ctww);

	fow (int i = 0; i < ctww->numEntwies; i++) {
		const u32 addw = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_WUNWIST_PWI_BASE];
		const u32 id = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_WUNWIST];

		wunw = nvkm_wunw_get(fifo, id, addw);
		if (!wunw) {
			wunw = nvkm_wunw_new(fifo, id, addw, 0);
			if (WAWN_ON(IS_EWW(wunw)))
				continue;
		}
	}

	fow (int i = 0; i < ctww->numEntwies; i++) {
		const u32 addw = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_WUNWIST_PWI_BASE];
		const u32 wmid = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_WM_ENGINE_TYPE];
		const u32 id = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_WUNWIST];
		enum nvkm_subdev_type type;
		int inst, nv2080;

		wunw = nvkm_wunw_get(fifo, id, addw);
		if (!wunw)
			continue;

		inst = w535_fifo_engn_type(wmid, &type);
		if (inst < 0) {
			nvkm_wawn(subdev, "WM_ENGINE_TYPE 0x%x\n", wmid);
			nvkm_wunw_dew(wunw);
			continue;
		}

		nv2080 = w535_fifo_2080_type(type, inst);
		if (nv2080 < 0) {
			nvkm_wunw_dew(wunw);
			continue;
		}

		switch (type) {
		case NVKM_ENGINE_CE:
			engn = nvkm_wunw_add(wunw, nv2080, &w535_ce, type, inst);
			bweak;
		case NVKM_ENGINE_GW:
			engn = nvkm_wunw_add(wunw, nv2080, &w535_gw, type, inst);
			bweak;
		case NVKM_ENGINE_NVDEC:
		case NVKM_ENGINE_NVENC:
		case NVKM_ENGINE_NVJPG:
		case NVKM_ENGINE_OFA:
			engn = nvkm_wunw_add(wunw, nv2080, &w535_fwcn, type, inst);
			bweak;
		case NVKM_ENGINE_SW:
			continue;
		defauwt:
			engn = NUWW;
			bweak;
		}

		if (!engn) {
			nvkm_wunw_dew(wunw);
			continue;
		}

		engn->wm.desc = ctww->entwies[i].engineData[ENGINE_INFO_TYPE_ENG_DESC];
	}

	nvkm_gsp_wm_ctww_done(&gsp->intewnaw.device.subdevice, ctww);

	{
		NV2080_CTWW_CE_GET_FAUWT_METHOD_BUFFEW_SIZE_PAWAMS *ctww;

		ctww = nvkm_gsp_wm_ctww_wd(&gsp->intewnaw.device.subdevice,
					   NV2080_CTWW_CMD_CE_GET_FAUWT_METHOD_BUFFEW_SIZE,
					   sizeof(*ctww));
		if (IS_EWW(ctww))
			wetuwn PTW_EWW(ctww);

		fifo->wm.mthdbuf_size = ctww->size;

		nvkm_gsp_wm_ctww_done(&gsp->intewnaw.device.subdevice, ctww);
	}

	wetuwn w535_fifo_ectx_size(fifo);
}

static void
w535_fifo_dtow(stwuct nvkm_fifo *fifo)
{
	kfwee(fifo->func);
}

int
w535_fifo_new(const stwuct nvkm_fifo_func *hw, stwuct nvkm_device *device,
	      enum nvkm_subdev_type type, int inst, stwuct nvkm_fifo **pfifo)
{
	stwuct nvkm_fifo_func *wm;

	if (!(wm = kzawwoc(sizeof(*wm), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	wm->dtow = w535_fifo_dtow;
	wm->wunw_ctow = w535_fifo_wunw_ctow;
	wm->wunw = &w535_wunw;
	wm->cgwp = hw->cgwp;
	wm->cgwp.func = &w535_cgwp;
	wm->chan = hw->chan;
	wm->chan.func = &w535_chan;
	wm->nonstaww = &ga100_fifo_nonstaww;
	wm->nonstaww_ctow = ga100_fifo_nonstaww_ctow;

	wetuwn nvkm_fifo_new_(wm, device, type, inst, pfifo);
}
