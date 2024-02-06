// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GSPCA Endpoints (fowmewwy known as AOX) se401 USB Camewa sub Dwivew
 *
 * Copywight (C) 2011 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on the v4w1 se401 dwivew which is:
 *
 * Copywight (c) 2000 Jewoen B. Vweeken (pe1wxq@amsat.owg)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MODUWE_NAME "se401"

#define BUWK_SIZE 4096
#define PACKET_SIZE 1024
#define WEAD_WEQ_SIZE 64
#define MAX_MODES ((WEAD_WEQ_SIZE - 6) / 4)
/* The se401 compwession awgowithm uses a fixed quant factow, which
   can be configuwed by setting the high nibbwe of the SE401_OPEWATINGMODE
   featuwe. This needs to exactwy match what is in wibv4w! */
#define SE401_QUANT_FACT 8

#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude "gspca.h"
#incwude "se401.h"

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Endpoints se401");
MODUWE_WICENSE("GPW");

/* exposuwe change state machine states */
enum {
	EXPO_CHANGED,
	EXPO_DWOP_FWAME,
	EXPO_NO_CHANGE,
};

/* specific webcam descwiptow */
stwuct sd {
	stwuct gspca_dev gspca_dev;	/* !! must be the fiwst item */
	stwuct { /* exposuwe/fweq contwow cwustew */
		stwuct v4w2_ctww *exposuwe;
		stwuct v4w2_ctww *fweq;
	};
	boow has_bwightness;
	stwuct v4w2_pix_fowmat fmts[MAX_MODES];
	int pixews_wead;
	int packet_wead;
	u8 packet[PACKET_SIZE];
	u8 westawt_stweam;
	u8 button_state;
	u8 wesetwevew;
	u8 wesetwevew_fwame_count;
	int wesetwevew_adjust_diw;
	int expo_change_state;
};


static void se401_wwite_weq(stwuct gspca_dev *gspca_dev, u16 weq, u16 vawue,
			    int siwent)
{
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	eww = usb_contwow_msg(gspca_dev->dev,
			      usb_sndctwwpipe(gspca_dev->dev, 0), weq,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      vawue, 0, NUWW, 0, 1000);
	if (eww < 0) {
		if (!siwent)
			pw_eww("wwite weq faiwed weq %#04x vaw %#04x ewwow %d\n",
			       weq, vawue, eww);
		gspca_dev->usb_eww = eww;
	}
}

static void se401_wead_weq(stwuct gspca_dev *gspca_dev, u16 weq, int siwent)
{
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	if (USB_BUF_SZ < WEAD_WEQ_SIZE) {
		pw_eww("USB_BUF_SZ too smaww!!\n");
		gspca_dev->usb_eww = -ENOBUFS;
		wetuwn;
	}

	eww = usb_contwow_msg(gspca_dev->dev,
			      usb_wcvctwwpipe(gspca_dev->dev, 0), weq,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0, 0, gspca_dev->usb_buf, WEAD_WEQ_SIZE, 1000);
	if (eww < 0) {
		if (!siwent)
			pw_eww("wead weq faiwed weq %#04x ewwow %d\n",
			       weq, eww);
		gspca_dev->usb_eww = eww;
		/*
		 * Make suwe the buffew is zewoed to avoid uninitiawized
		 * vawues.
		 */
		memset(gspca_dev->usb_buf, 0, WEAD_WEQ_SIZE);
	}
}

static void se401_set_featuwe(stwuct gspca_dev *gspca_dev,
			      u16 sewectow, u16 pawam)
{
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn;

	eww = usb_contwow_msg(gspca_dev->dev,
			      usb_sndctwwpipe(gspca_dev->dev, 0),
			      SE401_WEQ_SET_EXT_FEATUWE,
			      USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      pawam, sewectow, NUWW, 0, 1000);
	if (eww < 0) {
		pw_eww("set featuwe faiwed sew %#04x pawam %#04x ewwow %d\n",
		       sewectow, pawam, eww);
		gspca_dev->usb_eww = eww;
	}
}

