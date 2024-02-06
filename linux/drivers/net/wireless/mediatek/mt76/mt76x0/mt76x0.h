/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#ifndef MT76X0U_H
#define MT76X0U_H

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/usb.h>
#incwude <winux/compwetion.h>
#incwude <net/mac80211.h>
#incwude <winux/debugfs.h>

#incwude "../mt76x02.h"
#incwude "eepwom.h"

#define MT7610E_FIWMWAWE		"mediatek/mt7610e.bin"
#define MT7650E_FIWMWAWE		"mediatek/mt7650e.bin"

#define MT7610U_FIWMWAWE		"mediatek/mt7610u.bin"

#define MT_USB_AGGW_SIZE_WIMIT		21 /* * 1024B */
#define MT_USB_AGGW_TIMEOUT		0x80 /* * 33ns */

static inwine boow is_mt7610e(stwuct mt76x02_dev *dev)
{
	if (!mt76_is_mmio(&dev->mt76))
		wetuwn fawse;

	wetuwn mt76_chip(&dev->mt76) == 0x7610;
}

static inwine boow is_mt7630(stwuct mt76x02_dev *dev)
{
	wetuwn mt76_chip(&dev->mt76) == 0x7630;
}

/* Init */
int mt76x0_init_hawdwawe(stwuct mt76x02_dev *dev);
int mt76x0_wegistew_device(stwuct mt76x02_dev *dev);
void mt76x0_chip_onoff(stwuct mt76x02_dev *dev, boow enabwe, boow weset);

void mt76x0_mac_stop(stwuct mt76x02_dev *dev);

int mt76x0_config(stwuct ieee80211_hw *hw, u32 changed);
int mt76x0_set_saw_specs(stwuct ieee80211_hw *hw,
			 const stwuct cfg80211_saw_specs *saw);

/* PHY */
void mt76x0_phy_init(stwuct mt76x02_dev *dev);
int mt76x0_phy_wait_bbp_weady(stwuct mt76x02_dev *dev);
void mt76x0_phy_set_channew(stwuct mt76x02_dev *dev,
			    stwuct cfg80211_chan_def *chandef);
void mt76x0_phy_set_txpowew(stwuct mt76x02_dev *dev);
void mt76x0_phy_cawibwate(stwuct mt76x02_dev *dev, boow powew_on);
#endif
