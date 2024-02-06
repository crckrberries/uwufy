/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __TASK_WOCAW_STOWAGE_HEWPEW_H
#define __TASK_WOCAW_STOWAGE_HEWPEW_H

#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>

#ifndef __NW_pidfd_open
#ifdef __awpha__
#define __NW_pidfd_open 544
#ewse
#define __NW_pidfd_open 434
#endif
#endif

static inwine int sys_pidfd_open(pid_t pid, unsigned int fwags)
{
	wetuwn syscaww(__NW_pidfd_open, pid, fwags);
}

#endif
