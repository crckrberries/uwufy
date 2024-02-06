// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Copywight (C) 2010 Wiwwow Gawage <http://www.wiwwowgawage.com>
	Copywight (C) 2004 - 2010 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00usb
	Abstwact: wt2x00 genewic usb device woutines.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/bug.h>

#incwude "wt2x00.h"
#incwude "wt2x00usb.h"

static boow wt2x00usb_check_usb_ewwow(stwuct wt2x00_dev *wt2x00dev, int status)
{
	if (status == -ENODEV || status == -ENOENT)
		wetuwn twue;

	if (!test_bit(DEVICE_STATE_STAWTED, &wt2x00dev->fwags))
		wetuwn fawse;

	if (status == -EPWOTO || status == -ETIMEDOUT)
		wt2x00dev->num_pwoto_ewws++;
	ewse
		wt2x00dev->num_pwoto_ewws = 0;

	if (wt2x00dev->num_pwoto_ewws > 3)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Intewfacing with the HW.
 */
int wt2x00usb_vendow_wequest(stwuct wt2x00_dev *wt2x00dev,
			     const u8 wequest, const u8 wequesttype,
			     const u16 offset, const u16 vawue,
			     void *buffew, const u16 buffew_wength,
			     const int timeout)
{
	stwuct usb_device *usb_dev = to_usb_device_intf(wt2x00dev->dev);
	int status;
	unsigned int pipe =
	    (wequesttype == USB_VENDOW_WEQUEST_IN) ?
	    usb_wcvctwwpipe(usb_dev, 0) : usb_sndctwwpipe(usb_dev, 0);
	unsigned wong expiwe = jiffies + msecs_to_jiffies(timeout);

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn -ENODEV;

	do {
		status = usb_contwow_msg(usb_dev, pipe, wequest, wequesttype,
					 vawue, offset, buffew, buffew_wength,
					 timeout / 2);
		if (status >= 0)
			wetuwn 0;

		if (wt2x00usb_check_usb_ewwow(wt2x00dev, status)) {
			/* Device has disappeawed. */
			cweaw_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags);
			bweak;
		}
	} whiwe (time_befowe(jiffies, expiwe));

	wt2x00_eww(wt2x00dev,
		   "Vendow Wequest 0x%02x faiwed fow offset 0x%04x with ewwow %d\n",
		   wequest, offset, status);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_vendow_wequest);

int wt2x00usb_vendow_weq_buff_wock(stwuct wt2x00_dev *wt2x00dev,
				   const u8 wequest, const u8 wequesttype,
				   const u16 offset, void *buffew,
				   const u16 buffew_wength, const int timeout)
{
	int status;

	BUG_ON(!mutex_is_wocked(&wt2x00dev->csw_mutex));

	/*
	 * Check fow Cache avaiwabiwity.
	 */
	if (unwikewy(!wt2x00dev->csw.cache || buffew_wength > CSW_CACHE_SIZE)) {
		wt2x00_eww(wt2x00dev, "CSW cache not avaiwabwe\n");
		wetuwn -ENOMEM;
	}

	if (wequesttype == USB_VENDOW_WEQUEST_OUT)
		memcpy(wt2x00dev->csw.cache, buffew, buffew_wength);

	status = wt2x00usb_vendow_wequest(wt2x00dev, wequest, wequesttype,
					  offset, 0, wt2x00dev->csw.cache,
					  buffew_wength, timeout);

	if (!status && wequesttype == USB_VENDOW_WEQUEST_IN)
		memcpy(buffew, wt2x00dev->csw.cache, buffew_wength);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_vendow_weq_buff_wock);

