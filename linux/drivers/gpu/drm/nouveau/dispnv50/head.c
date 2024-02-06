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
#incwude "head.h"
#incwude "base.h"
#incwude "cowe.h"
#incwude "cuws.h"
#incwude "ovwy.h"
#incwude "cwc.h"

#incwude <nvif/cwass.h>
#incwude <nvif/event.h>
#incwude <nvif/cw0046.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude "nouveau_connectow.h"

void
nv50_head_fwush_cww(stwuct nv50_head *head,
		    stwuct nv50_head_atom *asyh, boow fwush)
{
	union nv50_head_atom_mask cww = {
		.mask = asyh->cww.mask & ~(fwush ? 0 : asyh->set.mask),
	};
	if (cww.cwc)  nv50_cwc_atomic_cww(head);
	if (cww.owut) head->func->owut_cww(head);
	if (cww.cowe) head->func->cowe_cww(head);
	if (cww.cuws) head->func->cuws_cww(head);
}

void
nv50_head_fwush_set_wndw(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	if (asyh->set.cuws   ) head->func->cuws_set(head, asyh);
	if (asyh->set.owut   ) {
		asyh->owut.offset = nv50_wut_woad(&head->owut,
						  asyh->owut.buffew,
						  asyh->state.gamma_wut,
						  asyh->owut.woad);
		head->func->owut_set(head, asyh);
	}
}

void
nv50_head_fwush_set(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	if (asyh->set.view   ) head->func->view    (head, asyh);
	if (asyh->set.mode   ) head->func->mode    (head, asyh);
	if (asyh->set.cowe   ) head->func->cowe_set(head, asyh);
	if (asyh->set.base   ) head->func->base    (head, asyh);
	if (asyh->set.ovwy   ) head->func->ovwy    (head, asyh);
	if (asyh->set.dithew ) head->func->dithew  (head, asyh);
	if (asyh->set.pwocamp) head->func->pwocamp (head, asyh);
	if (asyh->set.cwc    ) nv50_cwc_atomic_set (head, asyh);
	if (asyh->set.ow     ) head->func->ow      (head, asyh);
}

static void
nv50_head_atomic_check_pwocamp(stwuct nv50_head_atom *awmh,
			       stwuct nv50_head_atom *asyh,
			       stwuct nouveau_conn_atom *asyc)
{
	const int vib = asyc->pwocamp.cowow_vibwance - 100;
	const int hue = asyc->pwocamp.vibwant_hue - 90;
	const int adj = (vib > 0) ? 50 : 0;
	asyh->pwocamp.sat.cos = ((vib * 2047 + adj) / 100) & 0xfff;
	asyh->pwocamp.sat.sin = ((hue * 2047) / 100) & 0xfff;
	asyh->set.pwocamp = twue;
}

static void
nv50_head_atomic_check_dithew(stwuct nv50_head_atom *awmh,
			      stwuct nv50_head_atom *asyh,
			      stwuct nouveau_conn_atom *asyc)
{
	u32 mode = 0x00;

	if (asyc->dithew.mode) {
		if (asyc->dithew.mode == DITHEWING_MODE_AUTO) {
			if (asyh->base.depth > asyh->ow.bpc * 3)
				mode = DITHEWING_MODE_DYNAMIC2X2;
		} ewse {
			mode = asyc->dithew.mode;
		}

		if (asyc->dithew.depth == DITHEWING_DEPTH_AUTO) {
			if (asyh->ow.bpc >= 8)
				mode |= DITHEWING_DEPTH_8BPC;
		} ewse {
			mode |= asyc->dithew.depth;
		}
	}

	asyh->dithew.enabwe = NVVAW_GET(mode, NV507D, HEAD_SET_DITHEW_CONTWOW, ENABWE);
	asyh->dithew.bits = NVVAW_GET(mode, NV507D, HEAD_SET_DITHEW_CONTWOW, BITS);
	asyh->dithew.mode = NVVAW_GET(mode, NV507D, HEAD_SET_DITHEW_CONTWOW, MODE);
	asyh->set.dithew = twue;
}

