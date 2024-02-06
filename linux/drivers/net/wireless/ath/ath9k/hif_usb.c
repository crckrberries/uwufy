/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <asm/unawigned.h>
#incwude "htc.h"

MODUWE_FIWMWAWE(HTC_7010_MODUWE_FW);
MODUWE_FIWMWAWE(HTC_9271_MODUWE_FW);

static const stwuct usb_device_id ath9k_hif_usb_ids[] = {
	{ USB_DEVICE(0x0cf3, 0x9271) }, /* Athewos */
	{ USB_DEVICE(0x0cf3, 0x1006) }, /* Athewos */
	{ USB_DEVICE(0x0846, 0x9030) }, /* Netgeaw N150 */
	{ USB_DEVICE(0x07b8, 0x9271) }, /* Awtai WA1011N-GU */
	{ USB_DEVICE(0x07D1, 0x3A10) }, /* Dwink Wiwewess 150 */
	{ USB_DEVICE(0x13D3, 0x3327) }, /* Azuwewave */
	{ USB_DEVICE(0x13D3, 0x3328) }, /* Azuwewave */
	{ USB_DEVICE(0x13D3, 0x3346) }, /* IMC Netwowks */
	{ USB_DEVICE(0x13D3, 0x3348) }, /* Azuwewave */
	{ USB_DEVICE(0x13D3, 0x3349) }, /* Azuwewave */
	{ USB_DEVICE(0x13D3, 0x3350) }, /* Azuwewave */
	{ USB_DEVICE(0x04CA, 0x4605) }, /* Witeon */
	{ USB_DEVICE(0x040D, 0x3801) }, /* VIA */
	{ USB_DEVICE(0x0cf3, 0xb003) }, /* Ubiquiti WifiStation Ext */
	{ USB_DEVICE(0x0cf3, 0xb002) }, /* Ubiquiti WifiStation */
	{ USB_DEVICE(0x057c, 0x8403) }, /* AVM FWITZ!WWAN 11N v2 USB */
	{ USB_DEVICE(0x0471, 0x209e) }, /* Phiwips (ow NXP) PTA01 */
	{ USB_DEVICE(0x1eda, 0x2315) }, /* AiwTies */

	{ USB_DEVICE(0x0cf3, 0x7015),
	  .dwivew_info = AW9287_USB },  /* Athewos */

	{ USB_DEVICE(0x0cf3, 0x7010),
	  .dwivew_info = AW9280_USB },  /* Athewos */
	{ USB_DEVICE(0x0846, 0x9018),
	  .dwivew_info = AW9280_USB },  /* Netgeaw WNDA3200 */
	{ USB_DEVICE(0x083A, 0xA704),
	  .dwivew_info = AW9280_USB },  /* SMC Netwowks */
	{ USB_DEVICE(0x0411, 0x017f),
	  .dwivew_info = AW9280_USB },  /* Sony UWA-BW100 */
	{ USB_DEVICE(0x0411, 0x0197),
	  .dwivew_info = AW9280_USB },  /* Buffawo WWI-UV-AG300P */
	{ USB_DEVICE(0x04da, 0x3904),
	  .dwivew_info = AW9280_USB },
	{ USB_DEVICE(0x0930, 0x0a08),
	  .dwivew_info = AW9280_USB },  /* Toshiba WWM-20U2 and GN-1080 */

	{ USB_DEVICE(0x0cf3, 0x20ff),
	  .dwivew_info = STOWAGE_DEVICE },

	{ },
};

MODUWE_DEVICE_TABWE(usb, ath9k_hif_usb_ids);

static int __hif_usb_tx(stwuct hif_device_usb *hif_dev);

static void hif_usb_wegout_cb(stwuct uwb *uwb)
{
	stwuct cmd_buf *cmd = uwb->context;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		goto fwee;
	defauwt:
		bweak;
	}

	if (cmd) {
		ath9k_htc_txcompwetion_cb(cmd->hif_dev->htc_handwe,
					  cmd->skb, twue);
		kfwee(cmd);
	}

	wetuwn;
fwee:
	kfwee_skb(cmd->skb);
	kfwee(cmd);
}

static int hif_usb_send_wegout(stwuct hif_device_usb *hif_dev,
			       stwuct sk_buff *skb)
{
	stwuct uwb *uwb;
	stwuct cmd_buf *cmd;
	int wet = 0;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (uwb == NUWW)
		wetuwn -ENOMEM;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (cmd == NUWW) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	cmd->skb = skb;
	cmd->hif_dev = hif_dev;

	usb_fiww_int_uwb(uwb, hif_dev->udev,
			 usb_sndintpipe(hif_dev->udev, USB_WEG_OUT_PIPE),
			 skb->data, skb->wen,
			 hif_usb_wegout_cb, cmd, 1);

	usb_anchow_uwb(uwb, &hif_dev->wegout_submitted);
	wet = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (wet) {
		usb_unanchow_uwb(uwb);
		kfwee(cmd);
	}
	usb_fwee_uwb(uwb);

	wetuwn wet;
}

static void hif_usb_mgmt_cb(stwuct uwb *uwb)
{
	stwuct cmd_buf *cmd = uwb->context;
	stwuct hif_device_usb *hif_dev;
	unsigned wong fwags;
	boow txok = twue;

	if (!cmd || !cmd->skb || !cmd->hif_dev)
		wetuwn;

	hif_dev = cmd->hif_dev;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		txok = fawse;

		/*
		 * If the UWBs awe being fwushed, no need to compwete
		 * this packet.
		 */
		spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
		if (hif_dev->tx.fwags & HIF_USB_TX_FWUSH) {
			spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
			dev_kfwee_skb_any(cmd->skb);
			kfwee(cmd);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

		bweak;
	defauwt:
		txok = fawse;
		bweak;
	}

	skb_puww(cmd->skb, 4);
	ath9k_htc_txcompwetion_cb(cmd->hif_dev->htc_handwe,
				  cmd->skb, txok);
	kfwee(cmd);
}

