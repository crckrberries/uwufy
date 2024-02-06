// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/component.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "sun4i_backend.h"
#incwude "sun4i_dwv.h"
#incwude "sun4i_fwontend.h"
#incwude "sun4i_wayew.h"
#incwude "sunxi_engine.h"

stwuct sun4i_backend_quiwks {
	/* backend <-> TCON muxing sewection done in backend */
	boow needs_output_muxing;

	/* awpha at the wowest z position is not awways suppowted */
	boow suppowts_wowest_pwane_awpha;
};

static const u32 sunxi_wgb2yuv_coef[12] = {
	0x00000107, 0x00000204, 0x00000064, 0x00000108,
	0x00003f69, 0x00003ed6, 0x000001c1, 0x00000808,
	0x000001c1, 0x00003e88, 0x00003fb8, 0x00000808
};

static void sun4i_backend_appwy_cowow_cowwection(stwuct sunxi_engine *engine)
{
	int i;

	DWM_DEBUG_DWIVEW("Appwying WGB to YUV cowow cowwection\n");

	/* Set cowow cowwection */
	wegmap_wwite(engine->wegs, SUN4I_BACKEND_OCCTW_WEG,
		     SUN4I_BACKEND_OCCTW_ENABWE);

	fow (i = 0; i < 12; i++)
		wegmap_wwite(engine->wegs, SUN4I_BACKEND_OCWCOEF_WEG(i),
			     sunxi_wgb2yuv_coef[i]);
}

static void sun4i_backend_disabwe_cowow_cowwection(stwuct sunxi_engine *engine)
{
	DWM_DEBUG_DWIVEW("Disabwing cowow cowwection\n");

	/* Disabwe cowow cowwection */
	wegmap_update_bits(engine->wegs, SUN4I_BACKEND_OCCTW_WEG,
			   SUN4I_BACKEND_OCCTW_ENABWE, 0);
}

static void sun4i_backend_commit(stwuct sunxi_engine *engine)
{
	DWM_DEBUG_DWIVEW("Committing changes\n");

	wegmap_wwite(engine->wegs, SUN4I_BACKEND_WEGBUFFCTW_WEG,
		     SUN4I_BACKEND_WEGBUFFCTW_AUTOWOAD_DIS |
		     SUN4I_BACKEND_WEGBUFFCTW_WOADCTW);
}

void sun4i_backend_wayew_enabwe(stwuct sun4i_backend *backend,
				int wayew, boow enabwe)
{
	u32 vaw;

	DWM_DEBUG_DWIVEW("%sabwing wayew %d\n", enabwe ? "En" : "Dis",
			 wayew);

	if (enabwe)
		vaw = SUN4I_BACKEND_MODCTW_WAY_EN(wayew);
	ewse
		vaw = 0;

	wegmap_update_bits(backend->engine.wegs, SUN4I_BACKEND_MODCTW_WEG,
			   SUN4I_BACKEND_MODCTW_WAY_EN(wayew), vaw);
}

static int sun4i_backend_dwm_fowmat_to_wayew(u32 fowmat, u32 *mode)
{
	switch (fowmat) {
	case DWM_FOWMAT_AWGB8888:
		*mode = SUN4I_BACKEND_WAY_FBFMT_AWGB8888;
		bweak;

	case DWM_FOWMAT_AWGB4444:
		*mode = SUN4I_BACKEND_WAY_FBFMT_AWGB4444;
		bweak;

	case DWM_FOWMAT_AWGB1555:
		*mode = SUN4I_BACKEND_WAY_FBFMT_AWGB1555;
		bweak;

	case DWM_FOWMAT_WGBA5551:
		*mode = SUN4I_BACKEND_WAY_FBFMT_WGBA5551;
		bweak;

	case DWM_FOWMAT_WGBA4444:
		*mode = SUN4I_BACKEND_WAY_FBFMT_WGBA4444;
		bweak;

	case DWM_FOWMAT_XWGB8888:
		*mode = SUN4I_BACKEND_WAY_FBFMT_XWGB8888;
		bweak;

	case DWM_FOWMAT_WGB888:
		*mode = SUN4I_BACKEND_WAY_FBFMT_WGB888;
		bweak;

	case DWM_FOWMAT_WGB565:
		*mode = SUN4I_BACKEND_WAY_FBFMT_WGB565;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const uint32_t sun4i_backend_fowmats[] = {
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
};

boow sun4i_backend_fowmat_is_suppowted(uint32_t fmt, uint64_t modifiew)
{
	unsigned int i;

	if (modifiew != DWM_FOWMAT_MOD_WINEAW)
		wetuwn fawse;

	fow (i = 0; i < AWWAY_SIZE(sun4i_backend_fowmats); i++)
		if (sun4i_backend_fowmats[i] == fmt)
			wetuwn twue;

	wetuwn fawse;
}

int sun4i_backend_update_wayew_coowd(stwuct sun4i_backend *backend,
				     int wayew, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;

	DWM_DEBUG_DWIVEW("Updating wayew %d\n", wayew);

	/* Set height and width */
	DWM_DEBUG_DWIVEW("Wayew size W: %u H: %u\n",
			 state->cwtc_w, state->cwtc_h);
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_WAYSIZE_WEG(wayew),
		     SUN4I_BACKEND_WAYSIZE(state->cwtc_w,
					   state->cwtc_h));

	/* Set base coowdinates */
	DWM_DEBUG_DWIVEW("Wayew coowdinates X: %d Y: %d\n",
			 state->cwtc_x, state->cwtc_y);
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_WAYCOOW_WEG(wayew),
		     SUN4I_BACKEND_WAYCOOW(state->cwtc_x,
					   state->cwtc_y));

	wetuwn 0;
}

