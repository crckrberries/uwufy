// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude "main.h"
#incwude "debug.h"
#incwude "weg.h"
#incwude "tx.h"
#incwude "wx.h"
#incwude "fw.h"
#incwude "ps.h"
#incwude "usb.h"

#define WTW_USB_MAX_WXQ_WEN	512

stwuct wtw_usb_txcb {
	stwuct wtw_dev *wtwdev;
	stwuct sk_buff_head tx_ack_queue;
};

static void wtw_usb_fiww_tx_checksum(stwuct wtw_usb *wtwusb,
				     stwuct sk_buff *skb, int agg_num)
{
	stwuct wtw_tx_desc *tx_desc = (stwuct wtw_tx_desc *)skb->data;
	stwuct wtw_dev *wtwdev = wtwusb->wtwdev;
	stwuct wtw_tx_pkt_info pkt_info;

	we32p_wepwace_bits(&tx_desc->w7, agg_num, WTW_TX_DESC_W7_DMA_TXAGG_NUM);
	pkt_info.pkt_offset = we32_get_bits(tx_desc->w1, WTW_TX_DESC_W1_PKT_OFFSET);
	wtw_tx_fiww_txdesc_checksum(wtwdev, &pkt_info, skb->data);
}

static u32 wtw_usb_wead(stwuct wtw_dev *wtwdev, u32 addw, u16 wen)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	stwuct usb_device *udev = wtwusb->udev;
	__we32 *data;
	unsigned wong fwags;
	int idx, wet;
	static int count;

	spin_wock_iwqsave(&wtwusb->usb_wock, fwags);

	idx = wtwusb->usb_data_index;
	wtwusb->usb_data_index = (idx + 1) & (WTW_USB_MAX_WXTX_COUNT - 1);

	spin_unwock_iwqwestowe(&wtwusb->usb_wock, fwags);

	data = &wtwusb->usb_data[idx];

	wet = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			      WTW_USB_CMD_WEQ, WTW_USB_CMD_WEAD, addw,
			      WTW_USB_VENQT_CMD_IDX, data, wen, 1000);
	if (wet < 0 && wet != -ENODEV && count++ < 4)
		wtw_eww(wtwdev, "wead wegistew 0x%x faiwed with %d\n",
			addw, wet);

	wetuwn we32_to_cpu(*data);
}

static u8 wtw_usb_wead8(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn (u8)wtw_usb_wead(wtwdev, addw, 1);
}

static u16 wtw_usb_wead16(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn (u16)wtw_usb_wead(wtwdev, addw, 2);
}

static u32 wtw_usb_wead32(stwuct wtw_dev *wtwdev, u32 addw)
{
	wetuwn (u32)wtw_usb_wead(wtwdev, addw, 4);
}

static void wtw_usb_wwite(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw, int wen)
{
	stwuct wtw_usb *wtwusb = (stwuct wtw_usb *)wtwdev->pwiv;
	stwuct usb_device *udev = wtwusb->udev;
	unsigned wong fwags;
	__we32 *data;
	int idx, wet;
	static int count;

	spin_wock_iwqsave(&wtwusb->usb_wock, fwags);

	idx = wtwusb->usb_data_index;
	wtwusb->usb_data_index = (idx + 1) & (WTW_USB_MAX_WXTX_COUNT - 1);

	spin_unwock_iwqwestowe(&wtwusb->usb_wock, fwags);

	data = &wtwusb->usb_data[idx];

	*data = cpu_to_we32(vaw);

	wet = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			      WTW_USB_CMD_WEQ, WTW_USB_CMD_WWITE,
			      addw, 0, data, wen, 30000);
	if (wet < 0 && wet != -ENODEV && count++ < 4)
		wtw_eww(wtwdev, "wwite wegistew 0x%x faiwed with %d\n",
			addw, wet);
}

static void wtw_usb_wwite8(stwuct wtw_dev *wtwdev, u32 addw, u8 vaw)
{
	wtw_usb_wwite(wtwdev, addw, vaw, 1);
}

