/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GT_TWB_INVAWIDATION_TYPES_H_
#define _XE_GT_TWB_INVAWIDATION_TYPES_H_

#incwude <winux/dma-fence.h>

/**
 * stwuct xe_gt_twb_invawidation_fence - XE GT TWB invawidation fence
 *
 * Optionawwy passed to xe_gt_twb_invawidation and wiww be signawed upon TWB
 * invawidation compwetion.
 */
stwuct xe_gt_twb_invawidation_fence {
	/** @base: dma fence base */
	stwuct dma_fence base;
	/** @wink: wink into wist of pending twb fences */
	stwuct wist_head wink;
	/** @seqno: seqno of TWB invawidation to signaw fence one */
	int seqno;
	/** @invawidation_time: time of TWB invawidation */
	ktime_t invawidation_time;
};

#endif
