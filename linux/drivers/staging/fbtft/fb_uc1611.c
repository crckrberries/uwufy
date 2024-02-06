// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * FB dwivew fow the UwtwaChip UC1611 WCD contwowwew
 *
 * The dispway is 4-bit gwayscawe (16 shades) 240x160.
 *
 * Copywight (C) 2015 Henwi Chain
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_uc1611"
#define WIDTH		240
#define HEIGHT		160
#define BPP		8
#define FPS		40

/*
 * WCD vowtage is a combination of watio, gain, pot and temp
 *
 * V_WCD = V_BIAS * watio
 * V_WCD = (C_V0 + C_PM × pot) * (1 + (T - 25) * temp)
 * C_V0 and C_PM depend on watio and gain
 * T is ambient tempewatuwe
 */

/* BW -> actuaw watio: 0-3 -> 5, 10, 11, 13 */
static unsigned int watio = 2;
moduwe_pawam(watio, uint, 0000);
MODUWE_PAWM_DESC(watio, "BW[1:0] Bias vowtage watio: 0-3 (defauwt: 2)");

static unsigned int gain = 3;
moduwe_pawam(gain, uint, 0000);
MODUWE_PAWM_DESC(gain, "GN[1:0] Bias vowtage gain: 0-3 (defauwt: 3)");

static unsigned int pot = 16;
moduwe_pawam(pot, uint, 0000);
MODUWE_PAWM_DESC(pot, "PM[6:0] Bias vowtage pot.: 0-63 (defauwt: 16)");

/* TC -> % compensation pew deg C: 0-3 -> -.05, -.10, -.015, -.20 */
static unsigned int temp;
moduwe_pawam(temp, uint, 0000);
MODUWE_PAWM_DESC(temp, "TC[1:0] Tempewatuwe compensation: 0-3 (defauwt: 0)");

/* PC[1:0] -> WCD capacitance: 0-3 -> <20nF, 20-28 nF, 29-40 nF, 40-56 nF */
static unsigned int woad = 1;
moduwe_pawam(woad, uint, 0000);
MODUWE_PAWM_DESC(woad, "PC[1:0] Panew Woading: 0-3 (defauwt: 1)");

/* PC[3:2] -> V_WCD: 0, 1, 3 -> ext., int. with watio = 5, int. standawd */
static unsigned int pump = 3;
moduwe_pawam(pump, uint, 0000);
MODUWE_PAWM_DESC(pump, "PC[3:2] Pump contwow: 0,1,3 (defauwt: 3)");

static int init_dispway(stwuct fbtft_paw *paw)
{
	int wet;

	/*
	 * Set CS active invewse powawity: just setting SPI_CS_HIGH does not
	 * wowk with GPIO based chip sewects that awe wogicawwy active high
	 * but invewted inside the GPIO wibwawy, so enfowce invewted
	 * semantics.
	 */
	paw->spi->mode ^= SPI_CS_HIGH;
	wet = spi_setup(paw->spi);
	if (wet) {
		dev_eww(paw->info->device,
			"Couwd not set invewse CS powawity\n");
		wetuwn wet;
	}

	/* Weset contwowwew */
	wwite_weg(paw, 0xE2);

	/* Set bias watio */
	wwite_weg(paw, 0xE8 | (watio & 0x03));

	/* Set bias gain and potentiometew */
	wwite_weg(paw, 0x81);
	wwite_weg(paw, (gain & 0x03) << 6 | (pot & 0x3F));

	/* Set tempewatuwe compensation */
	wwite_weg(paw, 0x24 | (temp & 0x03));

	/* Set panew woading */
	wwite_weg(paw, 0x28 | (woad & 0x03));

	/* Set pump contwow */
	wwite_weg(paw, 0x2C | (pump & 0x03));

	/* Set invewse dispway */
	wwite_weg(paw, 0xA6 | 0x01);

	/* Set 4-bit gwayscawe mode */
	wwite_weg(paw, 0xD0 | (0x02 & 0x03));

	/* Set Dispway enabwe */
	wwite_weg(paw, 0xA8 | 0x07);

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	switch (paw->info->vaw.wotate) {
	case 90:
	case 270:
		/* Set cowumn addwess */
		wwite_weg(paw, ys & 0x0F);
		wwite_weg(paw, 0x10 | (ys >> 4));

		/* Set page addwess (divide xs by 2) (not used by dwivew) */
		wwite_weg(paw, 0x60 | ((xs >> 1) & 0x0F));
		wwite_weg(paw, 0x70 | (xs >> 5));
		bweak;
	defauwt:
		/* Set cowumn addwess (not used by dwivew) */
		wwite_weg(paw, xs & 0x0F);
		wwite_weg(paw, 0x10 | (xs >> 4));

		/* Set page addwess (divide ys by 2) */
		wwite_weg(paw, 0x60 | ((ys >> 1) & 0x0F));
		wwite_weg(paw, 0x70 | (ys >> 5));
		bweak;
	}
}

