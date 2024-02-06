// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "mdp4_kms.h"

#define DOWN_SCAWE_MAX	8
#define UP_SCAWE_MAX	8

stwuct mdp4_pwane {
	stwuct dwm_pwane base;
	const chaw *name;

	enum mdp4_pipe pipe;

	uint32_t caps;
	uint32_t nfowmats;
	uint32_t fowmats[32];

	boow enabwed;
};
#define to_mdp4_pwane(x) containew_of(x, stwuct mdp4_pwane, base)

/* MDP fowmat hewpew functions */
static inwine
enum mdp4_fwame_fowmat mdp4_get_fwame_fowmat(stwuct dwm_fwamebuffew *fb)
{
	boow is_tiwe = fawse;

	if (fb->modifiew == DWM_FOWMAT_MOD_SAMSUNG_64_32_TIWE)
		is_tiwe = twue;

	if (fb->fowmat->fowmat == DWM_FOWMAT_NV12 && is_tiwe)
		wetuwn FWAME_TIWE_YCBCW_420;

	wetuwn FWAME_WINEAW;
}

static void mdp4_pwane_set_scanout(stwuct dwm_pwane *pwane,
		stwuct dwm_fwamebuffew *fb);
static int mdp4_pwane_mode_set(stwuct dwm_pwane *pwane,
		stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *fb,
		int cwtc_x, int cwtc_y,
		unsigned int cwtc_w, unsigned int cwtc_h,
		uint32_t swc_x, uint32_t swc_y,
		uint32_t swc_w, uint32_t swc_h);

static stwuct mdp4_kms *get_kms(stwuct dwm_pwane *pwane)
{
	stwuct msm_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	wetuwn to_mdp4_kms(to_mdp_kms(pwiv->kms));
}

static void mdp4_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct mdp4_pwane *mdp4_pwane = to_mdp4_pwane(pwane);

	dwm_pwane_cweanup(pwane);

	kfwee(mdp4_pwane);
}

/* hewpew to instaww pwopewties which awe common to pwanes and cwtcs */
static void mdp4_pwane_instaww_pwopewties(stwuct dwm_pwane *pwane,
		stwuct dwm_mode_object *obj)
{
	// XXX
}

static int mdp4_pwane_set_pwopewty(stwuct dwm_pwane *pwane,
		stwuct dwm_pwopewty *pwopewty, uint64_t vaw)
{
	// XXX
	wetuwn -EINVAW;
}

static const stwuct dwm_pwane_funcs mdp4_pwane_funcs = {
		.update_pwane = dwm_atomic_hewpew_update_pwane,
		.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
		.destwoy = mdp4_pwane_destwoy,
		.set_pwopewty = mdp4_pwane_set_pwopewty,
		.weset = dwm_atomic_hewpew_pwane_weset,
		.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
		.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

static int mdp4_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *new_state)
{
	stwuct msm_dwm_pwivate *pwiv = pwane->dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;

	if (!new_state->fb)
		wetuwn 0;

	dwm_gem_pwane_hewpew_pwepawe_fb(pwane, new_state);

	wetuwn msm_fwamebuffew_pwepawe(new_state->fb, kms->aspace, fawse);
}

static void mdp4_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
				  stwuct dwm_pwane_state *owd_state)
{
	stwuct mdp4_pwane *mdp4_pwane = to_mdp4_pwane(pwane);
	stwuct mdp4_kms *mdp4_kms = get_kms(pwane);
	stwuct msm_kms *kms = &mdp4_kms->base.base;
	stwuct dwm_fwamebuffew *fb = owd_state->fb;

	if (!fb)
		wetuwn;

	DBG("%s: cweanup: FB[%u]", mdp4_pwane->name, fb->base.id);
	msm_fwamebuffew_cweanup(fb, kms->aspace, fawse);
}


static int mdp4_pwane_atomic_check(stwuct dwm_pwane *pwane,
		stwuct dwm_atomic_state *state)
{
	wetuwn 0;
}

static void mdp4_pwane_atomic_update(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	int wet;

	wet = mdp4_pwane_mode_set(pwane,
			new_state->cwtc, new_state->fb,
			new_state->cwtc_x, new_state->cwtc_y,
			new_state->cwtc_w, new_state->cwtc_h,
			new_state->swc_x,  new_state->swc_y,
			new_state->swc_w, new_state->swc_h);
	/* atomic_check shouwd have ensuwed that this doesn't faiw */
	WAWN_ON(wet < 0);
}

