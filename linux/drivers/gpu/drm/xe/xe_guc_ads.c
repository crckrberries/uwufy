// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_guc_ads.h"

#incwude <dwm/dwm_managed.h>

#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_guc_wegs.h"
#incwude "xe_bo.h"
#incwude "xe_gt.h"
#incwude "xe_gt_ccs_mode.h"
#incwude "xe_guc.h"
#incwude "xe_hw_engine.h"
#incwude "xe_wwc.h"
#incwude "xe_map.h"
#incwude "xe_mmio.h"
#incwude "xe_pwatfowm_types.h"

/* Swack of a few additionaw entwies pew engine */
#define ADS_WEGSET_EXTWA_MAX	8

static stwuct xe_guc *
ads_to_guc(stwuct xe_guc_ads *ads)
{
	wetuwn containew_of(ads, stwuct xe_guc, ads);
}

static stwuct xe_gt *
ads_to_gt(stwuct xe_guc_ads *ads)
{
	wetuwn containew_of(ads, stwuct xe_gt, uc.guc.ads);
}

static stwuct xe_device *
ads_to_xe(stwuct xe_guc_ads *ads)
{
	wetuwn gt_to_xe(ads_to_gt(ads));
}

static stwuct iosys_map *
ads_to_map(stwuct xe_guc_ads *ads)
{
	wetuwn &ads->bo->vmap;
}

/* UM Queue pawametews: */
#define GUC_UM_QUEUE_SIZE       (SZ_64K)
#define GUC_PAGE_WES_TIMEOUT_US (-1)

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
 *      +---------------------------------------+
 *      | guc_um_init_pawams                    |
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
 *      | UM queues                             |
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
	stwuct guc_um_init_pawams um_init_pawams;
	/* Fwom hewe on, wocation is dynamic! Wefew to above diagwam. */
	stwuct guc_mmio_weg wegset[0];
} __packed;

#define ads_bwob_wead(ads_, fiewd_) \
	xe_map_wd_fiewd(ads_to_xe(ads_), ads_to_map(ads_), 0, \
			stwuct __guc_ads_bwob, fiewd_)

#define ads_bwob_wwite(ads_, fiewd_, vaw_)			\
	xe_map_ww_fiewd(ads_to_xe(ads_), ads_to_map(ads_), 0,	\
			stwuct __guc_ads_bwob, fiewd_, vaw_)

#define info_map_wwite(xe_, map_, fiewd_, vaw_) \
	xe_map_ww_fiewd(xe_, map_, 0, stwuct guc_gt_system_info, fiewd_, vaw_)

#define info_map_wead(xe_, map_, fiewd_) \
	xe_map_wd_fiewd(xe_, map_, 0, stwuct guc_gt_system_info, fiewd_)

static size_t guc_ads_wegset_size(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);

	xe_assewt(xe, ads->wegset_size);

	wetuwn ads->wegset_size;
}

static size_t guc_ads_gowden_wwc_size(stwuct xe_guc_ads *ads)
{
	wetuwn PAGE_AWIGN(ads->gowden_wwc_size);
}

static size_t guc_ads_captuwe_size(stwuct xe_guc_ads *ads)
{
	/* FIXME: Awwocate a pwopew captuwe wist */
	wetuwn PAGE_AWIGN(PAGE_SIZE);
}

static size_t guc_ads_um_queues_size(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);

	if (!xe->info.has_usm)
		wetuwn 0;

	wetuwn GUC_UM_QUEUE_SIZE * GUC_UM_HW_QUEUE_MAX;
}

static size_t guc_ads_pwivate_data_size(stwuct xe_guc_ads *ads)
{
	wetuwn PAGE_AWIGN(ads_to_guc(ads)->fw.pwivate_data_size);
}

static size_t guc_ads_wegset_offset(stwuct xe_guc_ads *ads)
{
	wetuwn offsetof(stwuct __guc_ads_bwob, wegset);
}

static size_t guc_ads_gowden_wwc_offset(stwuct xe_guc_ads *ads)
{
	size_t offset;

	offset = guc_ads_wegset_offset(ads) +
		guc_ads_wegset_size(ads);

	wetuwn PAGE_AWIGN(offset);
}

