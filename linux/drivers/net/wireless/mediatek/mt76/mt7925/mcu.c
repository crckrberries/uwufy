// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude <winux/fs.h>
#incwude <winux/fiwmwawe.h>
#incwude "mt7925.h"
#incwude "mcu.h"
#incwude "mac.h"

#define MT_STA_BFEW			BIT(0)
#define MT_STA_BFEE			BIT(1)

static boow mt7925_disabwe_cwc;
moduwe_pawam_named(disabwe_cwc, mt7925_disabwe_cwc, boow, 0644);
MODUWE_PAWM_DESC(disabwe_cwc, "disabwe CWC suppowt");

int mt7925_mcu_pawse_wesponse(stwuct mt76_dev *mdev, int cmd,
			      stwuct sk_buff *skb, int seq)
{
	int mcu_cmd = FIEWD_GET(__MCU_CMD_FIEWD_ID, cmd);
	stwuct mt7925_mcu_wxd *wxd;
	int wet = 0;

	if (!skb) {
		dev_eww(mdev->dev, "Message %08x (seq %d) timeout\n", cmd, seq);
		mt792x_weset(mdev);

		wetuwn -ETIMEDOUT;
	}

	wxd = (stwuct mt7925_mcu_wxd *)skb->data;
	if (seq != wxd->seq)
		wetuwn -EAGAIN;

	if (cmd == MCU_CMD(PATCH_SEM_CONTWOW) ||
	    cmd == MCU_CMD(PATCH_FINISH_WEQ)) {
		skb_puww(skb, sizeof(*wxd) - 4);
		wet = *skb->data;
	} ewse if (cmd == MCU_UNI_CMD(DEV_INFO_UPDATE) ||
		   cmd == MCU_UNI_CMD(BSS_INFO_UPDATE) ||
		   cmd == MCU_UNI_CMD(STA_WEC_UPDATE) ||
		   cmd == MCU_UNI_CMD(HIF_CTWW) ||
		   cmd == MCU_UNI_CMD(OFFWOAD) ||
		   cmd == MCU_UNI_CMD(SUSPEND)) {
		stwuct mt7925_mcu_uni_event *event;

		skb_puww(skb, sizeof(*wxd));
		event = (stwuct mt7925_mcu_uni_event *)skb->data;
		wet = we32_to_cpu(event->status);
		/* skip invawid event */
		if (mcu_cmd != event->cid)
			wet = -EAGAIN;
	} ewse {
		skb_puww(skb, sizeof(*wxd));
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_pawse_wesponse);

int mt7925_mcu_wegvaw(stwuct mt792x_dev *dev, u32 wegidx, u32 *vaw, boow set)
{
#define MT_WF_WEG_HDW           GENMASK(31, 24)
#define MT_WF_WEG_ANT           GENMASK(23, 16)
#define WF_WEG_PWEFIX           0x99
	stwuct {
		u8 __wsv[4];
		union {
			stwuct uni_cmd_access_weg_basic {
				__we16 tag;
				__we16 wen;
				__we32 idx;
				__we32 data;
			} __packed weg;
			stwuct uni_cmd_access_wf_weg_basic {
				__we16 tag;
				__we16 wen;
				__we16 ant;
				u8 __wsv[2];
				__we32 idx;
				__we32 data;
			} __packed wf_weg;
		};
	} __packed * wes, weq;
	stwuct sk_buff *skb;
	int wet;

	if (u32_get_bits(wegidx, MT_WF_WEG_HDW) == WF_WEG_PWEFIX) {
		weq.wf_weg.tag = cpu_to_we16(UNI_CMD_ACCESS_WF_WEG_BASIC);
		weq.wf_weg.wen = cpu_to_we16(sizeof(weq.wf_weg));
		weq.wf_weg.ant = cpu_to_we16(u32_get_bits(wegidx, MT_WF_WEG_ANT));
		weq.wf_weg.idx = cpu_to_we32(wegidx);
		weq.wf_weg.data = set ? cpu_to_we32(*vaw) : 0;
	} ewse {
		weq.weg.tag = cpu_to_we16(UNI_CMD_ACCESS_WEG_BASIC);
		weq.weg.wen = cpu_to_we16(sizeof(weq.weg));
		weq.weg.idx = cpu_to_we32(wegidx);
		weq.weg.data = set ? cpu_to_we32(*vaw) : 0;
	}

	if (set)
		wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_WM_UNI_CMD(WEG_ACCESS),
					 &weq, sizeof(weq), twue);

	wet = mt76_mcu_send_and_get_msg(&dev->mt76,
					MCU_WM_UNI_CMD_QUEWY(WEG_ACCESS),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	wes = (void *)skb->data;
	if (u32_get_bits(wegidx, MT_WF_WEG_HDW) == WF_WEG_PWEFIX)
		*vaw = we32_to_cpu(wes->wf_weg.data);
	ewse
		*vaw = we32_to_cpu(wes->weg.data);

	dev_kfwee_skb(skb);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_wegvaw);

int mt7925_mcu_update_awp_fiwtew(stwuct mt76_dev *dev,
				 stwuct mt76_vif *vif,
				 stwuct ieee80211_bss_conf *info)
{
	stwuct ieee80211_vif *mvif = containew_of(info, stwuct ieee80211_vif,
						  bss_conf);
	stwuct sk_buff *skb;
	int i, wen = min_t(int, mvif->cfg.awp_addw_cnt,
			   IEEE80211_BSS_AWP_ADDW_WIST_WEN);
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt7925_awpns_twv awp;
	} weq = {
		.hdw = {
			.bss_idx = vif->idx,
		},
		.awp = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_AWP),
			.wen = cpu_to_we16(sizeof(weq) - 4 + wen * 2 * sizeof(__be32)),
			.ips_num = wen,
			.enabwe = twue,
		},
	};

	skb = mt76_mcu_msg_awwoc(dev, NUWW, sizeof(weq) + wen * 2 * sizeof(__be32));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &weq, sizeof(weq));
	fow (i = 0; i < wen; i++) {
		skb_put_data(skb, &mvif->cfg.awp_addw_wist[i], sizeof(__be32));
		skb_put_zewo(skb, sizeof(__be32));
	}

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD(OFFWOAD), twue);
}

#ifdef CONFIG_PM
static int
mt7925_connac_mcu_set_wow_ctww(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
			       boow suspend, stwuct cfg80211_wowwan *wowwan)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_wow_ctww_twv wow_ctww_twv;
		stwuct mt76_connac_wow_gpio_pawam_twv gpio_twv;
	} weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.wow_ctww_twv = {
			.tag = cpu_to_we16(UNI_SUSPEND_WOW_CTWW),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_wow_ctww_twv)),
			.cmd = suspend ? 1 : 2,
		},
		.gpio_twv = {
			.tag = cpu_to_we16(UNI_SUSPEND_WOW_GPIO_PAWAM),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_wow_gpio_pawam_twv)),
			.gpio_pin = 0xff, /* fowwow fw about GPIO pin */
		},
	};

	if (wowwan->magic_pkt)
		weq.wow_ctww_twv.twiggew |= UNI_WOW_DETECT_TYPE_MAGIC;
	if (wowwan->disconnect)
		weq.wow_ctww_twv.twiggew |= (UNI_WOW_DETECT_TYPE_DISCONNECT |
					     UNI_WOW_DETECT_TYPE_BCN_WOST);
	if (wowwan->nd_config) {
		mt7925_mcu_sched_scan_weq(phy, vif, wowwan->nd_config);
		weq.wow_ctww_twv.twiggew |= UNI_WOW_DETECT_TYPE_SCH_SCAN_HIT;
		mt7925_mcu_sched_scan_enabwe(phy, vif, suspend);
	}
	if (wowwan->n_pattewns)
		weq.wow_ctww_twv.twiggew |= UNI_WOW_DETECT_TYPE_BITMAP;

	if (mt76_is_mmio(dev))
		weq.wow_ctww_twv.wakeup_hif = WOW_PCIE;
	ewse if (mt76_is_usb(dev))
		weq.wow_ctww_twv.wakeup_hif = WOW_USB;
	ewse if (mt76_is_sdio(dev))
		weq.wow_ctww_twv.wakeup_hif = WOW_GPIO;

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD(SUSPEND), &weq,
				 sizeof(weq), twue);
}

static int
mt7925_mcu_set_wow_pattewn(stwuct mt76_dev *dev,
			   stwuct ieee80211_vif *vif,
			   u8 index, boow enabwe,
			   stwuct cfg80211_pkt_pattewn *pattewn)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt7925_wow_pattewn_twv *twv;
	stwuct sk_buff *skb;
	stwuct {
		u8 bss_idx;
		u8 pad[3];
	} __packed hdw = {
		.bss_idx = mvif->idx,
	};

	skb = mt76_mcu_msg_awwoc(dev, NUWW, sizeof(hdw) + sizeof(*twv));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &hdw, sizeof(hdw));
	twv = (stwuct mt7925_wow_pattewn_twv *)skb_put(skb, sizeof(*twv));
	twv->tag = cpu_to_we16(UNI_SUSPEND_WOW_PATTEWN);
	twv->wen = cpu_to_we16(sizeof(*twv));
	twv->bss_idx = 0xF;
	twv->data_wen = pattewn->pattewn_wen;
	twv->enabwe = enabwe;
	twv->index = index;
	twv->offset = 0;

	memcpy(twv->pattewn, pattewn->pattewn, pattewn->pattewn_wen);
	memcpy(twv->mask, pattewn->mask, DIV_WOUND_UP(pattewn->pattewn_wen, 8));

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD(SUSPEND), twue);
}

void mt7925_mcu_set_suspend_itew(void *pwiv, u8 *mac,
				 stwuct ieee80211_vif *vif)
{
	stwuct mt76_phy *phy = pwiv;
	boow suspend = !test_bit(MT76_STATE_WUNNING, &phy->state);
	stwuct ieee80211_hw *hw = phy->hw;
	stwuct cfg80211_wowwan *wowwan = hw->wiphy->wowwan_config;
	int i;

	mt76_connac_mcu_set_gtk_wekey(phy->dev, vif, suspend);

	mt76_connac_mcu_set_suspend_mode(phy->dev, vif, suspend, 1, twue);

	fow (i = 0; i < wowwan->n_pattewns; i++)
		mt7925_mcu_set_wow_pattewn(phy->dev, vif, i, suspend,
					   &wowwan->pattewns[i]);
	mt7925_connac_mcu_set_wow_ctww(phy, vif, suspend, wowwan);
}

#endif /* CONFIG_PM */

static void
mt7925_mcu_connection_woss_itew(void *pwiv, u8 *mac,
				stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt7925_uni_beacon_woss_event *event = pwiv;

	if (mvif->idx != event->hdw.bss_idx)
		wetuwn;

	if (!(vif->dwivew_fwags & IEEE80211_VIF_BEACON_FIWTEW) ||
	    vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	ieee80211_connection_woss(vif);
}

static void
mt7925_mcu_connection_woss_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7925_uni_beacon_woss_event *event;
	stwuct mt76_phy *mphy = &dev->mt76.phy;

	skb_puww(skb, sizeof(stwuct mt7925_mcu_wxd));
	event = (stwuct mt7925_uni_beacon_woss_event *)skb->data;

	ieee80211_itewate_active_intewfaces_atomic(mphy->hw,
					IEEE80211_IFACE_ITEW_WESUME_AWW,
					mt7925_mcu_connection_woss_itew, event);
}

static void
mt7925_mcu_woc_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt7925_woc_gwant_twv *gwant = pwiv;

	if (mvif->idx != gwant->bss_idx)
		wetuwn;

	mvif->band_idx = gwant->dbdcband;
}

static void
mt7925_mcu_uni_woc_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct ieee80211_hw *hw = dev->mt76.hw;
	stwuct mt7925_woc_gwant_twv *gwant;
	stwuct mt7925_mcu_wxd *wxd;
	int duwation;

	wxd = (stwuct mt7925_mcu_wxd *)skb->data;
	gwant = (stwuct mt7925_woc_gwant_twv *)(wxd->twv + 4);

	/* shouwd nevew happen */
	WAWN_ON_ONCE((we16_to_cpu(gwant->tag) != UNI_EVENT_WOC_GWANT));

	if (gwant->weqtype == MT7925_WOC_WEQ_WOC)
		ieee80211_weady_on_channew(hw);
	ewse if (gwant->weqtype == MT7925_WOC_WEQ_JOIN)
		ieee80211_itewate_active_intewfaces_atomic(hw,
						IEEE80211_IFACE_ITEW_WESUME_AWW,
						mt7925_mcu_woc_itew, gwant);
	dev->phy.woc_gwant = twue;
	wake_up(&dev->phy.woc_wait);
	duwation = we32_to_cpu(gwant->max_intewvaw);
	mod_timew(&dev->phy.woc_timew,
		  jiffies + msecs_to_jiffies(duwation));
}

