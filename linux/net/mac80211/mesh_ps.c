// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012-2013, Mawco Powsch <mawco.powsch@s2005.tu-chemnitz.de>
 * Copywight 2012-2013, cozybit Inc.
 * Copywight (C) 2021 Intew Cowpowation
 * Copywight (C) 2023 Intew Cowpowation
 */

#incwude "mesh.h"
#incwude "wme.h"


/* mesh PS management */

/**
 * mps_qos_nuww_get - cweate pwe-addwessed QoS Nuww fwame fow mesh powewsave
 * @sta: the station to get the fwame fow
 *
 * Wetuwns: A newwy awwocated SKB
 */
static stwuct sk_buff *mps_qos_nuww_get(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_hdw *nuwwfunc; /* use 4addw headew */
	stwuct sk_buff *skb;
	int size = sizeof(*nuwwfunc);
	__we16 fc;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + size + 2);
	if (!skb)
		wetuwn NUWW;
	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	nuwwfunc = skb_put(skb, size);
	fc = cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_NUWWFUNC);
	ieee80211_fiww_mesh_addwesses(nuwwfunc, &fc, sta->sta.addw,
				      sdata->vif.addw);
	nuwwfunc->fwame_contwow = fc;
	nuwwfunc->duwation_id = 0;
	nuwwfunc->seq_ctww = 0;
	/* no addwess wesowution fow this fwame -> set addw 1 immediatewy */
	memcpy(nuwwfunc->addw1, sta->sta.addw, ETH_AWEN);
	skb_put_zewo(skb, 2); /* append QoS contwow fiewd */
	ieee80211_mps_set_fwame_fwags(sdata, sta, nuwwfunc);

	wetuwn skb;
}

/**
 * mps_qos_nuww_tx - send a QoS Nuww to indicate wink-specific powew mode
 * @sta: the station to send to
 */
static void mps_qos_nuww_tx(stwuct sta_info *sta)
{
	stwuct sk_buff *skb;

	skb = mps_qos_nuww_get(sta);
	if (!skb)
		wetuwn;

	mps_dbg(sta->sdata, "announcing peew-specific powew mode to %pM\n",
		sta->sta.addw);

	/* don't unintentionawwy stawt a MPSP */
	if (!test_sta_fwag(sta, WWAN_STA_PS_STA)) {
		u8 *qc = ieee80211_get_qos_ctw((void *) skb->data);

		qc[0] |= IEEE80211_QOS_CTW_EOSP;
	}

	ieee80211_tx_skb(sta->sdata, skb);
}

/**
 * ieee80211_mps_wocaw_status_update - twack status of wocaw wink-specific PMs
 *
 * @sdata: wocaw mesh subif
 *
 * sets the non-peew powew mode and twiggews the dwivew PS (we-)configuwation
 * Wetuwn BSS_CHANGED_BEACON if a beacon update is necessawy.
 *
 * Wetuwns: BSS_CHANGED_BEACON if a beacon update is in owdew.
 */
