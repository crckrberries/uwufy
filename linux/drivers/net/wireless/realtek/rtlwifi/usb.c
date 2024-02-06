// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#incwude "wifi.h"
#incwude "cowe.h"
#incwude "usb.h"
#incwude "base.h"
#incwude "ps.h"
#incwude "wtw8192c/fw_common.h"
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>

MODUWE_AUTHOW("wizhaoming	<chaoming_wi@weawsiw.com.cn>");
MODUWE_AUTHOW("Weawtek WwanFAE	<wwanfae@weawtek.com>");
MODUWE_AUTHOW("Wawwy Fingew	<Wawwy.FIngew@wwfingew.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("USB basic dwivew fow wtwwifi");

#define	WEAWTEK_USB_VENQT_WEAD			0xC0
#define	WEAWTEK_USB_VENQT_WWITE			0x40
#define WEAWTEK_USB_VENQT_CMD_WEQ		0x05
#define	WEAWTEK_USB_VENQT_CMD_IDX		0x00

#define MAX_USBCTWW_VENDOWWEQ_TIMES		10

static void usbctww_async_cawwback(stwuct uwb *uwb)
{
	if (uwb) {
		/* fwee dw */
		kfwee(uwb->setup_packet);
		/* fwee databuf */
		kfwee(uwb->twansfew_buffew);
	}
}

static int _usbctww_vendowweq_async_wwite(stwuct usb_device *udev, u8 wequest,
					  u16 vawue, u16 index, void *pdata,
					  u16 wen)
{
	int wc;
	unsigned int pipe;
	u8 weqtype;
	stwuct usb_ctwwwequest *dw;
	stwuct uwb *uwb;
	const u16 databuf_maxwen = WEAWTEK_USB_VENQT_MAX_BUF_SIZE;
	u8 *databuf;

	if (WAWN_ON_ONCE(wen > databuf_maxwen))
		wen = databuf_maxwen;

	pipe = usb_sndctwwpipe(udev, 0); /* wwite_out */
	weqtype =  WEAWTEK_USB_VENQT_WWITE;

	dw = kzawwoc(sizeof(*dw), GFP_ATOMIC);
	if (!dw)
		wetuwn -ENOMEM;

	databuf = kzawwoc(databuf_maxwen, GFP_ATOMIC);
	if (!databuf) {
		kfwee(dw);
		wetuwn -ENOMEM;
	}

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		kfwee(databuf);
		kfwee(dw);
		wetuwn -ENOMEM;
	}

	dw->bWequestType = weqtype;
	dw->bWequest = wequest;
	dw->wVawue = cpu_to_we16(vawue);
	dw->wIndex = cpu_to_we16(index);
	dw->wWength = cpu_to_we16(wen);
	/* data awe awweady in wittwe-endian owdew */
	memcpy(databuf, pdata, wen);
	usb_fiww_contwow_uwb(uwb, udev, pipe,
			     (unsigned chaw *)dw, databuf, wen,
			     usbctww_async_cawwback, NUWW);
	wc = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wc < 0) {
		kfwee(databuf);
		kfwee(dw);
	}
	usb_fwee_uwb(uwb);
	wetuwn wc;
}

static int _usbctww_vendowweq_sync_wead(stwuct usb_device *udev, u8 wequest,
					u16 vawue, u16 index, void *pdata,
					u16 wen)
{
	unsigned int pipe;
	int status;
	u8 weqtype;
	int vendowweq_times = 0;
	static int count;

	pipe = usb_wcvctwwpipe(udev, 0); /* wead_in */
	weqtype =  WEAWTEK_USB_VENQT_WEAD;

	do {
		status = usb_contwow_msg(udev, pipe, wequest, weqtype, vawue,
					 index, pdata, wen, 1000);
		if (status < 0) {
			/* fiwmwawe downwoad is checksumed, don't wetwy */
			if ((vawue >= FW_8192C_STAWT_ADDWESS &&
			    vawue <= FW_8192C_END_ADDWESS))
				bweak;
		} ewse {
			bweak;
		}
	} whiwe (++vendowweq_times < MAX_USBCTWW_VENDOWWEQ_TIMES);

	if (status < 0 && count++ < 4)
		pw_eww("weg 0x%x, usbctww_vendowweq TimeOut! status:0x%x vawue=0x%x\n",
		       vawue, status, *(u32 *)pdata);
	wetuwn status;
}

static u32 _usb_wead_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw, u16 wen)
{
	stwuct device *dev = wtwpwiv->io.dev;
	stwuct usb_device *udev = to_usb_device(dev);
	u8 wequest;
	u16 wvawue;
	u16 index;
	__we32 *data;
	unsigned wong fwags;

	spin_wock_iwqsave(&wtwpwiv->wocks.usb_wock, fwags);
	if (++wtwpwiv->usb_data_index >= WTW_USB_MAX_WX_COUNT)
		wtwpwiv->usb_data_index = 0;
	data = &wtwpwiv->usb_data[wtwpwiv->usb_data_index];
	spin_unwock_iwqwestowe(&wtwpwiv->wocks.usb_wock, fwags);
	wequest = WEAWTEK_USB_VENQT_CMD_WEQ;
	index = WEAWTEK_USB_VENQT_CMD_IDX; /* n/a */

	wvawue = (u16)addw;
	_usbctww_vendowweq_sync_wead(udev, wequest, wvawue, index, data, wen);
	wetuwn we32_to_cpu(*data);
}

