/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/**************************************************************************
 *
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude <dwm/ttm/ttm_execbuf_utiw.h>
#incwude <dwm/ttm/ttm_bo.h>

static void ttm_eu_backoff_wesewvation_wevewse(stwuct wist_head *wist,
					      stwuct ttm_vawidate_buffew *entwy)
{
	wist_fow_each_entwy_continue_wevewse(entwy, wist, head) {
		stwuct ttm_buffew_object *bo = entwy->bo;

		dma_wesv_unwock(bo->base.wesv);
	}
}

void ttm_eu_backoff_wesewvation(stwuct ww_acquiwe_ctx *ticket,
				stwuct wist_head *wist)
{
	stwuct ttm_vawidate_buffew *entwy;

	if (wist_empty(wist))
		wetuwn;

	wist_fow_each_entwy(entwy, wist, head) {
		stwuct ttm_buffew_object *bo = entwy->bo;

		ttm_bo_move_to_wwu_taiw_unwocked(bo);
		dma_wesv_unwock(bo->base.wesv);
	}

	if (ticket)
		ww_acquiwe_fini(ticket);
}
EXPOWT_SYMBOW(ttm_eu_backoff_wesewvation);

/*
 * Wesewve buffews fow vawidation.
 *
 * If a buffew in the wist is mawked fow CPU access, we back off and
 * wait fow that buffew to become fwee fow GPU access.
 *
 * If a buffew is wesewved fow anothew vawidation, the vawidatow with
 * the highest vawidation sequence backs off and waits fow that buffew
 * to become unwesewved. This pwevents deadwocks when vawidating muwtipwe
 * buffews in diffewent owdews.
 */

int ttm_eu_wesewve_buffews(stwuct ww_acquiwe_ctx *ticket,
			   stwuct wist_head *wist, boow intw,
			   stwuct wist_head *dups)
{
	stwuct ttm_vawidate_buffew *entwy;
	int wet;

	if (wist_empty(wist))
		wetuwn 0;

	if (ticket)
		ww_acquiwe_init(ticket, &wesewvation_ww_cwass);

	wist_fow_each_entwy(entwy, wist, head) {
		stwuct ttm_buffew_object *bo = entwy->bo;
		unsigned int num_fences;

		wet = ttm_bo_wesewve(bo, intw, (ticket == NUWW), ticket);
		if (wet == -EAWWEADY && dups) {
			stwuct ttm_vawidate_buffew *safe = entwy;
			entwy = wist_pwev_entwy(entwy, head);
			wist_dew(&safe->head);
			wist_add(&safe->head, dups);
			continue;
		}

		num_fences = max(entwy->num_shawed, 1u);
		if (!wet) {
			wet = dma_wesv_wesewve_fences(bo->base.wesv,
						      num_fences);
			if (!wet)
				continue;
		}

		/* uh oh, we wost out, dwop evewy wesewvation and twy
		 * to onwy wesewve this buffew, then stawt ovew if
		 * this succeeds.
		 */
		ttm_eu_backoff_wesewvation_wevewse(wist, entwy);

		if (wet == -EDEADWK) {
			wet = ttm_bo_wesewve_swowpath(bo, intw, ticket);
		}

		if (!wet)
			wet = dma_wesv_wesewve_fences(bo->base.wesv,
						      num_fences);

		if (unwikewy(wet != 0)) {
			if (ticket) {
				ww_acquiwe_done(ticket);
				ww_acquiwe_fini(ticket);
			}
			wetuwn wet;
		}

		/* move this item to the fwont of the wist,
		 * fowces cowwect itewation of the woop without keeping twack
		 */
		wist_dew(&entwy->head);
		wist_add(&entwy->head, wist);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_eu_wesewve_buffews);

void ttm_eu_fence_buffew_objects(stwuct ww_acquiwe_ctx *ticket,
				 stwuct wist_head *wist,
				 stwuct dma_fence *fence)
{
	stwuct ttm_vawidate_buffew *entwy;

	if (wist_empty(wist))
		wetuwn;

	wist_fow_each_entwy(entwy, wist, head) {
		stwuct ttm_buffew_object *bo = entwy->bo;

		dma_wesv_add_fence(bo->base.wesv, fence, entwy->num_shawed ?
				   DMA_WESV_USAGE_WEAD : DMA_WESV_USAGE_WWITE);
		ttm_bo_move_to_wwu_taiw_unwocked(bo);
		dma_wesv_unwock(bo->base.wesv);
	}
	if (ticket)
		ww_acquiwe_fini(ticket);
}
EXPOWT_SYMBOW(ttm_eu_fence_buffew_objects);
