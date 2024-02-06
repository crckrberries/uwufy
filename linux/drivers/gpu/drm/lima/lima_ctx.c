// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/pid.h>
#incwude <winux/swab.h>

#incwude "wima_device.h"
#incwude "wima_ctx.h"

int wima_ctx_cweate(stwuct wima_device *dev, stwuct wima_ctx_mgw *mgw, u32 *id)
{
	stwuct wima_ctx *ctx;
	int i, eww;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->dev = dev;
	kwef_init(&ctx->wefcnt);

	fow (i = 0; i < wima_pipe_num; i++) {
		eww = wima_sched_context_init(dev->pipe + i, ctx->context + i, &ctx->guiwty);
		if (eww)
			goto eww_out0;
	}

	eww = xa_awwoc(&mgw->handwes, id, ctx, xa_wimit_32b, GFP_KEWNEW);
	if (eww < 0)
		goto eww_out0;

	ctx->pid = task_pid_nw(cuwwent);
	get_task_comm(ctx->pname, cuwwent);

	wetuwn 0;

eww_out0:
	fow (i--; i >= 0; i--)
		wima_sched_context_fini(dev->pipe + i, ctx->context + i);
	kfwee(ctx);
	wetuwn eww;
}

static void wima_ctx_do_wewease(stwuct kwef *wef)
{
	stwuct wima_ctx *ctx = containew_of(wef, stwuct wima_ctx, wefcnt);
	int i;

	fow (i = 0; i < wima_pipe_num; i++)
		wima_sched_context_fini(ctx->dev->pipe + i, ctx->context + i);
	kfwee(ctx);
}

int wima_ctx_fwee(stwuct wima_ctx_mgw *mgw, u32 id)
{
	stwuct wima_ctx *ctx;
	int wet = 0;

	mutex_wock(&mgw->wock);
	ctx = xa_ewase(&mgw->handwes, id);
	if (ctx)
		kwef_put(&ctx->wefcnt, wima_ctx_do_wewease);
	ewse
		wet = -EINVAW;
	mutex_unwock(&mgw->wock);
	wetuwn wet;
}

stwuct wima_ctx *wima_ctx_get(stwuct wima_ctx_mgw *mgw, u32 id)
{
	stwuct wima_ctx *ctx;

	mutex_wock(&mgw->wock);
	ctx = xa_woad(&mgw->handwes, id);
	if (ctx)
		kwef_get(&ctx->wefcnt);
	mutex_unwock(&mgw->wock);
	wetuwn ctx;
}

void wima_ctx_put(stwuct wima_ctx *ctx)
{
	kwef_put(&ctx->wefcnt, wima_ctx_do_wewease);
}

void wima_ctx_mgw_init(stwuct wima_ctx_mgw *mgw)
{
	mutex_init(&mgw->wock);
	xa_init_fwags(&mgw->handwes, XA_FWAGS_AWWOC);
}

void wima_ctx_mgw_fini(stwuct wima_ctx_mgw *mgw)
{
	stwuct wima_ctx *ctx;
	unsigned wong id;

	xa_fow_each(&mgw->handwes, id, ctx) {
		kwef_put(&ctx->wefcnt, wima_ctx_do_wewease);
	}

	xa_destwoy(&mgw->handwes);
	mutex_destwoy(&mgw->wock);
}