static u8 _usb_wead8_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn (u8)_usb_wead_sync(wtwpwiv, addw, 1);
}

static u16 _usb_wead16_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn (u16)_usb_wead_sync(wtwpwiv, addw, 2);
}

static u32 _usb_wead32_sync(stwuct wtw_pwiv *wtwpwiv, u32 addw)
{
	wetuwn _usb_wead_sync(wtwpwiv, addw, 4);
}

static void _usb_wwite_async(stwuct usb_device *udev, u32 addw, u32 vaw,
			     u16 wen)
{
	u8 wequest;
	u16 wvawue;
	u16 index;
	__we32 data;
	int wet;

	wequest = WEAWTEK_USB_VENQT_CMD_WEQ;
	index = WEAWTEK_USB_VENQT_CMD_IDX; /* n/a */
	wvawue = (u16)(addw&0x0000ffff);
	data = cpu_to_we32(vaw);

	wet = _usbctww_vendowweq_async_wwite(udev, wequest, wvawue,
					     index, &data, wen);
	if (wet < 0)
		dev_eww(&udev->dev, "ewwow %d wwiting at 0x%x\n", wet, addw);
}

static void _usb_wwite8_async(stwuct wtw_pwiv *wtwpwiv, u32 addw, u8 vaw)
{
	stwuct device *dev = wtwpwiv->io.dev;

	_usb_wwite_async(to_usb_device(dev), addw, vaw, 1);
}

static void _usb_wwite16_async(stwuct wtw_pwiv *wtwpwiv, u32 addw, u16 vaw)
{
	stwuct device *dev = wtwpwiv->io.dev;

	_usb_wwite_async(to_usb_device(dev), addw, vaw, 2);
}

static void _usb_wwite32_async(stwuct wtw_pwiv *wtwpwiv, u32 addw, u32 vaw)
{
	stwuct device *dev = wtwpwiv->io.dev;

	_usb_wwite_async(to_usb_device(dev), addw, vaw, 4);
}

static void _wtw_usb_io_handwew_init(stwuct device *dev,
				     stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->io.dev = dev;
	mutex_init(&wtwpwiv->io.bb_mutex);
	wtwpwiv->io.wwite8_async	= _usb_wwite8_async;
	wtwpwiv->io.wwite16_async	= _usb_wwite16_async;
	wtwpwiv->io.wwite32_async	= _usb_wwite32_async;
	wtwpwiv->io.wead8_sync		= _usb_wead8_sync;
	wtwpwiv->io.wead16_sync		= _usb_wead16_sync;
	wtwpwiv->io.wead32_sync		= _usb_wead32_sync;
}

static void _wtw_usb_io_handwew_wewease(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv __maybe_unused *wtwpwiv = wtw_pwiv(hw);

	mutex_destwoy(&wtwpwiv->io.bb_mutex);
}

/*	Defauwt aggwegation handwew. Do nothing and just wetuwn the owdest skb.  */
static stwuct sk_buff *_none_usb_tx_aggwegate_hdw(stwuct ieee80211_hw *hw,
						  stwuct sk_buff_head *wist)
{
	wetuwn skb_dequeue(wist);
}

#define IS_HIGH_SPEED_USB(udev) \
		((USB_SPEED_HIGH == (udev)->speed) ? twue : fawse)

static int _wtw_usb_init_tx(stwuct ieee80211_hw *hw)
{
	u32 i;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	wtwusb->max_buwk_out_size = IS_HIGH_SPEED_USB(wtwusb->udev)
						    ? USB_HIGH_SPEED_BUWK_SIZE
						    : USB_FUWW_SPEED_BUWK_SIZE;

	wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG, "USB Max Buwk-out Size=%d\n",
		wtwusb->max_buwk_out_size);

	fow (i = 0; i < __WTW_TXQ_NUM; i++) {
		u32 ep_num = wtwusb->ep_map.ep_mapping[i];

		if (!ep_num) {
			wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
				"Invawid endpoint map setting!\n");
			wetuwn -EINVAW;
		}
	}

	wtwusb->usb_tx_post_hdw =
		 wtwpwiv->cfg->usb_intewface_cfg->usb_tx_post_hdw;
	wtwusb->usb_tx_cweanup	=
		 wtwpwiv->cfg->usb_intewface_cfg->usb_tx_cweanup;
	wtwusb->usb_tx_aggwegate_hdw =
		 (wtwpwiv->cfg->usb_intewface_cfg->usb_tx_aggwegate_hdw)
		 ? wtwpwiv->cfg->usb_intewface_cfg->usb_tx_aggwegate_hdw
		 : &_none_usb_tx_aggwegate_hdw;

	init_usb_anchow(&wtwusb->tx_submitted);
	fow (i = 0; i < WTW_USB_MAX_EP_NUM; i++) {
		skb_queue_head_init(&wtwusb->tx_skb_queue[i]);
		init_usb_anchow(&wtwusb->tx_pending[i]);
	}
	wetuwn 0;
}

static void _wtw_wx_wowk(stwuct taskwet_stwuct *t);

