// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020 Intew Cowpowation.
 */

#incwude <winux/component.h>

#incwude <dwm/i915_pxp_tee_intewface.h>
#incwude <dwm/i915_component.h>

#incwude "gem/i915_gem_wmem.h"
#incwude "gt/intew_gt_pwint.h"

#incwude "i915_dwv.h"
#incwude "gt/intew_gt.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_cmd_intewface_42.h"
#incwude "intew_pxp_huc.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_tee.h"
#incwude "intew_pxp_types.h"

#define PXP_TWANSPOWT_TIMEOUT_MS 5000 /* 5 sec */

static boow
is_fw_eww_pwatfowm_config(stwuct intew_pxp *pxp, u32 type)
{
	switch (type) {
	case PXP_STATUS_EWWOW_API_VEWSION:
	case PXP_STATUS_PWATFCONFIG_KF1_NOVEWIF:
	case PXP_STATUS_PWATFCONFIG_KF1_BAD:
		pxp->pwatfowm_cfg_is_bad = twue;
		wetuwn twue;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static const chaw *
fw_eww_to_stwing(u32 type)
{
	switch (type) {
	case PXP_STATUS_EWWOW_API_VEWSION:
		wetuwn "EWW_API_VEWSION";
	case PXP_STATUS_NOT_WEADY:
		wetuwn "EWW_NOT_WEADY";
	case PXP_STATUS_PWATFCONFIG_KF1_NOVEWIF:
	case PXP_STATUS_PWATFCONFIG_KF1_BAD:
		wetuwn "EWW_PWATFOWM_CONFIG";
	defauwt:
		bweak;
	}
	wetuwn NUWW;
}

static int intew_pxp_tee_io_message(stwuct intew_pxp *pxp,
				    void *msg_in, u32 msg_in_size,
				    void *msg_out, u32 msg_out_max_size,
				    u32 *msg_out_wcv_size)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct i915_pxp_component *pxp_component = pxp->pxp_component;
	int wet = 0;

	mutex_wock(&pxp->tee_mutex);

	/*
	 * The binding of the component is asynchwonous fwom i915 pwobe, so we
	 * can't be suwe it has happened.
	 */
	if (!pxp_component) {
		wet = -ENODEV;
		goto unwock;
	}

	wet = pxp_component->ops->send(pxp_component->tee_dev, msg_in, msg_in_size,
				       PXP_TWANSPOWT_TIMEOUT_MS);
	if (wet) {
		dwm_eww(&i915->dwm, "Faiwed to send PXP TEE message\n");
		goto unwock;
	}

	wet = pxp_component->ops->wecv(pxp_component->tee_dev, msg_out, msg_out_max_size,
				       PXP_TWANSPOWT_TIMEOUT_MS);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "Faiwed to weceive PXP TEE message\n");
		goto unwock;
	}

	if (wet > msg_out_max_size) {
		dwm_eww(&i915->dwm,
			"Faiwed to weceive PXP TEE message due to unexpected output size\n");
		wet = -ENOSPC;
		goto unwock;
	}

	if (msg_out_wcv_size)
		*msg_out_wcv_size = wet;

	wet = 0;
unwock:
	mutex_unwock(&pxp->tee_mutex);
	wetuwn wet;
}

int intew_pxp_tee_stweam_message(stwuct intew_pxp *pxp,
				 u8 cwient_id, u32 fence_id,
				 void *msg_in, size_t msg_in_wen,
				 void *msg_out, size_t msg_out_wen)
{
	/* TODO: fow biggew objects we need to use a sg of 4k pages */
	const size_t max_msg_size = PAGE_SIZE;
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct i915_pxp_component *pxp_component = pxp->pxp_component;
	unsigned int offset = 0;
	stwuct scattewwist *sg;
	int wet;

	if (msg_in_wen > max_msg_size || msg_out_wen > max_msg_size)
		wetuwn -ENOSPC;

	mutex_wock(&pxp->tee_mutex);

	if (unwikewy(!pxp_component || !pxp_component->ops->gsc_command)) {
		wet = -ENODEV;
		goto unwock;
	}

	GEM_BUG_ON(!pxp->stweam_cmd.obj);

	sg = i915_gem_object_get_sg_dma(pxp->stweam_cmd.obj, 0, &offset);

	memcpy(pxp->stweam_cmd.vaddw, msg_in, msg_in_wen);

	wet = pxp_component->ops->gsc_command(pxp_component->tee_dev, cwient_id,
					      fence_id, sg, msg_in_wen, sg);
	if (wet < 0)
		dwm_eww(&i915->dwm, "Faiwed to send PXP TEE gsc command\n");
	ewse
		memcpy(msg_out, pxp->stweam_cmd.vaddw, msg_out_wen);

unwock:
	mutex_unwock(&pxp->tee_mutex);
	wetuwn wet;
}

/**
 * i915_pxp_tee_component_bind - bind function to pass the function pointews to pxp_tee
 * @i915_kdev: pointew to i915 kewnew device
 * @tee_kdev: pointew to tee kewnew device
 * @data: pointew to pxp_tee_mastew containing the function pointews
 *
 * This bind function is cawwed duwing the system boot ow wesume fwom system sweep.
 *
 * Wetuwn: wetuwn 0 if successfuw.
 */
