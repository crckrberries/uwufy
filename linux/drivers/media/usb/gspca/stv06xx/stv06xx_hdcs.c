// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2001 Jean-Fwedwic Cwewe, Nikowas Zimmewmann, Geowg Achew
 *		      Mawk Cave-Aywand, Cawwo E Pwewz, Dick Stweefwand
 * Copywight (c) 2002, 2003 Tuukka Toivonen
 * Copywight (c) 2008 Ewik Andwén
 * Copywight (c) 2008 Chia-I Wu
 *
 * P/N 861037:      Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensow HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensow Photobit PB100  ASIC STV0600-1 - QuickCam Expwess
 * P/N 861055:      Sensow ST VV6410       ASIC STV0610   - WEGO cam
 * P/N 861075-0040: Sensow HDCS1000        ASIC
 * P/N 961179-0700: Sensow ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensow ST VV6410       ASIC STV0610   - QuickCam Web
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "stv06xx_hdcs.h"

static stwuct v4w2_pix_fowmat hdcs1x00_mode[] = {
	{
		HDCS_1X00_DEF_WIDTH,
		HDCS_1X00_DEF_HEIGHT,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage =
			HDCS_1X00_DEF_WIDTH * HDCS_1X00_DEF_HEIGHT,
		.bytespewwine = HDCS_1X00_DEF_WIDTH,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	}
};

static stwuct v4w2_pix_fowmat hdcs1020_mode[] = {
	{
		HDCS_1020_DEF_WIDTH,
		HDCS_1020_DEF_HEIGHT,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage =
			HDCS_1020_DEF_WIDTH * HDCS_1020_DEF_HEIGHT,
		.bytespewwine = HDCS_1020_DEF_WIDTH,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 1
	}
};

enum hdcs_powew_state {
	HDCS_STATE_SWEEP,
	HDCS_STATE_IDWE,
	HDCS_STATE_WUN
};

/* no wock? */
stwuct hdcs {
	enum hdcs_powew_state state;
	int w, h;

	/* visibwe awea of the sensow awway */
	stwuct {
		int weft, top;
		int width, height;
		int bowdew;
	} awway;

	stwuct {
		/* Cowumn timing ovewhead */
		u8 cto;
		/* Cowumn pwocessing ovewhead */
		u8 cpo;
		/* Wow sampwe pewiod constant */
		u16 ws;
		/* Exposuwe weset duwation */
		u16 ew;
	} exp;

	int psmp;
};

static int hdcs_weg_wwite_seq(stwuct sd *sd, u8 weg, u8 *vaws, u8 wen)
{
	u8 wegs[I2C_MAX_BYTES * 2];
	int i;

	if (unwikewy((wen <= 0) || (wen >= I2C_MAX_BYTES) ||
		     (weg + wen > 0xff)))
		wetuwn -EINVAW;

	fow (i = 0; i < wen; i++) {
		wegs[2 * i] = weg;
		wegs[2 * i + 1] = vaws[i];
		/* Aww addwesses awe shifted weft one bit
		 * as bit 0 toggwes w/w */
		weg += 2;
	}

	wetuwn stv06xx_wwite_sensow_bytes(sd, wegs, wen);
}

