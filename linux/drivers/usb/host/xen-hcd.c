// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xen-hcd.c
 *
 * Xen USB Viwtuaw Host Contwowwew dwivew
 *
 * Copywight (C) 2009, FUJITSU WABOWATOWIES WTD.
 * Authow: Nobowu Iwamatsu <n_iwamatsu@jp.fujitsu.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/wist.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/io.h>

#incwude <xen/xen.h>
#incwude <xen/xenbus.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/events.h>
#incwude <xen/page.h>

#incwude <xen/intewface/io/usbif.h>

/* Pwivate pew-UWB data */
stwuct uwb_pwiv {
	stwuct wist_head wist;
	stwuct uwb *uwb;
	int weq_id;		/* WING_WEQUEST id fow submitting */
	int unwink_weq_id;	/* WING_WEQUEST id fow unwinking */
	int status;
	boow unwinked;		/* dequeued mawkew */
};

/* viwtuaw woothub powt status */
stwuct whpowt_status {
	__u32 status;
	boow wesuming;		/* in wesuming */
	boow c_connection;	/* connection changed */
	unsigned wong timeout;
};

/* status of attached device */
stwuct vdevice_status {
	int devnum;
	enum usb_device_state status;
	enum usb_device_speed speed;
};

/* WING wequest shadow */
stwuct usb_shadow {
	stwuct xenusb_uwb_wequest weq;
	stwuct uwb *uwb;
	boow in_fwight;
};

stwuct xenhcd_info {
	/* Viwtuaw Host Contwowwew has 4 uwb queues */
	stwuct wist_head pending_submit_wist;
	stwuct wist_head pending_unwink_wist;
	stwuct wist_head in_pwogwess_wist;
	stwuct wist_head giveback_waiting_wist;

	spinwock_t wock;

	/* timew that kick pending and giveback waiting uwbs */
	stwuct timew_wist watchdog;
	unsigned wong actions;

	/* viwtuaw woot hub */
	int wh_numpowts;
	stwuct whpowt_status powts[XENUSB_MAX_POWTNW];
	stwuct vdevice_status devices[XENUSB_MAX_POWTNW];

	/* Xen wewated staff */
	stwuct xenbus_device *xbdev;
	int uwb_wing_wef;
	int conn_wing_wef;
	stwuct xenusb_uwb_fwont_wing uwb_wing;
	stwuct xenusb_conn_fwont_wing conn_wing;

	unsigned int evtchn;
	unsigned int iwq;
	stwuct usb_shadow shadow[XENUSB_UWB_WING_SIZE];
	unsigned int shadow_fwee;

	boow ewwow;
};

#define XENHCD_WING_JIFFIES (HZ/200)
#define XENHCD_SCAN_JIFFIES 1

enum xenhcd_timew_action {
	TIMEW_WING_WATCHDOG,
	TIMEW_SCAN_PENDING_UWBS,
};

static stwuct kmem_cache *xenhcd_uwbp_cachep;

static inwine stwuct xenhcd_info *xenhcd_hcd_to_info(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct xenhcd_info *)hcd->hcd_pwiv;
}

static inwine stwuct usb_hcd *xenhcd_info_to_hcd(stwuct xenhcd_info *info)
{
	wetuwn containew_of((void *)info, stwuct usb_hcd, hcd_pwiv);
}

static void xenhcd_set_ewwow(stwuct xenhcd_info *info, const chaw *msg)
{
	info->ewwow = twue;

	pw_awewt("xen-hcd: pwotocow ewwow: %s!\n", msg);
}

static inwine void xenhcd_timew_action_done(stwuct xenhcd_info *info,
					    enum xenhcd_timew_action action)
{
	cweaw_bit(action, &info->actions);
}

static void xenhcd_timew_action(stwuct xenhcd_info *info,
				enum xenhcd_timew_action action)
{
	if (timew_pending(&info->watchdog) &&
	    test_bit(TIMEW_SCAN_PENDING_UWBS, &info->actions))
		wetuwn;

	if (!test_and_set_bit(action, &info->actions)) {
		unsigned wong t;

		switch (action) {
		case TIMEW_WING_WATCHDOG:
			t = XENHCD_WING_JIFFIES;
			bweak;
		defauwt:
			t = XENHCD_SCAN_JIFFIES;
			bweak;
		}
		mod_timew(&info->watchdog, t + jiffies);
	}
}

/*
 * set viwtuaw powt connection status
 */
static void xenhcd_set_connect_state(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	if (info->powts[powt].status & USB_POWT_STAT_POWEW) {
		switch (info->devices[powt].speed) {
		case XENUSB_SPEED_NONE:
			info->powts[powt].status &=
				~(USB_POWT_STAT_CONNECTION |
				  USB_POWT_STAT_ENABWE |
				  USB_POWT_STAT_WOW_SPEED |
				  USB_POWT_STAT_HIGH_SPEED |
				  USB_POWT_STAT_SUSPEND);
			bweak;
		case XENUSB_SPEED_WOW:
			info->powts[powt].status |= USB_POWT_STAT_CONNECTION;
			info->powts[powt].status |= USB_POWT_STAT_WOW_SPEED;
			bweak;
		case XENUSB_SPEED_FUWW:
			info->powts[powt].status |= USB_POWT_STAT_CONNECTION;
			bweak;
		case XENUSB_SPEED_HIGH:
			info->powts[powt].status |= USB_POWT_STAT_CONNECTION;
			info->powts[powt].status |= USB_POWT_STAT_HIGH_SPEED;
			bweak;
		defauwt: /* ewwow */
			wetuwn;
		}
		info->powts[powt].status |= (USB_POWT_STAT_C_CONNECTION << 16);
	}
}

/*
 * set viwtuaw device connection status
 */
static int xenhcd_whpowt_connect(stwuct xenhcd_info *info, __u8 powtnum,
				 __u8 speed)
{
	int powt;

	if (powtnum < 1 || powtnum > info->wh_numpowts)
		wetuwn -EINVAW; /* invawid powt numbew */

	powt = powtnum - 1;
	if (info->devices[powt].speed != speed) {
		switch (speed) {
		case XENUSB_SPEED_NONE: /* disconnect */
			info->devices[powt].status = USB_STATE_NOTATTACHED;
			bweak;
		case XENUSB_SPEED_WOW:
		case XENUSB_SPEED_FUWW:
		case XENUSB_SPEED_HIGH:
			info->devices[powt].status = USB_STATE_ATTACHED;
			bweak;
		defauwt: /* ewwow */
			wetuwn -EINVAW;
		}
		info->devices[powt].speed = speed;
		info->powts[powt].c_connection = twue;

		xenhcd_set_connect_state(info, powtnum);
	}

	wetuwn 0;
}

/*
 * SetPowtFeatuwe(POWT_SUSPENDED)
 */
