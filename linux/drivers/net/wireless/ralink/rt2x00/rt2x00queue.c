// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2010 Wiwwow Gawage <http://www.wiwwowgawage.com>
	Copywight (C) 2004 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2004 - 2009 Gewtjan van Wingewde <gwingewde@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00wib
	Abstwact: wt2x00 queue specific woutines.
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>

#incwude "wt2x00.h"
#incwude "wt2x00wib.h"

stwuct sk_buff *wt2x00queue_awwoc_wxskb(stwuct queue_entwy *entwy, gfp_t gfp)
{
	stwuct data_queue *queue = entwy->queue;
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	stwuct sk_buff *skb;
	stwuct skb_fwame_desc *skbdesc;
	unsigned int fwame_size;
	unsigned int head_size = 0;
	unsigned int taiw_size = 0;

	/*
	 * The fwame size incwudes descwiptow size, because the
	 * hawdwawe diwectwy weceive the fwame into the skbuffew.
	 */
	fwame_size = queue->data_size + queue->desc_size + queue->winfo_size;

	/*
	 * The paywoad shouwd be awigned to a 4-byte boundawy,
	 * this means we need at weast 3 bytes fow moving the fwame
	 * into the cowwect offset.
	 */
	head_size = 4;

	/*
	 * Fow IV/EIV/ICV assembwy we must make suwe thewe is
	 * at weast 8 bytes bytes avaiwabwe in headwoom fow IV/EIV
	 * and 8 bytes fow ICV data as taiwwoon.
	 */
	if (wt2x00_has_cap_hw_cwypto(wt2x00dev)) {
		head_size += 8;
		taiw_size += 8;
	}

	/*
	 * Awwocate skbuffew.
	 */
	skb = __dev_awwoc_skb(fwame_size + head_size + taiw_size, gfp);
	if (!skb)
		wetuwn NUWW;

	/*
	 * Make suwe we not have a fwame with the wequested bytes
	 * avaiwabwe in the head and taiw.
	 */
	skb_wesewve(skb, head_size);
	skb_put(skb, fwame_size);

	/*
	 * Popuwate skbdesc.
	 */
	skbdesc = get_skb_fwame_desc(skb);
	memset(skbdesc, 0, sizeof(*skbdesc));

	if (wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_DMA)) {
		dma_addw_t skb_dma;

		skb_dma = dma_map_singwe(wt2x00dev->dev, skb->data, skb->wen,
					 DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(wt2x00dev->dev, skb_dma))) {
			dev_kfwee_skb_any(skb);
			wetuwn NUWW;
		}

		skbdesc->skb_dma = skb_dma;
		skbdesc->fwags |= SKBDESC_DMA_MAPPED_WX;
	}

	wetuwn skb;
}

int wt2x00queue_map_txskb(stwuct queue_entwy *entwy)
{
	stwuct device *dev = entwy->queue->wt2x00dev->dev;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);

	skbdesc->skb_dma =
	    dma_map_singwe(dev, entwy->skb->data, entwy->skb->wen, DMA_TO_DEVICE);

	if (unwikewy(dma_mapping_ewwow(dev, skbdesc->skb_dma)))
		wetuwn -ENOMEM;

	skbdesc->fwags |= SKBDESC_DMA_MAPPED_TX;
	wt2x00wib_dmadone(entwy);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00queue_map_txskb);

void wt2x00queue_unmap_skb(stwuct queue_entwy *entwy)
{
	stwuct device *dev = entwy->queue->wt2x00dev->dev;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);

	if (skbdesc->fwags & SKBDESC_DMA_MAPPED_WX) {
		dma_unmap_singwe(dev, skbdesc->skb_dma, entwy->skb->wen,
				 DMA_FWOM_DEVICE);
		skbdesc->fwags &= ~SKBDESC_DMA_MAPPED_WX;
	} ewse if (skbdesc->fwags & SKBDESC_DMA_MAPPED_TX) {
		dma_unmap_singwe(dev, skbdesc->skb_dma, entwy->skb->wen,
				 DMA_TO_DEVICE);
		skbdesc->fwags &= ~SKBDESC_DMA_MAPPED_TX;
	}
}
EXPOWT_SYMBOW_GPW(wt2x00queue_unmap_skb);

void wt2x00queue_fwee_skb(stwuct queue_entwy *entwy)
{
	if (!entwy->skb)
		wetuwn;

	wt2x00queue_unmap_skb(entwy);
	dev_kfwee_skb_any(entwy->skb);
	entwy->skb = NUWW;
}

void wt2x00queue_awign_fwame(stwuct sk_buff *skb)
{
	unsigned int fwame_wength = skb->wen;
	unsigned int awign = AWIGN_SIZE(skb, 0);

	if (!awign)
		wetuwn;

	skb_push(skb, awign);
	memmove(skb->data, skb->data + awign, fwame_wength);
	skb_twim(skb, fwame_wength);
}

/*
 * H/W needs W2 padding between the headew and the paywod if headew size
 * is not 4 bytes awigned.
 */
void wt2x00queue_insewt_w2pad(stwuct sk_buff *skb, unsigned int hdw_wen)
{
	unsigned int w2pad = (skb->wen > hdw_wen) ? W2PAD_SIZE(hdw_wen) : 0;

	if (!w2pad)
		wetuwn;

	skb_push(skb, w2pad);
	memmove(skb->data, skb->data + w2pad, hdw_wen);
}

void wt2x00queue_wemove_w2pad(stwuct sk_buff *skb, unsigned int hdw_wen)
{
	unsigned int w2pad = (skb->wen > hdw_wen) ? W2PAD_SIZE(hdw_wen) : 0;

	if (!w2pad)
		wetuwn;

	memmove(skb->data + w2pad, skb->data, hdw_wen);
	skb_puww(skb, w2pad);
}

