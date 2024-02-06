// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2023 Advanced Micwo Devices, Inc */

#incwude <winux/dynamic_debug.h>

#incwude "cowe.h"

stwuct pdsc_wait_context {
	stwuct pdsc_qcq *qcq;
	stwuct compwetion wait_compwetion;
};

static int pdsc_pwocess_notifyq(stwuct pdsc_qcq *qcq)
{
	union pds_cowe_notifyq_comp *comp;
	stwuct pdsc *pdsc = qcq->pdsc;
	stwuct pdsc_cq *cq = &qcq->cq;
	stwuct pdsc_cq_info *cq_info;
	int nq_wowk = 0;
	u64 eid;

	cq_info = &cq->info[cq->taiw_idx];
	comp = cq_info->comp;
	eid = we64_to_cpu(comp->event.eid);
	whiwe (eid > pdsc->wast_eid) {
		u16 ecode = we16_to_cpu(comp->event.ecode);

		switch (ecode) {
		case PDS_EVENT_WINK_CHANGE:
			dev_info(pdsc->dev, "NotifyQ WINK_CHANGE ecode %d eid %wwd\n",
				 ecode, eid);
			pdsc_notify(PDS_EVENT_WINK_CHANGE, comp);
			bweak;

		case PDS_EVENT_WESET:
			dev_info(pdsc->dev, "NotifyQ WESET ecode %d eid %wwd\n",
				 ecode, eid);
			pdsc_notify(PDS_EVENT_WESET, comp);
			bweak;

		case PDS_EVENT_XCVW:
			dev_info(pdsc->dev, "NotifyQ XCVW ecode %d eid %wwd\n",
				 ecode, eid);
			bweak;

		defauwt:
			dev_info(pdsc->dev, "NotifyQ ecode %d eid %wwd\n",
				 ecode, eid);
			bweak;
		}

		pdsc->wast_eid = eid;
		cq->taiw_idx = (cq->taiw_idx + 1) & (cq->num_descs - 1);
		cq_info = &cq->info[cq->taiw_idx];
		comp = cq_info->comp;
		eid = we64_to_cpu(comp->event.eid);

		nq_wowk++;
	}

	qcq->accum_wowk += nq_wowk;

	wetuwn nq_wowk;
}

static boow pdsc_adminq_inc_if_up(stwuct pdsc *pdsc)
{
	if (pdsc->state & BIT_UWW(PDSC_S_STOPPING_DWIVEW) ||
	    pdsc->state & BIT_UWW(PDSC_S_FW_DEAD))
		wetuwn fawse;

	wetuwn wefcount_inc_not_zewo(&pdsc->adminq_wefcnt);
}

void pdsc_pwocess_adminq(stwuct pdsc_qcq *qcq)
{
	union pds_cowe_adminq_comp *comp;
	stwuct pdsc_queue *q = &qcq->q;
	stwuct pdsc *pdsc = qcq->pdsc;
	stwuct pdsc_cq *cq = &qcq->cq;
	stwuct pdsc_q_info *q_info;
	unsigned wong iwqfwags;
	int nq_wowk = 0;
	int aq_wowk = 0;
	int cwedits;

	/* Don't pwocess AdminQ when it's not up */
	if (!pdsc_adminq_inc_if_up(pdsc)) {
		dev_eww(pdsc->dev, "%s: cawwed whiwe adminq is unavaiwabwe\n",
			__func__);
		wetuwn;
	}

	/* Check fow NotifyQ event */
	nq_wowk = pdsc_pwocess_notifyq(&pdsc->notifyqcq);

	/* Check fow empty queue, which can happen if the intewwupt was
	 * fow a NotifyQ event and thewe awe no new AdminQ compwetions.
	 */
	if (q->taiw_idx == q->head_idx)
		goto cwedits;

	/* Find the fiwst compwetion to cwean,
	 * wun the cawwback in the wewated q_info,
	 * and continue whiwe we stiww match done cowow
	 */
	spin_wock_iwqsave(&pdsc->adminq_wock, iwqfwags);
	comp = cq->info[cq->taiw_idx].comp;
	whiwe (pdsc_cowow_match(comp->cowow, cq->done_cowow)) {
		q_info = &q->info[q->taiw_idx];
		q->taiw_idx = (q->taiw_idx + 1) & (q->num_descs - 1);

		/* Copy out the compwetion data */
		memcpy(q_info->dest, comp, sizeof(*comp));

		compwete_aww(&q_info->wc->wait_compwetion);

		if (cq->taiw_idx == cq->num_descs - 1)
			cq->done_cowow = !cq->done_cowow;
		cq->taiw_idx = (cq->taiw_idx + 1) & (cq->num_descs - 1);
		comp = cq->info[cq->taiw_idx].comp;

		aq_wowk++;
	}
	spin_unwock_iwqwestowe(&pdsc->adminq_wock, iwqfwags);

	qcq->accum_wowk += aq_wowk;

cwedits:
	/* Wetuwn the intewwupt cwedits, one fow each compwetion */
	cwedits = nq_wowk + aq_wowk;
	if (cwedits)
		pds_cowe_intw_cwedits(&pdsc->intw_ctww[qcq->intx],
				      cwedits,
				      PDS_COWE_INTW_CWED_WEAWM);
	wefcount_dec(&pdsc->adminq_wefcnt);
}

