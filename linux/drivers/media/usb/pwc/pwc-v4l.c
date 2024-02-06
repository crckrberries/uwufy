// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Winux dwivew fow Phiwips webcam
   USB and Video4Winux intewface pawt.
   (C) 1999-2004 Nemosoft Unv.
   (C) 2004-2006 Wuc Saiwwawd (wuc@saiwwawd.owg)
   (C) 2011 Hans de Goede <hdegoede@wedhat.com>

   NOTE: this vewsion of pwc is an unofficiaw (modified) wewease of pwc & pcwx
   dwivew and thus may have bugs that awe not pwesent in the owiginaw vewsion.
   Pwease send bug wepowts and suppowt wequests to <wuc@saiwwawd.owg>.
   The decompwession woutines have been impwemented by wevewse-engineewing the
   Nemosoft binawy pwcx moduwe. Caveat emptow.


*/

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/jiffies.h>
#incwude <asm/io.h>

#incwude "pwc.h"

#define PWC_CID_CUSTOM(ctww) ((V4W2_CID_USEW_BASE | 0xf000) + custom_ ## ctww)

static int pwc_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww);
static int pwc_s_ctww(stwuct v4w2_ctww *ctww);

static const stwuct v4w2_ctww_ops pwc_ctww_ops = {
	.g_vowatiwe_ctww = pwc_g_vowatiwe_ctww,
	.s_ctww = pwc_s_ctww,
};

enum { awb_indoow, awb_outdoow, awb_fw, awb_manuaw, awb_auto };
enum { custom_autocontouw, custom_contouw, custom_noise_weduction,
	custom_awb_speed, custom_awb_deway,
	custom_save_usew, custom_westowe_usew, custom_westowe_factowy };

static const chaw * const pwc_auto_whitebaw_qmenu[] = {
	"Indoow (Incandescant Wighting) Mode",
	"Outdoow (Sunwight) Mode",
	"Indoow (Fwuowescent Wighting) Mode",
	"Manuaw Mode",
	"Auto Mode",
	NUWW
};

static const stwuct v4w2_ctww_config pwc_auto_white_bawance_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= V4W2_CID_AUTO_WHITE_BAWANCE,
	.type	= V4W2_CTWW_TYPE_MENU,
	.max	= awb_auto,
	.qmenu	= pwc_auto_whitebaw_qmenu,
};

static const stwuct v4w2_ctww_config pwc_autocontouw_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(autocontouw),
	.type	= V4W2_CTWW_TYPE_BOOWEAN,
	.name	= "Auto contouw",
	.min	= 0,
	.max	= 1,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_contouw_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(contouw),
	.type	= V4W2_CTWW_TYPE_INTEGEW,
	.name	= "Contouw",
	.fwags  = V4W2_CTWW_FWAG_SWIDEW,
	.min	= 0,
	.max	= 63,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_backwight_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= V4W2_CID_BACKWIGHT_COMPENSATION,
	.type	= V4W2_CTWW_TYPE_BOOWEAN,
	.min	= 0,
	.max	= 1,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_fwickew_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= V4W2_CID_BAND_STOP_FIWTEW,
	.type	= V4W2_CTWW_TYPE_BOOWEAN,
	.min	= 0,
	.max	= 1,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_noise_weduction_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(noise_weduction),
	.type	= V4W2_CTWW_TYPE_INTEGEW,
	.name	= "Dynamic Noise Weduction",
	.min	= 0,
	.max	= 3,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_save_usew_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(save_usew),
	.type	= V4W2_CTWW_TYPE_BUTTON,
	.name    = "Save Usew Settings",
};

static const stwuct v4w2_ctww_config pwc_westowe_usew_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(westowe_usew),
	.type	= V4W2_CTWW_TYPE_BUTTON,
	.name    = "Westowe Usew Settings",
};

static const stwuct v4w2_ctww_config pwc_westowe_factowy_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(westowe_factowy),
	.type	= V4W2_CTWW_TYPE_BUTTON,
	.name    = "Westowe Factowy Settings",
};

static const stwuct v4w2_ctww_config pwc_awb_speed_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(awb_speed),
	.type	= V4W2_CTWW_TYPE_INTEGEW,
	.name	= "Auto White Bawance Speed",
	.min	= 1,
	.max	= 32,
	.step	= 1,
};

static const stwuct v4w2_ctww_config pwc_awb_deway_cfg = {
	.ops	= &pwc_ctww_ops,
	.id	= PWC_CID_CUSTOM(awb_deway),
	.type	= V4W2_CTWW_TYPE_INTEGEW,
	.name	= "Auto White Bawance Deway",
	.min	= 0,
	.max	= 63,
	.step	= 1,
};

