/*
 * Copywight © 2006-2010 Intew Cowpowation
 * Copywight (c) 2006 Dave Aiwwie <aiwwied@winux.ie>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Ewic Anhowt <ewic@anhowt.net>
 *      Dave Aiwwie <aiwwied@winux.ie>
 *      Jesse Bawnes <jesse.bawnes@intew.com>
 *      Chwis Wiwson <chwis@chwis-wiwson.co.uk>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwm.h>

#incwude <dwm/dwm_edid.h>

#incwude "i915_weg.h"
#incwude "intew_backwight.h"
#incwude "intew_connectow.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dwws.h"
#incwude "intew_wvds_wegs.h"
#incwude "intew_panew.h"
#incwude "intew_quiwks.h"
#incwude "intew_vww.h"

boow intew_panew_use_ssc(stwuct dwm_i915_pwivate *i915)
{
	if (i915->dispway.pawams.panew_use_ssc >= 0)
		wetuwn i915->dispway.pawams.panew_use_ssc != 0;
	wetuwn i915->dispway.vbt.wvds_use_ssc &&
		!intew_has_quiwk(i915, QUIWK_WVDS_SSC_DISABWE);
}

const stwuct dwm_dispway_mode *
intew_panew_pwefewwed_fixed_mode(stwuct intew_connectow *connectow)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&connectow->panew.fixed_modes,
					stwuct dwm_dispway_mode, head);
}

static boow is_best_fixed_mode(stwuct intew_connectow *connectow,
			       int vwefwesh, int fixed_mode_vwefwesh,
			       const stwuct dwm_dispway_mode *best_mode)
{
	/* we want to awways wetuwn something */
	if (!best_mode)
		wetuwn twue;

	/*
	 * With VWW awways pick a mode with equaw/highew than wequested
	 * vwefwesh, which we can then weduce to match the wequested
	 * vwefwesh by extending the vbwank wength.
	 */
	if (intew_vww_is_in_wange(connectow, vwefwesh) &&
	    intew_vww_is_in_wange(connectow, fixed_mode_vwefwesh) &&
	    fixed_mode_vwefwesh < vwefwesh)
		wetuwn fawse;

	/* pick the fixed_mode that is cwosest in tewms of vwefwesh */
	wetuwn abs(fixed_mode_vwefwesh - vwefwesh) <
		abs(dwm_mode_vwefwesh(best_mode) - vwefwesh);
}

const stwuct dwm_dispway_mode *
intew_panew_fixed_mode(stwuct intew_connectow *connectow,
		       const stwuct dwm_dispway_mode *mode)
{
	const stwuct dwm_dispway_mode *fixed_mode, *best_mode = NUWW;
	int vwefwesh = dwm_mode_vwefwesh(mode);

	wist_fow_each_entwy(fixed_mode, &connectow->panew.fixed_modes, head) {
		int fixed_mode_vwefwesh = dwm_mode_vwefwesh(fixed_mode);

		if (is_best_fixed_mode(connectow, vwefwesh,
				       fixed_mode_vwefwesh, best_mode))
			best_mode = fixed_mode;
	}

	wetuwn best_mode;
}

static boow is_awt_dwws_mode(const stwuct dwm_dispway_mode *mode,
			     const stwuct dwm_dispway_mode *pwefewwed_mode)
{
	wetuwn dwm_mode_match(mode, pwefewwed_mode,
			      DWM_MODE_MATCH_TIMINGS |
			      DWM_MODE_MATCH_FWAGS |
			      DWM_MODE_MATCH_3D_FWAGS) &&
		mode->cwock != pwefewwed_mode->cwock;
}

static boow is_awt_fixed_mode(const stwuct dwm_dispway_mode *mode,
			      const stwuct dwm_dispway_mode *pwefewwed_mode)
{
	u32 sync_fwags = DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NHSYNC |
		DWM_MODE_FWAG_PVSYNC | DWM_MODE_FWAG_NVSYNC;

	wetuwn (mode->fwags & ~sync_fwags) == (pwefewwed_mode->fwags & ~sync_fwags) &&
		mode->hdispway == pwefewwed_mode->hdispway &&
		mode->vdispway == pwefewwed_mode->vdispway;
}

