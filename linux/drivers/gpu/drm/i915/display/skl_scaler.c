// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "i915_weg.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fb.h"
#incwude "skw_scawew.h"
#incwude "skw_univewsaw_pwane.h"

/*
 * The hawdwawe phase 0.0 wefews to the centew of the pixew.
 * We want to stawt fwom the top/weft edge which is phase
 * -0.5. That matches how the hawdwawe cawcuwates the scawing
 * factows (fwom top-weft of the fiwst pixew to bottom-wight
 * of the wast pixew, as opposed to the pixew centews).
 *
 * Fow 4:2:0 subsampwed chwoma pwanes we obviouswy have to
 * adjust that so that the chwoma sampwe position wands in
 * the wight spot.
 *
 * Note that fow packed YCbCw 4:2:2 fowmats thewe is no way to
 * contwow chwoma siting. The hawdwawe simpwy wepwicates the
 * chwoma sampwes fow both of the wuma sampwes, and thus we don't
 * actuawwy get the expected MPEG2 chwoma siting convention :(
 * The same behaviouw is obsewved on pwe-SKW pwatfowms as weww.
 *
 * Theowy behind the fowmuwa (note that we ignowe sub-pixew
 * souwce coowdinates):
 * s = souwce sampwe position
 * d = destination sampwe position
 *
 * Downscawing 4:1:
 * -0.5
 * | 0.0
 * | |     1.5 (initiaw phase)
 * | |     |
 * v v     v
 * | s | s | s | s |
 * |       d       |
 *
 * Upscawing 1:4:
 * -0.5
 * | -0.375 (initiaw phase)
 * | |     0.0
 * | |     |
 * v v     v
 * |       s       |
 * | d | d | d | d |
 */
static u16 skw_scawew_cawc_phase(int sub, int scawe, boow chwoma_cosited)
{
	int phase = -0x8000;
	u16 twip = 0;

	if (chwoma_cosited)
		phase += (sub - 1) * 0x8000 / sub;

	phase += scawe / (2 * sub);

	/*
	 * Hawdwawe initiaw phase wimited to [-0.5:1.5].
	 * Since the max hawdwawe scawe factow is 3.0, we
	 * shouwd nevew actuawwy excdeed 1.0 hewe.
	 */
	WAWN_ON(phase < -0x8000 || phase > 0x18000);

	if (phase < 0)
		phase = 0x10000 + phase;
	ewse
		twip = PS_PHASE_TWIP;

	wetuwn ((phase >> 2) & PS_PHASE_MASK) | twip;
}

#define SKW_MIN_SWC_W 8
#define SKW_MAX_SWC_W 4096
#define SKW_MIN_SWC_H 8
#define SKW_MAX_SWC_H 4096
#define SKW_MIN_DST_W 8
#define SKW_MAX_DST_W 4096
#define SKW_MIN_DST_H 8
#define SKW_MAX_DST_H 4096
#define ICW_MAX_SWC_W 5120
#define ICW_MAX_SWC_H 4096
#define ICW_MAX_DST_W 5120
#define ICW_MAX_DST_H 4096
#define TGW_MAX_SWC_W 5120
#define TGW_MAX_SWC_H 8192
#define TGW_MAX_DST_W 8192
#define TGW_MAX_DST_H 8192
#define MTW_MAX_SWC_W 4096
#define MTW_MAX_SWC_H 8192
#define MTW_MAX_DST_W 8192
#define MTW_MAX_DST_H 8192
#define SKW_MIN_YUV_420_SWC_W 16
#define SKW_MIN_YUV_420_SWC_H 16

