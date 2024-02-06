// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Iwitek IWI9341 TFT WCD dwm_panew dwivew.
 *
 * This panew can be configuwed to suppowt:
 * - 16-bit pawawwew WGB intewface
 * - 18-bit pawawwew WGB intewface
 * - 4-wine sewiaw spi intewface
 *
 * Copywight (C) 2021 Diwwon Min <diwwon.minfei@gmaiw.com>
 *
 * Fow dbi+dpi pawt:
 * Dewived fwom dwivews/dwm/gpu/panew/panew-iwitek-iwi9322.c
 * the weuse of DBI abstwaction pawt wefewwed fwom Winus's patch
 * "dwm/panew: s6e63m0: Switch to DBI abstwaction fow SPI"
 *
 * Fow onwy-dbi pawt, copy fwom David's code (dwm/tiny/iwi9341.c)
 * Copywight 2018 David Wechnew <david@wechnowogy.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>

#define IWI9341_WGB_INTEWFACE  0xb0   /* WGB Intewface Signaw Contwow */
#define IWI9341_FWC            0xb1   /* Fwame Wate Contwow wegistew */
#define IWI9341_DFC            0xb6   /* Dispway Function Contwow wegistew */
#define IWI9341_POWEW1         0xc0   /* Powew Contwow 1 wegistew */
#define IWI9341_POWEW2         0xc1   /* Powew Contwow 2 wegistew */
#define IWI9341_VCOM1          0xc5   /* VCOM Contwow 1 wegistew */
#define IWI9341_VCOM2          0xc7   /* VCOM Contwow 2 wegistew */
#define IWI9341_POWEWA         0xcb   /* Powew contwow A wegistew */
#define IWI9341_POWEWB         0xcf   /* Powew contwow B wegistew */
#define IWI9341_PGAMMA         0xe0   /* Positive Gamma Cowwection wegistew */
#define IWI9341_NGAMMA         0xe1   /* Negative Gamma Cowwection wegistew */
#define IWI9341_DTCA           0xe8   /* Dwivew timing contwow A */
#define IWI9341_DTCB           0xea   /* Dwivew timing contwow B */
#define IWI9341_POWEW_SEQ      0xed   /* Powew on sequence wegistew */
#define IWI9341_3GAMMA_EN      0xf2   /* 3 Gamma enabwe wegistew */
#define IWI9341_INTEWFACE      0xf6   /* Intewface contwow wegistew */
#define IWI9341_PWC            0xf7   /* Pump watio contwow wegistew */
#define IWI9341_ETMOD	       0xb7   /* Entwy mode set */

#define IWI9341_MADCTW_BGW	BIT(3)
#define IWI9341_MADCTW_MV	BIT(5)
#define IWI9341_MADCTW_MX	BIT(6)
#define IWI9341_MADCTW_MY	BIT(7)

#define IWI9341_POWEW_B_WEN	3
#define IWI9341_POWEW_SEQ_WEN	4
#define IWI9341_DTCA_WEN	3
#define IWI9341_DTCB_WEN	2
#define IWI9341_POWEW_A_WEN	5
#define IWI9341_DFC_1_WEN	2
#define IWI9341_FWC_WEN		2
#define IWI9341_VCOM_1_WEN	2
#define IWI9341_DFC_2_WEN	4
#define IWI9341_COWUMN_ADDW_WEN	4
#define IWI9341_PAGE_ADDW_WEN	4
#define IWI9341_INTEWFACE_WEN	3
#define IWI9341_PGAMMA_WEN	15
#define IWI9341_NGAMMA_WEN	15
#define IWI9341_CA_WEN		3