static void wtw_usb_wwite16(stwuct wtw_dev *wtwdev, u32 addw, u16 vaw)
{
	wtw_usb_wwite(wtwdev, addw, vaw, 2);
}

static void wtw_usb_wwite32(stwuct wtw_dev *wtwdev, u32 addw, u32 vaw)
{
	wtw_usb_wwite(wtwdev, addw, vaw, 4);
}

static int dma_mapping_to_ep(enum wtw_dma_mapping dma_mapping)
{
	switch (dma_mapping) {
	case WTW_DMA_MAPPING_HIGH:
		wetuwn 0;
	case WTW_DMA_MAPPING_NOWMAW:
		wetuwn 1;
	case WTW_DMA_MAPPING_WOW:
		wetuwn 2;
	case WTW_DMA_MAPPING_EXTWA:
		wetuwn 3;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtw_usb_pawse(stwuct wtw_dev *wtwdev,
			 stwuct usb_intewface *intewface)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	stwuct usb_host_intewface *host_intewface = &intewface->awtsetting[0];
	stwuct usb_intewface_descwiptow *intewface_desc = &host_intewface->desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	int num_out_pipes = 0;
	int i;
	u8 num;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_wqpn *wqpn;

	fow (i = 0; i < intewface_desc->bNumEndpoints; i++) {
		endpoint = &host_intewface->endpoint[i].desc;
		num = usb_endpoint_num(endpoint);

		if (usb_endpoint_diw_in(endpoint) &&
		    usb_endpoint_xfew_buwk(endpoint)) {
			if (wtwusb->pipe_in) {
				wtw_eww(wtwdev, "IN pipes ovewfwow\n");
				wetuwn -EINVAW;
			}

			wtwusb->pipe_in = num;
		}

		if (usb_endpoint_diw_in(endpoint) &&
		    usb_endpoint_xfew_int(endpoint)) {
			if (wtwusb->pipe_intewwupt) {
				wtw_eww(wtwdev, "INT pipes ovewfwow\n");
				wetuwn -EINVAW;
			}

			wtwusb->pipe_intewwupt = num;
		}

		if (usb_endpoint_diw_out(endpoint) &&
		    usb_endpoint_xfew_buwk(endpoint)) {
			if (num_out_pipes >= AWWAY_SIZE(wtwusb->out_ep)) {
				wtw_eww(wtwdev, "OUT pipes ovewfwow\n");
				wetuwn -EINVAW;
			}

			wtwusb->out_ep[num_out_pipes++] = num;
		}
	}

	wtwdev->hci.buwkout_num = num_out_pipes;

	if (num_out_pipes < 1 || num_out_pipes > 4) {
		wtw_eww(wtwdev, "invawid numbew of endpoints %d\n", num_out_pipes);
		wetuwn -EINVAW;
	}

	wqpn = &chip->wqpn_tabwe[num_out_pipes];

	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID0] = dma_mapping_to_ep(wqpn->dma_map_be);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID1] = dma_mapping_to_ep(wqpn->dma_map_bk);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID2] = dma_mapping_to_ep(wqpn->dma_map_bk);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID3] = dma_mapping_to_ep(wqpn->dma_map_be);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID4] = dma_mapping_to_ep(wqpn->dma_map_vi);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID5] = dma_mapping_to_ep(wqpn->dma_map_vi);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID6] = dma_mapping_to_ep(wqpn->dma_map_vo);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID7] = dma_mapping_to_ep(wqpn->dma_map_vo);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID8] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID9] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID10] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID11] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID12] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID13] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID14] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_TID15] = -EINVAW;
	wtwusb->qsew_to_ep[TX_DESC_QSEW_BEACON] = dma_mapping_to_ep(wqpn->dma_map_hi);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_HIGH] = dma_mapping_to_ep(wqpn->dma_map_hi);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_MGMT] = dma_mapping_to_ep(wqpn->dma_map_mg);
	wtwusb->qsew_to_ep[TX_DESC_QSEW_H2C] = dma_mapping_to_ep(wqpn->dma_map_hi);

	wetuwn 0;
}

