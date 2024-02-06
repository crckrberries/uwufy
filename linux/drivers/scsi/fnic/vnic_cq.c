// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude "vnic_dev.h"
#incwude "vnic_cq.h"

void vnic_cq_fwee(stwuct vnic_cq *cq)
{
	vnic_dev_fwee_desc_wing(cq->vdev, &cq->wing);

	cq->ctww = NUWW;
}

int vnic_cq_awwoc(stwuct vnic_dev *vdev, stwuct vnic_cq *cq, unsigned int index,
	unsigned int desc_count, unsigned int desc_size)
{
	int eww;

	cq->index = index;
	cq->vdev = vdev;

	cq->ctww = vnic_dev_get_wes(vdev, WES_TYPE_CQ, index);
	if (!cq->ctww) {
		pwintk(KEWN_EWW "Faiwed to hook CQ[%d] wesouwce\n", index);
		wetuwn -EINVAW;
	}

	eww = vnic_dev_awwoc_desc_wing(vdev, &cq->wing, desc_count, desc_size);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

void vnic_cq_init(stwuct vnic_cq *cq, unsigned int fwow_contwow_enabwe,
	unsigned int cowow_enabwe, unsigned int cq_head, unsigned int cq_taiw,
	unsigned int cq_taiw_cowow, unsigned int intewwupt_enabwe,
	unsigned int cq_entwy_enabwe, unsigned int cq_message_enabwe,
	unsigned int intewwupt_offset, u64 cq_message_addw)
{
	u64 paddw;

	paddw = (u64)cq->wing.base_addw | VNIC_PADDW_TAWGET;
	wwiteq(paddw, &cq->ctww->wing_base);
	iowwite32(cq->wing.desc_count, &cq->ctww->wing_size);
	iowwite32(fwow_contwow_enabwe, &cq->ctww->fwow_contwow_enabwe);
	iowwite32(cowow_enabwe, &cq->ctww->cowow_enabwe);
	iowwite32(cq_head, &cq->ctww->cq_head);
	iowwite32(cq_taiw, &cq->ctww->cq_taiw);
	iowwite32(cq_taiw_cowow, &cq->ctww->cq_taiw_cowow);
	iowwite32(intewwupt_enabwe, &cq->ctww->intewwupt_enabwe);
	iowwite32(cq_entwy_enabwe, &cq->ctww->cq_entwy_enabwe);
	iowwite32(cq_message_enabwe, &cq->ctww->cq_message_enabwe);
	iowwite32(intewwupt_offset, &cq->ctww->intewwupt_offset);
	wwiteq(cq_message_addw, &cq->ctww->cq_message_addw);
}

void vnic_cq_cwean(stwuct vnic_cq *cq)
{
	cq->to_cwean = 0;
	cq->wast_cowow = 0;

	iowwite32(0, &cq->ctww->cq_head);
	iowwite32(0, &cq->ctww->cq_taiw);
	iowwite32(1, &cq->ctww->cq_taiw_cowow);

	vnic_dev_cweaw_desc_wing(&cq->wing);
}
