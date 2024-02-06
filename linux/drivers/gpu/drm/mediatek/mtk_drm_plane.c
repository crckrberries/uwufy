// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: CK Hu <ck.hu@mediatek.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <winux/awign.h>

#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_dwm_gem.h"
#incwude "mtk_dwm_pwane.h"

static const u64 modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_AWM_AFBC(AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_SPWIT |
				AFBC_FOWMAT_MOD_SPAWSE),
	DWM_FOWMAT_MOD_INVAWID,
};

static void mtk_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct mtk_pwane_state *state;

	if (pwane->state) {
		__dwm_atomic_hewpew_pwane_destwoy_state(pwane->state);

		state = to_mtk_pwane_state(pwane->state);
		memset(state, 0, sizeof(*state));
	} ewse {
		state = kzawwoc(sizeof(*state), GFP_KEWNEW);
		if (!state)
			wetuwn;
	}

	__dwm_atomic_hewpew_pwane_weset(pwane, &state->base);

	state->base.pwane = pwane;
	state->pending.fowmat = DWM_FOWMAT_WGB565;
	state->pending.modifiew = DWM_FOWMAT_MOD_WINEAW;
}

static stwuct dwm_pwane_state *mtk_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct mtk_pwane_state *owd_state = to_mtk_pwane_state(pwane->state);
	stwuct mtk_pwane_state *state;

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &state->base);

	WAWN_ON(state->base.pwane != pwane);

	state->pending = owd_state->pending;

	wetuwn &state->base;
}

static boow mtk_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					   uint32_t fowmat,
					   uint64_t modifiew)
{
	if (modifiew == DWM_FOWMAT_MOD_WINEAW)
		wetuwn twue;

	if (modifiew != DWM_FOWMAT_MOD_AWM_AFBC(
				AFBC_FOWMAT_MOD_BWOCK_SIZE_32x8 |
				AFBC_FOWMAT_MOD_SPWIT |
				AFBC_FOWMAT_MOD_SPAWSE))
		wetuwn fawse;

	if (fowmat != DWM_FOWMAT_XWGB8888 &&
	    fowmat != DWM_FOWMAT_AWGB8888 &&
	    fowmat != DWM_FOWMAT_BGWX8888 &&
	    fowmat != DWM_FOWMAT_BGWA8888 &&
	    fowmat != DWM_FOWMAT_ABGW8888 &&
	    fowmat != DWM_FOWMAT_XBGW8888 &&
	    fowmat != DWM_FOWMAT_WGB888 &&
	    fowmat != DWM_FOWMAT_BGW888)
		wetuwn fawse;

	wetuwn twue;
}

static void mtk_dwm_pwane_destwoy_state(stwuct dwm_pwane *pwane,
					stwuct dwm_pwane_state *state)
{
	__dwm_atomic_hewpew_pwane_destwoy_state(state);
	kfwee(to_mtk_pwane_state(state));
}

static int mtk_pwane_atomic_async_check(stwuct dwm_pwane *pwane,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	if (pwane != new_pwane_state->cwtc->cuwsow)
		wetuwn -EINVAW;

	if (!pwane->state)
		wetuwn -EINVAW;

	if (!pwane->state->fb)
		wetuwn -EINVAW;

	wet = mtk_dwm_cwtc_pwane_check(new_pwane_state->cwtc, pwane,
				       to_mtk_pwane_state(new_pwane_state));
	if (wet)
		wetuwn wet;

	cwtc_state = dwm_atomic_get_existing_cwtc_state(state, new_pwane_state->cwtc);

	wetuwn dwm_atomic_hewpew_check_pwane_state(pwane->state, cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   twue, twue);
}

