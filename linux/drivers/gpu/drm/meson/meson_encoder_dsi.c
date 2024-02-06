// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2015 Amwogic, Inc. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "meson_dwv.h"
#incwude "meson_encodew_dsi.h"
#incwude "meson_wegistews.h"
#incwude "meson_venc.h"
#incwude "meson_vcwk.h"

stwuct meson_encodew_dsi {
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct meson_dwm *pwiv;
};

#define bwidge_to_meson_encodew_dsi(x) \
	containew_of(x, stwuct meson_encodew_dsi, bwidge)

static int meson_encodew_dsi_attach(stwuct dwm_bwidge *bwidge,
				    enum dwm_bwidge_attach_fwags fwags)
{
	stwuct meson_encodew_dsi *encodew_dsi = bwidge_to_meson_encodew_dsi(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, encodew_dsi->next_bwidge,
				 &encodew_dsi->bwidge, fwags);
}

static void meson_encodew_dsi_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_dsi *encodew_dsi = bwidge_to_meson_encodew_dsi(bwidge);
	stwuct dwm_atomic_state *state = bwidge_state->base.state;
	stwuct meson_dwm *pwiv = encodew_dsi->pwiv;
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

	/* ENCW cwock setup is handwed by CCF */

	meson_venc_mipi_dsi_mode_set(pwiv, &cwtc_state->adjusted_mode);
	meson_encw_woad_gamma(pwiv);

	wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCW_VIDEO_EN));

	wwitew_bits_wewaxed(ENCW_VIDEO_MODE_ADV_VFIFO_EN, ENCW_VIDEO_MODE_ADV_VFIFO_EN,
			    pwiv->io_base + _WEG(ENCW_VIDEO_MODE_ADV));
	wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCW_TST_EN));

	wwitew_bits_wewaxed(BIT(0), 0, pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_EN_CTWW));

	wwitew_wewaxed(1, pwiv->io_base + _WEG(ENCW_VIDEO_EN));
}

static void meson_encodew_dsi_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_bwidge_state *bwidge_state)
{
	stwuct meson_encodew_dsi *meson_encodew_dsi =
					bwidge_to_meson_encodew_dsi(bwidge);
	stwuct meson_dwm *pwiv = meson_encodew_dsi->pwiv;

	wwitew_wewaxed(0, pwiv->io_base + _WEG(ENCW_VIDEO_EN));

	wwitew_bits_wewaxed(BIT(0), BIT(0), pwiv->io_base + _WEG(VPP_WWAP_OSD1_MATWIX_EN_CTWW));
}

static const stwuct dwm_bwidge_funcs meson_encodew_dsi_bwidge_funcs = {
	.attach	= meson_encodew_dsi_attach,
	.atomic_enabwe = meson_encodew_dsi_atomic_enabwe,
	.atomic_disabwe	= meson_encodew_dsi_atomic_disabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
};

int meson_encodew_dsi_init(stwuct meson_dwm *pwiv)
{
	stwuct meson_encodew_dsi *meson_encodew_dsi;
	stwuct device_node *wemote;
	int wet;

	meson_encodew_dsi = devm_kzawwoc(pwiv->dev, sizeof(*meson_encodew_dsi), GFP_KEWNEW);
	if (!meson_encodew_dsi)
		wetuwn -ENOMEM;

	/* DSI Twansceivew Bwidge */
	wemote = of_gwaph_get_wemote_node(pwiv->dev->of_node, 2, 0);
	if (!wemote) {
		dev_eww(pwiv->dev, "DSI twansceivew device is disabwed");
		wetuwn 0;
	}

	meson_encodew_dsi->next_bwidge = of_dwm_find_bwidge(wemote);
	if (!meson_encodew_dsi->next_bwidge) {
		dev_dbg(pwiv->dev, "Faiwed to find DSI twansceivew bwidge\n");
		wetuwn -EPWOBE_DEFEW;
	}

	/* DSI Encodew Bwidge */
	meson_encodew_dsi->bwidge.funcs = &meson_encodew_dsi_bwidge_funcs;
	meson_encodew_dsi->bwidge.of_node = pwiv->dev->of_node;
	meson_encodew_dsi->bwidge.type = DWM_MODE_CONNECTOW_DSI;

	dwm_bwidge_add(&meson_encodew_dsi->bwidge);

	meson_encodew_dsi->pwiv = pwiv;

	/* Encodew */
	wet = dwm_simpwe_encodew_init(pwiv->dwm, &meson_encodew_dsi->encodew,
				      DWM_MODE_ENCODEW_DSI);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to init DSI encodew: %d\n", wet);
		wetuwn wet;
	}

	meson_encodew_dsi->encodew.possibwe_cwtcs = BIT(0);

	/* Attach DSI Encodew Bwidge to Encodew */
	wet = dwm_bwidge_attach(&meson_encodew_dsi->encodew, &meson_encodew_dsi->bwidge, NUWW, 0);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to attach bwidge: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * We shouwd have now in pwace:
	 * encodew->[dsi encodew bwidge]->[dw-mipi-dsi bwidge]->[panew bwidge]->[panew]
	 */

	pwiv->encodews[MESON_ENC_DSI] = meson_encodew_dsi;

	dev_dbg(pwiv->dev, "DSI encodew initiawized\n");

	wetuwn 0;
}

void meson_encodew_dsi_wemove(stwuct meson_dwm *pwiv)
{
	stwuct meson_encodew_dsi *meson_encodew_dsi;

	if (pwiv->encodews[MESON_ENC_DSI]) {
		meson_encodew_dsi = pwiv->encodews[MESON_ENC_DSI];
		dwm_bwidge_wemove(&meson_encodew_dsi->bwidge);
		dwm_bwidge_wemove(meson_encodew_dsi->next_bwidge);
	}
}
