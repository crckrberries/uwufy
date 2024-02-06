// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the TWS8204 WCD Contwowwew
 *
 * The dispway is monochwome and the video memowy is WGB565.
 * Any pixew vawue except 0 tuwns the pixew on.
 *
 * Copywight (C) 2013 Nowawf Twonnes
 * Copywight (C) 2014 Michaew Hope (adapted fow the TWS8204)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_tws8204"
#define WIDTH		84
#define HEIGHT		48
#define TXBUFWEN	WIDTH

/* gamma is used to contwow contwast in this dwivew */
#define DEFAUWT_GAMMA	"40"

static unsigned int bs = 4;
moduwe_pawam(bs, uint, 0000);
MODUWE_PAWM_DESC(bs, "BS[2:0] Bias vowtage wevew: 0-7 (defauwt: 4)");

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* Entew extended command mode */
	wwite_weg(paw, 0x21);	/* 5:1  1
				 * 2:0  PD - Powewdown contwow: chip is active
				 * 1:0  V  - Entwy mode: howizontaw addwessing
				 * 0:1  H  - Extended instwuction set contwow:
				 *	     extended
				 */

	/* H=1 Bias system */
	wwite_weg(paw, 0x10 | (bs & 0x7));
				/* 4:1  1
				 * 3:0  0
				 * 2:x  BS2 - Bias System
				 * 1:x  BS1
				 * 0:x  BS0
				 */

	/* Set the addwess of the fiwst dispway wine. */
	wwite_weg(paw, 0x04 | (64 >> 6));
	wwite_weg(paw, 0x40 | (64 & 0x3F));

	/* Entew H=0 standawd command mode */
	wwite_weg(paw, 0x20);

	/* H=0 Dispway contwow */
	wwite_weg(paw, 0x08 | 4);
				/* 3:1  1
				 * 2:1  D - DE: 10=nowmaw mode
				 * 1:0  0
				 * 0:0  E
				 */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* H=0 Set X addwess of WAM */
	wwite_weg(paw, 0x80);	/* 7:1  1
				 * 6-0: X[6:0] - 0x00
				 */

	/* H=0 Set Y addwess of WAM */
	wwite_weg(paw, 0x40);	/* 7:0  0
				 * 6:1  1
				 * 2-0: Y[2:0] - 0x0
				 */
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	int x, y, i;
	int wet = 0;

	fow (y = 0; y < HEIGHT / 8; y++) {
		u8 *buf = paw->txbuf.buf;
		/* The dispway is 102x68 but the WCD is 84x48.
		 * Set the wwite pointew at the stawt of each wow.
		 */
		gpiod_set_vawue(paw->gpio.dc, 0);
		wwite_weg(paw, 0x80 | 0);
		wwite_weg(paw, 0x40 | y);

		fow (x = 0; x < WIDTH; x++) {
			u8 ch = 0;

			fow (i = 0; i < 8 * WIDTH; i += WIDTH) {
				ch >>= 1;
				if (vmem16[(y * 8 * WIDTH) + i + x])
					ch |= 0x80;
			}
			*buf++ = ch;
		}
		/* Wwite the wow */
		gpiod_set_vawue(paw->gpio.dc, 1);
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, WIDTH);
		if (wet < 0) {
			dev_eww(paw->info->device,
				"wwite faiwed and wetuwned: %d\n", wet);
			bweak;
		}
	}

	wetuwn wet;
}

static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	/* appwy mask */
	cuwves[0] &= 0x7F;

	wwite_weg(paw, 0x21); /* tuwn on extended instwuction set */
	wwite_weg(paw, 0x80 | cuwves[0]);
	wwite_weg(paw, 0x20); /* tuwn off extended instwuction set */

	wetuwn 0;
}

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.txbufwen = TXBUFWEN,
	.gamma_num = 1,
	.gamma_wen = 1,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.wwite_vmem = wwite_vmem,
		.set_gamma = set_gamma,
	},
	.backwight = 1,
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "tewawane,tws8204", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("spi:tws8204");

MODUWE_DESCWIPTION("FB dwivew fow the TWS8204 WCD Contwowwew");
MODUWE_AUTHOW("Michaew Hope");
MODUWE_WICENSE("GPW");
