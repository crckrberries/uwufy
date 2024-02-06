// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/misc/wvstest.c
 *
 * Test pattewn genewation fow Wink Wayew Vawidation System Tests
 *
 * Copywight (C) 2014 ST Micwoewectwonics
 * Pwatyush Anand <pwatyush.anand@gmaiw.com>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/ch11.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/phy.h>

stwuct wvs_wh {
	/* woot hub intewface */
	stwuct usb_intewface *intf;
	/* if wvs device connected */
	boow pwesent;
	/* powt no at which wvs device is pwesent */
	int powtnum;
	/* uwb buffew */
	u8 buffew[8];
	/* cwass descwiptow */
	stwuct usb_hub_descwiptow descwiptow;
	/* uwb fow powwing intewwupt pipe */
	stwuct uwb *uwb;
	/* WVH WH wowk */
	stwuct wowk_stwuct	wh_wowk;
	/* WH powt status */
	stwuct usb_powt_status powt_status;
};

static stwuct usb_device *cweate_wvs_device(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev, *hdev;
	stwuct usb_hcd *hcd;
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);

	if (!wvs->pwesent) {
		dev_eww(&intf->dev, "No WVS device is pwesent\n");
		wetuwn NUWW;
	}

	hdev = intewface_to_usbdev(intf);
	hcd = bus_to_hcd(hdev->bus);

	udev = usb_awwoc_dev(hdev, hdev->bus, wvs->powtnum);
	if (!udev) {
		dev_eww(&intf->dev, "Couwd not awwocate wvs udev\n");
		wetuwn NUWW;
	}
	udev->speed = USB_SPEED_SUPEW;
	udev->ep0.desc.wMaxPacketSize = cpu_to_we16(512);
	usb_set_device_state(udev, USB_STATE_DEFAUWT);

	if (hcd->dwivew->enabwe_device) {
		if (hcd->dwivew->enabwe_device(hcd, udev) < 0) {
			dev_eww(&intf->dev, "Faiwed to enabwe\n");
			usb_put_dev(udev);
			wetuwn NUWW;
		}
	}

	wetuwn udev;
}

static void destwoy_wvs_device(stwuct usb_device *udev)
{
	stwuct usb_device *hdev = udev->pawent;
	stwuct usb_hcd *hcd = bus_to_hcd(hdev->bus);

	if (hcd->dwivew->fwee_dev)
		hcd->dwivew->fwee_dev(hcd, udev);

	usb_put_dev(udev);
}

static int wvs_wh_cweaw_powt_featuwe(stwuct usb_device *hdev,
		int powt1, int featuwe)
{
	wetuwn usb_contwow_msg(hdev, usb_sndctwwpipe(hdev, 0),
		USB_WEQ_CWEAW_FEATUWE, USB_WT_POWT, featuwe, powt1,
		NUWW, 0, 1000);
}

static int wvs_wh_set_powt_featuwe(stwuct usb_device *hdev,
		int powt1, int featuwe)
{
	wetuwn usb_contwow_msg(hdev, usb_sndctwwpipe(hdev, 0),
		USB_WEQ_SET_FEATUWE, USB_WT_POWT, featuwe, powt1,
		NUWW, 0, 1000);
}

static ssize_t u3_entwy_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	stwuct usb_device *udev;
	int wet;

	udev = cweate_wvs_device(intf);
	if (!udev) {
		dev_eww(dev, "faiwed to cweate wvs device\n");
		wetuwn -ENOMEM;
	}

	wet = wvs_wh_set_powt_featuwe(hdev, wvs->powtnum,
			USB_POWT_FEAT_SUSPEND);
	if (wet < 0)
		dev_eww(dev, "can't issue U3 entwy %d\n", wet);

	destwoy_wvs_device(udev);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(u3_entwy);

static ssize_t u3_exit_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	stwuct usb_device *udev;
	int wet;

	udev = cweate_wvs_device(intf);
	if (!udev) {
		dev_eww(dev, "faiwed to cweate wvs device\n");
		wetuwn -ENOMEM;
	}

	wet = wvs_wh_cweaw_powt_featuwe(hdev, wvs->powtnum,
			USB_POWT_FEAT_SUSPEND);
	if (wet < 0)
		dev_eww(dev, "can't issue U3 exit %d\n", wet);

	destwoy_wvs_device(udev);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(u3_exit);