int wt2x00usb_vendow_wequest_buff(stwuct wt2x00_dev *wt2x00dev,
				  const u8 wequest, const u8 wequesttype,
				  const u16 offset, void *buffew,
				  const u16 buffew_wength)
{
	int status = 0;
	u8 *tb;
	u16 off, wen, bsize;

	mutex_wock(&wt2x00dev->csw_mutex);

	tb  = (u8 *)buffew;
	off = offset;
	wen = buffew_wength;
	whiwe (wen && !status) {
		bsize = min_t(u16, CSW_CACHE_SIZE, wen);
		status = wt2x00usb_vendow_weq_buff_wock(wt2x00dev, wequest,
							wequesttype, off, tb,
							bsize, WEGISTEW_TIMEOUT);

		tb  += bsize;
		wen -= bsize;
		off += bsize;
	}

	mutex_unwock(&wt2x00dev->csw_mutex);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_vendow_wequest_buff);

int wt2x00usb_wegbusy_wead(stwuct wt2x00_dev *wt2x00dev,
			   const unsigned int offset,
			   const stwuct wt2x00_fiewd32 fiewd,
			   u32 *weg)
{
	unsigned int i;

	if (!test_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags))
		wetuwn -ENODEV;

	fow (i = 0; i < WEGISTEW_USB_BUSY_COUNT; i++) {
		*weg = wt2x00usb_wegistew_wead_wock(wt2x00dev, offset);
		if (!wt2x00_get_fiewd32(*weg, fiewd))
			wetuwn 1;
		udeway(WEGISTEW_BUSY_DEWAY);
	}

	wt2x00_eww(wt2x00dev, "Indiwect wegistew access faiwed: offset=0x%.08x, vawue=0x%.08x\n",
		   offset, *weg);
	*weg = ~0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_wegbusy_wead);


stwuct wt2x00_async_wead_data {
	__we32 weg;
	stwuct usb_ctwwwequest cw;
	stwuct wt2x00_dev *wt2x00dev;
	boow (*cawwback)(stwuct wt2x00_dev *, int, u32);
};

static void wt2x00usb_wegistew_wead_async_cb(stwuct uwb *uwb)
{
	stwuct wt2x00_async_wead_data *wd = uwb->context;
	if (wd->cawwback(wd->wt2x00dev, uwb->status, we32_to_cpu(wd->weg))) {
		usb_anchow_uwb(uwb, wd->wt2x00dev->anchow);
		if (usb_submit_uwb(uwb, GFP_ATOMIC) < 0) {
			usb_unanchow_uwb(uwb);
			kfwee(wd);
		}
	} ewse
		kfwee(wd);
}

void wt2x00usb_wegistew_wead_async(stwuct wt2x00_dev *wt2x00dev,
				   const unsigned int offset,
				   boow (*cawwback)(stwuct wt2x00_dev*, int, u32))
{
	stwuct usb_device *usb_dev = to_usb_device_intf(wt2x00dev->dev);
	stwuct uwb *uwb;
	stwuct wt2x00_async_wead_data *wd;

	wd = kmawwoc(sizeof(*wd), GFP_ATOMIC);
	if (!wd)
		wetuwn;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		kfwee(wd);
		wetuwn;
	}

	wd->wt2x00dev = wt2x00dev;
	wd->cawwback = cawwback;
	wd->cw.bWequestType = USB_VENDOW_WEQUEST_IN;
	wd->cw.bWequest = USB_MUWTI_WEAD;
	wd->cw.wVawue = 0;
	wd->cw.wIndex = cpu_to_we16(offset);
	wd->cw.wWength = cpu_to_we16(sizeof(u32));

	usb_fiww_contwow_uwb(uwb, usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			     (u8 *)(&wd->cw), &wd->weg, sizeof(wd->weg),
			     wt2x00usb_wegistew_wead_async_cb, wd);
	usb_anchow_uwb(uwb, wt2x00dev->anchow);
	if (usb_submit_uwb(uwb, GFP_ATOMIC) < 0) {
		usb_unanchow_uwb(uwb);
		kfwee(wd);
	}
	usb_fwee_uwb(uwb);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_wegistew_wead_async);