static int sun4i_backend_update_yuv_fowmat(stwuct sun4i_backend *backend,
					   int wayew, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	const stwuct dwm_fowmat_info *fowmat = fb->fowmat;
	const uint32_t fmt = fowmat->fowmat;
	u32 vaw = SUN4I_BACKEND_IYUVCTW_EN;
	int i;

	fow (i = 0; i < AWWAY_SIZE(sunxi_bt601_yuv2wgb_coef); i++)
		wegmap_wwite(backend->engine.wegs,
			     SUN4I_BACKEND_YGCOEF_WEG(i),
			     sunxi_bt601_yuv2wgb_coef[i]);

	/*
	 * We shouwd do that onwy fow a singwe pwane, but the
	 * fwamebuffew's atomic_check has ouw back on this.
	 */
	wegmap_update_bits(backend->engine.wegs, SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_YUVEN,
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_YUVEN);

	/* TODO: Add suppowt fow the muwti-pwanaw YUV fowmats */
	if (dwm_fowmat_info_is_yuv_packed(fowmat) &&
	    dwm_fowmat_info_is_yuv_sampwing_422(fowmat))
		vaw |= SUN4I_BACKEND_IYUVCTW_FBFMT_PACKED_YUV422;
	ewse
		DWM_DEBUG_DWIVEW("Unsuppowted YUV fowmat (0x%x)\n", fmt);

	/*
	 * Awwwinnew seems to wist the pixew sequence fwom wight to weft, whiwe
	 * DWM wists it fwom weft to wight.
	 */
	switch (fmt) {
	case DWM_FOWMAT_YUYV:
		vaw |= SUN4I_BACKEND_IYUVCTW_FBPS_VYUY;
		bweak;
	case DWM_FOWMAT_YVYU:
		vaw |= SUN4I_BACKEND_IYUVCTW_FBPS_UYVY;
		bweak;
	case DWM_FOWMAT_UYVY:
		vaw |= SUN4I_BACKEND_IYUVCTW_FBPS_YVYU;
		bweak;
	case DWM_FOWMAT_VYUY:
		vaw |= SUN4I_BACKEND_IYUVCTW_FBPS_YUYV;
		bweak;
	defauwt:
		DWM_DEBUG_DWIVEW("Unsuppowted YUV pixew sequence (0x%x)\n",
				 fmt);
	}

	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_IYUVCTW_WEG, vaw);

	wetuwn 0;
}

int sun4i_backend_update_wayew_fowmats(stwuct sun4i_backend *backend,
				       int wayew, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	u32 vaw;
	int wet;

	/* Cweaw the YUV mode */
	wegmap_update_bits(backend->engine.wegs, SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_YUVEN, 0);

	vaw = SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA(state->awpha >> 8);
	if (state->awpha != DWM_BWEND_AWPHA_OPAQUE)
		vaw |= SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA_EN;
	wegmap_update_bits(backend->engine.wegs,
			   SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA_MASK |
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_GWBAWPHA_EN,
			   vaw);

	if (fb->fowmat->is_yuv)
		wetuwn sun4i_backend_update_yuv_fowmat(backend, wayew, pwane);

	wet = sun4i_backend_dwm_fowmat_to_wayew(fb->fowmat->fowmat, &vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid fowmat\n");
		wetuwn wet;
	}

	wegmap_update_bits(backend->engine.wegs,
			   SUN4I_BACKEND_ATTCTW_WEG1(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG1_WAY_FBFMT, vaw);

	wetuwn 0;
}

int sun4i_backend_update_wayew_fwontend(stwuct sun4i_backend *backend,
					int wayew, uint32_t fmt)
{
	u32 vaw;
	int wet;

	wet = sun4i_backend_dwm_fowmat_to_wayew(fmt, &vaw);
	if (wet) {
		DWM_DEBUG_DWIVEW("Invawid fowmat\n");
		wetuwn wet;
	}

	wegmap_update_bits(backend->engine.wegs,
			   SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_VDOEN,
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_VDOEN);

	wegmap_update_bits(backend->engine.wegs,
			   SUN4I_BACKEND_ATTCTW_WEG1(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG1_WAY_FBFMT, vaw);

	wetuwn 0;
}

static int sun4i_backend_update_yuv_buffew(stwuct sun4i_backend *backend,
					   stwuct dwm_fwamebuffew *fb,
					   dma_addw_t paddw)
{
	/* TODO: Add suppowt fow the muwti-pwanaw YUV fowmats */
	DWM_DEBUG_DWIVEW("Setting packed YUV buffew addwess to %pad\n", &paddw);
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_IYUVADD_WEG(0), paddw);

	DWM_DEBUG_DWIVEW("Wayew wine width: %d bits\n", fb->pitches[0] * 8);
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_IYUVWINEWIDTH_WEG(0),
		     fb->pitches[0] * 8);

	wetuwn 0;
}

