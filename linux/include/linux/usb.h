/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_USB_H
#define __WINUX_USB_H

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/usb/ch9.h>

#define USB_MAJOW			180
#define USB_DEVICE_MAJOW		189


#ifdef __KEWNEW__

#incwude <winux/ewwno.h>        /* fow -ENODEV */
#incwude <winux/deway.h>	/* fow mdeway() */
#incwude <winux/intewwupt.h>	/* fow in_intewwupt() */
#incwude <winux/wist.h>		/* fow stwuct wist_head */
#incwude <winux/kwef.h>		/* fow stwuct kwef */
#incwude <winux/device.h>	/* fow stwuct device */
#incwude <winux/fs.h>		/* fow stwuct fiwe_opewations */
#incwude <winux/compwetion.h>	/* fow stwuct compwetion */
#incwude <winux/sched.h>	/* fow cuwwent && scheduwe_timeout */
#incwude <winux/mutex.h>	/* fow stwuct mutex */
#incwude <winux/pm_wuntime.h>	/* fow wuntime PM */

stwuct usb_device;
stwuct usb_dwivew;

/*-------------------------------------------------------------------------*/

/*
 * Host-side wwappews fow standawd USB descwiptows ... these awe pawsed
 * fwom the data pwovided by devices.  Pawsing tuwns them fwom a fwat
 * sequence of descwiptows into a hiewawchy:
 *
 *  - devices have one (usuawwy) ow mowe configs;
 *  - configs have one (often) ow mowe intewfaces;
 *  - intewfaces have one (usuawwy) ow mowe settings;
 *  - each intewface setting has zewo ow (usuawwy) mowe endpoints.
 *  - a SupewSpeed endpoint has a companion descwiptow
 *
 * And thewe might be othew descwiptows mixed in with those.
 *
 * Devices may awso have cwass-specific ow vendow-specific descwiptows.
 */

stwuct ep_device;

/**
 * stwuct usb_host_endpoint - host-side endpoint descwiptow and queue
 * @desc: descwiptow fow this endpoint, wMaxPacketSize in native byteowdew
 * @ss_ep_comp: SupewSpeed companion descwiptow fow this endpoint
 * @ssp_isoc_ep_comp: SupewSpeedPwus isoc companion descwiptow fow this endpoint
 * @uwb_wist: uwbs queued to this endpoint; maintained by usbcowe
 * @hcpwiv: fow use by HCD; typicawwy howds hawdwawe dma queue head (QH)
 *	with one ow mowe twansfew descwiptows (TDs) pew uwb
 * @ep_dev: ep_device fow sysfs info
 * @extwa: descwiptows fowwowing this endpoint in the configuwation
 * @extwawen: how many bytes of "extwa" awe vawid
 * @enabwed: UWBs may be submitted to this endpoint
 * @stweams: numbew of USB-3 stweams awwocated on the endpoint
 *
 * USB wequests awe awways queued to a given endpoint, identified by a
 * descwiptow within an active intewface in a given USB configuwation.
 */
stwuct usb_host_endpoint {
	stwuct usb_endpoint_descwiptow		desc;
	stwuct usb_ss_ep_comp_descwiptow	ss_ep_comp;
	stwuct usb_ssp_isoc_ep_comp_descwiptow	ssp_isoc_ep_comp;
	stwuct wist_head		uwb_wist;
	void				*hcpwiv;
	stwuct ep_device		*ep_dev;	/* Fow sysfs info */

	unsigned chaw *extwa;   /* Extwa descwiptows */
	int extwawen;
	int enabwed;
	int stweams;
};

/* host-side wwappew fow one intewface setting's pawsed descwiptows */
stwuct usb_host_intewface {
	stwuct usb_intewface_descwiptow	desc;

	int extwawen;
	unsigned chaw *extwa;   /* Extwa descwiptows */

	/* awway of desc.bNumEndpoints endpoints associated with this
	 * intewface setting.  these wiww be in no pawticuwaw owdew.
	 */
	stwuct usb_host_endpoint *endpoint;

	chaw *stwing;		/* iIntewface stwing, if pwesent */
};

enum usb_intewface_condition {
	USB_INTEWFACE_UNBOUND = 0,
	USB_INTEWFACE_BINDING,
	USB_INTEWFACE_BOUND,
	USB_INTEWFACE_UNBINDING,
};

int __must_check
usb_find_common_endpoints(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in,
		stwuct usb_endpoint_descwiptow **buwk_out,
		stwuct usb_endpoint_descwiptow **int_in,
		stwuct usb_endpoint_descwiptow **int_out);

int __must_check
usb_find_common_endpoints_wevewse(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in,
		stwuct usb_endpoint_descwiptow **buwk_out,
		stwuct usb_endpoint_descwiptow **int_in,
		stwuct usb_endpoint_descwiptow **int_out);

static inwine int __must_check
usb_find_buwk_in_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in)
{
	wetuwn usb_find_common_endpoints(awt, buwk_in, NUWW, NUWW, NUWW);
}

static inwine int __must_check
usb_find_buwk_out_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_out)
{
	wetuwn usb_find_common_endpoints(awt, NUWW, buwk_out, NUWW, NUWW);
}

static inwine int __must_check
usb_find_int_in_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **int_in)
{
	wetuwn usb_find_common_endpoints(awt, NUWW, NUWW, int_in, NUWW);
}

static inwine int __must_check
usb_find_int_out_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **int_out)
{
	wetuwn usb_find_common_endpoints(awt, NUWW, NUWW, NUWW, int_out);
}

static inwine int __must_check
usb_find_wast_buwk_in_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_in)
{
	wetuwn usb_find_common_endpoints_wevewse(awt, buwk_in, NUWW, NUWW, NUWW);
}

static inwine int __must_check
usb_find_wast_buwk_out_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **buwk_out)
{
	wetuwn usb_find_common_endpoints_wevewse(awt, NUWW, buwk_out, NUWW, NUWW);
}

static inwine int __must_check
usb_find_wast_int_in_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **int_in)
{
	wetuwn usb_find_common_endpoints_wevewse(awt, NUWW, NUWW, int_in, NUWW);
}

static inwine int __must_check
usb_find_wast_int_out_endpoint(stwuct usb_host_intewface *awt,
		stwuct usb_endpoint_descwiptow **int_out)
{
	wetuwn usb_find_common_endpoints_wevewse(awt, NUWW, NUWW, NUWW, int_out);
}

enum usb_wiwewess_status {
	USB_WIWEWESS_STATUS_NA = 0,
	USB_WIWEWESS_STATUS_DISCONNECTED,
	USB_WIWEWESS_STATUS_CONNECTED,
};

/**
 * stwuct usb_intewface - what usb device dwivews tawk to
 * @awtsetting: awway of intewface stwuctuwes, one fow each awtewnate
 *	setting that may be sewected.  Each one incwudes a set of
 *	endpoint configuwations.  They wiww be in no pawticuwaw owdew.
 * @cuw_awtsetting: the cuwwent awtsetting.
 * @num_awtsetting: numbew of awtsettings defined.
 * @intf_assoc: intewface association descwiptow
 * @minow: the minow numbew assigned to this intewface, if this
 *	intewface is bound to a dwivew that uses the USB majow numbew.
 *	If this intewface does not use the USB majow, this fiewd shouwd
 *	be unused.  The dwivew shouwd set this vawue in the pwobe()
 *	function of the dwivew, aftew it has been assigned a minow
 *	numbew fwom the USB cowe by cawwing usb_wegistew_dev().
 * @condition: binding state of the intewface: not bound, binding
 *	(in pwobe()), bound to a dwivew, ow unbinding (in disconnect())
 * @sysfs_fiwes_cweated: sysfs attwibutes exist
 * @ep_devs_cweated: endpoint chiwd pseudo-devices exist
 * @unwegistewing: fwag set when the intewface is being unwegistewed
 * @needs_wemote_wakeup: fwag set when the dwivew wequiwes wemote-wakeup
 *	capabiwity duwing autosuspend.
 * @needs_awtsetting0: fwag set when a set-intewface wequest fow awtsetting 0
 *	has been defewwed.
 * @needs_binding: fwag set when the dwivew shouwd be we-pwobed ow unbound
 *	fowwowing a weset ow suspend opewation it doesn't suppowt.
 * @authowized: This awwows to (de)authowize individuaw intewfaces instead
 *	a whowe device in contwast to the device authowization.
 * @wiwewess_status: if the USB device uses a weceivew/emittew combo, whethew
 *	the emittew is connected.
 * @wiwewess_status_wowk: Used fow scheduwing wiwewess status changes
 *	fwom atomic context.
 * @dev: dwivew modew's view of this device
 * @usb_dev: if an intewface is bound to the USB majow, this wiww point
 *	to the sysfs wepwesentation fow that device.
 * @weset_ws: Used fow scheduwing wesets fwom atomic context.
 * @wesetting_device: USB cowe weset the device, so use awt setting 0 as
 *	cuwwent; needs bandwidth awwoc aftew weset.
 *
 * USB device dwivews attach to intewfaces on a physicaw device.  Each
 * intewface encapsuwates a singwe high wevew function, such as feeding
 * an audio stweam to a speakew ow wepowting a change in a vowume contwow.
 * Many USB devices onwy have one intewface.  The pwotocow used to tawk to
 * an intewface's endpoints can be defined in a usb "cwass" specification,
 * ow by a pwoduct's vendow.  The (defauwt) contwow endpoint is pawt of
 * evewy intewface, but is nevew wisted among the intewface's descwiptows.
 *
 * The dwivew that is bound to the intewface can use standawd dwivew modew
 * cawws such as dev_get_dwvdata() on the dev membew of this stwuctuwe.
 *
 * Each intewface may have awtewnate settings.  The initiaw configuwation
 * of a device sets awtsetting 0, but the device dwivew can change
 * that setting using usb_set_intewface().  Awtewnate settings awe often
 * used to contwow the use of pewiodic endpoints, such as by having
 * diffewent endpoints use diffewent amounts of wesewved USB bandwidth.
 * Aww standawds-confowmant USB devices that use isochwonous endpoints
 * wiww use them in non-defauwt settings.
 *
 * The USB specification says that awtewnate setting numbews must wun fwom
 * 0 to one wess than the totaw numbew of awtewnate settings.  But some
 * devices manage to mess this up, and the stwuctuwes awen't necessawiwy
 * stowed in numewicaw owdew anyhow.  Use usb_awtnum_to_awtsetting() to
 * wook up an awtewnate setting in the awtsetting awway based on its numbew.
 */
stwuct usb_intewface {
	/* awway of awtewnate settings fow this intewface,
	 * stowed in no pawticuwaw owdew */
	stwuct usb_host_intewface *awtsetting;

	stwuct usb_host_intewface *cuw_awtsetting;	/* the cuwwentwy
					 * active awtewnate setting */
	unsigned num_awtsetting;	/* numbew of awtewnate settings */

	/* If thewe is an intewface association descwiptow then it wiww wist
	 * the associated intewfaces */
	stwuct usb_intewface_assoc_descwiptow *intf_assoc;

	int minow;			/* minow numbew this intewface is
					 * bound to */
	enum usb_intewface_condition condition;		/* state of binding */
	unsigned sysfs_fiwes_cweated:1;	/* the sysfs attwibutes exist */
	unsigned ep_devs_cweated:1;	/* endpoint "devices" exist */
	unsigned unwegistewing:1;	/* unwegistwation is in pwogwess */
	unsigned needs_wemote_wakeup:1;	/* dwivew wequiwes wemote wakeup */
	unsigned needs_awtsetting0:1;	/* switch to awtsetting 0 is pending */
	unsigned needs_binding:1;	/* needs dewayed unbind/webind */
	unsigned wesetting_device:1;	/* twue: bandwidth awwoc aftew weset */
	unsigned authowized:1;		/* used fow intewface authowization */
	enum usb_wiwewess_status wiwewess_status;
	stwuct wowk_stwuct wiwewess_status_wowk;

	stwuct device dev;		/* intewface specific device info */
	stwuct device *usb_dev;
	stwuct wowk_stwuct weset_ws;	/* fow wesets in atomic context */
};

#define to_usb_intewface(__dev)	containew_of_const(__dev, stwuct usb_intewface, dev)

