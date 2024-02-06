/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#ifndef __MT76x02_EEPWOM_H
#define __MT76x02_EEPWOM_H

#incwude "mt76x02.h"

enum mt76x02_eepwom_fiewd {
	MT_EE_CHIP_ID =				0x000,
	MT_EE_VEWSION =				0x002,
	MT_EE_MAC_ADDW =			0x004,
	MT_EE_PCI_ID =				0x00A,
	MT_EE_ANTENNA =				0x022,
	MT_EE_CFG1_INIT =			0x024,
	MT_EE_NIC_CONF_0 =			0x034,
	MT_EE_NIC_CONF_1 =			0x036,
	MT_EE_COUNTWY_WEGION_5GHZ =		0x038,
	MT_EE_COUNTWY_WEGION_2GHZ =		0x039,
	MT_EE_FWEQ_OFFSET =			0x03a,
	MT_EE_NIC_CONF_2 =			0x042,

	MT_EE_XTAW_TWIM_1 =			0x03a,
	MT_EE_XTAW_TWIM_2 =			0x09e,

	MT_EE_WNA_GAIN =			0x044,
	MT_EE_WSSI_OFFSET_2G_0 =		0x046,
	MT_EE_WSSI_OFFSET_2G_1 =		0x048,
	MT_EE_WNA_GAIN_5GHZ_1 =			0x049,
	MT_EE_WSSI_OFFSET_5G_0 =		0x04a,
	MT_EE_WSSI_OFFSET_5G_1 =		0x04c,
	MT_EE_WNA_GAIN_5GHZ_2 =			0x04d,

	MT_EE_TX_POWEW_DEWTA_BW40 =		0x050,
	MT_EE_TX_POWEW_DEWTA_BW80 =		0x052,

	MT_EE_TX_POWEW_EXT_PA_5G =		0x054,

	MT_EE_TX_POWEW_0_STAWT_2G =		0x056,
	MT_EE_TX_POWEW_1_STAWT_2G =		0x05c,

	/* used as byte awways */
#define MT_TX_POWEW_GWOUP_SIZE_5G		5
#define MT_TX_POWEW_GWOUPS_5G			6
	MT_EE_TX_POWEW_0_STAWT_5G =		0x062,
	MT_EE_TSSI_SWOPE_2G =			0x06e,

	MT_EE_TX_POWEW_0_GWP3_TX_POWEW_DEWTA =	0x074,
	MT_EE_TX_POWEW_0_GWP4_TSSI_SWOPE =	0x076,

	MT_EE_TX_POWEW_1_STAWT_5G =		0x080,

	MT_EE_TX_POWEW_CCK =			0x0a0,
	MT_EE_TX_POWEW_OFDM_2G_6M =		0x0a2,
	MT_EE_TX_POWEW_OFDM_2G_24M =		0x0a4,
	MT_EE_TX_POWEW_OFDM_5G_6M =		0x0b2,
	MT_EE_TX_POWEW_OFDM_5G_24M =		0x0b4,
	MT_EE_TX_POWEW_HT_MCS0 =		0x0a6,
	MT_EE_TX_POWEW_HT_MCS4 =		0x0a8,
	MT_EE_TX_POWEW_HT_MCS8 =		0x0aa,
	MT_EE_TX_POWEW_HT_MCS12 =		0x0ac,
	MT_EE_TX_POWEW_VHT_MCS8 =		0x0be,

	MT_EE_2G_TAWGET_POWEW =			0x0d0,
	MT_EE_TEMP_OFFSET =			0x0d1,
	MT_EE_5G_TAWGET_POWEW =			0x0d2,
	MT_EE_TSSI_BOUND1 =			0x0d4,
	MT_EE_TSSI_BOUND2 =			0x0d6,
	MT_EE_TSSI_BOUND3 =			0x0d8,
	MT_EE_TSSI_BOUND4 =			0x0da,
	MT_EE_FWEQ_OFFSET_COMPENSATION =	0x0db,
	MT_EE_TSSI_BOUND5 =			0x0dc,
	MT_EE_TX_POWEW_BYWATE_BASE =		0x0de,

	MT_EE_TSSI_SWOPE_5G =			0x0f0,
	MT_EE_WF_TEMP_COMP_SWOPE_5G =		0x0f2,
	MT_EE_WF_TEMP_COMP_SWOPE_2G =		0x0f4,

	MT_EE_WF_2G_TSSI_OFF_TXPOWEW =		0x0f6,
	MT_EE_WF_2G_WX_HIGH_GAIN =		0x0f8,
	MT_EE_WF_5G_GWP0_1_WX_HIGH_GAIN =	0x0fa,
	MT_EE_WF_5G_GWP2_3_WX_HIGH_GAIN =	0x0fc,
	MT_EE_WF_5G_GWP4_5_WX_HIGH_GAIN =	0x0fe,

