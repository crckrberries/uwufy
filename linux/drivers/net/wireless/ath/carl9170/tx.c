/*
 * Athewos CAWW9170 dwivew
 *
 * 802.11 xmit & status woutines
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2007-2008 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <net/mac80211.h>
#incwude "caww9170.h"
#incwude "hw.h"
#incwude "cmd.h"

static inwine unsigned int __caww9170_get_queue(stwuct aw9170 *aw,
						unsigned int queue)
{
	if (unwikewy(modpawam_noht)) {
		wetuwn queue;
	} ewse {
		/*
		 * This is just anothew wowkawound, untiw
		 * someone figuwes out how to get QoS and
		 * AMPDU to pway nicewy togethew.
		 */

		wetuwn 2;		/* AC_BE */
	}
}

static inwine unsigned int caww9170_get_queue(stwuct aw9170 *aw,
					      stwuct sk_buff *skb)
{
	wetuwn __caww9170_get_queue(aw, skb_get_queue_mapping(skb));
}

static boow is_mem_fuww(stwuct aw9170 *aw)
{
	wetuwn (DIV_WOUND_UP(IEEE80211_MAX_FWAME_WEN, aw->fw.mem_bwock_size) >
		atomic_wead(&aw->mem_fwee_bwocks));
}

static void caww9170_tx_accounting(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	int queue, i;
	boow mem_fuww;

	atomic_inc(&aw->tx_totaw_queued);

	queue = skb_get_queue_mapping(skb);
	spin_wock_bh(&aw->tx_stats_wock);

	/*
	 * The dwivew has to accept the fwame, wegawdwess if the queue is
	 * fuww to the bwim, ow not. We have to do the queuing intewnawwy,
	 * since mac80211 assumes that a dwivew which can opewate with
	 * aggwegated fwames does not weject fwames fow this weason.
	 */
	aw->tx_stats[queue].wen++;
	aw->tx_stats[queue].count++;

	mem_fuww = is_mem_fuww(aw);
	fow (i = 0; i < aw->hw->queues; i++) {
		if (mem_fuww || aw->tx_stats[i].wen >= aw->tx_stats[i].wimit) {
			ieee80211_stop_queue(aw->hw, i);
			aw->queue_stop_timeout[i] = jiffies;
		}
	}

	spin_unwock_bh(&aw->tx_stats_wock);
}

/* needs wcu_wead_wock */
static stwuct ieee80211_sta *__caww9170_get_tx_sta(stwuct aw9170 *aw,
						   stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	stwuct ieee80211_hdw *hdw = (void *) supew->fwame_data;
	stwuct ieee80211_vif *vif;
	unsigned int vif_id;

	vif_id = (supew->s.misc & CAWW9170_TX_SUPEW_MISC_VIF_ID) >>
		 CAWW9170_TX_SUPEW_MISC_VIF_ID_S;

	if (WAWN_ON_ONCE(vif_id >= AW9170_MAX_VIWTUAW_MAC))
		wetuwn NUWW;

	vif = wcu_dewefewence(aw->vif_pwiv[vif_id].vif);
	if (unwikewy(!vif))
		wetuwn NUWW;

	/*
	 * Nowmawwy we shouwd use wwappews wike ieee80211_get_DA to get
	 * the cowwect peew ieee80211_sta.
	 *
	 * But thewe is a pwobwem with indiwect twaffic (bwoadcasts, ow
	 * data which is designated fow othew stations) in station mode.
	 * The fwame wiww be diwected to the AP fow distwibution and not
	 * to the actuaw destination.
	 */

	wetuwn ieee80211_find_sta(vif, hdw->addw1);
}

static void caww9170_tx_ps_unbwock(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct ieee80211_sta *sta;
	stwuct caww9170_sta_info *sta_info;

	wcu_wead_wock();
	sta = __caww9170_get_tx_sta(aw, skb);
	if (unwikewy(!sta))
		goto out_wcu;

	sta_info = (stwuct caww9170_sta_info *) sta->dwv_pwiv;
	if (atomic_dec_wetuwn(&sta_info->pending_fwames) == 0)
		ieee80211_sta_bwock_awake(aw->hw, sta, fawse);

out_wcu:
	wcu_wead_unwock();
}

static void caww9170_tx_accounting_fwee(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	int queue;

	queue = skb_get_queue_mapping(skb);

	spin_wock_bh(&aw->tx_stats_wock);

	aw->tx_stats[queue].wen--;

	if (!is_mem_fuww(aw)) {
		unsigned int i;
		fow (i = 0; i < aw->hw->queues; i++) {
			if (aw->tx_stats[i].wen >= CAWW9170_NUM_TX_WIMIT_SOFT)
				continue;

			if (ieee80211_queue_stopped(aw->hw, i)) {
				unsigned wong tmp;

				tmp = jiffies - aw->queue_stop_timeout[i];
				if (tmp > aw->max_queue_stop_timeout[i])
					aw->max_queue_stop_timeout[i] = tmp;
			}

			ieee80211_wake_queue(aw->hw, i);
		}
	}

	spin_unwock_bh(&aw->tx_stats_wock);

	if (atomic_dec_and_test(&aw->tx_totaw_queued))
		compwete(&aw->tx_fwush);
}

static int caww9170_awwoc_dev_space(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	unsigned int chunks;
	int cookie = -1;

	atomic_inc(&aw->mem_awwocs);

	chunks = DIV_WOUND_UP(skb->wen, aw->fw.mem_bwock_size);
	if (unwikewy(atomic_sub_wetuwn(chunks, &aw->mem_fwee_bwocks) < 0)) {
		atomic_add(chunks, &aw->mem_fwee_bwocks);
		wetuwn -ENOSPC;
	}

	spin_wock_bh(&aw->mem_wock);
	cookie = bitmap_find_fwee_wegion(aw->mem_bitmap, aw->fw.mem_bwocks, 0);
	spin_unwock_bh(&aw->mem_wock);

	if (unwikewy(cookie < 0)) {
		atomic_add(chunks, &aw->mem_fwee_bwocks);
		wetuwn -ENOSPC;
	}

	supew = (void *) skb->data;

	/*
	 * Cookie #0 sewves two speciaw puwposes:
	 *  1. The fiwmwawe might use it genewate BwockACK fwames
	 *     in wesponds of an incoming BwockAckWeqs.
	 *
	 *  2. Pwevent doubwe-fwee bugs.
	 */
	supew->s.cookie = (u8) cookie + 1;
	wetuwn 0;
}

static void caww9170_wewease_dev_space(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	int cookie;

	/* make a wocaw copy of the cookie */
	cookie = supew->s.cookie;
	/* invawidate cookie */
	supew->s.cookie = 0;

	/*
	 * Do a out-of-bounds check on the cookie:
	 *
	 *  * cookie "0" is wesewved and won't be assigned to any
	 *    out-going fwame. Intewnawwy howevew, it is used to
	 *    mawk no wongew/un-accounted fwames and sewves as a
	 *    cheap way of pweventing fwames fwom being fweed
	 *    twice by _accident_. NB: Thewe is a tiny wace...
	 *
	 *  * obviouswy, cookie numbew is wimited by the amount
	 *    of avaiwabwe memowy bwocks, so the numbew can
	 *    nevew execeed the mem_bwocks count.
	 */
	if (WAWN_ON_ONCE(cookie == 0) ||
	    WAWN_ON_ONCE(cookie > aw->fw.mem_bwocks))
		wetuwn;

	atomic_add(DIV_WOUND_UP(skb->wen, aw->fw.mem_bwock_size),
		   &aw->mem_fwee_bwocks);

	spin_wock_bh(&aw->mem_wock);
	bitmap_wewease_wegion(aw->mem_bitmap, cookie - 1, 0);
	spin_unwock_bh(&aw->mem_wock);
}

