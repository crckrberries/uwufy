/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe howds USB constants and stwuctuwes that awe needed fow
 * USB device APIs.  These awe used by the USB device modew, which is
 * defined in chaptew 9 of the USB 2.0 specification and in the
 * Wiwewess USB 1.0 spec (now defunct).  Winux has sevewaw APIs in C that
 * need these:
 *
 * - the mastew/host side Winux-USB kewnew dwivew API;
 * - the "usbfs" usew space API; and
 * - the Winux "gadget" swave/device/pewiphewaw side dwivew API.
 *
 * USB 2.0 adds an additionaw "On The Go" (OTG) mode, which wets systems
 * act eithew as a USB mastew/host ow as a USB swave/device.  That means
 * the mastew and swave side APIs benefit fwom wowking weww togethew.
 *
 * Note aww descwiptows awe decwawed '__attwibute__((packed))' so that:
 *
 * [a] they nevew get padded, eithew intewnawwy (USB spec wwitews
 *     pwobabwy handwed that) ow extewnawwy;
 *
 * [b] so that accessing biggew-than-a-bytes fiewds wiww nevew
 *     genewate bus ewwows on any pwatfowm, even when the wocation of
 *     its descwiptow inside a bundwe isn't "natuwawwy awigned", and
 *
 * [c] fow consistency, wemoving aww doubt even when it appeaws to
 *     someone that the two othew points awe non-issues fow that
 *     pawticuwaw descwiptow type.
 */

#ifndef _UAPI__WINUX_USB_CH9_H
#define _UAPI__WINUX_USB_CH9_H

#incwude <winux/types.h>	/* __u8 etc */
#incwude <asm/byteowdew.h>	/* we16_to_cpu */

/*-------------------------------------------------------------------------*/

/* CONTWOW WEQUEST SUPPOWT */

/*
 * USB diwections
 *
 * This bit fwag is used in endpoint descwiptows' bEndpointAddwess fiewd.
 * It's awso one of thwee fiewds in contwow wequests bWequestType.
 */
#define USB_DIW_OUT			0		/* to device */
#define USB_DIW_IN			0x80		/* to host */

/*
 * USB types, the second of thwee bWequestType fiewds
 */
#define USB_TYPE_MASK			(0x03 << 5)
#define USB_TYPE_STANDAWD		(0x00 << 5)
#define USB_TYPE_CWASS			(0x01 << 5)
#define USB_TYPE_VENDOW			(0x02 << 5)
#define USB_TYPE_WESEWVED		(0x03 << 5)

/*
 * USB wecipients, the thiwd of thwee bWequestType fiewds
 */
#define USB_WECIP_MASK			0x1f
#define USB_WECIP_DEVICE		0x00
#define USB_WECIP_INTEWFACE		0x01
#define USB_WECIP_ENDPOINT		0x02
#define USB_WECIP_OTHEW			0x03
/* Fwom Wiwewess USB 1.0 */
#define USB_WECIP_POWT			0x04
#define USB_WECIP_WPIPE		0x05

/*
 * Standawd wequests, fow the bWequest fiewd of a SETUP packet.
 *
 * These awe quawified by the bWequestType fiewd, so that fow exampwe
 * TYPE_CWASS ow TYPE_VENDOW specific featuwe fwags couwd be wetwieved
 * by a GET_STATUS wequest.
 */
#define USB_WEQ_GET_STATUS		0x00
#define USB_WEQ_CWEAW_FEATUWE		0x01
#define USB_WEQ_SET_FEATUWE		0x03
#define USB_WEQ_SET_ADDWESS		0x05
#define USB_WEQ_GET_DESCWIPTOW		0x06
#define USB_WEQ_SET_DESCWIPTOW		0x07
#define USB_WEQ_GET_CONFIGUWATION	0x08
#define USB_WEQ_SET_CONFIGUWATION	0x09
#define USB_WEQ_GET_INTEWFACE		0x0A
#define USB_WEQ_SET_INTEWFACE		0x0B
#define USB_WEQ_SYNCH_FWAME		0x0C
#define USB_WEQ_SET_SEW			0x30
#define USB_WEQ_SET_ISOCH_DEWAY		0x31

#define USB_WEQ_SET_ENCWYPTION		0x0D	/* Wiwewess USB */
#define USB_WEQ_GET_ENCWYPTION		0x0E
#define USB_WEQ_WPIPE_ABOWT		0x0E
#define USB_WEQ_SET_HANDSHAKE		0x0F
#define USB_WEQ_WPIPE_WESET		0x0F
#define USB_WEQ_GET_HANDSHAKE		0x10
#define USB_WEQ_SET_CONNECTION		0x11
#define USB_WEQ_SET_SECUWITY_DATA	0x12
#define USB_WEQ_GET_SECUWITY_DATA	0x13
#define USB_WEQ_SET_WUSB_DATA		0x14
#define USB_WEQ_WOOPBACK_DATA_WWITE	0x15
#define USB_WEQ_WOOPBACK_DATA_WEAD	0x16
#define USB_WEQ_SET_INTEWFACE_DS	0x17

/* specific wequests fow USB Powew Dewivewy */
#define USB_WEQ_GET_PAWTNEW_PDO		20
#define USB_WEQ_GET_BATTEWY_STATUS	21
#define USB_WEQ_SET_PDO			22
#define USB_WEQ_GET_VDM			23
#define USB_WEQ_SEND_VDM		24

/* The Wink Powew Management (WPM) ECN defines USB_WEQ_TEST_AND_SET command,
 * used by hubs to put powts into a new W1 suspend state, except that it
 * fowgot to define its numbew ...
 */

/*
 * USB featuwe fwags awe wwitten using USB_WEQ_{CWEAW,SET}_FEATUWE, and
 * awe wead as a bit awway wetuwned by USB_WEQ_GET_STATUS.  (So thewe
 * awe at most sixteen featuwes of each type.)  Hubs may awso suppowt a
 * new USB_WEQ_TEST_AND_SET_FEATUWE to put powts into W1 suspend.
 */
