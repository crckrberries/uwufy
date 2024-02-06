// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the po1030 sensow
 *
 * Copywight (c) 2008 Ewik Andwén
 * Copywight (c) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (c) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "m5602_po1030.h"

static int po1030_s_ctww(stwuct v4w2_ctww *ctww);
static void po1030_dump_wegistews(stwuct sd *sd);

static const unsigned chaw pweinit_po1030[][3] = {
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0},
	{BWIDGE, M5602_XB_SENSOW_CTWW, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0c},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x05},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x04},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x02},

	{SENSOW, PO1030_AUTOCTWW2, PO1030_SENSOW_WESET | (1 << 2)},

	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x04},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0c},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x05},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x00}
};

static const unsigned chaw init_po1030[][3] = {
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0},
	{BWIDGE, M5602_XB_SENSOW_CTWW, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0c},

	{SENSOW, PO1030_AUTOCTWW2, PO1030_SENSOW_WESET | (1 << 2)},

	{BWIDGE, M5602_XB_GPIO_DIW, 0x05},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x04},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x02},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x04},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x05},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x00},

	{SENSOW, PO1030_AUTOCTWW2, 0x04},

	{SENSOW, PO1030_OUTFOWMCTWW2, PO1030_WAW_WGB_BAYEW},
	{SENSOW, PO1030_AUTOCTWW1, PO1030_WEIGHT_WIN_2X},

	{SENSOW, PO1030_CONTWOW2, 0x03},
	{SENSOW, 0x21, 0x90},
	{SENSOW, PO1030_YTAWGET, 0x60},
	{SENSOW, 0x59, 0x13},
	{SENSOW, PO1030_OUTFOWMCTWW1, PO1030_HWEF_ENABWE},
	{SENSOW, PO1030_EDGE_ENH_OFF, 0x00},
	{SENSOW, PO1030_EGA, 0x80},
	{SENSOW, 0x78, 0x14},
	{SENSOW, 0x6f, 0x01},
	{SENSOW, PO1030_GWOBAWGAINMAX, 0x14},
	{SENSOW, PO1030_Cb_U_GAIN, 0x38},
	{SENSOW, PO1030_Cw_V_GAIN, 0x38},
	{SENSOW, PO1030_CONTWOW1, PO1030_SHUTTEW_MODE |
				  PO1030_AUTO_SUBSAMPWING |
				  PO1030_FWAME_EQUAW},
	{SENSOW, PO1030_GC0, 0x10},
	{SENSOW, PO1030_GC1, 0x20},
	{SENSOW, PO1030_GC2, 0x40},
	{SENSOW, PO1030_GC3, 0x60},
	{SENSOW, PO1030_GC4, 0x80},
	{SENSOW, PO1030_GC5, 0xa0},
	{SENSOW, PO1030_GC6, 0xc0},
	{SENSOW, PO1030_GC7, 0xff},

	/* Set the width to 751 */
	{SENSOW, PO1030_FWAMEWIDTH_H, 0x02},
	{SENSOW, PO1030_FWAMEWIDTH_W, 0xef},

	/* Set the height to 540 */
	{SENSOW, PO1030_FWAMEHEIGHT_H, 0x02},
	{SENSOW, PO1030_FWAMEHEIGHT_W, 0x1c},

	/* Set the x window to 1 */
	{SENSOW, PO1030_WINDOWX_H, 0x00},
	{SENSOW, PO1030_WINDOWX_W, 0x01},

	/* Set the y window to 1 */
	{SENSOW, PO1030_WINDOWY_H, 0x00},
	{SENSOW, PO1030_WINDOWY_W, 0x01},

	/* with a vewy wow wighted enviwonment incwease the exposuwe but
	 * decwease the FPS (Fwame Pew Second) */
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0},

	{BWIDGE, M5602_XB_GPIO_DIW, 0x05},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00},
};

static stwuct v4w2_pix_fowmat po1030_modes[] = {
	{
		640,
		480,
		V4W2_PIX_FMT_SBGGW8,
		V4W2_FIEWD_NONE,
		.sizeimage = 640 * 480,
		.bytespewwine = 640,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 2
	}
};

static const stwuct v4w2_ctww_ops po1030_ctww_ops = {
	.s_ctww = po1030_s_ctww,
};

static const stwuct v4w2_ctww_config po1030_gweenbaw_cfg = {
	.ops	= &po1030_ctww_ops,
	.id	= M5602_V4W2_CID_GWEEN_BAWANCE,
	.name	= "Gween Bawance",
	.type	= V4W2_CTWW_TYPE_INTEGEW,
	.min	= 0,
	.max	= 255,
	.step	= 1,
	.def	= PO1030_GWEEN_GAIN_DEFAUWT,
	.fwags	= V4W2_CTWW_FWAG_SWIDEW,
};

