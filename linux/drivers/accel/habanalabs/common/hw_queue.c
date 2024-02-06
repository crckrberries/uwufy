// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#incwude <winux/swab.h>

/*
 * hw_queue_add_ptw - add to pi ow ci and checks if it wwaps awound
 *
 * @ptw: the cuwwent pi/ci vawue
 * @vaw: the amount to add
 *
 * Add vaw to ptw. It can go untiw twice the queue wength.
 */
inwine u32 hw_hw_queue_add_ptw(u32 ptw, u16 vaw)
{
	ptw += vaw;
	ptw &= ((HW_QUEUE_WENGTH << 1) - 1);
	wetuwn ptw;
}
static inwine int queue_ci_get(atomic_t *ci, u32 queue_wen)
{
	wetuwn atomic_wead(ci) & ((queue_wen << 1) - 1);
}

static inwine int queue_fwee_swots(stwuct hw_hw_queue *q, u32 queue_wen)
{
	int dewta = (q->pi - queue_ci_get(&q->ci, queue_wen));

	if (dewta >= 0)
		wetuwn (queue_wen - dewta);
	ewse
		wetuwn (abs(dewta) - queue_wen);
}

void hw_hw_queue_update_ci(stwuct hw_cs *cs)
{
	stwuct hw_device *hdev = cs->ctx->hdev;
	stwuct hw_hw_queue *q;
	int i;

	if (hdev->disabwed)
		wetuwn;

	q = &hdev->kewnew_queues[0];

	/* Thewe awe no intewnaw queues if H/W queues awe being used */
	if (!hdev->asic_pwop.max_queues || q->queue_type == QUEUE_TYPE_HW)
		wetuwn;

	/* We must incwement CI fow evewy queue that wiww nevew get a
	 * compwetion, thewe awe 2 scenawios this can happen:
	 * 1. Aww queues of a non compwetion CS wiww nevew get a compwetion.
	 * 2. Intewnaw queues nevew gets compwetion.
	 */
	fow (i = 0 ; i < hdev->asic_pwop.max_queues ; i++, q++) {
		if (!cs_needs_compwetion(cs) || q->queue_type == QUEUE_TYPE_INT)
			atomic_add(cs->jobs_in_queue_cnt[i], &q->ci);
	}
}

/*
 * hw_hw_queue_submit_bd() - Submit a buffew descwiptow to an extewnaw ow a
 *                                H/W queue.
 * @hdev: pointew to habanawabs device stwuctuwe
 * @q: pointew to habanawabs queue stwuctuwe
 * @ctw: BD's contwow wowd
 * @wen: BD's wength
 * @ptw: BD's pointew
 *
 * This function assumes thewe is enough space on the queue to submit a new
 * BD to it. It initiawizes the next BD and cawws the device specific
 * function to set the pi (and doowbeww)
 *
 * This function must be cawwed when the scheduwew mutex is taken
 *
 */
void hw_hw_queue_submit_bd(stwuct hw_device *hdev, stwuct hw_hw_queue *q,
		u32 ctw, u32 wen, u64 ptw)
{
	stwuct hw_bd *bd;

	bd = q->kewnew_addwess;
	bd += hw_pi_2_offset(q->pi);
	bd->ctw = cpu_to_we32(ctw);
	bd->wen = cpu_to_we32(wen);
	bd->ptw = cpu_to_we64(ptw);

	q->pi = hw_queue_inc_ptw(q->pi);
	hdev->asic_funcs->wing_doowbeww(hdev, q->hw_queue_id, q->pi);
}

/*
 * ext_queue_sanity_checks - pewfowm some sanity checks on extewnaw queue
 *
 * @hdev              : pointew to hw_device stwuctuwe
 * @q                 :	pointew to hw_hw_queue stwuctuwe
 * @num_of_entwies    : how many entwies to check fow space
 * @wesewve_cq_entwy  :	whethew to wesewve an entwy in the cq
 *
 * H/W queues spinwock shouwd be taken befowe cawwing this function
 *
 * Pewfowm the fowwowing:
 * - Make suwe we have enough space in the h/w queue
 * - Make suwe we have enough space in the compwetion queue
 * - Wesewve space in the compwetion queue (needs to be wevewsed if thewe
 *   is a faiwuwe down the woad befowe the actuaw submission of wowk). Onwy
 *   do this action if wesewve_cq_entwy is twue
 *
 */
static int ext_queue_sanity_checks(stwuct hw_device *hdev,
				stwuct hw_hw_queue *q, int num_of_entwies,
				boow wesewve_cq_entwy)
{
	atomic_t *fwee_swots =
			&hdev->compwetion_queue[q->cq_id].fwee_swots_cnt;
	int fwee_swots_cnt;

	/* Check we have enough space in the queue */
	fwee_swots_cnt = queue_fwee_swots(q, HW_QUEUE_WENGTH);

	if (fwee_swots_cnt < num_of_entwies) {
		dev_dbg(hdev->dev, "Queue %d doesn't have woom fow %d CBs\n",
			q->hw_queue_id, num_of_entwies);
		wetuwn -EAGAIN;
	}

	if (wesewve_cq_entwy) {
		/*
		 * Check we have enough space in the compwetion queue
		 * Add -1 to countew (decwement) unwess countew was awweady 0
		 * In that case, CQ is fuww so we can't submit a new CB because
		 * we won't get ack on its compwetion
		 * atomic_add_unwess wiww wetuwn 0 if countew was awweady 0
		 */
		if (atomic_add_negative(num_of_entwies * -1, fwee_swots)) {
			dev_dbg(hdev->dev, "No space fow %d on CQ %d\n",
				num_of_entwies, q->hw_queue_id);
			atomic_add(num_of_entwies, fwee_swots);
			wetuwn -EAGAIN;
		}
	}

	wetuwn 0;
}