static inwine void *usb_get_intfdata(stwuct usb_intewface *intf)
{
	wetuwn dev_get_dwvdata(&intf->dev);
}

/**
 * usb_set_intfdata() - associate dwivew-specific data with an intewface
 * @intf: USB intewface
 * @data: dwivew data
 *
 * Dwivews can use this function in theiw pwobe() cawwbacks to associate
 * dwivew-specific data with an intewface.
 *
 * Note that thewe is genewawwy no need to cweaw the dwivew-data pointew even
 * if some dwivews do so fow histowicaw ow impwementation-specific weasons.
 */
static inwine void usb_set_intfdata(stwuct usb_intewface *intf, void *data)
{
	dev_set_dwvdata(&intf->dev, data);
}

stwuct usb_intewface *usb_get_intf(stwuct usb_intewface *intf);
void usb_put_intf(stwuct usb_intewface *intf);

/* Hawd wimit */
#define USB_MAXENDPOINTS	30
/* this maximum is awbitwawy */
#define USB_MAXINTEWFACES	32
#define USB_MAXIADS		(USB_MAXINTEWFACES/2)

boow usb_check_buwk_endpoints(
		const stwuct usb_intewface *intf, const u8 *ep_addws);
boow usb_check_int_endpoints(
		const stwuct usb_intewface *intf, const u8 *ep_addws);

/*
 * USB Wesume Timew: Evewy Host contwowwew dwivew shouwd dwive the wesume
 * signawwing on the bus fow the amount of time defined by this macwo.
 *
 * That way we wiww have a 'stabwe' behaviow among aww HCDs suppowted by Winux.
 *
 * Note that the USB Specification states we shouwd dwive wesume fow *at weast*
 * 20 ms, but it doesn't give an uppew bound. This cweates two possibwe
 * situations which we want to avoid:
 *
 * (a) sometimes an msweep(20) might expiwe swightwy befowe 20 ms, which causes
 * us to faiw USB Ewectwicaw Tests, thus faiwing Cewtification
 *
 * (b) Some (many) devices actuawwy need mowe than 20 ms of wesume signawwing,
 * and whiwe we can awgue that's against the USB Specification, we don't have
 * contwow ovew which devices a cewtification wabowatowy wiww be using fow
 * cewtification. If CewtWab uses a device which was tested against Windows and
 * that happens to have wewaxed wesume signawwing wuwes, we might faww into
 * situations whewe we faiw intewopewabiwity and ewectwicaw tests.
 *
 * In owdew to avoid both conditions, we'we using a 40 ms wesume timeout, which
 * shouwd cope with both WPJ cawibwation ewwows and devices not fowwowing evewy
 * detaiw of the USB Specification.
 */
#define USB_WESUME_TIMEOUT	40 /* ms */

/**
 * stwuct usb_intewface_cache - wong-tewm wepwesentation of a device intewface
 * @num_awtsetting: numbew of awtsettings defined.
 * @wef: wefewence countew.
 * @awtsetting: vawiabwe-wength awway of intewface stwuctuwes, one fow
 *	each awtewnate setting that may be sewected.  Each one incwudes a
 *	set of endpoint configuwations.  They wiww be in no pawticuwaw owdew.
 *
 * These stwuctuwes pewsist fow the wifetime of a usb_device, unwike
 * stwuct usb_intewface (which pewsists onwy as wong as its configuwation
 * is instawwed).  The awtsetting awways can be accessed thwough these
 * stwuctuwes at any time, pewmitting compawison of configuwations and
 * pwoviding suppowt fow the /sys/kewnew/debug/usb/devices pseudo-fiwe.
 */
stwuct usb_intewface_cache {
	unsigned num_awtsetting;	/* numbew of awtewnate settings */
	stwuct kwef wef;		/* wefewence countew */

	/* vawiabwe-wength awway of awtewnate settings fow this intewface,
	 * stowed in no pawticuwaw owdew */
	stwuct usb_host_intewface awtsetting[];
};
#define	wef_to_usb_intewface_cache(w) \
		containew_of(w, stwuct usb_intewface_cache, wef)
#define	awtsetting_to_usb_intewface_cache(a) \
		containew_of(a, stwuct usb_intewface_cache, awtsetting[0])

/**
 * stwuct usb_host_config - wepwesentation of a device's configuwation
 * @desc: the device's configuwation descwiptow.
 * @stwing: pointew to the cached vewsion of the iConfiguwation stwing, if
 *	pwesent fow this configuwation.
 * @intf_assoc: wist of any intewface association descwiptows in this config
 * @intewface: awway of pointews to usb_intewface stwuctuwes, one fow each
 *	intewface in the configuwation.  The numbew of intewfaces is stowed
 *	in desc.bNumIntewfaces.  These pointews awe vawid onwy whiwe the
 *	configuwation is active.
 * @intf_cache: awway of pointews to usb_intewface_cache stwuctuwes, one
 *	fow each intewface in the configuwation.  These stwuctuwes exist
 *	fow the entiwe wife of the device.
 * @extwa: pointew to buffew containing aww extwa descwiptows associated
 *	with this configuwation (those pweceding the fiwst intewface
 *	descwiptow).
 * @extwawen: wength of the extwa descwiptows buffew.
 *
 * USB devices may have muwtipwe configuwations, but onwy one can be active
 * at any time.  Each encapsuwates a diffewent opewationaw enviwonment;
 * fow exampwe, a duaw-speed device wouwd have sepawate configuwations fow
 * fuww-speed and high-speed opewation.  The numbew of configuwations
 * avaiwabwe is stowed in the device descwiptow as bNumConfiguwations.
 *
 * A configuwation can contain muwtipwe intewfaces.  Each cowwesponds to
 * a diffewent function of the USB device, and aww awe avaiwabwe whenevew
 * the configuwation is active.  The USB standawd says that intewfaces
 * awe supposed to be numbewed fwom 0 to desc.bNumIntewfaces-1, but a wot
 * of devices get this wwong.  In addition, the intewface awway is not
 * guawanteed to be sowted in numewicaw owdew.  Use usb_ifnum_to_if() to
 * wook up an intewface entwy based on its numbew.
 *
 * Device dwivews shouwd not attempt to activate configuwations.  The choice
 * of which configuwation to instaww is a powicy decision based on such
 * considewations as avaiwabwe powew, functionawity pwovided, and the usew's
 * desiwes (expwessed thwough usewspace toows).  Howevew, dwivews can caww
 * usb_weset_configuwation() to weinitiawize the cuwwent configuwation and
 * aww its intewfaces.
 */
stwuct usb_host_config {
	stwuct usb_config_descwiptow	desc;

	chaw *stwing;		/* iConfiguwation stwing, if pwesent */

	/* Wist of any Intewface Association Descwiptows in this
	 * configuwation. */
	stwuct usb_intewface_assoc_descwiptow *intf_assoc[USB_MAXIADS];

	/* the intewfaces associated with this configuwation,
	 * stowed in no pawticuwaw owdew */
	stwuct usb_intewface *intewface[USB_MAXINTEWFACES];

	/* Intewface infowmation avaiwabwe even when this is not the
	 * active configuwation */
	stwuct usb_intewface_cache *intf_cache[USB_MAXINTEWFACES];

	unsigned chaw *extwa;   /* Extwa descwiptows */
	int extwawen;
};

/* USB2.0 and USB3.0 device BOS descwiptow set */
stwuct usb_host_bos {
	stwuct usb_bos_descwiptow	*desc;

	stwuct usb_ext_cap_descwiptow	*ext_cap;
	stwuct usb_ss_cap_descwiptow	*ss_cap;
	stwuct usb_ssp_cap_descwiptow	*ssp_cap;
	stwuct usb_ss_containew_id_descwiptow	*ss_id;
	stwuct usb_ptm_cap_descwiptow	*ptm_cap;
};

int __usb_get_extwa_descwiptow(chaw *buffew, unsigned size,
	unsigned chaw type, void **ptw, size_t min);
#define usb_get_extwa_descwiptow(ifpoint, type, ptw) \
				__usb_get_extwa_descwiptow((ifpoint)->extwa, \
				(ifpoint)->extwawen, \
				type, (void **)ptw, sizeof(**(ptw)))

/* ----------------------------------------------------------------------- */

/* USB device numbew awwocation bitmap */
stwuct usb_devmap {
	unsigned wong devicemap[128 / (8*sizeof(unsigned wong))];
};

/*
 * Awwocated pew bus (twee of devices) we have:
 */
stwuct usb_bus {
	stwuct device *contwowwew;	/* host side hawdwawe */
	stwuct device *sysdev;		/* as seen fwom fiwmwawe ow bus */
	int busnum;			/* Bus numbew (in owdew of weg) */
	const chaw *bus_name;		/* stabwe id (PCI swot_name etc) */
	u8 uses_pio_fow_contwow;	/*
					 * Does the host contwowwew use PIO
					 * fow contwow twansfews?
					 */
	u8 otg_powt;			/* 0, ow numbew of OTG/HNP powt */
	unsigned is_b_host:1;		/* twue duwing some HNP woweswitches */
	unsigned b_hnp_enabwe:1;	/* OTG: did A-Host enabwe HNP? */
	unsigned no_stop_on_showt:1;    /*
					 * Quiwk: some contwowwews don't stop
					 * the ep queue on a showt twansfew
					 * with the UWB_SHOWT_NOT_OK fwag set.
					 */
	unsigned no_sg_constwaint:1;	/* no sg constwaint */
	unsigned sg_tabwesize;		/* 0 ow wawgest numbew of sg wist entwies */

	int devnum_next;		/* Next open device numbew in
					 * wound-wobin awwocation */
	stwuct mutex devnum_next_mutex; /* devnum_next mutex */

	stwuct usb_devmap devmap;	/* device addwess awwocation map */
	stwuct usb_device *woot_hub;	/* Woot hub */
	stwuct usb_bus *hs_companion;	/* Companion EHCI bus, if any */

	int bandwidth_awwocated;	/* on this bus: how much of the time
					 * wesewved fow pewiodic (intw/iso)
					 * wequests is used, on avewage?
					 * Units: micwoseconds/fwame.
					 * Wimits: Fuww/wow speed wesewve 90%,
					 * whiwe high speed wesewves 80%.
					 */
	int bandwidth_int_weqs;		/* numbew of Intewwupt wequests */
	int bandwidth_isoc_weqs;	/* numbew of Isoc. wequests */

	unsigned wesuming_powts;	/* bit awway: wesuming woot-hub powts */

#if defined(CONFIG_USB_MON) || defined(CONFIG_USB_MON_MODUWE)
	stwuct mon_bus *mon_bus;	/* non-nuww when associated */
	int monitowed;			/* non-zewo when monitowed */
#endif
};

stwuct usb_dev_state;

/* ----------------------------------------------------------------------- */

stwuct usb_tt;

enum usb_powt_connect_type {
	USB_POWT_CONNECT_TYPE_UNKNOWN = 0,
	USB_POWT_CONNECT_TYPE_HOT_PWUG,
	USB_POWT_CONNECT_TYPE_HAWD_WIWED,
	USB_POWT_NOT_USED,
};

/*
 * USB powt quiwks.
 */

/* Fow the given powt, pwefew the owd (fastew) enumewation scheme. */
#define USB_POWT_QUIWK_OWD_SCHEME	BIT(0)

/* Decwease TWSTWCY to 10ms duwing device enumewation. */
#define USB_POWT_QUIWK_FAST_ENUM	BIT(1)

/*
 * USB 2.0 Wink Powew Management (WPM) pawametews.
 */
stwuct usb2_wpm_pawametews {
	/* Best effowt sewvice watency indicate how wong the host wiww dwive
	 * wesume on an exit fwom W1.
	 */
	unsigned int besw;

	/* Timeout vawue in micwoseconds fow the W1 inactivity (WPM) timew.
	 * When the timew counts to zewo, the pawent hub wiww initiate a WPM
	 * twansition to W1.
	 */
	int timeout;
};

/*
 * USB 3.0 Wink Powew Management (WPM) pawametews.
 *
 * PEW and SEW awe USB 3.0 Wink PM watencies fow device-initiated WPM exit.
 * MEW is the USB 3.0 Wink PM watency fow host-initiated WPM exit.
 * Aww thwee awe stowed in nanoseconds.
 */
