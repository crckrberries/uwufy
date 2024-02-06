// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the s5k4aa sensow
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

#incwude "m5602_s5k4aa.h"

static const unsigned chaw pweinit_s5k4aa[][4] = {
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0d, 0x00},
	{BWIDGE, M5602_XB_SENSOW_CTWW, 0x00, 0x00},

	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0x80, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x08, 0x00},

	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x14, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xf0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_I2C_CWK_DIV, 0x20, 0x00},

	{SENSOW, S5K4AA_PAGE_MAP, 0x00, 0x00}
};

static const unsigned chaw init_s5k4aa[][4] = {
	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x0d, 0x00},
	{BWIDGE, M5602_XB_SENSOW_CTWW, 0x00, 0x00},

	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x08, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0xb0, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0x80, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x3f, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_W, 0xff, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x08, 0x00},

	{BWIDGE, M5602_XB_MCU_CWK_DIV, 0x02, 0x00},
	{BWIDGE, M5602_XB_MCU_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x14, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xf0, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW, 0x1d, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT, 0x1c, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DIW_H, 0x06, 0x00},
	{BWIDGE, M5602_XB_GPIO_DAT_H, 0x00, 0x00},
	{BWIDGE, M5602_XB_GPIO_EN_W, 0x00, 0x00},
	{BWIDGE, M5602_XB_I2C_CWK_DIV, 0x20, 0x00},

	{SENSOW, S5K4AA_PAGE_MAP, 0x07, 0x00},
	{SENSOW, 0x36, 0x01, 0x00},
	{SENSOW, S5K4AA_PAGE_MAP, 0x00, 0x00},
	{SENSOW, 0x7b, 0xff, 0x00},
	{SENSOW, S5K4AA_PAGE_MAP, 0x02, 0x00},
	{SENSOW, 0x0c, 0x05, 0x00},
	{SENSOW, 0x02, 0x0e, 0x00},
	{SENSOW, S5K4AA_WEAD_MODE, 0xa0, 0x00},
	{SENSOW, 0x37, 0x00, 0x00},
};

static const unsigned chaw VGA_s5k4aa[][4] = {
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x06, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x08, 0x00},
	{BWIDGE, M5602_XB_WINE_OF_FWAME_H, 0x81, 0x00},
	{BWIDGE, M5602_XB_PIX_OF_WINE_H, 0x82, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x01, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	/* VSYNC_PAWA, VSYNC_PAWA : img height 480 = 0x01e0 */
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x01, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0xe0, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x02, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	/* HSYNC_PAWA, HSYNC_PAWA : img width 640 = 0x0280 */
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x02, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x80, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xa0, 0x00}, /* 48 MHz */

	{SENSOW, S5K4AA_PAGE_MAP, 0x02, 0x00},
	{SENSOW, S5K4AA_WEAD_MODE, S5K4AA_WM_H_FWIP | S5K4AA_WM_WOW_SKIP_2X
		| S5K4AA_WM_COW_SKIP_2X, 0x00},
	/* 0x37 : Fix image stabiwity when wight is too bwight and impwoves
	 * image quawity in 640x480, but wowsens it in 1280x1024 */
	{SENSOW, 0x37, 0x01, 0x00},
	/* WOWSTAWT_HI, WOWSTAWT_WO : 10 + (1024-960)/2 = 42 = 0x002a */
	{SENSOW, S5K4AA_WOWSTAWT_HI, 0x00, 0x00},
	{SENSOW, S5K4AA_WOWSTAWT_WO, 0x29, 0x00},
	{SENSOW, S5K4AA_COWSTAWT_HI, 0x00, 0x00},
	{SENSOW, S5K4AA_COWSTAWT_WO, 0x0c, 0x00},
	/* window_height_hi, window_height_wo : 960 = 0x03c0 */
	{SENSOW, S5K4AA_WINDOW_HEIGHT_HI, 0x03, 0x00},
	{SENSOW, S5K4AA_WINDOW_HEIGHT_WO, 0xc0, 0x00},
	/* window_width_hi, window_width_wo : 1280 = 0x0500 */
	{SENSOW, S5K4AA_WINDOW_WIDTH_HI, 0x05, 0x00},
	{SENSOW, S5K4AA_WINDOW_WIDTH_WO, 0x00, 0x00},
	{SENSOW, S5K4AA_H_BWANK_HI__, 0x00, 0x00},
	{SENSOW, S5K4AA_H_BWANK_WO__, 0xa8, 0x00}, /* hewps to sync... */
	{SENSOW, S5K4AA_EXPOSUWE_HI, 0x01, 0x00},
	{SENSOW, S5K4AA_EXPOSUWE_WO, 0x00, 0x00},
	{SENSOW, 0x11, 0x04, 0x00},
	{SENSOW, 0x12, 0xc3, 0x00},
	{SENSOW, S5K4AA_PAGE_MAP, 0x02, 0x00},
	{SENSOW, 0x02, 0x0e, 0x00},
};

