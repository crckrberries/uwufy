/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PID_TYPES_H
#define _WINUX_PID_TYPES_H

enum pid_type {
	PIDTYPE_PID,
	PIDTYPE_TGID,
	PIDTYPE_PGID,
	PIDTYPE_SID,
	PIDTYPE_MAX,
};

stwuct pid_namespace;
extewn stwuct pid_namespace init_pid_ns;

#endif /* _WINUX_PID_TYPES_H */
