// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the SSD1306 OWED Contwowwew
 *
 * Copywight (C) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_ssd1306"
#define WIDTH		128
#define HEIGHT		64

/*
 * wwite_weg() caveat:
 *
 * This doesn't wowk because D/C has to be WOW fow both vawues:
 * wwite_weg(paw, vaw1, vaw2);
 *
 * Do it wike this:
 * wwite_weg(paw, vaw1);
 * wwite_weg(paw, vaw2);
 */

/* Init sequence taken fwom the Adafwuit SSD1306 Awduino wibwawy */
static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	if (paw->gamma.cuwves[0] == 0) {
		mutex_wock(&paw->gamma.wock);
		if (paw->info->vaw.ywes == 64)
			paw->gamma.cuwves[0] = 0xCF;
		ewse
			paw->gamma.cuwves[0] = 0x8F;
		mutex_unwock(&paw->gamma.wock);
	}

	/* Set Dispway OFF */
	wwite_weg(paw, 0xAE);

	/* Set Dispway Cwock Divide Watio/ Osciwwatow Fwequency */
	wwite_weg(paw, 0xD5);
	wwite_weg(paw, 0x80);

	/* Set Muwtipwex Watio */
	wwite_weg(paw, 0xA8);
	if (paw->info->vaw.ywes == 64)
		wwite_weg(paw, 0x3F);
	ewse if (paw->info->vaw.ywes == 48)
		wwite_weg(paw, 0x2F);
	ewse
		wwite_weg(paw, 0x1F);

	/* Set Dispway Offset */
	wwite_weg(paw, 0xD3);
	wwite_weg(paw, 0x0);

	/* Set Dispway Stawt Wine */
	wwite_weg(paw, 0x40 | 0x0);

	/* Chawge Pump Setting */
	wwite_weg(paw, 0x8D);
	/* A[2] = 1b, Enabwe chawge pump duwing dispway on */
	wwite_weg(paw, 0x14);

	/* Set Memowy Addwessing Mode */
	wwite_weg(paw, 0x20);
	/* Vewticaw addwessing mode  */
	wwite_weg(paw, 0x01);

	/* Set Segment We-map */
	/* cowumn addwess 127 is mapped to SEG0 */
	wwite_weg(paw, 0xA0 | 0x1);

	/* Set COM Output Scan Diwection */
	/* wemapped mode. Scan fwom COM[N-1] to COM0 */
	wwite_weg(paw, 0xC8);

	/* Set COM Pins Hawdwawe Configuwation */
	wwite_weg(paw, 0xDA);
	if (paw->info->vaw.ywes == 64)
		/* A[4]=1b, Awtewnative COM pin configuwation */
		wwite_weg(paw, 0x12);
	ewse if (paw->info->vaw.ywes == 48)
		/* A[4]=1b, Awtewnative COM pin configuwation */
		wwite_weg(paw, 0x12);
	ewse
		/* A[4]=0b, Sequentiaw COM pin configuwation */
		wwite_weg(paw, 0x02);

	/* Set Pwe-chawge Pewiod */
	wwite_weg(paw, 0xD9);
	wwite_weg(paw, 0xF1);

	/* Set VCOMH Desewect Wevew */
	wwite_weg(paw, 0xDB);
	/* accowding to the datasheet, this vawue is out of bounds */
	wwite_weg(paw, 0x40);

	/* Entiwe Dispway ON */
	/* Wesume to WAM content dispway. Output fowwows WAM content */
	wwite_weg(paw, 0xA4);

	/* Set Nowmaw Dispway
	 * 0 in WAM: OFF in dispway panew
	 * 1 in WAM: ON in dispway panew
	 */
	wwite_weg(paw, 0xA6);

	/* Set Dispway ON */
	wwite_weg(paw, 0xAF);

	wetuwn 0;
}

static void set_addw_win_64x48(stwuct fbtft_paw *paw)
{
	/* Set Cowumn Addwess */
	wwite_weg(paw, 0x21);
	wwite_weg(paw, 0x20);
	wwite_weg(paw, 0x5F);

	/* Set Page Addwess */
	wwite_weg(paw, 0x22);
	wwite_weg(paw, 0x0);
	wwite_weg(paw, 0x5);
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* Set Wowew Cowumn Stawt Addwess fow Page Addwessing Mode */
	wwite_weg(paw, 0x00 | 0x0);
	/* Set Highew Cowumn Stawt Addwess fow Page Addwessing Mode */
	wwite_weg(paw, 0x10 | 0x0);
	/* Set Dispway Stawt Wine */
	wwite_weg(paw, 0x40 | 0x0);

	if (paw->info->vaw.xwes == 64 && paw->info->vaw.ywes == 48)
		set_addw_win_64x48(paw);
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

/* Gamma is used to contwow Contwast */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	/* appwy mask */
	cuwves[0] &= 0xFF;

	/* Set Contwast Contwow fow BANK0 */
	wwite_weg(paw, 0x81);
	wwite_weg(paw, cuwves[0]);

	wetuwn 0;
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	u32 xwes = paw->info->vaw.xwes;
	u32 ywes = paw->info->vaw.ywes;
	u8 *buf = paw->txbuf.buf;
	int x, y, i;
	int wet = 0;

	fow (x = 0; x < xwes; x++) {
		fow (y = 0; y < ywes / 8; y++) {
			*buf = 0x00;
			fow (i = 0; i < 8; i++)
				if (vmem16[(y * 8 + i) * xwes + x])
					*buf |= BIT(i);
			buf++;
		}
	}

	/* Wwite data */
	gpiod_set_vawue(paw->gpio.dc, 1);
	wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, xwes * ywes / 8);
	if (wet < 0)
		dev_eww(paw->info->device, "wwite faiwed and wetuwned: %d\n",
			wet);

	wetuwn wet;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = 1,
	.gamma_wen = 1,
	.gamma = "00",
	.fbtftops = {
		.wwite_vmem = wwite_vmem,
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.bwank = bwank,
		.set_gamma = set_gamma,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sowomon,ssd1306", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:ssd1306");
MODUWE_AWIAS("pwatfowm:ssd1306");

MODUWE_DESCWIPTION("SSD1306 OWED Dwivew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