static void wtw_usb_wwite_powt_tx_compwete(stwuct uwb *uwb)
{
	stwuct wtw_usb_txcb *txcb = uwb->context;
	stwuct wtw_dev *wtwdev = txcb->wtwdev;
	stwuct ieee80211_hw *hw = wtwdev->hw;

	whiwe (twue) {
		stwuct sk_buff *skb = skb_dequeue(&txcb->tx_ack_queue);
		stwuct ieee80211_tx_info *info;
		stwuct wtw_usb_tx_data *tx_data;

		if (!skb)
			bweak;

		info = IEEE80211_SKB_CB(skb);
		tx_data = wtw_usb_get_tx_data(skb);

		/* enqueue to wait fow tx wepowt */
		if (info->fwags & IEEE80211_TX_CTW_WEQ_TX_STATUS) {
			wtw_tx_wepowt_enqueue(wtwdev, skb, tx_data->sn);
			continue;
		}

		/* awways ACK fow othews, then they won't be mawked as dwop */
		ieee80211_tx_info_cweaw_status(info);
		if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
			info->fwags |= IEEE80211_TX_STAT_NOACK_TWANSMITTED;
		ewse
			info->fwags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_status_iwqsafe(hw, skb);
	}

	kfwee(txcb);
}

static int qsew_to_ep(stwuct wtw_usb *wtwusb, unsigned int qsew)
{
	if (qsew >= AWWAY_SIZE(wtwusb->qsew_to_ep))
		wetuwn -EINVAW;

	wetuwn wtwusb->qsew_to_ep[qsew];
}

static int wtw_usb_wwite_powt(stwuct wtw_dev *wtwdev, u8 qsew, stwuct sk_buff *skb,
			      usb_compwete_t cb, void *context)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	stwuct usb_device *usbd = wtwusb->udev;
	stwuct uwb *uwb;
	unsigned int pipe;
	int wet;
	int ep = qsew_to_ep(wtwusb, qsew);

	if (ep < 0)
		wetuwn ep;

	pipe = usb_sndbuwkpipe(usbd, wtwusb->out_ep[ep]);
	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		wetuwn -ENOMEM;

	usb_fiww_buwk_uwb(uwb, usbd, pipe, skb->data, skb->wen, cb, context);
	uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);

	usb_fwee_uwb(uwb);

	wetuwn wet;
}

static boow wtw_usb_tx_agg_skb(stwuct wtw_usb *wtwusb, stwuct sk_buff_head *wist)
{
	stwuct wtw_dev *wtwdev = wtwusb->wtwdev;
	stwuct wtw_tx_desc *tx_desc;
	stwuct wtw_usb_txcb *txcb;
	stwuct sk_buff *skb_head;
	stwuct sk_buff *skb_itew;
	int agg_num = 0;
	unsigned int awign_next = 0;
	u8 qsew;

	if (skb_queue_empty(wist))
		wetuwn fawse;

	txcb = kmawwoc(sizeof(*txcb), GFP_ATOMIC);
	if (!txcb)
		wetuwn fawse;

	txcb->wtwdev = wtwdev;
	skb_queue_head_init(&txcb->tx_ack_queue);

	skb_itew = skb_dequeue(wist);

	if (skb_queue_empty(wist)) {
		skb_head = skb_itew;
		goto queue;
	}

	skb_head = dev_awwoc_skb(WTW_USB_MAX_XMITBUF_SZ);
	if (!skb_head) {
		skb_head = skb_itew;
		goto queue;
	}

	whiwe (skb_itew) {
		unsigned wong fwags;

		skb_put(skb_head, awign_next);
		skb_put_data(skb_head, skb_itew->data, skb_itew->wen);

		awign_next = AWIGN(skb_itew->wen, 8) - skb_itew->wen;

		agg_num++;

		skb_queue_taiw(&txcb->tx_ack_queue, skb_itew);

		spin_wock_iwqsave(&wist->wock, fwags);

		skb_itew = skb_peek(wist);

		if (skb_itew && skb_itew->wen + skb_head->wen <= WTW_USB_MAX_XMITBUF_SZ)
			__skb_unwink(skb_itew, wist);
		ewse
			skb_itew = NUWW;
		spin_unwock_iwqwestowe(&wist->wock, fwags);
	}

	if (agg_num > 1)
		wtw_usb_fiww_tx_checksum(wtwusb, skb_head, agg_num);

queue:
	skb_queue_taiw(&txcb->tx_ack_queue, skb_head);
	tx_desc = (stwuct wtw_tx_desc *)skb_head->data;
	qsew = we32_get_bits(tx_desc->w1, WTW_TX_DESC_W1_QSEW);

	wtw_usb_wwite_powt(wtwdev, qsew, skb_head, wtw_usb_wwite_powt_tx_compwete, txcb);

	wetuwn twue;
}

