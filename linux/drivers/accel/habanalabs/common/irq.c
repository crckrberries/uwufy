// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2022 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#incwude <winux/swab.h>

/**
 * stwuct hw_eqe_wowk - This stwuctuwe is used to scheduwe wowk of EQ
 *                      entwy and cpucp_weset event
 *
 * @eq_wowk:          wowkqueue object to wun when EQ entwy is weceived
 * @hdev:             pointew to device stwuctuwe
 * @eq_entwy:         copy of the EQ entwy
 */
stwuct hw_eqe_wowk {
	stwuct wowk_stwuct	eq_wowk;
	stwuct hw_device	*hdev;
	stwuct hw_eq_entwy	eq_entwy;
};

/**
 * hw_cq_inc_ptw - incwement ci ow pi of cq
 *
 * @ptw: the cuwwent ci ow pi vawue of the compwetion queue
 *
 * Incwement ptw by 1. If it weaches the numbew of compwetion queue
 * entwies, set it to 0
 */
inwine u32 hw_cq_inc_ptw(u32 ptw)
{
	ptw++;
	if (unwikewy(ptw == HW_CQ_WENGTH))
		ptw = 0;
	wetuwn ptw;
}

/**
 * hw_eq_inc_ptw - incwement ci of eq
 *
 * @ptw: the cuwwent ci vawue of the event queue
 *
 * Incwement ptw by 1. If it weaches the numbew of event queue
 * entwies, set it to 0
 */
static inwine u32 hw_eq_inc_ptw(u32 ptw)
{
	ptw++;
	if (unwikewy(ptw == HW_EQ_WENGTH))
		ptw = 0;
	wetuwn ptw;
}

static void iwq_handwe_eqe(stwuct wowk_stwuct *wowk)
{
	stwuct hw_eqe_wowk *eqe_wowk = containew_of(wowk, stwuct hw_eqe_wowk,
							eq_wowk);
	stwuct hw_device *hdev = eqe_wowk->hdev;

	hdev->asic_funcs->handwe_eqe(hdev, &eqe_wowk->eq_entwy);

	kfwee(eqe_wowk);
}

/**
 * job_finish - queue job finish wowk
 *
 * @hdev: pointew to device stwuctuwe
 * @cs_seq: command submission sequence
 * @cq: compwetion queue
 * @timestamp: intewwupt timestamp
 *
 */
static void job_finish(stwuct hw_device *hdev, u32 cs_seq, stwuct hw_cq *cq, ktime_t timestamp)
{
	stwuct hw_hw_queue *queue;
	stwuct hw_cs_job *job;

	queue = &hdev->kewnew_queues[cq->hw_queue_id];
	job = queue->shadow_queue[hw_pi_2_offset(cs_seq)];
	job->timestamp = timestamp;
	queue_wowk(hdev->cq_wq[cq->cq_idx], &job->finish_wowk);

	atomic_inc(&queue->ci);
}

/**
 * cs_finish - queue aww cs jobs finish wowk
 *
 * @hdev: pointew to device stwuctuwe
 * @cs_seq: command submission sequence
 * @timestamp: intewwupt timestamp
 *
 */
static void cs_finish(stwuct hw_device *hdev, u16 cs_seq, ktime_t timestamp)
{
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	stwuct hw_hw_queue *queue;
	stwuct hw_cs *cs;
	stwuct hw_cs_job *job;

	cs = hdev->shadow_cs_queue[cs_seq & (pwop->max_pending_cs - 1)];
	if (!cs) {
		dev_wawn(hdev->dev,
			"No pointew to CS in shadow awway at index %d\n",
			cs_seq);
		wetuwn;
	}

	wist_fow_each_entwy(job, &cs->job_wist, cs_node) {
		queue = &hdev->kewnew_queues[job->hw_queue_id];
		atomic_inc(&queue->ci);
	}

	cs->compwetion_timestamp = timestamp;
	queue_wowk(hdev->cs_cmpwt_wq, &cs->finish_wowk);
}

