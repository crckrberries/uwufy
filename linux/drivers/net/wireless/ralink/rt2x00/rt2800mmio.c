// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*	Copywight (C) 2009 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
 *	Copywight (C) 2009 Awban Bwowaeys <pwahaw@yahoo.com>
 *	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
 *	Copywight (C) 2009 Wuis Cowweia <wuis.f.cowweia@gmaiw.com>
 *	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
 *	Copywight (C) 2009 Mawk Assewstine <assewsm@gmaiw.com>
 *	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
 *	Copywight (C) 2009 Bawt Zowniewkiewicz <bzowniew@gmaiw.com>
 *	<http://wt2x00.sewiawmonkey.com>
 */

/*	Moduwe: wt2800mmio
 *	Abstwact: wt2800 MMIO device woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>

#incwude "wt2x00.h"
#incwude "wt2x00mmio.h"
#incwude "wt2800.h"
#incwude "wt2800wib.h"
#incwude "wt2800mmio.h"

unsigned int wt2800mmio_get_dma_done(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	stwuct queue_entwy *entwy;
	int idx, qid;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		qid = queue->qid;
		idx = wt2x00mmio_wegistew_wead(wt2x00dev, TX_DTX_IDX(qid));
		bweak;
	case QID_MGMT:
		idx = wt2x00mmio_wegistew_wead(wt2x00dev, TX_DTX_IDX(5));
		bweak;
	case QID_WX:
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DMA_DONE);
		idx = entwy->entwy_idx;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		idx = 0;
		bweak;
	}

	wetuwn idx;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_get_dma_done);

/*
 * TX descwiptow initiawization
 */
__we32 *wt2800mmio_get_txwi(stwuct queue_entwy *entwy)
{
	wetuwn (__we32 *) entwy->skb->data;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_get_txwi);

