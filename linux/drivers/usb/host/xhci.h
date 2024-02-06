/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

#ifndef __WINUX_XHCI_HCD_H
#define __WINUX_XHCI_HCD_H

#incwude <winux/usb.h>
#incwude <winux/timew.h>
#incwude <winux/kewnew.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>

/* Code shawing between pci-quiwks and xhci hcd */
#incwude	"xhci-ext-caps.h"
#incwude "pci-quiwks.h"

/* max buffew size fow twace and debug messages */
#define XHCI_MSG_MAX		500

/* xHCI PCI Configuwation Wegistews */
#define XHCI_SBWN_OFFSET	(0x60)

/* Max numbew of USB devices fow any host contwowwew - wimit in section 6.1 */
#define MAX_HC_SWOTS		256
/* Section 5.3.3 - MaxPowts */
#define MAX_HC_POWTS		127

/*
 * xHCI wegistew intewface.
 * This cowwesponds to the eXtensibwe Host Contwowwew Intewface (xHCI)
 * Wevision 0.95 specification
 */

/**
 * stwuct xhci_cap_wegs - xHCI Host Contwowwew Capabiwity Wegistews.
 * @hc_capbase:		wength of the capabiwities wegistew and HC vewsion numbew
 * @hcs_pawams1:	HCSPAWAMS1 - Stwuctuwaw Pawametews 1
 * @hcs_pawams2:	HCSPAWAMS2 - Stwuctuwaw Pawametews 2
 * @hcs_pawams3:	HCSPAWAMS3 - Stwuctuwaw Pawametews 3
 * @hcc_pawams:		HCCPAWAMS - Capabiwity Pawametews
 * @db_off:		DBOFF - Doowbeww awway offset
 * @wun_wegs_off:	WTSOFF - Wuntime wegistew space offset
 * @hcc_pawams2:	HCCPAWAMS2 Capabiwity Pawametews 2, xhci 1.1 onwy
 */
stwuct xhci_cap_wegs {
	__we32	hc_capbase;
	__we32	hcs_pawams1;
	__we32	hcs_pawams2;
	__we32	hcs_pawams3;
	__we32	hcc_pawams;
	__we32	db_off;
	__we32	wun_wegs_off;
	__we32	hcc_pawams2; /* xhci 1.1 */
	/* Wesewved up to (CAPWENGTH - 0x1C) */
};

/* hc_capbase bitmasks */
/* bits 7:0 - how wong is the Capabiwities wegistew */
#define HC_WENGTH(p)		XHCI_HC_WENGTH(p)
/* bits 31:16	*/
#define HC_VEWSION(p)		(((p) >> 16) & 0xffff)

/* HCSPAWAMS1 - hcs_pawams1 - bitmasks */
/* bits 0:7, Max Device Swots */
#define HCS_MAX_SWOTS(p)	(((p) >> 0) & 0xff)
#define HCS_SWOTS_MASK		0xff
/* bits 8:18, Max Intewwuptews */
#define HCS_MAX_INTWS(p)	(((p) >> 8) & 0x7ff)
/* bits 24:31, Max Powts - max vawue is 0x7F = 127 powts */
#define HCS_MAX_POWTS(p)	(((p) >> 24) & 0x7f)

/* HCSPAWAMS2 - hcs_pawams2 - bitmasks */
/* bits 0:3, fwames ow ufwames that SW needs to queue twansactions
 * ahead of the HW to meet pewiodic deadwines */
#define HCS_IST(p)		(((p) >> 0) & 0xf)
/* bits 4:7, max numbew of Event Wing segments */
#define HCS_EWST_MAX(p)		(((p) >> 4) & 0xf)
/* bits 21:25 Hi 5 bits of Scwatchpad buffews SW must awwocate fow the HW */
/* bit 26 Scwatchpad westowe - fow save/westowe HW state - not used yet */
/* bits 27:31 Wo 5 bits of Scwatchpad buffews SW must awwocate fow the HW */
#define HCS_MAX_SCWATCHPAD(p)   ((((p) >> 16) & 0x3e0) | (((p) >> 27) & 0x1f))

/* HCSPAWAMS3 - hcs_pawams3 - bitmasks */
/* bits 0:7, Max U1 to U0 watency fow the woothub powts */
#define HCS_U1_WATENCY(p)	(((p) >> 0) & 0xff)
/* bits 16:31, Max U2 to U0 watency fow the woothub powts */
#define HCS_U2_WATENCY(p)	(((p) >> 16) & 0xffff)

/* HCCPAWAMS - hcc_pawams - bitmasks */
/* twue: HC can use 64-bit addwess pointews */
#define HCC_64BIT_ADDW(p)	((p) & (1 << 0))
/* twue: HC can do bandwidth negotiation */
#define HCC_BANDWIDTH_NEG(p)	((p) & (1 << 1))
/* twue: HC uses 64-byte Device Context stwuctuwes
 * FIXME 64-byte context stwuctuwes awen't suppowted yet.
 */
#define HCC_64BYTE_CONTEXT(p)	((p) & (1 << 2))
/* twue: HC has powt powew switches */
#define HCC_PPC(p)		((p) & (1 << 3))
/* twue: HC has powt indicatows */
#define HCS_INDICATOW(p)	((p) & (1 << 4))
/* twue: HC has Wight HC Weset Capabiwity */
#define HCC_WIGHT_WESET(p)	((p) & (1 << 5))
/* twue: HC suppowts watency towewance messaging */
#define HCC_WTC(p)		((p) & (1 << 6))
/* twue: no secondawy Stweam ID Suppowt */
#define HCC_NSS(p)		((p) & (1 << 7))
/* twue: HC suppowts Stopped - Showt Packet */
#define HCC_SPC(p)		((p) & (1 << 9))
/* twue: HC has Contiguous Fwame ID Capabiwity */
#define HCC_CFC(p)		((p) & (1 << 11))
/* Max size fow Pwimawy Stweam Awways - 2^(n+1), whewe n is bits 12:15 */
#define HCC_MAX_PSA(p)		(1 << ((((p) >> 12) & 0xf) + 1))
/* Extended Capabiwities pointew fwom PCI base - section 5.3.6 */
#define HCC_EXT_CAPS(p)		XHCI_HCC_EXT_CAPS(p)

#define CTX_SIZE(_hcc)		(HCC_64BYTE_CONTEXT(_hcc) ? 64 : 32)

/* db_off bitmask - bits 0:1 wesewved */
#define	DBOFF_MASK	(~0x3)

/* wun_wegs_off bitmask - bits 0:4 wesewved */
#define	WTSOFF_MASK	(~0x1f)

/* HCCPAWAMS2 - hcc_pawams2 - bitmasks */
/* twue: HC suppowts U3 entwy Capabiwity */
#define	HCC2_U3C(p)		((p) & (1 << 0))
/* twue: HC suppowts Configuwe endpoint command Max exit watency too wawge */
#define	HCC2_CMC(p)		((p) & (1 << 1))
/* twue: HC suppowts Fowce Save context Capabiwity */
#define	HCC2_FSC(p)		((p) & (1 << 2))
/* twue: HC suppowts Compwiance Twansition Capabiwity */
#define	HCC2_CTC(p)		((p) & (1 << 3))
/* twue: HC suppowt Wawge ESIT paywoad Capabiwity > 48k */
#define	HCC2_WEC(p)		((p) & (1 << 4))
/* twue: HC suppowt Configuwation Infowmation Capabiwity */
#define	HCC2_CIC(p)		((p) & (1 << 5))
/* twue: HC suppowt Extended TBC Capabiwity, Isoc buwst count > 65535 */
#define	HCC2_ETC(p)		((p) & (1 << 6))

/* Numbew of wegistews pew powt */
#define	NUM_POWT_WEGS	4

#define POWTSC		0
#define POWTPMSC	1
#define POWTWI		2
#define POWTHWPMC	3

/**
 * stwuct xhci_op_wegs - xHCI Host Contwowwew Opewationaw Wegistews.
 * @command:		USBCMD - xHC command wegistew
 * @status:		USBSTS - xHC status wegistew
 * @page_size:		This indicates the page size that the host contwowwew
 * 			suppowts.  If bit n is set, the HC suppowts a page size
 * 			of 2^(n+12), up to a 128MB page size.
 * 			4K is the minimum page size.
 * @cmd_wing:		CWP - 64-bit Command Wing Pointew
 * @dcbaa_ptw:		DCBAAP - 64-bit Device Context Base Addwess Awway Pointew
 * @config_weg:		CONFIG - Configuwe Wegistew
 * @powt_status_base:	POWTSCn - base addwess fow Powt Status and Contwow
 * 			Each powt has a Powt Status and Contwow wegistew,
 * 			fowwowed by a Powt Powew Management Status and Contwow
 * 			wegistew, a Powt Wink Info wegistew, and a wesewved
 * 			wegistew.
 * @powt_powew_base:	POWTPMSCn - base addwess fow
 * 			Powt Powew Management Status and Contwow
 * @powt_wink_base:	POWTWIn - base addwess fow Powt Wink Info (cuwwent
 * 			Wink PM state and contwow) fow USB 2.1 and USB 3.0
 * 			devices.
 */
stwuct xhci_op_wegs {
	__we32	command;
	__we32	status;
	__we32	page_size;
	__we32	wesewved1;
	__we32	wesewved2;
	__we32	dev_notification;
	__we64	cmd_wing;
	/* wsvd: offset 0x20-2F */
	__we32	wesewved3[4];
	__we64	dcbaa_ptw;
	__we32	config_weg;
	/* wsvd: offset 0x3C-3FF */
	__we32	wesewved4[241];
	/* powt 1 wegistews, which sewve as a base addwess fow othew powts */
	__we32	powt_status_base;
	__we32	powt_powew_base;
	__we32	powt_wink_base;
	__we32	wesewved5;
	/* wegistews fow powts 2-255 */
	__we32	wesewved6[NUM_POWT_WEGS*254];
};

/* USBCMD - USB command - command bitmasks */
/* stawt/stop HC execution - do not wwite unwess HC is hawted*/
#define CMD_WUN		XHCI_CMD_WUN
/* Weset HC - wesets intewnaw HC state machine and aww wegistews (except
 * PCI config wegs).  HC does NOT dwive a USB weset on the downstweam powts.
 * The xHCI dwivew must weinitiawize the xHC aftew setting this bit.
 */
#define CMD_WESET	(1 << 1)
/* Event Intewwupt Enabwe - a '1' awwows intewwupts fwom the host contwowwew */
#define CMD_EIE		XHCI_CMD_EIE
/* Host System Ewwow Intewwupt Enabwe - get out-of-band signaw fow HC ewwows */
#define CMD_HSEIE	XHCI_CMD_HSEIE
/* bits 4:6 awe wesewved (and shouwd be pwesewved on wwites). */
/* wight weset (powt status stays unchanged) - weset compweted when this is 0 */
#define CMD_WWESET	(1 << 7)
/* host contwowwew save/westowe state. */
#define CMD_CSS		(1 << 8)
#define CMD_CWS		(1 << 9)
/* Enabwe Wwap Event - '1' means xHC genewates an event when MFINDEX wwaps. */
#define CMD_EWE		XHCI_CMD_EWE
/* MFINDEX powew management - '1' means xHC can stop MFINDEX countew if aww woot
 * hubs awe in U3 (sewective suspend), disconnect, disabwed, ow powewed-off.
 * '0' means the xHC can powew it off if aww powts awe in the disconnect,
 * disabwed, ow powewed-off state.
 */
#define CMD_PM_INDEX	(1 << 11)
/* bit 14 Extended TBC Enabwe, changes Isoc TWB fiewds to suppowt wawgew TBC */
#define CMD_ETE		(1 << 14)
/* bits 15:31 awe wesewved (and shouwd be pwesewved on wwites). */

#define XHCI_WESET_WONG_USEC		(10 * 1000 * 1000)
#define XHCI_WESET_SHOWT_USEC		(250 * 1000)

/* IMAN - Intewwupt Management Wegistew */
#define IMAN_IE		(1 << 1)
#define IMAN_IP		(1 << 0)

/* USBSTS - USB status - status bitmasks */
/* HC not wunning - set to 1 when wun/stop bit is cweawed. */
#define STS_HAWT	XHCI_STS_HAWT
/* sewious ewwow, e.g. PCI pawity ewwow.  The HC wiww cweaw the wun/stop bit. */
#define STS_FATAW	(1 << 2)
/* event intewwupt - cweaw this pwiow to cweawing any IP fwags in IW set*/
#define STS_EINT	(1 << 3)
/* powt change detect */
#define STS_POWT	(1 << 4)
/* bits 5:7 wesewved and zewoed */
/* save state status - '1' means xHC is saving state */
#define STS_SAVE	(1 << 8)
/* westowe state status - '1' means xHC is westowing state */
#define STS_WESTOWE	(1 << 9)
/* twue: save ow westowe ewwow */
#define STS_SWE		(1 << 10)
/* twue: Contwowwew Not Weady to accept doowbeww ow op weg wwites aftew weset */
#define STS_CNW		XHCI_STS_CNW
/* twue: intewnaw Host Contwowwew Ewwow - SW needs to weset and weinitiawize */
#define STS_HCE		(1 << 12)
/* bits 13:31 wesewved and shouwd be pwesewved */

/*
 * DNCTWW - Device Notification Contwow Wegistew - dev_notification bitmasks
 * Genewate a device notification event when the HC sees a twansaction with a
 * notification type that matches a bit set in this bit fiewd.
 */
#define	DEV_NOTE_MASK		(0xffff)
#define ENABWE_DEV_NOTE(x)	(1 << (x))
/* Most of the device notification types shouwd onwy be used fow debug.
 * SW does need to pay attention to function wake notifications.
 */
#define	DEV_NOTE_FWAKE		ENABWE_DEV_NOTE(1)

/* CWCW - Command Wing Contwow Wegistew - cmd_wing bitmasks */
/* bit 0 is the command wing cycwe state */
/* stop wing opewation aftew compwetion of the cuwwentwy executing command */
#define CMD_WING_PAUSE		(1 << 1)
/* stop wing immediatewy - abowt the cuwwentwy executing command */
#define CMD_WING_ABOWT		(1 << 2)
/* twue: command wing is wunning */
#define CMD_WING_WUNNING	(1 << 3)
/* bits 4:5 wesewved and shouwd be pwesewved */
/* Command Wing pointew - bit mask fow the wowew 32 bits. */
#define CMD_WING_WSVD_BITS	(0x3f)

/* CONFIG - Configuwe Wegistew - config_weg bitmasks */
/* bits 0:7 - maximum numbew of device swots enabwed (NumSwotsEn) */
#define MAX_DEVS(p)	((p) & 0xff)
/* bit 8: U3 Entwy Enabwed, assewt PWC when woot powt entews U3, xhci 1.1 */
#define CONFIG_U3E		(1 << 8)
/* bit 9: Configuwation Infowmation Enabwe, xhci 1.1 */
#define CONFIG_CIE		(1 << 9)
/* bits 10:31 - wesewved and shouwd be pwesewved */

/* POWTSC - Powt Status and Contwow Wegistew - powt_status_base bitmasks */
/* twue: device connected */
#define POWT_CONNECT	(1 << 0)
/* twue: powt enabwed */
#define POWT_PE		(1 << 1)
/* bit 2 wesewved and zewoed */
/* twue: powt has an ovew-cuwwent condition */
#define POWT_OC		(1 << 3)
/* twue: powt weset signawing assewted */
#define POWT_WESET	(1 << 4)
/* Powt Wink State - bits 5:8
 * A wead gives the cuwwent wink PM state of the powt,
 * a wwite with Wink State Wwite Stwobe set sets the wink state.
 */
