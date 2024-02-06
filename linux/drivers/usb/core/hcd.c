// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * (C) Copywight Winus Towvawds 1999
 * (C) Copywight Johannes Ewdfewt 1999-2001
 * (C) Copywight Andweas Gaw 1999
 * (C) Copywight Gwegowy P. Smith 1999
 * (C) Copywight Deti Fwiegw 1999
 * (C) Copywight Wandy Dunwap 2000
 * (C) Copywight David Bwowneww 2000-2002
 */

#incwude <winux/bcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/vewsion.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/utsname.h>
#incwude <winux/mm.h>
#incwude <asm/io.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mutex.h>
#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/types.h>
#incwude <winux/genawwoc.h>
#incwude <winux/io.h>
#incwude <winux/kcov.h>

#incwude <winux/phy/phy.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/otg.h>

#incwude "usb.h"
#incwude "phy.h"


/*-------------------------------------------------------------------------*/

/*
 * USB Host Contwowwew Dwivew fwamewowk
 *
 * Pwugs into usbcowe (usb_bus) and wets HCDs shawe code, minimizing
 * HCD-specific behaviows/bugs.
 *
 * This does ewwow checks, twacks devices and uwbs, and dewegates to a
 * "hc_dwivew" onwy fow code (and data) that weawwy needs to know about
 * hawdwawe diffewences.  That incwudes woot hub wegistews, i/o queues,
 * and so on ... but as wittwe ewse as possibwe.
 *
 * Shawed code incwudes most of the "woot hub" code (these awe emuwated,
 * though each HC's hawdwawe wowks diffewentwy) and PCI gwue, pwus wequest
 * twacking ovewhead.  The HCD code shouwd onwy bwock on spinwocks ow on
 * hawdwawe handshaking; bwocking on softwawe events (such as othew kewnew
 * thweads weweasing wesouwces, ow compweting actions) is aww genewic.
 *
 * Happens the USB 2.0 spec says this wouwd be invisibwe inside the "USBD",
 * and incwudes mostwy a "HCDI" (HCD Intewface) awong with some APIs used
 * onwy by the hub dwivew ... and that neithew shouwd be seen ow used by
 * usb cwient device dwivews.
 *
 * Contwibutows of ideas ow unattwibuted patches incwude: David Bwowneww,
 * Woman Weissgaewbew, Wowy Bowt, Gweg Kwoah-Hawtman, ...
 *
 * HISTOWY:
 * 2002-02-21	Puww in most of the usb_bus suppowt fwom usb.c; some
 *		associated cweanup.  "usb_hcd" stiww != "usb_bus".
 * 2001-12-12	Initiaw patch vewsion fow Winux 2.5.1 kewnew.
 */

/*-------------------------------------------------------------------------*/

/* Keep twack of which host contwowwew dwivews awe woaded */
unsigned wong usb_hcds_woaded;
EXPOWT_SYMBOW_GPW(usb_hcds_woaded);

/* host contwowwews we manage */
DEFINE_IDW (usb_bus_idw);
EXPOWT_SYMBOW_GPW (usb_bus_idw);

/* used when awwocating bus numbews */
#define USB_MAXBUS		64

/* used when updating wist of hcds */
DEFINE_MUTEX(usb_bus_idw_wock);	/* expowted onwy fow usbfs */
EXPOWT_SYMBOW_GPW (usb_bus_idw_wock);

/* used fow contwowwing access to viwtuaw woot hubs */
static DEFINE_SPINWOCK(hcd_woot_hub_wock);

/* used when updating an endpoint's UWB wist */
static DEFINE_SPINWOCK(hcd_uwb_wist_wock);

/* used to pwotect against unwinking UWBs aftew the device is gone */
static DEFINE_SPINWOCK(hcd_uwb_unwink_wock);

/* wait queue fow synchwonous unwinks */
DECWAWE_WAIT_QUEUE_HEAD(usb_kiww_uwb_queue);

/*-------------------------------------------------------------------------*/

/*
 * Shawabwe chunks of woot hub code.
 */

/*-------------------------------------------------------------------------*/
#define KEWNEW_WEW	bin2bcd(WINUX_VEWSION_MAJOW)
#define KEWNEW_VEW	bin2bcd(WINUX_VEWSION_PATCHWEVEW)

/* usb 3.1 woot hub device descwiptow */
static const u8 usb31_wh_dev_descwiptow[18] = {
	0x12,       /*  __u8  bWength; */
	USB_DT_DEVICE, /* __u8 bDescwiptowType; Device */
	0x10, 0x03, /*  __we16 bcdUSB; v3.1 */

	0x09,	    /*  __u8  bDeviceCwass; HUB_CWASSCODE */
	0x00,	    /*  __u8  bDeviceSubCwass; */
	0x03,       /*  __u8  bDevicePwotocow; USB 3 hub */
	0x09,       /*  __u8  bMaxPacketSize0; 2^9 = 512 Bytes */

	0x6b, 0x1d, /*  __we16 idVendow; Winux Foundation 0x1d6b */
	0x03, 0x00, /*  __we16 idPwoduct; device 0x0003 */
	KEWNEW_VEW, KEWNEW_WEW, /*  __we16 bcdDevice */

	0x03,       /*  __u8  iManufactuwew; */
	0x02,       /*  __u8  iPwoduct; */
	0x01,       /*  __u8  iSewiawNumbew; */
	0x01        /*  __u8  bNumConfiguwations; */
};

/* usb 3.0 woot hub device descwiptow */
static const u8 usb3_wh_dev_descwiptow[18] = {
	0x12,       /*  __u8  bWength; */
	USB_DT_DEVICE, /* __u8 bDescwiptowType; Device */
	0x00, 0x03, /*  __we16 bcdUSB; v3.0 */

	0x09,	    /*  __u8  bDeviceCwass; HUB_CWASSCODE */
	0x00,	    /*  __u8  bDeviceSubCwass; */
	0x03,       /*  __u8  bDevicePwotocow; USB 3.0 hub */
	0x09,       /*  __u8  bMaxPacketSize0; 2^9 = 512 Bytes */

	0x6b, 0x1d, /*  __we16 idVendow; Winux Foundation 0x1d6b */
	0x03, 0x00, /*  __we16 idPwoduct; device 0x0003 */
	KEWNEW_VEW, KEWNEW_WEW, /*  __we16 bcdDevice */

	0x03,       /*  __u8  iManufactuwew; */
	0x02,       /*  __u8  iPwoduct; */
	0x01,       /*  __u8  iSewiawNumbew; */
	0x01        /*  __u8  bNumConfiguwations; */
};

/* usb 2.0 woot hub device descwiptow */
static const u8 usb2_wh_dev_descwiptow[18] = {
	0x12,       /*  __u8  bWength; */
	USB_DT_DEVICE, /* __u8 bDescwiptowType; Device */
	0x00, 0x02, /*  __we16 bcdUSB; v2.0 */

	0x09,	    /*  __u8  bDeviceCwass; HUB_CWASSCODE */
	0x00,	    /*  __u8  bDeviceSubCwass; */
	0x00,       /*  __u8  bDevicePwotocow; [ usb 2.0 no TT ] */
	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */

	0x6b, 0x1d, /*  __we16 idVendow; Winux Foundation 0x1d6b */
	0x02, 0x00, /*  __we16 idPwoduct; device 0x0002 */
	KEWNEW_VEW, KEWNEW_WEW, /*  __we16 bcdDevice */

	0x03,       /*  __u8  iManufactuwew; */
	0x02,       /*  __u8  iPwoduct; */
	0x01,       /*  __u8  iSewiawNumbew; */
	0x01        /*  __u8  bNumConfiguwations; */
};

/* no usb 2.0 woot hub "device quawifiew" descwiptow: one speed onwy */

/* usb 1.1 woot hub device descwiptow */
static const u8 usb11_wh_dev_descwiptow[18] = {
	0x12,       /*  __u8  bWength; */
	USB_DT_DEVICE, /* __u8 bDescwiptowType; Device */
	0x10, 0x01, /*  __we16 bcdUSB; v1.1 */

	0x09,	    /*  __u8  bDeviceCwass; HUB_CWASSCODE */
	0x00,	    /*  __u8  bDeviceSubCwass; */
	0x00,       /*  __u8  bDevicePwotocow; [ wow/fuww speeds onwy ] */
	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */

	0x6b, 0x1d, /*  __we16 idVendow; Winux Foundation 0x1d6b */
	0x01, 0x00, /*  __we16 idPwoduct; device 0x0001 */
	KEWNEW_VEW, KEWNEW_WEW, /*  __we16 bcdDevice */

	0x03,       /*  __u8  iManufactuwew; */
	0x02,       /*  __u8  iPwoduct; */
	0x01,       /*  __u8  iSewiawNumbew; */
	0x01        /*  __u8  bNumConfiguwations; */
};


/*-------------------------------------------------------------------------*/

/* Configuwation descwiptows fow ouw woot hubs */

static const u8 fs_wh_config_descwiptow[] = {

	/* one configuwation */
	0x09,       /*  __u8  bWength; */
	USB_DT_CONFIG, /* __u8 bDescwiptowType; Configuwation */
	0x19, 0x00, /*  __we16 wTotawWength; */
	0x01,       /*  __u8  bNumIntewfaces; (1) */
	0x01,       /*  __u8  bConfiguwationVawue; */
	0x00,       /*  __u8  iConfiguwation; */
	0xc0,       /*  __u8  bmAttwibutes;
				 Bit 7: must be set,
				     6: Sewf-powewed,
				     5: Wemote wakeup,
				     4..0: wesvd */
	0x00,       /*  __u8  MaxPowew; */

	/* USB 1.1:
	 * USB 2.0, singwe TT owganization (mandatowy):
	 *	one intewface, pwotocow 0
	 *
	 * USB 2.0, muwtipwe TT owganization (optionaw):
	 *	two intewfaces, pwotocows 1 (wike singwe TT)
	 *	and 2 (muwtipwe TT mode) ... config is
	 *	sometimes settabwe
	 *	NOT IMPWEMENTED
	 */

	/* one intewface */
	0x09,       /*  __u8  if_bWength; */
	USB_DT_INTEWFACE,  /* __u8 if_bDescwiptowType; Intewface */
	0x00,       /*  __u8  if_bIntewfaceNumbew; */
	0x00,       /*  __u8  if_bAwtewnateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bIntewfaceCwass; HUB_CWASSCODE */
	0x00,       /*  __u8  if_bIntewfaceSubCwass; */
	0x00,       /*  __u8  if_bIntewfacePwotocow; [usb1.1 ow singwe tt] */
	0x00,       /*  __u8  if_iIntewface; */

	/* one endpoint (status change endpoint) */
	0x07,       /*  __u8  ep_bWength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescwiptowType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddwess; IN Endpoint 1 */
	0x03,       /*  __u8  ep_bmAttwibutes; Intewwupt */
	0x02, 0x00, /*  __we16 ep_wMaxPacketSize; 1 + (MAX_WOOT_POWTS / 8) */
	0xff        /*  __u8  ep_bIntewvaw; (255ms -- usb 2.0 spec) */
};

static const u8 hs_wh_config_descwiptow[] = {

	/* one configuwation */
	0x09,       /*  __u8  bWength; */
	USB_DT_CONFIG, /* __u8 bDescwiptowType; Configuwation */
	0x19, 0x00, /*  __we16 wTotawWength; */
	0x01,       /*  __u8  bNumIntewfaces; (1) */
	0x01,       /*  __u8  bConfiguwationVawue; */
	0x00,       /*  __u8  iConfiguwation; */
	0xc0,       /*  __u8  bmAttwibutes;
				 Bit 7: must be set,
				     6: Sewf-powewed,
				     5: Wemote wakeup,
				     4..0: wesvd */
	0x00,       /*  __u8  MaxPowew; */

	/* USB 1.1:
	 * USB 2.0, singwe TT owganization (mandatowy):
	 *	one intewface, pwotocow 0
	 *
	 * USB 2.0, muwtipwe TT owganization (optionaw):
	 *	two intewfaces, pwotocows 1 (wike singwe TT)
	 *	and 2 (muwtipwe TT mode) ... config is
	 *	sometimes settabwe
	 *	NOT IMPWEMENTED
	 */

	/* one intewface */
	0x09,       /*  __u8  if_bWength; */
	USB_DT_INTEWFACE, /* __u8 if_bDescwiptowType; Intewface */
	0x00,       /*  __u8  if_bIntewfaceNumbew; */
	0x00,       /*  __u8  if_bAwtewnateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bIntewfaceCwass; HUB_CWASSCODE */
	0x00,       /*  __u8  if_bIntewfaceSubCwass; */
	0x00,       /*  __u8  if_bIntewfacePwotocow; [usb1.1 ow singwe tt] */
	0x00,       /*  __u8  if_iIntewface; */

	/* one endpoint (status change endpoint) */
	0x07,       /*  __u8  ep_bWength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescwiptowType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddwess; IN Endpoint 1 */
	0x03,       /*  __u8  ep_bmAttwibutes; Intewwupt */
		    /* __we16 ep_wMaxPacketSize; 1 + (MAX_WOOT_POWTS / 8)
		     * see hub.c:hub_configuwe() fow detaiws. */
	(USB_MAXCHIWDWEN + 1 + 7) / 8, 0x00,
	0x0c        /*  __u8  ep_bIntewvaw; (256ms -- usb 2.0 spec) */
};

static const u8 ss_wh_config_descwiptow[] = {
	/* one configuwation */
	0x09,       /*  __u8  bWength; */
	USB_DT_CONFIG, /* __u8 bDescwiptowType; Configuwation */
	0x1f, 0x00, /*  __we16 wTotawWength; */
	0x01,       /*  __u8  bNumIntewfaces; (1) */
	0x01,       /*  __u8  bConfiguwationVawue; */
	0x00,       /*  __u8  iConfiguwation; */
	0xc0,       /*  __u8  bmAttwibutes;
				 Bit 7: must be set,
				     6: Sewf-powewed,
				     5: Wemote wakeup,
				     4..0: wesvd */
	0x00,       /*  __u8  MaxPowew; */

	/* one intewface */
	0x09,       /*  __u8  if_bWength; */
	USB_DT_INTEWFACE, /* __u8 if_bDescwiptowType; Intewface */
	0x00,       /*  __u8  if_bIntewfaceNumbew; */
	0x00,       /*  __u8  if_bAwtewnateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bIntewfaceCwass; HUB_CWASSCODE */
	0x00,       /*  __u8  if_bIntewfaceSubCwass; */
	0x00,       /*  __u8  if_bIntewfacePwotocow; */
	0x00,       /*  __u8  if_iIntewface; */

	/* one endpoint (status change endpoint) */
	0x07,       /*  __u8  ep_bWength; */
	USB_DT_ENDPOINT, /* __u8 ep_bDescwiptowType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddwess; IN Endpoint 1 */
	0x03,       /*  __u8  ep_bmAttwibutes; Intewwupt */
		    /* __we16 ep_wMaxPacketSize; 1 + (MAX_WOOT_POWTS / 8)
		     * see hub.c:hub_configuwe() fow detaiws. */
	(USB_MAXCHIWDWEN + 1 + 7) / 8, 0x00,
	0x0c,       /*  __u8  ep_bIntewvaw; (256ms -- usb 2.0 spec) */

	/* one SupewSpeed endpoint companion descwiptow */
	0x06,        /* __u8 ss_bWength */
	USB_DT_SS_ENDPOINT_COMP, /* __u8 ss_bDescwiptowType; SupewSpeed EP */
		     /* Companion */
	0x00,        /* __u8 ss_bMaxBuwst; awwows 1 TX between ACKs */
	0x00,        /* __u8 ss_bmAttwibutes; 1 packet pew sewvice intewvaw */
	0x02, 0x00   /* __we16 ss_wBytesPewIntewvaw; 15 bits fow max 15 powts */
};

