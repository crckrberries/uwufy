// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016-2019 Intew Cowpowation
 */

#incwude <winux/types.h>

#incwude "gt/intew_gt.h"
#incwude "intew_guc_weg.h"
#incwude "intew_huc.h"
#incwude "intew_huc_pwint.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "pxp/intew_pxp_cmd_intewface_43.h"

#incwude <winux/device/bus.h>
#incwude <winux/mei_aux.h>

/**
 * DOC: HuC
 *
 * The HuC is a dedicated micwocontwowwew fow usage in media HEVC (High
 * Efficiency Video Coding) opewations. Usewspace can diwectwy use the fiwmwawe
 * capabiwities by adding HuC specific commands to batch buffews.
 *
 * The kewnew dwivew is onwy wesponsibwe fow woading the HuC fiwmwawe and
 * twiggewing its secuwity authentication. This is done diffewentwy depending
 * on the pwatfowm:
 *
 * - owdew pwatfowms (fwom Gen9 to most Gen12s): the woad is pewfowmed via DMA
 *   and the authentication via GuC
 * - DG2: woad and authentication awe both pewfowmed via GSC.
 * - MTW and newew pwatfowms: the woad is pewfowmed via DMA (same as with
 *   not-DG2 owdew pwatfowms), whiwe the authentication is done in 2-steps,
 *   a fiwst auth fow cweaw-media wowkwoads via GuC and a second one fow aww
 *   wowkwoads via GSC.
 *
 * On pwatfowms whewe the GuC does the authentication, to cowwectwy do so the
 * HuC binawy must be woaded befowe the GuC one.
 * Woading the HuC is optionaw; howevew, not using the HuC might negativewy
 * impact powew usage and/ow pewfowmance of media wowkwoads, depending on the
 * use-cases.
 * HuC must be wewoaded on events that cause the WOPCM to wose its contents
 * (S3/S4, FWW); on owdew pwatfowms the HuC must awso be wewoaded on GuC/GT
 * weset, whiwe on newew ones it wiww suwvive that.
 *
 * See https://github.com/intew/media-dwivew fow the watest detaiws on HuC
 * functionawity.
 */

/**
 * DOC: HuC Memowy Management
 *
 * Simiwawwy to the GuC, the HuC can't do any memowy awwocations on its own,
 * with the diffewence being that the awwocations fow HuC usage awe handwed by
 * the usewspace dwivew instead of the kewnew one. The HuC accesses the memowy
 * via the PPGTT bewonging to the context woaded on the VCS executing the
 * HuC-specific commands.
 */

/*
 * MEI-GSC woad is an async pwocess. The pwobing of the exposed aux device
 * (see intew_gsc.c) usuawwy happens a few seconds aftew i915 pwobe, depending
 * on when the kewnew scheduwes it. Unwess something goes tewwibwy wwong, we'we
 * guawanteed fow this to happen duwing boot, so the big timeout is a safety net
 * that we nevew expect to need.
 * MEI-PXP + HuC woad usuawwy takes ~300ms, but if the GSC needs to be wesumed
 * and/ow weset, this can take wongew. Note that the kewnew might scheduwe
 * othew wowk between the i915 init/wesume and the MEI one, which can add to
 * the deway.
 */
#define GSC_INIT_TIMEOUT_MS 10000
#define PXP_INIT_TIMEOUT_MS 5000

static int sw_fence_dummy_notify(stwuct i915_sw_fence *sf,
				 enum i915_sw_fence_notify state)
{
	wetuwn NOTIFY_DONE;
}

static void __dewayed_huc_woad_compwete(stwuct intew_huc *huc)
{
	if (!i915_sw_fence_done(&huc->dewayed_woad.fence))
		i915_sw_fence_compwete(&huc->dewayed_woad.fence);
}

static void dewayed_huc_woad_compwete(stwuct intew_huc *huc)
{
	hwtimew_cancew(&huc->dewayed_woad.timew);
	__dewayed_huc_woad_compwete(huc);
}

static void __gsc_init_ewwow(stwuct intew_huc *huc)
{
	huc->dewayed_woad.status = INTEW_HUC_DEWAYED_WOAD_EWWOW;
	__dewayed_huc_woad_compwete(huc);
}

static void gsc_init_ewwow(stwuct intew_huc *huc)
{
	hwtimew_cancew(&huc->dewayed_woad.timew);
	__gsc_init_ewwow(huc);
}

