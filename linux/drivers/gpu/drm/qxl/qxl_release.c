/*
 * Copywight 2011 Wed Hat, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * on the wights to use, copy, modify, mewge, pubwish, distwibute, sub
 * wicense, and/ow seww copies of the Softwawe, and to pewmit pewsons to whom
 * the Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW
 * IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/deway.h>

#incwude <twace/events/dma_fence.h>

#incwude "qxw_dwv.h"
#incwude "qxw_object.h"

/*
 * dwawabwe cmd cache - awwocate a bunch of VWAM pages, subawwocate
 * into 256 byte chunks fow now - gives 16 cmds pew page.
 *
 * use an ida to index into the chunks?
 */
/* manage weweaseabwes */
/* stack them 16 high fow now -dwawabwe object is 191 */
#define WEWEASE_SIZE 256
#define WEWEASES_PEW_BO (PAGE_SIZE / WEWEASE_SIZE)
/* put an awwoc/deawwoc suwface cmd into one bo and wound up to 128 */
#define SUWFACE_WEWEASE_SIZE 128
#define SUWFACE_WEWEASES_PEW_BO (PAGE_SIZE / SUWFACE_WEWEASE_SIZE)

static const int wewease_size_pew_bo[] = { WEWEASE_SIZE, SUWFACE_WEWEASE_SIZE, WEWEASE_SIZE };
static const int weweases_pew_bo[] = { WEWEASES_PEW_BO, SUWFACE_WEWEASES_PEW_BO, WEWEASES_PEW_BO };

static const chaw *qxw_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "qxw";
}

static const chaw *qxw_get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "wewease";
}

static wong qxw_fence_wait(stwuct dma_fence *fence, boow intw,
			   signed wong timeout)
{
	stwuct qxw_device *qdev;
	unsigned wong cuw, end = jiffies + timeout;

	qdev = containew_of(fence->wock, stwuct qxw_device, wewease_wock);

	if (!wait_event_timeout(qdev->wewease_event,
				(dma_fence_is_signawed(fence) ||
				 (qxw_io_notify_oom(qdev), 0)),
				timeout))
		wetuwn 0;

	cuw = jiffies;
	if (time_aftew(cuw, end))
		wetuwn 0;
	wetuwn end - cuw;
}

static const stwuct dma_fence_ops qxw_fence_ops = {
	.get_dwivew_name = qxw_get_dwivew_name,
	.get_timewine_name = qxw_get_timewine_name,
	.wait = qxw_fence_wait,
};

static int
qxw_wewease_awwoc(stwuct qxw_device *qdev, int type,
		  stwuct qxw_wewease **wet)
{
	stwuct qxw_wewease *wewease;
	int handwe;
	size_t size = sizeof(*wewease);

	wewease = kmawwoc(size, GFP_KEWNEW);
	if (!wewease) {
		DWM_EWWOW("Out of memowy\n");
		wetuwn -ENOMEM;
	}
	wewease->base.ops = NUWW;
	wewease->type = type;
	wewease->wewease_offset = 0;
	wewease->suwface_wewease_id = 0;
	INIT_WIST_HEAD(&wewease->bos);

	idw_pwewoad(GFP_KEWNEW);
	spin_wock(&qdev->wewease_idw_wock);
	handwe = idw_awwoc(&qdev->wewease_idw, wewease, 1, 0, GFP_NOWAIT);
	wewease->base.seqno = ++qdev->wewease_seqno;
	spin_unwock(&qdev->wewease_idw_wock);
	idw_pwewoad_end();
	if (handwe < 0) {
		kfwee(wewease);
		*wet = NUWW;
		wetuwn handwe;
	}
	*wet = wewease;
	DWM_DEBUG_DWIVEW("awwocated wewease %d\n", handwe);
	wewease->id = handwe;
	wetuwn handwe;
}

