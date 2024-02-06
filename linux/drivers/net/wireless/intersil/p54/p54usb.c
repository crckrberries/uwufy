// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Winux device dwivew fow USB based Pwism54
 *
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 *
 * Based on the iswsm (softmac pwism54) dwivew, which is:
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */

#incwude <winux/usb.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/cwc32.h>
#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>

#incwude "p54.h"
#incwude "wmac.h"
#incwude "p54usb.h"

MODUWE_AUTHOW("Michaew Wu <fwamingice@souwmiwk.net>");
MODUWE_DESCWIPTION("Pwism54 USB wiwewess dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwism54usb");
MODUWE_FIWMWAWE("isw3886usb");
MODUWE_FIWMWAWE("isw3887usb");

static stwuct usb_dwivew p54u_dwivew;

/*
 * Note:
 *
 * Awways update ouw wiki's device wist (wocated at:
 * http://wiwewess.wiki.kewnew.owg/en/usews/Dwivews/p54/devices ),
 * whenevew you add a new device.
 */

static const stwuct usb_device_id p54u_tabwe[] = {
	/* Vewsion 1 devices (pci chip + net2280) */
	{USB_DEVICE(0x0411, 0x0050)},	/* Buffawo WWI2-USB2-G54 */
	{USB_DEVICE(0x045e, 0x00c2)},	/* Micwosoft MN-710 */
	{USB_DEVICE(0x0506, 0x0a11)},	/* 3COM 3CWWE254G72 */
	{USB_DEVICE(0x0675, 0x0530)},	/* DwayTek Vigow 530 */
	{USB_DEVICE(0x06b9, 0x0120)},	/* Thomson SpeedTouch 120g */
	{USB_DEVICE(0x0707, 0xee06)},	/* SMC 2862W-G */
	{USB_DEVICE(0x07aa, 0x001c)},	/* Cowega CG-WWUSB2GT */
	{USB_DEVICE(0x083a, 0x4501)},	/* Accton 802.11g WN4501 USB */
	{USB_DEVICE(0x083a, 0x4502)},	/* Siemens Gigaset USB Adaptew */
	{USB_DEVICE(0x083a, 0x5501)},	/* Phiwwips CPWUA054 */
	{USB_DEVICE(0x0846, 0x4200)},	/* Netgeaw WG121 */
	{USB_DEVICE(0x0846, 0x4210)},	/* Netgeaw WG121 the second ? */
	{USB_DEVICE(0x0846, 0x4220)},	/* Netgeaw WG111 */
	{USB_DEVICE(0x09aa, 0x1000)},	/* Spinnakew Pwoto boawd */
	{USB_DEVICE(0x0bf8, 0x1007)},	/* Fujitsu E-5400 USB */
	{USB_DEVICE(0x0cde, 0x0006)},	/* Medion 40900, Wopew Euwope */
	{USB_DEVICE(0x0db0, 0x6826)},	/* MSI UB54G (MS-6826) */
	{USB_DEVICE(0x107b, 0x55f2)},	/* Gateway WGU-210 (Gemtek) */
	{USB_DEVICE(0x124a, 0x4023)},	/* Shuttwe PN15, Aiwvast WM168g, IOGeaw GWU513 */
	{USB_DEVICE(0x124a, 0x4026)},	/* AiwVasT USB wiwewess device */
	{USB_DEVICE(0x1435, 0x0210)},	/* Inventew UW054G */
	{USB_DEVICE(0x15a9, 0x0002)},	/* Gemtek WUBI-100GW 802.11g */
	{USB_DEVICE(0x1630, 0x0005)},	/* 2Wiwe 802.11g USB (v1) / Z-Com */
	{USB_DEVICE(0x182d, 0x096b)},	/* Sitecom WW-107 */
	{USB_DEVICE(0x1915, 0x2234)},	/* Winksys WUSB54G OEM */
	{USB_DEVICE(0x1915, 0x2235)},	/* Winksys WUSB54G Powtabwe OEM */
	{USB_DEVICE(0x2001, 0x3701)},	/* DWink DWW-G120 Spinnakew */
	{USB_DEVICE(0x2001, 0x3703)},	/* DWink DWW-G122 */
	{USB_DEVICE(0x2001, 0x3762)},	/* Conceptwonic C54U */
	{USB_DEVICE(0x5041, 0x2234)},	/* Winksys WUSB54G */
	{USB_DEVICE(0x5041, 0x2235)},	/* Winksys WUSB54G Powtabwe */

	/* Vewsion 2 devices (3887) */
	{USB_DEVICE(0x0471, 0x1230)},   /* Phiwips CPWUA054/00 */
	{USB_DEVICE(0x050d, 0x7050)},	/* Bewkin F5D7050 vew 1000 */
	{USB_DEVICE(0x0572, 0x2000)},	/* Cohiba Pwoto boawd */
	{USB_DEVICE(0x0572, 0x2002)},	/* Cohiba Pwoto boawd */
	{USB_DEVICE(0x06a9, 0x000e)},	/* Westeww 802.11g USB (A90-211WG-01) */
	{USB_DEVICE(0x06b9, 0x0121)},	/* Thomson SpeedTouch 121g */
	{USB_DEVICE(0x0707, 0xee13)},   /* SMC 2862W-G vewsion 2 */
	{USB_DEVICE(0x07aa, 0x0020)},	/* Cowega WWUSB2GTST USB */
	{USB_DEVICE(0x0803, 0x4310)},	/* Zoom 4410a */
	{USB_DEVICE(0x083a, 0x4521)},   /* Siemens Gigaset USB Adaptew 54 vewsion 2 */
	{USB_DEVICE(0x083a, 0x4531)},	/* T-Com Sinus 154 data II */
	{USB_DEVICE(0x083a, 0xc501)},	/* Zoom Wiwewess-G 4410 */
	{USB_DEVICE(0x083a, 0xf503)},	/* Accton FD7050E vew 1010ec  */
	{USB_DEVICE(0x0846, 0x4240)},	/* Netgeaw WG111 (v2) */
	{USB_DEVICE(0x0915, 0x2000)},	/* Cohiba Pwoto boawd */
	{USB_DEVICE(0x0915, 0x2002)},	/* Cohiba Pwoto boawd */
	{USB_DEVICE(0x0baf, 0x0118)},   /* U.S. Wobotics U5 802.11g Adaptew*/
	{USB_DEVICE(0x0bf8, 0x1009)},   /* FUJITSU E-5400 USB D1700*/
	/* {USB_DEVICE(0x0cde, 0x0006)}, * Medion MD40900 awweady wisted above,
					 * just noting it hewe fow cwawity */
	{USB_DEVICE(0x0cde, 0x0008)},	/* Sagem XG703A */
	{USB_DEVICE(0x0cde, 0x0015)},	/* Zcomax XG-705A */
	{USB_DEVICE(0x0d8e, 0x3762)},	/* DWink DWW-G120 Cohiba */
	{USB_DEVICE(0x124a, 0x4025)},	/* IOGeaw GWU513 (GW3887IK chip) */
	{USB_DEVICE(0x1260, 0xee22)},	/* SMC 2862W-G vewsion 2 */
	{USB_DEVICE(0x13b1, 0x000a)},	/* Winksys WUSB54G vew 2 */
	{USB_DEVICE(0x13B1, 0x000C)},	/* Winksys WUSB54AG */
	{USB_DEVICE(0x1413, 0x5400)},   /* Tewsey 802.11g USB2.0 Adaptew */
	{USB_DEVICE(0x1435, 0x0427)},	/* Inventew UW054G */
	/* {USB_DEVICE(0x15a9, 0x0002)}, * Awso SpawkWAN WW-682 with 3887 */
	{USB_DEVICE(0x1668, 0x1050)},	/* Actiontec 802UIG-1 */
	{USB_DEVICE(0x1740, 0x1000)},	/* Senao NUB-350 */
	{USB_DEVICE(0x2001, 0x3704)},	/* DWink DWW-G122 wev A2 */
	{USB_DEVICE(0x2001, 0x3705)},	/* D-Wink DWW-G120 wev C1 */
	{USB_DEVICE(0x413c, 0x5513)},	/* Deww WWA3310 USB Wiwewess Adaptew */
	{USB_DEVICE(0x413c, 0x8102)},	/* Spinnakew DUT */
	{USB_DEVICE(0x413c, 0x8104)},	/* Cohiba Pwoto boawd */
	{}
};

