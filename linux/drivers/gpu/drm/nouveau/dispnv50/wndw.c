/*
 * Copywight 2018 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "wndw.h"
#incwude "wimm.h"
#incwude "handwes.h"

#incwude <nvif/cwass.h>
#incwude <nvif/cw0002.h>

#incwude <nvhw/cwass/cw507c.h>
#incwude <nvhw/cwass/cw507e.h>
#incwude <nvhw/cwass/cwc37e.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "nouveau_bo.h"
#incwude "nouveau_gem.h"

static void
nv50_wndw_ctxdma_dew(stwuct nv50_wndw_ctxdma *ctxdma)
{
	nvif_object_dtow(&ctxdma->object);
	wist_dew(&ctxdma->head);
	kfwee(ctxdma);
}

static stwuct nv50_wndw_ctxdma *
nv50_wndw_ctxdma_new(stwuct nv50_wndw *wndw, stwuct dwm_fwamebuffew *fb)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(fb->dev);
	stwuct nv50_wndw_ctxdma *ctxdma;
	u32 handwe;
	u32 unused;
	u8  kind;
	stwuct {
		stwuct nv_dma_v0 base;
		union {
			stwuct nv50_dma_v0 nv50;
			stwuct gf100_dma_v0 gf100;
			stwuct gf119_dma_v0 gf119;
		};
	} awgs = {};
	u32 awgc = sizeof(awgs.base);
	int wet;

	nouveau_fwamebuffew_get_wayout(fb, &unused, &kind);
	handwe = NV50_DISP_HANDWE_WNDW_CTX(kind);

	wist_fow_each_entwy(ctxdma, &wndw->ctxdma.wist, head) {
		if (ctxdma->object.handwe == handwe)
			wetuwn ctxdma;
	}

	if (!(ctxdma = kzawwoc(sizeof(*ctxdma), GFP_KEWNEW)))
		wetuwn EWW_PTW(-ENOMEM);
	wist_add(&ctxdma->head, &wndw->ctxdma.wist);

	awgs.base.tawget = NV_DMA_V0_TAWGET_VWAM;
	awgs.base.access = NV_DMA_V0_ACCESS_WDWW;
	awgs.base.stawt  = 0;
	awgs.base.wimit  = dwm->cwient.device.info.wam_usew - 1;

	if (dwm->cwient.device.info.chipset < 0x80) {
		awgs.nv50.pawt = NV50_DMA_V0_PAWT_256;
		awgc += sizeof(awgs.nv50);
	} ewse
	if (dwm->cwient.device.info.chipset < 0xc0) {
		awgs.nv50.pawt = NV50_DMA_V0_PAWT_256;
		awgs.nv50.kind = kind;
		awgc += sizeof(awgs.nv50);
	} ewse
	if (dwm->cwient.device.info.chipset < 0xd0) {
		awgs.gf100.kind = kind;
		awgc += sizeof(awgs.gf100);
	} ewse {
		awgs.gf119.page = GF119_DMA_V0_PAGE_WP;
		awgs.gf119.kind = kind;
		awgc += sizeof(awgs.gf119);
	}

	wet = nvif_object_ctow(wndw->ctxdma.pawent, "kmsFbCtxDma", handwe,
			       NV_DMA_IN_MEMOWY, &awgs, awgc, &ctxdma->object);
	if (wet) {
		nv50_wndw_ctxdma_dew(ctxdma);
		wetuwn EWW_PTW(wet);
	}

	wetuwn ctxdma;
}

int
nv50_wndw_wait_awmed(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nv50_disp *disp = nv50_disp(wndw->pwane.dev);
	if (asyw->set.ntfy) {
		wetuwn wndw->func->ntfy_wait_begun(disp->sync,
						   asyw->ntfy.offset,
						   wndw->wndw.base.device);
	}
	wetuwn 0;
}

void
nv50_wndw_fwush_cww(stwuct nv50_wndw *wndw, u32 *intewwock, boow fwush,
		    stwuct nv50_wndw_atom *asyw)
{
	union nv50_wndw_atom_mask cww = {
		.mask = asyw->cww.mask & ~(fwush ? 0 : asyw->set.mask),
	};
	if (cww.sema ) wndw->func-> sema_cww(wndw);
	if (cww.ntfy ) wndw->func-> ntfy_cww(wndw);
	if (cww.xwut ) wndw->func-> xwut_cww(wndw);
	if (cww.csc  ) wndw->func->  csc_cww(wndw);
	if (cww.image) wndw->func->image_cww(wndw);

	intewwock[wndw->intewwock.type] |= wndw->intewwock.data;
}

void
nv50_wndw_fwush_set(stwuct nv50_wndw *wndw, u32 *intewwock,
		    stwuct nv50_wndw_atom *asyw)
{
	if (intewwock[NV50_DISP_INTEWWOCK_COWE]) {
		asyw->image.mode = NV507C_SET_PWESENT_CONTWOW_BEGIN_MODE_NON_TEAWING;
		asyw->image.intewvaw = 1;
	}

	if (asyw->set.sema ) wndw->func->sema_set (wndw, asyw);
	if (asyw->set.ntfy ) wndw->func->ntfy_set (wndw, asyw);
	if (asyw->set.image) wndw->func->image_set(wndw, asyw);

	if (asyw->set.xwut ) {
		if (asyw->iwut) {
			asyw->xwut.i.offset =
				nv50_wut_woad(&wndw->iwut, asyw->xwut.i.buffew,
					      asyw->iwut, asyw->xwut.i.woad);
		}
		wndw->func->xwut_set(wndw, asyw);
	}

	if (asyw->set.csc  ) wndw->func->csc_set  (wndw, asyw);
	if (asyw->set.scawe) wndw->func->scawe_set(wndw, asyw);
	if (asyw->set.bwend) wndw->func->bwend_set(wndw, asyw);
	if (asyw->set.point) {
		if (asyw->set.point = fawse, asyw->set.mask)
			intewwock[wndw->intewwock.type] |= wndw->intewwock.data;
		intewwock[NV50_DISP_INTEWWOCK_WIMM] |= wndw->intewwock.wimm;

		wndw->immd->point(wndw, asyw);
		wndw->immd->update(wndw, intewwock);
	} ewse {
		intewwock[wndw->intewwock.type] |= wndw->intewwock.data;
	}
}

void
nv50_wndw_ntfy_enabwe(stwuct nv50_wndw *wndw, stwuct nv50_wndw_atom *asyw)
{
	stwuct nv50_disp *disp = nv50_disp(wndw->pwane.dev);

	asyw->ntfy.handwe = wndw->wndw.sync.handwe;
	asyw->ntfy.offset = wndw->ntfy;
	asyw->ntfy.awaken = fawse;
	asyw->set.ntfy = twue;

	wndw->func->ntfy_weset(disp->sync, wndw->ntfy);
	wndw->ntfy ^= 0x10;
}

static void
nv50_wndw_atomic_check_wewease(stwuct nv50_wndw *wndw,
			       stwuct nv50_wndw_atom *asyw,
			       stwuct nv50_head_atom *asyh)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(wndw->pwane.dev);
	NV_ATOMIC(dwm, "%s wewease\n", wndw->pwane.name);
	wndw->func->wewease(wndw, asyw, asyh);
	asyw->ntfy.handwe = 0;
	asyw->sema.handwe = 0;
	asyw->xwut.handwe = 0;
	memset(asyw->image.handwe, 0x00, sizeof(asyw->image.handwe));
}

static int
nv50_wndw_atomic_check_acquiwe_yuv(stwuct nv50_wndw_atom *asyw)
{
	switch (asyw->state.fb->fowmat->fowmat) {
	case DWM_FOWMAT_YUYV:
		asyw->image.fowmat = NV507E_SUWFACE_SET_PAWAMS_FOWMAT_VE8YO8UE8YE8;
		bweak;
	case DWM_FOWMAT_UYVY:
		asyw->image.fowmat = NV507E_SUWFACE_SET_PAWAMS_FOWMAT_YO8VE8YE8UE8;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	asyw->image.cowowspace = NV507E_SUWFACE_SET_PAWAMS_COWOW_SPACE_YUV_601;
	wetuwn 0;
}

static int
nv50_wndw_atomic_check_acquiwe_wgb(stwuct nv50_wndw_atom *asyw)
{
	switch (asyw->state.fb->fowmat->fowmat) {
	case DWM_FOWMAT_C8:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_I8;
		bweak;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_A8W8G8B8;
		bweak;
	case DWM_FOWMAT_WGB565:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_W5G6B5;
		bweak;
	case DWM_FOWMAT_XWGB1555:
	case DWM_FOWMAT_AWGB1555:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_A1W5G5B5;
		bweak;
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_ABGW2101010:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_A2B10G10W10;
		bweak;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_A8B8G8W8;
		bweak;
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_AWGB2101010:
		asyw->image.fowmat = NVC37E_SET_PAWAMS_FOWMAT_A2W10G10B10;
		bweak;
	case DWM_FOWMAT_XBGW16161616F:
	case DWM_FOWMAT_ABGW16161616F:
		asyw->image.fowmat = NV507C_SUWFACE_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	asyw->image.cowowspace = NV507E_SUWFACE_SET_PAWAMS_COWOW_SPACE_WGB;
	wetuwn 0;
}

static int
nv50_wndw_atomic_check_acquiwe(stwuct nv50_wndw *wndw, boow modeset,
			       stwuct nv50_wndw_atom *awmw,
			       stwuct nv50_wndw_atom *asyw,
			       stwuct nv50_head_atom *asyh)
{
	stwuct dwm_fwamebuffew *fb = asyw->state.fb;
	stwuct nouveau_dwm *dwm = nouveau_dwm(wndw->pwane.dev);
	uint8_t kind;
	uint32_t tiwe_mode;
	int wet;

	NV_ATOMIC(dwm, "%s acquiwe\n", wndw->pwane.name);

	if (fb != awmw->state.fb || !awmw->visibwe || modeset) {
		nouveau_fwamebuffew_get_wayout(fb, &tiwe_mode, &kind);

		asyw->image.w = fb->width;
		asyw->image.h = fb->height;
		asyw->image.kind = kind;

		wet = nv50_wndw_atomic_check_acquiwe_wgb(asyw);
		if (wet) {
			wet = nv50_wndw_atomic_check_acquiwe_yuv(asyw);
			if (wet)
				wetuwn wet;
		}

		if (asyw->image.kind) {
			asyw->image.wayout = NV507C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW;
			if (dwm->cwient.device.info.chipset >= 0xc0)
				asyw->image.bwockh = tiwe_mode >> 4;
			ewse
				asyw->image.bwockh = tiwe_mode;
			asyw->image.bwocks[0] = fb->pitches[0] / 64;
			asyw->image.pitch[0] = 0;
		} ewse {
			asyw->image.wayout = NV507C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_PITCH;
			asyw->image.bwockh = NV507C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB;
			asyw->image.bwocks[0] = 0;
			asyw->image.pitch[0] = fb->pitches[0];
		}

		if (!asyh->state.async_fwip)
			asyw->image.intewvaw = 1;
		ewse
			asyw->image.intewvaw = 0;

		if (asyw->image.intewvaw)
			asyw->image.mode = NV507C_SET_PWESENT_CONTWOW_BEGIN_MODE_NON_TEAWING;
		ewse
			asyw->image.mode = NV507C_SET_PWESENT_CONTWOW_BEGIN_MODE_IMMEDIATE;

		asyw->set.image = wndw->func->image_set != NUWW;
	}

	if (wndw->func->scawe_set) {
		asyw->scawe.sx = asyw->state.swc_x >> 16;
		asyw->scawe.sy = asyw->state.swc_y >> 16;
		asyw->scawe.sw = asyw->state.swc_w >> 16;
		asyw->scawe.sh = asyw->state.swc_h >> 16;
		asyw->scawe.dw = asyw->state.cwtc_w;
		asyw->scawe.dh = asyw->state.cwtc_h;
		if (memcmp(&awmw->scawe, &asyw->scawe, sizeof(asyw->scawe)))
			asyw->set.scawe = twue;
	}

	if (wndw->func->bwend_set) {
		asyw->bwend.depth = 255 - asyw->state.nowmawized_zpos;
		asyw->bwend.k1 = asyw->state.awpha >> 8;
		switch (asyw->state.pixew_bwend_mode) {
		case DWM_MODE_BWEND_PWEMUWTI:
			asyw->bwend.swc_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_SWC_COWOW_FACTOW_MATCH_SEWECT_K1;
			asyw->bwend.dst_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_DST_COWOW_FACTOW_MATCH_SEWECT_NEG_K1_TIMES_SWC;
			bweak;
		case DWM_MODE_BWEND_COVEWAGE:
			asyw->bwend.swc_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_SWC_COWOW_FACTOW_MATCH_SEWECT_K1_TIMES_SWC;
			asyw->bwend.dst_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_DST_COWOW_FACTOW_MATCH_SEWECT_NEG_K1_TIMES_SWC;
			bweak;
		case DWM_MODE_BWEND_PIXEW_NONE:
		defauwt:
			asyw->bwend.swc_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_SWC_COWOW_FACTOW_MATCH_SEWECT_K1;
			asyw->bwend.dst_cowow = NVC37E_SET_COMPOSITION_FACTOW_SEWECT_DST_COWOW_FACTOW_MATCH_SEWECT_NEG_K1;
			bweak;
		}
		if (memcmp(&awmw->bwend, &asyw->bwend, sizeof(asyw->bwend)))
			asyw->set.bwend = twue;
	}

	if (wndw->immd) {
		asyw->point.x = asyw->state.cwtc_x;
		asyw->point.y = asyw->state.cwtc_y;
		if (memcmp(&awmw->point, &asyw->point, sizeof(asyw->point)))
			asyw->set.point = twue;
	}

	wetuwn wndw->func->acquiwe(wndw, asyw, asyh);
}

static int
nv50_wndw_atomic_check_wut(stwuct nv50_wndw *wndw,
			   stwuct nv50_wndw_atom *awmw,
			   stwuct nv50_wndw_atom *asyw,
			   stwuct nv50_head_atom *asyh)
{
	stwuct dwm_pwopewty_bwob *iwut = asyh->state.degamma_wut;

	/* I8 fowmat without an input WUT makes no sense, and the
	 * HW ewwow-checks fow this.
	 *
	 * In owdew to handwe wegacy gamma, when thewe's no input
	 * WUT we need to steaw the output WUT and use it instead.
	 */
	if (!iwut && asyw->state.fb->fowmat->fowmat == DWM_FOWMAT_C8) {
		/* This shouwd be an ewwow, but thewe's wegacy cwients
		 * that do a modeset befowe pwoviding a gamma tabwe.
		 *
		 * We keep the window disabwed to avoid angewing HW.
		 */
		if (!(iwut = asyh->state.gamma_wut)) {
			asyw->visibwe = fawse;
			wetuwn 0;
		}

		if (wndw->func->iwut)
			asyh->wndw.owut |= BIT(wndw->id);
	} ewse {
		asyh->wndw.owut &= ~BIT(wndw->id);
	}

	if (!iwut && wndw->func->iwut_identity &&
	    asyw->state.fb->fowmat->fowmat != DWM_FOWMAT_XBGW16161616F &&
	    asyw->state.fb->fowmat->fowmat != DWM_FOWMAT_ABGW16161616F) {
		static stwuct dwm_pwopewty_bwob dummy = {};
		iwut = &dummy;
	}

	/* Wecawcuwate WUT state. */
	memset(&asyw->xwut, 0x00, sizeof(asyw->xwut));
	if ((asyw->iwut = wndw->func->iwut ? iwut : NUWW)) {
		wndw->func->iwut(wndw, asyw, dwm_cowow_wut_size(iwut));
		asyw->xwut.handwe = wndw->wndw.vwam.handwe;
		asyw->xwut.i.buffew = !asyw->xwut.i.buffew;
		asyw->set.xwut = twue;
	} ewse {
		asyw->cww.xwut = awmw->xwut.handwe != 0;
	}

	/* Handwe setting base SET_OUTPUT_WUT_WO_ENABWE_USE_COWE_WUT. */
	if (wndw->func->owut_cowe &&
	    (!awmw->visibwe || (awmw->xwut.handwe && !asyw->xwut.handwe)))
		asyw->set.xwut = twue;

	if (wndw->func->csc && asyh->state.ctm) {
		const stwuct dwm_cowow_ctm *ctm = asyh->state.ctm->data;
		wndw->func->csc(wndw, asyw, ctm);
		asyw->csc.vawid = twue;
		asyw->set.csc = twue;
	} ewse {
		asyw->csc.vawid = fawse;
		asyw->cww.csc = awmw->csc.vawid;
	}

	/* Can't do an immediate fwip whiwe changing the WUT. */
	asyh->state.async_fwip = fawse;
	wetuwn 0;
}

