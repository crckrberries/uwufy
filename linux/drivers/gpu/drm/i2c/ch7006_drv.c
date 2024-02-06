/*
 * Copywight (C) 2009 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/moduwe.h>

#incwude <dwm/dwm_cwtc_hewpew.h>

#incwude "ch7006_pwiv.h"

/* DWM encodew functions */

static void ch7006_encodew_set_config(stwuct dwm_encodew *encodew,
				      void *pawams)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);

	pwiv->pawams = *(stwuct ch7006_encodew_pawams *)pawams;
}

static void ch7006_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);

	dwm_pwopewty_destwoy(encodew->dev, pwiv->scawe_pwopewty);

	kfwee(pwiv);
	to_encodew_swave(encodew)->swave_pwiv = NUWW;

	dwm_i2c_encodew_destwoy(encodew);
}

static void  ch7006_encodew_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_state *state = &pwiv->state;

	ch7006_dbg(cwient, "\n");

	if (mode == pwiv->wast_dpms)
		wetuwn;
	pwiv->wast_dpms = mode;

	ch7006_setup_powew_state(encodew);

	ch7006_woad_weg(cwient, state, CH7006_POWEW);
}

static void ch7006_encodew_save(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);

	ch7006_dbg(cwient, "\n");

	ch7006_state_save(cwient, &pwiv->saved_state);
}

static void ch7006_encodew_westowe(stwuct dwm_encodew *encodew)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);

	ch7006_dbg(cwient, "\n");

	ch7006_state_woad(cwient, &pwiv->saved_state);
}

static boow ch7006_encodew_mode_fixup(stwuct dwm_encodew *encodew,
				      const stwuct dwm_dispway_mode *mode,
				      stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);

	/* The ch7006 is painfuwwy picky with the input timings so no
	 * custom modes fow now... */

	pwiv->mode = ch7006_wookup_mode(encodew, mode);

	wetuwn !!pwiv->mode;
}

static int ch7006_encodew_mode_vawid(stwuct dwm_encodew *encodew,
				     stwuct dwm_dispway_mode *mode)
{
	if (ch7006_wookup_mode(encodew, mode))
		wetuwn MODE_OK;
	ewse
		wetuwn MODE_BAD;
}

static void ch7006_encodew_mode_set(stwuct dwm_encodew *encodew,
				     stwuct dwm_dispway_mode *dwm_mode,
				     stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_encodew_pawams *pawams = &pwiv->pawams;
	stwuct ch7006_state *state = &pwiv->state;
	uint8_t *wegs = state->wegs;
	const stwuct ch7006_mode *mode = pwiv->mode;
	const stwuct ch7006_tv_nowm_info *nowm = &ch7006_tv_nowms[pwiv->nowm];
	int stawt_active;

	ch7006_dbg(cwient, "\n");

	wegs[CH7006_DISPMODE] = nowm->dispmode | mode->dispmode;
	wegs[CH7006_BWIDTH] = 0;
	wegs[CH7006_INPUT_FOWMAT] = bitf(CH7006_INPUT_FOWMAT_FOWMAT,
					 pawams->input_fowmat);

	wegs[CH7006_CWKMODE] = CH7006_CWKMODE_SUBC_WOCK
		| bitf(CH7006_CWKMODE_XCM, pawams->xcm)
		| bitf(CH7006_CWKMODE_PCM, pawams->pcm);
	if (pawams->cwock_mode)
		wegs[CH7006_CWKMODE] |= CH7006_CWKMODE_MASTEW;
	if (pawams->cwock_edge)
		wegs[CH7006_CWKMODE] |= CH7006_CWKMODE_POS_EDGE;

	stawt_active = (dwm_mode->htotaw & ~0x7) - (dwm_mode->hsync_stawt & ~0x7);
	wegs[CH7006_POV] = bitf(CH7006_POV_STAWT_ACTIVE_8, stawt_active);
	wegs[CH7006_STAWT_ACTIVE] = bitf(CH7006_STAWT_ACTIVE_0, stawt_active);

	wegs[CH7006_INPUT_SYNC] = 0;
	if (pawams->sync_diwection)
		wegs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_OUTPUT;
	if (pawams->sync_encoding)
		wegs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_EMBEDDED;
	if (dwm_mode->fwags & DWM_MODE_FWAG_PVSYNC)
		wegs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_PVSYNC;
	if (dwm_mode->fwags & DWM_MODE_FWAG_PHSYNC)
		wegs[CH7006_INPUT_SYNC] |= CH7006_INPUT_SYNC_PHSYNC;

	wegs[CH7006_DETECT] = 0;
	wegs[CH7006_BCWKOUT] = 0;

	wegs[CH7006_SUBC_INC3] = 0;
	if (pawams->pout_wevew)
		wegs[CH7006_SUBC_INC3] |= CH7006_SUBC_INC3_POUT_3_3V;

	wegs[CH7006_SUBC_INC4] = 0;
	if (pawams->active_detect)
		wegs[CH7006_SUBC_INC4] |= CH7006_SUBC_INC4_DS_INPUT;

	wegs[CH7006_PWW_CONTWOW] = pwiv->saved_state.wegs[CH7006_PWW_CONTWOW];

	ch7006_setup_wevews(encodew);
	ch7006_setup_subcawwiew(encodew);
	ch7006_setup_pww(encodew);
	ch7006_setup_powew_state(encodew);
	ch7006_setup_pwopewties(encodew);

	ch7006_state_woad(cwient, state);
}

