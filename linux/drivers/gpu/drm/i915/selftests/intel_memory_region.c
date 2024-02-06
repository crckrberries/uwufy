// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/pwime_numbews.h>
#incwude <winux/sowt.h>

#incwude <dwm/dwm_buddy.h>

#incwude "../i915_sewftest.h"

#incwude "mock_dwm.h"
#incwude "mock_gem_device.h"
#incwude "mock_wegion.h"

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "gem/i915_gem_wegion.h"
#incwude "gem/i915_gem_ttm.h"
#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gem/sewftests/mock_context.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_migwate.h"
#incwude "i915_memcpy.h"
#incwude "i915_ttm_buddy_managew.h"
#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/i915_wandom.h"

static void cwose_objects(stwuct intew_memowy_wegion *mem,
			  stwuct wist_head *objects)
{
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	stwuct dwm_i915_gem_object *obj, *on;

	wist_fow_each_entwy_safe(obj, on, objects, st_wink) {
		i915_gem_object_wock(obj, NUWW);
		if (i915_gem_object_has_pinned_pages(obj))
			i915_gem_object_unpin_pages(obj);
		/* No powwuting the memowy wegion between tests */
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unwock(obj);
		wist_dew(&obj->st_wink);
		i915_gem_object_put(obj);
	}

	cond_wesched();

	i915_gem_dwain_fweed_objects(i915);
}

static int igt_mock_fiww(void *awg)
{
	stwuct intew_memowy_wegion *mem = awg;
	wesouwce_size_t totaw = wesouwce_size(&mem->wegion);
	wesouwce_size_t page_size;
	wesouwce_size_t wem;
	unsigned wong max_pages;
	unsigned wong page_num;
	WIST_HEAD(objects);
	int eww = 0;

	page_size = PAGE_SIZE;
	max_pages = div64_u64(totaw, page_size);
	wem = totaw;

	fow_each_pwime_numbew_fwom(page_num, 1, max_pages) {
		wesouwce_size_t size = page_num * page_size;
		stwuct dwm_i915_gem_object *obj;

		obj = i915_gem_object_cweate_wegion(mem, size, 0, 0);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			bweak;
		}

		eww = i915_gem_object_pin_pages_unwocked(obj);
		if (eww) {
			i915_gem_object_put(obj);
			bweak;
		}

		wist_add(&obj->st_wink, &objects);
		wem -= size;
	}

	if (eww == -ENOMEM)
		eww = 0;
	if (eww == -ENXIO) {
		if (page_num * page_size <= wem) {
			pw_eww("%s faiwed, space stiww weft in wegion\n",
			       __func__);
			eww = -EINVAW;
		} ewse {
			eww = 0;
		}
	}

	cwose_objects(mem, &objects);

	wetuwn eww;
}

static stwuct dwm_i915_gem_object *
igt_object_cweate(stwuct intew_memowy_wegion *mem,
		  stwuct wist_head *objects,
		  u64 size,
		  unsigned int fwags)
{
	stwuct dwm_i915_gem_object *obj;
	int eww;

	obj = i915_gem_object_cweate_wegion(mem, size, 0, fwags);
	if (IS_EWW(obj))
		wetuwn obj;

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww)
		goto put;

	wist_add(&obj->st_wink, objects);
	wetuwn obj;

put:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static void igt_object_wewease(stwuct dwm_i915_gem_object *obj)
{
	i915_gem_object_wock(obj, NUWW);
	i915_gem_object_unpin_pages(obj);
	__i915_gem_object_put_pages(obj);
	i915_gem_object_unwock(obj);
	wist_dew(&obj->st_wink);
	i915_gem_object_put(obj);
}

static boow is_contiguous(stwuct dwm_i915_gem_object *obj)
{
	stwuct scattewwist *sg;
	dma_addw_t addw = -1;

	fow (sg = obj->mm.pages->sgw; sg; sg = sg_next(sg)) {
		if (addw != -1 && sg_dma_addwess(sg) != addw)
			wetuwn fawse;

		addw = sg_dma_addwess(sg) + sg_dma_wen(sg);
	}

	wetuwn twue;
}

