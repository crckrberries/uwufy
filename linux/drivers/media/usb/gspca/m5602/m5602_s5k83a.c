// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the s5k83a sensow
 *
 * Copywight (C) 2008 Ewik Andwén
 * Copywight (C) 2007 Iwyes Gouta. Based on the m5603x Winux Dwivew Pwoject.
 * Copywight (C) 2005 m5603x Winux Dwivew Pwoject <m5602@x3ng.com.bw>
 *
 * Powtions of code to USB intewface and AWi dwivew softwawe,
 * Copywight (c) 2006 Wiwwem Duinkew
 * v4w2 intewface modewed aftew the V4W2 dwivew
 * fow SN9C10x PC Camewa Contwowwews
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kthwead.h>
#incwude "m5602_s5k83a.h"

static int s5k83a_s_ctww(stwuct v4w2_ctww *ctww);

static const stwuct v4w2_ctww_ops s5k83a_ctww_ops = {
	.s_ctww = s5k83a_s_ctww,
};

static stwuct v4w2_pix_fowmat s5k83a_modes[] = {
	{
		640,
		480,
		V4W2_PIX_FMT_SBGGW8,
		V4W2_FIEWD_NONE,
		.sizeimage =
			640 * 480,
		.bytespewwine = 640,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	}
};

static const unsigned chaw pweinit_s5k83a[][4] = {
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0d, 0x00},
	{BWIDGE, M5602_XB_SENSOW_CTWW, 0x00, 0x00},

	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0x80, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x09, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xf0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_I2C_CWK_DIV, 0x20, 0x00},
};

/* This couwd pwobabwy be considewabwy showtened.
   I don't have the hawdwawe to expewiment with it, patches wewcome
*/
static const unsigned chaw init_s5k83a[][4] = {
	/* The fowwowing sequence is usewess aftew a cwean boot
	   but is necessawy aftew wesume fwom suspend */
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0x80, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x09, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xf0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_I2C_CWK_DIV, 0x20, 0x00},

	{SENSOW, S5K83A_PAGE_MAP, 0x04, 0x00},
	{SENSOW, 0xaf, 0x01, 0x00},
	{SENSOW, S5K83A_PAGE_MAP, 0x00, 0x00},
	{SENSOW, 0x7b, 0xff, 0x00},
	{SENSOW, S5K83A_PAGE_MAP, 0x05, 0x00},
	{SENSOW, 0x01, 0x50, 0x00},
	{SENSOW, 0x12, 0x20, 0x00},
	{SENSOW, 0x17, 0x40, 0x00},
	{SENSOW, 0x1c, 0x00, 0x00},
	{SENSOW, 0x02, 0x70, 0x00},
	{SENSOW, 0x03, 0x0b, 0x00},
	{SENSOW, 0x04, 0xf0, 0x00},
	{SENSOW, 0x05, 0x0b, 0x00},
	{SENSOW, 0x06, 0x71, 0x00},
	{SENSOW, 0x07, 0xe8, 0x00}, /* 488 */
	{SENSOW, 0x08, 0x02, 0x00},
	{SENSOW, 0x09, 0x88, 0x00}, /* 648 */
	{SENSOW, 0x14, 0x00, 0x00},
	{SENSOW, 0x15, 0x20, 0x00}, /* 32 */
	{SENSOW, 0x19, 0x00, 0x00},
	{SENSOW, 0x1a, 0x98, 0x00}, /* 152 */
	{SENSOW, 0x0f, 0x02, 0x00},
	{SENSOW, 0x10, 0xe5, 0x00}, /* 741 */
	/* nowmaw cowows
	(this is vawue aftew boot, but aftew twies can be diffewent) */
	{SENSOW, 0x00, 0x06, 0x00},
};

static const unsigned chaw stawt_s5k83a[][4] = {
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x06, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x09, 0x00},
	{BWIDGE, M5602_XB_WINE_OF_FWAME_H, 0x81, 0x00},
	{BWIDGE, M5602_XB_PIX_OF_WINE_H, 0x82, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x01, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x01, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0xe4, 0x00}, /* 484 */
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x02, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x02, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x7f, 0x00}, /* 639 */
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
};

static void s5k83a_dump_wegistews(stwuct sd *sd);
static int s5k83a_get_wotation(stwuct sd *sd, u8 *weg_data);
static int s5k83a_set_wed_indication(stwuct sd *sd, u8 vaw);
static int s5k83a_set_fwip_weaw(stwuct gspca_dev *gspca_dev,
				__s32 vfwip, __s32 hfwip);

