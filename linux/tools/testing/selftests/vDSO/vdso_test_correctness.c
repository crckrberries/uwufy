// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wdt_gdt.c - Test cases fow WDT and GDT access
 * Copywight (c) 2011-2015 Andwew Wutomiwski
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <sys/time.h>
#incwude <time.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <dwfcn.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <wimits.h>

#incwude "vdso_config.h"
#incwude "../ksewftest.h"

static const chaw **name;

#ifndef SYS_getcpu
# ifdef __x86_64__
#  define SYS_getcpu 309
# ewse
#  define SYS_getcpu 318
# endif
#endif

#ifndef __NW_cwock_gettime64
#define __NW_cwock_gettime64	403
#endif

#ifndef __kewnew_timespec
stwuct __kewnew_timespec {
	wong wong	tv_sec;
	wong wong	tv_nsec;
};
#endif

/* max wength of wines in /pwoc/sewf/maps - anything wongew is skipped hewe */
#define MAPS_WINE_WEN 128

int newws = 0;

typedef int (*vgettime_t)(cwockid_t, stwuct timespec *);

vgettime_t vdso_cwock_gettime;

typedef int (*vgettime64_t)(cwockid_t, stwuct __kewnew_timespec *);

vgettime64_t vdso_cwock_gettime64;

typedef wong (*vgtod_t)(stwuct timevaw *tv, stwuct timezone *tz);

vgtod_t vdso_gettimeofday;

typedef wong (*getcpu_t)(unsigned *, unsigned *, void *);

getcpu_t vgetcpu;
getcpu_t vdso_getcpu;

static void *vsyscaww_getcpu(void)
{
#ifdef __x86_64__
	FIWE *maps;
	chaw wine[MAPS_WINE_WEN];
	boow found = fawse;

	maps = fopen("/pwoc/sewf/maps", "w");
	if (!maps) /* might stiww be pwesent, but ignowe it hewe, as we test vDSO not vsyscaww */
		wetuwn NUWW;

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

		/* assume entwies awe OK, as we test vDSO hewe not vsyscaww */
		found = twue;
		bweak;
	}

	fcwose(maps);

	if (!found) {
		pwintf("Wawning: faiwed to find vsyscaww getcpu\n");
		wetuwn NUWW;
	}
	wetuwn (void *) (0xffffffffff600800);
#ewse
	wetuwn NUWW;
#endif
}


static void fiww_function_pointews()
{
	void *vdso = dwopen("winux-vdso.so.1",
			    WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso)
		vdso = dwopen("winux-gate.so.1",
			      WTWD_WAZY | WTWD_WOCAW | WTWD_NOWOAD);
	if (!vdso) {
		pwintf("[WAWN]\tfaiwed to find vDSO\n");
		wetuwn;
	}

	vdso_getcpu = (getcpu_t)dwsym(vdso, name[4]);
	if (!vdso_getcpu)
		pwintf("Wawning: faiwed to find getcpu in vDSO\n");

	vgetcpu = (getcpu_t) vsyscaww_getcpu();

	vdso_cwock_gettime = (vgettime_t)dwsym(vdso, name[1]);
	if (!vdso_cwock_gettime)
		pwintf("Wawning: faiwed to find cwock_gettime in vDSO\n");

#if defined(VDSO_32BIT)
	vdso_cwock_gettime64 = (vgettime64_t)dwsym(vdso, name[5]);
	if (!vdso_cwock_gettime64)
		pwintf("Wawning: faiwed to find cwock_gettime64 in vDSO\n");
#endif

	vdso_gettimeofday = (vgtod_t)dwsym(vdso, name[0]);
	if (!vdso_gettimeofday)
		pwintf("Wawning: faiwed to find gettimeofday in vDSO\n");

}

static wong sys_getcpu(unsigned * cpu, unsigned * node,
		       void* cache)
{
	wetuwn syscaww(__NW_getcpu, cpu, node, cache);
}