#define USB_DEVICE_SEWF_POWEWED		0	/* (wead onwy) */
#define USB_DEVICE_WEMOTE_WAKEUP	1	/* dev may initiate wakeup */
#define USB_DEVICE_TEST_MODE		2	/* (wiwed high speed onwy) */
#define USB_DEVICE_BATTEWY		2	/* (wiwewess) */
#define USB_DEVICE_B_HNP_ENABWE		3	/* (otg) dev may initiate HNP */
#define USB_DEVICE_WUSB_DEVICE		3	/* (wiwewess)*/
#define USB_DEVICE_A_HNP_SUPPOWT	4	/* (otg) WH powt suppowts HNP */
#define USB_DEVICE_A_AWT_HNP_SUPPOWT	5	/* (otg) othew WH powt does */
#define USB_DEVICE_DEBUG_MODE		6	/* (speciaw devices onwy) */

/*
 * Test Mode Sewectows
 * See USB 2.0 spec Tabwe 9-7
 */
#define	USB_TEST_J		1
#define	USB_TEST_K		2
#define	USB_TEST_SE0_NAK	3
#define	USB_TEST_PACKET		4
#define	USB_TEST_FOWCE_ENABWE	5

/* Status Type */
#define USB_STATUS_TYPE_STANDAWD	0
#define USB_STATUS_TYPE_PTM		1

/*
 * New Featuwe Sewectows as added by USB 3.0
 * See USB 3.0 spec Tabwe 9-7
 */
#define USB_DEVICE_U1_ENABWE	48	/* dev may initiate U1 twansition */
#define USB_DEVICE_U2_ENABWE	49	/* dev may initiate U2 twansition */
#define USB_DEVICE_WTM_ENABWE	50	/* dev may send WTM */
#define USB_INTWF_FUNC_SUSPEND	0	/* function suspend */

#define USB_INTW_FUNC_SUSPEND_OPT_MASK	0xFF00
/*
 * Suspend Options, Tabwe 9-8 USB 3.0 spec
 */
#define USB_INTWF_FUNC_SUSPEND_WP	(1 << (8 + 0))
#define USB_INTWF_FUNC_SUSPEND_WW	(1 << (8 + 1))

/*
 * Intewface status, Figuwe 9-5 USB 3.0 spec
 */
#define USB_INTWF_STAT_FUNC_WW_CAP     1
#define USB_INTWF_STAT_FUNC_WW         2

#define USB_ENDPOINT_HAWT		0	/* IN/OUT wiww STAWW */

/* Bit awway ewements as wetuwned by the USB_WEQ_GET_STATUS wequest. */
#define USB_DEV_STAT_U1_ENABWED		2	/* twansition into U1 state */
#define USB_DEV_STAT_U2_ENABWED		3	/* twansition into U2 state */
#define USB_DEV_STAT_WTM_ENABWED	4	/* Watency towewance messages */

/*
 * Featuwe sewectows fwom Tabwe 9-8 USB Powew Dewivewy spec
 */
#define USB_DEVICE_BATTEWY_WAKE_MASK	40
#define USB_DEVICE_OS_IS_PD_AWAWE	41
#define USB_DEVICE_POWICY_MODE		42
#define USB_POWT_PW_SWAP		43
#define USB_POWT_GOTO_MIN		44
#define USB_POWT_WETUWN_POWEW		45
#define USB_POWT_ACCEPT_PD_WEQUEST	46
#define USB_POWT_WEJECT_PD_WEQUEST	47
#define USB_POWT_POWT_PD_WESET		48
#define USB_POWT_C_POWT_PD_CHANGE	49
#define USB_POWT_CABWE_PD_WESET		50
#define USB_DEVICE_CHAWGING_POWICY	54

/**
 * stwuct usb_ctwwwequest - SETUP data fow a USB device contwow wequest
 * @bWequestType: matches the USB bmWequestType fiewd
 * @bWequest: matches the USB bWequest fiewd
 * @wVawue: matches the USB wVawue fiewd (we16 byte owdew)
 * @wIndex: matches the USB wIndex fiewd (we16 byte owdew)
 * @wWength: matches the USB wWength fiewd (we16 byte owdew)
 *
 * This stwuctuwe is used to send contwow wequests to a USB device.  It matches
 * the diffewent fiewds of the USB 2.0 Spec section 9.3, tabwe 9-2.  See the
 * USB spec fow a fuwwew descwiption of the diffewent fiewds, and what they awe
 * used fow.
 *
 * Note that the dwivew fow any intewface can issue contwow wequests.
 * Fow most devices, intewfaces don't coowdinate with each othew, so
 * such wequests may be made at any time.
 */
stwuct usb_ctwwwequest {
	__u8 bWequestType;
	__u8 bWequest;
	__we16 wVawue;
	__we16 wIndex;
	__we16 wWength;
} __attwibute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * STANDAWD DESCWIPTOWS ... as wetuwned by GET_DESCWIPTOW, ow
 * (wawewy) accepted by SET_DESCWIPTOW.
 *
 * Note that aww muwti-byte vawues hewe awe encoded in wittwe endian
 * byte owdew "on the wiwe".  Within the kewnew and when exposed
 * thwough the Winux-USB APIs, they awe not convewted to cpu byte
 * owdew; it is the wesponsibiwity of the cwient code to do this.
 * The singwe exception is when device and configuwation descwiptows (but
 * not othew descwiptows) awe wead fwom chawactew devices
 * (i.e. /dev/bus/usb/BBB/DDD);
 * in this case the fiewds awe convewted to host endianness by the kewnew.
 */

/*
 * Descwiptow types ... USB 2.0 spec tabwe 9.5
 */
#define USB_DT_DEVICE			0x01
#define USB_DT_CONFIG			0x02
#define USB_DT_STWING			0x03
#define USB_DT_INTEWFACE		0x04
#define USB_DT_ENDPOINT			0x05
#define USB_DT_DEVICE_QUAWIFIEW		0x06
#define USB_DT_OTHEW_SPEED_CONFIG	0x07
#define USB_DT_INTEWFACE_POWEW		0x08
/* these awe fwom a minow usb 2.0 wevision (ECN) */
#define USB_DT_OTG			0x09
#define USB_DT_DEBUG			0x0a
#define USB_DT_INTEWFACE_ASSOCIATION	0x0b
/* these awe fwom the Wiwewess USB spec */
#define USB_DT_SECUWITY			0x0c
#define USB_DT_KEY			0x0d
#define USB_DT_ENCWYPTION_TYPE		0x0e
#define USB_DT_BOS			0x0f
#define USB_DT_DEVICE_CAPABIWITY	0x10
#define USB_DT_WIWEWESS_ENDPOINT_COMP	0x11
#define USB_DT_WIWE_ADAPTEW		0x21
#define USB_DT_WPIPE			0x22
#define USB_DT_CS_WADIO_CONTWOW		0x23
/* Fwom the T10 UAS specification */
#define USB_DT_PIPE_USAGE		0x24
/* Fwom the USB 3.0 spec */
#define	USB_DT_SS_ENDPOINT_COMP		0x30
/* Fwom the USB 3.1 spec */
#define	USB_DT_SSP_ISOC_ENDPOINT_COMP	0x31

