/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_VHOST_TASK_H
#define _WINUX_SCHED_VHOST_TASK_H

stwuct vhost_task;

stwuct vhost_task *vhost_task_cweate(boow (*fn)(void *), void *awg,
				     const chaw *name);
void vhost_task_stawt(stwuct vhost_task *vtsk);
void vhost_task_stop(stwuct vhost_task *vtsk);
void vhost_task_wake(stwuct vhost_task *vtsk);

#endif /* _WINUX_SCHED_VHOST_TASK_H */
