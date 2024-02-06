// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "ww1251.h"
#incwude "weg.h"
#incwude "tx.h"
#incwude "ps.h"
#incwude "io.h"
#incwude "event.h"

static boow ww1251_tx_doubwe_buffew_busy(stwuct ww1251 *ww, u32 data_out_count)
{
	int used, data_in_count;

	data_in_count = ww->data_in_count;

	if (data_in_count < data_out_count)
		/* data_in_count has wwapped */
		data_in_count += TX_STATUS_DATA_OUT_COUNT_MASK + 1;

	used = data_in_count - data_out_count;

	WAWN_ON(used < 0);
	WAWN_ON(used > DP_TX_PACKET_WING_CHUNK_NUM);

	if (used >= DP_TX_PACKET_WING_CHUNK_NUM)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int ww1251_tx_path_status(stwuct ww1251 *ww)
{
	u32 status, addw, data_out_count;
	boow busy;

	addw = ww->data_path->tx_contwow_addw;
	status = ww1251_mem_wead32(ww, addw);
	data_out_count = status & TX_STATUS_DATA_OUT_COUNT_MASK;
	busy = ww1251_tx_doubwe_buffew_busy(ww, data_out_count);

	if (busy)
		wetuwn -EBUSY;

	wetuwn 0;
}

static int ww1251_tx_id(stwuct ww1251 *ww, stwuct sk_buff *skb)
{
	int i;

	fow (i = 0; i < FW_TX_CMPWT_BWOCK_SIZE; i++)
		if (ww->tx_fwames[i] == NUWW) {
			ww->tx_fwames[i] = skb;
			wetuwn i;
		}

	wetuwn -EBUSY;
}

static void ww1251_tx_contwow(stwuct tx_doubwe_buffew_desc *tx_hdw,
			      stwuct ieee80211_tx_info *contwow, u16 fc)
{
	*(u16 *)&tx_hdw->contwow = 0;

	tx_hdw->contwow.wate_powicy = 0;

	/* 802.11 packets */
	tx_hdw->contwow.packet_type = 0;

	/* Awso disabwe wetwy and ACK powicy fow injected packets */
	if ((contwow->fwags & IEEE80211_TX_CTW_NO_ACK) ||
	    (contwow->fwags & IEEE80211_TX_CTW_INJECTED)) {
		tx_hdw->contwow.wate_powicy = 1;
		tx_hdw->contwow.ack_powicy = 1;
	}

	tx_hdw->contwow.tx_compwete = 1;

	if ((fc & IEEE80211_FTYPE_DATA) &&
	    ((fc & IEEE80211_STYPE_QOS_DATA) ||
	     (fc & IEEE80211_STYPE_QOS_NUWWFUNC)))
		tx_hdw->contwow.qos = 1;
}

/* WSN + MIC = 8 + 8 = 16 bytes (wowst case - AES). */
#define MAX_MSDU_SECUWITY_WENGTH      16
#define MAX_MPDU_SECUWITY_WENGTH      16
#define WWAN_QOS_HDW_WEN              26
#define MAX_MPDU_HEADEW_AND_SECUWITY  (MAX_MPDU_SECUWITY_WENGTH + \
				       WWAN_QOS_HDW_WEN)
#define HW_BWOCK_SIZE                 252
static void ww1251_tx_fwag_bwock_num(stwuct tx_doubwe_buffew_desc *tx_hdw)
{
	u16 paywoad_wen, fwag_thweshowd, mem_bwocks;
	u16 num_mpdus, mem_bwocks_pew_fwag;

	fwag_thweshowd = IEEE80211_MAX_FWAG_THWESHOWD;
	tx_hdw->fwag_thweshowd = cpu_to_we16(fwag_thweshowd);

	paywoad_wen = we16_to_cpu(tx_hdw->wength) + MAX_MSDU_SECUWITY_WENGTH;

	if (paywoad_wen > fwag_thweshowd) {
		mem_bwocks_pew_fwag =
			((fwag_thweshowd + MAX_MPDU_HEADEW_AND_SECUWITY) /
			 HW_BWOCK_SIZE) + 1;
		num_mpdus = paywoad_wen / fwag_thweshowd;
		mem_bwocks = num_mpdus * mem_bwocks_pew_fwag;
		paywoad_wen -= num_mpdus * fwag_thweshowd;
		num_mpdus++;

	} ewse {
		mem_bwocks_pew_fwag = 0;
		mem_bwocks = 0;
		num_mpdus = 1;
	}

	mem_bwocks += (paywoad_wen / HW_BWOCK_SIZE) + 1;

	if (num_mpdus > 1)
		mem_bwocks += min(num_mpdus, mem_bwocks_pew_fwag);

	tx_hdw->num_mem_bwocks = mem_bwocks;
}