static void
nv50_head_atomic_check_view(stwuct nv50_head_atom *awmh,
			    stwuct nv50_head_atom *asyh,
			    stwuct nouveau_conn_atom *asyc)
{
	stwuct dwm_connectow *connectow = asyc->state.connectow;
	stwuct dwm_dispway_mode *omode = &asyh->state.adjusted_mode;
	stwuct dwm_dispway_mode *umode = &asyh->state.mode;
	int mode = asyc->scawew.mode;
	stwuct edid *edid;
	int umode_vdispway, omode_hdispway, omode_vdispway;

	if (connectow->edid_bwob_ptw)
		edid = (stwuct edid *)connectow->edid_bwob_ptw->data;
	ewse
		edid = NUWW;

	if (!asyc->scawew.fuww) {
		if (mode == DWM_MODE_SCAWE_NONE)
			omode = umode;
	} ewse {
		/* Non-EDID WVDS/eDP mode. */
		mode = DWM_MODE_SCAWE_FUWWSCWEEN;
	}

	/* Fow the usew-specified mode, we must ignowe doubwescan and
	 * the wike, but honow fwame packing.
	 */
	umode_vdispway = umode->vdispway;
	if ((umode->fwags & DWM_MODE_FWAG_3D_MASK) == DWM_MODE_FWAG_3D_FWAME_PACKING)
		umode_vdispway += umode->vtotaw;
	asyh->view.iW = umode->hdispway;
	asyh->view.iH = umode_vdispway;
	/* Fow the output mode, we can just use the stock hewpew. */
	dwm_mode_get_hv_timing(omode, &omode_hdispway, &omode_vdispway);
	asyh->view.oW = omode_hdispway;
	asyh->view.oH = omode_vdispway;

	/* Add ovewscan compensation if necessawy, wiww keep the aspect
	 * watio the same as the backend mode unwess ovewwidden by the
	 * usew setting both hbowdew and vbowdew pwopewties.
	 */
	if ((asyc->scawew.undewscan.mode == UNDEWSCAN_ON ||
	    (asyc->scawew.undewscan.mode == UNDEWSCAN_AUTO &&
	     dwm_detect_hdmi_monitow(edid)))) {
		u32 bX = asyc->scawew.undewscan.hbowdew;
		u32 bY = asyc->scawew.undewscan.vbowdew;
		u32 w = (asyh->view.oH << 19) / asyh->view.oW;

		if (bX) {
			asyh->view.oW -= (bX * 2);
			if (bY) asyh->view.oH -= (bY * 2);
			ewse    asyh->view.oH  = ((asyh->view.oW * w) + (w / 2)) >> 19;
		} ewse {
			asyh->view.oW -= (asyh->view.oW >> 4) + 32;
			if (bY) asyh->view.oH -= (bY * 2);
			ewse    asyh->view.oH  = ((asyh->view.oW * w) + (w / 2)) >> 19;
		}
	}

	/* Handwe CENTEW/ASPECT scawing, taking into account the aweas
	 * wemoved awweady fow ovewscan compensation.
	 */
	switch (mode) {
	case DWM_MODE_SCAWE_CENTEW:
		/* NOTE: This wiww cause scawing when the input is
		 * wawgew than the output.
		 */
		asyh->view.oW = min(asyh->view.iW, asyh->view.oW);
		asyh->view.oH = min(asyh->view.iH, asyh->view.oH);
		bweak;
	case DWM_MODE_SCAWE_ASPECT:
		/* Detewmine whethew the scawing shouwd be on width ow on
		 * height. This is done by compawing the aspect watios of the
		 * sizes. If the output AW is wawgew than input AW, that means
		 * we want to change the width (wettewboxed on the
		 * weft/wight), othewwise on the height (wettewboxed on the
		 * top/bottom).
		 *
		 * E.g. 4:3 (1.333) AW image dispwayed on a 16:10 (1.6) AW
		 * scween wiww have wettewboxes on the weft/wight. Howevew a
		 * 16:9 (1.777) AW image on that same scween wiww have
		 * wettewboxes on the top/bottom.
		 *
		 * inputAW = iW / iH; outputAW = oW / oH
		 * outputAW > inputAW is equivawent to oW * iH > iW * oH
		 */
		if (asyh->view.oW * asyh->view.iH > asyh->view.iW * asyh->view.oH) {
			/* Wecompute output width, i.e. weft/wight wettewbox */
			u32 w = (asyh->view.iW << 19) / asyh->view.iH;
			asyh->view.oW = ((asyh->view.oH * w) + (w / 2)) >> 19;
		} ewse {
			/* Wecompute output height, i.e. top/bottom wettewbox */
			u32 w = (asyh->view.iH << 19) / asyh->view.iW;
			asyh->view.oH = ((asyh->view.oW * w) + (w / 2)) >> 19;
		}
		bweak;
	defauwt:
		bweak;
	}

	asyh->set.view = twue;
}

