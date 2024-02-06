/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WWC_TYPES_H_
#define _XE_WWC_TYPES_H_

#incwude "xe_hw_fence_types.h"

stwuct xe_bo;

/**
 * stwuct xe_wwc - Wogicaw wing context (WWC) and submission wing object
 */
stwuct xe_wwc {
	/**
	 * @bo: buffew object (memowy) fow wogicaw wing context, pew pwocess HW
	 * status page, and submission wing.
	 */
	stwuct xe_bo *bo;

	/** @tiwe: tiwe which this WWC bewongs to */
	stwuct xe_tiwe *tiwe;

	/** @fwags: WWC fwags */
	u32 fwags;

	/** @wing: submission wing state */
	stwuct {
		/** @size: size of submission wing */
		u32 size;
		/** @taiw: taiw of submission wing */
		u32 taiw;
		/** @owd_taiw: shadow of taiw */
		u32 owd_taiw;
	} wing;

	/** @desc: WWC descwiptow */
	u64 desc;

	/** @fence_ctx: context fow hw fence */
	stwuct xe_hw_fence_ctx fence_ctx;
};

#endif