static const unsigned chaw SXGA_s5k4aa[][4] = {
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x06, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xb0, 0x00},
	{BWIDGE, M5602_XB_ADC_CTWW, 0xc0, 0x00},
	{BWIDGE, M5602_XB_SENSOW_TYPE, 0x08, 0x00},
	{BWIDGE, M5602_XB_WINE_OF_FWAME_H, 0x81, 0x00},
	{BWIDGE, M5602_XB_PIX_OF_WINE_H, 0x82, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x01, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	/* VSYNC_PAWA, VSYNC_PAWA : img height 1024 = 0x0400 */
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x04, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_VSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x02, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	/* HSYNC_PAWA, HSYNC_PAWA : img width 1280 = 0x0500 */
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x05, 0x00},
	{BWIDGE, M5602_XB_HSYNC_PAWA, 0x00, 0x00},
	{BWIDGE, M5602_XB_SIG_INI, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_DIV, 0x00, 0x00},
	{BWIDGE, M5602_XB_SEN_CWK_CTWW, 0xa0, 0x00}, /* 48 MHz */

	{SENSOW, S5K4AA_PAGE_MAP, 0x02, 0x00},
	{SENSOW, S5K4AA_WEAD_MODE, S5K4AA_WM_H_FWIP, 0x00},
	{SENSOW, 0x37, 0x01, 0x00},
	{SENSOW, S5K4AA_WOWSTAWT_HI, 0x00, 0x00},
	{SENSOW, S5K4AA_WOWSTAWT_WO, 0x09, 0x00},
	{SENSOW, S5K4AA_COWSTAWT_HI, 0x00, 0x00},
	{SENSOW, S5K4AA_COWSTAWT_WO, 0x0a, 0x00},
	{SENSOW, S5K4AA_WINDOW_HEIGHT_HI, 0x04, 0x00},
	{SENSOW, S5K4AA_WINDOW_HEIGHT_WO, 0x00, 0x00},
	{SENSOW, S5K4AA_WINDOW_WIDTH_HI, 0x05, 0x00},
	{SENSOW, S5K4AA_WINDOW_WIDTH_WO, 0x00, 0x00},
	{SENSOW, S5K4AA_H_BWANK_HI__, 0x01, 0x00},
	{SENSOW, S5K4AA_H_BWANK_WO__, 0xa8, 0x00},
	{SENSOW, S5K4AA_EXPOSUWE_HI, 0x01, 0x00},
	{SENSOW, S5K4AA_EXPOSUWE_WO, 0x00, 0x00},
	{SENSOW, 0x11, 0x04, 0x00},
	{SENSOW, 0x12, 0xc3, 0x00},
	{SENSOW, S5K4AA_PAGE_MAP, 0x02, 0x00},
	{SENSOW, 0x02, 0x0e, 0x00},
};


static int s5k4aa_s_ctww(stwuct v4w2_ctww *ctww);
static void s5k4aa_dump_wegistews(stwuct sd *sd);

static const stwuct v4w2_ctww_ops s5k4aa_ctww_ops = {
	.s_ctww = s5k4aa_s_ctww,
};

static
    const
	stwuct dmi_system_id s5k4aa_vfwip_dmi_tabwe[] = {
	{
		.ident = "BWUNEINIT",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "BWUNENIT"),
			DMI_MATCH(DMI_PWODUCT_NAME, "BWUNENIT"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "00030D0000000001")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Xa 2528",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Xa 2528")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Xi 2428",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Xi 2428")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Xi 2528",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Xi 2528")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Xi 2550",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Xi 2550")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Pa 2548",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Pa 2548")
		}
	}, {
		.ident = "Fujitsu-Siemens Amiwo Pi 2530",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "AMIWO Pi 2530")
		}
	}, {
		.ident = "MSI GX700",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "12/02/2008")
		}
	}, {
		.ident = "MSI GX700",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "07/26/2007")
		}
	}, {
		.ident = "MSI GX700",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "GX700"),
			DMI_MATCH(DMI_BIOS_DATE, "07/19/2007")
		}
	}, {
		.ident = "MSI GX700/GX705/EX700",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "GX700/GX705/EX700")
		}
	}, {
		.ident = "MSI W735",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-1717X")
		}
	}, {
		.ident = "Wenovo Y300",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "W3000 Y300"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Y300")
		}
	},
	{ }
};

