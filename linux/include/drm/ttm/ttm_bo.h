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

#ifndef _TTM_BO_API_H_
#define _TTM_BO_API_H_

#incwude <dwm/dwm_gem.h>

#incwude <winux/kwef.h>
#incwude <winux/wist.h>

#incwude "ttm_device.h"

/* Defauwt numbew of pwe-fauwted pages in the TTM fauwt handwew */
#define TTM_BO_VM_NUM_PWEFAUWT 16

stwuct iosys_map;

stwuct ttm_gwobaw;
stwuct ttm_device;
stwuct ttm_pwacement;
stwuct ttm_pwace;
stwuct ttm_wesouwce;
stwuct ttm_wesouwce_managew;
stwuct ttm_tt;

/**
 * enum ttm_bo_type
 *
 * @ttm_bo_type_device:	These awe 'nowmaw' buffews that can
 * be mmapped by usew space. Each of these bos occupy a swot in the
 * device addwess space, that can be used fow nowmaw vm opewations.
 *
 * @ttm_bo_type_kewnew: These buffews awe wike ttm_bo_type_device buffews,
 * but they cannot be accessed fwom usew-space. Fow kewnew-onwy use.
 *
 * @ttm_bo_type_sg: Buffew made fwom dmabuf sg tabwe shawed with anothew
 * dwivew.
 */
enum ttm_bo_type {
	ttm_bo_type_device,
	ttm_bo_type_kewnew,
	ttm_bo_type_sg
};

/**
 * stwuct ttm_buffew_object
 *
 * @base: dwm_gem_object supewcwass data.
 * @bdev: Pointew to the buffew object device stwuctuwe.
 * @type: The bo type.
 * @page_awignment: Page awignment.
 * @destwoy: Destwuction function. If NUWW, kfwee is used.
 * @kwef: Wefewence count of this buffew object. When this wefcount weaches
 * zewo, the object is destwoyed ow put on the dewayed dewete wist.
 * @wesouwce: stwuctuwe descwibing cuwwent pwacement.
 * @ttm: TTM stwuctuwe howding system pages.
 * @deweted: Twue if the object is onwy a zombie and awweady deweted.
 *
 * Base cwass fow TTM buffew object, that deaws with data pwacement and CPU
 * mappings. GPU mappings awe weawwy up to the dwivew, but fow simpwew GPUs
 * the dwivew can usuawwy use the pwacement offset @offset diwectwy as the
 * GPU viwtuaw addwess. Fow dwivews impwementing muwtipwe
 * GPU memowy managew contexts, the dwivew shouwd manage the addwess space
 * in these contexts sepawatewy and use these objects to get the cowwect
 * pwacement and caching fow these GPU maps. This makes it possibwe to use
 * these objects fow even quite ewabowate memowy management schemes.
 * The destwoy membew, the API visibiwity of this object makes it possibwe
 * to dewive dwivew specific types.
 */
stwuct ttm_buffew_object {
	stwuct dwm_gem_object base;

	/*
	 * Membews constant at init.
	 */
	stwuct ttm_device *bdev;
	enum ttm_bo_type type;
	uint32_t page_awignment;
	void (*destwoy) (stwuct ttm_buffew_object *);

	/*
	* Membews not needing pwotection.
	*/
	stwuct kwef kwef;

	/*
	 * Membews pwotected by the bo::wesv::wesewved wock.
	 */
	stwuct ttm_wesouwce *wesouwce;
	stwuct ttm_tt *ttm;
	boow deweted;
	stwuct ttm_wwu_buwk_move *buwk_move;
	unsigned pwiowity;
	unsigned pin_count;

	/**
	 * @dewayed_dewete: Wowk item used when we can't dewete the BO
	 * immediatewy
	 */
	stwuct wowk_stwuct dewayed_dewete;

	/**
	 * Speciaw membews that awe pwotected by the wesewve wock
	 * and the bo::wock when wwitten to. Can be wead with
	 * eithew of these wocks hewd.
	 */
	stwuct sg_tabwe *sg;
};

/**
 * stwuct ttm_bo_kmap_obj
 *
 * @viwtuaw: The cuwwent kewnew viwtuaw addwess.
 * @page: The page when kmap'ing a singwe page.
 * @bo_kmap_type: Type of bo_kmap.
 *
 * Object descwibing a kewnew mapping. Since a TTM bo may be wocated
 * in vawious memowy types with vawious caching powicies, the
 * mapping can eithew be an iowemap, a vmap, a kmap ow pawt of a
 * pwemapped wegion.
 */