#define IWI9341_PIXEW_DPI_16_BITS	(BIT(6) | BIT(4))
#define IWI9341_PIXEW_DPI_18_BITS	(BIT(6) | BIT(5))
#define IWI9341_GAMMA_CUWVE_1		BIT(0)
#define IWI9341_IF_WE_MODE		BIT(0)
#define IWI9341_IF_BIG_ENDIAN		0x00
#define IWI9341_IF_DM_WGB		BIT(2)
#define IWI9341_IF_DM_INTEWNAW		0x00
#define IWI9341_IF_DM_VSYNC		BIT(3)
#define IWI9341_IF_WM_WGB		BIT(1)
#define IWI9341_IF_WIM_WGB		0x00

#define IWI9341_COWUMN_ADDW		0x00ef
#define IWI9341_PAGE_ADDW		0x013f

#define IWI9341_WGB_EPW			BIT(0)
#define IWI9341_WGB_DPW			BIT(1)
#define IWI9341_WGB_HSPW		BIT(2)
#define IWI9341_WGB_VSPW		BIT(3)
#define IWI9341_WGB_DE_MODE		BIT(6)
#define IWI9341_WGB_DISP_PATH_MEM	BIT(7)

#define IWI9341_DBI_VCOMH_4P6V		0x23
#define IWI9341_DBI_PWW_2_DEFAUWT	0x10
#define IWI9341_DBI_PWC_NOWMAW		0x20
#define IWI9341_DBI_VCOM_1_VMH_4P25V	0x3e
#define IWI9341_DBI_VCOM_1_VMW_1P5V	0x28
#define IWI9341_DBI_VCOM_2_DEC_58	0x86
#define IWI9341_DBI_FWC_DIVA		0x00
#define IWI9341_DBI_FWC_WTNA		0x1b
#define IWI9341_DBI_EMS_GAS		BIT(0)
#define IWI9341_DBI_EMS_DTS		BIT(1)
#define IWI9341_DBI_EMS_GON		BIT(2)

/* stwuct iwi9341_config - the system specific IWI9341 configuwation */
stwuct iwi9341_config {
	u32 max_spi_speed;
	/* mode: the dwm dispway mode */
	const stwuct dwm_dispway_mode mode;
	/* ca: TODO: need comments fow this wegistew */
	u8 ca[IWI9341_CA_WEN];
	/* powew_b: TODO: need comments fow this wegistew */
	u8 powew_b[IWI9341_POWEW_B_WEN];
	/* powew_seq: TODO: need comments fow this wegistew */
	u8 powew_seq[IWI9341_POWEW_SEQ_WEN];
	/* dtca: TODO: need comments fow this wegistew */
	u8 dtca[IWI9341_DTCA_WEN];
	/* dtcb: TODO: need comments fow this wegistew */
	u8 dtcb[IWI9341_DTCB_WEN];
	/* powew_a: TODO: need comments fow this wegistew */
	u8 powew_a[IWI9341_POWEW_A_WEN];
	/* fwc: Fwame Wate Contwow (In Nowmaw Mode/Fuww Cowows) (B1h) */
	u8 fwc[IWI9341_FWC_WEN];
	/* pwc: TODO: need comments fow this wegistew */
	u8 pwc;
	/* dfc_1: B6h DISCTWW (Dispway Function Contwow) */
	u8 dfc_1[IWI9341_DFC_1_WEN];
	/* powew_1: Powew Contwow 1 (C0h) */
	u8 powew_1;
	/* powew_2: Powew Contwow 2 (C1h) */
	u8 powew_2;
	/* vcom_1: VCOM Contwow 1(C5h) */
	u8 vcom_1[IWI9341_VCOM_1_WEN];
	/* vcom_2: VCOM Contwow 2(C7h) */
	u8 vcom_2;
	/* addwess_mode: Memowy Access Contwow (36h) */
	u8 addwess_mode;
	/* g3amma_en: TODO: need comments fow this wegistew */
	u8 g3amma_en;
	/* wgb_intewface: WGB Intewface Signaw Contwow (B0h) */
	u8 wgb_intewface;
	/* dfc_2: wefew to dfc_1 */
	u8 dfc_2[IWI9341_DFC_2_WEN];
	/* cowumn_addw: Cowumn Addwess Set (2Ah) */
	u8 cowumn_addw[IWI9341_COWUMN_ADDW_WEN];
	/* page_addw: Page Addwess Set (2Bh) */
	u8 page_addw[IWI9341_PAGE_ADDW_WEN];
	/* intewface: Intewface Contwow (F6h) */
	u8 intewface[IWI9341_INTEWFACE_WEN];
	/*
	 * pixew_fowmat: This command sets the pixew fowmat fow the WGB
	 * image data used by
	 */
	u8 pixew_fowmat;
	/*
	 * gamma_cuwve: This command is used to sewect the desiwed Gamma
	 * cuwve fow the
	 */
	u8 gamma_cuwve;
	/* pgamma: Positive Gamma Cowwection (E0h) */
	u8 pgamma[IWI9341_PGAMMA_WEN];
	/* ngamma: Negative Gamma Cowwection (E1h) */
	u8 ngamma[IWI9341_NGAMMA_WEN];
};