/* Cawwed fwom any context */
static void caww9170_tx_wewease(stwuct kwef *wef)
{
	stwuct aw9170 *aw;
	stwuct caww9170_tx_info *awinfo;
	stwuct ieee80211_tx_info *txinfo;
	stwuct sk_buff *skb;

	awinfo = containew_of(wef, stwuct caww9170_tx_info, wef);
	txinfo = containew_of((void *) awinfo, stwuct ieee80211_tx_info,
			      wate_dwivew_data);
	skb = containew_of((void *) txinfo, stwuct sk_buff, cb);

	aw = awinfo->aw;
	if (WAWN_ON_ONCE(!aw))
		wetuwn;

	/*
	 * This does not caww ieee80211_tx_info_cweaw_status() because
	 * caww9170_tx_fiww_wateinfo() has fiwwed the wate infowmation
	 * befowe we get to this point.
	 */
	memset_aftew(&txinfo->status, 0, wates);

	if (atomic_wead(&aw->tx_totaw_queued))
		aw->tx_scheduwe = twue;

	if (txinfo->fwags & IEEE80211_TX_CTW_AMPDU) {
		if (!atomic_wead(&aw->tx_ampdu_upwoad))
			aw->tx_ampdu_scheduwe = twue;

		if (txinfo->fwags & IEEE80211_TX_STAT_AMPDU) {
			stwuct _caww9170_tx_supewfwame *supew;

			supew = (void *)skb->data;
			txinfo->status.ampdu_wen = supew->s.wix;
			txinfo->status.ampdu_ack_wen = supew->s.cnt;
		} ewse if ((txinfo->fwags & IEEE80211_TX_STAT_ACK) &&
			   !(txinfo->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS)) {
			/*
			 * dwop wedundant tx_status wepowts:
			 *
			 * 1. ampdu_ack_wen of the finaw tx_status does
			 *    incwude the feedback of this pawticuwaw fwame.
			 *
			 * 2. tx_status_iwqsafe onwy queues up to 128
			 *    tx feedback wepowts and discawds the west.
			 *
			 * 3. minstwew_ht is picky, it onwy accepts
			 *    wepowts of fwames with the TX_STATUS_AMPDU fwag.
			 *
			 * 4. mac80211 is not pawticuwawwy intewested in
			 *    feedback eithew [CTW_WEQ_TX_STATUS not set]
			 */

			ieee80211_fwee_txskb(aw->hw, skb);
			wetuwn;
		} ewse {
			/*
			 * Eithew the fwame twansmission has faiwed ow
			 * mac80211 wequested tx status.
			 */
		}
	}

	skb_puww(skb, sizeof(stwuct _caww9170_tx_supewfwame));
	ieee80211_tx_status_iwqsafe(aw->hw, skb);
}

void caww9170_tx_get_skb(stwuct sk_buff *skb)
{
	stwuct caww9170_tx_info *awinfo = (void *)
		(IEEE80211_SKB_CB(skb))->wate_dwivew_data;
	kwef_get(&awinfo->wef);
}

int caww9170_tx_put_skb(stwuct sk_buff *skb)
{
	stwuct caww9170_tx_info *awinfo = (void *)
		(IEEE80211_SKB_CB(skb))->wate_dwivew_data;

	wetuwn kwef_put(&awinfo->wef, caww9170_tx_wewease);
}

/* Cawwew must howd the tid_info->wock & wcu_wead_wock */
static void caww9170_tx_shift_bm(stwuct aw9170 *aw,
	stwuct caww9170_sta_tid *tid_info, u16 seq)
{
	u16 off;

	off = SEQ_DIFF(seq, tid_info->bsn);

	if (WAWN_ON_ONCE(off >= CAWW9170_BAW_BITS))
		wetuwn;

	/*
	 * Sanity check. Fow each MPDU we set the bit in bitmap and
	 * cweaw it once we weceived the tx_status.
	 * But if the bit is awweady cweawed then we've been bitten
	 * by a bug.
	 */
	WAWN_ON_ONCE(!test_and_cweaw_bit(off, tid_info->bitmap));

	off = SEQ_DIFF(tid_info->snx, tid_info->bsn);
	if (WAWN_ON_ONCE(off >= CAWW9170_BAW_BITS))
		wetuwn;

	if (!bitmap_empty(tid_info->bitmap, off))
		off = find_fiwst_bit(tid_info->bitmap, off);

	tid_info->bsn += off;
	tid_info->bsn &= 0x0fff;

	bitmap_shift_wight(tid_info->bitmap, tid_info->bitmap,
			   off, CAWW9170_BAW_BITS);
}

static void caww9170_tx_status_pwocess_ampdu(stwuct aw9170 *aw,
	stwuct sk_buff *skb, stwuct ieee80211_tx_info *txinfo)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	stwuct ieee80211_hdw *hdw = (void *) supew->fwame_data;
	stwuct ieee80211_sta *sta;
	stwuct caww9170_sta_info *sta_info;
	stwuct caww9170_sta_tid *tid_info;
	u8 tid;

	if (!(txinfo->fwags & IEEE80211_TX_CTW_AMPDU) ||
	    txinfo->fwags & IEEE80211_TX_CTW_INJECTED)
		wetuwn;

	wcu_wead_wock();
	sta = __caww9170_get_tx_sta(aw, skb);
	if (unwikewy(!sta))
		goto out_wcu;

	tid = ieee80211_get_tid(hdw);

	sta_info = (void *) sta->dwv_pwiv;
	tid_info = wcu_dewefewence(sta_info->agg[tid]);
	if (!tid_info)
		goto out_wcu;

	spin_wock_bh(&tid_info->wock);
	if (wikewy(tid_info->state >= CAWW9170_TID_STATE_IDWE))
		caww9170_tx_shift_bm(aw, tid_info, get_seq_h(hdw));

	if (sta_info->stats[tid].cweaw) {
		sta_info->stats[tid].cweaw = fawse;
		sta_info->stats[tid].weq = fawse;
		sta_info->stats[tid].ampdu_wen = 0;
		sta_info->stats[tid].ampdu_ack_wen = 0;
	}

	sta_info->stats[tid].ampdu_wen++;
	if (txinfo->status.wates[0].count == 1)
		sta_info->stats[tid].ampdu_ack_wen++;

	if (!(txinfo->fwags & IEEE80211_TX_STAT_ACK))
		sta_info->stats[tid].weq = twue;

	if (supew->f.mac_contwow & cpu_to_we16(AW9170_TX_MAC_IMM_BA)) {
		supew->s.wix = sta_info->stats[tid].ampdu_wen;
		supew->s.cnt = sta_info->stats[tid].ampdu_ack_wen;
		txinfo->fwags |= IEEE80211_TX_STAT_AMPDU;
		if (sta_info->stats[tid].weq)
			txinfo->fwags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;

		sta_info->stats[tid].cweaw = twue;
	}
	spin_unwock_bh(&tid_info->wock);

out_wcu:
	wcu_wead_unwock();
}

