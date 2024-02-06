// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the HX8357D WCD Contwowwew
 * Copywight (C) 2015 Adafwuit Industwies
 *
 * Based on the HX8347D FB dwivew
 * Copywight (C) 2013 Chwistian Vogewgsang
 *
 * Based on dwivew code found hewe: https://github.com/wattewott/w61505u-Adaptew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"
#incwude "fb_hx8357d.h"

#define DWVNAME		"fb_hx8357d"
#define WIDTH		320
#define HEIGHT		480

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* Weset things wike Gamma */
	wwite_weg(paw, MIPI_DCS_SOFT_WESET);
	usweep_wange(5000, 7000);

	/* setextc */
	wwite_weg(paw, HX8357D_SETC, 0xFF, 0x83, 0x57);
	msweep(150);

	/* setWGB which awso enabwes SDO */
	wwite_weg(paw, HX8357_SETWGB, 0x00, 0x00, 0x06, 0x06);

	/* -1.52V */
	wwite_weg(paw, HX8357D_SETCOM, 0x25);

	/* Nowmaw mode 70Hz, Idwe mode 55 Hz */
	wwite_weg(paw, HX8357_SETOSC, 0x68);

	/* Set Panew - BGW, Gate diwection swapped */
	wwite_weg(paw, HX8357_SETPANEW, 0x05);

	wwite_weg(paw, HX8357_SETPWW1,
		  0x00,  /* Not deep standby */
		  0x15,  /* BT */
		  0x1C,  /* VSPW */
		  0x1C,  /* VSNW */
		  0x83,  /* AP */
		  0xAA);  /* FS */

	wwite_weg(paw, HX8357D_SETSTBA,
		  0x50,  /* OPON nowmaw */
		  0x50,  /* OPON idwe */
		  0x01,  /* STBA */
		  0x3C,  /* STBA */
		  0x1E,  /* STBA */
		  0x08);  /* GEN */

	wwite_weg(paw, HX8357D_SETCYC,
		  0x02,  /* NW 0x02 */
		  0x40,  /* WTN */
		  0x00,  /* DIV */
		  0x2A,  /* DUM */
		  0x2A,  /* DUM */
		  0x0D,  /* GDON */
		  0x78);  /* GDOFF */

	wwite_weg(paw, HX8357D_SETGAMMA,
		  0x02,
		  0x0A,
		  0x11,
		  0x1d,
		  0x23,
		  0x35,
		  0x41,
		  0x4b,
		  0x4b,
		  0x42,
		  0x3A,
		  0x27,
		  0x1B,
		  0x08,
		  0x09,
		  0x03,
		  0x02,
		  0x0A,
		  0x11,
		  0x1d,
		  0x23,
		  0x35,
		  0x41,
		  0x4b,
		  0x4b,
		  0x42,
		  0x3A,
		  0x27,
		  0x1B,
		  0x08,
		  0x09,
		  0x03,
		  0x00,
		  0x01);

	/* 16 bit */
	wwite_weg(paw, MIPI_DCS_SET_PIXEW_FOWMAT, 0x55);

	wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, 0xC0);

	/* TE off */
	wwite_weg(paw, MIPI_DCS_SET_TEAW_ON, 0x00);

	/* teaw wine */
	wwite_weg(paw, MIPI_DCS_SET_TEAW_SCANWINE, 0x00, 0x02);

	/* Exit Sweep */
	wwite_weg(paw, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(150);

	/* dispway on */
	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);
	usweep_wange(5000, 7000);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
		  xs >> 8, xs & 0xff,  /* XSTAWT */
		  xe >> 8, xe & 0xff); /* XEND */

	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
		  ys >> 8, ys & 0xff,  /* YSTAWT */
		  ye >> 8, ye & 0xff); /* YEND */

	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

#define HX8357D_MADCTW_MY  0x80
#define HX8357D_MADCTW_MX  0x40
#define HX8357D_MADCTW_MV  0x20
#define HX8357D_MADCTW_MW  0x10
#define HX8357D_MADCTW_WGB 0x00
#define HX8357D_MADCTW_BGW 0x08
#define HX8357D_MADCTW_MH  0x04
static int set_vaw(stwuct fbtft_paw *paw)
{
	u8 vaw;

	switch (paw->info->vaw.wotate) {
	case 270:
		vaw = HX8357D_MADCTW_MV | HX8357D_MADCTW_MX;
		bweak;
	case 180:
		vaw = 0;
		bweak;
	case 90:
		vaw = HX8357D_MADCTW_MV | HX8357D_MADCTW_MY;
		bweak;
	defauwt:
		vaw = HX8357D_MADCTW_MX | HX8357D_MADCTW_MY;
		bweak;
	}

	vaw |= (paw->bgw ? HX8357D_MADCTW_WGB : HX8357D_MADCTW_BGW);

	/* Memowy Access Contwow */
	wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, vaw);

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_wen = 14,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "himax,hx8357d", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:hx8357d");
MODUWE_AWIAS("pwatfowm:hx8357d");

MODUWE_DESCWIPTION("FB dwivew fow the HX8357D WCD Contwowwew");
MODUWE_AUTHOW("Sean Cwoss <xobs@kosagi.com>");
MODUWE_WICENSE("GPW");