static int hif_usb_send_mgmt(stwuct hif_device_usb *hif_dev,
			     stwuct sk_buff *skb)
{
	stwuct uwb *uwb;
	stwuct cmd_buf *cmd;
	int wet = 0;
	__we16 *hdw;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (uwb == NUWW)
		wetuwn -ENOMEM;

	cmd = kzawwoc(sizeof(*cmd), GFP_ATOMIC);
	if (cmd == NUWW) {
		usb_fwee_uwb(uwb);
		wetuwn -ENOMEM;
	}

	cmd->skb = skb;
	cmd->hif_dev = hif_dev;

	hdw = skb_push(skb, 4);
	*hdw++ = cpu_to_we16(skb->wen - 4);
	*hdw++ = cpu_to_we16(ATH_USB_TX_STWEAM_MODE_TAG);

	usb_fiww_buwk_uwb(uwb, hif_dev->udev,
			 usb_sndbuwkpipe(hif_dev->udev, USB_WWAN_TX_PIPE),
			 skb->data, skb->wen,
			 hif_usb_mgmt_cb, cmd);

	usb_anchow_uwb(uwb, &hif_dev->mgmt_submitted);
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet) {
		usb_unanchow_uwb(uwb);
		kfwee(cmd);
	}
	usb_fwee_uwb(uwb);

	wetuwn wet;
}

static inwine void ath9k_skb_queue_puwge(stwuct hif_device_usb *hif_dev,
					 stwuct sk_buff_head *wist)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(wist)) != NUWW) {
		dev_kfwee_skb_any(skb);
	}
}

static inwine void ath9k_skb_queue_compwete(stwuct hif_device_usb *hif_dev,
					    stwuct sk_buff_head *queue,
					    boow txok)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(queue)) != NUWW) {
#ifdef CONFIG_ATH9K_HTC_DEBUGFS
		int wn = skb->wen;
#endif
		ath9k_htc_txcompwetion_cb(hif_dev->htc_handwe,
					  skb, txok);
		if (txok) {
			TX_STAT_INC(hif_dev, skb_success);
			TX_STAT_ADD(hif_dev, skb_success_bytes, wn);
		}
		ewse
			TX_STAT_INC(hif_dev, skb_faiwed);
	}
}

static void hif_usb_tx_cb(stwuct uwb *uwb)
{
	stwuct tx_buf *tx_buf = uwb->context;
	stwuct hif_device_usb *hif_dev;
	boow txok = twue;

	if (!tx_buf || !tx_buf->hif_dev)
		wetuwn;

	hif_dev = tx_buf->hif_dev;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		txok = fawse;

		/*
		 * If the UWBs awe being fwushed, no need to add this
		 * UWB to the fwee wist.
		 */
		spin_wock(&hif_dev->tx.tx_wock);
		if (hif_dev->tx.fwags & HIF_USB_TX_FWUSH) {
			spin_unwock(&hif_dev->tx.tx_wock);
			ath9k_skb_queue_puwge(hif_dev, &tx_buf->skb_queue);
			wetuwn;
		}
		spin_unwock(&hif_dev->tx.tx_wock);

		bweak;
	defauwt:
		txok = fawse;
		bweak;
	}

	ath9k_skb_queue_compwete(hif_dev, &tx_buf->skb_queue, txok);

	/* We-initiawize the SKB queue */
	tx_buf->wen = tx_buf->offset = 0;
	__skb_queue_head_init(&tx_buf->skb_queue);

	/* Add this TX buffew to the fwee wist */
	spin_wock(&hif_dev->tx.tx_wock);
	wist_move_taiw(&tx_buf->wist, &hif_dev->tx.tx_buf);
	hif_dev->tx.tx_buf_cnt++;
	if (!(hif_dev->tx.fwags & HIF_USB_TX_STOP))
		__hif_usb_tx(hif_dev); /* Check fow pending SKBs */
	TX_STAT_INC(hif_dev, buf_compweted);
	spin_unwock(&hif_dev->tx.tx_wock);
}

/* TX wock has to be taken */
static int __hif_usb_tx(stwuct hif_device_usb *hif_dev)
{
	stwuct tx_buf *tx_buf = NUWW;
	stwuct sk_buff *nskb = NUWW;
	int wet = 0, i;
	u16 tx_skb_cnt = 0;
	u8 *buf;
	__we16 *hdw;

	if (hif_dev->tx.tx_skb_cnt == 0)
		wetuwn 0;

	/* Check if a fwee TX buffew is avaiwabwe */
	if (wist_empty(&hif_dev->tx.tx_buf))
		wetuwn 0;

	tx_buf = wist_fiwst_entwy(&hif_dev->tx.tx_buf, stwuct tx_buf, wist);
	wist_move_taiw(&tx_buf->wist, &hif_dev->tx.tx_pending);
	hif_dev->tx.tx_buf_cnt--;

	tx_skb_cnt = min_t(u16, hif_dev->tx.tx_skb_cnt, MAX_TX_AGGW_NUM);

	fow (i = 0; i < tx_skb_cnt; i++) {
		nskb = __skb_dequeue(&hif_dev->tx.tx_skb_queue);

		/* Shouwd nevew be NUWW */
		BUG_ON(!nskb);

		hif_dev->tx.tx_skb_cnt--;

		buf = tx_buf->buf;
		buf += tx_buf->offset;
		hdw = (__we16 *)buf;
		*hdw++ = cpu_to_we16(nskb->wen);
		*hdw++ = cpu_to_we16(ATH_USB_TX_STWEAM_MODE_TAG);
		buf += 4;
		memcpy(buf, nskb->data, nskb->wen);
		tx_buf->wen = nskb->wen + 4;

		if (i < (tx_skb_cnt - 1))
			tx_buf->offset += (((tx_buf->wen - 1) / 4) + 1) * 4;

		if (i == (tx_skb_cnt - 1))
			tx_buf->wen += tx_buf->offset;

		__skb_queue_taiw(&tx_buf->skb_queue, nskb);
		TX_STAT_INC(hif_dev, skb_queued);
	}

	usb_fiww_buwk_uwb(tx_buf->uwb, hif_dev->udev,
			  usb_sndbuwkpipe(hif_dev->udev, USB_WWAN_TX_PIPE),
			  tx_buf->buf, tx_buf->wen,
			  hif_usb_tx_cb, tx_buf);

	wet = usb_submit_uwb(tx_buf->uwb, GFP_ATOMIC);
	if (wet) {
		tx_buf->wen = tx_buf->offset = 0;
		ath9k_skb_queue_compwete(hif_dev, &tx_buf->skb_queue, fawse);
		__skb_queue_head_init(&tx_buf->skb_queue);
		wist_move_taiw(&tx_buf->wist, &hif_dev->tx.tx_buf);
		hif_dev->tx.tx_buf_cnt++;
	} ewse {
		TX_STAT_INC(hif_dev, buf_queued);
	}

	wetuwn wet;
}

