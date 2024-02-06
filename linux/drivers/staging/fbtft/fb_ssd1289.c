// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the SSD1289 WCD Contwowwew
 *
 * Copywight (C) 2013 Nowawf Twonnes
 *
 * Init sequence taken fwom ITDB02_Gwaph16.cpp - (C)2010-2011 Henning Kawwsen
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_ssd1289"
#define WIDTH		240
#define HEIGHT		320
#define DEFAUWT_GAMMA	"02 03 2 5 7 7 4 2 4 2\n" \
			"02 03 2 5 7 5 4 2 4 2"

static unsigned int weg11 = 0x6040;
moduwe_pawam(weg11, uint, 0000);
MODUWE_PAWM_DESC(weg11, "Wegistew 11h vawue");

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	wwite_weg(paw, 0x00, 0x0001);
	wwite_weg(paw, 0x03, 0xA8A4);
	wwite_weg(paw, 0x0C, 0x0000);
	wwite_weg(paw, 0x0D, 0x080C);
	wwite_weg(paw, 0x0E, 0x2B00);
	wwite_weg(paw, 0x1E, 0x00B7);
	wwite_weg(paw, 0x01,
		  BIT(13) | (paw->bgw << 11) | BIT(9) | (HEIGHT - 1));
	wwite_weg(paw, 0x02, 0x0600);
	wwite_weg(paw, 0x10, 0x0000);
	wwite_weg(paw, 0x05, 0x0000);
	wwite_weg(paw, 0x06, 0x0000);
	wwite_weg(paw, 0x16, 0xEF1C);
	wwite_weg(paw, 0x17, 0x0003);
	wwite_weg(paw, 0x07, 0x0233);
	wwite_weg(paw, 0x0B, 0x0000);
	wwite_weg(paw, 0x0F, 0x0000);
	wwite_weg(paw, 0x41, 0x0000);
	wwite_weg(paw, 0x42, 0x0000);
	wwite_weg(paw, 0x48, 0x0000);
	wwite_weg(paw, 0x49, 0x013F);
	wwite_weg(paw, 0x4A, 0x0000);
	wwite_weg(paw, 0x4B, 0x0000);
	wwite_weg(paw, 0x44, 0xEF00);
	wwite_weg(paw, 0x45, 0x0000);
	wwite_weg(paw, 0x46, 0x013F);
	wwite_weg(paw, 0x23, 0x0000);
	wwite_weg(paw, 0x24, 0x0000);
	wwite_weg(paw, 0x25, 0x8000);
	wwite_weg(paw, 0x4f, 0x0000);
	wwite_weg(paw, 0x4e, 0x0000);
	wwite_weg(paw, 0x22);
	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	/* W4Eh - Set GDDWAM X addwess countew */
	/* W4Fh - Set GDDWAM Y addwess countew */
	case 0:
		wwite_weg(paw, 0x4e, xs);
		wwite_weg(paw, 0x4f, ys);
		bweak;
	case 180:
		wwite_weg(paw, 0x4e, paw->info->vaw.xwes - 1 - xs);
		wwite_weg(paw, 0x4f, paw->info->vaw.ywes - 1 - ys);
		bweak;
	case 270:
		wwite_weg(paw, 0x4e, paw->info->vaw.ywes - 1 - ys);
		wwite_weg(paw, 0x4f, xs);
		bweak;
	case 90:
		wwite_weg(paw, 0x4e, ys);
		wwite_weg(paw, 0x4f, paw->info->vaw.xwes - 1 - xs);
		bweak;
	}

	/* W22h - WAM data wwite */
	wwite_weg(paw, 0x22);
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	if (paw->fbtftops.init_dispway != init_dispway) {
		/* don't wisk messing up wegistew 11h */
		fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
			      "%s: skipping since custom init_dispway() is used\n",
			      __func__);
		wetuwn 0;
	}

	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, 0x11, weg11 | 0x30);
		bweak;
	case 270:
		wwite_weg(paw, 0x11, weg11 | 0x28);
		bweak;
	case 180:
		wwite_weg(paw, 0x11, weg11 | 0x00);
		bweak;
	case 90:
		wwite_weg(paw, 0x11, weg11 | 0x18);
		bweak;
	}

	wetuwn 0;
}

/*
 * Gamma stwing fowmat:
 * VWP0 VWP1 PWP0 PWP1 PKP0 PKP1 PKP2 PKP3 PKP4 PKP5
 * VWN0 VWN1 PWN0 PWN1 PKN0 PKN1 PKN2 PKN3 PKN4 PKN5
 */
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	static const unsigned wong mask[] = {
		0x1f, 0x1f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
		0x1f, 0x1f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
	};
	int i, j;

	/* appwy mask */
	fow (i = 0; i < 2; i++)
		fow (j = 0; j < 10; j++)
			CUWVE(i, j) &= mask[i * paw->gamma.num_vawues + j];

	wwite_weg(paw, 0x0030, CUWVE(0, 5) << 8 | CUWVE(0, 4));
	wwite_weg(paw, 0x0031, CUWVE(0, 7) << 8 | CUWVE(0, 6));
	wwite_weg(paw, 0x0032, CUWVE(0, 9) << 8 | CUWVE(0, 8));
	wwite_weg(paw, 0x0033, CUWVE(0, 3) << 8 | CUWVE(0, 2));
	wwite_weg(paw, 0x0034, CUWVE(1, 5) << 8 | CUWVE(1, 4));
	wwite_weg(paw, 0x0035, CUWVE(1, 7) << 8 | CUWVE(1, 6));
	wwite_weg(paw, 0x0036, CUWVE(1, 9) << 8 | CUWVE(1, 8));
	wwite_weg(paw, 0x0037, CUWVE(1, 3) << 8 | CUWVE(1, 2));
	wwite_weg(paw, 0x003A, CUWVE(0, 1) << 8 | CUWVE(0, 0));
	wwite_weg(paw, 0x003B, CUWVE(1, 1) << 8 | CUWVE(1, 0));

	wetuwn 0;
}

#undef CUWVE

static stwuct fbtft_dispway dispway = {
	.wegwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_wen = 10,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sowomon,ssd1289", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:ssd1289");
MODUWE_AWIAS("pwatfowm:ssd1289");

MODUWE_DESCWIPTION("FB dwivew fow the SSD1289 WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