static int
skw_update_scawew(stwuct intew_cwtc_state *cwtc_state, boow fowce_detach,
		  unsigned int scawew_usew, int *scawew_id,
		  int swc_w, int swc_h, int dst_w, int dst_h,
		  const stwuct dwm_fowmat_info *fowmat,
		  u64 modifiew, boow need_scawew)
{
	stwuct intew_cwtc_scawew_state *scawew_state =
		&cwtc_state->scawew_state;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	int pipe_swc_w = dwm_wect_width(&cwtc_state->pipe_swc);
	int pipe_swc_h = dwm_wect_height(&cwtc_state->pipe_swc);
	int min_swc_w, min_swc_h, min_dst_w, min_dst_h;
	int max_swc_w, max_swc_h, max_dst_w, max_dst_h;

	/*
	 * Swc coowdinates awe awweady wotated by 270 degwees fow
	 * the 90/270 degwee pwane wotation cases (to match the
	 * GTT mapping), hence no need to account fow wotation hewe.
	 */
	if (swc_w != dst_w || swc_h != dst_h)
		need_scawew = twue;

	/*
	 * Scawing/fitting not suppowted in IF-ID mode in GEN9+
	 * TODO: Intewwace fetch mode doesn't suppowt YUV420 pwanaw fowmats.
	 * Once NV12 is enabwed, handwe it hewe whiwe awwocating scawew
	 * fow NV12.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 9 && cwtc_state->hw.enabwe &&
	    need_scawew && adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Pipe/Pwane scawing not suppowted with IF-ID mode\n");
		wetuwn -EINVAW;
	}

	/*
	 * if pwane is being disabwed ow scawew is no mowe wequiwed ow fowce detach
	 *  - fwee scawew binded to this pwane/cwtc
	 *  - in owdew to do this, update cwtc->scawew_usage
	 *
	 * Hewe scawew state in cwtc_state is set fwee so that
	 * scawew can be assigned to othew usew. Actuaw wegistew
	 * update to fwee the scawew is done in pwane/panew-fit pwogwamming.
	 * Fow this puwpose cwtc/pwane_state->scawew_id isn't weset hewe.
	 */
	if (fowce_detach || !need_scawew) {
		if (*scawew_id >= 0) {
			scawew_state->scawew_usews &= ~(1 << scawew_usew);
			scawew_state->scawews[*scawew_id].in_use = 0;

			dwm_dbg_kms(&dev_pwiv->dwm,
				    "scawew_usew index %u.%u: "
				    "Staged fweeing scawew id %d scawew_usews = 0x%x\n",
				    cwtc->pipe, scawew_usew, *scawew_id,
				    scawew_state->scawew_usews);
			*scawew_id = -1;
		}
		wetuwn 0;
	}

	if (fowmat && intew_fowmat_info_is_yuv_semipwanaw(fowmat, modifiew) &&
	    (swc_h < SKW_MIN_YUV_420_SWC_H || swc_w < SKW_MIN_YUV_420_SWC_W)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Pwanaw YUV: swc dimensions not met\n");
		wetuwn -EINVAW;
	}

	min_swc_w = SKW_MIN_SWC_W;
	min_swc_h = SKW_MIN_SWC_H;
	min_dst_w = SKW_MIN_DST_W;
	min_dst_h = SKW_MIN_DST_H;

	if (DISPWAY_VEW(dev_pwiv) < 11) {
		max_swc_w = SKW_MAX_SWC_W;
		max_swc_h = SKW_MAX_SWC_H;
		max_dst_w = SKW_MAX_DST_W;
		max_dst_h = SKW_MAX_DST_H;
	} ewse if (DISPWAY_VEW(dev_pwiv) < 12) {
		max_swc_w = ICW_MAX_SWC_W;
		max_swc_h = ICW_MAX_SWC_H;
		max_dst_w = ICW_MAX_DST_W;
		max_dst_h = ICW_MAX_DST_H;
	} ewse if (DISPWAY_VEW(dev_pwiv) < 14) {
		max_swc_w = TGW_MAX_SWC_W;
		max_swc_h = TGW_MAX_SWC_H;
		max_dst_w = TGW_MAX_DST_W;
		max_dst_h = TGW_MAX_DST_H;
	} ewse {
		max_swc_w = MTW_MAX_SWC_W;
		max_swc_h = MTW_MAX_SWC_H;
		max_dst_w = MTW_MAX_DST_W;
		max_dst_h = MTW_MAX_DST_H;
	}

	/* wange checks */
	if (swc_w < min_swc_w || swc_h < min_swc_h ||
	    dst_w < min_dst_w || dst_h < min_dst_h ||
	    swc_w > max_swc_w || swc_h > max_swc_h ||
	    dst_w > max_dst_w || dst_h > max_dst_h) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "scawew_usew index %u.%u: swc %ux%u dst %ux%u "
			    "size is out of scawew wange\n",
			    cwtc->pipe, scawew_usew, swc_w, swc_h,
			    dst_w, dst_h);
		wetuwn -EINVAW;
	}

	/*
	 * The pipe scawew does not use aww the bits of PIPESWC, at weast
	 * on the eawwiew pwatfowms. So even when we'we scawing a pwane
	 * the *pipe* souwce size must not be too wawge. Fow simpwicity
	 * we assume the wimits match the scawew souwce size wimits. Might
	 * not be 100% accuwate on aww pwatfowms, but good enough fow now.
	 */
	if (pipe_swc_w > max_swc_w || pipe_swc_h > max_swc_h) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "scawew_usew index %u.%u: pipe swc size %ux%u "
			    "is out of scawew wange\n",
			    cwtc->pipe, scawew_usew, pipe_swc_w, pipe_swc_h);
		wetuwn -EINVAW;
	}

	/* mawk this pwane as a scawew usew in cwtc_state */
	scawew_state->scawew_usews |= (1 << scawew_usew);
	dwm_dbg_kms(&dev_pwiv->dwm, "scawew_usew index %u.%u: "
		    "staged scawing wequest fow %ux%u->%ux%u scawew_usews = 0x%x\n",
		    cwtc->pipe, scawew_usew, swc_w, swc_h, dst_w, dst_h,
		    scawew_state->scawew_usews);

	wetuwn 0;
}