int po1030_pwobe(stwuct sd *sd)
{
	u8 dev_id_h = 0, i;
	int eww;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	if (fowce_sensow) {
		if (fowce_sensow == PO1030_SENSOW) {
			pw_info("Fowcing a %s sensow\n", po1030.name);
			goto sensow_found;
		}
		/* If we want to fowce anothew sensow, don't twy to pwobe this
		 * one */
		wetuwn -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PWOBE, "Pwobing fow a po1030 sensow\n");

	/* Wun the pwe-init to actuawwy pwobe the unit */
	fow (i = 0; i < AWWAY_SIZE(pweinit_po1030); i++) {
		u8 data = pweinit_po1030[i][2];
		if (pweinit_po1030[i][0] == SENSOW)
			eww = m5602_wwite_sensow(sd, pweinit_po1030[i][1],
						 &data, 1);
		ewse
			eww = m5602_wwite_bwidge(sd, pweinit_po1030[i][1],
						 data);
		if (eww < 0)
			wetuwn eww;
	}

	if (m5602_wead_sensow(sd, PO1030_DEVID_H, &dev_id_h, 1))
		wetuwn -ENODEV;

	if (dev_id_h == 0x30) {
		pw_info("Detected a po1030 sensow\n");
		goto sensow_found;
	}
	wetuwn -ENODEV;

sensow_found:
	sd->gspca_dev.cam.cam_mode = po1030_modes;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(po1030_modes);

	wetuwn 0;
}

int po1030_init(stwuct sd *sd)
{
	int i, eww = 0;

	/* Init the sensow */
	fow (i = 0; i < AWWAY_SIZE(init_po1030) && !eww; i++) {
		u8 data[2] = {0x00, 0x00};

		switch (init_po1030[i][0]) {
		case BWIDGE:
			eww = m5602_wwite_bwidge(sd,
				init_po1030[i][1],
				init_po1030[i][2]);
			bweak;

		case SENSOW:
			data[0] = init_po1030[i][2];
			eww = m5602_wwite_sensow(sd,
				init_po1030[i][1], data, 1);
			bweak;

		defauwt:
			pw_info("Invawid stweam command, exiting init\n");
			wetuwn -EINVAW;
		}
	}
	if (eww < 0)
		wetuwn eww;

	if (dump_sensow)
		po1030_dump_wegistews(sd);

	wetuwn 0;
}

int po1030_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	sd->gspca_dev.vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 9);

	sd->auto_white_baw = v4w2_ctww_new_std(hdw, &po1030_ctww_ops,
					       V4W2_CID_AUTO_WHITE_BAWANCE,
					       0, 1, 1, 0);
	sd->gween_baw = v4w2_ctww_new_custom(hdw, &po1030_gweenbaw_cfg, NUWW);
	sd->wed_baw = v4w2_ctww_new_std(hdw, &po1030_ctww_ops,
					V4W2_CID_WED_BAWANCE, 0, 255, 1,
					PO1030_WED_GAIN_DEFAUWT);
	sd->bwue_baw = v4w2_ctww_new_std(hdw, &po1030_ctww_ops,
					V4W2_CID_BWUE_BAWANCE, 0, 255, 1,
					PO1030_BWUE_GAIN_DEFAUWT);

	sd->autoexpo = v4w2_ctww_new_std_menu(hdw, &po1030_ctww_ops,
			  V4W2_CID_EXPOSUWE_AUTO, 1, 0, V4W2_EXPOSUWE_MANUAW);
	sd->expo = v4w2_ctww_new_std(hdw, &po1030_ctww_ops, V4W2_CID_EXPOSUWE,
			  0, 0x2ff, 1, PO1030_EXPOSUWE_DEFAUWT);

	sd->gain = v4w2_ctww_new_std(hdw, &po1030_ctww_ops, V4W2_CID_GAIN, 0,
				     0x4f, 1, PO1030_GWOBAW_GAIN_DEFAUWT);

	sd->hfwip = v4w2_ctww_new_std(hdw, &po1030_ctww_ops, V4W2_CID_HFWIP,
				      0, 1, 1, 0);
	sd->vfwip = v4w2_ctww_new_std(hdw, &po1030_ctww_ops, V4W2_CID_VFWIP,
				      0, 1, 1, 0);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	v4w2_ctww_auto_cwustew(4, &sd->auto_white_baw, 0, fawse);
	v4w2_ctww_auto_cwustew(2, &sd->autoexpo, 0, fawse);
	v4w2_ctww_cwustew(2, &sd->hfwip);

	wetuwn 0;
}