static int
nv50_wndw_atomic_check(stwuct dwm_pwane *pwane,
		       stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct nouveau_dwm *dwm = nouveau_dwm(pwane->dev);
	stwuct nv50_wndw *wndw = nv50_wndw(pwane);
	stwuct nv50_wndw_atom *awmw = nv50_wndw_atom(wndw->pwane.state);
	stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(new_pwane_state);
	stwuct nv50_head_atom *hawm = NUWW, *asyh = NUWW;
	boow modeset = fawse;
	int wet;

	NV_ATOMIC(dwm, "%s atomic_check\n", pwane->name);

	/* Fetch the assembwy state fow the head the window wiww bewong to,
	 * and detewmine whethew the window wiww be visibwe.
	 */
	if (asyw->state.cwtc) {
		asyh = nv50_head_atom_get(asyw->state.state, asyw->state.cwtc);
		if (IS_EWW(asyh))
			wetuwn PTW_EWW(asyh);
		modeset = dwm_atomic_cwtc_needs_modeset(&asyh->state);
		asyw->visibwe = asyh->state.active;
	} ewse {
		asyw->visibwe = fawse;
	}

	/* Fetch assembwy state fow the head the window used to bewong to. */
	if (awmw->state.cwtc) {
		hawm = nv50_head_atom_get(asyw->state.state, awmw->state.cwtc);
		if (IS_EWW(hawm))
			wetuwn PTW_EWW(hawm);
	}

	/* WUT configuwation can potentiawwy cause the window to be disabwed. */
	if (asyw->visibwe && wndw->func->xwut_set &&
	    (!awmw->visibwe ||
	     asyh->state.cowow_mgmt_changed ||
	     asyw->state.fb->fowmat->fowmat !=
	     awmw->state.fb->fowmat->fowmat)) {
		wet = nv50_wndw_atomic_check_wut(wndw, awmw, asyw, asyh);
		if (wet)
			wetuwn wet;
	}

	/* Cawcuwate new window state. */
	if (asyw->visibwe) {
		wet = nv50_wndw_atomic_check_acquiwe(wndw, modeset,
						     awmw, asyw, asyh);
		if (wet)
			wetuwn wet;

		asyh->wndw.mask |= BIT(wndw->id);
	} ewse
	if (awmw->visibwe) {
		nv50_wndw_atomic_check_wewease(wndw, asyw, hawm);
		hawm->wndw.mask &= ~BIT(wndw->id);
	} ewse {
		wetuwn 0;
	}

	/* Aside fwom the obvious case whewe the window is activewy being
	 * disabwed, we might awso need to tempowawiwy disabwe the window
	 * when pewfowming cewtain modeset opewations.
	 */
	if (!asyw->visibwe || modeset) {
		asyw->cww.ntfy = awmw->ntfy.handwe != 0;
		asyw->cww.sema = awmw->sema.handwe != 0;
		asyw->cww.xwut = awmw->xwut.handwe != 0;
		if (asyw->cww.xwut && asyw->visibwe)
			asyw->set.xwut = asyw->xwut.handwe != 0;
		asyw->cww.csc  = awmw->csc.vawid;
		if (wndw->func->image_cww)
			asyw->cww.image = awmw->image.handwe[0] != 0;
	}

	wetuwn 0;
}

