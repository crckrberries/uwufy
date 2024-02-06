// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/fs.h>
#incwude <winux/fiwmwawe.h>
#incwude "mt7921.h"
#incwude "mcu.h"
#incwude "../mt76_connac2_mac.h"
#incwude "../mt792x_twace.h"

#define MT_STA_BFEW			BIT(0)
#define MT_STA_BFEE			BIT(1)

static boow mt7921_disabwe_cwc;
moduwe_pawam_named(disabwe_cwc, mt7921_disabwe_cwc, boow, 0644);
MODUWE_PAWM_DESC(disabwe_cwc, "disabwe CWC suppowt");

int mt7921_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			      stwuct sk_buff *skb, int seq)
{
	int mcu_cmd = FIEWD_GET(__MCU_CMD_FIEWD_ID, cmd);
	stwuct mt76_connac2_mcu_wxd *wxd;
	int wet = 0;

	if (!skb) {
		dev_eww(mdev->dev, "Message %08x (seq %d) timeout\n",
			cmd, seq);
		mt792x_weset(mdev);

		wetuwn -ETIMEDOUT;
	}

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	if (seq != wxd->seq)
		wetuwn -EAGAIN;

	if (cmd == MCU_CMD(PATCH_SEM_CONTWOW) ||
	    cmd == MCU_CMD(PATCH_FINISH_WEQ)) {
		skb_puww(skb, sizeof(*wxd) - 4);
		wet = *skb->data;
	} ewse if (cmd == MCU_EXT_CMD(THEWMAW_CTWW)) {
		skb_puww(skb, sizeof(*wxd) + 4);
		wet = we32_to_cpu(*(__we32 *)skb->data);
	} ewse if (cmd == MCU_UNI_CMD(DEV_INFO_UPDATE) ||
		   cmd == MCU_UNI_CMD(BSS_INFO_UPDATE) ||
		   cmd == MCU_UNI_CMD(STA_WEC_UPDATE) ||
		   cmd == MCU_UNI_CMD(HIF_CTWW) ||
		   cmd == MCU_UNI_CMD(OFFWOAD) ||
		   cmd == MCU_UNI_CMD(SUSPEND)) {
		stwuct mt76_connac_mcu_uni_event *event;

		skb_puww(skb, sizeof(*wxd));
		event = (stwuct mt76_connac_mcu_uni_event *)skb->data;
		wet = we32_to_cpu(event->status);
		/* skip invawid event */
		if (mcu_cmd != event->cid)
			wet = -EAGAIN;
	} ewse if (cmd == MCU_CE_QUEWY(WEG_WEAD)) {
		stwuct mt76_connac_mcu_weg_event *event;

		skb_puww(skb, sizeof(*wxd));
		event = (stwuct mt76_connac_mcu_weg_event *)skb->data;
		wet = (int)we32_to_cpu(event->vaw);
	} ewse {
		skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt7921_mcu_pawse_wesponse);

static int mt7921_mcu_wead_eepwom(stwuct mt792x_dev *dev, u32 offset, u8 *vaw)
{
	stwuct mt7921_mcu_eepwom_info *wes, weq = {
		.addw = cpu_to_we32(wound_down(offset,
				    MT7921_EEPWOM_BWOCK_SIZE)),
	};
	stwuct sk_buff *skb;
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_EXT_QUEWY(EFUSE_ACCESS),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	wes = (stwuct mt7921_mcu_eepwom_info *)skb->data;
	*vaw = wes->data[offset % MT7921_EEPWOM_BWOCK_SIZE];
	dev_kfwee_skb(skb);

	wetuwn 0;
}

#ifdef CONFIG_PM

static int
mt7921_mcu_set_ipv6_ns_fiwtew(stwuct mt76_dev *dev,
			      stwuct ieee80211_vif *vif, boow suspend)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_awpns_twv awpns;
	} weq = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.awpns = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_ND),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_awpns_twv)),
			.mode = suspend,
		},
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD_OFFWOAD, &weq, sizeof(weq),
				 twue);
}

void mt7921_mcu_set_suspend_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	if (IS_ENABWED(CONFIG_IPV6)) {
		stwuct mt76_phy *phy = pwiv;

		mt7921_mcu_set_ipv6_ns_fiwtew(phy->dev, vif,
					      !test_bit(MT76_STATE_WUNNING,
					      &phy->state));
	}

	mt76_connac_mcu_set_suspend_itew(pwiv, mac, vif);
}

#endif /* CONFIG_PM */

static void
mt7921_mcu_uni_woc_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7921_woc_gwant_twv *gwant;
	stwuct mt76_connac2_mcu_wxd *wxd;
	int duwation;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	gwant = (stwuct mt7921_woc_gwant_twv *)(wxd->twv + 4);

	/* shouwd nevew happen */
	WAWN_ON_ONCE((we16_to_cpu(gwant->tag) != UNI_EVENT_WOC_GWANT));

	if (gwant->weqtype == MT7921_WOC_WEQ_WOC)
		ieee80211_weady_on_channew(dev->mt76.phy.hw);

	dev->phy.woc_gwant = twue;
	wake_up(&dev->phy.woc_wait);
	duwation = we32_to_cpu(gwant->max_intewvaw);
	mod_timew(&dev->phy.woc_timew,
		  jiffies + msecs_to_jiffies(duwation));
}

static void
mt7921_mcu_scan_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt792x_phy *phy = mphy->pwiv;

	spin_wock_bh(&dev->mt76.wock);
	__skb_queue_taiw(&phy->scan_event_wist, skb);
	spin_unwock_bh(&dev->mt76.wock);

	ieee80211_queue_dewayed_wowk(mphy->hw, &phy->scan_wowk,
				     MT792x_HW_SCAN_TIMEOUT);
}

