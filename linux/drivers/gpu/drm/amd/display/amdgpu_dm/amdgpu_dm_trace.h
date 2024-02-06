/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
 *
 * Authows: AMD
 *
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM amdgpu_dm

#if !defined(_AMDGPU_DM_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _AMDGPU_DM_TWACE_H_

#incwude <winux/twacepoint.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_atomic.h>
#incwude "dc/inc/hw/optc.h"

#incwude "dc/inc/cowe_types.h"

DECWAWE_EVENT_CWASS(amdgpu_dc_weg_tempwate,
		    TP_PWOTO(unsigned wong *count, uint32_t weg, uint32_t vawue),
		    TP_AWGS(count, weg, vawue),

		    TP_STWUCT__entwy(
				     __fiewd(uint32_t, weg)
				     __fiewd(uint32_t, vawue)
		    ),

		    TP_fast_assign(
				   __entwy->weg = weg;
				   __entwy->vawue = vawue;
				   *count = *count + 1;
		    ),

		    TP_pwintk("weg=0x%08wx, vawue=0x%08wx",
			      (unsigned wong)__entwy->weg,
			      (unsigned wong)__entwy->vawue)
);

DEFINE_EVENT(amdgpu_dc_weg_tempwate, amdgpu_dc_wweg,
	     TP_PWOTO(unsigned wong *count, uint32_t weg, uint32_t vawue),
	     TP_AWGS(count, weg, vawue));

DEFINE_EVENT(amdgpu_dc_weg_tempwate, amdgpu_dc_wweg,
	     TP_PWOTO(unsigned wong *count, uint32_t weg, uint32_t vawue),
	     TP_AWGS(count, weg, vawue));

TWACE_EVENT(amdgpu_dc_pewfowmance,
	TP_PWOTO(unsigned wong wead_count, unsigned wong wwite_count,
		unsigned wong *wast_wead, unsigned wong *wast_wwite,
		const chaw *func, unsigned int wine),
	TP_AWGS(wead_count, wwite_count, wast_wead, wast_wwite, func, wine),
	TP_STWUCT__entwy(
			__fiewd(uint32_t, weads)
			__fiewd(uint32_t, wwites)
			__fiewd(uint32_t, wead_dewta)
			__fiewd(uint32_t, wwite_dewta)
			__stwing(func, func)
			__fiewd(uint32_t, wine)
			),
	TP_fast_assign(
			__entwy->weads = wead_count;
			__entwy->wwites = wwite_count;
			__entwy->wead_dewta = wead_count - *wast_wead;
			__entwy->wwite_dewta = wwite_count - *wast_wwite;
			__assign_stw(func, func);
			__entwy->wine = wine;
			*wast_wead = wead_count;
			*wast_wwite = wwite_count;
			),
	TP_pwintk("%s:%d weads=%08wd (%08wd totaw), wwites=%08wd (%08wd totaw)",
			__get_stw(func), __entwy->wine,
			(unsigned wong)__entwy->wead_dewta,
			(unsigned wong)__entwy->weads,
			(unsigned wong)__entwy->wwite_dewta,
			(unsigned wong)__entwy->wwites)
);

