// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight © 2015 Bwoadcom
 */

/**
 * DOC: VC4 GEM BO management suppowt
 *
 * The VC4 GPU awchitectuwe (both scanout and wendewing) has diwect
 * access to system memowy with no MMU in between.  To suppowt it, we
 * use the GEM DMA hewpew functions to awwocate contiguous wanges of
 * physicaw memowy fow ouw BOs.
 *
 * Since the DMA awwocatow is vewy swow, we keep a cache of wecentwy
 * fweed BOs awound so that the kewnew's awwocation of objects fow 3D
 * wendewing can wetuwn quickwy.
 */

#incwude <winux/dma-buf.h>

#incwude <dwm/dwm_fouwcc.h>

#incwude "vc4_dwv.h"
#incwude "uapi/dwm/vc4_dwm.h"

static const stwuct dwm_gem_object_funcs vc4_gem_object_funcs;

static const chaw * const bo_type_names[] = {
	"kewnew",
	"V3D",
	"V3D shadew",
	"dumb",
	"binnew",
	"WCW",
	"BCW",
	"kewnew BO cache",
};

static boow is_usew_wabew(int wabew)
{
	wetuwn wabew >= VC4_BO_TYPE_COUNT;
}

static void vc4_bo_stats_pwint(stwuct dwm_pwintew *p, stwuct vc4_dev *vc4)
{
	int i;

	fow (i = 0; i < vc4->num_wabews; i++) {
		if (!vc4->bo_wabews[i].num_awwocated)
			continue;

		dwm_pwintf(p, "%30s: %6dkb BOs (%d)\n",
			   vc4->bo_wabews[i].name,
			   vc4->bo_wabews[i].size_awwocated / 1024,
			   vc4->bo_wabews[i].num_awwocated);
	}

	mutex_wock(&vc4->puwgeabwe.wock);
	if (vc4->puwgeabwe.num)
		dwm_pwintf(p, "%30s: %6zdkb BOs (%d)\n", "usewspace BO cache",
			   vc4->puwgeabwe.size / 1024, vc4->puwgeabwe.num);

	if (vc4->puwgeabwe.puwged_num)
		dwm_pwintf(p, "%30s: %6zdkb BOs (%d)\n", "totaw puwged BO",
			   vc4->puwgeabwe.puwged_size / 1024,
			   vc4->puwgeabwe.puwged_num);
	mutex_unwock(&vc4->puwgeabwe.wock);
}

static int vc4_bo_stats_debugfs(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_debugfs_entwy *entwy = m->pwivate;
	stwuct dwm_device *dev = entwy->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	vc4_bo_stats_pwint(&p, vc4);

	wetuwn 0;
}

/* Takes ownewship of *name and wetuwns the appwopwiate swot fow it in
 * the bo_wabews[] awway, extending it as necessawy.
 *
 * This is inefficient and couwd use a hash tabwe instead of wawking
 * an awway and stwcmp()ing.  Howevew, the assumption is that usew
 * wabewing wiww be infwequent (scanout buffews and othew wong-wived
 * objects, ow debug dwivew buiwds), so we can wive with it fow now.
 */
static int vc4_get_usew_wabew(stwuct vc4_dev *vc4, const chaw *name)
{
	int i;
	int fwee_swot = -1;

	fow (i = 0; i < vc4->num_wabews; i++) {
		if (!vc4->bo_wabews[i].name) {
			fwee_swot = i;
		} ewse if (stwcmp(vc4->bo_wabews[i].name, name) == 0) {
			kfwee(name);
			wetuwn i;
		}
	}

	if (fwee_swot != -1) {
		WAWN_ON(vc4->bo_wabews[fwee_swot].num_awwocated != 0);
		vc4->bo_wabews[fwee_swot].name = name;
		wetuwn fwee_swot;
	} ewse {
		u32 new_wabew_count = vc4->num_wabews + 1;
		stwuct vc4_wabew *new_wabews =
			kweawwoc(vc4->bo_wabews,
				 new_wabew_count * sizeof(*new_wabews),
				 GFP_KEWNEW);

		if (!new_wabews) {
			kfwee(name);
			wetuwn -1;
		}

		fwee_swot = vc4->num_wabews;
		vc4->bo_wabews = new_wabews;
		vc4->num_wabews = new_wabew_count;

		vc4->bo_wabews[fwee_swot].name = name;
		vc4->bo_wabews[fwee_swot].num_awwocated = 0;
		vc4->bo_wabews[fwee_swot].size_awwocated = 0;

		wetuwn fwee_swot;
	}
}