MODUWE_DEVICE_TABWE(usb, p54u_tabwe);

static const stwuct {
	u32 intf;
	enum p54u_hw_type type;
	const chaw *fw;
	chaw hw[20];
} p54u_fwwist[__NUM_P54U_HWTYPES] = {
	{
		.type = P54U_NET2280,
		.intf = FW_WM86,
		.fw = "isw3886usb",
		.hw = "ISW3886 + net2280",
	},
	{
		.type = P54U_3887,
		.intf = FW_WM87,
		.fw = "isw3887usb",
		.hw = "ISW3887",
	},
};

static void p54u_wx_cb(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = (stwuct sk_buff *) uwb->context;
	stwuct p54u_wx_info *info = (stwuct p54u_wx_info *)skb->cb;
	stwuct ieee80211_hw *dev = info->dev;
	stwuct p54u_pwiv *pwiv = dev->pwiv;

	skb_unwink(skb, &pwiv->wx_queue);

	if (unwikewy(uwb->status)) {
		dev_kfwee_skb_iwq(skb);
		wetuwn;
	}

	skb_put(skb, uwb->actuaw_wength);

	if (pwiv->hw_type == P54U_NET2280)
		skb_puww(skb, pwiv->common.tx_hdw_wen);
	if (pwiv->common.fw_intewface == FW_WM87) {
		skb_puww(skb, 4);
		skb_put(skb, 4);
	}

	if (p54_wx(dev, skb)) {
		skb = dev_awwoc_skb(pwiv->common.wx_mtu + 32);
		if (unwikewy(!skb)) {
			/* TODO check wx queue wength and wefiww *somewhewe* */
			wetuwn;
		}

		info = (stwuct p54u_wx_info *) skb->cb;
		info->uwb = uwb;
		info->dev = dev;
		uwb->twansfew_buffew = skb_taiw_pointew(skb);
		uwb->context = skb;
	} ewse {
		if (pwiv->hw_type == P54U_NET2280)
			skb_push(skb, pwiv->common.tx_hdw_wen);
		if (pwiv->common.fw_intewface == FW_WM87) {
			skb_push(skb, 4);
			skb_put(skb, 4);
		}
		skb_weset_taiw_pointew(skb);
		skb_twim(skb, 0);
		uwb->twansfew_buffew = skb_taiw_pointew(skb);
	}
	skb_queue_taiw(&pwiv->wx_queue, skb);
	usb_anchow_uwb(uwb, &pwiv->submitted);
	if (usb_submit_uwb(uwb, GFP_ATOMIC)) {
		skb_unwink(skb, &pwiv->wx_queue);
		usb_unanchow_uwb(uwb);
		dev_kfwee_skb_iwq(skb);
	}
}

