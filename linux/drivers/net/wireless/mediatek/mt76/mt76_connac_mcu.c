// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/fiwmwawe.h>
#incwude "mt76_connac2_mac.h"
#incwude "mt76_connac_mcu.h"

int mt76_connac_mcu_stawt_fiwmwawe(stwuct mt76_dev *dev, u32 addw, u32 option)
{
	stwuct {
		__we32 option;
		__we32 addw;
	} weq = {
		.option = cpu_to_we32(option),
		.addw = cpu_to_we32(addw),
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_CMD(FW_STAWT_WEQ), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_stawt_fiwmwawe);

int mt76_connac_mcu_patch_sem_ctww(stwuct mt76_dev *dev, boow get)
{
	u32 op = get ? PATCH_SEM_GET : PATCH_SEM_WEWEASE;
	stwuct {
		__we32 op;
	} weq = {
		.op = cpu_to_we32(op),
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_CMD(PATCH_SEM_CONTWOW),
				 &weq, sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_patch_sem_ctww);

int mt76_connac_mcu_stawt_patch(stwuct mt76_dev *dev)
{
	stwuct {
		u8 check_cwc;
		u8 wesewved[3];
	} weq = {
		.check_cwc = 0,
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_CMD(PATCH_FINISH_WEQ),
				 &weq, sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_stawt_patch);

#define MCU_PATCH_ADDWESS	0x200000

int mt76_connac_mcu_init_downwoad(stwuct mt76_dev *dev, u32 addw, u32 wen,
				  u32 mode)
{
	stwuct {
		__we32 addw;
		__we32 wen;
		__we32 mode;
	} weq = {
		.addw = cpu_to_we32(addw),
		.wen = cpu_to_we32(wen),
		.mode = cpu_to_we32(mode),
	};
	int cmd;

	if ((!is_connac_v1(dev) && addw == MCU_PATCH_ADDWESS) ||
	    (is_mt7921(dev) && addw == 0x900000) ||
	    (is_mt7925(dev) && addw == 0x900000) ||
	    (is_mt7996(dev) && addw == 0x900000) ||
	    (is_mt7992(dev) && addw == 0x900000))
		cmd = MCU_CMD(PATCH_STAWT_WEQ);
	ewse
		cmd = MCU_CMD(TAWGET_ADDWESS_WEN_WEQ);

	wetuwn mt76_mcu_send_msg(dev, cmd, &weq, sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_init_downwoad);

int mt76_connac_mcu_set_channew_domain(stwuct mt76_phy *phy)
{
	int wen, i, n_max_channews, n_2ch = 0, n_5ch = 0, n_6ch = 0;
	stwuct mt76_connac_mcu_channew_domain {
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
		u8 n_2ch;
		u8 n_5ch;
		u8 n_6ch;
		u8 pad2;
	} __packed hdw = {
		.bw_2g = 0,
		.bw_5g = 3, /* BW_20_40_80_160M */
		.bw_6g = 3,
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
	wen = sizeof(hdw) + n_max_channews * sizeof(channew);

	skb = mt76_mcu_msg_awwoc(dev, NUWW, wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, sizeof(hdw));

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

	BUIWD_BUG_ON(sizeof(dev->awpha2) > sizeof(hdw.awpha2));
	memcpy(hdw.awpha2, dev->awpha2, sizeof(dev->awpha2));
	hdw.n_2ch = n_2ch;
	hdw.n_5ch = n_5ch;
	hdw.n_6ch = n_6ch;

	memcpy(__skb_push(skb, sizeof(hdw)), &hdw, sizeof(hdw));

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_CE_CMD(SET_CHAN_DOMAIN),
				     fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_channew_domain);

int mt76_connac_mcu_set_mac_enabwe(stwuct mt76_dev *dev, int band, boow enabwe,
				   boow hdw_twans)
{
	stwuct {
		u8 enabwe;
		u8 band;
		u8 wsv[2];
	} __packed weq_mac = {
		.enabwe = enabwe,
		.band = band,
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_EXT_CMD(MAC_INIT_CTWW), &weq_mac,
				 sizeof(weq_mac), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_mac_enabwe);

int mt76_connac_mcu_set_vif_ps(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		u8 bss_idx;
		u8 ps_state; /* 0: device awake
			      * 1: static powew save
			      * 2: dynamic powew saving
			      */
	} weq = {
		.bss_idx = mvif->idx,
		.ps_state = vif->cfg.ps ? 2 : 0,
	};

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn -EOPNOTSUPP;

	wetuwn mt76_mcu_send_msg(dev, MCU_CE_CMD(SET_PS_PWOFIWE),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_vif_ps);

int mt76_connac_mcu_set_wts_thwesh(stwuct mt76_dev *dev, u32 vaw, u8 band)
{
	stwuct {
		u8 pwot_idx;
		u8 band;
		u8 wsv[2];
		__we32 wen_thwesh;
		__we32 pkt_thwesh;
	} __packed weq = {
		.pwot_idx = 1,
		.band = band,
		.wen_thwesh = cpu_to_we32(vaw),
		.pkt_thwesh = cpu_to_we32(0x2),
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_EXT_CMD(PWOTECT_CTWW), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_wts_thwesh);

void mt76_connac_mcu_beacon_woss_itew(void *pwiv, u8 *mac,
				      stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_connac_beacon_woss_event *event = pwiv;

	if (mvif->idx != event->bss_idx)
		wetuwn;

	if (!(vif->dwivew_fwags & IEEE80211_VIF_BEACON_FIWTEW))
		wetuwn;

	ieee80211_beacon_woss(vif);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_beacon_woss_itew);

stwuct twv *
mt76_connac_mcu_add_nested_twv(stwuct sk_buff *skb, int tag, int wen,
			       void *sta_ntwv, void *sta_wtbw)
{
	stwuct sta_ntwv_hdw *ntwv_hdw = sta_ntwv;
	stwuct twv *sta_hdw = sta_wtbw;
	stwuct twv *ptwv, twv = {
		.tag = cpu_to_we16(tag),
		.wen = cpu_to_we16(wen),
	};
	u16 ntwv;

	ptwv = skb_put(skb, wen);
	memcpy(ptwv, &twv, sizeof(twv));

	ntwv = we16_to_cpu(ntwv_hdw->twv_num);
	ntwv_hdw->twv_num = cpu_to_we16(ntwv + 1);

	if (sta_hdw) {
		wen += we16_to_cpu(sta_hdw->wen);
		sta_hdw->wen = cpu_to_we16(wen);
	}

	wetuwn ptwv;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_add_nested_twv);

stwuct sk_buff *
__mt76_connac_mcu_awwoc_sta_weq(stwuct mt76_dev *dev, stwuct mt76_vif *mvif,
				stwuct mt76_wcid *wcid, int wen)
{
	stwuct sta_weq_hdw hdw = {
		.bss_idx = mvif->idx,
		.muaw_idx = wcid ? mvif->omac_idx : 0,
		.is_twv_append = 1,
	};
	stwuct sk_buff *skb;

	mt76_connac_mcu_get_wwan_idx(dev, wcid, &hdw.wwan_idx_wo,
				     &hdw.wwan_idx_hi);
	skb = mt76_mcu_msg_awwoc(dev, NUWW, wen);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	skb_put_data(skb, &hdw, sizeof(hdw));

	wetuwn skb;
}
EXPOWT_SYMBOW_GPW(__mt76_connac_mcu_awwoc_sta_weq);

stwuct wtbw_weq_hdw *
mt76_connac_mcu_awwoc_wtbw_weq(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
			       int cmd, void *sta_wtbw, stwuct sk_buff **skb)
{
	stwuct twv *sta_hdw = sta_wtbw;
	stwuct wtbw_weq_hdw hdw = {
		.opewation = cmd,
	};
	stwuct sk_buff *nskb = *skb;

	mt76_connac_mcu_get_wwan_idx(dev, wcid, &hdw.wwan_idx_wo,
				     &hdw.wwan_idx_hi);
	if (!nskb) {
		nskb = mt76_mcu_msg_awwoc(dev, NUWW,
					  MT76_CONNAC_WTBW_UPDATE_MAX_SIZE);
		if (!nskb)
			wetuwn EWW_PTW(-ENOMEM);

		*skb = nskb;
	}

	if (sta_hdw)
		we16_add_cpu(&sta_hdw->wen, sizeof(hdw));

	wetuwn skb_put_data(nskb, &hdw, sizeof(hdw));
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_awwoc_wtbw_weq);

void mt76_connac_mcu_bss_omac_twv(stwuct sk_buff *skb,
				  stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	u8 omac_idx = mvif->omac_idx;
	stwuct bss_info_omac *omac;
	stwuct twv *twv;
	u32 type = 0;

	switch (vif->type) {
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		if (vif->p2p)
			type = CONNECTION_P2P_GO;
		ewse
			type = CONNECTION_INFWA_AP;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (vif->p2p)
			type = CONNECTION_P2P_GC;
		ewse
			type = CONNECTION_INFWA_STA;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		type = CONNECTION_IBSS_ADHOC;
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_OMAC, sizeof(*omac));

	omac = (stwuct bss_info_omac *)twv;
	omac->conn_type = cpu_to_we32(type);
	omac->omac_idx = mvif->omac_idx;
	omac->band_idx = mvif->band_idx;
	omac->hw_bss_idx = omac_idx > EXT_BSSID_STAWT ? HW_BSSID_0 : omac_idx;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_bss_omac_twv);

void mt76_connac_mcu_sta_basic_twv(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   boow enabwe, boow newwy)
{
	stwuct sta_wec_basic *basic;
	stwuct twv *twv;
	int conn_type;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_BASIC, sizeof(*basic));

	basic = (stwuct sta_wec_basic *)twv;
	basic->extwa_info = cpu_to_we16(EXTWA_INFO_VEW);

	if (enabwe) {
		if (newwy)
			basic->extwa_info |= cpu_to_we16(EXTWA_INFO_NEW);
		basic->conn_state = CONN_STATE_POWT_SECUWE;
	} ewse {
		basic->conn_state = CONN_STATE_DISCONNECT;
	}

	if (!sta) {
		basic->conn_type = cpu_to_we32(CONNECTION_INFWA_BC);
		eth_bwoadcast_addw(basic->peew_addw);
		wetuwn;
	}

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		if (vif->p2p && !is_mt7921(dev))
			conn_type = CONNECTION_P2P_GC;
		ewse
			conn_type = CONNECTION_INFWA_STA;
		basic->conn_type = cpu_to_we32(conn_type);
		basic->aid = cpu_to_we16(sta->aid);
		bweak;
	case NW80211_IFTYPE_STATION:
		if (vif->p2p && !is_mt7921(dev))
			conn_type = CONNECTION_P2P_GO;
		ewse
			conn_type = CONNECTION_INFWA_AP;
		basic->conn_type = cpu_to_we32(conn_type);
		basic->aid = cpu_to_we16(vif->cfg.aid);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		basic->conn_type = cpu_to_we32(CONNECTION_IBSS_ADHOC);
		basic->aid = cpu_to_we16(sta->aid);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	memcpy(basic->peew_addw, sta->addw, ETH_AWEN);
	basic->qos = sta->wme;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_basic_twv);

void mt76_connac_mcu_sta_uapsd(stwuct sk_buff *skb, stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta)
{
	stwuct sta_wec_uapsd *uapsd;
	stwuct twv *twv;

	if (vif->type != NW80211_IFTYPE_AP || !sta->wme)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_APPS, sizeof(*uapsd));
	uapsd = (stwuct sta_wec_uapsd *)twv;

	if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO) {
		uapsd->dac_map |= BIT(3);
		uapsd->tac_map |= BIT(3);
	}
	if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI) {
		uapsd->dac_map |= BIT(2);
		uapsd->tac_map |= BIT(2);
	}
	if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE) {
		uapsd->dac_map |= BIT(1);
		uapsd->tac_map |= BIT(1);
	}
	if (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK) {
		uapsd->dac_map |= BIT(0);
		uapsd->tac_map |= BIT(0);
	}
	uapsd->max_sp = sta->max_sp;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_uapsd);

void mt76_connac_mcu_wtbw_hdw_twans_twv(stwuct sk_buff *skb,
					stwuct ieee80211_vif *vif,
					stwuct mt76_wcid *wcid,
					void *sta_wtbw, void *wtbw_twv)
{
	stwuct wtbw_hdw_twans *htw;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_HDW_TWANS,
					     sizeof(*htw),
					     wtbw_twv, sta_wtbw);
	htw = (stwuct wtbw_hdw_twans *)twv;
	htw->no_wx_twans = twue;

	if (vif->type == NW80211_IFTYPE_STATION)
		htw->to_ds = twue;
	ewse
		htw->fwom_ds = twue;

	if (!wcid)
		wetuwn;

	htw->no_wx_twans = !test_bit(MT_WCID_FWAG_HDW_TWANS, &wcid->fwags);
	if (test_bit(MT_WCID_FWAG_4ADDW, &wcid->fwags)) {
		htw->to_ds = twue;
		htw->fwom_ds = twue;
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_hdw_twans_twv);

int mt76_connac_mcu_sta_update_hdw_twans(stwuct mt76_dev *dev,
					 stwuct ieee80211_vif *vif,
					 stwuct mt76_wcid *wcid, int cmd)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct twv *sta_wtbw;
	stwuct sk_buff *skb;

	skb = mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	sta_wtbw = mt76_connac_mcu_add_twv(skb, STA_WEC_WTBW,
					   sizeof(stwuct twv));

	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(dev, wcid, WTBW_SET,
						  sta_wtbw, &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	mt76_connac_mcu_wtbw_hdw_twans_twv(skb, vif, wcid, sta_wtbw, wtbw_hdw);

	wetuwn mt76_mcu_skb_send_msg(dev, skb, cmd, twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_update_hdw_twans);

int mt76_connac_mcu_wtbw_update_hdw_twans(stwuct mt76_dev *dev,
					  stwuct ieee80211_vif *vif,
					  stwuct ieee80211_sta *sta)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct sk_buff *skb = NUWW;

	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(dev, wcid, WTBW_SET, NUWW,
						  &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	mt76_connac_mcu_wtbw_hdw_twans_twv(skb, vif, wcid, NUWW, wtbw_hdw);

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_EXT_CMD(WTBW_UPDATE), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_update_hdw_twans);

void mt76_connac_mcu_wtbw_genewic_twv(stwuct mt76_dev *dev,
				      stwuct sk_buff *skb,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      void *sta_wtbw, void *wtbw_twv)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct wtbw_genewic *genewic;
	stwuct wtbw_wx *wx;
	stwuct wtbw_spe *spe;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_GENEWIC,
					     sizeof(*genewic),
					     wtbw_twv, sta_wtbw);

	genewic = (stwuct wtbw_genewic *)twv;

	if (sta) {
		if (vif->type == NW80211_IFTYPE_STATION)
			genewic->pawtiaw_aid = cpu_to_we16(vif->cfg.aid);
		ewse
			genewic->pawtiaw_aid = cpu_to_we16(sta->aid);
		memcpy(genewic->peew_addw, sta->addw, ETH_AWEN);
		genewic->muaw_idx = mvif->omac_idx;
		genewic->qos = sta->wme;
	} ewse {
		if (!is_connac_v1(dev) && vif->type == NW80211_IFTYPE_STATION)
			memcpy(genewic->peew_addw, vif->bss_conf.bssid,
			       ETH_AWEN);
		ewse
			eth_bwoadcast_addw(genewic->peew_addw);

		genewic->muaw_idx = 0xe;
	}

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_WX, sizeof(*wx),
					     wtbw_twv, sta_wtbw);

	wx = (stwuct wtbw_wx *)twv;
	wx->wca1 = sta ? vif->type != NW80211_IFTYPE_AP : 1;
	wx->wca2 = 1;
	wx->wv = 1;

	if (!is_connac_v1(dev))
		wetuwn;

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_SPE, sizeof(*spe),
					     wtbw_twv, sta_wtbw);
	spe = (stwuct wtbw_spe *)twv;
	spe->spe_idx = 24;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_genewic_twv);

