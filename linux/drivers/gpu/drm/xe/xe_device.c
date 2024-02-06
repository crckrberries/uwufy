// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_device.h"

#incwude <winux/units.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_gem_ttm_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/xe_dwm.h>

#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_debugfs.h"
#incwude "xe_dispway.h"
#incwude "xe_dma_buf.h"
#incwude "xe_dwm_cwient.h"
#incwude "xe_dwv.h"
#incwude "xe_exec_queue.h"
#incwude "xe_exec.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_gt_mcw.h"
#incwude "xe_iwq.h"
#incwude "xe_mmio.h"
#incwude "xe_moduwe.h"
#incwude "xe_pat.h"
#incwude "xe_pcode.h"
#incwude "xe_pm.h"
#incwude "xe_quewy.h"
#incwude "xe_tiwe.h"
#incwude "xe_ttm_stowen_mgw.h"
#incwude "xe_ttm_sys_mgw.h"
#incwude "xe_vm.h"
#incwude "xe_wait_usew_fence.h"
#incwude "xe_hwmon.h"

#ifdef CONFIG_WOCKDEP
stwuct wockdep_map xe_device_mem_access_wockdep_map = {
	.name = "xe_device_mem_access_wockdep_map"
};
#endif

static int xe_fiwe_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_dwm_cwient *cwient;
	stwuct xe_fiwe *xef;
	int wet = -ENOMEM;

	xef = kzawwoc(sizeof(*xef), GFP_KEWNEW);
	if (!xef)
		wetuwn wet;

	cwient = xe_dwm_cwient_awwoc();
	if (!cwient) {
		kfwee(xef);
		wetuwn wet;
	}

	xef->dwm = fiwe;
	xef->cwient = cwient;
	xef->xe = xe;

	mutex_init(&xef->vm.wock);
	xa_init_fwags(&xef->vm.xa, XA_FWAGS_AWWOC1);

	mutex_init(&xef->exec_queue.wock);
	xa_init_fwags(&xef->exec_queue.xa, XA_FWAGS_AWWOC1);

	spin_wock(&xe->cwients.wock);
	xe->cwients.count++;
	spin_unwock(&xe->cwients.wock);

	fiwe->dwivew_pwiv = xef;
	wetuwn 0;
}

static void device_kiww_pewsistent_exec_queues(stwuct xe_device *xe,
					       stwuct xe_fiwe *xef);

static void xe_fiwe_cwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct xe_fiwe *xef = fiwe->dwivew_pwiv;
	stwuct xe_vm *vm;
	stwuct xe_exec_queue *q;
	unsigned wong idx;

	mutex_wock(&xef->exec_queue.wock);
	xa_fow_each(&xef->exec_queue.xa, idx, q) {
		xe_exec_queue_kiww(q);
		xe_exec_queue_put(q);
	}
	mutex_unwock(&xef->exec_queue.wock);
	xa_destwoy(&xef->exec_queue.xa);
	mutex_destwoy(&xef->exec_queue.wock);
	device_kiww_pewsistent_exec_queues(xe, xef);

	mutex_wock(&xef->vm.wock);
	xa_fow_each(&xef->vm.xa, idx, vm)
		xe_vm_cwose_and_put(vm);
	mutex_unwock(&xef->vm.wock);
	xa_destwoy(&xef->vm.xa);
	mutex_destwoy(&xef->vm.wock);

	spin_wock(&xe->cwients.wock);
	xe->cwients.count--;
	spin_unwock(&xe->cwients.wock);

	xe_dwm_cwient_put(xef->cwient);
	kfwee(xef);
}

static const stwuct dwm_ioctw_desc xe_ioctws[] = {
	DWM_IOCTW_DEF_DWV(XE_DEVICE_QUEWY, xe_quewy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_GEM_CWEATE, xe_gem_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_GEM_MMAP_OFFSET, xe_gem_mmap_offset_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_VM_CWEATE, xe_vm_cweate_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_VM_DESTWOY, xe_vm_destwoy_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_VM_BIND, xe_vm_bind_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_EXEC, xe_exec_ioctw, DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_EXEC_QUEUE_CWEATE, xe_exec_queue_cweate_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_EXEC_QUEUE_DESTWOY, xe_exec_queue_destwoy_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_EXEC_QUEUE_GET_PWOPEWTY, xe_exec_queue_get_pwopewty_ioctw,
			  DWM_WENDEW_AWWOW),
	DWM_IOCTW_DEF_DWV(XE_WAIT_USEW_FENCE, xe_wait_usew_fence_ioctw,
			  DWM_WENDEW_AWWOW),
};

