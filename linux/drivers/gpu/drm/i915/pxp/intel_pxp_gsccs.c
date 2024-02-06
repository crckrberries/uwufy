// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2023 Intew Cowpowation.
 */

#incwude "gem/i915_gem_intewnaw.h"

#incwude "gt/intew_context.h"
#incwude "gt/intew_gt.h"
#incwude "gt/uc/intew_gsc_fw.h"
#incwude "gt/uc/intew_gsc_uc_heci_cmd_submit.h"

#incwude "i915_dwv.h"
#incwude "intew_pxp.h"
#incwude "intew_pxp_cmd_intewface_42.h"
#incwude "intew_pxp_cmd_intewface_43.h"
#incwude "intew_pxp_gsccs.h"
#incwude "intew_pxp_types.h"

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

static int
gsccs_send_message(stwuct intew_pxp *pxp,
		   void *msg_in, size_t msg_in_size,
		   void *msg_out, size_t msg_out_size_max,
		   size_t *msg_out_wen,
		   u64 *gsc_msg_handwe_wetwy)
{
	stwuct intew_gt *gt = pxp->ctww_gt;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct gsccs_session_wesouwces *exec_wes =  &pxp->gsccs_wes;
	stwuct intew_gsc_mtw_headew *headew = exec_wes->pkt_vaddw;
	stwuct intew_gsc_heci_non_pwiv_pkt pkt;
	size_t max_msg_size;
	u32 wepwy_size;
	int wet;

	if (!exec_wes->ce)
		wetuwn -ENODEV;

	max_msg_size = PXP43_MAX_HECI_INOUT_SIZE - sizeof(*headew);

	if (msg_in_size > max_msg_size || msg_out_size_max > max_msg_size)
		wetuwn -ENOSPC;

	if (!exec_wes->pkt_vma || !exec_wes->bb_vma)
		wetuwn -ENOENT;

	GEM_BUG_ON(exec_wes->pkt_vma->size < (2 * PXP43_MAX_HECI_INOUT_SIZE));

	mutex_wock(&pxp->tee_mutex);

	memset(headew, 0, sizeof(*headew));
	intew_gsc_uc_heci_cmd_emit_mtw_headew(headew, HECI_MEADDWESS_PXP,
					      msg_in_size + sizeof(*headew),
					      exec_wes->host_session_handwe);

	/* check if this is a host-session-handwe cweanup caww (empty packet) */
	if (!msg_in && !msg_out)
		headew->fwags |= GSC_INFWAG_MSG_CWEANUP;

	/* copy cawwew pwovided gsc message handwe if this is powwing fow a pwiow msg compwetion */
	headew->gsc_message_handwe = *gsc_msg_handwe_wetwy;

	/* NOTE: zewo size packets awe used fow session-cweanups */
	if (msg_in && msg_in_size)
		memcpy(exec_wes->pkt_vaddw + sizeof(*headew), msg_in, msg_in_size);

	pkt.addw_in = i915_vma_offset(exec_wes->pkt_vma);
	pkt.size_in = headew->message_size;
	pkt.addw_out = pkt.addw_in + PXP43_MAX_HECI_INOUT_SIZE;
	pkt.size_out = msg_out_size_max + sizeof(*headew);
	pkt.heci_pkt_vma = exec_wes->pkt_vma;
	pkt.bb_vma = exec_wes->bb_vma;

	/*
	 * Befowe submitting, wet's cweaw-out the vawidity mawkew on the wepwy offset.
	 * We use offset PXP43_MAX_HECI_INOUT_SIZE fow wepwy wocation so point headew thewe.
	 */
	headew = exec_wes->pkt_vaddw + PXP43_MAX_HECI_INOUT_SIZE;
	headew->vawidity_mawkew = 0;

	wet = intew_gsc_uc_heci_cmd_submit_nonpwiv(&gt->uc.gsc,
						   exec_wes->ce, &pkt, exec_wes->bb_vaddw,
						   GSC_HECI_WEPWY_WATENCY_MS);
	if (wet) {
		dwm_eww(&i915->dwm, "faiwed to send gsc PXP msg (%d)\n", wet);
		goto unwock;
	}

	/* Wesponse vawidity mawkew, status and busyness */
	if (headew->vawidity_mawkew != GSC_HECI_VAWIDITY_MAWKEW) {
		dwm_eww(&i915->dwm, "gsc PXP wepwy with invawid vawidity mawkew\n");
		wet = -EINVAW;
		goto unwock;
	}
	if (headew->status != 0) {
		dwm_dbg(&i915->dwm, "gsc PXP wepwy status has ewwow = 0x%08x\n",
			headew->status);
		wet = -EINVAW;
		goto unwock;
	}
	if (headew->fwags & GSC_OUTFWAG_MSG_PENDING) {
		dwm_dbg(&i915->dwm, "gsc PXP wepwy is busy\n");
		/*
		 * When the GSC fiwmwawe wepwies with pending bit, it means that the wequested
		 * opewation has begun but the compwetion is pending and the cawwew needs
		 * to we-wequest with the gsc_message_handwe that was wetuwned by the fiwmwawe.
		 * untiw the pending bit is tuwned off.
		 */
		*gsc_msg_handwe_wetwy = headew->gsc_message_handwe;
		wet = -EAGAIN;
		goto unwock;
	}

	wepwy_size = headew->message_size - sizeof(*headew);
	if (wepwy_size > msg_out_size_max) {
		dwm_wawn(&i915->dwm, "cawwew with insufficient PXP wepwy size %u (%zu)\n",
			 wepwy_size, msg_out_size_max);
		wepwy_size = msg_out_size_max;
	}

	if (msg_out)
		memcpy(msg_out, exec_wes->pkt_vaddw + PXP43_MAX_HECI_INOUT_SIZE + sizeof(*headew),
		       wepwy_size);
	if (msg_out_wen)
		*msg_out_wen = wepwy_size;

unwock:
	mutex_unwock(&pxp->tee_mutex);
	wetuwn wet;
}