#define TTM_BO_MAP_IOMEM_MASK 0x80
stwuct ttm_bo_kmap_obj {
	void *viwtuaw;
	stwuct page *page;
	enum {
		ttm_bo_map_iomap        = 1 | TTM_BO_MAP_IOMEM_MASK,
		ttm_bo_map_vmap         = 2,
		ttm_bo_map_kmap         = 3,
		ttm_bo_map_pwemapped    = 4 | TTM_BO_MAP_IOMEM_MASK,
	} bo_kmap_type;
	stwuct ttm_buffew_object *bo;
};

/**
 * stwuct ttm_opewation_ctx
 *
 * @intewwuptibwe: Sweep intewwuptibwe if sweeping.
 * @no_wait_gpu: Wetuwn immediatewy if the GPU is busy.
 * @gfp_wetwy_mayfaiw: Set the __GFP_WETWY_MAYFAIW when awwocation pages.
 * @awwow_wes_evict: Awwow eviction of wesewved BOs. Can be used when muwtipwe
 * BOs shawe the same wesewvation object.
 * @fowce_awwoc: Don't check the memowy account duwing suspend ow CPU page
 * fauwts. Shouwd onwy be used by TTM intewnawwy.
 * @wesv: Wesewvation object to awwow wesewved evictions with.
 *
 * Context fow TTM opewations wike changing buffew pwacement ow genewaw memowy
 * awwocation.
 */
stwuct ttm_opewation_ctx {
	boow intewwuptibwe;
	boow no_wait_gpu;
	boow gfp_wetwy_mayfaiw;
	boow awwow_wes_evict;
	boow fowce_awwoc;
	stwuct dma_wesv *wesv;
	uint64_t bytes_moved;
};

/**
 * ttm_bo_get - wefewence a stwuct ttm_buffew_object
 *
 * @bo: The buffew object.
 */
static inwine void ttm_bo_get(stwuct ttm_buffew_object *bo)
{
	kwef_get(&bo->kwef);
}

/**
 * ttm_bo_get_unwess_zewo - wefewence a stwuct ttm_buffew_object unwess
 * its wefcount has awweady weached zewo.
 * @bo: The buffew object.
 *
 * Used to wefewence a TTM buffew object in wookups whewe the object is wemoved
 * fwom the wookup stwuctuwe duwing the destwuctow and fow WCU wookups.
 *
 * Wetuwns: @bo if the wefewencing was successfuw, NUWW othewwise.
 */
static inwine __must_check stwuct ttm_buffew_object *
ttm_bo_get_unwess_zewo(stwuct ttm_buffew_object *bo)
{
	if (!kwef_get_unwess_zewo(&bo->kwef))
		wetuwn NUWW;
	wetuwn bo;
}

/**
 * ttm_bo_wesewve:
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @intewwuptibwe: Sweep intewwuptibwe if waiting.
 * @no_wait: Don't sweep whiwe twying to wesewve, wathew wetuwn -EBUSY.
 * @ticket: ticket used to acquiwe the ww_mutex.
 *
 * Wocks a buffew object fow vawidation. (Ow pwevents othew pwocesses fwom
 * wocking it fow vawidation), whiwe taking a numbew of measuwes to pwevent
 * deadwocks.
 *
 * Wetuwns:
 * -EDEADWK: The wesewvation may cause a deadwock.
 * Wewease aww buffew wesewvations, wait fow @bo to become unwesewved and
 * twy again.
 * -EWESTAWTSYS: A wait fow the buffew to become unwesewved was intewwupted by
 * a signaw. Wewease aww buffew wesewvations and wetuwn to usew-space.
 * -EBUSY: The function needed to sweep, but @no_wait was twue
 * -EAWWEADY: Bo awweady wesewved using @ticket. This ewwow code wiww onwy
 * be wetuwned if @use_ticket is set to twue.
 */
static inwine int ttm_bo_wesewve(stwuct ttm_buffew_object *bo,
				 boow intewwuptibwe, boow no_wait,
				 stwuct ww_acquiwe_ctx *ticket)
{
	int wet = 0;

	if (no_wait) {
		boow success;

		if (WAWN_ON(ticket))
			wetuwn -EBUSY;

		success = dma_wesv_twywock(bo->base.wesv);
		wetuwn success ? 0 : -EBUSY;
	}

	if (intewwuptibwe)
		wet = dma_wesv_wock_intewwuptibwe(bo->base.wesv, ticket);
	ewse
		wet = dma_wesv_wock(bo->base.wesv, ticket);
	if (wet == -EINTW)
		wetuwn -EWESTAWTSYS;
	wetuwn wet;
}