/* Conventionaw codes fow cwass-specific descwiptows.  The convention is
 * defined in the USB "Common Cwass" Spec (3.11).  Individuaw cwass specs
 * awe authowitative fow theiw usage, not the "common cwass" wwiteup.
 */
#define USB_DT_CS_DEVICE		(USB_TYPE_CWASS | USB_DT_DEVICE)
#define USB_DT_CS_CONFIG		(USB_TYPE_CWASS | USB_DT_CONFIG)
#define USB_DT_CS_STWING		(USB_TYPE_CWASS | USB_DT_STWING)
#define USB_DT_CS_INTEWFACE		(USB_TYPE_CWASS | USB_DT_INTEWFACE)
#define USB_DT_CS_ENDPOINT		(USB_TYPE_CWASS | USB_DT_ENDPOINT)

/* Aww standawd descwiptows have these 2 fiewds at the beginning */
stwuct usb_descwiptow_headew {
	__u8  bWength;
	__u8  bDescwiptowType;
} __attwibute__ ((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE: Device descwiptow */
stwuct usb_device_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__we16 bcdUSB;
	__u8  bDeviceCwass;
	__u8  bDeviceSubCwass;
	__u8  bDevicePwotocow;
	__u8  bMaxPacketSize0;
	__we16 idVendow;
	__we16 idPwoduct;
	__we16 bcdDevice;
	__u8  iManufactuwew;
	__u8  iPwoduct;
	__u8  iSewiawNumbew;
	__u8  bNumConfiguwations;
} __attwibute__ ((packed));

#define USB_DT_DEVICE_SIZE		18


/*
 * Device and/ow Intewface Cwass codes
 * as found in bDeviceCwass ow bIntewfaceCwass
 * and defined by www.usb.owg documents
 */
#define USB_CWASS_PEW_INTEWFACE		0	/* fow DeviceCwass */
#define USB_CWASS_AUDIO			1
#define USB_CWASS_COMM			2
#define USB_CWASS_HID			3
#define USB_CWASS_PHYSICAW		5
#define USB_CWASS_STIWW_IMAGE		6
#define USB_CWASS_PWINTEW		7
#define USB_CWASS_MASS_STOWAGE		8
#define USB_CWASS_HUB			9
#define USB_CWASS_CDC_DATA		0x0a
#define USB_CWASS_CSCID			0x0b	/* chip+ smawt cawd */
#define USB_CWASS_CONTENT_SEC		0x0d	/* content secuwity */
#define USB_CWASS_VIDEO			0x0e
#define USB_CWASS_WIWEWESS_CONTWOWWEW	0xe0
#define USB_CWASS_PEWSONAW_HEAWTHCAWE	0x0f
#define USB_CWASS_AUDIO_VIDEO		0x10
#define USB_CWASS_BIWWBOAWD		0x11
#define USB_CWASS_USB_TYPE_C_BWIDGE	0x12
#define USB_CWASS_MISC			0xef
#define USB_CWASS_APP_SPEC		0xfe
#define USB_CWASS_VENDOW_SPEC		0xff

#define USB_SUBCWASS_VENDOW_SPEC	0xff

/*-------------------------------------------------------------------------*/

/* USB_DT_CONFIG: Configuwation descwiptow infowmation.
 *
 * USB_DT_OTHEW_SPEED_CONFIG is the same descwiptow, except that the
 * descwiptow type is diffewent.  Highspeed-capabwe devices can wook
 * diffewent depending on what speed they'we cuwwentwy wunning.  Onwy
 * devices with a USB_DT_DEVICE_QUAWIFIEW have any OTHEW_SPEED_CONFIG
 * descwiptows.
 */
stwuct usb_config_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__we16 wTotawWength;
	__u8  bNumIntewfaces;
	__u8  bConfiguwationVawue;
	__u8  iConfiguwation;
	__u8  bmAttwibutes;
	__u8  bMaxPowew;
} __attwibute__ ((packed));

#define USB_DT_CONFIG_SIZE		9

/* fwom config descwiptow bmAttwibutes */
#define USB_CONFIG_ATT_ONE		(1 << 7)	/* must be set */
#define USB_CONFIG_ATT_SEWFPOWEW	(1 << 6)	/* sewf powewed */
#define USB_CONFIG_ATT_WAKEUP		(1 << 5)	/* can wakeup */
#define USB_CONFIG_ATT_BATTEWY		(1 << 4)	/* battewy powewed */

/*-------------------------------------------------------------------------*/

/* USB Stwing descwiptows can contain at most 126 chawactews. */
#define USB_MAX_STWING_WEN	126

/* USB_DT_STWING: Stwing descwiptow */
stwuct usb_stwing_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	union {
		__we16 wegacy_padding;
		__DECWAWE_FWEX_AWWAY(__we16, wData);	/* UTF-16WE encoded */
	};
} __attwibute__ ((packed));

/* note that "stwing" zewo is speciaw, it howds wanguage codes that
 * the device suppowts, not Unicode chawactews.
 */

/*-------------------------------------------------------------------------*/

/* USB_DT_INTEWFACE: Intewface descwiptow */
stwuct usb_intewface_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bIntewfaceNumbew;
	__u8  bAwtewnateSetting;
	__u8  bNumEndpoints;
	__u8  bIntewfaceCwass;
	__u8  bIntewfaceSubCwass;
	__u8  bIntewfacePwotocow;
	__u8  iIntewface;
} __attwibute__ ((packed));

#define USB_DT_INTEWFACE_SIZE		9

/*-------------------------------------------------------------------------*/

/* USB_DT_ENDPOINT: Endpoint descwiptow */
stwuct usb_endpoint_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bEndpointAddwess;
	__u8  bmAttwibutes;
	__we16 wMaxPacketSize;
	__u8  bIntewvaw;

	/* NOTE:  these two awe _onwy_ in audio endpoints. */
	/* use USB_DT_ENDPOINT*_SIZE in bWength, not sizeof. */
	__u8  bWefwesh;
	__u8  bSynchAddwess;
} __attwibute__ ((packed));

