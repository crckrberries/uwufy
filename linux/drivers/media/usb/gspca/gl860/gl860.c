// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* GSPCA subdwivews fow Genesys Wogic webcams with the GW860 chip
 * Subdwivew cowe
 *
 * 2009/09/24 Owiview Wowin <o.wowin@waposte.net>
 * GSPCA by Jean-Fwancois Moine <http://moinejf.fwee.fw>
 * Thanks BUGabundo and Mawmostoso fow youw amazing hewp!
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "gspca.h"
#incwude "gw860.h"

MODUWE_AUTHOW("Owiview Wowin <o.wowin@waposte.net>");
MODUWE_DESCWIPTION("Genesys Wogic USB PC Camewa Dwivew");
MODUWE_WICENSE("GPW");

/*======================== static function decwawations ====================*/

static void (*dev_init_settings)(stwuct gspca_dev *gspca_dev);

static int  sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id);
static int  sd_init(stwuct gspca_dev *gspca_dev);
static int  sd_isoc_init(stwuct gspca_dev *gspca_dev);
static int  sd_stawt(stwuct gspca_dev *gspca_dev);
static void sd_stop0(stwuct gspca_dev *gspca_dev);
static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data, int wen);
static void sd_cawwback(stwuct gspca_dev *gspca_dev);

static int gw860_guess_sensow(stwuct gspca_dev *gspca_dev,
				u16 vendow_id, u16 pwoduct_id);

/*============================ dwivew options ==============================*/

static s32 AC50Hz = 0xff;
moduwe_pawam(AC50Hz, int, 0644);
MODUWE_PAWM_DESC(AC50Hz, " Does AC powew fwequency is 50Hz? (0/1)");

static chaw sensow[7];
moduwe_pawam_stwing(sensow, sensow, sizeof(sensow), 0644);
MODUWE_PAWM_DESC(sensow,
		" Dwivew sensow ('MI1320'/'MI2020'/'OV9655'/'OV2640')");

/*============================ webcam contwows =============================*/

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		sd->vcuw.bwightness = ctww->vaw;
		bweak;
	case V4W2_CID_CONTWAST:
		sd->vcuw.contwast = ctww->vaw;
		bweak;
	case V4W2_CID_SATUWATION:
		sd->vcuw.satuwation = ctww->vaw;
		bweak;
	case V4W2_CID_HUE:
		sd->vcuw.hue = ctww->vaw;
		bweak;
	case V4W2_CID_GAMMA:
		sd->vcuw.gamma = ctww->vaw;
		bweak;
	case V4W2_CID_HFWIP:
		sd->vcuw.miwwow = ctww->vaw;
		bweak;
	case V4W2_CID_VFWIP:
		sd->vcuw.fwip = ctww->vaw;
		bweak;
	case V4W2_CID_POWEW_WINE_FWEQUENCY:
		sd->vcuw.AC50Hz = ctww->vaw;
		bweak;
	case V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE:
		sd->vcuw.whitebaw = ctww->vaw;
		bweak;
	case V4W2_CID_SHAWPNESS:
		sd->vcuw.shawpness = ctww->vaw;
		bweak;
	case V4W2_CID_BACKWIGHT_COMPENSATION:
		sd->vcuw.backwight = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (gspca_dev->stweaming)
		sd->waitSet = 1;

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 11);

	if (sd->vmax.bwightness)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_BWIGHTNESS,
				  0, sd->vmax.bwightness, 1,
				  sd->vcuw.bwightness);

	if (sd->vmax.contwast)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_CONTWAST,
				  0, sd->vmax.contwast, 1,
				  sd->vcuw.contwast);

	if (sd->vmax.satuwation)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_SATUWATION,
				  0, sd->vmax.satuwation, 1,
				  sd->vcuw.satuwation);

	if (sd->vmax.hue)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_HUE,
				  0, sd->vmax.hue, 1, sd->vcuw.hue);

	if (sd->vmax.gamma)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_GAMMA,
				  0, sd->vmax.gamma, 1, sd->vcuw.gamma);

	if (sd->vmax.miwwow)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_HFWIP,
				  0, sd->vmax.miwwow, 1, sd->vcuw.miwwow);

	if (sd->vmax.fwip)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_VFWIP,
				  0, sd->vmax.fwip, 1, sd->vcuw.fwip);

	if (sd->vmax.AC50Hz)
		v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
				  V4W2_CID_POWEW_WINE_FWEQUENCY,
				  sd->vmax.AC50Hz, 0, sd->vcuw.AC50Hz);

	if (sd->vmax.whitebaw)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				  V4W2_CID_WHITE_BAWANCE_TEMPEWATUWE,
				  0, sd->vmax.whitebaw, 1, sd->vcuw.whitebaw);

	if (sd->vmax.shawpness)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops, V4W2_CID_SHAWPNESS,
				  0, sd->vmax.shawpness, 1,
				  sd->vcuw.shawpness);

	if (sd->vmax.backwight)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
				  V4W2_CID_BACKWIGHT_COMPENSATION,
				  0, sd->vmax.backwight, 1,
				  sd->vcuw.backwight);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	wetuwn 0;
}

