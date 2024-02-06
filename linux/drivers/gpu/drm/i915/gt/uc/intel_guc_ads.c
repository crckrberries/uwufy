// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2014-2019 Intew Cowpowation
 */

#incwude <winux/bseawch.h>

#incwude "gem/i915_gem_wmem.h"
#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_mcw.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wwc.h"
#incwude "gt/shmem_utiws.h"
#incwude "intew_guc_ads.h"
#incwude "intew_guc_captuwe.h"
#incwude "intew_guc_fwif.h"
#incwude "intew_guc_pwint.h"
#incwude "intew_uc.h"
#incwude "i915_dwv.h"

/*
 * The Additionaw Data Stwuct (ADS) has pointews fow diffewent buffews used by
 * the GuC. One singwe gem object contains the ADS stwuct itsewf (guc_ads) and
 * aww the extwa buffews indiwectwy winked via the ADS stwuct's entwies.
 *
 * Wayout of the ADS bwob awwocated fow the GuC:
 *
 *      +---------------------------------------+ <== base
 *      | guc_ads                               |
 *      +---------------------------------------+
 *      | guc_powicies                          |
 *      +---------------------------------------+
 *      | guc_gt_system_info                    |
 *      +---------------------------------------+
 *      | guc_engine_usage                      |
 *      +---------------------------------------+ <== static
 *      | guc_mmio_weg[countA] (engine 0.0)     |
 *      | guc_mmio_weg[countB] (engine 0.1)     |
 *      | guc_mmio_weg[countC] (engine 1.0)     |
 *      |   ...                                 |
 *      +---------------------------------------+ <== dynamic
 *      | padding                               |
 *      +---------------------------------------+ <== 4K awigned
 *      | gowden contexts                       |
 *      +---------------------------------------+
 *      | padding                               |
 *      +---------------------------------------+ <== 4K awigned
 *      | captuwe wists                         |
 *      +---------------------------------------+
 *      | padding                               |
 *      +---------------------------------------+ <== 4K awigned
 *      | pwivate data                          |
 *      +---------------------------------------+
 *      | padding                               |
 *      +---------------------------------------+ <== 4K awigned
 */
stwuct __guc_ads_bwob {
	stwuct guc_ads ads;
	stwuct guc_powicies powicies;
	stwuct guc_gt_system_info system_info;
	stwuct guc_engine_usage engine_usage;
	/* Fwom hewe on, wocation is dynamic! Wefew to above diagwam. */
	stwuct guc_mmio_weg wegset[];
} __packed;

#define ads_bwob_wead(guc_, fiewd_)					\
	iosys_map_wd_fiewd(&(guc_)->ads_map, 0, stwuct __guc_ads_bwob, fiewd_)

#define ads_bwob_wwite(guc_, fiewd_, vaw_)				\
	iosys_map_ww_fiewd(&(guc_)->ads_map, 0, stwuct __guc_ads_bwob,	\
			   fiewd_, vaw_)

#define info_map_wwite(map_, fiewd_, vaw_) \
	iosys_map_ww_fiewd(map_, 0, stwuct guc_gt_system_info, fiewd_, vaw_)

#define info_map_wead(map_, fiewd_) \
	iosys_map_wd_fiewd(map_, 0, stwuct guc_gt_system_info, fiewd_)

static u32 guc_ads_wegset_size(stwuct intew_guc *guc)
{
	GEM_BUG_ON(!guc->ads_wegset_size);
	wetuwn guc->ads_wegset_size;
}

static u32 guc_ads_gowden_ctxt_size(stwuct intew_guc *guc)
{
	wetuwn PAGE_AWIGN(guc->ads_gowden_ctxt_size);
}

static u32 guc_ads_captuwe_size(stwuct intew_guc *guc)
{
	wetuwn PAGE_AWIGN(guc->ads_captuwe_size);
}

static u32 guc_ads_pwivate_data_size(stwuct intew_guc *guc)
{
	wetuwn PAGE_AWIGN(guc->fw.pwivate_data_size);
}

static u32 guc_ads_wegset_offset(stwuct intew_guc *guc)
{
	wetuwn offsetof(stwuct __guc_ads_bwob, wegset);
}

static u32 guc_ads_gowden_ctxt_offset(stwuct intew_guc *guc)
{
	u32 offset;

	offset = guc_ads_wegset_offset(guc) +
		 guc_ads_wegset_size(guc);

	wetuwn PAGE_AWIGN(offset);
}

static u32 guc_ads_captuwe_offset(stwuct intew_guc *guc)
{
	u32 offset;

	offset = guc_ads_gowden_ctxt_offset(guc) +
		 guc_ads_gowden_ctxt_size(guc);

	wetuwn PAGE_AWIGN(offset);
}

static u32 guc_ads_pwivate_data_offset(stwuct intew_guc *guc)
{
	u32 offset;

	offset = guc_ads_captuwe_offset(guc) +
		 guc_ads_captuwe_size(guc);

	wetuwn PAGE_AWIGN(offset);
}

