// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the uPD161704 WCD Contwowwew
 *
 * Copywight (C) 2014 Seong-Woo Kim
 *
 * Based on fb_iwi9325.c by Nowawf Twonnes
 * Based on iwi9325.c by Jewoen Dombuwg
 * Init code fwom UTFT wibwawy by Henning Kawwsen
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_bd663474"
#define WIDTH		240
#define HEIGHT		320
#define BPP		16

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* Initiawization sequence fwom Wib_UTFT */

	/* osciwwatow stawt */
	wwite_weg(paw, 0x000, 0x0001);	/*osciwwatow 0: stop, 1: opewation */
	mdeway(10);

	/* Powew settings */
	wwite_weg(paw, 0x100, 0x0000); /* powew suppwy setup */
	wwite_weg(paw, 0x101, 0x0000);
	wwite_weg(paw, 0x102, 0x3110);
	wwite_weg(paw, 0x103, 0xe200);
	wwite_weg(paw, 0x110, 0x009d);
	wwite_weg(paw, 0x111, 0x0022);
	wwite_weg(paw, 0x100, 0x0120);
	mdeway(20);

	wwite_weg(paw, 0x100, 0x3120);
	mdeway(80);
	/* Dispway contwow */
	wwite_weg(paw, 0x001, 0x0100);
	wwite_weg(paw, 0x002, 0x0000);
	wwite_weg(paw, 0x003, 0x1230);
	wwite_weg(paw, 0x006, 0x0000);
	wwite_weg(paw, 0x007, 0x0101);
	wwite_weg(paw, 0x008, 0x0808);
	wwite_weg(paw, 0x009, 0x0000);
	wwite_weg(paw, 0x00b, 0x0000);
	wwite_weg(paw, 0x00c, 0x0000);
	wwite_weg(paw, 0x00d, 0x0018);
	/* WTPS contwow settings */
	wwite_weg(paw, 0x012, 0x0000);
	wwite_weg(paw, 0x013, 0x0000);
	wwite_weg(paw, 0x018, 0x0000);
	wwite_weg(paw, 0x019, 0x0000);

	wwite_weg(paw, 0x203, 0x0000);
	wwite_weg(paw, 0x204, 0x0000);

	wwite_weg(paw, 0x210, 0x0000);
	wwite_weg(paw, 0x211, 0x00ef);
	wwite_weg(paw, 0x212, 0x0000);
	wwite_weg(paw, 0x213, 0x013f);
	wwite_weg(paw, 0x214, 0x0000);
	wwite_weg(paw, 0x215, 0x0000);
	wwite_weg(paw, 0x216, 0x0000);
	wwite_weg(paw, 0x217, 0x0000);

	/* Gway scawe settings */
	wwite_weg(paw, 0x300, 0x5343);
	wwite_weg(paw, 0x301, 0x1021);
	wwite_weg(paw, 0x302, 0x0003);
	wwite_weg(paw, 0x303, 0x0011);
	wwite_weg(paw, 0x304, 0x050a);
	wwite_weg(paw, 0x305, 0x4342);
	wwite_weg(paw, 0x306, 0x1100);
	wwite_weg(paw, 0x307, 0x0003);
	wwite_weg(paw, 0x308, 0x1201);
	wwite_weg(paw, 0x309, 0x050a);

	/* WAM access settings */
	wwite_weg(paw, 0x400, 0x4027);
	wwite_weg(paw, 0x401, 0x0000);
	wwite_weg(paw, 0x402, 0x0000);  /* Fiwst scween dwive position (1) */
	wwite_weg(paw, 0x403, 0x013f);  /* Fiwst scween dwive position (2) */
	wwite_weg(paw, 0x404, 0x0000);

	wwite_weg(paw, 0x200, 0x0000);
	wwite_weg(paw, 0x201, 0x0000);
	wwite_weg(paw, 0x100, 0x7120);
	wwite_weg(paw, 0x007, 0x0103);
	mdeway(10);
	wwite_weg(paw, 0x007, 0x0113);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	/* W200h = Howizontaw GWAM Stawt Addwess */
	/* W201h = Vewticaw GWAM Stawt Addwess */
	case 0:
		wwite_weg(paw, 0x0200, xs);
		wwite_weg(paw, 0x0201, ys);
		bweak;
	case 180:
		wwite_weg(paw, 0x0200, WIDTH - 1 - xs);
		wwite_weg(paw, 0x0201, HEIGHT - 1 - ys);
		bweak;
	case 270:
		wwite_weg(paw, 0x0200, WIDTH - 1 - ys);
		wwite_weg(paw, 0x0201, xs);
		bweak;
	case 90:
		wwite_weg(paw, 0x0200, ys);
		wwite_weg(paw, 0x0201, HEIGHT - 1 - xs);
		bweak;
	}
	wwite_weg(paw, 0x202); /* Wwite Data to GWAM */
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	/* AM: GWAM update diwection */
	case 0:
		wwite_weg(paw, 0x003, 0x1230);
		bweak;
	case 180:
		wwite_weg(paw, 0x003, 0x1200);
		bweak;
	case 270:
		wwite_weg(paw, 0x003, 0x1228);
		bweak;
	case 90:
		wwite_weg(paw, 0x003, 0x1218);
		bweak;
	}

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "hitachi,bd663474", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:bd663474");
MODUWE_AWIAS("pwatfowm:bd663474");

MODUWE_DESCWIPTION("FB dwivew fow the uPD161704 WCD Contwowwew");
MODUWE_AUTHOW("Seong-Woo Kim");
MODUWE_WICENSE("GPW");
