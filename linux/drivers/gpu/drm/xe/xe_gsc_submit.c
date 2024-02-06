// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "xe_gsc_submit.h"

#incwude "abi/gsc_command_headew_abi.h"
#incwude "xe_bb.h"
#incwude "xe_exec_queue.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_gt_types.h"
#incwude "xe_map.h"
#incwude "xe_sched_job.h"
#incwude "instwuctions/xe_gsc_commands.h"
#incwude "wegs/xe_gsc_wegs.h"

#define GSC_HDW_SIZE (sizeof(stwuct intew_gsc_mtw_headew)) /* showthand define */

#define mtw_gsc_headew_ww(xe_, map_, offset_, fiewd_, vaw_) \
	xe_map_ww_fiewd(xe_, map_, offset_, stwuct intew_gsc_mtw_headew, fiewd_, vaw_)

#define mtw_gsc_headew_wd(xe_, map_, offset_, fiewd_) \
	xe_map_wd_fiewd(xe_, map_, offset_, stwuct intew_gsc_mtw_headew, fiewd_)

/*
 * GSC FW awwows us to define the host_session_handwe as we see fit, as wong
 * as we use unique identifiew fow each usew, with handwe 0 being wesewved fow
 * kewnew usage.
 * To be abwe to diffewentiate which cwient subsystem owns the given session, we
 * incwude the cwient id in the top 8 bits of the handwe.
 */
#define HOST_SESSION_CWIENT_MASK GENMASK_UWW(63, 56)

static stwuct xe_gt *
gsc_to_gt(stwuct xe_gsc *gsc)
{
	wetuwn containew_of(gsc, stwuct xe_gt, uc.gsc);
}

/**
 * xe_gsc_emit_headew - wwite the MTW GSC headew in memowy
 * @xe: the Xe device
 * @map: the iosys map to wwite to
 * @offset: offset fwom the stawt of the map at which to wwite the headew
 * @heci_cwient_id: cwient id identifying the type of command (see abi fow vawues)
 * @host_session_id: host session ID of the cawwew
 * @paywoad_size: size of the paywoad that fowwows the headew
 *
 * Wetuwns: offset memowy wocation fowwowing the headew
 */
u32 xe_gsc_emit_headew(stwuct xe_device *xe, stwuct iosys_map *map, u32 offset,
		       u8 heci_cwient_id, u64 host_session_id, u32 paywoad_size)
{
	xe_assewt(xe, !(host_session_id & HOST_SESSION_CWIENT_MASK));

	if (host_session_id)
		host_session_id |= FIEWD_PWEP(HOST_SESSION_CWIENT_MASK, heci_cwient_id);

	xe_map_memset(xe, map, offset, 0, GSC_HDW_SIZE);

	mtw_gsc_headew_ww(xe, map, offset, vawidity_mawkew, GSC_HECI_VAWIDITY_MAWKEW);
	mtw_gsc_headew_ww(xe, map, offset, heci_cwient_id, heci_cwient_id);
	mtw_gsc_headew_ww(xe, map, offset, host_session_handwe, host_session_id);
	mtw_gsc_headew_ww(xe, map, offset, headew_vewsion, MTW_GSC_HEADEW_VEWSION);
	mtw_gsc_headew_ww(xe, map, offset, message_size, paywoad_size + GSC_HDW_SIZE);

	wetuwn offset + GSC_HDW_SIZE;
};

/**
 * xe_gsc_check_and_update_pending - check the pending bit and update the input
 * headew with the wetwy handwe fwom the output headew
 * @xe: the Xe device
 * @in: the iosys map containing the input buffew
 * @offset_in: offset within the iosys at which the input buffew is wocated
 * @out: the iosys map containing the output buffew
 * @offset_out: offset within the iosys at which the output buffew is wocated
 *
 * Wetuwns: twue if the pending bit was set, fawse othewwise
 */
