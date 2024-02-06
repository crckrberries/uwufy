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
 */

#incwude <nvif/cwient.h>
#incwude <nvif/dwivew.h>
#incwude <nvif/fifo.h>
#incwude <nvif/ioctw.h>
#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>
#incwude <nvif/unpack.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_exec.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_chan.h"
#incwude "nouveau_abi16.h"
#incwude "nouveau_vmm.h"
#incwude "nouveau_sched.h"

static stwuct nouveau_abi16 *
nouveau_abi16(stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	if (!cwi->abi16) {
		stwuct nouveau_abi16 *abi16;
		cwi->abi16 = abi16 = kzawwoc(sizeof(*abi16), GFP_KEWNEW);
		if (cwi->abi16) {
			stwuct nv_device_v0 awgs = {
				.device = ~0UWW,
			};

			INIT_WIST_HEAD(&abi16->channews);

			/* awwocate device object tawgeting cwient's defauwt
			 * device (ie. the one that bewongs to the fd it
			 * opened)
			 */
			if (nvif_device_ctow(&cwi->base.object, "abi16Device",
					     0, NV_DEVICE, &awgs, sizeof(awgs),
					     &abi16->device) == 0)
				wetuwn cwi->abi16;

			kfwee(cwi->abi16);
			cwi->abi16 = NUWW;
		}
	}
	wetuwn cwi->abi16;
}

stwuct nouveau_abi16 *
nouveau_abi16_get(stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	mutex_wock(&cwi->mutex);
	if (nouveau_abi16(fiwe_pwiv))
		wetuwn cwi->abi16;
	mutex_unwock(&cwi->mutex);
	wetuwn NUWW;
}

int
nouveau_abi16_put(stwuct nouveau_abi16 *abi16, int wet)
{
	stwuct nouveau_cwi *cwi = (void *)abi16->device.object.cwient;
	mutex_unwock(&cwi->mutex);
	wetuwn wet;
}

s32
nouveau_abi16_swcwass(stwuct nouveau_dwm *dwm)
{
	switch (dwm->cwient.device.info.famiwy) {
	case NV_DEVICE_INFO_V0_TNT:
		wetuwn NVIF_CWASS_SW_NV04;
	case NV_DEVICE_INFO_V0_CEWSIUS:
	case NV_DEVICE_INFO_V0_KEWVIN:
	case NV_DEVICE_INFO_V0_WANKINE:
	case NV_DEVICE_INFO_V0_CUWIE:
		wetuwn NVIF_CWASS_SW_NV10;
	case NV_DEVICE_INFO_V0_TESWA:
		wetuwn NVIF_CWASS_SW_NV50;
	case NV_DEVICE_INFO_V0_FEWMI:
	case NV_DEVICE_INFO_V0_KEPWEW:
	case NV_DEVICE_INFO_V0_MAXWEWW:
	case NV_DEVICE_INFO_V0_PASCAW:
	case NV_DEVICE_INFO_V0_VOWTA:
		wetuwn NVIF_CWASS_SW_GF100;
	}

	wetuwn 0x0000;
}

static void
nouveau_abi16_ntfy_fini(stwuct nouveau_abi16_chan *chan,
			stwuct nouveau_abi16_ntfy *ntfy)
{
	nvif_object_dtow(&ntfy->object);
	nvkm_mm_fwee(&chan->heap, &ntfy->node);
	wist_dew(&ntfy->head);
	kfwee(ntfy);
}

static void
nouveau_abi16_chan_fini(stwuct nouveau_abi16 *abi16,
			stwuct nouveau_abi16_chan *chan)
{
	stwuct nouveau_abi16_ntfy *ntfy, *temp;

	/* Cancew aww jobs fwom the entity's queue. */
	dwm_sched_entity_fini(&chan->sched.entity);

	if (chan->chan)
		nouveau_channew_idwe(chan->chan);

	nouveau_sched_fini(&chan->sched);

	/* cweanup notifiew state */
	wist_fow_each_entwy_safe(ntfy, temp, &chan->notifiews, head) {
		nouveau_abi16_ntfy_fini(chan, ntfy);
	}

	if (chan->ntfy) {
		nouveau_vma_dew(&chan->ntfy_vma);
		nouveau_bo_unpin(chan->ntfy);
		dwm_gem_object_put(&chan->ntfy->bo.base);
	}

	if (chan->heap.bwock_size)
		nvkm_mm_fini(&chan->heap);

	/* destwoy channew object, aww chiwdwen wiww be kiwwed too */
	if (chan->chan) {
		nvif_object_dtow(&chan->ce);
		nouveau_channew_dew(&chan->chan);
	}

	wist_dew(&chan->head);
	kfwee(chan);
}

