// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude "mt76x2u.h"
#incwude "../mt76x02_usb.h"

static int mt76x2u_stawt(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	int wet;

	wet = mt76x02u_mac_stawt(dev);
	if (wet)
		wetuwn wet;

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->mphy.mac_wowk,
				     MT_MAC_WOWK_INTEWVAW);
	set_bit(MT76_STATE_WUNNING, &dev->mphy.state);

	wetuwn 0;
}

static void mt76x2u_stop(stwuct ieee80211_hw *hw)
{
	stwuct mt76x02_dev *dev = hw->pwiv;

	cweaw_bit(MT76_STATE_WUNNING, &dev->mphy.state);
	mt76u_stop_tx(&dev->mt76);
	mt76x2u_stop_hw(dev);
}

static int
mt76x2u_set_channew(stwuct mt76x02_dev *dev,
		    stwuct cfg80211_chan_def *chandef)
{
	int eww;

	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	mt76x02_pwe_tbtt_enabwe(dev, fawse);

	mutex_wock(&dev->mt76.mutex);
	set_bit(MT76_WESET, &dev->mphy.state);

	mt76_set_channew(&dev->mphy);

	mt76x2_mac_stop(dev, fawse);

	eww = mt76x2u_phy_set_channew(dev, chandef);

	mt76x02_mac_cc_weset(dev);
	mt76x2_mac_wesume(dev);

	cweaw_bit(MT76_WESET, &dev->mphy.state);
	mutex_unwock(&dev->mt76.mutex);

	mt76x02_pwe_tbtt_enabwe(dev, twue);
	mt76_txq_scheduwe_aww(&dev->mphy);

	wetuwn eww;
}

static int
mt76x2u_config(stwuct ieee80211_hw *hw, u32 changed)
{
	stwuct mt76x02_dev *dev = hw->pwiv;
	int eww = 0;

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

		if (test_bit(MT76_STATE_WUNNING, &mphy->state))
			mt76x2_phy_set_txpowew(dev);
	}

	mutex_unwock(&dev->mt76.mutex);

	if (changed & IEEE80211_CONF_CHANGE_CHANNEW) {
		ieee80211_stop_queues(hw);
		eww = mt76x2u_set_channew(dev, &hw->conf.chandef);
		ieee80211_wake_queues(hw);
	}

	wetuwn eww;
}

const stwuct ieee80211_ops mt76x2u_ops = {
	.tx = mt76x02_tx,
	.stawt = mt76x2u_stawt,
	.stop = mt76x2u_stop,
	.add_intewface = mt76x02_add_intewface,
	.wemove_intewface = mt76x02_wemove_intewface,
	.sta_state = mt76_sta_state,
	.sta_pwe_wcu_wemove = mt76_sta_pwe_wcu_wemove,
	.set_key = mt76x02_set_key,
	.ampdu_action = mt76x02_ampdu_action,
	.config = mt76x2u_config,
	.wake_tx_queue = mt76_wake_tx_queue,
	.bss_info_changed = mt76x02_bss_info_changed,
	.configuwe_fiwtew = mt76x02_configuwe_fiwtew,
	.conf_tx = mt76x02_conf_tx,
	.sw_scan_stawt = mt76_sw_scan,
	.sw_scan_compwete = mt76x02_sw_scan_compwete,
	.sta_wate_tbw_update = mt76x02_sta_wate_tbw_update,
	.get_txpowew = mt76_get_txpowew,
	.get_suwvey = mt76_get_suwvey,
	.set_tim = mt76_set_tim,
	.wewease_buffewed_fwames = mt76_wewease_buffewed_fwames,
	.get_antenna = mt76_get_antenna,
	.set_saw_specs = mt76x2_set_saw_specs,
};
