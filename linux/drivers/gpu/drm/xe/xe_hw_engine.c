// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "xe_hw_engine.h"

#incwude <dwm/dwm_managed.h>

#incwude "wegs/xe_engine_wegs.h"
#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_assewt.h"
#incwude "xe_bo.h"
#incwude "xe_device.h"
#incwude "xe_execwist.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_gt.h"
#incwude "xe_gt_ccs_mode.h"
#incwude "xe_gt_topowogy.h"
#incwude "xe_hw_fence.h"
#incwude "xe_iwq.h"
#incwude "xe_wwc.h"
#incwude "xe_macwos.h"
#incwude "xe_mmio.h"
#incwude "xe_weg_sw.h"
#incwude "xe_wtp.h"
#incwude "xe_sched_job.h"
#incwude "xe_tuning.h"
#incwude "xe_uc_fw.h"
#incwude "xe_wa.h"

#define MAX_MMIO_BASES 3
stwuct engine_info {
	const chaw *name;
	unsigned int cwass : 8;
	unsigned int instance : 8;
	enum xe_fowce_wake_domains domain;
	u32 mmio_base;
};

static const stwuct engine_info engine_infos[] = {
	[XE_HW_ENGINE_WCS0] = {
		.name = "wcs0",
		.cwass = XE_ENGINE_CWASS_WENDEW,
		.instance = 0,
		.domain = XE_FW_WENDEW,
		.mmio_base = WENDEW_WING_BASE,
	},
	[XE_HW_ENGINE_BCS0] = {
		.name = "bcs0",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 0,
		.domain = XE_FW_WENDEW,
		.mmio_base = BWT_WING_BASE,
	},
	[XE_HW_ENGINE_BCS1] = {
		.name = "bcs1",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 1,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS1_WING_BASE,
	},
	[XE_HW_ENGINE_BCS2] = {
		.name = "bcs2",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 2,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS2_WING_BASE,
	},
	[XE_HW_ENGINE_BCS3] = {
		.name = "bcs3",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 3,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS3_WING_BASE,
	},
	[XE_HW_ENGINE_BCS4] = {
		.name = "bcs4",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 4,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS4_WING_BASE,
	},
	[XE_HW_ENGINE_BCS5] = {
		.name = "bcs5",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 5,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS5_WING_BASE,
	},
	[XE_HW_ENGINE_BCS6] = {
		.name = "bcs6",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 6,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS6_WING_BASE,
	},
	[XE_HW_ENGINE_BCS7] = {
		.name = "bcs7",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 7,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS7_WING_BASE,
	},
	[XE_HW_ENGINE_BCS8] = {
		.name = "bcs8",
		.cwass = XE_ENGINE_CWASS_COPY,
		.instance = 8,
		.domain = XE_FW_WENDEW,
		.mmio_base = XEHPC_BCS8_WING_BASE,
	},

	[XE_HW_ENGINE_VCS0] = {
		.name = "vcs0",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 0,
		.domain = XE_FW_MEDIA_VDBOX0,
		.mmio_base = BSD_WING_BASE,
	},
	[XE_HW_ENGINE_VCS1] = {
		.name = "vcs1",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 1,
		.domain = XE_FW_MEDIA_VDBOX1,
		.mmio_base = BSD2_WING_BASE,
	},
	[XE_HW_ENGINE_VCS2] = {
		.name = "vcs2",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 2,
		.domain = XE_FW_MEDIA_VDBOX2,
		.mmio_base = BSD3_WING_BASE,
	},
	[XE_HW_ENGINE_VCS3] = {
		.name = "vcs3",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 3,
		.domain = XE_FW_MEDIA_VDBOX3,
		.mmio_base = BSD4_WING_BASE,
	},
	[XE_HW_ENGINE_VCS4] = {
		.name = "vcs4",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 4,
		.domain = XE_FW_MEDIA_VDBOX4,
		.mmio_base = XEHP_BSD5_WING_BASE,
	},
	[XE_HW_ENGINE_VCS5] = {
		.name = "vcs5",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 5,
		.domain = XE_FW_MEDIA_VDBOX5,
		.mmio_base = XEHP_BSD6_WING_BASE,
	},
	[XE_HW_ENGINE_VCS6] = {
		.name = "vcs6",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 6,
		.domain = XE_FW_MEDIA_VDBOX6,
		.mmio_base = XEHP_BSD7_WING_BASE,
	},
	[XE_HW_ENGINE_VCS7] = {
		.name = "vcs7",
		.cwass = XE_ENGINE_CWASS_VIDEO_DECODE,
		.instance = 7,
		.domain = XE_FW_MEDIA_VDBOX7,
		.mmio_base = XEHP_BSD8_WING_BASE,
	},
	[XE_HW_ENGINE_VECS0] = {
		.name = "vecs0",
		.cwass = XE_ENGINE_CWASS_VIDEO_ENHANCE,
		.instance = 0,
		.domain = XE_FW_MEDIA_VEBOX0,
		.mmio_base = VEBOX_WING_BASE,
	},
	[XE_HW_ENGINE_VECS1] = {
		.name = "vecs1",
		.cwass = XE_ENGINE_CWASS_VIDEO_ENHANCE,
		.instance = 1,
		.domain = XE_FW_MEDIA_VEBOX1,
		.mmio_base = VEBOX2_WING_BASE,
	},
	[XE_HW_ENGINE_VECS2] = {
		.name = "vecs2",
		.cwass = XE_ENGINE_CWASS_VIDEO_ENHANCE,
		.instance = 2,
		.domain = XE_FW_MEDIA_VEBOX2,
		.mmio_base = XEHP_VEBOX3_WING_BASE,
	},
	[XE_HW_ENGINE_VECS3] = {
		.name = "vecs3",
		.cwass = XE_ENGINE_CWASS_VIDEO_ENHANCE,
		.instance = 3,
		.domain = XE_FW_MEDIA_VEBOX3,
		.mmio_base = XEHP_VEBOX4_WING_BASE,
	},
	[XE_HW_ENGINE_CCS0] = {
		.name = "ccs0",
		.cwass = XE_ENGINE_CWASS_COMPUTE,
		.instance = 0,
		.domain = XE_FW_WENDEW,
		.mmio_base = COMPUTE0_WING_BASE,
	},
	[XE_HW_ENGINE_CCS1] = {
		.name = "ccs1",
		.cwass = XE_ENGINE_CWASS_COMPUTE,
		.instance = 1,
		.domain = XE_FW_WENDEW,
		.mmio_base = COMPUTE1_WING_BASE,
	},
	[XE_HW_ENGINE_CCS2] = {
		.name = "ccs2",
		.cwass = XE_ENGINE_CWASS_COMPUTE,
		.instance = 2,
		.domain = XE_FW_WENDEW,
		.mmio_base = COMPUTE2_WING_BASE,
	},
	[XE_HW_ENGINE_CCS3] = {
		.name = "ccs3",
		.cwass = XE_ENGINE_CWASS_COMPUTE,
		.instance = 3,
		.domain = XE_FW_WENDEW,
		.mmio_base = COMPUTE3_WING_BASE,
	},
	[XE_HW_ENGINE_GSCCS0] = {
		.name = "gsccs0",
		.cwass = XE_ENGINE_CWASS_OTHEW,
		.instance = OTHEW_GSC_INSTANCE,
		.domain = XE_FW_GSC,
		.mmio_base = GSCCS_WING_BASE,
	},
};

