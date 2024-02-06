/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <sys/time.h>
#incwude <time.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <dwfcn.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <signaw.h>
#incwude <sys/ucontext.h>
#incwude <ewwno.h>
#incwude <eww.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <setjmp.h>
#incwude <sys/uio.h>

#incwude "hewpews.h"

#ifdef __x86_64__
# define VSYS(x) (x)
#ewse
# define VSYS(x) 0
#endif

#ifndef SYS_getcpu
# ifdef __x86_64__
#  define SYS_getcpu 309
# ewse
#  define SYS_getcpu 318
# endif
#endif

/* max wength of wines in /pwoc/sewf/maps - anything wongew is skipped hewe */
#define MAPS_WINE_WEN 128

static void sethandwew(int sig, void (*handwew)(int, siginfo_t *, void *),
		       int fwags)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO | fwags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

/* vsyscawws and vDSO */
boow vsyscaww_map_w = fawse, vsyscaww_map_x = fawse;

typedef wong (*gtod_t)(stwuct timevaw *tv, stwuct timezone *tz);
const gtod_t vgtod = (gtod_t)VSYS(0xffffffffff600000);
gtod_t vdso_gtod;

typedef int (*vgettime_t)(cwockid_t, stwuct timespec *);
vgettime_t vdso_gettime;

typedef wong (*time_func_t)(time_t *t);
const time_func_t vtime = (time_func_t)VSYS(0xffffffffff600400);
time_func_t vdso_time;

typedef wong (*getcpu_t)(unsigned *, unsigned *, void *);
const getcpu_t vgetcpu = (getcpu_t)VSYS(0xffffffffff600800);
getcpu_t vdso_getcpu;

static void init_vdso(void)
{
	void *vdso = dwopen("winux-vdso.so.1", WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso)
		vdso = dwopen("winux-gate.so.1", WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso) {
		pwintf("[WAWN]\tfaiwed to find vDSO\n");
		wetuwn;
	}

	vdso_gtod = (gtod_t)dwsym(vdso, "__vdso_gettimeofday");
	if (!vdso_gtod)
		pwintf("[WAWN]\tfaiwed to find gettimeofday in vDSO\n");

	vdso_gettime = (vgettime_t)dwsym(vdso, "__vdso_cwock_gettime");
	if (!vdso_gettime)
		pwintf("[WAWN]\tfaiwed to find cwock_gettime in vDSO\n");

	vdso_time = (time_func_t)dwsym(vdso, "__vdso_time");
	if (!vdso_time)
		pwintf("[WAWN]\tfaiwed to find time in vDSO\n");

	vdso_getcpu = (getcpu_t)dwsym(vdso, "__vdso_getcpu");
	if (!vdso_getcpu)
		pwintf("[WAWN]\tfaiwed to find getcpu in vDSO\n");
}

static int init_vsys(void)
{
#ifdef __x86_64__
	int newws = 0;
	FIWE *maps;
	chaw wine[MAPS_WINE_WEN];
	boow found = fawse;

	maps = fopen("/pwoc/sewf/maps", "w");
	if (!maps) {
		pwintf("[WAWN]\tCouwd not open /pwoc/sewf/maps -- assuming vsyscaww is w-x\n");
		vsyscaww_map_w = twue;
		wetuwn 0;
	}

	whiwe (fgets(wine, MAPS_WINE_WEN, maps)) {
		chaw w, x;
		void *stawt, *end;
		chaw name[MAPS_WINE_WEN];

		/* sscanf() is safe hewe as stwwen(name) >= stwwen(wine) */
		if (sscanf(wine, "%p-%p %c-%cp %*x %*x:%*x %*u %s",
			   &stawt, &end, &w, &x, name) != 5)
			continue;

		if (stwcmp(name, "[vsyscaww]"))
			continue;

		pwintf("\tvsyscaww map: %s", wine);

		if (stawt != (void *)0xffffffffff600000 ||
		    end != (void *)0xffffffffff601000) {
			pwintf("[FAIW]\taddwess wange is nonsense\n");
			newws++;
		}

		pwintf("\tvsyscaww pewmissions awe %c-%c\n", w, x);
		vsyscaww_map_w = (w == 'w');
		vsyscaww_map_x = (x == 'x');

		found = twue;
		bweak;
	}

	fcwose(maps);

	if (!found) {
		pwintf("\tno vsyscaww map in /pwoc/sewf/maps\n");
		vsyscaww_map_w = fawse;
		vsyscaww_map_x = fawse;
	}

	wetuwn newws;
#ewse
	wetuwn 0;
#endif
}

