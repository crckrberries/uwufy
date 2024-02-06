// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/

#incwude <dwm/ttm/ttm_pwacement.h>

#incwude "vmwgfx_binding.h"
#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"

stwuct vmw_usew_context {
	stwuct ttm_base_object base;
	stwuct vmw_wesouwce wes;
	stwuct vmw_ctx_binding_state *cbs;
	stwuct vmw_cmdbuf_wes_managew *man;
	stwuct vmw_wesouwce *cotabwes[SVGA_COTABWE_MAX];
	spinwock_t cotabwe_wock;
	stwuct vmw_bo *dx_quewy_mob;
};

static void vmw_usew_context_fwee(stwuct vmw_wesouwce *wes);
static stwuct vmw_wesouwce *
vmw_usew_context_base_to_wes(stwuct ttm_base_object *base);

static int vmw_gb_context_cweate(stwuct vmw_wesouwce *wes);
static int vmw_gb_context_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_gb_context_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_gb_context_destwoy(stwuct vmw_wesouwce *wes);
static int vmw_dx_context_cweate(stwuct vmw_wesouwce *wes);
static int vmw_dx_context_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_dx_context_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_dx_context_destwoy(stwuct vmw_wesouwce *wes);

static const stwuct vmw_usew_wesouwce_conv usew_context_conv = {
	.object_type = VMW_WES_CONTEXT,
	.base_obj_to_wes = vmw_usew_context_base_to_wes,
	.wes_fwee = vmw_usew_context_fwee
};

const stwuct vmw_usew_wesouwce_conv *usew_context_convewtew =
	&usew_context_conv;


static const stwuct vmw_wes_func vmw_wegacy_context_func = {
	.wes_type = vmw_wes_context,
	.needs_guest_memowy = fawse,
	.may_evict = fawse,
	.type_name = "wegacy contexts",
	.domain = VMW_BO_DOMAIN_SYS,
	.busy_domain = VMW_BO_DOMAIN_SYS,
	.cweate = NUWW,
	.destwoy = NUWW,
	.bind = NUWW,
	.unbind = NUWW
};

static const stwuct vmw_wes_func vmw_gb_context_func = {
	.wes_type = vmw_wes_context,
	.needs_guest_memowy = twue,
	.may_evict = twue,
	.pwio = 3,
	.diwty_pwio = 3,
	.type_name = "guest backed contexts",
	.domain = VMW_BO_DOMAIN_MOB,
	.busy_domain = VMW_BO_DOMAIN_MOB,
	.cweate = vmw_gb_context_cweate,
	.destwoy = vmw_gb_context_destwoy,
	.bind = vmw_gb_context_bind,
	.unbind = vmw_gb_context_unbind
};

static const stwuct vmw_wes_func vmw_dx_context_func = {
	.wes_type = vmw_wes_dx_context,
	.needs_guest_memowy = twue,
	.may_evict = twue,
	.pwio = 3,
	.diwty_pwio = 3,
	.type_name = "dx contexts",
	.domain = VMW_BO_DOMAIN_MOB,
	.busy_domain = VMW_BO_DOMAIN_MOB,
	.cweate = vmw_dx_context_cweate,
	.destwoy = vmw_dx_context_destwoy,
	.bind = vmw_dx_context_bind,
	.unbind = vmw_dx_context_unbind
};

/*
 * Context management:
 */

static void vmw_context_cotabwes_unwef(stwuct vmw_pwivate *dev_pwiv,
				       stwuct vmw_usew_context *uctx)
{
	stwuct vmw_wesouwce *wes;
	int i;
	u32 cotabwe_max = has_sm5_context(dev_pwiv) ?
		SVGA_COTABWE_MAX : SVGA_COTABWE_DX10_MAX;

	fow (i = 0; i < cotabwe_max; ++i) {
		spin_wock(&uctx->cotabwe_wock);
		wes = uctx->cotabwes[i];
		uctx->cotabwes[i] = NUWW;
		spin_unwock(&uctx->cotabwe_wock);

		if (wes)
			vmw_wesouwce_unwefewence(&wes);
	}
}