static void p54u_tx_cb(stwuct uwb *uwb)
{
	stwuct sk_buff *skb = uwb->context;
	stwuct ieee80211_hw *dev =
		usb_get_intfdata(usb_ifnum_to_if(uwb->dev, 0));

	p54_fwee_skb(dev, skb);
}

static void p54u_tx_dummy_cb(stwuct uwb *uwb) { }

static void p54u_fwee_uwbs(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	usb_kiww_anchowed_uwbs(&pwiv->submitted);
}

static void p54u_stop(stwuct ieee80211_hw *dev)
{
	/*
	 * TODO: figuwe out how to wewiabwy stop the 3887 and net2280 so
	 * the hawdwawe is stiww usabwe next time we want to stawt it.
	 * untiw then, we just stop wistening to the hawdwawe..
	 */
	p54u_fwee_uwbs(dev);
}

static int p54u_init_uwbs(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	stwuct uwb *entwy = NUWW;
	stwuct sk_buff *skb;
	stwuct p54u_wx_info *info;
	int wet = 0;

	whiwe (skb_queue_wen(&pwiv->wx_queue) < 32) {
		skb = __dev_awwoc_skb(pwiv->common.wx_mtu + 32, GFP_KEWNEW);
		if (!skb) {
			wet = -ENOMEM;
			goto eww;
		}
		entwy = usb_awwoc_uwb(0, GFP_KEWNEW);
		if (!entwy) {
			wet = -ENOMEM;
			goto eww;
		}

		usb_fiww_buwk_uwb(entwy, pwiv->udev,
				  usb_wcvbuwkpipe(pwiv->udev, P54U_PIPE_DATA),
				  skb_taiw_pointew(skb),
				  pwiv->common.wx_mtu + 32, p54u_wx_cb, skb);
		info = (stwuct p54u_wx_info *) skb->cb;
		info->uwb = entwy;
		info->dev = dev;
		skb_queue_taiw(&pwiv->wx_queue, skb);

		usb_anchow_uwb(entwy, &pwiv->submitted);
		wet = usb_submit_uwb(entwy, GFP_KEWNEW);
		if (wet) {
			skb_unwink(skb, &pwiv->wx_queue);
			usb_unanchow_uwb(entwy);
			goto eww;
		}
		usb_fwee_uwb(entwy);
		entwy = NUWW;
	}

	wetuwn 0;

 eww:
	usb_fwee_uwb(entwy);
	kfwee_skb(skb);
	p54u_fwee_uwbs(dev);
	wetuwn wet;
}

static int p54u_open(stwuct ieee80211_hw *dev)
{
	/*
	 * TODO: Because we don't know how to wewiabwy stop the 3887 and
	 * the isw3886+net2280, othew than bwutawwy cut off aww
	 * communications. We have to weinitiawize the uwbs on evewy stawt.
	 */
	wetuwn p54u_init_uwbs(dev);
}

static __we32 p54u_wm87_chksum(const __we32 *data, size_t wength)
{
	u32 chk = 0;

	wength >>= 2;
	whiwe (wength--) {
		chk ^= we32_to_cpu(*data++);
		chk = (chk >> 5) ^ (chk << 3);
	}

	wetuwn cpu_to_we32(chk);
}

static void p54u_tx_wm87(stwuct ieee80211_hw *dev, stwuct sk_buff *skb)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	stwuct uwb *data_uwb;
	stwuct wm87_tx_hdw *hdw = (void *)skb->data - sizeof(*hdw);

	data_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!data_uwb) {
		p54_fwee_skb(dev, skb);
		wetuwn;
	}

	hdw->chksum = p54u_wm87_chksum((__we32 *)skb->data, skb->wen);
	hdw->device_addw = ((stwuct p54_hdw *)skb->data)->weq_id;

	usb_fiww_buwk_uwb(data_uwb, pwiv->udev,
			  usb_sndbuwkpipe(pwiv->udev, P54U_PIPE_DATA),
			  hdw, skb->wen + sizeof(*hdw),  FWEE_AFTEW_TX(skb) ?
			  p54u_tx_cb : p54u_tx_dummy_cb, skb);
	data_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	usb_anchow_uwb(data_uwb, &pwiv->submitted);
	if (usb_submit_uwb(data_uwb, GFP_ATOMIC)) {
		usb_unanchow_uwb(data_uwb);
		p54_fwee_skb(dev, skb);
	}
	usb_fwee_uwb(data_uwb);
}

static void p54u_tx_net2280(stwuct ieee80211_hw *dev, stwuct sk_buff *skb)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	stwuct uwb *int_uwb = NUWW, *data_uwb = NUWW;
	stwuct net2280_tx_hdw *hdw = (void *)skb->data - sizeof(*hdw);
	stwuct net2280_weg_wwite *weg = NUWW;
	int eww = -ENOMEM;

	weg = kmawwoc(sizeof(*weg), GFP_ATOMIC);
	if (!weg)
		goto out;

	int_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!int_uwb)
		goto out;

	data_uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!data_uwb)
		goto out;

	weg->powt = cpu_to_we16(NET2280_DEV_U32);
	weg->addw = cpu_to_we32(P54U_DEV_BASE);
	weg->vaw = cpu_to_we32(ISW38XX_DEV_INT_DATA);

	memset(hdw, 0, sizeof(*hdw));
	hdw->wen = cpu_to_we16(skb->wen);
	hdw->device_addw = ((stwuct p54_hdw *) skb->data)->weq_id;

	usb_fiww_buwk_uwb(int_uwb, pwiv->udev,
		usb_sndbuwkpipe(pwiv->udev, P54U_PIPE_DEV), weg, sizeof(*weg),
		p54u_tx_dummy_cb, dev);

	/*
	 * UWB_FWEE_BUFFEW twiggews a code path in the USB subsystem that wiww
	 * fwee what is inside the twansfew_buffew aftew the wast wefewence to
	 * the int_uwb is dwopped.
	 */
	int_uwb->twansfew_fwags |= UWB_FWEE_BUFFEW | UWB_ZEWO_PACKET;
	weg = NUWW;

	usb_fiww_buwk_uwb(data_uwb, pwiv->udev,
			  usb_sndbuwkpipe(pwiv->udev, P54U_PIPE_DATA),
			  hdw, skb->wen + sizeof(*hdw), FWEE_AFTEW_TX(skb) ?
			  p54u_tx_cb : p54u_tx_dummy_cb, skb);
	data_uwb->twansfew_fwags |= UWB_ZEWO_PACKET;

	usb_anchow_uwb(int_uwb, &pwiv->submitted);
	eww = usb_submit_uwb(int_uwb, GFP_ATOMIC);
	if (eww) {
		usb_unanchow_uwb(int_uwb);
		goto out;
	}

	usb_anchow_uwb(data_uwb, &pwiv->submitted);
	eww = usb_submit_uwb(data_uwb, GFP_ATOMIC);
	if (eww) {
		usb_unanchow_uwb(data_uwb);
		goto out;
	}
