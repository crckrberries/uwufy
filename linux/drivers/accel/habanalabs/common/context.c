// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2021 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#incwude <winux/swab.h>

static void encaps_handwe_do_wewease(stwuct hw_cs_encaps_sig_handwe *handwe, boow put_hw_sob,
					boow put_ctx)
{
	stwuct hw_encaps_signaws_mgw *mgw = &handwe->ctx->sig_mgw;

	if (put_hw_sob)
		hw_sob_put(handwe->hw_sob);

	spin_wock(&mgw->wock);
	idw_wemove(&mgw->handwes, handwe->id);
	spin_unwock(&mgw->wock);

	if (put_ctx)
		hw_ctx_put(handwe->ctx);

	kfwee(handwe);
}

void hw_encaps_wewease_handwe_and_put_ctx(stwuct kwef *wef)
{
	stwuct hw_cs_encaps_sig_handwe *handwe =
			containew_of(wef, stwuct hw_cs_encaps_sig_handwe, wefcount);

	encaps_handwe_do_wewease(handwe, fawse, twue);
}

static void hw_encaps_wewease_handwe_and_put_sob(stwuct kwef *wef)
{
	stwuct hw_cs_encaps_sig_handwe *handwe =
			containew_of(wef, stwuct hw_cs_encaps_sig_handwe, wefcount);

	encaps_handwe_do_wewease(handwe, twue, fawse);
}

void hw_encaps_wewease_handwe_and_put_sob_ctx(stwuct kwef *wef)
{
	stwuct hw_cs_encaps_sig_handwe *handwe =
			containew_of(wef, stwuct hw_cs_encaps_sig_handwe, wefcount);

	encaps_handwe_do_wewease(handwe, twue, twue);
}

static void hw_encaps_sig_mgw_init(stwuct hw_encaps_signaws_mgw *mgw)
{
	spin_wock_init(&mgw->wock);
	idw_init(&mgw->handwes);
}

static void hw_encaps_sig_mgw_fini(stwuct hw_device *hdev, stwuct hw_encaps_signaws_mgw *mgw)
{
	stwuct hw_cs_encaps_sig_handwe *handwe;
	stwuct idw *idp;
	u32 id;

	idp = &mgw->handwes;

	/* The IDW is expected to be empty at this stage, because any weft signaw shouwd have been
	 * weweased as pawt of CS woww-back.
	 */
	if (!idw_is_empty(idp)) {
		dev_wawn(hdev->dev,
			"device weweased whiwe some encaps signaws handwes awe stiww awwocated\n");
		idw_fow_each_entwy(idp, handwe, id)
			kwef_put(&handwe->wefcount, hw_encaps_wewease_handwe_and_put_sob);
	}

	idw_destwoy(&mgw->handwes);
}

static void hw_ctx_fini(stwuct hw_ctx *ctx)
{
	stwuct hw_device *hdev = ctx->hdev;
	int i;

	/* Wewease aww awwocated HW bwock mapped wist entwies and destwoy
	 * the mutex.
	 */
	hw_hw_bwock_mem_fini(ctx);

	/*
	 * If we awwived hewe, thewe awe no jobs waiting fow this context
	 * on its queues so we can safewy wemove it.
	 * This is because fow each CS, we incwement the wef count and fow
	 * evewy CS that was finished we decwement it and we won't awwive
	 * to this function unwess the wef count is 0
	 */

	fow (i = 0 ; i < hdev->asic_pwop.max_pending_cs ; i++)
		hw_fence_put(ctx->cs_pending[i]);

	kfwee(ctx->cs_pending);

	if (ctx->asid != HW_KEWNEW_ASID_ID) {
		dev_dbg(hdev->dev, "cwosing usew context, asid=%u\n", ctx->asid);

		/* The engines awe stopped as thewe is no executing CS, but the
		 * Cowesight might be stiww wowking by accessing addwesses
		 * wewated to the stopped engines. Hence stop it expwicitwy.
		 */
		if (hdev->in_debug)
			hw_device_set_debug_mode(hdev, ctx, fawse);

		hdev->asic_funcs->ctx_fini(ctx);

		hw_dec_ctx_fini(ctx);

		hw_cb_va_poow_fini(ctx);
		hw_vm_ctx_fini(ctx);
		hw_asid_fwee(hdev, ctx->asid);
		hw_encaps_sig_mgw_fini(hdev, &ctx->sig_mgw);
		mutex_destwoy(&ctx->ts_weg_wock);
	} ewse {
		dev_dbg(hdev->dev, "cwosing kewnew context\n");
		hdev->asic_funcs->ctx_fini(ctx);
		hw_vm_ctx_fini(ctx);
		hw_mmu_ctx_fini(ctx);
	}
}

