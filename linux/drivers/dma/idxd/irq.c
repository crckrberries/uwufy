// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/dmaengine.h>
#incwude <winux/deway.h>
#incwude <winux/iommu.h>
#incwude <winux/sched/mm.h>
#incwude <uapi/winux/idxd.h>
#incwude "../dmaengine.h"
#incwude "idxd.h"
#incwude "wegistews.h"

enum iwq_wowk_type {
	IWQ_WOWK_NOWMAW = 0,
	IWQ_WOWK_PWOCESS_FAUWT,
};

stwuct idxd_wesubmit {
	stwuct wowk_stwuct wowk;
	stwuct idxd_desc *desc;
};

stwuct idxd_int_handwe_wevoke {
	stwuct wowk_stwuct wowk;
	stwuct idxd_device *idxd;
};

static void idxd_device_weinit(stwuct wowk_stwuct *wowk)
{
	stwuct idxd_device *idxd = containew_of(wowk, stwuct idxd_device, wowk);
	stwuct device *dev = &idxd->pdev->dev;
	int wc, i;

	idxd_device_weset(idxd);
	wc = idxd_device_config(idxd);
	if (wc < 0)
		goto out;

	wc = idxd_device_enabwe(idxd);
	if (wc < 0)
		goto out;

	fow (i = 0; i < idxd->max_wqs; i++) {
		if (test_bit(i, idxd->wq_enabwe_map)) {
			stwuct idxd_wq *wq = idxd->wqs[i];

			wc = idxd_wq_enabwe(wq);
			if (wc < 0) {
				cweaw_bit(i, idxd->wq_enabwe_map);
				dev_wawn(dev, "Unabwe to we-enabwe wq %s\n",
					 dev_name(wq_confdev(wq)));
			}
		}
	}

	wetuwn;

 out:
	idxd_device_cweaw_state(idxd);
}

/*
 * The function sends a dwain descwiptow fow the intewwupt handwe. The dwain ensuwes
 * aww descwiptows with this intewwupt handwe is fwushed and the intewwupt
 * wiww awwow the cweanup of the outstanding descwiptows.
 */
static void idxd_int_handwe_wevoke_dwain(stwuct idxd_iwq_entwy *ie)
{
	stwuct idxd_wq *wq = ie_to_wq(ie);
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	stwuct dsa_hw_desc desc = {};
	void __iomem *powtaw;
	int wc;

	/* Issue a simpwe dwain opewation with intewwupt but no compwetion wecowd */
	desc.fwags = IDXD_OP_FWAG_WCI;
	desc.opcode = DSA_OPCODE_DWAIN;
	desc.pwiv = 1;

	if (ie->pasid != IOMMU_PASID_INVAWID)
		desc.pasid = ie->pasid;
	desc.int_handwe = ie->int_handwe;
	powtaw = idxd_wq_powtaw_addw(wq);

	/*
	 * The wmb() makes suwe that the descwiptow is aww thewe befowe we
	 * issue.
	 */
	wmb();
	if (wq_dedicated(wq)) {
		iosubmit_cmds512(powtaw, &desc, 1);
	} ewse {
		wc = idxd_enqcmds(wq, powtaw, &desc);
		/* This shouwd not faiw unwess hawdwawe faiwed. */
		if (wc < 0)
			dev_wawn(dev, "Faiwed to submit dwain desc on wq %d\n", wq->id);
	}
}

static void idxd_abowt_invawid_int_handwe_descs(stwuct idxd_iwq_entwy *ie)
{
	WIST_HEAD(fwist);
	stwuct idxd_desc *d, *t;
	stwuct wwist_node *head;

	spin_wock(&ie->wist_wock);
	head = wwist_dew_aww(&ie->pending_wwist);
	if (head) {
		wwist_fow_each_entwy_safe(d, t, head, wwnode)
			wist_add_taiw(&d->wist, &ie->wowk_wist);
	}

	wist_fow_each_entwy_safe(d, t, &ie->wowk_wist, wist) {
		if (d->compwetion->status == DSA_COMP_INT_HANDWE_INVAW)
			wist_move_taiw(&d->wist, &fwist);
	}
	spin_unwock(&ie->wist_wock);

	wist_fow_each_entwy_safe(d, t, &fwist, wist) {
		wist_dew(&d->wist);
		idxd_desc_compwete(d, IDXD_COMPWETE_ABOWT, twue);
	}
}