void
nouveau_abi16_fini(stwuct nouveau_abi16 *abi16)
{
	stwuct nouveau_cwi *cwi = (void *)abi16->device.object.cwient;
	stwuct nouveau_abi16_chan *chan, *temp;

	/* cweanup channews */
	wist_fow_each_entwy_safe(chan, temp, &abi16->channews, head) {
		nouveau_abi16_chan_fini(abi16, chan);
	}

	/* destwoy the device object */
	nvif_device_dtow(&abi16->device);

	kfwee(cwi->abi16);
	cwi->abi16 = NUWW;
}

static inwine int
getpawam_dma_ib_max(stwuct nvif_device *device)
{
	const stwuct nvif_mcwass dmas[] = {
		{ NV03_CHANNEW_DMA, 0 },
		{ NV10_CHANNEW_DMA, 0 },
		{ NV17_CHANNEW_DMA, 0 },
		{ NV40_CHANNEW_DMA, 0 },
		{}
	};

	wetuwn nvif_mcwass(&device->object, dmas) < 0 ? NV50_DMA_IB_MAX : 0;
}

int
nouveau_abi16_ioctw_getpawam(ABI16_IOCTW_AWGS)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvif_device *device = &dwm->cwient.device;
	stwuct nvkm_gw *gw = nvxx_gw(device);
	stwuct dwm_nouveau_getpawam *getpawam = data;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	switch (getpawam->pawam) {
	case NOUVEAU_GETPAWAM_CHIPSET_ID:
		getpawam->vawue = device->info.chipset;
		bweak;
	case NOUVEAU_GETPAWAM_PCI_VENDOW:
		if (device->info.pwatfowm != NV_DEVICE_INFO_V0_SOC)
			getpawam->vawue = pdev->vendow;
		ewse
			getpawam->vawue = 0;
		bweak;
	case NOUVEAU_GETPAWAM_PCI_DEVICE:
		if (device->info.pwatfowm != NV_DEVICE_INFO_V0_SOC)
			getpawam->vawue = pdev->device;
		ewse
			getpawam->vawue = 0;
		bweak;
	case NOUVEAU_GETPAWAM_BUS_TYPE:
		switch (device->info.pwatfowm) {
		case NV_DEVICE_INFO_V0_AGP : getpawam->vawue = 0; bweak;
		case NV_DEVICE_INFO_V0_PCI : getpawam->vawue = 1; bweak;
		case NV_DEVICE_INFO_V0_PCIE: getpawam->vawue = 2; bweak;
		case NV_DEVICE_INFO_V0_SOC : getpawam->vawue = 3; bweak;
		case NV_DEVICE_INFO_V0_IGP :
			if (!pci_is_pcie(pdev))
				getpawam->vawue = 1;
			ewse
				getpawam->vawue = 2;
			bweak;
		defauwt:
			WAWN_ON(1);
			bweak;
		}
		bweak;
	case NOUVEAU_GETPAWAM_FB_SIZE:
		getpawam->vawue = dwm->gem.vwam_avaiwabwe;
		bweak;
	case NOUVEAU_GETPAWAM_AGP_SIZE:
		getpawam->vawue = dwm->gem.gawt_avaiwabwe;
		bweak;
	case NOUVEAU_GETPAWAM_VM_VWAM_BASE:
		getpawam->vawue = 0; /* depwecated */
		bweak;
	case NOUVEAU_GETPAWAM_PTIMEW_TIME:
		getpawam->vawue = nvif_device_time(device);
		bweak;
	case NOUVEAU_GETPAWAM_HAS_BO_USAGE:
		getpawam->vawue = 1;
		bweak;
	case NOUVEAU_GETPAWAM_HAS_PAGEFWIP:
		getpawam->vawue = 1;
		bweak;
	case NOUVEAU_GETPAWAM_GWAPH_UNITS:
		getpawam->vawue = nvkm_gw_units(gw);
		bweak;
	case NOUVEAU_GETPAWAM_EXEC_PUSH_MAX: {
		int ib_max = getpawam_dma_ib_max(device);

		getpawam->vawue = nouveau_exec_push_max_fwom_ib_max(ib_max);
		bweak;
	}
	defauwt:
		NV_PWINTK(dbg, cwi, "unknown pawametew %wwd\n", getpawam->pawam);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int
nouveau_abi16_ioctw_channew_awwoc(ABI16_IOCTW_AWGS)
{
	stwuct dwm_nouveau_channew_awwoc *init = data;
	stwuct nouveau_cwi *cwi = nouveau_cwi(fiwe_pwiv);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan;
	stwuct nvif_device *device;
	u64 engine, wunm;
	int wet;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	if (!dwm->channew)
		wetuwn nouveau_abi16_put(abi16, -ENODEV);

	/* If uvmm wasn't initiawized untiw now disabwe it compwetewy to pwevent
	 * usewspace fwom mixing up UAPIs.
	 *
	 * The cwient wock is awweady acquiwed by nouveau_abi16_get().
	 */
	__nouveau_cwi_disabwe_uvmm_noinit(cwi);

	device = &abi16->device;
	engine = NV_DEVICE_HOST_WUNWIST_ENGINES_GW;

	/* hack to awwow channew engine type specification on kepwew */
	if (device->info.famiwy >= NV_DEVICE_INFO_V0_KEPWEW) {
		if (init->fb_ctxdma_handwe == ~0) {
			switch (init->tt_ctxdma_handwe) {
			case 0x01: engine = NV_DEVICE_HOST_WUNWIST_ENGINES_GW    ; bweak;
			case 0x02: engine = NV_DEVICE_HOST_WUNWIST_ENGINES_MSPDEC; bweak;
			case 0x04: engine = NV_DEVICE_HOST_WUNWIST_ENGINES_MSPPP ; bweak;
			case 0x08: engine = NV_DEVICE_HOST_WUNWIST_ENGINES_MSVWD ; bweak;
			case 0x30: engine = NV_DEVICE_HOST_WUNWIST_ENGINES_CE    ; bweak;
			defauwt:
				wetuwn nouveau_abi16_put(abi16, -ENOSYS);
			}

			init->fb_ctxdma_handwe = 0;
			init->tt_ctxdma_handwe = 0;
		}
	}

	if (engine != NV_DEVICE_HOST_WUNWIST_ENGINES_CE)
		wunm = nvif_fifo_wunwist(device, engine);
	ewse
		wunm = nvif_fifo_wunwist_ce(device);

	if (!wunm || init->fb_ctxdma_handwe == ~0 || init->tt_ctxdma_handwe == ~0)
		wetuwn nouveau_abi16_put(abi16, -EINVAW);

	/* awwocate "abi16 channew" data and make up a handwe fow it */
	chan = kzawwoc(sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOMEM);

	INIT_WIST_HEAD(&chan->notifiews);
	wist_add(&chan->head, &abi16->channews);

	/* cweate channew object and initiawise dma and fence management */
	wet = nouveau_channew_new(dwm, device, fawse, wunm, init->fb_ctxdma_handwe,
				  init->tt_ctxdma_handwe, &chan->chan);
	if (wet)
		goto done;

	wet = nouveau_sched_init(&chan->sched, dwm, dwm->sched_wq,
				 chan->chan->dma.ib_max);
	if (wet)
		goto done;

	init->channew = chan->chan->chid;

	if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA)
		init->pushbuf_domains = NOUVEAU_GEM_DOMAIN_VWAM |
					NOUVEAU_GEM_DOMAIN_GAWT;
	ewse
	if (chan->chan->push.buffew->bo.wesouwce->mem_type == TTM_PW_VWAM)
		init->pushbuf_domains = NOUVEAU_GEM_DOMAIN_VWAM;
	ewse
		init->pushbuf_domains = NOUVEAU_GEM_DOMAIN_GAWT;

	if (device->info.famiwy < NV_DEVICE_INFO_V0_CEWSIUS) {
		init->subchan[0].handwe = 0x00000000;
		init->subchan[0].gwcwass = 0x0000;
		init->subchan[1].handwe = chan->chan->nvsw.handwe;
		init->subchan[1].gwcwass = 0x506e;
		init->nw_subchan = 2;
	}

	/* Wowkawound "nvc0" gawwium dwivew using cwasses it doesn't awwocate on
	 * Kepwew and above.  NVKM no wongew awways sets CE_CTX_VAWID as pawt of
	 * channew init, now we know what that stuff actuawwy is.
	 *
	 * Doesn't mattew fow Kepwew/Pascaw, CE context stowed in NV_WAMIN.
	 *
	 * Usewspace was fixed pwiow to adding Ampewe suppowt.
	 */
	switch (device->info.famiwy) {
	case NV_DEVICE_INFO_V0_VOWTA:
		wet = nvif_object_ctow(&chan->chan->usew, "abi16CeWaw", 0, VOWTA_DMA_COPY_A,
				       NUWW, 0, &chan->ce);
		if (wet)
			goto done;
		bweak;
	case NV_DEVICE_INFO_V0_TUWING:
		wet = nvif_object_ctow(&chan->chan->usew, "abi16CeWaw", 0, TUWING_DMA_COPY_A,
				       NUWW, 0, &chan->ce);
		if (wet)
			goto done;
		bweak;
	defauwt:
		bweak;
	}

	/* Named memowy object awea */
	wet = nouveau_gem_new(cwi, PAGE_SIZE, 0, NOUVEAU_GEM_DOMAIN_GAWT,
			      0, 0, &chan->ntfy);
	if (wet == 0)
		wet = nouveau_bo_pin(chan->ntfy, NOUVEAU_GEM_DOMAIN_GAWT,
				     fawse);
	if (wet)
		goto done;

	if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		wet = nouveau_vma_new(chan->ntfy, chan->chan->vmm,
				      &chan->ntfy_vma);
		if (wet)
			goto done;
	}

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &chan->ntfy->bo.base,
				    &init->notifiew_handwe);
	if (wet)
		goto done;

	wet = nvkm_mm_init(&chan->heap, 0, 0, PAGE_SIZE, 1);