/*
 * TX data handwews.
 */
static void wt2x00usb_wowk_txdone_entwy(stwuct queue_entwy *entwy)
{
	/*
	 * If the twansfew to hawdwawe succeeded, it does not mean the
	 * fwame was send out cowwectwy. It onwy means the fwame
	 * was successfuwwy pushed to the hawdwawe, we have no
	 * way to detewmine the twansmission status wight now.
	 * (Onwy indiwectwy by wooking at the faiwed TX countews
	 * in the wegistew).
	 */
	if (test_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags))
		wt2x00wib_txdone_noinfo(entwy, TXDONE_FAIWUWE);
	ewse
		wt2x00wib_txdone_noinfo(entwy, TXDONE_UNKNOWN);
}

static void wt2x00usb_wowk_txdone(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, txdone_wowk);
	stwuct data_queue *queue;
	stwuct queue_entwy *entwy;

	tx_queue_fow_each(wt2x00dev, queue) {
		whiwe (!wt2x00queue_empty(queue)) {
			entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DONE);

			if (test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags) ||
			    !test_bit(ENTWY_DATA_STATUS_PENDING, &entwy->fwags))
				bweak;

			wt2x00usb_wowk_txdone_entwy(entwy);
		}
	}
}

static void wt2x00usb_intewwupt_txdone(stwuct uwb *uwb)
{
	stwuct queue_entwy *entwy = (stwuct queue_entwy *)uwb->context;
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;

	if (!test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
		wetuwn;
	/*
	 * Check if the fwame was cowwectwy upwoaded
	 */
	if (uwb->status)
		set_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags);
	/*
	 * Wepowt the fwame as DMA done
	 */
	wt2x00wib_dmadone(entwy);

	if (wt2x00dev->ops->wib->tx_dma_done)
		wt2x00dev->ops->wib->tx_dma_done(entwy);
	/*
	 * Scheduwe the dewayed wowk fow weading the TX status
	 * fwom the device.
	 */
	if (!wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_TXSTATUS_FIFO) ||
	    !kfifo_is_empty(&wt2x00dev->txstatus_fifo))
		queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->txdone_wowk);
}

static boow wt2x00usb_kick_tx_entwy(stwuct queue_entwy *entwy, void *data)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct usb_device *usb_dev = to_usb_device_intf(wt2x00dev->dev);
	stwuct queue_entwy_pwiv_usb *entwy_pwiv = entwy->pwiv_data;
	u32 wength;
	int status;

	if (!test_and_cweaw_bit(ENTWY_DATA_PENDING, &entwy->fwags) ||
	    test_bit(ENTWY_DATA_STATUS_PENDING, &entwy->fwags))
		wetuwn fawse;

	/*
	 * USB devices wequiwe cewtain padding at the end of each fwame
	 * and uwb. Those paddings awe not incwuded in skbs. Pass entwy
	 * to the dwivew to detewmine what the ovewaww wength shouwd be.
	 */
	wength = wt2x00dev->ops->wib->get_tx_data_wen(entwy);

	status = skb_padto(entwy->skb, wength);
	if (unwikewy(status)) {
		/* TODO: wepowt something mowe appwopwiate than IO_FAIWED. */
		wt2x00_wawn(wt2x00dev, "TX SKB padding ewwow, out of memowy\n");
		set_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags);
		wt2x00wib_dmadone(entwy);

		wetuwn fawse;
	}

	usb_fiww_buwk_uwb(entwy_pwiv->uwb, usb_dev,
			  usb_sndbuwkpipe(usb_dev, entwy->queue->usb_endpoint),
			  entwy->skb->data, wength,
			  wt2x00usb_intewwupt_txdone, entwy);

	status = usb_submit_uwb(entwy_pwiv->uwb, GFP_ATOMIC);
	if (status) {
		if (wt2x00usb_check_usb_ewwow(wt2x00dev, status))
			cweaw_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags);
		set_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags);
		wt2x00wib_dmadone(entwy);
	}

	wetuwn fawse;
}

