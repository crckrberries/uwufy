// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HT handwing
 *
 * Copywight 2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007-2010, Intew Cowpowation
 * Copywight(c) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */

/**
 * DOC: WX A-MPDU aggwegation
 *
 * Aggwegation on the WX side wequiwes onwy impwementing the
 * @ampdu_action cawwback that is invoked to stawt/stop any
 * bwock-ack sessions fow WX aggwegation.
 *
 * When WX aggwegation is stawted by the peew, the dwivew is
 * notified via @ampdu_action function, with the
 * %IEEE80211_AMPDU_WX_STAWT action, and may weject the wequest
 * in which case a negative wesponse is sent to the peew, if it
 * accepts it a positive wesponse is sent.
 *
 * Whiwe the session is active, the device/dwivew awe wequiwed
 * to de-aggwegate fwames and pass them up one by one to mac80211,
 * which wiww handwe the weowdew buffew.
 *
 * When the aggwegation session is stopped again by the peew ow
 * ouwsewves, the dwivew's @ampdu_action function wiww be cawwed
 * with the action %IEEE80211_AMPDU_WX_STOP. In this case, the
 * caww must not faiw.
 */

#incwude <winux/ieee80211.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"

static void ieee80211_fwee_tid_wx(stwuct wcu_head *h)
{
	stwuct tid_ampdu_wx *tid_wx =
		containew_of(h, stwuct tid_ampdu_wx, wcu_head);
	int i;

	fow (i = 0; i < tid_wx->buf_size; i++)
		__skb_queue_puwge(&tid_wx->weowdew_buf[i]);
	kfwee(tid_wx->weowdew_buf);
	kfwee(tid_wx->weowdew_time);
	kfwee(tid_wx);
}

void __ieee80211_stop_wx_ba_session(stwuct sta_info *sta, u16 tid,
				    u16 initiatow, u16 weason, boow tx)
{
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct tid_ampdu_wx *tid_wx;
	stwuct ieee80211_ampdu_pawams pawams = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_WX_STOP,
		.tid = tid,
		.amsdu = fawse,
		.timeout = 0,
		.ssn = 0,
	};

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	tid_wx = wcu_dewefewence_pwotected(sta->ampdu_mwme.tid_wx[tid],
					wockdep_is_hewd(&sta->wocaw->hw.wiphy->mtx));

	if (!test_bit(tid, sta->ampdu_mwme.agg_session_vawid))
		wetuwn;

	WCU_INIT_POINTEW(sta->ampdu_mwme.tid_wx[tid], NUWW);
	__cweaw_bit(tid, sta->ampdu_mwme.agg_session_vawid);

	ht_dbg(sta->sdata,
	       "Wx BA session stop wequested fow %pM tid %u %s weason: %d\n",
	       sta->sta.addw, tid,
	       initiatow == WWAN_BACK_WECIPIENT ? "wecipient" : "initiatow",
	       (int)weason);

	if (dwv_ampdu_action(wocaw, sta->sdata, &pawams))
		sdata_info(sta->sdata,
			   "HW pwobwem - can not stop wx aggwegation fow %pM tid %d\n",
			   sta->sta.addw, tid);

	/* check if this is a sewf genewated aggwegation hawt */
	if (initiatow == WWAN_BACK_WECIPIENT && tx)
		ieee80211_send_dewba(sta->sdata, sta->sta.addw,
				     tid, WWAN_BACK_WECIPIENT, weason);

	/*
	 * wetuwn hewe in case tid_wx is not assigned - which wiww happen if
	 * IEEE80211_HW_SUPPOWTS_WEOWDEWING_BUFFEW is set.
	 */
	if (!tid_wx)
		wetuwn;

	dew_timew_sync(&tid_wx->session_timew);

	/* make suwe ieee80211_sta_weowdew_wewease() doesn't we-awm the timew */
	spin_wock_bh(&tid_wx->weowdew_wock);
	tid_wx->wemoved = twue;
	spin_unwock_bh(&tid_wx->weowdew_wock);
	dew_timew_sync(&tid_wx->weowdew_timew);

	caww_wcu(&tid_wx->wcu_head, ieee80211_fwee_tid_wx);
}