static void
mt7925_mcu_scan_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
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
mt7925_mcu_tx_done_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
#define UNI_EVENT_TX_DONE_MSG 0
#define UNI_EVENT_TX_DONE_WAW 1
	stwuct mt7925_mcu_txs_event {
		u8 vew;
		u8 wsv[3];
		u8 data[0];
	} __packed * txs;
	stwuct twv *twv;
	u32 twv_wen;

	skb_puww(skb, sizeof(stwuct mt7925_mcu_wxd) + 4);
	twv = (stwuct twv *)skb->data;
	twv_wen = skb->wen;

	whiwe (twv_wen > 0 && we16_to_cpu(twv->wen) <= twv_wen) {
		switch (we16_to_cpu(twv->tag)) {
		case UNI_EVENT_TX_DONE_WAW:
			txs = (stwuct mt7925_mcu_txs_event *)twv->data;
			mt7925_mac_add_txs(dev, txs->data);
			bweak;
		defauwt:
			bweak;
		}
		twv_wen -= we16_to_cpu(twv->wen);
		twv = (stwuct twv *)((chaw *)(twv) + we16_to_cpu(twv->wen));
	}
}

static void
mt7925_mcu_uni_debug_msg_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7925_uni_debug_msg {
		__we16 tag;
		__we16 wen;
		u8 fmt;
		u8 wsv[3];
		u8 id;
		u8 type:3;
		u8 nw_awgs:5;
		union {
			stwuct idxwog {
				__we16 wsv;
				__we32 ts;
				__we32 idx;
				u8 data[];
			} __packed idx;
			stwuct txtwog {
				u8 wen;
				u8 wsv;
				__we32 ts;
				u8 data[];
			} __packed txt;
		};
	} __packed * hdw;

	skb_puww(skb, sizeof(stwuct mt7925_mcu_wxd) + 4);
	hdw = (stwuct mt7925_uni_debug_msg *)skb->data;

	if (hdw->id == 0x28) {
		skb_puww(skb, offsetof(stwuct mt7925_uni_debug_msg, id));
		wiphy_info(mt76_hw(dev)->wiphy, "%.*s", skb->wen, skb->data);
		wetuwn;
	} ewse if (hdw->id != 0xa8) {
		wetuwn;
	}

	if (hdw->type == 0) { /* idx wog */
		int i, wet, wen = PAGE_SIZE - 1, nw_vaw;
		stwuct page *page = dev_awwoc_pages(get_owdew(wen));
		__we32 *vaw;
		chaw *buf, *cuw;

		if (!page)
			wetuwn;

		buf = page_addwess(page);
		cuw = buf;

		nw_vaw = (we16_to_cpu(hdw->wen) - sizeof(*hdw)) / 4;
		vaw = (__we32 *)hdw->idx.data;
		fow (i = 0; i < nw_vaw && wen > 0; i++) {
			wet = snpwintf(cuw, wen, "0x%x,", we32_to_cpu(vaw[i]));
			if (wet <= 0)
				bweak;

			cuw += wet;
			wen -= wet;
		}
		if (cuw > buf)
			wiphy_info(mt76_hw(dev)->wiphy, "idx: 0x%X,%d,%s",
				   we32_to_cpu(hdw->idx.idx), nw_vaw, buf);
		put_page(page);
	} ewse if (hdw->type == 2) { /* stw wog */
		wiphy_info(mt76_hw(dev)->wiphy, "%.*s", hdw->txt.wen, hdw->txt.data);
	}
}

static void
mt7925_mcu_uni_wx_unsowicited_event(stwuct mt792x_dev *dev,
				    stwuct sk_buff *skb)
{
	stwuct mt7925_mcu_wxd *wxd;

	wxd = (stwuct mt7925_mcu_wxd *)skb->data;

	switch (wxd->eid) {
	case MCU_UNI_EVENT_FW_WOG_2_HOST:
		mt7925_mcu_uni_debug_msg_event(dev, skb);
		bweak;
	case MCU_UNI_EVENT_WOC:
		mt7925_mcu_uni_woc_event(dev, skb);
		bweak;
	case MCU_UNI_EVENT_SCAN_DONE:
		mt7925_mcu_scan_event(dev, skb);
		wetuwn;
	case MCU_UNI_EVENT_TX_DONE:
		mt7925_mcu_tx_done_event(dev, skb);
		bweak;
	case MCU_UNI_EVENT_BSS_BEACON_WOSS:
		mt7925_mcu_connection_woss_event(dev, skb);
		bweak;
	case MCU_UNI_EVENT_COWEDUMP:
		dev->fw_assewt = twue;
		mt76_connac_mcu_cowedump_event(&dev->mt76, skb, &dev->cowedump);
		wetuwn;
	defauwt:
		bweak;
	}
	dev_kfwee_skb(skb);
}

void mt7925_mcu_wx_event(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt7925_mcu_wxd *wxd = (stwuct mt7925_mcu_wxd *)skb->data;

	if (skb_wineawize(skb))
		wetuwn;

	if (wxd->option & MCU_UNI_CMD_UNSOWICITED_EVENT) {
		mt7925_mcu_uni_wx_unsowicited_event(dev, skb);
		wetuwn;
	}

	mt76_mcu_wx_event(&dev->mt76, skb);
}

static int
mt7925_mcu_sta_ba(stwuct mt76_dev *dev, stwuct mt76_vif *mvif,
		  stwuct ieee80211_ampdu_pawams *pawams,
		  boow enabwe, boow tx)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)pawams->sta->dwv_pwiv;
	stwuct sta_wec_ba_uni *ba;
	stwuct sk_buff *skb;
	stwuct twv *twv;
	int wen;

	wen = sizeof(stwuct sta_weq_hdw) + sizeof(*ba);
	skb = __mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid,
					      wen);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_BA, sizeof(*ba));

	ba = (stwuct sta_wec_ba_uni *)twv;
	ba->ba_type = tx ? MT_BA_TYPE_OWIGINATOW : MT_BA_TYPE_WECIPIENT;
	ba->winsize = cpu_to_we16(pawams->buf_size);
	ba->ssn = cpu_to_we16(pawams->ssn);
	ba->ba_en = enabwe << pawams->tid;
	ba->amsdu = pawams->amsdu;
	ba->tid = pawams->tid;

	wetuwn mt76_mcu_skb_send_msg(dev, skb,
				     MCU_UNI_CMD(STA_WEC_UPDATE), twue);
}

/** stawec & wtbw **/
int mt7925_mcu_uni_tx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)pawams->sta->dwv_pwiv;
	stwuct mt792x_vif *mvif = msta->vif;

	if (enabwe && !pawams->amsdu)
		msta->wcid.amsdu = fawse;

	wetuwn mt7925_mcu_sta_ba(&dev->mt76, &mvif->mt76, pawams,
				 enabwe, twue);
}

int mt7925_mcu_uni_wx_ba(stwuct mt792x_dev *dev,
			 stwuct ieee80211_ampdu_pawams *pawams,
			 boow enabwe)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)pawams->sta->dwv_pwiv;
	stwuct mt792x_vif *mvif = msta->vif;

	wetuwn mt7925_mcu_sta_ba(&dev->mt76, &mvif->mt76, pawams,
				 enabwe, fawse);
}

static int mt7925_woad_cwc(stwuct mt792x_dev *dev, const chaw *fw_name)
{
	const stwuct mt76_connac2_fw_twaiwew *hdw;
	const stwuct mt76_connac2_fw_wegion *wegion;
	const stwuct mt7925_cwc *cwc;
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt792x_phy *phy = &dev->phy;
	const stwuct fiwmwawe *fw;
	int wet, i, wen, offset = 0;
	u8 *cwc_base = NUWW;

	if (mt7925_disabwe_cwc ||
	    mt76_is_usb(&dev->mt76))
		wetuwn 0;

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
		cwc = (const stwuct mt7925_cwc *)(cwc_base + offset);

		/* do not init buf again if chip weset twiggewed */
		if (phy->cwc[cwc->idx])
			continue;

		phy->cwc[cwc->idx] = devm_kmemdup(mdev->dev, cwc,
						  we32_to_cpu(cwc->wen),
						  GFP_KEWNEW);

		if (!phy->cwc[cwc->idx]) {
			wet = -ENOMEM;
			goto out;
		}
	}

	wet = mt7925_mcu_set_cwc(dev, "00", ENVIWON_INDOOW);
out:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

int mt7925_mcu_fw_wog_2_host(stwuct mt792x_dev *dev, u8 ctww)
{
	stwuct {
		u8 _wsv[4];

		__we16 tag;
		__we16 wen;
		u8 ctww;
		u8 intewvaw;
		u8 _wsv2[2];
	} __packed weq = {
		.tag = cpu_to_we16(UNI_WSYS_CONFIG_FW_WOG_CTWW),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.ctww = ctww,
	};
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_UNI_CMD(WSYS_CONFIG),
					&weq, sizeof(weq), fawse, NUWW);
	wetuwn wet;
}

static void
mt7925_mcu_pawse_phy_cap(stwuct mt792x_dev *dev, chaw *data)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt76_dev *mdev = mphy->dev;
	stwuct mt7925_mcu_phy_cap {
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
		u8 eht;
	} __packed * cap;
	enum {
		WF0_24G,
		WF0_5G
	};

	cap = (stwuct mt7925_mcu_phy_cap *)data;

	mdev->phy.antenna_mask = BIT(cap->nss) - 1;
	mdev->phy.chainmask = mdev->phy.antenna_mask;
	mdev->phy.cap.has_2ghz = cap->hw_path & BIT(WF0_24G);
	mdev->phy.cap.has_5ghz = cap->hw_path & BIT(WF0_5G);
	dev->has_eht = cap->eht;
}

static int
mt7925_mcu_get_nic_capabiwity(stwuct mt792x_dev *dev)
{
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct {
		u8 _wsv[4];

		__we16 tag;
		__we16 wen;
	} __packed weq = {
		.tag = cpu_to_we16(UNI_CHIP_CONFIG_NIC_CAPA),
		.wen = cpu_to_we16(sizeof(weq) - 4),
	};
	stwuct mt76_connac_cap_hdw {
		__we16 n_ewement;
		u8 wsv[2];
	} __packed * hdw;
	stwuct sk_buff *skb;
	int wet, i;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_UNI_CMD(CHIP_CONFIG),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	hdw = (stwuct mt76_connac_cap_hdw *)skb->data;
	if (skb->wen < sizeof(*hdw)) {
		wet = -EINVAW;
		goto out;
	}

	skb_puww(skb, sizeof(*hdw));

	fow (i = 0; i < we16_to_cpu(hdw->n_ewement); i++) {
		stwuct twv *twv = (stwuct twv *)skb->data;
		int wen;

		if (skb->wen < sizeof(*twv))
			bweak;

		wen = we16_to_cpu(twv->wen);
		if (skb->wen < wen)
			bweak;

		switch (we16_to_cpu(twv->tag)) {
		case MT_NIC_CAP_6G:
			mphy->cap.has_6ghz = !!twv->data[0];
			bweak;
		case MT_NIC_CAP_MAC_ADDW:
			memcpy(mphy->macaddw, (void *)twv->data, ETH_AWEN);
			bweak;
		case MT_NIC_CAP_PHY:
			mt7925_mcu_pawse_phy_cap(dev, twv->data);
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

int mt7925_mcu_chip_config(stwuct mt792x_dev *dev, const chaw *cmd)
{
	u16 wen = stwwen(cmd) + 1;
	stwuct {
		u8 _wsv[4];
		__we16 tag;
		__we16 wen;
		stwuct mt76_connac_config config;
	} __packed weq = {
		.tag = cpu_to_we16(UNI_CHIP_CONFIG_CHIP_CFG),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.config = {
			.wesp_type = 0,
			.type = 0,
			.data_size = cpu_to_we16(wen),
		},
	};

	memcpy(weq.config.data, cmd, wen);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(CHIP_CONFIG),
				 &weq, sizeof(weq), fawse);
}

int mt7925_mcu_set_deep_sweep(stwuct mt792x_dev *dev, boow enabwe)
{
	chaw cmd[16];

	snpwintf(cmd, sizeof(cmd), "KeepFuwwPww %d", !enabwe);

	wetuwn mt7925_mcu_chip_config(dev, cmd);
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_set_deep_sweep);

int mt7925_wun_fiwmwawe(stwuct mt792x_dev *dev)
{
	int eww;

	eww = mt792x_woad_fiwmwawe(dev);
	if (eww)
		wetuwn eww;

	eww = mt7925_mcu_get_nic_capabiwity(dev);
	if (eww)
		wetuwn eww;

	set_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);
	eww = mt7925_woad_cwc(dev, mt792x_wam_name(dev));
	if (eww)
		wetuwn eww;

	wetuwn mt7925_mcu_fw_wog_2_host(dev, 1);
}
EXPOWT_SYMBOW_GPW(mt7925_wun_fiwmwawe);

static void
mt7925_mcu_sta_hdw_twans_twv(stwuct sk_buff *skb,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_hdw_twans *hdw_twans;
	stwuct mt76_wcid *wcid;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HDW_TWANS, sizeof(*hdw_twans));
	hdw_twans = (stwuct sta_wec_hdw_twans *)twv;
	hdw_twans->dis_wx_hdw_twan = twue;

	if (vif->type == NW80211_IFTYPE_STATION)
		hdw_twans->to_ds = twue;
	ewse
		hdw_twans->fwom_ds = twue;

	wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	if (!wcid)
		wetuwn;

	hdw_twans->dis_wx_hdw_twan = !test_bit(MT_WCID_FWAG_HDW_TWANS, &wcid->fwags);
	if (test_bit(MT_WCID_FWAG_4ADDW, &wcid->fwags)) {
		hdw_twans->to_ds = twue;
		hdw_twans->fwom_ds = twue;
	}
}

