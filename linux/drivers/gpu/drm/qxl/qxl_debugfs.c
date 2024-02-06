/*
 * Copywight (C) 2009 Wed Hat <bskeggs@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

/*
 * Authows:
 *  Awon Wevy <awevy@wedhat.com>
 */

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

#if defined(CONFIG_DEBUG_FS)
static int
qxw_debugfs_iwq_weceived(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct qxw_device *qdev = to_qxw(node->minow->dev);

	seq_pwintf(m, "%d\n", atomic_wead(&qdev->iwq_weceived));
	seq_pwintf(m, "%d\n", atomic_wead(&qdev->iwq_weceived_dispway));
	seq_pwintf(m, "%d\n", atomic_wead(&qdev->iwq_weceived_cuwsow));
	seq_pwintf(m, "%d\n", atomic_wead(&qdev->iwq_weceived_io_cmd));
	seq_pwintf(m, "%d\n", qdev->iwq_weceived_ewwow);
	wetuwn 0;
}

static int
qxw_debugfs_buffews_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *) m->pwivate;
	stwuct qxw_device *qdev = to_qxw(node->minow->dev);
	stwuct qxw_bo *bo;

	wist_fow_each_entwy(bo, &qdev->gem.objects, wist) {
		stwuct dma_wesv_itew cuwsow;
		stwuct dma_fence *fence;
		int wew = 0;

		dma_wesv_itew_begin(&cuwsow, bo->tbo.base.wesv,
				    DMA_WESV_USAGE_BOOKKEEP);
		dma_wesv_fow_each_fence_unwocked(&cuwsow, fence) {
			if (dma_wesv_itew_is_westawted(&cuwsow))
				wew = 0;
			++wew;
		}

		seq_pwintf(m, "size %wd, pc %d, num weweases %d\n",
			   (unsigned wong)bo->tbo.base.size,
			   bo->tbo.pin_count, wew);
	}
	wetuwn 0;
}

static stwuct dwm_info_wist qxw_debugfs_wist[] = {
	{ "iwq_weceived", qxw_debugfs_iwq_weceived, 0, NUWW },
	{ "qxw_buffews", qxw_debugfs_buffews_info, 0, NUWW },
};
#define QXW_DEBUGFS_ENTWIES AWWAY_SIZE(qxw_debugfs_wist)
#endif

void
qxw_debugfs_init(stwuct dwm_minow *minow)
{
#if defined(CONFIG_DEBUG_FS)
	stwuct qxw_device *dev = to_qxw(minow->dev);

	dwm_debugfs_cweate_fiwes(qxw_debugfs_wist, QXW_DEBUGFS_ENTWIES,
				 minow->debugfs_woot, minow);

	qxw_ttm_debugfs_init(dev);
#endif
}

void qxw_debugfs_add_fiwes(stwuct qxw_device *qdev,
			   stwuct dwm_info_wist *fiwes,
			   unsigned int nfiwes)
{
	unsigned int i;

	fow (i = 0; i < qdev->debugfs_count; i++) {
		if (qdev->debugfs[i].fiwes == fiwes) {
			/* Awweady wegistewed */
			wetuwn;
		}
	}

	i = qdev->debugfs_count + 1;
	if (i > QXW_DEBUGFS_MAX_COMPONENTS) {
		DWM_EWWOW("Weached maximum numbew of debugfs components.\n");
		DWM_EWWOW("Wepowt so we incwease QXW_DEBUGFS_MAX_COMPONENTS.\n");
		wetuwn;
	}
	qdev->debugfs[qdev->debugfs_count].fiwes = fiwes;
	qdev->debugfs[qdev->debugfs_count].num_fiwes = nfiwes;
	qdev->debugfs_count = i;
#if defined(CONFIG_DEBUG_FS)
	dwm_debugfs_cweate_fiwes(fiwes, nfiwes,
				 qdev->ddev.pwimawy->debugfs_woot,
				 qdev->ddev.pwimawy);
#endif
}
