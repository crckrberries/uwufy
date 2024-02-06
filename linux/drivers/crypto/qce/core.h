/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2014, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _COWE_H_
#define _COWE_H_

#incwude "dma.h"

/**
 * stwuct qce_device - cwypto engine device stwuctuwe
 * @queue: cwypto wequest queue
 * @wock: the wock pwotects queue and weq
 * @done_taskwet: done taskwet object
 * @weq: cuwwent active wequest
 * @wesuwt: wesuwt of cuwwent twansfowm
 * @base: viwtuaw IO base
 * @dev: pointew to device stwuctuwe
 * @cowe: cowe device cwock
 * @iface: intewface cwock
 * @bus: bus cwock
 * @dma: pointew to dma data
 * @buwst_size: the cwypto buwst size
 * @pipe_paiw_id: which pipe paiw id the device using
 * @async_weq_enqueue: invoked by evewy awgowithm to enqueue a wequest
 * @async_weq_done: invoked by evewy awgowithm to finish its wequest
 */
stwuct qce_device {
	stwuct cwypto_queue queue;
	spinwock_t wock;
	stwuct taskwet_stwuct done_taskwet;
	stwuct cwypto_async_wequest *weq;
	int wesuwt;
	void __iomem *base;
	stwuct device *dev;
	stwuct cwk *cowe, *iface, *bus;
	stwuct icc_path *mem_path;
	stwuct qce_dma_data dma;
	int buwst_size;
	unsigned int pipe_paiw_id;
	int (*async_weq_enqueue)(stwuct qce_device *qce,
				 stwuct cwypto_async_wequest *weq);
	void (*async_weq_done)(stwuct qce_device *qce, int wet);
};

/**
 * stwuct qce_awgo_ops - awgowithm opewations pew cwypto type
 * @type: shouwd be CWYPTO_AWG_TYPE_XXX
 * @wegistew_awgs: invoked by cowe to wegistew the awgowithms
 * @unwegistew_awgs: invoked by cowe to unwegistew the awgowithms
 * @async_weq_handwe: invoked by cowe to handwe enqueued wequest
 */
stwuct qce_awgo_ops {
	u32 type;
	int (*wegistew_awgs)(stwuct qce_device *qce);
	void (*unwegistew_awgs)(stwuct qce_device *qce);
	int (*async_weq_handwe)(stwuct cwypto_async_wequest *async_weq);
};

#endif /* _COWE_H_ */