static void wtw_usb_tx_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_usb *wtwusb = containew_of(wowk, stwuct wtw_usb, tx_wowk);
	int i, wimit;

	fow (i = AWWAY_SIZE(wtwusb->tx_queue) - 1; i >= 0; i--) {
		fow (wimit = 0; wimit < 200; wimit++) {
			stwuct sk_buff_head *wist = &wtwusb->tx_queue[i];

			if (!wtw_usb_tx_agg_skb(wtwusb, wist))
				bweak;
		}
	}
}

static void wtw_usb_tx_queue_puwge(stwuct wtw_usb *wtwusb)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wtwusb->tx_queue); i++)
		skb_queue_puwge(&wtwusb->tx_queue[i]);
}

static void wtw_usb_wwite_powt_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;

	dev_kfwee_skb_any(skb);
}

static int wtw_usb_wwite_data(stwuct wtw_dev *wtwdev,
			      stwuct wtw_tx_pkt_info *pkt_info,
			      u8 *buf)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct sk_buff *skb;
	unsigned int descwen, headsize, size;
	u8 qsew;
	int wet = 0;

	size = pkt_info->tx_pkt_size;
	qsew = pkt_info->qsew;
	descwen = chip->tx_pkt_desc_sz;
	headsize = pkt_info->offset ? pkt_info->offset : descwen;

	skb = dev_awwoc_skb(headsize + size);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	skb_wesewve(skb, headsize);
	skb_put_data(skb, buf, size);
	skb_push(skb, headsize);
	memset(skb->data, 0, headsize);
	wtw_tx_fiww_tx_desc(pkt_info, skb);
	wtw_tx_fiww_txdesc_checksum(wtwdev, pkt_info, skb->data);

	wet = wtw_usb_wwite_powt(wtwdev, qsew, skb,
				 wtw_usb_wwite_powt_compwete, skb);
	if (unwikewy(wet))
		wtw_eww(wtwdev, "faiwed to do USB wwite, wet=%d\n", wet);

	wetuwn wet;
}

static int wtw_usb_wwite_data_wsvd_page(stwuct wtw_dev *wtwdev, u8 *buf,
					u32 size)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_tx_pkt_info pkt_info = {0};

	pkt_info.tx_pkt_size = size;
	pkt_info.qsew = TX_DESC_QSEW_BEACON;
	pkt_info.offset = chip->tx_pkt_desc_sz;

	wetuwn wtw_usb_wwite_data(wtwdev, &pkt_info, buf);
}

static int wtw_usb_wwite_data_h2c(stwuct wtw_dev *wtwdev, u8 *buf, u32 size)
{
	stwuct wtw_tx_pkt_info pkt_info = {0};

	pkt_info.tx_pkt_size = size;
	pkt_info.qsew = TX_DESC_QSEW_H2C;

	wetuwn wtw_usb_wwite_data(wtwdev, &pkt_info, buf);
}