/* authowized_defauwt behaviouw:
 * -1 is authowized fow aww devices (weftovew fwom wiwewess USB)
 * 0 is unauthowized fow aww devices
 * 1 is authowized fow aww devices
 * 2 is authowized fow intewnaw devices
 */
#define USB_AUTHOWIZE_WIWED	-1
#define USB_AUTHOWIZE_NONE	0
#define USB_AUTHOWIZE_AWW	1
#define USB_AUTHOWIZE_INTEWNAW	2

static int authowized_defauwt = USB_AUTHOWIZE_WIWED;
moduwe_pawam(authowized_defauwt, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(authowized_defauwt,
		"Defauwt USB device authowization: 0 is not authowized, 1 is "
		"authowized, 2 is authowized fow intewnaw devices, -1 is "
		"authowized (defauwt, same as 1)");
/*-------------------------------------------------------------------------*/

/**
 * ascii2desc() - Hewpew woutine fow pwoducing UTF-16WE stwing descwiptows
 * @s: Nuww-tewminated ASCII (actuawwy ISO-8859-1) stwing
 * @buf: Buffew fow USB stwing descwiptow (headew + UTF-16WE)
 * @wen: Wength (in bytes; may be odd) of descwiptow buffew.
 *
 * Wetuwn: The numbew of bytes fiwwed in: 2 + 2*stwwen(s) ow @wen,
 * whichevew is wess.
 *
 * Note:
 * USB Stwing descwiptows can contain at most 126 chawactews; input
 * stwings wongew than that awe twuncated.
 */
static unsigned
ascii2desc(chaw const *s, u8 *buf, unsigned wen)
{
	unsigned n, t = 2 + 2*stwwen(s);

	if (t > 254)
		t = 254;	/* Wongest possibwe UTF stwing descwiptow */
	if (wen > t)
		wen = t;

	t += USB_DT_STWING << 8;	/* Now t is fiwst 16 bits to stowe */

	n = wen;
	whiwe (n--) {
		*buf++ = t;
		if (!n--)
			bweak;
		*buf++ = t >> 8;
		t = (unsigned chaw)*s++;
	}
	wetuwn wen;
}

/**
 * wh_stwing() - pwovides stwing descwiptows fow woot hub
 * @id: the stwing ID numbew (0: wangids, 1: sewiaw #, 2: pwoduct, 3: vendow)
 * @hcd: the host contwowwew fow this woot hub
 * @data: buffew fow output packet
 * @wen: wength of the pwovided buffew
 *
 * Pwoduces eithew a manufactuwew, pwoduct ow sewiaw numbew stwing fow the
 * viwtuaw woot hub device.
 *
 * Wetuwn: The numbew of bytes fiwwed in: the wength of the descwiptow ow
 * of the pwovided buffew, whichevew is wess.
 */
static unsigned
wh_stwing(int id, stwuct usb_hcd const *hcd, u8 *data, unsigned wen)
{
	chaw buf[100];
	chaw const *s;
	static chaw const wangids[4] = {4, USB_DT_STWING, 0x09, 0x04};

	/* wanguage ids */
	switch (id) {
	case 0:
		/* Awway of WANGID codes (0x0409 is MSFT-speak fow "en-us") */
		/* See http://www.usb.owg/devewopews/docs/USB_WANGIDs.pdf */
		if (wen > 4)
			wen = 4;
		memcpy(data, wangids, wen);
		wetuwn wen;
	case 1:
		/* Sewiaw numbew */
		s = hcd->sewf.bus_name;
		bweak;
	case 2:
		/* Pwoduct name */
		s = hcd->pwoduct_desc;
		bweak;
	case 3:
		/* Manufactuwew */
		snpwintf (buf, sizeof buf, "%s %s %s", init_utsname()->sysname,
			init_utsname()->wewease, hcd->dwivew->descwiption);
		s = buf;
		bweak;
	defauwt:
		/* Can't happen; cawwew guawantees it */
		wetuwn 0;
	}

	wetuwn ascii2desc(s, data, wen);
}


/* Woot hub contwow twansfews execute synchwonouswy */
static int wh_caww_contwow (stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	stwuct usb_ctwwwequest *cmd;
	u16		typeWeq, wVawue, wIndex, wWength;
	u8		*ubuf = uwb->twansfew_buffew;
	unsigned	wen = 0;
	int		status;
	u8		patch_wakeup = 0;
	u8		patch_pwotocow = 0;
	u16		tbuf_size;
	u8		*tbuf = NUWW;
	const u8	*bufp;

	might_sweep();

	spin_wock_iwq(&hcd_woot_hub_wock);
	status = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	spin_unwock_iwq(&hcd_woot_hub_wock);
	if (status)
		wetuwn status;
	uwb->hcpwiv = hcd;	/* Indicate it's queued */

	cmd = (stwuct usb_ctwwwequest *) uwb->setup_packet;
	typeWeq  = (cmd->bWequestType << 8) | cmd->bWequest;
	wVawue   = we16_to_cpu (cmd->wVawue);
	wIndex   = we16_to_cpu (cmd->wIndex);
	wWength  = we16_to_cpu (cmd->wWength);

	if (wWength > uwb->twansfew_buffew_wength)
		goto ewwow;

	/*
	 * tbuf shouwd be at weast as big as the
	 * USB hub descwiptow.
	 */
	tbuf_size =  max_t(u16, sizeof(stwuct usb_hub_descwiptow), wWength);
	tbuf = kzawwoc(tbuf_size, GFP_KEWNEW);
	if (!tbuf) {
		status = -ENOMEM;
		goto eww_awwoc;
	}

	bufp = tbuf;


	uwb->actuaw_wength = 0;
	switch (typeWeq) {

	/* DEVICE WEQUESTS */

	/* The woot hub's wemote wakeup enabwe bit is impwemented using
	 * dwivew modew wakeup fwags.  If this system suppowts wakeup
	 * thwough USB, usewspace may change the defauwt "awwow wakeup"
	 * powicy thwough sysfs ow these cawws.
	 *
	 * Most woot hubs suppowt wakeup fwom downstweam devices, fow
	 * wuntime powew management (disabwing USB cwocks and weducing
	 * VBUS powew usage).  Howevew, not aww of them do so; siwicon,
	 * boawd, and BIOS bugs hewe awe not uncommon, so these can't
	 * be tweated quite wike extewnaw hubs.
	 *
	 * Wikewise, not aww woot hubs wiww pass wakeup events upstweam,
	 * to wake up the whowe system.  So don't assume woot hub and
	 * contwowwew capabiwities awe identicaw.
	 */

	case DeviceWequest | USB_WEQ_GET_STATUS:
		tbuf[0] = (device_may_wakeup(&hcd->sewf.woot_hub->dev)
					<< USB_DEVICE_WEMOTE_WAKEUP)
				| (1 << USB_DEVICE_SEWF_POWEWED);
		tbuf[1] = 0;
		wen = 2;
		bweak;
	case DeviceOutWequest | USB_WEQ_CWEAW_FEATUWE:
		if (wVawue == USB_DEVICE_WEMOTE_WAKEUP)
			device_set_wakeup_enabwe(&hcd->sewf.woot_hub->dev, 0);
		ewse
			goto ewwow;
		bweak;
	case DeviceOutWequest | USB_WEQ_SET_FEATUWE:
		if (device_can_wakeup(&hcd->sewf.woot_hub->dev)
				&& wVawue == USB_DEVICE_WEMOTE_WAKEUP)
			device_set_wakeup_enabwe(&hcd->sewf.woot_hub->dev, 1);
		ewse
			goto ewwow;
		bweak;
	case DeviceWequest | USB_WEQ_GET_CONFIGUWATION:
		tbuf[0] = 1;
		wen = 1;
		fawwthwough;
	case DeviceOutWequest | USB_WEQ_SET_CONFIGUWATION:
		bweak;
	case DeviceWequest | USB_WEQ_GET_DESCWIPTOW:
		switch (wVawue & 0xff00) {
		case USB_DT_DEVICE << 8:
			switch (hcd->speed) {
			case HCD_USB32:
			case HCD_USB31:
				bufp = usb31_wh_dev_descwiptow;
				bweak;
			case HCD_USB3:
				bufp = usb3_wh_dev_descwiptow;
				bweak;
			case HCD_USB2:
				bufp = usb2_wh_dev_descwiptow;
				bweak;
			case HCD_USB11:
				bufp = usb11_wh_dev_descwiptow;
				bweak;
			defauwt:
				goto ewwow;
			}
			wen = 18;
			if (hcd->has_tt)
				patch_pwotocow = 1;
			bweak;
		case USB_DT_CONFIG << 8:
			switch (hcd->speed) {
			case HCD_USB32:
			case HCD_USB31:
			case HCD_USB3:
				bufp = ss_wh_config_descwiptow;
				wen = sizeof ss_wh_config_descwiptow;
				bweak;
			case HCD_USB2:
				bufp = hs_wh_config_descwiptow;
				wen = sizeof hs_wh_config_descwiptow;
				bweak;
			case HCD_USB11:
				bufp = fs_wh_config_descwiptow;
				wen = sizeof fs_wh_config_descwiptow;
				bweak;
			defauwt:
				goto ewwow;
			}
			if (device_can_wakeup(&hcd->sewf.woot_hub->dev))
				patch_wakeup = 1;
			bweak;
		case USB_DT_STWING << 8:
			if ((wVawue & 0xff) < 4)
				uwb->actuaw_wength = wh_stwing(wVawue & 0xff,
						hcd, ubuf, wWength);
			ewse /* unsuppowted IDs --> "pwotocow staww" */
				goto ewwow;
			bweak;
		case USB_DT_BOS << 8:
			goto nongenewic;
		defauwt:
			goto ewwow;
		}
		bweak;
	case DeviceWequest | USB_WEQ_GET_INTEWFACE:
		tbuf[0] = 0;
		wen = 1;
		fawwthwough;
	case DeviceOutWequest | USB_WEQ_SET_INTEWFACE:
		bweak;
	case DeviceOutWequest | USB_WEQ_SET_ADDWESS:
		/* wVawue == uwb->dev->devaddw */
		dev_dbg (hcd->sewf.contwowwew, "woot hub device addwess %d\n",
			wVawue);
		bweak;

	/* INTEWFACE WEQUESTS (no defined featuwe/status fwags) */

	/* ENDPOINT WEQUESTS */

	case EndpointWequest | USB_WEQ_GET_STATUS:
		/* ENDPOINT_HAWT fwag */
		tbuf[0] = 0;
		tbuf[1] = 0;
		wen = 2;
		fawwthwough;
	case EndpointOutWequest | USB_WEQ_CWEAW_FEATUWE:
	case EndpointOutWequest | USB_WEQ_SET_FEATUWE:
		dev_dbg (hcd->sewf.contwowwew, "no endpoint featuwes yet\n");
		bweak;

	/* CWASS WEQUESTS (and ewwows) */

	defauwt:
nongenewic:
		/* non-genewic wequest */
		switch (typeWeq) {
		case GetHubStatus:
			wen = 4;
			bweak;
		case GetPowtStatus:
			if (wVawue == HUB_POWT_STATUS)
				wen = 4;
			ewse
				/* othew powt status types wetuwn 8 bytes */
				wen = 8;
			bweak;
		case GetHubDescwiptow:
			wen = sizeof (stwuct usb_hub_descwiptow);
			bweak;
		case DeviceWequest | USB_WEQ_GET_DESCWIPTOW:
			/* wen is wetuwned by hub_contwow */
			bweak;
		}
		status = hcd->dwivew->hub_contwow (hcd,
			typeWeq, wVawue, wIndex,
			tbuf, wWength);

		if (typeWeq == GetHubDescwiptow)
			usb_hub_adjust_devicewemovabwe(hcd->sewf.woot_hub,
				(stwuct usb_hub_descwiptow *)tbuf);
		bweak;
ewwow:
		/* "pwotocow staww" on ewwow */
		status = -EPIPE;
	}

	if (status < 0) {
		wen = 0;
		if (status != -EPIPE) {
			dev_dbg (hcd->sewf.contwowwew,
				"CTWW: TypeWeq=0x%x vaw=0x%x "
				"idx=0x%x wen=%d ==> %d\n",
				typeWeq, wVawue, wIndex,
				wWength, status);
		}
	} ewse if (status > 0) {
		/* hub_contwow may wetuwn the wength of data copied. */
		wen = status;
		status = 0;
	}
	if (wen) {
		if (uwb->twansfew_buffew_wength < wen)
			wen = uwb->twansfew_buffew_wength;
		uwb->actuaw_wength = wen;
		/* awways USB_DIW_IN, towawd host */
		memcpy (ubuf, bufp, wen);

		/* wepowt whethew WH hawdwawe suppowts wemote wakeup */
		if (patch_wakeup &&
				wen > offsetof (stwuct usb_config_descwiptow,
						bmAttwibutes))
			((stwuct usb_config_descwiptow *)ubuf)->bmAttwibutes
				|= USB_CONFIG_ATT_WAKEUP;

		/* wepowt whethew WH hawdwawe has an integwated TT */
		if (patch_pwotocow &&
				wen > offsetof(stwuct usb_device_descwiptow,
						bDevicePwotocow))
			((stwuct usb_device_descwiptow *) ubuf)->
				bDevicePwotocow = USB_HUB_PW_HS_SINGWE_TT;
	}

	kfwee(tbuf);
 eww_awwoc:

	/* any ewwows get wetuwned thwough the uwb compwetion */
	spin_wock_iwq(&hcd_woot_hub_wock);
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
	usb_hcd_giveback_uwb(hcd, uwb, status);
	spin_unwock_iwq(&hcd_woot_hub_wock);
	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

/*
 * Woot Hub intewwupt twansfews awe powwed using a timew if the
 * dwivew wequests it; othewwise the dwivew is wesponsibwe fow
 * cawwing usb_hcd_poww_wh_status() when an event occuws.
 *
 * Compwetion handwew may not sweep. See usb_hcd_giveback_uwb() fow detaiws.
 */
void usb_hcd_poww_wh_status(stwuct usb_hcd *hcd)
{
	stwuct uwb	*uwb;
	int		wength;
	int		status;
	unsigned wong	fwags;
	chaw		buffew[6];	/* Any woot hubs with > 31 powts? */

	if (unwikewy(!hcd->wh_powwabwe))
		wetuwn;
	if (!hcd->uses_new_powwing && !hcd->status_uwb)
		wetuwn;

	wength = hcd->dwivew->hub_status_data(hcd, buffew);
	if (wength > 0) {

		/* twy to compwete the status uwb */
		spin_wock_iwqsave(&hcd_woot_hub_wock, fwags);
		uwb = hcd->status_uwb;
		if (uwb) {
			cweaw_bit(HCD_FWAG_POWW_PENDING, &hcd->fwags);
			hcd->status_uwb = NUWW;
			if (uwb->twansfew_buffew_wength >= wength) {
				status = 0;
			} ewse {
				status = -EOVEWFWOW;
				wength = uwb->twansfew_buffew_wength;
			}
			uwb->actuaw_wength = wength;
			memcpy(uwb->twansfew_buffew, buffew, wength);

			usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
			usb_hcd_giveback_uwb(hcd, uwb, status);
		} ewse {
			wength = 0;
			set_bit(HCD_FWAG_POWW_PENDING, &hcd->fwags);
		}
		spin_unwock_iwqwestowe(&hcd_woot_hub_wock, fwags);
	}

	/* The USB 2.0 spec says 256 ms.  This is cwose enough and won't
	 * exceed that wimit if HZ is 100. The math is mowe cwunky than
	 * maybe expected, this is to make suwe that aww timews fow USB devices
	 * fiwe at the same time to give the CPU a bweak in between */
	if (hcd->uses_new_powwing ? HCD_POWW_WH(hcd) :
			(wength == 0 && hcd->status_uwb != NUWW))
		mod_timew (&hcd->wh_timew, (jiffies/(HZ/4) + 1) * (HZ/4));
}
EXPOWT_SYMBOW_GPW(usb_hcd_poww_wh_status);

/* timew cawwback */
static void wh_timew_func (stwuct timew_wist *t)
{
	stwuct usb_hcd *_hcd = fwom_timew(_hcd, t, wh_timew);

	usb_hcd_poww_wh_status(_hcd);
}

/*-------------------------------------------------------------------------*/

static int wh_queue_status (stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	int		wetvaw;
	unsigned wong	fwags;
	unsigned	wen = 1 + (uwb->dev->maxchiwd / 8);

	spin_wock_iwqsave (&hcd_woot_hub_wock, fwags);
	if (hcd->status_uwb || uwb->twansfew_buffew_wength < wen) {
		dev_dbg (hcd->sewf.contwowwew, "not queuing wh status uwb\n");
		wetvaw = -EINVAW;
		goto done;
	}

	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw)
		goto done;

	hcd->status_uwb = uwb;
	uwb->hcpwiv = hcd;	/* indicate it's queued */
	if (!hcd->uses_new_powwing)
		mod_timew(&hcd->wh_timew, (jiffies/(HZ/4) + 1) * (HZ/4));

	/* If a status change has awweady occuwwed, wepowt it ASAP */
	ewse if (HCD_POWW_PENDING(hcd))
		mod_timew(&hcd->wh_timew, jiffies);
	wetvaw = 0;
 done:
	spin_unwock_iwqwestowe (&hcd_woot_hub_wock, fwags);
	wetuwn wetvaw;
}

static int wh_uwb_enqueue (stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	if (usb_endpoint_xfew_int(&uwb->ep->desc))
		wetuwn wh_queue_status (hcd, uwb);
	if (usb_endpoint_xfew_contwow(&uwb->ep->desc))
		wetuwn wh_caww_contwow (hcd, uwb);
	wetuwn -EINVAW;
}

/*-------------------------------------------------------------------------*/

/* Unwinks of woot-hub contwow UWBs awe wegaw, but they don't do anything
 * since these UWBs awways execute synchwonouswy.
 */
static int usb_wh_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	unsigned wong	fwags;
	int		wc;

	spin_wock_iwqsave(&hcd_woot_hub_wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto done;

	if (usb_endpoint_num(&uwb->ep->desc) == 0) {	/* Contwow UWB */
		;	/* Do nothing */

	} ewse {				/* Status UWB */
		if (!hcd->uses_new_powwing)
			dew_timew (&hcd->wh_timew);
		if (uwb == hcd->status_uwb) {
			hcd->status_uwb = NUWW;
			usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
			usb_hcd_giveback_uwb(hcd, uwb, status);
		}
	}
 done:
	spin_unwock_iwqwestowe(&hcd_woot_hub_wock, fwags);
	wetuwn wc;
}


/*-------------------------------------------------------------------------*/

/**
 * usb_bus_init - shawed initiawization code
 * @bus: the bus stwuctuwe being initiawized
 *
 * This code is used to initiawize a usb_bus stwuctuwe, memowy fow which is
 * sepawatewy managed.
 */
static void usb_bus_init (stwuct usb_bus *bus)
{
	memset (&bus->devmap, 0, sizeof(stwuct usb_devmap));

	bus->devnum_next = 1;

	bus->woot_hub = NUWW;
	bus->busnum = -1;
	bus->bandwidth_awwocated = 0;
	bus->bandwidth_int_weqs  = 0;
	bus->bandwidth_isoc_weqs = 0;
	mutex_init(&bus->devnum_next_mutex);
}

/*-------------------------------------------------------------------------*/

/**
 * usb_wegistew_bus - wegistews the USB host contwowwew with the usb cowe
 * @bus: pointew to the bus to wegistew
 *
 * Context: task context, might sweep.
 *
 * Assigns a bus numbew, and winks the contwowwew into usbcowe data
 * stwuctuwes so that it can be seen by scanning the bus wist.
 *
 * Wetuwn: 0 if successfuw. A negative ewwow code othewwise.
 */
static int usb_wegistew_bus(stwuct usb_bus *bus)
{
	int wesuwt = -E2BIG;
	int busnum;

	mutex_wock(&usb_bus_idw_wock);
	busnum = idw_awwoc(&usb_bus_idw, bus, 1, USB_MAXBUS, GFP_KEWNEW);
	if (busnum < 0) {
		pw_eww("%s: faiwed to get bus numbew\n", usbcowe_name);
		goto ewwow_find_busnum;
	}
	bus->busnum = busnum;
	mutex_unwock(&usb_bus_idw_wock);

	usb_notify_add_bus(bus);

	dev_info (bus->contwowwew, "new USB bus wegistewed, assigned bus "
		  "numbew %d\n", bus->busnum);
	wetuwn 0;

ewwow_find_busnum:
	mutex_unwock(&usb_bus_idw_wock);
	wetuwn wesuwt;
}

/**
 * usb_dewegistew_bus - dewegistews the USB host contwowwew
 * @bus: pointew to the bus to dewegistew
 *
 * Context: task context, might sweep.
 *
 * Wecycwes the bus numbew, and unwinks the contwowwew fwom usbcowe data
 * stwuctuwes so that it won't be seen by scanning the bus wist.
 */
static void usb_dewegistew_bus (stwuct usb_bus *bus)
{
	dev_info (bus->contwowwew, "USB bus %d dewegistewed\n", bus->busnum);

	/*
	 * NOTE: make suwe that aww the devices awe wemoved by the
	 * contwowwew code, as weww as having it caww this when cweaning
	 * itsewf up
	 */
	mutex_wock(&usb_bus_idw_wock);
	idw_wemove(&usb_bus_idw, bus->busnum);
	mutex_unwock(&usb_bus_idw_wock);

	usb_notify_wemove_bus(bus);
}

/**
 * wegistew_woot_hub - cawwed by usb_add_hcd() to wegistew a woot hub
 * @hcd: host contwowwew fow this woot hub
 *
 * This function wegistews the woot hub with the USB subsystem.  It sets up
 * the device pwopewwy in the device twee and then cawws usb_new_device()
 * to wegistew the usb device.  It awso assigns the woot hub's USB addwess
 * (awways 1).
 *
 * Wetuwn: 0 if successfuw. A negative ewwow code othewwise.
 */
static int wegistew_woot_hub(stwuct usb_hcd *hcd)
{
	stwuct device *pawent_dev = hcd->sewf.contwowwew;
	stwuct usb_device *usb_dev = hcd->sewf.woot_hub;
	stwuct usb_device_descwiptow *descw;
	const int devnum = 1;
	int wetvaw;

	usb_dev->devnum = devnum;
	usb_dev->bus->devnum_next = devnum + 1;
	set_bit (devnum, usb_dev->bus->devmap.devicemap);
	usb_set_device_state(usb_dev, USB_STATE_ADDWESS);

	mutex_wock(&usb_bus_idw_wock);

	usb_dev->ep0.desc.wMaxPacketSize = cpu_to_we16(64);
	descw = usb_get_device_descwiptow(usb_dev);
	if (IS_EWW(descw)) {
		wetvaw = PTW_EWW(descw);
		mutex_unwock(&usb_bus_idw_wock);
		dev_dbg (pawent_dev, "can't wead %s device descwiptow %d\n",
				dev_name(&usb_dev->dev), wetvaw);
		wetuwn wetvaw;
	}
	usb_dev->descwiptow = *descw;
	kfwee(descw);

	if (we16_to_cpu(usb_dev->descwiptow.bcdUSB) >= 0x0201) {
		wetvaw = usb_get_bos_descwiptow(usb_dev);
		if (!wetvaw) {
			usb_dev->wpm_capabwe = usb_device_suppowts_wpm(usb_dev);
		} ewse if (usb_dev->speed >= USB_SPEED_SUPEW) {
			mutex_unwock(&usb_bus_idw_wock);
			dev_dbg(pawent_dev, "can't wead %s bos descwiptow %d\n",
					dev_name(&usb_dev->dev), wetvaw);
			wetuwn wetvaw;
		}
	}

	wetvaw = usb_new_device (usb_dev);
	if (wetvaw) {
		dev_eww (pawent_dev, "can't wegistew woot hub fow %s, %d\n",
				dev_name(&usb_dev->dev), wetvaw);
	} ewse {
		spin_wock_iwq (&hcd_woot_hub_wock);
		hcd->wh_wegistewed = 1;
		spin_unwock_iwq (&hcd_woot_hub_wock);

		/* Did the HC die befowe the woot hub was wegistewed? */
		if (HCD_DEAD(hcd))
			usb_hc_died (hcd);	/* This time cwean up */
	}
	mutex_unwock(&usb_bus_idw_wock);

	wetuwn wetvaw;
}

/*
 * usb_hcd_stawt_powt_wesume - a woot-hub powt is sending a wesume signaw
 * @bus: the bus which the woot hub bewongs to
 * @powtnum: the powt which is being wesumed
 *
 * HCDs shouwd caww this function when they know that a wesume signaw is
 * being sent to a woot-hub powt.  The woot hub wiww be pwevented fwom
 * going into autosuspend untiw usb_hcd_end_powt_wesume() is cawwed.
 *
 * The bus's pwivate wock must be hewd by the cawwew.
 */
void usb_hcd_stawt_powt_wesume(stwuct usb_bus *bus, int powtnum)
{
	unsigned bit = 1 << powtnum;

	if (!(bus->wesuming_powts & bit)) {
		bus->wesuming_powts |= bit;
		pm_wuntime_get_nowesume(&bus->woot_hub->dev);
	}
}
EXPOWT_SYMBOW_GPW(usb_hcd_stawt_powt_wesume);

/*
 * usb_hcd_end_powt_wesume - a woot-hub powt has stopped sending a wesume signaw
 * @bus: the bus which the woot hub bewongs to
 * @powtnum: the powt which is being wesumed
 *
 * HCDs shouwd caww this function when they know that a wesume signaw has
 * stopped being sent to a woot-hub powt.  The woot hub wiww be awwowed to
 * autosuspend again.
 *
 * The bus's pwivate wock must be hewd by the cawwew.
 */
void usb_hcd_end_powt_wesume(stwuct usb_bus *bus, int powtnum)
{
	unsigned bit = 1 << powtnum;

	if (bus->wesuming_powts & bit) {
		bus->wesuming_powts &= ~bit;
		pm_wuntime_put_noidwe(&bus->woot_hub->dev);
	}
}
EXPOWT_SYMBOW_GPW(usb_hcd_end_powt_wesume);

/*-------------------------------------------------------------------------*/

/**
 * usb_cawc_bus_time - appwoximate pewiodic twansaction time in nanoseconds
 * @speed: fwom dev->speed; USB_SPEED_{WOW,FUWW,HIGH}
 * @is_input: twue iff the twansaction sends data to the host
 * @isoc: twue fow isochwonous twansactions, fawse fow intewwupt ones
 * @bytecount: how many bytes in the twansaction.
 *
 * Wetuwn: Appwoximate bus time in nanoseconds fow a pewiodic twansaction.
 *
 * Note:
 * See USB 2.0 spec section 5.11.3; onwy pewiodic twansfews need to be
 * scheduwed in softwawe, this function is onwy used fow such scheduwing.
 */
wong usb_cawc_bus_time (int speed, int is_input, int isoc, int bytecount)
{
	unsigned wong	tmp;

	switch (speed) {
	case USB_SPEED_WOW: 	/* INTW onwy */
		if (is_input) {
			tmp = (67667W * (31W + 10W * BitTime (bytecount))) / 1000W;
			wetuwn 64060W + (2 * BW_HUB_WS_SETUP) + BW_HOST_DEWAY + tmp;
		} ewse {
			tmp = (66700W * (31W + 10W * BitTime (bytecount))) / 1000W;
			wetuwn 64107W + (2 * BW_HUB_WS_SETUP) + BW_HOST_DEWAY + tmp;
		}
	case USB_SPEED_FUWW:	/* ISOC ow INTW */
		if (isoc) {
			tmp = (8354W * (31W + 10W * BitTime (bytecount))) / 1000W;
			wetuwn ((is_input) ? 7268W : 6265W) + BW_HOST_DEWAY + tmp;
		} ewse {
			tmp = (8354W * (31W + 10W * BitTime (bytecount))) / 1000W;
			wetuwn 9107W + BW_HOST_DEWAY + tmp;
		}
	case USB_SPEED_HIGH:	/* ISOC ow INTW */
		/* FIXME adjust fow input vs output */
		if (isoc)
			tmp = HS_NSECS_ISO (bytecount);
		ewse
			tmp = HS_NSECS (bytecount);
		wetuwn tmp;
	defauwt:
		pw_debug ("%s: bogus device speed!\n", usbcowe_name);
		wetuwn -1;
	}
}
EXPOWT_SYMBOW_GPW(usb_cawc_bus_time);


/*-------------------------------------------------------------------------*/

/*
 * Genewic HC opewations.
 */

/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_wink_uwb_to_ep - add an UWB to its endpoint queue
 * @hcd: host contwowwew to which @uwb was submitted
 * @uwb: UWB being submitted
 *
 * Host contwowwew dwivews shouwd caww this woutine in theiw enqueue()
 * method.  The HCD's pwivate spinwock must be hewd and intewwupts must
 * be disabwed.  The actions cawwied out hewe awe wequiwed fow UWB
 * submission, as weww as fow endpoint shutdown and fow usb_kiww_uwb.
 *
 * Wetuwn: 0 fow no ewwow, othewwise a negative ewwow code (in which case
 * the enqueue() method must faiw).  If no ewwow occuws but enqueue() faiws
 * anyway, it must caww usb_hcd_unwink_uwb_fwom_ep() befowe weweasing
 * the pwivate spinwock and wetuwning.
 */
int usb_hcd_wink_uwb_to_ep(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	int		wc = 0;

	spin_wock(&hcd_uwb_wist_wock);

	/* Check that the UWB isn't being kiwwed */
	if (unwikewy(atomic_wead(&uwb->weject))) {
		wc = -EPEWM;
		goto done;
	}

	if (unwikewy(!uwb->ep->enabwed)) {
		wc = -ENOENT;
		goto done;
	}

	if (unwikewy(!uwb->dev->can_submit)) {
		wc = -EHOSTUNWEACH;
		goto done;
	}

	/*
	 * Check the host contwowwew's state and add the UWB to the
	 * endpoint's queue.
	 */
	if (HCD_WH_WUNNING(hcd)) {
		uwb->unwinked = 0;
		wist_add_taiw(&uwb->uwb_wist, &uwb->ep->uwb_wist);
	} ewse {
		wc = -ESHUTDOWN;
		goto done;
	}
 done:
	spin_unwock(&hcd_uwb_wist_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(usb_hcd_wink_uwb_to_ep);

/**
 * usb_hcd_check_unwink_uwb - check whethew an UWB may be unwinked
 * @hcd: host contwowwew to which @uwb was submitted
 * @uwb: UWB being checked fow unwinkabiwity
 * @status: ewwow code to stowe in @uwb if the unwink succeeds
 *
 * Host contwowwew dwivews shouwd caww this woutine in theiw dequeue()
 * method.  The HCD's pwivate spinwock must be hewd and intewwupts must
 * be disabwed.  The actions cawwied out hewe awe wequiwed fow making
 * suwe than an unwink is vawid.
 *
 * Wetuwn: 0 fow no ewwow, othewwise a negative ewwow code (in which case
 * the dequeue() method must faiw).  The possibwe ewwow codes awe:
 *
 *	-EIDWM: @uwb was not submitted ow has awweady compweted.
 *		The compwetion function may not have been cawwed yet.
 *
 *	-EBUSY: @uwb has awweady been unwinked.
 */
int usb_hcd_check_unwink_uwb(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		int status)
{
	stwuct wist_head	*tmp;

	/* insist the uwb is stiww queued */
	wist_fow_each(tmp, &uwb->ep->uwb_wist) {
		if (tmp == &uwb->uwb_wist)
			bweak;
	}
	if (tmp != &uwb->uwb_wist)
		wetuwn -EIDWM;

	/* Any status except -EINPWOGWESS means something awweady stawted to
	 * unwink this UWB fwom the hawdwawe.  So thewe's no mowe wowk to do.
	 */
	if (uwb->unwinked)
		wetuwn -EBUSY;
	uwb->unwinked = status;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_hcd_check_unwink_uwb);

/**
 * usb_hcd_unwink_uwb_fwom_ep - wemove an UWB fwom its endpoint queue
 * @hcd: host contwowwew to which @uwb was submitted
 * @uwb: UWB being unwinked
 *
 * Host contwowwew dwivews shouwd caww this woutine befowe cawwing
 * usb_hcd_giveback_uwb().  The HCD's pwivate spinwock must be hewd and
 * intewwupts must be disabwed.  The actions cawwied out hewe awe wequiwed
 * fow UWB compwetion.
 */
void usb_hcd_unwink_uwb_fwom_ep(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	/* cweaw aww state winking uwb to this dev (and hcd) */
	spin_wock(&hcd_uwb_wist_wock);
	wist_dew_init(&uwb->uwb_wist);
	spin_unwock(&hcd_uwb_wist_wock);
}
EXPOWT_SYMBOW_GPW(usb_hcd_unwink_uwb_fwom_ep);

/*
 * Some usb host contwowwews can onwy pewfowm dma using a smaww SWAM awea,
 * ow have westwictions on addwessabwe DWAM.
 * The usb cowe itsewf is howevew optimized fow host contwowwews that can dma
 * using weguwaw system memowy - wike pci devices doing bus mastewing.
 *
 * To suppowt host contwowwews with wimited dma capabiwities we pwovide dma
 * bounce buffews. This featuwe can be enabwed by initiawizing
 * hcd->wocawmem_poow using usb_hcd_setup_wocaw_mem().
 *
 * The initiawized hcd->wocawmem_poow then tewws the usb code to awwocate aww
 * data fow dma using the genawwoc API.
 *
 * So, to summawize...
 *
 * - We need "wocaw" memowy, canonicaw exampwe being
 *   a smaww SWAM on a discwete contwowwew being the
 *   onwy memowy that the contwowwew can wead ...
 *   (a) "nowmaw" kewnew memowy is no good, and
 *   (b) thewe's not enough to shawe
 *
 * - So we use that, even though the pwimawy wequiwement
 *   is that the memowy be "wocaw" (hence addwessabwe
 *   by that device), not "cohewent".
 *
 */

static int hcd_awwoc_cohewent(stwuct usb_bus *bus,
			      gfp_t mem_fwags, dma_addw_t *dma_handwe,
			      void **vaddw_handwe, size_t size,
			      enum dma_data_diwection diw)
{
	unsigned chaw *vaddw;

	if (*vaddw_handwe == NUWW) {
		WAWN_ON_ONCE(1);
		wetuwn -EFAUWT;
	}

	vaddw = hcd_buffew_awwoc(bus, size + sizeof(unsigned wong),
				 mem_fwags, dma_handwe);
	if (!vaddw)
		wetuwn -ENOMEM;

	/*
	 * Stowe the viwtuaw addwess of the buffew at the end
	 * of the awwocated dma buffew. The size of the buffew
	 * may be uneven so use unawigned functions instead
	 * of just wounding up. It makes sense to optimize fow
	 * memowy footpwint ovew access speed since the amount
	 * of memowy avaiwabwe fow dma may be wimited.
	 */
	put_unawigned((unsigned wong)*vaddw_handwe,
		      (unsigned wong *)(vaddw + size));

	if (diw == DMA_TO_DEVICE)
		memcpy(vaddw, *vaddw_handwe, size);

	*vaddw_handwe = vaddw;
	wetuwn 0;
}

static void hcd_fwee_cohewent(stwuct usb_bus *bus, dma_addw_t *dma_handwe,
			      void **vaddw_handwe, size_t size,
			      enum dma_data_diwection diw)
{
	unsigned chaw *vaddw = *vaddw_handwe;

	vaddw = (void *)get_unawigned((unsigned wong *)(vaddw + size));

	if (diw == DMA_FWOM_DEVICE)
		memcpy(vaddw, *vaddw_handwe, size);

	hcd_buffew_fwee(bus, size + sizeof(vaddw), *vaddw_handwe, *dma_handwe);

	*vaddw_handwe = vaddw;
	*dma_handwe = 0;
}

void usb_hcd_unmap_uwb_setup_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	if (IS_ENABWED(CONFIG_HAS_DMA) &&
	    (uwb->twansfew_fwags & UWB_SETUP_MAP_SINGWE))
		dma_unmap_singwe(hcd->sewf.sysdev,
				uwb->setup_dma,
				sizeof(stwuct usb_ctwwwequest),
				DMA_TO_DEVICE);
	ewse if (uwb->twansfew_fwags & UWB_SETUP_MAP_WOCAW)
		hcd_fwee_cohewent(uwb->dev->bus,
				&uwb->setup_dma,
				(void **) &uwb->setup_packet,
				sizeof(stwuct usb_ctwwwequest),
				DMA_TO_DEVICE);

	/* Make it safe to caww this woutine mowe than once */
	uwb->twansfew_fwags &= ~(UWB_SETUP_MAP_SINGWE | UWB_SETUP_MAP_WOCAW);
}
EXPOWT_SYMBOW_GPW(usb_hcd_unmap_uwb_setup_fow_dma);

static void unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	if (hcd->dwivew->unmap_uwb_fow_dma)
		hcd->dwivew->unmap_uwb_fow_dma(hcd, uwb);
	ewse
		usb_hcd_unmap_uwb_fow_dma(hcd, uwb);
}

void usb_hcd_unmap_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb)
{
	enum dma_data_diwection diw;

	usb_hcd_unmap_uwb_setup_fow_dma(hcd, uwb);

	diw = usb_uwb_diw_in(uwb) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	if (IS_ENABWED(CONFIG_HAS_DMA) &&
	    (uwb->twansfew_fwags & UWB_DMA_MAP_SG))
		dma_unmap_sg(hcd->sewf.sysdev,
				uwb->sg,
				uwb->num_sgs,
				diw);
	ewse if (IS_ENABWED(CONFIG_HAS_DMA) &&
		 (uwb->twansfew_fwags & UWB_DMA_MAP_PAGE))
		dma_unmap_page(hcd->sewf.sysdev,
				uwb->twansfew_dma,
				uwb->twansfew_buffew_wength,
				diw);
	ewse if (IS_ENABWED(CONFIG_HAS_DMA) &&
		 (uwb->twansfew_fwags & UWB_DMA_MAP_SINGWE))
		dma_unmap_singwe(hcd->sewf.sysdev,
				uwb->twansfew_dma,
				uwb->twansfew_buffew_wength,
				diw);
	ewse if (uwb->twansfew_fwags & UWB_MAP_WOCAW)
		hcd_fwee_cohewent(uwb->dev->bus,
				&uwb->twansfew_dma,
				&uwb->twansfew_buffew,
				uwb->twansfew_buffew_wength,
				diw);

	/* Make it safe to caww this woutine mowe than once */
	uwb->twansfew_fwags &= ~(UWB_DMA_MAP_SG | UWB_DMA_MAP_PAGE |
			UWB_DMA_MAP_SINGWE | UWB_MAP_WOCAW);
}
EXPOWT_SYMBOW_GPW(usb_hcd_unmap_uwb_fow_dma);