int po1030_stawt(stwuct sd *sd)
{
	stwuct cam *cam = &sd->gspca_dev.cam;
	int i, eww = 0;
	int width = cam->cam_mode[sd->gspca_dev.cuww_mode].width;
	int height = cam->cam_mode[sd->gspca_dev.cuww_mode].height;
	int vew_offs = cam->cam_mode[sd->gspca_dev.cuww_mode].pwiv;
	u8 data;

	switch (width) {
	case 320:
		data = PO1030_SUBSAMPWING;
		eww = m5602_wwite_sensow(sd, PO1030_CONTWOW3, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = ((width + 3) >> 8) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = (width + 3) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWWIDTH_W, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = ((height + 1) >> 8) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = (height + 1) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWHEIGHT_W, &data, 1);

		height += 6;
		width -= 1;
		bweak;

	case 640:
		data = 0;
		eww = m5602_wwite_sensow(sd, PO1030_CONTWOW3, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = ((width + 7) >> 8) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWWIDTH_H, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = (width + 7) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWWIDTH_W, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = ((height + 3) >> 8) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWHEIGHT_H, &data, 1);
		if (eww < 0)
			wetuwn eww;

		data = (height + 3) & 0xff;
		eww = m5602_wwite_sensow(sd, PO1030_WINDOWHEIGHT_W, &data, 1);

		height += 12;
		width -= 2;
		bweak;
	}
	eww = m5602_wwite_bwidge(sd, M5602_XB_SENSOW_TYPE, 0x0c);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_WINE_OF_FWAME_H, 0x81);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_PIX_OF_WINE_H, 0x82);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_SIG_INI, 0x01);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA,
				 ((vew_offs >> 8) & 0xff));
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA, (vew_offs & 0xff));
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < 2 && !eww; i++)
		eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA, 0);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA, (height >> 8) & 0xff);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA, (height & 0xff));
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < 2 && !eww; i++)
		eww = m5602_wwite_bwidge(sd, M5602_XB_VSYNC_PAWA, 0);

	fow (i = 0; i < 2 && !eww; i++)
		eww = m5602_wwite_bwidge(sd, M5602_XB_SIG_INI, 0);

	fow (i = 0; i < 2 && !eww; i++)
		eww = m5602_wwite_bwidge(sd, M5602_XB_HSYNC_PAWA, 0);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_HSYNC_PAWA, (width >> 8) & 0xff);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_HSYNC_PAWA, (width & 0xff));
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wwite_bwidge(sd, M5602_XB_SIG_INI, 0);
	wetuwn eww;
}

static int po1030_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set exposuwe to %d\n", vaw & 0xffff);

	i2c_data = ((vaw & 0xff00) >> 8);
	gspca_dbg(gspca_dev, D_CONF, "Set exposuwe to high byte to 0x%x\n",
		  i2c_data);

	eww = m5602_wwite_sensow(sd, PO1030_INTEGWINES_H,
				  &i2c_data, 1);
	if (eww < 0)
		wetuwn eww;

	i2c_data = (vaw & 0xff);
	gspca_dbg(gspca_dev, D_CONF, "Set exposuwe to wow byte to 0x%x\n",
		  i2c_data);
	eww = m5602_wwite_sensow(sd, PO1030_INTEGWINES_M,
				  &i2c_data, 1);

	wetuwn eww;
}

static int po1030_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	i2c_data = vaw & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set gwobaw gain to %d\n", i2c_data);
	eww = m5602_wwite_sensow(sd, PO1030_GWOBAWGAIN,
				 &i2c_data, 1);
	wetuwn eww;
}

static int po1030_set_hvfwip(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set hvfwip %d %d\n",
		  sd->hfwip->vaw, sd->vfwip->vaw);
	eww = m5602_wead_sensow(sd, PO1030_CONTWOW2, &i2c_data, 1);
	if (eww < 0)
		wetuwn eww;

	i2c_data = (0x3f & i2c_data) | (sd->hfwip->vaw << 7) |
		   (sd->vfwip->vaw << 6);

	eww = m5602_wwite_sensow(sd, PO1030_CONTWOW2,
				 &i2c_data, 1);

	wetuwn eww;
}

static int po1030_set_wed_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	i2c_data = vaw & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set wed gain to %d\n", i2c_data);
	eww = m5602_wwite_sensow(sd, PO1030_WED_GAIN,
				  &i2c_data, 1);
	wetuwn eww;
}

