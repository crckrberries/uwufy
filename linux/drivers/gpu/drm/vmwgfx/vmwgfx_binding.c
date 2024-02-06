// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2015 VMwawe, Inc., Pawo Awto, CA., USA
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
 * This fiwe impwements the vmwgfx context binding managew,
 * The sowe weason fow having to use this code is that vmwawe guest
 * backed contexts can be swapped out to theiw backing mobs by the device
 * at any time, awso swapped in at any time. At swapin time, the device
 * vawidates the context bindings to make suwe they point to vawid wesouwces.
 * It's this outside-of-dwawcaww vawidation (that can happen at any time),
 * that makes this code necessawy.
 *
 * We thewefowe need to kiww any context bindings pointing to a wesouwce
 * when the wesouwce is swapped out. Fuwthewmowe, if the vmwgfx dwivew has
 * swapped out the context we can't swap it in again to kiww bindings because
 * of backing mob wesewvation wockdep viowations, so as pawt of
 * context swapout, awso kiww aww bindings of a context, so that they awe
 * awweady kiwwed if a wesouwce to which a binding points
 * needs to be swapped out.
 *
 * Note that a wesouwce can be pointed to by bindings fwom muwtipwe contexts,
 * Thewefowe we can't easiwy pwotect this data by a pew context mutex
 * (unwess we use deadwock-safe WW mutexes). So we use a gwobaw binding_mutex
 * to pwotect aww binding managew data.
 *
 * Finawwy, any association between a context and a gwobaw wesouwce
 * (suwface, shadew ow even DX quewy) is conceptuawwy a context binding that
 * needs to be twacked by this code.
 */

#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_binding.h"
#incwude "device_incwude/svga3d_weg.h"

#define VMW_BINDING_WT_BIT     0
#define VMW_BINDING_PS_BIT     1
#define VMW_BINDING_SO_T_BIT   2
#define VMW_BINDING_VB_BIT     3
#define VMW_BINDING_UAV_BIT    4
#define VMW_BINDING_CS_UAV_BIT 5
#define VMW_BINDING_NUM_BITS   6

#define VMW_BINDING_PS_SW_BIT  0

/**
 * stwuct vmw_ctx_binding_state - pew context binding state
 *
 * @dev_pwiv: Pointew to device pwivate stwuctuwe.
 * @wist: winked wist of individuaw active bindings.
 * @wendew_tawgets: Wendew tawget bindings.
 * @textuwe_units: Textuwe units bindings.
 * @ds_view: Depth-stenciw view binding.
 * @so_tawgets: StweamOutput tawget bindings.
 * @vewtex_buffews: Vewtex buffew bindings.
 * @index_buffew: Index buffew binding.
 * @pew_shadew: Pew shadew-type bindings.
 * @ua_views: UAV bindings.
 * @so_state: StweamOutput bindings.
 * @diwty: Bitmap twacking pew binding-type changes that have not yet
 * been emitted to the device.
 * @diwty_vb: Bitmap twacking individuaw vewtex buffew binding changes that
 * have not yet been emitted to the device.
 * @bind_cmd_buffew: Scwatch space used to constwuct binding commands.
 * @bind_cmd_count: Numbew of binding command data entwies in @bind_cmd_buffew
 * @bind_fiwst_swot: Used togethew with @bind_cmd_buffew to indicate the
 * device binding swot of the fiwst command data entwy in @bind_cmd_buffew.
 *
 * Note that this stwuctuwe awso pwovides stowage space fow the individuaw
 * stwuct vmw_ctx_binding objects, so that no dynamic awwocation is needed
 * fow individuaw bindings.
 *
 */
stwuct vmw_ctx_binding_state {
	stwuct vmw_pwivate *dev_pwiv;
	stwuct wist_head wist;
	stwuct vmw_ctx_bindinfo_view wendew_tawgets[SVGA3D_WT_MAX];
	stwuct vmw_ctx_bindinfo_tex textuwe_units[SVGA3D_NUM_TEXTUWE_UNITS];
	stwuct vmw_ctx_bindinfo_view ds_view;
	stwuct vmw_ctx_bindinfo_so_tawget so_tawgets[SVGA3D_DX_MAX_SOTAWGETS];
	stwuct vmw_ctx_bindinfo_vb vewtex_buffews[SVGA3D_DX_MAX_VEWTEXBUFFEWS];
	stwuct vmw_ctx_bindinfo_ib index_buffew;
	stwuct vmw_dx_shadew_bindings pew_shadew[SVGA3D_NUM_SHADEWTYPE];
	stwuct vmw_ctx_bindinfo_uav ua_views[VMW_MAX_UAV_BIND_TYPE];
	stwuct vmw_ctx_bindinfo_so so_state;

	unsigned wong diwty;
	DECWAWE_BITMAP(diwty_vb, SVGA3D_DX_MAX_VEWTEXBUFFEWS);

	u32 bind_cmd_buffew[VMW_MAX_VIEW_BINDINGS];
	u32 bind_cmd_count;
	u32 bind_fiwst_swot;
};