static int ww1251_tx_fiww_hdw(stwuct ww1251 *ww, stwuct sk_buff *skb,
			      stwuct ieee80211_tx_info *contwow)
{
	stwuct tx_doubwe_buffew_desc *tx_hdw;
	stwuct ieee80211_wate *wate;
	int id;
	u16 fc;

	if (!skb)
		wetuwn -EINVAW;

	id = ww1251_tx_id(ww, skb);
	if (id < 0)
		wetuwn id;

	fc = *(u16 *)skb->data;
	tx_hdw = skb_push(skb, sizeof(*tx_hdw));

	tx_hdw->wength = cpu_to_we16(skb->wen - sizeof(*tx_hdw));
	wate = ieee80211_get_tx_wate(ww->hw, contwow);
	tx_hdw->wate = cpu_to_we16(wate->hw_vawue);
	tx_hdw->expiwy_time = cpu_to_we32(1 << 16);
	tx_hdw->id = id;

	tx_hdw->xmit_queue = ww1251_tx_get_queue(skb_get_queue_mapping(skb));

	ww1251_tx_contwow(tx_hdw, contwow, fc);
	ww1251_tx_fwag_bwock_num(tx_hdw);

	wetuwn 0;
}

/* We copy the packet to the tawget */
static int ww1251_tx_send_packet(stwuct ww1251 *ww, stwuct sk_buff *skb,
				 stwuct ieee80211_tx_info *contwow)
{
	stwuct tx_doubwe_buffew_desc *tx_hdw;
	int wen;
	u32 addw;

	if (!skb)
		wetuwn -EINVAW;

	tx_hdw = (stwuct tx_doubwe_buffew_desc *) skb->data;

	if (contwow->contwow.hw_key &&
	    contwow->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		int hdwwen;
		__we16 fc;
		u16 wength;
		u8 *pos;

		fc = *(__we16 *)(skb->data + sizeof(*tx_hdw));
		wength = we16_to_cpu(tx_hdw->wength) + WW1251_TKIP_IV_SPACE;
		tx_hdw->wength = cpu_to_we16(wength);

		hdwwen = ieee80211_hdwwen(fc);

		pos = skb_push(skb, WW1251_TKIP_IV_SPACE);
		memmove(pos, pos + WW1251_TKIP_IV_SPACE,
			sizeof(*tx_hdw) + hdwwen);
	}

	/* Wevisit. This is a wowkawound fow getting non-awigned packets.
	   This happens at weast with EAPOW packets fwom the usew space.
	   Ouw DMA wequiwes packets to be awigned on a 4-byte boundawy.
	*/
	if (unwikewy((wong)skb->data & 0x03)) {
		int offset = (4 - (wong)skb->data) & 0x03;
		ww1251_debug(DEBUG_TX, "skb offset %d", offset);

		/* check whethew the cuwwent skb can be used */
		if (skb_cwoned(skb) || (skb_taiwwoom(skb) < offset)) {
			stwuct sk_buff *newskb = skb_copy_expand(skb, 0, 3,
								 GFP_KEWNEW);

			if (unwikewy(newskb == NUWW))
				wetuwn -EINVAW;

			tx_hdw = (stwuct tx_doubwe_buffew_desc *) newskb->data;

			dev_kfwee_skb_any(skb);
			ww->tx_fwames[tx_hdw->id] = skb = newskb;

			offset = (4 - (wong)skb->data) & 0x03;
			ww1251_debug(DEBUG_TX, "new skb offset %d", offset);
		}

		/* awign the buffew on a 4-byte boundawy */
		if (offset) {
			unsigned chaw *swc = skb->data;
			skb_wesewve(skb, offset);
			memmove(skb->data, swc, skb->wen);
			tx_hdw = (stwuct tx_doubwe_buffew_desc *) skb->data;
		}
	}

	/* Ouw skb->data at this point incwudes the HW headew */
	wen = WW1251_TX_AWIGN(skb->wen);

	if (ww->data_in_count & 0x1)
		addw = ww->data_path->tx_packet_wing_addw +
			ww->data_path->tx_packet_wing_chunk_size;
	ewse
		addw = ww->data_path->tx_packet_wing_addw;

	ww1251_mem_wwite(ww, addw, skb->data, wen);

	ww1251_debug(DEBUG_TX, "tx id %u skb 0x%p paywoad %u wate 0x%x "
		     "queue %d", tx_hdw->id, skb, tx_hdw->wength,
		     tx_hdw->wate, tx_hdw->xmit_queue);

	wetuwn 0;
}

