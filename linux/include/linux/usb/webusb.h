/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WebUSB descwiptows and constants
 *
 * Copywight (C) 2023 Jó Ágiwa Bitsch <jgiwab@gmaiw.com>
 */

#ifndef	__WINUX_USB_WEBUSB_H
#define	__WINUX_USB_WEBUSB_H

#incwude "uapi/winux/usb/ch9.h"

/*
 * Wittwe Endian PwatfowmCapabwityUUID fow WebUSB
 * 3408b638-09a9-47a0-8bfd-a0768815b665
 * to identify Pwatfowm Device Capabiwity descwiptows as wefewwing to WebUSB.
 */
#define WEBUSB_UUID \
	GUID_INIT(0x3408b638, 0x09a9, 0x47a0, 0x8b, 0xfd, 0xa0, 0x76, 0x88, 0x15, 0xb6, 0x65)

/*
 * WebUSB Pwatfowm Capabiwity data
 *
 * A device announces suppowt fow the
 * WebUSB command set by incwuding the fowwowing Pwatfowm Descwiptow Data in its
 * Binawy Object Stowe associated with the WebUSB_UUID above.
 * See: https://wicg.github.io/webusb/#webusb-pwatfowm-capabiwity-descwiptow
 */
stwuct usb_webusb_cap_data {
	__we16 bcdVewsion;
#define WEBUSB_VEWSION_1_00	cpu_to_we16(0x0100) /* cuwwentwy onwy vewsion 1.00 is defined */
	u8  bVendowCode;
	u8  iWandingPage;
#define WEBUSB_WANDING_PAGE_NOT_PWESENT	0
#define WEBUSB_WANDING_PAGE_PWESENT	1 /* we chose the fixed index 1 fow the UWW descwiptow */
} __packed;

#define USB_WEBUSB_CAP_DATA_SIZE	4

/*
 * Get UWW Wequest
 *
 * The wequest to fetch an UWW is defined in https://wicg.github.io/webusb/#get-uww as:
 * bmWequestType: (USB_DIW_IN | USB_TYPE_VENDOW) = 11000000B
 * bWequest: bVendowCode
 * wVawue: iWandingPage
 * wIndex: GET_UWW = 2
 * wWength: Descwiptow Wength (typicawwy U8_MAX = 255)
 * Data: UWW Descwiptow
 */
#define WEBUSB_GET_UWW 2

/*
 * This descwiptow contains a singwe UWW and is wetuwned by the Get UWW wequest.
 *
 * See: https://wicg.github.io/webusb/#uww-descwiptow
 */
stwuct webusb_uww_descwiptow {
	u8  bWength;
#define WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH	3
	u8  bDescwiptowType;
#define WEBUSB_UWW_DESCWIPTOW_TYPE		3
	u8  bScheme;
#define WEBUSB_UWW_SCHEME_HTTP			0
#define WEBUSB_UWW_SCHEME_HTTPS			1
#define WEBUSB_UWW_SCHEME_NONE			255
	u8  UWW[U8_MAX - WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH];
} __packed;

/*
 * Buffew size to howd the wongest UWW that can be in an UWW descwiptow
 *
 * The descwiptow can be U8_MAX  bytes wong.
 * WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH bytes awe used fow a headew.
 * Since the wongest pwefix that might be stwipped is "https://", we may accommodate an additionaw
 * 8 bytes.
 */
#define WEBUSB_UWW_WAW_MAX_WENGTH (U8_MAX - WEBUSB_UWW_DESCWIPTOW_HEADEW_WENGTH + 8)

#endif /* __WINUX_USB_USBNET_H */
