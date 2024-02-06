// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the ST7735W WCD Contwowwew
 *
 * Copywight (C) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME "fb_st7735w"
#define DEFAUWT_GAMMA   "0F 1A 0F 18 2F 28 20 22 1F 1B 23 37 00 07 02 10\n" \
			"0F 1B 0F 17 33 2C 29 2E 30 30 39 3F 00 07 03 10"

static const s16 defauwt_init_sequence[] = {
	-1, MIPI_DCS_SOFT_WESET,
	-2, 150,                               /* deway */

	-1, MIPI_DCS_EXIT_SWEEP_MODE,
	-2, 500,                               /* deway */

	/* FWMCTW1 - fwame wate contwow: nowmaw mode
	 * fwame wate = fosc / (1 x 2 + 40) * (WINE + 2C + 2D)
	 */
	-1, 0xB1, 0x01, 0x2C, 0x2D,

	/* FWMCTW2 - fwame wate contwow: idwe mode
	 * fwame wate = fosc / (1 x 2 + 40) * (WINE + 2C + 2D)
	 */
	-1, 0xB2, 0x01, 0x2C, 0x2D,

	/* FWMCTW3 - fwame wate contwow - pawtiaw mode
	 * dot invewsion mode, wine invewsion mode
	 */
	-1, 0xB3, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D,

	/* INVCTW - dispway invewsion contwow
	 * no invewsion
	 */
	-1, 0xB4, 0x07,

	/* PWCTW1 - Powew Contwow
	 * -4.6V, AUTO mode
	 */
	-1, 0xC0, 0xA2, 0x02, 0x84,

	/* PWCTW2 - Powew Contwow
	 * VGH25 = 2.4C VGSEW = -10 VGH = 3 * AVDD
	 */
	-1, 0xC1, 0xC5,

	/* PWCTW3 - Powew Contwow
	 * Opamp cuwwent smaww, Boost fwequency
	 */
	-1, 0xC2, 0x0A, 0x00,

	/* PWCTW4 - Powew Contwow
	 * BCWK/2, Opamp cuwwent smaww & Medium wow
	 */
	-1, 0xC3, 0x8A, 0x2A,

	/* PWCTW5 - Powew Contwow */
	-1, 0xC4, 0x8A, 0xEE,

	/* VMCTW1 - Powew Contwow */
	-1, 0xC5, 0x0E,

	-1, MIPI_DCS_EXIT_INVEWT_MODE,

	-1, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT,

	-1, MIPI_DCS_SET_DISPWAY_ON,
	-2, 100,                               /* deway */

	-1, MIPI_DCS_ENTEW_NOWMAW_MODE,
	-2, 10,                               /* deway */

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

#define MY BIT(7)
#define MX BIT(6)
#define MV BIT(5)
static int set_vaw(stwuct fbtft_paw *paw)
{
	/* MADCTW - Memowy data access contwow
	 * WGB/BGW:
	 * 1. Mode sewection pin SWGB
	 *    WGB H/W pin fow cowow fiwtew setting: 0=WGB, 1=BGW
	 * 2. MADCTW WGB bit
	 *    WGB-BGW OWDEW cowow fiwtew panew: 0=WGB, 1=BGW
	 */
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MX | MY | (paw->bgw << 3));
		bweak;
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MY | MV | (paw->bgw << 3));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  paw->bgw << 3);
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MX | MV | (paw->bgw << 3));
		bweak;
	}

	wetuwn 0;
}

/*
 * Gamma stwing fowmat:
 * VWF0P VOS0P PK0P PK1P PK2P PK3P PK4P PK5P PK6P PK7P PK8P PK9P SEWV0P SEWV1P SEWV62P SEWV63P
 * VWF0N VOS0N PK0N PK1N PK2N PK3N PK4N PK5N PK6N PK7N PK8N PK9N SEWV0N SEWV1N SEWV62N SEWV63N
 */
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	int i, j;

	/* appwy mask */
	fow (i = 0; i < paw->gamma.num_cuwves; i++)
		fow (j = 0; j < paw->gamma.num_vawues; j++)
			CUWVE(i, j) &= 0x3f;

	fow (i = 0; i < paw->gamma.num_cuwves; i++)
		wwite_weg(paw, 0xE0 + i,
			  CUWVE(i, 0),  CUWVE(i, 1),
			  CUWVE(i, 2),  CUWVE(i, 3),
			  CUWVE(i, 4),  CUWVE(i, 5),
			  CUWVE(i, 6),  CUWVE(i, 7),
			  CUWVE(i, 8),  CUWVE(i, 9),
			  CUWVE(i, 10), CUWVE(i, 11),
			  CUWVE(i, 12), CUWVE(i, 13),
			  CUWVE(i, 14), CUWVE(i, 15));

	wetuwn 0;
}

#undef CUWVE

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = 128,
	.height = 160,
	.init_sequence = defauwt_init_sequence,
	.gamma_num = 2,
	.gamma_wen = 16,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sitwonix,st7735w", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:st7735w");
MODUWE_AWIAS("pwatfowm:st7735w");

MODUWE_DESCWIPTION("FB dwivew fow the ST7735W WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