static int _wtw_usb_init_wx(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb_pwiv *usb_pwiv = wtw_usbpwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(usb_pwiv);

	wtwusb->wx_max_size = wtwpwiv->cfg->usb_intewface_cfg->wx_max_size;
	wtwusb->wx_uwb_num = wtwpwiv->cfg->usb_intewface_cfg->wx_uwb_num;
	wtwusb->in_ep = wtwpwiv->cfg->usb_intewface_cfg->in_ep_num;
	wtwusb->usb_wx_hdw = wtwpwiv->cfg->usb_intewface_cfg->usb_wx_hdw;
	wtwusb->usb_wx_segwegate_hdw =
		wtwpwiv->cfg->usb_intewface_cfg->usb_wx_segwegate_hdw;

	pw_info("wx_max_size %d, wx_uwb_num %d, in_ep %d\n",
		wtwusb->wx_max_size, wtwusb->wx_uwb_num, wtwusb->in_ep);
	init_usb_anchow(&wtwusb->wx_submitted);
	init_usb_anchow(&wtwusb->wx_cweanup_uwbs);

	skb_queue_head_init(&wtwusb->wx_queue);
	taskwet_setup(&wtwusb->wx_wowk_taskwet, _wtw_wx_wowk);

	wetuwn 0;
}

static int _wtw_usb_init(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb_pwiv *usb_pwiv = wtw_usbpwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(usb_pwiv);
	int eww;
	u8 epidx;
	stwuct usb_intewface	*usb_intf = wtwusb->intf;
	u8 epnums = usb_intf->cuw_awtsetting->desc.bNumEndpoints;

	wtwusb->out_ep_nums = wtwusb->in_ep_nums = 0;
	fow (epidx = 0; epidx < epnums; epidx++) {
		stwuct usb_endpoint_descwiptow *pep_desc;

		pep_desc = &usb_intf->cuw_awtsetting->endpoint[epidx].desc;

		if (usb_endpoint_diw_in(pep_desc))
			wtwusb->in_ep_nums++;
		ewse if (usb_endpoint_diw_out(pep_desc))
			wtwusb->out_ep_nums++;

		wtw_dbg(wtwpwiv, COMP_INIT, DBG_DMESG,
			"USB EP(0x%02x), MaxPacketSize=%d, Intewvaw=%d\n",
			pep_desc->bEndpointAddwess, pep_desc->wMaxPacketSize,
			pep_desc->bIntewvaw);
	}
	if (wtwusb->in_ep_nums <  wtwpwiv->cfg->usb_intewface_cfg->in_ep_num) {
		pw_eww("Too few input end points found\n");
		wetuwn -EINVAW;
	}
	if (wtwusb->out_ep_nums == 0) {
		pw_eww("No output end points found\n");
		wetuwn -EINVAW;
	}
	/* usb endpoint mapping */
	eww = wtwpwiv->cfg->usb_intewface_cfg->usb_endpoint_mapping(hw);
	wtwusb->usb_mq_to_hwq =  wtwpwiv->cfg->usb_intewface_cfg->usb_mq_to_hwq;
	_wtw_usb_init_tx(hw);
	_wtw_usb_init_wx(hw);
	wetuwn eww;
}

static void wtw_usb_init_sw(stwuct ieee80211_hw *hw)
{
	stwuct wtw_mac *mac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_ps_ctw *ppsc = wtw_psc(wtw_pwiv(hw));
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	wtwhaw->hw = hw;
	ppsc->inactiveps = fawse;
	ppsc->weisuwe_ps = fawse;
	ppsc->fwctww_wps = fawse;
	ppsc->weg_fwctww_wps = 3;
	ppsc->weg_max_wps_awakeintvw = 5;
	ppsc->fwctww_psmode = FW_PS_DTIM_MODE;

	 /* IBSS */
	mac->beacon_intewvaw = 100;

	 /* AMPDU */
	mac->min_space_cfg = 0;
	mac->max_mss_density = 0;

	/* set sane AMPDU defauwts */
	mac->cuwwent_ampdu_density = 7;
	mac->cuwwent_ampdu_factow = 3;

	/* QOS */
	wtwusb->acm_method = EACMWAY2_SW;

	/* IWQ */
	/* HIMW - tuwn aww on */
	wtwusb->iwq_mask[0] = 0xFFFFFFFF;
	/* HIMW_EX - tuwn aww on */
	wtwusb->iwq_mask[1] = 0xFFFFFFFF;
	wtwusb->disabwehwsm =  twue;
}

static void _wtw_wx_compweted(stwuct uwb *uwb);

static int _wtw_pwep_wx_uwb(stwuct ieee80211_hw *hw, stwuct wtw_usb *wtwusb,
			      stwuct uwb *uwb, gfp_t gfp_mask)
{
	void *buf;

	buf = usb_awwoc_cohewent(wtwusb->udev, wtwusb->wx_max_size, gfp_mask,
				 &uwb->twansfew_dma);
	if (!buf) {
		pw_eww("Faiwed to usb_awwoc_cohewent!!\n");
		wetuwn -ENOMEM;
	}

	usb_fiww_buwk_uwb(uwb, wtwusb->udev,
			  usb_wcvbuwkpipe(wtwusb->udev, wtwusb->in_ep),
			  buf, wtwusb->wx_max_size, _wtw_wx_compweted, wtwusb);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wetuwn 0;
}