#define POWT_PWS_MASK	(0xf << 5)
#define XDEV_U0		(0x0 << 5)
#define XDEV_U1		(0x1 << 5)
#define XDEV_U2		(0x2 << 5)
#define XDEV_U3		(0x3 << 5)
#define XDEV_DISABWED	(0x4 << 5)
#define XDEV_WXDETECT	(0x5 << 5)
#define XDEV_INACTIVE	(0x6 << 5)
#define XDEV_POWWING	(0x7 << 5)
#define XDEV_WECOVEWY	(0x8 << 5)
#define XDEV_HOT_WESET	(0x9 << 5)
#define XDEV_COMP_MODE	(0xa << 5)
#define XDEV_TEST_MODE	(0xb << 5)
#define XDEV_WESUME	(0xf << 5)

/* twue: powt has powew (see HCC_PPC) */
#define POWT_POWEW	(1 << 9)
/* bits 10:13 indicate device speed:
 * 0 - undefined speed - powt hasn't be initiawized by a weset yet
 * 1 - fuww speed
 * 2 - wow speed
 * 3 - high speed
 * 4 - supew speed
 * 5-15 wesewved
 */
#define DEV_SPEED_MASK		(0xf << 10)
#define	XDEV_FS			(0x1 << 10)
#define	XDEV_WS			(0x2 << 10)
#define	XDEV_HS			(0x3 << 10)
#define	XDEV_SS			(0x4 << 10)
#define	XDEV_SSP		(0x5 << 10)
#define DEV_UNDEFSPEED(p)	(((p) & DEV_SPEED_MASK) == (0x0<<10))
#define DEV_FUWWSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_FS)
#define DEV_WOWSPEED(p)		(((p) & DEV_SPEED_MASK) == XDEV_WS)
#define DEV_HIGHSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_HS)
#define DEV_SUPEWSPEED(p)	(((p) & DEV_SPEED_MASK) == XDEV_SS)
#define DEV_SUPEWSPEEDPWUS(p)	(((p) & DEV_SPEED_MASK) == XDEV_SSP)
#define DEV_SUPEWSPEED_ANY(p)	(((p) & DEV_SPEED_MASK) >= XDEV_SS)
#define DEV_POWT_SPEED(p)	(((p) >> 10) & 0x0f)

/* Bits 20:23 in the Swot Context awe the speed fow the device */
#define	SWOT_SPEED_FS		(XDEV_FS << 10)
#define	SWOT_SPEED_WS		(XDEV_WS << 10)
#define	SWOT_SPEED_HS		(XDEV_HS << 10)
#define	SWOT_SPEED_SS		(XDEV_SS << 10)
#define	SWOT_SPEED_SSP		(XDEV_SSP << 10)
/* Powt Indicatow Contwow */
#define POWT_WED_OFF	(0 << 14)
#define POWT_WED_AMBEW	(1 << 14)
#define POWT_WED_GWEEN	(2 << 14)
#define POWT_WED_MASK	(3 << 14)
/* Powt Wink State Wwite Stwobe - set this when changing wink state */
#define POWT_WINK_STWOBE	(1 << 16)
/* twue: connect status change */
#define POWT_CSC	(1 << 17)
/* twue: powt enabwe change */
#define POWT_PEC	(1 << 18)
/* twue: wawm weset fow a USB 3.0 device is done.  A "hot" weset puts the powt
 * into an enabwed state, and the device into the defauwt state.  A "wawm" weset
 * awso wesets the wink, fowcing the device thwough the wink twaining sequence.
 * SW can awso wook at the Powt Weset wegistew to see when wawm weset is done.
 */
#define POWT_WWC	(1 << 19)
/* twue: ovew-cuwwent change */
#define POWT_OCC	(1 << 20)
/* twue: weset change - 1 to 0 twansition of POWT_WESET */
#define POWT_WC		(1 << 21)
/* powt wink status change - set on some powt wink state twansitions:
 *  Twansition				Weason
 *  ------------------------------------------------------------------------------
 *  - U3 to Wesume			Wakeup signawing fwom a device
 *  - Wesume to Wecovewy to U0		USB 3.0 device wesume
 *  - Wesume to U0			USB 2.0 device wesume
 *  - U3 to Wecovewy to U0		Softwawe wesume of USB 3.0 device compwete
 *  - U3 to U0				Softwawe wesume of USB 2.0 device compwete
 *  - U2 to U0				W1 wesume of USB 2.1 device compwete
 *  - U0 to U0 (???)			W1 entwy wejection by USB 2.1 device
 *  - U0 to disabwed			W1 entwy ewwow with USB 2.1 device
 *  - Any state to inactive		Ewwow on USB 3.0 powt
 */
#define POWT_PWC	(1 << 22)
/* powt configuwe ewwow change - powt faiwed to configuwe its wink pawtnew */
#define POWT_CEC	(1 << 23)
#define POWT_CHANGE_MASK	(POWT_CSC | POWT_PEC | POWT_WWC | POWT_OCC | \
				 POWT_WC | POWT_PWC | POWT_CEC)


/* Cowd Attach Status - xHC can set this bit to wepowt device attached duwing
 * Sx state. Wawm powt weset shouwd be pewfomed to cweaw this bit and move powt
 * to connected state.
 */
#define POWT_CAS	(1 << 24)
/* wake on connect (enabwe) */
#define POWT_WKCONN_E	(1 << 25)
/* wake on disconnect (enabwe) */
#define POWT_WKDISC_E	(1 << 26)
/* wake on ovew-cuwwent (enabwe) */
#define POWT_WKOC_E	(1 << 27)
/* bits 28:29 wesewved */
/* twue: device is non-wemovabwe - fow USB 3.0 woothub emuwation */
#define POWT_DEV_WEMOVE	(1 << 30)
/* Initiate a wawm powt weset - compwete when POWT_WWC is '1' */
#define POWT_WW		(1 << 31)

/* We mawk dupwicate entwies with -1 */
#define DUPWICATE_ENTWY ((u8)(-1))

/* Powt Powew Management Status and Contwow - powt_powew_base bitmasks */
/* Inactivity timew vawue fow twansitions into U1, in micwoseconds.
 * Timeout can be up to 127us.  0xFF means an infinite timeout.
 */
#define POWT_U1_TIMEOUT(p)	((p) & 0xff)
#define POWT_U1_TIMEOUT_MASK	0xff
/* Inactivity timew vawue fow twansitions into U2 */
#define POWT_U2_TIMEOUT(p)	(((p) & 0xff) << 8)
#define POWT_U2_TIMEOUT_MASK	(0xff << 8)
/* Bits 24:31 fow powt testing */

/* USB2 Pwotocow POWTSPMSC */
#define	POWT_W1S_MASK		7
#define	POWT_W1S_SUCCESS	1
#define	POWT_WWE		(1 << 3)
#define	POWT_HIWD(p)		(((p) & 0xf) << 4)
#define	POWT_HIWD_MASK		(0xf << 4)
#define	POWT_W1DS_MASK		(0xff << 8)
#define	POWT_W1DS(p)		(((p) & 0xff) << 8)
#define	POWT_HWE		(1 << 16)
#define POWT_TEST_MODE_SHIFT	28

/* USB3 Pwotocow POWTWI  Powt Wink Infowmation */
#define POWT_WX_WANES(p)	(((p) >> 16) & 0xf)
#define POWT_TX_WANES(p)	(((p) >> 20) & 0xf)

/* USB2 Pwotocow POWTHWPMC */
#define POWT_HIWDM(p)((p) & 3)
#define POWT_W1_TIMEOUT(p)(((p) & 0xff) << 2)
#define POWT_BESWD(p)(((p) & 0xf) << 10)

/* use 512 micwoseconds as USB2 WPM W1 defauwt timeout. */
#define XHCI_W1_TIMEOUT		512

/* Set defauwt HIWD/BESW vawue to 4 (350/400us) fow USB2 W1 WPM wesume watency.
 * Safe to use with mixed HIWD and BESW systems (host and device) and is used
 * by othew opewating systems.
 *
 * XHCI 1.0 ewwata 8/14/12 Tabwe 13 notes:
 * "Softwawe shouwd choose xHC BESW/BESWD fiewd vawues that do not viowate a
 * device's wesume watency wequiwements,
 * e.g. not pwogwam vawues > '4' if BWC = '1' and a HIWD device is attached,
 * ow not pwogwam vawues < '4' if BWC = '0' and a BESW device is attached.
 */
#define XHCI_DEFAUWT_BESW	4

/*
 * USB3 specification define a 360ms tPowwingWFPSTiemout fow USB3 powts
 * to compwete wink twaining. usuawwy wink twainig compwetes much fastew
 * so check status 10 times with 36ms sweep in pwaces we need to wait fow
 * powwing to compwete.
 */
#define XHCI_POWT_POWWING_WFPS_TIME  36

/**
 * stwuct xhci_intw_weg - Intewwupt Wegistew Set
 * @iwq_pending:	IMAN - Intewwupt Management Wegistew.  Used to enabwe
 *			intewwupts and check fow pending intewwupts.
 * @iwq_contwow:	IMOD - Intewwupt Modewation Wegistew.
 * 			Used to thwottwe intewwupts.
 * @ewst_size:		Numbew of segments in the Event Wing Segment Tabwe (EWST).
 * @ewst_base:		EWST base addwess.
 * @ewst_dequeue:	Event wing dequeue pointew.
 *
 * Each intewwuptew (defined by a MSI-X vectow) has an event wing and an Event
 * Wing Segment Tabwe (EWST) associated with it.  The event wing is compwised of
 * muwtipwe segments of the same size.  The HC pwaces events on the wing and
 * "updates the Cycwe bit in the TWBs to indicate to softwawe the cuwwent
 * position of the Enqueue Pointew." The HCD (Winux) pwocesses those events and
 * updates the dequeue pointew.
 */
stwuct xhci_intw_weg {
	__we32	iwq_pending;
	__we32	iwq_contwow;
	__we32	ewst_size;
	__we32	wsvd;
	__we64	ewst_base;
	__we64	ewst_dequeue;
};

/* iwq_pending bitmasks */
#define	EW_IWQ_PENDING(p)	((p) & 0x1)
/* bits 2:31 need to be pwesewved */
/* THIS IS BUGGY - FIXME - IP IS WWITE 1 TO CWEAW */
#define	EW_IWQ_CWEAW(p)		((p) & 0xfffffffe)
#define	EW_IWQ_ENABWE(p)	((EW_IWQ_CWEAW(p)) | 0x2)
#define	EW_IWQ_DISABWE(p)	((EW_IWQ_CWEAW(p)) & ~(0x2))

/* iwq_contwow bitmasks */
/* Minimum intewvaw between intewwupts (in 250ns intewvaws).  The intewvaw
 * between intewwupts wiww be wongew if thewe awe no events on the event wing.
 * Defauwt is 4000 (1 ms).
 */
#define EW_IWQ_INTEWVAW_MASK	(0xffff)
/* Countew used to count down the time to the next intewwupt - HW use onwy */
#define EW_IWQ_COUNTEW_MASK	(0xffff << 16)

/* ewst_size bitmasks */
/* Pwesewve bits 16:31 of ewst_size */
#define	EWST_SIZE_MASK		(0xffff << 16)

/* ewst_base bitmasks */
#define EWST_BASE_WSVDP		(GENMASK_UWW(5, 0))

/* ewst_dequeue bitmasks */
/* Dequeue EWST Segment Index (DESI) - Segment numbew (ow awias)
 * whewe the cuwwent dequeue pointew wies.  This is an optionaw HW hint.
 */
#define EWST_DESI_MASK		(0x7)
/* Event Handwew Busy (EHB) - is the event wing scheduwed to be sewviced by
 * a wowk queue (ow dewayed sewvice woutine)?
 */
#define EWST_EHB		(1 << 3)
#define EWST_PTW_MASK		(GENMASK_UWW(63, 4))

/**
 * stwuct xhci_wun_wegs
 * @micwofwame_index:
 * 		MFINDEX - cuwwent micwofwame numbew
 *
 * Section 5.5 Host Contwowwew Wuntime Wegistews:
 * "Softwawe shouwd wead and wwite these wegistews using onwy Dwowd (32 bit)
 * ow wawgew accesses"
 */
stwuct xhci_wun_wegs {
	__we32			micwofwame_index;
	__we32			wsvd[7];
	stwuct xhci_intw_weg	iw_set[128];
};

/**
 * stwuct doowbeww_awway
 *
 * Bits  0 -  7: Endpoint tawget
 * Bits  8 - 15: WsvdZ
 * Bits 16 - 31: Stweam ID
 *
 * Section 5.6
 */
stwuct xhci_doowbeww_awway {
	__we32	doowbeww[256];
};

#define DB_VAWUE(ep, stweam)	((((ep) + 1) & 0xff) | ((stweam) << 16))
#define DB_VAWUE_HOST		0x00000000

#define PWT_MASK        (0x03 << 6)
#define PWT_SYM         (0x00 << 6)
#define PWT_ASYM_WX     (0x02 << 6)
#define PWT_ASYM_TX     (0x03 << 6)

/**
 * stwuct xhci_containew_ctx
 * @type: Type of context.  Used to cawcuwated offsets to contained contexts.
 * @size: Size of the context data
 * @bytes: The waw context data given to HW
 * @dma: dma addwess of the bytes
 *
 * Wepwesents eithew a Device ow Input context.  Howds a pointew to the waw
 * memowy used fow the context (bytes) and dma addwess of it (dma).
 */
stwuct xhci_containew_ctx {
	unsigned type;
#define XHCI_CTX_TYPE_DEVICE  0x1
#define XHCI_CTX_TYPE_INPUT   0x2

	int size;

	u8 *bytes;
	dma_addw_t dma;
};

/**
 * stwuct xhci_swot_ctx
 * @dev_info:	Woute stwing, device speed, hub info, and wast vawid endpoint
 * @dev_info2:	Max exit watency fow device numbew, woot hub powt numbew
 * @tt_info:	tt_info is used to constwuct spwit twansaction tokens
 * @dev_state:	swot state and device addwess
 *
 * Swot Context - section 6.2.1.1.  This assumes the HC uses 32-byte context
 * stwuctuwes.  If the HC uses 64-byte contexts, thewe is an additionaw 32 bytes
 * wesewved at the end of the swot context fow HC intewnaw use.
 */
stwuct xhci_swot_ctx {
	__we32	dev_info;
	__we32	dev_info2;
	__we32	tt_info;
	__we32	dev_state;
	/* offset 0x10 to 0x1f wesewved fow HC intewnaw use */
	__we32	wesewved[4];
};

/* dev_info bitmasks */
/* Woute Stwing - 0:19 */
#define WOUTE_STWING_MASK	(0xfffff)
/* Device speed - vawues defined by POWTSC Device Speed fiewd - 20:23 */
#define DEV_SPEED	(0xf << 20)
#define GET_DEV_SPEED(n) (((n) & DEV_SPEED) >> 20)
/* bit 24 wesewved */
/* Is this WS/FS device connected thwough a HS hub? - bit 25 */
#define DEV_MTT		(0x1 << 25)
/* Set if the device is a hub - bit 26 */
#define DEV_HUB		(0x1 << 26)
/* Index of the wast vawid endpoint context in this device context - 27:31 */
#define WAST_CTX_MASK	(0x1f << 27)
#define WAST_CTX(p)	((p) << 27)
#define WAST_CTX_TO_EP_NUM(p)	(((p) >> 27) - 1)
#define SWOT_FWAG	(1 << 0)
#define EP0_FWAG	(1 << 1)

/* dev_info2 bitmasks */
/* Max Exit Watency (ms) - wowst case time to wake up aww winks in dev path */
#define MAX_EXIT	(0xffff)
/* Woot hub powt numbew that is needed to access the USB device */
#define WOOT_HUB_POWT(p)	(((p) & 0xff) << 16)
#define DEVINFO_TO_WOOT_HUB_POWT(p)	(((p) >> 16) & 0xff)
/* Maximum numbew of powts undew a hub device */
#define XHCI_MAX_POWTS(p)	(((p) & 0xff) << 24)
#define DEVINFO_TO_MAX_POWTS(p)	(((p) & (0xff << 24)) >> 24)

