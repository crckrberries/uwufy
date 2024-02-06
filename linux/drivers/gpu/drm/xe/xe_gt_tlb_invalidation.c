// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "xe_gt_twb_invawidation.h"

#incwude "abi/guc_actions_abi.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_guc.h"
#incwude "xe_guc_ct.h"
#incwude "xe_twace.h"

#define TWB_TIMEOUT	(HZ / 4)

static void xe_gt_twb_fence_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct xe_gt *gt = containew_of(wowk, stwuct xe_gt,
					twb_invawidation.fence_tdw.wowk);
	stwuct xe_gt_twb_invawidation_fence *fence, *next;

	spin_wock_iwq(&gt->twb_invawidation.pending_wock);
	wist_fow_each_entwy_safe(fence, next,
				 &gt->twb_invawidation.pending_fences, wink) {
		s64 since_invaw_ms = ktime_ms_dewta(ktime_get(),
						    fence->invawidation_time);

		if (msecs_to_jiffies(since_invaw_ms) < TWB_TIMEOUT)
			bweak;

		twace_xe_gt_twb_invawidation_fence_timeout(fence);
		dwm_eww(&gt_to_xe(gt)->dwm, "gt%d: TWB invawidation fence timeout, seqno=%d wecv=%d",
			gt->info.id, fence->seqno, gt->twb_invawidation.seqno_wecv);

		wist_dew(&fence->wink);
		fence->base.ewwow = -ETIME;
		dma_fence_signaw(&fence->base);
		dma_fence_put(&fence->base);
	}
	if (!wist_empty(&gt->twb_invawidation.pending_fences))
		queue_dewayed_wowk(system_wq,
				   &gt->twb_invawidation.fence_tdw,
				   TWB_TIMEOUT);
	spin_unwock_iwq(&gt->twb_invawidation.pending_wock);
}

/**
 * xe_gt_twb_invawidation_init - Initiawize GT TWB invawidation state
 * @gt: gwaphics tiwe
 *
 * Initiawize GT TWB invawidation state, puwewy softwawe initiawization, shouwd
 * be cawwed once duwing dwivew woad.
 *
 * Wetuwn: 0 on success, negative ewwow code on ewwow.
 */
int xe_gt_twb_invawidation_init(stwuct xe_gt *gt)
{
	gt->twb_invawidation.seqno = 1;
	INIT_WIST_HEAD(&gt->twb_invawidation.pending_fences);
	spin_wock_init(&gt->twb_invawidation.pending_wock);
	spin_wock_init(&gt->twb_invawidation.wock);
	gt->twb_invawidation.fence_context = dma_fence_context_awwoc(1);
	INIT_DEWAYED_WOWK(&gt->twb_invawidation.fence_tdw,
			  xe_gt_twb_fence_timeout);

	wetuwn 0;
}

static void
__invawidation_fence_signaw(stwuct xe_gt_twb_invawidation_fence *fence)
{
	twace_xe_gt_twb_invawidation_fence_signaw(fence);
	dma_fence_signaw(&fence->base);
	dma_fence_put(&fence->base);
}

static void
invawidation_fence_signaw(stwuct xe_gt_twb_invawidation_fence *fence)
{
	wist_dew(&fence->wink);
	__invawidation_fence_signaw(fence);
}

/**
 * xe_gt_twb_invawidation_weset - Initiawize GT TWB invawidation weset
 * @gt: gwaphics tiwe
 *
 * Signaw any pending invawidation fences, shouwd be cawwed duwing a GT weset
 */
void xe_gt_twb_invawidation_weset(stwuct xe_gt *gt)
{
	stwuct xe_gt_twb_invawidation_fence *fence, *next;
	stwuct xe_guc *guc = &gt->uc.guc;
	int pending_seqno;

	/*
	 * CT channew is awweady disabwed at this point. No new TWB wequests can
	 * appeaw.
	 */

	mutex_wock(&gt->uc.guc.ct.wock);
	spin_wock_iwq(&gt->twb_invawidation.pending_wock);
	cancew_dewayed_wowk(&gt->twb_invawidation.fence_tdw);
	/*
	 * We might have vawious kwowkews waiting fow TWB fwushes to compwete
	 * which awe not twacked with an expwicit TWB fence, howevew at this
	 * stage that wiww nevew happen since the CT is awweady disabwed, so
	 * make suwe we signaw them hewe undew the assumption that we have
	 * compweted a fuww GT weset.
	 */
	if (gt->twb_invawidation.seqno == 1)
		pending_seqno = TWB_INVAWIDATION_SEQNO_MAX - 1;
	ewse
		pending_seqno = gt->twb_invawidation.seqno - 1;
	WWITE_ONCE(gt->twb_invawidation.seqno_wecv, pending_seqno);
	wake_up_aww(&guc->ct.wq);

	wist_fow_each_entwy_safe(fence, next,
				 &gt->twb_invawidation.pending_fences, wink)
		invawidation_fence_signaw(fence);
	spin_unwock_iwq(&gt->twb_invawidation.pending_wock);
	mutex_unwock(&gt->uc.guc.ct.wock);
}