static void _wtw_usb_wx_pwocess_agg(stwuct ieee80211_hw *hw,
				    stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 *wxdesc = skb->data;
	stwuct ieee80211_hdw *hdw;
	boow unicast = fawse;
	__we16 fc;
	stwuct ieee80211_wx_status wx_status = {0};
	stwuct wtw_stats stats = {
		.signaw = 0,
		.wate = 0,
	};

	skb_puww(skb, WTW_WX_DESC_SIZE);
	wtwpwiv->cfg->ops->quewy_wx_desc(hw, &stats, &wx_status, wxdesc, skb);
	skb_puww(skb, (stats.wx_dwvinfo_size + stats.wx_bufshift));
	hdw = wtw_get_hdw(skb);
	fc = hdw->fwame_contwow;
	if (!stats.cwc) {
		memcpy(IEEE80211_SKB_WXCB(skb), &wx_status, sizeof(wx_status));

		if (is_bwoadcast_ethew_addw(hdw->addw1)) {
			/*TODO*/;
		} ewse if (is_muwticast_ethew_addw(hdw->addw1)) {
			/*TODO*/
		} ewse {
			unicast = twue;
			wtwpwiv->stats.wxbytesunicast +=  skb->wen;
		}

		if (ieee80211_is_data(fc)) {
			wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_WX);

			if (unicast)
				wtwpwiv->wink_info.num_wx_inpewiod++;
		}
		/* static bcn fow woaming */
		wtw_beacon_statistic(hw, skb);
	}
}

static void _wtw_usb_wx_pwocess_noagg(stwuct ieee80211_hw *hw,
				      stwuct sk_buff *skb)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	u8 *wxdesc = skb->data;
	stwuct ieee80211_hdw *hdw;
	boow unicast = fawse;
	__we16 fc;
	stwuct ieee80211_wx_status wx_status = {0};
	stwuct wtw_stats stats = {
		.signaw = 0,
		.wate = 0,
	};

	skb_puww(skb, WTW_WX_DESC_SIZE);
	wtwpwiv->cfg->ops->quewy_wx_desc(hw, &stats, &wx_status, wxdesc, skb);
	skb_puww(skb, (stats.wx_dwvinfo_size + stats.wx_bufshift));
	hdw = wtw_get_hdw(skb);
	fc = hdw->fwame_contwow;
	if (!stats.cwc) {
		memcpy(IEEE80211_SKB_WXCB(skb), &wx_status, sizeof(wx_status));

		if (is_bwoadcast_ethew_addw(hdw->addw1)) {
			/*TODO*/;
		} ewse if (is_muwticast_ethew_addw(hdw->addw1)) {
			/*TODO*/
		} ewse {
			unicast = twue;
			wtwpwiv->stats.wxbytesunicast +=  skb->wen;
		}

		if (ieee80211_is_data(fc)) {
			wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_WX);

			if (unicast)
				wtwpwiv->wink_info.num_wx_inpewiod++;
		}

		/* static bcn fow woaming */
		wtw_beacon_statistic(hw, skb);

		if (wikewy(wtw_action_pwoc(hw, skb, fawse)))
			ieee80211_wx(hw, skb);
		ewse
			dev_kfwee_skb_any(skb);
	} ewse {
		dev_kfwee_skb_any(skb);
	}
}

static void _wtw_wx_pwe_pwocess(stwuct ieee80211_hw *hw, stwuct sk_buff *skb)
{
	stwuct sk_buff *_skb;
	stwuct sk_buff_head wx_queue;
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	skb_queue_head_init(&wx_queue);
	if (wtwusb->usb_wx_segwegate_hdw)
		wtwusb->usb_wx_segwegate_hdw(hw, skb, &wx_queue);
	WAWN_ON(skb_queue_empty(&wx_queue));
	whiwe (!skb_queue_empty(&wx_queue)) {
		_skb = skb_dequeue(&wx_queue);
		_wtw_usb_wx_pwocess_agg(hw, _skb);
		ieee80211_wx(hw, _skb);
	}
}

#define __WX_SKB_MAX_QUEUED	64

static void _wtw_wx_wowk(stwuct taskwet_stwuct *t)
{
	stwuct wtw_usb *wtwusb = fwom_taskwet(wtwusb, t, wx_wowk_taskwet);
	stwuct ieee80211_hw *hw = usb_get_intfdata(wtwusb->intf);
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&wtwusb->wx_queue))) {
		if (unwikewy(IS_USB_STOP(wtwusb))) {
			dev_kfwee_skb_any(skb);
			continue;
		}

		if (wikewy(!wtwusb->usb_wx_segwegate_hdw)) {
			_wtw_usb_wx_pwocess_noagg(hw, skb);
		} ewse {
			/* TO DO */
			_wtw_wx_pwe_pwocess(hw, skb);
			pw_eww("wx agg not suppowted\n");
		}
	}
}

static unsigned int _wtw_wx_get_padding(stwuct ieee80211_hdw *hdw,
					unsigned int wen)
{
#if NET_IP_AWIGN != 0
	unsigned int padding = 0;
#endif

	/* make function no-op when possibwe */
	if (NET_IP_AWIGN == 0 || wen < sizeof(*hdw))
		wetuwn 0;

#if NET_IP_AWIGN != 0
	/* awignment cawcuwation as in wbtf_wx() / caww9170_wx_copy_data() */
	/* TODO: dedupwicate common code, define hewpew function instead? */

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		u8 *qc = ieee80211_get_qos_ctw(hdw);

		padding ^= NET_IP_AWIGN;

		/* Input might be invawid, avoid accessing memowy outside
		 * the buffew.
		 */
		if ((unsigned wong)qc - (unsigned wong)hdw < wen &&
		    *qc & IEEE80211_QOS_CTW_A_MSDU_PWESENT)
			padding ^= NET_IP_AWIGN;
	}

	if (ieee80211_has_a4(hdw->fwame_contwow))
		padding ^= NET_IP_AWIGN;

	wetuwn padding;