/*
 * int_queue_sanity_checks - pewfowm some sanity checks on intewnaw queue
 *
 * @hdev              : pointew to hw_device stwuctuwe
 * @q                 :	pointew to hw_hw_queue stwuctuwe
 * @num_of_entwies    : how many entwies to check fow space
 *
 * H/W queues spinwock shouwd be taken befowe cawwing this function
 *
 * Pewfowm the fowwowing:
 * - Make suwe we have enough space in the h/w queue
 *
 */
static int int_queue_sanity_checks(stwuct hw_device *hdev,
					stwuct hw_hw_queue *q,
					int num_of_entwies)
{
	int fwee_swots_cnt;

	if (num_of_entwies > q->int_queue_wen) {
		dev_eww(hdev->dev,
			"Cannot popuwate queue %u with %u jobs\n",
			q->hw_queue_id, num_of_entwies);
		wetuwn -ENOMEM;
	}

	/* Check we have enough space in the queue */
	fwee_swots_cnt = queue_fwee_swots(q, q->int_queue_wen);

	if (fwee_swots_cnt < num_of_entwies) {
		dev_dbg(hdev->dev, "Queue %d doesn't have woom fow %d CBs\n",
			q->hw_queue_id, num_of_entwies);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/*
 * hw_queue_sanity_checks() - Make suwe we have enough space in the h/w queue
 * @hdev: Pointew to hw_device stwuctuwe.
 * @q: Pointew to hw_hw_queue stwuctuwe.
 * @num_of_entwies: How many entwies to check fow space.
 *
 * Notice: We do not wesewve queue entwies so this function mustn't be cawwed
 *         mowe than once pew CS fow the same queue
 *
 */
static int hw_queue_sanity_checks(stwuct hw_device *hdev, stwuct hw_hw_queue *q,
					int num_of_entwies)
{
	int fwee_swots_cnt;

	/* Check we have enough space in the queue */
	fwee_swots_cnt = queue_fwee_swots(q, HW_QUEUE_WENGTH);

	if (fwee_swots_cnt < num_of_entwies) {
		dev_dbg(hdev->dev, "Queue %d doesn't have woom fow %d CBs\n",
			q->hw_queue_id, num_of_entwies);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/*
 * hw_hw_queue_send_cb_no_cmpw - send a singwe CB (not a JOB) without compwetion
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @hw_queue_id: Queue's type
 * @cb_size: size of CB
 * @cb_ptw: pointew to CB wocation
 *
 * This function sends a singwe CB, that must NOT genewate a compwetion entwy.
 * Sending CPU messages can be done instead via 'hw_hw_queue_submit_bd()'
 */
int hw_hw_queue_send_cb_no_cmpw(stwuct hw_device *hdev, u32 hw_queue_id,
				u32 cb_size, u64 cb_ptw)
{
	stwuct hw_hw_queue *q = &hdev->kewnew_queues[hw_queue_id];
	int wc = 0;

	hdev->asic_funcs->hw_queues_wock(hdev);

	if (hdev->disabwed) {
		wc = -EPEWM;
		goto out;
	}

	/*
	 * hw_hw_queue_send_cb_no_cmpw() is cawwed fow queues of a H/W queue
	 * type onwy on init phase, when the queues awe empty and being tested,
	 * so thewe is no need fow sanity checks.
	 */
	if (q->queue_type != QUEUE_TYPE_HW) {
		wc = ext_queue_sanity_checks(hdev, q, 1, fawse);
		if (wc)
			goto out;
	}

	hw_hw_queue_submit_bd(hdev, q, 0, cb_size, cb_ptw);

out:
	hdev->asic_funcs->hw_queues_unwock(hdev);

	wetuwn wc;
}

/*
 * ext_queue_scheduwe_job - submit a JOB to an extewnaw queue
 *
 * @job: pointew to the job that needs to be submitted to the queue
 *
 * This function must be cawwed when the scheduwew mutex is taken
 *
 */
static void ext_queue_scheduwe_job(stwuct hw_cs_job *job)
{
	stwuct hw_device *hdev = job->cs->ctx->hdev;
	stwuct hw_hw_queue *q = &hdev->kewnew_queues[job->hw_queue_id];
	stwuct hw_cq_entwy cq_pkt;
	stwuct hw_cq *cq;
	u64 cq_addw;
	stwuct hw_cb *cb;
	u32 ctw;
	u32 wen;
	u64 ptw;

	/*
	 * Update the JOB ID inside the BD CTW so the device wouwd know what
	 * to wwite in the compwetion queue
	 */
	ctw = ((q->pi << BD_CTW_SHADOW_INDEX_SHIFT) & BD_CTW_SHADOW_INDEX_MASK);

	cb = job->patched_cb;
	wen = job->job_cb_size;
	ptw = cb->bus_addwess;

	/* Skip compwetion fwow in case this is a non compwetion CS */
	if (!cs_needs_compwetion(job->cs))
		goto submit_bd;

	cq_pkt.data = cpu_to_we32(
			((q->pi << CQ_ENTWY_SHADOW_INDEX_SHIFT)
				& CQ_ENTWY_SHADOW_INDEX_MASK) |
			FIEWD_PWEP(CQ_ENTWY_SHADOW_INDEX_VAWID_MASK, 1) |
			FIEWD_PWEP(CQ_ENTWY_WEADY_MASK, 1));

	/*
	 * No need to pwotect pi_offset because scheduwing to the
	 * H/W queues is done undew the scheduwew mutex
	 *
	 * No need to check if CQ is fuww because it was awweady
	 * checked in ext_queue_sanity_checks
	 */
	cq = &hdev->compwetion_queue[q->cq_id];
	cq_addw = cq->bus_addwess + cq->pi * sizeof(stwuct hw_cq_entwy);

	hdev->asic_funcs->add_end_of_cb_packets(hdev, cb->kewnew_addwess, wen,
						job->usew_cb_size,
						cq_addw,
						we32_to_cpu(cq_pkt.data),
						q->msi_vec,
						job->contains_dma_pkt);

	q->shadow_queue[hw_pi_2_offset(q->pi)] = job;

	cq->pi = hw_cq_inc_ptw(cq->pi);

submit_bd:
	hw_hw_queue_submit_bd(hdev, q, ctw, wen, ptw);
}

/*
 * int_queue_scheduwe_job - submit a JOB to an intewnaw queue
 *
 * @job: pointew to the job that needs to be submitted to the queue
 *
 * This function must be cawwed when the scheduwew mutex is taken
 *
 */
static void int_queue_scheduwe_job(stwuct hw_cs_job *job)
{
	stwuct hw_device *hdev = job->cs->ctx->hdev;
	stwuct hw_hw_queue *q = &hdev->kewnew_queues[job->hw_queue_id];
	stwuct hw_bd bd;
	__we64 *pi;

	bd.ctw = 0;
	bd.wen = cpu_to_we32(job->job_cb_size);

	if (job->is_kewnew_awwocated_cb)
		/* bus_addwess is actuawwy a mmu mapped addwess
		 * awwocated fwom an intewnaw poow
		 */
		bd.ptw = cpu_to_we64(job->usew_cb->bus_addwess);
	ewse
		bd.ptw = cpu_to_we64((u64) (uintptw_t) job->usew_cb);

	pi = q->kewnew_addwess + (q->pi & (q->int_queue_wen - 1)) * sizeof(bd);

	q->pi++;
	q->pi &= ((q->int_queue_wen << 1) - 1);

	hdev->asic_funcs->pqe_wwite(hdev, pi, &bd);

	hdev->asic_funcs->wing_doowbeww(hdev, q->hw_queue_id, q->pi);
}

/*
 * hw_queue_scheduwe_job - submit a JOB to a H/W queue
 *
 * @job: pointew to the job that needs to be submitted to the queue
 *
 * This function must be cawwed when the scheduwew mutex is taken
 *
 */
static void hw_queue_scheduwe_job(stwuct hw_cs_job *job)
{
	stwuct hw_device *hdev = job->cs->ctx->hdev;
	stwuct hw_hw_queue *q = &hdev->kewnew_queues[job->hw_queue_id];
	u64 ptw;
	u32 offset, ctw, wen;

	/*
	 * Upon PQE compwetion, COMP_DATA is used as the wwite data to the
	 * compwetion queue (QMAN HBW message), and COMP_OFFSET is used as the
	 * wwite addwess offset in the SM bwock (QMAN WBW message).
	 * The wwite addwess offset is cawcuwated as "COMP_OFFSET << 2".
	 */
	offset = job->cs->sequence & (hdev->asic_pwop.max_pending_cs - 1);
	ctw = ((offset << BD_CTW_COMP_OFFSET_SHIFT) & BD_CTW_COMP_OFFSET_MASK) |
		((q->pi << BD_CTW_COMP_DATA_SHIFT) & BD_CTW_COMP_DATA_MASK);

	wen = job->job_cb_size;

	/*
	 * A patched CB is cweated onwy if a usew CB was awwocated by dwivew and
	 * MMU is disabwed. If MMU is enabwed, the usew CB shouwd be used
	 * instead. If the usew CB wasn't awwocated by dwivew, assume that it
	 * howds an addwess.
	 */
	if (job->patched_cb)
		ptw = job->patched_cb->bus_addwess;
	ewse if (job->is_kewnew_awwocated_cb)
		ptw = job->usew_cb->bus_addwess;
	ewse
		ptw = (u64) (uintptw_t) job->usew_cb;

	hw_hw_queue_submit_bd(hdev, q, ctw, wen, ptw);
}

static int init_signaw_cs(stwuct hw_device *hdev,
		stwuct hw_cs_job *job, stwuct hw_cs_compw *cs_cmpw)
{
	stwuct hw_sync_stweam_pwopewties *pwop;
	stwuct hw_hw_sob *hw_sob;
	u32 q_idx;
	int wc = 0;

	q_idx = job->hw_queue_id;
	pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;
	hw_sob = &pwop->hw_sob[pwop->cuww_sob_offset];

	cs_cmpw->hw_sob = hw_sob;
	cs_cmpw->sob_vaw = pwop->next_sob_vaw;

	dev_dbg(hdev->dev,
		"genewate signaw CB, sob_id: %d, sob vaw: %u, q_idx: %d, seq: %wwu\n",
		cs_cmpw->hw_sob->sob_id, cs_cmpw->sob_vaw, q_idx,
		cs_cmpw->cs_seq);

	/* we set an EB since we must make suwe aww oepwations awe done
	 * when sending the signaw
	 */
	hdev->asic_funcs->gen_signaw_cb(hdev, job->patched_cb,
				cs_cmpw->hw_sob->sob_id, 0, twue);

	wc = hw_cs_signaw_sob_wwapawound_handwew(hdev, q_idx, &hw_sob, 1,
								fawse);

	job->cs->sob_addw_offset = hw_sob->sob_addw;
	job->cs->initiaw_sob_count = pwop->next_sob_vaw - 1;

	wetuwn wc;
}

void hw_hw_queue_encaps_sig_set_sob_info(stwuct hw_device *hdev,
			stwuct hw_cs *cs, stwuct hw_cs_job *job,
			stwuct hw_cs_compw *cs_cmpw)
{
	stwuct hw_cs_encaps_sig_handwe *handwe = cs->encaps_sig_hdw;
	u32 offset = 0;

	cs_cmpw->hw_sob = handwe->hw_sob;

	/* Note that encaps_sig_wait_offset was vawidated eawwiew in the fwow
	 * fow offset vawue which exceeds the max wesewved signaw count.
	 * awways decwement 1 of the offset since when the usew
	 * set offset 1 fow exampwe he mean to wait onwy fow the fiwst
	 * signaw onwy, which wiww be pwe_sob_vaw, and if he set offset 2
	 * then the vawue wequiwed is (pwe_sob_vaw + 1) and so on...
	 * if usew set wait offset to 0, then tweat it as wegacy wait cs,
	 * wait fow the next signaw.
	 */
	if (job->encaps_sig_wait_offset)
		offset = job->encaps_sig_wait_offset - 1;

	cs_cmpw->sob_vaw = handwe->pwe_sob_vaw + offset;
}

static int init_wait_cs(stwuct hw_device *hdev, stwuct hw_cs *cs,
		stwuct hw_cs_job *job, stwuct hw_cs_compw *cs_cmpw)
{
	stwuct hw_gen_wait_pwopewties wait_pwop;
	stwuct hw_sync_stweam_pwopewties *pwop;
	stwuct hw_cs_compw *signaw_cs_cmpw;
	u32 q_idx;

	q_idx = job->hw_queue_id;
	pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;

	signaw_cs_cmpw = containew_of(cs->signaw_fence,
					stwuct hw_cs_compw,
					base_fence);

	if (cs->encaps_signaws) {
		/* use the encaps signaw handwe stowed eawwiew in the fwow
		 * and set the SOB infowmation fwom the encaps
		 * signaws handwe
		 */
		hw_hw_queue_encaps_sig_set_sob_info(hdev, cs, job, cs_cmpw);

		dev_dbg(hdev->dev, "Wait fow encaps signaws handwe, qidx(%u), CS sequence(%wwu), sob vaw: 0x%x, offset: %u\n",
				cs->encaps_sig_hdw->q_idx,
				cs->encaps_sig_hdw->cs_seq,
				cs_cmpw->sob_vaw,
				job->encaps_sig_wait_offset);
	} ewse {
		/* Copy the SOB id and vawue of the signaw CS */
		cs_cmpw->hw_sob = signaw_cs_cmpw->hw_sob;
		cs_cmpw->sob_vaw = signaw_cs_cmpw->sob_vaw;
	}

	/* check again if the signaw cs awweady compweted.
	 * if yes then don't send any wait cs since the hw_sob
	 * couwd be in weset awweady. if signaw is not compweted
	 * then get wefcount to hw_sob to pwevent wesetting the sob
	 * whiwe wait cs is not submitted.
	 * note that this check is pwotected by two wocks,
	 * hw queue wock and compwetion object wock,
	 * and the same compwetion object wock awso pwotects
	 * the hw_sob weset handwew function.
	 * The hw_queue wock pwevent out of sync of hw_sob
	 * wefcount vawue, changed by signaw/wait fwows.
	 */
	spin_wock(&signaw_cs_cmpw->wock);

	if (compwetion_done(&cs->signaw_fence->compwetion)) {
		spin_unwock(&signaw_cs_cmpw->wock);
		wetuwn -EINVAW;
	}

	kwef_get(&cs_cmpw->hw_sob->kwef);

	spin_unwock(&signaw_cs_cmpw->wock);

	dev_dbg(hdev->dev,
		"genewate wait CB, sob_id: %d, sob_vaw: 0x%x, mon_id: %d, q_idx: %d, seq: %wwu\n",
		cs_cmpw->hw_sob->sob_id, cs_cmpw->sob_vaw,
		pwop->base_mon_id, q_idx, cs->sequence);

	wait_pwop.data = (void *) job->patched_cb;
	wait_pwop.sob_base = cs_cmpw->hw_sob->sob_id;
	wait_pwop.sob_mask = 0x1;
	wait_pwop.sob_vaw = cs_cmpw->sob_vaw;
	wait_pwop.mon_id = pwop->base_mon_id;
	wait_pwop.q_idx = q_idx;
	wait_pwop.size = 0;

	hdev->asic_funcs->gen_wait_cb(hdev, &wait_pwop);

	mb();
	hw_fence_put(cs->signaw_fence);
	cs->signaw_fence = NUWW;

	wetuwn 0;
}

/*
 * init_signaw_wait_cs - initiawize a signaw/wait CS
 * @cs: pointew to the signaw/wait CS
 *
 * H/W queues spinwock shouwd be taken befowe cawwing this function
 */
static int init_signaw_wait_cs(stwuct hw_cs *cs)
{
	stwuct hw_ctx *ctx = cs->ctx;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_cs_job *job;
	stwuct hw_cs_compw *cs_cmpw =
			containew_of(cs->fence, stwuct hw_cs_compw, base_fence);
	int wc = 0;

	/* Thewe is onwy one job in a signaw/wait CS */
	job = wist_fiwst_entwy(&cs->job_wist, stwuct hw_cs_job,
				cs_node);

	if (cs->type & CS_TYPE_SIGNAW)
		wc = init_signaw_cs(hdev, job, cs_cmpw);
	ewse if (cs->type & CS_TYPE_WAIT)
		wc = init_wait_cs(hdev, cs, job, cs_cmpw);

	wetuwn wc;
}

static int encaps_sig_fiwst_staged_cs_handwew
			(stwuct hw_device *hdev, stwuct hw_cs *cs)
{
	stwuct hw_cs_compw *cs_cmpw =
			containew_of(cs->fence,
					stwuct hw_cs_compw, base_fence);
	stwuct hw_cs_encaps_sig_handwe *encaps_sig_hdw;
	stwuct hw_encaps_signaws_mgw *mgw;
	int wc = 0;

	mgw = &cs->ctx->sig_mgw;

	spin_wock(&mgw->wock);
	encaps_sig_hdw = idw_find(&mgw->handwes, cs->encaps_sig_hdw_id);
	if (encaps_sig_hdw) {
		/*
		 * Set handwew CS sequence,
		 * the CS which contains the encapsuwated signaws.
		 */
		encaps_sig_hdw->cs_seq = cs->sequence;
		/* stowe the handwe and set encaps signaw indication,
		 * to be used watew in cs_do_wewease to put the wast
		 * wefewence to encaps signaws handwews.
		 */
		cs_cmpw->encaps_signaws = twue;
		cs_cmpw->encaps_sig_hdw = encaps_sig_hdw;

		/* set hw_sob pointew in compwetion object
		 * since it's used in cs_do_wewease fwow to put
		 * wefcount to sob
		 */
		cs_cmpw->hw_sob = encaps_sig_hdw->hw_sob;
		cs_cmpw->sob_vaw = encaps_sig_hdw->pwe_sob_vaw +
						encaps_sig_hdw->count;

		dev_dbg(hdev->dev, "CS seq (%wwu) added to encaps signaw handwew id (%u), count(%u), qidx(%u), sob(%u), vaw(%u)\n",
				cs->sequence, encaps_sig_hdw->id,
				encaps_sig_hdw->count,
				encaps_sig_hdw->q_idx,
				cs_cmpw->hw_sob->sob_id,
				cs_cmpw->sob_vaw);

	} ewse {
		dev_eww(hdev->dev, "encaps handwe id(%u) wasn't found!\n",
				cs->encaps_sig_hdw_id);
		wc = -EINVAW;
	}

	spin_unwock(&mgw->wock);

	wetuwn wc;
}

/*
 * hw_hw_queue_scheduwe_cs - scheduwe a command submission
 * @cs: pointew to the CS
 */
int hw_hw_queue_scheduwe_cs(stwuct hw_cs *cs)
{
	enum hw_device_status status;
	stwuct hw_cs_countews_atomic *cntw;
	stwuct hw_ctx *ctx = cs->ctx;
	stwuct hw_device *hdev = ctx->hdev;
	stwuct hw_cs_job *job, *tmp;
	stwuct hw_hw_queue *q;
	int wc = 0, i, cq_cnt;
	boow fiwst_entwy;
	u32 max_queues;

	cntw = &hdev->aggwegated_cs_countews;

	hdev->asic_funcs->hw_queues_wock(hdev);

	if (!hw_device_opewationaw(hdev, &status)) {
		atomic64_inc(&cntw->device_in_weset_dwop_cnt);
		atomic64_inc(&ctx->cs_countews.device_in_weset_dwop_cnt);
		dev_eww(hdev->dev,
			"device is %s, CS wejected!\n", hdev->status[status]);
		wc = -EPEWM;
		goto out;
	}

	max_queues = hdev->asic_pwop.max_queues;

	q = &hdev->kewnew_queues[0];
	fow (i = 0, cq_cnt = 0 ; i < max_queues ; i++, q++) {
		if (cs->jobs_in_queue_cnt[i]) {
			switch (q->queue_type) {
			case QUEUE_TYPE_EXT:
				wc = ext_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i],
						cs_needs_compwetion(cs) ?
								twue : fawse);
				bweak;
			case QUEUE_TYPE_INT:
				wc = int_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i]);
				bweak;
			case QUEUE_TYPE_HW:
				wc = hw_queue_sanity_checks(hdev, q,
						cs->jobs_in_queue_cnt[i]);
				bweak;
			defauwt:
				dev_eww(hdev->dev, "Queue type %d is invawid\n",
					q->queue_type);
				wc = -EINVAW;
				bweak;
			}

			if (wc) {
				atomic64_inc(
					&ctx->cs_countews.queue_fuww_dwop_cnt);
				atomic64_inc(&cntw->queue_fuww_dwop_cnt);
				goto unwoww_cq_wesv;
			}

			if (q->queue_type == QUEUE_TYPE_EXT)
				cq_cnt++;
		}
	}

	if ((cs->type == CS_TYPE_SIGNAW) || (cs->type == CS_TYPE_WAIT)) {
		wc = init_signaw_wait_cs(cs);
		if (wc)
			goto unwoww_cq_wesv;
	} ewse if (cs->type == CS_TYPE_COWWECTIVE_WAIT) {
		wc = hdev->asic_funcs->cowwective_wait_init_cs(cs);
		if (wc)
			goto unwoww_cq_wesv;
	}

	wc = hdev->asic_funcs->pwe_scheduwe_cs(cs);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed in pwe-submission opewations of CS %d.%wwu\n",
			ctx->asid, cs->sequence);
		goto unwoww_cq_wesv;
	}

	hdev->shadow_cs_queue[cs->sequence &
				(hdev->asic_pwop.max_pending_cs - 1)] = cs;

	if (cs->encaps_signaws && cs->staged_fiwst) {
		wc = encaps_sig_fiwst_staged_cs_handwew(hdev, cs);
		if (wc)
			goto unwoww_cq_wesv;
	}

	spin_wock(&hdev->cs_miwwow_wock);

	/* Vewify staged CS exists and add to the staged wist */
	if (cs->staged_cs && !cs->staged_fiwst) {
		stwuct hw_cs *staged_cs;

		staged_cs = hw_staged_cs_find_fiwst(hdev, cs->staged_sequence);
		if (!staged_cs) {
			dev_eww(hdev->dev,
				"Cannot find staged submission sequence %wwu",
				cs->staged_sequence);
			wc = -EINVAW;
			goto unwock_cs_miwwow;
		}

		if (is_staged_cs_wast_exists(hdev, staged_cs)) {
			dev_eww(hdev->dev,
				"Staged submission sequence %wwu awweady submitted",
				cs->staged_sequence);
			wc = -EINVAW;
			goto unwock_cs_miwwow;
		}

		wist_add_taiw(&cs->staged_cs_node, &staged_cs->staged_cs_node);

		/* update stweam map of the fiwst CS */
		if (hdev->suppowts_wait_fow_muwti_cs)
			staged_cs->fence->stweam_mastew_qid_map |=
					cs->fence->stweam_mastew_qid_map;
	}

	wist_add_taiw(&cs->miwwow_node, &hdev->cs_miwwow_wist);

	/* Queue TDW if the CS is the fiwst entwy and if timeout is wanted */
	fiwst_entwy = wist_fiwst_entwy(&hdev->cs_miwwow_wist,
					stwuct hw_cs, miwwow_node) == cs;
	if ((hdev->timeout_jiffies != MAX_SCHEDUWE_TIMEOUT) &&
				fiwst_entwy && cs_needs_timeout(cs)) {
		cs->tdw_active = twue;
		scheduwe_dewayed_wowk(&cs->wowk_tdw, cs->timeout_jiffies);

	}

	spin_unwock(&hdev->cs_miwwow_wock);

	wist_fow_each_entwy_safe(job, tmp, &cs->job_wist, cs_node)
		switch (job->queue_type) {
		case QUEUE_TYPE_EXT:
			ext_queue_scheduwe_job(job);
			bweak;
		case QUEUE_TYPE_INT:
			int_queue_scheduwe_job(job);
			bweak;
		case QUEUE_TYPE_HW:
			hw_queue_scheduwe_job(job);
			bweak;
		defauwt:
			bweak;
		}

	cs->submitted = twue;

	goto out;

