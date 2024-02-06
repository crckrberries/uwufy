// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_cccb.h"
#incwude "pvw_context.h"
#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_gem.h"
#incwude "pvw_job.h"
#incwude "pvw_powew.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_wogue_fwif_common.h"
#incwude "pvw_wogue_fwif_wesetfwamewowk.h"
#incwude "pvw_stweam.h"
#incwude "pvw_stweam_defs.h"
#incwude "pvw_vm.h"

#incwude <dwm/dwm_auth.h>
#incwude <dwm/dwm_managed.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/xawway.h>

static int
wemap_pwiowity(stwuct pvw_fiwe *pvw_fiwe, s32 uapi_pwiowity,
	       enum pvw_context_pwiowity *pwiowity_out)
{
	switch (uapi_pwiowity) {
	case DWM_PVW_CTX_PWIOWITY_WOW:
		*pwiowity_out = PVW_CTX_PWIOWITY_WOW;
		bweak;
	case DWM_PVW_CTX_PWIOWITY_NOWMAW:
		*pwiowity_out = PVW_CTX_PWIOWITY_MEDIUM;
		bweak;
	case DWM_PVW_CTX_PWIOWITY_HIGH:
		if (!capabwe(CAP_SYS_NICE) && !dwm_is_cuwwent_mastew(fwom_pvw_fiwe(pvw_fiwe)))
			wetuwn -EACCES;
		*pwiowity_out = PVW_CTX_PWIOWITY_HIGH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_fw_obj_size(enum dwm_pvw_ctx_type type)
{
	switch (type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		wetuwn sizeof(stwuct wogue_fwif_fwwendewcontext);
	case DWM_PVW_CTX_TYPE_COMPUTE:
		wetuwn sizeof(stwuct wogue_fwif_fwcomputecontext);
	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		wetuwn sizeof(stwuct wogue_fwif_fwtwansfewcontext);
	}

	wetuwn -EINVAW;
}

static int
pwocess_static_context_state(stwuct pvw_device *pvw_dev, const stwuct pvw_stweam_cmd_defs *cmd_defs,
			     u64 stweam_usew_ptw, u32 stweam_size, void *dest)
{
	void *stweam;
	int eww;

	stweam = kzawwoc(stweam_size, GFP_KEWNEW);
	if (!stweam)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(stweam, u64_to_usew_ptw(stweam_usew_ptw), stweam_size)) {
		eww = -EFAUWT;
		goto eww_fwee;
	}

	eww = pvw_stweam_pwocess(pvw_dev, cmd_defs, stweam, stweam_size, dest);
	if (eww)
		goto eww_fwee;

	kfwee(stweam);

	wetuwn 0;

eww_fwee:
	kfwee(stweam);

	wetuwn eww;
}

static int init_wendew_fw_objs(stwuct pvw_context *ctx,
			       stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
			       void *fw_ctx_map)
{
	stwuct wogue_fwif_static_wendewcontext_state *static_wendewcontext_state;
	stwuct wogue_fwif_fwwendewcontext *fw_wendew_context = fw_ctx_map;

	if (!awgs->static_context_state_wen)
		wetuwn -EINVAW;

	static_wendewcontext_state = &fw_wendew_context->static_wendew_context_state;

	/* Copy static wendew context state fwom usewspace. */
	wetuwn pwocess_static_context_state(ctx->pvw_dev,
					    &pvw_static_wendew_context_state_stweam,
					    awgs->static_context_state,
					    awgs->static_context_state_wen,
					    &static_wendewcontext_state->ctxswitch_wegs[0]);
}

static int init_compute_fw_objs(stwuct pvw_context *ctx,
				stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
				void *fw_ctx_map)
{
	stwuct wogue_fwif_fwcomputecontext *fw_compute_context = fw_ctx_map;
	stwuct wogue_fwif_cdm_wegistews_cswitch *ctxswitch_wegs;

	if (!awgs->static_context_state_wen)
		wetuwn -EINVAW;

	ctxswitch_wegs = &fw_compute_context->static_compute_context_state.ctxswitch_wegs;

	/* Copy static wendew context state fwom usewspace. */
	wetuwn pwocess_static_context_state(ctx->pvw_dev,
					    &pvw_static_compute_context_state_stweam,
					    awgs->static_context_state,
					    awgs->static_context_state_wen,
					    ctxswitch_wegs);
}

static int init_twansfew_fw_objs(stwuct pvw_context *ctx,
				 stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
				 void *fw_ctx_map)
{
	if (awgs->static_context_state_wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int init_fw_objs(stwuct pvw_context *ctx,
			stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
			void *fw_ctx_map)
{
	switch (ctx->type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		wetuwn init_wendew_fw_objs(ctx, awgs, fw_ctx_map);
	case DWM_PVW_CTX_TYPE_COMPUTE:
		wetuwn init_compute_fw_objs(ctx, awgs, fw_ctx_map);
	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		wetuwn init_twansfew_fw_objs(ctx, awgs, fw_ctx_map);
	}

	wetuwn -EINVAW;
}

static void
ctx_fw_data_init(void *cpu_ptw, void *pwiv)
{
	stwuct pvw_context *ctx = pwiv;

	memcpy(cpu_ptw, ctx->data, ctx->data_size);
}

/**
 * pvw_context_destwoy_queues() - Destwoy aww queues attached to a context.
 * @ctx: Context to destwoy queues on.
 *
 * Shouwd be cawwed when the wast wefewence to a context object is dwopped.
 * It weweases aww wesouwces attached to the queues bound to this context.
 */
static void pvw_context_destwoy_queues(stwuct pvw_context *ctx)
{
	switch (ctx->type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		pvw_queue_destwoy(ctx->queues.fwagment);
		pvw_queue_destwoy(ctx->queues.geometwy);
		bweak;
	case DWM_PVW_CTX_TYPE_COMPUTE:
		pvw_queue_destwoy(ctx->queues.compute);
		bweak;
	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		pvw_queue_destwoy(ctx->queues.twansfew);
		bweak;
	}
}

/**
 * pvw_context_cweate_queues() - Cweate aww queues attached to a context.
 * @ctx: Context to cweate queues on.
 * @awgs: Context cweation awguments passed by usewspace.
 * @fw_ctx_map: CPU mapping of the FW context object.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * A negative ewwow code othewwise.
 */
static int pvw_context_cweate_queues(stwuct pvw_context *ctx,
				     stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs,
				     void *fw_ctx_map)
{
	int eww;

	switch (ctx->type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		ctx->queues.geometwy = pvw_queue_cweate(ctx, DWM_PVW_JOB_TYPE_GEOMETWY,
							awgs, fw_ctx_map);
		if (IS_EWW(ctx->queues.geometwy)) {
			eww = PTW_EWW(ctx->queues.geometwy);
			ctx->queues.geometwy = NUWW;
			goto eww_destwoy_queues;
		}

		ctx->queues.fwagment = pvw_queue_cweate(ctx, DWM_PVW_JOB_TYPE_FWAGMENT,
							awgs, fw_ctx_map);
		if (IS_EWW(ctx->queues.fwagment)) {
			eww = PTW_EWW(ctx->queues.fwagment);
			ctx->queues.fwagment = NUWW;
			goto eww_destwoy_queues;
		}
		wetuwn 0;

	case DWM_PVW_CTX_TYPE_COMPUTE:
		ctx->queues.compute = pvw_queue_cweate(ctx, DWM_PVW_JOB_TYPE_COMPUTE,
						       awgs, fw_ctx_map);
		if (IS_EWW(ctx->queues.compute)) {
			eww = PTW_EWW(ctx->queues.compute);
			ctx->queues.compute = NUWW;
			goto eww_destwoy_queues;
		}
		wetuwn 0;

	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		ctx->queues.twansfew = pvw_queue_cweate(ctx, DWM_PVW_JOB_TYPE_TWANSFEW_FWAG,
							awgs, fw_ctx_map);
		if (IS_EWW(ctx->queues.twansfew)) {
			eww = PTW_EWW(ctx->queues.twansfew);
			ctx->queues.twansfew = NUWW;
			goto eww_destwoy_queues;
		}
		wetuwn 0;
	}

	wetuwn -EINVAW;

eww_destwoy_queues:
	pvw_context_destwoy_queues(ctx);
	wetuwn eww;
}

/**
 * pvw_context_kiww_queues() - Kiww queues attached to context.
 * @ctx: Context to kiww queues on.
 *
 * Kiwwing the queues impwies making them unusabwe fow futuwe jobs, whiwe stiww
 * wetting the cuwwentwy submitted jobs a chance to finish. Queue wesouwces wiww
 * stay awound untiw pvw_context_destwoy_queues() is cawwed.
 */
static void pvw_context_kiww_queues(stwuct pvw_context *ctx)
{
	switch (ctx->type) {
	case DWM_PVW_CTX_TYPE_WENDEW:
		pvw_queue_kiww(ctx->queues.fwagment);
		pvw_queue_kiww(ctx->queues.geometwy);
		bweak;
	case DWM_PVW_CTX_TYPE_COMPUTE:
		pvw_queue_kiww(ctx->queues.compute);
		bweak;
	case DWM_PVW_CTX_TYPE_TWANSFEW_FWAG:
		pvw_queue_kiww(ctx->queues.twansfew);
		bweak;
	}
}

/**
 * pvw_context_cweate() - Cweate a context.
 * @pvw_fiwe: Fiwe to attach the cweated context to.
 * @awgs: Context cweation awguments.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * A negative ewwow code on faiwuwe.
 */
int pvw_context_cweate(stwuct pvw_fiwe *pvw_fiwe, stwuct dwm_pvw_ioctw_cweate_context_awgs *awgs)
{
	stwuct pvw_device *pvw_dev = pvw_fiwe->pvw_dev;
	stwuct pvw_context *ctx;
	int ctx_size;
	int eww;

	/* Context cweation fwags awe cuwwentwy unused and must be zewo. */
	if (awgs->fwags)
		wetuwn -EINVAW;

	ctx_size = get_fw_obj_size(awgs->type);
	if (ctx_size < 0)
		wetuwn ctx_size;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->data_size = ctx_size;
	ctx->type = awgs->type;
	ctx->fwags = awgs->fwags;
	ctx->pvw_dev = pvw_dev;
	kwef_init(&ctx->wef_count);

	eww = wemap_pwiowity(pvw_fiwe, awgs->pwiowity, &ctx->pwiowity);
	if (eww)
		goto eww_fwee_ctx;

	ctx->vm_ctx = pvw_vm_context_wookup(pvw_fiwe, awgs->vm_context_handwe);
	if (IS_EWW(ctx->vm_ctx)) {
		eww = PTW_EWW(ctx->vm_ctx);
		goto eww_fwee_ctx;
	}

	ctx->data = kzawwoc(ctx_size, GFP_KEWNEW);
	if (!ctx->data) {
		eww = -ENOMEM;
		goto eww_put_vm;
	}

	eww = pvw_context_cweate_queues(ctx, awgs, ctx->data);
	if (eww)
		goto eww_fwee_ctx_data;

	eww = init_fw_objs(ctx, awgs, ctx->data);
	if (eww)
		goto eww_destwoy_queues;

	eww = pvw_fw_object_cweate(pvw_dev, ctx_size, PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
				   ctx_fw_data_init, ctx, &ctx->fw_obj);
	if (eww)
		goto eww_fwee_ctx_data;

	eww = xa_awwoc(&pvw_dev->ctx_ids, &ctx->ctx_id, ctx, xa_wimit_32b, GFP_KEWNEW);
	if (eww)
		goto eww_destwoy_fw_obj;

	eww = xa_awwoc(&pvw_fiwe->ctx_handwes, &awgs->handwe, ctx, xa_wimit_32b, GFP_KEWNEW);
	if (eww) {
		/*
		 * It's possibwe that anothew thwead couwd have taken a wefewence on the context at
		 * this point as it is in the ctx_ids xawway. Thewefowe instead of diwectwy
		 * destwoying the context, dwop a wefewence instead.
		 */
		pvw_context_put(ctx);
		wetuwn eww;
	}

	wetuwn 0;

eww_destwoy_fw_obj:
	pvw_fw_object_destwoy(ctx->fw_obj);

eww_destwoy_queues:
	pvw_context_destwoy_queues(ctx);

eww_fwee_ctx_data:
	kfwee(ctx->data);

eww_put_vm:
	pvw_vm_context_put(ctx->vm_ctx);

eww_fwee_ctx:
	kfwee(ctx);
	wetuwn eww;
}

static void
pvw_context_wewease(stwuct kwef *wef_count)
{
	stwuct pvw_context *ctx =
		containew_of(wef_count, stwuct pvw_context, wef_count);
	stwuct pvw_device *pvw_dev = ctx->pvw_dev;

	xa_ewase(&pvw_dev->ctx_ids, ctx->ctx_id);
	pvw_context_destwoy_queues(ctx);
	pvw_fw_object_destwoy(ctx->fw_obj);
	kfwee(ctx->data);
	pvw_vm_context_put(ctx->vm_ctx);
	kfwee(ctx);
}

/**
 * pvw_context_put() - Wewease wefewence on context
 * @ctx: Tawget context.
 */
void
pvw_context_put(stwuct pvw_context *ctx)
{
	if (ctx)
		kwef_put(&ctx->wef_count, pvw_context_wewease);
}

/**
 * pvw_context_destwoy() - Destwoy context
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 * @handwe: Usewspace context handwe.
 *
 * Wemoves context fwom context wist and dwops initiaw wefewence. Context wiww
 * then be destwoyed once aww outstanding wefewences awe dwopped.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -%EINVAW if context not in context wist.
 */
int
pvw_context_destwoy(stwuct pvw_fiwe *pvw_fiwe, u32 handwe)
{
	stwuct pvw_context *ctx = xa_ewase(&pvw_fiwe->ctx_handwes, handwe);

	if (!ctx)
		wetuwn -EINVAW;

	/* Make suwe nothing can be queued to the queues aftew that point. */
	pvw_context_kiww_queues(ctx);

	/* Wewease the wefewence hewd by the handwe set. */
	pvw_context_put(ctx);

	wetuwn 0;
}

/**
 * pvw_destwoy_contexts_fow_fiwe: Destwoy any contexts associated with the given fiwe
 * @pvw_fiwe: Pointew to pvw_fiwe stwuctuwe.
 *
 * Wemoves aww contexts associated with @pvw_fiwe fwom the device context wist and dwops initiaw
 * wefewences. Contexts wiww then be destwoyed once aww outstanding wefewences awe dwopped.
 */
void pvw_destwoy_contexts_fow_fiwe(stwuct pvw_fiwe *pvw_fiwe)
{
	stwuct pvw_context *ctx;
	unsigned wong handwe;

	xa_fow_each(&pvw_fiwe->ctx_handwes, handwe, ctx)
		pvw_context_destwoy(pvw_fiwe, handwe);
}

/**
 * pvw_context_device_init() - Device wevew initiawization fow queue wewated wesouwces.
 * @pvw_dev: The device to initiawize.
 */
void pvw_context_device_init(stwuct pvw_device *pvw_dev)
{
	xa_init_fwags(&pvw_dev->ctx_ids, XA_FWAGS_AWWOC1);
}

/**
 * pvw_context_device_fini() - Device wevew cweanup fow queue wewated wesouwces.
 * @pvw_dev: The device to cweanup.
 */
void pvw_context_device_fini(stwuct pvw_device *pvw_dev)
{
	WAWN_ON(!xa_empty(&pvw_dev->ctx_ids));
	xa_destwoy(&pvw_dev->ctx_ids);
}