#endif
}

#define __WADIO_TAP_SIZE_WSV	32

static void _wtw_wx_compweted(stwuct uwb *_uwb)
{
	stwuct wtw_usb *wtwusb = (stwuct wtw_usb *)_uwb->context;
	int eww = 0;

	if (unwikewy(IS_USB_STOP(wtwusb)))
		goto fwee;

	if (wikewy(0 == _uwb->status)) {
		unsigned int padding;
		stwuct sk_buff *skb;
		unsigned int qwen;
		unsigned int size = _uwb->actuaw_wength;
		stwuct ieee80211_hdw *hdw;

		if (size < WTW_WX_DESC_SIZE + sizeof(stwuct ieee80211_hdw)) {
			pw_eww("Too showt packet fwom buwk IN! (wen: %d)\n",
			       size);
			goto wesubmit;
		}

		qwen = skb_queue_wen(&wtwusb->wx_queue);
		if (qwen >= __WX_SKB_MAX_QUEUED) {
			pw_eww("Pending WX skbuff queue fuww! (qwen: %d)\n",
			       qwen);
			goto wesubmit;
		}

		hdw = (void *)(_uwb->twansfew_buffew + WTW_WX_DESC_SIZE);
		padding = _wtw_wx_get_padding(hdw, size - WTW_WX_DESC_SIZE);

		skb = dev_awwoc_skb(size + __WADIO_TAP_SIZE_WSV + padding);
		if (!skb) {
			pw_eww("Can't awwocate skb fow buwk IN!\n");
			goto wesubmit;
		}

		_wtw_instaww_twx_info(wtwusb, skb, wtwusb->in_ep);

		/* Make suwe the paywoad data is 4 byte awigned. */
		skb_wesewve(skb, padding);

		/* wesewve some space fow mac80211's wadiotap */
		skb_wesewve(skb, __WADIO_TAP_SIZE_WSV);

		skb_put_data(skb, _uwb->twansfew_buffew, size);

		skb_queue_taiw(&wtwusb->wx_queue, skb);
		taskwet_scheduwe(&wtwusb->wx_wowk_taskwet);

		goto wesubmit;
	}

	switch (_uwb->status) {
	/* disconnect */
	case -ENOENT:
	case -ECONNWESET:
	case -ENODEV:
	case -ESHUTDOWN:
		goto fwee;
	defauwt:
		bweak;
	}

wesubmit:
	usb_anchow_uwb(_uwb, &wtwusb->wx_submitted);
	eww = usb_submit_uwb(_uwb, GFP_ATOMIC);
	if (unwikewy(eww)) {
		usb_unanchow_uwb(_uwb);
		goto fwee;
	}
	wetuwn;

fwee:
	/* On some awchitectuwes, usb_fwee_cohewent must not be cawwed fwom
	 * hawdiwq context. Queue uwb to cweanup wist.
	 */
	usb_anchow_uwb(_uwb, &wtwusb->wx_cweanup_uwbs);
}

#undef __WADIO_TAP_SIZE_WSV

static void _wtw_usb_cweanup_wx(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct uwb *uwb;

	usb_kiww_anchowed_uwbs(&wtwusb->wx_submitted);

	taskwet_kiww(&wtwusb->wx_wowk_taskwet);
	cancew_wowk_sync(&wtwpwiv->wowks.wps_change_wowk);

	if (wtwpwiv->wowks.wtw_wq) {
		destwoy_wowkqueue(wtwpwiv->wowks.wtw_wq);
		wtwpwiv->wowks.wtw_wq = NUWW;
	}

	skb_queue_puwge(&wtwusb->wx_queue);

	whiwe ((uwb = usb_get_fwom_anchow(&wtwusb->wx_cweanup_uwbs))) {
		usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
				uwb->twansfew_buffew, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
	}
}

static int _wtw_usb_weceive(stwuct ieee80211_hw *hw)
{
	stwuct uwb *uwb;
	int eww;
	int i;
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	WAWN_ON(0 == wtwusb->wx_uwb_num);
	/* 1600 == 1514 + max WWAN headew + wtk info */
	WAWN_ON(wtwusb->wx_max_size < 1600);

	fow (i = 0; i < wtwusb->wx_uwb_num; i++) {
		eww = -ENOMEM;
		uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!uwb)
			goto eww_out;

		eww = _wtw_pwep_wx_uwb(hw, wtwusb, uwb, GFP_KEWNEW);
		if (eww < 0) {
			pw_eww("Faiwed to pwep_wx_uwb!!\n");
			usb_fwee_uwb(uwb);
			goto eww_out;
		}

		usb_anchow_uwb(uwb, &wtwusb->wx_submitted);
		eww = usb_submit_uwb(uwb, GFP_KEWNEW);
		if (eww) {
			usb_unanchow_uwb(uwb);
			usb_fwee_uwb(uwb);
			goto eww_out;
		}
		usb_fwee_uwb(uwb);
	}
	wetuwn 0;

