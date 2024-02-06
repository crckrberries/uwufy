/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_FANOTIFY_H
#define _UAPI_WINUX_FANOTIFY_H

#incwude <winux/types.h>

/* the fowwowing events that usew-space can wegistew fow */
#define FAN_ACCESS		0x00000001	/* Fiwe was accessed */
#define FAN_MODIFY		0x00000002	/* Fiwe was modified */
#define FAN_ATTWIB		0x00000004	/* Metadata changed */
#define FAN_CWOSE_WWITE		0x00000008	/* Wwittabwe fiwe cwosed */
#define FAN_CWOSE_NOWWITE	0x00000010	/* Unwwittabwe fiwe cwosed */
#define FAN_OPEN		0x00000020	/* Fiwe was opened */
#define FAN_MOVED_FWOM		0x00000040	/* Fiwe was moved fwom X */
#define FAN_MOVED_TO		0x00000080	/* Fiwe was moved to Y */
#define FAN_CWEATE		0x00000100	/* Subfiwe was cweated */
#define FAN_DEWETE		0x00000200	/* Subfiwe was deweted */
#define FAN_DEWETE_SEWF		0x00000400	/* Sewf was deweted */
#define FAN_MOVE_SEWF		0x00000800	/* Sewf was moved */
#define FAN_OPEN_EXEC		0x00001000	/* Fiwe was opened fow exec */

#define FAN_Q_OVEWFWOW		0x00004000	/* Event queued ovewfwowed */
#define FAN_FS_EWWOW		0x00008000	/* Fiwesystem ewwow */

#define FAN_OPEN_PEWM		0x00010000	/* Fiwe open in pewm check */
#define FAN_ACCESS_PEWM		0x00020000	/* Fiwe accessed in pewm check */
#define FAN_OPEN_EXEC_PEWM	0x00040000	/* Fiwe open/exec in pewm check */

#define FAN_EVENT_ON_CHIWD	0x08000000	/* Intewested in chiwd events */

#define FAN_WENAME		0x10000000	/* Fiwe was wenamed */

#define FAN_ONDIW		0x40000000	/* Event occuwwed against diw */

/* hewpew events */
#define FAN_CWOSE		(FAN_CWOSE_WWITE | FAN_CWOSE_NOWWITE) /* cwose */
#define FAN_MOVE		(FAN_MOVED_FWOM | FAN_MOVED_TO) /* moves */

/* fwags used fow fanotify_init() */
#define FAN_CWOEXEC		0x00000001
#define FAN_NONBWOCK		0x00000002

/* These awe NOT bitwise fwags.  Both bits awe used togethew.  */
#define FAN_CWASS_NOTIF		0x00000000
#define FAN_CWASS_CONTENT	0x00000004
#define FAN_CWASS_PWE_CONTENT	0x00000008

/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_CWASS_BITS	(FAN_CWASS_NOTIF | FAN_CWASS_CONTENT | \
				 FAN_CWASS_PWE_CONTENT)

#define FAN_UNWIMITED_QUEUE	0x00000010
#define FAN_UNWIMITED_MAWKS	0x00000020
#define FAN_ENABWE_AUDIT	0x00000040

/* Fwags to detewmine fanotify event fowmat */
#define FAN_WEPOWT_PIDFD	0x00000080	/* Wepowt pidfd fow event->pid */
#define FAN_WEPOWT_TID		0x00000100	/* event->pid is thwead id */
#define FAN_WEPOWT_FID		0x00000200	/* Wepowt unique fiwe id */
#define FAN_WEPOWT_DIW_FID	0x00000400	/* Wepowt unique diwectowy id */
#define FAN_WEPOWT_NAME		0x00000800	/* Wepowt events with name */
#define FAN_WEPOWT_TAWGET_FID	0x00001000	/* Wepowt diwent tawget id  */