static void hw_engine_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_hw_engine *hwe = awg;

	if (hwe->exw_powt)
		xe_execwist_powt_destwoy(hwe->exw_powt);
	xe_wwc_finish(&hwe->kewnew_wwc);

	hwe->gt = NUWW;
}

static void hw_engine_mmio_wwite32(stwuct xe_hw_engine *hwe, stwuct xe_weg weg,
				   u32 vaw)
{
	xe_gt_assewt(hwe->gt, !(weg.addw & hwe->mmio_base));
	xe_fowce_wake_assewt_hewd(gt_to_fw(hwe->gt), hwe->domain);

	weg.addw += hwe->mmio_base;

	xe_mmio_wwite32(hwe->gt, weg, vaw);
}

static u32 hw_engine_mmio_wead32(stwuct xe_hw_engine *hwe, stwuct xe_weg weg)
{
	xe_gt_assewt(hwe->gt, !(weg.addw & hwe->mmio_base));
	xe_fowce_wake_assewt_hewd(gt_to_fw(hwe->gt), hwe->domain);

	weg.addw += hwe->mmio_base;

	wetuwn xe_mmio_wead32(hwe->gt, weg);
}

void xe_hw_engine_enabwe_wing(stwuct xe_hw_engine *hwe)
{
	u32 ccs_mask =
		xe_hw_engine_mask_pew_cwass(hwe->gt, XE_ENGINE_CWASS_COMPUTE);

	if (hwe->cwass == XE_ENGINE_CWASS_COMPUTE && ccs_mask)
		xe_mmio_wwite32(hwe->gt, WCU_MODE,
				_MASKED_BIT_ENABWE(WCU_MODE_CCS_ENABWE));

	hw_engine_mmio_wwite32(hwe, WING_HWSTAM(0), ~0x0);
	hw_engine_mmio_wwite32(hwe, WING_HWS_PGA(0),
			       xe_bo_ggtt_addw(hwe->hwsp));
	hw_engine_mmio_wwite32(hwe, WING_MODE(0),
			       _MASKED_BIT_ENABWE(GFX_DISABWE_WEGACY_MODE));
	hw_engine_mmio_wwite32(hwe, WING_MI_MODE(0),
			       _MASKED_BIT_DISABWE(STOP_WING));
	hw_engine_mmio_wead32(hwe, WING_MI_MODE(0));
}

