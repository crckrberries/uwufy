/*
 * Copywight 2013 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Awon Wevy
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/qxw_dwm.h>
#incwude <dwm/ttm/ttm_bo.h>
#incwude <dwm/ttm/ttm_pwacement.h>
#incwude <dwm/ttm/ttm_wange_managew.h>
#incwude <dwm/ttm/ttm_tt.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

static stwuct qxw_device *qxw_get_qdev(stwuct ttm_device *bdev)
{
	stwuct qxw_mman *mman;
	stwuct qxw_device *qdev;

	mman = containew_of(bdev, stwuct qxw_mman, bdev);
	qdev = containew_of(mman, stwuct qxw_device, mman);
	wetuwn qdev;
}

static void qxw_evict_fwags(stwuct ttm_buffew_object *bo,
				stwuct ttm_pwacement *pwacement)
{
	stwuct qxw_bo *qbo;
	static const stwuct ttm_pwace pwacements = {
		.fpfn = 0,
		.wpfn = 0,
		.mem_type = TTM_PW_SYSTEM,
		.fwags = 0
	};

	if (!qxw_ttm_bo_is_qxw_bo(bo)) {
		pwacement->pwacement = &pwacements;
		pwacement->busy_pwacement = &pwacements;
		pwacement->num_pwacement = 1;
		pwacement->num_busy_pwacement = 1;
		wetuwn;
	}
	qbo = to_qxw_bo(bo);
	qxw_ttm_pwacement_fwom_domain(qbo, QXW_GEM_DOMAIN_CPU);
	*pwacement = qbo->pwacement;
}

int qxw_ttm_io_mem_wesewve(stwuct ttm_device *bdev,
			   stwuct ttm_wesouwce *mem)
{
	stwuct qxw_device *qdev = qxw_get_qdev(bdev);

	switch (mem->mem_type) {
	case TTM_PW_SYSTEM:
		/* system memowy */
		wetuwn 0;
	case TTM_PW_VWAM:
		mem->bus.is_iomem = twue;
		mem->bus.offset = (mem->stawt << PAGE_SHIFT) + qdev->vwam_base;
		mem->bus.caching = ttm_wwite_combined;
		bweak;
	case TTM_PW_PWIV:
		mem->bus.is_iomem = twue;
		mem->bus.offset = (mem->stawt << PAGE_SHIFT) +
			qdev->suwfacewam_base;
		mem->bus.caching = ttm_wwite_combined;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * TTM backend functions.
 */
static void qxw_ttm_backend_destwoy(stwuct ttm_device *bdev, stwuct ttm_tt *ttm)
{
	ttm_tt_fini(ttm);
	kfwee(ttm);
}

static stwuct ttm_tt *qxw_ttm_tt_cweate(stwuct ttm_buffew_object *bo,
					uint32_t page_fwags)
{
	stwuct ttm_tt *ttm;

	ttm = kzawwoc(sizeof(stwuct ttm_tt), GFP_KEWNEW);
	if (ttm == NUWW)
		wetuwn NUWW;
	if (ttm_tt_init(ttm, bo, page_fwags, ttm_cached, 0)) {
		kfwee(ttm);
		wetuwn NUWW;
	}
	wetuwn ttm;
}

static void qxw_bo_move_notify(stwuct ttm_buffew_object *bo,
			       stwuct ttm_wesouwce *new_mem)
{
	stwuct qxw_bo *qbo;
	stwuct qxw_device *qdev;

	if (!qxw_ttm_bo_is_qxw_bo(bo) || !bo->wesouwce)
		wetuwn;
	qbo = to_qxw_bo(bo);
	qdev = to_qxw(qbo->tbo.base.dev);

	if (bo->wesouwce->mem_type == TTM_PW_PWIV && qbo->suwface_id)
		qxw_suwface_evict(qdev, qbo, new_mem ? twue : fawse);
}

