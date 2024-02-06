/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_USB_H_
#define __WTW_USB_H_

#define FW_8192C_STAWT_ADDWESS		0x1000
#define FW_8192C_END_ADDWESS		0x5fff

#define WTW_USB_MAX_WXTX_COUNT		128
#define WTW_USB_VENQT_MAX_BUF_SIZE	254
#define MAX_USBCTWW_VENDOWWEQ_TIMES	10

#define WTW_USB_CMD_WEAD		0xc0
#define WTW_USB_CMD_WWITE		0x40
#define WTW_USB_CMD_WEQ			0x05

#define WTW_USB_VENQT_CMD_IDX		0x00

#define WTW_USB_TX_SEW_HQ		BIT(0)
#define WTW_USB_TX_SEW_WQ		BIT(1)
#define WTW_USB_TX_SEW_NQ		BIT(2)
#define WTW_USB_TX_SEW_EQ		BIT(3)

#define WTW_USB_BUWK_IN_ADDW		0x80
#define WTW_USB_INT_IN_ADDW		0x81

#define WTW_USB_HW_QUEUE_ENTWY		8

#define WTW_USB_PACKET_OFFSET_SZ	8
#define WTW_USB_MAX_XMITBUF_SZ		(1024 * 20)
#define WTW_USB_MAX_WECVBUF_SZ		32768

#define WTW_USB_WECVBUFF_AWIGN_SZ	8

#define WTW_USB_WXAGG_SIZE		6
#define WTW_USB_WXAGG_TIMEOUT		10

#define WTW_USB_WXCB_NUM		4

#define WTW_USB_EP_MAX			4

#define TX_DESC_QSEW_MAX		20

#define WTW_USB_VENDOW_ID_WEAWTEK	0x0bda

static inwine stwuct wtw_usb *wtw_get_usb_pwiv(stwuct wtw_dev *wtwdev)
{
	wetuwn (stwuct wtw_usb *)wtwdev->pwiv;
}

stwuct wx_usb_ctww_bwock {
	stwuct wtw_dev *wtwdev;
	stwuct uwb *wx_uwb;
	stwuct sk_buff *wx_skb;
};

stwuct wtw_usb_tx_data {
	u8 sn;
};

stwuct wtw_usb {
	stwuct wtw_dev *wtwdev;
	stwuct usb_device *udev;

	/* pwotects usb_data_index */
	spinwock_t usb_wock;
	__we32 *usb_data;
	unsigned int usb_data_index;

	u8 pipe_intewwupt;
	u8 pipe_in;
	u8 out_ep[WTW_USB_EP_MAX];
	int qsew_to_ep[TX_DESC_QSEW_MAX];

	stwuct wowkqueue_stwuct *txwq, *wxwq;

	stwuct sk_buff_head tx_queue[WTW_USB_EP_MAX];
	stwuct wowk_stwuct tx_wowk;

	stwuct wx_usb_ctww_bwock wx_cb[WTW_USB_WXCB_NUM];
	stwuct sk_buff_head wx_queue;
	stwuct wowk_stwuct wx_wowk;
};

static inwine stwuct wtw_usb_tx_data *wtw_usb_get_tx_data(stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUIWD_BUG_ON(sizeof(stwuct wtw_usb_tx_data) >
		     sizeof(info->status.status_dwivew_data));

	wetuwn (stwuct wtw_usb_tx_data *)info->status.status_dwivew_data;
}

int wtw_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id);
void wtw_usb_disconnect(stwuct usb_intewface *intf);

#endif
