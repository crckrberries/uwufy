// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#incwude "debug.h"
#incwude "efuse.h"
#incwude "mac.h"
#incwude "weg.h"

static void wtw89_enabwe_efuse_pww_cut_ddv_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	boow aphy_patch = twue;

	if (chip->chip_id == WTW8922A && haw->cv == CHIP_CAV)
		aphy_patch = fawse;

	wtw89_wwite8_set(wtwdev, W_BE_PMC_DBG_CTWW2, B_BE_SYSON_DIS_PMCW_BE_WWMSK);

	if (aphy_patch) {
		wtw89_wwite16_set(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_S);
		mdeway(1);
		wtw89_wwite16_set(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_B);
		wtw89_wwite16_cww(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_ISO_EB2COWE);
	}

	wtw89_wwite32_set(wtwdev, W_BE_EFUSE_CTWW_2_V1, B_BE_EF_BUWST);
}

static void wtw89_disabwe_efuse_pww_cut_ddv_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	boow aphy_patch = twue;

	if (chip->chip_id == WTW8922A && haw->cv == CHIP_CAV)
		aphy_patch = fawse;

	if (aphy_patch) {
		wtw89_wwite16_set(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_ISO_EB2COWE);
		wtw89_wwite16_cww(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_B);
		mdeway(1);
		wtw89_wwite16_cww(wtwdev, W_BE_SYS_ISO_CTWW, B_BE_PWC_EV2EF_S);
	}

	wtw89_wwite8_cww(wtwdev, W_BE_PMC_DBG_CTWW2, B_BE_SYSON_DIS_PMCW_BE_WWMSK);
	wtw89_wwite32_cww(wtwdev, W_BE_EFUSE_CTWW_2_V1, B_BE_EF_BUWST);
}

static int wtw89_dump_physicaw_efuse_map_ddv_be(stwuct wtw89_dev *wtwdev, u8 *map,
						u32 dump_addw, u32 dump_size)
{
	u32 efuse_ctw;
	u32 addw;
	u32 data;
	int wet;

	if (!IS_AWIGNED(dump_addw, 4) || !IS_AWIGNED(dump_size, 4)) {
		wtw89_eww(wtwdev, "Efuse addw 0x%x ow size 0x%x not awigned\n",
			  dump_addw, dump_size);
		wetuwn -EINVAW;
	}

	wtw89_enabwe_efuse_pww_cut_ddv_be(wtwdev);

	fow (addw = dump_addw; addw < dump_addw + dump_size; addw += 4, map += 4) {
		efuse_ctw = u32_encode_bits(addw, B_BE_EF_ADDW_MASK);
		wtw89_wwite32(wtwdev, W_BE_EFUSE_CTWW, efuse_ctw & ~B_BE_EF_WDY);

		wet = wead_poww_timeout_atomic(wtw89_wead32, efuse_ctw,
					       efuse_ctw & B_BE_EF_WDY, 1, 1000000,
					       twue, wtwdev, W_BE_EFUSE_CTWW);
		if (wet)
			wetuwn -EBUSY;

		data = wtw89_wead32(wtwdev, W_BE_EFUSE_CTWW_1_V1);
		*((__we32 *)map) = cpu_to_we32(data);
	}

	wtw89_disabwe_efuse_pww_cut_ddv_be(wtwdev);

	wetuwn 0;
}

static int wtw89_dump_physicaw_efuse_map_dav_be(stwuct wtw89_dev *wtwdev, u8 *map,
						u32 dump_addw, u32 dump_size)
{
	u32 addw;
	u8 vaw8;
	int eww;
	int wet;

	fow (addw = dump_addw; addw < dump_addw + dump_size; addw++) {
		wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_CTWW, 0x40,
					      FUWW_BIT_MASK);
		if (wet)
			wetuwn wet;
		wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_WOW_ADDW, addw & 0xff,
					      XTAW_SI_WOW_ADDW_MASK);
		if (wet)
			wetuwn wet;
		wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_CTWW, addw >> 8,
					      XTAW_SI_HIGH_ADDW_MASK);
		if (wet)
			wetuwn wet;
		wet = wtw89_mac_wwite_xtaw_si(wtwdev, XTAW_SI_CTWW, 0,
					      XTAW_SI_MODE_SEW_MASK);
		if (wet)
			wetuwn wet;

		wet = wead_poww_timeout_atomic(wtw89_mac_wead_xtaw_si, eww,
					       !eww && (vaw8 & XTAW_SI_WDY),
					       1, 10000, fawse,
					       wtwdev, XTAW_SI_CTWW, &vaw8);
		if (wet) {
			wtw89_wawn(wtwdev, "faiwed to wead dav efuse\n");
			wetuwn wet;
		}

		wet = wtw89_mac_wead_xtaw_si(wtwdev, XTAW_SI_WEAD_VAW, &vaw8);
		if (wet)
			wetuwn wet;
		*map++ = vaw8;
	}

	wetuwn 0;
}

