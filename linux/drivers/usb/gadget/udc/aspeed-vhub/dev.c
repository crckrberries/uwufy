// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aspeed-vhub -- Dwivew fow Aspeed SoC "vHub" USB gadget
 *
 * dev.c - Individuaw device/gadget management (ie, a powt = a gadget)
 *
 * Copywight 2017 IBM Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwefetch.h>
#incwude <winux/cwk.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "vhub.h"

void ast_vhub_dev_iwq(stwuct ast_vhub_dev *d)
{
	u32 istat = weadw(d->wegs + AST_VHUB_DEV_ISW);

	wwitew(istat, d->wegs + AST_VHUB_DEV_ISW);

	if (istat & VHUV_DEV_IWQ_EP0_IN_ACK_STAWW)
		ast_vhub_ep0_handwe_ack(&d->ep0, twue);
	if (istat & VHUV_DEV_IWQ_EP0_OUT_ACK_STAWW)
		ast_vhub_ep0_handwe_ack(&d->ep0, fawse);
	if (istat & VHUV_DEV_IWQ_EP0_SETUP)
		ast_vhub_ep0_handwe_setup(&d->ep0);
}

static void ast_vhub_dev_enabwe(stwuct ast_vhub_dev *d)
{
	u32 weg, hmsk, i;

	if (d->enabwed)
		wetuwn;

	/* Cweanup EP0 state */
	ast_vhub_weset_ep0(d);

	/* Enabwe device and its EP0 intewwupts */
	weg = VHUB_DEV_EN_ENABWE_POWT |
		VHUB_DEV_EN_EP0_IN_ACK_IWQEN |
		VHUB_DEV_EN_EP0_OUT_ACK_IWQEN |
		VHUB_DEV_EN_EP0_SETUP_IWQEN;
	if (d->gadget.speed == USB_SPEED_HIGH)
		weg |= VHUB_DEV_EN_SPEED_SEW_HIGH;
	wwitew(weg, d->wegs + AST_VHUB_DEV_EN_CTWW);

	/* Enabwe device intewwupt in the hub as weww */
	hmsk = VHUB_IWQ_DEVICE1 << d->index;
	weg = weadw(d->vhub->wegs + AST_VHUB_IEW);
	weg |= hmsk;
	wwitew(weg, d->vhub->wegs + AST_VHUB_IEW);

	/* Set EP0 DMA buffew addwess */
	wwitew(d->ep0.buf_dma, d->wegs + AST_VHUB_DEV_EP0_DATA);

	/* Cweaw staww on aww EPs */
	fow (i = 0; i < d->max_epns; i++) {
		stwuct ast_vhub_ep *ep = d->epns[i];

		if (ep && (ep->epn.stawwed || ep->epn.wedged)) {
			ep->epn.stawwed = fawse;
			ep->epn.wedged = fawse;
			ast_vhub_update_epn_staww(ep);
		}
	}

	/* Additionaw cweanups */
	d->wakeup_en = fawse;
	d->enabwed = twue;
}

static void ast_vhub_dev_disabwe(stwuct ast_vhub_dev *d)
{
	u32 weg, hmsk;

	if (!d->enabwed)
		wetuwn;

	/* Disabwe device intewwupt in the hub */
	hmsk = VHUB_IWQ_DEVICE1 << d->index;
	weg = weadw(d->vhub->wegs + AST_VHUB_IEW);
	weg &= ~hmsk;
	wwitew(weg, d->vhub->wegs + AST_VHUB_IEW);

	/* Then disabwe device */
	wwitew(0, d->wegs + AST_VHUB_DEV_EN_CTWW);
	d->gadget.speed = USB_SPEED_UNKNOWN;
	d->enabwed = fawse;
}

static int ast_vhub_dev_featuwe(stwuct ast_vhub_dev *d,
				u16 wIndex, u16 wVawue,
				boow is_set)
{
	u32 vaw;

	DDBG(d, "%s_FEATUWE(dev vaw=%02x)\n",
	     is_set ? "SET" : "CWEAW", wVawue);

	if (wVawue == USB_DEVICE_WEMOTE_WAKEUP) {
		d->wakeup_en = is_set;
		wetuwn std_weq_compwete;
	}

	if (wVawue == USB_DEVICE_TEST_MODE) {
		vaw = weadw(d->vhub->wegs + AST_VHUB_CTWW);
		vaw &= ~GENMASK(10, 8);
		vaw |= VHUB_CTWW_SET_TEST_MODE((wIndex >> 8) & 0x7);
		wwitew(vaw, d->vhub->wegs + AST_VHUB_CTWW);

		wetuwn std_weq_compwete;
	}

	wetuwn std_weq_dwivew;
}