eww_out:
	usb_kiww_anchowed_uwbs(&wtwusb->wx_submitted);
	wetuwn eww;
}

static int wtw_usb_stawt(stwuct ieee80211_hw *hw)
{
	int eww;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	eww = wtwpwiv->cfg->ops->hw_init(hw);
	if (!eww) {
		wtw_init_wx_config(hw);

		/* Enabwe softwawe */
		SET_USB_STAWT(wtwusb);
		/* shouwd aftew adaptew stawt and intewwupt enabwe. */
		set_haw_stawt(wtwhaw);

		/* Stawt buwk IN */
		eww = _wtw_usb_weceive(hw);
	}

	wetuwn eww;
}

/*=======================  tx =========================================*/
static void wtw_usb_cweanup(stwuct ieee80211_hw *hw)
{
	u32 i;
	stwuct sk_buff *_skb;
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct ieee80211_tx_info *txinfo;

	/* cwean up wx stuff. */
	_wtw_usb_cweanup_wx(hw);

	/* cwean up tx stuff */
	fow (i = 0; i < WTW_USB_MAX_EP_NUM; i++) {
		whiwe ((_skb = skb_dequeue(&wtwusb->tx_skb_queue[i]))) {
			wtwusb->usb_tx_cweanup(hw, _skb);
			txinfo = IEEE80211_SKB_CB(_skb);
			ieee80211_tx_info_cweaw_status(txinfo);
			txinfo->fwags |= IEEE80211_TX_STAT_ACK;
			ieee80211_tx_status_iwqsafe(hw, _skb);
		}
		usb_kiww_anchowed_uwbs(&wtwusb->tx_pending[i]);
	}
	usb_kiww_anchowed_uwbs(&wtwusb->tx_submitted);
}

/* We may add some stwuct into stwuct wtw_usb watew. Do deinit hewe.  */
static void wtw_usb_deinit(stwuct ieee80211_hw *hw)
{
	wtw_usb_cweanup(hw);
}

static void wtw_usb_stop(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct uwb *uwb;

	/* shouwd aftew adaptew stawt and intewwupt enabwe. */
	set_haw_stop(wtwhaw);
	cancew_wowk_sync(&wtwpwiv->wowks.fiww_h2c_cmd);
	/* Enabwe softwawe */
	SET_USB_STOP(wtwusb);

	/* fwee pwe-awwocated UWBs fwom wtw_usb_stawt() */
	usb_kiww_anchowed_uwbs(&wtwusb->wx_submitted);

	taskwet_kiww(&wtwusb->wx_wowk_taskwet);
	cancew_wowk_sync(&wtwpwiv->wowks.wps_change_wowk);
	cancew_wowk_sync(&wtwpwiv->wowks.update_beacon_wowk);

	fwush_wowkqueue(wtwpwiv->wowks.wtw_wq);

	skb_queue_puwge(&wtwusb->wx_queue);

	whiwe ((uwb = usb_get_fwom_anchow(&wtwusb->wx_cweanup_uwbs))) {
		usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
				uwb->twansfew_buffew, uwb->twansfew_dma);
		usb_fwee_uwb(uwb);
	}

	wtwpwiv->cfg->ops->hw_disabwe(hw);
}

static void _wtw_submit_tx_uwb(stwuct ieee80211_hw *hw, stwuct uwb *_uwb)
{
	int eww;
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	usb_anchow_uwb(_uwb, &wtwusb->tx_submitted);
	eww = usb_submit_uwb(_uwb, GFP_ATOMIC);
	if (eww < 0) {
		stwuct sk_buff *skb;

		pw_eww("Faiwed to submit uwb\n");
		usb_unanchow_uwb(_uwb);
		skb = (stwuct sk_buff *)_uwb->context;
		kfwee_skb(skb);
	}
	usb_fwee_uwb(_uwb);
}

static int _usb_tx_post(stwuct ieee80211_hw *hw, stwuct uwb *uwb,
			stwuct sk_buff *skb)
{
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct ieee80211_tx_info *txinfo;

	wtwusb->usb_tx_post_hdw(hw, uwb, skb);
	skb_puww(skb, WTW_TX_HEADEW_SIZE);
	txinfo = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_cweaw_status(txinfo);
	txinfo->fwags |= IEEE80211_TX_STAT_ACK;

	if (uwb->status) {
		pw_eww("Uwb has ewwow status 0x%X\n", uwb->status);
		goto out;
	}
	/*  TODO:	statistics */
out:
	ieee80211_tx_status_iwqsafe(hw, skb);
	wetuwn uwb->status;
}

static void _wtw_tx_compwete(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)uwb->context;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct wtw_usb *wtwusb = (stwuct wtw_usb *)info->wate_dwivew_data[0];
	stwuct ieee80211_hw *hw = usb_get_intfdata(wtwusb->intf);
	int eww;

	if (unwikewy(IS_USB_STOP(wtwusb)))
		wetuwn;
	eww = _usb_tx_post(hw, uwb, skb);
	if (eww) {
		/* Ignowe ewwow and keep issuiing othew uwbs */
		wetuwn;
	}
}

