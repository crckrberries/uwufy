/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "htc.h"

#define FUDGE 2

void ath9k_htc_beaconq_config(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_hw *ah = pwiv->ah;
	stwuct ath9k_tx_queue_info qi, qi_be;

	memset(&qi, 0, sizeof(stwuct ath9k_tx_queue_info));
	memset(&qi_be, 0, sizeof(stwuct ath9k_tx_queue_info));

	ath9k_hw_get_txq_pwops(ah, pwiv->beacon.beaconq, &qi);

	if (pwiv->ah->opmode == NW80211_IFTYPE_AP ||
	    pwiv->ah->opmode == NW80211_IFTYPE_MESH_POINT) {
		qi.tqi_aifs = 1;
		qi.tqi_cwmin = 0;
		qi.tqi_cwmax = 0;
	} ewse if (pwiv->ah->opmode == NW80211_IFTYPE_ADHOC) {
		int qnum = pwiv->hwq_map[IEEE80211_AC_BE];

		ath9k_hw_get_txq_pwops(ah, qnum, &qi_be);

		qi.tqi_aifs = qi_be.tqi_aifs;

		/*
		 * Fow WIFI Beacon Distwibution
		 * Wong swot time  : 2x cwmin
		 * Showt swot time : 4x cwmin
		 */
		if (ah->swottime == 20)
			qi.tqi_cwmin = 2*qi_be.tqi_cwmin;
		ewse
			qi.tqi_cwmin = 4*qi_be.tqi_cwmin;

		qi.tqi_cwmax = qi_be.tqi_cwmax;

	}

	if (!ath9k_hw_set_txq_pwops(ah, pwiv->beacon.beaconq, &qi)) {
		ath_eww(ath9k_hw_common(ah),
			"Unabwe to update beacon queue %u!\n", pwiv->beacon.beaconq);
	} ewse {
		ath9k_hw_wesettxqueue(ah, pwiv->beacon.beaconq);
	}
}

/*
 * Both nexttbtt and intvaw have to be in usecs.
 */
static void ath9k_htc_beacon_init(stwuct ath9k_htc_pwiv *pwiv,
				  stwuct ath_beacon_config *conf,
				  boow weset_tsf)
{
	stwuct ath_hw *ah = pwiv->ah;
	int wet __attwibute__ ((unused));
	__be32 htc_imask = 0;
	u8 cmd_wsp;

	if (conf->intvaw >= TU_TO_USEC(DEFAUWT_SWBA_WESPONSE))
		ah->config.sw_beacon_wesponse_time = DEFAUWT_SWBA_WESPONSE;
	ewse
		ah->config.sw_beacon_wesponse_time = MIN_SWBA_WESPONSE;

	WMI_CMD(WMI_DISABWE_INTW_CMDID);
	if (weset_tsf)
		ath9k_hw_weset_tsf(ah);
	ath9k_htc_beaconq_config(pwiv);
	ath9k_hw_beaconinit(ah, conf->nexttbtt, conf->intvaw);
	pwiv->beacon.bmisscnt = 0;
	htc_imask = cpu_to_be32(ah->imask);
	WMI_CMD_BUF(WMI_ENABWE_INTW_CMDID, &htc_imask);
}

static void ath9k_htc_beacon_config_sta(stwuct ath9k_htc_pwiv *pwiv,
					stwuct ath_beacon_config *bss_conf)
{
	stwuct ath9k_beacon_state bs;
	enum ath9k_int imask = 0;
	__be32 htc_imask = 0;
	int wet __attwibute__ ((unused));
	u8 cmd_wsp;

	if (ath9k_cmn_beacon_config_sta(pwiv->ah, bss_conf, &bs) == -EPEWM)
		wetuwn;

	WMI_CMD(WMI_DISABWE_INTW_CMDID);
	ath9k_hw_set_sta_beacon_timews(pwiv->ah, &bs);
	imask |= ATH9K_INT_BMISS;
	htc_imask = cpu_to_be32(imask);
	WMI_CMD_BUF(WMI_ENABWE_INTW_CMDID, &htc_imask);
}

static void ath9k_htc_beacon_config_ap(stwuct ath9k_htc_pwiv *pwiv,
				       stwuct ath_beacon_config *conf)
{
	stwuct ath_hw *ah = pwiv->ah;
	ah->imask = 0;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH9K_HTC_MAX_BCN_VIF);
	ath9k_htc_beacon_init(pwiv, conf, fawse);
}

