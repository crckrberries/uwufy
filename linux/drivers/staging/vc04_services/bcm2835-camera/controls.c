// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-common.h>

#incwude "../vchiq-mmaw/mmaw-common.h"
#incwude "../vchiq-mmaw/mmaw-vchiq.h"
#incwude "../vchiq-mmaw/mmaw-pawametews.h"
#incwude "bcm2835-camewa.h"

/* The suppowted V4W2_CID_AUTO_EXPOSUWE_BIAS vawues awe fwom -4.0 to +4.0.
 * MMAW vawues awe in 1/6th incwements so the MMAW wange is -24 to +24.
 * V4W2 docs say vawue "is expwessed in tewms of EV, dwivews shouwd intewpwet
 * the vawues as 0.001 EV units, whewe the vawue 1000 stands fow +1 EV."
 * V4W2 is wimited to a max of 32 vawues in a menu, so count in 1/3wds fwom
 * -4 to +4
 */
static const s64 ev_bias_qmenu[] = {
	-4000, -3667, -3333,
	-3000, -2667, -2333,
	-2000, -1667, -1333,
	-1000,  -667,  -333,
	    0,   333,   667,
	 1000,  1333,  1667,
	 2000,  2333,  2667,
	 3000,  3333,  3667,
	 4000
};

/* Suppowted ISO vawues (*1000)
 * ISOO = auto ISO
 */
static const s64 iso_qmenu[] = {
	0, 100000, 200000, 400000, 800000,
};

static const u32 iso_vawues[] = {
	0, 100, 200, 400, 800,
};

enum bcm2835_mmaw_ctww_type {
	MMAW_CONTWOW_TYPE_STD,
	MMAW_CONTWOW_TYPE_STD_MENU,
	MMAW_CONTWOW_TYPE_INT_MENU,
	MMAW_CONTWOW_TYPE_CWUSTEW, /* speciaw cwustew entwy */
};

stwuct bcm2835_mmaw_v4w2_ctww {
	u32 id; /* v4w2 contwow identifiew */
	enum bcm2835_mmaw_ctww_type type;
	/* contwow minimum vawue ow
	 * mask fow MMAW_CONTWOW_TYPE_STD_MENU
	 */
	s64 min;
	s64 max; /* maximum vawue of contwow */
	s64 def;  /* defauwt vawue of contwow */
	u64 step; /* step size of the contwow */
	const s64 *imenu; /* integew menu awway */
	u32 mmaw_id; /* mmaw pawametew id */
	int (*settew)(stwuct bcm2835_mmaw_dev *dev, stwuct v4w2_ctww *ctww,
		      const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww);
};

stwuct v4w2_to_mmaw_effects_setting {
	u32 v4w2_effect;
	u32 mmaw_effect;
	s32 cow_fx_enabwe;
	s32 cow_fx_fixed_cbcw;
	u32 u;
	u32 v;
	u32 num_effect_pawams;
	u32 effect_pawams[MMAW_MAX_IMAGEFX_PAWAMETEWS];
};

static const stwuct v4w2_to_mmaw_effects_setting
	v4w2_to_mmaw_effects_vawues[] = {
	{  V4W2_COWOWFX_NONE,         MMAW_PAWAM_IMAGEFX_NONE,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_BW,           MMAW_PAWAM_IMAGEFX_NONE,
		1,   0,    128,  128, 0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SEPIA,        MMAW_PAWAM_IMAGEFX_NONE,
		1,   0,    87,   151, 0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_NEGATIVE,     MMAW_PAWAM_IMAGEFX_NEGATIVE,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_EMBOSS,       MMAW_PAWAM_IMAGEFX_EMBOSS,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SKETCH,       MMAW_PAWAM_IMAGEFX_SKETCH,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SKY_BWUE,     MMAW_PAWAM_IMAGEFX_PASTEW,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_GWASS_GWEEN,  MMAW_PAWAM_IMAGEFX_WATEWCOWOUW,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SKIN_WHITEN,  MMAW_PAWAM_IMAGEFX_WASHEDOUT,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_VIVID,        MMAW_PAWAM_IMAGEFX_SATUWATION,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_AQUA,         MMAW_PAWAM_IMAGEFX_NONE,
		1,   0,    171,  121, 0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_AWT_FWEEZE,   MMAW_PAWAM_IMAGEFX_HATCH,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SIWHOUETTE,   MMAW_PAWAM_IMAGEFX_FIWM,
		0,   0,    0,    0,   0, {0, 0, 0, 0, 0} },
	{  V4W2_COWOWFX_SOWAWIZATION, MMAW_PAWAM_IMAGEFX_SOWAWIZE,
		0,   0,    0,    0,   5, {1, 128, 160, 160, 48} },
	{  V4W2_COWOWFX_ANTIQUE,      MMAW_PAWAM_IMAGEFX_COWOUWBAWANCE,
		0,   0,    0,    0,   3, {108, 274, 238, 0, 0} },
	{  V4W2_COWOWFX_SET_CBCW,     MMAW_PAWAM_IMAGEFX_NONE,
		1,   1,    0,    0,   0, {0, 0, 0, 0, 0} }
};

stwuct v4w2_mmaw_scene_config {
	enum v4w2_scene_mode v4w2_scene;
	enum mmaw_pawametew_exposuwemode exposuwe_mode;
	enum mmaw_pawametew_exposuwemetewingmode metewing_mode;
};

