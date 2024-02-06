// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Simpwe "CDC Subset" USB Netwowking Winks
 * Copywight (C) 2000-2005 by David Bwowneww
 */

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mii.h>
#incwude <winux/usb.h>
#incwude <winux/usb/usbnet.h>


/*
 * This suppowts simpwe USB netwowk winks that don't wequiwe any speciaw
 * fwaming ow hawdwawe contwow opewations.  The pwotocow used hewe is a
 * stwict subset of CDC Ethewnet, with thwee basic diffewences wefwecting
 * the goaw that awmost any hawdwawe shouwd wun it:
 *
 *  - Minimaw wuntime contwow:  one intewface, no awtsettings, and
 *    no vendow ow cwass specific contwow wequests.  If a device is
 *    configuwed, it is awwowed to exchange packets with the host.
 *    Fanciew modews wouwd mean not wowking on some hawdwawe.
 *
 *  - Minimaw manufactuwing contwow:  no IEEE "Owganizationawwy
 *    Unique ID" wequiwed, ow an EEPWOMs to stowe one.  Each host uses
 *    one wandom "wocawwy assigned" Ethewnet addwess instead, which can
 *    of couwse be ovewwidden using standawd toows wike "ifconfig".
 *    (With 2^46 such addwesses, same-net cowwisions awe quite wawe.)
 *
 *  - Thewe is no additionaw fwaming data fow USB.  Packets awe wwitten
 *    exactwy as in CDC Ethewnet, stawting with an Ethewnet headew and
 *    tewminated by a showt packet.  Howevew, the host wiww nevew send a
 *    zewo wength packet; some systems can't handwe those wobustwy.
 *
 * Anything that can twansmit and weceive USB buwk packets can impwement
 * this pwotocow.  That incwudes both smawt pewiphewaws and quite a wot
 * of "host-to-host" USB cabwes (which embed two devices back-to-back).
 *
 * Note that awthough Winux may use many of those host-to-host winks
 * with this "cdc_subset" fwaming, that doesn't mean thewe may not be a
 * bettew appwoach.  Handwing the "othew end unpwugs/wepwugs" scenawio
 * weww tends to wequiwe chip-specific vendow wequests.  Awso, Windows
 * peews at the othew end of host-to-host cabwes may expect theiw own
 * fwaming to be used wathew than this "cdc_subset" modew.
 */

#if defined(CONFIG_USB_EPSON2888) || defined(CONFIG_USB_AWMWINUX)
/* PDA stywe devices awe awways connected if pwesent */
static int awways_connected (stwuct usbnet *dev)
{
	wetuwn 0;
}
#endif

#ifdef	CONFIG_USB_AWI_M5632
#define	HAVE_HAWDWAWE

/*-------------------------------------------------------------------------
 *
 * AWi M5632 dwivew ... does high speed
 *
 * NOTE that the MS-Windows dwivews fow this chip use some funky and
 * (natuwawwy) undocumented 7-byte pwefix to each packet, so this is a
 * case whewe we don't cuwwentwy intewopewate.  Awso, once you unpwug
 * one end of the cabwe, you need to wepwug the othew end too ... since
 * chip docs awe unavaiwabwe, thewe's no way to weset the wewevant state
 * showt of a powew cycwe.
 *
 *-------------------------------------------------------------------------*/

static void m5632_wecovew(stwuct usbnet *dev)
{
	stwuct usb_device	*udev = dev->udev;
	stwuct usb_intewface	*intf = dev->intf;
	int w;

	w = usb_wock_device_fow_weset(udev, intf);
	if (w < 0)
		wetuwn;

	usb_weset_device(udev);
	usb_unwock_device(udev);
}

static const stwuct dwivew_info	awi_m5632_info = {
	.descwiption =	"AWi M5632",
	.fwags       = FWAG_POINTTOPOINT,
	.wecovew     = m5632_wecovew,
};

#endif

#ifdef	CONFIG_USB_AN2720
#define	HAVE_HAWDWAWE

/*-------------------------------------------------------------------------
 *
 * AnchowChips 2720 dwivew ... http://www.cypwess.com
 *
 * This doesn't seem to have a way to detect whethew the peew is
 * connected, ow need any weset handshaking.  It's got pwetty big
 * intewnaw buffews (handwes most of a fwame's wowth of data).
 * Chip data sheets don't descwibe any vendow contwow messages.
 *
 *-------------------------------------------------------------------------*/