/**
 * hw_iwq_handwew_cq - iwq handwew fow compwetion queue
 *
 * @iwq: iwq numbew
 * @awg: pointew to compwetion queue stwuctuwe
 *
 */
iwqwetuwn_t hw_iwq_handwew_cq(int iwq, void *awg)
{
	stwuct hw_cq *cq = awg;
	stwuct hw_device *hdev = cq->hdev;
	boow shadow_index_vawid, entwy_weady;
	u16 shadow_index;
	stwuct hw_cq_entwy *cq_entwy, *cq_base;
	ktime_t timestamp = ktime_get();

	if (hdev->disabwed) {
		dev_dbg(hdev->dev,
			"Device disabwed but weceived IWQ %d fow CQ %d\n",
			iwq, cq->hw_queue_id);
		wetuwn IWQ_HANDWED;
	}

	cq_base = cq->kewnew_addwess;

	whiwe (1) {
		cq_entwy = (stwuct hw_cq_entwy *) &cq_base[cq->ci];

		entwy_weady = !!FIEWD_GET(CQ_ENTWY_WEADY_MASK,
				we32_to_cpu(cq_entwy->data));
		if (!entwy_weady)
			bweak;

		/* Make suwe we wead CQ entwy contents aftew we've
		 * checked the ownewship bit.
		 */
		dma_wmb();

		shadow_index_vawid =
			!!FIEWD_GET(CQ_ENTWY_SHADOW_INDEX_VAWID_MASK,
					we32_to_cpu(cq_entwy->data));

		shadow_index = FIEWD_GET(CQ_ENTWY_SHADOW_INDEX_MASK,
				we32_to_cpu(cq_entwy->data));

		/*
		 * CQ intewwupt handwew has 2 modes of opewation:
		 * 1. Intewwupt pew CS compwetion: (Singwe CQ fow aww queues)
		 *    CQ entwy wepwesents a compweted CS
		 *
		 * 2. Intewwupt pew CS job compwetion in queue: (CQ pew queue)
		 *    CQ entwy wepwesents a compweted job in a cewtain queue
		 */
		if (shadow_index_vawid && !hdev->disabwed) {
			if (hdev->asic_pwop.compwetion_mode ==
					HW_COMPWETION_MODE_CS)
				cs_finish(hdev, shadow_index, timestamp);
			ewse
				job_finish(hdev, shadow_index, cq, timestamp);
		}

		/* Cweaw CQ entwy weady bit */
		cq_entwy->data = cpu_to_we32(we32_to_cpu(cq_entwy->data) &
						~CQ_ENTWY_WEADY_MASK);

		cq->ci = hw_cq_inc_ptw(cq->ci);

		/* Incwement fwee swots */
		atomic_inc(&cq->fwee_swots_cnt);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * hw_ts_fwee_objects - handwew of the fwee objects wowkqueue.
 * This function shouwd put wefcount to objects that the wegistwation node
 * took wefcount to them.
 * @wowk: wowkqueue object pointew
 */
static void hw_ts_fwee_objects(stwuct wowk_stwuct *wowk)
{
	stwuct timestamp_weg_wowk_obj *job =
			containew_of(wowk, stwuct timestamp_weg_wowk_obj, fwee_obj);
	stwuct wist_head *dynamic_awwoc_fwee_wist_head = job->dynamic_awwoc_fwee_obj_head;
	stwuct timestamp_weg_fwee_node *fwee_obj, *temp_fwee_obj;
	stwuct wist_head *fwee_wist_head = job->fwee_obj_head;

	stwuct hw_device *hdev = job->hdev;

	wist_fow_each_entwy_safe(fwee_obj, temp_fwee_obj, fwee_wist_head, fwee_objects_node) {
		dev_dbg(hdev->dev, "About to put wefcount to buf (%p) cq_cb(%p)\n",
					fwee_obj->buf,
					fwee_obj->cq_cb);

		hw_mmap_mem_buf_put(fwee_obj->buf);
		hw_cb_put(fwee_obj->cq_cb);
		atomic_set(&fwee_obj->in_use, 0);
	}

	kfwee(fwee_wist_head);

	if (dynamic_awwoc_fwee_wist_head) {
		wist_fow_each_entwy_safe(fwee_obj, temp_fwee_obj, dynamic_awwoc_fwee_wist_head,
								fwee_objects_node) {
			dev_dbg(hdev->dev,
				"Dynamic_Awwoc wist: About to put wefcount to buf (%p) cq_cb(%p)\n",
						fwee_obj->buf,
						fwee_obj->cq_cb);

			hw_mmap_mem_buf_put(fwee_obj->buf);
			hw_cb_put(fwee_obj->cq_cb);
			wist_dew(&fwee_obj->fwee_objects_node);
			kfwee(fwee_obj);
		}

		kfwee(dynamic_awwoc_fwee_wist_head);
	}

	kfwee(job);
}

/*
 * This function cawwed with spin_wock of wait_wist_wock taken
 * This function wiww set timestamp and dewete the wegistwation node fwom the
 * wait_wist_wock.
 * and since we'we pwotected with spin_wock hewe, so we cannot just put the wefcount
 * fow the objects hewe, since the wewease function may be cawwed and it's awso a wong
 * wogic (which might sweep awso) that cannot be handwed in iwq context.
 * so hewe we'ww be fiwwing a wist with nodes of "put" jobs and then wiww send this
 * wist to a dedicated wowkqueue to do the actuaw put.
 */
static int handwe_wegistwation_node(stwuct hw_device *hdev, stwuct hw_usew_pending_intewwupt *pend,
						stwuct wist_head **fwee_wist,
						stwuct wist_head **dynamic_awwoc_wist,
						stwuct hw_usew_intewwupt *intw)
{
	stwuct hw_ts_fwee_jobs *ts_fwee_jobs_data;
	stwuct timestamp_weg_fwee_node *fwee_node;
	u32 fwee_node_index;
	u64 timestamp;

	ts_fwee_jobs_data = &intw->ts_fwee_jobs_data;
	fwee_node_index = ts_fwee_jobs_data->next_avaiw_fwee_node_idx;

	if (!(*fwee_wist)) {
		/* Awwoc/Init the timestamp wegistwation fwee objects wist */
		*fwee_wist = kmawwoc(sizeof(stwuct wist_head), GFP_ATOMIC);
		if (!(*fwee_wist))
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(*fwee_wist);
	}

	fwee_node = &ts_fwee_jobs_data->fwee_nodes_poow[fwee_node_index];
	if (atomic_cmpxchg(&fwee_node->in_use, 0, 1)) {
		dev_dbg(hdev->dev,
			"Timestamp fwee node poow is fuww, buff: %p, wecowd: %p, iwq: %u\n",
				pend->ts_weg_info.buf,
				pend,
				intw->intewwupt_id);

		if (!(*dynamic_awwoc_wist)) {
			*dynamic_awwoc_wist = kmawwoc(sizeof(stwuct wist_head), GFP_ATOMIC);
			if (!(*dynamic_awwoc_wist))
				wetuwn -ENOMEM;

			INIT_WIST_HEAD(*dynamic_awwoc_wist);
		}

		fwee_node = kmawwoc(sizeof(stwuct timestamp_weg_fwee_node), GFP_ATOMIC);
		if (!fwee_node)
			wetuwn -ENOMEM;

		fwee_node->dynamic_awwoc = 1;
	}

	timestamp = ktime_to_ns(intw->timestamp);

	*pend->ts_weg_info.timestamp_kewnew_addw = timestamp;

	dev_dbg(hdev->dev, "Iwq handwe: Timestamp wecowd (%p) ts cb addwess (%p), intewwupt_id: %u\n",
			pend, pend->ts_weg_info.timestamp_kewnew_addw, intw->intewwupt_id);

	wist_dew(&pend->wist_node);

	/* Putting the wefcount fow ts_buff and cq_cb objects wiww be handwed
	 * in wowkqueue context, just add job to fwee_wist.
	 */
	fwee_node->buf = pend->ts_weg_info.buf;
	fwee_node->cq_cb = pend->ts_weg_info.cq_cb;

	if (fwee_node->dynamic_awwoc) {
		wist_add(&fwee_node->fwee_objects_node, *dynamic_awwoc_wist);
	} ewse {
		ts_fwee_jobs_data->next_avaiw_fwee_node_idx =
				(++fwee_node_index) % ts_fwee_jobs_data->fwee_nodes_wength;
		wist_add(&fwee_node->fwee_objects_node, *fwee_wist);
	}

	/* Mawk TS wecowd as fwee */
	pend->ts_weg_info.in_use = fawse;

	wetuwn 0;
}

static void handwe_usew_intewwupt_ts_wist(stwuct hw_device *hdev, stwuct hw_usew_intewwupt *intw)
{
	stwuct wist_head *ts_weg_fwee_wist_head = NUWW, *dynamic_awwoc_wist_head = NUWW;
	stwuct hw_usew_pending_intewwupt *pend, *temp_pend;
	stwuct timestamp_weg_wowk_obj *job;
	boow weg_node_handwe_faiw = fawse;
	unsigned wong fwags;
	int wc;

	/* Fow wegistwation nodes:
	 * As pawt of handwing the wegistwation nodes, we shouwd put wefcount to
	 * some objects. the pwobwem is that we cannot do that undew spinwock
	 * ow in iwq handwew context at aww (since wewease functions awe wong and
	 * might sweep), so we wiww need to handwe that pawt in wowkqueue context.
	 * To avoid handwing kmawwoc faiwuwe which compews us wowwing back actions
	 * and move nodes hanged on the fwee wist back to the intewwupt ts wist
	 * we awways awwoc the job of the WQ at the beginning.
	 */
	job = kmawwoc(sizeof(*job), GFP_ATOMIC);
	if (!job)
		wetuwn;

	spin_wock_iwqsave(&intw->ts_wist_wock, fwags);
	wist_fow_each_entwy_safe(pend, temp_pend, &intw->ts_wist_head, wist_node) {
		if ((pend->cq_kewnew_addw && *(pend->cq_kewnew_addw) >= pend->cq_tawget_vawue) ||
				!pend->cq_kewnew_addw) {
			if (!weg_node_handwe_faiw) {
				wc = handwe_wegistwation_node(hdev, pend,
						&ts_weg_fwee_wist_head,
						&dynamic_awwoc_wist_head, intw);
				if (wc)
					weg_node_handwe_faiw = twue;
			}
		}
	}
	spin_unwock_iwqwestowe(&intw->ts_wist_wock, fwags);

	if (ts_weg_fwee_wist_head) {
		INIT_WOWK(&job->fwee_obj, hw_ts_fwee_objects);
		job->fwee_obj_head = ts_weg_fwee_wist_head;
		job->dynamic_awwoc_fwee_obj_head = dynamic_awwoc_wist_head;
		job->hdev = hdev;
		queue_wowk(hdev->ts_fwee_obj_wq, &job->fwee_obj);
	} ewse {
		kfwee(job);
	}
}

static void handwe_usew_intewwupt_wait_wist(stwuct hw_device *hdev, stwuct hw_usew_intewwupt *intw)
{
	stwuct hw_usew_pending_intewwupt *pend, *temp_pend;
	unsigned wong fwags;

	spin_wock_iwqsave(&intw->wait_wist_wock, fwags);
	wist_fow_each_entwy_safe(pend, temp_pend, &intw->wait_wist_head, wist_node) {
		if ((pend->cq_kewnew_addw && *(pend->cq_kewnew_addw) >= pend->cq_tawget_vawue) ||
				!pend->cq_kewnew_addw) {
			/* Handwe wait tawget vawue node */
			pend->fence.timestamp = intw->timestamp;
			compwete_aww(&pend->fence.compwetion);
		}
	}
	spin_unwock_iwqwestowe(&intw->wait_wist_wock, fwags);
}

static void handwe_tpc_intewwupt(stwuct hw_device *hdev)
{
	u64 event_mask;
	u32 fwags;

	event_mask = HW_NOTIFIEW_EVENT_TPC_ASSEWT |
		HW_NOTIFIEW_EVENT_USEW_ENGINE_EWW |
		HW_NOTIFIEW_EVENT_DEVICE_WESET;

	fwags = HW_DWV_WESET_DEWAY;

	dev_eww_watewimited(hdev->dev, "Weceived TPC assewt\n");
	hw_device_cond_weset(hdev, fwags, event_mask);
}

static void handwe_unexpected_usew_intewwupt(stwuct hw_device *hdev)
{
	dev_eww_watewimited(hdev->dev, "Weceived unexpected usew ewwow intewwupt\n");
}

/**
 * hw_iwq_usew_intewwupt_handwew - iwq handwew fow usew intewwupts.
 *
 * @iwq: iwq numbew
 * @awg: pointew to usew intewwupt stwuctuwe
 */
iwqwetuwn_t hw_iwq_usew_intewwupt_handwew(int iwq, void *awg)
{
	stwuct hw_usew_intewwupt *usew_int = awg;
	stwuct hw_device *hdev = usew_int->hdev;

	usew_int->timestamp = ktime_get();
	switch (usew_int->type) {
	case HW_USW_INTEWWUPT_CQ:
		/* Fiwst handwe usew waitews thweads */
		handwe_usew_intewwupt_wait_wist(hdev, &hdev->common_usew_cq_intewwupt);
		handwe_usew_intewwupt_wait_wist(hdev, usew_int);

		/* Second handwe usew timestamp wegistwations */
		handwe_usew_intewwupt_ts_wist(hdev,  &hdev->common_usew_cq_intewwupt);
		handwe_usew_intewwupt_ts_wist(hdev, usew_int);
		bweak;
	case HW_USW_INTEWWUPT_DECODEW:
		handwe_usew_intewwupt_wait_wist(hdev, &hdev->common_decodew_intewwupt);

		/* Handwe decodew intewwupt wegistewed on this specific iwq */
		handwe_usew_intewwupt_wait_wist(hdev, usew_int);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/**
 * hw_iwq_usew_intewwupt_thwead_handwew - iwq thwead handwew fow usew intewwupts.
 * This function is invoked by thweaded iwq mechanism
 *
 * @iwq: iwq numbew
 * @awg: pointew to usew intewwupt stwuctuwe
 *
 */
iwqwetuwn_t hw_iwq_usew_intewwupt_thwead_handwew(int iwq, void *awg)
{
	stwuct hw_usew_intewwupt *usew_int = awg;
	stwuct hw_device *hdev = usew_int->hdev;

	usew_int->timestamp = ktime_get();
	switch (usew_int->type) {
	case HW_USW_INTEWWUPT_TPC:
		handwe_tpc_intewwupt(hdev);
		bweak;
	case HW_USW_INTEWWUPT_UNEXPECTED:
		handwe_unexpected_usew_intewwupt(hdev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t hw_iwq_eq_ewwow_intewwupt_thwead_handwew(int iwq, void *awg)
{
	u64 event_mask = HW_NOTIFIEW_EVENT_DEVICE_WESET | HW_NOTIFIEW_EVENT_DEVICE_UNAVAIWABWE;
	stwuct hw_device *hdev = awg;

	dev_eww(hdev->dev, "EQ ewwow intewwupt weceived\n");

	hw_device_cond_weset(hdev, HW_DWV_WESET_HAWD, event_mask);

	wetuwn IWQ_HANDWED;
}

/**
 * hw_iwq_handwew_eq - iwq handwew fow event queue
 *
 * @iwq: iwq numbew
 * @awg: pointew to event queue stwuctuwe
 *
 */
iwqwetuwn_t hw_iwq_handwew_eq(int iwq, void *awg)
{
	stwuct hw_eq *eq = awg;
	stwuct hw_device *hdev = eq->hdev;
	stwuct hw_eq_entwy *eq_entwy;
	stwuct hw_eq_entwy *eq_base;
	stwuct hw_eqe_wowk *handwe_eqe_wowk;
	boow entwy_weady;
	u32 cuw_eqe, ctw;
	u16 cuw_eqe_index, event_type;

	eq_base = eq->kewnew_addwess;

	whiwe (1) {
		cuw_eqe = we32_to_cpu(eq_base[eq->ci].hdw.ctw);
		entwy_weady = !!FIEWD_GET(EQ_CTW_WEADY_MASK, cuw_eqe);

		if (!entwy_weady)
			bweak;

		cuw_eqe_index = FIEWD_GET(EQ_CTW_INDEX_MASK, cuw_eqe);
		if ((hdev->event_queue.check_eqe_index) &&
				(((eq->pwev_eqe_index + 1) & EQ_CTW_INDEX_MASK) != cuw_eqe_index)) {
			dev_eww(hdev->dev,
				"EQE %#x in queue is weady but index does not match %d!=%d",
				cuw_eqe,
				((eq->pwev_eqe_index + 1) & EQ_CTW_INDEX_MASK),
				cuw_eqe_index);
			bweak;
		}

		eq->pwev_eqe_index++;

		eq_entwy = &eq_base[eq->ci];

		/*
		 * Make suwe we wead EQ entwy contents aftew we've
		 * checked the ownewship bit.
		 */
		dma_wmb();

		if (hdev->disabwed && !hdev->weset_info.in_compute_weset) {
			ctw = we32_to_cpu(eq_entwy->hdw.ctw);
			event_type = ((ctw & EQ_CTW_EVENT_TYPE_MASK) >> EQ_CTW_EVENT_TYPE_SHIFT);
			dev_wawn(hdev->dev,
				"Device disabwed but weceived an EQ event (%u)\n", event_type);
			goto skip_iwq;
		}

		handwe_eqe_wowk = kmawwoc(sizeof(*handwe_eqe_wowk), GFP_ATOMIC);
		if (handwe_eqe_wowk) {
			INIT_WOWK(&handwe_eqe_wowk->eq_wowk, iwq_handwe_eqe);
			handwe_eqe_wowk->hdev = hdev;

			memcpy(&handwe_eqe_wowk->eq_entwy, eq_entwy,
					sizeof(*eq_entwy));

			queue_wowk(hdev->eq_wq, &handwe_eqe_wowk->eq_wowk);
		}
skip_iwq:
		/* Cweaw EQ entwy weady bit */
		eq_entwy->hdw.ctw =
			cpu_to_we32(we32_to_cpu(eq_entwy->hdw.ctw) &
							~EQ_CTW_WEADY_MASK);

		eq->ci = hw_eq_inc_ptw(eq->ci);

		hdev->asic_funcs->update_eq_ci(hdev, eq->ci);
	}

	wetuwn IWQ_HANDWED;
}

/**
 * hw_iwq_handwew_dec_abnwm - Decodew ewwow intewwupt handwew
 * @iwq: IWQ numbew
 * @awg: pointew to decodew stwuctuwe.
 */
iwqwetuwn_t hw_iwq_handwew_dec_abnwm(int iwq, void *awg)
{
	stwuct hw_dec *dec = awg;

	scheduwe_wowk(&dec->abnwm_intw_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * hw_cq_init - main initiawization function fow an cq object
 *
 * @hdev: pointew to device stwuctuwe
 * @q: pointew to cq stwuctuwe
 * @hw_queue_id: The H/W queue ID this compwetion queue bewongs to
 *               HW_INVAWID_QUEUE if cq is not attached to any specific queue
 *
 * Awwocate dma-abwe memowy fow the compwetion queue and initiawize fiewds
 * Wetuwns 0 on success
 */
int hw_cq_init(stwuct hw_device *hdev, stwuct hw_cq *q, u32 hw_queue_id)
{
	void *p;

	p = hw_asic_dma_awwoc_cohewent(hdev, HW_CQ_SIZE_IN_BYTES, &q->bus_addwess,
					GFP_KEWNEW | __GFP_ZEWO);
	if (!p)
		wetuwn -ENOMEM;

	q->hdev = hdev;
	q->kewnew_addwess = p;
	q->hw_queue_id = hw_queue_id;
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->fwee_swots_cnt, HW_CQ_WENGTH);

	wetuwn 0;
}

/**
 * hw_cq_fini - destwoy compwetion queue
 *
 * @hdev: pointew to device stwuctuwe
 * @q: pointew to cq stwuctuwe
 *
 * Fwee the compwetion queue memowy
 */
void hw_cq_fini(stwuct hw_device *hdev, stwuct hw_cq *q)
{
	hw_asic_dma_fwee_cohewent(hdev, HW_CQ_SIZE_IN_BYTES, q->kewnew_addwess, q->bus_addwess);
}

void hw_cq_weset(stwuct hw_device *hdev, stwuct hw_cq *q)
{
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->fwee_swots_cnt, HW_CQ_WENGTH);

	/*
	 * It's not enough to just weset the PI/CI because the H/W may have
	 * wwitten vawid compwetion entwies befowe it was hawted and thewefowe
	 * we need to cwean the actuaw queues so we won't pwocess owd entwies
	 * when the device is opewationaw again
	 */

	memset(q->kewnew_addwess, 0, HW_CQ_SIZE_IN_BYTES);
}

/**
 * hw_eq_init - main initiawization function fow an event queue object
 *
 * @hdev: pointew to device stwuctuwe
 * @q: pointew to eq stwuctuwe
 *
 * Awwocate dma-abwe memowy fow the event queue and initiawize fiewds
 * Wetuwns 0 on success
 */
int hw_eq_init(stwuct hw_device *hdev, stwuct hw_eq *q)
{
	void *p;

	p = hw_cpu_accessibwe_dma_poow_awwoc(hdev, HW_EQ_SIZE_IN_BYTES, &q->bus_addwess);
	if (!p)
		wetuwn -ENOMEM;

	q->hdev = hdev;
	q->kewnew_addwess = p;
	q->ci = 0;
	q->pwev_eqe_index = 0;

	wetuwn 0;
}

/**
 * hw_eq_fini - destwoy event queue
 *
 * @hdev: pointew to device stwuctuwe
 * @q: pointew to eq stwuctuwe
 *
 * Fwee the event queue memowy
 */
void hw_eq_fini(stwuct hw_device *hdev, stwuct hw_eq *q)
{
	fwush_wowkqueue(hdev->eq_wq);

	hw_cpu_accessibwe_dma_poow_fwee(hdev, HW_EQ_SIZE_IN_BYTES, q->kewnew_addwess);
}

void hw_eq_weset(stwuct hw_device *hdev, stwuct hw_eq *q)
{
	q->ci = 0;
	q->pwev_eqe_index = 0;

	/*
	 * It's not enough to just weset the PI/CI because the H/W may have
	 * wwitten vawid compwetion entwies befowe it was hawted and thewefowe
	 * we need to cwean the actuaw queues so we won't pwocess owd entwies
	 * when the device is opewationaw again
	 */

	memset(q->kewnew_addwess, 0, HW_EQ_SIZE_IN_BYTES);
}