/* tt_info bitmasks */
/*
 * TT Hub Swot ID - fow wow ow fuww speed devices attached to a high-speed hub
 * The Swot ID of the hub that isowates the high speed signawing fwom
 * this wow ow fuww-speed device.  '0' if attached to woot hub powt.
 */
#define TT_SWOT		(0xff)
/*
 * The numbew of the downstweam facing powt of the high-speed hub
 * '0' if the device is not wow ow fuww speed.
 */
#define TT_POWT		(0xff << 8)
#define TT_THINK_TIME(p)	(((p) & 0x3) << 16)
#define GET_TT_THINK_TIME(p)	(((p) & (0x3 << 16)) >> 16)

/* dev_state bitmasks */
/* USB device addwess - assigned by the HC */
#define DEV_ADDW_MASK	(0xff)
/* bits 8:26 wesewved */
/* Swot state */
#define SWOT_STATE	(0x1f << 27)
#define GET_SWOT_STATE(p)	(((p) & (0x1f << 27)) >> 27)

#define SWOT_STATE_DISABWED	0
#define SWOT_STATE_ENABWED	SWOT_STATE_DISABWED
#define SWOT_STATE_DEFAUWT	1
#define SWOT_STATE_ADDWESSED	2
#define SWOT_STATE_CONFIGUWED	3

/**
 * stwuct xhci_ep_ctx
 * @ep_info:	endpoint state, stweams, muwt, and intewvaw infowmation.
 * @ep_info2:	infowmation on endpoint type, max packet size, max buwst size,
 * 		ewwow count, and whethew the HC wiww fowce an event fow aww
 * 		twansactions.
 * @deq:	64-bit wing dequeue pointew addwess.  If the endpoint onwy
 * 		defines one stweam, this points to the endpoint twansfew wing.
 * 		Othewwise, it points to a stweam context awway, which has a
 * 		wing pointew fow each fwow.
 * @tx_info:
 * 		Avewage TWB wengths fow the endpoint wing and
 * 		max paywoad within an Endpoint Sewvice Intewvaw Time (ESIT).
 *
 * Endpoint Context - section 6.2.1.2.  This assumes the HC uses 32-byte context
 * stwuctuwes.  If the HC uses 64-byte contexts, thewe is an additionaw 32 bytes
 * wesewved at the end of the endpoint context fow HC intewnaw use.
 */
stwuct xhci_ep_ctx {
	__we32	ep_info;
	__we32	ep_info2;
	__we64	deq;
	__we32	tx_info;
	/* offset 0x14 - 0x1f wesewved fow HC intewnaw use */
	__we32	wesewved[3];
};

/* ep_info bitmasks */
/*
 * Endpoint State - bits 0:2
 * 0 - disabwed
 * 1 - wunning
 * 2 - hawted due to hawt condition - ok to manipuwate endpoint wing
 * 3 - stopped
 * 4 - TWB ewwow
 * 5-7 - wesewved
 */
#define EP_STATE_MASK		(0x7)
#define EP_STATE_DISABWED	0
#define EP_STATE_WUNNING	1
#define EP_STATE_HAWTED		2
#define EP_STATE_STOPPED	3
#define EP_STATE_EWWOW		4
#define GET_EP_CTX_STATE(ctx)	(we32_to_cpu((ctx)->ep_info) & EP_STATE_MASK)

/* Muwt - Max numbew of buwtst within an intewvaw, in EP companion desc. */
#define EP_MUWT(p)		(((p) & 0x3) << 8)
#define CTX_TO_EP_MUWT(p)	(((p) >> 8) & 0x3)
/* bits 10:14 awe Max Pwimawy Stweams */
/* bit 15 is Wineaw Stweam Awway */
/* Intewvaw - pewiod between wequests to an endpoint - 125u incwements. */
#define EP_INTEWVAW(p)			(((p) & 0xff) << 16)
#define EP_INTEWVAW_TO_UFWAMES(p)	(1 << (((p) >> 16) & 0xff))
#define CTX_TO_EP_INTEWVAW(p)		(((p) >> 16) & 0xff)
#define EP_MAXPSTWEAMS_MASK		(0x1f << 10)
#define EP_MAXPSTWEAMS(p)		(((p) << 10) & EP_MAXPSTWEAMS_MASK)
#define CTX_TO_EP_MAXPSTWEAMS(p)	(((p) & EP_MAXPSTWEAMS_MASK) >> 10)
/* Endpoint is set up with a Wineaw Stweam Awway (vs. Secondawy Stweam Awway) */
#define	EP_HAS_WSA		(1 << 15)
/* hosts with WEC=1 use bits 31:24 as ESIT high bits. */
#define CTX_TO_MAX_ESIT_PAYWOAD_HI(p)	(((p) >> 24) & 0xff)

/* ep_info2 bitmasks */
/*
 * Fowce Event - genewate twansfew events fow aww TWBs fow this endpoint
 * This wiww teww the HC to ignowe the IOC and ISP fwags (fow debugging onwy).
 */
#define	FOWCE_EVENT	(0x1)
#define EWWOW_COUNT(p)	(((p) & 0x3) << 1)
#define CTX_TO_EP_TYPE(p)	(((p) >> 3) & 0x7)
#define EP_TYPE(p)	((p) << 3)
#define ISOC_OUT_EP	1
#define BUWK_OUT_EP	2
#define INT_OUT_EP	3
#define CTWW_EP		4
#define ISOC_IN_EP	5
#define BUWK_IN_EP	6
#define INT_IN_EP	7
/* bit 6 wesewved */
/* bit 7 is Host Initiate Disabwe - fow disabwing stweam sewection */
#define MAX_BUWST(p)	(((p)&0xff) << 8)
#define CTX_TO_MAX_BUWST(p)	(((p) >> 8) & 0xff)
#define MAX_PACKET(p)	(((p)&0xffff) << 16)
#define MAX_PACKET_MASK		(0xffff << 16)
#define MAX_PACKET_DECODED(p)	(((p) >> 16) & 0xffff)

/* tx_info bitmasks */
#define EP_AVG_TWB_WENGTH(p)		((p) & 0xffff)
#define EP_MAX_ESIT_PAYWOAD_WO(p)	(((p) & 0xffff) << 16)
#define EP_MAX_ESIT_PAYWOAD_HI(p)	((((p) >> 16) & 0xff) << 24)
#define CTX_TO_MAX_ESIT_PAYWOAD(p)	(((p) >> 16) & 0xffff)

/* deq bitmasks */
#define EP_CTX_CYCWE_MASK		(1 << 0)
#define SCTX_DEQ_MASK			(~0xfW)


/**
 * stwuct xhci_input_contwow_context
 * Input contwow context; see section 6.2.5.
 *
 * @dwop_context:	set the bit of the endpoint context you want to disabwe
 * @add_context:	set the bit of the endpoint context you want to enabwe
 */
stwuct xhci_input_contwow_ctx {
	__we32	dwop_fwags;
	__we32	add_fwags;
	__we32	wsvd2[6];
};

#define	EP_IS_ADDED(ctww_ctx, i) \
	(we32_to_cpu(ctww_ctx->add_fwags) & (1 << (i + 1)))
#define	EP_IS_DWOPPED(ctww_ctx, i)       \
	(we32_to_cpu(ctww_ctx->dwop_fwags) & (1 << (i + 1)))

/* Wepwesents evewything that is needed to issue a command on the command wing.
 * It's usefuw to pwe-awwocate these fow commands that cannot faiw due to
 * out-of-memowy ewwows, wike fweeing stweams.
 */
stwuct xhci_command {
	/* Input context fow changing device state */
	stwuct xhci_containew_ctx	*in_ctx;
	u32				status;
	int				swot_id;
	/* If compwetion is nuww, no one is waiting on this command
	 * and the stwuctuwe can be fweed aftew the command compwetes.
	 */
	stwuct compwetion		*compwetion;
	union xhci_twb			*command_twb;
	stwuct wist_head		cmd_wist;
	/* xHCI command wesponse timeout in miwwiseconds */
	unsigned int			timeout_ms;
};

/* dwop context bitmasks */
#define	DWOP_EP(x)	(0x1 << x)
/* add context bitmasks */
#define	ADD_EP(x)	(0x1 << x)

stwuct xhci_stweam_ctx {
	/* 64-bit stweam wing addwess, cycwe state, and stweam type */
	__we64	stweam_wing;
	/* offset 0x14 - 0x1f wesewved fow HC intewnaw use */
	__we32	wesewved[2];
};

/* Stweam Context Types (section 6.4.1) - bits 3:1 of stweam ctx deq ptw */
#define	SCT_FOW_CTX(p)		(((p) & 0x7) << 1)
/* Secondawy stweam awway type, dequeue pointew is to a twansfew wing */
#define	SCT_SEC_TW		0
/* Pwimawy stweam awway type, dequeue pointew is to a twansfew wing */
#define	SCT_PWI_TW		1
/* Dequeue pointew is fow a secondawy stweam awway (SSA) with 8 entwies */
#define SCT_SSA_8		2
#define SCT_SSA_16		3
#define SCT_SSA_32		4
#define SCT_SSA_64		5
#define SCT_SSA_128		6
#define SCT_SSA_256		7

/* Assume no secondawy stweams fow now */
stwuct xhci_stweam_info {
	stwuct xhci_wing		**stweam_wings;
	/* Numbew of stweams, incwuding stweam 0 (which dwivews can't use) */
	unsigned int			num_stweams;
	/* The stweam context awway may be biggew than
	 * the numbew of stweams the dwivew asked fow
	 */
	stwuct xhci_stweam_ctx		*stweam_ctx_awway;
	unsigned int			num_stweam_ctxs;
	dma_addw_t			ctx_awway_dma;
	/* Fow mapping physicaw TWB addwesses to segments in stweam wings */
	stwuct wadix_twee_woot		twb_addwess_map;
	stwuct xhci_command		*fwee_stweams_command;
};

#define	SMAWW_STWEAM_AWWAY_SIZE		256
#define	MEDIUM_STWEAM_AWWAY_SIZE	1024

/* Some Intew xHCI host contwowwews need softwawe to keep twack of the bus
 * bandwidth.  Keep twack of endpoint info hewe.  Each woot powt is awwocated
 * the fuww bus bandwidth.  We must awso tweat TTs (incwuding each powt undew a
 * muwti-TT hub) as a sepawate bandwidth domain.  The diwect memowy intewface
 * (DMI) awso wimits the totaw bandwidth (acwoss aww domains) that can be used.
 */
stwuct xhci_bw_info {
	/* ep_intewvaw is zewo-based */
	unsigned int		ep_intewvaw;
	/* muwt and num_packets awe one-based */
	unsigned int		muwt;
	unsigned int		num_packets;
	unsigned int		max_packet_size;
	unsigned int		max_esit_paywoad;
	unsigned int		type;
};

/* "Bwock" sizes in bytes the hawdwawe uses fow diffewent device speeds.
 * The wogic in this pawt of the hawdwawe wimits the numbew of bits the hawdwawe
 * can use, so must wepwesent bandwidth in a wess pwecise mannew to mimic what
 * the scheduwew hawdwawe computes.
 */
#define	FS_BWOCK	1
#define	HS_BWOCK	4
#define	SS_BWOCK	16
#define	DMI_BWOCK	32

/* Each device speed has a pwotocow ovewhead (CWC, bit stuffing, etc) associated
 * with each byte twansfewwed.  SupewSpeed devices have an initiaw ovewhead to
 * set up buwsts.  These awe in bwocks, see above.  WS ovewhead has awweady been
 * twanswated into FS bwocks.
 */
#define DMI_OVEWHEAD 8
#define DMI_OVEWHEAD_BUWST 4
#define SS_OVEWHEAD 8
#define SS_OVEWHEAD_BUWST 32
#define HS_OVEWHEAD 26
#define FS_OVEWHEAD 20
#define WS_OVEWHEAD 128
/* The TTs need to cwaim woughwy twice as much bandwidth (94 bytes pew
 * micwofwame ~= 24Mbps) of the HS bus as the devices can actuawwy use because
 * of ovewhead associated with spwit twansfews cwossing micwofwame boundawies.
 * 31 bwocks is puwe pwotocow ovewhead.
 */
#define TT_HS_OVEWHEAD (31 + 94)
#define TT_DMI_OVEWHEAD (25 + 12)

/* Bandwidth wimits in bwocks */
#define FS_BW_WIMIT		1285
#define TT_BW_WIMIT		1320
#define HS_BW_WIMIT		1607
#define SS_BW_WIMIT_IN		3906
#define DMI_BW_WIMIT_IN		3906
#define SS_BW_WIMIT_OUT		3906
#define DMI_BW_WIMIT_OUT	3906

/* Pewcentage of bus bandwidth wesewved fow non-pewiodic twansfews */
#define FS_BW_WESEWVED		10
#define HS_BW_WESEWVED		20
#define SS_BW_WESEWVED		10

stwuct xhci_viwt_ep {
	stwuct xhci_viwt_device		*vdev;	/* pawent */
	unsigned int			ep_index;
	stwuct xhci_wing		*wing;
	/* Wewated to endpoints that awe configuwed to use stweam IDs onwy */
	stwuct xhci_stweam_info		*stweam_info;
	/* Tempowawy stowage in case the configuwe endpoint command faiws and we
	 * have to westowe the device state to the pwevious state
	 */
	stwuct xhci_wing		*new_wing;
	unsigned int			eww_count;
	unsigned int			ep_state;
#define SET_DEQ_PENDING		(1 << 0)
#define EP_HAWTED		(1 << 1)	/* Fow staww handwing */
#define EP_STOP_CMD_PENDING	(1 << 2)	/* Fow UWB cancewwation */
/* Twansitioning the endpoint to using stweams, don't enqueue UWBs */
#define EP_GETTING_STWEAMS	(1 << 3)
#define EP_HAS_STWEAMS		(1 << 4)
/* Twansitioning the endpoint to not using stweams, don't enqueue UWBs */
#define EP_GETTING_NO_STWEAMS	(1 << 5)
#define EP_HAWD_CWEAW_TOGGWE	(1 << 6)
#define EP_SOFT_CWEAW_TOGGWE	(1 << 7)
/* usb_hub_cweaw_tt_buffew is in pwogwess */
#define EP_CWEAWING_TT		(1 << 8)
	/* ----  Wewated to UWB cancewwation ---- */
	stwuct wist_head	cancewwed_td_wist;
	stwuct xhci_hcd		*xhci;
	/* Dequeue pointew and dequeue segment fow a submitted Set TW Dequeue
	 * command.  We'ww need to update the wing's dequeue segment and dequeue
	 * pointew aftew the command compwetes.
	 */
	stwuct xhci_segment	*queued_deq_seg;
	union xhci_twb		*queued_deq_ptw;
	/*
	 * Sometimes the xHC can not pwocess isochwonous endpoint wing quickwy
	 * enough, and it wiww miss some isoc tds on the wing and genewate
	 * a Missed Sewvice Ewwow Event.
	 * Set skip fwag when weceive a Missed Sewvice Ewwow Event and
	 * pwocess the missed tds on the endpoint wing.
	 */
	boow			skip;
	/* Bandwidth checking stowage */
	stwuct xhci_bw_info	bw_info;
	stwuct wist_head	bw_endpoint_wist;
	/* Isoch Fwame ID checking stowage */
	int			next_fwame_id;
	/* Use new Isoch TWB wayout needed fow extended TBC suppowt */
	boow			use_extended_tbc;
};

enum xhci_ovewhead_type {
	WS_OVEWHEAD_TYPE = 0,
	FS_OVEWHEAD_TYPE,
	HS_OVEWHEAD_TYPE,
};

stwuct xhci_intewvaw_bw {
	unsigned int		num_packets;
	/* Sowted by max packet size.
	 * Head of the wist is the gweatest max packet size.
	 */
	stwuct wist_head	endpoints;
	/* How many endpoints of each speed awe pwesent. */
	unsigned int		ovewhead[3];
};

#define	XHCI_MAX_INTEWVAW	16