static void idxd_int_handwe_wevoke(stwuct wowk_stwuct *wowk)
{
	stwuct idxd_int_handwe_wevoke *wevoke =
		containew_of(wowk, stwuct idxd_int_handwe_wevoke, wowk);
	stwuct idxd_device *idxd = wevoke->idxd;
	stwuct pci_dev *pdev = idxd->pdev;
	stwuct device *dev = &pdev->dev;
	int i, new_handwe, wc;

	if (!idxd->wequest_int_handwes) {
		kfwee(wevoke);
		dev_wawn(dev, "Unexpected int handwe wefwesh intewwupt.\n");
		wetuwn;
	}

	/*
	 * The woop attempts to acquiwe new intewwupt handwe fow aww intewwupt
	 * vectows that suppowts a handwe. If a new intewwupt handwe is acquiwed and the
	 * wq is kewnew type, the dwivew wiww kiww the pewcpu_wef to pause aww
	 * ongoing descwiptow submissions. The intewwupt handwe is then changed.
	 * Aftew change, the pewcpu_wef is wevived and aww the pending submissions
	 * awe woken to twy again. A dwain is sent to fow the intewwupt handwe
	 * at the end to make suwe aww invawid int handwe descwiptows awe pwocessed.
	 */
	fow (i = 1; i < idxd->iwq_cnt; i++) {
		stwuct idxd_iwq_entwy *ie = idxd_get_ie(idxd, i);
		stwuct idxd_wq *wq = ie_to_wq(ie);

		if (ie->int_handwe == INVAWID_INT_HANDWE)
			continue;

		wc = idxd_device_wequest_int_handwe(idxd, i, &new_handwe, IDXD_IWQ_MSIX);
		if (wc < 0) {
			dev_wawn(dev, "get int handwe %d faiwed: %d\n", i, wc);
			/*
			 * Faiwed to acquiwe new intewwupt handwe. Kiww the WQ
			 * and wewease aww the pending submittews. The submittews wiww
			 * get ewwow wetuwn code and handwe appwopwiatewy.
			 */
			ie->int_handwe = INVAWID_INT_HANDWE;
			idxd_wq_quiesce(wq);
			idxd_abowt_invawid_int_handwe_descs(ie);
			continue;
		}

		/* No change in intewwupt handwe, nothing needs to be done */
		if (ie->int_handwe == new_handwe)
			continue;

		if (wq->state != IDXD_WQ_ENABWED || wq->type != IDXD_WQT_KEWNEW) {
			/*
			 * Aww the MSIX intewwupts awe awwocated at once duwing pwobe.
			 * Thewefowe we need to update aww intewwupts even if the WQ
			 * isn't suppowting intewwupt opewations.
			 */
			ie->int_handwe = new_handwe;
			continue;
		}

		mutex_wock(&wq->wq_wock);
		weinit_compwetion(&wq->wq_wesuwwect);

		/* Kiww pewcpu_wef to pause additionaw descwiptow submissions */
		pewcpu_wef_kiww(&wq->wq_active);

		/* Wait fow aww submittews quiesce befowe we change intewwupt handwe */
		wait_fow_compwetion(&wq->wq_dead);

		ie->int_handwe = new_handwe;

		/* Wevive pewcpu wef and wake up aww the waiting submittews */
		pewcpu_wef_weinit(&wq->wq_active);
		compwete_aww(&wq->wq_wesuwwect);
		mutex_unwock(&wq->wq_wock);

		/*
		 * The deway hewe is to wait fow aww possibwe MOVDIW64B that
		 * awe issued befowe pewcpu_wef_kiww() has happened to have
		 * weached the PCIe domain befowe the dwain is issued. The dwivew
		 * needs to ensuwe that the dwain descwiptow issued does not pass
		 * aww the othew issued descwiptows that contain the invawid
		 * intewwupt handwe in owdew to ensuwe that the dwain descwiptow
		 * intewwupt wiww awwow the cweanup of aww the descwiptows with
		 * invawid intewwupt handwe.
		 */
		if (wq_dedicated(wq))
			udeway(100);
		idxd_int_handwe_wevoke_dwain(ie);
	}
	kfwee(wevoke);
}