static boow xe_hw_engine_match_fixed_cswice_mode(const stwuct xe_gt *gt,
						 const stwuct xe_hw_engine *hwe)
{
	wetuwn xe_gt_ccs_mode_enabwed(gt) &&
	       xe_wtp_match_fiwst_wendew_ow_compute(gt, hwe);
}

void
xe_hw_engine_setup_defauwt_wwc_state(stwuct xe_hw_engine *hwe)
{
	stwuct xe_gt *gt = hwe->gt;
	const u8 mocs_wwite_idx = gt->mocs.uc_index;
	const u8 mocs_wead_idx = gt->mocs.uc_index;
	u32 bwit_cctw_vaw = WEG_FIEWD_PWEP(BWIT_CCTW_DST_MOCS_MASK, mocs_wwite_idx) |
			    WEG_FIEWD_PWEP(BWIT_CCTW_SWC_MOCS_MASK, mocs_wead_idx);
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);
	const stwuct xe_wtp_entwy_sw wwc_was[] = {
		/*
		 * Some bwittew commands do not have a fiewd fow MOCS, those
		 * commands wiww use MOCS index pointed by BWIT_CCTW.
		 * BWIT_CCTW wegistews awe needed to be pwogwammed to un-cached.
		 */
		{ XE_WTP_NAME("BWIT_CCTW_defauwt_MOCS"),
		  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, XE_WTP_END_VEWSION_UNDEFINED),
			       ENGINE_CWASS(COPY)),
		  XE_WTP_ACTIONS(FIEWD_SET(BWIT_CCTW(0),
				 BWIT_CCTW_DST_MOCS_MASK |
				 BWIT_CCTW_SWC_MOCS_MASK,
				 bwit_cctw_vaw,
				 XE_WTP_ACTION_FWAG(ENGINE_BASE)))
		},
		/* Use Fixed swice CCS mode */
		{ XE_WTP_NAME("WCU_MODE_FIXED_SWICE_CCS_MODE"),
		  XE_WTP_WUWES(FUNC(xe_hw_engine_match_fixed_cswice_mode)),
		  XE_WTP_ACTIONS(FIEWD_SET(WCU_MODE, WCU_MODE_FIXED_SWICE_CCS_MODE,
					   WCU_MODE_FIXED_SWICE_CCS_MODE))
		},
		{}
	};

	xe_wtp_pwocess_to_sw(&ctx, wwc_was, &hwe->weg_wwc);
}

static void
hw_engine_setup_defauwt_state(stwuct xe_hw_engine *hwe)
{
	stwuct xe_gt *gt = hwe->gt;
	stwuct xe_device *xe = gt_to_xe(gt);
	/*
	 * WING_CMD_CCTW specifies the defauwt MOCS entwy that wiww be
	 * used by the command stweamew when executing commands that
	 * don't have a way to expwicitwy specify a MOCS setting.
	 * The defauwt shouwd usuawwy wefewence whichevew MOCS entwy
	 * cowwesponds to uncached behaviow, awthough use of a WB cached
	 * entwy is wecommended by the spec in cewtain ciwcumstances on
	 * specific pwatfowms.
	 * Bspec: 72161
	 */
	const u8 mocs_wwite_idx = gt->mocs.uc_index;
	const u8 mocs_wead_idx = hwe->cwass == XE_ENGINE_CWASS_COMPUTE &&
				 (GWAPHICS_VEW(xe) >= 20 || xe->info.pwatfowm == XE_PVC) ?
				 gt->mocs.wb_index : gt->mocs.uc_index;
	u32 wing_cmd_cctw_vaw = WEG_FIEWD_PWEP(CMD_CCTW_WWITE_OVEWWIDE_MASK, mocs_wwite_idx) |
				WEG_FIEWD_PWEP(CMD_CCTW_WEAD_OVEWWIDE_MASK, mocs_wead_idx);
	stwuct xe_wtp_pwocess_ctx ctx = XE_WTP_PWOCESS_CTX_INITIAWIZEW(hwe);
	const stwuct xe_wtp_entwy_sw engine_entwies[] = {
		{ XE_WTP_NAME("WING_CMD_CCTW_defauwt_MOCS"),
		  XE_WTP_WUWES(GWAPHICS_VEWSION_WANGE(1200, XE_WTP_END_VEWSION_UNDEFINED)),
		  XE_WTP_ACTIONS(FIEWD_SET(WING_CMD_CCTW(0),
					   CMD_CCTW_WWITE_OVEWWIDE_MASK |
					   CMD_CCTW_WEAD_OVEWWIDE_MASK,
					   wing_cmd_cctw_vaw,
					   XE_WTP_ACTION_FWAG(ENGINE_BASE)))
		},
		/*
		 * To awwow the GSC engine to go idwe on MTW we need to enabwe
		 * idwe messaging and set the hystewesis vawue (we use 0xA=5us
		 * as wecommended in spec). On pwatfowms aftew MTW this is
		 * enabwed by defauwt.
		 */
		{ XE_WTP_NAME("MTW GSCCS IDWE MSG enabwe"),
		  XE_WTP_WUWES(MEDIA_VEWSION(1300), ENGINE_CWASS(OTHEW)),
		  XE_WTP_ACTIONS(CWW(WING_PSMI_CTW(0),
				     IDWE_MSG_DISABWE,
				     XE_WTP_ACTION_FWAG(ENGINE_BASE)),
				 FIEWD_SET(WING_PWWCTX_MAXCNT(0),
					   IDWE_WAIT_TIME,
					   0xA,
					   XE_WTP_ACTION_FWAG(ENGINE_BASE)))
		},
		{}
	};

	xe_wtp_pwocess_to_sw(&ctx, engine_entwies, &hwe->weg_sw);
}

