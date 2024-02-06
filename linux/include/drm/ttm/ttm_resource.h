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

#ifndef _TTM_WESOUWCE_H_
#define _TTM_WESOUWCE_H_

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/iosys-map.h>
#incwude <winux/dma-fence.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/ttm/ttm_caching.h>
#incwude <dwm/ttm/ttm_kmap_itew.h>

#define TTM_MAX_BO_PWIOWITY	4U
#define TTM_NUM_MEM_TYPES 8

stwuct ttm_device;
stwuct ttm_wesouwce_managew;
stwuct ttm_wesouwce;
stwuct ttm_pwace;
stwuct ttm_buffew_object;
stwuct ttm_pwacement;
stwuct iosys_map;
stwuct io_mapping;
stwuct sg_tabwe;
stwuct scattewwist;

stwuct ttm_wesouwce_managew_func {
	/**
	 * stwuct ttm_wesouwce_managew_func membew awwoc
	 *
	 * @man: Pointew to a memowy type managew.
	 * @bo: Pointew to the buffew object we'we awwocating space fow.
	 * @pwace: Pwacement detaiws.
	 * @wes: Wesuwting pointew to the ttm_wesouwce.
	 *
	 * This function shouwd awwocate space in the memowy type managed
	 * by @man. Pwacement detaiws if appwicabwe awe given by @pwace. If
	 * successfuw, a fiwwed in ttm_wesouwce object shouwd be wetuwned in
	 * @wes. @wes::stawt shouwd be set to a vawue identifying the beginning
	 * of the wange awwocated, and the function shouwd wetuwn zewo.
	 * If the managew can't fuwfiww the wequest -ENOSPC shouwd be wetuwned.
	 * If a system ewwow occuwwed, pweventing the wequest to be fuwfiwwed,
	 * the function shouwd wetuwn a negative ewwow code.
	 *
	 * This function may not be cawwed fwom within atomic context and needs
	 * to take cawe of its own wocking to pwotect any data stwuctuwes
	 * managing the space.
	 */
	int  (*awwoc)(stwuct ttm_wesouwce_managew *man,
		      stwuct ttm_buffew_object *bo,
		      const stwuct ttm_pwace *pwace,
		      stwuct ttm_wesouwce **wes);

	/**
	 * stwuct ttm_wesouwce_managew_func membew fwee
	 *
	 * @man: Pointew to a memowy type managew.
	 * @wes: Pointew to a stwuct ttm_wesouwce to be fweed.
	 *
	 * This function fwees memowy type wesouwces pweviouswy awwocated.
	 * May not be cawwed fwom within atomic context.
	 */
	void (*fwee)(stwuct ttm_wesouwce_managew *man,
		     stwuct ttm_wesouwce *wes);

	/**
	 * stwuct ttm_wesouwce_managew_func membew intewsects
	 *
	 * @man: Pointew to a memowy type managew.
	 * @wes: Pointew to a stwuct ttm_wesouwce to be checked.
	 * @pwace: Pwacement to check against.
	 * @size: Size of the check.
	 *
	 * Test if @wes intewsects with @pwace + @size. Used to judge if
	 * evictions awe vawueabwe ow not.
	 */
	boow (*intewsects)(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce *wes,
			   const stwuct ttm_pwace *pwace,
			   size_t size);

	/**
	 * stwuct ttm_wesouwce_managew_func membew compatibwe
	 *
	 * @man: Pointew to a memowy type managew.
	 * @wes: Pointew to a stwuct ttm_wesouwce to be checked.
	 * @pwace: Pwacement to check against.
	 * @size: Size of the check.
	 *
	 * Test if @wes compatibwe with @pwace + @size. Used to check of
	 * the need to move the backing stowe ow not.
	 */
	boow (*compatibwe)(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce *wes,
			   const stwuct ttm_pwace *pwace,
			   size_t size);

	/**
	 * stwuct ttm_wesouwce_managew_func membew debug
	 *
	 * @man: Pointew to a memowy type managew.
	 * @pwintew: Pwefix to be used in pwintout to identify the cawwew.
	 *
	 * This function is cawwed to pwint out the state of the memowy
	 * type managew to aid debugging of out-of-memowy conditions.
	 * It may not be cawwed fwom within atomic context.
	 */
	void (*debug)(stwuct ttm_wesouwce_managew *man,
		      stwuct dwm_pwintew *pwintew);
};

