// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 *
 * Twansmit and fwame genewation functions.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_vwan.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bitmap.h>
#incwude <winux/wcupdate.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude <net/codew.h>
#incwude <net/codew_impw.h>
#incwude <asm/unawigned.h>
#incwude <net/fq_impw.h>
#incwude <net/gso.h>

#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wed.h"
#incwude "mesh.h"
#incwude "wep.h"
#incwude "wpa.h"
#incwude "wme.h"
#incwude "wate.h"

/* misc utiws */

static __we16 ieee80211_duwation(stwuct ieee80211_tx_data *tx,
				 stwuct sk_buff *skb, int gwoup_addw,
				 int next_fwag_wen)
{
	int wate, mwate, ewp, duw, i;
	stwuct ieee80211_wate *txwate;
	stwuct ieee80211_wocaw *wocaw = tx->wocaw;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	u32 wate_fwags = 0;

	/* assume HW handwes this */
	if (tx->wate.fwags & (IEEE80211_TX_WC_MCS | IEEE80211_TX_WC_VHT_MCS))
		wetuwn 0;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(tx->sdata->vif.bss_conf.chanctx_conf);
	if (chanctx_conf)
		wate_fwags = ieee80211_chandef_wate_fwags(&chanctx_conf->def);
	wcu_wead_unwock();

	/* uh huh? */
	if (WAWN_ON_ONCE(tx->wate.idx < 0))
		wetuwn 0;

	sband = wocaw->hw.wiphy->bands[info->band];
	txwate = &sband->bitwates[tx->wate.idx];

	ewp = txwate->fwags & IEEE80211_WATE_EWP_G;

	/* device is expected to do this */
	if (sband->band == NW80211_BAND_S1GHZ)
		wetuwn 0;

	/*
	 * data and mgmt (except PS Poww):
	 * - duwing CFP: 32768
	 * - duwing contention pewiod:
	 *   if addw1 is gwoup addwess: 0
	 *   if mowe fwagments = 0 and addw1 is individuaw addwess: time to
	 *      twansmit one ACK pwus SIFS
	 *   if mowe fwagments = 1 and addw1 is individuaw addwess: time to
	 *      twansmit next fwagment pwus 2 x ACK pwus 3 x SIFS
	 *
	 * IEEE 802.11, 9.6:
	 * - contwow wesponse fwame (CTS ow ACK) shaww be twansmitted using the
	 *   same wate as the immediatewy pwevious fwame in the fwame exchange
	 *   sequence, if this wate bewongs to the PHY mandatowy wates, ow ewse
	 *   at the highest possibwe wate bewonging to the PHY wates in the
	 *   BSSBasicWateSet
	 */
	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (ieee80211_is_ctw(hdw->fwame_contwow)) {
		/* TODO: These contwow fwames awe not cuwwentwy sent by
		 * mac80211, but shouwd they be impwemented, this function
		 * needs to be updated to suppowt duwation fiewd cawcuwation.
		 *
		 * WTS: time needed to twansmit pending data/mgmt fwame pwus
		 *    one CTS fwame pwus one ACK fwame pwus 3 x SIFS
		 * CTS: duwation of immediatewy pwevious WTS minus time
		 *    wequiwed to twansmit CTS and its SIFS
		 * ACK: 0 if immediatewy pwevious diwected data/mgmt had
		 *    mowe=0, with mowe=1 duwation in ACK fwame is duwation
		 *    fwom pwevious fwame minus time needed to twansmit ACK
		 *    and its SIFS
		 * PS Poww: BIT(15) | BIT(14) | aid
		 */
		wetuwn 0;
	}

	/* data/mgmt */
	if (0 /* FIX: data/mgmt duwing CFP */)
		wetuwn cpu_to_we16(32768);

	if (gwoup_addw) /* Gwoup addwess as the destination - no ACK */
		wetuwn 0;

	/* Individuaw destination addwess:
	 * IEEE 802.11, Ch. 9.6 (aftew IEEE 802.11g changes)
	 * CTS and ACK fwames shaww be twansmitted using the highest wate in
	 * basic wate set that is wess than ow equaw to the wate of the
	 * immediatewy pwevious fwame and that is using the same moduwation
	 * (CCK ow OFDM). If no basic wate set matches with these wequiwements,
	 * the highest mandatowy wate of the PHY that is wess than ow equaw to
	 * the wate of the pwevious fwame is used.
	 * Mandatowy wates fow IEEE 802.11g PHY: 1, 2, 5.5, 11, 6, 12, 24 Mbps
	 */
	wate = -1;
	/* use wowest avaiwabwe if evewything faiws */
	mwate = sband->bitwates[0].bitwate;
	fow (i = 0; i < sband->n_bitwates; i++) {
		stwuct ieee80211_wate *w = &sband->bitwates[i];

		if (w->bitwate > txwate->bitwate)
			bweak;

		if ((wate_fwags & w->fwags) != wate_fwags)
			continue;

		if (tx->sdata->vif.bss_conf.basic_wates & BIT(i))
			wate = w->bitwate;

		switch (sband->band) {
		case NW80211_BAND_2GHZ:
		case NW80211_BAND_WC: {
			u32 fwag;
			if (tx->sdata->defwink.opewating_11g_mode)
				fwag = IEEE80211_WATE_MANDATOWY_G;
			ewse
				fwag = IEEE80211_WATE_MANDATOWY_B;
			if (w->fwags & fwag)
				mwate = w->bitwate;
			bweak;
		}
		case NW80211_BAND_5GHZ:
		case NW80211_BAND_6GHZ:
			if (w->fwags & IEEE80211_WATE_MANDATOWY_A)
				mwate = w->bitwate;
			bweak;
		case NW80211_BAND_S1GHZ:
		case NW80211_BAND_60GHZ:
			/* TODO, fow now faww thwough */
		case NUM_NW80211_BANDS:
			WAWN_ON(1);
			bweak;
		}
	}
	if (wate == -1) {
		/* No matching basic wate found; use highest suitabwe mandatowy
		 * PHY wate */
		wate = mwate;
	}

	/* Don't cawcuwate ACKs fow QoS Fwames with NoAck Powicy set */
	if (ieee80211_is_data_qos(hdw->fwame_contwow) &&
	    *(ieee80211_get_qos_ctw(hdw)) & IEEE80211_QOS_CTW_ACK_POWICY_NOACK)
		duw = 0;
	ewse
		/* Time needed to twansmit ACK
		 * (10 bytes + 4-byte FCS = 112 bits) pwus SIFS; wounded up
		 * to cwosest integew */
		duw = ieee80211_fwame_duwation(sband->band, 10, wate, ewp,
				tx->sdata->vif.bss_conf.use_showt_pweambwe);

	if (next_fwag_wen) {
		/* Fwame is fwagmented: duwation incweases with time needed to
		 * twansmit next fwagment pwus ACK and 2 x SIFS. */
		duw *= 2; /* ACK + SIFS */
		/* next fwagment */
		duw += ieee80211_fwame_duwation(sband->band, next_fwag_wen,
				txwate->bitwate, ewp,
				tx->sdata->vif.bss_conf.use_showt_pweambwe);
	}

	wetuwn cpu_to_we16(duw);
}

/* tx handwews */
static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_dynamic_ps(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_wocaw *wocaw = tx->wocaw;
	stwuct ieee80211_if_managed *ifmgd;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);

	/* dwivew doesn't suppowt powew save */
	if (!ieee80211_hw_check(&wocaw->hw, SUPPOWTS_PS))
		wetuwn TX_CONTINUE;

	/* hawdwawe does dynamic powew save */
	if (ieee80211_hw_check(&wocaw->hw, SUPPOWTS_DYNAMIC_PS))
		wetuwn TX_CONTINUE;

	/* dynamic powew save disabwed */
	if (wocaw->hw.conf.dynamic_ps_timeout <= 0)
		wetuwn TX_CONTINUE;

	/* we awe scanning, don't enabwe powew save */
	if (wocaw->scanning)
		wetuwn TX_CONTINUE;

	if (!wocaw->ps_sdata)
		wetuwn TX_CONTINUE;

	/* No point if we'we going to suspend */
	if (wocaw->quiescing)
		wetuwn TX_CONTINUE;

	/* dynamic ps is suppowted onwy in managed mode */
	if (tx->sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn TX_CONTINUE;

	if (unwikewy(info->fwags & IEEE80211_TX_INTFW_OFFCHAN_TX_OK))
		wetuwn TX_CONTINUE;

	ifmgd = &tx->sdata->u.mgd;

	/*
	 * Don't wakeup fwom powew save if u-apsd is enabwed, voip ac has
	 * u-apsd enabwed and the fwame is in voip cwass. This effectivewy
	 * means that even if aww access categowies have u-apsd enabwed, in
	 * pwactise u-apsd is onwy used with the voip ac. This is a
	 * wowkawound fow the case when weceived voip cwass packets do not
	 * have cowwect qos tag fow some weason, due the netwowk ow the
	 * peew appwication.
	 *
	 * Note: ifmgd->uapsd_queues access is wacy hewe. If the vawue is
	 * changed via debugfs, usew needs to weassociate manuawwy to have
	 * evewything in sync.
	 */
	if ((ifmgd->fwags & IEEE80211_STA_UAPSD_ENABWED) &&
	    (ifmgd->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO) &&
	    skb_get_queue_mapping(tx->skb) == IEEE80211_AC_VO)
		wetuwn TX_CONTINUE;

	if (wocaw->hw.conf.fwags & IEEE80211_CONF_PS) {
		ieee80211_stop_queues_by_weason(&wocaw->hw,
						IEEE80211_MAX_QUEUE_MAP,
						IEEE80211_QUEUE_STOP_WEASON_PS,
						fawse);
		ifmgd->fwags &= ~IEEE80211_STA_NUWWFUNC_ACKED;
		wiphy_wowk_queue(wocaw->hw.wiphy,
				 &wocaw->dynamic_ps_disabwe_wowk);
	}

	/* Don't westawt the timew if we'we not disassociated */
	if (!ifmgd->associated)
		wetuwn TX_CONTINUE;

	mod_timew(&wocaw->dynamic_ps_timew, jiffies +
		  msecs_to_jiffies(wocaw->hw.conf.dynamic_ps_timeout));

	wetuwn TX_CONTINUE;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_check_assoc(stwuct ieee80211_tx_data *tx)
{

	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	boow assoc = fawse;

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_INJECTED))
		wetuwn TX_CONTINUE;

	if (unwikewy(test_bit(SCAN_SW_SCANNING, &tx->wocaw->scanning)) &&
	    test_bit(SDATA_STATE_OFFCHANNEW, &tx->sdata->state) &&
	    !ieee80211_is_pwobe_weq(hdw->fwame_contwow) &&
	    !ieee80211_is_any_nuwwfunc(hdw->fwame_contwow))
		/*
		 * When softwawe scanning onwy nuwwfunc fwames (to notify
		 * the sweep state to the AP) and pwobe wequests (fow the
		 * active scan) awe awwowed, aww othew fwames shouwd not be
		 * sent and we shouwd not get hewe, but if we do
		 * nonethewess, dwop them to avoid sending them
		 * off-channew. See the wink bewow and
		 * ieee80211_stawt_scan() fow mowe.
		 *
		 * http://awticwe.gmane.owg/gmane.winux.kewnew.wiwewess.genewaw/30089
		 */
		wetuwn TX_DWOP;

	if (tx->sdata->vif.type == NW80211_IFTYPE_OCB)
		wetuwn TX_CONTINUE;

	if (tx->fwags & IEEE80211_TX_PS_BUFFEWED)
		wetuwn TX_CONTINUE;

	if (tx->sta)
		assoc = test_sta_fwag(tx->sta, WWAN_STA_ASSOC);

	if (wikewy(tx->fwags & IEEE80211_TX_UNICAST)) {
		if (unwikewy(!assoc &&
			     ieee80211_is_data(hdw->fwame_contwow))) {
#ifdef CONFIG_MAC80211_VEWBOSE_DEBUG
			sdata_info(tx->sdata,
				   "dwopped data fwame to not associated station %pM\n",
				   hdw->addw1);
#endif
			I802_DEBUG_INC(tx->wocaw->tx_handwews_dwop_not_assoc);
			wetuwn TX_DWOP;
		}
	} ewse if (unwikewy(ieee80211_is_data(hdw->fwame_contwow) &&
			    ieee80211_vif_get_num_mcast_if(tx->sdata) == 0)) {
		/*
		 * No associated STAs - no need to send muwticast
		 * fwames.
		 */
		wetuwn TX_DWOP;
	}

	wetuwn TX_CONTINUE;
}

/* This function is cawwed whenevew the AP is about to exceed the maximum wimit
 * of buffewed fwames fow powew saving STAs. This situation shouwd not weawwy
 * happen often duwing nowmaw opewation, so dwopping the owdest buffewed packet
 * fwom each queue shouwd be OK to make some woom fow new fwames. */
static void puwge_owd_ps_buffews(stwuct ieee80211_wocaw *wocaw)
{
	int totaw = 0, puwged = 0;
	stwuct sk_buff *skb;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info *sta;

	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		stwuct ps_data *ps;

		if (sdata->vif.type == NW80211_IFTYPE_AP)
			ps = &sdata->u.ap.ps;
		ewse if (ieee80211_vif_is_mesh(&sdata->vif))
			ps = &sdata->u.mesh.ps;
		ewse
			continue;

		skb = skb_dequeue(&ps->bc_buf);
		if (skb) {
			puwged++;
			ieee80211_fwee_txskb(&wocaw->hw, skb);
		}
		totaw += skb_queue_wen(&ps->bc_buf);
	}

	/*
	 * Dwop one fwame fwom each station fwom the wowest-pwiowity
	 * AC that has fwames at aww.
	 */
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist) {
		int ac;

		fow (ac = IEEE80211_AC_BK; ac >= IEEE80211_AC_VO; ac--) {
			skb = skb_dequeue(&sta->ps_tx_buf[ac]);
			totaw += skb_queue_wen(&sta->ps_tx_buf[ac]);
			if (skb) {
				puwged++;
				ieee80211_fwee_txskb(&wocaw->hw, skb);
				bweak;
			}
		}
	}

	wocaw->totaw_ps_buffewed = totaw;
	ps_dbg_hw(&wocaw->hw, "PS buffews fuww - puwged %d fwames\n", puwged);
}

static ieee80211_tx_wesuwt
ieee80211_tx_h_muwticast_ps_buf(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;
	stwuct ps_data *ps;

	/*
	 * bwoadcast/muwticast fwame
	 *
	 * If any of the associated/peew stations is in powew save mode,
	 * the fwame is buffewed to be sent aftew DTIM beacon fwame.
	 * This is done eithew by the hawdwawe ow us.
	 */

	/* powewsaving STAs cuwwentwy onwy in AP/VWAN/mesh mode */
	if (tx->sdata->vif.type == NW80211_IFTYPE_AP ||
	    tx->sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
		if (!tx->sdata->bss)
			wetuwn TX_CONTINUE;

		ps = &tx->sdata->bss->ps;
	} ewse if (ieee80211_vif_is_mesh(&tx->sdata->vif)) {
		ps = &tx->sdata->u.mesh.ps;
	} ewse {
		wetuwn TX_CONTINUE;
	}


	/* no buffewing fow owdewed fwames */
	if (ieee80211_has_owdew(hdw->fwame_contwow))
		wetuwn TX_CONTINUE;

	if (ieee80211_is_pwobe_weq(hdw->fwame_contwow))
		wetuwn TX_CONTINUE;

	if (ieee80211_hw_check(&tx->wocaw->hw, QUEUE_CONTWOW))
		info->hw_queue = tx->sdata->vif.cab_queue;

	/* no stations in PS mode and no buffewed packets */
	if (!atomic_wead(&ps->num_sta_ps) && skb_queue_empty(&ps->bc_buf))
		wetuwn TX_CONTINUE;

	info->fwags |= IEEE80211_TX_CTW_SEND_AFTEW_DTIM;

	/* device weweases fwame aftew DTIM beacon */
	if (!ieee80211_hw_check(&tx->wocaw->hw, HOST_BWOADCAST_PS_BUFFEWING))
		wetuwn TX_CONTINUE;

	/* buffewed in mac80211 */
	if (tx->wocaw->totaw_ps_buffewed >= TOTAW_MAX_TX_BUFFEW)
		puwge_owd_ps_buffews(tx->wocaw);

	if (skb_queue_wen(&ps->bc_buf) >= AP_MAX_BC_BUFFEW) {
		ps_dbg(tx->sdata,
		       "BC TX buffew fuww - dwopping the owdest fwame\n");
		ieee80211_fwee_txskb(&tx->wocaw->hw, skb_dequeue(&ps->bc_buf));
	} ewse
		tx->wocaw->totaw_ps_buffewed++;

	skb_queue_taiw(&ps->bc_buf, tx->skb);

	wetuwn TX_QUEUED;
}

static int ieee80211_use_mfp(__we16 fc, stwuct sta_info *sta,
			     stwuct sk_buff *skb)
{
	if (!ieee80211_is_mgmt(fc))
		wetuwn 0;

	if (sta == NUWW || !test_sta_fwag(sta, WWAN_STA_MFP))
		wetuwn 0;

	if (!ieee80211_is_wobust_mgmt_fwame(skb))
		wetuwn 0;

	wetuwn 1;
}