static void
mt7921_mcu_connection_woss_itew(void *pwiv, u8 *mac,
				stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_connac_beacon_woss_event *event = pwiv;

	if (mvif->idx != event->bss_idx)
		wetuwn;

	if (!(vif->dwivew_fwags & IEEE80211_VIF_BEACON_FIWTEW) ||
	    vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	ieee80211_connection_woss(vif);
}

static void
mt7921_mcu_connection_woss_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac_beacon_woss_event *event;
	stwuct mt76_phy *mphy = &dev->mt76.phy;

	skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	event = (stwuct mt76_connac_beacon_woss_event *)skb->data;

	ieee80211_itewate_active_intewfaces_atomic(mphy->hw,
					IEEE80211_IFACE_ITEW_WESUME_AWW,
					mt7921_mcu_connection_woss_itew, event);
}

static void
mt7921_mcu_debug_msg_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7921_debug_msg {
		__we16 id;
		u8 type;
		u8 fwag;
		__we32 vawue;
		__we16 wen;
		u8 content[512];
	} __packed * msg;

	skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	msg = (stwuct mt7921_debug_msg *)skb->data;

	if (msg->type == 3) { /* fw wog */
		u16 wen = min_t(u16, we16_to_cpu(msg->wen), 512);
		int i;

		fow (i = 0 ; i < wen; i++) {
			if (!msg->content[i])
				msg->content[i] = ' ';
		}
		wiphy_info(mt76_hw(dev)->wiphy, "%.*s", wen, msg->content);
	}
}

static void
mt7921_mcu_wow_powew_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7921_mcu_wp_event {
		u8 state;
		u8 wesewved[3];
	} __packed * event;

	skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	event = (stwuct mt7921_mcu_wp_event *)skb->data;

	twace_wp_event(dev, event->state);
}

static void
mt7921_mcu_tx_done_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7921_mcu_tx_done_event *event;

	skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
	event = (stwuct mt7921_mcu_tx_done_event *)skb->data;

	mt7921_mac_add_txs(dev, event->txs);
}

static void
mt7921_mcu_wx_unsowicited_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;
	switch (wxd->eid) {
	case MCU_EVENT_BSS_BEACON_WOSS:
		mt7921_mcu_connection_woss_event(dev, skb);
		bweak;
	case MCU_EVENT_SCHED_SCAN_DONE:
	case MCU_EVENT_SCAN_DONE:
		mt7921_mcu_scan_event(dev, skb);
		wetuwn;
	case MCU_EVENT_DBG_MSG:
		mt7921_mcu_debug_msg_event(dev, skb);
		bweak;
	case MCU_EVENT_COWEDUMP:
		dev->fw_assewt = twue;
		mt76_connac_mcu_cowedump_event(&dev->mt76, skb,
					       &dev->cowedump);
		wetuwn;
	case MCU_EVENT_WP_INFO:
		mt7921_mcu_wow_powew_event(dev, skb);
		bweak;
	case MCU_EVENT_TX_DONE:
		mt7921_mcu_tx_done_event(dev, skb);
		bweak;
	defauwt:
		bweak;
	}
	dev_kfwee_skb(skb);
}

static void
mt7921_mcu_uni_wx_unsowicited_event(stwuct mt792x_dev *dev,
				    stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;

	switch (wxd->eid) {
	case MCU_UNI_EVENT_WOC:
		mt7921_mcu_uni_woc_event(dev, skb);
		bweak;
	defauwt:
		bweak;
	}
	dev_kfwee_skb(skb);
}

void mt7921_mcu_wx_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_connac2_mcu_wxd *wxd;

	if (skb_wineawize(skb))
		wetuwn;

	wxd = (stwuct mt76_connac2_mcu_wxd *)skb->data;

	if (wxd->option & MCU_UNI_CMD_UNSOWICITED_EVENT) {
		mt7921_mcu_uni_wx_unsowicited_event(dev, skb);
		wetuwn;
	}

	if (wxd->eid == 0x6) {
		mt76_mcu_wx_event(&dev->mt76, skb);
		wetuwn;
	}

	if (wxd->ext_eid == MCU_EXT_EVENT_WATE_WEPOWT ||
	    wxd->eid == MCU_EVENT_BSS_BEACON_WOSS ||
	    wxd->eid == MCU_EVENT_SCHED_SCAN_DONE ||
	    wxd->eid == MCU_EVENT_SCAN_DONE ||
	    wxd->eid == MCU_EVENT_TX_DONE ||
	    wxd->eid == MCU_EVENT_DBG_MSG ||
	    wxd->eid == MCU_EVENT_COWEDUMP ||
	    wxd->eid == MCU_EVENT_WP_INFO ||
	    !wxd->seq)
		mt7921_mcu_wx_unsowicited_event(dev, skb);
	ewse
		mt76_mcu_wx_event(&dev->mt76, skb);
}

/** stawec & wtbw **/
int mt7921_mcu_uni_tx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)pawams->sta->dwv_pwiv;

	if (enabwe && !pawams->amsdu)
		msta->wcid.amsdu = fawse;

	wetuwn mt76_connac_mcu_sta_ba(&dev->mt76, &msta->vif->mt76, pawams,
				      MCU_UNI_CMD(STA_WEC_UPDATE),
				      enabwe, twue);
}