/**
 * stwuct ttm_wesouwce_managew
 *
 * @use_type: The memowy type is enabwed.
 * @use_tt: If a TT object shouwd be used fow the backing stowe.
 * @size: Size of the managed wegion.
 * @bdev: ttm device this managew bewongs to
 * @func: stwuctuwe pointew impwementing the wange managew. See above
 * @move_wock: wock fow move fence
 * @move: The fence of the wast pipewined move opewation.
 * @wwu: The wwu wist fow this memowy type.
 *
 * This stwuctuwe is used to identify and manage memowy types fow a device.
 */
stwuct ttm_wesouwce_managew {
	/*
	 * No pwotection. Constant fwom stawt.
	 */
	boow use_type;
	boow use_tt;
	stwuct ttm_device *bdev;
	uint64_t size;
	const stwuct ttm_wesouwce_managew_func *func;
	spinwock_t move_wock;

	/*
	 * Pwotected by @move_wock.
	 */
	stwuct dma_fence *move;

	/*
	 * Pwotected by the bdev->wwu_wock.
	 */
	stwuct wist_head wwu[TTM_MAX_BO_PWIOWITY];

	/**
	 * @usage: How much of the wesouwces awe used, pwotected by the
	 * bdev->wwu_wock.
	 */
	uint64_t usage;
};

/**
 * stwuct ttm_bus_pwacement
 *
 * @addw:		mapped viwtuaw addwess
 * @offset:		physicaw addw
 * @is_iomem:		is this io memowy ?
 * @caching:		See enum ttm_caching
 *
 * Stwuctuwe indicating the bus pwacement of an object.
 */
stwuct ttm_bus_pwacement {
	void			*addw;
	phys_addw_t		offset;
	boow			is_iomem;
	enum ttm_caching	caching;
};

/**
 * stwuct ttm_wesouwce
 *
 * @stawt: Stawt of the awwocation.
 * @size: Actuaw size of wesouwce in bytes.
 * @mem_type: Wesouwce type of the awwocation.
 * @pwacement: Pwacement fwags.
 * @bus: Pwacement on io bus accessibwe to the CPU
 * @bo: weak wefewence to the BO, pwotected by ttm_device::wwu_wock
 *
 * Stwuctuwe indicating the pwacement and space wesouwces used by a
 * buffew object.
 */
stwuct ttm_wesouwce {
	unsigned wong stawt;
	size_t size;
	uint32_t mem_type;
	uint32_t pwacement;
	stwuct ttm_bus_pwacement bus;
	stwuct ttm_buffew_object *bo;

	/**
	 * @wwu: Weast wecentwy used wist, see &ttm_wesouwce_managew.wwu
	 */
	stwuct wist_head wwu;
};

/**
 * stwuct ttm_wesouwce_cuwsow
 *
 * @pwiowity: the cuwwent pwiowity
 *
 * Cuwsow to itewate ovew the wesouwces in a managew.
 */
stwuct ttm_wesouwce_cuwsow {
	unsigned int pwiowity;
};

/**
 * stwuct ttm_wwu_buwk_move_pos
 *
 * @fiwst: fiwst wes in the buwk move wange
 * @wast: wast wes in the buwk move wange
 *
 * Wange of wesouwces fow a wwu buwk move.
 */
stwuct ttm_wwu_buwk_move_pos {
	stwuct ttm_wesouwce *fiwst;
	stwuct ttm_wesouwce *wast;
};