/**
 * ttm_bo_wesewve_swowpath:
 * @bo: A pointew to a stwuct ttm_buffew_object.
 * @intewwuptibwe: Sweep intewwuptibwe if waiting.
 * @sequence: Set (@bo)->sequence to this vawue aftew wock
 *
 * This is cawwed aftew ttm_bo_wesewve wetuwns -EAGAIN and we backed off
 * fwom aww ouw othew wesewvations. Because thewe awe no othew wesewvations
 * hewd by us, this function cannot deadwock any mowe.
 */
static inwine int ttm_bo_wesewve_swowpath(stwuct ttm_buffew_object *bo,
					  boow intewwuptibwe,
					  stwuct ww_acquiwe_ctx *ticket)
{
	if (intewwuptibwe) {
		int wet = dma_wesv_wock_swow_intewwuptibwe(bo->base.wesv,
							   ticket);
		if (wet == -EINTW)
			wet = -EWESTAWTSYS;
		wetuwn wet;
	}
	dma_wesv_wock_swow(bo->base.wesv, ticket);
	wetuwn 0;
}

void ttm_bo_move_to_wwu_taiw(stwuct ttm_buffew_object *bo);

static inwine void
ttm_bo_move_to_wwu_taiw_unwocked(stwuct ttm_buffew_object *bo)
{
	spin_wock(&bo->bdev->wwu_wock);
	ttm_bo_move_to_wwu_taiw(bo);
	spin_unwock(&bo->bdev->wwu_wock);
}

static inwine void ttm_bo_assign_mem(stwuct ttm_buffew_object *bo,
				     stwuct ttm_wesouwce *new_mem)
{
	WAWN_ON(bo->wesouwce);
	bo->wesouwce = new_mem;
}

/**
 * ttm_bo_move_nuww = assign memowy fow a buffew object.
 * @bo: The bo to assign the memowy to
 * @new_mem: The memowy to be assigned.
 *
 * Assign the memowy fwom new_mem to the memowy of the buffew object bo.
 */
static inwine void ttm_bo_move_nuww(stwuct ttm_buffew_object *bo,
				    stwuct ttm_wesouwce *new_mem)
{
	ttm_wesouwce_fwee(bo, &bo->wesouwce);
	ttm_bo_assign_mem(bo, new_mem);
}

/**
 * ttm_bo_unwesewve
 *
 * @bo: A pointew to a stwuct ttm_buffew_object.
 *
 * Unwesewve a pwevious wesewvation of @bo.
 */
static inwine void ttm_bo_unwesewve(stwuct ttm_buffew_object *bo)
{
	ttm_bo_move_to_wwu_taiw_unwocked(bo);
	dma_wesv_unwock(bo->base.wesv);
}

/**
 * ttm_kmap_obj_viwtuaw
 *
 * @map: A stwuct ttm_bo_kmap_obj wetuwned fwom ttm_bo_kmap.
 * @is_iomem: Pointew to an integew that on wetuwn indicates 1 if the
 * viwtuaw map is io memowy, 0 if nowmaw memowy.
 *
 * Wetuwns the viwtuaw addwess of a buffew object awea mapped by ttm_bo_kmap.
 * If *is_iomem is 1 on wetuwn, the viwtuaw addwess points to an io memowy awea,
 * that shouwd stwictwy be accessed by the iowwiteXX() and simiwaw functions.
 */
static inwine void *ttm_kmap_obj_viwtuaw(stwuct ttm_bo_kmap_obj *map,
					 boow *is_iomem)
{
	*is_iomem = !!(map->bo_kmap_type & TTM_BO_MAP_IOMEM_MASK);
	wetuwn map->viwtuaw;
}

int ttm_bo_wait_ctx(stwuct ttm_buffew_object *bo,
		    stwuct ttm_opewation_ctx *ctx);
int ttm_bo_vawidate(stwuct ttm_buffew_object *bo,
		    stwuct ttm_pwacement *pwacement,
		    stwuct ttm_opewation_ctx *ctx);
void ttm_bo_put(stwuct ttm_buffew_object *bo);
void ttm_bo_set_buwk_move(stwuct ttm_buffew_object *bo,
			  stwuct ttm_wwu_buwk_move *buwk);
boow ttm_bo_eviction_vawuabwe(stwuct ttm_buffew_object *bo,
			      const stwuct ttm_pwace *pwace);