int mt7925_mcu_wtbw_update_hdw_twans(stwuct mt792x_dev *dev,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_sta *msta;
	stwuct sk_buff *skb;

	msta = sta ? (stwuct mt792x_sta *)sta->dwv_pwiv : &mvif->sta;

	skb = __mt76_connac_mcu_awwoc_sta_weq(&dev->mt76, &mvif->mt76,
					      &msta->wcid,
					      MT7925_STA_UPDATE_MAX_SIZE);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* stawec hdw twans */
	mt7925_mcu_sta_hdw_twans_twv(skb, vif, sta);
	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_WMWA_UNI_CMD(STA_WEC_UPDATE), twue);
}

int mt7925_mcu_set_tx(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif)
{
#define MCU_EDCA_AC_PAWAM	0
#define WMM_AIFS_SET		BIT(0)
#define WMM_CW_MIN_SET		BIT(1)
#define WMM_CW_MAX_SET		BIT(2)
#define WMM_TXOP_SET		BIT(3)
#define WMM_PAWAM_SET		(WMM_AIFS_SET | WMM_CW_MIN_SET | \
				 WMM_CW_MAX_SET | WMM_TXOP_SET)
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct {
		u8 bss_idx;
		u8 __wsv[3];
	} __packed hdw = {
		.bss_idx = mvif->mt76.idx,
	};
	stwuct sk_buff *skb;
	int wen = sizeof(hdw) + IEEE80211_NUM_ACS * sizeof(stwuct edca);
	int ac;

	skb = mt76_mcu_msg_awwoc(&dev->mt76, NUWW, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &hdw, sizeof(hdw));

	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		stwuct ieee80211_tx_queue_pawams *q = &mvif->queue_pawams[ac];
		stwuct edca *e;
		stwuct twv *twv;

		twv = mt76_connac_mcu_add_twv(skb, MCU_EDCA_AC_PAWAM, sizeof(*e));

		e = (stwuct edca *)twv;
		e->set = WMM_PAWAM_SET;
		e->queue = ac + mvif->mt76.wmm_idx * MT76_CONNAC_MAX_WMM_SETS;
		e->aifs = q->aifs;
		e->txop = cpu_to_we16(q->txop);

		if (q->cw_min)
			e->cw_min = fws(q->cw_min);
		ewse
			e->cw_min = 5;

		if (q->cw_max)
			e->cw_max = fws(q->cw_max);
		ewse
			e->cw_max = 10;
	}

	wetuwn mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_UNI_CMD(EDCA_UPDATE), twue);
}

static int
mt7925_mcu_sta_key_twv(stwuct mt76_wcid *wcid,
		       stwuct mt76_connac_sta_key_conf *sta_key_conf,
		       stwuct sk_buff *skb,
		       stwuct ieee80211_key_conf *key,
		       enum set_key_cmd cmd)
{
	stwuct sta_wec_sec_uni *sec;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_KEY_V2, sizeof(*sec));
	sec = (stwuct sta_wec_sec_uni *)twv;
	sec->add = cmd;

	if (cmd == SET_KEY) {
		stwuct sec_key_uni *sec_key;
		u8 ciphew;

		ciphew = mt76_connac_mcu_get_ciphew(key->ciphew);
		if (ciphew == MCU_CIPHEW_NONE)
			wetuwn -EOPNOTSUPP;

		sec_key = &sec->key[0];
		sec_key->ciphew_wen = sizeof(*sec_key);

		if (ciphew == MCU_CIPHEW_BIP_CMAC_128) {
			sec_key->wwan_idx = cpu_to_we16(wcid->idx);
			sec_key->ciphew_id = MCU_CIPHEW_AES_CCMP;
			sec_key->key_id = sta_key_conf->keyidx;
			sec_key->key_wen = 16;
			memcpy(sec_key->key, sta_key_conf->key, 16);

			sec_key = &sec->key[1];
			sec_key->wwan_idx = cpu_to_we16(wcid->idx);
			sec_key->ciphew_id = MCU_CIPHEW_BIP_CMAC_128;
			sec_key->ciphew_wen = sizeof(*sec_key);
			sec_key->key_wen = 16;
			memcpy(sec_key->key, key->key, 16);
			sec->n_ciphew = 2;
		} ewse {
			sec_key->wwan_idx = cpu_to_we16(wcid->idx);
			sec_key->ciphew_id = ciphew;
			sec_key->key_id = key->keyidx;
			sec_key->key_wen = key->keywen;
			memcpy(sec_key->key, key->key, key->keywen);

			if (ciphew == MCU_CIPHEW_TKIP) {
				/* Wx/Tx MIC keys awe swapped */
				memcpy(sec_key->key + 16, key->key + 24, 8);
				memcpy(sec_key->key + 24, key->key + 16, 8);
			}

			/* stowe key_conf fow BIP batch update */
			if (ciphew == MCU_CIPHEW_AES_CCMP) {
				memcpy(sta_key_conf->key, key->key, key->keywen);
				sta_key_conf->keyidx = key->keyidx;
			}

			sec->n_ciphew = 1;
		}
	} ewse {
		sec->n_ciphew = 0;
	}

	wetuwn 0;
}

int mt7925_mcu_add_key(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
		       stwuct mt76_connac_sta_key_conf *sta_key_conf,
		       stwuct ieee80211_key_conf *key, int mcu_cmd,
		       stwuct mt76_wcid *wcid, enum set_key_cmd cmd)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct sk_buff *skb;
	int wet;

	skb = __mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid,
					      MT7925_STA_UPDATE_MAX_SIZE);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wet = mt7925_mcu_sta_key_twv(wcid, sta_key_conf, skb, key, cmd);
	if (wet)
		wetuwn wet;

	wetuwn mt76_mcu_skb_send_msg(dev, skb, mcu_cmd, twue);
}

int mt7925_mcu_set_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
		       stwuct ieee80211_channew *chan, int duwation,
		       enum mt7925_woc_weq type, u8 token_id)
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

int mt7925_mcu_abowt_woc(stwuct mt792x_phy *phy, stwuct mt792x_vif *vif,
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

int mt7925_mcu_set_chan_info(stwuct mt792x_phy *phy, u16 tag)
{
	static const u8 ch_band[] = {
		[NW80211_BAND_2GHZ] = 0,
		[NW80211_BAND_5GHZ] = 1,
		[NW80211_BAND_6GHZ] = 2,
	};
	stwuct mt792x_dev *dev = phy->dev;
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	int fweq1 = chandef->centew_fweq1;
	u8 band_idx = chandef->chan->band != NW80211_BAND_2GHZ;
	stwuct {
		/* fixed fiewd */
		u8 __wsv[4];

		__we16 tag;
		__we16 wen;
		u8 contwow_ch;
		u8 centew_ch;
		u8 bw;
		u8 tx_path_num;
		u8 wx_path;	/* mask ow num */
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
		u8 wsv1[53];
	} __packed weq = {
		.tag = cpu_to_we16(tag),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.contwow_ch = chandef->chan->hw_vawue,
		.centew_ch = ieee80211_fwequency_to_channew(fweq1),
		.bw = mt76_connac_chan_bw(chandef),
		.tx_path_num = hweight8(phy->mt76->antenna_mask),
		.wx_path = phy->mt76->antenna_mask,
		.band_idx = band_idx,
		.channew_band = ch_band[chandef->chan->band],
	};

	if (chandef->chan->band == NW80211_BAND_6GHZ)
		weq.channew_band = 2;
	ewse
		weq.channew_band = chandef->chan->band;

	if (tag == UNI_CHANNEW_WX_PATH ||
	    dev->mt76.hw->conf.fwags & IEEE80211_CONF_MONITOW)
		weq.switch_weason = CH_SWITCH_NOWMAW;
	ewse if (phy->mt76->hw->conf.fwags & IEEE80211_CONF_OFFCHANNEW)
		weq.switch_weason = CH_SWITCH_SCAN_BYPASS_DPD;
	ewse if (!cfg80211_weg_can_beacon(phy->mt76->hw->wiphy, chandef,
					  NW80211_IFTYPE_AP))
		weq.switch_weason = CH_SWITCH_DFS;
	ewse
		weq.switch_weason = CH_SWITCH_NOWMAW;

	if (tag == UNI_CHANNEW_SWITCH)
		weq.wx_path = hweight8(weq.wx_path);

	if (chandef->width == NW80211_CHAN_WIDTH_80P80) {
		int fweq2 = chandef->centew_fweq2;

		weq.centew_ch2 = ieee80211_fwequency_to_channew(fweq2);
	}

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(CHANNEW_SWITCH),
				 &weq, sizeof(weq), twue);
}

int mt7925_mcu_set_eepwom(stwuct mt792x_dev *dev)
{
	stwuct {
		u8 _wsv[4];

		__we16 tag;
		__we16 wen;
		u8 buffew_mode;
		u8 fowmat;
		__we16 buf_wen;
	} __packed weq = {
		.tag = cpu_to_we16(UNI_EFUSE_BUFFEW_MODE),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.buffew_mode = EE_MODE_EFUSE,
		.fowmat = EE_FOWMAT_WHOWE
	};

	wetuwn mt76_mcu_send_and_get_msg(&dev->mt76, MCU_UNI_CMD(EFUSE_CTWW),
					 &weq, sizeof(weq), fawse, NUWW);
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_set_eepwom);

int mt7925_mcu_uni_bss_ps(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif)
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
mt7925_mcu_uni_bss_bcnft(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
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
			u8 bmc_dewivewed_ac;
			u8 bmc_twiggewed_ac;
			u8 pad[3];
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
mt7925_mcu_set_bss_pm(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
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
			u8 bmc_dewivewed_ac;
			u8 bmc_twiggewed_ac;
			u8 pad[3];
		} __packed enabwe;
	} weq = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.enabwe = {
			.tag = cpu_to_we16(UNI_BSS_INFO_BCNFT),
			.wen = cpu_to_we16(sizeof(stwuct bcnft_twv)),
			.dtim_pewiod = vif->bss_conf.dtim_pewiod,
			.bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int),
		},
	};
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct pm_disabwe {
			__we16 tag;
			__we16 wen;
		} __packed disabwe;
	} weq1 = {
		.hdw = {
			.bss_idx = mvif->mt76.idx,
		},
		.disabwe = {
			.tag = cpu_to_we16(UNI_BSS_INFO_PM_DISABWE),
			.wen = cpu_to_we16(sizeof(stwuct pm_disabwe))
		},
	};
	int eww;

	eww = mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				&weq1, sizeof(weq1), fawse);
	if (eww < 0 || !enabwe)
		wetuwn eww;

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				 &weq, sizeof(weq), fawse);
}

static void
mt7925_mcu_sta_he_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	if (!sta->defwink.he_cap.has_he)
		wetuwn;

	mt76_connac_mcu_sta_he_twv_v2(skb, sta);
}

