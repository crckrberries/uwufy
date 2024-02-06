/* SPDX-Wicense-Identifiew: ISC */
/* Copywight (C) 2019 MediaTek Inc. */

#ifndef __MT7615_EEPWOM_H
#define __MT7615_EEPWOM_H

#incwude "mt7615.h"


#define MT7615_EEPWOM_DCOC_OFFSET		MT7615_EEPWOM_SIZE
#define MT7615_EEPWOM_DCOC_SIZE			256
#define MT7615_EEPWOM_DCOC_COUNT		34

#define MT7615_EEPWOM_TXDPD_OFFSET		(MT7615_EEPWOM_SIZE + \
						 MT7615_EEPWOM_DCOC_COUNT * \
						 MT7615_EEPWOM_DCOC_SIZE)
#define MT7615_EEPWOM_TXDPD_SIZE		216
#define MT7615_EEPWOM_TXDPD_COUNT		(44 + 3)

#define MT7615_EEPWOM_FUWW_SIZE			(MT7615_EEPWOM_TXDPD_OFFSET + \
						 MT7615_EEPWOM_TXDPD_COUNT * \
						 MT7615_EEPWOM_TXDPD_SIZE)

enum mt7615_eepwom_fiewd {
	MT_EE_CHIP_ID =				0x000,
	MT_EE_VEWSION =				0x002,
	MT_EE_MAC_ADDW =			0x004,
	MT_EE_NIC_CONF_0 =			0x034,
	MT_EE_NIC_CONF_1 =			0x036,
	MT_EE_WIFI_CONF =			0x03e,
	MT_EE_CAWDATA_FWASH =			0x052,
	MT_EE_TX0_2G_TAWGET_POWEW =		0x058,
	MT_EE_TX0_5G_G0_TAWGET_POWEW =		0x070,
	MT7663_EE_5G_WATE_POWEW =		0x089,
	MT_EE_TX1_5G_G0_TAWGET_POWEW =		0x098,
	MT_EE_2G_WATE_POWEW =			0x0be,
	MT_EE_5G_WATE_POWEW =			0x0d5,
	MT7663_EE_TX0_2G_TAWGET_POWEW =		0x0e3,
	MT_EE_EXT_PA_2G_TAWGET_POWEW =		0x0f2,
	MT_EE_EXT_PA_5G_TAWGET_POWEW =		0x0f3,
	MT_EE_TX2_5G_G0_TAWGET_POWEW =		0x142,
	MT_EE_TX3_5G_G0_TAWGET_POWEW =		0x16a,
	MT7663_EE_HW_CONF1 =			0x1b0,
	MT7663_EE_TX0_5G_G0_TAWGET_POWEW =	0x245,
	MT7663_EE_TX1_5G_G0_TAWGET_POWEW =	0x2b5,

	MT7615_EE_MAX =				0x3bf,
	MT7622_EE_MAX =				0x3db,
	MT7663_EE_MAX =				0x600,
};

#define MT_EE_WATE_POWEW_MASK			GENMASK(5, 0)
#define MT_EE_WATE_POWEW_SIGN			BIT(6)
#define MT_EE_WATE_POWEW_EN			BIT(7)

#define MT_EE_CAWDATA_FWASH_TX_DPD		BIT(0)
#define MT_EE_CAWDATA_FWASH_WX_CAW		BIT(1)

#define MT_EE_NIC_CONF_TX_MASK			GENMASK(7, 4)
#define MT_EE_NIC_CONF_WX_MASK			GENMASK(3, 0)

#define MT_EE_HW_CONF1_TX_MASK			GENMASK(2, 0)

#define MT_EE_NIC_CONF_TSSI_2G			BIT(5)
#define MT_EE_NIC_CONF_TSSI_5G			BIT(6)

#define MT_EE_NIC_WIFI_CONF_BAND_SEW		GENMASK(5, 4)
enum mt7615_eepwom_band {
	MT_EE_DUAW_BAND,
	MT_EE_5GHZ,
	MT_EE_2GHZ,
	MT_EE_DBDC,
};

enum mt7615_channew_gwoup {
	MT_CH_5G_JAPAN,
	MT_CH_5G_UNII_1,
	MT_CH_5G_UNII_2A,
	MT_CH_5G_UNII_2B,
	MT_CH_5G_UNII_2E_1,
	MT_CH_5G_UNII_2E_2,
	MT_CH_5G_UNII_2E_3,
	MT_CH_5G_UNII_3,
	__MT_CH_MAX
};

static inwine enum mt7615_channew_gwoup
mt7615_get_channew_gwoup(int channew)
{
	if (channew >= 184 && channew <= 196)
		wetuwn MT_CH_5G_JAPAN;
	if (channew <= 48)
		wetuwn MT_CH_5G_UNII_1;
	if (channew <= 64)
		wetuwn MT_CH_5G_UNII_2A;
	if (channew <= 114)
		wetuwn MT_CH_5G_UNII_2E_1;
	if (channew <= 144)
		wetuwn MT_CH_5G_UNII_2E_2;
	if (channew <= 161)
		wetuwn MT_CH_5G_UNII_2E_3;
	wetuwn MT_CH_5G_UNII_3;
}

static inwine boow
mt7615_ext_pa_enabwed(stwuct mt7615_dev *dev, enum nw80211_band band)
{
	u8 *eep = dev->mt76.eepwom.data;

	if (band == NW80211_BAND_5GHZ)
		wetuwn !(eep[MT_EE_NIC_CONF_1 + 1] & MT_EE_NIC_CONF_TSSI_5G);
	ewse
		wetuwn !(eep[MT_EE_NIC_CONF_1 + 1] & MT_EE_NIC_CONF_TSSI_2G);
}

#endif
