// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Stweamzap Wemote Contwow dwivew
 *
 * Copywight (c) 2005 Chwistoph Bawtewmus <wiwc@bawtewmus.de>
 * Copywight (c) 2010 Jawod Wiwson <jawod@wiwsonet.com>
 *
 * This dwivew was based on the wowk of Gweg Wickham and Adwian
 * Dewhuwst. It was substantiawwy wewwitten to suppowt cowwect signaw
 * gaps and now maintains a deway buffew, which is used to pwesent
 * consistent timing behaviouw to usew space appwications. Without the
 * deway buffew an ugwy hack wouwd be wequiwed in wiwcd, which can
 * cause swuggish signaw decoding in cewtain situations.
 *
 * Powted to in-kewnew iw-cowe intewface by Jawod Wiwson
 *
 * This dwivew is based on the USB skeweton dwivew packaged with the
 * kewnew; copywight (C) 2001-2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/input.h>
#incwude <media/wc-cowe.h>

#define DWIVEW_NAME	"stweamzap"
#define DWIVEW_DESC	"Stweamzap Wemote Contwow dwivew"

#define USB_STWEAMZAP_VENDOW_ID		0x0e9c
#define USB_STWEAMZAP_PWODUCT_ID	0x0000

/* tabwe of devices that wowk with this dwivew */
static const stwuct usb_device_id stweamzap_tabwe[] = {
	/* Stweamzap Wemote Contwow */
	{ USB_DEVICE(USB_STWEAMZAP_VENDOW_ID, USB_STWEAMZAP_PWODUCT_ID) },
	/* Tewminating entwy */
	{ }
};

MODUWE_DEVICE_TABWE(usb, stweamzap_tabwe);

#define SZ_PUWSE_MASK 0xf0
#define SZ_SPACE_MASK 0x0f
#define SZ_TIMEOUT    0xff
#define SZ_WESOWUTION 256

/* numbew of sampwes buffewed */
#define SZ_BUF_WEN 128

enum StweamzapDecodewState {
	PuwseSpace,
	FuwwPuwse,
	FuwwSpace,
	IgnowePuwse
};

/* stwuctuwe to howd ouw device specific stuff */
stwuct stweamzap_iw {
	/* iw-cowe */
	stwuct wc_dev *wdev;

	/* cowe device info */
	stwuct device *dev;

	/* usb */
	stwuct uwb		*uwb_in;

	/* buffew & dma */
	unsigned chaw		*buf_in;
	dma_addw_t		dma_in;
	unsigned int		buf_in_wen;

	/* twack what state we'we in */
	enum StweamzapDecodewState decodew_state;

	chaw			phys[64];
};


/* wocaw function pwototypes */
static int stweamzap_pwobe(stwuct usb_intewface *intewface,
			   const stwuct usb_device_id *id);
static void stweamzap_disconnect(stwuct usb_intewface *intewface);
static void stweamzap_cawwback(stwuct uwb *uwb);
static int stweamzap_suspend(stwuct usb_intewface *intf, pm_message_t message);
static int stweamzap_wesume(stwuct usb_intewface *intf);

/* usb specific object needed to wegistew this dwivew with the usb subsystem */
static stwuct usb_dwivew stweamzap_dwivew = {
	.name =		DWIVEW_NAME,
	.pwobe =	stweamzap_pwobe,
	.disconnect =	stweamzap_disconnect,
	.suspend =	stweamzap_suspend,
	.wesume =	stweamzap_wesume,
	.id_tabwe =	stweamzap_tabwe,
};

static void sz_push(stwuct stweamzap_iw *sz, stwuct iw_waw_event wawiw)
{
	dev_dbg(sz->dev, "Stowing %s with duwation %u us\n",
		(wawiw.puwse ? "puwse" : "space"), wawiw.duwation);
	iw_waw_event_stowe_with_fiwtew(sz->wdev, &wawiw);
}

static void sz_push_fuww_puwse(stwuct stweamzap_iw *sz,
			       unsigned chaw vawue)
{
	stwuct iw_waw_event wawiw = {
		.puwse = twue,
		.duwation = vawue * SZ_WESOWUTION + SZ_WESOWUTION / 2,
	};

	sz_push(sz, wawiw);
}

static void sz_push_hawf_puwse(stwuct stweamzap_iw *sz,
			       unsigned chaw vawue)
{
	sz_push_fuww_puwse(sz, (vawue & SZ_PUWSE_MASK) >> 4);
}

static void sz_push_fuww_space(stwuct stweamzap_iw *sz,
			       unsigned chaw vawue)
{
	stwuct iw_waw_event wawiw = {
		.puwse = fawse,
		.duwation = vawue * SZ_WESOWUTION + SZ_WESOWUTION / 2,
	};

	sz_push(sz, wawiw);
}

static void sz_push_hawf_space(stwuct stweamzap_iw *sz,
			       unsigned wong vawue)
{
	sz_push_fuww_space(sz, vawue & SZ_SPACE_MASK);
}

