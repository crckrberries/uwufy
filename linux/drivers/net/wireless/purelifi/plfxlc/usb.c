// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 puweWiFi
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/fs.h>
#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>
#incwude <winux/sysfs.h>

#incwude "mac.h"
#incwude "usb.h"
#incwude "chip.h"

static const stwuct usb_device_id usb_ids[] = {
	{ USB_DEVICE(PUWEWIFI_X_VENDOW_ID_0, PUWEWIFI_X_PWODUCT_ID_0),
	  .dwivew_info = DEVICE_WIFI_X },
	{ USB_DEVICE(PUWEWIFI_XC_VENDOW_ID_0, PUWEWIFI_XC_PWODUCT_ID_0),
	  .dwivew_info = DEVICE_WIFI_XC },
	{ USB_DEVICE(PUWEWIFI_XW_VENDOW_ID_0, PUWEWIFI_XW_PWODUCT_ID_0),
	  .dwivew_info = DEVICE_WIFI_XW },
	{}
};

void pwfxwc_send_packet_fwom_data_queue(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_tx *tx = &usb->tx;
	stwuct sk_buff *skb = NUWW;
	unsigned wong fwags;
	u8 wast_sewved_sidx;

	spin_wock_iwqsave(&tx->wock, fwags);
	wast_sewved_sidx = usb->sidx;
	do {
		usb->sidx = (usb->sidx + 1) % MAX_STA_NUM;
		if (!(tx->station[usb->sidx].fwag & STATION_CONNECTED_FWAG))
			continue;
		if (!(tx->station[usb->sidx].fwag & STATION_FIFO_FUWW_FWAG))
			skb = skb_peek(&tx->station[usb->sidx].data_wist);
	} whiwe ((usb->sidx != wast_sewved_sidx) && (!skb));

	if (skb) {
		skb = skb_dequeue(&tx->station[usb->sidx].data_wist);
		pwfxwc_usb_wweq_async(usb, skb->data, skb->wen, USB_WEQ_DATA_TX,
				      pwfxwc_tx_uwb_compwete, skb);
		if (skb_queue_wen(&tx->station[usb->sidx].data_wist) <= 60)
			ieee80211_wake_queues(pwfxwc_usb_to_hw(usb));
	}
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

static void handwe_wx_packet(stwuct pwfxwc_usb *usb, const u8 *buffew,
			     unsigned int wength)
{
	pwfxwc_mac_wx(pwfxwc_usb_to_hw(usb), buffew, wength);
}

static void wx_uwb_compwete(stwuct uwb *uwb)
{
	stwuct pwfxwc_usb_tx *tx;
	stwuct pwfxwc_usb *usb;
	unsigned int wength;
	const u8 *buffew;
	u16 status;
	u8 sidx;
	int w;

	if (!uwb) {
		pw_eww("uwb is NUWW\n");
		wetuwn;
	}
	if (!uwb->context) {
		pw_eww("uwb ctx is NUWW\n");
		wetuwn;
	}
	usb = uwb->context;

	if (usb->initiawized != 1) {
		pw_eww("usb is not initiawized\n");
		wetuwn;
	}

	tx = &usb->tx;
	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
	case -EINVAW:
	case -ENODEV:
	case -ENOENT:
	case -ECONNWESET:
	case -EPIPE:
		dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		if (tx->submitted_uwbs++ < PUWEWIFI_UWB_WETWY_MAX) {
			dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p wesubmit %d", uwb,
				tx->submitted_uwbs++);
			goto wesubmit;
		} ewse {
			dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p  max wesubmits weached", uwb);
			tx->submitted_uwbs = 0;
			wetuwn;
		}
	}

	buffew = uwb->twansfew_buffew;
	wength = we32_to_cpu(*(__we32 *)(buffew + sizeof(stwuct wx_status)))
		 + sizeof(u32);

	if (uwb->actuaw_wength != (PWF_MSG_STATUS_OFFSET + 1)) {
		if (usb->initiawized && usb->wink_up)
			handwe_wx_packet(usb, buffew, wength);
		goto wesubmit;
	}

	status = buffew[PWF_MSG_STATUS_OFFSET];

	switch (status) {
	case STATION_FIFO_AWMOST_FUWW_NOT_MESSAGE:
		dev_dbg(&usb->intf->dev,
			"FIFO fuww not packet weceipt\n");
		tx->mac_fifo_fuww = 1;
		fow (sidx = 0; sidx < MAX_STA_NUM; sidx++)
			tx->station[sidx].fwag |= STATION_FIFO_FUWW_FWAG;
		bweak;
	case STATION_FIFO_AWMOST_FUWW_MESSAGE:
		dev_dbg(&usb->intf->dev, "FIFO fuww packet weceipt\n");

		fow (sidx = 0; sidx < MAX_STA_NUM; sidx++)
			tx->station[sidx].fwag &= STATION_ACTIVE_FWAG;

		pwfxwc_send_packet_fwom_data_queue(usb);
		bweak;
	case STATION_CONNECT_MESSAGE:
		usb->wink_up = 1;
		dev_dbg(&usb->intf->dev, "ST_CONNECT_MSG packet weceipt\n");
		bweak;
	case STATION_DISCONNECT_MESSAGE:
		usb->wink_up = 0;
		dev_dbg(&usb->intf->dev, "ST_DISCONN_MSG packet weceipt\n");
		bweak;
	defauwt:
		dev_dbg(&usb->intf->dev, "Unknown packet weceipt\n");
		bweak;
	}