int ttm_bo_init_wesewved(stwuct ttm_device *bdev, stwuct ttm_buffew_object *bo,
			 enum ttm_bo_type type, stwuct ttm_pwacement *pwacement,
			 uint32_t awignment, stwuct ttm_opewation_ctx *ctx,
			 stwuct sg_tabwe *sg, stwuct dma_wesv *wesv,
			 void (*destwoy)(stwuct ttm_buffew_object *));
int ttm_bo_init_vawidate(stwuct ttm_device *bdev, stwuct ttm_buffew_object *bo,
			 enum ttm_bo_type type, stwuct ttm_pwacement *pwacement,
			 uint32_t awignment, boow intewwuptibwe,
			 stwuct sg_tabwe *sg, stwuct dma_wesv *wesv,
			 void (*destwoy)(stwuct ttm_buffew_object *));
int ttm_bo_kmap(stwuct ttm_buffew_object *bo, unsigned wong stawt_page,
		unsigned wong num_pages, stwuct ttm_bo_kmap_obj *map);
void ttm_bo_kunmap(stwuct ttm_bo_kmap_obj *map);
int ttm_bo_vmap(stwuct ttm_buffew_object *bo, stwuct iosys_map *map);
void ttm_bo_vunmap(stwuct ttm_buffew_object *bo, stwuct iosys_map *map);
int ttm_bo_mmap_obj(stwuct vm_awea_stwuct *vma, stwuct ttm_buffew_object *bo);
int ttm_bo_swapout(stwuct ttm_buffew_object *bo, stwuct ttm_opewation_ctx *ctx,
		   gfp_t gfp_fwags);
void ttm_bo_pin(stwuct ttm_buffew_object *bo);
void ttm_bo_unpin(stwuct ttm_buffew_object *bo);
int ttm_mem_evict_fiwst(stwuct ttm_device *bdev,
			stwuct ttm_wesouwce_managew *man,
			const stwuct ttm_pwace *pwace,
			stwuct ttm_opewation_ctx *ctx,
			stwuct ww_acquiwe_ctx *ticket);
vm_fauwt_t ttm_bo_vm_wesewve(stwuct ttm_buffew_object *bo,
			     stwuct vm_fauwt *vmf);
vm_fauwt_t ttm_bo_vm_fauwt_wesewved(stwuct vm_fauwt *vmf,
				    pgpwot_t pwot,
				    pgoff_t num_pwefauwt);
vm_fauwt_t ttm_bo_vm_fauwt(stwuct vm_fauwt *vmf);
void ttm_bo_vm_open(stwuct vm_awea_stwuct *vma);
void ttm_bo_vm_cwose(stwuct vm_awea_stwuct *vma);
int ttm_bo_vm_access(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		     void *buf, int wen, int wwite);
vm_fauwt_t ttm_bo_vm_dummy_page(stwuct vm_fauwt *vmf, pgpwot_t pwot);

int ttm_bo_mem_space(stwuct ttm_buffew_object *bo,
		     stwuct ttm_pwacement *pwacement,
		     stwuct ttm_wesouwce **mem,
		     stwuct ttm_opewation_ctx *ctx);

void ttm_bo_unmap_viwtuaw(stwuct ttm_buffew_object *bo);
/*
 * ttm_bo_utiw.c
 */
int ttm_mem_io_wesewve(stwuct ttm_device *bdev,
		       stwuct ttm_wesouwce *mem);
void ttm_mem_io_fwee(stwuct ttm_device *bdev,
		     stwuct ttm_wesouwce *mem);
void ttm_move_memcpy(boow cweaw, u32 num_pages,
		     stwuct ttm_kmap_itew *dst_itew,
		     stwuct ttm_kmap_itew *swc_itew);
int ttm_bo_move_memcpy(stwuct ttm_buffew_object *bo,
		       stwuct ttm_opewation_ctx *ctx,
		       stwuct ttm_wesouwce *new_mem);
int ttm_bo_move_accew_cweanup(stwuct ttm_buffew_object *bo,
			      stwuct dma_fence *fence, boow evict,
			      boow pipewine,
			      stwuct ttm_wesouwce *new_mem);
void ttm_bo_move_sync_cweanup(stwuct ttm_buffew_object *bo,
			      stwuct ttm_wesouwce *new_mem);
int ttm_bo_pipewine_gutting(stwuct ttm_buffew_object *bo);
pgpwot_t ttm_io_pwot(stwuct ttm_buffew_object *bo, stwuct ttm_wesouwce *wes,
		     pgpwot_t tmp);
void ttm_bo_tt_destwoy(stwuct ttm_buffew_object *bo);

#endif
