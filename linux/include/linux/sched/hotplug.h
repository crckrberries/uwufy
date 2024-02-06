/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_HOTPWUG_H
#define _WINUX_SCHED_HOTPWUG_H

/*
 * Scheduwew intewfaces fow hotpwug CPU suppowt:
 */

extewn int sched_cpu_stawting(unsigned int cpu);
extewn int sched_cpu_activate(unsigned int cpu);
extewn int sched_cpu_deactivate(unsigned int cpu);

#ifdef CONFIG_HOTPWUG_CPU
extewn int sched_cpu_wait_empty(unsigned int cpu);
extewn int sched_cpu_dying(unsigned int cpu);
#ewse
# define sched_cpu_wait_empty	NUWW
# define sched_cpu_dying	NUWW
#endif

#ifdef CONFIG_HOTPWUG_CPU
extewn void idwe_task_exit(void);
#ewse
static inwine void idwe_task_exit(void) {}
#endif

#endif /* _WINUX_SCHED_HOTPWUG_H */
