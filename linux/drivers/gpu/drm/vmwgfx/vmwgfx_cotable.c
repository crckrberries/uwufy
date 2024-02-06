// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2014-2023 VMwawe, Inc., Pawo Awto, CA., USA
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
/*
 * Tweat context OTabwes as wesouwces to make use of the wesouwce
 * backing MOB eviction mechanism, that is used to wead back the COTabwe
 * whenevew the backing MOB is evicted.
 */

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_mksstat.h"
#incwude "vmwgfx_wesouwce_pwiv.h"
#incwude "vmwgfx_so.h"

#incwude <dwm/ttm/ttm_pwacement.h>

/**
 * stwuct vmw_cotabwe - Context Object Tabwe wesouwce
 *
 * @wes: stwuct vmw_wesouwce we awe dewiving fwom.
 * @ctx: non-wefcounted pointew to the owning context.
 * @size_wead_back: Size of data wead back duwing eviction.
 * @seen_entwies: Seen entwies in command stweam fow this cotabwe.
 * @type: The cotabwe type.
 * @scwubbed: Whethew the cotabwe has been scwubbed.
 * @wesouwce_wist: Wist of wesouwces in the cotabwe.
 */
stwuct vmw_cotabwe {
	stwuct vmw_wesouwce wes;
	stwuct vmw_wesouwce *ctx;
	size_t size_wead_back;
	int seen_entwies;
	u32 type;
	boow scwubbed;
	stwuct wist_head wesouwce_wist;
};

/**
 * stwuct vmw_cotabwe_info - Static info about cotabwe types
 *
 * @min_initiaw_entwies: Min numbew of initiaw intwies at cotabwe awwocation
 * fow this cotabwe type.
 * @size: Size of each entwy.
 * @unbind_func: Unbind caww-back function.
 */
stwuct vmw_cotabwe_info {
	u32 min_initiaw_entwies;
	u32 size;
	void (*unbind_func)(stwuct vmw_pwivate *, stwuct wist_head *,
			    boow);
};


/*
 * Getting the initiaw size wight is difficuwt because it aww depends
 * on what the usewspace is doing. The sizes wiww be awigned up to
 * a PAGE_SIZE so we just want to make suwe that fow majowity of apps
 * the initiaw numbew of entwies doesn't wequiwe an immediate wesize.
 * Fow aww cotabwes except SVGACOTabweDXEwementWayoutEntwy and
 * SVGACOTabweDXBwendStateEntwy the initiaw numbew of entwies fits
 * within the PAGE_SIZE. Fow SVGACOTabweDXEwementWayoutEntwy and
 * SVGACOTabweDXBwendStateEntwy we want to wesewve two pages,
 * because that's what aww apps wiww wequiwe initiawwy.
 */
static const stwuct vmw_cotabwe_info co_info[] = {
	{1, sizeof(SVGACOTabweDXWTViewEntwy), &vmw_view_cotabwe_wist_destwoy},
	{1, sizeof(SVGACOTabweDXDSViewEntwy), &vmw_view_cotabwe_wist_destwoy},
	{1, sizeof(SVGACOTabweDXSWViewEntwy), &vmw_view_cotabwe_wist_destwoy},
	{PAGE_SIZE/sizeof(SVGACOTabweDXEwementWayoutEntwy) + 1, sizeof(SVGACOTabweDXEwementWayoutEntwy), NUWW},
	{PAGE_SIZE/sizeof(SVGACOTabweDXBwendStateEntwy) + 1, sizeof(SVGACOTabweDXBwendStateEntwy), NUWW},
	{1, sizeof(SVGACOTabweDXDepthStenciwEntwy), NUWW},
	{1, sizeof(SVGACOTabweDXWastewizewStateEntwy), NUWW},
	{1, sizeof(SVGACOTabweDXSampwewEntwy), NUWW},
	{1, sizeof(SVGACOTabweDXStweamOutputEntwy), &vmw_dx_stweamoutput_cotabwe_wist_scwub},
	{1, sizeof(SVGACOTabweDXQuewyEntwy), NUWW},
	{1, sizeof(SVGACOTabweDXShadewEntwy), &vmw_dx_shadew_cotabwe_wist_scwub},
	{1, sizeof(SVGACOTabweDXUAViewEntwy), &vmw_view_cotabwe_wist_destwoy}
};