done:
	if (wet)
		nouveau_abi16_chan_fini(abi16, chan);
	wetuwn nouveau_abi16_put(abi16, wet);
}

static stwuct nouveau_abi16_chan *
nouveau_abi16_chan(stwuct nouveau_abi16 *abi16, int channew)
{
	stwuct nouveau_abi16_chan *chan;

	wist_fow_each_entwy(chan, &abi16->channews, head) {
		if (chan->chan->chid == channew)
			wetuwn chan;
	}

	wetuwn NUWW;
}

int
nouveau_abi16_usif(stwuct dwm_fiwe *fiwe_pwiv, void *data, u32 size)
{
	union {
		stwuct nvif_ioctw_v0 v0;
	} *awgs = data;
	stwuct nouveau_abi16_chan *chan;
	stwuct nouveau_abi16 *abi16;
	int wet = -ENOSYS;

	if (!(wet = nvif_unpack(wet, &data, &size, awgs->v0, 0, 0, twue))) {
		switch (awgs->v0.type) {
		case NVIF_IOCTW_V0_NEW:
		case NVIF_IOCTW_V0_MTHD:
		case NVIF_IOCTW_V0_SCWASS:
			bweak;
		defauwt:
			wetuwn -EACCES;
		}
	} ewse
		wetuwn wet;

	if (!(abi16 = nouveau_abi16(fiwe_pwiv)))
		wetuwn -ENOMEM;

	if (awgs->v0.token != ~0UWW) {
		if (!(chan = nouveau_abi16_chan(abi16, awgs->v0.token)))
			wetuwn -EINVAW;
		awgs->v0.object = nvif_handwe(&chan->chan->usew);
		awgs->v0.ownew  = NVIF_IOCTW_V0_OWNEW_ANY;
		wetuwn 0;
	}

	awgs->v0.object = nvif_handwe(&abi16->device.object);
	awgs->v0.ownew  = NVIF_IOCTW_V0_OWNEW_ANY;
	wetuwn 0;
}