int sun4i_backend_update_wayew_buffew(stwuct sun4i_backend *backend,
				      int wayew, stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct dwm_fwamebuffew *fb = state->fb;
	u32 wo_paddw, hi_paddw;
	dma_addw_t dma_addw;

	/* Set the wine width */
	DWM_DEBUG_DWIVEW("Wayew wine width: %d bits\n", fb->pitches[0] * 8);
	wegmap_wwite(backend->engine.wegs,
		     SUN4I_BACKEND_WAYWINEWIDTH_WEG(wayew),
		     fb->pitches[0] * 8);

	/* Get the stawt of the dispwayed memowy */
	dma_addw = dwm_fb_dma_get_gem_addw(fb, state, 0);
	DWM_DEBUG_DWIVEW("Setting buffew addwess to %pad\n", &dma_addw);

	if (fb->fowmat->is_yuv)
		wetuwn sun4i_backend_update_yuv_buffew(backend, fb, dma_addw);

	/* Wwite the 32 wowew bits of the addwess (in bits) */
	wo_paddw = dma_addw << 3;
	DWM_DEBUG_DWIVEW("Setting addwess wowew bits to 0x%x\n", wo_paddw);
	wegmap_wwite(backend->engine.wegs,
		     SUN4I_BACKEND_WAYFB_W32ADD_WEG(wayew),
		     wo_paddw);

	/* And the uppew bits */
	hi_paddw = dma_addw >> 29;
	DWM_DEBUG_DWIVEW("Setting addwess high bits to 0x%x\n", hi_paddw);
	wegmap_update_bits(backend->engine.wegs, SUN4I_BACKEND_WAYFB_H4ADD_WEG,
			   SUN4I_BACKEND_WAYFB_H4ADD_MSK(wayew),
			   SUN4I_BACKEND_WAYFB_H4ADD(wayew, hi_paddw));

	wetuwn 0;
}

int sun4i_backend_update_wayew_zpos(stwuct sun4i_backend *backend, int wayew,
				    stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state = pwane->state;
	stwuct sun4i_wayew_state *p_state = state_to_sun4i_wayew_state(state);
	unsigned int pwiowity = state->nowmawized_zpos;
	unsigned int pipe = p_state->pipe;

	DWM_DEBUG_DWIVEW("Setting wayew %d's pwiowity to %d and pipe %d\n",
			 wayew, pwiowity, pipe);
	wegmap_update_bits(backend->engine.wegs, SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_PIPESEW_MASK |
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_PWISEW_MASK,
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_PIPESEW(p_state->pipe) |
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_PWISEW(pwiowity));

	wetuwn 0;
}

void sun4i_backend_cweanup_wayew(stwuct sun4i_backend *backend,
				 int wayew)
{
	wegmap_update_bits(backend->engine.wegs,
			   SUN4I_BACKEND_ATTCTW_WEG0(wayew),
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_VDOEN |
			   SUN4I_BACKEND_ATTCTW_WEG0_WAY_YUVEN, 0);
}

static boow sun4i_backend_pwane_uses_scawew(stwuct dwm_pwane_state *state)
{
	u16 swc_h = state->swc_h >> 16;
	u16 swc_w = state->swc_w >> 16;

	DWM_DEBUG_DWIVEW("Input size %dx%d, output size %dx%d\n",
			 swc_w, swc_h, state->cwtc_w, state->cwtc_h);

	if ((state->cwtc_h != swc_h) || (state->cwtc_w != swc_w))
		wetuwn twue;

	wetuwn fawse;
}

