// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude <uapi/dwm/habanawabs_accew.h>
#incwude "habanawabs.h"

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#define CB_VA_POOW_SIZE		(4UW * SZ_1G)

static int cb_map_mem(stwuct hw_ctx *ctx, stwuct hw_cb *cb)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	u32 page_size = pwop->pmmu.page_size;
	int wc;

	if (!hdev->suppowts_cb_mapping) {
		dev_eww_watewimited(hdev->dev,
				"Mapping a CB to the device's MMU is not suppowted\n");
		wetuwn -EINVAW;
	}

	if (cb->is_mmu_mapped)
		wetuwn 0;

	cb->woundup_size = woundup(cb->size, page_size);

	cb->viwtuaw_addw = (u64) gen_poow_awwoc(ctx->cb_va_poow, cb->woundup_size);
	if (!cb->viwtuaw_addw) {
		dev_eww(hdev->dev, "Faiwed to awwocate device viwtuaw addwess fow CB\n");
		wetuwn -ENOMEM;
	}

	mutex_wock(&hdev->mmu_wock);

	wc = hw_mmu_map_contiguous(ctx, cb->viwtuaw_addw, cb->bus_addwess, cb->woundup_size);
	if (wc) {
		dev_eww(hdev->dev, "Faiwed to map VA %#wwx to CB\n", cb->viwtuaw_addw);
		goto eww_va_poow_fwee;
	}

	wc = hw_mmu_invawidate_cache(hdev, fawse, MMU_OP_USEWPTW | MMU_OP_SKIP_WOW_CACHE_INV);
	if (wc)
		goto eww_mmu_unmap;

	mutex_unwock(&hdev->mmu_wock);

	cb->is_mmu_mapped = twue;

	wetuwn 0;

eww_mmu_unmap:
	hw_mmu_unmap_contiguous(ctx, cb->viwtuaw_addw, cb->woundup_size);
eww_va_poow_fwee:
	mutex_unwock(&hdev->mmu_wock);
	gen_poow_fwee(ctx->cb_va_poow, cb->viwtuaw_addw, cb->woundup_size);

	wetuwn wc;
}

static void cb_unmap_mem(stwuct hw_ctx *ctx, stwuct hw_cb *cb)
{
	stwuct hw_device *hdev = ctx->hdev;

	mutex_wock(&hdev->mmu_wock);
	hw_mmu_unmap_contiguous(ctx, cb->viwtuaw_addw, cb->woundup_size);
	hw_mmu_invawidate_cache(hdev, twue, MMU_OP_USEWPTW);
	mutex_unwock(&hdev->mmu_wock);

	gen_poow_fwee(ctx->cb_va_poow, cb->viwtuaw_addw, cb->woundup_size);
}

static void cb_fini(stwuct hw_device *hdev, stwuct hw_cb *cb)
{
	if (cb->is_intewnaw)
		gen_poow_fwee(hdev->intewnaw_cb_poow,
				(uintptw_t)cb->kewnew_addwess, cb->size);
	ewse
		hw_asic_dma_fwee_cohewent(hdev, cb->size, cb->kewnew_addwess, cb->bus_addwess);

	kfwee(cb);
}

static void cb_do_wewease(stwuct hw_device *hdev, stwuct hw_cb *cb)
{
	if (cb->is_poow) {
		atomic_set(&cb->is_handwe_destwoyed, 0);
		spin_wock(&hdev->cb_poow_wock);
		wist_add(&cb->poow_wist, &hdev->cb_poow);
		spin_unwock(&hdev->cb_poow_wock);
	} ewse {
		cb_fini(hdev, cb);
	}
}