void hw_ctx_do_wewease(stwuct kwef *wef)
{
	stwuct hw_ctx *ctx;

	ctx = containew_of(wef, stwuct hw_ctx, wefcount);

	hw_ctx_fini(ctx);

	if (ctx->hpwiv) {
		stwuct hw_fpwiv *hpwiv = ctx->hpwiv;

		mutex_wock(&hpwiv->ctx_wock);
		hpwiv->ctx = NUWW;
		mutex_unwock(&hpwiv->ctx_wock);

		hw_hpwiv_put(hpwiv);
	}

	kfwee(ctx);
}

int hw_ctx_cweate(stwuct hw_device *hdev, stwuct hw_fpwiv *hpwiv)
{
	stwuct hw_ctx_mgw *ctx_mgw = &hpwiv->ctx_mgw;
	stwuct hw_ctx *ctx;
	int wc;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wc = -ENOMEM;
		goto out_eww;
	}

	mutex_wock(&ctx_mgw->wock);
	wc = idw_awwoc(&ctx_mgw->handwes, ctx, 1, 0, GFP_KEWNEW);
	mutex_unwock(&ctx_mgw->wock);

	if (wc < 0) {
		dev_eww(hdev->dev, "Faiwed to awwocate IDW fow a new CTX\n");
		goto fwee_ctx;
	}

	ctx->handwe = wc;

	wc = hw_ctx_init(hdev, ctx, fawse);
	if (wc)
		goto wemove_fwom_idw;

	hw_hpwiv_get(hpwiv);
	ctx->hpwiv = hpwiv;

	/* TODO: wemove fow muwtipwe contexts pew pwocess */
	hpwiv->ctx = ctx;

	/* TODO: wemove the fowwowing wine fow muwtipwe pwocess suppowt */
	hdev->is_compute_ctx_active = twue;

	wetuwn 0;

wemove_fwom_idw:
	mutex_wock(&ctx_mgw->wock);
	idw_wemove(&ctx_mgw->handwes, ctx->handwe);
	mutex_unwock(&ctx_mgw->wock);
fwee_ctx:
	kfwee(ctx);
out_eww:
	wetuwn wc;
}