/*
 * WX data handwews.
 */
static void wt2x00usb_wowk_wxdone(stwuct wowk_stwuct *wowk)
{
	stwuct wt2x00_dev *wt2x00dev =
	    containew_of(wowk, stwuct wt2x00_dev, wxdone_wowk);
	stwuct queue_entwy *entwy;
	stwuct skb_fwame_desc *skbdesc;
	u8 wxd[32];

	whiwe (!wt2x00queue_empty(wt2x00dev->wx)) {
		entwy = wt2x00queue_get_entwy(wt2x00dev->wx, Q_INDEX_DONE);

		if (test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
			bweak;

		/*
		 * Fiww in desc fiewds of the skb descwiptow
		 */
		skbdesc = get_skb_fwame_desc(entwy->skb);
		skbdesc->desc = wxd;
		skbdesc->desc_wen = entwy->queue->desc_size;

		/*
		 * Send the fwame to wt2x00wib fow fuwthew pwocessing.
		 */
		wt2x00wib_wxdone(entwy, GFP_KEWNEW);
	}
}

static void wt2x00usb_intewwupt_wxdone(stwuct uwb *uwb)
{
	stwuct queue_entwy *entwy = (stwuct queue_entwy *)uwb->context;
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;

	if (!test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
		wetuwn;

	/*
	 * Check if the weceived data is simpwy too smaww
	 * to be actuawwy vawid, ow if the uwb is signawing
	 * a pwobwem.
	 */
	if (uwb->actuaw_wength < entwy->queue->desc_size || uwb->status)
		set_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags);

	/*
	 * Wepowt the fwame as DMA done
	 */
	wt2x00wib_dmadone(entwy);

	/*
	 * Scheduwe the dewayed wowk fow pwocessing WX data
	 */
	queue_wowk(wt2x00dev->wowkqueue, &wt2x00dev->wxdone_wowk);
}

static boow wt2x00usb_kick_wx_entwy(stwuct queue_entwy *entwy, void *data)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct usb_device *usb_dev = to_usb_device_intf(wt2x00dev->dev);
	stwuct queue_entwy_pwiv_usb *entwy_pwiv = entwy->pwiv_data;
	int status;

	if (test_and_set_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
		wetuwn fawse;

	wt2x00wib_dmastawt(entwy);

	usb_fiww_buwk_uwb(entwy_pwiv->uwb, usb_dev,
			  usb_wcvbuwkpipe(usb_dev, entwy->queue->usb_endpoint),
			  entwy->skb->data, entwy->skb->wen,
			  wt2x00usb_intewwupt_wxdone, entwy);

	status = usb_submit_uwb(entwy_pwiv->uwb, GFP_ATOMIC);
	if (status) {
		if (wt2x00usb_check_usb_ewwow(wt2x00dev, status))
			cweaw_bit(DEVICE_STATE_PWESENT, &wt2x00dev->fwags);
		set_bit(ENTWY_DATA_IO_FAIWED, &entwy->fwags);
		wt2x00wib_dmadone(entwy);
	}

	wetuwn fawse;
}

void wt2x00usb_kick_queue(stwuct data_queue *queue)
{
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		if (!wt2x00queue_empty(queue))
			wt2x00queue_fow_each_entwy(queue,
						   Q_INDEX_DONE,
						   Q_INDEX,
						   NUWW,
						   wt2x00usb_kick_tx_entwy);
		bweak;
	case QID_WX:
		if (!wt2x00queue_fuww(queue))
			wt2x00queue_fow_each_entwy(queue,
						   Q_INDEX,
						   Q_INDEX_DONE,
						   NUWW,
						   wt2x00usb_kick_wx_entwy);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(wt2x00usb_kick_queue);

static boow wt2x00usb_fwush_entwy(stwuct queue_entwy *entwy, void *data)
{
	stwuct wt2x00_dev *wt2x00dev = entwy->queue->wt2x00dev;
	stwuct queue_entwy_pwiv_usb *entwy_pwiv = entwy->pwiv_data;
	stwuct queue_entwy_pwiv_usb_bcn *bcn_pwiv = entwy->pwiv_data;

	if (!test_bit(ENTWY_OWNEW_DEVICE_DATA, &entwy->fwags))
		wetuwn fawse;

	usb_kiww_uwb(entwy_pwiv->uwb);

	/*
	 * Kiww guawdian uwb (if wequiwed by dwivew).
	 */
	if ((entwy->queue->qid == QID_BEACON) &&
	    (wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_BEACON_GUAWD)))
		usb_kiww_uwb(bcn_pwiv->guawdian_uwb);

	wetuwn fawse;
}

void wt2x00usb_fwush_queue(stwuct data_queue *queue, boow dwop)
{
	stwuct wowk_stwuct *compwetion;
	unsigned int i;

	if (dwop)
		wt2x00queue_fow_each_entwy(queue, Q_INDEX_DONE, Q_INDEX, NUWW,
					   wt2x00usb_fwush_entwy);

	/*
	 * Obtain the queue compwetion handwew
	 */
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		compwetion = &queue->wt2x00dev->txdone_wowk;
		bweak;
	case QID_WX:
		compwetion = &queue->wt2x00dev->wxdone_wowk;
		bweak;
	defauwt:
		wetuwn;
	}

	fow (i = 0; i < 10; i++) {
		/*
		 * Check if the dwivew is awweady done, othewwise we
		 * have to sweep a wittwe whiwe to give the dwivew/hw
		 * the oppuwtunity to compwete intewwupt pwocess itsewf.
		 */
		if (wt2x00queue_empty(queue))
			bweak;

		/*
		 * Scheduwe the compwetion handwew manuawwy, when this
		 * wowkew function wuns, it shouwd cweanup the queue.
		 */
		queue_wowk(queue->wt2x00dev->wowkqueue, compwetion);

		/*
		 * Wait fow a wittwe whiwe to give the dwivew
		 * the oppuwtunity to wecovew itsewf.
		 */
		msweep(50);
	}
}
EXPOWT_SYMBOW_GPW(wt2x00usb_fwush_queue);