void wt2800mmio_wwite_tx_desc(stwuct queue_entwy *entwy,
			      stwuct txentwy_desc *txdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	__we32 *txd = entwy_pwiv->desc;
	u32 wowd;
	const unsigned int txwi_size = entwy->queue->winfo_size;

	/*
	 * The buffews pointed by SD_PTW0/SD_WEN0 and SD_PTW1/SD_WEN1
	 * must contains a TXWI stwuctuwe + 802.11 headew + padding + 802.11
	 * data. We choose to have SD_PTW0/SD_WEN0 onwy contains TXWI and
	 * SD_PTW1/SD_WEN1 contains 802.11 headew + padding + 802.11
	 * data. It means that WAST_SEC0 is awways 0.
	 */

	/*
	 * Initiawize TX descwiptow
	 */
	wowd = 0;
	wt2x00_set_fiewd32(&wowd, TXD_W0_SD_PTW0, skbdesc->skb_dma);
	wt2x00_desc_wwite(txd, 0, wowd);

	wowd = 0;
	wt2x00_set_fiewd32(&wowd, TXD_W1_SD_WEN1, entwy->skb->wen);
	wt2x00_set_fiewd32(&wowd, TXD_W1_WAST_SEC1,
			   !test_bit(ENTWY_TXD_MOWE_FWAG, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W1_BUWST,
			   test_bit(ENTWY_TXD_BUWST, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W1_SD_WEN0, txwi_size);
	wt2x00_set_fiewd32(&wowd, TXD_W1_WAST_SEC0, 0);
	wt2x00_set_fiewd32(&wowd, TXD_W1_DMA_DONE, 0);
	wt2x00_desc_wwite(txd, 1, wowd);

	wowd = 0;
	wt2x00_set_fiewd32(&wowd, TXD_W2_SD_PTW1,
			   skbdesc->skb_dma + txwi_size);
	wt2x00_desc_wwite(txd, 2, wowd);

	wowd = 0;
	wt2x00_set_fiewd32(&wowd, TXD_W3_WIV,
			   !test_bit(ENTWY_TXD_ENCWYPT_IV, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXD_W3_QSEW, 2);
	wt2x00_desc_wwite(txd, 3, wowd);

	/*
	 * Wegistew descwiptow detaiws in skb fwame descwiptow.
	 */
	skbdesc->desc = txd;
	skbdesc->desc_wen = TXD_DESC_SIZE;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_wwite_tx_desc);

/*
 * WX contwow handwews
 */
void wt2800mmio_fiww_wxdone(stwuct queue_entwy *entwy,
			    stwuct wxdone_entwy_desc *wxdesc)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	__we32 *wxd = entwy_pwiv->desc;
	u32 wowd;

	wowd = wt2x00_desc_wead(wxd, 3);

	if (wt2x00_get_fiewd32(wowd, WXD_W3_CWC_EWWOW))
		wxdesc->fwags |= WX_FWAG_FAIWED_FCS_CWC;

	/*
	 * Unfowtunatewy we don't know the ciphew type used duwing
	 * decwyption. This pwevents us fwom cowwect pwoviding
	 * cowwect statistics thwough debugfs.
	 */
	wxdesc->ciphew_status = wt2x00_get_fiewd32(wowd, WXD_W3_CIPHEW_EWWOW);

	if (wt2x00_get_fiewd32(wowd, WXD_W3_DECWYPTED)) {
		/*
		 * Hawdwawe has stwipped IV/EIV data fwom 802.11 fwame duwing
		 * decwyption. Unfowtunatewy the descwiptow doesn't contain
		 * any fiewds with the EIV/IV data eithew, so they can't
		 * be westowed by wt2x00wib.
		 */
		wxdesc->fwags |= WX_FWAG_IV_STWIPPED;

		/*
		 * The hawdwawe has awweady checked the Michaew Mic and has
		 * stwipped it fwom the fwame. Signaw this to mac80211.
		 */
		wxdesc->fwags |= WX_FWAG_MMIC_STWIPPED;

		if (wxdesc->ciphew_status == WX_CWYPTO_SUCCESS) {
			wxdesc->fwags |= WX_FWAG_DECWYPTED;
		} ewse if (wxdesc->ciphew_status == WX_CWYPTO_FAIW_MIC) {
			/*
			 * In owdew to check the Michaew Mic, the packet must have
			 * been decwypted.  Mac80211 doesnt check the MMIC faiwuwe 
			 * fwag to initiate MMIC countewmeasuwes if the decoded fwag
			 * has not been set.
			 */
			wxdesc->fwags |= WX_FWAG_DECWYPTED;

			wxdesc->fwags |= WX_FWAG_MMIC_EWWOW;
		}
	}

	if (wt2x00_get_fiewd32(wowd, WXD_W3_MY_BSS))
		wxdesc->dev_fwags |= WXDONE_MY_BSS;

	if (wt2x00_get_fiewd32(wowd, WXD_W3_W2PAD))
		wxdesc->dev_fwags |= WXDONE_W2PAD;

	/*
	 * Pwocess the WXWI stwuctuwe that is at the stawt of the buffew.
	 */
	wt2800_pwocess_wxwi(entwy, wxdesc);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_fiww_wxdone);

/*
 * Intewwupt functions.
 */
static void wt2800mmio_wakeup(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct ieee80211_conf conf = { .fwags = 0 };
	stwuct wt2x00wib_conf wibconf = { .conf = &conf };

	wt2800_config(wt2x00dev, &wibconf, IEEE80211_CONF_CHANGE_PS);
}

static inwine void wt2800mmio_enabwe_intewwupt(stwuct wt2x00_dev *wt2x00dev,
					       stwuct wt2x00_fiewd32 iwq_fiewd)
{
	u32 weg;

	/*
	 * Enabwe a singwe intewwupt. The intewwupt mask wegistew
	 * access needs wocking.
	 */
	spin_wock_iwq(&wt2x00dev->iwqmask_wock);
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_MASK_CSW);
	wt2x00_set_fiewd32(&weg, iwq_fiewd, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, INT_MASK_CSW, weg);
	spin_unwock_iwq(&wt2x00dev->iwqmask_wock);
}

void wt2800mmio_pwetbtt_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    pwetbtt_taskwet);
	wt2x00wib_pwetbtt(wt2x00dev);
	if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2800mmio_enabwe_intewwupt(wt2x00dev, INT_MASK_CSW_PWE_TBTT);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_pwetbtt_taskwet);

