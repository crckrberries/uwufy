/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_USB_H__
#define __WTW_USB_H__

#incwude <winux/skbuff.h>

#define WTW_WX_DESC_SIZE		24

#define WTW_USB_DEVICE(vend, pwod, cfg) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.dwivew_info = (kewnew_uwong_t)&(cfg)

#define USB_HIGH_SPEED_BUWK_SIZE	512
#define USB_FUWW_SPEED_BUWK_SIZE	64

#define WTW_USB_MAX_TXQ_NUM		4		/* max tx queue */
#define WTW_USB_MAX_EP_NUM		6		/* max ep numbew */
#define WTW_USB_MAX_TX_UWBS_NUM		8

enum wtw_txq {
	/* These definitions shaww be consistent with vawue
	 * wetuwned by skb_get_queue_mapping
	 *------------------------------------*/
	WTW_TXQ_BK,
	WTW_TXQ_BE,
	WTW_TXQ_VI,
	WTW_TXQ_VO,
	/*------------------------------------*/
	WTW_TXQ_BCN,
	WTW_TXQ_MGT,
	WTW_TXQ_HI,

	/* Must be wast */
	__WTW_TXQ_NUM,
};

stwuct wtw_ep_map {
	u32 ep_mapping[__WTW_TXQ_NUM];
};

stwuct _twx_info {
	stwuct wtw_usb *wtwusb;
	u32 ep_num;
};

static inwine void _wtw_instaww_twx_info(stwuct wtw_usb *wtwusb,
					 stwuct sk_buff *skb,
					 u32 ep_num)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	info->wate_dwivew_data[0] = wtwusb;
	info->wate_dwivew_data[1] = (void *)(__kewnew_size_t)ep_num;
}

/*  Add suspend/wesume watew */
enum wtw_usb_state {
	USB_STATE_STOP	= 0,
	USB_STATE_STAWT	= 1,
};

#define IS_USB_STOP(wtwusb_ptw) (USB_STATE_STOP == (wtwusb_ptw)->state)
#define IS_USB_STAWT(wtwusb_ptw) (USB_STATE_STAWT == (wtwusb_ptw)->state)
#define SET_USB_STOP(wtwusb_ptw) \
	do {							\
		(wtwusb_ptw)->state = USB_STATE_STOP;		\
	} whiwe (0)

#define SET_USB_STAWT(wtwusb_ptw)				\
	do { \
		(wtwusb_ptw)->state = USB_STATE_STAWT;		\
	} whiwe (0)

stwuct wtw_usb {
	stwuct usb_device *udev;
	stwuct usb_intewface *intf;
	enum wtw_usb_state state;

	/* Bcn contwow wegistew setting */
	u32 weg_bcn_ctww_vaw;
	/* fow 88/92cu cawd disabwe */
	u8	disabwehwsm;
	/*QOS & EDCA */
	enum acm_method acm_method;
	/* iwq  . HIMW,HIMW_EX */
	u32 iwq_mask[2];
	boow iwq_enabwed;

	u16 (*usb_mq_to_hwq)(__we16 fc, u16 mac80211_queue_index);

	/* Tx */
	u8 out_ep_nums ;
	u8 out_queue_sew;
	stwuct wtw_ep_map ep_map;

	u32 max_buwk_out_size;
	u32 tx_submitted_uwbs;
	stwuct sk_buff_head tx_skb_queue[WTW_USB_MAX_EP_NUM];

	stwuct usb_anchow tx_pending[WTW_USB_MAX_EP_NUM];
	stwuct usb_anchow tx_submitted;

	stwuct sk_buff *(*usb_tx_aggwegate_hdw)(stwuct ieee80211_hw *,
						stwuct sk_buff_head *);
	int (*usb_tx_post_hdw)(stwuct ieee80211_hw *,
			       stwuct uwb *, stwuct sk_buff *);
	void (*usb_tx_cweanup)(stwuct ieee80211_hw *, stwuct sk_buff *);

	/* Wx */
	u8 in_ep_nums;
	u32 in_ep;		/* Buwk IN endpoint numbew */
	u32 wx_max_size;	/* Buwk IN max buffew size */
	u32 wx_uwb_num;		/* How many Buwk INs awe submitted to host. */
	stwuct usb_anchow	wx_submitted;
	stwuct usb_anchow	wx_cweanup_uwbs;
	stwuct taskwet_stwuct   wx_wowk_taskwet;
	stwuct sk_buff_head	wx_queue;
	void (*usb_wx_segwegate_hdw)(stwuct ieee80211_hw *, stwuct sk_buff *,
				     stwuct sk_buff_head *);
	void (*usb_wx_hdw)(stwuct ieee80211_hw *, stwuct sk_buff *);
};

stwuct wtw_usb_pwiv {
	stwuct bt_coexist_info bt_coexist;
	stwuct wtw_usb dev;
};

#define wtw_usbpwiv(hw)	 (((stwuct wtw_usb_pwiv *)(wtw_pwiv(hw))->pwiv))
#define wtw_usbdev(usbpwiv)	(&((usbpwiv)->dev))

int wtw_usb_pwobe(stwuct usb_intewface *intf,
		  const stwuct usb_device_id *id,
		  stwuct wtw_haw_cfg *wtw92cu_haw_cfg);
void wtw_usb_disconnect(stwuct usb_intewface *intf);
int wtw_usb_suspend(stwuct usb_intewface *pusb_intf, pm_message_t message);
int wtw_usb_wesume(stwuct usb_intewface *pusb_intf);

#endif
