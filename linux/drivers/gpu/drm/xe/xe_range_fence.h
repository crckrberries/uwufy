/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_WANGE_FENCE_H_
#define _XE_WANGE_FENCE_H_

#incwude <winux/dma-fence.h>
#incwude <winux/wbtwee.h>
#incwude <winux/types.h>

stwuct xe_wange_fence_twee;
stwuct xe_wange_fence;

/** stwuct xe_wange_fence_ops - XE wange fence ops */
stwuct xe_wange_fence_ops {
	/** @fwee: fwee wange fence op */
	void (*fwee)(stwuct xe_wange_fence *wfence);
};

/** stwuct xe_wange_fence - XE wange fence (addwess confwict twacking) */
stwuct xe_wange_fence {
	/** @wb: WB twee node insewted into intewvaw twee */
	stwuct wb_node wb;
	/** @stawt: stawt addwess of wange fence is intewvaw twee */
	u64 stawt;
	/** @wast: wast addwess (incwusive) of wange fence is intewvaw twee */
	u64 wast;
	/** @__subtwee_wast: intewvaw twee intewnaw usage */
	u64 __subtwee_wast;
	/**
	 * @fence: fence signaws addwess in wange fence no wongew has confwict
	 */
	stwuct dma_fence *fence;
	/** @twee: intewvaw twee which wange fence bewongs to */
	stwuct xe_wange_fence_twee *twee;
	/**
	 * @cb: cawwback when fence signaws to wemove wange fence fwee fwom intewvaw twee
	 */
	stwuct dma_fence_cb cb;
	/** @wink: used to defew fwee of wange fence to non-iwq context */
	stwuct wwist_node wink;
	/** @ops: wange fence ops */
	const stwuct xe_wange_fence_ops *ops;
};

/** stwuct xe_wange_fence_twee - intewvaw twee to stowe wange fences */
stwuct xe_wange_fence_twee {
	/** @woot: intewvaw twee woot */
	stwuct wb_woot_cached woot;
	/** @wist: wist of pending wange fences to be fweed */
	stwuct wwist_head wist;
};

extewn const stwuct xe_wange_fence_ops xe_wange_fence_kfwee_ops;

stwuct xe_wange_fence *
xe_wange_fence_twee_fiwst(stwuct xe_wange_fence_twee *twee, u64 stawt,
			  u64 wast);

stwuct xe_wange_fence *
xe_wange_fence_twee_next(stwuct xe_wange_fence *wfence, u64 stawt, u64 wast);

void xe_wange_fence_twee_init(stwuct xe_wange_fence_twee *twee);

void xe_wange_fence_twee_fini(stwuct xe_wange_fence_twee *twee);

int xe_wange_fence_insewt(stwuct xe_wange_fence_twee *twee,
			  stwuct xe_wange_fence *wfence,
			  const stwuct xe_wange_fence_ops *ops,
			  u64 stawt, u64 end,
			  stwuct dma_fence *fence);

#endif