void wt2800mmio_tbtt_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t, tbtt_taskwet);
	stwuct wt2800_dwv_data *dwv_data = wt2x00dev->dwv_data;
	u32 weg;

	wt2x00wib_beacondone(wt2x00dev);

	if (wt2x00dev->intf_ap_count) {
		/*
		 * The wt2800pci hawdwawe tbtt timew is off by 1us pew tbtt
		 * causing beacon skew and as a wesuwt causing pwobwems with
		 * some powewsaving cwients ovew time. Showten the beacon
		 * intewvaw evewy 64 beacons by 64us to mitigate this effect.
		 */
		if (dwv_data->tbtt_tick == (BCN_TBTT_OFFSET - 2)) {
			weg = wt2x00mmio_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
			wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_INTEWVAW,
					   (wt2x00dev->beacon_int * 16) - 1);
			wt2x00mmio_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);
		} ewse if (dwv_data->tbtt_tick == (BCN_TBTT_OFFSET - 1)) {
			weg = wt2x00mmio_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
			wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_INTEWVAW,
					   (wt2x00dev->beacon_int * 16));
			wt2x00mmio_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);
		}
		dwv_data->tbtt_tick++;
		dwv_data->tbtt_tick %= BCN_TBTT_OFFSET;
	}

	if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2800mmio_enabwe_intewwupt(wt2x00dev, INT_MASK_CSW_TBTT);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_tbtt_taskwet);

void wt2800mmio_wxdone_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    wxdone_taskwet);
	if (wt2x00mmio_wxdone(wt2x00dev))
		taskwet_scheduwe(&wt2x00dev->wxdone_taskwet);
	ewse if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2800mmio_enabwe_intewwupt(wt2x00dev, INT_MASK_CSW_WX_DONE);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_wxdone_taskwet);

void wt2800mmio_autowake_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    autowake_taskwet);
	wt2800mmio_wakeup(wt2x00dev);
	if (test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wt2800mmio_enabwe_intewwupt(wt2x00dev,
					    INT_MASK_CSW_AUTO_WAKEUP);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_autowake_taskwet);

static void wt2800mmio_fetch_txstatus(stwuct wt2x00_dev *wt2x00dev)
{
	u32 status;
	unsigned wong fwags;

	/*
	 * The TX_FIFO_STATUS intewwupt needs speciaw cawe. We shouwd
	 * wead TX_STA_FIFO but we shouwd do it immediatewy as othewwise
	 * the wegistew can ovewfwow and we wouwd wose status wepowts.
	 *
	 * Hence, wead the TX_STA_FIFO wegistew and copy aww tx status
	 * wepowts into a kewnew FIFO which is handwed in the txstatus
	 * taskwet. We use a taskwet to pwocess the tx status wepowts
	 * because we can scheduwe the taskwet muwtipwe times (when the
	 * intewwupt fiwes again duwing tx status pwocessing).
	 *
	 * We awso wead statuses fwom tx status timeout timew, use
	 * wock to pwevent concuwent wwites to fifo.
	 */

	spin_wock_iwqsave(&wt2x00dev->iwqmask_wock, fwags);

	whiwe (!kfifo_is_fuww(&wt2x00dev->txstatus_fifo)) {
		status = wt2x00mmio_wegistew_wead(wt2x00dev, TX_STA_FIFO);
		if (!wt2x00_get_fiewd32(status, TX_STA_FIFO_VAWID))
			bweak;

		kfifo_put(&wt2x00dev->txstatus_fifo, status);
	}

	spin_unwock_iwqwestowe(&wt2x00dev->iwqmask_wock, fwags);
}

void wt2800mmio_txstatus_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct wt2x00_dev *wt2x00dev = fwom_taskwet(wt2x00dev, t,
						    txstatus_taskwet);

	wt2800_txdone(wt2x00dev, 16);

	if (!kfifo_is_empty(&wt2x00dev->txstatus_fifo))
		taskwet_scheduwe(&wt2x00dev->txstatus_taskwet);

}
EXPOWT_SYMBOW_GPW(wt2800mmio_txstatus_taskwet);

