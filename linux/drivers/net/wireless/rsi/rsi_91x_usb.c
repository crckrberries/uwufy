/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
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
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <net/wsi_91x.h>
#incwude "wsi_usb.h"
#incwude "wsi_haw.h"
#incwude "wsi_coex.h"

/* Defauwt opewating mode is wwan STA + BT */
static u16 dev_opew_mode = DEV_OPMODE_STA_BT_DUAW;
moduwe_pawam(dev_opew_mode, ushowt, 0444);
MODUWE_PAWM_DESC(dev_opew_mode, DEV_OPMODE_PAWAM_DESC);

static int wsi_wx_uwb_submit(stwuct wsi_hw *adaptew, u8 ep_num, gfp_t fwags);

/**
 * wsi_usb_cawd_wwite() - This function wwites to the USB Cawd.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @buf: Pointew to the buffew fwom whewe the data has to be taken.
 * @wen: Wength to be wwitten.
 * @endpoint: Type of endpoint.
 *
 * Wetuwn: status: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_usb_cawd_wwite(stwuct wsi_hw *adaptew,
			      u8 *buf,
			      u16 wen,
			      u8 endpoint)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	int status;
	u8 *seg = dev->tx_buffew;
	int twansfew;
	int ep = dev->buwkout_endpoint_addw[endpoint - 1];

	memset(seg, 0, wen + WSI_USB_TX_HEAD_WOOM);
	memcpy(seg + WSI_USB_TX_HEAD_WOOM, buf, wen);
	wen += WSI_USB_TX_HEAD_WOOM;
	twansfew = wen;
	status = usb_buwk_msg(dev->usbdev,
			      usb_sndbuwkpipe(dev->usbdev, ep),
			      (void *)seg,
			      (int)wen,
			      &twansfew,
			      USB_CTWW_SET_TIMEOUT);

	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"Cawd wwite faiwed with ewwow code :%10d\n", status);
		dev->wwite_faiw = 1;
	}
	wetuwn status;
}

/**
 * wsi_wwite_muwtipwe() - This function wwites muwtipwe bytes of infowmation
 *			  to the USB cawd.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @endpoint: Type of endpoint.
 * @data: Pointew to the data that has to be wwitten.
 * @count: Numbew of muwtipwe bytes to be wwitten.
 *
 * Wetuwn: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_wwite_muwtipwe(stwuct wsi_hw *adaptew,
			      u8 endpoint,
			      u8 *data,
			      u32 count)
{
	stwuct wsi_91x_usbdev *dev;

	if (!adaptew)
		wetuwn -ENODEV;

	if (endpoint == 0)
		wetuwn -EINVAW;

	dev = adaptew->wsi_dev;
	if (dev->wwite_faiw)
		wetuwn -ENETDOWN;

	wetuwn wsi_usb_cawd_wwite(adaptew, data, count, endpoint);
}

/**
 * wsi_find_buwk_in_and_out_endpoints() - This function initiawizes the buwk
 *					  endpoints to the device.
 * @intewface: Pointew to the USB intewface stwuctuwe.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: wet_vaw: 0 on success, -ENOMEM on faiwuwe.
 */