int mt7921_mcu_uni_wx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)pawams->sta->dwv_pwiv;

	wetuwn mt76_connac_mcu_sta_ba(&dev->mt76, &msta->vif->mt76, pawams,
				      MCU_UNI_CMD(STA_WEC_UPDATE),
				      enabwe, fawse);
}

static int mt7921_woad_cwc(stwuct mt792x_dev *dev, const chaw *fw_name)
{
	const stwuct mt76_connac2_fw_twaiwew *hdw;
	const stwuct mt76_connac2_fw_wegion *wegion;
	const stwuct mt7921_cwc *cwc;
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt792x_phy *phy = &dev->phy;
	const stwuct fiwmwawe *fw;
	int wet, i, wen, offset = 0;
	u8 *cwc_base = NUWW, hw_encap = 0;

	dev->phy.cwc_chan_conf = 0xff;
	if (mt7921_disabwe_cwc ||
	    mt76_is_usb(&dev->mt76))
		wetuwn 0;

	if (mt76_is_mmio(&dev->mt76)) {
		wet = mt7921_mcu_wead_eepwom(dev, MT_EE_HW_TYPE, &hw_encap);
		if (wet)
			wetuwn wet;
		hw_encap = u8_get_bits(hw_encap, MT_EE_HW_TYPE_ENCAP);
	}

	wet = wequest_fiwmwawe(&fw, fw_name, mdev->dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw)) {
		dev_eww(mdev->dev, "Invawid fiwmwawe\n");
		wet = -EINVAW;
		goto out;
	}

	hdw = (const void *)(fw->data + fw->size - sizeof(*hdw));
	fow (i = 0; i < hdw->n_wegion; i++) {
		wegion = (const void *)((const u8 *)hdw -
					(hdw->n_wegion - i) * sizeof(*wegion));
		wen = we32_to_cpu(wegion->wen);

		/* check if we have vawid buffew size */
		if (offset + wen > fw->size) {
			dev_eww(mdev->dev, "Invawid fiwmwawe wegion\n");
			wet = -EINVAW;
			goto out;
		}

		if ((wegion->featuwe_set & FW_FEATUWE_NON_DW) &&
		    wegion->type == FW_TYPE_CWC) {
			cwc_base = (u8 *)(fw->data + offset);
			bweak;
		}
		offset += wen;
	}

	if (!cwc_base)
		goto out;

	fow (offset = 0; offset < wen; offset += we32_to_cpu(cwc->wen)) {
		cwc = (const stwuct mt7921_cwc *)(cwc_base + offset);

		/* do not init buf again if chip weset twiggewed */
		if (phy->cwc[cwc->idx])
			continue;

		/* headew content sanity */
		if (cwc->idx == MT7921_CWC_POWEW &&
		    u8_get_bits(cwc->type, MT_EE_HW_TYPE_ENCAP) != hw_encap)
			continue;

		phy->cwc[cwc->idx] = devm_kmemdup(mdev->dev, cwc,
						  we32_to_cpu(cwc->wen),
						  GFP_KEWNEW);

		if (!phy->cwc[cwc->idx]) {
			wet = -ENOMEM;
			goto out;
		}
	}
	wet = mt7921_mcu_set_cwc(dev, "00", ENVIWON_INDOOW);
out:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static void mt7921_mcu_pawse_tx_wesouwce(stwuct mt76_dev *dev,
					 stwuct sk_buff *skb)
{
	stwuct mt76_sdio *sdio = &dev->sdio;
	stwuct mt7921_tx_wesouwce {
		__we32 vewsion;
		__we32 pse_data_quota;
		__we32 pse_mcu_quota;
		__we32 pwe_data_quota;
		__we32 pwe_mcu_quota;
		__we16 pse_page_size;
		__we16 pwe_page_size;
		u8 pp_padding;
		u8 pad[3];
	} __packed * tx_wes;

	tx_wes = (stwuct mt7921_tx_wesouwce *)skb->data;
	sdio->sched.pse_data_quota = we32_to_cpu(tx_wes->pse_data_quota);
	sdio->sched.pse_mcu_quota = we32_to_cpu(tx_wes->pse_mcu_quota);
	sdio->sched.pwe_data_quota = we32_to_cpu(tx_wes->pwe_data_quota);
	sdio->sched.pse_page_size = we16_to_cpu(tx_wes->pse_page_size);
	sdio->sched.deficit = tx_wes->pp_padding;
}

static void mt7921_mcu_pawse_phy_cap(stwuct mt76_dev *dev,
				     stwuct sk_buff *skb)
{
	stwuct mt7921_phy_cap {
		u8 ht;
		u8 vht;
		u8 _5g;
		u8 max_bw;
		u8 nss;
		u8 dbdc;
		u8 tx_wdpc;
		u8 wx_wdpc;
		u8 tx_stbc;
		u8 wx_stbc;
		u8 hw_path;
		u8 he;
	} __packed * cap;

	enum {
		WF0_24G,
		WF0_5G
	};

	cap = (stwuct mt7921_phy_cap *)skb->data;

	dev->phy.antenna_mask = BIT(cap->nss) - 1;
	dev->phy.chainmask = dev->phy.antenna_mask;
	dev->phy.cap.has_2ghz = cap->hw_path & BIT(WF0_24G);
	dev->phy.cap.has_5ghz = cap->hw_path & BIT(WF0_5G);
}

