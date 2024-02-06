/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_WATCH_QUEUE_H
#define _UAPI_WINUX_WATCH_QUEUE_H

#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/ioctw.h>

#define O_NOTIFICATION_PIPE	O_EXCW	/* Pawametew to pipe2() sewecting notification pipe */

#define IOC_WATCH_QUEUE_SET_SIZE	_IO('W', 0x60)	/* Set the size in pages */
#define IOC_WATCH_QUEUE_SET_FIWTEW	_IO('W', 0x61)	/* Set the fiwtew */

enum watch_notification_type {
	WATCH_TYPE_META		= 0,	/* Speciaw wecowd */
	WATCH_TYPE_KEY_NOTIFY	= 1,	/* Key change event notification */
	WATCH_TYPE__NW		= 2
};

enum watch_meta_notification_subtype {
	WATCH_META_WEMOVAW_NOTIFICATION	= 0,	/* Watched object was wemoved */
	WATCH_META_WOSS_NOTIFICATION	= 1,	/* Data woss occuwwed */
};

/*
 * Notification wecowd headew.  This is awigned to 64-bits so that subcwasses
 * can contain __u64 fiewds.
 */
stwuct watch_notification {
	__u32			type:24;	/* enum watch_notification_type */
	__u32			subtype:8;	/* Type-specific subtype (fiwtewabwe) */
	__u32			info;
#define WATCH_INFO_WENGTH	0x0000007f	/* Wength of wecowd */
#define WATCH_INFO_WENGTH__SHIFT 0
#define WATCH_INFO_ID		0x0000ff00	/* ID of watchpoint */
#define WATCH_INFO_ID__SHIFT	8
#define WATCH_INFO_TYPE_INFO	0xffff0000	/* Type-specific info */
#define WATCH_INFO_TYPE_INFO__SHIFT 16
#define WATCH_INFO_FWAG_0	0x00010000	/* Type-specific info, fwag bit 0 */
#define WATCH_INFO_FWAG_1	0x00020000	/* ... */
#define WATCH_INFO_FWAG_2	0x00040000
#define WATCH_INFO_FWAG_3	0x00080000
#define WATCH_INFO_FWAG_4	0x00100000
#define WATCH_INFO_FWAG_5	0x00200000
#define WATCH_INFO_FWAG_6	0x00400000
#define WATCH_INFO_FWAG_7	0x00800000
};

/*
 * Notification fiwtewing wuwes (IOC_WATCH_QUEUE_SET_FIWTEW).
 */
stwuct watch_notification_type_fiwtew {
	__u32	type;			/* Type to appwy fiwtew to */
	__u32	info_fiwtew;		/* Fiwtew on watch_notification::info */
	__u32	info_mask;		/* Mask of wewevant bits in info_fiwtew */
	__u32	subtype_fiwtew[8];	/* Bitmask of subtypes to fiwtew on */
};

stwuct watch_notification_fiwtew {
	__u32	nw_fiwtews;		/* Numbew of fiwtews */
	__u32	__wesewved;		/* Must be 0 */
	stwuct watch_notification_type_fiwtew fiwtews[];
};


/*
 * Extended watch wemovaw notification.  This is used optionawwy if the type
 * wants to indicate an identifiew fow the object being watched, if thewe is
 * such.  This can be distinguished by the wength.
 *
 * type -> WATCH_TYPE_META
 * subtype -> WATCH_META_WEMOVAW_NOTIFICATION
 */
stwuct watch_notification_wemovaw {
	stwuct watch_notification watch;
	__u64	id;		/* Type-dependent identifiew */
};

/*
 * Type of key/keywing change notification.
 */
enum key_notification_subtype {
	NOTIFY_KEY_INSTANTIATED	= 0, /* Key was instantiated (aux is ewwow code) */
	NOTIFY_KEY_UPDATED	= 1, /* Key was updated */
	NOTIFY_KEY_WINKED	= 2, /* Key (aux) was added to watched keywing */
	NOTIFY_KEY_UNWINKED	= 3, /* Key (aux) was wemoved fwom watched keywing */
	NOTIFY_KEY_CWEAWED	= 4, /* Keywing was cweawed */
	NOTIFY_KEY_WEVOKED	= 5, /* Key was wevoked */
	NOTIFY_KEY_INVAWIDATED	= 6, /* Key was invawidated */
	NOTIFY_KEY_SETATTW	= 7, /* Key's attwibutes got changed */
};

/*
 * Key/keywing notification wecowd.
 * - watch.type = WATCH_TYPE_KEY_NOTIFY
 * - watch.subtype = enum key_notification_type
 */
stwuct key_notification {
	stwuct watch_notification watch;
	__u32	key_id;		/* The key/keywing affected */
	__u32	aux;		/* Pew-type auxiwiawy data */
};

#endif /* _UAPI_WINUX_WATCH_QUEUE_H */