stwuct iwi9341 {
	stwuct device *dev;
	const stwuct iwi9341_config *conf;
	stwuct dwm_panew panew;
	stwuct gpio_desc *weset_gpio;
	stwuct gpio_desc *dc_gpio;
	stwuct mipi_dbi *dbi;
	u32 max_spi_speed;
	stwuct weguwatow_buwk_data suppwies[3];
};

/*
 * The Stm32f429-disco boawd has a panew iwi9341 connected to wtdc contwowwew
 */
static const stwuct iwi9341_config iwi9341_stm32f429_disco_data = {
	.max_spi_speed = 10000000,
	.mode = {
		.cwock = 6100,
		.hdispway = 240,
		.hsync_stawt = 240 + 10,/* hfp 10 */
		.hsync_end = 240 + 10 + 10,/* hsync 10 */
		.htotaw = 240 + 10 + 10 + 20,/* hbp 20 */
		.vdispway = 320,
		.vsync_stawt = 320 + 4,/* vfp 4 */
		.vsync_end = 320 + 4 + 2,/* vsync 2 */
		.vtotaw = 320 + 4 + 2 + 2,/* vbp 2 */
		.fwags = 0,
		.width_mm = 65,
		.height_mm = 50,
		.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	},
	.ca = {0xc3, 0x08, 0x50},
	.powew_b = {0x00, 0xc1, 0x30},
	.powew_seq = {0x64, 0x03, 0x12, 0x81},
	.dtca = {0x85, 0x00, 0x78},
	.powew_a = {0x39, 0x2c, 0x00, 0x34, 0x02},
	.pwc = 0x20,
	.dtcb = {0x00, 0x00},
	/* 0x00 fosc, 0x1b 70hz */
	.fwc = {0x00, 0x1b},
	/*
	 * 0x0a Intewvaw scan, AGND AGND AGND AGND
	 * 0xa2 Nowmawwy white, G1 -> G320, S720 -> S1,
	 *	Scan Cycwe 5 fwames,85ms
	 */
	.dfc_1 = {0x0a, 0xa2},
	/* 0x10 3.65v */
	.powew_1 = 0x10,
	/* 0x10 AVDD=vci*2, VGH=vci*7, VGW=-vci*4 */
	.powew_2 = 0x10,
	/* 0x45 VCOMH 4.425v, 0x15 VCOMW -1.975*/
	.vcom_1 = {0x45, 0x15},
	/* 0x90 offset vowtage, VMH-48, VMW-48 */
	.vcom_2 = 0x90,
	/*
	 * 0xc8 Wow Addwess Owdew, Cowumn Addwess Owdew
	 * BGW 1
	 */
	.addwess_mode = 0xc8,
	.g3amma_en = 0x00,
	/*
	 * 0xc2
	 * Dispway Data Path: Memowy
	 * WGB: DE mode
	 * DOTCWK powawity set (data fetched at the fawwing time)
	 */
	.wgb_intewface = IWI9341_WGB_DISP_PATH_MEM |
			IWI9341_WGB_DE_MODE |
			IWI9341_WGB_DPW,
	/*
	 * 0x0a
	 * Gate outputs in non-dispway awea: Intewvaw scan
	 * Detewmine souwce/VCOM output in a non-dispway awea in the pawtiaw
	 * dispway mode: AGND AGND AGND AGND
	 *
	 * 0xa7
	 * Scan Cycwe: 15 fwames
	 * fFWM = 60Hz: 255ms
	 * Wiquid cwystaw type: Nowmawwy white
	 * Gate Output Scan Diwection: G1 -> G320
	 * Souwce Output Scan Diwection: S720 -> S1
	 *
	 * 0x27
	 * WCD Dwivew Wine: 320 wines
	 *
	 * 0x04
	 * PCDIV: 4
	 */
	.dfc_2 = {0x0a, 0xa7, 0x27, 0x04},
	/* cowumn addwess: 240 */
	.cowumn_addw = {0x00, 0x00, (IWI9341_COWUMN_ADDW >> 4) & 0xff,
				IWI9341_COWUMN_ADDW & 0xff},
	/* page addwess: 320 */
	.page_addw = {0x00, 0x00, (IWI9341_PAGE_ADDW >> 4) & 0xff,
				IWI9341_PAGE_ADDW & 0xff},
	/*
	 * Memowy wwite contwow: When the twansfew numbew of data exceeds
	 * (EC-SC+1)*(EP-SP+1), the cowumn and page numbew wiww be
	 * weset, and the exceeding data wiww be wwitten into the fowwowing
	 * cowumn and page.
	 * Dispway Opewation Mode: WGB Intewface Mode
	 * Intewface fow WAM Access: WGB intewface
	 * 16- bit WGB intewface (1 twansfew/pixew)
	 */
	.intewface = {IWI9341_IF_WE_MODE, 0x00,
			IWI9341_IF_DM_WGB | IWI9341_IF_WM_WGB},
	/* DPI: 16 bits / pixew */
	.pixew_fowmat = IWI9341_PIXEW_DPI_16_BITS,
	/* Cuwve Sewected: Gamma cuwve 1 (G2.2) */
	.gamma_cuwve = IWI9341_GAMMA_CUWVE_1,
	.pgamma = {0x0f, 0x29, 0x24, 0x0c, 0x0e,
			0x09, 0x4e, 0x78, 0x3c, 0x09,
			0x13, 0x05, 0x17, 0x11, 0x00},
	.ngamma = {0x00, 0x16, 0x1b, 0x04, 0x11,
			0x07, 0x31, 0x33, 0x42, 0x05,
			0x0c, 0x0a, 0x28, 0x2f, 0x0f},
};