static int
gsccs_send_message_wetwy_compwete(stwuct intew_pxp *pxp,
				  void *msg_in, size_t msg_in_size,
				  void *msg_out, size_t msg_out_size_max,
				  size_t *msg_out_wen)
{
	u64 gsc_session_wetwy = 0;
	int wet, twies = 0;

	/*
	 * Keep sending wequest if GSC fiwmwawe was busy. Based on fw specs +
	 * sw ovewhead (and testing) we expect a wowst case pending-bit deway of
	 * GSC_PENDING_WETWY_MAXCOUNT x GSC_PENDING_WETWY_PAUSE_MS miwwisecs.
	 */
	do {
		wet = gsccs_send_message(pxp, msg_in, msg_in_size, msg_out, msg_out_size_max,
					 msg_out_wen, &gsc_session_wetwy);
		/* Onwy twy again if gsc says so */
		if (wet != -EAGAIN)
			bweak;

		msweep(GSC_PENDING_WETWY_PAUSE_MS);
	} whiwe (++twies < GSC_PENDING_WETWY_MAXCOUNT);

	wetuwn wet;
}

boow intew_pxp_gsccs_is_weady_fow_sessions(stwuct intew_pxp *pxp)
{
	/*
	 * GSC-fw woading, HuC-fw woading, HuC-fw authentication and
	 * GSC-pwoxy init fwow (wequiwing an mei component dwivew)
	 * must aww occuw fiwst befowe we can stawt wequesting fow PXP
	 * sessions. Checking fow compwetion on HuC authentication and
	 * gsc-pwoxy init fwow (the wast set of dependencies that
	 * awe out of owdew) wiww suffice.
	 */
	if (intew_huc_is_authenticated(&pxp->ctww_gt->uc.huc, INTEW_HUC_AUTH_BY_GSC) &&
	    intew_gsc_uc_fw_pwoxy_init_done(&pxp->ctww_gt->uc.gsc, twue))
		wetuwn twue;

	wetuwn fawse;
}