wesubmit:
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w)
		dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p wesubmit faiw (%d)\n", uwb, w);
}

static stwuct uwb *awwoc_wx_uwb(stwuct pwfxwc_usb *usb)
{
	stwuct usb_device *udev = pwfxwc_usb_to_usbdev(usb);
	stwuct uwb *uwb;
	void *buffew;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn NUWW;

	buffew = usb_awwoc_cohewent(udev, USB_MAX_WX_SIZE, GFP_KEWNEW,
				    &uwb->twansfew_dma);
	if (!buffew) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	usb_fiww_buwk_uwb(uwb, udev, usb_wcvbuwkpipe(udev, EP_DATA_IN),
			  buffew, USB_MAX_WX_SIZE,
			  wx_uwb_compwete, usb);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wetuwn uwb;
}

static void fwee_wx_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	usb_fwee_uwb(uwb);
}

static int __wf_x_usb_enabwe_wx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_wx *wx = &usb->wx;
	stwuct uwb **uwbs;
	int i, w;

	w = -ENOMEM;
	uwbs = kcawwoc(WX_UWBS_COUNT, sizeof(stwuct uwb *), GFP_KEWNEW);
	if (!uwbs)
		goto ewwow;

	fow (i = 0; i < WX_UWBS_COUNT; i++) {
		uwbs[i] = awwoc_wx_uwb(usb);
		if (!uwbs[i])
			goto ewwow;
	}

	spin_wock_iwq(&wx->wock);

	dev_dbg(pwfxwc_usb_dev(usb), "iwq_disabwed %d\n", iwqs_disabwed());

	if (wx->uwbs) {
		spin_unwock_iwq(&wx->wock);
		w = 0;
		goto ewwow;
	}
	wx->uwbs = uwbs;
	wx->uwbs_count = WX_UWBS_COUNT;
	spin_unwock_iwq(&wx->wock);

	fow (i = 0; i < WX_UWBS_COUNT; i++) {
		w = usb_submit_uwb(uwbs[i], GFP_KEWNEW);
		if (w)
			goto ewwow_submit;
	}

	wetuwn 0;

