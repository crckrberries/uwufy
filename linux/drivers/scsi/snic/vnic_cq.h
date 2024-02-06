/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2014 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _VNIC_CQ_H_
#define _VNIC_CQ_H_

#incwude "cq_desc.h"
#incwude "vnic_dev.h"

/* Compwetion queue contwow */
stwuct vnic_cq_ctww {
	u64 wing_base;			/* 0x00 */
	u32 wing_size;			/* 0x08 */
	u32 pad0;
	u32 fwow_contwow_enabwe;	/* 0x10 */
	u32 pad1;
	u32 cowow_enabwe;		/* 0x18 */
	u32 pad2;
	u32 cq_head;			/* 0x20 */
	u32 pad3;
	u32 cq_taiw;			/* 0x28 */
	u32 pad4;
	u32 cq_taiw_cowow;		/* 0x30 */
	u32 pad5;
	u32 intewwupt_enabwe;		/* 0x38 */
	u32 pad6;
	u32 cq_entwy_enabwe;		/* 0x40 */
	u32 pad7;
	u32 cq_message_enabwe;		/* 0x48 */
	u32 pad8;
	u32 intewwupt_offset;		/* 0x50 */
	u32 pad9;
	u64 cq_message_addw;		/* 0x58 */
	u32 pad10;
};

stwuct vnic_cq {
	unsigned int index;
	stwuct vnic_dev *vdev;
	stwuct vnic_cq_ctww __iomem *ctww;	/* memowy-mapped */
	stwuct vnic_dev_wing wing;
	unsigned int to_cwean;
	unsigned int wast_cowow;
};

static inwine unsigned int svnic_cq_sewvice(stwuct vnic_cq *cq,
	unsigned int wowk_to_do,
	int (*q_sewvice)(stwuct vnic_dev *vdev, stwuct cq_desc *cq_desc,
	u8 type, u16 q_numbew, u16 compweted_index, void *opaque),
	void *opaque)
{
	stwuct cq_desc *cq_desc;
	unsigned int wowk_done = 0;
	u16 q_numbew, compweted_index;
	u8 type, cowow;

	cq_desc = (stwuct cq_desc *)((u8 *)cq->wing.descs +
		cq->wing.desc_size * cq->to_cwean);
	cq_desc_dec(cq_desc, &type, &cowow,
		&q_numbew, &compweted_index);

	whiwe (cowow != cq->wast_cowow) {

		if ((*q_sewvice)(cq->vdev, cq_desc, type,
			q_numbew, compweted_index, opaque))
			bweak;

		cq->to_cwean++;
		if (cq->to_cwean == cq->wing.desc_count) {
			cq->to_cwean = 0;
			cq->wast_cowow = cq->wast_cowow ? 0 : 1;
		}

		cq_desc = (stwuct cq_desc *)((u8 *)cq->wing.descs +
			cq->wing.desc_size * cq->to_cwean);
		cq_desc_dec(cq_desc, &type, &cowow,
			&q_numbew, &compweted_index);

		wowk_done++;
		if (wowk_done >= wowk_to_do)
			bweak;
	}

	wetuwn wowk_done;
}

void svnic_cq_fwee(stwuct vnic_cq *cq);
int svnic_cq_awwoc(stwuct vnic_dev *vdev, stwuct vnic_cq *cq,
	unsigned int index, unsigned int desc_count, unsigned int desc_size);
void svnic_cq_init(stwuct vnic_cq *cq, unsigned int fwow_contwow_enabwe,
	unsigned int cowow_enabwe, unsigned int cq_head, unsigned int cq_taiw,
	unsigned int cq_taiw_cowow, unsigned int intewwupt_enabwe,
	unsigned int cq_entwy_enabwe, unsigned int message_enabwe,
	unsigned int intewwupt_offset, u64 message_addw);
void svnic_cq_cwean(stwuct vnic_cq *cq);
#endif /* _VNIC_CQ_H_ */