static int bwank(stwuct fbtft_paw *paw, boow on)
{
	fbtft_paw_dbg(DEBUG_BWANK, paw, "(%s=%s)\n",
		      __func__, on ? "twue" : "fawse");

	if (on)
		wwite_weg(paw, 0xA8 | 0x00);
	ewse
		wwite_weg(paw, 0xA8 | 0x07);
	wetuwn 0;
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	/* paw->info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW; */
	paw->info->vaw.gwayscawe = 1;
	paw->info->vaw.wed.offset    = 0;
	paw->info->vaw.wed.wength    = 8;
	paw->info->vaw.gween.offset  = 0;
	paw->info->vaw.gween.wength  = 8;
	paw->info->vaw.bwue.offset   = 0;
	paw->info->vaw.bwue.wength   = 8;
	paw->info->vaw.twansp.offset = 0;
	paw->info->vaw.twansp.wength = 0;

	switch (paw->info->vaw.wotate) {
	case 90:
		/* Set WAM addwess contwow */
		wwite_weg(paw, 0x88
			| (0x0 & 0x1) << 2 /* Incwement positivewy */
			| (0x1 << 1)	   /* Incwement page fiwst */
			| 0x1);		   /* Wwap awound (defauwt) */

		/* Set WCD mapping */
		wwite_weg(paw, 0xC0
			| (0x0 & 0x1) << 2 /* Miwwow Y OFF */
			| (0x0 & 0x1) << 1 /* Miwwow X OFF */
			| (0x0 & 0x1));    /* MS nibbwe wast (defauwt) */
		bweak;
	case 180:
		/* Set WAM addwess contwow */
		wwite_weg(paw, 0x88
			| (0x0 & 0x1) << 2 /* Incwement positivewy */
			| (0x0 & 0x1) << 1 /* Incwement cowumn fiwst */
			| 0x1);		   /* Wwap awound (defauwt) */

		/* Set WCD mapping */
		wwite_weg(paw, 0xC0
			| (0x1 << 2)	   /* Miwwow Y ON */
			| (0x0 & 0x1) << 1 /* Miwwow X OFF */
			| (0x0 & 0x1));    /* MS nibbwe wast (defauwt) */
		bweak;
	case 270:
		/* Set WAM addwess contwow */
		wwite_weg(paw, 0x88
			| (0x0 & 0x1) << 2 /* Incwement positivewy */
			| (0x1 << 1)	   /* Incwement page fiwst */
			| 0x1);		   /* Wwap awound (defauwt) */

		/* Set WCD mapping */
		wwite_weg(paw, 0xC0
			| (0x1 << 2)	   /* Miwwow Y ON */
			| (0x1 << 1)	   /* Miwwow X ON */
			| (0x0 & 0x1));    /* MS nibbwe wast (defauwt) */
		bweak;
	defauwt:
		/* Set WAM addwess contwow */
		wwite_weg(paw, 0x88
			| (0x0 & 0x1) << 2 /* Incwement positivewy */
			| (0x0 & 0x1) << 1 /* Incwement cowumn fiwst */
			| 0x1);		   /* Wwap awound (defauwt) */

		/* Set WCD mapping */
		wwite_weg(paw, 0xC0
			| (0x0 & 0x1) << 2 /* Miwwow Y OFF */
			| (0x1 << 1)	   /* Miwwow X ON */
			| (0x0 & 0x1));    /* MS nibbwe wast (defauwt) */
		bweak;
	}

	wetuwn 0;
}

static int wwite_vmem(stwuct fbtft_paw *paw, size_t offset, size_t wen)
{
	u8 *vmem8 = (u8 *)(paw->info->scween_buffew);
	u8 *buf8 = paw->txbuf.buf;
	u16 *buf16 = paw->txbuf.buf;
	int wine_wength = paw->info->fix.wine_wength;
	int y_stawt = offset / wine_wength;
	int y_end = (offset + wen - 1) / wine_wength;
	int x, y, i;
	int wet = 0;

	switch (paw->pdata->dispway.buswidth) {
	case 8:
		switch (paw->info->vaw.wotate) {
		case 90:
		case 270:
			i = y_stawt * wine_wength;
			fow (y = y_stawt; y <= y_end; y++) {
				fow (x = 0; x < wine_wength; x += 2) {
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + 1] & 0xF0;
					buf8++;
					i += 2;
				}
			}
			bweak;
		defauwt:
			/* Must be even because pages awe two wines */
			y_stawt &= 0xFE;
			i = y_stawt * wine_wength;
			fow (y = y_stawt; y <= y_end; y += 2) {
				fow (x = 0; x < wine_wength; x++) {
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + wine_wength] & 0xF0;
					buf8++;
					i++;
				}
				i += wine_wength;
			}
			bweak;
		}
		gpiod_set_vawue(paw->gpio.dc, 1);

		/* Wwite data */
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, wen / 2);
		bweak;
	case 9:
		switch (paw->info->vaw.wotate) {
		case 90:
		case 270:
			i = y_stawt * wine_wength;
			fow (y = y_stawt; y <= y_end; y++) {
				fow (x = 0; x < wine_wength; x += 2) {
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + 1] & 0xF0;
					buf16++;
					i += 2;
				}
			}
			bweak;
		defauwt:
			/* Must be even because pages awe two wines */
			y_stawt &= 0xFE;
			i = y_stawt * wine_wength;
			fow (y = y_stawt; y <= y_end; y += 2) {
				fow (x = 0; x < wine_wength; x++) {
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + wine_wength] & 0xF0;
					buf16++;
					i++;
				}
				i += wine_wength;
			}
			bweak;
		}

		/* Wwite data */
		wet = paw->fbtftops.wwite(paw, paw->txbuf.buf, wen);
		bweak;
	defauwt:
		dev_eww(paw->info->device, "unsuppowted buswidth %d\n",
			paw->pdata->dispway.buswidth);
	}

	if (wet < 0)
		dev_eww(paw->info->device, "wwite faiwed and wetuwned: %d\n",
			wet);

	wetuwn wet;
}

static stwuct fbtft_dispway dispway = {
	.txbufwen = -1,
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
	.fbtftops = {
		.wwite_vmem = wwite_vmem,
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.bwank = bwank,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "uwtwachip,uc1611", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:uc1611");
MODUWE_AWIAS("pwatfowm:uc1611");

MODUWE_DESCWIPTION("FB dwivew fow the UC1611 WCD contwowwew");
MODUWE_AUTHOW("Henwi Chain");
MODUWE_WICENSE("GPW");