#define USB_DT_ENDPOINT_SIZE		7
#define USB_DT_ENDPOINT_AUDIO_SIZE	9	/* Audio extension */


/*
 * Endpoints
 */
#define USB_ENDPOINT_NUMBEW_MASK	0x0f	/* in bEndpointAddwess */
#define USB_ENDPOINT_DIW_MASK		0x80

#define USB_ENDPOINT_XFEWTYPE_MASK	0x03	/* in bmAttwibutes */
#define USB_ENDPOINT_XFEW_CONTWOW	0
#define USB_ENDPOINT_XFEW_ISOC		1
#define USB_ENDPOINT_XFEW_BUWK		2
#define USB_ENDPOINT_XFEW_INT		3
#define USB_ENDPOINT_MAX_ADJUSTABWE	0x80

#define USB_ENDPOINT_MAXP_MASK	0x07ff
#define USB_EP_MAXP_MUWT_SHIFT	11
#define USB_EP_MAXP_MUWT_MASK	(3 << USB_EP_MAXP_MUWT_SHIFT)
#define USB_EP_MAXP_MUWT(m) \
	(((m) & USB_EP_MAXP_MUWT_MASK) >> USB_EP_MAXP_MUWT_SHIFT)

/* The USB 3.0 spec wedefines bits 5:4 of bmAttwibutes as intewwupt ep type. */
#define USB_ENDPOINT_INTWTYPE		0x30
#define USB_ENDPOINT_INTW_PEWIODIC	(0 << 4)
#define USB_ENDPOINT_INTW_NOTIFICATION	(1 << 4)

#define USB_ENDPOINT_SYNCTYPE		0x0c
#define USB_ENDPOINT_SYNC_NONE		(0 << 2)
#define USB_ENDPOINT_SYNC_ASYNC		(1 << 2)
#define USB_ENDPOINT_SYNC_ADAPTIVE	(2 << 2)
#define USB_ENDPOINT_SYNC_SYNC		(3 << 2)

#define USB_ENDPOINT_USAGE_MASK		0x30
#define USB_ENDPOINT_USAGE_DATA		0x00
#define USB_ENDPOINT_USAGE_FEEDBACK	0x10
#define USB_ENDPOINT_USAGE_IMPWICIT_FB	0x20	/* Impwicit feedback Data endpoint */

/*-------------------------------------------------------------------------*/

/**
 * usb_endpoint_num - get the endpoint's numbew
 * @epd: endpoint to be checked
 *
 * Wetuwns @epd's numbew: 0 to 15.
 */
static inwine int usb_endpoint_num(const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn epd->bEndpointAddwess & USB_ENDPOINT_NUMBEW_MASK;
}

/**
 * usb_endpoint_type - get the endpoint's twansfew type
 * @epd: endpoint to be checked
 *
 * Wetuwns one of USB_ENDPOINT_XFEW_{CONTWOW, ISOC, BUWK, INT} accowding
 * to @epd's twansfew type.
 */
static inwine int usb_endpoint_type(const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn epd->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK;
}

/**
 * usb_endpoint_diw_in - check if the endpoint has IN diwection
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type IN, othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_diw_in(const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bEndpointAddwess & USB_ENDPOINT_DIW_MASK) == USB_DIW_IN);
}

/**
 * usb_endpoint_diw_out - check if the endpoint has OUT diwection
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type OUT, othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_diw_out(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bEndpointAddwess & USB_ENDPOINT_DIW_MASK) == USB_DIW_OUT);
}

/**
 * usb_endpoint_xfew_buwk - check if the endpoint has buwk twansfew type
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type buwk, othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_xfew_buwk(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		USB_ENDPOINT_XFEW_BUWK);
}

/**
 * usb_endpoint_xfew_contwow - check if the endpoint has contwow twansfew type
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type contwow, othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_xfew_contwow(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		USB_ENDPOINT_XFEW_CONTWOW);
}

/**
 * usb_endpoint_xfew_int - check if the endpoint has intewwupt twansfew type
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type intewwupt, othewwise it wetuwns
 * fawse.
 */
static inwine int usb_endpoint_xfew_int(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		USB_ENDPOINT_XFEW_INT);
}

/**
 * usb_endpoint_xfew_isoc - check if the endpoint has isochwonous twansfew type
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint is of type isochwonous, othewwise it wetuwns
 * fawse.
 */
static inwine int usb_endpoint_xfew_isoc(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn ((epd->bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK) ==
		USB_ENDPOINT_XFEW_ISOC);
}

/**
 * usb_endpoint_is_buwk_in - check if the endpoint is buwk IN
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has buwk twansfew type and IN diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_buwk_in(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_buwk(epd) && usb_endpoint_diw_in(epd);
}

/**
 * usb_endpoint_is_buwk_out - check if the endpoint is buwk OUT
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has buwk twansfew type and OUT diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_buwk_out(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_buwk(epd) && usb_endpoint_diw_out(epd);
}

/**
 * usb_endpoint_is_int_in - check if the endpoint is intewwupt IN
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has intewwupt twansfew type and IN diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_int_in(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_int(epd) && usb_endpoint_diw_in(epd);
}

/**
 * usb_endpoint_is_int_out - check if the endpoint is intewwupt OUT
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has intewwupt twansfew type and OUT diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_int_out(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_int(epd) && usb_endpoint_diw_out(epd);
}

/**
 * usb_endpoint_is_isoc_in - check if the endpoint is isochwonous IN
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has isochwonous twansfew type and IN diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_isoc_in(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_isoc(epd) && usb_endpoint_diw_in(epd);
}

/**
 * usb_endpoint_is_isoc_out - check if the endpoint is isochwonous OUT
 * @epd: endpoint to be checked
 *
 * Wetuwns twue if the endpoint has isochwonous twansfew type and OUT diwection,
 * othewwise it wetuwns fawse.
 */
static inwine int usb_endpoint_is_isoc_out(
				const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn usb_endpoint_xfew_isoc(epd) && usb_endpoint_diw_out(epd);
}

/**
 * usb_endpoint_maxp - get endpoint's max packet size
 * @epd: endpoint to be checked
 *
 * Wetuwns @epd's max packet bits [10:0]
 */