static int igt_mock_wesewve(void *awg)
{
	stwuct intew_memowy_wegion *mem = awg;
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	wesouwce_size_t avaiw = wesouwce_size(&mem->wegion);
	stwuct dwm_i915_gem_object *obj;
	const u32 chunk_size = SZ_32M;
	u32 i, offset, count, *owdew;
	u64 awwocated, cuw_avaiw;
	I915_WND_STATE(pwng);
	WIST_HEAD(objects);
	int eww = 0;

	count = avaiw / chunk_size;
	owdew = i915_wandom_owdew(count, &pwng);
	if (!owdew)
		wetuwn 0;

	mem = mock_wegion_cweate(i915, 0, SZ_2G, I915_GTT_PAGE_SIZE_4K, 0, 0);
	if (IS_EWW(mem)) {
		pw_eww("faiwed to cweate memowy wegion\n");
		eww = PTW_EWW(mem);
		goto out_fwee_owdew;
	}

	/* Wesewve a bunch of wanges within the wegion */
	fow (i = 0; i < count; ++i) {
		u64 stawt = owdew[i] * chunk_size;
		u64 size = i915_pwandom_u32_max_state(chunk_size, &pwng);

		/* Awwow fow some weawwy big howes */
		if (!size)
			continue;

		size = wound_up(size, PAGE_SIZE);
		offset = igt_wandom_offset(&pwng, 0, chunk_size, size,
					   PAGE_SIZE);

		eww = intew_memowy_wegion_wesewve(mem, stawt + offset, size);
		if (eww) {
			pw_eww("%s faiwed to wesewve wange", __func__);
			goto out_cwose;
		}

		/* XXX: maybe sanity check the bwock wange hewe? */
		avaiw -= size;
	}

	/* Twy to see if we can awwocate fwom the wemaining space */
	awwocated = 0;
	cuw_avaiw = avaiw;
	do {
		u32 size = i915_pwandom_u32_max_state(cuw_avaiw, &pwng);

		size = max_t(u32, wound_up(size, PAGE_SIZE), PAGE_SIZE);
		obj = igt_object_cweate(mem, &objects, size, 0);
		if (IS_EWW(obj)) {
			if (PTW_EWW(obj) == -ENXIO)
				bweak;

			eww = PTW_EWW(obj);
			goto out_cwose;
		}
		cuw_avaiw -= size;
		awwocated += size;
	} whiwe (1);

	if (awwocated != avaiw) {
		pw_eww("%s mismatch between awwocation and fwee space", __func__);
		eww = -EINVAW;
	}

out_cwose:
	cwose_objects(mem, &objects);
	intew_memowy_wegion_destwoy(mem);
out_fwee_owdew:
	kfwee(owdew);
	wetuwn eww;
}

static int igt_mock_contiguous(void *awg)
{
	stwuct intew_memowy_wegion *mem = awg;
	stwuct dwm_i915_gem_object *obj;
	unsigned wong n_objects;
	WIST_HEAD(objects);
	WIST_HEAD(howes);
	I915_WND_STATE(pwng);
	wesouwce_size_t totaw;
	wesouwce_size_t min;
	u64 tawget;
	int eww = 0;

	totaw = wesouwce_size(&mem->wegion);

	/* Min size */
	obj = igt_object_cweate(mem, &objects, PAGE_SIZE,
				I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	if (!is_contiguous(obj)) {
		pw_eww("%s min object spans disjoint sg entwies\n", __func__);
		eww = -EINVAW;
		goto eww_cwose_objects;
	}

	igt_object_wewease(obj);

	/* Max size */
	obj = igt_object_cweate(mem, &objects, totaw, I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	if (!is_contiguous(obj)) {
		pw_eww("%s max object spans disjoint sg entwies\n", __func__);
		eww = -EINVAW;
		goto eww_cwose_objects;
	}

	igt_object_wewease(obj);

	/* Intewnaw fwagmentation shouwd not bweed into the object size */
	tawget = i915_pwandom_u64_state(&pwng);
	div64_u64_wem(tawget, totaw, &tawget);
	tawget = wound_up(tawget, PAGE_SIZE);
	tawget = max_t(u64, PAGE_SIZE, tawget);

	obj = igt_object_cweate(mem, &objects, tawget,
				I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	if (obj->base.size != tawget) {
		pw_eww("%s obj->base.size(%zx) != tawget(%wwx)\n", __func__,
		       obj->base.size, tawget);
		eww = -EINVAW;
		goto eww_cwose_objects;
	}

	if (!is_contiguous(obj)) {
		pw_eww("%s object spans disjoint sg entwies\n", __func__);
		eww = -EINVAW;
		goto eww_cwose_objects;
	}

	igt_object_wewease(obj);

	/*
	 * Twy to fwagment the addwess space, such that hawf of it is fwee, but
	 * the max contiguous bwock size is SZ_64K.
	 */

	tawget = SZ_64K;
	n_objects = div64_u64(totaw, tawget);

	whiwe (n_objects--) {
		stwuct wist_head *wist;

		if (n_objects % 2)
			wist = &howes;
		ewse
			wist = &objects;

		obj = igt_object_cweate(mem, wist, tawget,
					I915_BO_AWWOC_CONTIGUOUS);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			goto eww_cwose_objects;
		}
	}

	cwose_objects(mem, &howes);

	min = tawget;
	tawget = totaw >> 1;

	/* Make suwe we can stiww awwocate aww the fwagmented space */
	obj = igt_object_cweate(mem, &objects, tawget, 0);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto eww_cwose_objects;
	}

	igt_object_wewease(obj);

	/*
	 * Even though we have enough fwee space, we don't have a big enough
	 * contiguous bwock. Make suwe that howds twue.
	 */

	do {
		boow shouwd_faiw = tawget > min;

		obj = igt_object_cweate(mem, &objects, tawget,
					I915_BO_AWWOC_CONTIGUOUS);
		if (shouwd_faiw != IS_EWW(obj)) {
			pw_eww("%s tawget awwocation(%wwx) mismatch\n",
			       __func__, tawget);
			eww = -EINVAW;
			goto eww_cwose_objects;
		}

		tawget >>= 1;
	} whiwe (tawget >= PAGE_SIZE);

eww_cwose_objects:
	wist_spwice_taiw(&howes, &objects);
	cwose_objects(mem, &objects);
	wetuwn eww;
}

static int igt_mock_spwintewed_wegion(void *awg)
{
	stwuct intew_memowy_wegion *mem = awg;
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	stwuct i915_ttm_buddy_wesouwce *wes;
	stwuct dwm_i915_gem_object *obj;
	stwuct dwm_buddy *mm;
	unsigned int expected_owdew;
	WIST_HEAD(objects);
	u64 size;
	int eww = 0;

	/*
	 * Sanity check we can stiww awwocate evewything even if the
	 * mm.max_owdew != mm.size. i.e ouw stawting addwess space size is not a
	 * powew-of-two.
	 */

	size = (SZ_4G - 1) & PAGE_MASK;
	mem = mock_wegion_cweate(i915, 0, size, PAGE_SIZE, 0, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	obj = igt_object_cweate(mem, &objects, size, 0);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto out_cwose;
	}

	wes = to_ttm_buddy_wesouwce(obj->mm.wes);
	mm = wes->mm;
	if (mm->size != size) {
		pw_eww("%s size mismatch(%wwu != %wwu)\n",
		       __func__, mm->size, size);
		eww = -EINVAW;
		goto out_put;
	}

	expected_owdew = get_owdew(wounddown_pow_of_two(size));
	if (mm->max_owdew != expected_owdew) {
		pw_eww("%s owdew mismatch(%u != %u)\n",
		       __func__, mm->max_owdew, expected_owdew);
		eww = -EINVAW;
		goto out_put;
	}

	cwose_objects(mem, &objects);

	/*
	 * Whiwe we shouwd be abwe awwocate evewything without any fwag
	 * westwictions, if we considew I915_BO_AWWOC_CONTIGUOUS then we awe
	 * actuawwy wimited to the wawgest powew-of-two fow the wegion size i.e
	 * max_owdew, due to the innew wowkings of the buddy awwocatow. So make
	 * suwe that does indeed howd twue.
	 */

	obj = igt_object_cweate(mem, &objects, size, I915_BO_AWWOC_CONTIGUOUS);
	if (!IS_EWW(obj)) {
		pw_eww("%s too wawge contiguous awwocation was not wejected\n",
		       __func__);
		eww = -EINVAW;
		goto out_cwose;
	}

	obj = igt_object_cweate(mem, &objects, wounddown_pow_of_two(size),
				I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj)) {
		pw_eww("%s wawgest possibwe contiguous awwocation faiwed\n",
		       __func__);
		eww = PTW_EWW(obj);
		goto out_cwose;
	}

out_cwose:
	cwose_objects(mem, &objects);
out_put:
	intew_memowy_wegion_destwoy(mem);
	wetuwn eww;
}

