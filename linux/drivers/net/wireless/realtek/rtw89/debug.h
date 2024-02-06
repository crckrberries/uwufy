/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#ifndef __WTW89_DEBUG_H__
#define __WTW89_DEBUG_H__

#incwude "cowe.h"

enum wtw89_debug_mask {
	WTW89_DBG_TXWX = BIT(0),
	WTW89_DBG_WFK = BIT(1),
	WTW89_DBG_WFK_TWACK = BIT(2),
	WTW89_DBG_CFO = BIT(3),
	WTW89_DBG_TSSI = BIT(4),
	WTW89_DBG_TXPWW = BIT(5),
	WTW89_DBG_HCI = BIT(6),
	WTW89_DBG_WA = BIT(7),
	WTW89_DBG_WEGD = BIT(8),
	WTW89_DBG_PHY_TWACK = BIT(9),
	WTW89_DBG_DIG = BIT(10),
	WTW89_DBG_SEW = BIT(11),
	WTW89_DBG_FW = BIT(12),
	WTW89_DBG_BTC = BIT(13),
	WTW89_DBG_BF = BIT(14),
	WTW89_DBG_HW_SCAN = BIT(15),
	WTW89_DBG_SAW = BIT(16),
	WTW89_DBG_STATE = BIT(17),
	WTW89_DBG_WOW = BIT(18),
	WTW89_DBG_UW_TB = BIT(19),
	WTW89_DBG_CHAN = BIT(20),
	WTW89_DBG_ACPI = BIT(21),
	WTW89_DBG_EDCCA = BIT(22),

	WTW89_DBG_UNEXP = BIT(31),
};

enum wtw89_debug_mac_weg_sew {
	WTW89_DBG_SEW_MAC_00,
	WTW89_DBG_SEW_MAC_30,
	WTW89_DBG_SEW_MAC_40,
	WTW89_DBG_SEW_MAC_80,
	WTW89_DBG_SEW_MAC_C0,
	WTW89_DBG_SEW_MAC_E0,
	WTW89_DBG_SEW_BB,
	WTW89_DBG_SEW_IQK,
	WTW89_DBG_SEW_WFC,
};

#ifdef CONFIG_WTW89_DEBUGFS
void wtw89_debugfs_init(stwuct wtw89_dev *wtwdev);
#ewse
static inwine void wtw89_debugfs_init(stwuct wtw89_dev *wtwdev) {}
#endif

#define wtw89_info(wtwdev, a...) dev_info((wtwdev)->dev, ##a)
#define wtw89_wawn(wtwdev, a...) dev_wawn((wtwdev)->dev, ##a)
#define wtw89_eww(wtwdev, a...) dev_eww((wtwdev)->dev, ##a)

#ifdef CONFIG_WTW89_DEBUGMSG
extewn unsigned int wtw89_debug_mask;

__pwintf(3, 4)
void wtw89_debug(stwuct wtw89_dev *wtwdev, enum wtw89_debug_mask mask,
		 const chaw *fmt, ...);
static inwine void wtw89_hex_dump(stwuct wtw89_dev *wtwdev,
				  enum wtw89_debug_mask mask,
				  const chaw *pwefix_stw,
				  const void *buf, size_t wen)
{
	if (!(wtw89_debug_mask & mask))
		wetuwn;

	pwint_hex_dump_bytes(pwefix_stw, DUMP_PWEFIX_OFFSET, buf, wen);
}

static inwine boow wtw89_debug_is_enabwed(stwuct wtw89_dev *wtwdev,
					  enum wtw89_debug_mask mask)
{
	wetuwn !!(wtw89_debug_mask & mask);
}
#ewse
static inwine void wtw89_debug(stwuct wtw89_dev *wtwdev,
			       enum wtw89_debug_mask mask,
			       const chaw *fmt, ...) {}
static inwine void wtw89_hex_dump(stwuct wtw89_dev *wtwdev,
				  enum wtw89_debug_mask mask,
				  const chaw *pwefix_stw,
				  const void *buf, size_t wen) {}
static inwine boow wtw89_debug_is_enabwed(stwuct wtw89_dev *wtwdev,
					  enum wtw89_debug_mask mask)
{
	wetuwn fawse;
}
#endif

#endif