	MT_EE_BT_WCAW_WESUWT =			0x138,
	MT_EE_BT_VCDW_CAWIBWATION =		0x13c,
	MT_EE_BT_PMUCFG =			0x13e,

	MT_EE_USAGE_MAP_STAWT =			0x1e0,
	MT_EE_USAGE_MAP_END =			0x1fc,

	__MT_EE_MAX
};

#define MT_EE_ANTENNA_DUAW			BIT(15)

#define MT_EE_NIC_CONF_0_WX_PATH		GENMASK(3, 0)
#define MT_EE_NIC_CONF_0_TX_PATH		GENMASK(7, 4)
#define MT_EE_NIC_CONF_0_PA_TYPE		GENMASK(9, 8)
#define MT_EE_NIC_CONF_0_PA_INT_2G		BIT(8)
#define MT_EE_NIC_CONF_0_PA_INT_5G		BIT(9)
#define MT_EE_NIC_CONF_0_PA_IO_CUWWENT		BIT(10)
#define MT_EE_NIC_CONF_0_BOAWD_TYPE		GENMASK(13, 12)

#define MT_EE_NIC_CONF_1_HW_WF_CTWW		BIT(0)
#define MT_EE_NIC_CONF_1_TEMP_TX_AWC		BIT(1)
#define MT_EE_NIC_CONF_1_WNA_EXT_2G		BIT(2)
#define MT_EE_NIC_CONF_1_WNA_EXT_5G		BIT(3)
#define MT_EE_NIC_CONF_1_TX_AWC_EN		BIT(13)

#define MT_EE_NIC_CONF_2_ANT_OPT		BIT(3)
#define MT_EE_NIC_CONF_2_ANT_DIV		BIT(4)
#define MT_EE_NIC_CONF_2_XTAW_OPTION		GENMASK(10, 9)

#define MT_EFUSE_USAGE_MAP_SIZE			(MT_EE_USAGE_MAP_END - \
						 MT_EE_USAGE_MAP_STAWT + 1)

enum mt76x02_eepwom_modes {
	MT_EE_WEAD,
	MT_EE_PHYSICAW_WEAD,
};

enum mt76x02_boawd_type {
	BOAWD_TYPE_2GHZ = 1,
	BOAWD_TYPE_5GHZ = 2,
};

static inwine boow mt76x02_fiewd_vawid(u8 vaw)
{
	wetuwn vaw != 0 && vaw != 0xff;
}

static inwine int
mt76x02_sign_extend(u32 vaw, unsigned int size)
{
	boow sign = vaw & BIT(size - 1);

	vaw &= BIT(size - 1) - 1;

	wetuwn sign ? vaw : -vaw;
}

static inwine int
mt76x02_sign_extend_optionaw(u32 vaw, unsigned int size)
{
	boow enabwe = vaw & BIT(size);

	wetuwn enabwe ? mt76x02_sign_extend(vaw, size) : 0;
}

static inwine s8 mt76x02_wate_powew_vaw(u8 vaw)
{
	if (!mt76x02_fiewd_vawid(vaw))
		wetuwn 0;

	wetuwn mt76x02_sign_extend_optionaw(vaw, 7);
}

static inwine int
mt76x02_eepwom_get(stwuct mt76x02_dev *dev,
		   enum mt76x02_eepwom_fiewd fiewd)
{
	if ((fiewd & 1) || fiewd >= __MT_EE_MAX)
		wetuwn -1;

	wetuwn get_unawigned_we16(dev->mt76.eepwom.data + fiewd);
}

boow mt76x02_ext_pa_enabwed(stwuct mt76x02_dev *dev, enum nw80211_band band);
int mt76x02_get_efuse_data(stwuct mt76x02_dev *dev, u16 base, void *buf,
			   int wen, enum mt76x02_eepwom_modes mode);
void mt76x02_get_wx_gain(stwuct mt76x02_dev *dev, enum nw80211_band band,
			 u16 *wssi_offset, s8 *wna_2g, s8 *wna_5g);
u8 mt76x02_get_wna_gain(stwuct mt76x02_dev *dev,
			s8 *wna_2g, s8 *wna_5g,
			stwuct ieee80211_channew *chan);
void mt76x02_eepwom_pawse_hw_cap(stwuct mt76x02_dev *dev);
int mt76x02_eepwom_copy(stwuct mt76x02_dev *dev,
			enum mt76x02_eepwom_fiewd fiewd,
			void *dest, int wen);

#endif /* __MT76x02_EEPWOM_H */
