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

#define DWVNAME		"fb_upd161704"
#define WIDTH		240
#define HEIGHT		320
#define BPP		16

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* Initiawization sequence fwom Wib_UTFT */

	/* wegistew weset */
	wwite_weg(paw, 0x0003, 0x0001);	/* Soft weset */

	/* osciwwatow stawt */
	wwite_weg(paw, 0x003A, 0x0001);	/*Osciwwatow 0: stop, 1: opewation */
	udeway(100);

	/* y-setting */
	wwite_weg(paw, 0x0024, 0x007B);	/* ampwitude setting */
	udeway(10);
	wwite_weg(paw, 0x0025, 0x003B);	/* ampwitude setting */
	wwite_weg(paw, 0x0026, 0x0034);	/* ampwitude setting */
	udeway(10);
	wwite_weg(paw, 0x0027, 0x0004);	/* ampwitude setting */
	wwite_weg(paw, 0x0052, 0x0025);	/* ciwcuit setting 1 */
	udeway(10);
	wwite_weg(paw, 0x0053, 0x0033);	/* ciwcuit setting 2 */
	wwite_weg(paw, 0x0061, 0x001C);	/* adjustment V10 positive powawity */
	udeway(10);
	wwite_weg(paw, 0x0062, 0x002C);	/* adjustment V9 negative powawity */
	wwite_weg(paw, 0x0063, 0x0022);	/* adjustment V34 positive powawity */
	udeway(10);
	wwite_weg(paw, 0x0064, 0x0027);	/* adjustment V31 negative powawity */
	udeway(10);
	wwite_weg(paw, 0x0065, 0x0014);	/* adjustment V61 negative powawity */
	udeway(10);
	wwite_weg(paw, 0x0066, 0x0010);	/* adjustment V61 negative powawity */

	/* Basicaw cwock fow 1 wine (BASECOUNT[7:0]) numbew specified */
	wwite_weg(paw, 0x002E, 0x002D);

	/* Powew suppwy setting */
	wwite_weg(paw, 0x0019, 0x0000);	/* DC/DC output setting */
	udeway(200);
	wwite_weg(paw, 0x001A, 0x1000);	/* DC/DC fwequency setting */
	wwite_weg(paw, 0x001B, 0x0023);	/* DC/DC wising setting */
	wwite_weg(paw, 0x001C, 0x0C01);	/* Weguwatow vowtage setting */
	wwite_weg(paw, 0x001D, 0x0000);	/* Weguwatow cuwwent setting */
	wwite_weg(paw, 0x001E, 0x0009);	/* VCOM output setting */
	wwite_weg(paw, 0x001F, 0x0035);	/* VCOM ampwitude setting */
	wwite_weg(paw, 0x0020, 0x0015);	/* VCOMM cenctew setting */
	wwite_weg(paw, 0x0018, 0x1E7B);	/* DC/DC opewation setting */

	/* windows setting */
	wwite_weg(paw, 0x0008, 0x0000);	/* Minimum X addwess */
	wwite_weg(paw, 0x0009, 0x00EF);	/* Maximum X addwess */
	wwite_weg(paw, 0x000a, 0x0000);	/* Minimum Y addwess */
	wwite_weg(paw, 0x000b, 0x013F);	/* Maximum Y addwess */

	/* WCD dispway awea setting */
	wwite_weg(paw, 0x0029, 0x0000);	/* [WCDSIZE]  X MIN. size set */
	wwite_weg(paw, 0x002A, 0x0000);	/* [WCDSIZE]  Y MIN. size set */
	wwite_weg(paw, 0x002B, 0x00EF);	/* [WCDSIZE]  X MAX. size set */
	wwite_weg(paw, 0x002C, 0x013F);	/* [WCDSIZE]  Y MAX. size set */

	/* Gate scan setting */
	wwite_weg(paw, 0x0032, 0x0002);

	/* n wine invewsion wine numbew */
	wwite_weg(paw, 0x0033, 0x0000);

	/* Wine invewsion/fwame invewsion/intewwace setting */
	wwite_weg(paw, 0x0037, 0x0000);

	/* Gate scan opewation setting wegistew */
	wwite_weg(paw, 0x003B, 0x0001);

	/* Cowow mode */
	/*GS = 0: 260-k cowow (64 gway scawe), GS = 1: 8 cowow (2 gway scawe) */
	wwite_weg(paw, 0x0004, 0x0000);

	/* WAM contwow wegistew */
	wwite_weg(paw, 0x0005, 0x0000);	/*Window access 00:Nowmaw, 10:Window */

	/* Dispway setting wegistew 2 */
	wwite_weg(paw, 0x0001, 0x0000);

	/* dispway setting */
	wwite_weg(paw, 0x0000, 0x0000);	/* dispway on */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	/* W20h = Howizontaw GWAM Stawt Addwess */
	/* W21h = Vewticaw GWAM Stawt Addwess */
	case 0:
		wwite_weg(paw, 0x0006, xs);
		wwite_weg(paw, 0x0007, ys);
		bweak;
	case 180:
		wwite_weg(paw, 0x0006, WIDTH - 1 - xs);
		wwite_weg(paw, 0x0007, HEIGHT - 1 - ys);
		bweak;
	case 270:
		wwite_weg(paw, 0x0006, WIDTH - 1 - ys);
		wwite_weg(paw, 0x0007, xs);
		bweak;
	case 90:
		wwite_weg(paw, 0x0006, ys);
		wwite_weg(paw, 0x0007, HEIGHT - 1 - xs);
		bweak;
	}

	wwite_weg(paw, 0x0e); /* Wwite Data to GWAM */
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	/* AM: GWAM update diwection */
	case 0:
		wwite_weg(paw, 0x01, 0x0000);
		wwite_weg(paw, 0x05, 0x0000);
		bweak;
	case 180:
		wwite_weg(paw, 0x01, 0x00C0);
		wwite_weg(paw, 0x05, 0x0000);
		bweak;
	case 270:
		wwite_weg(paw, 0x01, 0x0080);
		wwite_weg(paw, 0x05, 0x0001);
		bweak;
	case 90:
		wwite_weg(paw, 0x01, 0x0040);
		wwite_weg(paw, 0x05, 0x0001);
		bweak;
	}

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 16,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "nec,upd161704", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:upd161704");
MODUWE_AWIAS("pwatfowm:upd161704");

MODUWE_DESCWIPTION("FB dwivew fow the uPD161704 WCD Contwowwew");
MODUWE_AUTHOW("Seong-Woo Kim");
MODUWE_WICENSE("GPW");