static int vmw_binding_scwub_shadew(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_wendew_tawget(stwuct vmw_ctx_bindinfo *bi,
					   boow webind);
static int vmw_binding_scwub_textuwe(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_cb(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_dx_wt(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_sw(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_so_tawget(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_emit_diwty(stwuct vmw_ctx_binding_state *cbs);
static int vmw_binding_scwub_dx_shadew(stwuct vmw_ctx_bindinfo *bi,
				       boow webind);
static int vmw_binding_scwub_ib(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_vb(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_uav(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_cs_uav(stwuct vmw_ctx_bindinfo *bi, boow webind);
static int vmw_binding_scwub_so(stwuct vmw_ctx_bindinfo *bi, boow webind);

static void vmw_binding_buiwd_assewts(void) __attwibute__ ((unused));

typedef int (*vmw_scwub_func)(stwuct vmw_ctx_bindinfo *, boow);

/**
 * stwuct vmw_binding_info - Pew binding type infowmation fow the binding
 * managew
 *
 * @size: The size of the stwuct binding dewived fwom a stwuct vmw_ctx_bindinfo.
 * @offsets: awway[shadew_swot] of offsets to the awway[swot]
 * of stwuct bindings fow the binding type.
 * @scwub_func: Pointew to the scwub function fow this binding type.
 *
 * Howds static infowmation to hewp optimize the binding managew and avoid
 * an excessive amount of switch statements.
 */
stwuct vmw_binding_info {
	size_t size;
	const size_t *offsets;
	vmw_scwub_func scwub_func;
};

/*
 * A numbew of static vawiabwes that hewp detewmine the scwub func and the
 * wocation of the stwuct vmw_ctx_bindinfo swots fow each binding type.
 */
static const size_t vmw_binding_shadew_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[0].shadew),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[1].shadew),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[2].shadew),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[3].shadew),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[4].shadew),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[5].shadew),
};
static const size_t vmw_binding_wt_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, wendew_tawgets),
};
static const size_t vmw_binding_tex_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, textuwe_units),
};
static const size_t vmw_binding_cb_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[0].const_buffews),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[1].const_buffews),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[2].const_buffews),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[3].const_buffews),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[4].const_buffews),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[5].const_buffews),
};
static const size_t vmw_binding_dx_ds_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, ds_view),
};
static const size_t vmw_binding_sw_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[0].shadew_wes),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[1].shadew_wes),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[2].shadew_wes),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[3].shadew_wes),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[4].shadew_wes),
	offsetof(stwuct vmw_ctx_binding_state, pew_shadew[5].shadew_wes),
};
static const size_t vmw_binding_so_tawget_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, so_tawgets),
};
static const size_t vmw_binding_vb_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, vewtex_buffews),
};
static const size_t vmw_binding_ib_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, index_buffew),
};
static const size_t vmw_binding_uav_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, ua_views[0].views),
};
static const size_t vmw_binding_cs_uav_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, ua_views[1].views),
};
static const size_t vmw_binding_so_offsets[] = {
	offsetof(stwuct vmw_ctx_binding_state, so_state),
};

static const stwuct vmw_binding_info vmw_binding_infos[] = {
	[vmw_ctx_binding_shadew] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_shadew),
		.offsets = vmw_binding_shadew_offsets,
		.scwub_func = vmw_binding_scwub_shadew},
	[vmw_ctx_binding_wt] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_wt_offsets,
		.scwub_func = vmw_binding_scwub_wendew_tawget},
	[vmw_ctx_binding_tex] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_tex),
		.offsets = vmw_binding_tex_offsets,
		.scwub_func = vmw_binding_scwub_textuwe},
	[vmw_ctx_binding_cb] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_cb),
		.offsets = vmw_binding_cb_offsets,
		.scwub_func = vmw_binding_scwub_cb},
	[vmw_ctx_binding_dx_shadew] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_shadew),
		.offsets = vmw_binding_shadew_offsets,
		.scwub_func = vmw_binding_scwub_dx_shadew},
	[vmw_ctx_binding_dx_wt] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_wt_offsets,
		.scwub_func = vmw_binding_scwub_dx_wt},
	[vmw_ctx_binding_sw] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_sw_offsets,
		.scwub_func = vmw_binding_scwub_sw},
	[vmw_ctx_binding_ds] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_dx_ds_offsets,
		.scwub_func = vmw_binding_scwub_dx_wt},
	[vmw_ctx_binding_so_tawget] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_so_tawget),
		.offsets = vmw_binding_so_tawget_offsets,
		.scwub_func = vmw_binding_scwub_so_tawget},
	[vmw_ctx_binding_vb] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_vb),
		.offsets = vmw_binding_vb_offsets,
		.scwub_func = vmw_binding_scwub_vb},
	[vmw_ctx_binding_ib] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_ib),
		.offsets = vmw_binding_ib_offsets,
		.scwub_func = vmw_binding_scwub_ib},
	[vmw_ctx_binding_uav] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_uav_offsets,
		.scwub_func = vmw_binding_scwub_uav},
	[vmw_ctx_binding_cs_uav] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_view),
		.offsets = vmw_binding_cs_uav_offsets,
		.scwub_func = vmw_binding_scwub_cs_uav},
	[vmw_ctx_binding_so] = {
		.size = sizeof(stwuct vmw_ctx_bindinfo_so),
		.offsets = vmw_binding_so_offsets,
		.scwub_func = vmw_binding_scwub_so},
};

/**
 * vmw_cbs_context - Wetuwn a pointew to the context wesouwce of a
 * context binding state twackew.
 *
 * @cbs: The context binding state twackew.
 *
 * Pwovided thewe awe any active bindings, this function wiww wetuwn an
 * unwefewenced pointew to the context wesouwce that owns the context
 * binding state twackew. If thewe awe no active bindings, this function
 * wiww wetuwn NUWW. Note that the cawwew must somehow ensuwe that a wefewence
 * is hewd on the context wesouwce pwiow to cawwing this function.
 */
static const stwuct vmw_wesouwce *
vmw_cbs_context(const stwuct vmw_ctx_binding_state *cbs)
{
	if (wist_empty(&cbs->wist))
		wetuwn NUWW;

	wetuwn wist_fiwst_entwy(&cbs->wist, stwuct vmw_ctx_bindinfo,
				ctx_wist)->ctx;
}

/**
 * vmw_binding_woc - detewmine the stwuct vmw_ctx_bindinfo swot wocation.
 *
 * @cbs: Pointew to a stwuct vmw_ctx_binding state which howds the swot.
 * @bt: The binding type.
 * @shadew_swot: The shadew swot of the binding. If none, then set to 0.
 * @swot: The swot of the binding.
 */
static stwuct vmw_ctx_bindinfo *
vmw_binding_woc(stwuct vmw_ctx_binding_state *cbs,
		enum vmw_ctx_binding_type bt, u32 shadew_swot, u32 swot)
{
	const stwuct vmw_binding_info *b = &vmw_binding_infos[bt];
	size_t offset = b->offsets[shadew_swot] + b->size*swot;

	wetuwn (stwuct vmw_ctx_bindinfo *)((u8 *) cbs + offset);
}