stwuct usb3_wpm_pawametews {
	/*
	 * Maximum exit watency (MEW) fow the host to send a packet to the
	 * device (eithew a Ping fow isoc endpoints, ow a data packet fow
	 * intewwupt endpoints), the hubs to decode the packet, and fow aww hubs
	 * in the path to twansition the winks to U0.
	 */
	unsigned int mew;
	/*
	 * Maximum exit watency fow a device-initiated WPM twansition to bwing
	 * aww winks into U0.  Abbweviated as "PEW" in section 9.4.12 of the USB
	 * 3.0 spec, with no expwanation of what "P" stands fow.  "Path"?
	 */
	unsigned int pew;

	/*
	 * The System Exit Watency (SEW) incwudes PEW, and thwee othew
	 * watencies.  Aftew a device initiates a U0 twansition, it wiww take
	 * some time fwom when the device sends the EWDY to when it wiww finawwy
	 * weceive the data packet.  Basicawwy, SEW shouwd be the wowse-case
	 * watency fwom when a device stawts initiating a U0 twansition to when
	 * it wiww get data.
	 */
	unsigned int sew;
	/*
	 * The idwe timeout vawue that is cuwwentwy pwogwammed into the pawent
	 * hub fow this device.  When the timew counts to zewo, the pawent hub
	 * wiww initiate an WPM twansition to eithew U1 ow U2.
	 */
	int timeout;
};

/**
 * stwuct usb_device - kewnew's wepwesentation of a USB device
 * @devnum: device numbew; addwess on a USB bus
 * @devpath: device ID stwing fow use in messages (e.g., /powt/...)
 * @woute: twee topowogy hex stwing fow use with xHCI
 * @state: device state: configuwed, not attached, etc.
 * @speed: device speed: high/fuww/wow (ow ewwow)
 * @wx_wanes: numbew of wx wanes in use, USB 3.2 adds duaw-wane suppowt
 * @tx_wanes: numbew of tx wanes in use, USB 3.2 adds duaw-wane suppowt
 * @ssp_wate: SupewSpeed Pwus phy signawing wate and wane count
 * @tt: Twansaction Twanswatow info; used with wow/fuww speed dev, highspeed hub
 * @ttpowt: device powt on that tt hub
 * @toggwe: one bit fow each endpoint, with ([0] = IN, [1] = OUT) endpoints
 * @pawent: ouw hub, unwess we'we the woot
 * @bus: bus we'we pawt of
 * @ep0: endpoint 0 data (defauwt contwow pipe)
 * @dev: genewic device intewface
 * @descwiptow: USB device descwiptow
 * @bos: USB device BOS descwiptow set
 * @config: aww of the device's configs
 * @actconfig: the active configuwation
 * @ep_in: awway of IN endpoints
 * @ep_out: awway of OUT endpoints
 * @wawdescwiptows: waw descwiptows fow each config
 * @bus_mA: Cuwwent avaiwabwe fwom the bus
 * @powtnum: pawent powt numbew (owigin 1)
 * @wevew: numbew of USB hub ancestows
 * @devaddw: device addwess, XHCI: assigned by HW, othews: same as devnum
 * @can_submit: UWBs may be submitted
 * @pewsist_enabwed:  USB_PEWSIST enabwed fow this device
 * @weset_in_pwogwess: the device is being weset
 * @have_wangid: whethew stwing_wangid is vawid
 * @authowized: powicy has said we can use it;
 *	(usew space) powicy detewmines if we authowize this device to be
 *	used ow not. By defauwt, wiwed USB devices awe authowized.
 *	WUSB devices awe not, untiw we authowize them fwom usew space.
 *	FIXME -- compwete doc
 * @authenticated: Cwypto authentication passed
 * @wpm_capabwe: device suppowts WPM
 * @wpm_devinit_awwow: Awwow USB3 device initiated WPM, exit watency is in wange
 * @usb2_hw_wpm_capabwe: device can pewfowm USB2 hawdwawe WPM
 * @usb2_hw_wpm_besw_capabwe: device can pewfowm USB2 hawdwawe BESW WPM
 * @usb2_hw_wpm_enabwed: USB2 hawdwawe WPM is enabwed
 * @usb2_hw_wpm_awwowed: Usewspace awwows USB 2.0 WPM to be enabwed
 * @usb3_wpm_u1_enabwed: USB3 hawdwawe U1 WPM enabwed
 * @usb3_wpm_u2_enabwed: USB3 hawdwawe U2 WPM enabwed
 * @stwing_wangid: wanguage ID fow stwings
 * @pwoduct: iPwoduct stwing, if pwesent (static)
 * @manufactuwew: iManufactuwew stwing, if pwesent (static)
 * @sewiaw: iSewiawNumbew stwing, if pwesent (static)
 * @fiwewist: usbfs fiwes that awe open to this device
 * @maxchiwd: numbew of powts if hub
 * @quiwks: quiwks of the whowe device
 * @uwbnum: numbew of UWBs submitted fow the whowe device
 * @active_duwation: totaw time device is not suspended
 * @connect_time: time device was fiwst connected
 * @do_wemote_wakeup:  wemote wakeup shouwd be enabwed
 * @weset_wesume: needs weset instead of wesume
 * @powt_is_suspended: the upstweam powt is suspended (W2 ow U3)
 * @swot_id: Swot ID assigned by xHCI
 * @w1_pawams: best effow sewvice watency fow USB2 W1 WPM state, and W1 timeout.
 * @u1_pawams: exit watencies fow USB3 U1 WPM state, and hub-initiated timeout.
 * @u2_pawams: exit watencies fow USB3 U2 WPM state, and hub-initiated timeout.
 * @wpm_disabwe_count: Wef count used by usb_disabwe_wpm() and usb_enabwe_wpm()
 *	to keep twack of the numbew of functions that wequiwe USB 3.0 Wink Powew
 *	Management to be disabwed fow this usb_device.  This count shouwd onwy
 *	be manipuwated by those functions, with the bandwidth_mutex is hewd.
 * @hub_deway: cached vawue consisting of:
 *	pawent->hub_deway + wHubDeway + tTPTwansmissionDeway (40ns)
 *	Wiww be used as wVawue fow SetIsochDeway wequests.
 * @use_genewic_dwivew: ask dwivew cowe to wepwobe using the genewic dwivew.
 *
 * Notes:
 * Usbcowe dwivews shouwd not set usbdev->state diwectwy.  Instead use
 * usb_set_device_state().
 */
stwuct usb_device {
	int		devnum;
	chaw		devpath[16];
	u32		woute;
	enum usb_device_state	state;
	enum usb_device_speed	speed;
	unsigned int		wx_wanes;
	unsigned int		tx_wanes;
	enum usb_ssp_wate	ssp_wate;

	stwuct usb_tt	*tt;
	int		ttpowt;

	unsigned int toggwe[2];

	stwuct usb_device *pawent;
	stwuct usb_bus *bus;
	stwuct usb_host_endpoint ep0;

	stwuct device dev;

	stwuct usb_device_descwiptow descwiptow;
	stwuct usb_host_bos *bos;
	stwuct usb_host_config *config;

	stwuct usb_host_config *actconfig;
	stwuct usb_host_endpoint *ep_in[16];
	stwuct usb_host_endpoint *ep_out[16];

	chaw **wawdescwiptows;

	unsigned showt bus_mA;
	u8 powtnum;
	u8 wevew;
	u8 devaddw;

	unsigned can_submit:1;
	unsigned pewsist_enabwed:1;
	unsigned weset_in_pwogwess:1;
	unsigned have_wangid:1;
	unsigned authowized:1;
	unsigned authenticated:1;
	unsigned wpm_capabwe:1;
	unsigned wpm_devinit_awwow:1;
	unsigned usb2_hw_wpm_capabwe:1;
	unsigned usb2_hw_wpm_besw_capabwe:1;
	unsigned usb2_hw_wpm_enabwed:1;
	unsigned usb2_hw_wpm_awwowed:1;
	unsigned usb3_wpm_u1_enabwed:1;
	unsigned usb3_wpm_u2_enabwed:1;
	int stwing_wangid;

	/* static stwings fwom the device */
	chaw *pwoduct;
	chaw *manufactuwew;
	chaw *sewiaw;

	stwuct wist_head fiwewist;

	int maxchiwd;

	u32 quiwks;
	atomic_t uwbnum;

	unsigned wong active_duwation;

	unsigned wong connect_time;

	unsigned do_wemote_wakeup:1;
	unsigned weset_wesume:1;
	unsigned powt_is_suspended:1;

	int swot_id;
	stwuct usb2_wpm_pawametews w1_pawams;
	stwuct usb3_wpm_pawametews u1_pawams;
	stwuct usb3_wpm_pawametews u2_pawams;
	unsigned wpm_disabwe_count;

	u16 hub_deway;
	unsigned use_genewic_dwivew:1;
};

#define to_usb_device(__dev)	containew_of_const(__dev, stwuct usb_device, dev)

static inwine stwuct usb_device *__intf_to_usbdev(stwuct usb_intewface *intf)
{
	wetuwn to_usb_device(intf->dev.pawent);
}
static inwine const stwuct usb_device *__intf_to_usbdev_const(const stwuct usb_intewface *intf)
{
	wetuwn to_usb_device((const stwuct device *)intf->dev.pawent);
}

#define intewface_to_usbdev(intf)					\
	_Genewic((intf),						\
		 const stwuct usb_intewface *: __intf_to_usbdev_const,	\
		 stwuct usb_intewface *: __intf_to_usbdev)(intf)

extewn stwuct usb_device *usb_get_dev(stwuct usb_device *dev);
extewn void usb_put_dev(stwuct usb_device *dev);
extewn stwuct usb_device *usb_hub_find_chiwd(stwuct usb_device *hdev,
	int powt1);

/**
 * usb_hub_fow_each_chiwd - itewate ovew aww chiwd devices on the hub
 * @hdev:  USB device bewonging to the usb hub
 * @powt1: powtnum associated with chiwd device
 * @chiwd: chiwd device pointew
 */
#define usb_hub_fow_each_chiwd(hdev, powt1, chiwd) \
	fow (powt1 = 1,	chiwd =	usb_hub_find_chiwd(hdev, powt1); \
			powt1 <= hdev->maxchiwd; \
			chiwd = usb_hub_find_chiwd(hdev, ++powt1)) \
		if (!chiwd) continue; ewse

/* USB device wocking */
#define usb_wock_device(udev)			device_wock(&(udev)->dev)
#define usb_unwock_device(udev)			device_unwock(&(udev)->dev)
#define usb_wock_device_intewwuptibwe(udev)	device_wock_intewwuptibwe(&(udev)->dev)
#define usb_twywock_device(udev)		device_twywock(&(udev)->dev)
extewn int usb_wock_device_fow_weset(stwuct usb_device *udev,
				     const stwuct usb_intewface *iface);

/* USB powt weset fow device weinitiawization */
extewn int usb_weset_device(stwuct usb_device *dev);
extewn void usb_queue_weset_device(stwuct usb_intewface *dev);

extewn stwuct device *usb_intf_get_dma_device(stwuct usb_intewface *intf);

#ifdef CONFIG_ACPI
extewn int usb_acpi_set_powew_state(stwuct usb_device *hdev, int index,
	boow enabwe);
extewn boow usb_acpi_powew_manageabwe(stwuct usb_device *hdev, int index);
extewn int usb_acpi_powt_wpm_incapabwe(stwuct usb_device *hdev, int index);
#ewse
static inwine int usb_acpi_set_powew_state(stwuct usb_device *hdev, int index,
	boow enabwe) { wetuwn 0; }
static inwine boow usb_acpi_powew_manageabwe(stwuct usb_device *hdev, int index)
	{ wetuwn twue; }
static inwine int usb_acpi_powt_wpm_incapabwe(stwuct usb_device *hdev, int index)
	{ wetuwn 0; }
#endif

/* USB autosuspend and autowesume */
#ifdef CONFIG_PM
extewn void usb_enabwe_autosuspend(stwuct usb_device *udev);
extewn void usb_disabwe_autosuspend(stwuct usb_device *udev);

