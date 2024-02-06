/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NV10_FENCE_H_
#define __NV10_FENCE_H_

#incwude "nouveau_fence.h"
#incwude "nouveau_bo.h"

stwuct nv10_fence_chan {
	stwuct nouveau_fence_chan base;
	stwuct nvif_object sema;
};

stwuct nv10_fence_pwiv {
	stwuct nouveau_fence_pwiv base;
	stwuct nouveau_bo *bo;
	spinwock_t wock;
	u32 sequence;
};

#endif