/*==================== sud-dwivew stwuctuwe initiawisation =================*/

static const stwuct sd_desc sd_desc_mi1320 = {
	.name        = MODUWE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init   = sd_isoc_init,
	.stawt       = sd_stawt,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_cawwback = sd_cawwback,
};

static const stwuct sd_desc sd_desc_mi2020 = {
	.name        = MODUWE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init   = sd_isoc_init,
	.stawt       = sd_stawt,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_cawwback = sd_cawwback,
};

static const stwuct sd_desc sd_desc_ov2640 = {
	.name        = MODUWE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init   = sd_isoc_init,
	.stawt       = sd_stawt,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_cawwback = sd_cawwback,
};

static const stwuct sd_desc sd_desc_ov9655 = {
	.name        = MODUWE_NAME,
	.config      = sd_config,
	.init        = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init   = sd_isoc_init,
	.stawt       = sd_stawt,
	.stop0       = sd_stop0,
	.pkt_scan    = sd_pkt_scan,
	.dq_cawwback = sd_cawwback,
};

/*=========================== sub-dwivew image sizes =======================*/

static stwuct v4w2_pix_fowmat mi2020_mode[] = {
	{ 640,  480, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	},
	{ 800,  598, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 800,
		.sizeimage = 800 * 598,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	},
	{1280, 1024, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1280,
		.sizeimage = 1280 * 1024,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2
	},
	{1600, 1198, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1600,
		.sizeimage = 1600 * 1198,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 3
	},
};

static stwuct v4w2_pix_fowmat ov2640_mode[] = {
	{ 640,  480, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	},
	{ 800,  600, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 800,
		.sizeimage = 800 * 600,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	},
	{1280,  960, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1280,
		.sizeimage = 1280 * 960,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2
	},
	{1600, 1200, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1600,
		.sizeimage = 1600 * 1200,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 3
	},
};

static stwuct v4w2_pix_fowmat mi1320_mode[] = {
	{ 640,  480, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	},
	{ 800,  600, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 800,
		.sizeimage = 800 * 600,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	},
	{1280,  960, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1280,
		.sizeimage = 1280 * 960,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2
	},
};

static stwuct v4w2_pix_fowmat ov9655_mode[] = {
	{ 640,  480, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 640,
		.sizeimage = 640 * 480,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	},
	{1280,  960, V4W2_PIX_FMT_SGBWG8, V4W2_FIEWD_NONE,
		.bytespewwine = 1280,
		.sizeimage = 1280 * 960,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	},
};

/*========================= sud-dwivew functions ===========================*/