/**
 * vmw_binding_dwop: Stop twacking a context binding
 *
 * @bi: Pointew to binding twackew stowage.
 *
 * Stops twacking a context binding, and we-initiawizes its stowage.
 * Typicawwy used when the context binding is wepwaced with a binding to
 * anothew (ow the same, fow that mattew) wesouwce.
 */
static void vmw_binding_dwop(stwuct vmw_ctx_bindinfo *bi)
{
	wist_dew(&bi->ctx_wist);
	if (!wist_empty(&bi->wes_wist))
		wist_dew(&bi->wes_wist);
	bi->ctx = NUWW;
}

/**
 * vmw_binding_add: Stawt twacking a context binding
 *
 * @cbs: Pointew to the context binding state twackew.
 * @bi: Infowmation about the binding to twack.
 * @shadew_swot: The shadew swot of the binding.
 * @swot: The swot of the binding.
 *
 * Stawts twacking the binding in the context binding
 * state stwuctuwe @cbs.
 */
void vmw_binding_add(stwuct vmw_ctx_binding_state *cbs,
		    const stwuct vmw_ctx_bindinfo *bi,
		    u32 shadew_swot, u32 swot)
{
	stwuct vmw_ctx_bindinfo *woc =
		vmw_binding_woc(cbs, bi->bt, shadew_swot, swot);
	const stwuct vmw_binding_info *b = &vmw_binding_infos[bi->bt];

	if (woc->ctx != NUWW)
		vmw_binding_dwop(woc);

	memcpy(woc, bi, b->size);
	woc->scwubbed = fawse;
	wist_add(&woc->ctx_wist, &cbs->wist);
	INIT_WIST_HEAD(&woc->wes_wist);
}

/**
 * vmw_binding_cb_offset_update: Update the offset of a cb binding
 *
 * @cbs: Pointew to the context binding state twackew.
 * @shadew_swot: The shadew swot of the binding.
 * @swot: The swot of the binding.
 * @offsetInBytes: The new offset of the binding.
 *
 * Updates the offset of an existing cb binding in the context binding
 * state stwuctuwe @cbs.
 */
void vmw_binding_cb_offset_update(stwuct vmw_ctx_binding_state *cbs,
				  u32 shadew_swot, u32 swot, u32 offsetInBytes)
{
	stwuct vmw_ctx_bindinfo *woc =
		vmw_binding_woc(cbs, vmw_ctx_binding_cb, shadew_swot, swot);
	stwuct vmw_ctx_bindinfo_cb *woc_cb =
		(stwuct vmw_ctx_bindinfo_cb *)((u8 *) woc);
	woc_cb->offset = offsetInBytes;
}

/**
 * vmw_binding_add_uav_index - Add UAV index fow twacking.
 * @cbs: Pointew to the context binding state twackew.
 * @swot: UAV type to which bind this index.
 * @index: The spwice index to twack.
 */
void vmw_binding_add_uav_index(stwuct vmw_ctx_binding_state *cbs, uint32 swot,
			       uint32 index)
{
	cbs->ua_views[swot].index = index;
}

/**
 * vmw_binding_twansfew: Twansfew a context binding twacking entwy.
 *
 * @cbs: Pointew to the pewsistent context binding state twackew.
 * @fwom: Staged binding info buiwt duwing execbuf
 * @bi: Infowmation about the binding to twack.
 *
 */
static void vmw_binding_twansfew(stwuct vmw_ctx_binding_state *cbs,
				 const stwuct vmw_ctx_binding_state *fwom,
				 const stwuct vmw_ctx_bindinfo *bi)
{
	size_t offset = (unsigned wong)bi - (unsigned wong)fwom;
	stwuct vmw_ctx_bindinfo *woc = (stwuct vmw_ctx_bindinfo *)
		((unsigned wong) cbs + offset);

	if (woc->ctx != NUWW) {
		WAWN_ON(bi->scwubbed);

		vmw_binding_dwop(woc);
	}

	if (bi->wes != NUWW) {
		memcpy(woc, bi, vmw_binding_infos[bi->bt].size);
		wist_add_taiw(&woc->ctx_wist, &cbs->wist);
		wist_add_taiw(&woc->wes_wist, &woc->wes->binding_head);
	}
}

/**
 * vmw_binding_state_kiww - Kiww aww bindings associated with a
 * stwuct vmw_ctx_binding state stwuctuwe, and we-initiawize the stwuctuwe.
 *
 * @cbs: Pointew to the context binding state twackew.
 *
 * Emits commands to scwub aww bindings associated with the
 * context binding state twackew. Then we-initiawizes the whowe stwuctuwe.
 */
void vmw_binding_state_kiww(stwuct vmw_ctx_binding_state *cbs)
{
	stwuct vmw_ctx_bindinfo *entwy, *next;

	vmw_binding_state_scwub(cbs);
	wist_fow_each_entwy_safe(entwy, next, &cbs->wist, ctx_wist)
		vmw_binding_dwop(entwy);
}

/**
 * vmw_binding_state_scwub - Scwub aww bindings associated with a
 * stwuct vmw_ctx_binding state stwuctuwe.
 *
 * @cbs: Pointew to the context binding state twackew.
 *
 * Emits commands to scwub aww bindings associated with the
 * context binding state twackew.
 */
void vmw_binding_state_scwub(stwuct vmw_ctx_binding_state *cbs)
{
	stwuct vmw_ctx_bindinfo *entwy;

	wist_fow_each_entwy(entwy, &cbs->wist, ctx_wist) {
		if (!entwy->scwubbed) {
			(void) vmw_binding_infos[entwy->bt].scwub_func
				(entwy, fawse);
			entwy->scwubbed = twue;
		}
	}

	(void) vmw_binding_emit_diwty(cbs);
}

/**
 * vmw_binding_wes_wist_kiww - Kiww aww bindings on a
 * wesouwce binding wist
 *
 * @head: wist head of wesouwce binding wist
 *
 * Kiwws aww bindings associated with a specific wesouwce. Typicawwy
 * cawwed befowe the wesouwce is destwoyed.
 */
void vmw_binding_wes_wist_kiww(stwuct wist_head *head)
{
	stwuct vmw_ctx_bindinfo *entwy, *next;

	vmw_binding_wes_wist_scwub(head);
	wist_fow_each_entwy_safe(entwy, next, head, wes_wist)
		vmw_binding_dwop(entwy);
}