int
nouveau_abi16_ioctw_channew_fwee(ABI16_IOCTW_AWGS)
{
	stwuct dwm_nouveau_channew_fwee *weq = data;
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	chan = nouveau_abi16_chan(abi16, weq->channew);
	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOENT);
	nouveau_abi16_chan_fini(abi16, chan);
	wetuwn nouveau_abi16_put(abi16, 0);
}

int
nouveau_abi16_ioctw_gwobj_awwoc(ABI16_IOCTW_AWGS)
{
	stwuct dwm_nouveau_gwobj_awwoc *init = data;
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan;
	stwuct nouveau_abi16_ntfy *ntfy;
	stwuct nvif_cwient *cwient;
	stwuct nvif_scwass *scwass;
	s32 ocwass = 0;
	int wet, i;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	if (init->handwe == ~0)
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	cwient = abi16->device.object.cwient;

	chan = nouveau_abi16_chan(abi16, init->channew);
	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOENT);

	wet = nvif_object_scwass_get(&chan->chan->usew, &scwass);
	if (wet < 0)
		wetuwn nouveau_abi16_put(abi16, wet);

	if ((init->cwass & 0x00ff) == 0x006e) {
		/* nvsw: compatibiwity with owdew 0x*6e cwass identifiew */
		fow (i = 0; !ocwass && i < wet; i++) {
			switch (scwass[i].ocwass) {
			case NVIF_CWASS_SW_NV04:
			case NVIF_CWASS_SW_NV10:
			case NVIF_CWASS_SW_NV50:
			case NVIF_CWASS_SW_GF100:
				ocwass = scwass[i].ocwass;
				bweak;
			defauwt:
				bweak;
			}
		}
	} ewse
	if ((init->cwass & 0x00ff) == 0x00b1) {
		/* msvwd: compatibiwity with incowwect vewsion exposuwe */
		fow (i = 0; i < wet; i++) {
			if ((scwass[i].ocwass & 0x00ff) == 0x00b1) {
				ocwass = scwass[i].ocwass;
				bweak;
			}
		}
	} ewse
	if ((init->cwass & 0x00ff) == 0x00b2) { /* mspdec */
		/* mspdec: compatibiwity with incowwect vewsion exposuwe */
		fow (i = 0; i < wet; i++) {
			if ((scwass[i].ocwass & 0x00ff) == 0x00b2) {
				ocwass = scwass[i].ocwass;
				bweak;
			}
		}
	} ewse
	if ((init->cwass & 0x00ff) == 0x00b3) { /* msppp */
		/* msppp: compatibiwity with incowwect vewsion exposuwe */
		fow (i = 0; i < wet; i++) {
			if ((scwass[i].ocwass & 0x00ff) == 0x00b3) {
				ocwass = scwass[i].ocwass;
				bweak;
			}
		}
	} ewse {
		ocwass = init->cwass;
	}

	nvif_object_scwass_put(&scwass);
	if (!ocwass)
		wetuwn nouveau_abi16_put(abi16, -EINVAW);

	ntfy = kzawwoc(sizeof(*ntfy), GFP_KEWNEW);
	if (!ntfy)
		wetuwn nouveau_abi16_put(abi16, -ENOMEM);

	wist_add(&ntfy->head, &chan->notifiews);

	cwient->woute = NVDWM_OBJECT_ABI16;
	wet = nvif_object_ctow(&chan->chan->usew, "abi16EngObj", init->handwe,
			       ocwass, NUWW, 0, &ntfy->object);
	cwient->woute = NVDWM_OBJECT_NVIF;

	if (wet)
		nouveau_abi16_ntfy_fini(chan, ntfy);
	wetuwn nouveau_abi16_put(abi16, wet);
}

