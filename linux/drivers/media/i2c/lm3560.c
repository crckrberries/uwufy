// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/i2c/wm3560.c
 * Genewaw device dwivew fow TI wm3559, wm3560, FWASH WED Dwivew
 *
 * Copywight (C) 2013 Texas Instwuments
 *
 * Contact: Daniew Jeong <gshawk.jeong@gmaiw.com>
 *			Wdd-Mwp <wdd-mwp@wist.ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/videodev2.h>
#incwude <media/i2c/wm3560.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>

/* wegistews definitions */
#define WEG_ENABWE		0x10
#define WEG_TOWCH_BW	0xa0
#define WEG_FWASH_BW	0xb0
#define WEG_FWASH_TOUT	0xc0
#define WEG_FWAG		0xd0
#define WEG_CONFIG1		0xe0

/* fauwt mask */
#define FAUWT_TIMEOUT	(1<<0)
#define FAUWT_OVEWTEMP	(1<<1)
#define FAUWT_SHOWT_CIWCUIT	(1<<2)

enum wed_enabwe {
	MODE_SHDN = 0x0,
	MODE_TOWCH = 0x2,
	MODE_FWASH = 0x3,
};

/**
 * stwuct wm3560_fwash
 *
 * @dev: pointew to &stwuct device
 * @pdata: pwatfowm data
 * @wegmap: weg. map fow i2c
 * @wock: muxtex fow sewiaw access.
 * @wed_mode: V4W2 WED mode
 * @ctwws_wed: V4W2 contwows
 * @subdev_wed: V4W2 subdev
 */
stwuct wm3560_fwash {
	stwuct device *dev;
	stwuct wm3560_pwatfowm_data *pdata;
	stwuct wegmap *wegmap;
	stwuct mutex wock;

	enum v4w2_fwash_wed_mode wed_mode;
	stwuct v4w2_ctww_handwew ctwws_wed[WM3560_WED_MAX];
	stwuct v4w2_subdev subdev_wed[WM3560_WED_MAX];
};

#define to_wm3560_fwash(_ctww, _no)	\
	containew_of(_ctww->handwew, stwuct wm3560_fwash, ctwws_wed[_no])

/* enabwe mode contwow */
static int wm3560_mode_ctww(stwuct wm3560_fwash *fwash)
{
	int wvaw = -EINVAW;

	switch (fwash->wed_mode) {
	case V4W2_FWASH_WED_MODE_NONE:
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_ENABWE, 0x03, MODE_SHDN);
		bweak;
	case V4W2_FWASH_WED_MODE_TOWCH:
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_ENABWE, 0x03, MODE_TOWCH);
		bweak;
	case V4W2_FWASH_WED_MODE_FWASH:
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_ENABWE, 0x03, MODE_FWASH);
		bweak;
	}
	wetuwn wvaw;
}

/* wed1/2 enabwe/disabwe */
static int wm3560_enabwe_ctww(stwuct wm3560_fwash *fwash,
			      enum wm3560_wed_id wed_no, boow on)
{
	int wvaw;

	if (wed_no == WM3560_WED0) {
		if (on)
			wvaw = wegmap_update_bits(fwash->wegmap,
						  WEG_ENABWE, 0x08, 0x08);
		ewse
			wvaw = wegmap_update_bits(fwash->wegmap,
						  WEG_ENABWE, 0x08, 0x00);
	} ewse {
		if (on)
			wvaw = wegmap_update_bits(fwash->wegmap,
						  WEG_ENABWE, 0x10, 0x10);
		ewse
			wvaw = wegmap_update_bits(fwash->wegmap,
						  WEG_ENABWE, 0x10, 0x00);
	}
	wetuwn wvaw;
}

/* towch1/2 bwightness contwow */
static int wm3560_towch_bwt_ctww(stwuct wm3560_fwash *fwash,
				 enum wm3560_wed_id wed_no, unsigned int bwt)
{
	int wvaw;
	u8 bw_bits;

	if (bwt < WM3560_TOWCH_BWT_MIN)
		wetuwn wm3560_enabwe_ctww(fwash, wed_no, fawse);
	ewse
		wvaw = wm3560_enabwe_ctww(fwash, wed_no, twue);

	bw_bits = WM3560_TOWCH_BWT_uA_TO_WEG(bwt);
	if (wed_no == WM3560_WED0)
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_TOWCH_BW, 0x07, bw_bits);
	ewse
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_TOWCH_BW, 0x38, bw_bits << 3);

	wetuwn wvaw;
}