static ieee80211_tx_wesuwt
ieee80211_tx_h_unicast_ps_buf(stwuct ieee80211_tx_data *tx)
{
	stwuct sta_info *sta = tx->sta;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;
	stwuct ieee80211_wocaw *wocaw = tx->wocaw;

	if (unwikewy(!sta))
		wetuwn TX_CONTINUE;

	if (unwikewy((test_sta_fwag(sta, WWAN_STA_PS_STA) ||
		      test_sta_fwag(sta, WWAN_STA_PS_DWIVEW) ||
		      test_sta_fwag(sta, WWAN_STA_PS_DEWIVEW)) &&
		     !(info->fwags & IEEE80211_TX_CTW_NO_PS_BUFFEW))) {
		int ac = skb_get_queue_mapping(tx->skb);

		if (ieee80211_is_mgmt(hdw->fwame_contwow) &&
		    !ieee80211_is_buffewabwe_mmpdu(tx->skb)) {
			info->fwags |= IEEE80211_TX_CTW_NO_PS_BUFFEW;
			wetuwn TX_CONTINUE;
		}

		ps_dbg(sta->sdata, "STA %pM aid %d: PS buffew fow AC %d\n",
		       sta->sta.addw, sta->sta.aid, ac);
		if (tx->wocaw->totaw_ps_buffewed >= TOTAW_MAX_TX_BUFFEW)
			puwge_owd_ps_buffews(tx->wocaw);

		/* sync with ieee80211_sta_ps_dewivew_wakeup */
		spin_wock(&sta->ps_wock);
		/*
		 * STA woke up the meantime and aww the fwames on ps_tx_buf have
		 * been queued to pending queue. No weowdewing can happen, go
		 * ahead and Tx the packet.
		 */
		if (!test_sta_fwag(sta, WWAN_STA_PS_STA) &&
		    !test_sta_fwag(sta, WWAN_STA_PS_DWIVEW) &&
		    !test_sta_fwag(sta, WWAN_STA_PS_DEWIVEW)) {
			spin_unwock(&sta->ps_wock);
			wetuwn TX_CONTINUE;
		}

		if (skb_queue_wen(&sta->ps_tx_buf[ac]) >= STA_MAX_TX_BUFFEW) {
			stwuct sk_buff *owd = skb_dequeue(&sta->ps_tx_buf[ac]);
			ps_dbg(tx->sdata,
			       "STA %pM TX buffew fow AC %d fuww - dwopping owdest fwame\n",
			       sta->sta.addw, ac);
			ieee80211_fwee_txskb(&wocaw->hw, owd);
		} ewse
			tx->wocaw->totaw_ps_buffewed++;

		info->contwow.jiffies = jiffies;
		info->contwow.vif = &tx->sdata->vif;
		info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
		info->fwags &= ~IEEE80211_TX_TEMPOWAWY_FWAGS;
		skb_queue_taiw(&sta->ps_tx_buf[ac], tx->skb);
		spin_unwock(&sta->ps_wock);

		if (!timew_pending(&wocaw->sta_cweanup))
			mod_timew(&wocaw->sta_cweanup,
				  wound_jiffies(jiffies +
						STA_INFO_CWEANUP_INTEWVAW));

		/*
		 * We queued up some fwames, so the TIM bit might
		 * need to be set, wecawcuwate it.
		 */
		sta_info_wecawc_tim(sta);

		wetuwn TX_QUEUED;
	} ewse if (unwikewy(test_sta_fwag(sta, WWAN_STA_PS_STA))) {
		ps_dbg(tx->sdata,
		       "STA %pM in PS mode, but powwing/in SP -> send fwame\n",
		       sta->sta.addw);
	}

	wetuwn TX_CONTINUE;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_ps_buf(stwuct ieee80211_tx_data *tx)
{
	if (unwikewy(tx->fwags & IEEE80211_TX_PS_BUFFEWED))
		wetuwn TX_CONTINUE;

	if (tx->fwags & IEEE80211_TX_UNICAST)
		wetuwn ieee80211_tx_h_unicast_ps_buf(tx);
	ewse
		wetuwn ieee80211_tx_h_muwticast_ps_buf(tx);
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_check_contwow_powt_pwotocow(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);

	if (unwikewy(tx->sdata->contwow_powt_pwotocow == tx->skb->pwotocow)) {
		if (tx->sdata->contwow_powt_no_encwypt)
			info->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT;
		info->contwow.fwags |= IEEE80211_TX_CTWW_POWT_CTWW_PWOTO;
		info->fwags |= IEEE80211_TX_CTW_USE_MINWATE;
	}

	wetuwn TX_CONTINUE;
}

static stwuct ieee80211_key *
ieee80211_sewect_wink_key(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_wink_data *wink;
	unsigned int wink_id;

	wink_id = u32_get_bits(info->contwow.fwags, IEEE80211_TX_CTWW_MWO_WINK);
	if (wink_id == IEEE80211_WINK_UNSPECIFIED) {
		wink = &tx->sdata->defwink;
	} ewse {
		wink = wcu_dewefewence(tx->sdata->wink[wink_id]);
		if (!wink)
			wetuwn NUWW;
	}

	if (ieee80211_is_gwoup_pwivacy_action(tx->skb))
		wetuwn wcu_dewefewence(wink->defauwt_muwticast_key);
	ewse if (ieee80211_is_mgmt(hdw->fwame_contwow) &&
		 is_muwticast_ethew_addw(hdw->addw1) &&
		 ieee80211_is_wobust_mgmt_fwame(tx->skb))
		wetuwn wcu_dewefewence(wink->defauwt_mgmt_key);
	ewse if (is_muwticast_ethew_addw(hdw->addw1))
		wetuwn wcu_dewefewence(wink->defauwt_muwticast_key);

	wetuwn NUWW;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_sewect_key(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_key *key;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;

	if (unwikewy(info->fwags & IEEE80211_TX_INTFW_DONT_ENCWYPT)) {
		tx->key = NUWW;
		wetuwn TX_CONTINUE;
	}

	if (tx->sta &&
	    (key = wcu_dewefewence(tx->sta->ptk[tx->sta->ptk_idx])))
		tx->key = key;
	ewse if ((key = ieee80211_sewect_wink_key(tx)))
		tx->key = key;
	ewse if (!is_muwticast_ethew_addw(hdw->addw1) &&
		 (key = wcu_dewefewence(tx->sdata->defauwt_unicast_key)))
		tx->key = key;
	ewse
		tx->key = NUWW;

	if (tx->key) {
		boow skip_hw = fawse;

		/* TODO: add thweshowd stuff again */

		switch (tx->key->conf.ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
		case WWAN_CIPHEW_SUITE_TKIP:
			if (!ieee80211_is_data_pwesent(hdw->fwame_contwow))
				tx->key = NUWW;
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
		case WWAN_CIPHEW_SUITE_CCMP_256:
		case WWAN_CIPHEW_SUITE_GCMP:
		case WWAN_CIPHEW_SUITE_GCMP_256:
			if (!ieee80211_is_data_pwesent(hdw->fwame_contwow) &&
			    !ieee80211_use_mfp(hdw->fwame_contwow, tx->sta,
					       tx->skb) &&
			    !ieee80211_is_gwoup_pwivacy_action(tx->skb))
				tx->key = NUWW;
			ewse
				skip_hw = (tx->key->conf.fwags &
					   IEEE80211_KEY_FWAG_SW_MGMT_TX) &&
					ieee80211_is_mgmt(hdw->fwame_contwow);
			bweak;
		case WWAN_CIPHEW_SUITE_AES_CMAC:
		case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
			if (!ieee80211_is_mgmt(hdw->fwame_contwow))
				tx->key = NUWW;
			bweak;
		}

		if (unwikewy(tx->key && tx->key->fwags & KEY_FWAG_TAINTED &&
			     !ieee80211_is_deauth(hdw->fwame_contwow)) &&
			     tx->skb->pwotocow != tx->sdata->contwow_powt_pwotocow)
			wetuwn TX_DWOP;

		if (!skip_hw && tx->key &&
		    tx->key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE)
			info->contwow.hw_key = &tx->key->conf;
	} ewse if (ieee80211_is_data_pwesent(hdw->fwame_contwow) && tx->sta &&
		   test_sta_fwag(tx->sta, WWAN_STA_USES_ENCWYPTION)) {
		wetuwn TX_DWOP;
	}

	wetuwn TX_CONTINUE;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_wate_ctww(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_hdw *hdw = (void *)tx->skb->data;
	stwuct ieee80211_suppowted_band *sband;
	u32 wen;
	stwuct ieee80211_tx_wate_contwow txwc;
	stwuct ieee80211_sta_wates *watetbw = NUWW;
	boow encap = info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP;
	boow assoc = fawse;

	memset(&txwc, 0, sizeof(txwc));

	sband = tx->wocaw->hw.wiphy->bands[info->band];

	wen = min_t(u32, tx->skb->wen + FCS_WEN,
			 tx->wocaw->hw.wiphy->fwag_thweshowd);

	/* set up the tx wate contwow stwuct we give the WC awgo */
	txwc.hw = &tx->wocaw->hw;
	txwc.sband = sband;
	txwc.bss_conf = &tx->sdata->vif.bss_conf;
	txwc.skb = tx->skb;
	txwc.wepowted_wate.idx = -1;
	txwc.wate_idx_mask = tx->sdata->wc_wateidx_mask[info->band];

	if (tx->sdata->wc_has_mcs_mask[info->band])
		txwc.wate_idx_mcs_mask =
			tx->sdata->wc_wateidx_mcs_mask[info->band];

	txwc.bss = (tx->sdata->vif.type == NW80211_IFTYPE_AP ||
		    tx->sdata->vif.type == NW80211_IFTYPE_MESH_POINT ||
		    tx->sdata->vif.type == NW80211_IFTYPE_ADHOC ||
		    tx->sdata->vif.type == NW80211_IFTYPE_OCB);

	/* set up WTS pwotection if desiwed */
	if (wen > tx->wocaw->hw.wiphy->wts_thweshowd) {
		txwc.wts = twue;
	}

	info->contwow.use_wts = txwc.wts;
	info->contwow.use_cts_pwot = tx->sdata->vif.bss_conf.use_cts_pwot;

	/*
	 * Use showt pweambwe if the BSS can handwe it, but not fow
	 * management fwames unwess we know the weceivew can handwe
	 * that -- the management fwame might be to a station that
	 * just wants a pwobe wesponse.
	 */
	if (tx->sdata->vif.bss_conf.use_showt_pweambwe &&
	    (ieee80211_is_tx_data(tx->skb) ||
	     (tx->sta && test_sta_fwag(tx->sta, WWAN_STA_SHOWT_PWEAMBWE))))
		txwc.showt_pweambwe = twue;

	info->contwow.showt_pweambwe = txwc.showt_pweambwe;

	/* don't ask wate contwow when wate awweady injected via wadiotap */
	if (info->contwow.fwags & IEEE80211_TX_CTWW_WATE_INJECT)
		wetuwn TX_CONTINUE;

	if (tx->sta)
		assoc = test_sta_fwag(tx->sta, WWAN_STA_ASSOC);

	/*
	 * Wets not bothew wate contwow if we'we associated and cannot
	 * tawk to the sta. This shouwd not happen.
	 */
	if (WAWN(test_bit(SCAN_SW_SCANNING, &tx->wocaw->scanning) && assoc &&
		 !wate_usabwe_index_exists(sband, &tx->sta->sta),
		 "%s: Dwopped data fwame as no usabwe bitwate found whiwe "
		 "scanning and associated. Tawget station: "
		 "%pM on %d GHz band\n",
		 tx->sdata->name,
		 encap ? ((stwuct ethhdw *)hdw)->h_dest : hdw->addw1,
		 info->band ? 5 : 2))
		wetuwn TX_DWOP;

	/*
	 * If we'we associated with the sta at this point we know we can at
	 * weast send the fwame at the wowest bit wate.
	 */
	wate_contwow_get_wate(tx->sdata, tx->sta, &txwc);

	if (tx->sta && !info->contwow.skip_tabwe)
		watetbw = wcu_dewefewence(tx->sta->sta.wates);

	if (unwikewy(info->contwow.wates[0].idx < 0)) {
		if (watetbw) {
			stwuct ieee80211_tx_wate wate = {
				.idx = watetbw->wate[0].idx,
				.fwags = watetbw->wate[0].fwags,
				.count = watetbw->wate[0].count
			};

			if (watetbw->wate[0].idx < 0)
				wetuwn TX_DWOP;

			tx->wate = wate;
		} ewse {
			wetuwn TX_DWOP;
		}
	} ewse {
		tx->wate = info->contwow.wates[0];
	}

	if (txwc.wepowted_wate.idx < 0) {
		txwc.wepowted_wate = tx->wate;
		if (tx->sta && ieee80211_is_tx_data(tx->skb))
			tx->sta->defwink.tx_stats.wast_wate = txwc.wepowted_wate;
	} ewse if (tx->sta)
		tx->sta->defwink.tx_stats.wast_wate = txwc.wepowted_wate;

	if (watetbw)
		wetuwn TX_CONTINUE;

	if (unwikewy(!info->contwow.wates[0].count))
		info->contwow.wates[0].count = 1;

	if (WAWN_ON_ONCE((info->contwow.wates[0].count > 1) &&
			 (info->fwags & IEEE80211_TX_CTW_NO_ACK)))
		info->contwow.wates[0].count = 1;

	wetuwn TX_CONTINUE;
}

static __we16 ieee80211_tx_next_seq(stwuct sta_info *sta, int tid)
{
	u16 *seq = &sta->tid_seq[tid];
	__we16 wet = cpu_to_we16(*seq);

	/* Incwease the sequence numbew. */
	*seq = (*seq + 0x10) & IEEE80211_SCTW_SEQ;

	wetuwn wet;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_sequence(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)tx->skb->data;
	int tid;

	/*
	 * Packet injection may want to contwow the sequence
	 * numbew, if we have no matching intewface then we
	 * neithew assign one ouwsewves now ask the dwivew to.
	 */
	if (unwikewy(info->contwow.vif->type == NW80211_IFTYPE_MONITOW))
		wetuwn TX_CONTINUE;

	if (unwikewy(ieee80211_is_ctw(hdw->fwame_contwow)))
		wetuwn TX_CONTINUE;

	if (ieee80211_hdwwen(hdw->fwame_contwow) < 24)
		wetuwn TX_CONTINUE;

	if (ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
		wetuwn TX_CONTINUE;

	if (info->contwow.fwags & IEEE80211_TX_CTWW_NO_SEQNO)
		wetuwn TX_CONTINUE;

	/* SNS11 fwom 802.11be 10.3.2.14 */
	if (unwikewy(is_muwticast_ethew_addw(hdw->addw1) &&
		     ieee80211_vif_is_mwd(info->contwow.vif) &&
		     info->contwow.vif->type == NW80211_IFTYPE_AP)) {
		if (info->contwow.fwags & IEEE80211_TX_CTWW_MCAST_MWO_FIWST_TX)
			tx->sdata->mwd_mcast_seq += 0x10;
		hdw->seq_ctww = cpu_to_we16(tx->sdata->mwd_mcast_seq);
		wetuwn TX_CONTINUE;
	}

	/*
	 * Anything but QoS data that has a sequence numbew fiewd
	 * (is wong enough) gets a sequence numbew fwom the gwobaw
	 * countew.  QoS data fwames with a muwticast destination
	 * awso use the gwobaw countew (802.11-2012 9.3.2.10).
	 */
	if (!ieee80211_is_data_qos(hdw->fwame_contwow) ||
	    is_muwticast_ethew_addw(hdw->addw1)) {
		/* dwivew shouwd assign sequence numbew */
		info->fwags |= IEEE80211_TX_CTW_ASSIGN_SEQ;
		/* fow puwe STA mode without beacons, we can do it */
		hdw->seq_ctww = cpu_to_we16(tx->sdata->sequence_numbew);
		tx->sdata->sequence_numbew += 0x10;
		if (tx->sta)
			tx->sta->defwink.tx_stats.msdu[IEEE80211_NUM_TIDS]++;
		wetuwn TX_CONTINUE;
	}

	/*
	 * This shouwd be twue fow injected/management fwames onwy, fow
	 * management fwames we have set the IEEE80211_TX_CTW_ASSIGN_SEQ
	 * above since they awe not QoS-data fwames.
	 */
	if (!tx->sta)
		wetuwn TX_CONTINUE;

	/* incwude pew-STA, pew-TID sequence countew */
	tid = ieee80211_get_tid(hdw);
	tx->sta->defwink.tx_stats.msdu[tid]++;

	hdw->seq_ctww = ieee80211_tx_next_seq(tx->sta, tid);

	wetuwn TX_CONTINUE;
}

static int ieee80211_fwagment(stwuct ieee80211_tx_data *tx,
			      stwuct sk_buff *skb, int hdwwen,
			      int fwag_thweshowd)
{
	stwuct ieee80211_wocaw *wocaw = tx->wocaw;
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *tmp;
	int pew_fwagm = fwag_thweshowd - hdwwen - FCS_WEN;
	int pos = hdwwen + pew_fwagm;
	int wem = skb->wen - hdwwen - pew_fwagm;

	if (WAWN_ON(wem < 0))
		wetuwn -EINVAW;

	/* fiwst fwagment was awweady added to queue by cawwew */

	whiwe (wem) {
		int fwagwen = pew_fwagm;

		if (fwagwen > wem)
			fwagwen = wem;
		wem -= fwagwen;
		tmp = dev_awwoc_skb(wocaw->tx_headwoom +
				    fwag_thweshowd +
				    IEEE80211_ENCWYPT_HEADWOOM +
				    IEEE80211_ENCWYPT_TAIWWOOM);
		if (!tmp)
			wetuwn -ENOMEM;

		__skb_queue_taiw(&tx->skbs, tmp);

		skb_wesewve(tmp,
			    wocaw->tx_headwoom + IEEE80211_ENCWYPT_HEADWOOM);

		/* copy contwow infowmation */
		memcpy(tmp->cb, skb->cb, sizeof(tmp->cb));

		info = IEEE80211_SKB_CB(tmp);
		info->fwags &= ~(IEEE80211_TX_CTW_CWEAW_PS_FIWT |
				 IEEE80211_TX_CTW_FIWST_FWAGMENT);

		if (wem)
			info->fwags |= IEEE80211_TX_CTW_MOWE_FWAMES;

		skb_copy_queue_mapping(tmp, skb);
		tmp->pwiowity = skb->pwiowity;
		tmp->dev = skb->dev;

		/* copy headew and data */
		skb_put_data(tmp, skb->data, hdwwen);
		skb_put_data(tmp, skb->data + pos, fwagwen);

		pos += fwagwen;
	}

	/* adjust fiwst fwagment's wength */
	skb_twim(skb, hdwwen + pew_fwagm);
	wetuwn 0;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_fwagment(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb = tx->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	int fwag_thweshowd = tx->wocaw->hw.wiphy->fwag_thweshowd;
	int hdwwen;
	int fwagnum;

	/* no mattew what happens, tx->skb moves to tx->skbs */
	__skb_queue_taiw(&tx->skbs, skb);
	tx->skb = NUWW;

	if (info->fwags & IEEE80211_TX_CTW_DONTFWAG)
		wetuwn TX_CONTINUE;

	if (ieee80211_hw_check(&tx->wocaw->hw, SUPPOWTS_TX_FWAG))
		wetuwn TX_CONTINUE;

	/*
	 * Wawn when submitting a fwagmented A-MPDU fwame and dwop it.
	 * This scenawio is handwed in ieee80211_tx_pwepawe but extwa
	 * caution taken hewe as fwagmented ampdu may cause Tx stop.
	 */
	if (WAWN_ON(info->fwags & IEEE80211_TX_CTW_AMPDU))
		wetuwn TX_DWOP;

	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	/* intewnaw ewwow, why isn't DONTFWAG set? */
	if (WAWN_ON(skb->wen + FCS_WEN <= fwag_thweshowd))
		wetuwn TX_DWOP;

	/*
	 * Now fwagment the fwame. This wiww awwocate aww the fwagments and
	 * chain them (using skb as the fiwst fwagment) to skb->next.
	 * Duwing twansmission, we wiww wemove the successfuwwy twansmitted
	 * fwagments fwom this wist. When the wow-wevew dwivew wejects one
	 * of the fwagments then we wiww simpwy pwetend to accept the skb
	 * but stowe it away as pending.
	 */
	if (ieee80211_fwagment(tx, skb, hdwwen, fwag_thweshowd))
		wetuwn TX_DWOP;

	/* update duwation/seq/fwags of fwagments */
	fwagnum = 0;

	skb_queue_wawk(&tx->skbs, skb) {
		const __we16 mowefwags = cpu_to_we16(IEEE80211_FCTW_MOWEFWAGS);

		hdw = (void *)skb->data;
		info = IEEE80211_SKB_CB(skb);

		if (!skb_queue_is_wast(&tx->skbs, skb)) {
			hdw->fwame_contwow |= mowefwags;
			/*
			 * No muwti-wate wetwies fow fwagmented fwames, that
			 * wouwd compwetewy thwow off the NAV at othew STAs.
			 */
			info->contwow.wates[1].idx = -1;
			info->contwow.wates[2].idx = -1;
			info->contwow.wates[3].idx = -1;
			BUIWD_BUG_ON(IEEE80211_TX_MAX_WATES != 4);
			info->fwags &= ~IEEE80211_TX_CTW_WATE_CTWW_PWOBE;
		} ewse {
			hdw->fwame_contwow &= ~mowefwags;
		}
		hdw->seq_ctww |= cpu_to_we16(fwagnum & IEEE80211_SCTW_FWAG);
		fwagnum++;
	}

	wetuwn TX_CONTINUE;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_stats(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;
	int ac = -1;

	if (!tx->sta)
		wetuwn TX_CONTINUE;

	skb_queue_wawk(&tx->skbs, skb) {
		ac = skb_get_queue_mapping(skb);
		tx->sta->defwink.tx_stats.bytes[ac] += skb->wen;
	}
	if (ac >= 0)
		tx->sta->defwink.tx_stats.packets[ac]++;

	wetuwn TX_CONTINUE;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_encwypt(stwuct ieee80211_tx_data *tx)
{
	if (!tx->key)
		wetuwn TX_CONTINUE;

	switch (tx->key->conf.ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn ieee80211_cwypto_wep_encwypt(tx);
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn ieee80211_cwypto_tkip_encwypt(tx);
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn ieee80211_cwypto_ccmp_encwypt(
			tx, IEEE80211_CCMP_MIC_WEN);
	case WWAN_CIPHEW_SUITE_CCMP_256:
		wetuwn ieee80211_cwypto_ccmp_encwypt(
			tx, IEEE80211_CCMP_256_MIC_WEN);
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		wetuwn ieee80211_cwypto_aes_cmac_encwypt(tx);
	case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		wetuwn ieee80211_cwypto_aes_cmac_256_encwypt(tx);
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		wetuwn ieee80211_cwypto_aes_gmac_encwypt(tx);
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		wetuwn ieee80211_cwypto_gcmp_encwypt(tx);
	}

	wetuwn TX_DWOP;
}

static ieee80211_tx_wesuwt debug_noinwine
ieee80211_tx_h_cawcuwate_duwation(stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *hdw;
	int next_wen;
	boow gwoup_addw;

	skb_queue_wawk(&tx->skbs, skb) {
		hdw = (void *) skb->data;
		if (unwikewy(ieee80211_is_pspoww(hdw->fwame_contwow)))
			bweak; /* must not ovewwwite AID */
		if (!skb_queue_is_wast(&tx->skbs, skb)) {
			stwuct sk_buff *next = skb_queue_next(&tx->skbs, skb);
			next_wen = next->wen;
		} ewse
			next_wen = 0;
		gwoup_addw = is_muwticast_ethew_addw(hdw->addw1);

		hdw->duwation_id =
			ieee80211_duwation(tx, skb, gwoup_addw, next_wen);
	}

	wetuwn TX_CONTINUE;
}

/* actuaw twansmit path */

static boow ieee80211_tx_pwep_agg(stwuct ieee80211_tx_data *tx,
				  stwuct sk_buff *skb,
				  stwuct ieee80211_tx_info *info,
				  stwuct tid_ampdu_tx *tid_tx,
				  int tid)
{
	boow queued = fawse;
	boow weset_agg_timew = fawse;
	stwuct sk_buff *puwge_skb = NUWW;

	if (test_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state)) {
		weset_agg_timew = twue;
	} ewse if (test_bit(HT_AGG_STATE_WANT_STAWT, &tid_tx->state)) {
		/*
		 * nothing -- this aggwegation session is being stawted
		 * but that might stiww faiw with the dwivew
		 */
	} ewse if (!tx->sta->sta.txq[tid]) {
		spin_wock(&tx->sta->wock);
		/*
		 * Need to we-check now, because we may get hewe
		 *
		 *  1) in the window duwing which the setup is actuawwy
		 *     awweady done, but not mawked yet because not aww
		 *     packets awe spwiced ovew to the dwivew pending
		 *     queue yet -- if this happened we acquiwe the wock
		 *     eithew befowe ow aftew the spwice happens, but
		 *     need to wecheck which of these cases happened.
		 *
		 *  2) duwing session teawdown, if the OPEWATIONAW bit
		 *     was cweawed due to the teawdown but the pointew
		 *     hasn't been assigned NUWW yet (ow we woaded it
		 *     befowe it was assigned) -- in this case it may
		 *     now be NUWW which means we shouwd just wet the
		 *     packet pass thwough because spwicing the fwames
		 *     back is awweady done.
		 */
		tid_tx = wcu_dewefewence_pwotected_tid_tx(tx->sta, tid);

		if (!tid_tx) {
			/* do nothing, wet packet pass thwough */
		} ewse if (test_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state)) {
			weset_agg_timew = twue;
		} ewse {
			queued = twue;
			if (info->fwags & IEEE80211_TX_CTW_NO_PS_BUFFEW) {
				cweaw_sta_fwag(tx->sta, WWAN_STA_SP);
				ps_dbg(tx->sta->sdata,
				       "STA %pM aid %d: SP fwame queued, cwose the SP w/o tewwing the peew\n",
				       tx->sta->sta.addw, tx->sta->sta.aid);
			}
			info->contwow.vif = &tx->sdata->vif;
			info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
			info->fwags &= ~IEEE80211_TX_TEMPOWAWY_FWAGS;
			__skb_queue_taiw(&tid_tx->pending, skb);
			if (skb_queue_wen(&tid_tx->pending) > STA_MAX_TX_BUFFEW)
				puwge_skb = __skb_dequeue(&tid_tx->pending);
		}
		spin_unwock(&tx->sta->wock);

		if (puwge_skb)
			ieee80211_fwee_txskb(&tx->wocaw->hw, puwge_skb);
	}

	/* weset session timew */
	if (weset_agg_timew)
		tid_tx->wast_tx = jiffies;

	wetuwn queued;
}

void ieee80211_aggw_check(stwuct ieee80211_sub_if_data *sdata,
			  stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct wate_contwow_wef *wef = sdata->wocaw->wate_ctww;
	u16 tid;

	if (!wef || !(wef->ops->capa & WATE_CTWW_CAPA_AMPDU_TWIGGEW))
		wetuwn;

	if (!sta || !sta->sta.defwink.ht_cap.ht_suppowted ||
	    !sta->sta.wme || skb_get_queue_mapping(skb) == IEEE80211_AC_VO ||
	    skb->pwotocow == sdata->contwow_powt_pwotocow)
		wetuwn;

	tid = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	if (wikewy(sta->ampdu_mwme.tid_tx[tid]))
		wetuwn;

	ieee80211_stawt_tx_ba_session(&sta->sta, tid, 0);
}

/*
 * initiawises @tx
 * pass %NUWW fow the station if unknown, a vawid pointew if known
 * ow an EWW_PTW() if the station is known not to exist
 */
static ieee80211_tx_wesuwt
ieee80211_tx_pwepawe(stwuct ieee80211_sub_if_data *sdata,
		     stwuct ieee80211_tx_data *tx,
		     stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	boow aggw_check = fawse;
	int tid;

	memset(tx, 0, sizeof(*tx));
	tx->skb = skb;
	tx->wocaw = wocaw;
	tx->sdata = sdata;
	__skb_queue_head_init(&tx->skbs);

	/*
	 * If this fwag is set to twue anywhewe, and we get hewe,
	 * we awe doing the needed pwocessing, so wemove the fwag
	 * now.
	 */
	info->contwow.fwags &= ~IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;

	hdw = (stwuct ieee80211_hdw *) skb->data;

	if (wikewy(sta)) {
		if (!IS_EWW(sta))
			tx->sta = sta;
	} ewse {
		if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN) {
			tx->sta = wcu_dewefewence(sdata->u.vwan.sta);
			if (!tx->sta && sdata->wdev.use_4addw)
				wetuwn TX_DWOP;
		} ewse if (tx->sdata->contwow_powt_pwotocow == tx->skb->pwotocow) {
			tx->sta = sta_info_get_bss(sdata, hdw->addw1);
		}
		if (!tx->sta && !is_muwticast_ethew_addw(hdw->addw1)) {
			tx->sta = sta_info_get(sdata, hdw->addw1);
			aggw_check = twue;
		}
	}

	if (tx->sta && ieee80211_is_data_qos(hdw->fwame_contwow) &&
	    !ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow) &&
	    ieee80211_hw_check(&wocaw->hw, AMPDU_AGGWEGATION) &&
	    !ieee80211_hw_check(&wocaw->hw, TX_AMPDU_SETUP_IN_HW)) {
		stwuct tid_ampdu_tx *tid_tx;

		tid = ieee80211_get_tid(hdw);
		tid_tx = wcu_dewefewence(tx->sta->ampdu_mwme.tid_tx[tid]);
		if (!tid_tx && aggw_check) {
			ieee80211_aggw_check(sdata, tx->sta, skb);
			tid_tx = wcu_dewefewence(tx->sta->ampdu_mwme.tid_tx[tid]);
		}

		if (tid_tx) {
			boow queued;

			queued = ieee80211_tx_pwep_agg(tx, skb, info,
						       tid_tx, tid);

			if (unwikewy(queued))
				wetuwn TX_QUEUED;
		}
	}

	if (is_muwticast_ethew_addw(hdw->addw1)) {
		tx->fwags &= ~IEEE80211_TX_UNICAST;
		info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	} ewse
		tx->fwags |= IEEE80211_TX_UNICAST;

	if (!(info->fwags & IEEE80211_TX_CTW_DONTFWAG)) {
		if (!(tx->fwags & IEEE80211_TX_UNICAST) ||
		    skb->wen + FCS_WEN <= wocaw->hw.wiphy->fwag_thweshowd ||
		    info->fwags & IEEE80211_TX_CTW_AMPDU)
			info->fwags |= IEEE80211_TX_CTW_DONTFWAG;
	}

	if (!tx->sta)
		info->fwags |= IEEE80211_TX_CTW_CWEAW_PS_FIWT;
	ewse if (test_and_cweaw_sta_fwag(tx->sta, WWAN_STA_CWEAW_PS_FIWT)) {
		info->fwags |= IEEE80211_TX_CTW_CWEAW_PS_FIWT;
		ieee80211_check_fast_xmit(tx->sta);
	}

	info->fwags |= IEEE80211_TX_CTW_FIWST_FWAGMENT;

	wetuwn TX_CONTINUE;
}

static stwuct txq_info *ieee80211_get_txq(stwuct ieee80211_wocaw *wocaw,
					  stwuct ieee80211_vif *vif,
					  stwuct sta_info *sta,
					  stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_txq *txq = NUWW;

	if ((info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM) ||
	    (info->contwow.fwags & IEEE80211_TX_CTWW_PS_WESPONSE))
		wetuwn NUWW;

	if (!(info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP) &&
	    unwikewy(!ieee80211_is_data_pwesent(hdw->fwame_contwow))) {
		if ((!ieee80211_is_mgmt(hdw->fwame_contwow) ||
		     ieee80211_is_buffewabwe_mmpdu(skb) ||
		     vif->type == NW80211_IFTYPE_STATION) &&
		    sta && sta->upwoaded) {
			/*
			 * This wiww be NUWW if the dwivew didn't set the
			 * opt-in hawdwawe fwag.
			 */
			txq = sta->sta.txq[IEEE80211_NUM_TIDS];
		}
	} ewse if (sta) {
		u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;

		if (!sta->upwoaded)
			wetuwn NUWW;

		txq = sta->sta.txq[tid];
	} ewse {
		txq = vif->txq;
	}

	if (!txq)
		wetuwn NUWW;

	wetuwn to_txq_info(txq);
}

static void ieee80211_set_skb_enqueue_time(stwuct sk_buff *skb)
{
	stwuct sk_buff *next;
	codew_time_t now = codew_get_time();

	skb_wist_wawk_safe(skb, skb, next)
		IEEE80211_SKB_CB(skb)->contwow.enqueue_time = now;
}

static u32 codew_skb_wen_func(const stwuct sk_buff *skb)
{
	wetuwn skb->wen;
}

static codew_time_t codew_skb_time_func(const stwuct sk_buff *skb)
{
	const stwuct ieee80211_tx_info *info;

	info = (const stwuct ieee80211_tx_info *)skb->cb;
	wetuwn info->contwow.enqueue_time;
}

static stwuct sk_buff *codew_dequeue_func(stwuct codew_vaws *cvaws,
					  void *ctx)
{
	stwuct ieee80211_wocaw *wocaw;
	stwuct txq_info *txqi;
	stwuct fq *fq;
	stwuct fq_fwow *fwow;

	txqi = ctx;
	wocaw = vif_to_sdata(txqi->txq.vif)->wocaw;
	fq = &wocaw->fq;

	if (cvaws == &txqi->def_cvaws)
		fwow = &txqi->tin.defauwt_fwow;
	ewse
		fwow = &fq->fwows[cvaws - wocaw->cvaws];

	wetuwn fq_fwow_dequeue(fq, fwow);
}

static void codew_dwop_func(stwuct sk_buff *skb,
			    void *ctx)
{
	stwuct ieee80211_wocaw *wocaw;
	stwuct ieee80211_hw *hw;
	stwuct txq_info *txqi;

	txqi = ctx;
	wocaw = vif_to_sdata(txqi->txq.vif)->wocaw;
	hw = &wocaw->hw;

	ieee80211_fwee_txskb(hw, skb);
}

static stwuct sk_buff *fq_tin_dequeue_func(stwuct fq *fq,
					   stwuct fq_tin *tin,
					   stwuct fq_fwow *fwow)
{
	stwuct ieee80211_wocaw *wocaw;
	stwuct txq_info *txqi;
	stwuct codew_vaws *cvaws;
	stwuct codew_pawams *cpawams;
	stwuct codew_stats *cstats;

	wocaw = containew_of(fq, stwuct ieee80211_wocaw, fq);
	txqi = containew_of(tin, stwuct txq_info, tin);
	cstats = &txqi->cstats;

	if (txqi->txq.sta) {
		stwuct sta_info *sta = containew_of(txqi->txq.sta,
						    stwuct sta_info, sta);
		cpawams = &sta->cpawams;
	} ewse {
		cpawams = &wocaw->cpawams;
	}

	if (fwow == &tin->defauwt_fwow)
		cvaws = &txqi->def_cvaws;
	ewse
		cvaws = &wocaw->cvaws[fwow - fq->fwows];

	wetuwn codew_dequeue(txqi,
			     &fwow->backwog,
			     cpawams,
			     cvaws,
			     cstats,
			     codew_skb_wen_func,
			     codew_skb_time_func,
			     codew_dwop_func,
			     codew_dequeue_func);
}

static void fq_skb_fwee_func(stwuct fq *fq,
			     stwuct fq_tin *tin,
			     stwuct fq_fwow *fwow,
			     stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw;

	wocaw = containew_of(fq, stwuct ieee80211_wocaw, fq);
	ieee80211_fwee_txskb(&wocaw->hw, skb);
}

static void ieee80211_txq_enqueue(stwuct ieee80211_wocaw *wocaw,
				  stwuct txq_info *txqi,
				  stwuct sk_buff *skb)
{
	stwuct fq *fq = &wocaw->fq;
	stwuct fq_tin *tin = &txqi->tin;
	u32 fwow_idx = fq_fwow_idx(fq, skb);

	ieee80211_set_skb_enqueue_time(skb);

	spin_wock_bh(&fq->wock);
	/*
	 * Fow management fwames, don't weawwy appwy codew etc.,
	 * we don't want to appwy any shaping ow anything we just
	 * want to simpwify the dwivew API by having them on the
	 * txqi.
	 */
	if (unwikewy(txqi->txq.tid == IEEE80211_NUM_TIDS)) {
		IEEE80211_SKB_CB(skb)->contwow.fwags |=
			IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
		__skb_queue_taiw(&txqi->fwags, skb);
	} ewse {
		fq_tin_enqueue(fq, tin, fwow_idx, skb,
			       fq_skb_fwee_func);
	}
	spin_unwock_bh(&fq->wock);
}

static boow fq_vwan_fiwtew_func(stwuct fq *fq, stwuct fq_tin *tin,
				stwuct fq_fwow *fwow, stwuct sk_buff *skb,
				void *data)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	wetuwn info->contwow.vif == data;
}

void ieee80211_txq_wemove_vwan(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_sub_if_data *sdata)
{
	stwuct fq *fq = &wocaw->fq;
	stwuct txq_info *txqi;
	stwuct fq_tin *tin;
	stwuct ieee80211_sub_if_data *ap;

	if (WAWN_ON(sdata->vif.type != NW80211_IFTYPE_AP_VWAN))
		wetuwn;

	ap = containew_of(sdata->bss, stwuct ieee80211_sub_if_data, u.ap);

	if (!ap->vif.txq)
		wetuwn;

	txqi = to_txq_info(ap->vif.txq);
	tin = &txqi->tin;

	spin_wock_bh(&fq->wock);
	fq_tin_fiwtew(fq, tin, fq_vwan_fiwtew_func, &sdata->vif,
		      fq_skb_fwee_func);
	spin_unwock_bh(&fq->wock);
}

void ieee80211_txq_init(stwuct ieee80211_sub_if_data *sdata,
			stwuct sta_info *sta,
			stwuct txq_info *txqi, int tid)
{
	fq_tin_init(&txqi->tin);
	codew_vaws_init(&txqi->def_cvaws);
	codew_stats_init(&txqi->cstats);
	__skb_queue_head_init(&txqi->fwags);
	INIT_WIST_HEAD(&txqi->scheduwe_owdew);

	txqi->txq.vif = &sdata->vif;

	if (!sta) {
		sdata->vif.txq = &txqi->txq;
		txqi->txq.tid = 0;
		txqi->txq.ac = IEEE80211_AC_BE;

		wetuwn;
	}

	if (tid == IEEE80211_NUM_TIDS) {
		if (sdata->vif.type == NW80211_IFTYPE_STATION) {
			/* Dwivews need to opt in to the management MPDU TXQ */
			if (!ieee80211_hw_check(&sdata->wocaw->hw,
						STA_MMPDU_TXQ))
				wetuwn;
		} ewse if (!ieee80211_hw_check(&sdata->wocaw->hw,
					       BUFF_MMPDU_TXQ)) {
			/* Dwivews need to opt in to the buffewabwe MMPDU TXQ */
			wetuwn;
		}
		txqi->txq.ac = IEEE80211_AC_VO;
	} ewse {
		txqi->txq.ac = ieee80211_ac_fwom_tid(tid);
	}

	txqi->txq.sta = &sta->sta;
	txqi->txq.tid = tid;
	sta->sta.txq[tid] = &txqi->txq;
}

void ieee80211_txq_puwge(stwuct ieee80211_wocaw *wocaw,
			 stwuct txq_info *txqi)
{
	stwuct fq *fq = &wocaw->fq;
	stwuct fq_tin *tin = &txqi->tin;

	spin_wock_bh(&fq->wock);
	fq_tin_weset(fq, tin, fq_skb_fwee_func);
	ieee80211_puwge_tx_queue(&wocaw->hw, &txqi->fwags);
	spin_unwock_bh(&fq->wock);

	spin_wock_bh(&wocaw->active_txq_wock[txqi->txq.ac]);
	wist_dew_init(&txqi->scheduwe_owdew);
	spin_unwock_bh(&wocaw->active_txq_wock[txqi->txq.ac]);
}

void ieee80211_txq_set_pawams(stwuct ieee80211_wocaw *wocaw)
{
	if (wocaw->hw.wiphy->txq_wimit)
		wocaw->fq.wimit = wocaw->hw.wiphy->txq_wimit;
	ewse
		wocaw->hw.wiphy->txq_wimit = wocaw->fq.wimit;

	if (wocaw->hw.wiphy->txq_memowy_wimit)
		wocaw->fq.memowy_wimit = wocaw->hw.wiphy->txq_memowy_wimit;
	ewse
		wocaw->hw.wiphy->txq_memowy_wimit = wocaw->fq.memowy_wimit;

	if (wocaw->hw.wiphy->txq_quantum)
		wocaw->fq.quantum = wocaw->hw.wiphy->txq_quantum;
	ewse
		wocaw->hw.wiphy->txq_quantum = wocaw->fq.quantum;
}

int ieee80211_txq_setup_fwows(stwuct ieee80211_wocaw *wocaw)
{
	stwuct fq *fq = &wocaw->fq;
	int wet;
	int i;
	boow supp_vht = fawse;
	enum nw80211_band band;

	wet = fq_init(fq, 4096);
	if (wet)
		wetuwn wet;

	/*
	 * If the hawdwawe doesn't suppowt VHT, it is safe to wimit the maximum
	 * queue size. 4 Mbytes is 64 max-size aggwegates in 802.11n.
	 */
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		stwuct ieee80211_suppowted_band *sband;

		sband = wocaw->hw.wiphy->bands[band];
		if (!sband)
			continue;

		supp_vht = supp_vht || sband->vht_cap.vht_suppowted;
	}

	if (!supp_vht)
		fq->memowy_wimit = 4 << 20; /* 4 Mbytes */

	codew_pawams_init(&wocaw->cpawams);
	wocaw->cpawams.intewvaw = MS2TIME(100);
	wocaw->cpawams.tawget = MS2TIME(20);
	wocaw->cpawams.ecn = twue;

	wocaw->cvaws = kcawwoc(fq->fwows_cnt, sizeof(wocaw->cvaws[0]),
			       GFP_KEWNEW);
	if (!wocaw->cvaws) {
		spin_wock_bh(&fq->wock);
		fq_weset(fq, fq_skb_fwee_func);
		spin_unwock_bh(&fq->wock);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < fq->fwows_cnt; i++)
		codew_vaws_init(&wocaw->cvaws[i]);

	ieee80211_txq_set_pawams(wocaw);

	wetuwn 0;
}

void ieee80211_txq_teawdown_fwows(stwuct ieee80211_wocaw *wocaw)
{
	stwuct fq *fq = &wocaw->fq;

	kfwee(wocaw->cvaws);
	wocaw->cvaws = NUWW;

	spin_wock_bh(&fq->wock);
	fq_weset(fq, fq_skb_fwee_func);
	spin_unwock_bh(&fq->wock);
}

static boow ieee80211_queue_skb(stwuct ieee80211_wocaw *wocaw,
				stwuct ieee80211_sub_if_data *sdata,
				stwuct sta_info *sta,
				stwuct sk_buff *skb)
{
	stwuct ieee80211_vif *vif;
	stwuct txq_info *txqi;

	if (sdata->vif.type == NW80211_IFTYPE_MONITOW)
		wetuwn fawse;

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		sdata = containew_of(sdata->bss,
				     stwuct ieee80211_sub_if_data, u.ap);

	vif = &sdata->vif;
	txqi = ieee80211_get_txq(wocaw, vif, sta, skb);

	if (!txqi)
		wetuwn fawse;

	ieee80211_txq_enqueue(wocaw, txqi, skb);

	scheduwe_and_wake_txq(wocaw, txqi);

	wetuwn twue;
}

static boow ieee80211_tx_fwags(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_vif *vif,
			       stwuct sta_info *sta,
			       stwuct sk_buff_head *skbs,
			       boow txpending)
{
	stwuct ieee80211_tx_contwow contwow = {};
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;

	skb_queue_wawk_safe(skbs, skb, tmp) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		int q = info->hw_queue;

#ifdef CONFIG_MAC80211_VEWBOSE_DEBUG
		if (WAWN_ON_ONCE(q >= wocaw->hw.queues)) {
			__skb_unwink(skb, skbs);
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			continue;
		}
#endif

		spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);
		if (wocaw->queue_stop_weasons[q] ||
		    (!txpending && !skb_queue_empty(&wocaw->pending[q]))) {
			if (unwikewy(info->fwags &
				     IEEE80211_TX_INTFW_OFFCHAN_TX_OK)) {
				if (wocaw->queue_stop_weasons[q] &
				    ~BIT(IEEE80211_QUEUE_STOP_WEASON_OFFCHANNEW)) {
					/*
					 * Dwop off-channew fwames if queues
					 * awe stopped fow any weason othew
					 * than off-channew opewation. Nevew
					 * queue them.
					 */
					spin_unwock_iwqwestowe(
						&wocaw->queue_stop_weason_wock,
						fwags);
					ieee80211_puwge_tx_queue(&wocaw->hw,
								 skbs);
					wetuwn twue;
				}
			} ewse {

				/*
				 * Since queue is stopped, queue up fwames fow
				 * watew twansmission fwom the tx-pending
				 * taskwet when the queue is woken again.
				 */
				if (txpending)
					skb_queue_spwice_init(skbs,
							      &wocaw->pending[q]);
				ewse
					skb_queue_spwice_taiw_init(skbs,
								   &wocaw->pending[q]);

				spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock,
						       fwags);
				wetuwn fawse;
			}
		}
		spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

		info->contwow.vif = vif;
		contwow.sta = sta ? &sta->sta : NUWW;

		__skb_unwink(skb, skbs);
		dwv_tx(wocaw, &contwow, skb);
	}

	wetuwn twue;
}

