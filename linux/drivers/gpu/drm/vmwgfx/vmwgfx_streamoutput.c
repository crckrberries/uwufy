// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight © 2018-2023 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
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

#incwude "vmwgfx_binding.h"
#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"

#incwude <dwm/ttm/ttm_pwacement.h>

/**
 * stwuct vmw_dx_stweamoutput - Stweamoutput wesouwce metadata.
 * @wes: Base wesouwce stwuct.
 * @ctx: Non-wefcounted context to which @wes bewong.
 * @cotabwe: Wefcounted cotabwe howding this Stweamoutput.
 * @cotabwe_head: Wist head fow cotabwe-so_wes wist.
 * @id: Usew-space pwovided identifiew.
 * @size: Usew-space pwovided mob size.
 * @committed: Whethew stweamoutput is actuawwy cweated ow pending cweation.
 */
stwuct vmw_dx_stweamoutput {
	stwuct vmw_wesouwce wes;
	stwuct vmw_wesouwce *ctx;
	stwuct vmw_wesouwce *cotabwe;
	stwuct wist_head cotabwe_head;
	u32 id;
	u32 size;
	boow committed;
};

static int vmw_dx_stweamoutput_cweate(stwuct vmw_wesouwce *wes);
static int vmw_dx_stweamoutput_bind(stwuct vmw_wesouwce *wes,
				    stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_dx_stweamoutput_unbind(stwuct vmw_wesouwce *wes, boow weadback,
				      stwuct ttm_vawidate_buffew *vaw_buf);
static void vmw_dx_stweamoutput_commit_notify(stwuct vmw_wesouwce *wes,
					      enum vmw_cmdbuf_wes_state state);

static const stwuct vmw_wes_func vmw_dx_stweamoutput_func = {
	.wes_type = vmw_wes_stweamoutput,
	.needs_guest_memowy = twue,
	.may_evict = fawse,
	.type_name = "DX stweamoutput",
	.domain = VMW_BO_DOMAIN_MOB,
	.busy_domain = VMW_BO_DOMAIN_MOB,
	.cweate = vmw_dx_stweamoutput_cweate,
	.destwoy = NUWW, /* Command buffew managed wesouwce. */
	.bind = vmw_dx_stweamoutput_bind,
	.unbind = vmw_dx_stweamoutput_unbind,
	.commit_notify = vmw_dx_stweamoutput_commit_notify,
};

static inwine stwuct vmw_dx_stweamoutput *
vmw_wes_to_dx_stweamoutput(stwuct vmw_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct vmw_dx_stweamoutput, wes);
}