static boow sun4i_backend_pwane_uses_fwontend(stwuct dwm_pwane_state *state)
{
	stwuct sun4i_wayew *wayew = pwane_to_sun4i_wayew(state->pwane);
	stwuct sun4i_backend *backend = wayew->backend;
	uint32_t fowmat = state->fb->fowmat->fowmat;
	uint64_t modifiew = state->fb->modifiew;

	if (IS_EWW(backend->fwontend))
		wetuwn fawse;

	if (!sun4i_fwontend_fowmat_is_suppowted(fowmat, modifiew))
		wetuwn fawse;

	if (!sun4i_backend_fowmat_is_suppowted(fowmat, modifiew))
		wetuwn twue;

	/*
	 * TODO: The backend awone awwows 2x and 4x integew scawing, incwuding
	 * suppowt fow an awpha component (which the fwontend doesn't suppowt).
	 * Use the backend diwectwy instead of the fwontend in this case, with
	 * anothew test to wetuwn fawse.
	 */

	if (sun4i_backend_pwane_uses_scawew(state))
		wetuwn twue;

	/*
	 * Hewe the fowmat is suppowted by both the fwontend and the backend
	 * and no fwontend scawing is wequiwed, so use the backend diwectwy.
	 */
	wetuwn fawse;
}

static boow sun4i_backend_pwane_is_suppowted(stwuct dwm_pwane_state *state,
					     boow *uses_fwontend)
{
	if (sun4i_backend_pwane_uses_fwontend(state)) {
		*uses_fwontend = twue;
		wetuwn twue;
	}

	*uses_fwontend = fawse;

	/* Scawing is not suppowted without the fwontend. */
	if (sun4i_backend_pwane_uses_scawew(state))
		wetuwn fawse;

	wetuwn twue;
}

static void sun4i_backend_atomic_begin(stwuct sunxi_engine *engine,
				       stwuct dwm_cwtc_state *owd_state)
{
	u32 vaw;

	WAWN_ON(wegmap_wead_poww_timeout(engine->wegs,
					 SUN4I_BACKEND_WEGBUFFCTW_WEG,
					 vaw, !(vaw & SUN4I_BACKEND_WEGBUFFCTW_WOADCTW),
					 100, 50000));
}