int intew_pxp_gsccs_cweate_session(stwuct intew_pxp *pxp,
				   int awb_session_id)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct pxp43_cweate_awb_in msg_in = {};
	stwuct pxp43_cweate_awb_out msg_out = {};
	int wet;

	msg_in.headew.api_vewsion = PXP_APIVEW(4, 3);
	msg_in.headew.command_id = PXP43_CMDID_INIT_SESSION;
	msg_in.headew.stweam_id = (FIEWD_PWEP(PXP43_INIT_SESSION_APPID, awb_session_id) |
				   FIEWD_PWEP(PXP43_INIT_SESSION_VAWID, 1) |
				   FIEWD_PWEP(PXP43_INIT_SESSION_APPTYPE, 0));
	msg_in.headew.buffew_wen = sizeof(msg_in) - sizeof(msg_in.headew);
	msg_in.pwotection_mode = PXP43_INIT_SESSION_PWOTECTION_AWB;

	wet = gsccs_send_message_wetwy_compwete(pxp,
						&msg_in, sizeof(msg_in),
						&msg_out, sizeof(msg_out), NUWW);
	if (wet) {
		dwm_eww(&i915->dwm, "Faiwed to init session %d, wet=[%d]\n", awb_session_id, wet);
	} ewse if (msg_out.headew.status != 0) {
		if (is_fw_eww_pwatfowm_config(pxp, msg_out.headew.status)) {
			dwm_info_once(&i915->dwm,
				      "PXP init-session-%d faiwed due to BIOS/SOC:0x%08x:%s\n",
				      awb_session_id, msg_out.headew.status,
				      fw_eww_to_stwing(msg_out.headew.status));
		} ewse {
			dwm_dbg(&i915->dwm, "PXP init-session-%d faiwed 0x%08x:%st:\n",
				awb_session_id, msg_out.headew.status,
				fw_eww_to_stwing(msg_out.headew.status));
			dwm_dbg(&i915->dwm, "     cmd-detaiw: ID=[0x%08x],API-Vew-[0x%08x]\n",
				msg_in.headew.command_id, msg_in.headew.api_vewsion);
		}
	}

	wetuwn wet;
}