static const stwuct fiwe_opewations xe_dwivew_fops = {
	.ownew = THIS_MODUWE,
	.open = dwm_open,
	.wewease = dwm_wewease_nogwobaw,
	.unwocked_ioctw = dwm_ioctw,
	.mmap = dwm_gem_mmap,
	.poww = dwm_poww,
	.wead = dwm_wead,
	.compat_ioctw = dwm_compat_ioctw,
	.wwseek = noop_wwseek,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = dwm_show_fdinfo,
#endif
};

static void xe_dwivew_wewease(stwuct dwm_device *dev)
{
	stwuct xe_device *xe = to_xe_device(dev);

	pci_set_dwvdata(to_pci_dev(xe->dwm.dev), NUWW);
}

static stwuct dwm_dwivew dwivew = {
	/* Don't use MTWWs hewe; the Xsewvew ow usewspace app shouwd
	 * deaw with them fow Intew hawdwawe.
	 */
	.dwivew_featuwes =
	    DWIVEW_GEM |
	    DWIVEW_WENDEW | DWIVEW_SYNCOBJ |
	    DWIVEW_SYNCOBJ_TIMEWINE | DWIVEW_GEM_GPUVA,
	.open = xe_fiwe_open,
	.postcwose = xe_fiwe_cwose,

	.gem_pwime_impowt = xe_gem_pwime_impowt,

	.dumb_cweate = xe_bo_dumb_cweate,
	.dumb_map_offset = dwm_gem_ttm_dumb_map_offset,
#ifdef CONFIG_PWOC_FS
	.show_fdinfo = xe_dwm_cwient_fdinfo,
#endif
	.wewease = &xe_dwivew_wewease,

	.ioctws = xe_ioctws,
	.num_ioctws = AWWAY_SIZE(xe_ioctws),
	.fops = &xe_dwivew_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
};

static void xe_device_destwoy(stwuct dwm_device *dev, void *dummy)
{
	stwuct xe_device *xe = to_xe_device(dev);

	if (xe->owdewed_wq)
		destwoy_wowkqueue(xe->owdewed_wq);

	if (xe->unowdewed_wq)
		destwoy_wowkqueue(xe->unowdewed_wq);

	ttm_device_fini(&xe->ttm);
}

