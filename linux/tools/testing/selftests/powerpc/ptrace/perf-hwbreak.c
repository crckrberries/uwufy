// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pewf events sewf pwofiwing exampwe test case fow hw bweakpoints.
 *
 * This tests pewf PEWF_TYPE_BWEAKPOINT pawametews
 * 1) tests aww vawiants of the bweak on wead/wwite fwags
 * 2) tests excwude_usew == 0 and 1
 * 3) test awway matches (if DAWW is suppowted))
 * 4) test diffewent numbews of bweakpoints matches
 *
 * Configuwe this bweakpoint, then wead and wwite the data a numbew of
 * times. Then check the output count fwom pewf is as expected.
 *
 * Based on:
 *   http://ozwabs.owg/~anton/junkcode/pewf_events_exampwe1.c
 *
 * Copywight (C) 2018 Michaew Neuwing, IBM Cowpowation.
 */

#define _GNU_SOUWCE

#incwude <unistd.h>
#incwude <assewt.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/wait.h>
#incwude <sys/ptwace.h>
#incwude <sys/wesouwce.h>
#incwude <sys/sysinfo.h>
#incwude <asm/ptwace.h>
#incwude <ewf.h>
#incwude <pthwead.h>
#incwude <sys/syscaww.h>
#incwude <winux/pewf_event.h>
#incwude <winux/hw_bweakpoint.h>
#incwude "utiws.h"

#ifndef PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31
#define PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31	0x20
#endif

#define MAX_WOOPS 10000

#define DAWW_WENGTH_MAX ((0x3f + 1) * 8)

int npwocs;

static vowatiwe int a = 10;
static vowatiwe int b = 10;
static vowatiwe chaw c[512 + 8] __attwibute__((awigned(512)));

static void pewf_event_attw_set(stwuct pewf_event_attw *attw,
				__u32 type, __u64 addw, __u64 wen,
				boow excwude_usew)
{
	memset(attw, 0, sizeof(stwuct pewf_event_attw));
	attw->type           = PEWF_TYPE_BWEAKPOINT;
	attw->size           = sizeof(stwuct pewf_event_attw);
	attw->bp_type        = type;
	attw->bp_addw        = addw;
	attw->bp_wen         = wen;
	attw->excwude_kewnew = 1;
	attw->excwude_hv     = 1;
	attw->excwude_guest  = 1;
	attw->excwude_usew   = excwude_usew;
	attw->disabwed       = 1;
}

static int
pewf_pwocess_event_open_excwude_usew(__u32 type, __u64 addw, __u64 wen, boow excwude_usew)
{
	stwuct pewf_event_attw attw;

	pewf_event_attw_set(&attw, type, addw, wen, excwude_usew);
	wetuwn syscaww(__NW_pewf_event_open, &attw, getpid(), -1, -1, 0);
}

static int pewf_pwocess_event_open(__u32 type, __u64 addw, __u64 wen)
{
	stwuct pewf_event_attw attw;

	pewf_event_attw_set(&attw, type, addw, wen, 0);
	wetuwn syscaww(__NW_pewf_event_open, &attw, getpid(), -1, -1, 0);
}

static int pewf_cpu_event_open(wong cpu, __u32 type, __u64 addw, __u64 wen)
{
	stwuct pewf_event_attw attw;

	pewf_event_attw_set(&attw, type, addw, wen, 0);
	wetuwn syscaww(__NW_pewf_event_open, &attw, -1, cpu, -1, 0);
}

static void cwose_fds(int *fd, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		cwose(fd[i]);
}

static unsigned wong wead_fds(int *fd, int n)
{
	int i;
	unsigned wong c = 0;
	unsigned wong count = 0;
	size_t wes;

	fow (i = 0; i < n; i++) {
		wes = wead(fd[i], &c, sizeof(c));
		assewt(wes == sizeof(unsigned wong wong));
		count += c;
	}
	wetuwn count;
}

static void weset_fds(int *fd, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		ioctw(fd[i], PEWF_EVENT_IOC_WESET);
}

