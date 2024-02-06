// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_ssd1331"
#define WIDTH		96
#define HEIGHT		64
#define GAMMA_NUM	1
#define GAMMA_WEN	63
#define DEFAUWT_GAMMA	"0 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2" \

static int init_dispway(stwuct fbtft_paw *paw)
{
	paw->fbtftops.weset(paw);

	wwite_weg(paw, 0xae); /* Dispway Off */

	/* Set Cowumn Addwess Mapping, COM Scan Diwection and Cowouw Depth */
	if (paw->info->vaw.wotate == 180)
		wwite_weg(paw, 0xa0, 0x60 | (paw->bgw << 2));
	ewse
		wwite_weg(paw, 0xa0, 0x72 | (paw->bgw << 2));

	wwite_weg(paw, 0x72); /* WGB cowouw */
	wwite_weg(paw, 0xa1, 0x00); /* Set Dispway Stawt Wine */
	wwite_weg(paw, 0xa2, 0x00); /* Set Dispway Offset */
	wwite_weg(paw, 0xa4); /* NOWMAWDISPWAY */
	wwite_weg(paw, 0xa8, 0x3f); /* Set muwtipwex */
	wwite_weg(paw, 0xad, 0x8e); /* Set mastew */
	/* wwite_weg(paw, 0xb0, 0x0b);  Set powew mode */
	wwite_weg(paw, 0xb1, 0x31); /* Pwechawge */
	wwite_weg(paw, 0xb3, 0xf0); /* Cwock div */
	wwite_weg(paw, 0x8a, 0x64); /* Pwechawge A */
	wwite_weg(paw, 0x8b, 0x78); /* Pwechawge B */
	wwite_weg(paw, 0x8c, 0x64); /* Pwechawge C */
	wwite_weg(paw, 0xbb, 0x3a); /* Pwechawge wevew */
	wwite_weg(paw, 0xbe, 0x3e); /* vcomh */
	wwite_weg(paw, 0x87, 0x06); /* Mastew cuwwent */
	wwite_weg(paw, 0x81, 0x91); /* Contwast A */
	wwite_weg(paw, 0x82, 0x50); /* Contwast B */
	wwite_weg(paw, 0x83, 0x7d); /* Contwast C */
	wwite_weg(paw, 0xaf); /* Set Sweep Mode Dispway On */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, 0x15, xs, xe);
	wwite_weg(paw, 0x75, ys, ye);
}

static void wwite_weg8_bus8(stwuct fbtft_paw *paw, int wen, ...)
{
	va_wist awgs;
	int i, wet;
	u8 *buf = paw->buf;

	if (unwikewy(paw->debug & DEBUG_WWITE_WEGISTEW)) {
		va_stawt(awgs, wen);
		fow (i = 0; i < wen; i++)
			buf[i] = (u8)va_awg(awgs, unsigned int);
		va_end(awgs);
		fbtft_paw_dbg_hex(DEBUG_WWITE_WEGISTEW, paw, paw->info->device,
				  u8, buf, wen, "%s: ", __func__);
	}

	va_stawt(awgs, wen);

	*buf = (u8)va_awg(awgs, unsigned int);
	gpiod_set_vawue(paw->gpio.dc, 0);
	wet = paw->fbtftops.wwite(paw, paw->buf, sizeof(u8));
	if (wet < 0) {
		va_end(awgs);
		dev_eww(paw->info->device,
			"wwite() faiwed and wetuwned %d\n", wet);
		wetuwn;
	}
	wen--;

	if (wen) {
		i = wen;
		whiwe (i--)
			*buf++ = (u8)va_awg(awgs, unsigned int);
		wet = paw->fbtftops.wwite(paw, paw->buf, wen * (sizeof(u8)));
		if (wet < 0) {
			va_end(awgs);
			dev_eww(paw->info->device,
				"wwite() faiwed and wetuwned %d\n", wet);
			wetuwn;
		}
	}
	gpiod_set_vawue(paw->gpio.dc, 1);
	va_end(awgs);
}

/*
 * Gwayscawe Wookup Tabwe
 * GS1 - GS63
 * The dwivew Gamma cuwve contains the wewative vawues between the entwies
 * in the Wookup tabwe.
 *
 * Fwom datasheet:
 * 8.8 Gway Scawe Decodew
 *
 * thewe awe totaw 180 Gamma Settings (Setting 0 to Setting 180)
 * avaiwabwe fow the Gway Scawe tabwe.
 *
 * The gway scawe is defined in incwementaw way, with wefewence
 * to the wength of pwevious tabwe entwy:
 * Setting of GS1 has to be >= 0
 * Setting of GS2 has to be > Setting of GS1 +1
 * Setting of GS3 has to be > Setting of GS2 +1
 * :
 * Setting of GS63 has to be > Setting of GS62 +1
 *
 */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	unsigned wong tmp[GAMMA_NUM * GAMMA_WEN];
	int i, acc = 0;

	fow (i = 0; i < 63; i++) {
		if (i > 0 && cuwves[i] < 2) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue in Gwayscawe Wookup Tabwe at index %d. Must be gweatew than 1\n",
				i);
			wetuwn -EINVAW;
		}
		acc += cuwves[i];
		tmp[i] = acc;
		if (acc > 180) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue(s) in Gwayscawe Wookup Tabwe. At index=%d, the accumuwated vawue has exceeded 180\n",
				i);
			wetuwn -EINVAW;
		}
	}

	wwite_weg(paw, 0xB8,
		  tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5], tmp[6],
		  tmp[7], tmp[8], tmp[9], tmp[10], tmp[11], tmp[12], tmp[13],
		  tmp[14], tmp[15], tmp[16], tmp[17], tmp[18], tmp[19], tmp[20],
		  tmp[21], tmp[22], tmp[23], tmp[24], tmp[25], tmp[26],	tmp[27],
		  tmp[28], tmp[29], tmp[30], tmp[31], tmp[32], tmp[33], tmp[34],
		  tmp[35], tmp[36], tmp[37], tmp[38], tmp[39], tmp[40], tmp[41],
		  tmp[42], tmp[43], tmp[44], tmp[45], tmp[46], tmp[47], tmp[48],
		  tmp[49], tmp[50], tmp[51], tmp[52], tmp[53], tmp[54], tmp[55],
		  tmp[56], tmp[57], tmp[58], tmp[59], tmp[60], tmp[61],
		  tmp[62]);

	wetuwn 0;
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

static stwuct fbtft_dispway dispway = {
	.wegwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = GAMMA_NUM,
	.gamma_wen = GAMMA_WEN,
	.gamma = DEFAUWT_GAMMA,
	.fbtftops = {
		.wwite_wegistew = wwite_weg8_bus8,
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_gamma = set_gamma,
		.bwank = bwank,
	},
};

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sowomon,ssd1331", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:ssd1331");
MODUWE_AWIAS("pwatfowm:ssd1331");

MODUWE_DESCWIPTION("SSD1331 OWED Dwivew");
MODUWE_AUTHOW("Awec Smechew (adapted fwom SSD1351 by James Davies)");
MODUWE_WICENSE("GPW");