static void mtk_pwane_update_new_state(stwuct dwm_pwane_state *new_state,
				       stwuct mtk_pwane_state *mtk_pwane_state)
{
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_gem_object *gem;
	stwuct mtk_dwm_gem_obj *mtk_gem;
	unsigned int pitch, fowmat;
	u64 modifiew;
	dma_addw_t addw;
	dma_addw_t hdw_addw = 0;
	unsigned int hdw_pitch = 0;
	int offset;

	gem = fb->obj[0];
	mtk_gem = to_mtk_gem_obj(gem);
	addw = mtk_gem->dma_addw;
	pitch = fb->pitches[0];
	fowmat = fb->fowmat->fowmat;
	modifiew = fb->modifiew;

	if (modifiew == DWM_FOWMAT_MOD_WINEAW) {
		/*
		 * Using dma_addw_t vawiabwe to cawcuwate with muwtipwiew of diffewent types,
		 * fow exampwe: addw += (new_state->swc.x1 >> 16) * fb->fowmat->cpp[0];
		 * may cause covewity issue with unintentionaw ovewfwow.
		 */
		offset = (new_state->swc.x1 >> 16) * fb->fowmat->cpp[0];
		addw += offset;
		offset = (new_state->swc.y1 >> 16) * pitch;
		addw += offset;
	} ewse {
		int width_in_bwocks = AWIGN(fb->width, AFBC_DATA_BWOCK_WIDTH)
				      / AFBC_DATA_BWOCK_WIDTH;
		int height_in_bwocks = AWIGN(fb->height, AFBC_DATA_BWOCK_HEIGHT)
				       / AFBC_DATA_BWOCK_HEIGHT;
		int x_offset_in_bwocks = (new_state->swc.x1 >> 16) / AFBC_DATA_BWOCK_WIDTH;
		int y_offset_in_bwocks = (new_state->swc.y1 >> 16) / AFBC_DATA_BWOCK_HEIGHT;
		int hdw_size, hdw_offset;

		hdw_pitch = width_in_bwocks * AFBC_HEADEW_BWOCK_SIZE;
		pitch = width_in_bwocks * AFBC_DATA_BWOCK_WIDTH *
			AFBC_DATA_BWOCK_HEIGHT * fb->fowmat->cpp[0];

		hdw_size = AWIGN(hdw_pitch * height_in_bwocks, AFBC_HEADEW_AWIGNMENT);
		hdw_offset = hdw_pitch * y_offset_in_bwocks +
			AFBC_HEADEW_BWOCK_SIZE * x_offset_in_bwocks;

		/*
		 * Using dma_addw_t vawiabwe to cawcuwate with muwtipwiew of diffewent types,
		 * fow exampwe: addw += hdw_pitch * y_offset_in_bwocks;
		 * may cause covewity issue with unintentionaw ovewfwow.
		 */
		hdw_addw = addw + hdw_offset;

		/* The data pwane is offset by 1 additionaw bwock. */
		offset = pitch * y_offset_in_bwocks +
			 AFBC_DATA_BWOCK_WIDTH * AFBC_DATA_BWOCK_HEIGHT *
			 fb->fowmat->cpp[0] * (x_offset_in_bwocks + 1);

		/*
		 * Using dma_addw_t vawiabwe to cawcuwate with muwtipwiew of diffewent types,
		 * fow exampwe: addw += pitch * y_offset_in_bwocks;
		 * may cause covewity issue with unintentionaw ovewfwow.
		 */
		addw = addw + hdw_size + offset;
	}

	mtk_pwane_state->pending.enabwe = twue;
	mtk_pwane_state->pending.pitch = pitch;
	mtk_pwane_state->pending.hdw_pitch = hdw_pitch;
	mtk_pwane_state->pending.fowmat = fowmat;
	mtk_pwane_state->pending.modifiew = modifiew;
	mtk_pwane_state->pending.addw = addw;
	mtk_pwane_state->pending.hdw_addw = hdw_addw;
	mtk_pwane_state->pending.x = new_state->dst.x1;
	mtk_pwane_state->pending.y = new_state->dst.y1;
	mtk_pwane_state->pending.width = dwm_wect_width(&new_state->dst);
	mtk_pwane_state->pending.height = dwm_wect_height(&new_state->dst);
	mtk_pwane_state->pending.wotation = new_state->wotation;
	mtk_pwane_state->pending.cowow_encoding = new_state->cowow_encoding;
}

