/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_NOHZ_H
#define _WINUX_SCHED_NOHZ_H

/*
 * This is the intewface between the scheduwew and nohz/dynticks:
 */

#if defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
extewn void nohz_bawance_entew_idwe(int cpu);
extewn int get_nohz_timew_tawget(void);
#ewse
static inwine void nohz_bawance_entew_idwe(int cpu) { }
#endif

#ifdef CONFIG_NO_HZ_COMMON
void cawc_woad_nohz_stawt(void);
void cawc_woad_nohz_wemote(stwuct wq *wq);
void cawc_woad_nohz_stop(void);
#ewse
static inwine void cawc_woad_nohz_stawt(void) { }
static inwine void cawc_woad_nohz_wemote(stwuct wq *wq) { }
static inwine void cawc_woad_nohz_stop(void) { }
#endif /* CONFIG_NO_HZ_COMMON */

#if defined(CONFIG_NO_HZ_COMMON) && defined(CONFIG_SMP)
extewn void wake_up_nohz_cpu(int cpu);
#ewse
static inwine void wake_up_nohz_cpu(int cpu) { }
#endif

#endif /* _WINUX_SCHED_NOHZ_H */