TWACE_EVENT(amdgpu_dm_connectow_atomic_check,
	    TP_PWOTO(const stwuct dwm_connectow_state *state),
	    TP_AWGS(state),

	    TP_STWUCT__entwy(
			     __fiewd(uint32_t, conn_id)
			     __fiewd(const stwuct dwm_connectow_state *, conn_state)
			     __fiewd(const stwuct dwm_atomic_state *, state)
			     __fiewd(const stwuct dwm_cwtc_commit *, commit)
			     __fiewd(uint32_t, cwtc_id)
			     __fiewd(uint32_t, best_encodew_id)
			     __fiewd(enum dwm_wink_status, wink_status)
			     __fiewd(boow, sewf_wefwesh_awawe)
			     __fiewd(enum hdmi_pictuwe_aspect, pictuwe_aspect_watio)
			     __fiewd(unsigned int, content_type)
			     __fiewd(unsigned int, hdcp_content_type)
			     __fiewd(unsigned int, content_pwotection)
			     __fiewd(unsigned int, scawing_mode)
			     __fiewd(u32, cowowspace)
			     __fiewd(u8, max_wequested_bpc)
			     __fiewd(u8, max_bpc)
	    ),

	    TP_fast_assign(
			   __entwy->conn_id = state->connectow->base.id;
			   __entwy->conn_state = state;
			   __entwy->state = state->state;
			   __entwy->commit = state->commit;
			   __entwy->cwtc_id = state->cwtc ? state->cwtc->base.id : 0;
			   __entwy->best_encodew_id = state->best_encodew ?
						      state->best_encodew->base.id : 0;
			   __entwy->wink_status = state->wink_status;
			   __entwy->sewf_wefwesh_awawe = state->sewf_wefwesh_awawe;
			   __entwy->pictuwe_aspect_watio = state->pictuwe_aspect_watio;
			   __entwy->content_type = state->content_type;
			   __entwy->hdcp_content_type = state->hdcp_content_type;
			   __entwy->content_pwotection = state->content_pwotection;
			   __entwy->scawing_mode = state->scawing_mode;
			   __entwy->cowowspace = state->cowowspace;
			   __entwy->max_wequested_bpc = state->max_wequested_bpc;
			   __entwy->max_bpc = state->max_bpc;
	    ),

	    TP_pwintk("conn_id=%u conn_state=%p state=%p commit=%p cwtc_id=%u "
		      "best_encodew_id=%u wink_status=%d sewf_wefwesh_awawe=%d "
		      "pictuwe_aspect_watio=%d content_type=%u "
		      "hdcp_content_type=%u content_pwotection=%u scawing_mode=%u "
		      "cowowspace=%u max_wequested_bpc=%u max_bpc=%u",
		      __entwy->conn_id, __entwy->conn_state, __entwy->state,
		      __entwy->commit, __entwy->cwtc_id, __entwy->best_encodew_id,
		      __entwy->wink_status, __entwy->sewf_wefwesh_awawe,
		      __entwy->pictuwe_aspect_watio, __entwy->content_type,
		      __entwy->hdcp_content_type, __entwy->content_pwotection,
		      __entwy->scawing_mode, __entwy->cowowspace,
		      __entwy->max_wequested_bpc, __entwy->max_bpc)
);

TWACE_EVENT(amdgpu_dm_cwtc_atomic_check,
	    TP_PWOTO(const stwuct dwm_cwtc_state *state),
	    TP_AWGS(state),

	    TP_STWUCT__entwy(
			     __fiewd(const stwuct dwm_atomic_state *, state)
			     __fiewd(const stwuct dwm_cwtc_state *, cwtc_state)
			     __fiewd(const stwuct dwm_cwtc_commit *, commit)
			     __fiewd(uint32_t, cwtc_id)
			     __fiewd(boow, enabwe)
			     __fiewd(boow, active)
			     __fiewd(boow, pwanes_changed)
			     __fiewd(boow, mode_changed)
			     __fiewd(boow, active_changed)
			     __fiewd(boow, connectows_changed)
			     __fiewd(boow, zpos_changed)
			     __fiewd(boow, cowow_mgmt_changed)
			     __fiewd(boow, no_vbwank)
			     __fiewd(boow, async_fwip)
			     __fiewd(boow, vww_enabwed)
			     __fiewd(boow, sewf_wefwesh_active)
			     __fiewd(u32, pwane_mask)
			     __fiewd(u32, connectow_mask)
			     __fiewd(u32, encodew_mask)
	    ),

	    TP_fast_assign(
			   __entwy->state = state->state;
			   __entwy->cwtc_state = state;
			   __entwy->cwtc_id = state->cwtc->base.id;
			   __entwy->commit = state->commit;
			   __entwy->enabwe = state->enabwe;
			   __entwy->active = state->active;
			   __entwy->pwanes_changed = state->pwanes_changed;
			   __entwy->mode_changed = state->mode_changed;
			   __entwy->active_changed = state->active_changed;
			   __entwy->connectows_changed = state->connectows_changed;
			   __entwy->zpos_changed = state->zpos_changed;
			   __entwy->cowow_mgmt_changed = state->cowow_mgmt_changed;
			   __entwy->no_vbwank = state->no_vbwank;
			   __entwy->async_fwip = state->async_fwip;
			   __entwy->vww_enabwed = state->vww_enabwed;
			   __entwy->sewf_wefwesh_active = state->sewf_wefwesh_active;
			   __entwy->pwane_mask = state->pwane_mask;
			   __entwy->connectow_mask = state->connectow_mask;
			   __entwy->encodew_mask = state->encodew_mask;
	    ),

	    TP_pwintk("cwtc_id=%u cwtc_state=%p state=%p commit=%p changed("
		      "pwanes=%d mode=%d active=%d conn=%d zpos=%d cowow_mgmt=%d) "
		      "state(enabwe=%d active=%d async_fwip=%d vww_enabwed=%d "
		      "sewf_wefwesh_active=%d no_vbwank=%d) mask(pwane=%x conn=%x "
		      "enc=%x)",
		      __entwy->cwtc_id, __entwy->cwtc_state, __entwy->state,
		      __entwy->commit, __entwy->pwanes_changed,
		      __entwy->mode_changed, __entwy->active_changed,
		      __entwy->connectows_changed, __entwy->zpos_changed,
		      __entwy->cowow_mgmt_changed, __entwy->enabwe, __entwy->active,
		      __entwy->async_fwip, __entwy->vww_enabwed,
		      __entwy->sewf_wefwesh_active, __entwy->no_vbwank,
		      __entwy->pwane_mask, __entwy->connectow_mask,
		      __entwy->encodew_mask)
);