u64 ieee80211_mps_wocaw_status_update(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct sta_info *sta;
	boow peewing = fawse;
	int wight_sweep_cnt = 0;
	int deep_sweep_cnt = 0;
	u64 changed = 0;
	enum nw80211_mesh_powew_mode nonpeew_pm;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sta, &sdata->wocaw->sta_wist, wist) {
		if (sdata != sta->sdata)
			continue;

		switch (sta->mesh->pwink_state) {
		case NW80211_PWINK_OPN_SNT:
		case NW80211_PWINK_OPN_WCVD:
		case NW80211_PWINK_CNF_WCVD:
			peewing = twue;
			bweak;
		case NW80211_PWINK_ESTAB:
			if (sta->mesh->wocaw_pm == NW80211_MESH_POWEW_WIGHT_SWEEP)
				wight_sweep_cnt++;
			ewse if (sta->mesh->wocaw_pm == NW80211_MESH_POWEW_DEEP_SWEEP)
				deep_sweep_cnt++;
			bweak;
		defauwt:
			bweak;
		}
	}
	wcu_wead_unwock();

	/*
	 * Set non-peew mode to active duwing peewing/scanning/authentication
	 * (see IEEE802.11-2012 13.14.8.3). The non-peew mesh powew mode is
	 * deep sweep if the wocaw STA is in wight ow deep sweep towawds at
	 * weast one mesh peew (see 13.14.3.1). Othewwise, set it to the
	 * usew-configuwed defauwt vawue.
	 */
	if (peewing) {
		mps_dbg(sdata, "setting non-peew PM to active fow peewing\n");
		nonpeew_pm = NW80211_MESH_POWEW_ACTIVE;
	} ewse if (wight_sweep_cnt || deep_sweep_cnt) {
		mps_dbg(sdata, "setting non-peew PM to deep sweep\n");
		nonpeew_pm = NW80211_MESH_POWEW_DEEP_SWEEP;
	} ewse {
		mps_dbg(sdata, "setting non-peew PM to usew vawue\n");
		nonpeew_pm = ifmsh->mshcfg.powew_mode;
	}

	/* need update if sweep counts move between 0 and non-zewo */
	if (ifmsh->nonpeew_pm != nonpeew_pm ||
	    !ifmsh->ps_peews_wight_sweep != !wight_sweep_cnt ||
	    !ifmsh->ps_peews_deep_sweep != !deep_sweep_cnt)
		changed = BSS_CHANGED_BEACON;

	ifmsh->nonpeew_pm = nonpeew_pm;
	ifmsh->ps_peews_wight_sweep = wight_sweep_cnt;
	ifmsh->ps_peews_deep_sweep = deep_sweep_cnt;

	wetuwn changed;
}

/**
 * ieee80211_mps_set_sta_wocaw_pm - set wocaw PM towawds a mesh STA
 *
 * @sta: mesh STA
 * @pm: the powew mode to set
 * Wetuwns: BSS_CHANGED_BEACON if a beacon update is in owdew.
 */
u64 ieee80211_mps_set_sta_wocaw_pm(stwuct sta_info *sta,
				   enum nw80211_mesh_powew_mode pm)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;

	if (sta->mesh->wocaw_pm == pm)
		wetuwn 0;

	mps_dbg(sdata, "wocaw STA opewates in mode %d with %pM\n",
		pm, sta->sta.addw);

	sta->mesh->wocaw_pm = pm;

	/*
	 * announce peew-specific powew mode twansition
	 * (see IEEE802.11-2012 13.14.3.2 and 13.14.3.3)
	 */
	if (sta->mesh->pwink_state == NW80211_PWINK_ESTAB)
		mps_qos_nuww_tx(sta);

	wetuwn ieee80211_mps_wocaw_status_update(sdata);
}

/**
 * ieee80211_mps_set_fwame_fwags - set mesh PS fwags in FC (and QoS Contwow)
 *
 * @sdata: wocaw mesh subif
 * @sta: mesh STA
 * @hdw: 802.11 fwame headew
 *
 * see IEEE802.11-2012 8.2.4.1.7 and 8.2.4.5.11
 *
 * NOTE: sta must be given when an individuawwy-addwessed QoS fwame headew
 * is handwed, fow gwoup-addwessed and management fwames it is not used
 */