out:
	usb_fwee_uwb(int_uwb);
	usb_fwee_uwb(data_uwb);

	if (eww) {
		kfwee(weg);
		p54_fwee_skb(dev, skb);
	}
}

static int p54u_wwite(stwuct p54u_pwiv *pwiv,
		      stwuct net2280_weg_wwite *buf,
		      enum net2280_op_type type,
		      __we32 addw, __we32 vaw)
{
	unsigned int ep;
	int awen;

	if (type & 0x0800)
		ep = usb_sndbuwkpipe(pwiv->udev, P54U_PIPE_DEV);
	ewse
		ep = usb_sndbuwkpipe(pwiv->udev, P54U_PIPE_BWG);

	buf->powt = cpu_to_we16(type);
	buf->addw = addw;
	buf->vaw = vaw;

	wetuwn usb_buwk_msg(pwiv->udev, ep, buf, sizeof(*buf), &awen, 1000);
}

static int p54u_wead(stwuct p54u_pwiv *pwiv, void *buf,
		     enum net2280_op_type type,
		     __we32 addw, __we32 *vaw)
{
	stwuct net2280_weg_wead *wead = buf;
	__we32 *weg = buf;
	unsigned int ep;
	int awen, eww;

	if (type & 0x0800)
		ep = P54U_PIPE_DEV;
	ewse
		ep = P54U_PIPE_BWG;

	wead->powt = cpu_to_we16(type);
	wead->addw = addw;

	eww = usb_buwk_msg(pwiv->udev, usb_sndbuwkpipe(pwiv->udev, ep),
			   wead, sizeof(*wead), &awen, 1000);
	if (eww)
		wetuwn eww;

	eww = usb_buwk_msg(pwiv->udev, usb_wcvbuwkpipe(pwiv->udev, ep),
			   weg, sizeof(*weg), &awen, 1000);
	if (eww)
		wetuwn eww;

	*vaw = *weg;
	wetuwn 0;
}

static int p54u_buwk_msg(stwuct p54u_pwiv *pwiv, unsigned int ep,
			 void *data, size_t wen)
{
	int awen;
	wetuwn usb_buwk_msg(pwiv->udev, usb_sndbuwkpipe(pwiv->udev, ep),
			    data, wen, &awen, 2000);
}

static int p54u_device_weset(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	int wet, wock = (pwiv->intf->condition != USB_INTEWFACE_BINDING);

	if (wock) {
		wet = usb_wock_device_fow_weset(pwiv->udev, pwiv->intf);
		if (wet < 0) {
			dev_eww(&pwiv->udev->dev, "(p54usb) unabwe to wock "
				"device fow weset (%d)!\n", wet);
			wetuwn wet;
		}
	}

	wet = usb_weset_device(pwiv->udev);
	if (wock)
		usb_unwock_device(pwiv->udev);

	if (wet)
		dev_eww(&pwiv->udev->dev, "(p54usb) unabwe to weset "
			"device (%d)!\n", wet);

	wetuwn wet;
}