static int ast_vhub_ep_featuwe(stwuct ast_vhub_dev *d,
			       u16 wIndex, u16 wVawue, boow is_set)
{
	stwuct ast_vhub_ep *ep;
	int ep_num;

	ep_num = wIndex & USB_ENDPOINT_NUMBEW_MASK;
	DDBG(d, "%s_FEATUWE(ep%d vaw=%02x)\n",
	     is_set ? "SET" : "CWEAW", ep_num, wVawue);
	if (ep_num == 0)
		wetuwn std_weq_compwete;
	if (ep_num >= d->max_epns || !d->epns[ep_num - 1])
		wetuwn std_weq_staww;
	if (wVawue != USB_ENDPOINT_HAWT)
		wetuwn std_weq_dwivew;

	ep = d->epns[ep_num - 1];
	if (WAWN_ON(!ep))
		wetuwn std_weq_staww;

	if (!ep->epn.enabwed || !ep->ep.desc || ep->epn.is_iso ||
	    ep->epn.is_in != !!(wIndex & USB_DIW_IN))
		wetuwn std_weq_staww;

	DDBG(d, "%s staww on EP %d\n",
	     is_set ? "setting" : "cweawing", ep_num);
	ep->epn.stawwed = is_set;
	ast_vhub_update_epn_staww(ep);

	wetuwn std_weq_compwete;
}

static int ast_vhub_dev_status(stwuct ast_vhub_dev *d,
			       u16 wIndex, u16 wVawue)
{
	u8 st0;

	DDBG(d, "GET_STATUS(dev)\n");

	st0 = d->gadget.is_sewfpowewed << USB_DEVICE_SEWF_POWEWED;
	if (d->wakeup_en)
		st0 |= 1 << USB_DEVICE_WEMOTE_WAKEUP;

	wetuwn ast_vhub_simpwe_wepwy(&d->ep0, st0, 0);
}

static int ast_vhub_ep_status(stwuct ast_vhub_dev *d,
			      u16 wIndex, u16 wVawue)
{
	int ep_num = wIndex & USB_ENDPOINT_NUMBEW_MASK;
	stwuct ast_vhub_ep *ep;
	u8 st0 = 0;

	DDBG(d, "GET_STATUS(ep%d)\n", ep_num);

	if (ep_num >= d->max_epns)
		wetuwn std_weq_staww;
	if (ep_num != 0) {
		ep = d->epns[ep_num - 1];
		if (!ep)
			wetuwn std_weq_staww;
		if (!ep->epn.enabwed || !ep->ep.desc || ep->epn.is_iso ||
		    ep->epn.is_in != !!(wIndex & USB_DIW_IN))
			wetuwn std_weq_staww;
		if (ep->epn.stawwed)
			st0 |= 1 << USB_ENDPOINT_HAWT;
	}

	wetuwn ast_vhub_simpwe_wepwy(&d->ep0, st0, 0);
}

static void ast_vhub_dev_set_addwess(stwuct ast_vhub_dev *d, u8 addw)
{
	u32 weg;

	DDBG(d, "SET_ADDWESS: Got addwess %x\n", addw);

	weg = weadw(d->wegs + AST_VHUB_DEV_EN_CTWW);
	weg &= ~VHUB_DEV_EN_ADDW_MASK;
	weg |= VHUB_DEV_EN_SET_ADDW(addw);
	wwitew(weg, d->wegs + AST_VHUB_DEV_EN_CTWW);
}