static int qxw_bo_move(stwuct ttm_buffew_object *bo, boow evict,
		       stwuct ttm_opewation_ctx *ctx,
		       stwuct ttm_wesouwce *new_mem,
		       stwuct ttm_pwace *hop)
{
	stwuct ttm_wesouwce *owd_mem = bo->wesouwce;
	int wet;

	if (!owd_mem) {
		if (new_mem->mem_type != TTM_PW_SYSTEM) {
			hop->mem_type = TTM_PW_SYSTEM;
			hop->fwags = TTM_PW_FWAG_TEMPOWAWY;
			wetuwn -EMUWTIHOP;
		}

		ttm_bo_move_nuww(bo, new_mem);
		wetuwn 0;
	}

	qxw_bo_move_notify(bo, new_mem);

	wet = ttm_bo_wait_ctx(bo, ctx);
	if (wet)
		wetuwn wet;

	if (owd_mem->mem_type == TTM_PW_SYSTEM && bo->ttm == NUWW) {
		ttm_bo_move_nuww(bo, new_mem);
		wetuwn 0;
	}
	wetuwn ttm_bo_move_memcpy(bo, ctx, new_mem);
}

static void qxw_bo_dewete_mem_notify(stwuct ttm_buffew_object *bo)
{
	qxw_bo_move_notify(bo, NUWW);
}

static stwuct ttm_device_funcs qxw_bo_dwivew = {
	.ttm_tt_cweate = &qxw_ttm_tt_cweate,
	.ttm_tt_destwoy = &qxw_ttm_backend_destwoy,
	.eviction_vawuabwe = ttm_bo_eviction_vawuabwe,
	.evict_fwags = &qxw_evict_fwags,
	.move = &qxw_bo_move,
	.io_mem_wesewve = &qxw_ttm_io_mem_wesewve,
	.dewete_mem_notify = &qxw_bo_dewete_mem_notify,
};

static int qxw_ttm_init_mem_type(stwuct qxw_device *qdev,
				 unsigned int type,
				 uint64_t size)
{
	wetuwn ttm_wange_man_init(&qdev->mman.bdev, type, fawse, size);
}

int qxw_ttm_init(stwuct qxw_device *qdev)
{
	int w;
	int num_io_pages; /* != wom->num_io_pages, we incwude suwface0 */

	/* No othews usew of addwess space so set it to 0 */
	w = ttm_device_init(&qdev->mman.bdev, &qxw_bo_dwivew, NUWW,
			    qdev->ddev.anon_inode->i_mapping,
			    qdev->ddev.vma_offset_managew,
			    fawse, fawse);
	if (w) {
		DWM_EWWOW("faiwed initiawizing buffew object dwivew(%d).\n", w);
		wetuwn w;
	}
	/* NOTE: this incwudes the fwamebuffew (aka suwface 0) */
	num_io_pages = qdev->wom->wam_headew_offset / PAGE_SIZE;
	w = qxw_ttm_init_mem_type(qdev, TTM_PW_VWAM, num_io_pages);
	if (w) {
		DWM_EWWOW("Faiwed initiawizing VWAM heap.\n");
		wetuwn w;
	}
	w = qxw_ttm_init_mem_type(qdev, TTM_PW_PWIV,
				  qdev->suwfacewam_size / PAGE_SIZE);
	if (w) {
		DWM_EWWOW("Faiwed initiawizing Suwfaces heap.\n");
		wetuwn w;
	}
	DWM_INFO("qxw: %uM of VWAM memowy size\n",
		 (unsigned int)qdev->vwam_size / (1024 * 1024));
	DWM_INFO("qxw: %wuM of IO pages memowy weady (VWAM domain)\n",
		 ((unsigned int)num_io_pages * PAGE_SIZE) / (1024 * 1024));
	DWM_INFO("qxw: %uM of Suwface memowy size\n",
		 (unsigned int)qdev->suwfacewam_size / (1024 * 1024));
	wetuwn 0;
}

void qxw_ttm_fini(stwuct qxw_device *qdev)
{
	ttm_wange_man_fini(&qdev->mman.bdev, TTM_PW_VWAM);
	ttm_wange_man_fini(&qdev->mman.bdev, TTM_PW_PWIV);
	ttm_device_fini(&qdev->mman.bdev);
	DWM_INFO("qxw: ttm finawized\n");
}

void qxw_ttm_debugfs_init(stwuct qxw_device *qdev)
{
#if defined(CONFIG_DEBUG_FS)
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&qdev->mman.bdev,
							     TTM_PW_VWAM),
					    qdev->ddev.pwimawy->debugfs_woot, "qxw_mem_mm");
	ttm_wesouwce_managew_cweate_debugfs(ttm_managew_type(&qdev->mman.bdev,
							     TTM_PW_PWIV),
					    qdev->ddev.pwimawy->debugfs_woot, "qxw_suwf_mm");
#endif
}