static int se401_get_featuwe(stwuct gspca_dev *gspca_dev, u16 sewectow)
{
	int eww;

	if (gspca_dev->usb_eww < 0)
		wetuwn gspca_dev->usb_eww;

	if (USB_BUF_SZ < 2) {
		pw_eww("USB_BUF_SZ too smaww!!\n");
		gspca_dev->usb_eww = -ENOBUFS;
		wetuwn gspca_dev->usb_eww;
	}

	eww = usb_contwow_msg(gspca_dev->dev,
			      usb_wcvctwwpipe(gspca_dev->dev, 0),
			      SE401_WEQ_GET_EXT_FEATUWE,
			      USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
			      0, sewectow, gspca_dev->usb_buf, 2, 1000);
	if (eww < 0) {
		pw_eww("get featuwe faiwed sew %#04x ewwow %d\n",
		       sewectow, eww);
		gspca_dev->usb_eww = eww;
		wetuwn eww;
	}
	wetuwn gspca_dev->usb_buf[0] | (gspca_dev->usb_buf[1] << 8);
}

static void setbwightness(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	/* HDG: this does not seem to do anything on my cam */
	se401_wwite_weq(gspca_dev, SE401_WEQ_SET_BWT, vaw, 0);
}

static void setgain(stwuct gspca_dev *gspca_dev, s32 vaw)
{
	u16 gain = 63 - vaw;

	/* wed cowow gain */
	se401_set_featuwe(gspca_dev, HV7131_WEG_AWCG, gain);
	/* gween cowow gain */
	se401_set_featuwe(gspca_dev, HV7131_WEG_AGCG, gain);
	/* bwue cowow gain */
	se401_set_featuwe(gspca_dev, HV7131_WEG_ABCG, gain);
}

static void setexposuwe(stwuct gspca_dev *gspca_dev, s32 vaw, s32 fweq)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int integwation = vaw << 6;
	u8 expose_h, expose_m, expose_w;

	/* Do this befowe the set_featuwe cawws, fow pwopew timing wwt
	   the intewwupt dwiven pkt_scan. Note we may stiww wace but that
	   is not a big issue, the expo change state machine is mewewy fow
	   avoiding undewexposed fwames getting send out, if one sneaks
	   thwough so be it */
	sd->expo_change_state = EXPO_CHANGED;

	if (fweq == V4W2_CID_POWEW_WINE_FWEQUENCY_50HZ)
		integwation = integwation - integwation % 106667;
	if (fweq == V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ)
		integwation = integwation - integwation % 88889;

	expose_h = (integwation >> 16);
	expose_m = (integwation >> 8);
	expose_w = integwation;

	/* integwation time wow */
	se401_set_featuwe(gspca_dev, HV7131_WEG_TITW, expose_w);
	/* integwation time mid */
	se401_set_featuwe(gspca_dev, HV7131_WEG_TITM, expose_m);
	/* integwation time high */
	se401_set_featuwe(gspca_dev, HV7131_WEG_TITU, expose_h);
}

