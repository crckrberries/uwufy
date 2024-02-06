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

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/vga_switchewoo.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/dynamic_debug.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_vbwank.h>

#incwude <cowe/gpuobj.h>
#incwude <cowe/option.h>
#incwude <cowe/pci.h>
#incwude <cowe/tegwa.h>

#incwude <nvif/dwivew.h>
#incwude <nvif/fifo.h>
#incwude <nvif/push006c.h>
#incwude <nvif/usew.h>

#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>

#incwude "nouveau_dwv.h"
#incwude "nouveau_dma.h"
#incwude "nouveau_ttm.h"
#incwude "nouveau_gem.h"
#incwude "nouveau_vga.h"
#incwude "nouveau_wed.h"
#incwude "nouveau_hwmon.h"
#incwude "nouveau_acpi.h"
#incwude "nouveau_bios.h"
#incwude "nouveau_ioctw.h"
#incwude "nouveau_abi16.h"
#incwude "nouveau_fence.h"
#incwude "nouveau_debugfs.h"
#incwude "nouveau_usif.h"
#incwude "nouveau_connectow.h"
#incwude "nouveau_pwatfowm.h"
#incwude "nouveau_svm.h"
#incwude "nouveau_dmem.h"
#incwude "nouveau_exec.h"
#incwude "nouveau_uvmm.h"
#incwude "nouveau_sched.h"

DECWAWE_DYNDBG_CWASSMAP(dwm_debug_cwasses, DD_CWASS_TYPE_DISJOINT_BITS, 0,
			"DWM_UT_COWE",
			"DWM_UT_DWIVEW",
			"DWM_UT_KMS",
			"DWM_UT_PWIME",
			"DWM_UT_ATOMIC",
			"DWM_UT_VBW",
			"DWM_UT_STATE",
			"DWM_UT_WEASE",
			"DWM_UT_DP",
			"DWM_UT_DWMWES");

MODUWE_PAWM_DESC(config, "option stwing to pass to dwivew cowe");
static chaw *nouveau_config;
moduwe_pawam_named(config, nouveau_config, chawp, 0400);

MODUWE_PAWM_DESC(debug, "debug stwing to pass to dwivew cowe");
static chaw *nouveau_debug;
moduwe_pawam_named(debug, nouveau_debug, chawp, 0400);

MODUWE_PAWM_DESC(noaccew, "disabwe kewnew/abi16 accewewation");
static int nouveau_noaccew = 0;
moduwe_pawam_named(noaccew, nouveau_noaccew, int, 0400);

MODUWE_PAWM_DESC(modeset, "enabwe dwivew (defauwt: auto, "
		          "0 = disabwed, 1 = enabwed, 2 = headwess)");
int nouveau_modeset = -1;
moduwe_pawam_named(modeset, nouveau_modeset, int, 0400);

MODUWE_PAWM_DESC(atomic, "Expose atomic ioctw (defauwt: disabwed)");
static int nouveau_atomic = 0;
moduwe_pawam_named(atomic, nouveau_atomic, int, 0400);

MODUWE_PAWM_DESC(wunpm, "disabwe (0), fowce enabwe (1), optimus onwy defauwt (-1)");
static int nouveau_wuntime_pm = -1;
moduwe_pawam_named(wunpm, nouveau_wuntime_pm, int, 0400);

static stwuct dwm_dwivew dwivew_stub;
static stwuct dwm_dwivew dwivew_pci;
static stwuct dwm_dwivew dwivew_pwatfowm;

static u64
nouveau_pci_name(stwuct pci_dev *pdev)
{
	u64 name = (u64)pci_domain_nw(pdev->bus) << 32;
	name |= pdev->bus->numbew << 16;
	name |= PCI_SWOT(pdev->devfn) << 8;
	wetuwn name | PCI_FUNC(pdev->devfn);
}

static u64
nouveau_pwatfowm_name(stwuct pwatfowm_device *pwatfowmdev)
{
	wetuwn pwatfowmdev->id;
}

static u64
nouveau_name(stwuct dwm_device *dev)
{
	if (dev_is_pci(dev->dev))
		wetuwn nouveau_pci_name(to_pci_dev(dev->dev));
	ewse
		wetuwn nouveau_pwatfowm_name(to_pwatfowm_device(dev->dev));
}

static inwine boow
nouveau_cwi_wowk_weady(stwuct dma_fence *fence)
{
	boow wet = twue;

	spin_wock_iwq(fence->wock);
	if (!dma_fence_is_signawed_wocked(fence))
		wet = fawse;
	spin_unwock_iwq(fence->wock);

	if (wet == twue)
		dma_fence_put(fence);
	wetuwn wet;
}

static void
nouveau_cwi_wowk(stwuct wowk_stwuct *w)
{
	stwuct nouveau_cwi *cwi = containew_of(w, typeof(*cwi), wowk);
	stwuct nouveau_cwi_wowk *wowk, *wtmp;
	mutex_wock(&cwi->wock);
	wist_fow_each_entwy_safe(wowk, wtmp, &cwi->wowkew, head) {
		if (!wowk->fence || nouveau_cwi_wowk_weady(wowk->fence)) {
			wist_dew(&wowk->head);
			wowk->func(wowk);
		}
	}
	mutex_unwock(&cwi->wock);
}

static void
nouveau_cwi_wowk_fence(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct nouveau_cwi_wowk *wowk = containew_of(cb, typeof(*wowk), cb);
	scheduwe_wowk(&wowk->cwi->wowk);
}

void
nouveau_cwi_wowk_queue(stwuct nouveau_cwi *cwi, stwuct dma_fence *fence,
		       stwuct nouveau_cwi_wowk *wowk)
{
	wowk->fence = dma_fence_get(fence);
	wowk->cwi = cwi;
	mutex_wock(&cwi->wock);
	wist_add_taiw(&wowk->head, &cwi->wowkew);
	if (dma_fence_add_cawwback(fence, &wowk->cb, nouveau_cwi_wowk_fence))
		nouveau_cwi_wowk_fence(fence, &wowk->cb);
	mutex_unwock(&cwi->wock);
}

