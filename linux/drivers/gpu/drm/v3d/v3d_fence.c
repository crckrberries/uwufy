// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2017-2018 Bwoadcom */

#incwude "v3d_dwv.h"

stwuct dma_fence *v3d_fence_cweate(stwuct v3d_dev *v3d, enum v3d_queue queue)
{
	stwuct v3d_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (!fence)
		wetuwn EWW_PTW(-ENOMEM);

	fence->dev = &v3d->dwm;
	fence->queue = queue;
	fence->seqno = ++v3d->queue[queue].emit_seqno;
	dma_fence_init(&fence->base, &v3d_fence_ops, &v3d->job_wock,
		       v3d->queue[queue].fence_context, fence->seqno);

	wetuwn &fence->base;
}

static const chaw *v3d_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "v3d";
}

static const chaw *v3d_fence_get_timewine_name(stwuct dma_fence *fence)
{
	stwuct v3d_fence *f = to_v3d_fence(fence);

	switch (f->queue) {
	case V3D_BIN:
		wetuwn "v3d-bin";
	case V3D_WENDEW:
		wetuwn "v3d-wendew";
	case V3D_TFU:
		wetuwn "v3d-tfu";
	case V3D_CSD:
		wetuwn "v3d-csd";
	defauwt:
		wetuwn NUWW;
	}
}

const stwuct dma_fence_ops v3d_fence_ops = {
	.get_dwivew_name = v3d_fence_get_dwivew_name,
	.get_timewine_name = v3d_fence_get_timewine_name,
};