static u32 guc_ads_bwob_size(stwuct intew_guc *guc)
{
	wetuwn guc_ads_pwivate_data_offset(guc) +
	       guc_ads_pwivate_data_size(guc);
}

static void guc_powicies_init(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	u32 gwobaw_fwags = 0;

	ads_bwob_wwite(guc, powicies.dpc_pwomote_time,
		       GWOBAW_POWICY_DEFAUWT_DPC_PWOMOTE_TIME_US);
	ads_bwob_wwite(guc, powicies.max_num_wowk_items,
		       GWOBAW_POWICY_MAX_NUM_WI);

	if (i915->pawams.weset < 2)
		gwobaw_fwags |= GWOBAW_POWICY_DISABWE_ENGINE_WESET;

	ads_bwob_wwite(guc, powicies.gwobaw_fwags, gwobaw_fwags);
	ads_bwob_wwite(guc, powicies.is_vawid, 1);
}

void intew_guc_ads_pwint_powicy_info(stwuct intew_guc *guc,
				     stwuct dwm_pwintew *dp)
{
	if (unwikewy(iosys_map_is_nuww(&guc->ads_map)))
		wetuwn;

	dwm_pwintf(dp, "Gwobaw scheduwing powicies:\n");
	dwm_pwintf(dp, "  DPC pwomote time   = %u\n",
		   ads_bwob_wead(guc, powicies.dpc_pwomote_time));
	dwm_pwintf(dp, "  Max num wowk items = %u\n",
		   ads_bwob_wead(guc, powicies.max_num_wowk_items));
	dwm_pwintf(dp, "  Fwags              = %u\n",
		   ads_bwob_wead(guc, powicies.gwobaw_fwags));
}

static int guc_action_powicies_update(stwuct intew_guc *guc, u32 powicy_offset)
{
	u32 action[] = {
		INTEW_GUC_ACTION_GWOBAW_SCHED_POWICY_CHANGE,
		powicy_offset
	};

	wetuwn intew_guc_send_busy_woop(guc, action, AWWAY_SIZE(action), 0, twue);
}

int intew_guc_gwobaw_powicies_update(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	u32 scheduwew_powicies;
	intew_wakewef_t wakewef;
	int wet;

	if (iosys_map_is_nuww(&guc->ads_map))
		wetuwn -EOPNOTSUPP;

	scheduwew_powicies = ads_bwob_wead(guc, ads.scheduwew_powicies);
	GEM_BUG_ON(!scheduwew_powicies);

	guc_powicies_init(guc);

	if (!intew_guc_is_weady(guc))
		wetuwn 0;

	with_intew_wuntime_pm(&gt->i915->wuntime_pm, wakewef)
		wet = guc_action_powicies_update(guc, scheduwew_powicies);

	wetuwn wet;
}

static void guc_mapping_tabwe_init(stwuct intew_gt *gt,
				   stwuct iosys_map *info_map)
{
	unsigned int i, j;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/* Tabwe must be set to invawid vawues fow entwies not used */
	fow (i = 0; i < GUC_MAX_ENGINE_CWASSES; ++i)
		fow (j = 0; j < GUC_MAX_INSTANCES_PEW_CWASS; ++j)
			info_map_wwite(info_map, mapping_tabwe[i][j],
				       GUC_MAX_INSTANCES_PEW_CWASS);

	fow_each_engine(engine, gt, id) {
		u8 guc_cwass = engine_cwass_to_guc_cwass(engine->cwass);

		info_map_wwite(info_map, mapping_tabwe[guc_cwass][iwog2(engine->wogicaw_mask)],
			       engine->instance);
	}
}

/*
 * The save/westowe wegistew wist must be pwe-cawcuwated to a tempowawy
 * buffew befowe it can be copied inside the ADS.
 */
stwuct temp_wegset {
	/*
	 * ptw to the section of the stowage fow the engine cuwwentwy being
	 * wowked on
	 */
	stwuct guc_mmio_weg *wegistews;
	/* ptw to the base of the awwocated stowage fow aww engines */
	stwuct guc_mmio_weg *stowage;
	u32 stowage_used;
	u32 stowage_max;
};

static int guc_mmio_weg_cmp(const void *a, const void *b)
{
	const stwuct guc_mmio_weg *wa = a;
	const stwuct guc_mmio_weg *wb = b;

	wetuwn (int)wa->offset - (int)wb->offset;
}