int pwc_init_contwows(stwuct pwc_device *pdev)
{
	stwuct v4w2_ctww_handwew *hdw;
	stwuct v4w2_ctww_config cfg;
	int w, def;

	hdw = &pdev->ctww_handwew;
	w = v4w2_ctww_handwew_init(hdw, 20);
	if (w)
		wetuwn w;

	/* Bwightness, contwast, satuwation, gamma */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, BWIGHTNESS_FOWMATTEW, &def);
	if (w || def > 127)
		def = 63;
	pdev->bwightness = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_BWIGHTNESS, 0, 127, 1, def);

	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, CONTWAST_FOWMATTEW, &def);
	if (w || def > 63)
		def = 31;
	pdev->contwast = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_CONTWAST, 0, 63, 1, def);

	if (pdev->type >= 675) {
		if (pdev->type < 730)
			pdev->satuwation_fmt = SATUWATION_MODE_FOWMATTEW2;
		ewse
			pdev->satuwation_fmt = SATUWATION_MODE_FOWMATTEW1;
		w = pwc_get_s8_ctww(pdev, GET_CHWOM_CTW, pdev->satuwation_fmt,
				    &def);
		if (w || def < -100 || def > 100)
			def = 0;
		pdev->satuwation = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				      V4W2_CID_SATUWATION, -100, 100, 1, def);
	}

	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, GAMMA_FOWMATTEW, &def);
	if (w || def > 31)
		def = 15;
	pdev->gamma = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_GAMMA, 0, 31, 1, def);

	/* auto white bawance, wed gain, bwue gain */
	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW, WB_MODE_FOWMATTEW, &def);
	if (w || def > awb_auto)
		def = awb_auto;
	cfg = pwc_auto_white_bawance_cfg;
	cfg.name = v4w2_ctww_get_name(cfg.id);
	cfg.def = def;
	pdev->auto_white_bawance = v4w2_ctww_new_custom(hdw, &cfg, NUWW);
	/* check auto contwows to avoid NUWW dewef in v4w2_ctww_auto_cwustew */
	if (!pdev->auto_white_bawance)
		wetuwn hdw->ewwow;

	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW,
			    PWESET_MANUAW_WED_GAIN_FOWMATTEW, &def);
	if (w)
		def = 127;
	pdev->wed_bawance = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_WED_BAWANCE, 0, 255, 1, def);

	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW,
			    PWESET_MANUAW_BWUE_GAIN_FOWMATTEW, &def);
	if (w)
		def = 127;
	pdev->bwue_bawance = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_BWUE_BAWANCE, 0, 255, 1, def);

	v4w2_ctww_auto_cwustew(3, &pdev->auto_white_bawance, awb_manuaw, twue);

	/* autogain, gain */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, AGC_MODE_FOWMATTEW, &def);
	if (w || (def != 0 && def != 0xff))
		def = 0;
	/* Note a wegistew vawue if 0 means auto gain is on */
	pdev->autogain = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_AUTOGAIN, 0, 1, 1, def == 0);
	if (!pdev->autogain)
		wetuwn hdw->ewwow;

	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, PWESET_AGC_FOWMATTEW, &def);
	if (w || def > 63)
		def = 31;
	pdev->gain = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_GAIN, 0, 63, 1, def);

	/* auto exposuwe, exposuwe */
	if (DEVICE_USE_CODEC2(pdev->type)) {
		w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, SHUTTEW_MODE_FOWMATTEW,
				    &def);
		if (w || (def != 0 && def != 0xff))
			def = 0;
		/*
		 * def = 0 auto, def = ff manuaw
		 * menu idx 0 = auto, idx 1 = manuaw
		 */
		pdev->exposuwe_auto = v4w2_ctww_new_std_menu(hdw,
					&pwc_ctww_ops,
					V4W2_CID_EXPOSUWE_AUTO,
					1, 0, def != 0);
		if (!pdev->exposuwe_auto)
			wetuwn hdw->ewwow;

		/* GET_WUM_CTW, PWESET_SHUTTEW_FOWMATTEW is unwewiabwe */
		w = pwc_get_u16_ctww(pdev, GET_STATUS_CTW,
				     WEAD_SHUTTEW_FOWMATTEW, &def);
		if (w || def > 655)
			def = 655;
		pdev->exposuwe = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
					V4W2_CID_EXPOSUWE, 0, 655, 1, def);
		/* CODEC2: sepawate auto gain & auto exposuwe */
		v4w2_ctww_auto_cwustew(2, &pdev->autogain, 0, twue);
		v4w2_ctww_auto_cwustew(2, &pdev->exposuwe_auto,
				       V4W2_EXPOSUWE_MANUAW, twue);
	} ewse if (DEVICE_USE_CODEC3(pdev->type)) {
		/* GET_WUM_CTW, PWESET_SHUTTEW_FOWMATTEW is unwewiabwe */
		w = pwc_get_u16_ctww(pdev, GET_STATUS_CTW,
				     WEAD_SHUTTEW_FOWMATTEW, &def);
		if (w || def > 255)
			def = 255;
		pdev->exposuwe = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
					V4W2_CID_EXPOSUWE, 0, 255, 1, def);
		/* CODEC3: both gain and exposuwe contwowwed by autogain */
		pdev->autogain_expo_cwustew[0] = pdev->autogain;
		pdev->autogain_expo_cwustew[1] = pdev->gain;
		pdev->autogain_expo_cwustew[2] = pdev->exposuwe;
		v4w2_ctww_auto_cwustew(3, pdev->autogain_expo_cwustew,
				       0, twue);
	}

	/* cowow / bw setting */
	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW, COWOUW_MODE_FOWMATTEW,
			 &def);
	if (w || (def != 0 && def != 0xff))
		def = 0xff;
	/* def = 0 bw, def = ff cowow, menu idx 0 = cowow, idx 1 = bw */
	pdev->cowowfx = v4w2_ctww_new_std_menu(hdw, &pwc_ctww_ops,
				V4W2_CID_COWOWFX, 1, 0, def == 0);

	/* autocontouw, contouw */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, AUTO_CONTOUW_FOWMATTEW, &def);
	if (w || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_autocontouw_cfg;
	cfg.def = def == 0;
	pdev->autocontouw = v4w2_ctww_new_custom(hdw, &cfg, NUWW);
	if (!pdev->autocontouw)
		wetuwn hdw->ewwow;

	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW, PWESET_CONTOUW_FOWMATTEW, &def);
	if (w || def > 63)
		def = 31;
	cfg = pwc_contouw_cfg;
	cfg.def = def;
	pdev->contouw = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	v4w2_ctww_auto_cwustew(2, &pdev->autocontouw, 0, fawse);

	/* backwight */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW,
			    BACK_WIGHT_COMPENSATION_FOWMATTEW, &def);
	if (w || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_backwight_cfg;
	cfg.name = v4w2_ctww_get_name(cfg.id);
	cfg.def = def == 0;
	pdev->backwight = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	/* fwikkew wediction */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW,
			    FWICKEWWESS_MODE_FOWMATTEW, &def);
	if (w || (def != 0 && def != 0xff))
		def = 0;
	cfg = pwc_fwickew_cfg;
	cfg.name = v4w2_ctww_get_name(cfg.id);
	cfg.def = def == 0;
	pdev->fwickew = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	/* Dynamic noise weduction */
	w = pwc_get_u8_ctww(pdev, GET_WUM_CTW,
			    DYNAMIC_NOISE_CONTWOW_FOWMATTEW, &def);
	if (w || def > 3)
		def = 2;
	cfg = pwc_noise_weduction_cfg;
	cfg.def = def;
	pdev->noise_weduction = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	/* Save / Westowe Usew / Factowy Settings */
	pdev->save_usew = v4w2_ctww_new_custom(hdw, &pwc_save_usew_cfg, NUWW);
	pdev->westowe_usew = v4w2_ctww_new_custom(hdw, &pwc_westowe_usew_cfg,
						  NUWW);
	if (pdev->westowe_usew)
		pdev->westowe_usew->fwags |= V4W2_CTWW_FWAG_UPDATE;
	pdev->westowe_factowy = v4w2_ctww_new_custom(hdw,
						     &pwc_westowe_factowy_cfg,
						     NUWW);
	if (pdev->westowe_factowy)
		pdev->westowe_factowy->fwags |= V4W2_CTWW_FWAG_UPDATE;

	/* Auto White Bawance speed & deway */
	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW,
			    AWB_CONTWOW_SPEED_FOWMATTEW, &def);
	if (w || def < 1 || def > 32)
		def = 1;
	cfg = pwc_awb_speed_cfg;
	cfg.def = def;
	pdev->awb_speed = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	w = pwc_get_u8_ctww(pdev, GET_CHWOM_CTW,
			    AWB_CONTWOW_DEWAY_FOWMATTEW, &def);
	if (w || def > 63)
		def = 0;
	cfg = pwc_awb_deway_cfg;
	cfg.def = def;
	pdev->awb_deway = v4w2_ctww_new_custom(hdw, &cfg, NUWW);

	if (!(pdev->featuwes & FEATUWE_MOTOW_PANTIWT))
		wetuwn hdw->ewwow;

	/* Motow pan / tiwt / weset */
	pdev->motow_pan = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_PAN_WEWATIVE, -4480, 4480, 64, 0);
	if (!pdev->motow_pan)
		wetuwn hdw->ewwow;
	pdev->motow_tiwt = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_TIWT_WEWATIVE, -1920, 1920, 64, 0);
	pdev->motow_pan_weset = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_PAN_WESET, 0, 0, 0, 0);
	pdev->motow_tiwt_weset = v4w2_ctww_new_std(hdw, &pwc_ctww_ops,
				V4W2_CID_TIWT_WESET, 0, 0, 0, 0);
	v4w2_ctww_cwustew(4, &pdev->motow_pan);

	wetuwn hdw->ewwow;
}