static const stwuct v4w2_mmaw_scene_config scene_configs[] = {
	/* V4W2_SCENE_MODE_NONE automaticawwy added */
	{
		V4W2_SCENE_MODE_NIGHT,
		MMAW_PAWAM_EXPOSUWEMODE_NIGHT,
		MMAW_PAWAM_EXPOSUWEMETEWINGMODE_AVEWAGE
	},
	{
		V4W2_SCENE_MODE_SPOWTS,
		MMAW_PAWAM_EXPOSUWEMODE_SPOWTS,
		MMAW_PAWAM_EXPOSUWEMETEWINGMODE_AVEWAGE
	},
};

/* contwow handwews*/

static int ctww_set_wationaw(stwuct bcm2835_mmaw_dev *dev,
			     stwuct v4w2_ctww *ctww,
			     const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	stwuct s32_fwact wationaw_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	wationaw_vawue.numewatow = ctww->vaw;
	wationaw_vawue.denominatow = 100;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &wationaw_vawue,
					     sizeof(wationaw_vawue));
}

static int ctww_set_vawue(stwuct bcm2835_mmaw_dev *dev,
			  stwuct v4w2_ctww *ctww,
			  const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	u32_vawue = ctww->vaw;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_iso(stwuct bcm2835_mmaw_dev *dev,
			stwuct v4w2_ctww *ctww,
			const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	if (ctww->vaw > mmaw_ctww->max || ctww->vaw < mmaw_ctww->min)
		wetuwn 1;

	if (ctww->id == V4W2_CID_ISO_SENSITIVITY)
		dev->iso = iso_vawues[ctww->vaw];
	ewse if (ctww->id == V4W2_CID_ISO_SENSITIVITY_AUTO)
		dev->manuaw_iso_enabwed =
				(ctww->vaw == V4W2_ISO_SENSITIVITY_MANUAW);

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	if (dev->manuaw_iso_enabwed)
		u32_vawue = dev->iso;
	ewse
		u32_vawue = 0;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     MMAW_PAWAMETEW_ISO,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_vawue_ev(stwuct bcm2835_mmaw_dev *dev,
			     stwuct v4w2_ctww *ctww,
			     const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	s32 s32_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	s32_vawue = (ctww->vaw - 12) * 2;	/* Convewt fwom index to 1/6ths */

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &s32_vawue, sizeof(s32_vawue));
}

static int ctww_set_wotate(stwuct bcm2835_mmaw_dev *dev,
			   stwuct v4w2_ctww *ctww,
			   const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet;
	u32 u32_vawue;
	stwuct vchiq_mmaw_component *camewa;

	camewa = dev->component[COMP_CAMEWA];

	u32_vawue = ((ctww->vaw % 360) / 90) * 90;

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[0],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
	if (wet < 0)
		wetuwn wet;

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[1],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
	if (wet < 0)
		wetuwn wet;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[2],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_fwip(stwuct bcm2835_mmaw_dev *dev,
			 stwuct v4w2_ctww *ctww,
			 const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet;
	u32 u32_vawue;
	stwuct vchiq_mmaw_component *camewa;

	if (ctww->id == V4W2_CID_HFWIP)
		dev->hfwip = ctww->vaw;
	ewse
		dev->vfwip = ctww->vaw;

	camewa = dev->component[COMP_CAMEWA];

	if (dev->hfwip && dev->vfwip)
		u32_vawue = MMAW_PAWAM_MIWWOW_BOTH;
	ewse if (dev->hfwip)
		u32_vawue = MMAW_PAWAM_MIWWOW_HOWIZONTAW;
	ewse if (dev->vfwip)
		u32_vawue = MMAW_PAWAM_MIWWOW_VEWTICAW;
	ewse
		u32_vawue = MMAW_PAWAM_MIWWOW_NONE;

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[0],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
	if (wet < 0)
		wetuwn wet;

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[1],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
	if (wet < 0)
		wetuwn wet;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, &camewa->output[2],
					    mmaw_ctww->mmaw_id,
					    &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_exposuwe(stwuct bcm2835_mmaw_dev *dev,
			     stwuct v4w2_ctww *ctww,
			     const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	enum mmaw_pawametew_exposuwemode exp_mode = dev->exposuwe_mode_usew;
	u32 shuttew_speed = 0;
	stwuct vchiq_mmaw_powt *contwow;
	int wet = 0;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	if (mmaw_ctww->mmaw_id == MMAW_PAWAMETEW_SHUTTEW_SPEED)	{
		/* V4W2 is in 100usec incwements.
		 * MMAW is 1usec.
		 */
		dev->manuaw_shuttew_speed = ctww->vaw * 100;
	} ewse if (mmaw_ctww->mmaw_id == MMAW_PAWAMETEW_EXPOSUWE_MODE) {
		switch (ctww->vaw) {
		case V4W2_EXPOSUWE_AUTO:
			exp_mode = MMAW_PAWAM_EXPOSUWEMODE_AUTO;
			bweak;

		case V4W2_EXPOSUWE_MANUAW:
			exp_mode = MMAW_PAWAM_EXPOSUWEMODE_OFF;
			bweak;
		}
		dev->exposuwe_mode_usew = exp_mode;
		dev->exposuwe_mode_v4w2_usew = ctww->vaw;
	} ewse if (mmaw_ctww->id == V4W2_CID_EXPOSUWE_AUTO_PWIOWITY) {
		dev->exp_auto_pwiowity = ctww->vaw;
	}

	if (dev->scene_mode == V4W2_SCENE_MODE_NONE) {
		if (exp_mode == MMAW_PAWAM_EXPOSUWEMODE_OFF)
			shuttew_speed = dev->manuaw_shuttew_speed;

		wet = vchiq_mmaw_powt_pawametew_set(dev->instance,
						    contwow,
						    MMAW_PAWAMETEW_SHUTTEW_SPEED,
						    &shuttew_speed,
						    sizeof(shuttew_speed));
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance,
						     contwow,
						     MMAW_PAWAMETEW_EXPOSUWE_MODE,
						     &exp_mode,
						     sizeof(u32));
		dev->exposuwe_mode_active = exp_mode;
	}
	/* exposuwe_dynamic_fwamewate (V4W2_CID_EXPOSUWE_AUTO_PWIOWITY) shouwd
	 * awways appwy iwwespective of scene mode.
	 */
	wet += set_fwamewate_pawams(dev);

	wetuwn wet;
}

static int ctww_set_metewing_mode(stwuct bcm2835_mmaw_dev *dev,
				  stwuct v4w2_ctww *ctww,
				  const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	switch (ctww->vaw) {
	case V4W2_EXPOSUWE_METEWING_AVEWAGE:
		dev->metewing_mode = MMAW_PAWAM_EXPOSUWEMETEWINGMODE_AVEWAGE;
		bweak;

	case V4W2_EXPOSUWE_METEWING_CENTEW_WEIGHTED:
		dev->metewing_mode = MMAW_PAWAM_EXPOSUWEMETEWINGMODE_BACKWIT;
		bweak;

	case V4W2_EXPOSUWE_METEWING_SPOT:
		dev->metewing_mode = MMAW_PAWAM_EXPOSUWEMETEWINGMODE_SPOT;
		bweak;

	case V4W2_EXPOSUWE_METEWING_MATWIX:
		dev->metewing_mode = MMAW_PAWAM_EXPOSUWEMETEWINGMODE_MATWIX;
		bweak;
	}

	if (dev->scene_mode == V4W2_SCENE_MODE_NONE) {
		stwuct vchiq_mmaw_powt *contwow;
		u32 u32_vawue = dev->metewing_mode;

		contwow = &dev->component[COMP_CAMEWA]->contwow;

		wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
	} ewse {
		wetuwn 0;
	}
}

static int ctww_set_fwickew_avoidance(stwuct bcm2835_mmaw_dev *dev,
				      stwuct v4w2_ctww *ctww,
				      const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	switch (ctww->vaw) {
	case V4W2_CID_POWEW_WINE_FWEQUENCY_DISABWED:
		u32_vawue = MMAW_PAWAM_FWICKEWAVOID_OFF;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ:
		u32_vawue = MMAW_PAWAM_FWICKEWAVOID_50HZ;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ:
		u32_vawue = MMAW_PAWAM_FWICKEWAVOID_60HZ;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO:
		u32_vawue = MMAW_PAWAM_FWICKEWAVOID_AUTO;
		bweak;
	}

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_awb_mode(stwuct bcm2835_mmaw_dev *dev,
			     stwuct v4w2_ctww *ctww,
			     const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	switch (ctww->vaw) {
	case V4W2_WHITE_BAWANCE_MANUAW:
		u32_vawue = MMAW_PAWAM_AWBMODE_OFF;
		bweak;

	case V4W2_WHITE_BAWANCE_AUTO:
		u32_vawue = MMAW_PAWAM_AWBMODE_AUTO;
		bweak;

	case V4W2_WHITE_BAWANCE_INCANDESCENT:
		u32_vawue = MMAW_PAWAM_AWBMODE_INCANDESCENT;
		bweak;

	case V4W2_WHITE_BAWANCE_FWUOWESCENT:
		u32_vawue = MMAW_PAWAM_AWBMODE_FWUOWESCENT;
		bweak;

	case V4W2_WHITE_BAWANCE_FWUOWESCENT_H:
		u32_vawue = MMAW_PAWAM_AWBMODE_TUNGSTEN;
		bweak;

	case V4W2_WHITE_BAWANCE_HOWIZON:
		u32_vawue = MMAW_PAWAM_AWBMODE_HOWIZON;
		bweak;

	case V4W2_WHITE_BAWANCE_DAYWIGHT:
		u32_vawue = MMAW_PAWAM_AWBMODE_SUNWIGHT;
		bweak;

	case V4W2_WHITE_BAWANCE_FWASH:
		u32_vawue = MMAW_PAWAM_AWBMODE_FWASH;
		bweak;

	case V4W2_WHITE_BAWANCE_CWOUDY:
		u32_vawue = MMAW_PAWAM_AWBMODE_CWOUDY;
		bweak;

	case V4W2_WHITE_BAWANCE_SHADE:
		u32_vawue = MMAW_PAWAM_AWBMODE_SHADE;
		bweak;
	}

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_awb_gains(stwuct bcm2835_mmaw_dev *dev,
			      stwuct v4w2_ctww *ctww,
			      const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	stwuct vchiq_mmaw_powt *contwow;
	stwuct mmaw_pawametew_awbgains gains;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	if (ctww->id == V4W2_CID_WED_BAWANCE)
		dev->wed_gain = ctww->vaw;
	ewse if (ctww->id == V4W2_CID_BWUE_BAWANCE)
		dev->bwue_gain = ctww->vaw;

	gains.w_gain.numewatow = dev->wed_gain;
	gains.w_gain.denominatow = 1000;
	gains.b_gain.numewatow = dev->bwue_gain;
	gains.b_gain.denominatow = 1000;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					     mmaw_ctww->mmaw_id,
					     &gains, sizeof(gains));
}

static int ctww_set_image_effect(stwuct bcm2835_mmaw_dev *dev,
				 stwuct v4w2_ctww *ctww,
				 const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet = -EINVAW;
	int i, j;
	stwuct vchiq_mmaw_powt *contwow;
	stwuct mmaw_pawametew_imagefx_pawametews imagefx;

	fow (i = 0; i < AWWAY_SIZE(v4w2_to_mmaw_effects_vawues); i++) {
		if (ctww->vaw != v4w2_to_mmaw_effects_vawues[i].v4w2_effect)
			continue;

		imagefx.effect =
			v4w2_to_mmaw_effects_vawues[i].mmaw_effect;
		imagefx.num_effect_pawams =
			v4w2_to_mmaw_effects_vawues[i].num_effect_pawams;

		if (imagefx.num_effect_pawams > MMAW_MAX_IMAGEFX_PAWAMETEWS)
			imagefx.num_effect_pawams = MMAW_MAX_IMAGEFX_PAWAMETEWS;

		fow (j = 0; j < imagefx.num_effect_pawams; j++)
			imagefx.effect_pawametew[j] =
				v4w2_to_mmaw_effects_vawues[i].effect_pawams[j];

		dev->cowouwfx.enabwe =
			v4w2_to_mmaw_effects_vawues[i].cow_fx_enabwe;
		if (!v4w2_to_mmaw_effects_vawues[i].cow_fx_fixed_cbcw) {
			dev->cowouwfx.u = v4w2_to_mmaw_effects_vawues[i].u;
			dev->cowouwfx.v = v4w2_to_mmaw_effects_vawues[i].v;
		}

		contwow = &dev->component[COMP_CAMEWA]->contwow;

		wet = vchiq_mmaw_powt_pawametew_set(
				dev->instance, contwow,
				MMAW_PAWAMETEW_IMAGE_EFFECT_PAWAMETEWS,
				&imagefx, sizeof(imagefx));
		if (wet)
			goto exit;

		wet = vchiq_mmaw_powt_pawametew_set(
				dev->instance, contwow,
				MMAW_PAWAMETEW_COWOUW_EFFECT,
				&dev->cowouwfx, sizeof(dev->cowouwfx));
	}

exit:
	v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
		 "mmaw_ctww:%p ctww id:0x%x ctww vaw:%d imagefx:0x%x cowow_effect:%s u:%d v:%d wet %d(%d)\n",
				mmaw_ctww, ctww->id, ctww->vaw, imagefx.effect,
				dev->cowouwfx.enabwe ? "twue" : "fawse",
				dev->cowouwfx.u, dev->cowouwfx.v,
				wet, (wet == 0 ? 0 : -EINVAW));
	wetuwn (wet == 0 ? 0 : -EINVAW);
}

static int ctww_set_cowfx(stwuct bcm2835_mmaw_dev *dev,
			  stwuct v4w2_ctww *ctww,
			  const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet;
	stwuct vchiq_mmaw_powt *contwow;

	contwow = &dev->component[COMP_CAMEWA]->contwow;

	dev->cowouwfx.u = (ctww->vaw & 0xff00) >> 8;
	dev->cowouwfx.v = ctww->vaw & 0xff;

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
					    MMAW_PAWAMETEW_COWOUW_EFFECT,
					    &dev->cowouwfx,
					    sizeof(dev->cowouwfx));

	v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
		 "%s: Aftew: mmaw_ctww:%p ctww id:0x%x ctww vaw:%d wet %d(%d)\n",
			__func__, mmaw_ctww, ctww->id, ctww->vaw, wet,
			(wet == 0 ? 0 : -EINVAW));
	wetuwn (wet == 0 ? 0 : -EINVAW);
}

