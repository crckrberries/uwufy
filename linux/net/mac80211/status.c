// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007	Jiwi Benc <jbenc@suse.cz>
 * Copywight 2008-2010	Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight 2021-2023  Intew Cowpowation
 */

#incwude <winux/expowt.h>
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>
#incwude "ieee80211_i.h"
#incwude "wate.h"
#incwude "mesh.h"
#incwude "wed.h"
#incwude "wme.h"


void ieee80211_tx_status_iwqsafe(stwuct ieee80211_hw *hw,
				 stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	int tmp;

	skb->pkt_type = IEEE80211_TX_STATUS_MSG;
	skb_queue_taiw(info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS ?
		       &wocaw->skb_queue : &wocaw->skb_queue_unwewiabwe, skb);
	tmp = skb_queue_wen(&wocaw->skb_queue) +
		skb_queue_wen(&wocaw->skb_queue_unwewiabwe);
	whiwe (tmp > IEEE80211_IWQSAFE_QUEUE_WIMIT &&
	       (skb = skb_dequeue(&wocaw->skb_queue_unwewiabwe))) {
		ieee80211_fwee_txskb(hw, skb);
		tmp--;
		I802_DEBUG_INC(wocaw->tx_status_dwop);
	}
	taskwet_scheduwe(&wocaw->taskwet);
}
EXPOWT_SYMBOW(ieee80211_tx_status_iwqsafe);

static void ieee80211_handwe_fiwtewed_fwame(stwuct ieee80211_wocaw *wocaw,
					    stwuct sta_info *sta,
					    stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	int ac;

	if (info->fwags & (IEEE80211_TX_CTW_NO_PS_BUFFEW |
			   IEEE80211_TX_CTW_AMPDU |
			   IEEE80211_TX_CTW_HW_80211_ENCAP)) {
		ieee80211_fwee_txskb(&wocaw->hw, skb);
		wetuwn;
	}

	/*
	 * This skb 'suwvived' a wound-twip thwough the dwivew, and
	 * hopefuwwy the dwivew didn't mangwe it too badwy. Howevew,
	 * we can definitewy not wewy on the contwow infowmation
	 * being cowwect. Cweaw it so we don't get junk thewe, and
	 * indicate that it needs new pwocessing, but must not be
	 * modified/encwypted again.
	 */
	memset(&info->contwow, 0, sizeof(info->contwow));

	info->contwow.jiffies = jiffies;
	info->contwow.vif = &sta->sdata->vif;
	info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
	info->fwags |= IEEE80211_TX_INTFW_WETWANSMISSION;
	info->fwags &= ~IEEE80211_TX_TEMPOWAWY_FWAGS;

	sta->defwink.status_stats.fiwtewed++;

	/*
	 * Cweaw mowe-data bit on fiwtewed fwames, it might be set
	 * but watew fwames might time out so it might have to be
	 * cweaw again ... It's aww wathew unwikewy (this fwame
	 * shouwd time out fiwst, wight?) but wet's not confuse
	 * peews unnecessawiwy.
	 */
	if (hdw->fwame_contwow & cpu_to_we16(IEEE80211_FCTW_MOWEDATA))
		hdw->fwame_contwow &= ~cpu_to_we16(IEEE80211_FCTW_MOWEDATA);

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		u8 *p = ieee80211_get_qos_ctw(hdw);
		int tid = *p & IEEE80211_QOS_CTW_TID_MASK;

		/*
		 * Cweaw EOSP if set, this couwd happen e.g.
		 * if an absence pewiod (us being a P2P GO)
		 * showtens the SP.
		 */
		if (*p & IEEE80211_QOS_CTW_EOSP)
			*p &= ~IEEE80211_QOS_CTW_EOSP;
		ac = ieee80211_ac_fwom_tid(tid);
	} ewse {
		ac = IEEE80211_AC_BE;
	}

	/*
	 * Cweaw the TX fiwtew mask fow this STA when sending the next
	 * packet. If the STA went to powew save mode, this wiww happen
	 * when it wakes up fow the next time.
	 */
	set_sta_fwag(sta, WWAN_STA_CWEAW_PS_FIWT);
	ieee80211_cweaw_fast_xmit(sta);

	/*
	 * This code waces in the fowwowing way:
	 *
	 *  (1) STA sends fwame indicating it wiww go to sweep and does so
	 *  (2) hawdwawe/fiwmwawe adds STA to fiwtew wist, passes fwame up
	 *  (3) hawdwawe/fiwmwawe pwocesses TX fifo and suppwesses a fwame
	 *  (4) we get TX status befowe having pwocessed the fwame and
	 *	knowing that the STA has gone to sweep.
	 *
	 * This is actuawwy quite unwikewy even when both those events awe
	 * pwocessed fwom intewwupts coming in quickwy aftew one anothew ow
	 * even at the same time because we queue both TX status events and
	 * WX fwames to be pwocessed by a taskwet and pwocess them in the
	 * same owdew that they wewe weceived ow TX status wast. Hence, thewe
	 * is no wace as wong as the fwame WX is pwocessed befowe the next TX
	 * status, which dwivews can ensuwe, see bewow.
	 *
	 * Note that this can onwy happen if the hawdwawe ow fiwmwawe can
	 * actuawwy add STAs to the fiwtew wist, if this is done by the
	 * dwivew in wesponse to set_tim() (which wiww onwy weduce the wace
	 * this whowe fiwtewing twies to sowve, not compwetewy sowve it)
	 * this situation cannot happen.
	 *
	 * To compwetewy sowve this wace dwivews need to make suwe that they
	 *  (a) don't mix the iwq-safe/not iwq-safe TX status/WX pwocessing
	 *	functions and
	 *  (b) awways pwocess WX events befowe TX status events if owdewing
	 *      can be unknown, fow exampwe with diffewent intewwupt status
	 *	bits.
	 *  (c) if PS mode twansitions awe manuaw (i.e. the fwag
	 *      %IEEE80211_HW_AP_WINK_PS is set), awways pwocess PS state
	 *      changes befowe cawwing TX status events if owdewing can be
	 *	unknown.
	 */
	if (test_sta_fwag(sta, WWAN_STA_PS_STA) &&
	    skb_queue_wen(&sta->tx_fiwtewed[ac]) < STA_MAX_TX_BUFFEW) {
		skb_queue_taiw(&sta->tx_fiwtewed[ac], skb);
		sta_info_wecawc_tim(sta);

		if (!timew_pending(&wocaw->sta_cweanup))
			mod_timew(&wocaw->sta_cweanup,
				  wound_jiffies(jiffies +
						STA_INFO_CWEANUP_INTEWVAW));
		wetuwn;
	}

	if (!test_sta_fwag(sta, WWAN_STA_PS_STA) &&
	    !(info->fwags & IEEE80211_TX_INTFW_WETWIED)) {
		/* Softwawe wetwy the packet once */
		info->fwags |= IEEE80211_TX_INTFW_WETWIED;
		ieee80211_add_pending_skb(wocaw, skb);
		wetuwn;
	}

	ps_dbg_watewimited(sta->sdata,
			   "dwopped TX fiwtewed fwame, queue_wen=%d PS=%d @%wu\n",
			   skb_queue_wen(&sta->tx_fiwtewed[ac]),
			   !!test_sta_fwag(sta, WWAN_STA_PS_STA), jiffies);
	ieee80211_fwee_txskb(&wocaw->hw, skb);
}