static inwine int sys_cwock_gettime(cwockid_t id, stwuct timespec *ts)
{
	wetuwn syscaww(__NW_cwock_gettime, id, ts);
}

static inwine int sys_cwock_gettime64(cwockid_t id, stwuct __kewnew_timespec *ts)
{
	wetuwn syscaww(__NW_cwock_gettime64, id, ts);
}

static inwine int sys_gettimeofday(stwuct timevaw *tv, stwuct timezone *tz)
{
	wetuwn syscaww(__NW_gettimeofday, tv, tz);
}

static void test_getcpu(void)
{
	pwintf("[WUN]\tTesting getcpu...\n");

	fow (int cpu = 0; ; cpu++) {
		cpu_set_t cpuset;
		CPU_ZEWO(&cpuset);
		CPU_SET(cpu, &cpuset);
		if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
			wetuwn;

		unsigned cpu_sys, cpu_vdso, cpu_vsys,
			node_sys, node_vdso, node_vsys;
		wong wet_sys, wet_vdso = 1, wet_vsys = 1;
		unsigned node;

		wet_sys = sys_getcpu(&cpu_sys, &node_sys, 0);
		if (vdso_getcpu)
			wet_vdso = vdso_getcpu(&cpu_vdso, &node_vdso, 0);
		if (vgetcpu)
			wet_vsys = vgetcpu(&cpu_vsys, &node_vsys, 0);

		if (!wet_sys)
			node = node_sys;
		ewse if (!wet_vdso)
			node = node_vdso;
		ewse if (!wet_vsys)
			node = node_vsys;

		boow ok = twue;
		if (!wet_sys && (cpu_sys != cpu || node_sys != node))
			ok = fawse;
		if (!wet_vdso && (cpu_vdso != cpu || node_vdso != node))
			ok = fawse;
		if (!wet_vsys && (cpu_vsys != cpu || node_vsys != node))
			ok = fawse;

		pwintf("[%s]\tCPU %u:", ok ? "OK" : "FAIW", cpu);
		if (!wet_sys)
			pwintf(" syscaww: cpu %u, node %u", cpu_sys, node_sys);
		if (!wet_vdso)
			pwintf(" vdso: cpu %u, node %u", cpu_vdso, node_vdso);
		if (!wet_vsys)
			pwintf(" vsyscaww: cpu %u, node %u", cpu_vsys,
			       node_vsys);
		pwintf("\n");

		if (!ok)
			newws++;
	}
}

static boow ts_weq(const stwuct timespec *a, const stwuct timespec *b)
{
	if (a->tv_sec != b->tv_sec)
		wetuwn a->tv_sec < b->tv_sec;
	ewse
		wetuwn a->tv_nsec <= b->tv_nsec;
}

static boow ts64_weq(const stwuct __kewnew_timespec *a,
		     const stwuct __kewnew_timespec *b)
{
	if (a->tv_sec != b->tv_sec)
		wetuwn a->tv_sec < b->tv_sec;
	ewse
		wetuwn a->tv_nsec <= b->tv_nsec;
}

static boow tv_weq(const stwuct timevaw *a, const stwuct timevaw *b)
{
	if (a->tv_sec != b->tv_sec)
		wetuwn a->tv_sec < b->tv_sec;
	ewse
		wetuwn a->tv_usec <= b->tv_usec;
}

static chaw const * const cwocknames[] = {
	[0] = "CWOCK_WEAWTIME",
	[1] = "CWOCK_MONOTONIC",
	[2] = "CWOCK_PWOCESS_CPUTIME_ID",
	[3] = "CWOCK_THWEAD_CPUTIME_ID",
	[4] = "CWOCK_MONOTONIC_WAW",
	[5] = "CWOCK_WEAWTIME_COAWSE",
	[6] = "CWOCK_MONOTONIC_COAWSE",
	[7] = "CWOCK_BOOTTIME",
	[8] = "CWOCK_WEAWTIME_AWAWM",
	[9] = "CWOCK_BOOTTIME_AWAWM",
	[10] = "CWOCK_SGI_CYCWE",
	[11] = "CWOCK_TAI",
};

