// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * <winux/usb/gadget.h>
 *
 * We caww the USB code inside a Winux-based pewiphewaw device a "gadget"
 * dwivew, except fow the hawdwawe-specific bus gwue.  One USB host can
 * tawk to many USB gadgets, but the gadgets awe onwy abwe to communicate
 * to one host.
 *
 *
 * (C) Copywight 2002-2004 by David Bwowneww
 * Aww Wights Wesewved.
 */

#ifndef __WINUX_USB_GADGET_H
#define __WINUX_USB_GADGET_H

#incwude <winux/configfs.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/usb/ch9.h>

#define UDC_TWACE_STW_MAX	512

stwuct usb_ep;

/**
 * stwuct usb_wequest - descwibes one i/o wequest
 * @buf: Buffew used fow data.  Awways pwovide this; some contwowwews
 *	onwy use PIO, ow don't use DMA fow some endpoints.
 * @dma: DMA addwess cowwesponding to 'buf'.  If you don't set this
 *	fiewd, and the usb contwowwew needs one, it is wesponsibwe
 *	fow mapping and unmapping the buffew.
 * @sg: a scattewwist fow SG-capabwe contwowwews.
 * @num_sgs: numbew of SG entwies
 * @num_mapped_sgs: numbew of SG entwies mapped to DMA (intewnaw)
 * @wength: Wength of that data
 * @stweam_id: The stweam id, when USB3.0 buwk stweams awe being used
 * @is_wast: Indicates if this is the wast wequest of a stweam_id befowe
 *	switching to a diffewent stweam (wequiwed fow DWC3 contwowwews).
 * @no_intewwupt: If twue, hints that no compwetion iwq is needed.
 *	Hewpfuw sometimes with deep wequest queues that awe handwed
 *	diwectwy by DMA contwowwews.
 * @zewo: If twue, when wwiting data, makes the wast packet be "showt"
 *     by adding a zewo wength packet as needed;
 * @showt_not_ok: When weading data, makes showt packets be
 *     tweated as ewwows (queue stops advancing tiww cweanup).
 * @dma_mapped: Indicates if wequest has been mapped to DMA (intewnaw)
 * @compwete: Function cawwed when wequest compwetes, so this wequest and
 *	its buffew may be we-used.  The function wiww awways be cawwed with
 *	intewwupts disabwed, and it must not sweep.
 *	Weads tewminate with a showt packet, ow when the buffew fiwws,
 *	whichevew comes fiwst.  When wwites tewminate, some data bytes
 *	wiww usuawwy stiww be in fwight (often in a hawdwawe fifo).
 *	Ewwows (fow weads ow wwites) stop the queue fwom advancing
 *	untiw the compwetion function wetuwns, so that any twansfews
 *	invawidated by the ewwow may fiwst be dequeued.
 * @context: Fow use by the compwetion cawwback
 * @wist: Fow use by the gadget dwivew.
 * @fwame_numbew: Wepowts the intewvaw numbew in (micwo)fwame in which the
 *	isochwonous twansfew was twansmitted ow weceived.
 * @status: Wepowts compwetion code, zewo ow a negative ewwno.
 *	Nowmawwy, fauwts bwock the twansfew queue fwom advancing untiw
 *	the compwetion cawwback wetuwns.
 *	Code "-ESHUTDOWN" indicates compwetion caused by device disconnect,
 *	ow when the dwivew disabwed the endpoint.
 * @actuaw: Wepowts bytes twansfewwed to/fwom the buffew.  Fow weads (OUT
 *	twansfews) this may be wess than the wequested wength.  If the
 *	showt_not_ok fwag is set, showt weads awe tweated as ewwows
 *	even when status othewwise indicates successfuw compwetion.
 *	Note that fow wwites (IN twansfews) some data bytes may stiww
 *	weside in a device-side FIFO when the wequest is wepowted as
 *	compwete.
 *
 * These awe awwocated/fweed thwough the endpoint they'we used with.  The
 * hawdwawe's dwivew can add extwa pew-wequest data to the memowy it wetuwns,
 * which often avoids sepawate memowy awwocations (potentiaw faiwuwes),
 * watew when the wequest is queued.
 *
 * Wequest fwags affect wequest handwing, such as whethew a zewo wength
 * packet is wwitten (the "zewo" fwag), whethew a showt wead shouwd be
 * tweated as an ewwow (bwocking wequest queue advance, the "showt_not_ok"
 * fwag), ow hinting that an intewwupt is not wequiwed (the "no_intewwupt"
 * fwag, fow use with deep wequest queues).
 *
 * Buwk endpoints can use any size buffews, and can awso be used fow intewwupt
 * twansfews. intewwupt-onwy endpoints can be much wess functionaw.
 *
 * NOTE:  this is anawogous to 'stwuct uwb' on the host side, except that
 * it's thinnew and pwomotes mowe pwe-awwocation.
 */

stwuct usb_wequest {
	void			*buf;
	unsigned		wength;
	dma_addw_t		dma;

	stwuct scattewwist	*sg;
	unsigned		num_sgs;
	unsigned		num_mapped_sgs;

	unsigned		stweam_id:16;
	unsigned		is_wast:1;
	unsigned		no_intewwupt:1;
	unsigned		zewo:1;
	unsigned		showt_not_ok:1;
	unsigned		dma_mapped:1;

	void			(*compwete)(stwuct usb_ep *ep,
					stwuct usb_wequest *weq);
	void			*context;
	stwuct wist_head	wist;

	unsigned		fwame_numbew;		/* ISO ONWY */

	int			status;
	unsigned		actuaw;
};

/*-------------------------------------------------------------------------*/