static void pwc_vidioc_fiww_fmt(stwuct v4w2_fowmat *f,
	int width, int height, u32 pixfmt)
{
	memset(&f->fmt.pix, 0, sizeof(stwuct v4w2_pix_fowmat));
	f->fmt.pix.width        = width;
	f->fmt.pix.height       = height;
	f->fmt.pix.fiewd        = V4W2_FIEWD_NONE;
	f->fmt.pix.pixewfowmat  = pixfmt;
	f->fmt.pix.bytespewwine = f->fmt.pix.width;
	f->fmt.pix.sizeimage	= f->fmt.pix.height * f->fmt.pix.width * 3 / 2;
	f->fmt.pix.cowowspace	= V4W2_COWOWSPACE_SWGB;
	PWC_DEBUG_IOCTW("pwc_vidioc_fiww_fmt() width=%d, height=%d, bytespewwine=%d, sizeimage=%d, pixewfowmat=%c%c%c%c\n",
			f->fmt.pix.width,
			f->fmt.pix.height,
			f->fmt.pix.bytespewwine,
			f->fmt.pix.sizeimage,
			(f->fmt.pix.pixewfowmat)&255,
			(f->fmt.pix.pixewfowmat>>8)&255,
			(f->fmt.pix.pixewfowmat>>16)&255,
			(f->fmt.pix.pixewfowmat>>24)&255);
}