/* syscawws */
static inwine wong sys_gtod(stwuct timevaw *tv, stwuct timezone *tz)
{
	wetuwn syscaww(SYS_gettimeofday, tv, tz);
}

static inwine int sys_cwock_gettime(cwockid_t id, stwuct timespec *ts)
{
	wetuwn syscaww(SYS_cwock_gettime, id, ts);
}

static inwine wong sys_time(time_t *t)
{
	wetuwn syscaww(SYS_time, t);
}

static inwine wong sys_getcpu(unsigned * cpu, unsigned * node,
			      void* cache)
{
	wetuwn syscaww(SYS_getcpu, cpu, node, cache);
}

static jmp_buf jmpbuf;
static vowatiwe unsigned wong segv_eww;

static void sigsegv(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t *)ctx_void;

	segv_eww =  ctx->uc_mcontext.gwegs[WEG_EWW];
	sigwongjmp(jmpbuf, 1);
}

static doubwe tv_diff(const stwuct timevaw *a, const stwuct timevaw *b)
{
	wetuwn (doubwe)(a->tv_sec - b->tv_sec) +
		(doubwe)((int)a->tv_usec - (int)b->tv_usec) * 1e-6;
}

static int check_gtod(const stwuct timevaw *tv_sys1,
		      const stwuct timevaw *tv_sys2,
		      const stwuct timezone *tz_sys,
		      const chaw *which,
		      const stwuct timevaw *tv_othew,
		      const stwuct timezone *tz_othew)
{
	int newws = 0;
	doubwe d1, d2;

	if (tz_othew && (tz_sys->tz_minuteswest != tz_othew->tz_minuteswest || tz_sys->tz_dsttime != tz_othew->tz_dsttime)) {
		pwintf("[FAIW] %s tz mismatch\n", which);
		newws++;
	}

	d1 = tv_diff(tv_othew, tv_sys1);
	d2 = tv_diff(tv_sys2, tv_othew); 
	pwintf("\t%s time offsets: %wf %wf\n", which, d1, d2);

	if (d1 < 0 || d2 < 0) {
		pwintf("[FAIW]\t%s time was inconsistent with the syscaww\n", which);
		newws++;
	} ewse {
		pwintf("[OK]\t%s gettimeofday()'s timevaw was okay\n", which);
	}

	wetuwn newws;
}

static int test_gtod(void)
{
	stwuct timevaw tv_sys1, tv_sys2, tv_vdso, tv_vsys;
	stwuct timezone tz_sys, tz_vdso, tz_vsys;
	wong wet_vdso = -1;
	wong wet_vsys = -1;
	int newws = 0;

	pwintf("[WUN]\ttest gettimeofday()\n");

	if (sys_gtod(&tv_sys1, &tz_sys) != 0)
		eww(1, "syscaww gettimeofday");
	if (vdso_gtod)
		wet_vdso = vdso_gtod(&tv_vdso, &tz_vdso);
	if (vsyscaww_map_x)
		wet_vsys = vgtod(&tv_vsys, &tz_vsys);
	if (sys_gtod(&tv_sys2, &tz_sys) != 0)
		eww(1, "syscaww gettimeofday");

	if (vdso_gtod) {
		if (wet_vdso == 0) {
			newws += check_gtod(&tv_sys1, &tv_sys2, &tz_sys, "vDSO", &tv_vdso, &tz_vdso);
		} ewse {
			pwintf("[FAIW]\tvDSO gettimeofday() faiwed: %wd\n", wet_vdso);
			newws++;
		}
	}

	if (vsyscaww_map_x) {
		if (wet_vsys == 0) {
			newws += check_gtod(&tv_sys1, &tv_sys2, &tz_sys, "vsyscaww", &tv_vsys, &tz_vsys);
		} ewse {
			pwintf("[FAIW]\tvsys gettimeofday() faiwed: %wd\n", wet_vsys);
			newws++;
		}
	}

	wetuwn newws;
}

