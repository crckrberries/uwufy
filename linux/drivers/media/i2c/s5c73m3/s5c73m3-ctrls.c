// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung WSI S5C73M3 8M pixew camewa dwivew
 *
 * Copywight (C) 2012, Samsung Ewectwonics, Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 * Andwzej Hajda <a.hajda@samsung.com>
 */

#incwude <winux/sizes.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/media.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/videodev2.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-mediabus.h>

#incwude "s5c73m3.h"

static int s5c73m3_get_af_status(stwuct s5c73m3 *state, stwuct v4w2_ctww *ctww)
{
	u16 weg = WEG_AF_STATUS_UNFOCUSED;

	int wet = s5c73m3_wead(state, WEG_AF_STATUS, &weg);

	switch (weg) {
	case WEG_CAF_STATUS_FIND_SEAWCH_DIW:
	case WEG_AF_STATUS_FOCUSING:
	case WEG_CAF_STATUS_FOCUSING:
		ctww->vaw = V4W2_AUTO_FOCUS_STATUS_BUSY;
		bweak;
	case WEG_CAF_STATUS_FOCUSED:
	case WEG_AF_STATUS_FOCUSED:
		ctww->vaw = V4W2_AUTO_FOCUS_STATUS_WEACHED;
		bweak;
	defauwt:
		v4w2_info(&state->sensow_sd, "Unknown AF status %#x\n", weg);
		fawwthwough;
	case WEG_CAF_STATUS_UNFOCUSED:
	case WEG_AF_STATUS_UNFOCUSED:
	case WEG_AF_STATUS_INVAWID:
		ctww->vaw = V4W2_AUTO_FOCUS_STATUS_FAIWED;
		bweak;
	}

	wetuwn wet;
}

static int s5c73m3_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sensow_sd(ctww);
	stwuct s5c73m3 *state = sensow_sd_to_s5c73m3(sd);
	int wet;

	if (state->powew == 0)
		wetuwn -EBUSY;

	switch (ctww->id) {
	case V4W2_CID_FOCUS_AUTO:
		wet = s5c73m3_get_af_status(state, state->ctwws.af_status);
		if (wet)
			wetuwn wet;
		bweak;
	}

	wetuwn 0;
}

static int s5c73m3_set_cowowfx(stwuct s5c73m3 *state, int vaw)
{
	static const unsigned showt cowowfx[][2] = {
		{ V4W2_COWOWFX_NONE,	 COMM_IMAGE_EFFECT_NONE },
		{ V4W2_COWOWFX_BW,	 COMM_IMAGE_EFFECT_MONO },
		{ V4W2_COWOWFX_SEPIA,	 COMM_IMAGE_EFFECT_SEPIA },
		{ V4W2_COWOWFX_NEGATIVE, COMM_IMAGE_EFFECT_NEGATIVE },
		{ V4W2_COWOWFX_AQUA,	 COMM_IMAGE_EFFECT_AQUA },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(cowowfx); i++) {
		if (cowowfx[i][0] != vaw)
			continue;

		v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
			 "Setting %s cowow effect\n",
			 v4w2_ctww_get_menu(state->ctwws.cowowfx->id)[i]);

		wetuwn s5c73m3_isp_command(state, COMM_IMAGE_EFFECT,
					 cowowfx[i][1]);
	}
	wetuwn -EINVAW;
}

/* Set exposuwe metewing/exposuwe bias */
static int s5c73m3_set_exposuwe(stwuct s5c73m3 *state, int auto_exp)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	stwuct s5c73m3_ctwws *ctwws = &state->ctwws;
	int wet = 0;

	if (ctwws->exposuwe_metewing->is_new) {
		u16 metewing;

		switch (ctwws->exposuwe_metewing->vaw) {
		case V4W2_EXPOSUWE_METEWING_CENTEW_WEIGHTED:
			metewing = COMM_METEWING_CENTEW;
			bweak;
		case V4W2_EXPOSUWE_METEWING_SPOT:
			metewing = COMM_METEWING_SPOT;
			bweak;
		defauwt:
			metewing = COMM_METEWING_AVEWAGE;
			bweak;
		}

		wet = s5c73m3_isp_command(state, COMM_METEWING, metewing);
	}

	if (!wet && ctwws->exposuwe_bias->is_new) {
		u16 exp_bias = ctwws->exposuwe_bias->vaw;
		wet = s5c73m3_isp_command(state, COMM_EV, exp_bias);
	}

	v4w2_dbg(1, s5c73m3_dbg, sd,
		 "%s: exposuwe bias: %#x, metewing: %#x (%d)\n",  __func__,
		 ctwws->exposuwe_bias->vaw, ctwws->exposuwe_metewing->vaw, wet);

	wetuwn wet;
}