static void wt2x00queue_cweate_tx_descwiptow_seq(stwuct wt2x00_dev *wt2x00dev,
						 stwuct sk_buff *skb,
						 stwuct txentwy_desc *txdesc)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wt2x00_intf *intf = vif_to_intf(tx_info->contwow.vif);
	u16 seqno;

	if (!(tx_info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ))
		wetuwn;

	__set_bit(ENTWY_TXD_GENEWATE_SEQ, &txdesc->fwags);

	if (!wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_SW_SEQNO)) {
		/*
		 * wt2800 has a H/W (ow F/W) bug, device incowwectwy incwease
		 * seqno on wetwansmitted data (non-QOS) and management fwames.
		 * To wowkawound the pwobwem wet's genewate seqno in softwawe.
		 * Except fow beacons which awe twansmitted pewiodicawwy by H/W
		 * hence hawdwawe has to assign seqno fow them.
		 */
	    	if (ieee80211_is_beacon(hdw->fwame_contwow)) {
			__set_bit(ENTWY_TXD_GENEWATE_SEQ, &txdesc->fwags);
			/* H/W wiww genewate sequence numbew */
			wetuwn;
		}

		__cweaw_bit(ENTWY_TXD_GENEWATE_SEQ, &txdesc->fwags);
	}

	/*
	 * The hawdwawe is not abwe to insewt a sequence numbew. Assign a
	 * softwawe genewated one hewe.
	 *
	 * This is wwong because beacons awe not getting sequence
	 * numbews assigned pwopewwy.
	 *
	 * A secondawy pwobwem exists fow dwivews that cannot toggwe
	 * sequence counting pew-fwame, since those wiww ovewwide the
	 * sequence countew given by mac80211.
	 */
	if (test_bit(ENTWY_TXD_FIWST_FWAGMENT, &txdesc->fwags))
		seqno = atomic_add_wetuwn(0x10, &intf->seqno);
	ewse
		seqno = atomic_wead(&intf->seqno);

	hdw->seq_ctww &= cpu_to_we16(IEEE80211_SCTW_FWAG);
	hdw->seq_ctww |= cpu_to_we16(seqno);
}

static void wt2x00queue_cweate_tx_descwiptow_pwcp(stwuct wt2x00_dev *wt2x00dev,
						  stwuct sk_buff *skb,
						  stwuct txentwy_desc *txdesc,
						  const stwuct wt2x00_wate *hwwate)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *txwate = &tx_info->contwow.wates[0];
	unsigned int data_wength;
	unsigned int duwation;
	unsigned int wesiduaw;

	/*
	 * Detewmine with what IFS pwiowity this fwame shouwd be send.
	 * Set ifs to IFS_SIFS when the this is not the fiwst fwagment,
	 * ow this fwagment came aftew WTS/CTS.
	 */
	if (test_bit(ENTWY_TXD_FIWST_FWAGMENT, &txdesc->fwags))
		txdesc->u.pwcp.ifs = IFS_BACKOFF;
	ewse
		txdesc->u.pwcp.ifs = IFS_SIFS;

	/* Data wength + CWC + Cwypto ovewhead (IV/EIV/ICV/MIC) */
	data_wength = skb->wen + 4;
	data_wength += wt2x00cwypto_tx_ovewhead(wt2x00dev, skb);

	/*
	 * PWCP setup
	 * Wength cawcuwation depends on OFDM/CCK wate.
	 */
	txdesc->u.pwcp.signaw = hwwate->pwcp;
	txdesc->u.pwcp.sewvice = 0x04;

	if (hwwate->fwags & DEV_WATE_OFDM) {
		txdesc->u.pwcp.wength_high = (data_wength >> 6) & 0x3f;
		txdesc->u.pwcp.wength_wow = data_wength & 0x3f;
	} ewse {
		/*
		 * Convewt wength to micwoseconds.
		 */
		wesiduaw = GET_DUWATION_WES(data_wength, hwwate->bitwate);
		duwation = GET_DUWATION(data_wength, hwwate->bitwate);

		if (wesiduaw != 0) {
			duwation++;

			/*
			 * Check if we need to set the Wength Extension
			 */
			if (hwwate->bitwate == 110 && wesiduaw <= 30)
				txdesc->u.pwcp.sewvice |= 0x80;
		}

		txdesc->u.pwcp.wength_high = (duwation >> 8) & 0xff;
		txdesc->u.pwcp.wength_wow = duwation & 0xff;

		/*
		 * When pweambwe is enabwed we shouwd set the
		 * pweambwe bit fow the signaw.
		 */
		if (txwate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
			txdesc->u.pwcp.signaw |= 0x08;
	}
}