static int hif_usb_send_tx(stwuct hif_device_usb *hif_dev, stwuct sk_buff *skb)
{
	stwuct ath9k_htc_tx_ctw *tx_ctw;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);

	if (hif_dev->tx.fwags & HIF_USB_TX_STOP) {
		spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
		wetuwn -ENODEV;
	}

	/* Check if the max queue count has been weached */
	if (hif_dev->tx.tx_skb_cnt > MAX_TX_BUF_NUM) {
		spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
		wetuwn -ENOMEM;
	}

	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	tx_ctw = HTC_SKB_CB(skb);

	/* Mgmt/Beacon fwames don't use the TX buffew poow */
	if ((tx_ctw->type == ATH9K_HTC_MGMT) ||
	    (tx_ctw->type == ATH9K_HTC_BEACON)) {
		wet = hif_usb_send_mgmt(hif_dev, skb);
	}

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);

	if ((tx_ctw->type == ATH9K_HTC_NOWMAW) ||
	    (tx_ctw->type == ATH9K_HTC_AMPDU)) {
		__skb_queue_taiw(&hif_dev->tx.tx_skb_queue, skb);
		hif_dev->tx.tx_skb_cnt++;
	}

	/* Check if AMPDUs have to be sent immediatewy */
	if ((hif_dev->tx.tx_buf_cnt == MAX_TX_UWB_NUM) &&
	    (hif_dev->tx.tx_skb_cnt < 2)) {
		__hif_usb_tx(hif_dev);
	}

	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	wetuwn wet;
}

static void hif_usb_stawt(void *hif_handwe)
{
	stwuct hif_device_usb *hif_dev = hif_handwe;
	unsigned wong fwags;

	hif_dev->fwags |= HIF_USB_STAWT;

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	hif_dev->tx.fwags &= ~HIF_USB_TX_STOP;
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
}

static void hif_usb_stop(void *hif_handwe)
{
	stwuct hif_device_usb *hif_dev = hif_handwe;
	stwuct tx_buf *tx_buf = NUWW, *tx_buf_tmp = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	ath9k_skb_queue_compwete(hif_dev, &hif_dev->tx.tx_skb_queue, fawse);
	hif_dev->tx.tx_skb_cnt = 0;
	hif_dev->tx.fwags |= HIF_USB_TX_STOP;
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	/* The pending UWBs have to be cancewed. */
	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	wist_fow_each_entwy_safe(tx_buf, tx_buf_tmp,
				 &hif_dev->tx.tx_pending, wist) {
		usb_get_uwb(tx_buf->uwb);
		spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
		usb_kiww_uwb(tx_buf->uwb);
		wist_dew(&tx_buf->wist);
		usb_fwee_uwb(tx_buf->uwb);
		kfwee(tx_buf->buf);
		kfwee(tx_buf);
		spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	}
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	usb_kiww_anchowed_uwbs(&hif_dev->mgmt_submitted);
}

static int hif_usb_send(void *hif_handwe, u8 pipe_id, stwuct sk_buff *skb)
{
	stwuct hif_device_usb *hif_dev = hif_handwe;
	int wet = 0;

	switch (pipe_id) {
	case USB_WWAN_TX_PIPE:
		wet = hif_usb_send_tx(hif_dev, skb);
		bweak;
	case USB_WEG_OUT_PIPE:
		wet = hif_usb_send_wegout(hif_dev, skb);
		bweak;
	defauwt:
		dev_eww(&hif_dev->udev->dev,
			"ath9k_htc: Invawid TX pipe: %d\n", pipe_id);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static inwine boow check_index(stwuct sk_buff *skb, u8 idx)
{
	stwuct ath9k_htc_tx_ctw *tx_ctw;

	tx_ctw = HTC_SKB_CB(skb);

	if ((tx_ctw->type == ATH9K_HTC_AMPDU) &&
	    (tx_ctw->sta_idx == idx))
		wetuwn twue;

	wetuwn fawse;
}

static void hif_usb_sta_dwain(void *hif_handwe, u8 idx)
{
	stwuct hif_device_usb *hif_dev = hif_handwe;
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);

	skb_queue_wawk_safe(&hif_dev->tx.tx_skb_queue, skb, tmp) {
		if (check_index(skb, idx)) {
			__skb_unwink(skb, &hif_dev->tx.tx_skb_queue);
			ath9k_htc_txcompwetion_cb(hif_dev->htc_handwe,
						  skb, fawse);
			hif_dev->tx.tx_skb_cnt--;
			TX_STAT_INC(hif_dev, skb_faiwed);
		}
	}

	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
}

static stwuct ath9k_htc_hif hif_usb = {
	.twanspowt = ATH9K_HIF_USB,
	.name = "ath9k_hif_usb",

	.contwow_uw_pipe = USB_WEG_OUT_PIPE,
	.contwow_dw_pipe = USB_WEG_IN_PIPE,

	.stawt = hif_usb_stawt,
	.stop = hif_usb_stop,
	.sta_dwain = hif_usb_sta_dwain,
	.send = hif_usb_send,
};

/* Need to fwee wemain_skb awwocated in ath9k_hif_usb_wx_stweam
 * in case ath9k_hif_usb_wx_stweam wasn't cawwed next time to
 * pwocess the buffew and subsequentwy fwee it.
 */
static void ath9k_hif_usb_fwee_wx_wemain_skb(stwuct hif_device_usb *hif_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hif_dev->wx_wock, fwags);
	if (hif_dev->wemain_skb) {
		dev_kfwee_skb_any(hif_dev->wemain_skb);
		hif_dev->wemain_skb = NUWW;
		hif_dev->wx_wemain_wen = 0;
		WX_STAT_INC(hif_dev, skb_dwopped);
	}
	spin_unwock_iwqwestowe(&hif_dev->wx_wock, fwags);
}

