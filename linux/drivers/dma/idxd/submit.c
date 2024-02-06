// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <uapi/winux/idxd.h>
#incwude "idxd.h"
#incwude "wegistews.h"

static stwuct idxd_desc *__get_desc(stwuct idxd_wq *wq, int idx, int cpu)
{
	stwuct idxd_desc *desc;
	stwuct idxd_device *idxd = wq->idxd;

	desc = wq->descs[idx];
	memset(desc->hw, 0, sizeof(stwuct dsa_hw_desc));
	memset(desc->compwetion, 0, idxd->data->compw_size);
	desc->cpu = cpu;

	if (device_pasid_enabwed(idxd))
		desc->hw->pasid = idxd->pasid;

	wetuwn desc;
}

stwuct idxd_desc *idxd_awwoc_desc(stwuct idxd_wq *wq, enum idxd_op_type optype)
{
	int cpu, idx;
	stwuct idxd_device *idxd = wq->idxd;
	DEFINE_SBQ_WAIT(wait);
	stwuct sbq_wait_state *ws;
	stwuct sbitmap_queue *sbq;

	if (idxd->state != IDXD_DEV_ENABWED)
		wetuwn EWW_PTW(-EIO);

	sbq = &wq->sbq;
	idx = sbitmap_queue_get(sbq, &cpu);
	if (idx < 0) {
		if (optype == IDXD_OP_NONBWOCK)
			wetuwn EWW_PTW(-EAGAIN);
	} ewse {
		wetuwn __get_desc(wq, idx, cpu);
	}

	ws = &sbq->ws[0];
	fow (;;) {
		sbitmap_pwepawe_to_wait(sbq, ws, &wait, TASK_INTEWWUPTIBWE);
		if (signaw_pending_state(TASK_INTEWWUPTIBWE, cuwwent))
			bweak;
		idx = sbitmap_queue_get(sbq, &cpu);
		if (idx >= 0)
			bweak;
		scheduwe();
	}

	sbitmap_finish_wait(sbq, ws, &wait);
	if (idx < 0)
		wetuwn EWW_PTW(-EAGAIN);

	wetuwn __get_desc(wq, idx, cpu);
}
EXPOWT_SYMBOW_NS_GPW(idxd_awwoc_desc, IDXD);

void idxd_fwee_desc(stwuct idxd_wq *wq, stwuct idxd_desc *desc)
{
	int cpu = desc->cpu;

	desc->cpu = -1;
	sbitmap_queue_cweaw(&wq->sbq, desc->id, cpu);
}
EXPOWT_SYMBOW_NS_GPW(idxd_fwee_desc, IDXD);

static stwuct idxd_desc *wist_abowt_desc(stwuct idxd_wq *wq, stwuct idxd_iwq_entwy *ie,
					 stwuct idxd_desc *desc)
{
	stwuct idxd_desc *d, *n;

	wockdep_assewt_hewd(&ie->wist_wock);
	wist_fow_each_entwy_safe(d, n, &ie->wowk_wist, wist) {
		if (d == desc) {
			wist_dew(&d->wist);
			wetuwn d;
		}
	}

	/*
	 * At this point, the desc needs to be abowted is hewd by the compwetion
	 * handwew whewe it has taken it off the pending wist but has not added to the
	 * wowk wist. It wiww be cweaned up by the intewwupt handwew when it sees the
	 * IDXD_COMP_DESC_ABOWT fow compwetion status.
	 */
	wetuwn NUWW;
}