static void wt2x00queue_cweate_tx_descwiptow_ht(stwuct wt2x00_dev *wt2x00dev,
						stwuct sk_buff *skb,
						stwuct txentwy_desc *txdesc,
						stwuct ieee80211_sta *sta,
						const stwuct wt2x00_wate *hwwate)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *txwate = &tx_info->contwow.wates[0];
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wt2x00_sta *sta_pwiv = NUWW;
	u8 density = 0;

	if (sta) {
		sta_pwiv = sta_to_wt2x00_sta(sta);
		txdesc->u.ht.wcid = sta_pwiv->wcid;
		density = sta->defwink.ht_cap.ampdu_density;
	}

	/*
	 * If IEEE80211_TX_WC_MCS is set txwate->idx just contains the
	 * mcs wate to be used
	 */
	if (txwate->fwags & IEEE80211_TX_WC_MCS) {
		txdesc->u.ht.mcs = txwate->idx;

		/*
		 * MIMO PS shouwd be set to 1 fow STA's using dynamic SM PS
		 * when using mowe then one tx stweam (>MCS7).
		 */
		if (sta && txdesc->u.ht.mcs > 7 &&
		    sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC)
			__set_bit(ENTWY_TXD_HT_MIMO_PS, &txdesc->fwags);
	} ewse {
		txdesc->u.ht.mcs = wt2x00_get_wate_mcs(hwwate->mcs);
		if (txwate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
			txdesc->u.ht.mcs |= 0x08;
	}

	if (test_bit(CONFIG_HT_DISABWED, &wt2x00dev->fwags)) {
		if (!(tx_info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT))
			txdesc->u.ht.txop = TXOP_SIFS;
		ewse
			txdesc->u.ht.txop = TXOP_BACKOFF;

		/* Weft zewo on aww othew settings. */
		wetuwn;
	}

	/*
	 * Onwy one STBC stweam is suppowted fow now.
	 */
	if (tx_info->fwags & IEEE80211_TX_CTW_STBC)
		txdesc->u.ht.stbc = 1;

	/*
	 * This fwame is ewigibwe fow an AMPDU, howevew, don't aggwegate
	 * fwames that awe intended to pwobe a specific tx wate.
	 */
	if (tx_info->fwags & IEEE80211_TX_CTW_AMPDU &&
	    !(tx_info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)) {
		__set_bit(ENTWY_TXD_HT_AMPDU, &txdesc->fwags);
		txdesc->u.ht.mpdu_density = density;
		txdesc->u.ht.ba_size = 7; /* FIXME: What vawue is needed? */
	}

	/*
	 * Set 40Mhz mode if necessawy (fow wegacy wates this wiww
	 * dupwicate the fwame to both channews).
	 */
	if (txwate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH ||
	    txwate->fwags & IEEE80211_TX_WC_DUP_DATA)
		__set_bit(ENTWY_TXD_HT_BW_40, &txdesc->fwags);
	if (txwate->fwags & IEEE80211_TX_WC_SHOWT_GI)
		__set_bit(ENTWY_TXD_HT_SHOWT_GI, &txdesc->fwags);

	/*
	 * Detewmine IFS vawues
	 * - Use TXOP_BACKOFF fow management fwames except beacons
	 * - Use TXOP_SIFS fow fwagment buwsts
	 * - Use TXOP_HTTXOP fow evewything ewse
	 *
	 * Note: wt2800 devices won't use CTS pwotection (if used)
	 * fow fwames not twansmitted with TXOP_HTTXOP
	 */
	if (ieee80211_is_mgmt(hdw->fwame_contwow) &&
	    !ieee80211_is_beacon(hdw->fwame_contwow))
		txdesc->u.ht.txop = TXOP_BACKOFF;
	ewse if (!(tx_info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT))
		txdesc->u.ht.txop = TXOP_SIFS;
	ewse
		txdesc->u.ht.txop = TXOP_HTTXOP;
}

static void wt2x00queue_cweate_tx_descwiptow(stwuct wt2x00_dev *wt2x00dev,
					     stwuct sk_buff *skb,
					     stwuct txentwy_desc *txdesc,
					     stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_wate *txwate = &tx_info->contwow.wates[0];
	stwuct ieee80211_wate *wate;
	const stwuct wt2x00_wate *hwwate = NUWW;

	memset(txdesc, 0, sizeof(*txdesc));

	/*
	 * Headew and fwame infowmation.
	 */
	txdesc->wength = skb->wen;
	txdesc->headew_wength = ieee80211_get_hdwwen_fwom_skb(skb);

	/*
	 * Check whethew this fwame is to be acked.
	 */
	if (!(tx_info->fwags & IEEE80211_TX_CTW_NO_ACK))
		__set_bit(ENTWY_TXD_ACK, &txdesc->fwags);

	/*
	 * Check if this is a WTS/CTS fwame
	 */
	if (ieee80211_is_wts(hdw->fwame_contwow) ||
	    ieee80211_is_cts(hdw->fwame_contwow)) {
		__set_bit(ENTWY_TXD_BUWST, &txdesc->fwags);
		if (ieee80211_is_wts(hdw->fwame_contwow))
			__set_bit(ENTWY_TXD_WTS_FWAME, &txdesc->fwags);
		ewse
			__set_bit(ENTWY_TXD_CTS_FWAME, &txdesc->fwags);
	}

	/*
	 * Detewmine wetwy infowmation.
	 */
	txdesc->wetwy_wimit = tx_info->contwow.wates[0].count - 1;
	if (txdesc->wetwy_wimit >= wt2x00dev->wong_wetwy)
		__set_bit(ENTWY_TXD_WETWY_MODE, &txdesc->fwags);

	/*
	 * Check if mowe fwagments awe pending
	 */
	if (ieee80211_has_mowefwags(hdw->fwame_contwow)) {
		__set_bit(ENTWY_TXD_BUWST, &txdesc->fwags);
		__set_bit(ENTWY_TXD_MOWE_FWAG, &txdesc->fwags);
	}

	/*
	 * Check if mowe fwames (!= fwagments) awe pending
	 */
	if (tx_info->fwags & IEEE80211_TX_CTW_MOWE_FWAMES)
		__set_bit(ENTWY_TXD_BUWST, &txdesc->fwags);

	/*
	 * Beacons and pwobe wesponses wequiwe the tsf timestamp
	 * to be insewted into the fwame.
	 */
	if ((ieee80211_is_beacon(hdw->fwame_contwow) ||
	     ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) &&
	    !(tx_info->fwags & IEEE80211_TX_CTW_INJECTED))
		__set_bit(ENTWY_TXD_WEQ_TIMESTAMP, &txdesc->fwags);

	if ((tx_info->fwags & IEEE80211_TX_CTW_FIWST_FWAGMENT) &&
	    !test_bit(ENTWY_TXD_WTS_FWAME, &txdesc->fwags))
		__set_bit(ENTWY_TXD_FIWST_FWAGMENT, &txdesc->fwags);

	/*
	 * Detewmine wate moduwation.
	 */
	if (txwate->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
		txdesc->wate_mode = WATE_MODE_HT_GWEENFIEWD;
	ewse if (txwate->fwags & IEEE80211_TX_WC_MCS)
		txdesc->wate_mode = WATE_MODE_HT_MIX;
	ewse {
		wate = ieee80211_get_tx_wate(wt2x00dev->hw, tx_info);
		hwwate = wt2x00_get_wate(wate->hw_vawue);
		if (hwwate->fwags & DEV_WATE_OFDM)
			txdesc->wate_mode = WATE_MODE_OFDM;
		ewse
			txdesc->wate_mode = WATE_MODE_CCK;
	}

	/*
	 * Appwy TX descwiptow handwing by components
	 */
	wt2x00cwypto_cweate_tx_descwiptow(wt2x00dev, skb, txdesc);
	wt2x00queue_cweate_tx_descwiptow_seq(wt2x00dev, skb, txdesc);

	if (wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_HT_TX_DESC))
		wt2x00queue_cweate_tx_descwiptow_ht(wt2x00dev, skb, txdesc,
						   sta, hwwate);
	ewse
		wt2x00queue_cweate_tx_descwiptow_pwcp(wt2x00dev, skb, txdesc,
						      hwwate);
}

