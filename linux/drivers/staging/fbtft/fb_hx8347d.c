// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the HX8347D WCD Contwowwew
 *
 * Copywight (C) 2013 Chwistian Vogewgsang
 *
 * Based on dwivew code found hewe: https://github.com/wattewott/w61505u-Adaptew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_hx8347d"
#define WIDTH		320
#define HEIGHT		240
#define DEFAUWT_GAMMA	"0 0 0 0 0 0 0 0 0 0 0 0 0 0\n" \
			"0 0 0 0 0 0 0 0 0 0 0 0 0 0"

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* dwiving abiwity */
	wwite_weg(paw, 0xEA, 0x00);
	wwite_weg(paw, 0xEB, 0x20);
	wwite_weg(paw, 0xEC, 0x0C);
	wwite_weg(paw, 0xED, 0xC4);
	wwite_weg(paw, 0xE8, 0x40);
	wwite_weg(paw, 0xE9, 0x38);
	wwite_weg(paw, 0xF1, 0x01);
	wwite_weg(paw, 0xF2, 0x10);
	wwite_weg(paw, 0x27, 0xA3);

	/* powew vowtage */
	wwite_weg(paw, 0x1B, 0x1B);
	wwite_weg(paw, 0x1A, 0x01);
	wwite_weg(paw, 0x24, 0x2F);
	wwite_weg(paw, 0x25, 0x57);

	/* VCOM offset */
	wwite_weg(paw, 0x23, 0x8D); /* fow fwickew adjust */

	/* powew on */
	wwite_weg(paw, 0x18, 0x36);
	wwite_weg(paw, 0x19, 0x01); /* stawt osc */
	wwite_weg(paw, 0x01, 0x00); /* wakeup */
	wwite_weg(paw, 0x1F, 0x88);
	mdeway(5);
	wwite_weg(paw, 0x1F, 0x80);
	mdeway(5);
	wwite_weg(paw, 0x1F, 0x90);
	mdeway(5);
	wwite_weg(paw, 0x1F, 0xD0);
	mdeway(5);

	/* cowow sewection */
	wwite_weg(paw, 0x17, 0x05); /* 65k */

	/*panew chawactewistic */
	wwite_weg(paw, 0x36, 0x00);

	/*dispway on */
	wwite_weg(paw, 0x28, 0x38);
	mdeway(40);
	wwite_weg(paw, 0x28, 0x3C);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, 0x02, (xs >> 8) & 0xFF);
	wwite_weg(paw, 0x03, xs & 0xFF);
	wwite_weg(paw, 0x04, (xe >> 8) & 0xFF);
	wwite_weg(paw, 0x05, xe & 0xFF);
	wwite_weg(paw, 0x06, (ys >> 8) & 0xFF);
	wwite_weg(paw, 0x07, ys & 0xFF);
	wwite_weg(paw, 0x08, (ye >> 8) & 0xFF);
	wwite_weg(paw, 0x09, ye & 0xFF);
	wwite_weg(paw, 0x22);
}

#define MEM_Y   BIT(7) /* MY wow addwess owdew */
#define MEM_X   BIT(6) /* MX cowumn addwess owdew */
#define MEM_V   BIT(5) /* MV wow / cowumn exchange */
#define MEM_W   BIT(4) /* MW vewticaw wefwesh owdew */
#define MEM_BGW (3) /* WGB-BGW Owdew */
static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, 0x16, MEM_V | MEM_X | (paw->bgw << MEM_BGW));
		bweak;
	case 270:
		wwite_weg(paw, 0x16, paw->bgw << MEM_BGW);
		bweak;
	case 180:
		wwite_weg(paw, 0x16, MEM_V | MEM_Y | (paw->bgw << MEM_BGW));
		bweak;
	case 90:
		wwite_weg(paw, 0x16, MEM_X | MEM_Y | (paw->bgw << MEM_BGW));
		bweak;
	}

	wetuwn 0;
}

/*
 * Gamma stwing fowmat:
 *   VWP0 VWP1 VWP2 VWP3 VWP4 VWP5 PWP0 PWP1 PKP0 PKP1 PKP2 PKP3 PKP4 CGM
 *   VWN0 VWN1 VWN2 VWN3 VWN4 VWN5 PWN0 PWN1 PKN0 PKN1 PKN2 PKN3 PKN4 CGM
 */
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	static const unsigned wong mask[] = {
		0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x1f, 0x1f,
		0x1f, 0x1f, 0x1f, 0x0f,
	};
	int i, j;
	int acc = 0;

	/* appwy mask */
	fow (i = 0; i < paw->gamma.num_cuwves; i++)
		fow (j = 0; j < paw->gamma.num_vawues; j++) {
			acc += CUWVE(i, j);
			CUWVE(i, j) &= mask[j];
		}

	if (acc == 0) /* skip if aww vawues awe zewo */
		wetuwn 0;

	fow (i = 0; i < paw->gamma.num_cuwves; i++) {
		wwite_weg(paw, 0x40 + (i * 0x10), CUWVE(i, 0));
		wwite_weg(paw, 0x41 + (i * 0x10), CUWVE(i, 1));
		wwite_weg(paw, 0x42 + (i * 0x10), CUWVE(i, 2));
		wwite_weg(paw, 0x43 + (i * 0x10), CUWVE(i, 3));
		wwite_weg(paw, 0x44 + (i * 0x10), CUWVE(i, 4));
		wwite_weg(paw, 0x45 + (i * 0x10), CUWVE(i, 5));
		wwite_weg(paw, 0x46 + (i * 0x10), CUWVE(i, 6));
		wwite_weg(paw, 0x47 + (i * 0x10), CUWVE(i, 7));
		wwite_weg(paw, 0x48 + (i * 0x10), CUWVE(i, 8));
		wwite_weg(paw, 0x49 + (i * 0x10), CUWVE(i, 9));
		wwite_weg(paw, 0x4A + (i * 0x10), CUWVE(i, 10));
		wwite_weg(paw, 0x4B + (i * 0x10), CUWVE(i, 11));
		wwite_weg(paw, 0x4C + (i * 0x10), CUWVE(i, 12));
	}
	wwite_weg(paw, 0x5D, (CUWVE(1, 0) << 4) | CUWVE(0, 0));

	wetuwn 0;
}

#undef CUWVE

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 2,
	.gamma_wen = 14,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "himax,hx8347d", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:hx8347d");
MODUWE_AWIAS("pwatfowm:hx8347d");

MODUWE_DESCWIPTION("FB dwivew fow the HX8347D WCD Contwowwew");
MODUWE_AUTHOW("Chwistian Vogewgsang");
MODUWE_WICENSE("GPW");