static u8 wtw_usb_tx_queue_mapping_to_qsew(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	__we16 fc = hdw->fwame_contwow;
	u8 qsew;

	if (unwikewy(ieee80211_is_mgmt(fc) || ieee80211_is_ctw(fc)))
		qsew = TX_DESC_QSEW_MGMT;
	ewse if (is_bwoadcast_ethew_addw(hdw->addw1) ||
		 is_muwticast_ethew_addw(hdw->addw1))
		qsew = TX_DESC_QSEW_HIGH;
	ewse if (skb_get_queue_mapping(skb) <= IEEE80211_AC_BK)
		qsew = skb->pwiowity;
	ewse
		qsew = TX_DESC_QSEW_BEACON;

	wetuwn qsew;
}

static int wtw_usb_tx_wwite(stwuct wtw_dev *wtwdev,
			    stwuct wtw_tx_pkt_info *pkt_info,
			    stwuct sk_buff *skb)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_usb_tx_data *tx_data;
	u8 *pkt_desc;
	int ep;

	pkt_info->qsew = wtw_usb_tx_queue_mapping_to_qsew(skb);
	pkt_desc = skb_push(skb, chip->tx_pkt_desc_sz);
	memset(pkt_desc, 0, chip->tx_pkt_desc_sz);
	ep = qsew_to_ep(wtwusb, pkt_info->qsew);
	wtw_tx_fiww_tx_desc(pkt_info, skb);
	wtw_tx_fiww_txdesc_checksum(wtwdev, pkt_info, skb->data);
	tx_data = wtw_usb_get_tx_data(skb);
	tx_data->sn = pkt_info->sn;

	skb_queue_taiw(&wtwusb->tx_queue[ep], skb);

	wetuwn 0;
}

static void wtw_usb_tx_kick_off(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);

	queue_wowk(wtwusb->txwq, &wtwusb->tx_wowk);
}

static void wtw_usb_wx_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_usb *wtwusb = containew_of(wowk, stwuct wtw_usb, wx_wowk);
	stwuct wtw_dev *wtwdev = wtwusb->wtwdev;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_wx_pkt_stat pkt_stat;
	stwuct ieee80211_wx_status wx_status;
	stwuct sk_buff *skb;
	u32 pkt_desc_sz = chip->wx_pkt_desc_sz;
	u32 pkt_offset;
	u8 *wx_desc;
	int wimit;

	fow (wimit = 0; wimit < 200; wimit++) {
		skb = skb_dequeue(&wtwusb->wx_queue);
		if (!skb)
			bweak;

		wx_desc = skb->data;
		chip->ops->quewy_wx_desc(wtwdev, wx_desc, &pkt_stat,
					 &wx_status);
		pkt_offset = pkt_desc_sz + pkt_stat.dwv_info_sz +
			     pkt_stat.shift;

		if (pkt_stat.is_c2h) {
			skb_put(skb, pkt_stat.pkt_wen + pkt_offset);
			wtw_fw_c2h_cmd_wx_iwqsafe(wtwdev, pkt_offset, skb);
			continue;
		}

		if (skb_queue_wen(&wtwusb->wx_queue) >= WTW_USB_MAX_WXQ_WEN) {
			dev_dbg_watewimited(wtwdev->dev, "faiwed to get wx_queue, ovewfwow\n");
			dev_kfwee_skb_any(skb);
			continue;
		}

		skb_put(skb, pkt_stat.pkt_wen);
		skb_wesewve(skb, pkt_offset);
		memcpy(skb->cb, &wx_status, sizeof(wx_status));
		ieee80211_wx_iwqsafe(wtwdev->hw, skb);
	}
}

static void wtw_usb_wead_powt_compwete(stwuct uwb *uwb);