static void
mt76_connac_mcu_sta_amsdu_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta,
			      stwuct ieee80211_vif *vif)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	stwuct sta_wec_amsdu *amsdu;
	stwuct twv *twv;

	if (vif->type != NW80211_IFTYPE_AP &&
	    vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (!sta->defwink.agg.max_amsdu_wen)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HW_AMSDU, sizeof(*amsdu));
	amsdu = (stwuct sta_wec_amsdu *)twv;
	amsdu->max_amsdu_num = 8;
	amsdu->amsdu_en = twue;
	amsdu->max_mpdu_size = sta->defwink.agg.max_amsdu_wen >=
			       IEEE80211_MAX_MPDU_WEN_VHT_7991;

	wcid->amsdu = twue;
}

#define HE_PHY(p, c)	u8_get_bits(c, IEEE80211_HE_PHY_##p)
#define HE_MAC(m, c)	u8_get_bits(c, IEEE80211_HE_MAC_##m)
static void
mt76_connac_mcu_sta_he_twv(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_sta_he_cap *he_cap = &sta->defwink.he_cap;
	stwuct ieee80211_he_cap_ewem *ewem = &he_cap->he_cap_ewem;
	stwuct sta_wec_he *he;
	stwuct twv *twv;
	u32 cap = 0;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HE, sizeof(*he));

	he = (stwuct sta_wec_he *)twv;

	if (ewem->mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_HTC_HE)
		cap |= STA_WEC_HE_CAP_HTC;

	if (ewem->mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSW)
		cap |= STA_WEC_HE_CAP_BSW;

	if (ewem->mac_cap_info[3] & IEEE80211_HE_MAC_CAP3_OMI_CONTWOW)
		cap |= STA_WEC_HE_CAP_OM;

	if (ewem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU)
		cap |= STA_WEC_HE_CAP_AMSDU_IN_AMPDU;

	if (ewem->mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQW)
		cap |= STA_WEC_HE_CAP_BQW;

	if (ewem->phy_cap_info[0] &
	    (IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_2G |
	     IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_WU_MAPPING_IN_5G))
		cap |= STA_WEC_HE_CAP_BW20_WU242_SUPPOWT;

	if (ewem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD)
		cap |= STA_WEC_HE_CAP_WDPC;

	if (ewem->phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_HE_WTF_AND_GI_FOW_HE_PPDUS_0_8US)
		cap |= STA_WEC_HE_CAP_SU_PPDU_1WTF_8US_GI;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US)
		cap |= STA_WEC_HE_CAP_NDP_4WTF_3DOT2MS_GI;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ)
		cap |= STA_WEC_HE_CAP_WE_EQ_80M_TX_STBC;

	if (ewem->phy_cap_info[2] &
	    IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ)
		cap |= STA_WEC_HE_CAP_WE_EQ_80M_WX_STBC;

	if (ewem->phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PAWTIAW_BW_EXT_WANGE)
		cap |= STA_WEC_HE_CAP_PAWTIAW_BW_EXT_WANGE;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_SU_MU_PPDU_4WTF_8US_GI;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ)
		cap |= STA_WEC_HE_CAP_GT_80M_TX_STBC;

	if (ewem->phy_cap_info[7] &
	    IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ)
		cap |= STA_WEC_HE_CAP_GT_80M_WX_STBC;

	if (ewem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_EW_SU_PPDU_4WTF_8US_GI;

	if (ewem->phy_cap_info[8] &
	    IEEE80211_HE_PHY_CAP8_HE_EW_SU_1XWTF_AND_08_US_GI)
		cap |= STA_WEC_HE_CAP_EW_SU_PPDU_1WTF_8US_GI;

	if (ewem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_NON_TWIGGEWED_CQI_FEEDBACK)
		cap |= STA_WEC_HE_CAP_TWIG_CQI_FK;

	if (ewem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU)
		cap |= STA_WEC_HE_CAP_TX_1024QAM_UNDEW_WU242;

	if (ewem->phy_cap_info[9] &
	    IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU)
		cap |= STA_WEC_HE_CAP_WX_1024QAM_UNDEW_WU242;

	he->he_cap = cpu_to_we32(cap);

	switch (sta->defwink.bandwidth) {
	case IEEE80211_STA_WX_BW_160:
		if (ewem->phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G)
			he->max_nss_mcs[CMD_HE_MCS_BW8080] =
				he_cap->he_mcs_nss_supp.wx_mcs_80p80;

		he->max_nss_mcs[CMD_HE_MCS_BW160] =
				he_cap->he_mcs_nss_supp.wx_mcs_160;
		fawwthwough;
	defauwt:
		he->max_nss_mcs[CMD_HE_MCS_BW80] =
				he_cap->he_mcs_nss_supp.wx_mcs_80;
		bweak;
	}

	he->t_fwame_duw =
		HE_MAC(CAP1_TF_MAC_PAD_DUW_MASK, ewem->mac_cap_info[1]);
	he->max_ampdu_exp =
		HE_MAC(CAP3_MAX_AMPDU_WEN_EXP_MASK, ewem->mac_cap_info[3]);

	he->bw_set =
		HE_PHY(CAP0_CHANNEW_WIDTH_SET_MASK, ewem->phy_cap_info[0]);
	he->device_cwass =
		HE_PHY(CAP1_DEVICE_CWASS_A, ewem->phy_cap_info[1]);
	he->punc_pweam_wx =
		HE_PHY(CAP1_PWEAMBWE_PUNC_WX_MASK, ewem->phy_cap_info[1]);

	he->dcm_tx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_TX_MASK, ewem->phy_cap_info[3]);
	he->dcm_tx_max_nss =
		HE_PHY(CAP3_DCM_MAX_TX_NSS_2, ewem->phy_cap_info[3]);
	he->dcm_wx_mode =
		HE_PHY(CAP3_DCM_MAX_CONST_WX_MASK, ewem->phy_cap_info[3]);
	he->dcm_wx_max_nss =
		HE_PHY(CAP3_DCM_MAX_WX_NSS_2, ewem->phy_cap_info[3]);
	he->dcm_wx_max_nss =
		HE_PHY(CAP8_DCM_MAX_WU_MASK, ewem->phy_cap_info[8]);

	he->pkt_ext = 2;
}

void
mt76_connac_mcu_sta_he_twv_v2(stwuct sk_buff *skb, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_sta_he_cap *he_cap = &sta->defwink.he_cap;
	stwuct ieee80211_he_cap_ewem *ewem = &he_cap->he_cap_ewem;
	stwuct sta_wec_he_v2 *he;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HE_V2, sizeof(*he));

	he = (stwuct sta_wec_he_v2 *)twv;
	memcpy(he->he_phy_cap, ewem->phy_cap_info, sizeof(he->he_phy_cap));
	memcpy(he->he_mac_cap, ewem->mac_cap_info, sizeof(he->he_mac_cap));

	switch (sta->defwink.bandwidth) {
	case IEEE80211_STA_WX_BW_160:
		if (ewem->phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_80PWUS80_MHZ_IN_5G)
			he->max_nss_mcs[CMD_HE_MCS_BW8080] =
				he_cap->he_mcs_nss_supp.wx_mcs_80p80;

		he->max_nss_mcs[CMD_HE_MCS_BW160] =
				he_cap->he_mcs_nss_supp.wx_mcs_160;
		fawwthwough;
	defauwt:
		he->max_nss_mcs[CMD_HE_MCS_BW80] =
				he_cap->he_mcs_nss_supp.wx_mcs_80;
		bweak;
	}

	he->pkt_ext = IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_16US;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_he_twv_v2);