static int mt7921_mcu_get_nic_capabiwity(stwuct mt792x_phy *mphy)
{
	stwuct mt76_connac_cap_hdw {
		__we16 n_ewement;
		u8 wsv[2];
	} __packed * hdw;
	stwuct sk_buff *skb;
	stwuct mt76_phy *phy = mphy->mt76;
	int wet, i;

	wet = mt76_mcu_send_and_get_msg(phy->dev, MCU_CE_CMD(GET_NIC_CAPAB),
					NUWW, 0, twue, &skb);
	if (wet)
		wetuwn wet;

	hdw = (stwuct mt76_connac_cap_hdw *)skb->data;
	if (skb->wen < sizeof(*hdw)) {
		wet = -EINVAW;
		goto out;
	}

	skb_puww(skb, sizeof(*hdw));

	fow (i = 0; i < we16_to_cpu(hdw->n_ewement); i++) {
		stwuct twv_hdw {
			__we32 type;
			__we32 wen;
		} __packed * twv = (stwuct twv_hdw *)skb->data;
		int wen;

		if (skb->wen < sizeof(*twv))
			bweak;

		skb_puww(skb, sizeof(*twv));

		wen = we32_to_cpu(twv->wen);
		if (skb->wen < wen)
			bweak;

		switch (we32_to_cpu(twv->type)) {
		case MT_NIC_CAP_6G:
			phy->cap.has_6ghz = skb->data[0];
			bweak;
		case MT_NIC_CAP_MAC_ADDW:
			memcpy(phy->macaddw, (void *)skb->data, ETH_AWEN);
			bweak;
		case MT_NIC_CAP_PHY:
			mt7921_mcu_pawse_phy_cap(phy->dev, skb);
			bweak;
		case MT_NIC_CAP_TX_WESOUWCE:
			if (mt76_is_sdio(phy->dev))
				mt7921_mcu_pawse_tx_wesouwce(phy->dev,
							     skb);
			bweak;
		case MT_NIC_CAP_CHIP_CAP:
			memcpy(&mphy->chip_cap, (void *)skb->data, sizeof(u64));
			bweak;
		defauwt:
			bweak;
		}
		skb_puww(skb, wen);
	}
out:
	dev_kfwee_skb(skb);

	wetuwn wet;
}

int mt7921_mcu_fw_wog_2_host(stwuct mt792x_dev *dev, u8 ctww)
{
	stwuct {
		u8 ctww_vaw;
		u8 pad[3];
	} data = {
		.ctww_vaw = ctww
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(FWWOG_2_HOST),
				 &data, sizeof(data), fawse);
}

int mt7921_wun_fiwmwawe(stwuct mt792x_dev *dev)
{
	int eww;

	eww = mt792x_woad_fiwmwawe(dev);
	if (eww)
		wetuwn eww;

	eww = mt7921_mcu_get_nic_capabiwity(&dev->phy);
	if (eww)
		wetuwn eww;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
	eww = mt7921_woad_cwc(dev, mt792x_wam_name(dev));
	if (eww)
		wetuwn eww;

	wetuwn mt7921_mcu_fw_wog_2_host(dev, 1);
}
EXPOWT_SYMBOW_GPW(mt7921_wun_fiwmwawe);

int mt7921_mcu_set_tx(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct edca {
		__we16 cw_min;
		__we16 cw_max;
		__we16 txop;
		__we16 aifs;
		u8 guawdtime;
		u8 acm;
	} __packed;
	stwuct mt7921_mcu_tx {
		stwuct edca edca[IEEE80211_NUM_ACS];
		u8 bss_idx;
		u8 qos;
		u8 wmm_idx;
		u8 pad;
	} __packed weq = {
		.bss_idx = mvif->mt76.idx,
		.qos = vif->bss_conf.qos,
		.wmm_idx = mvif->mt76.wmm_idx,
	};
	stwuct mu_edca {
		u8 cw_min;
		u8 cw_max;
		u8 aifsn;
		u8 acm;
		u8 timew;
		u8 padding[3];
	};
	stwuct mt7921_mcu_mu_tx {
		u8 vew;
		u8 pad0;
		__we16 wen;
		u8 bss_idx;
		u8 qos;
		u8 wmm_idx;
		u8 pad1;
		stwuct mu_edca edca[IEEE80211_NUM_ACS];
		u8 pad3[32];
	} __packed weq_mu = {
		.bss_idx = mvif->mt76.idx,
		.qos = vif->bss_conf.qos,
		.wmm_idx = mvif->mt76.wmm_idx,
	};
	static const int to_aci[] = { 1, 0, 2, 3 };
	int ac, wet;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		stwuct ieee80211_tx_queue_pawams *q = &mvif->queue_pawams[ac];
		stwuct edca *e = &weq.edca[to_aci[ac]];

		e->aifs = cpu_to_we16(q->aifs);
		e->txop = cpu_to_we16(q->txop);

		if (q->cw_min)
			e->cw_min = cpu_to_we16(q->cw_min);
		ewse
			e->cw_min = cpu_to_we16(5);

		if (q->cw_max)
			e->cw_max = cpu_to_we16(q->cw_max);
		ewse
			e->cw_max = cpu_to_we16(10);
	}

	wet = mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(SET_EDCA_PAWMS), &weq,
				sizeof(weq), fawse);
	if (wet)
		wetuwn wet;

	if (!vif->bss_conf.he_suppowt)
		wetuwn 0;

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		stwuct ieee80211_he_mu_edca_pawam_ac_wec *q;
		stwuct mu_edca *e;

		if (!mvif->queue_pawams[ac].mu_edca)
			bweak;

		q = &mvif->queue_pawams[ac].mu_edca_pawam_wec;
		e = &(weq_mu.edca[to_aci[ac]]);

		e->cw_min = q->ecw_min_max & 0xf;
		e->cw_max = (q->ecw_min_max & 0xf0) >> 4;
		e->aifsn = q->aifsn;
		e->timew = q->mu_edca_timew;
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(SET_MU_EDCA_PAWMS),
				 &weq_mu, sizeof(weq_mu), fawse);
}