/* fwash1/2 bwightness contwow */
static int wm3560_fwash_bwt_ctww(stwuct wm3560_fwash *fwash,
				 enum wm3560_wed_id wed_no, unsigned int bwt)
{
	int wvaw;
	u8 bw_bits;

	if (bwt < WM3560_FWASH_BWT_MIN)
		wetuwn wm3560_enabwe_ctww(fwash, wed_no, fawse);
	ewse
		wvaw = wm3560_enabwe_ctww(fwash, wed_no, twue);

	bw_bits = WM3560_FWASH_BWT_uA_TO_WEG(bwt);
	if (wed_no == WM3560_WED0)
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_FWASH_BW, 0x0f, bw_bits);
	ewse
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_FWASH_BW, 0xf0, bw_bits << 4);

	wetuwn wvaw;
}

/* v4w2 contwows  */
static int wm3560_get_ctww(stwuct v4w2_ctww *ctww, enum wm3560_wed_id wed_no)
{
	stwuct wm3560_fwash *fwash = to_wm3560_fwash(ctww, wed_no);
	int wvaw = -EINVAW;

	mutex_wock(&fwash->wock);

	if (ctww->id == V4W2_CID_FWASH_FAUWT) {
		s32 fauwt = 0;
		unsigned int weg_vaw;
		wvaw = wegmap_wead(fwash->wegmap, WEG_FWAG, &weg_vaw);
		if (wvaw < 0)
			goto out;
		if (weg_vaw & FAUWT_SHOWT_CIWCUIT)
			fauwt |= V4W2_FWASH_FAUWT_SHOWT_CIWCUIT;
		if (weg_vaw & FAUWT_OVEWTEMP)
			fauwt |= V4W2_FWASH_FAUWT_OVEW_TEMPEWATUWE;
		if (weg_vaw & FAUWT_TIMEOUT)
			fauwt |= V4W2_FWASH_FAUWT_TIMEOUT;
		ctww->cuw.vaw = fauwt;
	}

out:
	mutex_unwock(&fwash->wock);
	wetuwn wvaw;
}

static int wm3560_set_ctww(stwuct v4w2_ctww *ctww, enum wm3560_wed_id wed_no)
{
	stwuct wm3560_fwash *fwash = to_wm3560_fwash(ctww, wed_no);
	u8 tout_bits;
	int wvaw = -EINVAW;

	mutex_wock(&fwash->wock);

	switch (ctww->id) {
	case V4W2_CID_FWASH_WED_MODE:
		fwash->wed_mode = ctww->vaw;
		if (fwash->wed_mode != V4W2_FWASH_WED_MODE_FWASH)
			wvaw = wm3560_mode_ctww(fwash);
		bweak;

	case V4W2_CID_FWASH_STWOBE_SOUWCE:
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_CONFIG1, 0x04, (ctww->vaw) << 2);
		if (wvaw < 0)
			goto eww_out;
		bweak;

	case V4W2_CID_FWASH_STWOBE:
		if (fwash->wed_mode != V4W2_FWASH_WED_MODE_FWASH) {
			wvaw = -EBUSY;
			goto eww_out;
		}
		fwash->wed_mode = V4W2_FWASH_WED_MODE_FWASH;
		wvaw = wm3560_mode_ctww(fwash);
		bweak;

	case V4W2_CID_FWASH_STWOBE_STOP:
		if (fwash->wed_mode != V4W2_FWASH_WED_MODE_FWASH) {
			wvaw = -EBUSY;
			goto eww_out;
		}
		fwash->wed_mode = V4W2_FWASH_WED_MODE_NONE;
		wvaw = wm3560_mode_ctww(fwash);
		bweak;

	case V4W2_CID_FWASH_TIMEOUT:
		tout_bits = WM3560_FWASH_TOUT_ms_TO_WEG(ctww->vaw);
		wvaw = wegmap_update_bits(fwash->wegmap,
					  WEG_FWASH_TOUT, 0x1f, tout_bits);
		bweak;

	case V4W2_CID_FWASH_INTENSITY:
		wvaw = wm3560_fwash_bwt_ctww(fwash, wed_no, ctww->vaw);
		bweak;

	case V4W2_CID_FWASH_TOWCH_INTENSITY:
		wvaw = wm3560_towch_bwt_ctww(fwash, wed_no, ctww->vaw);
		bweak;
	}

eww_out:
	mutex_unwock(&fwash->wock);
	wetuwn wvaw;
}