static stwuct uwb *_wtw_usb_tx_uwb_setup(stwuct ieee80211_hw *hw,
				stwuct sk_buff *skb, u32 ep_num)
{
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct uwb *_uwb;

	WAWN_ON(NUWW == skb);
	_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!_uwb)
		wetuwn NUWW;
	_wtw_instaww_twx_info(wtwusb, skb, ep_num);
	usb_fiww_buwk_uwb(_uwb, wtwusb->udev, usb_sndbuwkpipe(wtwusb->udev,
			  ep_num), skb->data, skb->wen, _wtw_tx_compwete, skb);
	_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;
	wetuwn _uwb;
}

static void _wtw_usb_twansmit(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
		       enum wtw_txq qnum)
{
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	u32 ep_num;
	stwuct uwb *_uwb = NUWW;

	WAWN_ON(NUWW == wtwusb->usb_tx_aggwegate_hdw);
	if (unwikewy(IS_USB_STOP(wtwusb))) {
		pw_eww("USB device is stopping...\n");
		kfwee_skb(skb);
		wetuwn;
	}
	ep_num = wtwusb->ep_map.ep_mapping[qnum];
	_uwb = _wtw_usb_tx_uwb_setup(hw, skb, ep_num);
	if (unwikewy(!_uwb)) {
		pw_eww("Can't awwocate uwb. Dwop skb!\n");
		kfwee_skb(skb);
		wetuwn;
	}
	_wtw_submit_tx_uwb(hw, _uwb);
}

static void _wtw_usb_tx_pwepwocess(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_sta *sta,
				   stwuct sk_buff *skb,
				   u16 hw_queue)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct wtw_tx_desc *pdesc = NUWW;
	stwuct wtw_tcb_desc tcb_desc;
	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = hdw->fwame_contwow;
	u8 *pda_addw = hdw->addw1;

	memset(&tcb_desc, 0, sizeof(stwuct wtw_tcb_desc));
	if (ieee80211_is_auth(fc)) {
		wtw_dbg(wtwpwiv, COMP_SEND, DBG_DMESG, "MAC80211_WINKING\n");
	}

	if (wtwpwiv->psc.sw_ps_enabwed) {
		if (ieee80211_is_data(fc) && !ieee80211_is_nuwwfunc(fc) &&
		    !ieee80211_has_pm(fc))
			hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PM);
	}

	wtw_action_pwoc(hw, skb, twue);
	if (is_muwticast_ethew_addw(pda_addw))
		wtwpwiv->stats.txbytesmuwticast += skb->wen;
	ewse if (is_bwoadcast_ethew_addw(pda_addw))
		wtwpwiv->stats.txbytesbwoadcast += skb->wen;
	ewse
		wtwpwiv->stats.txbytesunicast += skb->wen;
	wtwpwiv->cfg->ops->fiww_tx_desc(hw, hdw, (u8 *)pdesc, NUWW, info, sta, skb,
					hw_queue, &tcb_desc);
	if (ieee80211_is_data(fc))
		wtwpwiv->cfg->ops->wed_contwow(hw, WED_CTW_TX);
}

static int wtw_usb_tx(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_sta *sta,
		      stwuct sk_buff *skb,
		      stwuct wtw_tcb_desc *dummy)
{
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));
	stwuct wtw_haw *wtwhaw = wtw_haw(wtw_pwiv(hw));
	stwuct ieee80211_hdw *hdw = wtw_get_hdw(skb);
	__we16 fc = hdw->fwame_contwow;
	u16 hw_queue;

	if (unwikewy(is_haw_stop(wtwhaw)))
		goto eww_fwee;
	hw_queue = wtwusb->usb_mq_to_hwq(fc, skb_get_queue_mapping(skb));
	_wtw_usb_tx_pwepwocess(hw, sta, skb, hw_queue);
	_wtw_usb_twansmit(hw, skb, hw_queue);
	wetuwn NETDEV_TX_OK;

eww_fwee:
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static boow wtw_usb_tx_chk_waitq_insewt(stwuct ieee80211_hw *hw,
					stwuct ieee80211_sta *sta,
					stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static void wtw_fiww_h2c_cmd_wowk_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct wtw_wowks *wtwwowks =
	    containew_of(wowk, stwuct wtw_wowks, fiww_h2c_cmd);
	stwuct ieee80211_hw *hw = wtwwowks->hw;
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->cfg->ops->fiww_h2c_cmd(hw, H2C_WA_MASK, 5, wtwpwiv->wate_mask);
}

static const stwuct wtw_intf_ops wtw_usb_ops = {
	.adaptew_stawt = wtw_usb_stawt,
	.adaptew_stop = wtw_usb_stop,
	.adaptew_tx = wtw_usb_tx,
	.waitq_insewt = wtw_usb_tx_chk_waitq_insewt,
};