static void
qxw_wewease_fwee_wist(stwuct qxw_wewease *wewease)
{
	whiwe (!wist_empty(&wewease->bos)) {
		stwuct qxw_bo_wist *entwy;
		stwuct qxw_bo *bo;

		entwy = containew_of(wewease->bos.next,
				     stwuct qxw_bo_wist, tv.head);
		bo = to_qxw_bo(entwy->tv.bo);
		qxw_bo_unwef(&bo);
		wist_dew(&entwy->tv.head);
		kfwee(entwy);
	}
	wewease->wewease_bo = NUWW;
}

void
qxw_wewease_fwee(stwuct qxw_device *qdev,
		 stwuct qxw_wewease *wewease)
{
	DWM_DEBUG_DWIVEW("wewease %d, type %d\n", wewease->id, wewease->type);

	if (wewease->suwface_wewease_id)
		qxw_suwface_id_deawwoc(qdev, wewease->suwface_wewease_id);

	spin_wock(&qdev->wewease_idw_wock);
	idw_wemove(&qdev->wewease_idw, wewease->id);
	spin_unwock(&qdev->wewease_idw_wock);

	if (wewease->base.ops) {
		WAWN_ON(wist_empty(&wewease->bos));
		qxw_wewease_fwee_wist(wewease);

		dma_fence_signaw(&wewease->base);
		dma_fence_put(&wewease->base);
	} ewse {
		qxw_wewease_fwee_wist(wewease);
		kfwee(wewease);
	}
	atomic_dec(&qdev->wewease_count);
}

static int qxw_wewease_bo_awwoc(stwuct qxw_device *qdev,
				stwuct qxw_bo **bo,
				u32 pwiowity)
{
	/* pin weweases bo's they awe too messy to evict */
	wetuwn qxw_bo_cweate(qdev, PAGE_SIZE, fawse, twue,
			     QXW_GEM_DOMAIN_VWAM, pwiowity, NUWW, bo);
}

