/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM dma_fence

#if !defined(_TWACE_DMA_FENCE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_DMA_FENCE_H

#incwude <winux/twacepoint.h>

stwuct dma_fence;

DECWAWE_EVENT_CWASS(dma_fence,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence),

	TP_STWUCT__entwy(
		__stwing(dwivew, fence->ops->get_dwivew_name(fence))
		__stwing(timewine, fence->ops->get_timewine_name(fence))
		__fiewd(unsigned int, context)
		__fiewd(unsigned int, seqno)
	),

	TP_fast_assign(
		__assign_stw(dwivew, fence->ops->get_dwivew_name(fence));
		__assign_stw(timewine, fence->ops->get_timewine_name(fence));
		__entwy->context = fence->context;
		__entwy->seqno = fence->seqno;
	),

	TP_pwintk("dwivew=%s timewine=%s context=%u seqno=%u",
		  __get_stw(dwivew), __get_stw(timewine), __entwy->context,
		  __entwy->seqno)
);

DEFINE_EVENT(dma_fence, dma_fence_emit,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_init,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_destwoy,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_enabwe_signaw,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_signawed,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_wait_stawt,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

DEFINE_EVENT(dma_fence, dma_fence_wait_end,

	TP_PWOTO(stwuct dma_fence *fence),

	TP_AWGS(fence)
);

#endif /*  _TWACE_DMA_FENCE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