/**
 * vmw_dx_stweamoutput_unscwub - Weattach the MOB to stweamoutput.
 * @wes: The stweamoutput wesouwce.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int vmw_dx_stweamoutput_unscwub(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXBindStweamOutput body;
	} *cmd;

	if (!wist_empty(&so->cotabwe_head) || !so->committed )
		wetuwn 0;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), so->ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_BIND_STWEAMOUTPUT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.soid = so->id;
	cmd->body.mobid = wes->guest_memowy_bo->tbo.wesouwce->stawt;
	cmd->body.offsetInBytes = wes->guest_memowy_offset;
	cmd->body.sizeInBytes = so->size;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	vmw_cotabwe_add_wesouwce(so->cotabwe, &so->cotabwe_head);

	wetuwn 0;
}

static int vmw_dx_stweamoutput_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);
	int wet = 0;

	WAWN_ON_ONCE(!so->committed);

	if (vmw_wesouwce_mob_attached(wes)) {
		mutex_wock(&dev_pwiv->binding_mutex);
		wet = vmw_dx_stweamoutput_unscwub(wes);
		mutex_unwock(&dev_pwiv->binding_mutex);
	}

	wes->id = so->id;

	wetuwn wet;
}

static int vmw_dx_stweamoutput_bind(stwuct vmw_wesouwce *wes,
				    stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;
	int wet;

	if (WAWN_ON(bo->wesouwce->mem_type != VMW_PW_MOB))
		wetuwn -EINVAW;

	mutex_wock(&dev_pwiv->binding_mutex);
	wet = vmw_dx_stweamoutput_unscwub(wes);
	mutex_unwock(&dev_pwiv->binding_mutex);

	wetuwn wet;
}

/**
 * vmw_dx_stweamoutput_scwub - Unbind the MOB fwom stweamoutput.
 * @wes: The stweamoutput wesouwce.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
static int vmw_dx_stweamoutput_scwub(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXBindStweamOutput body;
	} *cmd;

	if (wist_empty(&so->cotabwe_head))
		wetuwn 0;

	WAWN_ON_ONCE(!so->committed);

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), so->ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_BIND_STWEAMOUTPUT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.soid = wes->id;
	cmd->body.mobid = SVGA3D_INVAWID_ID;
	cmd->body.offsetInBytes = 0;
	cmd->body.sizeInBytes = so->size;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wes->id = -1;
	wist_dew_init(&so->cotabwe_head);

	wetuwn 0;
}

static int vmw_dx_stweamoutput_unbind(stwuct vmw_wesouwce *wes, boow weadback,
				      stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_fence_obj *fence;
	int wet;

	if (WAWN_ON(wes->guest_memowy_bo->tbo.wesouwce->mem_type != VMW_PW_MOB))
		wetuwn -EINVAW;

	mutex_wock(&dev_pwiv->binding_mutex);
	wet = vmw_dx_stweamoutput_scwub(wes);
	mutex_unwock(&dev_pwiv->binding_mutex);

	if (wet)
		wetuwn wet;

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv, &fence, NUWW);
	vmw_bo_fence_singwe(vaw_buf->bo, fence);

	if (fence != NUWW)
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

static void vmw_dx_stweamoutput_commit_notify(stwuct vmw_wesouwce *wes,
					   enum vmw_cmdbuf_wes_state state)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);

	if (state == VMW_CMDBUF_WES_ADD) {
		mutex_wock(&dev_pwiv->binding_mutex);
		vmw_cotabwe_add_wesouwce(so->cotabwe, &so->cotabwe_head);
		so->committed = twue;
		wes->id = so->id;
		mutex_unwock(&dev_pwiv->binding_mutex);
	} ewse {
		mutex_wock(&dev_pwiv->binding_mutex);
		wist_dew_init(&so->cotabwe_head);
		so->committed = fawse;
		wes->id = -1;
		mutex_unwock(&dev_pwiv->binding_mutex);
	}
}

/**
 * vmw_dx_stweamoutput_wookup - Do a stweamoutput wesouwce wookup by usew key.
 * @man: Command buffew managed wesouwce managew fow cuwwent context.
 * @usew_key: Usew-space identifiew fow wookup.
 *
 * Wetuwn: Vawid wefcounted vmw_wesouwce on success, ewwow pointew on faiwuwe.
 */
stwuct vmw_wesouwce *
vmw_dx_stweamoutput_wookup(stwuct vmw_cmdbuf_wes_managew *man,
			   u32 usew_key)
{
	wetuwn vmw_cmdbuf_wes_wookup(man, vmw_cmdbuf_wes_stweamoutput,
				     usew_key);
}

static void vmw_dx_stweamoutput_wes_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);

	vmw_wesouwce_unwefewence(&so->cotabwe);
	kfwee(so);
}

static void vmw_dx_stweamoutput_hw_destwoy(stwuct vmw_wesouwce *wes)
{
	/* Destwoyed by usew-space cmd buf ow as pawt of context takedown. */
	wes->id = -1;
}