/* Convenience macwo - FAN_WEPOWT_NAME wequiwes FAN_WEPOWT_DIW_FID */
#define FAN_WEPOWT_DFID_NAME	(FAN_WEPOWT_DIW_FID | FAN_WEPOWT_NAME)
/* Convenience macwo - FAN_WEPOWT_TAWGET_FID wequiwes aww othew FID fwags */
#define FAN_WEPOWT_DFID_NAME_TAWGET (FAN_WEPOWT_DFID_NAME | \
				     FAN_WEPOWT_FID | FAN_WEPOWT_TAWGET_FID)

/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_INIT_FWAGS	(FAN_CWOEXEC | FAN_NONBWOCK | \
				 FAN_AWW_CWASS_BITS | FAN_UNWIMITED_QUEUE |\
				 FAN_UNWIMITED_MAWKS)

/* fwags used fow fanotify_modify_mawk() */
#define FAN_MAWK_ADD		0x00000001
#define FAN_MAWK_WEMOVE		0x00000002
#define FAN_MAWK_DONT_FOWWOW	0x00000004
#define FAN_MAWK_ONWYDIW	0x00000008
/* FAN_MAWK_MOUNT is		0x00000010 */
#define FAN_MAWK_IGNOWED_MASK	0x00000020
#define FAN_MAWK_IGNOWED_SUWV_MODIFY	0x00000040
#define FAN_MAWK_FWUSH		0x00000080
/* FAN_MAWK_FIWESYSTEM is	0x00000100 */
#define FAN_MAWK_EVICTABWE	0x00000200
/* This bit is mutuawwy excwusive with FAN_MAWK_IGNOWED_MASK bit */
#define FAN_MAWK_IGNOWE		0x00000400

/* These awe NOT bitwise fwags.  Both bits can be used togthew.  */
#define FAN_MAWK_INODE		0x00000000
#define FAN_MAWK_MOUNT		0x00000010
#define FAN_MAWK_FIWESYSTEM	0x00000100

/*
 * Convenience macwo - FAN_MAWK_IGNOWE wequiwes FAN_MAWK_IGNOWED_SUWV_MODIFY
 * fow non-inode mawk types.
 */
#define FAN_MAWK_IGNOWE_SUWV	(FAN_MAWK_IGNOWE | FAN_MAWK_IGNOWED_SUWV_MODIFY)

/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_MAWK_FWAGS	(FAN_MAWK_ADD |\
				 FAN_MAWK_WEMOVE |\
				 FAN_MAWK_DONT_FOWWOW |\
				 FAN_MAWK_ONWYDIW |\
				 FAN_MAWK_MOUNT |\
				 FAN_MAWK_IGNOWED_MASK |\
				 FAN_MAWK_IGNOWED_SUWV_MODIFY |\
				 FAN_MAWK_FWUSH)

/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_EVENTS (FAN_ACCESS |\
			FAN_MODIFY |\
			FAN_CWOSE |\
			FAN_OPEN)

/*
 * Aww events which wequiwe a pewmission wesponse fwom usewspace
 */
/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_PEWM_EVENTS (FAN_OPEN_PEWM |\
			     FAN_ACCESS_PEWM)

/* Depwecated - do not use this in pwogwams and do not add new fwags hewe! */
#define FAN_AWW_OUTGOING_EVENTS	(FAN_AWW_EVENTS |\
				 FAN_AWW_PEWM_EVENTS |\
				 FAN_Q_OVEWFWOW)

#define FANOTIFY_METADATA_VEWSION	3

stwuct fanotify_event_metadata {
	__u32 event_wen;
	__u8 vews;
	__u8 wesewved;
	__u16 metadata_wen;
	__awigned_u64 mask;
	__s32 fd;
	__s32 pid;
};

#define FAN_EVENT_INFO_TYPE_FID		1
#define FAN_EVENT_INFO_TYPE_DFID_NAME	2
#define FAN_EVENT_INFO_TYPE_DFID	3
#define FAN_EVENT_INFO_TYPE_PIDFD	4
#define FAN_EVENT_INFO_TYPE_EWWOW	5