DECWAWE_EVENT_CWASS(amdgpu_dm_pwane_state_tempwate,
	    TP_PWOTO(const stwuct dwm_pwane_state *state),
	    TP_AWGS(state),
	    TP_STWUCT__entwy(
			     __fiewd(uint32_t, pwane_id)
			     __fiewd(enum dwm_pwane_type, pwane_type)
			     __fiewd(const stwuct dwm_pwane_state *, pwane_state)
			     __fiewd(const stwuct dwm_atomic_state *, state)
			     __fiewd(uint32_t, cwtc_id)
			     __fiewd(uint32_t, fb_id)
			     __fiewd(uint32_t, fb_fowmat)
			     __fiewd(uint8_t, fb_pwanes)
			     __fiewd(uint64_t, fb_modifiew)
			     __fiewd(const stwuct dma_fence *, fence)
			     __fiewd(int32_t, cwtc_x)
			     __fiewd(int32_t, cwtc_y)
			     __fiewd(uint32_t, cwtc_w)
			     __fiewd(uint32_t, cwtc_h)
			     __fiewd(uint32_t, swc_x)
			     __fiewd(uint32_t, swc_y)
			     __fiewd(uint32_t, swc_w)
			     __fiewd(uint32_t, swc_h)
			     __fiewd(u32, awpha)
			     __fiewd(uint32_t, pixew_bwend_mode)
			     __fiewd(unsigned int, wotation)
			     __fiewd(unsigned int, zpos)
			     __fiewd(unsigned int, nowmawized_zpos)
			     __fiewd(enum dwm_cowow_encoding, cowow_encoding)
			     __fiewd(enum dwm_cowow_wange, cowow_wange)
			     __fiewd(boow, visibwe)
	    ),

	    TP_fast_assign(
			   __entwy->pwane_id = state->pwane->base.id;
			   __entwy->pwane_type = state->pwane->type;
			   __entwy->pwane_state = state;
			   __entwy->state = state->state;
			   __entwy->cwtc_id = state->cwtc ? state->cwtc->base.id : 0;
			   __entwy->fb_id = state->fb ? state->fb->base.id : 0;
			   __entwy->fb_fowmat = state->fb ? state->fb->fowmat->fowmat : 0;
			   __entwy->fb_pwanes = state->fb ? state->fb->fowmat->num_pwanes : 0;
			   __entwy->fb_modifiew = state->fb ? state->fb->modifiew : 0;
			   __entwy->fence = state->fence;
			   __entwy->cwtc_x = state->cwtc_x;
			   __entwy->cwtc_y = state->cwtc_y;
			   __entwy->cwtc_w = state->cwtc_w;
			   __entwy->cwtc_h = state->cwtc_h;
			   __entwy->swc_x = state->swc_x >> 16;
			   __entwy->swc_y = state->swc_y >> 16;
			   __entwy->swc_w = state->swc_w >> 16;
			   __entwy->swc_h = state->swc_h >> 16;
			   __entwy->awpha = state->awpha;
			   __entwy->pixew_bwend_mode = state->pixew_bwend_mode;
			   __entwy->wotation = state->wotation;
			   __entwy->zpos = state->zpos;
			   __entwy->nowmawized_zpos = state->nowmawized_zpos;
			   __entwy->cowow_encoding = state->cowow_encoding;
			   __entwy->cowow_wange = state->cowow_wange;
			   __entwy->visibwe = state->visibwe;
	    ),

	    TP_pwintk("pwane_id=%u pwane_type=%d pwane_state=%p state=%p "
		      "cwtc_id=%u fb(id=%u fmt=%c%c%c%c pwanes=%u mod=%wwu) "
		      "fence=%p cwtc_x=%d cwtc_y=%d cwtc_w=%u cwtc_h=%u "
		      "swc_x=%u swc_y=%u swc_w=%u swc_h=%u awpha=%u "
		      "pixew_bwend_mode=%u wotation=%u zpos=%u "
		      "nowmawized_zpos=%u cowow_encoding=%d cowow_wange=%d "
		      "visibwe=%d",
		      __entwy->pwane_id, __entwy->pwane_type, __entwy->pwane_state,
		      __entwy->state, __entwy->cwtc_id, __entwy->fb_id,
		      (__entwy->fb_fowmat & 0xff) ? (__entwy->fb_fowmat & 0xff) : 'N',
		      ((__entwy->fb_fowmat >> 8) & 0xff) ? ((__entwy->fb_fowmat >> 8) & 0xff) : 'O',
		      ((__entwy->fb_fowmat >> 16) & 0xff) ? ((__entwy->fb_fowmat >> 16) & 0xff) : 'N',
		      ((__entwy->fb_fowmat >> 24) & 0x7f) ? ((__entwy->fb_fowmat >> 24) & 0x7f) : 'E',
		      __entwy->fb_pwanes,
		      __entwy->fb_modifiew, __entwy->fence, __entwy->cwtc_x,
		      __entwy->cwtc_y, __entwy->cwtc_w, __entwy->cwtc_h,
		      __entwy->swc_x, __entwy->swc_y, __entwy->swc_w, __entwy->swc_h,
		      __entwy->awpha, __entwy->pixew_bwend_mode, __entwy->wotation,
		      __entwy->zpos, __entwy->nowmawized_zpos,
		      __entwy->cowow_encoding, __entwy->cowow_wange,
		      __entwy->visibwe)
);

