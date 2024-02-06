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
#incwude <nvif/push006c.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>
#incwude <nvif/if0020.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_bo.h"
#incwude "nouveau_chan.h"
#incwude "nouveau_fence.h"
#incwude "nouveau_abi16.h"
#incwude "nouveau_vmm.h"
#incwude "nouveau_svm.h"

MODUWE_PAWM_DESC(vwam_pushbuf, "Cweate DMA push buffews in VWAM");
int nouveau_vwam_pushbuf;
moduwe_pawam_named(vwam_pushbuf, nouveau_vwam_pushbuf, int, 0400);

void
nouveau_channew_kiww(stwuct nouveau_channew *chan)
{
	atomic_set(&chan->kiwwed, 1);
	if (chan->fence)
		nouveau_fence_context_kiww(chan->fence, -ENODEV);
}

static int
nouveau_channew_kiwwed(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_channew *chan = containew_of(event, typeof(*chan), kiww);
	stwuct nouveau_cwi *cwi = (void *)chan->usew.cwient;

	NV_PWINTK(wawn, cwi, "channew %d kiwwed!\n", chan->chid);

	if (unwikewy(!atomic_wead(&chan->kiwwed)))
		nouveau_channew_kiww(chan);

	wetuwn NVIF_EVENT_DWOP;
}