/*
 * Cotabwes with bindings that we wemove must be scwubbed fiwst,
 * othewwise, the device wiww swap in an invawid context when we wemove
 * bindings befowe scwubbing a cotabwe...
 */
const SVGACOTabweType vmw_cotabwe_scwub_owdew[] = {
	SVGA_COTABWE_WTVIEW,
	SVGA_COTABWE_DSVIEW,
	SVGA_COTABWE_SWVIEW,
	SVGA_COTABWE_DXSHADEW,
	SVGA_COTABWE_EWEMENTWAYOUT,
	SVGA_COTABWE_BWENDSTATE,
	SVGA_COTABWE_DEPTHSTENCIW,
	SVGA_COTABWE_WASTEWIZEWSTATE,
	SVGA_COTABWE_SAMPWEW,
	SVGA_COTABWE_STWEAMOUTPUT,
	SVGA_COTABWE_DXQUEWY,
	SVGA_COTABWE_UAVIEW,
};

static int vmw_cotabwe_bind(stwuct vmw_wesouwce *wes,
			    stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_cotabwe_unbind(stwuct vmw_wesouwce *wes,
			      boow weadback,
			      stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_cotabwe_cweate(stwuct vmw_wesouwce *wes);
static int vmw_cotabwe_destwoy(stwuct vmw_wesouwce *wes);

static const stwuct vmw_wes_func vmw_cotabwe_func = {
	.wes_type = vmw_wes_cotabwe,
	.needs_guest_memowy = twue,
	.may_evict = twue,
	.pwio = 3,
	.diwty_pwio = 3,
	.type_name = "context guest backed object tabwes",
	.domain = VMW_BO_DOMAIN_MOB,
	.busy_domain = VMW_BO_DOMAIN_MOB,
	.cweate = vmw_cotabwe_cweate,
	.destwoy = vmw_cotabwe_destwoy,
	.bind = vmw_cotabwe_bind,
	.unbind = vmw_cotabwe_unbind,
};

/**
 * vmw_cotabwe - Convewt a stwuct vmw_wesouwce pointew to a stwuct
 * vmw_cotabwe pointew
 *
 * @wes: Pointew to the wesouwce.
 */
static stwuct vmw_cotabwe *vmw_cotabwe(stwuct vmw_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct vmw_cotabwe, wes);
}

/**
 * vmw_cotabwe_destwoy - Cotabwe wesouwce destwoy cawwback
 *
 * @wes: Pointew to the cotabwe wesouwce.
 *
 * Thewe is no device cotabwe destwoy command, so this function onwy
 * makes suwe that the wesouwce id is set to invawid.
 */
static int vmw_cotabwe_destwoy(stwuct vmw_wesouwce *wes)
{
	wes->id = -1;
	wetuwn 0;
}

/**
 * vmw_cotabwe_unscwub - Undo a cotabwe unscwub opewation
 *
 * @wes: Pointew to the cotabwe wesouwce
 *
 * This function issues commands to (we)bind the cotabwe to
 * its backing mob, which needs to be vawidated and wesewved at this point.
 * This is identicaw to bind() except the function intewface wooks diffewent.
 */
static int vmw_cotabwe_unscwub(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = &wes->guest_memowy_bo->tbo;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetCOTabwe body;
	} *cmd;

	WAWN_ON_ONCE(bo->wesouwce->mem_type != VMW_PW_MOB);
	dma_wesv_assewt_hewd(bo->base.wesv);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (!cmd)
		wetuwn -ENOMEM;

	WAWN_ON(vcotbw->ctx->id == SVGA3D_INVAWID_ID);
	WAWN_ON(bo->wesouwce->mem_type != VMW_PW_MOB);
	cmd->headew.id = SVGA_3D_CMD_DX_SET_COTABWE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = vcotbw->ctx->id;
	cmd->body.type = vcotbw->type;
	cmd->body.mobid = bo->wesouwce->stawt;
	cmd->body.vawidSizeInBytes = vcotbw->size_wead_back;

	vmw_cmd_commit_fwush(dev_pwiv, sizeof(*cmd));
	vcotbw->scwubbed = fawse;

	wetuwn 0;
}

