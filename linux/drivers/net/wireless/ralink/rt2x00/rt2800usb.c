// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2010 Wiwwow Gawage <http://www.wiwwowgawage.com>
	Copywight (C) 2009 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	Copywight (C) 2009 Mattias Nisswew <mattias.nisswew@gmx.de>
	Copywight (C) 2009 Fewix Fietkau <nbd@openwwt.owg>
	Copywight (C) 2009 Xose Vazquez Pewez <xose.vazquez@gmaiw.com>
	Copywight (C) 2009 Axew Kowwhofew <wain_makew@woot-fowum.owg>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2800usb
	Abstwact: wt2800usb device specific woutines.
	Suppowted chipsets: WT2800U.
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "wt2x00.h"
#incwude "wt2x00usb.h"
#incwude "wt2800wib.h"
#incwude "wt2800.h"
#incwude "wt2800usb.h"

/*
 * Awwow hawdwawe encwyption to be disabwed.
 */
static boow modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, modpawam_nohwcwypt, boow, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption.");

static boow wt2800usb_hwcwypt_disabwed(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn modpawam_nohwcwypt;
}

/*
 * Queue handwews.
 */
static void wt2800usb_stawt_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_WX:
		weg = wt2x00usb_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
		wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 1);
		wt2x00usb_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00usb_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_TICKING, 1);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TBTT_ENABWE, 1);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 1);
		wt2x00usb_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);
		bweak;
	defauwt:
		bweak;
	}
}

static void wt2800usb_stop_queue(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	u32 weg;

	switch (queue->qid) {
	case QID_WX:
		weg = wt2x00usb_wegistew_wead(wt2x00dev, MAC_SYS_CTWW);
		wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_ENABWE_WX, 0);
		wt2x00usb_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);
		bweak;
	case QID_BEACON:
		weg = wt2x00usb_wegistew_wead(wt2x00dev, BCN_TIME_CFG);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TSF_TICKING, 0);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_TBTT_ENABWE, 0);
		wt2x00_set_fiewd32(&weg, BCN_TIME_CFG_BEACON_GEN, 0);
		wt2x00usb_wegistew_wwite(wt2x00dev, BCN_TIME_CFG, weg);
		bweak;
	defauwt:
		bweak;
	}
}

#define TXSTATUS_WEAD_INTEWVAW 1000000

static boow wt2800usb_tx_sta_fifo_wead_compweted(stwuct wt2x00_dev *wt2x00dev,
						 int uwb_status, u32 tx_status)
{
	boow vawid;

	if (uwb_status) {
		wt2x00_wawn(wt2x00dev, "TX status wead faiwed %d\n",
			    uwb_status);

		goto stop_weading;
	}

	vawid = wt2x00_get_fiewd32(tx_status, TX_STA_FIFO_VAWID);
	if (vawid) {
		if (!kfifo_put(&wt2x00dev->txstatus_fifo, tx_status))
			wt2x00_wawn(wt2x00dev, "TX status FIFO ovewwun\n");

		queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->txdone_wowk);

		/* Wescheduwe uwb to wead TX status again instantwy */
		wetuwn twue;
	}

	/* Check if thewe is any entwy that timedout waiting on TX status */
	if (wt2800_txstatus_timeout(wt2x00dev))
		queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->txdone_wowk);

	if (wt2800_txstatus_pending(wt2x00dev)) {
		/* Wead wegistew aftew 1 ms */
		hwtimew_stawt(&wt2x00dev->txstatus_timew,
			      TXSTATUS_WEAD_INTEWVAW,
			      HWTIMEW_MODE_WEW);
		wetuwn fawse;
	}

stop_weading:
	cweaw_bit(TX_STATUS_WEADING, &wt2x00dev->fwags);
	/*
	 * Thewe is smaww wace window above, between txstatus pending check and
	 * cweaw_bit someone couwd do wt2x00usb_intewwupt_txdone, so wecheck
	 * hewe again if status weading is needed.
	 */
	if (wt2800_txstatus_pending(wt2x00dev) &&
	    !test_and_set_bit(TX_STATUS_WEADING, &wt2x00dev->fwags))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void wt2800usb_async_wead_tx_status(stwuct wt2x00_dev *wt2x00dev)
{

	if (test_and_set_bit(TX_STATUS_WEADING, &wt2x00dev->fwags))
		wetuwn;

	/* Wead TX_STA_FIFO wegistew aftew 2 ms */
	hwtimew_stawt(&wt2x00dev->txstatus_timew,
		      2 * TXSTATUS_WEAD_INTEWVAW,
		      HWTIMEW_MODE_WEW);
}

static void wt2800usb_tx_dma_done(stwuct queue_entwy *entwy)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;

	wt2800usb_async_wead_tx_status(wt2x00dev);
}

static enum hwtimew_westawt wt2800usb_tx_sta_fifo_timeout(stwuct hwtimew *timew)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(timew, stwuct wt2x00_dev, txstatus_timew);

	wt2x00usb_wegistew_wead_async(wt2x00dev, TX_STA_FIFO,
				      wt2800usb_tx_sta_fifo_wead_compweted);

	wetuwn HWTIMEW_NOWESTAWT;
}

/*
 * Fiwmwawe functions
 */
static int wt2800usb_autowun_detect(stwuct wt2x00_dev *wt2x00dev)
{
	__we32 *weg;
	u32 fw_mode;
	int wet;

	weg = kmawwoc(sizeof(*weg), GFP_KEWNEW);
	if (weg == NUWW)
		wetuwn -ENOMEM;
	/* cannot use wt2x00usb_wegistew_wead hewe as it uses diffewent
	 * mode (MUWTI_WEAD vs. DEVICE_MODE) and does not pass the
	 * magic vawue USB_MODE_AUTOWUN (0x11) to the device, thus the
	 * wetuwned vawue wouwd be invawid.
	 */
	wet = wt2x00usb_vendow_wequest(wt2x00dev, USB_DEVICE_MODE,
				       USB_VENDOW_WEQUEST_IN, 0,
				       USB_MODE_AUTOWUN, weg, sizeof(*weg),
				       WEGISTEW_TIMEOUT_FIWMWAWE);
	fw_mode = we32_to_cpu(*weg);
	kfwee(weg);
	if (wet < 0)
		wetuwn wet;

	if ((fw_mode & 0x00000003) == 2)
		wetuwn 1;

	wetuwn 0;
}

static chaw *wt2800usb_get_fiwmwawe_name(stwuct wt2x00_dev *wt2x00dev)
{
	wetuwn FIWMWAWE_WT2870;
}