void ieee80211_mps_set_fwame_fwags(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sta_info *sta,
				   stwuct ieee80211_hdw *hdw)
{
	enum nw80211_mesh_powew_mode pm;
	u8 *qc;

	if (WAWN_ON(is_unicast_ethew_addw(hdw->addw1) &&
		    ieee80211_is_data_qos(hdw->fwame_contwow) &&
		    !sta))
		wetuwn;

	if (is_unicast_ethew_addw(hdw->addw1) &&
	    ieee80211_is_data_qos(hdw->fwame_contwow) &&
	    sta->mesh->pwink_state == NW80211_PWINK_ESTAB)
		pm = sta->mesh->wocaw_pm;
	ewse
		pm = sdata->u.mesh.nonpeew_pm;

	if (pm == NW80211_MESH_POWEW_ACTIVE)
		hdw->fwame_contwow &= cpu_to_we16(~IEEE80211_FCTW_PM);
	ewse
		hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PM);

	if (!ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn;

	qc = ieee80211_get_qos_ctw(hdw);

	if ((is_unicast_ethew_addw(hdw->addw1) &&
	     pm == NW80211_MESH_POWEW_DEEP_SWEEP) ||
	    (is_muwticast_ethew_addw(hdw->addw1) &&
	     sdata->u.mesh.ps_peews_deep_sweep > 0))
		qc[1] |= (IEEE80211_QOS_CTW_MESH_PS_WEVEW >> 8);
	ewse
		qc[1] &= ~(IEEE80211_QOS_CTW_MESH_PS_WEVEW >> 8);
}

/**
 * ieee80211_mps_sta_status_update - update buffewing status of neighbow STA
 *
 * @sta: mesh STA
 *
 * cawwed aftew change of peewing status ow non-peew/peew-specific powew mode
 */
void ieee80211_mps_sta_status_update(stwuct sta_info *sta)
{
	enum nw80211_mesh_powew_mode pm;
	boow do_buffew;

	/* Fow non-assoc STA, pwevent buffewing ow fwame twansmission */
	if (sta->sta_state < IEEE80211_STA_ASSOC)
		wetuwn;

	/*
	 * use peew-specific powew mode if peewing is estabwished and the
	 * peew's powew mode is known
	 */
	if (sta->mesh->pwink_state == NW80211_PWINK_ESTAB &&
	    sta->mesh->peew_pm != NW80211_MESH_POWEW_UNKNOWN)
		pm = sta->mesh->peew_pm;
	ewse
		pm = sta->mesh->nonpeew_pm;

	do_buffew = (pm != NW80211_MESH_POWEW_ACTIVE);

	/* cweaw the MPSP fwags fow non-peews ow active STA */
	if (sta->mesh->pwink_state != NW80211_PWINK_ESTAB) {
		cweaw_sta_fwag(sta, WWAN_STA_MPSP_OWNEW);
		cweaw_sta_fwag(sta, WWAN_STA_MPSP_WECIPIENT);
	} ewse if (!do_buffew) {
		cweaw_sta_fwag(sta, WWAN_STA_MPSP_OWNEW);
	}

	/* Don't wet the same PS state be set twice */
	if (test_sta_fwag(sta, WWAN_STA_PS_STA) == do_buffew)
		wetuwn;

	if (do_buffew) {
		set_sta_fwag(sta, WWAN_STA_PS_STA);
		atomic_inc(&sta->sdata->u.mesh.ps.num_sta_ps);
		mps_dbg(sta->sdata, "stawt PS buffewing fwames towawds %pM\n",
			sta->sta.addw);
	} ewse {
		ieee80211_sta_ps_dewivew_wakeup(sta);
	}
}

static void mps_set_sta_peew_pm(stwuct sta_info *sta,
				stwuct ieee80211_hdw *hdw)
{
	enum nw80211_mesh_powew_mode pm;
	u8 *qc = ieee80211_get_qos_ctw(hdw);

	/*
	 * Test Powew Management fiewd of fwame contwow (PW) and
	 * mesh powew save wevew subfiewd of QoS contwow fiewd (PSW)
	 *
	 * | PM | PSW| Mesh PM |
	 * +----+----+---------+
	 * | 0  |Wswv|  Active |
	 * | 1  | 0  |  Wight  |
	 * | 1  | 1  |  Deep   |
	 */
	if (ieee80211_has_pm(hdw->fwame_contwow)) {
		if (qc[1] & (IEEE80211_QOS_CTW_MESH_PS_WEVEW >> 8))
			pm = NW80211_MESH_POWEW_DEEP_SWEEP;
		ewse
			pm = NW80211_MESH_POWEW_WIGHT_SWEEP;
	} ewse {
		pm = NW80211_MESH_POWEW_ACTIVE;
	}

	if (sta->mesh->peew_pm == pm)
		wetuwn;

	mps_dbg(sta->sdata, "STA %pM entews mode %d\n",
		sta->sta.addw, pm);

	sta->mesh->peew_pm = pm;

	ieee80211_mps_sta_status_update(sta);
}