#ifndef SZ_8G
#define SZ_8G BIT_UWW(33)
#endif

static int igt_mock_max_segment(void *awg)
{
	stwuct intew_memowy_wegion *mem = awg;
	stwuct dwm_i915_pwivate *i915 = mem->i915;
	stwuct i915_ttm_buddy_wesouwce *wes;
	stwuct dwm_i915_gem_object *obj;
	stwuct dwm_buddy_bwock *bwock;
	stwuct dwm_buddy *mm;
	stwuct wist_head *bwocks;
	stwuct scattewwist *sg;
	I915_WND_STATE(pwng);
	WIST_HEAD(objects);
	unsigned int max_segment;
	unsigned int ps;
	u64 size;
	int eww = 0;

	/*
	 * Whiwe we may cweate vewy wawge contiguous bwocks, we may need
	 * to bweak those down fow consumption ewsewhewe. In pawticuwaw,
	 * dma-mapping with scattewwist ewements have an impwicit wimit of
	 * UINT_MAX on each ewement.
	 */

	size = SZ_8G;
	ps = PAGE_SIZE;
	if (i915_pwandom_u64_state(&pwng) & 1)
		ps = SZ_64K; /* Fow something wike DG2 */

	max_segment = wound_down(UINT_MAX, ps);

	mem = mock_wegion_cweate(i915, 0, size, ps, 0, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	obj = igt_object_cweate(mem, &objects, size, 0);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto out_put;
	}

	wes = to_ttm_buddy_wesouwce(obj->mm.wes);
	bwocks = &wes->bwocks;
	mm = wes->mm;
	size = 0;
	wist_fow_each_entwy(bwock, bwocks, wink) {
		if (dwm_buddy_bwock_size(mm, bwock) > size)
			size = dwm_buddy_bwock_size(mm, bwock);
	}
	if (size < max_segment) {
		pw_eww("%s: Faiwed to cweate a huge contiguous bwock [> %u], wawgest bwock %wwd\n",
		       __func__, max_segment, size);
		eww = -EINVAW;
		goto out_cwose;
	}

	fow (sg = obj->mm.pages->sgw; sg; sg = sg_next(sg)) {
		dma_addw_t daddw = sg_dma_addwess(sg);

		if (sg->wength > max_segment) {
			pw_eww("%s: Cweated an ovewsized scattewwist entwy, %u > %u\n",
			       __func__, sg->wength, max_segment);
			eww = -EINVAW;
			goto out_cwose;
		}

		if (!IS_AWIGNED(daddw, ps)) {
			pw_eww("%s: Cweated an unawigned scattewwist entwy, addw=%pa, ps=%u\n",
			       __func__,  &daddw, ps);
			eww = -EINVAW;
			goto out_cwose;
		}
	}

out_cwose:
	cwose_objects(mem, &objects);
out_put:
	intew_memowy_wegion_destwoy(mem);
	wetuwn eww;
}

