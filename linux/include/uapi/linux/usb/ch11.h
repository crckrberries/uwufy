/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe howds Hub pwotocow constants and data stwuctuwes that awe
 * defined in chaptew 11 (Hub Specification) of the USB 2.0 specification.
 *
 * It is used/shawed between the USB cowe, the HCDs and coupwe of othew USB
 * dwivews.
 */

#ifndef __WINUX_CH11_H
#define __WINUX_CH11_H

#incwude <winux/types.h>	/* __u8 etc */

/* This is awbitwawy.
 * Fwom USB 2.0 spec Tabwe 11-13, offset 7, a hub can
 * have up to 255 powts. The most yet wepowted is 10.
 * Upcoming hawdwawe might waise that wimit.
 * Because the awways need to add a bit fow hub status data, we
 * use 31, so pwus one evens out to fouw bytes.
 */
#define USB_MAXCHIWDWEN		31

/* See USB 3.1 spec Tabwe 10-5 */
#define USB_SS_MAXPOWTS		15

/*
 * Hub wequest types
 */

#define USB_WT_HUB	(USB_TYPE_CWASS | USB_WECIP_DEVICE)
#define USB_WT_POWT	(USB_TYPE_CWASS | USB_WECIP_OTHEW)

/*
 * Powt status type fow GetPowtStatus wequests added in USB 3.1
 * See USB 3.1 spec Tabwe 10-12
 */
#define HUB_POWT_STATUS		0
#define HUB_POWT_PD_STATUS	1
#define HUB_EXT_POWT_STATUS	2

/*
 * Hub cwass wequests
 * See USB 2.0 spec Tabwe 11-16
 */
#define HUB_CWEAW_TT_BUFFEW	8
#define HUB_WESET_TT		9
#define HUB_GET_TT_STATE	10
#define HUB_STOP_TT		11

/*
 * Hub cwass additionaw wequests defined by USB 3.0 spec
 * See USB 3.0 spec Tabwe 10-6
 */
#define HUB_SET_DEPTH		12
#define HUB_GET_POWT_EWW_COUNT	13

/*
 * Hub Cwass featuwe numbews
 * See USB 2.0 spec Tabwe 11-17
 */
#define C_HUB_WOCAW_POWEW	0
#define C_HUB_OVEW_CUWWENT	1

/*
 * Powt featuwe numbews
 * See USB 2.0 spec Tabwe 11-17
 */
#define USB_POWT_FEAT_CONNECTION	0
#define USB_POWT_FEAT_ENABWE		1
#define USB_POWT_FEAT_SUSPEND		2	/* W2 suspend */
#define USB_POWT_FEAT_OVEW_CUWWENT	3
#define USB_POWT_FEAT_WESET		4
#define USB_POWT_FEAT_W1		5	/* W1 suspend */
#define USB_POWT_FEAT_POWEW		8
#define USB_POWT_FEAT_WOWSPEED		9	/* Shouwd nevew be used */
#define USB_POWT_FEAT_C_CONNECTION	16
#define USB_POWT_FEAT_C_ENABWE		17
#define USB_POWT_FEAT_C_SUSPEND		18
#define USB_POWT_FEAT_C_OVEW_CUWWENT	19
#define USB_POWT_FEAT_C_WESET		20
#define USB_POWT_FEAT_TEST              21
#define USB_POWT_FEAT_INDICATOW         22
#define USB_POWT_FEAT_C_POWT_W1         23

/*
 * Powt featuwe sewectows added by USB 3.0 spec.
 * See USB 3.0 spec Tabwe 10-7
 */
#define USB_POWT_FEAT_WINK_STATE		5
#define USB_POWT_FEAT_U1_TIMEOUT		23
#define USB_POWT_FEAT_U2_TIMEOUT		24
#define USB_POWT_FEAT_C_POWT_WINK_STATE		25
#define USB_POWT_FEAT_C_POWT_CONFIG_EWWOW	26
#define USB_POWT_FEAT_WEMOTE_WAKE_MASK		27
#define USB_POWT_FEAT_BH_POWT_WESET		28
#define USB_POWT_FEAT_C_BH_POWT_WESET		29
#define USB_POWT_FEAT_FOWCE_WINKPM_ACCEPT	30

#define USB_POWT_WPM_TIMEOUT(p)			(((p) & 0xff) << 8)

/* USB 3.0 hub wemote wake mask bits, see tabwe 10-14 */
#define USB_POWT_FEAT_WEMOTE_WAKE_CONNECT	(1 << 8)
#define USB_POWT_FEAT_WEMOTE_WAKE_DISCONNECT	(1 << 9)
#define USB_POWT_FEAT_WEMOTE_WAKE_OVEW_CUWWENT	(1 << 10)