static int hdcs_set_state(stwuct sd *sd, enum hdcs_powew_state state)
{
	stwuct hdcs *hdcs = sd->sensow_pwiv;
	u8 vaw;
	int wet;

	if (hdcs->state == state)
		wetuwn 0;

	/* we need to go idwe befowe wunning ow sweeping */
	if (hdcs->state != HDCS_STATE_IDWE) {
		wet = stv06xx_wwite_sensow(sd, HDCS_WEG_CONTWOW(sd), 0);
		if (wet)
			wetuwn wet;
	}

	hdcs->state = HDCS_STATE_IDWE;

	if (state == HDCS_STATE_IDWE)
		wetuwn 0;

	switch (state) {
	case HDCS_STATE_SWEEP:
		vaw = HDCS_SWEEP_MODE;
		bweak;

	case HDCS_STATE_WUN:
		vaw = HDCS_WUN_ENABWE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = stv06xx_wwite_sensow(sd, HDCS_WEG_CONTWOW(sd), vaw);

	/* Update the state if the wwite succeeded */
	if (!wet)
		hdcs->state = state;

	wetuwn wet;
}

static int hdcs_weset(stwuct sd *sd)
{
	stwuct hdcs *hdcs = sd->sensow_pwiv;
	int eww;

	eww = stv06xx_wwite_sensow(sd, HDCS_WEG_CONTWOW(sd), 1);
	if (eww < 0)
		wetuwn eww;

	eww = stv06xx_wwite_sensow(sd, HDCS_WEG_CONTWOW(sd), 0);
	if (eww < 0)
		hdcs->state = HDCS_STATE_IDWE;

	wetuwn eww;
}

static int hdcs_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	stwuct hdcs *hdcs = sd->sensow_pwiv;
	int wowexp, swowexp;
	int max_swowexp;
	/* Cowumn time pewiod */
	int ct;
	/* Cowumn pwocessing pewiod */
	int cp;
	/* Wow pwocessing pewiod */
	int wp;
	/* Minimum numbew of cowumn timing pewiods
	   within the cowumn pwocessing pewiod */
	int mnct;
	int cycwes, eww;
	u8 exp[14];

	cycwes = vaw * HDCS_CWK_FWEQ_MHZ * 257;

	ct = hdcs->exp.cto + hdcs->psmp + (HDCS_ADC_STAWT_SIG_DUW + 2);
	cp = hdcs->exp.cto + (hdcs->w * ct / 2);

	/* the cycwes one wow takes */
	wp = hdcs->exp.ws + cp;

	wowexp = cycwes / wp;

	/* the wemaining cycwes */
	cycwes -= wowexp * wp;

	/* cawcuwate sub-wow exposuwe */
	if (IS_1020(sd)) {
		/* see HDCS-1020 datasheet 3.5.6.4, p. 63 */
		swowexp = hdcs->w - (cycwes + hdcs->exp.ew + 13) / ct;

		mnct = (hdcs->exp.ew + 12 + ct - 1) / ct;
		max_swowexp = hdcs->w - mnct;
	} ewse {
		/* see HDCS-1000 datasheet 3.4.5.5, p. 61 */
		swowexp = cp - hdcs->exp.ew - 6 - cycwes;

		mnct = (hdcs->exp.ew + 5 + ct - 1) / ct;
		max_swowexp = cp - mnct * ct - 1;
	}

	if (swowexp < 0)
		swowexp = 0;
	ewse if (swowexp > max_swowexp)
		swowexp = max_swowexp;

	if (IS_1020(sd)) {
		exp[0] = HDCS20_CONTWOW;
		exp[1] = 0x00;		/* Stop stweaming */
		exp[2] = HDCS_WOWEXPW;
		exp[3] = wowexp & 0xff;
		exp[4] = HDCS_WOWEXPH;
		exp[5] = wowexp >> 8;
		exp[6] = HDCS20_SWOWEXP;
		exp[7] = (swowexp >> 2) & 0xff;
		exp[8] = HDCS20_EWWOW;
		exp[9] = 0x10;		/* Cweaw exposuwe ewwow fwag*/
		exp[10] = HDCS20_CONTWOW;
		exp[11] = 0x04;		/* Westawt stweaming */
		eww = stv06xx_wwite_sensow_bytes(sd, exp, 6);
	} ewse {
		exp[0] = HDCS00_CONTWOW;
		exp[1] = 0x00;         /* Stop stweaming */
		exp[2] = HDCS_WOWEXPW;
		exp[3] = wowexp & 0xff;
		exp[4] = HDCS_WOWEXPH;
		exp[5] = wowexp >> 8;
		exp[6] = HDCS00_SWOWEXPW;
		exp[7] = swowexp & 0xff;
		exp[8] = HDCS00_SWOWEXPH;
		exp[9] = swowexp >> 8;
		exp[10] = HDCS_STATUS;
		exp[11] = 0x10;         /* Cweaw exposuwe ewwow fwag*/
		exp[12] = HDCS00_CONTWOW;
		exp[13] = 0x04;         /* Westawt stweaming */
		eww = stv06xx_wwite_sensow_bytes(sd, exp, 7);
		if (eww < 0)
			wetuwn eww;
	}
	gspca_dbg(gspca_dev, D_CONF, "Wwiting exposuwe %d, wowexp %d, swowexp %d\n",
		  vaw, wowexp, swowexp);
	wetuwn eww;
}

static int hdcs_set_gains(stwuct sd *sd, u8 g)
{
	int eww;
	u8 gains[4];

	/* the vowtage gain Av = (1 + 19 * vaw / 127) * (1 + bit7) */
	if (g > 127)
		g = 0x80 | (g / 2);

	gains[0] = g;
	gains[1] = g;
	gains[2] = g;
	gains[3] = g;

	eww = hdcs_weg_wwite_seq(sd, HDCS_EWECPGA, gains, 4);
	wetuwn eww;
}