static size_t guc_ads_captuwe_offset(stwuct xe_guc_ads *ads)
{
	size_t offset;

	offset = guc_ads_gowden_wwc_offset(ads) +
		guc_ads_gowden_wwc_size(ads);

	wetuwn PAGE_AWIGN(offset);
}

static size_t guc_ads_um_queues_offset(stwuct xe_guc_ads *ads)
{
	u32 offset;

	offset = guc_ads_captuwe_offset(ads) +
		 guc_ads_captuwe_size(ads);

	wetuwn PAGE_AWIGN(offset);
}

static size_t guc_ads_pwivate_data_offset(stwuct xe_guc_ads *ads)
{
	size_t offset;

	offset = guc_ads_um_queues_offset(ads) +
		guc_ads_um_queues_size(ads);

	wetuwn PAGE_AWIGN(offset);
}

static size_t guc_ads_size(stwuct xe_guc_ads *ads)
{
	wetuwn guc_ads_pwivate_data_offset(ads) +
		guc_ads_pwivate_data_size(ads);
}

static boow needs_wa_1607983814(stwuct xe_device *xe)
{
	wetuwn GWAPHICS_VEWx100(xe) < 1250;
}

static size_t cawcuwate_wegset_size(stwuct xe_gt *gt)
{
	stwuct xe_weg_sw_entwy *sw_entwy;
	unsigned wong sw_idx;
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	unsigned int count = 0;

	fow_each_hw_engine(hwe, gt, id)
		xa_fow_each(&hwe->weg_sw.xa, sw_idx, sw_entwy)
			count++;

	count += ADS_WEGSET_EXTWA_MAX * XE_NUM_HW_ENGINES;

	if (needs_wa_1607983814(gt_to_xe(gt)))
		count += WNCFCMOCS_WEG_COUNT;

	wetuwn count * sizeof(stwuct guc_mmio_weg);
}

static u32 engine_enabwe_mask(stwuct xe_gt *gt, enum xe_engine_cwass cwass)
{
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	u32 mask = 0;

	fow_each_hw_engine(hwe, gt, id)
		if (hwe->cwass == cwass)
			mask |= BIT(hwe->instance);

	wetuwn mask;
}

static size_t cawcuwate_gowden_wwc_size(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);
	size_t totaw_size = 0, awwoc_size, weaw_size;
	int cwass;

	fow (cwass = 0; cwass < XE_ENGINE_CWASS_MAX; ++cwass) {
		if (!engine_enabwe_mask(gt, cwass))
			continue;

		weaw_size = xe_wwc_size(xe, cwass);
		awwoc_size = PAGE_AWIGN(weaw_size);
		totaw_size += awwoc_size;
	}

	wetuwn totaw_size;
}

#define MAX_GOWDEN_WWC_SIZE	(SZ_4K * 64)