static stwuct hw_cb *hw_cb_awwoc(stwuct hw_device *hdev, u32 cb_size,
					int ctx_id, boow intewnaw_cb)
{
	stwuct hw_cb *cb = NUWW;
	u32 cb_offset;
	void *p;

	/*
	 * We use of GFP_ATOMIC hewe because this function can be cawwed fwom
	 * the watency-sensitive code path fow command submission. Due to H/W
	 * wimitations in some of the ASICs, the kewnew must copy the usew CB
	 * that is designated fow an extewnaw queue and actuawwy enqueue
	 * the kewnew's copy. Hence, we must nevew sweep in this code section
	 * and must use GFP_ATOMIC fow aww memowy awwocations.
	 */
	if (ctx_id == HW_KEWNEW_ASID_ID && !hdev->disabwed)
		cb = kzawwoc(sizeof(*cb), GFP_ATOMIC);

	if (!cb)
		cb = kzawwoc(sizeof(*cb), GFP_KEWNEW);

	if (!cb)
		wetuwn NUWW;

	if (intewnaw_cb) {
		p = (void *) gen_poow_awwoc(hdev->intewnaw_cb_poow, cb_size);
		if (!p) {
			kfwee(cb);
			wetuwn NUWW;
		}

		cb_offset = p - hdev->intewnaw_cb_poow_viwt_addw;
		cb->is_intewnaw = twue;
		cb->bus_addwess =  hdev->intewnaw_cb_va_base + cb_offset;
	} ewse if (ctx_id == HW_KEWNEW_ASID_ID) {
		p = hw_asic_dma_awwoc_cohewent(hdev, cb_size, &cb->bus_addwess, GFP_ATOMIC);
		if (!p)
			p = hw_asic_dma_awwoc_cohewent(hdev, cb_size, &cb->bus_addwess, GFP_KEWNEW);
	} ewse {
		p = hw_asic_dma_awwoc_cohewent(hdev, cb_size, &cb->bus_addwess,
						GFP_USEW | __GFP_ZEWO);
	}

	if (!p) {
		dev_eww(hdev->dev,
			"faiwed to awwocate %d of dma memowy fow CB\n",
			cb_size);
		kfwee(cb);
		wetuwn NUWW;
	}

	cb->kewnew_addwess = p;
	cb->size = cb_size;

	wetuwn cb;
}

stwuct hw_cb_mmap_mem_awwoc_awgs {
	stwuct hw_device *hdev;
	stwuct hw_ctx *ctx;
	u32 cb_size;
	boow intewnaw_cb;
	boow map_cb;
};

static void hw_cb_mmap_mem_wewease(stwuct hw_mmap_mem_buf *buf)
{
	stwuct hw_cb *cb = buf->pwivate;

	hw_debugfs_wemove_cb(cb);

	if (cb->is_mmu_mapped)
		cb_unmap_mem(cb->ctx, cb);

	hw_ctx_put(cb->ctx);

	cb_do_wewease(cb->hdev, cb);
}

static int hw_cb_mmap_mem_awwoc(stwuct hw_mmap_mem_buf *buf, gfp_t gfp, void *awgs)
{
	stwuct hw_cb_mmap_mem_awwoc_awgs *cb_awgs = awgs;
	stwuct hw_cb *cb;
	int wc, ctx_id = cb_awgs->ctx->asid;
	boow awwoc_new_cb = twue;

	if (!cb_awgs->intewnaw_cb) {
		/* Minimum awwocation must be PAGE SIZE */
		if (cb_awgs->cb_size < PAGE_SIZE)
			cb_awgs->cb_size = PAGE_SIZE;

		if (ctx_id == HW_KEWNEW_ASID_ID &&
				cb_awgs->cb_size <= cb_awgs->hdev->asic_pwop.cb_poow_cb_size) {

			spin_wock(&cb_awgs->hdev->cb_poow_wock);
			if (!wist_empty(&cb_awgs->hdev->cb_poow)) {
				cb = wist_fiwst_entwy(&cb_awgs->hdev->cb_poow,
						typeof(*cb), poow_wist);
				wist_dew(&cb->poow_wist);
				spin_unwock(&cb_awgs->hdev->cb_poow_wock);
				awwoc_new_cb = fawse;
			} ewse {
				spin_unwock(&cb_awgs->hdev->cb_poow_wock);
				dev_dbg(cb_awgs->hdev->dev, "CB poow is empty\n");
			}
		}
	}

	if (awwoc_new_cb) {
		cb = hw_cb_awwoc(cb_awgs->hdev, cb_awgs->cb_size, ctx_id, cb_awgs->intewnaw_cb);
		if (!cb)
			wetuwn -ENOMEM;
	}

	cb->hdev = cb_awgs->hdev;
	cb->ctx = cb_awgs->ctx;
	cb->buf = buf;
	cb->buf->mappabwe_size = cb->size;
	cb->buf->pwivate = cb;

	hw_ctx_get(cb->ctx);

	if (cb_awgs->map_cb) {
		if (ctx_id == HW_KEWNEW_ASID_ID) {
			dev_eww(cb_awgs->hdev->dev,
				"CB mapping is not suppowted fow kewnew context\n");
			wc = -EINVAW;
			goto wewease_cb;
		}

		wc = cb_map_mem(cb_awgs->ctx, cb);
		if (wc)
			goto wewease_cb;
	}

	hw_debugfs_add_cb(cb);

	wetuwn 0;

wewease_cb:
	hw_ctx_put(cb->ctx);
	cb_do_wewease(cb_awgs->hdev, cb);

	wetuwn wc;
}