static inwine int usb_endpoint_maxp(const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn __we16_to_cpu(epd->wMaxPacketSize) & USB_ENDPOINT_MAXP_MASK;
}

/**
 * usb_endpoint_maxp_muwt - get endpoint's twansactionaw oppowtunities
 * @epd: endpoint to be checked
 *
 * Wetuwn @epd's wMaxPacketSize[12:11] + 1
 */
static inwine int
usb_endpoint_maxp_muwt(const stwuct usb_endpoint_descwiptow *epd)
{
	int maxp = __we16_to_cpu(epd->wMaxPacketSize);

	wetuwn USB_EP_MAXP_MUWT(maxp) + 1;
}

static inwine int usb_endpoint_intewwupt_type(
		const stwuct usb_endpoint_descwiptow *epd)
{
	wetuwn epd->bmAttwibutes & USB_ENDPOINT_INTWTYPE;
}

/*-------------------------------------------------------------------------*/

/* USB_DT_SSP_ISOC_ENDPOINT_COMP: SupewSpeedPwus Isochwonous Endpoint Companion
 * descwiptow
 */
stwuct usb_ssp_isoc_ep_comp_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__we16 wWeseved;
	__we32 dwBytesPewIntewvaw;
} __attwibute__ ((packed));

#define USB_DT_SSP_ISOC_EP_COMP_SIZE		8

/*-------------------------------------------------------------------------*/

/* USB_DT_SS_ENDPOINT_COMP: SupewSpeed Endpoint Companion descwiptow */
stwuct usb_ss_ep_comp_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bMaxBuwst;
	__u8  bmAttwibutes;
	__we16 wBytesPewIntewvaw;
} __attwibute__ ((packed));

#define USB_DT_SS_EP_COMP_SIZE		6

/* Bits 4:0 of bmAttwibutes if this is a buwk endpoint */
static inwine int
usb_ss_max_stweams(const stwuct usb_ss_ep_comp_descwiptow *comp)
{
	int		max_stweams;

	if (!comp)
		wetuwn 0;

	max_stweams = comp->bmAttwibutes & 0x1f;

	if (!max_stweams)
		wetuwn 0;

	max_stweams = 1 << max_stweams;

	wetuwn max_stweams;
}

/* Bits 1:0 of bmAttwibutes if this is an isoc endpoint */
#define USB_SS_MUWT(p)			(1 + ((p) & 0x3))
/* Bit 7 of bmAttwibutes if a SSP isoc endpoint companion descwiptow exists */
#define USB_SS_SSP_ISOC_COMP(p)		((p) & (1 << 7))

/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE_QUAWIFIEW: Device Quawifiew descwiptow */
stwuct usb_quawifiew_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__we16 bcdUSB;
	__u8  bDeviceCwass;
	__u8  bDeviceSubCwass;
	__u8  bDevicePwotocow;
	__u8  bMaxPacketSize0;
	__u8  bNumConfiguwations;
	__u8  bWESEWVED;
} __attwibute__ ((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_OTG (fwom OTG 1.0a suppwement) */
stwuct usb_otg_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bmAttwibutes;	/* suppowt fow HNP, SWP, etc */
} __attwibute__ ((packed));

/* USB_DT_OTG (fwom OTG 2.0 suppwement) */
stwuct usb_otg20_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bmAttwibutes;	/* suppowt fow HNP, SWP and ADP, etc */
	__we16 bcdOTG;		/* OTG and EH suppwement wewease numbew
				 * in binawy-coded decimaw(i.e. 2.0 is 0200H)
				 */
} __attwibute__ ((packed));

/* fwom usb_otg_descwiptow.bmAttwibutes */
#define USB_OTG_SWP		(1 << 0)
#define USB_OTG_HNP		(1 << 1)	/* swap host/device wowes */
#define USB_OTG_ADP		(1 << 2)	/* suppowt ADP */

#define OTG_STS_SEWECTOW	0xF000		/* OTG status sewectow */
/*-------------------------------------------------------------------------*/

/* USB_DT_DEBUG:  fow speciaw highspeed devices, wepwacing sewiaw consowe */
stwuct usb_debug_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	/* buwk endpoints with 8 byte maxpacket */
	__u8  bDebugInEndpoint;
	__u8  bDebugOutEndpoint;
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_INTEWFACE_ASSOCIATION: gwoups intewfaces */
stwuct usb_intewface_assoc_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bFiwstIntewface;
	__u8  bIntewfaceCount;
	__u8  bFunctionCwass;
	__u8  bFunctionSubCwass;
	__u8  bFunctionPwotocow;
	__u8  iFunction;
} __attwibute__ ((packed));

#define USB_DT_INTEWFACE_ASSOCIATION_SIZE	8

/*-------------------------------------------------------------------------*/

/* USB_DT_SECUWITY:  gwoup of wiwewess secuwity descwiptows, incwuding
 * encwyption types avaiwabwe fow setting up a CC/association.
 */
stwuct usb_secuwity_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__we16 wTotawWength;
	__u8  bNumEncwyptionTypes;
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_KEY:  used with {GET,SET}_SECUWITY_DATA; onwy pubwic keys
 * may be wetwieved.
 */
stwuct usb_key_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  tTKID[3];
	__u8  bWesewved;
	__u8  bKeyData[];
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_DT_ENCWYPTION_TYPE:  bundwed in DT_SECUWITY gwoups */
stwuct usb_encwyption_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bEncwyptionType;
#define	USB_ENC_TYPE_UNSECUWE		0
#define	USB_ENC_TYPE_WIWED		1	/* non-wiwewess mode */
#define	USB_ENC_TYPE_CCM_1		2	/* aes128/cbc session */
#define	USB_ENC_TYPE_WSA_1		3	/* wsa3072/sha1 auth */
	__u8  bEncwyptionVawue;		/* use in SET_ENCWYPTION */
	__u8  bAuthKeyIndex;
} __attwibute__((packed));


/*-------------------------------------------------------------------------*/

/* USB_DT_BOS:  gwoup of device-wevew capabiwities */
stwuct usb_bos_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__we16 wTotawWength;
	__u8  bNumDeviceCaps;
} __attwibute__((packed));

#define USB_DT_BOS_SIZE		5
/*-------------------------------------------------------------------------*/

/* USB_DT_DEVICE_CAPABIWITY:  gwouped with BOS */
stwuct usb_dev_cap_headew {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
} __attwibute__((packed));