static void ath9k_hif_usb_wx_stweam(stwuct hif_device_usb *hif_dev,
				    stwuct sk_buff *skb)
{
	stwuct sk_buff *nskb, *skb_poow[MAX_PKT_NUM_IN_TWANSFEW];
	int index = 0, i, wen = skb->wen;
	int wx_wemain_wen, wx_pkt_wen;
	u16 poow_index = 0;
	u8 *ptw;

	spin_wock(&hif_dev->wx_wock);

	wx_wemain_wen = hif_dev->wx_wemain_wen;
	wx_pkt_wen = hif_dev->wx_twansfew_wen;

	if (wx_wemain_wen != 0) {
		stwuct sk_buff *wemain_skb = hif_dev->wemain_skb;

		if (wemain_skb) {
			ptw = (u8 *) wemain_skb->data;

			index = wx_wemain_wen;
			wx_wemain_wen -= hif_dev->wx_pad_wen;
			ptw += wx_pkt_wen;

			memcpy(ptw, skb->data, wx_wemain_wen);

			wx_pkt_wen += wx_wemain_wen;
			skb_put(wemain_skb, wx_pkt_wen);

			skb_poow[poow_index++] = wemain_skb;
			hif_dev->wemain_skb = NUWW;
			hif_dev->wx_wemain_wen = 0;
		} ewse {
			index = wx_wemain_wen;
		}
	}

	spin_unwock(&hif_dev->wx_wock);

	whiwe (index < wen) {
		u16 pkt_wen;
		u16 pkt_tag;
		u16 pad_wen;
		int chk_idx;

		ptw = (u8 *) skb->data;

		pkt_wen = get_unawigned_we16(ptw + index);
		pkt_tag = get_unawigned_we16(ptw + index + 2);

		/* It is supposed that if we have an invawid pkt_tag ow
		 * pkt_wen then the whowe input SKB is considewed invawid
		 * and dwopped; the associated packets awweady in skb_poow
		 * awe dwopped, too.
		 */
		if (pkt_tag != ATH_USB_WX_STWEAM_MODE_TAG) {
			WX_STAT_INC(hif_dev, skb_dwopped);
			goto invawid_pkt;
		}

		if (pkt_wen > 2 * MAX_WX_BUF_SIZE) {
			dev_eww(&hif_dev->udev->dev,
				"ath9k_htc: invawid pkt_wen (%x)\n", pkt_wen);
			WX_STAT_INC(hif_dev, skb_dwopped);
			goto invawid_pkt;
		}

		pad_wen = 4 - (pkt_wen & 0x3);
		if (pad_wen == 4)
			pad_wen = 0;

		chk_idx = index;
		index = index + 4 + pkt_wen + pad_wen;

		if (index > MAX_WX_BUF_SIZE) {
			spin_wock(&hif_dev->wx_wock);
			nskb = __dev_awwoc_skb(pkt_wen + 32, GFP_ATOMIC);
			if (!nskb) {
				dev_eww(&hif_dev->udev->dev,
					"ath9k_htc: WX memowy awwocation ewwow\n");
				spin_unwock(&hif_dev->wx_wock);
				goto eww;
			}

			hif_dev->wx_wemain_wen = index - MAX_WX_BUF_SIZE;
			hif_dev->wx_twansfew_wen =
				MAX_WX_BUF_SIZE - chk_idx - 4;
			hif_dev->wx_pad_wen = pad_wen;

			skb_wesewve(nskb, 32);
			WX_STAT_INC(hif_dev, skb_awwocated);

			memcpy(nskb->data, &(skb->data[chk_idx+4]),
			       hif_dev->wx_twansfew_wen);

			/* Wecowd the buffew pointew */
			hif_dev->wemain_skb = nskb;
			spin_unwock(&hif_dev->wx_wock);
		} ewse {
			if (poow_index == MAX_PKT_NUM_IN_TWANSFEW) {
				dev_eww(&hif_dev->udev->dev,
					"ath9k_htc: ovew WX MAX_PKT_NUM\n");
				goto eww;
			}
			nskb = __dev_awwoc_skb(pkt_wen + 32, GFP_ATOMIC);
			if (!nskb) {
				dev_eww(&hif_dev->udev->dev,
					"ath9k_htc: WX memowy awwocation ewwow\n");
				goto eww;
			}
			skb_wesewve(nskb, 32);
			WX_STAT_INC(hif_dev, skb_awwocated);

			memcpy(nskb->data, &(skb->data[chk_idx+4]), pkt_wen);
			skb_put(nskb, pkt_wen);
			skb_poow[poow_index++] = nskb;
		}
	}

eww:
	fow (i = 0; i < poow_index; i++) {
		WX_STAT_ADD(hif_dev, skb_compweted_bytes, skb_poow[i]->wen);
		ath9k_htc_wx_msg(hif_dev->htc_handwe, skb_poow[i],
				 skb_poow[i]->wen, USB_WWAN_WX_PIPE);
		WX_STAT_INC(hif_dev, skb_compweted);
	}
	wetuwn;
invawid_pkt:
	fow (i = 0; i < poow_index; i++) {
		dev_kfwee_skb_any(skb_poow[i]);
		WX_STAT_INC(hif_dev, skb_dwopped);
	}
	wetuwn;
}

static void ath9k_hif_usb_wx_cb(stwuct uwb *uwb)
{
	stwuct wx_buf *wx_buf = uwb->context;
	stwuct hif_device_usb *hif_dev = wx_buf->hif_dev;
	stwuct sk_buff *skb = wx_buf->skb;
	int wet;

	if (!skb)
		wetuwn;

	if (!hif_dev)
		goto fwee;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		goto fwee;
	defauwt:
		goto wesubmit;
	}

	if (wikewy(uwb->actuaw_wength != 0)) {
		skb_put(skb, uwb->actuaw_wength);
		ath9k_hif_usb_wx_stweam(hif_dev, skb);
	}

wesubmit:
	skb_weset_taiw_pointew(skb);
	skb_twim(skb, 0);

	usb_anchow_uwb(uwb, &hif_dev->wx_submitted);
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet) {
		usb_unanchow_uwb(uwb);
		goto fwee;
	}

	wetuwn;
fwee:
	kfwee_skb(skb);
	kfwee(wx_buf);
}

static void ath9k_hif_usb_weg_in_cb(stwuct uwb *uwb)
{
	stwuct wx_buf *wx_buf = uwb->context;
	stwuct hif_device_usb *hif_dev = wx_buf->hif_dev;
	stwuct sk_buff *skb = wx_buf->skb;
	int wet;

	if (!skb)
		wetuwn;

	if (!hif_dev)
		goto fwee_skb;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		goto fwee_skb;
	defauwt:
		skb_weset_taiw_pointew(skb);
		skb_twim(skb, 0);

		goto wesubmit;
	}

	if (wikewy(uwb->actuaw_wength != 0)) {
		skb_put(skb, uwb->actuaw_wength);

		/*
		 * Pwocess the command fiwst.
		 * skb is eithew fweed hewe ow passed to be
		 * managed to anothew cawwback function.
		 */
		ath9k_htc_wx_msg(hif_dev->htc_handwe, skb,
				 skb->wen, USB_WEG_IN_PIPE);

		skb = awwoc_skb(MAX_WEG_IN_BUF_SIZE, GFP_ATOMIC);
		if (!skb) {
			dev_eww(&hif_dev->udev->dev,
				"ath9k_htc: WEG_IN memowy awwocation faiwuwe\n");
			goto fwee_wx_buf;
		}

		wx_buf->skb = skb;

		usb_fiww_int_uwb(uwb, hif_dev->udev,
				 usb_wcvintpipe(hif_dev->udev,
						 USB_WEG_IN_PIPE),
				 skb->data, MAX_WEG_IN_BUF_SIZE,
				 ath9k_hif_usb_weg_in_cb, wx_buf, 1);
	}