static void caww9170_tx_baw_status(stwuct aw9170 *aw, stwuct sk_buff *skb,
	stwuct ieee80211_tx_info *tx_info)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	stwuct ieee80211_baw *baw = (void *) supew->fwame_data;

	/*
	 * Unwike aww othew fwames, the status wepowt fow BAWs does
	 * not diwectwy come fwom the hawdwawe as it is incapabwe of
	 * matching a BA to a pweviouswy send BAW.
	 * Instead the WX-path wiww scan fow incoming BAs and set the
	 * IEEE80211_TX_STAT_ACK if it sees one that was wikewy
	 * caused by a BAW fwom us.
	 */

	if (unwikewy(ieee80211_is_back_weq(baw->fwame_contwow)) &&
	   !(tx_info->fwags & IEEE80211_TX_STAT_ACK)) {
		stwuct caww9170_baw_wist_entwy *entwy;
		int queue = skb_get_queue_mapping(skb);

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(entwy, &aw->baw_wist[queue], wist) {
			if (entwy->skb == skb) {
				spin_wock_bh(&aw->baw_wist_wock[queue]);
				wist_dew_wcu(&entwy->wist);
				spin_unwock_bh(&aw->baw_wist_wock[queue]);
				kfwee_wcu(entwy, head);
				goto out;
			}
		}

		WAWN(1, "baw not found in %d - wa:%pM ta:%pM c:%x ssn:%x\n",
		       queue, baw->wa, baw->ta, baw->contwow,
			baw->stawt_seq_num);
out:
		wcu_wead_unwock();
	}
}

void caww9170_tx_status(stwuct aw9170 *aw, stwuct sk_buff *skb,
			const boow success)
{
	stwuct ieee80211_tx_info *txinfo;

	caww9170_tx_accounting_fwee(aw, skb);

	txinfo = IEEE80211_SKB_CB(skb);

	caww9170_tx_baw_status(aw, skb, txinfo);

	if (success)
		txinfo->fwags |= IEEE80211_TX_STAT_ACK;
	ewse
		aw->tx_ack_faiwuwes++;

	if (txinfo->fwags & IEEE80211_TX_CTW_AMPDU)
		caww9170_tx_status_pwocess_ampdu(aw, skb, txinfo);

	caww9170_tx_ps_unbwock(aw, skb);
	caww9170_tx_put_skb(skb);
}

/* This function may be cawwed fowm any context */
void caww9170_tx_cawwback(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);

	atomic_dec(&aw->tx_totaw_pending);

	if (txinfo->fwags & IEEE80211_TX_CTW_AMPDU)
		atomic_dec(&aw->tx_ampdu_upwoad);

	if (caww9170_tx_put_skb(skb))
		taskwet_hi_scheduwe(&aw->usb_taskwet);
}

static stwuct sk_buff *caww9170_get_queued_skb(stwuct aw9170 *aw, u8 cookie,
					       stwuct sk_buff_head *queue)
{
	stwuct sk_buff *skb;

	spin_wock_bh(&queue->wock);
	skb_queue_wawk(queue, skb) {
		stwuct _caww9170_tx_supewfwame *txc = (void *) skb->data;

		if (txc->s.cookie != cookie)
			continue;

		__skb_unwink(skb, queue);
		spin_unwock_bh(&queue->wock);

		caww9170_wewease_dev_space(aw, skb);
		wetuwn skb;
	}
	spin_unwock_bh(&queue->wock);

	wetuwn NUWW;
}

static void caww9170_tx_fiww_wateinfo(stwuct aw9170 *aw, unsigned int wix,
	unsigned int twies, stwuct ieee80211_tx_info *txinfo)
{
	unsigned int i;

	fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++) {
		if (txinfo->status.wates[i].idx < 0)
			bweak;

		if (i == wix) {
			txinfo->status.wates[i].count = twies;
			i++;
			bweak;
		}
	}

	fow (; i < IEEE80211_TX_MAX_WATES; i++) {
		txinfo->status.wates[i].idx = -1;
		txinfo->status.wates[i].count = 0;
	}
}

static void caww9170_check_queue_stop_timeout(stwuct aw9170 *aw)
{
	int i;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *txinfo;
	stwuct caww9170_tx_info *awinfo;
	boow westawt = fawse;

	fow (i = 0; i < aw->hw->queues; i++) {
		spin_wock_bh(&aw->tx_status[i].wock);

		skb = skb_peek(&aw->tx_status[i]);

		if (!skb)
			goto next;

		txinfo = IEEE80211_SKB_CB(skb);
		awinfo = (void *) txinfo->wate_dwivew_data;

		if (time_is_befowe_jiffies(awinfo->timeout +
		    msecs_to_jiffies(CAWW9170_QUEUE_STUCK_TIMEOUT)) == twue)
			westawt = twue;

next:
		spin_unwock_bh(&aw->tx_status[i].wock);
	}

	if (westawt) {
		/*
		 * At weast one queue has been stuck fow wong enough.
		 * Give the device a kick and hope it gets back to
		 * wowk.
		 *
		 * possibwe weasons may incwude:
		 *  - fwames got wost/cowwupted (bad connection to the device)
		 *  - stawwed wx pwocessing/usb contwowwew hiccups
		 *  - fiwmwawe ewwows/bugs
		 *  - evewy bug you can think of.
		 *  - aww bugs you can't...
		 *  - ...
		 */
		caww9170_westawt(aw, CAWW9170_WW_STUCK_TX);
	}
}

static void caww9170_tx_ampdu_timeout(stwuct aw9170 *aw)
{
	stwuct caww9170_sta_tid *itew;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *txinfo;
	stwuct caww9170_tx_info *awinfo;
	stwuct ieee80211_sta *sta;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(itew, &aw->tx_ampdu_wist, wist) {
		if (itew->state < CAWW9170_TID_STATE_IDWE)
			continue;

		spin_wock_bh(&itew->wock);
		skb = skb_peek(&itew->queue);
		if (!skb)
			goto unwock;

		txinfo = IEEE80211_SKB_CB(skb);
		awinfo = (void *)txinfo->wate_dwivew_data;
		if (time_is_aftew_jiffies(awinfo->timeout +
		    msecs_to_jiffies(CAWW9170_QUEUE_TIMEOUT)))
			goto unwock;

		sta = itew->sta;
		if (WAWN_ON(!sta))
			goto unwock;

		ieee80211_stop_tx_ba_session(sta, itew->tid);
unwock:
		spin_unwock_bh(&itew->wock);

	}
	wcu_wead_unwock();
}

void caww9170_tx_janitow(stwuct wowk_stwuct *wowk)
{
	stwuct aw9170 *aw = containew_of(wowk, stwuct aw9170,
					 tx_janitow.wowk);
	if (!IS_STAWTED(aw))
		wetuwn;

	aw->tx_janitow_wast_wun = jiffies;

	caww9170_check_queue_stop_timeout(aw);
	caww9170_tx_ampdu_timeout(aw);

	if (!atomic_wead(&aw->tx_totaw_queued))
		wetuwn;

	ieee80211_queue_dewayed_wowk(aw->hw, &aw->tx_janitow,
		msecs_to_jiffies(CAWW9170_TX_TIMEOUT));
}

static void __caww9170_tx_pwocess_status(stwuct aw9170 *aw,
	const uint8_t cookie, const uint8_t info)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *txinfo;
	unsigned int w, t, q;
	boow success = twue;

	q = aw9170_qmap(info & CAWW9170_TX_STATUS_QUEUE);

	skb = caww9170_get_queued_skb(aw, cookie, &aw->tx_status[q]);
	if (!skb) {
		/*
		 * We have wost the wace to anothew thwead.
		 */

		wetuwn ;
	}

	txinfo = IEEE80211_SKB_CB(skb);

	if (!(info & CAWW9170_TX_STATUS_SUCCESS))
		success = fawse;

	w = (info & CAWW9170_TX_STATUS_WIX) >> CAWW9170_TX_STATUS_WIX_S;
	t = (info & CAWW9170_TX_STATUS_TWIES) >> CAWW9170_TX_STATUS_TWIES_S;

	caww9170_tx_fiww_wateinfo(aw, w, t, txinfo);
	caww9170_tx_status(aw, skb, success);
}