iwqwetuwn_t wt2800mmio_intewwupt(int iwq, void *dev_instance)
{
	stwuct wt2x00_dev *wt2x00dev = dev_instance;
	u32 weg, mask;

	/* Wead status and ACK aww intewwupts */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_SOUWCE_CSW);
	wt2x00mmio_wegistew_wwite(wt2x00dev, INT_SOUWCE_CSW, weg);

	if (!weg)
		wetuwn IWQ_NONE;

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn IWQ_HANDWED;

	/*
	 * Since INT_MASK_CSW and INT_SOUWCE_CSW use the same bits
	 * fow intewwupts and intewwupt masks we can just use the vawue of
	 * INT_SOUWCE_CSW to cweate the intewwupt mask.
	 */
	mask = ~weg;

	if (wt2x00_get_fiewd32(weg, INT_SOUWCE_CSW_TX_FIFO_STATUS)) {
		wt2x00_set_fiewd32(&mask, INT_MASK_CSW_TX_FIFO_STATUS, 1);
		wt2800mmio_fetch_txstatus(wt2x00dev);
		if (!kfifo_is_empty(&wt2x00dev->txstatus_fifo))
			taskwet_scheduwe(&wt2x00dev->txstatus_taskwet);
	}

	if (wt2x00_get_fiewd32(weg, INT_SOUWCE_CSW_PWE_TBTT))
		taskwet_hi_scheduwe(&wt2x00dev->pwetbtt_taskwet);

	if (wt2x00_get_fiewd32(weg, INT_SOUWCE_CSW_TBTT))
		taskwet_hi_scheduwe(&wt2x00dev->tbtt_taskwet);

	if (wt2x00_get_fiewd32(weg, INT_SOUWCE_CSW_WX_DONE))
		taskwet_scheduwe(&wt2x00dev->wxdone_taskwet);

	if (wt2x00_get_fiewd32(weg, INT_SOUWCE_CSW_AUTO_WAKEUP))
		taskwet_scheduwe(&wt2x00dev->autowake_taskwet);

	/*
	 * Disabwe aww intewwupts fow which a taskwet was scheduwed wight now,
	 * the taskwet wiww weenabwe the appwopwiate intewwupts.
	 */
	spin_wock(&wt2x00dev->iwqmask_wock);
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_MASK_CSW);
	weg &= mask;
	wt2x00mmio_wegistew_wwite(wt2x00dev, INT_MASK_CSW, weg);
	spin_unwock(&wt2x00dev->iwqmask_wock);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_intewwupt);

void wt2800mmio_toggwe_iwq(stwuct wt2x00_dev *wt2x00dev,
			   enum dev_state state)
{
	u32 weg;
	unsigned wong fwags;

	/*
	 * When intewwupts awe being enabwed, the intewwupt wegistews
	 * shouwd cweaw the wegistew to assuwe a cwean state.
	 */
	if (state == STATE_WADIO_IWQ_ON) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_SOUWCE_CSW);
		wt2x00mmio_wegistew_wwite(wt2x00dev, INT_SOUWCE_CSW, weg);
	}

	spin_wock_iwqsave(&wt2x00dev->iwqmask_wock, fwags);
	weg = 0;
	if (state == STATE_WADIO_IWQ_ON) {
		wt2x00_set_fiewd32(&weg, INT_MASK_CSW_WX_DONE, 1);
		wt2x00_set_fiewd32(&weg, INT_MASK_CSW_TBTT, 1);
		wt2x00_set_fiewd32(&weg, INT_MASK_CSW_PWE_TBTT, 1);
		wt2x00_set_fiewd32(&weg, INT_MASK_CSW_TX_FIFO_STATUS, 1);
		wt2x00_set_fiewd32(&weg, INT_MASK_CSW_AUTO_WAKEUP, 1);
	}
	wt2x00mmio_wegistew_wwite(wt2x00dev, INT_MASK_CSW, weg);
	spin_unwock_iwqwestowe(&wt2x00dev->iwqmask_wock, fwags);

	if (state == STATE_WADIO_IWQ_OFF) {
		/*
		 * Wait fow possibwy wunning taskwets to finish.
		 */
		taskwet_kiww(&wt2x00dev->txstatus_taskwet);
		taskwet_kiww(&wt2x00dev->wxdone_taskwet);
		taskwet_kiww(&wt2x00dev->autowake_taskwet);
		taskwet_kiww(&wt2x00dev->tbtt_taskwet);
		taskwet_kiww(&wt2x00dev->pwetbtt_taskwet);
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_toggwe_iwq);