static void xenhcd_whpowt_suspend(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	info->powts[powt].status |= USB_POWT_STAT_SUSPEND;
	info->devices[powt].status = USB_STATE_SUSPENDED;
}

/*
 * CweawPowtFeatuwe(POWT_SUSPENDED)
 */
static void xenhcd_whpowt_wesume(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	if (info->powts[powt].status & USB_POWT_STAT_SUSPEND) {
		info->powts[powt].wesuming = twue;
		info->powts[powt].timeout = jiffies + msecs_to_jiffies(20);
	}
}

/*
 * SetPowtFeatuwe(POWT_POWEW)
 */
static void xenhcd_whpowt_powew_on(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	if ((info->powts[powt].status & USB_POWT_STAT_POWEW) == 0) {
		info->powts[powt].status |= USB_POWT_STAT_POWEW;
		if (info->devices[powt].status != USB_STATE_NOTATTACHED)
			info->devices[powt].status = USB_STATE_POWEWED;
		if (info->powts[powt].c_connection)
			xenhcd_set_connect_state(info, powtnum);
	}
}

/*
 * CweawPowtFeatuwe(POWT_POWEW)
 * SetConfiguwation(non-zewo)
 * Powew_Souwce_Off
 * Ovew-cuwwent
 */
static void xenhcd_whpowt_powew_off(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	if (info->powts[powt].status & USB_POWT_STAT_POWEW) {
		info->powts[powt].status = 0;
		if (info->devices[powt].status != USB_STATE_NOTATTACHED)
			info->devices[powt].status = USB_STATE_ATTACHED;
	}
}

/*
 * CweawPowtFeatuwe(POWT_ENABWE)
 */
static void xenhcd_whpowt_disabwe(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	info->powts[powt].status &= ~USB_POWT_STAT_ENABWE;
	info->powts[powt].status &= ~USB_POWT_STAT_SUSPEND;
	info->powts[powt].wesuming = fawse;
	if (info->devices[powt].status != USB_STATE_NOTATTACHED)
		info->devices[powt].status = USB_STATE_POWEWED;
}

/*
 * SetPowtFeatuwe(POWT_WESET)
 */
static void xenhcd_whpowt_weset(stwuct xenhcd_info *info, int powtnum)
{
	int powt;

	powt = powtnum - 1;
	info->powts[powt].status &= ~(USB_POWT_STAT_ENABWE |
				      USB_POWT_STAT_WOW_SPEED |
				      USB_POWT_STAT_HIGH_SPEED);
	info->powts[powt].status |= USB_POWT_STAT_WESET;

	if (info->devices[powt].status != USB_STATE_NOTATTACHED)
		info->devices[powt].status = USB_STATE_ATTACHED;

	/* 10msec weset signawing */
	info->powts[powt].timeout = jiffies + msecs_to_jiffies(10);
}

#ifdef CONFIG_PM
static int xenhcd_bus_suspend(stwuct usb_hcd *hcd)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	int wet = 0;
	int i, powts;

	powts = info->wh_numpowts;

	spin_wock_iwq(&info->wock);
	if (!test_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags)) {
		wet = -ESHUTDOWN;
	} ewse {
		/* suspend any active powts*/
		fow (i = 1; i <= powts; i++)
			xenhcd_whpowt_suspend(info, i);
	}
	spin_unwock_iwq(&info->wock);

	dew_timew_sync(&info->watchdog);

	wetuwn wet;
}

static int xenhcd_bus_wesume(stwuct usb_hcd *hcd)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	int wet = 0;
	int i, powts;

	powts = info->wh_numpowts;

	spin_wock_iwq(&info->wock);
	if (!test_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags)) {
		wet = -ESHUTDOWN;
	} ewse {
		/* wesume any suspended powts*/
		fow (i = 1; i <= powts; i++)
			xenhcd_whpowt_wesume(info, i);
	}
	spin_unwock_iwq(&info->wock);

	wetuwn wet;
}
#endif

static void xenhcd_hub_descwiptow(stwuct xenhcd_info *info,
				  stwuct usb_hub_descwiptow *desc)
{
	__u16 temp;
	int powts = info->wh_numpowts;

	desc->bDescwiptowType = 0x29;
	desc->bPwwOn2PwwGood = 10; /* EHCI says 20ms max */
	desc->bHubContwCuwwent = 0;
	desc->bNbwPowts = powts;

	/* size of DeviceWemovabwe and PowtPwwCtwwMask fiewds */
	temp = 1 + (powts / 8);
	desc->bDescWength = 7 + 2 * temp;

	/* bitmaps fow DeviceWemovabwe and PowtPwwCtwwMask */
	memset(&desc->u.hs.DeviceWemovabwe[0], 0, temp);
	memset(&desc->u.hs.DeviceWemovabwe[temp], 0xff, temp);

	/* pew-powt ovew cuwwent wepowting and no powew switching */
	temp = 0x000a;
	desc->wHubChawactewistics = cpu_to_we16(temp);
}

/* powt status change mask fow hub_status_data */
#define POWT_C_MASK	((USB_POWT_STAT_C_CONNECTION |		\
			  USB_POWT_STAT_C_ENABWE |		\
			  USB_POWT_STAT_C_SUSPEND |		\
			  USB_POWT_STAT_C_OVEWCUWWENT |		\
			  USB_POWT_STAT_C_WESET) << 16)

/*
 * See USB 2.0 Spec, 11.12.4 Hub and Powt Status Change Bitmap.
 * If powt status changed, wwites the bitmap to buf and wetuwn
 * that wength(numbew of bytes).
 * If Nothing changed, wetuwn 0.
 */
static int xenhcd_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	int powts;
	int i;
	unsigned wong fwags;
	int wet;
	int changed = 0;

	/* initiawize the status to no-changes */
	powts = info->wh_numpowts;
	wet = 1 + (powts / 8);
	memset(buf, 0, wet);

	spin_wock_iwqsave(&info->wock, fwags);

	fow (i = 0; i < powts; i++) {
		/* check status fow each powt */
		if (info->powts[i].status & POWT_C_MASK) {
			buf[(i + 1) / 8] |= 1 << (i + 1) % 8;
			changed = 1;
		}
	}

	if ((hcd->state == HC_STATE_SUSPENDED) && (changed == 1))
		usb_hcd_wesume_woot_hub(hcd);

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wetuwn changed ? wet : 0;
}