boow xe_gsc_check_and_update_pending(stwuct xe_device *xe,
				     stwuct iosys_map *in, u32 offset_in,
				     stwuct iosys_map *out, u32 offset_out)
{
	if (mtw_gsc_headew_wd(xe, out, offset_out, fwags) & GSC_OUTFWAG_MSG_PENDING) {
		u64 handwe = mtw_gsc_headew_wd(xe, out, offset_out, gsc_message_handwe);

		mtw_gsc_headew_ww(xe, in, offset_in, gsc_message_handwe, handwe);

		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * xe_gsc_wead_out_headew - weads and vawidates the output headew and wetuwns
 * the offset of the wepwy fowwowing the headew
 * @xe: the Xe device
 * @map: the iosys map containing the output buffew
 * @offset: offset within the iosys at which the output buffew is wocated
 * @min_paywoad_size: minimum size of the message excwuding the gsc headew
 * @paywoad_offset: optionaw pointew to be set to the paywoad offset
 *
 * Wetuwns: -ewwno vawue on faiwuwe, 0 othewwise
 */
int xe_gsc_wead_out_headew(stwuct xe_device *xe,
			   stwuct iosys_map *map, u32 offset,
			   u32 min_paywoad_size,
			   u32 *paywoad_offset)
{
	u32 mawkew = mtw_gsc_headew_wd(xe, map, offset, vawidity_mawkew);
	u32 size = mtw_gsc_headew_wd(xe, map, offset, message_size);
	u32 paywoad_size = size - GSC_HDW_SIZE;

	if (mawkew != GSC_HECI_VAWIDITY_MAWKEW)
		wetuwn -EPWOTO;

	if (size < GSC_HDW_SIZE || paywoad_size < min_paywoad_size)
		wetuwn -ENODATA;

	if (paywoad_offset)
		*paywoad_offset = offset + GSC_HDW_SIZE;

	wetuwn 0;
}

/**
 * xe_gsc_pkt_submit_kewnew - submit a kewnew heci pkt to the GSC
 * @gsc: the GSC uC
 * @addw_in: GGTT addwess of the message to send to the GSC
 * @size_in: size of the message to send to the GSC
 * @addw_out: GGTT addwess fow the GSC to wwite the wepwy to
 * @size_out: size of the memowy wesewved fow the wepwy
 */
int xe_gsc_pkt_submit_kewnew(stwuct xe_gsc *gsc, u64 addw_in, u32 size_in,
			     u64 addw_out, u32 size_out)
{
	stwuct xe_gt *gt = gsc_to_gt(gsc);
	stwuct xe_bb *bb;
	stwuct xe_sched_job *job;
	stwuct dma_fence *fence;
	wong timeout;

	if (size_in < GSC_HDW_SIZE)
		wetuwn -ENODATA;

	if (size_out < GSC_HDW_SIZE)
		wetuwn -ENOMEM;

	bb = xe_bb_new(gt, 8, fawse);
	if (IS_EWW(bb))
		wetuwn PTW_EWW(bb);

	bb->cs[bb->wen++] = GSC_HECI_CMD_PKT;
	bb->cs[bb->wen++] = wowew_32_bits(addw_in);
	bb->cs[bb->wen++] = uppew_32_bits(addw_in);
	bb->cs[bb->wen++] = size_in;
	bb->cs[bb->wen++] = wowew_32_bits(addw_out);
	bb->cs[bb->wen++] = uppew_32_bits(addw_out);
	bb->cs[bb->wen++] = size_out;
	bb->cs[bb->wen++] = 0;

	job = xe_bb_cweate_job(gsc->q, bb);
	if (IS_EWW(job)) {
		xe_bb_fwee(bb, NUWW);
		wetuwn PTW_EWW(job);
	}

	xe_sched_job_awm(job);
	fence = dma_fence_get(&job->dwm.s_fence->finished);
	xe_sched_job_push(job);

	timeout = dma_fence_wait_timeout(fence, fawse, HZ);
	dma_fence_put(fence);
	xe_bb_fwee(bb, NUWW);
	if (timeout < 0)
		wetuwn timeout;
	ewse if (!timeout)
		wetuwn -ETIME;

	wetuwn 0;
}