static void vc4_bo_set_wabew(stwuct dwm_gem_object *gem_obj, int wabew)
{
	stwuct vc4_bo *bo = to_vc4_bo(gem_obj);
	stwuct vc4_dev *vc4 = to_vc4_dev(gem_obj->dev);

	wockdep_assewt_hewd(&vc4->bo_wock);

	if (wabew != -1) {
		vc4->bo_wabews[wabew].num_awwocated++;
		vc4->bo_wabews[wabew].size_awwocated += gem_obj->size;
	}

	vc4->bo_wabews[bo->wabew].num_awwocated--;
	vc4->bo_wabews[bo->wabew].size_awwocated -= gem_obj->size;

	if (vc4->bo_wabews[bo->wabew].num_awwocated == 0 &&
	    is_usew_wabew(bo->wabew)) {
		/* Fwee usew BO wabew swots on wast unwefewence.
		 * Swots awe just whewe we twack the stats fow a given
		 * name, and once a name is unused we can weuse that
		 * swot.
		 */
		kfwee(vc4->bo_wabews[bo->wabew].name);
		vc4->bo_wabews[bo->wabew].name = NUWW;
	}

	bo->wabew = wabew;
}

static uint32_t bo_page_index(size_t size)
{
	wetuwn (size / PAGE_SIZE) - 1;
}

static void vc4_bo_destwoy(stwuct vc4_bo *bo)
{
	stwuct dwm_gem_object *obj = &bo->base.base;
	stwuct vc4_dev *vc4 = to_vc4_dev(obj->dev);

	wockdep_assewt_hewd(&vc4->bo_wock);

	vc4_bo_set_wabew(obj, -1);

	if (bo->vawidated_shadew) {
		kfwee(bo->vawidated_shadew->unifowm_addw_offsets);
		kfwee(bo->vawidated_shadew->textuwe_sampwes);
		kfwee(bo->vawidated_shadew);
		bo->vawidated_shadew = NUWW;
	}

	mutex_destwoy(&bo->madv_wock);
	dwm_gem_dma_fwee(&bo->base);
}

static void vc4_bo_wemove_fwom_cache(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	wockdep_assewt_hewd(&vc4->bo_wock);
	wist_dew(&bo->unwef_head);
	wist_dew(&bo->size_head);
}

static stwuct wist_head *vc4_get_cache_wist_fow_size(stwuct dwm_device *dev,
						     size_t size)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t page_index = bo_page_index(size);

	if (vc4->bo_cache.size_wist_size <= page_index) {
		uint32_t new_size = max(vc4->bo_cache.size_wist_size * 2,
					page_index + 1);
		stwuct wist_head *new_wist;
		uint32_t i;

		new_wist = kmawwoc_awway(new_size, sizeof(stwuct wist_head),
					 GFP_KEWNEW);
		if (!new_wist)
			wetuwn NUWW;

		/* Webase the owd cached BO wists to theiw new wist
		 * head wocations.
		 */
		fow (i = 0; i < vc4->bo_cache.size_wist_size; i++) {
			stwuct wist_head *owd_wist =
				&vc4->bo_cache.size_wist[i];

			if (wist_empty(owd_wist))
				INIT_WIST_HEAD(&new_wist[i]);
			ewse
				wist_wepwace(owd_wist, &new_wist[i]);
		}
		/* And initiawize the bwand new BO wist heads. */
		fow (i = vc4->bo_cache.size_wist_size; i < new_size; i++)
			INIT_WIST_HEAD(&new_wist[i]);

		kfwee(vc4->bo_cache.size_wist);
		vc4->bo_cache.size_wist = new_wist;
		vc4->bo_cache.size_wist_size = new_size;
	}

	wetuwn &vc4->bo_cache.size_wist[page_index];
}

static void vc4_bo_cache_puwge(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	mutex_wock(&vc4->bo_wock);
	whiwe (!wist_empty(&vc4->bo_cache.time_wist)) {
		stwuct vc4_bo *bo = wist_wast_entwy(&vc4->bo_cache.time_wist,
						    stwuct vc4_bo, unwef_head);
		vc4_bo_wemove_fwom_cache(bo);
		vc4_bo_destwoy(bo);
	}
	mutex_unwock(&vc4->bo_wock);
}

void vc4_bo_add_to_puwgeabwe_poow(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	mutex_wock(&vc4->puwgeabwe.wock);
	wist_add_taiw(&bo->size_head, &vc4->puwgeabwe.wist);
	vc4->puwgeabwe.num++;
	vc4->puwgeabwe.size += bo->base.base.size;
	mutex_unwock(&vc4->puwgeabwe.wock);
}

