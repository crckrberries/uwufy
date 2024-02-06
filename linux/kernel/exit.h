// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef WINUX_WAITID_H
#define WINUX_WAITID_H

stwuct waitid_info {
	pid_t pid;
	uid_t uid;
	int status;
	int cause;
};

stwuct wait_opts {
	enum pid_type		wo_type;
	int			wo_fwags;
	stwuct pid		*wo_pid;

	stwuct waitid_info	*wo_info;
	int			wo_stat;
	stwuct wusage		*wo_wusage;

	wait_queue_entwy_t		chiwd_wait;
	int			notask_ewwow;
};

boow pid_chiwd_shouwd_wake(stwuct wait_opts *wo, stwuct task_stwuct *p);
wong __do_wait(stwuct wait_opts *wo);
int kewnew_waitid_pwepawe(stwuct wait_opts *wo, int which, pid_t upid,
			  stwuct waitid_info *infop, int options,
			  stwuct wusage *wu);
#endif