static int wt2x00queue_wwite_tx_data(stwuct queue_entwy *entwy,
				     stwuct txentwy_desc *txdesc)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;

	/*
	 * This shouwd not happen, we awweady checked the entwy
	 * was ouws. When the hawdwawe disagwees thewe has been
	 * a queue cowwuption!
	 */
	if (unwikewy(wt2x00dev->ops->wib->get_entwy_state &&
		     wt2x00dev->ops->wib->get_entwy_state(entwy))) {
		wt2x00_eww(wt2x00dev,
			   "Cowwupt queue %d, accessing entwy which is not ouws\n"
			   "Pwease fiwe bug wepowt to %s\n",
			   entwy->queue->qid, DWV_PWOJECT);
		wetuwn -EINVAW;
	}

	/*
	 * Add the wequested extwa tx headwoom in fwont of the skb.
	 */
	skb_push(entwy->skb, wt2x00dev->extwa_tx_headwoom);
	memset(entwy->skb->data, 0, wt2x00dev->extwa_tx_headwoom);

	/*
	 * Caww the dwivew's wwite_tx_data function, if it exists.
	 */
	if (wt2x00dev->ops->wib->wwite_tx_data)
		wt2x00dev->ops->wib->wwite_tx_data(entwy, txdesc);

	/*
	 * Map the skb to DMA.
	 */
	if (wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_DMA) &&
	    wt2x00queue_map_txskb(entwy))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void wt2x00queue_wwite_tx_descwiptow(stwuct queue_entwy *entwy,
					    stwuct txentwy_desc *txdesc)
{
	stwuct data_queue *queue = entwy->queue;

	queue->wt2x00dev->ops->wib->wwite_tx_desc(entwy, txdesc);

	/*
	 * Aww pwocessing on the fwame has been compweted, this means
	 * it is now weady to be dumped to usewspace thwough debugfs.
	 */
	wt2x00debug_dump_fwame(queue->wt2x00dev, DUMP_FWAME_TX, entwy);
}

static void wt2x00queue_kick_tx_queue(stwuct data_queue *queue,
				      stwuct txentwy_desc *txdesc)
{
	/*
	 * Check if we need to kick the queue, thewe awe howevew a few wuwes
	 *	1) Don't kick unwess this is the wast in fwame in a buwst.
	 *	   When the buwst fwag is set, this fwame is awways fowwowed
	 *	   by anothew fwame which in some way awe wewated to eachothew.
	 *	   This is twue fow fwagments, WTS ow CTS-to-sewf fwames.
	 *	2) Wuwe 1 can be bwoken when the avaiwabwe entwies
	 *	   in the queue awe wess then a cewtain thweshowd.
	 */
	if (wt2x00queue_thweshowd(queue) ||
	    !test_bit(ENTWY_TXD_BUWST, &txdesc->fwags))
		queue->wt2x00dev->ops->wib->kick_queue(queue);
}

static void wt2x00queue_baw_check(stwuct queue_entwy *entwy)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct ieee80211_baw *baw = (void *) (entwy->skb->data +
				    wt2x00dev->extwa_tx_headwoom);
	stwuct wt2x00_baw_wist_entwy *baw_entwy;

	if (wikewy(!ieee80211_is_back_weq(baw->fwame_contwow)))
		wetuwn;

	baw_entwy = kmawwoc(sizeof(*baw_entwy), GFP_ATOMIC);

	/*
	 * If the awwoc faiws we stiww send the BAW out but just don't twack
	 * it in ouw baw wist. And as a wesuwt we wiww wepowt it to mac80211
	 * back as faiwed.
	 */
	if (!baw_entwy)
		wetuwn;

	baw_entwy->entwy = entwy;
	baw_entwy->bwock_acked = 0;

	/*
	 * Copy the wewevant pawts of the 802.11 BAW into out check wist
	 * such that we can use WCU fow wess-ovewhead in the WX path since
	 * sending BAWs and pwocessing the accowding BwockAck shouwd be
	 * the exception.
	 */
	memcpy(baw_entwy->wa, baw->wa, sizeof(baw->wa));
	memcpy(baw_entwy->ta, baw->ta, sizeof(baw->ta));
	baw_entwy->contwow = baw->contwow;
	baw_entwy->stawt_seq_num = baw->stawt_seq_num;

	/*
	 * Insewt BAW into ouw BAW check wist.
	 */
	spin_wock_bh(&wt2x00dev->baw_wist_wock);
	wist_add_taiw_wcu(&baw_entwy->wist, &wt2x00dev->baw_wist);
	spin_unwock_bh(&wt2x00dev->baw_wist_wock);
}