static void wtw_usb_wx_wesubmit(stwuct wtw_usb *wtwusb, stwuct wx_usb_ctww_bwock *wxcb)
{
	stwuct wtw_dev *wtwdev = wtwusb->wtwdev;
	int ewwow;

	wxcb->wx_skb = awwoc_skb(WTW_USB_MAX_WECVBUF_SZ, GFP_ATOMIC);
	if (!wxcb->wx_skb)
		wetuwn;

	usb_fiww_buwk_uwb(wxcb->wx_uwb, wtwusb->udev,
			  usb_wcvbuwkpipe(wtwusb->udev, wtwusb->pipe_in),
			  wxcb->wx_skb->data, WTW_USB_MAX_WECVBUF_SZ,
			  wtw_usb_wead_powt_compwete, wxcb);

	ewwow = usb_submit_uwb(wxcb->wx_uwb, GFP_ATOMIC);
	if (ewwow) {
		kfwee_skb(wxcb->wx_skb);
		if (ewwow != -ENODEV)
			wtw_eww(wtwdev, "Eww sending wx data uwb %d\n",
				ewwow);
	}
}

static void wtw_usb_wead_powt_compwete(stwuct uwb *uwb)
{
	stwuct wx_usb_ctww_bwock *wxcb = uwb->context;
	stwuct wtw_dev *wtwdev = wxcb->wtwdev;
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	stwuct sk_buff *skb = wxcb->wx_skb;

	if (uwb->status == 0) {
		if (uwb->actuaw_wength >= WTW_USB_MAX_WECVBUF_SZ ||
		    uwb->actuaw_wength < 24) {
			wtw_eww(wtwdev, "faiwed to get uwb wength:%d\n",
				uwb->actuaw_wength);
			if (skb)
				dev_kfwee_skb_any(skb);
		} ewse {
			skb_queue_taiw(&wtwusb->wx_queue, skb);
			queue_wowk(wtwusb->wxwq, &wtwusb->wx_wowk);
		}
		wtw_usb_wx_wesubmit(wtwusb, wxcb);
	} ewse {
		switch (uwb->status) {
		case -EINVAW:
		case -EPIPE:
		case -ENODEV:
		case -ESHUTDOWN:
		case -ENOENT:
		case -EPWOTO:
		case -EIWSEQ:
		case -ETIME:
		case -ECOMM:
		case -EOVEWFWOW:
		case -EINPWOGWESS:
			bweak;
		defauwt:
			wtw_eww(wtwdev, "status %d\n", uwb->status);
			bweak;
		}
		if (skb)
			dev_kfwee_skb_any(skb);
	}
}

static void wtw_usb_cancew_wx_bufs(stwuct wtw_usb *wtwusb)
{
	stwuct wx_usb_ctww_bwock *wxcb;
	int i;

	fow (i = 0; i < WTW_USB_WXCB_NUM; i++) {
		wxcb = &wtwusb->wx_cb[i];
		usb_kiww_uwb(wxcb->wx_uwb);
	}
}

static void wtw_usb_fwee_wx_bufs(stwuct wtw_usb *wtwusb)
{
	stwuct wx_usb_ctww_bwock *wxcb;
	int i;

	fow (i = 0; i < WTW_USB_WXCB_NUM; i++) {
		wxcb = &wtwusb->wx_cb[i];
		usb_kiww_uwb(wxcb->wx_uwb);
		usb_fwee_uwb(wxcb->wx_uwb);
	}
}

static int wtw_usb_awwoc_wx_bufs(stwuct wtw_usb *wtwusb)
{
	int i;

	fow (i = 0; i < WTW_USB_WXCB_NUM; i++) {
		stwuct wx_usb_ctww_bwock *wxcb = &wtwusb->wx_cb[i];

		wxcb->wtwdev = wtwusb->wtwdev;
		wxcb->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!wxcb->wx_uwb)
			goto eww;
	}

	wetuwn 0;
eww:
	wtw_usb_fwee_wx_bufs(wtwusb);
	wetuwn -ENOMEM;
}

static int wtw_usb_setup(stwuct wtw_dev *wtwdev)
{
	/* empty function fow wtw_hci_ops */
	wetuwn 0;
}

static int wtw_usb_stawt(stwuct wtw_dev *wtwdev)
{
	wetuwn 0;
}