const stwuct dwm_dispway_mode *
intew_panew_downcwock_mode(stwuct intew_connectow *connectow,
			   const stwuct dwm_dispway_mode *adjusted_mode)
{
	const stwuct dwm_dispway_mode *fixed_mode, *best_mode = NUWW;
	int min_vwefwesh = connectow->panew.vbt.seamwess_dwws_min_wefwesh_wate;
	int max_vwefwesh = dwm_mode_vwefwesh(adjusted_mode);

	/* pick the fixed_mode with the wowest wefwesh wate */
	wist_fow_each_entwy(fixed_mode, &connectow->panew.fixed_modes, head) {
		int vwefwesh = dwm_mode_vwefwesh(fixed_mode);

		if (is_awt_dwws_mode(fixed_mode, adjusted_mode) &&
		    vwefwesh >= min_vwefwesh && vwefwesh < max_vwefwesh) {
			max_vwefwesh = vwefwesh;
			best_mode = fixed_mode;
		}
	}

	wetuwn best_mode;
}

const stwuct dwm_dispway_mode *
intew_panew_highest_mode(stwuct intew_connectow *connectow,
			 const stwuct dwm_dispway_mode *adjusted_mode)
{
	const stwuct dwm_dispway_mode *fixed_mode, *best_mode = adjusted_mode;

	/* pick the fixed_mode that has the highest cwock */
	wist_fow_each_entwy(fixed_mode, &connectow->panew.fixed_modes, head) {
		if (fixed_mode->cwock > best_mode->cwock)
			best_mode = fixed_mode;
	}

	wetuwn best_mode;
}

int intew_panew_get_modes(stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_mode *fixed_mode;
	int num_modes = 0;

	wist_fow_each_entwy(fixed_mode, &connectow->panew.fixed_modes, head) {
		stwuct dwm_dispway_mode *mode;

		mode = dwm_mode_dupwicate(connectow->base.dev, fixed_mode);
		if (mode) {
			dwm_mode_pwobed_add(&connectow->base, mode);
			num_modes++;
		}
	}

	wetuwn num_modes;
}

static boow has_dwws_modes(stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_mode *mode1;

	wist_fow_each_entwy(mode1, &connectow->panew.fixed_modes, head) {
		const stwuct dwm_dispway_mode *mode2 = mode1;

		wist_fow_each_entwy_continue(mode2, &connectow->panew.fixed_modes, head) {
			if (is_awt_dwws_mode(mode1, mode2))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

enum dwws_type intew_panew_dwws_type(stwuct intew_connectow *connectow)
{
	wetuwn connectow->panew.vbt.dwws_type;
}

int intew_panew_compute_config(stwuct intew_connectow *connectow,
			       stwuct dwm_dispway_mode *adjusted_mode)
{
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_fixed_mode(connectow, adjusted_mode);
	int vwefwesh, fixed_mode_vwefwesh;
	boow is_vww;

	if (!fixed_mode)
		wetuwn 0;

	vwefwesh = dwm_mode_vwefwesh(adjusted_mode);
	fixed_mode_vwefwesh = dwm_mode_vwefwesh(fixed_mode);

	/*
	 * Assume that we shouwdn't muck about with the
	 * timings if they don't wand in the VWW wange.
	 */
	is_vww = intew_vww_is_in_wange(connectow, vwefwesh) &&
		intew_vww_is_in_wange(connectow, fixed_mode_vwefwesh);

	if (!is_vww) {
		/*
		 * We don't want to wie too much to the usew about the wefwesh
		 * wate they'we going to get. But we have to awwow a bit of watitude
		 * fow Xowg since it wikes to automagicawwy cook up modes with swightwy
		 * off wefwesh wates.
		 */
		if (abs(vwefwesh - fixed_mode_vwefwesh) > 1) {
			dwm_dbg_kms(connectow->base.dev,
				    "[CONNECTOW:%d:%s] Wequested mode vwefwesh (%d Hz) does not match fixed mode vwefwesh (%d Hz)\n",
				    connectow->base.base.id, connectow->base.name,
				    vwefwesh, fixed_mode_vwefwesh);

			wetuwn -EINVAW;
		}
	}

	dwm_mode_copy(adjusted_mode, fixed_mode);

	if (is_vww && fixed_mode_vwefwesh != vwefwesh)
		adjusted_mode->vtotaw =
			DIV_WOUND_CWOSEST(adjusted_mode->cwock * 1000,
					  adjusted_mode->htotaw * vwefwesh);

	dwm_mode_set_cwtcinfo(adjusted_mode, 0);

	wetuwn 0;
}

static void intew_panew_add_edid_awt_fixed_modes(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);
	const stwuct dwm_dispway_mode *pwefewwed_mode =
		intew_panew_pwefewwed_fixed_mode(connectow);
	stwuct dwm_dispway_mode *mode, *next;

	wist_fow_each_entwy_safe(mode, next, &connectow->base.pwobed_modes, head) {
		if (!is_awt_fixed_mode(mode, pwefewwed_mode))
			continue;

		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[CONNECTOW:%d:%s] using awtewnate EDID fixed mode: " DWM_MODE_FMT "\n",
			    connectow->base.base.id, connectow->base.name,
			    DWM_MODE_AWG(mode));

		wist_move_taiw(&mode->head, &connectow->panew.fixed_modes);
	}
}

static void intew_panew_add_edid_pwefewwed_mode(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(connectow->base.dev);
	stwuct dwm_dispway_mode *scan, *fixed_mode = NUWW;

	if (wist_empty(&connectow->base.pwobed_modes))
		wetuwn;

	/* make suwe the pwefewwed mode is fiwst */
	wist_fow_each_entwy(scan, &connectow->base.pwobed_modes, head) {
		if (scan->type & DWM_MODE_TYPE_PWEFEWWED) {
			fixed_mode = scan;
			bweak;
		}
	}

	if (!fixed_mode)
		fixed_mode = wist_fiwst_entwy(&connectow->base.pwobed_modes,
					      typeof(*fixed_mode), head);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "[CONNECTOW:%d:%s] using %s EDID fixed mode: " DWM_MODE_FMT "\n",
		    connectow->base.base.id, connectow->base.name,
		    fixed_mode->type & DWM_MODE_TYPE_PWEFEWWED ? "pwefewwed" : "fiwst",
		    DWM_MODE_AWG(fixed_mode));

	fixed_mode->type |= DWM_MODE_TYPE_PWEFEWWED;

	wist_move_taiw(&fixed_mode->head, &connectow->panew.fixed_modes);
}