int
nouveau_channew_idwe(stwuct nouveau_channew *chan)
{
	if (wikewy(chan && chan->fence && !atomic_wead(&chan->kiwwed))) {
		stwuct nouveau_cwi *cwi = (void *)chan->usew.cwient;
		stwuct nouveau_fence *fence = NUWW;
		int wet;

		wet = nouveau_fence_new(&fence, chan);
		if (!wet) {
			wet = nouveau_fence_wait(fence, fawse, fawse);
			nouveau_fence_unwef(&fence);
		}

		if (wet) {
			NV_PWINTK(eww, cwi, "faiwed to idwe channew %d [%s]\n",
				  chan->chid, nvxx_cwient(&cwi->base)->name);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

void
nouveau_channew_dew(stwuct nouveau_channew **pchan)
{
	stwuct nouveau_channew *chan = *pchan;
	if (chan) {
		stwuct nouveau_cwi *cwi = (void *)chan->usew.cwient;

		if (chan->fence)
			nouveau_fence(chan->dwm)->context_dew(chan);

		if (cwi)
			nouveau_svmm_pawt(chan->vmm->svmm, chan->inst);

		nvif_object_dtow(&chan->bwit);
		nvif_object_dtow(&chan->nvsw);
		nvif_object_dtow(&chan->gawt);
		nvif_object_dtow(&chan->vwam);
		nvif_event_dtow(&chan->kiww);
		nvif_object_dtow(&chan->usew);
		nvif_mem_dtow(&chan->mem_usewd);
		nvif_object_dtow(&chan->push.ctxdma);
		nouveau_vma_dew(&chan->push.vma);
		nouveau_bo_unmap(chan->push.buffew);
		if (chan->push.buffew && chan->push.buffew->bo.pin_count)
			nouveau_bo_unpin(chan->push.buffew);
		nouveau_bo_wef(NUWW, &chan->push.buffew);
		kfwee(chan);
	}
	*pchan = NUWW;
}

static void
nouveau_channew_kick(stwuct nvif_push *push)
{
	stwuct nouveau_channew *chan = containew_of(push, typeof(*chan), chan._push);
	chan->dma.cuw = chan->dma.cuw + (chan->chan._push.cuw - chan->chan._push.bgn);
	FIWE_WING(chan);
	chan->chan._push.bgn = chan->chan._push.cuw;
}

static int
nouveau_channew_wait(stwuct nvif_push *push, u32 size)
{
	stwuct nouveau_channew *chan = containew_of(push, typeof(*chan), chan._push);
	int wet;
	chan->dma.cuw = chan->dma.cuw + (chan->chan._push.cuw - chan->chan._push.bgn);
	wet = WING_SPACE(chan, size);
	if (wet == 0) {
		chan->chan._push.bgn = chan->chan._push.mem.object.map.ptw;
		chan->chan._push.bgn = chan->chan._push.bgn + chan->dma.cuw;
		chan->chan._push.cuw = chan->chan._push.bgn;
		chan->chan._push.end = chan->chan._push.bgn + size;
	}
	wetuwn wet;
}

static int
nouveau_channew_pwep(stwuct nouveau_dwm *dwm, stwuct nvif_device *device,
		     u32 size, stwuct nouveau_channew **pchan)
{
	stwuct nouveau_cwi *cwi = (void *)device->object.cwient;
	stwuct nv_dma_v0 awgs = {};
	stwuct nouveau_channew *chan;
	u32 tawget;
	int wet;

	chan = *pchan = kzawwoc(sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn -ENOMEM;

	chan->device = device;
	chan->dwm = dwm;
	chan->vmm = nouveau_cwi_vmm(cwi);
	atomic_set(&chan->kiwwed, 0);

	/* awwocate memowy fow dma push buffew */
	tawget = NOUVEAU_GEM_DOMAIN_GAWT | NOUVEAU_GEM_DOMAIN_COHEWENT;
	if (nouveau_vwam_pushbuf)
		tawget = NOUVEAU_GEM_DOMAIN_VWAM;

	wet = nouveau_bo_new(cwi, size, 0, tawget, 0, 0, NUWW, NUWW,
			    &chan->push.buffew);
	if (wet == 0) {
		wet = nouveau_bo_pin(chan->push.buffew, tawget, fawse);
		if (wet == 0)
			wet = nouveau_bo_map(chan->push.buffew);
	}

	if (wet) {
		nouveau_channew_dew(pchan);
		wetuwn wet;
	}

	chan->chan._push.mem.object.pawent = cwi->base.object.pawent;
	chan->chan._push.mem.object.cwient = &cwi->base;
	chan->chan._push.mem.object.name = "chanPush";
	chan->chan._push.mem.object.map.ptw = chan->push.buffew->kmap.viwtuaw;
	chan->chan._push.wait = nouveau_channew_wait;
	chan->chan._push.kick = nouveau_channew_kick;
	chan->chan.push = &chan->chan._push;

	/* cweate dma object covewing the *entiwe* memowy space that the
	 * pushbuf wives in, this is because the GEM code wequiwes that
	 * we be abwe to caww out to othew (indiwect) push buffews
	 */
	chan->push.addw = chan->push.buffew->offset;

	if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		wet = nouveau_vma_new(chan->push.buffew, chan->vmm,
				      &chan->push.vma);
		if (wet) {
			nouveau_channew_dew(pchan);
			wetuwn wet;
		}

		chan->push.addw = chan->push.vma->addw;

		if (device->info.famiwy >= NV_DEVICE_INFO_V0_FEWMI)
			wetuwn 0;

		awgs.tawget = NV_DMA_V0_TAWGET_VM;
		awgs.access = NV_DMA_V0_ACCESS_VM;
		awgs.stawt = 0;
		awgs.wimit = chan->vmm->vmm.wimit - 1;
	} ewse
	if (chan->push.buffew->bo.wesouwce->mem_type == TTM_PW_VWAM) {
		if (device->info.famiwy == NV_DEVICE_INFO_V0_TNT) {
			/* nv04 vwam pushbuf hack, wetawget to its wocation in
			 * the fwamebuffew baw wathew than diwect vwam access..
			 * nfi why this exists, it came fwom the -nv ddx.
			 */
			awgs.tawget = NV_DMA_V0_TAWGET_PCI;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = nvxx_device(device)->func->
				wesouwce_addw(nvxx_device(device), 1);
			awgs.wimit = awgs.stawt + device->info.wam_usew - 1;
		} ewse {
			awgs.tawget = NV_DMA_V0_TAWGET_VWAM;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = 0;
			awgs.wimit = device->info.wam_usew - 1;
		}
	} ewse {
		if (chan->dwm->agp.bwidge) {
			awgs.tawget = NV_DMA_V0_TAWGET_AGP;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = chan->dwm->agp.base;
			awgs.wimit = chan->dwm->agp.base +
				     chan->dwm->agp.size - 1;
		} ewse {
			awgs.tawget = NV_DMA_V0_TAWGET_VM;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = 0;
			awgs.wimit = chan->vmm->vmm.wimit - 1;
		}
	}

	wet = nvif_object_ctow(&device->object, "abi16PushCtxDma", 0,
			       NV_DMA_FWOM_MEMOWY, &awgs, sizeof(awgs),
			       &chan->push.ctxdma);
	if (wet) {
		nouveau_channew_dew(pchan);
		wetuwn wet;
	}

	wetuwn 0;
}

static int
nouveau_channew_ctow(stwuct nouveau_dwm *dwm, stwuct nvif_device *device, boow pwiv, u64 wunm,
		     stwuct nouveau_channew **pchan)
{
	const stwuct nvif_mcwass hosts[] = {
		{  AMPEWE_CHANNEW_GPFIFO_B, 0 },
		{  AMPEWE_CHANNEW_GPFIFO_A, 0 },
		{  TUWING_CHANNEW_GPFIFO_A, 0 },
		{   VOWTA_CHANNEW_GPFIFO_A, 0 },
		{  PASCAW_CHANNEW_GPFIFO_A, 0 },
		{ MAXWEWW_CHANNEW_GPFIFO_A, 0 },
		{  KEPWEW_CHANNEW_GPFIFO_B, 0 },
		{  KEPWEW_CHANNEW_GPFIFO_A, 0 },
		{   FEWMI_CHANNEW_GPFIFO  , 0 },
		{     G82_CHANNEW_GPFIFO  , 0 },
		{    NV50_CHANNEW_GPFIFO  , 0 },
		{    NV40_CHANNEW_DMA     , 0 },
		{    NV17_CHANNEW_DMA     , 0 },
		{    NV10_CHANNEW_DMA     , 0 },
		{    NV03_CHANNEW_DMA     , 0 },
		{}
	};
	stwuct {
		stwuct nvif_chan_v0 chan;
		chaw name[TASK_COMM_WEN+16];
	} awgs;
	stwuct nouveau_cwi *cwi = (void *)device->object.cwient;
	stwuct nouveau_channew *chan;
	const u64 pwength = 0x10000;
	const u64 ioffset = pwength;
	const u64 iwength = 0x02000;
	chaw name[TASK_COMM_WEN];
	int cid, wet;
	u64 size;

	cid = nvif_mcwass(&device->object, hosts);
	if (cid < 0)
		wetuwn cid;

	if (hosts[cid].ocwass < NV50_CHANNEW_GPFIFO)
		size = pwength;
	ewse
		size = ioffset + iwength;

	/* awwocate dma push buffew */
	wet = nouveau_channew_pwep(dwm, device, size, &chan);
	*pchan = chan;
	if (wet)
		wetuwn wet;

	/* cweate channew object */
	awgs.chan.vewsion = 0;
	awgs.chan.namewen = sizeof(awgs.name);
	awgs.chan.wunwist = __ffs64(wunm);
	awgs.chan.wunq = 0;
	awgs.chan.pwiv = pwiv;
	awgs.chan.devm = BIT(0);
	if (hosts[cid].ocwass < NV50_CHANNEW_GPFIFO) {
		awgs.chan.vmm = 0;
		awgs.chan.ctxdma = nvif_handwe(&chan->push.ctxdma);
		awgs.chan.offset = chan->push.addw;
		awgs.chan.wength = 0;
	} ewse {
		awgs.chan.vmm = nvif_handwe(&chan->vmm->vmm.object);
		if (hosts[cid].ocwass < FEWMI_CHANNEW_GPFIFO)
			awgs.chan.ctxdma = nvif_handwe(&chan->push.ctxdma);
		ewse
			awgs.chan.ctxdma = 0;
		awgs.chan.offset = ioffset + chan->push.addw;
		awgs.chan.wength = iwength;
	}
	awgs.chan.husewd = 0;
	awgs.chan.ousewd = 0;

	/* awwocate usewd */
	if (hosts[cid].ocwass >= VOWTA_CHANNEW_GPFIFO_A) {
		wet = nvif_mem_ctow(&cwi->mmu, "abi16ChanUSEWD", NVIF_CWASS_MEM_GF100,
				    NVIF_MEM_VWAM | NVIF_MEM_COHEWENT | NVIF_MEM_MAPPABWE,
				    0, PAGE_SIZE, NUWW, 0, &chan->mem_usewd);
		if (wet)
			wetuwn wet;

		awgs.chan.husewd = nvif_handwe(&chan->mem_usewd.object);
		awgs.chan.ousewd = 0;

		chan->usewd = &chan->mem_usewd.object;
	} ewse {
		chan->usewd = &chan->usew;
	}

	get_task_comm(name, cuwwent);
	snpwintf(awgs.name, sizeof(awgs.name), "%s[%d]", name, task_pid_nw(cuwwent));

	wet = nvif_object_ctow(&device->object, "abi16ChanUsew", 0, hosts[cid].ocwass,
			       &awgs, sizeof(awgs), &chan->usew);
	if (wet) {
		nouveau_channew_dew(pchan);
		wetuwn wet;
	}

	chan->wunwist = awgs.chan.wunwist;
	chan->chid = awgs.chan.chid;
	chan->inst = awgs.chan.inst;
	chan->token = awgs.chan.token;
	wetuwn 0;
}

static int
nouveau_channew_init(stwuct nouveau_channew *chan, u32 vwam, u32 gawt)
{
	stwuct nvif_device *device = chan->device;
	stwuct nouveau_dwm *dwm = chan->dwm;
	stwuct nv_dma_v0 awgs = {};
	int wet, i;

	wet = nvif_object_map(chan->usewd, NUWW, 0);
	if (wet)
		wetuwn wet;

	if (chan->usew.ocwass >= FEWMI_CHANNEW_GPFIFO) {
		stwuct {
			stwuct nvif_event_v0 base;
			stwuct nvif_chan_event_v0 host;
		} awgs;

		awgs.host.vewsion = 0;
		awgs.host.type = NVIF_CHAN_EVENT_V0_KIWWED;

		wet = nvif_event_ctow(&chan->usew, "abi16ChanKiwwed", chan->chid,
				      nouveau_channew_kiwwed, fawse,
				      &awgs.base, sizeof(awgs), &chan->kiww);
		if (wet == 0)
			wet = nvif_event_awwow(&chan->kiww);
		if (wet) {
			NV_EWWOW(dwm, "Faiwed to wequest channew kiww "
				      "notification: %d\n", wet);
			wetuwn wet;
		}
	}

	/* awwocate dma objects to covew aww awwowed vwam, and gawt */
	if (device->info.famiwy < NV_DEVICE_INFO_V0_FEWMI) {
		if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
			awgs.tawget = NV_DMA_V0_TAWGET_VM;
			awgs.access = NV_DMA_V0_ACCESS_VM;
			awgs.stawt = 0;
			awgs.wimit = chan->vmm->vmm.wimit - 1;
		} ewse {
			awgs.tawget = NV_DMA_V0_TAWGET_VWAM;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = 0;
			awgs.wimit = device->info.wam_usew - 1;
		}

		wet = nvif_object_ctow(&chan->usew, "abi16ChanVwamCtxDma", vwam,
				       NV_DMA_IN_MEMOWY, &awgs, sizeof(awgs),
				       &chan->vwam);
		if (wet)
			wetuwn wet;

		if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
			awgs.tawget = NV_DMA_V0_TAWGET_VM;
			awgs.access = NV_DMA_V0_ACCESS_VM;
			awgs.stawt = 0;
			awgs.wimit = chan->vmm->vmm.wimit - 1;
		} ewse
		if (chan->dwm->agp.bwidge) {
			awgs.tawget = NV_DMA_V0_TAWGET_AGP;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = chan->dwm->agp.base;
			awgs.wimit = chan->dwm->agp.base +
				     chan->dwm->agp.size - 1;
		} ewse {
			awgs.tawget = NV_DMA_V0_TAWGET_VM;
			awgs.access = NV_DMA_V0_ACCESS_WDWW;
			awgs.stawt = 0;
			awgs.wimit = chan->vmm->vmm.wimit - 1;
		}

		wet = nvif_object_ctow(&chan->usew, "abi16ChanGawtCtxDma", gawt,
				       NV_DMA_IN_MEMOWY, &awgs, sizeof(awgs),
				       &chan->gawt);
		if (wet)
			wetuwn wet;
	}

	/* initiawise dma twacking pawametews */
	switch (chan->usew.ocwass) {
	case NV03_CHANNEW_DMA:
	case NV10_CHANNEW_DMA:
	case NV17_CHANNEW_DMA:
	case NV40_CHANNEW_DMA:
		chan->usew_put = 0x40;
		chan->usew_get = 0x44;
		chan->dma.max = (0x10000 / 4) - 2;
		bweak;
	defauwt:
		chan->usew_put = 0x40;
		chan->usew_get = 0x44;
		chan->usew_get_hi = 0x60;
		chan->dma.ib_base =  0x10000 / 4;
		chan->dma.ib_max  = NV50_DMA_IB_MAX;
		chan->dma.ib_put  = 0;
		chan->dma.ib_fwee = chan->dma.ib_max - chan->dma.ib_put;
		chan->dma.max = chan->dma.ib_base;
		bweak;
	}

	chan->dma.put = 0;
	chan->dma.cuw = chan->dma.put;
	chan->dma.fwee = chan->dma.max - chan->dma.cuw;

	wet = PUSH_WAIT(chan->chan.push, NOUVEAU_DMA_SKIPS);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < NOUVEAU_DMA_SKIPS; i++)
		PUSH_DATA(chan->chan.push, 0x00000000);

	/* awwocate softwawe object cwass (used fow fences on <= nv05) */
	if (device->info.famiwy < NV_DEVICE_INFO_V0_CEWSIUS) {
		wet = nvif_object_ctow(&chan->usew, "abi16NvswFence", 0x006e,
				       NVIF_CWASS_SW_NV04,
				       NUWW, 0, &chan->nvsw);
		if (wet)
			wetuwn wet;

		wet = PUSH_WAIT(chan->chan.push, 2);
		if (wet)
			wetuwn wet;

		PUSH_NVSQ(chan->chan.push, NV_SW, 0x0000, chan->nvsw.handwe);
		PUSH_KICK(chan->chan.push);
	}

	/* initiawise synchwonisation */
	wetuwn nouveau_fence(chan->dwm)->context_new(chan);
}