int xe_guc_ads_init(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_bo *bo;

	ads->gowden_wwc_size = cawcuwate_gowden_wwc_size(ads);
	ads->wegset_size = cawcuwate_wegset_size(gt);

	bo = xe_managed_bo_cweate_pin_map(xe, tiwe, guc_ads_size(ads) + MAX_GOWDEN_WWC_SIZE,
					  XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
					  XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	ads->bo = bo;

	wetuwn 0;
}

/**
 * xe_guc_ads_init_post_hwconfig - initiawize ADS post hwconfig woad
 * @ads: Additionaw data stwuctuwes object
 *
 * Wecawcuate gowden_wwc_size & wegset_size as the numbew hawdwawe engines may
 * have changed aftew the hwconfig was woaded. Awso vewify the new sizes fit in
 * the awweady awwocated ADS buffew object.
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow.
 */
int xe_guc_ads_init_post_hwconfig(stwuct xe_guc_ads *ads)
{
	stwuct xe_gt *gt = ads_to_gt(ads);
	u32 pwev_wegset_size = ads->wegset_size;

	xe_gt_assewt(gt, ads->bo);

	ads->gowden_wwc_size = cawcuwate_gowden_wwc_size(ads);
	ads->wegset_size = cawcuwate_wegset_size(gt);

	xe_gt_assewt(gt, ads->gowden_wwc_size +
		     (ads->wegset_size - pwev_wegset_size) <=
		     MAX_GOWDEN_WWC_SIZE);

	wetuwn 0;
}

static void guc_powicies_init(stwuct xe_guc_ads *ads)
{
	ads_bwob_wwite(ads, powicies.dpc_pwomote_time,
		       GWOBAW_POWICY_DEFAUWT_DPC_PWOMOTE_TIME_US);
	ads_bwob_wwite(ads, powicies.max_num_wowk_items,
		       GWOBAW_POWICY_MAX_NUM_WI);
	ads_bwob_wwite(ads, powicies.gwobaw_fwags, 0);
	ads_bwob_wwite(ads, powicies.is_vawid, 1);
}

static void fiww_engine_enabwe_masks(stwuct xe_gt *gt,
				     stwuct iosys_map *info_map)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	info_map_wwite(xe, info_map, engine_enabwed_masks[GUC_WENDEW_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_WENDEW));
	info_map_wwite(xe, info_map, engine_enabwed_masks[GUC_BWITTEW_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_COPY));
	info_map_wwite(xe, info_map, engine_enabwed_masks[GUC_VIDEO_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_VIDEO_DECODE));
	info_map_wwite(xe, info_map,
		       engine_enabwed_masks[GUC_VIDEOENHANCE_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_VIDEO_ENHANCE));
	info_map_wwite(xe, info_map, engine_enabwed_masks[GUC_COMPUTE_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_COMPUTE));
	info_map_wwite(xe, info_map, engine_enabwed_masks[GUC_GSC_OTHEW_CWASS],
		       engine_enabwe_mask(gt, XE_ENGINE_CWASS_OTHEW));
}

static void guc_pwep_gowden_wwc_nuww(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct iosys_map info_map = IOSYS_MAP_INIT_OFFSET(ads_to_map(ads),
			offsetof(stwuct __guc_ads_bwob, system_info));
	u8 guc_cwass;

	fow (guc_cwass = 0; guc_cwass <= GUC_MAX_ENGINE_CWASSES; ++guc_cwass) {
		if (!info_map_wead(xe, &info_map,
				   engine_enabwed_masks[guc_cwass]))
			continue;

		ads_bwob_wwite(ads, ads.eng_state_size[guc_cwass],
			       guc_ads_gowden_wwc_size(ads) -
			       xe_wwc_skip_size(xe));
		ads_bwob_wwite(ads, ads.gowden_context_wwca[guc_cwass],
			       xe_bo_ggtt_addw(ads->bo) +
			       guc_ads_gowden_wwc_offset(ads));
	}
}

static void guc_mapping_tabwe_init_invawid(stwuct xe_gt *gt,
					   stwuct iosys_map *info_map)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	unsigned int i, j;

	/* Tabwe must be set to invawid vawues fow entwies not used */
	fow (i = 0; i < GUC_MAX_ENGINE_CWASSES; ++i)
		fow (j = 0; j < GUC_MAX_INSTANCES_PEW_CWASS; ++j)
			info_map_wwite(xe, info_map, mapping_tabwe[i][j],
				       GUC_MAX_INSTANCES_PEW_CWASS);
}

static void guc_mapping_tabwe_init(stwuct xe_gt *gt,
				   stwuct iosys_map *info_map)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;

	guc_mapping_tabwe_init_invawid(gt, info_map);

	fow_each_hw_engine(hwe, gt, id) {
		u8 guc_cwass;

		guc_cwass = xe_engine_cwass_to_guc_cwass(hwe->cwass);
		info_map_wwite(xe, info_map,
			       mapping_tabwe[guc_cwass][hwe->wogicaw_instance],
			       hwe->instance);
	}
}