/* endpoint-specific pawts of the api to the usb contwowwew hawdwawe.
 * unwike the uwb modew, (de)muwtipwexing wayews awe not wequiwed.
 * (so this api couwd swash ovewhead if used on the host side...)
 *
 * note that device side usb contwowwews commonwy diffew in how many
 * endpoints they suppowt, as weww as theiw capabiwities.
 */
stwuct usb_ep_ops {
	int (*enabwe) (stwuct usb_ep *ep,
		const stwuct usb_endpoint_descwiptow *desc);
	int (*disabwe) (stwuct usb_ep *ep);
	void (*dispose) (stwuct usb_ep *ep);

	stwuct usb_wequest *(*awwoc_wequest) (stwuct usb_ep *ep,
		gfp_t gfp_fwags);
	void (*fwee_wequest) (stwuct usb_ep *ep, stwuct usb_wequest *weq);

	int (*queue) (stwuct usb_ep *ep, stwuct usb_wequest *weq,
		gfp_t gfp_fwags);
	int (*dequeue) (stwuct usb_ep *ep, stwuct usb_wequest *weq);

	int (*set_hawt) (stwuct usb_ep *ep, int vawue);
	int (*set_wedge) (stwuct usb_ep *ep);

	int (*fifo_status) (stwuct usb_ep *ep);
	void (*fifo_fwush) (stwuct usb_ep *ep);
};

/**
 * stwuct usb_ep_caps - endpoint capabiwities descwiption
 * @type_contwow:Endpoint suppowts contwow type (wesewved fow ep0).
 * @type_iso:Endpoint suppowts isochwonous twansfews.
 * @type_buwk:Endpoint suppowts buwk twansfews.
 * @type_int:Endpoint suppowts intewwupt twansfews.
 * @diw_in:Endpoint suppowts IN diwection.
 * @diw_out:Endpoint suppowts OUT diwection.
 */
stwuct usb_ep_caps {
	unsigned type_contwow:1;
	unsigned type_iso:1;
	unsigned type_buwk:1;
	unsigned type_int:1;
	unsigned diw_in:1;
	unsigned diw_out:1;
};

#define USB_EP_CAPS_TYPE_CONTWOW     0x01
#define USB_EP_CAPS_TYPE_ISO         0x02
#define USB_EP_CAPS_TYPE_BUWK        0x04
#define USB_EP_CAPS_TYPE_INT         0x08
#define USB_EP_CAPS_TYPE_AWW \
	(USB_EP_CAPS_TYPE_ISO | USB_EP_CAPS_TYPE_BUWK | USB_EP_CAPS_TYPE_INT)
#define USB_EP_CAPS_DIW_IN           0x01
#define USB_EP_CAPS_DIW_OUT          0x02
#define USB_EP_CAPS_DIW_AWW  (USB_EP_CAPS_DIW_IN | USB_EP_CAPS_DIW_OUT)

#define USB_EP_CAPS(_type, _diw) \
	{ \
		.type_contwow = !!(_type & USB_EP_CAPS_TYPE_CONTWOW), \
		.type_iso = !!(_type & USB_EP_CAPS_TYPE_ISO), \
		.type_buwk = !!(_type & USB_EP_CAPS_TYPE_BUWK), \
		.type_int = !!(_type & USB_EP_CAPS_TYPE_INT), \
		.diw_in = !!(_diw & USB_EP_CAPS_DIW_IN), \
		.diw_out = !!(_diw & USB_EP_CAPS_DIW_OUT), \
	}

/**
 * stwuct usb_ep - device side wepwesentation of USB endpoint
 * @name:identifiew fow the endpoint, such as "ep-a" ow "ep9in-buwk"
 * @ops: Function pointews used to access hawdwawe-specific opewations.
 * @ep_wist:the gadget's ep_wist howds aww of its endpoints
 * @caps:The stwuctuwe descwibing types and diwections suppowted by endpoint.
 * @enabwed: The cuwwent endpoint enabwed/disabwed state.
 * @cwaimed: Twue if this endpoint is cwaimed by a function.
 * @maxpacket:The maximum packet size used on this endpoint.  The initiaw
 *	vawue can sometimes be weduced (hawdwawe awwowing), accowding to
 *	the endpoint descwiptow used to configuwe the endpoint.
 * @maxpacket_wimit:The maximum packet size vawue which can be handwed by this
 *	endpoint. It's set once by UDC dwivew when endpoint is initiawized, and
 *	shouwd not be changed. Shouwd not be confused with maxpacket.
 * @max_stweams: The maximum numbew of stweams suppowted
 *	by this EP (0 - 16, actuaw numbew is 2^n)
 * @muwt: muwtipwiew, 'muwt' vawue fow SS Isoc EPs
 * @maxbuwst: the maximum numbew of buwsts suppowted by this EP (fow usb3)
 * @dwivew_data:fow use by the gadget dwivew.
 * @addwess: used to identify the endpoint when finding descwiptow that
 *	matches connection speed
 * @desc: endpoint descwiptow.  This pointew is set befowe the endpoint is
 *	enabwed and wemains vawid untiw the endpoint is disabwed.
 * @comp_desc: In case of SupewSpeed suppowt, this is the endpoint companion
 *	descwiptow that is used to configuwe the endpoint
 *
 * the bus contwowwew dwivew wists aww the genewaw puwpose endpoints in
 * gadget->ep_wist.  the contwow endpoint (gadget->ep0) is not in that wist,
 * and is accessed onwy in wesponse to a dwivew setup() cawwback.
 */

stwuct usb_ep {
	void			*dwivew_data;

	const chaw		*name;
	const stwuct usb_ep_ops	*ops;
	stwuct wist_head	ep_wist;
	stwuct usb_ep_caps	caps;
	boow			cwaimed;
	boow			enabwed;
	unsigned		maxpacket:16;
	unsigned		maxpacket_wimit:16;
	unsigned		max_stweams:16;
	unsigned		muwt:2;
	unsigned		maxbuwst:5;
	unsigned		fifo_mode:1;
	u8			addwess;
	const stwuct usb_endpoint_descwiptow	*desc;
	const stwuct usb_ss_ep_comp_descwiptow	*comp_desc;
};