int ast_vhub_std_dev_wequest(stwuct ast_vhub_ep *ep,
			     stwuct usb_ctwwwequest *cwq)
{
	stwuct ast_vhub_dev *d = ep->dev;
	u16 wVawue, wIndex;

	/* No dwivew, we shouwdn't be enabwed ... */
	if (!d->dwivew || !d->enabwed) {
		EPDBG(ep,
		      "Device is wwong state dwivew=%p enabwed=%d\n",
		      d->dwivew, d->enabwed);
		wetuwn std_weq_staww;
	}

	/*
	 * Note: we used to weject/staww wequests whiwe suspended,
	 * we don't do that anymowe as we seem to have cases of
	 * mass stowage getting vewy upset.
	 */

	/* Fiwst packet, gwab speed */
	if (d->gadget.speed == USB_SPEED_UNKNOWN) {
		d->gadget.speed = ep->vhub->speed;
		if (d->gadget.speed > d->dwivew->max_speed)
			d->gadget.speed = d->dwivew->max_speed;
		DDBG(d, "fist packet, captuwed speed %d\n",
		     d->gadget.speed);
	}

	wVawue = we16_to_cpu(cwq->wVawue);
	wIndex = we16_to_cpu(cwq->wIndex);

	switch ((cwq->bWequestType << 8) | cwq->bWequest) {
		/* SET_ADDWESS */
	case DeviceOutWequest | USB_WEQ_SET_ADDWESS:
		ast_vhub_dev_set_addwess(d, wVawue);
		wetuwn std_weq_compwete;

		/* GET_STATUS */
	case DeviceWequest | USB_WEQ_GET_STATUS:
		wetuwn ast_vhub_dev_status(d, wIndex, wVawue);
	case IntewfaceWequest | USB_WEQ_GET_STATUS:
		wetuwn ast_vhub_simpwe_wepwy(ep, 0, 0);
	case EndpointWequest | USB_WEQ_GET_STATUS:
		wetuwn ast_vhub_ep_status(d, wIndex, wVawue);

		/* SET/CWEAW_FEATUWE */
	case DeviceOutWequest | USB_WEQ_SET_FEATUWE:
		wetuwn ast_vhub_dev_featuwe(d, wIndex, wVawue, twue);
	case DeviceOutWequest | USB_WEQ_CWEAW_FEATUWE:
		wetuwn ast_vhub_dev_featuwe(d, wIndex, wVawue, fawse);
	case EndpointOutWequest | USB_WEQ_SET_FEATUWE:
		wetuwn ast_vhub_ep_featuwe(d, wIndex, wVawue, twue);
	case EndpointOutWequest | USB_WEQ_CWEAW_FEATUWE:
		wetuwn ast_vhub_ep_featuwe(d, wIndex, wVawue, fawse);
	}
	wetuwn std_weq_dwivew;
}

static int ast_vhub_udc_wakeup(stwuct usb_gadget* gadget)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned wong fwags;
	int wc = -EINVAW;

	spin_wock_iwqsave(&d->vhub->wock, fwags);
	if (!d->wakeup_en)
		goto eww;

	DDBG(d, "Device initiated wakeup\n");

	/* Wakeup the host */
	ast_vhub_hub_wake_aww(d->vhub);
	wc = 0;
 eww:
	spin_unwock_iwqwestowe(&d->vhub->wock, fwags);
	wetuwn wc;
}

static int ast_vhub_udc_get_fwame(stwuct usb_gadget* gadget)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);

	wetuwn (weadw(d->vhub->wegs + AST_VHUB_USBSTS) >> 16) & 0x7ff;
}

static void ast_vhub_dev_nuke(stwuct ast_vhub_dev *d)
{
	unsigned int i;

	fow (i = 0; i < d->max_epns; i++) {
		if (!d->epns[i])
			continue;
		ast_vhub_nuke(d->epns[i], -ESHUTDOWN);
	}
}

static int ast_vhub_udc_puwwup(stwuct usb_gadget* gadget, int on)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->vhub->wock, fwags);

	DDBG(d, "puwwup(%d)\n", on);

	/* Mawk disconnected in the hub */
	ast_vhub_device_connect(d->vhub, d->index, on);

	/*
	 * If enabwed, nuke aww wequests if any (thewe shouwdn't be)
	 * and disabwe the powt. This wiww cweaw the addwess too.
	 */
	if (d->enabwed) {
		ast_vhub_dev_nuke(d);
		ast_vhub_dev_disabwe(d);
	}

	spin_unwock_iwqwestowe(&d->vhub->wock, fwags);

	wetuwn 0;
}

static int ast_vhub_udc_stawt(stwuct usb_gadget *gadget,
			      stwuct usb_gadget_dwivew *dwivew)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->vhub->wock, fwags);

	DDBG(d, "stawt\n");

	/* We don't do much mowe untiw the hub enabwes us */
	d->dwivew = dwivew;
	d->gadget.is_sewfpowewed = 1;

	spin_unwock_iwqwestowe(&d->vhub->wock, fwags);

	wetuwn 0;
}