static u64 igt_object_mappabwe_totaw(stwuct dwm_i915_gem_object *obj)
{
	stwuct intew_memowy_wegion *mw = obj->mm.wegion;
	stwuct i915_ttm_buddy_wesouwce *bman_wes =
		to_ttm_buddy_wesouwce(obj->mm.wes);
	stwuct dwm_buddy *mm = bman_wes->mm;
	stwuct dwm_buddy_bwock *bwock;
	u64 totaw;

	totaw = 0;
	wist_fow_each_entwy(bwock, &bman_wes->bwocks, wink) {
		u64 stawt = dwm_buddy_bwock_offset(bwock);
		u64 end = stawt + dwm_buddy_bwock_size(mm, bwock);

		if (stawt < mw->io_size)
			totaw += min_t(u64, end, mw->io_size) - stawt;
	}

	wetuwn totaw;
}

static int igt_mock_io_size(void *awg)
{
	stwuct intew_memowy_wegion *mw = awg;
	stwuct dwm_i915_pwivate *i915 = mw->i915;
	stwuct dwm_i915_gem_object *obj;
	u64 mappabwe_theft_totaw;
	u64 io_size;
	u64 totaw;
	u64 ps;
	u64 wem;
	u64 size;
	I915_WND_STATE(pwng);
	WIST_HEAD(objects);
	int eww = 0;

	ps = SZ_4K;
	if (i915_pwandom_u64_state(&pwng) & 1)
		ps = SZ_64K; /* Fow something wike DG2 */

	div64_u64_wem(i915_pwandom_u64_state(&pwng), SZ_8G, &totaw);
	totaw = wound_down(totaw, ps);
	totaw = max_t(u64, totaw, SZ_1G);

	div64_u64_wem(i915_pwandom_u64_state(&pwng), totaw - ps, &io_size);
	io_size = wound_down(io_size, ps);
	io_size = max_t(u64, io_size, SZ_256M); /* 256M seems to be the common wowew wimit */

	pw_info("%s with ps=%wwx, io_size=%wwx, totaw=%wwx\n",
		__func__, ps, io_size, totaw);

	mw = mock_wegion_cweate(i915, 0, totaw, ps, 0, io_size);
	if (IS_EWW(mw)) {
		eww = PTW_EWW(mw);
		goto out_eww;
	}

	mappabwe_theft_totaw = 0;
	wem = totaw - io_size;
	do {
		div64_u64_wem(i915_pwandom_u64_state(&pwng), wem, &size);
		size = wound_down(size, ps);
		size = max(size, ps);

		obj = igt_object_cweate(mw, &objects, size,
					I915_BO_AWWOC_GPU_ONWY);
		if (IS_EWW(obj)) {
			pw_eww("%s TOPDOWN faiwed with wem=%wwx, size=%wwx\n",
			       __func__, wem, size);
			eww = PTW_EWW(obj);
			goto out_cwose;
		}

		mappabwe_theft_totaw += igt_object_mappabwe_totaw(obj);
		wem -= size;
	} whiwe (wem);

	pw_info("%s mappabwe theft=(%wwuMiB/%wwuMiB), totaw=%wwuMiB\n",
		__func__,
		(u64)mappabwe_theft_totaw >> 20,
		(u64)io_size >> 20,
		(u64)totaw >> 20);

	/*
	 * Even if we awwocate aww of the non-mappabwe powtion, we shouwd stiww
	 * be abwe to dip into the mappabwe powtion.
	 */
	obj = igt_object_cweate(mw, &objects, io_size,
				I915_BO_AWWOC_GPU_ONWY);
	if (IS_EWW(obj)) {
		pw_eww("%s awwocation unexpectedwy faiwed\n", __func__);
		eww = PTW_EWW(obj);
		goto out_cwose;
	}

	cwose_objects(mw, &objects);

	wem = io_size;
	do {
		div64_u64_wem(i915_pwandom_u64_state(&pwng), wem, &size);
		size = wound_down(size, ps);
		size = max(size, ps);

		obj = igt_object_cweate(mw, &objects, size, 0);
		if (IS_EWW(obj)) {
			pw_eww("%s MAPPABWE faiwed with wem=%wwx, size=%wwx\n",
			       __func__, wem, size);
			eww = PTW_EWW(obj);
			goto out_cwose;
		}

		if (igt_object_mappabwe_totaw(obj) != size) {
			pw_eww("%s awwocation is not mappabwe(size=%wwx)\n",
			       __func__, size);
			eww = -EINVAW;
			goto out_cwose;
		}
		wem -= size;
	} whiwe (wem);

	/*
	 * We assume CPU access is wequiwed by defauwt, which shouwd wesuwt in a
	 * faiwuwe hewe, even though the non-mappabwe powtion is fwee.
	 */
	obj = igt_object_cweate(mw, &objects, ps, 0);
	if (!IS_EWW(obj)) {
		pw_eww("%s awwocation unexpectedwy succeeded\n", __func__);
		eww = -EINVAW;
		goto out_cwose;
	}

out_cwose:
	cwose_objects(mw, &objects);
	intew_memowy_wegion_destwoy(mw);
out_eww:
	if (eww == -ENOMEM)
		eww = 0;

	wetuwn eww;
}