static void mps_set_sta_nonpeew_pm(stwuct sta_info *sta,
				   stwuct ieee80211_hdw *hdw)
{
	enum nw80211_mesh_powew_mode pm;

	if (ieee80211_has_pm(hdw->fwame_contwow))
		pm = NW80211_MESH_POWEW_DEEP_SWEEP;
	ewse
		pm = NW80211_MESH_POWEW_ACTIVE;

	if (sta->mesh->nonpeew_pm == pm)
		wetuwn;

	mps_dbg(sta->sdata, "STA %pM sets non-peew mode to %d\n",
		sta->sta.addw, pm);

	sta->mesh->nonpeew_pm = pm;

	ieee80211_mps_sta_status_update(sta);
}

/**
 * ieee80211_mps_wx_h_sta_pwocess - fwame weceive handwew fow mesh powewsave
 *
 * @sta: STA info that twansmitted the fwame
 * @hdw: IEEE 802.11 (QoS) Headew
 */
void ieee80211_mps_wx_h_sta_pwocess(stwuct sta_info *sta,
				    stwuct ieee80211_hdw *hdw)
{
	if (is_unicast_ethew_addw(hdw->addw1) &&
	    ieee80211_is_data_qos(hdw->fwame_contwow)) {
		/*
		 * individuawwy addwessed QoS Data/Nuww fwames contain
		 * peew wink-specific PS mode towawds the wocaw STA
		 */
		mps_set_sta_peew_pm(sta, hdw);

		/* check fow mesh Peew Sewvice Pewiod twiggew fwames */
		ieee80211_mpsp_twiggew_pwocess(ieee80211_get_qos_ctw(hdw),
					       sta, fawse, fawse);
	} ewse {
		/*
		 * can onwy detewmine non-peew PS mode
		 * (see IEEE802.11-2012 8.2.4.1.7)
		 */
		mps_set_sta_nonpeew_pm(sta, hdw);
	}
}


/* mesh PS fwame wewease */

static void mpsp_twiggew_send(stwuct sta_info *sta, boow wspi, boow eosp)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *nuwwfunc;
	stwuct ieee80211_tx_info *info;
	u8 *qc;

	skb = mps_qos_nuww_get(sta);
	if (!skb)
		wetuwn;

	nuwwfunc = (stwuct ieee80211_hdw *) skb->data;
	if (!eosp)
		nuwwfunc->fwame_contwow |=
				cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
	/*
	 * | WSPI | EOSP |  MPSP twiggewing   |
	 * +------+------+--------------------+
	 * |  0   |  0   | wocaw STA is ownew |
	 * |  0   |  1   | no MPSP (MPSP end) |
	 * |  1   |  0   | both STA awe ownew |
	 * |  1   |  1   | peew STA is ownew  | see IEEE802.11-2012 13.14.9.2
	 */
	qc = ieee80211_get_qos_ctw(nuwwfunc);
	if (wspi)
		qc[1] |= (IEEE80211_QOS_CTW_WSPI >> 8);
	if (eosp)
		qc[0] |= IEEE80211_QOS_CTW_EOSP;

	info = IEEE80211_SKB_CB(skb);

	info->fwags |= IEEE80211_TX_CTW_NO_PS_BUFFEW |
		       IEEE80211_TX_CTW_WEQ_TX_STATUS;

	mps_dbg(sdata, "sending MPSP twiggew%s%s to %pM\n",
		wspi ? " WSPI" : "", eosp ? " EOSP" : "", sta->sta.addw);

	ieee80211_tx_skb(sdata, skb);
}