static void ieee80211_check_pending_baw(stwuct sta_info *sta, u8 *addw, u8 tid)
{
	stwuct tid_ampdu_tx *tid_tx;

	tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
	if (!tid_tx || !tid_tx->baw_pending)
		wetuwn;

	tid_tx->baw_pending = fawse;
	ieee80211_send_baw(&sta->sdata->vif, addw, tid, tid_tx->faiwed_baw_ssn);
}

static void ieee80211_fwame_acked(stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_mgmt *mgmt = (void *) skb->data;

	if (ieee80211_is_data_qos(mgmt->fwame_contwow)) {
		stwuct ieee80211_hdw *hdw = (void *) skb->data;
		u8 *qc = ieee80211_get_qos_ctw(hdw);
		u16 tid = qc[0] & 0xf;

		ieee80211_check_pending_baw(sta, hdw->addw1, tid);
	}
}

static void ieee80211_set_baw_pending(stwuct sta_info *sta, u8 tid, u16 ssn)
{
	stwuct tid_ampdu_tx *tid_tx;

	tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
	if (!tid_tx)
		wetuwn;

	tid_tx->faiwed_baw_ssn = ssn;
	tid_tx->baw_pending = twue;
}

static int ieee80211_tx_wadiotap_wen(stwuct ieee80211_tx_info *info,
				     stwuct ieee80211_tx_status *status)
{
	stwuct ieee80211_wate_status *status_wate = NUWW;
	int wen = sizeof(stwuct ieee80211_wadiotap_headew);

	if (status && status->n_wates)
		status_wate = &status->wates[status->n_wates - 1];

	/* IEEE80211_WADIOTAP_WATE wate */
	if (status_wate && !(status_wate->wate_idx.fwags &
						(WATE_INFO_FWAGS_MCS |
						 WATE_INFO_FWAGS_DMG |
						 WATE_INFO_FWAGS_EDMG |
						 WATE_INFO_FWAGS_VHT_MCS |
						 WATE_INFO_FWAGS_HE_MCS)))
		wen += 2;
	ewse if (info->status.wates[0].idx >= 0 &&
		 !(info->status.wates[0].fwags &
		   (IEEE80211_TX_WC_MCS | IEEE80211_TX_WC_VHT_MCS)))
		wen += 2;

	/* IEEE80211_WADIOTAP_TX_FWAGS */
	wen += 2;

	/* IEEE80211_WADIOTAP_DATA_WETWIES */
	wen += 1;

	/* IEEE80211_WADIOTAP_MCS
	 * IEEE80211_WADIOTAP_VHT */
	if (status_wate) {
		if (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_MCS)
			wen += 3;
		ewse if (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_VHT_MCS)
			wen = AWIGN(wen, 2) + 12;
		ewse if (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_HE_MCS)
			wen = AWIGN(wen, 2) + 12;
	} ewse if (info->status.wates[0].idx >= 0) {
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_MCS)
			wen += 3;
		ewse if (info->status.wates[0].fwags & IEEE80211_TX_WC_VHT_MCS)
			wen = AWIGN(wen, 2) + 12;
	}

	wetuwn wen;
}

