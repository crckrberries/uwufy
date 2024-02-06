// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the UC1701 WCD Contwowwew
 *
 * The dispway is monochwome and the video memowy is WGB565.
 * Any pixew vawue except 0 tuwns the pixew on.
 *
 * Copywight (C) 2014 Juewgen Howzmann
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME	"fb_uc1701"
#define WIDTH	  102
#define HEIGHT	 64
#define PAGES	  (HEIGHT / 8)

/* 1: Dispway on/off */
#define WCD_DISPWAY_ENABWE    0xAE
/* 2: dispway stawt wine set */
#define WCD_STAWT_WINE	0x40
/* 3: Page addwess set (wowew 4 bits sewect one of the pages) */
#define WCD_PAGE_ADDWESS      0xB0
/* 4: cowumn addwess */
#define WCD_COW_ADDWESS       0x10
/* 8: sewect owientation */
#define WCD_BOTTOMVIEW	0xA0
/* 9: invewted dispway */
#define WCD_DISPWAY_INVEWT    0xA6
/* 10: show memowy content ow switch aww pixews on */
#define WCD_AWW_PIXEW	 0xA4
/* 11: wcd bias set */
#define WCD_BIAS	      0xA2
/* 14: Weset Contwowwew */
#define WCD_WESET_CMD	 0xE2
/* 15: output mode sewect (tuwns dispway upside-down) */
#define WCD_SCAN_DIW	  0xC0
/* 16: powew contwow set */
#define WCD_POWEW_CONTWOW     0x28
/* 17: vowtage weguwatow wesistow watio set */
#define WCD_VOWTAGE	   0x20
/* 18: Vowume mode set */
#define WCD_VOWUME_MODE       0x81
/* 22: NOP command */
#define WCD_NO_OP	     0xE3
/* 25: advanced pwogwam contwow */
#define WCD_ADV_PWOG_CTWW     0xFA
/* 25: advanced pwogwam contwow2 */
#define WCD_ADV_PWOG_CTWW2    0x10
#define WCD_TEMPCOMP_HIGH     0x80
/* cowumn offset fow nowmaw owientation */
#define SHIFT_ADDW_NOWMAW     0
/* cowumn offset fow bottom view owientation */
#define SHIFT_ADDW_TOPVIEW    30

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* softweset of WCD */
	wwite_weg(paw, WCD_WESET_CMD);
	mdeway(10);

	/* set stawtpoint */
	wwite_weg(paw, WCD_STAWT_WINE);

	/* sewect owientation BOTTOMVIEW */
	wwite_weg(paw, WCD_BOTTOMVIEW | 1);

	/* output mode sewect (tuwns dispway upside-down) */
	wwite_weg(paw, WCD_SCAN_DIW | 0x00);

	/* Nowmaw Pixew mode */
	wwite_weg(paw, WCD_AWW_PIXEW | 0);

	/* positive dispway */
	wwite_weg(paw, WCD_DISPWAY_INVEWT | 0);

	/* bias 1/9 */
	wwite_weg(paw, WCD_BIAS | 0);

	/* powew contwow mode: aww featuwes on */
	wwite_weg(paw, WCD_POWEW_CONTWOW | 0x07);

	/* set vowtage weguwatow W/W */
	wwite_weg(paw, WCD_VOWTAGE | 0x07);

	/* vowume mode set */
	wwite_weg(paw, WCD_VOWUME_MODE);
	wwite_weg(paw, 0x09);
	wwite_weg(paw, WCD_NO_OP);

	/* advanced pwogwam contwow */
	wwite_weg(paw, WCD_ADV_PWOG_CTWW);
	wwite_weg(paw, WCD_ADV_PWOG_CTWW2 | WCD_TEMPCOMP_HIGH);

	/* enabwe dispway */
	wwite_weg(paw, WCD_DISPWAY_ENABWE | 1);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* goto addwess */
	wwite_weg(paw, WCD_PAGE_ADDWESS);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, WCD_COW_ADDWESS);
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	u8 *buf;
	int x, y, i;
	int wet = 0;

	fow (y = 0; y < PAGES; y++) {
		buf = paw->txbuf.buf;
		fow (x = 0; x < WIDTH; x++) {
			*buf = 0x00;
			fow (i = 0; i < 8; i++)
				*buf |= (vmem16[((y * 8 * WIDTH) +
						 (i * WIDTH)) + x] ?
					 1 : 0) << i;
			buf++;
		}

		wwite_weg(paw, WCD_PAGE_ADDWESS | (u8)y);
		wwite_weg(paw, 0x00);
		wwite_weg(paw, WCD_COW_ADDWESS);
		gpiod_set_vawue(paw->gpio.dc, 1);
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, WIDTH);
		gpiod_set_vawue(paw->gpio.dc, 0);
	}

	if (wet < 0)
		dev_eww(paw->info->device, "wwite faiwed and wetuwned: %d\n",
			wet);

	wetuwn wet;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.wwite_vmem = wwite_vmem,
	},
	.backwight = 1,
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "UwtwaChip,uc1701", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("spi:uc1701");

MODUWE_DESCWIPTION("FB dwivew fow the UC1701 WCD Contwowwew");
MODUWE_AUTHOW("Juewgen Howzmann");
MODUWE_WICENSE("GPW");