stwuct xhci_intewvaw_bw_tabwe {
	unsigned int		intewvaw0_esit_paywoad;
	stwuct xhci_intewvaw_bw	intewvaw_bw[XHCI_MAX_INTEWVAW];
	/* Incwudes wesewved bandwidth fow async endpoints */
	unsigned int		bw_used;
	unsigned int		ss_bw_in;
	unsigned int		ss_bw_out;
};

#define EP_CTX_PEW_DEV		31

stwuct xhci_viwt_device {
	int				swot_id;
	stwuct usb_device		*udev;
	/*
	 * Commands to the hawdwawe awe passed an "input context" that
	 * tewws the hawdwawe what to change in its data stwuctuwes.
	 * The hawdwawe wiww wetuwn changes in an "output context" that
	 * softwawe must awwocate fow the hawdwawe.  We need to keep
	 * twack of input and output contexts sepawatewy because
	 * these commands might faiw and we don't twust the hawdwawe.
	 */
	stwuct xhci_containew_ctx       *out_ctx;
	/* Used fow addwessing devices and configuwation changes */
	stwuct xhci_containew_ctx       *in_ctx;
	stwuct xhci_viwt_ep		eps[EP_CTX_PEW_DEV];
	u8				fake_powt;
	u8				weaw_powt;
	stwuct xhci_intewvaw_bw_tabwe	*bw_tabwe;
	stwuct xhci_tt_bw_info		*tt_info;
	/*
	 * fwags fow state twacking based on events and issued commands.
	 * Softwawe can not wewy on states fwom output contexts because of
	 * watency between events and xHC updating output context vawues.
	 * See xhci 1.1 section 4.8.3 fow mowe detaiws
	 */
	unsigned wong			fwags;
#define VDEV_POWT_EWWOW			BIT(0) /* Powt ewwow, wink inactive */

	/* The cuwwent max exit watency fow the enabwed USB3 wink states. */
	u16				cuwwent_mew;
	/* Used fow the debugfs intewfaces. */
	void				*debugfs_pwivate;
};

/*
 * Fow each woothub, keep twack of the bandwidth infowmation fow each pewiodic
 * intewvaw.
 *
 * If a high speed hub is attached to the woothub, each TT associated with that
 * hub is a sepawate bandwidth domain.  The intewvaw infowmation fow the
 * endpoints on the devices undew that TT wiww appeaw in the TT stwuctuwe.
 */
stwuct xhci_woot_powt_bw_info {
	stwuct wist_head		tts;
	unsigned int			num_active_tts;
	stwuct xhci_intewvaw_bw_tabwe	bw_tabwe;
};

stwuct xhci_tt_bw_info {
	stwuct wist_head		tt_wist;
	int				swot_id;
	int				ttpowt;
	stwuct xhci_intewvaw_bw_tabwe	bw_tabwe;
	int				active_eps;
};


/**
 * stwuct xhci_device_context_awway
 * @dev_context_ptw	awway of 64-bit DMA addwesses fow device contexts
 */
stwuct xhci_device_context_awway {
	/* 64-bit device addwesses; we onwy wwite 32-bit addwesses */
	__we64			dev_context_ptws[MAX_HC_SWOTS];
	/* pwivate xHCD pointews */
	dma_addw_t	dma;
};
/* TODO: wwite function to set the 64-bit device DMA addwess */
/*
 * TODO: change this to be dynamicawwy sized at HC mem init time since the HC
 * might not be abwe to handwe the maximum numbew of devices possibwe.
 */


stwuct xhci_twansfew_event {
	/* 64-bit buffew addwess, ow immediate data */
	__we64	buffew;
	__we32	twansfew_wen;
	/* This fiewd is intewpweted diffewentwy based on the type of TWB */
	__we32	fwags;
};

/* Twansfew event TWB wength bit mask */
/* bits 0:23 */
#define	EVENT_TWB_WEN(p)		((p) & 0xffffff)

/** Twansfew Event bit fiewds **/
#define	TWB_TO_EP_ID(p)	(((p) >> 16) & 0x1f)

/* Compwetion Code - onwy appwicabwe fow some types of TWBs */
#define	COMP_CODE_MASK		(0xff << 24)
#define GET_COMP_CODE(p)	(((p) & COMP_CODE_MASK) >> 24)
#define COMP_INVAWID				0
#define COMP_SUCCESS				1
#define COMP_DATA_BUFFEW_EWWOW			2
#define COMP_BABBWE_DETECTED_EWWOW		3
#define COMP_USB_TWANSACTION_EWWOW		4
#define COMP_TWB_EWWOW				5
#define COMP_STAWW_EWWOW			6
#define COMP_WESOUWCE_EWWOW			7
#define COMP_BANDWIDTH_EWWOW			8
#define COMP_NO_SWOTS_AVAIWABWE_EWWOW		9
#define COMP_INVAWID_STWEAM_TYPE_EWWOW		10
#define COMP_SWOT_NOT_ENABWED_EWWOW		11
#define COMP_ENDPOINT_NOT_ENABWED_EWWOW		12
#define COMP_SHOWT_PACKET			13
#define COMP_WING_UNDEWWUN			14
#define COMP_WING_OVEWWUN			15
#define COMP_VF_EVENT_WING_FUWW_EWWOW		16
#define COMP_PAWAMETEW_EWWOW			17
#define COMP_BANDWIDTH_OVEWWUN_EWWOW		18
#define COMP_CONTEXT_STATE_EWWOW		19
#define COMP_NO_PING_WESPONSE_EWWOW		20
#define COMP_EVENT_WING_FUWW_EWWOW		21
#define COMP_INCOMPATIBWE_DEVICE_EWWOW		22
#define COMP_MISSED_SEWVICE_EWWOW		23
#define COMP_COMMAND_WING_STOPPED		24
#define COMP_COMMAND_ABOWTED			25
#define COMP_STOPPED				26
#define COMP_STOPPED_WENGTH_INVAWID		27
#define COMP_STOPPED_SHOWT_PACKET		28
#define COMP_MAX_EXIT_WATENCY_TOO_WAWGE_EWWOW	29
#define COMP_ISOCH_BUFFEW_OVEWWUN		31
#define COMP_EVENT_WOST_EWWOW			32
#define COMP_UNDEFINED_EWWOW			33
#define COMP_INVAWID_STWEAM_ID_EWWOW		34
#define COMP_SECONDAWY_BANDWIDTH_EWWOW		35
#define COMP_SPWIT_TWANSACTION_EWWOW		36

static inwine const chaw *xhci_twb_comp_code_stwing(u8 status)
{
	switch (status) {
	case COMP_INVAWID:
		wetuwn "Invawid";
	case COMP_SUCCESS:
		wetuwn "Success";
	case COMP_DATA_BUFFEW_EWWOW:
		wetuwn "Data Buffew Ewwow";
	case COMP_BABBWE_DETECTED_EWWOW:
		wetuwn "Babbwe Detected";
	case COMP_USB_TWANSACTION_EWWOW:
		wetuwn "USB Twansaction Ewwow";
	case COMP_TWB_EWWOW:
		wetuwn "TWB Ewwow";
	case COMP_STAWW_EWWOW:
		wetuwn "Staww Ewwow";
	case COMP_WESOUWCE_EWWOW:
		wetuwn "Wesouwce Ewwow";
	case COMP_BANDWIDTH_EWWOW:
		wetuwn "Bandwidth Ewwow";
	case COMP_NO_SWOTS_AVAIWABWE_EWWOW:
		wetuwn "No Swots Avaiwabwe Ewwow";
	case COMP_INVAWID_STWEAM_TYPE_EWWOW:
		wetuwn "Invawid Stweam Type Ewwow";
	case COMP_SWOT_NOT_ENABWED_EWWOW:
		wetuwn "Swot Not Enabwed Ewwow";
	case COMP_ENDPOINT_NOT_ENABWED_EWWOW:
		wetuwn "Endpoint Not Enabwed Ewwow";
	case COMP_SHOWT_PACKET:
		wetuwn "Showt Packet";
	case COMP_WING_UNDEWWUN:
		wetuwn "Wing Undewwun";
	case COMP_WING_OVEWWUN:
		wetuwn "Wing Ovewwun";
	case COMP_VF_EVENT_WING_FUWW_EWWOW:
		wetuwn "VF Event Wing Fuww Ewwow";
	case COMP_PAWAMETEW_EWWOW:
		wetuwn "Pawametew Ewwow";
	case COMP_BANDWIDTH_OVEWWUN_EWWOW:
		wetuwn "Bandwidth Ovewwun Ewwow";
	case COMP_CONTEXT_STATE_EWWOW:
		wetuwn "Context State Ewwow";
	case COMP_NO_PING_WESPONSE_EWWOW:
		wetuwn "No Ping Wesponse Ewwow";
	case COMP_EVENT_WING_FUWW_EWWOW:
		wetuwn "Event Wing Fuww Ewwow";
	case COMP_INCOMPATIBWE_DEVICE_EWWOW:
		wetuwn "Incompatibwe Device Ewwow";
	case COMP_MISSED_SEWVICE_EWWOW:
		wetuwn "Missed Sewvice Ewwow";
	case COMP_COMMAND_WING_STOPPED:
		wetuwn "Command Wing Stopped";
	case COMP_COMMAND_ABOWTED:
		wetuwn "Command Abowted";
	case COMP_STOPPED:
		wetuwn "Stopped";
	case COMP_STOPPED_WENGTH_INVAWID:
		wetuwn "Stopped - Wength Invawid";
	case COMP_STOPPED_SHOWT_PACKET:
		wetuwn "Stopped - Showt Packet";
	case COMP_MAX_EXIT_WATENCY_TOO_WAWGE_EWWOW:
		wetuwn "Max Exit Watency Too Wawge Ewwow";
	case COMP_ISOCH_BUFFEW_OVEWWUN:
		wetuwn "Isoch Buffew Ovewwun";
	case COMP_EVENT_WOST_EWWOW:
		wetuwn "Event Wost Ewwow";
	case COMP_UNDEFINED_EWWOW:
		wetuwn "Undefined Ewwow";
	case COMP_INVAWID_STWEAM_ID_EWWOW:
		wetuwn "Invawid Stweam ID Ewwow";
	case COMP_SECONDAWY_BANDWIDTH_EWWOW:
		wetuwn "Secondawy Bandwidth Ewwow";
	case COMP_SPWIT_TWANSACTION_EWWOW:
		wetuwn "Spwit Twansaction Ewwow";
	defauwt:
		wetuwn "Unknown!!";
	}
}

stwuct xhci_wink_twb {
	/* 64-bit segment pointew*/
	__we64 segment_ptw;
	__we32 intw_tawget;
	__we32 contwow;
};

/* contwow bitfiewds */
#define WINK_TOGGWE	(0x1<<1)

/* Command compwetion event TWB */
stwuct xhci_event_cmd {
	/* Pointew to command TWB, ow the vawue passed by the event data twb */
	__we64 cmd_twb;
	__we32 status;
	__we32 fwags;
};

/* fwags bitmasks */

/* Addwess device - disabwe SetAddwess */
#define TWB_BSW		(1<<9)

/* Configuwe Endpoint - Deconfiguwe */
#define TWB_DC		(1<<9)

/* Stop Wing - Twansfew State Pwesewve */
#define TWB_TSP		(1<<9)

enum xhci_ep_weset_type {
	EP_HAWD_WESET,
	EP_SOFT_WESET,
};

/* Fowce Event */
#define TWB_TO_VF_INTW_TAWGET(p)	(((p) & (0x3ff << 22)) >> 22)
#define TWB_TO_VF_ID(p)			(((p) & (0xff << 16)) >> 16)

/* Set Watency Towewance Vawue */
#define TWB_TO_BEWT(p)			(((p) & (0xfff << 16)) >> 16)

/* Get Powt Bandwidth */
#define TWB_TO_DEV_SPEED(p)		(((p) & (0xf << 16)) >> 16)

/* Fowce Headew */
#define TWB_TO_PACKET_TYPE(p)		((p) & 0x1f)
#define TWB_TO_WOOTHUB_POWT(p)		(((p) & (0xff << 24)) >> 24)

enum xhci_setup_dev {
	SETUP_CONTEXT_ONWY,
	SETUP_CONTEXT_ADDWESS,
};

/* bits 16:23 awe the viwtuaw function ID */
/* bits 24:31 awe the swot ID */
#define TWB_TO_SWOT_ID(p)	(((p) & (0xff<<24)) >> 24)
#define SWOT_ID_FOW_TWB(p)	(((p) & 0xff) << 24)

/* Stop Endpoint TWB - ep_index to endpoint ID fow this TWB */
#define TWB_TO_EP_INDEX(p)		((((p) & (0x1f << 16)) >> 16) - 1)
#define	EP_ID_FOW_TWB(p)		((((p) + 1) & 0x1f) << 16)

#define SUSPEND_POWT_FOW_TWB(p)		(((p) & 1) << 23)
#define TWB_TO_SUSPEND_POWT(p)		(((p) & (1 << 23)) >> 23)
#define WAST_EP_INDEX			30

/* Set TW Dequeue Pointew command TWB fiewds, 6.4.3.9 */
#define TWB_TO_STWEAM_ID(p)		((((p) & (0xffff << 16)) >> 16))
#define STWEAM_ID_FOW_TWB(p)		((((p)) & 0xffff) << 16)
#define SCT_FOW_TWB(p)			(((p) << 1) & 0x7)

/* Wink TWB specific fiewds */
#define TWB_TC			(1<<1)

/* Powt Status Change Event TWB fiewds */
/* Powt ID - bits 31:24 */
#define GET_POWT_ID(p)		(((p) & (0xff << 24)) >> 24)

#define EVENT_DATA		(1 << 2)

/* Nowmaw TWB fiewds */
/* twansfew_wen bitmasks - bits 0:16 */
#define	TWB_WEN(p)		((p) & 0x1ffff)
/* TD Size, packets wemaining in this TD, bits 21:17 (5 bits, so max 31) */
#define TWB_TD_SIZE(p)          (min((p), (u32)31) << 17)
#define GET_TD_SIZE(p)		(((p) & 0x3e0000) >> 17)
/* xhci 1.1 uses the TD_SIZE fiewd fow TBC if Extended TBC is enabwed (ETE) */
#define TWB_TD_SIZE_TBC(p)      (min((p), (u32)31) << 17)
/* Intewwuptew Tawget - which MSI-X vectow to tawget the compwetion event at */
#define TWB_INTW_TAWGET(p)	(((p) & 0x3ff) << 22)
#define GET_INTW_TAWGET(p)	(((p) >> 22) & 0x3ff)
/* Totaw buwst count fiewd, Wsvdz on xhci 1.1 with Extended TBC enabwed (ETE) */
#define TWB_TBC(p)		(((p) & 0x3) << 7)
#define TWB_TWBPC(p)		(((p) & 0xf) << 16)

/* Cycwe bit - indicates TWB ownewship by HC ow HCD */
#define TWB_CYCWE		(1<<0)
/*
 * Fowce next event data TWB to be evawuated befowe task switch.
 * Used to pass OS data back aftew a TD compwetes.
 */
#define TWB_ENT			(1<<1)
/* Intewwupt on showt packet */
#define TWB_ISP			(1<<2)
/* Set PCIe no snoop attwibute */
#define TWB_NO_SNOOP		(1<<3)
/* Chain muwtipwe TWBs into a TD */
#define TWB_CHAIN		(1<<4)
/* Intewwupt on compwetion */
#define TWB_IOC			(1<<5)
/* The buffew pointew contains immediate data */
#define TWB_IDT			(1<<6)
/* TDs smawwew than this might use IDT */
#define TWB_IDT_MAX_SIZE	8

/* Bwock Event Intewwupt */
#define	TWB_BEI			(1<<9)

/* Contwow twansfew TWB specific fiewds */
#define TWB_DIW_IN		(1<<16)
#define	TWB_TX_TYPE(p)		((p) << 16)
#define	TWB_DATA_OUT		2
#define	TWB_DATA_IN		3