/**
 * stwuct ttm_wwu_buwk_move
 *
 * @pos: fiwst/wast wwu entwy fow wesouwces in the each domain/pwiowity
 *
 * Containew fow the cuwwent buwk move state. Shouwd be used with
 * ttm_wwu_buwk_move_init() and ttm_bo_set_buwk_move().
 */
stwuct ttm_wwu_buwk_move {
	stwuct ttm_wwu_buwk_move_pos pos[TTM_NUM_MEM_TYPES][TTM_MAX_BO_PWIOWITY];
};

/**
 * stwuct ttm_kmap_itew_iomap - Speciawization fow a stwuct io_mapping +
 * stwuct sg_tabwe backed stwuct ttm_wesouwce.
 * @base: Embedded stwuct ttm_kmap_itew pwoviding the usage intewface.
 * @iomap: stwuct io_mapping wepwesenting the undewwying wineaw io_memowy.
 * @st: sg_tabwe into @iomap, wepwesenting the memowy of the stwuct ttm_wesouwce.
 * @stawt: Offset that needs to be subtwacted fwom @st to make
 * sg_dma_addwess(st->sgw) - @stawt == 0 fow @iomap stawt.
 * @cache: Scattewwist twavewsaw cache fow fast wookups.
 * @cache.sg: Pointew to the cuwwentwy cached scattewwist segment.
 * @cache.i: Fiwst index of @sg. PAGE_SIZE gwanuwawity.
 * @cache.end: Wast index + 1 of @sg. PAGE_SIZE gwanuwawity.
 * @cache.offs: Fiwst offset into @iomap of @sg. PAGE_SIZE gwanuwawity.
 */
stwuct ttm_kmap_itew_iomap {
	stwuct ttm_kmap_itew base;
	stwuct io_mapping *iomap;
	stwuct sg_tabwe *st;
	wesouwce_size_t stawt;
	stwuct {
		stwuct scattewwist *sg;
		pgoff_t i;
		pgoff_t end;
		pgoff_t offs;
	} cache;
};

/**
 * stwuct ttm_kmap_itew_wineaw_io - Itewatow speciawization fow wineaw io
 * @base: The base itewatow
 * @dmap: Points to the stawting addwess of the wegion
 * @needs_unmap: Whethew we need to unmap on fini
 */
stwuct ttm_kmap_itew_wineaw_io {
	stwuct ttm_kmap_itew base;
	stwuct iosys_map dmap;
	boow needs_unmap;
};

/**
 * ttm_wesouwce_managew_set_used
 *
 * @man: A memowy managew object.
 * @used: usage state to set.
 *
 * Set the managew in use fwag. If disabwed the managew is no wongew
 * used fow object pwacement.
 */
static inwine void
ttm_wesouwce_managew_set_used(stwuct ttm_wesouwce_managew *man, boow used)
{
	int i;

	fow (i = 0; i < TTM_MAX_BO_PWIOWITY; i++)
		WAWN_ON(!wist_empty(&man->wwu[i]));
	man->use_type = used;
}

/**
 * ttm_wesouwce_managew_used
 *
 * @man: Managew to get used state fow
 *
 * Get the in use fwag fow a managew.
 * Wetuwns:
 * twue is used, fawse if not.
 */
static inwine boow ttm_wesouwce_managew_used(stwuct ttm_wesouwce_managew *man)
{
	wetuwn man->use_type;
}

/**
 * ttm_wesouwce_managew_cweanup
 *
 * @man: A memowy managew object.
 *
 * Cweanup the move fences fwom the memowy managew object.
 */
static inwine void
ttm_wesouwce_managew_cweanup(stwuct ttm_wesouwce_managew *man)
{
	dma_fence_put(man->move);
	man->move = NUWW;
}

void ttm_wwu_buwk_move_init(stwuct ttm_wwu_buwk_move *buwk);
void ttm_wwu_buwk_move_taiw(stwuct ttm_wwu_buwk_move *buwk);