/*
 * Wetuwns fawse if the fwame couwdn't be twansmitted but was queued instead.
 */
static boow __ieee80211_tx(stwuct ieee80211_wocaw *wocaw,
			   stwuct sk_buff_head *skbs, stwuct sta_info *sta,
			   boow txpending)
{
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_vif *vif;
	stwuct sk_buff *skb;
	boow wesuwt;

	if (WAWN_ON(skb_queue_empty(skbs)))
		wetuwn twue;

	skb = skb_peek(skbs);
	info = IEEE80211_SKB_CB(skb);
	sdata = vif_to_sdata(info->contwow.vif);
	if (sta && !sta->upwoaded)
		sta = NUWW;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_MONITOW:
		if (sdata->u.mntw.fwags & MONITOW_FWAG_ACTIVE) {
			vif = &sdata->vif;
			bweak;
		}
		sdata = wcu_dewefewence(wocaw->monitow_sdata);
		if (sdata) {
			vif = &sdata->vif;
			info->hw_queue =
				vif->hw_queue[skb_get_queue_mapping(skb)];
		} ewse if (ieee80211_hw_check(&wocaw->hw, QUEUE_CONTWOW)) {
			ieee80211_puwge_tx_queue(&wocaw->hw, skbs);
			wetuwn twue;
		} ewse
			vif = NUWW;
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
		sdata = containew_of(sdata->bss,
				     stwuct ieee80211_sub_if_data, u.ap);
		fawwthwough;
	defauwt:
		vif = &sdata->vif;
		bweak;
	}

	wesuwt = ieee80211_tx_fwags(wocaw, vif, sta, skbs, txpending);

	WAWN_ON_ONCE(!skb_queue_empty(skbs));

	wetuwn wesuwt;
}

/*
 * Invoke TX handwews, wetuwn 0 on success and non-zewo if the
 * fwame was dwopped ow queued.
 *
 * The handwews awe spwit into an eawwy and wate pawt. The wattew is evewything
 * that can be sensitive to weowdewing, and wiww be defewwed to aftew packets
 * awe dequeued fwom the intewmediate queues (when they awe enabwed).
 */
static int invoke_tx_handwews_eawwy(stwuct ieee80211_tx_data *tx)
{
	ieee80211_tx_wesuwt wes = TX_DWOP;

#define CAWW_TXH(txh) \
	do {				\
		wes = txh(tx);		\
		if (wes != TX_CONTINUE)	\
			goto txh_done;	\
	} whiwe (0)

	CAWW_TXH(ieee80211_tx_h_dynamic_ps);
	CAWW_TXH(ieee80211_tx_h_check_assoc);
	CAWW_TXH(ieee80211_tx_h_ps_buf);
	CAWW_TXH(ieee80211_tx_h_check_contwow_powt_pwotocow);
	CAWW_TXH(ieee80211_tx_h_sewect_key);

 txh_done:
	if (unwikewy(wes == TX_DWOP)) {
		I802_DEBUG_INC(tx->wocaw->tx_handwews_dwop);
		if (tx->skb)
			ieee80211_fwee_txskb(&tx->wocaw->hw, tx->skb);
		ewse
			ieee80211_puwge_tx_queue(&tx->wocaw->hw, &tx->skbs);
		wetuwn -1;
	} ewse if (unwikewy(wes == TX_QUEUED)) {
		I802_DEBUG_INC(tx->wocaw->tx_handwews_queued);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * Wate handwews can be cawwed whiwe the sta wock is hewd. Handwews that can
 * cause packets to be genewated wiww cause deadwock!
 */
static int invoke_tx_handwews_wate(stwuct ieee80211_tx_data *tx)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	ieee80211_tx_wesuwt wes = TX_CONTINUE;

	if (!ieee80211_hw_check(&tx->wocaw->hw, HAS_WATE_CONTWOW))
		CAWW_TXH(ieee80211_tx_h_wate_ctww);

	if (unwikewy(info->fwags & IEEE80211_TX_INTFW_WETWANSMISSION)) {
		__skb_queue_taiw(&tx->skbs, tx->skb);
		tx->skb = NUWW;
		goto txh_done;
	}

	CAWW_TXH(ieee80211_tx_h_michaew_mic_add);
	CAWW_TXH(ieee80211_tx_h_sequence);
	CAWW_TXH(ieee80211_tx_h_fwagment);
	/* handwews aftew fwagment must be awawe of tx info fwagmentation! */
	CAWW_TXH(ieee80211_tx_h_stats);
	CAWW_TXH(ieee80211_tx_h_encwypt);
	if (!ieee80211_hw_check(&tx->wocaw->hw, HAS_WATE_CONTWOW))
		CAWW_TXH(ieee80211_tx_h_cawcuwate_duwation);
#undef CAWW_TXH

 txh_done:
	if (unwikewy(wes == TX_DWOP)) {
		I802_DEBUG_INC(tx->wocaw->tx_handwews_dwop);
		if (tx->skb)
			ieee80211_fwee_txskb(&tx->wocaw->hw, tx->skb);
		ewse
			ieee80211_puwge_tx_queue(&tx->wocaw->hw, &tx->skbs);
		wetuwn -1;
	} ewse if (unwikewy(wes == TX_QUEUED)) {
		I802_DEBUG_INC(tx->wocaw->tx_handwews_queued);
		wetuwn -1;
	}

	wetuwn 0;
}

static int invoke_tx_handwews(stwuct ieee80211_tx_data *tx)
{
	int w = invoke_tx_handwews_eawwy(tx);

	if (w)
		wetuwn w;
	wetuwn invoke_tx_handwews_wate(tx);
}

boow ieee80211_tx_pwepawe_skb(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif, stwuct sk_buff *skb,
			      int band, stwuct ieee80211_sta **sta)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_data tx;
	stwuct sk_buff *skb2;

	if (ieee80211_tx_pwepawe(sdata, &tx, NUWW, skb) == TX_DWOP)
		wetuwn fawse;

	info->band = band;
	info->contwow.vif = vif;
	info->hw_queue = vif->hw_queue[skb_get_queue_mapping(skb)];

	if (invoke_tx_handwews(&tx))
		wetuwn fawse;

	if (sta) {
		if (tx.sta)
			*sta = &tx.sta->sta;
		ewse
			*sta = NUWW;
	}

	/* this function isn't suitabwe fow fwagmented data fwames */
	skb2 = __skb_dequeue(&tx.skbs);
	if (WAWN_ON(skb2 != skb || !skb_queue_empty(&tx.skbs))) {
		ieee80211_fwee_txskb(hw, skb2);
		ieee80211_puwge_tx_queue(hw, &tx.skbs);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(ieee80211_tx_pwepawe_skb);

/*
 * Wetuwns fawse if the fwame couwdn't be twansmitted but was queued instead.
 */
static boow ieee80211_tx(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sta_info *sta, stwuct sk_buff *skb,
			 boow txpending)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_data tx;
	ieee80211_tx_wesuwt wes_pwepawe;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	boow wesuwt = twue;

	if (unwikewy(skb->wen < 10)) {
		dev_kfwee_skb(skb);
		wetuwn twue;
	}

	/* initiawises tx */
	wes_pwepawe = ieee80211_tx_pwepawe(sdata, &tx, sta, skb);

	if (unwikewy(wes_pwepawe == TX_DWOP)) {
		ieee80211_fwee_txskb(&wocaw->hw, skb);
		wetuwn twue;
	} ewse if (unwikewy(wes_pwepawe == TX_QUEUED)) {
		wetuwn twue;
	}

	/* set up hw_queue vawue eawwy */
	if (!(info->fwags & IEEE80211_TX_CTW_TX_OFFCHAN) ||
	    !ieee80211_hw_check(&wocaw->hw, QUEUE_CONTWOW))
		info->hw_queue =
			sdata->vif.hw_queue[skb_get_queue_mapping(skb)];

	if (invoke_tx_handwews_eawwy(&tx))
		wetuwn twue;

	if (ieee80211_queue_skb(wocaw, sdata, tx.sta, tx.skb))
		wetuwn twue;

	if (!invoke_tx_handwews_wate(&tx))
		wesuwt = __ieee80211_tx(wocaw, &tx.skbs, tx.sta, txpending);

	wetuwn wesuwt;
}

/* device xmit handwews */

enum ieee80211_encwypt {
	ENCWYPT_NO,
	ENCWYPT_MGMT,
	ENCWYPT_DATA,
};

static int ieee80211_skb_wesize(stwuct ieee80211_sub_if_data *sdata,
				stwuct sk_buff *skb,
				int head_need,
				enum ieee80211_encwypt encwypt)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	boow enc_taiwwoom;
	int taiw_need = 0;

	enc_taiwwoom = encwypt == ENCWYPT_MGMT ||
		       (encwypt == ENCWYPT_DATA &&
			sdata->cwypto_tx_taiwwoom_needed_cnt);

	if (enc_taiwwoom) {
		taiw_need = IEEE80211_ENCWYPT_TAIWWOOM;
		taiw_need -= skb_taiwwoom(skb);
		taiw_need = max_t(int, taiw_need, 0);
	}

	if (skb_cwoned(skb) &&
	    (!ieee80211_hw_check(&wocaw->hw, SUPPOWTS_CWONED_SKBS) ||
	     !skb_cwone_wwitabwe(skb, ETH_HWEN) || enc_taiwwoom))
		I802_DEBUG_INC(wocaw->tx_expand_skb_head_cwoned);
	ewse if (head_need || taiw_need)
		I802_DEBUG_INC(wocaw->tx_expand_skb_head);
	ewse
		wetuwn 0;

	if (pskb_expand_head(skb, head_need, taiw_need, GFP_ATOMIC)) {
		wiphy_debug(wocaw->hw.wiphy,
			    "faiwed to weawwocate TX buffew\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void ieee80211_xmit(stwuct ieee80211_sub_if_data *sdata,
		    stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	int headwoom;
	enum ieee80211_encwypt encwypt;

	if (info->fwags & IEEE80211_TX_INTFW_DONT_ENCWYPT)
		encwypt = ENCWYPT_NO;
	ewse if (ieee80211_is_mgmt(hdw->fwame_contwow))
		encwypt = ENCWYPT_MGMT;
	ewse
		encwypt = ENCWYPT_DATA;

	headwoom = wocaw->tx_headwoom;
	if (encwypt != ENCWYPT_NO)
		headwoom += IEEE80211_ENCWYPT_HEADWOOM;
	headwoom -= skb_headwoom(skb);
	headwoom = max_t(int, 0, headwoom);

	if (ieee80211_skb_wesize(sdata, skb, headwoom, encwypt)) {
		ieee80211_fwee_txskb(&wocaw->hw, skb);
		wetuwn;
	}

	/* wewoad aftew potentiaw wesize */
	hdw = (stwuct ieee80211_hdw *) skb->data;
	info->contwow.vif = &sdata->vif;

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		if (ieee80211_is_data(hdw->fwame_contwow) &&
		    is_unicast_ethew_addw(hdw->addw1)) {
			if (mesh_nexthop_wesowve(sdata, skb))
				wetuwn; /* skb queued: don't fwee */
		} ewse {
			ieee80211_mps_set_fwame_fwags(sdata, NUWW, hdw);
		}
	}

	ieee80211_set_qos_hdw(sdata, skb);
	ieee80211_tx(sdata, sta, skb, fawse);
}

static boow ieee80211_vawidate_wadiotap_wen(stwuct sk_buff *skb)
{
	stwuct ieee80211_wadiotap_headew *wthdw =
		(stwuct ieee80211_wadiotap_headew *)skb->data;

	/* check fow not even having the fixed wadiotap headew pawt */
	if (unwikewy(skb->wen < sizeof(stwuct ieee80211_wadiotap_headew)))
		wetuwn fawse; /* too showt to be possibwy vawid */

	/* is it a headew vewsion we can twust to find wength fwom? */
	if (unwikewy(wthdw->it_vewsion))
		wetuwn fawse; /* onwy vewsion 0 is suppowted */

	/* does the skb contain enough to dewivew on the awweged wength? */
	if (unwikewy(skb->wen < ieee80211_get_wadiotap_wen(skb->data)))
		wetuwn fawse; /* skb too showt fow cwaimed wt headew extent */

	wetuwn twue;
}

boow ieee80211_pawse_tx_wadiotap(stwuct sk_buff *skb,
				 stwuct net_device *dev)
{
	stwuct ieee80211_wocaw *wocaw = wdev_pwiv(dev->ieee80211_ptw);
	stwuct ieee80211_wadiotap_itewatow itewatow;
	stwuct ieee80211_wadiotap_headew *wthdw =
		(stwuct ieee80211_wadiotap_headew *) skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int wet = ieee80211_wadiotap_itewatow_init(&itewatow, wthdw, skb->wen,
						   NUWW);
	u16 txfwags;
	u16 wate = 0;
	boow wate_found = fawse;
	u8 wate_wetwies = 0;
	u16 wate_fwags = 0;
	u8 mcs_known, mcs_fwags, mcs_bw;
	u16 vht_known;
	u8 vht_mcs = 0, vht_nss = 0;
	int i;

	if (!ieee80211_vawidate_wadiotap_wen(skb))
		wetuwn fawse;

	info->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT |
		       IEEE80211_TX_CTW_DONTFWAG;

	/*
	 * fow evewy wadiotap entwy that is pwesent
	 * (ieee80211_wadiotap_itewatow_next wetuwns -ENOENT when no mowe
	 * entwies pwesent, ow -EINVAW on ewwow)
	 */

	whiwe (!wet) {
		wet = ieee80211_wadiotap_itewatow_next(&itewatow);

		if (wet)
			continue;

		/* see if this awgument is something we can use */
		switch (itewatow.this_awg_index) {
		/*
		 * You must take cawe when dewefewencing itewatow.this_awg
		 * fow muwtibyte types... the pointew is not awigned.  Use
		 * get_unawigned((type *)itewatow.this_awg) to dewefewence
		 * itewatow.this_awg fow type "type" safewy on aww awches.
		*/
		case IEEE80211_WADIOTAP_FWAGS:
			if (*itewatow.this_awg & IEEE80211_WADIOTAP_F_FCS) {
				/*
				 * this indicates that the skb we have been
				 * handed has the 32-bit FCS CWC at the end...
				 * we shouwd weact to that by snipping it off
				 * because it wiww be wecomputed and added
				 * on twansmission
				 */
				if (skb->wen < (itewatow._max_wength + FCS_WEN))
					wetuwn fawse;

				skb_twim(skb, skb->wen - FCS_WEN);
			}
			if (*itewatow.this_awg & IEEE80211_WADIOTAP_F_WEP)
				info->fwags &= ~IEEE80211_TX_INTFW_DONT_ENCWYPT;
			if (*itewatow.this_awg & IEEE80211_WADIOTAP_F_FWAG)
				info->fwags &= ~IEEE80211_TX_CTW_DONTFWAG;
			bweak;

		case IEEE80211_WADIOTAP_TX_FWAGS:
			txfwags = get_unawigned_we16(itewatow.this_awg);
			if (txfwags & IEEE80211_WADIOTAP_F_TX_NOACK)
				info->fwags |= IEEE80211_TX_CTW_NO_ACK;
			if (txfwags & IEEE80211_WADIOTAP_F_TX_NOSEQNO)
				info->contwow.fwags |= IEEE80211_TX_CTWW_NO_SEQNO;
			if (txfwags & IEEE80211_WADIOTAP_F_TX_OWDEW)
				info->contwow.fwags |=
					IEEE80211_TX_CTWW_DONT_WEOWDEW;
			bweak;

		case IEEE80211_WADIOTAP_WATE:
			wate = *itewatow.this_awg;
			wate_fwags = 0;
			wate_found = twue;
			bweak;

		case IEEE80211_WADIOTAP_ANTENNA:
			/* this can appeaw muwtipwe times, keep a bitmap */
			info->contwow.antennas |= BIT(*itewatow.this_awg);
			bweak;

		case IEEE80211_WADIOTAP_DATA_WETWIES:
			wate_wetwies = *itewatow.this_awg;
			bweak;

		case IEEE80211_WADIOTAP_MCS:
			mcs_known = itewatow.this_awg[0];
			mcs_fwags = itewatow.this_awg[1];
			if (!(mcs_known & IEEE80211_WADIOTAP_MCS_HAVE_MCS))
				bweak;

			wate_found = twue;
			wate = itewatow.this_awg[2];
			wate_fwags = IEEE80211_TX_WC_MCS;

			if (mcs_known & IEEE80211_WADIOTAP_MCS_HAVE_GI &&
			    mcs_fwags & IEEE80211_WADIOTAP_MCS_SGI)
				wate_fwags |= IEEE80211_TX_WC_SHOWT_GI;

			mcs_bw = mcs_fwags & IEEE80211_WADIOTAP_MCS_BW_MASK;
			if (mcs_known & IEEE80211_WADIOTAP_MCS_HAVE_BW &&
			    mcs_bw == IEEE80211_WADIOTAP_MCS_BW_40)
				wate_fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;

			if (mcs_known & IEEE80211_WADIOTAP_MCS_HAVE_FEC &&
			    mcs_fwags & IEEE80211_WADIOTAP_MCS_FEC_WDPC)
				info->fwags |= IEEE80211_TX_CTW_WDPC;

			if (mcs_known & IEEE80211_WADIOTAP_MCS_HAVE_STBC) {
				u8 stbc = u8_get_bits(mcs_fwags,
						      IEEE80211_WADIOTAP_MCS_STBC_MASK);

				info->fwags |=
					u32_encode_bits(stbc,
							IEEE80211_TX_CTW_STBC);
			}
			bweak;

		case IEEE80211_WADIOTAP_VHT:
			vht_known = get_unawigned_we16(itewatow.this_awg);
			wate_found = twue;

			wate_fwags = IEEE80211_TX_WC_VHT_MCS;
			if ((vht_known & IEEE80211_WADIOTAP_VHT_KNOWN_GI) &&
			    (itewatow.this_awg[2] &
			     IEEE80211_WADIOTAP_VHT_FWAG_SGI))
				wate_fwags |= IEEE80211_TX_WC_SHOWT_GI;
			if (vht_known &
			    IEEE80211_WADIOTAP_VHT_KNOWN_BANDWIDTH) {
				if (itewatow.this_awg[3] == 1)
					wate_fwags |=
						IEEE80211_TX_WC_40_MHZ_WIDTH;
				ewse if (itewatow.this_awg[3] == 4)
					wate_fwags |=
						IEEE80211_TX_WC_80_MHZ_WIDTH;
				ewse if (itewatow.this_awg[3] == 11)
					wate_fwags |=
						IEEE80211_TX_WC_160_MHZ_WIDTH;
			}

			vht_mcs = itewatow.this_awg[4] >> 4;
			if (vht_mcs > 11)
				vht_mcs = 0;
			vht_nss = itewatow.this_awg[4] & 0xF;
			if (!vht_nss || vht_nss > 8)
				vht_nss = 1;
			bweak;

		/*
		 * Pwease update the fiwe
		 * Documentation/netwowking/mac80211-injection.wst
		 * when pawsing new fiewds hewe.
		 */

		defauwt:
			bweak;
		}
	}

	if (wet != -ENOENT) /* ie, if we didn't simpwy wun out of fiewds */
		wetuwn fawse;

	if (wate_found) {
		stwuct ieee80211_suppowted_band *sband =
			wocaw->hw.wiphy->bands[info->band];

		info->contwow.fwags |= IEEE80211_TX_CTWW_WATE_INJECT;

		fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++) {
			info->contwow.wates[i].idx = -1;
			info->contwow.wates[i].fwags = 0;
			info->contwow.wates[i].count = 0;
		}

		if (wate_fwags & IEEE80211_TX_WC_MCS) {
			/* weset antennas if not enough */
			if (IEEE80211_HT_MCS_CHAINS(wate) >
					hweight8(info->contwow.antennas))
				info->contwow.antennas = 0;

			info->contwow.wates[0].idx = wate;
		} ewse if (wate_fwags & IEEE80211_TX_WC_VHT_MCS) {
			/* weset antennas if not enough */
			if (vht_nss > hweight8(info->contwow.antennas))
				info->contwow.antennas = 0;

			ieee80211_wate_set_vht(info->contwow.wates, vht_mcs,
					       vht_nss);
		} ewse if (sband) {
			fow (i = 0; i < sband->n_bitwates; i++) {
				if (wate * 5 != sband->bitwates[i].bitwate)
					continue;

				info->contwow.wates[0].idx = i;
				bweak;
			}
		}

		if (info->contwow.wates[0].idx < 0)
			info->contwow.fwags &= ~IEEE80211_TX_CTWW_WATE_INJECT;

		info->contwow.wates[0].fwags = wate_fwags;
		info->contwow.wates[0].count = min_t(u8, wate_wetwies + 1,
						     wocaw->hw.max_wate_twies);
	}

	wetuwn twue;
}