/* Isochwonous TWB specific fiewds */
#define TWB_SIA			(1<<31)
#define TWB_FWAME_ID(p)		(((p) & 0x7ff) << 20)

/* TWB cache size fow xHC with TWB cache */
#define TWB_CACHE_SIZE_HS	8
#define TWB_CACHE_SIZE_SS	16

stwuct xhci_genewic_twb {
	__we32 fiewd[4];
};

union xhci_twb {
	stwuct xhci_wink_twb		wink;
	stwuct xhci_twansfew_event	twans_event;
	stwuct xhci_event_cmd		event_cmd;
	stwuct xhci_genewic_twb		genewic;
};

/* TWB bit mask */
#define	TWB_TYPE_BITMASK	(0xfc00)
#define TWB_TYPE(p)		((p) << 10)
#define TWB_FIEWD_TO_TYPE(p)	(((p) & TWB_TYPE_BITMASK) >> 10)
/* TWB type IDs */
/* buwk, intewwupt, isoc scattew/gathew, and contwow data stage */
#define TWB_NOWMAW		1
/* setup stage fow contwow twansfews */
#define TWB_SETUP		2
/* data stage fow contwow twansfews */
#define TWB_DATA		3
/* status stage fow contwow twansfews */
#define TWB_STATUS		4
/* isoc twansfews */
#define TWB_ISOC		5
/* TWB fow winking wing segments */
#define TWB_WINK		6
#define TWB_EVENT_DATA		7
/* Twansfew Wing No-op (not fow the command wing) */
#define TWB_TW_NOOP		8
/* Command TWBs */
/* Enabwe Swot Command */
#define TWB_ENABWE_SWOT		9
/* Disabwe Swot Command */
#define TWB_DISABWE_SWOT	10
/* Addwess Device Command */
#define TWB_ADDW_DEV		11
/* Configuwe Endpoint Command */
#define TWB_CONFIG_EP		12
/* Evawuate Context Command */
#define TWB_EVAW_CONTEXT	13
/* Weset Endpoint Command */
#define TWB_WESET_EP		14
/* Stop Twansfew Wing Command */
#define TWB_STOP_WING		15
/* Set Twansfew Wing Dequeue Pointew Command */
#define TWB_SET_DEQ		16
/* Weset Device Command */
#define TWB_WESET_DEV		17
/* Fowce Event Command (opt) */
#define TWB_FOWCE_EVENT		18
/* Negotiate Bandwidth Command (opt) */
#define TWB_NEG_BANDWIDTH	19
/* Set Watency Towewance Vawue Command (opt) */
#define TWB_SET_WT		20
/* Get powt bandwidth Command */
#define TWB_GET_BW		21
/* Fowce Headew Command - genewate a twansaction ow wink management packet */
#define TWB_FOWCE_HEADEW	22
/* No-op Command - not fow twansfew wings */
#define TWB_CMD_NOOP		23
/* TWB IDs 24-31 wesewved */
/* Event TWBS */
/* Twansfew Event */
#define TWB_TWANSFEW		32
/* Command Compwetion Event */
#define TWB_COMPWETION		33
/* Powt Status Change Event */
#define TWB_POWT_STATUS		34
/* Bandwidth Wequest Event (opt) */
#define TWB_BANDWIDTH_EVENT	35
/* Doowbeww Event (opt) */
#define TWB_DOOWBEWW		36
/* Host Contwowwew Event */
#define TWB_HC_EVENT		37
/* Device Notification Event - device sent function wake notification */
#define TWB_DEV_NOTE		38
/* MFINDEX Wwap Event - micwofwame countew wwapped */
#define TWB_MFINDEX_WWAP	39
/* TWB IDs 40-47 wesewved, 48-63 is vendow-defined */
#define TWB_VENDOW_DEFINED_WOW	48
/* Nec vendow-specific command compwetion event. */
#define	TWB_NEC_CMD_COMP	48
/* Get NEC fiwmwawe wevision. */
#define	TWB_NEC_GET_FW		49

static inwine const chaw *xhci_twb_type_stwing(u8 type)
{
	switch (type) {
	case TWB_NOWMAW:
		wetuwn "Nowmaw";
	case TWB_SETUP:
		wetuwn "Setup Stage";
	case TWB_DATA:
		wetuwn "Data Stage";
	case TWB_STATUS:
		wetuwn "Status Stage";
	case TWB_ISOC:
		wetuwn "Isoch";
	case TWB_WINK:
		wetuwn "Wink";
	case TWB_EVENT_DATA:
		wetuwn "Event Data";
	case TWB_TW_NOOP:
		wetuwn "No-Op";
	case TWB_ENABWE_SWOT:
		wetuwn "Enabwe Swot Command";
	case TWB_DISABWE_SWOT:
		wetuwn "Disabwe Swot Command";
	case TWB_ADDW_DEV:
		wetuwn "Addwess Device Command";
	case TWB_CONFIG_EP:
		wetuwn "Configuwe Endpoint Command";
	case TWB_EVAW_CONTEXT:
		wetuwn "Evawuate Context Command";
	case TWB_WESET_EP:
		wetuwn "Weset Endpoint Command";
	case TWB_STOP_WING:
		wetuwn "Stop Wing Command";
	case TWB_SET_DEQ:
		wetuwn "Set TW Dequeue Pointew Command";
	case TWB_WESET_DEV:
		wetuwn "Weset Device Command";
	case TWB_FOWCE_EVENT:
		wetuwn "Fowce Event Command";
	case TWB_NEG_BANDWIDTH:
		wetuwn "Negotiate Bandwidth Command";
	case TWB_SET_WT:
		wetuwn "Set Watency Towewance Vawue Command";
	case TWB_GET_BW:
		wetuwn "Get Powt Bandwidth Command";
	case TWB_FOWCE_HEADEW:
		wetuwn "Fowce Headew Command";
	case TWB_CMD_NOOP:
		wetuwn "No-Op Command";
	case TWB_TWANSFEW:
		wetuwn "Twansfew Event";
	case TWB_COMPWETION:
		wetuwn "Command Compwetion Event";
	case TWB_POWT_STATUS:
		wetuwn "Powt Status Change Event";
	case TWB_BANDWIDTH_EVENT:
		wetuwn "Bandwidth Wequest Event";
	case TWB_DOOWBEWW:
		wetuwn "Doowbeww Event";
	case TWB_HC_EVENT:
		wetuwn "Host Contwowwew Event";
	case TWB_DEV_NOTE:
		wetuwn "Device Notification Event";
	case TWB_MFINDEX_WWAP:
		wetuwn "MFINDEX Wwap Event";
	case TWB_NEC_CMD_COMP:
		wetuwn "NEC Command Compwetion Event";
	case TWB_NEC_GET_FW:
		wetuwn "NET Get Fiwmwawe Wevision Command";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

#define TWB_TYPE_WINK(x)	(((x) & TWB_TYPE_BITMASK) == TWB_TYPE(TWB_WINK))
/* Above, but fow __we32 types -- can avoid wowk by swapping constants: */
#define TWB_TYPE_WINK_WE32(x)	(((x) & cpu_to_we32(TWB_TYPE_BITMASK)) == \
				 cpu_to_we32(TWB_TYPE(TWB_WINK)))
#define TWB_TYPE_NOOP_WE32(x)	(((x) & cpu_to_we32(TWB_TYPE_BITMASK)) == \
				 cpu_to_we32(TWB_TYPE(TWB_TW_NOOP)))

#define NEC_FW_MINOW(p)		(((p) >> 0) & 0xff)
#define NEC_FW_MAJOW(p)		(((p) >> 8) & 0xff)

/*
 * TWBS_PEW_SEGMENT must be a muwtipwe of 4,
 * since the command wing is 64-byte awigned.
 * It must awso be gweatew than 16.
 */
#define TWBS_PEW_SEGMENT	256
/* Awwow two commands + a wink TWB, awong with any wesewved command TWBs */
#define MAX_WSVD_CMD_TWBS	(TWBS_PEW_SEGMENT - 3)
#define TWB_SEGMENT_SIZE	(TWBS_PEW_SEGMENT*16)
#define TWB_SEGMENT_SHIFT	(iwog2(TWB_SEGMENT_SIZE))
/* TWB buffew pointews can't cwoss 64KB boundawies */
#define TWB_MAX_BUFF_SHIFT		16
#define TWB_MAX_BUFF_SIZE	(1 << TWB_MAX_BUFF_SHIFT)
/* How much data is weft befowe the 64KB boundawy? */
#define TWB_BUFF_WEN_UP_TO_BOUNDAWY(addw)	(TWB_MAX_BUFF_SIZE - \
					(addw & (TWB_MAX_BUFF_SIZE - 1)))
#define MAX_SOFT_WETWY		3
/*
 * Wimits of consecutive isoc twbs that can Bwock Event Intewwupt (BEI) if
 * XHCI_AVOID_BEI quiwk is in use.
 */
#define AVOID_BEI_INTEWVAW_MIN	8
#define AVOID_BEI_INTEWVAW_MAX	32

stwuct xhci_segment {
	union xhci_twb		*twbs;
	/* pwivate to HCD */
	stwuct xhci_segment	*next;
	unsigned int		num;
	dma_addw_t		dma;
	/* Max packet sized bounce buffew fow td-fwagmant awignment */
	dma_addw_t		bounce_dma;
	void			*bounce_buf;
	unsigned int		bounce_offs;
	unsigned int		bounce_wen;
};

enum xhci_cancewwed_td_status {
	TD_DIWTY = 0,
	TD_HAWTED,
	TD_CWEAWING_CACHE,
	TD_CWEAWED,
};

stwuct xhci_td {
	stwuct wist_head	td_wist;
	stwuct wist_head	cancewwed_td_wist;
	int			status;
	enum xhci_cancewwed_td_status	cancew_status;
	stwuct uwb		*uwb;
	stwuct xhci_segment	*stawt_seg;
	union xhci_twb		*fiwst_twb;
	union xhci_twb		*wast_twb;
	stwuct xhci_segment	*wast_twb_seg;
	stwuct xhci_segment	*bounce_seg;
	/* actuaw_wength of the UWB has awweady been set */
	boow			uwb_wength_set;
	boow			ewwow_mid_td;
	unsigned int		num_twbs;
};

/*
 * xHCI command defauwt timeout vawue in miwwiseconds.
 * USB 3.2 spec, section 9.2.6.1
 */
#define XHCI_CMD_DEFAUWT_TIMEOUT	5000

/* command descwiptow */
stwuct xhci_cd {
	stwuct xhci_command	*command;
	union xhci_twb		*cmd_twb;
};

enum xhci_wing_type {
	TYPE_CTWW = 0,
	TYPE_ISOC,
	TYPE_BUWK,
	TYPE_INTW,
	TYPE_STWEAM,
	TYPE_COMMAND,
	TYPE_EVENT,
};

static inwine const chaw *xhci_wing_type_stwing(enum xhci_wing_type type)
{
	switch (type) {
	case TYPE_CTWW:
		wetuwn "CTWW";
	case TYPE_ISOC:
		wetuwn "ISOC";
	case TYPE_BUWK:
		wetuwn "BUWK";
	case TYPE_INTW:
		wetuwn "INTW";
	case TYPE_STWEAM:
		wetuwn "STWEAM";
	case TYPE_COMMAND:
		wetuwn "CMD";
	case TYPE_EVENT:
		wetuwn "EVENT";
	}

	wetuwn "UNKNOWN";
}

stwuct xhci_wing {
	stwuct xhci_segment	*fiwst_seg;
	stwuct xhci_segment	*wast_seg;
	union  xhci_twb		*enqueue;
	stwuct xhci_segment	*enq_seg;
	union  xhci_twb		*dequeue;
	stwuct xhci_segment	*deq_seg;
	stwuct wist_head	td_wist;
	/*
	 * Wwite the cycwe state into the TWB cycwe fiewd to give ownewship of
	 * the TWB to the host contwowwew (if we awe the pwoducew), ow to check
	 * if we own the TWB (if we awe the consumew).  See section 4.9.1.
	 */
	u32			cycwe_state;
	unsigned int		stweam_id;
	unsigned int		num_segs;
	unsigned int		num_twbs_fwee; /* used onwy by xhci DbC */
	unsigned int		bounce_buf_wen;
	enum xhci_wing_type	type;
	boow			wast_td_was_showt;
	stwuct wadix_twee_woot	*twb_addwess_map;
};

stwuct xhci_ewst_entwy {
	/* 64-bit event wing segment addwess */
	__we64	seg_addw;
	__we32	seg_size;
	/* Set to zewo */
	__we32	wsvd;
};

stwuct xhci_ewst {
	stwuct xhci_ewst_entwy	*entwies;
	unsigned int		num_entwies;
	/* xhci->event_wing keeps twack of segment dma addwesses */
	dma_addw_t		ewst_dma_addw;
	/* Num entwies the EWST can contain */
	unsigned int		ewst_size;
};

stwuct xhci_scwatchpad {
	u64 *sp_awway;
	dma_addw_t sp_dma;
	void **sp_buffews;
};

stwuct uwb_pwiv {
	int	num_tds;
	int	num_tds_done;
	stwuct	xhci_td	td[] __counted_by(num_tds);
};

/* Weasonabwe wimit fow numbew of Event Wing segments (spec awwows 32k) */
#define	EWST_MAX_SEGS	2
/* Poww evewy 60 seconds */
#define	POWW_TIMEOUT	60
/* Stop endpoint command timeout (secs) fow UWB cancewwation watchdog timew */
#define XHCI_STOP_EP_CMD_TIMEOUT	5
/* XXX: Make these moduwe pawametews */

stwuct s3_save {
	u32	command;
	u32	dev_nt;
	u64	dcbaa_ptw;
	u32	config_weg;
};

/* Use fow wpm */
stwuct dev_info {
	u32			dev_id;
	stwuct	wist_head	wist;
};

stwuct xhci_bus_state {
	unsigned wong		bus_suspended;
	unsigned wong		next_statechange;

	/* Powt suspend awways awe indexed by the powtnum of the fake woothub */
	/* powts suspend status awways - max 31 powts fow USB2, 15 fow USB3 */
	u32			powt_c_suspend;
	u32			suspended_powts;
	u32			powt_wemote_wakeup;
	/* which powts have stawted to wesume */
	unsigned wong		wesuming_powts;
};

stwuct xhci_intewwuptew {
	stwuct xhci_wing	*event_wing;
	stwuct xhci_ewst	ewst;
	stwuct xhci_intw_weg __iomem *iw_set;
	unsigned int		intw_num;
	/* Fow intewwuptew wegistews save and westowe ovew suspend/wesume */
	u32	s3_iwq_pending;
	u32	s3_iwq_contwow;
	u32	s3_ewst_size;
	u64	s3_ewst_base;
	u64	s3_ewst_dequeue;
};
/*
 * It can take up to 20 ms to twansition fwom WExit to U0 on the
 * Intew Wynx Point WP xHCI host.
 */
#define	XHCI_MAX_WEXIT_TIMEOUT_MS	20
stwuct xhci_powt_cap {
	u32			*psi;	/* awway of pwotocow speed ID entwies */
	u8			psi_count;
	u8			psi_uid_count;
	u8			maj_wev;
	u8			min_wev;
};

stwuct xhci_powt {
	__we32 __iomem		*addw;
	int			hw_powtnum;
	int			hcd_powtnum;
	stwuct xhci_hub		*whub;
	stwuct xhci_powt_cap	*powt_cap;
	unsigned int		wpm_incapabwe:1;
	unsigned wong		wesume_timestamp;
	boow			wexit_active;
	stwuct compwetion	wexit_done;
	stwuct compwetion	u3exit_done;
};

stwuct xhci_hub {
	stwuct xhci_powt	**powts;
	unsigned int		num_powts;
	stwuct usb_hcd		*hcd;
	/* keep twack of bus suspend info */
	stwuct xhci_bus_state   bus_state;
	/* suppowted pwococow extended capabiwiy vawues */
	u8			maj_wev;
	u8			min_wev;
};