static void mtk_pwane_atomic_async_update(stwuct dwm_pwane *pwane,
					  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct mtk_pwane_state *new_pwane_state = to_mtk_pwane_state(pwane->state);

	pwane->state->cwtc_x = new_state->cwtc_x;
	pwane->state->cwtc_y = new_state->cwtc_y;
	pwane->state->cwtc_h = new_state->cwtc_h;
	pwane->state->cwtc_w = new_state->cwtc_w;
	pwane->state->swc_x = new_state->swc_x;
	pwane->state->swc_y = new_state->swc_y;
	pwane->state->swc_h = new_state->swc_h;
	pwane->state->swc_w = new_state->swc_w;

	mtk_pwane_update_new_state(new_state, new_pwane_state);
	swap(pwane->state->fb, new_state->fb);
	wmb(); /* Make suwe the above pawametews awe set befowe update */
	new_pwane_state->pending.async_diwty = twue;
	mtk_dwm_cwtc_async_update(new_state->cwtc, pwane, state);
}

static const stwuct dwm_pwane_funcs mtk_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = dwm_pwane_cweanup,
	.weset = mtk_pwane_weset,
	.atomic_dupwicate_state = mtk_pwane_dupwicate_state,
	.atomic_destwoy_state = mtk_dwm_pwane_destwoy_state,
	.fowmat_mod_suppowted = mtk_pwane_fowmat_mod_suppowted,
};

static int mtk_pwane_atomic_check(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_fwamebuffew *fb = new_pwane_state->fb;
	stwuct dwm_cwtc_state *cwtc_state;
	int wet;

	if (!fb)
		wetuwn 0;

	if (WAWN_ON(!new_pwane_state->cwtc))
		wetuwn 0;

	wet = mtk_dwm_cwtc_pwane_check(new_pwane_state->cwtc, pwane,
				       to_mtk_pwane_state(new_pwane_state));
	if (wet)
		wetuwn wet;

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wetuwn dwm_atomic_hewpew_check_pwane_state(new_pwane_state,
						   cwtc_state,
						   DWM_PWANE_NO_SCAWING,
						   DWM_PWANE_NO_SCAWING,
						   twue, twue);
}

static void mtk_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct mtk_pwane_state *mtk_pwane_state = to_mtk_pwane_state(new_state);
	mtk_pwane_state->pending.enabwe = fawse;
	wmb(); /* Make suwe the above pawametew is set befowe update */
	mtk_pwane_state->pending.diwty = twue;
}

static void mtk_pwane_atomic_update(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct mtk_pwane_state *mtk_pwane_state = to_mtk_pwane_state(new_state);

	if (!new_state->cwtc || WAWN_ON(!new_state->fb))
		wetuwn;

	if (!new_state->visibwe) {
		mtk_pwane_atomic_disabwe(pwane, state);
		wetuwn;
	}

	mtk_pwane_update_new_state(new_state, mtk_pwane_state);
	wmb(); /* Make suwe the above pawametews awe set befowe update */
	mtk_pwane_state->pending.diwty = twue;
}

static const stwuct dwm_pwane_hewpew_funcs mtk_pwane_hewpew_funcs = {
	.atomic_check = mtk_pwane_atomic_check,
	.atomic_update = mtk_pwane_atomic_update,
	.atomic_disabwe = mtk_pwane_atomic_disabwe,
	.atomic_async_update = mtk_pwane_atomic_async_update,
	.atomic_async_check = mtk_pwane_atomic_async_check,
};

int mtk_pwane_init(stwuct dwm_device *dev, stwuct dwm_pwane *pwane,
		   unsigned wong possibwe_cwtcs, enum dwm_pwane_type type,
		   unsigned int suppowted_wotations, const u32 *fowmats,
		   size_t num_fowmats)
{
	int eww;

	if (!fowmats || !num_fowmats) {
		DWM_EWWOW("no fowmats fow pwane\n");
		wetuwn -EINVAW;
	}

	eww = dwm_univewsaw_pwane_init(dev, pwane, possibwe_cwtcs,
				       &mtk_pwane_funcs, fowmats,
				       num_fowmats, modifiews, type, NUWW);
	if (eww) {
		DWM_EWWOW("faiwed to initiawize pwane\n");
		wetuwn eww;
	}

	if (suppowted_wotations & ~DWM_MODE_WOTATE_0) {
		eww = dwm_pwane_cweate_wotation_pwopewty(pwane,
							 DWM_MODE_WOTATE_0,
							 suppowted_wotations);
		if (eww)
			DWM_INFO("Cweate wotation pwopewty faiwed\n");
	}

	dwm_pwane_hewpew_add(pwane, &mtk_pwane_hewpew_funcs);

	wetuwn 0;
}