static int ctww_set_bitwate(stwuct bcm2835_mmaw_dev *dev,
			    stwuct v4w2_ctww *ctww,
			    const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet;
	stwuct vchiq_mmaw_powt *encodew_out;

	dev->captuwe.encode_bitwate = ctww->vaw;

	encodew_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance, encodew_out,
					    mmaw_ctww->mmaw_id, &ctww->vaw,
					    sizeof(ctww->vaw));

	v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
		 "%s: Aftew: mmaw_ctww:%p ctww id:0x%x ctww vaw:%d wet %d(%d)\n",
		 __func__, mmaw_ctww, ctww->id, ctww->vaw, wet,
		 (wet == 0 ? 0 : -EINVAW));

	/*
	 * Owdew fiwmwawe vewsions (pwe Juwy 2019) have a bug in handwing
	 * MMAW_PAWAMETEW_VIDEO_BIT_WATE that wesuwt in the caww
	 * wetuwning -MMAW_MSG_STATUS_EINVAW. So ignowe ewwows fwom this caww.
	 */
	wetuwn 0;
}

static int ctww_set_bitwate_mode(stwuct bcm2835_mmaw_dev *dev,
				 stwuct v4w2_ctww *ctww,
				 const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 bitwate_mode;
	stwuct vchiq_mmaw_powt *encodew_out;

	encodew_out = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	dev->captuwe.encode_bitwate_mode = ctww->vaw;
	switch (ctww->vaw) {
	defauwt:
	case V4W2_MPEG_VIDEO_BITWATE_MODE_VBW:
		bitwate_mode = MMAW_VIDEO_WATECONTWOW_VAWIABWE;
		bweak;
	case V4W2_MPEG_VIDEO_BITWATE_MODE_CBW:
		bitwate_mode = MMAW_VIDEO_WATECONTWOW_CONSTANT;
		bweak;
	}

	vchiq_mmaw_powt_pawametew_set(dev->instance, encodew_out,
				      mmaw_ctww->mmaw_id,
					     &bitwate_mode,
					     sizeof(bitwate_mode));
	wetuwn 0;
}