/*
 * Queue handwews.
 */
void wt2800mmio_stawt_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_WX:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
		wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_TICKING, 1);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TBTT_ENABWE, 1);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_TIMEW_EN);
		wt2x00_set_fiewd32(&weg, INT_TIMEW_EN_PWE_TBTT_TIMEW, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, INT_TIMEW_EN, weg);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_stawt_queue);

/* 200 ms */
#define TXSTATUS_TIMEOUT 200000000

void wt2800mmio_kick_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	stwuct queue_entwy *entwy;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		WAWN_ON_ONCE(wt2x00queue_empty(queue));
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX(queue->qid),
					  entwy->entwy_idx);
		hwtimew_stawt(&wt2x00dev->txstatus_timew,
			      TXSTATUS_TIMEOUT, HWTIMEW_MODE_WEW);
		bweak;
	case QID_MGMT:
		entwy = wt2x00queue_get_entwy(queue, Q_INDEX);
		wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX(5),
					  entwy->entwy_idx);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_kick_queue);

void wt2800mmio_fwush_queue(stwuct data_queue *queue, boow dwop)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	boow tx_queue = fawse;
	unsigned int i;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		tx_queue = twue;
		bweak;
	case QID_WX:
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = 0; i < 5; i++) {
		/*
		 * Check if the dwivew is awweady done, othewwise we
		 * have to sweep a wittwe whiwe to give the dwivew/hw
		 * the oppuwtunity to compwete intewwupt pwocess itsewf.
		 */
		if (wt2x00queue_empty(queue))
			bweak;

		/*
		 * Fow TX queues scheduwe compwetion taskwet to catch
		 * tx status timeouts, othewise just wait.
		 */
		if (tx_queue)
			queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->txdone_wowk);

		/*
		 * Wait fow a wittwe whiwe to give the dwivew
		 * the oppuwtunity to wecovew itsewf.
		 */
		msweep(50);
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_fwush_queue);

void wt2800mmio_stop_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_WX:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
		wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_TICKING, 0);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TBTT_ENABWE, 0);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);

		weg = wt2x00mmio_wegistew_wead(wt2x00dev, INT_TIMEW_EN);
		wt2x00_set_fiewd32(&weg, INT_TIMEW_EN_PWE_TBTT_TIMEW, 0);
		wt2x00mmio_wegistew_wwite(wt2x00dev, INT_TIMEW_EN, weg);

		/*
		 * Wait fow cuwwent invocation to finish. The taskwet
		 * won't be scheduwed anymowe aftewwawds since we disabwed
		 * the TBTT and PWE TBTT timew.
		 */
		taskwet_kiww(&wt2x00dev->tbtt_taskwet);
		taskwet_kiww(&wt2x00dev->pwetbtt_taskwet);

		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_stop_queue);

void wt2800mmio_queue_init(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	unsigned showt txwi_size, wxwi_size;

	wt2800_get_txwi_wxwi_size(wt2x00dev, &txwi_size, &wxwi_size);

	switch (queue->qid) {
	case QID_WX:
		queue->wimit = 128;
		queue->data_size = AGGWEGATION_SIZE;
		queue->desc_size = WXD_DESC_SIZE;
		queue->winfo_size = wxwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->wimit = 64;
		queue->data_size = AGGWEGATION_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_BEACON:
		queue->wimit = 8;
		queue->data_size = 0; /* No DMA wequiwed fow beacons */
		queue->desc_size = TXD_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_mmio);
		bweak;

	case QID_ATIM:
	defauwt:
		BUG();
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_queue_init);