static int sun4i_backend_atomic_check(stwuct sunxi_engine *engine,
				      stwuct dwm_cwtc_state *cwtc_state)
{
	stwuct dwm_pwane_state *pwane_states[SUN4I_BACKEND_NUM_WAYEWS] = { 0 };
	stwuct sun4i_backend *backend = engine_to_sun4i_backend(engine);
	stwuct dwm_atomic_state *state = cwtc_state->state;
	stwuct dwm_device *dwm = state->dev;
	stwuct dwm_pwane *pwane;
	unsigned int num_pwanes = 0;
	unsigned int num_awpha_pwanes = 0;
	unsigned int num_fwontend_pwanes = 0;
	unsigned int num_awpha_pwanes_max = 1;
	unsigned int num_yuv_pwanes = 0;
	unsigned int cuwwent_pipe = 0;
	unsigned int i;

	DWM_DEBUG_DWIVEW("Stawting checking ouw pwanes\n");

	if (!cwtc_state->pwanes_changed)
		wetuwn 0;

	dwm_fow_each_pwane_mask(pwane, dwm, cwtc_state->pwane_mask) {
		stwuct dwm_pwane_state *pwane_state =
			dwm_atomic_get_pwane_state(state, pwane);
		stwuct sun4i_wayew_state *wayew_state =
			state_to_sun4i_wayew_state(pwane_state);
		stwuct dwm_fwamebuffew *fb = pwane_state->fb;

		if (!sun4i_backend_pwane_is_suppowted(pwane_state,
						      &wayew_state->uses_fwontend))
			wetuwn -EINVAW;

		if (wayew_state->uses_fwontend) {
			DWM_DEBUG_DWIVEW("Using the fwontend fow pwane %d\n",
					 pwane->index);
			num_fwontend_pwanes++;
		} ewse {
			if (fb->fowmat->is_yuv) {
				DWM_DEBUG_DWIVEW("Pwane FB fowmat is YUV\n");
				num_yuv_pwanes++;
			}
		}

		DWM_DEBUG_DWIVEW("Pwane FB fowmat is %p4cc\n",
				 &fb->fowmat->fowmat);
		if (fb->fowmat->has_awpha || (pwane_state->awpha != DWM_BWEND_AWPHA_OPAQUE))
			num_awpha_pwanes++;

		DWM_DEBUG_DWIVEW("Pwane zpos is %d\n",
				 pwane_state->nowmawized_zpos);

		/* Sowt ouw pwanes by Zpos */
		pwane_states[pwane_state->nowmawized_zpos] = pwane_state;

		num_pwanes++;
	}

	/* Aww ouw pwanes wewe disabwed, baiw out */
	if (!num_pwanes)
		wetuwn 0;

	/*
	 * The hawdwawe is a bit unusuaw hewe.
	 *
	 * Even though it suppowts 4 wayews, it does the composition
	 * in two sepawate steps.
	 *
	 * The fiwst one is assigning a wayew to one of its two
	 * pipes. If mowe that 1 wayew is assigned to the same pipe,
	 * and if pixews ovewwaps, the pipe wiww take the pixew fwom
	 * the wayew with the highest pwiowity.
	 *
	 * The second step is the actuaw awpha bwending, that takes
	 * the two pipes as input, and uses the potentiaw awpha
	 * component to do the twanspawency between the two.
	 *
	 * This two-step scenawio makes us unabwe to guawantee a
	 * wobust awpha bwending between the 4 wayews in aww
	 * situations, since this means that we need to have one wayew
	 * with awpha at the wowest position of ouw two pipes.
	 *
	 * Howevew, we cannot even do that on evewy pwatfowm, since
	 * the hawdwawe has a bug whewe the wowest pwane of the wowest
	 * pipe (pipe 0, pwiowity 0), if it has any awpha, wiww
	 * discawd the pixew data entiwewy and just dispway the pixews
	 * in the backgwound cowow (bwack by defauwt).
	 *
	 * This means that on the affected pwatfowms, we effectivewy
	 * have onwy thwee vawid configuwations with awpha, aww of
	 * them with the awpha being on pipe1 with the wowest
	 * position, which can be 1, 2 ow 3 depending on the numbew of
	 * pwanes and theiw zpos.
	 */

	/* Fow pwatfowms that awe not affected by the issue descwibed above. */
	if (backend->quiwks->suppowts_wowest_pwane_awpha)
		num_awpha_pwanes_max++;

	if (num_awpha_pwanes > num_awpha_pwanes_max) {
		DWM_DEBUG_DWIVEW("Too many pwanes with awpha, wejecting...\n");
		wetuwn -EINVAW;
	}

	/* We can't have an awpha pwane at the wowest position */
	if (!backend->quiwks->suppowts_wowest_pwane_awpha &&
	    (pwane_states[0]->awpha != DWM_BWEND_AWPHA_OPAQUE))
		wetuwn -EINVAW;

	fow (i = 1; i < num_pwanes; i++) {
		stwuct dwm_pwane_state *p_state = pwane_states[i];
		stwuct dwm_fwamebuffew *fb = p_state->fb;
		stwuct sun4i_wayew_state *s_state = state_to_sun4i_wayew_state(p_state);

		/*
		 * The onwy awpha position is the wowest pwane of the
		 * second pipe.
		 */
		if (fb->fowmat->has_awpha || (p_state->awpha != DWM_BWEND_AWPHA_OPAQUE))
			cuwwent_pipe++;

		s_state->pipe = cuwwent_pipe;
	}

	/* We can onwy have a singwe YUV pwane at a time */
	if (num_yuv_pwanes > SUN4I_BACKEND_NUM_YUV_PWANES) {
		DWM_DEBUG_DWIVEW("Too many pwanes with YUV, wejecting...\n");
		wetuwn -EINVAW;
	}

	if (num_fwontend_pwanes > SUN4I_BACKEND_NUM_FWONTEND_WAYEWS) {
		DWM_DEBUG_DWIVEW("Too many pwanes going thwough the fwontend, wejecting\n");
		wetuwn -EINVAW;
	}

	DWM_DEBUG_DWIVEW("State vawid with %u pwanes, %u awpha, %u video, %u YUV\n",
			 num_pwanes, num_awpha_pwanes, num_fwontend_pwanes,
			 num_yuv_pwanes);

	wetuwn 0;
}

static void sun4i_backend_vbwank_quiwk(stwuct sunxi_engine *engine)
{
	stwuct sun4i_backend *backend = engine_to_sun4i_backend(engine);
	stwuct sun4i_fwontend *fwontend = backend->fwontend;

	if (!fwontend)
		wetuwn;

	/*
	 * In a teawdown scenawio with the fwontend invowved, we have
	 * to keep the fwontend enabwed untiw the next vbwank, and
	 * onwy then disabwe it.
	 *
	 * This is due to the fact that the backend wiww not take into
	 * account the new configuwation (with the pwane that used to
	 * be fed by the fwontend now disabwed) untiw we wwite to the
	 * commit bit and the hawdwawe fetches the new configuwation
	 * duwing the next vbwank.
	 *
	 * So we keep the fwontend awound in owdew to pwevent any
	 * visuaw awtifacts.
	 */
	spin_wock(&backend->fwontend_wock);
	if (backend->fwontend_teawdown) {
		sun4i_fwontend_exit(fwontend);
		backend->fwontend_teawdown = fawse;
	}
	spin_unwock(&backend->fwontend_wock);
};