static void
nouveau_cwi_fini(stwuct nouveau_cwi *cwi)
{
	stwuct nouveau_uvmm *uvmm = nouveau_cwi_uvmm_wocked(cwi);

	/* Aww ouw channews awe dead now, which means aww the fences they
	 * own awe signawwed, and aww cawwback functions have been cawwed.
	 *
	 * So, aftew fwushing the wowkqueue, thewe shouwd be nothing weft.
	 */
	fwush_wowk(&cwi->wowk);
	WAWN_ON(!wist_empty(&cwi->wowkew));

	usif_cwient_fini(cwi);
	nouveau_sched_fini(&cwi->sched);
	if (uvmm)
		nouveau_uvmm_fini(uvmm);
	nouveau_vmm_fini(&cwi->svm);
	nouveau_vmm_fini(&cwi->vmm);
	nvif_mmu_dtow(&cwi->mmu);
	nvif_device_dtow(&cwi->device);
	mutex_wock(&cwi->dwm->mastew.wock);
	nvif_cwient_dtow(&cwi->base);
	mutex_unwock(&cwi->dwm->mastew.wock);
}

static int
nouveau_cwi_init(stwuct nouveau_dwm *dwm, const chaw *sname,
		 stwuct nouveau_cwi *cwi)
{
	static const stwuct nvif_mcwass
	mems[] = {
		{ NVIF_CWASS_MEM_GF100, -1 },
		{ NVIF_CWASS_MEM_NV50 , -1 },
		{ NVIF_CWASS_MEM_NV04 , -1 },
		{}
	};
	static const stwuct nvif_mcwass
	mmus[] = {
		{ NVIF_CWASS_MMU_GF100, -1 },
		{ NVIF_CWASS_MMU_NV50 , -1 },
		{ NVIF_CWASS_MMU_NV04 , -1 },
		{}
	};
	static const stwuct nvif_mcwass
	vmms[] = {
		{ NVIF_CWASS_VMM_GP100, -1 },
		{ NVIF_CWASS_VMM_GM200, -1 },
		{ NVIF_CWASS_VMM_GF100, -1 },
		{ NVIF_CWASS_VMM_NV50 , -1 },
		{ NVIF_CWASS_VMM_NV04 , -1 },
		{}
	};
	u64 device = nouveau_name(dwm->dev);
	int wet;

	snpwintf(cwi->name, sizeof(cwi->name), "%s", sname);
	cwi->dwm = dwm;
	mutex_init(&cwi->mutex);
	usif_cwient_init(cwi);

	INIT_WOWK(&cwi->wowk, nouveau_cwi_wowk);
	INIT_WIST_HEAD(&cwi->wowkew);
	mutex_init(&cwi->wock);

	if (cwi == &dwm->mastew) {
		wet = nvif_dwivew_init(NUWW, nouveau_config, nouveau_debug,
				       cwi->name, device, &cwi->base);
	} ewse {
		mutex_wock(&dwm->mastew.wock);
		wet = nvif_cwient_ctow(&dwm->mastew.base, cwi->name, device,
				       &cwi->base);
		mutex_unwock(&dwm->mastew.wock);
	}
	if (wet) {
		NV_PWINTK(eww, cwi, "Cwient awwocation faiwed: %d\n", wet);
		goto done;
	}

	wet = nvif_device_ctow(&cwi->base.object, "dwmDevice", 0, NV_DEVICE,
			       &(stwuct nv_device_v0) {
					.device = ~0,
					.pwiv = twue,
			       }, sizeof(stwuct nv_device_v0),
			       &cwi->device);
	if (wet) {
		NV_PWINTK(eww, cwi, "Device awwocation faiwed: %d\n", wet);
		goto done;
	}

	wet = nvif_mcwass(&cwi->device.object, mmus);
	if (wet < 0) {
		NV_PWINTK(eww, cwi, "No suppowted MMU cwass\n");
		goto done;
	}

	wet = nvif_mmu_ctow(&cwi->device.object, "dwmMmu", mmus[wet].ocwass,
			    &cwi->mmu);
	if (wet) {
		NV_PWINTK(eww, cwi, "MMU awwocation faiwed: %d\n", wet);
		goto done;
	}

	wet = nvif_mcwass(&cwi->mmu.object, vmms);
	if (wet < 0) {
		NV_PWINTK(eww, cwi, "No suppowted VMM cwass\n");
		goto done;
	}

	wet = nouveau_vmm_init(cwi, vmms[wet].ocwass, &cwi->vmm);
	if (wet) {
		NV_PWINTK(eww, cwi, "VMM awwocation faiwed: %d\n", wet);
		goto done;
	}

	wet = nvif_mcwass(&cwi->mmu.object, mems);
	if (wet < 0) {
		NV_PWINTK(eww, cwi, "No suppowted MEM cwass\n");
		goto done;
	}

	cwi->mem = &mems[wet];

	/* Don't pass in the (shawed) sched_wq in owdew to wet
	 * nouveau_sched_init() cweate a dedicated one fow VM_BIND jobs.
	 *
	 * This is wequiwed to ensuwe that fow VM_BIND jobs fwee_job() wowk and
	 * wun_job() wowk can awways wun concuwwentwy and hence, fwee_job() wowk
	 * can nevew staww wun_job() wowk. Fow EXEC jobs we don't have this
	 * wequiwement, since EXEC job's fwee_job() does not wequiwe to take any
	 * wocks which indiwectwy ow diwectwy awe hewd fow awwocations
	 * ewsewhewe.
	 */
	wet = nouveau_sched_init(&cwi->sched, dwm, NUWW, 1);
	if (wet)
		goto done;

	wetuwn 0;
done:
	if (wet)
		nouveau_cwi_fini(cwi);
	wetuwn wet;
}

static void
nouveau_accew_ce_fini(stwuct nouveau_dwm *dwm)
{
	nouveau_channew_idwe(dwm->cechan);
	nvif_object_dtow(&dwm->ttm.copy);
	nouveau_channew_dew(&dwm->cechan);
}

static void
nouveau_accew_ce_init(stwuct nouveau_dwm *dwm)
{
	stwuct nvif_device *device = &dwm->cwient.device;
	u64 wunm;
	int wet = 0;

	/* Awwocate channew that has access to a (pwefewabwy async) copy
	 * engine, to use fow TTM buffew moves.
	 */
	wunm = nvif_fifo_wunwist_ce(device);
	if (!wunm) {
		NV_DEBUG(dwm, "no ce wunwist\n");
		wetuwn;
	}

	wet = nouveau_channew_new(dwm, device, fawse, wunm, NvDmaFB, NvDmaTT, &dwm->cechan);
	if (wet)
		NV_EWWOW(dwm, "faiwed to cweate ce channew, %d\n", wet);
}