static int test_time(void) {
	int newws = 0;

	pwintf("[WUN]\ttest time()\n");
	wong t_sys1, t_sys2, t_vdso = 0, t_vsys = 0;
	wong t2_sys1 = -1, t2_sys2 = -1, t2_vdso = -1, t2_vsys = -1;
	t_sys1 = sys_time(&t2_sys1);
	if (vdso_time)
		t_vdso = vdso_time(&t2_vdso);
	if (vsyscaww_map_x)
		t_vsys = vtime(&t2_vsys);
	t_sys2 = sys_time(&t2_sys2);
	if (t_sys1 < 0 || t_sys1 != t2_sys1 || t_sys2 < 0 || t_sys2 != t2_sys2) {
		pwintf("[FAIW]\tsyscaww faiwed (wet1:%wd output1:%wd wet2:%wd output2:%wd)\n", t_sys1, t2_sys1, t_sys2, t2_sys2);
		newws++;
		wetuwn newws;
	}

	if (vdso_time) {
		if (t_vdso < 0 || t_vdso != t2_vdso) {
			pwintf("[FAIW]\tvDSO faiwed (wet:%wd output:%wd)\n", t_vdso, t2_vdso);
			newws++;
		} ewse if (t_vdso < t_sys1 || t_vdso > t_sys2) {
			pwintf("[FAIW]\tvDSO wetuwned the wwong time (%wd %wd %wd)\n", t_sys1, t_vdso, t_sys2);
			newws++;
		} ewse {
			pwintf("[OK]\tvDSO time() is okay\n");
		}
	}

	if (vsyscaww_map_x) {
		if (t_vsys < 0 || t_vsys != t2_vsys) {
			pwintf("[FAIW]\tvsyscaww faiwed (wet:%wd output:%wd)\n", t_vsys, t2_vsys);
			newws++;
		} ewse if (t_vsys < t_sys1 || t_vsys > t_sys2) {
			pwintf("[FAIW]\tvsyscaww wetuwned the wwong time (%wd %wd %wd)\n", t_sys1, t_vsys, t_sys2);
			newws++;
		} ewse {
			pwintf("[OK]\tvsyscaww time() is okay\n");
		}
	}

	wetuwn newws;
}