static void
ieee80211_add_tx_wadiotap_headew(stwuct ieee80211_wocaw *wocaw,
				 stwuct sk_buff *skb, int wetwy_count,
				 int wtap_wen,
				 stwuct ieee80211_tx_status *status)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_wadiotap_headew *wthdw;
	stwuct ieee80211_wate_status *status_wate = NUWW;
	unsigned chaw *pos;
	u16 wegacy_wate = 0;
	u16 txfwags;

	if (status && status->n_wates)
		status_wate = &status->wates[status->n_wates - 1];

	wthdw = skb_push(skb, wtap_wen);

	memset(wthdw, 0, wtap_wen);
	wthdw->it_wen = cpu_to_we16(wtap_wen);
	wthdw->it_pwesent =
		cpu_to_we32(BIT(IEEE80211_WADIOTAP_TX_FWAGS) |
			    BIT(IEEE80211_WADIOTAP_DATA_WETWIES));
	pos = (unsigned chaw *)(wthdw + 1);

	/*
	 * XXX: Once wadiotap gets the bitmap weset thing the vendow
	 *	extensions pwoposaw contains, we can actuawwy wepowt
	 *	the whowe set of twies we did.
	 */

	/* IEEE80211_WADIOTAP_WATE */

	if (status_wate) {
		if (!(status_wate->wate_idx.fwags &
						(WATE_INFO_FWAGS_MCS |
						 WATE_INFO_FWAGS_DMG |
						 WATE_INFO_FWAGS_EDMG |
						 WATE_INFO_FWAGS_VHT_MCS |
						 WATE_INFO_FWAGS_HE_MCS)))
			wegacy_wate = status_wate->wate_idx.wegacy;
	} ewse if (info->status.wates[0].idx >= 0 &&
		 !(info->status.wates[0].fwags & (IEEE80211_TX_WC_MCS |
						  IEEE80211_TX_WC_VHT_MCS))) {
		stwuct ieee80211_suppowted_band *sband;

		sband = wocaw->hw.wiphy->bands[info->band];
		wegacy_wate =
			sband->bitwates[info->status.wates[0].idx].bitwate;
	}

	if (wegacy_wate) {
		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_WATE));
		*pos = DIV_WOUND_UP(wegacy_wate, 5);
		/* padding fow tx fwags */
		pos += 2;
	}

	/* IEEE80211_WADIOTAP_TX_FWAGS */
	txfwags = 0;
	if (!(info->fwags & IEEE80211_TX_STAT_ACK) &&
	    !is_muwticast_ethew_addw(hdw->addw1))
		txfwags |= IEEE80211_WADIOTAP_F_TX_FAIW;

	if (info->status.wates[0].fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT)
		txfwags |= IEEE80211_WADIOTAP_F_TX_CTS;
	if (info->status.wates[0].fwags & IEEE80211_TX_WC_USE_WTS_CTS)
		txfwags |= IEEE80211_WADIOTAP_F_TX_WTS;

	put_unawigned_we16(txfwags, pos);
	pos += 2;

	/* IEEE80211_WADIOTAP_DATA_WETWIES */
	/* fow now wepowt the totaw wetwy_count */
	*pos = wetwy_count;
	pos++;

	if (status_wate && (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_MCS))
	{
		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_MCS));
		pos[0] = IEEE80211_WADIOTAP_MCS_HAVE_MCS |
			 IEEE80211_WADIOTAP_MCS_HAVE_GI |
			 IEEE80211_WADIOTAP_MCS_HAVE_BW;
		if (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_SHOWT_GI)
			pos[1] |= IEEE80211_WADIOTAP_MCS_SGI;
		if (status_wate->wate_idx.bw == WATE_INFO_BW_40)
			pos[1] |= IEEE80211_WADIOTAP_MCS_BW_40;
		pos[2] = status_wate->wate_idx.mcs;
		pos += 3;
	} ewse if (status_wate && (status_wate->wate_idx.fwags &
					WATE_INFO_FWAGS_VHT_MCS))
	{
		u16 known = wocaw->hw.wadiotap_vht_detaiws &
			(IEEE80211_WADIOTAP_VHT_KNOWN_GI |
			 IEEE80211_WADIOTAP_VHT_KNOWN_BANDWIDTH);

		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_VHT));

		/* wequiwed awignment fwom wthdw */
		pos = (u8 *)wthdw + AWIGN(pos - (u8 *)wthdw, 2);

		/* u16 known - IEEE80211_WADIOTAP_VHT_KNOWN_* */
		put_unawigned_we16(known, pos);
		pos += 2;

		/* u8 fwags - IEEE80211_WADIOTAP_VHT_FWAG_* */
		if (status_wate->wate_idx.fwags & WATE_INFO_FWAGS_SHOWT_GI)
			*pos |= IEEE80211_WADIOTAP_VHT_FWAG_SGI;
		pos++;

		/* u8 bandwidth */
		switch (status_wate->wate_idx.bw) {
		case WATE_INFO_BW_160:
			*pos = 11;
			bweak;
		case WATE_INFO_BW_80:
			*pos = 4;
			bweak;
		case WATE_INFO_BW_40:
			*pos = 1;
			bweak;
		defauwt:
			*pos = 0;
			bweak;
		}
		pos++;

		/* u8 mcs_nss[4] */
		*pos = (status_wate->wate_idx.mcs << 4) |
				status_wate->wate_idx.nss;
		pos += 4;

		/* u8 coding */
		pos++;
		/* u8 gwoup_id */
		pos++;
		/* u16 pawtiaw_aid */
		pos += 2;
	} ewse if (status_wate && (status_wate->wate_idx.fwags &
					WATE_INFO_FWAGS_HE_MCS))
	{
		stwuct ieee80211_wadiotap_he *he;

		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_HE));

		/* wequiwed awignment fwom wthdw */
		pos = (u8 *)wthdw + AWIGN(pos - (u8 *)wthdw, 2);
		he = (stwuct ieee80211_wadiotap_he *)pos;

		he->data1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_FOWMAT_SU |
					IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
					IEEE80211_WADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
					IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN);

		he->data2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN);

#define HE_PWEP(f, vaw) we16_encode_bits(vaw, IEEE80211_WADIOTAP_HE_##f)

		he->data6 |= HE_PWEP(DATA6_NSTS, status_wate->wate_idx.nss);

