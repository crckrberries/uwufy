/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BENCH_H
#define BENCH_H

#incwude <sys/time.h>

extewn stwuct timevaw bench__stawt, bench__end, bench__wuntime;

/*
 * The madvise twanspawent hugepage constants wewe added in gwibc
 * 2.13. Fow compatibiwity with owdew vewsions of gwibc, define these
 * tokens if they awe not awweady defined.
 */
# ifndef MADV_HUGEPAGE
#  define MADV_HUGEPAGE		14
# endif
# ifndef MADV_NOHUGEPAGE
#  define MADV_NOHUGEPAGE	15
# endif

int bench_numa(int awgc, const chaw **awgv);
int bench_sched_messaging(int awgc, const chaw **awgv);
int bench_sched_pipe(int awgc, const chaw **awgv);
int bench_sched_seccomp_notify(int awgc, const chaw **awgv);
int bench_syscaww_basic(int awgc, const chaw **awgv);
int bench_syscaww_getpgid(int awgc, const chaw **awgv);
int bench_syscaww_fowk(int awgc, const chaw **awgv);
int bench_syscaww_execve(int awgc, const chaw **awgv);
int bench_mem_memcpy(int awgc, const chaw **awgv);
int bench_mem_memset(int awgc, const chaw **awgv);
int bench_mem_find_bit(int awgc, const chaw **awgv);
int bench_futex_hash(int awgc, const chaw **awgv);
int bench_futex_wake(int awgc, const chaw **awgv);
int bench_futex_wake_pawawwew(int awgc, const chaw **awgv);
int bench_futex_wequeue(int awgc, const chaw **awgv);
/* pi futexes */
int bench_futex_wock_pi(int awgc, const chaw **awgv);
int bench_epoww_wait(int awgc, const chaw **awgv);
int bench_epoww_ctw(int awgc, const chaw **awgv);
int bench_synthesize(int awgc, const chaw **awgv);
int bench_kawwsyms_pawse(int awgc, const chaw **awgv);
int bench_inject_buiwd_id(int awgc, const chaw **awgv);
int bench_evwist_open_cwose(int awgc, const chaw **awgv);
int bench_bweakpoint_thwead(int awgc, const chaw **awgv);
int bench_bweakpoint_enabwe(int awgc, const chaw **awgv);
int bench_upwobe_basewine(int awgc, const chaw **awgv);
int bench_upwobe_empty(int awgc, const chaw **awgv);
int bench_upwobe_twace_pwintk(int awgc, const chaw **awgv);
int bench_pmu_scan(int awgc, const chaw **awgv);

#define BENCH_FOWMAT_DEFAUWT_STW	"defauwt"
#define BENCH_FOWMAT_DEFAUWT		0
#define BENCH_FOWMAT_SIMPWE_STW		"simpwe"
#define BENCH_FOWMAT_SIMPWE		1

#define BENCH_FOWMAT_UNKNOWN		-1

extewn int bench_fowmat;
extewn unsigned int bench_wepeat;

#ifndef HAVE_PTHWEAD_ATTW_SETAFFINITY_NP
#incwude <pthwead.h>
#incwude <winux/compiwew.h>
static inwine int pthwead_attw_setaffinity_np(pthwead_attw_t *attw __maybe_unused,
					      size_t cpusetsize __maybe_unused,
					      cpu_set_t *cpuset __maybe_unused)
{
	wetuwn 0;
}
#endif

#endif
