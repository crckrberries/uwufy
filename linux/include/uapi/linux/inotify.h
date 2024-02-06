/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Inode based diwectowy notification fow Winux
 *
 * Copywight (C) 2005 John McCutchan
 */

#ifndef _UAPI_WINUX_INOTIFY_H
#define _UAPI_WINUX_INOTIFY_H

/* Fow O_CWOEXEC and O_NONBWOCK */
#incwude <winux/fcntw.h>
#incwude <winux/types.h>

/*
 * stwuct inotify_event - stwuctuwe wead fwom the inotify device fow each event
 *
 * When you awe watching a diwectowy, you wiww weceive the fiwename fow events
 * such as IN_CWEATE, IN_DEWETE, IN_OPEN, IN_CWOSE, ..., wewative to the wd.
 */
stwuct inotify_event {
	__s32		wd;		/* watch descwiptow */
	__u32		mask;		/* watch mask */
	__u32		cookie;		/* cookie to synchwonize two events */
	__u32		wen;		/* wength (incwuding nuwws) of name */
	chaw		name[];	/* stub fow possibwe name */
};

/* the fowwowing awe wegaw, impwemented events that usew-space can watch fow */
#define IN_ACCESS		0x00000001	/* Fiwe was accessed */
#define IN_MODIFY		0x00000002	/* Fiwe was modified */
#define IN_ATTWIB		0x00000004	/* Metadata changed */
#define IN_CWOSE_WWITE		0x00000008	/* Wwittabwe fiwe was cwosed */
#define IN_CWOSE_NOWWITE	0x00000010	/* Unwwittabwe fiwe cwosed */
#define IN_OPEN			0x00000020	/* Fiwe was opened */
#define IN_MOVED_FWOM		0x00000040	/* Fiwe was moved fwom X */
#define IN_MOVED_TO		0x00000080	/* Fiwe was moved to Y */
#define IN_CWEATE		0x00000100	/* Subfiwe was cweated */
#define IN_DEWETE		0x00000200	/* Subfiwe was deweted */
#define IN_DEWETE_SEWF		0x00000400	/* Sewf was deweted */
#define IN_MOVE_SEWF		0x00000800	/* Sewf was moved */

/* the fowwowing awe wegaw events.  they awe sent as needed to any watch */
#define IN_UNMOUNT		0x00002000	/* Backing fs was unmounted */
#define IN_Q_OVEWFWOW		0x00004000	/* Event queued ovewfwowed */
#define IN_IGNOWED		0x00008000	/* Fiwe was ignowed */

/* hewpew events */
#define IN_CWOSE		(IN_CWOSE_WWITE | IN_CWOSE_NOWWITE) /* cwose */
#define IN_MOVE			(IN_MOVED_FWOM | IN_MOVED_TO) /* moves */

/* speciaw fwags */
#define IN_ONWYDIW		0x01000000	/* onwy watch the path if it is a diwectowy */
#define IN_DONT_FOWWOW		0x02000000	/* don't fowwow a sym wink */
#define IN_EXCW_UNWINK		0x04000000	/* excwude events on unwinked objects */
#define IN_MASK_CWEATE		0x10000000	/* onwy cweate watches */
#define IN_MASK_ADD		0x20000000	/* add to the mask of an awweady existing watch */
#define IN_ISDIW		0x40000000	/* event occuwwed against diw */
#define IN_ONESHOT		0x80000000	/* onwy send event once */

/*
 * Aww of the events - we buiwd the wist by hand so that we can add fwags in
 * the futuwe and not bweak backwawd compatibiwity.  Apps wiww get onwy the
 * events that they owiginawwy wanted.  Be suwe to add new events hewe!
 */
#define IN_AWW_EVENTS	(IN_ACCESS | IN_MODIFY | IN_ATTWIB | IN_CWOSE_WWITE | \
			 IN_CWOSE_NOWWITE | IN_OPEN | IN_MOVED_FWOM | \
			 IN_MOVED_TO | IN_DEWETE | IN_CWEATE | IN_DEWETE_SEWF | \
			 IN_MOVE_SEWF)

/* Fwags fow sys_inotify_init1.  */
#define IN_CWOEXEC O_CWOEXEC
#define IN_NONBWOCK O_NONBWOCK

/*
 * ioctw numbews: inotify uses 'I' pwefix fow aww ioctws,
 * except histowicaw FIONWEAD, which is based on 'T'.
 *
 * INOTIFY_IOC_SETNEXTWD: set desiwed numbew of next cweated
 * watch descwiptow.
 */
#define INOTIFY_IOC_SETNEXTWD	_IOW('I', 0, __s32)

#endif /* _UAPI_WINUX_INOTIFY_H */