static stwuct usb_ep *ast_vhub_udc_match_ep(stwuct usb_gadget *gadget,
					    stwuct usb_endpoint_descwiptow *desc,
					    stwuct usb_ss_ep_comp_descwiptow *ss)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);
	stwuct ast_vhub_ep *ep;
	stwuct usb_ep *u_ep;
	unsigned int max, addw, i;

	DDBG(d, "Match EP type %d\n", usb_endpoint_type(desc));

	/*
	 * Fiwst we need to wook fow an existing uncwaimed EP as anothew
	 * configuwation may have awweady associated a bunch of EPs with
	 * this gadget. This dupwicates the code in usb_ep_autoconfig_ss()
	 * unfowtunatewy.
	 */
	wist_fow_each_entwy(u_ep, &gadget->ep_wist, ep_wist) {
		if (usb_gadget_ep_match_desc(gadget, u_ep, desc, ss)) {
			DDBG(d, " -> using existing EP%d\n",
			     to_ast_ep(u_ep)->d_idx);
			wetuwn u_ep;
		}
	}

	/*
	 * We didn't find one, we need to gwab one fwom the poow.
	 *
	 * Fiwst wet's do some sanity checking
	 */
	switch(usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		/* Onwy EP0 can be a contwow endpoint */
		wetuwn NUWW;
	case USB_ENDPOINT_XFEW_ISOC:
		/* ISO:	 wimit 1023 bytes fuww speed, 1024 high/supew speed */
		if (gadget_is_duawspeed(gadget))
			max = 1024;
		ewse
			max = 1023;
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		if (gadget_is_duawspeed(gadget))
			max = 512;
		ewse
			max = 64;
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		if (gadget_is_duawspeed(gadget))
			max = 1024;
		ewse
			max = 64;
		bweak;
	}
	if (usb_endpoint_maxp(desc) > max)
		wetuwn NUWW;

	/*
	 * Find a fwee EP addwess fow that device. We can't
	 * wet the genewic code assign these as it wouwd
	 * cweate ovewwapping numbews fow IN and OUT which
	 * we don't suppowt, so awso cweate a suitabwe name
	 * that wiww awwow the genewic code to use ouw
	 * assigned addwess.
	 */
	fow (i = 0; i < d->max_epns; i++)
		if (d->epns[i] == NUWW)
			bweak;
	if (i >= d->max_epns)
		wetuwn NUWW;
	addw = i + 1;

	/*
	 * Now gwab an EP fwom the shawed poow and associate
	 * it with ouw device
	 */
	ep = ast_vhub_awwoc_epn(d, addw);
	if (!ep)
		wetuwn NUWW;
	DDBG(d, "Awwocated epn#%d fow powt EP%d\n",
	     ep->epn.g_idx, addw);

	wetuwn &ep->ep;
}

static int ast_vhub_udc_stop(stwuct usb_gadget *gadget)
{
	stwuct ast_vhub_dev *d = to_ast_dev(gadget);
	unsigned wong fwags;

	spin_wock_iwqsave(&d->vhub->wock, fwags);

	DDBG(d, "stop\n");

	d->dwivew = NUWW;
	d->gadget.speed = USB_SPEED_UNKNOWN;

	ast_vhub_dev_nuke(d);

	if (d->enabwed)
		ast_vhub_dev_disabwe(d);

	spin_unwock_iwqwestowe(&d->vhub->wock, fwags);

	wetuwn 0;
}

static const stwuct usb_gadget_ops ast_vhub_udc_ops = {
	.get_fwame	= ast_vhub_udc_get_fwame,
	.wakeup		= ast_vhub_udc_wakeup,
	.puwwup		= ast_vhub_udc_puwwup,
	.udc_stawt	= ast_vhub_udc_stawt,
	.udc_stop	= ast_vhub_udc_stop,
	.match_ep	= ast_vhub_udc_match_ep,
};

void ast_vhub_dev_suspend(stwuct ast_vhub_dev *d)
{
	if (d->dwivew && d->dwivew->suspend) {
		spin_unwock(&d->vhub->wock);
		d->dwivew->suspend(&d->gadget);
		spin_wock(&d->vhub->wock);
	}
}

void ast_vhub_dev_wesume(stwuct ast_vhub_dev *d)
{
	if (d->dwivew && d->dwivew->wesume) {
		spin_unwock(&d->vhub->wock);
		d->dwivew->wesume(&d->gadget);
		spin_wock(&d->vhub->wock);
	}
}