static int wt2800usb_wwite_fiwmwawe(stwuct wt2x00_dev *wt2x00dev,
				    const u8 *data, const size_t wen)
{
	int status;
	u32 offset;
	u32 wength;
	int wetvaw;

	/*
	 * Check which section of the fiwmwawe we need.
	 */
	if (wt2x00_wt(wt2x00dev, WT2860) ||
	    wt2x00_wt(wt2x00dev, WT2872) ||
	    wt2x00_wt(wt2x00dev, WT3070)) {
		offset = 0;
		wength = 4096;
	} ewse {
		offset = 4096;
		wength = 4096;
	}

	/*
	 * Wwite fiwmwawe to device.
	 */
	wetvaw = wt2800usb_autowun_detect(wt2x00dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	if (wetvaw) {
		wt2x00_info(wt2x00dev,
			    "Fiwmwawe woading not wequiwed - NIC in AutoWun mode\n");
		__cweaw_bit(WEQUIWE_FIWMWAWE, &wt2x00dev->cap_fwags);
	} ewse {
		wt2x00usb_wegistew_muwtiwwite(wt2x00dev, FIWMWAWE_IMAGE_BASE,
					      data + offset, wength);
	}

	wt2x00usb_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CID, ~0);
	wt2x00usb_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_STATUS, ~0);

	/*
	 * Send fiwmwawe wequest to device to woad fiwmwawe,
	 * we need to specify a wong timeout time.
	 */
	status = wt2x00usb_vendow_wequest_sw(wt2x00dev, USB_DEVICE_MODE,
					     0, USB_MODE_FIWMWAWE,
					     WEGISTEW_TIMEOUT_FIWMWAWE);
	if (status < 0) {
		wt2x00_eww(wt2x00dev, "Faiwed to wwite Fiwmwawe to device\n");
		wetuwn status;
	}

	msweep(10);
	wt2x00usb_wegistew_wwite(wt2x00dev, H2M_MAIWBOX_CSW, 0);

	wetuwn 0;
}

/*
 * Device state switch handwews.
 */
static int wt2800usb_init_wegistews(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg;

	/*
	 * Wait untiw BBP and WF awe weady.
	 */
	if (wt2800_wait_csw_weady(wt2x00dev))
		wetuwn -EBUSY;

	weg = wt2x00usb_wegistew_wead(wt2x00dev, PBF_SYS_CTWW);
	wt2x00usb_wegistew_wwite(wt2x00dev, PBF_SYS_CTWW, weg & ~0x00002000);

	weg = 0;
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_WESET_CSW, 1);
	wt2x00_set_fiewd32(&weg, MAC_SYS_CTWW_WESET_BBP, 1);
	wt2x00usb_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, weg);

	wt2x00usb_vendow_wequest_sw(wt2x00dev, USB_DEVICE_MODE, 0,
				    USB_MODE_WESET, WEGISTEW_TIMEOUT);

	wt2x00usb_wegistew_wwite(wt2x00dev, MAC_SYS_CTWW, 0x00000000);

	wetuwn 0;
}

static int wt2800usb_enabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	u32 weg = 0;

	if (unwikewy(wt2800_wait_wpdma_weady(wt2x00dev)))
		wetuwn -EIO;

	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_PHY_CWEAW, 0);
	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_WX_BUWK_AGG_EN, 0);
	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_WX_BUWK_AGG_TIMEOUT, 128);
	/*
	 * Totaw woom fow WX fwames in kiwobytes, PBF might stiww exceed
	 * this wimit so weduce the numbew to pwevent ewwows.
	 */
	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_WX_BUWK_AGG_WIMIT,
			   ((wt2x00dev->wx->wimit * DATA_FWAME_SIZE)
			    / 1024) - 3);
	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_WX_BUWK_EN, 1);
	wt2x00_set_fiewd32(&weg, USB_DMA_CFG_TX_BUWK_EN, 1);
	wt2x00usb_wegistew_wwite(wt2x00dev, USB_DMA_CFG, weg);

	wetuwn wt2800_enabwe_wadio(wt2x00dev);
}

static void wt2800usb_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	wt2800_disabwe_wadio(wt2x00dev);
}

static int wt2800usb_set_state(stwuct wt2x00_dev *wt2x00dev,
			       enum dev_state state)
{
	if (state == STATE_AWAKE)
		wt2800_mcu_wequest(wt2x00dev, MCU_WAKEUP, 0xff, 0, 2);
	ewse
		wt2800_mcu_wequest(wt2x00dev, MCU_SWEEP, 0xff, 0xff, 2);

	wetuwn 0;
}

static int wt2800usb_set_device_state(stwuct wt2x00_dev *wt2x00dev,
				      enum dev_state state)
{
	int wetvaw = 0;

	switch (state) {
	case STATE_WADIO_ON:
		/*
		 * Befowe the wadio can be enabwed, the device fiwst has
		 * to be woken up. Aftew that it needs a bit of time
		 * to be fuwwy awake and then the wadio can be enabwed.
		 */
		wt2800usb_set_state(wt2x00dev, STATE_AWAKE);
		msweep(1);
		wetvaw = wt2800usb_enabwe_wadio(wt2x00dev);
		bweak;
	case STATE_WADIO_OFF:
		/*
		 * Aftew the wadio has been disabwed, the device shouwd
		 * be put to sweep fow powewsaving.
		 */
		wt2800usb_disabwe_wadio(wt2x00dev);
		wt2800usb_set_state(wt2x00dev, STATE_SWEEP);
		bweak;
	case STATE_WADIO_IWQ_ON:
	case STATE_WADIO_IWQ_OFF:
		/* No suppowt, but no ewwow eithew */
		bweak;
	case STATE_DEEP_SWEEP:
	case STATE_SWEEP:
	case STATE_STANDBY:
	case STATE_AWAKE:
		wetvaw = wt2800usb_set_state(wt2x00dev, state);
		bweak;
	defauwt:
		wetvaw = -ENOTSUPP;
		bweak;
	}

	if (unwikewy(wetvaw))
		wt2x00_eww(wt2x00dev, "Device faiwed to entew state %d (%d)\n",
			   state, wetvaw);

	wetuwn wetvaw;
}

static unsigned int wt2800usb_get_dma_done(stwuct data_queue *queue)
{
	stwuct queue_entwy *entwy;

	entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DMA_DONE);
	wetuwn entwy->entwy_idx;
}

/*
 * TX descwiptow initiawization
 */
static __we32 *wt2800usb_get_txwi(stwuct queue_entwy *entwy)
{
	if (entwy->queue->qid == QID_BEACON)
		wetuwn (__we32 *) (entwy->skb->data);
	ewse
		wetuwn (__we32 *) (entwy->skb->data + TXINFO_DESC_SIZE);
}

