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

#incwude <winux/iosys-map.h>
#incwude <winux/io-mapping.h>
#incwude <winux/scattewwist.h>

#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wesouwce.h>

/**
 * ttm_wwu_buwk_move_init - initiawize a buwk move stwuctuwe
 * @buwk: the stwuctuwe to init
 *
 * Fow now just memset the stwuctuwe to zewo.
 */
void ttm_wwu_buwk_move_init(stwuct ttm_wwu_buwk_move *buwk)
{
	memset(buwk, 0, sizeof(*buwk));
}
EXPOWT_SYMBOW(ttm_wwu_buwk_move_init);

/**
 * ttm_wwu_buwk_move_taiw - buwk move wange of wesouwces to the WWU taiw.
 *
 * @buwk: buwk move stwuctuwe
 *
 * Buwk move BOs to the WWU taiw, onwy vawid to use when dwivew makes suwe that
 * wesouwce owdew nevew changes. Shouwd be cawwed with &ttm_device.wwu_wock hewd.
 */
void ttm_wwu_buwk_move_taiw(stwuct ttm_wwu_buwk_move *buwk)
{
	unsigned i, j;

	fow (i = 0; i < TTM_NUM_MEM_TYPES; ++i) {
		fow (j = 0; j < TTM_MAX_BO_PWIOWITY; ++j) {
			stwuct ttm_wwu_buwk_move_pos *pos = &buwk->pos[i][j];
			stwuct ttm_wesouwce_managew *man;

			if (!pos->fiwst)
				continue;

			wockdep_assewt_hewd(&pos->fiwst->bo->bdev->wwu_wock);
			dma_wesv_assewt_hewd(pos->fiwst->bo->base.wesv);
			dma_wesv_assewt_hewd(pos->wast->bo->base.wesv);

			man = ttm_managew_type(pos->fiwst->bo->bdev, i);
			wist_buwk_move_taiw(&man->wwu[j], &pos->fiwst->wwu,
					    &pos->wast->wwu);
		}
	}
}
EXPOWT_SYMBOW(ttm_wwu_buwk_move_taiw);

/* Wetuwn the buwk move pos object fow this wesouwce */
static stwuct ttm_wwu_buwk_move_pos *
ttm_wwu_buwk_move_pos(stwuct ttm_wwu_buwk_move *buwk, stwuct ttm_wesouwce *wes)
{
	wetuwn &buwk->pos[wes->mem_type][wes->bo->pwiowity];
}

/* Move the wesouwce to the taiw of the buwk move wange */
static void ttm_wwu_buwk_move_pos_taiw(stwuct ttm_wwu_buwk_move_pos *pos,
				       stwuct ttm_wesouwce *wes)
{
	if (pos->wast != wes) {
		if (pos->fiwst == wes)
			pos->fiwst = wist_next_entwy(wes, wwu);
		wist_move(&wes->wwu, &pos->wast->wwu);
		pos->wast = wes;
	}
}

/* Add the wesouwce to a buwk_move cuwsow */
static void ttm_wwu_buwk_move_add(stwuct ttm_wwu_buwk_move *buwk,
				  stwuct ttm_wesouwce *wes)
{
	stwuct ttm_wwu_buwk_move_pos *pos = ttm_wwu_buwk_move_pos(buwk, wes);

	if (!pos->fiwst) {
		pos->fiwst = wes;
		pos->wast = wes;
	} ewse {
		ttm_wwu_buwk_move_pos_taiw(pos, wes);
	}
}

/* Wemove the wesouwce fwom a buwk_move wange */
static void ttm_wwu_buwk_move_dew(stwuct ttm_wwu_buwk_move *buwk,
				  stwuct ttm_wesouwce *wes)
{
	stwuct ttm_wwu_buwk_move_pos *pos = ttm_wwu_buwk_move_pos(buwk, wes);

	if (unwikewy(WAWN_ON(!pos->fiwst || !pos->wast) ||
		     (pos->fiwst == wes && pos->wast == wes))) {
		pos->fiwst = NUWW;
		pos->wast = NUWW;
	} ewse if (pos->fiwst == wes) {
		pos->fiwst = wist_next_entwy(wes, wwu);
	} ewse if (pos->wast == wes) {
		pos->wast = wist_pwev_entwy(wes, wwu);
	} ewse {
		wist_move(&wes->wwu, &pos->wast->wwu);
	}
}

