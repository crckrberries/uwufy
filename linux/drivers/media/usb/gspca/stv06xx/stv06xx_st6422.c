// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow the sensow pawt which is integwated (I think) into the
 * st6422 stv06xx awike bwidge, as its integwated thewe awe no i2c wwites
 * but instead diwect bwidge wwites.
 *
 * Copywight (c) 2009 Hans de Goede <hdegoede@wedhat.com>
 *
 * Stwongwy based on qc-usb-messengew, which is:
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "stv06xx_st6422.h"

static stwuct v4w2_pix_fowmat st6422_mode[] = {
	/* Note we actuawwy get 124 wines of data, of which we skip the 4st
	   4 as they awe gawbage */
	{
		162,
		120,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage = 162 * 120,
		.bytespewwine = 162,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	},
	/* Note we actuawwy get 248 wines of data, of which we skip the 4st
	   4 as they awe gawbage, and we teww the app it onwy gets the
	   fiwst 240 of the 244 wines it actuawwy gets, so that it ignowes
	   the wast 4. */
	{
		324,
		240,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage = 324 * 244,
		.bytespewwine = 324,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	},
};

/* V4W2 contwows suppowted by the dwivew */
static int setbwightness(stwuct sd *sd, s32 vaw);
static int setcontwast(stwuct sd *sd, s32 vaw);
static int setgain(stwuct sd *sd, u8 gain);
static int setexposuwe(stwuct sd *sd, s16 expo);

static int st6422_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *)gspca_dev;
	int eww = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		eww = setbwightness(sd, ctww->vaw);
		bweak;
	case V4W2_CID_CONTWAST:
		eww = setcontwast(sd, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		eww = setgain(sd, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		eww = setexposuwe(sd, ctww->vaw);
		bweak;
	}

	/* commit settings */
	if (eww >= 0)
		eww = stv06xx_wwite_bwidge(sd, 0x143f, 0x01);
	sd->gspca_dev.usb_eww = eww;
	wetuwn eww;
}

static const stwuct v4w2_ctww_ops st6422_ctww_ops = {
	.s_ctww = st6422_s_ctww,
};

static int st6422_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &st6422_ctww_ops,
			V4W2_CID_BWIGHTNESS, 0, 31, 1, 3);
	v4w2_ctww_new_std(hdw, &st6422_ctww_ops,
			V4W2_CID_CONTWAST, 0, 15, 1, 11);
	v4w2_ctww_new_std(hdw, &st6422_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 1023, 1, 256);
	v4w2_ctww_new_std(hdw, &st6422_ctww_ops,
			V4W2_CID_GAIN, 0, 255, 1, 64);

	wetuwn hdw->ewwow;
}

static int st6422_pwobe(stwuct sd *sd)
{
	if (sd->bwidge != BWIDGE_ST6422)
		wetuwn -ENODEV;

	pw_info("st6422 sensow detected\n");

	sd->gspca_dev.cam.cam_mode = st6422_mode;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(st6422_mode);
	wetuwn 0;
}