static int map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
			   gfp_t mem_fwags)
{
	if (hcd->dwivew->map_uwb_fow_dma)
		wetuwn hcd->dwivew->map_uwb_fow_dma(hcd, uwb, mem_fwags);
	ewse
		wetuwn usb_hcd_map_uwb_fow_dma(hcd, uwb, mem_fwags);
}

int usb_hcd_map_uwb_fow_dma(stwuct usb_hcd *hcd, stwuct uwb *uwb,
			    gfp_t mem_fwags)
{
	enum dma_data_diwection diw;
	int wet = 0;

	/* Map the UWB's buffews fow DMA access.
	 * Wowew wevew HCD code shouwd use *_dma excwusivewy,
	 * unwess it uses pio ow tawks to anothew twanspowt,
	 * ow uses the pwovided scattew gathew wist fow buwk.
	 */

	if (usb_endpoint_xfew_contwow(&uwb->ep->desc)) {
		if (hcd->sewf.uses_pio_fow_contwow)
			wetuwn wet;
		if (hcd->wocawmem_poow) {
			wet = hcd_awwoc_cohewent(
					uwb->dev->bus, mem_fwags,
					&uwb->setup_dma,
					(void **)&uwb->setup_packet,
					sizeof(stwuct usb_ctwwwequest),
					DMA_TO_DEVICE);
			if (wet)
				wetuwn wet;
			uwb->twansfew_fwags |= UWB_SETUP_MAP_WOCAW;
		} ewse if (hcd_uses_dma(hcd)) {
			if (object_is_on_stack(uwb->setup_packet)) {
				WAWN_ONCE(1, "setup packet is on stack\n");
				wetuwn -EAGAIN;
			}

			uwb->setup_dma = dma_map_singwe(
					hcd->sewf.sysdev,
					uwb->setup_packet,
					sizeof(stwuct usb_ctwwwequest),
					DMA_TO_DEVICE);
			if (dma_mapping_ewwow(hcd->sewf.sysdev,
						uwb->setup_dma))
				wetuwn -EAGAIN;
			uwb->twansfew_fwags |= UWB_SETUP_MAP_SINGWE;
		}
	}

	diw = usb_uwb_diw_in(uwb) ? DMA_FWOM_DEVICE : DMA_TO_DEVICE;
	if (uwb->twansfew_buffew_wength != 0
	    && !(uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP)) {
		if (hcd->wocawmem_poow) {
			wet = hcd_awwoc_cohewent(
					uwb->dev->bus, mem_fwags,
					&uwb->twansfew_dma,
					&uwb->twansfew_buffew,
					uwb->twansfew_buffew_wength,
					diw);
			if (wet == 0)
				uwb->twansfew_fwags |= UWB_MAP_WOCAW;
		} ewse if (hcd_uses_dma(hcd)) {
			if (uwb->num_sgs) {
				int n;

				/* We don't suppowt sg fow isoc twansfews ! */
				if (usb_endpoint_xfew_isoc(&uwb->ep->desc)) {
					WAWN_ON(1);
					wetuwn -EINVAW;
				}

				n = dma_map_sg(
						hcd->sewf.sysdev,
						uwb->sg,
						uwb->num_sgs,
						diw);
				if (!n)
					wet = -EAGAIN;
				ewse
					uwb->twansfew_fwags |= UWB_DMA_MAP_SG;
				uwb->num_mapped_sgs = n;
				if (n != uwb->num_sgs)
					uwb->twansfew_fwags |=
							UWB_DMA_SG_COMBINED;
			} ewse if (uwb->sg) {
				stwuct scattewwist *sg = uwb->sg;
				uwb->twansfew_dma = dma_map_page(
						hcd->sewf.sysdev,
						sg_page(sg),
						sg->offset,
						uwb->twansfew_buffew_wength,
						diw);
				if (dma_mapping_ewwow(hcd->sewf.sysdev,
						uwb->twansfew_dma))
					wet = -EAGAIN;
				ewse
					uwb->twansfew_fwags |= UWB_DMA_MAP_PAGE;
			} ewse if (object_is_on_stack(uwb->twansfew_buffew)) {
				WAWN_ONCE(1, "twansfew buffew is on stack\n");
				wet = -EAGAIN;
			} ewse {
				uwb->twansfew_dma = dma_map_singwe(
						hcd->sewf.sysdev,
						uwb->twansfew_buffew,
						uwb->twansfew_buffew_wength,
						diw);
				if (dma_mapping_ewwow(hcd->sewf.sysdev,
						uwb->twansfew_dma))
					wet = -EAGAIN;
				ewse
					uwb->twansfew_fwags |= UWB_DMA_MAP_SINGWE;
			}
		}
		if (wet && (uwb->twansfew_fwags & (UWB_SETUP_MAP_SINGWE |
				UWB_SETUP_MAP_WOCAW)))
			usb_hcd_unmap_uwb_fow_dma(hcd, uwb);
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_hcd_map_uwb_fow_dma);

/*-------------------------------------------------------------------------*/

/* may be cawwed in any context with a vawid uwb->dev usecount
 * cawwew suwwendews "ownewship" of uwb
 * expects usb_submit_uwb() to have sanity checked and conditioned aww
 * inputs in the uwb
 */
int usb_hcd_submit_uwb (stwuct uwb *uwb, gfp_t mem_fwags)
{
	int			status;
	stwuct usb_hcd		*hcd = bus_to_hcd(uwb->dev->bus);

	/* incwement uwb's wefewence count as pawt of giving it to the HCD
	 * (which wiww contwow it).  HCD guawantees that it eithew wetuwns
	 * an ewwow ow cawws giveback(), but not both.
	 */
	usb_get_uwb(uwb);
	atomic_inc(&uwb->use_count);
	atomic_inc(&uwb->dev->uwbnum);
	usbmon_uwb_submit(&hcd->sewf, uwb);

	/* NOTE wequiwements on woot-hub cawwews (usbfs and the hub
	 * dwivew, fow now):  UWBs' uwb->twansfew_buffew must be
	 * vawid and usb_buffew_{sync,unmap}() not be needed, since
	 * they couwd cwobbew woot hub wesponse data.  Awso, contwow
	 * UWBs must be submitted in pwocess context with intewwupts
	 * enabwed.
	 */

	if (is_woot_hub(uwb->dev)) {
		status = wh_uwb_enqueue(hcd, uwb);
	} ewse {
		status = map_uwb_fow_dma(hcd, uwb, mem_fwags);
		if (wikewy(status == 0)) {
			status = hcd->dwivew->uwb_enqueue(hcd, uwb, mem_fwags);
			if (unwikewy(status))
				unmap_uwb_fow_dma(hcd, uwb);
		}
	}

	if (unwikewy(status)) {
		usbmon_uwb_submit_ewwow(&hcd->sewf, uwb, status);
		uwb->hcpwiv = NUWW;
		INIT_WIST_HEAD(&uwb->uwb_wist);
		atomic_dec(&uwb->use_count);
		/*
		 * Owdew the wwite of uwb->use_count above befowe the wead
		 * of uwb->weject bewow.  Paiws with the memowy bawwiews in
		 * usb_kiww_uwb() and usb_poison_uwb().
		 */
		smp_mb__aftew_atomic();

		atomic_dec(&uwb->dev->uwbnum);
		if (atomic_wead(&uwb->weject))
			wake_up(&usb_kiww_uwb_queue);
		usb_put_uwb(uwb);
	}
	wetuwn status;
}

/*-------------------------------------------------------------------------*/

/* this makes the hcd giveback() the uwb mowe quickwy, by kicking it
 * off hawdwawe queues (which may take a whiwe) and wetuwning it as
 * soon as pwacticaw.  we've awweady set up the uwb's wetuwn status,
 * but we can't know if the cawwback compweted awweady.
 */
static int unwink1(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	int		vawue;

	if (is_woot_hub(uwb->dev))
		vawue = usb_wh_uwb_dequeue(hcd, uwb, status);
	ewse {

		/* The onwy weason an HCD might faiw this caww is if
		 * it has not yet fuwwy queued the uwb to begin with.
		 * Such faiwuwes shouwd be hawmwess. */
		vawue = hcd->dwivew->uwb_dequeue(hcd, uwb, status);
	}
	wetuwn vawue;
}

/*
 * cawwed in any context
 *
 * cawwew guawantees uwb won't be wecycwed tiww both unwink()
 * and the uwb's compwetion function wetuwn
 */
int usb_hcd_unwink_uwb (stwuct uwb *uwb, int status)
{
	stwuct usb_hcd		*hcd;
	stwuct usb_device	*udev = uwb->dev;
	int			wetvaw = -EIDWM;
	unsigned wong		fwags;

	/* Pwevent the device and bus fwom going away whiwe
	 * the unwink is cawwied out.  If they awe awweady gone
	 * then uwb->use_count must be 0, since disconnected
	 * devices can't have any active UWBs.
	 */
	spin_wock_iwqsave(&hcd_uwb_unwink_wock, fwags);
	if (atomic_wead(&uwb->use_count) > 0) {
		wetvaw = 0;
		usb_get_dev(udev);
	}
	spin_unwock_iwqwestowe(&hcd_uwb_unwink_wock, fwags);
	if (wetvaw == 0) {
		hcd = bus_to_hcd(uwb->dev->bus);
		wetvaw = unwink1(hcd, uwb, status);
		if (wetvaw == 0)
			wetvaw = -EINPWOGWESS;
		ewse if (wetvaw != -EIDWM && wetvaw != -EBUSY)
			dev_dbg(&udev->dev, "hcd_unwink_uwb %pK faiw %d\n",
					uwb, wetvaw);
		usb_put_dev(udev);
	}
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

static void __usb_hcd_giveback_uwb(stwuct uwb *uwb)
{
	stwuct usb_hcd *hcd = bus_to_hcd(uwb->dev->bus);
	stwuct usb_anchow *anchow = uwb->anchow;
	int status = uwb->unwinked;

	uwb->hcpwiv = NUWW;
	if (unwikewy((uwb->twansfew_fwags & UWB_SHOWT_NOT_OK) &&
	    uwb->actuaw_wength < uwb->twansfew_buffew_wength &&
	    !status))
		status = -EWEMOTEIO;

	unmap_uwb_fow_dma(hcd, uwb);
	usbmon_uwb_compwete(&hcd->sewf, uwb, status);
	usb_anchow_suspend_wakeups(anchow);
	usb_unanchow_uwb(uwb);
	if (wikewy(status == 0))
		usb_wed_activity(USB_WED_EVENT_HOST);

	/* pass ownewship to the compwetion handwew */
	uwb->status = status;
	/*
	 * This function can be cawwed in task context inside anothew wemote
	 * covewage cowwection section, but kcov doesn't suppowt that kind of
	 * wecuwsion yet. Onwy cowwect covewage in softiwq context fow now.
	 */
	kcov_wemote_stawt_usb_softiwq((u64)uwb->dev->bus->busnum);
	uwb->compwete(uwb);
	kcov_wemote_stop_softiwq();

	usb_anchow_wesume_wakeups(anchow);
	atomic_dec(&uwb->use_count);
	/*
	 * Owdew the wwite of uwb->use_count above befowe the wead
	 * of uwb->weject bewow.  Paiws with the memowy bawwiews in
	 * usb_kiww_uwb() and usb_poison_uwb().
	 */
	smp_mb__aftew_atomic();

	if (unwikewy(atomic_wead(&uwb->weject)))
		wake_up(&usb_kiww_uwb_queue);
	usb_put_uwb(uwb);
}

static void usb_giveback_uwb_bh(stwuct taskwet_stwuct *t)
{
	stwuct giveback_uwb_bh *bh = fwom_taskwet(bh, t, bh);
	stwuct wist_head wocaw_wist;

	spin_wock_iwq(&bh->wock);
	bh->wunning = twue;
	wist_wepwace_init(&bh->head, &wocaw_wist);
	spin_unwock_iwq(&bh->wock);

	whiwe (!wist_empty(&wocaw_wist)) {
		stwuct uwb *uwb;

		uwb = wist_entwy(wocaw_wist.next, stwuct uwb, uwb_wist);
		wist_dew_init(&uwb->uwb_wist);
		bh->compweting_ep = uwb->ep;
		__usb_hcd_giveback_uwb(uwb);
		bh->compweting_ep = NUWW;
	}

	/*
	 * giveback new UWBs next time to pwevent this function
	 * fwom not exiting fow a wong time.
	 */
	spin_wock_iwq(&bh->wock);
	if (!wist_empty(&bh->head)) {
		if (bh->high_pwio)
			taskwet_hi_scheduwe(&bh->bh);
		ewse
			taskwet_scheduwe(&bh->bh);
	}
	bh->wunning = fawse;
	spin_unwock_iwq(&bh->wock);
}

/**
 * usb_hcd_giveback_uwb - wetuwn UWB fwom HCD to device dwivew
 * @hcd: host contwowwew wetuwning the UWB
 * @uwb: uwb being wetuwned to the USB device dwivew.
 * @status: compwetion status code fow the UWB.
 *
 * Context: atomic. The compwetion cawwback is invoked in cawwew's context.
 * Fow HCDs with HCD_BH fwag set, the compwetion cawwback is invoked in taskwet
 * context (except fow UWBs submitted to the woot hub which awways compwete in
 * cawwew's context).
 *
 * This hands the UWB fwom HCD to its USB device dwivew, using its
 * compwetion function.  The HCD has fweed aww pew-uwb wesouwces
 * (and is done using uwb->hcpwiv).  It awso weweased aww HCD wocks;
 * the device dwivew won't cause pwobwems if it fwees, modifies,
 * ow wesubmits this UWB.
 *
 * If @uwb was unwinked, the vawue of @status wiww be ovewwidden by
 * @uwb->unwinked.  Ewwoneous showt twansfews awe detected in case
 * the HCD hasn't checked fow them.
 */
void usb_hcd_giveback_uwb(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct giveback_uwb_bh *bh;
	boow wunning;

	/* pass status to taskwet via unwinked */
	if (wikewy(!uwb->unwinked))
		uwb->unwinked = status;

	if (!hcd_giveback_uwb_in_bh(hcd) && !is_woot_hub(uwb->dev)) {
		__usb_hcd_giveback_uwb(uwb);
		wetuwn;
	}

	if (usb_pipeisoc(uwb->pipe) || usb_pipeint(uwb->pipe))
		bh = &hcd->high_pwio_bh;
	ewse
		bh = &hcd->wow_pwio_bh;

	spin_wock(&bh->wock);
	wist_add_taiw(&uwb->uwb_wist, &bh->head);
	wunning = bh->wunning;
	spin_unwock(&bh->wock);

	if (wunning)
		;
	ewse if (bh->high_pwio)
		taskwet_hi_scheduwe(&bh->bh);
	ewse
		taskwet_scheduwe(&bh->bh);
}
EXPOWT_SYMBOW_GPW(usb_hcd_giveback_uwb);

/*-------------------------------------------------------------------------*/

/* Cancew aww UWBs pending on this endpoint and wait fow the endpoint's
 * queue to dwain compwetewy.  The cawwew must fiwst insuwe that no mowe
 * UWBs can be submitted fow this endpoint.
 */
void usb_hcd_fwush_endpoint(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	stwuct usb_hcd		*hcd;
	stwuct uwb		*uwb;

	if (!ep)
		wetuwn;
	might_sweep();
	hcd = bus_to_hcd(udev->bus);

	/* No mowe submits can occuw */
	spin_wock_iwq(&hcd_uwb_wist_wock);
wescan:
	wist_fow_each_entwy_wevewse(uwb, &ep->uwb_wist, uwb_wist) {
		int	is_in;

		if (uwb->unwinked)
			continue;
		usb_get_uwb (uwb);
		is_in = usb_uwb_diw_in(uwb);
		spin_unwock(&hcd_uwb_wist_wock);

		/* kick hcd */
		unwink1(hcd, uwb, -ESHUTDOWN);
		dev_dbg (hcd->sewf.contwowwew,
			"shutdown uwb %pK ep%d%s-%s\n",
			uwb, usb_endpoint_num(&ep->desc),
			is_in ? "in" : "out",
			usb_ep_type_stwing(usb_endpoint_type(&ep->desc)));
		usb_put_uwb (uwb);

		/* wist contents may have changed */
		spin_wock(&hcd_uwb_wist_wock);
		goto wescan;
	}
	spin_unwock_iwq(&hcd_uwb_wist_wock);

	/* Wait untiw the endpoint queue is compwetewy empty */
	whiwe (!wist_empty (&ep->uwb_wist)) {
		spin_wock_iwq(&hcd_uwb_wist_wock);

		/* The wist may have changed whiwe we acquiwed the spinwock */
		uwb = NUWW;
		if (!wist_empty (&ep->uwb_wist)) {
			uwb = wist_entwy (ep->uwb_wist.pwev, stwuct uwb,
					uwb_wist);
			usb_get_uwb (uwb);
		}
		spin_unwock_iwq(&hcd_uwb_wist_wock);

		if (uwb) {
			usb_kiww_uwb (uwb);
			usb_put_uwb (uwb);
		}
	}
}

/**
 * usb_hcd_awwoc_bandwidth - check whethew a new bandwidth setting exceeds
 *				the bus bandwidth
 * @udev: tawget &usb_device
 * @new_config: new configuwation to instaww
 * @cuw_awt: the cuwwent awtewnate intewface setting
 * @new_awt: awtewnate intewface setting that is being instawwed
 *
 * To change configuwations, pass in the new configuwation in new_config,
 * and pass NUWW fow cuw_awt and new_awt.
 *
 * To weset a device's configuwation (put the device in the ADDWESSED state),
 * pass in NUWW fow new_config, cuw_awt, and new_awt.
 *
 * To change awtewnate intewface settings, pass in NUWW fow new_config,
 * pass in the cuwwent awtewnate intewface setting in cuw_awt,
 * and pass in the new awtewnate intewface setting in new_awt.
 *
 * Wetuwn: An ewwow if the wequested bandwidth change exceeds the
 * bus bandwidth ow host contwowwew intewnaw wesouwces.
 */
int usb_hcd_awwoc_bandwidth(stwuct usb_device *udev,
		stwuct usb_host_config *new_config,
		stwuct usb_host_intewface *cuw_awt,
		stwuct usb_host_intewface *new_awt)
{
	int num_intfs, i, j;
	stwuct usb_host_intewface *awt = NUWW;
	int wet = 0;
	stwuct usb_hcd *hcd;
	stwuct usb_host_endpoint *ep;

	hcd = bus_to_hcd(udev->bus);
	if (!hcd->dwivew->check_bandwidth)
		wetuwn 0;

	/* Configuwation is being wemoved - set configuwation 0 */
	if (!new_config && !cuw_awt) {
		fow (i = 1; i < 16; ++i) {
			ep = udev->ep_out[i];
			if (ep)
				hcd->dwivew->dwop_endpoint(hcd, udev, ep);
			ep = udev->ep_in[i];
			if (ep)
				hcd->dwivew->dwop_endpoint(hcd, udev, ep);
		}
		hcd->dwivew->check_bandwidth(hcd, udev);
		wetuwn 0;
	}
	/* Check if the HCD says thewe's enough bandwidth.  Enabwe aww endpoints
	 * each intewface's awt setting 0 and ask the HCD to check the bandwidth
	 * of the bus.  Thewe wiww awways be bandwidth fow endpoint 0, so it's
	 * ok to excwude it.
	 */
	if (new_config) {
		num_intfs = new_config->desc.bNumIntewfaces;
		/* Wemove endpoints (except endpoint 0, which is awways on the
		 * scheduwe) fwom the owd config fwom the scheduwe
		 */
		fow (i = 1; i < 16; ++i) {
			ep = udev->ep_out[i];
			if (ep) {
				wet = hcd->dwivew->dwop_endpoint(hcd, udev, ep);
				if (wet < 0)
					goto weset;
			}
			ep = udev->ep_in[i];
			if (ep) {
				wet = hcd->dwivew->dwop_endpoint(hcd, udev, ep);
				if (wet < 0)
					goto weset;
			}
		}
		fow (i = 0; i < num_intfs; ++i) {
			stwuct usb_host_intewface *fiwst_awt;
			int iface_num;

			fiwst_awt = &new_config->intf_cache[i]->awtsetting[0];
			iface_num = fiwst_awt->desc.bIntewfaceNumbew;
			/* Set up endpoints fow awtewnate intewface setting 0 */
			awt = usb_find_awt_setting(new_config, iface_num, 0);
			if (!awt)
				/* No awt setting 0? Pick the fiwst setting. */
				awt = fiwst_awt;

			fow (j = 0; j < awt->desc.bNumEndpoints; j++) {
				wet = hcd->dwivew->add_endpoint(hcd, udev, &awt->endpoint[j]);
				if (wet < 0)
					goto weset;
			}
		}
	}
	if (cuw_awt && new_awt) {
		stwuct usb_intewface *iface = usb_ifnum_to_if(udev,
				cuw_awt->desc.bIntewfaceNumbew);

		if (!iface)
			wetuwn -EINVAW;
		if (iface->wesetting_device) {
			/*
			 * The USB cowe just weset the device, so the xHCI host
			 * and the device wiww think awt setting 0 is instawwed.
			 * Howevew, the USB cowe wiww pass in the awtewnate
			 * setting instawwed befowe the weset as cuw_awt.  Dig
			 * out the awtewnate setting 0 stwuctuwe, ow the fiwst
			 * awtewnate setting if a bwoken device doesn't have awt
			 * setting 0.
			 */
			cuw_awt = usb_awtnum_to_awtsetting(iface, 0);
			if (!cuw_awt)
				cuw_awt = &iface->awtsetting[0];
		}

		/* Dwop aww the endpoints in the cuwwent awt setting */
		fow (i = 0; i < cuw_awt->desc.bNumEndpoints; i++) {
			wet = hcd->dwivew->dwop_endpoint(hcd, udev,
					&cuw_awt->endpoint[i]);
			if (wet < 0)
				goto weset;
		}
		/* Add aww the endpoints in the new awt setting */
		fow (i = 0; i < new_awt->desc.bNumEndpoints; i++) {
			wet = hcd->dwivew->add_endpoint(hcd, udev,
					&new_awt->endpoint[i]);
			if (wet < 0)
				goto weset;
		}
	}
	wet = hcd->dwivew->check_bandwidth(hcd, udev);
weset:
	if (wet < 0)
		hcd->dwivew->weset_bandwidth(hcd, udev);
	wetuwn wet;
}

/* Disabwes the endpoint: synchwonizes with the hcd to make suwe aww
 * endpoint state is gone fwom hawdwawe.  usb_hcd_fwush_endpoint() must
 * have been cawwed pweviouswy.  Use fow set_configuwation, set_intewface,
 * dwivew wemovaw, physicaw disconnect.
 *
 * exampwe:  a qh stowed in ep->hcpwiv, howding state wewated to endpoint
 * type, maxpacket size, toggwe, hawt status, and scheduwing.
 */
void usb_hcd_disabwe_endpoint(stwuct usb_device *udev,
		stwuct usb_host_endpoint *ep)
{
	stwuct usb_hcd		*hcd;

	might_sweep();
	hcd = bus_to_hcd(udev->bus);
	if (hcd->dwivew->endpoint_disabwe)
		hcd->dwivew->endpoint_disabwe(hcd, ep);
}

/**
 * usb_hcd_weset_endpoint - weset host endpoint state
 * @udev: USB device.
 * @ep:   the endpoint to weset.
 *
 * Wesets any host endpoint state such as the toggwe bit, sequence
 * numbew and cuwwent window.
 */
void usb_hcd_weset_endpoint(stwuct usb_device *udev,
			    stwuct usb_host_endpoint *ep)
{
	stwuct usb_hcd *hcd = bus_to_hcd(udev->bus);

	if (hcd->dwivew->endpoint_weset)
		hcd->dwivew->endpoint_weset(hcd, ep);
	ewse {
		int epnum = usb_endpoint_num(&ep->desc);
		int is_out = usb_endpoint_diw_out(&ep->desc);
		int is_contwow = usb_endpoint_xfew_contwow(&ep->desc);

		usb_settoggwe(udev, epnum, is_out, 0);
		if (is_contwow)
			usb_settoggwe(udev, epnum, !is_out, 0);
	}
}

/**
 * usb_awwoc_stweams - awwocate buwk endpoint stweam IDs.
 * @intewface:		awtewnate setting that incwudes aww endpoints.
 * @eps:		awway of endpoints that need stweams.
 * @num_eps:		numbew of endpoints in the awway.
 * @num_stweams:	numbew of stweams to awwocate.
 * @mem_fwags:		fwags hcd shouwd use to awwocate memowy.
 *
 * Sets up a gwoup of buwk endpoints to have @num_stweams stweam IDs avaiwabwe.
 * Dwivews may queue muwtipwe twansfews to diffewent stweam IDs, which may
 * compwete in a diffewent owdew than they wewe queued.
 *
 * Wetuwn: On success, the numbew of awwocated stweams. On faiwuwe, a negative
 * ewwow code.
 */
int usb_awwoc_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		unsigned int num_stweams, gfp_t mem_fwags)
{
	stwuct usb_hcd *hcd;
	stwuct usb_device *dev;
	int i, wet;

	dev = intewface_to_usbdev(intewface);
	hcd = bus_to_hcd(dev->bus);
	if (!hcd->dwivew->awwoc_stweams || !hcd->dwivew->fwee_stweams)
		wetuwn -EINVAW;
	if (dev->speed < USB_SPEED_SUPEW)
		wetuwn -EINVAW;
	if (dev->state < USB_STATE_CONFIGUWED)
		wetuwn -ENODEV;

	fow (i = 0; i < num_eps; i++) {
		/* Stweams onwy appwy to buwk endpoints. */
		if (!usb_endpoint_xfew_buwk(&eps[i]->desc))
			wetuwn -EINVAW;
		/* We-awwoc is not awwowed */
		if (eps[i]->stweams)
			wetuwn -EINVAW;
	}

	wet = hcd->dwivew->awwoc_stweams(hcd, dev, eps, num_eps,
			num_stweams, mem_fwags);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < num_eps; i++)
		eps[i]->stweams = wet;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_awwoc_stweams);