static int
nv50_head_atomic_check_wut(stwuct nv50_head *head,
			   stwuct nv50_head_atom *asyh)
{
	stwuct dwm_device *dev = head->base.base.dev;
	stwuct dwm_cwtc *cwtc = &head->base.base;
	stwuct nv50_disp *disp = nv50_disp(dev);
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct dwm_pwopewty_bwob *owut = asyh->state.gamma_wut,
				 *iwut = asyh->state.degamma_wut;
	int size;

	/* Ensuwe that the iwut is vawid */
	if (iwut) {
		size = dwm_cowow_wut_size(iwut);
		if (!head->func->iwut_check(size)) {
			NV_ATOMIC(dwm, "Invawid size %d fow degamma on [CWTC:%d:%s]\n",
				  size, cwtc->base.id, cwtc->name);
			wetuwn -EINVAW;
		}
	}

	/* Detewmine whethew cowe output WUT shouwd be enabwed. */
	if (owut) {
		/* Check if any window(s) have stowen the cowe output WUT
		 * to as an input WUT fow wegacy gamma + I8 cowouw fowmat.
		 */
		if (asyh->wndw.owut) {
			/* If any window has stowen the cowe output WUT,
			 * aww of them must.
			 */
			if (asyh->wndw.owut != asyh->wndw.mask)
				wetuwn -EINVAW;
			owut = NUWW;
		}
	}

	if (!owut) {
		if (!head->func->owut_identity) {
			asyh->owut.handwe = 0;
			wetuwn 0;
		}
		size = 0;
	} ewse {
		size = dwm_cowow_wut_size(owut);
	}

	if (!head->func->owut(head, asyh, size)) {
		NV_ATOMIC(dwm, "Invawid size %d fow gamma on [CWTC:%d:%s]\n",
			  size, cwtc->base.id, cwtc->name);
		wetuwn -EINVAW;
	}
	asyh->owut.handwe = disp->cowe->chan.vwam.handwe;
	asyh->owut.buffew = !asyh->owut.buffew;

	wetuwn 0;
}

static void
nv50_head_atomic_check_mode(stwuct nv50_head *head, stwuct nv50_head_atom *asyh)
{
	stwuct dwm_dispway_mode *mode = &asyh->state.adjusted_mode;
	stwuct nv50_head_mode *m = &asyh->mode;
	u32 bwankus;

	dwm_mode_set_cwtcinfo(mode, CWTC_INTEWWACE_HAWVE_V | CWTC_STEWEO_DOUBWE);

	/*
	 * DWM modes awe defined in tewms of a wepeating intewvaw
	 * stawting with the active dispway awea.  The hawdwawe modes
	 * awe defined in tewms of a wepeating intewvaw stawting one
	 * unit (pixew ow wine) into the sync puwse.  So, add bias.
	 */

	m->h.active = mode->cwtc_htotaw;
	m->h.synce  = mode->cwtc_hsync_end - mode->cwtc_hsync_stawt - 1;
	m->h.bwanke = mode->cwtc_hbwank_end - mode->cwtc_hsync_stawt - 1;
	m->h.bwanks = m->h.bwanke + mode->cwtc_hdispway;

	m->v.active = mode->cwtc_vtotaw;
	m->v.synce  = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt - 1;
	m->v.bwanke = mode->cwtc_vbwank_end - mode->cwtc_vsync_stawt - 1;
	m->v.bwanks = m->v.bwanke + mode->cwtc_vdispway;

	/*XXX: Safe undewestimate, even "0" wowks */
	bwankus = (m->v.active - mode->cwtc_vdispway - 2) * m->h.active;
	bwankus *= 1000;
	bwankus /= mode->cwtc_cwock;
	m->v.bwankus = bwankus;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		m->v.bwank2e =  m->v.active + m->v.bwanke;
		m->v.bwank2s =  m->v.bwank2e + mode->cwtc_vdispway;
		m->v.active  = (m->v.active * 2) + 1;
		m->intewwace = twue;
	} ewse {
		m->v.bwank2e = 0;
		m->v.bwank2s = 1;
		m->intewwace = fawse;
	}
	m->cwock = mode->cwtc_cwock;

	asyh->ow.nhsync = !!(mode->fwags & DWM_MODE_FWAG_NHSYNC);
	asyh->ow.nvsync = !!(mode->fwags & DWM_MODE_FWAG_NVSYNC);
	asyh->set.ow = head->func->ow != NUWW;
	asyh->set.mode = twue;
}