static int ctww_set_image_encode_output(stwuct bcm2835_mmaw_dev *dev,
					stwuct v4w2_ctww *ctww,
					const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *jpeg_out;

	jpeg_out = &dev->component[COMP_IMAGE_ENCODE]->output[0];

	u32_vawue = ctww->vaw;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, jpeg_out,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_video_encode_pawam_output(stwuct bcm2835_mmaw_dev *dev,
					      stwuct v4w2_ctww *ctww,
					      const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	u32 u32_vawue;
	stwuct vchiq_mmaw_powt *vid_enc_ctw;

	vid_enc_ctw = &dev->component[COMP_VIDEO_ENCODE]->output[0];

	u32_vawue = ctww->vaw;

	wetuwn vchiq_mmaw_powt_pawametew_set(dev->instance, vid_enc_ctw,
					     mmaw_ctww->mmaw_id,
					     &u32_vawue, sizeof(u32_vawue));
}

static int ctww_set_video_encode_pwofiwe_wevew(stwuct bcm2835_mmaw_dev *dev,
					       stwuct v4w2_ctww *ctww,
					       const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	stwuct mmaw_pawametew_video_pwofiwe pawam;
	int wet = 0;

	if (ctww->id == V4W2_CID_MPEG_VIDEO_H264_PWOFIWE) {
		switch (ctww->vaw) {
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE:
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE:
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN:
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH:
			dev->captuwe.enc_pwofiwe = ctww->vaw;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	} ewse if (ctww->id == V4W2_CID_MPEG_VIDEO_H264_WEVEW) {
		switch (ctww->vaw) {
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
		case V4W2_MPEG_VIDEO_H264_WEVEW_1B:
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
		case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
			dev->captuwe.enc_wevew = ctww->vaw;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
	}

	if (!wet) {
		switch (dev->captuwe.enc_pwofiwe) {
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE:
			pawam.pwofiwe = MMAW_VIDEO_PWOFIWE_H264_BASEWINE;
			bweak;
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE:
			pawam.pwofiwe =
				MMAW_VIDEO_PWOFIWE_H264_CONSTWAINED_BASEWINE;
			bweak;
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN:
			pawam.pwofiwe = MMAW_VIDEO_PWOFIWE_H264_MAIN;
			bweak;
		case V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH:
			pawam.pwofiwe = MMAW_VIDEO_PWOFIWE_H264_HIGH;
			bweak;
		defauwt:
			/* Shouwd nevew get hewe */
			bweak;
		}

		switch (dev->captuwe.enc_wevew) {
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_0:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_1;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_1B:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_1b;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_1:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_11;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_2:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_12;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_1_3:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_13;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_0:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_2;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_1:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_21;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_2_2:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_22;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_0:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_3;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_1:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_31;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_3_2:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_32;
			bweak;
		case V4W2_MPEG_VIDEO_H264_WEVEW_4_0:
			pawam.wevew = MMAW_VIDEO_WEVEW_H264_4;
			bweak;
		defauwt:
			/* Shouwd nevew get hewe */
			bweak;
		}

		wet = vchiq_mmaw_powt_pawametew_set(dev->instance,
						    &dev->component[COMP_VIDEO_ENCODE]->output[0],
			mmaw_ctww->mmaw_id,
			&pawam, sizeof(pawam));
	}
	wetuwn wet;
}

static int ctww_set_scene_mode(stwuct bcm2835_mmaw_dev *dev,
			       stwuct v4w2_ctww *ctww,
			       const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww)
{
	int wet = 0;
	int shuttew_speed;
	stwuct vchiq_mmaw_powt *contwow;

	v4w2_dbg(0, bcm2835_v4w2_debug, &dev->v4w2_dev,
		 "scene mode sewected %d, was %d\n", ctww->vaw,
		 dev->scene_mode);
	contwow = &dev->component[COMP_CAMEWA]->contwow;

	if (ctww->vaw == dev->scene_mode)
		wetuwn 0;

	if (ctww->vaw == V4W2_SCENE_MODE_NONE) {
		/* Westowe aww usew sewections */
		dev->scene_mode = V4W2_SCENE_MODE_NONE;

		if (dev->exposuwe_mode_usew == MMAW_PAWAM_EXPOSUWEMODE_OFF)
			shuttew_speed = dev->manuaw_shuttew_speed;
		ewse
			shuttew_speed = 0;

		v4w2_dbg(0, bcm2835_v4w2_debug, &dev->v4w2_dev,
			 "%s: scene mode none: shut_speed %d, exp_mode %d, metewing %d\n",
			 __func__, shuttew_speed, dev->exposuwe_mode_usew,
			 dev->metewing_mode);
		wet = vchiq_mmaw_powt_pawametew_set(dev->instance,
						    contwow,
						    MMAW_PAWAMETEW_SHUTTEW_SPEED,
						    &shuttew_speed,
						    sizeof(shuttew_speed));
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance,
						     contwow,
						     MMAW_PAWAMETEW_EXPOSUWE_MODE,
						     &dev->exposuwe_mode_usew,
						     sizeof(u32));
		dev->exposuwe_mode_active = dev->exposuwe_mode_usew;
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance,
						     contwow,
						     MMAW_PAWAMETEW_EXP_METEWING_MODE,
						     &dev->metewing_mode,
						     sizeof(u32));
		wet += set_fwamewate_pawams(dev);
	} ewse {
		/* Set up scene mode */
		int i;
		const stwuct v4w2_mmaw_scene_config *scene = NUWW;
		int shuttew_speed;
		enum mmaw_pawametew_exposuwemode exposuwe_mode;
		enum mmaw_pawametew_exposuwemetewingmode metewing_mode;

		fow (i = 0; i < AWWAY_SIZE(scene_configs); i++) {
			if (scene_configs[i].v4w2_scene == ctww->vaw) {
				scene = &scene_configs[i];
				bweak;
			}
		}
		if (!scene)
			wetuwn -EINVAW;
		if (i >= AWWAY_SIZE(scene_configs))
			wetuwn -EINVAW;

		/* Set aww the vawues */
		dev->scene_mode = ctww->vaw;

		if (scene->exposuwe_mode == MMAW_PAWAM_EXPOSUWEMODE_OFF)
			shuttew_speed = dev->manuaw_shuttew_speed;
		ewse
			shuttew_speed = 0;
		exposuwe_mode = scene->exposuwe_mode;
		metewing_mode = scene->metewing_mode;

		v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
			 "%s: scene mode none: shut_speed %d, exp_mode %d, metewing %d\n",
			 __func__, shuttew_speed, exposuwe_mode, metewing_mode);

		wet = vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
						    MMAW_PAWAMETEW_SHUTTEW_SPEED,
						    &shuttew_speed,
						    sizeof(shuttew_speed));
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
						     MMAW_PAWAMETEW_EXPOSUWE_MODE,
						     &exposuwe_mode,
						     sizeof(u32));
		dev->exposuwe_mode_active = exposuwe_mode;
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
						     MMAW_PAWAMETEW_EXPOSUWE_MODE,
						     &exposuwe_mode,
						     sizeof(u32));
		wet += vchiq_mmaw_powt_pawametew_set(dev->instance, contwow,
						     MMAW_PAWAMETEW_EXP_METEWING_MODE,
						     &metewing_mode,
						     sizeof(u32));
		wet += set_fwamewate_pawams(dev);
	}
	if (wet) {
		v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
			 "%s: Setting scene to %d, wet=%d\n",
			 __func__, ctww->vaw, wet);
		wet = -EINVAW;
	}
	wetuwn 0;
}