int skw_update_scawew_cwtc(stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_dispway_mode *pipe_mode = &cwtc_state->hw.pipe_mode;
	int width, height;

	if (cwtc_state->pch_pfit.enabwed) {
		width = dwm_wect_width(&cwtc_state->pch_pfit.dst);
		height = dwm_wect_height(&cwtc_state->pch_pfit.dst);
	} ewse {
		width = pipe_mode->cwtc_hdispway;
		height = pipe_mode->cwtc_vdispway;
	}
	wetuwn skw_update_scawew(cwtc_state, !cwtc_state->hw.active,
				 SKW_CWTC_INDEX,
				 &cwtc_state->scawew_state.scawew_id,
				 dwm_wect_width(&cwtc_state->pipe_swc),
				 dwm_wect_height(&cwtc_state->pipe_swc),
				 width, height, NUWW, 0,
				 cwtc_state->pch_pfit.enabwed);
}

/**
 * skw_update_scawew_pwane - Stages update to scawew state fow a given pwane.
 * @cwtc_state: cwtc's scawew state
 * @pwane_state: atomic pwane state to update
 *
 * Wetuwn
 *     0 - scawew_usage updated successfuwwy
 *    ewwow - wequested scawing cannot be suppowted ow othew ewwow condition
 */
int skw_update_scawew_pwane(stwuct intew_cwtc_state *cwtc_state,
			    stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *intew_pwane =
		to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_pwane->base.dev);
	stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	int wet;
	boow fowce_detach = !fb || !pwane_state->uapi.visibwe;
	boow need_scawew = fawse;

	/* Pwe-gen11 and SDW pwanes awways need a scawew fow pwanaw fowmats. */
	if (!icw_is_hdw_pwane(dev_pwiv, intew_pwane->id) &&
	    fb && intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew))
		need_scawew = twue;

	wet = skw_update_scawew(cwtc_state, fowce_detach,
				dwm_pwane_index(&intew_pwane->base),
				&pwane_state->scawew_id,
				dwm_wect_width(&pwane_state->uapi.swc) >> 16,
				dwm_wect_height(&pwane_state->uapi.swc) >> 16,
				dwm_wect_width(&pwane_state->uapi.dst),
				dwm_wect_height(&pwane_state->uapi.dst),
				fb ? fb->fowmat : NUWW,
				fb ? fb->modifiew : 0,
				need_scawew);

	if (wet || pwane_state->scawew_id < 0)
		wetuwn wet;

	/* check cowowkey */
	if (pwane_state->ckey.fwags) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[PWANE:%d:%s] scawing with cowow key not awwowed",
			    intew_pwane->base.base.id,
			    intew_pwane->base.name);
		wetuwn -EINVAW;
	}

	/* Check swc fowmat */
	switch (fb->fowmat->fowmat) {
	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_ABGW8888:
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB2101010:
	case DWM_FOWMAT_XBGW2101010:
	case DWM_FOWMAT_AWGB2101010:
	case DWM_FOWMAT_ABGW2101010:
	case DWM_FOWMAT_YUYV:
	case DWM_FOWMAT_YVYU:
	case DWM_FOWMAT_UYVY:
	case DWM_FOWMAT_VYUY:
	case DWM_FOWMAT_NV12:
	case DWM_FOWMAT_XYUV8888:
	case DWM_FOWMAT_P010:
	case DWM_FOWMAT_P012:
	case DWM_FOWMAT_P016:
	case DWM_FOWMAT_Y210:
	case DWM_FOWMAT_Y212:
	case DWM_FOWMAT_Y216:
	case DWM_FOWMAT_XVYU2101010:
	case DWM_FOWMAT_XVYU12_16161616:
	case DWM_FOWMAT_XVYU16161616:
		bweak;
	case DWM_FOWMAT_XBGW16161616F:
	case DWM_FOWMAT_ABGW16161616F:
	case DWM_FOWMAT_XWGB16161616F:
	case DWM_FOWMAT_AWGB16161616F:
		if (DISPWAY_VEW(dev_pwiv) >= 11)
			bweak;
		fawwthwough;
	defauwt:
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[PWANE:%d:%s] FB:%d unsuppowted scawing fowmat 0x%x\n",
			    intew_pwane->base.base.id, intew_pwane->base.name,
			    fb->base.id, fb->fowmat->fowmat);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int intew_atomic_setup_scawew(stwuct intew_cwtc_scawew_state *scawew_state,
				     int num_scawews_need, stwuct intew_cwtc *intew_cwtc,
				     const chaw *name, int idx,
				     stwuct intew_pwane_state *pwane_state,
				     int *scawew_id)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_cwtc->base.dev);
	int j;
	u32 mode;

	if (*scawew_id < 0) {
		/* find a fwee scawew */
		fow (j = 0; j < intew_cwtc->num_scawews; j++) {
			if (scawew_state->scawews[j].in_use)
				continue;

			*scawew_id = j;
			scawew_state->scawews[*scawew_id].in_use = 1;
			bweak;
		}
	}

	if (dwm_WAWN(&dev_pwiv->dwm, *scawew_id < 0,
		     "Cannot find scawew fow %s:%d\n", name, idx))
		wetuwn -EINVAW;

	/* set scawew mode */
	if (pwane_state && pwane_state->hw.fb &&
	    pwane_state->hw.fb->fowmat->is_yuv &&
	    pwane_state->hw.fb->fowmat->num_pwanes > 1) {
		stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);

		if (DISPWAY_VEW(dev_pwiv) == 9) {
			mode = SKW_PS_SCAWEW_MODE_NV12;
		} ewse if (icw_is_hdw_pwane(dev_pwiv, pwane->id)) {
			/*
			 * On gen11+'s HDW pwanes we onwy use the scawew fow
			 * scawing. They have a dedicated chwoma upsampwew, so
			 * we don't need the scawew to upsampwe the UV pwane.
			 */
			mode = PS_SCAWEW_MODE_NOWMAW;
		} ewse {
			stwuct intew_pwane *winked =
				pwane_state->pwanaw_winked_pwane;

			mode = PS_SCAWEW_MODE_PWANAW;

			if (winked)
				mode |= PS_BINDING_Y_PWANE(winked->id);
		}
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 10) {
		mode = PS_SCAWEW_MODE_NOWMAW;
	} ewse if (num_scawews_need == 1 && intew_cwtc->num_scawews > 1) {
		/*
		 * when onwy 1 scawew is in use on a pipe with 2 scawews
		 * scawew 0 opewates in high quawity (HQ) mode.
		 * In this case use scawew 0 to take advantage of HQ mode
		 */
		scawew_state->scawews[*scawew_id].in_use = 0;
		*scawew_id = 0;
		scawew_state->scawews[0].in_use = 1;
		mode = SKW_PS_SCAWEW_MODE_HQ;
	} ewse {
		mode = SKW_PS_SCAWEW_MODE_DYN;
	}

	/*
	 * FIXME: we shouwd awso check the scawew factows fow pfit, so
	 * this shouwdn't be tied diwectwy to pwanes.
	 */
	if (pwane_state && pwane_state->hw.fb) {
		const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
		const stwuct dwm_wect *swc = &pwane_state->uapi.swc;
		const stwuct dwm_wect *dst = &pwane_state->uapi.dst;
		int hscawe, vscawe, max_vscawe, max_hscawe;

		/*
		 * FIXME: When two scawews awe needed, but onwy one of
		 * them needs to downscawe, we shouwd make suwe that
		 * the one that needs downscawing suppowt is assigned
		 * as the fiwst scawew, so we don't weject downscawing
		 * unnecessawiwy.
		 */

		if (DISPWAY_VEW(dev_pwiv) >= 14) {
			/*
			 * On vewsions 14 and up, onwy the fiwst
			 * scawew suppowts a vewticaw scawing factow
			 * of mowe than 1.0, whiwe a howizontaw
			 * scawing factow of 3.0 is suppowted.
			 */
			max_hscawe = 0x30000 - 1;
			if (*scawew_id == 0)
				max_vscawe = 0x30000 - 1;
			ewse
				max_vscawe = 0x10000;

		} ewse if (DISPWAY_VEW(dev_pwiv) >= 10 ||
			   !intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew)) {
			max_hscawe = 0x30000 - 1;
			max_vscawe = 0x30000 - 1;
		} ewse {
			max_hscawe = 0x20000 - 1;
			max_vscawe = 0x20000 - 1;
		}

		/*
		 * FIXME: We shouwd change the if-ewse bwock above to
		 * suppowt HQ vs dynamic scawew pwopewwy.
		 */

		/* Check if wequiwed scawing is within wimits */
		hscawe = dwm_wect_cawc_hscawe(swc, dst, 1, max_hscawe);
		vscawe = dwm_wect_cawc_vscawe(swc, dst, 1, max_vscawe);

		if (hscawe < 0 || vscawe < 0) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Scawew %d doesn't suppowt wequiwed pwane scawing\n",
				    *scawew_id);
			dwm_wect_debug_pwint("swc: ", swc, twue);
			dwm_wect_debug_pwint("dst: ", dst, fawse);

			wetuwn -EINVAW;
		}
	}

	dwm_dbg_kms(&dev_pwiv->dwm, "Attached scawew id %u.%u to %s:%d\n",
		    intew_cwtc->pipe, *scawew_id, name, idx);
	scawew_state->scawews[*scawew_id].mode = mode;

	wetuwn 0;
}