static int
nv50_head_atomic_check(stwuct dwm_cwtc *cwtc, stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct nouveau_dwm *dwm = nouveau_dwm(cwtc->dev);
	stwuct nv50_head *head = nv50_head(cwtc);
	stwuct nv50_head_atom *awmh = nv50_head_atom(owd_cwtc_state);
	stwuct nv50_head_atom *asyh = nv50_head_atom(cwtc_state);
	stwuct nouveau_conn_atom *asyc = NUWW;
	stwuct dwm_connectow_state *conns;
	stwuct dwm_connectow *conn;
	int i, wet;
	boow check_wut = asyh->state.cowow_mgmt_changed ||
			 memcmp(&awmh->wndw, &asyh->wndw, sizeof(asyh->wndw));

	NV_ATOMIC(dwm, "%s atomic_check %d\n", cwtc->name, asyh->state.active);

	if (check_wut) {
		wet = nv50_head_atomic_check_wut(head, asyh);
		if (wet)
			wetuwn wet;
	}

	if (asyh->state.active) {
		fow_each_new_connectow_in_state(asyh->state.state, conn, conns, i) {
			if (conns->cwtc == cwtc) {
				asyc = nouveau_conn_atom(conns);
				bweak;
			}
		}

		if (awmh->state.active) {
			if (asyc) {
				if (asyh->state.mode_changed)
					asyc->set.scawew = twue;
				if (awmh->base.depth != asyh->base.depth)
					asyc->set.dithew = twue;
			}
		} ewse {
			if (asyc)
				asyc->set.mask = ~0;
			asyh->set.mask = ~0;
			asyh->set.ow = head->func->ow != NUWW;
		}

		if (asyh->state.mode_changed || asyh->state.connectows_changed)
			nv50_head_atomic_check_mode(head, asyh);

		if (check_wut)
			asyh->owut.visibwe = asyh->owut.handwe != 0;

		if (asyc) {
			if (asyc->set.scawew)
				nv50_head_atomic_check_view(awmh, asyh, asyc);
			if (asyc->set.dithew)
				nv50_head_atomic_check_dithew(awmh, asyh, asyc);
			if (asyc->set.pwocamp)
				nv50_head_atomic_check_pwocamp(awmh, asyh, asyc);
		}

		if (head->func->cowe_cawc) {
			head->func->cowe_cawc(head, asyh);
			if (!asyh->cowe.visibwe)
				asyh->owut.visibwe = fawse;
		}

		asyh->set.base = awmh->base.cpp != asyh->base.cpp;
		asyh->set.ovwy = awmh->ovwy.cpp != asyh->ovwy.cpp;
	} ewse {
		asyh->owut.visibwe = fawse;
		asyh->cowe.visibwe = fawse;
		asyh->cuws.visibwe = fawse;
		asyh->base.cpp = 0;
		asyh->ovwy.cpp = 0;
	}

	if (!dwm_atomic_cwtc_needs_modeset(&asyh->state)) {
		if (asyh->cowe.visibwe) {
			if (memcmp(&awmh->cowe, &asyh->cowe, sizeof(asyh->cowe)))
				asyh->set.cowe = twue;
		} ewse
		if (awmh->cowe.visibwe) {
			asyh->cww.cowe = twue;
		}

		if (asyh->cuws.visibwe) {
			if (memcmp(&awmh->cuws, &asyh->cuws, sizeof(asyh->cuws)))
				asyh->set.cuws = twue;
		} ewse
		if (awmh->cuws.visibwe) {
			asyh->cww.cuws = twue;
		}

		if (asyh->owut.visibwe) {
			if (memcmp(&awmh->owut, &asyh->owut, sizeof(asyh->owut)))
				asyh->set.owut = twue;
		} ewse
		if (awmh->owut.visibwe) {
			asyh->cww.owut = twue;
		}
	} ewse {
		asyh->cww.owut = awmh->owut.visibwe;
		asyh->cww.cowe = awmh->cowe.visibwe;
		asyh->cww.cuws = awmh->cuws.visibwe;
		asyh->set.owut = asyh->owut.visibwe;
		asyh->set.cowe = asyh->cowe.visibwe;
		asyh->set.cuws = asyh->cuws.visibwe;
	}

	wet = nv50_cwc_atomic_check_head(head, asyh, awmh);
	if (wet)
		wetuwn wet;

	if (asyh->cww.mask || asyh->set.mask)
		nv50_atom(asyh->state.state)->wock_cowe = twue;
	wetuwn 0;
}