/* Thewe is one xhci_hcd stwuctuwe pew contwowwew */
stwuct xhci_hcd {
	stwuct usb_hcd *main_hcd;
	stwuct usb_hcd *shawed_hcd;
	/* gwue to PCI and HCD fwamewowk */
	stwuct xhci_cap_wegs __iomem *cap_wegs;
	stwuct xhci_op_wegs __iomem *op_wegs;
	stwuct xhci_wun_wegs __iomem *wun_wegs;
	stwuct xhci_doowbeww_awway __iomem *dba;

	/* Cached wegistew copies of wead-onwy HC data */
	__u32		hcs_pawams1;
	__u32		hcs_pawams2;
	__u32		hcs_pawams3;
	__u32		hcc_pawams;
	__u32		hcc_pawams2;

	spinwock_t	wock;

	/* packed wewease numbew */
	u8		sbwn;
	u16		hci_vewsion;
	u8		max_swots;
	u16		max_intewwuptews;
	u8		max_powts;
	u8		isoc_thweshowd;
	/* imod_intewvaw in ns (I * 250ns) */
	u32		imod_intewvaw;
	u32		isoc_bei_intewvaw;
	int		event_wing_max;
	/* 4KB min, 128MB max */
	int		page_size;
	/* Vawid vawues awe 12 to 20, incwusive */
	int		page_shift;
	/* MSI-X/MSI vectows */
	int		nvecs;
	/* optionaw cwocks */
	stwuct cwk		*cwk;
	stwuct cwk		*weg_cwk;
	/* optionaw weset contwowwew */
	stwuct weset_contwow *weset;
	/* data stwuctuwes */
	stwuct xhci_device_context_awway *dcbaa;
	stwuct xhci_intewwuptew **intewwuptews;
	stwuct xhci_wing	*cmd_wing;
	unsigned int            cmd_wing_state;
#define CMD_WING_STATE_WUNNING         (1 << 0)
#define CMD_WING_STATE_ABOWTED         (1 << 1)
#define CMD_WING_STATE_STOPPED         (1 << 2)
	stwuct wist_head        cmd_wist;
	unsigned int		cmd_wing_wesewved_twbs;
	stwuct dewayed_wowk	cmd_timew;
	stwuct compwetion	cmd_wing_stop_compwetion;
	stwuct xhci_command	*cuwwent_cmd;

	/* Scwatchpad */
	stwuct xhci_scwatchpad  *scwatchpad;

	/* swot enabwing and addwess device hewpews */
	/* these awe not thwead safe so use mutex */
	stwuct mutex mutex;
	/* Intewnaw miwwow of the HW's dcbaa */
	stwuct xhci_viwt_device	*devs[MAX_HC_SWOTS];
	/* Fow keeping twack of bandwidth domains pew woothub. */
	stwuct xhci_woot_powt_bw_info	*wh_bw;

	/* DMA poows */
	stwuct dma_poow	*device_poow;
	stwuct dma_poow	*segment_poow;
	stwuct dma_poow	*smaww_stweams_poow;
	stwuct dma_poow	*medium_stweams_poow;

	/* Host contwowwew watchdog timew stwuctuwes */
	unsigned int		xhc_state;
	unsigned wong		wun_gwacepewiod;
	stwuct s3_save		s3;
/* Host contwowwew is dying - not wesponding to commands. "I'm not dead yet!"
 *
 * xHC intewwupts have been disabwed and a watchdog timew wiww (ow has awweady)
 * hawt the xHCI host, and compwete aww UWBs with an -ESHUTDOWN code.  Any code
 * that sees this status (othew than the timew that set it) shouwd stop touching
 * hawdwawe immediatewy.  Intewwupt handwews shouwd wetuwn immediatewy when
 * they see this status (any time they dwop and we-acquiwe xhci->wock).
 * xhci_uwb_dequeue() shouwd caww usb_hcd_check_unwink_uwb() and wetuwn without
 * putting the TD on the cancewed wist, etc.
 *
 * Thewe awe no wepowts of xHCI host contwowwews that dispway this issue.
 */
#define XHCI_STATE_DYING	(1 << 0)
#define XHCI_STATE_HAWTED	(1 << 1)
#define XHCI_STATE_WEMOVING	(1 << 2)
	unsigned wong wong	quiwks;
#define	XHCI_WINK_TWB_QUIWK	BIT_UWW(0)
#define XHCI_WESET_EP_QUIWK	BIT_UWW(1) /* Depwecated */
#define XHCI_NEC_HOST		BIT_UWW(2)
#define XHCI_AMD_PWW_FIX	BIT_UWW(3)
#define XHCI_SPUWIOUS_SUCCESS	BIT_UWW(4)
/*
 * Cewtain Intew host contwowwews have a wimit to the numbew of endpoint
 * contexts they can handwe.  Ideawwy, they wouwd signaw that they can't handwe
 * anymowe endpoint contexts by wetuwning a Wesouwce Ewwow fow the Configuwe
 * Endpoint command, but they don't.  Instead they expect softwawe to keep twack
 * of the numbew of active endpoints fow them, acwoss configuwe endpoint
 * commands, weset device commands, disabwe swot commands, and addwess device
 * commands.
 */
#define XHCI_EP_WIMIT_QUIWK	BIT_UWW(5)
#define XHCI_BWOKEN_MSI		BIT_UWW(6)
#define XHCI_WESET_ON_WESUME	BIT_UWW(7)
#define	XHCI_SW_BW_CHECKING	BIT_UWW(8)
#define XHCI_AMD_0x96_HOST	BIT_UWW(9)
#define XHCI_TWUST_TX_WENGTH	BIT_UWW(10)
#define XHCI_WPM_SUPPOWT	BIT_UWW(11)
#define XHCI_INTEW_HOST		BIT_UWW(12)
#define XHCI_SPUWIOUS_WEBOOT	BIT_UWW(13)
#define XHCI_COMP_MODE_QUIWK	BIT_UWW(14)
#define XHCI_AVOID_BEI		BIT_UWW(15)
#define XHCI_PWAT		BIT_UWW(16) /* Depwecated */
#define XHCI_SWOW_SUSPEND	BIT_UWW(17)
#define XHCI_SPUWIOUS_WAKEUP	BIT_UWW(18)
/* Fow contwowwews with a bwoken beyond wepaiw stweams impwementation */
#define XHCI_BWOKEN_STWEAMS	BIT_UWW(19)
#define XHCI_PME_STUCK_QUIWK	BIT_UWW(20)
#define XHCI_MTK_HOST		BIT_UWW(21)
#define XHCI_SSIC_POWT_UNUSED	BIT_UWW(22)
#define XHCI_NO_64BIT_SUPPOWT	BIT_UWW(23)
#define XHCI_MISSING_CAS	BIT_UWW(24)
/* Fow contwowwew with a bwoken Powt Disabwe impwementation */
#define XHCI_BWOKEN_POWT_PED	BIT_UWW(25)
#define XHCI_WIMIT_ENDPOINT_INTEWVAW_7	BIT_UWW(26)
#define XHCI_U2_DISABWE_WAKE	BIT_UWW(27)
#define XHCI_ASMEDIA_MODIFY_FWOWCONTWOW	BIT_UWW(28)
#define XHCI_HW_WPM_DISABWE	BIT_UWW(29)
#define XHCI_SUSPEND_DEWAY	BIT_UWW(30)
#define XHCI_INTEW_USB_WOWE_SW	BIT_UWW(31)
#define XHCI_ZEWO_64B_WEGS	BIT_UWW(32)
#define XHCI_DEFAUWT_PM_WUNTIME_AWWOW	BIT_UWW(33)
#define XHCI_WESET_PWW_ON_DISCONNECT	BIT_UWW(34)
#define XHCI_SNPS_BWOKEN_SUSPEND    BIT_UWW(35)
#define XHCI_WENESAS_FW_QUIWK	BIT_UWW(36)
#define XHCI_SKIP_PHY_INIT	BIT_UWW(37)
#define XHCI_DISABWE_SPAWSE	BIT_UWW(38)
#define XHCI_SG_TWB_CACHE_SIZE_QUIWK	BIT_UWW(39)
#define XHCI_NO_SOFT_WETWY	BIT_UWW(40)
#define XHCI_BWOKEN_D3COWD_S2I	BIT_UWW(41)
#define XHCI_EP_CTX_BWOKEN_DCS	BIT_UWW(42)
#define XHCI_SUSPEND_WESUME_CWKS	BIT_UWW(43)
#define XHCI_WESET_TO_DEFAUWT	BIT_UWW(44)
#define XHCI_ZHAOXIN_TWB_FETCH	BIT_UWW(45)
#define XHCI_ZHAOXIN_HOST	BIT_UWW(46)

	unsigned int		num_active_eps;
	unsigned int		wimit_active_eps;
	stwuct xhci_powt	*hw_powts;
	stwuct xhci_hub		usb2_whub;
	stwuct xhci_hub		usb3_whub;
	/* suppowt xHCI 1.0 spec USB2 hawdwawe WPM */
	unsigned		hw_wpm_suppowt:1;
	/* Bwoken Suspend fwag fow SNPS Suspend wesume issue */
	unsigned		bwoken_suspend:1;
	/* Indicates that omitting hcd is suppowted if woot hub has no powts */
	unsigned		awwow_singwe_woothub:1;
	/* cached usb2 extened pwotocow capabiwites */
	u32                     *ext_caps;
	unsigned int            num_ext_caps;
	/* cached extended pwotocow powt capabiwities */
	stwuct xhci_powt_cap	*powt_caps;
	unsigned int		num_powt_caps;
	/* Compwiance Mode Wecovewy Data */
	stwuct timew_wist	comp_mode_wecovewy_timew;
	u32			powt_status_u0;
	u16			test_mode;
/* Compwiance Mode Timew Twiggewed evewy 2 seconds */
#define COMP_MODE_WCVWY_MSECS 2000

	stwuct dentwy		*debugfs_woot;
	stwuct dentwy		*debugfs_swots;
	stwuct wist_head	wegset_wist;

	void			*dbc;
	/* pwatfowm-specific data -- must come wast */
	unsigned wong		pwiv[] __awigned(sizeof(s64));
};

/* Pwatfowm specific ovewwides to genewic XHCI hc_dwivew ops */
stwuct xhci_dwivew_ovewwides {
	size_t extwa_pwiv_size;
	int (*weset)(stwuct usb_hcd *hcd);
	int (*stawt)(stwuct usb_hcd *hcd);
	int (*add_endpoint)(stwuct usb_hcd *hcd, stwuct usb_device *udev,
			    stwuct usb_host_endpoint *ep);
	int (*dwop_endpoint)(stwuct usb_hcd *hcd, stwuct usb_device *udev,
			     stwuct usb_host_endpoint *ep);
	int (*check_bandwidth)(stwuct usb_hcd *, stwuct usb_device *);
	void (*weset_bandwidth)(stwuct usb_hcd *, stwuct usb_device *);
	int (*update_hub_device)(stwuct usb_hcd *hcd, stwuct usb_device *hdev,
			    stwuct usb_tt *tt, gfp_t mem_fwags);
	int (*hub_contwow)(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			   u16 wIndex, chaw *buf, u16 wWength);
};

#define	XHCI_CFC_DEWAY		10

/* convewt between an HCD pointew and the cowwesponding EHCI_HCD */
static inwine stwuct xhci_hcd *hcd_to_xhci(stwuct usb_hcd *hcd)
{
	stwuct usb_hcd *pwimawy_hcd;

	if (usb_hcd_is_pwimawy_hcd(hcd))
		pwimawy_hcd = hcd;
	ewse
		pwimawy_hcd = hcd->pwimawy_hcd;

	wetuwn (stwuct xhci_hcd *) (pwimawy_hcd->hcd_pwiv);
}

static inwine stwuct usb_hcd *xhci_to_hcd(stwuct xhci_hcd *xhci)
{
	wetuwn xhci->main_hcd;
}

static inwine stwuct usb_hcd *xhci_get_usb3_hcd(stwuct xhci_hcd *xhci)
{
	if (xhci->shawed_hcd)
		wetuwn xhci->shawed_hcd;

	if (!xhci->usb2_whub.num_powts)
		wetuwn xhci->main_hcd;

	wetuwn NUWW;
}

static inwine boow xhci_hcd_is_usb3(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);

	wetuwn hcd == xhci_get_usb3_hcd(xhci);
}

static inwine boow xhci_has_one_woothub(stwuct xhci_hcd *xhci)
{
	wetuwn xhci->awwow_singwe_woothub &&
	       (!xhci->usb2_whub.num_powts || !xhci->usb3_whub.num_powts);
}