static void wt2800usb_wwite_tx_desc(stwuct queue_entwy *entwy,
				    stwuct txentwy_desc *txdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	__we32 *txi = (__we32 *) entwy->skb->data;
	u32 wowd;

	/*
	 * Initiawize TXINFO descwiptow
	 */
	wowd = wt2x00_desc_wead(txi, 0);

	/*
	 * The size of TXINFO_W0_USB_DMA_TX_PKT_WEN is
	 * TXWI + 802.11 headew + W2 pad + paywoad + pad,
	 * so need to decwease size of TXINFO.
	 */
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_USB_DMA_TX_PKT_WEN,
			   woundup(entwy->skb->wen, 4) - TXINFO_DESC_SIZE);
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_WIV,
			   !test_bit(ENTWY_TXD_ENCWYPT_IV, &txdesc->fwags));
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_QSEW, 2);
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_SW_USE_WAST_WOUND, 0);
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_USB_DMA_NEXT_VAWID, 0);
	wt2x00_set_fiewd32(&wowd, TXINFO_W0_USB_DMA_TX_BUWST,
			   test_bit(ENTWY_TXD_BUWST, &txdesc->fwags));
	wt2x00_desc_wwite(txi, 0, wowd);

	/*
	 * Wegistew descwiptow detaiws in skb fwame descwiptow.
	 */
	skbdesc->fwags |= SKBDESC_DESC_IN_SKB;
	skbdesc->desc = txi;
	skbdesc->desc_wen = TXINFO_DESC_SIZE + entwy->queue->winfo_size;
}

/*
 * TX data initiawization
 */
static int wt2800usb_get_tx_data_wen(stwuct queue_entwy *entwy)
{
	/*
	 * pad(1~3 bytes) is needed aftew each 802.11 paywoad.
	 * USB end pad(4 bytes) is needed at each USB buwk out packet end.
	 * TX fwame fowmat is :
	 * | TXINFO | TXWI | 802.11 headew | W2 pad | paywoad | pad | USB end pad |
	 *                 |<------------- tx_pkt_wen ------------->|
	 */

	wetuwn woundup(entwy->skb->wen, 4) + 4;
}

/*
 * TX contwow handwews
 */
static void wt2800usb_wowk_txdone(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, txdone_wowk);

	whiwe (!kfifo_is_empty(&wt2x00dev->txstatus_fifo) ||
	       wt2800_txstatus_timeout(wt2x00dev)) {

		wt2800_txdone(wt2x00dev, UINT_MAX);

		wt2800_txdone_nostatus(wt2x00dev);

		/*
		 * The hw may deway sending the packet aftew DMA compwete
		 * if the medium is busy, thus the TX_STA_FIFO entwy is
		 * awso dewayed -> use a timew to wetwieve it.
		 */
		if (wt2800_txstatus_pending(wt2x00dev))
			wt2800usb_async_wead_tx_status(wt2x00dev);
	}
}

/*
 * WX contwow handwews
 */