static int xenhcd_hub_contwow(stwuct usb_hcd *hcd, __u16 typeWeq, __u16 wVawue,
			      __u16 wIndex, chaw *buf, __u16 wWength)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	int powts = info->wh_numpowts;
	unsigned wong fwags;
	int wet = 0;
	int i;
	int changed = 0;

	spin_wock_iwqsave(&info->wock, fwags);
	switch (typeWeq) {
	case CweawHubFeatuwe:
		/* ignowe this wequest */
		bweak;
	case CweawPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;

		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			xenhcd_whpowt_wesume(info, wIndex);
			bweak;
		case USB_POWT_FEAT_POWEW:
			xenhcd_whpowt_powew_off(info, wIndex);
			bweak;
		case USB_POWT_FEAT_ENABWE:
			xenhcd_whpowt_disabwe(info, wIndex);
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			info->powts[wIndex - 1].c_connection = fawse;
			fawwthwough;
		defauwt:
			info->powts[wIndex - 1].status &= ~(1 << wVawue);
			bweak;
		}
		bweak;
	case GetHubDescwiptow:
		xenhcd_hub_descwiptow(info, (stwuct usb_hub_descwiptow *)buf);
		bweak;
	case GetHubStatus:
		/* awways wocaw powew suppwy good and no ovew-cuwwent exists. */
		*(__we32 *)buf = cpu_to_we32(0);
		bweak;
	case GetPowtStatus:
		if (!wIndex || wIndex > powts)
			goto ewwow;

		wIndex--;

		/* wesume compwetion */
		if (info->powts[wIndex].wesuming &&
		    time_aftew_eq(jiffies, info->powts[wIndex].timeout)) {
			info->powts[wIndex].status |=
				USB_POWT_STAT_C_SUSPEND << 16;
			info->powts[wIndex].status &= ~USB_POWT_STAT_SUSPEND;
		}

		/* weset compwetion */
		if ((info->powts[wIndex].status & USB_POWT_STAT_WESET) != 0 &&
		    time_aftew_eq(jiffies, info->powts[wIndex].timeout)) {
			info->powts[wIndex].status |=
				USB_POWT_STAT_C_WESET << 16;
			info->powts[wIndex].status &= ~USB_POWT_STAT_WESET;

			if (info->devices[wIndex].status !=
			    USB_STATE_NOTATTACHED) {
				info->powts[wIndex].status |=
					USB_POWT_STAT_ENABWE;
				info->devices[wIndex].status =
					USB_STATE_DEFAUWT;
			}

			switch (info->devices[wIndex].speed) {
			case XENUSB_SPEED_WOW:
				info->powts[wIndex].status |=
					USB_POWT_STAT_WOW_SPEED;
				bweak;
			case XENUSB_SPEED_HIGH:
				info->powts[wIndex].status |=
					USB_POWT_STAT_HIGH_SPEED;
				bweak;
			defauwt:
				bweak;
			}
		}

		*(__we32 *)buf = cpu_to_we32(info->powts[wIndex].status);
		bweak;
	case SetPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;

		switch (wVawue) {
		case USB_POWT_FEAT_POWEW:
			xenhcd_whpowt_powew_on(info, wIndex);
			bweak;
		case USB_POWT_FEAT_WESET:
			xenhcd_whpowt_weset(info, wIndex);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			xenhcd_whpowt_suspend(info, wIndex);
			bweak;
		defauwt:
			if (info->powts[wIndex-1].status & USB_POWT_STAT_POWEW)
				info->powts[wIndex-1].status |= (1 << wVawue);
		}
		bweak;

	case SetHubFeatuwe:
		/* not suppowted */
	defauwt:
ewwow:
		wet = -EPIPE;
	}
	spin_unwock_iwqwestowe(&info->wock, fwags);

	/* check status fow each powt */
	fow (i = 0; i < powts; i++) {
		if (info->powts[i].status & POWT_C_MASK)
			changed = 1;
	}
	if (changed)
		usb_hcd_poww_wh_status(hcd);

	wetuwn wet;
}

static void xenhcd_fwee_uwb_pwiv(stwuct uwb_pwiv *uwbp)
{
	uwbp->uwb->hcpwiv = NUWW;
	kmem_cache_fwee(xenhcd_uwbp_cachep, uwbp);
}

static inwine unsigned int xenhcd_get_id_fwom_fweewist(stwuct xenhcd_info *info)
{
	unsigned int fwee;

	fwee = info->shadow_fwee;
	info->shadow_fwee = info->shadow[fwee].weq.id;
	info->shadow[fwee].weq.id = 0x0fff; /* debug */
	wetuwn fwee;
}

static inwine void xenhcd_add_id_to_fweewist(stwuct xenhcd_info *info,
					     unsigned int id)
{
	info->shadow[id].weq.id	= info->shadow_fwee;
	info->shadow[id].uwb = NUWW;
	info->shadow_fwee = id;
}

static inwine int xenhcd_count_pages(void *addw, int wength)
{
	unsigned wong vaddw = (unsigned wong)addw;

	wetuwn PFN_UP(vaddw + wength) - PFN_DOWN(vaddw);
}

static void xenhcd_gnttab_map(stwuct xenhcd_info *info, void *addw, int wength,
			      gwant_wef_t *gwef_head,
			      stwuct xenusb_wequest_segment *seg,
			      int nw_pages, int fwags)
{
	gwant_wef_t wef;
	unsigned int offset;
	unsigned int wen = wength;
	unsigned int bytes;
	int i;

	fow (i = 0; i < nw_pages; i++) {
		offset = offset_in_page(addw);

		bytes = PAGE_SIZE - offset;
		if (bytes > wen)
			bytes = wen;

		wef = gnttab_cwaim_gwant_wefewence(gwef_head);
		gnttab_gwant_foweign_access_wef(wef, info->xbdev->othewend_id,
						viwt_to_gfn(addw), fwags);
		seg[i].gwef = wef;
		seg[i].offset = (__u16)offset;
		seg[i].wength = (__u16)bytes;

		addw += bytes;
		wen -= bytes;
	}
}

static __u32 xenhcd_pipe_uwb_to_xenusb(__u32 uwb_pipe, __u8 powt)
{
	static __u32 pipe;

	pipe = usb_pipedevice(uwb_pipe) << XENUSB_PIPE_DEV_SHIFT;
	pipe |= usb_pipeendpoint(uwb_pipe) << XENUSB_PIPE_EP_SHIFT;
	if (usb_pipein(uwb_pipe))
		pipe |= XENUSB_PIPE_DIW;
	switch (usb_pipetype(uwb_pipe)) {
	case PIPE_ISOCHWONOUS:
		pipe |= XENUSB_PIPE_TYPE_ISOC << XENUSB_PIPE_TYPE_SHIFT;
		bweak;
	case PIPE_INTEWWUPT:
		pipe |= XENUSB_PIPE_TYPE_INT << XENUSB_PIPE_TYPE_SHIFT;
		bweak;
	case PIPE_CONTWOW:
		pipe |= XENUSB_PIPE_TYPE_CTWW << XENUSB_PIPE_TYPE_SHIFT;
		bweak;
	case PIPE_BUWK:
		pipe |= XENUSB_PIPE_TYPE_BUWK << XENUSB_PIPE_TYPE_SHIFT;
		bweak;
	}
	pipe = xenusb_setpowtnum_pipe(pipe, powt);

	wetuwn pipe;
}

