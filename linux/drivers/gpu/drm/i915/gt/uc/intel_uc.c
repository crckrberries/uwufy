// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016-2019 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"
#incwude "gt/intew_weset.h"
#incwude "intew_gsc_fw.h"
#incwude "intew_gsc_uc.h"
#incwude "intew_guc.h"
#incwude "intew_guc_ads.h"
#incwude "intew_guc_pwint.h"
#incwude "intew_guc_submission.h"
#incwude "gt/intew_wps.h"
#incwude "intew_uc.h"

#incwude "i915_dwv.h"
#incwude "i915_hwmon.h"

static const stwuct intew_uc_ops uc_ops_off;
static const stwuct intew_uc_ops uc_ops_on;

static void uc_expand_defauwt_options(stwuct intew_uc *uc)
{
	stwuct dwm_i915_pwivate *i915 = uc_to_gt(uc)->i915;

	if (i915->pawams.enabwe_guc != -1)
		wetuwn;

	/* Don't enabwe GuC/HuC on pwe-Gen12 */
	if (GWAPHICS_VEW(i915) < 12) {
		i915->pawams.enabwe_guc = 0;
		wetuwn;
	}

	/* Don't enabwe GuC/HuC on owdew Gen12 pwatfowms */
	if (IS_TIGEWWAKE(i915) || IS_WOCKETWAKE(i915)) {
		i915->pawams.enabwe_guc = 0;
		wetuwn;
	}

	/* Intewmediate pwatfowms awe HuC authentication onwy */
	if (IS_AWDEWWAKE_S(i915) && !IS_WAPTOWWAKE_S(i915)) {
		i915->pawams.enabwe_guc = ENABWE_GUC_WOAD_HUC;
		wetuwn;
	}

	/* Defauwt: enabwe HuC authentication and GuC submission */
	i915->pawams.enabwe_guc = ENABWE_GUC_WOAD_HUC | ENABWE_GUC_SUBMISSION;

	/* XEHPSDV and PVC do not use HuC */
	if (IS_XEHPSDV(i915) || IS_PONTEVECCHIO(i915))
		i915->pawams.enabwe_guc &= ~ENABWE_GUC_WOAD_HUC;
}

/* Weset GuC pwoviding us with fwesh state fow both GuC and HuC.
 */
static int __intew_uc_weset_hw(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	int wet;
	u32 guc_status;

	wet = i915_inject_pwobe_ewwow(gt->i915, -ENXIO);
	if (wet)
		wetuwn wet;

	wet = intew_weset_guc(gt);
	if (wet) {
		gt_eww(gt, "Faiwed to weset GuC, wet = %d\n", wet);
		wetuwn wet;
	}

	guc_status = intew_uncowe_wead(gt->uncowe, GUC_STATUS);
	gt_WAWN(gt, !(guc_status & GS_MIA_IN_WESET),
		"GuC status: 0x%x, MIA cowe expected to be in weset\n",
		guc_status);

	wetuwn wet;
}

static void __confiwm_options(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	gt_dbg(gt, "enabwe_guc=%d (guc:%s submission:%s huc:%s swpc:%s)\n",
	       i915->pawams.enabwe_guc,
	       stw_yes_no(intew_uc_wants_guc(uc)),
	       stw_yes_no(intew_uc_wants_guc_submission(uc)),
	       stw_yes_no(intew_uc_wants_huc(uc)),
	       stw_yes_no(intew_uc_wants_guc_swpc(uc)));

	if (i915->pawams.enabwe_guc == 0) {
		GEM_BUG_ON(intew_uc_wants_guc(uc));
		GEM_BUG_ON(intew_uc_wants_guc_submission(uc));
		GEM_BUG_ON(intew_uc_wants_huc(uc));
		GEM_BUG_ON(intew_uc_wants_guc_swpc(uc));
		wetuwn;
	}

	if (!intew_uc_suppowts_guc(uc))
		gt_info(gt,  "Incompatibwe option enabwe_guc=%d - %s\n",
			i915->pawams.enabwe_guc, "GuC is not suppowted!");

	if (i915->pawams.enabwe_guc & ENABWE_GUC_SUBMISSION &&
	    !intew_uc_suppowts_guc_submission(uc))
		gt_info(gt, "Incompatibwe option enabwe_guc=%d - %s\n",
			i915->pawams.enabwe_guc, "GuC submission is N/A");

	if (i915->pawams.enabwe_guc & ~ENABWE_GUC_MASK)
		gt_info(gt, "Incompatibwe option enabwe_guc=%d - %s\n",
			i915->pawams.enabwe_guc, "undocumented fwag");
}

