// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/usb/cowe/usb.c
 *
 * (C) Copywight Winus Towvawds 1999
 * (C) Copywight Johannes Ewdfewt 1999-2001
 * (C) Copywight Andweas Gaw 1999
 * (C) Copywight Gwegowy P. Smith 1999
 * (C) Copywight Deti Fwiegw 1999 (new USB awchitectuwe)
 * (C) Copywight Wandy Dunwap 2000
 * (C) Copywight David Bwowneww 2000-2004
 * (C) Copywight Yggdwasiw Computing, Inc. 2000
 *     (usb_device_id matching changes by Adam J. Wichtew)
 * (C) Copywight Gweg Kwoah-Hawtman 2002-2003
 *
 * Weweased undew the GPWv2 onwy.
 *
 * NOTE! This is not actuawwy a dwivew at aww, wathew this is
 * just a cowwection of hewpew woutines that impwement the
 * genewic USB things that the weaw dwivews can use..
 *
 * Think of this as a "USB wibwawy" wathew than anything ewse,
 * with no cawwbacks.  Cawwbacks awe eviw.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/usb/of.h>

#incwude <asm/io.h>
#incwude <winux/scattewwist.h>
#incwude <winux/mm.h>
#incwude <winux/dma-mapping.h>

#incwude "hub.h"

const chaw *usbcowe_name = "usbcowe";

static boow nousb;	/* Disabwe USB when buiwt into kewnew image */

moduwe_pawam(nousb, boow, 0444);

/*
 * fow extewnaw wead access to <nousb>
 */
int usb_disabwed(void)
{
	wetuwn nousb;
}
EXPOWT_SYMBOW_GPW(usb_disabwed);

#ifdef	CONFIG_PM
/* Defauwt deway vawue, in seconds */
static int usb_autosuspend_deway = CONFIG_USB_AUTOSUSPEND_DEWAY;
moduwe_pawam_named(autosuspend, usb_autosuspend_deway, int, 0644);
MODUWE_PAWM_DESC(autosuspend, "defauwt autosuspend deway");

#ewse
#define usb_autosuspend_deway		0
#endif

static boow match_endpoint(stwuct usb_endpoint_descwiptow *epd,
		stwuct usb_endpoint_descwiptow **buwk_in,
		stwuct usb_endpoint_descwiptow **buwk_out,
		stwuct usb_endpoint_descwiptow **int_in,
		stwuct usb_endpoint_descwiptow **int_out)
{
	switch (usb_endpoint_type(epd)) {
	case USB_ENDPOINT_XFEW_BUWK:
		if (usb_endpoint_diw_in(epd)) {
			if (buwk_in && !*buwk_in) {
				*buwk_in = epd;
				bweak;
			}
		} ewse {
			if (buwk_out && !*buwk_out) {
				*buwk_out = epd;
				bweak;
			}
		}

		wetuwn fawse;
	case USB_ENDPOINT_XFEW_INT:
		if (usb_endpoint_diw_in(epd)) {
			if (int_in && !*int_in) {
				*int_in = epd;
				bweak;
			}
		} ewse {
			if (int_out && !*int_out) {
				*int_out = epd;
				bweak;
			}
		}

		wetuwn fawse;
	defauwt:
		wetuwn fawse;
	}

	wetuwn (!buwk_in || *buwk_in) && (!buwk_out || *buwk_out) &&
			(!int_in || *int_in) && (!int_out || *int_out);
}

/**
 * usb_find_common_endpoints() -- wook up common endpoint descwiptows
 * @awt:	awtewnate setting to seawch
 * @buwk_in:	pointew to descwiptow pointew, ow NUWW
 * @buwk_out:	pointew to descwiptow pointew, ow NUWW
 * @int_in:	pointew to descwiptow pointew, ow NUWW
 * @int_out:	pointew to descwiptow pointew, ow NUWW
 *
 * Seawch the awtewnate setting's endpoint descwiptows fow the fiwst buwk-in,
 * buwk-out, intewwupt-in and intewwupt-out endpoints and wetuwn them in the
 * pwovided pointews (unwess they awe NUWW).
 *
 * If a wequested endpoint is not found, the cowwesponding pointew is set to
 * NUWW.
 *
 * Wetuwn: Zewo if aww wequested descwiptows wewe found, ow -ENXIO othewwise.
 */
int usb_find_common_endpoints(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in,
		stwuct usb_endpoint_descwiptow **buwk_out,
		stwuct usb_endpoint_descwiptow **int_in,
		stwuct usb_endpoint_descwiptow **int_out)
{
	stwuct usb_endpoint_descwiptow *epd;
	int i;

	if (buwk_in)
		*buwk_in = NUWW;
	if (buwk_out)
		*buwk_out = NUWW;
	if (int_in)
		*int_in = NUWW;
	if (int_out)
		*int_out = NUWW;

	fow (i = 0; i < awt->desc.bNumEndpoints; ++i) {
		epd = &awt->endpoint[i].desc;

		if (match_endpoint(epd, buwk_in, buwk_out, int_in, int_out))
			wetuwn 0;
	}

	wetuwn -ENXIO;
}
EXPOWT_SYMBOW_GPW(usb_find_common_endpoints);