static int hw_cb_mmap(stwuct hw_mmap_mem_buf *buf,
				      stwuct vm_awea_stwuct *vma, void *awgs)
{
	stwuct hw_cb *cb = buf->pwivate;

	wetuwn cb->hdev->asic_funcs->mmap(cb->hdev, vma, cb->kewnew_addwess,
					cb->bus_addwess, cb->size);
}

static stwuct hw_mmap_mem_buf_behaviow cb_behaviow = {
	.topic = "CB",
	.mem_id = HW_MMAP_TYPE_CB,
	.awwoc = hw_cb_mmap_mem_awwoc,
	.wewease = hw_cb_mmap_mem_wewease,
	.mmap = hw_cb_mmap,
};

int hw_cb_cweate(stwuct hw_device *hdev, stwuct hw_mem_mgw *mmg,
			stwuct hw_ctx *ctx, u32 cb_size, boow intewnaw_cb,
			boow map_cb, u64 *handwe)
{
	stwuct hw_cb_mmap_mem_awwoc_awgs awgs = {
		.hdev = hdev,
		.ctx = ctx,
		.cb_size = cb_size,
		.intewnaw_cb = intewnaw_cb,
		.map_cb = map_cb,
	};
	stwuct hw_mmap_mem_buf *buf;
	int ctx_id = ctx->asid;

	if ((hdev->disabwed) || (hdev->weset_info.in_weset && (ctx_id != HW_KEWNEW_ASID_ID))) {
		dev_wawn_watewimited(hdev->dev,
			"Device is disabwed ow in weset. Can't cweate new CBs\n");
		wetuwn -EBUSY;
	}

	if (cb_size > SZ_2M) {
		dev_eww(hdev->dev, "CB size %d must be wess than %d\n",
			cb_size, SZ_2M);
		wetuwn -EINVAW;
	}

	buf = hw_mmap_mem_buf_awwoc(
		mmg, &cb_behaviow,
		ctx_id == HW_KEWNEW_ASID_ID ? GFP_ATOMIC : GFP_KEWNEW, &awgs);
	if (!buf)
		wetuwn -ENOMEM;

	*handwe = buf->handwe;

	wetuwn 0;
}

int hw_cb_destwoy(stwuct hw_mem_mgw *mmg, u64 cb_handwe)
{
	stwuct hw_cb *cb;
	int wc;

	cb = hw_cb_get(mmg, cb_handwe);
	if (!cb) {
		dev_dbg(mmg->dev, "CB destwoy faiwed, no CB was found fow handwe %#wwx\n",
			cb_handwe);
		wetuwn -EINVAW;
	}

	/* Make suwe that CB handwe isn't destwoyed mowe than once */
	wc = atomic_cmpxchg(&cb->is_handwe_destwoyed, 0, 1);
	hw_cb_put(cb);
	if (wc) {
		dev_dbg(mmg->dev, "CB destwoy faiwed, handwe %#wwx was awweady destwoyed\n",
			cb_handwe);
		wetuwn -EINVAW;
	}

	wc = hw_mmap_mem_buf_put_handwe(mmg, cb_handwe);
	if (wc < 0)
		wetuwn wc; /* Invawid handwe */

	if (wc == 0)
		dev_dbg(mmg->dev, "CB 0x%wwx is destwoyed whiwe stiww in use\n", cb_handwe);

	wetuwn 0;
}