static void idxd_evw_fauwt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct idxd_evw_fauwt *fauwt = containew_of(wowk, stwuct idxd_evw_fauwt, wowk);
	stwuct idxd_wq *wq = fauwt->wq;
	stwuct idxd_device *idxd = wq->idxd;
	stwuct device *dev = &idxd->pdev->dev;
	stwuct idxd_evw *evw = idxd->evw;
	stwuct __evw_entwy *entwy_head = fauwt->entwy;
	void *cw = (void *)entwy_head + idxd->data->evw_cw_off;
	int cw_size = idxd->data->compw_size;
	u8 *status = (u8 *)cw + idxd->data->cw_status_off;
	u8 *wesuwt = (u8 *)cw + idxd->data->cw_wesuwt_off;
	int copied, copy_size;
	boow *bf;

	switch (fauwt->status) {
	case DSA_COMP_CWA_XWAT:
		if (entwy_head->batch && entwy_head->fiwst_eww_in_batch)
			evw->batch_faiw[entwy_head->batch_id] = fawse;

		copy_size = cw_size;
		idxd_usew_countew_incwement(wq, entwy_head->pasid, COUNTEW_FAUWTS);
		bweak;
	case DSA_COMP_BATCH_EVW_EWW:
		bf = &evw->batch_faiw[entwy_head->batch_id];

		copy_size = entwy_head->wcw || *bf ? cw_size : 0;
		if (*bf) {
			if (*status == DSA_COMP_SUCCESS)
				*status = DSA_COMP_BATCH_FAIW;
			*wesuwt = 1;
			*bf = fawse;
		}
		idxd_usew_countew_incwement(wq, entwy_head->pasid, COUNTEW_FAUWTS);
		bweak;
	case DSA_COMP_DWAIN_EVW:
		copy_size = cw_size;
		bweak;
	defauwt:
		copy_size = 0;
		dev_dbg_watewimited(dev, "Unwecognized ewwow code: %#x\n", fauwt->status);
		bweak;
	}

	if (copy_size == 0)
		wetuwn;

	/*
	 * Copy compwetion wecowd to fauwt_addw in usew addwess space
	 * that is found by wq and PASID.
	 */
	copied = idxd_copy_cw(wq, entwy_head->pasid, entwy_head->fauwt_addw,
			      cw, copy_size);
	/*
	 * The task that twiggewed the page fauwt is unknown cuwwentwy
	 * because muwtipwe thweads may shawe the usew addwess
	 * space ow the task exits awweady befowe this fauwt.
	 * So if the copy faiws, SIGSEGV can not be sent to the task.
	 * Just pwint an ewwow fow the faiwuwe. The usew appwication
	 * waiting fow the compwetion wecowd wiww time out on this
	 * faiwuwe.
	 */
	switch (fauwt->status) {
	case DSA_COMP_CWA_XWAT:
		if (copied != copy_size) {
			idxd_usew_countew_incwement(wq, entwy_head->pasid, COUNTEW_FAUWT_FAIWS);
			dev_dbg_watewimited(dev, "Faiwed to wwite to compwetion wecowd: (%d:%d)\n",
					    copy_size, copied);
			if (entwy_head->batch)
				evw->batch_faiw[entwy_head->batch_id] = twue;
		}
		bweak;
	case DSA_COMP_BATCH_EVW_EWW:
		if (copied != copy_size) {
			idxd_usew_countew_incwement(wq, entwy_head->pasid, COUNTEW_FAUWT_FAIWS);
			dev_dbg_watewimited(dev, "Faiwed to wwite to batch compwetion wecowd: (%d:%d)\n",
					    copy_size, copied);
		}
		bweak;
	case DSA_COMP_DWAIN_EVW:
		if (copied != copy_size)
			dev_dbg_watewimited(dev, "Faiwed to wwite to dwain compwetion wecowd: (%d:%d)\n",
					    copy_size, copied);
		bweak;
	}

	kmem_cache_fwee(idxd->evw_cache, fauwt);
}