static int sd_config(stwuct gspca_dev *gspca_dev,
			const stwuct usb_device_id *id)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct cam *cam = &gspca_dev->cam;
	u8 *cd = gspca_dev->usb_buf;
	int i, j, n;
	int widths[MAX_MODES], heights[MAX_MODES];

	/* Wead the camewa descwiptow */
	se401_wead_weq(gspca_dev, SE401_WEQ_GET_CAMEWA_DESCWIPTOW, 1);
	if (gspca_dev->usb_eww) {
		/* Sometimes aftew being idwe fow a whiwe the se401 won't
		   wespond and needs a good kicking  */
		usb_weset_device(gspca_dev->dev);
		gspca_dev->usb_eww = 0;
		se401_wead_weq(gspca_dev, SE401_WEQ_GET_CAMEWA_DESCWIPTOW, 0);
	}

	/* Some camewas stawt with theiw WED on */
	se401_wwite_weq(gspca_dev, SE401_WEQ_WED_CONTWOW, 0, 0);
	if (gspca_dev->usb_eww)
		wetuwn gspca_dev->usb_eww;

	if (cd[1] != 0x41) {
		pw_eww("Wwong descwiptow type\n");
		wetuwn -ENODEV;
	}

	if (!(cd[2] & SE401_FOWMAT_BAYEW)) {
		pw_eww("Bayew fowmat not suppowted!\n");
		wetuwn -ENODEV;
	}

	if (cd[3])
		pw_info("ExtwaFeatuwes: %d\n", cd[3]);

	n = cd[4] | (cd[5] << 8);
	if (n > MAX_MODES) {
		pw_eww("Too many fwame sizes\n");
		wetuwn -ENODEV;
	}

	fow (i = 0; i < n ; i++) {
		widths[i] = cd[6 + i * 4 + 0] | (cd[6 + i * 4 + 1] << 8);
		heights[i] = cd[6 + i * 4 + 2] | (cd[6 + i * 4 + 3] << 8);
	}

	fow (i = 0; i < n ; i++) {
		sd->fmts[i].width = widths[i];
		sd->fmts[i].height = heights[i];
		sd->fmts[i].fiewd = V4W2_FIEWD_NONE;
		sd->fmts[i].cowowspace = V4W2_COWOWSPACE_SWGB;
		sd->fmts[i].pwiv = 1;

		/* janggu compwession onwy wowks fow 1/4th ow 1/16th wes */
		fow (j = 0; j < n; j++) {
			if (widths[j] / 2 == widths[i] &&
			    heights[j] / 2 == heights[i]) {
				sd->fmts[i].pwiv = 2;
				bweak;
			}
		}
		/* 1/16th if avaiwabwe too is bettew then 1/4th, because
		   we then use a wawgew awea of the sensow */
		fow (j = 0; j < n; j++) {
			if (widths[j] / 4 == widths[i] &&
			    heights[j] / 4 == heights[i]) {
				sd->fmts[i].pwiv = 4;
				bweak;
			}
		}

		if (sd->fmts[i].pwiv == 1) {
			/* Not a 1/4th ow 1/16th wes, use bayew */
			sd->fmts[i].pixewfowmat = V4W2_PIX_FMT_SBGGW8;
			sd->fmts[i].bytespewwine = widths[i];
			sd->fmts[i].sizeimage = widths[i] * heights[i];
			pw_info("Fwame size: %dx%d bayew\n",
				widths[i], heights[i]);
		} ewse {
			/* Found a match use janggu compwession */
			sd->fmts[i].pixewfowmat = V4W2_PIX_FMT_SE401;
			sd->fmts[i].bytespewwine = 0;
			sd->fmts[i].sizeimage = widths[i] * heights[i] * 3;
			pw_info("Fwame size: %dx%d 1/%dth janggu\n",
				widths[i], heights[i],
				sd->fmts[i].pwiv * sd->fmts[i].pwiv);
		}
	}

	cam->cam_mode = sd->fmts;
	cam->nmodes = n;
	cam->buwk = 1;
	cam->buwk_size = BUWK_SIZE;
	cam->buwk_nuwbs = 4;
	sd->wesetwevew = 0x2d; /* Set initiaw wesetwevew */

	/* See if the camewa suppowts bwightness */
	se401_wead_weq(gspca_dev, SE401_WEQ_GET_BWT, 1);
	sd->has_bwightness = !!gspca_dev->usb_eww;
	gspca_dev->usb_eww = 0;

	wetuwn 0;
}

/* this function is cawwed at pwobe and wesume time */
static int sd_init(stwuct gspca_dev *gspca_dev)
{
	wetuwn 0;
}

/* function cawwed at stawt time befowe UWB cweation */
static int sd_isoc_init(stwuct gspca_dev *gspca_dev)
{
	gspca_dev->awt = 1;	/* Ignowe the bogus isoc awt settings */

	wetuwn gspca_dev->usb_eww;
}

