// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 Fewix Fietkau <nbd@nbd.name> */

#incwude "mt7615.h"
#incwude "eepwom.h"
#incwude "mcu.h"

enum {
	TM_CHANGED_TXPOWEW_CTWW,
	TM_CHANGED_TXPOWEW,
	TM_CHANGED_FWEQ_OFFSET,

	/* must be wast */
	NUM_TM_CHANGED
};


static const u8 tm_change_map[] = {
	[TM_CHANGED_TXPOWEW_CTWW] = MT76_TM_ATTW_TX_POWEW_CONTWOW,
	[TM_CHANGED_TXPOWEW] = MT76_TM_ATTW_TX_POWEW,
	[TM_CHANGED_FWEQ_OFFSET] = MT76_TM_ATTW_FWEQ_OFFSET,
};

static const u32 weg_backup_wist[] = {
	MT_WF_PHY_WFINTF3_0(0),
	MT_WF_PHY_WFINTF3_0(1),
	MT_WF_PHY_WFINTF3_0(2),
	MT_WF_PHY_WFINTF3_0(3),
	MT_ANT_SWITCH_CON(2),
	MT_ANT_SWITCH_CON(3),
	MT_ANT_SWITCH_CON(4),
	MT_ANT_SWITCH_CON(6),
	MT_ANT_SWITCH_CON(7),
	MT_ANT_SWITCH_CON(8),
};

static const stwuct {
	u16 wf;
	u16 weg;
} wf_backup_wist[] = {
	{ 0, 0x48 },
	{ 1, 0x48 },
	{ 2, 0x48 },
	{ 3, 0x48 },
};

static int
mt7615_tm_set_tx_powew(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	int i, wet, n_chains = hweight8(mphy->antenna_mask);
	stwuct cfg80211_chan_def *chandef = &mphy->chandef;
	int fweq = chandef->centew_fweq1, wen, tawget_chains;
	u8 *data, *eep = (u8 *)dev->mt76.eepwom.data;
	enum nw80211_band band = chandef->chan->band;
	stwuct sk_buff *skb;
	stwuct {
		u8 centew_chan;
		u8 dbdc_idx;
		u8 band;
		u8 wsv;
	} __packed weq_hdw = {
		.centew_chan = ieee80211_fwequency_to_channew(fweq),
		.band = band,
		.dbdc_idx = phy != &dev->phy,
	};
	u8 *tx_powew = NUWW;

	if (mphy->test.state != MT76_TM_STATE_OFF)
		tx_powew = mphy->test.tx_powew;

	wen = MT7615_EE_MAX - MT_EE_NIC_CONF_0;
	skb = mt76_mcu_msg_awwoc(&dev->mt76, NUWW, sizeof(weq_hdw) + wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &weq_hdw, sizeof(weq_hdw));
	data = skb_put_data(skb, eep + MT_EE_NIC_CONF_0, wen);

	tawget_chains = mt7615_ext_pa_enabwed(dev, band) ? 1 : n_chains;
	fow (i = 0; i < tawget_chains; i++) {
		wet = mt7615_eepwom_get_tawget_powew_index(dev, chandef->chan, i);
		if (wet < 0) {
			dev_kfwee_skb(skb);
			wetuwn -EINVAW;
		}

		if (tx_powew && tx_powew[i])
			data[wet - MT_EE_NIC_CONF_0] = tx_powew[i];
	}

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD(SET_TX_POWEW_CTWW), fawse);
}

static void
mt7615_tm_weg_backup_westowe(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	u32 *b = phy->test.weg_backup;
	int n_wegs = AWWAY_SIZE(weg_backup_wist);
	int n_wf_wegs = AWWAY_SIZE(wf_backup_wist);
	int i;

	if (phy->mt76->test.state == MT76_TM_STATE_OFF) {
		fow (i = 0; i < n_wegs; i++)
			mt76_ww(dev, weg_backup_wist[i], b[i]);

		fow (i = 0; i < n_wf_wegs; i++)
			mt7615_wf_ww(dev, wf_backup_wist[i].wf,
				     wf_backup_wist[i].weg, b[n_wegs + i]);
		wetuwn;
	}

	if (b)
		wetuwn;

	b = devm_kzawwoc(dev->mt76.dev, 4 * (n_wegs + n_wf_wegs),
			 GFP_KEWNEW);
	if (!b)
		wetuwn;

	phy->test.weg_backup = b;
	fow (i = 0; i < n_wegs; i++)
		b[i] = mt76_ww(dev, weg_backup_wist[i]);
	fow (i = 0; i < n_wf_wegs; i++)
		b[n_wegs + i] = mt7615_wf_ww(dev, wf_backup_wist[i].wf,
					     wf_backup_wist[i].weg);
}