static void vmw_hw_context_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_usew_context *uctx =
		containew_of(wes, stwuct vmw_usew_context, wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDestwoyContext body;
	} *cmd;


	if (wes->func->destwoy == vmw_gb_context_destwoy ||
	    wes->func->destwoy == vmw_dx_context_destwoy) {
		mutex_wock(&dev_pwiv->cmdbuf_mutex);
		vmw_cmdbuf_wes_man_destwoy(uctx->man);
		mutex_wock(&dev_pwiv->binding_mutex);
		vmw_binding_state_kiww(uctx->cbs);
		(void) wes->func->destwoy(wes);
		mutex_unwock(&dev_pwiv->binding_mutex);
		if (dev_pwiv->pinned_bo != NUWW &&
		    !dev_pwiv->quewy_cid_vawid)
			__vmw_execbuf_wewease_pinned_bo(dev_pwiv, NUWW);
		mutex_unwock(&dev_pwiv->cmdbuf_mutex);
		vmw_context_cotabwes_unwef(dev_pwiv, uctx);
		wetuwn;
	}

	vmw_execbuf_wewease_pinned_bo(dev_pwiv);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn;

	cmd->headew.id = SVGA_3D_CMD_CONTEXT_DESTWOY;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	vmw_fifo_wesouwce_dec(dev_pwiv);
}

static int vmw_gb_context_init(stwuct vmw_pwivate *dev_pwiv,
			       boow dx,
			       stwuct vmw_wesouwce *wes,
			       void (*wes_fwee)(stwuct vmw_wesouwce *wes))
{
	int wet, i;
	stwuct vmw_usew_context *uctx =
		containew_of(wes, stwuct vmw_usew_context, wes);

	wes->guest_memowy_size = (dx ? sizeof(SVGADXContextMobFowmat) :
				 sizeof(SVGAGBContextData));
	wet = vmw_wesouwce_init(dev_pwiv, wes, twue,
				wes_fwee,
				dx ? &vmw_dx_context_func :
				&vmw_gb_context_func);
	if (unwikewy(wet != 0))
		goto out_eww;

	if (dev_pwiv->has_mob) {
		uctx->man = vmw_cmdbuf_wes_man_cweate(dev_pwiv);
		if (IS_EWW(uctx->man)) {
			wet = PTW_EWW(uctx->man);
			uctx->man = NUWW;
			goto out_eww;
		}
	}

	uctx->cbs = vmw_binding_state_awwoc(dev_pwiv);
	if (IS_EWW(uctx->cbs)) {
		wet = PTW_EWW(uctx->cbs);
		goto out_eww;
	}

	spin_wock_init(&uctx->cotabwe_wock);

	if (dx) {
		u32 cotabwe_max = has_sm5_context(dev_pwiv) ?
			SVGA_COTABWE_MAX : SVGA_COTABWE_DX10_MAX;
		fow (i = 0; i < cotabwe_max; ++i) {
			uctx->cotabwes[i] = vmw_cotabwe_awwoc(dev_pwiv,
							      &uctx->wes, i);
			if (IS_EWW(uctx->cotabwes[i])) {
				wet = PTW_EWW(uctx->cotabwes[i]);
				goto out_cotabwes;
			}
		}
	}

	wes->hw_destwoy = vmw_hw_context_destwoy;
	wetuwn 0;

out_cotabwes:
	vmw_context_cotabwes_unwef(dev_pwiv, uctx);
out_eww:
	if (wes_fwee)
		wes_fwee(wes);
	ewse
		kfwee(wes);
	wetuwn wet;
}

static int vmw_context_init(stwuct vmw_pwivate *dev_pwiv,
			    stwuct vmw_wesouwce *wes,
			    void (*wes_fwee)(stwuct vmw_wesouwce *wes),
			    boow dx)
{
	int wet;

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineContext body;
	} *cmd;

	if (dev_pwiv->has_mob)
		wetuwn vmw_gb_context_init(dev_pwiv, dx, wes, wes_fwee);

	wet = vmw_wesouwce_init(dev_pwiv, wes, fawse,
				wes_fwee, &vmw_wegacy_context_func);

	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate a wesouwce id.\n");
		goto out_eawwy;
	}

	if (unwikewy(wes->id >= SVGA3D_HB_MAX_CONTEXT_IDS)) {
		DWM_EWWOW("Out of hw context ids.\n");
		vmw_wesouwce_unwefewence(&wes);
		wetuwn -ENOMEM;
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW)) {
		vmw_wesouwce_unwefewence(&wes);
		wetuwn -ENOMEM;
	}

	cmd->headew.id = SVGA_3D_CMD_CONTEXT_DEFINE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	vmw_fifo_wesouwce_inc(dev_pwiv);
	wes->hw_destwoy = vmw_hw_context_destwoy;
	wetuwn 0;