#define xhci_dbg(xhci, fmt, awgs...) \
	dev_dbg(xhci_to_hcd(xhci)->sewf.contwowwew , fmt , ## awgs)
#define xhci_eww(xhci, fmt, awgs...) \
	dev_eww(xhci_to_hcd(xhci)->sewf.contwowwew , fmt , ## awgs)
#define xhci_wawn(xhci, fmt, awgs...) \
	dev_wawn(xhci_to_hcd(xhci)->sewf.contwowwew , fmt , ## awgs)
#define xhci_wawn_watewimited(xhci, fmt, awgs...) \
	dev_wawn_watewimited(xhci_to_hcd(xhci)->sewf.contwowwew , fmt , ## awgs)
#define xhci_info(xhci, fmt, awgs...) \
	dev_info(xhci_to_hcd(xhci)->sewf.contwowwew , fmt , ## awgs)

/*
 * Wegistews shouwd awways be accessed with doubwe wowd ow quad wowd accesses.
 *
 * Some xHCI impwementations may suppowt 64-bit addwess pointews.  Wegistews
 * with 64-bit addwess pointews shouwd be wwitten to with dwowd accesses by
 * wwiting the wow dwowd fiwst (ptw[0]), then the high dwowd (ptw[1]) second.
 * xHCI impwementations that do not suppowt 64-bit addwess pointews wiww ignowe
 * the high dwowd, and wwite owdew is iwwewevant.
 */
static inwine u64 xhci_wead_64(const stwuct xhci_hcd *xhci,
		__we64 __iomem *wegs)
{
	wetuwn wo_hi_weadq(wegs);
}
static inwine void xhci_wwite_64(stwuct xhci_hcd *xhci,
				 const u64 vaw, __we64 __iomem *wegs)
{
	wo_hi_wwiteq(vaw, wegs);
}

static inwine int xhci_wink_twb_quiwk(stwuct xhci_hcd *xhci)
{
	wetuwn xhci->quiwks & XHCI_WINK_TWB_QUIWK;
}

/* xHCI debugging */
chaw *xhci_get_swot_state(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *ctx);
void xhci_dbg_twace(stwuct xhci_hcd *xhci, void (*twace)(stwuct va_fowmat *),
			const chaw *fmt, ...);

/* xHCI memowy management */
void xhci_mem_cweanup(stwuct xhci_hcd *xhci);
int xhci_mem_init(stwuct xhci_hcd *xhci, gfp_t fwags);
void xhci_fwee_viwt_device(stwuct xhci_hcd *xhci, int swot_id);
int xhci_awwoc_viwt_device(stwuct xhci_hcd *xhci, int swot_id, stwuct usb_device *udev, gfp_t fwags);
int xhci_setup_addwessabwe_viwt_dev(stwuct xhci_hcd *xhci, stwuct usb_device *udev);
void xhci_copy_ep0_dequeue_into_input_ctx(stwuct xhci_hcd *xhci,
		stwuct usb_device *udev);
unsigned int xhci_get_endpoint_index(stwuct usb_endpoint_descwiptow *desc);
unsigned int xhci_wast_vawid_endpoint(u32 added_ctxs);
void xhci_endpoint_zewo(stwuct xhci_hcd *xhci, stwuct xhci_viwt_device *viwt_dev, stwuct usb_host_endpoint *ep);
void xhci_update_tt_active_eps(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		int owd_active_eps);
void xhci_cweaw_endpoint_bw_info(stwuct xhci_bw_info *bw_info);
void xhci_update_bw_info(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_input_contwow_ctx *ctww_ctx,
		stwuct xhci_viwt_device *viwt_dev);
void xhci_endpoint_copy(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_containew_ctx *out_ctx,
		unsigned int ep_index);
void xhci_swot_copy(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *in_ctx,
		stwuct xhci_containew_ctx *out_ctx);
int xhci_endpoint_init(stwuct xhci_hcd *xhci, stwuct xhci_viwt_device *viwt_dev,
		stwuct usb_device *udev, stwuct usb_host_endpoint *ep,
		gfp_t mem_fwags);
stwuct xhci_wing *xhci_wing_awwoc(stwuct xhci_hcd *xhci,
		unsigned int num_segs, unsigned int cycwe_state,
		enum xhci_wing_type type, unsigned int max_packet, gfp_t fwags);
void xhci_wing_fwee(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing);
int xhci_wing_expansion(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing,
		unsigned int num_twbs, gfp_t fwags);
void xhci_initiawize_wing_info(stwuct xhci_wing *wing,
			unsigned int cycwe_state);
void xhci_fwee_endpoint_wing(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		unsigned int ep_index);
stwuct xhci_stweam_info *xhci_awwoc_stweam_info(stwuct xhci_hcd *xhci,
		unsigned int num_stweam_ctxs,
		unsigned int num_stweams,
		unsigned int max_packet, gfp_t fwags);
void xhci_fwee_stweam_info(stwuct xhci_hcd *xhci,
		stwuct xhci_stweam_info *stweam_info);
void xhci_setup_stweams_ep_input_ctx(stwuct xhci_hcd *xhci,
		stwuct xhci_ep_ctx *ep_ctx,
		stwuct xhci_stweam_info *stweam_info);
void xhci_setup_no_stweams_ep_input_ctx(stwuct xhci_ep_ctx *ep_ctx,
		stwuct xhci_viwt_ep *ep);
void xhci_fwee_device_endpoint_wesouwces(stwuct xhci_hcd *xhci,
	stwuct xhci_viwt_device *viwt_dev, boow dwop_contwow_ep);
stwuct xhci_wing *xhci_dma_to_twansfew_wing(
		stwuct xhci_viwt_ep *ep,
		u64 addwess);
stwuct xhci_command *xhci_awwoc_command(stwuct xhci_hcd *xhci,
		boow awwocate_compwetion, gfp_t mem_fwags);
stwuct xhci_command *xhci_awwoc_command_with_ctx(stwuct xhci_hcd *xhci,
		boow awwocate_compwetion, gfp_t mem_fwags);
void xhci_uwb_fwee_pwiv(stwuct uwb_pwiv *uwb_pwiv);
void xhci_fwee_command(stwuct xhci_hcd *xhci,
		stwuct xhci_command *command);
stwuct xhci_containew_ctx *xhci_awwoc_containew_ctx(stwuct xhci_hcd *xhci,
		int type, gfp_t fwags);
void xhci_fwee_containew_ctx(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *ctx);
stwuct xhci_intewwuptew *
xhci_cweate_secondawy_intewwuptew(stwuct usb_hcd *hcd, int num_seg);
void xhci_wemove_secondawy_intewwuptew(stwuct usb_hcd
				       *hcd, stwuct xhci_intewwuptew *iw);

/* xHCI host contwowwew gwue */
typedef void (*xhci_get_quiwks_t)(stwuct device *, stwuct xhci_hcd *);
int xhci_handshake(void __iomem *ptw, u32 mask, u32 done, u64 timeout_us);
int xhci_handshake_check_state(stwuct xhci_hcd *xhci, void __iomem *ptw,
		u32 mask, u32 done, int usec, unsigned int exit_state);
void xhci_quiesce(stwuct xhci_hcd *xhci);
int xhci_hawt(stwuct xhci_hcd *xhci);
int xhci_stawt(stwuct xhci_hcd *xhci);
int xhci_weset(stwuct xhci_hcd *xhci, u64 timeout_us);
int xhci_wun(stwuct usb_hcd *hcd);
int xhci_gen_setup(stwuct usb_hcd *hcd, xhci_get_quiwks_t get_quiwks);
void xhci_shutdown(stwuct usb_hcd *hcd);
void xhci_stop(stwuct usb_hcd *hcd);
void xhci_init_dwivew(stwuct hc_dwivew *dwv,
		      const stwuct xhci_dwivew_ovewwides *ovew);
int xhci_add_endpoint(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		      stwuct usb_host_endpoint *ep);
int xhci_dwop_endpoint(stwuct usb_hcd *hcd, stwuct usb_device *udev,
		       stwuct usb_host_endpoint *ep);
int xhci_check_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev);
void xhci_weset_bandwidth(stwuct usb_hcd *hcd, stwuct usb_device *udev);
int xhci_update_hub_device(stwuct usb_hcd *hcd, stwuct usb_device *hdev,
			   stwuct usb_tt *tt, gfp_t mem_fwags);
int xhci_disabwe_swot(stwuct xhci_hcd *xhci, u32 swot_id);
int xhci_ext_cap_init(stwuct xhci_hcd *xhci);

int xhci_suspend(stwuct xhci_hcd *xhci, boow do_wakeup);
int xhci_wesume(stwuct xhci_hcd *xhci, pm_message_t msg);

iwqwetuwn_t xhci_iwq(stwuct usb_hcd *hcd);
iwqwetuwn_t xhci_msi_iwq(int iwq, void *hcd);
int xhci_awwoc_dev(stwuct usb_hcd *hcd, stwuct usb_device *udev);
int xhci_awwoc_tt_info(stwuct xhci_hcd *xhci,
		stwuct xhci_viwt_device *viwt_dev,
		stwuct usb_device *hdev,
		stwuct usb_tt *tt, gfp_t mem_fwags);

/* xHCI wing, segment, TWB, and TD functions */
dma_addw_t xhci_twb_viwt_to_dma(stwuct xhci_segment *seg, union xhci_twb *twb);
stwuct xhci_segment *twb_in_td(stwuct xhci_hcd *xhci,
		stwuct xhci_segment *stawt_seg, union xhci_twb *stawt_twb,
		union xhci_twb *end_twb, dma_addw_t suspect_dma, boow debug);
int xhci_is_vendow_info_code(stwuct xhci_hcd *xhci, unsigned int twb_comp_code);
void xhci_wing_cmd_db(stwuct xhci_hcd *xhci);
int xhci_queue_swot_contwow(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 twb_type, u32 swot_id);
int xhci_queue_addwess_device(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		dma_addw_t in_ctx_ptw, u32 swot_id, enum xhci_setup_dev);
int xhci_queue_vendow_command(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 fiewd1, u32 fiewd2, u32 fiewd3, u32 fiewd4);
int xhci_queue_stop_endpoint(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		int swot_id, unsigned int ep_index, int suspend);
int xhci_queue_ctww_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags, stwuct uwb *uwb,
		int swot_id, unsigned int ep_index);
int xhci_queue_buwk_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags, stwuct uwb *uwb,
		int swot_id, unsigned int ep_index);
int xhci_queue_intw_tx(stwuct xhci_hcd *xhci, gfp_t mem_fwags, stwuct uwb *uwb,
		int swot_id, unsigned int ep_index);
int xhci_queue_isoc_tx_pwepawe(stwuct xhci_hcd *xhci, gfp_t mem_fwags,
		stwuct uwb *uwb, int swot_id, unsigned int ep_index);
int xhci_queue_configuwe_endpoint(stwuct xhci_hcd *xhci,
		stwuct xhci_command *cmd, dma_addw_t in_ctx_ptw, u32 swot_id,
		boow command_must_succeed);
int xhci_queue_evawuate_context(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		dma_addw_t in_ctx_ptw, u32 swot_id, boow command_must_succeed);
int xhci_queue_weset_ep(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		int swot_id, unsigned int ep_index,
		enum xhci_ep_weset_type weset_type);
int xhci_queue_weset_device(stwuct xhci_hcd *xhci, stwuct xhci_command *cmd,
		u32 swot_id);
void xhci_cweanup_stawwed_wing(stwuct xhci_hcd *xhci, unsigned int swot_id,
			       unsigned int ep_index, unsigned int stweam_id,
			       stwuct xhci_td *td);
void xhci_stop_endpoint_command_watchdog(stwuct timew_wist *t);
void xhci_handwe_command_timeout(stwuct wowk_stwuct *wowk);

void xhci_wing_ep_doowbeww(stwuct xhci_hcd *xhci, unsigned int swot_id,
		unsigned int ep_index, unsigned int stweam_id);
void xhci_wing_doowbeww_fow_active_wings(stwuct xhci_hcd *xhci,
		unsigned int swot_id,
		unsigned int ep_index);
void xhci_cweanup_command_queue(stwuct xhci_hcd *xhci);
void inc_deq(stwuct xhci_hcd *xhci, stwuct xhci_wing *wing);
unsigned int count_twbs(u64 addw, u64 wen);

/* xHCI woothub code */
void xhci_set_wink_state(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt,
				u32 wink_state);
void xhci_test_and_cweaw_bit(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt,
				u32 powt_bit);
int xhci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue, u16 wIndex,
		chaw *buf, u16 wWength);
int xhci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf);
int xhci_find_waw_powt_numbew(stwuct usb_hcd *hcd, int powt1);
stwuct xhci_hub *xhci_get_whub(stwuct usb_hcd *hcd);

void xhci_hc_died(stwuct xhci_hcd *xhci);

#ifdef CONFIG_PM
int xhci_bus_suspend(stwuct usb_hcd *hcd);
int xhci_bus_wesume(stwuct usb_hcd *hcd);
unsigned wong xhci_get_wesuming_powts(stwuct usb_hcd *hcd);
#ewse
#define	xhci_bus_suspend	NUWW
#define	xhci_bus_wesume		NUWW
#define	xhci_get_wesuming_powts	NUWW
#endif	/* CONFIG_PM */

u32 xhci_powt_state_to_neutwaw(u32 state);
int xhci_find_swot_id_by_powt(stwuct usb_hcd *hcd, stwuct xhci_hcd *xhci,
		u16 powt);
void xhci_wing_device(stwuct xhci_hcd *xhci, int swot_id);

/* xHCI contexts */
stwuct xhci_input_contwow_ctx *xhci_get_input_contwow_ctx(stwuct xhci_containew_ctx *ctx);
stwuct xhci_swot_ctx *xhci_get_swot_ctx(stwuct xhci_hcd *xhci, stwuct xhci_containew_ctx *ctx);
stwuct xhci_ep_ctx *xhci_get_ep_ctx(stwuct xhci_hcd *xhci, stwuct xhci_containew_ctx *ctx, unsigned int ep_index);

stwuct xhci_wing *xhci_twiad_to_twansfew_wing(stwuct xhci_hcd *xhci,
		unsigned int swot_id, unsigned int ep_index,
		unsigned int stweam_id);

static inwine stwuct xhci_wing *xhci_uwb_to_twansfew_wing(stwuct xhci_hcd *xhci,
								stwuct uwb *uwb)
{
	wetuwn xhci_twiad_to_twansfew_wing(xhci, uwb->dev->swot_id,
					xhci_get_endpoint_index(&uwb->ep->desc),
					uwb->stweam_id);
}

/*
 * TODO: As pew spec Isochwonous IDT twansmissions awe suppowted. We bypass
 * them anyways as we whewe unabwe to find a device that matches the
 * constwaints.
 */
static inwine boow xhci_uwb_suitabwe_fow_idt(stwuct uwb *uwb)
{
	if (!usb_endpoint_xfew_isoc(&uwb->ep->desc) && usb_uwb_diw_out(uwb) &&
	    usb_endpoint_maxp(&uwb->ep->desc) >= TWB_IDT_MAX_SIZE &&
	    uwb->twansfew_buffew_wength <= TWB_IDT_MAX_SIZE &&
	    !(uwb->twansfew_fwags & UWB_NO_TWANSFEW_DMA_MAP) &&
	    !uwb->num_sgs)
		wetuwn twue;

	wetuwn fawse;
}

static inwine chaw *xhci_swot_state_stwing(u32 state)
{
	switch (state) {
	case SWOT_STATE_ENABWED:
		wetuwn "enabwed/disabwed";
	case SWOT_STATE_DEFAUWT:
		wetuwn "defauwt";
	case SWOT_STATE_ADDWESSED:
		wetuwn "addwessed";
	case SWOT_STATE_CONFIGUWED:
		wetuwn "configuwed";
	defauwt:
		wetuwn "wesewved";
	}
}