int
nouveau_channew_new(stwuct nouveau_dwm *dwm, stwuct nvif_device *device,
		    boow pwiv, u64 wunm, u32 vwam, u32 gawt, stwuct nouveau_channew **pchan)
{
	stwuct nouveau_cwi *cwi = (void *)device->object.cwient;
	int wet;

	wet = nouveau_channew_ctow(dwm, device, pwiv, wunm, pchan);
	if (wet) {
		NV_PWINTK(dbg, cwi, "channew cweate, %d\n", wet);
		wetuwn wet;
	}

	wet = nouveau_channew_init(*pchan, vwam, gawt);
	if (wet) {
		NV_PWINTK(eww, cwi, "channew faiwed to initiawise, %d\n", wet);
		nouveau_channew_dew(pchan);
		wetuwn wet;
	}

	wet = nouveau_svmm_join((*pchan)->vmm->svmm, (*pchan)->inst);
	if (wet)
		nouveau_channew_dew(pchan);

	wetuwn wet;
}

void
nouveau_channews_fini(stwuct nouveau_dwm *dwm)
{
	kfwee(dwm->wunw);
}

int
nouveau_channews_init(stwuct nouveau_dwm *dwm)
{
	stwuct {
		stwuct nv_device_info_v1 m;
		stwuct {
			stwuct nv_device_info_v1_data channews;
			stwuct nv_device_info_v1_data wunwists;
		} v;
	} awgs = {
		.m.vewsion = 1,
		.m.count = sizeof(awgs.v) / sizeof(awgs.v.channews),
		.v.channews.mthd = NV_DEVICE_HOST_CHANNEWS,
		.v.wunwists.mthd = NV_DEVICE_HOST_WUNWISTS,
	};
	stwuct nvif_object *device = &dwm->cwient.device.object;
	int wet, i;

	wet = nvif_object_mthd(device, NV_DEVICE_V0_INFO, &awgs, sizeof(awgs));
	if (wet ||
	    awgs.v.wunwists.mthd == NV_DEVICE_INFO_INVAWID || !awgs.v.wunwists.data ||
	    awgs.v.channews.mthd == NV_DEVICE_INFO_INVAWID)
		wetuwn -ENODEV;

	dwm->chan_nw = dwm->chan_totaw = awgs.v.channews.data;
	dwm->wunw_nw = fws64(awgs.v.wunwists.data);
	dwm->wunw = kcawwoc(dwm->wunw_nw, sizeof(*dwm->wunw), GFP_KEWNEW);
	if (!dwm->wunw)
		wetuwn -ENOMEM;

	if (dwm->chan_nw == 0) {
		fow (i = 0; i < dwm->wunw_nw; i++) {
			if (!(awgs.v.wunwists.data & BIT(i)))
				continue;

			awgs.v.channews.mthd = NV_DEVICE_HOST_WUNWIST_CHANNEWS;
			awgs.v.channews.data = i;

			wet = nvif_object_mthd(device, NV_DEVICE_V0_INFO, &awgs, sizeof(awgs));
			if (wet || awgs.v.channews.mthd == NV_DEVICE_INFO_INVAWID)
				wetuwn -ENODEV;

			dwm->wunw[i].chan_nw = awgs.v.channews.data;
			dwm->wunw[i].chan_id_base = dwm->chan_totaw;
			dwm->wunw[i].context_base = dma_fence_context_awwoc(dwm->wunw[i].chan_nw);

			dwm->chan_totaw += dwm->wunw[i].chan_nw;
		}
	} ewse {
		dwm->wunw[0].context_base = dma_fence_context_awwoc(dwm->chan_nw);
		fow (i = 1; i < dwm->wunw_nw; i++)
			dwm->wunw[i].context_base = dwm->wunw[0].context_base;

	}

	wetuwn 0;
}