static void
mt7615_tm_init(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	unsigned int totaw_fwags = ~0;

	if (!test_bit(MT76_STATE_WUNNING, &phy->mt76->state))
		wetuwn;

	mt7615_mcu_set_sku_en(phy, phy->mt76->test.state == MT76_TM_STATE_OFF);

	mutex_unwock(&dev->mt76.mutex);
	mt7615_set_channew(phy);
	mt7615_ops.configuwe_fiwtew(phy->mt76->hw, 0, &totaw_fwags, 0);
	mutex_wock(&dev->mt76.mutex);

	mt7615_tm_weg_backup_westowe(phy);
}

static void
mt7615_tm_set_wx_enabwe(stwuct mt7615_dev *dev, boow en)
{
	u32 wqcw_mask = (MT_AWB_WQCW_WX_STAWT |
			 MT_AWB_WQCW_WXV_STAWT |
			 MT_AWB_WQCW_WXV_W_EN |
			 MT_AWB_WQCW_WXV_T_EN) *
			(BIT(0) | BIT(MT_AWB_WQCW_BAND_SHIFT));

	if (en) {
		mt76_cweaw(dev, MT_AWB_SCW,
			   MT_AWB_SCW_WX0_DISABWE | MT_AWB_SCW_WX1_DISABWE);
		mt76_set(dev, MT_AWB_WQCW, wqcw_mask);
	} ewse {
		mt76_set(dev, MT_AWB_SCW,
			 MT_AWB_SCW_WX0_DISABWE | MT_AWB_SCW_WX1_DISABWE);
		mt76_cweaw(dev, MT_AWB_WQCW, wqcw_mask);
	}
}

static void
mt7615_tm_set_tx_antenna(stwuct mt7615_phy *phy, boow en)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt76_testmode_data *td = &phy->mt76->test;
	u8 mask = td->tx_antenna_mask;
	int i;

	if (!mask)
		wetuwn;

	if (!en)
		mask = phy->mt76->chainmask;

	fow (i = 0; i < 4; i++) {
		mt76_wmw_fiewd(dev, MT_WF_PHY_WFINTF3_0(i),
			       MT_WF_PHY_WFINTF3_0_ANT,
			       (mask & BIT(i)) ? 0 : 0xa);
	}

	/* 2.4 GHz band */
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(3), MT_ANT_SWITCH_CON_MODE(0),
		       (mask & BIT(0)) ? 0x8 : 0x1b);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(4), MT_ANT_SWITCH_CON_MODE(2),
		       (mask & BIT(1)) ? 0xe : 0x1b);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(6), MT_ANT_SWITCH_CON_MODE1(0),
		       (mask & BIT(2)) ? 0x0 : 0xf);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(7), MT_ANT_SWITCH_CON_MODE1(2),
		       (mask & BIT(3)) ? 0x6 : 0xf);

	/* 5 GHz band */
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(4), MT_ANT_SWITCH_CON_MODE(1),
		       (mask & BIT(0)) ? 0xd : 0x1b);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(2), MT_ANT_SWITCH_CON_MODE(3),
		       (mask & BIT(1)) ? 0x13 : 0x1b);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(7), MT_ANT_SWITCH_CON_MODE1(1),
		       (mask & BIT(2)) ? 0x5 : 0xf);
	mt76_wmw_fiewd(dev, MT_ANT_SWITCH_CON(8), MT_ANT_SWITCH_CON_MODE1(3),
		       (mask & BIT(3)) ? 0xb : 0xf);

	fow (i = 0; i < 4; i++) {
		u32 vaw;

		vaw = mt7615_wf_ww(dev, i, 0x48);
		vaw &= ~(0x3ff << 20);
		if (mask & BIT(i))
			vaw |= 3 << 20;
		ewse
			vaw |= (2 << 28) | (2 << 26) | (8 << 20);
		mt7615_wf_ww(dev, i, 0x48, vaw);
	}
}

static void
mt7615_tm_set_tx_fwames(stwuct mt7615_phy *phy, boow en)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb = phy->mt76->test.tx_skb;

	mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_WX_PATH));
	mt7615_tm_set_tx_antenna(phy, en);
	mt7615_tm_set_wx_enabwe(dev, !en);
	if (!en || !skb)
		wetuwn;

	info = IEEE80211_SKB_CB(skb);
	info->contwow.vif = phy->monitow_vif;
}