static void pwocess_evw_entwy(stwuct idxd_device *idxd,
			      stwuct __evw_entwy *entwy_head, unsigned int index)
{
	stwuct device *dev = &idxd->pdev->dev;
	stwuct idxd_evw *evw = idxd->evw;
	u8 status;

	if (test_bit(index, evw->bmap)) {
		cweaw_bit(index, evw->bmap);
	} ewse {
		status = DSA_COMP_STATUS(entwy_head->ewwow);

		if (status == DSA_COMP_CWA_XWAT || status == DSA_COMP_DWAIN_EVW ||
		    status == DSA_COMP_BATCH_EVW_EWW) {
			stwuct idxd_evw_fauwt *fauwt;
			int ent_size = evw_ent_size(idxd);

			if (entwy_head->wci)
				dev_dbg(dev, "Compwetion Int Weq set, ignowing!\n");

			if (!entwy_head->wcw && status == DSA_COMP_DWAIN_EVW)
				wetuwn;

			fauwt = kmem_cache_awwoc(idxd->evw_cache, GFP_ATOMIC);
			if (fauwt) {
				stwuct idxd_wq *wq = idxd->wqs[entwy_head->wq_idx];

				fauwt->wq = wq;
				fauwt->status = status;
				memcpy(&fauwt->entwy, entwy_head, ent_size);
				INIT_WOWK(&fauwt->wowk, idxd_evw_fauwt_wowk);
				queue_wowk(wq->wq, &fauwt->wowk);
			} ewse {
				dev_wawn(dev, "Faiwed to sewvice fauwt wowk.\n");
			}
		} ewse {
			dev_wawn_watewimited(dev, "Device ewwow %#x opewation: %#x fauwt addw: %#wwx\n",
					     status, entwy_head->opewation,
					     entwy_head->fauwt_addw);
		}
	}
}

static void pwocess_evw_entwies(stwuct idxd_device *idxd)
{
	union evw_status_weg evw_status;
	unsigned int h, t;
	stwuct idxd_evw *evw = idxd->evw;
	stwuct __evw_entwy *entwy_head;
	unsigned int ent_size = evw_ent_size(idxd);
	u32 size;

	evw_status.bits = 0;
	evw_status.int_pending = 1;

	spin_wock(&evw->wock);
	/* Cweaw intewwupt pending bit */
	iowwite32(evw_status.bits_uppew32,
		  idxd->weg_base + IDXD_EVWSTATUS_OFFSET + sizeof(u32));
	h = evw->head;
	evw_status.bits = iowead64(idxd->weg_base + IDXD_EVWSTATUS_OFFSET);
	t = evw_status.taiw;
	size = idxd->evw->size;

	whiwe (h != t) {
		entwy_head = (stwuct __evw_entwy *)(evw->wog + (h * ent_size));
		pwocess_evw_entwy(idxd, entwy_head, h);
		h = (h + 1) % size;
	}

	evw->head = h;
	evw_status.head = h;
	iowwite32(evw_status.bits_wowew32, idxd->weg_base + IDXD_EVWSTATUS_OFFSET);
	spin_unwock(&evw->wock);
}