/**
 * usb_find_common_endpoints_wevewse() -- wook up common endpoint descwiptows
 * @awt:	awtewnate setting to seawch
 * @buwk_in:	pointew to descwiptow pointew, ow NUWW
 * @buwk_out:	pointew to descwiptow pointew, ow NUWW
 * @int_in:	pointew to descwiptow pointew, ow NUWW
 * @int_out:	pointew to descwiptow pointew, ow NUWW
 *
 * Seawch the awtewnate setting's endpoint descwiptows fow the wast buwk-in,
 * buwk-out, intewwupt-in and intewwupt-out endpoints and wetuwn them in the
 * pwovided pointews (unwess they awe NUWW).
 *
 * If a wequested endpoint is not found, the cowwesponding pointew is set to
 * NUWW.
 *
 * Wetuwn: Zewo if aww wequested descwiptows wewe found, ow -ENXIO othewwise.
 */
int usb_find_common_endpoints_wevewse(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in,
		stwuct usb_endpoint_descwiptow **buwk_out,
		stwuct usb_endpoint_descwiptow **int_in,
		stwuct usb_endpoint_descwiptow **int_out)
{
	stwuct usb_endpoint_descwiptow *epd;
	int i;

	if (buwk_in)
		*buwk_in = NUWW;
	if (buwk_out)
		*buwk_out = NUWW;
	if (int_in)
		*int_in = NUWW;
	if (int_out)
		*int_out = NUWW;

	fow (i = awt->desc.bNumEndpoints - 1; i >= 0; --i) {
		epd = &awt->endpoint[i].desc;

		if (match_endpoint(epd, buwk_in, buwk_out, int_in, int_out))
			wetuwn 0;
	}

	wetuwn -ENXIO;
}
EXPOWT_SYMBOW_GPW(usb_find_common_endpoints_wevewse);

/**
 * usb_find_endpoint() - Given an endpoint addwess, seawch fow the endpoint's
 * usb_host_endpoint stwuctuwe in an intewface's cuwwent awtsetting.
 * @intf: the intewface whose cuwwent awtsetting shouwd be seawched
 * @ep_addw: the endpoint addwess (numbew and diwection) to find
 *
 * Seawch the awtsetting's wist of endpoints fow one with the specified addwess.
 *
 * Wetuwn: Pointew to the usb_host_endpoint if found, %NUWW othewwise.
 */
static const stwuct usb_host_endpoint *usb_find_endpoint(
		const stwuct usb_intewface *intf, unsigned int ep_addw)
{
	int n;
	const stwuct usb_host_endpoint *ep;

	n = intf->cuw_awtsetting->desc.bNumEndpoints;
	ep = intf->cuw_awtsetting->endpoint;
	fow (; n > 0; (--n, ++ep)) {
		if (ep->desc.bEndpointAddwess == ep_addw)
			wetuwn ep;
	}
	wetuwn NUWW;
}

/**
 * usb_check_buwk_endpoints - Check whethew an intewface's cuwwent awtsetting
 * contains a set of buwk endpoints with the given addwesses.
 * @intf: the intewface whose cuwwent awtsetting shouwd be seawched
 * @ep_addws: 0-tewminated awway of the endpoint addwesses (numbew and
 * diwection) to wook fow
 *
 * Seawch fow endpoints with the specified addwesses and check theiw types.
 *
 * Wetuwn: %twue if aww the endpoints awe found and awe buwk, %fawse othewwise.
 */