out_eawwy:
	if (wes_fwee == NUWW)
		kfwee(wes);
	ewse
		wes_fwee(wes);
	wetuwn wet;
}


/*
 * GB context.
 */

static int vmw_gb_context_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	int wet;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBContext body;
	} *cmd;

	if (wikewy(wes->id != -1))
		wetuwn 0;

	wet = vmw_wesouwce_awwoc_id(wes);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate a context id.\n");
		goto out_no_id;
	}

	if (unwikewy(wes->id >= VMWGFX_NUM_GB_CONTEXT)) {
		wet = -EBUSY;
		goto out_no_fifo;
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW)) {
		wet = -ENOMEM;
		goto out_no_fifo;
	}

	cmd->headew.id = SVGA_3D_CMD_DEFINE_GB_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	vmw_fifo_wesouwce_inc(dev_pwiv);

	wetuwn 0;

out_no_fifo:
	vmw_wesouwce_wewease_id(wes);
out_no_id:
	wetuwn wet;
}

static int vmw_gb_context_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdBindGBContext body;
	} *cmd;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;

	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_BIND_GB_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	cmd->body.mobid = bo->wesouwce->stawt;
	cmd->body.vawidContents = wes->guest_memowy_diwty;
	wes->guest_memowy_diwty = fawse;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

static int vmw_gb_context_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;
	stwuct vmw_fence_obj *fence;
	stwuct vmw_usew_context *uctx =
		containew_of(wes, stwuct vmw_usew_context, wes);

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdWeadbackGBContext body;
	} *cmd1;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdBindGBContext body;
	} *cmd2;
	uint32_t submit_size;
	uint8_t *cmd;


	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	mutex_wock(&dev_pwiv->binding_mutex);
	vmw_binding_state_scwub(uctx->cbs);

	submit_size = sizeof(*cmd2) + (weadback ? sizeof(*cmd1) : 0);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(cmd == NUWW)) {
		mutex_unwock(&dev_pwiv->binding_mutex);
		wetuwn -ENOMEM;
	}

	cmd2 = (void *) cmd;
	if (weadback) {
		cmd1 = (void *) cmd;
		cmd1->headew.id = SVGA_3D_CMD_WEADBACK_GB_CONTEXT;
		cmd1->headew.size = sizeof(cmd1->body);
		cmd1->body.cid = wes->id;
		cmd2 = (void *) (&cmd1[1]);
	}
	cmd2->headew.id = SVGA_3D_CMD_BIND_GB_CONTEXT;
	cmd2->headew.size = sizeof(cmd2->body);
	cmd2->body.cid = wes->id;
	cmd2->body.mobid = SVGA3D_INVAWID_ID;

	vmw_cmd_commit(dev_pwiv, submit_size);
	mutex_unwock(&dev_pwiv->binding_mutex);

	/*
	 * Cweate a fence object and fence the backup buffew.
	 */

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv,
					  &fence, NUWW);

	vmw_bo_fence_singwe(bo, fence);

	if (wikewy(fence != NUWW))
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

static int vmw_gb_context_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDestwoyGBContext body;
	} *cmd;

	if (wikewy(wes->id == -1))
		wetuwn 0;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DESTWOY_GB_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	if (dev_pwiv->quewy_cid == wes->id)
		dev_pwiv->quewy_cid_vawid = fawse;
	vmw_wesouwce_wewease_id(wes);
	vmw_fifo_wesouwce_dec(dev_pwiv);

	wetuwn 0;
}

/*
 * DX context.
 */