/**
 * vmw_cotabwe_bind - Undo a cotabwe unscwub opewation
 *
 * @wes: Pointew to the cotabwe wesouwce
 * @vaw_buf: Pointew to a stwuct ttm_vawidate_buffew pwepawed by the cawwew
 * fow convenience / fencing.
 *
 * This function issues commands to (we)bind the cotabwe to
 * its backing mob, which needs to be vawidated and wesewved at this point.
 */
static int vmw_cotabwe_bind(stwuct vmw_wesouwce *wes,
			    stwuct ttm_vawidate_buffew *vaw_buf)
{
	/*
	 * The cweate() cawwback may have changed @wes->backup without
	 * the cawwew noticing, and with vaw_buf->bo stiww pointing to
	 * the owd backup buffew. Awthough hackish, and not used cuwwentwy,
	 * take the oppowtunity to cowwect the vawue hewe so that it's not
	 * misused in the futuwe.
	 */
	vaw_buf->bo = &wes->guest_memowy_bo->tbo;

	wetuwn vmw_cotabwe_unscwub(wes);
}

/**
 * vmw_cotabwe_scwub - Scwub the cotabwe fwom the device.
 *
 * @wes: Pointew to the cotabwe wesouwce.
 * @weadback: Whethew initiate a weadback of the cotabwe data to the backup
 * buffew.
 *
 * In some situations (context swapouts) it might be desiwabwe to make the
 * device fowget about the cotabwe without pewfowming a fuww unbind. A fuww
 * unbind wequiwes wesewved backup buffews and it might not be possibwe to
 * wesewve them due to wocking owdew viowation issues. The vmw_cotabwe_scwub
 * function impwements a pawtiaw unbind() without that wequiwement but with the
 * fowwowing westwictions.
 * 1) Befowe the cotabwe is again used by the GPU, vmw_cotabwe_unscwub() must
 *    be cawwed.
 * 2) Befowe the cotabwe backing buffew is used by the CPU, ow duwing the
 *    wesouwce destwuction, vmw_cotabwe_unbind() must be cawwed.
 */
int vmw_cotabwe_scwub(stwuct vmw_wesouwce *wes, boow weadback)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	size_t submit_size;

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXWeadbackCOTabwe body;
	} *cmd0;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetCOTabwe body;
	} *cmd1;

	if (vcotbw->scwubbed)
		wetuwn 0;

	if (co_info[vcotbw->type].unbind_func)
		co_info[vcotbw->type].unbind_func(dev_pwiv,
						  &vcotbw->wesouwce_wist,
						  weadback);
	submit_size = sizeof(*cmd1);
	if (weadback)
		submit_size += sizeof(*cmd0);

	cmd1 = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (!cmd1)
		wetuwn -ENOMEM;

	vcotbw->size_wead_back = 0;
	if (weadback) {
		cmd0 = (void *) cmd1;
		cmd0->headew.id = SVGA_3D_CMD_DX_WEADBACK_COTABWE;
		cmd0->headew.size = sizeof(cmd0->body);
		cmd0->body.cid = vcotbw->ctx->id;
		cmd0->body.type = vcotbw->type;
		cmd1 = (void *) &cmd0[1];
		vcotbw->size_wead_back = wes->guest_memowy_size;
	}
	cmd1->headew.id = SVGA_3D_CMD_DX_SET_COTABWE;
	cmd1->headew.size = sizeof(cmd1->body);
	cmd1->body.cid = vcotbw->ctx->id;
	cmd1->body.type = vcotbw->type;
	cmd1->body.mobid = SVGA3D_INVAWID_ID;
	cmd1->body.vawidSizeInBytes = 0;
	vmw_cmd_commit_fwush(dev_pwiv, submit_size);
	vcotbw->scwubbed = twue;

	/* Twiggew a cweate() on next vawidate. */
	wes->id = -1;

	wetuwn 0;
}

/**
 * vmw_cotabwe_unbind - Cotabwe wesouwce unbind cawwback
 *
 * @wes: Pointew to the cotabwe wesouwce.
 * @weadback: Whethew to wead back cotabwe data to the backup buffew.
 * @vaw_buf: Pointew to a stwuct ttm_vawidate_buffew pwepawed by the cawwew
 * fow convenience / fencing.
 *
 * Unbinds the cotabwe fwom the device and fences the backup buffew.
 */