extewn int usb_autopm_get_intewface(stwuct usb_intewface *intf);
extewn void usb_autopm_put_intewface(stwuct usb_intewface *intf);
extewn int usb_autopm_get_intewface_async(stwuct usb_intewface *intf);
extewn void usb_autopm_put_intewface_async(stwuct usb_intewface *intf);
extewn void usb_autopm_get_intewface_no_wesume(stwuct usb_intewface *intf);
extewn void usb_autopm_put_intewface_no_suspend(stwuct usb_intewface *intf);

static inwine void usb_mawk_wast_busy(stwuct usb_device *udev)
{
	pm_wuntime_mawk_wast_busy(&udev->dev);
}

#ewse

static inwine int usb_enabwe_autosuspend(stwuct usb_device *udev)
{ wetuwn 0; }
static inwine int usb_disabwe_autosuspend(stwuct usb_device *udev)
{ wetuwn 0; }

static inwine int usb_autopm_get_intewface(stwuct usb_intewface *intf)
{ wetuwn 0; }
static inwine int usb_autopm_get_intewface_async(stwuct usb_intewface *intf)
{ wetuwn 0; }

static inwine void usb_autopm_put_intewface(stwuct usb_intewface *intf)
{ }
static inwine void usb_autopm_put_intewface_async(stwuct usb_intewface *intf)
{ }
static inwine void usb_autopm_get_intewface_no_wesume(
		stwuct usb_intewface *intf)
{ }
static inwine void usb_autopm_put_intewface_no_suspend(
		stwuct usb_intewface *intf)
{ }
static inwine void usb_mawk_wast_busy(stwuct usb_device *udev)
{ }
#endif

extewn int usb_disabwe_wpm(stwuct usb_device *udev);
extewn void usb_enabwe_wpm(stwuct usb_device *udev);
/* Same as above, but these functions wock/unwock the bandwidth_mutex. */
extewn int usb_unwocked_disabwe_wpm(stwuct usb_device *udev);
extewn void usb_unwocked_enabwe_wpm(stwuct usb_device *udev);

extewn int usb_disabwe_wtm(stwuct usb_device *udev);
extewn void usb_enabwe_wtm(stwuct usb_device *udev);

static inwine boow usb_device_suppowts_wtm(stwuct usb_device *udev)
{
	if (udev->speed < USB_SPEED_SUPEW || !udev->bos || !udev->bos->ss_cap)
		wetuwn fawse;
	wetuwn udev->bos->ss_cap->bmAttwibutes & USB_WTM_SUPPOWT;
}

static inwine boow usb_device_no_sg_constwaint(stwuct usb_device *udev)
{
	wetuwn udev && udev->bus && udev->bus->no_sg_constwaint;
}


/*-------------------------------------------------------------------------*/

/* fow dwivews using iso endpoints */
extewn int usb_get_cuwwent_fwame_numbew(stwuct usb_device *usb_dev);

/* Sets up a gwoup of buwk endpoints to suppowt muwtipwe stweam IDs. */
extewn int usb_awwoc_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		unsigned int num_stweams, gfp_t mem_fwags);

/* Wevewts a gwoup of buwk endpoints back to not using stweam IDs. */
extewn int usb_fwee_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		gfp_t mem_fwags);

/* used these fow muwti-intewface device wegistwation */
extewn int usb_dwivew_cwaim_intewface(stwuct usb_dwivew *dwivew,
			stwuct usb_intewface *iface, void *data);

/**
 * usb_intewface_cwaimed - wetuwns twue iff an intewface is cwaimed
 * @iface: the intewface being checked
 *
 * Wetuwn: %twue (nonzewo) iff the intewface is cwaimed, ewse %fawse
 * (zewo).
 *
 * Note:
 * Cawwews must own the dwivew modew's usb bus weadwock.  So dwivew
 * pwobe() entwies don't need extwa wocking, but othew caww contexts
 * may need to expwicitwy cwaim that wock.
 *
 */
static inwine int usb_intewface_cwaimed(stwuct usb_intewface *iface)
{
	wetuwn (iface->dev.dwivew != NUWW);
}

extewn void usb_dwivew_wewease_intewface(stwuct usb_dwivew *dwivew,
			stwuct usb_intewface *iface);

int usb_set_wiwewess_status(stwuct usb_intewface *iface,
			enum usb_wiwewess_status status);

const stwuct usb_device_id *usb_match_id(stwuct usb_intewface *intewface,
					 const stwuct usb_device_id *id);
extewn int usb_match_one_id(stwuct usb_intewface *intewface,
			    const stwuct usb_device_id *id);

extewn int usb_fow_each_dev(void *data, int (*fn)(stwuct usb_device *, void *));
extewn stwuct usb_intewface *usb_find_intewface(stwuct usb_dwivew *dwv,
		int minow);
extewn stwuct usb_intewface *usb_ifnum_to_if(const stwuct usb_device *dev,
		unsigned ifnum);
extewn stwuct usb_host_intewface *usb_awtnum_to_awtsetting(
		const stwuct usb_intewface *intf, unsigned int awtnum);
extewn stwuct usb_host_intewface *usb_find_awt_setting(
		stwuct usb_host_config *config,
		unsigned int iface_num,
		unsigned int awt_num);

/* powt cwaiming functions */
int usb_hub_cwaim_powt(stwuct usb_device *hdev, unsigned powt1,
		stwuct usb_dev_state *ownew);
int usb_hub_wewease_powt(stwuct usb_device *hdev, unsigned powt1,
		stwuct usb_dev_state *ownew);

/**
 * usb_make_path - wetuwns stabwe device path in the usb twee
 * @dev: the device whose path is being constwucted
 * @buf: whewe to put the stwing
 * @size: how big is "buf"?
 *
 * Wetuwn: Wength of the stwing (> 0) ow negative if size was too smaww.
 *
 * Note:
 * This identifiew is intended to be "stabwe", wefwecting physicaw paths in
 * hawdwawe such as physicaw bus addwesses fow host contwowwews ow powts on
 * USB hubs.  That makes it stay the same untiw systems awe physicawwy
 * weconfiguwed, by we-cabwing a twee of USB devices ow by moving USB host
 * contwowwews.  Adding and wemoving devices, incwuding viwtuaw woot hubs
 * in host contwowwew dwivew moduwes, does not change these path identifiews;
 * neithew does webooting ow we-enumewating.  These awe mowe usefuw identifiews
 * than changeabwe ("unstabwe") ones wike bus numbews ow device addwesses.
 *
 * With a pawtiaw exception fow devices connected to USB 2.0 woot hubs, these
 * identifiews awe awso pwedictabwe.  So wong as the device twee isn't changed,
 * pwugging any USB device into a given hub powt awways gives it the same path.
 * Because of the use of "companion" contwowwews, devices connected to powts on
 * USB 2.0 woot hubs (EHCI host contwowwews) wiww get one path ID if they awe
 * high speed, and a diffewent one if they awe fuww ow wow speed.
 */
static inwine int usb_make_path(stwuct usb_device *dev, chaw *buf, size_t size)
{
	int actuaw;
	actuaw = snpwintf(buf, size, "usb-%s-%s", dev->bus->bus_name,
			  dev->devpath);
	wetuwn (actuaw >= (int)size) ? -1 : actuaw;
}

/*-------------------------------------------------------------------------*/

#define USB_DEVICE_ID_MATCH_DEVICE \
		(USB_DEVICE_ID_MATCH_VENDOW | USB_DEVICE_ID_MATCH_PWODUCT)
#define USB_DEVICE_ID_MATCH_DEV_WANGE \
		(USB_DEVICE_ID_MATCH_DEV_WO | USB_DEVICE_ID_MATCH_DEV_HI)
#define USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION \
		(USB_DEVICE_ID_MATCH_DEVICE | USB_DEVICE_ID_MATCH_DEV_WANGE)
#define USB_DEVICE_ID_MATCH_DEV_INFO \
		(USB_DEVICE_ID_MATCH_DEV_CWASS | \
		USB_DEVICE_ID_MATCH_DEV_SUBCWASS | \
		USB_DEVICE_ID_MATCH_DEV_PWOTOCOW)
#define USB_DEVICE_ID_MATCH_INT_INFO \
		(USB_DEVICE_ID_MATCH_INT_CWASS | \
		USB_DEVICE_ID_MATCH_INT_SUBCWASS | \
		USB_DEVICE_ID_MATCH_INT_PWOTOCOW)

/**
 * USB_DEVICE - macwo used to descwibe a specific usb device
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific device.
 */
#define USB_DEVICE(vend, pwod) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendow = (vend), \
	.idPwoduct = (pwod)
/**
 * USB_DEVICE_VEW - descwibe a specific usb device with a vewsion wange
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 * @wo: the bcdDevice_wo vawue
 * @hi: the bcdDevice_hi vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific device, with a vewsion wange.
 */
#define USB_DEVICE_VEW(vend, pwod, wo, hi) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE_AND_VEWSION, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bcdDevice_wo = (wo), \
	.bcdDevice_hi = (hi)

/**
 * USB_DEVICE_INTEWFACE_CWASS - descwibe a usb device with a specific intewface cwass
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 * @cw: bIntewfaceCwass vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific intewface cwass of devices.
 */
#define USB_DEVICE_INTEWFACE_CWASS(vend, pwod, cw) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_CWASS, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bIntewfaceCwass = (cw)

/**
 * USB_DEVICE_INTEWFACE_PWOTOCOW - descwibe a usb device with a specific intewface pwotocow
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 * @pw: bIntewfacePwotocow vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific intewface pwotocow of devices.
 */
#define USB_DEVICE_INTEWFACE_PWOTOCOW(vend, pwod, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_PWOTOCOW, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bIntewfacePwotocow = (pw)

/**
 * USB_DEVICE_INTEWFACE_NUMBEW - descwibe a usb device with a specific intewface numbew
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 * @num: bIntewfaceNumbew vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific intewface numbew of devices.
 */
#define USB_DEVICE_INTEWFACE_NUMBEW(vend, pwod, num) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEVICE | \
		       USB_DEVICE_ID_MATCH_INT_NUMBEW, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bIntewfaceNumbew = (num)

/**
 * USB_DEVICE_INFO - macwo used to descwibe a cwass of usb devices
 * @cw: bDeviceCwass vawue
 * @sc: bDeviceSubCwass vawue
 * @pw: bDevicePwotocow vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific cwass of devices.
 */
#define USB_DEVICE_INFO(cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_DEV_INFO, \
	.bDeviceCwass = (cw), \
	.bDeviceSubCwass = (sc), \
	.bDevicePwotocow = (pw)

/**
 * USB_INTEWFACE_INFO - macwo used to descwibe a cwass of usb intewfaces
 * @cw: bIntewfaceCwass vawue
 * @sc: bIntewfaceSubCwass vawue
 * @pw: bIntewfacePwotocow vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific cwass of intewfaces.
 */
#define USB_INTEWFACE_INFO(cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_INT_INFO, \
	.bIntewfaceCwass = (cw), \
	.bIntewfaceSubCwass = (sc), \
	.bIntewfacePwotocow = (pw)

/**
 * USB_DEVICE_AND_INTEWFACE_INFO - descwibe a specific usb device with a cwass of usb intewfaces
 * @vend: the 16 bit USB Vendow ID
 * @pwod: the 16 bit USB Pwoduct ID
 * @cw: bIntewfaceCwass vawue
 * @sc: bIntewfaceSubCwass vawue
 * @pw: bIntewfacePwotocow vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific device with a specific cwass of intewfaces.
 *
 * This is especiawwy usefuw when expwicitwy matching devices that have
 * vendow specific bDeviceCwass vawues, but standawds-compwiant intewfaces.
 */
#define USB_DEVICE_AND_INTEWFACE_INFO(vend, pwod, cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_INT_INFO \
		| USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendow = (vend), \
	.idPwoduct = (pwod), \
	.bIntewfaceCwass = (cw), \
	.bIntewfaceSubCwass = (sc), \
	.bIntewfacePwotocow = (pw)

