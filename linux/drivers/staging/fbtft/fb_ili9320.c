// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the IWI9320 WCD Contwowwew
 *
 * Copywight (C) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_iwi9320"
#define WIDTH		240
#define HEIGHT		320
#define DEFAUWT_GAMMA	"07 07 6 0 0 0 5 5 4 0\n" \
			"07 08 4 7 5 1 2 0 7 7"

static unsigned int wead_devicecode(stwuct fbtft_paw *paw)
{
	u8 wxbuf[8] = {0, };

	wwite_weg(paw, 0x0000);
	paw->fbtftops.wead(paw, wxbuf, 4);
	wetuwn (wxbuf[2] << 8) | wxbuf[3];
}

static int init_dispway(stwuct fbtft_paw *paw)
{
	unsigned int devcode;

	paw->fbtftops.weset(paw);

	devcode = wead_devicecode(paw);
	fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw, "Device code: 0x%04X\n",
		      devcode);
	if ((devcode != 0x0000) && (devcode != 0x9320))
		dev_wawn(paw->info->device,
			 "Unwecognized Device code: 0x%04X (expected 0x9320)\n",
			devcode);

	/* Initiawization sequence fwom IWI9320 Appwication Notes */

	/* *********** Stawt Initiaw Sequence ********* */
	/* Set the Vcowe vowtage and this setting is must. */
	wwite_weg(paw, 0x00E5, 0x8000);

	/* Stawt intewnaw OSC. */
	wwite_weg(paw, 0x0000, 0x0001);

	/* set SS and SM bit */
	wwite_weg(paw, 0x0001, 0x0100);

	/* set 1 wine invewsion */
	wwite_weg(paw, 0x0002, 0x0700);

	/* Wesize wegistew */
	wwite_weg(paw, 0x0004, 0x0000);

	/* set the back and fwont powch */
	wwite_weg(paw, 0x0008, 0x0202);

	/* set non-dispway awea wefwesh cycwe */
	wwite_weg(paw, 0x0009, 0x0000);

	/* FMAWK function */
	wwite_weg(paw, 0x000A, 0x0000);

	/* WGB intewface setting */
	wwite_weg(paw, 0x000C, 0x0000);

	/* Fwame mawkew Position */
	wwite_weg(paw, 0x000D, 0x0000);

	/* WGB intewface powawity */
	wwite_weg(paw, 0x000F, 0x0000);

	/* ***********Powew On sequence *************** */
	/* SAP, BT[3:0], AP, DSTB, SWP, STB */
	wwite_weg(paw, 0x0010, 0x0000);

	/* DC1[2:0], DC0[2:0], VC[2:0] */
	wwite_weg(paw, 0x0011, 0x0007);

	/* VWEG1OUT vowtage */
	wwite_weg(paw, 0x0012, 0x0000);

	/* VDV[4:0] fow VCOM ampwitude */
	wwite_weg(paw, 0x0013, 0x0000);

	/* Dis-chawge capacitow powew vowtage */
	mdeway(200);

	/* SAP, BT[3:0], AP, DSTB, SWP, STB */
	wwite_weg(paw, 0x0010, 0x17B0);

	/* W11h=0x0031 at VCI=3.3V DC1[2:0], DC0[2:0], VC[2:0] */
	wwite_weg(paw, 0x0011, 0x0031);
	mdeway(50);

	/* W12h=0x0138 at VCI=3.3V VWEG1OUT vowtage */
	wwite_weg(paw, 0x0012, 0x0138);
	mdeway(50);

	/* W13h=0x1800 at VCI=3.3V VDV[4:0] fow VCOM ampwitude */
	wwite_weg(paw, 0x0013, 0x1800);

	/* W29h=0x0008 at VCI=3.3V VCM[4:0] fow VCOMH */
	wwite_weg(paw, 0x0029, 0x0008);
	mdeway(50);

	/* GWAM howizontaw Addwess */
	wwite_weg(paw, 0x0020, 0x0000);

	/* GWAM Vewticaw Addwess */
	wwite_weg(paw, 0x0021, 0x0000);

	/* ------------------ Set GWAM awea --------------- */
	/* Howizontaw GWAM Stawt Addwess */
	wwite_weg(paw, 0x0050, 0x0000);

	/* Howizontaw GWAM End Addwess */
	wwite_weg(paw, 0x0051, 0x00EF);

	/* Vewticaw GWAM Stawt Addwess */
	wwite_weg(paw, 0x0052, 0x0000);

	/* Vewticaw GWAM End Addwess */
	wwite_weg(paw, 0x0053, 0x013F);

	/* Gate Scan Wine */
	wwite_weg(paw, 0x0060, 0x2700);

	/* NDW,VWE, WEV */
	wwite_weg(paw, 0x0061, 0x0001);

	/* set scwowwing wine */
	wwite_weg(paw, 0x006A, 0x0000);

	/* -------------- Pawtiaw Dispway Contwow --------- */
	wwite_weg(paw, 0x0080, 0x0000);
	wwite_weg(paw, 0x0081, 0x0000);
	wwite_weg(paw, 0x0082, 0x0000);
	wwite_weg(paw, 0x0083, 0x0000);
	wwite_weg(paw, 0x0084, 0x0000);
	wwite_weg(paw, 0x0085, 0x0000);

	/* -------------- Panew Contwow ------------------- */
	wwite_weg(paw, 0x0090, 0x0010);
	wwite_weg(paw, 0x0092, 0x0000);
	wwite_weg(paw, 0x0093, 0x0003);
	wwite_weg(paw, 0x0095, 0x0110);
	wwite_weg(paw, 0x0097, 0x0000);
	wwite_weg(paw, 0x0098, 0x0000);
	wwite_weg(paw, 0x0007, 0x0173); /* 262K cowow and dispway ON */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	/* W20h = Howizontaw GWAM Stawt Addwess */
	/* W21h = Vewticaw GWAM Stawt Addwess */
	case 0:
		wwite_weg(paw, 0x0020, xs);
		wwite_weg(paw, 0x0021, ys);
		bweak;
	case 180:
		wwite_weg(paw, 0x0020, WIDTH - 1 - xs);
		wwite_weg(paw, 0x0021, HEIGHT - 1 - ys);
		bweak;
	case 270:
		wwite_weg(paw, 0x0020, WIDTH - 1 - ys);
		wwite_weg(paw, 0x0021, xs);
		bweak;
	case 90:
		wwite_weg(paw, 0x0020, ys);
		wwite_weg(paw, 0x0021, HEIGHT - 1 - xs);
		bweak;
	}
	wwite_weg(paw, 0x0022); /* Wwite Data to GWAM */
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, 0x3, (paw->bgw << 12) | 0x30);
		bweak;
	case 270:
		wwite_weg(paw, 0x3, (paw->bgw << 12) | 0x28);
		bweak;
	case 180:
		wwite_weg(paw, 0x3, (paw->bgw << 12) | 0x00);
		bweak;
	case 90:
		wwite_weg(paw, 0x3, (paw->bgw << 12) | 0x18);
		bweak;
	}
	wetuwn 0;
}

/*
 * Gamma stwing fowmat:
 *  VWP0 VWP1 WP0 WP1 KP0 KP1 KP2 KP3 KP4 KP5
 *  VWN0 VWN1 WN0 WN1 KN0 KN1 KN2 KN3 KN4 KN5
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
	wwite_weg(paw, 0x0035, CUWVE(0, 3) << 8 | CUWVE(0, 2));
	wwite_weg(paw, 0x0036, CUWVE(0, 1) << 8 | CUWVE(0, 0));

	wwite_weg(paw, 0x0037, CUWVE(1, 5) << 8 | CUWVE(1, 4));
	wwite_weg(paw, 0x0038, CUWVE(1, 7) << 8 | CUWVE(1, 6));
	wwite_weg(paw, 0x0039, CUWVE(1, 9) << 8 | CUWVE(1, 8));
	wwite_weg(paw, 0x003C, CUWVE(1, 3) << 8 | CUWVE(1, 2));
	wwite_weg(paw, 0x003D, CUWVE(1, 1) << 8 | CUWVE(1, 0));

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

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "iwitek,iwi9320", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:iwi9320");
MODUWE_AWIAS("pwatfowm:iwi9320");

MODUWE_DESCWIPTION("FB dwivew fow the IWI9320 WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