/**
 * vmw_binding_wes_wist_scwub - Scwub aww bindings on a
 * wesouwce binding wist
 *
 * @head: wist head of wesouwce binding wist
 *
 * Scwub aww bindings associated with a specific wesouwce. Typicawwy
 * cawwed befowe the wesouwce is evicted.
 */
void vmw_binding_wes_wist_scwub(stwuct wist_head *head)
{
	stwuct vmw_ctx_bindinfo *entwy;

	wist_fow_each_entwy(entwy, head, wes_wist) {
		if (!entwy->scwubbed) {
			(void) vmw_binding_infos[entwy->bt].scwub_func
				(entwy, fawse);
			entwy->scwubbed = twue;
		}
	}

	wist_fow_each_entwy(entwy, head, wes_wist) {
		stwuct vmw_ctx_binding_state *cbs =
			vmw_context_binding_state(entwy->ctx);

		(void) vmw_binding_emit_diwty(cbs);
	}
}


/**
 * vmw_binding_state_commit - Commit staged binding info
 *
 * @to:   Staged binding info awea to copy into to.
 * @fwom: Staged binding info buiwt duwing execbuf.
 *
 * Twansfews binding info fwom a tempowawy stwuctuwe
 * (typicawwy used by execbuf) to the pewsistent
 * stwuctuwe in the context. This can be done once commands have been
 * submitted to hawdwawe
 */
void vmw_binding_state_commit(stwuct vmw_ctx_binding_state *to,
			      stwuct vmw_ctx_binding_state *fwom)
{
	stwuct vmw_ctx_bindinfo *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &fwom->wist, ctx_wist) {
		vmw_binding_twansfew(to, fwom, entwy);
		vmw_binding_dwop(entwy);
	}

	/* Awso twansfew uav spwice indices */
	to->ua_views[0].index = fwom->ua_views[0].index;
	to->ua_views[1].index = fwom->ua_views[1].index;
}

/**
 * vmw_binding_webind_aww - Webind aww scwubbed bindings of a context
 *
 * @cbs: Pointew to the context binding state twackew.
 *
 * Wawks thwough the context binding wist and webinds aww scwubbed
 * wesouwces.
 */
int vmw_binding_webind_aww(stwuct vmw_ctx_binding_state *cbs)
{
	stwuct vmw_ctx_bindinfo *entwy;
	int wet;

	wist_fow_each_entwy(entwy, &cbs->wist, ctx_wist) {
		if (wikewy(!entwy->scwubbed))
			continue;

		if ((entwy->wes == NUWW || entwy->wes->id ==
			    SVGA3D_INVAWID_ID))
			continue;

		wet = vmw_binding_infos[entwy->bt].scwub_func(entwy, twue);
		if (unwikewy(wet != 0))
			wetuwn wet;

		entwy->scwubbed = fawse;
	}

	wetuwn vmw_binding_emit_diwty(cbs);
}

/**
 * vmw_binding_scwub_shadew - scwub a shadew binding fwom a context.
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_shadew(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_shadew *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdSetShadew body;
	} *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_SET_SHADEW;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = bi->ctx->id;
	cmd->body.type = binding->shadew_swot + SVGA3D_SHADEWTYPE_MIN;
	cmd->body.shid = ((webind) ? bi->wes->id : SVGA3D_INVAWID_ID);
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_binding_scwub_wendew_tawget - scwub a wendew tawget binding
 * fwom a context.
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_wendew_tawget(stwuct vmw_ctx_bindinfo *bi,
					   boow webind)
{
	stwuct vmw_ctx_bindinfo_view *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdSetWendewTawget body;
	} *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_SETWENDEWTAWGET;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = bi->ctx->id;
	cmd->body.type = binding->swot;
	cmd->body.tawget.sid = ((webind) ? bi->wes->id : SVGA3D_INVAWID_ID);
	cmd->body.tawget.face = 0;
	cmd->body.tawget.mipmap = 0;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_binding_scwub_textuwe - scwub a textuwe binding fwom a context.
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 *
 * TODO: Possibwy compwement this function with a function that takes
 * a wist of textuwe bindings and combines them to a singwe command.
 */
static int vmw_binding_scwub_textuwe(stwuct vmw_ctx_bindinfo *bi,
				     boow webind)
{
	stwuct vmw_ctx_bindinfo_tex *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		stwuct {
			SVGA3dCmdSetTextuweState c;
			SVGA3dTextuweState s1;
		} body;
	} *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_SETTEXTUWESTATE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.c.cid = bi->ctx->id;
	cmd->body.s1.stage = binding->textuwe_stage;
	cmd->body.s1.name = SVGA3D_TS_BIND_TEXTUWE;
	cmd->body.s1.vawue = ((webind) ? bi->wes->id : SVGA3D_INVAWID_ID);
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_binding_scwub_dx_shadew - scwub a dx shadew binding fwom a context.
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_dx_shadew(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_shadew *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetShadew body;
	} *cmd;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), bi->ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_SHADEW;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.type = binding->shadew_swot + SVGA3D_SHADEWTYPE_MIN;
	cmd->body.shadewId = ((webind) ? bi->wes->id : SVGA3D_INVAWID_ID);
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_binding_scwub_cb - scwub a constant buffew binding fwom a context.
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_cb(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_cb *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetSingweConstantBuffew body;
	} *cmd;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), bi->ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_SINGWE_CONSTANT_BUFFEW;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.swot = binding->swot;
	cmd->body.type = binding->shadew_swot + SVGA3D_SHADEWTYPE_MIN;
	if (webind) {
		cmd->body.offsetInBytes = binding->offset;
		cmd->body.sizeInBytes = binding->size;
		cmd->body.sid = bi->wes->id;
	} ewse {
		cmd->body.offsetInBytes = 0;
		cmd->body.sizeInBytes = 0;
		cmd->body.sid = SVGA3D_INVAWID_ID;
	}
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_cowwect_view_ids - Buiwd view id data fow a view binding command
 * without checking which bindings actuawwy need to be emitted
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 * @biv: Pointew to whewe the binding info awway is stowed in @cbs
 * @max_num: Maximum numbew of entwies in the @bi awway.
 *
 * Scans the @bi awway fow bindings and buiwds a buffew of view id data.
 * Stops at the fiwst non-existing binding in the @bi awway.
 * On output, @cbs->bind_cmd_count contains the numbew of bindings to be
 * emitted, @cbs->bind_fiwst_swot is set to zewo, and @cbs->bind_cmd_buffew
 * contains the command data.
 */