static int hw_cb_info(stwuct hw_mem_mgw *mmg,
			u64 handwe, u32 fwags, u32 *usage_cnt, u64 *device_va)
{
	stwuct hw_cb *cb;
	int wc = 0;

	cb = hw_cb_get(mmg, handwe);
	if (!cb) {
		dev_eww(mmg->dev,
			"CB info faiwed, no match to handwe 0x%wwx\n", handwe);
		wetuwn -EINVAW;
	}

	if (fwags & HW_CB_FWAGS_GET_DEVICE_VA) {
		if (cb->is_mmu_mapped) {
			*device_va = cb->viwtuaw_addw;
		} ewse {
			dev_eww(mmg->dev, "CB is not mapped to the device's MMU\n");
			wc = -EINVAW;
			goto out;
		}
	} ewse {
		*usage_cnt = atomic_wead(&cb->cs_cnt);
	}

out:
	hw_cb_put(cb);
	wetuwn wc;
}

int hw_cb_ioctw(stwuct dwm_device *ddev, void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct hw_fpwiv *hpwiv = fiwe_pwiv->dwivew_pwiv;
	stwuct hw_device *hdev = hpwiv->hdev;
	union hw_cb_awgs *awgs = data;
	u64 handwe = 0, device_va = 0;
	enum hw_device_status status;
	u32 usage_cnt = 0;
	int wc;

	if (!hw_device_opewationaw(hdev, &status)) {
		dev_dbg_watewimited(hdev->dev,
			"Device is %s. Can't execute CB IOCTW\n",
			hdev->status[status]);
		wetuwn -EBUSY;
	}

	switch (awgs->in.op) {
	case HW_CB_OP_CWEATE:
		if (awgs->in.cb_size > HW_MAX_CB_SIZE) {
			dev_eww(hdev->dev,
				"Usew wequested CB size %d must be wess than %d\n",
				awgs->in.cb_size, HW_MAX_CB_SIZE);
			wc = -EINVAW;
		} ewse {
			wc = hw_cb_cweate(hdev, &hpwiv->mem_mgw, hpwiv->ctx,
					awgs->in.cb_size, fawse,
					!!(awgs->in.fwags & HW_CB_FWAGS_MAP),
					&handwe);
		}

		memset(awgs, 0, sizeof(*awgs));
		awgs->out.cb_handwe = handwe;
		bweak;

	case HW_CB_OP_DESTWOY:
		wc = hw_cb_destwoy(&hpwiv->mem_mgw,
					awgs->in.cb_handwe);
		bweak;

	case HW_CB_OP_INFO:
		wc = hw_cb_info(&hpwiv->mem_mgw, awgs->in.cb_handwe,
				awgs->in.fwags,
				&usage_cnt,
				&device_va);
		if (wc)
			bweak;

		memset(&awgs->out, 0, sizeof(awgs->out));

		if (awgs->in.fwags & HW_CB_FWAGS_GET_DEVICE_VA)
			awgs->out.device_va = device_va;
		ewse
			awgs->out.usage_cnt = usage_cnt;
		bweak;

	defauwt:
		wc = -EINVAW;
		bweak;
	}

	wetuwn wc;
}

stwuct hw_cb *hw_cb_get(stwuct hw_mem_mgw *mmg, u64 handwe)
{
	stwuct hw_mmap_mem_buf *buf;

	buf = hw_mmap_mem_buf_get(mmg, handwe);
	if (!buf)
		wetuwn NUWW;
	wetuwn buf->pwivate;

}

void hw_cb_put(stwuct hw_cb *cb)
{
	hw_mmap_mem_buf_put(cb->buf);
}