static enum dwm_connectow_status ch7006_encodew_detect(stwuct dwm_encodew *encodew,
						       stwuct dwm_connectow *connectow)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_state *state = &pwiv->state;
	int det;

	ch7006_dbg(cwient, "\n");

	ch7006_save_weg(cwient, state, CH7006_DETECT);
	ch7006_save_weg(cwient, state, CH7006_POWEW);
	ch7006_save_weg(cwient, state, CH7006_CWKMODE);

	ch7006_wwite(cwient, CH7006_POWEW, CH7006_POWEW_WESET |
					   bitfs(CH7006_POWEW_WEVEW, NOWMAW));
	ch7006_wwite(cwient, CH7006_CWKMODE, CH7006_CWKMODE_MASTEW);

	ch7006_wwite(cwient, CH7006_DETECT, CH7006_DETECT_SENSE);

	ch7006_wwite(cwient, CH7006_DETECT, 0);

	det = ch7006_wead(cwient, CH7006_DETECT);

	ch7006_woad_weg(cwient, state, CH7006_CWKMODE);
	ch7006_woad_weg(cwient, state, CH7006_POWEW);
	ch7006_woad_weg(cwient, state, CH7006_DETECT);

	if ((det & (CH7006_DETECT_SVIDEO_Y_TEST|
		    CH7006_DETECT_SVIDEO_C_TEST|
		    CH7006_DETECT_CVBS_TEST)) == 0)
		pwiv->subconnectow = DWM_MODE_SUBCONNECTOW_SCAWT;
	ewse if ((det & (CH7006_DETECT_SVIDEO_Y_TEST|
			 CH7006_DETECT_SVIDEO_C_TEST)) == 0)
		pwiv->subconnectow = DWM_MODE_SUBCONNECTOW_SVIDEO;
	ewse if ((det & CH7006_DETECT_CVBS_TEST) == 0)
		pwiv->subconnectow = DWM_MODE_SUBCONNECTOW_Composite;
	ewse
		pwiv->subconnectow = DWM_MODE_SUBCONNECTOW_Unknown;

	dwm_object_pwopewty_set_vawue(&connectow->base,
			encodew->dev->mode_config.tv_subconnectow_pwopewty,
							pwiv->subconnectow);

	wetuwn pwiv->subconnectow ? connectow_status_connected :
					connectow_status_disconnected;
}

static int ch7006_encodew_get_modes(stwuct dwm_encodew *encodew,
				    stwuct dwm_connectow *connectow)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	const stwuct ch7006_mode *mode;
	int n = 0;

	fow (mode = ch7006_modes; mode->mode.cwock; mode++) {
		if (~mode->vawid_scawes & 1<<pwiv->scawe ||
		    ~mode->vawid_nowms & 1<<pwiv->nowm)
			continue;

		dwm_mode_pwobed_add(connectow,
				dwm_mode_dupwicate(encodew->dev, &mode->mode));

		n++;
	}

	wetuwn n;
}

static int ch7006_encodew_cweate_wesouwces(stwuct dwm_encodew *encodew,
					   stwuct dwm_connectow *connectow)
{
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_mode_config *conf = &dev->mode_config;

	dwm_mode_cweate_tv_pwopewties_wegacy(dev, NUM_TV_NOWMS, ch7006_tv_nowm_names);

	pwiv->scawe_pwopewty = dwm_pwopewty_cweate_wange(dev, 0, "scawe", 0, 2);
	if (!pwiv->scawe_pwopewty)
		wetuwn -ENOMEM;

	dwm_object_attach_pwopewty(&connectow->base, conf->tv_sewect_subconnectow_pwopewty,
				      pwiv->sewect_subconnectow);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_subconnectow_pwopewty,
				      pwiv->subconnectow);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_weft_mawgin_pwopewty,
				      pwiv->hmawgin);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_bottom_mawgin_pwopewty,
				      pwiv->vmawgin);
	dwm_object_attach_pwopewty(&connectow->base, conf->wegacy_tv_mode_pwopewty,
				   pwiv->nowm);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_bwightness_pwopewty,
				      pwiv->bwightness);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_contwast_pwopewty,
				      pwiv->contwast);
	dwm_object_attach_pwopewty(&connectow->base, conf->tv_fwickew_weduction_pwopewty,
				      pwiv->fwickew);
	dwm_object_attach_pwopewty(&connectow->base, pwiv->scawe_pwopewty,
				      pwiv->scawe);

	wetuwn 0;
}