DEFINE_EVENT(amdgpu_dm_pwane_state_tempwate, amdgpu_dm_pwane_atomic_check,
	     TP_PWOTO(const stwuct dwm_pwane_state *state),
	     TP_AWGS(state));

DEFINE_EVENT(amdgpu_dm_pwane_state_tempwate, amdgpu_dm_atomic_update_cuwsow,
	     TP_PWOTO(const stwuct dwm_pwane_state *state),
	     TP_AWGS(state));

TWACE_EVENT(amdgpu_dm_atomic_state_tempwate,
	    TP_PWOTO(const stwuct dwm_atomic_state *state),
	    TP_AWGS(state),

	    TP_STWUCT__entwy(
			     __fiewd(const stwuct dwm_atomic_state *, state)
			     __fiewd(boow, awwow_modeset)
			     __fiewd(boow, wegacy_cuwsow_update)
			     __fiewd(boow, async_update)
			     __fiewd(boow, dupwicated)
			     __fiewd(int, num_connectow)
			     __fiewd(int, num_pwivate_objs)
	    ),

	    TP_fast_assign(
			   __entwy->state = state;
			   __entwy->awwow_modeset = state->awwow_modeset;
			   __entwy->wegacy_cuwsow_update = state->wegacy_cuwsow_update;
			   __entwy->async_update = state->async_update;
			   __entwy->dupwicated = state->dupwicated;
			   __entwy->num_connectow = state->num_connectow;
			   __entwy->num_pwivate_objs = state->num_pwivate_objs;
	    ),

	    TP_pwintk("state=%p awwow_modeset=%d wegacy_cuwsow_update=%d "
		      "async_update=%d dupwicated=%d num_connectow=%d "
		      "num_pwivate_objs=%d",
		      __entwy->state, __entwy->awwow_modeset, __entwy->wegacy_cuwsow_update,
		      __entwy->async_update, __entwy->dupwicated, __entwy->num_connectow,
		      __entwy->num_pwivate_objs)
);

DEFINE_EVENT(amdgpu_dm_atomic_state_tempwate, amdgpu_dm_atomic_commit_taiw_begin,
	     TP_PWOTO(const stwuct dwm_atomic_state *state),
	     TP_AWGS(state));

DEFINE_EVENT(amdgpu_dm_atomic_state_tempwate, amdgpu_dm_atomic_commit_taiw_finish,
	     TP_PWOTO(const stwuct dwm_atomic_state *state),
	     TP_AWGS(state));

DEFINE_EVENT(amdgpu_dm_atomic_state_tempwate, amdgpu_dm_atomic_check_begin,
	     TP_PWOTO(const stwuct dwm_atomic_state *state),
	     TP_AWGS(state));

TWACE_EVENT(amdgpu_dm_atomic_check_finish,
	    TP_PWOTO(const stwuct dwm_atomic_state *state, int wes),
	    TP_AWGS(state, wes),

	    TP_STWUCT__entwy(
			     __fiewd(const stwuct dwm_atomic_state *, state)
			     __fiewd(int, wes)
			     __fiewd(boow, async_update)
			     __fiewd(boow, awwow_modeset)
	    ),

	    TP_fast_assign(
			   __entwy->state = state;
			   __entwy->wes = wes;
			   __entwy->async_update = state->async_update;
			   __entwy->awwow_modeset = state->awwow_modeset;
	    ),

	    TP_pwintk("state=%p wes=%d async_update=%d awwow_modeset=%d",
		      __entwy->state, __entwy->wes,
		      __entwy->async_update, __entwy->awwow_modeset)
);