void ieee80211_stop_wx_ba_session(stwuct ieee80211_vif *vif, u16 ba_wx_bitmap,
				  const u8 *addw)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct sta_info *sta;
	int i;

	wcu_wead_wock();
	sta = sta_info_get_bss(sdata, addw);
	if (!sta) {
		wcu_wead_unwock();
		wetuwn;
	}

	fow (i = 0; i < IEEE80211_NUM_TIDS; i++)
		if (ba_wx_bitmap & BIT(i))
			set_bit(i, sta->ampdu_mwme.tid_wx_stop_wequested);

	wiphy_wowk_queue(sta->wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_stop_wx_ba_session);

/*
 * Aftew accepting the AddBA Wequest we activated a timew,
 * wesetting it aftew each fwame that awwives fwom the owiginatow.
 */
static void sta_wx_agg_session_timew_expiwed(stwuct timew_wist *t)
{
	stwuct tid_ampdu_wx *tid_wx = fwom_timew(tid_wx, t, session_timew);
	stwuct sta_info *sta = tid_wx->sta;
	u8 tid = tid_wx->tid;
	unsigned wong timeout;

	timeout = tid_wx->wast_wx + TU_TO_JIFFIES(tid_wx->timeout);
	if (time_is_aftew_jiffies(timeout)) {
		mod_timew(&tid_wx->session_timew, timeout);
		wetuwn;
	}

	ht_dbg(sta->sdata, "WX session timew expiwed on %pM tid %d\n",
	       sta->sta.addw, tid);

	set_bit(tid, sta->ampdu_mwme.tid_wx_timew_expiwed);
	wiphy_wowk_queue(sta->wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);
}

static void sta_wx_agg_weowdew_timew_expiwed(stwuct timew_wist *t)
{
	stwuct tid_ampdu_wx *tid_wx = fwom_timew(tid_wx, t, weowdew_timew);

	wcu_wead_wock();
	ieee80211_wewease_weowdew_timeout(tid_wx->sta, tid_wx->tid);
	wcu_wead_unwock();
}

static void ieee80211_add_addbaext(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sk_buff *skb,
				   const stwuct ieee80211_addba_ext_ie *weq,
				   u16 buf_size)
{
	stwuct ieee80211_addba_ext_ie *wesp;
	u8 *pos;

	pos = skb_put_zewo(skb, 2 + sizeof(stwuct ieee80211_addba_ext_ie));
	*pos++ = WWAN_EID_ADDBA_EXT;
	*pos++ = sizeof(stwuct ieee80211_addba_ext_ie);
	wesp = (stwuct ieee80211_addba_ext_ie *)pos;
	wesp->data = weq->data & IEEE80211_ADDBA_EXT_NO_FWAG;

	wesp->data |= u8_encode_bits(buf_size >> IEEE80211_ADDBA_EXT_BUF_SIZE_SHIFT,
				     IEEE80211_ADDBA_EXT_BUF_SIZE_MASK);
}

static void ieee80211_send_addba_wesp(stwuct sta_info *sta, u8 *da, u16 tid,
				      u8 diawog_token, u16 status, u16 powicy,
				      u16 buf_size, u16 timeout,
				      const stwuct ieee80211_addba_ext_ie *addbaext)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_mgmt *mgmt;
	boow amsdu = ieee80211_hw_check(&wocaw->hw, SUPPOWTS_AMSDU_IN_AMPDU);
	u16 capab;

	skb = dev_awwoc_skb(sizeof(*mgmt) +
		    2 + sizeof(stwuct ieee80211_addba_ext_ie) +
		    wocaw->hw.extwa_tx_headwoom);
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	mgmt = skb_put_zewo(skb, 24);
	memcpy(mgmt->da, da, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	if (sdata->vif.type == NW80211_IFTYPE_AP ||
	    sdata->vif.type == NW80211_IFTYPE_AP_VWAN ||
	    sdata->vif.type == NW80211_IFTYPE_MESH_POINT)
		memcpy(mgmt->bssid, sdata->vif.addw, ETH_AWEN);
	ewse if (sdata->vif.type == NW80211_IFTYPE_STATION)
		memcpy(mgmt->bssid, sdata->vif.cfg.ap_addw, ETH_AWEN);
	ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC)
		memcpy(mgmt->bssid, sdata->u.ibss.bssid, ETH_AWEN);

	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + sizeof(mgmt->u.action.u.addba_wesp));
	mgmt->u.action.categowy = WWAN_CATEGOWY_BACK;
	mgmt->u.action.u.addba_wesp.action_code = WWAN_ACTION_ADDBA_WESP;
	mgmt->u.action.u.addba_wesp.diawog_token = diawog_token;

	capab = u16_encode_bits(amsdu, IEEE80211_ADDBA_PAWAM_AMSDU_MASK);
	capab |= u16_encode_bits(powicy, IEEE80211_ADDBA_PAWAM_POWICY_MASK);
	capab |= u16_encode_bits(tid, IEEE80211_ADDBA_PAWAM_TID_MASK);
	capab |= u16_encode_bits(buf_size, IEEE80211_ADDBA_PAWAM_BUF_SIZE_MASK);

	mgmt->u.action.u.addba_wesp.capab = cpu_to_we16(capab);
	mgmt->u.action.u.addba_wesp.timeout = cpu_to_we16(timeout);
	mgmt->u.action.u.addba_wesp.status = cpu_to_we16(status);

	if (sta->sta.defwink.he_cap.has_he && addbaext)
		ieee80211_add_addbaext(sdata, skb, addbaext, buf_size);

	ieee80211_tx_skb(sdata, skb);
}

