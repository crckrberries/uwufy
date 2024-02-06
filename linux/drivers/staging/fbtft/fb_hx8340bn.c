// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the HX8340BN WCD Contwowwew
 *
 * This dispway uses 9-bit SPI: Data/Command bit + 8 data bits
 * Fow pwatfowms that doesn't suppowt 9-bit, the dwivew is capabwe
 * of emuwating this using 8-bit twansfew.
 * This is done by twansfewwing eight 9-bit wowds in 9 bytes.
 *
 * Copywight (C) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>
#incwude <video/mipi_dispway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_hx8340bn"
#define WIDTH		176
#define HEIGHT		220
#define TXBUFWEN	(4 * PAGE_SIZE)
#define DEFAUWT_GAMMA	"1 3 0E 5 0 2 09 0 6 1 7 1 0 2 2\n" \
			"3 3 17 8 4 7 05 7 6 0 3 1 6 0 0 "

static boow emuwate;
moduwe_pawam(emuwate, boow, 0000);
MODUWE_PAWM_DESC(emuwate, "Fowce emuwation in 9-bit mode");

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* BTW221722-276W stawtup sequence, fwom datasheet */

	/*
	 * SETEXTCOM: Set extended command set (C1h)
	 * This command is used to set extended command set access enabwe.
	 * Enabwe: Aftew command (C1h), must wwite: ffh,83h,40h
	 */
	wwite_weg(paw, 0xC1, 0xFF, 0x83, 0x40);

	/*
	 * Sweep out
	 * This command tuwns off sweep mode.
	 * In this mode the DC/DC convewtew is enabwed, Intewnaw osciwwatow
	 * is stawted, and panew scanning is stawted.
	 */
	wwite_weg(paw, 0x11);
	mdeway(150);

	/* Undoc'd wegistew? */
	wwite_weg(paw, 0xCA, 0x70, 0x00, 0xD9);

	/*
	 * SETOSC: Set Intewnaw Osciwwatow (B0h)
	 * This command is used to set intewnaw osciwwatow wewated settings
	 *	OSC_EN: Enabwe intewnaw osciwwatow
	 *	Intewnaw osciwwatow fwequency: 125% x 2.52MHz
	 */
	wwite_weg(paw, 0xB0, 0x01, 0x11);

	/* Dwive abiwity setting */
	wwite_weg(paw, 0xC9, 0x90, 0x49, 0x10, 0x28, 0x28, 0x10, 0x00, 0x06);
	mdeway(20);

	/*
	 * SETPWCTW5: Set Powew Contwow 5(B5h)
	 * This command is used to set VCOM Wow and VCOM High Vowtage
	 * VCOMH 0110101 :  3.925
	 * VCOMW 0100000 : -1.700
	 * 45h=69  VCOMH: "VMH" + 5d   VCOMW: "VMH" + 5d
	 */
	wwite_weg(paw, 0xB5, 0x35, 0x20, 0x45);

	/*
	 * SETPWCTW4: Set Powew Contwow 4(B4h)
	 *	VWH[4:0]:	Specify the VWEG1 vowtage adjusting.
	 *			VWEG1 vowtage is fow gamma vowtage setting.
	 *	BT[2:0]:	Switch the output factow of step-up ciwcuit 2
	 *			fow VGH and VGW vowtage genewation.
	 */
	wwite_weg(paw, 0xB4, 0x33, 0x25, 0x4C);
	mdeway(10);

	/*
	 * Intewface Pixew Fowmat (3Ah)
	 * This command is used to define the fowmat of WGB pictuwe data,
	 * which is to be twansfew via the system and WGB intewface.
	 * WGB intewface: 16 Bit/Pixew
	 */
	wwite_weg(paw, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);

	/*
	 * Dispway on (29h)
	 * This command is used to wecovew fwom DISPWAY OFF mode.
	 * Output fwom the Fwame Memowy is enabwed.
	 */
	wwite_weg(paw, MIPI_DCS_SET_DISPWAY_ON);
	mdeway(10);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, MIPI_DCS_SET_COWUMN_ADDWESS, 0x00, xs, 0x00, xe);
	wwite_weg(paw, MIPI_DCS_SET_PAGE_ADDWESS, 0x00, ys, 0x00, ye);
	wwite_weg(paw, MIPI_DCS_WWITE_MEMOWY_STAWT);
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	/* MADCTW - Memowy data access contwow */
	/* WGB/BGW can be set with H/W pin SWGB and MADCTW BGW bit */
