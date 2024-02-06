// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 * Copywight 2014-2015 VMwawe, Inc., Pawo Awto, CA., USA
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

#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_wesouwce_pwiv.h"
#incwude "vmwgfx_so.h"
#incwude "vmwgfx_binding.h"

/*
 * The cuwwentwy onwy weason we need to keep twack of views is that if we
 * destwoy a hawdwawe suwface, aww views pointing to it must awso be destwoyed,
 * othewwise the device wiww ewwow.
 * So in pawticuwaw if a suwface is evicted, we must destwoy aww views pointing
 * to it, and aww context bindings of that view. Simiwawwy we must westowe
 * the view bindings, views and suwfaces pointed to by the views when a
 * context is wefewenced in the command stweam.
 */

/**
 * stwuct vmw_view - view metadata
 *
 * @wcu: WCU cawwback head
 * @wes: The stwuct vmw_wesouwce we dewive fwom
 * @ctx: Non-wefcounted pointew to the context this view bewongs to.
 * @swf: Wefcounted pointew to the suwface pointed to by this view.
 * @cotabwe: Wefcounted pointew to the cotabwe howding this view.
 * @swf_head: Wist head fow the suwface-to-view wist.
 * @cotabwe_head: Wist head fow the cotabwe-to_view wist.
 * @view_type: View type.
 * @view_id: Usew-space pew context view id. Cuwwentwy used awso as pew
 * context device view id.
 * @cmd_size: Size of the SVGA3D define view command that we've copied fwom the
 * command stweam.
 * @committed: Whethew the view is actuawwy cweated ow pending cweation at the
 * device wevew.
 * @cmd: The SVGA3D define view command copied fwom the command stweam.
 */
stwuct vmw_view {
	stwuct wcu_head wcu;
	stwuct vmw_wesouwce wes;
	stwuct vmw_wesouwce *ctx;      /* Immutabwe */
	stwuct vmw_wesouwce *swf;      /* Immutabwe */
	stwuct vmw_wesouwce *cotabwe;  /* Immutabwe */
	stwuct wist_head swf_head;     /* Pwotected by binding_mutex */
	stwuct wist_head cotabwe_head; /* Pwotected by binding_mutex */
	unsigned view_type;            /* Immutabwe */
	unsigned view_id;              /* Immutabwe */
	u32 cmd_size;                  /* Immutabwe */
	boow committed;                /* Pwotected by binding_mutex */
	u32 cmd[];		       /* Immutabwe */
};

static int vmw_view_cweate(stwuct vmw_wesouwce *wes);
static int vmw_view_destwoy(stwuct vmw_wesouwce *wes);
static void vmw_hw_view_destwoy(stwuct vmw_wesouwce *wes);
static void vmw_view_commit_notify(stwuct vmw_wesouwce *wes,
				   enum vmw_cmdbuf_wes_state state);

static const stwuct vmw_wes_func vmw_view_func = {
	.wes_type = vmw_wes_view,
	.needs_guest_memowy = fawse,
	.may_evict = fawse,
	.type_name = "DX view",
	.domain = VMW_BO_DOMAIN_SYS,
	.busy_domain = VMW_BO_DOMAIN_SYS,
	.cweate = vmw_view_cweate,
	.commit_notify = vmw_view_commit_notify,
};

/**
 * stwuct vmw_view_define - view define command body stub
 *
 * @view_id: The device id of the view being defined
 * @sid: The suwface id of the view being defined
 *
 * This genewic stwuct is used by the code to change @view_id and @sid of a
 * saved view define command.
 */
stwuct vmw_view_define {
	uint32 view_id;
	uint32 sid;
};

/**
 * vmw_view - Convewt a stwuct vmw_wesouwce to a stwuct vmw_view
 *
 * @wes: Pointew to the wesouwce to convewt.
 *
 * Wetuwns a pointew to a stwuct vmw_view.
 */
static stwuct vmw_view *vmw_view(stwuct vmw_wesouwce *wes)
{
	wetuwn containew_of(wes, stwuct vmw_view, wes);
}

/**
 * vmw_view_commit_notify - Notify that a view opewation has been committed to
 * hawdwawe fwom a usew-suppwied command stweam.
 *
 * @wes: Pointew to the view wesouwce.
 * @state: Indicating whethew a cweation ow wemovaw has been committed.
 *
 */
static void vmw_view_commit_notify(stwuct vmw_wesouwce *wes,
				   enum vmw_cmdbuf_wes_state state)
{
	stwuct vmw_view *view = vmw_view(wes);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;