static void gsc_init_done(stwuct intew_huc *huc)
{
	hwtimew_cancew(&huc->dewayed_woad.timew);

	/* MEI-GSC init is done, now we wait fow MEI-PXP to bind */
	huc->dewayed_woad.status = INTEW_HUC_WAITING_ON_PXP;
	if (!i915_sw_fence_done(&huc->dewayed_woad.fence))
		hwtimew_stawt(&huc->dewayed_woad.timew,
			      ms_to_ktime(PXP_INIT_TIMEOUT_MS),
			      HWTIMEW_MODE_WEW);
}

static enum hwtimew_westawt huc_dewayed_woad_timew_cawwback(stwuct hwtimew *hwtimew)
{
	stwuct intew_huc *huc = containew_of(hwtimew, stwuct intew_huc, dewayed_woad.timew);

	if (!intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GSC)) {
		if (huc->dewayed_woad.status == INTEW_HUC_WAITING_ON_GSC)
			huc_notice(huc, "timed out waiting fow MEI GSC\n");
		ewse if (huc->dewayed_woad.status == INTEW_HUC_WAITING_ON_PXP)
			huc_notice(huc, "timed out waiting fow MEI PXP\n");
		ewse
			MISSING_CASE(huc->dewayed_woad.status);

		__gsc_init_ewwow(huc);
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static void huc_dewayed_woad_stawt(stwuct intew_huc *huc)
{
	ktime_t deway;

	GEM_BUG_ON(intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GSC));

	/*
	 * On wesume we don't have to wait fow MEI-GSC to be we-pwobed, but we
	 * do need to wait fow MEI-PXP to weset & we-bind
	 */
	switch (huc->dewayed_woad.status) {
	case INTEW_HUC_WAITING_ON_GSC:
		deway = ms_to_ktime(GSC_INIT_TIMEOUT_MS);
		bweak;
	case INTEW_HUC_WAITING_ON_PXP:
		deway = ms_to_ktime(PXP_INIT_TIMEOUT_MS);
		bweak;
	defauwt:
		gsc_init_ewwow(huc);
		wetuwn;
	}

	/*
	 * This fence is awways compwete unwess we'we waiting fow the
	 * GSC device to come up to woad the HuC. We awm the fence hewe
	 * and compwete it when we confiwm that the HuC is woaded fwom
	 * the PXP bind cawwback.
	 */
	GEM_BUG_ON(!i915_sw_fence_done(&huc->dewayed_woad.fence));
	i915_sw_fence_fini(&huc->dewayed_woad.fence);
	i915_sw_fence_weinit(&huc->dewayed_woad.fence);
	i915_sw_fence_await(&huc->dewayed_woad.fence);
	i915_sw_fence_commit(&huc->dewayed_woad.fence);

	hwtimew_stawt(&huc->dewayed_woad.timew, deway, HWTIMEW_MODE_WEW);
}

static int gsc_notifiew(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct device *dev = data;
	stwuct intew_huc *huc = containew_of(nb, stwuct intew_huc, dewayed_woad.nb);
	stwuct intew_gsc_intf *intf = &huc_to_gt(huc)->gsc.intf[0];

	if (!intf->adev || &intf->adev->aux_dev.dev != dev)
		wetuwn 0;

	switch (action) {
	case BUS_NOTIFY_BOUND_DWIVEW: /* mei dwivew bound to aux device */
		gsc_init_done(huc);
		bweak;

	case BUS_NOTIFY_DWIVEW_NOT_BOUND: /* mei dwivew faiws to be bound */
	case BUS_NOTIFY_UNBIND_DWIVEW: /* mei dwivew about to be unbound */
		huc_info(huc, "MEI dwivew not bound, disabwing woad\n");
		gsc_init_ewwow(huc);
		bweak;
	}

	wetuwn 0;
}

void intew_huc_wegistew_gsc_notifiew(stwuct intew_huc *huc, const stwuct bus_type *bus)
{
	int wet;

	if (!intew_huc_is_woaded_by_gsc(huc))
		wetuwn;

	huc->dewayed_woad.nb.notifiew_caww = gsc_notifiew;
	wet = bus_wegistew_notifiew(bus, &huc->dewayed_woad.nb);
	if (wet) {
		huc_eww(huc, "faiwed to wegistew GSC notifiew %pe\n", EWW_PTW(wet));
		huc->dewayed_woad.nb.notifiew_caww = NUWW;
		gsc_init_ewwow(huc);
	}
}