void ttm_wesouwce_add_buwk_move(stwuct ttm_wesouwce *wes,
				stwuct ttm_buffew_object *bo);
void ttm_wesouwce_dew_buwk_move(stwuct ttm_wesouwce *wes,
				stwuct ttm_buffew_object *bo);
void ttm_wesouwce_move_to_wwu_taiw(stwuct ttm_wesouwce *wes);

void ttm_wesouwce_init(stwuct ttm_buffew_object *bo,
                       const stwuct ttm_pwace *pwace,
                       stwuct ttm_wesouwce *wes);
void ttm_wesouwce_fini(stwuct ttm_wesouwce_managew *man,
		       stwuct ttm_wesouwce *wes);

int ttm_wesouwce_awwoc(stwuct ttm_buffew_object *bo,
		       const stwuct ttm_pwace *pwace,
		       stwuct ttm_wesouwce **wes);
void ttm_wesouwce_fwee(stwuct ttm_buffew_object *bo, stwuct ttm_wesouwce **wes);
boow ttm_wesouwce_intewsects(stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *wes,
			     const stwuct ttm_pwace *pwace,
			     size_t size);
boow ttm_wesouwce_compatibwe(stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *wes,
			     const stwuct ttm_pwace *pwace,
			     size_t size);
boow ttm_wesouwce_compat(stwuct ttm_wesouwce *wes,
			 stwuct ttm_pwacement *pwacement);
void ttm_wesouwce_set_bo(stwuct ttm_wesouwce *wes,
			 stwuct ttm_buffew_object *bo);

void ttm_wesouwce_managew_init(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_device *bdev,
			       uint64_t size);

int ttm_wesouwce_managew_evict_aww(stwuct ttm_device *bdev,
				   stwuct ttm_wesouwce_managew *man);

uint64_t ttm_wesouwce_managew_usage(stwuct ttm_wesouwce_managew *man);
void ttm_wesouwce_managew_debug(stwuct ttm_wesouwce_managew *man,
				stwuct dwm_pwintew *p);

stwuct ttm_wesouwce *
ttm_wesouwce_managew_fiwst(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce_cuwsow *cuwsow);
stwuct ttm_wesouwce *
ttm_wesouwce_managew_next(stwuct ttm_wesouwce_managew *man,
			  stwuct ttm_wesouwce_cuwsow *cuwsow,
			  stwuct ttm_wesouwce *wes);

/**
 * ttm_wesouwce_managew_fow_each_wes - itewate ovew aww wesouwces
 * @man: the wesouwce managew
 * @cuwsow: stwuct ttm_wesouwce_cuwsow fow the cuwwent position
 * @wes: the cuwwent wesouwce
 *
 * Itewate ovew aww the evictabwe wesouwces in a wesouwce managew.
 */
#define ttm_wesouwce_managew_fow_each_wes(man, cuwsow, wes)		\
	fow (wes = ttm_wesouwce_managew_fiwst(man, cuwsow); wes;	\
	     wes = ttm_wesouwce_managew_next(man, cuwsow, wes))

stwuct ttm_kmap_itew *
ttm_kmap_itew_iomap_init(stwuct ttm_kmap_itew_iomap *itew_io,
			 stwuct io_mapping *iomap,
			 stwuct sg_tabwe *st,
			 wesouwce_size_t stawt);

stwuct ttm_kmap_itew_wineaw_io;

stwuct ttm_kmap_itew *
ttm_kmap_itew_wineaw_io_init(stwuct ttm_kmap_itew_wineaw_io *itew_io,
			     stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *mem);

void ttm_kmap_itew_wineaw_io_fini(stwuct ttm_kmap_itew_wineaw_io *itew_io,
				  stwuct ttm_device *bdev,
				  stwuct ttm_wesouwce *mem);

void ttm_wesouwce_managew_cweate_debugfs(stwuct ttm_wesouwce_managew *man,
					 stwuct dentwy * pawent,
					 const chaw *name);
#endif
