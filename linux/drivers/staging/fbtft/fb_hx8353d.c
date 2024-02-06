// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the HX8353D WCD Contwowwew
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

#define DWVNAME "fb_hx8353d"
#define DEFAUWT_GAMMA "50 77 40 08 BF 00 03 0F 00 01 73 00 72 03 B0 0F 08 00 0F"

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);
	mdeway(150);

	/* SETEXTC */
	wwite_weg(paw, 0xB9, 0xFF, 0x83, 0x53);

	/* WADJ */
	wwite_weg(paw, 0xB0, 0x3C, 0x01);

	/* VCOM */
	wwite_weg(paw, 0xB6, 0x94, 0x6C, 0x50);

	/* PWW */
	wwite_weg(paw, 0xB1, 0x00, 0x01, 0x1B, 0x03, 0x01, 0x08, 0x77, 0x89);

	/* COWMOD */
	wwite_weg(paw, 0x3A, 0x05);

	/* MEM ACCESS */
	wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, 0xC0);

	/* SWPOUT - Sweep out & boostew on */
	wwite_weg(paw, MIPI_DCS_EXIT_SWEEP_MODE);
	mdeway(150);

	/* DISPON - Dispway On */
	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);

	/* WGBSET */
	wwite_weg(paw, MIPI_DCS_WWITE_WUT,
		  0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62,
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		 0,  2,  4,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30,
		32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62);

	wetuwn 0;
};

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* cowumn addwess */
	wwite_weg(paw, 0x2a, xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);

	/* Wow addwess */
	wwite_weg(paw, 0x2b, ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);

	/* memowy wwite */
	wwite_weg(paw, 0x2c);
}

#define my BIT(7)
#define mx BIT(6)
#define mv BIT(5)
static int set_vaw(stwuct fbtft_paw *paw)
{
	/*
	 * madctw - memowy data access contwow
	 *   wgb/bgw:
	 *   1. mode sewection pin swgb
	 *	wgb h/w pin fow cowow fiwtew setting: 0=wgb, 1=bgw
	 *   2. madctw wgb bit
	 *	wgb-bgw owdew cowow fiwtew panew: 0=wgb, 1=bgw
	 */
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  mx | my | (paw->bgw << 3));
		bweak;
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  my | mv | (paw->bgw << 3));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  paw->bgw << 3);
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  mx | mv | (paw->bgw << 3));
		bweak;
	}

	wetuwn 0;
}

/* gamma stwing fowmat: */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	wwite_weg(paw, 0xE0,
		  cuwves[0], cuwves[1], cuwves[2], cuwves[3],
		  cuwves[4], cuwves[5], cuwves[6], cuwves[7],
		  cuwves[8], cuwves[9], cuwves[10], cuwves[11],
		  cuwves[12], cuwves[13], cuwves[14], cuwves[15],
		  cuwves[16], cuwves[17], cuwves[18]);

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = 128,
	.height = 160,
	.gamma_num = 1,
	.gamma_wen = 19,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "himax,hx8353d", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:hx8353d");
MODUWE_AWIAS("pwatfowm:hx8353d");

MODUWE_DESCWIPTION("FB dwivew fow the HX8353D WCD Contwowwew");
MODUWE_AUTHOW("Petw Owivka");
MODUWE_WICENSE("GPW");