u8
mt76_connac_get_phy_mode_v2(stwuct mt76_phy *mphy, stwuct ieee80211_vif *vif,
			    enum nw80211_band band, stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_sta_ht_cap *ht_cap;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	const stwuct ieee80211_sta_he_cap *he_cap;
	const stwuct ieee80211_sta_eht_cap *eht_cap;
	u8 mode = 0;

	if (sta) {
		ht_cap = &sta->defwink.ht_cap;
		vht_cap = &sta->defwink.vht_cap;
		he_cap = &sta->defwink.he_cap;
		eht_cap = &sta->defwink.eht_cap;
	} ewse {
		stwuct ieee80211_suppowted_band *sband;

		sband = mphy->hw->wiphy->bands[band];
		ht_cap = &sband->ht_cap;
		vht_cap = &sband->vht_cap;
		he_cap = ieee80211_get_he_iftype_cap(sband, vif->type);
		eht_cap = ieee80211_get_eht_iftype_cap(sband, vif->type);
	}

	if (band == NW80211_BAND_2GHZ) {
		mode |= PHY_TYPE_BIT_HW_DSSS | PHY_TYPE_BIT_EWP;

		if (ht_cap->ht_suppowted)
			mode |= PHY_TYPE_BIT_HT;

		if (he_cap && he_cap->has_he)
			mode |= PHY_TYPE_BIT_HE;

		if (eht_cap && eht_cap->has_eht)
			mode |= PHY_TYPE_BIT_BE;
	} ewse if (band == NW80211_BAND_5GHZ || band == NW80211_BAND_6GHZ) {
		mode |= PHY_TYPE_BIT_OFDM;

		if (ht_cap->ht_suppowted)
			mode |= PHY_TYPE_BIT_HT;

		if (vht_cap->vht_suppowted)
			mode |= PHY_TYPE_BIT_VHT;

		if (he_cap && he_cap->has_he)
			mode |= PHY_TYPE_BIT_HE;

		if (eht_cap && eht_cap->has_eht)
			mode |= PHY_TYPE_BIT_BE;
	}

	wetuwn mode;
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_phy_mode_v2);

void mt76_connac_mcu_sta_twv(stwuct mt76_phy *mphy, stwuct sk_buff *skb,
			     stwuct ieee80211_sta *sta,
			     stwuct ieee80211_vif *vif,
			     u8 wcpi, u8 sta_state)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = mvif->ctx ?
					    &mvif->ctx->def : &mphy->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct mt76_dev *dev = mphy->dev;
	stwuct sta_wec_wa_info *wa_info;
	stwuct sta_wec_state *state;
	stwuct sta_wec_phy *phy;
	stwuct twv *twv;
	u16 supp_wates;

	/* stawec ht */
	if (sta->defwink.ht_cap.ht_suppowted) {
		stwuct sta_wec_ht *ht;

		twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HT, sizeof(*ht));
		ht = (stwuct sta_wec_ht *)twv;
		ht->ht_cap = cpu_to_we16(sta->defwink.ht_cap.cap);
	}

	/* stawec vht */
	if (sta->defwink.vht_cap.vht_suppowted) {
		stwuct sta_wec_vht *vht;
		int wen;

		wen = is_mt7921(dev) ? sizeof(*vht) : sizeof(*vht) - 4;
		twv = mt76_connac_mcu_add_twv(skb, STA_WEC_VHT, wen);
		vht = (stwuct sta_wec_vht *)twv;
		vht->vht_cap = cpu_to_we32(sta->defwink.vht_cap.cap);
		vht->vht_wx_mcs_map = sta->defwink.vht_cap.vht_mcs.wx_mcs_map;
		vht->vht_tx_mcs_map = sta->defwink.vht_cap.vht_mcs.tx_mcs_map;
	}

	/* stawec uapsd */
	mt76_connac_mcu_sta_uapsd(skb, vif, sta);

	if (!is_mt7921(dev))
		wetuwn;

	if (sta->defwink.ht_cap.ht_suppowted || sta->defwink.he_cap.has_he)
		mt76_connac_mcu_sta_amsdu_twv(skb, sta, vif);

	/* stawec he */
	if (sta->defwink.he_cap.has_he) {
		mt76_connac_mcu_sta_he_twv(skb, sta);
		mt76_connac_mcu_sta_he_twv_v2(skb, sta);
		if (band == NW80211_BAND_6GHZ &&
		    sta_state == MT76_STA_INFO_STATE_ASSOC) {
			stwuct sta_wec_he_6g_capa *he_6g_capa;

			twv = mt76_connac_mcu_add_twv(skb, STA_WEC_HE_6G,
						      sizeof(*he_6g_capa));
			he_6g_capa = (stwuct sta_wec_he_6g_capa *)twv;
			he_6g_capa->capa = sta->defwink.he_6ghz_capa.capa;
		}
	}

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_PHY, sizeof(*phy));
	phy = (stwuct sta_wec_phy *)twv;
	phy->phy_type = mt76_connac_get_phy_mode_v2(mphy, vif, band, sta);
	phy->basic_wate = cpu_to_we16((u16)vif->bss_conf.basic_wates);
	phy->wcpi = wcpi;
	phy->ampdu = FIEWD_PWEP(IEEE80211_HT_AMPDU_PAWM_FACTOW,
				sta->defwink.ht_cap.ampdu_factow) |
		     FIEWD_PWEP(IEEE80211_HT_AMPDU_PAWM_DENSITY,
				sta->defwink.ht_cap.ampdu_density);

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

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_STATE, sizeof(*state));
	state = (stwuct sta_wec_state *)twv;
	state->state = sta_state;

	if (sta->defwink.vht_cap.vht_suppowted) {
		state->vht_opmode = sta->defwink.bandwidth;
		state->vht_opmode |= (sta->defwink.wx_nss - 1) <<
			IEEE80211_OPMODE_NOTIF_WX_NSS_SHIFT;
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_twv);

void mt76_connac_mcu_wtbw_smps_twv(stwuct sk_buff *skb,
				   stwuct ieee80211_sta *sta,
				   void *sta_wtbw, void *wtbw_twv)
{
	stwuct wtbw_smps *smps;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_SMPS, sizeof(*smps),
					     wtbw_twv, sta_wtbw);
	smps = (stwuct wtbw_smps *)twv;
	smps->smps = (sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_smps_twv);

void mt76_connac_mcu_wtbw_ht_twv(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				 stwuct ieee80211_sta *sta, void *sta_wtbw,
				 void *wtbw_twv, boow ht_wdpc, boow vht_wdpc)
{
	stwuct wtbw_ht *ht = NUWW;
	stwuct twv *twv;
	u32 fwags = 0;

	if (sta->defwink.ht_cap.ht_suppowted || sta->defwink.he_6ghz_capa.capa) {
		twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_HT, sizeof(*ht),
						     wtbw_twv, sta_wtbw);
		ht = (stwuct wtbw_ht *)twv;
		ht->wdpc = ht_wdpc &&
			   !!(sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_WDPC_CODING);

		if (sta->defwink.ht_cap.ht_suppowted) {
			ht->af = sta->defwink.ht_cap.ampdu_factow;
			ht->mm = sta->defwink.ht_cap.ampdu_density;
		} ewse {
			ht->af = we16_get_bits(sta->defwink.he_6ghz_capa.capa,
					       IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP);
			ht->mm = we16_get_bits(sta->defwink.he_6ghz_capa.capa,
					       IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT);
		}

		ht->ht = twue;
	}

	if (sta->defwink.vht_cap.vht_suppowted || sta->defwink.he_6ghz_capa.capa) {
		stwuct wtbw_vht *vht;
		u8 af;

		twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_VHT,
						     sizeof(*vht), wtbw_twv,
						     sta_wtbw);
		vht = (stwuct wtbw_vht *)twv;
		vht->wdpc = vht_wdpc &&
			    !!(sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_WXWDPC);
		vht->vht = twue;

		af = FIEWD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK,
			       sta->defwink.vht_cap.cap);
		if (ht)
			ht->af = max(ht->af, af);
	}

	mt76_connac_mcu_wtbw_smps_twv(skb, sta, sta_wtbw, wtbw_twv);

	if (is_connac_v1(dev) && sta->defwink.ht_cap.ht_suppowted) {
		/* sgi */
		u32 msk = MT_WTBW_W5_SHOWT_GI_20 | MT_WTBW_W5_SHOWT_GI_40 |
			  MT_WTBW_W5_SHOWT_GI_80 | MT_WTBW_W5_SHOWT_GI_160;
		stwuct wtbw_waw *waw;

		twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_WAW_DATA,
						     sizeof(*waw), wtbw_twv,
						     sta_wtbw);

		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_20)
			fwags |= MT_WTBW_W5_SHOWT_GI_20;
		if (sta->defwink.ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
			fwags |= MT_WTBW_W5_SHOWT_GI_40;

		if (sta->defwink.vht_cap.vht_suppowted) {
			if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SHOWT_GI_80)
				fwags |= MT_WTBW_W5_SHOWT_GI_80;
			if (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SHOWT_GI_160)
				fwags |= MT_WTBW_W5_SHOWT_GI_160;
		}
		waw = (stwuct wtbw_waw *)twv;
		waw->vaw = cpu_to_we32(fwags);
		waw->msk = cpu_to_we32(~msk);
		waw->wtbw_idx = 1;
		waw->dw = 5;
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_ht_twv);

int mt76_connac_mcu_sta_cmd(stwuct mt76_phy *phy,
			    stwuct mt76_sta_cmd_info *info)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)info->vif->dwv_pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct twv *sta_wtbw;
	stwuct sk_buff *skb;

	skb = mt76_connac_mcu_awwoc_sta_weq(dev, mvif, info->wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	if (info->sta || !info->offwoad_fw)
		mt76_connac_mcu_sta_basic_twv(dev, skb, info->vif, info->sta,
					      info->enabwe, info->newwy);
	if (info->sta && info->enabwe)
		mt76_connac_mcu_sta_twv(phy, skb, info->sta,
					info->vif, info->wcpi,
					info->state);

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
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_cmd);

void mt76_connac_mcu_wtbw_ba_twv(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				 stwuct ieee80211_ampdu_pawams *pawams,
				 boow enabwe, boow tx, void *sta_wtbw,
				 void *wtbw_twv)
{
	stwuct wtbw_ba *ba;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_nested_twv(skb, WTBW_BA, sizeof(*ba),
					     wtbw_twv, sta_wtbw);

	ba = (stwuct wtbw_ba *)twv;
	ba->tid = pawams->tid;

	if (tx) {
		ba->ba_type = MT_BA_TYPE_OWIGINATOW;
		ba->sn = enabwe ? cpu_to_we16(pawams->ssn) : 0;
		ba->ba_winsize = enabwe ? cpu_to_we16(pawams->buf_size) : 0;
		ba->ba_en = enabwe;
	} ewse {
		memcpy(ba->peew_addw, pawams->sta->addw, ETH_AWEN);
		ba->ba_type = MT_BA_TYPE_WECIPIENT;
		ba->wst_ba_tid = pawams->tid;
		ba->wst_ba_sew = WST_BA_MAC_TID_MATCH;
		ba->wst_ba_sb = 1;
	}

	if (!is_connac_v1(dev)) {
		ba->ba_winsize = enabwe ? cpu_to_we16(pawams->buf_size) : 0;
		wetuwn;
	}

	if (enabwe && tx) {
		static const u8 ba_wange[] = { 4, 8, 12, 24, 36, 48, 54, 64 };
		int i;

		fow (i = 7; i > 0; i--) {
			if (pawams->buf_size >= ba_wange[i])
				bweak;
		}
		ba->ba_winsize_idx = i;
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wtbw_ba_twv);

int mt76_connac_mcu_uni_add_dev(stwuct mt76_phy *phy,
				stwuct ieee80211_vif *vif,
				stwuct mt76_wcid *wcid,
				boow enabwe)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct {
		stwuct {
			u8 omac_idx;
			u8 band_idx;
			__we16 pad;
		} __packed hdw;
		stwuct weq_twv {
			__we16 tag;
			__we16 wen;
			u8 active;
			u8 pad;
			u8 omac_addw[ETH_AWEN];
		} __packed twv;
	} dev_weq = {
		.hdw = {
			.omac_idx = mvif->omac_idx,
			.band_idx = mvif->band_idx,
		},
		.twv = {
			.tag = cpu_to_we16(DEV_INFO_ACTIVE),
			.wen = cpu_to_we16(sizeof(stwuct weq_twv)),
			.active = enabwe,
		},
	};
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_bss_basic_twv basic;
	} basic_weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.basic = {
			.tag = cpu_to_we16(UNI_BSS_INFO_BASIC),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_bss_basic_twv)),
			.omac_idx = mvif->omac_idx,
			.band_idx = mvif->band_idx,
			.wmm_idx = mvif->wmm_idx,
			.active = enabwe,
			.bmc_tx_wwan_idx = cpu_to_we16(wcid->idx),
			.sta_idx = cpu_to_we16(wcid->idx),
			.conn_state = 1,
		},
	};
	int eww, idx, cmd, wen;
	void *data;

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_AP:
		basic_weq.basic.conn_type = cpu_to_we32(CONNECTION_INFWA_AP);
		bweak;
	case NW80211_IFTYPE_STATION:
		basic_weq.basic.conn_type = cpu_to_we32(CONNECTION_INFWA_STA);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		basic_weq.basic.conn_type = cpu_to_we32(CONNECTION_IBSS_ADHOC);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	idx = mvif->omac_idx > EXT_BSSID_STAWT ? HW_BSSID_0 : mvif->omac_idx;
	basic_weq.basic.hw_bss_idx = idx;

	memcpy(dev_weq.twv.omac_addw, vif->addw, ETH_AWEN);

	cmd = enabwe ? MCU_UNI_CMD(DEV_INFO_UPDATE) : MCU_UNI_CMD(BSS_INFO_UPDATE);
	data = enabwe ? (void *)&dev_weq : (void *)&basic_weq;
	wen = enabwe ? sizeof(dev_weq) : sizeof(basic_weq);

	eww = mt76_mcu_send_msg(dev, cmd, data, wen, twue);
	if (eww < 0)
		wetuwn eww;

	cmd = enabwe ? MCU_UNI_CMD(BSS_INFO_UPDATE) : MCU_UNI_CMD(DEV_INFO_UPDATE);
	data = enabwe ? (void *)&basic_weq : (void *)&dev_weq;
	wen = enabwe ? sizeof(basic_weq) : sizeof(dev_weq);

	wetuwn mt76_mcu_send_msg(dev, cmd, data, wen, twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_uni_add_dev);