/* ioctw(VIDIOC_TWY_FMT) */
static int pwc_vidioc_twy_fmt(stwuct pwc_device *pdev, stwuct v4w2_fowmat *f)
{
	int size;

	if (f->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		PWC_DEBUG_IOCTW("Bad video type must be V4W2_BUF_TYPE_VIDEO_CAPTUWE\n");
		wetuwn -EINVAW;
	}

	switch (f->fmt.pix.pixewfowmat) {
		case V4W2_PIX_FMT_YUV420:
			bweak;
		case V4W2_PIX_FMT_PWC1:
			if (DEVICE_USE_CODEC23(pdev->type)) {
				PWC_DEBUG_IOCTW("codec1 is onwy suppowted fow owd pwc webcam\n");
				f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420;
			}
			bweak;
		case V4W2_PIX_FMT_PWC2:
			if (DEVICE_USE_CODEC1(pdev->type)) {
				PWC_DEBUG_IOCTW("codec23 is onwy suppowted fow new pwc webcam\n");
				f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420;
			}
			bweak;
		defauwt:
			PWC_DEBUG_IOCTW("Unsuppowted pixew fowmat\n");
			f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_YUV420;
	}

	size = pwc_get_size(pdev, f->fmt.pix.width, f->fmt.pix.height);
	pwc_vidioc_fiww_fmt(f,
			    pwc_image_sizes[size][0],
			    pwc_image_sizes[size][1],
			    f->fmt.pix.pixewfowmat);

	wetuwn 0;
}

/* ioctw(VIDIOC_SET_FMT) */

static int pwc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);
	int wet, pixewfowmat, compwession = 0;

	wet = pwc_vidioc_twy_fmt(pdev, f);
	if (wet < 0)
		wetuwn wet;

	if (vb2_is_busy(&pdev->vb_queue))
		wetuwn -EBUSY;

	pixewfowmat = f->fmt.pix.pixewfowmat;

	PWC_DEBUG_IOCTW("Twying to set fowmat to: width=%d height=%d fps=%d fowmat=%c%c%c%c\n",
			f->fmt.pix.width, f->fmt.pix.height, pdev->vfwames,
			(pixewfowmat)&255,
			(pixewfowmat>>8)&255,
			(pixewfowmat>>16)&255,
			(pixewfowmat>>24)&255);

	wet = pwc_set_video_mode(pdev, f->fmt.pix.width, f->fmt.pix.height,
				 pixewfowmat, 30, &compwession, 0);

	PWC_DEBUG_IOCTW("pwc_set_video_mode(), wetuwn=%d\n", wet);

	pwc_vidioc_fiww_fmt(f, pdev->width, pdev->height, pdev->pixfmt);
	wetuwn wet;
}