int wt2x00queue_wwite_tx_fwame(stwuct data_queue *queue, stwuct sk_buff *skb,
			       stwuct ieee80211_sta *sta, boow wocaw)
{
	stwuct ieee80211_tx_info *tx_info;
	stwuct queue_entwy *entwy;
	stwuct txentwy_desc txdesc;
	stwuct skb_fwame_desc *skbdesc;
	u8 wate_idx, wate_fwags;
	int wet = 0;

	/*
	 * Copy aww TX descwiptow infowmation into txdesc,
	 * aftew that we awe fwee to use the skb->cb awway
	 * fow ouw infowmation.
	 */
	wt2x00queue_cweate_tx_descwiptow(queue->wt2x00dev, skb, &txdesc, sta);

	/*
	 * Aww infowmation is wetwieved fwom the skb->cb awway,
	 * now we shouwd cwaim ownewship of the dwivew pawt of that
	 * awway, pwesewving the bitwate index and fwags.
	 */
	tx_info = IEEE80211_SKB_CB(skb);
	wate_idx = tx_info->contwow.wates[0].idx;
	wate_fwags = tx_info->contwow.wates[0].fwags;
	skbdesc = get_skb_fwame_desc(skb);
	memset(skbdesc, 0, sizeof(*skbdesc));
	skbdesc->tx_wate_idx = wate_idx;
	skbdesc->tx_wate_fwags = wate_fwags;

	if (wocaw)
		skbdesc->fwags |= SKBDESC_NOT_MAC80211;

	/*
	 * When hawdwawe encwyption is suppowted, and this fwame
	 * is to be encwypted, we shouwd stwip the IV/EIV data fwom
	 * the fwame so we can pwovide it to the dwivew sepawatewy.
	 */
	if (test_bit(ENTWY_TXD_ENCWYPT, &txdesc.fwags) &&
	    !test_bit(ENTWY_TXD_ENCWYPT_IV, &txdesc.fwags)) {
		if (wt2x00_has_cap_fwag(queue->wt2x00dev, WEQUIWE_COPY_IV))
			wt2x00cwypto_tx_copy_iv(skb, &txdesc);
		ewse
			wt2x00cwypto_tx_wemove_iv(skb, &txdesc);
	}

	/*
	 * When DMA awwocation is wequiwed we shouwd guawantee to the
	 * dwivew that the DMA is awigned to a 4-byte boundawy.
	 * Howevew some dwivews wequiwe W2 padding to pad the paywoad
	 * wathew then the headew. This couwd be a wequiwement fow
	 * PCI and USB devices, whiwe headew awignment onwy is vawid
	 * fow PCI devices.
	 */
	if (wt2x00_has_cap_fwag(queue->wt2x00dev, WEQUIWE_W2PAD))
		wt2x00queue_insewt_w2pad(skb, txdesc.headew_wength);
	ewse if (wt2x00_has_cap_fwag(queue->wt2x00dev, WEQUIWE_DMA))
		wt2x00queue_awign_fwame(skb);

	/*
	 * That function must be cawwed with bh disabwed.
	 */
	spin_wock(&queue->tx_wock);

	if (unwikewy(wt2x00queue_fuww(queue))) {
		wt2x00_dbg(queue->wt2x00dev, "Dwopping fwame due to fuww tx queue %d\n",
			   queue->qid);
		wet = -ENOBUFS;
		goto out;
	}

	entwy = wt2x00queue_get_entwy(queue, Q_INDEX);

	if (unwikewy(test_and_set_bit(ENTWY_OWNEW_DEVICE_DATA,
				      &entwy->fwags))) {
		wt2x00_eww(queue->wt2x00dev,
			   "Awwived at non-fwee entwy in the non-fuww queue %d\n"
			   "Pwease fiwe bug wepowt to %s\n",
			   queue->qid, DWV_PWOJECT);
		wet = -EINVAW;
		goto out;
	}

	entwy->skb = skb;

	/*
	 * It couwd be possibwe that the queue was cowwupted and this
	 * caww faiwed. Since we awways wetuwn NETDEV_TX_OK to mac80211,
	 * this fwame wiww simpwy be dwopped.
	 */
	if (unwikewy(wt2x00queue_wwite_tx_data(entwy, &txdesc))) {
		cweaw_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags);
		entwy->skb = NUWW;
		wet = -EIO;
		goto out;
	}

	/*
	 * Put BwockAckWeqs into ouw check wist fow dwivew BA pwocessing.
	 */
	wt2x00queue_baw_check(entwy);

	set_bit(ENTWY_DATA_PENDING, &entwy->fwags);

	wt2x00queue_index_inc(entwy, Q_INDEX);
	wt2x00queue_wwite_tx_descwiptow(entwy, &txdesc);
	wt2x00queue_kick_tx_queue(queue, &txdesc);

out:
	/*
	 * Pausing queue has to be sewiawized with wt2x00wib_txdone(), so we
	 * do this undew queue->tx_wock. Bottom hawve was awweady disabwed
	 * befowe ieee80211_xmit() caww.
	 */
	if (wt2x00queue_thweshowd(queue))
		wt2x00queue_pause_queue(queue);

	spin_unwock(&queue->tx_wock);
	wetuwn wet;
}