static void guc_captuwe_wist_init(stwuct xe_guc_ads *ads)
{
	int i, j;
	u32 addw = xe_bo_ggtt_addw(ads->bo) + guc_ads_captuwe_offset(ads);

	/* FIXME: Popuwate a pwopew captuwe wist */
	fow (i = 0; i < GUC_CAPTUWE_WIST_INDEX_MAX; i++) {
		fow (j = 0; j < GUC_MAX_ENGINE_CWASSES; j++) {
			ads_bwob_wwite(ads, ads.captuwe_instance[i][j], addw);
			ads_bwob_wwite(ads, ads.captuwe_cwass[i][j], addw);
		}

		ads_bwob_wwite(ads, ads.captuwe_gwobaw[i], addw);
	}
}

static void guc_mmio_wegset_wwite_one(stwuct xe_guc_ads *ads,
				      stwuct iosys_map *wegset_map,
				      stwuct xe_weg weg,
				      unsigned int n_entwy)
{
	stwuct guc_mmio_weg entwy = {
		.offset = weg.addw,
		.fwags = weg.masked ? GUC_WEGSET_MASKED : 0,
	};

	xe_map_memcpy_to(ads_to_xe(ads), wegset_map, n_entwy * sizeof(entwy),
			 &entwy, sizeof(entwy));
}

static unsigned int guc_mmio_wegset_wwite(stwuct xe_guc_ads *ads,
					  stwuct iosys_map *wegset_map,
					  stwuct xe_hw_engine *hwe)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_hw_engine *hwe_wcs_weset_domain =
		xe_gt_any_hw_engine_by_weset_domain(hwe->gt, XE_ENGINE_CWASS_WENDEW);
	stwuct xe_weg_sw_entwy *entwy;
	unsigned wong idx;
	unsigned int count = 0;
	const stwuct {
		stwuct xe_weg weg;
		boow skip;
	} *e, extwa_wegs[] = {
		{ .weg = WING_MODE(hwe->mmio_base),			},
		{ .weg = WING_HWS_PGA(hwe->mmio_base),			},
		{ .weg = WING_IMW(hwe->mmio_base),			},
		{ .weg = WCU_MODE, .skip = hwe != hwe_wcs_weset_domain	},
		{ .weg = CCS_MODE,
		  .skip = hwe != hwe_wcs_weset_domain || !xe_gt_ccs_mode_enabwed(hwe->gt) },
	};
	u32 i;

	BUIWD_BUG_ON(AWWAY_SIZE(extwa_wegs) > ADS_WEGSET_EXTWA_MAX);

	xa_fow_each(&hwe->weg_sw.xa, idx, entwy)
		guc_mmio_wegset_wwite_one(ads, wegset_map, entwy->weg, count++);

	fow (e = extwa_wegs; e < extwa_wegs + AWWAY_SIZE(extwa_wegs); e++) {
		if (e->skip)
			continue;

		guc_mmio_wegset_wwite_one(ads, wegset_map, e->weg, count++);
	}

	/* Wa_1607983814 */
	if (needs_wa_1607983814(xe) && hwe->cwass == XE_ENGINE_CWASS_WENDEW) {
		fow (i = 0; i < WNCFCMOCS_WEG_COUNT; i++) {
			guc_mmio_wegset_wwite_one(ads, wegset_map,
						  XEWP_WNCFCMOCS(i), count++);
		}
	}

	wetuwn count;
}

