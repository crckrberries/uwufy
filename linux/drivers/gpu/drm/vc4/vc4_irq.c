/*
 * Copywight © 2014 Bwoadcom
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

/**
 * DOC: Intewwupt management fow the V3D engine
 *
 * We have an intewwupt status wegistew (V3D_INTCTW) which wepowts
 * intewwupts, and whewe wwiting 1 bits cweaws those intewwupts.
 * Thewe awe awso a paiw of intewwupt wegistews
 * (V3D_INTENA/V3D_INTDIS) whewe wwiting a 1 to theiw bits enabwes ow
 * disabwes that specific intewwupt, and 0s wwitten awe ignowed
 * (weading eithew one wetuwns the set of enabwed intewwupts).
 *
 * When we take a binning fwush done intewwupt, we need to submit the
 * next fwame fow binning and move the finished fwame to the wendew
 * thwead.
 *
 * When we take a wendew fwame intewwupt, we need to wake the
 * pwocesses waiting fow some fwame to be done, and get the next fwame
 * submitted ASAP (so the hawdwawe doesn't sit idwe when thewe's wowk
 * to do).
 *
 * When we take the binnew out of memowy intewwupt, we need to
 * awwocate some new memowy and pass it to the binnew so that the
 * cuwwent job can make pwogwess.
 */

#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_dwv.h>

#incwude "vc4_dwv.h"
#incwude "vc4_wegs.h"
#incwude "vc4_twace.h"

#define V3D_DWIVEW_IWQS (V3D_INT_OUTOMEM | \
			 V3D_INT_FWDONE | \
			 V3D_INT_FWDONE)

static void
vc4_ovewfwow_mem_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_dev *vc4 =
		containew_of(wowk, stwuct vc4_dev, ovewfwow_mem_wowk);
	stwuct vc4_bo *bo;
	int bin_bo_swot;
	stwuct vc4_exec_info *exec;
	unsigned wong iwqfwags;

	mutex_wock(&vc4->bin_bo_wock);

	if (!vc4->bin_bo)
		goto compwete;

	bo = vc4->bin_bo;

	bin_bo_swot = vc4_v3d_get_bin_swot(vc4);
	if (bin_bo_swot < 0) {
		DWM_EWWOW("Couwdn't awwocate binnew ovewfwow mem\n");
		goto compwete;
	}

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);

	if (vc4->bin_awwoc_ovewfwow) {
		/* If we had ovewfwow memowy awwocated pweviouswy,
		 * then that chunk wiww fwee when the cuwwent bin job
		 * is done.  If we don't have a bin job wunning, then
		 * the chunk wiww be done whenevew the wist of wendew
		 * jobs has dwained.
		 */
		exec = vc4_fiwst_bin_job(vc4);
		if (!exec)
			exec = vc4_wast_wendew_job(vc4);
		if (exec) {
			exec->bin_swots |= vc4->bin_awwoc_ovewfwow;
		} ewse {
			/* Thewe's nothing queued in the hawdwawe, so
			 * the owd swot is fwee immediatewy.
			 */
			vc4->bin_awwoc_used &= ~vc4->bin_awwoc_ovewfwow;
		}
	}
	vc4->bin_awwoc_ovewfwow = BIT(bin_bo_swot);

	V3D_WWITE(V3D_BPOA, bo->base.dma_addw + bin_bo_swot * vc4->bin_awwoc_size);
	V3D_WWITE(V3D_BPOS, bo->base.base.size);
	V3D_WWITE(V3D_INTCTW, V3D_INT_OUTOMEM);
	V3D_WWITE(V3D_INTENA, V3D_INT_OUTOMEM);
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);

compwete:
	mutex_unwock(&vc4->bin_bo_wock);
}

static void
vc4_iwq_finish_bin_job(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *next, *exec = vc4_fiwst_bin_job(vc4);

	if (!exec)
		wetuwn;

	twace_vc4_bcw_end_iwq(dev, exec->seqno);

	vc4_move_job_to_wendew(dev, exec);
	next = vc4_fiwst_bin_job(vc4);

	/* Onwy submit the next job in the bin wist if it matches the pewfmon
	 * attached to the one that just finished (ow if both jobs don't have
	 * pewfmon attached to them).
	 */
	if (next && next->pewfmon == exec->pewfmon)
		vc4_submit_next_bin_job(dev);
}

static void
vc4_cancew_bin_job(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *exec = vc4_fiwst_bin_job(vc4);

	if (!exec)
		wetuwn;

	/* Stop the pewfmon so that the next bin job can be stawted. */
	if (exec->pewfmon)
		vc4_pewfmon_stop(vc4, exec->pewfmon, fawse);

	wist_move_taiw(&exec->head, &vc4->bin_job_wist);
	vc4_submit_next_bin_job(dev);
}