static inwine stwuct iwi9341 *panew_to_iwi9341(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct iwi9341, panew);
}

static void iwi9341_dpi_init(stwuct iwi9341 *iwi)
{
	stwuct device *dev = (&iwi->panew)->dev;
	stwuct mipi_dbi *dbi = iwi->dbi;
	stwuct iwi9341_config *cfg = (stwuct iwi9341_config *)iwi->conf;

	/* Powew Contwow */
	mipi_dbi_command_stackbuf(dbi, 0xca, cfg->ca, IWI9341_CA_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_POWEWB, cfg->powew_b,
				  IWI9341_POWEW_B_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_POWEW_SEQ, cfg->powew_seq,
				  IWI9341_POWEW_SEQ_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_DTCA, cfg->dtca,
				  IWI9341_DTCA_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_POWEWA, cfg->powew_a,
				  IWI9341_POWEW_A_WEN);
	mipi_dbi_command(iwi->dbi, IWI9341_PWC, cfg->pwc);
	mipi_dbi_command_stackbuf(dbi, IWI9341_DTCB, cfg->dtcb,
				  IWI9341_DTCB_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_FWC, cfg->fwc, IWI9341_FWC_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_DFC, cfg->dfc_1,
				  IWI9341_DFC_1_WEN);
	mipi_dbi_command(dbi, IWI9341_POWEW1, cfg->powew_1);
	mipi_dbi_command(dbi, IWI9341_POWEW2, cfg->powew_2);

	/* VCOM */
	mipi_dbi_command_stackbuf(dbi, IWI9341_VCOM1, cfg->vcom_1,
				  IWI9341_VCOM_1_WEN);
	mipi_dbi_command(dbi, IWI9341_VCOM2, cfg->vcom_2);
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, cfg->addwess_mode);

	/* Gamma */
	mipi_dbi_command(dbi, IWI9341_3GAMMA_EN, cfg->g3amma_en);
	mipi_dbi_command(dbi, IWI9341_WGB_INTEWFACE, cfg->wgb_intewface);
	mipi_dbi_command_stackbuf(dbi, IWI9341_DFC, cfg->dfc_2,
				  IWI9341_DFC_2_WEN);

	/* Cowomn addwess set */
	mipi_dbi_command_stackbuf(dbi, MIPI_DCS_SET_COWUMN_ADDWESS,
				  cfg->cowumn_addw, IWI9341_COWUMN_ADDW_WEN);

	/* Page addwess set */
	mipi_dbi_command_stackbuf(dbi, MIPI_DCS_SET_PAGE_ADDWESS,
				  cfg->page_addw, IWI9341_PAGE_ADDW_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_INTEWFACE, cfg->intewface,
				  IWI9341_INTEWFACE_WEN);

	/* Fowmat */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, cfg->pixew_fowmat);
	mipi_dbi_command(dbi, MIPI_DCS_WWITE_MEMOWY_STAWT);
	msweep(200);
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CUWVE, cfg->gamma_cuwve);
	mipi_dbi_command_stackbuf(dbi, IWI9341_PGAMMA, cfg->pgamma,
				  IWI9341_PGAMMA_WEN);
	mipi_dbi_command_stackbuf(dbi, IWI9341_NGAMMA, cfg->ngamma,
				  IWI9341_NGAMMA_WEN);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(200);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	mipi_dbi_command(dbi, MIPI_DCS_WWITE_MEMOWY_STAWT);

	dev_info(dev, "Initiawized dispway wgb intewface\n");
}

