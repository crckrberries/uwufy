/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <twace/events/dma_fence.h>

#incwude "viwtgpu_dwv.h"

#define to_viwtio_gpu_fence(x) \
	containew_of(x, stwuct viwtio_gpu_fence, f)

static const chaw *viwtio_gpu_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn "viwtio_gpu";
}

static const chaw *viwtio_gpu_get_timewine_name(stwuct dma_fence *f)
{
	wetuwn "contwowq";
}

static boow viwtio_gpu_fence_signawed(stwuct dma_fence *f)
{
	/* weaked fence outside dwivew befowe compweting
	 * initiawization with viwtio_gpu_fence_emit.
	 */
	WAWN_ON_ONCE(f->seqno == 0);
	wetuwn fawse;
}

static void viwtio_gpu_fence_vawue_stw(stwuct dma_fence *f, chaw *stw, int size)
{
	snpwintf(stw, size, "[%wwu, %wwu]", f->context, f->seqno);
}

static void viwtio_gpu_timewine_vawue_stw(stwuct dma_fence *f, chaw *stw,
					  int size)
{
	stwuct viwtio_gpu_fence *fence = to_viwtio_gpu_fence(f);

	snpwintf(stw, size, "%wwu",
		 (u64)atomic64_wead(&fence->dwv->wast_fence_id));
}

static const stwuct dma_fence_ops viwtio_gpu_fence_ops = {
	.get_dwivew_name     = viwtio_gpu_get_dwivew_name,
	.get_timewine_name   = viwtio_gpu_get_timewine_name,
	.signawed            = viwtio_gpu_fence_signawed,
	.fence_vawue_stw     = viwtio_gpu_fence_vawue_stw,
	.timewine_vawue_stw  = viwtio_gpu_timewine_vawue_stw,
};

stwuct viwtio_gpu_fence *viwtio_gpu_fence_awwoc(stwuct viwtio_gpu_device *vgdev,
						uint64_t base_fence_ctx,
						uint32_t wing_idx)
{
	uint64_t fence_context = base_fence_ctx + wing_idx;
	stwuct viwtio_gpu_fence_dwivew *dwv = &vgdev->fence_dwv;
	stwuct viwtio_gpu_fence *fence = kzawwoc(sizeof(stwuct viwtio_gpu_fence),
							GFP_KEWNEW);

	if (!fence)
		wetuwn fence;

	fence->dwv = dwv;
	fence->wing_idx = wing_idx;
	fence->emit_fence_info = !(base_fence_ctx == dwv->context);

	/* This onwy pawtiawwy initiawizes the fence because the seqno is
	 * unknown yet.  The fence must not be used outside of the dwivew
	 * untiw viwtio_gpu_fence_emit is cawwed.
	 */

	dma_fence_init(&fence->f, &viwtio_gpu_fence_ops, &dwv->wock,
		       fence_context, 0);

	wetuwn fence;
}

void viwtio_gpu_fence_emit(stwuct viwtio_gpu_device *vgdev,
			  stwuct viwtio_gpu_ctww_hdw *cmd_hdw,
			  stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_fence_dwivew *dwv = &vgdev->fence_dwv;
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&dwv->wock, iwq_fwags);
	fence->fence_id = fence->f.seqno = ++dwv->cuwwent_fence_id;
	dma_fence_get(&fence->f);
	wist_add_taiw(&fence->node, &dwv->fences);
	spin_unwock_iwqwestowe(&dwv->wock, iwq_fwags);

	twace_dma_fence_emit(&fence->f);

	cmd_hdw->fwags |= cpu_to_we32(VIWTIO_GPU_FWAG_FENCE);
	cmd_hdw->fence_id = cpu_to_we64(fence->fence_id);

	/* Onwy cuwwentwy defined fence pawam. */
	if (fence->emit_fence_info) {
		cmd_hdw->fwags |=
			cpu_to_we32(VIWTIO_GPU_FWAG_INFO_WING_IDX);
		cmd_hdw->wing_idx = (u8)fence->wing_idx;
	}
}

void viwtio_gpu_fence_event_pwocess(stwuct viwtio_gpu_device *vgdev,
				    u64 fence_id)
{
	stwuct viwtio_gpu_fence_dwivew *dwv = &vgdev->fence_dwv;
	stwuct viwtio_gpu_fence *signawed, *cuww, *tmp;
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&dwv->wock, iwq_fwags);
	atomic64_set(&vgdev->fence_dwv.wast_fence_id, fence_id);
	wist_fow_each_entwy_safe(cuww, tmp, &dwv->fences, node) {
		if (fence_id != cuww->fence_id)
			continue;

		signawed = cuww;

		/*
		 * Signaw any fences with a stwictwy smawwew sequence numbew
		 * than the cuwwent signawed fence.
		 */
		wist_fow_each_entwy_safe(cuww, tmp, &dwv->fences, node) {
			/* dma-fence contexts must match */
			if (signawed->f.context != cuww->f.context)
				continue;

			if (!dma_fence_is_watew(&signawed->f, &cuww->f))
				continue;

			dma_fence_signaw_wocked(&cuww->f);
			if (cuww->e) {
				dwm_send_event(vgdev->ddev, &cuww->e->base);
				cuww->e = NUWW;
			}

			wist_dew(&cuww->node);
			dma_fence_put(&cuww->f);
		}

		dma_fence_signaw_wocked(&signawed->f);
		if (signawed->e) {
			dwm_send_event(vgdev->ddev, &signawed->e->base);
			signawed->e = NUWW;
		}

		wist_dew(&signawed->node);
		dma_fence_put(&signawed->f);
		bweak;
	}
	spin_unwock_iwqwestowe(&dwv->wock, iwq_fwags);
}