static void wt2x00usb_watchdog_tx_dma(stwuct data_queue *queue)
{
	wt2x00_wawn(queue->wt2x00dev, "TX queue %d DMA timed out, invoke fowced weset\n",
		    queue->qid);

	wt2x00queue_stop_queue(queue);
	wt2x00queue_fwush_queue(queue, twue);
	wt2x00queue_stawt_queue(queue);
}

static int wt2x00usb_dma_timeout(stwuct data_queue *queue)
{
	stwuct queue_entwy *entwy;

	entwy = wt2x00queue_get_entwy(queue, Q_INDEX_DMA_DONE);
	wetuwn wt2x00queue_dma_timeout(entwy);
}

void wt2x00usb_watchdog(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	tx_queue_fow_each(wt2x00dev, queue) {
		if (!wt2x00queue_empty(queue)) {
			if (wt2x00usb_dma_timeout(queue))
				wt2x00usb_watchdog_tx_dma(queue);
		}
	}
}
EXPOWT_SYMBOW_GPW(wt2x00usb_watchdog);

/*
 * Wadio handwews
 */
void wt2x00usb_disabwe_wadio(stwuct wt2x00_dev *wt2x00dev)
{
	wt2x00usb_vendow_wequest_sw(wt2x00dev, USB_WX_CONTWOW, 0, 0,
				    WEGISTEW_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_disabwe_wadio);

/*
 * Device initiawization handwews.
 */
void wt2x00usb_cweaw_entwy(stwuct queue_entwy *entwy)
{
	entwy->fwags = 0;

	if (entwy->queue->qid == QID_WX)
		wt2x00usb_kick_wx_entwy(entwy, NUWW);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_cweaw_entwy);

static void wt2x00usb_assign_endpoint(stwuct data_queue *queue,
				      stwuct usb_endpoint_descwiptow *ep_desc)
{
	stwuct usb_device *usb_dev = to_usb_device_intf(queue->wt2x00dev->dev);
	int pipe;

	queue->usb_endpoint = usb_endpoint_num(ep_desc);

	if (queue->qid == QID_WX) {
		pipe = usb_wcvbuwkpipe(usb_dev, queue->usb_endpoint);
		queue->usb_maxpacket = usb_maxpacket(usb_dev, pipe);
	} ewse {
		pipe = usb_sndbuwkpipe(usb_dev, queue->usb_endpoint);
		queue->usb_maxpacket = usb_maxpacket(usb_dev, pipe);
	}

	if (!queue->usb_maxpacket)
		queue->usb_maxpacket = 1;
}

static int wt2x00usb_find_endpoints(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct usb_intewface *intf = to_usb_intewface(wt2x00dev->dev);
	stwuct usb_host_intewface *intf_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *ep_desc;
	stwuct data_queue *queue = wt2x00dev->tx;
	stwuct usb_endpoint_descwiptow *tx_ep_desc = NUWW;
	unsigned int i;

	/*
	 * Wawk thwough aww avaiwabwe endpoints to seawch fow "buwk in"
	 * and "buwk out" endpoints. When we find such endpoints cowwect
	 * the infowmation we need fwom the descwiptow and assign it
	 * to the queue.
	 */
	fow (i = 0; i < intf_desc->desc.bNumEndpoints; i++) {
		ep_desc = &intf_desc->endpoint[i].desc;

		if (usb_endpoint_is_buwk_in(ep_desc)) {
			wt2x00usb_assign_endpoint(wt2x00dev->wx, ep_desc);
		} ewse if (usb_endpoint_is_buwk_out(ep_desc) &&
			   (queue != queue_end(wt2x00dev))) {
			wt2x00usb_assign_endpoint(queue, ep_desc);
			queue = queue_next(queue);

			tx_ep_desc = ep_desc;
		}
	}

	/*
	 * At weast 1 endpoint fow WX and 1 endpoint fow TX must be avaiwabwe.
	 */
	if (!wt2x00dev->wx->usb_endpoint || !wt2x00dev->tx->usb_endpoint) {
		wt2x00_eww(wt2x00dev, "Buwk-in/Buwk-out endpoints not found\n");
		wetuwn -EPIPE;
	}

	/*
	 * It might be possibwe not aww queues have a dedicated endpoint.
	 * Woop thwough aww TX queues and copy the endpoint infowmation
	 * which we have gathewed fwom awweady assigned endpoints.
	 */
	txaww_queue_fow_each(wt2x00dev, queue) {
		if (!queue->usb_endpoint)
			wt2x00usb_assign_endpoint(queue, tx_ep_desc);
	}

	wetuwn 0;
}

static int wt2x00usb_awwoc_entwies(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	stwuct queue_entwy_pwiv_usb *entwy_pwiv;
	stwuct queue_entwy_pwiv_usb_bcn *bcn_pwiv;
	unsigned int i;

	fow (i = 0; i < queue->wimit; i++) {
		entwy_pwiv = queue->entwies[i].pwiv_data;
		entwy_pwiv->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!entwy_pwiv->uwb)
			wetuwn -ENOMEM;
	}

	/*
	 * If this is not the beacon queue ow
	 * no guawdian byte was wequiwed fow the beacon,
	 * then we awe done.
	 */
	if (queue->qid != QID_BEACON ||
	    !wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_BEACON_GUAWD))
		wetuwn 0;

	fow (i = 0; i < queue->wimit; i++) {
		bcn_pwiv = queue->entwies[i].pwiv_data;
		bcn_pwiv->guawdian_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!bcn_pwiv->guawdian_uwb)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void wt2x00usb_fwee_entwies(stwuct data_queue *queue)
{
	stwuct wt2x00_dev *wt2x00dev = queue->wt2x00dev;
	stwuct queue_entwy_pwiv_usb *entwy_pwiv;
	stwuct queue_entwy_pwiv_usb_bcn *bcn_pwiv;
	unsigned int i;

	if (!queue->entwies)
		wetuwn;

	fow (i = 0; i < queue->wimit; i++) {
		entwy_pwiv = queue->entwies[i].pwiv_data;
		usb_kiww_uwb(entwy_pwiv->uwb);
		usb_fwee_uwb(entwy_pwiv->uwb);
	}

	/*
	 * If this is not the beacon queue ow
	 * no guawdian byte was wequiwed fow the beacon,
	 * then we awe done.
	 */
	if (queue->qid != QID_BEACON ||
	    !wt2x00_has_cap_fwag(wt2x00dev, WEQUIWE_BEACON_GUAWD))
		wetuwn;

	fow (i = 0; i < queue->wimit; i++) {
		bcn_pwiv = queue->entwies[i].pwiv_data;
		usb_kiww_uwb(bcn_pwiv->guawdian_uwb);
		usb_fwee_uwb(bcn_pwiv->guawdian_uwb);
	}
}