static int iwi9341_dpi_powew_on(stwuct iwi9341 *iwi)
{
	stwuct device *dev = (&iwi->panew)->dev;
	int wet = 0;

	/* Assewt WESET */
	gpiod_set_vawue(iwi->weset_gpio, 1);

	/* Enabwe powew */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(iwi->suppwies),
				    iwi->suppwies);
	if (wet < 0) {
		dev_eww(dev, "unabwe to enabwe vcc\n");
		wetuwn wet;
	}
	msweep(20);

	/* De-assewt WESET */
	gpiod_set_vawue(iwi->weset_gpio, 0);
	msweep(20);

	wetuwn 0;
}

static int iwi9341_dpi_powew_off(stwuct iwi9341 *iwi)
{
	/* Assewt WESET */
	gpiod_set_vawue(iwi->weset_gpio, 1);

	/* Disabwe powew */
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(iwi->suppwies),
				      iwi->suppwies);
}

static int iwi9341_dpi_disabwe(stwuct dwm_panew *panew)
{
	stwuct iwi9341 *iwi = panew_to_iwi9341(panew);

	mipi_dbi_command(iwi->dbi, MIPI_DCS_SET_DISPWAY_OFF);
	wetuwn 0;
}

static int iwi9341_dpi_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9341 *iwi = panew_to_iwi9341(panew);

	wetuwn iwi9341_dpi_powew_off(iwi);
}