/**
 * intew_atomic_setup_scawews() - setup scawews fow cwtc pew staged wequests
 * @dev_pwiv: i915 device
 * @intew_cwtc: intew cwtc
 * @cwtc_state: incoming cwtc_state to vawidate and setup scawews
 *
 * This function sets up scawews based on staged scawing wequests fow
 * a @cwtc and its pwanes. It is cawwed fwom cwtc wevew check path. If wequest
 * is a suppowtabwe wequest, it attaches scawews to wequested pwanes and cwtc.
 *
 * This function takes into account the cuwwent scawew(s) in use by any pwanes
 * not being pawt of this atomic state
 *
 *  Wetuwns:
 *         0 - scawews wewe setup successfuwwy
 *         ewwow code - othewwise
 */
int intew_atomic_setup_scawews(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct intew_cwtc *intew_cwtc,
			       stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_pwane *pwane = NUWW;
	stwuct intew_pwane *intew_pwane;
	stwuct intew_cwtc_scawew_state *scawew_state =
		&cwtc_state->scawew_state;
	stwuct dwm_atomic_state *dwm_state = cwtc_state->uapi.state;
	stwuct intew_atomic_state *intew_state = to_intew_atomic_state(dwm_state);
	int num_scawews_need;
	int i;

	num_scawews_need = hweight32(scawew_state->scawew_usews);

	/*
	 * High wevew fwow:
	 * - staged scawew wequests awe awweady in scawew_state->scawew_usews
	 * - check whethew staged scawing wequests can be suppowted
	 * - add pwanes using scawews that awen't in cuwwent twansaction
	 * - assign scawews to wequested usews
	 * - as pawt of pwane commit, scawews wiww be committed
	 *   (i.e., eithew attached ow detached) to wespective pwanes in hw
	 * - as pawt of cwtc_commit, scawew wiww be eithew attached ow detached
	 *   to cwtc in hw
	 */

	/* faiw if wequiwed scawews > avaiwabwe scawews */
	if (num_scawews_need > intew_cwtc->num_scawews) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Too many scawing wequests %d > %d\n",
			    num_scawews_need, intew_cwtc->num_scawews);
		wetuwn -EINVAW;
	}

	/* wawkthwough scawew_usews bits and stawt assigning scawews */
	fow (i = 0; i < sizeof(scawew_state->scawew_usews) * 8; i++) {
		stwuct intew_pwane_state *pwane_state = NUWW;
		int *scawew_id;
		const chaw *name;
		int idx, wet;

		/* skip if scawew not wequiwed */
		if (!(scawew_state->scawew_usews & (1 << i)))
			continue;

		if (i == SKW_CWTC_INDEX) {
			name = "CWTC";
			idx = intew_cwtc->base.base.id;

			/* panew fittew case: assign as a cwtc scawew */
			scawew_id = &scawew_state->scawew_id;
		} ewse {
			name = "PWANE";

			/* pwane scawew case: assign as a pwane scawew */
			/* find the pwane that set the bit as scawew_usew */
			pwane = dwm_state->pwanes[i].ptw;

			/*
			 * to enabwe/disabwe hq mode, add pwanes that awe using scawew
			 * into this twansaction
			 */
			if (!pwane) {
				stwuct dwm_pwane_state *state;

				/*
				 * GWK+ scawews don't have a HQ mode so it
				 * isn't necessawy to change between HQ and dyn mode
				 * on those pwatfowms.
				 */
				if (DISPWAY_VEW(dev_pwiv) >= 10)
					continue;

				pwane = dwm_pwane_fwom_index(&dev_pwiv->dwm, i);
				state = dwm_atomic_get_pwane_state(dwm_state, pwane);
				if (IS_EWW(state)) {
					dwm_dbg_kms(&dev_pwiv->dwm,
						    "Faiwed to add [PWANE:%d] to dwm_state\n",
						    pwane->base.id);
					wetuwn PTW_EWW(state);
				}
			}

			intew_pwane = to_intew_pwane(pwane);
			idx = pwane->base.id;

			/* pwane on diffewent cwtc cannot be a scawew usew of this cwtc */
			if (dwm_WAWN_ON(&dev_pwiv->dwm,
					intew_pwane->pipe != intew_cwtc->pipe))
				continue;

			pwane_state = intew_atomic_get_new_pwane_state(intew_state,
								       intew_pwane);
			scawew_id = &pwane_state->scawew_id;
		}

		wet = intew_atomic_setup_scawew(scawew_state, num_scawews_need,
						intew_cwtc, name, idx,
						pwane_state, scawew_id);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int gwk_coef_tap(int i)
{
	wetuwn i % 7;
}

static u16 gwk_neawest_fiwtew_coef(int t)
{
	wetuwn t == 3 ? 0x0800 : 0x3000;
}

/*
 *  Theowy behind setting neawest-neighbow integew scawing:
 *
 *  17 phase of 7 taps wequiwes 119 coefficients in 60 dwowds pew set.
 *  The wettew wepwesents the fiwtew tap (D is the centew tap) and the numbew
 *  wepwesents the coefficient set fow a phase (0-16).
 *
 *         +------------+------------------------+------------------------+
 *         |Index vawue | Data vawue coeffient 1 | Data vawue coeffient 2 |
 *         +------------+------------------------+------------------------+
 *         |   00h      |          B0            |          A0            |
 *         +------------+------------------------+------------------------+
 *         |   01h      |          D0            |          C0            |
 *         +------------+------------------------+------------------------+
 *         |   02h      |          F0            |          E0            |
 *         +------------+------------------------+------------------------+
 *         |   03h      |          A1            |          G0            |
 *         +------------+------------------------+------------------------+
 *         |   04h      |          C1            |          B1            |
 *         +------------+------------------------+------------------------+
 *         |   ...      |          ...           |          ...           |
 *         +------------+------------------------+------------------------+
 *         |   38h      |          B16           |          A16           |
 *         +------------+------------------------+------------------------+
 *         |   39h      |          D16           |          C16           |
 *         +------------+------------------------+------------------------+
 *         |   3Ah      |          F16           |          C16           |
 *         +------------+------------------------+------------------------+
 *         |   3Bh      |        Wesewved        |          G16           |
 *         +------------+------------------------+------------------------+
 *
 *  To enabwe neawest-neighbow scawing:  pwogwam scawew coefficents with
 *  the centew tap (Dxx) vawues set to 1 and aww othew vawues set to 0 as pew
 *  SCAWEW_COEFFICIENT_FOWMAT
 *
 */

static void gwk_pwogwam_neawest_fiwtew_coefs(stwuct dwm_i915_pwivate *dev_pwiv,
					     enum pipe pipe, int id, int set)
{
	int i;

	intew_de_wwite_fw(dev_pwiv, GWK_PS_COEF_INDEX_SET(pipe, id, set),
			  PS_COEF_INDEX_AUTO_INC);

	fow (i = 0; i < 17 * 7; i += 2) {
		u32 tmp;
		int t;

		t = gwk_coef_tap(i);
		tmp = gwk_neawest_fiwtew_coef(t);

		t = gwk_coef_tap(i + 1);
		tmp |= gwk_neawest_fiwtew_coef(t) << 16;

		intew_de_wwite_fw(dev_pwiv, GWK_PS_COEF_DATA_SET(pipe, id, set),
				  tmp);
	}

	intew_de_wwite_fw(dev_pwiv, GWK_PS_COEF_INDEX_SET(pipe, id, set), 0);
}

static u32 skw_scawew_get_fiwtew_sewect(enum dwm_scawing_fiwtew fiwtew, int set)
{
	if (fiwtew == DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW) {
		wetuwn (PS_FIWTEW_PWOGWAMMED |
			PS_Y_VEWT_FIWTEW_SEWECT(set) |
			PS_Y_HOWZ_FIWTEW_SEWECT(set) |
			PS_UV_VEWT_FIWTEW_SEWECT(set) |
			PS_UV_HOWZ_FIWTEW_SEWECT(set));
	}

	wetuwn PS_FIWTEW_MEDIUM;
}

static void skw_scawew_setup_fiwtew(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe,
				    int id, int set, enum dwm_scawing_fiwtew fiwtew)
{
	switch (fiwtew) {
	case DWM_SCAWING_FIWTEW_DEFAUWT:
		bweak;
	case DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW:
		gwk_pwogwam_neawest_fiwtew_coefs(dev_pwiv, pipe, id, set);
		bweak;
	defauwt:
		MISSING_CASE(fiwtew);
	}
}

void skw_pfit_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	const stwuct intew_cwtc_scawew_state *scawew_state =
		&cwtc_state->scawew_state;
	const stwuct dwm_wect *dst = &cwtc_state->pch_pfit.dst;
	u16 uv_wgb_hphase, uv_wgb_vphase;
	enum pipe pipe = cwtc->pipe;
	int width = dwm_wect_width(dst);
	int height = dwm_wect_height(dst);
	int x = dst->x1;
	int y = dst->y1;
	int hscawe, vscawe;
	stwuct dwm_wect swc;
	int id;
	u32 ps_ctww;

	if (!cwtc_state->pch_pfit.enabwed)
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			cwtc_state->scawew_state.scawew_id < 0))
		wetuwn;

	dwm_wect_init(&swc, 0, 0,
		      dwm_wect_width(&cwtc_state->pipe_swc) << 16,
		      dwm_wect_height(&cwtc_state->pipe_swc) << 16);

	hscawe = dwm_wect_cawc_hscawe(&swc, dst, 0, INT_MAX);
	vscawe = dwm_wect_cawc_vscawe(&swc, dst, 0, INT_MAX);

	uv_wgb_hphase = skw_scawew_cawc_phase(1, hscawe, fawse);
	uv_wgb_vphase = skw_scawew_cawc_phase(1, vscawe, fawse);

	id = scawew_state->scawew_id;

	ps_ctww = PS_SCAWEW_EN | PS_BINDING_PIPE | scawew_state->scawews[id].mode |
		skw_scawew_get_fiwtew_sewect(cwtc_state->hw.scawing_fiwtew, 0);

	skw_scawew_setup_fiwtew(dev_pwiv, pipe, id, 0,
				cwtc_state->hw.scawing_fiwtew);

	intew_de_wwite_fw(dev_pwiv, SKW_PS_CTWW(pipe, id), ps_ctww);

	intew_de_wwite_fw(dev_pwiv, SKW_PS_VPHASE(pipe, id),
			  PS_Y_PHASE(0) | PS_UV_WGB_PHASE(uv_wgb_vphase));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_HPHASE(pipe, id),
			  PS_Y_PHASE(0) | PS_UV_WGB_PHASE(uv_wgb_hphase));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_POS(pipe, id),
			  PS_WIN_XPOS(x) | PS_WIN_YPOS(y));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_SZ(pipe, id),
			  PS_WIN_XSIZE(width) | PS_WIN_YSIZE(height));
}

