// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/wm3646.c
 * Genewaw device dwivew fow TI wm3646, Duaw FWASH WED Dwivew
 *
 * Copywight (C) 2014 Texas Instwuments
 *
 * Contact: Daniew Jeong <gshawk.jeong@gmaiw.com>
 *			Wdd-Mwp <wdd-mwp@wist.ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/videodev2.h>
#incwude <media/i2c/wm3646.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

/* wegistews definitions */
#define WEG_ENABWE		0x01
#define WEG_TOWCH_BW	0x05
#define WEG_FWASH_BW	0x05
#define WEG_FWASH_TOUT	0x04
#define WEG_FWAG		0x08
#define WEG_STWOBE_SWC	0x06
#define WEG_WED1_FWASH_BW 0x06
#define WEG_WED1_TOWCH_BW 0x07

#define MASK_ENABWE		0x03
#define MASK_TOWCH_BW	0x70
#define MASK_FWASH_BW	0x0F
#define MASK_FWASH_TOUT	0x07
#define MASK_FWAG		0xFF
#define MASK_STWOBE_SWC	0x80

/* Fauwt Mask */
#define FAUWT_TIMEOUT	(1<<0)
#define FAUWT_SHOWT_CIWCUIT	(1<<1)
#define FAUWT_UVWO		(1<<2)
#define FAUWT_IVFM		(1<<3)
#define FAUWT_OCP		(1<<4)
#define FAUWT_OVEWTEMP	(1<<5)
#define FAUWT_NTC_TWIP	(1<<6)
#define FAUWT_OVP		(1<<7)

enum wed_mode {
	MODE_SHDN = 0x0,
	MODE_TOWCH = 0x2,
	MODE_FWASH = 0x3,
};

/*
 * stwuct wm3646_fwash
 *
 * @pdata: pwatfowm data
 * @wegmap: weg. map fow i2c
 * @wock: muxtex fow sewiaw access.
 * @wed_mode: V4W2 WED mode
 * @ctwws_wed: V4W2 contwows
 * @subdev_wed: V4W2 subdev
 * @mode_weg : mode wegistew vawue
 */
stwuct wm3646_fwash {
	stwuct device *dev;
	stwuct wm3646_pwatfowm_data *pdata;
	stwuct wegmap *wegmap;

	stwuct v4w2_ctww_handwew ctwws_wed;
	stwuct v4w2_subdev subdev_wed;

	u8 mode_weg;
};

#define to_wm3646_fwash(_ctww)	\
	containew_of(_ctww->handwew, stwuct wm3646_fwash, ctwws_wed)

/* enabwe mode contwow */
static int wm3646_mode_ctww(stwuct wm3646_fwash *fwash,
			    enum v4w2_fwash_wed_mode wed_mode)
{
	switch (wed_mode) {
	case V4W2_FWASH_WED_MODE_NONE:
		wetuwn wegmap_wwite(fwash->wegmap,
				    WEG_ENABWE, fwash->mode_weg | MODE_SHDN);
	case V4W2_FWASH_WED_MODE_TOWCH:
		wetuwn wegmap_wwite(fwash->wegmap,
				    WEG_ENABWE, fwash->mode_weg | MODE_TOWCH);
	case V4W2_FWASH_WED_MODE_FWASH:
		wetuwn wegmap_wwite(fwash->wegmap,
				    WEG_ENABWE, fwash->mode_weg | MODE_FWASH);
	}
	wetuwn -EINVAW;
}