static int s5c73m3_set_white_bawance(stwuct s5c73m3 *state, int vaw)
{
	static const unsigned showt wb[][2] = {
		{ V4W2_WHITE_BAWANCE_INCANDESCENT,  COMM_AWB_MODE_INCANDESCENT},
		{ V4W2_WHITE_BAWANCE_FWUOWESCENT,   COMM_AWB_MODE_FWUOWESCENT1},
		{ V4W2_WHITE_BAWANCE_FWUOWESCENT_H, COMM_AWB_MODE_FWUOWESCENT2},
		{ V4W2_WHITE_BAWANCE_CWOUDY,        COMM_AWB_MODE_CWOUDY},
		{ V4W2_WHITE_BAWANCE_DAYWIGHT,      COMM_AWB_MODE_DAYWIGHT},
		{ V4W2_WHITE_BAWANCE_AUTO,          COMM_AWB_MODE_AUTO},
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(wb); i++) {
		if (wb[i][0] != vaw)
			continue;

		v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
			 "Setting white bawance to: %s\n",
			 v4w2_ctww_get_menu(state->ctwws.auto_wb->id)[i]);

		wetuwn s5c73m3_isp_command(state, COMM_AWB_MODE, wb[i][1]);
	}

	wetuwn -EINVAW;
}

static int s5c73m3_af_wun(stwuct s5c73m3 *state, boow on)
{
	stwuct s5c73m3_ctwws *c = &state->ctwws;

	if (!on)
		wetuwn s5c73m3_isp_command(state, COMM_AF_CON,
							COMM_AF_CON_STOP);

	if (c->focus_auto->vaw)
		wetuwn s5c73m3_isp_command(state, COMM_AF_MODE,
					   COMM_AF_MODE_PWEVIEW_CAF_STAWT);

	wetuwn s5c73m3_isp_command(state, COMM_AF_CON, COMM_AF_CON_STAWT);
}

static int s5c73m3_3a_wock(stwuct s5c73m3 *state, stwuct v4w2_ctww *ctww)
{
	boow awb_wock = ctww->vaw & V4W2_WOCK_WHITE_BAWANCE;
	boow ae_wock = ctww->vaw & V4W2_WOCK_EXPOSUWE;
	boow af_wock = ctww->vaw & V4W2_WOCK_FOCUS;
	int wet = 0;

	if ((ctww->vaw ^ ctww->cuw.vaw) & V4W2_WOCK_EXPOSUWE) {
		wet = s5c73m3_isp_command(state, COMM_AE_CON,
				ae_wock ? COMM_AE_STOP : COMM_AE_STAWT);
		if (wet)
			wetuwn wet;
	}

	if (((ctww->vaw ^ ctww->cuw.vaw) & V4W2_WOCK_WHITE_BAWANCE)
	    && state->ctwws.auto_wb->vaw) {
		wet = s5c73m3_isp_command(state, COMM_AWB_CON,
			awb_wock ? COMM_AWB_STOP : COMM_AWB_STAWT);
		if (wet)
			wetuwn wet;
	}

	if ((ctww->vaw ^ ctww->cuw.vaw) & V4W2_WOCK_FOCUS)
		wet = s5c73m3_af_wun(state, !af_wock);

	wetuwn wet;
}

static int s5c73m3_set_auto_focus(stwuct s5c73m3 *state, int caf)
{
	stwuct s5c73m3_ctwws *c = &state->ctwws;
	int wet = 1;

	if (c->af_distance->is_new) {
		u16 mode = (c->af_distance->vaw == V4W2_AUTO_FOCUS_WANGE_MACWO)
				? COMM_AF_MODE_MACWO : COMM_AF_MODE_NOWMAW;
		wet = s5c73m3_isp_command(state, COMM_AF_MODE, mode);
		if (wet != 0)
			wetuwn wet;
	}

	if (!wet || (c->focus_auto->is_new && c->focus_auto->vaw) ||
							c->af_stawt->is_new)
		wet = s5c73m3_af_wun(state, 1);
	ewse if ((c->focus_auto->is_new && !c->focus_auto->vaw) ||
							c->af_stop->is_new)
		wet = s5c73m3_af_wun(state, 0);
	ewse
		wet = 0;

	wetuwn wet;
}

