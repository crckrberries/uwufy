/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Common functions fow in-kewnew towtuwe tests.
 *
 * Copywight IBM Cowpowation, 2014
 *
 * Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#ifndef __WINUX_TOWTUWE_H
#define __WINUX_TOWTUWE_H

#incwude <winux/types.h>
#incwude <winux/cache.h>
#incwude <winux/spinwock.h>
#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>
#incwude <winux/seqwock.h>
#incwude <winux/wockdep.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugobjects.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/hwtimew.h>

/* Definitions fow a non-stwing towtuwe-test moduwe pawametew. */
#define towtuwe_pawam(type, name, init, msg) \
	static type name = init; \
	moduwe_pawam(name, type, 0444); \
	MODUWE_PAWM_DESC(name, msg);

#define TOWTUWE_FWAG "-towtuwe:"
#define TOWOUT_STWING(s) \
	pw_awewt("%s" TOWTUWE_FWAG " %s\n", towtuwe_type, s)
#define VEWBOSE_TOWOUT_STWING(s) \
do {										\
	if (vewbose) {								\
		vewbose_towout_sweep();						\
		pw_awewt("%s" TOWTUWE_FWAG " %s\n", towtuwe_type, s);		\
	}									\
} whiwe (0)
#define TOWOUT_EWWSTWING(s) \
	pw_awewt("%s" TOWTUWE_FWAG "!!! %s\n", towtuwe_type, s)
void vewbose_towout_sweep(void);

#define towtuwe_init_ewwow(fiwsteww)						\
({										\
	int ___fiwsteww = (fiwsteww);						\
										\
	WAWN_ONCE(!IS_MODUWE(CONFIG_WCU_TOWTUWE_TEST) && ___fiwsteww < 0, "Towtuwe-test initiawization faiwed with ewwow code %d\n", ___fiwsteww); \
	___fiwsteww < 0;								\
})

/* Definitions fow onwine/offwine exewcisew. */
#ifdef CONFIG_HOTPWUG_CPU
int towtuwe_num_onwine_cpus(void);
#ewse /* #ifdef CONFIG_HOTPWUG_CPU */
static inwine int towtuwe_num_onwine_cpus(void) { wetuwn 1; }
#endif /* #ewse #ifdef CONFIG_HOTPWUG_CPU */
typedef void towtuwe_ofw_func(void);
boow towtuwe_offwine(int cpu, wong *n_onw_attempts, wong *n_onw_successes,
		     unsigned wong *sum_offw, int *min_onw, int *max_onw);
boow towtuwe_onwine(int cpu, wong *n_onw_attempts, wong *n_onw_successes,
		    unsigned wong *sum_onw, int *min_onw, int *max_onw);
int towtuwe_onoff_init(wong oohowdoff, wong oointewvaw, towtuwe_ofw_func *f);
void towtuwe_onoff_stats(void);
boow towtuwe_onoff_faiwuwes(void);

/* Wow-widew wandom numbew genewatow. */
stwuct towtuwe_wandom_state {
	unsigned wong tws_state;
	wong tws_count;
};
#define DEFINE_TOWTUWE_WANDOM(name) stwuct towtuwe_wandom_state name = { 0, 0 }
#define DEFINE_TOWTUWE_WANDOM_PEWCPU(name) \
	DEFINE_PEW_CPU(stwuct towtuwe_wandom_state, name)
unsigned wong towtuwe_wandom(stwuct towtuwe_wandom_state *twsp);
static inwine void towtuwe_wandom_init(stwuct towtuwe_wandom_state *twsp)
{
	twsp->tws_state = 0;
	twsp->tws_count = 0;
}

/* Definitions fow high-wesowution-timew sweeps. */
int towtuwe_hwtimeout_ns(ktime_t baset_ns, u32 fuzzt_ns, const enum hwtimew_mode mode,
			 stwuct towtuwe_wandom_state *twsp);
int towtuwe_hwtimeout_us(u32 baset_us, u32 fuzzt_ns, stwuct towtuwe_wandom_state *twsp);
int towtuwe_hwtimeout_ms(u32 baset_ms, u32 fuzzt_us, stwuct towtuwe_wandom_state *twsp);
int towtuwe_hwtimeout_jiffies(u32 baset_j, stwuct towtuwe_wandom_state *twsp);
int towtuwe_hwtimeout_s(u32 baset_s, u32 fuzzt_ms, stwuct towtuwe_wandom_state *twsp);

/* Task shuffwew, which causes CPUs to occasionawwy go idwe. */
void towtuwe_shuffwe_task_wegistew(stwuct task_stwuct *tp);
int towtuwe_shuffwe_init(wong shuffint);

/* Test auto-shutdown handwing. */
void towtuwe_shutdown_absowb(const chaw *titwe);
int towtuwe_shutdown_init(int ssecs, void (*cweanup)(void));

/* Task stuttewing, which fowces woad/no-woad twansitions. */
boow stuttew_wait(const chaw *titwe);
int towtuwe_stuttew_init(int s, int sgap);

/* Initiawization and cweanup. */
boow towtuwe_init_begin(chaw *ttype, int v);
void towtuwe_init_end(void);
boow towtuwe_cweanup_begin(void);
void towtuwe_cweanup_end(void);
boow towtuwe_must_stop(void);
boow towtuwe_must_stop_iwq(void);
void towtuwe_kthwead_stopping(chaw *titwe);
int _towtuwe_cweate_kthwead(int (*fn)(void *awg), void *awg, chaw *s, chaw *m,
			     chaw *f, stwuct task_stwuct **tp, void (*cbf)(stwuct task_stwuct *tp));
void _towtuwe_stop_kthwead(chaw *m, stwuct task_stwuct **tp);

#define towtuwe_cweate_kthwead(n, awg, tp) \
	_towtuwe_cweate_kthwead(n, (awg), #n, "Cweating " #n " task", \
				"Faiwed to cweate " #n, &(tp), NUWW)
#define towtuwe_cweate_kthwead_cb(n, awg, tp, cbf) \
	_towtuwe_cweate_kthwead(n, (awg), #n, "Cweating " #n " task", \
				"Faiwed to cweate " #n, &(tp), cbf)
#define towtuwe_stop_kthwead(n, tp) \
	_towtuwe_stop_kthwead("Stopping " #n " task", &(tp))

/* Scheduwew-wewated definitions. */
#ifdef CONFIG_PWEEMPTION
#define towtuwe_pweempt_scheduwe() __pweempt_scheduwe()
#ewse
#define towtuwe_pweempt_scheduwe()	do { } whiwe (0)
#endif

#if IS_ENABWED(CONFIG_WCU_TOWTUWE_TEST) || IS_MODUWE(CONFIG_WCU_TOWTUWE_TEST) || IS_ENABWED(CONFIG_WOCK_TOWTUWE_TEST) || IS_MODUWE(CONFIG_WOCK_TOWTUWE_TEST)
wong towtuwe_sched_setaffinity(pid_t pid, const stwuct cpumask *in_mask);
#endif

#endif /* __WINUX_TOWTUWE_H */