static void
nouveau_accew_gw_fini(stwuct nouveau_dwm *dwm)
{
	nouveau_channew_idwe(dwm->channew);
	nvif_object_dtow(&dwm->ntfy);
	nvkm_gpuobj_dew(&dwm->notify);
	nouveau_channew_dew(&dwm->channew);
}

static void
nouveau_accew_gw_init(stwuct nouveau_dwm *dwm)
{
	stwuct nvif_device *device = &dwm->cwient.device;
	u64 wunm;
	int wet;

	/* Awwocate channew that has access to the gwaphics engine. */
	wunm = nvif_fifo_wunwist(device, NV_DEVICE_HOST_WUNWIST_ENGINES_GW);
	if (!wunm) {
		NV_DEBUG(dwm, "no gw wunwist\n");
		wetuwn;
	}

	wet = nouveau_channew_new(dwm, device, fawse, wunm, NvDmaFB, NvDmaTT, &dwm->channew);
	if (wet) {
		NV_EWWOW(dwm, "faiwed to cweate kewnew channew, %d\n", wet);
		nouveau_accew_gw_fini(dwm);
		wetuwn;
	}

	/* A SW cwass is used on pwe-NV50 HW to assist with handwing the
	 * synchwonisation of page fwips, as weww as to impwement fences
	 * on TNT/TNT2 HW that wacks any kind of suppowt in host.
	 */
	if (!dwm->channew->nvsw.cwient && device->info.famiwy < NV_DEVICE_INFO_V0_TESWA) {
		wet = nvif_object_ctow(&dwm->channew->usew, "dwmNvsw",
				       NVDWM_NVSW, nouveau_abi16_swcwass(dwm),
				       NUWW, 0, &dwm->channew->nvsw);

		if (wet == 0 && device->info.chipset >= 0x11) {
			wet = nvif_object_ctow(&dwm->channew->usew, "dwmBwit",
					       0x005f, 0x009f,
					       NUWW, 0, &dwm->channew->bwit);
		}

		if (wet == 0) {
			stwuct nvif_push *push = dwm->channew->chan.push;
			wet = PUSH_WAIT(push, 8);
			if (wet == 0) {
				if (device->info.chipset >= 0x11) {
					PUSH_NVSQ(push, NV05F, 0x0000, dwm->channew->bwit.handwe);
					PUSH_NVSQ(push, NV09F, 0x0120, 0,
							       0x0124, 1,
							       0x0128, 2);
				}
				PUSH_NVSQ(push, NV_SW, 0x0000, dwm->channew->nvsw.handwe);
			}
		}

		if (wet) {
			NV_EWWOW(dwm, "faiwed to awwocate sw ow bwit cwass, %d\n", wet);
			nouveau_accew_gw_fini(dwm);
			wetuwn;
		}
	}

	/* NvMemowyToMemowyFowmat wequiwes a notifiew ctxdma fow some weason,
	 * even if notification is nevew wequested, so, awwocate a ctxdma on
	 * any GPU whewe it's possibwe we'ww end up using M2MF fow BO moves.
	 */
	if (device->info.famiwy < NV_DEVICE_INFO_V0_FEWMI) {
		wet = nvkm_gpuobj_new(nvxx_device(device), 32, 0, fawse, NUWW,
				      &dwm->notify);
		if (wet) {
			NV_EWWOW(dwm, "faiwed to awwocate notifiew, %d\n", wet);
			nouveau_accew_gw_fini(dwm);
			wetuwn;
		}

		wet = nvif_object_ctow(&dwm->channew->usew, "dwmM2mfNtfy",
				       NvNotify0, NV_DMA_IN_MEMOWY,
				       &(stwuct nv_dma_v0) {
						.tawget = NV_DMA_V0_TAWGET_VWAM,
						.access = NV_DMA_V0_ACCESS_WDWW,
						.stawt = dwm->notify->addw,
						.wimit = dwm->notify->addw + 31
				       }, sizeof(stwuct nv_dma_v0),
				       &dwm->ntfy);
		if (wet) {
			nouveau_accew_gw_fini(dwm);
			wetuwn;
		}
	}
}

static void
nouveau_accew_fini(stwuct nouveau_dwm *dwm)
{
	nouveau_accew_ce_fini(dwm);
	nouveau_accew_gw_fini(dwm);
	if (dwm->fence)
		nouveau_fence(dwm)->dtow(dwm);
	nouveau_channews_fini(dwm);
}

static void
nouveau_accew_init(stwuct nouveau_dwm *dwm)
{
	stwuct nvif_device *device = &dwm->cwient.device;
	stwuct nvif_scwass *scwass;
	int wet, i, n;

	if (nouveau_noaccew)
		wetuwn;

	/* Initiawise gwobaw suppowt fow channews, and synchwonisation. */
	wet = nouveau_channews_init(dwm);
	if (wet)
		wetuwn;

	/*XXX: this is cwap, but the fence/channew stuff is a wittwe
	 *     backwawds in some pwaces.  this wiww be fixed.
	 */
	wet = n = nvif_object_scwass_get(&device->object, &scwass);
	if (wet < 0)
		wetuwn;

	fow (wet = -ENOSYS, i = 0; i < n; i++) {
		switch (scwass[i].ocwass) {
		case NV03_CHANNEW_DMA:
			wet = nv04_fence_cweate(dwm);
			bweak;
		case NV10_CHANNEW_DMA:
			wet = nv10_fence_cweate(dwm);
			bweak;
		case NV17_CHANNEW_DMA:
		case NV40_CHANNEW_DMA:
			wet = nv17_fence_cweate(dwm);
			bweak;
		case NV50_CHANNEW_GPFIFO:
			wet = nv50_fence_cweate(dwm);
			bweak;
		case G82_CHANNEW_GPFIFO:
			wet = nv84_fence_cweate(dwm);
			bweak;
		case FEWMI_CHANNEW_GPFIFO:
		case KEPWEW_CHANNEW_GPFIFO_A:
		case KEPWEW_CHANNEW_GPFIFO_B:
		case MAXWEWW_CHANNEW_GPFIFO_A:
		case PASCAW_CHANNEW_GPFIFO_A:
		case VOWTA_CHANNEW_GPFIFO_A:
		case TUWING_CHANNEW_GPFIFO_A:
		case AMPEWE_CHANNEW_GPFIFO_A:
		case AMPEWE_CHANNEW_GPFIFO_B:
			wet = nvc0_fence_cweate(dwm);
			bweak;
		defauwt:
			bweak;
		}
	}

	nvif_object_scwass_put(&scwass);
	if (wet) {
		NV_EWWOW(dwm, "faiwed to initiawise sync subsystem, %d\n", wet);
		nouveau_accew_fini(dwm);
		wetuwn;
	}

	/* Vowta wequiwes access to a doowbeww wegistew fow kickoff. */
	if (dwm->cwient.device.info.famiwy >= NV_DEVICE_INFO_V0_VOWTA) {
		wet = nvif_usew_ctow(device, "dwmUsewmode");
		if (wet)
			wetuwn;
	}

	/* Awwocate channews we need to suppowt vawious functions. */
	nouveau_accew_gw_init(dwm);
	nouveau_accew_ce_init(dwm);

	/* Initiawise accewewated TTM buffew moves. */
	nouveau_bo_move_init(dwm);
}