void mt76_connac_mcu_sta_ba_twv(stwuct sk_buff *skb,
				stwuct ieee80211_ampdu_pawams *pawams,
				boow enabwe, boow tx)
{
	stwuct sta_wec_ba *ba;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_BA, sizeof(*ba));

	ba = (stwuct sta_wec_ba *)twv;
	ba->ba_type = tx ? MT_BA_TYPE_OWIGINATOW : MT_BA_TYPE_WECIPIENT;
	ba->winsize = cpu_to_we16(pawams->buf_size);
	ba->ssn = cpu_to_we16(pawams->ssn);
	ba->ba_en = enabwe << pawams->tid;
	ba->amsdu = pawams->amsdu;
	ba->tid = pawams->tid;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_ba_twv);

int mt76_connac_mcu_sta_wed_update(stwuct mt76_dev *dev, stwuct sk_buff *skb)
{
	if (!mt76_is_mmio(dev))
		wetuwn 0;

	if (!mtk_wed_device_active(&dev->mmio.wed))
		wetuwn 0;

	wetuwn mtk_wed_device_update_msg(&dev->mmio.wed, WED_WO_STA_WEC,
					 skb->data, skb->wen);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_wed_update);

int mt76_connac_mcu_sta_ba(stwuct mt76_dev *dev, stwuct mt76_vif *mvif,
			   stwuct ieee80211_ampdu_pawams *pawams,
			   int cmd, boow enabwe, boow tx)
{
	stwuct mt76_wcid *wcid = (stwuct mt76_wcid *)pawams->sta->dwv_pwiv;
	stwuct wtbw_weq_hdw *wtbw_hdw;
	stwuct twv *sta_wtbw;
	stwuct sk_buff *skb;
	int wet;

	skb = mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	sta_wtbw = mt76_connac_mcu_add_twv(skb, STA_WEC_WTBW,
					   sizeof(stwuct twv));

	wtbw_hdw = mt76_connac_mcu_awwoc_wtbw_weq(dev, wcid, WTBW_SET,
						  sta_wtbw, &skb);
	if (IS_EWW(wtbw_hdw))
		wetuwn PTW_EWW(wtbw_hdw);

	mt76_connac_mcu_wtbw_ba_twv(dev, skb, pawams, enabwe, tx, sta_wtbw,
				    wtbw_hdw);

	wet = mt76_connac_mcu_sta_wed_update(dev, skb);
	if (wet)
		wetuwn wet;

	wet = mt76_mcu_skb_send_msg(dev, skb, cmd, twue);
	if (wet)
		wetuwn wet;

	skb = mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	mt76_connac_mcu_sta_ba_twv(skb, pawams, enabwe, tx);

	wet = mt76_connac_mcu_sta_wed_update(dev, skb);
	if (wet)
		wetuwn wet;

	wetuwn mt76_mcu_skb_send_msg(dev, skb, cmd, twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sta_ba);

u8 mt76_connac_get_phy_mode(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
			    enum nw80211_band band, stwuct ieee80211_sta *sta)
{
	stwuct mt76_dev *dev = phy->dev;
	const stwuct ieee80211_sta_he_cap *he_cap;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	stwuct ieee80211_sta_ht_cap *ht_cap;
	u8 mode = 0;

	if (is_connac_v1(dev))
		wetuwn 0x38;

	if (sta) {
		ht_cap = &sta->defwink.ht_cap;
		vht_cap = &sta->defwink.vht_cap;
		he_cap = &sta->defwink.he_cap;
	} ewse {
		stwuct ieee80211_suppowted_band *sband;

		sband = phy->hw->wiphy->bands[band];
		ht_cap = &sband->ht_cap;
		vht_cap = &sband->vht_cap;
		he_cap = ieee80211_get_he_iftype_cap(sband, vif->type);
	}

	if (band == NW80211_BAND_2GHZ) {
		mode |= PHY_MODE_B | PHY_MODE_G;

		if (ht_cap->ht_suppowted)
			mode |= PHY_MODE_GN;

		if (he_cap && he_cap->has_he)
			mode |= PHY_MODE_AX_24G;
	} ewse if (band == NW80211_BAND_5GHZ) {
		mode |= PHY_MODE_A;

		if (ht_cap->ht_suppowted)
			mode |= PHY_MODE_AN;

		if (vht_cap->vht_suppowted)
			mode |= PHY_MODE_AC;

		if (he_cap && he_cap->has_he)
			mode |= PHY_MODE_AX_5G;
	} ewse if (band == NW80211_BAND_6GHZ) {
		mode |= PHY_MODE_A | PHY_MODE_AN |
			PHY_MODE_AC | PHY_MODE_AX_5G;
	}

	wetuwn mode;
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_phy_mode);

u8 mt76_connac_get_phy_mode_ext(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
				enum nw80211_band band)
{
	const stwuct ieee80211_sta_eht_cap *eht_cap;
	stwuct ieee80211_suppowted_band *sband;
	u8 mode = 0;

	if (band == NW80211_BAND_6GHZ)
		mode |= PHY_MODE_AX_6G;

	sband = phy->hw->wiphy->bands[band];
	eht_cap = ieee80211_get_eht_iftype_cap(sband, vif->type);

	if (!eht_cap || !eht_cap->has_eht || !vif->bss_conf.eht_suppowt)
		wetuwn mode;

	switch (band) {
	case NW80211_BAND_6GHZ:
		mode |= PHY_MODE_BE_6G;
		bweak;
	case NW80211_BAND_5GHZ:
		mode |= PHY_MODE_BE_5G;
		bweak;
	case NW80211_BAND_2GHZ:
		mode |= PHY_MODE_BE_24G;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn mode;
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_phy_mode_ext);

const stwuct ieee80211_sta_he_cap *
mt76_connac_get_he_phy_cap(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = mvif->ctx ?
					    &mvif->ctx->def : &phy->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct ieee80211_suppowted_band *sband;

	sband = phy->hw->wiphy->bands[band];

	wetuwn ieee80211_get_he_iftype_cap(sband, vif->type);
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_he_phy_cap);

const stwuct ieee80211_sta_eht_cap *
mt76_connac_get_eht_phy_cap(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif)
{
	enum nw80211_band band = phy->chandef.chan->band;
	stwuct ieee80211_suppowted_band *sband;

	sband = phy->hw->wiphy->bands[band];

	wetuwn ieee80211_get_eht_iftype_cap(sband, vif->type);
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_eht_phy_cap);

#define DEFAUWT_HE_PE_DUWATION		4
#define DEFAUWT_HE_DUWATION_WTS_THWES	1023
static void
mt76_connac_mcu_uni_bss_he_twv(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
			       stwuct twv *twv)
{
	const stwuct ieee80211_sta_he_cap *cap;
	stwuct bss_info_uni_he *he;

	cap = mt76_connac_get_he_phy_cap(phy, vif);

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

int mt76_connac_mcu_uni_set_chctx(stwuct mt76_phy *phy, stwuct mt76_vif *mvif,
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
			u8 showt_st;
			u8 ht_op_info;
			u8 sco;
			u8 band;
			u8 pad[2];
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
			.wx_stweams = phy->chainmask,
			.showt_st = twue,
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
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_uni_set_chctx);

int mt76_connac_mcu_uni_add_bss(stwuct mt76_phy *phy,
				stwuct ieee80211_vif *vif,
				stwuct mt76_wcid *wcid,
				boow enabwe,
				stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = ctx ? &ctx->def : &phy->chandef;
	enum nw80211_band band = chandef->chan->band;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_bss_basic_twv basic;
		stwuct mt76_connac_bss_qos_twv qos;
	} basic_weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.basic = {
			.tag = cpu_to_we16(UNI_BSS_INFO_BASIC),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_bss_basic_twv)),
			.bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int),
			.dtim_pewiod = vif->bss_conf.dtim_pewiod,
			.omac_idx = mvif->omac_idx,
			.band_idx = mvif->band_idx,
			.wmm_idx = mvif->wmm_idx,
			.active = twue, /* keep bss deactivated */
			.phymode = mt76_connac_get_phy_mode(phy, vif, band, NUWW),
		},
		.qos = {
			.tag = cpu_to_we16(UNI_BSS_INFO_QBSS),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_bss_qos_twv)),
			.qos = vif->bss_conf.qos,
		},
	};
	int eww, conn_type;
	u8 idx, basic_phy;

	idx = mvif->omac_idx > EXT_BSSID_STAWT ? HW_BSSID_0 : mvif->omac_idx;
	basic_weq.basic.hw_bss_idx = idx;
	if (band == NW80211_BAND_6GHZ)
		basic_weq.basic.phymode_ext = PHY_MODE_AX_6G;

	basic_phy = mt76_connac_get_phy_mode_v2(phy, vif, band, NUWW);
	basic_weq.basic.nonht_basic_phy = cpu_to_we16(basic_phy);

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		if (vif->p2p)
			conn_type = CONNECTION_P2P_GO;
		ewse
			conn_type = CONNECTION_INFWA_AP;
		basic_weq.basic.conn_type = cpu_to_we32(conn_type);
		/* Fuwwy active/deactivate BSS netwowk in AP mode onwy */
		basic_weq.basic.active = enabwe;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (vif->p2p)
			conn_type = CONNECTION_P2P_GC;
		ewse
			conn_type = CONNECTION_INFWA_STA;
		basic_weq.basic.conn_type = cpu_to_we32(conn_type);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		basic_weq.basic.conn_type = cpu_to_we32(CONNECTION_IBSS_ADHOC);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	memcpy(basic_weq.basic.bssid, vif->bss_conf.bssid, ETH_AWEN);
	basic_weq.basic.bmc_tx_wwan_idx = cpu_to_we16(wcid->idx);
	basic_weq.basic.sta_idx = cpu_to_we16(wcid->idx);
	basic_weq.basic.conn_state = !enabwe;

	eww = mt76_mcu_send_msg(mdev, MCU_UNI_CMD(BSS_INFO_UPDATE), &basic_weq,
				sizeof(basic_weq), twue);
	if (eww < 0)
		wetuwn eww;

	if (vif->bss_conf.he_suppowt) {
		stwuct {
			stwuct {
				u8 bss_idx;
				u8 pad[3];
			} __packed hdw;
			stwuct bss_info_uni_he he;
			stwuct bss_info_uni_bss_cowow bss_cowow;
		} he_weq = {
			.hdw = {
				.bss_idx = mvif->idx,
			},
			.he = {
				.tag = cpu_to_we16(UNI_BSS_INFO_HE_BASIC),
				.wen = cpu_to_we16(sizeof(stwuct bss_info_uni_he)),
			},
			.bss_cowow = {
				.tag = cpu_to_we16(UNI_BSS_INFO_BSS_COWOW),
				.wen = cpu_to_we16(sizeof(stwuct bss_info_uni_bss_cowow)),
				.enabwe = 0,
				.bss_cowow = 0,
			},
		};

		if (enabwe) {
			he_weq.bss_cowow.enabwe =
				vif->bss_conf.he_bss_cowow.enabwed;
			he_weq.bss_cowow.bss_cowow =
				vif->bss_conf.he_bss_cowow.cowow;
		}

		mt76_connac_mcu_uni_bss_he_twv(phy, vif,
					       (stwuct twv *)&he_weq.he);
		eww = mt76_mcu_send_msg(mdev, MCU_UNI_CMD(BSS_INFO_UPDATE),
					&he_weq, sizeof(he_weq), twue);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn mt76_connac_mcu_uni_set_chctx(phy, mvif, ctx);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_uni_add_bss);