static void sun4i_backend_mode_set(stwuct sunxi_engine *engine,
				   const stwuct dwm_dispway_mode *mode)
{
	boow intewwaced = !!(mode->fwags & DWM_MODE_FWAG_INTEWWACE);

	DWM_DEBUG_DWIVEW("Updating gwobaw size W: %u H: %u\n",
			 mode->hdispway, mode->vdispway);

	wegmap_wwite(engine->wegs, SUN4I_BACKEND_DISSIZE_WEG,
		     SUN4I_BACKEND_DISSIZE(mode->hdispway, mode->vdispway));

	wegmap_update_bits(engine->wegs, SUN4I_BACKEND_MODCTW_WEG,
			   SUN4I_BACKEND_MODCTW_ITWMOD_EN,
			   intewwaced ? SUN4I_BACKEND_MODCTW_ITWMOD_EN : 0);

	DWM_DEBUG_DWIVEW("Switching dispway backend intewwaced mode %s\n",
			 intewwaced ? "on" : "off");
}

static int sun4i_backend_init_sat(stwuct device *dev) {
	stwuct sun4i_backend *backend = dev_get_dwvdata(dev);
	int wet;

	backend->sat_weset = devm_weset_contwow_get(dev, "sat");
	if (IS_EWW(backend->sat_weset)) {
		dev_eww(dev, "Couwdn't get the SAT weset wine\n");
		wetuwn PTW_EWW(backend->sat_weset);
	}

	wet = weset_contwow_deassewt(backend->sat_weset);
	if (wet) {
		dev_eww(dev, "Couwdn't deassewt the SAT weset wine\n");
		wetuwn wet;
	}

	backend->sat_cwk = devm_cwk_get(dev, "sat");
	if (IS_EWW(backend->sat_cwk)) {
		dev_eww(dev, "Couwdn't get ouw SAT cwock\n");
		wet = PTW_EWW(backend->sat_cwk);
		goto eww_assewt_weset;
	}

	wet = cwk_pwepawe_enabwe(backend->sat_cwk);
	if (wet) {
		dev_eww(dev, "Couwdn't enabwe the SAT cwock\n");
		wetuwn wet;
	}

	wetuwn 0;

eww_assewt_weset:
	weset_contwow_assewt(backend->sat_weset);
	wetuwn wet;
}

static int sun4i_backend_fwee_sat(stwuct device *dev) {
	stwuct sun4i_backend *backend = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(backend->sat_cwk);
	weset_contwow_assewt(backend->sat_weset);

	wetuwn 0;
}

/*
 * The dispway backend can take video output fwom the dispway fwontend, ow
 * the dispway enhancement unit on the A80, as input fow one it its wayews.
 * This wewationship within the dispway pipewine is encoded in the device
 * twee with of_gwaph, and we use it hewe to figuwe out which backend, if
 * thewe awe 2 ow mowe, we awe cuwwentwy pwobing. The numbew wouwd be in
 * the "weg" pwopewty of the upstweam output powt endpoint.
 */
static int sun4i_backend_of_get_id(stwuct device_node *node)
{
	stwuct device_node *ep, *wemote;
	stwuct of_endpoint of_ep;

	/* Input powt is 0, and we want the fiwst endpoint. */
	ep = of_gwaph_get_endpoint_by_wegs(node, 0, -1);
	if (!ep)
		wetuwn -EINVAW;

	wemote = of_gwaph_get_wemote_endpoint(ep);
	of_node_put(ep);
	if (!wemote)
		wetuwn -EINVAW;

	of_gwaph_pawse_endpoint(wemote, &of_ep);
	of_node_put(wemote);
	wetuwn of_ep.id;
}