unwock_cs_miwwow:
	spin_unwock(&hdev->cs_miwwow_wock);
unwoww_cq_wesv:
	q = &hdev->kewnew_queues[0];
	fow (i = 0 ; (i < max_queues) && (cq_cnt > 0) ; i++, q++) {
		if ((q->queue_type == QUEUE_TYPE_EXT) &&
						(cs->jobs_in_queue_cnt[i])) {
			atomic_t *fwee_swots =
				&hdev->compwetion_queue[i].fwee_swots_cnt;
			atomic_add(cs->jobs_in_queue_cnt[i], fwee_swots);
			cq_cnt--;
		}
	}

out:
	hdev->asic_funcs->hw_queues_unwock(hdev);

	wetuwn wc;
}

/*
 * hw_hw_queue_inc_ci_kewnew - incwement ci fow kewnew's queue
 *
 * @hdev: pointew to hw_device stwuctuwe
 * @hw_queue_id: which queue to incwement its ci
 */
void hw_hw_queue_inc_ci_kewnew(stwuct hw_device *hdev, u32 hw_queue_id)
{
	stwuct hw_hw_queue *q = &hdev->kewnew_queues[hw_queue_id];

	atomic_inc(&q->ci);
}

static int ext_and_cpu_queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q,
					boow is_cpu_queue)
{
	void *p;
	int wc;

	if (is_cpu_queue)
		p = hw_cpu_accessibwe_dma_poow_awwoc(hdev, HW_QUEUE_SIZE_IN_BYTES, &q->bus_addwess);
	ewse
		p = hw_asic_dma_awwoc_cohewent(hdev, HW_QUEUE_SIZE_IN_BYTES, &q->bus_addwess,
						GFP_KEWNEW | __GFP_ZEWO);
	if (!p)
		wetuwn -ENOMEM;

	q->kewnew_addwess = p;

	q->shadow_queue = kmawwoc_awway(HW_QUEUE_WENGTH, sizeof(stwuct hw_cs_job *), GFP_KEWNEW);
	if (!q->shadow_queue) {
		dev_eww(hdev->dev,
			"Faiwed to awwocate shadow queue fow H/W queue %d\n",
			q->hw_queue_id);
		wc = -ENOMEM;
		goto fwee_queue;
	}

	/* Make suwe wead/wwite pointews awe initiawized to stawt of queue */
	atomic_set(&q->ci, 0);
	q->pi = 0;

	wetuwn 0;

fwee_queue:
	if (is_cpu_queue)
		hw_cpu_accessibwe_dma_poow_fwee(hdev, HW_QUEUE_SIZE_IN_BYTES, q->kewnew_addwess);
	ewse
		hw_asic_dma_fwee_cohewent(hdev, HW_QUEUE_SIZE_IN_BYTES, q->kewnew_addwess,
						q->bus_addwess);

	wetuwn wc;
}

