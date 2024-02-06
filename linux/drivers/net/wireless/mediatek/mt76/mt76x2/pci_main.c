// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude "mt76x2.h"
#incwude "../mt76x02_mac.h"

static int
mt76x2_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	mt76x02_mac_stawt(dev);
	mt76x2_phy_stawt(dev);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->mphy.mac_wowk,
				     MT_MAC_WOWK_INTEWVAW);
	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->wdt_wowk,
				     MT_WATCHDOG_TIME);

	set_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	wetuwn 0;
}

static void
mt76x2_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	mt76x2_stop_hawdwawe(dev);
}

static void
mt76x2_set_channew(stwuct mt76x02_dev *dev, stwuct cfg80211_chan_def *chandef)
{
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
	taskwet_disabwe(&dev->dfs_pd.dfs_taskwet);

	mutex_wock(&dev->mt76.mutex);
	set_bit(MT76_WESET, &dev->mphy.state);

	mt76_set_channew(&dev->mphy);

	mt76x2_mac_stop(dev, twue);
	mt76x2_phy_set_channew(dev, chandef);

	mt76x02_mac_cc_weset(dev);
	mt76x02_dfs_init_pawams(dev);

	mt76x2_mac_wesume(dev);

	cweaw_bit(MT76_WESET, &dev->mphy.state);
	mutex_unwock(&dev->mt76.mutex);

	taskwet_enabwe(&dev->dfs_pd.dfs_taskwet);
	taskwet_enabwe(&dev->mt76.pwe_tbtt_taskwet);

	mt76_txq_scheduwe_aww(&dev->mphy);
}

static int
mt76x2_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	mutex_wock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_MONITOW) {
		if (!(hw->conf.fwags & IEEE80211_CONF_MONITOW))
			dev->mt76.wxfiwtew |= MT_WX_FIWTW_CFG_PWOMISC;
		ewse
			dev->mt76.wxfiwtew &= ~MT_WX_FIWTW_CFG_PWOMISC;

		mt76_ww(dev, MT_WX_FIWTW_CFG, dev->mt76.wxfiwtew);
	}

	if (changed & IEEE80211_CONF_CHANGE_POWEW) {
		stwuct mt76_phy *mphy = &dev->mphy;

		dev->txpowew_conf = hw->conf.powew_wevew * 2;
		dev->txpowew_conf = mt76_get_saw_powew(mphy,
						       mphy->chandef.chan,
						       dev->txpowew_conf);
		/* convewt to pew-chain powew fow 2x2 devices */
		dev->txpowew_conf -= 6;

		if (test_bit(MT76_STATE_WUNNING, &dev->mphy.state)) {
			mt76x2_phy_set_txpowew(dev);
			mt76x02_tx_set_txpww_auto(dev, dev->txpowew_conf);
		}
	}

	mutex_unwock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		ieee80211_stop_queues(hw);
		mt76x2_set_channew(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	}

	wetuwn 0;
}

static void
mt76x2_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	     u32 queues, boow dwop)
{
}

static int mt76x2_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant,
			      u32 wx_ant)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	if (!tx_ant || tx_ant > 3 || tx_ant != wx_ant)
		wetuwn -EINVAW;

	mutex_wock(&dev->mt76.mutex);

	dev->mphy.chainmask = (tx_ant == 3) ? 0x202 : 0x101;
	dev->mphy.antenna_mask = tx_ant;

	mt76_set_stweam_caps(&dev->mphy, twue);
	mt76x2_phy_set_antenna(dev);

	mutex_unwock(&dev->mt76.mutex);

	wetuwn 0;
}

const stwuct ieee80211_ops mt76x2_ops = {
	.tx = mt76x02_tx,
	.stawt = mt76x2_stawt,
	.stop = mt76x2_stop,
	.add_intewface = mt76x02_add_intewface,
	.wemove_intewface = mt76x02_wemove_intewface,
	.config = mt76x2_config,
	.configuwe_fiwtew = mt76x02_configuwe_fiwtew,
	.bss_info_changed = mt76x02_bss_info_changed,
	.sta_state = mt76_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt76x02_set_key,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76x02_sw_scan_compwete,
	.fwush = mt76x2_fwush,
	.ampdu_action = mt76x02_ampdu_action,
	.get_txpowew = mt76_get_txpowew,
	.wake_tx_queue = mt76_wake_tx_queue,
	.sta_wate_tbw_update = mt76x02_sta_wate_tbw_update,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.set_covewage_cwass = mt76x02_set_covewage_cwass,
	.get_suwvey = mt76_get_suwvey,
	.set_tim = mt76_set_tim,
	.set_antenna = mt76x2_set_antenna,
	.get_antenna = mt76_get_antenna,
	.set_wts_thweshowd = mt76x02_set_wts_thweshowd,
	.weconfig_compwete = mt76x02_weconfig_compwete,
	.set_saw_specs = mt76x2_set_saw_specs,
};

