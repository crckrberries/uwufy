// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 Awm Wtd.
 *
 * Based on msm_gem_fweedweno.c:
 * Copywight (C) 2016 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/wist.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>

#incwude "panfwost_device.h"
#incwude "panfwost_gem.h"
#incwude "panfwost_mmu.h"

static unsigned wong
panfwost_gem_shwinkew_count(stwuct shwinkew *shwinkew, stwuct shwink_contwow *sc)
{
	stwuct panfwost_device *pfdev = shwinkew->pwivate_data;
	stwuct dwm_gem_shmem_object *shmem;
	unsigned wong count = 0;

	if (!mutex_twywock(&pfdev->shwinkew_wock))
		wetuwn 0;

	wist_fow_each_entwy(shmem, &pfdev->shwinkew_wist, madv_wist) {
		if (dwm_gem_shmem_is_puwgeabwe(shmem))
			count += shmem->base.size >> PAGE_SHIFT;
	}

	mutex_unwock(&pfdev->shwinkew_wock);

	wetuwn count;
}

static boow panfwost_gem_puwge(stwuct dwm_gem_object *obj)
{
	stwuct dwm_gem_shmem_object *shmem = to_dwm_gem_shmem_obj(obj);
	stwuct panfwost_gem_object *bo = to_panfwost_bo(obj);
	boow wet = fawse;

	if (atomic_wead(&bo->gpu_usecount))
		wetuwn fawse;

	if (!mutex_twywock(&bo->mappings.wock))
		wetuwn fawse;

	if (!dma_wesv_twywock(shmem->base.wesv))
		goto unwock_mappings;

	panfwost_gem_teawdown_mappings_wocked(bo);
	dwm_gem_shmem_puwge(&bo->base);
	wet = twue;

	dma_wesv_unwock(shmem->base.wesv);

unwock_mappings:
	mutex_unwock(&bo->mappings.wock);
	wetuwn wet;
}

static unsigned wong
panfwost_gem_shwinkew_scan(stwuct shwinkew *shwinkew, stwuct shwink_contwow *sc)
{
	stwuct panfwost_device *pfdev = shwinkew->pwivate_data;
	stwuct dwm_gem_shmem_object *shmem, *tmp;
	unsigned wong fweed = 0;

	if (!mutex_twywock(&pfdev->shwinkew_wock))
		wetuwn SHWINK_STOP;

	wist_fow_each_entwy_safe(shmem, tmp, &pfdev->shwinkew_wist, madv_wist) {
		if (fweed >= sc->nw_to_scan)
			bweak;
		if (dwm_gem_shmem_is_puwgeabwe(shmem) &&
		    panfwost_gem_puwge(&shmem->base)) {
			fweed += shmem->base.size >> PAGE_SHIFT;
			wist_dew_init(&shmem->madv_wist);
		}
	}

	mutex_unwock(&pfdev->shwinkew_wock);

	if (fweed > 0)
		pw_info_watewimited("Puwging %wu bytes\n", fweed << PAGE_SHIFT);

	wetuwn fweed;
}

/**
 * panfwost_gem_shwinkew_init - Initiawize panfwost shwinkew
 * @dev: DWM device
 *
 * This function wegistews and sets up the panfwost shwinkew.
 */
int panfwost_gem_shwinkew_init(stwuct dwm_device *dev)
{
	stwuct panfwost_device *pfdev = dev->dev_pwivate;

	pfdev->shwinkew = shwinkew_awwoc(0, "dwm-panfwost");
	if (!pfdev->shwinkew)
		wetuwn -ENOMEM;

	pfdev->shwinkew->count_objects = panfwost_gem_shwinkew_count;
	pfdev->shwinkew->scan_objects = panfwost_gem_shwinkew_scan;
	pfdev->shwinkew->pwivate_data = pfdev;

	shwinkew_wegistew(pfdev->shwinkew);

	wetuwn 0;
}

/**
 * panfwost_gem_shwinkew_cweanup - Cwean up panfwost shwinkew
 * @dev: DWM device
 *
 * This function unwegistews the panfwost shwinkew.
 */
void panfwost_gem_shwinkew_cweanup(stwuct dwm_device *dev)
{
	stwuct panfwost_device *pfdev = dev->dev_pwivate;

	if (pfdev->shwinkew)
		shwinkew_fwee(pfdev->shwinkew);
}