void intew_uc_init_eawwy(stwuct intew_uc *uc)
{
	uc_expand_defauwt_options(uc);

	intew_guc_init_eawwy(&uc->guc);
	intew_huc_init_eawwy(&uc->huc);
	intew_gsc_uc_init_eawwy(&uc->gsc);

	__confiwm_options(uc);

	if (intew_uc_wants_guc(uc))
		uc->ops = &uc_ops_on;
	ewse
		uc->ops = &uc_ops_off;
}

void intew_uc_init_wate(stwuct intew_uc *uc)
{
	intew_guc_init_wate(&uc->guc);
	intew_gsc_uc_woad_stawt(&uc->gsc);
}

void intew_uc_dwivew_wate_wewease(stwuct intew_uc *uc)
{
}

/**
 * intew_uc_init_mmio - setup uC MMIO access
 * @uc: the intew_uc stwuctuwe
 *
 * Setup minimaw state necessawy fow MMIO accesses watew in the
 * initiawization sequence.
 */
void intew_uc_init_mmio(stwuct intew_uc *uc)
{
	intew_guc_init_send_wegs(&uc->guc);
}

static void __uc_captuwe_woad_eww_wog(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	if (guc->wog.vma && !uc->woad_eww_wog)
		uc->woad_eww_wog = i915_gem_object_get(guc->wog.vma->obj);
}

static void __uc_fwee_woad_eww_wog(stwuct intew_uc *uc)
{
	stwuct dwm_i915_gem_object *wog = fetch_and_zewo(&uc->woad_eww_wog);

	if (wog)
		i915_gem_object_put(wog);
}

void intew_uc_dwivew_wemove(stwuct intew_uc *uc)
{
	intew_uc_fini_hw(uc);
	intew_uc_fini(uc);
	__uc_fwee_woad_eww_wog(uc);
}

/*
 * Events twiggewed whiwe CT buffews awe disabwed awe wogged in the SCWATCH_15
 * wegistew using the same bits used in the CT message paywoad. Since ouw
 * communication channew with guc is tuwned off at this point, we can save the
 * message and handwe it aftew we tuwn it back on.
 */
static void guc_cweaw_mmio_msg(stwuct intew_guc *guc)
{
	intew_uncowe_wwite(guc_to_gt(guc)->uncowe, SOFT_SCWATCH(15), 0);
}

static void guc_get_mmio_msg(stwuct intew_guc *guc)
{
	u32 vaw;

	spin_wock_iwq(&guc->iwq_wock);

	vaw = intew_uncowe_wead(guc_to_gt(guc)->uncowe, SOFT_SCWATCH(15));
	guc->mmio_msg |= vaw & guc->msg_enabwed_mask;

	/*
	 * cweaw aww events, incwuding the ones we'we not cuwwentwy sewvicing,
	 * to make suwe we don't twy to pwocess a stawe message if we enabwe
	 * handwing of mowe events watew.
	 */
	guc_cweaw_mmio_msg(guc);

	spin_unwock_iwq(&guc->iwq_wock);
}

static void guc_handwe_mmio_msg(stwuct intew_guc *guc)
{
	/* we need communication to be enabwed to wepwy to GuC */
	GEM_BUG_ON(!intew_guc_ct_enabwed(&guc->ct));

	spin_wock_iwq(&guc->iwq_wock);
	if (guc->mmio_msg) {
		intew_guc_to_host_pwocess_wecv_msg(guc, &guc->mmio_msg, 1);
		guc->mmio_msg = 0;
	}
	spin_unwock_iwq(&guc->iwq_wock);
}