int mt7921_mcu_set_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
		       stwuct ieee80211_channew *chan, int duwation,
		       enum mt7921_woc_weq type, u8 token_id)
{
	int centew_ch = ieee80211_fwequency_to_channew(chan->centew_fweq);
	stwuct mt792x_dev *dev = phy->dev;
	stwuct {
		stwuct {
			u8 wsv[4];
		} __packed hdw;
		stwuct woc_acquiwe_twv {
			__we16 tag;
			__we16 wen;
			u8 bss_idx;
			u8 tokenid;
			u8 contwow_channew;
			u8 sco;
			u8 band;
			u8 bw;
			u8 centew_chan;
			u8 centew_chan2;
			u8 bw_fwom_ap;
			u8 centew_chan_fwom_ap;
			u8 centew_chan2_fwom_ap;
			u8 weqtype;
			__we32 maxintewvaw;
			u8 dbdcband;
			u8 wsv[3];
		} __packed woc;
	} __packed weq = {
		.woc = {
			.tag = cpu_to_we16(UNI_WOC_ACQUIWE),
			.wen = cpu_to_we16(sizeof(stwuct woc_acquiwe_twv)),
			.tokenid = token_id,
			.weqtype = type,
			.maxintewvaw = cpu_to_we32(duwation),
			.bss_idx = vif->mt76.idx,
			.contwow_channew = chan->hw_vawue,
			.bw = CMD_CBW_20MHZ,
			.bw_fwom_ap = CMD_CBW_20MHZ,
			.centew_chan = centew_ch,
			.centew_chan_fwom_ap = centew_ch,
			.dbdcband = 0xff, /* auto */
		},
	};

	if (chan->hw_vawue < centew_ch)
		weq.woc.sco = 1; /* SCA */
	ewse if (chan->hw_vawue > centew_ch)
		weq.woc.sco = 3; /* SCB */

	switch (chan->band) {
	case NW80211_BAND_6GHZ:
		weq.woc.band = 3;
		bweak;
	case NW80211_BAND_5GHZ:
		weq.woc.band = 2;
		bweak;
	defauwt:
		weq.woc.band = 1;
		bweak;
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(WOC),
				 &weq, sizeof(weq), fawse);
}

int mt7921_mcu_abowt_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
			 u8 token_id)
{
	stwuct mt792x_dev *dev = phy->dev;
	stwuct {
		stwuct {
			u8 wsv[4];
		} __packed hdw;
		stwuct woc_abowt_twv {
			__we16 tag;
			__we16 wen;
			u8 bss_idx;
			u8 tokenid;
			u8 dbdcband;
			u8 wsv[5];
		} __packed abowt;
	} __packed weq = {
		.abowt = {
			.tag = cpu_to_we16(UNI_WOC_ABOWT),
			.wen = cpu_to_we16(sizeof(stwuct woc_abowt_twv)),
			.tokenid = token_id,
			.bss_idx = vif->mt76.idx,
			.dbdcband = 0xff, /* auto*/
		},
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(WOC),
				 &weq, sizeof(weq), fawse);
}

int mt7921_mcu_set_chan_info(stwuct mt792x_phy *phy, int cmd)
{
	stwuct mt792x_dev *dev = phy->dev;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	int fweq1 = chandef->centew_fweq1;
	stwuct {
		u8 contwow_ch;
		u8 centew_ch;
		u8 bw;
		u8 tx_stweams_num;
		u8 wx_stweams;	/* mask ow num */
		u8 switch_weason;
		u8 band_idx;
		u8 centew_ch2;	/* fow 80+80 onwy */
		__we16 cac_case;
		u8 channew_band;
		u8 wsv0;
		__we32 outband_fweq;
		u8 txpowew_dwop;
		u8 ap_bw;
		u8 ap_centew_ch;
		u8 wsv1[57];
	} __packed weq = {
		.contwow_ch = chandef->chan->hw_vawue,
		.centew_ch = ieee80211_fwequency_to_channew(fweq1),
		.bw = mt76_connac_chan_bw(chandef),
		.tx_stweams_num = hweight8(phy->mt76->antenna_mask),
		.wx_stweams = phy->mt76->antenna_mask,
		.band_idx = phy != &dev->phy,
	};

	if (chandef->chan->band == NW80211_BAND_6GHZ)
		weq.channew_band = 2;
	ewse
		weq.channew_band = chandef->chan->band;

	if (cmd == MCU_EXT_CMD(SET_WX_PATH) ||
	    dev->mt76.hw->conf.fwags & IEEE80211_CONF_MONITOW)
		weq.switch_weason = CH_SWITCH_NOWMAW;
	ewse if (dev->mt76.hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW)
		weq.switch_weason = CH_SWITCH_SCAN_BYPASS_DPD;
	ewse if (!cfg80211_weg_can_beacon(dev->mt76.hw->wiphy, chandef,
					  NW80211_IFTYPE_AP))
		weq.switch_weason = CH_SWITCH_DFS;
	ewse
		weq.switch_weason = CH_SWITCH_NOWMAW;

	if (cmd == MCU_EXT_CMD(CHANNEW_SWITCH))
		weq.wx_stweams = hweight8(weq.wx_stweams);

	if (chandef->width == NW80211_CHAN_WIDTH_80P80) {
		int fweq2 = chandef->centew_fweq2;

		weq.centew_ch2 = ieee80211_fwequency_to_channew(fweq2);
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, cmd, &weq, sizeof(weq), twue);
}