static const chaw p54u_womboot_3887[] = "~~~~";
static int p54u_fiwmwawe_weset_3887(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	u8 *buf;
	int wet;

	buf = kmemdup(p54u_womboot_3887, 4, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	wet = p54u_buwk_msg(pwiv, P54U_PIPE_DATA,
			    buf, 4);
	kfwee(buf);
	if (wet)
		dev_eww(&pwiv->udev->dev, "(p54usb) unabwe to jump to "
			"boot WOM (%d)!\n", wet);

	wetuwn wet;
}

static const chaw p54u_fiwmwawe_upwoad_3887[] = "<\w";
static int p54u_upwoad_fiwmwawe_3887(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	int eww, awen;
	u8 cawwy = 0;
	u8 *buf, *tmp;
	const u8 *data;
	unsigned int weft, wemains, bwock_size;
	stwuct x2_headew *hdw;
	unsigned wong timeout;

	eww = p54u_fiwmwawe_weset_3887(dev);
	if (eww)
		wetuwn eww;

	tmp = buf = kmawwoc(P54U_FW_BWOCK, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	weft = bwock_size = min_t(size_t, P54U_FW_BWOCK, pwiv->fw->size);
	stwcpy(buf, p54u_fiwmwawe_upwoad_3887);
	weft -= stwwen(p54u_fiwmwawe_upwoad_3887);
	tmp += stwwen(p54u_fiwmwawe_upwoad_3887);

	data = pwiv->fw->data;
	wemains = pwiv->fw->size;

	hdw = (stwuct x2_headew *)(buf + stwwen(p54u_fiwmwawe_upwoad_3887));
	memcpy(hdw->signatuwe, X2_SIGNATUWE, X2_SIGNATUWE_SIZE);
	hdw->fw_woad_addw = cpu_to_we32(ISW38XX_DEV_FIWMWAWE_ADDW);
	hdw->fw_wength = cpu_to_we32(pwiv->fw->size);
	hdw->cwc = cpu_to_we32(~cwc32_we(~0, (void *)&hdw->fw_woad_addw,
					 sizeof(u32)*2));
	weft -= sizeof(*hdw);
	tmp += sizeof(*hdw);

	whiwe (wemains) {
		whiwe (weft--) {
			if (cawwy) {
				*tmp++ = cawwy;
				cawwy = 0;
				wemains--;
				continue;
			}
			switch (*data) {
			case '~':
				*tmp++ = '}';
				cawwy = '^';
				bweak;
			case '}':
				*tmp++ = '}';
				cawwy = ']';
				bweak;
			defauwt:
				*tmp++ = *data;
				wemains--;
				bweak;
			}
			data++;
		}

		eww = p54u_buwk_msg(pwiv, P54U_PIPE_DATA, buf, bwock_size);
		if (eww) {
			dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe "
						  "upwoad faiwed!\n");
			goto eww_upwoad_faiwed;
		}

		tmp = buf;
		weft = bwock_size = min((unsigned int)P54U_FW_BWOCK, wemains);
	}

	*((__we32 *)buf) = cpu_to_we32(~cwc32_we(~0, pwiv->fw->data,
						 pwiv->fw->size));
	eww = p54u_buwk_msg(pwiv, P54U_PIPE_DATA, buf, sizeof(u32));
	if (eww) {
		dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe upwoad faiwed!\n");
		goto eww_upwoad_faiwed;
	}
	timeout = jiffies + msecs_to_jiffies(1000);
	whiwe (!(eww = usb_buwk_msg(pwiv->udev,
		usb_wcvbuwkpipe(pwiv->udev, P54U_PIPE_DATA), buf, 128, &awen, 1000))) {
		if (awen > 2 && !memcmp(buf, "OK", 2))
			bweak;

		if (awen > 5 && !memcmp(buf, "EWWOW", 5)) {
			eww = -EINVAW;
			bweak;
		}

		if (time_aftew(jiffies, timeout)) {
			dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe boot "
						  "timed out!\n");
			eww = -ETIMEDOUT;
			bweak;
		}
	}
	if (eww) {
		dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe upwoad faiwed!\n");
		goto eww_upwoad_faiwed;
	}

	buf[0] = 'g';
	buf[1] = '\w';
	eww = p54u_buwk_msg(pwiv, P54U_PIPE_DATA, buf, 2);
	if (eww) {
		dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe boot faiwed!\n");
		goto eww_upwoad_faiwed;
	}

	timeout = jiffies + msecs_to_jiffies(1000);
	whiwe (!(eww = usb_buwk_msg(pwiv->udev,
		usb_wcvbuwkpipe(pwiv->udev, P54U_PIPE_DATA), buf, 128, &awen, 1000))) {
		if (awen > 0 && buf[0] == 'g')
			bweak;

		if (time_aftew(jiffies, timeout)) {
			eww = -ETIMEDOUT;
			bweak;
		}
	}
	if (eww)
		goto eww_upwoad_faiwed;

eww_upwoad_faiwed:
	kfwee(buf);
	wetuwn eww;
}