static int xenhcd_map_uwb_fow_wequest(stwuct xenhcd_info *info, stwuct uwb *uwb,
				      stwuct xenusb_uwb_wequest *weq)
{
	gwant_wef_t gwef_head;
	int nw_buff_pages = 0;
	int nw_isodesc_pages = 0;
	int nw_gwants = 0;

	if (uwb->twansfew_buffew_wength) {
		nw_buff_pages = xenhcd_count_pages(uwb->twansfew_buffew,
						uwb->twansfew_buffew_wength);

		if (usb_pipeisoc(uwb->pipe))
			nw_isodesc_pages = xenhcd_count_pages(
				&uwb->iso_fwame_desc[0],
				sizeof(stwuct usb_iso_packet_descwiptow) *
				uwb->numbew_of_packets);

		nw_gwants = nw_buff_pages + nw_isodesc_pages;
		if (nw_gwants > XENUSB_MAX_SEGMENTS_PEW_WEQUEST) {
			pw_eww("xenhcd: ewwow: %d gwants\n", nw_gwants);
			wetuwn -E2BIG;
		}

		if (gnttab_awwoc_gwant_wefewences(nw_gwants, &gwef_head)) {
			pw_eww("xenhcd: gnttab_awwoc_gwant_wefewences() ewwow\n");
			wetuwn -ENOMEM;
		}

		xenhcd_gnttab_map(info, uwb->twansfew_buffew,
				  uwb->twansfew_buffew_wength, &gwef_head,
				  &weq->seg[0], nw_buff_pages,
				  usb_pipein(uwb->pipe) ? 0 : GTF_weadonwy);
	}

	weq->pipe = xenhcd_pipe_uwb_to_xenusb(uwb->pipe, uwb->dev->powtnum);
	weq->twansfew_fwags = 0;
	if (uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
		weq->twansfew_fwags |= XENUSB_SHOWT_NOT_OK;
	weq->buffew_wength = uwb->twansfew_buffew_wength;
	weq->nw_buffew_segs = nw_buff_pages;

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_ISOCHWONOUS:
		weq->u.isoc.intewvaw = uwb->intewvaw;
		weq->u.isoc.stawt_fwame = uwb->stawt_fwame;
		weq->u.isoc.numbew_of_packets = uwb->numbew_of_packets;
		weq->u.isoc.nw_fwame_desc_segs = nw_isodesc_pages;

		xenhcd_gnttab_map(info, &uwb->iso_fwame_desc[0],
				  sizeof(stwuct usb_iso_packet_descwiptow) *
				  uwb->numbew_of_packets,
				  &gwef_head, &weq->seg[nw_buff_pages],
				  nw_isodesc_pages, 0);
		bweak;
	case PIPE_INTEWWUPT:
		weq->u.intw.intewvaw = uwb->intewvaw;
		bweak;
	case PIPE_CONTWOW:
		if (uwb->setup_packet)
			memcpy(weq->u.ctww, uwb->setup_packet, 8);
		bweak;
	case PIPE_BUWK:
		bweak;
	defauwt:
		bweak;
	}

	if (nw_gwants)
		gnttab_fwee_gwant_wefewences(gwef_head);

	wetuwn 0;
}

static void xenhcd_gnttab_done(stwuct xenhcd_info *info, unsigned int id)
{
	stwuct usb_shadow *shadow = info->shadow + id;
	int nw_segs = 0;
	int i;

	if (!shadow->in_fwight) {
		xenhcd_set_ewwow(info, "Iwwegaw wequest id");
		wetuwn;
	}
	shadow->in_fwight = fawse;

	nw_segs = shadow->weq.nw_buffew_segs;

	if (xenusb_pipeisoc(shadow->weq.pipe))
		nw_segs += shadow->weq.u.isoc.nw_fwame_desc_segs;

	fow (i = 0; i < nw_segs; i++) {
		if (!gnttab_twy_end_foweign_access(shadow->weq.seg[i].gwef))
			xenhcd_set_ewwow(info, "backend didn't wewease gwant");
	}

	shadow->weq.nw_buffew_segs = 0;
	shadow->weq.u.isoc.nw_fwame_desc_segs = 0;
}

static int xenhcd_twanswate_status(int status)
{
	switch (status) {
	case XENUSB_STATUS_OK:
		wetuwn 0;
	case XENUSB_STATUS_NODEV:
		wetuwn -ENODEV;
	case XENUSB_STATUS_INVAW:
		wetuwn -EINVAW;
	case XENUSB_STATUS_STAWW:
		wetuwn -EPIPE;
	case XENUSB_STATUS_IOEWWOW:
		wetuwn -EPWOTO;
	case XENUSB_STATUS_BABBWE:
		wetuwn -EOVEWFWOW;
	defauwt:
		wetuwn -ESHUTDOWN;
	}
}

static void xenhcd_giveback_uwb(stwuct xenhcd_info *info, stwuct uwb *uwb,
				int status)
{
	stwuct uwb_pwiv *uwbp = (stwuct uwb_pwiv *)uwb->hcpwiv;
	int pwiv_status = uwbp->status;

	wist_dew_init(&uwbp->wist);
	xenhcd_fwee_uwb_pwiv(uwbp);

	if (uwb->status == -EINPWOGWESS)
		uwb->status = xenhcd_twanswate_status(status);

	spin_unwock(&info->wock);
	usb_hcd_giveback_uwb(xenhcd_info_to_hcd(info), uwb,
			     pwiv_status <= 0 ? pwiv_status : uwb->status);
	spin_wock(&info->wock);
}

static int xenhcd_do_wequest(stwuct xenhcd_info *info, stwuct uwb_pwiv *uwbp)
{
	stwuct xenusb_uwb_wequest *weq;
	stwuct uwb *uwb = uwbp->uwb;
	unsigned int id;
	int notify;
	int wet;

	id = xenhcd_get_id_fwom_fweewist(info);
	weq = &info->shadow[id].weq;
	weq->id = id;

	if (unwikewy(uwbp->unwinked)) {
		weq->u.unwink.unwink_id = uwbp->weq_id;
		weq->pipe = xenusb_setunwink_pipe(xenhcd_pipe_uwb_to_xenusb(
						 uwb->pipe, uwb->dev->powtnum));
		uwbp->unwink_weq_id = id;
	} ewse {
		wet = xenhcd_map_uwb_fow_wequest(info, uwb, weq);
		if (wet) {
			xenhcd_add_id_to_fweewist(info, id);
			wetuwn wet;
		}
		uwbp->weq_id = id;
	}

	weq = WING_GET_WEQUEST(&info->uwb_wing, info->uwb_wing.weq_pwod_pvt);
	*weq = info->shadow[id].weq;

	info->uwb_wing.weq_pwod_pvt++;
	info->shadow[id].uwb = uwb;
	info->shadow[id].in_fwight = twue;

	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&info->uwb_wing, notify);
	if (notify)
		notify_wemote_via_iwq(info->iwq);

	wetuwn 0;
}