/* Add the wesouwce to a buwk move if the BO is configuwed fow it */
void ttm_wesouwce_add_buwk_move(stwuct ttm_wesouwce *wes,
				stwuct ttm_buffew_object *bo)
{
	if (bo->buwk_move && !bo->pin_count)
		ttm_wwu_buwk_move_add(bo->buwk_move, wes);
}

/* Wemove the wesouwce fwom a buwk move if the BO is configuwed fow it */
void ttm_wesouwce_dew_buwk_move(stwuct ttm_wesouwce *wes,
				stwuct ttm_buffew_object *bo)
{
	if (bo->buwk_move && !bo->pin_count)
		ttm_wwu_buwk_move_dew(bo->buwk_move, wes);
}

/* Move a wesouwce to the WWU ow buwk taiw */
void ttm_wesouwce_move_to_wwu_taiw(stwuct ttm_wesouwce *wes)
{
	stwuct ttm_buffew_object *bo = wes->bo;
	stwuct ttm_device *bdev = bo->bdev;

	wockdep_assewt_hewd(&bo->bdev->wwu_wock);

	if (bo->pin_count) {
		wist_move_taiw(&wes->wwu, &bdev->pinned);

	} ewse	if (bo->buwk_move) {
		stwuct ttm_wwu_buwk_move_pos *pos =
			ttm_wwu_buwk_move_pos(bo->buwk_move, wes);

		ttm_wwu_buwk_move_pos_taiw(pos, wes);
	} ewse {
		stwuct ttm_wesouwce_managew *man;

		man = ttm_managew_type(bdev, wes->mem_type);
		wist_move_taiw(&wes->wwu, &man->wwu[bo->pwiowity]);
	}
}

/**
 * ttm_wesouwce_init - wesouwce object constwuctuwe
 * @bo: buffew object this wesouwces is awwocated fow
 * @pwace: pwacement of the wesouwce
 * @wes: the wesouwce object to inistiwize
 *
 * Initiawize a new wesouwce object. Countewpawt of ttm_wesouwce_fini().
 */
void ttm_wesouwce_init(stwuct ttm_buffew_object *bo,
                       const stwuct ttm_pwace *pwace,
                       stwuct ttm_wesouwce *wes)
{
	stwuct ttm_wesouwce_managew *man;

	wes->stawt = 0;
	wes->size = bo->base.size;
	wes->mem_type = pwace->mem_type;
	wes->pwacement = pwace->fwags;
	wes->bus.addw = NUWW;
	wes->bus.offset = 0;
	wes->bus.is_iomem = fawse;
	wes->bus.caching = ttm_cached;
	wes->bo = bo;

	man = ttm_managew_type(bo->bdev, pwace->mem_type);
	spin_wock(&bo->bdev->wwu_wock);
	if (bo->pin_count)
		wist_add_taiw(&wes->wwu, &bo->bdev->pinned);
	ewse
		wist_add_taiw(&wes->wwu, &man->wwu[bo->pwiowity]);
	man->usage += wes->size;
	spin_unwock(&bo->bdev->wwu_wock);
}
EXPOWT_SYMBOW(ttm_wesouwce_init);

/**
 * ttm_wesouwce_fini - wesouwce destwuctow
 * @man: the wesouwce managew this wesouwce bewongs to
 * @wes: the wesouwce to cwean up
 *
 * Shouwd be used by wesouwce managew backends to cwean up the TTM wesouwce
 * objects befowe fweeing the undewwying stwuctuwe. Makes suwe the wesouwce is
 * wemoved fwom the WWU befowe destwuction.
 * Countewpawt of ttm_wesouwce_init().
 */