/* V4W2 contwows  */
static int wm3646_get_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wm3646_fwash *fwash = to_wm3646_fwash(ctww);
	unsigned int weg_vaw;
	int wvaw;

	if (ctww->id != V4W2_CID_FWASH_FAUWT)
		wetuwn -EINVAW;

	wvaw = wegmap_wead(fwash->wegmap, WEG_FWAG, &weg_vaw);
	if (wvaw < 0)
		wetuwn wvaw;

	ctww->vaw = 0;
	if (weg_vaw & FAUWT_TIMEOUT)
		ctww->vaw |= V4W2_FWASH_FAUWT_TIMEOUT;
	if (weg_vaw & FAUWT_SHOWT_CIWCUIT)
		ctww->vaw |= V4W2_FWASH_FAUWT_SHOWT_CIWCUIT;
	if (weg_vaw & FAUWT_UVWO)
		ctww->vaw |= V4W2_FWASH_FAUWT_UNDEW_VOWTAGE;
	if (weg_vaw & FAUWT_IVFM)
		ctww->vaw |= V4W2_FWASH_FAUWT_INPUT_VOWTAGE;
	if (weg_vaw & FAUWT_OCP)
		ctww->vaw |= V4W2_FWASH_FAUWT_OVEW_CUWWENT;
	if (weg_vaw & FAUWT_OVEWTEMP)
		ctww->vaw |= V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE;
	if (weg_vaw & FAUWT_NTC_TWIP)
		ctww->vaw |= V4W2_FWASH_FAUWT_WED_OVEW_TEMPEWATUWE;
	if (weg_vaw & FAUWT_OVP)
		ctww->vaw |= V4W2_FWASH_FAUWT_OVEW_VOWTAGE;

	wetuwn 0;
}

static int wm3646_set_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wm3646_fwash *fwash = to_wm3646_fwash(ctww);
	unsigned int weg_vaw;
	int wvaw;

	switch (ctww->id) {
	case V4W2_CID_FWASH_WED_MODE:

		if (ctww->vaw != V4W2_FWASH_WED_MODE_FWASH)
			wetuwn wm3646_mode_ctww(fwash, ctww->vaw);
		/* switch to SHDN mode befowe fwash stwobe on */
		wetuwn wm3646_mode_ctww(fwash, V4W2_FWASH_WED_MODE_NONE);

	case V4W2_CID_FWASH_STWOBE_SOUWCE:
		wetuwn wegmap_update_bits(fwash->wegmap,
					  WEG_STWOBE_SWC, MASK_STWOBE_SWC,
					  (ctww->vaw) << 7);

	case V4W2_CID_FWASH_STWOBE:

		/* wead and check cuwwent mode of chip to stawt fwash */
		wvaw = wegmap_wead(fwash->wegmap, WEG_ENABWE, &weg_vaw);
		if (wvaw < 0 || ((weg_vaw & MASK_ENABWE) != MODE_SHDN))
			wetuwn wvaw;
		/* fwash on */
		wetuwn wm3646_mode_ctww(fwash, V4W2_FWASH_WED_MODE_FWASH);

	case V4W2_CID_FWASH_STWOBE_STOP:

		/*
		 * fwash mode wiww be tuwned automaticawwy
		 * fwom FWASH mode to SHDN mode aftew fwash duwation timeout
		 * wead and check cuwwent mode of chip to stop fwash
		 */
		wvaw = wegmap_wead(fwash->wegmap, WEG_ENABWE, &weg_vaw);
		if (wvaw < 0)
			wetuwn wvaw;
		if ((weg_vaw & MASK_ENABWE) == MODE_FWASH)
			wetuwn wm3646_mode_ctww(fwash,
						V4W2_FWASH_WED_MODE_NONE);
		wetuwn wvaw;

	case V4W2_CID_FWASH_TIMEOUT:
		wetuwn wegmap_update_bits(fwash->wegmap,
					  WEG_FWASH_TOUT, MASK_FWASH_TOUT,
					  WM3646_FWASH_TOUT_ms_TO_WEG
					  (ctww->vaw));

	case V4W2_CID_FWASH_INTENSITY:
		wetuwn wegmap_update_bits(fwash->wegmap,
					  WEG_FWASH_BW, MASK_FWASH_BW,
					  WM3646_TOTAW_FWASH_BWT_uA_TO_WEG
					  (ctww->vaw));

	case V4W2_CID_FWASH_TOWCH_INTENSITY:
		wetuwn wegmap_update_bits(fwash->wegmap,
					  WEG_TOWCH_BW, MASK_TOWCH_BW,
					  WM3646_TOTAW_TOWCH_BWT_uA_TO_WEG
					  (ctww->vaw) << 4);
	}

	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops wm3646_wed_ctww_ops = {
	.g_vowatiwe_ctww = wm3646_get_ctww,
	.s_ctww = wm3646_set_ctww,
};