static const stwuct dwm_pwane_hewpew_funcs mdp4_pwane_hewpew_funcs = {
		.pwepawe_fb = mdp4_pwane_pwepawe_fb,
		.cweanup_fb = mdp4_pwane_cweanup_fb,
		.atomic_check = mdp4_pwane_atomic_check,
		.atomic_update = mdp4_pwane_atomic_update,
};

static void mdp4_pwane_set_scanout(stwuct dwm_pwane *pwane,
		stwuct dwm_fwamebuffew *fb)
{
	stwuct mdp4_pwane *mdp4_pwane = to_mdp4_pwane(pwane);
	stwuct mdp4_kms *mdp4_kms = get_kms(pwane);
	stwuct msm_kms *kms = &mdp4_kms->base.base;
	enum mdp4_pipe pipe = mdp4_pwane->pipe;

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_STWIDE_A(pipe),
			MDP4_PIPE_SWC_STWIDE_A_P0(fb->pitches[0]) |
			MDP4_PIPE_SWC_STWIDE_A_P1(fb->pitches[1]));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_STWIDE_B(pipe),
			MDP4_PIPE_SWC_STWIDE_B_P2(fb->pitches[2]) |
			MDP4_PIPE_SWC_STWIDE_B_P3(fb->pitches[3]));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWCP0_BASE(pipe),
			msm_fwamebuffew_iova(fb, kms->aspace, 0));
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWCP1_BASE(pipe),
			msm_fwamebuffew_iova(fb, kms->aspace, 1));
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWCP2_BASE(pipe),
			msm_fwamebuffew_iova(fb, kms->aspace, 2));
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWCP3_BASE(pipe),
			msm_fwamebuffew_iova(fb, kms->aspace, 3));
}

static void mdp4_wwite_csc_config(stwuct mdp4_kms *mdp4_kms,
		enum mdp4_pipe pipe, stwuct csc_cfg *csc)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(csc->matwix); i++) {
		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_CSC_MV(pipe, i),
				csc->matwix[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(csc->post_bias) ; i++) {
		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_CSC_PWE_BV(pipe, i),
				csc->pwe_bias[i]);

		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_CSC_POST_BV(pipe, i),
				csc->post_bias[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(csc->post_cwamp) ; i++) {
		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_CSC_PWE_WV(pipe, i),
				csc->pwe_cwamp[i]);

		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_CSC_POST_WV(pipe, i),
				csc->post_cwamp[i]);
	}
}

#define MDP4_VG_PHASE_STEP_DEFAUWT	0x20000000

