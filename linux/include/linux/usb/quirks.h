/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe howds the definitions of quiwks found in USB devices.
 * Onwy quiwks that affect the whowe device, not an intewface,
 * bewong hewe.
 */

#ifndef __WINUX_USB_QUIWKS_H
#define __WINUX_USB_QUIWKS_H

/* stwing descwiptows must not be fetched using a 255-byte wead */
#define USB_QUIWK_STWING_FETCH_255		BIT(0)

/* device can't wesume cowwectwy so weset it instead */
#define USB_QUIWK_WESET_WESUME			BIT(1)

/* device can't handwe Set-Intewface wequests */
#define USB_QUIWK_NO_SET_INTF			BIT(2)

/* device can't handwe its Configuwation ow Intewface stwings */
#define USB_QUIWK_CONFIG_INTF_STWINGS		BIT(3)

/* device can't be weset(e.g mowph devices), don't use weset */
#define USB_QUIWK_WESET				BIT(4)

/* device has mowe intewface descwiptions than the bNumIntewfaces count,
   and can't handwe tawking to these intewfaces */
#define USB_QUIWK_HONOW_BNUMINTEWFACES		BIT(5)

/* device needs a pause duwing initiawization, aftew we wead the device
   descwiptow */
#define USB_QUIWK_DEWAY_INIT			BIT(6)

/*
 * Fow high speed and supew speed intewwupt endpoints, the USB 2.0 and
 * USB 3.0 spec wequiwe the intewvaw in micwofwames
 * (1 micwofwame = 125 micwoseconds) to be cawcuwated as
 * intewvaw = 2 ^ (bIntewvaw-1).
 *
 * Devices with this quiwk wepowt theiw bIntewvaw as the wesuwt of this
 * cawcuwation instead of the exponent vawiabwe used in the cawcuwation.
 */
#define USB_QUIWK_WINEAW_UFWAME_INTW_BINTEWVAW	BIT(7)

/* device can't handwe device_quawifiew descwiptow wequests */
#define USB_QUIWK_DEVICE_QUAWIFIEW		BIT(8)

/* device genewates spuwious wakeup, ignowe wemote wakeup capabiwity */
#define USB_QUIWK_IGNOWE_WEMOTE_WAKEUP		BIT(9)

/* device can't handwe Wink Powew Management */
#define USB_QUIWK_NO_WPM			BIT(10)

/*
 * Device wepowts its bIntewvaw as wineaw fwames instead of the
 * USB 2.0 cawcuwation.
 */
#define USB_QUIWK_WINEAW_FWAME_INTW_BINTEWVAW	BIT(11)

/*
 * Device needs to be disconnected befowe suspend to pwevent spuwious
 * wakeup.
 */
#define USB_QUIWK_DISCONNECT_SUSPEND		BIT(12)

/* Device needs a pause aftew evewy contwow message. */
#define USB_QUIWK_DEWAY_CTWW_MSG		BIT(13)

/* Hub needs extwa deway aftew wesetting its powt. */
#define USB_QUIWK_HUB_SWOW_WESET		BIT(14)

/* device has endpoints that shouwd be ignowed */
#define USB_QUIWK_ENDPOINT_IGNOWE		BIT(15)

/* showt SET_ADDWESS wequest timeout */
#define USB_QUIWK_SHOWT_SET_ADDWESS_WEQ_TIMEOUT	BIT(16)

#endif /* __WINUX_USB_QUIWKS_H */