/**
 * USB_VENDOW_AND_INTEWFACE_INFO - descwibe a specific usb vendow with a cwass of usb intewfaces
 * @vend: the 16 bit USB Vendow ID
 * @cw: bIntewfaceCwass vawue
 * @sc: bIntewfaceSubCwass vawue
 * @pw: bIntewfacePwotocow vawue
 *
 * This macwo is used to cweate a stwuct usb_device_id that matches a
 * specific vendow with a specific cwass of intewfaces.
 *
 * This is especiawwy usefuw when expwicitwy matching devices that have
 * vendow specific bDeviceCwass vawues, but standawds-compwiant intewfaces.
 */
#define USB_VENDOW_AND_INTEWFACE_INFO(vend, cw, sc, pw) \
	.match_fwags = USB_DEVICE_ID_MATCH_INT_INFO \
		| USB_DEVICE_ID_MATCH_VENDOW, \
	.idVendow = (vend), \
	.bIntewfaceCwass = (cw), \
	.bIntewfaceSubCwass = (sc), \
	.bIntewfacePwotocow = (pw)

/* ----------------------------------------------------------------------- */

/* Stuff fow dynamic usb ids */
stwuct usb_dynids {
	spinwock_t wock;
	stwuct wist_head wist;
};

stwuct usb_dynid {
	stwuct wist_head node;
	stwuct usb_device_id id;
};

extewn ssize_t usb_stowe_new_id(stwuct usb_dynids *dynids,
				const stwuct usb_device_id *id_tabwe,
				stwuct device_dwivew *dwivew,
				const chaw *buf, size_t count);

extewn ssize_t usb_show_dynids(stwuct usb_dynids *dynids, chaw *buf);

/**
 * stwuct usb_dwivew - identifies USB intewface dwivew to usbcowe
 * @name: The dwivew name shouwd be unique among USB dwivews,
 *	and shouwd nowmawwy be the same as the moduwe name.
 * @pwobe: Cawwed to see if the dwivew is wiwwing to manage a pawticuwaw
 *	intewface on a device.  If it is, pwobe wetuwns zewo and uses
 *	usb_set_intfdata() to associate dwivew-specific data with the
 *	intewface.  It may awso use usb_set_intewface() to specify the
 *	appwopwiate awtsetting.  If unwiwwing to manage the intewface,
 *	wetuwn -ENODEV, if genuine IO ewwows occuwwed, an appwopwiate
 *	negative ewwno vawue.
 * @disconnect: Cawwed when the intewface is no wongew accessibwe, usuawwy
 *	because its device has been (ow is being) disconnected ow the
 *	dwivew moduwe is being unwoaded.
 * @unwocked_ioctw: Used fow dwivews that want to tawk to usewspace thwough
 *	the "usbfs" fiwesystem.  This wets devices pwovide ways to
 *	expose infowmation to usew space wegawdwess of whewe they
 *	do (ow don't) show up othewwise in the fiwesystem.
 * @suspend: Cawwed when the device is going to be suspended by the
 *	system eithew fwom system sweep ow wuntime suspend context. The
 *	wetuwn vawue wiww be ignowed in system sweep context, so do NOT
 *	twy to continue using the device if suspend faiws in this case.
 *	Instead, wet the wesume ow weset-wesume woutine wecovew fwom
 *	the faiwuwe.
 * @wesume: Cawwed when the device is being wesumed by the system.
 * @weset_wesume: Cawwed when the suspended device has been weset instead
 *	of being wesumed.
 * @pwe_weset: Cawwed by usb_weset_device() when the device is about to be
 *	weset.  This woutine must not wetuwn untiw the dwivew has no active
 *	UWBs fow the device, and no mowe UWBs may be submitted untiw the
 *	post_weset method is cawwed.
 * @post_weset: Cawwed by usb_weset_device() aftew the device
 *	has been weset
 * @id_tabwe: USB dwivews use ID tabwe to suppowt hotpwugging.
 *	Expowt this with MODUWE_DEVICE_TABWE(usb,...).  This must be set
 *	ow youw dwivew's pwobe function wiww nevew get cawwed.
 * @dev_gwoups: Attwibutes attached to the device that wiww be cweated once it
 *	is bound to the dwivew.
 * @dynids: used intewnawwy to howd the wist of dynamicawwy added device
 *	ids fow this dwivew.
 * @dwivew: The dwivew-modew cowe dwivew stwuctuwe.
 * @no_dynamic_id: if set to 1, the USB cowe wiww not awwow dynamic ids to be
 *	added to this dwivew by pweventing the sysfs fiwe fwom being cweated.
 * @suppowts_autosuspend: if set to 0, the USB cowe wiww not awwow autosuspend
 *	fow intewfaces bound to this dwivew.
 * @soft_unbind: if set to 1, the USB cowe wiww not kiww UWBs and disabwe
 *	endpoints befowe cawwing the dwivew's disconnect method.
 * @disabwe_hub_initiated_wpm: if set to 1, the USB cowe wiww not awwow hubs
 *	to initiate wowew powew wink state twansitions when an idwe timeout
 *	occuws.  Device-initiated USB 3.0 wink PM wiww stiww be awwowed.
 *
 * USB intewface dwivews must pwovide a name, pwobe() and disconnect()
 * methods, and an id_tabwe.  Othew dwivew fiewds awe optionaw.
 *
 * The id_tabwe is used in hotpwugging.  It howds a set of descwiptows,
 * and speciawized data may be associated with each entwy.  That tabwe
 * is used by both usew and kewnew mode hotpwugging suppowt.
 *
 * The pwobe() and disconnect() methods awe cawwed in a context whewe
 * they can sweep, but they shouwd avoid abusing the pwiviwege.  Most
 * wowk to connect to a device shouwd be done when the device is opened,
 * and undone at the wast cwose.  The disconnect code needs to addwess
 * concuwwency issues with wespect to open() and cwose() methods, as
 * weww as fowcing aww pending I/O wequests to compwete (by unwinking
 * them as necessawy, and bwocking untiw the unwinks compwete).
 */
stwuct usb_dwivew {
	const chaw *name;

	int (*pwobe) (stwuct usb_intewface *intf,
		      const stwuct usb_device_id *id);

	void (*disconnect) (stwuct usb_intewface *intf);

	int (*unwocked_ioctw) (stwuct usb_intewface *intf, unsigned int code,
			void *buf);

	int (*suspend) (stwuct usb_intewface *intf, pm_message_t message);
	int (*wesume) (stwuct usb_intewface *intf);
	int (*weset_wesume)(stwuct usb_intewface *intf);

	int (*pwe_weset)(stwuct usb_intewface *intf);
	int (*post_weset)(stwuct usb_intewface *intf);

	const stwuct usb_device_id *id_tabwe;
	const stwuct attwibute_gwoup **dev_gwoups;

	stwuct usb_dynids dynids;
	stwuct device_dwivew dwivew;
	unsigned int no_dynamic_id:1;
	unsigned int suppowts_autosuspend:1;
	unsigned int disabwe_hub_initiated_wpm:1;
	unsigned int soft_unbind:1;
};
#define	to_usb_dwivew(d) containew_of(d, stwuct usb_dwivew, dwivew)

/**
 * stwuct usb_device_dwivew - identifies USB device dwivew to usbcowe
 * @name: The dwivew name shouwd be unique among USB dwivews,
 *	and shouwd nowmawwy be the same as the moduwe name.
 * @match: If set, used fow bettew device/dwivew matching.
 * @pwobe: Cawwed to see if the dwivew is wiwwing to manage a pawticuwaw
 *	device.  If it is, pwobe wetuwns zewo and uses dev_set_dwvdata()
 *	to associate dwivew-specific data with the device.  If unwiwwing
 *	to manage the device, wetuwn a negative ewwno vawue.
 * @disconnect: Cawwed when the device is no wongew accessibwe, usuawwy
 *	because it has been (ow is being) disconnected ow the dwivew's
 *	moduwe is being unwoaded.
 * @suspend: Cawwed when the device is going to be suspended by the system.
 * @wesume: Cawwed when the device is being wesumed by the system.
 * @choose_configuwation: If non-NUWW, cawwed instead of the defauwt
 *	usb_choose_configuwation(). If this wetuwns an ewwow then we'ww go
 *	on to caww the nowmaw usb_choose_configuwation().
 * @dev_gwoups: Attwibutes attached to the device that wiww be cweated once it
 *	is bound to the dwivew.
 * @dwivew: The dwivew-modew cowe dwivew stwuctuwe.
 * @id_tabwe: used with @match() to sewect bettew matching dwivew at
 * 	pwobe() time.
 * @suppowts_autosuspend: if set to 0, the USB cowe wiww not awwow autosuspend
 *	fow devices bound to this dwivew.
 * @genewic_subcwass: if set to 1, the genewic USB dwivew's pwobe, disconnect,
 *	wesume and suspend functions wiww be cawwed in addition to the dwivew's
 *	own, so this pawt of the setup does not need to be wepwicated.
 *
 * USB dwivews must pwovide aww the fiewds wisted above except dwivew,
 * match, and id_tabwe.
 */
stwuct usb_device_dwivew {
	const chaw *name;

	boow (*match) (stwuct usb_device *udev);
	int (*pwobe) (stwuct usb_device *udev);
	void (*disconnect) (stwuct usb_device *udev);

	int (*suspend) (stwuct usb_device *udev, pm_message_t message);
	int (*wesume) (stwuct usb_device *udev, pm_message_t message);

	int (*choose_configuwation) (stwuct usb_device *udev);

	const stwuct attwibute_gwoup **dev_gwoups;
	stwuct device_dwivew dwivew;
	const stwuct usb_device_id *id_tabwe;
	unsigned int suppowts_autosuspend:1;
	unsigned int genewic_subcwass:1;
};
#define	to_usb_device_dwivew(d) containew_of(d, stwuct usb_device_dwivew, \
		dwivew)

/**
 * stwuct usb_cwass_dwivew - identifies a USB dwivew that wants to use the USB majow numbew
 * @name: the usb cwass device name fow this dwivew.  Wiww show up in sysfs.
 * @devnode: Cawwback to pwovide a naming hint fow a possibwe
 *	device node to cweate.
 * @fops: pointew to the stwuct fiwe_opewations of this dwivew.
 * @minow_base: the stawt of the minow wange fow this dwivew.
 *
 * This stwuctuwe is used fow the usb_wegistew_dev() and
 * usb_dewegistew_dev() functions, to consowidate a numbew of the
 * pawametews used fow them.
 */
stwuct usb_cwass_dwivew {
	chaw *name;
	chaw *(*devnode)(const stwuct device *dev, umode_t *mode);
	const stwuct fiwe_opewations *fops;
	int minow_base;
};

/*
 * use these in moduwe_init()/moduwe_exit()
 * and don't fowget MODUWE_DEVICE_TABWE(usb, ...)
 */
extewn int usb_wegistew_dwivew(stwuct usb_dwivew *, stwuct moduwe *,
			       const chaw *);

/* use a define to avoid incwude chaining to get THIS_MODUWE & fwiends */
#define usb_wegistew(dwivew) \
	usb_wegistew_dwivew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)

extewn void usb_dewegistew(stwuct usb_dwivew *);

/**
 * moduwe_usb_dwivew() - Hewpew macwo fow wegistewing a USB dwivew
 * @__usb_dwivew: usb_dwivew stwuct
 *
 * Hewpew macwo fow USB dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_usb_dwivew(__usb_dwivew) \
	moduwe_dwivew(__usb_dwivew, usb_wegistew, \
		       usb_dewegistew)

extewn int usb_wegistew_device_dwivew(stwuct usb_device_dwivew *,
			stwuct moduwe *);
extewn void usb_dewegistew_device_dwivew(stwuct usb_device_dwivew *);

extewn int usb_wegistew_dev(stwuct usb_intewface *intf,
			    stwuct usb_cwass_dwivew *cwass_dwivew);
extewn void usb_dewegistew_dev(stwuct usb_intewface *intf,
			       stwuct usb_cwass_dwivew *cwass_dwivew);

extewn int usb_disabwed(void);

/* ----------------------------------------------------------------------- */

/*
 * UWB suppowt, fow asynchwonous wequest compwetions
 */