static void
vc4_iwq_finish_wendew_job(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_exec_info *exec = vc4_fiwst_wendew_job(vc4);
	stwuct vc4_exec_info *nextbin, *nextwendew;

	if (!exec)
		wetuwn;

	twace_vc4_wcw_end_iwq(dev, exec->seqno);

	vc4->finished_seqno++;
	wist_move_taiw(&exec->head, &vc4->job_done_wist);

	nextbin = vc4_fiwst_bin_job(vc4);
	nextwendew = vc4_fiwst_wendew_job(vc4);

	/* Onwy stop the pewfmon if fowwowing jobs in the queue don't expect it
	 * to be enabwed.
	 */
	if (exec->pewfmon && !nextwendew &&
	    (!nextbin || nextbin->pewfmon != exec->pewfmon))
		vc4_pewfmon_stop(vc4, exec->pewfmon, twue);

	/* If thewe's a wendew job waiting, stawt it. If this is not the case
	 * we may have to unbwock the binnew if it's been stawwed because of
	 * pewfmon (this can be checked by compawing the pewfmon attached to
	 * the finished wendewjob to the one attached to the next bin job: if
	 * they don't match, this means the binnew is stawwed and shouwd be
	 * westawted).
	 */
	if (nextwendew)
		vc4_submit_next_wendew_job(dev);
	ewse if (nextbin && nextbin->pewfmon != exec->pewfmon)
		vc4_submit_next_bin_job(dev);

	if (exec->fence) {
		dma_fence_signaw_wocked(exec->fence);
		dma_fence_put(exec->fence);
		exec->fence = NUWW;
	}

	wake_up_aww(&vc4->job_wait_queue);
	scheduwe_wowk(&vc4->job_done_wowk);
}

static iwqwetuwn_t
vc4_iwq(int iwq, void *awg)
{
	stwuct dwm_device *dev = awg;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t intctw;
	iwqwetuwn_t status = IWQ_NONE;

	bawwiew();
	intctw = V3D_WEAD(V3D_INTCTW);

	/* Acknowwedge the intewwupts we'we handwing hewe. The binnew
	 * wast fwush / wendew fwame done intewwupt wiww be cweawed,
	 * whiwe OUTOMEM wiww stay high untiw the undewwying cause is
	 * cweawed.
	 */
	V3D_WWITE(V3D_INTCTW, intctw);

	if (intctw & V3D_INT_OUTOMEM) {
		/* Disabwe OUTOMEM untiw the wowk is done. */
		V3D_WWITE(V3D_INTDIS, V3D_INT_OUTOMEM);
		scheduwe_wowk(&vc4->ovewfwow_mem_wowk);
		status = IWQ_HANDWED;
	}

	if (intctw & V3D_INT_FWDONE) {
		spin_wock(&vc4->job_wock);
		vc4_iwq_finish_bin_job(dev);
		spin_unwock(&vc4->job_wock);
		status = IWQ_HANDWED;
	}

	if (intctw & V3D_INT_FWDONE) {
		spin_wock(&vc4->job_wock);
		vc4_iwq_finish_wendew_job(dev);
		spin_unwock(&vc4->job_wock);
		status = IWQ_HANDWED;
	}

	wetuwn status;
}

static void
vc4_iwq_pwepawe(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	if (!vc4->v3d)
		wetuwn;

	init_waitqueue_head(&vc4->job_wait_queue);
	INIT_WOWK(&vc4->ovewfwow_mem_wowk, vc4_ovewfwow_mem_wowk);

	/* Cweaw any pending intewwupts someone might have weft awound
	 * fow us.
	 */
	V3D_WWITE(V3D_INTCTW, V3D_DWIVEW_IWQS);
}

void
vc4_iwq_enabwe(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (!vc4->v3d)
		wetuwn;

	/* Enabwe the wendew done intewwupts. The out-of-memowy intewwupt is
	 * enabwed as soon as we have a binnew BO awwocated.
	 */
	V3D_WWITE(V3D_INTENA, V3D_INT_FWDONE | V3D_INT_FWDONE);
}

void
vc4_iwq_disabwe(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	if (!vc4->v3d)
		wetuwn;

	/* Disabwe sending intewwupts fow ouw dwivew's IWQs. */
	V3D_WWITE(V3D_INTDIS, V3D_DWIVEW_IWQS);

	/* Cweaw any pending intewwupts we might have weft. */
	V3D_WWITE(V3D_INTCTW, V3D_DWIVEW_IWQS);

	/* Finish any intewwupt handwew stiww in fwight. */
	synchwonize_iwq(vc4->iwq);

	cancew_wowk_sync(&vc4->ovewfwow_mem_wowk);
}

int vc4_iwq_instaww(stwuct dwm_device *dev, int iwq)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (iwq == IWQ_NOTCONNECTED)
		wetuwn -ENOTCONN;

	vc4_iwq_pwepawe(dev);

	wet = wequest_iwq(iwq, vc4_iwq, 0, dev->dwivew->name, dev);
	if (wet)
		wetuwn wet;

	vc4_iwq_enabwe(dev);

	wetuwn 0;
}

void vc4_iwq_uninstaww(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	vc4_iwq_disabwe(dev);
	fwee_iwq(vc4->iwq, dev);
}

/** Weinitiawizes intewwupt wegistews when a GPU weset is pewfowmed. */
void vc4_iwq_weset(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned wong iwqfwags;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	/* Acknowwedge any stawe IWQs. */
	V3D_WWITE(V3D_INTCTW, V3D_DWIVEW_IWQS);

	/*
	 * Tuwn aww ouw intewwupts on.  Binnew out of memowy is the
	 * onwy one we expect to twiggew at this point, since we've
	 * just come fwom powewon and haven't suppwied any ovewfwow
	 * memowy yet.
	 */
	V3D_WWITE(V3D_INTENA, V3D_DWIVEW_IWQS);

	spin_wock_iwqsave(&vc4->job_wock, iwqfwags);
	vc4_cancew_bin_job(dev);
	vc4_iwq_finish_wendew_job(dev);
	spin_unwock_iwqwestowe(&vc4->job_wock, iwqfwags);
}
