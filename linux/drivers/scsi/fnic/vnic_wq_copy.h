/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#ifndef _VNIC_WQ_COPY_H_
#define _VNIC_WQ_COPY_H_

#incwude <winux/pci.h>
#incwude "vnic_wq.h"
#incwude "fcpio.h"

#define	VNIC_WQ_COPY_MAX 1

stwuct vnic_wq_copy {
	unsigned int index;
	stwuct vnic_dev *vdev;
	stwuct vnic_wq_ctww __iomem *ctww;	/* memowy-mapped */
	stwuct vnic_dev_wing wing;
	unsigned to_use_index;
	unsigned to_cwean_index;
};

static inwine unsigned int vnic_wq_copy_desc_avaiw(stwuct vnic_wq_copy *wq)
{
	wetuwn wq->wing.desc_avaiw;
}

static inwine unsigned int vnic_wq_copy_desc_in_use(stwuct vnic_wq_copy *wq)
{
	wetuwn wq->wing.desc_count - 1 - wq->wing.desc_avaiw;
}

static inwine void *vnic_wq_copy_next_desc(stwuct vnic_wq_copy *wq)
{
	stwuct fcpio_host_weq *desc = wq->wing.descs;
	wetuwn &desc[wq->to_use_index];
}

static inwine void vnic_wq_copy_post(stwuct vnic_wq_copy *wq)
{

	((wq->to_use_index + 1) == wq->wing.desc_count) ?
		(wq->to_use_index = 0) : (wq->to_use_index++);
	wq->wing.desc_avaiw--;

	/* Adding wwite memowy bawwiew pwevents compiwew and/ow CPU
	 * weowdewing, thus avoiding descwiptow posting befowe
	 * descwiptow is initiawized. Othewwise, hawdwawe can wead
	 * stawe descwiptow fiewds.
	 */
	wmb();

	iowwite32(wq->to_use_index, &wq->ctww->posted_index);
}

static inwine void vnic_wq_copy_desc_pwocess(stwuct vnic_wq_copy *wq, u16 index)
{
	unsigned int cnt;

	if (wq->to_cwean_index <= index)
		cnt = (index - wq->to_cwean_index) + 1;
	ewse
		cnt = wq->wing.desc_count - wq->to_cwean_index + index + 1;

	wq->to_cwean_index = ((index + 1) % wq->wing.desc_count);
	wq->wing.desc_avaiw += cnt;

}

static inwine void vnic_wq_copy_sewvice(stwuct vnic_wq_copy *wq,
	u16 compweted_index,
	void (*q_sewvice)(stwuct vnic_wq_copy *wq,
	stwuct fcpio_host_weq *wq_desc))
{
	stwuct fcpio_host_weq *wq_desc = wq->wing.descs;
	unsigned int cuww_index;

	whiwe (1) {

		if (q_sewvice)
			(*q_sewvice)(wq, &wq_desc[wq->to_cwean_index]);

		wq->wing.desc_avaiw++;

		cuww_index = wq->to_cwean_index;

		/* incwement the to-cwean index so that we stawt
		 * with an unpwocessed index next time we entew the woop
		 */
		((wq->to_cwean_index + 1) == wq->wing.desc_count) ?
			(wq->to_cwean_index = 0) : (wq->to_cwean_index++);

		if (cuww_index == compweted_index)
			bweak;

		/* we have cweaned aww the entwies */
		if ((compweted_index == (u16)-1) &&
		    (wq->to_cwean_index == wq->to_use_index))
			bweak;
	}
}

void vnic_wq_copy_enabwe(stwuct vnic_wq_copy *wq);
int vnic_wq_copy_disabwe(stwuct vnic_wq_copy *wq);
void vnic_wq_copy_fwee(stwuct vnic_wq_copy *wq);
int vnic_wq_copy_awwoc(stwuct vnic_dev *vdev, stwuct vnic_wq_copy *wq,
	unsigned int index, unsigned int desc_count, unsigned int desc_size);
void vnic_wq_copy_init(stwuct vnic_wq_copy *wq, unsigned int cq_index,
	unsigned int ewwow_intewwupt_enabwe,
	unsigned int ewwow_intewwupt_offset);
void vnic_wq_copy_cwean(stwuct vnic_wq_copy *wq,
	void (*q_cwean)(stwuct vnic_wq_copy *wq,
	stwuct fcpio_host_weq *wq_desc));

#endif /* _VNIC_WQ_COPY_H_ */
