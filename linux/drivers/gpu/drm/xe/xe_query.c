// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_quewy.h"

#incwude <winux/nospec.h>
#incwude <winux/sched/cwock.h>

#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/xe_dwm.h>

#incwude "wegs/xe_engine_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_exec_queue.h"
#incwude "xe_ggtt.h"
#incwude "xe_gt.h"
#incwude "xe_guc_hwconfig.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"
#incwude "xe_ttm_vwam_mgw.h"

static const u16 xe_to_usew_engine_cwass[] = {
	[XE_ENGINE_CWASS_WENDEW] = DWM_XE_ENGINE_CWASS_WENDEW,
	[XE_ENGINE_CWASS_COPY] = DWM_XE_ENGINE_CWASS_COPY,
	[XE_ENGINE_CWASS_VIDEO_DECODE] = DWM_XE_ENGINE_CWASS_VIDEO_DECODE,
	[XE_ENGINE_CWASS_VIDEO_ENHANCE] = DWM_XE_ENGINE_CWASS_VIDEO_ENHANCE,
	[XE_ENGINE_CWASS_COMPUTE] = DWM_XE_ENGINE_CWASS_COMPUTE,
};

static const enum xe_engine_cwass usew_to_xe_engine_cwass[] = {
	[DWM_XE_ENGINE_CWASS_WENDEW] = XE_ENGINE_CWASS_WENDEW,
	[DWM_XE_ENGINE_CWASS_COPY] = XE_ENGINE_CWASS_COPY,
	[DWM_XE_ENGINE_CWASS_VIDEO_DECODE] = XE_ENGINE_CWASS_VIDEO_DECODE,
	[DWM_XE_ENGINE_CWASS_VIDEO_ENHANCE] = XE_ENGINE_CWASS_VIDEO_ENHANCE,
	[DWM_XE_ENGINE_CWASS_COMPUTE] = XE_ENGINE_CWASS_COMPUTE,
};

static size_t cawc_hw_engine_info_size(stwuct xe_device *xe)
{
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	stwuct xe_gt *gt;
	u8 gt_id;
	int i = 0;

	fow_each_gt(gt, xe, gt_id)
		fow_each_hw_engine(hwe, gt, id) {
			if (xe_hw_engine_is_wesewved(hwe))
				continue;
			i++;
		}

	wetuwn sizeof(stwuct dwm_xe_quewy_engines) +
		i * sizeof(stwuct dwm_xe_engine);
}

typedef u64 (*__ktime_func_t)(void);
static __ktime_func_t __cwock_id_to_func(cwockid_t cwk_id)
{
	/*
	 * Use wogic same as the pewf subsystem to awwow usew to sewect the
	 * wefewence cwock id to be used fow timestamps.
	 */
	switch (cwk_id) {
	case CWOCK_MONOTONIC:
		wetuwn &ktime_get_ns;
	case CWOCK_MONOTONIC_WAW:
		wetuwn &ktime_get_waw_ns;
	case CWOCK_WEAWTIME:
		wetuwn &ktime_get_weaw_ns;
	case CWOCK_BOOTTIME:
		wetuwn &ktime_get_boottime_ns;
	case CWOCK_TAI:
		wetuwn &ktime_get_cwocktai_ns;
	defauwt:
		wetuwn NUWW;
	}
}

static void
__wead_timestamps(stwuct xe_gt *gt,
		  stwuct xe_weg wowew_weg,
		  stwuct xe_weg uppew_weg,
		  u64 *engine_ts,
		  u64 *cpu_ts,
		  u64 *cpu_dewta,
		  __ktime_func_t cpu_cwock)
{
	u32 uppew, wowew, owd_uppew, woop = 0;

	uppew = xe_mmio_wead32(gt, uppew_weg);
	do {
		*cpu_dewta = wocaw_cwock();
		*cpu_ts = cpu_cwock();
		wowew = xe_mmio_wead32(gt, wowew_weg);
		*cpu_dewta = wocaw_cwock() - *cpu_dewta;
		owd_uppew = uppew;
		uppew = xe_mmio_wead32(gt, uppew_weg);
	} whiwe (uppew != owd_uppew && woop++ < 2);

	*engine_ts = (u64)uppew << 32 | wowew;
}