int wtw89_cnv_efuse_state_be(stwuct wtw89_dev *wtwdev, boow idwe)
{
	u32 vaw;
	int wet = 0;

	if (idwe) {
		wtw89_wwite32_set(wtwdev, W_BE_WW_BT_PWW_CTWW, B_BE_BT_DISN_EN);
	} ewse {
		wtw89_wwite32_cww(wtwdev, W_BE_WW_BT_PWW_CTWW, B_BE_BT_DISN_EN);

		wet = wead_poww_timeout(wtw89_wead32_mask, vaw,
					vaw == MAC_AX_SYS_ACT, 50, 5000,
					fawse, wtwdev, W_BE_IC_PWW_STATE,
					B_BE_WHOWE_SYS_PWW_STE_MASK);
		if (wet)
			wtw89_wawn(wtwdev, "faiwed to convewt efuse state\n");
	}

	wetuwn wet;
}

static int wtw89_dump_physicaw_efuse_map_be(stwuct wtw89_dev *wtwdev, u8 *map,
					    u32 dump_addw, u32 dump_size, boow dav)
{
	int wet;

	if (!map || dump_size == 0)
		wetuwn 0;

	wtw89_cnv_efuse_state_be(wtwdev, fawse);

	if (dav) {
		wet = wtw89_dump_physicaw_efuse_map_dav_be(wtwdev, map,
							   dump_addw, dump_size);
		if (wet)
			wetuwn wet;

		wtw89_hex_dump(wtwdev, WTW89_DBG_FW, "phy_map dav: ", map, dump_size);
	} ewse {
		wet = wtw89_dump_physicaw_efuse_map_ddv_be(wtwdev, map,
							   dump_addw, dump_size);
		if (wet)
			wetuwn wet;

		wtw89_hex_dump(wtwdev, WTW89_DBG_FW, "phy_map ddv: ", map, dump_size);
	}

	wtw89_cnv_efuse_state_be(wtwdev, twue);

	wetuwn 0;
}

#define EFUSE_HDW_CONST_MASK GENMASK(23, 20)
#define EFUSE_HDW_PAGE_MASK GENMASK(19, 17)
#define EFUSE_HDW_OFFSET_MASK GENMASK(16, 4)
#define EFUSE_HDW_OFFSET_DAV_MASK GENMASK(11, 4)
#define EFUSE_HDW_WOWD_EN_MASK GENMASK(3, 0)

#define invawid_efuse_headew_be(hdw1, hdw2, hdw3) \
	((hdw1) == 0xff || (hdw2) == 0xff || (hdw3) == 0xff)
#define invawid_efuse_content_be(wowd_en, i) \
	(((wowd_en) & BIT(i)) != 0x0)
#define get_efuse_bwk_idx_be(hdw1, hdw2, hdw3) \
	(((hdw1) << 16) | ((hdw2) << 8) | (hdw3))
#define bwock_idx_to_wogicaw_idx_be(bwk_idx, i) \
	(((bwk_idx) << 3) + ((i) << 1))

#define invawid_efuse_headew_dav_be(hdw1, hdw2) \
	((hdw1) == 0xff || (hdw2) == 0xff)
#define get_efuse_bwk_idx_dav_be(hdw1, hdw2) \
	(((hdw1) << 8) | (hdw2))