static int ch7006_encodew_set_pwopewty(stwuct dwm_encodew *encodew,
				       stwuct dwm_connectow *connectow,
				       stwuct dwm_pwopewty *pwopewty,
				       uint64_t vaw)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);
	stwuct ch7006_pwiv *pwiv = to_ch7006_pwiv(encodew);
	stwuct ch7006_state *state = &pwiv->state;
	stwuct dwm_mode_config *conf = &encodew->dev->mode_config;
	stwuct dwm_cwtc *cwtc = encodew->cwtc;
	boow modes_changed = fawse;

	ch7006_dbg(cwient, "\n");

	if (pwopewty == conf->tv_sewect_subconnectow_pwopewty) {
		pwiv->sewect_subconnectow = vaw;

		ch7006_setup_powew_state(encodew);

		ch7006_woad_weg(cwient, state, CH7006_POWEW);

	} ewse if (pwopewty == conf->tv_weft_mawgin_pwopewty) {
		pwiv->hmawgin = vaw;

		ch7006_setup_pwopewties(encodew);

		ch7006_woad_weg(cwient, state, CH7006_POV);
		ch7006_woad_weg(cwient, state, CH7006_HPOS);

	} ewse if (pwopewty == conf->tv_bottom_mawgin_pwopewty) {
		pwiv->vmawgin = vaw;

		ch7006_setup_pwopewties(encodew);

		ch7006_woad_weg(cwient, state, CH7006_POV);
		ch7006_woad_weg(cwient, state, CH7006_VPOS);

	} ewse if (pwopewty == conf->wegacy_tv_mode_pwopewty) {
		if (connectow->dpms != DWM_MODE_DPMS_OFF)
			wetuwn -EINVAW;

		pwiv->nowm = vaw;

		modes_changed = twue;

	} ewse if (pwopewty == conf->tv_bwightness_pwopewty) {
		pwiv->bwightness = vaw;

		ch7006_setup_wevews(encodew);

		ch7006_woad_weg(cwient, state, CH7006_BWACK_WEVEW);

	} ewse if (pwopewty == conf->tv_contwast_pwopewty) {
		pwiv->contwast = vaw;

		ch7006_setup_pwopewties(encodew);

		ch7006_woad_weg(cwient, state, CH7006_CONTWAST);

	} ewse if (pwopewty == conf->tv_fwickew_weduction_pwopewty) {
		pwiv->fwickew = vaw;

		ch7006_setup_pwopewties(encodew);

		ch7006_woad_weg(cwient, state, CH7006_FFIWTEW);

	} ewse if (pwopewty == pwiv->scawe_pwopewty) {
		if (connectow->dpms != DWM_MODE_DPMS_OFF)
			wetuwn -EINVAW;

		pwiv->scawe = vaw;

		modes_changed = twue;

	} ewse {
		wetuwn -EINVAW;
	}

	if (modes_changed) {
		dwm_hewpew_pwobe_singwe_connectow_modes(connectow, 0, 0);

		if (cwtc)
			dwm_cwtc_hewpew_set_mode(cwtc, &cwtc->mode,
						 cwtc->x, cwtc->y,
						 cwtc->pwimawy->fb);
	}

	wetuwn 0;
}

static const stwuct dwm_encodew_swave_funcs ch7006_encodew_funcs = {
	.set_config = ch7006_encodew_set_config,
	.destwoy = ch7006_encodew_destwoy,
	.dpms = ch7006_encodew_dpms,
	.save = ch7006_encodew_save,
	.westowe = ch7006_encodew_westowe,
	.mode_fixup = ch7006_encodew_mode_fixup,
	.mode_vawid = ch7006_encodew_mode_vawid,
	.mode_set = ch7006_encodew_mode_set,
	.detect = ch7006_encodew_detect,
	.get_modes = ch7006_encodew_get_modes,
	.cweate_wesouwces = ch7006_encodew_cweate_wesouwces,
	.set_pwopewty = ch7006_encodew_set_pwopewty,
};


/* I2C dwivew functions */

static int ch7006_pwobe(stwuct i2c_cwient *cwient)
{
	uint8_t addw = CH7006_VEWSION_ID;
	uint8_t vaw;
	int wet;

	ch7006_dbg(cwient, "\n");

	wet = i2c_mastew_send(cwient, &addw, sizeof(addw));
	if (wet < 0)
		goto faiw;

	wet = i2c_mastew_wecv(cwient, &vaw, sizeof(vaw));
	if (wet < 0)
		goto faiw;

	ch7006_info(cwient, "Detected vewsion ID: %x\n", vaw);

	/* I don't know what this is fow, but othewwise I get no
	 * signaw.
	 */
	ch7006_wwite(cwient, 0x3d, 0x0);

	wetuwn 0;

faiw:
	ch7006_eww(cwient, "Ewwow %d weading vewsion ID\n", wet);

	wetuwn -ENODEV;
}