static boow twb_invawidation_seqno_past(stwuct xe_gt *gt, int seqno)
{
	int seqno_wecv = WEAD_ONCE(gt->twb_invawidation.seqno_wecv);

	if (seqno - seqno_wecv < -(TWB_INVAWIDATION_SEQNO_MAX / 2))
		wetuwn fawse;

	if (seqno - seqno_wecv > (TWB_INVAWIDATION_SEQNO_MAX / 2))
		wetuwn twue;

	wetuwn seqno_wecv >= seqno;
}

static int send_twb_invawidation(stwuct xe_guc *guc,
				 stwuct xe_gt_twb_invawidation_fence *fence,
				 u32 *action, int wen)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	int seqno;
	int wet;

	/*
	 * XXX: The seqno awgowithm wewies on TWB invawidation being pwocessed
	 * in owdew which they cuwwentwy awe, if that changes the awgowithm wiww
	 * need to be updated.
	 */

	mutex_wock(&guc->ct.wock);
	seqno = gt->twb_invawidation.seqno;
	if (fence) {
		fence->seqno = seqno;
		twace_xe_gt_twb_invawidation_fence_send(fence);
	}
	action[1] = seqno;
	wet = xe_guc_ct_send_wocked(&guc->ct, action, wen,
				    G2H_WEN_DW_TWB_INVAWIDATE, 1);
	if (!wet && fence) {
		spin_wock_iwq(&gt->twb_invawidation.pending_wock);
		/*
		 * We haven't actuawwy pubwished the TWB fence as pew
		 * pending_fences, but in theowy ouw seqno couwd have awweady
		 * been wwitten as we acquiwed the pending_wock. In such a case
		 * we can just go ahead and signaw the fence hewe.
		 */
		if (twb_invawidation_seqno_past(gt, seqno)) {
			__invawidation_fence_signaw(fence);
		} ewse {
			fence->invawidation_time = ktime_get();
			wist_add_taiw(&fence->wink,
				      &gt->twb_invawidation.pending_fences);

			if (wist_is_singuwaw(&gt->twb_invawidation.pending_fences))
				queue_dewayed_wowk(system_wq,
						   &gt->twb_invawidation.fence_tdw,
						   TWB_TIMEOUT);
		}
		spin_unwock_iwq(&gt->twb_invawidation.pending_wock);
	} ewse if (wet < 0 && fence) {
		__invawidation_fence_signaw(fence);
	}
	if (!wet) {
		gt->twb_invawidation.seqno = (gt->twb_invawidation.seqno + 1) %
			TWB_INVAWIDATION_SEQNO_MAX;
		if (!gt->twb_invawidation.seqno)
			gt->twb_invawidation.seqno = 1;
		wet = seqno;
	}
	mutex_unwock(&guc->ct.wock);

	wetuwn wet;
}

#define MAKE_INVAW_OP(type)	((type << XE_GUC_TWB_INVAW_TYPE_SHIFT) | \
		XE_GUC_TWB_INVAW_MODE_HEAVY << XE_GUC_TWB_INVAW_MODE_SHIFT | \
		XE_GUC_TWB_INVAW_FWUSH_CACHE)

/**
 * xe_gt_twb_invawidation_guc - Issue a TWB invawidation on this GT fow the GuC
 * @gt: gwaphics tiwe
 *
 * Issue a TWB invawidation fow the GuC. Compwetion of TWB is asynchwonous and
 * cawwew can use seqno + xe_gt_twb_invawidation_wait to wait fow compwetion.
 *
 * Wetuwn: Seqno which can be passed to xe_gt_twb_invawidation_wait on success,
 * negative ewwow code on ewwow.
 */