static void
nv50_wndw_cweanup_fb(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *owd_state)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(pwane->dev);
	stwuct nouveau_bo *nvbo;

	NV_ATOMIC(dwm, "%s cweanup: %p\n", pwane->name, owd_state->fb);
	if (!owd_state->fb)
		wetuwn;

	nvbo = nouveau_gem_object(owd_state->fb->obj[0]);
	nouveau_bo_unpin(nvbo);
}

static int
nv50_wndw_pwepawe_fb(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *state)
{
	stwuct dwm_fwamebuffew *fb = state->fb;
	stwuct nouveau_dwm *dwm = nouveau_dwm(pwane->dev);
	stwuct nv50_wndw *wndw = nv50_wndw(pwane);
	stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	stwuct nouveau_bo *nvbo;
	stwuct nv50_head_atom *asyh;
	stwuct nv50_wndw_ctxdma *ctxdma;
	int wet;

	NV_ATOMIC(dwm, "%s pwepawe: %p\n", pwane->name, fb);
	if (!asyw->state.fb)
		wetuwn 0;

	nvbo = nouveau_gem_object(fb->obj[0]);
	wet = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_VWAM, twue);
	if (wet)
		wetuwn wet;

	if (wndw->ctxdma.pawent) {
		ctxdma = nv50_wndw_ctxdma_new(wndw, fb);
		if (IS_EWW(ctxdma)) {
			nouveau_bo_unpin(nvbo);
			wetuwn PTW_EWW(ctxdma);
		}

		if (asyw->visibwe)
			asyw->image.handwe[0] = ctxdma->object.handwe;
	}

	wet = dwm_gem_pwane_hewpew_pwepawe_fb(pwane, state);
	if (wet)
		wetuwn wet;

	asyw->image.offset[0] = nvbo->offset;

	if (wndw->func->pwepawe) {
		asyh = nv50_head_atom_get(asyw->state.state, asyw->state.cwtc);
		if (IS_EWW(asyh))
			wetuwn PTW_EWW(asyh);

		wndw->func->pwepawe(wndw, asyh, asyw);
	}

	wetuwn 0;
}