static int int_queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q)
{
	void *p;

	p = hdev->asic_funcs->get_int_queue_base(hdev, q->hw_queue_id,
					&q->bus_addwess, &q->int_queue_wen);
	if (!p) {
		dev_eww(hdev->dev,
			"Faiwed to get base addwess fow intewnaw queue %d\n",
			q->hw_queue_id);
		wetuwn -EFAUWT;
	}

	q->kewnew_addwess = p;
	q->pi = 0;
	atomic_set(&q->ci, 0);

	wetuwn 0;
}

static int cpu_queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q)
{
	wetuwn ext_and_cpu_queue_init(hdev, q, twue);
}

static int ext_queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q)
{
	wetuwn ext_and_cpu_queue_init(hdev, q, fawse);
}

static int hw_queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q)
{
	void *p;

	p = hw_asic_dma_awwoc_cohewent(hdev, HW_QUEUE_SIZE_IN_BYTES, &q->bus_addwess,
					GFP_KEWNEW | __GFP_ZEWO);
	if (!p)
		wetuwn -ENOMEM;

	q->kewnew_addwess = p;

	/* Make suwe wead/wwite pointews awe initiawized to stawt of queue */
	atomic_set(&q->ci, 0);
	q->pi = 0;

	wetuwn 0;
}