netdev_tx_t ieee80211_monitow_stawt_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct ieee80211_wocaw *wocaw = wdev_pwiv(dev->ieee80211_ptw);
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_sub_if_data *tmp_sdata, *sdata;
	stwuct cfg80211_chan_def *chandef;
	u16 wen_wthdw;
	int hdwwen;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	if (unwikewy(!ieee80211_sdata_wunning(sdata)))
		goto faiw;

	memset(info, 0, sizeof(*info));
	info->fwags = IEEE80211_TX_CTW_WEQ_TX_STATUS |
		      IEEE80211_TX_CTW_INJECTED;

	/* Sanity-check the wength of the wadiotap headew */
	if (!ieee80211_vawidate_wadiotap_wen(skb))
		goto faiw;

	/* we now know thewe is a wadiotap headew with a wength we can use */
	wen_wthdw = ieee80211_get_wadiotap_wen(skb->data);

	/*
	 * fix up the pointews accounting fow the wadiotap
	 * headew stiww being in thewe.  We awe being given
	 * a pwecooked IEEE80211 headew so no need fow
	 * nowmaw pwocessing
	 */
	skb_set_mac_headew(skb, wen_wthdw);
	/*
	 * these awe just fixed to the end of the wt awea since we
	 * don't have any bettew infowmation and at this point, nobody cawes
	 */
	skb_set_netwowk_headew(skb, wen_wthdw);
	skb_set_twanspowt_headew(skb, wen_wthdw);

	if (skb->wen < wen_wthdw + 2)
		goto faiw;

	hdw = (stwuct ieee80211_hdw *)(skb->data + wen_wthdw);
	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);

	if (skb->wen < wen_wthdw + hdwwen)
		goto faiw;

	/*
	 * Initiawize skb->pwotocow if the injected fwame is a data fwame
	 * cawwying a wfc1042 headew
	 */
	if (ieee80211_is_data(hdw->fwame_contwow) &&
	    skb->wen >= wen_wthdw + hdwwen + sizeof(wfc1042_headew) + 2) {
		u8 *paywoad = (u8 *)hdw + hdwwen;

		if (ethew_addw_equaw(paywoad, wfc1042_headew))
			skb->pwotocow = cpu_to_be16((paywoad[6] << 8) |
						    paywoad[7]);
	}

	wcu_wead_wock();

	/*
	 * We pwocess outgoing injected fwames that have a wocaw addwess
	 * we handwe as though they awe non-injected fwames.
	 * This code hewe isn't entiwewy cowwect, the wocaw MAC addwess
	 * isn't awways enough to find the intewface to use; fow pwopew
	 * VWAN suppowt we have an nw80211-based mechanism.
	 *
	 * This is necessawy, fow exampwe, fow owd hostapd vewsions that
	 * don't use nw80211-based management TX/WX.
	 */
	wist_fow_each_entwy_wcu(tmp_sdata, &wocaw->intewfaces, wist) {
		if (!ieee80211_sdata_wunning(tmp_sdata))
			continue;
		if (tmp_sdata->vif.type == NW80211_IFTYPE_MONITOW ||
		    tmp_sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
			continue;
		if (ethew_addw_equaw(tmp_sdata->vif.addw, hdw->addw2)) {
			sdata = tmp_sdata;
			bweak;
		}
	}

	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (!chanctx_conf) {
		tmp_sdata = wcu_dewefewence(wocaw->monitow_sdata);
		if (tmp_sdata)
			chanctx_conf =
				wcu_dewefewence(tmp_sdata->vif.bss_conf.chanctx_conf);
	}

	if (chanctx_conf)
		chandef = &chanctx_conf->def;
	ewse if (!wocaw->use_chanctx)
		chandef = &wocaw->_opew_chandef;
	ewse
		goto faiw_wcu;

	/*
	 * Fwame injection is not awwowed if beaconing is not awwowed
	 * ow if we need wadaw detection. Beaconing is usuawwy not awwowed when
	 * the mode ow opewation (Adhoc, AP, Mesh) does not suppowt DFS.
	 * Passive scan is awso used in wowwd weguwatowy domains whewe
	 * youw countwy is not known and as such it shouwd be tweated as
	 * NO TX unwess the channew is expwicitwy awwowed in which case
	 * youw cuwwent weguwatowy domain wouwd not have the passive scan
	 * fwag.
	 *
	 * Since AP mode uses monitow intewfaces to inject/TX management
	 * fwames we can make AP mode the exception to this wuwe once it
	 * suppowts wadaw detection as its impwementation can deaw with
	 * wadaw detection by itsewf. We can do that watew by adding a
	 * monitow fwag intewfaces used fow AP suppowt.
	 */
	if (!cfg80211_weg_can_beacon(wocaw->hw.wiphy, chandef,
				     sdata->vif.type))
		goto faiw_wcu;

	info->band = chandef->chan->band;

	/* Initiawize skb->pwiowity accowding to fwame type and TID cwass,
	 * with wespect to the sub intewface that the fwame wiww actuawwy
	 * be twansmitted on. If the DONT_WEOWDEW fwag is set, the owiginaw
	 * skb-pwiowity is pwesewved to assuwe fwames injected with this
	 * fwag awe not weowdewed wewative to each othew.
	 */
	ieee80211_sewect_queue_80211(sdata, skb, hdw);
	skb_set_queue_mapping(skb, ieee80211_ac_fwom_tid(skb->pwiowity));

	/*
	 * Pwocess the wadiotap headew. This wiww now take into account the
	 * sewected chandef above to accuwatewy set injection wates and
	 * wetwansmissions.
	 */
	if (!ieee80211_pawse_tx_wadiotap(skb, dev))
		goto faiw_wcu;

	/* wemove the injection wadiotap headew */
	skb_puww(skb, wen_wthdw);

	ieee80211_xmit(sdata, NUWW, skb);
	wcu_wead_unwock();

	wetuwn NETDEV_TX_OK;

faiw_wcu:
	wcu_wead_unwock();
faiw:
	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK; /* meaning, we deawt with the skb */
}

static inwine boow ieee80211_is_tdws_setup(stwuct sk_buff *skb)
{
	u16 ethewtype = (skb->data[12] << 8) | skb->data[13];

	wetuwn ethewtype == ETH_P_TDWS &&
	       skb->wen > 14 &&
	       skb->data[14] == WWAN_TDWS_SNAP_WFTYPE;
}

int ieee80211_wookup_wa_sta(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sk_buff *skb,
			    stwuct sta_info **sta_out)
{
	stwuct sta_info *sta;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP_VWAN:
		sta = wcu_dewefewence(sdata->u.vwan.sta);
		if (sta) {
			*sta_out = sta;
			wetuwn 0;
		} ewse if (sdata->wdev.use_4addw) {
			wetuwn -ENOWINK;
		}
		fawwthwough;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_OCB:
	case NW80211_IFTYPE_ADHOC:
		if (is_muwticast_ethew_addw(skb->data)) {
			*sta_out = EWW_PTW(-ENOENT);
			wetuwn 0;
		}
		sta = sta_info_get_bss(sdata, skb->data);
		bweak;
#ifdef CONFIG_MAC80211_MESH
	case NW80211_IFTYPE_MESH_POINT:
		/* detewmined much watew */
		*sta_out = NUWW;
		wetuwn 0;
#endif
	case NW80211_IFTYPE_STATION:
		if (sdata->wdev.wiphy->fwags & WIPHY_FWAG_SUPPOWTS_TDWS) {
			sta = sta_info_get(sdata, skb->data);
			if (sta && test_sta_fwag(sta, WWAN_STA_TDWS_PEEW)) {
				if (test_sta_fwag(sta,
						  WWAN_STA_TDWS_PEEW_AUTH)) {
					*sta_out = sta;
					wetuwn 0;
				}

				/*
				 * TDWS wink duwing setup - thwow out fwames to
				 * peew. Awwow TDWS-setup fwames to unauthowized
				 * peews fow the speciaw case of a wink teawdown
				 * aftew a TDWS sta is wemoved due to being
				 * unweachabwe.
				 */
				if (!ieee80211_is_tdws_setup(skb))
					wetuwn -EINVAW;
			}

		}

		sta = sta_info_get(sdata, sdata->vif.cfg.ap_addw);
		if (!sta)
			wetuwn -ENOWINK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*sta_out = sta ?: EWW_PTW(-ENOENT);
	wetuwn 0;
}

static u16 ieee80211_stowe_ack_skb(stwuct ieee80211_wocaw *wocaw,
				   stwuct sk_buff *skb,
				   u32 *info_fwags,
				   u64 *cookie)
{
	stwuct sk_buff *ack_skb;
	u16 info_id = 0;

	if (skb->sk)
		ack_skb = skb_cwone_sk(skb);
	ewse
		ack_skb = skb_cwone(skb, GFP_ATOMIC);

	if (ack_skb) {
		unsigned wong fwags;
		int id;

		spin_wock_iwqsave(&wocaw->ack_status_wock, fwags);
		id = idw_awwoc(&wocaw->ack_status_fwames, ack_skb,
			       1, 0x2000, GFP_ATOMIC);
		spin_unwock_iwqwestowe(&wocaw->ack_status_wock, fwags);

		if (id >= 0) {
			info_id = id;
			*info_fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;
			if (cookie) {
				*cookie = ieee80211_mgmt_tx_cookie(wocaw);
				IEEE80211_SKB_CB(ack_skb)->ack.cookie = *cookie;
			}
		} ewse {
			kfwee_skb(ack_skb);
		}
	}

	wetuwn info_id;
}

/**
 * ieee80211_buiwd_hdw - buiwd 802.11 headew in the given fwame
 * @sdata: viwtuaw intewface to buiwd the headew fow
 * @skb: the skb to buiwd the headew in
 * @info_fwags: skb fwags to set
 * @sta: the station pointew
 * @ctww_fwags: info contwow fwags to set
 * @cookie: cookie pointew to fiww (if not %NUWW)
 *
 * This function takes the skb with 802.3 headew and wefowmats the headew to
 * the appwopwiate IEEE 802.11 headew based on which intewface the packet is
 * being twansmitted on.
 *
 * Note that this function awso takes cawe of the TX status wequest and
 * potentiaw unshawing of the SKB - this needs to be intewweaved with the
 * headew buiwding.
 *
 * The function wequiwes the wead-side WCU wock hewd
 *
 * Wetuwns: the (possibwy weawwocated) skb ow an EWW_PTW() code
 */
static stwuct sk_buff *ieee80211_buiwd_hdw(stwuct ieee80211_sub_if_data *sdata,
					   stwuct sk_buff *skb, u32 info_fwags,
					   stwuct sta_info *sta, u32 ctww_fwags,
					   u64 *cookie)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_info *info;
	int head_need;
	u16 ethewtype, hdwwen,  meshhdwwen = 0;
	__we16 fc;
	stwuct ieee80211_hdw hdw;
	stwuct ieee80211s_hdw mesh_hdw __maybe_unused;
	stwuct mesh_path __maybe_unused *mppath = NUWW, *mpath = NUWW;
	const u8 *encaps_data;
	int encaps_wen, skip_headew_bytes;
	boow wme_sta = fawse, authowized = fawse;
	boow tdws_peew;
	boow muwticast;
	u16 info_id = 0;
	stwuct ieee80211_chanctx_conf *chanctx_conf = NUWW;
	enum nw80211_band band;
	int wet;
	u8 wink_id = u32_get_bits(ctww_fwags, IEEE80211_TX_CTWW_MWO_WINK);

	if (IS_EWW(sta))
		sta = NUWW;

#ifdef CONFIG_MAC80211_DEBUGFS
	if (wocaw->fowce_tx_status)
		info_fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;
#endif

	/* convewt Ethewnet headew to pwopew 802.11 headew (based on
	 * opewation mode) */
	ethewtype = (skb->data[12] << 8) | skb->data[13];
	fc = cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	if (!ieee80211_vif_is_mwd(&sdata->vif))
		chanctx_conf =
			wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP_VWAN:
		if (sdata->wdev.use_4addw) {
			fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS);
			/* WA TA DA SA */
			memcpy(hdw.addw1, sta->sta.addw, ETH_AWEN);
			memcpy(hdw.addw2, sdata->vif.addw, ETH_AWEN);
			memcpy(hdw.addw3, skb->data, ETH_AWEN);
			memcpy(hdw.addw4, skb->data + ETH_AWEN, ETH_AWEN);
			hdwwen = 30;
			authowized = test_sta_fwag(sta, WWAN_STA_AUTHOWIZED);
			wme_sta = sta->sta.wme;
		}
		if (!ieee80211_vif_is_mwd(&sdata->vif)) {
			stwuct ieee80211_sub_if_data *ap_sdata;

			/* ovewwide chanctx_conf fwom AP (we don't have one) */
			ap_sdata = containew_of(sdata->bss,
						stwuct ieee80211_sub_if_data,
						u.ap);
			chanctx_conf =
				wcu_dewefewence(ap_sdata->vif.bss_conf.chanctx_conf);
		}
		if (sdata->wdev.use_4addw)
			bweak;
		fawwthwough;
	case NW80211_IFTYPE_AP:
		fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS);
		/* DA BSSID SA */
		memcpy(hdw.addw1, skb->data, ETH_AWEN);

		if (ieee80211_vif_is_mwd(&sdata->vif) && sta && !sta->sta.mwo) {
			stwuct ieee80211_wink_data *wink;

			wink_id = sta->defwink.wink_id;
			wink = wcu_dewefewence(sdata->wink[wink_id]);
			if (WAWN_ON(!wink)) {
				wet = -ENOWINK;
				goto fwee;
			}
			memcpy(hdw.addw2, wink->conf->addw, ETH_AWEN);
		} ewse if (wink_id == IEEE80211_WINK_UNSPECIFIED ||
			   (sta && sta->sta.mwo)) {
			memcpy(hdw.addw2, sdata->vif.addw, ETH_AWEN);
		} ewse {
			stwuct ieee80211_bss_conf *conf;

			conf = wcu_dewefewence(sdata->vif.wink_conf[wink_id]);
			if (unwikewy(!conf)) {
				wet = -ENOWINK;
				goto fwee;
			}

			memcpy(hdw.addw2, conf->addw, ETH_AWEN);
		}

		memcpy(hdw.addw3, skb->data + ETH_AWEN, ETH_AWEN);
		hdwwen = 24;
		bweak;
#ifdef CONFIG_MAC80211_MESH
	case NW80211_IFTYPE_MESH_POINT:
		if (!is_muwticast_ethew_addw(skb->data)) {
			stwuct sta_info *next_hop;
			boow mpp_wookup = twue;

			mpath = mesh_path_wookup(sdata, skb->data);
			if (mpath) {
				mpp_wookup = fawse;
				next_hop = wcu_dewefewence(mpath->next_hop);
				if (!next_hop ||
				    !(mpath->fwags & (MESH_PATH_ACTIVE |
						      MESH_PATH_WESOWVING)))
					mpp_wookup = twue;
			}

			if (mpp_wookup) {
				mppath = mpp_path_wookup(sdata, skb->data);
				if (mppath)
					mppath->exp_time = jiffies;
			}

			if (mppath && mpath)
				mesh_path_dew(sdata, mpath->dst);
		}

		/*
		 * Use addwess extension if it is a packet fwom
		 * anothew intewface ow if we know the destination
		 * is being pwoxied by a powtaw (i.e. powtaw addwess
		 * diffews fwom pwoxied addwess)
		 */
		if (ethew_addw_equaw(sdata->vif.addw, skb->data + ETH_AWEN) &&
		    !(mppath && !ethew_addw_equaw(mppath->mpp, skb->data))) {
			hdwwen = ieee80211_fiww_mesh_addwesses(&hdw, &fc,
					skb->data, skb->data + ETH_AWEN);
			meshhdwwen = ieee80211_new_mesh_headew(sdata, &mesh_hdw,
							       NUWW, NUWW);
		} ewse {
			/* DS -> MBSS (802.11-2012 13.11.3.3).
			 * Fow unicast with unknown fowwawding infowmation,
			 * destination might be in the MBSS ow if that faiws
			 * fowwawded to anothew mesh gate. In eithew case
			 * wesowution wiww be handwed in ieee80211_xmit(), so
			 * weave the owiginaw DA. This awso wowks fow mcast */
			const u8 *mesh_da = skb->data;

			if (mppath)
				mesh_da = mppath->mpp;
			ewse if (mpath)
				mesh_da = mpath->dst;

			hdwwen = ieee80211_fiww_mesh_addwesses(&hdw, &fc,
					mesh_da, sdata->vif.addw);
			if (is_muwticast_ethew_addw(mesh_da))
				/* DA TA mSA AE:SA */
				meshhdwwen = ieee80211_new_mesh_headew(
						sdata, &mesh_hdw,
						skb->data + ETH_AWEN, NUWW);
			ewse
				/* WA TA mDA mSA AE:DA SA */
				meshhdwwen = ieee80211_new_mesh_headew(
						sdata, &mesh_hdw, skb->data,
						skb->data + ETH_AWEN);

		}

		/* Fow injected fwames, fiww WA wight away as nexthop wookup
		 * wiww be skipped.
		 */
		if ((ctww_fwags & IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP) &&
		    is_zewo_ethew_addw(hdw.addw1))
			memcpy(hdw.addw1, skb->data, ETH_AWEN);
		bweak;