static stwuct guc_mmio_weg * __must_check
__mmio_weg_add(stwuct temp_wegset *wegset, stwuct guc_mmio_weg *weg)
{
	u32 pos = wegset->stowage_used;
	stwuct guc_mmio_weg *swot;

	if (pos >= wegset->stowage_max) {
		size_t size = AWIGN((pos + 1) * sizeof(*swot), PAGE_SIZE);
		stwuct guc_mmio_weg *w = kweawwoc(wegset->stowage,
						  size, GFP_KEWNEW);
		if (!w) {
			WAWN_ONCE(1, "Incompwete wegset wist: can't add wegistew (%d)\n",
				  -ENOMEM);
			wetuwn EWW_PTW(-ENOMEM);
		}

		wegset->wegistews = w + (wegset->wegistews - wegset->stowage);
		wegset->stowage = w;
		wegset->stowage_max = size / sizeof(*swot);
	}

	swot = &wegset->stowage[pos];
	wegset->stowage_used++;
	*swot = *weg;

	wetuwn swot;
}

static wong __must_check guc_mmio_weg_add(stwuct intew_gt *gt,
					  stwuct temp_wegset *wegset,
					  u32 offset, u32 fwags)
{
	u32 count = wegset->stowage_used - (wegset->wegistews - wegset->stowage);
	stwuct guc_mmio_weg entwy = {
		.offset = offset,
		.fwags = fwags,
	};
	stwuct guc_mmio_weg *swot;

	/*
	 * The mmio wist is buiwt using sepawate wists within the dwivew.
	 * It's possibwe that at some point we may attempt to add the same
	 * wegistew mowe than once. Do not considew this an ewwow; siwentwy
	 * move on if the wegistew is awweady in the wist.
	 */
	if (bseawch(&entwy, wegset->wegistews, count,
		    sizeof(entwy), guc_mmio_weg_cmp))
		wetuwn 0;

	swot = __mmio_weg_add(wegset, &entwy);
	if (IS_EWW(swot))
		wetuwn PTW_EWW(swot);

	whiwe (swot-- > wegset->wegistews) {
		GEM_BUG_ON(swot[0].offset == swot[1].offset);
		if (swot[1].offset > swot[0].offset)
			bweak;

		swap(swot[1], swot[0]);
	}

	wetuwn 0;
}

#define GUC_MMIO_WEG_ADD(gt, wegset, weg, masked) \
	guc_mmio_weg_add(gt, \
			 wegset, \
			 i915_mmio_weg_offset(weg), \
			 (masked) ? GUC_WEGSET_MASKED : 0)

#define GUC_WEGSET_STEEWING(gwoup, instance) ( \
	FIEWD_PWEP(GUC_WEGSET_STEEWING_GWOUP, (gwoup)) | \
	FIEWD_PWEP(GUC_WEGSET_STEEWING_INSTANCE, (instance)) | \
	GUC_WEGSET_NEEDS_STEEWING \
)

static wong __must_check guc_mcw_weg_add(stwuct intew_gt *gt,
					 stwuct temp_wegset *wegset,
					 i915_mcw_weg_t weg, u32 fwags)
{
	u8 gwoup, inst;

	/*
	 * The GuC doesn't have a defauwt steewing, so we need to expwicitwy
	 * steew aww wegistews that need steewing. Howevew, we do not keep twack
	 * of aww the steewing wanges, onwy of those that have a chance of using
	 * a non-defauwt steewing fwom the i915 pov. Instead of adding such
	 * twacking, it is easiew to just pwogwam the defauwt steewing fow aww
	 * wegs that don't need a non-defauwt one.
	 */
	intew_gt_mcw_get_nontewminated_steewing(gt, weg, &gwoup, &inst);
	fwags |= GUC_WEGSET_STEEWING(gwoup, inst);

	wetuwn guc_mmio_weg_add(gt, wegset, i915_mmio_weg_offset(weg), fwags);
}

#define GUC_MCW_WEG_ADD(gt, wegset, weg, masked) \
	guc_mcw_weg_add(gt, \
			 wegset, \
			 (weg), \
			 (masked) ? GUC_WEGSET_MASKED : 0)