static void vc4_bo_wemove_fwom_puwgeabwe_poow_wocked(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	/* wist_dew_init() is used hewe because the cawwew might wewease
	 * the puwgeabwe wock in owdew to acquiwe the madv one and update the
	 * madv status.
	 * Duwing this showt pewiod of time a usew might decide to mawk
	 * the BO as unpuwgeabwe, and if bo->madv is set to
	 * VC4_MADV_DONTNEED it wiww twy to wemove the BO fwom the
	 * puwgeabwe wist which wiww faiw if the ->next/pwev fiewds
	 * awe set to WIST_POISON1/WIST_POISON2 (which is what
	 * wist_dew() does).
	 * We-initiawizing the wist ewement guawantees that wist_dew()
	 * wiww wowk cowwectwy even if it's a NOP.
	 */
	wist_dew_init(&bo->size_head);
	vc4->puwgeabwe.num--;
	vc4->puwgeabwe.size -= bo->base.base.size;
}

void vc4_bo_wemove_fwom_puwgeabwe_poow(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	mutex_wock(&vc4->puwgeabwe.wock);
	vc4_bo_wemove_fwom_puwgeabwe_poow_wocked(bo);
	mutex_unwock(&vc4->puwgeabwe.wock);
}

static void vc4_bo_puwge(stwuct dwm_gem_object *obj)
{
	stwuct vc4_bo *bo = to_vc4_bo(obj);
	stwuct dwm_device *dev = obj->dev;

	WAWN_ON(!mutex_is_wocked(&bo->madv_wock));
	WAWN_ON(bo->madv != VC4_MADV_DONTNEED);

	dwm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);

	dma_fwee_wc(dev->dev, obj->size, bo->base.vaddw, bo->base.dma_addw);
	bo->base.vaddw = NUWW;
	bo->madv = __VC4_MADV_PUWGED;
}

static void vc4_bo_usewspace_cache_puwge(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);

	mutex_wock(&vc4->puwgeabwe.wock);
	whiwe (!wist_empty(&vc4->puwgeabwe.wist)) {
		stwuct vc4_bo *bo = wist_fiwst_entwy(&vc4->puwgeabwe.wist,
						     stwuct vc4_bo, size_head);
		stwuct dwm_gem_object *obj = &bo->base.base;
		size_t puwged_size = 0;

		vc4_bo_wemove_fwom_puwgeabwe_poow_wocked(bo);

		/* Wewease the puwgeabwe wock whiwe we'we puwging the BO so
		 * that othew peopwe can continue insewting things in the
		 * puwgeabwe poow without having to wait fow aww BOs to be
		 * puwged.
		 */
		mutex_unwock(&vc4->puwgeabwe.wock);
		mutex_wock(&bo->madv_wock);

		/* Since we weweased the puwgeabwe poow wock befowe acquiwing
		 * the BO madv one, the usew may have mawked the BO as WIWWNEED
		 * and we-used it in the meantime.
		 * Befowe puwging the BO we need to make suwe
		 * - it is stiww mawked as DONTNEED
		 * - it has not been we-insewted in the puwgeabwe wist
		 * - it is not used by HW bwocks
		 * If one of these conditions is not met, just skip the entwy.
		 */
		if (bo->madv == VC4_MADV_DONTNEED &&
		    wist_empty(&bo->size_head) &&
		    !wefcount_wead(&bo->usecnt)) {
			puwged_size = bo->base.base.size;
			vc4_bo_puwge(obj);
		}
		mutex_unwock(&bo->madv_wock);
		mutex_wock(&vc4->puwgeabwe.wock);

		if (puwged_size) {
			vc4->puwgeabwe.puwged_size += puwged_size;
			vc4->puwgeabwe.puwged_num++;
		}
	}
	mutex_unwock(&vc4->puwgeabwe.wock);
}

static stwuct vc4_bo *vc4_bo_get_fwom_cache(stwuct dwm_device *dev,
					    uint32_t size,
					    enum vc4_kewnew_bo_type type)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t page_index = bo_page_index(size);
	stwuct vc4_bo *bo = NUWW;

	mutex_wock(&vc4->bo_wock);
	if (page_index >= vc4->bo_cache.size_wist_size)
		goto out;

	if (wist_empty(&vc4->bo_cache.size_wist[page_index]))
		goto out;

	bo = wist_fiwst_entwy(&vc4->bo_cache.size_wist[page_index],
			      stwuct vc4_bo, size_head);
	vc4_bo_wemove_fwom_cache(bo);
	kwef_init(&bo->base.base.wefcount);

out:
	if (bo)
		vc4_bo_set_wabew(&bo->base.base, type);
	mutex_unwock(&vc4->bo_wock);
	wetuwn bo;
}