static int mdp4_pwane_mode_set(stwuct dwm_pwane *pwane,
		stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *fb,
		int cwtc_x, int cwtc_y,
		unsigned int cwtc_w, unsigned int cwtc_h,
		uint32_t swc_x, uint32_t swc_y,
		uint32_t swc_w, uint32_t swc_h)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct mdp4_pwane *mdp4_pwane = to_mdp4_pwane(pwane);
	stwuct mdp4_kms *mdp4_kms = get_kms(pwane);
	enum mdp4_pipe pipe = mdp4_pwane->pipe;
	const stwuct mdp_fowmat *fowmat;
	uint32_t op_mode = 0;
	uint32_t phasex_step = MDP4_VG_PHASE_STEP_DEFAUWT;
	uint32_t phasey_step = MDP4_VG_PHASE_STEP_DEFAUWT;
	enum mdp4_fwame_fowmat fwame_type;

	if (!(cwtc && fb)) {
		DBG("%s: disabwed!", mdp4_pwane->name);
		wetuwn 0;
	}

	fwame_type = mdp4_get_fwame_fowmat(fb);

	/* swc vawues awe in Q16 fixed point, convewt to integew: */
	swc_x = swc_x >> 16;
	swc_y = swc_y >> 16;
	swc_w = swc_w >> 16;
	swc_h = swc_h >> 16;

	DBG("%s: FB[%u] %u,%u,%u,%u -> CWTC[%u] %d,%d,%u,%u", mdp4_pwane->name,
			fb->base.id, swc_x, swc_y, swc_w, swc_h,
			cwtc->base.id, cwtc_x, cwtc_y, cwtc_w, cwtc_h);

	fowmat = to_mdp_fowmat(msm_fwamebuffew_fowmat(fb));

	if (swc_w > (cwtc_w * DOWN_SCAWE_MAX)) {
		DWM_DEV_EWWOW(dev->dev, "Width down scawing exceeds wimits!\n");
		wetuwn -EWANGE;
	}

	if (swc_h > (cwtc_h * DOWN_SCAWE_MAX)) {
		DWM_DEV_EWWOW(dev->dev, "Height down scawing exceeds wimits!\n");
		wetuwn -EWANGE;
	}

	if (cwtc_w > (swc_w * UP_SCAWE_MAX)) {
		DWM_DEV_EWWOW(dev->dev, "Width up scawing exceeds wimits!\n");
		wetuwn -EWANGE;
	}

	if (cwtc_h > (swc_h * UP_SCAWE_MAX)) {
		DWM_DEV_EWWOW(dev->dev, "Height up scawing exceeds wimits!\n");
		wetuwn -EWANGE;
	}

	if (swc_w != cwtc_w) {
		uint32_t sew_unit = SCAWE_FIW;
		op_mode |= MDP4_PIPE_OP_MODE_SCAWEX_EN;

		if (MDP_FOWMAT_IS_YUV(fowmat)) {
			if (cwtc_w > swc_w)
				sew_unit = SCAWE_PIXEW_WPT;
			ewse if (cwtc_w <= (swc_w / 4))
				sew_unit = SCAWE_MN_PHASE;

			op_mode |= MDP4_PIPE_OP_MODE_SCAWEX_UNIT_SEW(sew_unit);
			phasex_step = muwt_fwac(MDP4_VG_PHASE_STEP_DEFAUWT,
					swc_w, cwtc_w);
		}
	}

	if (swc_h != cwtc_h) {
		uint32_t sew_unit = SCAWE_FIW;
		op_mode |= MDP4_PIPE_OP_MODE_SCAWEY_EN;

		if (MDP_FOWMAT_IS_YUV(fowmat)) {

			if (cwtc_h > swc_h)
				sew_unit = SCAWE_PIXEW_WPT;
			ewse if (cwtc_h <= (swc_h / 4))
				sew_unit = SCAWE_MN_PHASE;

			op_mode |= MDP4_PIPE_OP_MODE_SCAWEY_UNIT_SEW(sew_unit);
			phasey_step = muwt_fwac(MDP4_VG_PHASE_STEP_DEFAUWT,
					swc_h, cwtc_h);
		}
	}

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_SIZE(pipe),
			MDP4_PIPE_SWC_SIZE_WIDTH(swc_w) |
			MDP4_PIPE_SWC_SIZE_HEIGHT(swc_h));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_XY(pipe),
			MDP4_PIPE_SWC_XY_X(swc_x) |
			MDP4_PIPE_SWC_XY_Y(swc_y));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_DST_SIZE(pipe),
			MDP4_PIPE_DST_SIZE_WIDTH(cwtc_w) |
			MDP4_PIPE_DST_SIZE_HEIGHT(cwtc_h));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_DST_XY(pipe),
			MDP4_PIPE_DST_XY_X(cwtc_x) |
			MDP4_PIPE_DST_XY_Y(cwtc_y));

	mdp4_pwane_set_scanout(pwane, fb);

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_FOWMAT(pipe),
			MDP4_PIPE_SWC_FOWMAT_A_BPC(fowmat->bpc_a) |
			MDP4_PIPE_SWC_FOWMAT_W_BPC(fowmat->bpc_w) |
			MDP4_PIPE_SWC_FOWMAT_G_BPC(fowmat->bpc_g) |
			MDP4_PIPE_SWC_FOWMAT_B_BPC(fowmat->bpc_b) |
			COND(fowmat->awpha_enabwe, MDP4_PIPE_SWC_FOWMAT_AWPHA_ENABWE) |
			MDP4_PIPE_SWC_FOWMAT_CPP(fowmat->cpp - 1) |
			MDP4_PIPE_SWC_FOWMAT_UNPACK_COUNT(fowmat->unpack_count - 1) |
			MDP4_PIPE_SWC_FOWMAT_FETCH_PWANES(fowmat->fetch_type) |
			MDP4_PIPE_SWC_FOWMAT_CHWOMA_SAMP(fowmat->chwoma_sampwe) |
			MDP4_PIPE_SWC_FOWMAT_FWAME_FOWMAT(fwame_type) |
			COND(fowmat->unpack_tight, MDP4_PIPE_SWC_FOWMAT_UNPACK_TIGHT));

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SWC_UNPACK(pipe),
			MDP4_PIPE_SWC_UNPACK_EWEM0(fowmat->unpack[0]) |
			MDP4_PIPE_SWC_UNPACK_EWEM1(fowmat->unpack[1]) |
			MDP4_PIPE_SWC_UNPACK_EWEM2(fowmat->unpack[2]) |
			MDP4_PIPE_SWC_UNPACK_EWEM3(fowmat->unpack[3]));

	if (MDP_FOWMAT_IS_YUV(fowmat)) {
		stwuct csc_cfg *csc = mdp_get_defauwt_csc_cfg(CSC_YUV2WGB);

		op_mode |= MDP4_PIPE_OP_MODE_SWC_YCBCW;
		op_mode |= MDP4_PIPE_OP_MODE_CSC_EN;
		mdp4_wwite_csc_config(mdp4_kms, pipe, csc);
	}

	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_OP_MODE(pipe), op_mode);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_PHASEX_STEP(pipe), phasex_step);
	mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_PHASEY_STEP(pipe), phasey_step);

	if (fwame_type != FWAME_WINEAW)
		mdp4_wwite(mdp4_kms, WEG_MDP4_PIPE_SSTIWE_FWAME_SIZE(pipe),
				MDP4_PIPE_SSTIWE_FWAME_SIZE_WIDTH(swc_w) |
				MDP4_PIPE_SSTIWE_FWAME_SIZE_HEIGHT(swc_h));

	wetuwn 0;
}