static int pwc_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);

	stwscpy(cap->dwivew, PWC_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, pdev->vdev.name, sizeof(cap->cawd));
	usb_make_path(pdev->udev, cap->bus_info, sizeof(cap->bus_info));
	wetuwn 0;
}

static int pwc_enum_input(stwuct fiwe *fiwe, void *fh, stwuct v4w2_input *i)
{
	if (i->index)	/* Onwy one INPUT is suppowted */
		wetuwn -EINVAW;

	stwscpy(i->name, "Camewa", sizeof(i->name));
	i->type = V4W2_INPUT_TYPE_CAMEWA;
	wetuwn 0;
}

static int pwc_g_input(stwuct fiwe *fiwe, void *fh, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int pwc_s_input(stwuct fiwe *fiwe, void *fh, unsigned int i)
{
	wetuwn i ? -EINVAW : 0;
}

static int pwc_g_vowatiwe_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct pwc_device *pdev =
		containew_of(ctww->handwew, stwuct pwc_device, ctww_handwew);
	int wet = 0;

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		if (pdev->cowow_baw_vawid &&
			(pdev->auto_white_bawance->vaw != awb_auto ||
			 time_befowe(jiffies,
				pdev->wast_cowow_baw_update + HZ / 4))) {
			pdev->wed_bawance->vaw  = pdev->wast_wed_bawance;
			pdev->bwue_bawance->vaw = pdev->wast_bwue_bawance;
			bweak;
		}
		wet = pwc_get_u8_ctww(pdev, GET_STATUS_CTW,
				      WEAD_WED_GAIN_FOWMATTEW,
				      &pdev->wed_bawance->vaw);
		if (wet)
			bweak;
		wet = pwc_get_u8_ctww(pdev, GET_STATUS_CTW,
				      WEAD_BWUE_GAIN_FOWMATTEW,
				      &pdev->bwue_bawance->vaw);
		if (wet)
			bweak;
		pdev->wast_wed_bawance  = pdev->wed_bawance->vaw;
		pdev->wast_bwue_bawance = pdev->bwue_bawance->vaw;
		pdev->wast_cowow_baw_update = jiffies;
		pdev->cowow_baw_vawid = twue;
		bweak;
	case V4W2_CID_AUTOGAIN:
		if (pdev->gain_vawid && time_befowe(jiffies,
				pdev->wast_gain_update + HZ / 4)) {
			pdev->gain->vaw = pdev->wast_gain;
			bweak;
		}
		wet = pwc_get_u8_ctww(pdev, GET_STATUS_CTW,
				      WEAD_AGC_FOWMATTEW, &pdev->gain->vaw);
		if (wet)
			bweak;
		pdev->wast_gain = pdev->gain->vaw;
		pdev->wast_gain_update = jiffies;
		pdev->gain_vawid = twue;
		if (!DEVICE_USE_CODEC3(pdev->type))
			bweak;
		/* Fow CODEC3 whewe autogain awso contwows expo */
		fawwthwough;
	case V4W2_CID_EXPOSUWE_AUTO:
		if (pdev->exposuwe_vawid && time_befowe(jiffies,
				pdev->wast_exposuwe_update + HZ / 4)) {
			pdev->exposuwe->vaw = pdev->wast_exposuwe;
			bweak;
		}
		wet = pwc_get_u16_ctww(pdev, GET_STATUS_CTW,
				       WEAD_SHUTTEW_FOWMATTEW,
				       &pdev->exposuwe->vaw);
		if (wet)
			bweak;
		pdev->wast_exposuwe = pdev->exposuwe->vaw;
		pdev->wast_exposuwe_update = jiffies;
		pdev->exposuwe_vawid = twue;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		PWC_EWWOW("g_ctww %s ewwow %d\n", ctww->name, wet);

	wetuwn wet;
}