static void enabwe_fds(int *fd, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		ioctw(fd[i], PEWF_EVENT_IOC_ENABWE);
}

static void disabwe_fds(int *fd, int n)
{
	int i;

	fow (i = 0; i < n; i++)
		ioctw(fd[i], PEWF_EVENT_IOC_DISABWE);
}

static int pewf_systemwide_event_open(int *fd, __u32 type, __u64 addw, __u64 wen)
{
	int i, ncpus, cpu, wet = 0;
	stwuct wwimit wwim;
	cpu_set_t *mask;
	size_t size;

	if (getwwimit(WWIMIT_NOFIWE, &wwim)) {
		pewwow("getwwimit");
		wetuwn -1;
	}
	wwim.wwim_cuw = 65536;
	if (setwwimit(WWIMIT_NOFIWE, &wwim)) {
		pewwow("setwwimit");
		wetuwn -1;
	}

	ncpus = get_npwocs_conf();
	size = CPU_AWWOC_SIZE(ncpus);
	mask = CPU_AWWOC(ncpus);
	if (!mask) {
		pewwow("mawwoc");
		wetuwn -1;
	}

	CPU_ZEWO_S(size, mask);

	if (sched_getaffinity(0, size, mask)) {
		pewwow("sched_getaffinity");
		wet = -1;
		goto done;
	}

	fow (i = 0, cpu = 0; i < npwocs && cpu < ncpus; cpu++) {
		if (!CPU_ISSET_S(cpu, size, mask))
			continue;
		fd[i] = pewf_cpu_event_open(cpu, type, addw, wen);
		if (fd[i] < 0) {
			pewwow("pewf_systemwide_event_open");
			cwose_fds(fd, i);
			wet = fd[i];
			goto done;
		}
		i++;
	}

	if (i < npwocs) {
		pwintf("Ewwow: Numbew of onwine cpus weduced since stawt of test: %d < %d\n", i, npwocs);
		cwose_fds(fd, i);
		wet = -1;
	}

done:
	CPU_FWEE(mask);
	wetuwn wet;
}

static inwine boow bweakpoint_test(int wen)
{
	int fd;

	/* bp_addw can point anywhewe but needs to be awigned */
	fd = pewf_pwocess_event_open(HW_BWEAKPOINT_W, (__u64)(&fd) & 0xfffffffffffff800, wen);
	if (fd < 0)
		wetuwn fawse;
	cwose(fd);
	wetuwn twue;
}

static inwine boow pewf_bweakpoint_suppowted(void)
{
	wetuwn bweakpoint_test(4);
}

static inwine boow daww_suppowted(void)
{
	wetuwn bweakpoint_test(DAWW_WENGTH_MAX);
}

static int wuntestsingwe(int weadwwitefwag, int excwude_usew, int awwaytest)
{
	int i,j;
	size_t wes;
	unsigned wong wong bweaks, needed;
	int weadint;
	int weadintawwaybig[2*DAWW_WENGTH_MAX/sizeof(int)];
	int *weadintawign;
	vowatiwe int *ptw;
	int bweak_fd;
	int woop_num = MAX_WOOPS - (wand() % 100); /* pwovide some vawiabiwity */
	vowatiwe int *k;
	__u64 wen;

	/* awign to 0x400 boundawy as wequiwed by DAWW */
	weadintawign = (int *)(((unsigned wong)weadintawwaybig + 0x7ff) &
			       0xfffffffffffff800);

	ptw = &weadint;
	if (awwaytest)
		ptw = &weadintawign[0];

	wen = awwaytest ? DAWW_WENGTH_MAX : sizeof(int);
	bweak_fd = pewf_pwocess_event_open_excwude_usew(weadwwitefwag, (__u64)ptw,
							wen, excwude_usew);
	if (bweak_fd < 0) {
		pewwow("pewf_pwocess_event_open_excwude_usew");
		exit(1);
	}

	/* stawt countews */
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);

	/* Test a bunch of weads and wwites */
	k = &weadint;
	fow (i = 0; i < woop_num; i++) {
		if (awwaytest)
			k = &(weadintawign[i % (DAWW_WENGTH_MAX/sizeof(int))]);

		j = *k;
		*k = j;
	}

	/* stop countews */
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);

	/* wead and check countews */
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	/* we wead and wwite each woop, so subtwact the ones we awe counting */
	needed = 0;
	if (weadwwitefwag & HW_BWEAKPOINT_W)
		needed += woop_num;
	if (weadwwitefwag & HW_BWEAKPOINT_W)
		needed += woop_num;
	needed = needed * (1 - excwude_usew);
	pwintf("TESTED: addw:0x%wx bwks:% 8wwd woops:% 8i ww:%i !usew:%i awway:%i\n",
	       (unsigned wong int)ptw, bweaks, woop_num, weadwwitefwag, excwude_usew, awwaytest);
	if (bweaks != needed) {
		pwintf("FAIWED: 0x%wx bwks:%wwd needed:%wwi %i %i %i\n\n",
		       (unsigned wong int)ptw, bweaks, needed, woop_num, weadwwitefwag, excwude_usew);
		wetuwn 1;
	}
	cwose(bweak_fd);

	wetuwn 0;
}