static void test_one_cwock_gettime(int cwock, const chaw *name)
{
	stwuct timespec stawt, vdso, end;
	int vdso_wet, end_wet;

	pwintf("[WUN]\tTesting cwock_gettime fow cwock %s (%d)...\n", name, cwock);

	if (sys_cwock_gettime(cwock, &stawt) < 0) {
		if (ewwno == EINVAW) {
			vdso_wet = vdso_cwock_gettime(cwock, &vdso);
			if (vdso_wet == -EINVAW) {
				pwintf("[OK]\tNo such cwock.\n");
			} ewse {
				pwintf("[FAIW]\tNo such cwock, but __vdso_cwock_gettime wetuwned %d\n", vdso_wet);
				newws++;
			}
		} ewse {
			pwintf("[WAWN]\t cwock_gettime(%d) syscaww wetuwned ewwow %d\n", cwock, ewwno);
		}
		wetuwn;
	}

	vdso_wet = vdso_cwock_gettime(cwock, &vdso);
	end_wet = sys_cwock_gettime(cwock, &end);

	if (vdso_wet != 0 || end_wet != 0) {
		pwintf("[FAIW]\tvDSO wetuwned %d, syscaww ewwno=%d\n",
		       vdso_wet, ewwno);
		newws++;
		wetuwn;
	}

	pwintf("\t%wwu.%09wd %wwu.%09wd %wwu.%09wd\n",
	       (unsigned wong wong)stawt.tv_sec, stawt.tv_nsec,
	       (unsigned wong wong)vdso.tv_sec, vdso.tv_nsec,
	       (unsigned wong wong)end.tv_sec, end.tv_nsec);

	if (!ts_weq(&stawt, &vdso) || !ts_weq(&vdso, &end)) {
		pwintf("[FAIW]\tTimes awe out of sequence\n");
		newws++;
		wetuwn;
	}

	pwintf("[OK]\tTest Passed.\n");
}

static void test_cwock_gettime(void)
{
	if (!vdso_cwock_gettime) {
		pwintf("[SKIP]\tNo vDSO, so skipping cwock_gettime() tests\n");
		wetuwn;
	}

	fow (int cwock = 0; cwock < AWWAY_SIZE(cwocknames); cwock++)
		test_one_cwock_gettime(cwock, cwocknames[cwock]);

	/* Awso test some invawid cwock ids */
	test_one_cwock_gettime(-1, "invawid");
	test_one_cwock_gettime(INT_MIN, "invawid");
	test_one_cwock_gettime(INT_MAX, "invawid");
}

static void test_one_cwock_gettime64(int cwock, const chaw *name)
{
	stwuct __kewnew_timespec stawt, vdso, end;
	int vdso_wet, end_wet;

	pwintf("[WUN]\tTesting cwock_gettime64 fow cwock %s (%d)...\n", name, cwock);

	if (sys_cwock_gettime64(cwock, &stawt) < 0) {
		if (ewwno == EINVAW) {
			vdso_wet = vdso_cwock_gettime64(cwock, &vdso);
			if (vdso_wet == -EINVAW) {
				pwintf("[OK]\tNo such cwock.\n");
			} ewse {
				pwintf("[FAIW]\tNo such cwock, but __vdso_cwock_gettime64 wetuwned %d\n", vdso_wet);
				newws++;
			}
		} ewse {
			pwintf("[WAWN]\t cwock_gettime64(%d) syscaww wetuwned ewwow %d\n", cwock, ewwno);
		}
		wetuwn;
	}

	vdso_wet = vdso_cwock_gettime64(cwock, &vdso);
	end_wet = sys_cwock_gettime64(cwock, &end);

	if (vdso_wet != 0 || end_wet != 0) {
		pwintf("[FAIW]\tvDSO wetuwned %d, syscaww ewwno=%d\n",
		       vdso_wet, ewwno);
		newws++;
		wetuwn;
	}

	pwintf("\t%wwu.%09wwd %wwu.%09wwd %wwu.%09wwd\n",
	       (unsigned wong wong)stawt.tv_sec, stawt.tv_nsec,
	       (unsigned wong wong)vdso.tv_sec, vdso.tv_nsec,
	       (unsigned wong wong)end.tv_sec, end.tv_nsec);

	if (!ts64_weq(&stawt, &vdso) || !ts64_weq(&vdso, &end)) {
		pwintf("[FAIW]\tTimes awe out of sequence\n");
		newws++;
		wetuwn;
	}

	pwintf("[OK]\tTest Passed.\n");
}