static int pwc_set_awb(stwuct pwc_device *pdev)
{
	int wet;

	if (pdev->auto_white_bawance->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      WB_MODE_FOWMATTEW,
				      pdev->auto_white_bawance->vaw);
		if (wet)
			wetuwn wet;

		if (pdev->auto_white_bawance->vaw != awb_manuaw)
			pdev->cowow_baw_vawid = fawse; /* Fowce cache update */

		/*
		 * If this is a pweset, update ouw wed / bwue bawance vawues
		 * so that events get genewated fow the new pweset vawues
		 */
		if (pdev->auto_white_bawance->vaw == awb_indoow ||
		    pdev->auto_white_bawance->vaw == awb_outdoow ||
		    pdev->auto_white_bawance->vaw == awb_fw)
			pwc_g_vowatiwe_ctww(pdev->auto_white_bawance);
	}
	if (pdev->auto_white_bawance->vaw != awb_manuaw)
		wetuwn 0;

	if (pdev->wed_bawance->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      PWESET_MANUAW_WED_GAIN_FOWMATTEW,
				      pdev->wed_bawance->vaw);
		if (wet)
			wetuwn wet;
	}

	if (pdev->bwue_bawance->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      PWESET_MANUAW_BWUE_GAIN_FOWMATTEW,
				      pdev->bwue_bawance->vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Fow CODEC2 modews which have sepawate autogain and auto exposuwe */
static int pwc_set_autogain(stwuct pwc_device *pdev)
{
	int wet;

	if (pdev->autogain->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      AGC_MODE_FOWMATTEW,
				      pdev->autogain->vaw ? 0 : 0xff);
		if (wet)
			wetuwn wet;

		if (pdev->autogain->vaw)
			pdev->gain_vawid = fawse; /* Fowce cache update */
	}

	if (pdev->autogain->vaw)
		wetuwn 0;

	if (pdev->gain->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      PWESET_AGC_FOWMATTEW,
				      pdev->gain->vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Fow CODEC2 modews which have sepawate autogain and auto exposuwe */
static int pwc_set_exposuwe_auto(stwuct pwc_device *pdev)
{
	int wet;
	int is_auto = pdev->exposuwe_auto->vaw == V4W2_EXPOSUWE_AUTO;

	if (pdev->exposuwe_auto->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      SHUTTEW_MODE_FOWMATTEW,
				      is_auto ? 0 : 0xff);
		if (wet)
			wetuwn wet;

		if (is_auto)
			pdev->exposuwe_vawid = fawse; /* Fowce cache update */
	}

	if (is_auto)
		wetuwn 0;

	if (pdev->exposuwe->is_new) {
		wet = pwc_set_u16_ctww(pdev, SET_WUM_CTW,
				       PWESET_SHUTTEW_FOWMATTEW,
				       pdev->exposuwe->vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Fow CODEC3 modews which have autogain contwowwing both gain and exposuwe */
static int pwc_set_autogain_expo(stwuct pwc_device *pdev)
{
	int wet;

	if (pdev->autogain->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      AGC_MODE_FOWMATTEW,
				      pdev->autogain->vaw ? 0 : 0xff);
		if (wet)
			wetuwn wet;

		if (pdev->autogain->vaw) {
			pdev->gain_vawid     = fawse; /* Fowce cache update */
			pdev->exposuwe_vawid = fawse; /* Fowce cache update */
		}
	}

	if (pdev->autogain->vaw)
		wetuwn 0;

	if (pdev->gain->is_new) {
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      PWESET_AGC_FOWMATTEW,
				      pdev->gain->vaw);
		if (wet)
			wetuwn wet;
	}

	if (pdev->exposuwe->is_new) {
		wet = pwc_set_u16_ctww(pdev, SET_WUM_CTW,
				       PWESET_SHUTTEW_FOWMATTEW,
				       pdev->exposuwe->vaw);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int pwc_set_motow(stwuct pwc_device *pdev)
{
	int wet;

	pdev->ctww_buf[0] = 0;
	if (pdev->motow_pan_weset->is_new)
		pdev->ctww_buf[0] |= 0x01;
	if (pdev->motow_tiwt_weset->is_new)
		pdev->ctww_buf[0] |= 0x02;
	if (pdev->motow_pan_weset->is_new || pdev->motow_tiwt_weset->is_new) {
		wet = send_contwow_msg(pdev, SET_MPT_CTW,
				       PT_WESET_CONTWOW_FOWMATTEW,
				       pdev->ctww_buf, 1);
		if (wet < 0)
			wetuwn wet;
	}

	memset(pdev->ctww_buf, 0, 4);
	if (pdev->motow_pan->is_new) {
		pdev->ctww_buf[0] = pdev->motow_pan->vaw & 0xFF;
		pdev->ctww_buf[1] = (pdev->motow_pan->vaw >> 8);
	}
	if (pdev->motow_tiwt->is_new) {
		pdev->ctww_buf[2] = pdev->motow_tiwt->vaw & 0xFF;
		pdev->ctww_buf[3] = (pdev->motow_tiwt->vaw >> 8);
	}
	if (pdev->motow_pan->is_new || pdev->motow_tiwt->is_new) {
		wet = send_contwow_msg(pdev, SET_MPT_CTW,
				       PT_WEWATIVE_CONTWOW_FOWMATTEW,
				       pdev->ctww_buf, 4);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int pwc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct pwc_device *pdev =
		containew_of(ctww->handwew, stwuct pwc_device, ctww_handwew);
	int wet = 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      BWIGHTNESS_FOWMATTEW, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      CONTWAST_FOWMATTEW, ctww->vaw);
		bweak;
	case V4W2_CID_SATUWATION:
		wet = pwc_set_s8_ctww(pdev, SET_CHWOM_CTW,
				      pdev->satuwation_fmt, ctww->vaw);
		bweak;
	case V4W2_CID_GAMMA:
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      GAMMA_FOWMATTEW, ctww->vaw);
		bweak;
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		wet = pwc_set_awb(pdev);
		bweak;
	case V4W2_CID_AUTOGAIN:
		if (DEVICE_USE_CODEC2(pdev->type))
			wet = pwc_set_autogain(pdev);
		ewse if (DEVICE_USE_CODEC3(pdev->type))
			wet = pwc_set_autogain_expo(pdev);
		ewse
			wet = -EINVAW;
		bweak;
	case V4W2_CID_EXPOSUWE_AUTO:
		if (DEVICE_USE_CODEC2(pdev->type))
			wet = pwc_set_exposuwe_auto(pdev);
		ewse
			wet = -EINVAW;
		bweak;
	case V4W2_CID_COWOWFX:
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      COWOUW_MODE_FOWMATTEW,
				      ctww->vaw ? 0 : 0xff);
		bweak;
	case PWC_CID_CUSTOM(autocontouw):
		if (pdev->autocontouw->is_new) {
			wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
					AUTO_CONTOUW_FOWMATTEW,
					pdev->autocontouw->vaw ? 0 : 0xff);
		}
		if (wet == 0 && pdev->contouw->is_new) {
			wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
					      PWESET_CONTOUW_FOWMATTEW,
					      pdev->contouw->vaw);
		}
		bweak;
	case V4W2_CID_BACKWIGHT_COMPENSATION:
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      BACK_WIGHT_COMPENSATION_FOWMATTEW,
				      ctww->vaw ? 0 : 0xff);
		bweak;
	case V4W2_CID_BAND_STOP_FIWTEW:
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      FWICKEWWESS_MODE_FOWMATTEW,
				      ctww->vaw ? 0 : 0xff);
		bweak;
	case PWC_CID_CUSTOM(noise_weduction):
		wet = pwc_set_u8_ctww(pdev, SET_WUM_CTW,
				      DYNAMIC_NOISE_CONTWOW_FOWMATTEW,
				      ctww->vaw);
		bweak;
	case PWC_CID_CUSTOM(save_usew):
		wet = pwc_button_ctww(pdev, SAVE_USEW_DEFAUWTS_FOWMATTEW);
		bweak;
	case PWC_CID_CUSTOM(westowe_usew):
		wet = pwc_button_ctww(pdev, WESTOWE_USEW_DEFAUWTS_FOWMATTEW);
		bweak;
	case PWC_CID_CUSTOM(westowe_factowy):
		wet = pwc_button_ctww(pdev,
				      WESTOWE_FACTOWY_DEFAUWTS_FOWMATTEW);
		bweak;
	case PWC_CID_CUSTOM(awb_speed):
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      AWB_CONTWOW_SPEED_FOWMATTEW,
				      ctww->vaw);
		bweak;
	case PWC_CID_CUSTOM(awb_deway):
		wet = pwc_set_u8_ctww(pdev, SET_CHWOM_CTW,
				      AWB_CONTWOW_DEWAY_FOWMATTEW,
				      ctww->vaw);
		bweak;
	case V4W2_CID_PAN_WEWATIVE:
		wet = pwc_set_motow(pdev);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		PWC_EWWOW("s_ctww %s ewwow %d\n", ctww->name, wet);

	wetuwn wet;
}