/* This function is cawwed at pwobe time */
static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct cam *cam;
	u16 vendow_id, pwoduct_id;

	/* Get USB VendowID and PwoductID */
	vendow_id  = id->idVendow;
	pwoduct_id = id->idPwoduct;

	sd->nbWightUp = 1;
	sd->nbIm = -1;

	sd->sensow = 0xff;
	if (stwcmp(sensow, "MI1320") == 0)
		sd->sensow = ID_MI1320;
	ewse if (stwcmp(sensow, "OV2640") == 0)
		sd->sensow = ID_OV2640;
	ewse if (stwcmp(sensow, "OV9655") == 0)
		sd->sensow = ID_OV9655;
	ewse if (stwcmp(sensow, "MI2020") == 0)
		sd->sensow = ID_MI2020;

	/* Get sensow and set the suitabwe init/stawt/../stop functions */
	if (gw860_guess_sensow(gspca_dev, vendow_id, pwoduct_id) == -1)
		wetuwn -1;

	cam = &gspca_dev->cam;

	switch (sd->sensow) {
	case ID_MI1320:
		gspca_dev->sd_desc = &sd_desc_mi1320;
		cam->cam_mode = mi1320_mode;
		cam->nmodes = AWWAY_SIZE(mi1320_mode);
		dev_init_settings   = mi1320_init_settings;
		bweak;

	case ID_MI2020:
		gspca_dev->sd_desc = &sd_desc_mi2020;
		cam->cam_mode = mi2020_mode;
		cam->nmodes = AWWAY_SIZE(mi2020_mode);
		dev_init_settings   = mi2020_init_settings;
		bweak;

	case ID_OV2640:
		gspca_dev->sd_desc = &sd_desc_ov2640;
		cam->cam_mode = ov2640_mode;
		cam->nmodes = AWWAY_SIZE(ov2640_mode);
		dev_init_settings   = ov2640_init_settings;
		bweak;

	case ID_OV9655:
		gspca_dev->sd_desc = &sd_desc_ov9655;
		cam->cam_mode = ov9655_mode;
		cam->nmodes = AWWAY_SIZE(ov9655_mode);
		dev_init_settings   = ov9655_init_settings;
		bweak;
	}

	dev_init_settings(gspca_dev);
	if (AC50Hz != 0xff)
		((stwuct sd *) gspca_dev)->vcuw.AC50Hz = AC50Hz;

	wetuwn 0;
}

/* This function is cawwed at pwobe time aftew sd_config */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn sd->dev_init_at_stawtup(gspca_dev);
}

/* This function is cawwed befowe to choose the awt setting */
static int sd_isoc_init(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn sd->dev_configuwe_awt(gspca_dev);
}

/* This function is cawwed to stawt the webcam */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	wetuwn sd->dev_init_pwe_awt(gspca_dev);
}

/* This function is cawwed to stop the webcam */
static void sd_stop0(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (!sd->gspca_dev.pwesent)
		wetuwn;

	wetuwn sd->dev_post_unset_awt(gspca_dev);
}

/* This function is cawwed when an image is being weceived */
static void sd_pkt_scan(stwuct gspca_dev *gspca_dev,
			u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	static s32 nSkipped;

	s32 mode = (s32) gspca_dev->cuww_mode;
	s32 nToSkip =
		sd->swapWB * (gspca_dev->cam.cam_mode[mode].bytespewwine + 1);

	/* Test onwy against 0202h, so endianness does not mattew */
	switch (*(s16 *) data) {
	case 0x0202:		/* End of fwame, stawt a new one */
		gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);
		nSkipped = 0;
		if (sd->nbIm >= 0 && sd->nbIm < 10)
			sd->nbIm++;
		gspca_fwame_add(gspca_dev, FIWST_PACKET, NUWW, 0);
		bweak;

	defauwt:
		data += 2;
		wen  -= 2;
		if (nSkipped + wen <= nToSkip)
			nSkipped += wen;
		ewse {
			if (nSkipped < nToSkip && nSkipped + wen > nToSkip) {
				data += nToSkip - nSkipped;
				wen  -= nToSkip - nSkipped;
				nSkipped = nToSkip + 1;
			}
			gspca_fwame_add(gspca_dev,
				INTEW_PACKET, data, wen);
		}
		bweak;
	}
}

/* This function is cawwed when an image has been wead */
/* This function is used to monitow webcam owientation */
static void sd_cawwback(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	if (!_OV9655_) {
		u8 state;
		u8 upsideDown;

		/* Pwobe sensow owientation */
		ctww_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, (void *)&state);

		/* C8/40 means upside-down (wooking backwawds) */
		/* D8/50 means wight-up (wooking onwawds) */
		upsideDown = (state == 0xc8 || state == 0x40);

		if (upsideDown && sd->nbWightUp > -4) {
			if (sd->nbWightUp > 0)
				sd->nbWightUp = 0;
			if (sd->nbWightUp == -3) {
				sd->miwwowMask = 1;
				sd->waitSet = 1;
			}
			sd->nbWightUp--;
		}
		if (!upsideDown && sd->nbWightUp < 4) {
			if (sd->nbWightUp  < 0)
				sd->nbWightUp = 0;
			if (sd->nbWightUp == 3) {
				sd->miwwowMask = 0;
				sd->waitSet = 1;
			}
			sd->nbWightUp++;
		}
	}

	if (sd->waitSet)
		sd->dev_camewa_settings(gspca_dev);
}

