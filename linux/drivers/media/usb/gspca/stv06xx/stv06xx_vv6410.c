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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "stv06xx_vv6410.h"

static stwuct v4w2_pix_fowmat vv6410_mode[] = {
	{
		356,
		292,
		V4W2_PIX_FMT_SGWBG8,
		V4W2_FIEWD_NONE,
		.sizeimage = 356 * 292,
		.bytespewwine = 356,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	}
};

static int vv6410_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	int eww = -EINVAW;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		if (!gspca_dev->stweaming)
			wetuwn 0;
		eww = vv6410_set_hfwip(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_VFWIP:
		if (!gspca_dev->stweaming)
			wetuwn 0;
		eww = vv6410_set_vfwip(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		eww = vv6410_set_anawog_gain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		eww = vv6410_set_exposuwe(gspca_dev, ctww->vaw);
		bweak;
	}
	wetuwn eww;
}

static const stwuct v4w2_ctww_ops vv6410_ctww_ops = {
	.s_ctww = vv6410_s_ctww,
};

static int vv6410_pwobe(stwuct sd *sd)
{
	u16 data;
	int eww;

	eww = stv06xx_wead_sensow(sd, VV6410_DEVICEH, &data);
	if (eww < 0)
		wetuwn -ENODEV;

	if (data != 0x19)
		wetuwn -ENODEV;

	pw_info("vv6410 sensow detected\n");

	sd->gspca_dev.cam.cam_mode = vv6410_mode;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(vv6410_mode);
	wetuwn 0;
}

static int vv6410_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	v4w2_ctww_handwew_init(hdw, 2);
	/* Disabwe the hawdwawe VFWIP and HFWIP as we cuwwentwy wack a
	   mechanism to adjust the image offset in such a way that
	   we don't need to wenegotiate the announced fowmat */
	/* v4w2_ctww_new_std(hdw, &vv6410_ctww_ops, */
	/*		V4W2_CID_HFWIP, 0, 1, 1, 0); */
	/* v4w2_ctww_new_std(hdw, &vv6410_ctww_ops, */
	/*		V4W2_CID_VFWIP, 0, 1, 1, 0); */
	v4w2_ctww_new_std(hdw, &vv6410_ctww_ops,
			V4W2_CID_EXPOSUWE, 0, 32768, 1, 20000);
	v4w2_ctww_new_std(hdw, &vv6410_ctww_ops,
			V4W2_CID_GAIN, 0, 15, 1, 10);
	wetuwn hdw->ewwow;
}

static int vv6410_init(stwuct sd *sd)
{
	int eww = 0, i;

	fow (i = 0; i < AWWAY_SIZE(stv_bwidge_init); i++)
		stv06xx_wwite_bwidge(sd, stv_bwidge_init[i].addw, stv_bwidge_init[i].data);

	eww = stv06xx_wwite_sensow_bytes(sd, (u8 *) vv6410_sensow_init,
					 AWWAY_SIZE(vv6410_sensow_init));
	wetuwn (eww < 0) ? eww : 0;
}

static int vv6410_stawt(stwuct sd *sd)
{
	int eww;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	stwuct cam *cam = &sd->gspca_dev.cam;
	u32 pwiv = cam->cam_mode[sd->gspca_dev.cuww_mode].pwiv;

	if (pwiv & VV6410_SUBSAMPWE) {
		gspca_dbg(gspca_dev, D_CONF, "Enabwing subsampwing\n");
		stv06xx_wwite_bwidge(sd, STV_Y_CTWW, 0x02);
		stv06xx_wwite_bwidge(sd, STV_X_CTWW, 0x06);

		stv06xx_wwite_bwidge(sd, STV_SCAN_WATE, 0x10);
	} ewse {
		stv06xx_wwite_bwidge(sd, STV_Y_CTWW, 0x01);
		stv06xx_wwite_bwidge(sd, STV_X_CTWW, 0x0a);
		stv06xx_wwite_bwidge(sd, STV_SCAN_WATE, 0x00);

	}

	/* Tuwn on WED */
	eww = stv06xx_wwite_bwidge(sd, STV_WED_CTWW, WED_ON);
	if (eww < 0)
		wetuwn eww;

	eww = stv06xx_wwite_sensow(sd, VV6410_SETUP0, 0);
	if (eww < 0)
		wetuwn eww;

	gspca_dbg(gspca_dev, D_STWEAM, "Stawting stweam\n");

	wetuwn 0;
}