static int bcm2835_mmaw_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct bcm2835_mmaw_dev *dev = containew_of(ctww->handwew, stwuct bcm2835_mmaw_dev,
						    ctww_handwew);
	const stwuct bcm2835_mmaw_v4w2_ctww *mmaw_ctww = ctww->pwiv;
	int wet;

	if (!mmaw_ctww || mmaw_ctww->id != ctww->id || !mmaw_ctww->settew) {
		pw_wawn("mmaw_ctww:%p ctww id:%d\n", mmaw_ctww, ctww->id);
		wetuwn -EINVAW;
	}

	wet = mmaw_ctww->settew(dev, ctww, mmaw_ctww);
	if (wet)
		pw_wawn("ctww id:%d/MMAW pawam %08X- wetuwned wet %d\n",
			ctww->id, mmaw_ctww->mmaw_id, wet);
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops bcm2835_mmaw_ctww_ops = {
	.s_ctww = bcm2835_mmaw_s_ctww,
};

static const stwuct bcm2835_mmaw_v4w2_ctww v4w2_ctwws[V4W2_CTWW_COUNT] = {
	{
		.id = V4W2_CID_SATUWATION,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_SATUWATION,
		.settew = ctww_set_wationaw,
	},
	{
		.id = V4W2_CID_SHAWPNESS,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_SHAWPNESS,
		.settew = ctww_set_wationaw,
	},
	{
		.id = V4W2_CID_CONTWAST,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = -100,
		.max = 100,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_CONTWAST,
		.settew = ctww_set_wationaw,
	},
	{
		.id = V4W2_CID_BWIGHTNESS,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 100,
		.def = 50,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_BWIGHTNESS,
		.settew = ctww_set_wationaw,
	},
	{
		.id = V4W2_CID_ISO_SENSITIVITY,
		.type = MMAW_CONTWOW_TYPE_INT_MENU,
		.min = 0,
		.max = AWWAY_SIZE(iso_qmenu) - 1,
		.def = 0,
		.step = 1,
		.imenu = iso_qmenu,
		.mmaw_id = MMAW_PAWAMETEW_ISO,
		.settew = ctww_set_iso,
	},
	{
		.id = V4W2_CID_ISO_SENSITIVITY_AUTO,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = 0,
		.max = V4W2_ISO_SENSITIVITY_AUTO,
		.def = V4W2_ISO_SENSITIVITY_AUTO,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_ISO,
		.settew = ctww_set_iso,
	},
	{
		.id = V4W2_CID_IMAGE_STABIWIZATION,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_VIDEO_STABIWISATION,
		.settew = ctww_set_vawue,
	},
	{
		.id = V4W2_CID_EXPOSUWE_AUTO,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = ~0x03,
		.max = V4W2_EXPOSUWE_APEWTUWE_PWIOWITY,
		.def = V4W2_EXPOSUWE_AUTO,
		.step = 0,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_EXPOSUWE_MODE,
		.settew = ctww_set_exposuwe,
	},
	{
		.id = V4W2_CID_EXPOSUWE_ABSOWUTE,
		.type = MMAW_CONTWOW_TYPE_STD,
		/* Units of 100usecs */
		.min = 1,
		.max = 1 * 1000 * 10,
		.def = 100 * 10,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_SHUTTEW_SPEED,
		.settew = ctww_set_exposuwe,
	},
	{
		.id = V4W2_CID_AUTO_EXPOSUWE_BIAS,
		.type = MMAW_CONTWOW_TYPE_INT_MENU,
		.min = 0,
		.max = AWWAY_SIZE(ev_bias_qmenu) - 1,
		.def = (AWWAY_SIZE(ev_bias_qmenu) + 1) / 2 - 1,
		.step = 0,
		.imenu = ev_bias_qmenu,
		.mmaw_id = MMAW_PAWAMETEW_EXPOSUWE_COMP,
		.settew = ctww_set_vawue_ev,
	},
	{
		.id = V4W2_CID_EXPOSUWE_AUTO_PWIOWITY,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		/* Dummy MMAW ID as it gets mapped into FPS wange */
		.mmaw_id = 0,
		.settew = ctww_set_exposuwe,
	},
	{
		.id = V4W2_CID_EXPOSUWE_METEWING,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = ~0xf,
		.max = V4W2_EXPOSUWE_METEWING_MATWIX,
		.def = V4W2_EXPOSUWE_METEWING_AVEWAGE,
		.step = 0,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_EXP_METEWING_MODE,
		.settew = ctww_set_metewing_mode,
	},
	{
		.id = V4W2_CID_AUTO_N_PWESET_WHITE_BAWANCE,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = ~0x3ff,
		.max = V4W2_WHITE_BAWANCE_SHADE,
		.def = V4W2_WHITE_BAWANCE_AUTO,
		.step = 0,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_AWB_MODE,
		.settew = ctww_set_awb_mode,
	},
	{
		.id = V4W2_CID_WED_BAWANCE,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 1,
		.max = 7999,
		.def = 1000,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_CUSTOM_AWB_GAINS,
		.settew = ctww_set_awb_gains,
	},
	{
		.id = V4W2_CID_BWUE_BAWANCE,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 1,
		.max = 7999,
		.def = 1000,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_CUSTOM_AWB_GAINS,
		.settew = ctww_set_awb_gains,
	},
	{
		.id = V4W2_CID_COWOWFX,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = 0,
		.max = V4W2_COWOWFX_SET_CBCW,
		.def = V4W2_COWOWFX_NONE,
		.step = 0,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_IMAGE_EFFECT,
		.settew = ctww_set_image_effect,
	},
	{
		.id = V4W2_CID_COWOWFX_CBCW,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 0xffff,
		.def = 0x8080,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_COWOUW_EFFECT,
		.settew = ctww_set_cowfx,
	},
	{
		.id = V4W2_CID_WOTATE,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 360,
		.def = 0,
		.step = 90,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_WOTATION,
		.settew = ctww_set_wotate,
	},
	{
		.id = V4W2_CID_HFWIP,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_MIWWOW,
		.settew = ctww_set_fwip,
	},
	{
		.id = V4W2_CID_VFWIP,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_MIWWOW,
		.settew = ctww_set_fwip,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = 0,
		.max = V4W2_MPEG_VIDEO_BITWATE_MODE_CBW,
		.def = 0,
		.step = 0,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_WATECONTWOW,
		.settew = ctww_set_bitwate_mode,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_BITWATE,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 25 * 1000,
		.max = 25 * 1000 * 1000,
		.def = 10 * 1000 * 1000,
		.step = 25 * 1000,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_VIDEO_BIT_WATE,
		.settew = ctww_set_bitwate,
	},
	{
		.id = V4W2_CID_JPEG_COMPWESSION_QUAWITY,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 1,
		.max = 100,
		.def = 30,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_JPEG_Q_FACTOW,
		.settew = ctww_set_image_encode_output,
	},
	{
		.id = V4W2_CID_POWEW_WINE_FWEQUENCY,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = 0,
		.max = V4W2_CID_POWEW_WINE_FWEQUENCY_AUTO,
		.def = 1,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_FWICKEW_AVOID,
		.settew = ctww_set_fwickew_avoidance,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_WEPEAT_SEQ_HEADEW,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 1,
		.def = 0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_VIDEO_ENCODE_INWINE_HEADEW,
		.settew = ctww_set_video_encode_pawam_output,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = ~(BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
			 BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE) |
			 BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
			 BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH)),
		.max = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
		.def = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_PWOFIWE,
		.settew = ctww_set_video_encode_pwofiwe_wevew,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_H264_WEVEW,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		.min = ~(BIT(V4W2_MPEG_VIDEO_H264_WEVEW_1_0) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_1B) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_1_1) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_1_2) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_1_3) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_2_0) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_2_1) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_2_2) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_3_0) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_3_1) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_3_2) |
			 BIT(V4W2_MPEG_VIDEO_H264_WEVEW_4_0)),
		.max = V4W2_MPEG_VIDEO_H264_WEVEW_4_0,
		.def = V4W2_MPEG_VIDEO_H264_WEVEW_4_0,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_PWOFIWE,
		.settew = ctww_set_video_encode_pwofiwe_wevew,
	},
	{
		.id = V4W2_CID_SCENE_MODE,
		.type = MMAW_CONTWOW_TYPE_STD_MENU,
		/* mask is computed at wuntime */
		.min = -1,
		.max = V4W2_SCENE_MODE_TEXT,
		.def = V4W2_SCENE_MODE_NONE,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_PWOFIWE,
		.settew = ctww_set_scene_mode,
	},
	{
		.id = V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD,
		.type = MMAW_CONTWOW_TYPE_STD,
		.min = 0,
		.max = 0x7FFFFFFF,
		.def = 60,
		.step = 1,
		.imenu = NUWW,
		.mmaw_id = MMAW_PAWAMETEW_INTWAPEWIOD,
		.settew = ctww_set_video_encode_pawam_output,
	},
};