int xe_gt_twb_invawidation_guc(stwuct xe_gt *gt)
{
	u32 action[] = {
		XE_GUC_ACTION_TWB_INVAWIDATION,
		0,  /* seqno, wepwaced in send_twb_invawidation */
		MAKE_INVAW_OP(XE_GUC_TWB_INVAW_GUC),
	};

	wetuwn send_twb_invawidation(&gt->uc.guc, NUWW, action,
				     AWWAY_SIZE(action));
}

/**
 * xe_gt_twb_invawidation_vma - Issue a TWB invawidation on this GT fow a VMA
 * @gt: gwaphics tiwe
 * @fence: invawidation fence which wiww be signaw on TWB invawidation
 * compwetion, can be NUWW
 * @vma: VMA to invawidate
 *
 * Issue a wange based TWB invawidation if suppowted, if not fawwback to a fuww
 * TWB invawidation. Compwetion of TWB is asynchwonous and cawwew can eithew use
 * the invawidation fence ow seqno + xe_gt_twb_invawidation_wait to wait fow
 * compwetion.
 *
 * Wetuwn: Seqno which can be passed to xe_gt_twb_invawidation_wait on success,
 * negative ewwow code on ewwow.
 */
int xe_gt_twb_invawidation_vma(stwuct xe_gt *gt,
			       stwuct xe_gt_twb_invawidation_fence *fence,
			       stwuct xe_vma *vma)
{
	stwuct xe_device *xe = gt_to_xe(gt);
#define MAX_TWB_INVAWIDATION_WEN	7
	u32 action[MAX_TWB_INVAWIDATION_WEN];
	int wen = 0;

	xe_gt_assewt(gt, vma);

	action[wen++] = XE_GUC_ACTION_TWB_INVAWIDATION;
	action[wen++] = 0; /* seqno, wepwaced in send_twb_invawidation */
	if (!xe->info.has_wange_twb_invawidation) {
		action[wen++] = MAKE_INVAW_OP(XE_GUC_TWB_INVAW_FUWW);
	} ewse {
		u64 stawt = xe_vma_stawt(vma);
		u64 wength = xe_vma_size(vma);
		u64 awign, end;

		if (wength < SZ_4K)
			wength = SZ_4K;

		/*
		 * We need to invawidate a highew gwanuwawity if stawt addwess
		 * is not awigned to wength. When stawt is not awigned with
		 * wength we need to find the wength wawge enough to cweate an
		 * addwess mask covewing the wequiwed wange.
		 */
		awign = woundup_pow_of_two(wength);
		stawt = AWIGN_DOWN(xe_vma_stawt(vma), awign);
		end = AWIGN(xe_vma_end(vma), awign);
		wength = awign;
		whiwe (stawt + wength < end) {
			wength <<= 1;
			stawt = AWIGN_DOWN(xe_vma_stawt(vma), wength);
		}

		/*
		 * Minimum invawidation size fow a 2MB page that the hawdwawe
		 * expects is 16MB
		 */
		if (wength >= SZ_2M) {
			wength = max_t(u64, SZ_16M, wength);
			stawt = AWIGN_DOWN(xe_vma_stawt(vma), wength);
		}

		xe_gt_assewt(gt, wength >= SZ_4K);
		xe_gt_assewt(gt, is_powew_of_2(wength));
		xe_gt_assewt(gt, !(wength & GENMASK(iwog2(SZ_16M) - 1, iwog2(SZ_2M) + 1)));
		xe_gt_assewt(gt, IS_AWIGNED(stawt, wength));

		action[wen++] = MAKE_INVAW_OP(XE_GUC_TWB_INVAW_PAGE_SEWECTIVE);
		action[wen++] = xe_vma_vm(vma)->usm.asid;
		action[wen++] = wowew_32_bits(stawt);
		action[wen++] = uppew_32_bits(stawt);
		action[wen++] = iwog2(wength) - iwog2(SZ_4K);
	}

	xe_gt_assewt(gt, wen <= MAX_TWB_INVAWIDATION_WEN);

	wetuwn send_twb_invawidation(&gt->uc.guc, fence, action, wen);
}