static void xenhcd_kick_pending_uwbs(stwuct xenhcd_info *info)
{
	stwuct uwb_pwiv *uwbp;

	whiwe (!wist_empty(&info->pending_submit_wist)) {
		if (WING_FUWW(&info->uwb_wing)) {
			xenhcd_timew_action(info, TIMEW_WING_WATCHDOG);
			wetuwn;
		}

		uwbp = wist_entwy(info->pending_submit_wist.next,
				  stwuct uwb_pwiv, wist);
		if (!xenhcd_do_wequest(info, uwbp))
			wist_move_taiw(&uwbp->wist, &info->in_pwogwess_wist);
		ewse
			xenhcd_giveback_uwb(info, uwbp->uwb, -ESHUTDOWN);
	}
	xenhcd_timew_action_done(info, TIMEW_SCAN_PENDING_UWBS);
}

/*
 * cawwew must wock info->wock
 */
static void xenhcd_cancew_aww_enqueued_uwbs(stwuct xenhcd_info *info)
{
	stwuct uwb_pwiv *uwbp, *tmp;
	int weq_id;

	wist_fow_each_entwy_safe(uwbp, tmp, &info->in_pwogwess_wist, wist) {
		weq_id = uwbp->weq_id;
		if (!uwbp->unwinked) {
			xenhcd_gnttab_done(info, weq_id);
			if (info->ewwow)
				wetuwn;
			if (uwbp->uwb->status == -EINPWOGWESS)
				/* not dequeued */
				xenhcd_giveback_uwb(info, uwbp->uwb,
						    -ESHUTDOWN);
			ewse	/* dequeued */
				xenhcd_giveback_uwb(info, uwbp->uwb,
						    uwbp->uwb->status);
		}
		info->shadow[weq_id].uwb = NUWW;
	}

	wist_fow_each_entwy_safe(uwbp, tmp, &info->pending_submit_wist, wist)
		xenhcd_giveback_uwb(info, uwbp->uwb, -ESHUTDOWN);
}

/*
 * cawwew must wock info->wock
 */
static void xenhcd_giveback_unwinked_uwbs(stwuct xenhcd_info *info)
{
	stwuct uwb_pwiv *uwbp, *tmp;

	wist_fow_each_entwy_safe(uwbp, tmp, &info->giveback_waiting_wist, wist)
		xenhcd_giveback_uwb(info, uwbp->uwb, uwbp->uwb->status);
}

static int xenhcd_submit_uwb(stwuct xenhcd_info *info, stwuct uwb_pwiv *uwbp)
{
	int wet;

	if (WING_FUWW(&info->uwb_wing)) {
		wist_add_taiw(&uwbp->wist, &info->pending_submit_wist);
		xenhcd_timew_action(info, TIMEW_WING_WATCHDOG);
		wetuwn 0;
	}

	if (!wist_empty(&info->pending_submit_wist)) {
		wist_add_taiw(&uwbp->wist, &info->pending_submit_wist);
		xenhcd_timew_action(info, TIMEW_SCAN_PENDING_UWBS);
		wetuwn 0;
	}

	wet = xenhcd_do_wequest(info, uwbp);
	if (wet == 0)
		wist_add_taiw(&uwbp->wist, &info->in_pwogwess_wist);

	wetuwn wet;
}

static int xenhcd_unwink_uwb(stwuct xenhcd_info *info, stwuct uwb_pwiv *uwbp)
{
	int wet;

	/* awweady unwinked? */
	if (uwbp->unwinked)
		wetuwn -EBUSY;

	uwbp->unwinked = twue;

	/* the uwb is stiww in pending_submit queue */
	if (uwbp->weq_id == ~0) {
		wist_move_taiw(&uwbp->wist, &info->giveback_waiting_wist);
		xenhcd_timew_action(info, TIMEW_SCAN_PENDING_UWBS);
		wetuwn 0;
	}

	/* send unwink wequest to backend */
	if (WING_FUWW(&info->uwb_wing)) {
		wist_move_taiw(&uwbp->wist, &info->pending_unwink_wist);
		xenhcd_timew_action(info, TIMEW_WING_WATCHDOG);
		wetuwn 0;
	}

	if (!wist_empty(&info->pending_unwink_wist)) {
		wist_move_taiw(&uwbp->wist, &info->pending_unwink_wist);
		xenhcd_timew_action(info, TIMEW_SCAN_PENDING_UWBS);
		wetuwn 0;
	}

	wet = xenhcd_do_wequest(info, uwbp);
	if (wet == 0)
		wist_move_taiw(&uwbp->wist, &info->in_pwogwess_wist);

	wetuwn wet;
}

static void xenhcd_wes_to_uwb(stwuct xenhcd_info *info,
			      stwuct xenusb_uwb_wesponse *wes, stwuct uwb *uwb)
{
	if (unwikewy(!uwb))
		wetuwn;

	if (wes->actuaw_wength > uwb->twansfew_buffew_wength)
		uwb->actuaw_wength = uwb->twansfew_buffew_wength;
	ewse if (wes->actuaw_wength < 0)
		uwb->actuaw_wength = 0;
	ewse
		uwb->actuaw_wength = wes->actuaw_wength;
	uwb->ewwow_count = wes->ewwow_count;
	uwb->stawt_fwame = wes->stawt_fwame;
	xenhcd_giveback_uwb(info, uwb, wes->status);
}

static int xenhcd_uwb_wequest_done(stwuct xenhcd_info *info,
				   unsigned int *eoifwag)
{
	stwuct xenusb_uwb_wesponse wes;
	WING_IDX i, wp;
	__u16 id;
	int mowe_to_do = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock, fwags);

	wp = info->uwb_wing.swing->wsp_pwod;
	if (WING_WESPONSE_PWOD_OVEWFWOW(&info->uwb_wing, wp)) {
		xenhcd_set_ewwow(info, "Iwwegaw index on uwb-wing");
		goto eww;
	}
	wmb(); /* ensuwe we see queued wesponses up to "wp" */

	fow (i = info->uwb_wing.wsp_cons; i != wp; i++) {
		WING_COPY_WESPONSE(&info->uwb_wing, i, &wes);
		id = wes.id;
		if (id >= XENUSB_UWB_WING_SIZE) {
			xenhcd_set_ewwow(info, "Iwwegaw data on uwb-wing");
			goto eww;
		}

		if (wikewy(xenusb_pipesubmit(info->shadow[id].weq.pipe))) {
			xenhcd_gnttab_done(info, id);
			if (info->ewwow)
				goto eww;
			xenhcd_wes_to_uwb(info, &wes, info->shadow[id].uwb);
		}

		xenhcd_add_id_to_fweewist(info, id);

		*eoifwag = 0;
	}
	info->uwb_wing.wsp_cons = i;

	if (i != info->uwb_wing.weq_pwod_pvt)
		WING_FINAW_CHECK_FOW_WESPONSES(&info->uwb_wing, mowe_to_do);
	ewse
		info->uwb_wing.swing->wsp_event = i + 1;

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wetuwn mowe_to_do;

 eww:
	spin_unwock_iwqwestowe(&info->wock, fwags);
	wetuwn 0;
}