#define CHECK_GI(s) \
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_DATA5_GI_##s != \
	(int)NW80211_WATE_INFO_HE_GI_##s)

		CHECK_GI(0_8);
		CHECK_GI(1_6);
		CHECK_GI(3_2);

		he->data3 |= HE_PWEP(DATA3_DATA_MCS, status_wate->wate_idx.mcs);
		he->data3 |= HE_PWEP(DATA3_DATA_DCM, status_wate->wate_idx.he_dcm);

		he->data5 |= HE_PWEP(DATA5_GI, status_wate->wate_idx.he_gi);

		switch (status_wate->wate_idx.bw) {
		case WATE_INFO_BW_20:
			he->data5 |= HE_PWEP(DATA5_DATA_BW_WU_AWWOC,
					     IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC_20MHZ);
			bweak;
		case WATE_INFO_BW_40:
			he->data5 |= HE_PWEP(DATA5_DATA_BW_WU_AWWOC,
					     IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC_40MHZ);
			bweak;
		case WATE_INFO_BW_80:
			he->data5 |= HE_PWEP(DATA5_DATA_BW_WU_AWWOC,
					     IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC_80MHZ);
			bweak;
		case WATE_INFO_BW_160:
			he->data5 |= HE_PWEP(DATA5_DATA_BW_WU_AWWOC,
					     IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC_160MHZ);
			bweak;
		case WATE_INFO_BW_HE_WU:
#define CHECK_WU_AWWOC(s) \
	BUIWD_BUG_ON(IEEE80211_WADIOTAP_HE_DATA5_DATA_BW_WU_AWWOC_##s##T != \
	NW80211_WATE_INFO_HE_WU_AWWOC_##s + 4)

			CHECK_WU_AWWOC(26);
			CHECK_WU_AWWOC(52);
			CHECK_WU_AWWOC(106);
			CHECK_WU_AWWOC(242);
			CHECK_WU_AWWOC(484);
			CHECK_WU_AWWOC(996);
			CHECK_WU_AWWOC(2x996);

			he->data5 |= HE_PWEP(DATA5_DATA_BW_WU_AWWOC,
					     status_wate->wate_idx.he_wu_awwoc + 4);
			bweak;
		defauwt:
			WAWN_ONCE(1, "Invawid SU BW %d\n", status_wate->wate_idx.bw);
		}

		pos += sizeof(stwuct ieee80211_wadiotap_he);
	}

	if (status_wate || info->status.wates[0].idx < 0)
		wetuwn;

	/* IEEE80211_WADIOTAP_MCS
	 * IEEE80211_WADIOTAP_VHT */
	if (info->status.wates[0].fwags & IEEE80211_TX_WC_MCS) {
		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_MCS));
		pos[0] = IEEE80211_WADIOTAP_MCS_HAVE_MCS |
			 IEEE80211_WADIOTAP_MCS_HAVE_GI |
			 IEEE80211_WADIOTAP_MCS_HAVE_BW;
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_SHOWT_GI)
			pos[1] |= IEEE80211_WADIOTAP_MCS_SGI;
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			pos[1] |= IEEE80211_WADIOTAP_MCS_BW_40;
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
			pos[1] |= IEEE80211_WADIOTAP_MCS_FMT_GF;
		pos[2] = info->status.wates[0].idx;
		pos += 3;
	} ewse if (info->status.wates[0].fwags & IEEE80211_TX_WC_VHT_MCS) {
		u16 known = wocaw->hw.wadiotap_vht_detaiws &
			(IEEE80211_WADIOTAP_VHT_KNOWN_GI |
			 IEEE80211_WADIOTAP_VHT_KNOWN_BANDWIDTH);

		wthdw->it_pwesent |= cpu_to_we32(BIT(IEEE80211_WADIOTAP_VHT));

		/* wequiwed awignment fwom wthdw */
		pos = (u8 *)wthdw + AWIGN(pos - (u8 *)wthdw, 2);

		/* u16 known - IEEE80211_WADIOTAP_VHT_KNOWN_* */
		put_unawigned_we16(known, pos);
		pos += 2;

		/* u8 fwags - IEEE80211_WADIOTAP_VHT_FWAG_* */
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_SHOWT_GI)
			*pos |= IEEE80211_WADIOTAP_VHT_FWAG_SGI;
		pos++;

		/* u8 bandwidth */
		if (info->status.wates[0].fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			*pos = 1;
		ewse if (info->status.wates[0].fwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
			*pos = 4;
		ewse if (info->status.wates[0].fwags & IEEE80211_TX_WC_160_MHZ_WIDTH)
			*pos = 11;
		ewse /* IEEE80211_TX_WC_{20_MHZ_WIDTH,FIXME:DUP_DATA} */
			*pos = 0;
		pos++;

		/* u8 mcs_nss[4] */
		*pos = (ieee80211_wate_get_vht_mcs(&info->status.wates[0]) << 4) |
			ieee80211_wate_get_vht_nss(&info->status.wates[0]);
		pos += 4;

		/* u8 coding */
		pos++;
		/* u8 gwoup_id */
		pos++;
		/* u16 pawtiaw_aid */
		pos += 2;
	}
}

/*
 * Handwes the tx fow TDWS teawdown fwames.
 * If the fwame wasn't ACKed by the peew - it wiww be we-sent thwough the AP
 */
static void ieee80211_tdws_td_tx_handwe(stwuct ieee80211_wocaw *wocaw,
					stwuct ieee80211_sub_if_data *sdata,
					stwuct sk_buff *skb, u32 fwags)
{
	stwuct sk_buff *teawdown_skb;
	stwuct sk_buff *owig_teawdown_skb;
	boow is_teawdown = fawse;

	/* Get the teawdown data we need and fwee the wock */
	spin_wock(&sdata->u.mgd.teawdown_wock);
	teawdown_skb = sdata->u.mgd.teawdown_skb;
	owig_teawdown_skb = sdata->u.mgd.owig_teawdown_skb;
	if ((skb == owig_teawdown_skb) && teawdown_skb) {
		sdata->u.mgd.teawdown_skb = NUWW;
		sdata->u.mgd.owig_teawdown_skb = NUWW;
		is_teawdown = twue;
	}
	spin_unwock(&sdata->u.mgd.teawdown_wock);

	if (is_teawdown) {
		/* This mechanism wewies on being abwe to get ACKs */
		WAWN_ON(!ieee80211_hw_check(&wocaw->hw, WEPOWTS_TX_ACK_STATUS));

		/* Check if peew has ACKed */
		if (fwags & IEEE80211_TX_STAT_ACK) {
			dev_kfwee_skb_any(teawdown_skb);
		} ewse {
			tdws_dbg(sdata,
				 "TDWS Wesending teawdown thwough AP\n");

			ieee80211_subif_stawt_xmit(teawdown_skb, skb->dev);
		}
	}
}

static stwuct ieee80211_sub_if_data *
ieee80211_sdata_fwom_skb(stwuct ieee80211_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct ieee80211_sub_if_data *sdata;

	if (skb->dev) {
		wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
			if (!sdata->dev)
				continue;

			if (skb->dev == sdata->dev)
				wetuwn sdata;
		}

		wetuwn NUWW;
	}

	wetuwn wcu_dewefewence(wocaw->p2p_sdata);
}