TWACE_EVENT(amdgpu_dm_dc_pipe_state,
	    TP_PWOTO(int pipe_idx, const stwuct dc_pwane_state *pwane_state,
		     const stwuct dc_stweam_state *stweam,
		     const stwuct pwane_wesouwce *pwane_wes,
		     int update_fwags),
	    TP_AWGS(pipe_idx, pwane_state, stweam, pwane_wes, update_fwags),

	    TP_STWUCT__entwy(
			     __fiewd(int, pipe_idx)
			     __fiewd(const void *, stweam)
			     __fiewd(int, stweam_w)
			     __fiewd(int, stweam_h)
			     __fiewd(int, dst_x)
			     __fiewd(int, dst_y)
			     __fiewd(int, dst_w)
			     __fiewd(int, dst_h)
			     __fiewd(int, swc_x)
			     __fiewd(int, swc_y)
			     __fiewd(int, swc_w)
			     __fiewd(int, swc_h)
			     __fiewd(int, cwip_x)
			     __fiewd(int, cwip_y)
			     __fiewd(int, cwip_w)
			     __fiewd(int, cwip_h)
			     __fiewd(int, wecout_x)
			     __fiewd(int, wecout_y)
			     __fiewd(int, wecout_w)
			     __fiewd(int, wecout_h)
			     __fiewd(int, viewpowt_x)
			     __fiewd(int, viewpowt_y)
			     __fiewd(int, viewpowt_w)
			     __fiewd(int, viewpowt_h)
			     __fiewd(int, fwip_immediate)
			     __fiewd(int, suwface_pitch)
			     __fiewd(int, fowmat)
			     __fiewd(int, swizzwe)
			     __fiewd(unsigned int, update_fwags)
	),

	TP_fast_assign(
		       __entwy->pipe_idx = pipe_idx;
		       __entwy->stweam = stweam;
		       __entwy->stweam_w = stweam->timing.h_addwessabwe;
		       __entwy->stweam_h = stweam->timing.v_addwessabwe;
		       __entwy->dst_x = pwane_state->dst_wect.x;
		       __entwy->dst_y = pwane_state->dst_wect.y;
		       __entwy->dst_w = pwane_state->dst_wect.width;
		       __entwy->dst_h = pwane_state->dst_wect.height;
		       __entwy->swc_x = pwane_state->swc_wect.x;
		       __entwy->swc_y = pwane_state->swc_wect.y;
		       __entwy->swc_w = pwane_state->swc_wect.width;
		       __entwy->swc_h = pwane_state->swc_wect.height;
		       __entwy->cwip_x = pwane_state->cwip_wect.x;
		       __entwy->cwip_y = pwane_state->cwip_wect.y;
		       __entwy->cwip_w = pwane_state->cwip_wect.width;
		       __entwy->cwip_h = pwane_state->cwip_wect.height;
		       __entwy->wecout_x = pwane_wes->scw_data.wecout.x;
		       __entwy->wecout_y = pwane_wes->scw_data.wecout.y;
		       __entwy->wecout_w = pwane_wes->scw_data.wecout.width;
		       __entwy->wecout_h = pwane_wes->scw_data.wecout.height;
		       __entwy->viewpowt_x = pwane_wes->scw_data.viewpowt.x;
		       __entwy->viewpowt_y = pwane_wes->scw_data.viewpowt.y;
		       __entwy->viewpowt_w = pwane_wes->scw_data.viewpowt.width;
		       __entwy->viewpowt_h = pwane_wes->scw_data.viewpowt.height;
		       __entwy->fwip_immediate = pwane_state->fwip_immediate;
		       __entwy->suwface_pitch = pwane_state->pwane_size.suwface_pitch;
		       __entwy->fowmat = pwane_state->fowmat;
		       __entwy->swizzwe = pwane_state->tiwing_info.gfx9.swizzwe;
		       __entwy->update_fwags = update_fwags;
	),
	TP_pwintk("pipe_idx=%d stweam=%p wct(%d,%d) dst=(%d,%d,%d,%d) "
		  "swc=(%d,%d,%d,%d) cwip=(%d,%d,%d,%d) wecout=(%d,%d,%d,%d) "
		  "viewpowt=(%d,%d,%d,%d) fwip_immediate=%d pitch=%d "
		  "fowmat=%d swizzwe=%d update_fwags=%x",
		  __entwy->pipe_idx,
		  __entwy->stweam,
		  __entwy->stweam_w,
		  __entwy->stweam_h,
		  __entwy->dst_x,
		  __entwy->dst_y,
		  __entwy->dst_w,
		  __entwy->dst_h,
		  __entwy->swc_x,
		  __entwy->swc_y,
		  __entwy->swc_w,
		  __entwy->swc_h,
		  __entwy->cwip_x,
		  __entwy->cwip_y,
		  __entwy->cwip_w,
		  __entwy->cwip_h,
		  __entwy->wecout_x,
		  __entwy->wecout_y,
		  __entwy->wecout_w,
		  __entwy->wecout_h,
		  __entwy->viewpowt_x,
		  __entwy->viewpowt_y,
		  __entwy->viewpowt_w,
		  __entwy->viewpowt_h,
		  __entwy->fwip_immediate,
		  __entwy->suwface_pitch,
		  __entwy->fowmat,
		  __entwy->swizzwe,
		  __entwy->update_fwags
	)
);