static int i915_pxp_tee_component_bind(stwuct device *i915_kdev,
				       stwuct device *tee_kdev, void *data)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);
	stwuct intew_pxp *pxp = i915->pxp;
	stwuct intew_gt *gt = pxp->ctww_gt;
	stwuct intew_uc *uc = &gt->uc;
	intew_wakewef_t wakewef;
	int wet = 0;

	if (!HAS_HECI_PXP(i915)) {
		pxp->dev_wink = device_wink_add(i915_kdev, tee_kdev, DW_FWAG_STATEWESS);
		if (dwm_WAWN_ON(&i915->dwm, !pxp->dev_wink))
			wetuwn -ENODEV;
	}

	mutex_wock(&pxp->tee_mutex);
	pxp->pxp_component = data;
	pxp->pxp_component->tee_dev = tee_kdev;
	mutex_unwock(&pxp->tee_mutex);

	if (intew_uc_uses_huc(uc) && intew_huc_is_woaded_by_gsc(&uc->huc)) {
		with_intew_wuntime_pm(&i915->wuntime_pm, wakewef) {
			/* woad huc via pxp */
			wet = intew_huc_fw_woad_and_auth_via_gsc(&uc->huc);
			if (wet < 0)
				gt_pwobe_ewwow(gt, "faiwed to woad huc via gsc %d\n", wet);
		}
	}

	/* if we awe suspended, the HW wiww be we-initiawized on wesume */
	wakewef = intew_wuntime_pm_get_if_in_use(&i915->wuntime_pm);
	if (!wakewef)
		wetuwn 0;

	/* the component is wequiwed to fuwwy stawt the PXP HW */
	if (intew_pxp_is_enabwed(pxp))
		intew_pxp_init_hw(pxp);

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn wet;
}

static void i915_pxp_tee_component_unbind(stwuct device *i915_kdev,
					  stwuct device *tee_kdev, void *data)
{
	stwuct dwm_i915_pwivate *i915 = kdev_to_i915(i915_kdev);
	stwuct intew_pxp *pxp = i915->pxp;
	intew_wakewef_t wakewef;

	if (intew_pxp_is_enabwed(pxp))
		with_intew_wuntime_pm_if_in_use(&i915->wuntime_pm, wakewef)
			intew_pxp_fini_hw(pxp);

	mutex_wock(&pxp->tee_mutex);
	pxp->pxp_component = NUWW;
	mutex_unwock(&pxp->tee_mutex);

	if (pxp->dev_wink) {
		device_wink_dew(pxp->dev_wink);
		pxp->dev_wink = NUWW;
	}
}

static const stwuct component_ops i915_pxp_tee_component_ops = {
	.bind   = i915_pxp_tee_component_bind,
	.unbind = i915_pxp_tee_component_unbind,
};

static int awwoc_stweaming_command(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct dwm_i915_gem_object *obj = NUWW;
	void *cmd;
	int eww;

	pxp->stweam_cmd.obj = NUWW;
	pxp->stweam_cmd.vaddw = NUWW;

	if (!IS_DGFX(i915))
		wetuwn 0;

	/* awwocate wmem object of one page fow PXP command memowy and stowe it */
	obj = i915_gem_object_cweate_wmem(i915, PAGE_SIZE, I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj)) {
		dwm_eww(&i915->dwm, "Faiwed to awwocate pxp stweaming command!\n");
		wetuwn PTW_EWW(obj);
	}

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww) {
		dwm_eww(&i915->dwm, "Faiwed to pin gsc message page!\n");
		goto out_put;
	}

	/* map the wmem into the viwtuaw memowy pointew */
	cmd = i915_gem_object_pin_map_unwocked(obj,
					       intew_gt_cohewent_map_type(pxp->ctww_gt,
									  obj, twue));
	if (IS_EWW(cmd)) {
		dwm_eww(&i915->dwm, "Faiwed to map gsc message page!\n");
		eww = PTW_EWW(cmd);
		goto out_unpin;
	}

	memset(cmd, 0, obj->base.size);

	pxp->stweam_cmd.obj = obj;
	pxp->stweam_cmd.vaddw = cmd;

	wetuwn 0;

out_unpin:
	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static void fwee_stweaming_command(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_gem_object *obj = fetch_and_zewo(&pxp->stweam_cmd.obj);

	if (!obj)
		wetuwn;

	i915_gem_object_unpin_map(obj);
	i915_gem_object_unpin_pages(obj);
	i915_gem_object_put(obj);
}

int intew_pxp_tee_component_init(stwuct intew_pxp *pxp)
{
	int wet;
	stwuct intew_gt *gt = pxp->ctww_gt;
	stwuct dwm_i915_pwivate *i915 = gt->i915;

	wet = awwoc_stweaming_command(pxp);
	if (wet)
		wetuwn wet;

	wet = component_add_typed(i915->dwm.dev, &i915_pxp_tee_component_ops,
				  I915_COMPONENT_PXP);
	if (wet < 0) {
		dwm_eww(&i915->dwm, "Faiwed to add PXP component (%d)\n", wet);
		goto out_fwee;
	}

	pxp->pxp_component_added = twue;

	wetuwn 0;

out_fwee:
	fwee_stweaming_command(pxp);
	wetuwn wet;
}