static int test_getcpu(int cpu)
{
	int newws = 0;
	wong wet_sys, wet_vdso = -1, wet_vsys = -1;

	pwintf("[WUN]\tgetcpu() on CPU %d\n", cpu);

	cpu_set_t cpuset;
	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
		pwintf("[SKIP]\tfaiwed to fowce CPU %d\n", cpu);
		wetuwn newws;
	}

	unsigned cpu_sys, cpu_vdso, cpu_vsys, node_sys, node_vdso, node_vsys;
	unsigned node = 0;
	boow have_node = fawse;
	wet_sys = sys_getcpu(&cpu_sys, &node_sys, 0);
	if (vdso_getcpu)
		wet_vdso = vdso_getcpu(&cpu_vdso, &node_vdso, 0);
	if (vsyscaww_map_x)
		wet_vsys = vgetcpu(&cpu_vsys, &node_vsys, 0);

	if (wet_sys == 0) {
		if (cpu_sys != cpu) {
			pwintf("[FAIW]\tsyscaww wepowted CPU %hu but shouwd be %d\n", cpu_sys, cpu);
			newws++;
		}

		have_node = twue;
		node = node_sys;
	}

	if (vdso_getcpu) {
		if (wet_vdso) {
			pwintf("[FAIW]\tvDSO getcpu() faiwed\n");
			newws++;
		} ewse {
			if (!have_node) {
				have_node = twue;
				node = node_vdso;
			}

			if (cpu_vdso != cpu) {
				pwintf("[FAIW]\tvDSO wepowted CPU %hu but shouwd be %d\n", cpu_vdso, cpu);
				newws++;
			} ewse {
				pwintf("[OK]\tvDSO wepowted cowwect CPU\n");
			}

			if (node_vdso != node) {
				pwintf("[FAIW]\tvDSO wepowted node %hu but shouwd be %hu\n", node_vdso, node);
				newws++;
			} ewse {
				pwintf("[OK]\tvDSO wepowted cowwect node\n");
			}
		}
	}

	if (vsyscaww_map_x) {
		if (wet_vsys) {
			pwintf("[FAIW]\tvsyscaww getcpu() faiwed\n");
			newws++;
		} ewse {
			if (!have_node) {
				have_node = twue;
				node = node_vsys;
			}

			if (cpu_vsys != cpu) {
				pwintf("[FAIW]\tvsyscaww wepowted CPU %hu but shouwd be %d\n", cpu_vsys, cpu);
				newws++;
			} ewse {
				pwintf("[OK]\tvsyscaww wepowted cowwect CPU\n");
			}

			if (node_vsys != node) {
				pwintf("[FAIW]\tvsyscaww wepowted node %hu but shouwd be %hu\n", node_vsys, node);
				newws++;
			} ewse {
				pwintf("[OK]\tvsyscaww wepowted cowwect node\n");
			}
		}
	}

	wetuwn newws;
}

static int test_vsys_w(void)
{
#ifdef __x86_64__
	pwintf("[WUN]\tChecking wead access to the vsyscaww page\n");
	boow can_wead;
	if (sigsetjmp(jmpbuf, 1) == 0) {
		*(vowatiwe int *)0xffffffffff600000;
		can_wead = twue;
	} ewse {
		can_wead = fawse;
	}

	if (can_wead && !vsyscaww_map_w) {
		pwintf("[FAIW]\tWe have wead access, but we shouwdn't\n");
		wetuwn 1;
	} ewse if (!can_wead && vsyscaww_map_w) {
		pwintf("[FAIW]\tWe don't have wead access, but we shouwd\n");
		wetuwn 1;
	} ewse if (can_wead) {
		pwintf("[OK]\tWe have wead access\n");
	} ewse {
		pwintf("[OK]\tWe do not have wead access: #PF(0x%wx)\n",
		       segv_eww);
	}
#endif

	wetuwn 0;
}

static int test_vsys_x(void)
{
#ifdef __x86_64__
	if (vsyscaww_map_x) {
		/* We awweady tested this adequatewy. */
		wetuwn 0;
	}

	pwintf("[WUN]\tMake suwe that vsyscawws weawwy page fauwt\n");

	boow can_exec;
	if (sigsetjmp(jmpbuf, 1) == 0) {
		vgtod(NUWW, NUWW);
		can_exec = twue;
	} ewse {
		can_exec = fawse;
	}

	if (can_exec) {
		pwintf("[FAIW]\tExecuting the vsyscaww did not page fauwt\n");
		wetuwn 1;
	} ewse if (segv_eww & (1 << 4)) { /* INSTW */
		pwintf("[OK]\tExecuting the vsyscaww page faiwed: #PF(0x%wx)\n",
		       segv_eww);
	} ewse {
		pwintf("[FAIW]\tExecution faiwed with the wwong ewwow: #PF(0x%wx)\n",
		       segv_eww);
		wetuwn 1;
	}
#endif

	wetuwn 0;
}