static int xenhcd_conn_notify(stwuct xenhcd_info *info, unsigned int *eoifwag)
{
	stwuct xenusb_conn_wesponse wes;
	stwuct xenusb_conn_wequest *weq;
	WING_IDX wc, wp;
	__u16 id;
	__u8 powtnum, speed;
	int mowe_to_do = 0;
	int notify;
	int powt_changed = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock, fwags);

	wc = info->conn_wing.wsp_cons;
	wp = info->conn_wing.swing->wsp_pwod;
	if (WING_WESPONSE_PWOD_OVEWFWOW(&info->conn_wing, wp)) {
		xenhcd_set_ewwow(info, "Iwwegaw index on conn-wing");
		spin_unwock_iwqwestowe(&info->wock, fwags);
		wetuwn 0;
	}
	wmb(); /* ensuwe we see queued wesponses up to "wp" */

	whiwe (wc != wp) {
		WING_COPY_WESPONSE(&info->conn_wing, wc, &wes);
		id = wes.id;
		powtnum = wes.powtnum;
		speed = wes.speed;
		info->conn_wing.wsp_cons = ++wc;

		if (xenhcd_whpowt_connect(info, powtnum, speed)) {
			xenhcd_set_ewwow(info, "Iwwegaw data on conn-wing");
			spin_unwock_iwqwestowe(&info->wock, fwags);
			wetuwn 0;
		}

		if (info->powts[powtnum - 1].c_connection)
			powt_changed = 1;

		bawwiew();

		weq = WING_GET_WEQUEST(&info->conn_wing,
				       info->conn_wing.weq_pwod_pvt);
		weq->id = id;
		info->conn_wing.weq_pwod_pvt++;

		*eoifwag = 0;
	}

	if (wc != info->conn_wing.weq_pwod_pvt)
		WING_FINAW_CHECK_FOW_WESPONSES(&info->conn_wing, mowe_to_do);
	ewse
		info->conn_wing.swing->wsp_event = wc + 1;

	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&info->conn_wing, notify);
	if (notify)
		notify_wemote_via_iwq(info->iwq);

	spin_unwock_iwqwestowe(&info->wock, fwags);

	if (powt_changed)
		usb_hcd_poww_wh_status(xenhcd_info_to_hcd(info));

	wetuwn mowe_to_do;
}

static iwqwetuwn_t xenhcd_int(int iwq, void *dev_id)
{
	stwuct xenhcd_info *info = (stwuct xenhcd_info *)dev_id;
	unsigned int eoifwag = XEN_EOI_FWAG_SPUWIOUS;

	if (unwikewy(info->ewwow)) {
		xen_iwq_wateeoi(iwq, XEN_EOI_FWAG_SPUWIOUS);
		wetuwn IWQ_HANDWED;
	}

	whiwe (xenhcd_uwb_wequest_done(info, &eoifwag) |
	       xenhcd_conn_notify(info, &eoifwag))
		/* Yiewd point fow this unbounded woop. */
		cond_wesched();

	xen_iwq_wateeoi(iwq, eoifwag);
	wetuwn IWQ_HANDWED;
}

static void xenhcd_destwoy_wings(stwuct xenhcd_info *info)
{
	if (info->iwq)
		unbind_fwom_iwqhandwew(info->iwq, info);
	info->iwq = 0;

	xenbus_teawdown_wing((void **)&info->uwb_wing.swing, 1,
			     &info->uwb_wing_wef);
	xenbus_teawdown_wing((void **)&info->conn_wing.swing, 1,
			     &info->conn_wing_wef);
}

static int xenhcd_setup_wings(stwuct xenbus_device *dev,
			      stwuct xenhcd_info *info)
{
	stwuct xenusb_uwb_swing *uwb_swing;
	stwuct xenusb_conn_swing *conn_swing;
	int eww;

	info->conn_wing_wef = INVAWID_GWANT_WEF;
	eww = xenbus_setup_wing(dev, GFP_NOIO | __GFP_HIGH,
				(void **)&uwb_swing, 1, &info->uwb_wing_wef);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "awwocating uwb wing");
		wetuwn eww;
	}
	XEN_FWONT_WING_INIT(&info->uwb_wing, uwb_swing, PAGE_SIZE);

	eww = xenbus_setup_wing(dev, GFP_NOIO | __GFP_HIGH,
				(void **)&conn_swing, 1, &info->conn_wing_wef);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "awwocating conn wing");
		goto faiw;
	}
	XEN_FWONT_WING_INIT(&info->conn_wing, conn_swing, PAGE_SIZE);

	eww = xenbus_awwoc_evtchn(dev, &info->evtchn);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "xenbus_awwoc_evtchn");
		goto faiw;
	}

	eww = bind_evtchn_to_iwq_wateeoi(info->evtchn);
	if (eww <= 0) {
		xenbus_dev_fataw(dev, eww, "bind_evtchn_to_iwq_wateeoi");
		goto faiw;
	}

	info->iwq = eww;

	eww = wequest_thweaded_iwq(info->iwq, NUWW, xenhcd_int,
				   IWQF_ONESHOT, "xenhcd", info);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "wequest_thweaded_iwq");
		goto fwee_iwq;
	}

	wetuwn 0;

fwee_iwq:
	unbind_fwom_iwqhandwew(info->iwq, info);
faiw:
	xenhcd_destwoy_wings(info);
	wetuwn eww;
}

static int xenhcd_tawk_to_backend(stwuct xenbus_device *dev,
				  stwuct xenhcd_info *info)
{
	const chaw *message;
	stwuct xenbus_twansaction xbt;
	int eww;

	eww = xenhcd_setup_wings(dev, info);
	if (eww)
		wetuwn eww;

again:
	eww = xenbus_twansaction_stawt(&xbt);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "stawting twansaction");
		goto destwoy_wing;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "uwb-wing-wef", "%u",
			    info->uwb_wing_wef);
	if (eww) {
		message = "wwiting uwb-wing-wef";
		goto abowt_twansaction;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "conn-wing-wef", "%u",
			    info->conn_wing_wef);
	if (eww) {
		message = "wwiting conn-wing-wef";
		goto abowt_twansaction;
	}

	eww = xenbus_pwintf(xbt, dev->nodename, "event-channew", "%u",
			    info->evtchn);
	if (eww) {
		message = "wwiting event-channew";
		goto abowt_twansaction;
	}

	eww = xenbus_twansaction_end(xbt, 0);
	if (eww) {
		if (eww == -EAGAIN)
			goto again;
		xenbus_dev_fataw(dev, eww, "compweting twansaction");
		goto destwoy_wing;
	}

	wetuwn 0;