/*=================== USB dwivew stwuctuwe initiawisation ==================*/

static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x05e3, 0x0503)},
	{USB_DEVICE(0x05e3, 0xf191)},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

static int sd_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id,
			&sd_desc_mi1320, sizeof(stwuct sd), THIS_MODUWE);
}

static void sd_disconnect(stwuct usb_intewface *intf)
{
	gspca_disconnect(intf);
}

static stwuct usb_dwivew sd_dwivew = {
	.name       = MODUWE_NAME,
	.id_tabwe   = device_tabwe,
	.pwobe      = sd_pwobe,
	.disconnect = sd_disconnect,
#ifdef CONFIG_PM
	.suspend    = gspca_suspend,
	.wesume     = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
};

/*====================== Init and Exit moduwe functions ====================*/

moduwe_usb_dwivew(sd_dwivew);

/*==========================================================================*/

int gw860_WTx(stwuct gspca_dev *gspca_dev,
		unsigned chaw pwef, u32 weq, u16 vaw, u16 index,
		s32 wen, void *pdata)
{
	stwuct usb_device *udev = gspca_dev->dev;
	s32 w = 0;

	if (pwef == 0x40) { /* Send */
		if (wen > 0) {
			memcpy(gspca_dev->usb_buf, pdata, wen);
			w = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
					weq, pwef, vaw, index,
					gspca_dev->usb_buf,
					wen, 400 + 200 * (wen > 1));
		} ewse {
			w = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
					weq, pwef, vaw, index, NUWW, wen, 400);
		}
	} ewse { /* Weceive */
		if (wen > 0) {
			w = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
					weq, pwef, vaw, index,
					gspca_dev->usb_buf,
					wen, 400 + 200 * (wen > 1));
			memcpy(pdata, gspca_dev->usb_buf, wen);
		} ewse {
			gspca_eww(gspca_dev, "zewo-wength wead wequest\n");
			w = -EINVAW;
		}
	}

	if (w < 0)
		pw_eww("ctww twansfew faiwed %4d [p%02x w%d v%04x i%04x wen%d]\n",
		       w, pwef, weq, vaw, index, wen);
	ewse if (wen > 1 && w < wen)
		gspca_eww(gspca_dev, "showt ctww twansfew %d/%d\n", w, wen);

	msweep(1);

	wetuwn w;
}

int fetch_vawidx(stwuct gspca_dev *gspca_dev, stwuct vawidx *tbw, int wen)
{
	int n;

	fow (n = 0; n < wen; n++) {
		if (tbw[n].idx != 0xffff)
			ctww_out(gspca_dev, 0x40, 1, tbw[n].vaw,
					tbw[n].idx, 0, NUWW);
		ewse if (tbw[n].vaw == 0xffff)
			bweak;
		ewse
			msweep(tbw[n].vaw);
	}
	wetuwn n;
}

int keep_on_fetching_vawidx(stwuct gspca_dev *gspca_dev, stwuct vawidx *tbw,
				int wen, int n)
{
	whiwe (++n < wen) {
		if (tbw[n].idx != 0xffff)
			ctww_out(gspca_dev, 0x40, 1, tbw[n].vaw, tbw[n].idx,
					0, NUWW);
		ewse if (tbw[n].vaw == 0xffff)
			bweak;
		ewse
			msweep(tbw[n].vaw);
	}
	wetuwn n;
}

void fetch_idxdata(stwuct gspca_dev *gspca_dev, stwuct idxdata *tbw, int wen)
{
	int n;

	fow (n = 0; n < wen; n++) {
		if (memcmp(tbw[n].data, "\xff\xff\xff", 3) != 0)
			ctww_out(gspca_dev, 0x40, 3, 0x7a00, tbw[n].idx,
					3, tbw[n].data);
		ewse
			msweep(tbw[n].idx);
	}
}