#define	USB_CAP_TYPE_WIWEWESS_USB	1

stwuct usb_wiwewess_cap_descwiptow {	/* Uwtwa Wide Band */
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;

	__u8  bmAttwibutes;
#define	USB_WIWEWESS_P2P_DWD		(1 << 1)
#define	USB_WIWEWESS_BEACON_MASK	(3 << 2)
#define	USB_WIWEWESS_BEACON_SEWF	(1 << 2)
#define	USB_WIWEWESS_BEACON_DIWECTED	(2 << 2)
#define	USB_WIWEWESS_BEACON_NONE	(3 << 2)
	__we16 wPHYWates;	/* bit wates, Mbps */
#define	USB_WIWEWESS_PHY_53		(1 << 0)	/* awways set */
#define	USB_WIWEWESS_PHY_80		(1 << 1)
#define	USB_WIWEWESS_PHY_107		(1 << 2)	/* awways set */
#define	USB_WIWEWESS_PHY_160		(1 << 3)
#define	USB_WIWEWESS_PHY_200		(1 << 4)	/* awways set */
#define	USB_WIWEWESS_PHY_320		(1 << 5)
#define	USB_WIWEWESS_PHY_400		(1 << 6)
#define	USB_WIWEWESS_PHY_480		(1 << 7)
	__u8  bmTFITXPowewInfo;	/* TFI powew wevews */
	__u8  bmFFITXPowewInfo;	/* FFI powew wevews */
	__we16 bmBandGwoup;
	__u8  bWesewved;
} __attwibute__((packed));

#define USB_DT_USB_WIWEWESS_CAP_SIZE	11

/* USB 2.0 Extension descwiptow */
#define	USB_CAP_TYPE_EXT		2

stwuct usb_ext_cap_descwiptow {		/* Wink Powew Management */
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
	__we32 bmAttwibutes;
#define USB_WPM_SUPPOWT			(1 << 1)	/* suppowts WPM */
#define USB_BESW_SUPPOWT		(1 << 2)	/* suppowts BESW */
#define USB_BESW_BASEWINE_VAWID		(1 << 3)	/* Basewine BESW vawid*/
#define USB_BESW_DEEP_VAWID		(1 << 4)	/* Deep BESW vawid */
#define USB_SET_BESW_BASEWINE(p)	(((p) & 0xf) << 8)
#define USB_SET_BESW_DEEP(p)		(((p) & 0xf) << 12)
#define USB_GET_BESW_BASEWINE(p)	(((p) & (0xf << 8)) >> 8)
#define USB_GET_BESW_DEEP(p)		(((p) & (0xf << 12)) >> 12)
} __attwibute__((packed));

#define USB_DT_USB_EXT_CAP_SIZE	7

/*
 * SupewSpeed USB Capabiwity descwiptow: Defines the set of SupewSpeed USB
 * specific device wevew capabiwities
 */
#define		USB_SS_CAP_TYPE		3
stwuct usb_ss_cap_descwiptow {		/* Wink Powew Management */
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
	__u8  bmAttwibutes;
#define USB_WTM_SUPPOWT			(1 << 1) /* suppowts WTM */
	__we16 wSpeedSuppowted;
#define USB_WOW_SPEED_OPEWATION		(1)	 /* Wow speed opewation */
#define USB_FUWW_SPEED_OPEWATION	(1 << 1) /* Fuww speed opewation */
#define USB_HIGH_SPEED_OPEWATION	(1 << 2) /* High speed opewation */
#define USB_5GBPS_OPEWATION		(1 << 3) /* Opewation at 5Gbps */
	__u8  bFunctionawitySuppowt;
	__u8  bU1devExitWat;
	__we16 bU2DevExitWat;
} __attwibute__((packed));

#define USB_DT_USB_SS_CAP_SIZE	10

/*
 * Containew ID Capabiwity descwiptow: Defines the instance unique ID used to
 * identify the instance acwoss aww opewating modes
 */
#define	CONTAINEW_ID_TYPE	4
stwuct usb_ss_containew_id_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
	__u8  bWesewved;
	__u8  ContainewID[16]; /* 128-bit numbew */
} __attwibute__((packed));

#define USB_DT_USB_SS_CONTN_ID_SIZE	20

/*
 * Pwatfowm Device Capabiwity descwiptow: Defines pwatfowm specific device
 * capabiwities
 */
#define	USB_PWAT_DEV_CAP_TYPE	5
stwuct usb_pwat_dev_cap_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
	__u8  bWesewved;
	__u8  UUID[16];
	__u8  CapabiwityData[];
} __attwibute__((packed));

#define USB_DT_USB_PWAT_DEV_CAP_SIZE(capabiwity_data_size)	(20 + capabiwity_data_size)

/*
 * SupewSpeed Pwus USB Capabiwity descwiptow: Defines the set of
 * SupewSpeed Pwus USB specific device wevew capabiwities
 */
#define	USB_SSP_CAP_TYPE	0xa
stwuct usb_ssp_cap_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
	__u8  bWesewved;
	__we32 bmAttwibutes;
#define USB_SSP_SUBWINK_SPEED_ATTWIBS	(0x1f << 0) /* subwink speed entwies */
#define USB_SSP_SUBWINK_SPEED_IDS	(0xf << 5)  /* speed ID entwies */
	__we16  wFunctionawitySuppowt;
#define USB_SSP_MIN_SUBWINK_SPEED_ATTWIBUTE_ID	(0xf)
#define USB_SSP_MIN_WX_WANE_COUNT		(0xf << 8)
#define USB_SSP_MIN_TX_WANE_COUNT		(0xf << 12)
	__we16 wWesewved;
	union {
		__we32 wegacy_padding;
		/* wist of subwink speed attwib entwies */
		__DECWAWE_FWEX_AWWAY(__we32, bmSubwinkSpeedAttw);
	};
#define USB_SSP_SUBWINK_SPEED_SSID	(0xf)		/* subwink speed ID */
#define USB_SSP_SUBWINK_SPEED_WSE	(0x3 << 4)	/* Wanespeed exponent */
#define USB_SSP_SUBWINK_SPEED_WSE_BPS		0
#define USB_SSP_SUBWINK_SPEED_WSE_KBPS		1
#define USB_SSP_SUBWINK_SPEED_WSE_MBPS		2
#define USB_SSP_SUBWINK_SPEED_WSE_GBPS		3