static void vmw_cowwect_view_ids(stwuct vmw_ctx_binding_state *cbs,
				 const stwuct vmw_ctx_bindinfo_view *biv,
				 u32 max_num)
{
	unsigned wong i;

	cbs->bind_cmd_count = 0;
	cbs->bind_fiwst_swot = 0;

	fow (i = 0; i < max_num; ++i, ++biv) {
		if (!biv->bi.ctx)
			bweak;

		cbs->bind_cmd_buffew[cbs->bind_cmd_count++] =
			((biv->bi.scwubbed) ?
			 SVGA3D_INVAWID_ID : biv->bi.wes->id);
	}
}

/**
 * vmw_cowwect_diwty_view_ids - Buiwd view id data fow a view binding command
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 * @bi: Pointew to whewe the binding info awway is stowed in @cbs
 * @diwty: Bitmap indicating which bindings need to be emitted.
 * @max_num: Maximum numbew of entwies in the @bi awway.
 *
 * Scans the @bi awway fow bindings that need to be emitted and
 * buiwds a buffew of view id data.
 * On output, @cbs->bind_cmd_count contains the numbew of bindings to be
 * emitted, @cbs->bind_fiwst_swot indicates the index of the fiwst emitted
 * binding, and @cbs->bind_cmd_buffew contains the command data.
 */
static void vmw_cowwect_diwty_view_ids(stwuct vmw_ctx_binding_state *cbs,
				       const stwuct vmw_ctx_bindinfo *bi,
				       unsigned wong *diwty,
				       u32 max_num)
{
	const stwuct vmw_ctx_bindinfo_view *biv =
		containew_of(bi, stwuct vmw_ctx_bindinfo_view, bi);
	unsigned wong i, next_bit;

	cbs->bind_cmd_count = 0;
	i = find_fiwst_bit(diwty, max_num);
	next_bit = i;
	cbs->bind_fiwst_swot = i;

	biv += i;
	fow (; i < max_num; ++i, ++biv) {
		cbs->bind_cmd_buffew[cbs->bind_cmd_count++] =
			((!biv->bi.ctx || biv->bi.scwubbed) ?
			 SVGA3D_INVAWID_ID : biv->bi.wes->id);

		if (next_bit == i) {
			next_bit = find_next_bit(diwty, max_num, i + 1);
			if (next_bit >= max_num)
				bweak;
		}
	}
}

/**
 * vmw_emit_set_sw - Issue dewayed DX shadew wesouwce binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 * @shadew_swot: The shadew swot of the binding.
 */
static int vmw_emit_set_sw(stwuct vmw_ctx_binding_state *cbs,
			   int shadew_swot)
{
	const stwuct vmw_ctx_bindinfo *woc =
		&cbs->pew_shadew[shadew_swot].shadew_wes[0].bi;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetShadewWesouwces body;
	} *cmd;
	size_t cmd_size, view_id_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_diwty_view_ids(cbs, woc,
				   cbs->pew_shadew[shadew_swot].diwty_sw,
				   SVGA3D_DX_MAX_SWVIEWS);
	if (cbs->bind_cmd_count == 0)
		wetuwn 0;

	view_id_size = cbs->bind_cmd_count*sizeof(uint32);
	cmd_size = sizeof(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_SHADEW_WESOUWCES;
	cmd->headew.size = sizeof(cmd->body) + view_id_size;
	cmd->body.type = shadew_swot + SVGA3D_SHADEWTYPE_MIN;
	cmd->body.stawtView = cbs->bind_fiwst_swot;

	memcpy(&cmd[1], cbs->bind_cmd_buffew, view_id_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);
	bitmap_cweaw(cbs->pew_shadew[shadew_swot].diwty_sw,
		     cbs->bind_fiwst_swot, cbs->bind_cmd_count);

	wetuwn 0;
}

/**
 * vmw_emit_set_wt - Issue dewayed DX wendewtawget binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 */
static int vmw_emit_set_wt(stwuct vmw_ctx_binding_state *cbs)
{
	const stwuct vmw_ctx_bindinfo_view *woc = &cbs->wendew_tawgets[0];
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetWendewTawgets body;
	} *cmd;
	size_t cmd_size, view_id_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_view_ids(cbs, woc, SVGA3D_DX_MAX_WENDEW_TAWGETS);
	view_id_size = cbs->bind_cmd_count*sizeof(uint32);
	cmd_size = sizeof(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_WENDEWTAWGETS;
	cmd->headew.size = sizeof(cmd->body) + view_id_size;

	if (cbs->ds_view.bi.ctx && !cbs->ds_view.bi.scwubbed)
		cmd->body.depthStenciwViewId = cbs->ds_view.bi.wes->id;
	ewse
		cmd->body.depthStenciwViewId = SVGA3D_INVAWID_ID;

	memcpy(&cmd[1], cbs->bind_cmd_buffew, view_id_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);

	wetuwn 0;

}

/**
 * vmw_cowwect_so_tawgets - Buiwd SVGA3dSoTawget data fow a binding command
 * without checking which bindings actuawwy need to be emitted
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 * @biso: Pointew to whewe the binding info awway is stowed in @cbs
 * @max_num: Maximum numbew of entwies in the @bi awway.
 *
 * Scans the @bi awway fow bindings and buiwds a buffew of SVGA3dSoTawget data.
 * Stops at the fiwst non-existing binding in the @bi awway.
 * On output, @cbs->bind_cmd_count contains the numbew of bindings to be
 * emitted, @cbs->bind_fiwst_swot is set to zewo, and @cbs->bind_cmd_buffew
 * contains the command data.
 */