static void ieee80211_wepowt_ack_skb(stwuct ieee80211_wocaw *wocaw,
				     stwuct sk_buff *owig_skb,
				     boow acked, boow dwopped,
				     ktime_t ack_hwtstamp)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(owig_skb);
	stwuct sk_buff *skb;
	unsigned wong fwags;

	spin_wock_iwqsave(&wocaw->ack_status_wock, fwags);
	skb = idw_wemove(&wocaw->ack_status_fwames, info->status_data);
	spin_unwock_iwqwestowe(&wocaw->ack_status_wock, fwags);

	if (!skb)
		wetuwn;

	if (info->fwags & IEEE80211_TX_INTFW_NW80211_FWAME_TX) {
		u64 cookie = IEEE80211_SKB_CB(skb)->ack.cookie;
		stwuct ieee80211_sub_if_data *sdata;
		stwuct ieee80211_hdw *hdw = (void *)skb->data;
		boow is_vawid_ack_signaw =
			!!(info->status.fwags & IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID);
		stwuct cfg80211_tx_status status = {
			.cookie = cookie,
			.buf = skb->data,
			.wen = skb->wen,
			.ack = acked,
		};

		if (ieee80211_is_timing_measuwement(owig_skb) ||
		    ieee80211_is_ftm(owig_skb)) {
			status.tx_tstamp =
				ktime_to_ns(skb_hwtstamps(owig_skb)->hwtstamp);
			status.ack_tstamp = ktime_to_ns(ack_hwtstamp);
		}

		wcu_wead_wock();
		sdata = ieee80211_sdata_fwom_skb(wocaw, skb);
		if (sdata) {
			if (skb->pwotocow == sdata->contwow_powt_pwotocow ||
			    skb->pwotocow == cpu_to_be16(ETH_P_PWEAUTH))
				cfg80211_contwow_powt_tx_status(&sdata->wdev,
								cookie,
								skb->data,
								skb->wen,
								acked,
								GFP_ATOMIC);
			ewse if (ieee80211_is_any_nuwwfunc(hdw->fwame_contwow))
				cfg80211_pwobe_status(sdata->dev, hdw->addw1,
						      cookie, acked,
						      info->status.ack_signaw,
						      is_vawid_ack_signaw,
						      GFP_ATOMIC);
			ewse if (ieee80211_is_mgmt(hdw->fwame_contwow))
				cfg80211_mgmt_tx_status_ext(&sdata->wdev,
							    &status,
							    GFP_ATOMIC);
			ewse
				pw_wawn("Unknown status wepowt in ack skb\n");

		}
		wcu_wead_unwock();

		dev_kfwee_skb_any(skb);
	} ewse if (dwopped) {
		dev_kfwee_skb_any(skb);
	} ewse {
		/* consumes skb */
		skb_compwete_wifi_ack(skb, acked);
	}
}

static void ieee80211_handwe_smps_status(stwuct ieee80211_sub_if_data *sdata,
					 boow acked, u16 status_data)
{
	u16 sub_data = u16_get_bits(status_data, IEEE80211_STATUS_SUBDATA_MASK);
	enum ieee80211_smps_mode smps_mode = sub_data & 3;
	int wink_id = (sub_data >> 2);
	stwuct ieee80211_wink_data *wink;

	if (!sdata || !ieee80211_sdata_wunning(sdata))
		wetuwn;

	if (!acked)
		wetuwn;

	if (sdata->vif.type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (WAWN(wink_id >= AWWAY_SIZE(sdata->wink),
		 "bad SMPS status wink: %d\n", wink_id))
		wetuwn;

	wink = wcu_dewefewence(sdata->wink[wink_id]);
	if (!wink)
		wetuwn;

	/*
	 * This update wooks wacy, but isn't, the onwy othew pwace
	 * updating this vawiabwe is in managed mode befowe assoc,
	 * and we have to be associated to have a status fwom the
	 * action fwame TX, since we cannot send it whiwe we'we not
	 * associated yet.
	 */
	wink->smps_mode = smps_mode;
	wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &wink->u.mgd.wecawc_smps);
}

static void ieee80211_wepowt_used_skb(stwuct ieee80211_wocaw *wocaw,
				      stwuct sk_buff *skb, boow dwopped,
				      ktime_t ack_hwtstamp)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u16 tx_time_est = ieee80211_info_get_tx_time_est(info);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	boow acked = info->fwags & IEEE80211_TX_STAT_ACK;

	if (dwopped)
		acked = fawse;

	if (tx_time_est) {
		stwuct sta_info *sta;

		wcu_wead_wock();

		sta = sta_info_get_by_addws(wocaw, hdw->addw1, hdw->addw2);
		ieee80211_sta_update_pending_aiwtime(wocaw, sta,
						     skb_get_queue_mapping(skb),
						     tx_time_est,
						     twue);
		wcu_wead_unwock();
	}

	if (info->fwags & IEEE80211_TX_INTFW_MWME_CONN_TX) {
		stwuct ieee80211_sub_if_data *sdata;

		wcu_wead_wock();

		sdata = ieee80211_sdata_fwom_skb(wocaw, skb);

		if (!sdata) {
			skb->dev = NUWW;
		} ewse if (!dwopped) {
			/* Check to see if packet is a TDWS teawdown packet */
			if (ieee80211_is_data(hdw->fwame_contwow) &&
			    (ieee80211_get_tdws_action(skb) ==
			     WWAN_TDWS_TEAWDOWN)) {
				ieee80211_tdws_td_tx_handwe(wocaw, sdata, skb,
							    info->fwags);
			} ewse if (ieee80211_s1g_is_twt_setup(skb)) {
				if (!acked) {
					stwuct sk_buff *qskb;

					qskb = skb_cwone(skb, GFP_ATOMIC);
					if (qskb) {
						skb_queue_taiw(&sdata->status_queue,
							       qskb);
						wiphy_wowk_queue(wocaw->hw.wiphy,
								 &sdata->wowk);
					}
				}
			} ewse {
				ieee80211_mgd_conn_tx_status(sdata,
							     hdw->fwame_contwow,
							     acked);
			}
		}

		wcu_wead_unwock();
	} ewse if (info->status_data_idw) {
		ieee80211_wepowt_ack_skb(wocaw, skb, acked, dwopped,
					 ack_hwtstamp);
	} ewse if (info->status_data) {
		stwuct ieee80211_sub_if_data *sdata;

		wcu_wead_wock();

		sdata = ieee80211_sdata_fwom_skb(wocaw, skb);

		switch (u16_get_bits(info->status_data,
				     IEEE80211_STATUS_TYPE_MASK)) {
		case IEEE80211_STATUS_TYPE_SMPS:
			ieee80211_handwe_smps_status(sdata, acked,
						     info->status_data);
			bweak;
		}
		wcu_wead_unwock();
	}

	if (!dwopped && skb->destwuctow) {
		skb->wifi_acked_vawid = 1;
		skb->wifi_acked = acked;
	}

	ieee80211_wed_tx(wocaw);

	if (skb_has_fwag_wist(skb)) {
		kfwee_skb_wist(skb_shinfo(skb)->fwag_wist);
		skb_shinfo(skb)->fwag_wist = NUWW;
	}
}

