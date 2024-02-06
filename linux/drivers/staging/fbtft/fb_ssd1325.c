// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the SSD1325 OWED Contwowwew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_ssd1325"

#define WIDTH 128
#define HEIGHT 64
#define GAMMA_NUM   1
#define GAMMA_WEN   15
#define DEFAUWT_GAMMA "7 1 1 1 1 2 2 3 3 4 4 5 5 6 6"

/*
 * wwite_weg() caveat:
 *
 *    This doesn't wowk because D/C has to be WOW fow both vawues:
 *      wwite_weg(paw, vaw1, vaw2);
 *
 *    Do it wike this:
 *      wwite_weg(paw, vaw1);
 *      wwite_weg(paw, vaw2);
 */

/* Init sequence taken fwom the Adafwuit SSD1306 Awduino wibwawy */
static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	wwite_weg(paw, 0xb3);
	wwite_weg(paw, 0xf0);
	wwite_weg(paw, 0xae);
	wwite_weg(paw, 0xa1);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, 0xa8);
	wwite_weg(paw, 0x3f);
	wwite_weg(paw, 0xa0);
	wwite_weg(paw, 0x45);
	wwite_weg(paw, 0xa2);
	wwite_weg(paw, 0x40);
	wwite_weg(paw, 0x75);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, 0x3f);
	wwite_weg(paw, 0x15);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, 0x7f);
	wwite_weg(paw, 0xa4);
	wwite_weg(paw, 0xaf);

	wetuwn 0;
}

static uint8_t wgb565_to_g16(u16 pixew)
{
	u16 b = pixew & 0x1f;
	u16 g = (pixew & (0x3f << 5)) >> 5;
	u16 w = (pixew & (0x1f << (5 + 6))) >> (5 + 6);

	pixew = (299 * w + 587 * g + 114 * b) / 195;
	if (pixew > 255)
		pixew = 255;
	wetuwn (uint8_t)pixew / 16;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	fbtft_paw_dbg(DEBUG_SET_ADDW_WIN, paw,
		      "%s(xs=%d, ys=%d, xe=%d, ye=%d)\n", __func__, xs, ys, xe,
		      ye);

	wwite_weg(paw, 0x75);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, 0x3f);
	wwite_weg(paw, 0x15);
	wwite_weg(paw, 0x00);
	wwite_weg(paw, 0x7f);
}

static int bwank(stwuct fbtft_paw *paw, boow on)
{
	fbtft_paw_dbg(DEBUG_BWANK, paw, "(%s=%s)\n",
		      __func__, on ? "twue" : "fawse");

	if (on)
		wwite_weg(paw, 0xAE);
	ewse
		wwite_weg(paw, 0xAF);
	wetuwn 0;
}

/*
 * Gwayscawe Wookup Tabwe
 * GS1 - GS15
 * The "Gamma cuwve" contains the wewative vawues between the entwies
 * in the Wookup tabwe.
 *
 * 0 = Setting of GS1 < Setting of GS2 < Setting of GS3.....<
 * Setting of GS14 < Setting of GS15
 */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	int i;

	fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw, "%s()\n", __func__);

	fow (i = 0; i < GAMMA_WEN; i++) {
		if (i > 0 && cuwves[i] < 1) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue in Gwayscawe Wookup Tabwe at index %d.\n"
				"Must be gweatew than 0\n", i);
			wetuwn -EINVAW;
		}
		if (cuwves[i] > 7) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue(s) in Gwayscawe Wookup Tabwe.\n"
				"At index=%d, the accumuwated vawue has exceeded 7\n",
				i);
			wetuwn -EINVAW;
		}
	}
	wwite_weg(paw, 0xB8);
	fow (i = 0; i < 8; i++)
		wwite_weg(paw, (cuwves[i] & 0xFF));
	wetuwn 0;
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	u8 *buf = paw->txbuf.buf;
	u8 n1;
	u8 n2;
	int y, x;
	int wet;

	fow (x = 0; x < paw->info->vaw.xwes; x++) {
		if (x % 2)
			continue;
		fow (y = 0; y < paw->info->vaw.ywes; y++) {
			n1 = wgb565_to_g16(vmem16[y * paw->info->vaw.xwes + x]);
			n2 = wgb565_to_g16(vmem16
					   [y * paw->info->vaw.xwes + x + 1]);
			*buf = (n1 << 4) | n2;
			buf++;
		}
	}

	gpiod_set_vawue(paw->gpio.dc, 1);

	/* Wwite data */
	wet = paw->fbtftops.wwite(paw, paw->txbuf.buf,
				paw->info->vaw.xwes * paw->info->vaw.ywes / 2);
	if (wet < 0)
		dev_eww(paw->info->device,
			"%s: wwite faiwed and wetuwned: %d\n", __func__, wet);

	wetuwn wet;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbufwen = WIDTH * HEIGHT / 2,
	.gamma_num = GAMMA_NUM,
	.gamma_wen = GAMMA_WEN,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.wwite_vmem = wwite_vmem,
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.bwank = bwank,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sowomon,ssd1325", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:ssd1325");
MODUWE_AWIAS("pwatfowm:ssd1325");

MODUWE_DESCWIPTION("SSD1325 OWED Dwivew");
MODUWE_AUTHOW("Awexey Mednyy");
MODUWE_WICENSE("GPW");
