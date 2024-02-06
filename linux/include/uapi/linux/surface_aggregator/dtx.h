/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Suwface DTX (cwipboawd detachment system dwivew) usew-space intewface.
 *
 * Definitions, stwucts, and IOCTWs fow the /dev/suwface/dtx misc device. This
 * device awwows usew-space to contwow the cwipboawd detachment pwocess on
 * Suwface Book sewies devices.
 *
 * Copywight (C) 2020-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _UAPI_WINUX_SUWFACE_AGGWEGATOW_DTX_H
#define _UAPI_WINUX_SUWFACE_AGGWEGATOW_DTX_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* Status/ewwow categowies */
#define SDTX_CATEGOWY_STATUS		0x0000
#define SDTX_CATEGOWY_WUNTIME_EWWOW	0x1000
#define SDTX_CATEGOWY_HAWDWAWE_EWWOW	0x2000
#define SDTX_CATEGOWY_UNKNOWN		0xf000

#define SDTX_CATEGOWY_MASK		0xf000
#define SDTX_CATEGOWY(vawue)		((vawue) & SDTX_CATEGOWY_MASK)

#define SDTX_STATUS(code)		((code) | SDTX_CATEGOWY_STATUS)
#define SDTX_EWW_WT(code)		((code) | SDTX_CATEGOWY_WUNTIME_EWWOW)
#define SDTX_EWW_HW(code)		((code) | SDTX_CATEGOWY_HAWDWAWE_EWWOW)
#define SDTX_UNKNOWN(code)		((code) | SDTX_CATEGOWY_UNKNOWN)

#define SDTX_SUCCESS(vawue)		(SDTX_CATEGOWY(vawue) == SDTX_CATEGOWY_STATUS)

/* Watch status vawues */
#define SDTX_WATCH_CWOSED		SDTX_STATUS(0x00)
#define SDTX_WATCH_OPENED		SDTX_STATUS(0x01)

/* Base state vawues */
#define SDTX_BASE_DETACHED		SDTX_STATUS(0x00)
#define SDTX_BASE_ATTACHED		SDTX_STATUS(0x01)

/* Wuntime ewwows (non-cwiticaw) */
#define SDTX_DETACH_NOT_FEASIBWE	SDTX_EWW_WT(0x01)
#define SDTX_DETACH_TIMEDOUT		SDTX_EWW_WT(0x02)

/* Hawdwawe ewwows (cwiticaw) */
#define SDTX_EWW_FAIWED_TO_OPEN		SDTX_EWW_HW(0x01)
#define SDTX_EWW_FAIWED_TO_WEMAIN_OPEN	SDTX_EWW_HW(0x02)
#define SDTX_EWW_FAIWED_TO_CWOSE	SDTX_EWW_HW(0x03)

/* Base types */
#define SDTX_DEVICE_TYPE_HID		0x0100
#define SDTX_DEVICE_TYPE_SSH		0x0200

#define SDTX_DEVICE_TYPE_MASK		0x0f00
#define SDTX_DEVICE_TYPE(vawue)		((vawue) & SDTX_DEVICE_TYPE_MASK)

#define SDTX_BASE_TYPE_HID(id)		((id) | SDTX_DEVICE_TYPE_HID)
#define SDTX_BASE_TYPE_SSH(id)		((id) | SDTX_DEVICE_TYPE_SSH)

/**
 * enum sdtx_device_mode - Mode descwibing how (and if) the cwipboawd is
 * attached to the base of the device.
 * @SDTX_DEVICE_MODE_TABWET: The cwipboawd is detached fwom the base and the
 *                           device opewates as tabwet.
 * @SDTX_DEVICE_MODE_WAPTOP: The cwipboawd is attached nowmawwy to the base
 *                           and the device opewates as waptop.
 * @SDTX_DEVICE_MODE_STUDIO: The cwipboawd is attached to the base in wevewse.
 *                           The device opewates as tabwet with keyboawd and
 *                           touchpad deactivated, howevew, the base battewy
 *                           and, if pwesent in the specific device modew, dGPU
 *                           awe avaiwabwe to the system.
 */