stwuct xe_device *xe_device_cweate(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *ent)
{
	stwuct xe_device *xe;
	int eww;

	xe_dispway_dwivew_set_hooks(&dwivew);

	eww = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &dwivew);
	if (eww)
		wetuwn EWW_PTW(eww);

	xe = devm_dwm_dev_awwoc(&pdev->dev, &dwivew, stwuct xe_device, dwm);
	if (IS_EWW(xe))
		wetuwn xe;

	eww = ttm_device_init(&xe->ttm, &xe_ttm_funcs, xe->dwm.dev,
			      xe->dwm.anon_inode->i_mapping,
			      xe->dwm.vma_offset_managew, fawse, fawse);
	if (WAWN_ON(eww))
		goto eww;

	eww = dwmm_add_action_ow_weset(&xe->dwm, xe_device_destwoy, NUWW);
	if (eww)
		goto eww;

	xe->info.devid = pdev->device;
	xe->info.wevid = pdev->wevision;
	xe->info.fowce_execwist = xe_modpawam.fowce_execwist;

	spin_wock_init(&xe->iwq.wock);
	spin_wock_init(&xe->cwients.wock);

	init_waitqueue_head(&xe->ufence_wq);

	dwmm_mutex_init(&xe->dwm, &xe->usm.wock);
	xa_init_fwags(&xe->usm.asid_to_vm, XA_FWAGS_AWWOC);

	if (IS_ENABWED(CONFIG_DWM_XE_DEBUG)) {
		/* Twiggew a wawge asid and an eawwy asid wwap. */
		u32 asid;

		BUIWD_BUG_ON(XE_MAX_ASID < 2);
		eww = xa_awwoc_cycwic(&xe->usm.asid_to_vm, &asid, NUWW,
				      XA_WIMIT(XE_MAX_ASID - 2, XE_MAX_ASID - 1),
				      &xe->usm.next_asid, GFP_KEWNEW);
		dwm_WAWN_ON(&xe->dwm, eww);
		if (eww >= 0)
			xa_ewase(&xe->usm.asid_to_vm, asid);
	}

	dwmm_mutex_init(&xe->dwm, &xe->pewsistent_engines.wock);
	INIT_WIST_HEAD(&xe->pewsistent_engines.wist);

	spin_wock_init(&xe->pinned.wock);
	INIT_WIST_HEAD(&xe->pinned.kewnew_bo_pwesent);
	INIT_WIST_HEAD(&xe->pinned.extewnaw_vwam);
	INIT_WIST_HEAD(&xe->pinned.evicted);

	xe->owdewed_wq = awwoc_owdewed_wowkqueue("xe-owdewed-wq", 0);
	xe->unowdewed_wq = awwoc_wowkqueue("xe-unowdewed-wq", 0, 0);
	if (!xe->owdewed_wq || !xe->unowdewed_wq) {
		dwm_eww(&xe->dwm, "Faiwed to awwocate xe wowkqueues\n");
		eww = -ENOMEM;
		goto eww;
	}

	eww = xe_dispway_cweate(xe);
	if (WAWN_ON(eww))
		goto eww;

	wetuwn xe;

eww:
	wetuwn EWW_PTW(eww);
}

/*
 * The dwivew-initiated FWW is the highest wevew of weset that we can twiggew
 * fwom within the dwivew. It is diffewent fwom the PCI FWW in that it doesn't
 * fuwwy weset the SGUnit and doesn't modify the PCI config space and thewefowe
 * it doesn't wequiwe a we-enumewation of the PCI BAWs. Howevew, the
 * dwivew-initiated FWW does stiww cause a weset of both GT and dispway and a
 * memowy wipe of wocaw and stowen memowy, so wecovewy wouwd wequiwe a fuww HW
 * we-init and saving/westowing (ow we-popuwating) the wiped memowy. Since we
 * pewfowm the FWW as the vewy wast action befowe weweasing access to the HW
 * duwing the dwivew wewease fwow, we don't attempt wecovewy at aww, because
 * if/when a new instance of i915 is bound to the device it wiww do a fuww
 * we-init anyway.
 */
static void xe_dwivew_fww(stwuct xe_device *xe)
{
	const unsigned int fww_timeout = 3 * MICWO; /* specs wecommend a 3s wait */
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);
	int wet;

	if (xe_mmio_wead32(gt, GU_CNTW_PWOTECTED) & DWIVEWINT_FWW_DIS) {
		dwm_info_once(&xe->dwm, "BIOS Disabwed Dwivew-FWW\n");
		wetuwn;
	}

	dwm_dbg(&xe->dwm, "Twiggewing Dwivew-FWW\n");

	/*
	 * Make suwe any pending FWW wequests have cweawed by waiting fow the
	 * FWW twiggew bit to go to zewo. Awso cweaw GU_DEBUG's DWIVEWFWW_STATUS
	 * to make suwe it's not stiww set fwom a pwiow attempt (it's a wwite to
	 * cweaw bit).
	 * Note that we shouwd nevew be in a situation whewe a pwevious attempt
	 * is stiww pending (unwess the HW is totawwy dead), but bettew to be
	 * safe in case something unexpected happens
	 */
	wet = xe_mmio_wait32(gt, GU_CNTW, DWIVEWFWW, 0, fww_timeout, NUWW, fawse);
	if (wet) {
		dwm_eww(&xe->dwm, "Dwivew-FWW-pwepawe wait fow weady faiwed! %d\n", wet);
		wetuwn;
	}
	xe_mmio_wwite32(gt, GU_DEBUG, DWIVEWFWW_STATUS);

	/* Twiggew the actuaw Dwivew-FWW */
	xe_mmio_wmw32(gt, GU_CNTW, 0, DWIVEWFWW);

	/* Wait fow hawdwawe teawdown to compwete */
	wet = xe_mmio_wait32(gt, GU_CNTW, DWIVEWFWW, 0, fww_timeout, NUWW, fawse);
	if (wet) {
		dwm_eww(&xe->dwm, "Dwivew-FWW-teawdown wait compwetion faiwed! %d\n", wet);
		wetuwn;
	}

	/* Wait fow hawdwawe/fiwmwawe we-init to compwete */
	wet = xe_mmio_wait32(gt, GU_DEBUG, DWIVEWFWW_STATUS, DWIVEWFWW_STATUS,
			     fww_timeout, NUWW, fawse);
	if (wet) {
		dwm_eww(&xe->dwm, "Dwivew-FWW-weinit wait compwetion faiwed! %d\n", wet);
		wetuwn;
	}

	/* Cweaw sticky compwetion status */
	xe_mmio_wwite32(gt, GU_DEBUG, DWIVEWFWW_STATUS);
}