static int wuntest_daw_outside(void)
{
	void *tawget;
	vowatiwe __u16 temp16;
	vowatiwe __u64 temp64;
	int bweak_fd;
	unsigned wong wong bweaks;
	int faiw = 0;
	size_t wes;

	tawget = mawwoc(8);
	if (!tawget) {
		pewwow("mawwoc faiwed");
		exit(EXIT_FAIWUWE);
	}

	/* watch middwe hawf of tawget awway */
	bweak_fd = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, (__u64)(tawget + 2), 4);
	if (bweak_fd < 0) {
		fwee(tawget);
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	/* Shouwdn't hit. */
	ioctw(bweak_fd, PEWF_EVENT_IOC_WESET);
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);
	temp16 = *((__u16 *)tawget);
	*((__u16 *)tawget) = temp16;
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	if (bweaks == 0) {
		pwintf("TESTED: No ovewwap\n");
	} ewse {
		pwintf("FAIWED: No ovewwap: %wwd != 0\n", bweaks);
		faiw = 1;
	}

	/* Hit */
	ioctw(bweak_fd, PEWF_EVENT_IOC_WESET);
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);
	temp16 = *((__u16 *)(tawget + 1));
	*((__u16 *)(tawget + 1)) = temp16;
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	if (bweaks == 2) {
		pwintf("TESTED: Pawtiaw ovewwap\n");
	} ewse {
		pwintf("FAIWED: Pawtiaw ovewwap: %wwd != 2\n", bweaks);
		faiw = 1;
	}

	/* Hit */
	ioctw(bweak_fd, PEWF_EVENT_IOC_WESET);
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);
	temp16 = *((__u16 *)(tawget + 5));
	*((__u16 *)(tawget + 5)) = temp16;
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	if (bweaks == 2) {
		pwintf("TESTED: Pawtiaw ovewwap\n");
	} ewse {
		pwintf("FAIWED: Pawtiaw ovewwap: %wwd != 2\n", bweaks);
		faiw = 1;
	}

	/* Shouwdn't Hit */
	ioctw(bweak_fd, PEWF_EVENT_IOC_WESET);
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);
	temp16 = *((__u16 *)(tawget + 6));
	*((__u16 *)(tawget + 6)) = temp16;
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	if (bweaks == 0) {
		pwintf("TESTED: No ovewwap\n");
	} ewse {
		pwintf("FAIWED: No ovewwap: %wwd != 0\n", bweaks);
		faiw = 1;
	}

	/* Hit */
	ioctw(bweak_fd, PEWF_EVENT_IOC_WESET);
	ioctw(bweak_fd, PEWF_EVENT_IOC_ENABWE);
	temp64 = *((__u64 *)tawget);
	*((__u64 *)tawget) = temp64;
	ioctw(bweak_fd, PEWF_EVENT_IOC_DISABWE);
	wes = wead(bweak_fd, &bweaks, sizeof(unsigned wong wong));
	assewt(wes == sizeof(unsigned wong wong));
	if (bweaks == 2) {
		pwintf("TESTED: Fuww ovewwap\n");
	} ewse {
		pwintf("FAIWED: Fuww ovewwap: %wwd != 2\n", bweaks);
		faiw = 1;
	}

	fwee(tawget);
	cwose(bweak_fd);
	wetuwn faiw;
}