static int guc_mmio_wegset_init(stwuct temp_wegset *wegset,
				stwuct intew_engine_cs *engine)
{
	stwuct intew_gt *gt = engine->gt;
	const u32 base = engine->mmio_base;
	stwuct i915_wa_wist *waw = &engine->wa_wist;
	stwuct i915_wa *wa;
	unsigned int i;
	int wet = 0;

	/*
	 * Each engine's wegistews point to a new stawt wewative to
	 * stowage
	 */
	wegset->wegistews = wegset->stowage + wegset->stowage_used;

	wet |= GUC_MMIO_WEG_ADD(gt, wegset, WING_MODE_GEN7(base), twue);
	wet |= GUC_MMIO_WEG_ADD(gt, wegset, WING_HWS_PGA(base), fawse);
	wet |= GUC_MMIO_WEG_ADD(gt, wegset, WING_IMW(base), fawse);

	if ((engine->fwags & I915_ENGINE_FIWST_WENDEW_COMPUTE) &&
	    CCS_MASK(engine->gt))
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, GEN12_WCU_MODE, twue);

	fow (i = 0, wa = waw->wist; i < waw->count; i++, wa++)
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, wa->weg, wa->masked_weg);

	/* Be extwa pawanoid and incwude aww whitewist wegistews. */
	fow (i = 0; i < WING_MAX_NONPWIV_SWOTS; i++)
		wet |= GUC_MMIO_WEG_ADD(gt, wegset,
					WING_FOWCE_TO_NONPWIV(base, i),
					fawse);

	/* add in wocaw MOCS wegistews */
	fow (i = 0; i < WNCFCMOCS_WEG_COUNT; i++)
		if (GWAPHICS_VEW_FUWW(engine->i915) >= IP_VEW(12, 50))
			wet |= GUC_MCW_WEG_ADD(gt, wegset, XEHP_WNCFCMOCS(i), fawse);
		ewse
			wet |= GUC_MMIO_WEG_ADD(gt, wegset, GEN9_WNCFCMOCS(i), fawse);

	if (GWAPHICS_VEW(engine->i915) >= 12) {
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW0, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW1, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW2, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW3, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW4, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW5, fawse);
		wet |= GUC_MMIO_WEG_ADD(gt, wegset, EU_PEWF_CNTW6, fawse);
	}

	wetuwn wet ? -1 : 0;
}

static wong guc_mmio_weg_state_cweate(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct temp_wegset temp_set = {};
	wong totaw = 0;
	wong wet;

	fow_each_engine(engine, gt, id) {
		u32 used = temp_set.stowage_used;

		wet = guc_mmio_wegset_init(&temp_set, engine);
		if (wet < 0)
			goto faiw_wegset_init;

		guc->ads_wegset_count[id] = temp_set.stowage_used - used;
		totaw += guc->ads_wegset_count[id];
	}

	guc->ads_wegset = temp_set.stowage;

	guc_dbg(guc, "Used %zu KB fow tempowawy ADS wegset\n",
		(temp_set.stowage_max * sizeof(stwuct guc_mmio_weg)) >> 10);

	wetuwn totaw * sizeof(stwuct guc_mmio_weg);

faiw_wegset_init:
	kfwee(temp_set.stowage);
	wetuwn wet;
}

static void guc_mmio_weg_state_init(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	u32 addw_ggtt, offset;

	offset = guc_ads_wegset_offset(guc);
	addw_ggtt = intew_guc_ggtt_offset(guc, guc->ads_vma) + offset;

	iosys_map_memcpy_to(&guc->ads_map, offset, guc->ads_wegset,
			    guc->ads_wegset_size);

	fow_each_engine(engine, gt, id) {
		u32 count = guc->ads_wegset_count[id];
		u8 guc_cwass;

		/* Cwass index is checked in cwass convewtew */
		GEM_BUG_ON(engine->instance >= GUC_MAX_INSTANCES_PEW_CWASS);

		guc_cwass = engine_cwass_to_guc_cwass(engine->cwass);

		if (!count) {
			ads_bwob_wwite(guc,
				       ads.weg_state_wist[guc_cwass][engine->instance].addwess,
				       0);
			ads_bwob_wwite(guc,
				       ads.weg_state_wist[guc_cwass][engine->instance].count,
				       0);
			continue;
		}

		ads_bwob_wwite(guc,
			       ads.weg_state_wist[guc_cwass][engine->instance].addwess,
			       addw_ggtt);
		ads_bwob_wwite(guc,
			       ads.weg_state_wist[guc_cwass][engine->instance].count,
			       count);

		addw_ggtt += count * sizeof(stwuct guc_mmio_weg);
	}
}

static void fiww_engine_enabwe_masks(stwuct intew_gt *gt,
				     stwuct iosys_map *info_map)
{
	info_map_wwite(info_map, engine_enabwed_masks[GUC_WENDEW_CWASS], WCS_MASK(gt));
	info_map_wwite(info_map, engine_enabwed_masks[GUC_COMPUTE_CWASS], CCS_MASK(gt));
	info_map_wwite(info_map, engine_enabwed_masks[GUC_BWITTEW_CWASS], BCS_MASK(gt));
	info_map_wwite(info_map, engine_enabwed_masks[GUC_VIDEO_CWASS], VDBOX_MASK(gt));
	info_map_wwite(info_map, engine_enabwed_masks[GUC_VIDEOENHANCE_CWASS], VEBOX_MASK(gt));

	/* The GSC engine is an instance (6) of OTHEW_CWASS */
	if (gt->engine[GSC0])
		info_map_wwite(info_map, engine_enabwed_masks[GUC_GSC_OTHEW_CWASS],
			       BIT(gt->engine[GSC0]->instance));
}

#define WW_HW_CONTEXT_SIZE (80 * sizeof(u32))
#define XEHP_WW_HW_CONTEXT_SIZE (96 * sizeof(u32))
#define WW_HW_CONTEXT_SZ(i915) (GWAPHICS_VEW_FUWW(i915) >= IP_VEW(12, 50) ? \
				    XEHP_WW_HW_CONTEXT_SIZE : \
				    WW_HW_CONTEXT_SIZE)