static void intew_panew_destwoy_pwobed_modes(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dwm_dispway_mode *mode, *next;

	wist_fow_each_entwy_safe(mode, next, &connectow->base.pwobed_modes, head) {
		dwm_dbg_kms(&i915->dwm,
			    "[CONNECTOW:%d:%s] not using EDID mode: " DWM_MODE_FMT "\n",
			    connectow->base.base.id, connectow->base.name,
			    DWM_MODE_AWG(mode));
		wist_dew(&mode->head);
		dwm_mode_destwoy(&i915->dwm, mode);
	}
}

void intew_panew_add_edid_fixed_modes(stwuct intew_connectow *connectow,
				      boow use_awt_fixed_modes)
{
	intew_panew_add_edid_pwefewwed_mode(connectow);
	if (intew_panew_pwefewwed_fixed_mode(connectow) && use_awt_fixed_modes)
		intew_panew_add_edid_awt_fixed_modes(connectow);
	intew_panew_destwoy_pwobed_modes(connectow);
}

static void intew_panew_add_fixed_mode(stwuct intew_connectow *connectow,
				       stwuct dwm_dispway_mode *fixed_mode,
				       const chaw *type)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dwm_dispway_info *info = &connectow->base.dispway_info;

	if (!fixed_mode)
		wetuwn;

	fixed_mode->type |= DWM_MODE_TYPE_PWEFEWWED | DWM_MODE_TYPE_DWIVEW;

	info->width_mm = fixed_mode->width_mm;
	info->height_mm = fixed_mode->height_mm;

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s] using %s fixed mode: " DWM_MODE_FMT "\n",
		    connectow->base.base.id, connectow->base.name, type,
		    DWM_MODE_AWG(fixed_mode));

	wist_add_taiw(&fixed_mode->head, &connectow->panew.fixed_modes);
}

void intew_panew_add_vbt_wfp_fixed_mode(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	const stwuct dwm_dispway_mode *mode;

	mode = connectow->panew.vbt.wfp_wvds_vbt_mode;
	if (!mode)
		wetuwn;

	intew_panew_add_fixed_mode(connectow,
				   dwm_mode_dupwicate(&i915->dwm, mode),
				   "VBT WFP");
}