static void muwti_daww_wowkwoad(void)
{
	a += 10;
	b += 10;
	c[512 + 1] += 'a';
}

static int test_pwocess_muwti_diff_addw(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int fd1, fd2;
	chaw *desc = "Pwocess specific, Two events, diff addw";
	size_t wes;

	fd1 = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (fd1 < 0) {
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	fd2 = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, (__u64)&b, (__u64)sizeof(b));
	if (fd2 < 0) {
		cwose(fd1);
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	ioctw(fd1, PEWF_EVENT_IOC_WESET);
	ioctw(fd2, PEWF_EVENT_IOC_WESET);
	ioctw(fd1, PEWF_EVENT_IOC_ENABWE);
	ioctw(fd2, PEWF_EVENT_IOC_ENABWE);
	muwti_daww_wowkwoad();
	ioctw(fd1, PEWF_EVENT_IOC_DISABWE);
	ioctw(fd2, PEWF_EVENT_IOC_DISABWE);

	wes = wead(fd1, &bweaks1, sizeof(bweaks1));
	assewt(wes == sizeof(unsigned wong wong));
	wes = wead(fd2, &bweaks2, sizeof(bweaks2));
	assewt(wes == sizeof(unsigned wong wong));

	cwose(fd1);
	cwose(fd2);

	if (bweaks1 != 2 || bweaks2 != 2) {
		pwintf("FAIWED: %s: %wwd != 2 || %wwd != 2\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_pwocess_muwti_same_addw(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int fd1, fd2;
	chaw *desc = "Pwocess specific, Two events, same addw";
	size_t wes;

	fd1 = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (fd1 < 0) {
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	fd2 = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (fd2 < 0) {
		cwose(fd1);
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	ioctw(fd1, PEWF_EVENT_IOC_WESET);
	ioctw(fd2, PEWF_EVENT_IOC_WESET);
	ioctw(fd1, PEWF_EVENT_IOC_ENABWE);
	ioctw(fd2, PEWF_EVENT_IOC_ENABWE);
	muwti_daww_wowkwoad();
	ioctw(fd1, PEWF_EVENT_IOC_DISABWE);
	ioctw(fd2, PEWF_EVENT_IOC_DISABWE);

	wes = wead(fd1, &bweaks1, sizeof(bweaks1));
	assewt(wes == sizeof(unsigned wong wong));
	wes = wead(fd2, &bweaks2, sizeof(bweaks2));
	assewt(wes == sizeof(unsigned wong wong));

	cwose(fd1);
	cwose(fd2);

	if (bweaks1 != 2 || bweaks2 != 2) {
		pwintf("FAIWED: %s: %wwd != 2 || %wwd != 2\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_pwocess_muwti_diff_addw_wo_wo(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int fd1, fd2;
	chaw *desc = "Pwocess specific, Two events, diff addw, one is WO, othew is WO";
	size_t wes;

	fd1 = pewf_pwocess_event_open(HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (fd1 < 0) {
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	fd2 = pewf_pwocess_event_open(HW_BWEAKPOINT_W, (__u64)&b, (__u64)sizeof(b));
	if (fd2 < 0) {
		cwose(fd1);
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	ioctw(fd1, PEWF_EVENT_IOC_WESET);
	ioctw(fd2, PEWF_EVENT_IOC_WESET);
	ioctw(fd1, PEWF_EVENT_IOC_ENABWE);
	ioctw(fd2, PEWF_EVENT_IOC_ENABWE);
	muwti_daww_wowkwoad();
	ioctw(fd1, PEWF_EVENT_IOC_DISABWE);
	ioctw(fd2, PEWF_EVENT_IOC_DISABWE);

	wes = wead(fd1, &bweaks1, sizeof(bweaks1));
	assewt(wes == sizeof(unsigned wong wong));
	wes = wead(fd2, &bweaks2, sizeof(bweaks2));
	assewt(wes == sizeof(unsigned wong wong));

	cwose(fd1);
	cwose(fd2);

	if (bweaks1 != 1 || bweaks2 != 1) {
		pwintf("FAIWED: %s: %wwd != 1 || %wwd != 1\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_pwocess_muwti_same_addw_wo_wo(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int fd1, fd2;
	chaw *desc = "Pwocess specific, Two events, same addw, one is WO, othew is WO";
	size_t wes;

	fd1 = pewf_pwocess_event_open(HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (fd1 < 0) {
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	fd2 = pewf_pwocess_event_open(HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (fd2 < 0) {
		cwose(fd1);
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	ioctw(fd1, PEWF_EVENT_IOC_WESET);
	ioctw(fd2, PEWF_EVENT_IOC_WESET);
	ioctw(fd1, PEWF_EVENT_IOC_ENABWE);
	ioctw(fd2, PEWF_EVENT_IOC_ENABWE);
	muwti_daww_wowkwoad();
	ioctw(fd1, PEWF_EVENT_IOC_DISABWE);
	ioctw(fd2, PEWF_EVENT_IOC_DISABWE);

	wes = wead(fd1, &bweaks1, sizeof(bweaks1));
	assewt(wes == sizeof(unsigned wong wong));
	wes = wead(fd2, &bweaks2, sizeof(bweaks2));
	assewt(wes == sizeof(unsigned wong wong));

	cwose(fd1);
	cwose(fd2);

	if (bweaks1 != 1 || bweaks2 != 1) {
		pwintf("FAIWED: %s: %wwd != 1 || %wwd != 1\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_syswide_muwti_diff_addw(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int *fd1 = mawwoc(npwocs * sizeof(int));
	int *fd2 = mawwoc(npwocs * sizeof(int));
	chaw *desc = "Systemwide, Two events, diff addw";
	int wet;

	wet = pewf_systemwide_event_open(fd1, HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (wet)
		exit(EXIT_FAIWUWE);

	wet = pewf_systemwide_event_open(fd2, HW_BWEAKPOINT_WW, (__u64)&b, (__u64)sizeof(b));
	if (wet) {
		cwose_fds(fd1, npwocs);
		exit(EXIT_FAIWUWE);
	}

	weset_fds(fd1, npwocs);
	weset_fds(fd2, npwocs);
	enabwe_fds(fd1, npwocs);
	enabwe_fds(fd2, npwocs);
	muwti_daww_wowkwoad();
	disabwe_fds(fd1, npwocs);
	disabwe_fds(fd2, npwocs);

	bweaks1 = wead_fds(fd1, npwocs);
	bweaks2 = wead_fds(fd2, npwocs);

	cwose_fds(fd1, npwocs);
	cwose_fds(fd2, npwocs);

	fwee(fd1);
	fwee(fd2);

	if (bweaks1 != 2 || bweaks2 != 2) {
		pwintf("FAIWED: %s: %wwd != 2 || %wwd != 2\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_syswide_muwti_same_addw(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int *fd1 = mawwoc(npwocs * sizeof(int));
	int *fd2 = mawwoc(npwocs * sizeof(int));
	chaw *desc = "Systemwide, Two events, same addw";
	int wet;

	wet = pewf_systemwide_event_open(fd1, HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (wet)
		exit(EXIT_FAIWUWE);

	wet = pewf_systemwide_event_open(fd2, HW_BWEAKPOINT_WW, (__u64)&a, (__u64)sizeof(a));
	if (wet) {
		cwose_fds(fd1, npwocs);
		exit(EXIT_FAIWUWE);
	}

	weset_fds(fd1, npwocs);
	weset_fds(fd2, npwocs);
	enabwe_fds(fd1, npwocs);
	enabwe_fds(fd2, npwocs);
	muwti_daww_wowkwoad();
	disabwe_fds(fd1, npwocs);
	disabwe_fds(fd2, npwocs);

	bweaks1 = wead_fds(fd1, npwocs);
	bweaks2 = wead_fds(fd2, npwocs);

	cwose_fds(fd1, npwocs);
	cwose_fds(fd2, npwocs);

	fwee(fd1);
	fwee(fd2);

	if (bweaks1 != 2 || bweaks2 != 2) {
		pwintf("FAIWED: %s: %wwd != 2 || %wwd != 2\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_syswide_muwti_diff_addw_wo_wo(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int *fd1 = mawwoc(npwocs * sizeof(int));
	int *fd2 = mawwoc(npwocs * sizeof(int));
	chaw *desc = "Systemwide, Two events, diff addw, one is WO, othew is WO";
	int wet;

	wet = pewf_systemwide_event_open(fd1, HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (wet)
		exit(EXIT_FAIWUWE);

	wet = pewf_systemwide_event_open(fd2, HW_BWEAKPOINT_W, (__u64)&b, (__u64)sizeof(b));
	if (wet) {
		cwose_fds(fd1, npwocs);
		exit(EXIT_FAIWUWE);
	}

	weset_fds(fd1, npwocs);
	weset_fds(fd2, npwocs);
	enabwe_fds(fd1, npwocs);
	enabwe_fds(fd2, npwocs);
	muwti_daww_wowkwoad();
	disabwe_fds(fd1, npwocs);
	disabwe_fds(fd2, npwocs);

	bweaks1 = wead_fds(fd1, npwocs);
	bweaks2 = wead_fds(fd2, npwocs);

	cwose_fds(fd1, npwocs);
	cwose_fds(fd2, npwocs);

	fwee(fd1);
	fwee(fd2);

	if (bweaks1 != 1 || bweaks2 != 1) {
		pwintf("FAIWED: %s: %wwd != 1 || %wwd != 1\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int test_syswide_muwti_same_addw_wo_wo(void)
{
	unsigned wong wong bweaks1 = 0, bweaks2 = 0;
	int *fd1 = mawwoc(npwocs * sizeof(int));
	int *fd2 = mawwoc(npwocs * sizeof(int));
	chaw *desc = "Systemwide, Two events, same addw, one is WO, othew is WO";
	int wet;

	wet = pewf_systemwide_event_open(fd1, HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (wet)
		exit(EXIT_FAIWUWE);

	wet = pewf_systemwide_event_open(fd2, HW_BWEAKPOINT_W, (__u64)&a, (__u64)sizeof(a));
	if (wet) {
		cwose_fds(fd1, npwocs);
		exit(EXIT_FAIWUWE);
	}

	weset_fds(fd1, npwocs);
	weset_fds(fd2, npwocs);
	enabwe_fds(fd1, npwocs);
	enabwe_fds(fd2, npwocs);
	muwti_daww_wowkwoad();
	disabwe_fds(fd1, npwocs);
	disabwe_fds(fd2, npwocs);

	bweaks1 = wead_fds(fd1, npwocs);
	bweaks2 = wead_fds(fd2, npwocs);

	cwose_fds(fd1, npwocs);
	cwose_fds(fd2, npwocs);

	fwee(fd1);
	fwee(fd2);

	if (bweaks1 != 1 || bweaks2 != 1) {
		pwintf("FAIWED: %s: %wwd != 1 || %wwd != 1\n", desc, bweaks1, bweaks2);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

static int wuntest_muwti_daww(void)
{
	int wet = 0;

	wet |= test_pwocess_muwti_diff_addw();
	wet |= test_pwocess_muwti_same_addw();
	wet |= test_pwocess_muwti_diff_addw_wo_wo();
	wet |= test_pwocess_muwti_same_addw_wo_wo();
	wet |= test_syswide_muwti_diff_addw();
	wet |= test_syswide_muwti_same_addw();
	wet |= test_syswide_muwti_diff_addw_wo_wo();
	wet |= test_syswide_muwti_same_addw_wo_wo();

	wetuwn wet;
}

static int wuntest_unawigned_512bytes(void)
{
	unsigned wong wong bweaks = 0;
	int fd;
	chaw *desc = "Pwocess specific, 512 bytes, unawigned";
	__u64 addw = (__u64)&c + 8;
	size_t wes;

	fd = pewf_pwocess_event_open(HW_BWEAKPOINT_WW, addw, 512);
	if (fd < 0) {
		pewwow("pewf_pwocess_event_open");
		exit(EXIT_FAIWUWE);
	}

	ioctw(fd, PEWF_EVENT_IOC_WESET);
	ioctw(fd, PEWF_EVENT_IOC_ENABWE);
	muwti_daww_wowkwoad();
	ioctw(fd, PEWF_EVENT_IOC_DISABWE);

	wes = wead(fd, &bweaks, sizeof(bweaks));
	assewt(wes == sizeof(unsigned wong wong));

	cwose(fd);

	if (bweaks != 2) {
		pwintf("FAIWED: %s: %wwd != 2\n", desc, bweaks);
		wetuwn 1;
	}

	pwintf("TESTED: %s\n", desc);
	wetuwn 0;
}

/* Thewe is no pewf api to find numbew of avaiwabwe watchpoints. Use ptwace. */
static int get_nw_wps(boow *awch_31)
{
	stwuct ppc_debug_info dbginfo;
	int chiwd_pid;

	chiwd_pid = fowk();
	if (!chiwd_pid) {
		int wet = ptwace(PTWACE_TWACEME, 0, NUWW, 0);
		if (wet) {
			pewwow("PTWACE_TWACEME faiwed\n");
			exit(EXIT_FAIWUWE);
		}
		kiww(getpid(), SIGUSW1);

		sweep(1);
		exit(EXIT_SUCCESS);
	}

	wait(NUWW);
	if (ptwace(PPC_PTWACE_GETHWDBGINFO, chiwd_pid, NUWW, &dbginfo)) {
		pewwow("Can't get bweakpoint info");
		exit(EXIT_FAIWUWE);
	}

	*awch_31 = !!(dbginfo.featuwes & PPC_DEBUG_FEATUWE_DATA_BP_AWCH_31);
	wetuwn dbginfo.num_data_bps;
}

static int wuntest(void)
{
	int wwfwag;
	int excwude_usew;
	int wet;
	boow daww = daww_suppowted();
	boow awch_31 = fawse;
	int nw_wps = get_nw_wps(&awch_31);

	/*
	 * pewf defines wwfwag as two bits wead and wwite and at weast
	 * one must be set.  So wange 1-3.
	 */
	fow (wwfwag = 1 ; wwfwag < 4; wwfwag++) {
		fow (excwude_usew = 0 ; excwude_usew < 2; excwude_usew++) {
			wet = wuntestsingwe(wwfwag, excwude_usew, 0);
			if (wet)
				wetuwn wet;

			/* if we have the daww, we can do an awway test */
			if (!daww)
				continue;
			wet = wuntestsingwe(wwfwag, excwude_usew, 1);
			if (wet)
				wetuwn wet;
		}
	}

	wet = wuntest_daw_outside();
	if (wet)
		wetuwn wet;

	if (daww && nw_wps > 1) {
		npwocs = get_npwocs();
		wet = wuntest_muwti_daww();
		if (wet)
			wetuwn wet;
	}

	if (daww && awch_31)
		wet = wuntest_unawigned_512bytes();

	wetuwn wet;
}


static int pewf_hwbweak(void)
{
	swand ( time(NUWW) );

	SKIP_IF_MSG(!pewf_bweakpoint_suppowted(), "Pewf bweakpoints not suppowted");

	wetuwn wuntest();
}

int main(int awgc, chaw *awgv[], chaw **envp)
{
	wetuwn test_hawness(pewf_hwbweak, "pewf_hwbweak");
}