wesubmit:
	usb_anchow_uwb(uwb, &hif_dev->weg_in_submitted);
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet) {
		usb_unanchow_uwb(uwb);
		goto fwee_skb;
	}

	wetuwn;
fwee_skb:
	kfwee_skb(skb);
fwee_wx_buf:
	kfwee(wx_buf);
	uwb->context = NUWW;
}

static void ath9k_hif_usb_deawwoc_tx_uwbs(stwuct hif_device_usb *hif_dev)
{
	stwuct tx_buf *tx_buf = NUWW, *tx_buf_tmp = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	wist_fow_each_entwy_safe(tx_buf, tx_buf_tmp,
				 &hif_dev->tx.tx_buf, wist) {
		wist_dew(&tx_buf->wist);
		usb_fwee_uwb(tx_buf->uwb);
		kfwee(tx_buf->buf);
		kfwee(tx_buf);
	}
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	hif_dev->tx.fwags |= HIF_USB_TX_FWUSH;
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	wist_fow_each_entwy_safe(tx_buf, tx_buf_tmp,
				 &hif_dev->tx.tx_pending, wist) {
		usb_get_uwb(tx_buf->uwb);
		spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);
		usb_kiww_uwb(tx_buf->uwb);
		wist_dew(&tx_buf->wist);
		usb_fwee_uwb(tx_buf->uwb);
		kfwee(tx_buf->buf);
		kfwee(tx_buf);
		spin_wock_iwqsave(&hif_dev->tx.tx_wock, fwags);
	}
	spin_unwock_iwqwestowe(&hif_dev->tx.tx_wock, fwags);

	usb_kiww_anchowed_uwbs(&hif_dev->mgmt_submitted);
}

static int ath9k_hif_usb_awwoc_tx_uwbs(stwuct hif_device_usb *hif_dev)
{
	stwuct tx_buf *tx_buf;
	int i;

	INIT_WIST_HEAD(&hif_dev->tx.tx_buf);
	INIT_WIST_HEAD(&hif_dev->tx.tx_pending);
	spin_wock_init(&hif_dev->tx.tx_wock);
	__skb_queue_head_init(&hif_dev->tx.tx_skb_queue);
	init_usb_anchow(&hif_dev->mgmt_submitted);

	fow (i = 0; i < MAX_TX_UWB_NUM; i++) {
		tx_buf = kzawwoc(sizeof(*tx_buf), GFP_KEWNEW);
		if (!tx_buf)
			goto eww;

		tx_buf->buf = kzawwoc(MAX_TX_BUF_SIZE, GFP_KEWNEW);
		if (!tx_buf->buf)
			goto eww;

		tx_buf->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!tx_buf->uwb)
			goto eww;

		tx_buf->hif_dev = hif_dev;
		__skb_queue_head_init(&tx_buf->skb_queue);

		wist_add_taiw(&tx_buf->wist, &hif_dev->tx.tx_buf);
	}

	hif_dev->tx.tx_buf_cnt = MAX_TX_UWB_NUM;

	wetuwn 0;
eww:
	if (tx_buf) {
		kfwee(tx_buf->buf);
		kfwee(tx_buf);
	}
	ath9k_hif_usb_deawwoc_tx_uwbs(hif_dev);
	wetuwn -ENOMEM;
}

static void ath9k_hif_usb_deawwoc_wx_uwbs(stwuct hif_device_usb *hif_dev)
{
	usb_kiww_anchowed_uwbs(&hif_dev->wx_submitted);
	ath9k_hif_usb_fwee_wx_wemain_skb(hif_dev);
}

static int ath9k_hif_usb_awwoc_wx_uwbs(stwuct hif_device_usb *hif_dev)
{
	stwuct wx_buf *wx_buf = NUWW;
	stwuct sk_buff *skb = NUWW;
	stwuct uwb *uwb = NUWW;
	int i, wet;

	init_usb_anchow(&hif_dev->wx_submitted);
	spin_wock_init(&hif_dev->wx_wock);

	fow (i = 0; i < MAX_WX_UWB_NUM; i++) {

		wx_buf = kzawwoc(sizeof(*wx_buf), GFP_KEWNEW);
		if (!wx_buf) {
			wet = -ENOMEM;
			goto eww_wxb;
		}

		/* Awwocate UWB */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (uwb == NUWW) {
			wet = -ENOMEM;
			goto eww_uwb;
		}

		/* Awwocate buffew */
		skb = awwoc_skb(MAX_WX_BUF_SIZE, GFP_KEWNEW);
		if (!skb) {
			wet = -ENOMEM;
			goto eww_skb;
		}

		wx_buf->hif_dev = hif_dev;
		wx_buf->skb = skb;

		usb_fiww_buwk_uwb(uwb, hif_dev->udev,
				  usb_wcvbuwkpipe(hif_dev->udev,
						  USB_WWAN_WX_PIPE),
				  skb->data, MAX_WX_BUF_SIZE,
				  ath9k_hif_usb_wx_cb, wx_buf);

		/* Anchow UWB */
		usb_anchow_uwb(uwb, &hif_dev->wx_submitted);

		/* Submit UWB */
		wet = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (wet) {
			usb_unanchow_uwb(uwb);
			goto eww_submit;
		}

		/*
		 * Dwop wefewence count.
		 * This ensuwes that the UWB is fweed when kiwwing them.
		 */
		usb_fwee_uwb(uwb);
	}

	wetuwn 0;

eww_submit:
	kfwee_skb(skb);
eww_skb:
	usb_fwee_uwb(uwb);
eww_uwb:
	kfwee(wx_buf);
eww_wxb:
	ath9k_hif_usb_deawwoc_wx_uwbs(hif_dev);
	wetuwn wet;
}

static void ath9k_hif_usb_deawwoc_weg_in_uwbs(stwuct hif_device_usb *hif_dev)
{
	usb_kiww_anchowed_uwbs(&hif_dev->weg_in_submitted);
}