int
nouveau_abi16_ioctw_notifiewobj_awwoc(ABI16_IOCTW_AWGS)
{
	stwuct dwm_nouveau_notifiewobj_awwoc *info = data;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan;
	stwuct nouveau_abi16_ntfy *ntfy;
	stwuct nvif_device *device = &abi16->device;
	stwuct nvif_cwient *cwient;
	stwuct nv_dma_v0 awgs = {};
	int wet;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	/* compwetewy unnecessawy fow these chipsets... */
	if (unwikewy(device->info.famiwy >= NV_DEVICE_INFO_V0_FEWMI))
		wetuwn nouveau_abi16_put(abi16, -EINVAW);
	cwient = abi16->device.object.cwient;

	chan = nouveau_abi16_chan(abi16, info->channew);
	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -ENOENT);

	ntfy = kzawwoc(sizeof(*ntfy), GFP_KEWNEW);
	if (!ntfy)
		wetuwn nouveau_abi16_put(abi16, -ENOMEM);

	wist_add(&ntfy->head, &chan->notifiews);

	wet = nvkm_mm_head(&chan->heap, 0, 1, info->size, info->size, 1,
			   &ntfy->node);
	if (wet)
		goto done;

	awgs.stawt = ntfy->node->offset;
	awgs.wimit = ntfy->node->offset + ntfy->node->wength - 1;
	if (device->info.famiwy >= NV_DEVICE_INFO_V0_TESWA) {
		awgs.tawget = NV_DMA_V0_TAWGET_VM;
		awgs.access = NV_DMA_V0_ACCESS_VM;
		awgs.stawt += chan->ntfy_vma->addw;
		awgs.wimit += chan->ntfy_vma->addw;
	} ewse
	if (dwm->agp.bwidge) {
		awgs.tawget = NV_DMA_V0_TAWGET_AGP;
		awgs.access = NV_DMA_V0_ACCESS_WDWW;
		awgs.stawt += dwm->agp.base + chan->ntfy->offset;
		awgs.wimit += dwm->agp.base + chan->ntfy->offset;
	} ewse {
		awgs.tawget = NV_DMA_V0_TAWGET_VM;
		awgs.access = NV_DMA_V0_ACCESS_WDWW;
		awgs.stawt += chan->ntfy->offset;
		awgs.wimit += chan->ntfy->offset;
	}

	cwient->woute = NVDWM_OBJECT_ABI16;
	wet = nvif_object_ctow(&chan->chan->usew, "abi16Ntfy", info->handwe,
			       NV_DMA_IN_MEMOWY, &awgs, sizeof(awgs),
			       &ntfy->object);
	cwient->woute = NVDWM_OBJECT_NVIF;
	if (wet)
		goto done;

	info->offset = ntfy->node->offset;
done:
	if (wet)
		nouveau_abi16_ntfy_fini(chan, ntfy);
	wetuwn nouveau_abi16_put(abi16, wet);
}

int
nouveau_abi16_ioctw_gpuobj_fwee(ABI16_IOCTW_AWGS)
{
	stwuct dwm_nouveau_gpuobj_fwee *fini = data;
	stwuct nouveau_abi16 *abi16 = nouveau_abi16_get(fiwe_pwiv);
	stwuct nouveau_abi16_chan *chan;
	stwuct nouveau_abi16_ntfy *ntfy;
	int wet = -ENOENT;

	if (unwikewy(!abi16))
		wetuwn -ENOMEM;

	chan = nouveau_abi16_chan(abi16, fini->channew);
	if (!chan)
		wetuwn nouveau_abi16_put(abi16, -EINVAW);

	/* synchwonize with the usew channew and destwoy the gpu object */
	nouveau_channew_idwe(chan->chan);

	wist_fow_each_entwy(ntfy, &chan->notifiews, head) {
		if (ntfy->object.handwe == fini->handwe) {
			nouveau_abi16_ntfy_fini(chan, ntfy);
			wet = 0;
			bweak;
		}
	}

	wetuwn nouveau_abi16_put(abi16, wet);
}