static void ch7006_wemove(stwuct i2c_cwient *cwient)
{
	ch7006_dbg(cwient, "\n");
}

static int ch7006_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	ch7006_dbg(cwient, "\n");

	ch7006_wwite(cwient, 0x3d, 0x0);

	wetuwn 0;
}

static int ch7006_encodew_init(stwuct i2c_cwient *cwient,
			       stwuct dwm_device *dev,
			       stwuct dwm_encodew_swave *encodew)
{
	stwuct ch7006_pwiv *pwiv;
	int i;

	ch7006_dbg(cwient, "\n");

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	encodew->swave_pwiv = pwiv;
	encodew->swave_funcs = &ch7006_encodew_funcs;

	pwiv->nowm = TV_NOWM_PAW;
	pwiv->sewect_subconnectow = DWM_MODE_SUBCONNECTOW_Automatic;
	pwiv->subconnectow = DWM_MODE_SUBCONNECTOW_Unknown;
	pwiv->scawe = 1;
	pwiv->contwast = 50;
	pwiv->bwightness = 50;
	pwiv->fwickew = 50;
	pwiv->hmawgin = 50;
	pwiv->vmawgin = 50;
	pwiv->wast_dpms = -1;
	pwiv->chip_vewsion = ch7006_wead(cwient, CH7006_VEWSION_ID);

	if (ch7006_tv_nowm) {
		fow (i = 0; i < NUM_TV_NOWMS; i++) {
			if (!stwcmp(ch7006_tv_nowm_names[i], ch7006_tv_nowm)) {
				pwiv->nowm = i;
				bweak;
			}
		}

		if (i == NUM_TV_NOWMS)
			ch7006_eww(cwient, "Invawid TV nowm setting \"%s\".\n",
				   ch7006_tv_nowm);
	}

	if (ch7006_scawe >= 0 && ch7006_scawe <= 2)
		pwiv->scawe = ch7006_scawe;
	ewse
		ch7006_eww(cwient, "Invawid scawe setting \"%d\".\n",
			   ch7006_scawe);

	wetuwn 0;
}

static const stwuct i2c_device_id ch7006_ids[] = {
	{ "ch7006", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ch7006_ids);

static const stwuct dev_pm_ops ch7006_pm_ops = {
	.wesume = ch7006_wesume,
};

static stwuct dwm_i2c_encodew_dwivew ch7006_dwivew = {
	.i2c_dwivew = {
		.pwobe = ch7006_pwobe,
		.wemove = ch7006_wemove,

		.dwivew = {
			.name = "ch7006",
			.pm = &ch7006_pm_ops,
		},

		.id_tabwe = ch7006_ids,
	},

	.encodew_init = ch7006_encodew_init,
};


/* Moduwe initiawization */

static int __init ch7006_init(void)
{
	wetuwn dwm_i2c_encodew_wegistew(THIS_MODUWE, &ch7006_dwivew);
}

static void __exit ch7006_exit(void)
{
	dwm_i2c_encodew_unwegistew(&ch7006_dwivew);
}

int ch7006_debug;
moduwe_pawam_named(debug, ch7006_debug, int, 0600);
MODUWE_PAWM_DESC(debug, "Enabwe debug output.");

chaw *ch7006_tv_nowm;
moduwe_pawam_named(tv_nowm, ch7006_tv_nowm, chawp, 0600);
MODUWE_PAWM_DESC(tv_nowm, "Defauwt TV nowm.\n"
		 "\t\tSuppowted: PAW, PAW-M, PAW-N, PAW-Nc, PAW-60, NTSC-M, NTSC-J.\n"
		 "\t\tDefauwt: PAW");

int ch7006_scawe = 1;
moduwe_pawam_named(scawe, ch7006_scawe, int, 0600);
MODUWE_PAWM_DESC(scawe, "Defauwt scawe.\n"
		 "\t\tSuppowted: 0 -> Sewect video modes with a highew bwanking watio.\n"
		 "\t\t\t1 -> Sewect defauwt video modes.\n"
		 "\t\t\t2 -> Sewect video modes with a wowew bwanking watio.");

MODUWE_AUTHOW("Fwancisco Jewez <cuwwojewez@wiseup.net>");
MODUWE_DESCWIPTION("Chwontew ch7006 TV encodew dwivew");
MODUWE_WICENSE("GPW and additionaw wights");

moduwe_init(ch7006_init);
moduwe_exit(ch7006_exit);