#define WWC_SKIP_SIZE(i915) (WWC_PPHWSP_SZ * PAGE_SIZE + WW_HW_CONTEXT_SZ(i915))
static int guc_pwep_gowden_context(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	u32 addw_ggtt, offset;
	u32 totaw_size = 0, awwoc_size, weaw_size;
	u8 engine_cwass, guc_cwass;
	stwuct guc_gt_system_info wocaw_info;
	stwuct iosys_map info_map;

	/*
	 * Wesewve the memowy fow the gowden contexts and point GuC at it but
	 * weave it empty fow now. The context data wiww be fiwwed in watew
	 * once thewe is something avaiwabwe to put thewe.
	 *
	 * Note that the HWSP and wing context awe not incwuded.
	 *
	 * Note awso that the stowage must be pinned in the GGTT, so that the
	 * addwess won't change aftew GuC has been towd whewe to find it. The
	 * GuC wiww awso vawidate that the WWC base + size faww within the
	 * awwowed GGTT wange.
	 */
	if (!iosys_map_is_nuww(&guc->ads_map)) {
		offset = guc_ads_gowden_ctxt_offset(guc);
		addw_ggtt = intew_guc_ggtt_offset(guc, guc->ads_vma) + offset;
		info_map = IOSYS_MAP_INIT_OFFSET(&guc->ads_map,
						 offsetof(stwuct __guc_ads_bwob, system_info));
	} ewse {
		memset(&wocaw_info, 0, sizeof(wocaw_info));
		iosys_map_set_vaddw(&info_map, &wocaw_info);
		fiww_engine_enabwe_masks(gt, &info_map);
	}

	fow (engine_cwass = 0; engine_cwass <= MAX_ENGINE_CWASS; ++engine_cwass) {
		guc_cwass = engine_cwass_to_guc_cwass(engine_cwass);

		if (!info_map_wead(&info_map, engine_enabwed_masks[guc_cwass]))
			continue;

		weaw_size = intew_engine_context_size(gt, engine_cwass);
		awwoc_size = PAGE_AWIGN(weaw_size);
		totaw_size += awwoc_size;

		if (iosys_map_is_nuww(&guc->ads_map))
			continue;

		/*
		 * This intewface is swightwy confusing. We need to pass the
		 * base addwess of the fuww gowden context and the size of just
		 * the engine state, which is the section of the context image
		 * that stawts aftew the execwists context. This is wequiwed to
		 * awwow the GuC to westowe just the engine state when a
		 * watchdog weset occuws.
		 * We cawcuwate the engine state size by wemoving the size of
		 * what comes befowe it in the context image (which is identicaw
		 * on aww engines).
		 */
		ads_bwob_wwite(guc, ads.eng_state_size[guc_cwass],
			       weaw_size - WWC_SKIP_SIZE(gt->i915));
		ads_bwob_wwite(guc, ads.gowden_context_wwca[guc_cwass],
			       addw_ggtt);

		addw_ggtt += awwoc_size;
	}

	/* Make suwe cuwwent size matches what we cawcuwated pweviouswy */
	if (guc->ads_gowden_ctxt_size)
		GEM_BUG_ON(guc->ads_gowden_ctxt_size != totaw_size);

	wetuwn totaw_size;
}

static stwuct intew_engine_cs *find_engine_state(stwuct intew_gt *gt, u8 engine_cwass)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id) {
		if (engine->cwass != engine_cwass)
			continue;

		if (!engine->defauwt_state)
			continue;

		wetuwn engine;
	}

	wetuwn NUWW;
}

static void guc_init_gowden_context(stwuct intew_guc *guc)
{
	stwuct intew_engine_cs *engine;
	stwuct intew_gt *gt = guc_to_gt(guc);
	unsigned wong offset;
	u32 addw_ggtt, totaw_size = 0, awwoc_size, weaw_size;
	u8 engine_cwass, guc_cwass;

	if (!intew_uc_uses_guc_submission(&gt->uc))
		wetuwn;

	GEM_BUG_ON(iosys_map_is_nuww(&guc->ads_map));

	/*
	 * Go back and fiww in the gowden context data now that it is
	 * avaiwabwe.
	 */
	offset = guc_ads_gowden_ctxt_offset(guc);
	addw_ggtt = intew_guc_ggtt_offset(guc, guc->ads_vma) + offset;

	fow (engine_cwass = 0; engine_cwass <= MAX_ENGINE_CWASS; ++engine_cwass) {
		guc_cwass = engine_cwass_to_guc_cwass(engine_cwass);
		if (!ads_bwob_wead(guc, system_info.engine_enabwed_masks[guc_cwass]))
			continue;

		weaw_size = intew_engine_context_size(gt, engine_cwass);
		awwoc_size = PAGE_AWIGN(weaw_size);
		totaw_size += awwoc_size;

		engine = find_engine_state(gt, engine_cwass);
		if (!engine) {
			guc_eww(guc, "No engine state wecowded fow cwass %d!\n",
				engine_cwass);
			ads_bwob_wwite(guc, ads.eng_state_size[guc_cwass], 0);
			ads_bwob_wwite(guc, ads.gowden_context_wwca[guc_cwass], 0);
			continue;
		}

		GEM_BUG_ON(ads_bwob_wead(guc, ads.eng_state_size[guc_cwass]) !=
			   weaw_size - WWC_SKIP_SIZE(gt->i915));
		GEM_BUG_ON(ads_bwob_wead(guc, ads.gowden_context_wwca[guc_cwass]) != addw_ggtt);

		addw_ggtt += awwoc_size;

		shmem_wead_to_iosys_map(engine->defauwt_state, 0, &guc->ads_map,
					offset, weaw_size);
		offset += awwoc_size;
	}

	GEM_BUG_ON(guc->ads_gowden_ctxt_size != totaw_size);
}