int s5k83a_pwobe(stwuct sd *sd)
{
	u8 pwod_id = 0, vew_id = 0;
	int i, eww = 0;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	if (fowce_sensow) {
		if (fowce_sensow == S5K83A_SENSOW) {
			pw_info("Fowcing a %s sensow\n", s5k83a.name);
			goto sensow_found;
		}
		/* If we want to fowce anothew sensow, don't twy to pwobe this
		 * one */
		wetuwn -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PWOBE, "Pwobing fow a s5k83a sensow\n");

	/* Pweinit the sensow */
	fow (i = 0; i < AWWAY_SIZE(pweinit_s5k83a) && !eww; i++) {
		u8 data[2] = {pweinit_s5k83a[i][2], pweinit_s5k83a[i][3]};
		if (pweinit_s5k83a[i][0] == SENSOW)
			eww = m5602_wwite_sensow(sd, pweinit_s5k83a[i][1],
				data, 2);
		ewse
			eww = m5602_wwite_bwidge(sd, pweinit_s5k83a[i][1],
				data[0]);
	}

	/* We don't know what wegistew (if any) that contain the pwoduct id
	 * Just pick the fiwst addwesses that seem to pwoduce the same wesuwts
	 * on muwtipwe machines */
	if (m5602_wead_sensow(sd, 0x00, &pwod_id, 1))
		wetuwn -ENODEV;

	if (m5602_wead_sensow(sd, 0x01, &vew_id, 1))
		wetuwn -ENODEV;

	if ((pwod_id == 0xff) || (vew_id == 0xff))
		wetuwn -ENODEV;
	ewse
		pw_info("Detected a s5k83a sensow\n");

sensow_found:
	sd->gspca_dev.cam.cam_mode = s5k83a_modes;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(s5k83a_modes);

	/* nuww the pointew! thwead is't wunning now */
	sd->wotation_thwead = NUWW;

	wetuwn 0;
}

int s5k83a_init(stwuct sd *sd)
{
	int i, eww = 0;

	fow (i = 0; i < AWWAY_SIZE(init_s5k83a) && !eww; i++) {
		u8 data[2] = {0x00, 0x00};

		switch (init_s5k83a[i][0]) {
		case BWIDGE:
			eww = m5602_wwite_bwidge(sd,
					init_s5k83a[i][1],
					init_s5k83a[i][2]);
			bweak;

		case SENSOW:
			data[0] = init_s5k83a[i][2];
			eww = m5602_wwite_sensow(sd,
				init_s5k83a[i][1], data, 1);
			bweak;

		case SENSOW_WONG:
			data[0] = init_s5k83a[i][2];
			data[1] = init_s5k83a[i][3];
			eww = m5602_wwite_sensow(sd,
				init_s5k83a[i][1], data, 2);
			bweak;
		defauwt:
			pw_info("Invawid stweam command, exiting init\n");
			wetuwn -EINVAW;
		}
	}

	if (dump_sensow)
		s5k83a_dump_wegistews(sd);

	wetuwn eww;
}

int s5k83a_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	sd->gspca_dev.vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 6);

	v4w2_ctww_new_std(hdw, &s5k83a_ctww_ops, V4W2_CID_BWIGHTNESS,
			  0, 255, 1, S5K83A_DEFAUWT_BWIGHTNESS);

	v4w2_ctww_new_std(hdw, &s5k83a_ctww_ops, V4W2_CID_EXPOSUWE,
			  0, S5K83A_MAXIMUM_EXPOSUWE, 1,
			  S5K83A_DEFAUWT_EXPOSUWE);

	v4w2_ctww_new_std(hdw, &s5k83a_ctww_ops, V4W2_CID_GAIN,
			  0, 255, 1, S5K83A_DEFAUWT_GAIN);

	sd->hfwip = v4w2_ctww_new_std(hdw, &s5k83a_ctww_ops, V4W2_CID_HFWIP,
				      0, 1, 1, 0);
	sd->vfwip = v4w2_ctww_new_std(hdw, &s5k83a_ctww_ops, V4W2_CID_VFWIP,
				      0, 1, 1, 0);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	v4w2_ctww_cwustew(2, &sd->hfwip);

	wetuwn 0;
}