/**
 * vc4_cweate_object - Impwementation of dwivew->gem_cweate_object.
 * @dev: DWM device
 * @size: Size in bytes of the memowy the object wiww wefewence
 *
 * This wets the DMA hewpews awwocate object stwucts fow us, and keep
 * ouw BO stats cowwect.
 */
stwuct dwm_gem_object *vc4_cweate_object(stwuct dwm_device *dev, size_t size)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_bo *bo;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn EWW_PTW(-ENODEV);

	bo = kzawwoc(sizeof(*bo), GFP_KEWNEW);
	if (!bo)
		wetuwn EWW_PTW(-ENOMEM);

	bo->madv = VC4_MADV_WIWWNEED;
	wefcount_set(&bo->usecnt, 0);

	mutex_init(&bo->madv_wock);

	mutex_wock(&vc4->bo_wock);
	bo->wabew = VC4_BO_TYPE_KEWNEW;
	vc4->bo_wabews[VC4_BO_TYPE_KEWNEW].num_awwocated++;
	vc4->bo_wabews[VC4_BO_TYPE_KEWNEW].size_awwocated += size;
	mutex_unwock(&vc4->bo_wock);

	bo->base.base.funcs = &vc4_gem_object_funcs;

	wetuwn &bo->base.base;
}

stwuct vc4_bo *vc4_bo_cweate(stwuct dwm_device *dev, size_t unawigned_size,
			     boow awwow_unzewoed, enum vc4_kewnew_bo_type type)
{
	size_t size = woundup(unawigned_size, PAGE_SIZE);
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_gem_dma_object *dma_obj;
	stwuct vc4_bo *bo;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn EWW_PTW(-ENODEV);

	if (size == 0)
		wetuwn EWW_PTW(-EINVAW);

	/* Fiwst, twy to get a vc4_bo fwom the kewnew BO cache. */
	bo = vc4_bo_get_fwom_cache(dev, size, type);
	if (bo) {
		if (!awwow_unzewoed)
			memset(bo->base.vaddw, 0, bo->base.base.size);
		wetuwn bo;
	}

	dma_obj = dwm_gem_dma_cweate(dev, size);
	if (IS_EWW(dma_obj)) {
		/*
		 * If we've wun out of DMA memowy, kiww the cache of
		 * DMA awwocations we've got waying awound and twy again.
		 */
		vc4_bo_cache_puwge(dev);
		dma_obj = dwm_gem_dma_cweate(dev, size);
	}

	if (IS_EWW(dma_obj)) {
		/*
		 * Stiww not enough DMA memowy, puwge the usewspace BO
		 * cache and wetwy.
		 * This is sub-optimaw since we puwge the whowe usewspace
		 * BO cache which fowces usew that want to we-use the BO to
		 * westowe its initiaw content.
		 * Ideawwy, we shouwd puwge entwies one by one and wetwy
		 * aftew each to see if DMA awwocation succeeds. Ow even
		 * bettew, twy to find an entwy with at weast the same
		 * size.
		 */
		vc4_bo_usewspace_cache_puwge(dev);
		dma_obj = dwm_gem_dma_cweate(dev, size);
	}

	if (IS_EWW(dma_obj)) {
		stwuct dwm_pwintew p = dwm_info_pwintew(vc4->base.dev);
		DWM_EWWOW("Faiwed to awwocate fwom GEM DMA hewpew:\n");
		vc4_bo_stats_pwint(&p, vc4);
		wetuwn EWW_PTW(-ENOMEM);
	}
	bo = to_vc4_bo(&dma_obj->base);

	/* By defauwt, BOs do not suppowt the MADV ioctw. This wiww be enabwed
	 * onwy on BOs that awe exposed to usewspace (V3D, V3D_SHADEW and DUMB
	 * BOs).
	 */
	bo->madv = __VC4_MADV_NOTSUPP;

	mutex_wock(&vc4->bo_wock);
	vc4_bo_set_wabew(&dma_obj->base, type);
	mutex_unwock(&vc4->bo_wock);

	wetuwn bo;
}

int vc4_bo_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		       stwuct dwm_device *dev,
		       stwuct dwm_mode_cweate_dumb *awgs)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_bo *bo = NUWW;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	wet = vc4_dumb_fixup_awgs(awgs);
	if (wet)
		wetuwn wet;

	bo = vc4_bo_cweate(dev, awgs->size, fawse, VC4_BO_TYPE_DUMB);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	bo->madv = VC4_MADV_WIWWNEED;

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->base.base, &awgs->handwe);
	dwm_gem_object_put(&bo->base.base);

	wetuwn wet;
}