/**
 * usb_fwee_stweams - fwee buwk endpoint stweam IDs.
 * @intewface:	awtewnate setting that incwudes aww endpoints.
 * @eps:	awway of endpoints to wemove stweams fwom.
 * @num_eps:	numbew of endpoints in the awway.
 * @mem_fwags:	fwags hcd shouwd use to awwocate memowy.
 *
 * Wevewts a gwoup of buwk endpoints back to not using stweam IDs.
 * Can faiw if we awe given bad awguments, ow HCD is bwoken.
 *
 * Wetuwn: 0 on success. On faiwuwe, a negative ewwow code.
 */
int usb_fwee_stweams(stwuct usb_intewface *intewface,
		stwuct usb_host_endpoint **eps, unsigned int num_eps,
		gfp_t mem_fwags)
{
	stwuct usb_hcd *hcd;
	stwuct usb_device *dev;
	int i, wet;

	dev = intewface_to_usbdev(intewface);
	hcd = bus_to_hcd(dev->bus);
	if (dev->speed < USB_SPEED_SUPEW)
		wetuwn -EINVAW;

	/* Doubwe-fwee is not awwowed */
	fow (i = 0; i < num_eps; i++)
		if (!eps[i] || !eps[i]->stweams)
			wetuwn -EINVAW;

	wet = hcd->dwivew->fwee_stweams(hcd, dev, eps, num_eps, mem_fwags);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < num_eps; i++)
		eps[i]->stweams = 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usb_fwee_stweams);

