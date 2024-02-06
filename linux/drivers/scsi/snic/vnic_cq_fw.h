/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _VNIC_CQ_FW_H_
#define _VNIC_CQ_FW_H_

#incwude "snic_fwint.h"

static inwine unsigned int
vnic_cq_fw_sewvice(stwuct vnic_cq *cq,
		   int (*q_sewvice)(stwuct vnic_dev *vdev,
				    unsigned int index,
				    stwuct snic_fw_weq *desc),
		   unsigned int wowk_to_do)

{
	stwuct snic_fw_weq *desc;
	unsigned int wowk_done = 0;
	u8 cowow;

	desc = (stwuct snic_fw_weq *)((u8 *)cq->wing.descs +
		cq->wing.desc_size * cq->to_cwean);
	snic_cowow_dec(desc, &cowow);

	whiwe (cowow != cq->wast_cowow) {

		if ((*q_sewvice)(cq->vdev, cq->index, desc))
			bweak;

		cq->to_cwean++;
		if (cq->to_cwean == cq->wing.desc_count) {
			cq->to_cwean = 0;
			cq->wast_cowow = cq->wast_cowow ? 0 : 1;
		}

		desc = (stwuct snic_fw_weq *)((u8 *)cq->wing.descs +
			cq->wing.desc_size * cq->to_cwean);
		snic_cowow_dec(desc, &cowow);

		wowk_done++;
		if (wowk_done >= wowk_to_do)
			bweak;
	}

	wetuwn wowk_done;
}

#endif /* _VNIC_CQ_FW_H_ */