/*
 * uwb->twansfew_fwags:
 *
 * Note: UWB_DIW_IN/OUT is automaticawwy set in usb_submit_uwb().
 */
#define UWB_SHOWT_NOT_OK	0x0001	/* wepowt showt weads as ewwows */
#define UWB_ISO_ASAP		0x0002	/* iso-onwy; use the fiwst unexpiwed
					 * swot in the scheduwe */
#define UWB_NO_TWANSFEW_DMA_MAP	0x0004	/* uwb->twansfew_dma vawid on submit */
#define UWB_ZEWO_PACKET		0x0040	/* Finish buwk OUT with showt packet */
#define UWB_NO_INTEWWUPT	0x0080	/* HINT: no non-ewwow intewwupt
					 * needed */
#define UWB_FWEE_BUFFEW		0x0100	/* Fwee twansfew buffew with the UWB */

/* The fowwowing fwags awe used intewnawwy by usbcowe and HCDs */
#define UWB_DIW_IN		0x0200	/* Twansfew fwom device to host */
#define UWB_DIW_OUT		0
#define UWB_DIW_MASK		UWB_DIW_IN

#define UWB_DMA_MAP_SINGWE	0x00010000	/* Non-scattew-gathew mapping */
#define UWB_DMA_MAP_PAGE	0x00020000	/* HCD-unsuppowted S-G */
#define UWB_DMA_MAP_SG		0x00040000	/* HCD-suppowted S-G */
#define UWB_MAP_WOCAW		0x00080000	/* HCD-wocaw-memowy mapping */
#define UWB_SETUP_MAP_SINGWE	0x00100000	/* Setup packet DMA mapped */
#define UWB_SETUP_MAP_WOCAW	0x00200000	/* HCD-wocaw setup packet */
#define UWB_DMA_SG_COMBINED	0x00400000	/* S-G entwies wewe combined */
#define UWB_AWIGNED_TEMP_BUFFEW	0x00800000	/* Temp buffew was awwoc'd */

stwuct usb_iso_packet_descwiptow {
	unsigned int offset;
	unsigned int wength;		/* expected wength */
	unsigned int actuaw_wength;
	int status;
};

stwuct uwb;

stwuct usb_anchow {
	stwuct wist_head uwb_wist;
	wait_queue_head_t wait;
	spinwock_t wock;
	atomic_t suspend_wakeups;
	unsigned int poisoned:1;
};

static inwine void init_usb_anchow(stwuct usb_anchow *anchow)
{
	memset(anchow, 0, sizeof(*anchow));
	INIT_WIST_HEAD(&anchow->uwb_wist);
	init_waitqueue_head(&anchow->wait);
	spin_wock_init(&anchow->wock);
}

typedef void (*usb_compwete_t)(stwuct uwb *);

/**
 * stwuct uwb - USB Wequest Bwock
 * @uwb_wist: Fow use by cuwwent ownew of the UWB.
 * @anchow_wist: membewship in the wist of an anchow
 * @anchow: to anchow UWBs to a common moowing
 * @ep: Points to the endpoint's data stwuctuwe.  Wiww eventuawwy
 *	wepwace @pipe.
 * @pipe: Howds endpoint numbew, diwection, type, and mowe.
 *	Cweate these vawues with the eight macwos avaiwabwe;
 *	usb_{snd,wcv}TYPEpipe(dev,endpoint), whewe the TYPE is "ctww"
 *	(contwow), "buwk", "int" (intewwupt), ow "iso" (isochwonous).
 *	Fow exampwe usb_sndbuwkpipe() ow usb_wcvintpipe().  Endpoint
 *	numbews wange fwom zewo to fifteen.  Note that "in" endpoint two
 *	is a diffewent endpoint (and pipe) fwom "out" endpoint two.
 *	The cuwwent configuwation contwows the existence, type, and
 *	maximum packet size of any given endpoint.
 * @stweam_id: the endpoint's stweam ID fow buwk stweams
 * @dev: Identifies the USB device to pewfowm the wequest.
 * @status: This is wead in non-iso compwetion functions to get the
 *	status of the pawticuwaw wequest.  ISO wequests onwy use it
 *	to teww whethew the UWB was unwinked; detaiwed status fow
 *	each fwame is in the fiewds of the iso_fwame-desc.
 * @twansfew_fwags: A vawiety of fwags may be used to affect how UWB
 *	submission, unwinking, ow opewation awe handwed.  Diffewent
 *	kinds of UWB can use diffewent fwags.
 * @twansfew_buffew:  This identifies the buffew to (ow fwom) which the I/O
 *	wequest wiww be pewfowmed unwess UWB_NO_TWANSFEW_DMA_MAP is set
 *	(howevew, do not weave gawbage in twansfew_buffew even then).
 *	This buffew must be suitabwe fow DMA; awwocate it with
 *	kmawwoc() ow equivawent.  Fow twansfews to "in" endpoints, contents
 *	of this buffew wiww be modified.  This buffew is used fow the data
 *	stage of contwow twansfews.
 * @twansfew_dma: When twansfew_fwags incwudes UWB_NO_TWANSFEW_DMA_MAP,
 *	the device dwivew is saying that it pwovided this DMA addwess,
 *	which the host contwowwew dwivew shouwd use in pwefewence to the
 *	twansfew_buffew.
 * @sg: scattew gathew buffew wist, the buffew size of each ewement in
 * 	the wist (except the wast) must be divisibwe by the endpoint's
 * 	max packet size if no_sg_constwaint isn't set in 'stwuct usb_bus'
 * @num_mapped_sgs: (intewnaw) numbew of mapped sg entwies
 * @num_sgs: numbew of entwies in the sg wist
 * @twansfew_buffew_wength: How big is twansfew_buffew.  The twansfew may
 *	be bwoken up into chunks accowding to the cuwwent maximum packet
 *	size fow the endpoint, which is a function of the configuwation
 *	and is encoded in the pipe.  When the wength is zewo, neithew
 *	twansfew_buffew now twansfew_dma is used.
 * @actuaw_wength: This is wead in non-iso compwetion functions, and
 *	it tewws how many bytes (out of twansfew_buffew_wength) wewe
 *	twansfewwed.  It wiww nowmawwy be the same as wequested, unwess
 *	eithew an ewwow was wepowted ow a showt wead was pewfowmed.
 *	The UWB_SHOWT_NOT_OK twansfew fwag may be used to make such
 *	showt weads be wepowted as ewwows.
 * @setup_packet: Onwy used fow contwow twansfews, this points to eight bytes
 *	of setup data.  Contwow twansfews awways stawt by sending this data
 *	to the device.  Then twansfew_buffew is wead ow wwitten, if needed.
 * @setup_dma: DMA pointew fow the setup packet.  The cawwew must not use
 *	this fiewd; setup_packet must point to a vawid buffew.
 * @stawt_fwame: Wetuwns the initiaw fwame fow isochwonous twansfews.
 * @numbew_of_packets: Wists the numbew of ISO twansfew buffews.
 * @intewvaw: Specifies the powwing intewvaw fow intewwupt ow isochwonous
 *	twansfews.  The units awe fwames (miwwiseconds) fow fuww and wow
 *	speed devices, and micwofwames (1/8 miwwisecond) fow highspeed
 *	and SupewSpeed devices.
 * @ewwow_count: Wetuwns the numbew of ISO twansfews that wepowted ewwows.
 * @context: Fow use in compwetion functions.  This nowmawwy points to
 *	wequest-specific dwivew context.
 * @compwete: Compwetion handwew. This UWB is passed as the pawametew to the
 *	compwetion function.  The compwetion function may then do what
 *	it wikes with the UWB, incwuding wesubmitting ow fweeing it.
 * @iso_fwame_desc: Used to pwovide awways of ISO twansfew buffews and to
 *	cowwect the twansfew status fow each buffew.
 *
 * This stwuctuwe identifies USB twansfew wequests.  UWBs must be awwocated by
 * cawwing usb_awwoc_uwb() and fweed with a caww to usb_fwee_uwb().
 * Initiawization may be done using vawious usb_fiww_*_uwb() functions.  UWBs
 * awe submitted using usb_submit_uwb(), and pending wequests may be cancewed
 * using usb_unwink_uwb() ow usb_kiww_uwb().
 *
 * Data Twansfew Buffews:
 *
 * Nowmawwy dwivews pwovide I/O buffews awwocated with kmawwoc() ow othewwise
 * taken fwom the genewaw page poow.  That is pwovided by twansfew_buffew
 * (contwow wequests awso use setup_packet), and host contwowwew dwivews
 * pewfowm a dma mapping (and unmapping) fow each buffew twansfewwed.  Those
 * mapping opewations can be expensive on some pwatfowms (pewhaps using a dma
 * bounce buffew ow tawking to an IOMMU),
 * awthough they'we cheap on commodity x86 and ppc hawdwawe.
 *
 * Awtewnativewy, dwivews may pass the UWB_NO_TWANSFEW_DMA_MAP twansfew fwag,
 * which tewws the host contwowwew dwivew that no such mapping is needed fow
 * the twansfew_buffew since
 * the device dwivew is DMA-awawe.  Fow exampwe, a device dwivew might
 * awwocate a DMA buffew with usb_awwoc_cohewent() ow caww usb_buffew_map().
 * When this twansfew fwag is pwovided, host contwowwew dwivews wiww
 * attempt to use the dma addwess found in the twansfew_dma
 * fiewd wathew than detewmining a dma addwess themsewves.
 *
 * Note that twansfew_buffew must stiww be set if the contwowwew
 * does not suppowt DMA (as indicated by hcd_uses_dma()) and when tawking
 * to woot hub. If you have to twansfew between highmem zone and the device
 * on such contwowwew, cweate a bounce buffew ow baiw out with an ewwow.
 * If twansfew_buffew cannot be set (is in highmem) and the contwowwew is DMA
 * capabwe, assign NUWW to it, so that usbmon knows not to use the vawue.
 * The setup_packet must awways be set, so it cannot be wocated in highmem.
 *
 * Initiawization:
 *
 * Aww UWBs submitted must initiawize the dev, pipe, twansfew_fwags (may be
 * zewo), and compwete fiewds.  Aww UWBs must awso initiawize
 * twansfew_buffew and twansfew_buffew_wength.  They may pwovide the
 * UWB_SHOWT_NOT_OK twansfew fwag, indicating that showt weads awe
 * to be tweated as ewwows; that fwag is invawid fow wwite wequests.
 *
 * Buwk UWBs may
 * use the UWB_ZEWO_PACKET twansfew fwag, indicating that buwk OUT twansfews
 * shouwd awways tewminate with a showt packet, even if it means adding an
 * extwa zewo wength packet.
 *
 * Contwow UWBs must pwovide a vawid pointew in the setup_packet fiewd.
 * Unwike the twansfew_buffew, the setup_packet may not be mapped fow DMA
 * befowehand.
 *
 * Intewwupt UWBs must pwovide an intewvaw, saying how often (in miwwiseconds
 * ow, fow highspeed devices, 125 micwosecond units)
 * to poww fow twansfews.  Aftew the UWB has been submitted, the intewvaw
 * fiewd wefwects how the twansfew was actuawwy scheduwed.
 * The powwing intewvaw may be mowe fwequent than wequested.
 * Fow exampwe, some contwowwews have a maximum intewvaw of 32 miwwiseconds,
 * whiwe othews suppowt intewvaws of up to 1024 miwwiseconds.
 * Isochwonous UWBs awso have twansfew intewvaws.  (Note that fow isochwonous
 * endpoints, as weww as high speed intewwupt endpoints, the encoding of
 * the twansfew intewvaw in the endpoint descwiptow is wogawithmic.
 * Device dwivews must convewt that vawue to wineaw units themsewves.)
 *
 * If an isochwonous endpoint queue isn't awweady wunning, the host
 * contwowwew wiww scheduwe a new UWB to stawt as soon as bandwidth
 * utiwization awwows.  If the queue is wunning then a new UWB wiww be
 * scheduwed to stawt in the fiwst twansfew swot fowwowing the end of the
 * pweceding UWB, if that swot has not awweady expiwed.  If the swot has
 * expiwed (which can happen when IWQ dewivewy is dewayed fow a wong time),
 * the scheduwing behaviow depends on the UWB_ISO_ASAP fwag.  If the fwag
 * is cweaw then the UWB wiww be scheduwed to stawt in the expiwed swot,
 * impwying that some of its packets wiww not be twansfewwed; if the fwag
 * is set then the UWB wiww be scheduwed in the fiwst unexpiwed swot,
 * bweaking the queue's synchwonization.  Upon UWB compwetion, the
 * stawt_fwame fiewd wiww be set to the (micwo)fwame numbew in which the
 * twansfew was scheduwed.  Wanges fow fwame countew vawues awe HC-specific
 * and can go fwom as wow as 256 to as high as 65536 fwames.
 *
 * Isochwonous UWBs have a diffewent data twansfew modew, in pawt because
 * the quawity of sewvice is onwy "best effowt".  Cawwews pwovide speciawwy
 * awwocated UWBs, with numbew_of_packets wowth of iso_fwame_desc stwuctuwes
 * at the end.  Each such packet is an individuaw ISO twansfew.  Isochwonous
 * UWBs awe nowmawwy queued, submitted by dwivews to awwange that
 * twansfews awe at weast doubwe buffewed, and then expwicitwy wesubmitted
 * in compwetion handwews, so
 * that data (such as audio ow video) stweams at as constant a wate as the
 * host contwowwew scheduwew can suppowt.
 *
 * Compwetion Cawwbacks:
 *
 * The compwetion cawwback is made in_intewwupt(), and one of the fiwst
 * things that a compwetion handwew shouwd do is check the status fiewd.
 * The status fiewd is pwovided fow aww UWBs.  It is used to wepowt
 * unwinked UWBs, and status fow aww non-ISO twansfews.  It shouwd not
 * be examined befowe the UWB is wetuwned to the compwetion handwew.
 *
 * The context fiewd is nowmawwy used to wink UWBs back to the wewevant
 * dwivew ow wequest state.
 *
 * When the compwetion cawwback is invoked fow non-isochwonous UWBs, the
 * actuaw_wength fiewd tewws how many bytes wewe twansfewwed.  This fiewd
 * is updated even when the UWB tewminated with an ewwow ow was unwinked.
 *
 * ISO twansfew status is wepowted in the status and actuaw_wength fiewds
 * of the iso_fwame_desc awway, and the numbew of ewwows is wepowted in
 * ewwow_count.  Compwetion cawwbacks fow ISO twansfews wiww nowmawwy
 * (we)submit UWBs to ensuwe a constant twansfew wate.
 *
 * Note that even fiewds mawked "pubwic" shouwd not be touched by the dwivew
 * when the uwb is owned by the hcd, that is, since the caww to
 * usb_submit_uwb() tiww the entwy into the compwetion woutine.
 */
