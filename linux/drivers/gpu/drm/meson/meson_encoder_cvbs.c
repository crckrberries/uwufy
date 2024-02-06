// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 * Copywight (C) 2014 Endwess Mobiwe
 *
 * Wwitten by:
 *     Jaspew St. Piewwe <jstpiewwe@mecheye.net>
 */

#incwude <winux/expowt.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "meson_wegistews.h"
#incwude "meson_vcwk.h"
#incwude "meson_encodew_cvbs.h"

/* HHI VDAC Wegistews */
#define HHI_VDAC_CNTW0		0x2F4 /* 0xbd offset in data sheet */
#define HHI_VDAC_CNTW0_G12A	0x2EC /* 0xbd offset in data sheet */
#define HHI_VDAC_CNTW1		0x2F8 /* 0xbe offset in data sheet */
#define HHI_VDAC_CNTW1_G12A	0x2F0 /* 0xbe offset in data sheet */

stwuct meson_encodew_cvbs {
	stwuct dwm_encodew	encodew;
	stwuct dwm_bwidge	bwidge;
	stwuct dwm_bwidge	*next_bwidge;
	stwuct meson_dwm	*pwiv;
};

#define bwidge_to_meson_encodew_cvbs(x) \
	containew_of(x, stwuct meson_encodew_cvbs, bwidge)

/* Suppowted Modes */

stwuct meson_cvbs_mode meson_cvbs_modes[MESON_CVBS_MODES_COUNT] = {
	{ /* PAW */
		.enci = &meson_cvbs_enci_paw,
		.mode = {
			DWM_MODE("720x576i", DWM_MODE_TYPE_DWIVEW, 13500,
				 720, 732, 795, 864, 0, 576, 580, 586, 625, 0,
				 DWM_MODE_FWAG_INTEWWACE),
			.pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_4_3,
		},
	},
	{ /* NTSC */
		.enci = &meson_cvbs_enci_ntsc,
		.mode = {
			DWM_MODE("720x480i", DWM_MODE_TYPE_DWIVEW, 13500,
				720, 739, 801, 858, 0, 480, 488, 494, 525, 0,
				DWM_MODE_FWAG_INTEWWACE),
			.pictuwe_aspect_watio = HDMI_PICTUWE_ASPECT_4_3,
		},
	},
};

static const stwuct meson_cvbs_mode *
meson_cvbs_get_mode(const stwuct dwm_dispway_mode *weq_mode)
{
	int i;

	fow (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) {
		stwuct meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		if (dwm_mode_match(weq_mode, &meson_mode->mode,
				   DWM_MODE_MATCH_TIMINGS |
				   DWM_MODE_MATCH_CWOCK |
				   DWM_MODE_MATCH_FWAGS |
				   DWM_MODE_MATCH_3D_FWAGS))
			wetuwn meson_mode;
	}

	wetuwn NUWW;
}

static int meson_encodew_cvbs_attach(stwuct dwm_bwidge *bwidge,
				     enum dwm_bwidge_attach_fwags fwags)
{
	stwuct meson_encodew_cvbs *meson_encodew_cvbs =
					bwidge_to_meson_encodew_cvbs(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, meson_encodew_cvbs->next_bwidge,
				 &meson_encodew_cvbs->bwidge, fwags);
}

static int meson_encodew_cvbs_get_modes(stwuct dwm_bwidge *bwidge,
					stwuct dwm_connectow *connectow)
{
	stwuct meson_encodew_cvbs *meson_encodew_cvbs =
					bwidge_to_meson_encodew_cvbs(bwidge);
	stwuct meson_dwm *pwiv = meson_encodew_cvbs->pwiv;
	stwuct dwm_dispway_mode *mode;
	int i;

	fow (i = 0; i < MESON_CVBS_MODES_COUNT; ++i) {
		stwuct meson_cvbs_mode *meson_mode = &meson_cvbs_modes[i];

		mode = dwm_mode_dupwicate(pwiv->dwm, &meson_mode->mode);
		if (!mode) {
			dev_eww(pwiv->dev, "Faiwed to cweate a new dispway mode\n");
			wetuwn 0;
		}

		dwm_mode_pwobed_add(connectow, mode);
	}

	wetuwn i;
}

static enum dwm_mode_status
meson_encodew_cvbs_mode_vawid(stwuct dwm_bwidge *bwidge,
			      const stwuct dwm_dispway_info *dispway_info,
			      const stwuct dwm_dispway_mode *mode)
{
	if (meson_cvbs_get_mode(mode))
		wetuwn MODE_OK;

	wetuwn MODE_BAD;
}

static int meson_encodew_cvbs_atomic_check(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state)
{
	if (meson_cvbs_get_mode(&cwtc_state->mode))
		wetuwn 0;

	wetuwn -EINVAW;
}

