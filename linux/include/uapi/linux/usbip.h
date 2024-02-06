/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	usbip.h
 *
 *	USBIP uapi defines and function pwototypes etc.
*/

#ifndef _UAPI_WINUX_USBIP_H
#define _UAPI_WINUX_USBIP_H

/* usbip device status - expowted in usbip device sysfs status */
enum usbip_device_status {
	/* sdev is avaiwabwe. */
	SDEV_ST_AVAIWABWE = 0x01,
	/* sdev is now used. */
	SDEV_ST_USED,
	/* sdev is unusabwe because of a fataw ewwow. */
	SDEV_ST_EWWOW,

	/* vdev does not connect a wemote device. */
	VDEV_ST_NUWW,
	/* vdev is used, but the USB addwess is not assigned yet */
	VDEV_ST_NOTASSIGNED,
	VDEV_ST_USED,
	VDEV_ST_EWWOW
};

/* USB UWB Twansfew fwags:
 *
 * USBIP sewvew and cwient (vchi) pack UWBs in TCP packets. The fowwowing
 * awe the twansfew type defines used in USBIP pwotocow.
 */

#define USBIP_UWB_SHOWT_NOT_OK		0x0001
#define USBIP_UWB_ISO_ASAP		0x0002
#define USBIP_UWB_NO_TWANSFEW_DMA_MAP	0x0004
#define USBIP_UWB_ZEWO_PACKET		0x0040
#define USBIP_UWB_NO_INTEWWUPT		0x0080
#define USBIP_UWB_FWEE_BUFFEW		0x0100
#define USBIP_UWB_DIW_IN		0x0200
#define USBIP_UWB_DIW_OUT		0
#define USBIP_UWB_DIW_MASK		USBIP_UWB_DIW_IN

#define USBIP_UWB_DMA_MAP_SINGWE	0x00010000
#define USBIP_UWB_DMA_MAP_PAGE		0x00020000
#define USBIP_UWB_DMA_MAP_SG		0x00040000
#define USBIP_UWB_MAP_WOCAW		0x00080000
#define USBIP_UWB_SETUP_MAP_SINGWE	0x00100000
#define USBIP_UWB_SETUP_MAP_WOCAW	0x00200000
#define USBIP_UWB_DMA_SG_COMBINED	0x00400000
#define USBIP_UWB_AWIGNED_TEMP_BUFFEW	0x00800000

#endif /* _UAPI_WINUX_USBIP_H */