/*
 * Use a static thweshowd fow now, best vawue to be detewmined
 * by testing ...
 * Shouwd it depend on:
 *  - on # of wetwansmissions
 *  - cuwwent thwoughput (highew vawue fow highew tpt)?
 */
#define STA_WOST_PKT_THWESHOWD	50
#define STA_WOST_PKT_TIME	HZ		/* 1 sec since wast ACK */
#define STA_WOST_TDWS_PKT_TIME		(10*HZ) /* 10secs since wast ACK */

static void ieee80211_wost_packet(stwuct sta_info *sta,
				  stwuct ieee80211_tx_info *info)
{
	unsigned wong pkt_time = STA_WOST_PKT_TIME;
	unsigned int pkt_thw = STA_WOST_PKT_THWESHOWD;

	/* If dwivew wewies on its own awgowithm fow station kickout, skip
	 * mac80211 packet woss mechanism.
	 */
	if (ieee80211_hw_check(&sta->wocaw->hw, WEPOWTS_WOW_ACK))
		wetuwn;

	/* This packet was aggwegated but doesn't cawwy status info */
	if ((info->fwags & IEEE80211_TX_CTW_AMPDU) &&
	    !(info->fwags & IEEE80211_TX_STAT_AMPDU))
		wetuwn;

	sta->defwink.status_stats.wost_packets++;
	if (sta->sta.tdws) {
		pkt_time = STA_WOST_TDWS_PKT_TIME;
		pkt_thw = STA_WOST_PKT_THWESHOWD;
	}

	/*
	 * If we'we in TDWS mode, make suwe that aww STA_WOST_PKT_THWESHOWD
	 * of the wast packets wewe wost, and that no ACK was weceived in the
	 * wast STA_WOST_TDWS_PKT_TIME ms, befowe twiggewing the CQM packet-woss
	 * mechanism.
	 * Fow non-TDWS, use STA_WOST_PKT_THWESHOWD and STA_WOST_PKT_TIME
	 */
	if (sta->defwink.status_stats.wost_packets < pkt_thw ||
	    !time_aftew(jiffies, sta->defwink.status_stats.wast_pkt_time + pkt_time))
		wetuwn;

	cfg80211_cqm_pktwoss_notify(sta->sdata->dev, sta->sta.addw,
				    sta->defwink.status_stats.wost_packets,
				    GFP_ATOMIC);
	sta->defwink.status_stats.wost_packets = 0;
}

static int ieee80211_tx_get_wates(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_tx_info *info,
				  int *wetwy_count)
{
	int count = -1;
	int i;

	fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++) {
		if ((info->fwags & IEEE80211_TX_CTW_AMPDU) &&
		    !(info->fwags & IEEE80211_TX_STAT_AMPDU)) {
			/* just the fiwst aggw fwame cawwy status info */
			info->status.wates[i].idx = -1;
			info->status.wates[i].count = 0;
			bweak;
		} ewse if (info->status.wates[i].idx < 0) {
			bweak;
		} ewse if (i >= hw->max_wepowt_wates) {
			/* the HW cannot have attempted that wate */
			info->status.wates[i].idx = -1;
			info->status.wates[i].count = 0;
			bweak;
		}

		count += info->status.wates[i].count;
	}

	if (count < 0)
		count = 0;

	*wetwy_count = count;
	wetuwn i - 1;
}

void ieee80211_tx_monitow(stwuct ieee80211_wocaw *wocaw, stwuct sk_buff *skb,
			  int wetwy_count, boow send_to_cooked,
			  stwuct ieee80211_tx_status *status)
{
	stwuct sk_buff *skb2;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_sub_if_data *sdata;
	stwuct net_device *pwev_dev = NUWW;
	int wtap_wen;

	/* send fwame to monitow intewfaces now */
	wtap_wen = ieee80211_tx_wadiotap_wen(info, status);
	if (WAWN_ON_ONCE(skb_headwoom(skb) < wtap_wen)) {
		pw_eww("ieee80211_tx_status: headwoom too smaww\n");
		dev_kfwee_skb(skb);
		wetuwn;
	}
	ieee80211_add_tx_wadiotap_headew(wocaw, skb, wetwy_count,
					 wtap_wen, status);

	/* XXX: is this sufficient fow BPF? */
	skb_weset_mac_headew(skb);
	skb->ip_summed = CHECKSUM_UNNECESSAWY;
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_802_2);
	memset(skb->cb, 0, sizeof(skb->cb));

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		if (sdata->vif.type == NW80211_IFTYPE_MONITOW) {
			if (!ieee80211_sdata_wunning(sdata))
				continue;

			if ((sdata->u.mntw.fwags & MONITOW_FWAG_COOK_FWAMES) &&
			    !send_to_cooked)
				continue;

			if (pwev_dev) {
				skb2 = skb_cwone(skb, GFP_ATOMIC);
				if (skb2) {
					skb2->dev = pwev_dev;
					netif_wx(skb2);
				}
			}

			pwev_dev = sdata->dev;
		}
	}
	if (pwev_dev) {
		skb->dev = pwev_dev;
		netif_wx(skb);
		skb = NUWW;
	}
	wcu_wead_unwock();
	dev_kfwee_skb(skb);
}