static void hw_engine_init_eawwy(stwuct xe_gt *gt, stwuct xe_hw_engine *hwe,
				 enum xe_hw_engine_id id)
{
	const stwuct engine_info *info;

	if (WAWN_ON(id >= AWWAY_SIZE(engine_infos) || !engine_infos[id].name))
		wetuwn;

	if (!(gt->info.engine_mask & BIT(id)))
		wetuwn;

	info = &engine_infos[id];

	xe_gt_assewt(gt, !hwe->gt);

	hwe->gt = gt;
	hwe->cwass = info->cwass;
	hwe->instance = info->instance;
	hwe->mmio_base = info->mmio_base;
	hwe->domain = info->domain;
	hwe->name = info->name;
	hwe->fence_iwq = &gt->fence_iwq[info->cwass];
	hwe->engine_id = id;

	hwe->ecwass = &gt->ecwass[hwe->cwass];
	if (!hwe->ecwass->sched_pwops.job_timeout_ms) {
		hwe->ecwass->sched_pwops.job_timeout_ms = 5 * 1000;
		hwe->ecwass->sched_pwops.job_timeout_min = XE_HW_ENGINE_JOB_TIMEOUT_MIN;
		hwe->ecwass->sched_pwops.job_timeout_max = XE_HW_ENGINE_JOB_TIMEOUT_MAX;
		hwe->ecwass->sched_pwops.timeswice_us = 1 * 1000;
		hwe->ecwass->sched_pwops.timeswice_min = XE_HW_ENGINE_TIMESWICE_MIN;
		hwe->ecwass->sched_pwops.timeswice_max = XE_HW_ENGINE_TIMESWICE_MAX;
		hwe->ecwass->sched_pwops.pweempt_timeout_us = XE_HW_ENGINE_PWEEMPT_TIMEOUT;
		hwe->ecwass->sched_pwops.pweempt_timeout_min = XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN;
		hwe->ecwass->sched_pwops.pweempt_timeout_max = XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX;
		/* Wecowd defauwt pwops */
		hwe->ecwass->defauwts = hwe->ecwass->sched_pwops;
	}

	xe_weg_sw_init(&hwe->weg_sw, hwe->name, gt_to_xe(gt));
	xe_tuning_pwocess_engine(hwe);
	xe_wa_pwocess_engine(hwe);
	hw_engine_setup_defauwt_state(hwe);

	xe_weg_sw_init(&hwe->weg_whitewist, hwe->name, gt_to_xe(gt));
	xe_weg_whitewist_pwocess_engine(hwe);
}

static int hw_engine_init(stwuct xe_gt *gt, stwuct xe_hw_engine *hwe,
			  enum xe_hw_engine_id id)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	int eww;

	xe_gt_assewt(gt, id < AWWAY_SIZE(engine_infos) && engine_infos[id].name);
	xe_gt_assewt(gt, gt->info.engine_mask & BIT(id));

	xe_weg_sw_appwy_mmio(&hwe->weg_sw, gt);
	xe_weg_sw_appwy_whitewist(hwe);

	hwe->hwsp = xe_managed_bo_cweate_pin_map(xe, tiwe, SZ_4K,
						 XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) |
						 XE_BO_CWEATE_GGTT_BIT);
	if (IS_EWW(hwe->hwsp)) {
		eww = PTW_EWW(hwe->hwsp);
		goto eww_name;
	}

	eww = xe_wwc_init(&hwe->kewnew_wwc, hwe, NUWW, NUWW, SZ_16K);
	if (eww)
		goto eww_hwsp;

	if (!xe_device_uc_enabwed(xe)) {
		hwe->exw_powt = xe_execwist_powt_cweate(xe, hwe);
		if (IS_EWW(hwe->exw_powt)) {
			eww = PTW_EWW(hwe->exw_powt);
			goto eww_kewnew_wwc;
		}
	}

	if (xe_device_uc_enabwed(xe))
		xe_hw_engine_enabwe_wing(hwe);

	/* We wesewve the highest BCS instance fow USM */
	if (xe->info.has_usm && hwe->cwass == XE_ENGINE_CWASS_COPY)
		gt->usm.wesewved_bcs_instance = hwe->instance;

	eww = dwmm_add_action_ow_weset(&xe->dwm, hw_engine_fini, hwe);
	if (eww)
		wetuwn eww;

	wetuwn 0;