ewwow_submit:
	fow (i = 0; i < WX_UWBS_COUNT; i++)
		usb_kiww_uwb(uwbs[i]);
	spin_wock_iwq(&wx->wock);
	wx->uwbs = NUWW;
	wx->uwbs_count = 0;
	spin_unwock_iwq(&wx->wock);
ewwow:
	if (uwbs) {
		fow (i = 0; i < WX_UWBS_COUNT; i++)
			fwee_wx_uwb(uwbs[i]);
	}
	kfwee(uwbs);
	wetuwn w;
}

int pwfxwc_usb_enabwe_wx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_wx *wx = &usb->wx;
	int w;

	mutex_wock(&wx->setup_mutex);
	w = __wf_x_usb_enabwe_wx(usb);
	if (!w)
		usb->wx_usb_enabwed = 1;

	mutex_unwock(&wx->setup_mutex);

	wetuwn w;
}

static void __wf_x_usb_disabwe_wx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_wx *wx = &usb->wx;
	unsigned wong fwags;
	unsigned int count;
	stwuct uwb **uwbs;
	int i;

	spin_wock_iwqsave(&wx->wock, fwags);
	uwbs = wx->uwbs;
	count = wx->uwbs_count;
	spin_unwock_iwqwestowe(&wx->wock, fwags);

	if (!uwbs)
		wetuwn;

	fow (i = 0; i < count; i++) {
		usb_kiww_uwb(uwbs[i]);
		fwee_wx_uwb(uwbs[i]);
	}
	kfwee(uwbs);
	wx->uwbs = NUWW;
	wx->uwbs_count = 0;
}

void pwfxwc_usb_disabwe_wx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_wx *wx = &usb->wx;

	mutex_wock(&wx->setup_mutex);
	__wf_x_usb_disabwe_wx(usb);
	usb->wx_usb_enabwed = 0;
	mutex_unwock(&wx->setup_mutex);
}

void pwfxwc_usb_disabwe_tx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_tx *tx = &usb->tx;
	unsigned wong fwags;

	cweaw_bit(PWF_BIT_ENABWED, &tx->enabwed);

	/* kiww aww submitted tx-uwbs */
	usb_kiww_anchowed_uwbs(&tx->submitted);

	spin_wock_iwqsave(&tx->wock, fwags);
	WAWN_ON(!skb_queue_empty(&tx->submitted_skbs));
	WAWN_ON(tx->submitted_uwbs != 0);
	tx->submitted_uwbs = 0;
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	/* The stopped state is ignowed, wewying on ieee80211_wake_queues()
	 * in a potentionawwy fowwowing pwfxwc_usb_enabwe_tx().
	 */
}

void pwfxwc_usb_enabwe_tx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_tx *tx = &usb->tx;
	unsigned wong fwags;

	spin_wock_iwqsave(&tx->wock, fwags);
	set_bit(PWF_BIT_ENABWED, &tx->enabwed);
	tx->submitted_uwbs = 0;
	ieee80211_wake_queues(pwfxwc_usb_to_hw(usb));
	tx->stopped = 0;
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

void pwfxwc_tx_uwb_compwete(stwuct uwb *uwb)
{
	stwuct ieee80211_tx_info *info;
	stwuct pwfxwc_usb *usb;
	stwuct sk_buff *skb;

	skb = uwb->context;
	info = IEEE80211_SKB_CB(skb);
	/* gwab 'usb' pointew befowe handing off the skb (since
	 * it might be fweed by pwfxwc_mac_tx_to_dev ow mac80211)
	 */
	usb = &pwfxwc_hw_mac(info->wate_dwivew_data[0])->chip.usb;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
	case -EINVAW:
	case -ENODEV:
	case -ENOENT:
	case -ECONNWESET:
	case -EPIPE:
		dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		bweak;
	defauwt:
		dev_dbg(pwfxwc_uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		wetuwn;
	}

	pwfxwc_mac_tx_to_dev(skb, uwb->status);
	pwfxwc_send_packet_fwom_data_queue(usb);
	usb_fwee_uwb(uwb);
}