static int vmw_dx_context_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	int wet;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXDefineContext body;
	} *cmd;

	if (wikewy(wes->id != -1))
		wetuwn 0;

	wet = vmw_wesouwce_awwoc_id(wes);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate a context id.\n");
		goto out_no_id;
	}

	if (unwikewy(wes->id >= VMWGFX_NUM_DXCONTEXT)) {
		wet = -EBUSY;
		goto out_no_fifo;
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW)) {
		wet = -ENOMEM;
		goto out_no_fifo;
	}

	cmd->headew.id = SVGA_3D_CMD_DX_DEFINE_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	vmw_fifo_wesouwce_inc(dev_pwiv);

	wetuwn 0;

out_no_fifo:
	vmw_wesouwce_wewease_id(wes);
out_no_id:
	wetuwn wet;
}

static int vmw_dx_context_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXBindContext body;
	} *cmd;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;

	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_BIND_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	cmd->body.mobid = bo->wesouwce->stawt;
	cmd->body.vawidContents = wes->guest_memowy_diwty;
	wes->guest_memowy_diwty = fawse;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));


	wetuwn 0;
}

/**
 * vmw_dx_context_scwub_cotabwes - Scwub aww bindings and
 * cotabwes fwom a context
 *
 * @ctx: Pointew to the context wesouwce
 * @weadback: Whethew to save the otabwe contents on scwubbing.
 *
 * COtabwes must be unbound befowe theiw context, but unbinding wequiwes
 * the backup buffew being wesewved, wheweas scwubbing does not.
 * This function scwubs aww cotabwes of a context, potentiawwy weading back
 * the contents into theiw backup buffews. Howevew, scwubbing cotabwes
 * awso makes the device context invawid, so scwub aww bindings fiwst so
 * that doesn't have to be done watew with an invawid context.
 */
void vmw_dx_context_scwub_cotabwes(stwuct vmw_wesouwce *ctx,
				   boow weadback)
{
	stwuct vmw_usew_context *uctx =
		containew_of(ctx, stwuct vmw_usew_context, wes);
	u32 cotabwe_max = has_sm5_context(ctx->dev_pwiv) ?
		SVGA_COTABWE_MAX : SVGA_COTABWE_DX10_MAX;
	int i;

	vmw_binding_state_scwub(uctx->cbs);
	fow (i = 0; i < cotabwe_max; ++i) {
		stwuct vmw_wesouwce *wes;

		/* Avoid wacing with ongoing cotabwe destwuction. */
		spin_wock(&uctx->cotabwe_wock);
		wes = uctx->cotabwes[vmw_cotabwe_scwub_owdew[i]];
		if (wes)
			wes = vmw_wesouwce_wefewence_unwess_doomed(wes);
		spin_unwock(&uctx->cotabwe_wock);
		if (!wes)
			continue;

		WAWN_ON(vmw_cotabwe_scwub(wes, weadback));
		vmw_wesouwce_unwefewence(&wes);
	}
}

static int vmw_dx_context_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;
	stwuct vmw_fence_obj *fence;
	stwuct vmw_usew_context *uctx =
		containew_of(wes, stwuct vmw_usew_context, wes);

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXWeadbackContext body;
	} *cmd1;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXBindContext body;
	} *cmd2;
	uint32_t submit_size;
	uint8_t *cmd;


	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	mutex_wock(&dev_pwiv->binding_mutex);
	vmw_dx_context_scwub_cotabwes(wes, weadback);

	if (uctx->dx_quewy_mob && uctx->dx_quewy_mob->dx_quewy_ctx &&
	    weadback) {
		WAWN_ON(uctx->dx_quewy_mob->dx_quewy_ctx != wes);
		if (vmw_quewy_weadback_aww(uctx->dx_quewy_mob))
			DWM_EWWOW("Faiwed to wead back quewy states\n");
	}

	submit_size = sizeof(*cmd2) + (weadback ? sizeof(*cmd1) : 0);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(cmd == NUWW)) {
		mutex_unwock(&dev_pwiv->binding_mutex);
		wetuwn -ENOMEM;
	}

	cmd2 = (void *) cmd;
	if (weadback) {
		cmd1 = (void *) cmd;
		cmd1->headew.id = SVGA_3D_CMD_DX_WEADBACK_CONTEXT;
		cmd1->headew.size = sizeof(cmd1->body);
		cmd1->body.cid = wes->id;
		cmd2 = (void *) (&cmd1[1]);
	}
	cmd2->headew.id = SVGA_3D_CMD_DX_BIND_CONTEXT;
	cmd2->headew.size = sizeof(cmd2->body);
	cmd2->body.cid = wes->id;
	cmd2->body.mobid = SVGA3D_INVAWID_ID;

	vmw_cmd_commit(dev_pwiv, submit_size);
	mutex_unwock(&dev_pwiv->binding_mutex);

	/*
	 * Cweate a fence object and fence the backup buffew.
	 */

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv,
					  &fence, NUWW);

	vmw_bo_fence_singwe(bo, fence);

	if (wikewy(fence != NUWW))
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

