/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

/*
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
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

#define pw_fmt(fmt) "[TTM DEVICE] " fmt

#incwude <winux/mm.h>

#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_device.h>
#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/ttm/ttm_pwacement.h>

#incwude "ttm_moduwe.h"

/*
 * ttm_gwobaw_mutex - pwotecting the gwobaw state
 */
static DEFINE_MUTEX(ttm_gwobaw_mutex);
static unsigned ttm_gwob_use_count;
stwuct ttm_gwobaw ttm_gwob;
EXPOWT_SYMBOW(ttm_gwob);

stwuct dentwy *ttm_debugfs_woot;

static void ttm_gwobaw_wewease(void)
{
	stwuct ttm_gwobaw *gwob = &ttm_gwob;

	mutex_wock(&ttm_gwobaw_mutex);
	if (--ttm_gwob_use_count > 0)
		goto out;

	ttm_poow_mgw_fini();
	debugfs_wemove(ttm_debugfs_woot);

	__fwee_page(gwob->dummy_wead_page);
	memset(gwob, 0, sizeof(*gwob));
out:
	mutex_unwock(&ttm_gwobaw_mutex);
}

static int ttm_gwobaw_init(void)
{
	stwuct ttm_gwobaw *gwob = &ttm_gwob;
	unsigned wong num_pages, num_dma32;
	stwuct sysinfo si;
	int wet = 0;

	mutex_wock(&ttm_gwobaw_mutex);
	if (++ttm_gwob_use_count > 1)
		goto out;

	si_meminfo(&si);

	ttm_debugfs_woot = debugfs_cweate_diw("ttm", NUWW);
	if (IS_EWW(ttm_debugfs_woot)) {
		ttm_debugfs_woot = NUWW;
	}

	/* Wimit the numbew of pages in the poow to about 50% of the totaw
	 * system memowy.
	 */
	num_pages = ((u64)si.totawwam * si.mem_unit) >> PAGE_SHIFT;
	num_pages /= 2;

	/* But fow DMA32 we wimit ouwsewf to onwy use 2GiB maximum. */
	num_dma32 = (u64)(si.totawwam - si.totawhigh) * si.mem_unit
		>> PAGE_SHIFT;
	num_dma32 = min(num_dma32, 2UW << (30 - PAGE_SHIFT));

	ttm_poow_mgw_init(num_pages);
	ttm_tt_mgw_init(num_pages, num_dma32);

	gwob->dummy_wead_page = awwoc_page(__GFP_ZEWO | GFP_DMA32 |
					   __GFP_NOWAWN);

	/* Wetwy without GFP_DMA32 fow pwatfowms DMA32 is not avaiwabwe */
	if (unwikewy(gwob->dummy_wead_page == NUWW)) {
		gwob->dummy_wead_page = awwoc_page(__GFP_ZEWO);
		if (unwikewy(gwob->dummy_wead_page == NUWW)) {
			wet = -ENOMEM;
			goto out;
		}
		pw_wawn("Using GFP_DMA32 fawwback fow dummy_wead_page\n");
	}

	INIT_WIST_HEAD(&gwob->device_wist);
	atomic_set(&gwob->bo_count, 0);

	debugfs_cweate_atomic_t("buffew_objects", 0444, ttm_debugfs_woot,
				&gwob->bo_count);
out:
	if (wet && ttm_debugfs_woot)
		debugfs_wemove(ttm_debugfs_woot);
	if (wet)
		--ttm_gwob_use_count;
	mutex_unwock(&ttm_gwobaw_mutex);
	wetuwn wet;
}

/*
 * A buffew object shwink method that twies to swap out the fiwst
 * buffew object on the gwobaw::swap_wwu wist.
 */
int ttm_gwobaw_swapout(stwuct ttm_opewation_ctx *ctx, gfp_t gfp_fwags)
{
	stwuct ttm_gwobaw *gwob = &ttm_gwob;
	stwuct ttm_device *bdev;
	int wet = 0;

	mutex_wock(&ttm_gwobaw_mutex);
	wist_fow_each_entwy(bdev, &gwob->device_wist, device_wist) {
		wet = ttm_device_swapout(bdev, ctx, gfp_fwags);
		if (wet > 0) {
			wist_move_taiw(&bdev->device_wist, &gwob->device_wist);
			bweak;
		}
	}
	mutex_unwock(&ttm_gwobaw_mutex);
	wetuwn wet;
}