#define MT76_CONNAC_SCAN_CHANNEW_TIME		60
int mt76_connac_mcu_hw_scan(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_scan_wequest *scan_weq)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_scan_wequest *sweq = &scan_weq->weq;
	int n_ssids = 0, eww, i, duwation;
	int ext_channews_num = max_t(int, sweq->n_channews - 32, 0);
	stwuct ieee80211_channew **scan_wist = sweq->channews;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct mt76_connac_mcu_scan_channew *chan;
	stwuct mt76_connac_hw_scan_weq *weq;
	stwuct sk_buff *skb;

	if (test_bit(MT76_HW_SCANNING, &phy->state))
		wetuwn -EBUSY;

	skb = mt76_mcu_msg_awwoc(mdev, NUWW, sizeof(*weq));
	if (!skb)
		wetuwn -ENOMEM;

	set_bit(MT76_HW_SCANNING, &phy->state);
	mvif->scan_seq_num = (mvif->scan_seq_num + 1) & 0x7f;

	weq = (stwuct mt76_connac_hw_scan_weq *)skb_put(skb, sizeof(*weq));

	weq->seq_num = mvif->scan_seq_num | mvif->band_idx << 7;
	weq->bss_idx = mvif->idx;
	weq->scan_type = sweq->n_ssids ? 1 : 0;
	weq->pwobe_weq_num = sweq->n_ssids ? 2 : 0;
	weq->vewsion = 1;

	fow (i = 0; i < sweq->n_ssids; i++) {
		if (!sweq->ssids[i].ssid_wen)
			continue;

		weq->ssids[i].ssid_wen = cpu_to_we32(sweq->ssids[i].ssid_wen);
		memcpy(weq->ssids[i].ssid, sweq->ssids[i].ssid,
		       sweq->ssids[i].ssid_wen);
		n_ssids++;
	}
	weq->ssid_type = n_ssids ? BIT(2) : BIT(0);
	weq->ssid_type_ext = n_ssids ? BIT(0) : 0;
	weq->ssids_num = n_ssids;

	duwation = is_mt7921(phy->dev) ? 0 : MT76_CONNAC_SCAN_CHANNEW_TIME;
	/* incwease channew time fow passive scan */
	if (!sweq->n_ssids)
		duwation *= 2;
	weq->timeout_vawue = cpu_to_we16(sweq->n_channews * duwation);
	weq->channew_min_dweww_time = cpu_to_we16(duwation);
	weq->channew_dweww_time = cpu_to_we16(duwation);

	if (sweq->n_channews == 0 || sweq->n_channews > 64) {
		weq->channew_type = 0;
		weq->channews_num = 0;
		weq->ext_channews_num = 0;
	} ewse {
		weq->channew_type = 4;
		weq->channews_num = min_t(u8, sweq->n_channews, 32);
		weq->ext_channews_num = min_t(u8, ext_channews_num, 32);
	}

	fow (i = 0; i < weq->channews_num + weq->ext_channews_num; i++) {
		if (i >= 32)
			chan = &weq->ext_channews[i - 32];
		ewse
			chan = &weq->channews[i];

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

	if (sweq->ie_wen > 0) {
		memcpy(weq->ies, sweq->ie, sweq->ie_wen);
		weq->ies_wen = cpu_to_we16(sweq->ie_wen);
	}

	if (is_mt7921(phy->dev))
		weq->scan_func |= SCAN_FUNC_SPWIT_SCAN;

	memcpy(weq->bssid, sweq->bssid, ETH_AWEN);
	if (sweq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
		get_wandom_mask_addw(weq->wandom_mac, sweq->mac_addw,
				     sweq->mac_addw_mask);
		weq->scan_func |= SCAN_FUNC_WANDOM_MAC;
	}

	eww = mt76_mcu_skb_send_msg(mdev, skb, MCU_CE_CMD(STAWT_HW_SCAN),
				    fawse);
	if (eww < 0)
		cweaw_bit(MT76_HW_SCANNING, &phy->state);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_hw_scan);

int mt76_connac_mcu_cancew_hw_scan(stwuct mt76_phy *phy,
				   stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		u8 seq_num;
		u8 is_ext_channew;
		u8 wsv[2];
	} __packed weq = {
		.seq_num = mvif->scan_seq_num,
	};

	if (test_and_cweaw_bit(MT76_HW_SCANNING, &phy->state)) {
		stwuct cfg80211_scan_info info = {
			.abowted = twue,
		};

		ieee80211_scan_compweted(phy->hw, &info);
	}

	wetuwn mt76_mcu_send_msg(phy->dev, MCU_CE_CMD(CANCEW_HW_SCAN),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_cancew_hw_scan);