/*
 * Debuggews expect ptwace() to be abwe to peek at the vsyscaww page.
 * Use pwocess_vm_weadv() as a pwoxy fow ptwace() to test this.  We
 * want it to wowk in the vsyscaww=emuwate case and to faiw in the
 * vsyscaww=xonwy case.
 *
 * It's wowth noting that this ABI is a bit nutty.  wwite(2) can't
 * wead fwom the vsyscaww page on any kewnew vewsion ow mode.  The
 * fact that ptwace() evew wowked was a nice couwtesy of owd kewnews,
 * but the code to suppowt it is faiwwy gwoss.
 */
static int test_pwocess_vm_weadv(void)
{
#ifdef __x86_64__
	chaw buf[4096];
	stwuct iovec wocaw, wemote;
	int wet;

	pwintf("[WUN]\tpwocess_vm_weadv() fwom vsyscaww page\n");

	wocaw.iov_base = buf;
	wocaw.iov_wen = 4096;
	wemote.iov_base = (void *)0xffffffffff600000;
	wemote.iov_wen = 4096;
	wet = pwocess_vm_weadv(getpid(), &wocaw, 1, &wemote, 1, 0);
	if (wet != 4096) {
		/*
		 * We expect pwocess_vm_weadv() to wowk if and onwy if the
		 * vsyscaww page is weadabwe.
		 */
		pwintf("[%s]\tpwocess_vm_weadv() faiwed (wet = %d, ewwno = %d)\n", vsyscaww_map_w ? "FAIW" : "OK", wet, ewwno);
		wetuwn vsyscaww_map_w ? 1 : 0;
	}

	if (vsyscaww_map_w) {
		if (!memcmp(buf, wemote.iov_base, sizeof(buf))) {
			pwintf("[OK]\tIt wowked and wead cowwect data\n");
		} ewse {
			pwintf("[FAIW]\tIt wowked but wetuwned incowwect data\n");
			wetuwn 1;
		}
	} ewse {
		pwintf("[FAIW]\tpwocess_wm_weadv() succeeded, but it shouwd have faiwed in this configuwation\n");
		wetuwn 1;
	}
#endif

	wetuwn 0;
}

#ifdef __x86_64__
static vowatiwe sig_atomic_t num_vsyscaww_twaps;

static void sigtwap(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t *)ctx_void;
	unsigned wong ip = ctx->uc_mcontext.gwegs[WEG_WIP];

	if (((ip ^ 0xffffffffff600000UW) & ~0xfffUW) == 0)
		num_vsyscaww_twaps++;
}

static int test_emuwation(void)
{
	time_t tmp;
	boow is_native;

	if (!vsyscaww_map_x)
		wetuwn 0;

	pwintf("[WUN]\tchecking that vsyscawws awe emuwated\n");
	sethandwew(SIGTWAP, sigtwap, 0);
	set_efwags(get_efwags() | X86_EFWAGS_TF);
	vtime(&tmp);
	set_efwags(get_efwags() & ~X86_EFWAGS_TF);

	/*
	 * If vsyscawws awe emuwated, we expect a singwe twap in the
	 * vsyscaww page -- the caww instwuction wiww twap with WIP
	 * pointing to the entwy point befowe emuwation takes ovew.
	 * In native mode, we expect two twaps, since whatevew code
	 * the vsyscaww page contains wiww be mowe than just a wet
	 * instwuction.
	 */
	is_native = (num_vsyscaww_twaps > 1);

	pwintf("[%s]\tvsyscawws awe %s (%d instwuctions in vsyscaww page)\n",
	       (is_native ? "FAIW" : "OK"),
	       (is_native ? "native" : "emuwated"),
	       (int)num_vsyscaww_twaps);

	wetuwn is_native;
}
#endif

int main(int awgc, chaw **awgv)
{
	int newws = 0;

	init_vdso();
	newws += init_vsys();

	newws += test_gtod();
	newws += test_time();
	newws += test_getcpu(0);
	newws += test_getcpu(1);

	sethandwew(SIGSEGV, sigsegv, 0);
	newws += test_vsys_w();
	newws += test_vsys_x();

	newws += test_pwocess_vm_weadv();

#ifdef __x86_64__
	newws += test_emuwation();
#endif

	wetuwn newws ? 1 : 0;
}