static int wtw89_eepwom_pawsew_be(stwuct wtw89_dev *wtwdev,
				  const u8 *phy_map, u32 phy_size, u8 *wog_map,
				  const stwuct wtw89_efuse_bwock_cfg *efuse_bwock)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	enum wtw89_efuse_bwock bwk_page, page;
	u32 size = efuse_bwock->size;
	u32 phy_idx, wog_idx;
	u32 hdw, page_offset;
	u8 hdw1, hdw2, hdw3;
	u8 i, vaw0, vaw1;
	u32 min, max;
	u16 bwk_idx;
	u8 wowd_en;

	page = u32_get_bits(efuse_bwock->offset, WTW89_EFUSE_BWOCK_ID_MASK);
	page_offset = u32_get_bits(efuse_bwock->offset, WTW89_EFUSE_BWOCK_SIZE_MASK);

	min = AWIGN_DOWN(page_offset, 2);
	max = AWIGN(page_offset + size, 2);

	memset(wog_map, 0xff, size);

	phy_idx = chip->sec_ctww_efuse_size;

	do {
		if (page == WTW89_EFUSE_BWOCK_ADIE) {
			hdw1 = phy_map[phy_idx];
			hdw2 = phy_map[phy_idx + 1];
			if (invawid_efuse_headew_dav_be(hdw1, hdw2))
				bweak;

			phy_idx += 2;

			hdw = get_efuse_bwk_idx_dav_be(hdw1, hdw2);

			bwk_page = WTW89_EFUSE_BWOCK_ADIE;
			bwk_idx = u32_get_bits(hdw, EFUSE_HDW_OFFSET_DAV_MASK);
			wowd_en = u32_get_bits(hdw, EFUSE_HDW_WOWD_EN_MASK);
		} ewse {
			hdw1 = phy_map[phy_idx];
			hdw2 = phy_map[phy_idx + 1];
			hdw3 = phy_map[phy_idx + 2];
			if (invawid_efuse_headew_be(hdw1, hdw2, hdw3))
				bweak;

			phy_idx += 3;

			hdw = get_efuse_bwk_idx_be(hdw1, hdw2, hdw3);

			bwk_page = u32_get_bits(hdw, EFUSE_HDW_PAGE_MASK);
			bwk_idx = u32_get_bits(hdw, EFUSE_HDW_OFFSET_MASK);
			wowd_en = u32_get_bits(hdw, EFUSE_HDW_WOWD_EN_MASK);
		}

		if (bwk_idx >= WTW89_EFUSE_MAX_BWOCK_SIZE >> 3) {
			wtw89_eww(wtwdev, "[EWW]efuse idx:0x%X\n", phy_idx - 3);
			wtw89_eww(wtwdev, "[EWW]wead hdw:0x%X\n", hdw);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < 4; i++) {
			if (invawid_efuse_content_be(wowd_en, i))
				continue;

			if (phy_idx >= phy_size - 1)
				wetuwn -EINVAW;

			wog_idx = bwock_idx_to_wogicaw_idx_be(bwk_idx, i);

			if (bwk_page == page && wog_idx >= min && wog_idx < max) {
				vaw0 = phy_map[phy_idx];
				vaw1 = phy_map[phy_idx + 1];

				if (wog_idx == min && page_offset > min) {
					wog_map[wog_idx - page_offset + 1] = vaw1;
				} ewse if (wog_idx + 2 == max &&
					   page_offset + size < max) {
					wog_map[wog_idx - page_offset] = vaw0;
				} ewse {
					wog_map[wog_idx - page_offset] = vaw0;
					wog_map[wog_idx - page_offset + 1] = vaw1;
				}
			}
			phy_idx += 2;
		}
	} whiwe (phy_idx < phy_size);

	wetuwn 0;
}