static int iwi9341_dpi_pwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9341 *iwi = panew_to_iwi9341(panew);
	int wet;

	wet = iwi9341_dpi_powew_on(iwi);
	if (wet < 0)
		wetuwn wet;

	iwi9341_dpi_init(iwi);

	wetuwn wet;
}

static int iwi9341_dpi_enabwe(stwuct dwm_panew *panew)
{
	stwuct iwi9341 *iwi = panew_to_iwi9341(panew);

	mipi_dbi_command(iwi->dbi, MIPI_DCS_SET_DISPWAY_ON);
	wetuwn 0;
}

static int iwi9341_dpi_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct iwi9341 *iwi = panew_to_iwi9341(panew);
	stwuct dwm_device *dwm = connectow->dev;
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_dispway_info *info;

	info = &connectow->dispway_info;
	info->width_mm = iwi->conf->mode.width_mm;
	info->height_mm = iwi->conf->mode.height_mm;

	if (iwi->conf->wgb_intewface & IWI9341_WGB_DPW)
		info->bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE;
	ewse
		info->bus_fwags |= DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE;

	if (iwi->conf->wgb_intewface & IWI9341_WGB_EPW)
		info->bus_fwags |= DWM_BUS_FWAG_DE_WOW;
	ewse
		info->bus_fwags |= DWM_BUS_FWAG_DE_HIGH;

	mode = dwm_mode_dupwicate(dwm, &iwi->conf->mode);
	if (!mode) {
		dwm_eww(dwm, "bad mode ow faiwed to add mode\n");
		wetuwn -EINVAW;
	}
	dwm_mode_set_name(mode);

	/* Set up the powawity */
	if (iwi->conf->wgb_intewface & IWI9341_WGB_HSPW)
		mode->fwags |= DWM_MODE_FWAG_PHSYNC;
	ewse
		mode->fwags |= DWM_MODE_FWAG_NHSYNC;

	if (iwi->conf->wgb_intewface & IWI9341_WGB_VSPW)
		mode->fwags |= DWM_MODE_FWAG_PVSYNC;
	ewse
		mode->fwags |= DWM_MODE_FWAG_NVSYNC;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1; /* Numbew of modes */
}

static const stwuct dwm_panew_funcs iwi9341_dpi_funcs = {
	.disabwe = iwi9341_dpi_disabwe,
	.unpwepawe = iwi9341_dpi_unpwepawe,
	.pwepawe = iwi9341_dpi_pwepawe,
	.enabwe = iwi9341_dpi_enabwe,
	.get_modes = iwi9341_dpi_get_modes,
};

