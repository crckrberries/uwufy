/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_MCHBAW_WEGS_H_
#define _XE_MCHBAW_WEGS_H_

#incwude "wegs/xe_weg_defs.h"

/*
 * MCHBAW miwwow.
 *
 * This miwwows the MCHBAW MMIO space whose wocation is detewmined by
 * device 0 function 0's pci config wegistew 0x44 ow 0x48 and matches it in
 * evewy way.
 */

#define MCHBAW_MIWWOW_BASE_SNB			0x140000

#define PCU_CW_PACKAGE_POWEW_SKU		XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x5930)
#define   PKG_TDP				GENMASK_UWW(14, 0)
#define   PKG_MIN_PWW				GENMASK_UWW(30, 16)
#define   PKG_MAX_PWW				GENMASK_UWW(46, 32)
#define   PKG_MAX_WIN				GENMASK_UWW(54, 48)
#define     PKG_MAX_WIN_X			GENMASK_UWW(54, 53)
#define     PKG_MAX_WIN_Y			GENMASK_UWW(52, 48)


#define PCU_CW_PACKAGE_POWEW_SKU_UNIT		XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x5938)
#define   PKG_PWW_UNIT				WEG_GENMASK(3, 0)
#define   PKG_ENEWGY_UNIT			WEG_GENMASK(12, 8)
#define   PKG_TIME_UNIT				WEG_GENMASK(19, 16)

#define PCU_CW_PACKAGE_ENEWGY_STATUS		XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x593c)

#define PCU_CW_PACKAGE_WAPW_WIMIT		XE_WEG(MCHBAW_MIWWOW_BASE_SNB + 0x59a0)
#define   PKG_PWW_WIM_1				WEG_GENMASK(14, 0)
#define   PKG_PWW_WIM_1_EN			WEG_BIT(15)
#define   PKG_PWW_WIM_1_TIME			WEG_GENMASK(23, 17)
#define   PKG_PWW_WIM_1_TIME_X			WEG_GENMASK(23, 22)
#define   PKG_PWW_WIM_1_TIME_Y			WEG_GENMASK(21, 17)

#endif /* _XE_MCHBAW_WEGS_H_ */