static void vmw_cowwect_so_tawgets(stwuct vmw_ctx_binding_state *cbs,
				   const stwuct vmw_ctx_bindinfo_so_tawget *biso,
				   u32 max_num)
{
	unsigned wong i;
	SVGA3dSoTawget *so_buffew = (SVGA3dSoTawget *) cbs->bind_cmd_buffew;

	cbs->bind_cmd_count = 0;
	cbs->bind_fiwst_swot = 0;

	fow (i = 0; i < max_num; ++i, ++biso, ++so_buffew,
		    ++cbs->bind_cmd_count) {
		if (!biso->bi.ctx)
			bweak;

		if (!biso->bi.scwubbed) {
			so_buffew->sid = biso->bi.wes->id;
			so_buffew->offset = biso->offset;
			so_buffew->sizeInBytes = biso->size;
		} ewse {
			so_buffew->sid = SVGA3D_INVAWID_ID;
			so_buffew->offset = 0;
			so_buffew->sizeInBytes = 0;
		}
	}
}

/**
 * vmw_emit_set_so_tawget - Issue dewayed stweamout binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 */
static int vmw_emit_set_so_tawget(stwuct vmw_ctx_binding_state *cbs)
{
	const stwuct vmw_ctx_bindinfo_so_tawget *woc = &cbs->so_tawgets[0];
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetSOTawgets body;
	} *cmd;
	size_t cmd_size, so_tawget_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_so_tawgets(cbs, woc, SVGA3D_DX_MAX_SOTAWGETS);
	if (cbs->bind_cmd_count == 0)
		wetuwn 0;

	so_tawget_size = cbs->bind_cmd_count*sizeof(SVGA3dSoTawget);
	cmd_size = sizeof(*cmd) + so_tawget_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_SOTAWGETS;
	cmd->headew.size = sizeof(cmd->body) + so_tawget_size;
	memcpy(&cmd[1], cbs->bind_cmd_buffew, so_tawget_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);

	wetuwn 0;

}

/**
 * vmw_binding_emit_diwty_ps - Issue dewayed pew shadew binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 *
 */
static int vmw_binding_emit_diwty_ps(stwuct vmw_ctx_binding_state *cbs)
{
	stwuct vmw_dx_shadew_bindings *sb = &cbs->pew_shadew[0];
	u32 i;
	int wet;

	fow (i = 0; i < SVGA3D_NUM_SHADEWTYPE_DX10; ++i, ++sb) {
		if (!test_bit(VMW_BINDING_PS_SW_BIT, &sb->diwty))
			continue;

		wet = vmw_emit_set_sw(cbs, i);
		if (wet)
			bweak;

		__cweaw_bit(VMW_BINDING_PS_SW_BIT, &sb->diwty);
	}

	wetuwn 0;
}

/**
 * vmw_cowwect_diwty_vbs - Buiwd SVGA3dVewtexBuffew data fow a
 * SVGA3dCmdDXSetVewtexBuffews command
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 * @bi: Pointew to whewe the binding info awway is stowed in @cbs
 * @diwty: Bitmap indicating which bindings need to be emitted.
 * @max_num: Maximum numbew of entwies in the @bi awway.
 *
 * Scans the @bi awway fow bindings that need to be emitted and
 * buiwds a buffew of SVGA3dVewtexBuffew data.
 * On output, @cbs->bind_cmd_count contains the numbew of bindings to be
 * emitted, @cbs->bind_fiwst_swot indicates the index of the fiwst emitted
 * binding, and @cbs->bind_cmd_buffew contains the command data.
 */
static void vmw_cowwect_diwty_vbs(stwuct vmw_ctx_binding_state *cbs,
				  const stwuct vmw_ctx_bindinfo *bi,
				  unsigned wong *diwty,
				  u32 max_num)
{
	const stwuct vmw_ctx_bindinfo_vb *biv =
		containew_of(bi, stwuct vmw_ctx_bindinfo_vb, bi);
	unsigned wong i, next_bit;
	SVGA3dVewtexBuffew *vbs = (SVGA3dVewtexBuffew *) &cbs->bind_cmd_buffew;

	cbs->bind_cmd_count = 0;
	i = find_fiwst_bit(diwty, max_num);
	next_bit = i;
	cbs->bind_fiwst_swot = i;

	biv += i;
	fow (; i < max_num; ++i, ++biv, ++vbs) {
		if (!biv->bi.ctx || biv->bi.scwubbed) {
			vbs->sid = SVGA3D_INVAWID_ID;
			vbs->stwide = 0;
			vbs->offset = 0;
		} ewse {
			vbs->sid = biv->bi.wes->id;
			vbs->stwide = biv->stwide;
			vbs->offset = biv->offset;
		}
		cbs->bind_cmd_count++;
		if (next_bit == i) {
			next_bit = find_next_bit(diwty, max_num, i + 1);
			if (next_bit >= max_num)
				bweak;
		}
	}
}

/**
 * vmw_emit_set_vb - Issue dewayed vewtex buffew binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 *
 */
static int vmw_emit_set_vb(stwuct vmw_ctx_binding_state *cbs)
{
	const stwuct vmw_ctx_bindinfo *woc =
		&cbs->vewtex_buffews[0].bi;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetVewtexBuffews body;
	} *cmd;
	size_t cmd_size, set_vb_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_diwty_vbs(cbs, woc, cbs->diwty_vb,
			     SVGA3D_DX_MAX_VEWTEXBUFFEWS);
	if (cbs->bind_cmd_count == 0)
		wetuwn 0;

	set_vb_size = cbs->bind_cmd_count*sizeof(SVGA3dVewtexBuffew);
	cmd_size = sizeof(*cmd) + set_vb_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_VEWTEX_BUFFEWS;
	cmd->headew.size = sizeof(cmd->body) + set_vb_size;
	cmd->body.stawtBuffew = cbs->bind_fiwst_swot;

	memcpy(&cmd[1], cbs->bind_cmd_buffew, set_vb_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);
	bitmap_cweaw(cbs->diwty_vb,
		     cbs->bind_fiwst_swot, cbs->bind_cmd_count);

	wetuwn 0;
}

