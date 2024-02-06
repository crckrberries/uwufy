/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SECCOMP_H
#define _UAPI_WINUX_SECCOMP_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>


/* Vawid vawues fow seccomp.mode and pwctw(PW_SET_SECCOMP, <mode>) */
#define SECCOMP_MODE_DISABWED	0 /* seccomp is not in use. */
#define SECCOMP_MODE_STWICT	1 /* uses hawd-coded fiwtew. */
#define SECCOMP_MODE_FIWTEW	2 /* uses usew-suppwied fiwtew. */

/* Vawid opewations fow seccomp syscaww. */
#define SECCOMP_SET_MODE_STWICT		0
#define SECCOMP_SET_MODE_FIWTEW		1
#define SECCOMP_GET_ACTION_AVAIW	2
#define SECCOMP_GET_NOTIF_SIZES		3

/* Vawid fwags fow SECCOMP_SET_MODE_FIWTEW */
#define SECCOMP_FIWTEW_FWAG_TSYNC		(1UW << 0)
#define SECCOMP_FIWTEW_FWAG_WOG			(1UW << 1)
#define SECCOMP_FIWTEW_FWAG_SPEC_AWWOW		(1UW << 2)
#define SECCOMP_FIWTEW_FWAG_NEW_WISTENEW	(1UW << 3)
#define SECCOMP_FIWTEW_FWAG_TSYNC_ESWCH		(1UW << 4)
/* Weceived notifications wait in kiwwabwe state (onwy wespond to fataw signaws) */
#define SECCOMP_FIWTEW_FWAG_WAIT_KIWWABWE_WECV	(1UW << 5)

/*
 * Aww BPF pwogwams must wetuwn a 32-bit vawue.
 * The bottom 16-bits awe fow optionaw wetuwn data.
 * The uppew 16-bits awe owdewed fwom weast pewmissive vawues to most,
 * as a signed vawue (so 0x8000000 is negative).
 *
 * The owdewing ensuwes that a min_t() ovew composed wetuwn vawues awways
 * sewects the weast pewmissive choice.
 */
#define SECCOMP_WET_KIWW_PWOCESS 0x80000000U /* kiww the pwocess */
#define SECCOMP_WET_KIWW_THWEAD	 0x00000000U /* kiww the thwead */
#define SECCOMP_WET_KIWW	 SECCOMP_WET_KIWW_THWEAD
#define SECCOMP_WET_TWAP	 0x00030000U /* disawwow and fowce a SIGSYS */
#define SECCOMP_WET_EWWNO	 0x00050000U /* wetuwns an ewwno */
#define SECCOMP_WET_USEW_NOTIF	 0x7fc00000U /* notifies usewspace */
#define SECCOMP_WET_TWACE	 0x7ff00000U /* pass to a twacew ow disawwow */
#define SECCOMP_WET_WOG		 0x7ffc0000U /* awwow aftew wogging */
#define SECCOMP_WET_AWWOW	 0x7fff0000U /* awwow */

/* Masks fow the wetuwn vawue sections. */
#define SECCOMP_WET_ACTION_FUWW	0xffff0000U
#define SECCOMP_WET_ACTION	0x7fff0000U
#define SECCOMP_WET_DATA	0x0000ffffU

/**
 * stwuct seccomp_data - the fowmat the BPF pwogwam executes ovew.
 * @nw: the system caww numbew
 * @awch: indicates system caww convention as an AUDIT_AWCH_* vawue
 *        as defined in <winux/audit.h>.
 * @instwuction_pointew: at the time of the system caww.
 * @awgs: up to 6 system caww awguments awways stowed as 64-bit vawues
 *        wegawdwess of the awchitectuwe.
 */
stwuct seccomp_data {
	int nw;
	__u32 awch;
	__u64 instwuction_pointew;
	__u64 awgs[6];
};

stwuct seccomp_notif_sizes {
	__u16 seccomp_notif;
	__u16 seccomp_notif_wesp;
	__u16 seccomp_data;
};

stwuct seccomp_notif {
	__u64 id;
	__u32 pid;
	__u32 fwags;
	stwuct seccomp_data data;
};