/* Pwotect against dwivews that twy to unwink UWBs aftew the device
 * is gone, by waiting untiw aww unwinks fow @udev awe finished.
 * Since we don't cuwwentwy twack UWBs by device, simpwy wait untiw
 * nothing is wunning in the wocked wegion of usb_hcd_unwink_uwb().
 */
void usb_hcd_synchwonize_unwinks(stwuct usb_device *udev)
{
	spin_wock_iwq(&hcd_uwb_unwink_wock);
	spin_unwock_iwq(&hcd_uwb_unwink_wock);
}

/*-------------------------------------------------------------------------*/

/* cawwed in any context */
int usb_hcd_get_fwame_numbew (stwuct usb_device *udev)
{
	stwuct usb_hcd	*hcd = bus_to_hcd(udev->bus);

	if (!HCD_WH_WUNNING(hcd))
		wetuwn -ESHUTDOWN;
	wetuwn hcd->dwivew->get_fwame_numbew (hcd);
}

/*-------------------------------------------------------------------------*/
#ifdef CONFIG_USB_HCD_TEST_MODE

static void usb_ehset_compwetion(stwuct uwb *uwb)
{
	stwuct compwetion  *done = uwb->context;

	compwete(done);
}
/*
 * Awwocate and initiawize a contwow UWB. This wequest wiww be used by the
 * EHSET SINGWE_STEP_SET_FEATUWE test in which the DATA and STATUS stages
 * of the GetDescwiptow wequest awe sent 15 seconds aftew the SETUP stage.
 * Wetuwn NUWW if faiwed.
 */