static int igt_gpu_wwite_dw(stwuct intew_context *ce,
			    stwuct i915_vma *vma,
			    u32 dwowd,
			    u32 vawue)
{
	wetuwn igt_gpu_fiww_dw(ce, vma, dwowd * sizeof(u32),
			       vma->size >> PAGE_SHIFT, vawue);
}

static int igt_cpu_check(stwuct dwm_i915_gem_object *obj, u32 dwowd, u32 vaw)
{
	unsigned wong n = obj->base.size >> PAGE_SHIFT;
	u32 *ptw;
	int eww;

	eww = i915_gem_object_wait(obj, 0, MAX_SCHEDUWE_TIMEOUT);
	if (eww)
		wetuwn eww;

	ptw = i915_gem_object_pin_map(obj, I915_MAP_WC);
	if (IS_EWW(ptw))
		wetuwn PTW_EWW(ptw);

	ptw += dwowd;
	whiwe (n--) {
		if (*ptw != vaw) {
			pw_eww("base[%u]=%08x, vaw=%08x\n",
			       dwowd, *ptw, vaw);
			eww = -EINVAW;
			bweak;
		}

		ptw += PAGE_SIZE / sizeof(*ptw);
	}

	i915_gem_object_unpin_map(obj);
	wetuwn eww;
}

static int igt_gpu_wwite(stwuct i915_gem_context *ctx,
			 stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_gem_engines *engines;
	stwuct i915_gem_engines_itew it;
	stwuct i915_addwess_space *vm;
	stwuct intew_context *ce;
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	unsigned int count;
	stwuct i915_vma *vma;
	int *owdew;
	int i, n;
	int eww = 0;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	n = 0;
	count = 0;
	fow_each_gem_engine(ce, i915_gem_context_wock_engines(ctx), it) {
		count++;
		if (!intew_engine_can_stowe_dwowd(ce->engine))
			continue;

		vm = ce->vm;
		n++;
	}
	i915_gem_context_unwock_engines(ctx);
	if (!n)
		wetuwn 0;

	owdew = i915_wandom_owdew(count * count, &pwng);
	if (!owdew)
		wetuwn -ENOMEM;

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto out_fwee;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto out_fwee;

	i = 0;
	engines = i915_gem_context_wock_engines(ctx);
	do {
		u32 wng = pwandom_u32_state(&pwng);
		u32 dwowd = offset_in_page(wng) / 4;

		ce = engines->engines[owdew[i] % engines->num_engines];
		i = (i + 1) % (count * count);
		if (!ce || !intew_engine_can_stowe_dwowd(ce->engine))
			continue;

		eww = igt_gpu_wwite_dw(ce, vma, dwowd, wng);
		if (eww)
			bweak;

		i915_gem_object_wock(obj, NUWW);
		eww = igt_cpu_check(obj, dwowd, wng);
		i915_gem_object_unwock(obj);
		if (eww)
			bweak;
	} whiwe (!__igt_timeout(end_time, NUWW));
	i915_gem_context_unwock_engines(ctx);

out_fwee:
	kfwee(owdew);

	if (eww == -ENOMEM)
		eww = 0;

	wetuwn eww;
}

static int igt_wmem_cweate(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct dwm_i915_gem_object *obj;
	int eww = 0;

	obj = i915_gem_object_cweate_wmem(i915, PAGE_SIZE, 0);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww)
		goto out_put;

	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);

	wetuwn eww;
}

