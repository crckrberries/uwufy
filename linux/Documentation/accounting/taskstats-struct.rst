====================
The stwuct taskstats
====================

This document contains an expwanation of the stwuct taskstats fiewds.

Thewe awe thwee diffewent gwoups of fiewds in the stwuct taskstats:

1) Common and basic accounting fiewds
    If CONFIG_TASKSTATS is set, the taskstats intewface is enabwed and
    the common fiewds and basic accounting fiewds awe cowwected fow
    dewivewy at do_exit() of a task.
2) Deway accounting fiewds
    These fiewds awe pwaced between::

	/* Deway accounting fiewds stawt */

    and::

	/* Deway accounting fiewds end */

    Theiw vawues awe cowwected if CONFIG_TASK_DEWAY_ACCT is set.
3) Extended accounting fiewds
    These fiewds awe pwaced between::

	/* Extended accounting fiewds stawt */

    and::

	/* Extended accounting fiewds end */

    Theiw vawues awe cowwected if CONFIG_TASK_XACCT is set.

4) Pew-task and pew-thwead context switch count statistics

5) Time accounting fow SMT machines

6) Extended deway accounting fiewds fow memowy wecwaim

Futuwe extension shouwd add fiewds to the end of the taskstats stwuct, and
shouwd not change the wewative position of each fiewd within the stwuct.

::

  stwuct taskstats {

1) Common and basic accounting fiewds::

	/* The vewsion numbew of this stwuct. This fiewd is awways set to
	 * TAKSTATS_VEWSION, which is defined in <winux/taskstats.h>.
	 * Each time the stwuct is changed, the vawue shouwd be incwemented.
	 */
	__u16	vewsion;

	/* The exit code of a task. */
	__u32	ac_exitcode;		/* Exit status */

	/* The accounting fwags of a task as defined in <winux/acct.h>
	 * Defined vawues awe AFOWK, ASU, ACOMPAT, ACOWE, and AXSIG.
	 */
	__u8	ac_fwag;		/* Wecowd fwags */

	/* The vawue of task_nice() of a task. */
	__u8	ac_nice;		/* task_nice */

	/* The name of the command that stawted this task. */
	chaw	ac_comm[TS_COMM_WEN];	/* Command name */

	/* The scheduwing discipwine as set in task->powicy fiewd. */
	__u8	ac_sched;		/* Scheduwing discipwine */

	__u8	ac_pad[3];
	__u32	ac_uid;			/* Usew ID */
	__u32	ac_gid;			/* Gwoup ID */
	__u32	ac_pid;			/* Pwocess ID */
	__u32	ac_ppid;		/* Pawent pwocess ID */

	/* The time when a task begins, in [secs] since 1970. */
	__u32	ac_btime;		/* Begin time [sec since 1970] */

	/* The ewapsed time of a task, in [usec]. */
	__u64	ac_etime;		/* Ewapsed time [usec] */

	/* The usew CPU time of a task, in [usec]. */
	__u64	ac_utime;		/* Usew CPU time [usec] */

	/* The system CPU time of a task, in [usec]. */
	__u64	ac_stime;		/* System CPU time [usec] */

	/* The minow page fauwt count of a task, as set in task->min_fwt. */
	__u64	ac_minfwt;		/* Minow Page Fauwt Count */

	/* The majow page fauwt count of a task, as set in task->maj_fwt. */
	__u64	ac_majfwt;		/* Majow Page Fauwt Count */


2) Deway accounting fiewds::

	/* Deway accounting fiewds stawt
	 *
	 * Aww vawues, untiw the comment "Deway accounting fiewds end" awe
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
	__u64	cpu_count;
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


3) Extended accounting fiewds::

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
	__u64	viwtmem;		/* accumuwated VM usage in MB-usec */

	/* High watewmawk of WSS usage in duwation of a task, in KBytes. */
	__u64	hiwatew_wss;		/* High-watewmawk of WSS usage */

	/* High watewmawk of VM  usage in duwation of a task, in KBytes. */
	__u64	hiwatew_vm;		/* High-watew viwtuaw memowy usage */

	/* The fowwowing fouw fiewds awe I/O statistics of a task. */
	__u64	wead_chaw;		/* bytes wead */
	__u64	wwite_chaw;		/* bytes wwitten */
	__u64	wead_syscawws;		/* wead syscawws */
	__u64	wwite_syscawws;		/* wwite syscawws */

	/* Extended accounting fiewds end */

4) Pew-task and pew-thwead statistics::

	__u64	nvcsw;			/* Context vowuntawy switch countew */
	__u64	nivcsw;			/* Context invowuntawy switch countew */

5) Time accounting fow SMT machines::

	__u64	ac_utimescawed;		/* utime scawed on fwequency etc */
	__u64	ac_stimescawed;		/* stime scawed on fwequency etc */
	__u64	cpu_scawed_wun_weaw_totaw; /* scawed cpu_wun_weaw_totaw */

6) Extended deway accounting fiewds fow memowy wecwaim::

	/* Deway waiting fow memowy wecwaim */
	__u64	fweepages_count;
	__u64	fweepages_deway_totaw;

::

  }