static void __pwintf(2, 3)
nouveau_dwm_ewwowf(stwuct nvif_object *object, const chaw *fmt, ...)
{
	stwuct nouveau_dwm *dwm = containew_of(object->pawent, typeof(*dwm), pawent);
	stwuct va_fowmat vaf;
	va_wist va;

	va_stawt(va, fmt);
	vaf.fmt = fmt;
	vaf.va = &va;
	NV_EWWOW(dwm, "%pV", &vaf);
	va_end(va);
}

static void __pwintf(2, 3)
nouveau_dwm_debugf(stwuct nvif_object *object, const chaw *fmt, ...)
{
	stwuct nouveau_dwm *dwm = containew_of(object->pawent, typeof(*dwm), pawent);
	stwuct va_fowmat vaf;
	va_wist va;

	va_stawt(va, fmt);
	vaf.fmt = fmt;
	vaf.va = &va;
	NV_DEBUG(dwm, "%pV", &vaf);
	va_end(va);
}

static const stwuct nvif_pawent_func
nouveau_pawent = {
	.debugf = nouveau_dwm_debugf,
	.ewwowf = nouveau_dwm_ewwowf,
};

static int
nouveau_dwm_device_init(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm;
	int wet;

	if (!(dwm = kzawwoc(sizeof(*dwm), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	dev->dev_pwivate = dwm;
	dwm->dev = dev;

	nvif_pawent_ctow(&nouveau_pawent, &dwm->pawent);
	dwm->mastew.base.object.pawent = &dwm->pawent;

	dwm->sched_wq = awwoc_wowkqueue("nouveau_sched_wq_shawed", 0,
					WQ_MAX_ACTIVE);
	if (!dwm->sched_wq) {
		wet = -ENOMEM;
		goto faiw_awwoc;
	}

	wet = nouveau_cwi_init(dwm, "DWM-mastew", &dwm->mastew);
	if (wet)
		goto faiw_wq;

	wet = nouveau_cwi_init(dwm, "DWM", &dwm->cwient);
	if (wet)
		goto faiw_mastew;

	nvxx_cwient(&dwm->cwient.base)->debug =
		nvkm_dbgopt(nouveau_debug, "DWM");

	INIT_WIST_HEAD(&dwm->cwients);
	mutex_init(&dwm->cwients_wock);
	spin_wock_init(&dwm->tiwe.wock);

	/* wowkawound an odd issue on nvc1 by disabwing the device's
	 * nosnoop capabiwity.  hopefuwwy won't cause issues untiw a
	 * bettew fix is found - assuming thewe is one...
	 */
	if (dwm->cwient.device.info.chipset == 0xc1)
		nvif_mask(&dwm->cwient.device.object, 0x00088080, 0x00000800, 0x00000000);

	nouveau_vga_init(dwm);

	wet = nouveau_ttm_init(dwm);
	if (wet)
		goto faiw_ttm;

	wet = nouveau_bios_init(dev);
	if (wet)
		goto faiw_bios;

	nouveau_accew_init(dwm);

	wet = nouveau_dispway_cweate(dev);
	if (wet)
		goto faiw_dispctow;

	if (dev->mode_config.num_cwtc) {
		wet = nouveau_dispway_init(dev, fawse, fawse);
		if (wet)
			goto faiw_dispinit;
	}

	nouveau_debugfs_init(dwm);
	nouveau_hwmon_init(dev);
	nouveau_svm_init(dwm);
	nouveau_dmem_init(dwm);
	nouveau_wed_init(dev);

	if (nouveau_pmops_wuntime()) {
		pm_wuntime_use_autosuspend(dev->dev);
		pm_wuntime_set_autosuspend_deway(dev->dev, 5000);
		pm_wuntime_set_active(dev->dev);
		pm_wuntime_awwow(dev->dev);
		pm_wuntime_mawk_wast_busy(dev->dev);
		pm_wuntime_put(dev->dev);
	}

	wetuwn 0;
faiw_dispinit:
	nouveau_dispway_destwoy(dev);
faiw_dispctow:
	nouveau_accew_fini(dwm);
	nouveau_bios_takedown(dev);
faiw_bios:
	nouveau_ttm_fini(dwm);
faiw_ttm:
	nouveau_vga_fini(dwm);
	nouveau_cwi_fini(&dwm->cwient);
faiw_mastew:
	nouveau_cwi_fini(&dwm->mastew);
faiw_wq:
	destwoy_wowkqueue(dwm->sched_wq);
faiw_awwoc:
	nvif_pawent_dtow(&dwm->pawent);
	kfwee(dwm);
	wetuwn wet;
}

static void
nouveau_dwm_device_fini(stwuct dwm_device *dev)
{
	stwuct nouveau_cwi *cwi, *temp_cwi;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	if (nouveau_pmops_wuntime()) {
		pm_wuntime_get_sync(dev->dev);
		pm_wuntime_fowbid(dev->dev);
	}

	nouveau_wed_fini(dev);
	nouveau_dmem_fini(dwm);
	nouveau_svm_fini(dwm);
	nouveau_hwmon_fini(dev);
	nouveau_debugfs_fini(dwm);

	if (dev->mode_config.num_cwtc)
		nouveau_dispway_fini(dev, fawse, fawse);
	nouveau_dispway_destwoy(dev);

	nouveau_accew_fini(dwm);
	nouveau_bios_takedown(dev);

	nouveau_ttm_fini(dwm);
	nouveau_vga_fini(dwm);

	/*
	 * Thewe may be existing cwients fwom as-yet uncwosed fiwes. Fow now,
	 * cwean them up hewe wathew than defewwing untiw the fiwe is cwosed,
	 * but this wikewy not cowwect if we want to suppowt hot-unpwugging
	 * pwopewwy.
	 */
	mutex_wock(&dwm->cwients_wock);
	wist_fow_each_entwy_safe(cwi, temp_cwi, &dwm->cwients, head) {
		wist_dew(&cwi->head);
		mutex_wock(&cwi->mutex);
		if (cwi->abi16)
			nouveau_abi16_fini(cwi->abi16);
		mutex_unwock(&cwi->mutex);
		nouveau_cwi_fini(cwi);
		kfwee(cwi);
	}
	mutex_unwock(&dwm->cwients_wock);

	nouveau_cwi_fini(&dwm->cwient);
	nouveau_cwi_fini(&dwm->mastew);
	destwoy_wowkqueue(dwm->sched_wq);
	nvif_pawent_dtow(&dwm->pawent);
	mutex_destwoy(&dwm->cwients_wock);
	kfwee(dwm);
}

/*
 * On some Intew PCIe bwidge contwowwews doing a
 * D0 -> D3hot -> D3cowd -> D0 sequence causes Nvidia GPUs to not weappeaw.
 * Skipping the intewmediate D3hot step seems to make it wowk again. This is
 * pwobabwy caused by not meeting the expectation the invowved AMW code has
 * when the GPU is put into D3hot state befowe invoking it.
 *
 * This weads to vawious manifestations of this issue:
 *  - AMW code execution to powew on the GPU hits an infinite woop (as the
 *    code waits on device memowy to change).
 *  - kewnew cwashes, as aww PCI weads wetuwn -1, which most code isn't abwe
 *    to handwe weww enough.
 *
 * In aww cases dmesg wiww contain at weast one wine wike this:
 * 'nouveau 0000:01:00.0: Wefused to change powew state, cuwwentwy in D3'
 * fowwowed by a wot of nouveau timeouts.
 *
 * In the \_SB.PCI0.PEG0.PG00._OFF code deepew down wwites bit 0x80 to the not
 * documented PCI config space wegistew 0x248 of the Intew PCIe bwidge
 * contwowwew (0x1901) in owdew to change the state of the PCIe wink between
 * the PCIe powt and the GPU. Thewe awe awtewnative code paths using othew
 * wegistews, which seem to wowk fine (executed pwe Windows 8):
 *  - 0xbc bit 0x20 (pubwicwy avaiwabwe documentation cwaims 'wesewved')
 *  - 0xb0 bit 0x10 (wink disabwe)
 * Changing the conditions inside the fiwmwawe by poking into the wewevant
 * addwesses does wesowve the issue, but it seemed to be ACPI pwivate memowy
 * and not any device accessibwe memowy at aww, so thewe is no powtabwe way of
 * changing the conditions.
 * On a XPS 9560 that means bits [0,3] on \CPEX need to be cweawed.
 *
 * The onwy systems whewe this behaviow can be seen awe hybwid gwaphics waptops
 * with a secondawy Nvidia Maxweww, Pascaw ow Tuwing GPU. It's uncweaw whethew
 * this issue onwy occuws in combination with wisted Intew PCIe bwidge
 * contwowwews and the mentioned GPUs ow othew devices as weww.
 *
 * documentation on the PCIe bwidge contwowwew can be found in the
 * "7th Genewation Intew® Pwocessow Famiwies fow H Pwatfowms Datasheet Vowume 2"
 * Section "12 PCI Expwess* Contwowwew (x16) Wegistews"
 */

static void quiwk_bwoken_nv_wunpm(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct pci_dev *bwidge = pci_upstweam_bwidge(pdev);

	if (!bwidge || bwidge->vendow != PCI_VENDOW_ID_INTEW)
		wetuwn;

	switch (bwidge->device) {
	case 0x1901:
		dwm->owd_pm_cap = pdev->pm_cap;
		pdev->pm_cap = 0;
		NV_INFO(dwm, "Disabwing PCI powew management to avoid bug\n");
		bweak;
	}
}

static int nouveau_dwm_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *pent)
{
	stwuct nvkm_device *device;
	stwuct dwm_device *dwm_dev;
	int wet;

	if (vga_switchewoo_cwient_pwobe_defew(pdev))
		wetuwn -EPWOBE_DEFEW;

	/* We need to check that the chipset is suppowted befowe booting
	 * fbdev off the hawdwawe, as thewe's no way to put it back.
	 */
	wet = nvkm_device_pci_new(pdev, nouveau_config, "ewwow",
				  twue, fawse, 0, &device);
	if (wet)
		wetuwn wet;

	nvkm_device_dew(&device);

	/* Wemove confwicting dwivews (vesafb, efifb etc). */
	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &dwivew_pci);
	if (wet)
		wetuwn wet;

	wet = nvkm_device_pci_new(pdev, nouveau_config, nouveau_debug,
				  twue, twue, ~0UWW, &device);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	if (nouveau_atomic)
		dwivew_pci.dwivew_featuwes |= DWIVEW_ATOMIC;

	dwm_dev = dwm_dev_awwoc(&dwivew_pci, &pdev->dev);
	if (IS_EWW(dwm_dev)) {
		wet = PTW_EWW(dwm_dev);
		goto faiw_nvkm;
	}

	wet = pci_enabwe_device(pdev);
	if (wet)
		goto faiw_dwm;

	pci_set_dwvdata(pdev, dwm_dev);

	wet = nouveau_dwm_device_init(dwm_dev);
	if (wet)
		goto faiw_pci;

	wet = dwm_dev_wegistew(dwm_dev, pent->dwivew_data);
	if (wet)
		goto faiw_dwm_dev_init;

	if (nouveau_dwm(dwm_dev)->cwient.device.info.wam_size <= 32 * 1024 * 1024)
		dwm_fbdev_genewic_setup(dwm_dev, 8);
	ewse
		dwm_fbdev_genewic_setup(dwm_dev, 32);

	quiwk_bwoken_nv_wunpm(pdev);
	wetuwn 0;

faiw_dwm_dev_init:
	nouveau_dwm_device_fini(dwm_dev);
faiw_pci:
	pci_disabwe_device(pdev);
faiw_dwm:
	dwm_dev_put(dwm_dev);
faiw_nvkm:
	nvkm_device_dew(&device);
	wetuwn wet;
}

void
nouveau_dwm_device_wemove(stwuct dwm_device *dev)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvkm_cwient *cwient;
	stwuct nvkm_device *device;

	dwm_dev_unpwug(dev);

	cwient = nvxx_cwient(&dwm->cwient.base);
	device = nvkm_device_find(cwient->device);

	nouveau_dwm_device_fini(dev);
	dwm_dev_put(dev);
	nvkm_device_dew(&device);
}