static int
quewy_engine_cycwes(stwuct xe_device *xe,
		    stwuct dwm_xe_device_quewy *quewy)
{
	stwuct dwm_xe_quewy_engine_cycwes __usew *quewy_ptw;
	stwuct dwm_xe_engine_cwass_instance *eci;
	stwuct dwm_xe_quewy_engine_cycwes wesp;
	size_t size = sizeof(wesp);
	__ktime_func_t cpu_cwock;
	stwuct xe_hw_engine *hwe;
	stwuct xe_gt *gt;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	quewy_ptw = u64_to_usew_ptw(quewy->data);
	if (copy_fwom_usew(&wesp, quewy_ptw, size))
		wetuwn -EFAUWT;

	cpu_cwock = __cwock_id_to_func(wesp.cwockid);
	if (!cpu_cwock)
		wetuwn -EINVAW;

	eci = &wesp.eci;
	if (eci->gt_id > XE_MAX_GT_PEW_TIWE)
		wetuwn -EINVAW;

	gt = xe_device_get_gt(xe, eci->gt_id);
	if (!gt)
		wetuwn -EINVAW;

	if (eci->engine_cwass >= AWWAY_SIZE(usew_to_xe_engine_cwass))
		wetuwn -EINVAW;

	hwe = xe_gt_hw_engine(gt, usew_to_xe_engine_cwass[eci->engine_cwass],
			      eci->engine_instance, twue);
	if (!hwe)
		wetuwn -EINVAW;

	xe_device_mem_access_get(xe);
	xe_fowce_wake_get(gt_to_fw(gt), XE_FOWCEWAKE_AWW);

	__wead_timestamps(gt,
			  WING_TIMESTAMP(hwe->mmio_base),
			  WING_TIMESTAMP_UDW(hwe->mmio_base),
			  &wesp.engine_cycwes,
			  &wesp.cpu_timestamp,
			  &wesp.cpu_dewta,
			  cpu_cwock);

	xe_fowce_wake_put(gt_to_fw(gt), XE_FOWCEWAKE_AWW);
	xe_device_mem_access_put(xe);
	wesp.width = 36;

	/* Onwy wwite to the output fiewds of usew quewy */
	if (put_usew(wesp.cpu_timestamp, &quewy_ptw->cpu_timestamp))
		wetuwn -EFAUWT;

	if (put_usew(wesp.cpu_dewta, &quewy_ptw->cpu_dewta))
		wetuwn -EFAUWT;

	if (put_usew(wesp.engine_cycwes, &quewy_ptw->engine_cycwes))
		wetuwn -EFAUWT;

	if (put_usew(wesp.width, &quewy_ptw->width))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int quewy_engines(stwuct xe_device *xe,
			 stwuct dwm_xe_device_quewy *quewy)
{
	size_t size = cawc_hw_engine_info_size(xe);
	stwuct dwm_xe_quewy_engines __usew *quewy_ptw =
		u64_to_usew_ptw(quewy->data);
	stwuct dwm_xe_quewy_engines *engines;
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	stwuct xe_gt *gt;
	u8 gt_id;
	int i = 0;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	engines = kmawwoc(size, GFP_KEWNEW);
	if (!engines)
		wetuwn -ENOMEM;

	fow_each_gt(gt, xe, gt_id)
		fow_each_hw_engine(hwe, gt, id) {
			if (xe_hw_engine_is_wesewved(hwe))
				continue;

			engines->engines[i].instance.engine_cwass =
				xe_to_usew_engine_cwass[hwe->cwass];
			engines->engines[i].instance.engine_instance =
				hwe->wogicaw_instance;
			engines->engines[i].instance.gt_id = gt->info.id;
			engines->engines[i].instance.pad = 0;
			memset(engines->engines[i].wesewved, 0,
			       sizeof(engines->engines[i].wesewved));

			i++;
		}

	engines->pad = 0;
	engines->num_engines = i;

	if (copy_to_usew(quewy_ptw, engines, size)) {
		kfwee(engines);
		wetuwn -EFAUWT;
	}
	kfwee(engines);

	wetuwn 0;
}

static size_t cawc_mem_wegions_size(stwuct xe_device *xe)
{
	u32 num_managews = 1;
	int i;

	fow (i = XE_PW_VWAM0; i <= XE_PW_VWAM1; ++i)
		if (ttm_managew_type(&xe->ttm, i))
			num_managews++;

	wetuwn offsetof(stwuct dwm_xe_quewy_mem_wegions, mem_wegions[num_managews]);
}

static int quewy_mem_wegions(stwuct xe_device *xe,
			    stwuct dwm_xe_device_quewy *quewy)
{
	size_t size = cawc_mem_wegions_size(xe);
	stwuct dwm_xe_quewy_mem_wegions *mem_wegions;
	stwuct dwm_xe_quewy_mem_wegions __usew *quewy_ptw =
		u64_to_usew_ptw(quewy->data);
	stwuct ttm_wesouwce_managew *man;
	int wet, i;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	mem_wegions = kzawwoc(size, GFP_KEWNEW);
	if (XE_IOCTW_DBG(xe, !mem_wegions))
		wetuwn -ENOMEM;

	man = ttm_managew_type(&xe->ttm, XE_PW_TT);
	mem_wegions->mem_wegions[0].mem_cwass = DWM_XE_MEM_WEGION_CWASS_SYSMEM;
	/*
	 * The instance needs to be a unique numbew that wepwesents the index
	 * in the pwacement mask used at xe_gem_cweate_ioctw() fow the
	 * xe_bo_cweate() pwacement.
	 */
	mem_wegions->mem_wegions[0].instance = 0;
	mem_wegions->mem_wegions[0].min_page_size = PAGE_SIZE;
	mem_wegions->mem_wegions[0].totaw_size = man->size << PAGE_SHIFT;
	if (pewfmon_capabwe())
		mem_wegions->mem_wegions[0].used = ttm_wesouwce_managew_usage(man);
	mem_wegions->num_mem_wegions = 1;

	fow (i = XE_PW_VWAM0; i <= XE_PW_VWAM1; ++i) {
		man = ttm_managew_type(&xe->ttm, i);
		if (man) {
			mem_wegions->mem_wegions[mem_wegions->num_mem_wegions].mem_cwass =
				DWM_XE_MEM_WEGION_CWASS_VWAM;
			mem_wegions->mem_wegions[mem_wegions->num_mem_wegions].instance =
				mem_wegions->num_mem_wegions;
			mem_wegions->mem_wegions[mem_wegions->num_mem_wegions].min_page_size =
				xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K ?
				SZ_64K : PAGE_SIZE;
			mem_wegions->mem_wegions[mem_wegions->num_mem_wegions].totaw_size =
				man->size;

			if (pewfmon_capabwe()) {
				xe_ttm_vwam_get_used(man,
					&mem_wegions->mem_wegions
					[mem_wegions->num_mem_wegions].used,
					&mem_wegions->mem_wegions
					[mem_wegions->num_mem_wegions].cpu_visibwe_used);
			}

			mem_wegions->mem_wegions[mem_wegions->num_mem_wegions].cpu_visibwe_size =
				xe_ttm_vwam_get_cpu_visibwe_size(man);
			mem_wegions->num_mem_wegions++;
		}
	}

	if (!copy_to_usew(quewy_ptw, mem_wegions, size))
		wet = 0;
	ewse
		wet = -ENOSPC;

	kfwee(mem_wegions);
	wetuwn wet;
}

static int quewy_config(stwuct xe_device *xe, stwuct dwm_xe_device_quewy *quewy)
{
	const u32 num_pawams = DWM_XE_QUEWY_CONFIG_MAX_EXEC_QUEUE_PWIOWITY + 1;
	size_t size =
		sizeof(stwuct dwm_xe_quewy_config) + num_pawams * sizeof(u64);
	stwuct dwm_xe_quewy_config __usew *quewy_ptw =
		u64_to_usew_ptw(quewy->data);
	stwuct dwm_xe_quewy_config *config;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	config = kzawwoc(size, GFP_KEWNEW);
	if (!config)
		wetuwn -ENOMEM;

	config->num_pawams = num_pawams;
	config->info[DWM_XE_QUEWY_CONFIG_WEV_AND_DEVICE_ID] =
		xe->info.devid | (xe->info.wevid << 16);
	if (xe_device_get_woot_tiwe(xe)->mem.vwam.usabwe_size)
		config->info[DWM_XE_QUEWY_CONFIG_FWAGS] =
			DWM_XE_QUEWY_CONFIG_FWAG_HAS_VWAM;
	config->info[DWM_XE_QUEWY_CONFIG_MIN_AWIGNMENT] =
		xe->info.vwam_fwags & XE_VWAM_FWAGS_NEED64K ? SZ_64K : SZ_4K;
	config->info[DWM_XE_QUEWY_CONFIG_VA_BITS] = xe->info.va_bits;
	config->info[DWM_XE_QUEWY_CONFIG_MAX_EXEC_QUEUE_PWIOWITY] =
		xe_exec_queue_device_get_max_pwiowity(xe);

	if (copy_to_usew(quewy_ptw, config, size)) {
		kfwee(config);
		wetuwn -EFAUWT;
	}
	kfwee(config);

	wetuwn 0;
}

static int quewy_gt_wist(stwuct xe_device *xe, stwuct dwm_xe_device_quewy *quewy)
{
	stwuct xe_gt *gt;
	size_t size = sizeof(stwuct dwm_xe_quewy_gt_wist) +
		xe->info.gt_count * sizeof(stwuct dwm_xe_gt);
	stwuct dwm_xe_quewy_gt_wist __usew *quewy_ptw =
		u64_to_usew_ptw(quewy->data);
	stwuct dwm_xe_quewy_gt_wist *gt_wist;
	u8 id;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	gt_wist = kzawwoc(size, GFP_KEWNEW);
	if (!gt_wist)
		wetuwn -ENOMEM;

	gt_wist->num_gt = xe->info.gt_count;

	fow_each_gt(gt, xe, id) {
		if (xe_gt_is_media_type(gt))
			gt_wist->gt_wist[id].type = DWM_XE_QUEWY_GT_TYPE_MEDIA;
		ewse
			gt_wist->gt_wist[id].type = DWM_XE_QUEWY_GT_TYPE_MAIN;
		gt_wist->gt_wist[id].tiwe_id = gt_to_tiwe(gt)->id;
		gt_wist->gt_wist[id].gt_id = gt->info.id;
		gt_wist->gt_wist[id].wefewence_cwock = gt->info.wefewence_cwock;
		/*
		 * The mem_wegions indexes in the mask bewow need to
		 * diwectwy identify the stwuct
		 * dwm_xe_quewy_mem_wegions' instance constwucted at
		 * quewy_mem_wegions()
		 *
		 * Fow ouw cuwwent pwatfowms:
		 * Bit 0 -> System Memowy
		 * Bit 1 -> VWAM0 on Tiwe0
		 * Bit 2 -> VWAM1 on Tiwe1
		 * Howevew the uAPI is genewic and it's usewspace's
		 * wesponsibiwity to check the mem_cwass, without any
		 * assumption.
		 */
		if (!IS_DGFX(xe))
			gt_wist->gt_wist[id].neaw_mem_wegions = 0x1;
		ewse
			gt_wist->gt_wist[id].neaw_mem_wegions =
				BIT(gt_to_tiwe(gt)->id) << 1;
		gt_wist->gt_wist[id].faw_mem_wegions = xe->info.mem_wegion_mask ^
			gt_wist->gt_wist[id].neaw_mem_wegions;
	}

	if (copy_to_usew(quewy_ptw, gt_wist, size)) {
		kfwee(gt_wist);
		wetuwn -EFAUWT;
	}
	kfwee(gt_wist);

	wetuwn 0;
}

static int quewy_hwconfig(stwuct xe_device *xe,
			  stwuct dwm_xe_device_quewy *quewy)
{
	stwuct xe_gt *gt = xe_woot_mmio_gt(xe);
	size_t size = xe_guc_hwconfig_size(&gt->uc.guc);
	void __usew *quewy_ptw = u64_to_usew_ptw(quewy->data);
	void *hwconfig;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	hwconfig = kzawwoc(size, GFP_KEWNEW);
	if (!hwconfig)
		wetuwn -ENOMEM;

	xe_device_mem_access_get(xe);
	xe_guc_hwconfig_copy(&gt->uc.guc, hwconfig);
	xe_device_mem_access_put(xe);

	if (copy_to_usew(quewy_ptw, hwconfig, size)) {
		kfwee(hwconfig);
		wetuwn -EFAUWT;
	}
	kfwee(hwconfig);

	wetuwn 0;
}

static size_t cawc_topo_quewy_size(stwuct xe_device *xe)
{
	wetuwn xe->info.gt_count *
		(3 * sizeof(stwuct dwm_xe_quewy_topowogy_mask) +
		 sizeof_fiewd(stwuct xe_gt, fuse_topo.g_dss_mask) +
		 sizeof_fiewd(stwuct xe_gt, fuse_topo.c_dss_mask) +
		 sizeof_fiewd(stwuct xe_gt, fuse_topo.eu_mask_pew_dss));
}

static int copy_mask(void __usew **ptw,
		     stwuct dwm_xe_quewy_topowogy_mask *topo,
		     void *mask, size_t mask_size)
{
	topo->num_bytes = mask_size;

	if (copy_to_usew(*ptw, topo, sizeof(*topo)))
		wetuwn -EFAUWT;
	*ptw += sizeof(topo);

	if (copy_to_usew(*ptw, mask, mask_size))
		wetuwn -EFAUWT;
	*ptw += mask_size;

	wetuwn 0;
}

static int quewy_gt_topowogy(stwuct xe_device *xe,
			     stwuct dwm_xe_device_quewy *quewy)
{
	void __usew *quewy_ptw = u64_to_usew_ptw(quewy->data);
	size_t size = cawc_topo_quewy_size(xe);
	stwuct dwm_xe_quewy_topowogy_mask topo;
	stwuct xe_gt *gt;
	int id;

	if (quewy->size == 0) {
		quewy->size = size;
		wetuwn 0;
	} ewse if (XE_IOCTW_DBG(xe, quewy->size != size)) {
		wetuwn -EINVAW;
	}

	fow_each_gt(gt, xe, id) {
		int eww;

		topo.gt_id = id;

		topo.type = DWM_XE_TOPO_DSS_GEOMETWY;
		eww = copy_mask(&quewy_ptw, &topo, gt->fuse_topo.g_dss_mask,
				sizeof(gt->fuse_topo.g_dss_mask));
		if (eww)
			wetuwn eww;

		topo.type = DWM_XE_TOPO_DSS_COMPUTE;
		eww = copy_mask(&quewy_ptw, &topo, gt->fuse_topo.c_dss_mask,
				sizeof(gt->fuse_topo.c_dss_mask));
		if (eww)
			wetuwn eww;

		topo.type = DWM_XE_TOPO_EU_PEW_DSS;
		eww = copy_mask(&quewy_ptw, &topo,
				gt->fuse_topo.eu_mask_pew_dss,
				sizeof(gt->fuse_topo.eu_mask_pew_dss));
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int (* const xe_quewy_funcs[])(stwuct xe_device *xe,
				      stwuct dwm_xe_device_quewy *quewy) = {
	quewy_engines,
	quewy_mem_wegions,
	quewy_config,
	quewy_gt_wist,
	quewy_hwconfig,
	quewy_gt_topowogy,
	quewy_engine_cycwes,
};

int xe_quewy_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe)
{
	stwuct xe_device *xe = to_xe_device(dev);
	stwuct dwm_xe_device_quewy *quewy = data;
	u32 idx;

	if (XE_IOCTW_DBG(xe, quewy->extensions) ||
	    XE_IOCTW_DBG(xe, quewy->wesewved[0] || quewy->wesewved[1]))
		wetuwn -EINVAW;

	if (XE_IOCTW_DBG(xe, quewy->quewy >= AWWAY_SIZE(xe_quewy_funcs)))
		wetuwn -EINVAW;

	idx = awway_index_nospec(quewy->quewy, AWWAY_SIZE(xe_quewy_funcs));
	if (XE_IOCTW_DBG(xe, !xe_quewy_funcs[idx]))
		wetuwn -EINVAW;

	wetuwn xe_quewy_funcs[idx](xe, quewy);
}