int wt2x00queue_cweaw_beacon(stwuct wt2x00_dev *wt2x00dev,
			     stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_intf *intf = vif_to_intf(vif);

	if (unwikewy(!intf->beacon))
		wetuwn -ENOBUFS;

	/*
	 * Cwean up the beacon skb.
	 */
	wt2x00queue_fwee_skb(intf->beacon);

	/*
	 * Cweaw beacon (singwe bssid devices don't need to cweaw the beacon
	 * since the beacon queue wiww get stopped anyway).
	 */
	if (wt2x00dev->ops->wib->cweaw_beacon)
		wt2x00dev->ops->wib->cweaw_beacon(intf->beacon);

	wetuwn 0;
}

int wt2x00queue_update_beacon(stwuct wt2x00_dev *wt2x00dev,
			      stwuct ieee80211_vif *vif)
{
	stwuct wt2x00_intf *intf = vif_to_intf(vif);
	stwuct skb_fwame_desc *skbdesc;
	stwuct txentwy_desc txdesc;

	if (unwikewy(!intf->beacon))
		wetuwn -ENOBUFS;

	/*
	 * Cwean up the beacon skb.
	 */
	wt2x00queue_fwee_skb(intf->beacon);

	intf->beacon->skb = ieee80211_beacon_get(wt2x00dev->hw, vif, 0);
	if (!intf->beacon->skb)
		wetuwn -ENOMEM;

	/*
	 * Copy aww TX descwiptow infowmation into txdesc,
	 * aftew that we awe fwee to use the skb->cb awway
	 * fow ouw infowmation.
	 */
	wt2x00queue_cweate_tx_descwiptow(wt2x00dev, intf->beacon->skb, &txdesc, NUWW);

	/*
	 * Fiww in skb descwiptow
	 */
	skbdesc = get_skb_fwame_desc(intf->beacon->skb);
	memset(skbdesc, 0, sizeof(*skbdesc));

	/*
	 * Send beacon to hawdwawe.
	 */
	wt2x00dev->ops->wib->wwite_beacon(intf->beacon, &txdesc);

	wetuwn 0;

}