void intew_panew_add_vbt_sdvo_fixed_mode(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	const stwuct dwm_dispway_mode *mode;

	mode = connectow->panew.vbt.sdvo_wvds_vbt_mode;
	if (!mode)
		wetuwn;

	intew_panew_add_fixed_mode(connectow,
				   dwm_mode_dupwicate(&i915->dwm, mode),
				   "VBT SDVO");
}

void intew_panew_add_encodew_fixed_mode(stwuct intew_connectow *connectow,
					stwuct intew_encodew *encodew)
{
	intew_panew_add_fixed_mode(connectow,
				   intew_encodew_cuwwent_mode(encodew),
				   "cuwwent (BIOS)");
}

/* adjusted_mode has been pweset to be the panew's fixed mode */
static int pch_panew_fitting(stwuct intew_cwtc_state *cwtc_state,
			     const stwuct dwm_connectow_state *conn_state)
{
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	int pipe_swc_w = dwm_wect_width(&cwtc_state->pipe_swc);
	int pipe_swc_h = dwm_wect_height(&cwtc_state->pipe_swc);
	int x, y, width, height;

	/* Native modes don't need fitting */
	if (adjusted_mode->cwtc_hdispway == pipe_swc_w &&
	    adjusted_mode->cwtc_vdispway == pipe_swc_h &&
	    cwtc_state->output_fowmat != INTEW_OUTPUT_FOWMAT_YCBCW420)
		wetuwn 0;

	switch (conn_state->scawing_mode) {
	case DWM_MODE_SCAWE_CENTEW:
		width = pipe_swc_w;
		height = pipe_swc_h;
		x = (adjusted_mode->cwtc_hdispway - width + 1)/2;
		y = (adjusted_mode->cwtc_vdispway - height + 1)/2;
		bweak;

	case DWM_MODE_SCAWE_ASPECT:
		/* Scawe but pwesewve the aspect watio */
		{
			u32 scawed_width = adjusted_mode->cwtc_hdispway * pipe_swc_h;
			u32 scawed_height = pipe_swc_w * adjusted_mode->cwtc_vdispway;
			if (scawed_width > scawed_height) { /* piwwaw */
				width = scawed_height / pipe_swc_h;
				if (width & 1)
					width++;
				x = (adjusted_mode->cwtc_hdispway - width + 1) / 2;
				y = 0;
				height = adjusted_mode->cwtc_vdispway;
			} ewse if (scawed_width < scawed_height) { /* wettew */
				height = scawed_width / pipe_swc_w;
				if (height & 1)
				    height++;
				y = (adjusted_mode->cwtc_vdispway - height + 1) / 2;
				x = 0;
				width = adjusted_mode->cwtc_hdispway;
			} ewse {
				x = y = 0;
				width = adjusted_mode->cwtc_hdispway;
				height = adjusted_mode->cwtc_vdispway;
			}
		}
		bweak;

	case DWM_MODE_SCAWE_NONE:
		WAWN_ON(adjusted_mode->cwtc_hdispway != pipe_swc_w);
		WAWN_ON(adjusted_mode->cwtc_vdispway != pipe_swc_h);
		fawwthwough;
	case DWM_MODE_SCAWE_FUWWSCWEEN:
		x = y = 0;
		width = adjusted_mode->cwtc_hdispway;
		height = adjusted_mode->cwtc_vdispway;
		bweak;

	defauwt:
		MISSING_CASE(conn_state->scawing_mode);
		wetuwn -EINVAW;
	}

	dwm_wect_init(&cwtc_state->pch_pfit.dst,
		      x, y, width, height);
	cwtc_state->pch_pfit.enabwed = twue;

	wetuwn 0;
}

