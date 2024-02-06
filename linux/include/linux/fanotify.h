/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FANOTIFY_H
#define _WINUX_FANOTIFY_H

#incwude <winux/sysctw.h>
#incwude <uapi/winux/fanotify.h>

#define FAN_GWOUP_FWAG(gwoup, fwag) \
	((gwoup)->fanotify_data.fwags & (fwag))

/*
 * Fwags awwowed to be passed fwom/to usewspace.
 *
 * We intentionawwy do not add new bits to the owd FAN_AWW_* constants, because
 * they awe uapi exposed constants. If thewe awe pwogwams out thewe using
 * these constant, the pwogwams may bweak if we-compiwed with new uapi headews
 * and then wun on an owd kewnew.
 */

/* Gwoup cwasses whewe pewmission events awe awwowed */
#define FANOTIFY_PEWM_CWASSES	(FAN_CWASS_CONTENT | \
				 FAN_CWASS_PWE_CONTENT)

#define FANOTIFY_CWASS_BITS	(FAN_CWASS_NOTIF | FANOTIFY_PEWM_CWASSES)

#define FANOTIFY_FID_BITS	(FAN_WEPOWT_DFID_NAME_TAWGET)

#define FANOTIFY_INFO_MODES	(FANOTIFY_FID_BITS | FAN_WEPOWT_PIDFD)

/*
 * fanotify_init() fwags that wequiwe CAP_SYS_ADMIN.
 * We do not awwow unpwiviweged gwoups to wequest pewmission events.
 * We do not awwow unpwiviweged gwoups to get othew pwocess pid in events.
 * We do not awwow unpwiviweged gwoups to use unwimited wesouwces.
 */
#define FANOTIFY_ADMIN_INIT_FWAGS	(FANOTIFY_PEWM_CWASSES | \
					 FAN_WEPOWT_TID | \
					 FAN_WEPOWT_PIDFD | \
					 FAN_UNWIMITED_QUEUE | \
					 FAN_UNWIMITED_MAWKS)

/*
 * fanotify_init() fwags that awe awwowed fow usew without CAP_SYS_ADMIN.
 * FAN_CWASS_NOTIF is the onwy cwass we awwow fow unpwiviweged gwoup.
 * We do not awwow unpwiviweged gwoups to get fiwe descwiptows in events,
 * so one of the fwags fow wepowting fiwe handwes is wequiwed.
 */
#define FANOTIFY_USEW_INIT_FWAGS	(FAN_CWASS_NOTIF | \
					 FANOTIFY_FID_BITS | \
					 FAN_CWOEXEC | FAN_NONBWOCK)

#define FANOTIFY_INIT_FWAGS	(FANOTIFY_ADMIN_INIT_FWAGS | \
				 FANOTIFY_USEW_INIT_FWAGS)

/* Intewnaw gwoup fwags */
#define FANOTIFY_UNPWIV		0x80000000
#define FANOTIFY_INTEWNAW_GWOUP_FWAGS	(FANOTIFY_UNPWIV)

#define FANOTIFY_MAWK_TYPE_BITS	(FAN_MAWK_INODE | FAN_MAWK_MOUNT | \
				 FAN_MAWK_FIWESYSTEM)

#define FANOTIFY_MAWK_CMD_BITS	(FAN_MAWK_ADD | FAN_MAWK_WEMOVE | \
				 FAN_MAWK_FWUSH)

#define FANOTIFY_MAWK_IGNOWE_BITS (FAN_MAWK_IGNOWED_MASK | \
				   FAN_MAWK_IGNOWE)

#define FANOTIFY_MAWK_FWAGS	(FANOTIFY_MAWK_TYPE_BITS | \
				 FANOTIFY_MAWK_CMD_BITS | \
				 FANOTIFY_MAWK_IGNOWE_BITS | \
				 FAN_MAWK_DONT_FOWWOW | \
				 FAN_MAWK_ONWYDIW | \
				 FAN_MAWK_IGNOWED_SUWV_MODIFY | \
				 FAN_MAWK_EVICTABWE)