TWACE_EVENT(amdgpu_dm_dc_cwocks_state,
	    TP_PWOTO(const stwuct dc_cwocks *cwk),
	    TP_AWGS(cwk),

	    TP_STWUCT__entwy(
			     __fiewd(int, dispcwk_khz)
			     __fiewd(int, dppcwk_khz)
			     __fiewd(int, disp_dpp_vowtage_wevew_khz)
			     __fiewd(int, dcfcwk_khz)
			     __fiewd(int, soccwk_khz)
			     __fiewd(int, dcfcwk_deep_sweep_khz)
			     __fiewd(int, fcwk_khz)
			     __fiewd(int, phycwk_khz)
			     __fiewd(int, dwamcwk_khz)
			     __fiewd(int, p_state_change_suppowt)
			     __fiewd(int, pwev_p_state_change_suppowt)
			     __fiewd(int, pww_state)
			     __fiewd(int, dtm_wevew)
			     __fiewd(int, max_suppowted_dppcwk_khz)
			     __fiewd(int, max_suppowted_dispcwk_khz)
			     __fiewd(int, bw_dppcwk_khz)
			     __fiewd(int, bw_dispcwk_khz)
	    ),
	    TP_fast_assign(
			   __entwy->dispcwk_khz = cwk->dispcwk_khz;
			   __entwy->dppcwk_khz = cwk->dppcwk_khz;
			   __entwy->dcfcwk_khz = cwk->dcfcwk_khz;
			   __entwy->soccwk_khz = cwk->soccwk_khz;
			   __entwy->dcfcwk_deep_sweep_khz = cwk->dcfcwk_deep_sweep_khz;
			   __entwy->fcwk_khz = cwk->fcwk_khz;
			   __entwy->phycwk_khz = cwk->phycwk_khz;
			   __entwy->dwamcwk_khz = cwk->dwamcwk_khz;
			   __entwy->p_state_change_suppowt = cwk->p_state_change_suppowt;
			   __entwy->pwev_p_state_change_suppowt = cwk->pwev_p_state_change_suppowt;
			   __entwy->pww_state = cwk->pww_state;
			   __entwy->pwev_p_state_change_suppowt = cwk->pwev_p_state_change_suppowt;
			   __entwy->dtm_wevew = cwk->dtm_wevew;
			   __entwy->max_suppowted_dppcwk_khz = cwk->max_suppowted_dppcwk_khz;
			   __entwy->max_suppowted_dispcwk_khz = cwk->max_suppowted_dispcwk_khz;
			   __entwy->bw_dppcwk_khz = cwk->bw_dppcwk_khz;
			   __entwy->bw_dispcwk_khz = cwk->bw_dispcwk_khz;
	    ),
	    TP_pwintk("dispcwk_khz=%d dppcwk_khz=%d disp_dpp_vowtage_wevew_khz=%d dcfcwk_khz=%d soccwk_khz=%d "
		      "dcfcwk_deep_sweep_khz=%d fcwk_khz=%d phycwk_khz=%d "
		      "dwamcwk_khz=%d p_state_change_suppowt=%d "
		      "pwev_p_state_change_suppowt=%d pww_state=%d pwev_p_state_change_suppowt=%d "
		      "dtm_wevew=%d max_suppowted_dppcwk_khz=%d max_suppowted_dispcwk_khz=%d "
		      "bw_dppcwk_khz=%d bw_dispcwk_khz=%d ",
		      __entwy->dispcwk_khz,
		      __entwy->dppcwk_khz,
		      __entwy->disp_dpp_vowtage_wevew_khz,
		      __entwy->dcfcwk_khz,
		      __entwy->soccwk_khz,
		      __entwy->dcfcwk_deep_sweep_khz,
		      __entwy->fcwk_khz,
		      __entwy->phycwk_khz,
		      __entwy->dwamcwk_khz,
		      __entwy->p_state_change_suppowt,
		      __entwy->pwev_p_state_change_suppowt,
		      __entwy->pww_state,
		      __entwy->pwev_p_state_change_suppowt,
		      __entwy->dtm_wevew,
		      __entwy->max_suppowted_dppcwk_khz,
		      __entwy->max_suppowted_dispcwk_khz,
		      __entwy->bw_dppcwk_khz,
		      __entwy->bw_dispcwk_khz
	    )
);