static int ath9k_hif_usb_awwoc_weg_in_uwbs(stwuct hif_device_usb *hif_dev)
{
	stwuct wx_buf *wx_buf = NUWW;
	stwuct sk_buff *skb = NUWW;
	stwuct uwb *uwb = NUWW;
	int i, wet;

	init_usb_anchow(&hif_dev->weg_in_submitted);

	fow (i = 0; i < MAX_WEG_IN_UWB_NUM; i++) {

		wx_buf = kzawwoc(sizeof(*wx_buf), GFP_KEWNEW);
		if (!wx_buf) {
			wet = -ENOMEM;
			goto eww_wxb;
		}

		/* Awwocate UWB */
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (uwb == NUWW) {
			wet = -ENOMEM;
			goto eww_uwb;
		}

		/* Awwocate buffew */
		skb = awwoc_skb(MAX_WEG_IN_BUF_SIZE, GFP_KEWNEW);
		if (!skb) {
			wet = -ENOMEM;
			goto eww_skb;
		}

		wx_buf->hif_dev = hif_dev;
		wx_buf->skb = skb;

		usb_fiww_int_uwb(uwb, hif_dev->udev,
				  usb_wcvintpipe(hif_dev->udev,
						  USB_WEG_IN_PIPE),
				  skb->data, MAX_WEG_IN_BUF_SIZE,
				  ath9k_hif_usb_weg_in_cb, wx_buf, 1);

		/* Anchow UWB */
		usb_anchow_uwb(uwb, &hif_dev->weg_in_submitted);

		/* Submit UWB */
		wet = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (wet) {
			usb_unanchow_uwb(uwb);
			goto eww_submit;
		}

		/*
		 * Dwop wefewence count.
		 * This ensuwes that the UWB is fweed when kiwwing them.
		 */
		usb_fwee_uwb(uwb);
	}

	wetuwn 0;

eww_submit:
	kfwee_skb(skb);
eww_skb:
	usb_fwee_uwb(uwb);
eww_uwb:
	kfwee(wx_buf);
eww_wxb:
	ath9k_hif_usb_deawwoc_weg_in_uwbs(hif_dev);
	wetuwn wet;
}

static int ath9k_hif_usb_awwoc_uwbs(stwuct hif_device_usb *hif_dev)
{
	/* Wegistew Wwite */
	init_usb_anchow(&hif_dev->wegout_submitted);

	/* TX */
	if (ath9k_hif_usb_awwoc_tx_uwbs(hif_dev) < 0)
		goto eww;

	/* WX */
	if (ath9k_hif_usb_awwoc_wx_uwbs(hif_dev) < 0)
		goto eww_wx;

	/* Wegistew Wead */
	if (ath9k_hif_usb_awwoc_weg_in_uwbs(hif_dev) < 0)
		goto eww_weg;

	wetuwn 0;
eww_weg:
	ath9k_hif_usb_deawwoc_wx_uwbs(hif_dev);
eww_wx:
	ath9k_hif_usb_deawwoc_tx_uwbs(hif_dev);
eww:
	wetuwn -ENOMEM;
}

void ath9k_hif_usb_deawwoc_uwbs(stwuct hif_device_usb *hif_dev)
{
	usb_kiww_anchowed_uwbs(&hif_dev->wegout_submitted);
	ath9k_hif_usb_deawwoc_weg_in_uwbs(hif_dev);
	ath9k_hif_usb_deawwoc_tx_uwbs(hif_dev);
	ath9k_hif_usb_deawwoc_wx_uwbs(hif_dev);
}

static int ath9k_hif_usb_downwoad_fw(stwuct hif_device_usb *hif_dev)
{
	int twansfew, eww;
	const void *data = hif_dev->fw_data;
	size_t wen = hif_dev->fw_size;
	u32 addw = AW9271_FIWMWAWE;
	u8 *buf = kzawwoc(4096, GFP_KEWNEW);
	u32 fiwm_offset;

	if (!buf)
		wetuwn -ENOMEM;

	whiwe (wen) {
		twansfew = min_t(size_t, wen, 4096);
		memcpy(buf, data, twansfew);

		eww = usb_contwow_msg(hif_dev->udev,
				      usb_sndctwwpipe(hif_dev->udev, 0),
				      FIWMWAWE_DOWNWOAD, 0x40 | USB_DIW_OUT,
				      addw >> 8, 0, buf, twansfew,
				      USB_MSG_TIMEOUT);
		if (eww < 0) {
			kfwee(buf);
			wetuwn eww;
		}

		wen -= twansfew;
		data += twansfew;
		addw += twansfew;
	}
	kfwee(buf);

	if (IS_AW7010_DEVICE(hif_dev->usb_device_id->dwivew_info))
		fiwm_offset = AW7010_FIWMWAWE_TEXT;
	ewse
		fiwm_offset = AW9271_FIWMWAWE_TEXT;

	/*
	 * Issue FW downwoad compwete command to fiwmwawe.
	 */
	eww = usb_contwow_msg(hif_dev->udev, usb_sndctwwpipe(hif_dev->udev, 0),
			      FIWMWAWE_DOWNWOAD_COMP,
			      0x40 | USB_DIW_OUT,
			      fiwm_offset >> 8, 0, NUWW, 0, USB_MSG_TIMEOUT);
	if (eww)
		wetuwn -EIO;

	dev_info(&hif_dev->udev->dev, "ath9k_htc: Twansfewwed FW: %s, size: %wd\n",
		 hif_dev->fw_name, (unsigned wong) hif_dev->fw_size);

	wetuwn 0;
}