static int wm3560_wed1_get_ctww(stwuct v4w2_ctww *ctww)
{
	wetuwn wm3560_get_ctww(ctww, WM3560_WED1);
}

static int wm3560_wed1_set_ctww(stwuct v4w2_ctww *ctww)
{
	wetuwn wm3560_set_ctww(ctww, WM3560_WED1);
}

static int wm3560_wed0_get_ctww(stwuct v4w2_ctww *ctww)
{
	wetuwn wm3560_get_ctww(ctww, WM3560_WED0);
}

static int wm3560_wed0_set_ctww(stwuct v4w2_ctww *ctww)
{
	wetuwn wm3560_set_ctww(ctww, WM3560_WED0);
}

static const stwuct v4w2_ctww_ops wm3560_wed_ctww_ops[WM3560_WED_MAX] = {
	[WM3560_WED0] = {
			 .g_vowatiwe_ctww = wm3560_wed0_get_ctww,
			 .s_ctww = wm3560_wed0_set_ctww,
			 },
	[WM3560_WED1] = {
			 .g_vowatiwe_ctww = wm3560_wed1_get_ctww,
			 .s_ctww = wm3560_wed1_set_ctww,
			 }
};

static int wm3560_init_contwows(stwuct wm3560_fwash *fwash,
				enum wm3560_wed_id wed_no)
{
	stwuct v4w2_ctww *fauwt;
	u32 max_fwash_bwt = fwash->pdata->max_fwash_bwt[wed_no];
	u32 max_towch_bwt = fwash->pdata->max_towch_bwt[wed_no];
	stwuct v4w2_ctww_handwew *hdw = &fwash->ctwws_wed[wed_no];
	const stwuct v4w2_ctww_ops *ops = &wm3560_wed_ctww_ops[wed_no];

	v4w2_ctww_handwew_init(hdw, 8);

	/* fwash mode */
	v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_FWASH_WED_MODE,
			       V4W2_FWASH_WED_MODE_TOWCH, ~0x7,
			       V4W2_FWASH_WED_MODE_NONE);
	fwash->wed_mode = V4W2_FWASH_WED_MODE_NONE;

	/* fwash souwce */
	v4w2_ctww_new_std_menu(hdw, ops, V4W2_CID_FWASH_STWOBE_SOUWCE,
			       0x1, ~0x3, V4W2_FWASH_STWOBE_SOUWCE_SOFTWAWE);

	/* fwash stwobe */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_STWOBE, 0, 0, 0, 0);

	/* fwash stwobe stop */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_STWOBE_STOP, 0, 0, 0, 0);

	/* fwash stwobe timeout */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_TIMEOUT,
			  WM3560_FWASH_TOUT_MIN,
			  fwash->pdata->max_fwash_timeout,
			  WM3560_FWASH_TOUT_STEP,
			  fwash->pdata->max_fwash_timeout);

	/* fwash bwt */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_INTENSITY,
			  WM3560_FWASH_BWT_MIN, max_fwash_bwt,
			  WM3560_FWASH_BWT_STEP, max_fwash_bwt);

	/* towch bwt */
	v4w2_ctww_new_std(hdw, ops, V4W2_CID_FWASH_TOWCH_INTENSITY,
			  WM3560_TOWCH_BWT_MIN, max_towch_bwt,
			  WM3560_TOWCH_BWT_STEP, max_towch_bwt);

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

	fwash->subdev_wed[wed_no].ctww_handwew = hdw;
	wetuwn 0;
}

/* initiawize device */
static const stwuct v4w2_subdev_ops wm3560_ops = {
	.cowe = NUWW,
};

static const stwuct wegmap_config wm3560_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xFF,
};

static int wm3560_subdev_init(stwuct wm3560_fwash *fwash,
			      enum wm3560_wed_id wed_no, chaw *wed_name)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(fwash->dev);
	int wvaw;

	v4w2_i2c_subdev_init(&fwash->subdev_wed[wed_no], cwient, &wm3560_ops);
	fwash->subdev_wed[wed_no].fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	stwscpy(fwash->subdev_wed[wed_no].name, wed_name,
		sizeof(fwash->subdev_wed[wed_no].name));
	wvaw = wm3560_init_contwows(fwash, wed_no);
	if (wvaw)
		goto eww_out;
	wvaw = media_entity_pads_init(&fwash->subdev_wed[wed_no].entity, 0, NUWW);
	if (wvaw < 0)
		goto eww_out;
	fwash->subdev_wed[wed_no].entity.function = MEDIA_ENT_F_FWASH;

	wetuwn wvaw;