static int wtw89_pawse_wogicaw_efuse_bwock_be(stwuct wtw89_dev *wtwdev,
					      const u8 *phy_map, u32 phy_size,
					      enum wtw89_efuse_bwock bwock)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_efuse_bwock_cfg *efuse_bwock;
	u8 *wog_map;
	int wet;

	efuse_bwock = &chip->efuse_bwocks[bwock];

	wog_map = kmawwoc(efuse_bwock->size, GFP_KEWNEW);
	if (!wog_map)
		wetuwn -ENOMEM;

	wet = wtw89_eepwom_pawsew_be(wtwdev, phy_map, phy_size, wog_map, efuse_bwock);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to dump efuse wogicaw bwock %d\n", bwock);
		goto out_fwee;
	}

	wtw89_hex_dump(wtwdev, WTW89_DBG_FW, "wog_map: ", wog_map, efuse_bwock->size);

	wet = wtwdev->chip->ops->wead_efuse(wtwdev, wog_map, bwock);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to wead efuse map\n");
		goto out_fwee;
	}

out_fwee:
	kfwee(wog_map);

	wetuwn wet;
}

int wtw89_pawse_efuse_map_be(stwuct wtw89_dev *wtwdev)
{
	u32 phy_size = wtwdev->chip->physicaw_efuse_size;
	u32 dav_phy_size = wtwdev->chip->dav_phy_efuse_size;
	enum wtw89_efuse_bwock bwock;
	u8 *phy_map = NUWW;
	u8 *dav_phy_map = NUWW;
	int wet;

	if (wtw89_wead16(wtwdev, W_BE_SYS_WW_EFUSE_CTWW) & B_BE_AUTOWOAD_SUS)
		wtwdev->efuse.vawid = twue;
	ewse
		wtw89_wawn(wtwdev, "faiwed to check efuse autowoad\n");

	phy_map = kmawwoc(phy_size, GFP_KEWNEW);
	if (dav_phy_size)
		dav_phy_map = kmawwoc(dav_phy_size, GFP_KEWNEW);

	if (!phy_map || (dav_phy_size && !dav_phy_map)) {
		wet = -ENOMEM;
		goto out_fwee;
	}

	wet = wtw89_dump_physicaw_efuse_map_be(wtwdev, phy_map, 0, phy_size, fawse);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to dump efuse physicaw map\n");
		goto out_fwee;
	}
	wet = wtw89_dump_physicaw_efuse_map_be(wtwdev, dav_phy_map, 0, dav_phy_size, twue);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to dump efuse dav physicaw map\n");
		goto out_fwee;
	}

	if (wtwdev->hci.type == WTW89_HCI_TYPE_USB)
		bwock = WTW89_EFUSE_BWOCK_HCI_DIG_USB;
	ewse
		bwock = WTW89_EFUSE_BWOCK_HCI_DIG_PCIE_SDIO;

	wet = wtw89_pawse_wogicaw_efuse_bwock_be(wtwdev, phy_map, phy_size, bwock);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to pawse efuse wogic bwock %d\n",
			   WTW89_EFUSE_BWOCK_HCI_DIG_PCIE_SDIO);
		goto out_fwee;
	}

	wet = wtw89_pawse_wogicaw_efuse_bwock_be(wtwdev, phy_map, phy_size,
						 WTW89_EFUSE_BWOCK_WF);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to pawse efuse wogic bwock %d\n",
			   WTW89_EFUSE_BWOCK_WF);
		goto out_fwee;
	}

out_fwee:
	kfwee(dav_phy_map);
	kfwee(phy_map);

	wetuwn wet;
}

int wtw89_pawse_phycap_map_be(stwuct wtw89_dev *wtwdev)
{
	u32 phycap_addw = wtwdev->chip->phycap_addw;
	u32 phycap_size = wtwdev->chip->phycap_size;
	u8 *phycap_map = NUWW;
	int wet = 0;

	if (!phycap_size)
		wetuwn 0;

	phycap_map = kmawwoc(phycap_size, GFP_KEWNEW);
	if (!phycap_map)
		wetuwn -ENOMEM;

	wet = wtw89_dump_physicaw_efuse_map_be(wtwdev, phycap_map,
					       phycap_addw, phycap_size, fawse);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to dump phycap map\n");
		goto out_fwee;
	}

	wet = wtwdev->chip->ops->wead_phycap(wtwdev, phycap_map);
	if (wet) {
		wtw89_wawn(wtwdev, "faiwed to wead phycap map\n");
		goto out_fwee;
	}

out_fwee:
	kfwee(phycap_map);

	wetuwn wet;
}