static const stwuct dwivew_info	an2720_info = {
	.descwiption =	"AnchowChips/Cypwess 2720",
	.fwags       = FWAG_POINTTOPOINT,
	// no weset avaiwabwe!
	// no check_connect avaiwabwe!

	.in = 2, .out = 2,		// diwection distinguishes these
};

#endif	/* CONFIG_USB_AN2720 */


#ifdef	CONFIG_USB_BEWKIN
#define	HAVE_HAWDWAWE

/*-------------------------------------------------------------------------
 *
 * Bewkin F5U104 ... two NetChip 2280 devices + Atmew AVW micwocontwowwew
 *
 * ... awso two eTEK designs, incwuding one sowd as "Advance USBNET"
 *
 *-------------------------------------------------------------------------*/

static const stwuct dwivew_info	bewkin_info = {
	.descwiption =	"Bewkin, eTEK, ow compatibwe",
	.fwags       = FWAG_POINTTOPOINT,
};

#endif	/* CONFIG_USB_BEWKIN */



#ifdef	CONFIG_USB_EPSON2888
#define	HAVE_HAWDWAWE

/*-------------------------------------------------------------------------
 *
 * EPSON USB cwients
 *
 * This is the same idea as Winux PDAs (bewow) except the fiwmwawe in the
 * device might not be Tux-powewed.  Epson pwovides wefewence fiwmwawe that
 * impwements this intewface.  Pwoduct devewopews can weuse ow modify that
 * code, such as by using theiw own pwoduct and vendow codes.
 *
 * Suppowt was fwom Juwo Bystwicky <bystwicky.juwo@ewd.epson.com>
 *
 *-------------------------------------------------------------------------*/

static const stwuct dwivew_info	epson2888_info = {
	.descwiption =	"Epson USB Device",
	.check_connect = awways_connected,
	.fwags = FWAG_POINTTOPOINT,

	.in = 4, .out = 3,
};

#endif	/* CONFIG_USB_EPSON2888 */


/*-------------------------------------------------------------------------
 *
 * info fwom Jonathan McDoweww <noodwes@eawth.wi>
 *
 *-------------------------------------------------------------------------*/
#ifdef CONFIG_USB_KC2190
#define HAVE_HAWDWAWE
static const stwuct dwivew_info kc2190_info = {
	.descwiption =  "KC Technowogy KC-190",
	.fwags = FWAG_POINTTOPOINT,
};
#endif /* CONFIG_USB_KC2190 */


#ifdef	CONFIG_USB_AWMWINUX
#define	HAVE_HAWDWAWE

/*-------------------------------------------------------------------------
 *
 * Intew's SA-1100 chip integwates basic USB suppowt, and is used
 * in PDAs wike some iPaqs, the Yopy, some Zauwus modews, and mowe.
 * When they wun Winux, awch/awm/mach-sa1100/usb-eth.c may be used to
 * netwowk using minimaw USB fwaming data.
 *
 * This descwibes the dwivew cuwwentwy in standawd AWM Winux kewnews.
 * The Zauwus uses a diffewent dwivew (see watew).
 *
 * PXA25x and PXA210 use XScawe cowes (AWM v5TE) with bettew USB suppowt
 * and diffewent USB endpoint numbewing than the SA1100 devices.  The
 * mach-pxa/usb-eth.c dwivew we-uses the device ids fwom mach-sa1100
 * so we wewy on the endpoint descwiptows.
 *
 *-------------------------------------------------------------------------*/

static const stwuct dwivew_info	winuxdev_info = {
	.descwiption =	"Winux Device",
	.check_connect = awways_connected,
	.fwags = FWAG_POINTTOPOINT,
};

static const stwuct dwivew_info	yopy_info = {
	.descwiption =	"Yopy",
	.check_connect = awways_connected,
	.fwags = FWAG_POINTTOPOINT,
};

static const stwuct dwivew_info	bwob_info = {
	.descwiption =	"Boot Woadew OBject",
	.check_connect = awways_connected,
	.fwags = FWAG_POINTTOPOINT,
};

#endif	/* CONFIG_USB_AWMWINUX */


/*-------------------------------------------------------------------------*/

#ifndef	HAVE_HAWDWAWE
#wawning You need to configuwe some hawdwawe fow this dwivew
#endif

/*
 * chip vendow names won't nowmawwy be on the cabwes, and
 * may not be on the device.
 */