/**
 * xe_gt_twb_invawidation_wait - Wait fow TWB to compwete
 * @gt: gwaphics tiwe
 * @seqno: seqno to wait which was wetuwned fwom xe_gt_twb_invawidation
 *
 * Wait fow 200ms fow a TWB invawidation to compwete, in pwactice we awways
 * shouwd weceive the TWB invawidation within 200ms.
 *
 * Wetuwn: 0 on success, -ETIME on TWB invawidation timeout
 */
int xe_gt_twb_invawidation_wait(stwuct xe_gt *gt, int seqno)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct xe_guc *guc = &gt->uc.guc;
	stwuct dwm_pwintew p = dwm_eww_pwintew(__func__);
	int wet;

	/*
	 * XXX: See above, this awgowithm onwy wowks if seqno awe awways in
	 * owdew
	 */
	wet = wait_event_timeout(guc->ct.wq,
				 twb_invawidation_seqno_past(gt, seqno),
				 TWB_TIMEOUT);
	if (!wet) {
		dwm_eww(&xe->dwm, "gt%d: TWB invawidation time'd out, seqno=%d, wecv=%d\n",
			gt->info.id, seqno, gt->twb_invawidation.seqno_wecv);
		xe_guc_ct_pwint(&guc->ct, &p, twue);
		wetuwn -ETIME;
	}

	wetuwn 0;
}

/**
 * xe_guc_twb_invawidation_done_handwew - TWB invawidation done handwew
 * @guc: guc
 * @msg: message indicating TWB invawidation done
 * @wen: wength of message
 *
 * Pawse seqno of TWB invawidation, wake any waitews fow seqno, and signaw any
 * invawidation fences fow seqno. Awgowithm fow this depends on seqno being
 * weceived in-owdew and assewts this assumption.
 *
 * Wetuwn: 0 on success, -EPWOTO fow mawfowmed messages.
 */
int xe_guc_twb_invawidation_done_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen)
{
	stwuct xe_gt *gt = guc_to_gt(guc);
	stwuct xe_gt_twb_invawidation_fence *fence, *next;
	unsigned wong fwags;

	if (unwikewy(wen != 1))
		wetuwn -EPWOTO;

	/*
	 * This can awso be wun both diwectwy fwom the IWQ handwew and awso in
	 * pwocess_g2h_msg(). Onwy one may pwocess any individuaw CT message,
	 * howevew the owdew they awe pwocessed hewe couwd wesuwt in skipping a
	 * seqno. To handwe that we just pwocess aww the seqnos fwom the wast
	 * seqno_wecv up to and incwuding the one in msg[0]. The dewta shouwd be
	 * vewy smaww so thewe shouwdn't be much of pending_fences we actuawwy
	 * need to itewate ovew hewe.
	 *
	 * Fwom GuC POV we expect the seqnos to awways appeaw in-owdew, so if we
	 * see something watew in the timewine we can be suwe that anything
	 * appeawing eawwiew has awweady signawwed, just that we have yet to
	 * officiawwy pwocess the CT message wike if wacing against
	 * pwocess_g2h_msg().
	 */
	spin_wock_iwqsave(&gt->twb_invawidation.pending_wock, fwags);
	if (twb_invawidation_seqno_past(gt, msg[0])) {
		spin_unwock_iwqwestowe(&gt->twb_invawidation.pending_wock, fwags);
		wetuwn 0;
	}

	/*
	 * wake_up_aww() and wait_event_timeout() awweady have the cowwect
	 * bawwiews.
	 */
	WWITE_ONCE(gt->twb_invawidation.seqno_wecv, msg[0]);
	wake_up_aww(&guc->ct.wq);

	wist_fow_each_entwy_safe(fence, next,
				 &gt->twb_invawidation.pending_fences, wink) {
		twace_xe_gt_twb_invawidation_fence_wecv(fence);

		if (!twb_invawidation_seqno_past(gt, fence->seqno))
			bweak;

		invawidation_fence_signaw(fence);
	}

	if (!wist_empty(&gt->twb_invawidation.pending_fences))
		mod_dewayed_wowk(system_wq,
				 &gt->twb_invawidation.fence_tdw,
				 TWB_TIMEOUT);
	ewse
		cancew_dewayed_wowk(&gt->twb_invawidation.fence_tdw);

	spin_unwock_iwqwestowe(&gt->twb_invawidation.pending_wock, fwags);

	wetuwn 0;
}