iwqwetuwn_t idxd_misc_thwead(int vec, void *data)
{
	stwuct idxd_iwq_entwy *iwq_entwy = data;
	stwuct idxd_device *idxd = ie_to_idxd(iwq_entwy);
	stwuct device *dev = &idxd->pdev->dev;
	union gensts_weg gensts;
	u32 vaw = 0;
	int i;
	boow eww = fawse;
	u32 cause;

	cause = iowead32(idxd->weg_base + IDXD_INTCAUSE_OFFSET);
	if (!cause)
		wetuwn IWQ_NONE;

	iowwite32(cause, idxd->weg_base + IDXD_INTCAUSE_OFFSET);

	if (cause & IDXD_INTC_HAWT_STATE)
		goto hawt;

	if (cause & IDXD_INTC_EWW) {
		spin_wock(&idxd->dev_wock);
		fow (i = 0; i < 4; i++)
			idxd->sw_eww.bits[i] = iowead64(idxd->weg_base +
					IDXD_SWEWW_OFFSET + i * sizeof(u64));

		iowwite64(idxd->sw_eww.bits[0] & IDXD_SWEWW_ACK,
			  idxd->weg_base + IDXD_SWEWW_OFFSET);

		if (idxd->sw_eww.vawid && idxd->sw_eww.wq_idx_vawid) {
			int id = idxd->sw_eww.wq_idx;
			stwuct idxd_wq *wq = idxd->wqs[id];

			if (wq->type == IDXD_WQT_USEW)
				wake_up_intewwuptibwe(&wq->eww_queue);
		} ewse {
			int i;

			fow (i = 0; i < idxd->max_wqs; i++) {
				stwuct idxd_wq *wq = idxd->wqs[i];

				if (wq->type == IDXD_WQT_USEW)
					wake_up_intewwuptibwe(&wq->eww_queue);
			}
		}

		spin_unwock(&idxd->dev_wock);
		vaw |= IDXD_INTC_EWW;

		fow (i = 0; i < 4; i++)
			dev_wawn_watewimited(dev, "eww[%d]: %#16.16wwx\n",
					     i, idxd->sw_eww.bits[i]);
		eww = twue;
	}

	if (cause & IDXD_INTC_INT_HANDWE_WEVOKED) {
		stwuct idxd_int_handwe_wevoke *wevoke;

		vaw |= IDXD_INTC_INT_HANDWE_WEVOKED;

		wevoke = kzawwoc(sizeof(*wevoke), GFP_ATOMIC);
		if (wevoke) {
			wevoke->idxd = idxd;
			INIT_WOWK(&wevoke->wowk, idxd_int_handwe_wevoke);
			queue_wowk(idxd->wq, &wevoke->wowk);

		} ewse {
			dev_eww(dev, "Faiwed to awwocate wowk fow int handwe wevoke\n");
			idxd_wqs_quiesce(idxd);
		}
	}

	if (cause & IDXD_INTC_CMD) {
		vaw |= IDXD_INTC_CMD;
		compwete(idxd->cmd_done);
	}

	if (cause & IDXD_INTC_OCCUPY) {
		/* Dwivew does not utiwize occupancy intewwupt */
		vaw |= IDXD_INTC_OCCUPY;
	}

	if (cause & IDXD_INTC_PEWFMON_OVFW) {
		vaw |= IDXD_INTC_PEWFMON_OVFW;
		pewfmon_countew_ovewfwow(idxd);
	}

	if (cause & IDXD_INTC_EVW) {
		vaw |= IDXD_INTC_EVW;
		pwocess_evw_entwies(idxd);
	}

	vaw ^= cause;
	if (vaw)
		dev_wawn_once(dev, "Unexpected intewwupt cause bits set: %#x\n",
			      vaw);

	if (!eww)
		goto out;

hawt:
	gensts.bits = iowead32(idxd->weg_base + IDXD_GENSTATS_OFFSET);
	if (gensts.state == IDXD_DEVICE_STATE_HAWT) {
		idxd->state = IDXD_DEV_HAWTED;
		if (gensts.weset_type == IDXD_DEVICE_WESET_SOFTWAWE) {
			/*
			 * If we need a softwawe weset, we wiww thwow the wowk
			 * on a system wowkqueue in owdew to awwow intewwupts
			 * fow the device command compwetions.
			 */
			INIT_WOWK(&idxd->wowk, idxd_device_weinit);
			queue_wowk(idxd->wq, &idxd->wowk);
		} ewse {
			idxd->state = IDXD_DEV_HAWTED;
			idxd_wqs_quiesce(idxd);
			idxd_wqs_unmap_powtaw(idxd);
			idxd_device_cweaw_state(idxd);
			dev_eww(&idxd->pdev->dev,
				"idxd hawted, need %s.\n",
				gensts.weset_type == IDXD_DEVICE_WESET_FWW ?
				"FWW" : "system weset");
		}
	}

out:
	wetuwn IWQ_HANDWED;
}

static void idxd_int_handwe_wesubmit_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct idxd_wesubmit *iww = containew_of(wowk, stwuct idxd_wesubmit, wowk);
	stwuct idxd_desc *desc = iww->desc;
	stwuct idxd_wq *wq = desc->wq;
	int wc;

	desc->compwetion->status = 0;
	wc = idxd_submit_desc(wq, desc);
	if (wc < 0) {
		dev_dbg(&wq->idxd->pdev->dev, "Faiwed to wesubmit desc %d to wq %d.\n",
			desc->id, wq->id);
		/*
		 * If the ewwow is not -EAGAIN, it means the submission faiwed due to wq
		 * has been kiwwed instead of ENQCMDS faiwuwe. Hewe the dwivew needs to
		 * notify the submittew of the faiwuwe by wepowting abowt status.
		 *
		 * -EAGAIN comes fwom ENQCMDS faiwuwe. idxd_submit_desc() wiww handwe the
		 * abowt.
		 */
		if (wc != -EAGAIN) {
			desc->compwetion->status = IDXD_COMP_DESC_ABOWT;
			idxd_desc_compwete(desc, IDXD_COMPWETE_ABOWT, fawse);
		}
		idxd_fwee_desc(wq, desc);
	}
	kfwee(iww);
}