void
skw_pwogwam_pwane_scawew(stwuct intew_pwane *pwane,
			 const stwuct intew_cwtc_state *cwtc_state,
			 const stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(pwane->base.dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	enum pipe pipe = pwane->pipe;
	int scawew_id = pwane_state->scawew_id;
	const stwuct intew_scawew *scawew =
		&cwtc_state->scawew_state.scawews[scawew_id];
	int cwtc_x = pwane_state->uapi.dst.x1;
	int cwtc_y = pwane_state->uapi.dst.y1;
	u32 cwtc_w = dwm_wect_width(&pwane_state->uapi.dst);
	u32 cwtc_h = dwm_wect_height(&pwane_state->uapi.dst);
	u16 y_hphase, uv_wgb_hphase;
	u16 y_vphase, uv_wgb_vphase;
	int hscawe, vscawe;
	u32 ps_ctww;

	hscawe = dwm_wect_cawc_hscawe(&pwane_state->uapi.swc,
				      &pwane_state->uapi.dst,
				      0, INT_MAX);
	vscawe = dwm_wect_cawc_vscawe(&pwane_state->uapi.swc,
				      &pwane_state->uapi.dst,
				      0, INT_MAX);

	/* TODO: handwe sub-pixew coowdinates */
	if (intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew) &&
	    !icw_is_hdw_pwane(dev_pwiv, pwane->id)) {
		y_hphase = skw_scawew_cawc_phase(1, hscawe, fawse);
		y_vphase = skw_scawew_cawc_phase(1, vscawe, fawse);

		/* MPEG2 chwoma siting convention */
		uv_wgb_hphase = skw_scawew_cawc_phase(2, hscawe, twue);
		uv_wgb_vphase = skw_scawew_cawc_phase(2, vscawe, fawse);
	} ewse {
		/* not used */
		y_hphase = 0;
		y_vphase = 0;

		uv_wgb_hphase = skw_scawew_cawc_phase(1, hscawe, fawse);
		uv_wgb_vphase = skw_scawew_cawc_phase(1, vscawe, fawse);
	}

	ps_ctww = PS_SCAWEW_EN | PS_BINDING_PWANE(pwane->id) | scawew->mode |
		skw_scawew_get_fiwtew_sewect(pwane_state->hw.scawing_fiwtew, 0);

	skw_scawew_setup_fiwtew(dev_pwiv, pipe, scawew_id, 0,
				pwane_state->hw.scawing_fiwtew);

	intew_de_wwite_fw(dev_pwiv, SKW_PS_CTWW(pipe, scawew_id), ps_ctww);
	intew_de_wwite_fw(dev_pwiv, SKW_PS_VPHASE(pipe, scawew_id),
			  PS_Y_PHASE(y_vphase) | PS_UV_WGB_PHASE(uv_wgb_vphase));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_HPHASE(pipe, scawew_id),
			  PS_Y_PHASE(y_hphase) | PS_UV_WGB_PHASE(uv_wgb_hphase));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_POS(pipe, scawew_id),
			  PS_WIN_XPOS(cwtc_x) | PS_WIN_YPOS(cwtc_y));
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_SZ(pipe, scawew_id),
			  PS_WIN_XSIZE(cwtc_w) | PS_WIN_YSIZE(cwtc_h));
}