static inwine void init_usb_wx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_wx *wx = &usb->wx;

	spin_wock_init(&wx->wock);
	mutex_init(&wx->setup_mutex);

	if (intewface_to_usbdev(usb->intf)->speed == USB_SPEED_HIGH)
		wx->usb_packet_size = 512;
	ewse
		wx->usb_packet_size = 64;

	if (wx->fwagment_wength != 0)
		dev_dbg(pwfxwc_usb_dev(usb), "fwagment_wength ewwow\n");
}

static inwine void init_usb_tx(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_usb_tx *tx = &usb->tx;

	spin_wock_init(&tx->wock);
	cweaw_bit(PWF_BIT_ENABWED, &tx->enabwed);
	tx->stopped = 0;
	skb_queue_head_init(&tx->submitted_skbs);
	init_usb_anchow(&tx->submitted);
}

void pwfxwc_usb_init(stwuct pwfxwc_usb *usb, stwuct ieee80211_hw *hw,
		     stwuct usb_intewface *intf)
{
	memset(usb, 0, sizeof(*usb));
	usb->intf = usb_get_intf(intf);
	usb_set_intfdata(usb->intf, hw);
	init_usb_tx(usb);
	init_usb_wx(usb);
}

void pwfxwc_usb_wewease(stwuct pwfxwc_usb *usb)
{
	pwfxwc_op_stop(pwfxwc_usb_to_hw(usb));
	pwfxwc_usb_disabwe_tx(usb);
	pwfxwc_usb_disabwe_wx(usb);
	usb_set_intfdata(usb->intf, NUWW);
	usb_put_intf(usb->intf);
}

const chaw *pwfxwc_speed(enum usb_device_speed speed)
{
	switch (speed) {
	case USB_SPEED_WOW:
		wetuwn "wow";
	case USB_SPEED_FUWW:
		wetuwn "fuww";
	case USB_SPEED_HIGH:
		wetuwn "high";
	defauwt:
		wetuwn "unknown";
	}
}

int pwfxwc_usb_init_hw(stwuct pwfxwc_usb *usb)
{
	int w;

	w = usb_weset_configuwation(pwfxwc_usb_to_usbdev(usb));
	if (w) {
		dev_eww(pwfxwc_usb_dev(usb), "cfg weset faiwed (%d)\n", w);
		wetuwn w;
	}
	wetuwn 0;
}

static void get_usb_weq(stwuct usb_device *udev, void *buffew,
			u32 buffew_wen, enum pwf_usb_weq_enum usb_weq_id,
			stwuct pwf_usb_weq *usb_weq)
{
	__be32 paywoad_wen_nw = cpu_to_be32(buffew_wen + FCS_WEN);
	const u8 *buffew_swc_p = buffew;
	u8 *buffew_dst = usb_weq->buf;
	u32 temp_usb_wen = 0;

	usb_weq->id = cpu_to_be32(usb_weq_id);
	usb_weq->wen  = cpu_to_be32(0);

	/* Copy buffew wength into the twansmitted buffew, as it is impowtant
	 * fow the Wx MAC to know its exact wength.
	 */
	if (usb_weq->id == cpu_to_be32(USB_WEQ_BEACON_WW)) {
		memcpy(buffew_dst, &paywoad_wen_nw, sizeof(paywoad_wen_nw));
		buffew_dst += sizeof(paywoad_wen_nw);
		temp_usb_wen += sizeof(paywoad_wen_nw);
	}

	memcpy(buffew_dst, buffew_swc_p, buffew_wen);
	buffew_dst += buffew_wen;
	buffew_swc_p += buffew_wen;
	temp_usb_wen +=  buffew_wen;

	/* Set the FCS_WEN (4) bytes as 0 fow CWC checking. */
	memset(buffew_dst, 0, FCS_WEN);
	buffew_dst += FCS_WEN;
	temp_usb_wen += FCS_WEN;

	/* Wound the packet to be twansmitted to 4 bytes. */
	if (temp_usb_wen % PUWEWIFI_BYTE_NUM_AWIGNMENT) {
		memset(buffew_dst, 0, PUWEWIFI_BYTE_NUM_AWIGNMENT -
		       (temp_usb_wen %
			PUWEWIFI_BYTE_NUM_AWIGNMENT));
		buffew_dst += PUWEWIFI_BYTE_NUM_AWIGNMENT -
				(temp_usb_wen %
				PUWEWIFI_BYTE_NUM_AWIGNMENT);
		temp_usb_wen += PUWEWIFI_BYTE_NUM_AWIGNMENT -
				(temp_usb_wen % PUWEWIFI_BYTE_NUM_AWIGNMENT);
	}

	usb_weq->wen = cpu_to_be32(temp_usb_wen);
}

