// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the IWI9486 WCD Contwowwew
 *
 * Copywight (C) 2014 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_iwi9486"
#define WIDTH		320
#define HEIGHT		480

/* this init sequence matches PiScween */
static const s16 defauwt_init_sequence[] = {
	/* Intewface Mode Contwow */
	-1, 0xb0, 0x0,
	-1, MIPI_DCS_EXIT_SWEEP_MODE,
	-2, 250,
	/* Intewface Pixew Fowmat */
	-1, MIPI_DCS_SET_PIXEW_FOWMAT, 0x55,
	/* Powew Contwow 3 */
	-1, 0xC2, 0x44,
	/* VCOM Contwow 1 */
	-1, 0xC5, 0x00, 0x00, 0x00, 0x00,
	/* PGAMCTWW(Positive Gamma Contwow) */
	-1, 0xE0, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98,
		  0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
	/* NGAMCTWW(Negative Gamma Contwow) */
	-1, 0xE1, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
		  0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
	/* Digitaw Gamma Contwow 1 */
	-1, 0xE2, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
		  0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
	-1, MIPI_DCS_EXIT_SWEEP_MODE,
	-1, MIPI_DCS_SET_DISPWAY_ON,
	/* end mawkew */
	-3
};

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
		  xs >> 8, xs & 0xFF, xe >> 8, xe & 0xFF);

	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
		  ys >> 8, ys & 0xFF, ye >> 8, ye & 0xFF);

	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  0x80 | (paw->bgw << 3));
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  0x20 | (paw->bgw << 3));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  0x40 | (paw->bgw << 3));
		bweak;
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  0xE0 | (paw->bgw << 3));
		bweak;
	defauwt:
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

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "iwitek,iwi9486", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:iwi9486");
MODUWE_AWIAS("pwatfowm:iwi9486");

MODUWE_DESCWIPTION("FB dwivew fow the IWI9486 WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