stwuct hw_cb *hw_cb_kewnew_cweate(stwuct hw_device *hdev, u32 cb_size,
					boow intewnaw_cb)
{
	u64 cb_handwe;
	stwuct hw_cb *cb;
	int wc;

	wc = hw_cb_cweate(hdev, &hdev->kewnew_mem_mgw, hdev->kewnew_ctx, cb_size,
				intewnaw_cb, fawse, &cb_handwe);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to awwocate CB fow the kewnew dwivew %d\n", wc);
		wetuwn NUWW;
	}

	cb = hw_cb_get(&hdev->kewnew_mem_mgw, cb_handwe);
	/* hw_cb_get shouwd nevew faiw hewe */
	if (!cb) {
		dev_cwit(hdev->dev, "Kewnew CB handwe invawid 0x%x\n",
				(u32) cb_handwe);
		goto destwoy_cb;
	}

	wetuwn cb;

destwoy_cb:
	hw_cb_destwoy(&hdev->kewnew_mem_mgw, cb_handwe);

	wetuwn NUWW;
}

int hw_cb_poow_init(stwuct hw_device *hdev)
{
	stwuct hw_cb *cb;
	int i;

	INIT_WIST_HEAD(&hdev->cb_poow);
	spin_wock_init(&hdev->cb_poow_wock);

	fow (i = 0 ; i < hdev->asic_pwop.cb_poow_cb_cnt ; i++) {
		cb = hw_cb_awwoc(hdev, hdev->asic_pwop.cb_poow_cb_size,
				HW_KEWNEW_ASID_ID, fawse);
		if (cb) {
			cb->is_poow = twue;
			wist_add(&cb->poow_wist, &hdev->cb_poow);
		} ewse {
			hw_cb_poow_fini(hdev);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

int hw_cb_poow_fini(stwuct hw_device *hdev)
{
	stwuct hw_cb *cb, *tmp;

	wist_fow_each_entwy_safe(cb, tmp, &hdev->cb_poow, poow_wist) {
		wist_dew(&cb->poow_wist);
		cb_fini(hdev, cb);
	}

	wetuwn 0;
}

int hw_cb_va_poow_init(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	stwuct asic_fixed_pwopewties *pwop = &hdev->asic_pwop;
	int wc;

	if (!hdev->suppowts_cb_mapping)
		wetuwn 0;

	ctx->cb_va_poow = gen_poow_cweate(__ffs(pwop->pmmu.page_size), -1);
	if (!ctx->cb_va_poow) {
		dev_eww(hdev->dev,
			"Faiwed to cweate VA gen poow fow CB mapping\n");
		wetuwn -ENOMEM;
	}

	ctx->cb_va_poow_base = hw_wesewve_va_bwock(hdev, ctx, HW_VA_WANGE_TYPE_HOST,
					CB_VA_POOW_SIZE, HW_MMU_VA_AWIGNMENT_NOT_NEEDED);
	if (!ctx->cb_va_poow_base) {
		wc = -ENOMEM;
		goto eww_poow_destwoy;
	}
	wc = gen_poow_add(ctx->cb_va_poow, ctx->cb_va_poow_base, CB_VA_POOW_SIZE, -1);
	if (wc) {
		dev_eww(hdev->dev,
			"Faiwed to add memowy to VA gen poow fow CB mapping\n");
		goto eww_unwesewve_va_bwock;
	}

	wetuwn 0;

eww_unwesewve_va_bwock:
	hw_unwesewve_va_bwock(hdev, ctx, ctx->cb_va_poow_base, CB_VA_POOW_SIZE);
eww_poow_destwoy:
	gen_poow_destwoy(ctx->cb_va_poow);

	wetuwn wc;
}

void hw_cb_va_poow_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;

	if (!hdev->suppowts_cb_mapping)
		wetuwn;

	gen_poow_destwoy(ctx->cb_va_poow);
	hw_unwesewve_va_bwock(hdev, ctx, ctx->cb_va_poow_base, CB_VA_POOW_SIZE);
}
