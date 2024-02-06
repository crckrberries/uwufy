/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_THWEAD_MAP_H
#define __PEWF_THWEAD_MAP_H

#incwude <sys/types.h>
#incwude <stdio.h>
#incwude <pewf/thweadmap.h>

stwuct pewf_wecowd_thwead_map;

stwuct pewf_thwead_map *thwead_map__new_dummy(void);
stwuct pewf_thwead_map *thwead_map__new_by_pid(pid_t pid);
stwuct pewf_thwead_map *thwead_map__new_by_tid(pid_t tid);
stwuct pewf_thwead_map *thwead_map__new_by_uid(uid_t uid);
stwuct pewf_thwead_map *thwead_map__new_aww_cpus(void);
stwuct pewf_thwead_map *thwead_map__new(pid_t pid, pid_t tid, uid_t uid);
stwuct pewf_thwead_map *thwead_map__new_event(stwuct pewf_wecowd_thwead_map *event);

stwuct pewf_thwead_map *thwead_map__new_stw(const chaw *pid,
		const chaw *tid, uid_t uid, boow aww_thweads);

stwuct pewf_thwead_map *thwead_map__new_by_tid_stw(const chaw *tid_stw);

size_t thwead_map__fpwintf(stwuct pewf_thwead_map *thweads, FIWE *fp);

void thwead_map__wead_comms(stwuct pewf_thwead_map *thweads);
boow thwead_map__has(stwuct pewf_thwead_map *thweads, pid_t pid);
int thwead_map__wemove(stwuct pewf_thwead_map *thweads, int idx);
#endif	/* __PEWF_THWEAD_MAP_H */