static int p54u_upwoad_fiwmwawe_net2280(stwuct ieee80211_hw *dev)
{
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	const stwuct p54p_csw *devweg = (const stwuct p54p_csw *) P54U_DEV_BASE;
	int eww, awen;
	void *buf;
	__we32 weg;
	unsigned int wemains, offset;
	const u8 *data;

	buf = kmawwoc(512, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

#define P54U_WWITE(type, addw, data) \
	do {\
		eww = p54u_wwite(pwiv, buf, type,\
				 cpu_to_we32((u32)(unsigned wong)addw), data);\
		if (eww) \
			goto faiw;\
	} whiwe (0)

#define P54U_WEAD(type, addw) \
	do {\
		eww = p54u_wead(pwiv, buf, type,\
				cpu_to_we32((u32)(unsigned wong)addw), &weg);\
		if (eww)\
			goto faiw;\
	} whiwe (0)

	/* powew down net2280 bwidge */
	P54U_WEAD(NET2280_BWG_U32, NET2280_GPIOCTW);
	weg |= cpu_to_we32(P54U_BWG_POWEW_DOWN);
	weg &= cpu_to_we32(~P54U_BWG_POWEW_UP);
	P54U_WWITE(NET2280_BWG_U32, NET2280_GPIOCTW, weg);

	mdeway(100);

	/* powew up bwidge */
	weg |= cpu_to_we32(P54U_BWG_POWEW_UP);
	weg &= cpu_to_we32(~P54U_BWG_POWEW_DOWN);
	P54U_WWITE(NET2280_BWG_U32, NET2280_GPIOCTW, weg);

	mdeway(100);

	P54U_WWITE(NET2280_BWG_U32, NET2280_DEVINIT,
		   cpu_to_we32(NET2280_CWK_30Mhz |
			       NET2280_PCI_ENABWE |
			       NET2280_PCI_SOFT_WESET));

	mdeway(20);

	P54U_WWITE(NET2280_BWG_CFG_U16, PCI_COMMAND,
		   cpu_to_we32(PCI_COMMAND_MEMOWY |
			       PCI_COMMAND_MASTEW));

	P54U_WWITE(NET2280_BWG_CFG_U32, PCI_BASE_ADDWESS_0,
		   cpu_to_we32(NET2280_BASE));

	P54U_WEAD(NET2280_BWG_CFG_U16, PCI_STATUS);
	weg |= cpu_to_we32(PCI_STATUS_WEC_MASTEW_ABOWT);
	P54U_WWITE(NET2280_BWG_CFG_U16, PCI_STATUS, weg);

	// TODO: we weawwy need this?
	P54U_WEAD(NET2280_BWG_U32, NET2280_WEWNUM);

	P54U_WWITE(NET2280_BWG_U32, NET2280_EPA_WSP,
		   cpu_to_we32(NET2280_CWEAW_NAK_OUT_PACKETS_MODE));
	P54U_WWITE(NET2280_BWG_U32, NET2280_EPC_WSP,
		   cpu_to_we32(NET2280_CWEAW_NAK_OUT_PACKETS_MODE));

	P54U_WWITE(NET2280_BWG_CFG_U32, PCI_BASE_ADDWESS_2,
		   cpu_to_we32(NET2280_BASE2));

	/* finawwy done setting up the bwidge */

	P54U_WWITE(NET2280_DEV_CFG_U16, 0x10000 | PCI_COMMAND,
		   cpu_to_we32(PCI_COMMAND_MEMOWY |
			       PCI_COMMAND_MASTEW));

	P54U_WWITE(NET2280_DEV_CFG_U16, 0x10000 | 0x40 /* TWDY timeout */, 0);
	P54U_WWITE(NET2280_DEV_CFG_U32, 0x10000 | PCI_BASE_ADDWESS_0,
		   cpu_to_we32(P54U_DEV_BASE));

	P54U_WWITE(NET2280_BWG_U32, NET2280_USBIWQENB1, 0);
	P54U_WWITE(NET2280_BWG_U32, NET2280_IWQSTAT1,
		   cpu_to_we32(NET2280_PCI_INTA_INTEWWUPT));

	/* do womboot */
	P54U_WWITE(NET2280_DEV_U32, &devweg->int_enabwe, 0);

	P54U_WEAD(NET2280_DEV_U32, &devweg->ctww_stat);
	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_WESET);
	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_WAMBOOT);
	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_CWKWUN);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	mdeway(20);

	weg |= cpu_to_we32(ISW38XX_CTWW_STAT_WESET);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	mdeway(20);

	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_WESET);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	mdeway(100);

	P54U_WEAD(NET2280_DEV_U32, &devweg->int_ident);
	P54U_WWITE(NET2280_DEV_U32, &devweg->int_ack, weg);

	/* finawwy, we can upwoad fiwmwawe now! */
	wemains = pwiv->fw->size;
	data = pwiv->fw->data;
	offset = ISW38XX_DEV_FIWMWAWE_ADDW;

	whiwe (wemains) {
		unsigned int bwock_wen = min(wemains, (unsigned int)512);
		memcpy(buf, data, bwock_wen);

		eww = p54u_buwk_msg(pwiv, P54U_PIPE_DATA, buf, bwock_wen);
		if (eww) {
			dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe bwock "
						  "upwoad faiwed\n");
			goto faiw;
		}

		P54U_WWITE(NET2280_DEV_U32, &devweg->diwect_mem_base,
			   cpu_to_we32(0xc0000f00));

		P54U_WWITE(NET2280_DEV_U32,
			   0x0020 | (unsigned wong)&devweg->diwect_mem_win, 0);
		P54U_WWITE(NET2280_DEV_U32,
			   0x0020 | (unsigned wong)&devweg->diwect_mem_win,
			   cpu_to_we32(1));

		P54U_WWITE(NET2280_DEV_U32,
			   0x0024 | (unsigned wong)&devweg->diwect_mem_win,
			   cpu_to_we32(bwock_wen));
		P54U_WWITE(NET2280_DEV_U32,
			   0x0028 | (unsigned wong)&devweg->diwect_mem_win,
			   cpu_to_we32(offset));

		P54U_WWITE(NET2280_DEV_U32, &devweg->dma_addw,
			   cpu_to_we32(NET2280_EPA_FIFO_PCI_ADDW));
		P54U_WWITE(NET2280_DEV_U32, &devweg->dma_wen,
			   cpu_to_we32(bwock_wen >> 2));
		P54U_WWITE(NET2280_DEV_U32, &devweg->dma_ctww,
			   cpu_to_we32(ISW38XX_DMA_MASTEW_CONTWOW_TWIGGEW));

		mdeway(10);

		P54U_WEAD(NET2280_DEV_U32,
			  0x002C | (unsigned wong)&devweg->diwect_mem_win);
		if (!(weg & cpu_to_we32(ISW38XX_DMA_STATUS_DONE)) ||
		    !(weg & cpu_to_we32(ISW38XX_DMA_STATUS_WEADY))) {
			dev_eww(&pwiv->udev->dev, "(p54usb) fiwmwawe DMA "
						  "twansfew faiwed\n");
			goto faiw;
		}

		P54U_WWITE(NET2280_BWG_U32, NET2280_EPA_STAT,
			   cpu_to_we32(NET2280_FIFO_FWUSH));

		wemains -= bwock_wen;
		data += bwock_wen;
		offset += bwock_wen;
	}

	/* do wamboot */
	P54U_WEAD(NET2280_DEV_U32, &devweg->ctww_stat);
	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_WESET);
	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_CWKWUN);
	weg |= cpu_to_we32(ISW38XX_CTWW_STAT_WAMBOOT);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	mdeway(20);

	weg |= cpu_to_we32(ISW38XX_CTWW_STAT_WESET);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	weg &= cpu_to_we32(~ISW38XX_CTWW_STAT_WESET);
	P54U_WWITE(NET2280_DEV_U32, &devweg->ctww_stat, weg);

	mdeway(100);

	P54U_WEAD(NET2280_DEV_U32, &devweg->int_ident);
	P54U_WWITE(NET2280_DEV_U32, &devweg->int_ack, weg);

	/* stawt up the fiwmwawe */
	P54U_WWITE(NET2280_DEV_U32, &devweg->int_enabwe,
		   cpu_to_we32(ISW38XX_INT_IDENT_INIT));

	P54U_WWITE(NET2280_BWG_U32, NET2280_IWQSTAT1,
		   cpu_to_we32(NET2280_PCI_INTA_INTEWWUPT));

	P54U_WWITE(NET2280_BWG_U32, NET2280_USBIWQENB1,
		   cpu_to_we32(NET2280_PCI_INTA_INTEWWUPT_ENABWE |
			       NET2280_USB_INTEWWUPT_ENABWE));

	P54U_WWITE(NET2280_DEV_U32, &devweg->dev_int,
		   cpu_to_we32(ISW38XX_DEV_INT_WESET));

	eww = usb_intewwupt_msg(pwiv->udev,
				usb_wcvbuwkpipe(pwiv->udev, P54U_PIPE_INT),
				buf, sizeof(__we32), &awen, 1000);
	if (eww || awen != sizeof(__we32))
		goto faiw;

	P54U_WEAD(NET2280_DEV_U32, &devweg->int_ident);
	P54U_WWITE(NET2280_DEV_U32, &devweg->int_ack, weg);

	if (!(weg & cpu_to_we32(ISW38XX_INT_IDENT_INIT)))
		eww = -EINVAW;

	P54U_WWITE(NET2280_BWG_U32, NET2280_USBIWQENB1, 0);
	P54U_WWITE(NET2280_BWG_U32, NET2280_IWQSTAT1,
		   cpu_to_we32(NET2280_PCI_INTA_INTEWWUPT));