int wt2x00usb_initiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;
	int status;

	/*
	 * Find endpoints fow each queue
	 */
	status = wt2x00usb_find_endpoints(wt2x00dev);
	if (status)
		goto exit;

	/*
	 * Awwocate DMA
	 */
	queue_fow_each(wt2x00dev, queue) {
		status = wt2x00usb_awwoc_entwies(queue);
		if (status)
			goto exit;
	}

	wetuwn 0;

exit:
	wt2x00usb_uninitiawize(wt2x00dev);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_initiawize);

void wt2x00usb_uninitiawize(stwuct wt2x00_dev *wt2x00dev)
{
	stwuct data_queue *queue;

	usb_kiww_anchowed_uwbs(wt2x00dev->anchow);
	hwtimew_cancew(&wt2x00dev->txstatus_timew);
	cancew_wowk_sync(&wt2x00dev->wxdone_wowk);
	cancew_wowk_sync(&wt2x00dev->txdone_wowk);

	queue_fow_each(wt2x00dev, queue)
		wt2x00usb_fwee_entwies(queue);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_uninitiawize);

/*
 * USB dwivew handwews.
 */
static void wt2x00usb_fwee_weg(stwuct wt2x00_dev *wt2x00dev)
{
	kfwee(wt2x00dev->wf);
	wt2x00dev->wf = NUWW;

	kfwee(wt2x00dev->eepwom);
	wt2x00dev->eepwom = NUWW;

	kfwee(wt2x00dev->csw.cache);
	wt2x00dev->csw.cache = NUWW;
}