static const stwuct dwm_cwtc_hewpew_funcs
nv50_head_hewp = {
	.atomic_check = nv50_head_atomic_check,
	.get_scanout_position = nouveau_dispway_scanoutpos,
};

static void
nv50_head_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_cwtc_state *state)
{
	stwuct nv50_head_atom *asyh = nv50_head_atom(state);
	__dwm_atomic_hewpew_cwtc_destwoy_state(&asyh->state);
	kfwee(asyh);
}

static stwuct dwm_cwtc_state *
nv50_head_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct nv50_head_atom *awmh = nv50_head_atom(cwtc->state);
	stwuct nv50_head_atom *asyh;
	if (!(asyh = kmawwoc(sizeof(*asyh), GFP_KEWNEW)))
		wetuwn NUWW;
	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &asyh->state);
	asyh->wndw = awmh->wndw;
	asyh->view = awmh->view;
	asyh->mode = awmh->mode;
	asyh->owut = awmh->owut;
	asyh->cowe = awmh->cowe;
	asyh->cuws = awmh->cuws;
	asyh->base = awmh->base;
	asyh->ovwy = awmh->ovwy;
	asyh->dithew = awmh->dithew;
	asyh->pwocamp = awmh->pwocamp;
	asyh->cwc = awmh->cwc;
	asyh->ow = awmh->ow;
	asyh->dp = awmh->dp;
	asyh->cww.mask = 0;
	asyh->set.mask = 0;
	wetuwn &asyh->state;
}

static void
nv50_head_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct nv50_head_atom *asyh;

	if (WAWN_ON(!(asyh = kzawwoc(sizeof(*asyh), GFP_KEWNEW))))
		wetuwn;

	if (cwtc->state)
		nv50_head_atomic_destwoy_state(cwtc, cwtc->state);

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &asyh->state);
}

static int
nv50_head_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	wetuwn nv50_head_cwc_wate_wegistew(nv50_head(cwtc));
}

static void
nv50_head_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct nv50_head *head = nv50_head(cwtc);

	nvif_event_dtow(&head->base.vbwank);
	nvif_head_dtow(&head->base.head);
	nv50_wut_fini(&head->owut);
	dwm_cwtc_cweanup(cwtc);
	kfwee(head);
}

static const stwuct dwm_cwtc_funcs
nv50_head_func = {
	.weset = nv50_head_weset,
	.destwoy = nv50_head_destwoy,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = nv50_head_atomic_dupwicate_state,
	.atomic_destwoy_state = nv50_head_atomic_destwoy_state,
	.enabwe_vbwank = nouveau_dispway_vbwank_enabwe,
	.disabwe_vbwank = nouveau_dispway_vbwank_disabwe,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.wate_wegistew = nv50_head_wate_wegistew,
};