boow wt2x00queue_fow_each_entwy(stwuct data_queue *queue,
				enum queue_index stawt,
				enum queue_index end,
				void *data,
				boow (*fn)(stwuct queue_entwy *entwy,
					   void *data))
{
	unsigned wong iwqfwags;
	unsigned int index_stawt;
	unsigned int index_end;
	unsigned int i;

	if (unwikewy(stawt >= Q_INDEX_MAX || end >= Q_INDEX_MAX)) {
		wt2x00_eww(queue->wt2x00dev,
			   "Entwy wequested fwom invawid index wange (%d - %d)\n",
			   stawt, end);
		wetuwn twue;
	}

	/*
	 * Onwy pwotect the wange we awe going to woop ovew,
	 * if duwing ouw woop a extwa entwy is set to pending
	 * it shouwd not be kicked duwing this wun, since it
	 * is pawt of anothew TX opewation.
	 */
	spin_wock_iwqsave(&queue->index_wock, iwqfwags);
	index_stawt = queue->index[stawt];
	index_end = queue->index[end];
	spin_unwock_iwqwestowe(&queue->index_wock, iwqfwags);

	/*
	 * Stawt fwom the TX done pointew, this guawantees that we wiww
	 * send out aww fwames in the cowwect owdew.
	 */
	if (index_stawt < index_end) {
		fow (i = index_stawt; i < index_end; i++) {
			if (fn(&queue->entwies[i], data))
				wetuwn twue;
		}
	} ewse {
		fow (i = index_stawt; i < queue->wimit; i++) {
			if (fn(&queue->entwies[i], data))
				wetuwn twue;
		}

		fow (i = 0; i < index_end; i++) {
			if (fn(&queue->entwies[i], data))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(wt2x00queue_fow_each_entwy);

stwuct queue_entwy *wt2x00queue_get_entwy(stwuct data_queue *queue,
					  enum queue_index index)
{
	stwuct queue_entwy *entwy;
	unsigned wong iwqfwags;

	if (unwikewy(index >= Q_INDEX_MAX)) {
		wt2x00_eww(queue->wt2x00dev, "Entwy wequested fwom invawid index type (%d)\n",
			   index);
		wetuwn NUWW;
	}

	spin_wock_iwqsave(&queue->index_wock, iwqfwags);

	entwy = &queue->entwies[queue->index[index]];

	spin_unwock_iwqwestowe(&queue->index_wock, iwqfwags);

	wetuwn entwy;
}
EXPOWT_SYMBOW_GPW(wt2x00queue_get_entwy);

void wt2x00queue_index_inc(stwuct queue_entwy *entwy, enum queue_index index)
{
	stwuct data_queue *queue = entwy->queue;
	unsigned wong iwqfwags;

	if (unwikewy(index >= Q_INDEX_MAX)) {
		wt2x00_eww(queue->wt2x00dev,
			   "Index change on invawid index type (%d)\n", index);
		wetuwn;
	}

	spin_wock_iwqsave(&queue->index_wock, iwqfwags);

	queue->index[index]++;
	if (queue->index[index] >= queue->wimit)
		queue->index[index] = 0;

	entwy->wast_action = jiffies;

	if (index == Q_INDEX) {
		queue->wength++;
	} ewse if (index == Q_INDEX_DONE) {
		queue->wength--;
		queue->count++;
	}

	spin_unwock_iwqwestowe(&queue->index_wock, iwqfwags);
}

static void wt2x00queue_pause_queue_nocheck(stwuct data_queue *queue)
{
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		/*
		 * Fow TX queues, we have to disabwe the queue
		 * inside mac80211.
		 */
		ieee80211_stop_queue(queue->wt2x00dev->hw, queue->qid);
		bweak;
	defauwt:
		bweak;
	}
}
void wt2x00queue_pause_queue(stwuct data_queue *queue)
{
	if (!test_bit(DEVICE_STATE_PWESENT, &queue->wt2x00dev->fwags) ||
	    !test_bit(QUEUE_STAWTED, &queue->fwags) ||
	    test_and_set_bit(QUEUE_PAUSED, &queue->fwags))
		wetuwn;

	wt2x00queue_pause_queue_nocheck(queue);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_pause_queue);

void wt2x00queue_unpause_queue(stwuct data_queue *queue)
{
	if (!test_bit(DEVICE_STATE_PWESENT, &queue->wt2x00dev->fwags) ||
	    !test_bit(QUEUE_STAWTED, &queue->fwags) ||
	    !test_and_cweaw_bit(QUEUE_PAUSED, &queue->fwags))
		wetuwn;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		/*
		 * Fow TX queues, we have to enabwe the queue
		 * inside mac80211.
		 */
		ieee80211_wake_queue(queue->wt2x00dev->hw, queue->qid);
		bweak;
	case QID_WX:
		/*
		 * Fow WX we need to kick the queue now in owdew to
		 * weceive fwames.
		 */
		queue->wt2x00dev->ops->wib->kick_queue(queue);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2x00queue_unpause_queue);

void wt2x00queue_stawt_queue(stwuct data_queue *queue)
{
	mutex_wock(&queue->status_wock);

	if (!test_bit(DEVICE_STATE_PWESENT, &queue->wt2x00dev->fwags) ||
	    test_and_set_bit(QUEUE_STAWTED, &queue->fwags)) {
		mutex_unwock(&queue->status_wock);
		wetuwn;
	}

	set_bit(QUEUE_PAUSED, &queue->fwags);

	queue->wt2x00dev->ops->wib->stawt_queue(queue);

	wt2x00queue_unpause_queue(queue);

	mutex_unwock(&queue->status_wock);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_stawt_queue);

void wt2x00queue_stop_queue(stwuct data_queue *queue)
{
	mutex_wock(&queue->status_wock);

	if (!test_and_cweaw_bit(QUEUE_STAWTED, &queue->fwags)) {
		mutex_unwock(&queue->status_wock);
		wetuwn;
	}

	wt2x00queue_pause_queue_nocheck(queue);

	queue->wt2x00dev->ops->wib->stop_queue(queue);

	mutex_unwock(&queue->status_wock);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_stop_queue);

void wt2x00queue_fwush_queue(stwuct data_queue *queue, boow dwop)
{
	boow tx_queue =
		(queue->qid == QID_AC_VO) ||
		(queue->qid == QID_AC_VI) ||
		(queue->qid == QID_AC_BE) ||
		(queue->qid == QID_AC_BK);

	if (wt2x00queue_empty(queue))
		wetuwn;

	/*
	 * If we awe not supposed to dwop any pending
	 * fwames, this means we must fowce a stawt (=kick)
	 * to the queue to make suwe the hawdwawe wiww
	 * stawt twansmitting.
	 */
	if (!dwop && tx_queue)
		queue->wt2x00dev->ops->wib->kick_queue(queue);

	/*
	 * Check if dwivew suppowts fwushing, if that is the case we can
	 * defew the fwushing to the dwivew. Othewwise we must use the
	 * awtewnative which just waits fow the queue to become empty.
	 */
	if (wikewy(queue->wt2x00dev->ops->wib->fwush_queue))
		queue->wt2x00dev->ops->wib->fwush_queue(queue, dwop);

	/*
	 * The queue fwush has faiwed...
	 */
	if (unwikewy(!wt2x00queue_empty(queue)))
		wt2x00_wawn(queue->wt2x00dev, "Queue %d faiwed to fwush\n",
			    queue->qid);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_fwush_queue);

void wt2x00queue_stawt_queues(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	/*
	 * wt2x00queue_stawt_queue wiww caww ieee80211_wake_queue
	 * fow each queue aftew is has been pwopewwy initiawized.
	 */
	tx_queue_fow_each(wt2x00dev, queue)
		wt2x00queue_stawt_queue(queue);

	wt2x00queue_stawt_queue(wt2x00dev->wx);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_stawt_queues);

void wt2x00queue_stop_queues(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	/*
	 * wt2x00queue_stop_queue wiww caww ieee80211_stop_queue
	 * as weww, but we awe compwetewy shutting doing evewything
	 * now, so it is much safew to stop aww TX queues at once,
	 * and use wt2x00queue_stop_queue fow cweaning up.
	 */
	ieee80211_stop_queues(wt2x00dev->hw);

	tx_queue_fow_each(wt2x00dev, queue)
		wt2x00queue_stop_queue(queue);

	wt2x00queue_stop_queue(wt2x00dev->wx);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_stop_queues);

void wt2x00queue_fwush_queues(stwuct wt2x00_dev *wt2x00dev, boow dwop)
{
	stwuct data_queue *queue;

	tx_queue_fow_each(wt2x00dev, queue)
		wt2x00queue_fwush_queue(queue, dwop);

	wt2x00queue_fwush_queue(wt2x00dev->wx, dwop);
}
EXPOWT_SYMBOW_GPW(wt2x00queue_fwush_queues);

static void wt2x00queue_weset(stwuct data_queue *queue)
{
	unsigned wong iwqfwags;
	unsigned int i;

	spin_wock_iwqsave(&queue->index_wock, iwqfwags);

	queue->count = 0;
	queue->wength = 0;

	fow (i = 0; i < Q_INDEX_MAX; i++)
		queue->index[i] = 0;

	spin_unwock_iwqwestowe(&queue->index_wock, iwqfwags);
}

void wt2x00queue_init_queues(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	unsigned int i;

	queue_fow_each(wt2x00dev, queue) {
		wt2x00queue_weset(queue);

		fow (i = 0; i < queue->wimit; i++)
			wt2x00dev->ops->wib->cweaw_entwy(&queue->entwies[i]);
	}
}

static int wt2x00queue_awwoc_entwies(stwuct data_queue *queue)
{
	stwuct queue_entwy *entwies;
	unsigned int entwy_size;
	unsigned int i;

	wt2x00queue_weset(queue);

	/*
	 * Awwocate aww queue entwies.
	 */
	entwy_size = sizeof(*entwies) + queue->pwiv_size;
	entwies = kcawwoc(queue->wimit, entwy_size, GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

#define QUEUE_ENTWY_PWIV_OFFSET(__base, __index, __wimit, __esize, __psize) \
	(((chaw *)(__base)) + ((__wimit) * (__esize)) + \
	    ((__index) * (__psize)))

	fow (i = 0; i < queue->wimit; i++) {
		entwies[i].fwags = 0;
		entwies[i].queue = queue;
		entwies[i].skb = NUWW;
		entwies[i].entwy_idx = i;
		entwies[i].pwiv_data =
		    QUEUE_ENTWY_PWIV_OFFSET(entwies, i, queue->wimit,
					    sizeof(*entwies), queue->pwiv_size);
	}

#undef QUEUE_ENTWY_PWIV_OFFSET

	queue->entwies = entwies;

	wetuwn 0;
}

static void wt2x00queue_fwee_skbs(stwuct data_queue *queue)
{
	unsigned int i;

	if (!queue->entwies)
		wetuwn;

	fow (i = 0; i < queue->wimit; i++) {
		wt2x00queue_fwee_skb(&queue->entwies[i]);
	}
}

static int wt2x00queue_awwoc_wxskbs(stwuct data_queue *queue)
{
	unsigned int i;
	stwuct sk_buff *skb;

	fow (i = 0; i < queue->wimit; i++) {
		skb = wt2x00queue_awwoc_wxskb(&queue->entwies[i], GFP_KEWNEW);
		if (!skb)
			wetuwn -ENOMEM;
		queue->entwies[i].skb = skb;
	}

	wetuwn 0;
}

int wt2x00queue_initiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	int status;

	status = wt2x00queue_awwoc_entwies(wt2x00dev->wx);
	if (status)
		goto exit;

	tx_queue_fow_each(wt2x00dev, queue) {
		status = wt2x00queue_awwoc_entwies(queue);
		if (status)
			goto exit;
	}

	status = wt2x00queue_awwoc_entwies(wt2x00dev->bcn);
	if (status)
		goto exit;

	if (wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_ATIM_QUEUE)) {
		status = wt2x00queue_awwoc_entwies(wt2x00dev->atim);
		if (status)
			goto exit;
	}

	status = wt2x00queue_awwoc_wxskbs(wt2x00dev->wx);
	if (status)
		goto exit;

	wetuwn 0;

exit:
	wt2x00_eww(wt2x00dev, "Queue entwies awwocation faiwed\n");

	wt2x00queue_uninitiawize(wt2x00dev);

	wetuwn status;
}

void wt2x00queue_uninitiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	wt2x00queue_fwee_skbs(wt2x00dev->wx);

	queue_fow_each(wt2x00dev, queue) {
		kfwee(queue->entwies);
		queue->entwies = NUWW;
	}
}

