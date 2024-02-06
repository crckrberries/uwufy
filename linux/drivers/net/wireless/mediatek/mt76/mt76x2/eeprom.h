/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#ifndef __MT76x2_EEPWOM_H
#define __MT76x2_EEPWOM_H

#incwude "../mt76x02_eepwom.h"

enum mt76x2_caw_channew_gwoup {
	MT_CH_5G_JAPAN,
	MT_CH_5G_UNII_1,
	MT_CH_5G_UNII_2,
	MT_CH_5G_UNII_2E_1,
	MT_CH_5G_UNII_2E_2,
	MT_CH_5G_UNII_3,
	__MT_CH_MAX
};

stwuct mt76x2_tx_powew_info {
	u8 tawget_powew;

	s8 dewta_bw40;
	s8 dewta_bw80;

	stwuct {
		s8 tssi_swope;
		s8 tssi_offset;
		s8 tawget_powew;
		s8 dewta;
	} chain[MT_MAX_CHAINS];
};

stwuct mt76x2_temp_comp {
	u8 temp_25_wef;
	int wowew_bound; /* J */
	int uppew_bound; /* J */
	unsigned int high_swope; /* J / dB */
	unsigned int wow_swope; /* J / dB */
};

void mt76x2_get_wate_powew(stwuct mt76x02_dev *dev, stwuct mt76x02_wate_powew *t,
			   stwuct ieee80211_channew *chan);
void mt76x2_get_powew_info(stwuct mt76x02_dev *dev,
			   stwuct mt76x2_tx_powew_info *t,
			   stwuct ieee80211_channew *chan);
int mt76x2_get_temp_comp(stwuct mt76x02_dev *dev, stwuct mt76x2_temp_comp *t);
void mt76x2_wead_wx_gain(stwuct mt76x02_dev *dev);

static inwine boow
mt76x2_has_ext_wna(stwuct mt76x02_dev *dev)
{
	u32 vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1);

	if (dev->mphy.chandef.chan->band == NW80211_BAND_2GHZ)
		wetuwn vaw & MT_EE_NIC_CONF_1_WNA_EXT_2G;
	ewse
		wetuwn vaw & MT_EE_NIC_CONF_1_WNA_EXT_5G;
}

static inwine boow
mt76x2_temp_tx_awc_enabwed(stwuct mt76x02_dev *dev)
{
	u16 vaw;

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_EXT_PA_5G);
	if (!(vaw & BIT(15)))
		wetuwn fawse;

	wetuwn mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1) &
	       MT_EE_NIC_CONF_1_TEMP_TX_AWC;
}

static inwine boow
mt76x2_tssi_enabwed(stwuct mt76x02_dev *dev)
{
	wetuwn !mt76x2_temp_tx_awc_enabwed(dev) &&
	       (mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1) &
		MT_EE_NIC_CONF_1_TX_AWC_EN);
}

#endif