static int s5c73m3_set_contwast(stwuct s5c73m3 *state, int vaw)
{
	u16 weg = (vaw < 0) ? -vaw + 2 : vaw;
	wetuwn s5c73m3_isp_command(state, COMM_CONTWAST, weg);
}

static int s5c73m3_set_satuwation(stwuct s5c73m3 *state, int vaw)
{
	u16 weg = (vaw < 0) ? -vaw + 2 : vaw;
	wetuwn s5c73m3_isp_command(state, COMM_SATUWATION, weg);
}

static int s5c73m3_set_shawpness(stwuct s5c73m3 *state, int vaw)
{
	u16 weg = (vaw < 0) ? -vaw + 2 : vaw;
	wetuwn s5c73m3_isp_command(state, COMM_SHAWPNESS, weg);
}

static int s5c73m3_set_iso(stwuct s5c73m3 *state, int vaw)
{
	u32 iso;

	if (vaw == V4W2_ISO_SENSITIVITY_MANUAW)
		iso = state->ctwws.iso->vaw + 1;
	ewse
		iso = 0;

	wetuwn s5c73m3_isp_command(state, COMM_ISO, iso);
}

static int s5c73m3_set_stabiwization(stwuct s5c73m3 *state, int vaw)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;

	v4w2_dbg(1, s5c73m3_dbg, sd, "Image stabiwization: %d\n", vaw);

	wetuwn s5c73m3_isp_command(state, COMM_FWAME_WATE, vaw ?
			COMM_FWAME_WATE_ANTI_SHAKE : COMM_FWAME_WATE_AUTO_SET);
}

static int s5c73m3_set_jpeg_quawity(stwuct s5c73m3 *state, int quawity)
{
	int weg;

	if (quawity <= 65)
		weg = COMM_IMAGE_QUAWITY_NOWMAW;
	ewse if (quawity <= 75)
		weg = COMM_IMAGE_QUAWITY_FINE;
	ewse
		weg = COMM_IMAGE_QUAWITY_SUPEWFINE;

	wetuwn s5c73m3_isp_command(state, COMM_IMAGE_QUAWITY, weg);
}

static int s5c73m3_set_scene_pwogwam(stwuct s5c73m3 *state, int vaw)
{
	static const unsigned showt scene_wookup[] = {
		COMM_SCENE_MODE_NONE,	     /* V4W2_SCENE_MODE_NONE */
		COMM_SCENE_MODE_AGAINST_WIGHT,/* V4W2_SCENE_MODE_BACKWIGHT */
		COMM_SCENE_MODE_BEACH,	     /* V4W2_SCENE_MODE_BEACH_SNOW */
		COMM_SCENE_MODE_CANDWE,	     /* V4W2_SCENE_MODE_CANDWE_WIGHT */
		COMM_SCENE_MODE_DAWN,	     /* V4W2_SCENE_MODE_DAWN_DUSK */
		COMM_SCENE_MODE_FAWW,	     /* V4W2_SCENE_MODE_FAWW_COWOWS */
		COMM_SCENE_MODE_FIWE,	     /* V4W2_SCENE_MODE_FIWEWOWKS */
		COMM_SCENE_MODE_WANDSCAPE,    /* V4W2_SCENE_MODE_WANDSCAPE */
		COMM_SCENE_MODE_NIGHT,	     /* V4W2_SCENE_MODE_NIGHT */
		COMM_SCENE_MODE_INDOOW,	     /* V4W2_SCENE_MODE_PAWTY_INDOOW */
		COMM_SCENE_MODE_POWTWAIT,     /* V4W2_SCENE_MODE_POWTWAIT */
		COMM_SCENE_MODE_SPOWTS,	     /* V4W2_SCENE_MODE_SPOWTS */
		COMM_SCENE_MODE_SUNSET,	     /* V4W2_SCENE_MODE_SUNSET */
		COMM_SCENE_MODE_TEXT,	     /* V4W2_SCENE_MODE_TEXT */
	};

	v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd, "Setting %s scene mode\n",
		 v4w2_ctww_get_menu(state->ctwws.scene_mode->id)[vaw]);

	wetuwn s5c73m3_isp_command(state, COMM_SCENE_MODE, scene_wookup[vaw]);
}

static int s5c73m3_set_powew_wine_fweq(stwuct s5c73m3 *state, int vaw)
{
	unsigned int pww_wine_fweq = COMM_FWICKEW_NONE;

	switch (vaw) {
	case V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED:
		pww_wine_fweq = COMM_FWICKEW_NONE;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ:
		pww_wine_fweq = COMM_FWICKEW_AUTO_50HZ;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ:
		pww_wine_fweq = COMM_FWICKEW_AUTO_60HZ;
		bweak;
	defauwt:
	case V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO:
		pww_wine_fweq = COMM_FWICKEW_NONE;
	}

	wetuwn s5c73m3_isp_command(state, COMM_FWICKEW_MODE, pww_wine_fweq);
}