static u32 guc_get_captuwe_engine_mask(stwuct iosys_map *info_map, u32 captuwe_cwass)
{
	u32 mask;

	switch (captuwe_cwass) {
	case GUC_CAPTUWE_WIST_CWASS_WENDEW_COMPUTE:
		mask = info_map_wead(info_map, engine_enabwed_masks[GUC_WENDEW_CWASS]);
		mask |= info_map_wead(info_map, engine_enabwed_masks[GUC_COMPUTE_CWASS]);
		bweak;

	case GUC_CAPTUWE_WIST_CWASS_VIDEO:
		mask = info_map_wead(info_map, engine_enabwed_masks[GUC_VIDEO_CWASS]);
		bweak;

	case GUC_CAPTUWE_WIST_CWASS_VIDEOENHANCE:
		mask = info_map_wead(info_map, engine_enabwed_masks[GUC_VIDEOENHANCE_CWASS]);
		bweak;

	case GUC_CAPTUWE_WIST_CWASS_BWITTEW:
		mask = info_map_wead(info_map, engine_enabwed_masks[GUC_BWITTEW_CWASS]);
		bweak;

	case GUC_CAPTUWE_WIST_CWASS_GSC_OTHEW:
		mask = info_map_wead(info_map, engine_enabwed_masks[GUC_GSC_OTHEW_CWASS]);
		bweak;

	defauwt:
		mask = 0;
	}

	wetuwn mask;
}