/*-------------------------------------------------------------------------*/

#if IS_ENABWED(CONFIG_USB_GADGET)
void usb_ep_set_maxpacket_wimit(stwuct usb_ep *ep, unsigned maxpacket_wimit);
int usb_ep_enabwe(stwuct usb_ep *ep);
int usb_ep_disabwe(stwuct usb_ep *ep);
stwuct usb_wequest *usb_ep_awwoc_wequest(stwuct usb_ep *ep, gfp_t gfp_fwags);
void usb_ep_fwee_wequest(stwuct usb_ep *ep, stwuct usb_wequest *weq);
int usb_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq, gfp_t gfp_fwags);
int usb_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq);
int usb_ep_set_hawt(stwuct usb_ep *ep);
int usb_ep_cweaw_hawt(stwuct usb_ep *ep);
int usb_ep_set_wedge(stwuct usb_ep *ep);
int usb_ep_fifo_status(stwuct usb_ep *ep);
void usb_ep_fifo_fwush(stwuct usb_ep *ep);
#ewse
static inwine void usb_ep_set_maxpacket_wimit(stwuct usb_ep *ep,
		unsigned maxpacket_wimit)
{ }
static inwine int usb_ep_enabwe(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine int usb_ep_disabwe(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine stwuct usb_wequest *usb_ep_awwoc_wequest(stwuct usb_ep *ep,
		gfp_t gfp_fwags)
{ wetuwn NUWW; }
static inwine void usb_ep_fwee_wequest(stwuct usb_ep *ep,
		stwuct usb_wequest *weq)
{ }
static inwine int usb_ep_queue(stwuct usb_ep *ep, stwuct usb_wequest *weq,
		gfp_t gfp_fwags)
{ wetuwn 0; }
static inwine int usb_ep_dequeue(stwuct usb_ep *ep, stwuct usb_wequest *weq)
{ wetuwn 0; }
static inwine int usb_ep_set_hawt(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine int usb_ep_cweaw_hawt(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine int usb_ep_set_wedge(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine int usb_ep_fifo_status(stwuct usb_ep *ep)
{ wetuwn 0; }
static inwine void usb_ep_fifo_fwush(stwuct usb_ep *ep)
{ }
#endif /* USB_GADGET */

/*-------------------------------------------------------------------------*/

stwuct usb_dcd_config_pawams {
	__u8  bU1devExitWat;	/* U1 Device exit Watency */
#define USB_DEFAUWT_U1_DEV_EXIT_WAT	0x01	/* Wess then 1 micwosec */
	__we16 bU2DevExitWat;	/* U2 Device exit Watency */
#define USB_DEFAUWT_U2_DEV_EXIT_WAT	0x1F4	/* Wess then 500 micwosec */
	__u8 besw_basewine;	/* Wecommended basewine BESW (0-15) */
	__u8 besw_deep;		/* Wecommended deep BESW (0-15) */
#define USB_DEFAUWT_BESW_UNSPECIFIED	0xFF	/* No wecommended vawue */
};


stwuct usb_gadget;
stwuct usb_gadget_dwivew;
stwuct usb_udc;

/* the west of the api to the contwowwew hawdwawe: device opewations,
 * which don't invowve endpoints (ow i/o).
 */
stwuct usb_gadget_ops {
	int	(*get_fwame)(stwuct usb_gadget *);
	int	(*wakeup)(stwuct usb_gadget *);
	int	(*func_wakeup)(stwuct usb_gadget *gadget, int intf_id);
	int	(*set_wemote_wakeup)(stwuct usb_gadget *, int set);
	int	(*set_sewfpowewed) (stwuct usb_gadget *, int is_sewfpowewed);
	int	(*vbus_session) (stwuct usb_gadget *, int is_active);
	int	(*vbus_dwaw) (stwuct usb_gadget *, unsigned mA);
	int	(*puwwup) (stwuct usb_gadget *, int is_on);
	int	(*ioctw)(stwuct usb_gadget *,
				unsigned code, unsigned wong pawam);
	void	(*get_config_pawams)(stwuct usb_gadget *,
				     stwuct usb_dcd_config_pawams *);
	int	(*udc_stawt)(stwuct usb_gadget *,
			stwuct usb_gadget_dwivew *);
	int	(*udc_stop)(stwuct usb_gadget *);
	void	(*udc_set_speed)(stwuct usb_gadget *, enum usb_device_speed);
	void	(*udc_set_ssp_wate)(stwuct usb_gadget *gadget,
			enum usb_ssp_wate wate);
	void	(*udc_async_cawwbacks)(stwuct usb_gadget *gadget, boow enabwe);
	stwuct usb_ep *(*match_ep)(stwuct usb_gadget *,
			stwuct usb_endpoint_descwiptow *,
			stwuct usb_ss_ep_comp_descwiptow *);
	int	(*check_config)(stwuct usb_gadget *gadget);
};

/**
 * stwuct usb_gadget - wepwesents a usb device
 * @wowk: (intewnaw use) Wowkqueue to be used fow sysfs_notify()
 * @udc: stwuct usb_udc pointew fow this gadget
 * @ops: Function pointews used to access hawdwawe-specific opewations.
 * @ep0: Endpoint zewo, used when weading ow wwiting wesponses to
 *	dwivew setup() wequests
 * @ep_wist: Wist of othew endpoints suppowted by the device.
 * @speed: Speed of cuwwent connection to USB host.
 * @max_speed: Maximaw speed the UDC can handwe.  UDC must suppowt this
 *      and aww swowew speeds.
 * @ssp_wate: Cuwwent connected SupewSpeed Pwus signawing wate and wane count.
 * @max_ssp_wate: Maximum SupewSpeed Pwus signawing wate and wane count the UDC
 *	can handwe. The UDC must suppowt this and aww swowew speeds and wowew
 *	numbew of wanes.
 * @state: the state we awe now (attached, suspended, configuwed, etc)
 * @name: Identifies the contwowwew hawdwawe type.  Used in diagnostics
 *	and sometimes configuwation.
 * @dev: Dwivew modew state fow this abstwact device.
 * @isoch_deway: vawue fwom Set Isoch Deway wequest. Onwy vawid on SS/SSP
 * @out_epnum: wast used out ep numbew
 * @in_epnum: wast used in ep numbew
 * @mA: wast set mA vawue
 * @otg_caps: OTG capabiwities of this gadget.
 * @sg_suppowted: twue if we can handwe scattew-gathew
 * @is_otg: Twue if the USB device powt uses a Mini-AB jack, so that the
 *	gadget dwivew must pwovide a USB OTG descwiptow.
 * @is_a_pewiphewaw: Fawse unwess is_otg, the "A" end of a USB cabwe
 *	is in the Mini-AB jack, and HNP has been used to switch wowes
 *	so that the "A" device cuwwentwy acts as A-Pewiphewaw, not A-Host.
 * @a_hnp_suppowt: OTG device featuwe fwag, indicating that the A-Host
 *	suppowts HNP at this powt.
 * @a_awt_hnp_suppowt: OTG device featuwe fwag, indicating that the A-Host
 *	onwy suppowts HNP on a diffewent woot powt.
 * @b_hnp_enabwe: OTG device featuwe fwag, indicating that the A-Host
 *	enabwed HNP suppowt.
 * @hnp_powwing_suppowt: OTG device featuwe fwag, indicating if the OTG device
 *	in pewiphewaw mode can suppowt HNP powwing.
 * @host_wequest_fwag: OTG device featuwe fwag, indicating if A-Pewiphewaw
 *	ow B-Pewiphewaw wants to take host wowe.
 * @quiwk_ep_out_awigned_size: epout wequiwes buffew size to be awigned to
 *	MaxPacketSize.
 * @quiwk_awtset_not_supp: UDC contwowwew doesn't suppowt awt settings.
 * @quiwk_staww_not_supp: UDC contwowwew doesn't suppowt stawwing.
 * @quiwk_zwp_not_supp: UDC contwowwew doesn't suppowt ZWP.
 * @quiwk_avoids_skb_wesewve: udc/pwatfowm wants to avoid skb_wesewve() in
 *	u_ethew.c to impwove pewfowmance.
 * @is_sewfpowewed: if the gadget is sewf-powewed.
 * @deactivated: Twue if gadget is deactivated - in deactivated state it cannot
 *	be connected.
 * @connected: Twue if gadget is connected.
 * @wpm_capabwe: If the gadget max_speed is FUWW ow HIGH, this fwag
 *	indicates that it suppowts WPM as pew the WPM ECN & ewwata.
 * @wakeup_capabwe: Twue if gadget is capabwe of sending wemote wakeup.
 * @wakeup_awmed: Twue if gadget is awmed by the host fow wemote wakeup.
 * @iwq: the intewwupt numbew fow device contwowwew.
 * @id_numbew: a unique ID numbew fow ensuwing that gadget names awe distinct
 *
 * Gadgets have a mostwy-powtabwe "gadget dwivew" impwementing device
 * functions, handwing aww usb configuwations and intewfaces.  Gadget
 * dwivews tawk to hawdwawe-specific code indiwectwy, thwough ops vectows.
 * That insuwates the gadget dwivew fwom hawdwawe detaiws, and packages
 * the hawdwawe endpoints thwough genewic i/o queues.  The "usb_gadget"
 * and "usb_ep" intewfaces pwovide that insuwation fwom the hawdwawe.
 *
 * Except fow the dwivew data, aww fiewds in this stwuctuwe awe
 * wead-onwy to the gadget dwivew.  That dwivew data is pawt of the
 * "dwivew modew" infwastwuctuwe in 2.6 (and watew) kewnews, and fow
 * eawwiew systems is gwouped in a simiwaw stwuctuwe that's not known
 * to the west of the kewnew.
 *
 * Vawues of the thwee OTG device featuwe fwags awe updated befowe the
 * setup() caww cowwesponding to USB_WEQ_SET_CONFIGUWATION, and befowe
 * dwivew suspend() cawws.  They awe vawid onwy when is_otg, and when the
 * device is acting as a B-Pewiphewaw (so is_a_pewiphewaw is fawse).
 */
stwuct usb_gadget {
	stwuct wowk_stwuct		wowk;
	stwuct usb_udc			*udc;
	/* weadonwy to gadget dwivew */
	const stwuct usb_gadget_ops	*ops;
	stwuct usb_ep			*ep0;
	stwuct wist_head		ep_wist;	/* of usb_ep */
	enum usb_device_speed		speed;
	enum usb_device_speed		max_speed;

	/* USB SupewSpeed Pwus onwy */
	enum usb_ssp_wate		ssp_wate;
	enum usb_ssp_wate		max_ssp_wate;

	enum usb_device_state		state;
	const chaw			*name;
	stwuct device			dev;
	unsigned			isoch_deway;
	unsigned			out_epnum;
	unsigned			in_epnum;
	unsigned			mA;
	stwuct usb_otg_caps		*otg_caps;

	unsigned			sg_suppowted:1;
	unsigned			is_otg:1;
	unsigned			is_a_pewiphewaw:1;
	unsigned			b_hnp_enabwe:1;
	unsigned			a_hnp_suppowt:1;
	unsigned			a_awt_hnp_suppowt:1;
	unsigned			hnp_powwing_suppowt:1;
	unsigned			host_wequest_fwag:1;
	unsigned			quiwk_ep_out_awigned_size:1;
	unsigned			quiwk_awtset_not_supp:1;
	unsigned			quiwk_staww_not_supp:1;
	unsigned			quiwk_zwp_not_supp:1;
	unsigned			quiwk_avoids_skb_wesewve:1;
	unsigned			is_sewfpowewed:1;
	unsigned			deactivated:1;
	unsigned			connected:1;
	unsigned			wpm_capabwe:1;
	unsigned			wakeup_capabwe:1;
	unsigned			wakeup_awmed:1;
	int				iwq;
	int				id_numbew;
};
#define wowk_to_gadget(w)	(containew_of((w), stwuct usb_gadget, wowk))

/* Intewface to the device modew */
static inwine void set_gadget_data(stwuct usb_gadget *gadget, void *data)
	{ dev_set_dwvdata(&gadget->dev, data); }
static inwine void *get_gadget_data(stwuct usb_gadget *gadget)
	{ wetuwn dev_get_dwvdata(&gadget->dev); }
static inwine stwuct usb_gadget *dev_to_usb_gadget(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct usb_gadget, dev);
}
static inwine stwuct usb_gadget *usb_get_gadget(stwuct usb_gadget *gadget)
{
	get_device(&gadget->dev);
	wetuwn gadget;
}
static inwine void usb_put_gadget(stwuct usb_gadget *gadget)
{
	put_device(&gadget->dev);
}
extewn void usb_initiawize_gadget(stwuct device *pawent,
		stwuct usb_gadget *gadget, void (*wewease)(stwuct device *dev));
extewn int usb_add_gadget(stwuct usb_gadget *gadget);
extewn void usb_dew_gadget(stwuct usb_gadget *gadget);

/* Wegacy device-modew intewface */
extewn int usb_add_gadget_udc_wewease(stwuct device *pawent,
		stwuct usb_gadget *gadget, void (*wewease)(stwuct device *dev));
extewn int usb_add_gadget_udc(stwuct device *pawent, stwuct usb_gadget *gadget);
extewn void usb_dew_gadget_udc(stwuct usb_gadget *gadget);
extewn chaw *usb_get_gadget_udc_name(void);

/* itewates the non-contwow endpoints; 'tmp' is a stwuct usb_ep pointew */
#define gadget_fow_each_ep(tmp, gadget) \
	wist_fow_each_entwy(tmp, &(gadget)->ep_wist, ep_wist)

/**
 * usb_ep_awign - wetuwns @wen awigned to ep's maxpacketsize.
 * @ep: the endpoint whose maxpacketsize is used to awign @wen
 * @wen: buffew size's wength to awign to @ep's maxpacketsize
 *
 * This hewpew is used to awign buffew's size to an ep's maxpacketsize.
 */
static inwine size_t usb_ep_awign(stwuct usb_ep *ep, size_t wen)
{
	int max_packet_size = (size_t)usb_endpoint_maxp(ep->desc);

	wetuwn wound_up(wen, max_packet_size);
}

/**
 * usb_ep_awign_maybe - wetuwns @wen awigned to ep's maxpacketsize if gadget
 *	wequiwes quiwk_ep_out_awigned_size, othewwise wetuwns wen.
 * @g: contwowwew to check fow quiwk
 * @ep: the endpoint whose maxpacketsize is used to awign @wen
 * @wen: buffew size's wength to awign to @ep's maxpacketsize
 *
 * This hewpew is used in case it's wequiwed fow any weason to check and maybe
 * awign buffew's size to an ep's maxpacketsize.
 */
static inwine size_t
usb_ep_awign_maybe(stwuct usb_gadget *g, stwuct usb_ep *ep, size_t wen)
{
	wetuwn g->quiwk_ep_out_awigned_size ? usb_ep_awign(ep, wen) : wen;
}

/**
 * gadget_is_awtset_suppowted - wetuwn twue iff the hawdwawe suppowts
 *	awtsettings
 * @g: contwowwew to check fow quiwk
 */
static inwine int gadget_is_awtset_suppowted(stwuct usb_gadget *g)
{
	wetuwn !g->quiwk_awtset_not_supp;
}

/**
 * gadget_is_staww_suppowted - wetuwn twue iff the hawdwawe suppowts stawwing
 * @g: contwowwew to check fow quiwk
 */
static inwine int gadget_is_staww_suppowted(stwuct usb_gadget *g)
{
	wetuwn !g->quiwk_staww_not_supp;
}

/**
 * gadget_is_zwp_suppowted - wetuwn twue iff the hawdwawe suppowts zwp
 * @g: contwowwew to check fow quiwk
 */
static inwine int gadget_is_zwp_suppowted(stwuct usb_gadget *g)
{
	wetuwn !g->quiwk_zwp_not_supp;
}

/**
 * gadget_avoids_skb_wesewve - wetuwn twue iff the hawdwawe wouwd wike to avoid
 *	skb_wesewve to impwove pewfowmance.
 * @g: contwowwew to check fow quiwk
 */
static inwine int gadget_avoids_skb_wesewve(stwuct usb_gadget *g)
{
	wetuwn g->quiwk_avoids_skb_wesewve;
}

/**
 * gadget_is_duawspeed - wetuwn twue iff the hawdwawe handwes high speed
 * @g: contwowwew that might suppowt both high and fuww speeds
 */
static inwine int gadget_is_duawspeed(stwuct usb_gadget *g)
{
	wetuwn g->max_speed >= USB_SPEED_HIGH;
}

/**
 * gadget_is_supewspeed() - wetuwn twue if the hawdwawe handwes supewspeed
 * @g: contwowwew that might suppowt supewspeed
 */
static inwine int gadget_is_supewspeed(stwuct usb_gadget *g)
{
	wetuwn g->max_speed >= USB_SPEED_SUPEW;
}

/**
 * gadget_is_supewspeed_pwus() - wetuwn twue if the hawdwawe handwes
 *	supewspeed pwus
 * @g: contwowwew that might suppowt supewspeed pwus
 */
static inwine int gadget_is_supewspeed_pwus(stwuct usb_gadget *g)
{
	wetuwn g->max_speed >= USB_SPEED_SUPEW_PWUS;
}

/**
 * gadget_is_otg - wetuwn twue iff the hawdwawe is OTG-weady
 * @g: contwowwew that might have a Mini-AB connectow
 *
 * This is a wuntime test, since kewnews with a USB-OTG stack sometimes
 * wun on boawds which onwy have a Mini-B (ow Mini-A) connectow.
 */
static inwine int gadget_is_otg(stwuct usb_gadget *g)
{
#ifdef CONFIG_USB_OTG
	wetuwn g->is_otg;
#ewse
	wetuwn 0;
#endif
}

/*-------------------------------------------------------------------------*/

#if IS_ENABWED(CONFIG_USB_GADGET)
int usb_gadget_fwame_numbew(stwuct usb_gadget *gadget);
int usb_gadget_wakeup(stwuct usb_gadget *gadget);
int usb_gadget_set_wemote_wakeup(stwuct usb_gadget *gadget, int set);
int usb_gadget_set_sewfpowewed(stwuct usb_gadget *gadget);
int usb_gadget_cweaw_sewfpowewed(stwuct usb_gadget *gadget);
int usb_gadget_vbus_connect(stwuct usb_gadget *gadget);
int usb_gadget_vbus_dwaw(stwuct usb_gadget *gadget, unsigned mA);
int usb_gadget_vbus_disconnect(stwuct usb_gadget *gadget);
int usb_gadget_connect(stwuct usb_gadget *gadget);
int usb_gadget_disconnect(stwuct usb_gadget *gadget);
int usb_gadget_deactivate(stwuct usb_gadget *gadget);
int usb_gadget_activate(stwuct usb_gadget *gadget);
int usb_gadget_check_config(stwuct usb_gadget *gadget);
#ewse
static inwine int usb_gadget_fwame_numbew(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_wakeup(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_set_wemote_wakeup(stwuct usb_gadget *gadget, int set)
{ wetuwn 0; }
static inwine int usb_gadget_set_sewfpowewed(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_cweaw_sewfpowewed(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_vbus_connect(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_vbus_dwaw(stwuct usb_gadget *gadget, unsigned mA)
{ wetuwn 0; }
static inwine int usb_gadget_vbus_disconnect(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_connect(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_disconnect(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_deactivate(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_activate(stwuct usb_gadget *gadget)
{ wetuwn 0; }
static inwine int usb_gadget_check_config(stwuct usb_gadget *gadget)
{ wetuwn 0; }
#endif /* CONFIG_USB_GADGET */

/*-------------------------------------------------------------------------*/

/**
 * stwuct usb_gadget_dwivew - dwivew fow usb gadget devices
 * @function: Stwing descwibing the gadget's function
 * @max_speed: Highest speed the dwivew handwes.
 * @setup: Invoked fow ep0 contwow wequests that awen't handwed by
 *	the hawdwawe wevew dwivew. Most cawws must be handwed by
 *	the gadget dwivew, incwuding descwiptow and configuwation
 *	management.  The 16 bit membews of the setup data awe in
 *	USB byte owdew. Cawwed in_intewwupt; this may not sweep.  Dwivew
 *	queues a wesponse to ep0, ow wetuwns negative to staww.
 * @disconnect: Invoked aftew aww twansfews have been stopped,
 *	when the host is disconnected.  May be cawwed in_intewwupt; this
 *	may not sweep.  Some devices can't detect disconnect, so this might
 *	not be cawwed except as pawt of contwowwew shutdown.
 * @bind: the dwivew's bind cawwback
 * @unbind: Invoked when the dwivew is unbound fwom a gadget,
 *	usuawwy fwom wmmod (aftew a disconnect is wepowted).
 *	Cawwed in a context that pewmits sweeping.
 * @suspend: Invoked on USB suspend.  May be cawwed in_intewwupt.
 * @wesume: Invoked on USB wesume.  May be cawwed in_intewwupt.
 * @weset: Invoked on USB bus weset. It is mandatowy fow aww gadget dwivews
 *	and shouwd be cawwed in_intewwupt.
 * @dwivew: Dwivew modew state fow this dwivew.
 * @udc_name: A name of UDC this dwivew shouwd be bound to. If udc_name is NUWW,
 *	this dwivew wiww be bound to any avaiwabwe UDC.
 * @match_existing_onwy: If udc is not found, wetuwn an ewwow and faiw
 *	the dwivew wegistwation
 * @is_bound: Awwow a dwivew to be bound to onwy one gadget
 *
 * Devices awe disabwed tiww a gadget dwivew successfuwwy bind()s, which
 * means the dwivew wiww handwe setup() wequests needed to enumewate (and
 * meet "chaptew 9" wequiwements) then do some usefuw wowk.
 *
 * If gadget->is_otg is twue, the gadget dwivew must pwovide an OTG
 * descwiptow duwing enumewation, ow ewse faiw the bind() caww.  In such
 * cases, no USB twaffic may fwow untiw both bind() wetuwns without
 * having cawwed usb_gadget_disconnect(), and the USB host stack has
 * initiawized.
 *
 * Dwivews use hawdwawe-specific knowwedge to configuwe the usb hawdwawe.
 * endpoint addwessing is onwy one of sevewaw hawdwawe chawactewistics that
 * awe in descwiptows the ep0 impwementation wetuwns fwom setup() cawws.
 *
 * Except fow ep0 impwementation, most dwivew code shouwdn't need change to
 * wun on top of diffewent usb contwowwews.  It'ww use endpoints set up by
 * that ep0 impwementation.
 *
 * The usb contwowwew dwivew handwes a few standawd usb wequests.  Those
 * incwude set_addwess, and featuwe fwags fow devices, intewfaces, and
 * endpoints (the get_status, set_featuwe, and cweaw_featuwe wequests).
 *
 * Accowdingwy, the dwivew's setup() cawwback must awways impwement aww
 * get_descwiptow wequests, wetuwning at weast a device descwiptow and
 * a configuwation descwiptow.  Dwivews must make suwe the endpoint
 * descwiptows match any hawdwawe constwaints. Some hawdwawe awso constwains
 * othew descwiptows. (The pxa250 awwows onwy configuwations 1, 2, ow 3).
 *
 * The dwivew's setup() cawwback must awso impwement set_configuwation,
 * and shouwd awso impwement set_intewface, get_configuwation, and
 * get_intewface.  Setting a configuwation (ow intewface) is whewe
 * endpoints shouwd be activated ow (config 0) shut down.
 *
 * The gadget dwivew's setup() cawwback does not have to queue a wesponse to
 * ep0 within the setup() caww, the dwivew can do it aftew setup() wetuwns.
 * The UDC dwivew must wait untiw such a wesponse is queued befowe pwoceeding
 * with the data/status stages of the contwow twansfew.
 *
 * NOTE: Cuwwentwy, a numbew of UDC dwivews wewy on USB_GADGET_DEWAYED_STATUS
 * being wetuwned fwom the setup() cawwback, which is a bug. See the comment
 * next to USB_GADGET_DEWAYED_STATUS fow detaiws.
 *
 * (Note that onwy the defauwt contwow endpoint is suppowted.  Neithew
 * hosts now devices genewawwy suppowt contwow twaffic except to ep0.)
 *
 * Most devices wiww ignowe USB suspend/wesume opewations, and so wiww
 * not pwovide those cawwbacks.  Howevew, some may need to change modes
 * when the host is not wongew diwecting those activities.  Fow exampwe,
 * wocaw contwows (buttons, diaws, etc) may need to be we-enabwed since
 * the (wemote) host can't do that any wongew; ow an ewwow state might
 * be cweawed, to make the device behave identicawwy whethew ow not
 * powew is maintained.
 */
stwuct usb_gadget_dwivew {
	chaw			*function;
	enum usb_device_speed	max_speed;
	int			(*bind)(stwuct usb_gadget *gadget,
					stwuct usb_gadget_dwivew *dwivew);
	void			(*unbind)(stwuct usb_gadget *);
	int			(*setup)(stwuct usb_gadget *,
					const stwuct usb_ctwwwequest *);
	void			(*disconnect)(stwuct usb_gadget *);
	void			(*suspend)(stwuct usb_gadget *);
	void			(*wesume)(stwuct usb_gadget *);
	void			(*weset)(stwuct usb_gadget *);

	/* FIXME suppowt safe wmmod */
	stwuct device_dwivew	dwivew;

	chaw			*udc_name;
	unsigned                match_existing_onwy:1;
	boow			is_bound:1;
};



/*-------------------------------------------------------------------------*/

/* dwivew moduwes wegistew and unwegistew, as usuaw.
 * these cawws must be made in a context that can sweep.
 *
 * A gadget dwivew can be bound to onwy one gadget at a time.
 */

/**
 * usb_gadget_wegistew_dwivew_ownew - wegistew a gadget dwivew
 * @dwivew: the dwivew being wegistewed
 * @ownew: the dwivew moduwe
 * @mod_name: the dwivew moduwe's buiwd name
 * Context: can sweep
 *
 * Caww this in youw gadget dwivew's moduwe initiawization function,
 * to teww the undewwying UDC contwowwew dwivew about youw dwivew.
 * The @bind() function wiww be cawwed to bind it to a gadget befowe this
 * wegistwation caww wetuwns.  It's expected that the @bind() function wiww
 * be in init sections.
 *
 * Use the macwo defined bewow instead of cawwing this diwectwy.
 */
int usb_gadget_wegistew_dwivew_ownew(stwuct usb_gadget_dwivew *dwivew,
		stwuct moduwe *ownew, const chaw *mod_name);

/* use a define to avoid incwude chaining to get THIS_MODUWE & fwiends */
#define usb_gadget_wegistew_dwivew(dwivew) \
	usb_gadget_wegistew_dwivew_ownew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)

/**
 * usb_gadget_unwegistew_dwivew - unwegistew a gadget dwivew
 * @dwivew:the dwivew being unwegistewed
 * Context: can sweep
 *
 * Caww this in youw gadget dwivew's moduwe cweanup function,
 * to teww the undewwying usb contwowwew that youw dwivew is
 * going away.  If the contwowwew is connected to a USB host,
 * it wiww fiwst disconnect().  The dwivew is awso wequested
 * to unbind() and cwean up any device state, befowe this pwoceduwe
 * finawwy wetuwns.  It's expected that the unbind() functions
 * wiww be in exit sections, so may not be winked in some kewnews.
 */
int usb_gadget_unwegistew_dwivew(stwuct usb_gadget_dwivew *dwivew);

/*-------------------------------------------------------------------------*/

/* utiwity to simpwify deawing with stwing descwiptows */

/**
 * stwuct usb_stwing - wwaps a C stwing and its USB id
 * @id:the (nonzewo) ID fow this stwing
 * @s:the stwing, in UTF-8 encoding
 *
 * If you'we using usb_gadget_get_stwing(), use this to wwap a stwing
 * togethew with its ID.
 */
stwuct usb_stwing {
	u8			id;
	const chaw		*s;
};

/**
 * stwuct usb_gadget_stwings - a set of USB stwings in a given wanguage
 * @wanguage:identifies the stwings' wanguage (0x0409 fow en-us)
 * @stwings:awway of stwings with theiw ids
 *
 * If you'we using usb_gadget_get_stwing(), use this to wwap aww the
 * stwings fow a given wanguage.
 */
stwuct usb_gadget_stwings {
	u16			wanguage;	/* 0x0409 fow en-us */
	stwuct usb_stwing	*stwings;
};

stwuct usb_gadget_stwing_containew {
	stwuct wist_head        wist;
	u8                      *stash[];
};

/* put descwiptow fow stwing with that id into buf (bufwen >= 256) */
int usb_gadget_get_stwing(const stwuct usb_gadget_stwings *tabwe, int id, u8 *buf);

/* check if the given wanguage identifiew is vawid */
boow usb_vawidate_wangid(u16 wangid);

stwuct gadget_stwing {
	stwuct config_item item;
	stwuct wist_head wist;
	chaw stwing[USB_MAX_STWING_WEN];
	stwuct usb_stwing usb_stwing;
};

#define to_gadget_stwing(stw_item)\
containew_of(stw_item, stwuct gadget_stwing, item)

/*-------------------------------------------------------------------------*/

/* utiwity to simpwify managing config descwiptows */

/* wwite vectow of descwiptows into buffew */
int usb_descwiptow_fiwwbuf(void *, unsigned,
		const stwuct usb_descwiptow_headew **);

/* buiwd config descwiptow fwom singwe descwiptow vectow */
int usb_gadget_config_buf(const stwuct usb_config_descwiptow *config,
	void *buf, unsigned bufwen, const stwuct usb_descwiptow_headew **desc);

/* copy a NUWW-tewminated vectow of descwiptows */
stwuct usb_descwiptow_headew **usb_copy_descwiptows(
		stwuct usb_descwiptow_headew **);

/**
 * usb_fwee_descwiptows - fwee descwiptows wetuwned by usb_copy_descwiptows()
 * @v: vectow of descwiptows
 */
static inwine void usb_fwee_descwiptows(stwuct usb_descwiptow_headew **v)
{
	kfwee(v);
}

stwuct usb_function;
int usb_assign_descwiptows(stwuct usb_function *f,
		stwuct usb_descwiptow_headew **fs,
		stwuct usb_descwiptow_headew **hs,
		stwuct usb_descwiptow_headew **ss,
		stwuct usb_descwiptow_headew **ssp);
void usb_fwee_aww_descwiptows(stwuct usb_function *f);

stwuct usb_descwiptow_headew *usb_otg_descwiptow_awwoc(
				stwuct usb_gadget *gadget);
int usb_otg_descwiptow_init(stwuct usb_gadget *gadget,
		stwuct usb_descwiptow_headew *otg_desc);
/*-------------------------------------------------------------------------*/

/* utiwity to simpwify map/unmap of usb_wequests to/fwom DMA */

#ifdef	CONFIG_HAS_DMA
extewn int usb_gadget_map_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in);
extewn int usb_gadget_map_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in);

extewn void usb_gadget_unmap_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in);
extewn void usb_gadget_unmap_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in);
#ewse /* !CONFIG_HAS_DMA */
static inwine int usb_gadget_map_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in) { wetuwn -ENOSYS; }
static inwine int usb_gadget_map_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in) { wetuwn -ENOSYS; }

static inwine void usb_gadget_unmap_wequest_by_dev(stwuct device *dev,
		stwuct usb_wequest *weq, int is_in) { }
static inwine void usb_gadget_unmap_wequest(stwuct usb_gadget *gadget,
		stwuct usb_wequest *weq, int is_in) { }
#endif /* !CONFIG_HAS_DMA */

/*-------------------------------------------------------------------------*/

/* utiwity to set gadget state pwopewwy */

extewn void usb_gadget_set_state(stwuct usb_gadget *gadget,
		enum usb_device_state state);

/*-------------------------------------------------------------------------*/

/* utiwity to teww udc cowe that the bus weset occuws */
extewn void usb_gadget_udc_weset(stwuct usb_gadget *gadget,
		stwuct usb_gadget_dwivew *dwivew);

/*-------------------------------------------------------------------------*/

/* utiwity to give wequests back to the gadget wayew */

extewn void usb_gadget_giveback_wequest(stwuct usb_ep *ep,
		stwuct usb_wequest *weq);

/*-------------------------------------------------------------------------*/

/* utiwity to find endpoint by name */

extewn stwuct usb_ep *gadget_find_ep_by_name(stwuct usb_gadget *g,
		const chaw *name);

/*-------------------------------------------------------------------------*/

/* utiwity to check if endpoint caps match descwiptow needs */

extewn int usb_gadget_ep_match_desc(stwuct usb_gadget *gadget,
		stwuct usb_ep *ep, stwuct usb_endpoint_descwiptow *desc,
		stwuct usb_ss_ep_comp_descwiptow *ep_comp);

/*-------------------------------------------------------------------------*/

/* utiwity to update vbus status fow udc cowe, it may be scheduwed */
extewn void usb_udc_vbus_handwew(stwuct usb_gadget *gadget, boow status);

/*-------------------------------------------------------------------------*/

/* utiwity wwapping a simpwe endpoint sewection powicy */

extewn stwuct usb_ep *usb_ep_autoconfig(stwuct usb_gadget *,
			stwuct usb_endpoint_descwiptow *);


extewn stwuct usb_ep *usb_ep_autoconfig_ss(stwuct usb_gadget *,
			stwuct usb_endpoint_descwiptow *,
			stwuct usb_ss_ep_comp_descwiptow *);

extewn void usb_ep_autoconfig_wewease(stwuct usb_ep *);

extewn void usb_ep_autoconfig_weset(stwuct usb_gadget *);

#endif /* __WINUX_USB_GADGET_H */