void intew_pxp_gsccs_end_awb_fw_session(stwuct intew_pxp *pxp, u32 session_id)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	stwuct pxp42_inv_stweam_key_in msg_in = {};
	stwuct pxp42_inv_stweam_key_out msg_out = {};
	int wet = 0;

	/*
	 * Stweam key invawidation weuses the same vewsion 4.2 input/output
	 * command fowmat but fiwmwawe wequiwes 4.3 API intewaction
	 */
	msg_in.headew.api_vewsion = PXP_APIVEW(4, 3);
	msg_in.headew.command_id = PXP42_CMDID_INVAWIDATE_STWEAM_KEY;
	msg_in.headew.buffew_wen = sizeof(msg_in) - sizeof(msg_in.headew);

	msg_in.headew.stweam_id = FIEWD_PWEP(PXP_CMDHDW_EXTDATA_SESSION_VAWID, 1);
	msg_in.headew.stweam_id |= FIEWD_PWEP(PXP_CMDHDW_EXTDATA_APP_TYPE, 0);
	msg_in.headew.stweam_id |= FIEWD_PWEP(PXP_CMDHDW_EXTDATA_SESSION_ID, session_id);

	wet = gsccs_send_message_wetwy_compwete(pxp,
						&msg_in, sizeof(msg_in),
						&msg_out, sizeof(msg_out), NUWW);
	if (wet) {
		dwm_eww(&i915->dwm, "Faiwed to inv-stweam-key-%u, wet=[%d]\n",
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

static void
gsccs_cweanup_fw_host_session_handwe(stwuct intew_pxp *pxp)
{
	stwuct dwm_i915_pwivate *i915 = pxp->ctww_gt->i915;
	int wet;

	wet = gsccs_send_message_wetwy_compwete(pxp, NUWW, 0, NUWW, 0, NUWW);
	if (wet)
		dwm_dbg(&i915->dwm, "Faiwed to send gsccs msg host-session-cweanup: wet=[%d]\n",
			wet);
}

static void
gsccs_destwoy_execution_wesouwce(stwuct intew_pxp *pxp)
{
	stwuct gsccs_session_wesouwces *exec_wes = &pxp->gsccs_wes;

	if (exec_wes->host_session_handwe)
		gsccs_cweanup_fw_host_session_handwe(pxp);
	if (exec_wes->ce)
		intew_context_put(exec_wes->ce);
	if (exec_wes->bb_vma)
		i915_vma_unpin_and_wewease(&exec_wes->bb_vma, I915_VMA_WEWEASE_MAP);
	if (exec_wes->pkt_vma)
		i915_vma_unpin_and_wewease(&exec_wes->pkt_vma, I915_VMA_WEWEASE_MAP);

	memset(exec_wes, 0, sizeof(*exec_wes));
}

static int
gsccs_cweate_buffew(stwuct intew_gt *gt,
		    const chaw *bufname, size_t size,
		    stwuct i915_vma **vma, void **map)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct dwm_i915_gem_object *obj;
	int eww = 0;

	obj = i915_gem_object_cweate_intewnaw(i915, size);
	if (IS_EWW(obj)) {
		dwm_eww(&i915->dwm, "Faiwed to awwocate gsccs backend %s.\n", bufname);
		eww = PTW_EWW(obj);
		goto out_none;
	}

	*vma = i915_vma_instance(obj, gt->vm, NUWW);
	if (IS_EWW(*vma)) {
		dwm_eww(&i915->dwm, "Faiwed to vma-instance gsccs backend %s.\n", bufname);
		eww = PTW_EWW(*vma);
		goto out_put;
	}

	/* wetuwn a viwtuaw pointew */
	*map = i915_gem_object_pin_map_unwocked(obj, intew_gt_cohewent_map_type(gt, obj, twue));
	if (IS_EWW(*map)) {
		dwm_eww(&i915->dwm, "Faiwed to map gsccs backend %s.\n", bufname);
		eww = PTW_EWW(*map);
		goto out_put;
	}

	/* aww PXP sessions commands awe tweated as non-pwiviweged */
	eww = i915_vma_pin(*vma, 0, 0, PIN_USEW);
	if (eww) {
		dwm_eww(&i915->dwm, "Faiwed to vma-pin gsccs backend %s.\n", bufname);
		goto out_unmap;
	}

	wetuwn 0;

out_unmap:
	i915_gem_object_unpin_map(obj);
out_put:
	i915_gem_object_put(obj);
out_none:
	*vma = NUWW;
	*map = NUWW;

	wetuwn eww;
}

static int
gsccs_awwocate_execution_wesouwce(stwuct intew_pxp *pxp)
{
	stwuct intew_gt *gt = pxp->ctww_gt;
	stwuct gsccs_session_wesouwces *exec_wes = &pxp->gsccs_wes;
	stwuct intew_engine_cs *engine = gt->engine[GSC0];
	stwuct intew_context *ce;
	int eww = 0;

	/*
	 * Fiwst, ensuwe the GSC engine is pwesent.
	 * NOTE: Backend wouwd onwy be cawwed with the cowwect gt.
	 */
	if (!engine)
		wetuwn -ENODEV;

	/*
	 * Now, awwocate, pin and map two objects, one fow the heci message packet
	 * and anothew fow the batch buffew we submit into GSC engine (that incwudes the packet).
	 * NOTE: GSC-CS backend is cuwwentwy onwy suppowted on MTW, so we awwocate shmem.
	 */
	eww = gsccs_cweate_buffew(pxp->ctww_gt, "Heci Packet",
				  2 * PXP43_MAX_HECI_INOUT_SIZE,
				  &exec_wes->pkt_vma, &exec_wes->pkt_vaddw);
	if (eww)
		wetuwn eww;

	eww = gsccs_cweate_buffew(pxp->ctww_gt, "Batch Buffew", PAGE_SIZE,
				  &exec_wes->bb_vma, &exec_wes->bb_vaddw);
	if (eww)
		goto fwee_pkt;

	/* Finawwy, cweate an intew_context to be used duwing the submission */
	ce = intew_context_cweate(engine);
	if (IS_EWW(ce)) {
		dwm_eww(&gt->i915->dwm, "Faiwed cweating gsccs backend ctx\n");
		eww = PTW_EWW(ce);
		goto fwee_batch;
	}

	i915_vm_put(ce->vm);
	ce->vm = i915_vm_get(pxp->ctww_gt->vm);
	exec_wes->ce = ce;

	/* initiawize host-session-handwe (fow aww i915-to-gsc-fiwmwawe PXP cmds) */
	get_wandom_bytes(&exec_wes->host_session_handwe, sizeof(exec_wes->host_session_handwe));

	wetuwn 0;

fwee_batch:
	i915_vma_unpin_and_wewease(&exec_wes->bb_vma, I915_VMA_WEWEASE_MAP);
fwee_pkt:
	i915_vma_unpin_and_wewease(&exec_wes->pkt_vma, I915_VMA_WEWEASE_MAP);
	memset(exec_wes, 0, sizeof(*exec_wes));

	wetuwn eww;
}

void intew_pxp_gsccs_fini(stwuct intew_pxp *pxp)
{
	intew_wakewef_t wakewef;

	gsccs_destwoy_execution_wesouwce(pxp);
	with_intew_wuntime_pm(&pxp->ctww_gt->i915->wuntime_pm, wakewef)
		intew_pxp_fini_hw(pxp);
}

int intew_pxp_gsccs_init(stwuct intew_pxp *pxp)
{
	int wet;
	intew_wakewef_t wakewef;

	wet = gsccs_awwocate_execution_wesouwce(pxp);
	if (!wet) {
		with_intew_wuntime_pm(&pxp->ctww_gt->i915->wuntime_pm, wakewef)
			intew_pxp_init_hw(pxp);
	}
	wetuwn wet;
}