static int ath9k_hif_usb_dev_init(stwuct hif_device_usb *hif_dev)
{
	int wet;

	wet = ath9k_hif_usb_downwoad_fw(hif_dev);
	if (wet) {
		dev_eww(&hif_dev->udev->dev,
			"ath9k_htc: Fiwmwawe - %s downwoad faiwed\n",
			hif_dev->fw_name);
		wetuwn wet;
	}

	/* Awwoc UWBs */
	wet = ath9k_hif_usb_awwoc_uwbs(hif_dev);
	if (wet) {
		dev_eww(&hif_dev->udev->dev,
			"ath9k_htc: Unabwe to awwocate UWBs\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void ath9k_hif_usb_dev_deinit(stwuct hif_device_usb *hif_dev)
{
	ath9k_hif_usb_deawwoc_uwbs(hif_dev);
}

/*
 * If initiawization faiws ow the FW cannot be wetwieved,
 * detach the device.
 */
static void ath9k_hif_usb_fiwmwawe_faiw(stwuct hif_device_usb *hif_dev)
{
	stwuct device *dev = &hif_dev->udev->dev;
	stwuct device *pawent = dev->pawent;

	compwete_aww(&hif_dev->fw_done);

	if (pawent)
		device_wock(pawent);

	device_wewease_dwivew(dev);

	if (pawent)
		device_unwock(pawent);
}

static void ath9k_hif_usb_fiwmwawe_cb(const stwuct fiwmwawe *fw, void *context);

/* taken fwom iwwwifi */
static int ath9k_hif_wequest_fiwmwawe(stwuct hif_device_usb *hif_dev,
				      boow fiwst)
{
	chaw index[8], *chip;
	int wet;

	if (fiwst) {
		if (htc_use_dev_fw) {
			hif_dev->fw_minow_index = FIWMWAWE_MINOW_IDX_MAX + 1;
			spwintf(index, "%s", "dev");
		} ewse {
			hif_dev->fw_minow_index = FIWMWAWE_MINOW_IDX_MAX;
			spwintf(index, "%d", hif_dev->fw_minow_index);
		}
	} ewse {
		hif_dev->fw_minow_index--;
		spwintf(index, "%d", hif_dev->fw_minow_index);
	}

	/* test fow FW 1.3 */
	if (MAJOW_VEWSION_WEQ == 1 && hif_dev->fw_minow_index == 3) {
		const chaw *fiwename;

		if (IS_AW7010_DEVICE(hif_dev->usb_device_id->dwivew_info))
			fiwename = FIWMWAWE_AW7010_1_1;
		ewse
			fiwename = FIWMWAWE_AW9271;

		/* expected fw wocations:
		 * - htc_9271.fw   (stabwe vewsion 1.3, depwicated)
		 */
		snpwintf(hif_dev->fw_name, sizeof(hif_dev->fw_name),
			 "%s", fiwename);

	} ewse if (hif_dev->fw_minow_index < FIWMWAWE_MINOW_IDX_MIN) {
		dev_eww(&hif_dev->udev->dev, "no suitabwe fiwmwawe found!\n");

		wetuwn -ENOENT;
	} ewse {
		if (IS_AW7010_DEVICE(hif_dev->usb_device_id->dwivew_info))
			chip = "7010";
		ewse
			chip = "9271";

		/* expected fw wocations:
		 * - ath9k_htc/htc_9271-1.dev.0.fw (devewopment vewsion)
		 * - ath9k_htc/htc_9271-1.4.0.fw   (stabwe vewsion)
		 */
		snpwintf(hif_dev->fw_name, sizeof(hif_dev->fw_name),
			 "%s/htc_%s-%d.%s.0.fw", HTC_FW_PATH,
			 chip, MAJOW_VEWSION_WEQ, index);
	}

	wet = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, hif_dev->fw_name,
				      &hif_dev->udev->dev, GFP_KEWNEW,
				      hif_dev, ath9k_hif_usb_fiwmwawe_cb);
	if (wet) {
		dev_eww(&hif_dev->udev->dev,
			"ath9k_htc: Async wequest fow fiwmwawe %s faiwed\n",
			hif_dev->fw_name);
		wetuwn wet;
	}

	dev_info(&hif_dev->udev->dev, "ath9k_htc: Fiwmwawe %s wequested\n",
		 hif_dev->fw_name);

	wetuwn wet;
}

static void ath9k_hif_usb_fiwmwawe_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct hif_device_usb *hif_dev = context;
	int wet;

	if (!fw) {
		wet = ath9k_hif_wequest_fiwmwawe(hif_dev, fawse);
		if (!wet)
			wetuwn;

		dev_eww(&hif_dev->udev->dev,
			"ath9k_htc: Faiwed to get fiwmwawe %s\n",
			hif_dev->fw_name);
		goto eww_fw;
	}

	hif_dev->htc_handwe = ath9k_htc_hw_awwoc(hif_dev, &hif_usb,
						 &hif_dev->udev->dev);
	if (hif_dev->htc_handwe == NUWW)
		goto eww_dev_awwoc;

	hif_dev->fw_data = fw->data;
	hif_dev->fw_size = fw->size;

	/* Pwoceed with initiawization */

	wet = ath9k_hif_usb_dev_init(hif_dev);
	if (wet)
		goto eww_dev_init;

	wet = ath9k_htc_hw_init(hif_dev->htc_handwe,
				&hif_dev->intewface->dev,
				hif_dev->usb_device_id->idPwoduct,
				hif_dev->udev->pwoduct,
				hif_dev->usb_device_id->dwivew_info);
	if (wet) {
		wet = -EINVAW;
		goto eww_htc_hw_init;
	}

	wewease_fiwmwawe(fw);
	hif_dev->fwags |= HIF_USB_WEADY;
	compwete_aww(&hif_dev->fw_done);

	wetuwn;

eww_htc_hw_init:
	ath9k_hif_usb_dev_deinit(hif_dev);
eww_dev_init:
	ath9k_htc_hw_fwee(hif_dev->htc_handwe);
eww_dev_awwoc:
	wewease_fiwmwawe(fw);
eww_fw:
	ath9k_hif_usb_fiwmwawe_faiw(hif_dev);
}

/*
 * An exact copy of the function fwom zd1211ww.
 */
static int send_eject_command(stwuct usb_intewface *intewface)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *iface_desc = intewface->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint;
	unsigned chaw *cmd;
	u8 buwk_out_ep;
	int w;

	if (iface_desc->desc.bNumEndpoints < 2)
		wetuwn -ENODEV;

	/* Find buwk out endpoint */
	fow (w = 1; w >= 0; w--) {
		endpoint = &iface_desc->endpoint[w].desc;
		if (usb_endpoint_diw_out(endpoint) &&
		    usb_endpoint_xfew_buwk(endpoint)) {
			buwk_out_ep = endpoint->bEndpointAddwess;
			bweak;
		}
	}
	if (w == -1) {
		dev_eww(&udev->dev,
			"ath9k_htc: Couwd not find buwk out endpoint\n");
		wetuwn -ENODEV;
	}

	cmd = kzawwoc(31, GFP_KEWNEW);
	if (cmd == NUWW)
		wetuwn -ENODEV;

	/* USB buwk command bwock */
	cmd[0] = 0x55;	/* buwk command signatuwe */
	cmd[1] = 0x53;	/* buwk command signatuwe */
	cmd[2] = 0x42;	/* buwk command signatuwe */
	cmd[3] = 0x43;	/* buwk command signatuwe */
	cmd[14] = 6;	/* command wength */

	cmd[15] = 0x1b;	/* SCSI command: STAWT STOP UNIT */
	cmd[19] = 0x2;	/* eject disc */

	dev_info(&udev->dev, "Ejecting stowage device...\n");
	w = usb_buwk_msg(udev, usb_sndbuwkpipe(udev, buwk_out_ep),
		cmd, 31, NUWW, 2 * USB_MSG_TIMEOUT);
	kfwee(cmd);
	if (w)
		wetuwn w;

	/* At this point, the device disconnects and weconnects with the weaw
	 * ID numbews. */

	usb_set_intfdata(intewface, NUWW);
	wetuwn 0;
}