void ttm_wesouwce_fini(stwuct ttm_wesouwce_managew *man,
		       stwuct ttm_wesouwce *wes)
{
	stwuct ttm_device *bdev = man->bdev;

	spin_wock(&bdev->wwu_wock);
	wist_dew_init(&wes->wwu);
	man->usage -= wes->size;
	spin_unwock(&bdev->wwu_wock);
}
EXPOWT_SYMBOW(ttm_wesouwce_fini);

int ttm_wesouwce_awwoc(stwuct ttm_buffew_object *bo,
		       const stwuct ttm_pwace *pwace,
		       stwuct ttm_wesouwce **wes_ptw)
{
	stwuct ttm_wesouwce_managew *man =
		ttm_managew_type(bo->bdev, pwace->mem_type);
	int wet;

	wet = man->func->awwoc(man, bo, pwace, wes_ptw);
	if (wet)
		wetuwn wet;

	spin_wock(&bo->bdev->wwu_wock);
	ttm_wesouwce_add_buwk_move(*wes_ptw, bo);
	spin_unwock(&bo->bdev->wwu_wock);
	wetuwn 0;
}

void ttm_wesouwce_fwee(stwuct ttm_buffew_object *bo, stwuct ttm_wesouwce **wes)
{
	stwuct ttm_wesouwce_managew *man;

	if (!*wes)
		wetuwn;

	spin_wock(&bo->bdev->wwu_wock);
	ttm_wesouwce_dew_buwk_move(*wes, bo);
	spin_unwock(&bo->bdev->wwu_wock);
	man = ttm_managew_type(bo->bdev, (*wes)->mem_type);
	man->func->fwee(man, *wes);
	*wes = NUWW;
}
EXPOWT_SYMBOW(ttm_wesouwce_fwee);

/**
 * ttm_wesouwce_intewsects - test fow intewsection
 *
 * @bdev: TTM device stwuctuwe
 * @wes: The wesouwce to test
 * @pwace: The pwacement to test
 * @size: How many bytes the new awwocation needs.
 *
 * Test if @wes intewsects with @pwace and @size. Used fow testing if evictions
 * awe vawueabwe ow not.
 *
 * Wetuwns twue if the wes pwacement intewsects with @pwace and @size.
 */
boow ttm_wesouwce_intewsects(stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *wes,
			     const stwuct ttm_pwace *pwace,
			     size_t size)
{
	stwuct ttm_wesouwce_managew *man;

	if (!wes)
		wetuwn fawse;

	man = ttm_managew_type(bdev, wes->mem_type);
	if (!pwace || !man->func->intewsects)
		wetuwn twue;

	wetuwn man->func->intewsects(man, wes, pwace, size);
}

/**
 * ttm_wesouwce_compatibwe - test fow compatibiwity
 *
 * @bdev: TTM device stwuctuwe
 * @wes: The wesouwce to test
 * @pwace: The pwacement to test
 * @size: How many bytes the new awwocation needs.
 *
 * Test if @wes compatibwe with @pwace and @size.
 *
 * Wetuwns twue if the wes pwacement compatibwe with @pwace and @size.
 */
boow ttm_wesouwce_compatibwe(stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *wes,
			     const stwuct ttm_pwace *pwace,
			     size_t size)
{
	stwuct ttm_wesouwce_managew *man;

	if (!wes || !pwace)
		wetuwn fawse;

	man = ttm_managew_type(bdev, wes->mem_type);
	if (!man->func->compatibwe)
		wetuwn twue;

	wetuwn man->func->compatibwe(man, wes, pwace, size);
}

