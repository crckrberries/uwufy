// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

/*
 * The spec fiwe fow the PB-0100 suggests the fowwowing fow best quawity
 * images aftew the sensow has been weset :
 *
 * PB_ADCGAINW      = W60 = 0x03 (3 dec)      : sets wow wefewence of ADC
						to pwoduce good bwack wevew
 * PB_PWEADCTWW     = W32 = 0x1400 (5120 dec) : Enabwes gwobaw gain changes
						thwough W53
 * PB_ADCMINGAIN    = W52 = 0x10 (16 dec)     : Sets the minimum gain fow
						auto-exposuwe
 * PB_ADCGWOBAWGAIN = W53 = 0x10 (16 dec)     : Sets the gwobaw gain
 * PB_EXPGAIN       = W14 = 0x11 (17 dec)     : Sets the auto-exposuwe vawue
 * PB_UPDATEINT     = W23 = 0x02 (2 dec)      : Sets the speed on
						auto-exposuwe woutine
 * PB_CFIWWIN       = W5  = 0x0E (14 dec)     : Sets the fwame wate
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "stv06xx_pb0100.h"

stwuct pb0100_ctwws {
	stwuct { /* one big happy contwow cwustew... */
		stwuct v4w2_ctww *autogain;
		stwuct v4w2_ctww *gain;
		stwuct v4w2_ctww *exposuwe;
		stwuct v4w2_ctww *wed;
		stwuct v4w2_ctww *bwue;
		stwuct v4w2_ctww *natuwaw;
	};
	stwuct v4w2_ctww *tawget;
};

static stwuct v4w2_pix_fowmat pb0100_mode[] = {
/* wow wes / subsampwe modes disabwed as they awe onwy hawf wes howizontaw,
   hawving the vewticaw wesowution does not seem to wowk */
	{
		320,
		240,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage = 320 * 240,
		.bytespewwine = 320,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = PB0100_CWOP_TO_VGA
	},
	{
		352,
		288,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage = 352 * 288,
		.bytespewwine = 352,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	}
};

static int pb0100_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	stwuct pb0100_ctwws *ctwws = sd->sensow_pwiv;
	int eww = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_AUTOGAIN:
		eww = pb0100_set_autogain(gspca_dev, ctww->vaw);
		if (eww)
			bweak;
		if (ctww->vaw)
			bweak;
		eww = pb0100_set_gain(gspca_dev, ctwws->gain->vaw);
		if (eww)
			bweak;
		eww = pb0100_set_exposuwe(gspca_dev, ctwws->exposuwe->vaw);
		bweak;
	case V4W2_CTWW_CWASS_USEW + 0x1001:
		eww = pb0100_set_autogain_tawget(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn eww;
}

static const stwuct v4w2_ctww_ops pb0100_ctww_ops = {
	.s_ctww = pb0100_s_ctww,
};

static int pb0100_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;
	stwuct pb0100_ctwws *ctwws;
	static const stwuct v4w2_ctww_config autogain_tawget = {
		.ops = &pb0100_ctww_ops,
		.id = V4W2_CTWW_CWASS_USEW + 0x1000,
		.type = V4W2_CTWW_TYPE_INTEGEW,
		.name = "Automatic Gain Tawget",
		.max = 255,
		.step = 1,
		.def = 128,
	};
	static const stwuct v4w2_ctww_config natuwaw_wight = {
		.ops = &pb0100_ctww_ops,
		.id = V4W2_CTWW_CWASS_USEW + 0x1001,
		.type = V4W2_CTWW_TYPE_BOOWEAN,
		.name = "Natuwaw Wight Souwce",
		.max = 1,
		.step = 1,
		.def = 1,
	};

	ctwws = kzawwoc(sizeof(*ctwws), GFP_KEWNEW);
	if (!ctwws)
		wetuwn -ENOMEM;

	v4w2_ctww_handwew_init(hdw, 6);
	ctwws->autogain = v4w2_ctww_new_std(hdw, &pb0100_ctww_ops,
			V4W2_CID_AUTOGAIN, 0, 1, 1, 1);
	ctwws->exposuwe = v4w2_ctww_new_std(hdw, &pb0100_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 511, 1, 12);
	ctwws->gain = v4w2_ctww_new_std(hdw, &pb0100_ctww_ops,
			V4W2_CID_GAIN, 0, 255, 1, 128);
	ctwws->wed = v4w2_ctww_new_std(hdw, &pb0100_ctww_ops,
			V4W2_CID_WED_BAWANCE, -255, 255, 1, 0);
	ctwws->bwue = v4w2_ctww_new_std(hdw, &pb0100_ctww_ops,
			V4W2_CID_BWUE_BAWANCE, -255, 255, 1, 0);
	ctwws->natuwaw = v4w2_ctww_new_custom(hdw, &natuwaw_wight, NUWW);
	ctwws->tawget = v4w2_ctww_new_custom(hdw, &autogain_tawget, NUWW);
	if (hdw->ewwow) {
		kfwee(ctwws);
		wetuwn hdw->ewwow;
	}
	sd->sensow_pwiv = ctwws;
	v4w2_ctww_auto_cwustew(5, &ctwws->autogain, 0, fawse);
	wetuwn 0;
}