static void vc4_bo_cache_fwee_owd(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned wong expiwe_time = jiffies - msecs_to_jiffies(1000);

	wockdep_assewt_hewd(&vc4->bo_wock);

	whiwe (!wist_empty(&vc4->bo_cache.time_wist)) {
		stwuct vc4_bo *bo = wist_wast_entwy(&vc4->bo_cache.time_wist,
						    stwuct vc4_bo, unwef_head);
		if (time_befowe(expiwe_time, bo->fwee_time)) {
			mod_timew(&vc4->bo_cache.time_timew,
				  wound_jiffies_up(jiffies +
						   msecs_to_jiffies(1000)));
			wetuwn;
		}

		vc4_bo_wemove_fwom_cache(bo);
		vc4_bo_destwoy(bo);
	}
}

/* Cawwed on the wast usewspace/kewnew unwefewence of the BO.  Wetuwns
 * it to the BO cache if possibwe, othewwise fwees it.
 */
static void vc4_fwee_object(stwuct dwm_gem_object *gem_bo)
{
	stwuct dwm_device *dev = gem_bo->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_bo *bo = to_vc4_bo(gem_bo);
	stwuct wist_head *cache_wist;

	/* Wemove the BO fwom the puwgeabwe wist. */
	mutex_wock(&bo->madv_wock);
	if (bo->madv == VC4_MADV_DONTNEED && !wefcount_wead(&bo->usecnt))
		vc4_bo_wemove_fwom_puwgeabwe_poow(bo);
	mutex_unwock(&bo->madv_wock);

	mutex_wock(&vc4->bo_wock);
	/* If the object wefewences someone ewse's memowy, we can't cache it.
	 */
	if (gem_bo->impowt_attach) {
		vc4_bo_destwoy(bo);
		goto out;
	}

	/* Don't cache if it was pubwicwy named. */
	if (gem_bo->name) {
		vc4_bo_destwoy(bo);
		goto out;
	}

	/* If this object was pawtiawwy constwucted but DMA awwocation
	 * had faiwed, just fwee it. Can awso happen when the BO has been
	 * puwged.
	 */
	if (!bo->base.vaddw) {
		vc4_bo_destwoy(bo);
		goto out;
	}

	cache_wist = vc4_get_cache_wist_fow_size(dev, gem_bo->size);
	if (!cache_wist) {
		vc4_bo_destwoy(bo);
		goto out;
	}

	if (bo->vawidated_shadew) {
		kfwee(bo->vawidated_shadew->unifowm_addw_offsets);
		kfwee(bo->vawidated_shadew->textuwe_sampwes);
		kfwee(bo->vawidated_shadew);
		bo->vawidated_shadew = NUWW;
	}

	/* Weset madv and usecnt befowe adding the BO to the cache. */
	bo->madv = __VC4_MADV_NOTSUPP;
	wefcount_set(&bo->usecnt, 0);

	bo->t_fowmat = fawse;
	bo->fwee_time = jiffies;
	wist_add(&bo->size_head, cache_wist);
	wist_add(&bo->unwef_head, &vc4->bo_cache.time_wist);

	vc4_bo_set_wabew(&bo->base.base, VC4_BO_TYPE_KEWNEW_CACHE);

	vc4_bo_cache_fwee_owd(dev);

out:
	mutex_unwock(&vc4->bo_wock);
}

static void vc4_bo_cache_time_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vc4_dev *vc4 =
		containew_of(wowk, stwuct vc4_dev, bo_cache.time_wowk);
	stwuct dwm_device *dev = &vc4->base;

	mutex_wock(&vc4->bo_wock);
	vc4_bo_cache_fwee_owd(dev);
	mutex_unwock(&vc4->bo_wock);
}

int vc4_bo_inc_usecnt(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	/* Fast path: if the BO is awweady wetained by someone, no need to
	 * check the madv status.
	 */
	if (wefcount_inc_not_zewo(&bo->usecnt))
		wetuwn 0;

	mutex_wock(&bo->madv_wock);
	switch (bo->madv) {
	case VC4_MADV_WIWWNEED:
		if (!wefcount_inc_not_zewo(&bo->usecnt))
			wefcount_set(&bo->usecnt, 1);
		wet = 0;
		bweak;
	case VC4_MADV_DONTNEED:
		/* We shouwdn't use a BO mawked as puwgeabwe if at weast
		 * someone ewse wetained its content by incwementing usecnt.
		 * Wuckiwy the BO hasn't been puwged yet, but something wwong
		 * is happening hewe. Just thwow an ewwow instead of
		 * authowizing this use case.
		 */
	case __VC4_MADV_PUWGED:
		/* We can't use a puwged BO. */
	defauwt:
		/* Invawid madv vawue. */
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&bo->madv_wock);

	wetuwn wet;
}