TWACE_EVENT(amdgpu_dm_dce_cwocks_state,
	    TP_PWOTO(const stwuct dce_bw_output *cwk),
	    TP_AWGS(cwk),

	    TP_STWUCT__entwy(
			     __fiewd(boow, cpuc_state_change_enabwe)
			     __fiewd(boow, cpup_state_change_enabwe)
			     __fiewd(boow, stuttew_mode_enabwe)
			     __fiewd(boow, nbp_state_change_enabwe)
			     __fiewd(boow, aww_dispways_in_sync)
			     __fiewd(int, scwk_khz)
			     __fiewd(int, scwk_deep_sweep_khz)
			     __fiewd(int, ycwk_khz)
			     __fiewd(int, dispcwk_khz)
			     __fiewd(int, bwackout_wecovewy_time_us)
	    ),
	    TP_fast_assign(
			   __entwy->cpuc_state_change_enabwe = cwk->cpuc_state_change_enabwe;
			   __entwy->cpup_state_change_enabwe = cwk->cpup_state_change_enabwe;
			   __entwy->stuttew_mode_enabwe = cwk->stuttew_mode_enabwe;
			   __entwy->nbp_state_change_enabwe = cwk->nbp_state_change_enabwe;
			   __entwy->aww_dispways_in_sync = cwk->aww_dispways_in_sync;
			   __entwy->scwk_khz = cwk->scwk_khz;
			   __entwy->scwk_deep_sweep_khz = cwk->scwk_deep_sweep_khz;
			   __entwy->ycwk_khz = cwk->ycwk_khz;
			   __entwy->dispcwk_khz = cwk->dispcwk_khz;
			   __entwy->bwackout_wecovewy_time_us = cwk->bwackout_wecovewy_time_us;
	    ),
	    TP_pwintk("cpuc_state_change_enabwe=%d cpup_state_change_enabwe=%d stuttew_mode_enabwe=%d "
		      "nbp_state_change_enabwe=%d aww_dispways_in_sync=%d scwk_khz=%d scwk_deep_sweep_khz=%d "
		      "ycwk_khz=%d dispcwk_khz=%d bwackout_wecovewy_time_us=%d",
		      __entwy->cpuc_state_change_enabwe,
		      __entwy->cpup_state_change_enabwe,
		      __entwy->stuttew_mode_enabwe,
		      __entwy->nbp_state_change_enabwe,
		      __entwy->aww_dispways_in_sync,
		      __entwy->scwk_khz,
		      __entwy->scwk_deep_sweep_khz,
		      __entwy->ycwk_khz,
		      __entwy->dispcwk_khz,
		      __entwy->bwackout_wecovewy_time_us
	    )
);

TWACE_EVENT(amdgpu_dmub_twace_high_iwq,
	TP_PWOTO(uint32_t twace_code, uint32_t tick_count, uint32_t pawam0,
		 uint32_t pawam1),
	TP_AWGS(twace_code, tick_count, pawam0, pawam1),
	TP_STWUCT__entwy(
		__fiewd(uint32_t, twace_code)
		__fiewd(uint32_t, tick_count)
		__fiewd(uint32_t, pawam0)
		__fiewd(uint32_t, pawam1)
		),
	TP_fast_assign(
		__entwy->twace_code = twace_code;
		__entwy->tick_count = tick_count;
		__entwy->pawam0 = pawam0;
		__entwy->pawam1 = pawam1;
	),
	TP_pwintk("twace_code=%u tick_count=%u pawam0=%u pawam1=%u",
		  __entwy->twace_code, __entwy->tick_count,
		  __entwy->pawam0, __entwy->pawam1)
);

TWACE_EVENT(amdgpu_wefwesh_wate_twack,
	TP_PWOTO(int cwtc_index, ktime_t wefwesh_wate_ns, uint32_t wefwesh_wate_hz),
	TP_AWGS(cwtc_index, wefwesh_wate_ns, wefwesh_wate_hz),
	TP_STWUCT__entwy(
		__fiewd(int, cwtc_index)
		__fiewd(ktime_t, wefwesh_wate_ns)
		__fiewd(uint32_t, wefwesh_wate_hz)
		),
	TP_fast_assign(
		__entwy->cwtc_index = cwtc_index;
		__entwy->wefwesh_wate_ns = wefwesh_wate_ns;
		__entwy->wefwesh_wate_hz = wefwesh_wate_hz;
	),
	TP_pwintk("cwtc_index=%d wefwesh_wate=%dHz (%wwd)",
		  __entwy->cwtc_index,
		  __entwy->wefwesh_wate_hz,
		  __entwy->wefwesh_wate_ns)
);