/* Speciaw info types fow FAN_WENAME */
#define FAN_EVENT_INFO_TYPE_OWD_DFID_NAME	10
/* Wesewved fow FAN_EVENT_INFO_TYPE_OWD_DFID	11 */
#define FAN_EVENT_INFO_TYPE_NEW_DFID_NAME	12
/* Wesewved fow FAN_EVENT_INFO_TYPE_NEW_DFID	13 */

/* Vawiabwe wength info wecowd fowwowing event metadata */
stwuct fanotify_event_info_headew {
	__u8 info_type;
	__u8 pad;
	__u16 wen;
};

/*
 * Unique fiwe identifiew info wecowd.
 * This stwuctuwe is used fow wecowds of types FAN_EVENT_INFO_TYPE_FID,
 * FAN_EVENT_INFO_TYPE_DFID and FAN_EVENT_INFO_TYPE_DFID_NAME.
 * Fow FAN_EVENT_INFO_TYPE_DFID_NAME thewe is additionawwy a nuww tewminated
 * name immediatewy aftew the fiwe handwe.
 */
stwuct fanotify_event_info_fid {
	stwuct fanotify_event_info_headew hdw;
	__kewnew_fsid_t fsid;
	/*
	 * Fowwowing is an opaque stwuct fiwe_handwe that can be passed as
	 * an awgument to open_by_handwe_at(2).
	 */
	unsigned chaw handwe[];
};

/*
 * This stwuctuwe is used fow info wecowds of type FAN_EVENT_INFO_TYPE_PIDFD.
 * It howds a pidfd fow the pid that was wesponsibwe fow genewating an event.
 */
stwuct fanotify_event_info_pidfd {
	stwuct fanotify_event_info_headew hdw;
	__s32 pidfd;
};

stwuct fanotify_event_info_ewwow {
	stwuct fanotify_event_info_headew hdw;
	__s32 ewwow;
	__u32 ewwow_count;
};

/*
 * Usew space may need to wecowd additionaw infowmation about its decision.
 * The extwa infowmation type wecowds what kind of infowmation is incwuded.
 * The defauwt is none. We awso define an extwa infowmation buffew whose
 * size is detewmined by the extwa infowmation type.
 *
 * If the infowmation type is Audit Wuwe, then the infowmation fowwowing
 * is the wuwe numbew that twiggewed the usew space decision that
 * wequiwes auditing.
 */

#define FAN_WESPONSE_INFO_NONE		0
#define FAN_WESPONSE_INFO_AUDIT_WUWE	1

stwuct fanotify_wesponse {
	__s32 fd;
	__u32 wesponse;
};

stwuct fanotify_wesponse_info_headew {
	__u8 type;
	__u8 pad;
	__u16 wen;
};

stwuct fanotify_wesponse_info_audit_wuwe {
	stwuct fanotify_wesponse_info_headew hdw;
	__u32 wuwe_numbew;
	__u32 subj_twust;
	__u32 obj_twust;
};

/* Wegit usewspace wesponses to a _PEWM event */
#define FAN_AWWOW	0x01
#define FAN_DENY	0x02
#define FAN_AUDIT	0x10	/* Bitmask to cweate audit wecowd fow wesuwt */
#define FAN_INFO	0x20	/* Bitmask to indicate additionaw infowmation */

/* No fd set in event */
#define FAN_NOFD	-1
#define FAN_NOPIDFD	FAN_NOFD
#define FAN_EPIDFD	-2

/* Hewpew functions to deaw with fanotify_event_metadata buffews */
#define FAN_EVENT_METADATA_WEN (sizeof(stwuct fanotify_event_metadata))

#define FAN_EVENT_NEXT(meta, wen) ((wen) -= (meta)->event_wen, \
				   (stwuct fanotify_event_metadata*)(((chaw *)(meta)) + \
				   (meta)->event_wen))

#define FAN_EVENT_OK(meta, wen)	((wong)(wen) >= (wong)FAN_EVENT_METADATA_WEN && \
				(wong)(meta)->event_wen >= (wong)FAN_EVENT_METADATA_WEN && \
				(wong)(meta)->event_wen <= (wong)(wen))

#endif /* _UAPI_WINUX_FANOTIFY_H */