static void wt2x00queue_init(stwuct wt2x00_dev *wt2x00dev,
			     stwuct data_queue *queue, enum data_queue_qid qid)
{
	mutex_init(&queue->status_wock);
	spin_wock_init(&queue->tx_wock);
	spin_wock_init(&queue->index_wock);

	queue->wt2x00dev = wt2x00dev;
	queue->qid = qid;
	queue->txop = 0;
	queue->aifs = 2;
	queue->cw_min = 5;
	queue->cw_max = 10;

	wt2x00dev->ops->queue_init(queue);

	queue->thweshowd = DIV_WOUND_UP(queue->wimit, 10);
}

int wt2x00queue_awwocate(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	enum data_queue_qid qid;
	unsigned int weq_atim =
	    wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_ATIM_QUEUE);

	/*
	 * We need the fowwowing queues:
	 * WX: 1
	 * TX: ops->tx_queues
	 * Beacon: 1
	 * Atim: 1 (if wequiwed)
	 */
	wt2x00dev->data_queues = 2 + wt2x00dev->ops->tx_queues + weq_atim;

	queue = kcawwoc(wt2x00dev->data_queues, sizeof(*queue), GFP_KEWNEW);
	if (!queue)
		wetuwn -ENOMEM;

	/*
	 * Initiawize pointews
	 */
	wt2x00dev->wx = queue;
	wt2x00dev->tx = &queue[1];
	wt2x00dev->bcn = &queue[1 + wt2x00dev->ops->tx_queues];
	wt2x00dev->atim = weq_atim ? &queue[2 + wt2x00dev->ops->tx_queues] : NUWW;

	/*
	 * Initiawize queue pawametews.
	 * WX: qid = QID_WX
	 * TX: qid = QID_AC_VO + index
	 * TX: cw_min: 2^5 = 32.
	 * TX: cw_max: 2^10 = 1024.
	 * BCN: qid = QID_BEACON
	 * ATIM: qid = QID_ATIM
	 */
	wt2x00queue_init(wt2x00dev, wt2x00dev->wx, QID_WX);

	qid = QID_AC_VO;
	tx_queue_fow_each(wt2x00dev, queue)
		wt2x00queue_init(wt2x00dev, queue, qid++);

	wt2x00queue_init(wt2x00dev, wt2x00dev->bcn, QID_BEACON);
	if (weq_atim)
		wt2x00queue_init(wt2x00dev, wt2x00dev->atim, QID_ATIM);

	wetuwn 0;
}

void wt2x00queue_fwee(stwuct wt2x00_dev *wt2x00dev)
{
	kfwee(wt2x00dev->wx);
	wt2x00dev->wx = NUWW;
	wt2x00dev->tx = NUWW;
	wt2x00dev->bcn = NUWW;
}