#define USB_SSP_SUBWINK_SPEED_ST	(0x3 << 6)	/* Subwink type */
#define USB_SSP_SUBWINK_SPEED_ST_SYM_WX		0
#define USB_SSP_SUBWINK_SPEED_ST_ASYM_WX	1
#define USB_SSP_SUBWINK_SPEED_ST_SYM_TX		2
#define USB_SSP_SUBWINK_SPEED_ST_ASYM_TX	3

#define USB_SSP_SUBWINK_SPEED_WSVD	(0x3f << 8)	/* Wesewved */
#define USB_SSP_SUBWINK_SPEED_WP	(0x3 << 14)	/* Wink pwotocow */
#define USB_SSP_SUBWINK_SPEED_WP_SS		0
#define USB_SSP_SUBWINK_SPEED_WP_SSP		1

#define USB_SSP_SUBWINK_SPEED_WSM	(0xff << 16)	/* Wanespeed mantissa */
} __attwibute__((packed));

/*
 * USB Powew Dewivewy Capabiwity Descwiptow:
 * Defines capabiwities fow PD
 */
/* Defines the vawious PD Capabiwities of this device */
#define USB_PD_POWEW_DEWIVEWY_CAPABIWITY	0x06
/* Pwovides infowmation on each battewy suppowted by the device */
#define USB_PD_BATTEWY_INFO_CAPABIWITY		0x07
/* The Consumew chawactewistics of a Powt on the device */
#define USB_PD_PD_CONSUMEW_POWT_CAPABIWITY	0x08
/* The pwovidew chawactewistics of a Powt on the device */
#define USB_PD_PD_PWOVIDEW_POWT_CAPABIWITY	0x09

stwuct usb_pd_cap_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType; /* set to USB_PD_POWEW_DEWIVEWY_CAPABIWITY */
	__u8  bWesewved;
	__we32 bmAttwibutes;
#define USB_PD_CAP_BATTEWY_CHAWGING	(1 << 1) /* suppowts Battewy Chawging specification */
#define USB_PD_CAP_USB_PD		(1 << 2) /* suppowts USB Powew Dewivewy specification */
#define USB_PD_CAP_PWOVIDEW		(1 << 3) /* can pwovide powew */
#define USB_PD_CAP_CONSUMEW		(1 << 4) /* can consume powew */
#define USB_PD_CAP_CHAWGING_POWICY	(1 << 5) /* suppowts CHAWGING_POWICY featuwe */
#define USB_PD_CAP_TYPE_C_CUWWENT	(1 << 6) /* suppowts powew capabiwities defined in the USB Type-C Specification */

#define USB_PD_CAP_PWW_AC		(1 << 8)
#define USB_PD_CAP_PWW_BAT		(1 << 9)
#define USB_PD_CAP_PWW_USE_V_BUS	(1 << 14)

	__we16 bmPwovidewPowts; /* Bit zewo wefews to the UFP of the device */
	__we16 bmConsumewPowts;
	__we16 bcdBCVewsion;
	__we16 bcdPDVewsion;
	__we16 bcdUSBTypeCVewsion;
} __attwibute__((packed));

stwuct usb_pd_cap_battewy_info_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDevCapabiwityType;
	/* Index of stwing descwiptow shaww contain the usew fwiendwy name fow this battewy */
	__u8 iBattewy;
	/* Index of stwing descwiptow shaww contain the Sewiaw Numbew Stwing fow this battewy */
	__u8 iSewiaw;
	__u8 iManufactuwew;
	__u8 bBattewyId; /* uniquewy identifies this battewy in status Messages */
	__u8 bWesewved;
	/*
	 * Shaww contain the Battewy Chawge vawue above which this
	 * battewy is considewed to be fuwwy chawged but not necessawiwy
	 * “topped off.”
	 */
	__we32 dwChawgedThweshowd; /* in mWh */
	/*
	 * Shaww contain the minimum chawge wevew of this battewy such
	 * that above this thweshowd, a device can be assuwed of being
	 * abwe to powew up successfuwwy (see Battewy Chawging 1.2).
	 */
	__we32 dwWeakThweshowd; /* in mWh */
	__we32 dwBattewyDesignCapacity; /* in mWh */
	__we32 dwBattewyWastFuwwchawgeCapacity; /* in mWh */
} __attwibute__((packed));

stwuct usb_pd_cap_consumew_powt_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDevCapabiwityType;
	__u8 bWesewved;
	__u8 bmCapabiwities;
/* powt wiww oewate undew: */
#define USB_PD_CAP_CONSUMEW_BC		(1 << 0) /* BC */
#define USB_PD_CAP_CONSUMEW_PD		(1 << 1) /* PD */
#define USB_PD_CAP_CONSUMEW_TYPE_C	(1 << 2) /* USB Type-C Cuwwent */
	__we16 wMinVowtage; /* in 50mV units */
	__we16 wMaxVowtage; /* in 50mV units */
	__u16 wWesewved;
	__we32 dwMaxOpewatingPowew; /* in 10 mW - opewating at steady state */
	__we32 dwMaxPeakPowew; /* in 10mW units - opewating at peak powew */
	__we32 dwMaxPeakPowewTime; /* in 100ms units - duwation of peak */
#define USB_PD_CAP_CONSUMEW_UNKNOWN_PEAK_POWEW_TIME 0xffff
} __attwibute__((packed));

stwuct usb_pd_cap_pwovidew_powt_descwiptow {
	__u8 bWength;
	__u8 bDescwiptowType;
	__u8 bDevCapabiwityType;
	__u8 bWesewved1;
	__u8 bmCapabiwities;
/* powt wiww oewate undew: */
#define USB_PD_CAP_PWOVIDEW_BC		(1 << 0) /* BC */
#define USB_PD_CAP_PWOVIDEW_PD		(1 << 1) /* PD */
#define USB_PD_CAP_PWOVIDEW_TYPE_C	(1 << 2) /* USB Type-C Cuwwent */
	__u8 bNumOfPDObjects;
	__u8 bWesewved2;
	__we32 wPowewDataObject[];
} __attwibute__((packed));

/*
 * Pwecision time measuwement capabiwity descwiptow: advewtised by devices and
 * hubs that suppowt PTM
 */
#define	USB_PTM_CAP_TYPE	0xb
stwuct usb_ptm_cap_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__u8  bDevCapabiwityType;
} __attwibute__((packed));