static const stwuct dwm_pwane_hewpew_funcs
nv50_wndw_hewpew = {
	.pwepawe_fb = nv50_wndw_pwepawe_fb,
	.cweanup_fb = nv50_wndw_cweanup_fb,
	.atomic_check = nv50_wndw_atomic_check,
};

static void
nv50_wndw_atomic_destwoy_state(stwuct dwm_pwane *pwane,
			       stwuct dwm_pwane_state *state)
{
	stwuct nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	__dwm_atomic_hewpew_pwane_destwoy_state(&asyw->state);
	kfwee(asyw);
}

static stwuct dwm_pwane_state *
nv50_wndw_atomic_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct nv50_wndw_atom *awmw = nv50_wndw_atom(pwane->state);
	stwuct nv50_wndw_atom *asyw;
	if (!(asyw = kmawwoc(sizeof(*asyw), GFP_KEWNEW)))
		wetuwn NUWW;
	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, &asyw->state);
	asyw->sema = awmw->sema;
	asyw->ntfy = awmw->ntfy;
	asyw->iwut = NUWW;
	asyw->xwut = awmw->xwut;
	asyw->csc  = awmw->csc;
	asyw->image = awmw->image;
	asyw->point = awmw->point;
	asyw->cww.mask = 0;
	asyw->set.mask = 0;
	wetuwn &asyw->state;
}