static void
mt7925_mcu_sta_he_6g_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_he_6g_capa *he_6g;
	stwuct twv *twv;

	if (!sta->defwink.he_6ghz_capa.capa)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HE_6G, sizeof(*he_6g));

	he_6g = (stwuct sta_wec_he_6g_capa *)twv;
	he_6g->capa = sta->defwink.he_6ghz_capa.capa;
}

static void
mt7925_mcu_sta_eht_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_eht_mcs_nss_supp *mcs_map;
	stwuct ieee80211_eht_cap_ewem_fixed *ewem;
	stwuct sta_wec_eht *eht;
	stwuct twv *twv;

	if (!sta->defwink.eht_cap.has_eht)
		wetuwn;

	mcs_map = &sta->defwink.eht_cap.eht_mcs_nss_supp;
	ewem = &sta->defwink.eht_cap.eht_cap_ewem;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_EHT, sizeof(*eht));

	eht = (stwuct sta_wec_eht *)twv;
	eht->tid_bitmap = 0xff;
	eht->mac_cap = cpu_to_we16(*(u16 *)ewem->mac_cap_info);
	eht->phy_cap = cpu_to_we64(*(u64 *)ewem->phy_cap_info);
	eht->phy_cap_ext = cpu_to_we64(ewem->phy_cap_info[8]);

	if (sta->defwink.bandwidth == IEEE80211_STA_WX_BW_20)
		memcpy(eht->mcs_map_bw20, &mcs_map->onwy_20mhz, sizeof(eht->mcs_map_bw20));
	memcpy(eht->mcs_map_bw80, &mcs_map->bw._80, sizeof(eht->mcs_map_bw80));
	memcpy(eht->mcs_map_bw160, &mcs_map->bw._160, sizeof(eht->mcs_map_bw160));
}

static void
mt7925_mcu_sta_ht_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_ht *ht;
	stwuct twv *twv;

	if (!sta->defwink.ht_cap.ht_suppowted)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HT, sizeof(*ht));

	ht = (stwuct sta_wec_ht *)twv;
	ht->ht_cap = cpu_to_we16(sta->defwink.ht_cap.cap);
}

static void
mt7925_mcu_sta_vht_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_vht *vht;
	stwuct twv *twv;

	/* Fow 6G band, this twv is necessawy to wet hw wowk nowmawwy */
	if (!sta->defwink.he_6ghz_capa.capa && !sta->defwink.vht_cap.vht_suppowted)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_VHT, sizeof(*vht));

	vht = (stwuct sta_wec_vht *)twv;
	vht->vht_cap = cpu_to_we32(sta->defwink.vht_cap.cap);
	vht->vht_wx_mcs_map = sta->defwink.vht_cap.vht_mcs.wx_mcs_map;
	vht->vht_tx_mcs_map = sta->defwink.vht_cap.vht_mcs.tx_mcs_map;
}

static void
mt7925_mcu_sta_amsdu_twv(stwuct sk_buff *skb,
			 stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;
	stwuct sta_wec_amsdu *amsdu;
	stwuct twv *twv;

	if (vif->type != NW80211_IFTYPE_STATION &&
	    vif->type != NW80211_IFTYPE_AP)
		wetuwn;

	if (!sta->defwink.agg.max_amsdu_wen)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HW_AMSDU, sizeof(*amsdu));
	amsdu = (stwuct sta_wec_amsdu *)twv;
	amsdu->max_amsdu_num = 8;
	amsdu->amsdu_en = twue;
	msta->wcid.amsdu = twue;

	switch (sta->defwink.agg.max_amsdu_wen) {
	case IEEE80211_MAX_MPDU_WEN_VHT_11454:
		amsdu->max_mpdu_size =
			IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
		wetuwn;
	case IEEE80211_MAX_MPDU_WEN_HT_7935:
	case IEEE80211_MAX_MPDU_WEN_VHT_7991:
		amsdu->max_mpdu_size = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991;
		wetuwn;
	defauwt:
		amsdu->max_mpdu_size = IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895;
		wetuwn;
	}
}

static void
mt7925_mcu_sta_phy_twv(stwuct sk_buff *skb,
		       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = &mvif->mt76.ctx->def;
	stwuct sta_wec_phy *phy;
	stwuct twv *twv;
	u8 af = 0, mm = 0;

	if (!sta->defwink.ht_cap.ht_suppowted && !sta->defwink.he_6ghz_capa.capa)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_PHY, sizeof(*phy));
	phy = (stwuct sta_wec_phy *)twv;
	phy->phy_type = mt76_connac_get_phy_mode_v2(mvif->phy->mt76, vif, chandef->chan->band, sta);
	if (sta->defwink.ht_cap.ht_suppowted) {
		af = sta->defwink.ht_cap.ampdu_factow;
		mm = sta->defwink.ht_cap.ampdu_density;
	}

	if (sta->defwink.vht_cap.vht_suppowted) {
		u8 vht_af = FIEWD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK,
				      sta->defwink.vht_cap.cap);

		af = max_t(u8, af, vht_af);
	}

	if (sta->defwink.he_6ghz_capa.capa) {
		af = we16_get_bits(sta->defwink.he_6ghz_capa.capa,
				   IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP);
		mm = we16_get_bits(sta->defwink.he_6ghz_capa.capa,
				   IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT);
	}

	phy->ampdu = FIEWD_PWEP(IEEE80211_HT_AMPDU_PAWM_FACTOW, af) |
		     FIEWD_PWEP(IEEE80211_HT_AMPDU_PAWM_DENSITY, mm);
	phy->max_ampdu_wen = af;
}

static void
mt7925_mcu_sta_state_v2_twv(stwuct mt76_phy *mphy, stwuct sk_buff *skb,
			    stwuct ieee80211_sta *sta,
			    stwuct ieee80211_vif *vif,
			    u8 wcpi, u8 sta_state)
{
	stwuct sta_wec_state_v2 {
		__we16 tag;
		__we16 wen;
		u8 state;
		u8 wsv[3];
		__we32 fwags;
		u8 vht_opmode;
		u8 action;
		u8 wsv2[2];
	} __packed * state;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_STATE, sizeof(*state));
	state = (stwuct sta_wec_state_v2 *)twv;
	state->state = sta_state;

	if (sta->defwink.vht_cap.vht_suppowted) {
		state->vht_opmode = sta->defwink.bandwidth;
		state->vht_opmode |= sta->defwink.wx_nss <<
			IEEE80211_OPMODE_NOTIF_WX_NSS_SHIFT;
	}
}

static void
mt7925_mcu_sta_wate_ctww_twv(stwuct sk_buff *skb,
			     stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = &mvif->mt76.ctx->def;
	enum nw80211_band band = chandef->chan->band;
	stwuct sta_wec_wa_info *wa_info;
	stwuct twv *twv;
	u16 supp_wates;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_WA, sizeof(*wa_info));
	wa_info = (stwuct sta_wec_wa_info *)twv;

	supp_wates = sta->defwink.supp_wates[band];
	if (band == NW80211_BAND_2GHZ)
		supp_wates = FIEWD_PWEP(WA_WEGACY_OFDM, supp_wates >> 4) |
			     FIEWD_PWEP(WA_WEGACY_CCK, supp_wates & 0xf);
	ewse
		supp_wates = FIEWD_PWEP(WA_WEGACY_OFDM, supp_wates);

	wa_info->wegacy = cpu_to_we16(supp_wates);

	if (sta->defwink.ht_cap.ht_suppowted)
		memcpy(wa_info->wx_mcs_bitmask,
		       sta->defwink.ht_cap.mcs.wx_mask,
		       HT_MCS_MASK_NUM);
}

static void
mt7925_mcu_sta_mwd_twv(stwuct sk_buff *skb,
		       stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	stwuct sta_wec_mwd *mwd;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_MWD, sizeof(*mwd));
	mwd = (stwuct sta_wec_mwd *)twv;
	memcpy(mwd->mac_addw, vif->addw, ETH_AWEN);
	mwd->pwimawy_id = cpu_to_we16(wcid->idx);
	mwd->wwan_id = cpu_to_we16(wcid->idx);

	/* TODO: 0 means defwink onwy, add secondawy wink(1) watew */
	mwd->wink_num = !!(hweight8(vif->active_winks) > 1);
	WAWN_ON_ONCE(mwd->wink_num);
}

static int
mt7925_mcu_sta_cmd(stwuct mt76_phy *phy,
		   stwuct mt76_sta_cmd_info *info)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)info->vif->dwv_pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct twv *sta_wtbw;
	stwuct sk_buff *skb;

	skb = __mt76_connac_mcu_awwoc_sta_weq(dev, mvif, info->wcid,
					      MT7925_STA_UPDATE_MAX_SIZE);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	if (info->sta || !info->offwoad_fw)
		mt76_connac_mcu_sta_basic_twv(dev, skb, info->vif, info->sta,
					      info->enabwe, info->newwy);
	if (info->sta && info->enabwe) {
		mt7925_mcu_sta_phy_twv(skb, info->vif, info->sta);
		mt7925_mcu_sta_ht_twv(skb, info->sta);
		mt7925_mcu_sta_vht_twv(skb, info->sta);
		mt76_connac_mcu_sta_uapsd(skb, info->vif, info->sta);
		mt7925_mcu_sta_amsdu_twv(skb, info->vif, info->sta);
		mt7925_mcu_sta_he_twv(skb, info->sta);
		mt7925_mcu_sta_he_6g_twv(skb, info->sta);
		mt7925_mcu_sta_eht_twv(skb, info->sta);
		mt7925_mcu_sta_wate_ctww_twv(skb, info->vif, info->sta);
		mt7925_mcu_sta_state_v2_twv(phy, skb, info->sta,
					    info->vif, info->wcpi,
					    info->state);
		mt7925_mcu_sta_hdw_twans_twv(skb, info->vif, info->sta);
		mt7925_mcu_sta_mwd_twv(skb, info->vif, info->sta);
	}

	sta_wtbw = mt76_connac_mcu_add_twv(skb, STA_WEC_WTBW,
					   sizeof(stwuct twv));

	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(dev, info->wcid,
						  WTBW_WESET_AND_SET,
						  sta_wtbw, &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	if (info->enabwe) {
		mt76_connac_mcu_wtbw_genewic_twv(dev, skb, info->vif,
						 info->sta, sta_wtbw,
						 wtbw_hdw);
		mt76_connac_mcu_wtbw_hdw_twans_twv(skb, info->vif, info->wcid,
						   sta_wtbw, wtbw_hdw);
		if (info->sta)
			mt76_connac_mcu_wtbw_ht_twv(dev, skb, info->sta,
						    sta_wtbw, wtbw_hdw,
						    twue, twue);
	}

	wetuwn mt76_mcu_skb_send_msg(dev, skb, info->cmd, twue);
}

int mt7925_mcu_sta_update(stwuct mt792x_dev *dev, stwuct ieee80211_sta *sta,
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

	wetuwn mt7925_mcu_sta_cmd(&dev->mphy, &info);
}

int mt7925_mcu_set_beacon_fiwtew(stwuct mt792x_dev *dev,
				 stwuct ieee80211_vif *vif,
				 boow enabwe)
{
#define MT7925_FIF_BIT_CWW		BIT(1)
#define MT7925_FIF_BIT_SET		BIT(0)
	int eww = 0;

	if (enabwe) {
		eww = mt7925_mcu_uni_bss_bcnft(dev, vif, twue);
		if (eww)
			wetuwn eww;

		wetuwn mt7925_mcu_set_wxfiwtew(dev, 0,
					       MT7925_FIF_BIT_SET,
					       MT_WF_WFCW_DWOP_OTHEW_BEACON);
	}

	eww = mt7925_mcu_set_bss_pm(dev, vif, fawse);
	if (eww)
		wetuwn eww;

	wetuwn mt7925_mcu_set_wxfiwtew(dev, 0,
				       MT7925_FIF_BIT_CWW,
				       MT_WF_WFCW_DWOP_OTHEW_BEACON);
}

int mt7925_get_txpww_info(stwuct mt792x_dev *dev, u8 band_idx, stwuct mt7925_txpww *txpww)
{
#define TX_POWEW_SHOW_INFO 0x7
#define TXPOWEW_AWW_WATE_POWEW_INFO 0x2
	stwuct mt7925_txpww_event *event;
	stwuct mt7925_txpww_weq weq = {
		.tag = cpu_to_we16(TX_POWEW_SHOW_INFO),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.catg = TXPOWEW_AWW_WATE_POWEW_INFO,
		.band_idx = band_idx,
	};
	stwuct sk_buff *skb;
	int wet;

	wet = mt76_mcu_send_and_get_msg(&dev->mt76, MCU_UNI_CMD(TXPOWEW),
					&weq, sizeof(weq), twue, &skb);
	if (wet)
		wetuwn wet;

	event = (stwuct mt7925_txpww_event *)skb->data;
	memcpy(txpww, &event->txpww, sizeof(event->txpww));

	dev_kfwee_skb(skb);

	wetuwn 0;
}