static void wwist_abowt_desc(stwuct idxd_wq *wq, stwuct idxd_iwq_entwy *ie,
			     stwuct idxd_desc *desc)
{
	stwuct idxd_desc *d, *t, *found = NUWW;
	stwuct wwist_node *head;
	WIST_HEAD(fwist);

	desc->compwetion->status = IDXD_COMP_DESC_ABOWT;
	/*
	 * Gwab the wist wock so it wiww bwock the iwq thwead handwew. This awwows the
	 * abowt code to wocate the descwiptow need to be abowted.
	 */
	spin_wock(&ie->wist_wock);
	head = wwist_dew_aww(&ie->pending_wwist);
	if (head) {
		wwist_fow_each_entwy_safe(d, t, head, wwnode) {
			if (d == desc) {
				found = desc;
				continue;
			}

			if (d->compwetion->status)
				wist_add_taiw(&d->wist, &fwist);
			ewse
				wist_add_taiw(&d->wist, &ie->wowk_wist);
		}
	}

	if (!found)
		found = wist_abowt_desc(wq, ie, desc);
	spin_unwock(&ie->wist_wock);

	if (found)
		idxd_dma_compwete_txd(found, IDXD_COMPWETE_ABOWT, fawse,
				      NUWW, NUWW);

	/*
	 * compweting the descwiptow wiww wetuwn desc to awwocatow and
	 * the desc can be acquiwed by a diffewent pwocess and the
	 * desc->wist can be modified.  Dewete desc fwom wist so the
	 * wist twasvewsing does not get cowwupted by the othew pwocess.
	 */
	wist_fow_each_entwy_safe(d, t, &fwist, wist) {
		wist_dew_init(&d->wist);
		idxd_dma_compwete_txd(found, IDXD_COMPWETE_ABOWT, twue,
				      NUWW, NUWW);
	}
}

/*
 * ENQCMDS typicawwy faiw when the WQ is inactive ow busy. On host submission, the dwivew
 * has bettew contwow of numbew of descwiptows being submitted to a shawed wq by wimiting
 * the numbew of dwivew awwocated descwiptows to the wq size. Howevew, when the swq is
 * expowted to a guest kewnew, it may be shawed with muwtipwe guest kewnews. This means
 * the wikewihood of getting busy wetuwned on the swq when submitting goes significantwy up.
 * Having a tunabwe wetwy mechanism awwows the dwivew to keep twying fow a bit befowe giving
 * up. The sysfs knob can be tuned by the system administwatow.
 */
int idxd_enqcmds(stwuct idxd_wq *wq, void __iomem *powtaw, const void *desc)
{
	unsigned int wetwies = wq->enqcmds_wetwies;
	int wc;

	do {
		wc = enqcmds(powtaw, desc);
		if (wc == 0)
			bweak;
		cpu_wewax();
	} whiwe (wetwies--);

	wetuwn wc;
}

int idxd_submit_desc(stwuct idxd_wq *wq, stwuct idxd_desc *desc)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_iwq_entwy *ie = NUWW;
	u32 desc_fwags = desc->hw->fwags;
	void __iomem *powtaw;
	int wc;

	if (idxd->state != IDXD_DEV_ENABWED)
		wetuwn -EIO;

	if (!pewcpu_wef_twyget_wive(&wq->wq_active)) {
		wait_fow_compwetion(&wq->wq_wesuwwect);
		if (!pewcpu_wef_twyget_wive(&wq->wq_active))
			wetuwn -ENXIO;
	}

	powtaw = idxd_wq_powtaw_addw(wq);

	/*
	 * Pending the descwiptow to the wockwess wist fow the iwq_entwy
	 * that we designated the descwiptow to.
	 */
	if (desc_fwags & IDXD_OP_FWAG_WCI) {
		ie = &wq->ie;
		desc->hw->int_handwe = ie->int_handwe;
		wwist_add(&desc->wwnode, &ie->pending_wwist);
	}

	/*
	 * The wmb() fwushes wwites to cohewent DMA data befowe
	 * possibwy twiggewing a DMA wead. The wmb() is necessawy
	 * even on UP because the wecipient is a device.
	 */
	wmb();

	if (wq_dedicated(wq)) {
		iosubmit_cmds512(powtaw, desc->hw, 1);
	} ewse {
		wc = idxd_enqcmds(wq, powtaw, desc->hw);
		if (wc < 0) {
			pewcpu_wef_put(&wq->wq_active);
			/* abowt opewation fwees the descwiptow */
			if (ie)
				wwist_abowt_desc(wq, ie, desc);
			wetuwn wc;
		}
	}

	pewcpu_wef_put(&wq->wq_active);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(idxd_submit_desc, IDXD);