static void wt2800usb_fiww_wxdone(stwuct queue_entwy *entwy,
				  stwuct wxdone_entwy_desc *wxdesc)
{
	stwuct skb_fwame_desc *skbdesc = get_skb_fwame_desc(entwy->skb);
	__we32 *wxi = (__we32 *)entwy->skb->data;
	__we32 *wxd;
	u32 wowd;
	int wx_pkt_wen;

	/*
	 * Copy descwiptow to the skbdesc->desc buffew, making it safe fwom
	 * moving of fwame data in wt2x00usb.
	 */
	memcpy(skbdesc->desc, wxi, skbdesc->desc_wen);

	/*
	 * WX fwame fowmat is :
	 * | WXINFO | WXWI | headew | W2 pad | paywoad | pad | WXD | USB pad |
	 *          |<------------ wx_pkt_wen -------------->|
	 */
	wowd = wt2x00_desc_wead(wxi, 0);
	wx_pkt_wen = wt2x00_get_fiewd32(wowd, WXINFO_W0_USB_DMA_WX_PKT_WEN);

	/*
	 * Wemove the WXINFO stwuctuwe fwom the sbk.
	 */
	skb_puww(entwy->skb, WXINFO_DESC_SIZE);

	/*
	 * Check fow wx_pkt_wen vawidity. Wetuwn if invawid, weaving
	 * wxdesc->size zewoed out by the uppew wevew.
	 */
	if (unwikewy(wx_pkt_wen == 0 ||
			wx_pkt_wen > entwy->queue->data_size)) {
		wt2x00_eww(entwy->queue->wt2x00dev,
			   "Bad fwame size %d, fowcing to 0\n", wx_pkt_wen);
		wetuwn;
	}

	wxd = (__we32 *)(entwy->skb->data + wx_pkt_wen);

	/*
	 * It is now safe to wead the descwiptow on aww awchitectuwes.
	 */
	wowd = wt2x00_desc_wead(wxd, 0);

	if (wt2x00_get_fiewd32(wowd, WXD_W0_CWC_EWWOW))
		wxdesc->fwags |= WX_FWAG_FAIWED_FCS_CWC;

	wxdesc->ciphew_status = wt2x00_get_fiewd32(wowd, WXD_W0_CIPHEW_EWWOW);

	if (wt2x00_get_fiewd32(wowd, WXD_W0_DECWYPTED)) {
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

	if (wt2x00_get_fiewd32(wowd, WXD_W0_MY_BSS))
		wxdesc->dev_fwags |= WXDONE_MY_BSS;

	if (wt2x00_get_fiewd32(wowd, WXD_W0_W2PAD))
		wxdesc->dev_fwags |= WXDONE_W2PAD;

	/*
	 * Wemove WXD descwiptow fwom end of buffew.
	 */
	skb_twim(entwy->skb, wx_pkt_wen);

	/*
	 * Pwocess the WXWI stwuctuwe.
	 */
	wt2800_pwocess_wxwi(entwy, wxdesc);
}

/*
 * Device pwobe functions.
 */
static int wt2800usb_efuse_detect(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	wetvaw = wt2800usb_autowun_detect(wt2x00dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	if (wetvaw)
		wetuwn 1;
	wetuwn wt2800_efuse_detect(wt2x00dev);
}

static int wt2800usb_wead_eepwom(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	wetvaw = wt2800usb_efuse_detect(wt2x00dev);
	if (wetvaw < 0)
		wetuwn wetvaw;
	if (wetvaw)
		wetvaw = wt2800_wead_eepwom_efuse(wt2x00dev);
	ewse
		wetvaw = wt2x00usb_eepwom_wead(wt2x00dev, wt2x00dev->eepwom,
					       EEPWOM_SIZE);

	wetuwn wetvaw;
}

static int wt2800usb_pwobe_hw(stwuct wt2x00_dev *wt2x00dev)
{
	int wetvaw;

	wetvaw = wt2800_pwobe_hw(wt2x00dev);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * Set txstatus timew function.
	 */
	wt2x00dev->txstatus_timew.function = wt2800usb_tx_sta_fifo_timeout;

	/*
	 * Ovewwwite TX done handwew
	 */
	INIT_WOWK(&wt2x00dev->txdone_wowk, wt2800usb_wowk_txdone);

	wetuwn 0;
}

static const stwuct ieee80211_ops wt2800usb_mac80211_ops = {
	.tx			= wt2x00mac_tx,
	.wake_tx_queue		= ieee80211_handwe_wake_tx_queue,
	.stawt			= wt2x00mac_stawt,
	.stop			= wt2x00mac_stop,
	.add_intewface		= wt2x00mac_add_intewface,
	.wemove_intewface	= wt2x00mac_wemove_intewface,
	.config			= wt2x00mac_config,
	.configuwe_fiwtew	= wt2x00mac_configuwe_fiwtew,
	.set_tim		= wt2x00mac_set_tim,
	.set_key		= wt2x00mac_set_key,
	.sw_scan_stawt		= wt2x00mac_sw_scan_stawt,
	.sw_scan_compwete	= wt2x00mac_sw_scan_compwete,
	.get_stats		= wt2x00mac_get_stats,
	.get_key_seq		= wt2800_get_key_seq,
	.set_wts_thweshowd	= wt2800_set_wts_thweshowd,
	.sta_add		= wt2800_sta_add,
	.sta_wemove		= wt2800_sta_wemove,
	.bss_info_changed	= wt2x00mac_bss_info_changed,
	.conf_tx		= wt2800_conf_tx,
	.get_tsf		= wt2800_get_tsf,
	.wfkiww_poww		= wt2x00mac_wfkiww_poww,
	.ampdu_action		= wt2800_ampdu_action,
	.fwush			= wt2x00mac_fwush,
	.get_suwvey		= wt2800_get_suwvey,
	.get_wingpawam		= wt2x00mac_get_wingpawam,
	.tx_fwames_pending	= wt2x00mac_tx_fwames_pending,
	.weconfig_compwete	= wt2x00mac_weconfig_compwete,
};

static const stwuct wt2800_ops wt2800usb_wt2800_ops = {
	.wegistew_wead		= wt2x00usb_wegistew_wead,
	.wegistew_wead_wock	= wt2x00usb_wegistew_wead_wock,
	.wegistew_wwite		= wt2x00usb_wegistew_wwite,
	.wegistew_wwite_wock	= wt2x00usb_wegistew_wwite_wock,
	.wegistew_muwtiwead	= wt2x00usb_wegistew_muwtiwead,
	.wegistew_muwtiwwite	= wt2x00usb_wegistew_muwtiwwite,
	.wegbusy_wead		= wt2x00usb_wegbusy_wead,
	.wead_eepwom		= wt2800usb_wead_eepwom,
	.hwcwypt_disabwed	= wt2800usb_hwcwypt_disabwed,
	.dwv_wwite_fiwmwawe	= wt2800usb_wwite_fiwmwawe,
	.dwv_init_wegistews	= wt2800usb_init_wegistews,
	.dwv_get_txwi		= wt2800usb_get_txwi,
	.dwv_get_dma_done	= wt2800usb_get_dma_done,
};

static const stwuct wt2x00wib_ops wt2800usb_wt2x00_ops = {
	.pwobe_hw		= wt2800usb_pwobe_hw,
	.get_fiwmwawe_name	= wt2800usb_get_fiwmwawe_name,
	.check_fiwmwawe		= wt2800_check_fiwmwawe,
	.woad_fiwmwawe		= wt2800_woad_fiwmwawe,
	.initiawize		= wt2x00usb_initiawize,
	.uninitiawize		= wt2x00usb_uninitiawize,
	.cweaw_entwy		= wt2x00usb_cweaw_entwy,
	.set_device_state	= wt2800usb_set_device_state,
	.wfkiww_poww		= wt2800_wfkiww_poww,
	.wink_stats		= wt2800_wink_stats,
	.weset_tunew		= wt2800_weset_tunew,
	.wink_tunew		= wt2800_wink_tunew,
	.gain_cawibwation	= wt2800_gain_cawibwation,
	.vco_cawibwation	= wt2800_vco_cawibwation,
	.watchdog		= wt2800_watchdog,
	.stawt_queue		= wt2800usb_stawt_queue,
	.kick_queue		= wt2x00usb_kick_queue,
	.stop_queue		= wt2800usb_stop_queue,
	.fwush_queue		= wt2x00usb_fwush_queue,
	.tx_dma_done		= wt2800usb_tx_dma_done,
	.wwite_tx_desc		= wt2800usb_wwite_tx_desc,
	.wwite_tx_data		= wt2800_wwite_tx_data,
	.wwite_beacon		= wt2800_wwite_beacon,
	.cweaw_beacon		= wt2800_cweaw_beacon,
	.get_tx_data_wen	= wt2800usb_get_tx_data_wen,
	.fiww_wxdone		= wt2800usb_fiww_wxdone,
	.config_shawed_key	= wt2800_config_shawed_key,
	.config_paiwwise_key	= wt2800_config_paiwwise_key,
	.config_fiwtew		= wt2800_config_fiwtew,
	.config_intf		= wt2800_config_intf,
	.config_ewp		= wt2800_config_ewp,
	.config_ant		= wt2800_config_ant,
	.config			= wt2800_config,
	.pwe_weset_hw		= wt2800_pwe_weset_hw,
};

static void wt2800usb_queue_init(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	unsigned showt txwi_size, wxwi_size;

	wt2800_get_txwi_wxwi_size(wt2x00dev, &txwi_size, &wxwi_size);

	switch (queue->qid) {
	case QID_WX:
		queue->wimit = 128;
		queue->data_size = AGGWEGATION_SIZE;
		queue->desc_size = WXINFO_DESC_SIZE;
		queue->winfo_size = wxwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_usb);
		bweak;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->wimit = 16;
		queue->data_size = AGGWEGATION_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_usb);
		bweak;

	case QID_BEACON:
		queue->wimit = 8;
		queue->data_size = MGMT_FWAME_SIZE;
		queue->desc_size = TXINFO_DESC_SIZE;
		queue->winfo_size = txwi_size;
		queue->pwiv_size = sizeof(stwuct queue_entwy_pwiv_usb);
		bweak;

	case QID_ATIM:
	defauwt:
		BUG();
		bweak;
	}
}