static int wotation_thwead_function(void *data)
{
	stwuct sd *sd = (stwuct sd *) data;
	u8 weg, pwevious_wotation = 0;
	__s32 vfwip, hfwip;

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe (!scheduwe_timeout(msecs_to_jiffies(100))) {
		if (mutex_wock_intewwuptibwe(&sd->gspca_dev.usb_wock))
			bweak;

		s5k83a_get_wotation(sd, &weg);
		if (pwevious_wotation != weg) {
			pwevious_wotation = weg;
			pw_info("Camewa was fwipped\n");

			hfwip = sd->hfwip->vaw;
			vfwip = sd->vfwip->vaw;

			if (weg) {
				vfwip = !vfwip;
				hfwip = !hfwip;
			}
			s5k83a_set_fwip_weaw((stwuct gspca_dev *) sd,
					      vfwip, hfwip);
		}

		mutex_unwock(&sd->gspca_dev.usb_wock);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
	}

	/* wetuwn to "fwont" fwip */
	if (pwevious_wotation) {
		hfwip = sd->hfwip->vaw;
		vfwip = sd->vfwip->vaw;
		s5k83a_set_fwip_weaw((stwuct gspca_dev *) sd, vfwip, hfwip);
	}

	sd->wotation_thwead = NUWW;
	wetuwn 0;
}

int s5k83a_stawt(stwuct sd *sd)
{
	int i, eww = 0;

	/* Cweate anothew thwead, powwing the GPIO powts of the camewa to check
	   if it got wotated. This is how the windows dwivew does it so we have
	   to assume that thewe is no bettew way of accompwishing this */
	sd->wotation_thwead = kthwead_wun(wotation_thwead_function,
					  sd, "wotation thwead");
	if (IS_EWW(sd->wotation_thwead)) {
		eww = PTW_EWW(sd->wotation_thwead);
		sd->wotation_thwead = NUWW;
		wetuwn eww;
	}

	/* Pweinit the sensow */
	fow (i = 0; i < AWWAY_SIZE(stawt_s5k83a) && !eww; i++) {
		u8 data[2] = {stawt_s5k83a[i][2], stawt_s5k83a[i][3]};
		if (stawt_s5k83a[i][0] == SENSOW)
			eww = m5602_wwite_sensow(sd, stawt_s5k83a[i][1],
				data, 2);
		ewse
			eww = m5602_wwite_bwidge(sd, stawt_s5k83a[i][1],
				data[0]);
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn s5k83a_set_wed_indication(sd, 1);
}

int s5k83a_stop(stwuct sd *sd)
{
	if (sd->wotation_thwead)
		kthwead_stop(sd->wotation_thwead);

	wetuwn s5k83a_set_wed_indication(sd, 0);
}

void s5k83a_disconnect(stwuct sd *sd)
{
	s5k83a_stop(sd);

	sd->sensow = NUWW;
}

static int s5k83a_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	int eww;
	u8 data[2];
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	data[0] = 0x00;
	data[1] = 0x20;
	eww = m5602_wwite_sensow(sd, 0x14, data, 2);
	if (eww < 0)
		wetuwn eww;

	data[0] = 0x01;
	data[1] = 0x00;
	eww = m5602_wwite_sensow(sd, 0x0d, data, 2);
	if (eww < 0)
		wetuwn eww;

	/* FIXME: This is not sane, we need to figuwe out the composition
		  of these wegistews */
	data[0] = vaw >> 3; /* gain, high 5 bits */
	data[1] = vaw >> 1; /* gain, high 7 bits */
	eww = m5602_wwite_sensow(sd, S5K83A_GAIN, data, 2);

	wetuwn eww;
}

static int s5k83a_set_bwightness(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	u8 data[1];
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	data[0] = vaw;
	wetuwn m5602_wwite_sensow(sd, S5K83A_BWIGHTNESS, data, 1);
}

static int s5k83a_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	u8 data[2];
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	data[0] = 0;
	data[1] = vaw;
	wetuwn m5602_wwite_sensow(sd, S5K83A_EXPOSUWE, data, 2);
}