static int gw860_guess_sensow(stwuct gspca_dev *gspca_dev,
				u16 vendow_id, u16 pwoduct_id)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 pwobe, nb26, nb96, nOV, ntwy;

	if (pwoduct_id == 0xf191)
		sd->sensow = ID_MI1320;

	if (sd->sensow == 0xff) {
		ctww_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &pwobe);
		ctww_in(gspca_dev, 0xc0, 2, 0x0000, 0x0004, 1, &pwobe);

		ctww_out(gspca_dev, 0x40, 1, 0x0000, 0x0000, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x0010, 0x0010, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x0008, 0x00c0, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x0001, 0x00c1, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x0001, 0x00c2, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x0020, 0x0006, 0, NUWW);
		msweep(3);
		ctww_out(gspca_dev, 0x40, 1, 0x006a, 0x000d, 0, NUWW);
		msweep(56);

		gspca_dbg(gspca_dev, D_PWOBE, "pwobing fow sensow MI2020 ow OVXXXX\n");
		nOV = 0;
		fow (ntwy = 0; ntwy < 4; ntwy++) {
			ctww_out(gspca_dev, 0x40, 1, 0x0040, 0x0000, 0, NUWW);
			msweep(3);
			ctww_out(gspca_dev, 0x40, 1, 0x0063, 0x0006, 0, NUWW);
			msweep(3);
			ctww_out(gspca_dev, 0x40, 1, 0x7a00, 0x8030, 0, NUWW);
			msweep(10);
			ctww_in(gspca_dev, 0xc0, 2, 0x7a00, 0x8030, 1, &pwobe);
			gspca_dbg(gspca_dev, D_PWOBE, "pwobe=0x%02x\n", pwobe);
			if (pwobe == 0xff)
				nOV++;
		}

		if (nOV) {
			gspca_dbg(gspca_dev, D_PWOBE, "0xff -> OVXXXX\n");
			gspca_dbg(gspca_dev, D_PWOBE, "pwobing fow sensow OV2640 ow OV9655");

			nb26 = nb96 = 0;
			fow (ntwy = 0; ntwy < 4; ntwy++) {
				ctww_out(gspca_dev, 0x40, 1, 0x0040, 0x0000,
						0, NUWW);
				msweep(3);
				ctww_out(gspca_dev, 0x40, 1, 0x6000, 0x800a,
						0, NUWW);
				msweep(10);

				/* Wait fow 26(OV2640) ow 96(OV9655) */
				ctww_in(gspca_dev, 0xc0, 2, 0x6000, 0x800a,
						1, &pwobe);

				if (pwobe == 0x26 || pwobe == 0x40) {
					gspca_dbg(gspca_dev, D_PWOBE,
						  "pwobe=0x%02x -> OV2640\n",
						  pwobe);
					sd->sensow = ID_OV2640;
					nb26 += 4;
					bweak;
				}
				if (pwobe == 0x96 || pwobe == 0x55) {
					gspca_dbg(gspca_dev, D_PWOBE,
						  "pwobe=0x%02x -> OV9655\n",
						  pwobe);
					sd->sensow = ID_OV9655;
					nb96 += 4;
					bweak;
				}
				gspca_dbg(gspca_dev, D_PWOBE, "pwobe=0x%02x\n",
					  pwobe);
				if (pwobe == 0x00)
					nb26++;
				if (pwobe == 0xff)
					nb96++;
				msweep(3);
			}
			if (nb26 < 4 && nb96 < 4)
				wetuwn -1;
		} ewse {
			gspca_dbg(gspca_dev, D_PWOBE, "Not any 0xff -> MI2020\n");
			sd->sensow = ID_MI2020;
		}
	}

	if (_MI1320_) {
		gspca_dbg(gspca_dev, D_PWOBE, "05e3:f191 sensow MI1320 (1.3M)\n");
	} ewse if (_MI2020_) {
		gspca_dbg(gspca_dev, D_PWOBE, "05e3:0503 sensow MI2020 (2.0M)\n");
	} ewse if (_OV9655_) {
		gspca_dbg(gspca_dev, D_PWOBE, "05e3:0503 sensow OV9655 (1.3M)\n");
	} ewse if (_OV2640_) {
		gspca_dbg(gspca_dev, D_PWOBE, "05e3:0503 sensow OV2640 (2.0M)\n");
	} ewse {
		gspca_dbg(gspca_dev, D_PWOBE, "***** Unknown sensow *****\n");
		wetuwn -1;
	}

	wetuwn 0;
}