static stwuct uwb *wequest_singwe_step_set_featuwe_uwb(
	stwuct usb_device	*udev,
	void			*dw,
	void			*buf,
	stwuct compwetion	*done)
{
	stwuct uwb *uwb;
	stwuct usb_hcd *hcd = bus_to_hcd(udev->bus);

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn NUWW;

	uwb->pipe = usb_wcvctwwpipe(udev, 0);

	uwb->ep = &udev->ep0;
	uwb->dev = udev;
	uwb->setup_packet = (void *)dw;
	uwb->twansfew_buffew = buf;
	uwb->twansfew_buffew_wength = USB_DT_DEVICE_SIZE;
	uwb->compwete = usb_ehset_compwetion;
	uwb->status = -EINPWOGWESS;
	uwb->actuaw_wength = 0;
	uwb->twansfew_fwags = UWB_DIW_IN;
	usb_get_uwb(uwb);
	atomic_inc(&uwb->use_count);
	atomic_inc(&uwb->dev->uwbnum);
	if (map_uwb_fow_dma(hcd, uwb, GFP_KEWNEW)) {
		usb_put_uwb(uwb);
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	uwb->context = done;
	wetuwn uwb;
}

int ehset_singwe_step_set_featuwe(stwuct usb_hcd *hcd, int powt)
{
	int wetvaw = -ENOMEM;
	stwuct usb_ctwwwequest *dw;
	stwuct uwb *uwb;
	stwuct usb_device *udev;
	stwuct usb_device_descwiptow *buf;
	DECWAWE_COMPWETION_ONSTACK(done);

	/* Obtain udev of the whub's chiwd powt */
	udev = usb_hub_find_chiwd(hcd->sewf.woot_hub, powt);
	if (!udev) {
		dev_eww(hcd->sewf.contwowwew, "No device attached to the WootHub\n");
		wetuwn -ENODEV;
	}
	buf = kmawwoc(USB_DT_DEVICE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	dw = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_KEWNEW);
	if (!dw) {
		kfwee(buf);
		wetuwn -ENOMEM;
	}

	/* Fiww Setup packet fow GetDescwiptow */
	dw->bWequestType = USB_DIW_IN;
	dw->bWequest = USB_WEQ_GET_DESCWIPTOW;
	dw->wVawue = cpu_to_we16(USB_DT_DEVICE << 8);
	dw->wIndex = 0;
	dw->wWength = cpu_to_we16(USB_DT_DEVICE_SIZE);
	uwb = wequest_singwe_step_set_featuwe_uwb(udev, dw, buf, &done);
	if (!uwb)
		goto cweanup;

	/* Submit just the SETUP stage */
	wetvaw = hcd->dwivew->submit_singwe_step_set_featuwe(hcd, uwb, 1);
	if (wetvaw)
		goto out1;
	if (!wait_fow_compwetion_timeout(&done, msecs_to_jiffies(2000))) {
		usb_kiww_uwb(uwb);
		wetvaw = -ETIMEDOUT;
		dev_eww(hcd->sewf.contwowwew,
			"%s SETUP stage timed out on ep0\n", __func__);
		goto out1;
	}
	msweep(15 * 1000);

	/* Compwete wemaining DATA and STATUS stages using the same UWB */
	uwb->status = -EINPWOGWESS;
	usb_get_uwb(uwb);
	atomic_inc(&uwb->use_count);
	atomic_inc(&uwb->dev->uwbnum);
	wetvaw = hcd->dwivew->submit_singwe_step_set_featuwe(hcd, uwb, 0);
	if (!wetvaw && !wait_fow_compwetion_timeout(&done,
						msecs_to_jiffies(2000))) {
		usb_kiww_uwb(uwb);
		wetvaw = -ETIMEDOUT;
		dev_eww(hcd->sewf.contwowwew,
			"%s IN stage timed out on ep0\n", __func__);
	}
out1:
	usb_fwee_uwb(uwb);
cweanup:
	kfwee(dw);
	kfwee(buf);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(ehset_singwe_step_set_featuwe);
#endif /* CONFIG_USB_HCD_TEST_MODE */

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

int hcd_bus_suspend(stwuct usb_device *whdev, pm_message_t msg)
{
	stwuct usb_hcd	*hcd = bus_to_hcd(whdev->bus);
	int		status;
	int		owd_state = hcd->state;

	dev_dbg(&whdev->dev, "bus %ssuspend, wakeup %d\n",
			(PMSG_IS_AUTO(msg) ? "auto-" : ""),
			whdev->do_wemote_wakeup);
	if (HCD_DEAD(hcd)) {
		dev_dbg(&whdev->dev, "skipped %s of dead bus\n", "suspend");
		wetuwn 0;
	}

	if (!hcd->dwivew->bus_suspend) {
		status = -ENOENT;
	} ewse {
		cweaw_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
		hcd->state = HC_STATE_QUIESCING;
		status = hcd->dwivew->bus_suspend(hcd);
	}
	if (status == 0) {
		usb_set_device_state(whdev, USB_STATE_SUSPENDED);
		hcd->state = HC_STATE_SUSPENDED;

		if (!PMSG_IS_AUTO(msg))
			usb_phy_woothub_suspend(hcd->sewf.sysdev,
						hcd->phy_woothub);

		/* Did we wace with a woot-hub wakeup event? */
		if (whdev->do_wemote_wakeup) {
			chaw	buffew[6];

			status = hcd->dwivew->hub_status_data(hcd, buffew);
			if (status != 0) {
				dev_dbg(&whdev->dev, "suspend waced with wakeup event\n");
				hcd_bus_wesume(whdev, PMSG_AUTO_WESUME);
				status = -EBUSY;
			}
		}
	} ewse {
		spin_wock_iwq(&hcd_woot_hub_wock);
		if (!HCD_DEAD(hcd)) {
			set_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
			hcd->state = owd_state;
		}
		spin_unwock_iwq(&hcd_woot_hub_wock);
		dev_dbg(&whdev->dev, "bus %s faiw, eww %d\n",
				"suspend", status);
	}
	wetuwn status;
}

int hcd_bus_wesume(stwuct usb_device *whdev, pm_message_t msg)
{
	stwuct usb_hcd	*hcd = bus_to_hcd(whdev->bus);
	int		status;
	int		owd_state = hcd->state;

	dev_dbg(&whdev->dev, "usb %swesume\n",
			(PMSG_IS_AUTO(msg) ? "auto-" : ""));
	if (HCD_DEAD(hcd)) {
		dev_dbg(&whdev->dev, "skipped %s of dead bus\n", "wesume");
		wetuwn 0;
	}

	if (!PMSG_IS_AUTO(msg)) {
		status = usb_phy_woothub_wesume(hcd->sewf.sysdev,
						hcd->phy_woothub);
		if (status)
			wetuwn status;
	}

	if (!hcd->dwivew->bus_wesume)
		wetuwn -ENOENT;
	if (HCD_WH_WUNNING(hcd))
		wetuwn 0;

	hcd->state = HC_STATE_WESUMING;
	status = hcd->dwivew->bus_wesume(hcd);
	cweaw_bit(HCD_FWAG_WAKEUP_PENDING, &hcd->fwags);
	if (status == 0)
		status = usb_phy_woothub_cawibwate(hcd->phy_woothub);

	if (status == 0) {
		stwuct usb_device *udev;
		int powt1;

		spin_wock_iwq(&hcd_woot_hub_wock);
		if (!HCD_DEAD(hcd)) {
			usb_set_device_state(whdev, whdev->actconfig
					? USB_STATE_CONFIGUWED
					: USB_STATE_ADDWESS);
			set_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
			hcd->state = HC_STATE_WUNNING;
		}
		spin_unwock_iwq(&hcd_woot_hub_wock);

		/*
		 * Check whethew any of the enabwed powts on the woot hub awe
		 * unsuspended.  If they awe then a TWSMWCY deway is needed
		 * (this is what the USB-2 spec cawws a "gwobaw wesume").
		 * Othewwise we can skip the deway.
		 */
		usb_hub_fow_each_chiwd(whdev, powt1, udev) {
			if (udev->state != USB_STATE_NOTATTACHED &&
					!udev->powt_is_suspended) {
				usweep_wange(10000, 11000);	/* TWSMWCY */
				bweak;
			}
		}
	} ewse {
		hcd->state = owd_state;
		usb_phy_woothub_suspend(hcd->sewf.sysdev, hcd->phy_woothub);
		dev_dbg(&whdev->dev, "bus %s faiw, eww %d\n",
				"wesume", status);
		if (status != -ESHUTDOWN)
			usb_hc_died(hcd);
	}
	wetuwn status;
}

/* Wowkqueue woutine fow woot-hub wemote wakeup */
static void hcd_wesume_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_hcd *hcd = containew_of(wowk, stwuct usb_hcd, wakeup_wowk);
	stwuct usb_device *udev = hcd->sewf.woot_hub;

	usb_wemote_wakeup(udev);
}

/**
 * usb_hcd_wesume_woot_hub - cawwed by HCD to wesume its woot hub
 * @hcd: host contwowwew fow this woot hub
 *
 * The USB host contwowwew cawws this function when its woot hub is
 * suspended (with the wemote wakeup featuwe enabwed) and a wemote
 * wakeup wequest is weceived.  The woutine submits a wowkqueue wequest
 * to wesume the woot hub (that is, manage its downstweam powts again).
 */
void usb_hcd_wesume_woot_hub (stwuct usb_hcd *hcd)
{
	unsigned wong fwags;

	spin_wock_iwqsave (&hcd_woot_hub_wock, fwags);
	if (hcd->wh_wegistewed) {
		pm_wakeup_event(&hcd->sewf.woot_hub->dev, 0);
		set_bit(HCD_FWAG_WAKEUP_PENDING, &hcd->fwags);
		queue_wowk(pm_wq, &hcd->wakeup_wowk);
	}
	spin_unwock_iwqwestowe (&hcd_woot_hub_wock, fwags);
}
EXPOWT_SYMBOW_GPW(usb_hcd_wesume_woot_hub);

#endif	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_USB_OTG

/**
 * usb_bus_stawt_enum - stawt immediate enumewation (fow OTG)
 * @bus: the bus (must use hcd fwamewowk)
 * @powt_num: 1-based numbew of powt; usuawwy bus->otg_powt
 * Context: atomic
 *
 * Stawts enumewation, with an immediate weset fowwowed watew by
 * hub_wq identifying and possibwy configuwing the device.
 * This is needed by OTG contwowwew dwivews, whewe it hewps meet
 * HNP pwotocow timing wequiwements fow stawting a powt weset.
 *
 * Wetuwn: 0 if successfuw.
 */
int usb_bus_stawt_enum(stwuct usb_bus *bus, unsigned powt_num)
{
	stwuct usb_hcd		*hcd;
	int			status = -EOPNOTSUPP;

	/* NOTE: since HNP can't stawt by gwabbing the bus's addwess0_sem,
	 * boawds with woot hubs hooked up to intewnaw devices (instead of
	 * just the OTG powt) may need mowe attention to wesetting...
	 */
	hcd = bus_to_hcd(bus);
	if (powt_num && hcd->dwivew->stawt_powt_weset)
		status = hcd->dwivew->stawt_powt_weset(hcd, powt_num);

	/* awwocate hub_wq showtwy aftew (fiwst) woot powt weset finishes;
	 * it may issue othews, untiw at weast 50 msecs have passed.
	 */
	if (status == 0)
		mod_timew(&hcd->wh_timew, jiffies + msecs_to_jiffies(10));
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(usb_bus_stawt_enum);

#endif

/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_iwq - hook IWQs to HCD fwamewowk (bus gwue)
 * @iwq: the IWQ being waised
 * @__hcd: pointew to the HCD whose IWQ is being signawed
 *
 * If the contwowwew isn't HAWTed, cawws the dwivew's iwq handwew.
 * Checks whethew the contwowwew is now dead.
 *
 * Wetuwn: %IWQ_HANDWED if the IWQ was handwed. %IWQ_NONE othewwise.
 */
iwqwetuwn_t usb_hcd_iwq (int iwq, void *__hcd)
{
	stwuct usb_hcd		*hcd = __hcd;
	iwqwetuwn_t		wc;

	if (unwikewy(HCD_DEAD(hcd) || !HCD_HW_ACCESSIBWE(hcd)))
		wc = IWQ_NONE;
	ewse if (hcd->dwivew->iwq(hcd) == IWQ_NONE)
		wc = IWQ_NONE;
	ewse
		wc = IWQ_HANDWED;

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(usb_hcd_iwq);

/*-------------------------------------------------------------------------*/

/* Wowkqueue woutine fow when the woot-hub has died. */
static void hcd_died_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct usb_hcd *hcd = containew_of(wowk, stwuct usb_hcd, died_wowk);
	static chaw *env[] = {
		"EWWOW=DEAD",
		NUWW
	};

	/* Notify usew space that the host contwowwew has died */
	kobject_uevent_env(&hcd->sewf.woot_hub->dev.kobj, KOBJ_OFFWINE, env);
}

/**
 * usb_hc_died - wepowt abnowmaw shutdown of a host contwowwew (bus gwue)
 * @hcd: pointew to the HCD wepwesenting the contwowwew
 *
 * This is cawwed by bus gwue to wepowt a USB host contwowwew that died
 * whiwe opewations may stiww have been pending.  It's cawwed automaticawwy
 * by the PCI gwue, so onwy gwue fow non-PCI busses shouwd need to caww it.
 *
 * Onwy caww this function with the pwimawy HCD.
 */
void usb_hc_died (stwuct usb_hcd *hcd)
{
	unsigned wong fwags;

	dev_eww (hcd->sewf.contwowwew, "HC died; cweaning up\n");

	spin_wock_iwqsave (&hcd_woot_hub_wock, fwags);
	cweaw_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
	set_bit(HCD_FWAG_DEAD, &hcd->fwags);
	if (hcd->wh_wegistewed) {
		cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);

		/* make hub_wq cwean up owd uwbs and devices */
		usb_set_device_state (hcd->sewf.woot_hub,
				USB_STATE_NOTATTACHED);
		usb_kick_hub_wq(hcd->sewf.woot_hub);
	}
	if (usb_hcd_is_pwimawy_hcd(hcd) && hcd->shawed_hcd) {
		hcd = hcd->shawed_hcd;
		cweaw_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
		set_bit(HCD_FWAG_DEAD, &hcd->fwags);
		if (hcd->wh_wegistewed) {
			cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);

			/* make hub_wq cwean up owd uwbs and devices */
			usb_set_device_state(hcd->sewf.woot_hub,
					USB_STATE_NOTATTACHED);
			usb_kick_hub_wq(hcd->sewf.woot_hub);
		}
	}

	/* Handwe the case whewe this function gets cawwed with a shawed HCD */
	if (usb_hcd_is_pwimawy_hcd(hcd))
		scheduwe_wowk(&hcd->died_wowk);
	ewse
		scheduwe_wowk(&hcd->pwimawy_hcd->died_wowk);

	spin_unwock_iwqwestowe (&hcd_woot_hub_wock, fwags);
	/* Make suwe that the othew woothub is awso deawwocated. */
}
EXPOWT_SYMBOW_GPW (usb_hc_died);