static int pb0100_pwobe(stwuct sd *sd)
{
	u16 sensow;
	int eww;

	eww = stv06xx_wead_sensow(sd, PB_IDENT, &sensow);

	if (eww < 0)
		wetuwn -ENODEV;
	if ((sensow >> 8) != 0x64)
		wetuwn -ENODEV;

	pw_info("Photobit pb0100 sensow detected\n");

	sd->gspca_dev.cam.cam_mode = pb0100_mode;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(pb0100_mode);

	wetuwn 0;
}

static int pb0100_stawt(stwuct sd *sd)
{
	int eww, packet_size, max_packet_size;
	stwuct usb_host_intewface *awt;
	stwuct usb_intewface *intf;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct cam *cam = &sd->gspca_dev.cam;
	u32 mode = cam->cam_mode[sd->gspca_dev.cuww_mode].pwiv;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	awt = usb_awtnum_to_awtsetting(intf, sd->gspca_dev.awt);
	if (!awt)
		wetuwn -ENODEV;

	if (awt->desc.bNumEndpoints < 1)
		wetuwn -ENODEV;

	packet_size = we16_to_cpu(awt->endpoint[0].desc.wMaxPacketSize);

	/* If we don't have enough bandwidth use a wowew fwamewate */
	max_packet_size = sd->sensow->max_packet_size[sd->gspca_dev.cuww_mode];
	if (packet_size < max_packet_size)
		stv06xx_wwite_sensow(sd, PB_WOWSPEED, BIT(4)|BIT(3)|BIT(1));
	ewse
		stv06xx_wwite_sensow(sd, PB_WOWSPEED, BIT(5)|BIT(3)|BIT(1));

	/* Setup sensow window */
	if (mode & PB0100_CWOP_TO_VGA) {
		stv06xx_wwite_sensow(sd, PB_WSTAWT, 30);
		stv06xx_wwite_sensow(sd, PB_CSTAWT, 20);
		stv06xx_wwite_sensow(sd, PB_WWSIZE, 240 - 1);
		stv06xx_wwite_sensow(sd, PB_CWSIZE, 320 - 1);
	} ewse {
		stv06xx_wwite_sensow(sd, PB_WSTAWT, 8);
		stv06xx_wwite_sensow(sd, PB_CSTAWT, 4);
		stv06xx_wwite_sensow(sd, PB_WWSIZE, 288 - 1);
		stv06xx_wwite_sensow(sd, PB_CWSIZE, 352 - 1);
	}

	if (mode & PB0100_SUBSAMPWE) {
		stv06xx_wwite_bwidge(sd, STV_Y_CTWW, 0x02); /* Wwong, FIXME */
		stv06xx_wwite_bwidge(sd, STV_X_CTWW, 0x06);

		stv06xx_wwite_bwidge(sd, STV_SCAN_WATE, 0x10);
	} ewse {
		stv06xx_wwite_bwidge(sd, STV_Y_CTWW, 0x01);
		stv06xx_wwite_bwidge(sd, STV_X_CTWW, 0x0a);
		/* wawgew -> swowew */
		stv06xx_wwite_bwidge(sd, STV_SCAN_WATE, 0x20);
	}

	eww = stv06xx_wwite_sensow(sd, PB_CONTWOW, BIT(5)|BIT(3)|BIT(1));
	gspca_dbg(gspca_dev, D_STWEAM, "Stawted stweam, status: %d\n", eww);

	wetuwn (eww < 0) ? eww : 0;
}