int mt7925_mcu_set_sniffew(stwuct mt792x_dev *dev, stwuct ieee80211_vif *vif,
			   boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;

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
	} __packed weq = {
		.hdw = {
			.band_idx = mvif->mt76.band_idx,
		},
		.enabwe = {
			.tag = cpu_to_we16(UNI_SNIFFEW_ENABWE),
			.wen = cpu_to_we16(sizeof(stwuct sniffew_enabwe_twv)),
			.enabwe = enabwe,
		},
	};

	mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(SNIFFEW), &weq, sizeof(weq), twue);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(SNIFFEW), &weq, sizeof(weq),
				 twue);
}

int mt7925_mcu_config_sniffew(stwuct mt792x_vif *vif,
			      stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct mt76_phy *mphy = vif->phy->mt76;
	stwuct cfg80211_chan_def *chandef = ctx ? &ctx->def : &mphy->chandef;
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
			.tag = cpu_to_we16(UNI_SNIFFEW_CONFIG),
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

	wetuwn mt76_mcu_send_msg(mphy->dev, MCU_UNI_CMD(SNIFFEW),
				 &weq, sizeof(weq), twue);
}

int
mt7925_mcu_uni_add_beacon_offwoad(stwuct mt792x_dev *dev,
				  stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
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
			.type = 1,
		},
	};
	stwuct sk_buff *skb;
	u8 cap_offs;

	/* suppowt enabwe/update pwocess onwy
	 * disabwe fwow wouwd be handwed in bss stop handwew automaticawwy
	 */
	if (!enabwe)
		wetuwn -EOPNOTSUPP;

	skb = ieee80211_beacon_get_tempwate(mt76_hw(dev), vif, &offs, 0);
	if (!skb)
		wetuwn -EINVAW;

	cap_offs = offsetof(stwuct ieee80211_mgmt, u.beacon.capab_info);
	if (!skb_puww(skb, cap_offs)) {
		dev_eww(dev->mt76.dev, "beacon fowmat eww\n");
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	if (skb->wen > 512) {
		dev_eww(dev->mt76.dev, "beacon size wimit exceed\n");
		dev_kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	memcpy(weq.beacon_twv.pkt, skb->data, skb->wen);
	weq.beacon_twv.pkt_wen = cpu_to_we16(skb->wen);
	offs.tim_offset -= cap_offs;
	weq.beacon_twv.tim_ie_pos = cpu_to_we16(offs.tim_offset);

	if (offs.cntdwn_countew_offs[0]) {
		u16 csa_offs;

		csa_offs = offs.cntdwn_countew_offs[0] - cap_offs - 4;
		weq.beacon_twv.csa_ie_pos = cpu_to_we16(csa_offs);
	}
	dev_kfwee_skb(skb);

	wetuwn mt76_mcu_send_msg(&dev->mt76, MCU_UNI_CMD(BSS_INFO_UPDATE),
				 &weq, sizeof(weq), twue);
}

int mt7925_mcu_set_chctx(stwuct mt76_phy *phy, stwuct mt76_vif *mvif,
			 stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct cfg80211_chan_def *chandef = ctx ? &ctx->def : &phy->chandef;
	int fweq1 = chandef->centew_fweq1, fweq2 = chandef->centew_fweq2;
	enum nw80211_band band = chandef->chan->band;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct wwm_twv {
			__we16 tag;
			__we16 wen;
			u8 contwow_channew;
			u8 centew_chan;
			u8 centew_chan2;
			u8 bw;
			u8 tx_stweams;
			u8 wx_stweams;
			u8 ht_op_info;
			u8 sco;
			u8 band;
			u8 pad[3];
		} __packed wwm;
	} __packed wwm_weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.wwm = {
			.tag = cpu_to_we16(UNI_BSS_INFO_WWM),
			.wen = cpu_to_we16(sizeof(stwuct wwm_twv)),
			.contwow_channew = chandef->chan->hw_vawue,
			.centew_chan = ieee80211_fwequency_to_channew(fweq1),
			.centew_chan2 = ieee80211_fwequency_to_channew(fweq2),
			.tx_stweams = hweight8(phy->antenna_mask),
			.ht_op_info = 4, /* set HT 40M awwowed */
			.wx_stweams = hweight8(phy->antenna_mask),
			.band = band,
		},
	};

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_40:
		wwm_weq.wwm.bw = CMD_CBW_40MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		wwm_weq.wwm.bw = CMD_CBW_80MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
		wwm_weq.wwm.bw = CMD_CBW_8080MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		wwm_weq.wwm.bw = CMD_CBW_160MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_5:
		wwm_weq.wwm.bw = CMD_CBW_5MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		wwm_weq.wwm.bw = CMD_CBW_10MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
	defauwt:
		wwm_weq.wwm.bw = CMD_CBW_20MHZ;
		wwm_weq.wwm.ht_op_info = 0;
		bweak;
	}

	if (wwm_weq.wwm.contwow_channew < wwm_weq.wwm.centew_chan)
		wwm_weq.wwm.sco = 1; /* SCA */
	ewse if (wwm_weq.wwm.contwow_channew > wwm_weq.wwm.centew_chan)
		wwm_weq.wwm.sco = 3; /* SCB */

	wetuwn mt76_mcu_send_msg(mdev, MCU_UNI_CMD(BSS_INFO_UPDATE), &wwm_weq,
				 sizeof(wwm_weq), twue);
}

static stwuct sk_buff *
__mt7925_mcu_awwoc_bss_weq(stwuct mt76_dev *dev, stwuct mt76_vif *mvif, int wen)
{
	stwuct bss_weq_hdw hdw = {
		.bss_idx = mvif->idx,
	};
	stwuct sk_buff *skb;

	skb = mt76_mcu_msg_awwoc(dev, NUWW, wen);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	skb_put_data(skb, &hdw, sizeof(hdw));

	wetuwn skb;
}

static u8
mt7925_get_phy_mode_ext(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
			enum nw80211_band band, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_he_6ghz_capa *he_6ghz_capa;
	const stwuct ieee80211_sta_eht_cap *eht_cap;
	__we16 capa = 0;
	u8 mode = 0;

	if (sta) {
		he_6ghz_capa = &sta->defwink.he_6ghz_capa;
		eht_cap = &sta->defwink.eht_cap;
	} ewse {
		stwuct ieee80211_suppowted_band *sband;

		sband = phy->hw->wiphy->bands[band];
		capa = ieee80211_get_he_6ghz_capa(sband, vif->type);
		he_6ghz_capa = (stwuct ieee80211_he_6ghz_capa *)&capa;

		eht_cap = ieee80211_get_eht_iftype_cap(sband, vif->type);
	}

	switch (band) {
	case NW80211_BAND_2GHZ:
		if (eht_cap && eht_cap->has_eht)
			mode |= PHY_MODE_BE_24G;
		bweak;
	case NW80211_BAND_5GHZ:
		if (eht_cap && eht_cap->has_eht)
			mode |= PHY_MODE_BE_5G;
		bweak;
	case NW80211_BAND_6GHZ:
		if (he_6ghz_capa && he_6ghz_capa->capa)
			mode |= PHY_MODE_AX_6G;

		if (eht_cap && eht_cap->has_eht)
			mode |= PHY_MODE_BE_6G;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mode;
}

static void
mt7925_mcu_bss_basic_twv(stwuct sk_buff *skb,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta,
			 stwuct ieee80211_chanctx_conf *ctx,
			 stwuct mt76_phy *phy, u16 wwan_idx,
			 boow enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_sta *msta = sta ? (stwuct mt792x_sta *)sta->dwv_pwiv :
				  &mvif->sta;
	stwuct cfg80211_chan_def *chandef = ctx ? &ctx->def : &phy->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct mt76_connac_bss_basic_twv *basic_weq;
	u8 idx, basic_phy;
	stwuct twv *twv;
	int conn_type;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_BASIC, sizeof(*basic_weq));
	basic_weq = (stwuct mt76_connac_bss_basic_twv *)twv;

	idx = mvif->mt76.omac_idx > EXT_BSSID_STAWT ? HW_BSSID_0 :
						      mvif->mt76.omac_idx;
	basic_weq->hw_bss_idx = idx;

	basic_weq->phymode_ext = mt7925_get_phy_mode_ext(phy, vif, band, sta);

	basic_phy = mt76_connac_get_phy_mode_v2(phy, vif, band, sta);
	basic_weq->nonht_basic_phy = cpu_to_we16(basic_phy);

	memcpy(basic_weq->bssid, vif->bss_conf.bssid, ETH_AWEN);
	basic_weq->phymode = mt76_connac_get_phy_mode(phy, vif, band, sta);
	basic_weq->bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int);
	basic_weq->dtim_pewiod = vif->bss_conf.dtim_pewiod;
	basic_weq->bmc_tx_wwan_idx = cpu_to_we16(wwan_idx);
	basic_weq->sta_idx = cpu_to_we16(msta->wcid.idx);
	basic_weq->omac_idx = mvif->mt76.omac_idx;
	basic_weq->band_idx = mvif->mt76.band_idx;
	basic_weq->wmm_idx = mvif->mt76.wmm_idx;
	basic_weq->conn_state = !enabwe;

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		if (vif->p2p)
			conn_type = CONNECTION_P2P_GO;
		ewse
			conn_type = CONNECTION_INFWA_AP;
		basic_weq->conn_type = cpu_to_we32(conn_type);
		basic_weq->active = enabwe;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (vif->p2p)
			conn_type = CONNECTION_P2P_GC;
		ewse
			conn_type = CONNECTION_INFWA_STA;
		basic_weq->conn_type = cpu_to_we32(conn_type);
		basic_weq->active = twue;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		basic_weq->conn_type = cpu_to_we32(CONNECTION_IBSS_ADHOC);
		basic_weq->active = twue;
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

static void
mt7925_mcu_bss_sec_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct bss_sec_twv {
		__we16 tag;
		__we16 wen;
		u8 mode;
		u8 status;
		u8 ciphew;
		u8 __wsv;
	} __packed * sec;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_SEC, sizeof(*sec));
	sec = (stwuct bss_sec_twv *)twv;

	switch (mvif->ciphew) {
	case MCU_CIPHEW_GCMP_256:
	case MCU_CIPHEW_GCMP:
		sec->mode = MODE_WPA3_SAE;
		sec->status = 8;
		bweak;
	case MCU_CIPHEW_AES_CCMP:
		sec->mode = MODE_WPA2_PSK;
		sec->status = 6;
		bweak;
	case MCU_CIPHEW_TKIP:
		sec->mode = MODE_WPA2_PSK;
		sec->status = 4;
		bweak;
	case MCU_CIPHEW_WEP104:
	case MCU_CIPHEW_WEP40:
		sec->mode = MODE_SHAWED;
		sec->status = 0;
		bweak;
	defauwt:
		sec->mode = MODE_OPEN;
		sec->status = 1;
		bweak;
	}

	sec->ciphew = mvif->ciphew;
}

static void
mt7925_mcu_bss_bmc_twv(stwuct sk_buff *skb, stwuct mt792x_phy *phy,
		       stwuct ieee80211_chanctx_conf *ctx,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct cfg80211_chan_def *chandef = ctx ? &ctx->def : &phy->mt76->chandef;
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	enum nw80211_band band = chandef->chan->band;
	stwuct bss_wate_twv *bmc;
	stwuct twv *twv;
	u8 idx = mvif->mcast_wates_idx ?
		 mvif->mcast_wates_idx : mvif->basic_wates_idx;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_WATE, sizeof(*bmc));

	bmc = (stwuct bss_wate_twv *)twv;

	bmc->showt_pweambwe = (band == NW80211_BAND_2GHZ);
	bmc->bc_fixed_wate = idx;
	bmc->mc_fixed_wate = idx;
}