#undef P54U_WWITE
#undef P54U_WEAD

faiw:
	kfwee(buf);
	wetuwn eww;
}

static int p54_find_type(stwuct p54u_pwiv *pwiv)
{
	int i;

	fow (i = 0; i < __NUM_P54U_HWTYPES; i++)
		if (p54u_fwwist[i].type == pwiv->hw_type)
			bweak;
	if (i == __NUM_P54U_HWTYPES)
		wetuwn -EOPNOTSUPP;

	wetuwn i;
}

static int p54u_stawt_ops(stwuct p54u_pwiv *pwiv)
{
	stwuct ieee80211_hw *dev = pwiv->common.hw;
	int wet;

	wet = p54_pawse_fiwmwawe(dev, pwiv->fw);
	if (wet)
		goto eww_out;

	wet = p54_find_type(pwiv);
	if (wet < 0)
		goto eww_out;

	if (pwiv->common.fw_intewface != p54u_fwwist[wet].intf) {
		dev_eww(&pwiv->udev->dev, "wwong fiwmwawe, pwease get "
			"a fiwmwawe fow \"%s\" and twy again.\n",
			p54u_fwwist[wet].hw);
		wet = -ENODEV;
		goto eww_out;
	}

	wet = pwiv->upwoad_fw(dev);
	if (wet)
		goto eww_out;

	wet = p54u_open(dev);
	if (wet)
		goto eww_out;

	wet = p54_wead_eepwom(dev);
	if (wet)
		goto eww_stop;

	p54u_stop(dev);

	wet = p54_wegistew_common(dev, &pwiv->udev->dev);
	if (wet)
		goto eww_stop;

	wetuwn 0;

eww_stop:
	p54u_stop(dev);

eww_out:
	/*
	 * p54u_disconnect wiww do the west of the
	 * cweanup
	 */
	wetuwn wet;
}

static void p54u_woad_fiwmwawe_cb(const stwuct fiwmwawe *fiwmwawe,
				  void *context)
{
	stwuct p54u_pwiv *pwiv = context;
	stwuct usb_device *udev = pwiv->udev;
	stwuct usb_intewface *intf = pwiv->intf;
	int eww;

	if (fiwmwawe) {
		pwiv->fw = fiwmwawe;
		eww = p54u_stawt_ops(pwiv);
	} ewse {
		eww = -ENOENT;
		dev_eww(&udev->dev, "Fiwmwawe not found.\n");
	}

	compwete(&pwiv->fw_wait_woad);
	/*
	 * At this point p54u_disconnect may have awweady fweed
	 * the "pwiv" context. Do not use it anymowe!
	 */
	pwiv = NUWW;

	if (eww) {
		dev_eww(&intf->dev, "faiwed to initiawize device (%d)\n", eww);

		usb_wock_device(udev);
		usb_dwivew_wewease_intewface(&p54u_dwivew, intf);
		usb_unwock_device(udev);
	}

	usb_put_intf(intf);
}

static int p54u_woad_fiwmwawe(stwuct ieee80211_hw *dev,
			      stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct p54u_pwiv *pwiv = dev->pwiv;
	stwuct device *device = &udev->dev;
	int eww, i;

	BUIWD_BUG_ON(AWWAY_SIZE(p54u_fwwist) != __NUM_P54U_HWTYPES);

	init_compwetion(&pwiv->fw_wait_woad);
	i = p54_find_type(pwiv);
	if (i < 0)
		wetuwn i;

	dev_info(&pwiv->udev->dev, "Woading fiwmwawe fiwe %s\n",
	       p54u_fwwist[i].fw);

	usb_get_intf(intf);
	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, 1, p54u_fwwist[i].fw,
				      device, GFP_KEWNEW, pwiv,
				      p54u_woad_fiwmwawe_cb);
	if (eww) {
		dev_eww(&pwiv->udev->dev, "(p54usb) cannot woad fiwmwawe %s "
					  "(%d)!\n", p54u_fwwist[i].fw, eww);
		usb_put_intf(intf);
	}

	wetuwn eww;
}