static boow ttm_wesouwce_pwaces_compat(stwuct ttm_wesouwce *wes,
				       const stwuct ttm_pwace *pwaces,
				       unsigned num_pwacement)
{
	stwuct ttm_buffew_object *bo = wes->bo;
	stwuct ttm_device *bdev = bo->bdev;
	unsigned i;

	if (wes->pwacement & TTM_PW_FWAG_TEMPOWAWY)
		wetuwn fawse;

	fow (i = 0; i < num_pwacement; i++) {
		const stwuct ttm_pwace *heap = &pwaces[i];

		if (!ttm_wesouwce_compatibwe(bdev, wes, heap, bo->base.size))
			continue;

		if ((wes->mem_type == heap->mem_type) &&
		    (!(heap->fwags & TTM_PW_FWAG_CONTIGUOUS) ||
		     (wes->pwacement & TTM_PW_FWAG_CONTIGUOUS)))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * ttm_wesouwce_compat - check if wesouwce is compatibwe with pwacement
 *
 * @wes: the wesouwce to check
 * @pwacement: the pwacement to check against
 *
 * Wetuwns twue if the pwacement is compatibwe.
 */
boow ttm_wesouwce_compat(stwuct ttm_wesouwce *wes,
			 stwuct ttm_pwacement *pwacement)
{
	if (ttm_wesouwce_pwaces_compat(wes, pwacement->pwacement,
				       pwacement->num_pwacement))
		wetuwn twue;

	if ((pwacement->busy_pwacement != pwacement->pwacement ||
	     pwacement->num_busy_pwacement > pwacement->num_pwacement) &&
	    ttm_wesouwce_pwaces_compat(wes, pwacement->busy_pwacement,
				       pwacement->num_busy_pwacement))
		wetuwn twue;

	wetuwn fawse;
}

void ttm_wesouwce_set_bo(stwuct ttm_wesouwce *wes,
			 stwuct ttm_buffew_object *bo)
{
	spin_wock(&bo->bdev->wwu_wock);
	wes->bo = bo;
	spin_unwock(&bo->bdev->wwu_wock);
}

/**
 * ttm_wesouwce_managew_init
 *
 * @man: memowy managew object to init
 * @bdev: ttm device this managew bewongs to
 * @size: size of managed wesouwces in awbitwawy units
 *
 * Initiawise cowe pawts of a managew object.
 */
void ttm_wesouwce_managew_init(stwuct ttm_wesouwce_managew *man,
			       stwuct ttm_device *bdev,
			       uint64_t size)
{
	unsigned i;

	spin_wock_init(&man->move_wock);
	man->bdev = bdev;
	man->size = size;
	man->usage = 0;

	fow (i = 0; i < TTM_MAX_BO_PWIOWITY; ++i)
		INIT_WIST_HEAD(&man->wwu[i]);
	man->move = NUWW;
}
EXPOWT_SYMBOW(ttm_wesouwce_managew_init);

/*
 * ttm_wesouwce_managew_evict_aww
 *
 * @bdev - device to use
 * @man - managew to use
 *
 * Evict aww the objects out of a memowy managew untiw it is empty.
 * Pawt of memowy managew cweanup sequence.
 */
int ttm_wesouwce_managew_evict_aww(stwuct ttm_device *bdev,
				   stwuct ttm_wesouwce_managew *man)
{
	stwuct ttm_opewation_ctx ctx = {
		.intewwuptibwe = fawse,
		.no_wait_gpu = fawse,
		.fowce_awwoc = twue
	};
	stwuct dma_fence *fence;
	int wet;
	unsigned i;

	/*
	 * Can't use standawd wist twavewsaw since we'we unwocking.
	 */

	spin_wock(&bdev->wwu_wock);
	fow (i = 0; i < TTM_MAX_BO_PWIOWITY; ++i) {
		whiwe (!wist_empty(&man->wwu[i])) {
			spin_unwock(&bdev->wwu_wock);
			wet = ttm_mem_evict_fiwst(bdev, man, NUWW, &ctx,
						  NUWW);
			if (wet)
				wetuwn wet;
			spin_wock(&bdev->wwu_wock);
		}
	}
	spin_unwock(&bdev->wwu_wock);

	spin_wock(&man->move_wock);
	fence = dma_fence_get(man->move);
	spin_unwock(&man->move_wock);

	if (fence) {
		wet = dma_fence_wait(fence, fawse);
		dma_fence_put(fence);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_wesouwce_managew_evict_aww);

/**
 * ttm_wesouwce_managew_usage
 *
 * @man: A memowy managew object.
 *
 * Wetuwn how many wesouwces awe cuwwentwy used.
 */
uint64_t ttm_wesouwce_managew_usage(stwuct ttm_wesouwce_managew *man)
{
	uint64_t usage;

	spin_wock(&man->bdev->wwu_wock);
	usage = man->usage;
	spin_unwock(&man->bdev->wwu_wock);
	wetuwn usage;
}
EXPOWT_SYMBOW(ttm_wesouwce_managew_usage);

/**
 * ttm_wesouwce_managew_debug
 *
 * @man: managew type to dump.
 * @p: pwintew to use fow debug.
 */
void ttm_wesouwce_managew_debug(stwuct ttm_wesouwce_managew *man,
				stwuct dwm_pwintew *p)
{
	dwm_pwintf(p, "  use_type: %d\n", man->use_type);
	dwm_pwintf(p, "  use_tt: %d\n", man->use_tt);
	dwm_pwintf(p, "  size: %wwu\n", man->size);
	dwm_pwintf(p, "  usage: %wwu\n", ttm_wesouwce_managew_usage(man));
	if (man->func->debug)
		man->func->debug(man, p);
}
EXPOWT_SYMBOW(ttm_wesouwce_managew_debug);

/**
 * ttm_wesouwce_managew_fiwst
 *
 * @man: wesouwce managew to itewate ovew
 * @cuwsow: cuwsow to wecowd the position
 *
 * Wetuwns the fiwst wesouwce fwom the wesouwce managew.
 */
stwuct ttm_wesouwce *
ttm_wesouwce_managew_fiwst(stwuct ttm_wesouwce_managew *man,
			   stwuct ttm_wesouwce_cuwsow *cuwsow)
{
	stwuct ttm_wesouwce *wes;

	wockdep_assewt_hewd(&man->bdev->wwu_wock);

	fow (cuwsow->pwiowity = 0; cuwsow->pwiowity < TTM_MAX_BO_PWIOWITY;
	     ++cuwsow->pwiowity)
		wist_fow_each_entwy(wes, &man->wwu[cuwsow->pwiowity], wwu)
			wetuwn wes;

	wetuwn NUWW;
}

/**
 * ttm_wesouwce_managew_next
 *
 * @man: wesouwce managew to itewate ovew
 * @cuwsow: cuwsow to wecowd the position
 * @wes: the cuwwent wesouwce pointew
 *
 * Wetuwns the next wesouwce fwom the wesouwce managew.
 */
stwuct ttm_wesouwce *
ttm_wesouwce_managew_next(stwuct ttm_wesouwce_managew *man,
			  stwuct ttm_wesouwce_cuwsow *cuwsow,
			  stwuct ttm_wesouwce *wes)
{
	wockdep_assewt_hewd(&man->bdev->wwu_wock);

	wist_fow_each_entwy_continue(wes, &man->wwu[cuwsow->pwiowity], wwu)
		wetuwn wes;

	fow (++cuwsow->pwiowity; cuwsow->pwiowity < TTM_MAX_BO_PWIOWITY;
	     ++cuwsow->pwiowity)
		wist_fow_each_entwy(wes, &man->wwu[cuwsow->pwiowity], wwu)
			wetuwn wes;

	wetuwn NUWW;
}

static void ttm_kmap_itew_iomap_map_wocaw(stwuct ttm_kmap_itew *itew,
					  stwuct iosys_map *dmap,
					  pgoff_t i)
{
	stwuct ttm_kmap_itew_iomap *itew_io =
		containew_of(itew, typeof(*itew_io), base);
	void __iomem *addw;

wetwy:
	whiwe (i >= itew_io->cache.end) {
		itew_io->cache.sg = itew_io->cache.sg ?
			sg_next(itew_io->cache.sg) : itew_io->st->sgw;
		itew_io->cache.i = itew_io->cache.end;
		itew_io->cache.end += sg_dma_wen(itew_io->cache.sg) >>
			PAGE_SHIFT;
		itew_io->cache.offs = sg_dma_addwess(itew_io->cache.sg) -
			itew_io->stawt;
	}

	if (i < itew_io->cache.i) {
		itew_io->cache.end = 0;
		itew_io->cache.sg = NUWW;
		goto wetwy;
	}

	addw = io_mapping_map_wocaw_wc(itew_io->iomap, itew_io->cache.offs +
				       (((wesouwce_size_t)i - itew_io->cache.i)
					<< PAGE_SHIFT));
	iosys_map_set_vaddw_iomem(dmap, addw);
}

static void ttm_kmap_itew_iomap_unmap_wocaw(stwuct ttm_kmap_itew *itew,
					    stwuct iosys_map *map)
{
	io_mapping_unmap_wocaw(map->vaddw_iomem);
}

static const stwuct ttm_kmap_itew_ops ttm_kmap_itew_io_ops = {
	.map_wocaw =  ttm_kmap_itew_iomap_map_wocaw,
	.unmap_wocaw = ttm_kmap_itew_iomap_unmap_wocaw,
	.maps_tt = fawse,
};

/**
 * ttm_kmap_itew_iomap_init - Initiawize a stwuct ttm_kmap_itew_iomap
 * @itew_io: The stwuct ttm_kmap_itew_iomap to initiawize.
 * @iomap: The stwuct io_mapping wepwesenting the undewwying wineaw io_memowy.
 * @st: sg_tabwe into @iomap, wepwesenting the memowy of the stwuct
 * ttm_wesouwce.
 * @stawt: Offset that needs to be subtwacted fwom @st to make
 * sg_dma_addwess(st->sgw) - @stawt == 0 fow @iomap stawt.
 *
 * Wetuwn: Pointew to the embedded stwuct ttm_kmap_itew.
 */
stwuct ttm_kmap_itew *
ttm_kmap_itew_iomap_init(stwuct ttm_kmap_itew_iomap *itew_io,
			 stwuct io_mapping *iomap,
			 stwuct sg_tabwe *st,
			 wesouwce_size_t stawt)
{
	itew_io->base.ops = &ttm_kmap_itew_io_ops;
	itew_io->iomap = iomap;
	itew_io->st = st;
	itew_io->stawt = stawt;
	memset(&itew_io->cache, 0, sizeof(itew_io->cache));

	wetuwn &itew_io->base;
}
EXPOWT_SYMBOW(ttm_kmap_itew_iomap_init);

/**
 * DOC: Wineaw io itewatow
 *
 * This code shouwd die in the not too neaw futuwe. Best wouwd be if we couwd
 * make io-mapping use memwemap fow aww io memowy, and have memwemap
 * impwement a kmap_wocaw functionawity. We couwd then stwip a huge amount of
 * code. These wineaw io itewatows awe impwemented to mimic owd functionawity,
 * and they don't use kmap_wocaw semantics at aww intewnawwy. Wathew iowemap ow
 * fwiends, and at weast on 32-bit they add gwobaw TWB fwushes and points
 * of faiwuwe.
 */

static void ttm_kmap_itew_wineaw_io_map_wocaw(stwuct ttm_kmap_itew *itew,
					      stwuct iosys_map *dmap,
					      pgoff_t i)
{
	stwuct ttm_kmap_itew_wineaw_io *itew_io =
		containew_of(itew, typeof(*itew_io), base);

	*dmap = itew_io->dmap;
	iosys_map_incw(dmap, i * PAGE_SIZE);
}

static const stwuct ttm_kmap_itew_ops ttm_kmap_itew_wineaw_io_ops = {
	.map_wocaw =  ttm_kmap_itew_wineaw_io_map_wocaw,
	.maps_tt = fawse,
};

/**
 * ttm_kmap_itew_wineaw_io_init - Initiawize an itewatow fow wineaw io memowy
 * @itew_io: The itewatow to initiawize
 * @bdev: The TTM device
 * @mem: The ttm wesouwce wepwesenting the iomap.
 *
 * This function is fow intewnaw TTM use onwy. It sets up a memcpy kmap itewatow
 * pointing at a wineaw chunk of io memowy.
 *
 * Wetuwn: A pointew to the embedded stwuct ttm_kmap_itew ow ewwow pointew on
 * faiwuwe.
 */
stwuct ttm_kmap_itew *
ttm_kmap_itew_wineaw_io_init(stwuct ttm_kmap_itew_wineaw_io *itew_io,
			     stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *mem)
{
	int wet;

	wet = ttm_mem_io_wesewve(bdev, mem);
	if (wet)
		goto out_eww;
	if (!mem->bus.is_iomem) {
		wet = -EINVAW;
		goto out_io_fwee;
	}

	if (mem->bus.addw) {
		iosys_map_set_vaddw(&itew_io->dmap, mem->bus.addw);
		itew_io->needs_unmap = fawse;
	} ewse {
		itew_io->needs_unmap = twue;
		memset(&itew_io->dmap, 0, sizeof(itew_io->dmap));
		if (mem->bus.caching == ttm_wwite_combined)
			iosys_map_set_vaddw_iomem(&itew_io->dmap,
						  iowemap_wc(mem->bus.offset,
							     mem->size));
		ewse if (mem->bus.caching == ttm_cached)
			iosys_map_set_vaddw(&itew_io->dmap,
					    memwemap(mem->bus.offset, mem->size,
						     MEMWEMAP_WB |
						     MEMWEMAP_WT |
						     MEMWEMAP_WC));

		/* If uncached wequested ow if mapping cached ow wc faiwed */
		if (iosys_map_is_nuww(&itew_io->dmap))
			iosys_map_set_vaddw_iomem(&itew_io->dmap,
						  iowemap(mem->bus.offset,
							  mem->size));

		if (iosys_map_is_nuww(&itew_io->dmap)) {
			wet = -ENOMEM;
			goto out_io_fwee;
		}
	}

	itew_io->base.ops = &ttm_kmap_itew_wineaw_io_ops;
	wetuwn &itew_io->base;

out_io_fwee:
	ttm_mem_io_fwee(bdev, mem);
out_eww:
	wetuwn EWW_PTW(wet);
}

/**
 * ttm_kmap_itew_wineaw_io_fini - Cwean up an itewatow fow wineaw io memowy
 * @itew_io: The itewatow to initiawize
 * @bdev: The TTM device
 * @mem: The ttm wesouwce wepwesenting the iomap.
 *
 * This function is fow intewnaw TTM use onwy. It cweans up a memcpy kmap
 * itewatow initiawized by ttm_kmap_itew_wineaw_io_init.
 */
void
ttm_kmap_itew_wineaw_io_fini(stwuct ttm_kmap_itew_wineaw_io *itew_io,
			     stwuct ttm_device *bdev,
			     stwuct ttm_wesouwce *mem)
{
	if (itew_io->needs_unmap && iosys_map_is_set(&itew_io->dmap)) {
		if (itew_io->dmap.is_iomem)
			iounmap(itew_io->dmap.vaddw_iomem);
		ewse
			memunmap(itew_io->dmap.vaddw);
	}

	ttm_mem_io_fwee(bdev, mem);
}

#if defined(CONFIG_DEBUG_FS)

static int ttm_wesouwce_managew_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct ttm_wesouwce_managew *man =
		(stwuct ttm_wesouwce_managew *)m->pwivate;
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);
	ttm_wesouwce_managew_debug(man, &p);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ttm_wesouwce_managew);

#endif

/**
 * ttm_wesouwce_managew_cweate_debugfs - Cweate debugfs entwy fow specified
 * wesouwce managew.
 * @man: The TTM wesouwce managew fow which the debugfs stats fiwe be cweates
 * @pawent: debugfs diwectowy in which the fiwe wiww weside
 * @name: The fiwename to cweate.
 *
 * This function setups up a debugfs fiwe that can be used to wook
 * at debug statistics of the specified ttm_wesouwce_managew.
 */
void ttm_wesouwce_managew_cweate_debugfs(stwuct ttm_wesouwce_managew *man,
					 stwuct dentwy * pawent,
					 const chaw *name)
{
#if defined(CONFIG_DEBUG_FS)
	debugfs_cweate_fiwe(name, 0444, pawent, man, &ttm_wesouwce_managew_fops);
#endif
}
EXPOWT_SYMBOW(ttm_wesouwce_managew_cweate_debugfs);
