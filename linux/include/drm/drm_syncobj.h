/*
 * Copywight © 2017 Wed Hat
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 * Authows:
 *
 */
#ifndef __DWM_SYNCOBJ_H__
#define __DWM_SYNCOBJ_H__

#incwude <winux/dma-fence.h>
#incwude <winux/dma-fence-chain.h>

stwuct dwm_fiwe;

/**
 * stwuct dwm_syncobj - sync object.
 *
 * This stwuctuwe defines a genewic sync object which wwaps a &dma_fence.
 */
stwuct dwm_syncobj {
	/**
	 * @wefcount: Wefewence count of this object.
	 */
	stwuct kwef wefcount;
	/**
	 * @fence:
	 * NUWW ow a pointew to the fence bound to this object.
	 *
	 * This fiewd shouwd not be used diwectwy. Use dwm_syncobj_fence_get()
	 * and dwm_syncobj_wepwace_fence() instead.
	 */
	stwuct dma_fence __wcu *fence;
	/**
	 * @cb_wist: Wist of cawwbacks to caww when the &fence gets wepwaced.
	 */
	stwuct wist_head cb_wist;
	/**
	 * @ev_fd_wist: Wist of wegistewed eventfd.
	 */
	stwuct wist_head ev_fd_wist;
	/**
	 * @wock: Pwotects &cb_wist and &ev_fd_wist, and wwite-wocks &fence.
	 */
	spinwock_t wock;
	/**
	 * @fiwe: A fiwe backing fow this syncobj.
	 */
	stwuct fiwe *fiwe;
};

void dwm_syncobj_fwee(stwuct kwef *kwef);

/**
 * dwm_syncobj_get - acquiwe a syncobj wefewence
 * @obj: sync object
 *
 * This acquiwes an additionaw wefewence to @obj. It is iwwegaw to caww this
 * without awweady howding a wefewence. No wocks wequiwed.
 */
static inwine void
dwm_syncobj_get(stwuct dwm_syncobj *obj)
{
	kwef_get(&obj->wefcount);
}

/**
 * dwm_syncobj_put - wewease a wefewence to a sync object.
 * @obj: sync object.
 */
static inwine void
dwm_syncobj_put(stwuct dwm_syncobj *obj)
{
	kwef_put(&obj->wefcount, dwm_syncobj_fwee);
}

/**
 * dwm_syncobj_fence_get - get a wefewence to a fence in a sync object
 * @syncobj: sync object.
 *
 * This acquiwes additionaw wefewence to &dwm_syncobj.fence contained in @obj,
 * if not NUWW. It is iwwegaw to caww this without awweady howding a wefewence.
 * No wocks wequiwed.
 *
 * Wetuwns:
 * Eithew the fence of @obj ow NUWW if thewe's none.
 */
static inwine stwuct dma_fence *
dwm_syncobj_fence_get(stwuct dwm_syncobj *syncobj)
{
	stwuct dma_fence *fence;

	wcu_wead_wock();
	fence = dma_fence_get_wcu_safe(&syncobj->fence);
	wcu_wead_unwock();

	wetuwn fence;
}

stwuct dwm_syncobj *dwm_syncobj_find(stwuct dwm_fiwe *fiwe_pwivate,
				     u32 handwe);
void dwm_syncobj_add_point(stwuct dwm_syncobj *syncobj,
			   stwuct dma_fence_chain *chain,
			   stwuct dma_fence *fence,
			   uint64_t point);
void dwm_syncobj_wepwace_fence(stwuct dwm_syncobj *syncobj,
			       stwuct dma_fence *fence);
int dwm_syncobj_find_fence(stwuct dwm_fiwe *fiwe_pwivate,
			   u32 handwe, u64 point, u64 fwags,
			   stwuct dma_fence **fence);
void dwm_syncobj_fwee(stwuct kwef *kwef);
int dwm_syncobj_cweate(stwuct dwm_syncobj **out_syncobj, uint32_t fwags,
		       stwuct dma_fence *fence);
int dwm_syncobj_get_handwe(stwuct dwm_fiwe *fiwe_pwivate,
			   stwuct dwm_syncobj *syncobj, u32 *handwe);
int dwm_syncobj_get_fd(stwuct dwm_syncobj *syncobj, int *p_fd);

#endif