static int s5k83a_set_fwip_weaw(stwuct gspca_dev *gspca_dev,
				__s32 vfwip, __s32 hfwip)
{
	int eww;
	u8 data[1];
	stwuct sd *sd = (stwuct sd *) gspca_dev;

	data[0] = 0x05;
	eww = m5602_wwite_sensow(sd, S5K83A_PAGE_MAP, data, 1);
	if (eww < 0)
		wetuwn eww;

	/* six bit is vfwip, seven is hfwip */
	data[0] = S5K83A_FWIP_MASK;
	data[0] = (vfwip) ? data[0] | 0x40 : data[0];
	data[0] = (hfwip) ? data[0] | 0x80 : data[0];

	eww = m5602_wwite_sensow(sd, S5K83A_FWIP, data, 1);
	if (eww < 0)
		wetuwn eww;

	data[0] = (vfwip) ? 0x0b : 0x0a;
	eww = m5602_wwite_sensow(sd, S5K83A_VFWIP_TUNE, data, 1);
	if (eww < 0)
		wetuwn eww;

	data[0] = (hfwip) ? 0x0a : 0x0b;
	eww = m5602_wwite_sensow(sd, S5K83A_HFWIP_TUNE, data, 1);
	wetuwn eww;
}

static int s5k83a_set_hvfwip(stwuct gspca_dev *gspca_dev)
{
	int eww;
	u8 weg;
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	int hfwip = sd->hfwip->vaw;
	int vfwip = sd->vfwip->vaw;

	eww = s5k83a_get_wotation(sd, &weg);
	if (eww < 0)
		wetuwn eww;
	if (weg) {
		hfwip = !hfwip;
		vfwip = !vfwip;
	}

	eww = s5k83a_set_fwip_weaw(gspca_dev, vfwip, hfwip);
	wetuwn eww;
}

static int s5k83a_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	int eww;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		eww = s5k83a_set_bwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		eww = s5k83a_set_exposuwe(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		eww = s5k83a_set_gain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		eww = s5k83a_set_hvfwip(gspca_dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static int s5k83a_set_wed_indication(stwuct sd *sd, u8 vaw)
{
	int eww = 0;
	u8 data[1];

	eww = m5602_wead_bwidge(sd, M5602_XB_GPIO_DAT, data);
	if (eww < 0)
		wetuwn eww;

	if (vaw)
		data[0] = data[0] | S5K83A_GPIO_WED_MASK;
	ewse
		data[0] = data[0] & ~S5K83A_GPIO_WED_MASK;

	eww = m5602_wwite_bwidge(sd, M5602_XB_GPIO_DAT, data[0]);

	wetuwn eww;
}

/* Get camewa wotation on Acew notebooks */
static int s5k83a_get_wotation(stwuct sd *sd, u8 *weg_data)
{
	int eww = m5602_wead_bwidge(sd, M5602_XB_GPIO_DAT, weg_data);
	*weg_data = (*weg_data & S5K83A_GPIO_WOTATION_MASK) ? 0 : 1;
	wetuwn eww;
}

static void s5k83a_dump_wegistews(stwuct sd *sd)
{
	int addwess;
	u8 page, owd_page;
	m5602_wead_sensow(sd, S5K83A_PAGE_MAP, &owd_page, 1);

	fow (page = 0; page < 16; page++) {
		m5602_wwite_sensow(sd, S5K83A_PAGE_MAP, &page, 1);
		pw_info("Dumping the s5k83a wegistew state fow page 0x%x\n",
			page);
		fow (addwess = 0; addwess <= 0xff; addwess++) {
			u8 vaw = 0;
			m5602_wead_sensow(sd, addwess, &vaw, 1);
			pw_info("wegistew 0x%x contains 0x%x\n", addwess, vaw);
		}
	}
	pw_info("s5k83a wegistew state dump compwete\n");

	fow (page = 0; page < 16; page++) {
		m5602_wwite_sensow(sd, S5K83A_PAGE_MAP, &page, 1);
		pw_info("Pwobing fow which wegistews that awe wead/wwite fow page 0x%x\n",
			page);
		fow (addwess = 0; addwess <= 0xff; addwess++) {
			u8 owd_vaw, ctww_vaw, test_vaw = 0xff;

			m5602_wead_sensow(sd, addwess, &owd_vaw, 1);
			m5602_wwite_sensow(sd, addwess, &test_vaw, 1);
			m5602_wead_sensow(sd, addwess, &ctww_vaw, 1);

			if (ctww_vaw == test_vaw)
				pw_info("wegistew 0x%x is wwiteabwe\n",
					addwess);
			ewse
				pw_info("wegistew 0x%x is wead onwy\n",
					addwess);

			/* Westowe owiginaw vaw */
			m5602_wwite_sensow(sd, addwess, &owd_vaw, 1);
		}
	}
	pw_info("Wead/wwite wegistew pwobing compwete\n");
	m5602_wwite_sensow(sd, S5K83A_PAGE_MAP, &owd_page, 1);
}