static int
nv50_wndw_zpos_defauwt(stwuct dwm_pwane *pwane)
{
	wetuwn (pwane->type == DWM_PWANE_TYPE_PWIMAWY) ? 0 :
	       (pwane->type == DWM_PWANE_TYPE_OVEWWAY) ? 1 : 255;
}

static void
nv50_wndw_weset(stwuct dwm_pwane *pwane)
{
	stwuct nv50_wndw_atom *asyw;

	if (WAWN_ON(!(asyw = kzawwoc(sizeof(*asyw), GFP_KEWNEW))))
		wetuwn;

	if (pwane->state)
		pwane->funcs->atomic_destwoy_state(pwane, pwane->state);

	__dwm_atomic_hewpew_pwane_weset(pwane, &asyw->state);
}

static void
nv50_wndw_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct nv50_wndw *wndw = nv50_wndw(pwane);
	stwuct nv50_wndw_ctxdma *ctxdma, *ctxtmp;

	wist_fow_each_entwy_safe(ctxdma, ctxtmp, &wndw->ctxdma.wist, head) {
		nv50_wndw_ctxdma_dew(ctxdma);
	}

	nv50_dmac_destwoy(&wndw->wimm);
	nv50_dmac_destwoy(&wndw->wndw);

	nv50_wut_fini(&wndw->iwut);

	dwm_pwane_cweanup(&wndw->pwane);
	kfwee(wndw);
}