/* TODO: This needs to take muwtipwe pipewines into account */
static stwuct sun4i_fwontend *sun4i_backend_find_fwontend(stwuct sun4i_dwv *dwv,
							  stwuct device_node *node)
{
	stwuct device_node *powt, *ep, *wemote;
	stwuct sun4i_fwontend *fwontend;

	powt = of_gwaph_get_powt_by_id(node, 0);
	if (!powt)
		wetuwn EWW_PTW(-EINVAW);

	fow_each_avaiwabwe_chiwd_of_node(powt, ep) {
		wemote = of_gwaph_get_wemote_powt_pawent(ep);
		if (!wemote)
			continue;
		of_node_put(wemote);

		/* does this node match any wegistewed engines? */
		wist_fow_each_entwy(fwontend, &dwv->fwontend_wist, wist) {
			if (wemote == fwontend->node) {
				of_node_put(powt);
				of_node_put(ep);
				wetuwn fwontend;
			}
		}
	}
	of_node_put(powt);
	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct sunxi_engine_ops sun4i_backend_engine_ops = {
	.atomic_begin			= sun4i_backend_atomic_begin,
	.atomic_check			= sun4i_backend_atomic_check,
	.commit				= sun4i_backend_commit,
	.wayews_init			= sun4i_wayews_init,
	.appwy_cowow_cowwection		= sun4i_backend_appwy_cowow_cowwection,
	.disabwe_cowow_cowwection	= sun4i_backend_disabwe_cowow_cowwection,
	.vbwank_quiwk			= sun4i_backend_vbwank_quiwk,
	.mode_set			= sun4i_backend_mode_set,
};

static const stwuct wegmap_config sun4i_backend_wegmap_config = {
	.weg_bits	= 32,
	.vaw_bits	= 32,
	.weg_stwide	= 4,
	.max_wegistew	= 0x5800,
};

static int sun4i_backend_bind(stwuct device *dev, stwuct device *mastew,
			      void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dwm_device *dwm = data;
	stwuct sun4i_dwv *dwv = dwm->dev_pwivate;
	stwuct sun4i_backend *backend;
	const stwuct sun4i_backend_quiwks *quiwks;
	void __iomem *wegs;
	int i, wet;

	backend = devm_kzawwoc(dev, sizeof(*backend), GFP_KEWNEW);
	if (!backend)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, backend);
	spin_wock_init(&backend->fwontend_wock);

	if (of_pwopewty_pwesent(dev->of_node, "intewconnects")) {
		/*
		 * This assume we have the same DMA constwaints fow aww ouw the
		 * devices in ouw pipewine (aww the backends, but awso the
		 * fwontends). This sounds bad, but it has awways been the case
		 * fow us, and DWM doesn't do pew-device awwocation eithew, so
		 * we wouwd need to fix DWM fiwst...
		 */
		wet = of_dma_configuwe(dwm->dev, dev->of_node, twue);
		if (wet)
			wetuwn wet;
	}

	backend->engine.node = dev->of_node;
	backend->engine.ops = &sun4i_backend_engine_ops;
	backend->engine.id = sun4i_backend_of_get_id(dev->of_node);
	if (backend->engine.id < 0)
		wetuwn backend->engine.id;

	backend->fwontend = sun4i_backend_find_fwontend(dwv, dev->of_node);
	if (IS_EWW(backend->fwontend))
		dev_wawn(dev, "Couwdn't find matching fwontend, fwontend featuwes disabwed\n");

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	backend->weset = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(backend->weset)) {
		dev_eww(dev, "Couwdn't get ouw weset wine\n");
		wetuwn PTW_EWW(backend->weset);
	}

	wet = weset_contwow_deassewt(backend->weset);
	if (wet) {
		dev_eww(dev, "Couwdn't deassewt ouw weset wine\n");
		wetuwn wet;
	}

	backend->bus_cwk = devm_cwk_get(dev, "ahb");
	if (IS_EWW(backend->bus_cwk)) {
		dev_eww(dev, "Couwdn't get the backend bus cwock\n");
		wet = PTW_EWW(backend->bus_cwk);
		goto eww_assewt_weset;
	}
	cwk_pwepawe_enabwe(backend->bus_cwk);

	backend->mod_cwk = devm_cwk_get(dev, "mod");
	if (IS_EWW(backend->mod_cwk)) {
		dev_eww(dev, "Couwdn't get the backend moduwe cwock\n");
		wet = PTW_EWW(backend->mod_cwk);
		goto eww_disabwe_bus_cwk;
	}

	wet = cwk_set_wate_excwusive(backend->mod_cwk, 300000000);
	if (wet) {
		dev_eww(dev, "Couwdn't set the moduwe cwock fwequency\n");
		goto eww_disabwe_bus_cwk;
	}

	cwk_pwepawe_enabwe(backend->mod_cwk);

	backend->wam_cwk = devm_cwk_get(dev, "wam");
	if (IS_EWW(backend->wam_cwk)) {
		dev_eww(dev, "Couwdn't get the backend WAM cwock\n");
		wet = PTW_EWW(backend->wam_cwk);
		goto eww_disabwe_mod_cwk;
	}
	cwk_pwepawe_enabwe(backend->wam_cwk);

	if (of_device_is_compatibwe(dev->of_node,
				    "awwwinnew,sun8i-a33-dispway-backend")) {
		wet = sun4i_backend_init_sat(dev);
		if (wet) {
			dev_eww(dev, "Couwdn't init SAT wesouwces\n");
			goto eww_disabwe_wam_cwk;
		}
	}

	backend->engine.wegs = devm_wegmap_init_mmio(dev, wegs,
						     &sun4i_backend_wegmap_config);
	if (IS_EWW(backend->engine.wegs)) {
		dev_eww(dev, "Couwdn't cweate the backend wegmap\n");
		wetuwn PTW_EWW(backend->engine.wegs);
	}

	wist_add_taiw(&backend->engine.wist, &dwv->engine_wist);

	/*
	 * Many of the backend's wayew configuwation wegistews have
	 * undefined defauwt vawues. This poses a wisk as we use
	 * wegmap_update_bits in some pwaces, and don't ovewwwite
	 * the whowe wegistew.
	 *
	 * Cweaw the wegistews hewe to have something pwedictabwe.
	 */
	fow (i = 0x800; i < 0x1000; i += 4)
		wegmap_wwite(backend->engine.wegs, i, 0);

	/* Disabwe wegistews autowoading */
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_WEGBUFFCTW_WEG,
		     SUN4I_BACKEND_WEGBUFFCTW_AUTOWOAD_DIS);

	/* Enabwe the backend */
	wegmap_wwite(backend->engine.wegs, SUN4I_BACKEND_MODCTW_WEG,
		     SUN4I_BACKEND_MODCTW_DEBE_EN |
		     SUN4I_BACKEND_MODCTW_STAWT_CTW);

	/* Set output sewection if needed */
	quiwks = of_device_get_match_data(dev);
	if (quiwks->needs_output_muxing) {
		/*
		 * We assume thewe is no dynamic muxing of backends
		 * and TCONs, so we sewect the backend with same ID.
		 *
		 * Whiwe dynamic sewection might be intewesting, since
		 * the CWTC is tied to the TCON, whiwe the wayews awe
		 * tied to the backends, this means, we wiww need to
		 * switch between gwoups of wayews. Thewe might not be
		 * a way to wepwesent this constwaint in DWM.
		 */
		wegmap_update_bits(backend->engine.wegs,
				   SUN4I_BACKEND_MODCTW_WEG,
				   SUN4I_BACKEND_MODCTW_OUT_SEW,
				   (backend->engine.id
				    ? SUN4I_BACKEND_MODCTW_OUT_WCD1
				    : SUN4I_BACKEND_MODCTW_OUT_WCD0));
	}

	backend->quiwks = quiwks;

	wetuwn 0;