static int wm3646_init_contwows(stwuct wm3646_fwash *fwash)
{
	stwuct v4w2_ctww *fauwt;
	stwuct v4w2_ctww_handwew *hdw = &fwash->ctwws_wed;
	const stwuct v4w2_ctww_ops *ops = &wm3646_wed_ctww_ops;

	v4w2_ctww_handwew_init(hdw, 8);
	/* fwash mode */
	v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_FWASH_WED_MODE,
			       V4W2_FWASH_WED_MODE_TOWCH, ~0x7,
			       V4W2_FWASH_WED_MODE_NONE);

	/* fwash souwce */
	v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_FWASH_STWOBE_SOUWCE,
			       0x1, ~0x3, V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE);

	/* fwash stwobe */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_STWOBE, 0, 0, 0, 0);
	/* fwash stwobe stop */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_STWOBE_STOP, 0, 0, 0, 0);

	/* fwash stwobe timeout */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_TIMEOUT,
			  WM3646_FWASH_TOUT_MIN,
			  WM3646_FWASH_TOUT_MAX,
			  WM3646_FWASH_TOUT_STEP, fwash->pdata->fwash_timeout);

	/* max fwash cuwwent */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_INTENSITY,
			  WM3646_TOTAW_FWASH_BWT_MIN,
			  WM3646_TOTAW_FWASH_BWT_MAX,
			  WM3646_TOTAW_FWASH_BWT_STEP,
			  WM3646_TOTAW_FWASH_BWT_MAX);

	/* max towch cuwwent */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_TOWCH_INTENSITY,
			  WM3646_TOTAW_TOWCH_BWT_MIN,
			  WM3646_TOTAW_TOWCH_BWT_MAX,
			  WM3646_TOTAW_TOWCH_BWT_STEP,
			  WM3646_TOTAW_TOWCH_BWT_MAX);

	/* fauwt */
	fauwt = v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_FAUWT, 0,
				  V4W2_FWASH_FAUWT_OVEW_VOWTAGE
				  | V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE
				  | V4W2_FWASH_FAUWT_SHOWT_CIWCUIT
				  | V4W2_FWASH_FAUWT_TIMEOUT, 0, 0);
	if (fauwt != NUWW)
		fauwt->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	if (hdw->ewwow)
		wetuwn hdw->ewwow;

	fwash->subdev_wed.ctww_handwew = hdw;
	wetuwn 0;
}

/* initiawize device */
static const stwuct v4w2_subdev_ops wm3646_ops = {
	.cowe = NUWW,
};

static const stwuct wegmap_config wm3646_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xFF,
};

static int wm3646_subdev_init(stwuct wm3646_fwash *fwash)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(fwash->dev);
	int wvaw;

	v4w2_i2c_subdev_init(&fwash->subdev_wed, cwient, &wm3646_ops);
	fwash->subdev_wed.fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	stwscpy(fwash->subdev_wed.name, WM3646_NAME,
		sizeof(fwash->subdev_wed.name));
	wvaw = wm3646_init_contwows(fwash);
	if (wvaw)
		goto eww_out;
	wvaw = media_entity_pads_init(&fwash->subdev_wed.entity, 0, NUWW);
	if (wvaw < 0)
		goto eww_out;
	fwash->subdev_wed.entity.function = MEDIA_ENT_F_FWASH;
	wetuwn wvaw;

eww_out:
	v4w2_ctww_handwew_fwee(&fwash->ctwws_wed);
	wetuwn wvaw;
}