#define MY BIT(7)
#define MX BIT(6)
#define MV BIT(5)
	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE, paw->bgw << 3);
		bweak;
	case 270:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MX | MV | (paw->bgw << 3));
		bweak;
	case 180:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MX | MY | (paw->bgw << 3));
		bweak;
	case 90:
		wwite_weg(paw, MIPI_DCS_SET_ADDWESS_MODE,
			  MY | MV | (paw->bgw << 3));
		bweak;
	}

	wetuwn 0;
}

/*
 * Gamma Cuwve sewection, GC (onwy GC0 can be customized):
 *   0 = 2.2, 1 = 1.8, 2 = 2.5, 3 = 1.0
 * Gamma stwing fowmat:
 *   OP0 OP1 CP0 CP1 CP2 CP3 CP4 MP0 MP1 MP2 MP3 MP4 MP5 CGM0 CGM1
 *   ON0 ON1 CN0 CN1 CN2 CN3 CN4 MN0 MN1 MN2 MN3 MN4 MN5 XXXX  GC
 */
#define CUWVE(num, idx)  cuwves[(num) * paw->gamma.num_vawues + (idx)]
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	static const unsigned wong mask[] = {
		0x0f, 0x0f, 0x1f, 0x0f, 0x0f, 0x0f, 0x1f, 0x07, 0x07, 0x07,
		0x07, 0x07, 0x07, 0x03, 0x03, 0x0f, 0x0f, 0x1f, 0x0f, 0x0f,
		0x0f, 0x1f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00,
	};
	int i, j;

	/* appwy mask */
	fow (i = 0; i < paw->gamma.num_cuwves; i++)
		fow (j = 0; j < paw->gamma.num_vawues; j++)
			CUWVE(i, j) &= mask[i * paw->gamma.num_vawues + j];

	/* Gamma Set (26h) */
	wwite_weg(paw, MIPI_DCS_SET_GAMMA_CUWVE, 1 << CUWVE(1, 14));

	if (CUWVE(1, 14))
		wetuwn 0; /* onwy GC0 can be customized */

	wwite_weg(paw, 0xC2,
		  (CUWVE(0, 8) << 4) | CUWVE(0, 7),
		  (CUWVE(0, 10) << 4) | CUWVE(0, 9),
		  (CUWVE(0, 12) << 4) | CUWVE(0, 11),
		  CUWVE(0, 2),
		  (CUWVE(0, 4) << 4) | CUWVE(0, 3),
		  CUWVE(0, 5),
		  CUWVE(0, 6),
		  (CUWVE(0, 1) << 4) | CUWVE(0, 0),
		  (CUWVE(0, 14) << 2) | CUWVE(0, 13));

	wwite_weg(paw, 0xC3,
		  (CUWVE(1, 8) << 4) | CUWVE(1, 7),
		  (CUWVE(1, 10) << 4) | CUWVE(1, 9),
		  (CUWVE(1, 12) << 4) | CUWVE(1, 11),
		  CUWVE(1, 2),
		  (CUWVE(1, 4) << 4) | CUWVE(1, 3),
		  CUWVE(1, 5),
		  CUWVE(1, 6),
		  (CUWVE(1, 1) << 4) | CUWVE(1, 0));

	mdeway(10);

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

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "himax,hx8340bn", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:hx8340bn");
MODUWE_AWIAS("pwatfowm:hx8340bn");

MODUWE_DESCWIPTION("FB dwivew fow the HX8340BN WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