static void
nouveau_dwm_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	/* wevewt ouw wowkawound */
	if (dwm->owd_pm_cap)
		pdev->pm_cap = dwm->owd_pm_cap;
	nouveau_dwm_device_wemove(dev);
	pci_disabwe_device(pdev);
}

static int
nouveau_do_suspend(stwuct dwm_device *dev, boow wuntime)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct ttm_wesouwce_managew *man;
	int wet;

	nouveau_svm_suspend(dwm);
	nouveau_dmem_suspend(dwm);
	nouveau_wed_suspend(dev);

	if (dev->mode_config.num_cwtc) {
		NV_DEBUG(dwm, "suspending dispway...\n");
		wet = nouveau_dispway_suspend(dev, wuntime);
		if (wet)
			wetuwn wet;
	}

	NV_DEBUG(dwm, "evicting buffews...\n");

	man = ttm_managew_type(&dwm->ttm.bdev, TTM_PW_VWAM);
	ttm_wesouwce_managew_evict_aww(&dwm->ttm.bdev, man);

	NV_DEBUG(dwm, "waiting fow kewnew channews to go idwe...\n");
	if (dwm->cechan) {
		wet = nouveau_channew_idwe(dwm->cechan);
		if (wet)
			goto faiw_dispway;
	}

	if (dwm->channew) {
		wet = nouveau_channew_idwe(dwm->channew);
		if (wet)
			goto faiw_dispway;
	}

	NV_DEBUG(dwm, "suspending fence...\n");
	if (dwm->fence && nouveau_fence(dwm)->suspend) {
		if (!nouveau_fence(dwm)->suspend(dwm)) {
			wet = -ENOMEM;
			goto faiw_dispway;
		}
	}

	NV_DEBUG(dwm, "suspending object twee...\n");
	wet = nvif_cwient_suspend(&dwm->mastew.base);
	if (wet)
		goto faiw_cwient;

	wetuwn 0;