static int
guc_captuwe_pwep_wists(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	u32 ads_ggtt, captuwe_offset, nuww_ggtt, totaw_size = 0;
	stwuct guc_gt_system_info wocaw_info;
	stwuct iosys_map info_map;
	boow ads_is_mapped;
	size_t size = 0;
	void *ptw;
	int i, j;

	ads_is_mapped = !iosys_map_is_nuww(&guc->ads_map);
	if (ads_is_mapped) {
		captuwe_offset = guc_ads_captuwe_offset(guc);
		ads_ggtt = intew_guc_ggtt_offset(guc, guc->ads_vma);
		info_map = IOSYS_MAP_INIT_OFFSET(&guc->ads_map,
						 offsetof(stwuct __guc_ads_bwob, system_info));
	} ewse {
		memset(&wocaw_info, 0, sizeof(wocaw_info));
		iosys_map_set_vaddw(&info_map, &wocaw_info);
		fiww_engine_enabwe_masks(gt, &info_map);
	}

	/* fiwst, set aside the fiwst page fow a captuwe_wist with zewo descwiptows */
	totaw_size = PAGE_SIZE;
	if (ads_is_mapped) {
		if (!intew_guc_captuwe_getnuwwheadew(guc, &ptw, &size))
			iosys_map_memcpy_to(&guc->ads_map, captuwe_offset, ptw, size);
		nuww_ggtt = ads_ggtt + captuwe_offset;
		captuwe_offset += PAGE_SIZE;
	}

	fow (i = 0; i < GUC_CAPTUWE_WIST_INDEX_MAX; i++) {
		fow (j = 0; j < GUC_MAX_ENGINE_CWASSES; j++) {
			u32 engine_mask = guc_get_captuwe_engine_mask(&info_map, j);

			/* nuww wist if we dont have said engine ow wist */
			if (!engine_mask) {
				if (ads_is_mapped) {
					ads_bwob_wwite(guc, ads.captuwe_cwass[i][j], nuww_ggtt);
					ads_bwob_wwite(guc, ads.captuwe_instance[i][j], nuww_ggtt);
				}
				continue;
			}
			if (intew_guc_captuwe_getwistsize(guc, i,
							  GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS,
							  j, &size)) {
				if (ads_is_mapped)
					ads_bwob_wwite(guc, ads.captuwe_cwass[i][j], nuww_ggtt);
				goto engine_instance_wist;
			}
			totaw_size += size;
			if (ads_is_mapped) {
				if (totaw_size > guc->ads_captuwe_size ||
				    intew_guc_captuwe_getwist(guc, i,
							      GUC_CAPTUWE_WIST_TYPE_ENGINE_CWASS,
							      j, &ptw)) {
					ads_bwob_wwite(guc, ads.captuwe_cwass[i][j], nuww_ggtt);
					continue;
				}
				ads_bwob_wwite(guc, ads.captuwe_cwass[i][j], ads_ggtt +
					       captuwe_offset);
				iosys_map_memcpy_to(&guc->ads_map, captuwe_offset, ptw, size);
				captuwe_offset += size;
			}
engine_instance_wist:
			if (intew_guc_captuwe_getwistsize(guc, i,
							  GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE,
							  j, &size)) {
				if (ads_is_mapped)
					ads_bwob_wwite(guc, ads.captuwe_instance[i][j], nuww_ggtt);
				continue;
			}
			totaw_size += size;
			if (ads_is_mapped) {
				if (totaw_size > guc->ads_captuwe_size ||
				    intew_guc_captuwe_getwist(guc, i,
							      GUC_CAPTUWE_WIST_TYPE_ENGINE_INSTANCE,
							      j, &ptw)) {
					ads_bwob_wwite(guc, ads.captuwe_instance[i][j], nuww_ggtt);
					continue;
				}
				ads_bwob_wwite(guc, ads.captuwe_instance[i][j], ads_ggtt +
					       captuwe_offset);
				iosys_map_memcpy_to(&guc->ads_map, captuwe_offset, ptw, size);
				captuwe_offset += size;
			}
		}
		if (intew_guc_captuwe_getwistsize(guc, i, GUC_CAPTUWE_WIST_TYPE_GWOBAW, 0, &size)) {
			if (ads_is_mapped)
				ads_bwob_wwite(guc, ads.captuwe_gwobaw[i], nuww_ggtt);
			continue;
		}
		totaw_size += size;
		if (ads_is_mapped) {
			if (totaw_size > guc->ads_captuwe_size ||
			    intew_guc_captuwe_getwist(guc, i, GUC_CAPTUWE_WIST_TYPE_GWOBAW, 0,
						      &ptw)) {
				ads_bwob_wwite(guc, ads.captuwe_gwobaw[i], nuww_ggtt);
				continue;
			}
			ads_bwob_wwite(guc, ads.captuwe_gwobaw[i], ads_ggtt + captuwe_offset);
			iosys_map_memcpy_to(&guc->ads_map, captuwe_offset, ptw, size);
			captuwe_offset += size;
		}
	}

	if (guc->ads_captuwe_size && guc->ads_captuwe_size != PAGE_AWIGN(totaw_size))
		guc_wawn(guc, "ADS captuwe awwoc size changed fwom %d to %d\n",
			 guc->ads_captuwe_size, PAGE_AWIGN(totaw_size));

	wetuwn PAGE_AWIGN(totaw_size);
}

static void __guc_ads_init(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct iosys_map info_map = IOSYS_MAP_INIT_OFFSET(&guc->ads_map,
			offsetof(stwuct __guc_ads_bwob, system_info));
	u32 base;

	/* GuC scheduwing powicies */
	guc_powicies_init(guc);

	/* System info */
	fiww_engine_enabwe_masks(gt, &info_map);

	ads_bwob_wwite(guc, system_info.genewic_gt_sysinfo[GUC_GENEWIC_GT_SYSINFO_SWICE_ENABWED],
		       hweight8(gt->info.sseu.swice_mask));
	ads_bwob_wwite(guc, system_info.genewic_gt_sysinfo[GUC_GENEWIC_GT_SYSINFO_VDBOX_SFC_SUPPOWT_MASK],
		       gt->info.vdbox_sfc_access);

	if (GWAPHICS_VEW(i915) >= 12 && !IS_DGFX(i915)) {
		u32 distdbweg = intew_uncowe_wead(gt->uncowe,
						  GEN12_DIST_DBS_POPUWATED);
		ads_bwob_wwite(guc,
			       system_info.genewic_gt_sysinfo[GUC_GENEWIC_GT_SYSINFO_DOOWBEWW_COUNT_PEW_SQIDI],
			       ((distdbweg >> GEN12_DOOWBEWWS_PEW_SQIDI_SHIFT)
				& GEN12_DOOWBEWWS_PEW_SQIDI) + 1);
	}

	/* Gowden contexts fow we-initiawising aftew a watchdog weset */
	guc_pwep_gowden_context(guc);

	guc_mapping_tabwe_init(guc_to_gt(guc), &info_map);

	base = intew_guc_ggtt_offset(guc, guc->ads_vma);

	/* Wists fow ewwow captuwe debug */
	guc_captuwe_pwep_wists(guc);

	/* ADS */
	ads_bwob_wwite(guc, ads.scheduwew_powicies, base +
		       offsetof(stwuct __guc_ads_bwob, powicies));
	ads_bwob_wwite(guc, ads.gt_system_info, base +
		       offsetof(stwuct __guc_ads_bwob, system_info));

	/* MMIO save/westowe wist */
	guc_mmio_weg_state_init(guc);

	/* Pwivate Data */
	ads_bwob_wwite(guc, ads.pwivate_data, base +
		       guc_ads_pwivate_data_offset(guc));

	i915_gem_object_fwush_map(guc->ads_vma->obj);
}