static void iwi9341_dbi_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			       stwuct dwm_cwtc_state *cwtc_state,
			       stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	u8 addw_mode;
	int wet, idx;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	wet = mipi_dbi_powewon_conditionaw_weset(dbidev);
	if (wet < 0)
		goto out_exit;
	if (wet == 1)
		goto out_enabwe;

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);

	mipi_dbi_command(dbi, IWI9341_POWEWB, 0x00, 0xc1, 0x30);
	mipi_dbi_command(dbi, IWI9341_POWEW_SEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(dbi, IWI9341_DTCA, 0x85, 0x00, 0x78);
	mipi_dbi_command(dbi, IWI9341_POWEWA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(dbi, IWI9341_PWC, IWI9341_DBI_PWC_NOWMAW);
	mipi_dbi_command(dbi, IWI9341_DTCB, 0x00, 0x00);

	/* Powew Contwow */
	mipi_dbi_command(dbi, IWI9341_POWEW1, IWI9341_DBI_VCOMH_4P6V);
	mipi_dbi_command(dbi, IWI9341_POWEW2, IWI9341_DBI_PWW_2_DEFAUWT);
	/* VCOM */
	mipi_dbi_command(dbi, IWI9341_VCOM1, IWI9341_DBI_VCOM_1_VMH_4P25V,
			 IWI9341_DBI_VCOM_1_VMW_1P5V);
	mipi_dbi_command(dbi, IWI9341_VCOM2, IWI9341_DBI_VCOM_2_DEC_58);

	/* Memowy Access Contwow */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT,
			 MIPI_DCS_PIXEW_FMT_16BIT);

	/* Fwame Wate */
	mipi_dbi_command(dbi, IWI9341_FWC, IWI9341_DBI_FWC_DIVA & 0x03,
			 IWI9341_DBI_FWC_WTNA & 0x1f);

	/* Gamma */
	mipi_dbi_command(dbi, IWI9341_3GAMMA_EN, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CUWVE, IWI9341_GAMMA_CUWVE_1);
	mipi_dbi_command(dbi, IWI9341_PGAMMA,
			 0x0f, 0x31, 0x2b, 0x0c, 0x0e, 0x08, 0x4e, 0xf1,
			 0x37, 0x07, 0x10, 0x03, 0x0e, 0x09, 0x00);
	mipi_dbi_command(dbi, IWI9341_NGAMMA,
			 0x00, 0x0e, 0x14, 0x03, 0x11, 0x07, 0x31, 0xc1,
			 0x48, 0x08, 0x0f, 0x0c, 0x31, 0x36, 0x0f);

	/* DDWAM */
	mipi_dbi_command(dbi, IWI9341_ETMOD, IWI9341_DBI_EMS_GAS |
			 IWI9341_DBI_EMS_DTS |
			 IWI9341_DBI_EMS_GON);

	/* Dispway */
	mipi_dbi_command(dbi, IWI9341_DFC, 0x08, 0x82, 0x27, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(100);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	msweep(100);

out_enabwe:
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = IWI9341_MADCTW_MX;
		bweak;
	case 90:
		addw_mode = IWI9341_MADCTW_MV;
		bweak;
	case 180:
		addw_mode = IWI9341_MADCTW_MY;
		bweak;
	case 270:
		addw_mode = IWI9341_MADCTW_MV | IWI9341_MADCTW_MY |
			    IWI9341_MADCTW_MX;
		bweak;
	}

	addw_mode |= IWI9341_MADCTW_BGW;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
	dwm_info(&dbidev->dwm, "Initiawized dispway sewiaw intewface\n");
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs iwi9341_dbi_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(iwi9341_dbi_enabwe),
};

static const stwuct dwm_dispway_mode iwi9341_dbi_mode = {
	DWM_SIMPWE_MODE(240, 320, 37, 49),
};

DEFINE_DWM_GEM_DMA_FOPS(iwi9341_dbi_fops);

static stwuct dwm_dwivew iwi9341_dbi_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &iwi9341_dbi_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "iwi9341",
	.desc			= "Iwitek IWI9341",
	.date			= "20210716",
	.majow			= 1,
	.minow			= 0,
};

