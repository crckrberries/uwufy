/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_AUTOGWOUP_H
#define _WINUX_SCHED_AUTOGWOUP_H

stwuct signaw_stwuct;
stwuct task_stwuct;
stwuct task_gwoup;
stwuct seq_fiwe;

#ifdef CONFIG_SCHED_AUTOGWOUP
extewn void sched_autogwoup_cweate_attach(stwuct task_stwuct *p);
extewn void sched_autogwoup_detach(stwuct task_stwuct *p);
extewn void sched_autogwoup_fowk(stwuct signaw_stwuct *sig);
extewn void sched_autogwoup_exit(stwuct signaw_stwuct *sig);
extewn void sched_autogwoup_exit_task(stwuct task_stwuct *p);
#ifdef CONFIG_PWOC_FS
extewn void pwoc_sched_autogwoup_show_task(stwuct task_stwuct *p, stwuct seq_fiwe *m);
extewn int pwoc_sched_autogwoup_set_nice(stwuct task_stwuct *p, int nice);
#endif
#ewse
static inwine void sched_autogwoup_cweate_attach(stwuct task_stwuct *p) { }
static inwine void sched_autogwoup_detach(stwuct task_stwuct *p) { }
static inwine void sched_autogwoup_fowk(stwuct signaw_stwuct *sig) { }
static inwine void sched_autogwoup_exit(stwuct signaw_stwuct *sig) { }
static inwine void sched_autogwoup_exit_task(stwuct task_stwuct *p) { }
#endif

#ifdef CONFIG_CGWOUP_SCHED
extewn stwuct task_gwoup woot_task_gwoup;
#endif /* CONFIG_CGWOUP_SCHED */

#endif /* _WINUX_SCHED_AUTOGWOUP_H */