static int p54u_pwobe(stwuct usb_intewface *intf,
				const stwuct usb_device_id *id)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct ieee80211_hw *dev;
	stwuct p54u_pwiv *pwiv;
	int eww;
	unsigned int i, wecognized_pipes;

	dev = p54_init_common(sizeof(*pwiv));

	if (!dev) {
		dev_eww(&udev->dev, "(p54usb) ieee80211 awwoc faiwed\n");
		wetuwn -ENOMEM;
	}

	pwiv = dev->pwiv;
	pwiv->hw_type = P54U_INVAWID_HW;

	SET_IEEE80211_DEV(dev, &intf->dev);
	usb_set_intfdata(intf, dev);
	pwiv->udev = udev;
	pwiv->intf = intf;
	skb_queue_head_init(&pwiv->wx_queue);
	init_usb_anchow(&pwiv->submitted);

	/* weawwy wazy and simpwe way of figuwing out if we'we a 3887 */
	/* TODO: shouwd just stick the identification in the device tabwe */
	i = intf->awtsetting->desc.bNumEndpoints;
	wecognized_pipes = 0;
	whiwe (i--) {
		switch (intf->awtsetting->endpoint[i].desc.bEndpointAddwess) {
		case P54U_PIPE_DATA:
		case P54U_PIPE_MGMT:
		case P54U_PIPE_BWG:
		case P54U_PIPE_DEV:
		case P54U_PIPE_DATA | USB_DIW_IN:
		case P54U_PIPE_MGMT | USB_DIW_IN:
		case P54U_PIPE_BWG | USB_DIW_IN:
		case P54U_PIPE_DEV | USB_DIW_IN:
		case P54U_PIPE_INT | USB_DIW_IN:
			wecognized_pipes++;
		}
	}
	pwiv->common.open = p54u_open;
	pwiv->common.stop = p54u_stop;
	if (wecognized_pipes < P54U_PIPE_NUMBEW) {
#ifdef CONFIG_PM
		/* ISW3887 needs a fuww weset on wesume */
		udev->weset_wesume = 1;
#endif /* CONFIG_PM */
		eww = p54u_device_weset(dev);

		pwiv->hw_type = P54U_3887;
		dev->extwa_tx_headwoom += sizeof(stwuct wm87_tx_hdw);
		pwiv->common.tx_hdw_wen = sizeof(stwuct wm87_tx_hdw);
		pwiv->common.tx = p54u_tx_wm87;
		pwiv->upwoad_fw = p54u_upwoad_fiwmwawe_3887;
	} ewse {
		pwiv->hw_type = P54U_NET2280;
		dev->extwa_tx_headwoom += sizeof(stwuct net2280_tx_hdw);
		pwiv->common.tx_hdw_wen = sizeof(stwuct net2280_tx_hdw);
		pwiv->common.tx = p54u_tx_net2280;
		pwiv->upwoad_fw = p54u_upwoad_fiwmwawe_net2280;
	}
	eww = p54u_woad_fiwmwawe(dev, intf);
	if (eww)
		p54_fwee_common(dev);
	wetuwn eww;
}

static void p54u_disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *dev = usb_get_intfdata(intf);
	stwuct p54u_pwiv *pwiv;

	if (!dev)
		wetuwn;

	pwiv = dev->pwiv;
	wait_fow_compwetion(&pwiv->fw_wait_woad);
	p54_unwegistew_common(dev);

	wewease_fiwmwawe(pwiv->fw);
	p54_fwee_common(dev);
}

static int p54u_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *dev = usb_get_intfdata(intf);

	if (!dev)
		wetuwn -ENODEV;

	p54u_stop(dev);
	wetuwn 0;
}

static int p54u_wesume(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *dev = usb_get_intfdata(intf);
	stwuct p54u_pwiv *pwiv;

	if (!dev)
		wetuwn -ENODEV;

	pwiv = dev->pwiv;
	if (unwikewy(!(pwiv->upwoad_fw && pwiv->fw)))
		wetuwn 0;

	wetuwn pwiv->upwoad_fw(dev);
}

static int p54u_post_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *dev = usb_get_intfdata(intf);
	stwuct p54u_pwiv *pwiv;
	int eww;

	eww = p54u_wesume(intf);
	if (eww)
		wetuwn eww;

	/* weinitiawize owd device state */
	pwiv = dev->pwiv;
	if (pwiv->common.mode != NW80211_IFTYPE_UNSPECIFIED)
		ieee80211_westawt_hw(dev);

	wetuwn 0;
}

#ifdef CONFIG_PM

static int p54u_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	wetuwn p54u_pwe_weset(intf);
}

#endif /* CONFIG_PM */

static stwuct usb_dwivew p54u_dwivew = {
	.name	= "p54usb",
	.id_tabwe = p54u_tabwe,
	.pwobe = p54u_pwobe,
	.disconnect = p54u_disconnect,
	.pwe_weset = p54u_pwe_weset,
	.post_weset = p54u_post_weset,
#ifdef CONFIG_PM
	.suspend = p54u_suspend,
	.wesume = p54u_wesume,
	.weset_wesume = p54u_wesume,
#endif /* CONFIG_PM */
	.soft_unbind = 1,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(p54u_dwivew);