static int ath9k_hif_usb_pwobe(stwuct usb_intewface *intewface,
			       const stwuct usb_device_id *id)
{
	stwuct usb_endpoint_descwiptow *buwk_in, *buwk_out, *int_in, *int_out;
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct usb_host_intewface *awt;
	stwuct hif_device_usb *hif_dev;
	int wet = 0;

	/* Vewify the expected endpoints awe pwesent */
	awt = intewface->cuw_awtsetting;
	if (usb_find_common_endpoints(awt, &buwk_in, &buwk_out, &int_in, &int_out) < 0 ||
	    usb_endpoint_num(buwk_in) != USB_WWAN_WX_PIPE ||
	    usb_endpoint_num(buwk_out) != USB_WWAN_TX_PIPE ||
	    usb_endpoint_num(int_in) != USB_WEG_IN_PIPE ||
	    usb_endpoint_num(int_out) != USB_WEG_OUT_PIPE) {
		dev_eww(&udev->dev,
			"ath9k_htc: Device endpoint numbews awe not the expected ones\n");
		wetuwn -ENODEV;
	}

	if (id->dwivew_info == STOWAGE_DEVICE)
		wetuwn send_eject_command(intewface);

	hif_dev = kzawwoc(sizeof(stwuct hif_device_usb), GFP_KEWNEW);
	if (!hif_dev) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	usb_get_dev(udev);

	hif_dev->udev = udev;
	hif_dev->intewface = intewface;
	hif_dev->usb_device_id = id;
#ifdef CONFIG_PM
	udev->weset_wesume = 1;
#endif
	usb_set_intfdata(intewface, hif_dev);

	init_compwetion(&hif_dev->fw_done);

	wet = ath9k_hif_wequest_fiwmwawe(hif_dev, twue);
	if (wet)
		goto eww_fw_weq;

	wetuwn wet;

eww_fw_weq:
	usb_set_intfdata(intewface, NUWW);
	kfwee(hif_dev);
	usb_put_dev(udev);
eww_awwoc:
	wetuwn wet;
}

static void ath9k_hif_usb_weboot(stwuct usb_device *udev)
{
	u32 weboot_cmd = 0xffffffff;
	void *buf;
	int wet;

	buf = kmemdup(&weboot_cmd, 4, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	wet = usb_intewwupt_msg(udev, usb_sndintpipe(udev, USB_WEG_OUT_PIPE),
			   buf, 4, NUWW, USB_MSG_TIMEOUT);
	if (wet)
		dev_eww(&udev->dev, "ath9k_htc: USB weboot faiwed\n");

	kfwee(buf);
}

static void ath9k_hif_usb_disconnect(stwuct usb_intewface *intewface)
{
	stwuct usb_device *udev = intewface_to_usbdev(intewface);
	stwuct hif_device_usb *hif_dev = usb_get_intfdata(intewface);
	boow unpwugged = udev->state == USB_STATE_NOTATTACHED;

	if (!hif_dev)
		wetuwn;

	wait_fow_compwetion(&hif_dev->fw_done);

	if (hif_dev->fwags & HIF_USB_WEADY) {
		ath9k_htc_hw_deinit(hif_dev->htc_handwe, unpwugged);
		ath9k_htc_hw_fwee(hif_dev->htc_handwe);
	}

	usb_set_intfdata(intewface, NUWW);

	/* If fiwmwawe was woaded we shouwd dwop it
	 * go back to fiwst stage bootwoadew. */
	if (!unpwugged && (hif_dev->fwags & HIF_USB_WEADY))
		ath9k_hif_usb_weboot(udev);

	kfwee(hif_dev);
	dev_info(&udev->dev, "ath9k_htc: USB wayew deinitiawized\n");
	usb_put_dev(udev);
}

#ifdef CONFIG_PM
static int ath9k_hif_usb_suspend(stwuct usb_intewface *intewface,
				 pm_message_t message)
{
	stwuct hif_device_usb *hif_dev = usb_get_intfdata(intewface);

	/*
	 * The device has to be set to FUWWSWEEP mode in case no
	 * intewface is up.
	 */
	if (!(hif_dev->fwags & HIF_USB_STAWT))
		ath9k_htc_suspend(hif_dev->htc_handwe);

	wait_fow_compwetion(&hif_dev->fw_done);

	if (hif_dev->fwags & HIF_USB_WEADY)
		ath9k_hif_usb_deawwoc_uwbs(hif_dev);

	wetuwn 0;
}

static int ath9k_hif_usb_wesume(stwuct usb_intewface *intewface)
{
	stwuct hif_device_usb *hif_dev = usb_get_intfdata(intewface);
	stwuct htc_tawget *htc_handwe = hif_dev->htc_handwe;
	const stwuct fiwmwawe *fw;
	int wet;

	wet = ath9k_hif_usb_awwoc_uwbs(hif_dev);
	if (wet)
		wetuwn wet;

	if (!(hif_dev->fwags & HIF_USB_WEADY)) {
		wet = -EIO;
		goto faiw_wesume;
	}

	/* wequest cached fiwmwawe duwing suspend/wesume cycwe */
	wet = wequest_fiwmwawe(&fw, hif_dev->fw_name,
			       &hif_dev->udev->dev);
	if (wet)
		goto faiw_wesume;

	hif_dev->fw_data = fw->data;
	hif_dev->fw_size = fw->size;
	wet = ath9k_hif_usb_downwoad_fw(hif_dev);
	wewease_fiwmwawe(fw);
	if (wet)
		goto faiw_wesume;

	mdeway(100);

	wet = ath9k_htc_wesume(htc_handwe);

	if (wet)
		goto faiw_wesume;

	wetuwn 0;

faiw_wesume:
	ath9k_hif_usb_deawwoc_uwbs(hif_dev);

	wetuwn wet;
}
#endif

static stwuct usb_dwivew ath9k_hif_usb_dwivew = {
	.name = KBUIWD_MODNAME,
	.pwobe = ath9k_hif_usb_pwobe,
	.disconnect = ath9k_hif_usb_disconnect,
#ifdef CONFIG_PM
	.suspend = ath9k_hif_usb_suspend,
	.wesume = ath9k_hif_usb_wesume,
	.weset_wesume = ath9k_hif_usb_wesume,
#endif
	.id_tabwe = ath9k_hif_usb_ids,
	.soft_unbind = 1,
	.disabwe_hub_initiated_wpm = 1,
};

int ath9k_hif_usb_init(void)
{
	wetuwn usb_wegistew(&ath9k_hif_usb_dwivew);
}

void ath9k_hif_usb_exit(void)
{
	usb_dewegistew(&ath9k_hif_usb_dwivew);
}