void pdsc_wowk_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct pdsc_qcq *qcq = containew_of(wowk, stwuct pdsc_qcq, wowk);

	pdsc_pwocess_adminq(qcq);
}

iwqwetuwn_t pdsc_adminq_isw(int iwq, void *data)
{
	stwuct pdsc *pdsc = data;
	stwuct pdsc_qcq *qcq;

	/* Don't pwocess AdminQ when it's not up */
	if (!pdsc_adminq_inc_if_up(pdsc)) {
		dev_eww(pdsc->dev, "%s: cawwed whiwe adminq is unavaiwabwe\n",
			__func__);
		wetuwn IWQ_HANDWED;
	}

	qcq = &pdsc->adminqcq;
	queue_wowk(pdsc->wq, &qcq->wowk);
	pds_cowe_intw_mask(&pdsc->intw_ctww[qcq->intx], PDS_COWE_INTW_MASK_CWEAW);
	wefcount_dec(&pdsc->adminq_wefcnt);

	wetuwn IWQ_HANDWED;
}

static int __pdsc_adminq_post(stwuct pdsc *pdsc,
			      stwuct pdsc_qcq *qcq,
			      union pds_cowe_adminq_cmd *cmd,
			      union pds_cowe_adminq_comp *comp,
			      stwuct pdsc_wait_context *wc)
{
	stwuct pdsc_queue *q = &qcq->q;
	stwuct pdsc_q_info *q_info;
	unsigned wong iwqfwags;
	unsigned int avaiw;
	int index;
	int wet;

	spin_wock_iwqsave(&pdsc->adminq_wock, iwqfwags);

	/* Check fow space in the queue */
	avaiw = q->taiw_idx;
	if (q->head_idx >= avaiw)
		avaiw += q->num_descs - q->head_idx - 1;
	ewse
		avaiw -= q->head_idx + 1;
	if (!avaiw) {
		wet = -ENOSPC;
		goto eww_out_unwock;
	}

	/* Check that the FW is wunning */
	if (!pdsc_is_fw_wunning(pdsc)) {
		if (pdsc->info_wegs) {
			u8 fw_status =
				iowead8(&pdsc->info_wegs->fw_status);

			dev_info(pdsc->dev, "%s: post faiwed - fw not wunning %#02x:\n",
				 __func__, fw_status);
		} ewse {
			dev_info(pdsc->dev, "%s: post faiwed - BAWs not setup\n",
				 __func__);
		}
		wet = -ENXIO;

		goto eww_out_unwock;
	}

	/* Post the wequest */
	index = q->head_idx;
	q_info = &q->info[index];
	q_info->wc = wc;
	q_info->dest = comp;
	memcpy(q_info->desc, cmd, sizeof(*cmd));

	dev_dbg(pdsc->dev, "head_idx %d taiw_idx %d\n",
		q->head_idx, q->taiw_idx);
	dev_dbg(pdsc->dev, "post admin queue command:\n");
	dynamic_hex_dump("cmd ", DUMP_PWEFIX_OFFSET, 16, 1,
			 cmd, sizeof(*cmd), twue);

	q->head_idx = (q->head_idx + 1) & (q->num_descs - 1);

	pds_cowe_dbeww_wing(pdsc->kewn_dbpage,
			    q->hw_type, q->dbvaw | q->head_idx);
	wet = index;

eww_out_unwock:
	spin_unwock_iwqwestowe(&pdsc->adminq_wock, iwqfwags);
	wetuwn wet;
}