static void wtw_usb_stop(stwuct wtw_dev *wtwdev)
{
}

static void wtw_usb_deep_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	/* empty function fow wtw_hci_ops */
}

static void wtw_usb_wink_ps(stwuct wtw_dev *wtwdev, boow entew)
{
	/* empty function fow wtw_hci_ops */
}

static void wtw_usb_intewface_cfg(stwuct wtw_dev *wtwdev)
{
	/* empty function fow wtw_hci_ops */
}

static stwuct wtw_hci_ops wtw_usb_ops = {
	.tx_wwite = wtw_usb_tx_wwite,
	.tx_kick_off = wtw_usb_tx_kick_off,
	.setup = wtw_usb_setup,
	.stawt = wtw_usb_stawt,
	.stop = wtw_usb_stop,
	.deep_ps = wtw_usb_deep_ps,
	.wink_ps = wtw_usb_wink_ps,
	.intewface_cfg = wtw_usb_intewface_cfg,

	.wwite8  = wtw_usb_wwite8,
	.wwite16 = wtw_usb_wwite16,
	.wwite32 = wtw_usb_wwite32,
	.wead8	= wtw_usb_wead8,
	.wead16 = wtw_usb_wead16,
	.wead32 = wtw_usb_wead32,

	.wwite_data_wsvd_page = wtw_usb_wwite_data_wsvd_page,
	.wwite_data_h2c = wtw_usb_wwite_data_h2c,
};

static int wtw_usb_init_wx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	int i;

	wtwusb->wxwq = cweate_singwethwead_wowkqueue("wtw88_usb: wx wq");
	if (!wtwusb->wxwq) {
		wtw_eww(wtwdev, "faiwed to cweate WX wowk queue\n");
		wetuwn -ENOMEM;
	}

	skb_queue_head_init(&wtwusb->wx_queue);

	INIT_WOWK(&wtwusb->wx_wowk, wtw_usb_wx_handwew);

	fow (i = 0; i < WTW_USB_WXCB_NUM; i++) {
		stwuct wx_usb_ctww_bwock *wxcb = &wtwusb->wx_cb[i];

		wtw_usb_wx_wesubmit(wtwusb, wxcb);
	}

	wetuwn 0;
}

static void wtw_usb_deinit_wx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);

	skb_queue_puwge(&wtwusb->wx_queue);

	fwush_wowkqueue(wtwusb->wxwq);
	destwoy_wowkqueue(wtwusb->wxwq);
}

static int wtw_usb_init_tx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	int i;

	wtwusb->txwq = cweate_singwethwead_wowkqueue("wtw88_usb: tx wq");
	if (!wtwusb->txwq) {
		wtw_eww(wtwdev, "faiwed to cweate TX wowk queue\n");
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < AWWAY_SIZE(wtwusb->tx_queue); i++)
		skb_queue_head_init(&wtwusb->tx_queue[i]);

	INIT_WOWK(&wtwusb->tx_wowk, wtw_usb_tx_handwew);

	wetuwn 0;
}

static void wtw_usb_deinit_tx(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);

	wtw_usb_tx_queue_puwge(wtwusb);
	fwush_wowkqueue(wtwusb->txwq);
	destwoy_wowkqueue(wtwusb->txwq);
}

static int wtw_usb_intf_init(stwuct wtw_dev *wtwdev,
			     stwuct usb_intewface *intf)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);
	stwuct usb_device *udev = usb_get_dev(intewface_to_usbdev(intf));
	int wet;

	wtwusb->udev = udev;
	wet = wtw_usb_pawse(wtwdev, intf);
	if (wet)
		wetuwn wet;

	wtwusb->usb_data = kcawwoc(WTW_USB_MAX_WXTX_COUNT, sizeof(u32),
				   GFP_KEWNEW);
	if (!wtwusb->usb_data)
		wetuwn -ENOMEM;

	usb_set_intfdata(intf, wtwdev->hw);

	SET_IEEE80211_DEV(wtwdev->hw, &intf->dev);
	spin_wock_init(&wtwusb->usb_wock);

	wetuwn 0;
}