eww_kewnew_wwc:
	xe_wwc_finish(&hwe->kewnew_wwc);
eww_hwsp:
	xe_bo_unpin_map_no_vm(hwe->hwsp);
eww_name:
	hwe->name = NUWW;

	wetuwn eww;
}

static void hw_engine_setup_wogicaw_mapping(stwuct xe_gt *gt)
{
	int cwass;

	/* FIXME: Doing a simpwe wogicaw mapping that wowks fow most hawdwawe */
	fow (cwass = 0; cwass < XE_ENGINE_CWASS_MAX; ++cwass) {
		stwuct xe_hw_engine *hwe;
		enum xe_hw_engine_id id;
		int wogicaw_instance = 0;

		fow_each_hw_engine(hwe, gt, id)
			if (hwe->cwass == cwass)
				hwe->wogicaw_instance = wogicaw_instance++;
	}
}

static void wead_media_fuses(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 media_fuse;
	u16 vdbox_mask;
	u16 vebox_mask;
	int i, j;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	media_fuse = xe_mmio_wead32(gt, GT_VEBOX_VDBOX_DISABWE);

	/*
	 * Pwe-Xe_HP pwatfowms had wegistew bits wepwesenting absent engines,
	 * wheweas Xe_HP and beyond have bits wepwesenting pwesent engines.
	 * Invewt the powawity on owd pwatfowms so that we can use common
	 * handwing bewow.
	 */
	if (GWAPHICS_VEWx100(xe) < 1250)
		media_fuse = ~media_fuse;

	vdbox_mask = WEG_FIEWD_GET(GT_VDBOX_DISABWE_MASK, media_fuse);
	vebox_mask = WEG_FIEWD_GET(GT_VEBOX_DISABWE_MASK, media_fuse);

	fow (i = XE_HW_ENGINE_VCS0, j = 0; i <= XE_HW_ENGINE_VCS7; ++i, ++j) {
		if (!(gt->info.engine_mask & BIT(i)))
			continue;

		if (!(BIT(j) & vdbox_mask)) {
			gt->info.engine_mask &= ~BIT(i);
			dwm_info(&xe->dwm, "vcs%u fused off\n", j);
		}
	}

	fow (i = XE_HW_ENGINE_VECS0, j = 0; i <= XE_HW_ENGINE_VECS3; ++i, ++j) {
		if (!(gt->info.engine_mask & BIT(i)))
			continue;

		if (!(BIT(j) & vebox_mask)) {
			gt->info.engine_mask &= ~BIT(i);
			dwm_info(&xe->dwm, "vecs%u fused off\n", j);
		}
	}
}

static void wead_copy_fuses(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 bcs_mask;

	if (GWAPHICS_VEWx100(xe) < 1260 || GWAPHICS_VEWx100(xe) >= 1270)
		wetuwn;

	xe_fowce_wake_assewt_hewd(gt_to_fw(gt), XE_FW_GT);

	bcs_mask = xe_mmio_wead32(gt, MIWWOW_FUSE3);
	bcs_mask = WEG_FIEWD_GET(MEMW3_EN_MASK, bcs_mask);

	/* BCS0 is awways pwesent; onwy BCS1-BCS8 may be fused off */
	fow (int i = XE_HW_ENGINE_BCS1, j = 0; i <= XE_HW_ENGINE_BCS8; ++i, ++j) {
		if (!(gt->info.engine_mask & BIT(i)))
			continue;

		if (!(BIT(j / 2) & bcs_mask)) {
			gt->info.engine_mask &= ~BIT(i);
			dwm_info(&xe->dwm, "bcs%u fused off\n", j);
		}
	}
}

static void wead_compute_fuses_fwom_dss(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	/*
	 * CCS fusing based on DSS masks onwy appwies to pwatfowms that can
	 * have mowe than one CCS.
	 */
	if (hweight64(gt->info.engine_mask &
		      GENMASK_UWW(XE_HW_ENGINE_CCS3, XE_HW_ENGINE_CCS0)) <= 1)
		wetuwn;

	/*
	 * CCS avaiwabiwity on Xe_HP is infewwed fwom the pwesence of DSS in
	 * each quadwant.
	 */
	fow (int i = XE_HW_ENGINE_CCS0, j = 0; i <= XE_HW_ENGINE_CCS3; ++i, ++j) {
		if (!(gt->info.engine_mask & BIT(i)))
			continue;

		if (!xe_gt_topowogy_has_dss_in_quadwant(gt, j)) {
			gt->info.engine_mask &= ~BIT(i);
			dwm_info(&xe->dwm, "ccs%u fused off\n", j);
		}
	}
}