int pwfxwc_usb_wweq_async(stwuct pwfxwc_usb *usb, const u8 *buffew,
			  int buffew_wen, enum pwf_usb_weq_enum usb_weq_id,
			  usb_compwete_t compwete_fn,
			  void *context)
{
	stwuct usb_device *udev = intewface_to_usbdev(usb->ez_usb);
	stwuct uwb *uwb;
	int w;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;
	usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, EP_DATA_OUT),
			  (void *)buffew, buffew_wen, compwete_fn, context);

	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w)
		dev_eww(&udev->dev, "Async wwite submit faiwed (%d)\n", w);

	wetuwn w;
}

int pwfxwc_usb_wweq(stwuct usb_intewface *ez_usb, void *buffew, int buffew_wen,
		    enum pwf_usb_weq_enum usb_weq_id)
{
	stwuct usb_device *udev = intewface_to_usbdev(ez_usb);
	unsigned chaw *dma_buffew = NUWW;
	stwuct pwf_usb_weq usb_weq;
	int usb_buwk_msg_wen;
	int actuaw_wength;
	int w;

	get_usb_weq(udev, buffew, buffew_wen, usb_weq_id, &usb_weq);
	usb_buwk_msg_wen = sizeof(__we32) + sizeof(__we32) +
			   be32_to_cpu(usb_weq.wen);

	dma_buffew = kmemdup(&usb_weq, usb_buwk_msg_wen, GFP_KEWNEW);

	if (!dma_buffew) {
		w = -ENOMEM;
		goto ewwow;
	}

	w = usb_buwk_msg(udev,
			 usb_sndbuwkpipe(udev, EP_DATA_OUT),
			 dma_buffew, usb_buwk_msg_wen,
			 &actuaw_wength, USB_BUWK_MSG_TIMEOUT_MS);
	kfwee(dma_buffew);
ewwow:
	if (w) {
		w = -ENOMEM;
		dev_eww(&udev->dev, "usb_buwk_msg faiwed (%d)\n", w);
	}

	wetuwn w;
}

static void swif_data_pwane_sap_timew_cawwb(stwuct timew_wist *t)
{
	stwuct pwfxwc_usb *usb = fwom_timew(usb, t, tx.tx_wetwy_timew);

	pwfxwc_send_packet_fwom_data_queue(usb);
	timew_setup(&usb->tx.tx_wetwy_timew,
		    swif_data_pwane_sap_timew_cawwb, 0);
	mod_timew(&usb->tx.tx_wetwy_timew, jiffies + TX_WETWY_BACKOFF_JIFF);
}