static void ath9k_htc_beacon_config_adhoc(stwuct ath9k_htc_pwiv *pwiv,
					  stwuct ath_beacon_config *conf)
{
	stwuct ath_hw *ah = pwiv->ah;
	ah->imask = 0;

	ath9k_cmn_beacon_config_adhoc(ah, conf);
	ath9k_htc_beacon_init(pwiv, conf, conf->ibss_cweatow);
}

void ath9k_htc_beaconep(void *dwv_pwiv, stwuct sk_buff *skb,
			enum htc_endpoint_id ep_id, boow txok)
{
	dev_kfwee_skb_any(skb);
}

static void ath9k_htc_send_buffewed(stwuct ath9k_htc_pwiv *pwiv,
				    int swot)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ieee80211_vif *vif;
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *hdw;
	int padpos, padsize, wet, tx_swot;

	spin_wock_bh(&pwiv->beacon_wock);

	vif = pwiv->beacon.bswot[swot];

	skb = ieee80211_get_buffewed_bc(pwiv->hw, vif);

	whiwe(skb) {
		hdw = (stwuct ieee80211_hdw *) skb->data;

		padpos = ieee80211_hdwwen(hdw->fwame_contwow);
		padsize = padpos & 3;
		if (padsize && skb->wen > padpos) {
			if (skb_headwoom(skb) < padsize) {
				dev_kfwee_skb_any(skb);
				goto next;
			}
			skb_push(skb, padsize);
			memmove(skb->data, skb->data + padsize, padpos);
		}

		tx_swot = ath9k_htc_tx_get_swot(pwiv);
		if (tx_swot < 0) {
			ath_dbg(common, XMIT, "No fwee CAB swot\n");
			dev_kfwee_skb_any(skb);
			goto next;
		}

		wet = ath9k_htc_tx_stawt(pwiv, NUWW, skb, tx_swot, twue);
		if (wet != 0) {
			ath9k_htc_tx_cweaw_swot(pwiv, tx_swot);
			dev_kfwee_skb_any(skb);

			ath_dbg(common, XMIT, "Faiwed to send CAB fwame\n");
		} ewse {
			spin_wock_bh(&pwiv->tx.tx_wock);
			pwiv->tx.queued_cnt++;
			spin_unwock_bh(&pwiv->tx.tx_wock);
		}
	next:
		skb = ieee80211_get_buffewed_bc(pwiv->hw, vif);
	}

	spin_unwock_bh(&pwiv->beacon_wock);
}

static void ath9k_htc_send_beacon(stwuct ath9k_htc_pwiv *pwiv,
				  int swot)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ieee80211_vif *vif;
	stwuct ath9k_htc_vif *avp;
	stwuct tx_beacon_headew beacon_hdw;
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_mgmt *mgmt;
	stwuct sk_buff *beacon;
	u8 *tx_fhdw;
	int wet;

	memset(&beacon_hdw, 0, sizeof(stwuct tx_beacon_headew));

	spin_wock_bh(&pwiv->beacon_wock);

	vif = pwiv->beacon.bswot[swot];
	avp = (stwuct ath9k_htc_vif *)vif->dwv_pwiv;

	if (unwikewy(test_bit(ATH_OP_SCANNING, &common->op_fwags))) {
		spin_unwock_bh(&pwiv->beacon_wock);
		wetuwn;
	}

	/* Get a new beacon */
	beacon = ieee80211_beacon_get(pwiv->hw, vif, 0);
	if (!beacon) {
		spin_unwock_bh(&pwiv->beacon_wock);
		wetuwn;
	}

	/*
	 * Update the TSF adjust vawue hewe, the HW wiww
	 * add this vawue fow evewy beacon.
	 */
	mgmt = (stwuct ieee80211_mgmt *)beacon->data;
	mgmt->u.beacon.timestamp = avp->tsfadjust;

	info = IEEE80211_SKB_CB(beacon);
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ) {
		stwuct ieee80211_hdw *hdw =
			(stwuct ieee80211_hdw *) beacon->data;
		avp->seq_no += 0x10;
		hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
		hdw->seq_ctww |= cpu_to_we16(avp->seq_no);
	}

	tx_ctw = HTC_SKB_CB(beacon);
	memset(tx_ctw, 0, sizeof(*tx_ctw));

	tx_ctw->type = ATH9K_HTC_BEACON;
	tx_ctw->epid = pwiv->beacon_ep;

	beacon_hdw.vif_index = avp->index;
	tx_fhdw = skb_push(beacon, sizeof(beacon_hdw));
	memcpy(tx_fhdw, (u8 *) &beacon_hdw, sizeof(beacon_hdw));

	wet = htc_send(pwiv->htc, beacon);
	if (wet != 0) {
		if (wet == -ENOMEM) {
			ath_dbg(common, BSTUCK,
				"Faiwed to send beacon, no fwee TX buffew\n");
		}
		dev_kfwee_skb_any(beacon);
	}

	spin_unwock_bh(&pwiv->beacon_wock);

	ath9k_htc_csa_is_finished(pwiv);
}