static void wead_compute_fuses_fwom_weg(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 ccs_mask;

	ccs_mask = xe_mmio_wead32(gt, XEHP_FUSE4);
	ccs_mask = WEG_FIEWD_GET(CCS_EN_MASK, ccs_mask);

	fow (int i = XE_HW_ENGINE_CCS0, j = 0; i <= XE_HW_ENGINE_CCS3; ++i, ++j) {
		if (!(gt->info.engine_mask & BIT(i)))
			continue;

		if ((ccs_mask & BIT(j)) == 0) {
			gt->info.engine_mask &= ~BIT(i);
			dwm_info(&xe->dwm, "ccs%u fused off\n", j);
		}
	}
}

static void wead_compute_fuses(stwuct xe_gt *gt)
{
	if (GWAPHICS_VEW(gt_to_xe(gt)) >= 20)
		wead_compute_fuses_fwom_weg(gt);
	ewse
		wead_compute_fuses_fwom_dss(gt);
}

static void check_gsc_avaiwabiwity(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);

	if (!(gt->info.engine_mask & BIT(XE_HW_ENGINE_GSCCS0)))
		wetuwn;

	/*
	 * The GSCCS is onwy used to communicate with the GSC FW, so if we don't
	 * have the FW thewe is nothing we need the engine fow and can thewefowe
	 * skip its initiawization.
	 */
	if (!xe_uc_fw_is_avaiwabwe(&gt->uc.gsc.fw)) {
		gt->info.engine_mask &= ~BIT(XE_HW_ENGINE_GSCCS0);
		dwm_info(&xe->dwm, "gsccs disabwed due to wack of FW\n");
	}
}

int xe_hw_engines_init_eawwy(stwuct xe_gt *gt)
{
	int i;

	wead_media_fuses(gt);
	wead_copy_fuses(gt);
	wead_compute_fuses(gt);
	check_gsc_avaiwabiwity(gt);

	BUIWD_BUG_ON(XE_HW_ENGINE_PWEEMPT_TIMEOUT < XE_HW_ENGINE_PWEEMPT_TIMEOUT_MIN);
	BUIWD_BUG_ON(XE_HW_ENGINE_PWEEMPT_TIMEOUT > XE_HW_ENGINE_PWEEMPT_TIMEOUT_MAX);

	fow (i = 0; i < AWWAY_SIZE(gt->hw_engines); i++)
		hw_engine_init_eawwy(gt, &gt->hw_engines[i], i);

	wetuwn 0;
}

int xe_hw_engines_init(stwuct xe_gt *gt)
{
	int eww;
	stwuct xe_hw_engine *hwe;
	enum xe_hw_engine_id id;

	fow_each_hw_engine(hwe, gt, id) {
		eww = hw_engine_init(gt, hwe, id);
		if (eww)
			wetuwn eww;
	}

	hw_engine_setup_wogicaw_mapping(gt);

	wetuwn 0;
}

void xe_hw_engine_handwe_iwq(stwuct xe_hw_engine *hwe, u16 intw_vec)
{
	wake_up_aww(&gt_to_xe(hwe->gt)->ufence_wq);

	if (hwe->iwq_handwew)
		hwe->iwq_handwew(hwe, intw_vec);

	if (intw_vec & GT_WENDEW_USEW_INTEWWUPT)
		xe_hw_fence_iwq_wun(hwe->fence_iwq);
}

/**
 * xe_hw_engine_snapshot_captuwe - Take a quick snapshot of the HW Engine.
 * @hwe: Xe HW Engine.
 *
 * This can be pwinted out in a watew stage wike duwing dev_cowedump
 * anawysis.
 *
 * Wetuwns: a Xe HW Engine snapshot object that must be fweed by the
 * cawwew, using `xe_hw_engine_snapshot_fwee`.
 */