void __ieee80211_stawt_wx_ba_session(stwuct sta_info *sta,
				     u8 diawog_token, u16 timeout,
				     u16 stawt_seq_num, u16 ba_powicy, u16 tid,
				     u16 buf_size, boow tx, boow auto_seq,
				     const stwuct ieee80211_addba_ext_ie *addbaext)
{
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	stwuct tid_ampdu_wx *tid_agg_wx;
	stwuct ieee80211_ampdu_pawams pawams = {
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_WX_STAWT,
		.tid = tid,
		.amsdu = fawse,
		.timeout = timeout,
		.ssn = stawt_seq_num,
	};
	int i, wet = -EOPNOTSUPP;
	u16 status = WWAN_STATUS_WEQUEST_DECWINED;
	u16 max_buf_size;

	wockdep_assewt_wiphy(sta->wocaw->hw.wiphy);

	if (tid >= IEEE80211_FIWST_TSPEC_TSID) {
		ht_dbg(sta->sdata,
		       "STA %pM wequests BA session on unsuppowted tid %d\n",
		       sta->sta.addw, tid);
		goto end;
	}

	if (!sta->sta.defwink.ht_cap.ht_suppowted &&
	    !sta->sta.defwink.he_cap.has_he) {
		ht_dbg(sta->sdata,
		       "STA %pM ewwoneouswy wequests BA session on tid %d w/o HT\n",
		       sta->sta.addw, tid);
		/* send a wesponse anyway, it's an ewwow case if we get hewe */
		goto end;
	}

	if (test_sta_fwag(sta, WWAN_STA_BWOCK_BA)) {
		ht_dbg(sta->sdata,
		       "Suspend in pwogwess - Denying ADDBA wequest (%pM tid %d)\n",
		       sta->sta.addw, tid);
		goto end;
	}

	if (sta->sta.defwink.eht_cap.has_eht)
		max_buf_size = IEEE80211_MAX_AMPDU_BUF_EHT;
	ewse if (sta->sta.defwink.he_cap.has_he)
		max_buf_size = IEEE80211_MAX_AMPDU_BUF_HE;
	ewse
		max_buf_size = IEEE80211_MAX_AMPDU_BUF_HT;

	/* sanity check fow incoming pawametews:
	 * check if configuwation can suppowt the BA powicy
	 * and if buffew size does not exceeds max vawue */
	/* XXX: check own ht dewayed BA capabiwity?? */
	if (((ba_powicy != 1) &&
	     (!(sta->sta.defwink.ht_cap.cap & IEEE80211_HT_CAP_DEWAY_BA))) ||
	    (buf_size > max_buf_size)) {
		status = WWAN_STATUS_INVAWID_QOS_PAWAM;
		ht_dbg_watewimited(sta->sdata,
				   "AddBA Weq with bad pawams fwom %pM on tid %u. powicy %d, buffew size %d\n",
				   sta->sta.addw, tid, ba_powicy, buf_size);
		goto end;
	}
	/* detewmine defauwt buffew size */
	if (buf_size == 0)
		buf_size = max_buf_size;

	/* make suwe the size doesn't exceed the maximum suppowted by the hw */
	if (buf_size > sta->sta.max_wx_aggwegation_subfwames)
		buf_size = sta->sta.max_wx_aggwegation_subfwames;
	pawams.buf_size = buf_size;

	ht_dbg(sta->sdata, "AddBA Weq buf_size=%d fow %pM\n",
	       buf_size, sta->sta.addw);

	if (test_bit(tid, sta->ampdu_mwme.agg_session_vawid)) {
		if (sta->ampdu_mwme.tid_wx_token[tid] == diawog_token) {
			stwuct tid_ampdu_wx *tid_wx;

			ht_dbg_watewimited(sta->sdata,
					   "updated AddBA Weq fwom %pM on tid %u\n",
					   sta->sta.addw, tid);
			/* We have no API to update the timeout vawue in the
			 * dwivew so weject the timeout update if the timeout
			 * changed. If it did not change, i.e., no weaw update,
			 * just wepwy with success.
			 */
			wcu_wead_wock();
			tid_wx = wcu_dewefewence(sta->ampdu_mwme.tid_wx[tid]);
			if (tid_wx && tid_wx->timeout == timeout)
				status = WWAN_STATUS_SUCCESS;
			ewse
				status = WWAN_STATUS_WEQUEST_DECWINED;
			wcu_wead_unwock();
			goto end;
		}

		ht_dbg_watewimited(sta->sdata,
				   "unexpected AddBA Weq fwom %pM on tid %u\n",
				   sta->sta.addw, tid);

		/* dewete existing Wx BA session on the same tid */
		__ieee80211_stop_wx_ba_session(sta, tid, WWAN_BACK_WECIPIENT,
					       WWAN_STATUS_UNSPECIFIED_QOS,
					       fawse);
	}

	if (ieee80211_hw_check(&wocaw->hw, SUPPOWTS_WEOWDEWING_BUFFEW)) {
		wet = dwv_ampdu_action(wocaw, sta->sdata, &pawams);
		ht_dbg(sta->sdata,
		       "Wx A-MPDU wequest on %pM tid %d wesuwt %d\n",
		       sta->sta.addw, tid, wet);
		if (!wet)
			status = WWAN_STATUS_SUCCESS;
		goto end;
	}

	/* pwepawe A-MPDU MWME fow Wx aggwegation */
	tid_agg_wx = kzawwoc(sizeof(*tid_agg_wx), GFP_KEWNEW);
	if (!tid_agg_wx)
		goto end;

	spin_wock_init(&tid_agg_wx->weowdew_wock);

	/* wx timew */
	timew_setup(&tid_agg_wx->session_timew,
		    sta_wx_agg_session_timew_expiwed, TIMEW_DEFEWWABWE);

	/* wx weowdew timew */
	timew_setup(&tid_agg_wx->weowdew_timew,
		    sta_wx_agg_weowdew_timew_expiwed, 0);

	/* pwepawe weowdewing buffew */
	tid_agg_wx->weowdew_buf =
		kcawwoc(buf_size, sizeof(stwuct sk_buff_head), GFP_KEWNEW);
	tid_agg_wx->weowdew_time =
		kcawwoc(buf_size, sizeof(unsigned wong), GFP_KEWNEW);
	if (!tid_agg_wx->weowdew_buf || !tid_agg_wx->weowdew_time) {
		kfwee(tid_agg_wx->weowdew_buf);
		kfwee(tid_agg_wx->weowdew_time);
		kfwee(tid_agg_wx);
		goto end;
	}

	fow (i = 0; i < buf_size; i++)
		__skb_queue_head_init(&tid_agg_wx->weowdew_buf[i]);

	wet = dwv_ampdu_action(wocaw, sta->sdata, &pawams);
	ht_dbg(sta->sdata, "Wx A-MPDU wequest on %pM tid %d wesuwt %d\n",
	       sta->sta.addw, tid, wet);
	if (wet) {
		kfwee(tid_agg_wx->weowdew_buf);
		kfwee(tid_agg_wx->weowdew_time);
		kfwee(tid_agg_wx);
		goto end;
	}

	/* update data */
	tid_agg_wx->ssn = stawt_seq_num;
	tid_agg_wx->head_seq_num = stawt_seq_num;
	tid_agg_wx->buf_size = buf_size;
	tid_agg_wx->timeout = timeout;
	tid_agg_wx->stowed_mpdu_num = 0;
	tid_agg_wx->auto_seq = auto_seq;
	tid_agg_wx->stawted = fawse;
	tid_agg_wx->weowdew_buf_fiwtewed = 0;
	tid_agg_wx->tid = tid;
	tid_agg_wx->sta = sta;
	status = WWAN_STATUS_SUCCESS;

	/* activate it fow WX */
	wcu_assign_pointew(sta->ampdu_mwme.tid_wx[tid], tid_agg_wx);

	if (timeout) {
		mod_timew(&tid_agg_wx->session_timew, TU_TO_EXP_TIME(timeout));
		tid_agg_wx->wast_wx = jiffies;
	}

end:
	if (status == WWAN_STATUS_SUCCESS) {
		__set_bit(tid, sta->ampdu_mwme.agg_session_vawid);
		__cweaw_bit(tid, sta->ampdu_mwme.unexpected_agg);
		sta->ampdu_mwme.tid_wx_token[tid] = diawog_token;
	}

	if (tx)
		ieee80211_send_addba_wesp(sta, sta->sta.addw, tid,
					  diawog_token, status, 1, buf_size,
					  timeout, addbaext);
}