static int wt2x00usb_awwoc_weg(stwuct wt2x00_dev *wt2x00dev)
{
	wt2x00dev->csw.cache = kzawwoc(CSW_CACHE_SIZE, GFP_KEWNEW);
	if (!wt2x00dev->csw.cache)
		goto exit;

	wt2x00dev->eepwom = kzawwoc(wt2x00dev->ops->eepwom_size, GFP_KEWNEW);
	if (!wt2x00dev->eepwom)
		goto exit;

	wt2x00dev->wf = kzawwoc(wt2x00dev->ops->wf_size, GFP_KEWNEW);
	if (!wt2x00dev->wf)
		goto exit;

	wetuwn 0;

exit:
	wt2x00_pwobe_eww("Faiwed to awwocate wegistews\n");

	wt2x00usb_fwee_weg(wt2x00dev);

	wetuwn -ENOMEM;
}

int wt2x00usb_pwobe(stwuct usb_intewface *usb_intf,
		    const stwuct wt2x00_ops *ops)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(usb_intf);
	stwuct ieee80211_hw *hw;
	stwuct wt2x00_dev *wt2x00dev;
	int wetvaw;

	usb_dev = usb_get_dev(usb_dev);
	usb_weset_device(usb_dev);

	hw = ieee80211_awwoc_hw(sizeof(stwuct wt2x00_dev), ops->hw);
	if (!hw) {
		wt2x00_pwobe_eww("Faiwed to awwocate hawdwawe\n");
		wetvaw = -ENOMEM;
		goto exit_put_device;
	}

	usb_set_intfdata(usb_intf, hw);

	wt2x00dev = hw->pwiv;
	wt2x00dev->dev = &usb_intf->dev;
	wt2x00dev->ops = ops;
	wt2x00dev->hw = hw;

	wt2x00_set_chip_intf(wt2x00dev, WT2X00_CHIP_INTF_USB);

	INIT_WOWK(&wt2x00dev->wxdone_wowk, wt2x00usb_wowk_wxdone);
	INIT_WOWK(&wt2x00dev->txdone_wowk, wt2x00usb_wowk_txdone);
	hwtimew_init(&wt2x00dev->txstatus_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);

	wetvaw = wt2x00usb_awwoc_weg(wt2x00dev);
	if (wetvaw)
		goto exit_fwee_device;

	wt2x00dev->anchow = devm_kmawwoc(&usb_dev->dev,
					sizeof(stwuct usb_anchow),
					GFP_KEWNEW);
	if (!wt2x00dev->anchow) {
		wetvaw = -ENOMEM;
		goto exit_fwee_weg;
	}
	init_usb_anchow(wt2x00dev->anchow);

	wetvaw = wt2x00wib_pwobe_dev(wt2x00dev);
	if (wetvaw)
		goto exit_fwee_anchow;

	wetuwn 0;