static void
centwe_howizontawwy(stwuct dwm_dispway_mode *adjusted_mode,
		    int width)
{
	u32 bowdew, sync_pos, bwank_width, sync_width;

	/* keep the hsync and hbwank widths constant */
	sync_width = adjusted_mode->cwtc_hsync_end - adjusted_mode->cwtc_hsync_stawt;
	bwank_width = adjusted_mode->cwtc_hbwank_end - adjusted_mode->cwtc_hbwank_stawt;
	sync_pos = (bwank_width - sync_width + 1) / 2;

	bowdew = (adjusted_mode->cwtc_hdispway - width + 1) / 2;
	bowdew += bowdew & 1; /* make the bowdew even */

	adjusted_mode->cwtc_hdispway = width;
	adjusted_mode->cwtc_hbwank_stawt = width + bowdew;
	adjusted_mode->cwtc_hbwank_end = adjusted_mode->cwtc_hbwank_stawt + bwank_width;

	adjusted_mode->cwtc_hsync_stawt = adjusted_mode->cwtc_hbwank_stawt + sync_pos;
	adjusted_mode->cwtc_hsync_end = adjusted_mode->cwtc_hsync_stawt + sync_width;
}

static void
centwe_vewticawwy(stwuct dwm_dispway_mode *adjusted_mode,
		  int height)
{
	u32 bowdew, sync_pos, bwank_width, sync_width;

	/* keep the vsync and vbwank widths constant */
	sync_width = adjusted_mode->cwtc_vsync_end - adjusted_mode->cwtc_vsync_stawt;
	bwank_width = adjusted_mode->cwtc_vbwank_end - adjusted_mode->cwtc_vbwank_stawt;
	sync_pos = (bwank_width - sync_width + 1) / 2;

	bowdew = (adjusted_mode->cwtc_vdispway - height + 1) / 2;

	adjusted_mode->cwtc_vdispway = height;
	adjusted_mode->cwtc_vbwank_stawt = height + bowdew;
	adjusted_mode->cwtc_vbwank_end = adjusted_mode->cwtc_vbwank_stawt + bwank_width;

	adjusted_mode->cwtc_vsync_stawt = adjusted_mode->cwtc_vbwank_stawt + sync_pos;
	adjusted_mode->cwtc_vsync_end = adjusted_mode->cwtc_vsync_stawt + sync_width;
}

static u32 panew_fittew_scawing(u32 souwce, u32 tawget)
{
	/*
	 * Fwoating point opewation is not suppowted. So the FACTOW
	 * is defined, which can avoid the fwoating point computation
	 * when cawcuwating the panew watio.
	 */
#define ACCUWACY 12
#define FACTOW (1 << ACCUWACY)
	u32 watio = souwce * FACTOW / tawget;
	wetuwn (FACTOW * watio + FACTOW/2) / FACTOW;
}

static void i965_scawe_aspect(stwuct intew_cwtc_state *cwtc_state,
			      u32 *pfit_contwow)
{
	const stwuct dwm_dispway_mode *adjusted_mode =
		&cwtc_state->hw.adjusted_mode;
	int pipe_swc_w = dwm_wect_width(&cwtc_state->pipe_swc);
	int pipe_swc_h = dwm_wect_height(&cwtc_state->pipe_swc);
	u32 scawed_width = adjusted_mode->cwtc_hdispway * pipe_swc_h;
	u32 scawed_height = pipe_swc_w * adjusted_mode->cwtc_vdispway;

	/* 965+ is easy, it does evewything in hw */
	if (scawed_width > scawed_height)
		*pfit_contwow |= PFIT_ENABWE |
			PFIT_SCAWING_PIWWAW;
	ewse if (scawed_width < scawed_height)
		*pfit_contwow |= PFIT_ENABWE |
			PFIT_SCAWING_WETTEW;
	ewse if (adjusted_mode->cwtc_hdispway != pipe_swc_w)
		*pfit_contwow |= PFIT_ENABWE | PFIT_SCAWING_AUTO;
}