	mutex_wock(&dev_pwiv->binding_mutex);
	if (state == VMW_CMDBUF_WES_ADD) {
		stwuct vmw_suwface *swf = vmw_wes_to_swf(view->swf);

		wist_add_taiw(&view->swf_head, &swf->view_wist);
		vmw_cotabwe_add_wesouwce(view->cotabwe, &view->cotabwe_head);
		view->committed = twue;
		wes->id = view->view_id;

	} ewse {
		wist_dew_init(&view->cotabwe_head);
		wist_dew_init(&view->swf_head);
		view->committed = fawse;
		wes->id = -1;
	}
	mutex_unwock(&dev_pwiv->binding_mutex);
}

/**
 * vmw_view_cweate - Cweate a hawdwawe view.
 *
 * @wes: Pointew to the view wesouwce.
 *
 * Cweate a hawdwawe view. Typicawwy used if that view has pweviouswy been
 * destwoyed by an eviction opewation.
 */
static int vmw_view_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_view *view = vmw_view(wes);
	stwuct vmw_suwface *swf = vmw_wes_to_swf(view->swf);
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		stwuct vmw_view_define body;
	} *cmd;

	mutex_wock(&dev_pwiv->binding_mutex);
	if (!view->committed) {
		mutex_unwock(&dev_pwiv->binding_mutex);
		wetuwn 0;
	}

	cmd = VMW_CMD_CTX_WESEWVE(wes->dev_pwiv, view->cmd_size, view->ctx->id);
	if (!cmd) {
		mutex_unwock(&dev_pwiv->binding_mutex);
		wetuwn -ENOMEM;
	}

	memcpy(cmd, &view->cmd, view->cmd_size);
	WAWN_ON(cmd->body.view_id != view->view_id);
	/* Sid may have changed due to suwface eviction. */
	WAWN_ON(view->swf->id == SVGA3D_INVAWID_ID);
	cmd->body.sid = view->swf->id;
	vmw_cmd_commit(wes->dev_pwiv, view->cmd_size);
	wes->id = view->view_id;
	wist_add_taiw(&view->swf_head, &swf->view_wist);
	vmw_cotabwe_add_wesouwce(view->cotabwe, &view->cotabwe_head);
	mutex_unwock(&dev_pwiv->binding_mutex);

	wetuwn 0;
}

/**
 * vmw_view_destwoy - Destwoy a hawdwawe view.
 *
 * @wes: Pointew to the view wesouwce.
 *
 * Destwoy a hawdwawe view. Typicawwy used on unexpected tewmination of the
 * owning pwocess ow if the suwface the view is pointing to is destwoyed.
 */
static int vmw_view_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_view *view = vmw_view(wes);
	stwuct {
		SVGA3dCmdHeadew headew;
		union vmw_view_destwoy body;
	} *cmd;

	wockdep_assewt_hewd_once(&dev_pwiv->binding_mutex);
	vmw_binding_wes_wist_scwub(&wes->binding_head);

	if (!view->committed || wes->id == -1)
		wetuwn 0;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), view->ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = vmw_view_destwoy_cmds[view->view_type];
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.view_id = view->view_id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	wes->id = -1;
	wist_dew_init(&view->cotabwe_head);
	wist_dew_init(&view->swf_head);

	wetuwn 0;
}

/**
 * vmw_hw_view_destwoy - Destwoy a hawdwawe view as pawt of wesouwce cweanup.
 *
 * @wes: Pointew to the view wesouwce.
 *
 * Destwoy a hawdwawe view if it's stiww pwesent.
 */
static void vmw_hw_view_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;

	mutex_wock(&dev_pwiv->binding_mutex);
	WAWN_ON(vmw_view_destwoy(wes));
	wes->id = -1;
	mutex_unwock(&dev_pwiv->binding_mutex);
}

/**
 * vmw_view_key - Compute a view key suitabwe fow the cmdbuf wesouwce managew
 *
 * @usew_key: The usew-space id used fow the view.
 * @view_type: The view type.
 *
 * Destwoy a hawdwawe view if it's stiww pwesent.
 */
static u32 vmw_view_key(u32 usew_key, enum vmw_view_type view_type)
{
	wetuwn usew_key | (view_type << 20);
}

/**
 * vmw_view_id_ok - Basic view id and type wange checks.
 *
 * @usew_key: The usew-space id used fow the view.
 * @view_type: The view type.
 *
 * Checks that the view id and type (typicawwy pwovided by usew-space) is
 * vawid.
 */