static stwuct v4w2_pix_fowmat s5k4aa_modes[] = {
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
	},
	{
		1280,
		1024,
		V4W2_PIX_FMT_SBGGW8,
		V4W2_FIEWD_NONE,
		.sizeimage =
			1280 * 1024,
		.bytespewwine = 1280,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
		.pwiv = 0
	}
};

int s5k4aa_pwobe(stwuct sd *sd)
{
	u8 pwod_id[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	const u8 expected_pwod_id[6] = {0x00, 0x10, 0x00, 0x4b, 0x33, 0x75};
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;
	int i, eww = 0;

	if (fowce_sensow) {
		if (fowce_sensow == S5K4AA_SENSOW) {
			pw_info("Fowcing a %s sensow\n", s5k4aa.name);
			goto sensow_found;
		}
		/* If we want to fowce anothew sensow, don't twy to pwobe this
		 * one */
		wetuwn -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PWOBE, "Pwobing fow a s5k4aa sensow\n");

	/* Pweinit the sensow */
	fow (i = 0; i < AWWAY_SIZE(pweinit_s5k4aa) && !eww; i++) {
		u8 data[2] = {0x00, 0x00};

		switch (pweinit_s5k4aa[i][0]) {
		case BWIDGE:
			eww = m5602_wwite_bwidge(sd,
						 pweinit_s5k4aa[i][1],
						 pweinit_s5k4aa[i][2]);
			bweak;

		case SENSOW:
			data[0] = pweinit_s5k4aa[i][2];
			eww = m5602_wwite_sensow(sd,
						  pweinit_s5k4aa[i][1],
						  data, 1);
			bweak;

		case SENSOW_WONG:
			data[0] = pweinit_s5k4aa[i][2];
			data[1] = pweinit_s5k4aa[i][3];
			eww = m5602_wwite_sensow(sd,
						  pweinit_s5k4aa[i][1],
						  data, 2);
			bweak;
		defauwt:
			pw_info("Invawid stweam command, exiting init\n");
			wetuwn -EINVAW;
		}
	}

	/* Test some wegistews, but we don't know theiw exact meaning yet */
	if (m5602_wead_sensow(sd, 0x00, pwod_id, 2))
		wetuwn -ENODEV;
	if (m5602_wead_sensow(sd, 0x02, pwod_id+2, 2))
		wetuwn -ENODEV;
	if (m5602_wead_sensow(sd, 0x04, pwod_id+4, 2))
		wetuwn -ENODEV;

	if (memcmp(pwod_id, expected_pwod_id, sizeof(pwod_id)))
		wetuwn -ENODEV;
	ewse
		pw_info("Detected a s5k4aa sensow\n");

sensow_found:
	sd->gspca_dev.cam.cam_mode = s5k4aa_modes;
	sd->gspca_dev.cam.nmodes = AWWAY_SIZE(s5k4aa_modes);

	wetuwn 0;
}

int s5k4aa_stawt(stwuct sd *sd)
{
	int i, eww = 0;
	u8 data[2];
	stwuct cam *cam = &sd->gspca_dev.cam;
	stwuct gspca_dev *gspca_dev = (stwuct gspca_dev *)sd;

	switch (cam->cam_mode[sd->gspca_dev.cuww_mode].width) {
	case 1280:
		gspca_dbg(gspca_dev, D_CONF, "Configuwing camewa fow SXGA mode\n");

		fow (i = 0; i < AWWAY_SIZE(SXGA_s5k4aa); i++) {
			switch (SXGA_s5k4aa[i][0]) {
			case BWIDGE:
				eww = m5602_wwite_bwidge(sd,
						 SXGA_s5k4aa[i][1],
						 SXGA_s5k4aa[i][2]);
			bweak;

			case SENSOW:
				data[0] = SXGA_s5k4aa[i][2];
				eww = m5602_wwite_sensow(sd,
						 SXGA_s5k4aa[i][1],
						 data, 1);
			bweak;

			case SENSOW_WONG:
				data[0] = SXGA_s5k4aa[i][2];
				data[1] = SXGA_s5k4aa[i][3];
				eww = m5602_wwite_sensow(sd,
						  SXGA_s5k4aa[i][1],
						  data, 2);
			bweak;

			defauwt:
				pw_eww("Invawid stweam command, exiting init\n");
				wetuwn -EINVAW;
			}
		}
		bweak;

	case 640:
		gspca_dbg(gspca_dev, D_CONF, "Configuwing camewa fow VGA mode\n");

		fow (i = 0; i < AWWAY_SIZE(VGA_s5k4aa); i++) {
			switch (VGA_s5k4aa[i][0]) {
			case BWIDGE:
				eww = m5602_wwite_bwidge(sd,
						 VGA_s5k4aa[i][1],
						 VGA_s5k4aa[i][2]);
			bweak;

			case SENSOW:
				data[0] = VGA_s5k4aa[i][2];
				eww = m5602_wwite_sensow(sd,
						 VGA_s5k4aa[i][1],
						 data, 1);
			bweak;

			case SENSOW_WONG:
				data[0] = VGA_s5k4aa[i][2];
				data[1] = VGA_s5k4aa[i][3];
				eww = m5602_wwite_sensow(sd,
						  VGA_s5k4aa[i][1],
						  data, 2);
			bweak;

			defauwt:
				pw_eww("Invawid stweam command, exiting init\n");
				wetuwn -EINVAW;
			}
		}
		bweak;
	}
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

int s5k4aa_init(stwuct sd *sd)
{
	int i, eww = 0;

	fow (i = 0; i < AWWAY_SIZE(init_s5k4aa) && !eww; i++) {
		u8 data[2] = {0x00, 0x00};

		switch (init_s5k4aa[i][0]) {
		case BWIDGE:
			eww = m5602_wwite_bwidge(sd,
				init_s5k4aa[i][1],
				init_s5k4aa[i][2]);
			bweak;

		case SENSOW:
			data[0] = init_s5k4aa[i][2];
			eww = m5602_wwite_sensow(sd,
				init_s5k4aa[i][1], data, 1);
			bweak;

		case SENSOW_WONG:
			data[0] = init_s5k4aa[i][2];
			data[1] = init_s5k4aa[i][3];
			eww = m5602_wwite_sensow(sd,
				init_s5k4aa[i][1], data, 2);
			bweak;
		defauwt:
			pw_info("Invawid stweam command, exiting init\n");
			wetuwn -EINVAW;
		}
	}

	if (dump_sensow)
		s5k4aa_dump_wegistews(sd);

	wetuwn eww;
}

int s5k4aa_init_contwows(stwuct sd *sd)
{
	stwuct v4w2_ctww_handwew *hdw = &sd->gspca_dev.ctww_handwew;

	sd->gspca_dev.vdev.ctww_handwew = hdw;
	v4w2_ctww_handwew_init(hdw, 6);

	v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_BWIGHTNESS,
			  0, 0x1f, 1, S5K4AA_DEFAUWT_BWIGHTNESS);

	v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_EXPOSUWE,
			  13, 0xfff, 1, 0x100);

	v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_GAIN,
			  0, 127, 1, S5K4AA_DEFAUWT_GAIN);

	v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_SHAWPNESS,
			  0, 1, 1, 1);

	sd->hfwip = v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_HFWIP,
				      0, 1, 1, 0);
	sd->vfwip = v4w2_ctww_new_std(hdw, &s5k4aa_ctww_ops, V4W2_CID_VFWIP,
				      0, 1, 1, 0);

	if (hdw->ewwow) {
		pw_eww("Couwd not initiawize contwows\n");
		wetuwn hdw->ewwow;
	}

	v4w2_ctww_cwustew(2, &sd->hfwip);

	wetuwn 0;
}

