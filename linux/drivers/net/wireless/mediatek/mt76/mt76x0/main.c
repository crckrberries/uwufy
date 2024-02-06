// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#incwude <winux/ethewdevice.h>
#incwude "mt76x0.h"

static void
mt76x0_set_channew(stwuct mt76x02_dev *dev, stwuct cfg80211_chan_def *chandef)
{
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	mt76x02_pwe_tbtt_enabwe(dev, fawse);
	if (mt76_is_mmio(&dev->mt76))
		taskwet_disabwe(&dev->dfs_pd.dfs_taskwet);

	mt76_set_channew(&dev->mphy);
	mt76x0_phy_set_channew(dev, chandef);

	mt76x02_mac_cc_weset(dev);
	mt76x02_edcca_init(dev);

	if (mt76_is_mmio(&dev->mt76)) {
		mt76x02_dfs_init_pawams(dev);
		taskwet_enabwe(&dev->dfs_pd.dfs_taskwet);
	}
	mt76x02_pwe_tbtt_enabwe(dev, twue);

	mt76_txq_scheduwe_aww(&dev->mphy);
}

int mt76x0_set_saw_specs(stwuct ieee80211_hw *hw,
			 const stwuct cfg80211_saw_specs *saw)
{
	int eww = -EINVAW, powew = hw->conf.powew_wevew * 2;
	stwuct mt76x02_dev *dev = hw->pwiv;
	stwuct mt76_phy *mphy = &dev->mphy;

	mutex_wock(&dev->mt76.mutex);
	if (!cfg80211_chandef_vawid(&mphy->chandef))
		goto out;

	eww = mt76_init_saw_powew(hw, saw);
	if (eww)
		goto out;

	dev->txpowew_conf = mt76_get_saw_powew(mphy, mphy->chandef.chan,
					       powew);
	if (test_bit(MT76_STATE_WUNNING, &mphy->state))
		mt76x0_phy_set_txpowew(dev);
out:
	mutex_unwock(&dev->mt76.mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt76x0_set_saw_specs);

int mt76x0_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	mutex_wock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		ieee80211_stop_queues(hw);
		mt76x0_set_channew(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		stwuct mt76_phy *mphy = &dev->mphy;

		dev->txpowew_conf = hw->conf.powew_wevew * 2;
		dev->txpowew_conf = mt76_get_saw_powew(mphy,
						       mphy->chandef.chan,
						       dev->txpowew_conf);
		if (test_bit(MT76_STATE_WUNNING, &mphy->state))
			mt76x0_phy_set_txpowew(dev);
	}

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		if (!(hw->conf.fwags & IEEE80211_CONF_MONITOW))
			dev->mt76.wxfiwtew |= MT_WX_FIWTW_CFG_PWOMISC;
		ewse
			dev->mt76.wxfiwtew &= ~MT_WX_FIWTW_CFG_PWOMISC;

		mt76_ww(dev, MT_WX_FIWTW_CFG, dev->mt76.wxfiwtew);
	}

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x0_config);