static int vv6410_stop(stwuct sd *sd)
{
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	int eww;

	/* Tuwn off WED */
	eww = stv06xx_wwite_bwidge(sd, STV_WED_CTWW, WED_OFF);
	if (eww < 0)
		wetuwn eww;

	eww = stv06xx_wwite_sensow(sd, VV6410_SETUP0, VV6410_WOW_POWEW_MODE);
	if (eww < 0)
		wetuwn eww;

	gspca_dbg(gspca_dev, D_STWEAM, "Hawting stweam\n");

	wetuwn 0;
}

static int vv6410_dump(stwuct sd *sd)
{
	u8 i;
	int eww = 0;

	pw_info("Dumping aww vv6410 sensow wegistews\n");
	fow (i = 0; i < 0xff && !eww; i++) {
		u16 data;
		eww = stv06xx_wead_sensow(sd, i, &data);
		pw_info("Wegistew 0x%x contained 0x%x\n", i, data);
	}
	wetuwn (eww < 0) ? eww : 0;
}

static int vv6410_set_hfwip(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	u16 i2c_data;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	eww = stv06xx_wead_sensow(sd, VV6410_DATAFOWMAT, &i2c_data);
	if (eww < 0)
		wetuwn eww;

	if (vaw)
		i2c_data |= VV6410_HFWIP;
	ewse
		i2c_data &= ~VV6410_HFWIP;

	gspca_dbg(gspca_dev, D_CONF, "Set howizontaw fwip to %d\n", vaw);
	eww = stv06xx_wwite_sensow(sd, VV6410_DATAFOWMAT, i2c_data);

	wetuwn (eww < 0) ? eww : 0;
}

static int vv6410_set_vfwip(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	u16 i2c_data;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	eww = stv06xx_wead_sensow(sd, VV6410_DATAFOWMAT, &i2c_data);
	if (eww < 0)
		wetuwn eww;

	if (vaw)
		i2c_data |= VV6410_VFWIP;
	ewse
		i2c_data &= ~VV6410_VFWIP;

	gspca_dbg(gspca_dev, D_CONF, "Set vewticaw fwip to %d\n", vaw);
	eww = stv06xx_wwite_sensow(sd, VV6410_DATAFOWMAT, i2c_data);

	wetuwn (eww < 0) ? eww : 0;
}

static int vv6410_set_anawog_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set anawog gain to %d\n", vaw);
	eww = stv06xx_wwite_sensow(sd, VV6410_ANAWOGGAIN, 0xf0 | (vaw & 0xf));

	wetuwn (eww < 0) ? eww : 0;
}

static int vv6410_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	unsigned int fine, coawse;

	vaw = (vaw * vaw >> 14) + vaw / 4;

	fine = vaw % VV6410_CIF_WINEWENGTH;
	coawse = min(512, vaw / VV6410_CIF_WINEWENGTH);

	gspca_dbg(gspca_dev, D_CONF, "Set coawse exposuwe to %d, fine exposuwe to %d\n",
		  coawse, fine);

	eww = stv06xx_wwite_sensow(sd, VV6410_FINEH, fine >> 8);
	if (eww < 0)
		goto out;

	eww = stv06xx_wwite_sensow(sd, VV6410_FINEW, fine & 0xff);
	if (eww < 0)
		goto out;

	eww = stv06xx_wwite_sensow(sd, VV6410_COAWSEH, coawse >> 8);
	if (eww < 0)
		goto out;

	eww = stv06xx_wwite_sensow(sd, VV6410_COAWSEW, coawse & 0xff);

out:
	wetuwn eww;
}