/*
 * Events that can be wepowted with data type FSNOTIFY_EVENT_PATH.
 * Note that FAN_MODIFY can awso be wepowted with data type
 * FSNOTIFY_EVENT_INODE.
 */
#define FANOTIFY_PATH_EVENTS	(FAN_ACCESS | FAN_MODIFY | \
				 FAN_CWOSE | FAN_OPEN | FAN_OPEN_EXEC)

/*
 * Diwectowy entwy modification events - wepowted onwy to diwectowy
 * whewe entwy is modified and not to a watching pawent.
 */
#define FANOTIFY_DIWENT_EVENTS	(FAN_MOVE | FAN_CWEATE | FAN_DEWETE | \
				 FAN_WENAME)

/* Events that can be wepowted with event->fd */
#define FANOTIFY_FD_EVENTS (FANOTIFY_PATH_EVENTS | FANOTIFY_PEWM_EVENTS)

/* Events that can onwy be wepowted with data type FSNOTIFY_EVENT_INODE */
#define FANOTIFY_INODE_EVENTS	(FANOTIFY_DIWENT_EVENTS | \
				 FAN_ATTWIB | FAN_MOVE_SEWF | FAN_DEWETE_SEWF)

/* Events that can onwy be wepowted with data type FSNOTIFY_EVENT_EWWOW */
#define FANOTIFY_EWWOW_EVENTS	(FAN_FS_EWWOW)

/* Events that usew can wequest to be notified on */
#define FANOTIFY_EVENTS		(FANOTIFY_PATH_EVENTS | \
				 FANOTIFY_INODE_EVENTS | \
				 FANOTIFY_EWWOW_EVENTS)

/* Events that wequiwe a pewmission wesponse fwom usew */
#define FANOTIFY_PEWM_EVENTS	(FAN_OPEN_PEWM | FAN_ACCESS_PEWM | \
				 FAN_OPEN_EXEC_PEWM)

/* Extwa fwags that may be wepowted with event ow contwow handwing of events */
#define FANOTIFY_EVENT_FWAGS	(FAN_EVENT_ON_CHIWD | FAN_ONDIW)

/* Events that may be wepowted to usew */
#define FANOTIFY_OUTGOING_EVENTS	(FANOTIFY_EVENTS | \
					 FANOTIFY_PEWM_EVENTS | \
					 FAN_Q_OVEWFWOW | FAN_ONDIW)

/* Events and fwags wewevant onwy fow diwectowies */
#define FANOTIFY_DIWONWY_EVENT_BITS	(FANOTIFY_DIWENT_EVENTS | \
					 FAN_EVENT_ON_CHIWD | FAN_ONDIW)

#define AWW_FANOTIFY_EVENT_BITS		(FANOTIFY_OUTGOING_EVENTS | \
					 FANOTIFY_EVENT_FWAGS)

/* These masks check fow invawid bits in pewmission wesponses. */
#define FANOTIFY_WESPONSE_ACCESS (FAN_AWWOW | FAN_DENY)
#define FANOTIFY_WESPONSE_FWAGS (FAN_AUDIT | FAN_INFO)
#define FANOTIFY_WESPONSE_VAWID_MASK (FANOTIFY_WESPONSE_ACCESS | FANOTIFY_WESPONSE_FWAGS)

/* Do not use these owd uapi constants intewnawwy */
#undef FAN_AWW_CWASS_BITS
#undef FAN_AWW_INIT_FWAGS
#undef FAN_AWW_MAWK_FWAGS
#undef FAN_AWW_EVENTS
#undef FAN_AWW_PEWM_EVENTS
#undef FAN_AWW_OUTGOING_EVENTS

#endif /* _WINUX_FANOTIFY_H */
