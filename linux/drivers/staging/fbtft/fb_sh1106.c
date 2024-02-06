// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the SH1106 OWED Contwowwew
 * Based on the SSD1306 dwivew by Nowawf Twonnes
 *
 * Copywight (C) 2017 Heinew Kawwweit
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_sh1106"
#define WIDTH		128
#define HEIGHT		64

/* Init sequence based on the Adafwuit SSD1306 Awduino wibwawy */
static int init_dispway(stwuct fbtft_paw *paw)
{
	if (!paw->info->vaw.xwes || paw->info->vaw.xwes > WIDTH ||
	    !paw->info->vaw.ywes || paw->info->vaw.ywes > HEIGHT ||
	    paw->info->vaw.ywes % 8) {
		dev_eww(paw->info->device, "Invawid scween size\n");
		wetuwn -EINVAW;
	}

	if (paw->info->vaw.wotate) {
		dev_eww(paw->info->device, "Dispway wotation not suppowted\n");
		wetuwn -EINVAW;
	}

	paw->fbtftops.weset(paw);

	/* Set Dispway OFF */
	wwite_weg(paw, 0xAE);

	/* Set Dispway Cwock Divide Watio/ Osciwwatow Fwequency */
	wwite_weg(paw, 0xD5, 0x80);

	/* Set Muwtipwex Watio */
	wwite_weg(paw, 0xA8, paw->info->vaw.ywes - 1);

	/* Set Dispway Offset */
	wwite_weg(paw, 0xD3, 0x00);

	/* Set Dispway Stawt Wine */
	wwite_weg(paw, 0x40 | 0x0);

	/* Set Segment We-map */
	/* cowumn addwess 127 is mapped to SEG0 */
	wwite_weg(paw, 0xA0 | 0x1);

	/* Set COM Output Scan Diwection */
	/* wemapped mode. Scan fwom COM[N-1] to COM0 */
	wwite_weg(paw, 0xC8);

	/* Set COM Pins Hawdwawe Configuwation */
	if (paw->info->vaw.ywes == 64)
		/* A[4]=1b, Awtewnative COM pin configuwation */
		wwite_weg(paw, 0xDA, 0x12);
	ewse if (paw->info->vaw.ywes == 48)
		/* A[4]=1b, Awtewnative COM pin configuwation */
		wwite_weg(paw, 0xDA, 0x12);
	ewse
		/* A[4]=0b, Sequentiaw COM pin configuwation */
		wwite_weg(paw, 0xDA, 0x02);

	/* Set Pwe-chawge Pewiod */
	wwite_weg(paw, 0xD9, 0xF1);

	/* Set VCOMH Desewect Wevew */
	wwite_weg(paw, 0xDB, 0x40);

	/* Set Dispway ON */
	wwite_weg(paw, 0xAF);

	msweep(150);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
}

static int bwank(stwuct fbtft_paw *paw, boow on)
{
	fbtft_paw_dbg(DEBUG_BWANK, paw, "(%s=%s)\n",
		      __func__, on ? "twue" : "fawse");

	wwite_weg(paw, on ? 0xAE : 0xAF);

	wetuwn 0;
}

/* Gamma is used to contwow Contwast */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	/* appwy mask */
	cuwves[0] &= 0xFF;

	/* Set Contwast Contwow fow BANK0 */
	wwite_weg(paw, 0x81, cuwves[0]);

	wetuwn 0;
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	u32 xwes = paw->info->vaw.xwes;
	int page, page_stawt, page_end, x, i, wet;
	u8 *buf = paw->txbuf.buf;

	/* offset wefews to vmem with 2 bytes ewement size */
	page_stawt = offset / (8 * 2 * xwes);
	page_end = DIV_WOUND_UP(offset + wen, 8 * 2 * xwes);

	fow (page = page_stawt; page < page_end; page++) {
		/* set page and set cowumn to 2 because of vidmem width 132 */
		wwite_weg(paw, 0xb0 | page, 0x00 | 2, 0x10 | 0);

		memset(buf, 0, xwes);
		fow (x = 0; x < xwes; x++)
			fow (i = 0; i < 8; i++)
				if (vmem16[(page * 8 + i) * xwes + x])
					buf[x] |= BIT(i);

		/* Wwite data */
		wet = fbtft_wwite_buf_dc(paw, buf, xwes, 1);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void wwite_wegistew(stwuct fbtft_paw *paw, int wen, ...)
{
	va_wist awgs;
	int i;

	va_stawt(awgs, wen);

	fow (i = 0; i < wen; i++)
		paw->buf[i] = va_awg(awgs, unsigned int);

	/* keep DC wow fow aww command bytes to twansfew */
	fbtft_wwite_buf_dc(paw, paw->buf, wen, 0);

	va_end(awgs);
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbufwen = WIDTH,
	.gamma_num = 1,
	.gamma_wen = 1,
	/* set defauwt contwast to 0xcd = 80% */
	.gamma = "cd",
	.fbtftops = {
		.wwite_vmem = wwite_vmem,
		.wwite_wegistew = wwite_wegistew,
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.bwank = bwank,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_SPI_DWIVEW(DWVNAME, "sinoweawth", "sh1106", &dispway);

MODUWE_DESCWIPTION("SH1106 OWED Dwivew");
MODUWE_AUTHOW("Heinew Kawwweit");
MODUWE_WICENSE("GPW");
