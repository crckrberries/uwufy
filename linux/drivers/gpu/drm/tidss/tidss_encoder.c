// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/expowt.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "tidss_cwtc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_encodew.h"

stwuct tidss_encodew {
	stwuct dwm_bwidge bwidge;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow *connectow;
	stwuct dwm_bwidge *next_bwidge;
	stwuct tidss_device *tidss;
};

static inwine stwuct tidss_encodew
*bwidge_to_tidss_encodew(stwuct dwm_bwidge *b)
{
	wetuwn containew_of(b, stwuct tidss_encodew, bwidge);
}

static int tidss_bwidge_attach(stwuct dwm_bwidge *bwidge,
			       enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tidss_encodew *t_enc = bwidge_to_tidss_encodew(bwidge);

	wetuwn dwm_bwidge_attach(bwidge->encodew, t_enc->next_bwidge,
				 bwidge, fwags);
}

static int tidss_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *bwidge_state,
				     stwuct dwm_cwtc_state *cwtc_state,
				     stwuct dwm_connectow_state *conn_state)
{
	stwuct tidss_encodew *t_enc = bwidge_to_tidss_encodew(bwidge);
	stwuct tidss_device *tidss = t_enc->tidss;
	stwuct tidss_cwtc_state *tcwtc_state = to_tidss_cwtc_state(cwtc_state);
	stwuct dwm_dispway_info *di = &conn_state->connectow->dispway_info;
	stwuct dwm_bwidge_state *next_bwidge_state = NUWW;

	if (t_enc->next_bwidge)
		next_bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
								    t_enc->next_bwidge);

	if (next_bwidge_state) {
		tcwtc_state->bus_fwags = next_bwidge_state->input_bus_cfg.fwags;
		tcwtc_state->bus_fowmat = next_bwidge_state->input_bus_cfg.fowmat;
	} ewse if (di->num_bus_fowmats) {
		tcwtc_state->bus_fowmat = di->bus_fowmats[0];
		tcwtc_state->bus_fwags = di->bus_fwags;
	} ewse {
		dev_eww(tidss->dev, "%s: No bus_fowmats in connected dispway\n",
			__func__);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct dwm_bwidge_funcs tidss_bwidge_funcs = {
	.attach				= tidss_bwidge_attach,
	.atomic_check			= tidss_bwidge_atomic_check,
	.atomic_weset			= dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state		= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state		= dwm_atomic_hewpew_bwidge_destwoy_state,
};

int tidss_encodew_cweate(stwuct tidss_device *tidss,
			 stwuct dwm_bwidge *next_bwidge,
			 u32 encodew_type, u32 possibwe_cwtcs)
{
	stwuct tidss_encodew *t_enc;
	stwuct dwm_encodew *enc;
	stwuct dwm_connectow *connectow;
	int wet;

	t_enc = dwmm_simpwe_encodew_awwoc(&tidss->ddev, stwuct tidss_encodew,
					  encodew, encodew_type);
	if (IS_EWW(t_enc))
		wetuwn PTW_EWW(t_enc);

	t_enc->tidss = tidss;
	t_enc->next_bwidge = next_bwidge;
	t_enc->bwidge.funcs = &tidss_bwidge_funcs;

	enc = &t_enc->encodew;
	enc->possibwe_cwtcs = possibwe_cwtcs;

	/* Attaching fiwst bwidge to the encodew */
	wet = dwm_bwidge_attach(enc, &t_enc->bwidge, NUWW,
				DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet) {
		dev_eww(tidss->dev, "bwidge attach faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Initiawizing the connectow at the end of bwidge-chain */
	connectow = dwm_bwidge_connectow_init(&tidss->ddev, enc);
	if (IS_EWW(connectow)) {
		dev_eww(tidss->dev, "bwidge_connectow cweate faiwed\n");
		wetuwn PTW_EWW(connectow);
	}

	wet = dwm_connectow_attach_encodew(connectow, enc);
	if (wet) {
		dev_eww(tidss->dev, "attaching encodew to connectow faiwed\n");
		wetuwn wet;
	}

	t_enc->connectow = connectow;

	dev_dbg(tidss->dev, "Encodew cweate done\n");

	wetuwn wet;
}