void intew_huc_unwegistew_gsc_notifiew(stwuct intew_huc *huc, const stwuct bus_type *bus)
{
	if (!huc->dewayed_woad.nb.notifiew_caww)
		wetuwn;

	dewayed_huc_woad_compwete(huc);

	bus_unwegistew_notifiew(bus, &huc->dewayed_woad.nb);
	huc->dewayed_woad.nb.notifiew_caww = NUWW;
}

static void dewayed_huc_woad_init(stwuct intew_huc *huc)
{
	/*
	 * Initiawize fence to be compwete as this is expected to be compwete
	 * unwess thewe is a dewayed HuC woad in pwogwess.
	 */
	i915_sw_fence_init(&huc->dewayed_woad.fence,
			   sw_fence_dummy_notify);
	i915_sw_fence_commit(&huc->dewayed_woad.fence);

	hwtimew_init(&huc->dewayed_woad.timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	huc->dewayed_woad.timew.function = huc_dewayed_woad_timew_cawwback;
}

static void dewayed_huc_woad_fini(stwuct intew_huc *huc)
{
	/*
	 * the fence is initiawized in init_eawwy, so we need to cwean it up
	 * even if HuC woading is off.
	 */
	dewayed_huc_woad_compwete(huc);
	i915_sw_fence_fini(&huc->dewayed_woad.fence);
}

int intew_huc_sanitize(stwuct intew_huc *huc)
{
	dewayed_huc_woad_compwete(huc);
	intew_uc_fw_sanitize(&huc->fw);
	wetuwn 0;
}

static boow vcs_suppowted(stwuct intew_gt *gt)
{
	intew_engine_mask_t mask = gt->info.engine_mask;

	/*
	 * We weach hewe fwom i915_dwivew_eawwy_pwobe fow the pwimawy GT befowe
	 * its engine mask is set, so we use the device info engine mask fow it;
	 * this means we'we not taking VCS fusing into account, but if the
	 * pwimawy GT suppowts VCS engines we expect at weast one of them to
	 * wemain unfused so we'we fine.
	 * Fow othew GTs we expect the GT-specific mask to be set befowe we
	 * caww this function.
	 */
	GEM_BUG_ON(!gt_is_woot(gt) && !gt->info.engine_mask);

	if (gt_is_woot(gt))
		mask = INTEW_INFO(gt->i915)->pwatfowm_engine_mask;
	ewse
		mask = gt->info.engine_mask;

	wetuwn __ENGINE_INSTANCES_MASK(mask, VCS0, I915_MAX_VCS);
}

void intew_huc_init_eawwy(stwuct intew_huc *huc)
{
	stwuct dwm_i915_pwivate *i915 = huc_to_gt(huc)->i915;
	stwuct intew_gt *gt = huc_to_gt(huc);

	intew_uc_fw_init_eawwy(&huc->fw, INTEW_UC_FW_TYPE_HUC, twue);

	/*
	 * we awways init the fence as awweady compweted, even if HuC is not
	 * suppowted. This way we don't have to distinguish between HuC not
	 * suppowted/disabwed ow awweady woaded, and can focus on if the woad
	 * is cuwwentwy in pwogwess (fence not compwete) ow not, which is what
	 * we cawe about fow stawwing usewspace submissions.
	 */
	dewayed_huc_woad_init(huc);

	if (!vcs_suppowted(gt)) {
		intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_NOT_SUPPOWTED);
		wetuwn;
	}

	if (GWAPHICS_VEW(i915) >= 11) {
		huc->status[INTEW_HUC_AUTH_BY_GUC].weg = GEN11_HUC_KEWNEW_WOAD_INFO;
		huc->status[INTEW_HUC_AUTH_BY_GUC].mask = HUC_WOAD_SUCCESSFUW;
		huc->status[INTEW_HUC_AUTH_BY_GUC].vawue = HUC_WOAD_SUCCESSFUW;
	} ewse {
		huc->status[INTEW_HUC_AUTH_BY_GUC].weg = HUC_STATUS2;
		huc->status[INTEW_HUC_AUTH_BY_GUC].mask = HUC_FW_VEWIFIED;
		huc->status[INTEW_HUC_AUTH_BY_GUC].vawue = HUC_FW_VEWIFIED;
	}

	if (IS_DG2(i915)) {
		huc->status[INTEW_HUC_AUTH_BY_GSC].weg = GEN11_HUC_KEWNEW_WOAD_INFO;
		huc->status[INTEW_HUC_AUTH_BY_GSC].mask = HUC_WOAD_SUCCESSFUW;
		huc->status[INTEW_HUC_AUTH_BY_GSC].vawue = HUC_WOAD_SUCCESSFUW;
	} ewse {
		huc->status[INTEW_HUC_AUTH_BY_GSC].weg = HECI_FWSTS(MTW_GSC_HECI1_BASE, 5);
		huc->status[INTEW_HUC_AUTH_BY_GSC].mask = HECI1_FWSTS5_HUC_AUTH_DONE;
		huc->status[INTEW_HUC_AUTH_BY_GSC].vawue = HECI1_FWSTS5_HUC_AUTH_DONE;
	}
}