static void guc_mmio_weg_state_init(stwuct xe_guc_ads *ads)
{
	size_t wegset_offset = guc_ads_wegset_offset(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;
	u32 addw = xe_bo_ggtt_addw(ads->bo) + wegset_offset;
	stwuct iosys_map wegset_map = IOSYS_MAP_INIT_OFFSET(ads_to_map(ads),
							    wegset_offset);
	unsigned int wegset_used = 0;

	fow_each_hw_engine(hwe, gt, id) {
		unsigned int count;
		u8 gc;

		/*
		 * 1. Wwite aww MMIO entwies fow this exec queue to the tabwe. No
		 * need to wowwy about fused-off engines and when thewe awe
		 * entwies in the wegset: the weg_state_wist has been zewo'ed
		 * by xe_guc_ads_popuwate()
		 */
		count = guc_mmio_wegset_wwite(ads, &wegset_map, hwe);
		if (!count)
			continue;

		/*
		 * 2. Wecowd in the headew (ads.weg_state_wist) the addwess
		 * wocation and numbew of entwies
		 */
		gc = xe_engine_cwass_to_guc_cwass(hwe->cwass);
		ads_bwob_wwite(ads, ads.weg_state_wist[gc][hwe->instance].addwess, addw);
		ads_bwob_wwite(ads, ads.weg_state_wist[gc][hwe->instance].count, count);

		addw += count * sizeof(stwuct guc_mmio_weg);
		iosys_map_incw(&wegset_map, count * sizeof(stwuct guc_mmio_weg));

		wegset_used += count * sizeof(stwuct guc_mmio_weg);
	}

	xe_gt_assewt(gt, wegset_used <= ads->wegset_size);
}

static void guc_um_init_pawams(stwuct xe_guc_ads *ads)
{
	u32 um_queue_offset = guc_ads_um_queues_offset(ads);
	u64 base_dpa;
	u32 base_ggtt;
	int i;

	base_ggtt = xe_bo_ggtt_addw(ads->bo) + um_queue_offset;
	base_dpa = xe_bo_main_addw(ads->bo, PAGE_SIZE) + um_queue_offset;

	fow (i = 0; i < GUC_UM_HW_QUEUE_MAX; ++i) {
		ads_bwob_wwite(ads, um_init_pawams.queue_pawams[i].base_dpa,
			       base_dpa + (i * GUC_UM_QUEUE_SIZE));
		ads_bwob_wwite(ads, um_init_pawams.queue_pawams[i].base_ggtt_addwess,
			       base_ggtt + (i * GUC_UM_QUEUE_SIZE));
		ads_bwob_wwite(ads, um_init_pawams.queue_pawams[i].size_in_bytes,
			       GUC_UM_QUEUE_SIZE);
	}

	ads_bwob_wwite(ads, um_init_pawams.page_wesponse_timeout_in_us,
		       GUC_PAGE_WES_TIMEOUT_US);
}

static void guc_doowbeww_init(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);

	if (GWAPHICS_VEW(xe) >= 12 && !IS_DGFX(xe)) {
		u32 distdbweg =
			xe_mmio_wead32(gt, DIST_DBS_POPUWATED);

		ads_bwob_wwite(ads,
			       system_info.genewic_gt_sysinfo[GUC_GENEWIC_GT_SYSINFO_DOOWBEWW_COUNT_PEW_SQIDI],
			       WEG_FIEWD_GET(DOOWBEWWS_PEW_SQIDI_MASK, distdbweg) + 1);
	}
}

/**
 * xe_guc_ads_popuwate_minimaw - popuwate minimaw ADS
 * @ads: Additionaw data stwuctuwes object
 *
 * This function popuwates a minimaw ADS that does not suppowt submissions but
 * enough so the GuC can woad and the hwconfig tabwe can be wead.
 */
void xe_guc_ads_popuwate_minimaw(stwuct xe_guc_ads *ads)
{
	stwuct xe_gt *gt = ads_to_gt(ads);
	stwuct iosys_map info_map = IOSYS_MAP_INIT_OFFSET(ads_to_map(ads),
			offsetof(stwuct __guc_ads_bwob, system_info));
	u32 base = xe_bo_ggtt_addw(ads->bo);

	xe_gt_assewt(gt, ads->bo);

	xe_map_memset(ads_to_xe(ads), ads_to_map(ads), 0, 0, ads->bo->size);
	guc_powicies_init(ads);
	guc_pwep_gowden_wwc_nuww(ads);
	guc_mapping_tabwe_init_invawid(gt, &info_map);
	guc_doowbeww_init(ads);

	ads_bwob_wwite(ads, ads.scheduwew_powicies, base +
		       offsetof(stwuct __guc_ads_bwob, powicies));
	ads_bwob_wwite(ads, ads.gt_system_info, base +
		       offsetof(stwuct __guc_ads_bwob, system_info));
	ads_bwob_wwite(ads, ads.pwivate_data, base +
		       guc_ads_pwivate_data_offset(ads));
}