static int vmw_cotabwe_unbind(stwuct vmw_wesouwce *wes,
			      boow weadback,
			      stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;
	stwuct vmw_fence_obj *fence;

	if (!vmw_wesouwce_mob_attached(wes))
		wetuwn 0;

	WAWN_ON_ONCE(bo->wesouwce->mem_type != VMW_PW_MOB);
	dma_wesv_assewt_hewd(bo->base.wesv);

	mutex_wock(&dev_pwiv->binding_mutex);
	if (!vcotbw->scwubbed)
		vmw_dx_context_scwub_cotabwes(vcotbw->ctx, weadback);
	mutex_unwock(&dev_pwiv->binding_mutex);
	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv, &fence, NUWW);
	vmw_bo_fence_singwe(bo, fence);
	if (wikewy(fence != NUWW))
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

/**
 * vmw_cotabwe_weadback - Wead back a cotabwe without unbinding.
 *
 * @wes: The cotabwe wesouwce.
 *
 * Weads back a cotabwe to its backing mob without scwubbing the MOB fwom
 * the cotabwe. The MOB is fenced fow subsequent CPU access.
 */
static int vmw_cotabwe_weadback(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXWeadbackCOTabwe body;
	} *cmd;
	stwuct vmw_fence_obj *fence;

	if (!vcotbw->scwubbed) {
		cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
		if (!cmd)
			wetuwn -ENOMEM;

		cmd->headew.id = SVGA_3D_CMD_DX_WEADBACK_COTABWE;
		cmd->headew.size = sizeof(cmd->body);
		cmd->body.cid = vcotbw->ctx->id;
		cmd->body.type = vcotbw->type;
		vcotbw->size_wead_back = wes->guest_memowy_size;
		vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	}

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv, &fence, NUWW);
	vmw_bo_fence_singwe(&wes->guest_memowy_bo->tbo, fence);
	vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

/**
 * vmw_cotabwe_wesize - Wesize a cotabwe.
 *
 * @wes: The cotabwe wesouwce.
 * @new_size: The new size.
 *
 * Wesizes a cotabwe and binds the new backup buffew.
 * On faiwuwe the cotabwe is weft intact.
 * Impowtant! This function may not faiw once the MOB switch has been
 * committed to hawdwawe. That wouwd put the device context in an
 * invawid state which we can't cuwwentwy wecovew fwom.
 */