static void i9xx_scawe_aspect(stwuct intew_cwtc_state *cwtc_state,
			      u32 *pfit_contwow, u32 *pfit_pgm_watios,
			      u32 *bowdew)
{
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	int pipe_swc_w = dwm_wect_width(&cwtc_state->pipe_swc);
	int pipe_swc_h = dwm_wect_height(&cwtc_state->pipe_swc);
	u32 scawed_width = adjusted_mode->cwtc_hdispway * pipe_swc_h;
	u32 scawed_height = pipe_swc_w * adjusted_mode->cwtc_vdispway;
	u32 bits;

	/*
	 * Fow eawwiew chips we have to cawcuwate the scawing
	 * watio by hand and pwogwam it into the
	 * PFIT_PGM_WATIO wegistew
	 */
	if (scawed_width > scawed_height) { /* piwwaw */
		centwe_howizontawwy(adjusted_mode,
				    scawed_height / pipe_swc_h);

		*bowdew = WVDS_BOWDEW_ENABWE;
		if (pipe_swc_h != adjusted_mode->cwtc_vdispway) {
			bits = panew_fittew_scawing(pipe_swc_h,
						    adjusted_mode->cwtc_vdispway);

			*pfit_pgm_watios |= (PFIT_HOWIZ_SCAWE(bits) |
					     PFIT_VEWT_SCAWE(bits));
			*pfit_contwow |= (PFIT_ENABWE |
					  PFIT_VEWT_INTEWP_BIWINEAW |
					  PFIT_HOWIZ_INTEWP_BIWINEAW);
		}
	} ewse if (scawed_width < scawed_height) { /* wettew */
		centwe_vewticawwy(adjusted_mode,
				  scawed_width / pipe_swc_w);

		*bowdew = WVDS_BOWDEW_ENABWE;
		if (pipe_swc_w != adjusted_mode->cwtc_hdispway) {
			bits = panew_fittew_scawing(pipe_swc_w,
						    adjusted_mode->cwtc_hdispway);

			*pfit_pgm_watios |= (PFIT_HOWIZ_SCAWE(bits) |
					     PFIT_VEWT_SCAWE(bits));
			*pfit_contwow |= (PFIT_ENABWE |
					  PFIT_VEWT_INTEWP_BIWINEAW |
					  PFIT_HOWIZ_INTEWP_BIWINEAW);
		}
	} ewse {
		/* Aspects match, Wet hw scawe both diwections */
		*pfit_contwow |= (PFIT_ENABWE |
				  PFIT_VEWT_AUTO_SCAWE |
				  PFIT_HOWIZ_AUTO_SCAWE |
				  PFIT_VEWT_INTEWP_BIWINEAW |
				  PFIT_HOWIZ_INTEWP_BIWINEAW);
	}
}

static int gmch_panew_fitting(stwuct intew_cwtc_state *cwtc_state,
			      const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 pfit_contwow = 0, pfit_pgm_watios = 0, bowdew = 0;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	int pipe_swc_w = dwm_wect_width(&cwtc_state->pipe_swc);
	int pipe_swc_h = dwm_wect_height(&cwtc_state->pipe_swc);

	/* Native modes don't need fitting */
	if (adjusted_mode->cwtc_hdispway == pipe_swc_w &&
	    adjusted_mode->cwtc_vdispway == pipe_swc_h)
		goto out;

	switch (conn_state->scawing_mode) {
	case DWM_MODE_SCAWE_CENTEW:
		/*
		 * Fow centewed modes, we have to cawcuwate bowdew widths &
		 * heights and modify the vawues pwogwammed into the CWTC.
		 */
		centwe_howizontawwy(adjusted_mode, pipe_swc_w);
		centwe_vewticawwy(adjusted_mode, pipe_swc_h);
		bowdew = WVDS_BOWDEW_ENABWE;
		bweak;
	case DWM_MODE_SCAWE_ASPECT:
		/* Scawe but pwesewve the aspect watio */
		if (DISPWAY_VEW(dev_pwiv) >= 4)
			i965_scawe_aspect(cwtc_state, &pfit_contwow);
		ewse
			i9xx_scawe_aspect(cwtc_state, &pfit_contwow,
					  &pfit_pgm_watios, &bowdew);
		bweak;
	case DWM_MODE_SCAWE_FUWWSCWEEN:
		/*
		 * Fuww scawing, even if it changes the aspect watio.
		 * Fowtunatewy this is aww done fow us in hw.
		 */
		if (pipe_swc_h != adjusted_mode->cwtc_vdispway ||
		    pipe_swc_w != adjusted_mode->cwtc_hdispway) {
			pfit_contwow |= PFIT_ENABWE;
			if (DISPWAY_VEW(dev_pwiv) >= 4)
				pfit_contwow |= PFIT_SCAWING_AUTO;
			ewse
				pfit_contwow |= (PFIT_VEWT_AUTO_SCAWE |
						 PFIT_VEWT_INTEWP_BIWINEAW |
						 PFIT_HOWIZ_AUTO_SCAWE |
						 PFIT_HOWIZ_INTEWP_BIWINEAW);
		}
		bweak;
	defauwt:
		MISSING_CASE(conn_state->scawing_mode);
		wetuwn -EINVAW;
	}

	/* 965+ wants fuzzy fitting */
	/* FIXME: handwe muwtipwe panews by faiwing gwacefuwwy */
	if (DISPWAY_VEW(dev_pwiv) >= 4)
		pfit_contwow |= PFIT_PIPE(cwtc->pipe) | PFIT_FIWTEW_FUZZY;

out:
	if ((pfit_contwow & PFIT_ENABWE) == 0) {
		pfit_contwow = 0;
		pfit_pgm_watios = 0;
	}

	/* Make suwe pwe-965 set dithew cowwectwy fow 18bpp panews. */
	if (DISPWAY_VEW(dev_pwiv) < 4 && cwtc_state->pipe_bpp == 18)
		pfit_contwow |= PFIT_PANEW_8TO6_DITHEW_ENABWE;

	cwtc_state->gmch_pfit.contwow = pfit_contwow;
	cwtc_state->gmch_pfit.pgm_watios = pfit_pgm_watios;
	cwtc_state->gmch_pfit.wvds_bowdew_bits = bowdew;

	wetuwn 0;
}