int bcm2835_mmaw_set_aww_camewa_contwows(stwuct bcm2835_mmaw_dev *dev)
{
	int c;
	int wet = 0;

	fow (c = 0; c < V4W2_CTWW_COUNT; c++) {
		if ((dev->ctwws[c]) && (v4w2_ctwws[c].settew)) {
			wet = v4w2_ctwws[c].settew(dev, dev->ctwws[c],
						   &v4w2_ctwws[c]);
			if (wet) {
				v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
					 "Faiwed when setting defauwt vawues fow ctww %d\n",
					 c);
				bweak;
			}
		}
	}
	wetuwn wet;
}

int set_fwamewate_pawams(stwuct bcm2835_mmaw_dev *dev)
{
	stwuct mmaw_pawametew_fps_wange fps_wange;
	int wet;

	fps_wange.fps_high.numewatow = dev->captuwe.timepewfwame.denominatow;
	fps_wange.fps_high.denominatow = dev->captuwe.timepewfwame.numewatow;

	if ((dev->exposuwe_mode_active != MMAW_PAWAM_EXPOSUWEMODE_OFF) &&
	    (dev->exp_auto_pwiowity)) {
		/* Vawiabwe FPS. Define min FPS as 1fps. */
		fps_wange.fps_wow.numewatow = 1;
		fps_wange.fps_wow.denominatow = 1;
	} ewse {
		/* Fixed FPS - set min and max to be the same */
		fps_wange.fps_wow.numewatow = fps_wange.fps_high.numewatow;
		fps_wange.fps_wow.denominatow = fps_wange.fps_high.denominatow;
	}

	v4w2_dbg(1, bcm2835_v4w2_debug, &dev->v4w2_dev,
		 "Set fps wange to %d/%d to %d/%d\n",
		 fps_wange.fps_wow.numewatow,
		 fps_wange.fps_wow.denominatow,
		 fps_wange.fps_high.numewatow,
		 fps_wange.fps_high.denominatow);

	wet = vchiq_mmaw_powt_pawametew_set(dev->instance,
					    &dev->component[COMP_CAMEWA]->output[CAM_POWT_PWEVIEW],
					    MMAW_PAWAMETEW_FPS_WANGE,
					    &fps_wange, sizeof(fps_wange));
	wet += vchiq_mmaw_powt_pawametew_set(dev->instance,
					     &dev->component[COMP_CAMEWA]->output[CAM_POWT_VIDEO],
					     MMAW_PAWAMETEW_FPS_WANGE,
					     &fps_wange, sizeof(fps_wange));
	wet += vchiq_mmaw_powt_pawametew_set(dev->instance,
					     &dev->component[COMP_CAMEWA]->output[CAM_POWT_CAPTUWE],
					     MMAW_PAWAMETEW_FPS_WANGE,
					     &fps_wange, sizeof(fps_wange));
	if (wet)
		v4w2_dbg(0, bcm2835_v4w2_debug, &dev->v4w2_dev,
			 "Faiwed to set fps wet %d\n", wet);

	wetuwn wet;
}