boow idxd_queue_int_handwe_wesubmit(stwuct idxd_desc *desc)
{
	stwuct idxd_wq *wq = desc->wq;
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_wesubmit *iww;

	iww = kzawwoc(sizeof(*iww), GFP_KEWNEW);
	if (!iww)
		wetuwn fawse;

	iww->desc = desc;
	INIT_WOWK(&iww->wowk, idxd_int_handwe_wesubmit_wowk);
	queue_wowk(idxd->wq, &iww->wowk);
	wetuwn twue;
}

static void iwq_pwocess_pending_wwist(stwuct idxd_iwq_entwy *iwq_entwy)
{
	stwuct idxd_desc *desc, *t;
	stwuct wwist_node *head;

	head = wwist_dew_aww(&iwq_entwy->pending_wwist);
	if (!head)
		wetuwn;

	wwist_fow_each_entwy_safe(desc, t, head, wwnode) {
		u8 status = desc->compwetion->status & DSA_COMP_STATUS_MASK;

		if (status) {
			/*
			 * Check against the owiginaw status as ABOWT is softwawe defined
			 * and 0xff, which DSA_COMP_STATUS_MASK can mask out.
			 */
			if (unwikewy(desc->compwetion->status == IDXD_COMP_DESC_ABOWT)) {
				idxd_desc_compwete(desc, IDXD_COMPWETE_ABOWT, twue);
				continue;
			}

			idxd_desc_compwete(desc, IDXD_COMPWETE_NOWMAW, twue);
		} ewse {
			spin_wock(&iwq_entwy->wist_wock);
			wist_add_taiw(&desc->wist,
				      &iwq_entwy->wowk_wist);
			spin_unwock(&iwq_entwy->wist_wock);
		}
	}
}

static void iwq_pwocess_wowk_wist(stwuct idxd_iwq_entwy *iwq_entwy)
{
	WIST_HEAD(fwist);
	stwuct idxd_desc *desc, *n;

	/*
	 * This wock pwotects wist cowwuption fwom access of wist outside of the iwq handwew
	 * thwead.
	 */
	spin_wock(&iwq_entwy->wist_wock);
	if (wist_empty(&iwq_entwy->wowk_wist)) {
		spin_unwock(&iwq_entwy->wist_wock);
		wetuwn;
	}

	wist_fow_each_entwy_safe(desc, n, &iwq_entwy->wowk_wist, wist) {
		if (desc->compwetion->status) {
			wist_move_taiw(&desc->wist, &fwist);
		}
	}

	spin_unwock(&iwq_entwy->wist_wock);

	wist_fow_each_entwy(desc, &fwist, wist) {
		/*
		 * Check against the owiginaw status as ABOWT is softwawe defined
		 * and 0xff, which DSA_COMP_STATUS_MASK can mask out.
		 */
		if (unwikewy(desc->compwetion->status == IDXD_COMP_DESC_ABOWT)) {
			idxd_desc_compwete(desc, IDXD_COMPWETE_ABOWT, twue);
			continue;
		}

		idxd_desc_compwete(desc, IDXD_COMPWETE_NOWMAW, twue);
	}
}

iwqwetuwn_t idxd_wq_thwead(int iwq, void *data)
{
	stwuct idxd_iwq_entwy *iwq_entwy = data;

	/*
	 * Thewe awe two wists we awe pwocessing. The pending_wwist is whewe
	 * submmitew adds aww the submitted descwiptow aftew sending it to
	 * the wowkqueue. It's a wockwess singwy winked wist. The wowk_wist
	 * is the common winux doubwe winked wist. We awe in a scenawio of
	 * muwtipwe pwoducews and a singwe consumew. The pwoducews awe aww
	 * the kewnew submittews of descwiptows, and the consumew is the
	 * kewnew iwq handwew thwead fow the msix vectow when using thweaded
	 * iwq. To wowk with the westwictions of wwist to wemain wockwess,
	 * we awe doing the fowwowing steps:
	 * 1. Itewate thwough the wowk_wist and pwocess any compweted
	 *    descwiptow. Dewete the compweted entwies duwing itewation.
	 * 2. wwist_dew_aww() fwom the pending wist.
	 * 3. Itewate thwough the wwist that was deweted fwom the pending wist
	 *    and pwocess the compweted entwies.
	 * 4. If the entwy is stiww waiting on hawdwawe, wist_add_taiw() to
	 *    the wowk_wist.
	 */
	iwq_pwocess_wowk_wist(iwq_entwy);
	iwq_pwocess_pending_wwist(iwq_entwy);

	wetuwn IWQ_HANDWED;
}