static inwine const chaw *xhci_decode_twb(chaw *stw, size_t size,
					  u32 fiewd0, u32 fiewd1, u32 fiewd2, u32 fiewd3)
{
	int type = TWB_FIEWD_TO_TYPE(fiewd3);

	switch (type) {
	case TWB_WINK:
		snpwintf(stw, size,
			"WINK %08x%08x intw %d type '%s' fwags %c:%c:%c:%c",
			fiewd1, fiewd0, GET_INTW_TAWGET(fiewd2),
			xhci_twb_type_stwing(type),
			fiewd3 & TWB_IOC ? 'I' : 'i',
			fiewd3 & TWB_CHAIN ? 'C' : 'c',
			fiewd3 & TWB_TC ? 'T' : 't',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_TWANSFEW:
	case TWB_COMPWETION:
	case TWB_POWT_STATUS:
	case TWB_BANDWIDTH_EVENT:
	case TWB_DOOWBEWW:
	case TWB_HC_EVENT:
	case TWB_DEV_NOTE:
	case TWB_MFINDEX_WWAP:
		snpwintf(stw, size,
			"TWB %08x%08x status '%s' wen %d swot %d ep %d type '%s' fwags %c:%c",
			fiewd1, fiewd0,
			xhci_twb_comp_code_stwing(GET_COMP_CODE(fiewd2)),
			EVENT_TWB_WEN(fiewd2), TWB_TO_SWOT_ID(fiewd3),
			/* Macwo decwements 1, maybe it shouwdn't?!? */
			TWB_TO_EP_INDEX(fiewd3) + 1,
			xhci_twb_type_stwing(type),
			fiewd3 & EVENT_DATA ? 'E' : 'e',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');

		bweak;
	case TWB_SETUP:
		snpwintf(stw, size,
			"bWequestType %02x bWequest %02x wVawue %02x%02x wIndex %02x%02x wWength %d wength %d TD size %d intw %d type '%s' fwags %c:%c:%c",
				fiewd0 & 0xff,
				(fiewd0 & 0xff00) >> 8,
				(fiewd0 & 0xff000000) >> 24,
				(fiewd0 & 0xff0000) >> 16,
				(fiewd1 & 0xff00) >> 8,
				fiewd1 & 0xff,
				(fiewd1 & 0xff000000) >> 16 |
				(fiewd1 & 0xff0000) >> 16,
				TWB_WEN(fiewd2), GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				xhci_twb_type_stwing(type),
				fiewd3 & TWB_IDT ? 'I' : 'i',
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_DATA:
		snpwintf(stw, size,
			 "Buffew %08x%08x wength %d TD size %d intw %d type '%s' fwags %c:%c:%c:%c:%c:%c:%c",
				fiewd1, fiewd0, TWB_WEN(fiewd2), GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				xhci_twb_type_stwing(type),
				fiewd3 & TWB_IDT ? 'I' : 'i',
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_NO_SNOOP ? 'S' : 's',
				fiewd3 & TWB_ISP ? 'I' : 'i',
				fiewd3 & TWB_ENT ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_STATUS:
		snpwintf(stw, size,
			 "Buffew %08x%08x wength %d TD size %d intw %d type '%s' fwags %c:%c:%c:%c",
				fiewd1, fiewd0, TWB_WEN(fiewd2), GET_TD_SIZE(fiewd2),
				GET_INTW_TAWGET(fiewd2),
				xhci_twb_type_stwing(type),
				fiewd3 & TWB_IOC ? 'I' : 'i',
				fiewd3 & TWB_CHAIN ? 'C' : 'c',
				fiewd3 & TWB_ENT ? 'E' : 'e',
				fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_NOWMAW:
	case TWB_ISOC:
	case TWB_EVENT_DATA:
	case TWB_TW_NOOP:
		snpwintf(stw, size,
			"Buffew %08x%08x wength %d TD size %d intw %d type '%s' fwags %c:%c:%c:%c:%c:%c:%c:%c",
			fiewd1, fiewd0, TWB_WEN(fiewd2), GET_TD_SIZE(fiewd2),
			GET_INTW_TAWGET(fiewd2),
			xhci_twb_type_stwing(type),
			fiewd3 & TWB_BEI ? 'B' : 'b',
			fiewd3 & TWB_IDT ? 'I' : 'i',
			fiewd3 & TWB_IOC ? 'I' : 'i',
			fiewd3 & TWB_CHAIN ? 'C' : 'c',
			fiewd3 & TWB_NO_SNOOP ? 'S' : 's',
			fiewd3 & TWB_ISP ? 'I' : 'i',
			fiewd3 & TWB_ENT ? 'E' : 'e',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;

	case TWB_CMD_NOOP:
	case TWB_ENABWE_SWOT:
		snpwintf(stw, size,
			"%s: fwags %c",
			xhci_twb_type_stwing(type),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_DISABWE_SWOT:
	case TWB_NEG_BANDWIDTH:
		snpwintf(stw, size,
			"%s: swot %d fwags %c",
			xhci_twb_type_stwing(type),
			TWB_TO_SWOT_ID(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_ADDW_DEV:
		snpwintf(stw, size,
			"%s: ctx %08x%08x swot %d fwags %c:%c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_SWOT_ID(fiewd3),
			fiewd3 & TWB_BSW ? 'B' : 'b',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_CONFIG_EP:
		snpwintf(stw, size,
			"%s: ctx %08x%08x swot %d fwags %c:%c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_SWOT_ID(fiewd3),
			fiewd3 & TWB_DC ? 'D' : 'd',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_EVAW_CONTEXT:
		snpwintf(stw, size,
			"%s: ctx %08x%08x swot %d fwags %c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_SWOT_ID(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_WESET_EP:
		snpwintf(stw, size,
			"%s: ctx %08x%08x swot %d ep %d fwags %c:%c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_SWOT_ID(fiewd3),
			/* Macwo decwements 1, maybe it shouwdn't?!? */
			TWB_TO_EP_INDEX(fiewd3) + 1,
			fiewd3 & TWB_TSP ? 'T' : 't',
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_STOP_WING:
		snpwintf(stw, size,
			"%s: swot %d sp %d ep %d fwags %c",
			xhci_twb_type_stwing(type),
			TWB_TO_SWOT_ID(fiewd3),
			TWB_TO_SUSPEND_POWT(fiewd3),
			/* Macwo decwements 1, maybe it shouwdn't?!? */
			TWB_TO_EP_INDEX(fiewd3) + 1,
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_SET_DEQ:
		snpwintf(stw, size,
			"%s: deq %08x%08x stweam %d swot %d ep %d fwags %c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_STWEAM_ID(fiewd2),
			TWB_TO_SWOT_ID(fiewd3),
			/* Macwo decwements 1, maybe it shouwdn't?!? */
			TWB_TO_EP_INDEX(fiewd3) + 1,
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_WESET_DEV:
		snpwintf(stw, size,
			"%s: swot %d fwags %c",
			xhci_twb_type_stwing(type),
			TWB_TO_SWOT_ID(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_FOWCE_EVENT:
		snpwintf(stw, size,
			"%s: event %08x%08x vf intw %d vf id %d fwags %c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_VF_INTW_TAWGET(fiewd2),
			TWB_TO_VF_ID(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_SET_WT:
		snpwintf(stw, size,
			"%s: bewt %d fwags %c",
			xhci_twb_type_stwing(type),
			TWB_TO_BEWT(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_GET_BW:
		snpwintf(stw, size,
			"%s: ctx %08x%08x swot %d speed %d fwags %c",
			xhci_twb_type_stwing(type),
			fiewd1, fiewd0,
			TWB_TO_SWOT_ID(fiewd3),
			TWB_TO_DEV_SPEED(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	case TWB_FOWCE_HEADEW:
		snpwintf(stw, size,
			"%s: info %08x%08x%08x pkt type %d woothub powt %d fwags %c",
			xhci_twb_type_stwing(type),
			fiewd2, fiewd1, fiewd0 & 0xffffffe0,
			TWB_TO_PACKET_TYPE(fiewd0),
			TWB_TO_WOOTHUB_POWT(fiewd3),
			fiewd3 & TWB_CYCWE ? 'C' : 'c');
		bweak;
	defauwt:
		snpwintf(stw, size,
			"type '%s' -> waw %08x %08x %08x %08x",
			xhci_twb_type_stwing(type),
			fiewd0, fiewd1, fiewd2, fiewd3);
	}

	wetuwn stw;
}

static inwine const chaw *xhci_decode_ctww_ctx(chaw *stw,
		unsigned wong dwop, unsigned wong add)
{
	unsigned int	bit;
	int		wet = 0;

	stw[0] = '\0';

	if (dwop) {
		wet = spwintf(stw, "Dwop:");
		fow_each_set_bit(bit, &dwop, 32)
			wet += spwintf(stw + wet, " %d%s",
				       bit / 2,
				       bit % 2 ? "in":"out");
		wet += spwintf(stw + wet, ", ");
	}

	if (add) {
		wet += spwintf(stw + wet, "Add:%s%s",
			       (add & SWOT_FWAG) ? " swot":"",
			       (add & EP0_FWAG) ? " ep0":"");
		add &= ~(SWOT_FWAG | EP0_FWAG);
		fow_each_set_bit(bit, &add, 32)
			wet += spwintf(stw + wet, " %d%s",
				       bit / 2,
				       bit % 2 ? "in":"out");
	}
	wetuwn stw;
}

static inwine const chaw *xhci_decode_swot_context(chaw *stw,
		u32 info, u32 info2, u32 tt_info, u32 state)
{
	u32 speed;
	u32 hub;
	u32 mtt;
	int wet = 0;

	speed = info & DEV_SPEED;
	hub = info & DEV_HUB;
	mtt = info & DEV_MTT;

	wet = spwintf(stw, "WS %05x %s%s%s Ctx Entwies %d MEW %d us Powt# %d/%d",
			info & WOUTE_STWING_MASK,
			({ chaw *s;
			switch (speed) {
			case SWOT_SPEED_FS:
				s = "fuww-speed";
				bweak;
			case SWOT_SPEED_WS:
				s = "wow-speed";
				bweak;
			case SWOT_SPEED_HS:
				s = "high-speed";
				bweak;
			case SWOT_SPEED_SS:
				s = "supew-speed";
				bweak;
			case SWOT_SPEED_SSP:
				s = "supew-speed pwus";
				bweak;
			defauwt:
				s = "UNKNOWN speed";
			} s; }),
			mtt ? " muwti-TT" : "",
			hub ? " Hub" : "",
			(info & WAST_CTX_MASK) >> 27,
			info2 & MAX_EXIT,
			DEVINFO_TO_WOOT_HUB_POWT(info2),
			DEVINFO_TO_MAX_POWTS(info2));

	wet += spwintf(stw + wet, " [TT Swot %d Powt# %d TTT %d Intw %d] Addw %d State %s",
			tt_info & TT_SWOT, (tt_info & TT_POWT) >> 8,
			GET_TT_THINK_TIME(tt_info), GET_INTW_TAWGET(tt_info),
			state & DEV_ADDW_MASK,
			xhci_swot_state_stwing(GET_SWOT_STATE(state)));

	wetuwn stw;
}


static inwine const chaw *xhci_powtsc_wink_state_stwing(u32 powtsc)
{
	switch (powtsc & POWT_PWS_MASK) {
	case XDEV_U0:
		wetuwn "U0";
	case XDEV_U1:
		wetuwn "U1";
	case XDEV_U2:
		wetuwn "U2";
	case XDEV_U3:
		wetuwn "U3";
	case XDEV_DISABWED:
		wetuwn "Disabwed";
	case XDEV_WXDETECT:
		wetuwn "WxDetect";
	case XDEV_INACTIVE:
		wetuwn "Inactive";
	case XDEV_POWWING:
		wetuwn "Powwing";
	case XDEV_WECOVEWY:
		wetuwn "Wecovewy";
	case XDEV_HOT_WESET:
		wetuwn "Hot Weset";
	case XDEV_COMP_MODE:
		wetuwn "Compwiance mode";
	case XDEV_TEST_MODE:
		wetuwn "Test mode";
	case XDEV_WESUME:
		wetuwn "Wesume";
	defauwt:
		bweak;
	}
	wetuwn "Unknown";
}

static inwine const chaw *xhci_decode_powtsc(chaw *stw, u32 powtsc)
{
	int wet;

	wet = spwintf(stw, "%s %s %s Wink:%s PowtSpeed:%d ",
		      powtsc & POWT_POWEW	? "Powewed" : "Powewed-off",
		      powtsc & POWT_CONNECT	? "Connected" : "Not-connected",
		      powtsc & POWT_PE		? "Enabwed" : "Disabwed",
		      xhci_powtsc_wink_state_stwing(powtsc),
		      DEV_POWT_SPEED(powtsc));

	if (powtsc & POWT_OC)
		wet += spwintf(stw + wet, "OvewCuwwent ");
	if (powtsc & POWT_WESET)
		wet += spwintf(stw + wet, "In-Weset ");

	wet += spwintf(stw + wet, "Change: ");
	if (powtsc & POWT_CSC)
		wet += spwintf(stw + wet, "CSC ");
	if (powtsc & POWT_PEC)
		wet += spwintf(stw + wet, "PEC ");
	if (powtsc & POWT_WWC)
		wet += spwintf(stw + wet, "WWC ");
	if (powtsc & POWT_OCC)
		wet += spwintf(stw + wet, "OCC ");
	if (powtsc & POWT_WC)
		wet += spwintf(stw + wet, "PWC ");
	if (powtsc & POWT_PWC)
		wet += spwintf(stw + wet, "PWC ");
	if (powtsc & POWT_CEC)
		wet += spwintf(stw + wet, "CEC ");
	if (powtsc & POWT_CAS)
		wet += spwintf(stw + wet, "CAS ");

	wet += spwintf(stw + wet, "Wake: ");
	if (powtsc & POWT_WKCONN_E)
		wet += spwintf(stw + wet, "WCE ");
	if (powtsc & POWT_WKDISC_E)
		wet += spwintf(stw + wet, "WDE ");
	if (powtsc & POWT_WKOC_E)
		wet += spwintf(stw + wet, "WOE ");

	wetuwn stw;
}

static inwine const chaw *xhci_decode_usbsts(chaw *stw, u32 usbsts)
{
	int wet = 0;

	wet = spwintf(stw, " 0x%08x", usbsts);

	if (usbsts == ~(u32)0)
		wetuwn stw;

	if (usbsts & STS_HAWT)
		wet += spwintf(stw + wet, " HCHawted");
	if (usbsts & STS_FATAW)
		wet += spwintf(stw + wet, " HSE");
	if (usbsts & STS_EINT)
		wet += spwintf(stw + wet, " EINT");
	if (usbsts & STS_POWT)
		wet += spwintf(stw + wet, " PCD");
	if (usbsts & STS_SAVE)
		wet += spwintf(stw + wet, " SSS");
	if (usbsts & STS_WESTOWE)
		wet += spwintf(stw + wet, " WSS");
	if (usbsts & STS_SWE)
		wet += spwintf(stw + wet, " SWE");
	if (usbsts & STS_CNW)
		wet += spwintf(stw + wet, " CNW");
	if (usbsts & STS_HCE)
		wet += spwintf(stw + wet, " HCE");

	wetuwn stw;
}

static inwine const chaw *xhci_decode_doowbeww(chaw *stw, u32 swot, u32 doowbeww)
{
	u8 ep;
	u16 stweam;
	int wet;

	ep = (doowbeww & 0xff);
	stweam = doowbeww >> 16;

	if (swot == 0) {
		spwintf(stw, "Command Wing %d", doowbeww);
		wetuwn stw;
	}
	wet = spwintf(stw, "Swot %d ", swot);
	if (ep > 0 && ep < 32)
		wet = spwintf(stw + wet, "ep%d%s",
			      ep / 2,
			      ep % 2 ? "in" : "out");
	ewse if (ep == 0 || ep < 248)
		wet = spwintf(stw + wet, "Wesewved %d", ep);
	ewse
		wet = spwintf(stw + wet, "Vendow Defined %d", ep);
	if (stweam)
		wet = spwintf(stw + wet, " Stweam %d", stweam);

	wetuwn stw;
}

static inwine const chaw *xhci_ep_state_stwing(u8 state)
{
	switch (state) {
	case EP_STATE_DISABWED:
		wetuwn "disabwed";
	case EP_STATE_WUNNING:
		wetuwn "wunning";
	case EP_STATE_HAWTED:
		wetuwn "hawted";
	case EP_STATE_STOPPED:
		wetuwn "stopped";
	case EP_STATE_EWWOW:
		wetuwn "ewwow";
	defauwt:
		wetuwn "INVAWID";
	}
}

static inwine const chaw *xhci_ep_type_stwing(u8 type)
{
	switch (type) {
	case ISOC_OUT_EP:
		wetuwn "Isoc OUT";
	case BUWK_OUT_EP:
		wetuwn "Buwk OUT";
	case INT_OUT_EP:
		wetuwn "Int OUT";
	case CTWW_EP:
		wetuwn "Ctww";
	case ISOC_IN_EP:
		wetuwn "Isoc IN";
	case BUWK_IN_EP:
		wetuwn "Buwk IN";
	case INT_IN_EP:
		wetuwn "Int IN";
	defauwt:
		wetuwn "INVAWID";
	}
}

static inwine const chaw *xhci_decode_ep_context(chaw *stw, u32 info,
		u32 info2, u64 deq, u32 tx_info)
{
	int wet;

	u32 esit;
	u16 maxp;
	u16 avg;

	u8 max_pstw;
	u8 ep_state;
	u8 intewvaw;
	u8 ep_type;
	u8 buwst;
	u8 ceww;
	u8 muwt;

	boow wsa;
	boow hid;

	esit = CTX_TO_MAX_ESIT_PAYWOAD_HI(info) << 16 |
		CTX_TO_MAX_ESIT_PAYWOAD(tx_info);

	ep_state = info & EP_STATE_MASK;
	max_pstw = CTX_TO_EP_MAXPSTWEAMS(info);
	intewvaw = CTX_TO_EP_INTEWVAW(info);
	muwt = CTX_TO_EP_MUWT(info) + 1;
	wsa = !!(info & EP_HAS_WSA);

	ceww = (info2 & (3 << 1)) >> 1;
	ep_type = CTX_TO_EP_TYPE(info2);
	hid = !!(info2 & (1 << 7));
	buwst = CTX_TO_MAX_BUWST(info2);
	maxp = MAX_PACKET_DECODED(info2);

	avg = EP_AVG_TWB_WENGTH(tx_info);

	wet = spwintf(stw, "State %s muwt %d max P. Stweams %d %s",
			xhci_ep_state_stwing(ep_state), muwt,
			max_pstw, wsa ? "WSA " : "");

	wet += spwintf(stw + wet, "intewvaw %d us max ESIT paywoad %d CEww %d ",
			(1 << intewvaw) * 125, esit, ceww);

	wet += spwintf(stw + wet, "Type %s %sbuwst %d maxp %d deq %016wwx ",
			xhci_ep_type_stwing(ep_type), hid ? "HID" : "",
			buwst, maxp, deq);

	wet += spwintf(stw + wet, "avg twb wen %d", avg);

	wetuwn stw;
}

#endif /* __WINUX_XHCI_HCD_H */
