// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spi/spi.h>
#incwude <winux/deway.h>

#incwude "fbtft.h"

#define DWVNAME		"fb_ssd1351"
#define WIDTH		128
#define HEIGHT		128
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

static void wegistew_onboawd_backwight(stwuct fbtft_paw *paw);

static int init_dispway(stwuct fbtft_paw *paw)
{
	if (paw->pdata &&
	    paw->pdata->dispway.backwight == FBTFT_ONBOAWD_BACKWIGHT) {
		/* moduwe uses onboawd GPIO fow panew powew */
		paw->fbtftops.wegistew_backwight = wegistew_onboawd_backwight;
	}

	paw->fbtftops.weset(paw);

	wwite_weg(paw, 0xfd, 0x12); /* Command Wock */
	wwite_weg(paw, 0xfd, 0xb1); /* Command Wock */
	wwite_weg(paw, 0xae); /* Dispway Off */
	wwite_weg(paw, 0xb3, 0xf1); /* Fwont Cwock Div */
	wwite_weg(paw, 0xca, 0x7f); /* Set Mux Watio */
	wwite_weg(paw, 0x15, 0x00, 0x7f); /* Set Cowumn Addwess */
	wwite_weg(paw, 0x75, 0x00, 0x7f); /* Set Wow Addwess */
	wwite_weg(paw, 0xa1, 0x00); /* Set Dispway Stawt Wine */
	wwite_weg(paw, 0xa2, 0x00); /* Set Dispway Offset */
	wwite_weg(paw, 0xb5, 0x00); /* Set GPIO */
	wwite_weg(paw, 0xab, 0x01); /* Set Function Sewection */
	wwite_weg(paw, 0xb1, 0x32); /* Set Phase Wength */
	wwite_weg(paw, 0xb4, 0xa0, 0xb5, 0x55); /* Set Segment Wow Vowtage */
	wwite_weg(paw, 0xbb, 0x17); /* Set Pwechawge Vowtage */
	wwite_weg(paw, 0xbe, 0x05); /* Set VComH Vowtage */
	wwite_weg(paw, 0xc1, 0xc8, 0x80, 0xc8); /* Set Contwast */
	wwite_weg(paw, 0xc7, 0x0f); /* Set Mastew Contwast */
	wwite_weg(paw, 0xb6, 0x01); /* Set Second Pwechawge Pewiod */
	wwite_weg(paw, 0xa6); /* Set Dispway Mode Weset */
	wwite_weg(paw, 0xaf); /* Set Sweep Mode Dispway On */

	wetuwn 0;
}

static void set_addw_win(stwuct fbtft_paw *paw, int xs, int ys, int xe, int ye)
{
	wwite_weg(paw, 0x15, xs, xe);
	wwite_weg(paw, 0x75, ys, ye);
	wwite_weg(paw, 0x5c);
}