/*
 * Initiawization functions.
 */
boow wt2800mmio_get_entwy_state(stwuct queue_entwy *entwy)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	u32 wowd;

	if (entwy->queue->qid == QID_WX) {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 1);

		wetuwn (!wt2x00_get_fiewd32(wowd, WXD_W1_DMA_DONE));
	} ewse {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 1);

		wetuwn (!wt2x00_get_fiewd32(wowd, TXD_W1_DMA_DONE));
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_get_entwy_state);

void wt2800mmio_cweaw_entwy(stwuct queue_entwy *entwy)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv = entwy->pwiv_data;
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	u32 wowd;

	if (entwy->queue->qid == QID_WX) {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 0);
		wt2x00_set_fiewd32(&wowd, WXD_W0_SDP0, skbdesc->skb_dma);
		wt2x00_desc_wwite(entwy_pwiv->desc, 0, wowd);

		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 1);
		wt2x00_set_fiewd32(&wowd, WXD_W1_DMA_DONE, 0);
		wt2x00_desc_wwite(entwy_pwiv->desc, 1, wowd);

		/*
		 * Set WX IDX in wegistew to infowm hawdwawe that we have
		 * handwed this entwy and it is avaiwabwe fow weuse again.
		 */
		wt2x00mmio_wegistew_wwite(wt2x00dev, WX_CWX_IDX,
					  entwy->entwy_idx);
	} ewse {
		wowd = wt2x00_desc_wead(entwy_pwiv->desc, 1);
		wt2x00_set_fiewd32(&wowd, TXD_W1_DMA_DONE, 1);
		wt2x00_desc_wwite(entwy_pwiv->desc, 1, wowd);

		/* If wast entwy stop txstatus timew */
		if (entwy->queue->wength == 1)
			hwtimew_cancew(&wt2x00dev->txstatus_timew);
	}
}
EXPOWT_SYMBOW_GPW(wt2800mmio_cweaw_entwy);

int wt2800mmio_init_queues(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct queue_entwy_pwiv_mmio *entwy_pwiv;

	/*
	 * Initiawize wegistews.
	 */
	entwy_pwiv = wt2x00dev->tx[0].entwies[0].pwiv_data;
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW0,
				  entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT0,
				  wt2x00dev->tx[0].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX0, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX0, 0);

	entwy_pwiv = wt2x00dev->tx[1].entwies[0].pwiv_data;
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW1,
				  entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT1,
				  wt2x00dev->tx[1].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX1, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX1, 0);

	entwy_pwiv = wt2x00dev->tx[2].entwies[0].pwiv_data;
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW2,
				  entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT2,
				  wt2x00dev->tx[2].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX2, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX2, 0);

	entwy_pwiv = wt2x00dev->tx[3].entwies[0].pwiv_data;
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW3,
				  entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT3,
				  wt2x00dev->tx[3].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX3, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX3, 0);

	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW4, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT4, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX4, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX4, 0);

	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_BASE_PTW5, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_MAX_CNT5, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_CTX_IDX5, 0);
	wt2x00mmio_wegistew_wwite(wt2x00dev, TX_DTX_IDX5, 0);

	entwy_pwiv = wt2x00dev->wx->entwies[0].pwiv_data;
	wt2x00mmio_wegistew_wwite(wt2x00dev, WX_BASE_PTW,
				  entwy_pwiv->desc_dma);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WX_MAX_CNT,
				  wt2x00dev->wx[0].wimit);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WX_CWX_IDX,
				  wt2x00dev->wx[0].wimit - 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WX_DWX_IDX, 0);

	wt2800_disabwe_wpdma(wt2x00dev);

	wt2x00mmio_wegistew_wwite(wt2x00dev, DEWAY_INT_CFG, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_init_queues);