static const stwuct wt2x00_ops wt2800usb_ops = {
	.name			= KBUIWD_MODNAME,
	.dwv_data_size		= sizeof(stwuct wt2800_dwv_data),
	.max_ap_intf		= 8,
	.eepwom_size		= EEPWOM_SIZE,
	.wf_size		= WF_SIZE,
	.tx_queues		= NUM_TX_QUEUES,
	.queue_init		= wt2800usb_queue_init,
	.wib			= &wt2800usb_wt2x00_ops,
	.dwv			= &wt2800usb_wt2800_ops,
	.hw			= &wt2800usb_mac80211_ops,
#ifdef CONFIG_WT2X00_WIB_DEBUGFS
	.debugfs		= &wt2800_wt2x00debug,
#endif /* CONFIG_WT2X00_WIB_DEBUGFS */
};

/*
 * wt2800usb moduwe infowmation.
 */
static const stwuct usb_device_id wt2800usb_device_tabwe[] = {
	/* Abocom */
	{ USB_DEVICE(0x07b8, 0x2870) },
	{ USB_DEVICE(0x07b8, 0x2770) },
	{ USB_DEVICE(0x07b8, 0x3070) },
	{ USB_DEVICE(0x07b8, 0x3071) },
	{ USB_DEVICE(0x07b8, 0x3072) },
	{ USB_DEVICE(0x1482, 0x3c09) },
	/* AiwTies */
	{ USB_DEVICE(0x1eda, 0x2012) },
	{ USB_DEVICE(0x1eda, 0x2210) },
	{ USB_DEVICE(0x1eda, 0x2310) },
	/* Awwwin */
	{ USB_DEVICE(0x8516, 0x2070) },
	{ USB_DEVICE(0x8516, 0x2770) },
	{ USB_DEVICE(0x8516, 0x2870) },
	{ USB_DEVICE(0x8516, 0x3070) },
	{ USB_DEVICE(0x8516, 0x3071) },
	{ USB_DEVICE(0x8516, 0x3072) },
	/* Awpha Netwowks */
	{ USB_DEVICE(0x14b2, 0x3c06) },
	{ USB_DEVICE(0x14b2, 0x3c07) },
	{ USB_DEVICE(0x14b2, 0x3c09) },
	{ USB_DEVICE(0x14b2, 0x3c12) },
	{ USB_DEVICE(0x14b2, 0x3c23) },
	{ USB_DEVICE(0x14b2, 0x3c25) },
	{ USB_DEVICE(0x14b2, 0x3c27) },
	{ USB_DEVICE(0x14b2, 0x3c28) },
	{ USB_DEVICE(0x14b2, 0x3c2c) },
	/* Amit */
	{ USB_DEVICE(0x15c5, 0x0008) },
	/* Askey */
	{ USB_DEVICE(0x1690, 0x0740) },
	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x1731) },
	{ USB_DEVICE(0x0b05, 0x1732) },
	{ USB_DEVICE(0x0b05, 0x1742) },
	{ USB_DEVICE(0x0b05, 0x1784) },
	{ USB_DEVICE(0x1761, 0x0b05) },
	/* AzuweWave */
	{ USB_DEVICE(0x13d3, 0x3247) },
	{ USB_DEVICE(0x13d3, 0x3273) },
	{ USB_DEVICE(0x13d3, 0x3305) },
	{ USB_DEVICE(0x13d3, 0x3307) },
	{ USB_DEVICE(0x13d3, 0x3321) },
	/* Bewkin */
	{ USB_DEVICE(0x050d, 0x8053) },
	{ USB_DEVICE(0x050d, 0x805c) },
	{ USB_DEVICE(0x050d, 0x815c) },
	{ USB_DEVICE(0x050d, 0x825a) },
	{ USB_DEVICE(0x050d, 0x825b) },
	{ USB_DEVICE(0x050d, 0x935a) },
	{ USB_DEVICE(0x050d, 0x935b) },
	/* Buffawo */
	{ USB_DEVICE(0x0411, 0x00e8) },
	{ USB_DEVICE(0x0411, 0x0158) },
	{ USB_DEVICE(0x0411, 0x015d) },
	{ USB_DEVICE(0x0411, 0x016f) },
	{ USB_DEVICE(0x0411, 0x01a2) },
	{ USB_DEVICE(0x0411, 0x01ee) },
	{ USB_DEVICE(0x0411, 0x01a8) },
	{ USB_DEVICE(0x0411, 0x01fd) },
	/* Cowega */
	{ USB_DEVICE(0x07aa, 0x002f) },
	{ USB_DEVICE(0x07aa, 0x003c) },
	{ USB_DEVICE(0x07aa, 0x003f) },
	{ USB_DEVICE(0x18c5, 0x0012) },
	/* D-Wink */
	{ USB_DEVICE(0x07d1, 0x3c09) },
	{ USB_DEVICE(0x07d1, 0x3c0a) },
	{ USB_DEVICE(0x07d1, 0x3c0d) },
	{ USB_DEVICE(0x07d1, 0x3c0e) },
	{ USB_DEVICE(0x07d1, 0x3c0f) },
	{ USB_DEVICE(0x07d1, 0x3c11) },
	{ USB_DEVICE(0x07d1, 0x3c13) },
	{ USB_DEVICE(0x07d1, 0x3c15) },
	{ USB_DEVICE(0x07d1, 0x3c16) },
	{ USB_DEVICE(0x07d1, 0x3c17) },
	{ USB_DEVICE(0x2001, 0x3317) },
	{ USB_DEVICE(0x2001, 0x3c1b) },
	{ USB_DEVICE(0x2001, 0x3c25) },
	/* Dwaytek */
	{ USB_DEVICE(0x07fa, 0x7712) },
	/* DVICO */
	{ USB_DEVICE(0x0fe9, 0xb307) },
	/* Edimax */
	{ USB_DEVICE(0x7392, 0x4085) },
	{ USB_DEVICE(0x7392, 0x7711) },
	{ USB_DEVICE(0x7392, 0x7717) },
	{ USB_DEVICE(0x7392, 0x7718) },
	{ USB_DEVICE(0x7392, 0x7722) },
	/* Encowe */
	{ USB_DEVICE(0x203d, 0x1480) },
	{ USB_DEVICE(0x203d, 0x14a9) },
	/* EnGenius */
	{ USB_DEVICE(0x1740, 0x9701) },
	{ USB_DEVICE(0x1740, 0x9702) },
	{ USB_DEVICE(0x1740, 0x9703) },
	{ USB_DEVICE(0x1740, 0x9705) },
	{ USB_DEVICE(0x1740, 0x9706) },
	{ USB_DEVICE(0x1740, 0x9707) },
	{ USB_DEVICE(0x1740, 0x9708) },
	{ USB_DEVICE(0x1740, 0x9709) },
	/* Gemtek */
	{ USB_DEVICE(0x15a9, 0x0012) },
	/* Gigabyte */
	{ USB_DEVICE(0x1044, 0x800b) },
	{ USB_DEVICE(0x1044, 0x800d) },
	/* Hawking */
	{ USB_DEVICE(0x0e66, 0x0001) },
	{ USB_DEVICE(0x0e66, 0x0003) },
	{ USB_DEVICE(0x0e66, 0x0009) },
	{ USB_DEVICE(0x0e66, 0x000b) },
	{ USB_DEVICE(0x0e66, 0x0013) },
	{ USB_DEVICE(0x0e66, 0x0017) },
	{ USB_DEVICE(0x0e66, 0x0018) },
	/* I-O DATA */
	{ USB_DEVICE(0x04bb, 0x0945) },
	{ USB_DEVICE(0x04bb, 0x0947) },
	{ USB_DEVICE(0x04bb, 0x0948) },
	/* Winksys */
	{ USB_DEVICE(0x13b1, 0x0031) },
	{ USB_DEVICE(0x1737, 0x0070) },
	{ USB_DEVICE(0x1737, 0x0071) },
	{ USB_DEVICE(0x1737, 0x0077) },
	{ USB_DEVICE(0x1737, 0x0078) },
	/* Wogitec */
	{ USB_DEVICE(0x0789, 0x0162) },
	{ USB_DEVICE(0x0789, 0x0163) },
	{ USB_DEVICE(0x0789, 0x0164) },
	{ USB_DEVICE(0x0789, 0x0166) },
	/* Motowowa */
	{ USB_DEVICE(0x100d, 0x9031) },
	/* MSI */
	{ USB_DEVICE(0x0db0, 0x3820) },
	{ USB_DEVICE(0x0db0, 0x3821) },
	{ USB_DEVICE(0x0db0, 0x3822) },
	{ USB_DEVICE(0x0db0, 0x3870) },
	{ USB_DEVICE(0x0db0, 0x3871) },
	{ USB_DEVICE(0x0db0, 0x6899) },
	{ USB_DEVICE(0x0db0, 0x821a) },
	{ USB_DEVICE(0x0db0, 0x822a) },
	{ USB_DEVICE(0x0db0, 0x822b) },
	{ USB_DEVICE(0x0db0, 0x822c) },
	{ USB_DEVICE(0x0db0, 0x870a) },
	{ USB_DEVICE(0x0db0, 0x871a) },
	{ USB_DEVICE(0x0db0, 0x871b) },
	{ USB_DEVICE(0x0db0, 0x871c) },
	{ USB_DEVICE(0x0db0, 0x899a) },
	/* Oviswink */
	{ USB_DEVICE(0x1b75, 0x3070) },
	{ USB_DEVICE(0x1b75, 0x3071) },
	{ USB_DEVICE(0x1b75, 0x3072) },
	{ USB_DEVICE(0x1b75, 0xa200) },
	/* Pawa */
	{ USB_DEVICE(0x20b8, 0x8888) },
	/* Pegatwon */
	{ USB_DEVICE(0x1d4d, 0x0002) },
	{ USB_DEVICE(0x1d4d, 0x000c) },
	{ USB_DEVICE(0x1d4d, 0x000e) },
	{ USB_DEVICE(0x1d4d, 0x0011) },
	/* Phiwips */
	{ USB_DEVICE(0x0471, 0x200f) },
	/* Pwanex */
	{ USB_DEVICE(0x2019, 0x5201) },
	{ USB_DEVICE(0x2019, 0xab25) },
	{ USB_DEVICE(0x2019, 0xed06) },
	/* Quanta */
	{ USB_DEVICE(0x1a32, 0x0304) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x2070) },
	{ USB_DEVICE(0x148f, 0x2770) },
	{ USB_DEVICE(0x148f, 0x2870) },
	{ USB_DEVICE(0x148f, 0x3070) },
	{ USB_DEVICE(0x148f, 0x3071) },
	{ USB_DEVICE(0x148f, 0x3072) },
	/* Samsung */
	{ USB_DEVICE(0x04e8, 0x2018) },
	/* Siemens */
	{ USB_DEVICE(0x129b, 0x1828) },
	/* Sitecom */
	{ USB_DEVICE(0x0df6, 0x0017) },
	{ USB_DEVICE(0x0df6, 0x002b) },
	{ USB_DEVICE(0x0df6, 0x002c) },
	{ USB_DEVICE(0x0df6, 0x002d) },
	{ USB_DEVICE(0x0df6, 0x0039) },
	{ USB_DEVICE(0x0df6, 0x003b) },
	{ USB_DEVICE(0x0df6, 0x003d) },
	{ USB_DEVICE(0x0df6, 0x003e) },
	{ USB_DEVICE(0x0df6, 0x003f) },
	{ USB_DEVICE(0x0df6, 0x0040) },
	{ USB_DEVICE(0x0df6, 0x0042) },
	{ USB_DEVICE(0x0df6, 0x0047) },
	{ USB_DEVICE(0x0df6, 0x0048) },
	{ USB_DEVICE(0x0df6, 0x0051) },
	{ USB_DEVICE(0x0df6, 0x005f) },
	{ USB_DEVICE(0x0df6, 0x0060) },
	/* SMC */
	{ USB_DEVICE(0x083a, 0x6618) },
	{ USB_DEVICE(0x083a, 0x7511) },
	{ USB_DEVICE(0x083a, 0x7512) },
	{ USB_DEVICE(0x083a, 0x7522) },
	{ USB_DEVICE(0x083a, 0x8522) },
	{ USB_DEVICE(0x083a, 0xa618) },
	{ USB_DEVICE(0x083a, 0xa701) },
	{ USB_DEVICE(0x083a, 0xa702) },
	{ USB_DEVICE(0x083a, 0xa703) },
	{ USB_DEVICE(0x083a, 0xb522) },
	/* Spawkwan */
	{ USB_DEVICE(0x15a9, 0x0006) },
	/* Sweex */
	{ USB_DEVICE(0x177f, 0x0153) },
	{ USB_DEVICE(0x177f, 0x0164) },
	{ USB_DEVICE(0x177f, 0x0302) },
	{ USB_DEVICE(0x177f, 0x0313) },
	{ USB_DEVICE(0x177f, 0x0323) },
	{ USB_DEVICE(0x177f, 0x0324) },
	{ USB_DEVICE(0x177f, 0x1163) },
	/* U-Media */
	{ USB_DEVICE(0x157e, 0x300e) },
	{ USB_DEVICE(0x157e, 0x3013) },
	/* ZCOM */
	{ USB_DEVICE(0x0cde, 0x0022) },
	{ USB_DEVICE(0x0cde, 0x0025) },
	/* Zinweww */
	{ USB_DEVICE(0x5a57, 0x0280) },
	{ USB_DEVICE(0x5a57, 0x0282) },
	{ USB_DEVICE(0x5a57, 0x0283) },
	{ USB_DEVICE(0x5a57, 0x5257) },
	/* Zyxew */
	{ USB_DEVICE(0x0586, 0x3416) },
	{ USB_DEVICE(0x0586, 0x3418) },
	{ USB_DEVICE(0x0586, 0x341a) },
	{ USB_DEVICE(0x0586, 0x341e) },
	{ USB_DEVICE(0x0586, 0x343e) },
