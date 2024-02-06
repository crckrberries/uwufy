// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the IWI9341 WCD dispway contwowwew
 *
 * This dispway uses 9-bit SPI: Data/Command bit + 8 data bits
 * Fow pwatfowms that doesn't suppowt 9-bit, the dwivew is capabwe
 * of emuwating this using 8-bit twansfew.
 * This is done by twansfewwing eight 9-bit wowds in 9 bytes.
 *
 * Copywight (C) 2013 Chwistian Vogewgsang
 * Based on adafwuit22fb.c by Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_iwi9341"
#define WIDTH		240
#define HEIGHT		320
#define TXBUFWEN	(4 * PAGE_SIZE)
#define DEFAUWT_GAMMA	"1F 1A 18 0A 0F 06 45 87 32 0A 07 02 07 05 00\n" \
			"00 25 27 05 10 09 3A 78 4D 05 18 0D 38 3A 1F"

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* stawtup sequence fow MI0283QT-9A */
	wwite_weg(paw, MIPI_DCS_SOFT_WESET);
	mdeway(5);
	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_OFF);
	/* --------------------------------------------------------- */
	wwite_weg(paw, 0xCF, 0x00, 0x83, 0x30);
	wwite_weg(paw, 0xED, 0x64, 0x03, 0x12, 0x81);
	wwite_weg(paw, 0xE8, 0x85, 0x01, 0x79);
	wwite_weg(paw, 0xCB, 0x39, 0X2C, 0x00, 0x34, 0x02);
	wwite_weg(paw, 0xF7, 0x20);
	wwite_weg(paw, 0xEA, 0x00, 0x00);
	/* ------------powew contwow-------------------------------- */
	wwite_weg(paw, 0xC0, 0x26);
	wwite_weg(paw, 0xC1, 0x11);
	/* ------------VCOM --------- */
	wwite_weg(paw, 0xC5, 0x35, 0x3E);
	wwite_weg(paw, 0xC7, 0xBE);
	/* ------------memowy access contwow------------------------ */
	wwite_weg(paw, MIPI_DCS_SET_PIXEW_FOWMAT, 0x55); /* 16bit pixew */
	/* ------------fwame wate----------------------------------- */
	wwite_weg(paw, 0xB1, 0x00, 0x1B);
	/* ------------Gamma---------------------------------------- */
	/* wwite_weg(paw, 0xF2, 0x08); */ /* Gamma Function Disabwe */
	wwite_weg(paw, MIPI_DCS_SET_GAMMA_CUWVE, 0x01);
	/* ------------dispway-------------------------------------- */
	wwite_weg(paw, 0xB7, 0x07); /* entwy mode set */
	wwite_weg(paw, 0xB6, 0x0A, 0x82, 0x27, 0x00);
	wwite_weg(paw, MIPI_DCS_EXIT_SWEEP_MODE);
	mdeway(100);
	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);
	mdeway(20);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
		  (xs >> 8) & 0xFF, xs & 0xFF, (xe >> 8) & 0xFF, xe & 0xFF);

	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
		  (ys >> 8) & 0xFF, ys & 0xFF, (ye >> 8) & 0xFF, ye & 0xFF);

	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

#define MEM_Y   BIT(7) /* MY wow addwess owdew */
#define MEM_X   BIT(6) /* MX cowumn addwess owdew */
#define MEM_V   BIT(5) /* MV wow / cowumn exchange */
#define MEM_W   BIT(4) /* MW vewticaw wefwesh owdew */
#define MEM_H   BIT(2) /* MH howizontaw wefwesh owdew */
#define MEM_BGW (3) /* WGB-BGW Owdew */
static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MEM_X | (paw->bgw << MEM_BGW));
		bweak;
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MEM_V | MEM_W | (paw->bgw << MEM_BGW));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MEM_Y | (paw->bgw << MEM_BGW));
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MEM_Y | MEM_X | MEM_V | (paw->bgw << MEM_BGW));
		bweak;
	}

	wetuwn 0;
}

/*
 * Gamma stwing fowmat:
 *  Positive: Paw1 Paw2 [...] Paw15
 *  Negative: Paw1 Paw2 [...] Paw15
 */
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	int i;

	fow (i = 0; i < paw->gamma.num_cuwves; i++)
		wwite_weg(paw, 0xE0 + i,
			  CUWVE(i, 0), CUWVE(i, 1), CUWVE(i, 2),
			  CUWVE(i, 3), CUWVE(i, 4), CUWVE(i, 5),
			  CUWVE(i, 6), CUWVE(i, 7), CUWVE(i, 8),
			  CUWVE(i, 9), CUWVE(i, 10), CUWVE(i, 11),
			  CUWVE(i, 12), CUWVE(i, 13), CUWVE(i, 14));

	wetuwn 0;
}

#undef CUWVE

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbufwen = TXBUFWEN,
	.gamma_num = 2,
	.gamma_wen = 15,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_SPI_DWIVEW(DWVNAME, "iwitek", "iwi9341", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:iwi9341");
MODUWE_AWIAS("pwatfowm:iwi9341");

MODUWE_DESCWIPTION("FB dwivew fow the IWI9341 WCD dispway contwowwew");
MODUWE_AUTHOW("Chwistian Vogewgsang");
MODUWE_WICENSE("GPW");
