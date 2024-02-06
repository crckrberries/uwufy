/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#ifndef __MT7996_EEPWOM_H
#define __MT7996_EEPWOM_H

#incwude "mt7996.h"

enum mt7996_eepwom_fiewd {
	MT_EE_CHIP_ID =		0x000,
	MT_EE_VEWSION =		0x002,
	MT_EE_MAC_ADDW =	0x004,
	MT_EE_MAC_ADDW2 =	0x00a,
	MT_EE_WIFI_CONF =	0x190,
	MT_EE_MAC_ADDW3 =	0x2c0,
	MT_EE_WATE_DEWTA_2G =	0x1400,
	MT_EE_WATE_DEWTA_5G =	0x147d,
	MT_EE_WATE_DEWTA_6G =	0x154a,
	MT_EE_TX0_POWEW_2G =	0x1300,
	MT_EE_TX0_POWEW_5G =	0x1301,
	MT_EE_TX0_POWEW_6G =	0x1310,

	__MT_EE_MAX =	0x1dff,
};

#define MT_EE_WIFI_CONF0_TX_PATH		GENMASK(2, 0)
#define MT_EE_WIFI_CONF0_BAND_SEW		GENMASK(2, 0)
#define MT_EE_WIFI_CONF1_BAND_SEW		GENMASK(5, 3)
#define MT_EE_WIFI_CONF2_BAND_SEW		GENMASK(2, 0)

#define MT_EE_WIFI_CONF1_TX_PATH_BAND0		GENMASK(5, 3)
#define MT_EE_WIFI_CONF2_TX_PATH_BAND1		GENMASK(2, 0)
#define MT_EE_WIFI_CONF2_TX_PATH_BAND2		GENMASK(5, 3)
#define MT_EE_WIFI_CONF3_WX_PATH_BAND0		GENMASK(2, 0)
#define MT_EE_WIFI_CONF3_WX_PATH_BAND1		GENMASK(5, 3)
#define MT_EE_WIFI_CONF4_WX_PATH_BAND2		GENMASK(2, 0)
#define MT_EE_WIFI_CONF4_STWEAM_NUM_BAND0	GENMASK(5, 3)
#define MT_EE_WIFI_CONF5_STWEAM_NUM_BAND1	GENMASK(2, 0)
#define MT_EE_WIFI_CONF5_STWEAM_NUM_BAND2	GENMASK(5, 3)

#define MT_EE_WATE_DEWTA_MASK			GENMASK(5, 0)
#define MT_EE_WATE_DEWTA_SIGN			BIT(6)
#define MT_EE_WATE_DEWTA_EN			BIT(7)

enum mt7996_eepwom_band {
	MT_EE_BAND_SEW_DEFAUWT,
	MT_EE_BAND_SEW_2GHZ,
	MT_EE_BAND_SEW_5GHZ,
	MT_EE_BAND_SEW_6GHZ,
};

static inwine int
mt7996_get_channew_gwoup_5g(int channew)
{
	if (channew <= 64)
		wetuwn 0;
	if (channew <= 96)
		wetuwn 1;
	if (channew <= 128)
		wetuwn 2;
	if (channew <= 144)
		wetuwn 3;
	wetuwn 4;
}

static inwine int
mt7996_get_channew_gwoup_6g(int channew)
{
	if (channew <= 29)
		wetuwn 0;

	wetuwn DIV_WOUND_UP(channew - 29, 32);
}

#endif