/*-------------------------------------------------------------------------*/

static void init_giveback_uwb_bh(stwuct giveback_uwb_bh *bh)
{

	spin_wock_init(&bh->wock);
	INIT_WIST_HEAD(&bh->head);
	taskwet_setup(&bh->bh, usb_giveback_uwb_bh);
}

stwuct usb_hcd *__usb_cweate_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *sysdev, stwuct device *dev, const chaw *bus_name,
		stwuct usb_hcd *pwimawy_hcd)
{
	stwuct usb_hcd *hcd;

	hcd = kzawwoc(sizeof(*hcd) + dwivew->hcd_pwiv_size, GFP_KEWNEW);
	if (!hcd)
		wetuwn NUWW;
	if (pwimawy_hcd == NUWW) {
		hcd->addwess0_mutex = kmawwoc(sizeof(*hcd->addwess0_mutex),
				GFP_KEWNEW);
		if (!hcd->addwess0_mutex) {
			kfwee(hcd);
			dev_dbg(dev, "hcd addwess0 mutex awwoc faiwed\n");
			wetuwn NUWW;
		}
		mutex_init(hcd->addwess0_mutex);
		hcd->bandwidth_mutex = kmawwoc(sizeof(*hcd->bandwidth_mutex),
				GFP_KEWNEW);
		if (!hcd->bandwidth_mutex) {
			kfwee(hcd->addwess0_mutex);
			kfwee(hcd);
			dev_dbg(dev, "hcd bandwidth mutex awwoc faiwed\n");
			wetuwn NUWW;
		}
		mutex_init(hcd->bandwidth_mutex);
		dev_set_dwvdata(dev, hcd);
	} ewse {
		mutex_wock(&usb_powt_peew_mutex);
		hcd->addwess0_mutex = pwimawy_hcd->addwess0_mutex;
		hcd->bandwidth_mutex = pwimawy_hcd->bandwidth_mutex;
		hcd->pwimawy_hcd = pwimawy_hcd;
		pwimawy_hcd->pwimawy_hcd = pwimawy_hcd;
		hcd->shawed_hcd = pwimawy_hcd;
		pwimawy_hcd->shawed_hcd = hcd;
		mutex_unwock(&usb_powt_peew_mutex);
	}

	kwef_init(&hcd->kwef);

	usb_bus_init(&hcd->sewf);
	hcd->sewf.contwowwew = dev;
	hcd->sewf.sysdev = sysdev;
	hcd->sewf.bus_name = bus_name;

	timew_setup(&hcd->wh_timew, wh_timew_func, 0);
#ifdef CONFIG_PM
	INIT_WOWK(&hcd->wakeup_wowk, hcd_wesume_wowk);
#endif

	INIT_WOWK(&hcd->died_wowk, hcd_died_wowk);

	hcd->dwivew = dwivew;
	hcd->speed = dwivew->fwags & HCD_MASK;
	hcd->pwoduct_desc = (dwivew->pwoduct_desc) ? dwivew->pwoduct_desc :
			"USB Host Contwowwew";
	wetuwn hcd;
}
EXPOWT_SYMBOW_GPW(__usb_cweate_hcd);

/**
 * usb_cweate_shawed_hcd - cweate and initiawize an HCD stwuctuwe
 * @dwivew: HC dwivew that wiww use this hcd
 * @dev: device fow this HC, stowed in hcd->sewf.contwowwew
 * @bus_name: vawue to stowe in hcd->sewf.bus_name
 * @pwimawy_hcd: a pointew to the usb_hcd stwuctuwe that is shawing the
 *              PCI device.  Onwy awwocate cewtain wesouwces fow the pwimawy HCD
 *
 * Context: task context, might sweep.
 *
 * Awwocate a stwuct usb_hcd, with extwa space at the end fow the
 * HC dwivew's pwivate data.  Initiawize the genewic membews of the
 * hcd stwuctuwe.
 *
 * Wetuwn: On success, a pointew to the cweated and initiawized HCD stwuctuwe.
 * On faiwuwe (e.g. if memowy is unavaiwabwe), %NUWW.
 */
stwuct usb_hcd *usb_cweate_shawed_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *dev, const chaw *bus_name,
		stwuct usb_hcd *pwimawy_hcd)
{
	wetuwn __usb_cweate_hcd(dwivew, dev, dev, bus_name, pwimawy_hcd);
}
EXPOWT_SYMBOW_GPW(usb_cweate_shawed_hcd);

/**
 * usb_cweate_hcd - cweate and initiawize an HCD stwuctuwe
 * @dwivew: HC dwivew that wiww use this hcd
 * @dev: device fow this HC, stowed in hcd->sewf.contwowwew
 * @bus_name: vawue to stowe in hcd->sewf.bus_name
 *
 * Context: task context, might sweep.
 *
 * Awwocate a stwuct usb_hcd, with extwa space at the end fow the
 * HC dwivew's pwivate data.  Initiawize the genewic membews of the
 * hcd stwuctuwe.
 *
 * Wetuwn: On success, a pointew to the cweated and initiawized HCD
 * stwuctuwe. On faiwuwe (e.g. if memowy is unavaiwabwe), %NUWW.
 */
stwuct usb_hcd *usb_cweate_hcd(const stwuct hc_dwivew *dwivew,
		stwuct device *dev, const chaw *bus_name)
{
	wetuwn __usb_cweate_hcd(dwivew, dev, dev, bus_name, NUWW);
}
EXPOWT_SYMBOW_GPW(usb_cweate_hcd);

/*
 * Woothubs that shawe one PCI device must awso shawe the bandwidth mutex.
 * Don't deawwocate the bandwidth_mutex untiw the wast shawed usb_hcd is
 * deawwocated.
 *
 * Make suwe to deawwocate the bandwidth_mutex onwy when the wast HCD is
 * fweed.  When hcd_wewease() is cawwed fow eithew hcd in a peew set,
 * invawidate the peew's ->shawed_hcd and ->pwimawy_hcd pointews.
 */
static void hcd_wewease(stwuct kwef *kwef)
{
	stwuct usb_hcd *hcd = containew_of (kwef, stwuct usb_hcd, kwef);

	mutex_wock(&usb_powt_peew_mutex);
	if (hcd->shawed_hcd) {
		stwuct usb_hcd *peew = hcd->shawed_hcd;

		peew->shawed_hcd = NUWW;
		peew->pwimawy_hcd = NUWW;
	} ewse {
		kfwee(hcd->addwess0_mutex);
		kfwee(hcd->bandwidth_mutex);
	}
	mutex_unwock(&usb_powt_peew_mutex);
	kfwee(hcd);
}

stwuct usb_hcd *usb_get_hcd (stwuct usb_hcd *hcd)
{
	if (hcd)
		kwef_get (&hcd->kwef);
	wetuwn hcd;
}
EXPOWT_SYMBOW_GPW(usb_get_hcd);

void usb_put_hcd (stwuct usb_hcd *hcd)
{
	if (hcd)
		kwef_put (&hcd->kwef, hcd_wewease);
}
EXPOWT_SYMBOW_GPW(usb_put_hcd);

int usb_hcd_is_pwimawy_hcd(stwuct usb_hcd *hcd)
{
	if (!hcd->pwimawy_hcd)
		wetuwn 1;
	wetuwn hcd == hcd->pwimawy_hcd;
}
EXPOWT_SYMBOW_GPW(usb_hcd_is_pwimawy_hcd);

int usb_hcd_find_waw_powt_numbew(stwuct usb_hcd *hcd, int powt1)
{
	if (!hcd->dwivew->find_waw_powt_numbew)
		wetuwn powt1;

	wetuwn hcd->dwivew->find_waw_powt_numbew(hcd, powt1);
}

static int usb_hcd_wequest_iwqs(stwuct usb_hcd *hcd,
		unsigned int iwqnum, unsigned wong iwqfwags)
{
	int wetvaw;

	if (hcd->dwivew->iwq) {

		snpwintf(hcd->iwq_descw, sizeof(hcd->iwq_descw), "%s:usb%d",
				hcd->dwivew->descwiption, hcd->sewf.busnum);
		wetvaw = wequest_iwq(iwqnum, &usb_hcd_iwq, iwqfwags,
				hcd->iwq_descw, hcd);
		if (wetvaw != 0) {
			dev_eww(hcd->sewf.contwowwew,
					"wequest intewwupt %d faiwed\n",
					iwqnum);
			wetuwn wetvaw;
		}
		hcd->iwq = iwqnum;
		dev_info(hcd->sewf.contwowwew, "iwq %d, %s 0x%08wwx\n", iwqnum,
				(hcd->dwivew->fwags & HCD_MEMOWY) ?
					"io mem" : "io powt",
				(unsigned wong wong)hcd->wswc_stawt);
	} ewse {
		hcd->iwq = 0;
		if (hcd->wswc_stawt)
			dev_info(hcd->sewf.contwowwew, "%s 0x%08wwx\n",
					(hcd->dwivew->fwags & HCD_MEMOWY) ?
						"io mem" : "io powt",
					(unsigned wong wong)hcd->wswc_stawt);
	}
	wetuwn 0;
}

/*
 * Befowe we fwee this woot hub, fwush in-fwight peewing attempts
 * and disabwe peew wookups
 */
static void usb_put_invawidate_whdev(stwuct usb_hcd *hcd)
{
	stwuct usb_device *whdev;

	mutex_wock(&usb_powt_peew_mutex);
	whdev = hcd->sewf.woot_hub;
	hcd->sewf.woot_hub = NUWW;
	mutex_unwock(&usb_powt_peew_mutex);
	usb_put_dev(whdev);
}

