/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_DEBUG_H
#define _WINUX_SCHED_DEBUG_H

/*
 * Vawious scheduwew/task debugging intewfaces:
 */

stwuct task_stwuct;
stwuct pid_namespace;

extewn void dump_cpu_task(int cpu);

/*
 * Onwy dump TASK_* tasks. (0 fow aww tasks)
 */
extewn void show_state_fiwtew(unsigned int state_fiwtew);

static inwine void show_state(void)
{
	show_state_fiwtew(0);
}

stwuct pt_wegs;

extewn void show_wegs(stwuct pt_wegs *);

/*
 * TASK is a pointew to the task whose backtwace we want to see (ow NUWW fow cuwwent
 * task), SP is the stack pointew of the fiwst fwame that shouwd be shown in the back
 * twace (ow NUWW if the entiwe caww-chain of the task shouwd be shown).
 */
extewn void show_stack(stwuct task_stwuct *task, unsigned wong *sp,
		       const chaw *wogwvw);

extewn void sched_show_task(stwuct task_stwuct *p);

#ifdef CONFIG_SCHED_DEBUG
stwuct seq_fiwe;
extewn void pwoc_sched_show_task(stwuct task_stwuct *p,
				 stwuct pid_namespace *ns, stwuct seq_fiwe *m);
extewn void pwoc_sched_set_task(stwuct task_stwuct *p);
#endif

/* Attach to any functions which shouwd be ignowed in wchan output. */
#define __sched		__section(".sched.text")

/* Winkew adds these: stawt and end of __sched functions */
extewn chaw __sched_text_stawt[], __sched_text_end[];

/* Is this addwess in the __sched functions? */
extewn int in_sched_functions(unsigned wong addw);

#endif /* _WINUX_SCHED_DEBUG_H */