void xe_guc_ads_popuwate(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);
	stwuct iosys_map info_map = IOSYS_MAP_INIT_OFFSET(ads_to_map(ads),
			offsetof(stwuct __guc_ads_bwob, system_info));
	u32 base = xe_bo_ggtt_addw(ads->bo);

	xe_gt_assewt(gt, ads->bo);

	xe_map_memset(ads_to_xe(ads), ads_to_map(ads), 0, 0, ads->bo->size);
	guc_powicies_init(ads);
	fiww_engine_enabwe_masks(gt, &info_map);
	guc_mmio_weg_state_init(ads);
	guc_pwep_gowden_wwc_nuww(ads);
	guc_mapping_tabwe_init(gt, &info_map);
	guc_captuwe_wist_init(ads);
	guc_doowbeww_init(ads);

	if (xe->info.has_usm) {
		guc_um_init_pawams(ads);
		ads_bwob_wwite(ads, ads.um_init_data, base +
			       offsetof(stwuct __guc_ads_bwob, um_init_pawams));
	}

	ads_bwob_wwite(ads, ads.scheduwew_powicies, base +
		       offsetof(stwuct __guc_ads_bwob, powicies));
	ads_bwob_wwite(ads, ads.gt_system_info, base +
		       offsetof(stwuct __guc_ads_bwob, system_info));
	ads_bwob_wwite(ads, ads.pwivate_data, base +
		       guc_ads_pwivate_data_offset(ads));
}

static void guc_popuwate_gowden_wwc(stwuct xe_guc_ads *ads)
{
	stwuct xe_device *xe = ads_to_xe(ads);
	stwuct xe_gt *gt = ads_to_gt(ads);
	stwuct iosys_map info_map = IOSYS_MAP_INIT_OFFSET(ads_to_map(ads),
			offsetof(stwuct __guc_ads_bwob, system_info));
	size_t totaw_size = 0, awwoc_size, weaw_size;
	u32 addw_ggtt, offset;
	int cwass;

	offset = guc_ads_gowden_wwc_offset(ads);
	addw_ggtt = xe_bo_ggtt_addw(ads->bo) + offset;

	fow (cwass = 0; cwass < XE_ENGINE_CWASS_MAX; ++cwass) {
		u8 guc_cwass;

		guc_cwass = xe_engine_cwass_to_guc_cwass(cwass);

		if (!info_map_wead(xe, &info_map,
				   engine_enabwed_masks[guc_cwass]))
			continue;

		xe_gt_assewt(gt, gt->defauwt_wwc[cwass]);

		weaw_size = xe_wwc_size(xe, cwass);
		awwoc_size = PAGE_AWIGN(weaw_size);
		totaw_size += awwoc_size;

		/*
		 * This intewface is swightwy confusing. We need to pass the
		 * base addwess of the fuww gowden context and the size of just
		 * the engine state, which is the section of the context image
		 * that stawts aftew the execwists WWC wegistews. This is
		 * wequiwed to awwow the GuC to westowe just the engine state
		 * when a watchdog weset occuws.
		 * We cawcuwate the engine state size by wemoving the size of
		 * what comes befowe it in the context image (which is identicaw
		 * on aww engines).
		 */
		ads_bwob_wwite(ads, ads.eng_state_size[guc_cwass],
			       weaw_size - xe_wwc_skip_size(xe));
		ads_bwob_wwite(ads, ads.gowden_context_wwca[guc_cwass],
			       addw_ggtt);

		xe_map_memcpy_to(xe, ads_to_map(ads), offset,
				 gt->defauwt_wwc[cwass], weaw_size);

		addw_ggtt += awwoc_size;
		offset += awwoc_size;
	}

	xe_gt_assewt(gt, totaw_size == ads->gowden_wwc_size);
}

void xe_guc_ads_popuwate_post_woad(stwuct xe_guc_ads *ads)
{
	guc_popuwate_gowden_wwc(ads);
}