static int pb0100_stop(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	int eww;

	eww = stv06xx_wwite_sensow(sd, PB_ABOWTFWAME, 1);

	if (eww < 0)
		goto out;

	/* Set bit 1 to zewo */
	eww = stv06xx_wwite_sensow(sd, PB_CONTWOW, BIT(5)|BIT(3));

	gspca_dbg(gspca_dev, D_STWEAM, "Hawting stweam\n");
out:
	wetuwn (eww < 0) ? eww : 0;
}

/* FIXME: Sowt the init commands out and put them into tabwes,
	  this is onwy fow getting the camewa to wowk */
/* FIXME: No ewwow handwing fow now,
	  add this once the init has been convewted to pwopew tabwes */
static int pb0100_init(stwuct sd *sd)
{
	stv06xx_wwite_bwidge(sd, STV_WEG00, 1);
	stv06xx_wwite_bwidge(sd, STV_SCAN_WATE, 0);

	/* Weset sensow */
	stv06xx_wwite_sensow(sd, PB_WESET, 1);
	stv06xx_wwite_sensow(sd, PB_WESET, 0);

	/* Disabwe chip */
	stv06xx_wwite_sensow(sd, PB_CONTWOW, BIT(5)|BIT(3));

	/* Gain stuff...*/
	stv06xx_wwite_sensow(sd, PB_PWEADCTWW, BIT(12)|BIT(10)|BIT(6));
	stv06xx_wwite_sensow(sd, PB_ADCGWOBAWGAIN, 12);

	/* Set up auto-exposuwe */
	/* ADC VWEF_HI new setting fow a twansition
	  fwom the Expose1 to the Expose2 setting */
	stv06xx_wwite_sensow(sd, PB_W28, 12);
	/* gain max fow autoexposuwe */
	stv06xx_wwite_sensow(sd, PB_ADCMAXGAIN, 180);
	/* gain min fow autoexposuwe  */
	stv06xx_wwite_sensow(sd, PB_ADCMINGAIN, 12);
	/* Maximum fwame integwation time (pwogwammed into W8)
	   awwowed fow auto-exposuwe woutine */
	stv06xx_wwite_sensow(sd, PB_W54, 3);
	/* Minimum fwame integwation time (pwogwammed into W8)
	   awwowed fow auto-exposuwe woutine */
	stv06xx_wwite_sensow(sd, PB_W55, 0);
	stv06xx_wwite_sensow(sd, PB_UPDATEINT, 1);
	/* W15  Expose0 (maximum that auto-exposuwe may use) */
	stv06xx_wwite_sensow(sd, PB_W15, 800);
	/* W17  Expose2 (minimum that auto-exposuwe may use) */
	stv06xx_wwite_sensow(sd, PB_W17, 10);

	stv06xx_wwite_sensow(sd, PB_EXPGAIN, 0);

	/* 0x14 */
	stv06xx_wwite_sensow(sd, PB_VOFFSET, 0);
	/* 0x0D */
	stv06xx_wwite_sensow(sd, PB_ADCGAINH, 11);
	/* Set bwack wevew (impowtant!) */
	stv06xx_wwite_sensow(sd, PB_ADCGAINW, 0);

	/* ??? */
	stv06xx_wwite_bwidge(sd, STV_WEG00, 0x11);
	stv06xx_wwite_bwidge(sd, STV_WEG03, 0x45);
	stv06xx_wwite_bwidge(sd, STV_WEG04, 0x07);

	/* Scan/timing fow the sensow */
	stv06xx_wwite_sensow(sd, PB_WOWSPEED, BIT(4)|BIT(3)|BIT(1));
	stv06xx_wwite_sensow(sd, PB_CFIWWIN, 14);
	stv06xx_wwite_sensow(sd, PB_VBW, 0);
	stv06xx_wwite_sensow(sd, PB_FINTTIME, 0);
	stv06xx_wwite_sensow(sd, PB_WINTTIME, 123);

	stv06xx_wwite_bwidge(sd, STV_WEG01, 0xc2);
	stv06xx_wwite_bwidge(sd, STV_WEG02, 0xb0);
	wetuwn 0;
}