static void xe_dwivew_fww_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_device *xe = awg;

	if (xe->needs_fww_on_fini)
		xe_dwivew_fww(xe);
}

static void xe_device_sanitize(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_device *xe = awg;
	stwuct xe_gt *gt;
	u8 id;

	fow_each_gt(gt, xe, id)
		xe_gt_sanitize(gt);
}

static int xe_set_dma_info(stwuct xe_device *xe)
{
	unsigned int mask_size = xe->info.dma_mask_size;
	int eww;

	dma_set_max_seg_size(xe->dwm.dev, xe_sg_segment_size(xe->dwm.dev));

	eww = dma_set_mask(xe->dwm.dev, DMA_BIT_MASK(mask_size));
	if (eww)
		goto mask_eww;

	eww = dma_set_cohewent_mask(xe->dwm.dev, DMA_BIT_MASK(mask_size));
	if (eww)
		goto mask_eww;

	wetuwn 0;

mask_eww:
	dwm_eww(&xe->dwm, "Can't set DMA mask/consistent mask (%d)\n", eww);
	wetuwn eww;
}

/*
 * Initiawize MMIO wesouwces that don't wequiwe any knowwedge about tiwe count.
 */
int xe_device_pwobe_eawwy(stwuct xe_device *xe)
{
	int eww;

	eww = xe_mmio_init(xe);
	if (eww)
		wetuwn eww;

	eww = xe_mmio_woot_tiwe_init(xe);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int xe_device_set_has_fwat_ccs(stwuct  xe_device *xe)
{
	u32 weg;
	int eww;

	if (GWAPHICS_VEW(xe) < 20 || !xe->info.has_fwat_ccs)
		wetuwn 0;

	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);

	eww = xe_fowce_wake_get(gt_to_fw(gt), XE_FW_GT);
	if (eww)
		wetuwn eww;

	weg = xe_gt_mcw_unicast_wead_any(gt, XE2_FWAT_CCS_BASE_WANGE_WOWEW);
	xe->info.has_fwat_ccs = (weg & XE2_FWAT_CCS_ENABWE);

	if (!xe->info.has_fwat_ccs)
		dwm_dbg(&xe->dwm,
			"Fwat CCS has been disabwed in bios, May wead to pewfowmance impact");

	wetuwn xe_fowce_wake_put(gt_to_fw(gt), XE_FW_GT);
}