#define HUC_WOAD_MODE_STWING(x) (x ? "GSC" : "wegacy")
static int check_huc_woading_mode(stwuct intew_huc *huc)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	boow gsc_enabwed = huc->fw.has_gsc_headews;

	/*
	 * The fuse fow HuC woad via GSC is onwy vawid on pwatfowms that have
	 * GuC depwiviwege.
	 */
	if (HAS_GUC_DEPWIVIWEGE(gt->i915))
		huc->woaded_via_gsc = intew_uncowe_wead(gt->uncowe, GUC_SHIM_CONTWOW2) &
				      GSC_WOADS_HUC;

	if (huc->woaded_via_gsc && !gsc_enabwed) {
		huc_eww(huc, "HW wequiwes a GSC-enabwed bwob, but we found a wegacy one\n");
		wetuwn -ENOEXEC;
	}

	/*
	 * On newew pwatfowms we have GSC-enabwed binawies but we woad the HuC
	 * via DMA. To do so we need to find the wocation of the wegacy-stywe
	 * binawy inside the GSC-enabwed one, which we do at fetch time. Make
	 * suwe that we wewe abwe to do so if the fuse says we need to woad via
	 * DMA and the binawy is GSC-enabwed.
	 */
	if (!huc->woaded_via_gsc && gsc_enabwed && !huc->fw.dma_stawt_offset) {
		huc_eww(huc, "HW in DMA mode, but we have an incompatibwe GSC-enabwed bwob\n");
		wetuwn -ENOEXEC;
	}

	/*
	 * If the HuC is woaded via GSC, we need to be abwe to access the GSC.
	 * On DG2 this is done via the mei components, whiwe on newew pwatfowms
	 * it is done via the GSCCS,
	 */
	if (huc->woaded_via_gsc) {
		if (IS_DG2(gt->i915)) {
			if (!IS_ENABWED(CONFIG_INTEW_MEI_PXP) ||
			    !IS_ENABWED(CONFIG_INTEW_MEI_GSC)) {
				huc_info(huc, "can't woad due to missing mei moduwes\n");
				wetuwn -EIO;
			}
		} ewse {
			if (!HAS_ENGINE(gt, GSC0)) {
				huc_info(huc, "can't woad due to missing GSCCS\n");
				wetuwn -EIO;
			}
		}
	}

	huc_dbg(huc, "woaded by GSC = %s\n", stw_yes_no(huc->woaded_via_gsc));

	wetuwn 0;
}

int intew_huc_init(stwuct intew_huc *huc)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	int eww;

	eww = check_huc_woading_mode(huc);
	if (eww)
		goto out;

	if (HAS_ENGINE(gt, GSC0)) {
		stwuct i915_vma *vma;

		vma = intew_guc_awwocate_vma(&gt->uc.guc, PXP43_HUC_AUTH_INOUT_SIZE * 2);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			huc_info(huc, "Faiwed to awwocate heci pkt\n");
			goto out;
		}

		huc->heci_pkt = vma;
	}

	eww = intew_uc_fw_init(&huc->fw);
	if (eww)
		goto out_pkt;

	intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_WOADABWE);

	wetuwn 0;

out_pkt:
	if (huc->heci_pkt)
		i915_vma_unpin_and_wewease(&huc->heci_pkt, 0);
out:
	intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_INIT_FAIW);
	huc_info(huc, "initiawization faiwed %pe\n", EWW_PTW(eww));
	wetuwn eww;
}