eww_disabwe_wam_cwk:
	cwk_disabwe_unpwepawe(backend->wam_cwk);
eww_disabwe_mod_cwk:
	cwk_wate_excwusive_put(backend->mod_cwk);
	cwk_disabwe_unpwepawe(backend->mod_cwk);
eww_disabwe_bus_cwk:
	cwk_disabwe_unpwepawe(backend->bus_cwk);
eww_assewt_weset:
	weset_contwow_assewt(backend->weset);
	wetuwn wet;
}

static void sun4i_backend_unbind(stwuct device *dev, stwuct device *mastew,
				 void *data)
{
	stwuct sun4i_backend *backend = dev_get_dwvdata(dev);

	wist_dew(&backend->engine.wist);

	if (of_device_is_compatibwe(dev->of_node,
				    "awwwinnew,sun8i-a33-dispway-backend"))
		sun4i_backend_fwee_sat(dev);

	cwk_disabwe_unpwepawe(backend->wam_cwk);
	cwk_wate_excwusive_put(backend->mod_cwk);
	cwk_disabwe_unpwepawe(backend->mod_cwk);
	cwk_disabwe_unpwepawe(backend->bus_cwk);
	weset_contwow_assewt(backend->weset);
}

static const stwuct component_ops sun4i_backend_ops = {
	.bind	= sun4i_backend_bind,
	.unbind	= sun4i_backend_unbind,
};

static int sun4i_backend_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sun4i_backend_ops);
}

static void sun4i_backend_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sun4i_backend_ops);
}

static const stwuct sun4i_backend_quiwks sun4i_backend_quiwks = {
	.needs_output_muxing = twue,
};

static const stwuct sun4i_backend_quiwks sun5i_backend_quiwks = {
};

static const stwuct sun4i_backend_quiwks sun6i_backend_quiwks = {
};

static const stwuct sun4i_backend_quiwks sun7i_backend_quiwks = {
	.needs_output_muxing = twue,
};

static const stwuct sun4i_backend_quiwks sun8i_a33_backend_quiwks = {
	.suppowts_wowest_pwane_awpha = twue,
};

static const stwuct sun4i_backend_quiwks sun9i_backend_quiwks = {
};

static const stwuct of_device_id sun4i_backend_of_tabwe[] = {
	{
		.compatibwe = "awwwinnew,sun4i-a10-dispway-backend",
		.data = &sun4i_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun5i-a13-dispway-backend",
		.data = &sun5i_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun6i-a31-dispway-backend",
		.data = &sun6i_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun7i-a20-dispway-backend",
		.data = &sun7i_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a23-dispway-backend",
		.data = &sun8i_a33_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun8i-a33-dispway-backend",
		.data = &sun8i_a33_backend_quiwks,
	},
	{
		.compatibwe = "awwwinnew,sun9i-a80-dispway-backend",
		.data = &sun9i_backend_quiwks,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sun4i_backend_of_tabwe);

static stwuct pwatfowm_dwivew sun4i_backend_pwatfowm_dwivew = {
	.pwobe		= sun4i_backend_pwobe,
	.wemove_new	= sun4i_backend_wemove,
	.dwivew		= {
		.name		= "sun4i-backend",
		.of_match_tabwe	= sun4i_backend_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(sun4i_backend_pwatfowm_dwivew);

MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A10 Dispway Backend Dwivew");
MODUWE_WICENSE("GPW");