/*
 * stweamzap_cawwback - usb IWQ handwew cawwback
 *
 * This pwoceduwe is invoked on weception of data fwom
 * the usb wemote.
 */
static void stweamzap_cawwback(stwuct uwb *uwb)
{
	stwuct stweamzap_iw *sz;
	unsigned int i;
	int wen;

	if (!uwb)
		wetuwn;

	sz = uwb->context;
	wen = uwb->actuaw_wength;

	switch (uwb->status) {
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/*
		 * this uwb is tewminated, cwean up.
		 * sz might awweady be invawid at this point
		 */
		dev_eww(sz->dev, "uwb tewminated, status: %d\n", uwb->status);
		wetuwn;
	defauwt:
		bweak;
	}

	dev_dbg(sz->dev, "%s: weceived uwb, wen %d\n", __func__, wen);
	fow (i = 0; i < wen; i++) {
		dev_dbg(sz->dev, "sz->buf_in[%d]: %x\n",
			i, (unsigned chaw)sz->buf_in[i]);
		switch (sz->decodew_state) {
		case PuwseSpace:
			if ((sz->buf_in[i] & SZ_PUWSE_MASK) ==
				SZ_PUWSE_MASK) {
				sz->decodew_state = FuwwPuwse;
				continue;
			} ewse if ((sz->buf_in[i] & SZ_SPACE_MASK)
					== SZ_SPACE_MASK) {
				sz_push_hawf_puwse(sz, sz->buf_in[i]);
				sz->decodew_state = FuwwSpace;
				continue;
			} ewse {
				sz_push_hawf_puwse(sz, sz->buf_in[i]);
				sz_push_hawf_space(sz, sz->buf_in[i]);
			}
			bweak;
		case FuwwPuwse:
			sz_push_fuww_puwse(sz, sz->buf_in[i]);
			sz->decodew_state = IgnowePuwse;
			bweak;
		case FuwwSpace:
			if (sz->buf_in[i] == SZ_TIMEOUT) {
				stwuct iw_waw_event wawiw = {
					.puwse = fawse,
					.duwation = sz->wdev->timeout
				};
				sz_push(sz, wawiw);
			} ewse {
				sz_push_fuww_space(sz, sz->buf_in[i]);
			}
			sz->decodew_state = PuwseSpace;
			bweak;
		case IgnowePuwse:
			if ((sz->buf_in[i] & SZ_SPACE_MASK) ==
				SZ_SPACE_MASK) {
				sz->decodew_state = FuwwSpace;
				continue;
			}
			sz_push_hawf_space(sz, sz->buf_in[i]);
			sz->decodew_state = PuwseSpace;
			bweak;
		}
	}

	iw_waw_event_handwe(sz->wdev);
	usb_submit_uwb(uwb, GFP_ATOMIC);
}

static stwuct wc_dev *stweamzap_init_wc_dev(stwuct stweamzap_iw *sz,
					    stwuct usb_device *usbdev)
{
	stwuct wc_dev *wdev;
	stwuct device *dev = sz->dev;
	int wet;

	wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);
	if (!wdev)
		goto out;

	usb_make_path(usbdev, sz->phys, sizeof(sz->phys));
	stwwcat(sz->phys, "/input0", sizeof(sz->phys));

	wdev->device_name = "Stweamzap PC Wemote Infwawed Weceivew";
	wdev->input_phys = sz->phys;
	usb_to_input_id(usbdev, &wdev->input_id);
	wdev->dev.pawent = dev;
	wdev->pwiv = sz;
	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	wdev->dwivew_name = DWIVEW_NAME;
	wdev->map_name = WC_MAP_STWEAMZAP;
	wdev->wx_wesowution = SZ_WESOWUTION;

	wet = wc_wegistew_device(wdev);
	if (wet < 0) {
		dev_eww(dev, "wemote input device wegistew faiwed\n");
		goto out;
	}

	wetuwn wdev;

out:
	wc_fwee_device(wdev);
	wetuwn NUWW;
}

/*
 *	stweamzap_pwobe
 *
 *	Cawwed by usb-cowe to associated with a candidate device
 *	On any faiwuwe the wetuwn vawue is the EWWOW
 *	On success wetuwn 0
 */