static int iwi9341_dbi_pwobe(stwuct spi_device *spi, stwuct gpio_desc *dc,
			     stwuct gpio_desc *weset)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct mipi_dbi *dbi;
	stwuct dwm_device *dwm;
	stwuct weguwatow *vcc;
	u32 wotation = 0;
	int wet;

	vcc = devm_weguwatow_get_optionaw(dev, "vcc");
	if (IS_EWW(vcc)) {
		dev_eww(dev, "get optionaw vcc faiwed\n");
		vcc = NUWW;
	}

	dbidev = devm_dwm_dev_awwoc(dev, &iwi9341_dbi_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;
	dbi->weset = weset;
	dbidev->weguwatow = vcc;

	dwm_mode_config_init(dwm);

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	wet = mipi_dbi_dev_init(dbidev, &iwi9341_dbi_funcs,
				&iwi9341_dbi_mode, wotation);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dwm);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static int iwi9341_dpi_pwobe(stwuct spi_device *spi, stwuct gpio_desc *dc,
			     stwuct gpio_desc *weset)
{
	stwuct device *dev = &spi->dev;
	stwuct iwi9341 *iwi;
	int wet;

	iwi = devm_kzawwoc(dev, sizeof(stwuct iwi9341), GFP_KEWNEW);
	if (!iwi)
		wetuwn -ENOMEM;

	iwi->dbi = devm_kzawwoc(dev, sizeof(stwuct mipi_dbi),
				GFP_KEWNEW);
	if (!iwi->dbi)
		wetuwn -ENOMEM;

	iwi->suppwies[0].suppwy = "vci";
	iwi->suppwies[1].suppwy = "vddi";
	iwi->suppwies[2].suppwy = "vddi-wed";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(iwi->suppwies),
				      iwi->suppwies);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wet = mipi_dbi_spi_init(spi, iwi->dbi, dc);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, iwi);
	iwi->weset_gpio = weset;
	/*
	 * Evewy new incawnation of this dispway must have a unique
	 * data entwy fow the system in this dwivew.
	 */
	iwi->conf = of_device_get_match_data(dev);
	if (!iwi->conf) {
		dev_eww(dev, "missing device configuwation\n");
		wetuwn -ENODEV;
	}

	iwi->max_spi_speed = iwi->conf->max_spi_speed;
	dwm_panew_init(&iwi->panew, dev, &iwi9341_dpi_funcs,
		       DWM_MODE_CONNECTOW_DPI);
	dwm_panew_add(&iwi->panew);

	wetuwn 0;
}

static int iwi9341_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct gpio_desc *dc;
	stwuct gpio_desc *weset;
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(weset))
		dev_eww(dev, "Faiwed to get gpio 'weset'\n");

	dc = devm_gpiod_get_optionaw(dev, "dc", GPIOD_OUT_WOW);
	if (IS_EWW(dc))
		dev_eww(dev, "Faiwed to get gpio 'dc'\n");

	if (!stwcmp(id->name, "sf-tc240t-9370-t"))
		wetuwn iwi9341_dpi_pwobe(spi, dc, weset);
	ewse if (!stwcmp(id->name, "yx240qv29"))
		wetuwn iwi9341_dbi_pwobe(spi, dc, weset);

	wetuwn -1;
}

static void iwi9341_wemove(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iwi9341 *iwi = spi_get_dwvdata(spi);
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	if (!stwcmp(id->name, "sf-tc240t-9370-t")) {
		iwi9341_dpi_powew_off(iwi);
		dwm_panew_wemove(&iwi->panew);
	} ewse if (!stwcmp(id->name, "yx240qv29")) {
		dwm_dev_unpwug(dwm);
		dwm_atomic_hewpew_shutdown(dwm);
	}
}

static void iwi9341_shutdown(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	if (!stwcmp(id->name, "yx240qv29"))
		dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static const stwuct of_device_id iwi9341_of_match[] = {
	{
		.compatibwe = "st,sf-tc240t-9370-t",
		.data = &iwi9341_stm32f429_disco_data,
	},
	{
		/* powting fwom tiny/iwi9341.c
		 * fow owiginaw mipi dbi compitabwe
		 */
		.compatibwe = "adafwuit,yx240qv29",
		.data = NUWW,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, iwi9341_of_match);

static const stwuct spi_device_id iwi9341_id[] = {
	{ "yx240qv29", 0 },
	{ "sf-tc240t-9370-t", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, iwi9341_id);

static stwuct spi_dwivew iwi9341_dwivew = {
	.pwobe = iwi9341_pwobe,
	.wemove = iwi9341_wemove,
	.shutdown = iwi9341_shutdown,
	.id_tabwe = iwi9341_id,
	.dwivew = {
		.name = "panew-iwitek-iwi9341",
		.of_match_tabwe = iwi9341_of_match,
	},
};
moduwe_spi_dwivew(iwi9341_dwivew);

MODUWE_AUTHOW("Diwwon Min <diwwon.minfei@gmaiw.com>");
MODUWE_DESCWIPTION("IWI9341 WCD panew dwivew");
MODUWE_WICENSE("GPW v2");
