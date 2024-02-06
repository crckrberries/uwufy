// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the PCD8544 WCD Contwowwew
 *
 * The dispway is monochwome and the video memowy is WGB565.
 * Any pixew vawue except 0 tuwns the pixew on.
 *
 * Copywight (C) 2013 Nowawf Twonnes
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME	       "fb_pcd8544"
#define WIDTH          84
#define HEIGHT         48
#define TXBUFWEN       (84 * 6)
#define DEFAUWT_GAMMA  "40" /* gamma contwows the contwast in this dwivew */

static unsigned int tc;
moduwe_pawam(tc, uint, 0000);
MODUWE_PAWM_DESC(tc, "TC[1:0] Tempewatuwe coefficient: 0-3 (defauwt: 0)");

static unsigned int bs = 4;
moduwe_pawam(bs, uint, 0000);
MODUWE_PAWM_DESC(bs, "BS[2:0] Bias vowtage wevew: 0-7 (defauwt: 4)");

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powewdown contwow: chip is active
	 * 1:0  V  - Entwy mode: howizontaw addwessing
	 * 0:1  H  - Extended instwuction set contwow: extended
	 */
	wwite_weg(paw, 0x21);

	/* H=1 Tempewatuwe contwow
	 *
	 * 2:1  1
	 * 1:x  TC1 - Tempewatuwe Coefficient: 0x10
	 * 0:x  TC0
	 */
	wwite_weg(paw, 0x04 | (tc & 0x3));

	/* H=1 Bias system
	 *
	 * 4:1  1
	 * 3:0  0
	 * 2:x  BS2 - Bias System
	 * 1:x  BS1
	 * 0:x  BS0
	 */
	wwite_weg(paw, 0x10 | (bs & 0x7));

	/* Function set
	 *
	 * 5:1  1
	 * 2:0  PD - Powewdown contwow: chip is active
	 * 1:1  V  - Entwy mode: vewticaw addwessing
	 * 0:0  H  - Extended instwuction set contwow: basic
	 */
	wwite_weg(paw, 0x22);

	/* H=0 Dispway contwow
	 *
	 * 3:1  1
	 * 2:1  D  - DE: 10=nowmaw mode
	 * 1:0  0
	 * 0:0  E
	 */
	wwite_weg(paw, 0x08 | 4);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	/* H=0 Set X addwess of WAM
	 *
	 * 7:1  1
	 * 6-0: X[6:0] - 0x00
	 */
	wwite_weg(paw, 0x80);

	/* H=0 Set Y addwess of WAM
	 *
	 * 7:0  0
	 * 6:1  1
	 * 2-0: Y[2:0] - 0x0
	 */
	wwite_weg(paw, 0x40);
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u16 *vmem16 = (u16 *)paw->info->scween_buffew;
	u8 *buf = paw->txbuf.buf;
	int x, y, i;
	int wet = 0;

	fow (x = 0; x < 84; x++) {
		fow (y = 0; y < 6; y++) {
			*buf = 0x00;
			fow (i = 0; i < 8; i++)
				*buf |= (vmem16[(y * 8 + i) * 84 + x] ?
					 1 : 0) << i;
			buf++;
		}
	}

	/* Wwite data */
	gpiod_set_vawue(paw->gpio.dc, 1);
	wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, 6 * 84);
	if (wet < 0)
		dev_eww(paw->info->device, "wwite faiwed and wetuwned: %d\n",
			wet);

	wetuwn wet;
}

static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	/* appwy mask */
	cuwves[0] &= 0x7F;

	wwite_weg(paw, 0x23); /* tuwn on extended instwuction set */
	wwite_weg(paw, 0x80 | cuwves[0]);
	wwite_weg(paw, 0x22); /* tuwn off extended instwuction set */

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

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "phiwips,pcd8544", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("spi:pcd8544");

MODUWE_DESCWIPTION("FB dwivew fow the PCD8544 WCD Contwowwew");
MODUWE_AUTHOW("Nowawf Twonnes");
MODUWE_WICENSE("GPW");