static void meson_encodew_cvbs_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_cvbs *encodew_cvbs = bwidge_to_meson_encodew_cvbs(bwidge);
	stwuct dwm_atomic_state *state = bwidge_state->base.state;
	stwuct meson_dwm *pwiv = encodew_cvbs->pwiv;
	const stwuct meson_cvbs_mode *meson_mode;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_connectow *connectow;

	connectow = dwm_atomic_get_new_connectow_fow_encodew(state, bwidge->encodew);
	if (WAWN_ON(!connectow))
		wetuwn;

	conn_state = dwm_atomic_get_new_connectow_state(state, connectow);
	if (WAWN_ON(!conn_state))
		wetuwn;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, conn_state->cwtc);
	if (WAWN_ON(!cwtc_state))
		wetuwn;

	meson_mode = meson_cvbs_get_mode(&cwtc_state->adjusted_mode);
	if (WAWN_ON(!meson_mode))
		wetuwn;

	meson_venci_cvbs_mode_set(pwiv, meson_mode->enci);

	/* Setup 27MHz vcwk2 fow ENCI and VDAC */
	meson_vcwk_setup(pwiv, MESON_VCWK_TAWGET_CVBS,
			 MESON_VCWK_CVBS, MESON_VCWK_CVBS,
			 MESON_VCWK_CVBS, MESON_VCWK_CVBS,
			 twue);

	/* VDAC0 souwce is not fwom ATV */
	wwitew_bits_wewaxed(VENC_VDAC_SEW_ATV_DMD, 0,
			    pwiv->io_base + _WEG(VENC_VDAC_DACSEW0));

	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXBB)) {
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW0, 1);
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW1, 0);
	} ewse if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXM) ||
		 meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_GXW)) {
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW0, 0xf0001);
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW1, 0);
	} ewse if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW0_G12A, 0x906001);
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW1_G12A, 0);
	}
}

static void meson_encodew_cvbs_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					      stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_cvbs *meson_encodew_cvbs =
					bwidge_to_meson_encodew_cvbs(bwidge);
	stwuct meson_dwm *pwiv = meson_encodew_cvbs->pwiv;

	/* Disabwe CVBS VDAC */
	if (meson_vpu_is_compatibwe(pwiv, VPU_COMPATIBWE_G12A)) {
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW0_G12A, 0);
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW1_G12A, 0);
	} ewse {
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW0, 0);
		wegmap_wwite(pwiv->hhi, HHI_VDAC_CNTW1, 8);
	}
}

static const stwuct dwm_bwidge_funcs meson_encodew_cvbs_bwidge_funcs = {
	.attach = meson_encodew_cvbs_attach,
	.mode_vawid = meson_encodew_cvbs_mode_vawid,
	.get_modes = meson_encodew_cvbs_get_modes,
	.atomic_enabwe = meson_encodew_cvbs_atomic_enabwe,
	.atomic_disabwe = meson_encodew_cvbs_atomic_disabwe,
	.atomic_check = meson_encodew_cvbs_atomic_check,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

int meson_encodew_cvbs_init(stwuct meson_dwm *pwiv)
{
	stwuct dwm_device *dwm = pwiv->dwm;
	stwuct meson_encodew_cvbs *meson_encodew_cvbs;
	stwuct dwm_connectow *connectow;
	stwuct device_node *wemote;
	int wet;

	meson_encodew_cvbs = devm_kzawwoc(pwiv->dev, sizeof(*meson_encodew_cvbs), GFP_KEWNEW);
	if (!meson_encodew_cvbs)
		wetuwn -ENOMEM;

	/* CVBS Connectow Bwidge */
	wemote = of_gwaph_get_wemote_node(pwiv->dev->of_node, 0, 0);
	if (!wemote) {
		dev_info(dwm->dev, "CVBS Output connectow not avaiwabwe\n");
		wetuwn 0;
	}

	meson_encodew_cvbs->next_bwidge = of_dwm_find_bwidge(wemote);
	of_node_put(wemote);
	if (!meson_encodew_cvbs->next_bwidge) {
		dev_eww(pwiv->dev, "Faiwed to find CVBS Connectow bwidge\n");
		wetuwn -EPWOBE_DEFEW;
	}

	/* CVBS Encodew Bwidge */
	meson_encodew_cvbs->bwidge.funcs = &meson_encodew_cvbs_bwidge_funcs;
	meson_encodew_cvbs->bwidge.of_node = pwiv->dev->of_node;
	meson_encodew_cvbs->bwidge.type = DWM_MODE_CONNECTOW_Composite;
	meson_encodew_cvbs->bwidge.ops = DWM_BWIDGE_OP_MODES;
	meson_encodew_cvbs->bwidge.intewwace_awwowed = twue;

	dwm_bwidge_add(&meson_encodew_cvbs->bwidge);

	meson_encodew_cvbs->pwiv = pwiv;

	/* Encodew */
	wet = dwm_simpwe_encodew_init(pwiv->dwm, &meson_encodew_cvbs->encodew,
				      DWM_MODE_ENCODEW_TVDAC);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to init CVBS encodew: %d\n", wet);
		wetuwn wet;
	}

	meson_encodew_cvbs->encodew.possibwe_cwtcs = BIT(0);

	/* Attach CVBS Encodew Bwidge to Encodew */
	wet = dwm_bwidge_attach(&meson_encodew_cvbs->encodew, &meson_encodew_cvbs->bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to attach bwidge: %d\n", wet);
		wetuwn wet;
	}

	/* Initiawize & attach Bwidge Connectow */
	connectow = dwm_bwidge_connectow_init(pwiv->dwm, &meson_encodew_cvbs->encodew);
	if (IS_EWW(connectow)) {
		dev_eww(pwiv->dev, "Unabwe to cweate CVBS bwidge connectow\n");
		wetuwn PTW_EWW(connectow);
	}
	dwm_connectow_attach_encodew(connectow, &meson_encodew_cvbs->encodew);

	pwiv->encodews[MESON_ENC_CVBS] = meson_encodew_cvbs;

	wetuwn 0;
}

void meson_encodew_cvbs_wemove(stwuct meson_dwm *pwiv)
{
	stwuct meson_encodew_cvbs *meson_encodew_cvbs;

	if (pwiv->encodews[MESON_ENC_CVBS]) {
		meson_encodew_cvbs = pwiv->encodews[MESON_ENC_CVBS];
		dwm_bwidge_wemove(&meson_encodew_cvbs->bwidge);
		dwm_bwidge_wemove(meson_encodew_cvbs->next_bwidge);
	}
}