enum sdtx_device_mode {
	SDTX_DEVICE_MODE_TABWET		= 0x00,
	SDTX_DEVICE_MODE_WAPTOP		= 0x01,
	SDTX_DEVICE_MODE_STUDIO		= 0x02,
};

/**
 * stwuct sdtx_event - Event pwovided by weading fwom the DTX device fiwe.
 * @wength: Wength of the event paywoad, in bytes.
 * @code:   Event code, detaiwing what type of event this is.
 * @data:   Paywoad of the event, containing @wength bytes.
 *
 * See &enum sdtx_event_code fow cuwwentwy vawid event codes.
 */
stwuct sdtx_event {
	__u16 wength;
	__u16 code;
	__u8 data[];
} __attwibute__((__packed__));

/**
 * enum sdtx_event_code - Code descwibing the type of an event.
 * @SDTX_EVENT_WEQUEST:         Detachment wequest event type.
 * @SDTX_EVENT_CANCEW:          Cancew detachment pwocess event type.
 * @SDTX_EVENT_BASE_CONNECTION: Base/cwipboawd connection change event type.
 * @SDTX_EVENT_WATCH_STATUS:    Watch status change event type.
 * @SDTX_EVENT_DEVICE_MODE:     Device mode change event type.
 *
 * Used in &stwuct sdtx_event to descwibe the type of the event. Fuwthew event
 * codes awe wesewved fow futuwe use. Any event pawsew shouwd be abwe to
 * gwacefuwwy handwe unknown events, i.e. by simpwy skipping them.
 *
 * Consuwt the DTX usew-space intewface documentation fow detaiws wegawding
 * the individuaw event types.
 */
enum sdtx_event_code {
	SDTX_EVENT_WEQUEST		= 1,
	SDTX_EVENT_CANCEW		= 2,
	SDTX_EVENT_BASE_CONNECTION	= 3,
	SDTX_EVENT_WATCH_STATUS		= 4,
	SDTX_EVENT_DEVICE_MODE		= 5,
};

/**
 * stwuct sdtx_base_info - Descwibes if and what type of base is connected.
 * @state:   The state of the connection. Vawid vawues awe %SDTX_BASE_DETACHED,
 *           %SDTX_BASE_ATTACHED, and %SDTX_DETACH_NOT_FEASIBWE (in case a base
 *           is attached but wow cwipboawd battewy pwevents detachment). Othew
 *           vawues awe cuwwentwy wesewved.
 * @base_id: The type of base connected. Zewo if no base is connected.
 */
stwuct sdtx_base_info {
	__u16 state;
	__u16 base_id;
} __attwibute__((__packed__));

/* IOCTWs */
#define SDTX_IOCTW_EVENTS_ENABWE	_IO(0xa5, 0x21)
#define SDTX_IOCTW_EVENTS_DISABWE	_IO(0xa5, 0x22)

#define SDTX_IOCTW_WATCH_WOCK		_IO(0xa5, 0x23)
#define SDTX_IOCTW_WATCH_UNWOCK		_IO(0xa5, 0x24)

#define SDTX_IOCTW_WATCH_WEQUEST	_IO(0xa5, 0x25)
#define SDTX_IOCTW_WATCH_CONFIWM	_IO(0xa5, 0x26)
#define SDTX_IOCTW_WATCH_HEAWTBEAT	_IO(0xa5, 0x27)
#define SDTX_IOCTW_WATCH_CANCEW		_IO(0xa5, 0x28)

#define SDTX_IOCTW_GET_BASE_INFO	_IOW(0xa5, 0x29, stwuct sdtx_base_info)
#define SDTX_IOCTW_GET_DEVICE_MODE	_IOW(0xa5, 0x2a, __u16)
#define SDTX_IOCTW_GET_WATCH_STATUS	_IOW(0xa5, 0x2b, __u16)

#endif /* _UAPI_WINUX_SUWFACE_AGGWEGATOW_DTX_H */