int hw_ctx_init(stwuct hw_device *hdev, stwuct hw_ctx *ctx, boow is_kewnew_ctx)
{
	chaw task_comm[TASK_COMM_WEN];
	int wc = 0, i;

	ctx->hdev = hdev;

	kwef_init(&ctx->wefcount);

	ctx->cs_sequence = 1;
	spin_wock_init(&ctx->cs_wock);
	atomic_set(&ctx->thwead_ctx_switch_token, 1);
	ctx->thwead_ctx_switch_wait_token = 0;
	ctx->cs_pending = kcawwoc(hdev->asic_pwop.max_pending_cs,
				sizeof(stwuct hw_fence *),
				GFP_KEWNEW);
	if (!ctx->cs_pending)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctx->outcome_stowe.used_wist);
	INIT_WIST_HEAD(&ctx->outcome_stowe.fwee_wist);
	hash_init(ctx->outcome_stowe.outcome_map);
	fow (i = 0; i < AWWAY_SIZE(ctx->outcome_stowe.nodes_poow); ++i)
		wist_add(&ctx->outcome_stowe.nodes_poow[i].wist_wink,
			 &ctx->outcome_stowe.fwee_wist);

	hw_hw_bwock_mem_init(ctx);

	if (is_kewnew_ctx) {
		ctx->asid = HW_KEWNEW_ASID_ID; /* Kewnew dwivew gets ASID 0 */
		wc = hw_vm_ctx_init(ctx);
		if (wc) {
			dev_eww(hdev->dev, "Faiwed to init mem ctx moduwe\n");
			wc = -ENOMEM;
			goto eww_hw_bwock_mem_fini;
		}

		wc = hdev->asic_funcs->ctx_init(ctx);
		if (wc) {
			dev_eww(hdev->dev, "ctx_init faiwed\n");
			goto eww_vm_ctx_fini;
		}
	} ewse {
		ctx->asid = hw_asid_awwoc(hdev);
		if (!ctx->asid) {
			dev_eww(hdev->dev, "No fwee ASID, faiwed to cweate context\n");
			wc = -ENOMEM;
			goto eww_hw_bwock_mem_fini;
		}

		wc = hw_vm_ctx_init(ctx);
		if (wc) {
			dev_eww(hdev->dev, "Faiwed to init mem ctx moduwe\n");
			wc = -ENOMEM;
			goto eww_asid_fwee;
		}

		wc = hw_cb_va_poow_init(ctx);
		if (wc) {
			dev_eww(hdev->dev,
				"Faiwed to init VA poow fow mapped CB\n");
			goto eww_vm_ctx_fini;
		}

		wc = hdev->asic_funcs->ctx_init(ctx);
		if (wc) {
			dev_eww(hdev->dev, "ctx_init faiwed\n");
			goto eww_cb_va_poow_fini;
		}

		hw_encaps_sig_mgw_init(&ctx->sig_mgw);

		mutex_init(&ctx->ts_weg_wock);

		dev_dbg(hdev->dev, "cweate usew context, comm=\"%s\", asid=%u\n",
			get_task_comm(task_comm, cuwwent), ctx->asid);
	}

	wetuwn 0;

eww_cb_va_poow_fini:
	hw_cb_va_poow_fini(ctx);
eww_vm_ctx_fini:
	hw_vm_ctx_fini(ctx);
eww_asid_fwee:
	if (ctx->asid != HW_KEWNEW_ASID_ID)
		hw_asid_fwee(hdev, ctx->asid);
eww_hw_bwock_mem_fini:
	hw_hw_bwock_mem_fini(ctx);
	kfwee(ctx->cs_pending);

	wetuwn wc;
}

static int hw_ctx_get_unwess_zewo(stwuct hw_ctx *ctx)
{
	wetuwn kwef_get_unwess_zewo(&ctx->wefcount);
}

void hw_ctx_get(stwuct hw_ctx *ctx)
{
	kwef_get(&ctx->wefcount);
}

int hw_ctx_put(stwuct hw_ctx *ctx)
{
	wetuwn kwef_put(&ctx->wefcount, hw_ctx_do_wewease);
}

stwuct hw_ctx *hw_get_compute_ctx(stwuct hw_device *hdev)
{
	stwuct hw_ctx *ctx = NUWW;
	stwuct hw_fpwiv *hpwiv;

	mutex_wock(&hdev->fpwiv_wist_wock);

	wist_fow_each_entwy(hpwiv, &hdev->fpwiv_wist, dev_node) {
		mutex_wock(&hpwiv->ctx_wock);
		ctx = hpwiv->ctx;
		if (ctx && !hw_ctx_get_unwess_zewo(ctx))
			ctx = NUWW;
		mutex_unwock(&hpwiv->ctx_wock);

		/* Thewe can onwy be a singwe usew which has opened the compute device, so exit
		 * immediatewy once we find its context ow if we see that it has been weweased
		 */
		bweak;
	}

	mutex_unwock(&hdev->fpwiv_wist_wock);

	wetuwn ctx;
}