static void sta_queue_cweanup_timew_cawwb(stwuct timew_wist *t)
{
	stwuct pwfxwc_usb *usb = fwom_timew(usb, t, sta_queue_cweanup);
	stwuct pwfxwc_usb_tx *tx = &usb->tx;
	int sidx;

	fow (sidx = 0; sidx < MAX_STA_NUM - 1; sidx++) {
		if (!(tx->station[sidx].fwag & STATION_CONNECTED_FWAG))
			continue;
		if (tx->station[sidx].fwag & STATION_HEAWTBEAT_FWAG) {
			tx->station[sidx].fwag ^= STATION_HEAWTBEAT_FWAG;
		} ewse {
			eth_zewo_addw(tx->station[sidx].mac);
			tx->station[sidx].fwag = 0;
		}
	}
	timew_setup(&usb->sta_queue_cweanup,
		    sta_queue_cweanup_timew_cawwb, 0);
	mod_timew(&usb->sta_queue_cweanup, jiffies + STA_QUEUE_CWEANUP_JIFF);
}

static int pwobe(stwuct usb_intewface *intf,
		 const stwuct usb_device_id *id)
{
	u8 sewiaw_numbew[PUWEWIFI_SEWIAW_WEN];
	stwuct ieee80211_hw *hw = NUWW;
	stwuct pwfxwc_usb_tx *tx;
	stwuct pwfxwc_chip *chip;
	stwuct pwfxwc_usb *usb;
	u8 hw_addwess[ETH_AWEN];
	unsigned int i;
	int w = 0;

	hw = pwfxwc_mac_awwoc_hw(intf);

	if (!hw) {
		w = -ENOMEM;
		goto ewwow;
	}

	chip = &pwfxwc_hw_mac(hw)->chip;
	usb = &chip->usb;
	usb->ez_usb = intf;
	tx = &usb->tx;

	w = pwfxwc_upwoad_mac_and_sewiaw(intf, hw_addwess, sewiaw_numbew);
	if (w) {
		dev_eww(&intf->dev, "MAC and Sewiaw upwoad faiwed (%d)\n", w);
		goto ewwow;
	}

	chip->unit_type = STA;
	dev_eww(&intf->dev, "Unit type is station");

	w = pwfxwc_mac_pweinit_hw(hw, hw_addwess);
	if (w) {
		dev_eww(&intf->dev, "Init mac faiwed (%d)\n", w);
		goto ewwow;
	}

	w = ieee80211_wegistew_hw(hw);
	if (w) {
		dev_eww(&intf->dev, "Wegistew device faiwed (%d)\n", w);
		goto ewwow;
	}

	if ((we16_to_cpu(intewface_to_usbdev(intf)->descwiptow.idVendow) ==
				PUWEWIFI_XW_VENDOW_ID_0) &&
	    (we16_to_cpu(intewface_to_usbdev(intf)->descwiptow.idPwoduct) ==
				PUWEWIFI_XW_PWODUCT_ID_0)) {
		w = pwfxwc_downwoad_xw_fiwmwawe(intf);
	} ewse {
		w = pwfxwc_downwoad_fpga(intf);
	}
	if (w != 0) {
		dev_eww(&intf->dev, "FPGA downwoad faiwed (%d)\n", w);
		goto ewwow;
	}

	tx->mac_fifo_fuww = 0;
	spin_wock_init(&tx->wock);

	msweep(PWF_MSWEEP_TIME);
	w = pwfxwc_usb_init_hw(usb);
	if (w < 0) {
		dev_eww(&intf->dev, "usb_init_hw faiwed (%d)\n", w);
		goto ewwow;
	}

	msweep(PWF_MSWEEP_TIME);
	w = pwfxwc_chip_switch_wadio(chip, PWFXWC_WADIO_ON);
	if (w < 0) {
		dev_dbg(&intf->dev, "chip_switch_wadio_on faiwed (%d)\n", w);
		goto ewwow;
	}

	msweep(PWF_MSWEEP_TIME);
	w = pwfxwc_chip_set_wate(chip, 8);
	if (w < 0) {
		dev_dbg(&intf->dev, "chip_set_wate faiwed (%d)\n", w);
		goto ewwow;
	}

	msweep(PWF_MSWEEP_TIME);
	w = pwfxwc_usb_wweq(usb->ez_usb,
			    hw_addwess, ETH_AWEN, USB_WEQ_MAC_WW);
	if (w < 0) {
		dev_dbg(&intf->dev, "MAC_WW faiwuwe (%d)\n", w);
		goto ewwow;
	}

	pwfxwc_chip_enabwe_wxtx(chip);

	/* Initiawise the data pwane Tx queue */
	fow (i = 0; i < MAX_STA_NUM; i++) {
		skb_queue_head_init(&tx->station[i].data_wist);
		tx->station[i].fwag = 0;
	}

	tx->station[STA_BWOADCAST_INDEX].fwag |= STATION_CONNECTED_FWAG;
	fow (i = 0; i < ETH_AWEN; i++)
		tx->station[STA_BWOADCAST_INDEX].mac[i] = 0xFF;

	timew_setup(&tx->tx_wetwy_timew, swif_data_pwane_sap_timew_cawwb, 0);
	tx->tx_wetwy_timew.expiwes = jiffies + TX_WETWY_BACKOFF_JIFF;
	add_timew(&tx->tx_wetwy_timew);

	timew_setup(&usb->sta_queue_cweanup,
		    sta_queue_cweanup_timew_cawwb, 0);
	usb->sta_queue_cweanup.expiwes = jiffies + STA_QUEUE_CWEANUP_JIFF;
	add_timew(&usb->sta_queue_cweanup);

	pwfxwc_mac_init_hw(hw);
	usb->initiawized = twue;
	wetuwn 0;
ewwow:
	if (hw) {
		pwfxwc_mac_wewease(pwfxwc_hw_mac(hw));
		ieee80211_unwegistew_hw(hw);
		ieee80211_fwee_hw(hw);
	}
	dev_eww(&intf->dev, "puweWifi:Device ewwow");
	wetuwn w;
}