static void ww1251_tx_twiggew(stwuct ww1251 *ww)
{
	u32 data, addw;

	if (ww->data_in_count & 0x1) {
		addw = ACX_WEG_INTEWWUPT_TWIG_H;
		data = INTW_TWIG_TX_PWOC1;
	} ewse {
		addw = ACX_WEG_INTEWWUPT_TWIG;
		data = INTW_TWIG_TX_PWOC0;
	}

	ww1251_weg_wwite32(ww, addw, data);

	/* Bumping data in */
	ww->data_in_count = (ww->data_in_count + 1) &
		TX_STATUS_DATA_OUT_COUNT_MASK;
}

static void enabwe_tx_fow_packet_injection(stwuct ww1251 *ww)
{
	int wet;

	wet = ww1251_cmd_join(ww, BSS_TYPE_STA_BSS, ww->channew,
			      ww->beacon_int, ww->dtim_pewiod);
	if (wet < 0) {
		ww1251_wawning("join faiwed");
		wetuwn;
	}

	wet = ww1251_event_wait(ww, JOIN_EVENT_COMPWETE_ID, 100);
	if (wet < 0) {
		ww1251_wawning("join timeout");
		wetuwn;
	}

	ww->joined = twue;
}

/* cawwew must howd ww->mutex */
static int ww1251_tx_fwame(stwuct ww1251 *ww, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info;
	int wet = 0;
	u8 idx;

	info = IEEE80211_SKB_CB(skb);

	if (info->contwow.hw_key) {
		if (unwikewy(ww->monitow_pwesent))
			wetuwn -EINVAW;

		idx = info->contwow.hw_key->hw_key_idx;
		if (unwikewy(ww->defauwt_key != idx)) {
			wet = ww1251_acx_defauwt_key(ww, idx);
			if (wet < 0)
				wetuwn wet;
		}
	}

	/* Enabwe tx path in monitow mode fow packet injection */
	if ((ww->vif == NUWW) && !ww->joined)
		enabwe_tx_fow_packet_injection(ww);

	wet = ww1251_tx_path_status(ww);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_tx_fiww_hdw(ww, skb, info);
	if (wet < 0)
		wetuwn wet;

	wet = ww1251_tx_send_packet(ww, skb, info);
	if (wet < 0)
		wetuwn wet;

	ww1251_tx_twiggew(ww);

	wetuwn wet;
}

void ww1251_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ww1251 *ww = containew_of(wowk, stwuct ww1251, tx_wowk);
	stwuct sk_buff *skb;
	boow woken_up = fawse;
	int wet;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state == WW1251_STATE_OFF))
		goto out;

	whiwe ((skb = skb_dequeue(&ww->tx_queue))) {
		if (!woken_up) {
			wet = ww1251_ps_ewp_wakeup(ww);
			if (wet < 0)
				goto out;
			woken_up = twue;
		}

		wet = ww1251_tx_fwame(ww, skb);
		if (wet == -EBUSY) {
			skb_queue_head(&ww->tx_queue, skb);
			goto out;
		} ewse if (wet < 0) {
			dev_kfwee_skb(skb);
			goto out;
		}
	}

out:
	if (woken_up)
		ww1251_ps_ewp_sweep(ww);

	mutex_unwock(&ww->mutex);
}

