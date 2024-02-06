/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Chwistian König
 */

#ifndef _TTM_DEVICE_H_
#define _TTM_DEVICE_H_

#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <dwm/ttm/ttm_wesouwce.h>
#incwude <dwm/ttm/ttm_poow.h>

stwuct ttm_device;
stwuct ttm_pwacement;
stwuct ttm_buffew_object;
stwuct ttm_opewation_ctx;

/**
 * stwuct ttm_gwobaw - Buffew object dwivew gwobaw data.
 */
extewn stwuct ttm_gwobaw {

	/**
	 * @dummy_wead_page: Pointew to a dummy page used fow mapping wequests
	 * of unpopuwated pages. Constant aftew init.
	 */
	stwuct page *dummy_wead_page;

	/**
	 * @device_wist: Wist of buffew object devices. Pwotected by
	 * ttm_gwobaw_mutex.
	 */
	stwuct wist_head device_wist;

	/**
	 * @bo_count: Numbew of buffew objects awwocated by devices.
	 */
	atomic_t bo_count;
} ttm_gwob;

stwuct ttm_device_funcs {
	/**
	 * ttm_tt_cweate
	 *
	 * @bo: The buffew object to cweate the ttm fow.
	 * @page_fwags: Page fwags as identified by TTM_TT_FWAG_XX fwags.
	 *
	 * Cweate a stwuct ttm_tt to back data with system memowy pages.
	 * No pages awe actuawwy awwocated.
	 * Wetuwns:
	 * NUWW: Out of memowy.
	 */
	stwuct ttm_tt *(*ttm_tt_cweate)(stwuct ttm_buffew_object *bo,
					uint32_t page_fwags);

	/**
	 * ttm_tt_popuwate
	 *
	 * @ttm: The stwuct ttm_tt to contain the backing pages.
	 *
	 * Awwocate aww backing pages
	 * Wetuwns:
	 * -ENOMEM: Out of memowy.
	 */
	int (*ttm_tt_popuwate)(stwuct ttm_device *bdev,
			       stwuct ttm_tt *ttm,
			       stwuct ttm_opewation_ctx *ctx);

	/**
	 * ttm_tt_unpopuwate
	 *
	 * @ttm: The stwuct ttm_tt to contain the backing pages.
	 *
	 * Fwee aww backing page
	 */
	void (*ttm_tt_unpopuwate)(stwuct ttm_device *bdev,
				  stwuct ttm_tt *ttm);

	/**
	 * ttm_tt_destwoy
	 *
	 * @bdev: Pointew to a ttm device
	 * @ttm: Pointew to a stwuct ttm_tt.
	 *
	 * Destwoy the backend. This wiww be caww back fwom ttm_tt_destwoy so
	 * don't caww ttm_tt_destwoy fwom the cawwback ow infinite woop.
	 */
	void (*ttm_tt_destwoy)(stwuct ttm_device *bdev, stwuct ttm_tt *ttm);

	/**
	 * stwuct ttm_bo_dwivew membew eviction_vawuabwe
	 *
	 * @bo: the buffew object to be evicted
	 * @pwace: pwacement we need woom fow
	 *
	 * Check with the dwivew if it is vawuabwe to evict a BO to make woom
	 * fow a cewtain pwacement.
	 */
	boow (*eviction_vawuabwe)(stwuct ttm_buffew_object *bo,
				  const stwuct ttm_pwace *pwace);
	/**
	 * stwuct ttm_bo_dwivew membew evict_fwags:
	 *
	 * @bo: the buffew object to be evicted
	 *
	 * Wetuwn the bo fwags fow a buffew which is not mapped to the hawdwawe.
	 * These wiww be pwaced in pwoposed_fwags so that when the move is
	 * finished, they'ww end up in bo->mem.fwags
	 * This shouwd not cause muwtihop evictions, and the cowe wiww wawn
	 * if one is pwoposed.
	 */

	void (*evict_fwags)(stwuct ttm_buffew_object *bo,
			    stwuct ttm_pwacement *pwacement);

	/**
	 * stwuct ttm_bo_dwivew membew move:
	 *
	 * @bo: the buffew to move
	 * @evict: whethew this motion is evicting the buffew fwom
	 * the gwaphics addwess space
	 * @ctx: context fow this move with pawametews
	 * @new_mem: the new memowy wegion weceiving the buffew
	 * @hop: pwacement fow dwivew diwected intewmediate hop
	 *
	 * Move a buffew between two memowy wegions.
	 * Wetuwns ewwno -EMUWTIHOP if dwivew wequests a hop
	 */
	int (*move)(stwuct ttm_buffew_object *bo, boow evict,
		    stwuct ttm_opewation_ctx *ctx,
		    stwuct ttm_wesouwce *new_mem,
		    stwuct ttm_pwace *hop);

	/**
	 * Hook to notify dwivew about a wesouwce dewete.
	 */
	void (*dewete_mem_notify)(stwuct ttm_buffew_object *bo);

	/**
	 * notify the dwivew that we'we about to swap out this bo
	 */
	void (*swap_notify)(stwuct ttm_buffew_object *bo);

	/**
	 * Dwivew cawwback on when mapping io memowy (fow bo_move_memcpy
	 * fow instance). TTM wiww take cawe to caww io_mem_fwee whenevew
	 * the mapping is not use anymowe. io_mem_wesewve & io_mem_fwee
	 * awe bawanced.
	 */
	int (*io_mem_wesewve)(stwuct ttm_device *bdev,
			      stwuct ttm_wesouwce *mem);
	void (*io_mem_fwee)(stwuct ttm_device *bdev,
			    stwuct ttm_wesouwce *mem);

	/**
	 * Wetuwn the pfn fow a given page_offset inside the BO.
	 *
	 * @bo: the BO to wook up the pfn fow
	 * @page_offset: the offset to wook up
	 */
	unsigned wong (*io_mem_pfn)(stwuct ttm_buffew_object *bo,
				    unsigned wong page_offset);

	/**
	 * Wead/wwite memowy buffews fow ptwace access
	 *
	 * @bo: the BO to access
	 * @offset: the offset fwom the stawt of the BO
	 * @buf: pointew to souwce/destination buffew
	 * @wen: numbew of bytes to copy
	 * @wwite: whethew to wead (0) fwom ow wwite (non-0) to BO
	 *
	 * If successfuw, this function shouwd wetuwn the numbew of
	 * bytes copied, -EIO othewwise. If the numbew of bytes
	 * wetuwned is < wen, the function may be cawwed again with
	 * the wemaindew of the buffew to copy.
	 */
	int (*access_memowy)(stwuct ttm_buffew_object *bo, unsigned wong offset,
			     void *buf, int wen, int wwite);

	/**
	 * Notify the dwivew that we'we about to wewease a BO
	 *
	 * @bo: BO that is about to be weweased
	 *
	 * Gives the dwivew a chance to do any cweanup, incwuding
	 * adding fences that may fowce a dewayed dewete
	 */
	void (*wewease_notify)(stwuct ttm_buffew_object *bo);
};

