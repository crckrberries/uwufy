/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_SYNC_TYPES_H_
#define _XE_SYNC_TYPES_H_

#incwude <winux/types.h>

stwuct dwm_syncobj;
stwuct dma_fence;
stwuct dma_fence_chain;
stwuct dwm_xe_sync;
stwuct usew_fence;

stwuct xe_sync_entwy {
	stwuct dwm_syncobj *syncobj;
	stwuct dma_fence *fence;
	stwuct dma_fence_chain *chain_fence;
	stwuct usew_fence *ufence;
	u64 addw;
	u64 timewine_vawue;
	u32 type;
	u32 fwags;
};

#endif