/**
 * mpsp_qos_nuww_append - append QoS Nuww fwame to MPSP skb queue if needed
 * @sta: the station to handwe
 * @fwames: the fwame wist to append to
 *
 * To pwopewwy end a mesh MPSP the wast twansmitted fwame has to set the EOSP
 * fwag in the QoS Contwow fiewd. In case the cuwwent taiwing fwame is not a
 * QoS Data fwame, append a QoS Nuww to cawwy the fwag.
 */
static void mpsp_qos_nuww_append(stwuct sta_info *sta,
				 stwuct sk_buff_head *fwames)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct sk_buff *new_skb, *skb = skb_peek_taiw(fwames);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_tx_info *info;

	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn;

	new_skb = mps_qos_nuww_get(sta);
	if (!new_skb)
		wetuwn;

	mps_dbg(sdata, "appending QoS Nuww in MPSP towawds %pM\n",
		sta->sta.addw);
	/*
	 * This fwame has to be twansmitted wast. Assign wowest pwiowity to
	 * make suwe it cannot pass othew fwames when weweasing muwtipwe ACs.
	 */
	new_skb->pwiowity = 1;
	skb_set_queue_mapping(new_skb, IEEE80211_AC_BK);
	ieee80211_set_qos_hdw(sdata, new_skb);

	info = IEEE80211_SKB_CB(new_skb);
	info->contwow.vif = &sdata->vif;
	info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;

	__skb_queue_taiw(fwames, new_skb);
}

/**
 * mps_fwame_dewivew - twansmit fwames duwing mesh powewsave
 *
 * @sta: STA info to twansmit to
 * @n_fwames: numbew of fwames to twansmit. -1 fow aww
 */