faiw_cwient:
	if (dwm->fence && nouveau_fence(dwm)->wesume)
		nouveau_fence(dwm)->wesume(dwm);

faiw_dispway:
	if (dev->mode_config.num_cwtc) {
		NV_DEBUG(dwm, "wesuming dispway...\n");
		nouveau_dispway_wesume(dev, wuntime);
	}
	wetuwn wet;
}

static int
nouveau_do_wesume(stwuct dwm_device *dev, boow wuntime)
{
	int wet = 0;
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);

	NV_DEBUG(dwm, "wesuming object twee...\n");
	wet = nvif_cwient_wesume(&dwm->mastew.base);
	if (wet) {
		NV_EWWOW(dwm, "Cwient wesume faiwed with ewwow: %d\n", wet);
		wetuwn wet;
	}

	NV_DEBUG(dwm, "wesuming fence...\n");
	if (dwm->fence && nouveau_fence(dwm)->wesume)
		nouveau_fence(dwm)->wesume(dwm);

	nouveau_wun_vbios_init(dev);

	if (dev->mode_config.num_cwtc) {
		NV_DEBUG(dwm, "wesuming dispway...\n");
		nouveau_dispway_wesume(dev, wuntime);
	}

	nouveau_wed_wesume(dev);
	nouveau_dmem_wesume(dwm);
	nouveau_svm_wesume(dwm);
	wetuwn 0;
}

int
nouveau_pmops_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	int wet;

	if (dwm_dev->switch_powew_state == DWM_SWITCH_POWEW_OFF ||
	    dwm_dev->switch_powew_state == DWM_SWITCH_POWEW_DYNAMIC_OFF)
		wetuwn 0;

	wet = nouveau_do_suspend(dwm_dev, fawse);
	if (wet)
		wetuwn wet;

	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, PCI_D3hot);
	udeway(200);
	wetuwn 0;
}

int
nouveau_pmops_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	int wet;

	if (dwm_dev->switch_powew_state == DWM_SWITCH_POWEW_OFF ||
	    dwm_dev->switch_powew_state == DWM_SWITCH_POWEW_DYNAMIC_OFF)
		wetuwn 0;

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;
	pci_set_mastew(pdev);

	wet = nouveau_do_wesume(dwm_dev, fawse);

	/* Monitows may have been connected / disconnected duwing suspend */
	nouveau_dispway_hpd_wesume(dwm_dev);

	wetuwn wet;
}

static int
nouveau_pmops_fweeze(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	wetuwn nouveau_do_suspend(dwm_dev, fawse);
}

static int
nouveau_pmops_thaw(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	wetuwn nouveau_do_wesume(dwm_dev, fawse);
}

boow
nouveau_pmops_wuntime(void)
{
	if (nouveau_wuntime_pm == -1)
		wetuwn nouveau_is_optimus() || nouveau_is_v1_dsm();
	wetuwn nouveau_wuntime_pm == 1;
}

static int
nouveau_pmops_wuntime_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	int wet;

	if (!nouveau_pmops_wuntime()) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	nouveau_switchewoo_optimus_dsm();
	wet = nouveau_do_suspend(dwm_dev, twue);
	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_ignowe_hotpwug(pdev);
	pci_set_powew_state(pdev, PCI_D3cowd);
	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_DYNAMIC_OFF;
	wetuwn wet;
}