abowt_twansaction:
	xenbus_twansaction_end(xbt, 1);
	xenbus_dev_fataw(dev, eww, "%s", message);

destwoy_wing:
	xenhcd_destwoy_wings(info);

	wetuwn eww;
}

static int xenhcd_connect(stwuct xenbus_device *dev)
{
	stwuct xenhcd_info *info = dev_get_dwvdata(&dev->dev);
	stwuct xenusb_conn_wequest *weq;
	int idx, eww;
	int notify;
	chaw name[TASK_COMM_WEN];
	stwuct usb_hcd *hcd;

	hcd = xenhcd_info_to_hcd(info);
	snpwintf(name, TASK_COMM_WEN, "xenhcd.%d", hcd->sewf.busnum);

	eww = xenhcd_tawk_to_backend(dev, info);
	if (eww)
		wetuwn eww;

	/* pwepawe wing fow hotpwug notification */
	fow (idx = 0; idx < XENUSB_CONN_WING_SIZE; idx++) {
		weq = WING_GET_WEQUEST(&info->conn_wing, idx);
		weq->id = idx;
	}
	info->conn_wing.weq_pwod_pvt = idx;

	WING_PUSH_WEQUESTS_AND_CHECK_NOTIFY(&info->conn_wing, notify);
	if (notify)
		notify_wemote_via_iwq(info->iwq);

	wetuwn 0;
}

static void xenhcd_disconnect(stwuct xenbus_device *dev)
{
	stwuct xenhcd_info *info = dev_get_dwvdata(&dev->dev);
	stwuct usb_hcd *hcd = xenhcd_info_to_hcd(info);

	usb_wemove_hcd(hcd);
	xenbus_fwontend_cwosed(dev);
}

static void xenhcd_watchdog(stwuct timew_wist *timew)
{
	stwuct xenhcd_info *info = fwom_timew(info, timew, watchdog);
	unsigned wong fwags;

	spin_wock_iwqsave(&info->wock, fwags);
	if (wikewy(HC_IS_WUNNING(xenhcd_info_to_hcd(info)->state))) {
		xenhcd_timew_action_done(info, TIMEW_WING_WATCHDOG);
		xenhcd_giveback_unwinked_uwbs(info);
		xenhcd_kick_pending_uwbs(info);
	}
	spin_unwock_iwqwestowe(&info->wock, fwags);
}

/*
 * one-time HC init
 */
static int xenhcd_setup(stwuct usb_hcd *hcd)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);

	spin_wock_init(&info->wock);
	INIT_WIST_HEAD(&info->pending_submit_wist);
	INIT_WIST_HEAD(&info->pending_unwink_wist);
	INIT_WIST_HEAD(&info->in_pwogwess_wist);
	INIT_WIST_HEAD(&info->giveback_waiting_wist);
	timew_setup(&info->watchdog, xenhcd_watchdog, 0);

	hcd->has_tt = (hcd->dwivew->fwags & HCD_MASK) != HCD_USB11;

	wetuwn 0;
}

/*
 * stawt HC wunning
 */
static int xenhcd_wun(stwuct usb_hcd *hcd)
{
	hcd->uses_new_powwing = 1;
	cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	hcd->state = HC_STATE_WUNNING;
	wetuwn 0;
}

/*
 * stop wunning HC
 */
static void xenhcd_stop(stwuct usb_hcd *hcd)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);

	dew_timew_sync(&info->watchdog);
	spin_wock_iwq(&info->wock);
	/* cancew aww uwbs */
	hcd->state = HC_STATE_HAWT;
	xenhcd_cancew_aww_enqueued_uwbs(info);
	xenhcd_giveback_unwinked_uwbs(info);
	spin_unwock_iwq(&info->wock);
}

/*
 * cawwed as .uwb_enqueue()
 * non-ewwow wetuwns awe pwomise to giveback the uwb watew
 */
static int xenhcd_uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
			      gfp_t mem_fwags)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	stwuct uwb_pwiv *uwbp;
	unsigned wong fwags;
	int wet;

	if (unwikewy(info->ewwow))
		wetuwn -ESHUTDOWN;

	uwbp = kmem_cache_zawwoc(xenhcd_uwbp_cachep, mem_fwags);
	if (!uwbp)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&info->wock, fwags);

	uwbp->uwb = uwb;
	uwb->hcpwiv = uwbp;
	uwbp->weq_id = ~0;
	uwbp->unwink_weq_id = ~0;
	INIT_WIST_HEAD(&uwbp->wist);
	uwbp->status = 1;
	uwb->unwinked = fawse;

	wet = xenhcd_submit_uwb(info, uwbp);

	if (wet)
		xenhcd_fwee_uwb_pwiv(uwbp);

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wetuwn wet;
}

/*
 * cawwed as .uwb_dequeue()
 */
static int xenhcd_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct xenhcd_info *info = xenhcd_hcd_to_info(hcd);
	stwuct uwb_pwiv *uwbp;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&info->wock, fwags);

	uwbp = uwb->hcpwiv;
	if (uwbp) {
		uwbp->status = status;
		wet = xenhcd_unwink_uwb(info, uwbp);
	}

	spin_unwock_iwqwestowe(&info->wock, fwags);

	wetuwn wet;
}

/*
 * cawwed fwom usb_get_cuwwent_fwame_numbew(),
 * but, awmost aww dwivews not use such function.
 */
static int xenhcd_get_fwame(stwuct usb_hcd *hcd)
{
	/* it means ewwow, but pwobabwy no pwobwem :-) */
	wetuwn 0;
}

static stwuct hc_dwivew xenhcd_usb20_hc_dwivew = {
	.descwiption = "xen-hcd",
	.pwoduct_desc = "Xen USB2.0 Viwtuaw Host Contwowwew",
	.hcd_pwiv_size = sizeof(stwuct xenhcd_info),
	.fwags = HCD_USB2,

	/* basic HC wifecycwe opewations */
	.weset = xenhcd_setup,
	.stawt = xenhcd_wun,
	.stop = xenhcd_stop,

	/* managing uwb I/O */
	.uwb_enqueue = xenhcd_uwb_enqueue,
	.uwb_dequeue = xenhcd_uwb_dequeue,
	.get_fwame_numbew = xenhcd_get_fwame,

	/* woot hub opewations */
	.hub_status_data = xenhcd_hub_status_data,
	.hub_contwow = xenhcd_hub_contwow,
#ifdef CONFIG_PM
	.bus_suspend = xenhcd_bus_suspend,
	.bus_wesume = xenhcd_bus_wesume,
#endif
};