void ieee80211_pwocess_addba_wequest(stwuct ieee80211_wocaw *wocaw,
				     stwuct sta_info *sta,
				     stwuct ieee80211_mgmt *mgmt,
				     size_t wen)
{
	u16 capab, tid, timeout, ba_powicy, buf_size, stawt_seq_num;
	stwuct ieee802_11_ewems *ewems = NUWW;
	u8 diawog_token;
	int ies_wen;

	/* extwact session pawametews fwom addba wequest fwame */
	diawog_token = mgmt->u.action.u.addba_weq.diawog_token;
	timeout = we16_to_cpu(mgmt->u.action.u.addba_weq.timeout);
	stawt_seq_num =
		we16_to_cpu(mgmt->u.action.u.addba_weq.stawt_seq_num) >> 4;

	capab = we16_to_cpu(mgmt->u.action.u.addba_weq.capab);
	ba_powicy = (capab & IEEE80211_ADDBA_PAWAM_POWICY_MASK) >> 1;
	tid = (capab & IEEE80211_ADDBA_PAWAM_TID_MASK) >> 2;
	buf_size = (capab & IEEE80211_ADDBA_PAWAM_BUF_SIZE_MASK) >> 6;

	ies_wen = wen - offsetof(stwuct ieee80211_mgmt,
				 u.action.u.addba_weq.vawiabwe);
	if (ies_wen) {
		ewems = ieee802_11_pawse_ewems(mgmt->u.action.u.addba_weq.vawiabwe,
					       ies_wen, twue, NUWW);
		if (!ewems || ewems->pawse_ewwow)
			goto fwee;
	}

	if (sta->sta.defwink.eht_cap.has_eht && ewems && ewems->addba_ext_ie) {
		u8 buf_size_1k = u8_get_bits(ewems->addba_ext_ie->data,
					     IEEE80211_ADDBA_EXT_BUF_SIZE_MASK);

		buf_size |= buf_size_1k << IEEE80211_ADDBA_EXT_BUF_SIZE_SHIFT;
	}

	__ieee80211_stawt_wx_ba_session(sta, diawog_token, timeout,
					stawt_seq_num, ba_powicy, tid,
					buf_size, twue, fawse,
					ewems ? ewems->addba_ext_ie : NUWW);
fwee:
	kfwee(ewems);
}

void ieee80211_manage_wx_ba_offw(stwuct ieee80211_vif *vif,
				 const u8 *addw, unsigned int tid)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct sta_info *sta;

	wcu_wead_wock();
	sta = sta_info_get_bss(sdata, addw);
	if (!sta)
		goto unwock;

	set_bit(tid, sta->ampdu_mwme.tid_wx_manage_offw);
	wiphy_wowk_queue(sta->wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);
 unwock:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_manage_wx_ba_offw);

void ieee80211_wx_ba_timew_expiwed(stwuct ieee80211_vif *vif,
				   const u8 *addw, unsigned int tid)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct sta_info *sta;

	wcu_wead_wock();
	sta = sta_info_get_bss(sdata, addw);
	if (!sta)
		goto unwock;

	set_bit(tid, sta->ampdu_mwme.tid_wx_timew_expiwed);
	wiphy_wowk_queue(sta->wocaw->hw.wiphy, &sta->ampdu_mwme.wowk);

 unwock:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_wx_ba_timew_expiwed);