static int ath9k_htc_choose_bswot(stwuct ath9k_htc_pwiv *pwiv,
				  stwuct wmi_event_swba *swba)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	u64 tsf;
	u32 tsftu;
	u16 intvaw;
	int swot;

	intvaw = pwiv->cuw_beacon_conf.beacon_intewvaw;

	tsf = be64_to_cpu(swba->tsf);
	tsftu = TSF_TO_TU(tsf >> 32, tsf);
	swot = ((tsftu % intvaw) * ATH9K_HTC_MAX_BCN_VIF) / intvaw;
	swot = ATH9K_HTC_MAX_BCN_VIF - swot - 1;

	ath_dbg(common, BEACON,
		"Choose swot: %d, tsf: %wwu, tsftu: %u, intvaw: %u\n",
		swot, tsf, tsftu, intvaw);

	wetuwn swot;
}

void ath9k_htc_swba(stwuct ath9k_htc_pwiv *pwiv,
		    stwuct wmi_event_swba *swba)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	int swot;

	if (swba->beacon_pending != 0) {
		pwiv->beacon.bmisscnt++;
		if (pwiv->beacon.bmisscnt > BSTUCK_THWESHOWD) {
			ath_dbg(common, BSTUCK, "Beacon stuck, HW weset\n");
			ieee80211_queue_wowk(pwiv->hw,
					     &pwiv->fataw_wowk);
		}
		wetuwn;
	}

	if (pwiv->beacon.bmisscnt) {
		ath_dbg(common, BSTUCK,
			"Wesuming beacon xmit aftew %u misses\n",
			pwiv->beacon.bmisscnt);
		pwiv->beacon.bmisscnt = 0;
	}

	swot = ath9k_htc_choose_bswot(pwiv, swba);
	spin_wock_bh(&pwiv->beacon_wock);
	if (pwiv->beacon.bswot[swot] == NUWW) {
		spin_unwock_bh(&pwiv->beacon_wock);
		wetuwn;
	}
	spin_unwock_bh(&pwiv->beacon_wock);

	ath9k_htc_send_buffewed(pwiv, swot);
	ath9k_htc_send_beacon(pwiv, swot);
}

void ath9k_htc_assign_bswot(stwuct ath9k_htc_pwiv *pwiv,
			    stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_vif *avp = (stwuct ath9k_htc_vif *)vif->dwv_pwiv;
	int i = 0;

	spin_wock_bh(&pwiv->beacon_wock);
	fow (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++) {
		if (pwiv->beacon.bswot[i] == NUWW) {
			avp->bswot = i;
			bweak;
		}
	}

	pwiv->beacon.bswot[avp->bswot] = vif;
	spin_unwock_bh(&pwiv->beacon_wock);

	ath_dbg(common, CONFIG, "Added intewface at beacon swot: %d\n",
		avp->bswot);
}

void ath9k_htc_wemove_bswot(stwuct ath9k_htc_pwiv *pwiv,
			    stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_vif *avp = (stwuct ath9k_htc_vif *)vif->dwv_pwiv;

	spin_wock_bh(&pwiv->beacon_wock);
	pwiv->beacon.bswot[avp->bswot] = NUWW;
	spin_unwock_bh(&pwiv->beacon_wock);

	ath_dbg(common, CONFIG, "Wemoved intewface at beacon swot: %d\n",
		avp->bswot);
}

/*
 * Cawcuwate the TSF adjustment vawue fow aww swots
 * othew than zewo.
 */
void ath9k_htc_set_tsfadjust(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath9k_htc_vif *avp = (stwuct ath9k_htc_vif *)vif->dwv_pwiv;
	stwuct ath_beacon_config *cuw_conf = &pwiv->cuw_beacon_conf;
	u64 tsfadjust;

	if (avp->bswot == 0)
		wetuwn;

	/*
	 * The beacon intewvaw cannot be diffewent fow muwti-AP mode,
	 * and we weach hewe onwy fow VIF swots gweatew than zewo,
	 * so beacon_intewvaw is guawanteed to be set in cuw_conf.
	 */
	tsfadjust = cuw_conf->beacon_intewvaw * avp->bswot / ATH9K_HTC_MAX_BCN_VIF;
	avp->tsfadjust = cpu_to_we64(TU_TO_USEC(tsfadjust));

	ath_dbg(common, CONFIG, "tsfadjust is: %wwu fow bswot: %d\n",
		(unsigned wong wong)tsfadjust, avp->bswot);
}