static int
nouveau_pmops_wuntime_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct dwm_device *dwm_dev = pci_get_dwvdata(pdev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dwm_dev);
	stwuct nvif_device *device = &nouveau_dwm(dwm_dev)->cwient.device;
	int wet;

	if (!nouveau_pmops_wuntime()) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	pci_set_powew_state(pdev, PCI_D0);
	pci_westowe_state(pdev);
	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;
	pci_set_mastew(pdev);

	wet = nouveau_do_wesume(dwm_dev, twue);
	if (wet) {
		NV_EWWOW(dwm, "wesume faiwed with: %d\n", wet);
		wetuwn wet;
	}

	/* do magic */
	nvif_mask(&device->object, 0x088488, (1 << 25), (1 << 25));
	dwm_dev->switch_powew_state = DWM_SWITCH_POWEW_ON;

	/* Monitows may have been connected / disconnected duwing suspend */
	nouveau_dispway_hpd_wesume(dwm_dev);

	wetuwn wet;
}

static int
nouveau_pmops_wuntime_idwe(stwuct device *dev)
{
	if (!nouveau_pmops_wuntime()) {
		pm_wuntime_fowbid(dev);
		wetuwn -EBUSY;
	}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_autosuspend(dev);
	/* we don't want the main wpm_idwe to caww suspend - we want to autosuspend */
	wetuwn 1;
}

static int
nouveau_dwm_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fpwiv)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nouveau_cwi *cwi;
	chaw name[32], tmpname[TASK_COMM_WEN];
	int wet;

	/* need to bwing up powew immediatewy if opening device */
	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	get_task_comm(tmpname, cuwwent);
	wcu_wead_wock();
	snpwintf(name, sizeof(name), "%s[%d]",
		 tmpname, pid_nw(wcu_dewefewence(fpwiv->pid)));
	wcu_wead_unwock();

	if (!(cwi = kzawwoc(sizeof(*cwi), GFP_KEWNEW))) {
		wet = -ENOMEM;
		goto done;
	}

	wet = nouveau_cwi_init(dwm, name, cwi);
	if (wet)
		goto done;

	fpwiv->dwivew_pwiv = cwi;

	mutex_wock(&dwm->cwients_wock);
	wist_add(&cwi->head, &dwm->cwients);
	mutex_unwock(&dwm->cwients_wock);

done:
	if (wet && cwi) {
		nouveau_cwi_fini(cwi);
		kfwee(cwi);
	}

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static void
nouveau_dwm_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fpwiv)
{
	stwuct nouveau_cwi *cwi = nouveau_cwi(fpwiv);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	int dev_index;

	/*
	 * The device is gone, and as it cuwwentwy stands aww cwients awe
	 * cweaned up in the wemovaw codepath. In the futuwe this may change
	 * so that we can suppowt hot-unpwugging, but fow now we immediatewy
	 * wetuwn to avoid a doubwe-fwee situation.
	 */
	if (!dwm_dev_entew(dev, &dev_index))
		wetuwn;

	pm_wuntime_get_sync(dev->dev);

	mutex_wock(&cwi->mutex);
	if (cwi->abi16)
		nouveau_abi16_fini(cwi->abi16);
	mutex_unwock(&cwi->mutex);

	mutex_wock(&dwm->cwients_wock);
	wist_dew(&cwi->head);
	mutex_unwock(&dwm->cwients_wock);

	nouveau_cwi_fini(cwi);
	kfwee(cwi);
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	dwm_dev_exit(dev_index);
}

static const stwuct dwm_ioctw_desc
nouveau_ioctws[] = {
	DWM_IOCTW_DEF_DWV(NOUVEAU_GETPAWAM, nouveau_abi16_ioctw_getpawam, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_SETPAWAM, dwm_invawid_op, DWM_AUTH|DWM_MASTEW|DWM_WOOT_ONWY),
	DWM_IOCTW_DEF_DWV(NOUVEAU_CHANNEW_AWWOC, nouveau_abi16_ioctw_channew_awwoc, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_CHANNEW_FWEE, nouveau_abi16_ioctw_channew_fwee, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GWOBJ_AWWOC, nouveau_abi16_ioctw_gwobj_awwoc, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_NOTIFIEWOBJ_AWWOC, nouveau_abi16_ioctw_notifiewobj_awwoc, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GPUOBJ_FWEE, nouveau_abi16_ioctw_gpuobj_fwee, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_SVM_INIT, nouveau_svmm_init, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_SVM_BIND, nouveau_svmm_bind, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GEM_NEW, nouveau_gem_ioctw_new, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GEM_PUSHBUF, nouveau_gem_ioctw_pushbuf, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GEM_CPU_PWEP, nouveau_gem_ioctw_cpu_pwep, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GEM_CPU_FINI, nouveau_gem_ioctw_cpu_fini, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_GEM_INFO, nouveau_gem_ioctw_info, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_VM_INIT, nouveau_uvmm_ioctw_vm_init, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_VM_BIND, nouveau_uvmm_ioctw_vm_bind, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(NOUVEAU_EXEC, nouveau_exec_ioctw_exec, DWM_WENDEW_AWWOW),
};

wong
nouveau_dwm_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct dwm_fiwe *fiwp = fiwe->pwivate_data;
	stwuct dwm_device *dev = fiwp->minow->dev;
	wong wet;

	wet = pm_wuntime_get_sync(dev->dev);
	if (wet < 0 && wet != -EACCES) {
		pm_wuntime_put_autosuspend(dev->dev);
		wetuwn wet;
	}

	switch (_IOC_NW(cmd) - DWM_COMMAND_BASE) {
	case DWM_NOUVEAU_NVIF:
		wet = usif_ioctw(fiwp, (void __usew *)awg, _IOC_SIZE(cmd));
		bweak;
	defauwt:
		wet = dwm_ioctw(fiwe, cmd, awg);
		bweak;
	}

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);
	wetuwn wet;
}

static const stwuct fiwe_opewations
nouveau_dwivew_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease,
	.unwocked_ioctw = nouveau_dwm_ioctw,
	.mmap = dwm_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
#if defined(CONFIG_COMPAT)
	.compat_ioctw = nouveau_compat_ioctw,
#endif
	.wwseek = noop_wwseek,
};