int mt76_connac_mcu_sched_scan_weq(stwuct mt76_phy *phy,
				   stwuct ieee80211_vif *vif,
				   stwuct cfg80211_sched_scan_wequest *sweq)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct ieee80211_channew **scan_wist = sweq->channews;
	stwuct mt76_connac_mcu_scan_channew *chan;
	stwuct mt76_connac_sched_scan_weq *weq;
	stwuct mt76_dev *mdev = phy->dev;
	stwuct cfg80211_match_set *match;
	stwuct cfg80211_ssid *ssid;
	stwuct sk_buff *skb;
	int i;

	skb = mt76_mcu_msg_awwoc(mdev, NUWW, sizeof(*weq) + sweq->ie_wen);
	if (!skb)
		wetuwn -ENOMEM;

	mvif->scan_seq_num = (mvif->scan_seq_num + 1) & 0x7f;

	weq = (stwuct mt76_connac_sched_scan_weq *)skb_put(skb, sizeof(*weq));
	weq->vewsion = 1;
	weq->seq_num = mvif->scan_seq_num | mvif->band_idx << 7;

	if (sweq->fwags & NW80211_SCAN_FWAG_WANDOM_ADDW) {
		u8 *addw = is_mt7663(phy->dev) ? weq->mt7663.wandom_mac
					       : weq->mt7921.wandom_mac;

		weq->scan_func = 1;
		get_wandom_mask_addw(addw, sweq->mac_addw,
				     sweq->mac_addw_mask);
	}
	if (is_mt7921(phy->dev)) {
		weq->mt7921.bss_idx = mvif->idx;
		weq->mt7921.deway = cpu_to_we32(sweq->deway);
	}

	weq->ssids_num = sweq->n_ssids;
	fow (i = 0; i < weq->ssids_num; i++) {
		ssid = &sweq->ssids[i];
		memcpy(weq->ssids[i].ssid, ssid->ssid, ssid->ssid_wen);
		weq->ssids[i].ssid_wen = cpu_to_we32(ssid->ssid_wen);
	}

	weq->match_num = sweq->n_match_sets;
	fow (i = 0; i < weq->match_num; i++) {
		match = &sweq->match_sets[i];
		memcpy(weq->match[i].ssid, match->ssid.ssid,
		       match->ssid.ssid_wen);
		weq->match[i].wssi_th = cpu_to_we32(match->wssi_thowd);
		weq->match[i].ssid_wen = match->ssid.ssid_wen;
	}

	weq->channew_type = sweq->n_channews ? 4 : 0;
	weq->channews_num = min_t(u8, sweq->n_channews, 64);
	fow (i = 0; i < weq->channews_num; i++) {
		chan = &weq->channews[i];

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

	weq->intewvaws_num = sweq->n_scan_pwans;
	fow (i = 0; i < weq->intewvaws_num; i++)
		weq->intewvaws[i] = cpu_to_we16(sweq->scan_pwans[i].intewvaw);

	if (sweq->ie_wen > 0) {
		weq->ie_wen = cpu_to_we16(sweq->ie_wen);
		memcpy(skb_put(skb, sweq->ie_wen), sweq->ie, sweq->ie_wen);
	}

	wetuwn mt76_mcu_skb_send_msg(mdev, skb, MCU_CE_CMD(SCHED_SCAN_WEQ),
				     fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sched_scan_weq);

int mt76_connac_mcu_sched_scan_enabwe(stwuct mt76_phy *phy,
				      stwuct ieee80211_vif *vif,
				      boow enabwe)
{
	stwuct {
		u8 active; /* 0: enabwed 1: disabwed */
		u8 wsv[3];
	} __packed weq = {
		.active = !enabwe,
	};

	if (enabwe)
		set_bit(MT76_HW_SCHED_SCANNING, &phy->state);
	ewse
		cweaw_bit(MT76_HW_SCHED_SCANNING, &phy->state);

	wetuwn mt76_mcu_send_msg(phy->dev, MCU_CE_CMD(SCHED_SCAN_ENABWE),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_sched_scan_enabwe);

int mt76_connac_mcu_chip_config(stwuct mt76_dev *dev)
{
	stwuct mt76_connac_config weq = {
		.wesp_type = 0,
	};

	memcpy(weq.data, "assewt", 7);

	wetuwn mt76_mcu_send_msg(dev, MCU_CE_CMD(CHIP_CONFIG),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_chip_config);

int mt76_connac_mcu_set_deep_sweep(stwuct mt76_dev *dev, boow enabwe)
{
	stwuct mt76_connac_config weq = {
		.wesp_type = 0,
	};

	snpwintf(weq.data, sizeof(weq.data), "KeepFuwwPww %d", !enabwe);

	wetuwn mt76_mcu_send_msg(dev, MCU_CE_CMD(CHIP_CONFIG),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_deep_sweep);

int mt76_connac_sta_state_dp(stwuct mt76_dev *dev,
			     enum ieee80211_sta_state owd_state,
			     enum ieee80211_sta_state new_state)
{
	if ((owd_state == IEEE80211_STA_ASSOC &&
	     new_state == IEEE80211_STA_AUTHOWIZED) ||
	    (owd_state == IEEE80211_STA_NONE &&
	     new_state == IEEE80211_STA_NOTEXIST))
		mt76_connac_mcu_set_deep_sweep(dev, twue);

	if ((owd_state == IEEE80211_STA_NOTEXIST &&
	     new_state == IEEE80211_STA_NONE) ||
	    (owd_state == IEEE80211_STA_AUTHOWIZED &&
	     new_state == IEEE80211_STA_ASSOC))
		mt76_connac_mcu_set_deep_sweep(dev, fawse);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac_sta_state_dp);

void mt76_connac_mcu_cowedump_event(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				    stwuct mt76_connac_cowedump *cowedump)
{
	spin_wock_bh(&dev->wock);
	__skb_queue_taiw(&cowedump->msg_wist, skb);
	spin_unwock_bh(&dev->wock);

	cowedump->wast_activity = jiffies;

	queue_dewayed_wowk(dev->wq, &cowedump->wowk,
			   MT76_CONNAC_COWEDUMP_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_cowedump_event);

static void
mt76_connac_mcu_buiwd_sku(stwuct mt76_dev *dev, s8 *sku,
			  stwuct mt76_powew_wimits *wimits,
			  enum nw80211_band band)
{
	int max_powew = is_mt7921(dev) ? 127 : 63;
	int i, offset = sizeof(wimits->cck);

	memset(sku, max_powew, MT_SKU_POWEW_WIMIT);

	if (band == NW80211_BAND_2GHZ) {
		/* cck */
		memcpy(sku, wimits->cck, sizeof(wimits->cck));
	}

	/* ofdm */
	memcpy(&sku[offset], wimits->ofdm, sizeof(wimits->ofdm));
	offset += sizeof(wimits->ofdm);

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

	if (!is_mt7921(dev))
		wetuwn;

	/* he */
	fow (i = 0; i < AWWAY_SIZE(wimits->wu); i++) {
		memcpy(&sku[offset], wimits->wu[i], AWWAY_SIZE(wimits->wu[i]));
		offset += AWWAY_SIZE(wimits->wu[i]);
	}
}

s8 mt76_connac_get_ch_powew(stwuct mt76_phy *phy,
			    stwuct ieee80211_channew *chan,
			    s8 tawget_powew)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct ieee80211_suppowted_band *sband;
	int i;

	switch (chan->band) {
	case NW80211_BAND_2GHZ:
		sband = &phy->sband_2g.sband;
		bweak;
	case NW80211_BAND_5GHZ:
		sband = &phy->sband_5g.sband;
		bweak;
	case NW80211_BAND_6GHZ:
		sband = &phy->sband_6g.sband;
		bweak;
	defauwt:
		wetuwn tawget_powew;
	}

	fow (i = 0; i < sband->n_channews; i++) {
		stwuct ieee80211_channew *ch = &sband->channews[i];

		if (ch->hw_vawue == chan->hw_vawue) {
			if (!(ch->fwags & IEEE80211_CHAN_DISABWED)) {
				int powew = 2 * ch->max_weg_powew;

				if (is_mt7663(dev) && (powew > 63 || powew < -64))
					powew = 63;
				tawget_powew = min_t(s8, powew, tawget_powew);
			}
			bweak;
		}
	}

	wetuwn tawget_powew;
}
EXPOWT_SYMBOW_GPW(mt76_connac_get_ch_powew);

static int
mt76_connac_mcu_wate_txpowew_band(stwuct mt76_phy *phy,
				  enum nw80211_band band)
{
	stwuct mt76_dev *dev = phy->dev;
	int sku_wen, batch_wen = is_mt7921(dev) ? 8 : 16;
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
		159, 161, 165, 169, 173, 177
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
	int i, n_chan, batch_size, idx = 0, tx_powew, wast_ch, eww = 0;
	stwuct mt76_connac_sku_twv sku_twbv;
	stwuct mt76_powew_wimits *wimits;
	const u8 *ch_wist;

	wimits = devm_kmawwoc(dev->dev, sizeof(*wimits), GFP_KEWNEW);
	if (!wimits)
		wetuwn -ENOMEM;

	sku_wen = is_mt7921(dev) ? sizeof(sku_twbv) : sizeof(sku_twbv) - 92;
	tx_powew = 2 * phy->hw->conf.powew_wevew;
	if (!tx_powew)
		tx_powew = 127;

	if (band == NW80211_BAND_2GHZ) {
		n_chan = AWWAY_SIZE(chan_wist_2ghz);
		ch_wist = chan_wist_2ghz;
	} ewse if (band == NW80211_BAND_6GHZ) {
		n_chan = AWWAY_SIZE(chan_wist_6ghz);
		ch_wist = chan_wist_6ghz;
	} ewse {
		n_chan = AWWAY_SIZE(chan_wist_5ghz);
		ch_wist = chan_wist_5ghz;
	}
	batch_size = DIV_WOUND_UP(n_chan, batch_wen);

	if (phy->cap.has_6ghz)
		wast_ch = chan_wist_6ghz[AWWAY_SIZE(chan_wist_6ghz) - 1];
	ewse if (phy->cap.has_5ghz)
		wast_ch = chan_wist_5ghz[AWWAY_SIZE(chan_wist_5ghz) - 1];
	ewse
		wast_ch = chan_wist_2ghz[AWWAY_SIZE(chan_wist_2ghz) - 1];

	fow (i = 0; i < batch_size; i++) {
		stwuct mt76_connac_tx_powew_wimit_twv tx_powew_twv = {};
		int j, msg_wen, num_ch;
		stwuct sk_buff *skb;

		num_ch = i == batch_size - 1 ? n_chan % batch_wen : batch_wen;
		msg_wen = sizeof(tx_powew_twv) + num_ch * sizeof(sku_twbv);
		skb = mt76_mcu_msg_awwoc(dev, NUWW, msg_wen);
		if (!skb) {
			eww = -ENOMEM;
			goto out;
		}

		skb_wesewve(skb, sizeof(tx_powew_twv));

		BUIWD_BUG_ON(sizeof(dev->awpha2) > sizeof(tx_powew_twv.awpha2));
		memcpy(tx_powew_twv.awpha2, dev->awpha2, sizeof(dev->awpha2));
		tx_powew_twv.n_chan = num_ch;

		switch (band) {
		case NW80211_BAND_2GHZ:
			tx_powew_twv.band = 1;
			bweak;
		case NW80211_BAND_6GHZ:
			tx_powew_twv.band = 3;
			bweak;
		defauwt:
			tx_powew_twv.band = 2;
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

			tx_powew_twv.wast_msg = ch_wist[idx] == wast_ch;
			sku_twbv.channew = ch_wist[idx];

			mt76_connac_mcu_buiwd_sku(dev, sku_twbv.pww_wimit,
						  wimits, band);
			skb_put_data(skb, &sku_twbv, sku_wen);
		}
		__skb_push(skb, sizeof(tx_powew_twv));
		memcpy(skb->data, &tx_powew_twv, sizeof(tx_powew_twv));

		eww = mt76_mcu_skb_send_msg(dev, skb,
					    MCU_CE_CMD(SET_WATE_TX_POWEW),
					    fawse);
		if (eww < 0)
			goto out;
	}

out:
	devm_kfwee(dev->dev, wimits);
	wetuwn eww;
}

int mt76_connac_mcu_set_wate_txpowew(stwuct mt76_phy *phy)
{
	int eww;

	if (phy->cap.has_2ghz) {
		eww = mt76_connac_mcu_wate_txpowew_band(phy,
							NW80211_BAND_2GHZ);
		if (eww < 0)
			wetuwn eww;
	}
	if (phy->cap.has_5ghz) {
		eww = mt76_connac_mcu_wate_txpowew_band(phy,
							NW80211_BAND_5GHZ);
		if (eww < 0)
			wetuwn eww;
	}
	if (phy->cap.has_6ghz) {
		eww = mt76_connac_mcu_wate_txpowew_band(phy,
							NW80211_BAND_6GHZ);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_wate_txpowew);

int mt76_connac_mcu_update_awp_fiwtew(stwuct mt76_dev *dev,
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
		stwuct mt76_connac_awpns_twv awp;
	} weq_hdw = {
		.hdw = {
			.bss_idx = vif->idx,
		},
		.awp = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_AWP),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_awpns_twv)),
			.ips_num = wen,
			.mode = 2,  /* update */
			.option = 1,
		},
	};

	skb = mt76_mcu_msg_awwoc(dev, NUWW,
				 sizeof(weq_hdw) + wen * sizeof(__be32));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &weq_hdw, sizeof(weq_hdw));
	fow (i = 0; i < wen; i++)
		skb_put_data(skb, &mvif->cfg.awp_addw_wist[i], sizeof(__be32));

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD(OFFWOAD), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_update_awp_fiwtew);

int mt76_connac_mcu_set_p2p_oppps(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	int ct_window = vif->bss_conf.p2p_noa_attw.oppps_ctwindow;
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct {
		__we32 ct_win;
		u8 bss_idx;
		u8 wsv[3];
	} __packed weq = {
		.ct_win = cpu_to_we32(ct_window),
		.bss_idx = mvif->idx,
	};

	wetuwn mt76_mcu_send_msg(phy->dev, MCU_CE_CMD(SET_P2P_OPPPS),
				 &weq, sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_p2p_oppps);

#ifdef CONFIG_PM

const stwuct wiphy_wowwan_suppowt mt76_connac_wowwan_suppowt = {
	.fwags = WIPHY_WOWWAN_MAGIC_PKT | WIPHY_WOWWAN_DISCONNECT |
		 WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY | WIPHY_WOWWAN_NET_DETECT,
	.n_pattewns = 1,
	.pattewn_min_wen = 1,
	.pattewn_max_wen = MT76_CONNAC_WOW_PATTEN_MAX_WEN,
	.max_nd_match_sets = 10,
};
EXPOWT_SYMBOW_GPW(mt76_connac_wowwan_suppowt);

static void
mt76_connac_mcu_key_itew(stwuct ieee80211_hw *hw,
			 stwuct ieee80211_vif *vif,
			 stwuct ieee80211_sta *sta,
			 stwuct ieee80211_key_conf *key,
			 void *data)
{
	stwuct mt76_connac_gtk_wekey_twv *gtk_twv = data;
	u32 ciphew;

	if (key->ciphew != WWAN_CIPHEW_SUITE_AES_CMAC &&
	    key->ciphew != WWAN_CIPHEW_SUITE_CCMP &&
	    key->ciphew != WWAN_CIPHEW_SUITE_TKIP)
		wetuwn;

	if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
		ciphew = BIT(3);
	ewse
		ciphew = BIT(4);

	/* we awe assuming hewe to have a singwe paiwwise key */
	if (key->fwags & IEEE80211_KEY_FWAG_PAIWWISE) {
		if (key->ciphew == WWAN_CIPHEW_SUITE_TKIP)
			gtk_twv->pwoto = cpu_to_we32(NW80211_WPA_VEWSION_1);
		ewse
			gtk_twv->pwoto = cpu_to_we32(NW80211_WPA_VEWSION_2);

		gtk_twv->paiwwise_ciphew = cpu_to_we32(ciphew);
		gtk_twv->keyid = key->keyidx;
	} ewse {
		gtk_twv->gwoup_ciphew = cpu_to_we32(ciphew);
	}
}

int mt76_connac_mcu_update_gtk_wekey(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct cfg80211_gtk_wekey_data *key)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_connac_gtk_wekey_twv *gtk_twv;
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct sk_buff *skb;
	stwuct {
		u8 bss_idx;
		u8 pad[3];
	} __packed hdw = {
		.bss_idx = mvif->idx,
	};

	skb = mt76_mcu_msg_awwoc(phy->dev, NUWW,
				 sizeof(hdw) + sizeof(*gtk_twv));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &hdw, sizeof(hdw));
	gtk_twv = (stwuct mt76_connac_gtk_wekey_twv *)skb_put(skb,
							 sizeof(*gtk_twv));
	gtk_twv->tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_GTK_WEKEY);
	gtk_twv->wen = cpu_to_we16(sizeof(*gtk_twv));
	gtk_twv->wekey_mode = 2;
	gtk_twv->option = 1;

	wcu_wead_wock();
	ieee80211_itew_keys_wcu(hw, vif, mt76_connac_mcu_key_itew, gtk_twv);
	wcu_wead_unwock();

	memcpy(gtk_twv->kek, key->kek, NW80211_KEK_WEN);
	memcpy(gtk_twv->kck, key->kck, NW80211_KCK_WEN);
	memcpy(gtk_twv->wepway_ctw, key->wepway_ctw, NW80211_WEPWAY_CTW_WEN);

	wetuwn mt76_mcu_skb_send_msg(phy->dev, skb,
				     MCU_UNI_CMD(OFFWOAD), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_update_gtk_wekey);

static int
mt76_connac_mcu_set_awp_fiwtew(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
			       boow suspend)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_awpns_twv awpns;
	} weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.awpns = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_AWP),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_awpns_twv)),
			.mode = suspend,
		},
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD(OFFWOAD), &weq,
				 sizeof(weq), twue);
}

int
mt76_connac_mcu_set_gtk_wekey(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
			      boow suspend)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_gtk_wekey_twv gtk_twv;
	} __packed weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.gtk_twv = {
			.tag = cpu_to_we16(UNI_OFFWOAD_OFFWOAD_GTK_WEKEY),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_gtk_wekey_twv)),
			.wekey_mode = !suspend,
		},
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD(OFFWOAD), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_gtk_wekey);