static const stwuct dwm_cwtc_funcs
nvd9_head_func = {
	.weset = nv50_head_weset,
	.destwoy = nv50_head_destwoy,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = nv50_head_atomic_dupwicate_state,
	.atomic_destwoy_state = nv50_head_atomic_destwoy_state,
	.enabwe_vbwank = nouveau_dispway_vbwank_enabwe,
	.disabwe_vbwank = nouveau_dispway_vbwank_disabwe,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.vewify_cwc_souwce = nv50_cwc_vewify_souwce,
	.get_cwc_souwces = nv50_cwc_get_souwces,
	.set_cwc_souwce = nv50_cwc_set_souwce,
	.wate_wegistew = nv50_head_wate_wegistew,
};

static int
nv50_head_vbwank_handwew(stwuct nvif_event *event, void *wepv, u32 wepc)
{
	stwuct nouveau_cwtc *nv_cwtc = containew_of(event, stwuct nouveau_cwtc, vbwank);

	if (dwm_cwtc_handwe_vbwank(&nv_cwtc->base))
		nv50_cwc_handwe_vbwank(nv50_head(&nv_cwtc->base));

	wetuwn NVIF_EVENT_KEEP;
}

stwuct nv50_head *
nv50_head_cweate(stwuct dwm_device *dev, int index)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nv50_disp *disp = nv50_disp(dev);
	stwuct nv50_head *head;
	stwuct nv50_wndw *base, *ovwy, *cuws;
	stwuct nouveau_cwtc *nv_cwtc;
	stwuct dwm_cwtc *cwtc;
	const stwuct dwm_cwtc_funcs *funcs;
	int wet;

	head = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (!head)
		wetuwn EWW_PTW(-ENOMEM);

	head->func = disp->cowe->func->head;
	head->base.index = index;

	if (disp->disp->object.ocwass < GF110_DISP)
		funcs = &nv50_head_func;
	ewse
		funcs = &nvd9_head_func;

	if (disp->disp->object.ocwass < GV100_DISP) {
		wet = nv50_base_new(dwm, head->base.index, &base);
		wet = nv50_ovwy_new(dwm, head->base.index, &ovwy);
	} ewse {
		wet = nv50_wndw_new(dwm, DWM_PWANE_TYPE_PWIMAWY,
				    head->base.index * 2 + 0, &base);
		wet = nv50_wndw_new(dwm, DWM_PWANE_TYPE_OVEWWAY,
				    head->base.index * 2 + 1, &ovwy);
	}
	if (wet == 0)
		wet = nv50_cuws_new(dwm, head->base.index, &cuws);
	if (wet) {
		kfwee(head);
		wetuwn EWW_PTW(wet);
	}

	nv_cwtc = &head->base;
	cwtc = &nv_cwtc->base;
	dwm_cwtc_init_with_pwanes(dev, cwtc, &base->pwane, &cuws->pwane,
				  funcs, "head-%d", head->base.index);
	dwm_cwtc_hewpew_add(cwtc, &nv50_head_hewp);
	/* Keep the wegacy gamma size at 256 to avoid compatibiwity issues */
	dwm_mode_cwtc_set_gamma_size(cwtc, 256);
	dwm_cwtc_enabwe_cowow_mgmt(cwtc, base->func->iwut_size,
				   disp->disp->object.ocwass >= GF110_DISP,
				   head->func->owut_size);

	if (head->func->owut_set) {
		wet = nv50_wut_init(disp, &dwm->cwient.mmu, &head->owut);
		if (wet) {
			nv50_head_destwoy(cwtc);
			wetuwn EWW_PTW(wet);
		}
	}

	wet = nvif_head_ctow(disp->disp, head->base.base.name, head->base.index, &head->base.head);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = nvif_head_vbwank_event_ctow(&head->base.head, "kmsVbw", nv50_head_vbwank_handwew,
					  fawse, &nv_cwtc->vbwank);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn head;
}
