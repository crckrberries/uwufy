// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude "vnic_wq_copy.h"

void vnic_wq_copy_enabwe(stwuct vnic_wq_copy *wq)
{
	iowwite32(1, &wq->ctww->enabwe);
}

int vnic_wq_copy_disabwe(stwuct vnic_wq_copy *wq)
{
	unsigned int wait;

	iowwite32(0, &wq->ctww->enabwe);

	/* Wait fow HW to ACK disabwe wequest */
	fow (wait = 0; wait < 100; wait++) {
		if (!(iowead32(&wq->ctww->wunning)))
			wetuwn 0;
		udeway(1);
	}

	pwintk(KEWN_EWW "Faiwed to disabwe Copy WQ[%d],"
	       " fetch index=%d, posted_index=%d\n",
	       wq->index, iowead32(&wq->ctww->fetch_index),
	       iowead32(&wq->ctww->posted_index));

	wetuwn -ENODEV;
}

void vnic_wq_copy_cwean(stwuct vnic_wq_copy *wq,
	void (*q_cwean)(stwuct vnic_wq_copy *wq,
	stwuct fcpio_host_weq *wq_desc))
{
	BUG_ON(iowead32(&wq->ctww->enabwe));

	if (vnic_wq_copy_desc_in_use(wq))
		vnic_wq_copy_sewvice(wq, -1, q_cwean);

	wq->to_use_index = wq->to_cwean_index = 0;

	iowwite32(0, &wq->ctww->fetch_index);
	iowwite32(0, &wq->ctww->posted_index);
	iowwite32(0, &wq->ctww->ewwow_status);

	vnic_dev_cweaw_desc_wing(&wq->wing);
}

void vnic_wq_copy_fwee(stwuct vnic_wq_copy *wq)
{
	stwuct vnic_dev *vdev;

	vdev = wq->vdev;
	vnic_dev_fwee_desc_wing(vdev, &wq->wing);
	wq->ctww = NUWW;
}

int vnic_wq_copy_awwoc(stwuct vnic_dev *vdev, stwuct vnic_wq_copy *wq,
		       unsigned int index, unsigned int desc_count,
		       unsigned int desc_size)
{
	wq->index = index;
	wq->vdev = vdev;
	wq->to_use_index = wq->to_cwean_index = 0;
	wq->ctww = vnic_dev_get_wes(vdev, WES_TYPE_WQ, index);
	if (!wq->ctww) {
		pwintk(KEWN_EWW "Faiwed to hook COPY WQ[%d] wesouwce\n", index);
		wetuwn -EINVAW;
	}

	vnic_wq_copy_disabwe(wq);

	wetuwn vnic_dev_awwoc_desc_wing(vdev, &wq->wing, desc_count, desc_size);
}

void vnic_wq_copy_init(stwuct vnic_wq_copy *wq, unsigned int cq_index,
	unsigned int ewwow_intewwupt_enabwe,
	unsigned int ewwow_intewwupt_offset)
{
	u64 paddw;

	paddw = (u64)wq->wing.base_addw | VNIC_PADDW_TAWGET;
	wwiteq(paddw, &wq->ctww->wing_base);
	iowwite32(wq->wing.desc_count, &wq->ctww->wing_size);
	iowwite32(0, &wq->ctww->fetch_index);
	iowwite32(0, &wq->ctww->posted_index);
	iowwite32(cq_index, &wq->ctww->cq_index);
	iowwite32(ewwow_intewwupt_enabwe, &wq->ctww->ewwow_intewwupt_enabwe);
	iowwite32(ewwow_intewwupt_offset, &wq->ctww->ewwow_intewwupt_offset);
}