static void
mt7925_mcu_bss_mwd_twv(stwuct sk_buff *skb,
		       stwuct ieee80211_vif *vif,
		       stwuct ieee80211_sta *sta)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	boow is_mwd = ieee80211_vif_is_mwd(vif);
	stwuct bss_mwd_twv *mwd;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_MWD, sizeof(*mwd));
	mwd = (stwuct bss_mwd_twv *)twv;

	mwd->wink_id = sta ? (is_mwd ? vif->bss_conf.wink_id : 0) : 0xff;
	mwd->gwoup_mwd_id = is_mwd ? mvif->mt76.idx : 0xff;
	mwd->own_mwd_id = mvif->mt76.idx + 32;
	mwd->wemap_idx = 0xff;

	if (sta)
		memcpy(mwd->mac_addw, sta->addw, ETH_AWEN);
}

static void
mt7925_mcu_bss_qos_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif)
{
	stwuct mt76_connac_bss_qos_twv *qos;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_QBSS, sizeof(*qos));
	qos = (stwuct mt76_connac_bss_qos_twv *)twv;
	qos->qos = vif->bss_conf.qos;
}

static void
mt7925_mcu_bss_he_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
		      stwuct mt792x_phy *phy)
{
#define DEFAUWT_HE_PE_DUWATION		4
#define DEFAUWT_HE_DUWATION_WTS_THWES	1023
	const stwuct ieee80211_sta_he_cap *cap;
	stwuct bss_info_uni_he *he;
	stwuct twv *twv;

	cap = mt76_connac_get_he_phy_cap(phy->mt76, vif);

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_HE_BASIC, sizeof(*he));

	he = (stwuct bss_info_uni_he *)twv;
	he->he_pe_duwation = vif->bss_conf.htc_twig_based_pkt_ext;
	if (!he->he_pe_duwation)
		he->he_pe_duwation = DEFAUWT_HE_PE_DUWATION;

	he->he_wts_thwes = cpu_to_we16(vif->bss_conf.fwame_time_wts_th);
	if (!he->he_wts_thwes)
		he->he_wts_thwes = cpu_to_we16(DEFAUWT_HE_DUWATION_WTS_THWES);

	he->max_nss_mcs[CMD_HE_MCS_BW80] = cap->he_mcs_nss_supp.tx_mcs_80;
	he->max_nss_mcs[CMD_HE_MCS_BW160] = cap->he_mcs_nss_supp.tx_mcs_160;
	he->max_nss_mcs[CMD_HE_MCS_BW8080] = cap->he_mcs_nss_supp.tx_mcs_80p80;
}

static void
mt7925_mcu_bss_cowow_twv(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
			 boow enabwe)
{
	stwuct bss_info_uni_bss_cowow *cowow;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, UNI_BSS_INFO_BSS_COWOW, sizeof(*cowow));
	cowow = (stwuct bss_info_uni_bss_cowow *)twv;

	cowow->enabwe = enabwe ?
		vif->bss_conf.he_bss_cowow.enabwed : 0;
	cowow->bss_cowow = enabwe ?
		vif->bss_conf.he_bss_cowow.cowow : 0;
}

int mt7925_mcu_add_bss_info(stwuct mt792x_phy *phy,
			    stwuct ieee80211_chanctx_conf *ctx,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta,
			    int enabwe)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_dev *dev = phy->dev;
	stwuct sk_buff *skb;
	int eww;

	skb = __mt7925_mcu_awwoc_bss_weq(&dev->mt76, &mvif->mt76,
					 MT7925_BSS_UPDATE_MAX_SIZE);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	/* bss_basic must be fiwst */
	mt7925_mcu_bss_basic_twv(skb, vif, sta, ctx, phy->mt76,
				 mvif->sta.wcid.idx, enabwe);
	mt7925_mcu_bss_sec_twv(skb, vif);

	mt7925_mcu_bss_bmc_twv(skb, phy, ctx, vif, sta);
	mt7925_mcu_bss_qos_twv(skb, vif);
	mt7925_mcu_bss_mwd_twv(skb, vif, sta);

	if (vif->bss_conf.he_suppowt) {
		mt7925_mcu_bss_he_twv(skb, vif, phy);
		mt7925_mcu_bss_cowow_twv(skb, vif, enabwe);
	}

	eww = mt76_mcu_skb_send_msg(&dev->mt76, skb,
				    MCU_UNI_CMD(BSS_INFO_UPDATE), twue);
	if (eww < 0)
		wetuwn eww;

	wetuwn mt7925_mcu_set_chctx(phy->mt76, &mvif->mt76, ctx);
}

int mt7925_mcu_set_dbdc(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *mdev = phy->dev;

	stwuct mbmc_conf_twv *conf;
	stwuct mbmc_set_weq *hdw;
	stwuct sk_buff *skb;
	stwuct twv *twv;
	int max_wen, eww;

	max_wen = sizeof(*hdw) + sizeof(*conf);
	skb = mt76_mcu_msg_awwoc(mdev, NUWW, max_wen);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = (stwuct mbmc_set_weq *)skb_put(skb, sizeof(*hdw));

	twv = mt76_connac_mcu_add_twv(skb, UNI_MBMC_SETTING, sizeof(*conf));
	conf = (stwuct mbmc_conf_twv *)twv;

	conf->mbmc_en = 1;
	conf->band = 0; /* unused */

	eww = mt76_mcu_skb_send_msg(mdev, skb, MCU_UNI_CMD(SET_DBDC_PAWMS),
				    fawse);

	wetuwn eww;
}

#define MT76_CONNAC_SCAN_CHANNEW_TIME		60

int mt7925_mcu_hw_scan(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_scan_wequest *scan_weq)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_scan_wequest *sweq = &scan_weq->weq;
	int n_ssids = 0, eww, i, duwation;
	stwuct ieee80211_channew **scan_wist = sweq->channews;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct mt76_connac_mcu_scan_channew *chan;
	stwuct sk_buff *skb;

	stwuct scan_hdw_twv *hdw;
	stwuct scan_weq_twv *weq;
	stwuct scan_ssid_twv *ssid;
	stwuct scan_bssid_twv *bssid;
	stwuct scan_chan_info_twv *chan_info;
	stwuct scan_ie_twv *ie;
	stwuct scan_misc_twv *misc;
	stwuct twv *twv;
	int max_wen;

	max_wen = sizeof(*hdw) + sizeof(*weq) + sizeof(*ssid) +
				sizeof(*bssid) + sizeof(*chan_info) +
				sizeof(*misc) + sizeof(*ie);

	skb = mt76_mcu_msg_awwoc(mdev, NUWW, max_wen);
	if (!skb)
		wetuwn -ENOMEM;

	set_bit(MT76_HW_SCANNING, &phy->state);
	mvif->scan_seq_num = (mvif->scan_seq_num + 1) & 0x7f;

	hdw = (stwuct scan_hdw_twv *)skb_put(skb, sizeof(*hdw));
	hdw->seq_num = mvif->scan_seq_num | mvif->band_idx << 7;
	hdw->bss_idx = mvif->idx;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_WEQ, sizeof(*weq));
	weq = (stwuct scan_weq_twv *)twv;
	weq->scan_type = sweq->n_ssids ? 1 : 0;
	weq->pwobe_weq_num = sweq->n_ssids ? 2 : 0;

	duwation = MT76_CONNAC_SCAN_CHANNEW_TIME;
	/* incwease channew time fow passive scan */
	if (!sweq->n_ssids)
		duwation *= 2;
	weq->timeout_vawue = cpu_to_we16(sweq->n_channews * duwation);
	weq->channew_min_dweww_time = cpu_to_we16(duwation);
	weq->channew_dweww_time = cpu_to_we16(duwation);

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_SSID, sizeof(*ssid));
	ssid = (stwuct scan_ssid_twv *)twv;
	fow (i = 0; i < sweq->n_ssids; i++) {
		if (!sweq->ssids[i].ssid_wen)
			continue;

		ssid->ssids[i].ssid_wen = cpu_to_we32(sweq->ssids[i].ssid_wen);
		memcpy(ssid->ssids[i].ssid, sweq->ssids[i].ssid,
		       sweq->ssids[i].ssid_wen);
		n_ssids++;
	}
	ssid->ssid_type = n_ssids ? BIT(2) : BIT(0);
	ssid->ssids_num = n_ssids;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_BSSID, sizeof(*bssid));
	bssid = (stwuct scan_bssid_twv *)twv;

	memcpy(bssid->bssid, sweq->bssid, ETH_AWEN);

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_CHANNEW, sizeof(*chan_info));
	chan_info = (stwuct scan_chan_info_twv *)twv;
	chan_info->channews_num = min_t(u8, sweq->n_channews,
					AWWAY_SIZE(chan_info->channews));
	fow (i = 0; i < chan_info->channews_num; i++) {
		chan = &chan_info->channews[i];

		switch (scan_wist[i]->band) {
		case NW80211_BAND_2GHZ:
			chan->band = 1;
			bweak;
		case NW80211_BAND_6GHZ:
			chan->band = 3;
			bweak;
		defauwt:
			chan->band = 2;
			bweak;
		}
		chan->channew_num = scan_wist[i]->hw_vawue;
	}
	chan_info->channew_type = sweq->n_channews ? 4 : 0;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_IE, sizeof(*ie));
	ie = (stwuct scan_ie_twv *)twv;
	if (sweq->ie_wen > 0) {
		memcpy(ie->ies, sweq->ie, sweq->ie_wen);
		ie->ies_wen = cpu_to_we16(sweq->ie_wen);
	}

	weq->scan_func |= SCAN_FUNC_SPWIT_SCAN;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_MISC, sizeof(*misc));
	misc = (stwuct scan_misc_twv *)twv;
	if (sweq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
		get_wandom_mask_addw(misc->wandom_mac, sweq->mac_addw,
				     sweq->mac_addw_mask);
		weq->scan_func |= SCAN_FUNC_WANDOM_MAC;
	}

	eww = mt76_mcu_skb_send_msg(mdev, skb, MCU_UNI_CMD(SCAN_WEQ),
				    fawse);
	if (eww < 0)
		cweaw_bit(MT76_HW_SCANNING, &phy->state);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_hw_scan);

int mt7925_mcu_sched_scan_weq(stwuct mt76_phy *phy,
			      stwuct ieee80211_vif *vif,
			      stwuct cfg80211_sched_scan_wequest *sweq)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct ieee80211_channew **scan_wist = sweq->channews;
	stwuct mt76_connac_mcu_scan_channew *chan;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct cfg80211_match_set *cfg_match;
	stwuct cfg80211_ssid *cfg_ssid;

	stwuct scan_hdw_twv *hdw;
	stwuct scan_sched_weq *weq;
	stwuct scan_ssid_twv *ssid;
	stwuct scan_chan_info_twv *chan_info;
	stwuct scan_ie_twv *ie;
	stwuct scan_sched_ssid_match_sets *match;
	stwuct sk_buff *skb;
	stwuct twv *twv;
	int i, max_wen;

	max_wen = sizeof(*hdw) + sizeof(*weq) + sizeof(*ssid) +
		  sizeof(*chan_info) + sizeof(*ie) +
		  sizeof(*match);

	skb = mt76_mcu_msg_awwoc(mdev, NUWW, max_wen);
	if (!skb)
		wetuwn -ENOMEM;

	mvif->scan_seq_num = (mvif->scan_seq_num + 1) & 0x7f;

	hdw = (stwuct scan_hdw_twv *)skb_put(skb, sizeof(*hdw));
	hdw->seq_num = mvif->scan_seq_num | mvif->band_idx << 7;
	hdw->bss_idx = mvif->idx;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_SCHED_WEQ, sizeof(*weq));
	weq = (stwuct scan_sched_weq *)twv;
	weq->vewsion = 1;

	if (sweq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW)
		weq->scan_func |= SCAN_FUNC_WANDOM_MAC;

	weq->intewvaws_num = sweq->n_scan_pwans;
	fow (i = 0; i < weq->intewvaws_num; i++)
		weq->intewvaws[i] = cpu_to_we16(sweq->scan_pwans[i].intewvaw);

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_SSID, sizeof(*ssid));
	ssid = (stwuct scan_ssid_twv *)twv;

	ssid->ssids_num = sweq->n_ssids;
	ssid->ssid_type = BIT(2);
	fow (i = 0; i < ssid->ssids_num; i++) {
		cfg_ssid = &sweq->ssids[i];
		memcpy(ssid->ssids[i].ssid, cfg_ssid->ssid, cfg_ssid->ssid_wen);
		ssid->ssids[i].ssid_wen = cpu_to_we32(cfg_ssid->ssid_wen);
	}

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_SSID_MATCH_SETS, sizeof(*match));
	match = (stwuct scan_sched_ssid_match_sets *)twv;
	match->match_num = sweq->n_match_sets;
	fow (i = 0; i < match->match_num; i++) {
		cfg_match = &sweq->match_sets[i];
		memcpy(match->match[i].ssid, cfg_match->ssid.ssid,
		       cfg_match->ssid.ssid_wen);
		match->match[i].wssi_th = cpu_to_we32(cfg_match->wssi_thowd);
		match->match[i].ssid_wen = cfg_match->ssid.ssid_wen;
	}

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_CHANNEW, sizeof(*chan_info));
	chan_info = (stwuct scan_chan_info_twv *)twv;
	chan_info->channews_num = min_t(u8, sweq->n_channews,
					AWWAY_SIZE(chan_info->channews));
	fow (i = 0; i < chan_info->channews_num; i++) {
		chan = &chan_info->channews[i];

		switch (scan_wist[i]->band) {
		case NW80211_BAND_2GHZ:
			chan->band = 1;
			bweak;
		case NW80211_BAND_6GHZ:
			chan->band = 3;
			bweak;
		defauwt:
			chan->band = 2;
			bweak;
		}
		chan->channew_num = scan_wist[i]->hw_vawue;
	}
	chan_info->channew_type = sweq->n_channews ? 4 : 0;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_IE, sizeof(*ie));
	ie = (stwuct scan_ie_twv *)twv;
	if (sweq->ie_wen > 0) {
		memcpy(ie->ies, sweq->ie, sweq->ie_wen);
		ie->ies_wen = cpu_to_we16(sweq->ie_wen);
	}

	wetuwn mt76_mcu_skb_send_msg(mdev, skb, MCU_UNI_CMD(SCAN_WEQ),
				     fawse);
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_sched_scan_weq);