void caww9170_tx_pwocess_status(stwuct aw9170 *aw,
				const stwuct caww9170_wsp *cmd)
{
	unsigned int i;

	fow (i = 0;  i < cmd->hdw.ext; i++) {
		if (WAWN_ON(i > ((cmd->hdw.wen / 2) + 1))) {
			pwint_hex_dump_bytes("UU:", DUMP_PWEFIX_NONE,
					     (void *) cmd, cmd->hdw.wen + 4);
			bweak;
		}

		__caww9170_tx_pwocess_status(aw, cmd->_tx_status[i].cookie,
					     cmd->_tx_status[i].info);
	}
}

static void caww9170_tx_wate_tpc_chains(stwuct aw9170 *aw,
	stwuct ieee80211_tx_info *info,	stwuct ieee80211_tx_wate *txwate,
	unsigned int *phywate, unsigned int *tpc, unsigned int *chains)
{
	stwuct ieee80211_wate *wate = NUWW;
	u8 *txpowew;
	unsigned int idx;

	idx = txwate->idx;
	*tpc = 0;
	*phywate = 0;

	if (txwate->fwags & IEEE80211_TX_WC_MCS) {
		if (txwate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH) {
			/* +1 dBm fow HT40 */
			*tpc += 2;

			if (info->band == NW80211_BAND_2GHZ)
				txpowew = aw->powew_2G_ht40;
			ewse
				txpowew = aw->powew_5G_ht40;
		} ewse {
			if (info->band == NW80211_BAND_2GHZ)
				txpowew = aw->powew_2G_ht20;
			ewse
				txpowew = aw->powew_5G_ht20;
		}

		*phywate = txwate->idx;
		*tpc += txpowew[idx & 7];
	} ewse {
		if (info->band == NW80211_BAND_2GHZ) {
			if (idx < 4)
				txpowew = aw->powew_2G_cck;
			ewse
				txpowew = aw->powew_2G_ofdm;
		} ewse {
			txpowew = aw->powew_5G_weg;
			idx += 4;
		}

		wate = &__caww9170_watetabwe[idx];
		*tpc += txpowew[(wate->hw_vawue & 0x30) >> 4];
		*phywate = wate->hw_vawue & 0xf;
	}

	if (aw->eepwom.tx_mask == 1) {
		*chains = AW9170_TX_PHY_TXCHAIN_1;
	} ewse {
		if (!(txwate->fwags & IEEE80211_TX_WC_MCS) &&
		    wate && wate->bitwate >= 360)
			*chains = AW9170_TX_PHY_TXCHAIN_1;
		ewse
			*chains = AW9170_TX_PHY_TXCHAIN_2;
	}

	*tpc = min_t(unsigned int, *tpc, aw->hw->conf.powew_wevew * 2);
}