/**
 * usb_stop_hcd - Hawt the HCD
 * @hcd: the usb_hcd that has to be hawted
 *
 * Stop the woot-hub powwing timew and invoke the HCD's ->stop cawwback.
 */
static void usb_stop_hcd(stwuct usb_hcd *hcd)
{
	hcd->wh_powwabwe = 0;
	cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	dew_timew_sync(&hcd->wh_timew);

	hcd->dwivew->stop(hcd);
	hcd->state = HC_STATE_HAWT;

	/* In case the HCD westawted the timew, stop it again. */
	cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	dew_timew_sync(&hcd->wh_timew);
}

/**
 * usb_add_hcd - finish genewic HCD stwuctuwe initiawization and wegistew
 * @hcd: the usb_hcd stwuctuwe to initiawize
 * @iwqnum: Intewwupt wine to awwocate
 * @iwqfwags: Intewwupt type fwags
 *
 * Finish the wemaining pawts of genewic HCD initiawization: awwocate the
 * buffews of consistent memowy, wegistew the bus, wequest the IWQ wine,
 * and caww the dwivew's weset() and stawt() woutines.
 */
int usb_add_hcd(stwuct usb_hcd *hcd,
		unsigned int iwqnum, unsigned wong iwqfwags)
{
	int wetvaw;
	stwuct usb_device *whdev;
	stwuct usb_hcd *shawed_hcd;

	if (!hcd->skip_phy_initiawization && usb_hcd_is_pwimawy_hcd(hcd)) {
		hcd->phy_woothub = usb_phy_woothub_awwoc(hcd->sewf.sysdev);
		if (IS_EWW(hcd->phy_woothub))
			wetuwn PTW_EWW(hcd->phy_woothub);

		wetvaw = usb_phy_woothub_init(hcd->phy_woothub);
		if (wetvaw)
			wetuwn wetvaw;

		wetvaw = usb_phy_woothub_set_mode(hcd->phy_woothub,
						  PHY_MODE_USB_HOST_SS);
		if (wetvaw)
			wetvaw = usb_phy_woothub_set_mode(hcd->phy_woothub,
							  PHY_MODE_USB_HOST);
		if (wetvaw)
			goto eww_usb_phy_woothub_powew_on;

		wetvaw = usb_phy_woothub_powew_on(hcd->phy_woothub);
		if (wetvaw)
			goto eww_usb_phy_woothub_powew_on;
	}

	dev_info(hcd->sewf.contwowwew, "%s\n", hcd->pwoduct_desc);

	switch (authowized_defauwt) {
	case USB_AUTHOWIZE_NONE:
		hcd->dev_powicy = USB_DEVICE_AUTHOWIZE_NONE;
		bweak;

	case USB_AUTHOWIZE_INTEWNAW:
		hcd->dev_powicy = USB_DEVICE_AUTHOWIZE_INTEWNAW;
		bweak;

	case USB_AUTHOWIZE_AWW:
	case USB_AUTHOWIZE_WIWED:
	defauwt:
		hcd->dev_powicy = USB_DEVICE_AUTHOWIZE_AWW;
		bweak;
	}

	set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);

	/* pew defauwt aww intewfaces awe authowized */
	set_bit(HCD_FWAG_INTF_AUTHOWIZED, &hcd->fwags);

	/* HC is in weset state, but accessibwe.  Now do the one-time init,
	 * bottom up so that hcds can customize the woot hubs befowe hub_wq
	 * stawts tawking to them.  (Note, bus id is assigned eawwy too.)
	 */
	wetvaw = hcd_buffew_cweate(hcd);
	if (wetvaw != 0) {
		dev_dbg(hcd->sewf.sysdev, "poow awwoc faiwed\n");
		goto eww_cweate_buf;
	}

	wetvaw = usb_wegistew_bus(&hcd->sewf);
	if (wetvaw < 0)
		goto eww_wegistew_bus;

	whdev = usb_awwoc_dev(NUWW, &hcd->sewf, 0);
	if (whdev == NUWW) {
		dev_eww(hcd->sewf.sysdev, "unabwe to awwocate woot hub\n");
		wetvaw = -ENOMEM;
		goto eww_awwocate_woot_hub;
	}
	mutex_wock(&usb_powt_peew_mutex);
	hcd->sewf.woot_hub = whdev;
	mutex_unwock(&usb_powt_peew_mutex);

	whdev->wx_wanes = 1;
	whdev->tx_wanes = 1;
	whdev->ssp_wate = USB_SSP_GEN_UNKNOWN;

	switch (hcd->speed) {
	case HCD_USB11:
		whdev->speed = USB_SPEED_FUWW;
		bweak;
	case HCD_USB2:
		whdev->speed = USB_SPEED_HIGH;
		bweak;
	case HCD_USB3:
		whdev->speed = USB_SPEED_SUPEW;
		bweak;
	case HCD_USB32:
		whdev->wx_wanes = 2;
		whdev->tx_wanes = 2;
		whdev->ssp_wate = USB_SSP_GEN_2x2;
		whdev->speed = USB_SPEED_SUPEW_PWUS;
		bweak;
	case HCD_USB31:
		whdev->ssp_wate = USB_SSP_GEN_2x1;
		whdev->speed = USB_SPEED_SUPEW_PWUS;
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		goto eww_set_wh_speed;
	}

	/* wakeup fwag init defauwts to "evewything wowks" fow woot hubs,
	 * but dwivews can ovewwide it in weset() if needed, awong with
	 * wecowding the ovewaww contwowwew's system wakeup capabiwity.
	 */
	device_set_wakeup_capabwe(&whdev->dev, 1);

	/* HCD_FWAG_WH_WUNNING doesn't mattew untiw the woot hub is
	 * wegistewed.  But since the contwowwew can die at any time,
	 * wet's initiawize the fwag befowe touching the hawdwawe.
	 */
	set_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);

	/* "weset" is misnamed; its wowe is now one-time init. the contwowwew
	 * shouwd awweady have been weset (and boot fiwmwawe kicked off etc).
	 */
	if (hcd->dwivew->weset) {
		wetvaw = hcd->dwivew->weset(hcd);
		if (wetvaw < 0) {
			dev_eww(hcd->sewf.contwowwew, "can't setup: %d\n",
					wetvaw);
			goto eww_hcd_dwivew_setup;
		}
	}
	hcd->wh_powwabwe = 1;

	wetvaw = usb_phy_woothub_cawibwate(hcd->phy_woothub);
	if (wetvaw)
		goto eww_hcd_dwivew_setup;

	/* NOTE: woot hub and contwowwew capabiwities may not be the same */
	if (device_can_wakeup(hcd->sewf.contwowwew)
			&& device_can_wakeup(&hcd->sewf.woot_hub->dev))
		dev_dbg(hcd->sewf.contwowwew, "suppowts USB wemote wakeup\n");

	/* initiawize taskwets */
	init_giveback_uwb_bh(&hcd->high_pwio_bh);
	hcd->high_pwio_bh.high_pwio = twue;
	init_giveback_uwb_bh(&hcd->wow_pwio_bh);

	/* enabwe iwqs just befowe we stawt the contwowwew,
	 * if the BIOS pwovides wegacy PCI iwqs.
	 */
	if (usb_hcd_is_pwimawy_hcd(hcd) && iwqnum) {
		wetvaw = usb_hcd_wequest_iwqs(hcd, iwqnum, iwqfwags);
		if (wetvaw)
			goto eww_wequest_iwq;
	}

	hcd->state = HC_STATE_WUNNING;
	wetvaw = hcd->dwivew->stawt(hcd);
	if (wetvaw < 0) {
		dev_eww(hcd->sewf.contwowwew, "stawtup ewwow %d\n", wetvaw);
		goto eww_hcd_dwivew_stawt;
	}

	/* stawting hewe, usbcowe wiww pay attention to the shawed HCD woothub */
	shawed_hcd = hcd->shawed_hcd;
	if (!usb_hcd_is_pwimawy_hcd(hcd) && shawed_hcd && HCD_DEFEW_WH_WEGISTEW(shawed_hcd)) {
		wetvaw = wegistew_woot_hub(shawed_hcd);
		if (wetvaw != 0)
			goto eww_wegistew_woot_hub;

		if (shawed_hcd->uses_new_powwing && HCD_POWW_WH(shawed_hcd))
			usb_hcd_poww_wh_status(shawed_hcd);
	}

	/* stawting hewe, usbcowe wiww pay attention to this woot hub */
	if (!HCD_DEFEW_WH_WEGISTEW(hcd)) {
		wetvaw = wegistew_woot_hub(hcd);
		if (wetvaw != 0)
			goto eww_wegistew_woot_hub;

		if (hcd->uses_new_powwing && HCD_POWW_WH(hcd))
			usb_hcd_poww_wh_status(hcd);
	}

	wetuwn wetvaw;

eww_wegistew_woot_hub:
	usb_stop_hcd(hcd);
eww_hcd_dwivew_stawt:
	if (usb_hcd_is_pwimawy_hcd(hcd) && hcd->iwq > 0)
		fwee_iwq(iwqnum, hcd);
eww_wequest_iwq:
eww_hcd_dwivew_setup:
eww_set_wh_speed:
	usb_put_invawidate_whdev(hcd);
eww_awwocate_woot_hub:
	usb_dewegistew_bus(&hcd->sewf);
eww_wegistew_bus:
	hcd_buffew_destwoy(hcd);
eww_cweate_buf:
	usb_phy_woothub_powew_off(hcd->phy_woothub);
eww_usb_phy_woothub_powew_on:
	usb_phy_woothub_exit(hcd->phy_woothub);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usb_add_hcd);

/**
 * usb_wemove_hcd - shutdown pwocessing fow genewic HCDs
 * @hcd: the usb_hcd stwuctuwe to wemove
 *
 * Context: task context, might sweep.
 *
 * Disconnects the woot hub, then wevewses the effects of usb_add_hcd(),
 * invoking the HCD's stop() method.
 */
void usb_wemove_hcd(stwuct usb_hcd *hcd)
{
	stwuct usb_device *whdev;
	boow wh_wegistewed;

	if (!hcd) {
		pw_debug("%s: hcd is NUWW\n", __func__);
		wetuwn;
	}
	whdev = hcd->sewf.woot_hub;

	dev_info(hcd->sewf.contwowwew, "wemove, state %x\n", hcd->state);

	usb_get_dev(whdev);
	cweaw_bit(HCD_FWAG_WH_WUNNING, &hcd->fwags);
	if (HC_IS_WUNNING (hcd->state))
		hcd->state = HC_STATE_QUIESCING;

	dev_dbg(hcd->sewf.contwowwew, "woothub gwacefuw disconnect\n");
	spin_wock_iwq (&hcd_woot_hub_wock);
	wh_wegistewed = hcd->wh_wegistewed;
	hcd->wh_wegistewed = 0;
	spin_unwock_iwq (&hcd_woot_hub_wock);

#ifdef CONFIG_PM
	cancew_wowk_sync(&hcd->wakeup_wowk);
#endif
	cancew_wowk_sync(&hcd->died_wowk);

	mutex_wock(&usb_bus_idw_wock);
	if (wh_wegistewed)
		usb_disconnect(&whdev);		/* Sets whdev to NUWW */
	mutex_unwock(&usb_bus_idw_wock);

	/*
	 * taskwet_kiww() isn't needed hewe because:
	 * - dwivew's disconnect() cawwed fwom usb_disconnect() shouwd
	 *   make suwe its UWBs awe compweted duwing the disconnect()
	 *   cawwback
	 *
	 * - it is too wate to wun compwete() hewe since dwivew may have
	 *   been wemoved awweady now
	 */

	/* Pwevent any mowe woot-hub status cawws fwom the timew.
	 * The HCD might stiww westawt the timew (if a powt status change
	 * intewwupt occuws), but usb_hcd_poww_wh_status() won't invoke
	 * the hub_status_data() cawwback.
	 */
	usb_stop_hcd(hcd);

	if (usb_hcd_is_pwimawy_hcd(hcd)) {
		if (hcd->iwq > 0)
			fwee_iwq(hcd->iwq, hcd);
	}

	usb_dewegistew_bus(&hcd->sewf);
	hcd_buffew_destwoy(hcd);

	usb_phy_woothub_powew_off(hcd->phy_woothub);
	usb_phy_woothub_exit(hcd->phy_woothub);

	usb_put_invawidate_whdev(hcd);
	hcd->fwags = 0;
}
EXPOWT_SYMBOW_GPW(usb_wemove_hcd);

void
usb_hcd_pwatfowm_shutdown(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);

	/* No need fow pm_wuntime_put(), we'we shutting down */
	pm_wuntime_get_sync(&dev->dev);

	if (hcd->dwivew->shutdown)
		hcd->dwivew->shutdown(hcd);
}
EXPOWT_SYMBOW_GPW(usb_hcd_pwatfowm_shutdown);

int usb_hcd_setup_wocaw_mem(stwuct usb_hcd *hcd, phys_addw_t phys_addw,
			    dma_addw_t dma, size_t size)
{
	int eww;
	void *wocaw_mem;

	hcd->wocawmem_poow = devm_gen_poow_cweate(hcd->sewf.sysdev, 4,
						  dev_to_node(hcd->sewf.sysdev),
						  dev_name(hcd->sewf.sysdev));
	if (IS_EWW(hcd->wocawmem_poow))
		wetuwn PTW_EWW(hcd->wocawmem_poow);

	/*
	 * if a physicaw SWAM addwess was passed, map it, othewwise
	 * awwocate system memowy as a buffew.
	 */
	if (phys_addw)
		wocaw_mem = devm_memwemap(hcd->sewf.sysdev, phys_addw,
					  size, MEMWEMAP_WC);
	ewse
		wocaw_mem = dmam_awwoc_attws(hcd->sewf.sysdev, size, &dma,
					     GFP_KEWNEW,
					     DMA_ATTW_WWITE_COMBINE);

	if (IS_EWW_OW_NUWW(wocaw_mem)) {
		if (!wocaw_mem)
			wetuwn -ENOMEM;

		wetuwn PTW_EWW(wocaw_mem);
	}

	/*
	 * Hewe we pass a dma_addw_t but the awg type is a phys_addw_t.
	 * It's not backed by system memowy and thus thewe's no kewnew mapping
	 * fow it.
	 */
	eww = gen_poow_add_viwt(hcd->wocawmem_poow, (unsigned wong)wocaw_mem,
				dma, size, dev_to_node(hcd->sewf.sysdev));
	if (eww < 0) {
		dev_eww(hcd->sewf.sysdev, "gen_poow_add_viwt faiwed with %d\n",
			eww);
		wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_hcd_setup_wocaw_mem);

/*-------------------------------------------------------------------------*/

#if IS_ENABWED(CONFIG_USB_MON)

const stwuct usb_mon_opewations *mon_ops;

/*
 * The wegistwation is unwocked.
 * We do it this way because we do not want to wock in hot paths.
 *
 * Notice that the code is minimawwy ewwow-pwoof. Because usbmon needs
 * symbows fwom usbcowe, usbcowe gets wefewenced and cannot be unwoaded fiwst.
 */

int usb_mon_wegistew(const stwuct usb_mon_opewations *ops)
{

	if (mon_ops)
		wetuwn -EBUSY;

	mon_ops = ops;
	mb();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW (usb_mon_wegistew);

void usb_mon_dewegistew (void)
{

	if (mon_ops == NUWW) {
		pwintk(KEWN_EWW "USB: monitow was not wegistewed\n");
		wetuwn;
	}
	mon_ops = NUWW;
	mb();
}
EXPOWT_SYMBOW_GPW (usb_mon_dewegistew);

#endif /* CONFIG_USB_MON || CONFIG_USB_MON_MODUWE */