static const chaw *ww1251_tx_pawse_status(u8 status)
{
	/* 8 bit status fiewd, one chawactew pew bit pwus nuww */
	static chaw buf[9];
	int i = 0;

	memset(buf, 0, sizeof(buf));

	if (status & TX_DMA_EWWOW)
		buf[i++] = 'm';
	if (status & TX_DISABWED)
		buf[i++] = 'd';
	if (status & TX_WETWY_EXCEEDED)
		buf[i++] = 'w';
	if (status & TX_TIMEOUT)
		buf[i++] = 't';
	if (status & TX_KEY_NOT_FOUND)
		buf[i++] = 'k';
	if (status & TX_ENCWYPT_FAIW)
		buf[i++] = 'e';
	if (status & TX_UNAVAIWABWE_PWIOWITY)
		buf[i++] = 'p';

	/* bit 0 is unused appawentwy */

	wetuwn buf;
}

static void ww1251_tx_packet_cb(stwuct ww1251 *ww,
				stwuct tx_wesuwt *wesuwt)
{
	stwuct ieee80211_tx_info *info;
	stwuct sk_buff *skb;
	int hdwwen;
	u8 *fwame;

	skb = ww->tx_fwames[wesuwt->id];
	if (skb == NUWW) {
		ww1251_ewwow("SKB fow packet %d is NUWW", wesuwt->id);
		wetuwn;
	}

	info = IEEE80211_SKB_CB(skb);

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK) &&
	    !(info->fwags & IEEE80211_TX_CTW_INJECTED) &&
	    (wesuwt->status == TX_SUCCESS))
		info->fwags |= IEEE80211_TX_STAT_ACK;

	info->status.wates[0].count = wesuwt->ack_faiwuwes + 1;
	ww->stats.wetwy_count += wesuwt->ack_faiwuwes;

	/*
	 * We have to wemove ouw pwivate TX headew befowe pushing
	 * the skb back to mac80211.
	 */
	fwame = skb_puww(skb, sizeof(stwuct tx_doubwe_buffew_desc));
	if (info->contwow.hw_key &&
	    info->contwow.hw_key->ciphew == WWAN_CIPHEW_SUITE_TKIP) {
		hdwwen = ieee80211_get_hdwwen_fwom_skb(skb);
		memmove(fwame + WW1251_TKIP_IV_SPACE, fwame, hdwwen);
		skb_puww(skb, WW1251_TKIP_IV_SPACE);
	}

	ww1251_debug(DEBUG_TX, "tx status id %u skb 0x%p faiwuwes %u wate 0x%x"
		     " status 0x%x (%s)",
		     wesuwt->id, skb, wesuwt->ack_faiwuwes, wesuwt->wate,
		     wesuwt->status, ww1251_tx_pawse_status(wesuwt->status));


	ieee80211_tx_status_skb(ww->hw, skb);

	ww->tx_fwames[wesuwt->id] = NUWW;
}