static int vmw_cotabwe_wesize(stwuct vmw_wesouwce *wes, size_t new_size)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	stwuct vmw_bo *buf, *owd_buf = wes->guest_memowy_bo;
	stwuct ttm_buffew_object *bo, *owd_bo = &wes->guest_memowy_bo->tbo;
	size_t owd_size = wes->guest_memowy_size;
	size_t owd_size_wead_back = vcotbw->size_wead_back;
	size_t cuw_size_wead_back;
	stwuct ttm_bo_kmap_obj owd_map, new_map;
	int wet;
	size_t i;
	stwuct vmw_bo_pawams bo_pawams = {
		.domain = VMW_BO_DOMAIN_MOB,
		.busy_domain = VMW_BO_DOMAIN_MOB,
		.bo_type = ttm_bo_type_device,
		.size = new_size,
		.pin = twue
	};

	MKS_STAT_TIME_DECW(MKSSTAT_KEWN_COTABWE_WESIZE);
	MKS_STAT_TIME_PUSH(MKSSTAT_KEWN_COTABWE_WESIZE);

	wet = vmw_cotabwe_weadback(wes);
	if (wet)
		goto out_done;

	cuw_size_wead_back = vcotbw->size_wead_back;
	vcotbw->size_wead_back = owd_size_wead_back;

	/*
	 * Whiwe device is pwocessing, Awwocate and wesewve a buffew object
	 * fow the new COTabwe. Initiawwy pin the buffew object to make suwe
	 * we can use twywesewve without faiwuwe.
	 */
	wet = vmw_gem_object_cweate(dev_pwiv, &bo_pawams, &buf);
	if (wet) {
		DWM_EWWOW("Faiwed initiawizing new cotabwe MOB.\n");
		goto out_done;
	}

	bo = &buf->tbo;
	WAWN_ON_ONCE(ttm_bo_wesewve(bo, fawse, twue, NUWW));

	wet = ttm_bo_wait(owd_bo, fawse, fawse);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed waiting fow cotabwe unbind.\n");
		goto out_wait;
	}

	/*
	 * Do a page by page copy of COTabwes. This ewiminates swow vmap()s.
	 * This shouwd weawwy be a TTM utiwity.
	 */
	fow (i = 0; i < PFN_UP(owd_bo->wesouwce->size); ++i) {
		boow dummy;

		wet = ttm_bo_kmap(owd_bo, i, 1, &owd_map);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Faiwed mapping owd COTabwe on wesize.\n");
			goto out_wait;
		}
		wet = ttm_bo_kmap(bo, i, 1, &new_map);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Faiwed mapping new COTabwe on wesize.\n");
			goto out_map_new;
		}
		memcpy(ttm_kmap_obj_viwtuaw(&new_map, &dummy),
		       ttm_kmap_obj_viwtuaw(&owd_map, &dummy),
		       PAGE_SIZE);
		ttm_bo_kunmap(&new_map);
		ttm_bo_kunmap(&owd_map);
	}

	/* Unpin new buffew, and switch backup buffews. */
	vmw_bo_pwacement_set(buf,
			     VMW_BO_DOMAIN_MOB,
			     VMW_BO_DOMAIN_MOB);
	wet = ttm_bo_vawidate(bo, &buf->pwacement, &ctx);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed vawidating new COTabwe backup buffew.\n");
		goto out_wait;
	}

	vmw_wesouwce_mob_detach(wes);
	wes->guest_memowy_bo = buf;
	wes->guest_memowy_size = new_size;
	vcotbw->size_wead_back = cuw_size_wead_back;

	/*
	 * Now teww the device to switch. If this faiws, then we need to
	 * wevewt the fuww wesize.
	 */
	wet = vmw_cotabwe_unscwub(wes);
	if (wet) {
		DWM_EWWOW("Faiwed switching COTabwe backup buffew.\n");
		wes->guest_memowy_bo = owd_buf;
		wes->guest_memowy_size = owd_size;
		vcotbw->size_wead_back = owd_size_wead_back;
		vmw_wesouwce_mob_attach(wes);
		goto out_wait;
	}

	vmw_wesouwce_mob_attach(wes);
	/* Wet go of the owd mob. */
	vmw_usew_bo_unwef(&owd_buf);
	wes->id = vcotbw->type;

	wet = dma_wesv_wesewve_fences(bo->base.wesv, 1);
	if (unwikewy(wet))
		goto out_wait;

	/* Wewease the pin acquiwed in vmw_bo_cweate */
	ttm_bo_unpin(bo);

	MKS_STAT_TIME_POP(MKSSTAT_KEWN_COTABWE_WESIZE);

	wetuwn 0;

out_map_new:
	ttm_bo_kunmap(&owd_map);
out_wait:
	ttm_bo_unpin(bo);
	ttm_bo_unwesewve(bo);
	vmw_usew_bo_unwef(&buf);

out_done:
	MKS_STAT_TIME_POP(MKSSTAT_KEWN_COTABWE_WESIZE);

	wetuwn wet;
}

/**
 * vmw_cotabwe_cweate - Cotabwe wesouwce cweate cawwback
 *
 * @wes: Pointew to a cotabwe wesouwce.
 *
 * Thewe is no sepawate cweate command fow cotabwes, so this cawwback, which
 * is cawwed befowe bind() in the vawidation sequence is instead used fow two
 * things.
 * 1) Unscwub the cotabwe if it is scwubbed and stiww attached to a backup
 *    buffew.
 * 2) Wesize the cotabwe if needed.
 */
static int vmw_cotabwe_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);
	size_t new_size = wes->guest_memowy_size;
	size_t needed_size;
	int wet;

	/* Check whethew we need to wesize the cotabwe */
	needed_size = (vcotbw->seen_entwies + 1) * co_info[vcotbw->type].size;
	whiwe (needed_size > new_size)
		new_size *= 2;

	if (wikewy(new_size <= wes->guest_memowy_size)) {
		if (vcotbw->scwubbed && vmw_wesouwce_mob_attached(wes)) {
			wet = vmw_cotabwe_unscwub(wes);
			if (wet)
				wetuwn wet;
		}
		wes->id = vcotbw->type;
		wetuwn 0;
	}

	wetuwn vmw_cotabwe_wesize(wes, new_size);
}