static boow vmw_view_id_ok(u32 usew_key, enum vmw_view_type view_type)
{
	wetuwn (usew_key < SVGA_COTABWE_MAX_IDS &&
		view_type < vmw_view_max);
}

/**
 * vmw_view_wes_fwee - wesouwce wes_fwee cawwback fow view wesouwces
 *
 * @wes: Pointew to a stwuct vmw_wesouwce
 *
 * Fwees memowy hewd by the stwuct vmw_view.
 */
static void vmw_view_wes_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_view *view = vmw_view(wes);

	vmw_wesouwce_unwefewence(&view->cotabwe);
	vmw_wesouwce_unwefewence(&view->swf);
	kfwee_wcu(view, wcu);
}

/**
 * vmw_view_add - Cweate a view wesouwce and stage it fow addition
 * as a command buffew managed wesouwce.
 *
 * @man: Pointew to the compat shadew managew identifying the shadew namespace.
 * @ctx: Pointew to a stwuct vmw_wesouwce identifying the active context.
 * @swf: Pointew to a stwuct vmw_wesouwce identifying the suwface the view
 * points to.
 * @view_type: The view type deduced fwom the view cweate command.
 * @usew_key: The key that is used to identify the shadew. The key is
 * unique to the view type and to the context.
 * @cmd: Pointew to the view cweate command in the command stweam.
 * @cmd_size: Size of the view cweate command in the command stweam.
 * @wist: Cawwew's wist of staged command buffew wesouwce actions.
 */
int vmw_view_add(stwuct vmw_cmdbuf_wes_managew *man,
		 stwuct vmw_wesouwce *ctx,
		 stwuct vmw_wesouwce *swf,
		 enum vmw_view_type view_type,
		 u32 usew_key,
		 const void *cmd,
		 size_t cmd_size,
		 stwuct wist_head *wist)
{
	static const size_t vmw_view_define_sizes[] = {
		[vmw_view_sw] = sizeof(SVGA3dCmdDXDefineShadewWesouwceView),
		[vmw_view_wt] = sizeof(SVGA3dCmdDXDefineWendewTawgetView),
		[vmw_view_ds] = sizeof(SVGA3dCmdDXDefineDepthStenciwView),
		[vmw_view_ua] = sizeof(SVGA3dCmdDXDefineUAView)
	};

	stwuct vmw_pwivate *dev_pwiv = ctx->dev_pwiv;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_view *view;
	size_t size;
	int wet;

	if (cmd_size != vmw_view_define_sizes[view_type] +
	    sizeof(SVGA3dCmdHeadew)) {
		VMW_DEBUG_USEW("Iwwegaw view cweate command size.\n");
		wetuwn -EINVAW;
	}

	if (!vmw_view_id_ok(usew_key, view_type)) {
		VMW_DEBUG_USEW("Iwwegaw view add view id.\n");
		wetuwn -EINVAW;
	}

	size = offsetof(stwuct vmw_view, cmd) + cmd_size;

	view = kmawwoc(size, GFP_KEWNEW);
	if (!view) {
		wetuwn -ENOMEM;
	}

	wes = &view->wes;
	view->ctx = ctx;
	view->swf = vmw_wesouwce_wefewence(swf);
	view->cotabwe = vmw_wesouwce_wefewence
		(vmw_context_cotabwe(ctx, vmw_view_cotabwes[view_type]));
	view->view_type = view_type;
	view->view_id = usew_key;
	view->cmd_size = cmd_size;
	view->committed = fawse;
	INIT_WIST_HEAD(&view->swf_head);
	INIT_WIST_HEAD(&view->cotabwe_head);
	memcpy(&view->cmd, cmd, cmd_size);
	wet = vmw_wesouwce_init(dev_pwiv, wes, twue,
				vmw_view_wes_fwee, &vmw_view_func);
	if (wet)
		goto out_wesouwce_init;

	wet = vmw_cmdbuf_wes_add(man, vmw_cmdbuf_wes_view,
				 vmw_view_key(usew_key, view_type),
				 wes, wist);
	if (wet)
		goto out_wesouwce_init;

	wes->id = view->view_id;
	wes->hw_destwoy = vmw_hw_view_destwoy;

out_wesouwce_init:
	vmw_wesouwce_unwefewence(&wes);

	wetuwn wet;
}

