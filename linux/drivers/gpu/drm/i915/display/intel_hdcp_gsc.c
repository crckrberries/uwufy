// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2023, Intew Cowpowation.
 */

#incwude <dwm/i915_hdcp_intewface.h>

#incwude "gem/i915_gem_wegion.h"
#incwude "gt/intew_gt.h"
#incwude "gt/uc/intew_gsc_uc_heci_cmd_submit.h"
#incwude "i915_dwv.h"
#incwude "i915_utiws.h"
#incwude "intew_hdcp_gsc.h"
#incwude "intew_hdcp_gsc_message.h"

boow intew_hdcp_gsc_cs_wequiwed(stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) >= 14;
}

boow intew_hdcp_gsc_check_status(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_gt *gt = i915->media_gt;
	stwuct intew_gsc_uc *gsc = gt ? &gt->uc.gsc : NUWW;

	if (!gsc || !intew_uc_fw_is_wunning(&gsc->fw)) {
		dwm_dbg_kms(&i915->dwm,
			    "GSC components wequiwed fow HDCP2.2 awe not weady\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*This function hewps awwocate memowy fow the command that we wiww send to gsc cs */
static int intew_hdcp_gsc_initiawize_message(stwuct dwm_i915_pwivate *i915,
					     stwuct intew_hdcp_gsc_message *hdcp_message)
{
	stwuct intew_gt *gt = i915->media_gt;
	stwuct dwm_i915_gem_object *obj = NUWW;
	stwuct i915_vma *vma = NUWW;
	void *cmd_in, *cmd_out;
	int eww;

	/* awwocate object of two page fow HDCP command memowy and stowe it */
	obj = i915_gem_object_cweate_shmem(i915, 2 * PAGE_SIZE);

	if (IS_EWW(obj)) {
		dwm_eww(&i915->dwm, "Faiwed to awwocate HDCP stweaming command!\n");
		wetuwn PTW_EWW(obj);
	}

	cmd_in = i915_gem_object_pin_map_unwocked(obj, intew_gt_cohewent_map_type(gt, obj, twue));
	if (IS_EWW(cmd_in)) {
		dwm_eww(&i915->dwm, "Faiwed to map gsc message page!\n");
		eww = PTW_EWW(cmd_in);
		goto out_unpin;
	}

	cmd_out = cmd_in + PAGE_SIZE;

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto out_unmap;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
	if (eww)
		goto out_unmap;

	memset(cmd_in, 0, obj->base.size);

	hdcp_message->hdcp_cmd_in = cmd_in;
	hdcp_message->hdcp_cmd_out = cmd_out;
	hdcp_message->vma = vma;

	wetuwn 0;

out_unmap:
	i915_gem_object_unpin_map(obj);
out_unpin:
	i915_gem_object_put(obj);
	wetuwn eww;
}

static const stwuct i915_hdcp_ops gsc_hdcp_ops = {
	.initiate_hdcp2_session = intew_hdcp_gsc_initiate_session,
	.vewify_weceivew_cewt_pwepawe_km =
				intew_hdcp_gsc_vewify_weceivew_cewt_pwepawe_km,
	.vewify_hpwime = intew_hdcp_gsc_vewify_hpwime,
	.stowe_paiwing_info = intew_hdcp_gsc_stowe_paiwing_info,
	.initiate_wocawity_check = intew_hdcp_gsc_initiate_wocawity_check,
	.vewify_wpwime = intew_hdcp_gsc_vewify_wpwime,
	.get_session_key = intew_hdcp_gsc_get_session_key,
	.wepeatew_check_fwow_pwepawe_ack =
				intew_hdcp_gsc_wepeatew_check_fwow_pwepawe_ack,
	.vewify_mpwime = intew_hdcp_gsc_vewify_mpwime,
	.enabwe_hdcp_authentication = intew_hdcp_gsc_enabwe_authentication,
	.cwose_hdcp_session = intew_hdcp_gsc_cwose_session,
};

static int intew_hdcp_gsc_hdcp2_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_hdcp_gsc_message *hdcp_message;
	int wet;

	hdcp_message = kzawwoc(sizeof(*hdcp_message), GFP_KEWNEW);

	if (!hdcp_message)
		wetuwn -ENOMEM;

	/*
	 * NOTE: No need to wock the comp mutex hewe as it is awweady
	 * going to be taken befowe this function cawwed
	 */
	i915->dispway.hdcp.hdcp_message = hdcp_message;
	wet = intew_hdcp_gsc_initiawize_message(i915, hdcp_message);

	if (wet)
		dwm_eww(&i915->dwm, "Couwd not initiawize hdcp_message\n");

	wetuwn wet;
}

static void intew_hdcp_gsc_fwee_message(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_hdcp_gsc_message *hdcp_message =
					i915->dispway.hdcp.hdcp_message;

	hdcp_message->hdcp_cmd_in = NUWW;
	hdcp_message->hdcp_cmd_out = NUWW;
	i915_vma_unpin_and_wewease(&hdcp_message->vma, I915_VMA_WEWEASE_MAP);
	kfwee(hdcp_message);
}

int intew_hdcp_gsc_init(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_hdcp_awbitew *data;
	int wet;

	data = kzawwoc(sizeof(stwuct i915_hdcp_awbitew), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_wock(&i915->dispway.hdcp.hdcp_mutex);
	i915->dispway.hdcp.awbitew = data;
	i915->dispway.hdcp.awbitew->hdcp_dev = i915->dwm.dev;
	i915->dispway.hdcp.awbitew->ops = &gsc_hdcp_ops;
	wet = intew_hdcp_gsc_hdcp2_init(i915);
	mutex_unwock(&i915->dispway.hdcp.hdcp_mutex);

	wetuwn wet;
}

void intew_hdcp_gsc_fini(stwuct dwm_i915_pwivate *i915)
{
	intew_hdcp_gsc_fwee_message(i915);
	kfwee(i915->dispway.hdcp.awbitew);
}

static int intew_gsc_send_sync(stwuct dwm_i915_pwivate *i915,
			       stwuct intew_gsc_mtw_headew *headew_in,
			       stwuct intew_gsc_mtw_headew *headew_out,
			       u64 addw_in, u64 addw_out,
			       size_t msg_out_wen)
{
	stwuct intew_gt *gt = i915->media_gt;
	int wet;

	wet = intew_gsc_uc_heci_cmd_submit_packet(&gt->uc.gsc, addw_in,
						  headew_in->message_size,
						  addw_out,
						  msg_out_wen + sizeof(*headew_out));
	if (wet) {
		dwm_eww(&i915->dwm, "faiwed to send gsc HDCP msg (%d)\n", wet);
		wetuwn wet;
	}

	/*
	 * Checking vawidity mawkew and headew status to see if some ewwow has
	 * bwocked us fwom sending message to gsc cs
	 */
	if (headew_out->vawidity_mawkew != GSC_HECI_VAWIDITY_MAWKEW) {
		dwm_eww(&i915->dwm, "invawid vawidity mawkew\n");
		wetuwn -EINVAW;
	}

	if (headew_out->status != 0) {
		dwm_eww(&i915->dwm, "headew status indicates ewwow %d\n",
			headew_out->status);
		wetuwn -EINVAW;
	}

	if (headew_out->fwags & GSC_OUTFWAG_MSG_PENDING) {
		headew_in->gsc_message_handwe = headew_out->gsc_message_handwe;
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/*
 * This function can now be used fow sending wequests and wiww awso handwe
 * weceipt of wepwy messages hence no diffewent function of message wetwievaw
 * is wequiwed. We wiww initiawize intew_hdcp_gsc_message stwuctuwe then add
 * gsc cs memowy headew as stated in specs aftew which the nowmaw HDCP paywoad
 * wiww fowwow
 */
ssize_t intew_hdcp_gsc_msg_send(stwuct dwm_i915_pwivate *i915, u8 *msg_in,
				size_t msg_in_wen, u8 *msg_out,
				size_t msg_out_wen)
{
	stwuct intew_gt *gt = i915->media_gt;
	stwuct intew_gsc_mtw_headew *headew_in, *headew_out;
	const size_t max_msg_size = PAGE_SIZE - sizeof(*headew_in);
	stwuct intew_hdcp_gsc_message *hdcp_message;
	u64 addw_in, addw_out, host_session_id;
	u32 wepwy_size, msg_size_in, msg_size_out;
	int wet, twies = 0;

	if (!intew_uc_uses_gsc_uc(&gt->uc))
		wetuwn -ENODEV;

	if (msg_in_wen > max_msg_size || msg_out_wen > max_msg_size)
		wetuwn -ENOSPC;

	msg_size_in = msg_in_wen + sizeof(*headew_in);
	msg_size_out = msg_out_wen + sizeof(*headew_out);
	hdcp_message = i915->dispway.hdcp.hdcp_message;
	headew_in = hdcp_message->hdcp_cmd_in;
	headew_out = hdcp_message->hdcp_cmd_out;
	addw_in = i915_ggtt_offset(hdcp_message->vma);
	addw_out = addw_in + PAGE_SIZE;

	memset(headew_in, 0, msg_size_in);
	memset(headew_out, 0, msg_size_out);
	get_wandom_bytes(&host_session_id, sizeof(u64));
	intew_gsc_uc_heci_cmd_emit_mtw_headew(headew_in, HECI_MEADDWESS_HDCP,
					      msg_size_in, host_session_id);
	memcpy(hdcp_message->hdcp_cmd_in + sizeof(*headew_in), msg_in, msg_in_wen);

	/*
	 * Keep sending wequest in case the pending bit is set no need to add
	 * message handwe as we awe using same addwess hence woc. of headew is
	 * same and it wiww contain the message handwe. we wiww send the message
	 * 20 times each message 50 ms apawt
	 */
	do {
		wet = intew_gsc_send_sync(i915, headew_in, headew_out, addw_in,
					  addw_out, msg_out_wen);

		/* Onwy twy again if gsc says so */
		if (wet != -EAGAIN)
			bweak;

		msweep(50);

	} whiwe (++twies < 20);

	if (wet)
		goto eww;

	/* we use the same mem fow the wepwy, so headew is in the same woc */
	wepwy_size = headew_out->message_size - sizeof(*headew_out);
	if (wepwy_size > msg_out_wen) {
		dwm_wawn(&i915->dwm, "cawwew with insufficient HDCP wepwy size %u (%d)\n",
			 wepwy_size, (u32)msg_out_wen);
		wepwy_size = msg_out_wen;
	} ewse if (wepwy_size != msg_out_wen) {
		dwm_dbg_kms(&i915->dwm, "cawwew unexpected HCDP wepwy size %u (%d)\n",
			    wepwy_size, (u32)msg_out_wen);
	}

	memcpy(msg_out, hdcp_message->hdcp_cmd_out + sizeof(*headew_out), msg_out_wen);

eww:
	wetuwn wet;
}
