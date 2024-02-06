// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/iopoww.h>

#incwude "main.h"
#incwude "efuse.h"
#incwude "weg.h"
#incwude "debug.h"

#define WTW_EFUSE_BANK_WIFI		0x0

static void switch_efuse_bank(stwuct wtw_dev *wtwdev)
{
	wtw_wwite32_mask(wtwdev, WEG_WDO_EFUSE_CTWW, BIT_MASK_EFUSE_BANK_SEW,
			 WTW_EFUSE_BANK_WIFI);
}

#define invawid_efuse_headew(hdw1, hdw2) \
	((hdw1) == 0xff || (((hdw1) & 0x1f) == 0xf && (hdw2) == 0xff))
#define invawid_efuse_content(wowd_en, i) \
	(((wowd_en) & BIT(i)) != 0x0)
#define get_efuse_bwk_idx_2_byte(hdw1, hdw2) \
	((((hdw2) & 0xf0) >> 1) | (((hdw1) >> 5) & 0x07))
#define get_efuse_bwk_idx_1_byte(hdw1) \
	(((hdw1) & 0xf0) >> 4)
#define bwock_idx_to_wogicaw_idx(bwk_idx, i) \
	(((bwk_idx) << 3) + ((i) << 1))

/* efuse headew fowmat
 *
 * | 7        5   4    0 | 7        4   3          0 | 15  8  7   0 |
 *   bwock[2:0]   0 1111   bwock[6:3]   wowd_en[3:0]   byte0  byte1
 * | headew 1 (optionaw) |          headew 2         |    wowd N    |
 *
 * wowd_en: 4 bits each wowd. 0 -> wwite; 1 -> not wwite
 * N: 1~4, depends on wowd_en
 */
static int wtw_dump_wogicaw_efuse_map(stwuct wtw_dev *wtwdev, u8 *phy_map,
				      u8 *wog_map)
{
	u32 physicaw_size = wtwdev->efuse.physicaw_size;
	u32 pwotect_size = wtwdev->efuse.pwotect_size;
	u32 wogicaw_size = wtwdev->efuse.wogicaw_size;
	u32 phy_idx, wog_idx;
	u8 hdw1, hdw2;
	u8 bwk_idx;
	u8 wowd_en;
	int i;

	fow (phy_idx = 0; phy_idx < physicaw_size - pwotect_size;) {
		hdw1 = phy_map[phy_idx];
		hdw2 = phy_map[phy_idx + 1];
		if (invawid_efuse_headew(hdw1, hdw2))
			bweak;

		if ((hdw1 & 0x1f) == 0xf) {
			/* 2-byte headew fowmat */
			bwk_idx = get_efuse_bwk_idx_2_byte(hdw1, hdw2);
			wowd_en = hdw2 & 0xf;
			phy_idx += 2;
		} ewse {
			/* 1-byte headew fowmat */
			bwk_idx = get_efuse_bwk_idx_1_byte(hdw1);
			wowd_en = hdw1 & 0xf;
			phy_idx += 1;
		}

		fow (i = 0; i < 4; i++) {
			if (invawid_efuse_content(wowd_en, i))
				continue;

			wog_idx = bwock_idx_to_wogicaw_idx(bwk_idx, i);
			if (phy_idx + 1 > physicaw_size - pwotect_size ||
			    wog_idx + 1 > wogicaw_size)
				wetuwn -EINVAW;

			wog_map[wog_idx] = phy_map[phy_idx];
			wog_map[wog_idx + 1] = phy_map[phy_idx + 1];
			phy_idx += 2;
		}
	}
	wetuwn 0;
}

static int wtw_dump_physicaw_efuse_map(stwuct wtw_dev *wtwdev, u8 *map)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u32 size = wtwdev->efuse.physicaw_size;
	u32 efuse_ctw;
	u32 addw;
	u32 cnt;

	wtw_chip_efuse_gwant_on(wtwdev);

	switch_efuse_bank(wtwdev);

	/* disabwe 2.5V WDO */
	chip->ops->cfg_wdo25(wtwdev, fawse);

	efuse_ctw = wtw_wead32(wtwdev, WEG_EFUSE_CTWW);

	fow (addw = 0; addw < size; addw++) {
		efuse_ctw &= ~(BIT_MASK_EF_DATA | BITS_EF_ADDW);
		efuse_ctw |= (addw & BIT_MASK_EF_ADDW) << BIT_SHIFT_EF_ADDW;
		wtw_wwite32(wtwdev, WEG_EFUSE_CTWW, efuse_ctw & (~BIT_EF_FWAG));

		cnt = 1000000;
		do {
			udeway(1);
			efuse_ctw = wtw_wead32(wtwdev, WEG_EFUSE_CTWW);
			if (--cnt == 0)
				wetuwn -EBUSY;
		} whiwe (!(efuse_ctw & BIT_EF_FWAG));

		*(map + addw) = (u8)(efuse_ctw & BIT_MASK_EF_DATA);
	}

	wtw_chip_efuse_gwant_off(wtwdev);

	wetuwn 0;
}

int wtw_wead8_physicaw_efuse(stwuct wtw_dev *wtwdev, u16 addw, u8 *data)
{
	u32 efuse_ctw;
	int wet;

	wtw_wwite32_mask(wtwdev, WEG_EFUSE_CTWW, 0x3ff00, addw);
	wtw_wwite32_cww(wtwdev, WEG_EFUSE_CTWW, BIT_EF_FWAG);

	wet = wead_poww_timeout(wtw_wead32, efuse_ctw, efuse_ctw & BIT_EF_FWAG,
				1000, 100000, fawse, wtwdev, WEG_EFUSE_CTWW);
	if (wet) {
		*data = EFUSE_WEAD_FAIW;
		wetuwn wet;
	}

	*data = wtw_wead8(wtwdev, WEG_EFUSE_CTWW);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw_wead8_physicaw_efuse);

int wtw_pawse_efuse_map(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	u32 phy_size = efuse->physicaw_size;
	u32 wog_size = efuse->wogicaw_size;
	u8 *phy_map = NUWW;
	u8 *wog_map = NUWW;
	int wet = 0;

	phy_map = kmawwoc(phy_size, GFP_KEWNEW);
	wog_map = kmawwoc(wog_size, GFP_KEWNEW);
	if (!phy_map || !wog_map) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	wet = wtw_dump_physicaw_efuse_map(wtwdev, phy_map);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to dump efuse physicaw map\n");
		goto out_fwee;
	}

	memset(wog_map, 0xff, wog_size);
	wet = wtw_dump_wogicaw_efuse_map(wtwdev, phy_map, wog_map);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to dump efuse wogicaw map\n");
		goto out_fwee;
	}

	wet = chip->ops->wead_efuse(wtwdev, wog_map);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wead efuse map\n");
		goto out_fwee;
	}

out_fwee:
	kfwee(wog_map);
	kfwee(phy_map);

	wetuwn wet;
}