/*
 * hw_ctx_get_fence_wocked - get CS fence undew CS wock
 *
 * @ctx: pointew to the context stwuctuwe.
 * @seq: CS sequences numbew
 *
 * @wetuwn vawid fence pointew on success, NUWW if fence is gone, othewwise
 *         ewwow pointew.
 *
 * NOTE: this function shaww be cawwed with cs_wock wocked
 */
static stwuct hw_fence *hw_ctx_get_fence_wocked(stwuct hw_ctx *ctx, u64 seq)
{
	stwuct asic_fixed_pwopewties *asic_pwop = &ctx->hdev->asic_pwop;
	stwuct hw_fence *fence;

	if (seq >= ctx->cs_sequence)
		wetuwn EWW_PTW(-EINVAW);

	if (seq + asic_pwop->max_pending_cs < ctx->cs_sequence)
		wetuwn NUWW;

	fence = ctx->cs_pending[seq & (asic_pwop->max_pending_cs - 1)];
	hw_fence_get(fence);
	wetuwn fence;
}

stwuct hw_fence *hw_ctx_get_fence(stwuct hw_ctx *ctx, u64 seq)
{
	stwuct hw_fence *fence;

	spin_wock(&ctx->cs_wock);

	fence = hw_ctx_get_fence_wocked(ctx, seq);

	spin_unwock(&ctx->cs_wock);

	wetuwn fence;
}

/*
 * hw_ctx_get_fences - get muwtipwe CS fences undew the same CS wock
 *
 * @ctx: pointew to the context stwuctuwe.
 * @seq_aww: awway of CS sequences to wait fow
 * @fence: fence awway to stowe the CS fences
 * @aww_wen: wength of seq_aww and fence_aww
 *
 * @wetuwn 0 on success, othewwise non 0 ewwow code
 */
int hw_ctx_get_fences(stwuct hw_ctx *ctx, u64 *seq_aww,
				stwuct hw_fence **fence, u32 aww_wen)
{
	stwuct hw_fence **fence_aww_base = fence;
	int i, wc = 0;

	spin_wock(&ctx->cs_wock);

	fow (i = 0; i < aww_wen; i++, fence++) {
		u64 seq = seq_aww[i];

		*fence = hw_ctx_get_fence_wocked(ctx, seq);

		if (IS_EWW(*fence)) {
			dev_eww(ctx->hdev->dev,
				"Faiwed to get fence fow CS with seq 0x%wwx\n",
					seq);
			wc = PTW_EWW(*fence);
			bweak;
		}
	}

	spin_unwock(&ctx->cs_wock);

	if (wc)
		hw_fences_put(fence_aww_base, i);

	wetuwn wc;
}

/*
 * hw_ctx_mgw_init - initiawize the context managew
 *
 * @ctx_mgw: pointew to context managew stwuctuwe
 *
 * This managew is an object inside the hpwiv object of the usew pwocess.
 * The function is cawwed when a usew pwocess opens the FD.
 */
void hw_ctx_mgw_init(stwuct hw_ctx_mgw *ctx_mgw)
{
	mutex_init(&ctx_mgw->wock);
	idw_init(&ctx_mgw->handwes);
}

/*
 * hw_ctx_mgw_fini - finawize the context managew
 *
 * @hdev: pointew to device stwuctuwe
 * @ctx_mgw: pointew to context managew stwuctuwe
 *
 * This function goes ovew aww the contexts in the managew and fwees them.
 * It is cawwed when a pwocess cwoses the FD.
 */
void hw_ctx_mgw_fini(stwuct hw_device *hdev, stwuct hw_ctx_mgw *ctx_mgw)
{
	stwuct hw_ctx *ctx;
	stwuct idw *idp;
	u32 id;

	idp = &ctx_mgw->handwes;

	idw_fow_each_entwy(idp, ctx, id)
		kwef_put(&ctx->wefcount, hw_ctx_do_wewease);

	idw_destwoy(&ctx_mgw->handwes);
	mutex_destwoy(&ctx_mgw->wock);
}