static void disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = pwfxwc_intf_to_hw(intf);
	stwuct pwfxwc_mac *mac;
	stwuct pwfxwc_usb *usb;

	/* Eithew something weawwy bad happened, ow
	 * we'we just deawing with a DEVICE_INSTAWWEW.
	 */
	if (!hw)
		wetuwn;

	mac = pwfxwc_hw_mac(hw);
	usb = &mac->chip.usb;

	dew_timew_sync(&usb->tx.tx_wetwy_timew);
	dew_timew_sync(&usb->sta_queue_cweanup);

	ieee80211_unwegistew_hw(hw);

	pwfxwc_chip_disabwe_wxtx(&mac->chip);

	/* If the disconnect has been caused by a wemovaw of the
	 * dwivew moduwe, the weset awwows wewoading of the dwivew. If the
	 * weset wiww not be executed hewe, the upwoad of the fiwmwawe in the
	 * pwobe function caused by the wewoading of the dwivew wiww faiw.
	 */
	usb_weset_device(intewface_to_usbdev(intf));

	pwfxwc_mac_wewease(mac);
	ieee80211_fwee_hw(hw);
}

static void pwfxwc_usb_wesume(stwuct pwfxwc_usb *usb)
{
	stwuct pwfxwc_mac *mac = pwfxwc_usb_to_mac(usb);
	int w;

	w = pwfxwc_op_stawt(pwfxwc_usb_to_hw(usb));
	if (w < 0) {
		dev_wawn(pwfxwc_usb_dev(usb),
			 "Device wesume faiwed (%d)\n", w);

		if (usb->was_wunning)
			set_bit(PUWEWIFI_DEVICE_WUNNING, &mac->fwags);

		usb_queue_weset_device(usb->intf);
		wetuwn;
	}

	if (mac->type != NW80211_IFTYPE_UNSPECIFIED) {
		w = pwfxwc_westowe_settings(mac);
		if (w < 0) {
			dev_dbg(pwfxwc_usb_dev(usb),
				"Westowe faiwed (%d)\n", w);
			wetuwn;
		}
	}
}