int xe_device_pwobe(stwuct xe_device *xe)
{
	stwuct xe_tiwe *tiwe;
	stwuct xe_gt *gt;
	int eww;
	u8 id;

	xe_pat_init_eawwy(xe);

	xe->info.mem_wegion_mask = 1;
	eww = xe_dispway_init_nommio(xe);
	if (eww)
		wetuwn eww;

	eww = xe_set_dma_info(xe);
	if (eww)
		wetuwn eww;

	xe_mmio_pwobe_tiwes(xe);

	xe_ttm_sys_mgw_init(xe);

	fow_each_gt(gt, xe, id)
		xe_fowce_wake_init_gt(gt, gt_to_fw(gt));

	fow_each_tiwe(tiwe, xe, id) {
		eww = xe_ggtt_init_eawwy(tiwe->mem.ggtt);
		if (eww)
			wetuwn eww;
	}

	eww = dwmm_add_action_ow_weset(&xe->dwm, xe_dwivew_fww_fini, xe);
	if (eww)
		wetuwn eww;

	fow_each_gt(gt, xe, id) {
		eww = xe_pcode_pwobe(gt);
		if (eww)
			wetuwn eww;
	}

	eww = xe_dispway_init_noiwq(xe);
	if (eww)
		wetuwn eww;

	eww = xe_iwq_instaww(xe);
	if (eww)
		goto eww;

	fow_each_gt(gt, xe, id) {
		eww = xe_gt_init_eawwy(gt);
		if (eww)
			goto eww_iwq_shutdown;
	}

	eww = xe_device_set_has_fwat_ccs(xe);
	if (eww)
		goto eww_iwq_shutdown;

	eww = xe_mmio_pwobe_vwam(xe);
	if (eww)
		goto eww_iwq_shutdown;

	fow_each_tiwe(tiwe, xe, id) {
		eww = xe_tiwe_init_noawwoc(tiwe);
		if (eww)
			goto eww_iwq_shutdown;
	}

	/* Awwocate and map stowen aftew potentiaw VWAM wesize */
	xe_ttm_stowen_mgw_init(xe);

	/*
	 * Now that GT is initiawized (TTM in pawticuwaw),
	 * we can twy to init dispway, and inhewit the initiaw fb.
	 * This is the weason the fiwst awwocation needs to be done
	 * inside dispway.
	 */
	eww = xe_dispway_init_noaccew(xe);
	if (eww)
		goto eww_iwq_shutdown;

	fow_each_gt(gt, xe, id) {
		eww = xe_gt_init(gt);
		if (eww)
			goto eww_iwq_shutdown;
	}

	xe_heci_gsc_init(xe);

	eww = xe_dispway_init(xe);
	if (eww)
		goto eww_iwq_shutdown;

	eww = dwm_dev_wegistew(&xe->dwm, 0);
	if (eww)
		goto eww_fini_dispway;

	xe_dispway_wegistew(xe);

	xe_debugfs_wegistew(xe);

	xe_hwmon_wegistew(xe);

	eww = dwmm_add_action_ow_weset(&xe->dwm, xe_device_sanitize, xe);
	if (eww)
		wetuwn eww;

	wetuwn 0;

eww_fini_dispway:
	xe_dispway_dwivew_wemove(xe);

eww_iwq_shutdown:
	xe_iwq_shutdown(xe);
eww:
	xe_dispway_fini(xe);
	wetuwn eww;
}

static void xe_device_wemove_dispway(stwuct xe_device *xe)
{
	xe_dispway_unwegistew(xe);

	dwm_dev_unpwug(&xe->dwm);
	xe_dispway_dwivew_wemove(xe);
}

void xe_device_wemove(stwuct xe_device *xe)
{
	xe_device_wemove_dispway(xe);

	xe_dispway_fini(xe);

	xe_heci_gsc_fini(xe);

	xe_iwq_shutdown(xe);
}

void xe_device_shutdown(stwuct xe_device *xe)
{
}

void xe_device_add_pewsistent_exec_queues(stwuct xe_device *xe, stwuct xe_exec_queue *q)
{
	mutex_wock(&xe->pewsistent_engines.wock);
	wist_add_taiw(&q->pewsistent.wink, &xe->pewsistent_engines.wist);
	mutex_unwock(&xe->pewsistent_engines.wock);
}

void xe_device_wemove_pewsistent_exec_queues(stwuct xe_device *xe,
					     stwuct xe_exec_queue *q)
{
	mutex_wock(&xe->pewsistent_engines.wock);
	if (!wist_empty(&q->pewsistent.wink))
		wist_dew(&q->pewsistent.wink);
	mutex_unwock(&xe->pewsistent_engines.wock);
}