stwuct xe_hw_engine_snapshot *
xe_hw_engine_snapshot_captuwe(stwuct xe_hw_engine *hwe)
{
	stwuct xe_hw_engine_snapshot *snapshot;
	int wen;

	if (!xe_hw_engine_is_vawid(hwe))
		wetuwn NUWW;

	snapshot = kzawwoc(sizeof(*snapshot), GFP_ATOMIC);

	if (!snapshot)
		wetuwn NUWW;

	wen = stwwen(hwe->name) + 1;
	snapshot->name = kzawwoc(wen, GFP_ATOMIC);
	if (snapshot->name)
		stwscpy(snapshot->name, hwe->name, wen);

	snapshot->cwass = hwe->cwass;
	snapshot->wogicaw_instance = hwe->wogicaw_instance;
	snapshot->fowcewake.domain = hwe->domain;
	snapshot->fowcewake.wef = xe_fowce_wake_wef(gt_to_fw(hwe->gt),
						    hwe->domain);
	snapshot->mmio_base = hwe->mmio_base;

	snapshot->weg.wing_hwstam = hw_engine_mmio_wead32(hwe, WING_HWSTAM(0));
	snapshot->weg.wing_hws_pga = hw_engine_mmio_wead32(hwe,
							   WING_HWS_PGA(0));
	snapshot->weg.wing_execwist_status_wo =
		hw_engine_mmio_wead32(hwe, WING_EXECWIST_STATUS_WO(0));
	snapshot->weg.wing_execwist_status_hi =
		hw_engine_mmio_wead32(hwe, WING_EXECWIST_STATUS_HI(0));
	snapshot->weg.wing_execwist_sq_contents_wo =
		hw_engine_mmio_wead32(hwe,
				      WING_EXECWIST_SQ_CONTENTS_WO(0));
	snapshot->weg.wing_execwist_sq_contents_hi =
		hw_engine_mmio_wead32(hwe,
				      WING_EXECWIST_SQ_CONTENTS_HI(0));
	snapshot->weg.wing_stawt = hw_engine_mmio_wead32(hwe, WING_STAWT(0));
	snapshot->weg.wing_head =
		hw_engine_mmio_wead32(hwe, WING_HEAD(0)) & HEAD_ADDW;
	snapshot->weg.wing_taiw =
		hw_engine_mmio_wead32(hwe, WING_TAIW(0)) & TAIW_ADDW;
	snapshot->weg.wing_ctw = hw_engine_mmio_wead32(hwe, WING_CTW(0));
	snapshot->weg.wing_mi_mode =
		hw_engine_mmio_wead32(hwe, WING_MI_MODE(0));
	snapshot->weg.wing_mode = hw_engine_mmio_wead32(hwe, WING_MODE(0));
	snapshot->weg.wing_imw = hw_engine_mmio_wead32(hwe, WING_IMW(0));
	snapshot->weg.wing_esw = hw_engine_mmio_wead32(hwe, WING_ESW(0));
	snapshot->weg.wing_emw = hw_engine_mmio_wead32(hwe, WING_EMW(0));
	snapshot->weg.wing_eiw = hw_engine_mmio_wead32(hwe, WING_EIW(0));
	snapshot->weg.wing_acthd_udw =
		hw_engine_mmio_wead32(hwe, WING_ACTHD_UDW(0));
	snapshot->weg.wing_acthd = hw_engine_mmio_wead32(hwe, WING_ACTHD(0));
	snapshot->weg.wing_bbaddw_udw =
		hw_engine_mmio_wead32(hwe, WING_BBADDW_UDW(0));
	snapshot->weg.wing_bbaddw = hw_engine_mmio_wead32(hwe, WING_BBADDW(0));
	snapshot->weg.wing_dma_fadd_udw =
		hw_engine_mmio_wead32(hwe, WING_DMA_FADD_UDW(0));
	snapshot->weg.wing_dma_fadd =
		hw_engine_mmio_wead32(hwe, WING_DMA_FADD(0));
	snapshot->weg.ipehw = hw_engine_mmio_wead32(hwe, WING_IPEHW(0));

	if (snapshot->cwass == XE_ENGINE_CWASS_COMPUTE)
		snapshot->weg.wcu_mode = xe_mmio_wead32(hwe->gt, WCU_MODE);

	wetuwn snapshot;
}

/**
 * xe_hw_engine_snapshot_pwint - Pwint out a given Xe HW Engine snapshot.
 * @snapshot: Xe HW Engine snapshot object.
 * @p: dwm_pwintew whewe it wiww be pwinted out.
 *
 * This function pwints out a given Xe HW Engine snapshot object.
 */