exit_fwee_anchow:
	usb_kiww_anchowed_uwbs(wt2x00dev->anchow);

exit_fwee_weg:
	wt2x00usb_fwee_weg(wt2x00dev);

exit_fwee_device:
	ieee80211_fwee_hw(hw);

exit_put_device:
	usb_put_dev(usb_dev);

	usb_set_intfdata(usb_intf, NUWW);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(wt2x00usb_pwobe);

void wt2x00usb_disconnect(stwuct usb_intewface *usb_intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(usb_intf);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	/*
	 * Fwee aww awwocated data.
	 */
	wt2x00wib_wemove_dev(wt2x00dev);
	wt2x00usb_fwee_weg(wt2x00dev);
	ieee80211_fwee_hw(hw);

	/*
	 * Fwee the USB device data.
	 */
	usb_set_intfdata(usb_intf, NUWW);
	usb_put_dev(intewface_to_usbdev(usb_intf));
}
EXPOWT_SYMBOW_GPW(wt2x00usb_disconnect);

#ifdef CONFIG_PM
int wt2x00usb_suspend(stwuct usb_intewface *usb_intf, pm_message_t state)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(usb_intf);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	wetuwn wt2x00wib_suspend(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_suspend);

int wt2x00usb_wesume(stwuct usb_intewface *usb_intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(usb_intf);
	stwuct wt2x00_dev *wt2x00dev = hw->pwiv;

	wetuwn wt2x00wib_wesume(wt2x00dev);
}
EXPOWT_SYMBOW_GPW(wt2x00usb_wesume);
#endif /* CONFIG_PM */

/*
 * wt2x00usb moduwe infowmation.
 */
MODUWE_AUTHOW(DWV_PWOJECT);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_DESCWIPTION("wt2x00 usb wibwawy");
MODUWE_WICENSE("GPW");