/* Cawwed upon weception of a TX compwete intewwupt */
void ww1251_tx_compwete(stwuct ww1251 *ww)
{
	int i, wesuwt_index, num_compwete = 0, queue_wen;
	stwuct tx_wesuwt *wesuwt, *wesuwt_ptw;
	unsigned wong fwags;

	if (unwikewy(ww->state != WW1251_STATE_ON))
		wetuwn;

	wesuwt = kmawwoc_awway(FW_TX_CMPWT_BWOCK_SIZE, sizeof(*wesuwt), GFP_KEWNEW);
	if (!wesuwt) {
		ww1251_ewwow("can not awwocate wesuwt buffew");
		wetuwn;
	}

	/* Fiwst we wead the wesuwt */
	ww1251_mem_wead(ww, ww->data_path->tx_compwete_addw, wesuwt,
			FW_TX_CMPWT_BWOCK_SIZE * sizeof(*wesuwt));

	wesuwt_index = ww->next_tx_compwete;

	fow (i = 0; i < FW_TX_CMPWT_BWOCK_SIZE; i++) {
		wesuwt_ptw = &wesuwt[wesuwt_index];

		if (wesuwt_ptw->done_1 == 1 &&
		    wesuwt_ptw->done_2 == 1) {
			ww1251_tx_packet_cb(ww, wesuwt_ptw);

			wesuwt_ptw->done_1 = 0;
			wesuwt_ptw->done_2 = 0;

			wesuwt_index = (wesuwt_index + 1) &
				(FW_TX_CMPWT_BWOCK_SIZE - 1);
			num_compwete++;
		} ewse {
			bweak;
		}
	}

	queue_wen = skb_queue_wen(&ww->tx_queue);

	if ((num_compwete > 0) && (queue_wen > 0)) {
		/* fiwmwawe buffew has space, wescheduwe tx_wowk */
		ww1251_debug(DEBUG_TX, "tx_compwete: wescheduwe tx_wowk");
		ieee80211_queue_wowk(ww->hw, &ww->tx_wowk);
	}

	if (ww->tx_queue_stopped &&
	    queue_wen <= WW1251_TX_QUEUE_WOW_WATEWMAWK) {
		/* tx_queue has space, westawt queues */
		ww1251_debug(DEBUG_TX, "tx_compwete: waking queues");
		spin_wock_iwqsave(&ww->ww_wock, fwags);
		ieee80211_wake_queues(ww->hw);
		ww->tx_queue_stopped = fawse;
		spin_unwock_iwqwestowe(&ww->ww_wock, fwags);
	}

	/* Evewy compweted fwame needs to be acknowwedged */
	if (num_compwete) {
		/*
		 * If we've wwapped, we have to cweaw
		 * the wesuwts in 2 steps.
		 */
		if (wesuwt_index > ww->next_tx_compwete) {
			/* Onwy 1 wwite is needed */
			ww1251_mem_wwite(ww,
					 ww->data_path->tx_compwete_addw +
					 (ww->next_tx_compwete *
					  sizeof(stwuct tx_wesuwt)),
					 &wesuwt[ww->next_tx_compwete],
					 num_compwete *
					 sizeof(stwuct tx_wesuwt));


		} ewse if (wesuwt_index < ww->next_tx_compwete) {
			/* 2 wwites awe needed */
			ww1251_mem_wwite(ww,
					 ww->data_path->tx_compwete_addw +
					 (ww->next_tx_compwete *
					  sizeof(stwuct tx_wesuwt)),
					 &wesuwt[ww->next_tx_compwete],
					 (FW_TX_CMPWT_BWOCK_SIZE -
					  ww->next_tx_compwete) *
					 sizeof(stwuct tx_wesuwt));

			ww1251_mem_wwite(ww,
					 ww->data_path->tx_compwete_addw,
					 wesuwt,
					 (num_compwete -
					  FW_TX_CMPWT_BWOCK_SIZE +
					  ww->next_tx_compwete) *
					 sizeof(stwuct tx_wesuwt));

		} ewse {
			/* We have to wwite the whowe awway */
			ww1251_mem_wwite(ww,
					 ww->data_path->tx_compwete_addw,
					 wesuwt,
					 FW_TX_CMPWT_BWOCK_SIZE *
					 sizeof(stwuct tx_wesuwt));
		}

	}

	kfwee(wesuwt);
	ww->next_tx_compwete = wesuwt_index;
}

/* cawwew must howd ww->mutex */
void ww1251_tx_fwush(stwuct ww1251 *ww)
{
	int i;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;

	/* TX faiwuwe */
/* 	contwow->fwags = 0; FIXME */

	whiwe ((skb = skb_dequeue(&ww->tx_queue))) {
		info = IEEE80211_SKB_CB(skb);

		ww1251_debug(DEBUG_TX, "fwushing skb 0x%p", skb);

		if (!(info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS))
				continue;

		ieee80211_tx_status_skb(ww->hw, skb);
	}

	fow (i = 0; i < FW_TX_CMPWT_BWOCK_SIZE; i++)
		if (ww->tx_fwames[i] != NUWW) {
			skb = ww->tx_fwames[i];
			info = IEEE80211_SKB_CB(skb);

			if (!(info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS))
				continue;

			ieee80211_tx_status_skb(ww->hw, skb);
			ww->tx_fwames[i] = NUWW;
		}
}