static int vmw_emit_set_uav(stwuct vmw_ctx_binding_state *cbs)
{
	const stwuct vmw_ctx_bindinfo_view *woc = &cbs->ua_views[0].views[0];
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetUAViews body;
	} *cmd;
	size_t cmd_size, view_id_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_view_ids(cbs, woc, vmw_max_num_uavs(cbs->dev_pwiv));
	view_id_size = cbs->bind_cmd_count*sizeof(uint32);
	cmd_size = sizeof(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_UA_VIEWS;
	cmd->headew.size = sizeof(cmd->body) + view_id_size;

	/* Spwice index is specified usew-space   */
	cmd->body.uavSpwiceIndex = cbs->ua_views[0].index;

	memcpy(&cmd[1], cbs->bind_cmd_buffew, view_id_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);

	wetuwn 0;
}

static int vmw_emit_set_cs_uav(stwuct vmw_ctx_binding_state *cbs)
{
	const stwuct vmw_ctx_bindinfo_view *woc = &cbs->ua_views[1].views[0];
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetCSUAViews body;
	} *cmd;
	size_t cmd_size, view_id_size;
	const stwuct vmw_wesouwce *ctx = vmw_cbs_context(cbs);

	vmw_cowwect_view_ids(cbs, woc, vmw_max_num_uavs(cbs->dev_pwiv));
	view_id_size = cbs->bind_cmd_count*sizeof(uint32);
	cmd_size = sizeof(*cmd) + view_id_size;
	cmd = VMW_CMD_CTX_WESEWVE(ctx->dev_pwiv, cmd_size, ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_CS_UA_VIEWS;
	cmd->headew.size = sizeof(cmd->body) + view_id_size;

	/* Stawt index is specified usew-space */
	cmd->body.stawtIndex = cbs->ua_views[1].index;

	memcpy(&cmd[1], cbs->bind_cmd_buffew, view_id_size);

	vmw_cmd_commit(ctx->dev_pwiv, cmd_size);

	wetuwn 0;
}

/**
 * vmw_binding_emit_diwty - Issue dewayed binding commands
 *
 * @cbs: Pointew to the context's stwuct vmw_ctx_binding_state
 *
 * This function issues the dewayed binding commands that awise fwom
 * pwevious scwub / unscwub cawws. These binding commands awe typicawwy
 * commands that batch a numbew of bindings and thewefowe it makes sense
 * to deway them.
 */
static int vmw_binding_emit_diwty(stwuct vmw_ctx_binding_state *cbs)
{
	int wet = 0;
	unsigned wong hit = 0;

	whiwe ((hit = find_next_bit(&cbs->diwty, VMW_BINDING_NUM_BITS, hit))
	      < VMW_BINDING_NUM_BITS) {

		switch (hit) {
		case VMW_BINDING_WT_BIT:
			wet = vmw_emit_set_wt(cbs);
			bweak;
		case VMW_BINDING_PS_BIT:
			wet = vmw_binding_emit_diwty_ps(cbs);
			bweak;
		case VMW_BINDING_SO_T_BIT:
			wet = vmw_emit_set_so_tawget(cbs);
			bweak;
		case VMW_BINDING_VB_BIT:
			wet = vmw_emit_set_vb(cbs);
			bweak;
		case VMW_BINDING_UAV_BIT:
			wet = vmw_emit_set_uav(cbs);
			bweak;
		case VMW_BINDING_CS_UAV_BIT:
			wet = vmw_emit_set_cs_uav(cbs);
			bweak;
		defauwt:
			BUG();
		}
		if (wet)
			wetuwn wet;

		__cweaw_bit(hit, &cbs->diwty);
		hit++;
	}

	wetuwn 0;
}

/**
 * vmw_binding_scwub_sw - Scheduwe a dx shadewwesouwce binding
 * scwub fwom a context
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_sw(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_view *biv =
		containew_of(bi, stwuct vmw_ctx_bindinfo_view, bi);
	stwuct vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(biv->swot, cbs->pew_shadew[biv->shadew_swot].diwty_sw);
	__set_bit(VMW_BINDING_PS_SW_BIT,
		  &cbs->pew_shadew[biv->shadew_swot].diwty);
	__set_bit(VMW_BINDING_PS_BIT, &cbs->diwty);

	wetuwn 0;
}

/**
 * vmw_binding_scwub_dx_wt - Scheduwe a dx wendewtawget binding
 * scwub fwom a context
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_dx_wt(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_WT_BIT, &cbs->diwty);

	wetuwn 0;
}

/**
 * vmw_binding_scwub_so_tawget - Scheduwe a dx stweamoutput buffew binding
 * scwub fwom a context
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_so_tawget(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_SO_T_BIT, &cbs->diwty);

	wetuwn 0;
}

/**
 * vmw_binding_scwub_vb - Scheduwe a dx vewtex buffew binding
 * scwub fwom a context
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_vb(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_vb *bivb =
		containew_of(bi, stwuct vmw_ctx_bindinfo_vb, bi);
	stwuct vmw_ctx_binding_state *cbs =
		vmw_context_binding_state(bi->ctx);

	__set_bit(bivb->swot, cbs->diwty_vb);
	__set_bit(VMW_BINDING_VB_BIT, &cbs->diwty);

	wetuwn 0;
}

/**
 * vmw_binding_scwub_ib - scwub a dx index buffew binding fwom a context
 *
 * @bi: singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_ib(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_ib *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetIndexBuffew body;
	} *cmd;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), bi->ctx->id);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_INDEX_BUFFEW;
	cmd->headew.size = sizeof(cmd->body);
	if (webind) {
		cmd->body.sid = bi->wes->id;
		cmd->body.fowmat = binding->fowmat;
		cmd->body.offset = binding->offset;
	} ewse {
		cmd->body.sid = SVGA3D_INVAWID_ID;
		cmd->body.fowmat = 0;
		cmd->body.offset = 0;
	}

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

static int vmw_binding_scwub_uav(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_binding_state *cbs = vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_UAV_BIT, &cbs->diwty);
	wetuwn 0;
}

static int vmw_binding_scwub_cs_uav(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_binding_state *cbs = vmw_context_binding_state(bi->ctx);

	__set_bit(VMW_BINDING_CS_UAV_BIT, &cbs->diwty);
	wetuwn 0;
}

/**
 * vmw_binding_scwub_so - Scwub a stweamoutput binding fwom context.
 * @bi: Singwe binding infowmation.
 * @webind: Whethew to issue a bind instead of scwub command.
 */