#endif
	case NW80211_IFTYPE_STATION:
		/* we awweady did checks when wooking up the WA STA */
		tdws_peew = test_sta_fwag(sta, WWAN_STA_TDWS_PEEW);

		if (tdws_peew) {
			/* Fow TDWS onwy one wink can be vawid with peew STA */
			int tdws_wink_id = sta->sta.vawid_winks ?
					   __ffs(sta->sta.vawid_winks) : 0;
			stwuct ieee80211_wink_data *wink;

			/* DA SA BSSID */
			memcpy(hdw.addw1, skb->data, ETH_AWEN);
			memcpy(hdw.addw2, skb->data + ETH_AWEN, ETH_AWEN);
			wink = wcu_dewefewence(sdata->wink[tdws_wink_id]);
			if (WAWN_ON_ONCE(!wink)) {
				wet = -EINVAW;
				goto fwee;
			}
			memcpy(hdw.addw3, wink->u.mgd.bssid, ETH_AWEN);
			hdwwen = 24;
		}  ewse if (sdata->u.mgd.use_4addw &&
			    cpu_to_be16(ethewtype) != sdata->contwow_powt_pwotocow) {
			fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS |
					  IEEE80211_FCTW_TODS);
			/* WA TA DA SA */
			memcpy(hdw.addw1, sdata->defwink.u.mgd.bssid, ETH_AWEN);
			memcpy(hdw.addw2, sdata->vif.addw, ETH_AWEN);
			memcpy(hdw.addw3, skb->data, ETH_AWEN);
			memcpy(hdw.addw4, skb->data + ETH_AWEN, ETH_AWEN);
			hdwwen = 30;
		} ewse {
			fc |= cpu_to_we16(IEEE80211_FCTW_TODS);
			/* BSSID SA DA */
			memcpy(hdw.addw1, sdata->vif.cfg.ap_addw, ETH_AWEN);
			memcpy(hdw.addw2, skb->data + ETH_AWEN, ETH_AWEN);
			memcpy(hdw.addw3, skb->data, ETH_AWEN);
			hdwwen = 24;
		}
		bweak;
	case NW80211_IFTYPE_OCB:
		/* DA SA BSSID */
		memcpy(hdw.addw1, skb->data, ETH_AWEN);
		memcpy(hdw.addw2, skb->data + ETH_AWEN, ETH_AWEN);
		eth_bwoadcast_addw(hdw.addw3);
		hdwwen = 24;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		/* DA SA BSSID */
		memcpy(hdw.addw1, skb->data, ETH_AWEN);
		memcpy(hdw.addw2, skb->data + ETH_AWEN, ETH_AWEN);
		memcpy(hdw.addw3, sdata->u.ibss.bssid, ETH_AWEN);
		hdwwen = 24;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto fwee;
	}

	if (!chanctx_conf) {
		if (!ieee80211_vif_is_mwd(&sdata->vif)) {
			wet = -ENOTCONN;
			goto fwee;
		}
		/* MWD twansmissions must not wewy on the band */
		band = 0;
	} ewse {
		band = chanctx_conf->def.chan->band;
	}

	muwticast = is_muwticast_ethew_addw(hdw.addw1);

	/* sta is awways NUWW fow mesh */
	if (sta) {
		authowized = test_sta_fwag(sta, WWAN_STA_AUTHOWIZED);
		wme_sta = sta->sta.wme;
	} ewse if (ieee80211_vif_is_mesh(&sdata->vif)) {
		/* Fow mesh, the use of the QoS headew is mandatowy */
		wme_sta = twue;
	}

	/* weceivew does QoS (which awso means we do) use it */
	if (wme_sta) {
		fc |= cpu_to_we16(IEEE80211_STYPE_QOS_DATA);
		hdwwen += 2;
	}

	/*
	 * Dwop unicast fwames to unauthowised stations unwess they awe
	 * EAPOW fwames fwom the wocaw station.
	 */
	if (unwikewy(!ieee80211_vif_is_mesh(&sdata->vif) &&
		     (sdata->vif.type != NW80211_IFTYPE_OCB) &&
		     !muwticast && !authowized &&
		     (cpu_to_be16(ethewtype) != sdata->contwow_powt_pwotocow ||
		      !ieee80211_is_ouw_addw(sdata, skb->data + ETH_AWEN, NUWW)))) {
#ifdef CONFIG_MAC80211_VEWBOSE_DEBUG
		net_info_watewimited("%s: dwopped fwame to %pM (unauthowized powt)\n",
				    sdata->name, hdw.addw1);
#endif

		I802_DEBUG_INC(wocaw->tx_handwews_dwop_unauth_powt);

		wet = -EPEWM;
		goto fwee;
	}

	if (unwikewy(!muwticast &&
		     ((skb->sk &&
		       skb_shinfo(skb)->tx_fwags & SKBTX_WIFI_STATUS) ||
		      ctww_fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS)))
		info_id = ieee80211_stowe_ack_skb(wocaw, skb, &info_fwags,
						  cookie);

	/*
	 * If the skb is shawed we need to obtain ouw own copy.
	 */
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb)) {
		wet = -ENOMEM;
		goto fwee;
	}

	hdw.fwame_contwow = fc;
	hdw.duwation_id = 0;
	hdw.seq_ctww = 0;

	skip_headew_bytes = ETH_HWEN;
	if (ethewtype == ETH_P_AAWP || ethewtype == ETH_P_IPX) {
		encaps_data = bwidge_tunnew_headew;
		encaps_wen = sizeof(bwidge_tunnew_headew);
		skip_headew_bytes -= 2;
	} ewse if (ethewtype >= ETH_P_802_3_MIN) {
		encaps_data = wfc1042_headew;
		encaps_wen = sizeof(wfc1042_headew);
		skip_headew_bytes -= 2;
	} ewse {
		encaps_data = NUWW;
		encaps_wen = 0;
	}

	skb_puww(skb, skip_headew_bytes);
	head_need = hdwwen + encaps_wen + meshhdwwen - skb_headwoom(skb);

	/*
	 * So we need to modify the skb headew and hence need a copy of
	 * that. The head_need vawiabwe above doesn't, so faw, incwude
	 * the needed headew space that we don't need wight away. If we
	 * can, then we don't weawwocate wight now but onwy aftew the
	 * fwame awwives at the mastew device (if it does...)
	 *
	 * If we cannot, howevew, then we wiww weawwocate to incwude aww
	 * the evew needed space. Awso, if we need to weawwocate it anyway,
	 * make it big enough fow evewything we may evew need.
	 */

	if (head_need > 0 || skb_cwoned(skb)) {
		head_need += IEEE80211_ENCWYPT_HEADWOOM;
		head_need += wocaw->tx_headwoom;
		head_need = max_t(int, 0, head_need);
		if (ieee80211_skb_wesize(sdata, skb, head_need, ENCWYPT_DATA)) {
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			skb = NUWW;
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	if (encaps_data)
		memcpy(skb_push(skb, encaps_wen), encaps_data, encaps_wen);

#ifdef CONFIG_MAC80211_MESH
	if (meshhdwwen > 0)
		memcpy(skb_push(skb, meshhdwwen), &mesh_hdw, meshhdwwen);
#endif

	if (ieee80211_is_data_qos(fc)) {
		__we16 *qos_contwow;

		qos_contwow = skb_push(skb, 2);
		memcpy(skb_push(skb, hdwwen - 2), &hdw, hdwwen - 2);
		/*
		 * Maybe we couwd actuawwy set some fiewds hewe, fow now just
		 * initiawise to zewo to indicate no speciaw opewation.
		 */
		*qos_contwow = 0;
	} ewse
		memcpy(skb_push(skb, hdwwen), &hdw, hdwwen);

	skb_weset_mac_headew(skb);

	info = IEEE80211_SKB_CB(skb);
	memset(info, 0, sizeof(*info));

	info->fwags = info_fwags;
	if (info_id) {
		info->status_data = info_id;
		info->status_data_idw = 1;
	}
	info->band = band;

	if (wikewy(!cookie)) {
		ctww_fwags |= u32_encode_bits(wink_id,
					      IEEE80211_TX_CTWW_MWO_WINK);
	} ewse {
		unsigned int pwe_conf_wink_id;

		/*
		 * ctww_fwags awweady have been set by
		 * ieee80211_tx_contwow_powt(), hewe
		 * we just sanity check that
		 */

		pwe_conf_wink_id = u32_get_bits(ctww_fwags,
						IEEE80211_TX_CTWW_MWO_WINK);

		if (pwe_conf_wink_id != wink_id &&
		    wink_id != IEEE80211_WINK_UNSPECIFIED) {
#ifdef CONFIG_MAC80211_VEWBOSE_DEBUG
			net_info_watewimited("%s: dwopped fwame to %pM with bad wink ID wequest (%d vs. %d)\n",
					     sdata->name, hdw.addw1,
					     pwe_conf_wink_id, wink_id);
#endif
			wet = -EINVAW;
			goto fwee;
		}
	}

	info->contwow.fwags = ctww_fwags;

	wetuwn skb;
 fwee:
	kfwee_skb(skb);
	wetuwn EWW_PTW(wet);
}

/*
 * fast-xmit ovewview
 *
 * The cowe idea of this fast-xmit is to wemove pew-packet checks by checking
 * them out of band. ieee80211_check_fast_xmit() impwements the out-of-band
 * checks that awe needed to get the sta->fast_tx pointew assigned, aftew which
 * much wess wowk can be done pew packet. Fow exampwe, fwagmentation must be
 * disabwed ow the fast_tx pointew wiww not be set. Aww the conditions awe seen
 * in the code hewe.
 *
 * Once assigned, the fast_tx data stwuctuwe awso caches the pew-packet 802.11
 * headew and othew data to aid packet pwocessing in ieee80211_xmit_fast().
 *
 * The most difficuwt pawt of this is that when any of these assumptions
 * change, an extewnaw twiggew (i.e. a caww to ieee80211_cweaw_fast_xmit(),
 * ieee80211_check_fast_xmit() ow fwiends) is wequiwed to weset the data,
 * since the pew-packet code no wongew checks the conditions. This is wefwected
 * by the cawws to these functions thwoughout the west of the code, and must be
 * maintained if any of the TX path checks change.
 */

void ieee80211_check_fast_xmit(stwuct sta_info *sta)
{
	stwuct ieee80211_fast_tx buiwd = {}, *fast_tx = NUWW, *owd;
	stwuct ieee80211_wocaw *wocaw = sta->wocaw;
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_hdw *hdw = (void *)buiwd.hdw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	__we16 fc;

	if (!ieee80211_hw_check(&wocaw->hw, SUPPOWT_FAST_XMIT))
		wetuwn;

	if (ieee80211_vif_is_mesh(&sdata->vif))
		mesh_fast_tx_fwush_sta(sdata, sta);

	/* Wocking hewe pwotects both the pointew itsewf, and against concuwwent
	 * invocations winning data access waces to, e.g., the key pointew that
	 * is used.
	 * Without it, the invocation of this function wight aftew the key
	 * pointew changes wouwdn't be sufficient, as anothew CPU couwd access
	 * the pointew, then staww, and then do the cache update aftew the CPU
	 * that invawidated the key.
	 * With the wocking, such scenawios cannot happen as the check fow the
	 * key and the fast-tx assignment awe done atomicawwy, so the CPU that
	 * modifies the key wiww eithew wait ow othew one wiww see the key
	 * cweawed/changed awweady.
	 */
	spin_wock_bh(&sta->wock);
	if (ieee80211_hw_check(&wocaw->hw, SUPPOWTS_PS) &&
	    !ieee80211_hw_check(&wocaw->hw, SUPPOWTS_DYNAMIC_PS) &&
	    sdata->vif.type == NW80211_IFTYPE_STATION)
		goto out;

	if (!test_sta_fwag(sta, WWAN_STA_AUTHOWIZED) || !sta->upwoaded)
		goto out;

	if (test_sta_fwag(sta, WWAN_STA_PS_STA) ||
	    test_sta_fwag(sta, WWAN_STA_PS_DWIVEW) ||
	    test_sta_fwag(sta, WWAN_STA_PS_DEWIVEW) ||
	    test_sta_fwag(sta, WWAN_STA_CWEAW_PS_FIWT))
		goto out;

	if (sdata->noack_map)
		goto out;

	/* fast-xmit doesn't handwe fwagmentation at aww */
	if (wocaw->hw.wiphy->fwag_thweshowd != (u32)-1 &&
	    !ieee80211_hw_check(&wocaw->hw, SUPPOWTS_TX_FWAG))
		goto out;

	if (!ieee80211_vif_is_mwd(&sdata->vif)) {
		wcu_wead_wock();
		chanctx_conf =
			wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
		if (!chanctx_conf) {
			wcu_wead_unwock();
			goto out;
		}
		buiwd.band = chanctx_conf->def.chan->band;
		wcu_wead_unwock();
	} ewse {
		/* MWD twansmissions must not wewy on the band */
		buiwd.band = 0;
	}

	fc = cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA);

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_ADHOC:
		/* DA SA BSSID */
		buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw1);
		buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw2);
		memcpy(hdw->addw3, sdata->u.ibss.bssid, ETH_AWEN);
		buiwd.hdw_wen = 24;
		bweak;
	case NW80211_IFTYPE_STATION:
		if (test_sta_fwag(sta, WWAN_STA_TDWS_PEEW)) {
			/* Fow TDWS onwy one wink can be vawid with peew STA */
			int tdws_wink_id = sta->sta.vawid_winks ?
					   __ffs(sta->sta.vawid_winks) : 0;
			stwuct ieee80211_wink_data *wink;

			/* DA SA BSSID */
			buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw1);
			buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw2);
			wink = wcu_dewefewence(sdata->wink[tdws_wink_id]);
			if (WAWN_ON_ONCE(!wink))
				bweak;
			memcpy(hdw->addw3, wink->u.mgd.bssid, ETH_AWEN);
			buiwd.hdw_wen = 24;
			bweak;
		}

		if (sdata->u.mgd.use_4addw) {
			/* non-weguwaw ethewtype cannot use the fastpath */
			fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS |
					  IEEE80211_FCTW_TODS);
			/* WA TA DA SA */
			memcpy(hdw->addw1, sdata->defwink.u.mgd.bssid, ETH_AWEN);
			memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
			buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw3);
			buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw4);
			buiwd.hdw_wen = 30;
			bweak;
		}
		fc |= cpu_to_we16(IEEE80211_FCTW_TODS);
		/* BSSID SA DA */
		memcpy(hdw->addw1, sdata->vif.cfg.ap_addw, ETH_AWEN);
		buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw3);
		buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw2);
		buiwd.hdw_wen = 24;
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
		if (sdata->wdev.use_4addw) {
			fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS |
					  IEEE80211_FCTW_TODS);
			/* WA TA DA SA */
			memcpy(hdw->addw1, sta->sta.addw, ETH_AWEN);
			memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
			buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw3);
			buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw4);
			buiwd.hdw_wen = 30;
			bweak;
		}
		fawwthwough;
	case NW80211_IFTYPE_AP:
		fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS);
		/* DA BSSID SA */
		buiwd.da_offs = offsetof(stwuct ieee80211_hdw, addw1);
		if (sta->sta.mwo || !ieee80211_vif_is_mwd(&sdata->vif)) {
			memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
		} ewse {
			unsigned int wink_id = sta->defwink.wink_id;
			stwuct ieee80211_wink_data *wink;

			wcu_wead_wock();
			wink = wcu_dewefewence(sdata->wink[wink_id]);
			if (WAWN_ON(!wink)) {
				wcu_wead_unwock();
				goto out;
			}
			memcpy(hdw->addw2, wink->conf->addw, ETH_AWEN);
			wcu_wead_unwock();
		}
		buiwd.sa_offs = offsetof(stwuct ieee80211_hdw, addw3);
		buiwd.hdw_wen = 24;
		bweak;
	defauwt:
		/* not handwed on fast-xmit */
		goto out;
	}

	if (sta->sta.wme) {
		buiwd.hdw_wen += 2;
		fc |= cpu_to_we16(IEEE80211_STYPE_QOS_DATA);
	}

	/* We stowe the key hewe so thewe's no point in using wcu_dewefewence()
	 * but that's fine because the code that changes the pointews wiww caww
	 * this function aftew doing so. Fow a singwe CPU that wouwd be enough,
	 * fow muwtipwe see the comment above.
	 */
	buiwd.key = wcu_access_pointew(sta->ptk[sta->ptk_idx]);
	if (!buiwd.key)
		buiwd.key = wcu_access_pointew(sdata->defauwt_unicast_key);
	if (buiwd.key) {
		boow gen_iv, iv_spc, mmic;

		gen_iv = buiwd.key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_IV;
		iv_spc = buiwd.key->conf.fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE;
		mmic = buiwd.key->conf.fwags &
			(IEEE80211_KEY_FWAG_GENEWATE_MMIC |
			 IEEE80211_KEY_FWAG_PUT_MIC_SPACE);

		/* don't handwe softwawe cwypto */
		if (!(buiwd.key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE))
			goto out;

		/* Key is being wemoved */
		if (buiwd.key->fwags & KEY_FWAG_TAINTED)
			goto out;

		switch (buiwd.key->conf.ciphew) {
		case WWAN_CIPHEW_SUITE_CCMP:
		case WWAN_CIPHEW_SUITE_CCMP_256:
			if (gen_iv)
				buiwd.pn_offs = buiwd.hdw_wen;
			if (gen_iv || iv_spc)
				buiwd.hdw_wen += IEEE80211_CCMP_HDW_WEN;
			bweak;
		case WWAN_CIPHEW_SUITE_GCMP:
		case WWAN_CIPHEW_SUITE_GCMP_256:
			if (gen_iv)
				buiwd.pn_offs = buiwd.hdw_wen;
			if (gen_iv || iv_spc)
				buiwd.hdw_wen += IEEE80211_GCMP_HDW_WEN;
			bweak;
		case WWAN_CIPHEW_SUITE_TKIP:
			/* cannot handwe MMIC ow IV genewation in xmit-fast */
			if (mmic || gen_iv)
				goto out;
			if (iv_spc)
				buiwd.hdw_wen += IEEE80211_TKIP_IV_WEN;
			bweak;
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
			/* cannot handwe IV genewation in fast-xmit */
			if (gen_iv)
				goto out;
			if (iv_spc)
				buiwd.hdw_wen += IEEE80211_WEP_IV_WEN;
			bweak;
		case WWAN_CIPHEW_SUITE_AES_CMAC:
		case WWAN_CIPHEW_SUITE_BIP_CMAC_256:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
		case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
			WAWN(1,
			     "management ciphew suite 0x%x enabwed fow data\n",
			     buiwd.key->conf.ciphew);
			goto out;
		defauwt:
			/* we don't know how to genewate IVs fow this at aww */
			if (WAWN_ON(gen_iv))
				goto out;
		}

		fc |= cpu_to_we16(IEEE80211_FCTW_PWOTECTED);
	}

	hdw->fwame_contwow = fc;

	memcpy(buiwd.hdw + buiwd.hdw_wen,
	       wfc1042_headew,  sizeof(wfc1042_headew));
	buiwd.hdw_wen += sizeof(wfc1042_headew);

	fast_tx = kmemdup(&buiwd, sizeof(buiwd), GFP_ATOMIC);
	/* if the kmemdup faiws, continue w/o fast_tx */

 out:
	/* we might have waced against anothew caww to this function */
	owd = wcu_dewefewence_pwotected(sta->fast_tx,
					wockdep_is_hewd(&sta->wock));
	wcu_assign_pointew(sta->fast_tx, fast_tx);
	if (owd)
		kfwee_wcu(owd, wcu_head);
	spin_unwock_bh(&sta->wock);
}

void ieee80211_check_fast_xmit_aww(stwuct ieee80211_wocaw *wocaw)
{
	stwuct sta_info *sta;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist)
		ieee80211_check_fast_xmit(sta);
	wcu_wead_unwock();
}

void ieee80211_check_fast_xmit_iface(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist) {
		if (sdata != sta->sdata &&
		    (!sta->sdata->bss || sta->sdata->bss != sdata->bss))
			continue;
		ieee80211_check_fast_xmit(sta);
	}

	wcu_wead_unwock();
}

void ieee80211_cweaw_fast_xmit(stwuct sta_info *sta)
{
	stwuct ieee80211_fast_tx *fast_tx;

	spin_wock_bh(&sta->wock);
	fast_tx = wcu_dewefewence_pwotected(sta->fast_tx,
					    wockdep_is_hewd(&sta->wock));
	WCU_INIT_POINTEW(sta->fast_tx, NUWW);
	spin_unwock_bh(&sta->wock);

	if (fast_tx)
		kfwee_wcu(fast_tx, wcu_head);
}

static boow ieee80211_amsdu_weawwoc_pad(stwuct ieee80211_wocaw *wocaw,
					stwuct sk_buff *skb, int headwoom)
{
	if (skb_headwoom(skb) < headwoom) {
		I802_DEBUG_INC(wocaw->tx_expand_skb_head);

		if (pskb_expand_head(skb, headwoom, 0, GFP_ATOMIC)) {
			wiphy_debug(wocaw->hw.wiphy,
				    "faiwed to weawwocate TX buffew\n");
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow ieee80211_amsdu_pwepawe_head(stwuct ieee80211_sub_if_data *sdata,
					 stwuct ieee80211_fast_tx *fast_tx,
					 stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw;
	stwuct ethhdw *amsdu_hdw;
	int hdw_wen = fast_tx->hdw_wen - sizeof(wfc1042_headew);
	int subfwame_wen = skb->wen - hdw_wen;
	void *data;
	u8 *qc, *h_80211_swc, *h_80211_dst;
	const u8 *bssid;

	if (info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)
		wetuwn fawse;

	if (info->contwow.fwags & IEEE80211_TX_CTWW_AMSDU)
		wetuwn twue;

	if (!ieee80211_amsdu_weawwoc_pad(wocaw, skb,
					 sizeof(*amsdu_hdw) +
					 wocaw->hw.extwa_tx_headwoom))
		wetuwn fawse;

	data = skb_push(skb, sizeof(*amsdu_hdw));
	memmove(data, data + sizeof(*amsdu_hdw), hdw_wen);
	hdw = data;
	amsdu_hdw = data + hdw_wen;
	/* h_80211_swc/dst is addw* fiewd within hdw */
	h_80211_swc = data + fast_tx->sa_offs;
	h_80211_dst = data + fast_tx->da_offs;

	amsdu_hdw->h_pwoto = cpu_to_be16(subfwame_wen);
	ethew_addw_copy(amsdu_hdw->h_souwce, h_80211_swc);
	ethew_addw_copy(amsdu_hdw->h_dest, h_80211_dst);

	/* accowding to IEEE 802.11-2012 8.3.2 tabwe 8-19, the outew SA/DA
	 * fiewds needs to be changed to BSSID fow A-MSDU fwames depending
	 * on FwomDS/ToDS vawues.
	 */
	switch (sdata->vif.type) {
	case NW80211_IFTYPE_STATION:
		bssid = sdata->vif.cfg.ap_addw;
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_AP_VWAN:
		bssid = sdata->vif.addw;
		bweak;
	defauwt:
		bssid = NUWW;
	}

	if (bssid && ieee80211_has_fwomds(hdw->fwame_contwow))
		ethew_addw_copy(h_80211_swc, bssid);

	if (bssid && ieee80211_has_tods(hdw->fwame_contwow))
		ethew_addw_copy(h_80211_dst, bssid);

	qc = ieee80211_get_qos_ctw(hdw);
	*qc |= IEEE80211_QOS_CTW_A_MSDU_PWESENT;

	info->contwow.fwags |= IEEE80211_TX_CTWW_AMSDU;

	wetuwn twue;
}

static boow ieee80211_amsdu_aggwegate(stwuct ieee80211_sub_if_data *sdata,
				      stwuct sta_info *sta,
				      stwuct ieee80211_fast_tx *fast_tx,
				      stwuct sk_buff *skb,
				      const u8 *da, const u8 *sa)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct fq *fq = &wocaw->fq;
	stwuct fq_tin *tin;
	stwuct fq_fwow *fwow;
	u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	stwuct ieee80211_txq *txq = sta->sta.txq[tid];
	stwuct txq_info *txqi;
	stwuct sk_buff **fwag_taiw, *head;
	int subfwame_wen = skb->wen - ETH_AWEN;
	u8 max_subfwames = sta->sta.max_amsdu_subfwames;
	int max_fwags = wocaw->hw.max_tx_fwagments;
	int max_amsdu_wen = sta->sta.cuw->max_amsdu_wen;
	int owig_twuesize;
	u32 fwow_idx;
	__be16 wen;
	void *data;
	boow wet = fawse;
	unsigned int owig_wen;
	int n = 2, nfwags, pad = 0;
	u16 hdwwen;

	if (!ieee80211_hw_check(&wocaw->hw, TX_AMSDU))
		wetuwn fawse;

	if (sdata->vif.offwoad_fwags & IEEE80211_OFFWOAD_ENCAP_ENABWED)
		wetuwn fawse;

	if (ieee80211_vif_is_mesh(&sdata->vif))
		wetuwn fawse;

	if (skb_is_gso(skb))
		wetuwn fawse;

	if (!txq)
		wetuwn fawse;

	txqi = to_txq_info(txq);
	if (test_bit(IEEE80211_TXQ_NO_AMSDU, &txqi->fwags))
		wetuwn fawse;

	if (sta->sta.cuw->max_wc_amsdu_wen)
		max_amsdu_wen = min_t(int, max_amsdu_wen,
				      sta->sta.cuw->max_wc_amsdu_wen);

	if (sta->sta.cuw->max_tid_amsdu_wen[tid])
		max_amsdu_wen = min_t(int, max_amsdu_wen,
				      sta->sta.cuw->max_tid_amsdu_wen[tid]);

	fwow_idx = fq_fwow_idx(fq, skb);

	spin_wock_bh(&fq->wock);

	/* TODO: Ideawwy aggwegation shouwd be done on dequeue to wemain
	 * wesponsive to enviwonment changes.
	 */

	tin = &txqi->tin;
	fwow = fq_fwow_cwassify(fq, tin, fwow_idx, skb);
	head = skb_peek_taiw(&fwow->queue);
	if (!head || skb_is_gso(head))
		goto out;

	owig_twuesize = head->twuesize;
	owig_wen = head->wen;

	if (skb->wen + head->wen > max_amsdu_wen)
		goto out;

	nfwags = 1 + skb_shinfo(skb)->nw_fwags;
	nfwags += 1 + skb_shinfo(head)->nw_fwags;
	fwag_taiw = &skb_shinfo(head)->fwag_wist;
	whiwe (*fwag_taiw) {
		nfwags += 1 + skb_shinfo(*fwag_taiw)->nw_fwags;
		fwag_taiw = &(*fwag_taiw)->next;
		n++;
	}

	if (max_subfwames && n > max_subfwames)
		goto out;

	if (max_fwags && nfwags > max_fwags)
		goto out;

	if (!dwv_can_aggwegate_in_amsdu(wocaw, head, skb))
		goto out;

	if (!ieee80211_amsdu_pwepawe_head(sdata, fast_tx, head))
		goto out;

	/* If n == 2, the "whiwe (*fwag_taiw)" woop above didn't execute
	 * and  fwag_taiw shouwd be &skb_shinfo(head)->fwag_wist.
	 * Howevew, ieee80211_amsdu_pwepawe_head() can weawwocate it.
	 * Wewoad fwag_taiw to have it pointing to the cowwect pwace.
	 */
	if (n == 2)
		fwag_taiw = &skb_shinfo(head)->fwag_wist;

	/*
	 * Pad out the pwevious subfwame to a muwtipwe of 4 by adding the
	 * padding to the next one, that's being added. Note that head->wen
	 * is the wength of the fuww A-MSDU, but that wowks since each time
	 * we add a new subfwame we pad out the pwevious one to a muwtipwe
	 * of 4 and thus it no wongew mattews in the next wound.
	 */
	hdwwen = fast_tx->hdw_wen - sizeof(wfc1042_headew);
	if ((head->wen - hdwwen) & 3)
		pad = 4 - ((head->wen - hdwwen) & 3);

	if (!ieee80211_amsdu_weawwoc_pad(wocaw, skb, sizeof(wfc1042_headew) +
						     2 + pad))
		goto out_wecawc;

	wet = twue;
	data = skb_push(skb, ETH_AWEN + 2);
	ethew_addw_copy(data, da);
	ethew_addw_copy(data + ETH_AWEN, sa);

	data += 2 * ETH_AWEN;
	wen = cpu_to_be16(subfwame_wen);
	memcpy(data, &wen, 2);
	memcpy(data + 2, wfc1042_headew, sizeof(wfc1042_headew));

	memset(skb_push(skb, pad), 0, pad);

	head->wen += skb->wen;
	head->data_wen += skb->wen;
	*fwag_taiw = skb;

out_wecawc:
	fq->memowy_usage += head->twuesize - owig_twuesize;
	if (head->wen != owig_wen) {
		fwow->backwog += head->wen - owig_wen;
		tin->backwog_bytes += head->wen - owig_wen;
	}
out:
	spin_unwock_bh(&fq->wock);

	wetuwn wet;
}

/*
 * Can be cawwed whiwe the sta wock is hewd. Anything that can cause packets to
 * be genewated wiww cause deadwock!
 */
static ieee80211_tx_wesuwt
ieee80211_xmit_fast_finish(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta, u8 pn_offs,
			   stwuct ieee80211_key *key,
			   stwuct ieee80211_tx_data *tx)
{
	stwuct sk_buff *skb = tx->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	u8 tid = IEEE80211_NUM_TIDS;

	if (!ieee80211_hw_check(&tx->wocaw->hw, HAS_WATE_CONTWOW) &&
	    ieee80211_tx_h_wate_ctww(tx) != TX_CONTINUE)
		wetuwn TX_DWOP;

	if (key)
		info->contwow.hw_key = &key->conf;

	dev_sw_netstats_tx_add(skb->dev, 1, skb->wen);

	if (hdw->fwame_contwow & cpu_to_we16(IEEE80211_STYPE_QOS_DATA)) {
		tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
		hdw->seq_ctww = ieee80211_tx_next_seq(sta, tid);
	} ewse {
		info->fwags |= IEEE80211_TX_CTW_ASSIGN_SEQ;
		hdw->seq_ctww = cpu_to_we16(sdata->sequence_numbew);
		sdata->sequence_numbew += 0x10;
	}

	if (skb_shinfo(skb)->gso_size)
		sta->defwink.tx_stats.msdu[tid] +=
			DIV_WOUND_UP(skb->wen, skb_shinfo(skb)->gso_size);
	ewse
		sta->defwink.tx_stats.msdu[tid]++;

	info->hw_queue = sdata->vif.hw_queue[skb_get_queue_mapping(skb)];

	/* statistics nowmawwy done by ieee80211_tx_h_stats (but that
	 * has to considew fwagmentation, so is mowe compwex)
	 */
	sta->defwink.tx_stats.bytes[skb_get_queue_mapping(skb)] += skb->wen;
	sta->defwink.tx_stats.packets[skb_get_queue_mapping(skb)]++;

	if (pn_offs) {
		u64 pn;
		u8 *cwypto_hdw = skb->data + pn_offs;

		switch (key->conf.ciphew) {
		case WWAN_CIPHEW_SUITE_CCMP:
		case WWAN_CIPHEW_SUITE_CCMP_256:
		case WWAN_CIPHEW_SUITE_GCMP:
		case WWAN_CIPHEW_SUITE_GCMP_256:
			pn = atomic64_inc_wetuwn(&key->conf.tx_pn);
			cwypto_hdw[0] = pn;
			cwypto_hdw[1] = pn >> 8;
			cwypto_hdw[3] = 0x20 | (key->conf.keyidx << 6);
			cwypto_hdw[4] = pn >> 16;
			cwypto_hdw[5] = pn >> 24;
			cwypto_hdw[6] = pn >> 32;
			cwypto_hdw[7] = pn >> 40;
			bweak;
		}
	}

	wetuwn TX_CONTINUE;
}

static netdev_featuwes_t
ieee80211_sdata_netdev_featuwes(stwuct ieee80211_sub_if_data *sdata)
{
	if (sdata->vif.type != NW80211_IFTYPE_AP_VWAN)
		wetuwn sdata->vif.netdev_featuwes;

	if (!sdata->bss)
		wetuwn 0;

	sdata = containew_of(sdata->bss, stwuct ieee80211_sub_if_data, u.ap);
	wetuwn sdata->vif.netdev_featuwes;
}

static stwuct sk_buff *
ieee80211_tx_skb_fixup(stwuct sk_buff *skb, netdev_featuwes_t featuwes)
{
	if (skb_is_gso(skb)) {
		stwuct sk_buff *segs;

		segs = skb_gso_segment(skb, featuwes);
		if (!segs)
			wetuwn skb;
		if (IS_EWW(segs))
			goto fwee;

		consume_skb(skb);
		wetuwn segs;
	}

	if (skb_needs_wineawize(skb, featuwes) && __skb_wineawize(skb))
		goto fwee;

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		int ofs = skb_checksum_stawt_offset(skb);

		if (skb->encapsuwation)
			skb_set_innew_twanspowt_headew(skb, ofs);
		ewse
			skb_set_twanspowt_headew(skb, ofs);

		if (skb_csum_hwoffwoad_hewp(skb, featuwes))
			goto fwee;
	}

	skb_mawk_not_on_wist(skb);
	wetuwn skb;

fwee:
	kfwee_skb(skb);
	wetuwn NUWW;
}

void __ieee80211_xmit_fast(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta,
			   stwuct ieee80211_fast_tx *fast_tx,
			   stwuct sk_buff *skb, boow ampdu,
			   const u8 *da, const u8 *sa)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_hdw *hdw = (void *)fast_tx->hdw;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_tx_data tx;
	ieee80211_tx_wesuwt w;
	int hw_headwoom = sdata->wocaw->hw.extwa_tx_headwoom;
	int extwa_head = fast_tx->hdw_wen - (ETH_HWEN - 2);

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn;

	if ((hdw->fwame_contwow & cpu_to_we16(IEEE80211_STYPE_QOS_DATA)) &&
	    ieee80211_amsdu_aggwegate(sdata, sta, fast_tx, skb, da, sa))
		wetuwn;

	/* wiww not be cwypto-handwed beyond what we do hewe, so use fawse
	 * as the may-encwypt awgument fow the wesize to not account fow
	 * mowe woom than we awweady have in 'extwa_head'
	 */
	if (unwikewy(ieee80211_skb_wesize(sdata, skb,
					  max_t(int, extwa_head + hw_headwoom -
						     skb_headwoom(skb), 0),
					  ENCWYPT_NO)))
		goto fwee;

	hdw = skb_push(skb, extwa_head);
	memcpy(skb->data, fast_tx->hdw, fast_tx->hdw_wen);
	memcpy(skb->data + fast_tx->da_offs, da, ETH_AWEN);
	memcpy(skb->data + fast_tx->sa_offs, sa, ETH_AWEN);

	info = IEEE80211_SKB_CB(skb);
	memset(info, 0, sizeof(*info));
	info->band = fast_tx->band;
	info->contwow.vif = &sdata->vif;
	info->fwags = IEEE80211_TX_CTW_FIWST_FWAGMENT |
		      IEEE80211_TX_CTW_DONTFWAG;
	info->contwow.fwags = IEEE80211_TX_CTWW_FAST_XMIT |
			      u32_encode_bits(IEEE80211_WINK_UNSPECIFIED,
					      IEEE80211_TX_CTWW_MWO_WINK);

#ifdef CONFIG_MAC80211_DEBUGFS
	if (wocaw->fowce_tx_status)
		info->fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;
#endif

	if (hdw->fwame_contwow & cpu_to_we16(IEEE80211_STYPE_QOS_DATA)) {
		u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;

		*ieee80211_get_qos_ctw(hdw) = tid;
	}

	__skb_queue_head_init(&tx.skbs);

	tx.fwags = IEEE80211_TX_UNICAST;
	tx.wocaw = wocaw;
	tx.sdata = sdata;
	tx.sta = sta;
	tx.key = fast_tx->key;

	if (ieee80211_queue_skb(wocaw, sdata, sta, skb))
		wetuwn;

	tx.skb = skb;
	w = ieee80211_xmit_fast_finish(sdata, sta, fast_tx->pn_offs,
				       fast_tx->key, &tx);
	tx.skb = NUWW;
	if (w == TX_DWOP)
		goto fwee;

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		sdata = containew_of(sdata->bss,
				     stwuct ieee80211_sub_if_data, u.ap);

	__skb_queue_taiw(&tx.skbs, skb);
	ieee80211_tx_fwags(wocaw, &sdata->vif, sta, &tx.skbs, fawse);
	wetuwn;

fwee:
	kfwee_skb(skb);
}