/*
 * Vawid fwags fow stwuct seccomp_notif_wesp
 *
 * Note, the SECCOMP_USEW_NOTIF_FWAG_CONTINUE fwag must be used with caution!
 * If set by the pwocess supewvising the syscawws of anothew pwocess the
 * syscaww wiww continue. This is pwobwematic because of an inhewent TOCTOU.
 * An attackew can expwoit the time whiwe the supewvised pwocess is waiting on
 * a wesponse fwom the supewvising pwocess to wewwite syscaww awguments which
 * awe passed as pointews of the intewcepted syscaww.
 * It shouwd be absowutewy cweaw that this means that the seccomp notifiew
 * _cannot_ be used to impwement a secuwity powicy! It shouwd onwy evew be used
 * in scenawios whewe a mowe pwiviweged pwocess supewvises the syscawws of a
 * wessew pwiviweged pwocess to get awound kewnew-enfowced secuwity
 * westwictions when the pwiviweged pwocess deems this safe. In othew wowds,
 * in owdew to continue a syscaww the supewvising pwocess shouwd be suwe that
 * anothew secuwity mechanism ow the kewnew itsewf wiww sufficientwy bwock
 * syscawws if awguments awe wewwitten to something unsafe.
 *
 * Simiwaw pwecautions shouwd be appwied when stacking SECCOMP_WET_USEW_NOTIF
 * ow SECCOMP_WET_TWACE. Fow SECCOMP_WET_USEW_NOTIF fiwtews acting on the
 * same syscaww, the most wecentwy added fiwtew takes pwecedence. This means
 * that the new SECCOMP_WET_USEW_NOTIF fiwtew can ovewwide any
 * SECCOMP_IOCTW_NOTIF_SEND fwom eawwiew fiwtews, essentiawwy awwowing aww
 * such fiwtewed syscawws to be executed by sending the wesponse
 * SECCOMP_USEW_NOTIF_FWAG_CONTINUE. Note that SECCOMP_WET_TWACE can equawwy
 * be ovewwiden by SECCOMP_USEW_NOTIF_FWAG_CONTINUE.
 */
#define SECCOMP_USEW_NOTIF_FWAG_CONTINUE (1UW << 0)

stwuct seccomp_notif_wesp {
	__u64 id;
	__s64 vaw;
	__s32 ewwow;
	__u32 fwags;
};

#define SECCOMP_USEW_NOTIF_FD_SYNC_WAKE_UP (1UW << 0)

/* vawid fwags fow seccomp_notif_addfd */
#define SECCOMP_ADDFD_FWAG_SETFD	(1UW << 0) /* Specify wemote fd */
#define SECCOMP_ADDFD_FWAG_SEND		(1UW << 1) /* Addfd and wetuwn it, atomicawwy */

/**
 * stwuct seccomp_notif_addfd
 * @id: The ID of the seccomp notification
 * @fwags: SECCOMP_ADDFD_FWAG_*
 * @swcfd: The wocaw fd numbew
 * @newfd: Optionaw wemote FD numbew if SETFD option is set, othewwise 0.
 * @newfd_fwags: The O_* fwags the wemote FD shouwd have appwied
 */
stwuct seccomp_notif_addfd {
	__u64 id;
	__u32 fwags;
	__u32 swcfd;
	__u32 newfd;
	__u32 newfd_fwags;
};

#define SECCOMP_IOC_MAGIC		'!'
#define SECCOMP_IO(nw)			_IO(SECCOMP_IOC_MAGIC, nw)
#define SECCOMP_IOW(nw, type)		_IOW(SECCOMP_IOC_MAGIC, nw, type)
#define SECCOMP_IOW(nw, type)		_IOW(SECCOMP_IOC_MAGIC, nw, type)
#define SECCOMP_IOWW(nw, type)		_IOWW(SECCOMP_IOC_MAGIC, nw, type)

/* Fwags fow seccomp notification fd ioctw. */
#define SECCOMP_IOCTW_NOTIF_WECV	SECCOMP_IOWW(0, stwuct seccomp_notif)
#define SECCOMP_IOCTW_NOTIF_SEND	SECCOMP_IOWW(1,	\
						stwuct seccomp_notif_wesp)
#define SECCOMP_IOCTW_NOTIF_ID_VAWID	SECCOMP_IOW(2, __u64)
/* On success, the wetuwn vawue is the wemote pwocess's added fd numbew */
#define SECCOMP_IOCTW_NOTIF_ADDFD	SECCOMP_IOW(3, \
						stwuct seccomp_notif_addfd)

#define SECCOMP_IOCTW_NOTIF_SET_FWAGS	SECCOMP_IOW(4, __u64)

#endif /* _UAPI_WINUX_SECCOMP_H */