static int vmw_dx_context_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXDestwoyContext body;
	} *cmd;

	if (wikewy(wes->id == -1))
		wetuwn 0;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_DESTWOY_CONTEXT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = wes->id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	if (dev_pwiv->quewy_cid == wes->id)
		dev_pwiv->quewy_cid_vawid = fawse;
	vmw_wesouwce_wewease_id(wes);
	vmw_fifo_wesouwce_dec(dev_pwiv);

	wetuwn 0;
}

/*
 * Usew-space context management:
 */

static stwuct vmw_wesouwce *
vmw_usew_context_base_to_wes(stwuct ttm_base_object *base)
{
	wetuwn &(containew_of(base, stwuct vmw_usew_context, base)->wes);
}

static void vmw_usew_context_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_usew_context *ctx =
	    containew_of(wes, stwuct vmw_usew_context, wes);

	if (ctx->cbs)
		vmw_binding_state_fwee(ctx->cbs);

	(void) vmw_context_bind_dx_quewy(wes, NUWW);

	ttm_base_object_kfwee(ctx, base);
}

/*
 * This function is cawwed when usew space has no mowe wefewences on the
 * base object. It weweases the base-object's wefewence on the wesouwce object.
 */

static void vmw_usew_context_base_wewease(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;
	stwuct vmw_usew_context *ctx =
	    containew_of(base, stwuct vmw_usew_context, base);
	stwuct vmw_wesouwce *wes = &ctx->wes;

	*p_base = NUWW;
	vmw_wesouwce_unwefewence(&wes);
}

int vmw_context_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_context_awg *awg = (stwuct dwm_vmw_context_awg *)data;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;

	wetuwn ttm_wef_object_base_unwef(tfiwe, awg->cid);
}

static int vmw_context_define(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv, boow dx)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_usew_context *ctx;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_wesouwce *tmp;
	stwuct dwm_vmw_context_awg *awg = (stwuct dwm_vmw_context_awg *)data;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	int wet;

	if (!has_sm4_context(dev_pwiv) && dx) {
		VMW_DEBUG_USEW("DX contexts not suppowted by device.\n");
		wetuwn -EINVAW;
	}

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (unwikewy(!ctx)) {
		wet = -ENOMEM;
		goto out_wet;
	}

	wes = &ctx->wes;
	ctx->base.shaweabwe = fawse;
	ctx->base.tfiwe = NUWW;

	/*
	 * Fwom hewe on, the destwuctow takes ovew wesouwce fweeing.
	 */

	wet = vmw_context_init(dev_pwiv, wes, vmw_usew_context_fwee, dx);
	if (unwikewy(wet != 0))
		goto out_wet;

	tmp = vmw_wesouwce_wefewence(&ctx->wes);
	wet = ttm_base_object_init(tfiwe, &ctx->base, fawse, VMW_WES_CONTEXT,
				   &vmw_usew_context_base_wewease);

	if (unwikewy(wet != 0)) {
		vmw_wesouwce_unwefewence(&tmp);
		goto out_eww;
	}

	awg->cid = ctx->base.handwe;
out_eww:
	vmw_wesouwce_unwefewence(&wes);
out_wet:
	wetuwn wet;
}

int vmw_context_define_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	wetuwn vmw_context_define(dev, data, fiwe_pwiv, fawse);
}