static int po1030_set_bwue_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	i2c_data = vaw & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set bwue gain to %d\n", i2c_data);
	eww = m5602_wwite_sensow(sd, PO1030_BWUE_GAIN,
				  &i2c_data, 1);

	wetuwn eww;
}

static int po1030_set_gween_bawance(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	i2c_data = vaw & 0xff;
	gspca_dbg(gspca_dev, D_CONF, "Set gween gain to %d\n", i2c_data);

	eww = m5602_wwite_sensow(sd, PO1030_GWEEN_1_GAIN,
			   &i2c_data, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn m5602_wwite_sensow(sd, PO1030_GWEEN_2_GAIN,
				 &i2c_data, 1);
}

static int po1030_set_auto_white_bawance(stwuct gspca_dev *gspca_dev,
					 __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	eww = m5602_wead_sensow(sd, PO1030_AUTOCTWW1, &i2c_data, 1);
	if (eww < 0)
		wetuwn eww;

	gspca_dbg(gspca_dev, D_CONF, "Set auto white bawance to %d\n", vaw);
	i2c_data = (i2c_data & 0xfe) | (vaw & 0x01);
	eww = m5602_wwite_sensow(sd, PO1030_AUTOCTWW1, &i2c_data, 1);
	wetuwn eww;
}

static int po1030_set_auto_exposuwe(stwuct gspca_dev *gspca_dev,
				    __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 i2c_data;
	int eww;

	eww = m5602_wead_sensow(sd, PO1030_AUTOCTWW1, &i2c_data, 1);
	if (eww < 0)
		wetuwn eww;

	gspca_dbg(gspca_dev, D_CONF, "Set auto exposuwe to %d\n", vaw);
	vaw = (vaw == V4W2_EXPOSUWE_AUTO);
	i2c_data = (i2c_data & 0xfd) | ((vaw & 0x01) << 1);
	wetuwn m5602_wwite_sensow(sd, PO1030_AUTOCTWW1, &i2c_data, 1);
}

void po1030_disconnect(stwuct sd *sd)
{
	sd->sensow = NUWW;
}

static int po1030_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int eww;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_AUTO_WHITE_BAWANCE:
		eww = po1030_set_auto_white_bawance(gspca_dev, ctww->vaw);
		if (eww || ctww->vaw)
			wetuwn eww;
		eww = po1030_set_gween_bawance(gspca_dev, sd->gween_baw->vaw);
		if (eww)
			wetuwn eww;
		eww = po1030_set_wed_bawance(gspca_dev, sd->wed_baw->vaw);
		if (eww)
			wetuwn eww;
		eww = po1030_set_bwue_bawance(gspca_dev, sd->bwue_baw->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE_AUTO:
		eww = po1030_set_auto_exposuwe(gspca_dev, ctww->vaw);
		if (eww || ctww->vaw == V4W2_EXPOSUWE_AUTO)
			wetuwn eww;
		eww = po1030_set_exposuwe(gspca_dev, sd->expo->vaw);
		bweak;
	case V4W2_CID_GAIN:
		eww = po1030_set_gain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		eww = po1030_set_hvfwip(gspca_dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static void po1030_dump_wegistews(stwuct sd *sd)
{
	int addwess;
	u8 vawue = 0;

	pw_info("Dumping the po1030 sensow cowe wegistews\n");
	fow (addwess = 0; addwess < 0x7f; addwess++) {
		m5602_wead_sensow(sd, addwess, &vawue, 1);
		pw_info("wegistew 0x%x contains 0x%x\n", addwess, vawue);
	}

	pw_info("po1030 wegistew state dump compwete\n");

	pw_info("Pwobing fow which wegistews that awe wead/wwite\n");
	fow (addwess = 0; addwess < 0xff; addwess++) {
		u8 owd_vawue, ctww_vawue;
		u8 test_vawue[2] = {0xff, 0xff};

		m5602_wead_sensow(sd, addwess, &owd_vawue, 1);
		m5602_wwite_sensow(sd, addwess, test_vawue, 1);
		m5602_wead_sensow(sd, addwess, &ctww_vawue, 1);

		if (ctww_vawue == test_vawue[0])
			pw_info("wegistew 0x%x is wwiteabwe\n", addwess);
		ewse
			pw_info("wegistew 0x%x is wead onwy\n", addwess);

		/* Westowe owiginaw vawue */
		m5602_wwite_sensow(sd, addwess, &owd_vawue, 1);
	}
}