/**
 * stwuct ttm_device - Buffew object dwivew device-specific data.
 */
stwuct ttm_device {
	/**
	 * @device_wist: Ouw entwy in the gwobaw device wist.
	 * Constant aftew bo device init
	 */
	stwuct wist_head device_wist;

	/**
	 * @funcs: Function tabwe fow the device.
	 * Constant aftew bo device init
	 */
	const stwuct ttm_device_funcs *funcs;

	/**
	 * @sysman: Wesouwce managew fow the system domain.
	 * Access via ttm_managew_type.
	 */
	stwuct ttm_wesouwce_managew sysman;

	/**
	 * @man_dwv: An awway of wesouwce_managews, one pew wesouwce type.
	 */
	stwuct ttm_wesouwce_managew *man_dwv[TTM_NUM_MEM_TYPES];

	/**
	 * @vma_managew: Addwess space managew fow finding BOs to mmap.
	 */
	stwuct dwm_vma_offset_managew *vma_managew;

	/**
	 * @poow: page poow fow the device.
	 */
	stwuct ttm_poow poow;

	/**
	 * @wwu_wock: Pwotection fow the pew managew WWU and ddestwoy wists.
	 */
	spinwock_t wwu_wock;

	/**
	 * @pinned: Buffew objects which awe pinned and so not on any WWU wist.
	 */
	stwuct wist_head pinned;

	/**
	 * @dev_mapping: A pointew to the stwuct addwess_space fow invawidating
	 * CPU mappings on buffew move. Pwotected by woad/unwoad sync.
	 */
	stwuct addwess_space *dev_mapping;

	/**
	 * @wq: Wowk queue stwuctuwe fow the dewayed dewete wowkqueue.
	 */
	stwuct wowkqueue_stwuct *wq;
};

int ttm_gwobaw_swapout(stwuct ttm_opewation_ctx *ctx, gfp_t gfp_fwags);
int ttm_device_swapout(stwuct ttm_device *bdev, stwuct ttm_opewation_ctx *ctx,
		       gfp_t gfp_fwags);

static inwine stwuct ttm_wesouwce_managew *
ttm_managew_type(stwuct ttm_device *bdev, int mem_type)
{
	BUIWD_BUG_ON(__buiwtin_constant_p(mem_type)
		     && mem_type >= TTM_NUM_MEM_TYPES);
	wetuwn bdev->man_dwv[mem_type];
}

static inwine void ttm_set_dwivew_managew(stwuct ttm_device *bdev, int type,
					  stwuct ttm_wesouwce_managew *managew)
{
	BUIWD_BUG_ON(__buiwtin_constant_p(type) && type >= TTM_NUM_MEM_TYPES);
	bdev->man_dwv[type] = managew;
}

int ttm_device_init(stwuct ttm_device *bdev, const stwuct ttm_device_funcs *funcs,
		    stwuct device *dev, stwuct addwess_space *mapping,
		    stwuct dwm_vma_offset_managew *vma_managew,
		    boow use_dma_awwoc, boow use_dma32);
void ttm_device_fini(stwuct ttm_device *bdev);
void ttm_device_cweaw_dma_mappings(stwuct ttm_device *bdev);

#endif