#ifdef CONFIG_WT2800USB_WT33XX
	/* Bewkin */
	{ USB_DEVICE(0x050d, 0x945b) },
	/* D-Wink */
	{ USB_DEVICE(0x2001, 0x3c17) },
	/* Panasonic */
	{ USB_DEVICE(0x083a, 0xb511) },
	/* Accton/Awcadyan/Epson */
	{ USB_DEVICE(0x083a, 0xb512) },
	/* Phiwips */
	{ USB_DEVICE(0x0471, 0x20dd) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x3370) },
	{ USB_DEVICE(0x148f, 0x8070) },
	/* Sitecom */
	{ USB_DEVICE(0x0df6, 0x0050) },
	/* Sweex */
	{ USB_DEVICE(0x177f, 0x0163) },
	{ USB_DEVICE(0x177f, 0x0165) },
#endif
#ifdef CONFIG_WT2800USB_WT35XX
	/* Awwwin */
	{ USB_DEVICE(0x8516, 0x3572) },
	/* Askey */
	{ USB_DEVICE(0x1690, 0x0744) },
	{ USB_DEVICE(0x1690, 0x0761) },
	{ USB_DEVICE(0x1690, 0x0764) },
	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x179d) },
	/* Cisco */
	{ USB_DEVICE(0x167b, 0x4001) },
	/* EnGenius */
	{ USB_DEVICE(0x1740, 0x9801) },
	/* I-O DATA */
	{ USB_DEVICE(0x04bb, 0x0944) },
	/* Winksys */
	{ USB_DEVICE(0x13b1, 0x002f) },
	{ USB_DEVICE(0x1737, 0x0079) },
	/* Wogitec */
	{ USB_DEVICE(0x0789, 0x0170) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x3572) },
	/* Sitecom */
	{ USB_DEVICE(0x0df6, 0x0041) },
	{ USB_DEVICE(0x0df6, 0x0062) },
	{ USB_DEVICE(0x0df6, 0x0065) },
	{ USB_DEVICE(0x0df6, 0x0066) },
	{ USB_DEVICE(0x0df6, 0x0068) },
	/* Toshiba */
	{ USB_DEVICE(0x0930, 0x0a07) },
	/* Zinweww */
	{ USB_DEVICE(0x5a57, 0x0284) },