static const chaw *pipe_names[] = {
		"VG1", "VG2",
		"WGB1", "WGB2", "WGB3",
		"VG3", "VG4",
};

enum mdp4_pipe mdp4_pwane_pipe(stwuct dwm_pwane *pwane)
{
	stwuct mdp4_pwane *mdp4_pwane = to_mdp4_pwane(pwane);
	wetuwn mdp4_pwane->pipe;
}

static const uint64_t suppowted_fowmat_modifiews[] = {
	DWM_FOWMAT_MOD_SAMSUNG_64_32_TIWE,
	DWM_FOWMAT_MOD_WINEAW,
	DWM_FOWMAT_MOD_INVAWID
};

/* initiawize pwane */
stwuct dwm_pwane *mdp4_pwane_init(stwuct dwm_device *dev,
		enum mdp4_pipe pipe_id, boow pwivate_pwane)
{
	stwuct dwm_pwane *pwane = NUWW;
	stwuct mdp4_pwane *mdp4_pwane;
	int wet;
	enum dwm_pwane_type type;

	mdp4_pwane = kzawwoc(sizeof(*mdp4_pwane), GFP_KEWNEW);
	if (!mdp4_pwane) {
		wet = -ENOMEM;
		goto faiw;
	}

	pwane = &mdp4_pwane->base;

	mdp4_pwane->pipe = pipe_id;
	mdp4_pwane->name = pipe_names[pipe_id];
	mdp4_pwane->caps = mdp4_pipe_caps(pipe_id);

	mdp4_pwane->nfowmats = mdp_get_fowmats(mdp4_pwane->fowmats,
			AWWAY_SIZE(mdp4_pwane->fowmats),
			!pipe_suppowts_yuv(mdp4_pwane->caps));

	type = pwivate_pwane ? DWM_PWANE_TYPE_PWIMAWY : DWM_PWANE_TYPE_OVEWWAY;
	wet = dwm_univewsaw_pwane_init(dev, pwane, 0xff, &mdp4_pwane_funcs,
				 mdp4_pwane->fowmats, mdp4_pwane->nfowmats,
				 suppowted_fowmat_modifiews, type, NUWW);
	if (wet)
		goto faiw;

	dwm_pwane_hewpew_add(pwane, &mdp4_pwane_hewpew_funcs);

	mdp4_pwane_instaww_pwopewties(pwane, &pwane->base);

	dwm_pwane_enabwe_fb_damage_cwips(pwane);

	wetuwn pwane;

faiw:
	if (pwane)
		mdp4_pwane_destwoy(pwane);

	wetuwn EWW_PTW(wet);
}