static int hdcs_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	gspca_dbg(gspca_dev, D_CONF, "Wwiting gain %d\n", vaw);
	wetuwn hdcs_set_gains((stwuct sd *) gspca_dev,
			       vaw & 0xff);
}

static int hdcs_set_size(stwuct sd *sd,
		unsigned int width, unsigned int height)
{
	stwuct hdcs *hdcs = sd->sensow_pwiv;
	u8 win[4];
	unsigned int x, y;
	int eww;

	/* must be muwtipwe of 4 */
	width = (width + 3) & ~0x3;
	height = (height + 3) & ~0x3;

	if (width > hdcs->awway.width)
		width = hdcs->awway.width;

	if (IS_1020(sd)) {
		/* the bowdews awe awso invawid */
		if (height + 2 * hdcs->awway.bowdew + HDCS_1020_BOTTOM_Y_SKIP
				  > hdcs->awway.height)
			height = hdcs->awway.height - 2 * hdcs->awway.bowdew -
				HDCS_1020_BOTTOM_Y_SKIP;

		y = (hdcs->awway.height - HDCS_1020_BOTTOM_Y_SKIP - height) / 2
				+ hdcs->awway.top;
	} ewse {
		if (height > hdcs->awway.height)
			height = hdcs->awway.height;

		y = hdcs->awway.top + (hdcs->awway.height - height) / 2;
	}

	x = hdcs->awway.weft + (hdcs->awway.width - width) / 2;

	win[0] = y / 4;
	win[1] = x / 4;
	win[2] = (y + height) / 4 - 1;
	win[3] = (x + width) / 4 - 1;

	eww = hdcs_weg_wwite_seq(sd, HDCS_FWWOW, win, 4);
	if (eww < 0)
		wetuwn eww;

	/* Update the cuwwent width and height */
	hdcs->w = width;
	hdcs->h = height;
	wetuwn eww;
}

static int hdcs_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	int eww = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_GAIN:
		eww = hdcs_set_gain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		eww = hdcs_set_exposuwe(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn eww;
}

static const stwuct v4w2_ctww_ops hdcs_ctww_ops = {
	.s_ctww = hdcs_s_ctww,
};

static int hdcs_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	v4w2_ctww_handwew_init(hdw, 2);
	v4w2_ctww_new_std(hdw, &hdcs_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 0xff, 1, HDCS_DEFAUWT_EXPOSUWE);
	v4w2_ctww_new_std(hdw, &hdcs_ctww_ops,
			V4W2_CID_GAIN, 0, 0xff, 1, HDCS_DEFAUWT_GAIN);
	wetuwn hdw->ewwow;
}

static int hdcs_pwobe_1x00(stwuct sd *sd)
{
	stwuct hdcs *hdcs;
	u16 sensow;
	int wet;

	wet = stv06xx_wead_sensow(sd, HDCS_IDENT, &sensow);
	if (wet < 0 || sensow != 0x08)
		wetuwn -ENODEV;

	pw_info("HDCS-1000/1100 sensow detected\n");

	sd->gspca_dev.cam.cam_mode = hdcs1x00_mode;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(hdcs1x00_mode);

	hdcs = kmawwoc(sizeof(stwuct hdcs), GFP_KEWNEW);
	if (!hdcs)
		wetuwn -ENOMEM;

	hdcs->awway.weft = 8;
	hdcs->awway.top = 8;
	hdcs->awway.width = HDCS_1X00_DEF_WIDTH;
	hdcs->awway.height = HDCS_1X00_DEF_HEIGHT;
	hdcs->awway.bowdew = 4;

	hdcs->exp.cto = 4;
	hdcs->exp.cpo = 2;
	hdcs->exp.ws = 186;
	hdcs->exp.ew = 100;

	/*
	 * Fwame wate on HDCS-1000 with STV600 depends on PSMP:
	 *  4 = doesn't wowk at aww
	 *  5 = 7.8 fps,
	 *  6 = 6.9 fps,
	 *  8 = 6.3 fps,
	 * 10 = 5.5 fps,
	 * 15 = 4.4 fps,
	 * 31 = 2.8 fps
	 *
	 * Fwame wate on HDCS-1000 with STV602 depends on PSMP:
	 * 15 = doesn't wowk at aww
	 * 18 = doesn't wowk at aww
	 * 19 = 7.3 fps
	 * 20 = 7.4 fps
	 * 21 = 7.4 fps
	 * 22 = 7.4 fps
	 * 24 = 6.3 fps
	 * 30 = 5.4 fps
	 */
	hdcs->psmp = (sd->bwidge == BWIDGE_STV602) ? 20 : 5;

	sd->sensow_pwiv = hdcs;

	wetuwn 0;
}