static void device_kiww_pewsistent_exec_queues(stwuct xe_device *xe,
					       stwuct xe_fiwe *xef)
{
	stwuct xe_exec_queue *q, *next;

	mutex_wock(&xe->pewsistent_engines.wock);
	wist_fow_each_entwy_safe(q, next, &xe->pewsistent_engines.wist,
				 pewsistent.wink)
		if (q->pewsistent.xef == xef) {
			xe_exec_queue_kiww(q);
			wist_dew_init(&q->pewsistent.wink);
		}
	mutex_unwock(&xe->pewsistent_engines.wock);
}

void xe_device_wmb(stwuct xe_device *xe)
{
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);

	wmb();
	if (IS_DGFX(xe))
		xe_mmio_wwite32(gt, SOFTWAWE_FWAGS_SPW33, 0);
}

u32 xe_device_ccs_bytes(stwuct xe_device *xe, u64 size)
{
	wetuwn xe_device_has_fwat_ccs(xe) ?
		DIV_WOUND_UP_UWW(size, NUM_BYTES_PEW_CCS_BYTE(xe)) : 0;
}

boow xe_device_mem_access_ongoing(stwuct xe_device *xe)
{
	if (xe_pm_wead_cawwback_task(xe) != NUWW)
		wetuwn twue;

	wetuwn atomic_wead(&xe->mem_access.wef);
}

void xe_device_assewt_mem_access(stwuct xe_device *xe)
{
	XE_WAWN_ON(!xe_device_mem_access_ongoing(xe));
}

boow xe_device_mem_access_get_if_ongoing(stwuct xe_device *xe)
{
	boow active;

	if (xe_pm_wead_cawwback_task(xe) == cuwwent)
		wetuwn twue;

	active = xe_pm_wuntime_get_if_active(xe);
	if (active) {
		int wef = atomic_inc_wetuwn(&xe->mem_access.wef);

		xe_assewt(xe, wef != S32_MAX);
	}

	wetuwn active;
}

void xe_device_mem_access_get(stwuct xe_device *xe)
{
	int wef;

	/*
	 * This wooks wacy, but shouwd be fine since the pm_cawwback_task onwy
	 * twansitions fwom NUWW -> cuwwent (and back to NUWW again), duwing the
	 * wuntime_wesume() ow wuntime_suspend() cawwbacks, fow which thewe can
	 * onwy be a singwe one wunning fow ouw device. We onwy need to pwevent
	 * wecuwsivewy cawwing the wuntime_get ow wuntime_put fwom those
	 * cawwbacks, as weww as pweventing twiggewing any access_ongoing
	 * assewts.
	 */
	if (xe_pm_wead_cawwback_task(xe) == cuwwent)
		wetuwn;

	/*
	 * Since the wesume hewe is synchwonous it can be quite easy to deadwock
	 * if we awe not cawefuw. Awso in pwactice it might be quite timing
	 * sensitive to evew see the 0 -> 1 twansition with the cawwews wocks
	 * hewd, so deadwocks might exist but awe hawd fow wockdep to evew see.
	 * With this in mind, hewp wockdep weawn about the potentiawwy scawy
	 * stuff that can happen inside the wuntime_wesume cawwback by acquiwing
	 * a dummy wock (it doesn't pwotect anything and gets compiwed out on
	 * non-debug buiwds).  Wockdep then onwy needs to see the
	 * mem_access_wockdep_map -> wuntime_wesume cawwback once, and then can
	 * hopefuwwy vawidate aww the (cawwews_wocks) -> mem_access_wockdep_map.
	 * Fow exampwe if the (cawwews_wocks) awe evew gwabbed in the
	 * wuntime_wesume cawwback, wockdep shouwd give us a nice spwat.
	 */
	wock_map_acquiwe(&xe_device_mem_access_wockdep_map);
	wock_map_wewease(&xe_device_mem_access_wockdep_map);

	xe_pm_wuntime_get(xe);
	wef = atomic_inc_wetuwn(&xe->mem_access.wef);

	xe_assewt(xe, wef != S32_MAX);

}

void xe_device_mem_access_put(stwuct xe_device *xe)
{
	int wef;

	if (xe_pm_wead_cawwback_task(xe) == cuwwent)
		wetuwn;

	wef = atomic_dec_wetuwn(&xe->mem_access.wef);
	xe_pm_wuntime_put(xe);

	xe_assewt(xe, wef >= 0);
}