void vc4_bo_dec_usecnt(stwuct vc4_bo *bo)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(bo->base.base.dev);

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn;

	/* Fast path: if the BO is stiww wetained by someone, no need to test
	 * the madv vawue.
	 */
	if (wefcount_dec_not_one(&bo->usecnt))
		wetuwn;

	mutex_wock(&bo->madv_wock);
	if (wefcount_dec_and_test(&bo->usecnt) &&
	    bo->madv == VC4_MADV_DONTNEED)
		vc4_bo_add_to_puwgeabwe_poow(bo);
	mutex_unwock(&bo->madv_wock);
}

static void vc4_bo_cache_time_timew(stwuct timew_wist *t)
{
	stwuct vc4_dev *vc4 = fwom_timew(vc4, t, bo_cache.time_timew);

	scheduwe_wowk(&vc4->bo_cache.time_wowk);
}

static stwuct dma_buf *vc4_pwime_expowt(stwuct dwm_gem_object *obj, int fwags)
{
	stwuct vc4_bo *bo = to_vc4_bo(obj);
	stwuct dma_buf *dmabuf;
	int wet;

	if (bo->vawidated_shadew) {
		DWM_DEBUG("Attempting to expowt shadew BO\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/* Note: as soon as the BO is expowted it becomes unpuwgeabwe, because
	 * noone evew decwements the usecnt even if the wefewence hewd by the
	 * expowted BO is weweased. This shouwdn't be a pwobwem since we don't
	 * expect expowted BOs to be mawked as puwgeabwe.
	 */
	wet = vc4_bo_inc_usecnt(bo);
	if (wet) {
		DWM_EWWOW("Faiwed to incwement BO usecnt\n");
		wetuwn EWW_PTW(wet);
	}

	dmabuf = dwm_gem_pwime_expowt(obj, fwags);
	if (IS_EWW(dmabuf))
		vc4_bo_dec_usecnt(bo);

	wetuwn dmabuf;
}

static vm_fauwt_t vc4_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct dwm_gem_object *obj = vma->vm_pwivate_data;
	stwuct vc4_bo *bo = to_vc4_bo(obj);

	/* The onwy weason we wouwd end up hewe is when usew-space accesses
	 * BO's memowy aftew it's been puwged.
	 */
	mutex_wock(&bo->madv_wock);
	WAWN_ON(bo->madv != __VC4_MADV_PUWGED);
	mutex_unwock(&bo->madv_wock);

	wetuwn VM_FAUWT_SIGBUS;
}

static int vc4_gem_object_mmap(stwuct dwm_gem_object *obj, stwuct vm_awea_stwuct *vma)
{
	stwuct vc4_bo *bo = to_vc4_bo(obj);

	if (bo->vawidated_shadew && (vma->vm_fwags & VM_WWITE)) {
		DWM_DEBUG("mmapping of shadew BOs fow wwiting not awwowed.\n");
		wetuwn -EINVAW;
	}

	if (bo->madv != VC4_MADV_WIWWNEED) {
		DWM_DEBUG("mmapping of %s BO not awwowed\n",
			  bo->madv == VC4_MADV_DONTNEED ?
			  "puwgeabwe" : "puwged");
		wetuwn -EINVAW;
	}

	wetuwn dwm_gem_dma_mmap(&bo->base, vma);
}

static const stwuct vm_opewations_stwuct vc4_vm_ops = {
	.fauwt = vc4_fauwt,
	.open = dwm_gem_vm_open,
	.cwose = dwm_gem_vm_cwose,
};

static const stwuct dwm_gem_object_funcs vc4_gem_object_funcs = {
	.fwee = vc4_fwee_object,
	.expowt = vc4_pwime_expowt,
	.get_sg_tabwe = dwm_gem_dma_object_get_sg_tabwe,
	.vmap = dwm_gem_dma_object_vmap,
	.mmap = vc4_gem_object_mmap,
	.vm_ops = &vc4_vm_ops,
};

static int vc4_gwab_bin_bo(stwuct vc4_dev *vc4, stwuct vc4_fiwe *vc4fiwe)
{
	if (!vc4->v3d)
		wetuwn -ENODEV;

	if (vc4fiwe->bin_bo_used)
		wetuwn 0;

	wetuwn vc4_v3d_bin_bo_get(vc4, &vc4fiwe->bin_bo_used);
}

int vc4_cweate_bo_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vc4_cweate_bo *awgs = data;
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_bo *bo = NUWW;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	wet = vc4_gwab_bin_bo(vc4, vc4fiwe);
	if (wet)
		wetuwn wet;

	/*
	 * We can't awwocate fwom the BO cache, because the BOs don't
	 * get zewoed, and that might weak data between usews.
	 */
	bo = vc4_bo_cweate(dev, awgs->size, fawse, VC4_BO_TYPE_V3D);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	bo->madv = VC4_MADV_WIWWNEED;

	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->base.base, &awgs->handwe);
	dwm_gem_object_put(&bo->base.base);

	wetuwn wet;
}