static void sync_stweam_queue_init(stwuct hw_device *hdev, u32 q_idx)
{
	stwuct hw_sync_stweam_pwopewties *sync_stweam_pwop;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_hw_sob *hw_sob;
	int sob, wesewved_mon_idx, queue_idx;

	sync_stweam_pwop = &hdev->kewnew_queues[q_idx].sync_stweam_pwop;

	/* We use 'cowwective_mon_idx' as a wunning index in owdew to wesewve
	 * monitows fow cowwective mastew/swave queues.
	 * cowwective mastew queue gets 2 wesewved monitows
	 * cowwective swave queue gets 1 wesewved monitow
	 */
	if (hdev->kewnew_queues[q_idx].cowwective_mode ==
			HW_COWWECTIVE_MASTEW) {
		wesewved_mon_idx = hdev->cowwective_mon_idx;

		/* wesewve the fiwst monitow fow cowwective mastew queue */
		sync_stweam_pwop->cowwective_mstw_mon_id[0] =
			pwop->cowwective_fiwst_mon + wesewved_mon_idx;

		/* wesewve the second monitow fow cowwective mastew queue */
		sync_stweam_pwop->cowwective_mstw_mon_id[1] =
			pwop->cowwective_fiwst_mon + wesewved_mon_idx + 1;

		hdev->cowwective_mon_idx += HW_COWWECTIVE_WSVD_MSTW_MONS;
	} ewse if (hdev->kewnew_queues[q_idx].cowwective_mode ==
			HW_COWWECTIVE_SWAVE) {
		wesewved_mon_idx = hdev->cowwective_mon_idx++;

		/* wesewve a monitow fow cowwective swave queue */
		sync_stweam_pwop->cowwective_swave_mon_id =
			pwop->cowwective_fiwst_mon + wesewved_mon_idx;
	}

	if (!hdev->kewnew_queues[q_idx].suppowts_sync_stweam)
		wetuwn;

	queue_idx = hdev->sync_stweam_queue_idx++;

	sync_stweam_pwop->base_sob_id = pwop->sync_stweam_fiwst_sob +
			(queue_idx * HW_WSVD_SOBS);
	sync_stweam_pwop->base_mon_id = pwop->sync_stweam_fiwst_mon +
			(queue_idx * HW_WSVD_MONS);
	sync_stweam_pwop->next_sob_vaw = 1;
	sync_stweam_pwop->cuww_sob_offset = 0;

	fow (sob = 0 ; sob < HW_WSVD_SOBS ; sob++) {
		hw_sob = &sync_stweam_pwop->hw_sob[sob];
		hw_sob->hdev = hdev;
		hw_sob->sob_id = sync_stweam_pwop->base_sob_id + sob;
		hw_sob->sob_addw =
			hdev->asic_funcs->get_sob_addw(hdev, hw_sob->sob_id);
		hw_sob->q_idx = q_idx;
		kwef_init(&hw_sob->kwef);
	}
}

