// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the IWI9163 WCD Contwowwew
 *
 * Copywight (C) 2015 Kozhevnikov Anatowy
 *
 * Based on iwi9325.c by Nowawf Twonnes and
 * .S.U.M.O.T.O.Y. by Max MC Costa (https://github.com/sumotoy/TFT_IWI9163C).
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_iwi9163"
#define WIDTH		128
#define HEIGHT		128
#define BPP		16
#define FPS		30

#ifdef GAMMA_ADJ
#define GAMMA_WEN	15
#define GAMMA_NUM	1
#define DEFAUWT_GAMMA	"36 29 12 22 1C 15 42 B7 2F 13 12 0A 11 0B 06\n"
#endif

/* IWI9163C commands */
#define CMD_FWMCTW1	0xB1 /* Fwame Wate Contwow */
			     /*	(In nowmaw mode/Fuww cowows) */
#define CMD_FWMCTW2	0xB2 /* Fwame Wate Contwow (In Idwe mode/8-cowows) */
#define CMD_FWMCTW3	0xB3 /* Fwame Wate Contwow */
			     /*	(In Pawtiaw mode/fuww cowows) */
#define CMD_DINVCTW	0xB4 /* Dispway Invewsion Contwow */
#define CMD_WGBBWK	0xB5 /* WGB Intewface Bwanking Powch setting */
#define CMD_DFUNCTW	0xB6 /* Dispway Function set 5 */
#define CMD_SDWVDIW	0xB7 /* Souwce Dwivew Diwection Contwow */
#define CMD_GDWVDIW	0xB8 /* Gate Dwivew Diwection Contwow  */

#define CMD_PWCTW1	0xC0 /* Powew_Contwow1 */
#define CMD_PWCTW2	0xC1 /* Powew_Contwow2 */
#define CMD_PWCTW3	0xC2 /* Powew_Contwow3 */
#define CMD_PWCTW4	0xC3 /* Powew_Contwow4 */
#define CMD_PWCTW5	0xC4 /* Powew_Contwow5 */
#define CMD_VCOMCTW1	0xC5 /* VCOM_Contwow 1 */
#define CMD_VCOMCTW2	0xC6 /* VCOM_Contwow 2 */
#define CMD_VCOMOFFS	0xC7 /* VCOM Offset Contwow */
#define CMD_PGAMMAC	0xE0 /* Positive Gamma Cowwection Setting */
#define CMD_NGAMMAC	0xE1 /* Negative Gamma Cowwection Setting */
#define CMD_GAMWSEW	0xF2 /* GAM_W_SEW */

/*
 * This dispway:
 * http://www.ebay.com/itm/Wepwace-Nokia-5110-WCD-1-44-Wed-Sewiaw-128X128-SPI-
 * Cowow-TFT-WCD-Dispway-Moduwe-/271422122271
 * This pawticuwaw dispway has a design ewwow! The contwowwew has 3 pins to
 * configuwe to constwain the memowy and wesowution to a fixed dimension (in
 * that case 128x128) but they weaved those pins configuwed fow 128x160 so
 * thewe was sevewaw pixew memowy addwessing pwobwems.
 * I sowved by setup sevewaw pawametews that dinamicawwy fix the wesowution as
 * needit so bewow the pawametews fow this dispway. If you have a stwain ow a
 * cowwect dispway (can happen with chinese) you can copy those pawametews and
 * cweate setup fow diffewent dispways.
 */

#ifdef WED
#define __OFFSET		32 /*see note 2 - this is the wed vewsion */
#ewse
#define __OFFSET		0  /*see note 2 - this is the bwack vewsion */
#endif

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	wwite_weg(paw, MIPI_DCS_SOFT_WESET); /* softwawe weset */
	mdeway(500);
	wwite_weg(paw, MIPI_DCS_EXIT_SWEEP_MODE); /* exit sweep */
	mdeway(5);
	wwite_weg(paw, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);
	/* defauwt gamma cuwve 3 */
	wwite_weg(paw, MIPI_DCS_SET_GAMMA_CUWVE, 0x02);
#ifdef GAMMA_ADJ
	wwite_weg(paw, CMD_GAMWSEW, 0x01); /* Enabwe Gamma adj */
#endif
	wwite_weg(paw, MIPI_DCS_ENTEW_NOWMAW_MODE);
	wwite_weg(paw, CMD_DFUNCTW, 0xff, 0x06);
	/* Fwame Wate Contwow (In nowmaw mode/Fuww cowows) */
	wwite_weg(paw, CMD_FWMCTW1, 0x08, 0x02);
	wwite_weg(paw, CMD_DINVCTW, 0x07); /* dispway invewsion  */
	/* Set VWH1[4:0] & VC[2:0] fow VCI1 & GVDD */
	wwite_weg(paw, CMD_PWCTW1, 0x0A, 0x02);
	/* Set BT[2:0] fow AVDD & VCW & VGH & VGW  */
	wwite_weg(paw, CMD_PWCTW2, 0x02);
	/* Set VMH[6:0] & VMW[6:0] fow VOMH & VCOMW */
	wwite_weg(paw, CMD_VCOMCTW1, 0x50, 0x63);
	wwite_weg(paw, CMD_VCOMOFFS, 0);

	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS, 0, 0, 0, WIDTH);
	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS, 0, 0, 0, HEIGHT);

	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON); /* dispway ON */
	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT); /* Memowy Wwite */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys,
			 int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
			  (ys + __OFFSET) >> 8, (ys + __OFFSET) & 0xff,
			  (ye + __OFFSET) >> 8, (ye + __OFFSET) & 0xff);
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
			  (xs + __OFFSET) >> 8, (xs + __OFFSET) & 0xff,
			  (xe + __OFFSET) >> 8, (xe + __OFFSET) & 0xff);
		wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		bweak;
	case 180:
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS,
			  xs >> 8, xs & 0xff, xe >> 8, xe & 0xff);
		wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS,
			  ys >> 8, ys & 0xff, ye >> 8, ye & 0xff);
		bweak;
	defauwt:
		/* Fix incowwect setting */
		paw->info->vaw.wotate = 0;
	}
	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