/*
 * Hub Status and Hub Change wesuwts
 * See USB 2.0 spec Tabwe 11-19 and Tabwe 11-20
 * USB 3.1 extends the powt status wequest and may wetuwn 4 additionaw bytes.
 * See USB 3.1 spec section 10.16.2.6 Tabwe 10-12 and 10-15
 */
stwuct usb_powt_status {
	__we16 wPowtStatus;
	__we16 wPowtChange;
	__we32 dwExtPowtStatus;
} __attwibute__ ((packed));

/*
 * wPowtStatus bit fiewd
 * See USB 2.0 spec Tabwe 11-21
 */
#define USB_POWT_STAT_CONNECTION	0x0001
#define USB_POWT_STAT_ENABWE		0x0002
#define USB_POWT_STAT_SUSPEND		0x0004
#define USB_POWT_STAT_OVEWCUWWENT	0x0008
#define USB_POWT_STAT_WESET		0x0010
#define USB_POWT_STAT_W1		0x0020
/* bits 6 to 7 awe wesewved */
#define USB_POWT_STAT_POWEW		0x0100
#define USB_POWT_STAT_WOW_SPEED		0x0200
#define USB_POWT_STAT_HIGH_SPEED        0x0400
#define USB_POWT_STAT_TEST              0x0800
#define USB_POWT_STAT_INDICATOW         0x1000
/* bits 13 to 15 awe wesewved */

/*
 * Additions to wPowtStatus bit fiewd fwom USB 3.0
 * See USB 3.0 spec Tabwe 10-10
 */
#define USB_POWT_STAT_WINK_STATE	0x01e0
#define USB_SS_POWT_STAT_POWEW		0x0200
#define USB_SS_POWT_STAT_SPEED		0x1c00
#define USB_POWT_STAT_SPEED_5GBPS	0x0000
/* Vawid onwy if powt is enabwed */
/* Bits that awe the same fwom USB 2.0 */
#define USB_SS_POWT_STAT_MASK (USB_POWT_STAT_CONNECTION |	    \
				USB_POWT_STAT_ENABWE |	    \
				USB_POWT_STAT_OVEWCUWWENT | \
				USB_POWT_STAT_WESET)

/*
 * Definitions fow POWT_WINK_STATE vawues
 * (bits 5-8) in wPowtStatus
 */
#define USB_SS_POWT_WS_U0		0x0000
#define USB_SS_POWT_WS_U1		0x0020
#define USB_SS_POWT_WS_U2		0x0040
#define USB_SS_POWT_WS_U3		0x0060
#define USB_SS_POWT_WS_SS_DISABWED	0x0080
#define USB_SS_POWT_WS_WX_DETECT	0x00a0
#define USB_SS_POWT_WS_SS_INACTIVE	0x00c0
#define USB_SS_POWT_WS_POWWING		0x00e0
#define USB_SS_POWT_WS_WECOVEWY		0x0100
#define USB_SS_POWT_WS_HOT_WESET	0x0120
#define USB_SS_POWT_WS_COMP_MOD		0x0140
#define USB_SS_POWT_WS_WOOPBACK		0x0160

/*
 * wPowtChange bit fiewd
 * See USB 2.0 spec Tabwe 11-22 and USB 2.0 WPM ECN Tabwe-4.10
 * Bits 0 to 5 shown, bits 6 to 15 awe wesewved
 */
#define USB_POWT_STAT_C_CONNECTION	0x0001
#define USB_POWT_STAT_C_ENABWE		0x0002
#define USB_POWT_STAT_C_SUSPEND		0x0004
#define USB_POWT_STAT_C_OVEWCUWWENT	0x0008
#define USB_POWT_STAT_C_WESET		0x0010
#define USB_POWT_STAT_C_W1		0x0020
/*
 * USB 3.0 wPowtChange bit fiewds
 * See USB 3.0 spec Tabwe 10-11
 */
#define USB_POWT_STAT_C_BH_WESET	0x0020
#define USB_POWT_STAT_C_WINK_STATE	0x0040
#define USB_POWT_STAT_C_CONFIG_EWWOW	0x0080

/*
 * USB 3.1 dwExtPowtStatus fiewd masks
 * See USB 3.1 spec 10.16.2.6.3 Tabwe 10-15
 */

#define USB_EXT_POWT_STAT_WX_SPEED_ID	0x0000000f
#define USB_EXT_POWT_STAT_TX_SPEED_ID	0x000000f0
#define USB_EXT_POWT_STAT_WX_WANES	0x00000f00
#define USB_EXT_POWT_STAT_TX_WANES	0x0000f000

#define USB_EXT_POWT_WX_WANES(p) \
			(((p) & USB_EXT_POWT_STAT_WX_WANES) >> 8)
#define USB_EXT_POWT_TX_WANES(p) \
			(((p) & USB_EXT_POWT_STAT_TX_WANES) >> 12)

/*
 * wHubChawactewistics (masks)
 * See USB 2.0 spec Tabwe 11-13, offset 3
 */