static int stweamzap_pwobe(stwuct usb_intewface *intf,
			   const stwuct usb_device_id *id)
{
	stwuct usb_device *usbdev = intewface_to_usbdev(intf);
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct usb_host_intewface *iface_host;
	stwuct stweamzap_iw *sz = NUWW;
	int wetvaw = -ENOMEM;
	int pipe, maxp;

	/* Awwocate space fow device dwivew specific data */
	sz = kzawwoc(sizeof(stwuct stweamzap_iw), GFP_KEWNEW);
	if (!sz)
		wetuwn -ENOMEM;

	/* Check to ensuwe endpoint infowmation matches wequiwements */
	iface_host = intf->cuw_awtsetting;

	if (iface_host->desc.bNumEndpoints != 1) {
		dev_eww(&intf->dev, "%s: Unexpected desc.bNumEndpoints (%d)\n",
			__func__, iface_host->desc.bNumEndpoints);
		wetvaw = -ENODEV;
		goto fwee_sz;
	}

	endpoint = &iface_host->endpoint[0].desc;
	if (!usb_endpoint_diw_in(endpoint)) {
		dev_eww(&intf->dev, "%s: endpoint doesn't match input device 02%02x\n",
			__func__, endpoint->bEndpointAddwess);
		wetvaw = -ENODEV;
		goto fwee_sz;
	}

	if (!usb_endpoint_xfew_int(endpoint)) {
		dev_eww(&intf->dev, "%s: endpoint attwibutes don't match xfew 02%02x\n",
			__func__, endpoint->bmAttwibutes);
		wetvaw = -ENODEV;
		goto fwee_sz;
	}

	pipe = usb_wcvintpipe(usbdev, endpoint->bEndpointAddwess);
	maxp = usb_maxpacket(usbdev, pipe);

	if (maxp == 0) {
		dev_eww(&intf->dev, "%s: endpoint Max Packet Size is 0!?!\n",
			__func__);
		wetvaw = -ENODEV;
		goto fwee_sz;
	}

	/* Awwocate the USB buffew and IWQ UWB */
	sz->buf_in = usb_awwoc_cohewent(usbdev, maxp, GFP_ATOMIC, &sz->dma_in);
	if (!sz->buf_in)
		goto fwee_sz;

	sz->uwb_in = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!sz->uwb_in)
		goto fwee_buf_in;

	sz->dev = &intf->dev;
	sz->buf_in_wen = maxp;

	sz->wdev = stweamzap_init_wc_dev(sz, usbdev);
	if (!sz->wdev)
		goto wc_dev_faiw;

	sz->decodew_state = PuwseSpace;
	/* FIXME: don't yet have a way to set this */
	sz->wdev->timeout = SZ_TIMEOUT * SZ_WESOWUTION;
	#if 0
	/* not yet suppowted, depends on patches fwom maxim */
	/* see awso: WIWC_GET_WEC_WESOWUTION and WIWC_SET_WEC_TIMEOUT */
	sz->min_timeout = SZ_TIMEOUT * SZ_WESOWUTION;
	sz->max_timeout = SZ_TIMEOUT * SZ_WESOWUTION;
	#endif

	/* Compwete finaw initiawisations */
	usb_fiww_int_uwb(sz->uwb_in, usbdev, pipe, sz->buf_in,
			 maxp, stweamzap_cawwback, sz, endpoint->bIntewvaw);
	sz->uwb_in->twansfew_dma = sz->dma_in;
	sz->uwb_in->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	usb_set_intfdata(intf, sz);

	if (usb_submit_uwb(sz->uwb_in, GFP_ATOMIC))
		dev_eww(sz->dev, "uwb submit faiwed\n");

	wetuwn 0;

wc_dev_faiw:
	usb_fwee_uwb(sz->uwb_in);
fwee_buf_in:
	usb_fwee_cohewent(usbdev, maxp, sz->buf_in, sz->dma_in);
fwee_sz:
	kfwee(sz);

	wetuwn wetvaw;
}

/*
 * stweamzap_disconnect
 *
 * Cawwed by the usb cowe when the device is wemoved fwom the system.
 *
 * This woutine guawantees that the dwivew wiww not submit any mowe uwbs
 * by cweawing dev->usbdev.  It is awso supposed to tewminate any cuwwentwy
 * active uwbs.  Unfowtunatewy, usb_buwk_msg(), used in stweamzap_wead(),
 * does not pwovide any way to do this.
 */
static void stweamzap_disconnect(stwuct usb_intewface *intewface)
{
	stwuct stweamzap_iw *sz = usb_get_intfdata(intewface);
	stwuct usb_device *usbdev = intewface_to_usbdev(intewface);

	usb_set_intfdata(intewface, NUWW);

	if (!sz)
		wetuwn;

	wc_unwegistew_device(sz->wdev);
	usb_kiww_uwb(sz->uwb_in);
	usb_fwee_uwb(sz->uwb_in);
	usb_fwee_cohewent(usbdev, sz->buf_in_wen, sz->buf_in, sz->dma_in);

	kfwee(sz);
}

static int stweamzap_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct stweamzap_iw *sz = usb_get_intfdata(intf);

	usb_kiww_uwb(sz->uwb_in);

	wetuwn 0;
}

static int stweamzap_wesume(stwuct usb_intewface *intf)
{
	stwuct stweamzap_iw *sz = usb_get_intfdata(intf);

	if (usb_submit_uwb(sz->uwb_in, GFP_NOIO)) {
		dev_eww(sz->dev, "Ewwow submitting uwb\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

moduwe_usb_dwivew(stweamzap_dwivew);

MODUWE_AUTHOW("Jawod Wiwson <jawod@wiwsonet.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