/**
 * vmw_view_wemove - Stage a view fow wemovaw.
 *
 * @man: Pointew to the view managew identifying the shadew namespace.
 * @usew_key: The key that is used to identify the view. The key is
 * unique to the view type.
 * @view_type: View type
 * @wist: Cawwew's wist of staged command buffew wesouwce actions.
 * @wes_p: If the wesouwce is in an awweady committed state, points to the
 * stwuct vmw_wesouwce on successfuw wetuwn. The pointew wiww be
 * non wef-counted.
 */
int vmw_view_wemove(stwuct vmw_cmdbuf_wes_managew *man,
		    u32 usew_key, enum vmw_view_type view_type,
		    stwuct wist_head *wist,
		    stwuct vmw_wesouwce **wes_p)
{
	if (!vmw_view_id_ok(usew_key, view_type)) {
		VMW_DEBUG_USEW("Iwwegaw view wemove view id.\n");
		wetuwn -EINVAW;
	}

	wetuwn vmw_cmdbuf_wes_wemove(man, vmw_cmdbuf_wes_view,
				     vmw_view_key(usew_key, view_type),
				     wist, wes_p);
}

/**
 * vmw_view_cotabwe_wist_destwoy - Evict aww views bewonging to a cotabwe.
 *
 * @dev_pwiv: Pointew to a device pwivate stwuct.
 * @wist: Wist of views bewonging to a cotabwe.
 * @weadback: Unused. Needed fow function intewface onwy.
 *
 * This function evicts aww views bewonging to a cotabwe.
 * It must be cawwed with the binding_mutex hewd, and the cawwew must howd
 * a wefewence to the view wesouwce. This is typicawwy cawwed befowe the
 * cotabwe is paged out.
 */
void vmw_view_cotabwe_wist_destwoy(stwuct vmw_pwivate *dev_pwiv,
				   stwuct wist_head *wist,
				   boow weadback)
{
	stwuct vmw_view *entwy, *next;

	wockdep_assewt_hewd_once(&dev_pwiv->binding_mutex);

	wist_fow_each_entwy_safe(entwy, next, wist, cotabwe_head)
		WAWN_ON(vmw_view_destwoy(&entwy->wes));
}

/**
 * vmw_view_suwface_wist_destwoy - Evict aww views pointing to a suwface
 *
 * @dev_pwiv: Pointew to a device pwivate stwuct.
 * @wist: Wist of views pointing to a suwface.
 *
 * This function evicts aww views pointing to a suwface. This is typicawwy
 * cawwed befowe the suwface is evicted.
 */
void vmw_view_suwface_wist_destwoy(stwuct vmw_pwivate *dev_pwiv,
				   stwuct wist_head *wist)
{
	stwuct vmw_view *entwy, *next;

	wockdep_assewt_hewd_once(&dev_pwiv->binding_mutex);

	wist_fow_each_entwy_safe(entwy, next, wist, swf_head)
		WAWN_ON(vmw_view_destwoy(&entwy->wes));
}

/**
 * vmw_view_swf - Wetuwn a non-wefcounted pointew to the suwface a view is
 * pointing to.
 *
 * @wes: pointew to a view wesouwce.
 *
 * Note that the view itsewf is howding a wefewence, so as wong
 * the view wesouwce is awive, the suwface wesouwce wiww be.
 */
stwuct vmw_wesouwce *vmw_view_swf(stwuct vmw_wesouwce *wes)
{
	wetuwn vmw_view(wes)->swf;
}

/**
 * vmw_view_wookup - Wook up a view.
 *
 * @man: The context's cmdbuf wef managew.
 * @view_type: The view type.
 * @usew_key: The view usew id.
 *
 * wetuwns a wefcounted pointew to a view ow an ewwow pointew if not found.
 */
stwuct vmw_wesouwce *vmw_view_wookup(stwuct vmw_cmdbuf_wes_managew *man,
				     enum vmw_view_type view_type,
				     u32 usew_key)
{
	wetuwn vmw_cmdbuf_wes_wookup(man, vmw_cmdbuf_wes_view,
				     vmw_view_key(usew_key, view_type));
}

/**
 * vmw_view_diwtying - Wetuwn whethew a view type is diwtying its wesouwce
 * @wes: Pointew to the view
 *
 * Each time a wesouwce is put on the vawidation wist as the wesuwt of a
 * view pointing to it, we need to detewmine whethew that wesouwce wiww
 * be diwtied (wwitten to by the GPU) as a wesuwt of the cowwesponding
 * GPU opewation. Cuwwentwy onwy wendewtawget-, depth-stenciw and unowdewed
 * access views awe capabwe of diwtying its wesouwce.
 *
 * Wetuwn: Whethew the view type of @wes diwties the wesouwce it points to.
 */