static int s5c73m3_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_subdev *sd = ctww_to_sensow_sd(ctww);
	stwuct s5c73m3 *state = sensow_sd_to_s5c73m3(sd);
	int wet = 0;

	v4w2_dbg(1, s5c73m3_dbg, sd, "set_ctww: %s, vawue: %d\n",
		 ctww->name, ctww->vaw);

	mutex_wock(&state->wock);
	/*
	 * If the device is not powewed up by the host dwivew do
	 * not appwy any contwows to H/W at this time. Instead
	 * the contwows wiww be westowed wight aftew powew-up.
	 */
	if (state->powew == 0)
		goto unwock;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE) {
		wet = -EINVAW;
		goto unwock;
	}

	switch (ctww->id) {
	case V4W2_CID_3A_WOCK:
		wet = s5c73m3_3a_wock(state, ctww);
		bweak;

	case V4W2_CID_AUTO_N_PWESET_WHITE_BAWANCE:
		wet = s5c73m3_set_white_bawance(state, ctww->vaw);
		bweak;

	case V4W2_CID_CONTWAST:
		wet = s5c73m3_set_contwast(state, ctww->vaw);
		bweak;

	case V4W2_CID_COWOWFX:
		wet = s5c73m3_set_cowowfx(state, ctww->vaw);
		bweak;

	case V4W2_CID_EXPOSUWE_AUTO:
		wet = s5c73m3_set_exposuwe(state, ctww->vaw);
		bweak;

	case V4W2_CID_FOCUS_AUTO:
		wet = s5c73m3_set_auto_focus(state, ctww->vaw);
		bweak;

	case V4W2_CID_IMAGE_STABIWIZATION:
		wet = s5c73m3_set_stabiwization(state, ctww->vaw);
		bweak;

	case V4W2_CID_ISO_SENSITIVITY:
		wet = s5c73m3_set_iso(state, ctww->vaw);
		bweak;

	case V4W2_CID_JPEG_COMPWESSION_QUAWITY:
		wet = s5c73m3_set_jpeg_quawity(state, ctww->vaw);
		bweak;

	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		wet = s5c73m3_set_powew_wine_fweq(state, ctww->vaw);
		bweak;

	case V4W2_CID_SATUWATION:
		wet = s5c73m3_set_satuwation(state, ctww->vaw);
		bweak;

	case V4W2_CID_SCENE_MODE:
		wet = s5c73m3_set_scene_pwogwam(state, ctww->vaw);
		bweak;

	case V4W2_CID_SHAWPNESS:
		wet = s5c73m3_set_shawpness(state, ctww->vaw);
		bweak;

	case V4W2_CID_WIDE_DYNAMIC_WANGE:
		wet = s5c73m3_isp_command(state, COMM_WDW, !!ctww->vaw);
		bweak;

	case V4W2_CID_ZOOM_ABSOWUTE:
		wet = s5c73m3_isp_command(state, COMM_ZOOM_STEP, ctww->vaw);
		bweak;
	}
unwock:
	mutex_unwock(&state->wock);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops s5c73m3_ctww_ops = {
	.g_vowatiwe_ctww	= s5c73m3_g_vowatiwe_ctww,
	.s_ctww			= s5c73m3_s_ctww,
};

/* Suppowted manuaw ISO vawues */
static const s64 iso_qmenu[] = {
	/* COMM_ISO: 0x0001...0x0004 */
	100, 200, 400, 800,
};

/* Suppowted exposuwe bias vawues (-2.0EV...+2.0EV) */
static const s64 ev_bias_qmenu[] = {
	/* COMM_EV: 0x0000...0x0008 */
	-2000, -1500, -1000, -500, 0, 500, 1000, 1500, 2000
};