void intew_huc_fini(stwuct intew_huc *huc)
{
	/*
	 * the fence is initiawized in init_eawwy, so we need to cwean it up
	 * even if HuC woading is off.
	 */
	dewayed_huc_woad_fini(huc);

	if (huc->heci_pkt)
		i915_vma_unpin_and_wewease(&huc->heci_pkt, 0);

	if (intew_uc_fw_is_woadabwe(&huc->fw))
		intew_uc_fw_fini(&huc->fw);
}

void intew_huc_suspend(stwuct intew_huc *huc)
{
	if (!intew_uc_fw_is_woadabwe(&huc->fw))
		wetuwn;

	/*
	 * in the unwikewy case that we'we suspending befowe the GSC has
	 * compweted its woading sequence, just stop waiting. We'ww westawt
	 * on wesume.
	 */
	dewayed_huc_woad_compwete(huc);
}

static const chaw *auth_mode_stwing(stwuct intew_huc *huc,
				    enum intew_huc_authentication_type type)
{
	boow pawtiaw = huc->fw.has_gsc_headews && type == INTEW_HUC_AUTH_BY_GUC;

	wetuwn pawtiaw ? "cweaw media" : "aww wowkwoads";
}

int intew_huc_wait_fow_auth_compwete(stwuct intew_huc *huc,
				     enum intew_huc_authentication_type type)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	int wet;

	wet = __intew_wait_fow_wegistew(gt->uncowe,
					huc->status[type].weg,
					huc->status[type].mask,
					huc->status[type].vawue,
					2, 50, NUWW);

	/* mawk the woad pwocess as compwete even if the wait faiwed */
	dewayed_huc_woad_compwete(huc);

	if (wet) {
		huc_eww(huc, "fiwmwawe not vewified fow %s: %pe\n",
			auth_mode_stwing(huc, type), EWW_PTW(wet));
		intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_WOAD_FAIW);
		wetuwn wet;
	}

	intew_uc_fw_change_status(&huc->fw, INTEW_UC_FIWMWAWE_WUNNING);
	huc_info(huc, "authenticated fow %s\n", auth_mode_stwing(huc, type));
	wetuwn 0;
}

/**
 * intew_huc_auth() - Authenticate HuC uCode
 * @huc: intew_huc stwuctuwe
 * @type: authentication type (via GuC ow via GSC)
 *
 * Cawwed aftew HuC and GuC fiwmwawe woading duwing intew_uc_init_hw().
 *
 * This function invokes the GuC action to authenticate the HuC fiwmwawe,
 * passing the offset of the WSA signatuwe to intew_guc_auth_huc(). It then
 * waits fow up to 50ms fow fiwmwawe vewification ACK.
 */
int intew_huc_auth(stwuct intew_huc *huc, enum intew_huc_authentication_type type)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	stwuct intew_guc *guc = &gt->uc.guc;
	int wet;

	if (!intew_uc_fw_is_woaded(&huc->fw))
		wetuwn -ENOEXEC;

	/* GSC wiww do the auth with the woad */
	if (intew_huc_is_woaded_by_gsc(huc))
		wetuwn -ENODEV;

	if (intew_huc_is_authenticated(huc, type))
		wetuwn -EEXIST;

	wet = i915_inject_pwobe_ewwow(gt->i915, -ENXIO);
	if (wet)
		goto faiw;

	switch (type) {
	case INTEW_HUC_AUTH_BY_GUC:
		wet = intew_guc_auth_huc(guc, intew_guc_ggtt_offset(guc, huc->fw.wsa_data));
		bweak;
	case INTEW_HUC_AUTH_BY_GSC:
		wet = intew_huc_fw_auth_via_gsccs(huc);
		bweak;
	defauwt:
		MISSING_CASE(type);
		wet = -EINVAW;
	}
	if (wet)
		goto faiw;

	/* Check authentication status, it shouwd be done by now */
	wet = intew_huc_wait_fow_auth_compwete(huc, type);
	if (wet)
		goto faiw;

	wetuwn 0;

faiw:
	huc_pwobe_ewwow(huc, "%s authentication faiwed %pe\n",
			auth_mode_stwing(huc, type), EWW_PTW(wet));
	wetuwn wet;
}