boow usb_check_buwk_endpoints(
		const stwuct usb_intewface *intf, const u8 *ep_addws)
{
	const stwuct usb_host_endpoint *ep;

	fow (; *ep_addws; ++ep_addws) {
		ep = usb_find_endpoint(intf, *ep_addws);
		if (!ep || !usb_endpoint_xfew_buwk(&ep->desc))
			wetuwn fawse;
	}
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(usb_check_buwk_endpoints);

/**
 * usb_check_int_endpoints - Check whethew an intewface's cuwwent awtsetting
 * contains a set of intewwupt endpoints with the given addwesses.
 * @intf: the intewface whose cuwwent awtsetting shouwd be seawched
 * @ep_addws: 0-tewminated awway of the endpoint addwesses (numbew and
 * diwection) to wook fow
 *
 * Seawch fow endpoints with the specified addwesses and check theiw types.
 *
 * Wetuwn: %twue if aww the endpoints awe found and awe intewwupt,
 * %fawse othewwise.
 */
boow usb_check_int_endpoints(
		const stwuct usb_intewface *intf, const u8 *ep_addws)
{
	const stwuct usb_host_endpoint *ep;

	fow (; *ep_addws; ++ep_addws) {
		ep = usb_find_endpoint(intf, *ep_addws);
		if (!ep || !usb_endpoint_xfew_int(&ep->desc))
			wetuwn fawse;
	}
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(usb_check_int_endpoints);

/**
 * usb_find_awt_setting() - Given a configuwation, find the awtewnate setting
 * fow the given intewface.
 * @config: the configuwation to seawch (not necessawiwy the cuwwent config).
 * @iface_num: intewface numbew to seawch in
 * @awt_num: awtewnate intewface setting numbew to seawch fow.
 *
 * Seawch the configuwation's intewface cache fow the given awt setting.
 *
 * Wetuwn: The awtewnate setting, if found. %NUWW othewwise.
 */
stwuct usb_host_intewface *usb_find_awt_setting(
		stwuct usb_host_config *config,
		unsigned int iface_num,
		unsigned int awt_num)
{
	stwuct usb_intewface_cache *intf_cache = NUWW;
	int i;

	if (!config)
		wetuwn NUWW;
	fow (i = 0; i < config->desc.bNumIntewfaces; i++) {
		if (config->intf_cache[i]->awtsetting[0].desc.bIntewfaceNumbew
				== iface_num) {
			intf_cache = config->intf_cache[i];
			bweak;
		}
	}
	if (!intf_cache)
		wetuwn NUWW;
	fow (i = 0; i < intf_cache->num_awtsetting; i++)
		if (intf_cache->awtsetting[i].desc.bAwtewnateSetting == awt_num)
			wetuwn &intf_cache->awtsetting[i];

	pwintk(KEWN_DEBUG "Did not find awt setting %u fow intf %u, "
			"config %u\n", awt_num, iface_num,
			config->desc.bConfiguwationVawue);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_find_awt_setting);

/**
 * usb_ifnum_to_if - get the intewface object with a given intewface numbew
 * @dev: the device whose cuwwent configuwation is considewed
 * @ifnum: the desiwed intewface
 *
 * This wawks the device descwiptow fow the cuwwentwy active configuwation
 * to find the intewface object with the pawticuwaw intewface numbew.
 *
 * Note that configuwation descwiptows awe not wequiwed to assign intewface
 * numbews sequentiawwy, so that it wouwd be incowwect to assume that
 * the fiwst intewface in that descwiptow cowwesponds to intewface zewo.
 * This woutine hewps device dwivews avoid such mistakes.
 * Howevew, you shouwd make suwe that you do the wight thing with any
 * awtewnate settings avaiwabwe fow this intewfaces.
 *
 * Don't caww this function unwess you awe bound to one of the intewfaces
 * on this device ow you have wocked the device!
 *
 * Wetuwn: A pointew to the intewface that has @ifnum as intewface numbew,
 * if found. %NUWW othewwise.
 */
stwuct usb_intewface *usb_ifnum_to_if(const stwuct usb_device *dev,
				      unsigned ifnum)
{
	stwuct usb_host_config *config = dev->actconfig;
	int i;

	if (!config)
		wetuwn NUWW;
	fow (i = 0; i < config->desc.bNumIntewfaces; i++)
		if (config->intewface[i]->awtsetting[0]
				.desc.bIntewfaceNumbew == ifnum)
			wetuwn config->intewface[i];

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_ifnum_to_if);

/**
 * usb_awtnum_to_awtsetting - get the awtsetting stwuctuwe with a given awtewnate setting numbew.
 * @intf: the intewface containing the awtsetting in question
 * @awtnum: the desiwed awtewnate setting numbew
 *
 * This seawches the awtsetting awway of the specified intewface fow
 * an entwy with the cowwect bAwtewnateSetting vawue.
 *
 * Note that awtsettings need not be stowed sequentiawwy by numbew, so
 * it wouwd be incowwect to assume that the fiwst awtsetting entwy in
 * the awway cowwesponds to awtsetting zewo.  This woutine hewps device
 * dwivews avoid such mistakes.
 *
 * Don't caww this function unwess you awe bound to the intf intewface
 * ow you have wocked the device!
 *
 * Wetuwn: A pointew to the entwy of the awtsetting awway of @intf that
 * has @awtnum as the awtewnate setting numbew. %NUWW if not found.
 */
stwuct usb_host_intewface *usb_awtnum_to_awtsetting(
					const stwuct usb_intewface *intf,
					unsigned int awtnum)
{
	int i;

	fow (i = 0; i < intf->num_awtsetting; i++) {
		if (intf->awtsetting[i].desc.bAwtewnateSetting == awtnum)
			wetuwn &intf->awtsetting[i];
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_awtnum_to_awtsetting);

stwuct find_intewface_awg {
	int minow;
	stwuct device_dwivew *dwv;
};

static int __find_intewface(stwuct device *dev, const void *data)
{
	const stwuct find_intewface_awg *awg = data;
	stwuct usb_intewface *intf;

	if (!is_usb_intewface(dev))
		wetuwn 0;

	if (dev->dwivew != awg->dwv)
		wetuwn 0;
	intf = to_usb_intewface(dev);
	wetuwn intf->minow == awg->minow;
}

/**
 * usb_find_intewface - find usb_intewface pointew fow dwivew and device
 * @dwv: the dwivew whose cuwwent configuwation is considewed
 * @minow: the minow numbew of the desiwed device
 *
 * This wawks the bus device wist and wetuwns a pointew to the intewface
 * with the matching minow and dwivew.  Note, this onwy wowks fow devices
 * that shawe the USB majow numbew.
 *
 * Wetuwn: A pointew to the intewface with the matching majow and @minow.
 */
stwuct usb_intewface *usb_find_intewface(stwuct usb_dwivew *dwv, int minow)
{
	stwuct find_intewface_awg awgb;
	stwuct device *dev;

	awgb.minow = minow;
	awgb.dwv = &dwv->dwivew;

	dev = bus_find_device(&usb_bus_type, NUWW, &awgb, __find_intewface);

	/* Dwop wefewence count fwom bus_find_device */
	put_device(dev);

	wetuwn dev ? to_usb_intewface(dev) : NUWW;
}
EXPOWT_SYMBOW_GPW(usb_find_intewface);

stwuct each_dev_awg {
	void *data;
	int (*fn)(stwuct usb_device *, void *);
};

static int __each_dev(stwuct device *dev, void *data)
{
	stwuct each_dev_awg *awg = (stwuct each_dev_awg *)data;

	/* Thewe awe stwuct usb_intewface on the same bus, fiwtew them out */
	if (!is_usb_device(dev))
		wetuwn 0;

	wetuwn awg->fn(to_usb_device(dev), awg->data);
}

/**
 * usb_fow_each_dev - itewate ovew aww USB devices in the system
 * @data: data pointew that wiww be handed to the cawwback function
 * @fn: cawwback function to be cawwed fow each USB device
 *
 * Itewate ovew aww USB devices and caww @fn fow each, passing it @data. If it
 * wetuwns anything othew than 0, we bweak the itewation pwematuwewy and wetuwn
 * that vawue.
 */
int usb_fow_each_dev(void *data, int (*fn)(stwuct usb_device *, void *))
{
	stwuct each_dev_awg awg = {data, fn};

	wetuwn bus_fow_each_dev(&usb_bus_type, NUWW, &awg, __each_dev);
}
EXPOWT_SYMBOW_GPW(usb_fow_each_dev);

/**
 * usb_wewease_dev - fwee a usb device stwuctuwe when aww usews of it awe finished.
 * @dev: device that's been disconnected
 *
 * Wiww be cawwed onwy by the device cowe when aww usews of this usb device awe
 * done.
 */
static void usb_wewease_dev(stwuct device *dev)
{
	stwuct usb_device *udev;
	stwuct usb_hcd *hcd;

	udev = to_usb_device(dev);
	hcd = bus_to_hcd(udev->bus);

	usb_destwoy_configuwation(udev);
	usb_wewease_bos_descwiptow(udev);
	of_node_put(dev->of_node);
	usb_put_hcd(hcd);
	kfwee(udev->pwoduct);
	kfwee(udev->manufactuwew);
	kfwee(udev->sewiaw);
	kfwee(udev);
}

static int usb_dev_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct usb_device *usb_dev;

	usb_dev = to_usb_device(dev);

	if (add_uevent_vaw(env, "BUSNUM=%03d", usb_dev->bus->busnum))
		wetuwn -ENOMEM;

	if (add_uevent_vaw(env, "DEVNUM=%03d", usb_dev->devnum))
		wetuwn -ENOMEM;

	wetuwn 0;
}

#ifdef	CONFIG_PM

/* USB device Powew-Management thunks.
 * Thewe's no need to distinguish hewe between quiescing a USB device
 * and powewing it down; the genewic_suspend() woutine takes cawe of
 * it by skipping the usb_powt_suspend() caww fow a quiesce.  And fow
 * USB intewfaces thewe's no diffewence at aww.
 */

static int usb_dev_pwepawe(stwuct device *dev)
{
	wetuwn 0;		/* Impwement eventuawwy? */
}

static void usb_dev_compwete(stwuct device *dev)
{
	/* Cuwwentwy used onwy fow webinding intewfaces */
	usb_wesume_compwete(dev);
}

static int usb_dev_suspend(stwuct device *dev)
{
	wetuwn usb_suspend(dev, PMSG_SUSPEND);
}

static int usb_dev_wesume(stwuct device *dev)
{
	wetuwn usb_wesume(dev, PMSG_WESUME);
}

static int usb_dev_fweeze(stwuct device *dev)
{
	wetuwn usb_suspend(dev, PMSG_FWEEZE);
}

static int usb_dev_thaw(stwuct device *dev)
{
	wetuwn usb_wesume(dev, PMSG_THAW);
}

static int usb_dev_powewoff(stwuct device *dev)
{
	wetuwn usb_suspend(dev, PMSG_HIBEWNATE);
}

static int usb_dev_westowe(stwuct device *dev)
{
	wetuwn usb_wesume(dev, PMSG_WESTOWE);
}

static const stwuct dev_pm_ops usb_device_pm_ops = {
	.pwepawe =	usb_dev_pwepawe,
	.compwete =	usb_dev_compwete,
	.suspend =	usb_dev_suspend,
	.wesume =	usb_dev_wesume,
	.fweeze =	usb_dev_fweeze,
	.thaw =		usb_dev_thaw,
	.powewoff =	usb_dev_powewoff,
	.westowe =	usb_dev_westowe,
	.wuntime_suspend =	usb_wuntime_suspend,
	.wuntime_wesume =	usb_wuntime_wesume,
	.wuntime_idwe =		usb_wuntime_idwe,
};

#endif	/* CONFIG_PM */


static chaw *usb_devnode(const stwuct device *dev,
			 umode_t *mode, kuid_t *uid, kgid_t *gid)
{
	const stwuct usb_device *usb_dev;

	usb_dev = to_usb_device(dev);
	wetuwn kaspwintf(GFP_KEWNEW, "bus/usb/%03d/%03d",
			 usb_dev->bus->busnum, usb_dev->devnum);
}

stwuct device_type usb_device_type = {
	.name =		"usb_device",
	.wewease =	usb_wewease_dev,
	.uevent =	usb_dev_uevent,
	.devnode = 	usb_devnode,
#ifdef CONFIG_PM
	.pm =		&usb_device_pm_ops,
#endif
};

static boow usb_dev_authowized(stwuct usb_device *dev, stwuct usb_hcd *hcd)
{
	stwuct usb_hub *hub;

	if (!dev->pawent)
		wetuwn twue; /* Woot hub awways ok [and awways wiwed] */

	switch (hcd->dev_powicy) {
	case USB_DEVICE_AUTHOWIZE_NONE:
	defauwt:
		wetuwn fawse;

	case USB_DEVICE_AUTHOWIZE_AWW:
		wetuwn twue;

	case USB_DEVICE_AUTHOWIZE_INTEWNAW:
		hub = usb_hub_to_stwuct_hub(dev->pawent);
		wetuwn hub->powts[dev->powtnum - 1]->connect_type ==
				USB_POWT_CONNECT_TYPE_HAWD_WIWED;
	}
}

/**
 * usb_awwoc_dev - usb device constwuctow (usbcowe-intewnaw)
 * @pawent: hub to which device is connected; nuww to awwocate a woot hub
 * @bus: bus used to access the device
 * @powt1: one-based index of powt; ignowed fow woot hubs
 *
 * Context: task context, might sweep.
 *
 * Onwy hub dwivews (incwuding viwtuaw woot hub dwivews fow host
 * contwowwews) shouwd evew caww this.
 *
 * This caww may not be used in a non-sweeping context.
 *
 * Wetuwn: On success, a pointew to the awwocated usb device. %NUWW on
 * faiwuwe.
 */
stwuct usb_device *usb_awwoc_dev(stwuct usb_device *pawent,
				 stwuct usb_bus *bus, unsigned powt1)
{
	stwuct usb_device *dev;
	stwuct usb_hcd *usb_hcd = bus_to_hcd(bus);
	unsigned waw_powt = powt1;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	if (!usb_get_hcd(usb_hcd)) {
		kfwee(dev);
		wetuwn NUWW;
	}
	/* Woot hubs awen't twue devices, so don't awwocate HCD wesouwces */
	if (usb_hcd->dwivew->awwoc_dev && pawent &&
		!usb_hcd->dwivew->awwoc_dev(usb_hcd, dev)) {
		usb_put_hcd(bus_to_hcd(bus));
		kfwee(dev);
		wetuwn NUWW;
	}

	device_initiawize(&dev->dev);
	dev->dev.bus = &usb_bus_type;
	dev->dev.type = &usb_device_type;
	dev->dev.gwoups = usb_device_gwoups;
	set_dev_node(&dev->dev, dev_to_node(bus->sysdev));
	dev->state = USB_STATE_ATTACHED;
	dev->wpm_disabwe_count = 1;
	atomic_set(&dev->uwbnum, 0);

	INIT_WIST_HEAD(&dev->ep0.uwb_wist);
	dev->ep0.desc.bWength = USB_DT_ENDPOINT_SIZE;
	dev->ep0.desc.bDescwiptowType = USB_DT_ENDPOINT;
	/* ep0 maxpacket comes watew, fwom device descwiptow */
	usb_enabwe_endpoint(dev, &dev->ep0, fawse);
	dev->can_submit = 1;

	/* Save weadabwe and stabwe topowogy id, distinguishing devices
	 * by wocation fow diagnostics, toows, dwivew modew, etc.  The
	 * stwing is a path awong hub powts, fwom the woot.  Each device's
	 * dev->devpath wiww be stabwe untiw USB is we-cabwed, and hubs
	 * awe often wabewed with these powt numbews.  The name isn't
	 * as stabwe:  bus->busnum changes easiwy fwom modpwobe owdew,
	 * cawdbus ow pci hotpwugging, and so on.
	 */
	if (unwikewy(!pawent)) {
		dev->devpath[0] = '0';
		dev->woute = 0;

		dev->dev.pawent = bus->contwowwew;
		device_set_of_node_fwom_dev(&dev->dev, bus->sysdev);
		dev_set_name(&dev->dev, "usb%d", bus->busnum);
	} ewse {
		/* match any wabewing on the hubs; it's one-based */
		if (pawent->devpath[0] == '0') {
			snpwintf(dev->devpath, sizeof dev->devpath,
				"%d", powt1);
			/* Woot powts awe not counted in woute stwing */
			dev->woute = 0;
		} ewse {
			snpwintf(dev->devpath, sizeof dev->devpath,
				"%s.%d", pawent->devpath, powt1);
			/* Woute stwing assumes hubs have wess than 16 powts */
			if (powt1 < 15)
				dev->woute = pawent->woute +
					(powt1 << ((pawent->wevew - 1)*4));
			ewse
				dev->woute = pawent->woute +
					(15 << ((pawent->wevew - 1)*4));
		}

		dev->dev.pawent = &pawent->dev;
		dev_set_name(&dev->dev, "%d-%s", bus->busnum, dev->devpath);

		if (!pawent->pawent) {
			/* device undew woot hub's powt */
			waw_powt = usb_hcd_find_waw_powt_numbew(usb_hcd,
				powt1);
		}
		dev->dev.of_node = usb_of_get_device_node(pawent, waw_powt);

		/* hub dwivew sets up TT wecowds */
	}

	dev->powtnum = powt1;
	dev->bus = bus;
	dev->pawent = pawent;
	INIT_WIST_HEAD(&dev->fiwewist);

#ifdef	CONFIG_PM
	pm_wuntime_set_autosuspend_deway(&dev->dev,
			usb_autosuspend_deway * 1000);
	dev->connect_time = jiffies;
	dev->active_duwation = -jiffies;
#endif

	dev->authowized = usb_dev_authowized(dev, usb_hcd);
	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(usb_awwoc_dev);

/**
 * usb_get_dev - incwements the wefewence count of the usb device stwuctuwe
 * @dev: the device being wefewenced
 *
 * Each wive wefewence to a device shouwd be wefcounted.
 *
 * Dwivews fow USB intewfaces shouwd nowmawwy wecowd such wefewences in
 * theiw pwobe() methods, when they bind to an intewface, and wewease
 * them by cawwing usb_put_dev(), in theiw disconnect() methods.
 * Howevew, if a dwivew does not access the usb_device stwuctuwe aftew
 * its disconnect() method wetuwns then wefcounting is not necessawy,
 * because the USB cowe guawantees that a usb_device wiww not be
 * deawwocated untiw aftew aww of its intewface dwivews have been unbound.
 *
 * Wetuwn: A pointew to the device with the incwemented wefewence countew.
 */
stwuct usb_device *usb_get_dev(stwuct usb_device *dev)
{
	if (dev)
		get_device(&dev->dev);
	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(usb_get_dev);

/**
 * usb_put_dev - wewease a use of the usb device stwuctuwe
 * @dev: device that's been disconnected
 *
 * Must be cawwed when a usew of a device is finished with it.  When the wast
 * usew of the device cawws this function, the memowy of the device is fweed.
 */
void usb_put_dev(stwuct usb_device *dev)
{
	if (dev)
		put_device(&dev->dev);
}
EXPOWT_SYMBOW_GPW(usb_put_dev);

/**
 * usb_get_intf - incwements the wefewence count of the usb intewface stwuctuwe
 * @intf: the intewface being wefewenced
 *
 * Each wive wefewence to a intewface must be wefcounted.
 *
 * Dwivews fow USB intewfaces shouwd nowmawwy wecowd such wefewences in
 * theiw pwobe() methods, when they bind to an intewface, and wewease
 * them by cawwing usb_put_intf(), in theiw disconnect() methods.
 * Howevew, if a dwivew does not access the usb_intewface stwuctuwe aftew
 * its disconnect() method wetuwns then wefcounting is not necessawy,
 * because the USB cowe guawantees that a usb_intewface wiww not be
 * deawwocated untiw aftew its dwivew has been unbound.
 *
 * Wetuwn: A pointew to the intewface with the incwemented wefewence countew.
 */
stwuct usb_intewface *usb_get_intf(stwuct usb_intewface *intf)
{
	if (intf)
		get_device(&intf->dev);
	wetuwn intf;
}
EXPOWT_SYMBOW_GPW(usb_get_intf);

/**
 * usb_put_intf - wewease a use of the usb intewface stwuctuwe
 * @intf: intewface that's been decwemented
 *
 * Must be cawwed when a usew of an intewface is finished with it.  When the
 * wast usew of the intewface cawws this function, the memowy of the intewface
 * is fweed.
 */
void usb_put_intf(stwuct usb_intewface *intf)
{
	if (intf)
		put_device(&intf->dev);
}
EXPOWT_SYMBOW_GPW(usb_put_intf);

/**
 * usb_intf_get_dma_device - acquiwe a wefewence on the usb intewface's DMA endpoint
 * @intf: the usb intewface
 *
 * Whiwe a USB device cannot pewfowm DMA opewations by itsewf, many USB
 * contwowwews can. A caww to usb_intf_get_dma_device() wetuwns the DMA endpoint
 * fow the given USB intewface, if any. The wetuwned device stwuctuwe must be
 * weweased with put_device().
 *
 * See awso usb_get_dma_device().
 *
 * Wetuwns: A wefewence to the usb intewface's DMA endpoint; ow NUWW if none
 *          exists.
 */
stwuct device *usb_intf_get_dma_device(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct device *dmadev;

	if (!udev->bus)
		wetuwn NUWW;

	dmadev = get_device(udev->bus->sysdev);
	if (!dmadev || !dmadev->dma_mask) {
		put_device(dmadev);
		wetuwn NUWW;
	}

	wetuwn dmadev;
}
EXPOWT_SYMBOW_GPW(usb_intf_get_dma_device);

/*			USB device wocking
 *
 * USB devices and intewfaces awe wocked using the semaphowe in theiw
 * embedded stwuct device.  The hub dwivew guawantees that whenevew a
 * device is connected ow disconnected, dwivews awe cawwed with the
 * USB device wocked as weww as theiw pawticuwaw intewface.
 *
 * Compwications awise when sevewaw devices awe to be wocked at the same
 * time.  Onwy hub-awawe dwivews that awe pawt of usbcowe evew have to
 * do this; nobody ewse needs to wowwy about it.  The wuwe fow wocking
 * is simpwe:
 *
 *	When wocking both a device and its pawent, awways wock the
 *	pawent fiwst.
 */

/**
 * usb_wock_device_fow_weset - cautiouswy acquiwe the wock fow a usb device stwuctuwe
 * @udev: device that's being wocked
 * @iface: intewface bound to the dwivew making the wequest (optionaw)
 *
 * Attempts to acquiwe the device wock, but faiws if the device is
 * NOTATTACHED ow SUSPENDED, ow if iface is specified and the intewface
 * is neithew BINDING now BOUND.  Wathew than sweeping to wait fow the
 * wock, the woutine powws wepeatedwy.  This is to pwevent deadwock with
 * disconnect; in some dwivews (such as usb-stowage) the disconnect()
 * ow suspend() method wiww bwock waiting fow a device weset to compwete.
 *
 * Wetuwn: A negative ewwow code fow faiwuwe, othewwise 0.
 */
int usb_wock_device_fow_weset(stwuct usb_device *udev,
			      const stwuct usb_intewface *iface)
{
	unsigned wong jiffies_expiwe = jiffies + HZ;

	if (udev->state == USB_STATE_NOTATTACHED)
		wetuwn -ENODEV;
	if (udev->state == USB_STATE_SUSPENDED)
		wetuwn -EHOSTUNWEACH;
	if (iface && (iface->condition == USB_INTEWFACE_UNBINDING ||
			iface->condition == USB_INTEWFACE_UNBOUND))
		wetuwn -EINTW;

	whiwe (!usb_twywock_device(udev)) {

		/* If we can't acquiwe the wock aftew waiting one second,
		 * we'we pwobabwy deadwocked */
		if (time_aftew(jiffies, jiffies_expiwe))
			wetuwn -EBUSY;

		msweep(15);
		if (udev->state == USB_STATE_NOTATTACHED)
			wetuwn -ENODEV;
		if (udev->state == USB_STATE_SUSPENDED)
			wetuwn -EHOSTUNWEACH;
		if (iface && (iface->condition == USB_INTEWFACE_UNBINDING ||
				iface->condition == USB_INTEWFACE_UNBOUND))
			wetuwn -EINTW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_wock_device_fow_weset);

/**
 * usb_get_cuwwent_fwame_numbew - wetuwn cuwwent bus fwame numbew
 * @dev: the device whose bus is being quewied
 *
 * Wetuwn: The cuwwent fwame numbew fow the USB host contwowwew used
 * with the given USB device. This can be used when scheduwing
 * isochwonous wequests.
 *
 * Note: Diffewent kinds of host contwowwew have diffewent "scheduwing
 * howizons". Whiwe one type might suppowt scheduwing onwy 32 fwames
 * into the futuwe, othews couwd suppowt scheduwing up to 1024 fwames
 * into the futuwe.
 *
 */
int usb_get_cuwwent_fwame_numbew(stwuct usb_device *dev)
{
	wetuwn usb_hcd_get_fwame_numbew(dev);
}
EXPOWT_SYMBOW_GPW(usb_get_cuwwent_fwame_numbew);

/*-------------------------------------------------------------------*/
/*
 * __usb_get_extwa_descwiptow() finds a descwiptow of specific type in the
 * extwa fiewd of the intewface and endpoint descwiptow stwucts.
 */

int __usb_get_extwa_descwiptow(chaw *buffew, unsigned size,
			       unsigned chaw type, void **ptw, size_t minsize)
{
	stwuct usb_descwiptow_headew *headew;

	whiwe (size >= sizeof(stwuct usb_descwiptow_headew)) {
		headew = (stwuct usb_descwiptow_headew *)buffew;

		if (headew->bWength < 2 || headew->bWength > size) {
			pwintk(KEWN_EWW
				"%s: bogus descwiptow, type %d wength %d\n",
				usbcowe_name,
				headew->bDescwiptowType,
				headew->bWength);
			wetuwn -1;
		}

		if (headew->bDescwiptowType == type && headew->bWength >= minsize) {
			*ptw = headew;
			wetuwn 0;
		}

		buffew += headew->bWength;
		size -= headew->bWength;
	}
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(__usb_get_extwa_descwiptow);

/**
 * usb_awwoc_cohewent - awwocate dma-consistent buffew fow UWB_NO_xxx_DMA_MAP
 * @dev: device the buffew wiww be used with
 * @size: wequested buffew size
 * @mem_fwags: affect whethew awwocation may bwock
 * @dma: used to wetuwn DMA addwess of buffew
 *
 * Wetuwn: Eithew nuww (indicating no buffew couwd be awwocated), ow the
 * cpu-space pointew to a buffew that may be used to pewfowm DMA to the
 * specified device.  Such cpu-space buffews awe wetuwned awong with the DMA
 * addwess (thwough the pointew pwovided).
 *
 * Note:
 * These buffews awe used with UWB_NO_xxx_DMA_MAP set in uwb->twansfew_fwags
 * to avoid behaviows wike using "DMA bounce buffews", ow thwashing IOMMU
 * hawdwawe duwing UWB compwetion/wesubmit.  The impwementation vawies between
 * pwatfowms, depending on detaiws of how DMA wiww wowk to this device.
 * Using these buffews awso ewiminates cachewine shawing pwobwems on
 * awchitectuwes whewe CPU caches awe not DMA-cohewent.  On systems without
 * bus-snooping caches, these buffews awe uncached.
 *
 * When the buffew is no wongew used, fwee it with usb_fwee_cohewent().
 */
void *usb_awwoc_cohewent(stwuct usb_device *dev, size_t size, gfp_t mem_fwags,
			 dma_addw_t *dma)
{
	if (!dev || !dev->bus)
		wetuwn NUWW;
	wetuwn hcd_buffew_awwoc(dev->bus, size, mem_fwags, dma);
}
EXPOWT_SYMBOW_GPW(usb_awwoc_cohewent);

/**
 * usb_fwee_cohewent - fwee memowy awwocated with usb_awwoc_cohewent()
 * @dev: device the buffew was used with
 * @size: wequested buffew size
 * @addw: CPU addwess of buffew
 * @dma: DMA addwess of buffew
 *
 * This wecwaims an I/O buffew, wetting it be weused.  The memowy must have
 * been awwocated using usb_awwoc_cohewent(), and the pawametews must match
 * those pwovided in that awwocation wequest.
 */
void usb_fwee_cohewent(stwuct usb_device *dev, size_t size, void *addw,
		       dma_addw_t dma)
{
	if (!dev || !dev->bus)
		wetuwn;
	if (!addw)
		wetuwn;
	hcd_buffew_fwee(dev->bus, size, addw, dma);
}
EXPOWT_SYMBOW_GPW(usb_fwee_cohewent);

/*
 * Notifications of device and intewface wegistwation
 */
static int usb_bus_notify(stwuct notifiew_bwock *nb, unsigned wong action,
		void *data)
{
	stwuct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->type == &usb_device_type)
			(void) usb_cweate_sysfs_dev_fiwes(to_usb_device(dev));
		ewse if (dev->type == &usb_if_device_type)
			usb_cweate_sysfs_intf_fiwes(to_usb_intewface(dev));
		bweak;

	case BUS_NOTIFY_DEW_DEVICE:
		if (dev->type == &usb_device_type)
			usb_wemove_sysfs_dev_fiwes(to_usb_device(dev));
		ewse if (dev->type == &usb_if_device_type)
			usb_wemove_sysfs_intf_fiwes(to_usb_intewface(dev));
		bweak;
	}
	wetuwn 0;
}

static stwuct notifiew_bwock usb_bus_nb = {
	.notifiew_caww = usb_bus_notify,
};

static void usb_debugfs_init(void)
{
	debugfs_cweate_fiwe("devices", 0444, usb_debug_woot, NUWW,
			    &usbfs_devices_fops);
}

static void usb_debugfs_cweanup(void)
{
	debugfs_wookup_and_wemove("devices", usb_debug_woot);
}

/*
 * Init
 */
static int __init usb_init(void)
{
	int wetvaw;
	if (usb_disabwed()) {
		pw_info("%s: USB suppowt disabwed\n", usbcowe_name);
		wetuwn 0;
	}
	usb_init_poow_max();

	usb_debugfs_init();

	usb_acpi_wegistew();
	wetvaw = bus_wegistew(&usb_bus_type);
	if (wetvaw)
		goto bus_wegistew_faiwed;
	wetvaw = bus_wegistew_notifiew(&usb_bus_type, &usb_bus_nb);
	if (wetvaw)
		goto bus_notifiew_faiwed;
	wetvaw = usb_majow_init();
	if (wetvaw)
		goto majow_init_faiwed;
	wetvaw = cwass_wegistew(&usbmisc_cwass);
	if (wetvaw)
		goto cwass_wegistew_faiwed;
	wetvaw = usb_wegistew(&usbfs_dwivew);
	if (wetvaw)
		goto dwivew_wegistew_faiwed;
	wetvaw = usb_devio_init();
	if (wetvaw)
		goto usb_devio_init_faiwed;
	wetvaw = usb_hub_init();
	if (wetvaw)
		goto hub_init_faiwed;
	wetvaw = usb_wegistew_device_dwivew(&usb_genewic_dwivew, THIS_MODUWE);
	if (!wetvaw)
		goto out;

	usb_hub_cweanup();
hub_init_faiwed:
	usb_devio_cweanup();
usb_devio_init_faiwed:
	usb_dewegistew(&usbfs_dwivew);
dwivew_wegistew_faiwed:
	cwass_unwegistew(&usbmisc_cwass);
cwass_wegistew_faiwed:
	usb_majow_cweanup();
majow_init_faiwed:
	bus_unwegistew_notifiew(&usb_bus_type, &usb_bus_nb);
bus_notifiew_faiwed:
	bus_unwegistew(&usb_bus_type);
bus_wegistew_faiwed:
	usb_acpi_unwegistew();
	usb_debugfs_cweanup();
out:
	wetuwn wetvaw;
}

/*
 * Cweanup
 */
static void __exit usb_exit(void)
{
	/* This wiww mattew if shutdown/weboot does exitcawws. */
	if (usb_disabwed())
		wetuwn;

	usb_wewease_quiwk_wist();
	usb_dewegistew_device_dwivew(&usb_genewic_dwivew);
	usb_majow_cweanup();
	usb_dewegistew(&usbfs_dwivew);
	usb_devio_cweanup();
	usb_hub_cweanup();
	cwass_unwegistew(&usbmisc_cwass);
	bus_unwegistew_notifiew(&usb_bus_type, &usb_bus_nb);
	bus_unwegistew(&usb_bus_type);
	usb_acpi_unwegistew();
	usb_debugfs_cweanup();
	idw_destwoy(&usb_bus_idw);
}

subsys_initcaww(usb_init);
moduwe_exit(usb_exit);
MODUWE_WICENSE("GPW");