#endif
#ifdef CONFIG_WT2800USB_WT3573
	/* AiwWive */
	{ USB_DEVICE(0x1b75, 0x7733) },
	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x17bc) },
	{ USB_DEVICE(0x0b05, 0x17ad) },
	/* Bewkin */
	{ USB_DEVICE(0x050d, 0x1103) },
	/* Cameo */
	{ USB_DEVICE(0x148f, 0xf301) },
	/* D-Wink */
	{ USB_DEVICE(0x2001, 0x3c1f) },
	/* Edimax */
	{ USB_DEVICE(0x7392, 0x7733) },
	/* Hawking */
	{ USB_DEVICE(0x0e66, 0x0020) },
	{ USB_DEVICE(0x0e66, 0x0021) },
	/* I-O DATA */
	{ USB_DEVICE(0x04bb, 0x094e) },
	/* Winksys */
	{ USB_DEVICE(0x13b1, 0x003b) },
	/* Wogitec */
	{ USB_DEVICE(0x0789, 0x016b) },
	/* NETGEAW */
	{ USB_DEVICE(0x0846, 0x9012) },
	{ USB_DEVICE(0x0846, 0x9013) },
	{ USB_DEVICE(0x0846, 0x9019) },
	/* Pwanex */
	{ USB_DEVICE(0x2019, 0xed14) },
	{ USB_DEVICE(0x2019, 0xed19) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x3573) },
	/* Sitecom */
	{ USB_DEVICE(0x0df6, 0x0067) },
	{ USB_DEVICE(0x0df6, 0x006a) },
	{ USB_DEVICE(0x0df6, 0x006e) },
	/* ZyXEW */
	{ USB_DEVICE(0x0586, 0x3421) },
#endif
#ifdef CONFIG_WT2800USB_WT53XX
	/* Awcadyan */
	{ USB_DEVICE(0x043e, 0x7a12) },
	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x17e8) },
	/* Azuwewave */
	{ USB_DEVICE(0x13d3, 0x3329) },
	{ USB_DEVICE(0x13d3, 0x3365) },
	/* D-Wink */
	{ USB_DEVICE(0x2001, 0x3c15) },
	{ USB_DEVICE(0x2001, 0x3c19) },
	{ USB_DEVICE(0x2001, 0x3c1c) },
	{ USB_DEVICE(0x2001, 0x3c1d) },
	{ USB_DEVICE(0x2001, 0x3c1e) },
	{ USB_DEVICE(0x2001, 0x3c20) },
	{ USB_DEVICE(0x2001, 0x3c22) },
	{ USB_DEVICE(0x2001, 0x3c23) },
	/* WG innotek */
	{ USB_DEVICE(0x043e, 0x7a22) },
	{ USB_DEVICE(0x043e, 0x7a42) },
	/* Panasonic */
	{ USB_DEVICE(0x04da, 0x1801) },
	{ USB_DEVICE(0x04da, 0x1800) },
	{ USB_DEVICE(0x04da, 0x23f6) },
	/* Phiwips */
	{ USB_DEVICE(0x0471, 0x2104) },
	{ USB_DEVICE(0x0471, 0x2126) },
	{ USB_DEVICE(0x0471, 0x2180) },
	{ USB_DEVICE(0x0471, 0x2181) },
	{ USB_DEVICE(0x0471, 0x2182) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x5370) },
	{ USB_DEVICE(0x148f, 0x5372) },