int
mt7925_mcu_sched_scan_enabwe(stwuct mt76_phy *phy,
			     stwuct ieee80211_vif *vif,
			     boow enabwe)
{
	stwuct mt76_dev *mdev = phy->dev;
	stwuct scan_sched_enabwe *weq;
	stwuct scan_hdw_twv *hdw;
	stwuct sk_buff *skb;
	stwuct twv *twv;
	int max_wen;

	max_wen = sizeof(*hdw) + sizeof(*weq);

	skb = mt76_mcu_msg_awwoc(mdev, NUWW, max_wen);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = (stwuct scan_hdw_twv *)skb_put(skb, sizeof(*hdw));
	hdw->seq_num = 0;
	hdw->bss_idx = 0;

	twv = mt76_connac_mcu_add_twv(skb, UNI_SCAN_SCHED_ENABWE, sizeof(*weq));
	weq = (stwuct scan_sched_enabwe *)twv;
	weq->active = !enabwe;

	if (enabwe)
		set_bit(MT76_HW_SCHED_SCANNING, &phy->state);
	ewse
		cweaw_bit(MT76_HW_SCHED_SCANNING, &phy->state);

	wetuwn mt76_mcu_skb_send_msg(mdev, skb, MCU_UNI_CMD(SCAN_WEQ),
				     fawse);
}

int mt7925_mcu_cancew_hw_scan(stwuct mt76_phy *phy,
			      stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct scan_hdw {
			u8 seq_num;
			u8 bss_idx;
			u8 pad[2];
		} __packed hdw;
		stwuct scan_cancew_twv {
			__we16 tag;
			__we16 wen;
			u8 is_ext_channew;
			u8 wsv[3];
		} __packed cancew;
	} weq = {
		.hdw = {
			.seq_num = mvif->scan_seq_num,
			.bss_idx = mvif->idx,
		},
		.cancew = {
			.tag = cpu_to_we16(UNI_SCAN_CANCEW),
			.wen = cpu_to_we16(sizeof(stwuct scan_cancew_twv)),
		},
	};

	if (test_and_cweaw_bit(MT76_HW_SCANNING, &phy->state)) {
		stwuct cfg80211_scan_info info = {
			.abowted = twue,
		};

		ieee80211_scan_compweted(phy->hw, &info);
	}

	wetuwn mt76_mcu_send_msg(phy->dev, MCU_UNI_CMD(SCAN_WEQ),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_cancew_hw_scan);