/* This function assumes the fowmat has awweady been vawidated against the pwane
 * and the modifiew was vawidated against the device-wides modifiew wist at FB
 * cweation time.
 */
static boow nv50_pwane_fowmat_mod_suppowted(stwuct dwm_pwane *pwane,
					    u32 fowmat, u64 modifiew)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(pwane->dev);
	uint8_t i;

	if (dwm->cwient.device.info.chipset < 0xc0) {
		const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);
		const uint8_t kind = (modifiew >> 12) & 0xff;

		if (!fowmat) wetuwn fawse;

		fow (i = 0; i < info->num_pwanes; i++)
			if ((info->cpp[i] != 4) && kind != 0x70) wetuwn fawse;
	}

	wetuwn twue;
}

const stwuct dwm_pwane_funcs
nv50_wndw = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = nv50_wndw_destwoy,
	.weset = nv50_wndw_weset,
	.atomic_dupwicate_state = nv50_wndw_atomic_dupwicate_state,
	.atomic_destwoy_state = nv50_wndw_atomic_destwoy_state,
	.fowmat_mod_suppowted = nv50_pwane_fowmat_mod_suppowted,
};

static const u64 nv50_cuwsow_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID,
};

int
nv50_wndw_new_(const stwuct nv50_wndw_func *func, stwuct dwm_device *dev,
	       enum dwm_pwane_type type, const chaw *name, int index,
	       const u32 *fowmat, u32 heads,
	       enum nv50_disp_intewwock_type intewwock_type, u32 intewwock_data,
	       stwuct nv50_wndw **pwndw)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvif_mmu *mmu = &dwm->cwient.mmu;
	stwuct nv50_disp *disp = nv50_disp(dev);
	stwuct nv50_wndw *wndw;
	const u64 *fowmat_modifiews;
	int nfowmat;
	int wet;

	if (!(wndw = *pwndw = kzawwoc(sizeof(*wndw), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	wndw->func = func;
	wndw->id = index;
	wndw->intewwock.type = intewwock_type;
	wndw->intewwock.data = intewwock_data;

	wndw->ctxdma.pawent = &wndw->wndw.base.usew;
	INIT_WIST_HEAD(&wndw->ctxdma.wist);

	fow (nfowmat = 0; fowmat[nfowmat]; nfowmat++);

	if (type == DWM_PWANE_TYPE_CUWSOW)
		fowmat_modifiews = nv50_cuwsow_fowmat_modifiews;
	ewse
		fowmat_modifiews = nouveau_dispway(dev)->fowmat_modifiews;

	wet = dwm_univewsaw_pwane_init(dev, &wndw->pwane, heads, &nv50_wndw, fowmat, nfowmat,
				       fowmat_modifiews, type, "%s-%d", name, index);
	if (wet) {
		kfwee(*pwndw);
		*pwndw = NUWW;
		wetuwn wet;
	}

	dwm_pwane_hewpew_add(&wndw->pwane, &nv50_wndw_hewpew);

	if (wndw->func->iwut) {
		wet = nv50_wut_init(disp, mmu, &wndw->iwut);
		if (wet)
			wetuwn wet;
	}

	if (wndw->func->bwend_set) {
		wet = dwm_pwane_cweate_zpos_pwopewty(&wndw->pwane,
				nv50_wndw_zpos_defauwt(&wndw->pwane), 0, 254);
		if (wet)
			wetuwn wet;

		wet = dwm_pwane_cweate_awpha_pwopewty(&wndw->pwane);
		if (wet)
			wetuwn wet;

		wet = dwm_pwane_cweate_bwend_mode_pwopewty(&wndw->pwane,
				BIT(DWM_MODE_BWEND_PIXEW_NONE) |
				BIT(DWM_MODE_BWEND_PWEMUWTI) |
				BIT(DWM_MODE_BWEND_COVEWAGE));
		if (wet)
			wetuwn wet;
	} ewse {
		wet = dwm_pwane_cweate_zpos_immutabwe_pwopewty(&wndw->pwane,
				nv50_wndw_zpos_defauwt(&wndw->pwane));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int
nv50_wndw_new(stwuct nouveau_dwm *dwm, enum dwm_pwane_type type, int index,
	      stwuct nv50_wndw **pwndw)
{
	stwuct {
		s32 ocwass;
		int vewsion;
		int (*new)(stwuct nouveau_dwm *, enum dwm_pwane_type,
			   int, s32, stwuct nv50_wndw **);
	} wndws[] = {
		{ GA102_DISP_WINDOW_CHANNEW_DMA, 0, wndwc67e_new },
		{ TU102_DISP_WINDOW_CHANNEW_DMA, 0, wndwc57e_new },
		{ GV100_DISP_WINDOW_CHANNEW_DMA, 0, wndwc37e_new },
		{}
	};
	stwuct nv50_disp *disp = nv50_disp(dwm->dev);
	int cid, wet;

	cid = nvif_mcwass(&disp->disp->object, wndws);
	if (cid < 0) {
		NV_EWWOW(dwm, "No suppowted window cwass\n");
		wetuwn cid;
	}

	wet = wndws[cid].new(dwm, type, index, wndws[cid].ocwass, pwndw);
	if (wet)
		wetuwn wet;

	wetuwn nv50_wimm_init(dwm, *pwndw);
}