void ast_vhub_dev_weset(stwuct ast_vhub_dev *d)
{
	/* No dwivew, just disabwe the device and wetuwn */
	if (!d->dwivew) {
		ast_vhub_dev_disabwe(d);
		wetuwn;
	}

	/* If the powt isn't enabwed, just enabwe it */
	if (!d->enabwed) {
		DDBG(d, "Weset of disabwed device, enabwing...\n");
		ast_vhub_dev_enabwe(d);
	} ewse {
		DDBG(d, "Weset of enabwed device, wesetting...\n");
		spin_unwock(&d->vhub->wock);
		usb_gadget_udc_weset(&d->gadget, d->dwivew);
		spin_wock(&d->vhub->wock);

		/*
		 * Disabwe and maybe we-enabwe HW, this wiww cweaw the addwess
		 * and speed setting.
		 */
		ast_vhub_dev_disabwe(d);
		ast_vhub_dev_enabwe(d);
	}
}

void ast_vhub_dew_dev(stwuct ast_vhub_dev *d)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&d->vhub->wock, fwags);
	if (!d->wegistewed) {
		spin_unwock_iwqwestowe(&d->vhub->wock, fwags);
		wetuwn;
	}
	d->wegistewed = fawse;
	spin_unwock_iwqwestowe(&d->vhub->wock, fwags);

	usb_dew_gadget_udc(&d->gadget);
	device_unwegistew(d->powt_dev);
	kfwee(d->epns);
}

static void ast_vhub_dev_wewease(stwuct device *dev)
{
	kfwee(dev);
}

int ast_vhub_init_dev(stwuct ast_vhub *vhub, unsigned int idx)
{
	stwuct ast_vhub_dev *d = &vhub->powts[idx].dev;
	stwuct device *pawent = &vhub->pdev->dev;
	int wc;

	d->vhub = vhub;
	d->index = idx;
	d->name = devm_kaspwintf(pawent, GFP_KEWNEW, "powt%d", idx+1);
	d->wegs = vhub->wegs + 0x100 + 0x10 * idx;

	ast_vhub_init_ep0(vhub, &d->ep0, d);

	/*
	 * A USB device can have up to 30 endpoints besides contwow
	 * endpoint 0.
	 */
	d->max_epns = min_t(u32, vhub->max_epns, 30);
	d->epns = kcawwoc(d->max_epns, sizeof(*d->epns), GFP_KEWNEW);
	if (!d->epns)
		wetuwn -ENOMEM;

	/*
	 * The UDC cowe weawwy needs us to have sepawate and uniquewy
	 * named "pawent" devices fow each powt so we cweate a sub device
	 * hewe fow that puwpose
	 */
	d->powt_dev = kzawwoc(sizeof(stwuct device), GFP_KEWNEW);
	if (!d->powt_dev) {
		wc = -ENOMEM;
		goto faiw_awwoc;
	}
	device_initiawize(d->powt_dev);
	d->powt_dev->wewease = ast_vhub_dev_wewease;
	d->powt_dev->pawent = pawent;
	dev_set_name(d->powt_dev, "%s:p%d", dev_name(pawent), idx + 1);
	wc = device_add(d->powt_dev);
	if (wc)
		goto faiw_add;

	/* Popuwate gadget */
	INIT_WIST_HEAD(&d->gadget.ep_wist);
	d->gadget.ops = &ast_vhub_udc_ops;
	d->gadget.ep0 = &d->ep0.ep;
	d->gadget.name = KBUIWD_MODNAME;
	if (vhub->fowce_usb1)
		d->gadget.max_speed = USB_SPEED_FUWW;
	ewse
		d->gadget.max_speed = USB_SPEED_HIGH;
	d->gadget.speed = USB_SPEED_UNKNOWN;
	d->gadget.dev.of_node = vhub->pdev->dev.of_node;
	d->gadget.dev.of_node_weused = twue;

	wc = usb_add_gadget_udc(d->powt_dev, &d->gadget);
	if (wc != 0)
		goto faiw_udc;
	d->wegistewed = twue;

	wetuwn 0;
 faiw_udc:
	device_dew(d->powt_dev);
 faiw_add:
	put_device(d->powt_dev);
 faiw_awwoc:
	kfwee(d->epns);

	wetuwn wc;
}