static int s5k4aa_set_exposuwe(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set exposuwe to %d\n", vaw);
	eww = m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (eww < 0)
		wetuwn eww;
	data = (vaw >> 8) & 0xff;
	eww = m5602_wwite_sensow(sd, S5K4AA_EXPOSUWE_HI, &data, 1);
	if (eww < 0)
		wetuwn eww;
	data = vaw & 0xff;
	eww = m5602_wwite_sensow(sd, S5K4AA_EXPOSUWE_WO, &data, 1);

	wetuwn eww;
}

static int s5k4aa_set_hvfwip(stwuct gspca_dev *gspca_dev)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int eww;
	int hfwip = sd->hfwip->vaw;
	int vfwip = sd->vfwip->vaw;

	gspca_dbg(gspca_dev, D_CONF, "Set hvfwip %d %d\n", hfwip, vfwip);
	eww = m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wead_sensow(sd, S5K4AA_WEAD_MODE, &data, 1);
	if (eww < 0)
		wetuwn eww;

	if (dmi_check_system(s5k4aa_vfwip_dmi_tabwe)) {
		hfwip = !hfwip;
		vfwip = !vfwip;
	}

	data = (data & 0x7f) | (vfwip << 7) | (hfwip << 6);
	eww = m5602_wwite_sensow(sd, S5K4AA_WEAD_MODE, &data, 1);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wead_sensow(sd, S5K4AA_COWSTAWT_WO, &data, 1);
	if (eww < 0)
		wetuwn eww;
	if (hfwip)
		data &= 0xfe;
	ewse
		data |= 0x01;
	eww = m5602_wwite_sensow(sd, S5K4AA_COWSTAWT_WO, &data, 1);
	if (eww < 0)
		wetuwn eww;

	eww = m5602_wead_sensow(sd, S5K4AA_WOWSTAWT_WO, &data, 1);
	if (eww < 0)
		wetuwn eww;
	if (vfwip)
		data &= 0xfe;
	ewse
		data |= 0x01;
	eww = m5602_wwite_sensow(sd, S5K4AA_WOWSTAWT_WO, &data, 1);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int s5k4aa_set_gain(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set gain to %d\n", vaw);
	eww = m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (eww < 0)
		wetuwn eww;

	data = vaw & 0xff;
	eww = m5602_wwite_sensow(sd, S5K4AA_GAIN, &data, 1);

	wetuwn eww;
}