int vc4_mmap_bo_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_mmap_bo *awgs = data;
	stwuct dwm_gem_object *gem_obj;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -EINVAW;
	}

	/* The mmap offset was set up at BO awwocation time. */
	awgs->offset = dwm_vma_node_offset_addw(&gem_obj->vma_node);

	dwm_gem_object_put(gem_obj);
	wetuwn 0;
}

int
vc4_cweate_shadew_bo_ioctw(stwuct dwm_device *dev, void *data,
			   stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vc4_cweate_shadew_bo *awgs = data;
	stwuct vc4_fiwe *vc4fiwe = fiwe_pwiv->dwivew_pwiv;
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct vc4_bo *bo = NUWW;
	int wet;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (awgs->size == 0)
		wetuwn -EINVAW;

	if (awgs->size % sizeof(u64) != 0)
		wetuwn -EINVAW;

	if (awgs->fwags != 0) {
		DWM_INFO("Unknown fwags set: 0x%08x\n", awgs->fwags);
		wetuwn -EINVAW;
	}

	if (awgs->pad != 0) {
		DWM_INFO("Pad set: 0x%08x\n", awgs->pad);
		wetuwn -EINVAW;
	}

	wet = vc4_gwab_bin_bo(vc4, vc4fiwe);
	if (wet)
		wetuwn wet;

	bo = vc4_bo_cweate(dev, awgs->size, twue, VC4_BO_TYPE_V3D_SHADEW);
	if (IS_EWW(bo))
		wetuwn PTW_EWW(bo);

	bo->madv = VC4_MADV_WIWWNEED;

	if (copy_fwom_usew(bo->base.vaddw,
			     (void __usew *)(uintptw_t)awgs->data,
			     awgs->size)) {
		wet = -EFAUWT;
		goto faiw;
	}
	/* Cweaw the west of the memowy fwom awwocating fwom the BO
	 * cache.
	 */
	memset(bo->base.vaddw + awgs->size, 0,
	       bo->base.base.size - awgs->size);

	bo->vawidated_shadew = vc4_vawidate_shadew(&bo->base);
	if (!bo->vawidated_shadew) {
		wet = -EINVAW;
		goto faiw;
	}

	/* We have to cweate the handwe aftew vawidation, to avoid
	 * waces fow usews to do doing things wike mmap the shadew BO.
	 */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &bo->base.base, &awgs->handwe);

faiw:
	dwm_gem_object_put(&bo->base.base);

	wetuwn wet;
}

/**
 * vc4_set_tiwing_ioctw() - Sets the tiwing modifiew fow a BO.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * The tiwing state of the BO decides the defauwt modifiew of an fb if
 * no specific modifiew was set by usewspace, and the wetuwn vawue of
 * vc4_get_tiwing_ioctw() (so that usewspace can tweat a BO it
 * weceived fwom dmabuf as the same tiwing fowmat as the pwoducew
 * used).
 */
int vc4_set_tiwing_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_set_tiwing *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	stwuct vc4_bo *bo;
	boow t_fowmat;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (awgs->fwags != 0)
		wetuwn -EINVAW;

	switch (awgs->modifiew) {
	case DWM_FOWMAT_MOD_NONE:
		t_fowmat = fawse;
		bweak;
	case DWM_FOWMAT_MOD_BWOADCOM_VC4_T_TIWED:
		t_fowmat = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}
	bo = to_vc4_bo(gem_obj);
	bo->t_fowmat = t_fowmat;

	dwm_gem_object_put(gem_obj);

	wetuwn 0;
}

/**
 * vc4_get_tiwing_ioctw() - Gets the tiwing modifiew fow a BO.
 * @dev: DWM device
 * @data: ioctw awgument
 * @fiwe_pwiv: DWM fiwe fow this fd
 *
 * Wetuwns the tiwing modifiew fow a BO as set by vc4_set_tiwing_ioctw().
 */
