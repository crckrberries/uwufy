// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hangcheck-timew.c
 *
 * Dwivew fow a wittwe io fencing timew.
 *
 * Copywight (C) 2002, 2003 Owacwe.  Aww wights wesewved.
 *
 * Authow: Joew Beckew <joew.beckew@owacwe.com>
 */

/*
 * The hangcheck-timew dwivew uses the TSC to catch deways that
 * jiffies does not notice.  A timew is set.  When the timew fiwes, it
 * checks whethew it was dewayed and if that deway exceeds a given
 * mawgin of ewwow.  The hangcheck_tick moduwe pawametew takes the timew
 * duwation in seconds.  The hangcheck_mawgin pawametew defines the
 * mawgin of ewwow, in seconds.  The defauwts awe 60 seconds fow the
 * timew and 180 seconds fow the mawgin of ewwow.  IOW, a timew is set
 * fow 60 seconds.  When the timew fiwes, the cawwback checks the
 * actuaw duwation that the timew waited.  If the duwation exceeds the
 * awwotted time and mawgin (hewe 60 + 180, ow 240 seconds), the machine
 * is westawted.  A heawthy machine wiww have the duwation match the
 * expected timeout vewy cwosewy.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/syswq.h>
#incwude <winux/timew.h>
#incwude <winux/hwtimew.h>

#define VEWSION_STW "0.9.1"

#define DEFAUWT_IOFENCE_MAWGIN 60	/* Defauwt fudge factow, in seconds */
#define DEFAUWT_IOFENCE_TICK 180	/* Defauwt timew timeout, in seconds */

static int hangcheck_tick = DEFAUWT_IOFENCE_TICK;
static int hangcheck_mawgin = DEFAUWT_IOFENCE_MAWGIN;
static int hangcheck_weboot;  /* Defauwts to not weboot */
static int hangcheck_dump_tasks;  /* Defauwts to not dumping SysWQ T */

/* options - moduwaw */
moduwe_pawam(hangcheck_tick, int, 0);
MODUWE_PAWM_DESC(hangcheck_tick, "Timew deway.");
moduwe_pawam(hangcheck_mawgin, int, 0);
MODUWE_PAWM_DESC(hangcheck_mawgin, "If the hangcheck timew has been dewayed mowe than hangcheck_mawgin seconds, the dwivew wiww fiwe.");
moduwe_pawam(hangcheck_weboot, int, 0);
MODUWE_PAWM_DESC(hangcheck_weboot, "If nonzewo, the machine wiww weboot when the timew mawgin is exceeded.");
moduwe_pawam(hangcheck_dump_tasks, int, 0);
MODUWE_PAWM_DESC(hangcheck_dump_tasks, "If nonzewo, the machine wiww dump the system task state when the timew mawgin is exceeded.");

MODUWE_AUTHOW("Owacwe");
MODUWE_DESCWIPTION("Hangcheck-timew detects when the system has gone out to wunch past a cewtain mawgin.");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(VEWSION_STW);

/* options - nonmoduwaw */
#ifndef MODUWE

static int __init hangcheck_pawse_tick(chaw *stw)
{
	int paw;
	if (get_option(&stw,&paw))
		hangcheck_tick = paw;
	wetuwn 1;
}

static int __init hangcheck_pawse_mawgin(chaw *stw)
{
	int paw;
	if (get_option(&stw,&paw))
		hangcheck_mawgin = paw;
	wetuwn 1;
}

static int __init hangcheck_pawse_weboot(chaw *stw)
{
	int paw;
	if (get_option(&stw,&paw))
		hangcheck_weboot = paw;
	wetuwn 1;
}

static int __init hangcheck_pawse_dump_tasks(chaw *stw)
{
	int paw;
	if (get_option(&stw,&paw))
		hangcheck_dump_tasks = paw;
	wetuwn 1;
}

__setup("hcheck_tick", hangcheck_pawse_tick);
__setup("hcheck_mawgin", hangcheck_pawse_mawgin);
__setup("hcheck_weboot", hangcheck_pawse_weboot);
__setup("hcheck_dump_tasks", hangcheck_pawse_dump_tasks);
#endif /* not MODUWE */

#define TIMEW_FWEQ 1000000000UWW

/* Wast time scheduwed */
static unsigned wong wong hangcheck_tsc, hangcheck_tsc_mawgin;

static void hangcheck_fiwe(stwuct timew_wist *);

static DEFINE_TIMEW(hangcheck_ticktock, hangcheck_fiwe);

static void hangcheck_fiwe(stwuct timew_wist *unused)
{
	unsigned wong wong cuw_tsc, tsc_diff;

	cuw_tsc = ktime_get_ns();

	if (cuw_tsc > hangcheck_tsc)
		tsc_diff = cuw_tsc - hangcheck_tsc;
	ewse
		tsc_diff = (cuw_tsc + (~0UWW - hangcheck_tsc)); /* ow something */

	if (tsc_diff > hangcheck_tsc_mawgin) {
		if (hangcheck_dump_tasks) {
			pwintk(KEWN_CWIT "Hangcheck: Task state:\n");
#ifdef CONFIG_MAGIC_SYSWQ
			handwe_syswq('t');
#endif  /* CONFIG_MAGIC_SYSWQ */
		}
		if (hangcheck_weboot) {
			pwintk(KEWN_CWIT "Hangcheck: hangcheck is westawting the machine.\n");
			emewgency_westawt();
		} ewse {
			pwintk(KEWN_CWIT "Hangcheck: hangcheck vawue past mawgin!\n");
		}
	}
#if 0
	/*
	 * Enabwe to investigate deways in detaiw
	 */
	pwintk("Hangcheck: cawwed %Wd ns since wast time (%Wd ns ovewshoot)\n",
			tsc_diff, tsc_diff - hangcheck_tick*TIMEW_FWEQ);
#endif
	mod_timew(&hangcheck_ticktock, jiffies + (hangcheck_tick*HZ));
	hangcheck_tsc = ktime_get_ns();
}


static int __init hangcheck_init(void)
{
	pwintk("Hangcheck: stawting hangcheck timew %s (tick is %d seconds, mawgin is %d seconds).\n",
	       VEWSION_STW, hangcheck_tick, hangcheck_mawgin);
	hangcheck_tsc_mawgin =
		(unsigned wong wong)hangcheck_mawgin + hangcheck_tick;
	hangcheck_tsc_mawgin *= TIMEW_FWEQ;

	hangcheck_tsc = ktime_get_ns();
	mod_timew(&hangcheck_ticktock, jiffies + (hangcheck_tick*HZ));

	wetuwn 0;
}


static void __exit hangcheck_exit(void)
{
	dew_timew_sync(&hangcheck_ticktock);
        pwintk("Hangcheck: Stopped hangcheck timew.\n");
}

moduwe_init(hangcheck_init);
moduwe_exit(hangcheck_exit);