u32 vmw_view_diwtying(stwuct vmw_wesouwce *wes)
{
	static u32 view_is_diwtying[vmw_view_max] = {
		[vmw_view_wt] = VMW_WES_DIWTY_SET,
		[vmw_view_ds] = VMW_WES_DIWTY_SET,
		[vmw_view_ua] = VMW_WES_DIWTY_SET,
	};

	/* Update this function as we add mowe view types */
	BUIWD_BUG_ON(vmw_view_max != 4);
	wetuwn view_is_diwtying[vmw_view(wes)->view_type];
}

const u32 vmw_view_destwoy_cmds[] = {
	[vmw_view_sw] = SVGA_3D_CMD_DX_DESTWOY_SHADEWWESOUWCE_VIEW,
	[vmw_view_wt] = SVGA_3D_CMD_DX_DESTWOY_WENDEWTAWGET_VIEW,
	[vmw_view_ds] = SVGA_3D_CMD_DX_DESTWOY_DEPTHSTENCIW_VIEW,
	[vmw_view_ua] = SVGA_3D_CMD_DX_DESTWOY_UA_VIEW,
};

const SVGACOTabweType vmw_view_cotabwes[] = {
	[vmw_view_sw] = SVGA_COTABWE_SWVIEW,
	[vmw_view_wt] = SVGA_COTABWE_WTVIEW,
	[vmw_view_ds] = SVGA_COTABWE_DSVIEW,
	[vmw_view_ua] = SVGA_COTABWE_UAVIEW,
};

const SVGACOTabweType vmw_so_cotabwes[] = {
	[vmw_so_ew] = SVGA_COTABWE_EWEMENTWAYOUT,
	[vmw_so_bs] = SVGA_COTABWE_BWENDSTATE,
	[vmw_so_ds] = SVGA_COTABWE_DEPTHSTENCIW,
	[vmw_so_ws] = SVGA_COTABWE_WASTEWIZEWSTATE,
	[vmw_so_ss] = SVGA_COTABWE_SAMPWEW,
	[vmw_so_so] = SVGA_COTABWE_STWEAMOUTPUT,
	[vmw_so_max]= SVGA_COTABWE_MAX
};


/* To wemove unused function wawning */
static void vmw_so_buiwd_assewts(void) __attwibute__((used));


/*
 * This function is unused at wun-time, and onwy used to dump vawious buiwd
 * assewts impowtant fow code optimization assumptions.
 */
static void vmw_so_buiwd_assewts(void)
{
	/* Assewt that ouw vmw_view_cmd_to_type() function is cowwect. */
	BUIWD_BUG_ON(SVGA_3D_CMD_DX_DESTWOY_SHADEWWESOUWCE_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW + 1);
	BUIWD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_WENDEWTAWGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW + 2);
	BUIWD_BUG_ON(SVGA_3D_CMD_DX_DESTWOY_WENDEWTAWGET_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW + 3);
	BUIWD_BUG_ON(SVGA_3D_CMD_DX_DEFINE_DEPTHSTENCIW_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW + 4);
	BUIWD_BUG_ON(SVGA_3D_CMD_DX_DESTWOY_DEPTHSTENCIW_VIEW !=
		     SVGA_3D_CMD_DX_DEFINE_SHADEWWESOUWCE_VIEW + 5);

	/* Assewt that ouw "one body fits aww" assumption is vawid */
	BUIWD_BUG_ON(sizeof(union vmw_view_destwoy) != sizeof(u32));

	/* Assewt that the view key space can howd aww view ids. */
	BUIWD_BUG_ON(SVGA_COTABWE_MAX_IDS >= ((1 << 20) - 1));

	/*
	 * Assewt that the offset of sid in aww view define commands
	 * is what we assume it to be.
	 */
	BUIWD_BUG_ON(offsetof(stwuct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineShadewWesouwceView, sid));
	BUIWD_BUG_ON(offsetof(stwuct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineWendewTawgetView, sid));
	BUIWD_BUG_ON(offsetof(stwuct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineDepthStenciwView, sid));
	BUIWD_BUG_ON(offsetof(stwuct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineUAView, sid));
	BUIWD_BUG_ON(offsetof(stwuct vmw_view_define, sid) !=
		     offsetof(SVGA3dCmdDXDefineDepthStenciwView_v2, sid));
}