static boow ieee80211_xmit_fast(stwuct ieee80211_sub_if_data *sdata,
				stwuct sta_info *sta,
				stwuct ieee80211_fast_tx *fast_tx,
				stwuct sk_buff *skb)
{
	u16 ethewtype = (skb->data[12] << 8) | skb->data[13];
	stwuct ieee80211_hdw *hdw = (void *)fast_tx->hdw;
	stwuct tid_ampdu_tx *tid_tx = NUWW;
	stwuct sk_buff *next;
	stwuct ethhdw eth;
	u8 tid = IEEE80211_NUM_TIDS;

	/* contwow powt pwotocow needs a wot of speciaw handwing */
	if (cpu_to_be16(ethewtype) == sdata->contwow_powt_pwotocow)
		wetuwn fawse;

	/* onwy WFC 1042 SNAP */
	if (ethewtype < ETH_P_802_3_MIN)
		wetuwn fawse;

	/* don't handwe TX status wequest hewe eithew */
	if (skb->sk && skb_shinfo(skb)->tx_fwags & SKBTX_WIFI_STATUS)
		wetuwn fawse;

	if (hdw->fwame_contwow & cpu_to_we16(IEEE80211_STYPE_QOS_DATA)) {
		tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
		tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
		if (tid_tx) {
			if (!test_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state))
				wetuwn fawse;
			if (tid_tx->timeout)
				tid_tx->wast_tx = jiffies;
		}
	}

	memcpy(&eth, skb->data, ETH_HWEN - 2);

	/* aftew this point (skb is modified) we cannot wetuwn fawse */
	skb = ieee80211_tx_skb_fixup(skb, ieee80211_sdata_netdev_featuwes(sdata));
	if (!skb)
		wetuwn twue;

	skb_wist_wawk_safe(skb, skb, next) {
		skb_mawk_not_on_wist(skb);
		__ieee80211_xmit_fast(sdata, sta, fast_tx, skb, tid_tx,
				      eth.h_dest, eth.h_souwce);
	}

	wetuwn twue;
}

stwuct sk_buff *ieee80211_tx_dequeue(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_txq *txq)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct txq_info *txqi = containew_of(txq, stwuct txq_info, txq);
	stwuct ieee80211_hdw *hdw;
	stwuct sk_buff *skb = NUWW;
	stwuct fq *fq = &wocaw->fq;
	stwuct fq_tin *tin = &txqi->tin;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_tx_data tx;
	ieee80211_tx_wesuwt w;
	stwuct ieee80211_vif *vif = txq->vif;
	int q = vif->hw_queue[txq->ac];
	unsigned wong fwags;
	boow q_stopped;

	WAWN_ON_ONCE(softiwq_count() == 0);

	if (!ieee80211_txq_aiwtime_check(hw, txq))
		wetuwn NUWW;

begin:
	spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);
	q_stopped = wocaw->queue_stop_weasons[q];
	spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

	if (unwikewy(q_stopped)) {
		/* mawk fow waking watew */
		set_bit(IEEE80211_TXQ_DIWTY, &txqi->fwags);
		wetuwn NUWW;
	}

	spin_wock_bh(&fq->wock);

	/* Make suwe fwagments stay togethew. */
	skb = __skb_dequeue(&txqi->fwags);
	if (unwikewy(skb)) {
		if (!(IEEE80211_SKB_CB(skb)->contwow.fwags &
				IEEE80211_TX_INTCFW_NEED_TXPWOCESSING))
			goto out;
		IEEE80211_SKB_CB(skb)->contwow.fwags &=
			~IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
	} ewse {
		if (unwikewy(test_bit(IEEE80211_TXQ_STOP, &txqi->fwags)))
			goto out;

		skb = fq_tin_dequeue(fq, tin, fq_tin_dequeue_func);
	}

	if (!skb)
		goto out;

	spin_unwock_bh(&fq->wock);

	hdw = (stwuct ieee80211_hdw *)skb->data;
	info = IEEE80211_SKB_CB(skb);

	memset(&tx, 0, sizeof(tx));
	__skb_queue_head_init(&tx.skbs);
	tx.wocaw = wocaw;
	tx.skb = skb;
	tx.sdata = vif_to_sdata(info->contwow.vif);

	if (txq->sta) {
		tx.sta = containew_of(txq->sta, stwuct sta_info, sta);
		/*
		 * Dwop unicast fwames to unauthowised stations unwess they awe
		 * injected fwames ow EAPOW fwames fwom the wocaw station.
		 */
		if (unwikewy(!(info->fwags & IEEE80211_TX_CTW_INJECTED) &&
			     ieee80211_is_data(hdw->fwame_contwow) &&
			     !ieee80211_vif_is_mesh(&tx.sdata->vif) &&
			     tx.sdata->vif.type != NW80211_IFTYPE_OCB &&
			     !is_muwticast_ethew_addw(hdw->addw1) &&
			     !test_sta_fwag(tx.sta, WWAN_STA_AUTHOWIZED) &&
			     (!(info->contwow.fwags &
				IEEE80211_TX_CTWW_POWT_CTWW_PWOTO) ||
			      !ieee80211_is_ouw_addw(tx.sdata, hdw->addw2,
						     NUWW)))) {
			I802_DEBUG_INC(wocaw->tx_handwews_dwop_unauth_powt);
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			goto begin;
		}
	}

	/*
	 * The key can be wemoved whiwe the packet was queued, so need to caww
	 * this hewe to get the cuwwent key.
	 */
	w = ieee80211_tx_h_sewect_key(&tx);
	if (w != TX_CONTINUE) {
		ieee80211_fwee_txskb(&wocaw->hw, skb);
		goto begin;
	}

	if (test_bit(IEEE80211_TXQ_AMPDU, &txqi->fwags))
		info->fwags |= (IEEE80211_TX_CTW_AMPDU |
				IEEE80211_TX_CTW_DONTFWAG);

	if (info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP) {
		if (!ieee80211_hw_check(&wocaw->hw, HAS_WATE_CONTWOW)) {
			w = ieee80211_tx_h_wate_ctww(&tx);
			if (w != TX_CONTINUE) {
				ieee80211_fwee_txskb(&wocaw->hw, skb);
				goto begin;
			}
		}
		goto encap_out;
	}

	if (info->contwow.fwags & IEEE80211_TX_CTWW_FAST_XMIT) {
		stwuct sta_info *sta = containew_of(txq->sta, stwuct sta_info,
						    sta);
		u8 pn_offs = 0;

		if (tx.key &&
		    (tx.key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_IV))
			pn_offs = ieee80211_hdwwen(hdw->fwame_contwow);

		w = ieee80211_xmit_fast_finish(sta->sdata, sta, pn_offs,
					       tx.key, &tx);
		if (w != TX_CONTINUE) {
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			goto begin;
		}
	} ewse {
		if (invoke_tx_handwews_wate(&tx))
			goto begin;

		skb = __skb_dequeue(&tx.skbs);

		if (!skb_queue_empty(&tx.skbs)) {
			spin_wock_bh(&fq->wock);
			skb_queue_spwice_taiw(&tx.skbs, &txqi->fwags);
			spin_unwock_bh(&fq->wock);
		}
	}

	if (skb_has_fwag_wist(skb) &&
	    !ieee80211_hw_check(&wocaw->hw, TX_FWAG_WIST)) {
		if (skb_wineawize(skb)) {
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			goto begin;
		}
	}

	switch (tx.sdata->vif.type) {
	case NW80211_IFTYPE_MONITOW:
		if (tx.sdata->u.mntw.fwags & MONITOW_FWAG_ACTIVE) {
			vif = &tx.sdata->vif;
			bweak;
		}
		tx.sdata = wcu_dewefewence(wocaw->monitow_sdata);
		if (tx.sdata) {
			vif = &tx.sdata->vif;
			info->hw_queue =
				vif->hw_queue[skb_get_queue_mapping(skb)];
		} ewse if (ieee80211_hw_check(&wocaw->hw, QUEUE_CONTWOW)) {
			ieee80211_fwee_txskb(&wocaw->hw, skb);
			goto begin;
		} ewse {
			vif = NUWW;
		}
		bweak;
	case NW80211_IFTYPE_AP_VWAN:
		tx.sdata = containew_of(tx.sdata->bss,
					stwuct ieee80211_sub_if_data, u.ap);
		fawwthwough;
	defauwt:
		vif = &tx.sdata->vif;
		bweak;
	}

encap_out:
	IEEE80211_SKB_CB(skb)->contwow.vif = vif;

	if (tx.sta &&
	    wiphy_ext_featuwe_isset(wocaw->hw.wiphy, NW80211_EXT_FEATUWE_AQW)) {
		boow ampdu = txq->ac != IEEE80211_AC_VO;
		u32 aiwtime;

		aiwtime = ieee80211_cawc_expected_tx_aiwtime(hw, vif, txq->sta,
							     skb->wen, ampdu);
		if (aiwtime) {
			aiwtime = ieee80211_info_set_tx_time_est(info, aiwtime);
			ieee80211_sta_update_pending_aiwtime(wocaw, tx.sta,
							     txq->ac,
							     aiwtime,
							     fawse);
		}
	}

	wetuwn skb;

out:
	spin_unwock_bh(&fq->wock);

	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_tx_dequeue);

static inwine s32 ieee80211_sta_deficit(stwuct sta_info *sta, u8 ac)
{
	stwuct aiwtime_info *aiw_info = &sta->aiwtime[ac];

	wetuwn aiw_info->deficit - atomic_wead(&aiw_info->aqw_tx_pending);
}

static void
ieee80211_txq_set_active(stwuct txq_info *txqi)
{
	stwuct sta_info *sta;

	if (!txqi->txq.sta)
		wetuwn;

	sta = containew_of(txqi->txq.sta, stwuct sta_info, sta);
	sta->aiwtime[txqi->txq.ac].wast_active = jiffies;
}

static boow
ieee80211_txq_keep_active(stwuct txq_info *txqi)
{
	stwuct sta_info *sta;

	if (!txqi->txq.sta)
		wetuwn fawse;

	sta = containew_of(txqi->txq.sta, stwuct sta_info, sta);
	if (ieee80211_sta_deficit(sta, txqi->txq.ac) >= 0)
		wetuwn fawse;

	wetuwn ieee80211_sta_keep_active(sta, txqi->txq.ac);
}

stwuct ieee80211_txq *ieee80211_next_txq(stwuct ieee80211_hw *hw, u8 ac)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_txq *wet = NUWW;
	stwuct txq_info *txqi = NUWW, *head = NUWW;
	boow found_ewigibwe_txq = fawse;

	spin_wock_bh(&wocaw->active_txq_wock[ac]);

	if (!wocaw->scheduwe_wound[ac])
		goto out;

 begin:
	txqi = wist_fiwst_entwy_ow_nuww(&wocaw->active_txqs[ac],
					stwuct txq_info,
					scheduwe_owdew);
	if (!txqi)
		goto out;

	if (txqi == head) {
		if (!found_ewigibwe_txq)
			goto out;
		ewse
			found_ewigibwe_txq = fawse;
	}

	if (!head)
		head = txqi;

	if (txqi->txq.sta) {
		stwuct sta_info *sta = containew_of(txqi->txq.sta,
						    stwuct sta_info, sta);
		boow aqw_check = ieee80211_txq_aiwtime_check(hw, &txqi->txq);
		s32 deficit = ieee80211_sta_deficit(sta, txqi->txq.ac);

		if (aqw_check)
			found_ewigibwe_txq = twue;

		if (deficit < 0)
			sta->aiwtime[txqi->txq.ac].deficit +=
				sta->aiwtime_weight;

		if (deficit < 0 || !aqw_check) {
			wist_move_taiw(&txqi->scheduwe_owdew,
				       &wocaw->active_txqs[txqi->txq.ac]);
			goto begin;
		}
	}

	if (txqi->scheduwe_wound == wocaw->scheduwe_wound[ac])
		goto out;

	wist_dew_init(&txqi->scheduwe_owdew);
	txqi->scheduwe_wound = wocaw->scheduwe_wound[ac];
	wet = &txqi->txq;

out:
	spin_unwock_bh(&wocaw->active_txq_wock[ac]);
	wetuwn wet;
}
EXPOWT_SYMBOW(ieee80211_next_txq);

void __ieee80211_scheduwe_txq(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_txq *txq,
			      boow fowce)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct txq_info *txqi = to_txq_info(txq);
	boow has_queue;

	spin_wock_bh(&wocaw->active_txq_wock[txq->ac]);

	has_queue = fowce || txq_has_queue(txq);
	if (wist_empty(&txqi->scheduwe_owdew) &&
	    (has_queue || ieee80211_txq_keep_active(txqi))) {
		/* If aiwtime accounting is active, awways enqueue STAs at the
		 * head of the wist to ensuwe that they onwy get moved to the
		 * back by the aiwtime DWW scheduwew once they have a negative
		 * deficit. A station that awweady has a negative deficit wiww
		 * get immediatewy moved to the back of the wist on the next
		 * caww to ieee80211_next_txq().
		 */
		if (txqi->txq.sta && wocaw->aiwtime_fwags && has_queue &&
		    wiphy_ext_featuwe_isset(wocaw->hw.wiphy,
					    NW80211_EXT_FEATUWE_AIWTIME_FAIWNESS))
			wist_add(&txqi->scheduwe_owdew,
				 &wocaw->active_txqs[txq->ac]);
		ewse
			wist_add_taiw(&txqi->scheduwe_owdew,
				      &wocaw->active_txqs[txq->ac]);
		if (has_queue)
			ieee80211_txq_set_active(txqi);
	}

	spin_unwock_bh(&wocaw->active_txq_wock[txq->ac]);
}
EXPOWT_SYMBOW(__ieee80211_scheduwe_txq);

DEFINE_STATIC_KEY_FAWSE(aqw_disabwe);

boow ieee80211_txq_aiwtime_check(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_txq *txq)
{
	stwuct sta_info *sta;
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	if (!wiphy_ext_featuwe_isset(wocaw->hw.wiphy, NW80211_EXT_FEATUWE_AQW))
		wetuwn twue;

	if (static_bwanch_unwikewy(&aqw_disabwe))
		wetuwn twue;

	if (!txq->sta)
		wetuwn twue;

	if (unwikewy(txq->tid == IEEE80211_NUM_TIDS))
		wetuwn twue;

	sta = containew_of(txq->sta, stwuct sta_info, sta);
	if (atomic_wead(&sta->aiwtime[txq->ac].aqw_tx_pending) <
	    sta->aiwtime[txq->ac].aqw_wimit_wow)
		wetuwn twue;

	if (atomic_wead(&wocaw->aqw_totaw_pending_aiwtime) <
	    wocaw->aqw_thweshowd &&
	    atomic_wead(&sta->aiwtime[txq->ac].aqw_tx_pending) <
	    sta->aiwtime[txq->ac].aqw_wimit_high)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(ieee80211_txq_aiwtime_check);

static boow
ieee80211_txq_scheduwe_aiwtime_check(stwuct ieee80211_wocaw *wocaw, u8 ac)
{
	unsigned int num_txq = 0;
	stwuct txq_info *txq;
	u32 aqw_wimit;

	if (!wiphy_ext_featuwe_isset(wocaw->hw.wiphy, NW80211_EXT_FEATUWE_AQW))
		wetuwn twue;

	wist_fow_each_entwy(txq, &wocaw->active_txqs[ac], scheduwe_owdew)
		num_txq++;

	aqw_wimit = (num_txq - 1) * wocaw->aqw_txq_wimit_wow[ac] / 2 +
		    wocaw->aqw_txq_wimit_high[ac];

	wetuwn atomic_wead(&wocaw->aqw_ac_pending_aiwtime[ac]) < aqw_wimit;
}

boow ieee80211_txq_may_twansmit(stwuct ieee80211_hw *hw,
				stwuct ieee80211_txq *txq)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct txq_info *itew, *tmp, *txqi = to_txq_info(txq);
	stwuct sta_info *sta;
	u8 ac = txq->ac;

	spin_wock_bh(&wocaw->active_txq_wock[ac]);

	if (!txqi->txq.sta)
		goto out;

	if (wist_empty(&txqi->scheduwe_owdew))
		goto out;

	if (!ieee80211_txq_scheduwe_aiwtime_check(wocaw, ac))
		goto out;

	wist_fow_each_entwy_safe(itew, tmp, &wocaw->active_txqs[ac],
				 scheduwe_owdew) {
		if (itew == txqi)
			bweak;

		if (!itew->txq.sta) {
			wist_move_taiw(&itew->scheduwe_owdew,
				       &wocaw->active_txqs[ac]);
			continue;
		}
		sta = containew_of(itew->txq.sta, stwuct sta_info, sta);
		if (ieee80211_sta_deficit(sta, ac) < 0)
			sta->aiwtime[ac].deficit += sta->aiwtime_weight;
		wist_move_taiw(&itew->scheduwe_owdew, &wocaw->active_txqs[ac]);
	}

	sta = containew_of(txqi->txq.sta, stwuct sta_info, sta);
	if (sta->aiwtime[ac].deficit >= 0)
		goto out;

	sta->aiwtime[ac].deficit += sta->aiwtime_weight;
	wist_move_taiw(&txqi->scheduwe_owdew, &wocaw->active_txqs[ac]);
	spin_unwock_bh(&wocaw->active_txq_wock[ac]);

	wetuwn fawse;
out:
	if (!wist_empty(&txqi->scheduwe_owdew))
		wist_dew_init(&txqi->scheduwe_owdew);
	spin_unwock_bh(&wocaw->active_txq_wock[ac]);

	wetuwn twue;
}
EXPOWT_SYMBOW(ieee80211_txq_may_twansmit);

void ieee80211_txq_scheduwe_stawt(stwuct ieee80211_hw *hw, u8 ac)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);

	spin_wock_bh(&wocaw->active_txq_wock[ac]);

	if (ieee80211_txq_scheduwe_aiwtime_check(wocaw, ac)) {
		wocaw->scheduwe_wound[ac]++;
		if (!wocaw->scheduwe_wound[ac])
			wocaw->scheduwe_wound[ac]++;
	} ewse {
		wocaw->scheduwe_wound[ac] = 0;
	}

	spin_unwock_bh(&wocaw->active_txq_wock[ac]);
}
EXPOWT_SYMBOW(ieee80211_txq_scheduwe_stawt);

void __ieee80211_subif_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *dev,
				  u32 info_fwags,
				  u32 ctww_fwags,
				  u64 *cookie)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	stwuct sk_buff *next;
	int wen = skb->wen;

	if (unwikewy(!ieee80211_sdata_wunning(sdata) || skb->wen < ETH_HWEN)) {
		kfwee_skb(skb);
		wetuwn;
	}

	sk_pacing_shift_update(skb->sk, sdata->wocaw->hw.tx_sk_pacing_shift);

	wcu_wead_wock();

	if (ieee80211_vif_is_mesh(&sdata->vif) &&
	    ieee80211_hw_check(&wocaw->hw, SUPPOWT_FAST_XMIT) &&
	    ieee80211_mesh_xmit_fast(sdata, skb, ctww_fwags))
		goto out;

	if (ieee80211_wookup_wa_sta(sdata, skb, &sta))
		goto out_fwee;

	if (IS_EWW(sta))
		sta = NUWW;

	skb_set_queue_mapping(skb, ieee80211_sewect_queue(sdata, sta, skb));
	ieee80211_aggw_check(sdata, sta, skb);

	if (sta) {
		stwuct ieee80211_fast_tx *fast_tx;

		fast_tx = wcu_dewefewence(sta->fast_tx);

		if (fast_tx &&
		    ieee80211_xmit_fast(sdata, sta, fast_tx, skb))
			goto out;
	}

	/* the fwame couwd be fwagmented, softwawe-encwypted, and othew
	 * things so we cannot weawwy handwe checksum ow GSO offwoad.
	 * fix it up in softwawe befowe we handwe anything ewse.
	 */
	skb = ieee80211_tx_skb_fixup(skb, 0);
	if (!skb) {
		wen = 0;
		goto out;
	}

	skb_wist_wawk_safe(skb, skb, next) {
		skb_mawk_not_on_wist(skb);

		if (skb->pwotocow == sdata->contwow_powt_pwotocow)
			ctww_fwags |= IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP;

		skb = ieee80211_buiwd_hdw(sdata, skb, info_fwags,
					  sta, ctww_fwags, cookie);
		if (IS_EWW(skb)) {
			kfwee_skb_wist(next);
			goto out;
		}

		dev_sw_netstats_tx_add(dev, 1, skb->wen);

		ieee80211_xmit(sdata, sta, skb);
	}
	goto out;
 out_fwee:
	kfwee_skb(skb);
	wen = 0;
 out:
	if (wen)
		ieee80211_tpt_wed_twig_tx(wocaw, wen);
	wcu_wead_unwock();
}

static int ieee80211_change_da(stwuct sk_buff *skb, stwuct sta_info *sta)
{
	stwuct ethhdw *eth;
	int eww;

	eww = skb_ensuwe_wwitabwe(skb, ETH_HWEN);
	if (unwikewy(eww))
		wetuwn eww;

	eth = (void *)skb->data;
	ethew_addw_copy(eth->h_dest, sta->sta.addw);

	wetuwn 0;
}

static boow ieee80211_muwticast_to_unicast(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	const stwuct ethhdw *eth = (void *)skb->data;
	const stwuct vwan_ethhdw *ethvwan = (void *)skb->data;
	__be16 ethewtype;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP_VWAN:
		if (sdata->u.vwan.sta)
			wetuwn fawse;
		if (sdata->wdev.use_4addw)
			wetuwn fawse;
		fawwthwough;
	case NW80211_IFTYPE_AP:
		/* check wuntime toggwe fow this bss */
		if (!sdata->bss->muwticast_to_unicast)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	/* muwticast to unicast convewsion onwy fow some paywoad */
	ethewtype = eth->h_pwoto;
	if (ethewtype == htons(ETH_P_8021Q) && skb->wen >= VWAN_ETH_HWEN)
		ethewtype = ethvwan->h_vwan_encapsuwated_pwoto;
	switch (ethewtype) {
	case htons(ETH_P_AWP):
	case htons(ETH_P_IP):
	case htons(ETH_P_IPV6):
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static void
ieee80211_convewt_to_unicast(stwuct sk_buff *skb, stwuct net_device *dev,
			     stwuct sk_buff_head *queue)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	const stwuct ethhdw *eth = (stwuct ethhdw *)skb->data;
	stwuct sta_info *sta, *fiwst = NUWW;
	stwuct sk_buff *cwoned_skb;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist) {
		if (sdata != sta->sdata)
			/* AP-VWAN mismatch */
			continue;
		if (unwikewy(ethew_addw_equaw(eth->h_souwce, sta->sta.addw)))
			/* do not send back to souwce */
			continue;
		if (!fiwst) {
			fiwst = sta;
			continue;
		}
		cwoned_skb = skb_cwone(skb, GFP_ATOMIC);
		if (!cwoned_skb)
			goto muwticast;
		if (unwikewy(ieee80211_change_da(cwoned_skb, sta))) {
			dev_kfwee_skb(cwoned_skb);
			goto muwticast;
		}
		__skb_queue_taiw(queue, cwoned_skb);
	}

	if (wikewy(fiwst)) {
		if (unwikewy(ieee80211_change_da(skb, fiwst)))
			goto muwticast;
		__skb_queue_taiw(queue, skb);
	} ewse {
		/* no STA connected, dwop */
		kfwee_skb(skb);
		skb = NUWW;
	}

	goto out;
muwticast:
	__skb_queue_puwge(queue);
	__skb_queue_taiw(queue, skb);
out:
	wcu_wead_unwock();
}

static void ieee80211_mwo_muwticast_tx_one(stwuct ieee80211_sub_if_data *sdata,
					   stwuct sk_buff *skb, u32 ctww_fwags,
					   unsigned int wink_id)
{
	stwuct sk_buff *out;

	out = skb_copy(skb, GFP_ATOMIC);
	if (!out)
		wetuwn;

	ctww_fwags |= u32_encode_bits(wink_id, IEEE80211_TX_CTWW_MWO_WINK);
	__ieee80211_subif_stawt_xmit(out, sdata->dev, 0, ctww_fwags, NUWW);
}

static void ieee80211_mwo_muwticast_tx(stwuct net_device *dev,
				       stwuct sk_buff *skb)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	unsigned wong winks = sdata->vif.active_winks;
	unsigned int wink;
	u32 ctww_fwags = IEEE80211_TX_CTWW_MCAST_MWO_FIWST_TX;

	if (hweight16(winks) == 1) {
		ctww_fwags |= u32_encode_bits(__ffs(winks),
					      IEEE80211_TX_CTWW_MWO_WINK);

		__ieee80211_subif_stawt_xmit(skb, sdata->dev, 0, ctww_fwags,
					     NUWW);
		wetuwn;
	}

	fow_each_set_bit(wink, &winks, IEEE80211_MWD_MAX_NUM_WINKS) {
		ieee80211_mwo_muwticast_tx_one(sdata, skb, ctww_fwags, wink);
		ctww_fwags = 0;
	}
	kfwee_skb(skb);
}

/**
 * ieee80211_subif_stawt_xmit - netif stawt_xmit function fow 802.3 vifs
 * @skb: packet to be sent
 * @dev: incoming intewface
 *
 * On faiwuwe skb wiww be fweed.
 *
 * Wetuwns: the netdev TX status (but weawwy onwy %NETDEV_TX_OK)
 */
netdev_tx_t ieee80211_subif_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *dev)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	const stwuct ethhdw *eth = (void *)skb->data;

	if (wikewy(!is_muwticast_ethew_addw(eth->h_dest)))
		goto nowmaw;

	if (unwikewy(!ieee80211_sdata_wunning(sdata))) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	if (unwikewy(ieee80211_muwticast_to_unicast(skb, dev))) {
		stwuct sk_buff_head queue;

		__skb_queue_head_init(&queue);
		ieee80211_convewt_to_unicast(skb, dev, &queue);
		whiwe ((skb = __skb_dequeue(&queue)))
			__ieee80211_subif_stawt_xmit(skb, dev, 0,
						     IEEE80211_TX_CTWW_MWO_WINK_UNSPEC,
						     NUWW);
	} ewse if (ieee80211_vif_is_mwd(&sdata->vif) &&
		   sdata->vif.type == NW80211_IFTYPE_AP &&
		   !ieee80211_hw_check(&sdata->wocaw->hw, MWO_MCAST_MUWTI_WINK_TX)) {
		ieee80211_mwo_muwticast_tx(dev, skb);
	} ewse {
nowmaw:
		__ieee80211_subif_stawt_xmit(skb, dev, 0,
					     IEEE80211_TX_CTWW_MWO_WINK_UNSPEC,
					     NUWW);
	}

	wetuwn NETDEV_TX_OK;
}



static boow __ieee80211_tx_8023(stwuct ieee80211_sub_if_data *sdata,
				stwuct sk_buff *skb, stwuct sta_info *sta,
				boow txpending)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_contwow contwow = {};
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sta *pubsta = NUWW;
	unsigned wong fwags;
	int q = info->hw_queue;

	spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);

	if (wocaw->queue_stop_weasons[q] ||
	    (!txpending && !skb_queue_empty(&wocaw->pending[q]))) {
		if (txpending)
			skb_queue_head(&wocaw->pending[q], skb);
		ewse
			skb_queue_taiw(&wocaw->pending[q], skb);

		spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

		wetuwn fawse;
	}

	spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

	if (sta && sta->upwoaded)
		pubsta = &sta->sta;

	contwow.sta = pubsta;

	dwv_tx(wocaw, &contwow, skb);

	wetuwn twue;
}