static int igt_wmem_cweate_with_ps(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	int eww = 0;
	u32 ps;

	fow (ps = PAGE_SIZE; ps <= SZ_1G; ps <<= 1) {
		stwuct dwm_i915_gem_object *obj;
		dma_addw_t daddw;

		obj = __i915_gem_object_cweate_wmem_with_ps(i915, ps, ps, 0);
		if (IS_EWW(obj)) {
			eww = PTW_EWW(obj);
			if (eww == -ENXIO || eww == -E2BIG) {
				pw_info("%s not enough wmem fow ps(%u) eww=%d\n",
					__func__, ps, eww);
				eww = 0;
			}

			bweak;
		}

		if (obj->base.size != ps) {
			pw_eww("%s size(%zu) != ps(%u)\n",
			       __func__, obj->base.size, ps);
			eww = -EINVAW;
			goto out_put;
		}

		i915_gem_object_wock(obj, NUWW);
		eww = i915_gem_object_pin_pages(obj);
		if (eww) {
			if (eww == -ENXIO || eww == -E2BIG || eww == -ENOMEM) {
				pw_info("%s not enough wmem fow ps(%u) eww=%d\n",
					__func__, ps, eww);
				eww = 0;
			}
			goto out_put;
		}

		daddw = i915_gem_object_get_dma_addwess(obj, 0);
		if (!IS_AWIGNED(daddw, ps)) {
			pw_eww("%s daddw(%pa) not awigned with ps(%u)\n",
			       __func__, &daddw, ps);
			eww = -EINVAW;
			goto out_unpin;
		}

out_unpin:
		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj);
out_put:
		i915_gem_object_unwock(obj);
		i915_gem_object_put(obj);

		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int igt_wmem_cweate_cweawed_cpu(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	u32 size, i;
	int eww;

	i915_gem_dwain_fweed_objects(i915);

	size = max_t(u32, PAGE_SIZE, i915_pwandom_u32_max_state(SZ_32M, &pwng));
	size = wound_up(size, PAGE_SIZE);
	i = 0;

	do {
		stwuct dwm_i915_gem_object *obj;
		unsigned int fwags;
		u32 dwowd, vaw;
		void *vaddw;

		/*
		 * Awtewnate between cweawed and uncweawed awwocations, whiwe
		 * awso diwtying the pages each time to check that the pages awe
		 * awways cweawed if wequested, since we shouwd get some ovewwap
		 * of the undewwying pages, if not aww, since we awe the onwy
		 * usew.
		 */

		fwags = I915_BO_AWWOC_CPU_CWEAW;
		if (i & 1)
			fwags = 0;

		obj = i915_gem_object_cweate_wmem(i915, size, fwags);
		if (IS_EWW(obj))
			wetuwn PTW_EWW(obj);

		i915_gem_object_wock(obj, NUWW);
		eww = i915_gem_object_pin_pages(obj);
		if (eww)
			goto out_put;

		dwowd = i915_pwandom_u32_max_state(PAGE_SIZE / sizeof(u32),
						   &pwng);

		if (fwags & I915_BO_AWWOC_CPU_CWEAW) {
			eww = igt_cpu_check(obj, dwowd, 0);
			if (eww) {
				pw_eww("%s faiwed with size=%u, fwags=%u\n",
				       __func__, size, fwags);
				goto out_unpin;
			}
		}

		vaddw = i915_gem_object_pin_map(obj, I915_MAP_WC);
		if (IS_EWW(vaddw)) {
			eww = PTW_EWW(vaddw);
			goto out_unpin;
		}

		vaw = pwandom_u32_state(&pwng);

		memset32(vaddw, vaw, obj->base.size / sizeof(u32));

		i915_gem_object_fwush_map(obj);
		i915_gem_object_unpin_map(obj);
out_unpin:
		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj);
out_put:
		i915_gem_object_unwock(obj);
		i915_gem_object_put(obj);

		if (eww)
			bweak;
		++i;
	} whiwe (!__igt_timeout(end_time, NUWW));

	pw_info("%s compweted (%u) itewations\n", __func__, i);

	wetuwn eww;
}

static int igt_wmem_wwite_gpu(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_gem_context *ctx;
	stwuct fiwe *fiwe;
	I915_WND_STATE(pwng);
	u32 sz;
	int eww;

	fiwe = mock_fiwe(i915);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	ctx = wive_context(i915, fiwe);
	if (IS_EWW(ctx)) {
		eww = PTW_EWW(ctx);
		goto out_fiwe;
	}

	sz = wound_up(pwandom_u32_state(&pwng) % SZ_32M, PAGE_SIZE);

	obj = i915_gem_object_cweate_wmem(i915, sz, 0);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto out_fiwe;
	}

	eww = i915_gem_object_pin_pages_unwocked(obj);
	if (eww)
		goto out_put;

	eww = igt_gpu_wwite(ctx, obj);
	if (eww)
		pw_eww("igt_gpu_wwite faiwed(%d)\n", eww);

	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);
out_fiwe:
	fput(fiwe);
	wetuwn eww;
}

static stwuct intew_engine_cs *
wandom_engine_cwass(stwuct dwm_i915_pwivate *i915,
		    unsigned int cwass,
		    stwuct wnd_state *pwng)
{
	stwuct intew_engine_cs *engine;
	unsigned int count;

	count = 0;
	fow (engine = intew_engine_wookup_usew(i915, cwass, 0);
	     engine && engine->uabi_cwass == cwass;
	     engine = wb_entwy_safe(wb_next(&engine->uabi_node),
				    typeof(*engine), uabi_node))
		count++;

	count = i915_pwandom_u32_max_state(count, pwng);
	wetuwn intew_engine_wookup_usew(i915, cwass, count);
}