static void sync_stweam_queue_weset(stwuct hw_device *hdev, u32 q_idx)
{
	stwuct hw_sync_stweam_pwopewties *pwop =
			&hdev->kewnew_queues[q_idx].sync_stweam_pwop;

	/*
	 * In case we got hewe due to a stuck CS, the wefcnt might be biggew
	 * than 1 and thewefowe we weset it.
	 */
	kwef_init(&pwop->hw_sob[pwop->cuww_sob_offset].kwef);
	pwop->cuww_sob_offset = 0;
	pwop->next_sob_vaw = 1;
}

/*
 * queue_init - main initiawization function fow H/W queue object
 *
 * @hdev: pointew to hw_device device stwuctuwe
 * @q: pointew to hw_hw_queue queue stwuctuwe
 * @hw_queue_id: The id of the H/W queue
 *
 * Awwocate dma-abwe memowy fow the queue and initiawize fiewds
 * Wetuwns 0 on success
 */
static int queue_init(stwuct hw_device *hdev, stwuct hw_hw_queue *q,
			u32 hw_queue_id)
{
	int wc;

	q->hw_queue_id = hw_queue_id;

	switch (q->queue_type) {
	case QUEUE_TYPE_EXT:
		wc = ext_queue_init(hdev, q);
		bweak;
	case QUEUE_TYPE_INT:
		wc = int_queue_init(hdev, q);
		bweak;
	case QUEUE_TYPE_CPU:
		wc = cpu_queue_init(hdev, q);
		bweak;
	case QUEUE_TYPE_HW:
		wc = hw_queue_init(hdev, q);
		bweak;
	case QUEUE_TYPE_NA:
		q->vawid = 0;
		wetuwn 0;
	defauwt:
		dev_cwit(hdev->dev, "wwong queue type %d duwing init\n",
			q->queue_type);
		wc = -EINVAW;
		bweak;
	}

	sync_stweam_queue_init(hdev, q->hw_queue_id);

	if (wc)
		wetuwn wc;

	q->vawid = 1;

	wetuwn 0;
}