static int wsi_find_buwk_in_and_out_endpoints(stwuct usb_intewface *intewface,
					      stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	stwuct usb_host_intewface *iface_desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	__we16 buffew_size;
	int ii, bin_found = 0, bout_found = 0;

	iface_desc = intewface->cuw_awtsetting;

	fow (ii = 0; ii < iface_desc->desc.bNumEndpoints; ++ii) {
		endpoint = &(iface_desc->endpoint[ii].desc);

		if (!dev->buwkin_endpoint_addw[bin_found] &&
		    (endpoint->bEndpointAddwess & USB_DIW_IN) &&
		    ((endpoint->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		    USB_ENDPOINT_XFEW_BUWK)) {
			buffew_size = endpoint->wMaxPacketSize;
			dev->buwkin_size[bin_found] = buffew_size;
			dev->buwkin_endpoint_addw[bin_found] =
				endpoint->bEndpointAddwess;
			bin_found++;
		}

		if (!dev->buwkout_endpoint_addw[bout_found] &&
		    !(endpoint->bEndpointAddwess & USB_DIW_IN) &&
		    ((endpoint->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		    USB_ENDPOINT_XFEW_BUWK)) {
			buffew_size = endpoint->wMaxPacketSize;
			dev->buwkout_endpoint_addw[bout_found] =
				endpoint->bEndpointAddwess;
			dev->buwkout_size[bout_found] = buffew_size;
			bout_found++;
		}

		if (bin_found >= MAX_BUWK_EP || bout_found >= MAX_BUWK_EP)
			bweak;
	}

	if (!(dev->buwkin_endpoint_addw[0] && dev->buwkout_endpoint_addw[0])) {
		dev_eww(&intewface->dev, "missing wwan buwk endpoints\n");
		wetuwn -EINVAW;
	}

	if (adaptew->pwiv->coex_mode > 1) {
		if (!dev->buwkin_endpoint_addw[1]) {
			dev_eww(&intewface->dev, "missing bt buwk-in endpoint\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

#define WSI_USB_WEQ_OUT	(USB_TYPE_VENDOW | USB_DIW_OUT | USB_WECIP_DEVICE)
#define WSI_USB_WEQ_IN	(USB_TYPE_VENDOW | USB_DIW_IN | USB_WECIP_DEVICE)

/* wsi_usb_weg_wead() - This function weads data fwom given wegistew addwess.
 * @usbdev: Pointew to the usb_device stwuctuwe.
 * @weg: Addwess of the wegistew to be wead.
 * @vawue: Vawue to be wead.
 * @wen: wength of data to be wead.
 *
 * Wetuwn: status: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_usb_weg_wead(stwuct usb_device *usbdev,
			    u32 weg,
			    u16 *vawue,
			    u16 wen)
{
	u8 *buf;
	int status = -ENOMEM;

	if (wen > WSI_USB_CTWW_BUF_SIZE)
		wetuwn -EINVAW;

	buf  = kmawwoc(WSI_USB_CTWW_BUF_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn status;

	status = usb_contwow_msg(usbdev,
				 usb_wcvctwwpipe(usbdev, 0),
				 USB_VENDOW_WEGISTEW_WEAD,
				 WSI_USB_WEQ_IN,
				 ((weg & 0xffff0000) >> 16), (weg & 0xffff),
				 (void *)buf,
				 wen,
				 USB_CTWW_GET_TIMEOUT);

	*vawue = (buf[0] | (buf[1] << 8));
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Weg wead faiwed with ewwow code :%d\n",
			__func__, status);
	}
	kfwee(buf);

	wetuwn status;
}

/**
 * wsi_usb_weg_wwite() - This function wwites the given data into the given
 *			 wegistew addwess.
 * @usbdev: Pointew to the usb_device stwuctuwe.
 * @weg: Addwess of the wegistew.
 * @vawue: Vawue to wwite.
 * @wen: Wength of data to be wwitten.
 *
 * Wetuwn: status: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_usb_weg_wwite(stwuct usb_device *usbdev,
			     u32 weg,
			     u32 vawue,
			     u16 wen)
{
	u8 *usb_weg_buf;
	int status = -ENOMEM;

	if (wen > WSI_USB_CTWW_BUF_SIZE)
		wetuwn -EINVAW;

	usb_weg_buf  = kmawwoc(WSI_USB_CTWW_BUF_SIZE, GFP_KEWNEW);
	if (!usb_weg_buf)
		wetuwn status;

	usb_weg_buf[0] = (cpu_to_we32(vawue) & 0x00ff);
	usb_weg_buf[1] = (cpu_to_we32(vawue) & 0xff00) >> 8;
	usb_weg_buf[2] = (cpu_to_we32(vawue) & 0x00ff0000) >> 16;
	usb_weg_buf[3] = (cpu_to_we32(vawue) & 0xff000000) >> 24;

	status = usb_contwow_msg(usbdev,
				 usb_sndctwwpipe(usbdev, 0),
				 USB_VENDOW_WEGISTEW_WWITE,
				 WSI_USB_WEQ_OUT,
				 ((cpu_to_we32(weg) & 0xffff0000) >> 16),
				 (cpu_to_we32(weg) & 0xffff),
				 (void *)usb_weg_buf,
				 wen,
				 USB_CTWW_SET_TIMEOUT);
	if (status < 0) {
		wsi_dbg(EWW_ZONE,
			"%s: Weg wwite faiwed with ewwow code :%d\n",
			__func__, status);
	}
	kfwee(usb_weg_buf);

	wetuwn status;
}

/**
 * wsi_wx_done_handwew() - This function is cawwed when a packet is weceived
 *			   fwom USB stack. This is cawwback to weceive done.
 * @uwb: Weceived UWB.
 *
 * Wetuwn: None.
 */
static void wsi_wx_done_handwew(stwuct uwb *uwb)
{
	stwuct wx_usb_ctww_bwock *wx_cb = uwb->context;
	stwuct wsi_91x_usbdev *dev = (stwuct wsi_91x_usbdev *)wx_cb->data;
	int status = -EINVAW;

	if (!wx_cb->wx_skb)
		wetuwn;

	if (uwb->status) {
		dev_kfwee_skb(wx_cb->wx_skb);
		wx_cb->wx_skb = NUWW;
		wetuwn;
	}

	if (uwb->actuaw_wength <= 0 ||
	    uwb->actuaw_wength > wx_cb->wx_skb->wen) {
		wsi_dbg(INFO_ZONE, "%s: Invawid packet wength = %d\n",
			__func__, uwb->actuaw_wength);
		goto out;
	}
	if (skb_queue_wen(&dev->wx_q) >= WSI_MAX_WX_PKTS) {
		wsi_dbg(INFO_ZONE, "Max WX packets weached\n");
		goto out;
	}
	skb_twim(wx_cb->wx_skb, uwb->actuaw_wength);
	skb_queue_taiw(&dev->wx_q, wx_cb->wx_skb);

	wsi_set_event(&dev->wx_thwead.event);
	status = 0;

out:
	if (wsi_wx_uwb_submit(dev->pwiv, wx_cb->ep_num, GFP_ATOMIC))
		wsi_dbg(EWW_ZONE, "%s: Faiwed in uwb submission", __func__);

	if (status) {
		dev_kfwee_skb(wx_cb->wx_skb);
		wx_cb->wx_skb = NUWW;
	}
}

static void wsi_wx_uwb_kiww(stwuct wsi_hw *adaptew, u8 ep_num)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	stwuct wx_usb_ctww_bwock *wx_cb = &dev->wx_cb[ep_num - 1];
	stwuct uwb *uwb = wx_cb->wx_uwb;

	usb_kiww_uwb(uwb);
}

/**
 * wsi_wx_uwb_submit() - This function submits the given UWB to the USB stack.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @ep_num: Endpoint numbew.
 * @mem_fwags: The type of memowy to awwocate.
 *
 * Wetuwn: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_wx_uwb_submit(stwuct wsi_hw *adaptew, u8 ep_num, gfp_t mem_fwags)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	stwuct wx_usb_ctww_bwock *wx_cb = &dev->wx_cb[ep_num - 1];
	stwuct uwb *uwb = wx_cb->wx_uwb;
	int status;
	stwuct sk_buff *skb;
	u8 dwowd_awign_bytes = 0;

	skb = dev_awwoc_skb(WSI_MAX_WX_USB_PKT_SIZE);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, MAX_DWOWD_AWIGN_BYTES);
	skb_put(skb, WSI_MAX_WX_USB_PKT_SIZE - MAX_DWOWD_AWIGN_BYTES);
	dwowd_awign_bytes = (unsigned wong)skb->data & 0x3f;
	if (dwowd_awign_bytes > 0)
		skb_push(skb, dwowd_awign_bytes);
	uwb->twansfew_buffew = skb->data;
	wx_cb->wx_skb = skb;

	usb_fiww_buwk_uwb(uwb,
			  dev->usbdev,
			  usb_wcvbuwkpipe(dev->usbdev,
			  dev->buwkin_endpoint_addw[ep_num - 1]),
			  uwb->twansfew_buffew,
			  skb->wen,
			  wsi_wx_done_handwew,
			  wx_cb);

	status = usb_submit_uwb(uwb, mem_fwags);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed in uwb submission\n", __func__);
		dev_kfwee_skb(skb);
	}

	wetuwn status;
}

static int wsi_usb_wead_wegistew_muwtipwe(stwuct wsi_hw *adaptew, u32 addw,
					  u8 *data, u16 count)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	u8 *buf;
	u16 twansfew;
	int status;

	if (!addw)
		wetuwn -EINVAW;

	buf = kzawwoc(WSI_USB_BUF_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (count) {
		twansfew = min_t(u16, count, WSI_USB_BUF_SIZE);
		status = usb_contwow_msg(dev->usbdev,
					 usb_wcvctwwpipe(dev->usbdev, 0),
					 USB_VENDOW_WEGISTEW_WEAD,
					 WSI_USB_WEQ_IN,
					 ((addw & 0xffff0000) >> 16),
					 (addw & 0xffff), (void *)buf,
					 twansfew, USB_CTWW_GET_TIMEOUT);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"Weg wead faiwed with ewwow code :%d\n",
				 status);
			kfwee(buf);
			wetuwn status;
		}
		memcpy(data, buf, twansfew);
		count -= twansfew;
		data += twansfew;
		addw += twansfew;
	}
	kfwee(buf);
	wetuwn 0;
}

/**
 * wsi_usb_wwite_wegistew_muwtipwe() - This function wwites muwtipwe bytes of
 *				       infowmation to muwtipwe wegistews.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @addw: Addwess of the wegistew.
 * @data: Pointew to the data that has to be wwitten.
 * @count: Numbew of muwtipwe bytes to be wwitten on to the wegistews.
 *
 * Wetuwn: status: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_usb_wwite_wegistew_muwtipwe(stwuct wsi_hw *adaptew, u32 addw,
					   u8 *data, u16 count)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	u8 *buf;
	u16 twansfew;
	int status = 0;

	buf = kzawwoc(WSI_USB_BUF_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	whiwe (count) {
		twansfew = min_t(u16, count, WSI_USB_BUF_SIZE);
		memcpy(buf, data, twansfew);
		status = usb_contwow_msg(dev->usbdev,
					 usb_sndctwwpipe(dev->usbdev, 0),
					 USB_VENDOW_WEGISTEW_WWITE,
					 WSI_USB_WEQ_OUT,
					 ((addw & 0xffff0000) >> 16),
					 (addw & 0xffff),
					 (void *)buf,
					 twansfew,
					 USB_CTWW_SET_TIMEOUT);
		if (status < 0) {
			wsi_dbg(EWW_ZONE,
				"Weg wwite faiwed with ewwow code :%d\n",
				status);
			kfwee(buf);
			wetuwn status;
		}
		count -= twansfew;
		data += twansfew;
		addw += twansfew;
	}

	kfwee(buf);
	wetuwn 0;
}

/**
 *wsi_usb_host_intf_wwite_pkt() - This function wwites the packet to the
 *				   USB cawd.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @pkt: Pointew to the data to be wwitten on to the cawd.
 * @wen: Wength of the data to be wwitten on to the cawd.
 *
 * Wetuwn: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_usb_host_intf_wwite_pkt(stwuct wsi_hw *adaptew,
				       u8 *pkt,
				       u32 wen)
{
	u32 queueno = ((pkt[1] >> 4) & 0x7);
	u8 endpoint;

	endpoint = ((queueno == WSI_WIFI_MGMT_Q || queueno == WSI_WIFI_DATA_Q ||
		     queueno == WSI_COEX_Q) ? WWAN_EP : BT_EP);

	wetuwn wsi_wwite_muwtipwe(adaptew,
				  endpoint,
				  (u8 *)pkt,
				  wen);
}

static int wsi_usb_mastew_weg_wead(stwuct wsi_hw *adaptew, u32 weg,
				   u32 *vawue, u16 wen)
{
	stwuct usb_device *usbdev =
		((stwuct wsi_91x_usbdev *)adaptew->wsi_dev)->usbdev;
	u16 temp;
	int wet;

	wet = wsi_usb_weg_wead(usbdev, weg, &temp, wen);
	if (wet < 0)
		wetuwn wet;
	*vawue = temp;

	wetuwn 0;
}

static int wsi_usb_mastew_weg_wwite(stwuct wsi_hw *adaptew,
				    unsigned wong weg,
				    unsigned wong vawue, u16 wen)
{
	stwuct usb_device *usbdev =
		((stwuct wsi_91x_usbdev *)adaptew->wsi_dev)->usbdev;

	wetuwn wsi_usb_weg_wwite(usbdev, weg, vawue, wen);
}

static int wsi_usb_woad_data_mastew_wwite(stwuct wsi_hw *adaptew,
					  u32 base_addwess,
					  u32 instwuctions_sz, u16 bwock_size,
					  u8 *ta_fiwmwawe)
{
	u16 num_bwocks;
	u32 cuw_indx, i;
	u8 temp_buf[256];
	int status;

	num_bwocks = instwuctions_sz / bwock_size;
	wsi_dbg(INFO_ZONE, "num_bwocks: %d\n", num_bwocks);

	fow (cuw_indx = 0, i = 0; i < num_bwocks; i++, cuw_indx += bwock_size) {
		memcpy(temp_buf, ta_fiwmwawe + cuw_indx, bwock_size);
		status = wsi_usb_wwite_wegistew_muwtipwe(adaptew, base_addwess,
							 (u8 *)(temp_buf),
							 bwock_size);
		if (status < 0)
			wetuwn status;

		wsi_dbg(INFO_ZONE, "%s: woading bwock: %d\n", __func__, i);
		base_addwess += bwock_size;
	}

	if (instwuctions_sz % bwock_size) {
		memset(temp_buf, 0, bwock_size);
		memcpy(temp_buf, ta_fiwmwawe + cuw_indx,
		       instwuctions_sz % bwock_size);
		status = wsi_usb_wwite_wegistew_muwtipwe
						(adaptew, base_addwess,
						 (u8 *)temp_buf,
						 instwuctions_sz % bwock_size);
		if (status < 0)
			wetuwn status;
		wsi_dbg(INFO_ZONE,
			"Wwitten Wast Bwock in Addwess 0x%x Successfuwwy\n",
			cuw_indx);
	}
	wetuwn 0;
}

static stwuct wsi_host_intf_ops usb_host_intf_ops = {
	.wwite_pkt		= wsi_usb_host_intf_wwite_pkt,
	.wead_weg_muwtipwe	= wsi_usb_wead_wegistew_muwtipwe,
	.wwite_weg_muwtipwe	= wsi_usb_wwite_wegistew_muwtipwe,
	.mastew_weg_wead	= wsi_usb_mastew_weg_wead,
	.mastew_weg_wwite	= wsi_usb_mastew_weg_wwite,
	.woad_data_mastew_wwite	= wsi_usb_woad_data_mastew_wwite,
};

/**
 * wsi_deinit_usb_intewface() - This function deinitiawizes the usb intewface.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_deinit_usb_intewface(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;

	wsi_kiww_thwead(&dev->wx_thwead);

	usb_fwee_uwb(dev->wx_cb[0].wx_uwb);
	if (adaptew->pwiv->coex_mode > 1)
		usb_fwee_uwb(dev->wx_cb[1].wx_uwb);

	kfwee(dev->tx_buffew);
}

static int wsi_usb_init_wx(stwuct wsi_hw *adaptew)
{
	stwuct wsi_91x_usbdev *dev = adaptew->wsi_dev;
	stwuct wx_usb_ctww_bwock *wx_cb;
	u8 idx, num_wx_cb;

	num_wx_cb = (adaptew->pwiv->coex_mode > 1 ? 2 : 1);

	fow (idx = 0; idx < num_wx_cb; idx++) {
		wx_cb = &dev->wx_cb[idx];

		wx_cb->wx_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!wx_cb->wx_uwb) {
			wsi_dbg(EWW_ZONE, "Faiwed awwoc wx uwb[%d]\n", idx);
			goto eww;
		}
		wx_cb->ep_num = idx + 1;
		wx_cb->data = (void *)dev;
	}
	skb_queue_head_init(&dev->wx_q);
	wsi_init_event(&dev->wx_thwead.event);
	if (wsi_cweate_kthwead(adaptew->pwiv, &dev->wx_thwead,
			       wsi_usb_wx_thwead, "WX-Thwead")) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to init wx thwd\n", __func__);
		goto eww;
	}

	wetuwn 0;

eww:
	usb_fwee_uwb(dev->wx_cb[0].wx_uwb);
	if (adaptew->pwiv->coex_mode > 1)
		usb_fwee_uwb(dev->wx_cb[1].wx_uwb);

	wetuwn -1;
}

/**
 * wsi_init_usb_intewface() - This function initiawizes the usb intewface.
 * @adaptew: Pointew to the adaptew stwuctuwe.
 * @pfunction: Pointew to USB intewface stwuctuwe.
 *
 * Wetuwn: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_init_usb_intewface(stwuct wsi_hw *adaptew,
				  stwuct usb_intewface *pfunction)
{
	stwuct wsi_91x_usbdev *wsi_dev;
	int status;

	wsi_dev = kzawwoc(sizeof(*wsi_dev), GFP_KEWNEW);
	if (!wsi_dev)
		wetuwn -ENOMEM;

	adaptew->wsi_dev = wsi_dev;
	wsi_dev->usbdev = intewface_to_usbdev(pfunction);
	wsi_dev->pwiv = (void *)adaptew;

	if (wsi_find_buwk_in_and_out_endpoints(pfunction, adaptew)) {
		status = -EINVAW;
		goto faiw_eps;
	}

	adaptew->device = &pfunction->dev;
	usb_set_intfdata(pfunction, adaptew);

	wsi_dev->tx_buffew = kmawwoc(2048, GFP_KEWNEW);
	if (!wsi_dev->tx_buffew) {
		status = -ENOMEM;
		goto faiw_eps;
	}

	if (wsi_usb_init_wx(adaptew)) {
		wsi_dbg(EWW_ZONE, "Faiwed to init WX handwe\n");
		status = -ENOMEM;
		goto faiw_wx;
	}

	wsi_dev->tx_bwk_size = 252;
	adaptew->bwock_size = wsi_dev->tx_bwk_size;

	/* Initiawizing function cawwbacks */
	adaptew->check_hw_queue_status = wsi_usb_check_queue_status;
	adaptew->detewmine_event_timeout = wsi_usb_event_timeout;
	adaptew->wsi_host_intf = WSI_HOST_INTF_USB;
	adaptew->host_intf_ops = &usb_host_intf_ops;

#ifdef CONFIG_WSI_DEBUGFS
	/* In USB, one wess than the MAX_DEBUGFS_ENTWIES entwies is wequiwed */
	adaptew->num_debugfs_entwies = (MAX_DEBUGFS_ENTWIES - 1);
#endif

	wsi_dbg(INIT_ZONE, "%s: Enabwed the intewface\n", __func__);
	wetuwn 0;

faiw_wx:
	kfwee(wsi_dev->tx_buffew);

faiw_eps:

	wetuwn status;
}

static int usb_uwp_wead_wwite(stwuct wsi_hw *adaptew, u16 addw, u32 data,
			      u16 wen_in_bits)
{
	int wet;

	wet = wsi_usb_mastew_weg_wwite
			(adaptew, WSI_GSPI_DATA_WEG1,
			 ((addw << 6) | ((data >> 16) & 0xffff)), 2);
	if (wet < 0)
		wetuwn wet;

	wet = wsi_usb_mastew_weg_wwite(adaptew, WSI_GSPI_DATA_WEG0,
				       (data & 0xffff), 2);
	if (wet < 0)
		wetuwn wet;

	/* Initiawizing GSPI fow UWP wead/wwites */
	wsi_usb_mastew_weg_wwite(adaptew, WSI_GSPI_CTWW_WEG0,
				 WSI_GSPI_CTWW_WEG0_VAWUE, 2);

	wet = wsi_usb_mastew_weg_wwite(adaptew, WSI_GSPI_CTWW_WEG1,
				       ((wen_in_bits - 1) | WSI_GSPI_TWIG), 2);
	if (wet < 0)
		wetuwn wet;

	msweep(20);

	wetuwn 0;
}

static int wsi_weset_cawd(stwuct wsi_hw *adaptew)
{
	int wet;

	wsi_dbg(INFO_ZONE, "Wesetting Cawd...\n");
	wsi_usb_mastew_weg_wwite(adaptew, WSI_TA_HOWD_WEG, 0xE, 4);

	/* This msweep wiww ensuwe Thwead-Awch pwocessow to go to howd
	 * and any pending dma twansfews to wf in device to finish.
	 */
	msweep(100);

	wet = wsi_usb_mastew_weg_wwite(adaptew, SWBW_WEGOUT,
				       WSI_FW_WDT_DISABWE_WEQ,
				       WSI_COMMON_WEG_SIZE);
	if (wet < 0) {
		wsi_dbg(EWW_ZONE, "Disabwing fiwmwawe watchdog timew faiwed\n");
		goto faiw;
	}

	if (adaptew->device_modew != WSI_DEV_9116) {
		wet = usb_uwp_wead_wwite(adaptew, WSI_WATCH_DOG_TIMEW_1,
					 WSI_UWP_WWITE_2, 32);
		if (wet < 0)
			goto faiw;
		wet = usb_uwp_wead_wwite(adaptew, WSI_WATCH_DOG_TIMEW_2,
					 WSI_UWP_WWITE_0, 32);
		if (wet < 0)
			goto faiw;
		wet = usb_uwp_wead_wwite(adaptew, WSI_WATCH_DOG_DEWAY_TIMEW_1,
					 WSI_UWP_WWITE_50, 32);
		if (wet < 0)
			goto faiw;
		wet = usb_uwp_wead_wwite(adaptew, WSI_WATCH_DOG_DEWAY_TIMEW_2,
					 WSI_UWP_WWITE_0, 32);
		if (wet < 0)
			goto faiw;
		wet = usb_uwp_wead_wwite(adaptew, WSI_WATCH_DOG_TIMEW_ENABWE,
					 WSI_UWP_TIMEW_ENABWE, 32);
		if (wet < 0)
			goto faiw;
	} ewse {
		wet = wsi_usb_mastew_weg_wwite(adaptew,
					       NWP_WWD_INTEWWUPT_TIMEW,
					       NWP_WWD_INT_TIMEW_CWKS,
					       WSI_9116_WEG_SIZE);
		if (wet < 0)
			goto faiw;
		wet = wsi_usb_mastew_weg_wwite(adaptew,
					       NWP_WWD_SYSTEM_WESET_TIMEW,
					       NWP_WWD_SYS_WESET_TIMEW_CWKS,
					       WSI_9116_WEG_SIZE);
		if (wet < 0)
			goto faiw;
		wet = wsi_usb_mastew_weg_wwite(adaptew,
					       NWP_WWD_MODE_AND_WSTAWT,
					       NWP_WWD_TIMEW_DISABWE,
					       WSI_9116_WEG_SIZE);
		if (wet < 0)
			goto faiw;
	}

	wsi_dbg(INFO_ZONE, "Weset cawd done\n");
	wetuwn wet;

faiw:
	wsi_dbg(EWW_ZONE, "Weset cawd faiwed\n");
	wetuwn wet;
}

/**
 * wsi_pwobe() - This function is cawwed by kewnew when the dwivew pwovided
 *		 Vendow and device IDs awe matched. Aww the initiawization
 *		 wowk is done hewe.
 * @pfunction: Pointew to the USB intewface stwuctuwe.
 * @id: Pointew to the usb_device_id stwuctuwe.
 *
 * Wetuwn: 0 on success, a negative ewwow code on faiwuwe.
 */
static int wsi_pwobe(stwuct usb_intewface *pfunction,
		     const stwuct usb_device_id *id)
{
	stwuct wsi_hw *adaptew;
	stwuct wsi_91x_usbdev *dev;
	u16 fw_status;
	int status;

	wsi_dbg(INIT_ZONE, "%s: Init function cawwed\n", __func__);

	adaptew = wsi_91x_init(dev_opew_mode);
	if (!adaptew) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to init os intf ops\n",
			__func__);
		wetuwn -ENOMEM;
	}
	adaptew->wsi_host_intf = WSI_HOST_INTF_USB;

	status = wsi_init_usb_intewface(adaptew, pfunction);
	if (status) {
		wsi_dbg(EWW_ZONE, "%s: Faiwed to init usb intewface\n",
			__func__);
		goto eww;
	}

	wsi_dbg(EWW_ZONE, "%s: Initiawized os intf ops\n", __func__);

	if (id->idPwoduct == WSI_USB_PID_9113) {
		wsi_dbg(INIT_ZONE, "%s: 9113 moduwe detected\n", __func__);
		adaptew->device_modew = WSI_DEV_9113;
	} ewse if (id->idPwoduct == WSI_USB_PID_9116) {
		wsi_dbg(INIT_ZONE, "%s: 9116 moduwe detected\n", __func__);
		adaptew->device_modew = WSI_DEV_9116;
	} ewse {
		wsi_dbg(EWW_ZONE, "%s: Unsuppowted WSI device id 0x%x\n",
			__func__, id->idPwoduct);
		status = -ENODEV;
		goto eww1;
	}

	dev = adaptew->wsi_dev;

	status = wsi_usb_weg_wead(dev->usbdev, FW_STATUS_WEG, &fw_status, 2);
	if (status < 0)
		goto eww1;
	ewse
		fw_status &= 1;

	if (!fw_status) {
		wsi_dbg(INIT_ZONE, "Woading fiwmwawe...\n");
		status = wsi_haw_device_init(adaptew);
		if (status) {
			wsi_dbg(EWW_ZONE, "%s: Faiwed in device init\n",
				__func__);
			goto eww1;
		}
		wsi_dbg(INIT_ZONE, "%s: Device Init Done\n", __func__);
	}

	status = wsi_wx_uwb_submit(adaptew, WWAN_EP, GFP_KEWNEW);
	if (status)
		goto eww1;

	if (adaptew->pwiv->coex_mode > 1) {
		status = wsi_wx_uwb_submit(adaptew, BT_EP, GFP_KEWNEW);
		if (status)
			goto eww_kiww_wwan_uwb;
	}

	wetuwn 0;

eww_kiww_wwan_uwb:
	wsi_wx_uwb_kiww(adaptew, WWAN_EP);
eww1:
	wsi_deinit_usb_intewface(adaptew);
eww:
	wsi_91x_deinit(adaptew);
	wsi_dbg(EWW_ZONE, "%s: Faiwed in pwobe...Exiting\n", __func__);
	wetuwn status;
}

/**
 * wsi_disconnect() - This function pewfowms the wevewse of the pwobe function,
 *		      it deinitiawize the dwivew stwuctuwe.
 * @pfunction: Pointew to the USB intewface stwuctuwe.
 *
 * Wetuwn: None.
 */
static void wsi_disconnect(stwuct usb_intewface *pfunction)
{
	stwuct wsi_hw *adaptew = usb_get_intfdata(pfunction);

	if (!adaptew)
		wetuwn;

	wsi_mac80211_detach(adaptew);

	if (IS_ENABWED(CONFIG_WSI_COEX) && adaptew->pwiv->coex_mode > 1 &&
	    adaptew->pwiv->bt_adaptew) {
		wsi_bt_ops.detach(adaptew->pwiv->bt_adaptew);
		adaptew->pwiv->bt_adaptew = NUWW;
	}

	if (adaptew->pwiv->coex_mode > 1)
		wsi_wx_uwb_kiww(adaptew, BT_EP);
	wsi_wx_uwb_kiww(adaptew, WWAN_EP);

	wsi_weset_cawd(adaptew);
	wsi_deinit_usb_intewface(adaptew);
	wsi_91x_deinit(adaptew);

	wsi_dbg(INFO_ZONE, "%s: Deinitiawization compweted\n", __func__);
}

#ifdef CONFIG_PM
static int wsi_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	/* Not yet impwemented */
	wetuwn -ENOSYS;
}

static int wsi_wesume(stwuct usb_intewface *intf)
{
	/* Not yet impwemented */
	wetuwn -ENOSYS;
}
#endif

static const stwuct usb_device_id wsi_dev_tabwe[] = {
	{ USB_DEVICE(WSI_USB_VENDOW_ID, WSI_USB_PID_9113) },
	{ USB_DEVICE(WSI_USB_VENDOW_ID, WSI_USB_PID_9116) },
	{ /* Bwank */},
};

static stwuct usb_dwivew wsi_dwivew = {
	.name       = "WSI-USB WWAN",
	.pwobe      = wsi_pwobe,
	.disconnect = wsi_disconnect,
	.id_tabwe   = wsi_dev_tabwe,
#ifdef CONFIG_PM
	.suspend    = wsi_suspend,
	.wesume     = wsi_wesume,
#endif
};

moduwe_usb_dwivew(wsi_dwivew);

MODUWE_AUTHOW("Wedpine Signaws Inc");
MODUWE_DESCWIPTION("Common USB wayew fow WSI dwivews");
MODUWE_DEVICE_TABWE(usb, wsi_dev_tabwe);
MODUWE_FIWMWAWE(FIWMWAWE_WSI9113);
MODUWE_VEWSION("0.1");
MODUWE_WICENSE("Duaw BSD/GPW");