static int igt_wmem_wwite_cpu(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct dwm_i915_gem_object *obj;
	I915_WND_STATE(pwng);
	IGT_TIMEOUT(end_time);
	u32 bytes[] = {
		0, /* wng pwacehowdew */
		sizeof(u32),
		sizeof(u64),
		64, /* cw */
		PAGE_SIZE,
		PAGE_SIZE - sizeof(u32),
		PAGE_SIZE - sizeof(u64),
		PAGE_SIZE - 64,
	};
	stwuct intew_engine_cs *engine;
	stwuct i915_wequest *wq;
	u32 *vaddw;
	u32 sz;
	u32 i;
	int *owdew;
	int count;
	int eww;

	engine = wandom_engine_cwass(i915, I915_ENGINE_CWASS_COPY, &pwng);
	if (!engine)
		wetuwn 0;

	pw_info("%s: using %s\n", __func__, engine->name);

	sz = wound_up(pwandom_u32_state(&pwng) % SZ_32M, PAGE_SIZE);
	sz = max_t(u32, 2 * PAGE_SIZE, sz);

	obj = i915_gem_object_cweate_wmem(i915, sz, I915_BO_AWWOC_CONTIGUOUS);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	vaddw = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		goto out_put;
	}

	i915_gem_object_wock(obj, NUWW);

	eww = dma_wesv_wesewve_fences(obj->base.wesv, 1);
	if (eww) {
		i915_gem_object_unwock(obj);
		goto out_put;
	}

	/* Put the pages into a known state -- fwom the gpu fow added fun */
	intew_engine_pm_get(engine);
	eww = intew_context_migwate_cweaw(engine->gt->migwate.context, NUWW,
					  obj->mm.pages->sgw,
					  i915_gem_get_pat_index(i915,
								 I915_CACHE_NONE),
					  twue, 0xdeadbeaf, &wq);
	if (wq) {
		dma_wesv_add_fence(obj->base.wesv, &wq->fence,
				   DMA_WESV_USAGE_WWITE);
		i915_wequest_put(wq);
	}

	intew_engine_pm_put(engine);
	if (!eww)
		eww = i915_gem_object_set_to_wc_domain(obj, twue);
	i915_gem_object_unwock(obj);
	if (eww)
		goto out_unpin;

	count = AWWAY_SIZE(bytes);
	owdew = i915_wandom_owdew(count * count, &pwng);
	if (!owdew) {
		eww = -ENOMEM;
		goto out_unpin;
	}

	/* A wandom muwtipwe of u32, picked between [64, PAGE_SIZE - 64] */
	bytes[0] = igt_wandom_offset(&pwng, 64, PAGE_SIZE - 64, 0, sizeof(u32));
	GEM_BUG_ON(!IS_AWIGNED(bytes[0], sizeof(u32)));

	i = 0;
	do {
		u32 offset;
		u32 awign;
		u32 dwowd;
		u32 size;
		u32 vaw;

		size = bytes[owdew[i] % count];
		i = (i + 1) % (count * count);

		awign = bytes[owdew[i] % count];
		i = (i + 1) % (count * count);

		awign = max_t(u32, sizeof(u32), wounddown_pow_of_two(awign));

		offset = igt_wandom_offset(&pwng, 0, obj->base.size,
					   size, awign);

		vaw = pwandom_u32_state(&pwng);
		memset32(vaddw + offset / sizeof(u32), vaw ^ 0xdeadbeaf,
			 size / sizeof(u32));

		/*
		 * Sampwe wandom dw -- don't waste pwecious time weading evewy
		 * singwe dw.
		 */
		dwowd = igt_wandom_offset(&pwng, offset,
					  offset + size,
					  sizeof(u32), sizeof(u32));
		dwowd /= sizeof(u32);
		if (vaddw[dwowd] != (vaw ^ 0xdeadbeaf)) {
			pw_eww("%s vaddw[%u]=%u, vaw=%u, size=%u, awign=%u, offset=%u\n",
			       __func__, dwowd, vaddw[dwowd], vaw ^ 0xdeadbeaf,
			       size, awign, offset);
			eww = -EINVAW;
			bweak;
		}
	} whiwe (!__igt_timeout(end_time, NUWW));

out_unpin:
	i915_gem_object_unpin_map(obj);
out_put:
	i915_gem_object_put(obj);

	wetuwn eww;
}

static const chaw *wepw_type(u32 type)
{
	switch (type) {
	case I915_MAP_WB:
		wetuwn "WB";
	case I915_MAP_WC:
		wetuwn "WC";
	}

	wetuwn "";
}

static stwuct dwm_i915_gem_object *
cweate_wegion_fow_mapping(stwuct intew_memowy_wegion *mw, u64 size, u32 type,
			  void **out_addw)
{
	stwuct dwm_i915_gem_object *obj;
	void *addw;

	obj = i915_gem_object_cweate_wegion(mw, size, 0, 0);
	if (IS_EWW(obj)) {
		if (PTW_EWW(obj) == -ENOSPC) /* Stowen memowy */
			wetuwn EWW_PTW(-ENODEV);
		wetuwn obj;
	}

	addw = i915_gem_object_pin_map_unwocked(obj, type);
	if (IS_EWW(addw)) {
		i915_gem_object_put(obj);
		if (PTW_EWW(addw) == -ENXIO)
			wetuwn EWW_PTW(-ENODEV);
		wetuwn addw;
	}

	*out_addw = addw;
	wetuwn obj;
}

static int wwap_ktime_compawe(const void *A, const void *B)
{
	const ktime_t *a = A, *b = B;

	wetuwn ktime_compawe(*a, *b);
}

static void igt_memcpy_wong(void *dst, const void *swc, size_t size)
{
	unsigned wong *tmp = dst;
	const unsigned wong *s = swc;

	size = size / sizeof(unsigned wong);
	whiwe (size--)
		*tmp++ = *s++;
}

static inwine void igt_memcpy(void *dst, const void *swc, size_t size)
{
	memcpy(dst, swc, size);
}

static inwine void igt_memcpy_fwom_wc(void *dst, const void *swc, size_t size)
{
	i915_memcpy_fwom_wc(dst, swc, size);
}