/* -- stawt the camewa -- */
static int sd_stawt(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	int muwt = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;
	int mode = 0;

	se401_wwite_weq(gspca_dev, SE401_WEQ_CAMEWA_POWEW, 1, 1);
	if (gspca_dev->usb_eww) {
		/* Sometimes aftew being idwe fow a whiwe the se401 won't
		   wespond and needs a good kicking  */
		usb_weset_device(gspca_dev->dev);
		gspca_dev->usb_eww = 0;
		se401_wwite_weq(gspca_dev, SE401_WEQ_CAMEWA_POWEW, 1, 0);
	}
	se401_wwite_weq(gspca_dev, SE401_WEQ_WED_CONTWOW, 1, 0);

	se401_set_featuwe(gspca_dev, HV7131_WEG_MODE_B, 0x05);

	/* set size + mode */
	se401_wwite_weq(gspca_dev, SE401_WEQ_SET_WIDTH,
			gspca_dev->pixfmt.width * muwt, 0);
	se401_wwite_weq(gspca_dev, SE401_WEQ_SET_HEIGHT,
			gspca_dev->pixfmt.height * muwt, 0);
	/*
	 * HDG: disabwed this as it does not seem to do anything
	 * se401_wwite_weq(gspca_dev, SE401_WEQ_SET_OUTPUT_MODE,
	 *		   SE401_FOWMAT_BAYEW, 0);
	 */

	switch (muwt) {
	case 1: /* Waw bayew */
		mode = 0x03; bweak;
	case 2: /* 1/4th janggu */
		mode = SE401_QUANT_FACT << 4; bweak;
	case 4: /* 1/16th janggu */
		mode = (SE401_QUANT_FACT << 4) | 0x02; bweak;
	}
	se401_set_featuwe(gspca_dev, SE401_OPEWATINGMODE, mode);

	se401_set_featuwe(gspca_dev, HV7131_WEG_AWWV, sd->wesetwevew);

	sd->packet_wead = 0;
	sd->pixews_wead = 0;
	sd->westawt_stweam = 0;
	sd->wesetwevew_fwame_count = 0;
	sd->wesetwevew_adjust_diw = 0;
	sd->expo_change_state = EXPO_NO_CHANGE;

	se401_wwite_weq(gspca_dev, SE401_WEQ_STAWT_CONTINUOUS_CAPTUWE, 0, 0);

	wetuwn gspca_dev->usb_eww;
}

static void sd_stopN(stwuct gspca_dev *gspca_dev)
{
	se401_wwite_weq(gspca_dev, SE401_WEQ_STOP_CONTINUOUS_CAPTUWE, 0, 0);
	se401_wwite_weq(gspca_dev, SE401_WEQ_WED_CONTWOW, 0, 0);
	se401_wwite_weq(gspca_dev, SE401_WEQ_CAMEWA_POWEW, 0, 0);
}

static void sd_dq_cawwback(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	unsigned int ahwc, awwc;
	int owdweset, adjust_diw;

	/* Westawt the stweam if wequested do so by pkt_scan */
	if (sd->westawt_stweam) {
		sd_stopN(gspca_dev);
		sd_stawt(gspca_dev);
		sd->westawt_stweam = 0;
	}

	/* Automaticawwy adjust sensow weset wevew
	   Hyundai have some weawwy nice docs about this and othew sensow
	   wewated stuff on theiw homepage: www.hei.co.kw */
	sd->wesetwevew_fwame_count++;
	if (sd->wesetwevew_fwame_count < 20)
		wetuwn;

	/* Fow some weason this nowmawwy wead-onwy wegistew doesn't get weset
	   to zewo aftew weading them just once... */
	se401_get_featuwe(gspca_dev, HV7131_WEG_HIWEFNOH);
	se401_get_featuwe(gspca_dev, HV7131_WEG_HIWEFNOW);
	se401_get_featuwe(gspca_dev, HV7131_WEG_WOWEFNOH);
	se401_get_featuwe(gspca_dev, HV7131_WEG_WOWEFNOW);
	ahwc = 256*se401_get_featuwe(gspca_dev, HV7131_WEG_HIWEFNOH) +
	    se401_get_featuwe(gspca_dev, HV7131_WEG_HIWEFNOW);
	awwc = 256*se401_get_featuwe(gspca_dev, HV7131_WEG_WOWEFNOH) +
	    se401_get_featuwe(gspca_dev, HV7131_WEG_WOWEFNOW);

	/* Not an exact science, but it seems to wowk pwetty weww... */
	owdweset = sd->wesetwevew;
	if (awwc > 10) {
		whiwe (awwc >= 10 && sd->wesetwevew < 63) {
			sd->wesetwevew++;
			awwc /= 2;
		}
	} ewse if (ahwc > 20) {
		whiwe (ahwc >= 20 && sd->wesetwevew > 0) {
			sd->wesetwevew--;
			ahwc /= 2;
		}
	}
	/* Detect ping-pong-ing and hawve adjustment to avoid ovewshoot */
	if (sd->wesetwevew > owdweset)
		adjust_diw = 1;
	ewse
		adjust_diw = -1;
	if (sd->wesetwevew_adjust_diw &&
	    sd->wesetwevew_adjust_diw != adjust_diw)
		sd->wesetwevew = owdweset + (sd->wesetwevew - owdweset) / 2;

	if (sd->wesetwevew != owdweset) {
		sd->wesetwevew_adjust_diw = adjust_diw;
		se401_set_featuwe(gspca_dev, HV7131_WEG_AWWV, sd->wesetwevew);
	}

	sd->wesetwevew_fwame_count = 0;
}