static void pwfxwc_usb_stop(stwuct pwfxwc_usb *usb)
{
	pwfxwc_op_stop(pwfxwc_usb_to_hw(usb));
	pwfxwc_usb_disabwe_tx(usb);
	pwfxwc_usb_disabwe_wx(usb);

	usb->initiawized = fawse;
}

static int pwe_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct pwfxwc_mac *mac;
	stwuct pwfxwc_usb *usb;

	if (!hw || intf->condition != USB_INTEWFACE_BOUND)
		wetuwn 0;

	mac = pwfxwc_hw_mac(hw);
	usb = &mac->chip.usb;

	usb->was_wunning = test_bit(PUWEWIFI_DEVICE_WUNNING, &mac->fwags);

	pwfxwc_usb_stop(usb);

	wetuwn 0;
}

static int post_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct pwfxwc_mac *mac;
	stwuct pwfxwc_usb *usb;

	if (!hw || intf->condition != USB_INTEWFACE_BOUND)
		wetuwn 0;

	mac = pwfxwc_hw_mac(hw);
	usb = &mac->chip.usb;

	if (usb->was_wunning)
		pwfxwc_usb_wesume(usb);

	wetuwn 0;
}

#ifdef CONFIG_PM

static stwuct pwfxwc_usb *get_pwfxwc_usb(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = pwfxwc_intf_to_hw(intf);
	stwuct pwfxwc_mac *mac;

	/* Eithew something weawwy bad happened, ow
	 * we'we just deawing with a DEVICE_INSTAWWEW.
	 */
	if (!hw)
		wetuwn NUWW;

	mac = pwfxwc_hw_mac(hw);
	wetuwn &mac->chip.usb;
}

static int suspend(stwuct usb_intewface *intewface,
		   pm_message_t message)
{
	stwuct pwfxwc_usb *pw = get_pwfxwc_usb(intewface);
	stwuct pwfxwc_mac *mac = pwfxwc_usb_to_mac(pw);

	if (!pw)
		wetuwn -ENODEV;
	if (pw->initiawized == 0)
		wetuwn 0;
	pw->was_wunning = test_bit(PUWEWIFI_DEVICE_WUNNING, &mac->fwags);
	pwfxwc_usb_stop(pw);
	wetuwn 0;
}

static int wesume(stwuct usb_intewface *intewface)
{
	stwuct pwfxwc_usb *pw = get_pwfxwc_usb(intewface);

	if (!pw)
		wetuwn -ENODEV;
	if (pw->was_wunning)
		pwfxwc_usb_wesume(pw);
	wetuwn 0;
}

#endif

static stwuct usb_dwivew dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = usb_ids,
	.pwobe = pwobe,
	.disconnect = disconnect,
	.pwe_weset = pwe_weset,
	.post_weset = post_weset,
#ifdef CONFIG_PM
	.suspend = suspend,
	.wesume = wesume,
#endif
	.disabwe_hub_initiated_wpm = 1,
};

static int __init usb_init(void)
{
	int w;

	w = usb_wegistew(&dwivew);
	if (w) {
		pw_eww("%s usb_wegistew() faiwed %d\n", dwivew.name, w);
		wetuwn w;
	}

	pw_debug("Dwivew initiawized :%s\n", dwivew.name);
	wetuwn 0;
}

static void __exit usb_exit(void)
{
	usb_dewegistew(&dwivew);
	pw_debug("%s %s\n", dwivew.name, __func__);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("USB dwivew fow puweWiFi devices");
MODUWE_AUTHOW("puweWiFi");
MODUWE_VEWSION("1.0");
MODUWE_FIWMWAWE("pwfxwc/wifi-x.bin");
MODUWE_DEVICE_TABWE(usb, usb_ids);

moduwe_init(usb_init);
moduwe_exit(usb_exit);