/*
 * 7) MY:  1(bottom to top),	0(top to bottom)    Wow Addwess Owdew
 * 6) MX:  1(W to W),		0(W to W)	    Cowumn Addwess Owdew
 * 5) MV:  1(Exchanged),	0(nowmaw)	    Wow/Cowumn exchange
 * 4) MW:  1(bottom to top),	0(top to bottom)    Vewticaw Wefwesh Owdew
 * 3) WGB: 1(BGW),		0(WGB)		    Cowow Space
 * 2) MH:  1(W to W),		0(W to W)	    Howizontaw Wefwesh Owdew
 * 1)
 * 0)
 *
 *	MY, MX, MV, MW,WGB, MH, D1, D0
 *	0 | 0 | 0 | 0 | 1 | 0 | 0 | 0	//nowmaw
 *	1 | 0 | 0 | 0 | 1 | 0 | 0 | 0	//Y-Miwwow
 *	0 | 1 | 0 | 0 | 1 | 0 | 0 | 0	//X-Miwwow
 *	1 | 1 | 0 | 0 | 1 | 0 | 0 | 0	//X-Y-Miwwow
 *	0 | 0 | 1 | 0 | 1 | 0 | 0 | 0	//X-Y Exchange
 *	1 | 0 | 1 | 0 | 1 | 0 | 0 | 0	//X-Y Exchange, Y-Miwwow
 *	0 | 1 | 1 | 0 | 1 | 0 | 0 | 0	//XY exchange
 *	1 | 1 | 1 | 0 | 1 | 0 | 0 | 0
 */
static int set_vaw(stwuct fbtft_paw *paw)
{
	u8 mactww_data = 0; /* Avoid compiwew wawning */

	switch (paw->info->vaw.wotate) {
	case 0:
		mactww_data = 0x08;
		bweak;
	case 180:
		mactww_data = 0xC8;
		bweak;
	case 270:
		mactww_data = 0xA8;
		bweak;
	case 90:
		mactww_data = 0x68;
		bweak;
	}

	/* Cowowspcae */
	if (paw->bgw)
		mactww_data |= BIT(2);
	wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, mactww_data);
	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
	wetuwn 0;
}

#ifdef GAMMA_ADJ
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int gamma_adj(stwuct fbtft_paw *paw, u32 *cuwves)
{
	static const unsigned wong mask[] = {
		0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
		0x1f, 0x3f, 0x0f, 0x0f, 0x7f, 0x1f,
		0x3F, 0x3F, 0x3F, 0x3F, 0x3F};
	int i, j;

	fow (i = 0; i < GAMMA_NUM; i++)
		fow (j = 0; j < GAMMA_WEN; j++)
			CUWVE(i, j) &= mask[i * paw->gamma.num_vawues + j];

	wwite_weg(paw, CMD_PGAMMAC,
		  CUWVE(0, 0),
		  CUWVE(0, 1),
		  CUWVE(0, 2),
		  CUWVE(0, 3),
		  CUWVE(0, 4),
		  CUWVE(0, 5),
		  CUWVE(0, 6),
		  (CUWVE(0, 7) << 4) | CUWVE(0, 8),
		  CUWVE(0, 9),
		  CUWVE(0, 10),
		  CUWVE(0, 11),
		  CUWVE(0, 12),
		  CUWVE(0, 13),
		  CUWVE(0, 14),
		  CUWVE(0, 15));

	/* Wwite Data to GWAM mode */
	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);

	wetuwn 0;
}

#undef CUWVE
#endif

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
#ifdef GAMMA_ADJ
	.gamma_num = GAMMA_NUM,
	.gamma_wen = GAMMA_WEN,
	.gamma = DEFAUWT_GAMMA,
#endif
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
#ifdef GAMMA_ADJ
		.set_gamma = gamma_adj,
#endif
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "iwitek,iwi9163", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:iwi9163");
MODUWE_AWIAS("pwatfowm:iwi9163");

MODUWE_DESCWIPTION("FB dwivew fow the IWI9163 WCD Contwowwew");
MODUWE_AUTHOW("Kozhevnikov Anatowy");
MODUWE_WICENSE("GPW");