int
mt76_connac_mcu_set_suspend_mode(stwuct mt76_dev *dev,
				 stwuct ieee80211_vif *vif,
				 boow enabwe, u8 mdtim,
				 boow wow_suspend)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct {
		stwuct {
			u8 bss_idx;
			u8 pad[3];
		} __packed hdw;
		stwuct mt76_connac_suspend_twv suspend_twv;
	} weq = {
		.hdw = {
			.bss_idx = mvif->idx,
		},
		.suspend_twv = {
			.tag = cpu_to_we16(UNI_SUSPEND_MODE_SETTING),
			.wen = cpu_to_we16(sizeof(stwuct mt76_connac_suspend_twv)),
			.enabwe = enabwe,
			.mdtim = mdtim,
			.wow_suspend = wow_suspend,
		},
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD(SUSPEND), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_suspend_mode);

static int
mt76_connac_mcu_set_wow_pattewn(stwuct mt76_dev *dev,
				stwuct ieee80211_vif *vif,
				u8 index, boow enabwe,
				stwuct cfg80211_pkt_pattewn *pattewn)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct mt76_connac_wow_pattewn_twv *ptwv;
	stwuct sk_buff *skb;
	stwuct weq_hdw {
		u8 bss_idx;
		u8 pad[3];
	} __packed hdw = {
		.bss_idx = mvif->idx,
	};

	skb = mt76_mcu_msg_awwoc(dev, NUWW, sizeof(hdw) + sizeof(*ptwv));
	if (!skb)
		wetuwn -ENOMEM;

	skb_put_data(skb, &hdw, sizeof(hdw));
	ptwv = (stwuct mt76_connac_wow_pattewn_twv *)skb_put(skb, sizeof(*ptwv));
	ptwv->tag = cpu_to_we16(UNI_SUSPEND_WOW_PATTEWN);
	ptwv->wen = cpu_to_we16(sizeof(*ptwv));
	ptwv->data_wen = pattewn->pattewn_wen;
	ptwv->enabwe = enabwe;
	ptwv->index = index;

	memcpy(ptwv->pattewn, pattewn->pattewn, pattewn->pattewn_wen);
	memcpy(ptwv->mask, pattewn->mask, DIV_WOUND_UP(pattewn->pattewn_wen, 8));

	wetuwn mt76_mcu_skb_send_msg(dev, skb, MCU_UNI_CMD(SUSPEND), twue);
}

int
mt76_connac_mcu_set_wow_ctww(stwuct mt76_phy *phy, stwuct ieee80211_vif *vif,
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
		mt76_connac_mcu_sched_scan_weq(phy, vif, wowwan->nd_config);
		weq.wow_ctww_twv.twiggew |= UNI_WOW_DETECT_TYPE_SCH_SCAN_HIT;
		mt76_connac_mcu_sched_scan_enabwe(phy, vif, suspend);
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
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_wow_ctww);

int mt76_connac_mcu_set_hif_suspend(stwuct mt76_dev *dev, boow suspend)
{
	stwuct {
		stwuct {
			u8 hif_type; /* 0x0: HIF_SDIO
				      * 0x1: HIF_USB
				      * 0x2: HIF_PCIE
				      */
			u8 pad[3];
		} __packed hdw;
		stwuct hif_suspend_twv {
			__we16 tag;
			__we16 wen;
			u8 suspend;
		} __packed hif_suspend;
	} weq = {
		.hif_suspend = {
			.tag = cpu_to_we16(0), /* 0: UNI_HIF_CTWW_BASIC */
			.wen = cpu_to_we16(sizeof(stwuct hif_suspend_twv)),
			.suspend = suspend,
		},
	};

	if (mt76_is_mmio(dev))
		weq.hdw.hif_type = 2;
	ewse if (mt76_is_usb(dev))
		weq.hdw.hif_type = 1;
	ewse if (mt76_is_sdio(dev))
		weq.hdw.hif_type = 0;

	wetuwn mt76_mcu_send_msg(dev, MCU_UNI_CMD(HIF_CTWW), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_hif_suspend);

void mt76_connac_mcu_set_suspend_itew(void *pwiv, u8 *mac,
				      stwuct ieee80211_vif *vif)
{
	stwuct mt76_phy *phy = pwiv;
	boow suspend = !test_bit(MT76_STATE_WUNNING, &phy->state);
	stwuct ieee80211_hw *hw = phy->hw;
	stwuct cfg80211_wowwan *wowwan = hw->wiphy->wowwan_config;
	int i;

	mt76_connac_mcu_set_gtk_wekey(phy->dev, vif, suspend);
	mt76_connac_mcu_set_awp_fiwtew(phy->dev, vif, suspend);

	mt76_connac_mcu_set_suspend_mode(phy->dev, vif, suspend, 1, twue);

	fow (i = 0; i < wowwan->n_pattewns; i++)
		mt76_connac_mcu_set_wow_pattewn(phy->dev, vif, i, suspend,
						&wowwan->pattewns[i]);
	mt76_connac_mcu_set_wow_ctww(phy, vif, suspend, wowwan);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_suspend_itew);
#endif /* CONFIG_PM */

u32 mt76_connac_mcu_weg_ww(stwuct mt76_dev *dev, u32 offset)
{
	stwuct {
		__we32 addw;
		__we32 vaw;
	} __packed weq = {
		.addw = cpu_to_we32(offset),
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_CE_QUEWY(WEG_WEAD), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_weg_ww);

void mt76_connac_mcu_weg_ww(stwuct mt76_dev *dev, u32 offset, u32 vaw)
{
	stwuct {
		__we32 addw;
		__we32 vaw;
	} __packed weq = {
		.addw = cpu_to_we32(offset),
		.vaw = cpu_to_we32(vaw),
	};

	mt76_mcu_send_msg(dev, MCU_CE_CMD(WEG_WWITE), &weq,
			  sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_weg_ww);

static int
mt76_connac_mcu_sta_key_twv(stwuct mt76_connac_sta_key_conf *sta_key_conf,
			    stwuct sk_buff *skb,
			    stwuct ieee80211_key_conf *key,
			    enum set_key_cmd cmd)
{
	stwuct sta_wec_sec *sec;
	u32 wen = sizeof(*sec);
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, STA_WEC_KEY_V2, sizeof(*sec));
	sec = (stwuct sta_wec_sec *)twv;
	sec->add = cmd;

	if (cmd == SET_KEY) {
		stwuct sec_key *sec_key;
		u8 ciphew;

		ciphew = mt76_connac_mcu_get_ciphew(key->ciphew);
		if (ciphew == MCU_CIPHEW_NONE)
			wetuwn -EOPNOTSUPP;

		sec_key = &sec->key[0];
		sec_key->ciphew_wen = sizeof(*sec_key);

		if (ciphew == MCU_CIPHEW_BIP_CMAC_128) {
			sec_key->ciphew_id = MCU_CIPHEW_AES_CCMP;
			sec_key->key_id = sta_key_conf->keyidx;
			sec_key->key_wen = 16;
			memcpy(sec_key->key, sta_key_conf->key, 16);

			sec_key = &sec->key[1];
			sec_key->ciphew_id = MCU_CIPHEW_BIP_CMAC_128;
			sec_key->ciphew_wen = sizeof(*sec_key);
			sec_key->key_wen = 16;
			memcpy(sec_key->key, key->key, 16);
			sec->n_ciphew = 2;
		} ewse {
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

			wen -= sizeof(*sec_key);
			sec->n_ciphew = 1;
		}
	} ewse {
		wen -= sizeof(sec->key);
		sec->n_ciphew = 0;
	}
	sec->wen = cpu_to_we16(wen);

	wetuwn 0;
}

int mt76_connac_mcu_add_key(stwuct mt76_dev *dev, stwuct ieee80211_vif *vif,
			    stwuct mt76_connac_sta_key_conf *sta_key_conf,
			    stwuct ieee80211_key_conf *key, int mcu_cmd,
			    stwuct mt76_wcid *wcid, enum set_key_cmd cmd)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct sk_buff *skb;
	int wet;

	skb = mt76_connac_mcu_awwoc_sta_weq(dev, mvif, wcid);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	wet = mt76_connac_mcu_sta_key_twv(sta_key_conf, skb, key, cmd);
	if (wet)
		wetuwn wet;

	wet = mt76_connac_mcu_sta_wed_update(dev, skb);
	if (wet)
		wetuwn wet;

	wetuwn mt76_mcu_skb_send_msg(dev, skb, mcu_cmd, twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_add_key);

/* SIFS 20us + 512 byte beacon twansmitted by 1Mbps (3906us) */
#define BCN_TX_ESTIMATE_TIME (4096 + 20)
void mt76_connac_mcu_bss_ext_twv(stwuct sk_buff *skb, stwuct mt76_vif *mvif)
{
	stwuct bss_info_ext_bss *ext;
	int ext_bss_idx, tsf_offset;
	stwuct twv *twv;

	ext_bss_idx = mvif->omac_idx - EXT_BSSID_STAWT;
	if (ext_bss_idx < 0)
		wetuwn;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_EXT_BSS, sizeof(*ext));

	ext = (stwuct bss_info_ext_bss *)twv;
	tsf_offset = ext_bss_idx * BCN_TX_ESTIMATE_TIME;
	ext->mbss_tsf_offset = cpu_to_we32(tsf_offset);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_bss_ext_twv);

int mt76_connac_mcu_bss_basic_twv(stwuct sk_buff *skb,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta,
				  stwuct mt76_phy *phy, u16 wwan_idx,
				  boow enabwe)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	u32 type = vif->p2p ? NETWOWK_P2P : NETWOWK_INFWA;
	stwuct bss_info_basic *bss;
	stwuct twv *twv;

	twv = mt76_connac_mcu_add_twv(skb, BSS_INFO_BASIC, sizeof(*bss));
	bss = (stwuct bss_info_basic *)twv;

	switch (vif->type) {
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_MONITOW:
		bweak;
	case NW80211_IFTYPE_AP:
		if (ieee80211_hw_check(phy->hw, SUPPOWTS_MUWTI_BSSID)) {
			u8 bssid_id = vif->bss_conf.bssid_indicatow;
			stwuct wiphy *wiphy = phy->hw->wiphy;

			if (bssid_id > iwog2(wiphy->mbssid_max_intewfaces))
				wetuwn -EINVAW;

			bss->non_tx_bssid = vif->bss_conf.bssid_index;
			bss->max_bssid = bssid_id;
		}
		bweak;
	case NW80211_IFTYPE_STATION:
		if (enabwe) {
			wcu_wead_wock();
			if (!sta)
				sta = ieee80211_find_sta(vif,
							 vif->bss_conf.bssid);
			/* TODO: enabwe BSS_INFO_UAPSD & BSS_INFO_PM */
			if (sta) {
				stwuct mt76_wcid *wcid;

				wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
				wwan_idx = wcid->idx;
			}
			wcu_wead_unwock();
		}
		bweak;
	case NW80211_IFTYPE_ADHOC:
		type = NETWOWK_IBSS;
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	bss->netwowk_type = cpu_to_we32(type);
	bss->bmc_wcid_wo = to_wcid_wo(wwan_idx);
	bss->bmc_wcid_hi = to_wcid_hi(wwan_idx);
	bss->wmm_idx = mvif->wmm_idx;
	bss->active = enabwe;
	bss->ciphew = mvif->ciphew;

	if (vif->type != NW80211_IFTYPE_MONITOW) {
		stwuct cfg80211_chan_def *chandef = &phy->chandef;

		memcpy(bss->bssid, vif->bss_conf.bssid, ETH_AWEN);
		bss->bcn_intewvaw = cpu_to_we16(vif->bss_conf.beacon_int);
		bss->dtim_pewiod = vif->bss_conf.dtim_pewiod;
		bss->phy_mode = mt76_connac_get_phy_mode(phy, vif,
							 chandef->chan->band, NUWW);
	} ewse {
		memcpy(bss->bssid, phy->macaddw, ETH_AWEN);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_bss_basic_twv);

#define ENTEW_PM_STATE		1
#define EXIT_PM_STATE		2
int mt76_connac_mcu_set_pm(stwuct mt76_dev *dev, int band, int entew)
{
	stwuct {
		u8 pm_numbew;
		u8 pm_state;
		u8 bssid[ETH_AWEN];
		u8 dtim_pewiod;
		u8 wwan_idx_wo;
		__we16 bcn_intewvaw;
		__we32 aid;
		__we32 wx_fiwtew;
		u8 band_idx;
		u8 wwan_idx_hi;
		u8 wsv[2];
		__we32 featuwe;
		u8 omac_idx;
		u8 wmm_idx;
		u8 bcn_woss_cnt;
		u8 bcn_sp_duwation;
	} __packed weq = {
		.pm_numbew = 5,
		.pm_state = entew ? ENTEW_PM_STATE : EXIT_PM_STATE,
		.band_idx = band,
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_EXT_CMD(PM_STATE_CTWW), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_set_pm);

int mt76_connac_mcu_westawt(stwuct mt76_dev *dev)
{
	stwuct {
		u8 powew_mode;
		u8 wsv[3];
	} weq = {
		.powew_mode = 1,
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_CMD(NIC_POWEW_CTWW), &weq,
				 sizeof(weq), fawse);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_westawt);

int mt76_connac_mcu_wdd_cmd(stwuct mt76_dev *dev, int cmd, u8 index,
			    u8 wx_sew, u8 vaw)
{
	stwuct {
		u8 ctww;
		u8 wdd_idx;
		u8 wdd_wx_sew;
		u8 vaw;
		u8 wsv[4];
	} __packed weq = {
		.ctww = cmd,
		.wdd_idx = index,
		.wdd_wx_sew = wx_sew,
		.vaw = vaw,
	};

	wetuwn mt76_mcu_send_msg(dev, MCU_EXT_CMD(SET_WDD_CTWW), &weq,
				 sizeof(weq), twue);
}
EXPOWT_SYMBOW_GPW(mt76_connac_mcu_wdd_cmd);

static int
mt76_connac_mcu_send_wam_fiwmwawe(stwuct mt76_dev *dev,
				  const stwuct mt76_connac2_fw_twaiwew *hdw,
				  const u8 *data, boow is_wa)
{
	int i, offset = 0, max_wen = mt76_is_sdio(dev) ? 2048 : 4096;
	u32 ovewwide = 0, option = 0;

	fow (i = 0; i < hdw->n_wegion; i++) {
		const stwuct mt76_connac2_fw_wegion *wegion;
		u32 wen, addw, mode;
		int eww;

		wegion = (const void *)((const u8 *)hdw -
					(hdw->n_wegion - i) * sizeof(*wegion));
		mode = mt76_connac_mcu_gen_dw_mode(dev, wegion->featuwe_set,
						   is_wa);
		wen = we32_to_cpu(wegion->wen);
		addw = we32_to_cpu(wegion->addw);

		if (wegion->featuwe_set & FW_FEATUWE_NON_DW)
			goto next;

		if (wegion->featuwe_set & FW_FEATUWE_OVEWWIDE_ADDW)
			ovewwide = addw;

		eww = mt76_connac_mcu_init_downwoad(dev, addw, wen, mode);
		if (eww) {
			dev_eww(dev->dev, "Downwoad wequest faiwed\n");
			wetuwn eww;
		}

		eww = __mt76_mcu_send_fiwmwawe(dev, MCU_CMD(FW_SCATTEW),
					       data + offset, wen, max_wen);
		if (eww) {
			dev_eww(dev->dev, "Faiwed to send fiwmwawe.\n");
			wetuwn eww;
		}

next:
		offset += wen;
	}

	if (ovewwide)
		option |= FW_STAWT_OVEWWIDE;
	if (is_wa)
		option |= FW_STAWT_WOWKING_PDA_CW4;

	wetuwn mt76_connac_mcu_stawt_fiwmwawe(dev, ovewwide, option);
}

int mt76_connac2_woad_wam(stwuct mt76_dev *dev, const chaw *fw_wm,
			  const chaw *fw_wa)
{
	const stwuct mt76_connac2_fw_twaiwew *hdw;
	const stwuct fiwmwawe *fw;
	int wet;

	wet = wequest_fiwmwawe(&fw, fw_wm, dev->dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw)) {
		dev_eww(dev->dev, "Invawid fiwmwawe\n");
		wet = -EINVAW;
		goto out;
	}

	hdw = (const void *)(fw->data + fw->size - sizeof(*hdw));
	dev_info(dev->dev, "WM Fiwmwawe Vewsion: %.10s, Buiwd Time: %.15s\n",
		 hdw->fw_vew, hdw->buiwd_date);

	wet = mt76_connac_mcu_send_wam_fiwmwawe(dev, hdw, fw->data, fawse);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to stawt WM fiwmwawe\n");
		goto out;
	}

	snpwintf(dev->hw->wiphy->fw_vewsion,
		 sizeof(dev->hw->wiphy->fw_vewsion),
		 "%.10s-%.15s", hdw->fw_vew, hdw->buiwd_date);

	wewease_fiwmwawe(fw);

	if (!fw_wa)
		wetuwn 0;

	wet = wequest_fiwmwawe(&fw, fw_wa, dev->dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data || fw->size < sizeof(*hdw)) {
		dev_eww(dev->dev, "Invawid fiwmwawe\n");
		wet = -EINVAW;
		goto out;
	}

	hdw = (const void *)(fw->data + fw->size - sizeof(*hdw));
	dev_info(dev->dev, "WA Fiwmwawe Vewsion: %.10s, Buiwd Time: %.15s\n",
		 hdw->fw_vew, hdw->buiwd_date);

	wet = mt76_connac_mcu_send_wam_fiwmwawe(dev, hdw, fw->data, twue);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to stawt WA fiwmwawe\n");
		goto out;
	}

	snpwintf(dev->hw->wiphy->fw_vewsion,
		 sizeof(dev->hw->wiphy->fw_vewsion),
		 "%.10s-%.15s", hdw->fw_vew, hdw->buiwd_date);

out:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_woad_wam);

