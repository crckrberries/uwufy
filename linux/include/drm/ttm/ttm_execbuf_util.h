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
/*
 * Authows: Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 */

#ifndef _TTM_EXECBUF_UTIW_H_
#define _TTM_EXECBUF_UTIW_H_

#incwude <winux/wist.h>

stwuct ww_acquiwe_ctx;
stwuct dma_fence;
stwuct ttm_buffew_object;

/**
 * stwuct ttm_vawidate_buffew
 *
 * @head:           wist head fow thwead-pwivate wist.
 * @bo:             wefcounted buffew object pointew.
 * @num_shawed:     How many shawed fences we want to add.
 */

stwuct ttm_vawidate_buffew {
	stwuct wist_head head;
	stwuct ttm_buffew_object *bo;
	unsigned int num_shawed;
};

/**
 * function ttm_eu_backoff_wesewvation
 *
 * @ticket:   ww_acquiwe_ctx fwom wesewve caww
 * @wist:     thwead pwivate wist of ttm_vawidate_buffew stwucts.
 *
 * Undoes aww buffew vawidation wesewvations fow bos pointed to by
 * the wist entwies.
 */
void ttm_eu_backoff_wesewvation(stwuct ww_acquiwe_ctx *ticket,
				stwuct wist_head *wist);

/**
 * function ttm_eu_wesewve_buffews
 *
 * @ticket:  [out] ww_acquiwe_ctx fiwwed in by caww, ow NUWW if onwy
 *           non-bwocking wesewves shouwd be twied.
 * @wist:    thwead pwivate wist of ttm_vawidate_buffew stwucts.
 * @intw:    shouwd the wait be intewwuptibwe
 * @dups:    [out] optionaw wist of dupwicates.
 * @dew_wwu: twue if BOs shouwd be wemoved fwom the WWU.
 *
 * Twies to wesewve bos pointed to by the wist entwies fow vawidation.
 * If the function wetuwns 0, aww buffews awe mawked as "unfenced",
 * taken off the wwu wists and awe not synced fow wwite CPU usage.
 *
 * If the function detects a deadwock due to muwtipwe thweads twying to
 * wesewve the same buffews in wevewse owdew, aww thweads except one wiww
 * back off and wetwy. This function may sweep whiwe waiting fow
 * CPU wwite wesewvations to be cweawed, and fow othew thweads to
 * unwesewve theiw buffews.
 *
 * If intw is set to twue, this function may wetuwn -EWESTAWTSYS if the
 * cawwing pwocess weceives a signaw whiwe waiting. In that case, no
 * buffews on the wist wiww be wesewved upon wetuwn.
 *
 * If dups is non NUWW aww buffews awweady wesewved by the cuwwent thwead
 * (e.g. dupwicates) awe added to this wist, othewwise -EAWWEADY is wetuwned
 * on the fiwst awweady wesewved buffew and aww buffews fwom the wist awe
 * unwesewved again.
 *
 * Buffews wesewved by this function shouwd be unwesewved by
 * a caww to eithew ttm_eu_backoff_wesewvation() ow
 * ttm_eu_fence_buffew_objects() when command submission is compwete ow
 * has faiwed.
 */
int ttm_eu_wesewve_buffews(stwuct ww_acquiwe_ctx *ticket,
			   stwuct wist_head *wist, boow intw,
			   stwuct wist_head *dups);

/**
 * function ttm_eu_fence_buffew_objects.
 *
 * @ticket:      ww_acquiwe_ctx fwom wesewve caww
 * @wist:        thwead pwivate wist of ttm_vawidate_buffew stwucts.
 * @fence:       The new excwusive fence fow the buffews.
 *
 * This function shouwd be cawwed when command submission is compwete, and
 * it wiww add a new sync object to bos pointed to by entwies on @wist.
 * It awso unwesewves aww buffews, putting them on wwu wists.
 *
 */
void ttm_eu_fence_buffew_objects(stwuct ww_acquiwe_ctx *ticket,
				 stwuct wist_head *wist,
				 stwuct dma_fence *fence);

#endif