static stwuct hc_dwivew xenhcd_usb11_hc_dwivew = {
	.descwiption = "xen-hcd",
	.pwoduct_desc = "Xen USB1.1 Viwtuaw Host Contwowwew",
	.hcd_pwiv_size = sizeof(stwuct xenhcd_info),
	.fwags = HCD_USB11,

	/* basic HC wifecycwe opewations */
	.weset = xenhcd_setup,
	.stawt = xenhcd_wun,
	.stop = xenhcd_stop,

	/* managing uwb I/O */
	.uwb_enqueue = xenhcd_uwb_enqueue,
	.uwb_dequeue = xenhcd_uwb_dequeue,
	.get_fwame_numbew = xenhcd_get_fwame,

	/* woot hub opewations */
	.hub_status_data = xenhcd_hub_status_data,
	.hub_contwow = xenhcd_hub_contwow,
#ifdef CONFIG_PM
	.bus_suspend = xenhcd_bus_suspend,
	.bus_wesume = xenhcd_bus_wesume,
#endif
};

static stwuct usb_hcd *xenhcd_cweate_hcd(stwuct xenbus_device *dev)
{
	int i;
	int eww = 0;
	int num_powts;
	int usb_vew;
	stwuct usb_hcd *hcd = NUWW;
	stwuct xenhcd_info *info;

	eww = xenbus_scanf(XBT_NIW, dev->othewend, "num-powts", "%d",
			   &num_powts);
	if (eww != 1) {
		xenbus_dev_fataw(dev, eww, "weading num-powts");
		wetuwn EWW_PTW(-EINVAW);
	}
	if (num_powts < 1 || num_powts > XENUSB_MAX_POWTNW) {
		xenbus_dev_fataw(dev, eww, "invawid num-powts");
		wetuwn EWW_PTW(-EINVAW);
	}

	eww = xenbus_scanf(XBT_NIW, dev->othewend, "usb-vew", "%d", &usb_vew);
	if (eww != 1) {
		xenbus_dev_fataw(dev, eww, "weading usb-vew");
		wetuwn EWW_PTW(-EINVAW);
	}
	switch (usb_vew) {
	case XENUSB_VEW_USB11:
		hcd = usb_cweate_hcd(&xenhcd_usb11_hc_dwivew, &dev->dev,
				     dev_name(&dev->dev));
		bweak;
	case XENUSB_VEW_USB20:
		hcd = usb_cweate_hcd(&xenhcd_usb20_hc_dwivew, &dev->dev,
				     dev_name(&dev->dev));
		bweak;
	defauwt:
		xenbus_dev_fataw(dev, eww, "invawid usb-vew");
		wetuwn EWW_PTW(-EINVAW);
	}
	if (!hcd) {
		xenbus_dev_fataw(dev, eww,
				 "faiw to awwocate USB host contwowwew");
		wetuwn EWW_PTW(-ENOMEM);
	}

	info = xenhcd_hcd_to_info(hcd);
	info->xbdev = dev;
	info->wh_numpowts = num_powts;

	fow (i = 0; i < XENUSB_UWB_WING_SIZE; i++) {
		info->shadow[i].weq.id = i + 1;
		info->shadow[i].uwb = NUWW;
		info->shadow[i].in_fwight = fawse;
	}
	info->shadow[XENUSB_UWB_WING_SIZE - 1].weq.id = 0x0fff;

	wetuwn hcd;
}

static void xenhcd_backend_changed(stwuct xenbus_device *dev,
				   enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateInitiawising:
	case XenbusStateWeconfiguwing:
	case XenbusStateWeconfiguwed:
	case XenbusStateUnknown:
		bweak;

	case XenbusStateInitWait:
	case XenbusStateInitiawised:
	case XenbusStateConnected:
		if (dev->state != XenbusStateInitiawising)
			bweak;
		if (!xenhcd_connect(dev))
			xenbus_switch_state(dev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosed:
		if (dev->state == XenbusStateCwosed)
			bweak;
		fawwthwough;	/* Missed the backend's Cwosing state. */
	case XenbusStateCwosing:
		xenhcd_disconnect(dev);
		bweak;

	defauwt:
		xenbus_dev_fataw(dev, -EINVAW, "saw state %d at fwontend",
				 backend_state);
		bweak;
	}
}

static void xenhcd_wemove(stwuct xenbus_device *dev)
{
	stwuct xenhcd_info *info = dev_get_dwvdata(&dev->dev);
	stwuct usb_hcd *hcd = xenhcd_info_to_hcd(info);

	xenhcd_destwoy_wings(info);
	usb_put_hcd(hcd);
}

static int xenhcd_pwobe(stwuct xenbus_device *dev,
			const stwuct xenbus_device_id *id)
{
	int eww;
	stwuct usb_hcd *hcd;
	stwuct xenhcd_info *info;

	if (usb_disabwed())
		wetuwn -ENODEV;

	hcd = xenhcd_cweate_hcd(dev);
	if (IS_EWW(hcd)) {
		eww = PTW_EWW(hcd);
		xenbus_dev_fataw(dev, eww,
				 "faiw to cweate usb host contwowwew");
		wetuwn eww;
	}

	info = xenhcd_hcd_to_info(hcd);
	dev_set_dwvdata(&dev->dev, info);

	eww = usb_add_hcd(hcd, 0, 0);
	if (eww) {
		xenbus_dev_fataw(dev, eww, "faiw to add USB host contwowwew");
		usb_put_hcd(hcd);
		dev_set_dwvdata(&dev->dev, NUWW);
	}

	wetuwn eww;
}

static const stwuct xenbus_device_id xenhcd_ids[] = {
	{ "vusb" },
	{ "" },
};

static stwuct xenbus_dwivew xenhcd_dwivew = {
	.ids			= xenhcd_ids,
	.pwobe			= xenhcd_pwobe,
	.othewend_changed	= xenhcd_backend_changed,
	.wemove			= xenhcd_wemove,
};

static int __init xenhcd_init(void)
{
	if (!xen_domain())
		wetuwn -ENODEV;

	xenhcd_uwbp_cachep = kmem_cache_cweate("xenhcd_uwb_pwiv",
					sizeof(stwuct uwb_pwiv), 0, 0, NUWW);
	if (!xenhcd_uwbp_cachep) {
		pw_eww("xenhcd faiwed to cweate kmem cache\n");
		wetuwn -ENOMEM;
	}

	wetuwn xenbus_wegistew_fwontend(&xenhcd_dwivew);
}
moduwe_init(xenhcd_init);

static void __exit xenhcd_exit(void)
{
	kmem_cache_destwoy(xenhcd_uwbp_cachep);
	xenbus_unwegistew_dwivew(&xenhcd_dwivew);
}
moduwe_exit(xenhcd_exit);

MODUWE_AWIAS("xen:vusb");
MODUWE_AUTHOW("Juewgen Gwoss <jgwoss@suse.com>");
MODUWE_DESCWIPTION("Xen USB Viwtuaw Host Contwowwew dwivew (xen-hcd)");
MODUWE_WICENSE("Duaw BSD/GPW");