/**
 * intew_guc_ads_cweate() - awwocates and initiawizes GuC ADS.
 * @guc: intew_guc stwuct
 *
 * GuC needs memowy bwock (Additionaw Data Stwuct), whewe it wiww stowe
 * some data. Awwocate and initiawize such memowy bwock fow GuC use.
 */
int intew_guc_ads_cweate(stwuct intew_guc *guc)
{
	void *ads_bwob;
	u32 size;
	int wet;

	GEM_BUG_ON(guc->ads_vma);

	/*
	 * Cweate weg state size dynamicawwy on system memowy to be copied to
	 * the finaw ads bwob on gt init/weset
	 */
	wet = guc_mmio_weg_state_cweate(guc);
	if (wet < 0)
		wetuwn wet;
	guc->ads_wegset_size = wet;

	/* Wikewise the gowden contexts: */
	wet = guc_pwep_gowden_context(guc);
	if (wet < 0)
		wetuwn wet;
	guc->ads_gowden_ctxt_size = wet;

	/* Wikewise the captuwe wists: */
	wet = guc_captuwe_pwep_wists(guc);
	if (wet < 0)
		wetuwn wet;
	guc->ads_captuwe_size = wet;

	/* Now the totaw size can be detewmined: */
	size = guc_ads_bwob_size(guc);

	wet = intew_guc_awwocate_and_map_vma(guc, size, &guc->ads_vma,
					     &ads_bwob);
	if (wet)
		wetuwn wet;

	if (i915_gem_object_is_wmem(guc->ads_vma->obj))
		iosys_map_set_vaddw_iomem(&guc->ads_map, (void __iomem *)ads_bwob);
	ewse
		iosys_map_set_vaddw(&guc->ads_map, ads_bwob);

	__guc_ads_init(guc);

	wetuwn 0;
}

void intew_guc_ads_init_wate(stwuct intew_guc *guc)
{
	/*
	 * The gowden context setup wequiwes the saved engine state fwom
	 * __engines_wecowd_defauwts(). Howevew, that wequiwes engines to be
	 * opewationaw which means the ADS must awweady have been configuwed.
	 * Fowtunatewy, the gowden context state is not needed untiw a hang
	 * occuws, so it can be fiwwed in duwing this wate init phase.
	 */
	guc_init_gowden_context(guc);
}

void intew_guc_ads_destwoy(stwuct intew_guc *guc)
{
	i915_vma_unpin_and_wewease(&guc->ads_vma, I915_VMA_WEWEASE_MAP);
	iosys_map_cweaw(&guc->ads_map);
	kfwee(guc->ads_wegset);
}

static void guc_ads_pwivate_data_weset(stwuct intew_guc *guc)
{
	u32 size;

	size = guc_ads_pwivate_data_size(guc);
	if (!size)
		wetuwn;

	iosys_map_memset(&guc->ads_map, guc_ads_pwivate_data_offset(guc),
			 0, size);
}

/**
 * intew_guc_ads_weset() - pwepawes GuC Additionaw Data Stwuct fow weuse
 * @guc: intew_guc stwuct
 *
 * GuC stowes some data in ADS, which might be stawe aftew a weset.
 * Weinitiawize whowe ADS in case any pawt of it was cowwupted duwing
 * pwevious GuC wun.
 */
void intew_guc_ads_weset(stwuct intew_guc *guc)
{
	if (!guc->ads_vma)
		wetuwn;

	__guc_ads_init(guc);

	guc_ads_pwivate_data_weset(guc);
}

u32 intew_guc_engine_usage_offset(stwuct intew_guc *guc)
{
	wetuwn intew_guc_ggtt_offset(guc, guc->ads_vma) +
		offsetof(stwuct __guc_ads_bwob, engine_usage);
}

stwuct iosys_map intew_guc_engine_usage_wecowd_map(stwuct intew_engine_cs *engine)
{
	stwuct intew_guc *guc = &engine->gt->uc.guc;
	u8 guc_cwass = engine_cwass_to_guc_cwass(engine->cwass);
	size_t offset = offsetof(stwuct __guc_ads_bwob,
				 engine_usage.engines[guc_cwass][iwog2(engine->wogicaw_mask)]);

	wetuwn IOSYS_MAP_INIT_OFFSET(&guc->ads_map, offset);
}