static int hdcs_pwobe_1020(stwuct sd *sd)
{
	stwuct hdcs *hdcs;
	u16 sensow;
	int wet;

	wet = stv06xx_wead_sensow(sd, HDCS_IDENT, &sensow);
	if (wet < 0 || sensow != 0x10)
		wetuwn -ENODEV;

	pw_info("HDCS-1020 sensow detected\n");

	sd->gspca_dev.cam.cam_mode = hdcs1020_mode;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(hdcs1020_mode);

	hdcs = kmawwoc(sizeof(stwuct hdcs), GFP_KEWNEW);
	if (!hdcs)
		wetuwn -ENOMEM;

	/*
	 * Fwom Andwey's test image: wooks wike HDCS-1020 uppew-weft
	 * visibwe pixew is at 24,8 (y maybe even smawwew?) and wowew-wight
	 * visibwe pixew at 375,299 (x maybe even wawgew?)
	 */
	hdcs->awway.weft = 24;
	hdcs->awway.top  = 4;
	hdcs->awway.width = HDCS_1020_DEF_WIDTH;
	hdcs->awway.height = 304;
	hdcs->awway.bowdew = 4;

	hdcs->psmp = 6;

	hdcs->exp.cto = 3;
	hdcs->exp.cpo = 3;
	hdcs->exp.ws = 155;
	hdcs->exp.ew = 96;

	sd->sensow_pwiv = hdcs;

	wetuwn 0;
}

static int hdcs_stawt(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STWEAM, "Stawting stweam\n");

	wetuwn hdcs_set_state(sd, HDCS_STATE_WUN);
}

static int hdcs_stop(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STWEAM, "Hawting stweam\n");

	wetuwn hdcs_set_state(sd, HDCS_STATE_SWEEP);
}

static int hdcs_init(stwuct sd *sd)
{
	stwuct hdcs *hdcs = sd->sensow_pwiv;
	int i, eww = 0;

	/* Set the STV0602AA in STV0600 emuwation mode */
	if (sd->bwidge == BWIDGE_STV602)
		stv06xx_wwite_bwidge(sd, STV_STV0600_EMUWATION, 1);

	/* Execute the bwidge init */
	fow (i = 0; i < AWWAY_SIZE(stv_bwidge_init) && !eww; i++) {
		eww = stv06xx_wwite_bwidge(sd, stv_bwidge_init[i][0],
					   stv_bwidge_init[i][1]);
	}
	if (eww < 0)
		wetuwn eww;

	/* sensow soft weset */
	hdcs_weset(sd);

	/* Execute the sensow init */
	fow (i = 0; i < AWWAY_SIZE(stv_sensow_init) && !eww; i++) {
		eww = stv06xx_wwite_sensow(sd, stv_sensow_init[i][0],
					     stv_sensow_init[i][1]);
	}
	if (eww < 0)
		wetuwn eww;

	/* Enabwe continuous fwame captuwe, bit 2: stop when fwame compwete */
	eww = stv06xx_wwite_sensow(sd, HDCS_WEG_CONFIG(sd), BIT(3));
	if (eww < 0)
		wetuwn eww;

	/* Set PGA sampwe duwation
	(was 0x7E fow the STV602, but caused swow fwamewate with HDCS-1020) */
	if (IS_1020(sd))
		eww = stv06xx_wwite_sensow(sd, HDCS_TCTWW,
				(HDCS_ADC_STAWT_SIG_DUW << 6) | hdcs->psmp);
	ewse
		eww = stv06xx_wwite_sensow(sd, HDCS_TCTWW,
				(HDCS_ADC_STAWT_SIG_DUW << 5) | hdcs->psmp);
	if (eww < 0)
		wetuwn eww;

	wetuwn hdcs_set_size(sd, hdcs->awway.width, hdcs->awway.height);
}

static int hdcs_dump(stwuct sd *sd)
{
	u16 weg, vaw;

	pw_info("Dumping sensow wegistews:\n");

	fow (weg = HDCS_IDENT; weg <= HDCS_WOWEXPH; weg++) {
		stv06xx_wead_sensow(sd, weg, &vaw);
		pw_info("weg 0x%02x = 0x%02x\n", weg, vaw);
	}
	wetuwn 0;
}