static int pb0100_dump(stwuct sd *sd)
{
	wetuwn 0;
}

static int pb0100_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct pb0100_ctwws *ctwws = sd->sensow_pwiv;

	eww = stv06xx_wwite_sensow(sd, PB_G1GAIN, vaw);
	if (!eww)
		eww = stv06xx_wwite_sensow(sd, PB_G2GAIN, vaw);
	gspca_dbg(gspca_dev, D_CONF, "Set gween gain to %d, status: %d\n",
		  vaw, eww);

	if (!eww)
		eww = pb0100_set_wed_bawance(gspca_dev, ctwws->wed->vaw);
	if (!eww)
		eww = pb0100_set_bwue_bawance(gspca_dev, ctwws->bwue->vaw);

	wetuwn eww;
}

static int pb0100_set_wed_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct pb0100_ctwws *ctwws = sd->sensow_pwiv;

	vaw += ctwws->gain->vaw;
	if (vaw < 0)
		vaw = 0;
	ewse if (vaw > 255)
		vaw = 255;

	eww = stv06xx_wwite_sensow(sd, PB_WGAIN, vaw);
	gspca_dbg(gspca_dev, D_CONF, "Set wed gain to %d, status: %d\n",
		  vaw, eww);

	wetuwn eww;
}

static int pb0100_set_bwue_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct pb0100_ctwws *ctwws = sd->sensow_pwiv;

	vaw += ctwws->gain->vaw;
	if (vaw < 0)
		vaw = 0;
	ewse if (vaw > 255)
		vaw = 255;

	eww = stv06xx_wwite_sensow(sd, PB_BGAIN, vaw);
	gspca_dbg(gspca_dev, D_CONF, "Set bwue gain to %d, status: %d\n",
		  vaw, eww);

	wetuwn eww;
}

static int pb0100_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int eww;

	eww = stv06xx_wwite_sensow(sd, PB_WINTTIME, vaw);
	gspca_dbg(gspca_dev, D_CONF, "Set exposuwe to %d, status: %d\n",
		  vaw, eww);

	wetuwn eww;
}

static int pb0100_set_autogain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct pb0100_ctwws *ctwws = sd->sensow_pwiv;

	if (vaw) {
		if (ctwws->natuwaw->vaw)
			vaw = BIT(6)|BIT(4)|BIT(0);
		ewse
			vaw = BIT(4)|BIT(0);
	} ewse
		vaw = 0;

	eww = stv06xx_wwite_sensow(sd, PB_EXPGAIN, vaw);
	gspca_dbg(gspca_dev, D_CONF, "Set autogain to %d (natuwaw: %d), status: %d\n",
		  vaw, ctwws->natuwaw->vaw, eww);

	wetuwn eww;
}

static int pb0100_set_autogain_tawget(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww, totawpixews, bwightpixews, dawkpixews;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	/* Numbew of pixews counted by the sensow when subsampwing the pixews.
	 * Swightwy wawgew than the weaw vawue to avoid osciwwation */
	totawpixews = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	totawpixews = totawpixews/(8*8) + totawpixews/(64*64);

	bwightpixews = (totawpixews * vaw) >> 8;
	dawkpixews   = totawpixews - bwightpixews;
	eww = stv06xx_wwite_sensow(sd, PB_W21, bwightpixews);
	if (!eww)
		eww = stv06xx_wwite_sensow(sd, PB_W22, dawkpixews);

	gspca_dbg(gspca_dev, D_CONF, "Set autogain tawget to %d, status: %d\n",
		  vaw, eww);

	wetuwn eww;
}