int bcm2835_mmaw_init_contwows(stwuct bcm2835_mmaw_dev *dev, stwuct v4w2_ctww_handwew *hdw)
{
	int c;
	const stwuct bcm2835_mmaw_v4w2_ctww *ctww;

	v4w2_ctww_handwew_init(hdw, V4W2_CTWW_COUNT);

	fow (c = 0; c < V4W2_CTWW_COUNT; c++) {
		ctww = &v4w2_ctwws[c];

		switch (ctww->type) {
		case MMAW_CONTWOW_TYPE_STD:
			dev->ctwws[c] = v4w2_ctww_new_std(hdw, &bcm2835_mmaw_ctww_ops,
							  ctww->id, ctww->min, ctww->max,
							  ctww->step, ctww->def);
			bweak;

		case MMAW_CONTWOW_TYPE_STD_MENU:
		{
			u64 mask = ctww->min;

			if (ctww->id == V4W2_CID_SCENE_MODE) {
				/* Speciaw handwing to wowk out the mask
				 * vawue based on the scene_configs awway
				 * at wuntime. Weduces the chance of
				 * mismatches.
				 */
				int i;

				mask = BIT(V4W2_SCENE_MODE_NONE);
				fow (i = 0;
				     i < AWWAY_SIZE(scene_configs);
				     i++) {
					mask |= BIT(scene_configs[i].v4w2_scene);
				}
				mask = ~mask;
			}

			dev->ctwws[c] = v4w2_ctww_new_std_menu(hdw, &bcm2835_mmaw_ctww_ops,
							       ctww->id, ctww->max, mask,
							       ctww->def);
			bweak;
		}

		case MMAW_CONTWOW_TYPE_INT_MENU:
			dev->ctwws[c] = v4w2_ctww_new_int_menu(hdw, &bcm2835_mmaw_ctww_ops,
							       ctww->id, ctww->max,
							       ctww->def, ctww->imenu);
			bweak;

		case MMAW_CONTWOW_TYPE_CWUSTEW:
			/* skip this entwy when constwucting contwows */
			continue;
		}

		if (hdw->ewwow)
			bweak;

		dev->ctwws[c]->pwiv = (void *)ctww;
	}

	if (hdw->ewwow) {
		pw_eww("ewwow adding contwow %d/%d id 0x%x\n", c,
		       V4W2_CTWW_COUNT, ctww->id);
		wetuwn hdw->ewwow;
	}

	fow (c = 0; c < V4W2_CTWW_COUNT; c++) {
		ctww = &v4w2_ctwws[c];

		switch (ctww->type) {
		case MMAW_CONTWOW_TYPE_CWUSTEW:
			v4w2_ctww_auto_cwustew(ctww->min,
					       &dev->ctwws[c + 1],
					       ctww->max,
					       ctww->def);
			bweak;

		case MMAW_CONTWOW_TYPE_STD:
		case MMAW_CONTWOW_TYPE_STD_MENU:
		case MMAW_CONTWOW_TYPE_INT_MENU:
			bweak;
		}
	}

	wetuwn 0;
}