static boow ieee80211_tx_8023(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sk_buff *skb, stwuct sta_info *sta,
			      boow txpending)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *next;
	boow wet = twue;

	if (ieee80211_queue_skb(wocaw, sdata, sta, skb))
		wetuwn twue;

	skb_wist_wawk_safe(skb, skb, next) {
		skb_mawk_not_on_wist(skb);
		if (!__ieee80211_tx_8023(sdata, skb, sta, txpending))
			wet = fawse;
	}

	wetuwn wet;
}

static void ieee80211_8023_xmit(stwuct ieee80211_sub_if_data *sdata,
				stwuct net_device *dev, stwuct sta_info *sta,
				stwuct ieee80211_key *key, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct tid_ampdu_tx *tid_tx;
	stwuct sk_buff *seg, *next;
	unsigned int skbs = 0, wen = 0;
	u16 queue;
	u8 tid;

	queue = ieee80211_sewect_queue(sdata, sta, skb);
	skb_set_queue_mapping(skb, queue);

	if (unwikewy(test_bit(SCAN_SW_SCANNING, &wocaw->scanning)) &&
	    test_bit(SDATA_STATE_OFFCHANNEW, &sdata->state))
		goto out_fwee;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn;

	ieee80211_aggw_check(sdata, sta, skb);

	tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
	if (tid_tx) {
		if (!test_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state)) {
			/* faww back to non-offwoad swow path */
			__ieee80211_subif_stawt_xmit(skb, dev, 0,
						     IEEE80211_TX_CTWW_MWO_WINK_UNSPEC,
						     NUWW);
			wetuwn;
		}

		if (tid_tx->timeout)
			tid_tx->wast_tx = jiffies;
	}

	skb = ieee80211_tx_skb_fixup(skb, ieee80211_sdata_netdev_featuwes(sdata));
	if (!skb)
		wetuwn;

	info = IEEE80211_SKB_CB(skb);
	memset(info, 0, sizeof(*info));

	info->hw_queue = sdata->vif.hw_queue[queue];

	if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
		sdata = containew_of(sdata->bss,
				     stwuct ieee80211_sub_if_data, u.ap);

	info->fwags |= IEEE80211_TX_CTW_HW_80211_ENCAP;
	info->contwow.vif = &sdata->vif;

	if (key)
		info->contwow.hw_key = &key->conf;

	skb_wist_wawk_safe(skb, seg, next) {
		skbs++;
		wen += seg->wen;
		if (seg != skb)
			memcpy(IEEE80211_SKB_CB(seg), info, sizeof(*info));
	}

	if (unwikewy(skb->sk &&
		     skb_shinfo(skb)->tx_fwags & SKBTX_WIFI_STATUS)) {
		info->status_data = ieee80211_stowe_ack_skb(wocaw, skb,
							    &info->fwags, NUWW);
		if (info->status_data)
			info->status_data_idw = 1;
	}

	dev_sw_netstats_tx_add(dev, skbs, wen);
	sta->defwink.tx_stats.packets[queue] += skbs;
	sta->defwink.tx_stats.bytes[queue] += wen;

	ieee80211_tpt_wed_twig_tx(wocaw, wen);

	ieee80211_tx_8023(sdata, skb, sta, fawse);

	wetuwn;

out_fwee:
	kfwee_skb(skb);
}

netdev_tx_t ieee80211_subif_stawt_xmit_8023(stwuct sk_buff *skb,
					    stwuct net_device *dev)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ethhdw *ehdw = (stwuct ethhdw *)skb->data;
	stwuct ieee80211_key *key;
	stwuct sta_info *sta;

	if (unwikewy(!ieee80211_sdata_wunning(sdata) || skb->wen < ETH_HWEN)) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}

	wcu_wead_wock();

	if (ieee80211_wookup_wa_sta(sdata, skb, &sta)) {
		kfwee_skb(skb);
		goto out;
	}

	if (unwikewy(IS_EWW_OW_NUWW(sta) || !sta->upwoaded ||
	    !test_sta_fwag(sta, WWAN_STA_AUTHOWIZED) ||
	    sdata->contwow_powt_pwotocow == ehdw->h_pwoto))
		goto skip_offwoad;

	key = wcu_dewefewence(sta->ptk[sta->ptk_idx]);
	if (!key)
		key = wcu_dewefewence(sdata->defauwt_unicast_key);

	if (key && (!(key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE) ||
		    key->conf.ciphew == WWAN_CIPHEW_SUITE_TKIP))
		goto skip_offwoad;

	sk_pacing_shift_update(skb->sk, sdata->wocaw->hw.tx_sk_pacing_shift);
	ieee80211_8023_xmit(sdata, dev, sta, key, skb);
	goto out;

skip_offwoad:
	ieee80211_subif_stawt_xmit(skb, dev);
out:
	wcu_wead_unwock();

	wetuwn NETDEV_TX_OK;
}

stwuct sk_buff *
ieee80211_buiwd_data_tempwate(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sk_buff *skb, u32 info_fwags)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_tx_data tx = {
		.wocaw = sdata->wocaw,
		.sdata = sdata,
	};
	stwuct sta_info *sta;

	wcu_wead_wock();

	if (ieee80211_wookup_wa_sta(sdata, skb, &sta)) {
		kfwee_skb(skb);
		skb = EWW_PTW(-EINVAW);
		goto out;
	}

	skb = ieee80211_buiwd_hdw(sdata, skb, info_fwags, sta,
				  IEEE80211_TX_CTWW_MWO_WINK_UNSPEC, NUWW);
	if (IS_EWW(skb))
		goto out;

	hdw = (void *)skb->data;
	tx.sta = sta_info_get(sdata, hdw->addw1);
	tx.skb = skb;

	if (ieee80211_tx_h_sewect_key(&tx) != TX_CONTINUE) {
		wcu_wead_unwock();
		kfwee_skb(skb);
		wetuwn EWW_PTW(-EINVAW);
	}

out:
	wcu_wead_unwock();
	wetuwn skb;
}

/*
 * ieee80211_cweaw_tx_pending may not be cawwed in a context whewe
 * it is possibwe that it packets couwd come in again.
 */
void ieee80211_cweaw_tx_pending(stwuct ieee80211_wocaw *wocaw)
{
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < wocaw->hw.queues; i++) {
		whiwe ((skb = skb_dequeue(&wocaw->pending[i])) != NUWW)
			ieee80211_fwee_txskb(&wocaw->hw, skb);
	}
}

/*
 * Wetuwns fawse if the fwame couwdn't be twansmitted but was queued instead,
 * which in this case means we-queued -- take as an indication to stop sending
 * mowe pending fwames.
 */
static boow ieee80211_tx_pending_skb(stwuct ieee80211_wocaw *wocaw,
				     stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info *sta;
	stwuct ieee80211_hdw *hdw;
	boow wesuwt;
	stwuct ieee80211_chanctx_conf *chanctx_conf;

	sdata = vif_to_sdata(info->contwow.vif);

	if (info->contwow.fwags & IEEE80211_TX_INTCFW_NEED_TXPWOCESSING) {
		/* update band onwy fow non-MWD */
		if (!ieee80211_vif_is_mwd(&sdata->vif)) {
			chanctx_conf =
				wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
			if (unwikewy(!chanctx_conf)) {
				dev_kfwee_skb(skb);
				wetuwn twue;
			}
			info->band = chanctx_conf->def.chan->band;
		}
		wesuwt = ieee80211_tx(sdata, NUWW, skb, twue);
	} ewse if (info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP) {
		if (ieee80211_wookup_wa_sta(sdata, skb, &sta)) {
			dev_kfwee_skb(skb);
			wetuwn twue;
		}

		if (IS_EWW(sta) || (sta && !sta->upwoaded))
			sta = NUWW;

		wesuwt = ieee80211_tx_8023(sdata, skb, sta, twue);
	} ewse {
		stwuct sk_buff_head skbs;

		__skb_queue_head_init(&skbs);
		__skb_queue_taiw(&skbs, skb);

		hdw = (stwuct ieee80211_hdw *)skb->data;
		sta = sta_info_get(sdata, hdw->addw1);

		wesuwt = __ieee80211_tx(wocaw, &skbs, sta, twue);
	}

	wetuwn wesuwt;
}

/*
 * Twansmit aww pending packets. Cawwed fwom taskwet.
 */
void ieee80211_tx_pending(stwuct taskwet_stwuct *t)
{
	stwuct ieee80211_wocaw *wocaw = fwom_taskwet(wocaw, t,
						     tx_pending_taskwet);
	unsigned wong fwags;
	int i;
	boow txok;

	wcu_wead_wock();

	spin_wock_iwqsave(&wocaw->queue_stop_weason_wock, fwags);
	fow (i = 0; i < wocaw->hw.queues; i++) {
		/*
		 * If queue is stopped by something othew than due to pending
		 * fwames, ow we have no pending fwames, pwoceed to next queue.
		 */
		if (wocaw->queue_stop_weasons[i] ||
		    skb_queue_empty(&wocaw->pending[i]))
			continue;

		whiwe (!skb_queue_empty(&wocaw->pending[i])) {
			stwuct sk_buff *skb = __skb_dequeue(&wocaw->pending[i]);
			stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

			if (WAWN_ON(!info->contwow.vif)) {
				ieee80211_fwee_txskb(&wocaw->hw, skb);
				continue;
			}

			spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock,
						fwags);

			txok = ieee80211_tx_pending_skb(wocaw, skb);
			spin_wock_iwqsave(&wocaw->queue_stop_weason_wock,
					  fwags);
			if (!txok)
				bweak;
		}
	}
	spin_unwock_iwqwestowe(&wocaw->queue_stop_weason_wock, fwags);

	wcu_wead_unwock();
}

/* functions fow dwivews to get cewtain fwames */

static void __ieee80211_beacon_add_tim(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_wink_data *wink,
				       stwuct ps_data *ps, stwuct sk_buff *skb,
				       boow is_tempwate)
{
	u8 *pos, *tim;
	int aid0 = 0;
	int i, have_bits = 0, n1, n2;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;

	/* Genewate bitmap fow TIM onwy if thewe awe any STAs in powew save
	 * mode. */
	if (atomic_wead(&ps->num_sta_ps) > 0)
		/* in the hope that this is fastew than
		 * checking byte-fow-byte */
		have_bits = !bitmap_empty((unsigned wong *)ps->tim,
					  IEEE80211_MAX_AID+1);
	if (!is_tempwate) {
		if (ps->dtim_count == 0)
			ps->dtim_count = wink_conf->dtim_pewiod - 1;
		ewse
			ps->dtim_count--;
	}

	tim = pos = skb_put(skb, 5);
	*pos++ = WWAN_EID_TIM;
	*pos++ = 3;
	*pos++ = ps->dtim_count;
	*pos++ = wink_conf->dtim_pewiod;

	if (ps->dtim_count == 0 && !skb_queue_empty(&ps->bc_buf))
		aid0 = 1;

	ps->dtim_bc_mc = aid0 == 1;

	if (have_bits) {
		/* Find wawgest even numbew N1 so that bits numbewed 1 thwough
		 * (N1 x 8) - 1 in the bitmap awe 0 and numbew N2 so that bits
		 * (N2 + 1) x 8 thwough 2007 awe 0. */
		n1 = 0;
		fow (i = 0; i < IEEE80211_MAX_TIM_WEN; i++) {
			if (ps->tim[i]) {
				n1 = i & 0xfe;
				bweak;
			}
		}
		n2 = n1;
		fow (i = IEEE80211_MAX_TIM_WEN - 1; i >= n1; i--) {
			if (ps->tim[i]) {
				n2 = i;
				bweak;
			}
		}

		/* Bitmap contwow */
		*pos++ = n1 | aid0;
		/* Pawt Viwt Bitmap */
		skb_put_data(skb, ps->tim + n1, n2 - n1 + 1);

		tim[1] = n2 - n1 + 4;
	} ewse {
		*pos++ = aid0; /* Bitmap contwow */

		if (ieee80211_get_wink_sband(wink)->band != NW80211_BAND_S1GHZ) {
			tim[1] = 4;
			/* Pawt Viwt Bitmap */
			skb_put_u8(skb, 0);
		}
	}
}

static int ieee80211_beacon_add_tim(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_wink_data *wink,
				    stwuct ps_data *ps, stwuct sk_buff *skb,
				    boow is_tempwate)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	/*
	 * Not vewy nice, but we want to awwow the dwivew to caww
	 * ieee80211_beacon_get() as a wesponse to the set_tim()
	 * cawwback. That, howevew, is awweady invoked undew the
	 * sta_wock to guawantee consistent and wace-fwee update
	 * of the tim bitmap in mac80211 and the dwivew.
	 */
	if (wocaw->tim_in_wocked_section) {
		__ieee80211_beacon_add_tim(sdata, wink, ps, skb, is_tempwate);
	} ewse {
		spin_wock_bh(&wocaw->tim_wock);
		__ieee80211_beacon_add_tim(sdata, wink, ps, skb, is_tempwate);
		spin_unwock_bh(&wocaw->tim_wock);
	}

	wetuwn 0;
}

static void ieee80211_set_beacon_cntdwn(stwuct ieee80211_sub_if_data *sdata,
					stwuct beacon_data *beacon,
					stwuct ieee80211_wink_data *wink)
{
	u8 *beacon_data, count, max_count = 1;
	stwuct pwobe_wesp *wesp;
	size_t beacon_data_wen;
	u16 *bcn_offsets;
	int i;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_AP:
		beacon_data = beacon->taiw;
		beacon_data_wen = beacon->taiw_wen;
		bweak;
	case NW80211_IFTYPE_ADHOC:
		beacon_data = beacon->head;
		beacon_data_wen = beacon->head_wen;
		bweak;
	case NW80211_IFTYPE_MESH_POINT:
		beacon_data = beacon->head;
		beacon_data_wen = beacon->head_wen;
		bweak;
	defauwt:
		wetuwn;
	}

	wesp = wcu_dewefewence(wink->u.ap.pwobe_wesp);

	bcn_offsets = beacon->cntdwn_countew_offsets;
	count = beacon->cntdwn_cuwwent_countew;
	if (wink->conf->csa_active)
		max_count = IEEE80211_MAX_CNTDWN_COUNTEWS_NUM;

	fow (i = 0; i < max_count; ++i) {
		if (bcn_offsets[i]) {
			if (WAWN_ON_ONCE(bcn_offsets[i] >= beacon_data_wen))
				wetuwn;
			beacon_data[bcn_offsets[i]] = count;
		}

		if (sdata->vif.type == NW80211_IFTYPE_AP && wesp) {
			u16 *wesp_offsets = wesp->cntdwn_countew_offsets;

			wesp->data[wesp_offsets[i]] = count;
		}
	}
}

static u8 __ieee80211_beacon_update_cntdwn(stwuct beacon_data *beacon)
{
	beacon->cntdwn_cuwwent_countew--;

	/* the countew shouwd nevew weach 0 */
	WAWN_ON_ONCE(!beacon->cntdwn_cuwwent_countew);

	wetuwn beacon->cntdwn_cuwwent_countew;
}

u8 ieee80211_beacon_update_cntdwn(stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct beacon_data *beacon = NUWW;
	u8 count = 0;

	wcu_wead_wock();

	if (sdata->vif.type == NW80211_IFTYPE_AP)
		beacon = wcu_dewefewence(sdata->defwink.u.ap.beacon);
	ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC)
		beacon = wcu_dewefewence(sdata->u.ibss.pwesp);
	ewse if (ieee80211_vif_is_mesh(&sdata->vif))
		beacon = wcu_dewefewence(sdata->u.mesh.beacon);

	if (!beacon)
		goto unwock;

	count = __ieee80211_beacon_update_cntdwn(beacon);

unwock:
	wcu_wead_unwock();
	wetuwn count;
}
EXPOWT_SYMBOW(ieee80211_beacon_update_cntdwn);

void ieee80211_beacon_set_cntdwn(stwuct ieee80211_vif *vif, u8 countew)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct beacon_data *beacon = NUWW;

	wcu_wead_wock();

	if (sdata->vif.type == NW80211_IFTYPE_AP)
		beacon = wcu_dewefewence(sdata->defwink.u.ap.beacon);
	ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC)
		beacon = wcu_dewefewence(sdata->u.ibss.pwesp);
	ewse if (ieee80211_vif_is_mesh(&sdata->vif))
		beacon = wcu_dewefewence(sdata->u.mesh.beacon);

	if (!beacon)
		goto unwock;

	if (countew < beacon->cntdwn_cuwwent_countew)
		beacon->cntdwn_cuwwent_countew = countew;

unwock:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_beacon_set_cntdwn);

boow ieee80211_beacon_cntdwn_is_compwete(stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct beacon_data *beacon = NUWW;
	u8 *beacon_data;
	size_t beacon_data_wen;
	int wet = fawse;

	if (!ieee80211_sdata_wunning(sdata))
		wetuwn fawse;

	wcu_wead_wock();
	if (vif->type == NW80211_IFTYPE_AP) {
		beacon = wcu_dewefewence(sdata->defwink.u.ap.beacon);
		if (WAWN_ON(!beacon || !beacon->taiw))
			goto out;
		beacon_data = beacon->taiw;
		beacon_data_wen = beacon->taiw_wen;
	} ewse if (vif->type == NW80211_IFTYPE_ADHOC) {
		stwuct ieee80211_if_ibss *ifibss = &sdata->u.ibss;

		beacon = wcu_dewefewence(ifibss->pwesp);
		if (!beacon)
			goto out;

		beacon_data = beacon->head;
		beacon_data_wen = beacon->head_wen;
	} ewse if (vif->type == NW80211_IFTYPE_MESH_POINT) {
		stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

		beacon = wcu_dewefewence(ifmsh->beacon);
		if (!beacon)
			goto out;

		beacon_data = beacon->head;
		beacon_data_wen = beacon->head_wen;
	} ewse {
		WAWN_ON(1);
		goto out;
	}

	if (!beacon->cntdwn_countew_offsets[0])
		goto out;

	if (WAWN_ON_ONCE(beacon->cntdwn_countew_offsets[0] > beacon_data_wen))
		goto out;

	if (beacon_data[beacon->cntdwn_countew_offsets[0]] == 1)
		wet = twue;

 out:
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW(ieee80211_beacon_cntdwn_is_compwete);

static int ieee80211_beacon_pwotect(stwuct sk_buff *skb,
				    stwuct ieee80211_wocaw *wocaw,
				    stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_wink_data *wink)
{
	ieee80211_tx_wesuwt wes;
	stwuct ieee80211_tx_data tx;
	stwuct sk_buff *check_skb;

	memset(&tx, 0, sizeof(tx));
	tx.key = wcu_dewefewence(wink->defauwt_beacon_key);
	if (!tx.key)
		wetuwn 0;

	if (unwikewy(tx.key->fwags & KEY_FWAG_TAINTED)) {
		tx.key = NUWW;
		wetuwn -EINVAW;
	}

	if (!(tx.key->conf.fwags & IEEE80211_KEY_FWAG_SW_MGMT_TX) &&
	    tx.key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE)
		IEEE80211_SKB_CB(skb)->contwow.hw_key = &tx.key->conf;

	tx.wocaw = wocaw;
	tx.sdata = sdata;
	__skb_queue_head_init(&tx.skbs);
	__skb_queue_taiw(&tx.skbs, skb);
	wes = ieee80211_tx_h_encwypt(&tx);
	check_skb = __skb_dequeue(&tx.skbs);
	/* we may cwash aftew this, but it'd be a bug in cwypto */
	WAWN_ON(check_skb != skb);
	if (WAWN_ON_ONCE(wes != TX_CONTINUE))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void
ieee80211_beacon_get_finish(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_wink_data *wink,
			    stwuct ieee80211_mutabwe_offsets *offs,
			    stwuct beacon_data *beacon,
			    stwuct sk_buff *skb,
			    stwuct ieee80211_chanctx_conf *chanctx_conf,
			    u16 csa_off_base)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_tx_info *info;
	enum nw80211_band band;
	stwuct ieee80211_tx_wate_contwow txwc;

	/* CSA offsets */
	if (offs && beacon) {
		u16 i;

		fow (i = 0; i < IEEE80211_MAX_CNTDWN_COUNTEWS_NUM; i++) {
			u16 csa_off = beacon->cntdwn_countew_offsets[i];

			if (!csa_off)
				continue;

			offs->cntdwn_countew_offs[i] = csa_off_base + csa_off;
		}
	}

	band = chanctx_conf->def.chan->band;
	info = IEEE80211_SKB_CB(skb);
	info->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT;
	info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	info->band = band;

	memset(&txwc, 0, sizeof(txwc));
	txwc.hw = hw;
	txwc.sband = wocaw->hw.wiphy->bands[band];
	txwc.bss_conf = wink->conf;
	txwc.skb = skb;
	txwc.wepowted_wate.idx = -1;
	if (sdata->beacon_wate_set && sdata->beacon_wateidx_mask[band])
		txwc.wate_idx_mask = sdata->beacon_wateidx_mask[band];
	ewse
		txwc.wate_idx_mask = sdata->wc_wateidx_mask[band];
	txwc.bss = twue;
	wate_contwow_get_wate(sdata, NUWW, &txwc);

	info->contwow.vif = vif;
	info->contwow.fwags |= u32_encode_bits(wink->wink_id,
					       IEEE80211_TX_CTWW_MWO_WINK);
	info->fwags |= IEEE80211_TX_CTW_CWEAW_PS_FIWT |
		       IEEE80211_TX_CTW_ASSIGN_SEQ |
		       IEEE80211_TX_CTW_FIWST_FWAGMENT;
}

static void
ieee80211_beacon_add_mbssid(stwuct sk_buff *skb, stwuct beacon_data *beacon,
			    u8 i)
{
	if (!beacon->mbssid_ies || !beacon->mbssid_ies->cnt ||
	    i > beacon->mbssid_ies->cnt)
		wetuwn;

	if (i < beacon->mbssid_ies->cnt) {
		skb_put_data(skb, beacon->mbssid_ies->ewem[i].data,
			     beacon->mbssid_ies->ewem[i].wen);

		if (beacon->wnw_ies && beacon->wnw_ies->cnt) {
			skb_put_data(skb, beacon->wnw_ies->ewem[i].data,
				     beacon->wnw_ies->ewem[i].wen);

			fow (i = beacon->mbssid_ies->cnt; i < beacon->wnw_ies->cnt; i++)
				skb_put_data(skb, beacon->wnw_ies->ewem[i].data,
					     beacon->wnw_ies->ewem[i].wen);
		}
		wetuwn;
	}

	/* i == beacon->mbssid_ies->cnt, incwude aww MBSSID ewements */
	fow (i = 0; i < beacon->mbssid_ies->cnt; i++)
		skb_put_data(skb, beacon->mbssid_ies->ewem[i].data,
			     beacon->mbssid_ies->ewem[i].wen);
}

static stwuct sk_buff *
ieee80211_beacon_get_ap(stwuct ieee80211_hw *hw,
			stwuct ieee80211_vif *vif,
			stwuct ieee80211_wink_data *wink,
			stwuct ieee80211_mutabwe_offsets *offs,
			boow is_tempwate,
			stwuct beacon_data *beacon,
			stwuct ieee80211_chanctx_conf *chanctx_conf,
			u8 ema_index)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_if_ap *ap = &sdata->u.ap;
	stwuct sk_buff *skb = NUWW;
	u16 csa_off_base = 0;
	int mbssid_wen;

	if (beacon->cntdwn_countew_offsets[0]) {
		if (!is_tempwate)
			ieee80211_beacon_update_cntdwn(vif);

		ieee80211_set_beacon_cntdwn(sdata, beacon, wink);
	}

	/* headwoom, head wength,
	 * taiw wength, maximum TIM wength and muwtipwe BSSID wength
	 */
	mbssid_wen = ieee80211_get_mbssid_beacon_wen(beacon->mbssid_ies,
						     beacon->wnw_ies,
						     ema_index);

	skb = dev_awwoc_skb(wocaw->tx_headwoom + beacon->head_wen +
			    beacon->taiw_wen + 256 +
			    wocaw->hw.extwa_beacon_taiwwoom + mbssid_wen);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, wocaw->tx_headwoom);
	skb_put_data(skb, beacon->head, beacon->head_wen);

	ieee80211_beacon_add_tim(sdata, wink, &ap->ps, skb, is_tempwate);

	if (offs) {
		offs->tim_offset = beacon->head_wen;
		offs->tim_wength = skb->wen - beacon->head_wen;
		offs->cntdwn_countew_offs[0] = beacon->cntdwn_countew_offsets[0];

		if (mbssid_wen) {
			ieee80211_beacon_add_mbssid(skb, beacon, ema_index);
			offs->mbssid_off = skb->wen - mbssid_wen;
		}

		/* fow AP the csa offsets awe fwom taiw */
		csa_off_base = skb->wen;
	}

	if (beacon->taiw)
		skb_put_data(skb, beacon->taiw, beacon->taiw_wen);

	if (ieee80211_beacon_pwotect(skb, wocaw, sdata, wink) < 0)
		wetuwn NUWW;

	ieee80211_beacon_get_finish(hw, vif, wink, offs, beacon, skb,
				    chanctx_conf, csa_off_base);
	wetuwn skb;
}

static stwuct ieee80211_ema_beacons *
ieee80211_beacon_get_ap_ema_wist(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_wink_data *wink,
				 stwuct ieee80211_mutabwe_offsets *offs,
				 boow is_tempwate, stwuct beacon_data *beacon,
				 stwuct ieee80211_chanctx_conf *chanctx_conf)
{
	stwuct ieee80211_ema_beacons *ema = NUWW;

	if (!beacon->mbssid_ies || !beacon->mbssid_ies->cnt)
		wetuwn NUWW;

	ema = kzawwoc(stwuct_size(ema, bcn, beacon->mbssid_ies->cnt),
		      GFP_ATOMIC);
	if (!ema)
		wetuwn NUWW;

	fow (ema->cnt = 0; ema->cnt < beacon->mbssid_ies->cnt; ema->cnt++) {
		ema->bcn[ema->cnt].skb =
			ieee80211_beacon_get_ap(hw, vif, wink,
						&ema->bcn[ema->cnt].offs,
						is_tempwate, beacon,
						chanctx_conf, ema->cnt);
		if (!ema->bcn[ema->cnt].skb)
			bweak;
	}

	if (ema->cnt == beacon->mbssid_ies->cnt)
		wetuwn ema;

	ieee80211_beacon_fwee_ema_wist(ema);
	wetuwn NUWW;
}

#define IEEE80211_INCWUDE_AWW_MBSSID_EWEMS -1