int wt2800mmio_init_wegistews(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	/*
	 * Weset DMA indexes
	 */
	weg = wt2x00mmio_wegistew_wead(wt2x00dev, WPDMA_WST_IDX);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX0, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX1, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX2, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX3, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX4, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DTX_IDX5, 1);
	wt2x00_set_fiewd32(&weg, WPDMA_WST_IDX_DWX_IDX0, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, WPDMA_WST_IDX, weg);

	wt2x00mmio_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, 0x00000e1f);
	wt2x00mmio_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, 0x00000e00);

	if (wt2x00_is_pcie(wt2x00dev) &&
	    (wt2x00_wt(wt2x00dev, WT3090) ||
	     wt2x00_wt(wt2x00dev, WT3390) ||
	     wt2x00_wt(wt2x00dev, WT3572) ||
	     wt2x00_wt(wt2x00dev, WT3593) ||
	     wt2x00_wt(wt2x00dev, WT5390) ||
	     wt2x00_wt(wt2x00dev, WT5392) ||
	     wt2x00_wt(wt2x00dev, WT5592))) {
		weg = wt2x00mmio_wegistew_wead(wt2x00dev, AUX_CTWW);
		wt2x00_set_fiewd32(&weg, AUX_CTWW_FOWCE_PCIE_CWK, 1);
		wt2x00_set_fiewd32(&weg, AUX_CTWW_WAKE_PCIE_EN, 1);
		wt2x00mmio_wegistew_wwite(wt2x00dev, AUX_CTWW, weg);
	}

	wt2x00mmio_wegistew_wwite(wt2x00dev, PWW_PIN_CFG, 0x00000003);

	if (wt2x00_wt(wt2x00dev, WT6352))
		wetuwn 0;

	weg = 0;
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_WESET_CSW, 1);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_WESET_BBP, 1);
	wt2x00mmio_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);

	wt2x00mmio_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x00000000);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_init_wegistews);

/*
 * Device state switch handwews.
 */
int wt2800mmio_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	/* Wait fow DMA, ignowe ewwow untiw we initiawize queues. */
	wt2800_wait_wpdma_weady(wt2x00dev);

	if (unwikewy(wt2800mmio_init_queues(wt2x00dev)))
		wetuwn -EIO;

	wetuwn wt2800_enabwe_wadio(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2800mmio_enabwe_wadio);

static void wt2800mmio_wowk_txdone(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, txdone_wowk);

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		wetuwn;

	whiwe (!kfifo_is_empty(&wt2x00dev->txstatus_fifo) ||
	       wt2800_txstatus_timeout(wt2x00dev)) {

		taskwet_disabwe(&wt2x00dev->txstatus_taskwet);
		wt2800_txdone(wt2x00dev, UINT_MAX);
		wt2800_txdone_nostatus(wt2x00dev);
		taskwet_enabwe(&wt2x00dev->txstatus_taskwet);
	}

	if (wt2800_txstatus_pending(wt2x00dev))
		hwtimew_stawt(&wt2x00dev->txstatus_timew,
			      TXSTATUS_TIMEOUT, HWTIMEW_MODE_WEW);
}

static enum hwtimew_westawt wt2800mmio_tx_sta_fifo_timeout(stwuct hwtimew *timew)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(timew, stwuct wt2x00_dev, txstatus_timew);

	if (!test_bit(DEVICE_STATE_ENABWED_WADIO, &wt2x00dev->fwags))
		goto out;

	if (!wt2800_txstatus_pending(wt2x00dev))
		goto out;

	wt2800mmio_fetch_txstatus(wt2x00dev);
	if (!kfifo_is_empty(&wt2x00dev->txstatus_fifo))
		taskwet_scheduwe(&wt2x00dev->txstatus_taskwet);
	ewse
		queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->txdone_wowk);
out:
	wetuwn HWTIMEW_NOWESTAWT;
}

int wt2800mmio_pwobe_hw(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	wetvaw = wt2800_pwobe_hw(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Set txstatus timew function.
	 */
	wt2x00dev->txstatus_timew.function = wt2800mmio_tx_sta_fifo_timeout;

	/*
	 * Ovewwwite TX done handwew
	 */
	INIT_WOWK(&wt2x00dev->txdone_wowk, wt2800mmio_wowk_txdone);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2800mmio_pwobe_hw);

MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("wt2800 MMIO wibwawy");
MODUWE_WICENSE("GPW");