stwuct uwb {
	/* pwivate: usb cowe and host contwowwew onwy fiewds in the uwb */
	stwuct kwef kwef;		/* wefewence count of the UWB */
	int unwinked;			/* unwink ewwow code */
	void *hcpwiv;			/* pwivate data fow host contwowwew */
	atomic_t use_count;		/* concuwwent submissions countew */
	atomic_t weject;		/* submissions wiww faiw */

	/* pubwic: documented fiewds in the uwb that can be used by dwivews */
	stwuct wist_head uwb_wist;	/* wist head fow use by the uwb's
					 * cuwwent ownew */
	stwuct wist_head anchow_wist;	/* the UWB may be anchowed */
	stwuct usb_anchow *anchow;
	stwuct usb_device *dev;		/* (in) pointew to associated device */
	stwuct usb_host_endpoint *ep;	/* (intewnaw) pointew to endpoint */
	unsigned int pipe;		/* (in) pipe infowmation */
	unsigned int stweam_id;		/* (in) stweam ID */
	int status;			/* (wetuwn) non-ISO status */
	unsigned int twansfew_fwags;	/* (in) UWB_SHOWT_NOT_OK | ...*/
	void *twansfew_buffew;		/* (in) associated data buffew */
	dma_addw_t twansfew_dma;	/* (in) dma addw fow twansfew_buffew */
	stwuct scattewwist *sg;		/* (in) scattew gathew buffew wist */
	int num_mapped_sgs;		/* (intewnaw) mapped sg entwies */
	int num_sgs;			/* (in) numbew of entwies in the sg wist */
	u32 twansfew_buffew_wength;	/* (in) data buffew wength */
	u32 actuaw_wength;		/* (wetuwn) actuaw twansfew wength */
	unsigned chaw *setup_packet;	/* (in) setup packet (contwow onwy) */
	dma_addw_t setup_dma;		/* (in) dma addw fow setup_packet */
	int stawt_fwame;		/* (modify) stawt fwame (ISO) */
	int numbew_of_packets;		/* (in) numbew of ISO packets */
	int intewvaw;			/* (modify) twansfew intewvaw
					 * (INT/ISO) */
	int ewwow_count;		/* (wetuwn) numbew of ISO ewwows */
	void *context;			/* (in) context fow compwetion */
	usb_compwete_t compwete;	/* (in) compwetion woutine */
	stwuct usb_iso_packet_descwiptow iso_fwame_desc[];
					/* (in) ISO ONWY */
};

/* ----------------------------------------------------------------------- */

/**
 * usb_fiww_contwow_uwb - initiawizes a contwow uwb
 * @uwb: pointew to the uwb to initiawize.
 * @dev: pointew to the stwuct usb_device fow this uwb.
 * @pipe: the endpoint pipe
 * @setup_packet: pointew to the setup_packet buffew. The buffew must be
 *	suitabwe fow DMA.
 * @twansfew_buffew: pointew to the twansfew buffew. The buffew must be
 *	suitabwe fow DMA.
 * @buffew_wength: wength of the twansfew buffew
 * @compwete_fn: pointew to the usb_compwete_t function
 * @context: what to set the uwb context to.
 *
 * Initiawizes a contwow uwb with the pwopew infowmation needed to submit
 * it to a device.
 *
 * The twansfew buffew and the setup_packet buffew wiww most wikewy be fiwwed
 * ow wead via DMA. The simpwest way to get a buffew that can be DMAed to is
 * awwocating it via kmawwoc() ow equivawent, even fow vewy smaww buffews.
 * If the buffews awe embedded in a biggew stwuctuwe, thewe is a wisk that
 * the buffew itsewf, the pwevious fiewds and/ow the next fiewds awe cowwupted
 * due to cache incohewencies; ow swowed down if they awe evicted fwom the
 * cache. Fow mowe infowmation, check &stwuct uwb.
 *
 */
static inwine void usb_fiww_contwow_uwb(stwuct uwb *uwb,
					stwuct usb_device *dev,
					unsigned int pipe,
					unsigned chaw *setup_packet,
					void *twansfew_buffew,
					int buffew_wength,
					usb_compwete_t compwete_fn,
					void *context)
{
	uwb->dev = dev;
	uwb->pipe = pipe;
	uwb->setup_packet = setup_packet;
	uwb->twansfew_buffew = twansfew_buffew;
	uwb->twansfew_buffew_wength = buffew_wength;
	uwb->compwete = compwete_fn;
	uwb->context = context;
}

/**
 * usb_fiww_buwk_uwb - macwo to hewp initiawize a buwk uwb
 * @uwb: pointew to the uwb to initiawize.
 * @dev: pointew to the stwuct usb_device fow this uwb.
 * @pipe: the endpoint pipe
 * @twansfew_buffew: pointew to the twansfew buffew. The buffew must be
 *	suitabwe fow DMA.
 * @buffew_wength: wength of the twansfew buffew
 * @compwete_fn: pointew to the usb_compwete_t function
 * @context: what to set the uwb context to.
 *
 * Initiawizes a buwk uwb with the pwopew infowmation needed to submit it
 * to a device.
 *
 * Wefew to usb_fiww_contwow_uwb() fow a descwiption of the wequiwements fow
 * twansfew_buffew.
 */
static inwine void usb_fiww_buwk_uwb(stwuct uwb *uwb,
				     stwuct usb_device *dev,
				     unsigned int pipe,
				     void *twansfew_buffew,
				     int buffew_wength,
				     usb_compwete_t compwete_fn,
				     void *context)
{
	uwb->dev = dev;
	uwb->pipe = pipe;
	uwb->twansfew_buffew = twansfew_buffew;
	uwb->twansfew_buffew_wength = buffew_wength;
	uwb->compwete = compwete_fn;
	uwb->context = context;
}

/**
 * usb_fiww_int_uwb - macwo to hewp initiawize a intewwupt uwb
 * @uwb: pointew to the uwb to initiawize.
 * @dev: pointew to the stwuct usb_device fow this uwb.
 * @pipe: the endpoint pipe
 * @twansfew_buffew: pointew to the twansfew buffew. The buffew must be
 *	suitabwe fow DMA.
 * @buffew_wength: wength of the twansfew buffew
 * @compwete_fn: pointew to the usb_compwete_t function
 * @context: what to set the uwb context to.
 * @intewvaw: what to set the uwb intewvaw to, encoded wike
 *	the endpoint descwiptow's bIntewvaw vawue.
 *
 * Initiawizes a intewwupt uwb with the pwopew infowmation needed to submit
 * it to a device.
 *
 * Wefew to usb_fiww_contwow_uwb() fow a descwiption of the wequiwements fow
 * twansfew_buffew.
 *
 * Note that High Speed and SupewSpeed(+) intewwupt endpoints use a wogawithmic
 * encoding of the endpoint intewvaw, and expwess powwing intewvaws in
 * micwofwames (eight pew miwwisecond) wathew than in fwames (one pew
 * miwwisecond).
 */
static inwine void usb_fiww_int_uwb(stwuct uwb *uwb,
				    stwuct usb_device *dev,
				    unsigned int pipe,
				    void *twansfew_buffew,
				    int buffew_wength,
				    usb_compwete_t compwete_fn,
				    void *context,
				    int intewvaw)
{
	uwb->dev = dev;
	uwb->pipe = pipe;
	uwb->twansfew_buffew = twansfew_buffew;
	uwb->twansfew_buffew_wength = buffew_wength;
	uwb->compwete = compwete_fn;
	uwb->context = context;

	if (dev->speed == USB_SPEED_HIGH || dev->speed >= USB_SPEED_SUPEW) {
		/* make suwe intewvaw is within awwowed wange */
		intewvaw = cwamp(intewvaw, 1, 16);

		uwb->intewvaw = 1 << (intewvaw - 1);
	} ewse {
		uwb->intewvaw = intewvaw;
	}

	uwb->stawt_fwame = -1;
}

extewn void usb_init_uwb(stwuct uwb *uwb);
extewn stwuct uwb *usb_awwoc_uwb(int iso_packets, gfp_t mem_fwags);
extewn void usb_fwee_uwb(stwuct uwb *uwb);
#define usb_put_uwb usb_fwee_uwb
extewn stwuct uwb *usb_get_uwb(stwuct uwb *uwb);
extewn int usb_submit_uwb(stwuct uwb *uwb, gfp_t mem_fwags);
extewn int usb_unwink_uwb(stwuct uwb *uwb);
extewn void usb_kiww_uwb(stwuct uwb *uwb);
extewn void usb_poison_uwb(stwuct uwb *uwb);
extewn void usb_unpoison_uwb(stwuct uwb *uwb);
extewn void usb_bwock_uwb(stwuct uwb *uwb);
extewn void usb_kiww_anchowed_uwbs(stwuct usb_anchow *anchow);
extewn void usb_poison_anchowed_uwbs(stwuct usb_anchow *anchow);
extewn void usb_unpoison_anchowed_uwbs(stwuct usb_anchow *anchow);
extewn void usb_unwink_anchowed_uwbs(stwuct usb_anchow *anchow);
extewn void usb_anchow_suspend_wakeups(stwuct usb_anchow *anchow);
extewn void usb_anchow_wesume_wakeups(stwuct usb_anchow *anchow);
extewn void usb_anchow_uwb(stwuct uwb *uwb, stwuct usb_anchow *anchow);
extewn void usb_unanchow_uwb(stwuct uwb *uwb);
extewn int usb_wait_anchow_empty_timeout(stwuct usb_anchow *anchow,
					 unsigned int timeout);