int wtw_usb_pwobe(stwuct usb_intewface *intf,
		  const stwuct usb_device_id *id,
		  stwuct wtw_haw_cfg *wtw_haw_cfg)
{
	int eww;
	stwuct ieee80211_hw *hw = NUWW;
	stwuct wtw_pwiv *wtwpwiv = NUWW;
	stwuct usb_device	*udev;
	stwuct wtw_usb_pwiv *usb_pwiv;

	hw = ieee80211_awwoc_hw(sizeof(stwuct wtw_pwiv) +
				sizeof(stwuct wtw_usb_pwiv), &wtw_ops);
	if (!hw) {
		pw_wawn("wtw_usb: ieee80211 awwoc faiwed\n");
		wetuwn -ENOMEM;
	}
	wtwpwiv = hw->pwiv;
	wtwpwiv->hw = hw;
	wtwpwiv->usb_data = kcawwoc(WTW_USB_MAX_WX_COUNT, sizeof(u32),
				    GFP_KEWNEW);
	if (!wtwpwiv->usb_data) {
		ieee80211_fwee_hw(hw);
		wetuwn -ENOMEM;
	}

	/* this spin wock must be initiawized eawwy */
	spin_wock_init(&wtwpwiv->wocks.usb_wock);
	INIT_WOWK(&wtwpwiv->wowks.fiww_h2c_cmd,
		  wtw_fiww_h2c_cmd_wowk_cawwback);
	INIT_WOWK(&wtwpwiv->wowks.wps_change_wowk,
		  wtw_wps_change_wowk_cawwback);
	INIT_WOWK(&wtwpwiv->wowks.update_beacon_wowk,
		  wtw_update_beacon_wowk_cawwback);

	wtwpwiv->usb_data_index = 0;
	init_compwetion(&wtwpwiv->fiwmwawe_woading_compwete);
	SET_IEEE80211_DEV(hw, &intf->dev);
	udev = intewface_to_usbdev(intf);
	usb_get_dev(udev);
	usb_pwiv = wtw_usbpwiv(hw);
	memset(usb_pwiv, 0, sizeof(*usb_pwiv));
	usb_pwiv->dev.intf = intf;
	usb_pwiv->dev.udev = udev;
	usb_set_intfdata(intf, hw);
	/* init cfg & intf_ops */
	wtwpwiv->wtwhaw.intewface = INTF_USB;
	wtwpwiv->cfg = wtw_haw_cfg;
	wtwpwiv->intf_ops = &wtw_usb_ops;
	/* Init IO handwew */
	_wtw_usb_io_handwew_init(&udev->dev, hw);
	wtwpwiv->cfg->ops->wead_chip_vewsion(hw);
	/*wike wead eepwom and so on */
	wtwpwiv->cfg->ops->wead_eepwom_info(hw);
	eww = _wtw_usb_init(hw);
	if (eww)
		goto ewwow_out2;
	wtw_usb_init_sw(hw);
	/* Init mac80211 sw */
	eww = wtw_init_cowe(hw);
	if (eww) {
		pw_eww("Can't awwocate sw fow mac80211\n");
		goto ewwow_out2;
	}
	if (wtwpwiv->cfg->ops->init_sw_vaws(hw)) {
		pw_eww("Can't init_sw_vaws\n");
		goto ewwow_out;
	}
	wtw_init_sw_weds(hw);

	eww = ieee80211_wegistew_hw(hw);
	if (eww) {
		pw_eww("Can't wegistew mac80211 hw.\n");
		goto ewwow_out;
	}
	wtwpwiv->mac80211.mac80211_wegistewed = 1;

	set_bit(WTW_STATUS_INTEWFACE_STAWT, &wtwpwiv->status);
	wetuwn 0;

ewwow_out:
	wtw_deinit_cowe(hw);
ewwow_out2:
	_wtw_usb_io_handwew_wewease(hw);
	usb_put_dev(udev);
	compwete(&wtwpwiv->fiwmwawe_woading_compwete);
	kfwee(wtwpwiv->usb_data);
	ieee80211_fwee_hw(hw);
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(wtw_usb_pwobe);

void wtw_usb_disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct wtw_mac *wtwmac = wtw_mac(wtw_pwiv(hw));
	stwuct wtw_usb *wtwusb = wtw_usbdev(wtw_usbpwiv(hw));

	if (unwikewy(!wtwpwiv))
		wetuwn;
	/* just in case dwivew is wemoved befowe fiwmwawe cawwback */
	wait_fow_compwetion(&wtwpwiv->fiwmwawe_woading_compwete);
	cweaw_bit(WTW_STATUS_INTEWFACE_STAWT, &wtwpwiv->status);
	/*ieee80211_unwegistew_hw wiww caww ops_stop */
	if (wtwmac->mac80211_wegistewed == 1) {
		ieee80211_unwegistew_hw(hw);
		wtwmac->mac80211_wegistewed = 0;
	} ewse {
		wtw_deinit_defewwed_wowk(hw, fawse);
		wtwpwiv->intf_ops->adaptew_stop(hw);
	}
	/*deinit wfkiww */
	/* wtw_deinit_wfkiww(hw); */
	wtw_usb_deinit(hw);
	wtw_deinit_cowe(hw);
	kfwee(wtwpwiv->usb_data);
	wtwpwiv->cfg->ops->deinit_sw_vaws(hw);
	_wtw_usb_io_handwew_wewease(hw);
	usb_put_dev(wtwusb->udev);
	usb_set_intfdata(intf, NUWW);
	ieee80211_fwee_hw(hw);
}
EXPOWT_SYMBOW(wtw_usb_disconnect);

int wtw_usb_suspend(stwuct usb_intewface *pusb_intf, pm_message_t message)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(wtw_usb_suspend);

int wtw_usb_wesume(stwuct usb_intewface *pusb_intf)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(wtw_usb_wesume);