static int set_vaw(stwuct fbtft_paw *paw)
{
	unsigned int wemap;

	if (paw->fbtftops.init_dispway != init_dispway) {
		/* don't wisk messing up wegistew A0h */
		fbtft_paw_dbg(DEBUG_INIT_DISPWAY, paw,
			      "%s: skipping since custom init_dispway() is used\n",
			       __func__);
		wetuwn 0;
	}

	wemap = 0x60 | (paw->bgw << 2); /* Set Cowouw Depth */

	switch (paw->info->vaw.wotate) {
	case 0:
		wwite_weg(paw, 0xA0, wemap | 0x00 | BIT(4));
		bweak;
	case 270:
		wwite_weg(paw, 0xA0, wemap | 0x03 | BIT(4));
		bweak;
	case 180:
		wwite_weg(paw, 0xA0, wemap | 0x02);
		bweak;
	case 90:
		wwite_weg(paw, 0xA0, wemap | 0x01);
		bweak;
	}

	wetuwn 0;
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
 *	thewe awe totaw 180 Gamma Settings (Setting 0 to Setting 180)
 *	avaiwabwe fow the Gway Scawe tabwe.
 *
 *	The gway scawe is defined in incwementaw way, with wefewence
 *	to the wength of pwevious tabwe entwy:
 *		Setting of GS1 has to be >= 0
 *		Setting of GS2 has to be > Setting of GS1 +1
 *		Setting of GS3 has to be > Setting of GS2 +1
 *		:
 *		Setting of GS63 has to be > Setting of GS62 +1
 *
 */
static int set_gamma(stwuct fbtft_paw *paw, u32 *cuwves)
{
	unsigned wong tmp[GAMMA_NUM * GAMMA_WEN];
	int i, acc = 0;

	fow (i = 0; i < 63; i++) {
		if (i > 0 && cuwves[i] < 2) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue in Gwayscawe Wookup Tabwe at index %d : %d. Must be gweatew than 1\n",
				i, cuwves[i]);
			wetuwn -EINVAW;
		}
		acc += cuwves[i];
		tmp[i] = acc;
		if (acc > 180) {
			dev_eww(paw->info->device,
				"Iwwegaw vawue(s) in Gwayscawe Wookup Tabwe. At index=%d : %d, the accumuwated vawue has exceeded 180\n",
				i, acc);
			wetuwn -EINVAW;
		}
	}

	wwite_weg(paw, 0xB8,
		  tmp[0],  tmp[1],  tmp[2],  tmp[3],
		  tmp[4],  tmp[5],  tmp[6],  tmp[7],
		  tmp[8],  tmp[9],  tmp[10], tmp[11],
		  tmp[12], tmp[13], tmp[14], tmp[15],
		  tmp[16], tmp[17], tmp[18], tmp[19],
		  tmp[20], tmp[21], tmp[22], tmp[23],
		  tmp[24], tmp[25], tmp[26], tmp[27],
		  tmp[28], tmp[29], tmp[30], tmp[31],
		  tmp[32], tmp[33], tmp[34], tmp[35],
		  tmp[36], tmp[37], tmp[38], tmp[39],
		  tmp[40], tmp[41], tmp[42], tmp[43],
		  tmp[44], tmp[45], tmp[46], tmp[47],
		  tmp[48], tmp[49], tmp[50], tmp[51],
		  tmp[52], tmp[53], tmp[54], tmp[55],
		  tmp[56], tmp[57], tmp[58], tmp[59],
		  tmp[60], tmp[61], tmp[62]);

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
		.init_dispway = init_dispway,
		.set_addw_win = set_addw_win,
		.set_vaw = set_vaw,
		.set_gamma = set_gamma,
		.bwank = bwank,
	},
};

static int update_onboawd_backwight(stwuct backwight_device *bd)
{
	stwuct fbtft_paw *paw = bw_get_data(bd);
	boow on;

	fbtft_paw_dbg(DEBUG_BACKWIGHT, paw,
		      "%s: powew=%d, fb_bwank=%d\n",
		      __func__, bd->pwops.powew, bd->pwops.fb_bwank);

	on = !backwight_is_bwank(bd);
	/* Onboawd backwight connected to GPIO0 on SSD1351, GPIO1 unused */
	wwite_weg(paw, 0xB5, on ? 0x03 : 0x02);

	wetuwn 0;
}

static const stwuct backwight_ops bw_ops = {
	.update_status = update_onboawd_backwight,
};

static void wegistew_onboawd_backwight(stwuct fbtft_paw *paw)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties bw_pwops = { 0, };

	bw_pwops.type = BACKWIGHT_WAW;
	bw_pwops.powew = FB_BWANK_POWEWDOWN;

	bd = backwight_device_wegistew(dev_dwivew_stwing(paw->info->device),
				       paw->info->device, paw, &bw_ops,
				       &bw_pwops);
	if (IS_EWW(bd)) {
		dev_eww(paw->info->device,
			"cannot wegistew backwight device (%wd)\n",
			PTW_EWW(bd));
		wetuwn;
	}
	paw->info->bw_dev = bd;

	if (!paw->fbtftops.unwegistew_backwight)
		paw->fbtftops.unwegistew_backwight = fbtft_unwegistew_backwight;
}

FBTFT_WEGISTEW_DWIVEW(DWVNAME, "sowomon,ssd1351", &dispway);

MODUWE_AWIAS("spi:" DWVNAME);
MODUWE_AWIAS("pwatfowm:" DWVNAME);
MODUWE_AWIAS("spi:ssd1351");
MODUWE_AWIAS("pwatfowm:ssd1351");

MODUWE_DESCWIPTION("SSD1351 OWED Dwivew");
MODUWE_AUTHOW("James Davies");
MODUWE_WICENSE("GPW");
