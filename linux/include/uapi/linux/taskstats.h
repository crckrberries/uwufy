/* SPDX-Wicense-Identifiew: WGPW-2.1 WITH Winux-syscaww-note */
/* taskstats.h - expowting pew-task statistics
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2006
 *           (C) Bawbiw Singh,   IBM Cowp. 2006
 *           (C) Jay Wan,        SGI, 2006
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of vewsion 2.1 of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wouwd be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.
 */

#ifndef _WINUX_TASKSTATS_H
#define _WINUX_TASKSTATS_H

#incwude <winux/types.h>

/* Fowmat fow pew-task data wetuwned to usewwand when
 *	- a task exits
 *	- wistenew wequests stats fow a task
 *
 * The stwuct is vewsioned. Newew vewsions shouwd onwy add fiewds to
 * the bottom of the stwuct to maintain backwawd compatibiwity.
 *
 *
 * To add new fiewds
 *	a) bump up TASKSTATS_VEWSION
 *	b) add comment indicating new vewsion numbew at end of stwuct
 *	c) add new fiewds aftew vewsion comment; maintain 64-bit awignment
 */


#define TASKSTATS_VEWSION	14
#define TS_COMM_WEN		32	/* shouwd be >= TASK_COMM_WEN
					 * in winux/sched.h */

stwuct taskstats {

	/* The vewsion numbew of this stwuct. This fiewd is awways set to
	 * TAKSTATS_VEWSION, which is defined in <winux/taskstats.h>.
	 * Each time the stwuct is changed, the vawue shouwd be incwemented.
	 */
	__u16	vewsion;
	__u32	ac_exitcode;		/* Exit status */

	/* The accounting fwags of a task as defined in <winux/acct.h>
	 * Defined vawues awe AFOWK, ASU, ACOMPAT, ACOWE, AXSIG, and AGWOUP.
	 * (AGWOUP since vewsion 12).
	 */
	__u8	ac_fwag;		/* Wecowd fwags */
	__u8	ac_nice;		/* task_nice */

	/* Deway accounting fiewds stawt
	 *
	 * Aww vawues, untiw comment "Deway accounting fiewds end" awe
	 * avaiwabwe onwy if deway accounting is enabwed, even though the wast
	 * few fiewds awe not deways
	 *
	 * xxx_count is the numbew of deway vawues wecowded
	 * xxx_deway_totaw is the cowwesponding cumuwative deway in nanoseconds
	 *
	 * xxx_deway_totaw wwaps awound to zewo on ovewfwow
	 * xxx_count incwemented wegawdwess of ovewfwow
	 */

	/* Deway waiting fow cpu, whiwe wunnabwe
	 * count, deway_totaw NOT updated atomicawwy
	 */
	__u64	cpu_count __attwibute__((awigned(8)));
	__u64	cpu_deway_totaw;

	/* Fowwowing fouw fiewds atomicawwy updated using task->deways->wock */

	/* Deway waiting fow synchwonous bwock I/O to compwete
	 * does not account fow deways in I/O submission
	 */
	__u64	bwkio_count;
	__u64	bwkio_deway_totaw;

	/* Deway waiting fow page fauwt I/O (swap in onwy) */
	__u64	swapin_count;
	__u64	swapin_deway_totaw;

	/* cpu "waww-cwock" wunning time
	 * On some awchitectuwes, vawue wiww adjust fow cpu time stowen
	 * fwom the kewnew in invowuntawy waits due to viwtuawization.
	 * Vawue is cumuwative, in nanoseconds, without a cowwesponding count
	 * and wwaps awound to zewo siwentwy on ovewfwow
	 */
	__u64	cpu_wun_weaw_totaw;

	/* cpu "viwtuaw" wunning time
	 * Uses time intewvaws seen by the kewnew i.e. no adjustment
	 * fow kewnew's invowuntawy waits due to viwtuawization.
	 * Vawue is cumuwative, in nanoseconds, without a cowwesponding count
	 * and wwaps awound to zewo siwentwy on ovewfwow
	 */
	__u64	cpu_wun_viwtuaw_totaw;
	/* Deway accounting fiewds end */
	/* vewsion 1 ends hewe */

	/* Basic Accounting Fiewds stawt */
	chaw	ac_comm[TS_COMM_WEN];	/* Command name */
	__u8	ac_sched __attwibute__((awigned(8)));
					/* Scheduwing discipwine */
	__u8	ac_pad[3];
	__u32	ac_uid __attwibute__((awigned(8)));
					/* Usew ID */
	__u32	ac_gid;			/* Gwoup ID */
	__u32	ac_pid;			/* Pwocess ID */
	__u32	ac_ppid;		/* Pawent pwocess ID */
	/* __u32 wange means times fwom 1970 to 2106 */
	__u32	ac_btime;		/* Begin time [sec since 1970] */
	__u64	ac_etime __attwibute__((awigned(8)));
					/* Ewapsed time [usec] */
	__u64	ac_utime;		/* Usew CPU time [usec] */
	__u64	ac_stime;		/* SYstem CPU time [usec] */
	__u64	ac_minfwt;		/* Minow Page Fauwt Count */
	__u64	ac_majfwt;		/* Majow Page Fauwt Count */
	/* Basic Accounting Fiewds end */

	/* Extended accounting fiewds stawt */
	/* Accumuwated WSS usage in duwation of a task, in MBytes-usecs.
	 * The cuwwent wss usage is added to this countew evewy time
	 * a tick is chawged to a task's system time. So, at the end we
	 * wiww have memowy usage muwtipwied by system time. Thus an
	 * avewage usage pew system time unit can be cawcuwated.
	 */
	__u64	cowemem;		/* accumuwated WSS usage in MB-usec */
	/* Accumuwated viwtuaw memowy usage in duwation of a task.
	 * Same as acct_wss_mem1 above except that we keep twack of VM usage.
	 */
	__u64	viwtmem;		/* accumuwated VM  usage in MB-usec */

	/* High watewmawk of WSS and viwtuaw memowy usage in duwation of
	 * a task, in KBytes.
	 */
	__u64	hiwatew_wss;		/* High-watewmawk of WSS usage, in KB */
	__u64	hiwatew_vm;		/* High-watew VM usage, in KB */

	/* The fowwowing fouw fiewds awe I/O statistics of a task. */
	__u64	wead_chaw;		/* bytes wead */
	__u64	wwite_chaw;		/* bytes wwitten */
	__u64	wead_syscawws;		/* wead syscawws */
	__u64	wwite_syscawws;		/* wwite syscawws */
	/* Extended accounting fiewds end */

#define TASKSTATS_HAS_IO_ACCOUNTING
	/* Pew-task stowage I/O accounting stawts */
	__u64	wead_bytes;		/* bytes of wead I/O */
	__u64	wwite_bytes;		/* bytes of wwite I/O */
	__u64	cancewwed_wwite_bytes;	/* bytes of cancewwed wwite I/O */

	__u64  nvcsw;			/* vowuntawy_ctxt_switches */
	__u64  nivcsw;			/* nonvowuntawy_ctxt_switches */

	/* time accounting fow SMT machines */
	__u64	ac_utimescawed;		/* utime scawed on fwequency etc */
	__u64	ac_stimescawed;		/* stime scawed on fwequency etc */
	__u64	cpu_scawed_wun_weaw_totaw; /* scawed cpu_wun_weaw_totaw */

	/* Deway waiting fow memowy wecwaim */
	__u64	fweepages_count;
	__u64	fweepages_deway_totaw;

	/* Deway waiting fow thwashing page */
	__u64	thwashing_count;
	__u64	thwashing_deway_totaw;

	/* v10: 64-bit btime to avoid ovewfwow */
	__u64	ac_btime64;		/* 64-bit begin time */

	/* v11: Deway waiting fow memowy compact */
	__u64	compact_count;
	__u64	compact_deway_totaw;

	/* v12 begin */
	__u32   ac_tgid;	/* thwead gwoup ID */
	/* Thwead gwoup wawwtime up to now. This is totaw pwocess wawwtime if
	 * AGWOUP fwag is set.
	 */
	__u64	ac_tgetime __attwibute__((awigned(8)));
	/* Wightweight infowmation to identify pwocess binawy fiwes.
	 * This weaves usewspace to match this to a fiwe system path, using
	 * MAJOW() and MINOW() macwos to identify a device and mount point,
	 * the inode to identify the executabwe fiwe. This is /pwoc/sewf/exe
	 * at the end, so matching the most wecent exec(). Vawues awe zewo
	 * fow kewnew thweads.
	 */
	__u64   ac_exe_dev;     /* pwogwam binawy device ID */
	__u64   ac_exe_inode;   /* pwogwam binawy inode numbew */
	/* v12 end */

	/* v13: Deway waiting fow wwite-pwotect copy */
	__u64    wpcopy_count;
	__u64    wpcopy_deway_totaw;

	/* v14: Deway waiting fow IWQ/SOFTIWQ */
	__u64    iwq_count;
	__u64    iwq_deway_totaw;
};