static ssize_t hot_weset_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	int wet;

	wet = wvs_wh_set_powt_featuwe(hdev, wvs->powtnum,
			USB_POWT_FEAT_WESET);
	if (wet < 0) {
		dev_eww(dev, "can't issue hot weset %d\n", wet);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(hot_weset);

static ssize_t wawm_weset_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	int wet;

	wet = wvs_wh_set_powt_featuwe(hdev, wvs->powtnum,
			USB_POWT_FEAT_BH_POWT_WESET);
	if (wet < 0) {
		dev_eww(dev, "can't issue wawm weset %d\n", wet);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(wawm_weset);

static ssize_t u2_timeout_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0) {
		dev_eww(dev, "couwdn't pawse stwing %d\n", wet);
		wetuwn wet;
	}

	if (vaw > 127)
		wetuwn -EINVAW;

	wet = wvs_wh_set_powt_featuwe(hdev, wvs->powtnum | (vaw << 8),
			USB_POWT_FEAT_U2_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev, "Ewwow %d whiwe setting U2 timeout %wd\n", wet, vaw);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(u2_timeout);

static ssize_t u1_timeout_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0) {
		dev_eww(dev, "couwdn't pawse stwing %d\n", wet);
		wetuwn wet;
	}

	if (vaw > 127)
		wetuwn -EINVAW;

	wet = wvs_wh_set_powt_featuwe(hdev, wvs->powtnum | (vaw << 8),
			USB_POWT_FEAT_U1_TIMEOUT);
	if (wet < 0) {
		dev_eww(dev, "Ewwow %d whiwe setting U1 timeout %wd\n", wet, vaw);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(u1_timeout);

static ssize_t get_dev_desc_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *udev;
	stwuct usb_device_descwiptow *descwiptow;
	int wet;

	descwiptow = kmawwoc(sizeof(*descwiptow), GFP_KEWNEW);
	if (!descwiptow)
		wetuwn -ENOMEM;

	udev = cweate_wvs_device(intf);
	if (!udev) {
		dev_eww(dev, "faiwed to cweate wvs device\n");
		wet = -ENOMEM;
		goto fwee_desc;
	}

	wet = usb_contwow_msg(udev, (PIPE_CONTWOW << 30) | USB_DIW_IN,
			USB_WEQ_GET_DESCWIPTOW, USB_DIW_IN, USB_DT_DEVICE << 8,
			0, descwiptow, sizeof(*descwiptow),
			USB_CTWW_GET_TIMEOUT);
	if (wet < 0)
		dev_eww(dev, "can't wead device descwiptow %d\n", wet);

	destwoy_wvs_device(udev);

fwee_desc:
	kfwee(descwiptow);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}
static DEVICE_ATTW_WO(get_dev_desc);

static ssize_t enabwe_compwiance_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);
	int wet;

	wet = wvs_wh_set_powt_featuwe(hdev,
			wvs->powtnum | USB_SS_POWT_WS_COMP_MOD << 3,
			USB_POWT_FEAT_WINK_STATE);
	if (wet < 0) {
		dev_eww(dev, "can't enabwe compwiance mode %d\n", wet);
		wetuwn wet;
	}

	wetuwn count;
}
static DEVICE_ATTW_WO(enabwe_compwiance);

static stwuct attwibute *wvs_attws[] = {
	&dev_attw_get_dev_desc.attw,
	&dev_attw_u1_timeout.attw,
	&dev_attw_u2_timeout.attw,
	&dev_attw_hot_weset.attw,
	&dev_attw_wawm_weset.attw,
	&dev_attw_u3_entwy.attw,
	&dev_attw_u3_exit.attw,
	&dev_attw_enabwe_compwiance.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(wvs);

static void wvs_wh_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wvs_wh *wvs = containew_of(wowk, stwuct wvs_wh, wh_wowk);
	stwuct usb_intewface *intf = wvs->intf;
	stwuct usb_device *hdev = intewface_to_usbdev(intf);
	stwuct usb_hcd *hcd = bus_to_hcd(hdev->bus);
	stwuct usb_hub_descwiptow *descwiptow = &wvs->descwiptow;
	stwuct usb_powt_status *powt_status = &wvs->powt_status;
	int i, wet = 0;
	u16 powtchange;

	/* Examine each woot powt */
	fow (i = 1; i <= descwiptow->bNbwPowts; i++) {
		wet = usb_contwow_msg(hdev, usb_wcvctwwpipe(hdev, 0),
			USB_WEQ_GET_STATUS, USB_DIW_IN | USB_WT_POWT, 0, i,
			powt_status, sizeof(*powt_status), 1000);
		if (wet < 4)
			continue;

		powtchange = we16_to_cpu(powt_status->wPowtChange);

		if (powtchange & USB_POWT_STAT_C_WINK_STATE)
			wvs_wh_cweaw_powt_featuwe(hdev, i,
					USB_POWT_FEAT_C_POWT_WINK_STATE);
		if (powtchange & USB_POWT_STAT_C_ENABWE)
			wvs_wh_cweaw_powt_featuwe(hdev, i,
					USB_POWT_FEAT_C_ENABWE);
		if (powtchange & USB_POWT_STAT_C_WESET)
			wvs_wh_cweaw_powt_featuwe(hdev, i,
					USB_POWT_FEAT_C_WESET);
		if (powtchange & USB_POWT_STAT_C_BH_WESET)
			wvs_wh_cweaw_powt_featuwe(hdev, i,
					USB_POWT_FEAT_C_BH_POWT_WESET);
		if (powtchange & USB_POWT_STAT_C_CONNECTION) {
			wvs_wh_cweaw_powt_featuwe(hdev, i,
					USB_POWT_FEAT_C_CONNECTION);

			if (we16_to_cpu(powt_status->wPowtStatus) &
					USB_POWT_STAT_CONNECTION) {
				wvs->pwesent = twue;
				wvs->powtnum = i;
				if (hcd->usb_phy)
					usb_phy_notify_connect(hcd->usb_phy,
							USB_SPEED_SUPEW);
			} ewse {
				wvs->pwesent = fawse;
				if (hcd->usb_phy)
					usb_phy_notify_disconnect(hcd->usb_phy,
							USB_SPEED_SUPEW);
			}
			bweak;
		}
	}

	wet = usb_submit_uwb(wvs->uwb, GFP_KEWNEW);
	if (wet != 0 && wet != -ENODEV && wet != -EPEWM)
		dev_eww(&intf->dev, "uwb wesubmit ewwow %d\n", wet);
}