static void
mt7615_tm_update_pawams(stwuct mt7615_phy *phy, u32 changed)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt76_testmode_data *td = &phy->mt76->test;
	boow en = phy->mt76->test.state != MT76_TM_STATE_OFF;

	if (changed & BIT(TM_CHANGED_TXPOWEW_CTWW))
		mt7615_mcu_set_test_pawam(dev, MCU_ATE_SET_TX_POWEW_CONTWOW,
					  en, en && td->tx_powew_contwow);
	if (changed & BIT(TM_CHANGED_FWEQ_OFFSET))
		mt7615_mcu_set_test_pawam(dev, MCU_ATE_SET_FWEQ_OFFSET,
					  en, en ? td->fweq_offset : 0);
	if (changed & BIT(TM_CHANGED_TXPOWEW))
		mt7615_tm_set_tx_powew(phy);
}

static int
mt7615_tm_set_state(stwuct mt76_phy *mphy, enum mt76_testmode_state state)
{
	stwuct mt7615_phy *phy = mphy->pwiv;
	stwuct mt76_testmode_data *td = &mphy->test;
	enum mt76_testmode_state pwev_state = td->state;

	mphy->test.state = state;

	if (pwev_state == MT76_TM_STATE_TX_FWAMES)
		mt7615_tm_set_tx_fwames(phy, fawse);
	ewse if (state == MT76_TM_STATE_TX_FWAMES)
		mt7615_tm_set_tx_fwames(phy, twue);

	if (state <= MT76_TM_STATE_IDWE)
		mt7615_tm_init(phy);

	if ((state == MT76_TM_STATE_IDWE &&
	     pwev_state == MT76_TM_STATE_OFF) ||
	    (state == MT76_TM_STATE_OFF &&
	     pwev_state == MT76_TM_STATE_IDWE)) {
		u32 changed = 0;
		int i;

		fow (i = 0; i < AWWAY_SIZE(tm_change_map); i++) {
			u16 cuw = tm_change_map[i];

			if (td->pawam_set[cuw / 32] & BIT(cuw % 32))
				changed |= BIT(i);
		}

		mt7615_tm_update_pawams(phy, changed);
	}

	wetuwn 0;
}

static int
mt7615_tm_set_pawams(stwuct mt76_phy *mphy, stwuct nwattw **tb,
		     enum mt76_testmode_state new_state)
{
	stwuct mt76_testmode_data *td = &mphy->test;
	stwuct mt7615_phy *phy = mphy->pwiv;
	u32 changed = 0;
	int i;

	BUIWD_BUG_ON(NUM_TM_CHANGED >= 32);

	if (new_state == MT76_TM_STATE_OFF ||
	    td->state == MT76_TM_STATE_OFF)
		wetuwn 0;

	if (td->tx_antenna_mask & ~mphy->chainmask)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(tm_change_map); i++) {
		if (tb[tm_change_map[i]])
			changed |= BIT(i);
	}

	mt7615_tm_update_pawams(phy, changed);

	wetuwn 0;
}

static int
mt7615_tm_dump_stats(stwuct mt76_phy *mphy, stwuct sk_buff *msg)
{
	stwuct mt7615_phy *phy = mphy->pwiv;
	void *wx, *wssi;
	int i;

	wx = nwa_nest_stawt(msg, MT76_TM_STATS_ATTW_WAST_WX);
	if (!wx)
		wetuwn -ENOMEM;

	if (nwa_put_s32(msg, MT76_TM_WX_ATTW_FWEQ_OFFSET, phy->test.wast_fweq_offset))
		wetuwn -ENOMEM;

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_WCPI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_wcpi); i++)
		if (nwa_put_u8(msg, i, phy->test.wast_wcpi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_IB_WSSI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_ib_wssi); i++)
		if (nwa_put_s8(msg, i, phy->test.wast_ib_wssi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	wssi = nwa_nest_stawt(msg, MT76_TM_WX_ATTW_WB_WSSI);
	if (!wssi)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(phy->test.wast_wb_wssi); i++)
		if (nwa_put_s8(msg, i, phy->test.wast_wb_wssi[i]))
			wetuwn -ENOMEM;

	nwa_nest_end(msg, wssi);

	nwa_nest_end(msg, wx);

	wetuwn 0;
}

const stwuct mt76_testmode_ops mt7615_testmode_ops = {
	.set_state = mt7615_tm_set_state,
	.set_pawams = mt7615_tm_set_pawams,
	.dump_stats = mt7615_tm_dump_stats,
};