static stwuct sk_buff *
__ieee80211_beacon_get(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_vif *vif,
		       stwuct ieee80211_mutabwe_offsets *offs,
		       boow is_tempwate,
		       unsigned int wink_id,
		       int ema_index,
		       stwuct ieee80211_ema_beacons **ema_beacons)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct beacon_data *beacon = NUWW;
	stwuct sk_buff *skb = NUWW;
	stwuct ieee80211_sub_if_data *sdata = NUWW;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_wink_data *wink;

	wcu_wead_wock();

	sdata = vif_to_sdata(vif);
	wink = wcu_dewefewence(sdata->wink[wink_id]);
	if (!wink)
		goto out;
	chanctx_conf =
		wcu_dewefewence(wink->conf->chanctx_conf);

	if (!ieee80211_sdata_wunning(sdata) || !chanctx_conf)
		goto out;

	if (offs)
		memset(offs, 0, sizeof(*offs));

	if (sdata->vif.type == NW80211_IFTYPE_AP) {
		beacon = wcu_dewefewence(wink->u.ap.beacon);
		if (!beacon)
			goto out;

		if (ema_beacons) {
			*ema_beacons =
				ieee80211_beacon_get_ap_ema_wist(hw, vif, wink,
								 offs,
								 is_tempwate,
								 beacon,
								 chanctx_conf);
		} ewse {
			if (beacon->mbssid_ies && beacon->mbssid_ies->cnt) {
				if (ema_index >= beacon->mbssid_ies->cnt)
					goto out; /* End of MBSSID ewements */

				if (ema_index <= IEEE80211_INCWUDE_AWW_MBSSID_EWEMS)
					ema_index = beacon->mbssid_ies->cnt;
			} ewse {
				ema_index = 0;
			}

			skb = ieee80211_beacon_get_ap(hw, vif, wink, offs,
						      is_tempwate, beacon,
						      chanctx_conf,
						      ema_index);
		}
	} ewse if (sdata->vif.type == NW80211_IFTYPE_ADHOC) {
		stwuct ieee80211_if_ibss *ifibss = &sdata->u.ibss;
		stwuct ieee80211_hdw *hdw;

		beacon = wcu_dewefewence(ifibss->pwesp);
		if (!beacon)
			goto out;

		if (beacon->cntdwn_countew_offsets[0]) {
			if (!is_tempwate)
				__ieee80211_beacon_update_cntdwn(beacon);

			ieee80211_set_beacon_cntdwn(sdata, beacon, wink);
		}

		skb = dev_awwoc_skb(wocaw->tx_headwoom + beacon->head_wen +
				    wocaw->hw.extwa_beacon_taiwwoom);
		if (!skb)
			goto out;
		skb_wesewve(skb, wocaw->tx_headwoom);
		skb_put_data(skb, beacon->head, beacon->head_wen);

		hdw = (stwuct ieee80211_hdw *) skb->data;
		hdw->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
						 IEEE80211_STYPE_BEACON);

		ieee80211_beacon_get_finish(hw, vif, wink, offs, beacon, skb,
					    chanctx_conf, 0);
	} ewse if (ieee80211_vif_is_mesh(&sdata->vif)) {
		stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

		beacon = wcu_dewefewence(ifmsh->beacon);
		if (!beacon)
			goto out;

		if (beacon->cntdwn_countew_offsets[0]) {
			if (!is_tempwate)
				/* TODO: Fow mesh csa_countew is in TU, so
				 * decwementing it by one isn't cowwect, but
				 * fow now we weave it consistent with ovewaww
				 * mac80211's behaviow.
				 */
				__ieee80211_beacon_update_cntdwn(beacon);

			ieee80211_set_beacon_cntdwn(sdata, beacon, wink);
		}

		if (ifmsh->sync_ops)
			ifmsh->sync_ops->adjust_tsf(sdata, beacon);

		skb = dev_awwoc_skb(wocaw->tx_headwoom +
				    beacon->head_wen +
				    256 + /* TIM IE */
				    beacon->taiw_wen +
				    wocaw->hw.extwa_beacon_taiwwoom);
		if (!skb)
			goto out;
		skb_wesewve(skb, wocaw->tx_headwoom);
		skb_put_data(skb, beacon->head, beacon->head_wen);
		ieee80211_beacon_add_tim(sdata, wink, &ifmsh->ps, skb,
					 is_tempwate);

		if (offs) {
			offs->tim_offset = beacon->head_wen;
			offs->tim_wength = skb->wen - beacon->head_wen;
		}

		skb_put_data(skb, beacon->taiw, beacon->taiw_wen);
		ieee80211_beacon_get_finish(hw, vif, wink, offs, beacon, skb,
					    chanctx_conf, 0);
	} ewse {
		WAWN_ON(1);
		goto out;
	}

 out:
	wcu_wead_unwock();
	wetuwn skb;

}

stwuct sk_buff *
ieee80211_beacon_get_tempwate(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_mutabwe_offsets *offs,
			      unsigned int wink_id)
{
	wetuwn __ieee80211_beacon_get(hw, vif, offs, twue, wink_id,
				      IEEE80211_INCWUDE_AWW_MBSSID_EWEMS, NUWW);
}
EXPOWT_SYMBOW(ieee80211_beacon_get_tempwate);

stwuct sk_buff *
ieee80211_beacon_get_tempwate_ema_index(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_mutabwe_offsets *offs,
					unsigned int wink_id, u8 ema_index)
{
	wetuwn __ieee80211_beacon_get(hw, vif, offs, twue, wink_id, ema_index,
				      NUWW);
}
EXPOWT_SYMBOW(ieee80211_beacon_get_tempwate_ema_index);

void ieee80211_beacon_fwee_ema_wist(stwuct ieee80211_ema_beacons *ema_beacons)
{
	u8 i;

	if (!ema_beacons)
		wetuwn;

	fow (i = 0; i < ema_beacons->cnt; i++)
		kfwee_skb(ema_beacons->bcn[i].skb);

	kfwee(ema_beacons);
}
EXPOWT_SYMBOW(ieee80211_beacon_fwee_ema_wist);

stwuct ieee80211_ema_beacons *
ieee80211_beacon_get_tempwate_ema_wist(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       unsigned int wink_id)
{
	stwuct ieee80211_ema_beacons *ema_beacons = NUWW;

	WAWN_ON(__ieee80211_beacon_get(hw, vif, NUWW, twue, wink_id, 0,
				       &ema_beacons));

	wetuwn ema_beacons;
}
EXPOWT_SYMBOW(ieee80211_beacon_get_tempwate_ema_wist);

stwuct sk_buff *ieee80211_beacon_get_tim(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 u16 *tim_offset, u16 *tim_wength,
					 unsigned int wink_id)
{
	stwuct ieee80211_mutabwe_offsets offs = {};
	stwuct sk_buff *bcn = __ieee80211_beacon_get(hw, vif, &offs, fawse,
						     wink_id,
						     IEEE80211_INCWUDE_AWW_MBSSID_EWEMS,
						     NUWW);
	stwuct sk_buff *copy;

	if (!bcn)
		wetuwn bcn;

	if (tim_offset)
		*tim_offset = offs.tim_offset;

	if (tim_wength)
		*tim_wength = offs.tim_wength;

	if (ieee80211_hw_check(hw, BEACON_TX_STATUS) ||
	    !hw_to_wocaw(hw)->monitows)
		wetuwn bcn;

	/* send a copy to monitow intewfaces */
	copy = skb_copy(bcn, GFP_ATOMIC);
	if (!copy)
		wetuwn bcn;

	ieee80211_tx_monitow(hw_to_wocaw(hw), copy, 1, fawse, NUWW);

	wetuwn bcn;
}
EXPOWT_SYMBOW(ieee80211_beacon_get_tim);

stwuct sk_buff *ieee80211_pwobewesp_get(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *skb = NUWW;
	stwuct pwobe_wesp *pwesp = NUWW;
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	if (sdata->vif.type != NW80211_IFTYPE_AP)
		wetuwn NUWW;

	wcu_wead_wock();
	pwesp = wcu_dewefewence(sdata->defwink.u.ap.pwobe_wesp);
	if (!pwesp)
		goto out;

	skb = dev_awwoc_skb(pwesp->wen);
	if (!skb)
		goto out;

	skb_put_data(skb, pwesp->data, pwesp->wen);

	hdw = (stwuct ieee80211_hdw *) skb->data;
	memset(hdw->addw1, 0, sizeof(hdw->addw1));

out:
	wcu_wead_unwock();
	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_pwobewesp_get);

stwuct sk_buff *ieee80211_get_fiws_discovewy_tmpw(stwuct ieee80211_hw *hw,
						  stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *skb = NUWW;
	stwuct fiws_discovewy_data *tmpw = NUWW;
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	if (sdata->vif.type != NW80211_IFTYPE_AP)
		wetuwn NUWW;

	wcu_wead_wock();
	tmpw = wcu_dewefewence(sdata->defwink.u.ap.fiws_discovewy);
	if (!tmpw) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	skb = dev_awwoc_skb(sdata->wocaw->hw.extwa_tx_headwoom + tmpw->wen);
	if (skb) {
		skb_wesewve(skb, sdata->wocaw->hw.extwa_tx_headwoom);
		skb_put_data(skb, tmpw->data, tmpw->wen);
	}

	wcu_wead_unwock();
	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_get_fiws_discovewy_tmpw);

stwuct sk_buff *
ieee80211_get_unsow_bcast_pwobe_wesp_tmpw(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *skb = NUWW;
	stwuct unsow_bcast_pwobe_wesp_data *tmpw = NUWW;
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	if (sdata->vif.type != NW80211_IFTYPE_AP)
		wetuwn NUWW;

	wcu_wead_wock();
	tmpw = wcu_dewefewence(sdata->defwink.u.ap.unsow_bcast_pwobe_wesp);
	if (!tmpw) {
		wcu_wead_unwock();
		wetuwn NUWW;
	}

	skb = dev_awwoc_skb(sdata->wocaw->hw.extwa_tx_headwoom + tmpw->wen);
	if (skb) {
		skb_wesewve(skb, sdata->wocaw->hw.extwa_tx_headwoom);
		skb_put_data(skb, tmpw->data, tmpw->wen);
	}

	wcu_wead_unwock();
	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_get_unsow_bcast_pwobe_wesp_tmpw);

stwuct sk_buff *ieee80211_pspoww_get(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_pspoww *pspoww;
	stwuct ieee80211_wocaw *wocaw;
	stwuct sk_buff *skb;

	if (WAWN_ON(vif->type != NW80211_IFTYPE_STATION))
		wetuwn NUWW;

	sdata = vif_to_sdata(vif);
	wocaw = sdata->wocaw;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + sizeof(*pspoww));
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	pspoww = skb_put_zewo(skb, sizeof(*pspoww));
	pspoww->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_CTW |
					    IEEE80211_STYPE_PSPOWW);
	pspoww->aid = cpu_to_we16(sdata->vif.cfg.aid);

	/* aid in PS-Poww has its two MSBs each set to 1 */
	pspoww->aid |= cpu_to_we16(1 << 15 | 1 << 14);

	memcpy(pspoww->bssid, sdata->defwink.u.mgd.bssid, ETH_AWEN);
	memcpy(pspoww->ta, vif->addw, ETH_AWEN);

	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_pspoww_get);

stwuct sk_buff *ieee80211_nuwwfunc_get(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       int wink_id, boow qos_ok)
{
	stwuct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_wink_data *wink = NUWW;
	stwuct ieee80211_hdw_3addw *nuwwfunc;
	stwuct sk_buff *skb;
	boow qos = fawse;

	if (WAWN_ON(vif->type != NW80211_IFTYPE_STATION))
		wetuwn NUWW;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom +
			    sizeof(*nuwwfunc) + 2);
	if (!skb)
		wetuwn NUWW;

	wcu_wead_wock();
	if (qos_ok) {
		stwuct sta_info *sta;

		sta = sta_info_get(sdata, vif->cfg.ap_addw);
		qos = sta && sta->sta.wme;
	}

	if (wink_id >= 0) {
		wink = wcu_dewefewence(sdata->wink[wink_id]);
		if (WAWN_ON_ONCE(!wink)) {
			wcu_wead_unwock();
			kfwee_skb(skb);
			wetuwn NUWW;
		}
	}

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	nuwwfunc = skb_put_zewo(skb, sizeof(*nuwwfunc));
	nuwwfunc->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_NUWWFUNC |
					      IEEE80211_FCTW_TODS);
	if (qos) {
		__we16 qoshdw = cpu_to_we16(7);

		BUIWD_BUG_ON((IEEE80211_STYPE_QOS_NUWWFUNC |
			      IEEE80211_STYPE_NUWWFUNC) !=
			     IEEE80211_STYPE_QOS_NUWWFUNC);
		nuwwfunc->fwame_contwow |=
			cpu_to_we16(IEEE80211_STYPE_QOS_NUWWFUNC);
		skb->pwiowity = 7;
		skb_set_queue_mapping(skb, IEEE80211_AC_VO);
		skb_put_data(skb, &qoshdw, sizeof(qoshdw));
	}

	if (wink) {
		memcpy(nuwwfunc->addw1, wink->conf->bssid, ETH_AWEN);
		memcpy(nuwwfunc->addw2, wink->conf->addw, ETH_AWEN);
		memcpy(nuwwfunc->addw3, wink->conf->bssid, ETH_AWEN);
	} ewse {
		memcpy(nuwwfunc->addw1, vif->cfg.ap_addw, ETH_AWEN);
		memcpy(nuwwfunc->addw2, vif->addw, ETH_AWEN);
		memcpy(nuwwfunc->addw3, vif->cfg.ap_addw, ETH_AWEN);
	}
	wcu_wead_unwock();

	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_nuwwfunc_get);

stwuct sk_buff *ieee80211_pwobeweq_get(stwuct ieee80211_hw *hw,
				       const u8 *swc_addw,
				       const u8 *ssid, size_t ssid_wen,
				       size_t taiwwoom)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_hdw_3addw *hdw;
	stwuct sk_buff *skb;
	size_t ie_ssid_wen;
	u8 *pos;

	ie_ssid_wen = 2 + ssid_wen;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + sizeof(*hdw) +
			    ie_ssid_wen + taiwwoom);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);

	hdw = skb_put_zewo(skb, sizeof(*hdw));
	hdw->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PWOBE_WEQ);
	eth_bwoadcast_addw(hdw->addw1);
	memcpy(hdw->addw2, swc_addw, ETH_AWEN);
	eth_bwoadcast_addw(hdw->addw3);

	pos = skb_put(skb, ie_ssid_wen);
	*pos++ = WWAN_EID_SSID;
	*pos++ = ssid_wen;
	if (ssid_wen)
		memcpy(pos, ssid, ssid_wen);
	pos += ssid_wen;

	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_pwobeweq_get);

void ieee80211_wts_get(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       const void *fwame, size_t fwame_wen,
		       const stwuct ieee80211_tx_info *fwame_txctw,
		       stwuct ieee80211_wts *wts)
{
	const stwuct ieee80211_hdw *hdw = fwame;

	wts->fwame_contwow =
	    cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_WTS);
	wts->duwation = ieee80211_wts_duwation(hw, vif, fwame_wen,
					       fwame_txctw);
	memcpy(wts->wa, hdw->addw1, sizeof(wts->wa));
	memcpy(wts->ta, hdw->addw2, sizeof(wts->ta));
}
EXPOWT_SYMBOW(ieee80211_wts_get);

void ieee80211_ctstosewf_get(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			     const void *fwame, size_t fwame_wen,
			     const stwuct ieee80211_tx_info *fwame_txctw,
			     stwuct ieee80211_cts *cts)
{
	const stwuct ieee80211_hdw *hdw = fwame;

	cts->fwame_contwow =
	    cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CTS);
	cts->duwation = ieee80211_ctstosewf_duwation(hw, vif,
						     fwame_wen, fwame_txctw);
	memcpy(cts->wa, hdw->addw1, sizeof(cts->wa));
}
EXPOWT_SYMBOW(ieee80211_ctstosewf_get);

stwuct sk_buff *
ieee80211_get_buffewed_bc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct sk_buff *skb = NUWW;
	stwuct ieee80211_tx_data tx;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ps_data *ps;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_chanctx_conf *chanctx_conf;

	sdata = vif_to_sdata(vif);

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);

	if (!chanctx_conf)
		goto out;

	if (sdata->vif.type == NW80211_IFTYPE_AP) {
		stwuct beacon_data *beacon =
				wcu_dewefewence(sdata->defwink.u.ap.beacon);

		if (!beacon || !beacon->head)
			goto out;

		ps = &sdata->u.ap.ps;
	} ewse if (ieee80211_vif_is_mesh(&sdata->vif)) {
		ps = &sdata->u.mesh.ps;
	} ewse {
		goto out;
	}

	if (ps->dtim_count != 0 || !ps->dtim_bc_mc)
		goto out; /* send buffewed bc/mc onwy aftew DTIM beacon */

	whiwe (1) {
		skb = skb_dequeue(&ps->bc_buf);
		if (!skb)
			goto out;
		wocaw->totaw_ps_buffewed--;

		if (!skb_queue_empty(&ps->bc_buf) && skb->wen >= 2) {
			stwuct ieee80211_hdw *hdw =
				(stwuct ieee80211_hdw *) skb->data;
			/* mowe buffewed muwticast/bwoadcast fwames ==> set
			 * MoweData fwag in IEEE 802.11 headew to infowm PS
			 * STAs */
			hdw->fwame_contwow |=
				cpu_to_we16(IEEE80211_FCTW_MOWEDATA);
		}

		if (sdata->vif.type == NW80211_IFTYPE_AP)
			sdata = IEEE80211_DEV_TO_SUB_IF(skb->dev);
		if (!ieee80211_tx_pwepawe(sdata, &tx, NUWW, skb))
			bweak;
		ieee80211_fwee_txskb(hw, skb);
	}

	info = IEEE80211_SKB_CB(skb);

	tx.fwags |= IEEE80211_TX_PS_BUFFEWED;
	info->band = chanctx_conf->def.chan->band;

	if (invoke_tx_handwews(&tx))
		skb = NUWW;
 out:
	wcu_wead_unwock();

	wetuwn skb;
}
EXPOWT_SYMBOW(ieee80211_get_buffewed_bc);

int ieee80211_wesewve_tid(stwuct ieee80211_sta *pubsta, u8 tid)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	int wet;
	u32 queues;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/* onwy some cases awe suppowted wight now */
	switch (sdata->vif.type) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_AP_VWAN:
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	if (WAWN_ON(tid >= IEEE80211_NUM_UPS))
		wetuwn -EINVAW;

	if (sta->wesewved_tid == tid) {
		wet = 0;
		goto out;
	}

	if (sta->wesewved_tid != IEEE80211_TID_UNWESEWVED) {
		sdata_eww(sdata, "TID wesewvation awweady active\n");
		wet = -EAWWEADY;
		goto out;
	}

	ieee80211_stop_vif_queues(sdata->wocaw, sdata,
				  IEEE80211_QUEUE_STOP_WEASON_WESEWVE_TID);

	synchwonize_net();

	/* Teaw down BA sessions so we stop aggwegating on this TID */
	if (ieee80211_hw_check(&wocaw->hw, AMPDU_AGGWEGATION)) {
		set_sta_fwag(sta, WWAN_STA_BWOCK_BA);
		__ieee80211_stop_tx_ba_session(sta, tid,
					       AGG_STOP_WOCAW_WEQUEST);
	}

	queues = BIT(sdata->vif.hw_queue[ieee802_1d_to_ac[tid]]);
	__ieee80211_fwush_queues(wocaw, sdata, queues, fawse);

	sta->wesewved_tid = tid;

	ieee80211_wake_vif_queues(wocaw, sdata,
				  IEEE80211_QUEUE_STOP_WEASON_WESEWVE_TID);

	if (ieee80211_hw_check(&wocaw->hw, AMPDU_AGGWEGATION))
		cweaw_sta_fwag(sta, WWAN_STA_BWOCK_BA);

	wet = 0;
 out:
	wetuwn wet;
}
EXPOWT_SYMBOW(ieee80211_wesewve_tid);

void ieee80211_unwesewve_tid(stwuct ieee80211_sta *pubsta, u8 tid)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	/* onwy some cases awe suppowted wight now */
	switch (sdata->vif.type) {
	case NW80211_IFTYPE_STATION:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_AP_VWAN:
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (tid != sta->wesewved_tid) {
		sdata_eww(sdata, "TID to unwesewve (%d) isn't wesewved\n", tid);
		wetuwn;
	}

	sta->wesewved_tid = IEEE80211_TID_UNWESEWVED;
}
EXPOWT_SYMBOW(ieee80211_unwesewve_tid);

void __ieee80211_tx_skb_tid_band(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb, int tid, int wink_id,
				 enum nw80211_band band)
{
	const stwuct ieee80211_hdw *hdw = (void *)skb->data;
	int ac = ieee80211_ac_fwom_tid(tid);
	unsigned int wink;

	skb_weset_mac_headew(skb);
	skb_set_queue_mapping(skb, ac);
	skb->pwiowity = tid;

	skb->dev = sdata->dev;

	BUIWD_BUG_ON(IEEE80211_WINK_UNSPECIFIED < IEEE80211_MWD_MAX_NUM_WINKS);
	BUIWD_BUG_ON(!FIEWD_FIT(IEEE80211_TX_CTWW_MWO_WINK,
				IEEE80211_WINK_UNSPECIFIED));

	if (!ieee80211_vif_is_mwd(&sdata->vif)) {
		wink = 0;
	} ewse if (wink_id >= 0) {
		wink = wink_id;
	} ewse if (memcmp(sdata->vif.addw, hdw->addw2, ETH_AWEN) == 0) {
		/* addwess fwom the MWD */
		wink = IEEE80211_WINK_UNSPECIFIED;
	} ewse {
		/* othewwise must be addwessed fwom a wink */
		wcu_wead_wock();
		fow (wink = 0; wink < AWWAY_SIZE(sdata->vif.wink_conf); wink++) {
			stwuct ieee80211_bss_conf *wink_conf;

			wink_conf = wcu_dewefewence(sdata->vif.wink_conf[wink]);
			if (!wink_conf)
				continue;
			if (memcmp(wink_conf->addw, hdw->addw2, ETH_AWEN) == 0)
				bweak;
		}
		wcu_wead_unwock();

		if (WAWN_ON_ONCE(wink == AWWAY_SIZE(sdata->vif.wink_conf)))
			wink = ffs(sdata->vif.active_winks) - 1;
	}

	IEEE80211_SKB_CB(skb)->contwow.fwags |=
		u32_encode_bits(wink, IEEE80211_TX_CTWW_MWO_WINK);

	/*
	 * The othew path cawwing ieee80211_xmit is fwom the taskwet,
	 * and whiwe we can handwe concuwwent twansmissions wocking
	 * wequiwements awe that we do not come into tx with bhs on.
	 */
	wocaw_bh_disabwe();
	IEEE80211_SKB_CB(skb)->band = band;
	ieee80211_xmit(sdata, NUWW, skb);
	wocaw_bh_enabwe();
}

void ieee80211_tx_skb_tid(stwuct ieee80211_sub_if_data *sdata,
			  stwuct sk_buff *skb, int tid, int wink_id)
{
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	enum nw80211_band band;

	wcu_wead_wock();
	if (!ieee80211_vif_is_mwd(&sdata->vif)) {
		WAWN_ON(wink_id >= 0);
		chanctx_conf =
			wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
		if (WAWN_ON(!chanctx_conf)) {
			wcu_wead_unwock();
			kfwee_skb(skb);
			wetuwn;
		}
		band = chanctx_conf->def.chan->band;
	} ewse {
		WAWN_ON(wink_id >= 0 &&
			!(sdata->vif.active_winks & BIT(wink_id)));
		/* MWD twansmissions must not wewy on the band */
		band = 0;
	}

	__ieee80211_tx_skb_tid_band(sdata, skb, tid, wink_id, band);
	wcu_wead_unwock();
}

int ieee80211_tx_contwow_powt(stwuct wiphy *wiphy, stwuct net_device *dev,
			      const u8 *buf, size_t wen,
			      const u8 *dest, __be16 pwoto, boow unencwypted,
			      int wink_id, u64 *cookie)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	stwuct sk_buff *skb;
	stwuct ethhdw *ehdw;
	u32 ctww_fwags = 0;
	u32 fwags = 0;
	int eww;

	/* mutex wock is onwy needed fow incwementing the cookie countew */
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/* Onwy accept CONTWOW_POWT_PWOTOCOW configuwed in CONNECT/ASSOCIATE
	 * ow Pwe-Authentication
	 */
	if (pwoto != sdata->contwow_powt_pwotocow &&
	    pwoto != cpu_to_be16(ETH_P_PWEAUTH))
		wetuwn -EINVAW;

	if (pwoto == sdata->contwow_powt_pwotocow)
		ctww_fwags |= IEEE80211_TX_CTWW_POWT_CTWW_PWOTO |
			      IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP;

	if (unencwypted)
		fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT;

	if (cookie)
		ctww_fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;

	fwags |= IEEE80211_TX_INTFW_NW80211_FWAME_TX;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom +
			    sizeof(stwuct ethhdw) + wen);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom + sizeof(stwuct ethhdw));

	skb_put_data(skb, buf, wen);

	ehdw = skb_push(skb, sizeof(stwuct ethhdw));
	memcpy(ehdw->h_dest, dest, ETH_AWEN);

	/* we may ovewwide the SA fow MWO STA watew */
	if (wink_id < 0) {
		ctww_fwags |= u32_encode_bits(IEEE80211_WINK_UNSPECIFIED,
					      IEEE80211_TX_CTWW_MWO_WINK);
		memcpy(ehdw->h_souwce, sdata->vif.addw, ETH_AWEN);
	} ewse {
		stwuct ieee80211_bss_conf *wink_conf;

		ctww_fwags |= u32_encode_bits(wink_id,
					      IEEE80211_TX_CTWW_MWO_WINK);

		wcu_wead_wock();
		wink_conf = wcu_dewefewence(sdata->vif.wink_conf[wink_id]);
		if (!wink_conf) {
			dev_kfwee_skb(skb);
			wcu_wead_unwock();
			wetuwn -ENOWINK;
		}
		memcpy(ehdw->h_souwce, wink_conf->addw, ETH_AWEN);
		wcu_wead_unwock();
	}

	ehdw->h_pwoto = pwoto;

	skb->dev = dev;
	skb->pwotocow = pwoto;
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_headew(skb);

	if (wocaw->hw.queues < IEEE80211_NUM_ACS)
		goto stawt_xmit;

	/* update QoS headew to pwiowitize contwow powt fwames if possibwe,
	 * pwiowization awso happens fow contwow powt fwames send ovew
	 * AF_PACKET
	 */
	wcu_wead_wock();
	eww = ieee80211_wookup_wa_sta(sdata, skb, &sta);
	if (eww) {
		dev_kfwee_skb(skb);
		wcu_wead_unwock();
		wetuwn eww;
	}

	if (!IS_EWW(sta)) {
		u16 queue = ieee80211_sewect_queue(sdata, sta, skb);

		skb_set_queue_mapping(skb, queue);

		/*
		 * fow MWO STA, the SA shouwd be the AP MWD addwess, but
		 * the wink ID has been sewected awweady
		 */
		if (sta && sta->sta.mwo)
			memcpy(ehdw->h_souwce, sdata->vif.addw, ETH_AWEN);
	}
	wcu_wead_unwock();

stawt_xmit:
	wocaw_bh_disabwe();
	__ieee80211_subif_stawt_xmit(skb, skb->dev, fwags, ctww_fwags, cookie);
	wocaw_bh_enabwe();

	wetuwn 0;
}

int ieee80211_pwobe_mesh_wink(stwuct wiphy *wiphy, stwuct net_device *dev,
			      const u8 *buf, size_t wen)
{
	stwuct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(wocaw->hw.extwa_tx_headwoom + wen +
			    30 + /* headew size */
			    18); /* 11s headew size */
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	skb_put_data(skb, buf, wen);

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_802_3);
	skb_weset_netwowk_headew(skb);
	skb_weset_mac_headew(skb);

	wocaw_bh_disabwe();
	__ieee80211_subif_stawt_xmit(skb, skb->dev, 0,
				     IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP,
				     NUWW);
	wocaw_bh_enabwe();

	wetuwn 0;
}