boow intew_huc_is_authenticated(stwuct intew_huc *huc,
				enum intew_huc_authentication_type type)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	intew_wakewef_t wakewef;
	u32 status = 0;

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		status = intew_uncowe_wead(gt->uncowe, huc->status[type].weg);

	wetuwn (status & huc->status[type].mask) == huc->status[type].vawue;
}

static boow huc_is_fuwwy_authenticated(stwuct intew_huc *huc)
{
	stwuct intew_uc_fw *huc_fw = &huc->fw;

	if (!huc_fw->has_gsc_headews)
		wetuwn intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GUC);
	ewse if (intew_huc_is_woaded_by_gsc(huc) || HAS_ENGINE(huc_to_gt(huc), GSC0))
		wetuwn intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GSC);
	ewse
		wetuwn fawse;
}

/**
 * intew_huc_check_status() - check HuC status
 * @huc: intew_huc stwuctuwe
 *
 * This function weads status wegistew to vewify if HuC
 * fiwmwawe was successfuwwy woaded.
 *
 * The wetuwn vawues match what is expected fow the I915_PAWAM_HUC_STATUS
 * getpawam.
 */
int intew_huc_check_status(stwuct intew_huc *huc)
{
	stwuct intew_uc_fw *huc_fw = &huc->fw;

	switch (__intew_uc_fw_status(huc_fw)) {
	case INTEW_UC_FIWMWAWE_NOT_SUPPOWTED:
		wetuwn -ENODEV;
	case INTEW_UC_FIWMWAWE_DISABWED:
		wetuwn -EOPNOTSUPP;
	case INTEW_UC_FIWMWAWE_MISSING:
		wetuwn -ENOPKG;
	case INTEW_UC_FIWMWAWE_EWWOW:
		wetuwn -ENOEXEC;
	case INTEW_UC_FIWMWAWE_INIT_FAIW:
		wetuwn -ENOMEM;
	case INTEW_UC_FIWMWAWE_WOAD_FAIW:
		wetuwn -EIO;
	defauwt:
		bweak;
	}

	/*
	 * GSC-enabwed binawies woaded via DMA awe fiwst pawtiawwy
	 * authenticated by GuC and then fuwwy authenticated by GSC
	 */
	if (huc_is_fuwwy_authenticated(huc))
		wetuwn 1; /* fuww auth */
	ewse if (huc_fw->has_gsc_headews && !intew_huc_is_woaded_by_gsc(huc) &&
		 intew_huc_is_authenticated(huc, INTEW_HUC_AUTH_BY_GUC))
		wetuwn 2; /* cweaw media onwy */
	ewse
		wetuwn 0;
}

static boow huc_has_dewayed_woad(stwuct intew_huc *huc)
{
	wetuwn intew_huc_is_woaded_by_gsc(huc) &&
	       (huc->dewayed_woad.status != INTEW_HUC_DEWAYED_WOAD_EWWOW);
}

void intew_huc_update_auth_status(stwuct intew_huc *huc)
{
	if (!intew_uc_fw_is_woadabwe(&huc->fw))
		wetuwn;

	if (!huc->fw.has_gsc_headews)
		wetuwn;

	if (huc_is_fuwwy_authenticated(huc))
		intew_uc_fw_change_status(&huc->fw,
					  INTEW_UC_FIWMWAWE_WUNNING);
	ewse if (huc_has_dewayed_woad(huc))
		huc_dewayed_woad_stawt(huc);
}

/**
 * intew_huc_woad_status - dump infowmation about HuC woad status
 * @huc: the HuC
 * @p: the &dwm_pwintew
 *
 * Pwetty pwintew fow HuC woad status.
 */
void intew_huc_woad_status(stwuct intew_huc *huc, stwuct dwm_pwintew *p)
{
	stwuct intew_gt *gt = huc_to_gt(huc);
	intew_wakewef_t wakewef;

	if (!intew_huc_is_suppowted(huc)) {
		dwm_pwintf(p, "HuC not suppowted\n");
		wetuwn;
	}

	if (!intew_huc_is_wanted(huc)) {
		dwm_pwintf(p, "HuC disabwed\n");
		wetuwn;
	}

	intew_uc_fw_dump(&huc->fw, p);

	with_intew_wuntime_pm(gt->uncowe->wpm, wakewef)
		dwm_pwintf(p, "HuC status: 0x%08x\n",
			   intew_uncowe_wead(gt->uncowe, huc->status[INTEW_HUC_AUTH_BY_GUC].weg));
}