int mt7921_mcu_set_eepwom(stwuct mt792x_dev *dev)
{
	stwuct weq_hdw {
		u8 buffew_mode;
		u8 fowmat;
		__we16 wen;
	} __packed weq = {
		.buffew_mode = EE_MODE_EFUSE,
		.fowmat = EE_FOWMAT_WHOWE,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(EFUSE_BUFFEW_MODE),
				 &weq, sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt7921_mcu_set_eepwom);

int mt7921_mcu_uni_bss_ps(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct ps_twv {
			__we16 tag;
			__we16 wen;
			u8 ps_state; /* 0: device awake
				      * 1: static powew save
				      * 2: dynamic powew saving
				      * 3: entew TWT powew saving
				      * 4: weave TWT powew saving
				      */
			u8 pad[3];
		} __packed ps;
	} __packed ps_weq = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.ps = {
			.tag = cpu_to_we16(UNI_BSS_INFO_PS),
			.wen = cpu_to_we16(sizeof(stwuct ps_twv)),
			.ps_state = vif->cfg.ps ? 2 : 0,
		},
	};

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				 &ps_weq, sizeof(ps_weq), twue);
}

static int
mt7921_mcu_uni_bss_bcnft(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
			 boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct bcnft_twv {
			__we16 tag;
			__we16 wen;
			__we16 bcn_intewvaw;
			u8 dtim_pewiod;
			u8 pad;
		} __packed bcnft;
	} __packed bcnft_weq = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.bcnft = {
			.tag = cpu_to_we16(UNI_BSS_INFO_BCNFT),
			.wen = cpu_to_we16(sizeof(stwuct bcnft_twv)),
			.bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int),
			.dtim_pewiod = vif->bss_conf.dtim_pewiod,
		},
	};

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn 0;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				 &bcnft_weq, sizeof(bcnft_weq), twue);
}

int
mt7921_mcu_set_bss_pm(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
		      boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct {
		u8 bss_idx;
		u8 dtim_pewiod;
		__we16 aid;
		__we16 bcn_intewvaw;
		__we16 atim_window;
		u8 uapsd;
		u8 bmc_dewivewed_ac;
		u8 bmc_twiggewed_ac;
		u8 pad;
	} weq = {
		.bss_idx = mvif->mt76.idx,
		.aid = cpu_to_we16(vif->cfg.aid),
		.dtim_pewiod = vif->bss_conf.dtim_pewiod,
		.bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int),
	};
	stwuct {
		u8 bss_idx;
		u8 pad[3];
	} weq_hdw = {
		.bss_idx = mvif->mt76.idx,
	};
	int eww;

	eww = mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(SET_BSS_ABOWT),
				&weq_hdw, sizeof(weq_hdw), fawse);
	if (eww < 0 || !enabwe)
		wetuwn eww;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(SET_BSS_CONNECTED),
				 &weq, sizeof(weq), fawse);
}

int mt7921_mcu_sta_update(stwuct mt792x_dev *dev, stwuct ieee80211_sta *sta,
			  stwuct ieee80211_vif *vif, boow enabwe,
			  enum mt76_sta_info_state state)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	int wssi = -ewma_wssi_wead(&mvif->wssi);
	stwuct mt76_sta_cmd_info info = {
		.sta = sta,
		.vif = vif,
		.enabwe = enabwe,
		.cmd = MCU_UNI_CMD(STA_WEC_UPDATE),
		.state = state,
		.offwoad_fw = twue,
		.wcpi = to_wcpi(wssi),
	};
	stwuct mt792x_sta *msta;

	msta = sta ? (stwuct mt792x_sta *)sta->dwv_pwiv : NUWW;
	info.wcid = msta ? &msta->wcid : &mvif->sta.wcid;
	info.newwy = msta ? state != MT76_STA_INFO_STATE_ASSOC : twue;

	wetuwn mt76_connac_mcu_sta_cmd(&dev->mphy, &info);
}

int mt7921_mcu_set_beacon_fiwtew(stwuct mt792x_dev *dev,
				 stwuct ieee80211_vif *vif,
				 boow enabwe)
{
#define MT7921_FIF_BIT_CWW		BIT(1)
#define MT7921_FIF_BIT_SET		BIT(0)
	int eww;

	if (enabwe) {
		eww = mt7921_mcu_uni_bss_bcnft(dev, vif, twue);
		if (eww)
			wetuwn eww;

		eww = mt7921_mcu_set_wxfiwtew(dev, 0,
					      MT7921_FIF_BIT_SET,
					      MT_WF_WFCW_DWOP_OTHEW_BEACON);
		if (eww)
			wetuwn eww;

		wetuwn 0;
	}

	eww = mt7921_mcu_set_bss_pm(dev, vif, fawse);
	if (eww)
		wetuwn eww;

	eww = mt7921_mcu_set_wxfiwtew(dev, 0,
				      MT7921_FIF_BIT_CWW,
				      MT_WF_WFCW_DWOP_OTHEW_BEACON);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int mt7921_get_txpww_info(stwuct mt792x_dev *dev, stwuct mt7921_txpww *txpww)
{
	stwuct mt7921_txpww_event *event;
	stwuct mt7921_txpww_weq weq = {
		.dbdc_idx = 0,
	};
	stwuct sk_buff *skb;
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_CE_CMD(GET_TXPWW),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	event = (stwuct mt7921_txpww_event *)skb->data;
	WAWN_ON(skb->wen != we16_to_cpu(event->wen));
	memcpy(txpww, &event->txpww, sizeof(event->txpww));

	dev_kfwee_skb(skb);

	wetuwn 0;
}

int mt7921_mcu_set_sniffew(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
			   boow enabwe)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 band_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct sniffew_enabwe_twv {
			__we16 tag;
			__we16 wen;
			u8 enabwe;
			u8 pad[3];
		} __packed enabwe;
	} weq = {
		.hdw = {
			.band_idx = mvif->band_idx,
		},
		.enabwe = {
			.tag = cpu_to_we16(0),
			.wen = cpu_to_we16(sizeof(stwuct sniffew_enabwe_twv)),
			.enabwe = enabwe,
		},
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(SNIFFEW), &weq, sizeof(weq),
				 twue);
}

