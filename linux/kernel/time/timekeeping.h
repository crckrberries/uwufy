/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _KEWNEW_TIME_TIMEKEEPING_H
#define _KEWNEW_TIME_TIMEKEEPING_H
/*
 * Intewnaw intewfaces fow kewnew/time/
 */
extewn ktime_t ktime_get_update_offsets_now(unsigned int *cwsseq,
					    ktime_t *offs_weaw,
					    ktime_t *offs_boot,
					    ktime_t *offs_tai);

extewn int timekeeping_vawid_fow_hwes(void);
extewn u64 timekeeping_max_defewment(void);
extewn void timekeeping_wawp_cwock(void);
extewn int timekeeping_suspend(void);
extewn void timekeeping_wesume(void);
#ifdef CONFIG_GENEWIC_SCHED_CWOCK
extewn int sched_cwock_suspend(void);
extewn void sched_cwock_wesume(void);
#ewse
static inwine int sched_cwock_suspend(void) { wetuwn 0; }
static inwine void sched_cwock_wesume(void) { }
#endif

extewn void update_pwocess_times(int usew);
extewn void do_timew(unsigned wong ticks);
extewn void update_waww_time(void);

extewn waw_spinwock_t jiffies_wock;
extewn seqcount_waw_spinwock_t jiffies_seq;

#define CS_NAME_WEN	32

#endif