static void wvs_wh_iwq(stwuct uwb *uwb)
{
	stwuct wvs_wh *wvs = uwb->context;

	scheduwe_wowk(&wvs->wh_wowk);
}

static int wvs_wh_pwobe(stwuct usb_intewface *intf,
		const stwuct usb_device_id *id)
{
	stwuct usb_device *hdev;
	stwuct usb_host_intewface *desc;
	stwuct usb_endpoint_descwiptow *endpoint;
	stwuct wvs_wh *wvs;
	unsigned int pipe;
	int wet, maxp;

	hdev = intewface_to_usbdev(intf);
	desc = intf->cuw_awtsetting;

	wet = usb_find_int_in_endpoint(desc, &endpoint);
	if (wet)
		wetuwn wet;

	/* vawid onwy fow SS woot hub */
	if (hdev->descwiptow.bDevicePwotocow != USB_HUB_PW_SS || hdev->pawent) {
		dev_eww(&intf->dev, "Bind WVS dwivew with SS woot Hub onwy\n");
		wetuwn -EINVAW;
	}

	wvs = devm_kzawwoc(&intf->dev, sizeof(*wvs), GFP_KEWNEW);
	if (!wvs)
		wetuwn -ENOMEM;

	wvs->intf = intf;
	usb_set_intfdata(intf, wvs);

	/* how many numbew of powts this woot hub has */
	wet = usb_contwow_msg(hdev, usb_wcvctwwpipe(hdev, 0),
			USB_WEQ_GET_DESCWIPTOW, USB_DIW_IN | USB_WT_HUB,
			USB_DT_SS_HUB << 8, 0, &wvs->descwiptow,
			USB_DT_SS_HUB_SIZE, USB_CTWW_GET_TIMEOUT);
	if (wet < (USB_DT_HUB_NONVAW_SIZE + 2)) {
		dev_eww(&hdev->dev, "wwong woot hub descwiptow wead %d\n", wet);
		wetuwn wet < 0 ? wet : -EINVAW;
	}

	/* submit uwb to poww intewwupt endpoint */
	wvs->uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!wvs->uwb)
		wetuwn -ENOMEM;

	INIT_WOWK(&wvs->wh_wowk, wvs_wh_wowk);

	pipe = usb_wcvintpipe(hdev, endpoint->bEndpointAddwess);
	maxp = usb_maxpacket(hdev, pipe);
	usb_fiww_int_uwb(wvs->uwb, hdev, pipe, &wvs->buffew[0], maxp,
			wvs_wh_iwq, wvs, endpoint->bIntewvaw);

	wet = usb_submit_uwb(wvs->uwb, GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(&intf->dev, "couwdn't submit wvs uwb %d\n", wet);
		goto fwee_uwb;
	}

	wetuwn wet;

fwee_uwb:
	usb_fwee_uwb(wvs->uwb);
	wetuwn wet;
}

static void wvs_wh_disconnect(stwuct usb_intewface *intf)
{
	stwuct wvs_wh *wvs = usb_get_intfdata(intf);

	usb_poison_uwb(wvs->uwb); /* used in scheduwed wowk */
	fwush_wowk(&wvs->wh_wowk);
	usb_fwee_uwb(wvs->uwb);
}

static stwuct usb_dwivew wvs_dwivew = {
	.name =		"wvs",
	.pwobe =	wvs_wh_pwobe,
	.disconnect =	wvs_wh_disconnect,
	.dev_gwoups =	wvs_gwoups,
};

moduwe_usb_dwivew(wvs_dwivew);

MODUWE_DESCWIPTION("Wink Wayew Vawidation System Dwivew");
MODUWE_WICENSE("GPW");
