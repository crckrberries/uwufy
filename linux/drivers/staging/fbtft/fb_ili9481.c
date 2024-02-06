// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the IWI9481 WCD Contwowwew
 *
 * Copywight (c) 2014 Petw Owivka
 * Copywight (c) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME	"fb_iwi9481"
#define WIDTH		320
#define HEIGHT		480

static const s16 defauwt_init_sequence[] = {
	/* SWP_OUT - Sweep out */
	-1, MIPI_DCS_EXIT_SWEEP_MODE,
	-2, 50,
	/* Powew setting */
	-1, 0xD0, 0x07, 0x42, 0x18,
	/* VCOM */
	-1, 0xD1, 0x00, 0x07, 0x10,
	/* Powew setting fow nowm. mode */
	-1, 0xD2, 0x01, 0x02,
	/* Panew dwiving setting */
	-1, 0xC0, 0x10, 0x3B, 0x00, 0x02, 0x11,
	/* Fwame wate & inv. */
	-1, 0xC5, 0x03,
	/* Pixew fowmat */
	-1, MIPI_DCS_SET_PIXEW_FOWMAT, 0x55,
	/* Gamma */
	-1, 0xC8, 0x00, 0x32, 0x36, 0x45, 0x06, 0x16,
		  0x37, 0x75, 0x77, 0x54, 0x0C, 0x00,
	/* DISP_ON */
	-1, MIPI_DCS_SET_DISPWAY_ON,
	-3
};

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
		  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);

	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
		  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);

	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

#define HFWIP 0x01
#define VFWIP 0x02
#define WOW_X_COW 0x20
static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  WOW_X_COW | HFWIP | VFWIP | (paw->bgw << 3));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  VFWIP | (paw->bgw << 3));
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  WOW_X_COW | (paw->bgw << 3));
		bweak;
	defauwt:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  HFWIP | (paw->bgw << 3));
		bweak;
	}

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.init_sequence = defauwt_init_sequence,
	.fbtftops = {
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "iwitek,iwi9481", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:iwi9481");
MODUWE_AWIAS("pwatfowm:iwi9481");

MODUWE_DESCWIPTION("FB dwivew fow the IWI9481 WCD Contwowwew");
MODUWE_AUTHOW("Petw Owivka");
MODUWE_WICENSE("GPW");