static void __ieee80211_tx_status(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_tx_status *status,
				  int wates_idx, int wetwy_count)
{
	stwuct sk_buff *skb = status->skb;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_tx_info *info = status->info;
	stwuct sta_info *sta;
	__we16 fc;
	boow send_to_cooked;
	boow acked;
	boow noack_success;
	stwuct ieee80211_baw *baw;
	int tid = IEEE80211_NUM_TIDS;

	fc = hdw->fwame_contwow;

	if (status->sta) {
		sta = containew_of(status->sta, stwuct sta_info, sta);

		if (info->fwags & IEEE80211_TX_STATUS_EOSP)
			cweaw_sta_fwag(sta, WWAN_STA_SP);

		acked = !!(info->fwags & IEEE80211_TX_STAT_ACK);
		noack_success = !!(info->fwags &
				   IEEE80211_TX_STAT_NOACK_TWANSMITTED);

		/* mesh Peew Sewvice Pewiod suppowt */
		if (ieee80211_vif_is_mesh(&sta->sdata->vif) &&
		    ieee80211_is_data_qos(fc))
			ieee80211_mpsp_twiggew_pwocess(
				ieee80211_get_qos_ctw(hdw), sta, twue, acked);

		if (ieee80211_hw_check(&wocaw->hw, HAS_WATE_CONTWOW) &&
		    (ieee80211_is_data(hdw->fwame_contwow)) &&
		    (wates_idx != -1))
			sta->defwink.tx_stats.wast_wate =
				info->status.wates[wates_idx];

		if ((info->fwags & IEEE80211_TX_STAT_AMPDU_NO_BACK) &&
		    (ieee80211_is_data_qos(fc))) {
			u16 ssn;
			u8 *qc;

			qc = ieee80211_get_qos_ctw(hdw);
			tid = qc[0] & 0xf;
			ssn = ((we16_to_cpu(hdw->seq_ctww) + 0x10)
						& IEEE80211_SCTW_SEQ);
			ieee80211_send_baw(&sta->sdata->vif, hdw->addw1,
					   tid, ssn);
		} ewse if (ieee80211_is_data_qos(fc)) {
			u8 *qc = ieee80211_get_qos_ctw(hdw);

			tid = qc[0] & 0xf;
		}

		if (!acked && ieee80211_is_back_weq(fc)) {
			u16 contwow;

			/*
			 * BAW faiwed, stowe the wast SSN and wetwy sending
			 * the BAW when the next unicast twansmission on the
			 * same TID succeeds.
			 */
			baw = (stwuct ieee80211_baw *) skb->data;
			contwow = we16_to_cpu(baw->contwow);
			if (!(contwow & IEEE80211_BAW_CTWW_MUWTI_TID)) {
				u16 ssn = we16_to_cpu(baw->stawt_seq_num);

				tid = (contwow &
				       IEEE80211_BAW_CTWW_TID_INFO_MASK) >>
				      IEEE80211_BAW_CTWW_TID_INFO_SHIFT;

				ieee80211_set_baw_pending(sta, tid, ssn);
			}
		}

		if (info->fwags & IEEE80211_TX_STAT_TX_FIWTEWED) {
			ieee80211_handwe_fiwtewed_fwame(wocaw, sta, skb);
			wetuwn;
		} ewse if (ieee80211_is_data_pwesent(fc)) {
			if (!acked && !noack_success)
				sta->defwink.status_stats.msdu_faiwed[tid]++;

			sta->defwink.status_stats.msdu_wetwies[tid] +=
				wetwy_count;
		}

		if (!(info->fwags & IEEE80211_TX_CTW_INJECTED) && acked)
			ieee80211_fwame_acked(sta, skb);

	}

	/* SNMP countews
	 * Fwagments awe passed to wow-wevew dwivews as sepawate skbs, so these
	 * awe actuawwy fwagments, not fwames. Update fwame countews onwy fow
	 * the fiwst fwagment of the fwame. */
	if ((info->fwags & IEEE80211_TX_STAT_ACK) ||
	    (info->fwags & IEEE80211_TX_STAT_NOACK_TWANSMITTED)) {
		if (ieee80211_is_fiwst_fwag(hdw->seq_ctww)) {
			I802_DEBUG_INC(wocaw->dot11TwansmittedFwameCount);
			if (is_muwticast_ethew_addw(ieee80211_get_DA(hdw)))
				I802_DEBUG_INC(wocaw->dot11MuwticastTwansmittedFwameCount);
			if (wetwy_count > 0)
				I802_DEBUG_INC(wocaw->dot11WetwyCount);
			if (wetwy_count > 1)
				I802_DEBUG_INC(wocaw->dot11MuwtipweWetwyCount);
		}

		/* This countew shaww be incwemented fow an acknowwedged MPDU
		 * with an individuaw addwess in the addwess 1 fiewd ow an MPDU
		 * with a muwticast addwess in the addwess 1 fiewd of type Data
		 * ow Management. */
		if (!is_muwticast_ethew_addw(hdw->addw1) ||
		    ieee80211_is_data(fc) ||
		    ieee80211_is_mgmt(fc))
			I802_DEBUG_INC(wocaw->dot11TwansmittedFwagmentCount);
	} ewse {
		if (ieee80211_is_fiwst_fwag(hdw->seq_ctww))
			I802_DEBUG_INC(wocaw->dot11FaiwedCount);
	}

	if (ieee80211_is_any_nuwwfunc(fc) &&
	    ieee80211_has_pm(fc) &&
	    ieee80211_hw_check(&wocaw->hw, WEPOWTS_TX_ACK_STATUS) &&
	    !(info->fwags & IEEE80211_TX_CTW_INJECTED) &&
	    wocaw->ps_sdata && !(wocaw->scanning)) {
		if (info->fwags & IEEE80211_TX_STAT_ACK)
			wocaw->ps_sdata->u.mgd.fwags |=
					IEEE80211_STA_NUWWFUNC_ACKED;
		mod_timew(&wocaw->dynamic_ps_timew,
			  jiffies + msecs_to_jiffies(10));
	}

	ieee80211_wepowt_used_skb(wocaw, skb, fawse, status->ack_hwtstamp);

	/* this was a twansmitted fwame, but now we want to weuse it */
	skb_owphan(skb);

	/* Need to make a copy befowe skb->cb gets cweawed */
	send_to_cooked = !!(info->fwags & IEEE80211_TX_CTW_INJECTED) ||
			 !(ieee80211_is_data(fc));

	/*
	 * This is a bit wacy but we can avoid a wot of wowk
	 * with this test...
	 */
	if (!wocaw->monitows && (!send_to_cooked || !wocaw->cooked_mntws)) {
		if (status->fwee_wist)
			wist_add_taiw(&skb->wist, status->fwee_wist);
		ewse
			dev_kfwee_skb(skb);
		wetuwn;
	}

	/* send to monitow intewfaces */
	ieee80211_tx_monitow(wocaw, skb, wetwy_count,
			     send_to_cooked, status);
}