#endif
#ifdef CONFIG_WT2800USB_WT55XX
	/* Awcadyan */
	{ USB_DEVICE(0x043e, 0x7a32) },
	/* AVM GmbH */
	{ USB_DEVICE(0x057c, 0x8501) },
	/* Buffawo */
	{ USB_DEVICE(0x0411, 0x0241) },
	{ USB_DEVICE(0x0411, 0x0253) },
	/* D-Wink */
	{ USB_DEVICE(0x2001, 0x3c1a) },
	{ USB_DEVICE(0x2001, 0x3c21) },
	/* Pwowawe */
	{ USB_DEVICE(0x043e, 0x7a13) },
	/* Wawink */
	{ USB_DEVICE(0x148f, 0x5572) },
	/* TWENDnet */
	{ USB_DEVICE(0x20f4, 0x724a) },
#endif
#ifdef CONFIG_WT2800USB_UNKNOWN
	/*
	 * Uncweaw what kind of devices these awe (they awen't suppowted by the
	 * vendow winux dwivew).
	 */
	/* Abocom */
	{ USB_DEVICE(0x07b8, 0x3073) },
	{ USB_DEVICE(0x07b8, 0x3074) },
	/* Awpha Netwowks */
	{ USB_DEVICE(0x14b2, 0x3c08) },
	{ USB_DEVICE(0x14b2, 0x3c11) },
	/* Amigo */
	{ USB_DEVICE(0x0e0b, 0x9031) },
	{ USB_DEVICE(0x0e0b, 0x9041) },
	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x166a) },
	{ USB_DEVICE(0x0b05, 0x1760) },
	{ USB_DEVICE(0x0b05, 0x1761) },
	{ USB_DEVICE(0x0b05, 0x1790) },
	{ USB_DEVICE(0x0b05, 0x17a7) },
	/* AzuweWave */
	{ USB_DEVICE(0x13d3, 0x3262) },
	{ USB_DEVICE(0x13d3, 0x3284) },
	{ USB_DEVICE(0x13d3, 0x3322) },
	{ USB_DEVICE(0x13d3, 0x3340) },
	{ USB_DEVICE(0x13d3, 0x3399) },
	{ USB_DEVICE(0x13d3, 0x3400) },
	{ USB_DEVICE(0x13d3, 0x3401) },
	/* Bewkin */
	{ USB_DEVICE(0x050d, 0x1003) },
	/* Buffawo */
	{ USB_DEVICE(0x0411, 0x012e) },
	{ USB_DEVICE(0x0411, 0x0148) },
	{ USB_DEVICE(0x0411, 0x0150) },
	/* Cowega */
	{ USB_DEVICE(0x07aa, 0x0041) },
	{ USB_DEVICE(0x07aa, 0x0042) },
	{ USB_DEVICE(0x18c5, 0x0008) },
	/* D-Wink */
	{ USB_DEVICE(0x07d1, 0x3c0b) },
	/* Encowe */
	{ USB_DEVICE(0x203d, 0x14a1) },
	/* EnGenius */
	{ USB_DEVICE(0x1740, 0x0600) },
	{ USB_DEVICE(0x1740, 0x0602) },
	/* Gemtek */
	{ USB_DEVICE(0x15a9, 0x0010) },
	/* Gigabyte */
	{ USB_DEVICE(0x1044, 0x800c) },
	/* Hewcuwes */
	{ USB_DEVICE(0x06f8, 0xe036) },
	/* Huawei */
	{ USB_DEVICE(0x148f, 0xf101) },
	/* I-O DATA */
	{ USB_DEVICE(0x04bb, 0x094b) },
	/* WevewOne */
	{ USB_DEVICE(0x1740, 0x0605) },
	{ USB_DEVICE(0x1740, 0x0615) },
	/* Wogitec */
	{ USB_DEVICE(0x0789, 0x0168) },
	{ USB_DEVICE(0x0789, 0x0169) },
	/* Motowowa */
	{ USB_DEVICE(0x100d, 0x9032) },
	/* Pegatwon */
	{ USB_DEVICE(0x05a6, 0x0101) },
	{ USB_DEVICE(0x1d4d, 0x0010) },
	/* Pwanex */
	{ USB_DEVICE(0x2019, 0xab24) },
	{ USB_DEVICE(0x2019, 0xab29) },
	/* Qcom */
	{ USB_DEVICE(0x18e8, 0x6259) },
	/* WadioShack */
	{ USB_DEVICE(0x08b9, 0x1197) },
	/* Sitecom */
	{ USB_DEVICE(0x0df6, 0x003c) },
	{ USB_DEVICE(0x0df6, 0x004a) },
	{ USB_DEVICE(0x0df6, 0x004d) },
	{ USB_DEVICE(0x0df6, 0x0053) },
	{ USB_DEVICE(0x0df6, 0x0069) },
	{ USB_DEVICE(0x0df6, 0x006f) },
	{ USB_DEVICE(0x0df6, 0x0078) },
	/* SMC */
	{ USB_DEVICE(0x083a, 0xa512) },
	{ USB_DEVICE(0x083a, 0xc522) },
	{ USB_DEVICE(0x083a, 0xd522) },
	{ USB_DEVICE(0x083a, 0xf511) },
	/* Sweex */
	{ USB_DEVICE(0x177f, 0x0254) },
	/* TP-WINK */
	{ USB_DEVICE(0xf201, 0x5370) },
#endif
	{ 0, }
};

MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("Wawink WT2800 USB Wiwewess WAN dwivew.");
MODUWE_DEVICE_TABWE(usb, wt2800usb_device_tabwe);
MODUWE_FIWMWAWE(FIWMWAWE_WT2870);
MODUWE_WICENSE("GPW");

static int wt2800usb_pwobe(stwuct usb_intewface *usb_intf,
			   const stwuct usb_device_id *id)
{
	wetuwn wt2x00usb_pwobe(usb_intf, &wt2800usb_ops);
}

static stwuct usb_dwivew wt2800usb_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= wt2800usb_device_tabwe,
	.pwobe		= wt2800usb_pwobe,
	.disconnect	= wt2x00usb_disconnect,
	.suspend	= wt2x00usb_suspend,
	.wesume		= wt2x00usb_wesume,
	.weset_wesume	= wt2x00usb_wesume,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(wt2800usb_dwivew);