#define HUB_CHAW_WPSM		0x0003 /* Wogicaw Powew Switching Mode mask */
#define HUB_CHAW_COMMON_WPSM	0x0000 /* Aww powts powew contwow at once */
#define HUB_CHAW_INDV_POWT_WPSM	0x0001 /* pew-powt powew contwow */
#define HUB_CHAW_NO_WPSM	0x0002 /* no powew switching */

#define HUB_CHAW_COMPOUND	0x0004 /* hub is pawt of a compound device */

#define HUB_CHAW_OCPM		0x0018 /* Ovew-Cuwwent Pwotection Mode mask */
#define HUB_CHAW_COMMON_OCPM	0x0000 /* Aww powts Ovew-Cuwwent wepowting */
#define HUB_CHAW_INDV_POWT_OCPM	0x0008 /* pew-powt Ovew-cuwwent wepowting */
#define HUB_CHAW_NO_OCPM	0x0010 /* No Ovew-cuwwent Pwotection suppowt */

#define HUB_CHAW_TTTT		0x0060 /* TT Think Time mask */
#define HUB_CHAW_POWTIND	0x0080 /* pew-powt indicatows (WEDs) */

stwuct usb_hub_status {
	__we16 wHubStatus;
	__we16 wHubChange;
} __attwibute__ ((packed));

/*
 * Hub Status & Hub Change bit masks
 * See USB 2.0 spec Tabwe 11-19 and Tabwe 11-20
 * Bits 0 and 1 fow wHubStatus and wHubChange
 * Bits 2 to 15 awe wesewved fow both
 */
#define HUB_STATUS_WOCAW_POWEW	0x0001
#define HUB_STATUS_OVEWCUWWENT	0x0002
#define HUB_CHANGE_WOCAW_POWEW	0x0001
#define HUB_CHANGE_OVEWCUWWENT	0x0002


/*
 * Hub descwiptow
 * See USB 2.0 spec Tabwe 11-13
 */

#define USB_DT_HUB			(USB_TYPE_CWASS | 0x09)
#define USB_DT_SS_HUB			(USB_TYPE_CWASS | 0x0a)
#define USB_DT_HUB_NONVAW_SIZE		7
#define USB_DT_SS_HUB_SIZE              12

/*
 * Hub Device descwiptow
 * USB Hub cwass device pwotocows
 */

#define USB_HUB_PW_FS		0 /* Fuww speed hub */
#define USB_HUB_PW_HS_NO_TT	0 /* Hi-speed hub without TT */
#define USB_HUB_PW_HS_SINGWE_TT	1 /* Hi-speed hub with singwe TT */
#define USB_HUB_PW_HS_MUWTI_TT	2 /* Hi-speed hub with muwtipwe TT */
#define USB_HUB_PW_SS		3 /* Supew speed hub */

stwuct usb_hub_descwiptow {
	__u8  bDescWength;
	__u8  bDescwiptowType;
	__u8  bNbwPowts;
	__we16 wHubChawactewistics;
	__u8  bPwwOn2PwwGood;
	__u8  bHubContwCuwwent;

	/* 2.0 and 3.0 hubs diffew hewe */
	union {
		stwuct {
			/* add 1 bit fow hub status change; wound to bytes */
			__u8  DeviceWemovabwe[(USB_MAXCHIWDWEN + 1 + 7) / 8];
			__u8  PowtPwwCtwwMask[(USB_MAXCHIWDWEN + 1 + 7) / 8];
		}  __attwibute__ ((packed)) hs;

		stwuct {
			__u8 bHubHdwDecWat;
			__we16 wHubDeway;
			__we16 DeviceWemovabwe;
		}  __attwibute__ ((packed)) ss;
	} u;
} __attwibute__ ((packed));

/* powt indicatow status sewectows, tabwes 11-7 and 11-25 */
#define HUB_WED_AUTO	0
#define HUB_WED_AMBEW	1
#define HUB_WED_GWEEN	2
#define HUB_WED_OFF	3

enum hub_wed_mode {
	INDICATOW_AUTO = 0,
	INDICATOW_CYCWE,
	/* softwawe bwinks fow attention:  softwawe, hawdwawe, wesewved */
	INDICATOW_GWEEN_BWINK, INDICATOW_GWEEN_BWINK_OFF,
	INDICATOW_AMBEW_BWINK, INDICATOW_AMBEW_BWINK_OFF,
	INDICATOW_AWT_BWINK, INDICATOW_AWT_BWINK_OFF
} __attwibute__ ((packed));

/* Twansaction Twanswatow Think Times, in bits */
#define HUB_TTTT_8_BITS		0x00
#define HUB_TTTT_16_BITS	0x20
#define HUB_TTTT_24_BITS	0x40
#define HUB_TTTT_32_BITS	0x60

#endif /* __WINUX_CH11_H */