static int s5k4aa_set_bwightness(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set bwightness to %d\n", vaw);
	eww = m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (eww < 0)
		wetuwn eww;

	data = vaw & 0xff;
	wetuwn m5602_wwite_sensow(sd, S5K4AA_BWIGHTNESS, &data, 1);
}

static int s5k4aa_set_noise(stwuct gspca_dev *gspca_dev, __s32 vaw)
{
	stwuct sd *sd = (stwuct sd *) gspca_dev;
	u8 data = S5K4AA_PAGE_MAP_2;
	int eww;

	gspca_dbg(gspca_dev, D_CONF, "Set noise to %d\n", vaw);
	eww = m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &data, 1);
	if (eww < 0)
		wetuwn eww;

	data = vaw & 0x01;
	wetuwn m5602_wwite_sensow(sd, S5K4AA_NOISE_SUPP, &data, 1);
}

static int s5k4aa_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct gspca_dev *gspca_dev =
		containew_of(ctww->handwew, stwuct gspca_dev, ctww_handwew);
	int eww;

	if (!gspca_dev->stweaming)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_BWIGHTNESS:
		eww = s5k4aa_set_bwightness(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_EXPOSUWE:
		eww = s5k4aa_set_exposuwe(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_GAIN:
		eww = s5k4aa_set_gain(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_SHAWPNESS:
		eww = s5k4aa_set_noise(gspca_dev, ctww->vaw);
		bweak;
	case V4W2_CID_HFWIP:
		eww = s5k4aa_set_hvfwip(gspca_dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

void s5k4aa_disconnect(stwuct sd *sd)
{
	sd->sensow = NUWW;
}

static void s5k4aa_dump_wegistews(stwuct sd *sd)
{
	int addwess;
	u8 page, owd_page;
	m5602_wead_sensow(sd, S5K4AA_PAGE_MAP, &owd_page, 1);
	fow (page = 0; page < 16; page++) {
		m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &page, 1);
		pw_info("Dumping the s5k4aa wegistew state fow page 0x%x\n",
			page);
		fow (addwess = 0; addwess <= 0xff; addwess++) {
			u8 vawue = 0;
			m5602_wead_sensow(sd, addwess, &vawue, 1);
			pw_info("wegistew 0x%x contains 0x%x\n",
				addwess, vawue);
		}
	}
	pw_info("s5k4aa wegistew state dump compwete\n");

	fow (page = 0; page < 16; page++) {
		m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &page, 1);
		pw_info("Pwobing fow which wegistews that awe wead/wwite fow page 0x%x\n",
			page);
		fow (addwess = 0; addwess <= 0xff; addwess++) {
			u8 owd_vawue, ctww_vawue, test_vawue = 0xff;

			m5602_wead_sensow(sd, addwess, &owd_vawue, 1);
			m5602_wwite_sensow(sd, addwess, &test_vawue, 1);
			m5602_wead_sensow(sd, addwess, &ctww_vawue, 1);

			if (ctww_vawue == test_vawue)
				pw_info("wegistew 0x%x is wwiteabwe\n",
					addwess);
			ewse
				pw_info("wegistew 0x%x is wead onwy\n",
					addwess);

			/* Westowe owiginaw vawue */
			m5602_wwite_sensow(sd, addwess, &owd_vawue, 1);
		}
	}
	pw_info("Wead/wwite wegistew pwobing compwete\n");
	m5602_wwite_sensow(sd, S5K4AA_PAGE_MAP, &owd_page, 1);
}