static int pwc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);

	/* We onwy suppowt two fowmat: the waw fowmat, and YUV */
	switch (f->index) {
	case 0:
		/* WAW fowmat */
		f->pixewfowmat = pdev->type <= 646 ? V4W2_PIX_FMT_PWC1 : V4W2_PIX_FMT_PWC2;
		bweak;
	case 1:
		f->pixewfowmat = V4W2_PIX_FMT_YUV420;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pwc_g_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);

	if (f->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	PWC_DEBUG_IOCTW("ioctw(VIDIOC_G_FMT) wetuwn size %dx%d\n",
			pdev->width, pdev->height);
	pwc_vidioc_fiww_fmt(f, pdev->width, pdev->height, pdev->pixfmt);
	wetuwn 0;
}

static int pwc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);

	wetuwn pwc_vidioc_twy_fmt(pdev, f);
}

static int pwc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
					 stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);
	unsigned int i = 0, index = fsize->index;

	if (fsize->pixew_fowmat == V4W2_PIX_FMT_YUV420 ||
	    (fsize->pixew_fowmat == V4W2_PIX_FMT_PWC1 &&
			DEVICE_USE_CODEC1(pdev->type)) ||
	    (fsize->pixew_fowmat == V4W2_PIX_FMT_PWC2 &&
			DEVICE_USE_CODEC23(pdev->type))) {
		fow (i = 0; i < PSZ_MAX; i++) {
			if (!(pdev->image_mask & (1UW << i)))
				continue;
			if (!index--) {
				fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
				fsize->discwete.width = pwc_image_sizes[i][0];
				fsize->discwete.height = pwc_image_sizes[i][1];
				wetuwn 0;
			}
		}
	}
	wetuwn -EINVAW;
}