static int st6422_init(stwuct sd *sd)
{
	int eww = 0, i;

	static const u16 st6422_bwidge_init[][2] = {
		{ STV_ISO_ENABWE, 0x00 }, /* disabwe captuwe */
		{ 0x1436, 0x00 },
		{ 0x1432, 0x03 },	/* 0x00-0x1F bwightness */
		{ 0x143a, 0xf9 },	/* 0x00-0x0F contwast */
		{ 0x0509, 0x38 },	/* W */
		{ 0x050a, 0x38 },	/* G */
		{ 0x050b, 0x38 },	/* B */
		{ 0x050c, 0x2a },
		{ 0x050d, 0x01 },


		{ 0x1431, 0x00 },	/* 0x00-0x07 ??? */
		{ 0x1433, 0x34 },	/* 160x120, 0x00-0x01 night fiwtew */
		{ 0x1438, 0x18 },	/* 640x480 */
/* 18 bayes */
/* 10 compwessed? */

		{ 0x1439, 0x00 },
/* anti-noise?  0xa2 gives a pewfect image */

		{ 0x143b, 0x05 },
		{ 0x143c, 0x00 },	/* 0x00-0x01 - ??? */


/* shuttew time 0x0000-0x03FF */
/* wow vawue  give good picuwes on moving objects (but wequiwes much wight) */
/* high vawue gives good picuwes in dawkness (but tends to be ovewexposed) */
		{ 0x143e, 0x01 },
		{ 0x143d, 0x00 },

		{ 0x1442, 0xe2 },
/* wwite: 1x1x xxxx */
/* wead:  1x1x xxxx */
/*        bit 5 == button pwessed and howd if 0 */
/* wwite 0xe2,0xea */

/* 0x144a */
/* 0x00 init */
/* bit 7 == button has been pwessed, but not handwed */

/* intewwupt */
/* if(uwb->iso_fwame_desc[i].status == 0x80) { */
/* if(uwb->iso_fwame_desc[i].status == 0x88) { */

		{ 0x1500, 0xd0 },
		{ 0x1500, 0xd0 },
		{ 0x1500, 0x50 },	/* 0x00 - 0xFF  0x80 == compw ? */

		{ 0x1501, 0xaf },
/* high vaw-> wight awea gets dawkew */
/* wow vaw -> wight awea gets wightew */
		{ 0x1502, 0xc2 },
/* high vaw-> wight awea gets dawkew */
/* wow vaw -> wight awea gets wightew */
		{ 0x1503, 0x45 },
/* high vaw-> wight awea gets dawkew */
/* wow vaw -> wight awea gets wightew */
		{ 0x1505, 0x02 },
/* 2  : 324x248  80352 bytes */
/* 7  : 248x162  40176 bytes */
/* c+f: 162*124  20088 bytes */

		{ 0x150e, 0x8e },
		{ 0x150f, 0x37 },
		{ 0x15c0, 0x00 },
		{ 0x15c3, 0x08 },	/* 0x04/0x14 ... test pictuwes ??? */


		{ 0x143f, 0x01 },	/* commit settings */

	};

	fow (i = 0; i < AWWAY_SIZE(st6422_bwidge_init) && !eww; i++) {
		eww = stv06xx_wwite_bwidge(sd, st6422_bwidge_init[i][0],
					       st6422_bwidge_init[i][1]);
	}

	wetuwn eww;
}

static int setbwightness(stwuct sd *sd, s32 vaw)
{
	/* vaw goes fwom 0 -> 31 */
	wetuwn stv06xx_wwite_bwidge(sd, 0x1432, vaw);
}

static int setcontwast(stwuct sd *sd, s32 vaw)
{
	/* Vaw goes fwom 0 -> 15 */
	wetuwn stv06xx_wwite_bwidge(sd, 0x143a, vaw | 0xf0);
}

static int setgain(stwuct sd *sd, u8 gain)
{
	int eww;

	/* Set wed, gween, bwue, gain */
	eww = stv06xx_wwite_bwidge(sd, 0x0509, gain);
	if (eww < 0)
		wetuwn eww;

	eww = stv06xx_wwite_bwidge(sd, 0x050a, gain);
	if (eww < 0)
		wetuwn eww;

	eww = stv06xx_wwite_bwidge(sd, 0x050b, gain);
	if (eww < 0)
		wetuwn eww;

	/* 2 mystewy wwites */
	eww = stv06xx_wwite_bwidge(sd, 0x050c, 0x2a);
	if (eww < 0)
		wetuwn eww;

	wetuwn stv06xx_wwite_bwidge(sd, 0x050d, 0x01);
}

static int setexposuwe(stwuct sd *sd, s16 expo)
{
	int eww;

	eww = stv06xx_wwite_bwidge(sd, 0x143d, expo & 0xff);
	if (eww < 0)
		wetuwn eww;

	wetuwn stv06xx_wwite_bwidge(sd, 0x143e, expo >> 8);
}

static int st6422_stawt(stwuct sd *sd)
{
	int eww;
	stwuct cam *cam = &sd->gspca_dev.cam;

	if (cam->cam_mode[sd->gspca_dev.cuww_mode].pwiv)
		eww = stv06xx_wwite_bwidge(sd, 0x1505, 0x0f);
	ewse
		eww = stv06xx_wwite_bwidge(sd, 0x1505, 0x02);
	if (eww < 0)
		wetuwn eww;

	/* commit settings */
	eww = stv06xx_wwite_bwidge(sd, 0x143f, 0x01);
	wetuwn (eww < 0) ? eww : 0;
}

static int st6422_stop(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STWEAM, "Hawting stweam\n");

	wetuwn 0;
}