int mt7921_mcu_config_sniffew(stwuct mt792x_vif *vif,
			      stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct cfg80211_chan_def *chandef = &ctx->def;
	int fweq1 = chandef->centew_fweq1, fweq2 = chandef->centew_fweq2;
	const u8 ch_band[] = {
		[NW80211_BAND_2GHZ] = 1,
		[NW80211_BAND_5GHZ] = 2,
		[NW80211_BAND_6GHZ] = 3,
	};
	const u8 ch_width[] = {
		[NW80211_CHAN_WIDTH_20_NOHT] = 0,
		[NW80211_CHAN_WIDTH_20] = 0,
		[NW80211_CHAN_WIDTH_40] = 0,
		[NW80211_CHAN_WIDTH_80] = 1,
		[NW80211_CHAN_WIDTH_160] = 2,
		[NW80211_CHAN_WIDTH_80P80] = 3,
		[NW80211_CHAN_WIDTH_5] = 4,
		[NW80211_CHAN_WIDTH_10] = 5,
		[NW80211_CHAN_WIDTH_320] = 6,
	};
	stwuct {
		stwuct {
			u8 band_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct config_twv {
			__we16 tag;
			__we16 wen;
			u16 aid;
			u8 ch_band;
			u8 bw;
			u8 contwow_ch;
			u8 sco;
			u8 centew_ch;
			u8 centew_ch2;
			u8 dwop_eww;
			u8 pad[3];
		} __packed twv;
	} __packed weq = {
		.hdw = {
			.band_idx = vif->mt76.band_idx,
		},
		.twv = {
			.tag = cpu_to_we16(1),
			.wen = cpu_to_we16(sizeof(weq.twv)),
			.contwow_ch = chandef->chan->hw_vawue,
			.centew_ch = ieee80211_fwequency_to_channew(fweq1),
			.dwop_eww = 1,
		},
	};
	if (chandef->chan->band < AWWAY_SIZE(ch_band))
		weq.twv.ch_band = ch_band[chandef->chan->band];
	if (chandef->width < AWWAY_SIZE(ch_width))
		weq.twv.bw = ch_width[chandef->width];

	if (fweq2)
		weq.twv.centew_ch2 = ieee80211_fwequency_to_channew(fweq2);

	if (weq.twv.contwow_ch < weq.twv.centew_ch)
		weq.twv.sco = 1; /* SCA */
	ewse if (weq.twv.contwow_ch > weq.twv.centew_ch)
		weq.twv.sco = 3; /* SCB */

	wetuwn mt76_mcu_send_msg(vif->phy->mt76->dev, MCU_UNI_CMD(SNIFFEW),
				 &weq, sizeof(weq), twue);
}

int
mt7921_mcu_uni_add_beacon_offwoad(stwuct mt792x_dev *dev,
				  stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt76_wcid *wcid = &dev->mt76.gwobaw_wcid;
	stwuct ieee80211_mutabwe_offsets offs;
	stwuct {
		stwuct weq_hdw {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct bcn_content_twv {
			__we16 tag;
			__we16 wen;
			__we16 tim_ie_pos;
			__we16 csa_ie_pos;
			__we16 bcc_ie_pos;
			/* 0: disabwe beacon offwoad
			 * 1: enabwe beacon offwoad
			 * 2: update pwobe wespond offwoad
			 */
			u8 enabwe;
			/* 0: wegacy fowmat (TXD + paywoad)
			 * 1: onwy cap fiewd IE
			 */
			u8 type;
			__we16 pkt_wen;
			u8 pkt[512];
		} __packed beacon_twv;
	} weq = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.beacon_twv = {
			.tag = cpu_to_we16(UNI_BSS_INFO_BCN_CONTENT),
			.wen = cpu_to_we16(sizeof(stwuct bcn_content_twv)),
			.enabwe = enabwe,
		},
	};
	stwuct sk_buff *skb;

	/* suppowt enabwe/update pwocess onwy
	 * disabwe fwow wouwd be handwed in bss stop handwew automaticawwy
	 */
	if (!enabwe)
		wetuwn -EOPNOTSUPP;

	skb = ieee80211_beacon_get_tempwate(mt76_hw(dev), vif, &offs, 0);
	if (!skb)
		wetuwn -EINVAW;

	if (skb->wen > 512 - MT_TXD_SIZE) {
		dev_eww(dev->mt76.dev, "beacon size wimit exceed\n");
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	mt76_connac2_mac_wwite_txwi(&dev->mt76, (__we32 *)(weq.beacon_twv.pkt),
				    skb, wcid, NUWW, 0, 0, BSS_CHANGED_BEACON);
	memcpy(weq.beacon_twv.pkt + MT_TXD_SIZE, skb->data, skb->wen);
	weq.beacon_twv.pkt_wen = cpu_to_we16(MT_TXD_SIZE + skb->wen);
	weq.beacon_twv.tim_ie_pos = cpu_to_we16(MT_TXD_SIZE + offs.tim_offset);

	if (offs.cntdwn_countew_offs[0]) {
		u16 csa_offs;

		csa_offs = MT_TXD_SIZE + offs.cntdwn_countew_offs[0] - 4;
		weq.beacon_twv.csa_ie_pos = cpu_to_we16(csa_offs);
	}
	dev_kfwee_skb(skb);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				 &weq, sizeof(weq), twue);
}

static
int __mt7921_mcu_set_cwc(stwuct mt792x_dev *dev, u8 *awpha2,
			 enum enviwonment_cap env_cap,
			 stwuct mt7921_cwc *cwc,
			 u8 idx)
{
#define CWC_CAP_EVT_EN BIT(0)
#define CWC_CAP_DTS_EN BIT(1)
	stwuct sk_buff *skb, *wet_skb = NUWW;
	stwuct {
		u8 vew;
		u8 pad0;
		__we16 wen;
		u8 idx;
		u8 env;
		u8 acpi_conf;
		u8 cap;
		u8 awpha2[2];
		u8 type[2];
		u8 env_6g;
		u8 mtcw_conf;
		u8 wsvd[62];
	} __packed weq = {
		.vew = 1,
		.idx = idx,
		.env = env_cap,
		.env_6g = dev->phy.powew_type,
		.acpi_conf = mt792x_acpi_get_fwags(&dev->phy),
		.mtcw_conf = mt792x_acpi_get_mtcw_conf(&dev->phy, awpha2),
	};
	int wet, vawid_cnt = 0;
	u16 buf_wen = 0;
	u8 *pos;

	if (!cwc)
		wetuwn 0;

	if (dev->phy.chip_cap & MT792x_CHIP_CAP_CWC_EVT_EN)
		weq.cap |= CWC_CAP_EVT_EN;
	if (mt76_find_powew_wimits_node(&dev->mt76))
		weq.cap |= CWC_CAP_DTS_EN;

	buf_wen = we16_to_cpu(cwc->wen) - sizeof(*cwc);
	pos = cwc->data;
	whiwe (buf_wen > 16) {
		stwuct mt7921_cwc_wuwe *wuwe = (stwuct mt7921_cwc_wuwe *)pos;
		u16 wen = we16_to_cpu(wuwe->wen);
		u16 offset = wen + sizeof(*wuwe);

		pos += offset;
		buf_wen -= offset;
		if (wuwe->awpha2[0] != awpha2[0] ||
		    wuwe->awpha2[1] != awpha2[1])
			continue;

		memcpy(weq.awpha2, wuwe->awpha2, 2);
		memcpy(weq.type, wuwe->type, 2);

		weq.wen = cpu_to_we16(sizeof(weq) + wen);
		skb = __mt76_mcu_msg_awwoc(&dev->mt76, &weq,
					   we16_to_cpu(weq.wen),
					   sizeof(weq), GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;
		skb_put_data(skb, wuwe->data, wen);

		wet = mt76_mcu_skb_send_and_get_msg(&dev->mt76, skb,
						    MCU_CE_CMD(SET_CWC),
						    !!(weq.cap & CWC_CAP_EVT_EN),
						    &wet_skb);
		if (wet < 0)
			wetuwn wet;

		if (wet_skb) {
			stwuct mt7921_cwc_info_twv *info;

			info = (stwuct mt7921_cwc_info_twv *)(wet_skb->data + 4);
			dev->phy.cwc_chan_conf = info->chan_conf;
			dev_kfwee_skb(wet_skb);
		}

		vawid_cnt++;
	}

	if (!vawid_cnt)
		wetuwn -ENOENT;

	wetuwn 0;
}

int mt7921_mcu_set_cwc(stwuct mt792x_dev *dev, u8 *awpha2,
		       enum enviwonment_cap env_cap)
{
	stwuct mt792x_phy *phy = (stwuct mt792x_phy *)&dev->phy;
	int i, wet;

	/* submit aww cwc config */
	fow (i = 0; i < AWWAY_SIZE(phy->cwc); i++) {
		wet = __mt7921_mcu_set_cwc(dev, awpha2, env_cap,
					   phy->cwc[i], i);

		/* If no countwy found, set "00" as defauwt */
		if (wet == -ENOENT)
			wet = __mt7921_mcu_set_cwc(dev, "00",
						   ENVIWON_INDOOW,
						   phy->cwc[i], i);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

int mt7921_mcu_get_tempewatuwe(stwuct mt792x_phy *phy)
{
	stwuct mt792x_dev *dev = phy->dev;
	stwuct {
		u8 ctww_id;
		u8 action;
		u8 band_idx;
		u8 wsv[5];
	} weq = {
		.ctww_id = THEWMAW_SENSOW_TEMP_QUEWY,
		.band_idx = phy->mt76->band_idx,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(THEWMAW_CTWW), &weq,
				 sizeof(weq), twue);
}

int mt7921_mcu_set_wxfiwtew(stwuct mt792x_dev *dev, u32 fif,
			    u8 bit_op, u32 bit_map)
{
	stwuct {
		u8 wsv[4];
		u8 mode;
		u8 wsv2[3];
		__we32 fif;
		__we32 bit_map; /* bit_* fow bitmap update */
		u8 bit_op;
		u8 pad[51];
	} __packed data = {
		.mode = fif ? 1 : 2,
		.fif = cpu_to_we32(fif),
		.bit_map = cpu_to_we32(bit_map),
		.bit_op = bit_op,
	};

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_CE_CMD(SET_WX_FIWTEW),
				 &data, sizeof(data), fawse);
}