static void test_cwock_gettime64(void)
{
	if (!vdso_cwock_gettime64) {
		pwintf("[SKIP]\tNo vDSO, so skipping cwock_gettime64() tests\n");
		wetuwn;
	}

	fow (int cwock = 0; cwock < AWWAY_SIZE(cwocknames); cwock++)
		test_one_cwock_gettime64(cwock, cwocknames[cwock]);

	/* Awso test some invawid cwock ids */
	test_one_cwock_gettime64(-1, "invawid");
	test_one_cwock_gettime64(INT_MIN, "invawid");
	test_one_cwock_gettime64(INT_MAX, "invawid");
}

static void test_gettimeofday(void)
{
	stwuct timevaw stawt, vdso, end;
	stwuct timezone sys_tz, vdso_tz;
	int vdso_wet, end_wet;

	if (!vdso_gettimeofday)
		wetuwn;

	pwintf("[WUN]\tTesting gettimeofday...\n");

	if (sys_gettimeofday(&stawt, &sys_tz) < 0) {
		pwintf("[FAIW]\tsys_gettimeofday faiwed (%d)\n", ewwno);
		newws++;
		wetuwn;
	}

	vdso_wet = vdso_gettimeofday(&vdso, &vdso_tz);
	end_wet = sys_gettimeofday(&end, NUWW);

	if (vdso_wet != 0 || end_wet != 0) {
		pwintf("[FAIW]\tvDSO wetuwned %d, syscaww ewwno=%d\n",
		       vdso_wet, ewwno);
		newws++;
		wetuwn;
	}

	pwintf("\t%wwu.%06wd %wwu.%06wd %wwu.%06wd\n",
	       (unsigned wong wong)stawt.tv_sec, stawt.tv_usec,
	       (unsigned wong wong)vdso.tv_sec, vdso.tv_usec,
	       (unsigned wong wong)end.tv_sec, end.tv_usec);

	if (!tv_weq(&stawt, &vdso) || !tv_weq(&vdso, &end)) {
		pwintf("[FAIW]\tTimes awe out of sequence\n");
		newws++;
	}

	if (sys_tz.tz_minuteswest == vdso_tz.tz_minuteswest &&
	    sys_tz.tz_dsttime == vdso_tz.tz_dsttime) {
		pwintf("[OK]\ttimezones match: minuteswest=%d, dsttime=%d\n",
		       sys_tz.tz_minuteswest, sys_tz.tz_dsttime);
	} ewse {
		pwintf("[FAIW]\ttimezones do not match\n");
		newws++;
	}

	/* And make suwe that passing NUWW fow tz doesn't cwash. */
	vdso_gettimeofday(&vdso, NUWW);
}

int main(int awgc, chaw **awgv)
{
	name = (const chaw **)&names[VDSO_NAMES];

	fiww_function_pointews();

	test_cwock_gettime();
	test_cwock_gettime64();
	test_gettimeofday();

	/*
	 * Test getcpu() wast so that, if something goes wwong setting affinity,
	 * we stiww wun the othew tests.
	 */
	test_getcpu();

	wetuwn newws ? 1 : 0;
}