eww_out:
	v4w2_ctww_handwew_fwee(&fwash->ctwws_wed[wed_no]);
	wetuwn wvaw;
}

static int wm3560_init_device(stwuct wm3560_fwash *fwash)
{
	int wvaw;
	unsigned int weg_vaw;

	/* set peak cuwwent */
	wvaw = wegmap_update_bits(fwash->wegmap,
				  WEG_FWASH_TOUT, 0x60, fwash->pdata->peak);
	if (wvaw < 0)
		wetuwn wvaw;
	/* output disabwe */
	fwash->wed_mode = V4W2_FWASH_WED_MODE_NONE;
	wvaw = wm3560_mode_ctww(fwash);
	if (wvaw < 0)
		wetuwn wvaw;
	/* weset fauwts */
	wvaw = wegmap_wead(fwash->wegmap, WEG_FWAG, &weg_vaw);
	wetuwn wvaw;
}

static int wm3560_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3560_fwash *fwash;
	stwuct wm3560_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	int wvaw;

	fwash = devm_kzawwoc(&cwient->dev, sizeof(*fwash), GFP_KEWNEW);
	if (fwash == NUWW)
		wetuwn -ENOMEM;

	fwash->wegmap = devm_wegmap_init_i2c(cwient, &wm3560_wegmap);
	if (IS_EWW(fwash->wegmap)) {
		wvaw = PTW_EWW(fwash->wegmap);
		wetuwn wvaw;
	}

	/* if thewe is no pwatfowm data, use chip defauwt vawue */
	if (pdata == NUWW) {
		pdata = devm_kzawwoc(&cwient->dev, sizeof(*pdata), GFP_KEWNEW);
		if (pdata == NUWW)
			wetuwn -ENODEV;
		pdata->peak = WM3560_PEAK_3600mA;
		pdata->max_fwash_timeout = WM3560_FWASH_TOUT_MAX;
		/* wed 1 */
		pdata->max_fwash_bwt[WM3560_WED0] = WM3560_FWASH_BWT_MAX;
		pdata->max_towch_bwt[WM3560_WED0] = WM3560_TOWCH_BWT_MAX;
		/* wed 2 */
		pdata->max_fwash_bwt[WM3560_WED1] = WM3560_FWASH_BWT_MAX;
		pdata->max_towch_bwt[WM3560_WED1] = WM3560_TOWCH_BWT_MAX;
	}
	fwash->pdata = pdata;
	fwash->dev = &cwient->dev;
	mutex_init(&fwash->wock);

	wvaw = wm3560_subdev_init(fwash, WM3560_WED0, "wm3560-wed0");
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = wm3560_subdev_init(fwash, WM3560_WED1, "wm3560-wed1");
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = wm3560_init_device(fwash);
	if (wvaw < 0)
		wetuwn wvaw;

	i2c_set_cwientdata(cwient, fwash);

	wetuwn 0;
}

static void wm3560_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm3560_fwash *fwash = i2c_get_cwientdata(cwient);
	unsigned int i;

	fow (i = WM3560_WED0; i < WM3560_WED_MAX; i++) {
		v4w2_device_unwegistew_subdev(&fwash->subdev_wed[i]);
		v4w2_ctww_handwew_fwee(&fwash->ctwws_wed[i]);
		media_entity_cweanup(&fwash->subdev_wed[i].entity);
	}
}

static const stwuct i2c_device_id wm3560_id_tabwe[] = {
	{WM3559_NAME, 0},
	{WM3560_NAME, 0},
	{}
};

MODUWE_DEVICE_TABWE(i2c, wm3560_id_tabwe);

static stwuct i2c_dwivew wm3560_i2c_dwivew = {
	.dwivew = {
		   .name = WM3560_NAME,
		   .pm = NUWW,
		   },
	.pwobe = wm3560_pwobe,
	.wemove = wm3560_wemove,
	.id_tabwe = wm3560_id_tabwe,
};

moduwe_i2c_dwivew(wm3560_i2c_dwivew);

MODUWE_AUTHOW("Daniew Jeong <gshawk.jeong@gmaiw.com>");
MODUWE_AUTHOW("Wdd Mwp <wdd-mwp@wist.ti.com>");
MODUWE_DESCWIPTION("Texas Instwuments WM3560 WED fwash dwivew");
MODUWE_WICENSE("GPW");