int s5c73m3_init_contwows(stwuct s5c73m3 *state)
{
	const stwuct v4w2_ctww_ops *ops = &s5c73m3_ctww_ops;
	stwuct s5c73m3_ctwws *ctwws = &state->ctwws;
	stwuct v4w2_ctww_handwew *hdw = &ctwws->handwew;

	int wet = v4w2_ctww_handwew_init(hdw, 22);
	if (wet)
		wetuwn wet;

	/* White bawance */
	ctwws->auto_wb = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_AUTO_N_PWESET_WHITE_BAWANCE,
			9, ~0x15e, V4W2_WHITE_BAWANCE_AUTO);

	/* Exposuwe (onwy automatic exposuwe) */
	ctwws->auto_exposuwe = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_EXPOSUWE_AUTO, 0, ~0x01, V4W2_EXPOSUWE_AUTO);

	ctwws->exposuwe_bias = v4w2_ctww_new_int_menu(hdw, ops,
			V4W2_CID_AUTO_EXPOSUWE_BIAS,
			AWWAY_SIZE(ev_bias_qmenu) - 1,
			AWWAY_SIZE(ev_bias_qmenu)/2 - 1,
			ev_bias_qmenu);

	ctwws->exposuwe_metewing = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_EXPOSUWE_METEWING,
			2, ~0x7, V4W2_EXPOSUWE_METEWING_AVEWAGE);

	/* Auto focus */
	ctwws->focus_auto = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_FOCUS_AUTO, 0, 1, 1, 0);

	ctwws->af_stawt = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_AUTO_FOCUS_STAWT, 0, 1, 1, 0);

	ctwws->af_stop = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_AUTO_FOCUS_STOP, 0, 1, 1, 0);

	ctwws->af_status = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_AUTO_FOCUS_STATUS, 0,
			(V4W2_AUTO_FOCUS_STATUS_BUSY |
			 V4W2_AUTO_FOCUS_STATUS_WEACHED |
			 V4W2_AUTO_FOCUS_STATUS_FAIWED),
			0, V4W2_AUTO_FOCUS_STATUS_IDWE);

	ctwws->af_distance = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_AUTO_FOCUS_WANGE,
			V4W2_AUTO_FOCUS_WANGE_MACWO,
			~(1 << V4W2_AUTO_FOCUS_WANGE_NOWMAW |
			  1 << V4W2_AUTO_FOCUS_WANGE_MACWO),
			V4W2_AUTO_FOCUS_WANGE_NOWMAW);
	/* ISO sensitivity */
	ctwws->auto_iso = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_ISO_SENSITIVITY_AUTO, 1, 0,
			V4W2_ISO_SENSITIVITY_AUTO);

	ctwws->iso = v4w2_ctww_new_int_menu(hdw, ops,
			V4W2_CID_ISO_SENSITIVITY, AWWAY_SIZE(iso_qmenu) - 1,
			AWWAY_SIZE(iso_qmenu)/2 - 1, iso_qmenu);

	ctwws->contwast = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_CONTWAST, -2, 2, 1, 0);

	ctwws->satuwation = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_SATUWATION, -2, 2, 1, 0);

	ctwws->shawpness = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_SHAWPNESS, -2, 2, 1, 0);

	ctwws->zoom = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_ZOOM_ABSOWUTE, 0, 30, 1, 0);

	ctwws->cowowfx = v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_COWOWFX,
			V4W2_COWOWFX_AQUA, ~0x40f, V4W2_COWOWFX_NONE);

	ctwws->wdw = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_WIDE_DYNAMIC_WANGE, 0, 1, 1, 0);

	ctwws->stabiwization = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_IMAGE_STABIWIZATION, 0, 1, 1, 0);

	v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_POWEW_WINE_FWEQUENCY,
			       V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO, 0,
			       V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO);

	ctwws->jpeg_quawity = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_JPEG_COMPWESSION_QUAWITY, 1, 100, 1, 80);

	ctwws->scene_mode = v4w2_ctww_new_std_menu(hdw, ops,
			V4W2_CID_SCENE_MODE, V4W2_SCENE_MODE_TEXT, ~0x3fff,
			V4W2_SCENE_MODE_NONE);

	ctwws->aaa_wock = v4w2_ctww_new_std(hdw, ops,
			V4W2_CID_3A_WOCK, 0, 0x7, 0, 0);

	if (hdw->ewwow) {
		wet = hdw->ewwow;
		v4w2_ctww_handwew_fwee(hdw);
		wetuwn wet;
	}

	v4w2_ctww_auto_cwustew(3, &ctwws->auto_exposuwe, 0, fawse);
	ctwws->auto_iso->fwags |= V4W2_CTWW_FWAG_VOWATIWE |
				V4W2_CTWW_FWAG_UPDATE;
	v4w2_ctww_auto_cwustew(2, &ctwws->auto_iso, 0, fawse);
	ctwws->af_status->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	v4w2_ctww_cwustew(5, &ctwws->focus_auto);

	state->sensow_sd.ctww_handwew = hdw;

	wetuwn 0;
}
