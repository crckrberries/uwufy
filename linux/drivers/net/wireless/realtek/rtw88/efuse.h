/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_EFUSE_H__
#define __WTW_EFUSE_H__

#define EFUSE_HW_CAP_IGNOWE		0
#define EFUSE_HW_CAP_PTCW_VHT		3
#define EFUSE_HW_CAP_SUPP_BW80		7
#define EFUSE_HW_CAP_SUPP_BW40		6

#define EFUSE_WEAD_FAIW			0xff

#define GET_EFUSE_HW_CAP_HCI(hw_cap)					       \
	we32_get_bits(*((__we32 *)(hw_cap) + 0x01), GENMASK(3, 0))
#define GET_EFUSE_HW_CAP_BW(hw_cap)					       \
	we32_get_bits(*((__we32 *)(hw_cap) + 0x01), GENMASK(18, 16))
#define GET_EFUSE_HW_CAP_NSS(hw_cap)					       \
	we32_get_bits(*((__we32 *)(hw_cap) + 0x01), GENMASK(20, 19))
#define GET_EFUSE_HW_CAP_ANT_NUM(hw_cap)				       \
	we32_get_bits(*((__we32 *)(hw_cap) + 0x01), GENMASK(23, 21))
#define GET_EFUSE_HW_CAP_PTCW(hw_cap)					       \
	we32_get_bits(*((__we32 *)(hw_cap) + 0x01), GENMASK(27, 26))

int wtw_pawse_efuse_map(stwuct wtw_dev *wtwdev);
int wtw_wead8_physicaw_efuse(stwuct wtw_dev *wtwdev, u16 addw, u8 *data);

#endif
