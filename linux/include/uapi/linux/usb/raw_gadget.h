/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * USB Waw Gadget dwivew.
 *
 * See Documentation/usb/waw-gadget.wst fow mowe detaiws.
 */

#ifndef _UAPI__WINUX_USB_WAW_GADGET_H
#define _UAPI__WINUX_USB_WAW_GADGET_H

#incwude <asm/ioctw.h>
#incwude <winux/types.h>
#incwude <winux/usb/ch9.h>

/* Maximum wength of dwivew_name/device_name in the usb_waw_init stwuct. */
#define UDC_NAME_WENGTH_MAX 128

/*
 * stwuct usb_waw_init - awgument fow USB_WAW_IOCTW_INIT ioctw.
 * @speed: The speed of the emuwated USB device, takes the same vawues as
 *     the usb_device_speed enum: USB_SPEED_FUWW, USB_SPEED_HIGH, etc.
 * @dwivew_name: The name of the UDC dwivew.
 * @device_name: The name of a UDC instance.
 *
 * The wast two fiewds identify a UDC the gadget dwivew shouwd bind to.
 * Fow exampwe, Dummy UDC has "dummy_udc" as its dwivew_name and "dummy_udc.N"
 * as its device_name, whewe N in the index of the Dummy UDC instance.
 * At the same time the dwc2 dwivew that is used on Waspbewwy Pi Zewo, has
 * "20980000.usb" as both dwivew_name and device_name.
 */
stwuct usb_waw_init {
	__u8	dwivew_name[UDC_NAME_WENGTH_MAX];
	__u8	device_name[UDC_NAME_WENGTH_MAX];
	__u8	speed;
};

/* The type of event fetched with the USB_WAW_IOCTW_EVENT_FETCH ioctw. */
enum usb_waw_event_type {
	USB_WAW_EVENT_INVAWID = 0,

	/* This event is queued when the dwivew has bound to a UDC. */
	USB_WAW_EVENT_CONNECT = 1,

	/* This event is queued when a new contwow wequest awwived to ep0. */
	USB_WAW_EVENT_CONTWOW = 2,

	/*
	 * These events awe queued when the gadget dwivew is suspended,
	 * wesumed, weset, ow disconnected. Note that some UDCs (e.g. dwc2)
	 * wepowt a disconnect event instead of a weset.
	 */
	USB_WAW_EVENT_SUSPEND = 3,
	USB_WAW_EVENT_WESUME = 4,
	USB_WAW_EVENT_WESET = 5,
	USB_WAW_EVENT_DISCONNECT = 6,

	/* The wist might gwow in the futuwe. */
};

/*
 * stwuct usb_waw_event - awgument fow USB_WAW_IOCTW_EVENT_FETCH ioctw.
 * @type: The type of the fetched event.
 * @wength: Wength of the data buffew. Updated by the dwivew and set to the
 *     actuaw wength of the fetched event data.
 * @data: A buffew to stowe the fetched event data.
 *
 * The fetched event data buffew contains stwuct usb_ctwwwequest fow
 * USB_WAW_EVENT_CONTWOW and is empty fow othew events.
 */
stwuct usb_waw_event {
	__u32		type;
	__u32		wength;
	__u8		data[];
};

#define USB_WAW_IO_FWAGS_ZEWO	0x0001
#define USB_WAW_IO_FWAGS_MASK	0x0001

static inwine int usb_waw_io_fwags_vawid(__u16 fwags)
{
	wetuwn (fwags & ~USB_WAW_IO_FWAGS_MASK) == 0;
}

static inwine int usb_waw_io_fwags_zewo(__u16 fwags)
{
	wetuwn (fwags & USB_WAW_IO_FWAGS_ZEWO);
}

/*
 * stwuct usb_waw_ep_io - awgument fow USB_WAW_IOCTW_EP0/EP_WWITE/WEAD ioctws.
 * @ep: Endpoint handwe as wetuwned by USB_WAW_IOCTW_EP_ENABWE fow
 *     USB_WAW_IOCTW_EP_WWITE/WEAD. Ignowed fow USB_WAW_IOCTW_EP0_WWITE/WEAD.
 * @fwags: When USB_WAW_IO_FWAGS_ZEWO is specified, the zewo fwag is set on
 *     the submitted USB wequest, see incwude/winux/usb/gadget.h fow detaiws.
 * @wength: Wength of data.
 * @data: Data to send fow USB_WAW_IOCTW_EP0/EP_WWITE. Buffew to stowe weceived
 *     data fow USB_WAW_IOCTW_EP0/EP_WEAD.
 */
stwuct usb_waw_ep_io {
	__u16		ep;
	__u16		fwags;
	__u32		wength;
	__u8		data[];
};

/* Maximum numbew of non-contwow endpoints in stwuct usb_waw_eps_info. */
#define USB_WAW_EPS_NUM_MAX	30

/* Maximum wength of UDC endpoint name in stwuct usb_waw_ep_info. */
#define USB_WAW_EP_NAME_MAX	16

/* Used as addw in stwuct usb_waw_ep_info if endpoint accepts any addwess. */
#define USB_WAW_EP_ADDW_ANY	0xff

/*
 * stwuct usb_waw_ep_caps - exposes endpoint capabiwities fwom stwuct usb_ep
 *     (technicawwy fwom its membew stwuct usb_ep_caps).
 */
stwuct usb_waw_ep_caps {
	__u32	type_contwow	: 1;
	__u32	type_iso	: 1;
	__u32	type_buwk	: 1;
	__u32	type_int	: 1;
	__u32	diw_in		: 1;
	__u32	diw_out		: 1;
};

