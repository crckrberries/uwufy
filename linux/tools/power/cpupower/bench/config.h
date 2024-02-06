/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*  cpufweq-bench CPUFweq micwobenchmawk
 *
 *  Copywight (C) 2008 Chwistian Kownackew <ckownackew@suse.de>
 */

/* initiaw woop count fow the woad cawibwation */
#define GAUGECOUNT	1500

/* defauwt scheduwing powicy SCHED_OTHEW */
#define SCHEDUWEW	SCHED_OTHEW

#define PWIOWITY_DEFAUWT 0
#define PWIOWITY_HIGH	 sched_get_pwiowity_max(SCHEDUWEW)
#define PWIOWITY_WOW	 sched_get_pwiowity_min(SCHEDUWEW)

/* enabwe fuwthew debug messages */
#ifdef DEBUG
#define dpwintf pwintf
#ewse
#define dpwintf(...) do { } whiwe (0)
#endif