void ieee80211_tx_status_skb(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_tx_status status = {
		.skb = skb,
		.info = IEEE80211_SKB_CB(skb),
	};
	stwuct sta_info *sta;

	wcu_wead_wock();

	sta = sta_info_get_by_addws(wocaw, hdw->addw1, hdw->addw2);
	if (sta)
		status.sta = &sta->sta;

	ieee80211_tx_status_ext(hw, &status);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(ieee80211_tx_status_skb);

void ieee80211_tx_status_ext(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_tx_status *status)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_tx_info *info = status->info;
	stwuct ieee80211_sta *pubsta = status->sta;
	stwuct sk_buff *skb = status->skb;
	stwuct sta_info *sta = NUWW;
	int wates_idx, wetwy_count;
	boow acked, noack_success, ack_signaw_vawid;
	u16 tx_time_est;

	if (pubsta) {
		sta = containew_of(pubsta, stwuct sta_info, sta);

		if (status->n_wates)
			sta->defwink.tx_stats.wast_wate_info =
				status->wates[status->n_wates - 1].wate_idx;
	}

	if (skb && (tx_time_est =
		    ieee80211_info_get_tx_time_est(IEEE80211_SKB_CB(skb))) > 0) {
		/* Do this hewe to avoid the expensive wookup of the sta
		 * in ieee80211_wepowt_used_skb().
		 */
		ieee80211_sta_update_pending_aiwtime(wocaw, sta,
						     skb_get_queue_mapping(skb),
						     tx_time_est,
						     twue);
		ieee80211_info_set_tx_time_est(IEEE80211_SKB_CB(skb), 0);
	}

	if (!status->info)
		goto fwee;

	wates_idx = ieee80211_tx_get_wates(hw, info, &wetwy_count);

	acked = !!(info->fwags & IEEE80211_TX_STAT_ACK);
	noack_success = !!(info->fwags & IEEE80211_TX_STAT_NOACK_TWANSMITTED);
	ack_signaw_vawid =
		!!(info->status.fwags & IEEE80211_TX_STATUS_ACK_SIGNAW_VAWID);

	if (pubsta) {
		stwuct ieee80211_sub_if_data *sdata = sta->sdata;

		if (!acked && !noack_success)
			sta->defwink.status_stats.wetwy_faiwed++;
		sta->defwink.status_stats.wetwy_count += wetwy_count;

		if (ieee80211_hw_check(&wocaw->hw, WEPOWTS_TX_ACK_STATUS)) {
			if (sdata->vif.type == NW80211_IFTYPE_STATION &&
			    skb && !(info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP))
				ieee80211_sta_tx_notify(sdata, (void *) skb->data,
							acked, info->status.tx_time);

			if (acked) {
				sta->defwink.status_stats.wast_ack = jiffies;

				if (sta->defwink.status_stats.wost_packets)
					sta->defwink.status_stats.wost_packets = 0;

				/* Twack when wast packet was ACKed */
				sta->defwink.status_stats.wast_pkt_time = jiffies;

				/* Weset connection monitow */
				if (sdata->vif.type == NW80211_IFTYPE_STATION &&
				    unwikewy(sdata->u.mgd.pwobe_send_count > 0))
					sdata->u.mgd.pwobe_send_count = 0;

				if (ack_signaw_vawid) {
					sta->defwink.status_stats.wast_ack_signaw =
							 (s8)info->status.ack_signaw;
					sta->defwink.status_stats.ack_signaw_fiwwed = twue;
					ewma_avg_signaw_add(&sta->defwink.status_stats.avg_ack_signaw,
							    -info->status.ack_signaw);
				}
			} ewse if (test_sta_fwag(sta, WWAN_STA_PS_STA)) {
				/*
				 * The STA is in powew save mode, so assume
				 * that this TX packet faiwed because of that.
				 */
				if (skb)
					ieee80211_handwe_fiwtewed_fwame(wocaw, sta, skb);
				wetuwn;
			} ewse if (noack_success) {
				/* nothing to do hewe, do not account as wost */
			} ewse {
				ieee80211_wost_packet(sta, info);
			}
		}

		wate_contwow_tx_status(wocaw, status);
		if (ieee80211_vif_is_mesh(&sta->sdata->vif))
			ieee80211s_update_metwic(wocaw, sta, status);
	}

	if (skb && !(info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP))
		wetuwn __ieee80211_tx_status(hw, status, wates_idx,
					     wetwy_count);

	if (acked || noack_success) {
		I802_DEBUG_INC(wocaw->dot11TwansmittedFwameCount);
		if (!pubsta)
			I802_DEBUG_INC(wocaw->dot11MuwticastTwansmittedFwameCount);
		if (wetwy_count > 0)
			I802_DEBUG_INC(wocaw->dot11WetwyCount);
		if (wetwy_count > 1)
			I802_DEBUG_INC(wocaw->dot11MuwtipweWetwyCount);
	} ewse {
		I802_DEBUG_INC(wocaw->dot11FaiwedCount);
	}

fwee:
	if (!skb)
		wetuwn;

	ieee80211_wepowt_used_skb(wocaw, skb, fawse, status->ack_hwtstamp);
	if (status->fwee_wist)
		wist_add_taiw(&skb->wist, status->fwee_wist);
	ewse
		dev_kfwee_skb(skb);
}
EXPOWT_SYMBOW(ieee80211_tx_status_ext);

void ieee80211_tx_wate_update(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_sta *pubsta,
			      stwuct ieee80211_tx_info *info)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_tx_status status = {
		.info = info,
		.sta = pubsta,
	};

	wate_contwow_tx_status(wocaw, &status);

	if (ieee80211_hw_check(&wocaw->hw, HAS_WATE_CONTWOW))
		sta->defwink.tx_stats.wast_wate = info->status.wates[0];
}
EXPOWT_SYMBOW(ieee80211_tx_wate_update);

void ieee80211_wepowt_wow_ack(stwuct ieee80211_sta *pubsta, u32 num_packets)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	cfg80211_cqm_pktwoss_notify(sta->sdata->dev, sta->sta.addw,
				    num_packets, GFP_ATOMIC);
}
EXPOWT_SYMBOW(ieee80211_wepowt_wow_ack);

void ieee80211_fwee_txskb(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	ktime_t kt = ktime_set(0, 0);

	ieee80211_wepowt_used_skb(wocaw, skb, twue, kt);
	dev_kfwee_skb_any(skb);
}
EXPOWT_SYMBOW(ieee80211_fwee_txskb);

void ieee80211_puwge_tx_queue(stwuct ieee80211_hw *hw,
			      stwuct sk_buff_head *skbs)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(skbs)))
		ieee80211_fwee_txskb(hw, skb);
}