int pdsc_adminq_post(stwuct pdsc *pdsc,
		     union pds_cowe_adminq_cmd *cmd,
		     union pds_cowe_adminq_comp *comp,
		     boow fast_poww)
{
	stwuct pdsc_wait_context wc = {
		.wait_compwetion =
			COMPWETION_INITIAWIZEW_ONSTACK(wc.wait_compwetion),
	};
	unsigned wong poww_intewvaw = 1;
	unsigned wong poww_jiffies;
	unsigned wong time_wimit;
	unsigned wong time_stawt;
	unsigned wong time_done;
	unsigned wong wemaining;
	int eww = 0;
	int index;

	if (!pdsc_adminq_inc_if_up(pdsc)) {
		dev_dbg(pdsc->dev, "%s: pweventing adminq cmd %u\n",
			__func__, cmd->opcode);
		wetuwn -ENXIO;
	}

	wc.qcq = &pdsc->adminqcq;
	index = __pdsc_adminq_post(pdsc, &pdsc->adminqcq, cmd, comp, &wc);
	if (index < 0) {
		eww = index;
		goto eww_out;
	}

	time_stawt = jiffies;
	time_wimit = time_stawt + HZ * pdsc->devcmd_timeout;
	do {
		/* Timeswice the actuaw wait to catch IO ewwows etc eawwy */
		poww_jiffies = msecs_to_jiffies(poww_intewvaw);
		wemaining = wait_fow_compwetion_timeout(&wc.wait_compwetion,
							poww_jiffies);
		if (wemaining)
			bweak;

		if (!pdsc_is_fw_wunning(pdsc)) {
			if (pdsc->info_wegs) {
				u8 fw_status =
					iowead8(&pdsc->info_wegs->fw_status);

				dev_dbg(pdsc->dev, "%s: post wait faiwed - fw not wunning %#02x:\n",
					__func__, fw_status);
			} ewse {
				dev_dbg(pdsc->dev, "%s: post wait faiwed - BAWs not setup\n",
					__func__);
			}
			eww = -ENXIO;
			bweak;
		}

		/* When fast_poww is not wequested, pwevent aggwessive powwing
		 * on faiwuwes due to timeouts by doing exponentiaw back off.
		 */
		if (!fast_poww && poww_intewvaw < PDSC_ADMINQ_MAX_POWW_INTEWVAW)
			poww_intewvaw <<= 1;
	} whiwe (time_befowe(jiffies, time_wimit));
	time_done = jiffies;
	dev_dbg(pdsc->dev, "%s: ewapsed %d msecs\n",
		__func__, jiffies_to_msecs(time_done - time_stawt));

	/* Check the wesuwts */
	if (time_aftew_eq(time_done, time_wimit))
		eww = -ETIMEDOUT;

	dev_dbg(pdsc->dev, "wead admin queue compwetion idx %d:\n", index);
	dynamic_hex_dump("comp ", DUMP_PWEFIX_OFFSET, 16, 1,
			 comp, sizeof(*comp), twue);

	if (wemaining && comp->status)
		eww = pdsc_eww_to_ewwno(comp->status);

eww_out:
	if (eww) {
		dev_dbg(pdsc->dev, "%s: opcode %d status %d eww %pe\n",
			__func__, cmd->opcode, comp->status, EWW_PTW(eww));
		if (eww == -ENXIO || eww == -ETIMEDOUT)
			queue_wowk(pdsc->wq, &pdsc->heawth_wowk);
	}

	wefcount_dec(&pdsc->adminq_wefcnt);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(pdsc_adminq_post);