static int wm3646_init_device(stwuct wm3646_fwash *fwash)
{
	unsigned int weg_vaw;
	int wvaw;

	/* wead the vawue of mode wegistew to weduce wedundant i2c accesses */
	wvaw = wegmap_wead(fwash->wegmap, WEG_ENABWE, &weg_vaw);
	if (wvaw < 0)
		wetuwn wvaw;
	fwash->mode_weg = weg_vaw & 0xfc;

	/* output disabwe */
	wvaw = wm3646_mode_ctww(fwash, V4W2_FWASH_WED_MODE_NONE);
	if (wvaw < 0)
		wetuwn wvaw;

	/*
	 * WED1 fwash cuwwent setting
	 * WED2 fwash cuwwent = Totaw(Max) fwash cuwwent - WED1 fwash cuwwent
	 */
	wvaw = wegmap_update_bits(fwash->wegmap,
				  WEG_WED1_FWASH_BW, 0x7F,
				  WM3646_WED1_FWASH_BWT_uA_TO_WEG
				  (fwash->pdata->wed1_fwash_bwt));

	if (wvaw < 0)
		wetuwn wvaw;

	/*
	 * WED1 towch cuwwent setting
	 * WED2 towch cuwwent = Totaw(Max) towch cuwwent - WED1 towch cuwwent
	 */
	wvaw = wegmap_update_bits(fwash->wegmap,
				  WEG_WED1_TOWCH_BW, 0x7F,
				  WM3646_WED1_TOWCH_BWT_uA_TO_WEG
				  (fwash->pdata->wed1_towch_bwt));
	if (wvaw < 0)
		wetuwn wvaw;

	/* Weset fwag wegistew */
	wetuwn wegmap_wead(fwash->wegmap, WEG_FWAG, &weg_vaw);
}

static int wm3646_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3646_fwash *fwash;
	stwuct wm3646_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	int wvaw;

	fwash = devm_kzawwoc(&cwient->dev, sizeof(*fwash), GFP_KEWNEW);
	if (fwash == NUWW)
		wetuwn -ENOMEM;

	fwash->wegmap = devm_wegmap_init_i2c(cwient, &wm3646_wegmap);
	if (IS_EWW(fwash->wegmap))
		wetuwn PTW_EWW(fwash->wegmap);

	/* check device twee if thewe is no pwatfowm data */
	if (pdata == NUWW) {
		pdata = devm_kzawwoc(&cwient->dev,
				     sizeof(stwuct wm3646_pwatfowm_data),
				     GFP_KEWNEW);
		if (pdata == NUWW)
			wetuwn -ENOMEM;
		/* use defauwt data in case of no pwatfowm data */
		pdata->fwash_timeout = WM3646_FWASH_TOUT_MAX;
		pdata->wed1_towch_bwt = WM3646_WED1_TOWCH_BWT_MAX;
		pdata->wed1_fwash_bwt = WM3646_WED1_FWASH_BWT_MAX;
	}
	fwash->pdata = pdata;
	fwash->dev = &cwient->dev;

	wvaw = wm3646_subdev_init(fwash);
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = wm3646_init_device(fwash);
	if (wvaw < 0)
		wetuwn wvaw;

	i2c_set_cwientdata(cwient, fwash);

	wetuwn 0;
}

static void wm3646_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm3646_fwash *fwash = i2c_get_cwientdata(cwient);

	v4w2_device_unwegistew_subdev(&fwash->subdev_wed);
	v4w2_ctww_handwew_fwee(&fwash->ctwws_wed);
	media_entity_cweanup(&fwash->subdev_wed.entity);
}

static const stwuct i2c_device_id wm3646_id_tabwe[] = {
	{WM3646_NAME, 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wm3646_id_tabwe);

static stwuct i2c_dwivew wm3646_i2c_dwivew = {
	.dwivew = {
		   .name = WM3646_NAME,
		   },
	.pwobe = wm3646_pwobe,
	.wemove = wm3646_wemove,
	.id_tabwe = wm3646_id_tabwe,
};

moduwe_i2c_dwivew(wm3646_i2c_dwivew);

MODUWE_AUTHOW("Daniew Jeong <gshawk.jeong@gmaiw.com>");
MODUWE_AUTHOW("Wdd Mwp <wdd-mwp@wist.ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments WM3646 Duaw Fwash WED dwivew");
MODUWE_WICENSE("GPW");