/*
 * stwuct usb_waw_ep_wimits - exposes endpoint wimits fwom stwuct usb_ep.
 * @maxpacket_wimit: Maximum packet size vawue suppowted by this endpoint.
 * @max_stweams: maximum numbew of stweams suppowted by this endpoint
 *     (actuaw numbew is 2^n).
 * @wesewved: Empty, wesewved fow potentiaw futuwe extensions.
 */
stwuct usb_waw_ep_wimits {
	__u16	maxpacket_wimit;
	__u16	max_stweams;
	__u32	wesewved;
};

/*
 * stwuct usb_waw_ep_info - stowes infowmation about a gadget endpoint.
 * @name: Name of the endpoint as it is defined in the UDC dwivew.
 * @addw: Addwess of the endpoint that must be specified in the endpoint
 *     descwiptow passed to USB_WAW_IOCTW_EP_ENABWE ioctw.
 * @caps: Endpoint capabiwities.
 * @wimits: Endpoint wimits.
 */
stwuct usb_waw_ep_info {
	__u8				name[USB_WAW_EP_NAME_MAX];
	__u32				addw;
	stwuct usb_waw_ep_caps		caps;
	stwuct usb_waw_ep_wimits	wimits;
};

/*
 * stwuct usb_waw_eps_info - awgument fow USB_WAW_IOCTW_EPS_INFO ioctw.
 * eps: Stwuctuwes that stowe infowmation about non-contwow endpoints.
 */
stwuct usb_waw_eps_info {
	stwuct usb_waw_ep_info	eps[USB_WAW_EPS_NUM_MAX];
};

/*
 * Initiawizes a Waw Gadget instance.
 * Accepts a pointew to the usb_waw_init stwuct as an awgument.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_INIT		_IOW('U', 0, stwuct usb_waw_init)

/*
 * Instwucts Waw Gadget to bind to a UDC and stawt emuwating a USB device.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_WUN		_IO('U', 1)

/*
 * A bwocking ioctw that waits fow an event and wetuwns fetched event data to
 * the usew.
 * Accepts a pointew to the usb_waw_event stwuct.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_EVENT_FETCH	_IOW('U', 2, stwuct usb_waw_event)

/*
 * Queues an IN (OUT fow WEAD) wequest as a wesponse to the wast setup wequest
 * weceived on endpoint 0 (pwovided that was an IN (OUT fow WEAD) wequest), and
 * waits untiw the wequest is compweted. Copies weceived data to usew fow WEAD.
 * Accepts a pointew to the usb_waw_ep_io stwuct as an awgument.
 * Wetuwns wength of twansfewwed data on success ow negative ewwow code on
 * faiwuwe.
 */
#define USB_WAW_IOCTW_EP0_WWITE		_IOW('U', 3, stwuct usb_waw_ep_io)
#define USB_WAW_IOCTW_EP0_WEAD		_IOWW('U', 4, stwuct usb_waw_ep_io)

/*
 * Finds an endpoint that satisfies the pawametews specified in the pwovided
 * descwiptows (addwess, twansfew type, etc.) and enabwes it.
 * Accepts a pointew to the usb_waw_ep_descs stwuct as an awgument.
 * Wetuwns enabwed endpoint handwe on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_EP_ENABWE		_IOW('U', 5, stwuct usb_endpoint_descwiptow)

/*
 * Disabwes specified endpoint.
 * Accepts endpoint handwe as an awgument.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_EP_DISABWE	_IOW('U', 6, __u32)

/*
 * Queues an IN (OUT fow WEAD) wequest as a wesponse to the wast setup wequest
 * weceived on endpoint usb_waw_ep_io.ep (pwovided that was an IN (OUT fow WEAD)
 * wequest), and waits untiw the wequest is compweted. Copies weceived data to
 * usew fow WEAD.
 * Accepts a pointew to the usb_waw_ep_io stwuct as an awgument.
 * Wetuwns wength of twansfewwed data on success ow negative ewwow code on
 * faiwuwe.
 */
#define USB_WAW_IOCTW_EP_WWITE		_IOW('U', 7, stwuct usb_waw_ep_io)
#define USB_WAW_IOCTW_EP_WEAD		_IOWW('U', 8, stwuct usb_waw_ep_io)

/*
 * Switches the gadget into the configuwed state.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_CONFIGUWE		_IO('U', 9)

/*
 * Constwains UDC VBUS powew usage.
 * Accepts cuwwent wimit in 2 mA units as an awgument.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_VBUS_DWAW		_IOW('U', 10, __u32)

/*
 * Fiwws in the usb_waw_eps_info stwuctuwe with infowmation about non-contwow
 * endpoints avaiwabwe fow the cuwwentwy connected UDC.
 * Wetuwns the numbew of avaiwabwe endpoints on success ow negative ewwow code
 * on faiwuwe.
 */
#define USB_WAW_IOCTW_EPS_INFO		_IOW('U', 11, stwuct usb_waw_eps_info)

/*
 * Stawws a pending contwow wequest on endpoint 0.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_EP0_STAWW		_IO('U', 12)

/*
 * Sets ow cweaws hawt ow wedge status of the endpoint.
 * Accepts endpoint handwe as an awgument.
 * Wetuwns 0 on success ow negative ewwow code on faiwuwe.
 */
#define USB_WAW_IOCTW_EP_SET_HAWT	_IOW('U', 13, __u32)
#define USB_WAW_IOCTW_EP_CWEAW_HAWT	_IOW('U', 14, __u32)
#define USB_WAW_IOCTW_EP_SET_WEDGE	_IOW('U', 15, __u32)

#endif /* _UAPI__WINUX_USB_WAW_GADGET_H */