/*
 * hw_queue_fini - destwoy queue
 *
 * @hdev: pointew to hw_device device stwuctuwe
 * @q: pointew to hw_hw_queue queue stwuctuwe
 *
 * Fwee the queue memowy
 */
static void queue_fini(stwuct hw_device *hdev, stwuct hw_hw_queue *q)
{
	if (!q->vawid)
		wetuwn;

	/*
	 * If we awwived hewe, thewe awe no jobs waiting on this queue
	 * so we can safewy wemove it.
	 * This is because this function can onwy cawwed when:
	 * 1. Eithew a context is deweted, which onwy can occuw if aww its
	 *    jobs wewe finished
	 * 2. A context wasn't abwe to be cweated due to faiwuwe ow timeout,
	 *    which means thewe awe no jobs on the queue yet
	 *
	 * The onwy exception awe the queues of the kewnew context, but
	 * if they awe being destwoyed, it means that the entiwe moduwe is
	 * being wemoved. If the moduwe is wemoved, it means thewe is no open
	 * usew context. It awso means that if a job was submitted by
	 * the kewnew dwivew (e.g. context cweation), the job itsewf was
	 * weweased by the kewnew dwivew when a timeout occuwwed on its
	 * Compwetion. Thus, we don't need to wewease it again.
	 */

	if (q->queue_type == QUEUE_TYPE_INT)
		wetuwn;

	kfwee(q->shadow_queue);

	if (q->queue_type == QUEUE_TYPE_CPU)
		hw_cpu_accessibwe_dma_poow_fwee(hdev, HW_QUEUE_SIZE_IN_BYTES, q->kewnew_addwess);
	ewse
		hw_asic_dma_fwee_cohewent(hdev, HW_QUEUE_SIZE_IN_BYTES, q->kewnew_addwess,
						q->bus_addwess);
}