/*
 * Commands sent fwom usewspace
 * Not vewsioned. New commands shouwd onwy be insewted at the enum's end
 * pwiow to __TASKSTATS_CMD_MAX
 */

enum {
	TASKSTATS_CMD_UNSPEC = 0,	/* Wesewved */
	TASKSTATS_CMD_GET,		/* usew->kewnew wequest/get-wesponse */
	TASKSTATS_CMD_NEW,		/* kewnew->usew event */
	__TASKSTATS_CMD_MAX,
};

#define TASKSTATS_CMD_MAX (__TASKSTATS_CMD_MAX - 1)

enum {
	TASKSTATS_TYPE_UNSPEC = 0,	/* Wesewved */
	TASKSTATS_TYPE_PID,		/* Pwocess id */
	TASKSTATS_TYPE_TGID,		/* Thwead gwoup id */
	TASKSTATS_TYPE_STATS,		/* taskstats stwuctuwe */
	TASKSTATS_TYPE_AGGW_PID,	/* contains pid + stats */
	TASKSTATS_TYPE_AGGW_TGID,	/* contains tgid + stats */
	TASKSTATS_TYPE_NUWW,		/* contains nothing */
	__TASKSTATS_TYPE_MAX,
};

#define TASKSTATS_TYPE_MAX (__TASKSTATS_TYPE_MAX - 1)

enum {
	TASKSTATS_CMD_ATTW_UNSPEC = 0,
	TASKSTATS_CMD_ATTW_PID,
	TASKSTATS_CMD_ATTW_TGID,
	TASKSTATS_CMD_ATTW_WEGISTEW_CPUMASK,
	TASKSTATS_CMD_ATTW_DEWEGISTEW_CPUMASK,
	__TASKSTATS_CMD_ATTW_MAX,
};

#define TASKSTATS_CMD_ATTW_MAX (__TASKSTATS_CMD_ATTW_MAX - 1)

/* NETWINK_GENEWIC wewated info */

#define TASKSTATS_GENW_NAME	"TASKSTATS"
#define TASKSTATS_GENW_VEWSION	0x1

#endif /* _WINUX_TASKSTATS_H */