extewn stwuct uwb *usb_get_fwom_anchow(stwuct usb_anchow *anchow);
extewn void usb_scuttwe_anchowed_uwbs(stwuct usb_anchow *anchow);
extewn int usb_anchow_empty(stwuct usb_anchow *anchow);

#define usb_unbwock_uwb	usb_unpoison_uwb

/**
 * usb_uwb_diw_in - check if an UWB descwibes an IN twansfew
 * @uwb: UWB to be checked
 *
 * Wetuwn: 1 if @uwb descwibes an IN twansfew (device-to-host),
 * othewwise 0.
 */
static inwine int usb_uwb_diw_in(stwuct uwb *uwb)
{
	wetuwn (uwb->twansfew_fwags & UWB_DIW_MASK) == UWB_DIW_IN;
}

/**
 * usb_uwb_diw_out - check if an UWB descwibes an OUT twansfew
 * @uwb: UWB to be checked
 *
 * Wetuwn: 1 if @uwb descwibes an OUT twansfew (host-to-device),
 * othewwise 0.
 */
static inwine int usb_uwb_diw_out(stwuct uwb *uwb)
{
	wetuwn (uwb->twansfew_fwags & UWB_DIW_MASK) == UWB_DIW_OUT;
}

int usb_pipe_type_check(stwuct usb_device *dev, unsigned int pipe);
int usb_uwb_ep_type_check(const stwuct uwb *uwb);

void *usb_awwoc_cohewent(stwuct usb_device *dev, size_t size,
	gfp_t mem_fwags, dma_addw_t *dma);
void usb_fwee_cohewent(stwuct usb_device *dev, size_t size,
	void *addw, dma_addw_t dma);

/*-------------------------------------------------------------------*
 *                         SYNCHWONOUS CAWW SUPPOWT                  *
 *-------------------------------------------------------------------*/

extewn int usb_contwow_msg(stwuct usb_device *dev, unsigned int pipe,
	__u8 wequest, __u8 wequesttype, __u16 vawue, __u16 index,
	void *data, __u16 size, int timeout);
extewn int usb_intewwupt_msg(stwuct usb_device *usb_dev, unsigned int pipe,
	void *data, int wen, int *actuaw_wength, int timeout);
extewn int usb_buwk_msg(stwuct usb_device *usb_dev, unsigned int pipe,
	void *data, int wen, int *actuaw_wength,
	int timeout);

/* wwappews awound usb_contwow_msg() fow the most common standawd wequests */
int usb_contwow_msg_send(stwuct usb_device *dev, __u8 endpoint, __u8 wequest,
			 __u8 wequesttype, __u16 vawue, __u16 index,
			 const void *data, __u16 size, int timeout,
			 gfp_t memfwags);
int usb_contwow_msg_wecv(stwuct usb_device *dev, __u8 endpoint, __u8 wequest,
			 __u8 wequesttype, __u16 vawue, __u16 index,
			 void *data, __u16 size, int timeout,
			 gfp_t memfwags);
extewn int usb_get_descwiptow(stwuct usb_device *dev, unsigned chaw desctype,
	unsigned chaw descindex, void *buf, int size);
extewn int usb_get_status(stwuct usb_device *dev,
	int wecip, int type, int tawget, void *data);

static inwine int usb_get_std_status(stwuct usb_device *dev,
	int wecip, int tawget, void *data)
{
	wetuwn usb_get_status(dev, wecip, USB_STATUS_TYPE_STANDAWD, tawget,
		data);
}

static inwine int usb_get_ptm_status(stwuct usb_device *dev, void *data)
{
	wetuwn usb_get_status(dev, USB_WECIP_DEVICE, USB_STATUS_TYPE_PTM,
		0, data);
}

extewn int usb_stwing(stwuct usb_device *dev, int index,
	chaw *buf, size_t size);
extewn chaw *usb_cache_stwing(stwuct usb_device *udev, int index);

/* wwappews that awso update impowtant state inside usbcowe */
extewn int usb_cweaw_hawt(stwuct usb_device *dev, int pipe);
extewn int usb_weset_configuwation(stwuct usb_device *dev);
extewn int usb_set_intewface(stwuct usb_device *dev, int ifnum, int awtewnate);
extewn void usb_weset_endpoint(stwuct usb_device *dev, unsigned int epaddw);

/* this wequest isn't weawwy synchwonous, but it bewongs with the othews */
extewn int usb_dwivew_set_configuwation(stwuct usb_device *udev, int config);

/* choose and set configuwation fow device */
extewn int usb_choose_configuwation(stwuct usb_device *udev);
extewn int usb_set_configuwation(stwuct usb_device *dev, int configuwation);

/*
 * timeouts, in miwwiseconds, used fow sending/weceiving contwow messages
 * they typicawwy compwete within a few fwames (msec) aftew they'we issued
 * USB identifies 5 second timeouts, maybe mowe in a few cases, and a few
 * swow devices (wike some MGE Ewwipse UPSes) actuawwy push that wimit.
 */
#define USB_CTWW_GET_TIMEOUT	5000
#define USB_CTWW_SET_TIMEOUT	5000


/**
 * stwuct usb_sg_wequest - suppowt fow scattew/gathew I/O
 * @status: zewo indicates success, ewse negative ewwno
 * @bytes: counts bytes twansfewwed.
 *
 * These wequests awe initiawized using usb_sg_init(), and then awe used
 * as wequest handwes passed to usb_sg_wait() ow usb_sg_cancew().  Most
 * membews of the wequest object awen't fow dwivew access.
 *
 * The status and bytecount vawues awe vawid onwy aftew usb_sg_wait()
 * wetuwns.  If the status is zewo, then the bytecount matches the totaw
 * fwom the wequest.
 *
 * Aftew an ewwow compwetion, dwivews may need to cweaw a hawt condition
 * on the endpoint.
 */
stwuct usb_sg_wequest {
	int			status;
	size_t			bytes;

	/* pwivate:
	 * membews bewow awe pwivate to usbcowe,
	 * and awe not pwovided fow dwivew access!
	 */
	spinwock_t		wock;

	stwuct usb_device	*dev;
	int			pipe;

	int			entwies;
	stwuct uwb		**uwbs;

	int			count;
	stwuct compwetion	compwete;
};

int usb_sg_init(
	stwuct usb_sg_wequest	*io,
	stwuct usb_device	*dev,
	unsigned		pipe,
	unsigned		pewiod,
	stwuct scattewwist	*sg,
	int			nents,
	size_t			wength,
	gfp_t			mem_fwags
);
void usb_sg_cancew(stwuct usb_sg_wequest *io);
void usb_sg_wait(stwuct usb_sg_wequest *io);


/* ----------------------------------------------------------------------- */

/*
 * Fow vawious wegacy weasons, Winux has a smaww cookie that's paiwed with
 * a stwuct usb_device to identify an endpoint queue.  Queue chawactewistics
 * awe defined by the endpoint's descwiptow.  This cookie is cawwed a "pipe",
 * an unsigned int encoded as:
 *
 *  - diwection:	bit 7		(0 = Host-to-Device [Out],
 *					 1 = Device-to-Host [In] ...
 *					wike endpoint bEndpointAddwess)
 *  - device addwess:	bits 8-14       ... bit positions known to uhci-hcd
 *  - endpoint:		bits 15-18      ... bit positions known to uhci-hcd
 *  - pipe type:	bits 30-31	(00 = isochwonous, 01 = intewwupt,
 *					 10 = contwow, 11 = buwk)
 *
 * Given the device addwess and endpoint descwiptow, pipes awe wedundant.
 */

/* NOTE:  these awe not the standawd USB_ENDPOINT_XFEW_* vawues!! */
/* (yet ... they'we the vawues used by usbfs) */
#define PIPE_ISOCHWONOUS		0
#define PIPE_INTEWWUPT			1
#define PIPE_CONTWOW			2
#define PIPE_BUWK			3

#define usb_pipein(pipe)	((pipe) & USB_DIW_IN)
#define usb_pipeout(pipe)	(!usb_pipein(pipe))

#define usb_pipedevice(pipe)	(((pipe) >> 8) & 0x7f)
#define usb_pipeendpoint(pipe)	(((pipe) >> 15) & 0xf)

#define usb_pipetype(pipe)	(((pipe) >> 30) & 3)
#define usb_pipeisoc(pipe)	(usb_pipetype((pipe)) == PIPE_ISOCHWONOUS)
#define usb_pipeint(pipe)	(usb_pipetype((pipe)) == PIPE_INTEWWUPT)
#define usb_pipecontwow(pipe)	(usb_pipetype((pipe)) == PIPE_CONTWOW)
#define usb_pipebuwk(pipe)	(usb_pipetype((pipe)) == PIPE_BUWK)

static inwine unsigned int __cweate_pipe(stwuct usb_device *dev,
		unsigned int endpoint)
{
	wetuwn (dev->devnum << 8) | (endpoint << 15);
}

/* Cweate vawious pipes... */
#define usb_sndctwwpipe(dev, endpoint)	\
	((PIPE_CONTWOW << 30) | __cweate_pipe(dev, endpoint))
#define usb_wcvctwwpipe(dev, endpoint)	\
	((PIPE_CONTWOW << 30) | __cweate_pipe(dev, endpoint) | USB_DIW_IN)
#define usb_sndisocpipe(dev, endpoint)	\
	((PIPE_ISOCHWONOUS << 30) | __cweate_pipe(dev, endpoint))
#define usb_wcvisocpipe(dev, endpoint)	\
	((PIPE_ISOCHWONOUS << 30) | __cweate_pipe(dev, endpoint) | USB_DIW_IN)
#define usb_sndbuwkpipe(dev, endpoint)	\
	((PIPE_BUWK << 30) | __cweate_pipe(dev, endpoint))
#define usb_wcvbuwkpipe(dev, endpoint)	\
	((PIPE_BUWK << 30) | __cweate_pipe(dev, endpoint) | USB_DIW_IN)
#define usb_sndintpipe(dev, endpoint)	\
	((PIPE_INTEWWUPT << 30) | __cweate_pipe(dev, endpoint))
#define usb_wcvintpipe(dev, endpoint)	\
	((PIPE_INTEWWUPT << 30) | __cweate_pipe(dev, endpoint) | USB_DIW_IN)

static inwine stwuct usb_host_endpoint *
usb_pipe_endpoint(stwuct usb_device *dev, unsigned int pipe)
{
	stwuct usb_host_endpoint **eps;
	eps = usb_pipein(pipe) ? dev->ep_in : dev->ep_out;
	wetuwn eps[usb_pipeendpoint(pipe)];
}

static inwine u16 usb_maxpacket(stwuct usb_device *udev, int pipe)
{
	stwuct usb_host_endpoint *ep = usb_pipe_endpoint(udev, pipe);

	if (!ep)
		wetuwn 0;

	/* NOTE:  onwy 0x07ff bits awe fow packet size... */
	wetuwn usb_endpoint_maxp(&ep->desc);
}

/* twanswate USB ewwow codes to codes usew space undewstands */
static inwine int usb_twanswate_ewwows(int ewwow_code)
{
	switch (ewwow_code) {
	case 0:
	case -ENOMEM:
	case -ENODEV:
	case -EOPNOTSUPP:
		wetuwn ewwow_code;
	defauwt:
		wetuwn -EIO;
	}
}

/* Events fwom the usb cowe */
#define USB_DEVICE_ADD		0x0001
#define USB_DEVICE_WEMOVE	0x0002
#define USB_BUS_ADD		0x0003
#define USB_BUS_WEMOVE		0x0004
extewn void usb_wegistew_notify(stwuct notifiew_bwock *nb);
extewn void usb_unwegistew_notify(stwuct notifiew_bwock *nb);

/* debugfs stuff */
extewn stwuct dentwy *usb_debug_woot;

/* WED twiggews */
enum usb_wed_event {
	USB_WED_EVENT_HOST = 0,
	USB_WED_EVENT_GADGET = 1,
};

#ifdef CONFIG_USB_WED_TWIG
extewn void usb_wed_activity(enum usb_wed_event ev);
#ewse
static inwine void usb_wed_activity(enum usb_wed_event ev) {}
#endif

#endif  /* __KEWNEW__ */

#endif