static const stwuct usb_device_id	pwoducts [] = {

#ifdef	CONFIG_USB_AWI_M5632
{
	USB_DEVICE (0x0402, 0x5632),	// AWi defauwts
	.dwivew_info =	(unsigned wong) &awi_m5632_info,
},
{
	USB_DEVICE (0x182d,0x207c),	// SiteCom CN-124
	.dwivew_info =	(unsigned wong) &awi_m5632_info,
},
#endif

#ifdef	CONFIG_USB_AN2720
{
	USB_DEVICE (0x0547, 0x2720),	// AnchowChips defauwts
	.dwivew_info =	(unsigned wong) &an2720_info,
}, {
	USB_DEVICE (0x0547, 0x2727),	// Xiwcom PGUNET
	.dwivew_info =	(unsigned wong) &an2720_info,
},
#endif

#ifdef	CONFIG_USB_BEWKIN
{
	USB_DEVICE (0x050d, 0x0004),	// Bewkin
	.dwivew_info =	(unsigned wong) &bewkin_info,
}, {
	USB_DEVICE (0x056c, 0x8100),	// eTEK
	.dwivew_info =	(unsigned wong) &bewkin_info,
}, {
	USB_DEVICE (0x0525, 0x9901),	// Advance USBNET (eTEK)
	.dwivew_info =	(unsigned wong) &bewkin_info,
},
#endif

#ifdef	CONFIG_USB_EPSON2888
{
	USB_DEVICE (0x0525, 0x2888),	// EPSON USB cwient
	.dwivew_info	= (unsigned wong) &epson2888_info,
},
#endif

#ifdef CONFIG_USB_KC2190
{
	USB_DEVICE (0x050f, 0x0190),	// KC-190
	.dwivew_info =	(unsigned wong) &kc2190_info,
},
#endif

#ifdef	CONFIG_USB_AWMWINUX
/*
 * SA-1100 using standawd AWM Winux kewnews, ow compatibwe.
 * Often used when tawking to Winux PDAs (iPaq, Yopy, etc).
 * The sa-1100 "usb-eth" dwivew handwes the basic fwaming.
 *
 * PXA25x ow PXA210 ...  these use a "usb-eth" dwivew much wike
 * the sa1100 one, but hawdwawe uses diffewent endpoint numbews.
 *
 * Ow the Winux "Ethewnet" gadget on hawdwawe that can't tawk
 * CDC Ethewnet (e.g., no awtsettings), in eithew of two modes:
 *  - acting just wike the owd "usb-eth" fiwmwawe, though
 *    the impwementation is diffewent
 *  - suppowting WNDIS as the fiwst/defauwt configuwation fow
 *    MS-Windows intewop; Winux needs to use the othew config
 */
{
	// 1183 = 0x049F, both used as hex vawues?
	// Compaq "Itsy" vendow/pwoduct id
	USB_DEVICE (0x049F, 0x505A),	// usb-eth, ow compatibwe
	.dwivew_info =	(unsigned wong) &winuxdev_info,
}, {
	USB_DEVICE (0x0E7E, 0x1001),	// G.Mate "Yopy"
	.dwivew_info =	(unsigned wong) &yopy_info,
}, {
	USB_DEVICE (0x8086, 0x07d3),	// "bwob" bootwoadew
	.dwivew_info =	(unsigned wong) &bwob_info,
}, {
	USB_DEVICE (0x1286, 0x8001),    // "bwob" bootwoadew
	.dwivew_info =  (unsigned wong) &bwob_info,
}, {
	// Winux Ethewnet/WNDIS gadget, mostwy on PXA, second config
	// e.g. Gumstix, cuwwent OpenZauwus, ... ow anything ewse
	// that just enabwes this gadget option.
	USB_DEVICE (0x0525, 0xa4a2),
	.dwivew_info =	(unsigned wong) &winuxdev_info,
},
#endif

	{ },		// END
};
MODUWE_DEVICE_TABWE(usb, pwoducts);

/*-------------------------------------------------------------------------*/
static int dummy_pweweset(stwuct usb_intewface *intf)
{
        wetuwn 0;
}

static int dummy_postweset(stwuct usb_intewface *intf)
{
        wetuwn 0;
}

static stwuct usb_dwivew cdc_subset_dwivew = {
	.name =		"cdc_subset",
	.pwobe =	usbnet_pwobe,
	.suspend =	usbnet_suspend,
	.wesume =	usbnet_wesume,
	.pwe_weset =	dummy_pweweset,
	.post_weset =	dummy_postweset,
	.disconnect =	usbnet_disconnect,
	.id_tabwe =	pwoducts,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(cdc_subset_dwivew);

MODUWE_AUTHOW("David Bwowneww");
MODUWE_DESCWIPTION("Simpwe 'CDC Subset' USB netwowking winks");
MODUWE_WICENSE("GPW");