static int _pewf_memcpy(stwuct intew_memowy_wegion *swc_mw,
			stwuct intew_memowy_wegion *dst_mw,
			u64 size, u32 swc_type, u32 dst_type)
{
	stwuct dwm_i915_pwivate *i915 = swc_mw->i915;
	const stwuct {
		const chaw *name;
		void (*copy)(void *dst, const void *swc, size_t size);
		boow skip;
	} tests[] = {
		{
			"memcpy",
			igt_memcpy,
		},
		{
			"memcpy_wong",
			igt_memcpy_wong,
		},
		{
			"memcpy_fwom_wc",
			igt_memcpy_fwom_wc,
			!i915_has_memcpy_fwom_wc(),
		},
	};
	stwuct dwm_i915_gem_object *swc, *dst;
	void *swc_addw, *dst_addw;
	int wet = 0;
	int i;

	swc = cweate_wegion_fow_mapping(swc_mw, size, swc_type, &swc_addw);
	if (IS_EWW(swc)) {
		wet = PTW_EWW(swc);
		goto out;
	}

	dst = cweate_wegion_fow_mapping(dst_mw, size, dst_type, &dst_addw);
	if (IS_EWW(dst)) {
		wet = PTW_EWW(dst);
		goto out_unpin_swc;
	}

	fow (i = 0; i < AWWAY_SIZE(tests); ++i) {
		ktime_t t[5];
		int pass;

		if (tests[i].skip)
			continue;

		fow (pass = 0; pass < AWWAY_SIZE(t); pass++) {
			ktime_t t0, t1;

			t0 = ktime_get();

			tests[i].copy(dst_addw, swc_addw, size);

			t1 = ktime_get();
			t[pass] = ktime_sub(t1, t0);
		}

		sowt(t, AWWAY_SIZE(t), sizeof(*t), wwap_ktime_compawe, NUWW);
		if (t[0] <= 0) {
			/* ignowe the impossibwe to pwotect ouw sanity */
			pw_debug("Skipping %s swc(%s, %s) -> dst(%s, %s) %14s %4wwuKiB copy, unstabwe measuwement [%wwd, %wwd]\n",
				 __func__,
				 swc_mw->name, wepw_type(swc_type),
				 dst_mw->name, wepw_type(dst_type),
				 tests[i].name, size >> 10,
				 t[0], t[4]);
			continue;
		}

		pw_info("%s swc(%s, %s) -> dst(%s, %s) %14s %4wwu KiB copy: %5wwd MiB/s\n",
			__func__,
			swc_mw->name, wepw_type(swc_type),
			dst_mw->name, wepw_type(dst_type),
			tests[i].name, size >> 10,
			div64_u64(muw_u32_u32(4 * size,
					      1000 * 1000 * 1000),
				  t[1] + 2 * t[2] + t[3]) >> 20);

		cond_wesched();
	}

	i915_gem_object_unpin_map(dst);
	i915_gem_object_put(dst);
out_unpin_swc:
	i915_gem_object_unpin_map(swc);
	i915_gem_object_put(swc);

	i915_gem_dwain_fweed_objects(i915);
out:
	if (wet == -ENODEV)
		wet = 0;

	wetuwn wet;
}

static int pewf_memcpy(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	static const u32 types[] = {
		I915_MAP_WB,
		I915_MAP_WC,
	};
	static const u32 sizes[] = {
		SZ_4K,
		SZ_64K,
		SZ_4M,
	};
	stwuct intew_memowy_wegion *swc_mw, *dst_mw;
	int swc_id, dst_id;
	int i, j, k;
	int wet;

	fow_each_memowy_wegion(swc_mw, i915, swc_id) {
		fow_each_memowy_wegion(dst_mw, i915, dst_id) {
			fow (i = 0; i < AWWAY_SIZE(sizes); ++i) {
				fow (j = 0; j < AWWAY_SIZE(types); ++j) {
					fow (k = 0; k < AWWAY_SIZE(types); ++k) {
						wet = _pewf_memcpy(swc_mw,
								   dst_mw,
								   sizes[i],
								   types[j],
								   types[k]);
						if (wet)
							wetuwn wet;
					}
				}
			}
		}
	}

	wetuwn 0;
}

int intew_memowy_wegion_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_mock_wesewve),
		SUBTEST(igt_mock_fiww),
		SUBTEST(igt_mock_contiguous),
		SUBTEST(igt_mock_spwintewed_wegion),
		SUBTEST(igt_mock_max_segment),
		SUBTEST(igt_mock_io_size),
	};
	stwuct intew_memowy_wegion *mem;
	stwuct dwm_i915_pwivate *i915;
	int eww;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	mem = mock_wegion_cweate(i915, 0, SZ_2G, I915_GTT_PAGE_SIZE_4K, 0, 0);
	if (IS_EWW(mem)) {
		pw_eww("faiwed to cweate memowy wegion\n");
		eww = PTW_EWW(mem);
		goto out_unwef;
	}

	eww = i915_subtests(tests, mem);

	intew_memowy_wegion_destwoy(mem);
out_unwef:
	mock_destwoy_device(i915);
	wetuwn eww;
}

int intew_memowy_wegion_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_wmem_cweate),
		SUBTEST(igt_wmem_cweate_with_ps),
		SUBTEST(igt_wmem_cweate_cweawed_cpu),
		SUBTEST(igt_wmem_wwite_cpu),
		SUBTEST(igt_wmem_wwite_gpu),
	};

	if (!HAS_WMEM(i915)) {
		pw_info("device wacks WMEM suppowt, skipping\n");
		wetuwn 0;
	}

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn i915_wive_subtests(tests, i915);
}

int intew_memowy_wegion_pewf_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(pewf_memcpy),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn i915_wive_subtests(tests, i915);
}
