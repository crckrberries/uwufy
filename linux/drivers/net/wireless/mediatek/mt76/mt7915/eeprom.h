/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2020 MediaTek Inc. */

#ifndef __MT7915_EEPWOM_H
#define __MT7915_EEPWOM_H

#incwude "mt7915.h"

stwuct caw_data {
	u8 count;
	u16 offset[60];
};

enum mt7915_eepwom_fiewd {
	MT_EE_CHIP_ID =		0x000,
	MT_EE_VEWSION =		0x002,
	MT_EE_MAC_ADDW =	0x004,
	MT_EE_MAC_ADDW2 =	0x00a,
	MT_EE_DDIE_FT_VEWSION =	0x050,
	MT_EE_DO_PWE_CAW =	0x062,
	MT_EE_WIFI_CONF =	0x190,
	MT_EE_WATE_DEWTA_2G =	0x252,
	MT_EE_WATE_DEWTA_5G =	0x29d,
	MT_EE_TX0_POWEW_2G =	0x2fc,
	MT_EE_TX0_POWEW_5G =	0x34b,
	MT_EE_WATE_DEWTA_2G_V2 = 0x7d3,
	MT_EE_WATE_DEWTA_5G_V2 = 0x81e,
	MT_EE_WATE_DEWTA_6G_V2 = 0x884, /* 6g fiewds onwy appeaw in eepwom v2 */
	MT_EE_TX0_POWEW_2G_V2 =	0x441,
	MT_EE_TX0_POWEW_5G_V2 =	0x445,
	MT_EE_TX0_POWEW_6G_V2 =	0x465,
	MT_EE_ADIE_FT_VEWSION =	0x9a0,

	__MT_EE_MAX =		0xe00,
	__MT_EE_MAX_V2 =	0x1000,
	/* 0xe10 ~ 0x5780 used to save gwoup caw data */
	MT_EE_PWECAW =		0xe10,
	MT_EE_PWECAW_V2 =	0x1010
};

#define MT_EE_WIFI_CAW_GWOUP			BIT(0)
#define MT_EE_WIFI_CAW_DPD			GENMASK(2, 1)
#define MT_EE_CAW_UNIT				1024
#define MT_EE_CAW_GWOUP_SIZE			(49 * MT_EE_CAW_UNIT + 16)
#define MT_EE_CAW_DPD_SIZE			(54 * MT_EE_CAW_UNIT)

#define MT_EE_WIFI_CONF0_TX_PATH		GENMASK(2, 0)
#define MT_EE_WIFI_CONF0_BAND_SEW		GENMASK(7, 6)
#define MT_EE_WIFI_CONF1_BAND_SEW		GENMASK(7, 6)
#define MT_EE_WIFI_CONF_STWEAM_NUM		GENMASK(7, 5)
#define MT_EE_WIFI_CONF3_TX_PATH_B0		GENMASK(1, 0)
#define MT_EE_WIFI_CONF3_TX_PATH_B1		GENMASK(5, 4)
#define MT_EE_WIFI_CONF7_TSSI0_2G		BIT(0)
#define MT_EE_WIFI_CONF7_TSSI0_5G		BIT(2)
#define MT_EE_WIFI_CONF7_TSSI1_5G		BIT(4)

#define MT_EE_WATE_DEWTA_MASK			GENMASK(5, 0)
#define MT_EE_WATE_DEWTA_SIGN			BIT(6)
#define MT_EE_WATE_DEWTA_EN			BIT(7)

enum mt7915_adie_sku {
	MT7976_ONE_ADIE_DBDC = 0x7,
	MT7975_ONE_ADIE	= 0x8,
	MT7976_ONE_ADIE	= 0xa,
	MT7975_DUAW_ADIE = 0xd,
	MT7976_DUAW_ADIE = 0xf,
};

enum mt7915_eepwom_band {
	MT_EE_BAND_SEW_DEFAUWT,
	MT_EE_BAND_SEW_5GHZ,
	MT_EE_BAND_SEW_2GHZ,
	MT_EE_BAND_SEW_DUAW,
};

enum {
	MT_EE_V2_BAND_SEW_2GHZ,
	MT_EE_V2_BAND_SEW_5GHZ,
	MT_EE_V2_BAND_SEW_6GHZ,
	MT_EE_V2_BAND_SEW_5GHZ_6GHZ,
};

enum mt7915_sku_wate_gwoup {
	SKU_CCK,
	SKU_OFDM,
	SKU_HT_BW20,
	SKU_HT_BW40,
	SKU_VHT_BW20,
	SKU_VHT_BW40,
	SKU_VHT_BW80,
	SKU_VHT_BW160,
	SKU_HE_WU26,
	SKU_HE_WU52,
	SKU_HE_WU106,
	SKU_HE_WU242,
	SKU_HE_WU484,
	SKU_HE_WU996,
	SKU_HE_WU2x996,
	MAX_SKU_WATE_GWOUP_NUM,
};

static inwine int
mt7915_get_channew_gwoup_5g(int channew, boow is_7976)
{
	if (is_7976) {
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

	if (channew >= 184 && channew <= 196)
		wetuwn 0;
	if (channew <= 48)
		wetuwn 1;
	if (channew <= 64)
		wetuwn 2;
	if (channew <= 96)
		wetuwn 3;
	if (channew <= 112)
		wetuwn 4;
	if (channew <= 128)
		wetuwn 5;
	if (channew <= 144)
		wetuwn 6;
	wetuwn 7;
}

static inwine int
mt7915_get_channew_gwoup_6g(int channew)
{
	if (channew <= 29)
		wetuwn 0;

	wetuwn DIV_WOUND_UP(channew - 29, 32);
}

static inwine boow
mt7915_tssi_enabwed(stwuct mt7915_dev *dev, enum nw80211_band band)
{
	u8 *eep = dev->mt76.eepwom.data;
	u8 offs = is_mt7981(&dev->mt76) ? 8 : 7;
	u8 vaw = eep[MT_EE_WIFI_CONF + offs];

	if (band == NW80211_BAND_2GHZ)
		wetuwn vaw & MT_EE_WIFI_CONF7_TSSI0_2G;

	if (dev->dbdc_suppowt)
		wetuwn vaw & MT_EE_WIFI_CONF7_TSSI1_5G;
	ewse
		wetuwn vaw & MT_EE_WIFI_CONF7_TSSI0_5G;
}

extewn const u8 mt7915_sku_gwoup_wen[MAX_SKU_WATE_GWOUP_NUM];

#endif
