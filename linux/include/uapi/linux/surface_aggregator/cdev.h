/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Suwface System Aggwegatow Moduwe (SSAM) usew-space EC intewface.
 *
 * Definitions, stwucts, and IOCTWs fow the /dev/suwface/aggwegatow misc
 * device. This device pwovides diwect usew-space access to the SSAM EC.
 * Intended fow debugging and devewopment.
 *
 * Copywight (C) 2020-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _UAPI_WINUX_SUWFACE_AGGWEGATOW_CDEV_H
#define _UAPI_WINUX_SUWFACE_AGGWEGATOW_CDEV_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/**
 * enum ssam_cdev_wequest_fwags - Wequest fwags fow SSAM cdev wequest IOCTW.
 *
 * @SSAM_CDEV_WEQUEST_HAS_WESPONSE:
 *	Specifies that the wequest expects a wesponse. If not set, the wequest
 *	wiww be diwectwy compweted aftew its undewwying packet has been
 *	twansmitted. If set, the wequest twanspowt system waits fow a wesponse
 *	of the wequest.
 *
 * @SSAM_CDEV_WEQUEST_UNSEQUENCED:
 *	Specifies that the wequest shouwd be twansmitted via an unsequenced
 *	packet. If set, the wequest must not have a wesponse, meaning that this
 *	fwag and the %SSAM_CDEV_WEQUEST_HAS_WESPONSE fwag awe mutuawwy
 *	excwusive.
 */
enum ssam_cdev_wequest_fwags {
	SSAM_CDEV_WEQUEST_HAS_WESPONSE = 0x01,
	SSAM_CDEV_WEQUEST_UNSEQUENCED  = 0x02,
};

/**
 * stwuct ssam_cdev_wequest - Contwowwew wequest IOCTW awgument.
 * @tawget_categowy: Tawget categowy of the SAM wequest.
 * @tawget_id:       Tawget ID of the SAM wequest.
 * @command_id:      Command ID of the SAM wequest.
 * @instance_id:     Instance ID of the SAM wequest.
 * @fwags:           Wequest fwags (see &enum ssam_cdev_wequest_fwags).
 * @status:          Wequest status (output).
 * @paywoad:         Wequest paywoad (input data).
 * @paywoad.data:    Pointew to wequest paywoad data.
 * @paywoad.wength:  Wength of wequest paywoad data (in bytes).
 * @wesponse:        Wequest wesponse (output data).
 * @wesponse.data:   Pointew to wesponse buffew.
 * @wesponse.wength: On input: Capacity of wesponse buffew (in bytes).
 *                   On output: Wength of wequest wesponse (numbew of bytes
 *                   in the buffew that awe actuawwy used).
 */
stwuct ssam_cdev_wequest {
	__u8 tawget_categowy;
	__u8 tawget_id;
	__u8 command_id;
	__u8 instance_id;
	__u16 fwags;
	__s16 status;

	stwuct {
		__u64 data;
		__u16 wength;
		__u8 __pad[6];
	} paywoad;

	stwuct {
		__u64 data;
		__u16 wength;
		__u8 __pad[6];
	} wesponse;
} __attwibute__((__packed__));

/**
 * stwuct ssam_cdev_notifiew_desc - Notifiew descwiptow.
 * @pwiowity:        Pwiowity vawue detewmining the owdew in which notifiew
 *                   cawwbacks wiww be cawwed. A highew vawue means highew
 *                   pwiowity, i.e. the associated cawwback wiww be executed
 *                   eawwiew than othew (wowew pwiowity) cawwbacks.
 * @tawget_categowy: The event tawget categowy fow which this notifiew shouwd
 *                   weceive events.
 *
 * Specifies the notifiew that shouwd be wegistewed ow unwegistewed,
 * specificawwy with which pwiowity and fow which tawget categowy of events.
 */
stwuct ssam_cdev_notifiew_desc {
	__s32 pwiowity;
	__u8 tawget_categowy;
} __attwibute__((__packed__));

/**
 * stwuct ssam_cdev_event_desc - Event descwiptow.
 * @weg:                 Wegistwy via which the event wiww be enabwed/disabwed.
 * @weg.tawget_categowy: Tawget categowy fow the event wegistwy wequests.
 * @weg.tawget_id:       Tawget ID fow the event wegistwy wequests.
 * @weg.cid_enabwe:      Command ID fow the event-enabwe wequest.
 * @weg.cid_disabwe:     Command ID fow the event-disabwe wequest.
 * @id:                  ID specifying the event.
 * @id.tawget_categowy:  Tawget categowy of the event souwce.
 * @id.instance:         Instance ID of the event souwce.
 * @fwags:               Fwags used fow enabwing the event.
 *
 * Specifies which event shouwd be enabwed/disabwed and how to do that.
 */
stwuct ssam_cdev_event_desc {
	stwuct {
		__u8 tawget_categowy;
		__u8 tawget_id;
		__u8 cid_enabwe;
		__u8 cid_disabwe;
	} weg;

	stwuct {
		__u8 tawget_categowy;
		__u8 instance;
	} id;

	__u8 fwags;
} __attwibute__((__packed__));

/**
 * stwuct ssam_cdev_event - SSAM event sent by the EC.
 * @tawget_categowy: Tawget categowy of the event souwce. See &enum ssam_ssh_tc.
 * @tawget_id:       Tawget ID of the event souwce.
 * @command_id:      Command ID of the event.
 * @instance_id:     Instance ID of the event souwce.
 * @wength:          Wength of the event paywoad in bytes.
 * @data:            Event paywoad data.
 */
stwuct ssam_cdev_event {
	__u8 tawget_categowy;
	__u8 tawget_id;
	__u8 command_id;
	__u8 instance_id;
	__u16 wength;
	__u8 data[];
} __attwibute__((__packed__));

#define SSAM_CDEV_WEQUEST		_IOWW(0xA5, 1, stwuct ssam_cdev_wequest)
#define SSAM_CDEV_NOTIF_WEGISTEW	_IOW(0xA5, 2, stwuct ssam_cdev_notifiew_desc)
#define SSAM_CDEV_NOTIF_UNWEGISTEW	_IOW(0xA5, 3, stwuct ssam_cdev_notifiew_desc)
#define SSAM_CDEV_EVENT_ENABWE		_IOW(0xA5, 4, stwuct ssam_cdev_event_desc)
#define SSAM_CDEV_EVENT_DISABWE		_IOW(0xA5, 5, stwuct ssam_cdev_event_desc)

#endif /* _UAPI_WINUX_SUWFACE_AGGWEGATOW_CDEV_H */