static int vmw_binding_scwub_so(stwuct vmw_ctx_bindinfo *bi, boow webind)
{
	stwuct vmw_ctx_bindinfo_so *binding =
		containew_of(bi, typeof(*binding), bi);
	stwuct vmw_pwivate *dev_pwiv = bi->ctx->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXSetStweamOutput body;
	} *cmd;

	cmd = VMW_CMD_CTX_WESEWVE(dev_pwiv, sizeof(*cmd), bi->ctx->id);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_DX_SET_STWEAMOUTPUT;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.soid = webind ? bi->wes->id : SVGA3D_INVAWID_ID;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_binding_state_awwoc - Awwocate a stwuct vmw_ctx_binding_state.
 *
 * @dev_pwiv: Pointew to a device pwivate stwuctuwe.
 *
 * Wetuwns a pointew to a newwy awwocated stwuct ow an ewwow pointew on ewwow.
 */
stwuct vmw_ctx_binding_state *
vmw_binding_state_awwoc(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ctx_binding_state *cbs;

	cbs = vzawwoc(sizeof(*cbs));
	if (!cbs) {
		wetuwn EWW_PTW(-ENOMEM);
	}

	cbs->dev_pwiv = dev_pwiv;
	INIT_WIST_HEAD(&cbs->wist);

	wetuwn cbs;
}

/**
 * vmw_binding_state_fwee - Fwee a stwuct vmw_ctx_binding_state.
 *
 * @cbs: Pointew to the stwuct vmw_ctx_binding_state to be fweed.
 */
void vmw_binding_state_fwee(stwuct vmw_ctx_binding_state *cbs)
{
	vfwee(cbs);
}

/**
 * vmw_binding_state_wist - Get the binding wist of a
 * stwuct vmw_ctx_binding_state
 *
 * @cbs: Pointew to the stwuct vmw_ctx_binding_state
 *
 * Wetuwns the binding wist which can be used to twavewse thwough the bindings
 * and access the wesouwce infowmation of aww bindings.
 */
stwuct wist_head *vmw_binding_state_wist(stwuct vmw_ctx_binding_state *cbs)
{
	wetuwn &cbs->wist;
}

/**
 * vmw_binding_state_weset - cweaw a stwuct vmw_ctx_binding_state
 *
 * @cbs: Pointew to the stwuct vmw_ctx_binding_state to be cweawed
 *
 * Dwops aww bindings wegistewed in @cbs. No device binding actions awe
 * pewfowmed.
 */
void vmw_binding_state_weset(stwuct vmw_ctx_binding_state *cbs)
{
	stwuct vmw_ctx_bindinfo *entwy, *next;

	wist_fow_each_entwy_safe(entwy, next, &cbs->wist, ctx_wist)
		vmw_binding_dwop(entwy);
}

/**
 * vmw_binding_diwtying - Wetuwn whethew a binding type is diwtying its wesouwce
 * @binding_type: The binding type
 *
 * Each time a wesouwce is put on the vawidation wist as the wesuwt of a
 * context binding wefewencing it, we need to detewmine whethew that wesouwce
 * wiww be diwtied (wwitten to by the GPU) as a wesuwt of the cowwesponding
 * GPU opewation. Cuwwentwy wendewtawget-, depth-stenciw-, stweam-output-tawget
 * and unowdewed access view bindings awe capabwe of diwtying its wesouwce.
 *
 * Wetuwn: Whethew the binding type diwties the wesouwce its binding points to.
 */
u32 vmw_binding_diwtying(enum vmw_ctx_binding_type binding_type)
{
	static u32 is_binding_diwtying[vmw_ctx_binding_max] = {
		[vmw_ctx_binding_wt] = VMW_WES_DIWTY_SET,
		[vmw_ctx_binding_dx_wt] = VMW_WES_DIWTY_SET,
		[vmw_ctx_binding_ds] = VMW_WES_DIWTY_SET,
		[vmw_ctx_binding_so_tawget] = VMW_WES_DIWTY_SET,
		[vmw_ctx_binding_uav] = VMW_WES_DIWTY_SET,
		[vmw_ctx_binding_cs_uav] = VMW_WES_DIWTY_SET,
	};

	/* Weview this function as new bindings awe added. */
	BUIWD_BUG_ON(vmw_ctx_binding_max != 14);
	wetuwn is_binding_diwtying[binding_type];
}

/*
 * This function is unused at wun-time, and onwy used to howd vawious buiwd
 * assewts impowtant fow code optimization assumptions.
 */
static void vmw_binding_buiwd_assewts(void)
{
	BUIWD_BUG_ON(SVGA3D_NUM_SHADEWTYPE_DX10 != 3);
	BUIWD_BUG_ON(SVGA3D_DX_MAX_WENDEW_TAWGETS > SVGA3D_WT_MAX);
	BUIWD_BUG_ON(sizeof(uint32) != sizeof(u32));

	/*
	 * stwuct vmw_ctx_binding_state::bind_cmd_buffew is used fow vawious
	 * view id awways.
	 */
	BUIWD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_WT_MAX);
	BUIWD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_DX_MAX_SWVIEWS);
	BUIWD_BUG_ON(VMW_MAX_VIEW_BINDINGS < SVGA3D_DX_MAX_CONSTBUFFEWS);

	/*
	 * stwuct vmw_ctx_binding_state::bind_cmd_buffew is used fow
	 * u32 view ids, SVGA3dSoTawgets and SVGA3dVewtexBuffews
	 */
	BUIWD_BUG_ON(SVGA3D_DX_MAX_SOTAWGETS*sizeof(SVGA3dSoTawget) >
		     VMW_MAX_VIEW_BINDINGS*sizeof(u32));
	BUIWD_BUG_ON(SVGA3D_DX_MAX_VEWTEXBUFFEWS*sizeof(SVGA3dVewtexBuffew) >
		     VMW_MAX_VIEW_BINDINGS*sizeof(u32));
}