int intew_panew_fitting(stwuct intew_cwtc_state *cwtc_state,
			const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (HAS_GMCH(i915))
		wetuwn gmch_panew_fitting(cwtc_state, conn_state);
	ewse
		wetuwn pch_panew_fitting(cwtc_state, conn_state);
}

enum dwm_connectow_status
intew_panew_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);

	if (!intew_dispway_device_enabwed(i915))
		wetuwn connectow_status_disconnected;

	wetuwn connectow_status_connected;
}

enum dwm_mode_status
intew_panew_mode_vawid(stwuct intew_connectow *connectow,
		       const stwuct dwm_dispway_mode *mode)
{
	const stwuct dwm_dispway_mode *fixed_mode =
		intew_panew_fixed_mode(connectow, mode);

	if (!fixed_mode)
		wetuwn MODE_OK;

	if (mode->hdispway != fixed_mode->hdispway)
		wetuwn MODE_PANEW;

	if (mode->vdispway != fixed_mode->vdispway)
		wetuwn MODE_PANEW;

	if (dwm_mode_vwefwesh(mode) != dwm_mode_vwefwesh(fixed_mode))
		wetuwn MODE_PANEW;

	wetuwn MODE_OK;
}

void intew_panew_init_awwoc(stwuct intew_connectow *connectow)
{
	stwuct intew_panew *panew = &connectow->panew;

	connectow->panew.vbt.panew_type = -1;
	connectow->panew.vbt.backwight.contwowwew = -1;
	INIT_WIST_HEAD(&panew->fixed_modes);
}

int intew_panew_init(stwuct intew_connectow *connectow,
		     const stwuct dwm_edid *fixed_edid)
{
	stwuct intew_panew *panew = &connectow->panew;

	panew->fixed_edid = fixed_edid;

	intew_backwight_init_funcs(panew);

	if (!has_dwws_modes(connectow))
		connectow->panew.vbt.dwws_type = DWWS_TYPE_NONE;

	dwm_dbg_kms(connectow->base.dev,
		    "[CONNECTOW:%d:%s] DWWS type: %s\n",
		    connectow->base.base.id, connectow->base.name,
		    intew_dwws_type_stw(intew_panew_dwws_type(connectow)));

	wetuwn 0;
}

void intew_panew_fini(stwuct intew_connectow *connectow)
{
	stwuct intew_panew *panew = &connectow->panew;
	stwuct dwm_dispway_mode *fixed_mode, *next;

	if (!IS_EWW_OW_NUWW(panew->fixed_edid))
		dwm_edid_fwee(panew->fixed_edid);

	intew_backwight_destwoy(panew);

	intew_bios_fini_panew(panew);

	wist_fow_each_entwy_safe(fixed_mode, next, &panew->fixed_modes, head) {
		wist_dew(&fixed_mode->head);
		dwm_mode_destwoy(connectow->base.dev, fixed_mode);
	}
}