int mt7925_mcu_set_channew_domain(stwuct mt76_phy *phy)
{
	int wen, i, n_max_channews, n_2ch = 0, n_5ch = 0, n_6ch = 0;
	stwuct {
		stwuct {
			u8 awpha2[4]; /* weguwatowy_wequest.awpha2 */
			u8 bw_2g; /* BW_20_40M		0
				   * BW_20M		1
				   * BW_20_40_80M	2
				   * BW_20_40_80_160M	3
				   * BW_20_40_80_8080M	4
				   */
			u8 bw_5g;
			u8 bw_6g;
			u8 pad;
		} __packed hdw;
		stwuct n_chan {
			__we16 tag;
			__we16 wen;
			u8 n_2ch;
			u8 n_5ch;
			u8 n_6ch;
			u8 pad;
		} __packed n_ch;
	} weq = {
		.hdw = {
			.bw_2g = 0,
			.bw_5g = 3, /* BW_20_40_80_160M */
			.bw_6g = 3,
		},
		.n_ch = {
			.tag = cpu_to_we16(2),
		},
	};
	stwuct mt76_connac_mcu_chan {
		__we16 hw_vawue;
		__we16 pad;
		__we32 fwags;
	} __packed channew;
	stwuct mt76_dev *dev = phy->dev;
	stwuct ieee80211_channew *chan;
	stwuct sk_buff *skb;

	n_max_channews = phy->sband_2g.sband.n_channews +
			 phy->sband_5g.sband.n_channews +
			 phy->sband_6g.sband.n_channews;
	wen = sizeof(weq) + n_max_channews * sizeof(channew);

	skb = mt76_mcu_msg_awwoc(dev, NUWW, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, sizeof(weq));

	fow (i = 0; i < phy->sband_2g.sband.n_channews; i++) {
		chan = &phy->sband_2g.sband.channews[i];
		if (chan->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		channew.hw_vawue = cpu_to_we16(chan->hw_vawue);
		channew.fwags = cpu_to_we32(chan->fwags);
		channew.pad = 0;

		skb_put_data(skb, &channew, sizeof(channew));
		n_2ch++;
	}
	fow (i = 0; i < phy->sband_5g.sband.n_channews; i++) {
		chan = &phy->sband_5g.sband.channews[i];
		if (chan->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		channew.hw_vawue = cpu_to_we16(chan->hw_vawue);
		channew.fwags = cpu_to_we32(chan->fwags);
		channew.pad = 0;

		skb_put_data(skb, &channew, sizeof(channew));
		n_5ch++;
	}
	fow (i = 0; i < phy->sband_6g.sband.n_channews; i++) {
		chan = &phy->sband_6g.sband.channews[i];
		if (chan->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		channew.hw_vawue = cpu_to_we16(chan->hw_vawue);
		channew.fwags = cpu_to_we32(chan->fwags);
		channew.pad = 0;

		skb_put_data(skb, &channew, sizeof(channew));
		n_6ch++;
	}

	BUIWD_BUG_ON(sizeof(dev->awpha2) > sizeof(weq.hdw.awpha2));
	memcpy(weq.hdw.awpha2, dev->awpha2, sizeof(dev->awpha2));
	weq.n_ch.n_2ch = n_2ch;
	weq.n_ch.n_5ch = n_5ch;
	weq.n_ch.n_6ch = n_6ch;
	wen = sizeof(stwuct n_chan) + (n_2ch + n_5ch + n_6ch) * sizeof(channew);
	weq.n_ch.wen = cpu_to_we16(wen);
	memcpy(__skb_push(skb, sizeof(weq)), &weq, sizeof(weq));

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD(SET_DOMAIN_INFO),
				     fawse);
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_set_channew_domain);

static int
__mt7925_mcu_set_cwc(stwuct mt792x_dev *dev, u8 *awpha2,
		     enum enviwonment_cap env_cap,
		     stwuct mt7925_cwc *cwc, u8 idx)
{
	stwuct mt7925_cwc_segment *seg;
	stwuct sk_buff *skb;
	stwuct {
		u8 wsv[4];
		__we16 tag;
		__we16 wen;

		u8 vew;
		u8 pad0;
		__we16 size;
		u8 idx;
		u8 env;
		u8 acpi_conf;
		u8 pad1;
		u8 awpha2[2];
		u8 type[2];
		u8 wsvd[64];
	} __packed weq = {
		.tag = cpu_to_we16(0x3),
		.wen = cpu_to_we16(sizeof(weq) - 4),

		.idx = idx,
		.env = env_cap,
		.acpi_conf = mt792x_acpi_get_fwags(&dev->phy),
	};
	int wet, vawid_cnt = 0;
	u8 i, *pos;

	if (!cwc)
		wetuwn 0;

	pos = cwc->data + sizeof(*seg) * cwc->nw_seg;
	fow (i = 0; i < cwc->nw_countwy; i++) {
		stwuct mt7925_cwc_wuwe *wuwe = (stwuct mt7925_cwc_wuwe *)pos;

		pos += sizeof(*wuwe);
		if (wuwe->awpha2[0] != awpha2[0] ||
		    wuwe->awpha2[1] != awpha2[1])
			continue;

		seg = (stwuct mt7925_cwc_segment *)cwc->data
			  + wuwe->seg_idx - 1;

		memcpy(weq.awpha2, wuwe->awpha2, 2);
		memcpy(weq.type, wuwe->type, 2);

		weq.size = cpu_to_we16(seg->wen);
		skb = __mt76_mcu_msg_awwoc(&dev->mt76, &weq,
					   we16_to_cpu(weq.size) + sizeof(weq),
					   sizeof(weq), GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;
		skb_put_data(skb, cwc->data + seg->offset, seg->wen);

		wet = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					    MCU_UNI_CMD(SET_POWEW_WIMIT),
					    twue);
		if (wet < 0)
			wetuwn wet;
		vawid_cnt++;
	}

	if (!vawid_cnt)
		wetuwn -ENOENT;

	wetuwn 0;
}

int mt7925_mcu_set_cwc(stwuct mt792x_dev *dev, u8 *awpha2,
		       enum enviwonment_cap env_cap)
{
	stwuct mt792x_phy *phy = (stwuct mt792x_phy *)&dev->phy;
	int i, wet;

	/* submit aww cwc config */
	fow (i = 0; i < AWWAY_SIZE(phy->cwc); i++) {
		wet = __mt7925_mcu_set_cwc(dev, awpha2, env_cap,
					   phy->cwc[i], i);

		/* If no countwy found, set "00" as defauwt */
		if (wet == -ENOENT)
			wet = __mt7925_mcu_set_cwc(dev, "00",
						   ENVIWON_INDOOW,
						   phy->cwc[i], i);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

int mt7925_mcu_fiww_message(stwuct mt76_dev *mdev, stwuct sk_buff *skb,
			    int cmd, int *wait_seq)
{
	int txd_wen, mcu_cmd = FIEWD_GET(__MCU_CMD_FIEWD_ID, cmd);
	stwuct mt76_connac2_mcu_uni_txd *uni_txd;
	stwuct mt76_connac2_mcu_txd *mcu_txd;
	__we32 *txd;
	u32 vaw;
	u8 seq;

	/* TODO: make dynamic based on msg type */
	mdev->mcu.timeout = 20 * HZ;

	seq = ++mdev->mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++mdev->mcu.msg_seq & 0xf;

	if (cmd == MCU_CMD(FW_SCATTEW))
		goto exit;

	txd_wen = cmd & __MCU_CMD_FIEWD_UNI ? sizeof(*uni_txd) : sizeof(*mcu_txd);
	txd = (__we32 *)skb_push(skb, txd_wen);

	vaw = FIEWD_PWEP(MT_TXD0_TX_BYTES, skb->wen) |
	      FIEWD_PWEP(MT_TXD0_PKT_FMT, MT_TX_TYPE_CMD) |
	      FIEWD_PWEP(MT_TXD0_Q_IDX, MT_TX_MCU_POWT_WX_Q0);
	txd[0] = cpu_to_we32(vaw);

	vaw = FIEWD_PWEP(MT_TXD1_HDW_FOWMAT, MT_HDW_FOWMAT_CMD);
	txd[1] = cpu_to_we32(vaw);

	if (cmd & __MCU_CMD_FIEWD_UNI) {
		uni_txd = (stwuct mt76_connac2_mcu_uni_txd *)txd;
		uni_txd->wen = cpu_to_we16(skb->wen - sizeof(uni_txd->txd));
		uni_txd->option = MCU_CMD_UNI_EXT_ACK;
		uni_txd->cid = cpu_to_we16(mcu_cmd);
		uni_txd->s2d_index = MCU_S2D_H2N;
		uni_txd->pkt_type = MCU_PKT_ID;
		uni_txd->seq = seq;

		goto exit;
	}

	mcu_txd = (stwuct mt76_connac2_mcu_txd *)txd;
	mcu_txd->wen = cpu_to_we16(skb->wen - sizeof(mcu_txd->txd));
	mcu_txd->pq_id = cpu_to_we16(MCU_PQ_ID(MT_TX_POWT_IDX_MCU,
					       MT_TX_MCU_POWT_WX_Q0));
	mcu_txd->pkt_type = MCU_PKT_ID;
	mcu_txd->seq = seq;
	mcu_txd->cid = mcu_cmd;
	mcu_txd->ext_cid = FIEWD_GET(__MCU_CMD_FIEWD_EXT_ID, cmd);

	if (mcu_txd->ext_cid || (cmd & __MCU_CMD_FIEWD_CE)) {
		if (cmd & __MCU_CMD_FIEWD_QUEWY)
			mcu_txd->set_quewy = MCU_Q_QUEWY;
		ewse
			mcu_txd->set_quewy = MCU_Q_SET;
		mcu_txd->ext_cid_ack = !!mcu_txd->ext_cid;
	} ewse {
		mcu_txd->set_quewy = MCU_Q_NA;
	}

	if (cmd & __MCU_CMD_FIEWD_WA)
		mcu_txd->s2d_index = MCU_S2D_H2C;
	ewse
		mcu_txd->s2d_index = MCU_S2D_H2N;

exit:
	if (wait_seq)
		*wait_seq = seq;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7925_mcu_fiww_message);

int mt7925_mcu_set_wts_thwesh(stwuct mt792x_phy *phy, u32 vaw)
{
	stwuct {
		u8 band_idx;
		u8 _wsv[3];

		__we16 tag;
		__we16 wen;
		__we32 wen_thwesh;
		__we32 pkt_thwesh;
	} __packed weq = {
		.band_idx = phy->mt76->band_idx,
		.tag = cpu_to_we16(UNI_BAND_CONFIG_WTS_THWESHOWD),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.wen_thwesh = cpu_to_we32(vaw),
		.pkt_thwesh = cpu_to_we32(0x2),
	};

	wetuwn mt76_mcu_send_msg(&phy->dev->mt76, MCU_UNI_CMD(BAND_CONFIG),
				 &weq, sizeof(weq), twue);
}

int mt7925_mcu_set_wadio_en(stwuct mt792x_phy *phy, boow enabwe)
{
	stwuct {
		u8 band_idx;
		u8 _wsv[3];

		__we16 tag;
		__we16 wen;
		u8 enabwe;
		u8 _wsv2[3];
	} __packed weq = {
		.band_idx = phy->mt76->band_idx,
		.tag = cpu_to_we16(UNI_BAND_CONFIG_WADIO_ENABWE),
		.wen = cpu_to_we16(sizeof(weq) - 4),
		.enabwe = enabwe,
	};

	wetuwn mt76_mcu_send_msg(&phy->dev->mt76, MCU_UNI_CMD(BAND_CONFIG),
				 &weq, sizeof(weq), twue);
}

static void
mt7925_mcu_buiwd_sku(stwuct mt76_dev *dev, s8 *sku,
		     stwuct mt76_powew_wimits *wimits,
		     enum nw80211_band band)
{
	int i, offset = sizeof(wimits->cck);

	memset(sku, 127, MT_CONNAC3_SKU_POWEW_WIMIT);

	if (band == NW80211_BAND_2GHZ) {
		/* cck */
		memcpy(sku, wimits->cck, sizeof(wimits->cck));
	}

	/* ofdm */
	memcpy(&sku[offset], wimits->ofdm, sizeof(wimits->ofdm));
	offset += (sizeof(wimits->ofdm) * 5);

	/* ht */
	fow (i = 0; i < 2; i++) {
		memcpy(&sku[offset], wimits->mcs[i], 8);
		offset += 8;
	}
	sku[offset++] = wimits->mcs[0][0];

	/* vht */
	fow (i = 0; i < AWWAY_SIZE(wimits->mcs); i++) {
		memcpy(&sku[offset], wimits->mcs[i],
		       AWWAY_SIZE(wimits->mcs[i]));
		offset += 12;
	}

	/* he */
	fow (i = 0; i < AWWAY_SIZE(wimits->wu); i++) {
		memcpy(&sku[offset], wimits->wu[i], AWWAY_SIZE(wimits->wu[i]));
		offset += AWWAY_SIZE(wimits->wu[i]);
	}

	/* eht */
	fow (i = 0; i < AWWAY_SIZE(wimits->eht); i++) {
		memcpy(&sku[offset], wimits->eht[i], AWWAY_SIZE(wimits->eht[i]));
		offset += AWWAY_SIZE(wimits->eht[i]);
	}
}

static int
mt7925_mcu_wate_txpowew_band(stwuct mt76_phy *phy,
			     enum nw80211_band band)
{
	int tx_powew, n_chan, wast_ch, eww = 0, idx = 0;
	int i, sku_wen, batch_size, batch_wen = 3;
	stwuct mt76_dev *dev = phy->dev;
	static const u8 chan_wist_2ghz[] = {
		1, 2,  3,  4,  5,  6,  7,
		8, 9, 10, 11, 12, 13, 14
	};
	static const u8 chan_wist_5ghz[] = {
		 36,  38,  40,  42,  44,  46,  48,
		 50,  52,  54,  56,  58,  60,  62,
		 64, 100, 102, 104, 106, 108, 110,
		112, 114, 116, 118, 120, 122, 124,
		126, 128, 132, 134, 136, 138, 140,
		142, 144, 149, 151, 153, 155, 157,
		159, 161, 165, 167
	};
	static const u8 chan_wist_6ghz[] = {
		  1,   3,   5,   7,   9,  11,  13,
		 15,  17,  19,  21,  23,  25,  27,
		 29,  33,  35,  37,  39,  41,  43,
		 45,  47,  49,  51,  53,  55,  57,
		 59,  61,  65,  67,  69,  71,  73,
		 75,  77,  79,  81,  83,  85,  87,
		 89,  91,  93,  97,  99, 101, 103,
		105, 107, 109, 111, 113, 115, 117,
		119, 121, 123, 125, 129, 131, 133,
		135, 137, 139, 141, 143, 145, 147,
		149, 151, 153, 155, 157, 161, 163,
		165, 167, 169, 171, 173, 175, 177,
		179, 181, 183, 185, 187, 189, 193,
		195, 197, 199, 201, 203, 205, 207,
		209, 211, 213, 215, 217, 219, 221,
		225, 227, 229, 233
	};
	stwuct mt76_powew_wimits *wimits;
	stwuct mt7925_sku_twv *sku_twbv;
	const u8 *ch_wist;

	sku_wen = sizeof(*sku_twbv);
	tx_powew = 2 * phy->hw->conf.powew_wevew;
	if (!tx_powew)
		tx_powew = 127;

	if (band == NW80211_BAND_2GHZ) {
		n_chan = AWWAY_SIZE(chan_wist_2ghz);
		ch_wist = chan_wist_2ghz;
		wast_ch = chan_wist_2ghz[AWWAY_SIZE(chan_wist_2ghz) - 1];
	} ewse if (band == NW80211_BAND_6GHZ) {
		n_chan = AWWAY_SIZE(chan_wist_6ghz);
		ch_wist = chan_wist_6ghz;
		wast_ch = chan_wist_6ghz[AWWAY_SIZE(chan_wist_6ghz) - 1];
	} ewse {
		n_chan = AWWAY_SIZE(chan_wist_5ghz);
		ch_wist = chan_wist_5ghz;
		wast_ch = chan_wist_5ghz[AWWAY_SIZE(chan_wist_5ghz) - 1];
	}
	batch_size = DIV_WOUND_UP(n_chan, batch_wen);

	wimits = devm_kmawwoc(dev->dev, sizeof(*wimits), GFP_KEWNEW);
	if (!wimits)
		wetuwn -ENOMEM;

	sku_twbv = devm_kmawwoc(dev->dev, sku_wen, GFP_KEWNEW);
	if (!sku_twbv) {
		devm_kfwee(dev->dev, wimits);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < batch_size; i++) {
		stwuct mt7925_tx_powew_wimit_twv *tx_powew_twv;
		int j, msg_wen, num_ch;
		stwuct sk_buff *skb;

		num_ch = i == batch_size - 1 ? n_chan % batch_wen : batch_wen;
		msg_wen = sizeof(*tx_powew_twv) + num_ch * sku_wen;
		skb = mt76_mcu_msg_awwoc(dev, NUWW, msg_wen);
		if (!skb) {
			eww = -ENOMEM;
			goto out;
		}

		tx_powew_twv = (stwuct mt7925_tx_powew_wimit_twv *)
			       skb_put(skb, sizeof(*tx_powew_twv));

		BUIWD_BUG_ON(sizeof(dev->awpha2) > sizeof(tx_powew_twv->awpha2));
		memcpy(tx_powew_twv->awpha2, dev->awpha2, sizeof(dev->awpha2));
		tx_powew_twv->n_chan = num_ch;
		tx_powew_twv->tag = cpu_to_we16(0x1);
		tx_powew_twv->wen = cpu_to_we16(sizeof(*tx_powew_twv));

		switch (band) {
		case NW80211_BAND_2GHZ:
			tx_powew_twv->band = 1;
			bweak;
		case NW80211_BAND_6GHZ:
			tx_powew_twv->band = 3;
			bweak;
		defauwt:
			tx_powew_twv->band = 2;
			bweak;
		}

		fow (j = 0; j < num_ch; j++, idx++) {
			stwuct ieee80211_channew chan = {
				.hw_vawue = ch_wist[idx],
				.band = band,
			};
			s8 weg_powew, saw_powew;

			weg_powew = mt76_connac_get_ch_powew(phy, &chan,
							     tx_powew);
			saw_powew = mt76_get_saw_powew(phy, &chan, weg_powew);

			mt76_get_wate_powew_wimits(phy, &chan, wimits,
						   saw_powew);

			tx_powew_twv->wast_msg = ch_wist[idx] == wast_ch;
			sku_twbv->channew = ch_wist[idx];

			mt7925_mcu_buiwd_sku(dev, sku_twbv->pww_wimit,
					     wimits, band);
			skb_put_data(skb, sku_twbv, sku_wen);
		}
		eww = mt76_mcu_skb_send_msg(dev, skb,
					    MCU_UNI_CMD(SET_POWEW_WIMIT),
					    twue);
		if (eww < 0)
			goto out;
	}

out:
	devm_kfwee(dev->dev, sku_twbv);
	devm_kfwee(dev->dev, wimits);
	wetuwn eww;
}

int mt7925_mcu_set_wate_txpowew(stwuct mt76_phy *phy)
{
	int eww;

	if (phy->cap.has_2ghz) {
		eww = mt7925_mcu_wate_txpowew_band(phy,
						   NW80211_BAND_2GHZ);
		if (eww < 0)
			wetuwn eww;
	}

	if (phy->cap.has_5ghz) {
		eww = mt7925_mcu_wate_txpowew_band(phy,
						   NW80211_BAND_5GHZ);
		if (eww < 0)
			wetuwn eww;
	}

	if (phy->cap.has_6ghz) {
		eww = mt7925_mcu_wate_txpowew_band(phy,
						   NW80211_BAND_6GHZ);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

int mt7925_mcu_set_wxfiwtew(stwuct mt792x_dev *dev, u32 fif,
			    u8 bit_op, u32 bit_map)
{
	stwuct mt792x_phy *phy = &dev->phy;
	stwuct {
		u8 band_idx;
		u8 wsv1[3];

		__we16 tag;
		__we16 wen;
		u8 mode;
		u8 wsv2[3];
		__we32 fif;
		__we32 bit_map; /* bit_* fow bitmap update */
		u8 bit_op;
		u8 pad[51];
	} __packed weq = {
		.band_idx = phy->mt76->band_idx,
		.tag = cpu_to_we16(UNI_BAND_CONFIG_SET_MAC80211_WX_FIWTEW),
		.wen = cpu_to_we16(sizeof(weq) - 4),

		.mode = fif ? 0 : 1,
		.fif = cpu_to_we32(fif),
		.bit_map = cpu_to_we32(bit_map),
		.bit_op = bit_op,
	};

	wetuwn mt76_mcu_send_msg(&phy->dev->mt76, MCU_UNI_CMD(BAND_CONFIG),
				 &weq, sizeof(weq), twue);
}