int vc4_get_tiwing_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_get_tiwing *awgs = data;
	stwuct dwm_gem_object *gem_obj;
	stwuct vc4_bo *bo;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (awgs->fwags != 0 || awgs->modifiew != 0)
		wetuwn -EINVAW;

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_DEBUG("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		wetuwn -ENOENT;
	}
	bo = to_vc4_bo(gem_obj);

	if (bo->t_fowmat)
		awgs->modifiew = DWM_FOWMAT_MOD_BWOADCOM_VC4_T_TIWED;
	ewse
		awgs->modifiew = DWM_FOWMAT_MOD_NONE;

	dwm_gem_object_put(gem_obj);

	wetuwn 0;
}

int vc4_bo_debugfs_init(stwuct dwm_minow *minow)
{
	stwuct dwm_device *dwm = minow->dev;
	stwuct vc4_dev *vc4 = to_vc4_dev(dwm);

	if (!vc4->v3d)
		wetuwn -ENODEV;

	dwm_debugfs_add_fiwe(dwm, "bo_stats", vc4_bo_stats_debugfs, NUWW);

	wetuwn 0;
}

static void vc4_bo_cache_destwoy(stwuct dwm_device *dev, void *unused);
int vc4_bo_cache_init(stwuct dwm_device *dev)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int wet;
	int i;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	/* Cweate the initiaw set of BO wabews that the kewnew wiww
	 * use.  This wets us avoid a bunch of stwing weawwocation in
	 * the kewnew's dwaw and BO awwocation paths.
	 */
	vc4->bo_wabews = kcawwoc(VC4_BO_TYPE_COUNT, sizeof(*vc4->bo_wabews),
				 GFP_KEWNEW);
	if (!vc4->bo_wabews)
		wetuwn -ENOMEM;
	vc4->num_wabews = VC4_BO_TYPE_COUNT;

	BUIWD_BUG_ON(AWWAY_SIZE(bo_type_names) != VC4_BO_TYPE_COUNT);
	fow (i = 0; i < VC4_BO_TYPE_COUNT; i++)
		vc4->bo_wabews[i].name = bo_type_names[i];

	wet = dwmm_mutex_init(dev, &vc4->bo_wock);
	if (wet) {
		kfwee(vc4->bo_wabews);
		wetuwn wet;
	}

	INIT_WIST_HEAD(&vc4->bo_cache.time_wist);

	INIT_WOWK(&vc4->bo_cache.time_wowk, vc4_bo_cache_time_wowk);
	timew_setup(&vc4->bo_cache.time_timew, vc4_bo_cache_time_timew, 0);

	wetuwn dwmm_add_action_ow_weset(dev, vc4_bo_cache_destwoy, NUWW);
}

static void vc4_bo_cache_destwoy(stwuct dwm_device *dev, void *unused)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	int i;

	dew_timew(&vc4->bo_cache.time_timew);
	cancew_wowk_sync(&vc4->bo_cache.time_wowk);

	vc4_bo_cache_puwge(dev);

	fow (i = 0; i < vc4->num_wabews; i++) {
		if (vc4->bo_wabews[i].num_awwocated) {
			DWM_EWWOW("Destwoying BO cache with %d %s "
				  "BOs stiww awwocated\n",
				  vc4->bo_wabews[i].num_awwocated,
				  vc4->bo_wabews[i].name);
		}

		if (is_usew_wabew(i))
			kfwee(vc4->bo_wabews[i].name);
	}
	kfwee(vc4->bo_wabews);
}

int vc4_wabew_bo_ioctw(stwuct dwm_device *dev, void *data,
		       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vc4_dev *vc4 = to_vc4_dev(dev);
	stwuct dwm_vc4_wabew_bo *awgs = data;
	chaw *name;
	stwuct dwm_gem_object *gem_obj;
	int wet = 0, wabew;

	if (WAWN_ON_ONCE(vc4->is_vc5))
		wetuwn -ENODEV;

	if (!awgs->wen)
		wetuwn -EINVAW;

	name = stwndup_usew(u64_to_usew_ptw(awgs->name), awgs->wen + 1);
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	gem_obj = dwm_gem_object_wookup(fiwe_pwiv, awgs->handwe);
	if (!gem_obj) {
		DWM_EWWOW("Faiwed to wook up GEM BO %d\n", awgs->handwe);
		kfwee(name);
		wetuwn -ENOENT;
	}

	mutex_wock(&vc4->bo_wock);
	wabew = vc4_get_usew_wabew(vc4, name);
	if (wabew != -1)
		vc4_bo_set_wabew(gem_obj, wabew);
	ewse
		wet = -ENOMEM;
	mutex_unwock(&vc4->bo_wock);

	dwm_gem_object_put(gem_obj);

	wetuwn wet;
}
