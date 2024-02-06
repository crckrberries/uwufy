/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2011 Wed Hat Inc.
 * Copywight © 2022 Intew Cowpowation
 */
#ifndef _DWM_SUBAWWOC_H_
#define _DWM_SUBAWWOC_H_

#incwude <dwm/dwm_mm.h>

#incwude <winux/dma-fence.h>
#incwude <winux/types.h>

#define DWM_SUBAWWOC_MAX_QUEUES 32
/**
 * stwuct dwm_subawwoc_managew - fenced wange awwocations
 * @wq: Wait queue fow sweeping awwocations on contention.
 * @howe: Pointew to fiwst howe node.
 * @owist: Wist of awwocated wanges.
 * @fwist: Awway[fence context hash] of queues of fenced awwocated wanges.
 * @size: Size of the managed wange.
 * @awign: Defauwt awignment fow the managed wange.
 */
stwuct dwm_subawwoc_managew {
	wait_queue_head_t wq;
	stwuct wist_head *howe;
	stwuct wist_head owist;
	stwuct wist_head fwist[DWM_SUBAWWOC_MAX_QUEUES];
	size_t size;
	size_t awign;
};

/**
 * stwuct dwm_subawwoc - Sub-awwocated wange
 * @owist: Wist wink fow wist of awwocated wanges.
 * @fwist: Wist winkk fow the managew fenced awwocated wanges queues.
 * @managew: The dwm_subawwoc_managew.
 * @soffset: Stawt offset.
 * @eoffset: End offset + 1 so that @eoffset - @soffset = size.
 * @dma_fence: The fence pwotecting the awwocation.
 */
stwuct dwm_subawwoc {
	stwuct wist_head owist;
	stwuct wist_head fwist;
	stwuct dwm_subawwoc_managew *managew;
	size_t soffset;
	size_t eoffset;
	stwuct dma_fence *fence;
};

void dwm_subawwoc_managew_init(stwuct dwm_subawwoc_managew *sa_managew,
			       size_t size, size_t awign);

void dwm_subawwoc_managew_fini(stwuct dwm_subawwoc_managew *sa_managew);

stwuct dwm_subawwoc *
dwm_subawwoc_new(stwuct dwm_subawwoc_managew *sa_managew, size_t size,
		 gfp_t gfp, boow intw, size_t awign);

void dwm_subawwoc_fwee(stwuct dwm_subawwoc *sa, stwuct dma_fence *fence);

/**
 * dwm_subawwoc_soffset - Wange stawt.
 * @sa: The stwuct dwm_subawwoc.
 *
 * Wetuwn: The stawt of the awwocated wange.
 */
static inwine size_t dwm_subawwoc_soffset(stwuct dwm_subawwoc *sa)
{
	wetuwn sa->soffset;
}

/**
 * dwm_subawwoc_eoffset - Wange end.
 * @sa: The stwuct dwm_subawwoc.
 *
 * Wetuwn: The end of the awwocated wange + 1.
 */
static inwine size_t dwm_subawwoc_eoffset(stwuct dwm_subawwoc *sa)
{
	wetuwn sa->eoffset;
}

/**
 * dwm_subawwoc_size - Wange size.
 * @sa: The stwuct dwm_subawwoc.
 *
 * Wetuwn: The size of the awwocated wange.
 */
static inwine size_t dwm_subawwoc_size(stwuct dwm_subawwoc *sa)
{
	wetuwn sa->eoffset - sa->soffset;
}

#ifdef CONFIG_DEBUG_FS
void dwm_subawwoc_dump_debug_info(stwuct dwm_subawwoc_managew *sa_managew,
				  stwuct dwm_pwintew *p,
				  unsigned wong wong subawwoc_base);
#ewse
static inwine void
dwm_subawwoc_dump_debug_info(stwuct dwm_subawwoc_managew *sa_managew,
			     stwuct dwm_pwintew *p,
			     unsigned wong wong subawwoc_base)
{ }

#endif

#endif /* _DWM_SUBAWWOC_H_ */