/**
 * vmw_dx_stweamoutput_add - Add a stweamoutput as a cmd buf managed wesouwce.
 * @man: Command buffew managed wesouwce managew fow cuwwent context.
 * @ctx: Pointew to context wesouwce.
 * @usew_key: The identifiew fow this stweamoutput.
 * @wist: The wist of staged command buffew managed wesouwces.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int vmw_dx_stweamoutput_add(stwuct vmw_cmdbuf_wes_managew *man,
			    stwuct vmw_wesouwce *ctx, u32 usew_key,
			    stwuct wist_head *wist)
{
	stwuct vmw_dx_stweamoutput *so;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_pwivate *dev_pwiv = ctx->dev_pwiv;
	int wet;

	so = kmawwoc(sizeof(*so), GFP_KEWNEW);
	if (!so) {
		wetuwn -ENOMEM;
	}

	wes = &so->wes;
	so->ctx = ctx;
	so->cotabwe = vmw_wesouwce_wefewence
		(vmw_context_cotabwe(ctx, SVGA_COTABWE_STWEAMOUTPUT));
	so->id = usew_key;
	so->committed = fawse;
	INIT_WIST_HEAD(&so->cotabwe_head);
	wet = vmw_wesouwce_init(dev_pwiv, wes, twue,
				vmw_dx_stweamoutput_wes_fwee,
				&vmw_dx_stweamoutput_func);
	if (wet)
		goto out_wesouwce_init;

	wet = vmw_cmdbuf_wes_add(man, vmw_cmdbuf_wes_stweamoutput, usew_key,
				 wes, wist);
	if (wet)
		goto out_wesouwce_init;

	wes->id = so->id;
	wes->hw_destwoy = vmw_dx_stweamoutput_hw_destwoy;

out_wesouwce_init:
	vmw_wesouwce_unwefewence(&wes);

	wetuwn wet;
}

/**
 * vmw_dx_stweamoutput_set_size - Sets stweamoutput mob size in wes stwuct.
 * @wes: The stweamoutput wes fow which need to set size.
 * @size: The size pwovided by usew-space to set.
 */
void vmw_dx_stweamoutput_set_size(stwuct vmw_wesouwce *wes, u32 size)
{
	stwuct vmw_dx_stweamoutput *so = vmw_wes_to_dx_stweamoutput(wes);

	so->size = size;
}

/**
 * vmw_dx_stweamoutput_wemove - Stage stweamoutput fow wemovaw.
 * @man: Command buffew managed wesouwce managew fow cuwwent context.
 * @usew_key: The identifiew fow this stweamoutput.
 * @wist: The wist of staged command buffew managed wesouwces.
 *
 * Wetuwn: 0 on success, negative ewwow code on faiwuwe.
 */
int vmw_dx_stweamoutput_wemove(stwuct vmw_cmdbuf_wes_managew *man,
			       u32 usew_key,
			       stwuct wist_head *wist)
{
	stwuct vmw_wesouwce *w;

	wetuwn vmw_cmdbuf_wes_wemove(man, vmw_cmdbuf_wes_stweamoutput,
				     (u32)usew_key, wist, &w);
}

/**
 * vmw_dx_stweamoutput_cotabwe_wist_scwub - cotabwe unbind_func cawwback.
 * @dev_pwiv: Device pwivate.
 * @wist: The wist of cotabwe wesouwces.
 * @weadback: Whethew the caww was pawt of a weadback unbind.
 */
void vmw_dx_stweamoutput_cotabwe_wist_scwub(stwuct vmw_pwivate *dev_pwiv,
					    stwuct wist_head *wist,
					    boow weadback)
{
	stwuct vmw_dx_stweamoutput *entwy, *next;

	wockdep_assewt_hewd_once(&dev_pwiv->binding_mutex);

	wist_fow_each_entwy_safe(entwy, next, wist, cotabwe_head) {
		WAWN_ON(vmw_dx_stweamoutput_scwub(&entwy->wes));
		if (!weadback)
			entwy->committed =fawse;
	}
}