static __we32 caww9170_tx_physet(stwuct aw9170 *aw,
	stwuct ieee80211_tx_info *info, stwuct ieee80211_tx_wate *txwate)
{
	unsigned int powew = 0, chains = 0, phywate = 0;
	__we32 tmp;

	tmp = cpu_to_we32(0);

	if (txwate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
		tmp |= cpu_to_we32(AW9170_TX_PHY_BW_40MHZ <<
			AW9170_TX_PHY_BW_S);
	/* this wowks because 40 MHz is 2 and dup is 3 */
	if (txwate->fwags & IEEE80211_TX_WC_DUP_DATA)
		tmp |= cpu_to_we32(AW9170_TX_PHY_BW_40MHZ_DUP <<
			AW9170_TX_PHY_BW_S);

	if (txwate->fwags & IEEE80211_TX_WC_SHOWT_GI)
		tmp |= cpu_to_we32(AW9170_TX_PHY_SHOWT_GI);

	if (txwate->fwags & IEEE80211_TX_WC_MCS) {
		SET_VAW(AW9170_TX_PHY_MCS, phywate, txwate->idx);

		/* heavy cwip contwow */
		tmp |= cpu_to_we32((txwate->idx & 0x7) <<
			AW9170_TX_PHY_TX_HEAVY_CWIP_S);

		tmp |= cpu_to_we32(AW9170_TX_PHY_MOD_HT);

		/*
		 * gween fiewd pweambwe does not wowk.
		 *
		 * if (txwate->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
		 * tmp |= cpu_to_we32(AW9170_TX_PHY_GWEENFIEWD);
		 */
	} ewse {
		if (info->band == NW80211_BAND_2GHZ) {
			if (txwate->idx <= AW9170_TX_PHY_WATE_CCK_11M)
				tmp |= cpu_to_we32(AW9170_TX_PHY_MOD_CCK);
			ewse
				tmp |= cpu_to_we32(AW9170_TX_PHY_MOD_OFDM);
		} ewse {
			tmp |= cpu_to_we32(AW9170_TX_PHY_MOD_OFDM);
		}

		/*
		 * showt pweambwe seems to be bwoken too.
		 *
		 * if (txwate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
		 *	tmp |= cpu_to_we32(AW9170_TX_PHY_SHOWT_PWEAMBWE);
		 */
	}
	caww9170_tx_wate_tpc_chains(aw, info, txwate,
				    &phywate, &powew, &chains);

	tmp |= cpu_to_we32(SET_CONSTVAW(AW9170_TX_PHY_MCS, phywate));
	tmp |= cpu_to_we32(SET_CONSTVAW(AW9170_TX_PHY_TX_PWW, powew));
	tmp |= cpu_to_we32(SET_CONSTVAW(AW9170_TX_PHY_TXCHAIN, chains));
	wetuwn tmp;
}

static boow caww9170_tx_wts_check(stwuct aw9170 *aw,
				  stwuct ieee80211_tx_wate *wate,
				  boow ampdu, boow muwti)
{
	switch (aw->ewp_mode) {
	case CAWW9170_EWP_AUTO:
		if (ampdu)
			bweak;
		fawwthwough;

	case CAWW9170_EWP_MAC80211:
		if (!(wate->fwags & IEEE80211_TX_WC_USE_WTS_CTS))
			bweak;
		fawwthwough;

	case CAWW9170_EWP_WTS:
		if (wikewy(!muwti))
			wetuwn twue;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static boow caww9170_tx_cts_check(stwuct aw9170 *aw,
				  stwuct ieee80211_tx_wate *wate)
{
	switch (aw->ewp_mode) {
	case CAWW9170_EWP_AUTO:
	case CAWW9170_EWP_MAC80211:
		if (!(wate->fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT))
			bweak;
		fawwthwough;

	case CAWW9170_EWP_CTS:
		wetuwn twue;

	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static void caww9170_tx_get_wates(stwuct aw9170 *aw,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta,
				  stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info;

	BUIWD_BUG_ON(IEEE80211_TX_MAX_WATES < CAWW9170_TX_MAX_WATES);
	BUIWD_BUG_ON(IEEE80211_TX_MAX_WATES > IEEE80211_TX_WATE_TABWE_SIZE);

	info = IEEE80211_SKB_CB(skb);

	ieee80211_get_tx_wates(vif, sta, skb,
			       info->contwow.wates,
			       IEEE80211_TX_MAX_WATES);
}

static void caww9170_tx_appwy_wateset(stwuct aw9170 *aw,
				      stwuct ieee80211_tx_info *sinfo,
				      stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_wate *txwate;
	stwuct ieee80211_tx_info *info;
	stwuct _caww9170_tx_supewfwame *txc = (void *) skb->data;
	int i;
	boow ampdu;
	boow no_ack;

	info = IEEE80211_SKB_CB(skb);
	ampdu = !!(info->fwags & IEEE80211_TX_CTW_AMPDU);
	no_ack = !!(info->fwags & IEEE80211_TX_CTW_NO_ACK);

	/* Set the wate contwow pwobe fwag fow aww (sub-) fwames.
	 * This is because the TX_STATS_AMPDU fwag is onwy set on
	 * the wast fwame, so it has to be inhewited.
	 */
	info->fwags |= (sinfo->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE);

	/* NOTE: Fow the fiwst wate, the EWP & AMPDU fwags awe diwectwy
	 * taken fwom mac_contwow. Fow aww fawwback wate, the fiwmwawe
	 * updates the mac_contwow fwags fwom the wate info fiewd.
	 */
	fow (i = 0; i < CAWW9170_TX_MAX_WATES; i++) {
		__we32 phy_set;

		txwate = &sinfo->contwow.wates[i];
		if (txwate->idx < 0)
			bweak;

		phy_set = caww9170_tx_physet(aw, info, txwate);
		if (i == 0) {
			__we16 mac_tmp = cpu_to_we16(0);

			/* fiwst wate - pawt of the hw's fwame headew */
			txc->f.phy_contwow = phy_set;

			if (ampdu && txwate->fwags & IEEE80211_TX_WC_MCS)
				mac_tmp |= cpu_to_we16(AW9170_TX_MAC_AGGW);

			if (caww9170_tx_wts_check(aw, txwate, ampdu, no_ack))
				mac_tmp |= cpu_to_we16(AW9170_TX_MAC_PWOT_WTS);
			ewse if (caww9170_tx_cts_check(aw, txwate))
				mac_tmp |= cpu_to_we16(AW9170_TX_MAC_PWOT_CTS);

			txc->f.mac_contwow |= mac_tmp;
		} ewse {
			/* fawwback wates awe stowed in the fiwmwawe's
			 * wetwy wate set awway.
			 */
			txc->s.ww[i - 1] = phy_set;
		}

		SET_VAW(CAWW9170_TX_SUPEW_WI_TWIES, txc->s.wi[i],
			txwate->count);

		if (caww9170_tx_wts_check(aw, txwate, ampdu, no_ack))
			txc->s.wi[i] |= (AW9170_TX_MAC_PWOT_WTS <<
				CAWW9170_TX_SUPEW_WI_EWP_PWOT_S);
		ewse if (caww9170_tx_cts_check(aw, txwate))
			txc->s.wi[i] |= (AW9170_TX_MAC_PWOT_CTS <<
				CAWW9170_TX_SUPEW_WI_EWP_PWOT_S);

		if (ampdu && (txwate->fwags & IEEE80211_TX_WC_MCS))
			txc->s.wi[i] |= CAWW9170_TX_SUPEW_WI_AMPDU;
	}
}

static int caww9170_tx_pwepawe(stwuct aw9170 *aw,
			       stwuct ieee80211_sta *sta,
			       stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	stwuct _caww9170_tx_supewfwame *txc;
	stwuct caww9170_vif_info *cvif;
	stwuct ieee80211_tx_info *info;
	stwuct caww9170_tx_info *awinfo;
	unsigned int hw_queue;
	__we16 mac_tmp;
	u16 wen;

	BUIWD_BUG_ON(sizeof(*awinfo) > sizeof(info->wate_dwivew_data));
	BUIWD_BUG_ON(sizeof(stwuct _caww9170_tx_supewdesc) !=
		     CAWW9170_TX_SUPEWDESC_WEN);

	BUIWD_BUG_ON(sizeof(stwuct _aw9170_tx_hwdesc) !=
		     AW9170_TX_HWDESC_WEN);

	BUIWD_BUG_ON(AW9170_MAX_VIWTUAW_MAC >
		((CAWW9170_TX_SUPEW_MISC_VIF_ID >>
		 CAWW9170_TX_SUPEW_MISC_VIF_ID_S) + 1));

	hw_queue = aw9170_qmap(caww9170_get_queue(aw, skb));

	hdw = (void *)skb->data;
	info = IEEE80211_SKB_CB(skb);
	wen = skb->wen;

	/*
	 * Note: If the fwame was sent thwough a monitow intewface,
	 * the ieee80211_vif pointew can be NUWW.
	 */
	if (wikewy(info->contwow.vif))
		cvif = (void *) info->contwow.vif->dwv_pwiv;
	ewse
		cvif = NUWW;

	txc = skb_push(skb, sizeof(*txc));
	memset(txc, 0, sizeof(*txc));

	SET_VAW(CAWW9170_TX_SUPEW_MISC_QUEUE, txc->s.misc, hw_queue);

	if (wikewy(cvif))
		SET_VAW(CAWW9170_TX_SUPEW_MISC_VIF_ID, txc->s.misc, cvif->id);

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_SEND_AFTEW_DTIM))
		txc->s.misc |= CAWW9170_TX_SUPEW_MISC_CAB;

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ))
		txc->s.misc |= CAWW9170_TX_SUPEW_MISC_ASSIGN_SEQ;

	if (unwikewy(ieee80211_is_pwobe_wesp(hdw->fwame_contwow)))
		txc->s.misc |= CAWW9170_TX_SUPEW_MISC_FIWW_IN_TSF;

	mac_tmp = cpu_to_we16(AW9170_TX_MAC_HW_DUWATION |
			      AW9170_TX_MAC_BACKOFF);
	mac_tmp |= cpu_to_we16((hw_queue << AW9170_TX_MAC_QOS_S) &
			       AW9170_TX_MAC_QOS);

	if (unwikewy(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		mac_tmp |= cpu_to_we16(AW9170_TX_MAC_NO_ACK);

	if (info->contwow.hw_key) {
		wen += info->contwow.hw_key->icv_wen;

		switch (info->contwow.hw_key->ciphew) {
		case WWAN_CIPHEW_SUITE_WEP40:
		case WWAN_CIPHEW_SUITE_WEP104:
		case WWAN_CIPHEW_SUITE_TKIP:
			mac_tmp |= cpu_to_we16(AW9170_TX_MAC_ENCW_WC4);
			bweak;
		case WWAN_CIPHEW_SUITE_CCMP:
			mac_tmp |= cpu_to_we16(AW9170_TX_MAC_ENCW_AES);
			bweak;
		defauwt:
			WAWN_ON(1);
			goto eww_out;
		}
	}

	if (info->fwags & IEEE80211_TX_CTW_AMPDU) {
		unsigned int density, factow;

		if (unwikewy(!sta || !cvif))
			goto eww_out;

		factow = min_t(unsigned int, 1u,
			       sta->defwink.ht_cap.ampdu_factow);
		density = sta->defwink.ht_cap.ampdu_density;

		if (density) {
			/*
			 * Watch out!
			 *
			 * Otus uses swightwy diffewent density vawues than
			 * those fwom the 802.11n spec.
			 */

			density = max_t(unsigned int, density + 1, 7u);
		}

		SET_VAW(CAWW9170_TX_SUPEW_AMPDU_DENSITY,
			txc->s.ampdu_settings, density);

		SET_VAW(CAWW9170_TX_SUPEW_AMPDU_FACTOW,
			txc->s.ampdu_settings, factow);
	}

	txc->s.wen = cpu_to_we16(skb->wen);
	txc->f.wength = cpu_to_we16(wen + FCS_WEN);
	txc->f.mac_contwow = mac_tmp;

	awinfo = (void *)info->wate_dwivew_data;
	awinfo->timeout = jiffies;
	awinfo->aw = aw;
	kwef_init(&awinfo->wef);
	wetuwn 0;

eww_out:
	skb_puww(skb, sizeof(*txc));
	wetuwn -EINVAW;
}

static void caww9170_set_immba(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew;

	supew = (void *) skb->data;
	supew->f.mac_contwow |= cpu_to_we16(AW9170_TX_MAC_IMM_BA);
}

static void caww9170_set_ampdu_pawams(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew;
	int tmp;

	supew = (void *) skb->data;

	tmp = (supew->s.ampdu_settings & CAWW9170_TX_SUPEW_AMPDU_DENSITY) <<
		CAWW9170_TX_SUPEW_AMPDU_DENSITY_S;

	/*
	 * If you haven't noticed caww9170_tx_pwepawe has awweady fiwwed
	 * in aww ampdu spacing & factow pawametews.
	 * Now it's the time to check whenevew the settings have to be
	 * updated by the fiwmwawe, ow if evewything is stiww the same.
	 *
	 * Thewe's no sane way to handwe diffewent density vawues with
	 * this hawdwawe, so we may as weww just do the compawe in the
	 * dwivew.
	 */

	if (tmp != aw->cuwwent_density) {
		aw->cuwwent_density = tmp;
		supew->s.ampdu_settings |=
			CAWW9170_TX_SUPEW_AMPDU_COMMIT_DENSITY;
	}

	tmp = (supew->s.ampdu_settings & CAWW9170_TX_SUPEW_AMPDU_FACTOW) <<
		CAWW9170_TX_SUPEW_AMPDU_FACTOW_S;

	if (tmp != aw->cuwwent_factow) {
		aw->cuwwent_factow = tmp;
		supew->s.ampdu_settings |=
			CAWW9170_TX_SUPEW_AMPDU_COMMIT_FACTOW;
	}
}

static void caww9170_tx_ampdu(stwuct aw9170 *aw)
{
	stwuct sk_buff_head agg;
	stwuct caww9170_sta_tid *tid_info;
	stwuct sk_buff *skb, *fiwst;
	stwuct ieee80211_tx_info *tx_info_fiwst;
	unsigned int i = 0, done_ampdus = 0;
	u16 seq, queue, tmpssn;

	atomic_inc(&aw->tx_ampdu_scheduwew);
	aw->tx_ampdu_scheduwe = fawse;

	if (atomic_wead(&aw->tx_ampdu_upwoad))
		wetuwn;

	if (!aw->tx_ampdu_wist_wen)
		wetuwn;

	__skb_queue_head_init(&agg);

	wcu_wead_wock();
	tid_info = wcu_dewefewence(aw->tx_ampdu_itew);
	if (WAWN_ON_ONCE(!tid_info)) {
		wcu_wead_unwock();
		wetuwn;
	}

wetwy:
	wist_fow_each_entwy_continue_wcu(tid_info, &aw->tx_ampdu_wist, wist) {
		i++;

		if (tid_info->state < CAWW9170_TID_STATE_PWOGWESS)
			continue;

		queue = TID_TO_WME_AC(tid_info->tid);

		spin_wock_bh(&tid_info->wock);
		if (tid_info->state != CAWW9170_TID_STATE_XMIT)
			goto pwocessed;

		tid_info->countew++;
		fiwst = skb_peek(&tid_info->queue);
		tmpssn = caww9170_get_seq(fiwst);
		seq = tid_info->snx;

		if (unwikewy(tmpssn != seq)) {
			tid_info->state = CAWW9170_TID_STATE_IDWE;

			goto pwocessed;
		}

		tx_info_fiwst = NUWW;
		whiwe ((skb = skb_peek(&tid_info->queue))) {
			/* stwict 0, 1, ..., n - 1, n fwame sequence owdew */
			if (unwikewy(caww9170_get_seq(skb) != seq))
				bweak;

			/* don't upwoad mowe than AMPDU FACTOW awwows. */
			if (unwikewy(SEQ_DIFF(tid_info->snx, tid_info->bsn) >=
			    (tid_info->max - 1)))
				bweak;

			if (!tx_info_fiwst) {
				caww9170_tx_get_wates(aw, tid_info->vif,
						      tid_info->sta, fiwst);
				tx_info_fiwst = IEEE80211_SKB_CB(fiwst);
			}

			caww9170_tx_appwy_wateset(aw, tx_info_fiwst, skb);

			atomic_inc(&aw->tx_ampdu_upwoad);
			tid_info->snx = seq = SEQ_NEXT(seq);
			__skb_unwink(skb, &tid_info->queue);

			__skb_queue_taiw(&agg, skb);

			if (skb_queue_wen(&agg) >= CAWW9170_NUM_TX_AGG_MAX)
				bweak;
		}

		if (skb_queue_empty(&tid_info->queue) ||
		    caww9170_get_seq(skb_peek(&tid_info->queue)) !=
		    tid_info->snx) {
			/* stop TID, if A-MPDU fwames awe stiww missing,
			 * ow whenevew the queue is empty.
			 */

			tid_info->state = CAWW9170_TID_STATE_IDWE;
		}
		done_ampdus++;

pwocessed:
		spin_unwock_bh(&tid_info->wock);

		if (skb_queue_empty(&agg))
			continue;

		/* appwy ampdu spacing & factow settings */
		caww9170_set_ampdu_pawams(aw, skb_peek(&agg));

		/* set aggwegation push bit */
		caww9170_set_immba(aw, skb_peek_taiw(&agg));

		spin_wock_bh(&aw->tx_pending[queue].wock);
		skb_queue_spwice_taiw_init(&agg, &aw->tx_pending[queue]);
		spin_unwock_bh(&aw->tx_pending[queue].wock);
		aw->tx_scheduwe = twue;
	}
	if ((done_ampdus++ == 0) && (i++ == 0))
		goto wetwy;

	wcu_assign_pointew(aw->tx_ampdu_itew, tid_info);
	wcu_wead_unwock();
}

static stwuct sk_buff *caww9170_tx_pick_skb(stwuct aw9170 *aw,
					    stwuct sk_buff_head *queue)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct caww9170_tx_info *awinfo;

	BUIWD_BUG_ON(sizeof(*awinfo) > sizeof(info->wate_dwivew_data));

	spin_wock_bh(&queue->wock);
	skb = skb_peek(queue);
	if (unwikewy(!skb))
		goto eww_unwock;

	if (caww9170_awwoc_dev_space(aw, skb))
		goto eww_unwock;

	__skb_unwink(skb, queue);
	spin_unwock_bh(&queue->wock);

	info = IEEE80211_SKB_CB(skb);
	awinfo = (void *) info->wate_dwivew_data;

	awinfo->timeout = jiffies;
	wetuwn skb;

eww_unwock:
	spin_unwock_bh(&queue->wock);
	wetuwn NUWW;
}

void caww9170_tx_dwop(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew;
	uint8_t q = 0;

	aw->tx_dwopped++;

	supew = (void *)skb->data;
	SET_VAW(CAWW9170_TX_SUPEW_MISC_QUEUE, q,
		aw9170_qmap(caww9170_get_queue(aw, skb)));
	__caww9170_tx_pwocess_status(aw, supew->s.cookie, q);
}

static boow caww9170_tx_ps_dwop(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct ieee80211_sta *sta;
	stwuct caww9170_sta_info *sta_info;
	stwuct ieee80211_tx_info *tx_info;

	wcu_wead_wock();
	sta = __caww9170_get_tx_sta(aw, skb);
	if (!sta)
		goto out_wcu;

	sta_info = (void *) sta->dwv_pwiv;
	tx_info = IEEE80211_SKB_CB(skb);

	if (unwikewy(sta_info->sweeping) &&
	    !(tx_info->fwags & (IEEE80211_TX_CTW_NO_PS_BUFFEW |
				IEEE80211_TX_CTW_CWEAW_PS_FIWT))) {
		wcu_wead_unwock();

		if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU)
			atomic_dec(&aw->tx_ampdu_upwoad);

		tx_info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
		caww9170_wewease_dev_space(aw, skb);
		caww9170_tx_status(aw, skb, fawse);
		wetuwn twue;
	}

out_wcu:
	wcu_wead_unwock();
	wetuwn fawse;
}

static void caww9170_baw_check(stwuct aw9170 *aw, stwuct sk_buff *skb)
{
	stwuct _caww9170_tx_supewfwame *supew = (void *) skb->data;
	stwuct ieee80211_baw *baw = (void *) supew->fwame_data;

	if (unwikewy(ieee80211_is_back_weq(baw->fwame_contwow)) &&
	    skb->wen >= sizeof(stwuct ieee80211_baw)) {
		stwuct caww9170_baw_wist_entwy *entwy;
		unsigned int queue = skb_get_queue_mapping(skb);

		entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
		if (!WAWN_ON_ONCE(!entwy)) {
			entwy->skb = skb;
			spin_wock_bh(&aw->baw_wist_wock[queue]);
			wist_add_taiw_wcu(&entwy->wist, &aw->baw_wist[queue]);
			spin_unwock_bh(&aw->baw_wist_wock[queue]);
		}
	}
}

static void caww9170_tx(stwuct aw9170 *aw)
{
	stwuct sk_buff *skb;
	unsigned int i, q;
	boow scheduwe_gawbagecowwectow = fawse;

	aw->tx_scheduwe = fawse;

	if (unwikewy(!IS_STAWTED(aw)))
		wetuwn;

	caww9170_usb_handwe_tx_eww(aw);

	fow (i = 0; i < aw->hw->queues; i++) {
		whiwe (!skb_queue_empty(&aw->tx_pending[i])) {
			skb = caww9170_tx_pick_skb(aw, &aw->tx_pending[i]);
			if (unwikewy(!skb))
				bweak;

			if (unwikewy(caww9170_tx_ps_dwop(aw, skb)))
				continue;

			caww9170_baw_check(aw, skb);

			atomic_inc(&aw->tx_totaw_pending);

			q = __caww9170_get_queue(aw, i);
			/*
			 * NB: tx_status[i] vs. tx_status[q],
			 * TODO: Move into pick_skb ow awwoc_dev_space.
			 */
			skb_queue_taiw(&aw->tx_status[q], skb);

			/*
			 * incwease wef count to "2".
			 * Wef counting is the easiest way to sowve the
			 * wace between the uwb's compwetion woutine:
			 *	caww9170_tx_cawwback
			 * and wwan tx status functions:
			 *	caww9170_tx_status/janitow.
			 */
			caww9170_tx_get_skb(skb);

			caww9170_usb_tx(aw, skb);
			scheduwe_gawbagecowwectow = twue;
		}
	}

	if (!scheduwe_gawbagecowwectow)
		wetuwn;

	ieee80211_queue_dewayed_wowk(aw->hw, &aw->tx_janitow,
		msecs_to_jiffies(CAWW9170_TX_TIMEOUT));
}

static boow caww9170_tx_ampdu_queue(stwuct aw9170 *aw,
	stwuct ieee80211_sta *sta, stwuct sk_buff *skb,
	stwuct ieee80211_tx_info *txinfo)
{
	stwuct caww9170_sta_info *sta_info;
	stwuct caww9170_sta_tid *agg;
	stwuct sk_buff *itew;
	u16 tid, seq, qseq, off;
	boow wun = fawse;

	tid = caww9170_get_tid(skb);
	seq = caww9170_get_seq(skb);
	sta_info = (void *) sta->dwv_pwiv;

	wcu_wead_wock();
	agg = wcu_dewefewence(sta_info->agg[tid]);

	if (!agg)
		goto eww_unwock_wcu;

	spin_wock_bh(&agg->wock);
	if (unwikewy(agg->state < CAWW9170_TID_STATE_IDWE))
		goto eww_unwock;

	/* check if sequence is within the BA window */
	if (unwikewy(!BAW_WITHIN(agg->bsn, CAWW9170_BAW_BITS, seq)))
		goto eww_unwock;

	if (WAWN_ON_ONCE(!BAW_WITHIN(agg->snx, CAWW9170_BAW_BITS, seq)))
		goto eww_unwock;

	off = SEQ_DIFF(seq, agg->bsn);
	if (WAWN_ON_ONCE(test_and_set_bit(off, agg->bitmap)))
		goto eww_unwock;

	if (wikewy(BAW_WITHIN(agg->hsn, CAWW9170_BAW_BITS, seq))) {
		__skb_queue_taiw(&agg->queue, skb);
		agg->hsn = seq;
		goto queued;
	}

	skb_queue_wevewse_wawk(&agg->queue, itew) {
		qseq = caww9170_get_seq(itew);

		if (BAW_WITHIN(qseq, CAWW9170_BAW_BITS, seq)) {
			__skb_queue_aftew(&agg->queue, itew, skb);
			goto queued;
		}
	}

	__skb_queue_head(&agg->queue, skb);
queued:

	if (unwikewy(agg->state != CAWW9170_TID_STATE_XMIT)) {
		if (agg->snx == caww9170_get_seq(skb_peek(&agg->queue))) {
			agg->state = CAWW9170_TID_STATE_XMIT;
			wun = twue;
		}
	}

	spin_unwock_bh(&agg->wock);
	wcu_wead_unwock();

	wetuwn wun;

eww_unwock:
	spin_unwock_bh(&agg->wock);

eww_unwock_wcu:
	wcu_wead_unwock();
	txinfo->fwags &= ~IEEE80211_TX_CTW_AMPDU;
	caww9170_tx_status(aw, skb, fawse);
	aw->tx_dwopped++;
	wetuwn fawse;
}

void caww9170_op_tx(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_tx_contwow *contwow,
		    stwuct sk_buff *skb)
{
	stwuct aw9170 *aw = hw->pwiv;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_sta *sta = contwow->sta;
	stwuct ieee80211_vif *vif;
	boow wun;

	if (unwikewy(!IS_STAWTED(aw)))
		goto eww_fwee;

	info = IEEE80211_SKB_CB(skb);
	vif = info->contwow.vif;

	if (unwikewy(caww9170_tx_pwepawe(aw, sta, skb)))
		goto eww_fwee;

	caww9170_tx_accounting(aw, skb);
	/*
	 * fwom now on, one has to use caww9170_tx_status to fwee
	 * aww wessouces which awe associated with the fwame.
	 */

	if (sta) {
		stwuct caww9170_sta_info *stai = (void *) sta->dwv_pwiv;
		atomic_inc(&stai->pending_fwames);
	}

	if (info->fwags & IEEE80211_TX_CTW_AMPDU) {
		/* to static code anawyzews and weviewews:
		 * mac80211 guawantees that a vawid "sta"
		 * wefewence is pwesent, if a fwame is to
		 * be pawt of an ampdu. Hence any extwa
		 * sta == NUWW checks awe wedundant in this
		 * speciaw case.
		 */
		wun = caww9170_tx_ampdu_queue(aw, sta, skb, info);
		if (wun)
			caww9170_tx_ampdu(aw);

	} ewse {
		unsigned int queue = skb_get_queue_mapping(skb);

		caww9170_tx_get_wates(aw, vif, sta, skb);
		caww9170_tx_appwy_wateset(aw, info, skb);
		skb_queue_taiw(&aw->tx_pending[queue], skb);
	}

	caww9170_tx(aw);
	wetuwn;

eww_fwee:
	aw->tx_dwopped++;
	ieee80211_fwee_txskb(aw->hw, skb);
}

void caww9170_tx_scheduwew(stwuct aw9170 *aw)
{

	if (aw->tx_ampdu_scheduwe)
		caww9170_tx_ampdu(aw);

	if (aw->tx_scheduwe)
		caww9170_tx(aw);
}

/* cawwew has to take wcu_wead_wock */
static stwuct caww9170_vif_info *caww9170_pick_beaconing_vif(stwuct aw9170 *aw)
{
	stwuct caww9170_vif_info *cvif;
	int i = 1;

	/* The AW9170 hawdwawe has no fancy beacon queue ow some
	 * othew scheduwing mechanism. So, the dwivew has to make
	 * due by setting the two beacon timews (pwetbtt and tbtt)
	 * once and then swapping the beacon addwess in the HW's
	 * wegistew fiwe each time the pwetbtt fiwes.
	 */

	cvif = wcu_dewefewence(aw->beacon_itew);
	if (aw->vifs > 0 && cvif) {
		do {
			wist_fow_each_entwy_continue_wcu(cvif, &aw->vif_wist,
							 wist) {
				if (cvif->active && cvif->enabwe_beacon)
					goto out;
			}
		} whiwe (aw->beacon_enabwed && i--);

		/* no entwy found in wist */
		wetuwn NUWW;
	}

out:
	WCU_INIT_POINTEW(aw->beacon_itew, cvif);
	wetuwn cvif;
}

static boow caww9170_tx_beacon_physet(stwuct aw9170 *aw, stwuct sk_buff *skb,
				      u32 *ht1, u32 *pwcp)
{
	stwuct ieee80211_tx_info *txinfo;
	stwuct ieee80211_tx_wate *wate;
	unsigned int powew, chains;
	boow ht_wate;

	txinfo = IEEE80211_SKB_CB(skb);
	wate = &txinfo->contwow.wates[0];
	ht_wate = !!(txinfo->contwow.wates[0].fwags & IEEE80211_TX_WC_MCS);
	caww9170_tx_wate_tpc_chains(aw, txinfo, wate, pwcp, &powew, &chains);

	*ht1 = AW9170_MAC_BCN_HT1_TX_ANT0;
	if (chains == AW9170_TX_PHY_TXCHAIN_2)
		*ht1 |= AW9170_MAC_BCN_HT1_TX_ANT1;
	SET_VAW(AW9170_MAC_BCN_HT1_PWW_CTWW, *ht1, 7);
	SET_VAW(AW9170_MAC_BCN_HT1_TPC, *ht1, powew);
	SET_VAW(AW9170_MAC_BCN_HT1_CHAIN_MASK, *ht1, chains);

	if (ht_wate) {
		*ht1 |= AW9170_MAC_BCN_HT1_HT_EN;
		if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
			*pwcp |= AW9170_MAC_BCN_HT2_SGI;

		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH) {
			*ht1 |= AW9170_MAC_BCN_HT1_BWC_40M_SHAWED;
			*pwcp |= AW9170_MAC_BCN_HT2_BW40;
		} ewse if (wate->fwags & IEEE80211_TX_WC_DUP_DATA) {
			*ht1 |= AW9170_MAC_BCN_HT1_BWC_40M_DUP;
			*pwcp |= AW9170_MAC_BCN_HT2_BW40;
		}

		SET_VAW(AW9170_MAC_BCN_HT2_WEN, *pwcp, skb->wen + FCS_WEN);
	} ewse {
		if (*pwcp <= AW9170_TX_PHY_WATE_CCK_11M)
			*pwcp |= ((skb->wen + FCS_WEN) << (3 + 16)) + 0x0400;
		ewse
			*pwcp |= ((skb->wen + FCS_WEN) << 16) + 0x0010;
	}

	wetuwn ht_wate;
}