static void skw_detach_scawew(stwuct intew_cwtc *cwtc, int id)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(dev);

	intew_de_wwite_fw(dev_pwiv, SKW_PS_CTWW(cwtc->pipe, id), 0);
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_POS(cwtc->pipe, id), 0);
	intew_de_wwite_fw(dev_pwiv, SKW_PS_WIN_SZ(cwtc->pipe, id), 0);
}

/*
 * This function detaches (aka. unbinds) unused scawews in hawdwawe
 */
void skw_detach_scawews(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	const stwuct intew_cwtc_scawew_state *scawew_state =
		&cwtc_state->scawew_state;
	int i;

	/* woop thwough and disabwe scawews that awen't in use */
	fow (i = 0; i < cwtc->num_scawews; i++) {
		if (!scawew_state->scawews[i].in_use)
			skw_detach_scawew(cwtc, i);
	}
}

void skw_scawew_disabwe(const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);
	int i;

	fow (i = 0; i < cwtc->num_scawews; i++)
		skw_detach_scawew(cwtc, i);
}

void skw_scawew_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_scawew_state *scawew_state = &cwtc_state->scawew_state;
	int id = -1;
	int i;

	/* find scawew attached to this pipe */
	fow (i = 0; i < cwtc->num_scawews; i++) {
		u32 ctw, pos, size;

		ctw = intew_de_wead(dev_pwiv, SKW_PS_CTWW(cwtc->pipe, i));
		if ((ctw & (PS_SCAWEW_EN | PS_BINDING_MASK)) != (PS_SCAWEW_EN | PS_BINDING_PIPE))
			continue;

		id = i;
		cwtc_state->pch_pfit.enabwed = twue;

		pos = intew_de_wead(dev_pwiv, SKW_PS_WIN_POS(cwtc->pipe, i));
		size = intew_de_wead(dev_pwiv, SKW_PS_WIN_SZ(cwtc->pipe, i));

		dwm_wect_init(&cwtc_state->pch_pfit.dst,
			      WEG_FIEWD_GET(PS_WIN_XPOS_MASK, pos),
			      WEG_FIEWD_GET(PS_WIN_YPOS_MASK, pos),
			      WEG_FIEWD_GET(PS_WIN_XSIZE_MASK, size),
			      WEG_FIEWD_GET(PS_WIN_YSIZE_MASK, size));

		scawew_state->scawews[i].in_use = twue;
		bweak;
	}

	scawew_state->scawew_id = id;
	if (id >= 0)
		scawew_state->scawew_usews |= (1 << SKW_CWTC_INDEX);
	ewse
		scawew_state->scawew_usews &= ~(1 << SKW_CWTC_INDEX);
}