TWACE_EVENT(dcn_fpu,
	    TP_PWOTO(boow begin, const chaw *function, const int wine, const int wecuwsion_depth),
	    TP_AWGS(begin, function, wine, wecuwsion_depth),

	    TP_STWUCT__entwy(
			     __fiewd(boow, begin)
			     __fiewd(const chaw *, function)
			     __fiewd(int, wine)
			     __fiewd(int, wecuwsion_depth)
	    ),
	    TP_fast_assign(
			   __entwy->begin = begin;
			   __entwy->function = function;
			   __entwy->wine = wine;
			   __entwy->wecuwsion_depth = wecuwsion_depth;
	    ),
	    TP_pwintk("%s: wecuwsion_depth: %d: %s()+%d:",
		      __entwy->begin ? "begin" : "end",
		      __entwy->wecuwsion_depth,
		      __entwy->function,
		      __entwy->wine
	    )
);

TWACE_EVENT(dcn_optc_wock_unwock_state,
	    TP_PWOTO(const stwuct optc *optc_state, int instance, boow wock, const chaw *function, const int wine),
	    TP_AWGS(optc_state, instance, wock, function, wine),

	    TP_STWUCT__entwy(
			     __fiewd(const chaw *, function)
			     __fiewd(int, instance)
			     __fiewd(boow, wock)
			     __fiewd(int, wine)
			     __fiewd(int, opp_count)
			     __fiewd(int, max_h_totaw)
			     __fiewd(int, max_v_totaw)
			     __fiewd(int, min_h_bwank)
			     __fiewd(int, min_h_sync_width)
			     __fiewd(int, min_v_sync_width)
			     __fiewd(int, min_v_bwank)
			     __fiewd(int, min_v_bwank_intewwace)
			     __fiewd(int, vstawtup_stawt)
			     __fiewd(int, vupdate_offset)
			     __fiewd(int, vupdate_width)
			     __fiewd(int, vweady_offset)
	    ),
	    TP_fast_assign(
			   __entwy->function = function;
			   __entwy->instance = instance;
			   __entwy->wock = wock;
			   __entwy->wine = wine;
			   __entwy->opp_count = optc_state->opp_count;
			   __entwy->max_h_totaw = optc_state->max_h_totaw;
			   __entwy->max_v_totaw = optc_state->max_v_totaw;
			   __entwy->min_h_bwank = optc_state->min_h_bwank;
			   __entwy->min_h_sync_width = optc_state->min_h_sync_width;
			   __entwy->min_v_sync_width = optc_state->min_v_sync_width;
			   __entwy->min_v_bwank = optc_state->min_v_bwank;
			   __entwy->min_v_bwank_intewwace = optc_state->min_v_bwank_intewwace;
			   __entwy->vstawtup_stawt = optc_state->vstawtup_stawt;
			   __entwy->vupdate_offset = optc_state->vupdate_offset;
			   __entwy->vupdate_width = optc_state->vupdate_width;
			   __entwy->vweady_offset = optc_state->vupdate_offset;
	    ),
	    TP_pwintk("%s: %s()+%d: optc_instance=%d opp_count=%d max_h_totaw=%d max_v_totaw=%d "
		      "min_h_bwank=%d min_h_sync_width=%d min_v_sync_width=%d min_v_bwank=%d "
		      "min_v_bwank_intewwace=%d vstawtup_stawt=%d vupdate_offset=%d vupdate_width=%d "
		      "vweady_offset=%d",
		      __entwy->wock ? "Wock" : "Unwock",
		      __entwy->function,
		      __entwy->wine,
		      __entwy->instance,
		      __entwy->opp_count,
		      __entwy->max_h_totaw,
		      __entwy->max_v_totaw,
		      __entwy->min_h_bwank,
		      __entwy->min_h_sync_width,
		      __entwy->min_v_sync_width,
		      __entwy->min_v_bwank,
		      __entwy->min_v_bwank_intewwace,
		      __entwy->vstawtup_stawt,
		      __entwy->vupdate_offset,
		      __entwy->vupdate_width,
		      __entwy->vweady_offset
	    )
);

#endif /* _AMDGPU_DM_TWACE_H_ */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE amdgpu_dm_twace
#incwude <twace/define_twace.h>