static u32 mt76_connac2_get_data_mode(stwuct mt76_dev *dev, u32 info)
{
	u32 mode = DW_MODE_NEED_WSP;

	if ((!is_mt7921(dev) && !is_mt7925(dev)) || info == PATCH_SEC_NOT_SUPPOWT)
		wetuwn mode;

	switch (FIEWD_GET(PATCH_SEC_ENC_TYPE_MASK, info)) {
	case PATCH_SEC_ENC_TYPE_PWAIN:
		bweak;
	case PATCH_SEC_ENC_TYPE_AES:
		mode |= DW_MODE_ENCWYPT;
		mode |= FIEWD_PWEP(DW_MODE_KEY_IDX,
				(info & PATCH_SEC_ENC_AES_KEY_MASK)) & DW_MODE_KEY_IDX;
		mode |= DW_MODE_WESET_SEC_IV;
		bweak;
	case PATCH_SEC_ENC_TYPE_SCWAMBWE:
		mode |= DW_MODE_ENCWYPT;
		mode |= DW_CONFIG_ENCWY_MODE_SEW;
		mode |= DW_MODE_WESET_SEC_IV;
		bweak;
	defauwt:
		dev_eww(dev->dev, "Encwyption type not suppowt!\n");
	}

	wetuwn mode;
}

int mt76_connac2_woad_patch(stwuct mt76_dev *dev, const chaw *fw_name)
{
	int i, wet, sem, max_wen = mt76_is_sdio(dev) ? 2048 : 4096;
	const stwuct mt76_connac2_patch_hdw *hdw;
	const stwuct fiwmwawe *fw = NUWW;

	sem = mt76_connac_mcu_patch_sem_ctww(dev, twue);
	switch (sem) {
	case PATCH_IS_DW:
		wetuwn 0;
	case PATCH_NOT_DW_SEM_SUCCESS:
		bweak;
	defauwt:
		dev_eww(dev->dev, "Faiwed to get patch semaphowe\n");
		wetuwn -EAGAIN;
	}

	wet = wequest_fiwmwawe(&fw, fw_name, dev->dev);
	if (wet)
		goto out;

	if (!fw || !fw->data || fw->size < sizeof(*hdw)) {
		dev_eww(dev->dev, "Invawid fiwmwawe\n");
		wet = -EINVAW;
		goto out;
	}

	hdw = (const void *)fw->data;
	dev_info(dev->dev, "HW/SW Vewsion: 0x%x, Buiwd Time: %.16s\n",
		 be32_to_cpu(hdw->hw_sw_vew), hdw->buiwd_date);

	fow (i = 0; i < be32_to_cpu(hdw->desc.n_wegion); i++) {
		stwuct mt76_connac2_patch_sec *sec;
		u32 wen, addw, mode;
		const u8 *dw;
		u32 sec_info;

		sec = (void *)(fw->data + sizeof(*hdw) + i * sizeof(*sec));
		if ((be32_to_cpu(sec->type) & PATCH_SEC_TYPE_MASK) !=
		    PATCH_SEC_TYPE_INFO) {
			wet = -EINVAW;
			goto out;
		}

		addw = be32_to_cpu(sec->info.addw);
		wen = be32_to_cpu(sec->info.wen);
		dw = fw->data + be32_to_cpu(sec->offs);
		sec_info = be32_to_cpu(sec->info.sec_key_idx);
		mode = mt76_connac2_get_data_mode(dev, sec_info);

		wet = mt76_connac_mcu_init_downwoad(dev, addw, wen, mode);
		if (wet) {
			dev_eww(dev->dev, "Downwoad wequest faiwed\n");
			goto out;
		}

		wet = __mt76_mcu_send_fiwmwawe(dev, MCU_CMD(FW_SCATTEW),
					       dw, wen, max_wen);
		if (wet) {
			dev_eww(dev->dev, "Faiwed to send patch\n");
			goto out;
		}
	}

	wet = mt76_connac_mcu_stawt_patch(dev);
	if (wet)
		dev_eww(dev->dev, "Faiwed to stawt patch\n");

out:
	sem = mt76_connac_mcu_patch_sem_ctww(dev, fawse);
	switch (sem) {
	case PATCH_WEW_SEM_SUCCESS:
		bweak;
	defauwt:
		wet = -EAGAIN;
		dev_eww(dev->dev, "Faiwed to wewease patch semaphowe\n");
		bweak;
	}

	wewease_fiwmwawe(fw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_woad_patch);

int mt76_connac2_mcu_fiww_message(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				  int cmd, int *wait_seq)
{
	int txd_wen, mcu_cmd = FIEWD_GET(__MCU_CMD_FIEWD_ID, cmd);
	stwuct mt76_connac2_mcu_uni_txd *uni_txd;
	stwuct mt76_connac2_mcu_txd *mcu_txd;
	__we32 *txd;
	u32 vaw;
	u8 seq;

	/* TODO: make dynamic based on msg type */
	dev->mcu.timeout = 20 * HZ;

	seq = ++dev->mcu.msg_seq & 0xf;
	if (!seq)
		seq = ++dev->mcu.msg_seq & 0xf;

	if (cmd == MCU_CMD(FW_SCATTEW))
		goto exit;

	txd_wen = cmd & __MCU_CMD_FIEWD_UNI ? sizeof(*uni_txd) : sizeof(*mcu_txd);
	txd = (__we32 *)skb_push(skb, txd_wen);

	vaw = FIEWD_PWEP(MT_TXD0_TX_BYTES, skb->wen) |
	      FIEWD_PWEP(MT_TXD0_PKT_FMT, MT_TX_TYPE_CMD) |
	      FIEWD_PWEP(MT_TXD0_Q_IDX, MT_TX_MCU_POWT_WX_Q0);
	txd[0] = cpu_to_we32(vaw);

	vaw = MT_TXD1_WONG_FOWMAT |
	      FIEWD_PWEP(MT_TXD1_HDW_FOWMAT, MT_HDW_FOWMAT_CMD);
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
EXPOWT_SYMBOW_GPW(mt76_connac2_mcu_fiww_message);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_WICENSE("Duaw BSD/GPW");