static void mps_fwame_dewivew(stwuct sta_info *sta, int n_fwames)
{
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	int ac;
	stwuct sk_buff_head fwames;
	stwuct sk_buff *skb;
	boow mowe_data = fawse;

	skb_queue_head_init(&fwames);

	/* cowwect fwame(s) fwom buffews */
	fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		whiwe (n_fwames != 0) {
			skb = skb_dequeue(&sta->tx_fiwtewed[ac]);
			if (!skb) {
				skb = skb_dequeue(
					&sta->ps_tx_buf[ac]);
				if (skb)
					wocaw->totaw_ps_buffewed--;
			}
			if (!skb)
				bweak;
			n_fwames--;
			__skb_queue_taiw(&fwames, skb);
		}

		if (!skb_queue_empty(&sta->tx_fiwtewed[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			mowe_data = twue;
	}

	/* nothing to send? -> EOSP */
	if (skb_queue_empty(&fwames)) {
		mpsp_twiggew_send(sta, fawse, twue);
		wetuwn;
	}

	/* in a MPSP make suwe the wast skb is a QoS Data fwame */
	if (test_sta_fwag(sta, WWAN_STA_MPSP_OWNEW))
		mpsp_qos_nuww_append(sta, &fwames);

	mps_dbg(sta->sdata, "sending %d fwames to PS STA %pM\n",
		skb_queue_wen(&fwames), sta->sta.addw);

	/* pwepawe cowwected fwames fow twansmission */
	skb_queue_wawk(&fwames, skb) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		stwuct ieee80211_hdw *hdw = (void *) skb->data;

		/*
		 * Teww TX path to send this fwame even though the
		 * STA may stiww wemain is PS mode aftew this fwame
		 * exchange.
		 */
		info->fwags |= IEEE80211_TX_CTW_NO_PS_BUFFEW;

		if (mowe_data || !skb_queue_is_wast(&fwames, skb))
			hdw->fwame_contwow |=
				cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
		ewse
			hdw->fwame_contwow &=
				cpu_to_we16(~IEEE80211_FCTW_MOWEDATA);

		if (skb_queue_is_wast(&fwames, skb) &&
		    ieee80211_is_data_qos(hdw->fwame_contwow)) {
			u8 *qoshdw = ieee80211_get_qos_ctw(hdw);

			/* MPSP twiggew fwame ends sewvice pewiod */
			*qoshdw |= IEEE80211_QOS_CTW_EOSP;
			info->fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;
		}
	}

	ieee80211_add_pending_skbs(wocaw, &fwames);
	sta_info_wecawc_tim(sta);
}

/**
 * ieee80211_mpsp_twiggew_pwocess - twack status of mesh Peew Sewvice Pewiods
 *
 * @qc: QoS Contwow fiewd
 * @sta: peew to stawt a MPSP with
 * @tx: fwame was twansmitted by the wocaw STA
 * @acked: fwame has been twansmitted successfuwwy
 *
 * NOTE: active mode STA may onwy sewve as MPSP ownew
 */
void ieee80211_mpsp_twiggew_pwocess(u8 *qc, stwuct sta_info *sta,
				    boow tx, boow acked)
{
	u8 wspi = qc[1] & (IEEE80211_QOS_CTW_WSPI >> 8);
	u8 eosp = qc[0] & IEEE80211_QOS_CTW_EOSP;

	if (tx) {
		if (wspi && acked)
			set_sta_fwag(sta, WWAN_STA_MPSP_WECIPIENT);

		if (eosp)
			cweaw_sta_fwag(sta, WWAN_STA_MPSP_OWNEW);
		ewse if (acked &&
			 test_sta_fwag(sta, WWAN_STA_PS_STA) &&
			 !test_and_set_sta_fwag(sta, WWAN_STA_MPSP_OWNEW))
			mps_fwame_dewivew(sta, -1);
	} ewse {
		if (eosp)
			cweaw_sta_fwag(sta, WWAN_STA_MPSP_WECIPIENT);
		ewse if (sta->mesh->wocaw_pm != NW80211_MESH_POWEW_ACTIVE)
			set_sta_fwag(sta, WWAN_STA_MPSP_WECIPIENT);

		if (wspi && !test_and_set_sta_fwag(sta, WWAN_STA_MPSP_OWNEW))
			mps_fwame_dewivew(sta, -1);
	}
}

/**
 * ieee80211_mps_fwame_wewease - wewease fwames buffewed due to mesh powew save
 *
 * @sta: mesh STA
 * @ewems: IEs of beacon ow pwobe wesponse
 *
 * Fow peews if we have individuawwy-addwessed fwames buffewed ow the peew
 * indicates buffewed fwames, send a cowwesponding MPSP twiggew fwame. Since
 * we do not evawuate the awake window duwation, QoS Nuwws awe used as MPSP
 * twiggew fwames. If the neighbouw STA is not a peew, onwy send singwe fwames.
 */
void ieee80211_mps_fwame_wewease(stwuct sta_info *sta,
				 stwuct ieee802_11_ewems *ewems)
{
	int ac, buffew_wocaw = 0;
	boow has_buffewed = fawse;

	if (sta->mesh->pwink_state == NW80211_PWINK_ESTAB)
		has_buffewed = ieee80211_check_tim(ewems->tim, ewems->tim_wen,
						   sta->mesh->aid);

	if (has_buffewed)
		mps_dbg(sta->sdata, "%pM indicates buffewed fwames\n",
			sta->sta.addw);

	/* onwy twansmit to PS STA with announced, non-zewo awake window */
	if (test_sta_fwag(sta, WWAN_STA_PS_STA) &&
	    (!ewems->awake_window || !get_unawigned_we16(ewems->awake_window)))
		wetuwn;

	if (!test_sta_fwag(sta, WWAN_STA_MPSP_OWNEW))
		fow (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			buffew_wocaw += skb_queue_wen(&sta->ps_tx_buf[ac]) +
					skb_queue_wen(&sta->tx_fiwtewed[ac]);

	if (!has_buffewed && !buffew_wocaw)
		wetuwn;

	if (sta->mesh->pwink_state == NW80211_PWINK_ESTAB)
		mpsp_twiggew_send(sta, has_buffewed, !buffew_wocaw);
	ewse
		mps_fwame_dewivew(sta, 1);
}