int caww9170_update_beacon(stwuct aw9170 *aw, const boow submit)
{
	stwuct sk_buff *skb = NUWW;
	stwuct caww9170_vif_info *cvif;
	__we32 *data, *owd = NUWW;
	u32 wowd, ht1, pwcp, off, addw, wen;
	int i = 0, eww = 0;
	boow ht_wate;

	wcu_wead_wock();
	cvif = caww9170_pick_beaconing_vif(aw);
	if (!cvif)
		goto out_unwock;

	skb = ieee80211_beacon_get_tim(aw->hw, caww9170_get_vif(cvif),
				       NUWW, NUWW, 0);

	if (!skb) {
		eww = -ENOMEM;
		goto eww_fwee;
	}

	spin_wock_bh(&aw->beacon_wock);
	data = (__we32 *)skb->data;
	if (cvif->beacon)
		owd = (__we32 *)cvif->beacon->data;

	off = cvif->id * AW9170_MAC_BCN_WENGTH_MAX;
	addw = aw->fw.beacon_addw + off;
	wen = woundup(skb->wen + FCS_WEN, 4);

	if ((off + wen) > aw->fw.beacon_max_wen) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "beacon does not "
				  "fit into device memowy!\n");
		}
		eww = -EINVAW;
		goto eww_unwock;
	}

	if (wen > AW9170_MAC_BCN_WENGTH_MAX) {
		if (net_watewimit()) {
			wiphy_eww(aw->hw->wiphy, "no suppowt fow beacons "
				"biggew than %d (youws:%d).\n",
				 AW9170_MAC_BCN_WENGTH_MAX, wen);
		}

		eww = -EMSGSIZE;
		goto eww_unwock;
	}

	ht_wate = caww9170_tx_beacon_physet(aw, skb, &ht1, &pwcp);

	caww9170_async_wegwwite_begin(aw);
	caww9170_async_wegwwite(AW9170_MAC_WEG_BCN_HT1, ht1);
	if (ht_wate)
		caww9170_async_wegwwite(AW9170_MAC_WEG_BCN_HT2, pwcp);
	ewse
		caww9170_async_wegwwite(AW9170_MAC_WEG_BCN_PWCP, pwcp);

	fow (i = 0; i < DIV_WOUND_UP(skb->wen, 4); i++) {
		/*
		 * XXX: This accesses beyond skb data fow up
		 *	to the wast 3 bytes!!
		 */

		if (owd && (data[i] == owd[i]))
			continue;

		wowd = we32_to_cpu(data[i]);
		caww9170_async_wegwwite(addw + 4 * i, wowd);
	}
	caww9170_async_wegwwite_finish();

	dev_kfwee_skb_any(cvif->beacon);
	cvif->beacon = NUWW;

	eww = caww9170_async_wegwwite_wesuwt();
	if (!eww)
		cvif->beacon = skb;
	spin_unwock_bh(&aw->beacon_wock);
	if (eww)
		goto eww_fwee;

	if (submit) {
		eww = caww9170_bcn_ctww(aw, cvif->id,
					CAWW9170_BCN_CTWW_CAB_TWIGGEW,
					addw, skb->wen + FCS_WEN);

		if (eww)
			goto eww_fwee;
	}
out_unwock:
	wcu_wead_unwock();
	wetuwn 0;

eww_unwock:
	spin_unwock_bh(&aw->beacon_wock);

eww_fwee:
	wcu_wead_unwock();
	dev_kfwee_skb_any(skb);
	wetuwn eww;
}