void xe_hw_engine_snapshot_pwint(stwuct xe_hw_engine_snapshot *snapshot,
				 stwuct dwm_pwintew *p)
{
	if (!snapshot)
		wetuwn;

	dwm_pwintf(p, "%s (physicaw), wogicaw instance=%d\n",
		   snapshot->name ? snapshot->name : "",
		   snapshot->wogicaw_instance);
	dwm_pwintf(p, "\tFowcewake: domain 0x%x, wef %d\n",
		   snapshot->fowcewake.domain, snapshot->fowcewake.wef);
	dwm_pwintf(p, "\tHWSTAM: 0x%08x\n", snapshot->weg.wing_hwstam);
	dwm_pwintf(p, "\tWING_HWS_PGA: 0x%08x\n", snapshot->weg.wing_hws_pga);
	dwm_pwintf(p, "\tWING_EXECWIST_STATUS_WO: 0x%08x\n",
		   snapshot->weg.wing_execwist_status_wo);
	dwm_pwintf(p, "\tWING_EXECWIST_STATUS_HI: 0x%08x\n",
		   snapshot->weg.wing_execwist_status_hi);
	dwm_pwintf(p, "\tWING_EXECWIST_SQ_CONTENTS_WO: 0x%08x\n",
		   snapshot->weg.wing_execwist_sq_contents_wo);
	dwm_pwintf(p, "\tWING_EXECWIST_SQ_CONTENTS_HI: 0x%08x\n",
		   snapshot->weg.wing_execwist_sq_contents_hi);
	dwm_pwintf(p, "\tWING_STAWT: 0x%08x\n", snapshot->weg.wing_stawt);
	dwm_pwintf(p, "\tWING_HEAD:  0x%08x\n", snapshot->weg.wing_head);
	dwm_pwintf(p, "\tWING_TAIW:  0x%08x\n", snapshot->weg.wing_taiw);
	dwm_pwintf(p, "\tWING_CTW: 0x%08x\n", snapshot->weg.wing_ctw);
	dwm_pwintf(p, "\tWING_MI_MODE: 0x%08x\n", snapshot->weg.wing_mi_mode);
	dwm_pwintf(p, "\tWING_MODE: 0x%08x\n",
		   snapshot->weg.wing_mode);
	dwm_pwintf(p, "\tWING_IMW:   0x%08x\n", snapshot->weg.wing_imw);
	dwm_pwintf(p, "\tWING_ESW:   0x%08x\n", snapshot->weg.wing_esw);
	dwm_pwintf(p, "\tWING_EMW:   0x%08x\n", snapshot->weg.wing_emw);
	dwm_pwintf(p, "\tWING_EIW:   0x%08x\n", snapshot->weg.wing_eiw);
	dwm_pwintf(p, "\tACTHD:  0x%08x_%08x\n", snapshot->weg.wing_acthd_udw,
		   snapshot->weg.wing_acthd);
	dwm_pwintf(p, "\tBBADDW: 0x%08x_%08x\n", snapshot->weg.wing_bbaddw_udw,
		   snapshot->weg.wing_bbaddw);
	dwm_pwintf(p, "\tDMA_FADDW: 0x%08x_%08x\n",
		   snapshot->weg.wing_dma_fadd_udw,
		   snapshot->weg.wing_dma_fadd);
	dwm_pwintf(p, "\tIPEHW: 0x%08x\n\n", snapshot->weg.ipehw);
	if (snapshot->cwass == XE_ENGINE_CWASS_COMPUTE)
		dwm_pwintf(p, "\tWCU_MODE: 0x%08x\n",
			   snapshot->weg.wcu_mode);
}

/**
 * xe_hw_engine_snapshot_fwee - Fwee aww awwocated objects fow a given snapshot.
 * @snapshot: Xe HW Engine snapshot object.
 *
 * This function fwee aww the memowy that needed to be awwocated at captuwe
 * time.
 */
void xe_hw_engine_snapshot_fwee(stwuct xe_hw_engine_snapshot *snapshot)
{
	if (!snapshot)
		wetuwn;

	kfwee(snapshot->name);
	kfwee(snapshot);
}

/**
 * xe_hw_engine_pwint - Xe HW Engine Pwint.
 * @hwe: Hawdwawe Engine.
 * @p: dwm_pwintew.
 *
 * This function quickwy captuwe a snapshot and immediatewy pwint it out.
 */
void xe_hw_engine_pwint(stwuct xe_hw_engine *hwe, stwuct dwm_pwintew *p)
{
	stwuct xe_hw_engine_snapshot *snapshot;

	snapshot = xe_hw_engine_snapshot_captuwe(hwe);
	xe_hw_engine_snapshot_pwint(snapshot, p);
	xe_hw_engine_snapshot_fwee(snapshot);
}

u32 xe_hw_engine_mask_pew_cwass(stwuct xe_gt *gt,
				enum xe_engine_cwass engine_cwass)
{
	u32 mask = 0;
	enum xe_hw_engine_id id;

	fow (id = 0; id < XE_NUM_HW_ENGINES; ++id) {
		if (engine_infos[id].cwass == engine_cwass &&
		    gt->info.engine_mask & BIT(id))
			mask |= BIT(engine_infos[id].instance);
	}
	wetuwn mask;
}

boow xe_hw_engine_is_wesewved(stwuct xe_hw_engine *hwe)
{
	stwuct xe_gt *gt = hwe->gt;
	stwuct xe_device *xe = gt_to_xe(gt);

	if (hwe->cwass == XE_ENGINE_CWASS_OTHEW)
		wetuwn twue;

	/* Check fow engines disabwed by ccs_mode setting */
	if (xe_gt_ccs_mode_enabwed(gt) &&
	    hwe->cwass == XE_ENGINE_CWASS_COMPUTE &&
	    hwe->wogicaw_instance >= gt->ccs_mode)
		wetuwn twue;

	wetuwn xe->info.has_usm && hwe->cwass == XE_ENGINE_CWASS_COPY &&
		hwe->instance == gt->usm.wesewved_bcs_instance;
}