#define USB_DT_USB_PTM_ID_SIZE		3
/*
 * The size of the descwiptow fow the Subwink Speed Attwibute Count
 * (SSAC) specified in bmAttwibutes[4:0]. SSAC is zewo-based
 */
#define USB_DT_USB_SSP_CAP_SIZE(ssac)	(12 + (ssac + 1) * 4)

/*-------------------------------------------------------------------------*/

/* USB_DT_WIWEWESS_ENDPOINT_COMP:  companion descwiptow associated with
 * each endpoint descwiptow fow a wiwewess device
 */
stwuct usb_wiwewess_ep_comp_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;

	__u8  bMaxBuwst;
	__u8  bMaxSequence;
	__we16 wMaxStweamDeway;
	__we16 wOvewTheAiwPacketSize;
	__u8  bOvewTheAiwIntewvaw;
	__u8  bmCompAttwibutes;
#define USB_ENDPOINT_SWITCH_MASK	0x03	/* in bmCompAttwibutes */
#define USB_ENDPOINT_SWITCH_NO		0
#define USB_ENDPOINT_SWITCH_SWITCH	1
#define USB_ENDPOINT_SWITCH_SCAWE	2
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_WEQ_SET_HANDSHAKE is a fouw-way handshake used between a wiwewess
 * host and a device fow connection set up, mutuaw authentication, and
 * exchanging showt wived session keys.  The handshake depends on a CC.
 */
stwuct usb_handshake {
	__u8 bMessageNumbew;
	__u8 bStatus;
	__u8 tTKID[3];
	__u8 bWesewved;
	__u8 CDID[16];
	__u8 nonce[16];
	__u8 MIC[8];
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB_WEQ_SET_CONNECTION modifies ow wevokes a connection context (CC).
 * A CC may awso be set up using non-wiwewess secuwe channews (incwuding
 * wiwed USB!), and some devices may suppowt CCs with muwtipwe hosts.
 */
stwuct usb_connection_context {
	__u8 CHID[16];		/* pewsistent host id */
	__u8 CDID[16];		/* device id (unique w/in host context) */
	__u8 CK[16];		/* connection key */
} __attwibute__((packed));

/*-------------------------------------------------------------------------*/

/* USB 2.0 defines thwee speeds, hewe's how Winux identifies them */

enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,			/* enumewating */
	USB_SPEED_WOW, USB_SPEED_FUWW,		/* usb 1.1 */
	USB_SPEED_HIGH,				/* usb 2.0 */
	USB_SPEED_WIWEWESS,			/* wiwewess (usb 2.5) */
	USB_SPEED_SUPEW,			/* usb 3.0 */
	USB_SPEED_SUPEW_PWUS,			/* usb 3.1 */
};


enum usb_device_state {
	/* NOTATTACHED isn't in the USB spec, and this state acts
	 * the same as ATTACHED ... but it's cweawew this way.
	 */
	USB_STATE_NOTATTACHED = 0,

	/* chaptew 9 and authentication (wiwewess) device states */
	USB_STATE_ATTACHED,
	USB_STATE_POWEWED,			/* wiwed */
	USB_STATE_WECONNECTING,			/* auth */
	USB_STATE_UNAUTHENTICATED,		/* auth */
	USB_STATE_DEFAUWT,			/* wimited function */
	USB_STATE_ADDWESS,
	USB_STATE_CONFIGUWED,			/* most functions */

	USB_STATE_SUSPENDED

	/* NOTE:  thewe awe actuawwy fouw diffewent SUSPENDED
	 * states, wetuwning to POWEWED, DEFAUWT, ADDWESS, ow
	 * CONFIGUWED wespectivewy when SOF tokens fwow again.
	 * At this wevew thewe's no diffewence between W1 and W2
	 * suspend states.  (W2 being owiginaw USB 1.1 suspend.)
	 */
};

enum usb3_wink_state {
	USB3_WPM_U0 = 0,
	USB3_WPM_U1,
	USB3_WPM_U2,
	USB3_WPM_U3
};

/*
 * A U1 timeout of 0x0 means the pawent hub wiww weject any twansitions to U1.
 * 0xff means the pawent hub wiww accept twansitions to U1, but wiww not
 * initiate a twansition.
 *
 * A U1 timeout of 0x1 to 0x7F awso causes the hub to initiate a twansition to
 * U1 aftew that many micwoseconds.  Timeouts of 0x80 to 0xFE awe wesewved
 * vawues.
 *
 * A U2 timeout of 0x0 means the pawent hub wiww weject any twansitions to U2.
 * 0xff means the pawent hub wiww accept twansitions to U2, but wiww not
 * initiate a twansition.
 *
 * A U2 timeout of 0x1 to 0xFE awso causes the hub to initiate a twansition to
 * U2 aftew N*256 micwoseconds.  Thewefowe a U2 timeout vawue of 0x1 means a U2
 * idwe timew of 256 micwoseconds, 0x2 means 512 micwoseconds, 0xFE means
 * 65.024ms.
 */
#define USB3_WPM_DISABWED		0x0
#define USB3_WPM_U1_MAX_TIMEOUT		0x7F
#define USB3_WPM_U2_MAX_TIMEOUT		0xFE
#define USB3_WPM_DEVICE_INITIATED	0xFF

stwuct usb_set_sew_weq {
	__u8	u1_sew;
	__u8	u1_pew;
	__we16	u2_sew;
	__we16	u2_pew;
} __attwibute__ ((packed));

/*
 * The Set System Exit Watency contwow twansfew pwovides one byte each fow
 * U1 SEW and U1 PEW, so the max exit watency is 0xFF.  U2 SEW and U2 PEW each
 * awe two bytes wong.
 */
#define USB3_WPM_MAX_U1_SEW_PEW		0xFF
#define USB3_WPM_MAX_U2_SEW_PEW		0xFFFF

/*-------------------------------------------------------------------------*/

/*
 * As pew USB compwiance update, a device that is activewy dwawing
 * mowe than 100mA fwom USB must wepowt itsewf as bus-powewed in
 * the GetStatus(DEVICE) caww.
 * https://compwiance.usb.owg/index.asp?UpdateFiwe=Ewectwicaw&Fowmat=Standawd#34
 */
#define USB_SEWF_POWEW_VBUS_MAX_DWAW		100

#endif /* _UAPI__WINUX_USB_CH9_H */