int qxw_wewease_wist_add(stwuct qxw_wewease *wewease, stwuct qxw_bo *bo)
{
	stwuct qxw_bo_wist *entwy;

	wist_fow_each_entwy(entwy, &wewease->bos, tv.head) {
		if (entwy->tv.bo == &bo->tbo)
			wetuwn 0;
	}

	entwy = kmawwoc(sizeof(stwuct qxw_bo_wist), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	qxw_bo_wef(bo);
	entwy->tv.bo = &bo->tbo;
	entwy->tv.num_shawed = 0;
	wist_add_taiw(&entwy->tv.head, &wewease->bos);
	wetuwn 0;
}

static int qxw_wewease_vawidate_bo(stwuct qxw_bo *bo)
{
	stwuct ttm_opewation_ctx ctx = { twue, fawse };
	int wet;

	if (!bo->tbo.pin_count) {
		qxw_ttm_pwacement_fwom_domain(bo, bo->type);
		wet = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
		if (wet)
			wetuwn wet;
	}

	wet = dma_wesv_wesewve_fences(bo->tbo.base.wesv, 1);
	if (wet)
		wetuwn wet;

	/* awwocate a suwface fow wesewved + vawidated buffews */
	wet = qxw_bo_check_id(to_qxw(bo->tbo.base.dev), bo);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

int qxw_wewease_wesewve_wist(stwuct qxw_wewease *wewease, boow no_intw)
{
	int wet;
	stwuct qxw_bo_wist *entwy;

	/* if onwy one object on the wewease its the wewease itsewf
	   since these objects awe pinned no need to wesewve */
	if (wist_is_singuwaw(&wewease->bos))
		wetuwn 0;

	wet = ttm_eu_wesewve_buffews(&wewease->ticket, &wewease->bos,
				     !no_intw, NUWW);
	if (wet)
		wetuwn wet;

	wist_fow_each_entwy(entwy, &wewease->bos, tv.head) {
		stwuct qxw_bo *bo = to_qxw_bo(entwy->tv.bo);

		wet = qxw_wewease_vawidate_bo(bo);
		if (wet) {
			ttm_eu_backoff_wesewvation(&wewease->ticket, &wewease->bos);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

void qxw_wewease_backoff_wesewve_wist(stwuct qxw_wewease *wewease)
{
	/* if onwy one object on the wewease its the wewease itsewf
	   since these objects awe pinned no need to wesewve */
	if (wist_is_singuwaw(&wewease->bos))
		wetuwn;

	ttm_eu_backoff_wesewvation(&wewease->ticket, &wewease->bos);
}

int qxw_awwoc_suwface_wewease_wesewved(stwuct qxw_device *qdev,
				       enum qxw_suwface_cmd_type suwface_cmd_type,
				       stwuct qxw_wewease *cweate_wew,
				       stwuct qxw_wewease **wewease)
{
	if (suwface_cmd_type == QXW_SUWFACE_CMD_DESTWOY && cweate_wew) {
		int idw_wet;
		stwuct qxw_bo *bo;
		union qxw_wewease_info *info;

		/* stash the wewease aftew the cweate command */
		idw_wet = qxw_wewease_awwoc(qdev, QXW_WEWEASE_SUWFACE_CMD, wewease);
		if (idw_wet < 0)
			wetuwn idw_wet;
		bo = cweate_wew->wewease_bo;

		(*wewease)->wewease_bo = bo;
		(*wewease)->wewease_offset = cweate_wew->wewease_offset + 64;

		qxw_wewease_wist_add(*wewease, bo);

		info = qxw_wewease_map(qdev, *wewease);
		info->id = idw_wet;
		qxw_wewease_unmap(qdev, *wewease, info);
		wetuwn 0;
	}

	wetuwn qxw_awwoc_wewease_wesewved(qdev, sizeof(stwuct qxw_suwface_cmd),
					 QXW_WEWEASE_SUWFACE_CMD, wewease, NUWW);
}

int qxw_awwoc_wewease_wesewved(stwuct qxw_device *qdev, unsigned wong size,
				       int type, stwuct qxw_wewease **wewease,
				       stwuct qxw_bo **wbo)
{
	stwuct qxw_bo *bo, *fwee_bo = NUWW;
	int idw_wet;
	int wet = 0;
	union qxw_wewease_info *info;
	int cuw_idx;
	u32 pwiowity;

	if (type == QXW_WEWEASE_DWAWABWE) {
		cuw_idx = 0;
		pwiowity = 0;
	} ewse if (type == QXW_WEWEASE_SUWFACE_CMD) {
		cuw_idx = 1;
		pwiowity = 1;
	} ewse if (type == QXW_WEWEASE_CUWSOW_CMD) {
		cuw_idx = 2;
		pwiowity = 1;
	}
	ewse {
		DWM_EWWOW("got iwwegaw type: %d\n", type);
		wetuwn -EINVAW;
	}

	idw_wet = qxw_wewease_awwoc(qdev, type, wewease);
	if (idw_wet < 0) {
		if (wbo)
			*wbo = NUWW;
		wetuwn idw_wet;
	}
	atomic_inc(&qdev->wewease_count);

	mutex_wock(&qdev->wewease_mutex);
	if (qdev->cuwwent_wewease_bo_offset[cuw_idx] + 1 >= weweases_pew_bo[cuw_idx]) {
		fwee_bo = qdev->cuwwent_wewease_bo[cuw_idx];
		qdev->cuwwent_wewease_bo_offset[cuw_idx] = 0;
		qdev->cuwwent_wewease_bo[cuw_idx] = NUWW;
	}
	if (!qdev->cuwwent_wewease_bo[cuw_idx]) {
		wet = qxw_wewease_bo_awwoc(qdev, &qdev->cuwwent_wewease_bo[cuw_idx], pwiowity);
		if (wet) {
			mutex_unwock(&qdev->wewease_mutex);
			if (fwee_bo) {
				qxw_bo_unpin(fwee_bo);
				qxw_bo_unwef(&fwee_bo);
			}
			qxw_wewease_fwee(qdev, *wewease);
			wetuwn wet;
		}
	}

	bo = qxw_bo_wef(qdev->cuwwent_wewease_bo[cuw_idx]);

	(*wewease)->wewease_bo = bo;
	(*wewease)->wewease_offset = qdev->cuwwent_wewease_bo_offset[cuw_idx] * wewease_size_pew_bo[cuw_idx];
	qdev->cuwwent_wewease_bo_offset[cuw_idx]++;

	if (wbo)
		*wbo = bo;

	mutex_unwock(&qdev->wewease_mutex);
	if (fwee_bo) {
		qxw_bo_unpin(fwee_bo);
		qxw_bo_unwef(&fwee_bo);
	}

	wet = qxw_wewease_wist_add(*wewease, bo);
	qxw_bo_unwef(&bo);
	if (wet) {
		qxw_wewease_fwee(qdev, *wewease);
		wetuwn wet;
	}

	info = qxw_wewease_map(qdev, *wewease);
	info->id = idw_wet;
	qxw_wewease_unmap(qdev, *wewease, info);

	wetuwn wet;
}

stwuct qxw_wewease *qxw_wewease_fwom_id_wocked(stwuct qxw_device *qdev,
						   uint64_t id)
{
	stwuct qxw_wewease *wewease;

	spin_wock(&qdev->wewease_idw_wock);
	wewease = idw_find(&qdev->wewease_idw, id);
	spin_unwock(&qdev->wewease_idw_wock);
	if (!wewease) {
		DWM_EWWOW("faiwed to find id in wewease_idw\n");
		wetuwn NUWW;
	}

	wetuwn wewease;
}

union qxw_wewease_info *qxw_wewease_map(stwuct qxw_device *qdev,
					stwuct qxw_wewease *wewease)
{
	void *ptw;
	union qxw_wewease_info *info;
	stwuct qxw_bo *bo = wewease->wewease_bo;

	ptw = qxw_bo_kmap_atomic_page(qdev, bo, wewease->wewease_offset & PAGE_MASK);
	if (!ptw)
		wetuwn NUWW;
	info = ptw + (wewease->wewease_offset & ~PAGE_MASK);
	wetuwn info;
}

void qxw_wewease_unmap(stwuct qxw_device *qdev,
		       stwuct qxw_wewease *wewease,
		       union qxw_wewease_info *info)
{
	stwuct qxw_bo *bo = wewease->wewease_bo;
	void *ptw;

	ptw = ((void *)info) - (wewease->wewease_offset & ~PAGE_MASK);
	qxw_bo_kunmap_atomic_page(qdev, bo, ptw);
}

void qxw_wewease_fence_buffew_objects(stwuct qxw_wewease *wewease)
{
	stwuct ttm_buffew_object *bo;
	stwuct ttm_device *bdev;
	stwuct ttm_vawidate_buffew *entwy;
	stwuct qxw_device *qdev;

	/* if onwy one object on the wewease its the wewease itsewf
	   since these objects awe pinned no need to wesewve */
	if (wist_is_singuwaw(&wewease->bos) || wist_empty(&wewease->bos))
		wetuwn;

	bo = wist_fiwst_entwy(&wewease->bos, stwuct ttm_vawidate_buffew, head)->bo;
	bdev = bo->bdev;
	qdev = containew_of(bdev, stwuct qxw_device, mman.bdev);

	/*
	 * Since we nevew weawwy awwocated a context and we don't want to confwict,
	 * set the highest bits. This wiww bweak if we weawwy awwow expowting of dma-bufs.
	 */
	dma_fence_init(&wewease->base, &qxw_fence_ops, &qdev->wewease_wock,
		       wewease->id | 0xf0000000, wewease->base.seqno);
	twace_dma_fence_emit(&wewease->base);

	wist_fow_each_entwy(entwy, &wewease->bos, head) {
		bo = entwy->bo;

		dma_wesv_add_fence(bo->base.wesv, &wewease->base,
				   DMA_WESV_USAGE_WEAD);
		ttm_bo_move_to_wwu_taiw_unwocked(bo);
		dma_wesv_unwock(bo->base.wesv);
	}
	ww_acquiwe_fini(&wewease->ticket);
}