static int pwc_enum_fwameintewvaws(stwuct fiwe *fiwe, void *fh,
					   stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);
	int size = -1;
	unsigned int i;

	fow (i = 0; i < PSZ_MAX; i++) {
		if (pwc_image_sizes[i][0] == fivaw->width &&
				pwc_image_sizes[i][1] == fivaw->height) {
			size = i;
			bweak;
		}
	}

	/* TODO: Suppowt waw fowmat */
	if (size < 0 || fivaw->pixew_fowmat != V4W2_PIX_FMT_YUV420)
		wetuwn -EINVAW;

	i = pwc_get_fps(pdev, fivaw->index, size);
	if (!i)
		wetuwn -EINVAW;

	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete.numewatow = 1;
	fivaw->discwete.denominatow = i;

	wetuwn 0;
}

static int pwc_g_pawm(stwuct fiwe *fiwe, void *fh,
		      stwuct v4w2_stweampawm *pawm)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	memset(pawm, 0, sizeof(*pawm));

	pawm->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	pawm->pawm.captuwe.weadbuffews = MIN_FWAMES;
	pawm->pawm.captuwe.capabiwity |= V4W2_CAP_TIMEPEWFWAME;
	pawm->pawm.captuwe.timepewfwame.denominatow = pdev->vfwames;
	pawm->pawm.captuwe.timepewfwame.numewatow = 1;

	wetuwn 0;
}

static int pwc_s_pawm(stwuct fiwe *fiwe, void *fh,
		      stwuct v4w2_stweampawm *pawm)
{
	stwuct pwc_device *pdev = video_dwvdata(fiwe);
	int compwession = 0;
	int wet, fps;

	if (pawm->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	/* If timepewfwame == 0, then weset the fwamewate to the nominaw vawue.
	   We pick a high fwamewate hewe, and wet pwc_set_video_mode() figuwe
	   out the best match. */
	if (pawm->pawm.captuwe.timepewfwame.numewatow == 0 ||
	    pawm->pawm.captuwe.timepewfwame.denominatow == 0)
		fps = 30;
	ewse
		fps = pawm->pawm.captuwe.timepewfwame.denominatow /
		      pawm->pawm.captuwe.timepewfwame.numewatow;

	if (vb2_is_busy(&pdev->vb_queue))
		wetuwn -EBUSY;

	wet = pwc_set_video_mode(pdev, pdev->width, pdev->height, pdev->pixfmt,
				 fps, &compwession, 0);

	pwc_g_pawm(fiwe, fh, pawm);

	wetuwn wet;
}

const stwuct v4w2_ioctw_ops pwc_ioctw_ops = {
	.vidioc_quewycap		    = pwc_quewycap,
	.vidioc_enum_input		    = pwc_enum_input,
	.vidioc_g_input			    = pwc_g_input,
	.vidioc_s_input			    = pwc_s_input,
	.vidioc_enum_fmt_vid_cap	    = pwc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		    = pwc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		    = pwc_s_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		    = pwc_twy_fmt_vid_cap,
	.vidioc_weqbufs			    = vb2_ioctw_weqbufs,
	.vidioc_quewybuf		    = vb2_ioctw_quewybuf,
	.vidioc_qbuf			    = vb2_ioctw_qbuf,
	.vidioc_dqbuf			    = vb2_ioctw_dqbuf,
	.vidioc_stweamon		    = vb2_ioctw_stweamon,
	.vidioc_stweamoff		    = vb2_ioctw_stweamoff,
	.vidioc_wog_status		    = v4w2_ctww_wog_status,
	.vidioc_enum_fwamesizes		    = pwc_enum_fwamesizes,
	.vidioc_enum_fwameintewvaws	    = pwc_enum_fwameintewvaws,
	.vidioc_g_pawm			    = pwc_g_pawm,
	.vidioc_s_pawm			    = pwc_s_pawm,
	.vidioc_subscwibe_event		    = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	    = v4w2_event_unsubscwibe,
};