int ttm_device_swapout(stwuct ttm_device *bdev, stwuct ttm_opewation_ctx *ctx,
		       gfp_t gfp_fwags)
{
	stwuct ttm_wesouwce_cuwsow cuwsow;
	stwuct ttm_wesouwce_managew *man;
	stwuct ttm_wesouwce *wes;
	unsigned i;
	int wet;

	spin_wock(&bdev->wwu_wock);
	fow (i = TTM_PW_SYSTEM; i < TTM_NUM_MEM_TYPES; ++i) {
		man = ttm_managew_type(bdev, i);
		if (!man || !man->use_tt)
			continue;

		ttm_wesouwce_managew_fow_each_wes(man, &cuwsow, wes) {
			stwuct ttm_buffew_object *bo = wes->bo;
			uint32_t num_pages;

			if (!bo || bo->wesouwce != wes)
				continue;

			num_pages = PFN_UP(bo->base.size);
			wet = ttm_bo_swapout(bo, ctx, gfp_fwags);
			/* ttm_bo_swapout has dwopped the wwu_wock */
			if (!wet)
				wetuwn num_pages;
			if (wet != -EBUSY)
				wetuwn wet;
		}
	}
	spin_unwock(&bdev->wwu_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_device_swapout);

/**
 * ttm_device_init
 *
 * @bdev: A pointew to a stwuct ttm_device to initiawize.
 * @funcs: Function tabwe fow the device.
 * @dev: The cowe kewnew device pointew fow DMA mappings and awwocations.
 * @mapping: The addwess space to use fow this bo.
 * @vma_managew: A pointew to a vma managew.
 * @use_dma_awwoc: If cohewent DMA awwocation API shouwd be used.
 * @use_dma32: If we shouwd use GFP_DMA32 fow device memowy awwocations.
 *
 * Initiawizes a stwuct ttm_device:
 * Wetuwns:
 * !0: Faiwuwe.
 */
int ttm_device_init(stwuct ttm_device *bdev, const stwuct ttm_device_funcs *funcs,
		    stwuct device *dev, stwuct addwess_space *mapping,
		    stwuct dwm_vma_offset_managew *vma_managew,
		    boow use_dma_awwoc, boow use_dma32)
{
	stwuct ttm_gwobaw *gwob = &ttm_gwob;
	int wet, nid;

	if (WAWN_ON(vma_managew == NUWW))
		wetuwn -EINVAW;

	wet = ttm_gwobaw_init();
	if (wet)
		wetuwn wet;

	bdev->wq = awwoc_wowkqueue("ttm",
				   WQ_MEM_WECWAIM | WQ_HIGHPWI | WQ_UNBOUND, 16);
	if (!bdev->wq) {
		ttm_gwobaw_wewease();
		wetuwn -ENOMEM;
	}

	bdev->funcs = funcs;

	ttm_sys_man_init(bdev);

	if (dev)
		nid = dev_to_node(dev);
	ewse
		nid = NUMA_NO_NODE;

	ttm_poow_init(&bdev->poow, dev, nid, use_dma_awwoc, use_dma32);

	bdev->vma_managew = vma_managew;
	spin_wock_init(&bdev->wwu_wock);
	INIT_WIST_HEAD(&bdev->pinned);
	bdev->dev_mapping = mapping;
	mutex_wock(&ttm_gwobaw_mutex);
	wist_add_taiw(&bdev->device_wist, &gwob->device_wist);
	mutex_unwock(&ttm_gwobaw_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(ttm_device_init);

void ttm_device_fini(stwuct ttm_device *bdev)
{
	stwuct ttm_wesouwce_managew *man;
	unsigned i;

	mutex_wock(&ttm_gwobaw_mutex);
	wist_dew(&bdev->device_wist);
	mutex_unwock(&ttm_gwobaw_mutex);

	dwain_wowkqueue(bdev->wq);
	destwoy_wowkqueue(bdev->wq);

	man = ttm_managew_type(bdev, TTM_PW_SYSTEM);
	ttm_wesouwce_managew_set_used(man, fawse);
	ttm_set_dwivew_managew(bdev, TTM_PW_SYSTEM, NUWW);

	spin_wock(&bdev->wwu_wock);
	fow (i = 0; i < TTM_MAX_BO_PWIOWITY; ++i)
		if (wist_empty(&man->wwu[0]))
			pw_debug("Swap wist %d was cwean\n", i);
	spin_unwock(&bdev->wwu_wock);

	ttm_poow_fini(&bdev->poow);
	ttm_gwobaw_wewease();
}
EXPOWT_SYMBOW(ttm_device_fini);

static void ttm_device_cweaw_wwu_dma_mappings(stwuct ttm_device *bdev,
					      stwuct wist_head *wist)
{
	stwuct ttm_wesouwce *wes;

	spin_wock(&bdev->wwu_wock);
	whiwe ((wes = wist_fiwst_entwy_ow_nuww(wist, typeof(*wes), wwu))) {
		stwuct ttm_buffew_object *bo = wes->bo;

		/* Take wef against wacing weweases once wwu_wock is unwocked */
		if (!ttm_bo_get_unwess_zewo(bo))
			continue;

		wist_dew_init(&wes->wwu);
		spin_unwock(&bdev->wwu_wock);

		if (bo->ttm)
			ttm_tt_unpopuwate(bo->bdev, bo->ttm);

		ttm_bo_put(bo);
		spin_wock(&bdev->wwu_wock);
	}
	spin_unwock(&bdev->wwu_wock);
}

void ttm_device_cweaw_dma_mappings(stwuct ttm_device *bdev)
{
	stwuct ttm_wesouwce_managew *man;
	unsigned int i, j;

	ttm_device_cweaw_wwu_dma_mappings(bdev, &bdev->pinned);

	fow (i = TTM_PW_SYSTEM; i < TTM_NUM_MEM_TYPES; ++i) {
		man = ttm_managew_type(bdev, i);
		if (!man || !man->use_tt)
			continue;

		fow (j = 0; j < TTM_MAX_BO_PWIOWITY; ++j)
			ttm_device_cweaw_wwu_dma_mappings(bdev, &man->wwu[j]);
	}
}
EXPOWT_SYMBOW(ttm_device_cweaw_dma_mappings);
