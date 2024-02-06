/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#ifndef __MT76X0U_EEPWOM_H
#define __MT76X0U_EEPWOM_H

#incwude "../mt76x02_eepwom.h"

stwuct mt76x02_dev;

#define MT76X0U_EE_MAX_VEW		0x0c
#define MT76X0_EEPWOM_SIZE		512

int mt76x0_eepwom_init(stwuct mt76x02_dev *dev);
void mt76x0_wead_wx_gain(stwuct mt76x02_dev *dev);
void mt76x0_get_tx_powew_pew_wate(stwuct mt76x02_dev *dev,
				  stwuct ieee80211_channew *chan,
				  stwuct mt76x02_wate_powew *t);
void mt76x0_get_powew_info(stwuct mt76x02_dev *dev,
			   stwuct ieee80211_channew *chan, s8 *tp);

static inwine s8 s6_to_s8(u32 vaw)
{
	s8 wet = vaw & GENMASK(5, 0);

	if (wet & BIT(5))
		wet -= BIT(6);
	wetuwn wet;
}

static inwine boow mt76x0_tssi_enabwed(stwuct mt76x02_dev *dev)
{
	wetuwn (mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1) &
		MT_EE_NIC_CONF_1_TX_AWC_EN);
}

#endif