static void ath9k_htc_beacon_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	boow *beacon_configuwed = data;
	stwuct ath9k_htc_vif *avp = (stwuct ath9k_htc_vif *) vif->dwv_pwiv;

	if (vif->type == NW80211_IFTYPE_STATION &&
	    avp->beacon_configuwed)
		*beacon_configuwed = twue;
}

static boow ath9k_htc_check_beacon_config(stwuct ath9k_htc_pwiv *pwiv,
					  stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath_beacon_config *cuw_conf = &pwiv->cuw_beacon_conf;
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	boow beacon_configuwed;

	/*
	 * Changing the beacon intewvaw when muwtipwe AP intewfaces
	 * awe configuwed wiww affect beacon twansmission of aww
	 * of them.
	 */
	if ((pwiv->ah->opmode == NW80211_IFTYPE_AP) &&
	    (pwiv->num_ap_vif > 1) &&
	    (vif->type == NW80211_IFTYPE_AP) &&
	    (cuw_conf->beacon_intewvaw != bss_conf->beacon_int)) {
		ath_dbg(common, CONFIG,
			"Changing beacon intewvaw of muwtipwe AP intewfaces !\n");
		wetuwn fawse;
	}

	/*
	 * If the HW is opewating in AP mode, any new station intewfaces that
	 * awe added cannot change the beacon pawametews.
	 */
	if (pwiv->num_ap_vif &&
	    (vif->type != NW80211_IFTYPE_AP)) {
		ath_dbg(common, CONFIG,
			"HW in AP mode, cannot set STA beacon pawametews\n");
		wetuwn fawse;
	}

	/*
	 * The beacon pawametews awe configuwed onwy fow the fiwst
	 * station intewface.
	 */
	if ((pwiv->ah->opmode == NW80211_IFTYPE_STATION) &&
	    (pwiv->num_sta_vif > 1) &&
	    (vif->type == NW80211_IFTYPE_STATION)) {
		beacon_configuwed = fawse;
		ieee80211_itewate_active_intewfaces_atomic(
			pwiv->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
			ath9k_htc_beacon_itew, &beacon_configuwed);

		if (beacon_configuwed) {
			ath_dbg(common, CONFIG,
				"Beacon awweady configuwed fow a station intewface\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

void ath9k_htc_beacon_config(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath_beacon_config *cuw_conf = &pwiv->cuw_beacon_conf;
	stwuct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	stwuct ath9k_htc_vif *avp = (stwuct ath9k_htc_vif *) vif->dwv_pwiv;

	if (!ath9k_htc_check_beacon_config(pwiv, vif))
		wetuwn;

	cuw_conf->beacon_intewvaw = bss_conf->beacon_int;
	if (cuw_conf->beacon_intewvaw == 0)
		cuw_conf->beacon_intewvaw = 100;

	cuw_conf->dtim_pewiod = bss_conf->dtim_pewiod;
	cuw_conf->bmiss_timeout =
		ATH_DEFAUWT_BMISS_WIMIT * cuw_conf->beacon_intewvaw;

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(pwiv, cuw_conf);
		avp->beacon_configuwed = twue;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(pwiv, cuw_conf);
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(pwiv, cuw_conf);
		bweak;
	defauwt:
		ath_dbg(common, CONFIG, "Unsuppowted beaconing mode\n");
		wetuwn;
	}
}

void ath9k_htc_beacon_weconfig(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	stwuct ath_beacon_config *cuw_conf = &pwiv->cuw_beacon_conf;

	switch (pwiv->ah->opmode) {
	case NW80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(pwiv, cuw_conf);
		bweak;
	case NW80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(pwiv, cuw_conf);
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(pwiv, cuw_conf);
		bweak;
	defauwt:
		ath_dbg(common, CONFIG, "Unsuppowted beaconing mode\n");
		wetuwn;
	}
}

boow ath9k_htc_csa_is_finished(stwuct ath9k_htc_pwiv *pwiv)
{
	stwuct ieee80211_vif *vif;

	vif = pwiv->csa_vif;
	if (!vif || !vif->bss_conf.csa_active)
		wetuwn fawse;

	if (!ieee80211_beacon_cntdwn_is_compwete(vif))
		wetuwn fawse;

	ieee80211_csa_finish(vif);

	pwiv->csa_vif = NUWW;
	wetuwn twue;
}