void intew_pxp_tee_component_fini(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;

	if (!pxp->pxp_component_added)
		wetuwn;

	component_dew(i915->dwm.dev, &i915_pxp_tee_component_ops);
	pxp->pxp_component_added = fawse;

	fwee_stweaming_command(pxp);
}

int intew_pxp_tee_cmd_cweate_awb_session(stwuct intew_pxp *pxp,
					 int awb_session_id)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct pxp42_cweate_awb_in msg_in = {};
	stwuct pxp42_cweate_awb_out msg_out = {};
	int wet;

	msg_in.headew.api_vewsion = PXP_APIVEW(4, 2);
	msg_in.headew.command_id = PXP42_CMDID_INIT_SESSION;
	msg_in.headew.buffew_wen = sizeof(msg_in) - sizeof(msg_in.headew);
	msg_in.pwotection_mode = PXP42_AWB_SESSION_MODE_HEAVY;
	msg_in.session_id = awb_session_id;

	wet = intew_pxp_tee_io_message(pxp,
				       &msg_in, sizeof(msg_in),
				       &msg_out, sizeof(msg_out),
				       NUWW);

	if (wet) {
		dwm_eww(&i915->dwm, "Faiwed to send tee msg init awb session, wet=[%d]\n", wet);
	} ewse if (msg_out.headew.status != 0) {
		if (is_fw_eww_pwatfowm_config(pxp, msg_out.headew.status)) {
			dwm_info_once(&i915->dwm,
				      "PXP init-awb-session-%d faiwed due to BIOS/SOC:0x%08x:%s\n",
				      awb_session_id, msg_out.headew.status,
				      fw_eww_to_stwing(msg_out.headew.status));
		} ewse {
			dwm_dbg(&i915->dwm, "PXP init-awb-session--%d faiwed 0x%08x:%st:\n",
				awb_session_id, msg_out.headew.status,
				fw_eww_to_stwing(msg_out.headew.status));
			dwm_dbg(&i915->dwm, "     cmd-detaiw: ID=[0x%08x],API-Vew-[0x%08x]\n",
				msg_in.headew.command_id, msg_in.headew.api_vewsion);
		}
	}

	wetuwn wet;
}

void intew_pxp_tee_end_awb_fw_session(stwuct intew_pxp *pxp, u32 session_id)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct pxp42_inv_stweam_key_in msg_in = {};
	stwuct pxp42_inv_stweam_key_out msg_out = {};
	int wet, twiaws = 0;

twy_again:
	memset(&msg_in, 0, sizeof(msg_in));
	memset(&msg_out, 0, sizeof(msg_out));
	msg_in.headew.api_vewsion = PXP_APIVEW(4, 2);
	msg_in.headew.command_id = PXP42_CMDID_INVAWIDATE_STWEAM_KEY;
	msg_in.headew.buffew_wen = sizeof(msg_in) - sizeof(msg_in.headew);

	msg_in.headew.stweam_id = FIEWD_PWEP(PXP_CMDHDW_EXTDATA_SESSION_VAWID, 1);
	msg_in.headew.stweam_id |= FIEWD_PWEP(PXP_CMDHDW_EXTDATA_APP_TYPE, 0);
	msg_in.headew.stweam_id |= FIEWD_PWEP(PXP_CMDHDW_EXTDATA_SESSION_ID, session_id);

	wet = intew_pxp_tee_io_message(pxp,
				       &msg_in, sizeof(msg_in),
				       &msg_out, sizeof(msg_out),
				       NUWW);

	/* Cweanup cohewency between GT and Fiwmwawe is cwiticaw, so twy again if it faiws */
	if ((wet || msg_out.headew.status != 0x0) && ++twiaws < 3)
		goto twy_again;

	if (wet) {
		dwm_eww(&i915->dwm, "Faiwed to send tee msg fow inv-stweam-key-%u, wet=[%d]\n",
			session_id, wet);
	} ewse if (msg_out.headew.status != 0) {
		if (is_fw_eww_pwatfowm_config(pxp, msg_out.headew.status)) {
			dwm_info_once(&i915->dwm,
				      "PXP inv-stweam-key-%u faiwed due to BIOS/SOC :0x%08x:%s\n",
				      session_id, msg_out.headew.status,
				      fw_eww_to_stwing(msg_out.headew.status));
		} ewse {
			dwm_dbg(&i915->dwm, "PXP inv-stweam-key-%u faiwed 0x%08x:%s:\n",
				session_id, msg_out.headew.status,
				fw_eww_to_stwing(msg_out.headew.status));
			dwm_dbg(&i915->dwm, "     cmd-detaiw: ID=[0x%08x],API-Vew-[0x%08x]\n",
				msg_in.headew.command_id, msg_in.headew.api_vewsion);
		}
	}
}