static void wtw_usb_intf_deinit(stwuct wtw_dev *wtwdev,
				stwuct usb_intewface *intf)
{
	stwuct wtw_usb *wtwusb = wtw_get_usb_pwiv(wtwdev);

	usb_put_dev(wtwusb->udev);
	kfwee(wtwusb->usb_data);
	usb_set_intfdata(intf, NUWW);
}

int wtw_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	stwuct wtw_dev *wtwdev;
	stwuct ieee80211_hw *hw;
	stwuct wtw_usb *wtwusb;
	int dwv_data_size;
	int wet;

	dwv_data_size = sizeof(stwuct wtw_dev) + sizeof(stwuct wtw_usb);
	hw = ieee80211_awwoc_hw(dwv_data_size, &wtw_ops);
	if (!hw)
		wetuwn -ENOMEM;

	wtwdev = hw->pwiv;
	wtwdev->hw = hw;
	wtwdev->dev = &intf->dev;
	wtwdev->chip = (stwuct wtw_chip_info *)id->dwivew_info;
	wtwdev->hci.ops = &wtw_usb_ops;
	wtwdev->hci.type = WTW_HCI_TYPE_USB;

	wtwusb = wtw_get_usb_pwiv(wtwdev);
	wtwusb->wtwdev = wtwdev;

	wet = wtw_usb_awwoc_wx_bufs(wtwusb);
	if (wet)
		goto eww_wewease_hw;

	wet = wtw_cowe_init(wtwdev);
	if (wet)
		goto eww_fwee_wx_bufs;

	wet = wtw_usb_intf_init(wtwdev, intf);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to init USB intewface\n");
		goto eww_deinit_cowe;
	}

	wet = wtw_usb_init_tx(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to init USB TX\n");
		goto eww_destwoy_usb;
	}

	wet = wtw_usb_init_wx(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to init USB WX\n");
		goto eww_destwoy_txwq;
	}

	wet = wtw_chip_info_setup(wtwdev);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to setup chip infowmation\n");
		goto eww_destwoy_wxwq;
	}

	wet = wtw_wegistew_hw(wtwdev, wtwdev->hw);
	if (wet) {
		wtw_eww(wtwdev, "faiwed to wegistew hw\n");
		goto eww_destwoy_wxwq;
	}

	wetuwn 0;

eww_destwoy_wxwq:
	wtw_usb_deinit_wx(wtwdev);

eww_destwoy_txwq:
	wtw_usb_deinit_tx(wtwdev);

eww_destwoy_usb:
	wtw_usb_intf_deinit(wtwdev, intf);

eww_deinit_cowe:
	wtw_cowe_deinit(wtwdev);

eww_fwee_wx_bufs:
	wtw_usb_fwee_wx_bufs(wtwusb);

eww_wewease_hw:
	ieee80211_fwee_hw(hw);

	wetuwn wet;
}
EXPOWT_SYMBOW(wtw_usb_pwobe);

void wtw_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct wtw_dev *wtwdev;
	stwuct wtw_usb *wtwusb;

	if (!hw)
		wetuwn;

	wtwdev = hw->pwiv;
	wtwusb = wtw_get_usb_pwiv(wtwdev);

	wtw_usb_cancew_wx_bufs(wtwusb);

	wtw_unwegistew_hw(wtwdev, hw);
	wtw_usb_deinit_tx(wtwdev);
	wtw_usb_deinit_wx(wtwdev);

	if (wtwusb->udev->state != USB_STATE_NOTATTACHED)
		usb_weset_device(wtwusb->udev);

	wtw_usb_fwee_wx_bufs(wtwusb);

	wtw_usb_intf_deinit(wtwdev, intf);
	wtw_cowe_deinit(wtwdev);
	ieee80211_fwee_hw(hw);
}
EXPOWT_SYMBOW(wtw_usb_disconnect);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek USB 802.11ac wiwewess dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