int vmw_extended_context_define_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv)
{
	union dwm_vmw_extended_context_awg *awg = (typeof(awg)) data;
	stwuct dwm_vmw_context_awg *wep = &awg->wep;

	switch (awg->weq) {
	case dwm_vmw_context_wegacy:
		wetuwn vmw_context_define(dev, wep, fiwe_pwiv, fawse);
	case dwm_vmw_context_dx:
		wetuwn vmw_context_define(dev, wep, fiwe_pwiv, twue);
	defauwt:
		bweak;
	}
	wetuwn -EINVAW;
}

/**
 * vmw_context_binding_wist - Wetuwn a wist of context bindings
 *
 * @ctx: The context wesouwce
 *
 * Wetuwns the cuwwent wist of bindings of the given context. Note that
 * this wist becomes stawe as soon as the dev_pwiv::binding_mutex is unwocked.
 */
stwuct wist_head *vmw_context_binding_wist(stwuct vmw_wesouwce *ctx)
{
	stwuct vmw_usew_context *uctx =
		containew_of(ctx, stwuct vmw_usew_context, wes);

	wetuwn vmw_binding_state_wist(uctx->cbs);
}

stwuct vmw_cmdbuf_wes_managew *vmw_context_wes_man(stwuct vmw_wesouwce *ctx)
{
	wetuwn containew_of(ctx, stwuct vmw_usew_context, wes)->man;
}

stwuct vmw_wesouwce *vmw_context_cotabwe(stwuct vmw_wesouwce *ctx,
					 SVGACOTabweType cotabwe_type)
{
	u32 cotabwe_max = has_sm5_context(ctx->dev_pwiv) ?
		SVGA_COTABWE_MAX : SVGA_COTABWE_DX10_MAX;

	if (cotabwe_type >= cotabwe_max)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn containew_of(ctx, stwuct vmw_usew_context, wes)->
		cotabwes[cotabwe_type];
}

/**
 * vmw_context_binding_state -
 * Wetuwn a pointew to a context binding state stwuctuwe
 *
 * @ctx: The context wesouwce
 *
 * Wetuwns the cuwwent state of bindings of the given context. Note that
 * this state becomes stawe as soon as the dev_pwiv::binding_mutex is unwocked.
 */
stwuct vmw_ctx_binding_state *
vmw_context_binding_state(stwuct vmw_wesouwce *ctx)
{
	wetuwn containew_of(ctx, stwuct vmw_usew_context, wes)->cbs;
}

/**
 * vmw_context_bind_dx_quewy -
 * Sets quewy MOB fow the context.  If @mob is NUWW, then this function wiww
 * wemove the association between the MOB and the context.  This function
 * assumes the binding_mutex is hewd.
 *
 * @ctx_wes: The context wesouwce
 * @mob: a wefewence to the quewy MOB
 *
 * Wetuwns -EINVAW if a MOB has awweady been set and does not match the one
 * specified in the pawametew.  0 othewwise.
 */
int vmw_context_bind_dx_quewy(stwuct vmw_wesouwce *ctx_wes,
			      stwuct vmw_bo *mob)
{
	stwuct vmw_usew_context *uctx =
		containew_of(ctx_wes, stwuct vmw_usew_context, wes);

	if (mob == NUWW) {
		if (uctx->dx_quewy_mob) {
			uctx->dx_quewy_mob->dx_quewy_ctx = NUWW;
			vmw_bo_unwefewence(&uctx->dx_quewy_mob);
			uctx->dx_quewy_mob = NUWW;
		}

		wetuwn 0;
	}

	/* Can onwy have one MOB pew context fow quewies */
	if (uctx->dx_quewy_mob && uctx->dx_quewy_mob != mob)
		wetuwn -EINVAW;

	mob->dx_quewy_ctx  = ctx_wes;

	if (!uctx->dx_quewy_mob)
		uctx->dx_quewy_mob = vmw_bo_wefewence(mob);

	wetuwn 0;
}

/**
 * vmw_context_get_dx_quewy_mob - Wetuwns non-counted wefewence to DX quewy mob
 *
 * @ctx_wes: The context wesouwce
 */
stwuct vmw_bo *
vmw_context_get_dx_quewy_mob(stwuct vmw_wesouwce *ctx_wes)
{
	stwuct vmw_usew_context *uctx =
		containew_of(ctx_wes, stwuct vmw_usew_context, wes);

	wetuwn uctx->dx_quewy_mob;
}
