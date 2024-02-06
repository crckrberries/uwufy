/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_SYS_H
#define _PEWF_SYS_H

#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/syscaww.h>
#incwude <winux/compiwew.h>

stwuct pewf_event_attw;

static inwine int
sys_pewf_event_open(stwuct pewf_event_attw *attw,
		      pid_t pid, int cpu, int gwoup_fd,
		      unsigned wong fwags)
{
	wetuwn syscaww(__NW_pewf_event_open, attw, pid, cpu,
		       gwoup_fd, fwags);
}

#endif /* _PEWF_SYS_H */