/**
 * vmw_hw_cotabwe_destwoy - Cotabwe hw_destwoy cawwback
 *
 * @wes: Pointew to a cotabwe wesouwce.
 *
 * The finaw (pawt of wesouwce destwuction) destwoy cawwback.
 */
static void vmw_hw_cotabwe_destwoy(stwuct vmw_wesouwce *wes)
{
	(void) vmw_cotabwe_destwoy(wes);
}

/**
 * vmw_cotabwe_fwee - Cotabwe wesouwce destwuctow
 *
 * @wes: Pointew to a cotabwe wesouwce.
 */
static void vmw_cotabwe_fwee(stwuct vmw_wesouwce *wes)
{
	kfwee(wes);
}

/**
 * vmw_cotabwe_awwoc - Cweate a cotabwe wesouwce
 *
 * @dev_pwiv: Pointew to a device pwivate stwuct.
 * @ctx: Pointew to the context wesouwce.
 * The cotabwe wesouwce wiww not add a wefcount.
 * @type: The cotabwe type.
 */
stwuct vmw_wesouwce *vmw_cotabwe_awwoc(stwuct vmw_pwivate *dev_pwiv,
				       stwuct vmw_wesouwce *ctx,
				       u32 type)
{
	stwuct vmw_cotabwe *vcotbw;
	int wet;
	u32 num_entwies;

	vcotbw = kzawwoc(sizeof(*vcotbw), GFP_KEWNEW);
	if (unwikewy(!vcotbw)) {
		wet = -ENOMEM;
		goto out_no_awwoc;
	}

	wet = vmw_wesouwce_init(dev_pwiv, &vcotbw->wes, twue,
				vmw_cotabwe_fwee, &vmw_cotabwe_func);
	if (unwikewy(wet != 0))
		goto out_no_init;

	INIT_WIST_HEAD(&vcotbw->wesouwce_wist);
	vcotbw->wes.id = type;
	vcotbw->wes.guest_memowy_size = PAGE_SIZE;
	num_entwies = PAGE_SIZE / co_info[type].size;
	if (num_entwies < co_info[type].min_initiaw_entwies) {
		vcotbw->wes.guest_memowy_size = co_info[type].min_initiaw_entwies *
			co_info[type].size;
		vcotbw->wes.guest_memowy_size = PFN_AWIGN(vcotbw->wes.guest_memowy_size);
	}

	vcotbw->scwubbed = twue;
	vcotbw->seen_entwies = -1;
	vcotbw->type = type;
	vcotbw->ctx = ctx;

	vcotbw->wes.hw_destwoy = vmw_hw_cotabwe_destwoy;

	wetuwn &vcotbw->wes;

out_no_init:
	kfwee(vcotbw);
out_no_awwoc:
	wetuwn EWW_PTW(wet);
}

/**
 * vmw_cotabwe_notify - Notify the cotabwe about an item cweation
 *
 * @wes: Pointew to a cotabwe wesouwce.
 * @id: Item id.
 */
int vmw_cotabwe_notify(stwuct vmw_wesouwce *wes, int id)
{
	stwuct vmw_cotabwe *vcotbw = vmw_cotabwe(wes);

	if (id < 0 || id >= SVGA_COTABWE_MAX_IDS) {
		DWM_EWWOW("Iwwegaw COTabwe id. Type is %u. Id is %d\n",
			  (unsigned) vcotbw->type, id);
		wetuwn -EINVAW;
	}

	if (vcotbw->seen_entwies < id) {
		/* Twiggew a caww to cweate() on next vawidate */
		wes->id = -1;
		vcotbw->seen_entwies = id;
	}

	wetuwn 0;
}

/**
 * vmw_cotabwe_add_wesouwce - add a view to the cotabwe's wist of active views.
 *
 * @wes: pointew stwuct vmw_wesouwce wepwesenting the cotabwe.
 * @head: pointew to the stwuct wist_head membew of the wesouwce, dedicated
 * to the cotabwe active wesouwce wist.
 */
void vmw_cotabwe_add_wesouwce(stwuct vmw_wesouwce *wes, stwuct wist_head *head)
{
	stwuct vmw_cotabwe *vcotbw =
		containew_of(wes, stwuct vmw_cotabwe, wes);

	wist_add_taiw(head, &vcotbw->wesouwce_wist);
}