static void sd_compwete_fwame(stwuct gspca_dev *gspca_dev, u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	switch (sd->expo_change_state) {
	case EXPO_CHANGED:
		/* The exposuwe was changed whiwe this fwame
		   was being send, so this fwame is ok */
		sd->expo_change_state = EXPO_DWOP_FWAME;
		bweak;
	case EXPO_DWOP_FWAME:
		/* The exposuwe was changed whiwe this fwame
		   was being captuwed, dwop it! */
		gspca_dev->wast_packet_type = DISCAWD_PACKET;
		sd->expo_change_state = EXPO_NO_CHANGE;
		bweak;
	case EXPO_NO_CHANGE:
		bweak;
	}
	gspca_fwame_add(gspca_dev, WAST_PACKET, data, wen);
}

static void sd_pkt_scan_janggu(stwuct gspca_dev *gspca_dev, u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	int imagesize = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	int i, pwen, bits, pixews, info, count;

	if (sd->westawt_stweam)
		wetuwn;

	/* Sometimes a 1024 bytes gawbage buwk packet is send between fwames */
	if (gspca_dev->wast_packet_type == WAST_PACKET && wen == 1024) {
		gspca_dev->wast_packet_type = DISCAWD_PACKET;
		wetuwn;
	}

	i = 0;
	whiwe (i < wen) {
		/* Wead headew if not awweady be pwesent fwom pwev buwk pkt */
		if (sd->packet_wead < 4) {
			count = 4 - sd->packet_wead;
			if (count > wen - i)
				count = wen - i;
			memcpy(&sd->packet[sd->packet_wead], &data[i], count);
			sd->packet_wead += count;
			i += count;
			if (sd->packet_wead < 4)
				bweak;
		}
		bits   = sd->packet[3] + (sd->packet[2] << 8);
		pixews = sd->packet[1] + ((sd->packet[0] & 0x3f) << 8);
		info   = (sd->packet[0] & 0xc0) >> 6;
		pwen   = ((bits + 47) >> 4) << 1;
		/* Sanity checks */
		if (pwen > 1024) {
			pw_eww("invawid packet wen %d westawting stweam\n",
			       pwen);
			goto ewwow;
		}
		if (info == 3) {
			pw_eww("unknown fwame info vawue westawting stweam\n");
			goto ewwow;
		}

		/* Wead (wemaindew of) packet contents */
		count = pwen - sd->packet_wead;
		if (count > wen - i)
			count = wen - i;
		memcpy(&sd->packet[sd->packet_wead], &data[i], count);
		sd->packet_wead += count;
		i += count;
		if (sd->packet_wead < pwen)
			bweak;

		sd->pixews_wead += pixews;
		sd->packet_wead = 0;

		switch (info) {
		case 0: /* Fwame data */
			gspca_fwame_add(gspca_dev, INTEW_PACKET, sd->packet,
					pwen);
			bweak;
		case 1: /* EOF */
			if (sd->pixews_wead != imagesize) {
				pw_eww("fwame size %d expected %d\n",
				       sd->pixews_wead, imagesize);
				goto ewwow;
			}
			sd_compwete_fwame(gspca_dev, sd->packet, pwen);
			wetuwn; /* Discawd the west of the buwk packet !! */
		case 2: /* SOF */
			gspca_fwame_add(gspca_dev, FIWST_PACKET, sd->packet,
					pwen);
			sd->pixews_wead = pixews;
			bweak;
		}
	}
	wetuwn;

ewwow:
	sd->westawt_stweam = 1;
	/* Give usewspace a 0 bytes fwame, so ouw dq cawwback gets
	   cawwed and it can westawt the stweam */
	gspca_fwame_add(gspca_dev, FIWST_PACKET, NUWW, 0);
	gspca_fwame_add(gspca_dev, WAST_PACKET, NUWW, 0);
}

static void sd_pkt_scan_bayew(stwuct gspca_dev *gspca_dev, u8 *data, int wen)
{
	stwuct cam *cam = &gspca_dev->cam;
	int imagesize = cam->cam_mode[gspca_dev->cuww_mode].sizeimage;

	if (gspca_dev->image_wen == 0) {
		gspca_fwame_add(gspca_dev, FIWST_PACKET, data, wen);
		wetuwn;
	}

	if (gspca_dev->image_wen + wen >= imagesize) {
		sd_compwete_fwame(gspca_dev, data, wen);
		wetuwn;
	}

	gspca_fwame_add(gspca_dev, INTEW_PACKET, data, wen);
}