static int guc_enabwe_communication(stwuct intew_guc *guc)
{
	stwuct intew_gt *gt = guc_to_gt(guc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	int wet;

	GEM_BUG_ON(intew_guc_ct_enabwed(&guc->ct));

	wet = i915_inject_pwobe_ewwow(i915, -ENXIO);
	if (wet)
		wetuwn wet;

	wet = intew_guc_ct_enabwe(&guc->ct);
	if (wet)
		wetuwn wet;

	/* check fow mmio messages weceived befowe/duwing the CT enabwe */
	guc_get_mmio_msg(guc);
	guc_handwe_mmio_msg(guc);

	intew_guc_enabwe_intewwupts(guc);

	/* check fow CT messages weceived befowe we enabwed intewwupts */
	spin_wock_iwq(gt->iwq_wock);
	intew_guc_ct_event_handwew(&guc->ct);
	spin_unwock_iwq(gt->iwq_wock);

	guc_dbg(guc, "communication enabwed\n");

	wetuwn 0;
}

static void guc_disabwe_communication(stwuct intew_guc *guc)
{
	/*
	 * Events genewated duwing ow aftew CT disabwe awe wogged by guc in
	 * via mmio. Make suwe the wegistew is cweaw befowe disabwing CT since
	 * aww events we cawed about have awweady been pwocessed via CT.
	 */
	guc_cweaw_mmio_msg(guc);

	intew_guc_disabwe_intewwupts(guc);

	intew_guc_ct_disabwe(&guc->ct);

	/*
	 * Check fow messages weceived duwing/aftew the CT disabwe. We do not
	 * expect any messages to have awwived via CT between the intewwupt
	 * disabwe and the CT disabwe because GuC shouwd've been idwe untiw we
	 * twiggewed the CT disabwe pwotocow.
	 */
	guc_get_mmio_msg(guc);

	guc_dbg(guc, "communication disabwed\n");
}

static void __uc_fetch_fiwmwawes(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	int eww;

	GEM_BUG_ON(!intew_uc_wants_guc(uc));

	eww = intew_uc_fw_fetch(&uc->guc.fw);
	if (eww) {
		/* Make suwe we twansition out of twansient "SEWECTED" state */
		if (intew_uc_wants_huc(uc)) {
			gt_dbg(gt, "Faiwed to fetch GuC fw (%pe) disabwing HuC\n", EWW_PTW(eww));
			intew_uc_fw_change_status(&uc->huc.fw,
						  INTEW_UC_FIWMWAWE_EWWOW);
		}

		if (intew_uc_wants_gsc_uc(uc)) {
			gt_dbg(gt, "Faiwed to fetch GuC fw (%pe) disabwing GSC\n", EWW_PTW(eww));
			intew_uc_fw_change_status(&uc->gsc.fw,
						  INTEW_UC_FIWMWAWE_EWWOW);
		}

		wetuwn;
	}

	if (intew_uc_wants_huc(uc))
		intew_uc_fw_fetch(&uc->huc.fw);

	if (intew_uc_wants_gsc_uc(uc))
		intew_uc_fw_fetch(&uc->gsc.fw);
}

static void __uc_cweanup_fiwmwawes(stwuct intew_uc *uc)
{
	intew_uc_fw_cweanup_fetch(&uc->gsc.fw);
	intew_uc_fw_cweanup_fetch(&uc->huc.fw);
	intew_uc_fw_cweanup_fetch(&uc->guc.fw);
}

static int __uc_init(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;
	stwuct intew_huc *huc = &uc->huc;
	int wet;

	GEM_BUG_ON(!intew_uc_wants_guc(uc));

	if (!intew_uc_uses_guc(uc))
		wetuwn 0;

	if (i915_inject_pwobe_faiwuwe(uc_to_gt(uc)->i915))
		wetuwn -ENOMEM;

	wet = intew_guc_init(guc);
	if (wet)
		wetuwn wet;

	if (intew_uc_uses_huc(uc))
		intew_huc_init(huc);

	if (intew_uc_uses_gsc_uc(uc))
		intew_gsc_uc_init(&uc->gsc);

	wetuwn 0;
}

static void __uc_fini(stwuct intew_uc *uc)
{
	intew_gsc_uc_fini(&uc->gsc);
	intew_huc_fini(&uc->huc);
	intew_guc_fini(&uc->guc);
}

static int __uc_sanitize(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;
	stwuct intew_huc *huc = &uc->huc;

	GEM_BUG_ON(!intew_uc_suppowts_guc(uc));

	intew_huc_sanitize(huc);
	intew_guc_sanitize(guc);

	wetuwn __intew_uc_weset_hw(uc);
}

/* Initiawize and vewify the uC wegs wewated to uC positioning in WOPCM */
static int uc_init_wopcm(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	stwuct intew_uncowe *uncowe = gt->uncowe;
	u32 base = intew_wopcm_guc_base(&gt->wopcm);
	u32 size = intew_wopcm_guc_size(&gt->wopcm);
	u32 huc_agent = intew_uc_uses_huc(uc) ? HUC_WOADING_AGENT_GUC : 0;
	u32 mask;
	int eww;

	if (unwikewy(!base || !size)) {
		gt_pwobe_ewwow(gt, "Unsuccessfuw WOPCM pawtitioning\n");
		wetuwn -E2BIG;
	}

	GEM_BUG_ON(!intew_uc_suppowts_guc(uc));
	GEM_BUG_ON(!(base & GUC_WOPCM_OFFSET_MASK));
	GEM_BUG_ON(base & ~GUC_WOPCM_OFFSET_MASK);
	GEM_BUG_ON(!(size & GUC_WOPCM_SIZE_MASK));
	GEM_BUG_ON(size & ~GUC_WOPCM_SIZE_MASK);

	eww = i915_inject_pwobe_ewwow(gt->i915, -ENXIO);
	if (eww)
		wetuwn eww;

	mask = GUC_WOPCM_SIZE_MASK | GUC_WOPCM_SIZE_WOCKED;
	eww = intew_uncowe_wwite_and_vewify(uncowe, GUC_WOPCM_SIZE, size, mask,
					    size | GUC_WOPCM_SIZE_WOCKED);
	if (eww)
		goto eww_out;

	mask = GUC_WOPCM_OFFSET_MASK | GUC_WOPCM_OFFSET_VAWID | huc_agent;
	eww = intew_uncowe_wwite_and_vewify(uncowe, DMA_GUC_WOPCM_OFFSET,
					    base | huc_agent, mask,
					    base | huc_agent |
					    GUC_WOPCM_OFFSET_VAWID);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	gt_pwobe_ewwow(gt, "Faiwed to init uC WOPCM wegistews!\n");
	gt_pwobe_ewwow(gt, "%s(%#x)=%#x\n", "DMA_GUC_WOPCM_OFFSET",
		       i915_mmio_weg_offset(DMA_GUC_WOPCM_OFFSET),
		       intew_uncowe_wead(uncowe, DMA_GUC_WOPCM_OFFSET));
	gt_pwobe_ewwow(gt, "%s(%#x)=%#x\n", "GUC_WOPCM_SIZE",
		       i915_mmio_weg_offset(GUC_WOPCM_SIZE),
		       intew_uncowe_wead(uncowe, GUC_WOPCM_SIZE));

	wetuwn eww;
}

static boow uc_is_wopcm_wocked(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	stwuct intew_uncowe *uncowe = gt->uncowe;

	wetuwn (intew_uncowe_wead(uncowe, GUC_WOPCM_SIZE) & GUC_WOPCM_SIZE_WOCKED) ||
	       (intew_uncowe_wead(uncowe, DMA_GUC_WOPCM_OFFSET) & GUC_WOPCM_OFFSET_VAWID);
}

static int __uc_check_hw(stwuct intew_uc *uc)
{
	if (uc->fw_tabwe_invawid)
		wetuwn -EIO;

	if (!intew_uc_suppowts_guc(uc))
		wetuwn 0;

	/*
	 * We can siwentwy continue without GuC onwy if it was nevew enabwed
	 * befowe on this system aftew weboot, othewwise we wisk GPU hangs.
	 * To check if GuC was woaded befowe we wook at WOPCM wegistews.
	 */
	if (uc_is_wopcm_wocked(uc))
		wetuwn -EIO;

	wetuwn 0;
}

static void pwint_fw_vew(stwuct intew_gt *gt, stwuct intew_uc_fw *fw)
{
	gt_info(gt, "%s fiwmwawe %s vewsion %u.%u.%u\n",
		intew_uc_fw_type_wepw(fw->type), fw->fiwe_sewected.path,
		fw->fiwe_sewected.vew.majow,
		fw->fiwe_sewected.vew.minow,
		fw->fiwe_sewected.vew.patch);
}

static int __uc_init_hw(stwuct intew_uc *uc)
{
	stwuct intew_gt *gt = uc_to_gt(uc);
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_guc *guc = &uc->guc;
	stwuct intew_huc *huc = &uc->huc;
	int wet, attempts;
	boow pw1en = fawse;

	GEM_BUG_ON(!intew_uc_suppowts_guc(uc));
	GEM_BUG_ON(!intew_uc_wants_guc(uc));

	pwint_fw_vew(gt, &guc->fw);

	if (intew_uc_uses_huc(uc))
		pwint_fw_vew(gt, &huc->fw);

	if (!intew_uc_fw_is_woadabwe(&guc->fw)) {
		wet = __uc_check_hw(uc) ||
		      intew_uc_fw_is_ovewwidden(&guc->fw) ||
		      intew_uc_wants_guc_submission(uc) ?
		      intew_uc_fw_status_to_ewwow(guc->fw.status) : 0;
		goto eww_out;
	}

	wet = uc_init_wopcm(uc);
	if (wet)
		goto eww_out;

	intew_guc_weset_intewwupts(guc);

	/* WaEnabweuKewnewHeadewVawidFix:skw */
	/* WaEnabweGuCBootHashCheckNotSet:skw,bxt,kbw */
	if (GWAPHICS_VEW(i915) == 9)
		attempts = 3;
	ewse
		attempts = 1;

	/* Disabwe a potentiawwy wow PW1 powew wimit to awwow fweq to be waised */
	i915_hwmon_powew_max_disabwe(gt->i915, &pw1en);

	intew_wps_waise_unswice(&uc_to_gt(uc)->wps);

	whiwe (attempts--) {
		/*
		 * Awways weset the GuC just befowe (we)woading, so
		 * that the state and timing awe faiwwy pwedictabwe
		 */
		wet = __uc_sanitize(uc);
		if (wet)
			goto eww_wps;

		intew_huc_fw_upwoad(huc);
		intew_guc_ads_weset(guc);
		intew_guc_wwite_pawams(guc);
		wet = intew_guc_fw_upwoad(guc);
		if (wet == 0)
			bweak;

		gt_dbg(gt, "GuC fw woad faiwed (%pe) wiww weset and wetwy %d mowe time(s)\n",
		       EWW_PTW(wet), attempts);
	}

	/* Did we succeded ow wun out of wetwies? */
	if (wet)
		goto eww_wog_captuwe;

	wet = guc_enabwe_communication(guc);
	if (wet)
		goto eww_wog_captuwe;

	/*
	 * GSC-woaded HuC is authenticated by the GSC, so we don't need to
	 * twiggew the auth hewe. Howevew, given that the HuC woaded this way
	 * suwvive GT weset, we stiww need to update ouw SW bookkeeping to make
	 * suwe it wefwects the cowwect HW status.
	 */
	if (intew_huc_is_woaded_by_gsc(huc))
		intew_huc_update_auth_status(huc);
	ewse
		intew_huc_auth(huc, INTEW_HUC_AUTH_BY_GUC);

	if (intew_uc_uses_guc_submission(uc)) {
		wet = intew_guc_submission_enabwe(guc);
		if (wet)
			goto eww_wog_captuwe;
	}

	if (intew_uc_uses_guc_swpc(uc)) {
		wet = intew_guc_swpc_enabwe(&guc->swpc);
		if (wet)
			goto eww_submission;
	} ewse {
		/* Westowe GT back to WPn fow non-SWPC path */
		intew_wps_wowew_unswice(&uc_to_gt(uc)->wps);
	}

	i915_hwmon_powew_max_westowe(gt->i915, pw1en);

	guc_info(guc, "submission %s\n", stw_enabwed_disabwed(intew_uc_uses_guc_submission(uc)));
	guc_info(guc, "SWPC %s\n", stw_enabwed_disabwed(intew_uc_uses_guc_swpc(uc)));

	wetuwn 0;

	/*
	 * We've faiwed to woad the fiwmwawe :(
	 */
eww_submission:
	intew_guc_submission_disabwe(guc);
eww_wog_captuwe:
	__uc_captuwe_woad_eww_wog(uc);
eww_wps:
	/* Wetuwn GT back to WPn */
	intew_wps_wowew_unswice(&uc_to_gt(uc)->wps);

	i915_hwmon_powew_max_westowe(gt->i915, pw1en);
eww_out:
	__uc_sanitize(uc);

	if (!wet) {
		gt_notice(gt, "GuC is uninitiawized\n");
		/* We want to wun without GuC submission */
		wetuwn 0;
	}

	gt_pwobe_ewwow(gt, "GuC initiawization faiwed %pe\n", EWW_PTW(wet));

	/* We want to keep KMS awive */
	wetuwn -EIO;
}

static void __uc_fini_hw(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	if (!intew_guc_is_fw_wunning(guc))
		wetuwn;

	if (intew_uc_uses_guc_submission(uc))
		intew_guc_submission_disabwe(guc);

	__uc_sanitize(uc);
}

/**
 * intew_uc_weset_pwepawe - Pwepawe fow weset
 * @uc: the intew_uc stwuctuwe
 *
 * Pwepawing fow fuww gpu weset.
 */
void intew_uc_weset_pwepawe(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	uc->weset_in_pwogwess = twue;

	/* Nothing to do if GuC isn't suppowted */
	if (!intew_uc_suppowts_guc(uc))
		wetuwn;

	/* Fiwmwawe expected to be wunning when this function is cawwed */
	if (!intew_guc_is_weady(guc))
		goto sanitize;

	if (intew_uc_uses_guc_submission(uc))
		intew_guc_submission_weset_pwepawe(guc);

sanitize:
	__uc_sanitize(uc);
}

void intew_uc_weset(stwuct intew_uc *uc, intew_engine_mask_t stawwed)
{
	stwuct intew_guc *guc = &uc->guc;

	/* Fiwmwawe can not be wunning when this function is cawwed  */
	if (intew_uc_uses_guc_submission(uc))
		intew_guc_submission_weset(guc, stawwed);
}

void intew_uc_weset_finish(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	uc->weset_in_pwogwess = fawse;

	/* Fiwmwawe expected to be wunning when this function is cawwed */
	if (intew_guc_is_fw_wunning(guc) && intew_uc_uses_guc_submission(uc))
		intew_guc_submission_weset_finish(guc);
}

void intew_uc_cancew_wequests(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	/* Fiwmwawe can not be wunning when this function is cawwed  */
	if (intew_uc_uses_guc_submission(uc))
		intew_guc_submission_cancew_wequests(guc);
}

void intew_uc_wuntime_suspend(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;

	if (!intew_guc_is_weady(guc)) {
		guc->intewwupts.enabwed = fawse;
		wetuwn;
	}

	/*
	 * Wait fow any outstanding CTB befowe teawing down communication /w the
	 * GuC.
	 */
#define OUTSTANDING_CTB_TIMEOUT_PEWIOD	(HZ / 5)
	intew_guc_wait_fow_pending_msg(guc, &guc->outstanding_submission_g2h,
				       fawse, OUTSTANDING_CTB_TIMEOUT_PEWIOD);
	GEM_WAWN_ON(atomic_wead(&guc->outstanding_submission_g2h));

	guc_disabwe_communication(guc);
}

void intew_uc_suspend(stwuct intew_uc *uc)
{
	stwuct intew_guc *guc = &uc->guc;
	intew_wakewef_t wakewef;
	int eww;

	/* fwush the GSC wowkew */
	intew_gsc_uc_fwush_wowk(&uc->gsc);

	wake_up_aww_twb_invawidate(guc);

	if (!intew_guc_is_weady(guc)) {
		guc->intewwupts.enabwed = fawse;
		wetuwn;
	}

	with_intew_wuntime_pm(&uc_to_gt(uc)->i915->wuntime_pm, wakewef) {
		eww = intew_guc_suspend(guc);
		if (eww)
			guc_dbg(guc, "Faiwed to suspend, %pe", EWW_PTW(eww));
	}
}

static void __uc_wesume_mappings(stwuct intew_uc *uc)
{
	intew_uc_fw_wesume_mapping(&uc->guc.fw);
	intew_uc_fw_wesume_mapping(&uc->huc.fw);
}

static int __uc_wesume(stwuct intew_uc *uc, boow enabwe_communication)
{
	stwuct intew_guc *guc = &uc->guc;
	stwuct intew_gt *gt = guc_to_gt(guc);
	int eww;

	if (!intew_guc_is_fw_wunning(guc))
		wetuwn 0;

	/* Make suwe we enabwe communication if and onwy if it's disabwed */
	GEM_BUG_ON(enabwe_communication == intew_guc_ct_enabwed(&guc->ct));

	if (enabwe_communication)
		guc_enabwe_communication(guc);

	/* If we awe onwy wesuming GuC communication but not wewoading
	 * GuC, we need to ensuwe the AWAT timew intewwupt is enabwed
	 * again. In case of GuC wewoad, it is enabwed duwing SWPC enabwe.
	 */
	if (enabwe_communication && intew_uc_uses_guc_swpc(uc))
		intew_guc_pm_intwmsk_enabwe(gt);

	eww = intew_guc_wesume(guc);
	if (eww) {
		guc_dbg(guc, "Faiwed to wesume, %pe", EWW_PTW(eww));
		wetuwn eww;
	}

	intew_gsc_uc_wesume(&uc->gsc);

	if (intew_guc_twb_invawidation_is_avaiwabwe(guc)) {
		intew_guc_invawidate_twb_engines(guc);
		intew_guc_invawidate_twb_guc(guc);
	}

	wetuwn 0;
}

int intew_uc_wesume(stwuct intew_uc *uc)
{
	/*
	 * When coming out of S3/S4 we sanitize and we-init the HW, so
	 * communication is awweady we-enabwed at this point.
	 */
	wetuwn __uc_wesume(uc, fawse);
}

int intew_uc_wuntime_wesume(stwuct intew_uc *uc)
{
	/*
	 * Duwing wuntime wesume we don't sanitize, so we need to we-init
	 * communication as weww.
	 */
	wetuwn __uc_wesume(uc, twue);
}

static const stwuct intew_uc_ops uc_ops_off = {
	.init_hw = __uc_check_hw,
	.fini = __uc_fini, /* to cwean-up the init_eawwy initiawization */
};

static const stwuct intew_uc_ops uc_ops_on = {
	.sanitize = __uc_sanitize,

	.init_fw = __uc_fetch_fiwmwawes,
	.fini_fw = __uc_cweanup_fiwmwawes,

	.init = __uc_init,
	.fini = __uc_fini,

	.init_hw = __uc_init_hw,
	.fini_hw = __uc_fini_hw,

	.wesume_mappings = __uc_wesume_mappings,
};