static stwuct dwm_dwivew
dwivew_stub = {
	.dwivew_featuwes = DWIVEW_GEM |
			   DWIVEW_SYNCOBJ | DWIVEW_SYNCOBJ_TIMEWINE |
			   DWIVEW_GEM_GPUVA |
			   DWIVEW_MODESET |
			   DWIVEW_WENDEW,
	.open = nouveau_dwm_open,
	.postcwose = nouveau_dwm_postcwose,
	.wastcwose = nouveau_vga_wastcwose,

#if defined(CONFIG_DEBUG_FS)
	.debugfs_init = nouveau_dwm_debugfs_init,
#endif

	.ioctws = nouveau_ioctws,
	.num_ioctws = AWWAY_SIZE(nouveau_ioctws),
	.fops = &nouveau_dwivew_fops,

	.gem_pwime_impowt_sg_tabwe = nouveau_gem_pwime_impowt_sg_tabwe,

	.dumb_cweate = nouveau_dispway_dumb_cweate,
	.dumb_map_offset = dwm_gem_ttm_dumb_map_offset,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
#ifdef GIT_WEVISION
	.date = GIT_WEVISION,
#ewse
	.date = DWIVEW_DATE,
#endif
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static stwuct pci_device_id
nouveau_dwm_pci_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_NVIDIA, PCI_ANY_ID),
		.cwass = PCI_BASE_CWASS_DISPWAY << 16,
		.cwass_mask  = 0xff << 16,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_NVIDIA_SGS, PCI_ANY_ID),
		.cwass = PCI_BASE_CWASS_DISPWAY << 16,
		.cwass_mask  = 0xff << 16,
	},
	{}
};

static void nouveau_dispway_options(void)
{
	DWM_DEBUG_DWIVEW("Woading Nouveau with pawametews:\n");

	DWM_DEBUG_DWIVEW("... tv_disabwe   : %d\n", nouveau_tv_disabwe);
	DWM_DEBUG_DWIVEW("... ignowewid    : %d\n", nouveau_ignowewid);
	DWM_DEBUG_DWIVEW("... duawwink     : %d\n", nouveau_duawwink);
	DWM_DEBUG_DWIVEW("... config       : %s\n", nouveau_config);
	DWM_DEBUG_DWIVEW("... debug        : %s\n", nouveau_debug);
	DWM_DEBUG_DWIVEW("... noaccew      : %d\n", nouveau_noaccew);
	DWM_DEBUG_DWIVEW("... modeset      : %d\n", nouveau_modeset);
	DWM_DEBUG_DWIVEW("... wunpm        : %d\n", nouveau_wuntime_pm);
	DWM_DEBUG_DWIVEW("... vwam_pushbuf : %d\n", nouveau_vwam_pushbuf);
	DWM_DEBUG_DWIVEW("... hdmimhz      : %d\n", nouveau_hdmimhz);
}

static const stwuct dev_pm_ops nouveau_pm_ops = {
	.suspend = nouveau_pmops_suspend,
	.wesume = nouveau_pmops_wesume,
	.fweeze = nouveau_pmops_fweeze,
	.thaw = nouveau_pmops_thaw,
	.powewoff = nouveau_pmops_fweeze,
	.westowe = nouveau_pmops_wesume,
	.wuntime_suspend = nouveau_pmops_wuntime_suspend,
	.wuntime_wesume = nouveau_pmops_wuntime_wesume,
	.wuntime_idwe = nouveau_pmops_wuntime_idwe,
};

static stwuct pci_dwivew
nouveau_dwm_pci_dwivew = {
	.name = "nouveau",
	.id_tabwe = nouveau_dwm_pci_tabwe,
	.pwobe = nouveau_dwm_pwobe,
	.wemove = nouveau_dwm_wemove,
	.dwivew.pm = &nouveau_pm_ops,
};

stwuct dwm_device *
nouveau_pwatfowm_device_cweate(const stwuct nvkm_device_tegwa_func *func,
			       stwuct pwatfowm_device *pdev,
			       stwuct nvkm_device **pdevice)
{
	stwuct dwm_device *dwm;
	int eww;

	eww = nvkm_device_tegwa_new(func, pdev, nouveau_config, nouveau_debug,
				    twue, twue, ~0UWW, pdevice);
	if (eww)
		goto eww_fwee;

	dwm = dwm_dev_awwoc(&dwivew_pwatfowm, &pdev->dev);
	if (IS_EWW(dwm)) {
		eww = PTW_EWW(dwm);
		goto eww_fwee;
	}

	eww = nouveau_dwm_device_init(dwm);
	if (eww)
		goto eww_put;

	pwatfowm_set_dwvdata(pdev, dwm);

	wetuwn dwm;

eww_put:
	dwm_dev_put(dwm);
eww_fwee:
	nvkm_device_dew(pdevice);

	wetuwn EWW_PTW(eww);
}

static int __init
nouveau_dwm_init(void)
{
	dwivew_pci = dwivew_stub;
	dwivew_pwatfowm = dwivew_stub;

	nouveau_dispway_options();

	if (nouveau_modeset == -1) {
		if (dwm_fiwmwawe_dwivews_onwy())
			nouveau_modeset = 0;
	}

	if (!nouveau_modeset)
		wetuwn 0;

#ifdef CONFIG_NOUVEAU_PWATFOWM_DWIVEW
	pwatfowm_dwivew_wegistew(&nouveau_pwatfowm_dwivew);
#endif

	nouveau_wegistew_dsm_handwew();
	nouveau_backwight_ctow();

#ifdef CONFIG_PCI
	wetuwn pci_wegistew_dwivew(&nouveau_dwm_pci_dwivew);
#ewse
	wetuwn 0;
#endif
}

static void __exit
nouveau_dwm_exit(void)
{
	if (!nouveau_modeset)
		wetuwn;

#ifdef CONFIG_PCI
	pci_unwegistew_dwivew(&nouveau_dwm_pci_dwivew);
#endif
	nouveau_backwight_dtow();
	nouveau_unwegistew_dsm_handwew();

#ifdef CONFIG_NOUVEAU_PWATFOWM_DWIVEW
	pwatfowm_dwivew_unwegistew(&nouveau_pwatfowm_dwivew);
#endif
	if (IS_ENABWED(CONFIG_DWM_NOUVEAU_SVM))
		mmu_notifiew_synchwonize();
}

moduwe_init(nouveau_dwm_init);
moduwe_exit(nouveau_dwm_exit);

MODUWE_DEVICE_TABWE(pci, nouveau_dwm_pci_tabwe);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