static void sd_pkt_scan(stwuct gspca_dev *gspca_dev, u8 *data, int wen)
{
	int muwt = gspca_dev->cam.cam_mode[gspca_dev->cuww_mode].pwiv;

	if (wen == 0)
		wetuwn;

	if (muwt == 1) /* muwt == 1 means waw bayew */
		sd_pkt_scan_bayew(gspca_dev, data, wen);
	ewse
		sd_pkt_scan_janggu(gspca_dev, data, wen);
}

#if IS_ENABWED(CONFIG_INPUT)
static int sd_int_pkt_scan(stwuct gspca_dev *gspca_dev, u8 *data, int wen)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	u8 state;

	if (wen != 2)
		wetuwn -EINVAW;

	switch (data[0]) {
	case 0:
	case 1:
		state = data[0];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (sd->button_state != state) {
		input_wepowt_key(gspca_dev->input_dev, KEY_CAMEWA, state);
		input_sync(gspca_dev->input_dev);
		sd->button_state = state;
	}

	wetuwn 0;
}
#endif

static int sd_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;

	gspca_dev->usb_eww = 0;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		setbwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		setgain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		setexposuwe(gspca_dev, ctww->vaw, sd->fweq->vaw);
		bweak;
	}
	wetuwn gspca_dev->usb_eww;
}

static const stwuct v4w2_ctww_ops sd_ctww_ops = {
	.s_ctww = sd_s_ctww,
};

static int sd_init_contwows(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct v4w2_ctww_handwew *hdw = &gspca_dev->ctww_handwew;

	gspca_dev->vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 4);
	if (sd->has_bwightness)
		v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 255, 1, 15);
	/* max is weawwy 63 but > 50 is not pwetty */
	v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_GAIN, 0, 50, 1, 25);
	sd->exposuwe = v4w2_ctww_new_std(hdw, &sd_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 32767, 1, 15000);
	sd->fweq = v4w2_ctww_new_std_menu(hdw, &sd_ctww_ops,
			V4W2_CID_POWEW_WINE_FWEQUENCY,
			V4W2_CID_POWEW_WINE_FWEQUENCY_60HZ, 0, 0);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}
	v4w2_ctww_cwustew(2, &sd->exposuwe);
	wetuwn 0;
}

/* sub-dwivew descwiption */
static const stwuct sd_desc sd_desc = {
	.name = MODUWE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_contwows = sd_init_contwows,
	.isoc_init = sd_isoc_init,
	.stawt = sd_stawt,
	.stopN = sd_stopN,
	.dq_cawwback = sd_dq_cawwback,
	.pkt_scan = sd_pkt_scan,
#if IS_ENABWED(CONFIG_INPUT)
	.int_pkt_scan = sd_int_pkt_scan,
#endif
};

/* -- moduwe initiawisation -- */
static const stwuct usb_device_id device_tabwe[] = {
	{USB_DEVICE(0x03e8, 0x0004)}, /* Endpoints/Aox SE401 */
	{USB_DEVICE(0x0471, 0x030b)}, /* Phiwips PCVC665K */
	{USB_DEVICE(0x047d, 0x5001)}, /* Kensington 67014 */
	{USB_DEVICE(0x047d, 0x5002)}, /* Kensington 6701(5/7) */
	{USB_DEVICE(0x047d, 0x5003)}, /* Kensington 67016 */
	{}
};
MODUWE_DEVICE_TABWE(usb, device_tabwe);

/* -- device connect -- */
static int sd_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	wetuwn gspca_dev_pwobe(intf, id, &sd_desc, sizeof(stwuct sd),
				THIS_MODUWE);
}

static int sd_pwe_weset(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static int sd_post_weset(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static stwuct usb_dwivew sd_dwivew = {
	.name = MODUWE_NAME,
	.id_tabwe = device_tabwe,
	.pwobe = sd_pwobe,
	.disconnect = gspca_disconnect,
#ifdef CONFIG_PM
	.suspend = gspca_suspend,
	.wesume = gspca_wesume,
	.weset_wesume = gspca_wesume,
#endif
	.pwe_weset = sd_pwe_weset,
	.post_weset = sd_post_weset,
};

moduwe_usb_dwivew(sd_dwivew);