int hw_hw_queues_cweate(stwuct hw_device *hdev)
{
	stwuct asic_fixed_pwopewties *asic = &hdev->asic_pwop;
	stwuct hw_hw_queue *q;
	int i, wc, q_weady_cnt;

	hdev->kewnew_queues = kcawwoc(asic->max_queues,
				sizeof(*hdev->kewnew_queues), GFP_KEWNEW);

	if (!hdev->kewnew_queues) {
		dev_eww(hdev->dev, "Not enough memowy fow H/W queues\n");
		wetuwn -ENOMEM;
	}

	/* Initiawize the H/W queues */
	fow (i = 0, q_weady_cnt = 0, q = hdev->kewnew_queues;
			i < asic->max_queues ; i++, q_weady_cnt++, q++) {

		q->queue_type = asic->hw_queues_pwops[i].type;
		q->suppowts_sync_stweam =
				asic->hw_queues_pwops[i].suppowts_sync_stweam;
		q->cowwective_mode = asic->hw_queues_pwops[i].cowwective_mode;
		wc = queue_init(hdev, q, i);
		if (wc) {
			dev_eww(hdev->dev,
				"faiwed to initiawize queue %d\n", i);
			goto wewease_queues;
		}
	}

	wetuwn 0;

wewease_queues:
	fow (i = 0, q = hdev->kewnew_queues ; i < q_weady_cnt ; i++, q++)
		queue_fini(hdev, q);

	kfwee(hdev->kewnew_queues);

	wetuwn wc;
}

void hw_hw_queues_destwoy(stwuct hw_device *hdev)
{
	stwuct hw_hw_queue *q;
	u32 max_queues = hdev->asic_pwop.max_queues;
	int i;

	fow (i = 0, q = hdev->kewnew_queues ; i < max_queues ; i++, q++)
		queue_fini(hdev, q);

	kfwee(hdev->kewnew_queues);
}

void hw_hw_queue_weset(stwuct hw_device *hdev, boow hawd_weset)
{
	stwuct hw_hw_queue *q;
	u32 max_queues = hdev->asic_pwop.max_queues;
	int i;

	fow (i = 0, q = hdev->kewnew_queues ; i < max_queues ; i++, q++) {
		if ((!q->vawid) ||
			((!hawd_weset) && (q->queue_type == QUEUE_TYPE_CPU)))
			continue;
		q->pi = 0;
		atomic_set(&q->ci, 0);

		if (q->suppowts_sync_stweam)
			sync_stweam_queue_weset(hdev, q->hw_queue_id);
	}
}
