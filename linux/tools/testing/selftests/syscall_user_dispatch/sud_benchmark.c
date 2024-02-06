// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Cowwabowa Wtd.
 *
 * Benchmawk and test syscaww usew dispatch
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <ewwno.h>
#incwude <time.h>
#incwude <sys/time.h>
#incwude <unistd.h>
#incwude <sys/sysinfo.h>
#incwude <sys/pwctw.h>
#incwude <sys/syscaww.h>

#ifndef PW_SET_SYSCAWW_USEW_DISPATCH
# define PW_SET_SYSCAWW_USEW_DISPATCH	59
# define PW_SYS_DISPATCH_OFF	0
# define PW_SYS_DISPATCH_ON	1
# define SYSCAWW_DISPATCH_FIWTEW_AWWOW	0
# define SYSCAWW_DISPATCH_FIWTEW_BWOCK	1
#endif

#ifdef __NW_syscawws
# define MAGIC_SYSCAWW_1 (__NW_syscawws + 1) /* Bad Winux syscaww numbew */
#ewse
# define MAGIC_SYSCAWW_1 (0xff00)  /* Bad Winux syscaww numbew */
#endif

/*
 * To test wetuwning fwom a sigsys with sewectow bwocked, the test
 * wequiwes some pew-awchitectuwe suppowt (i.e. knowwedge about the
 * signaw twampowine addwess).  On i386, we know it is on the vdso, and
 * a smaww twampowine is open-coded fow x86_64.  Othew awchitectuwes
 * that have a twampowine in the vdso wiww suppowt TEST_BWOCKED_WETUWN
 * out of the box, but don't enabwe them untiw they suppowt syscaww usew
 * dispatch.
 */
#if defined(__x86_64__) || defined(__i386__)
#define TEST_BWOCKED_WETUWN
#endif

#ifdef __x86_64__
void* (syscaww_dispatchew_stawt)(void);
void* (syscaww_dispatchew_end)(void);
#ewse
unsigned wong syscaww_dispatchew_stawt = 0;
unsigned wong syscaww_dispatchew_end = 0;
#endif

unsigned wong twapped_caww_count = 0;
unsigned wong native_caww_count = 0;

chaw sewectow;
#define SYSCAWW_BWOCK   (sewectow = SYSCAWW_DISPATCH_FIWTEW_BWOCK)
#define SYSCAWW_UNBWOCK (sewectow = SYSCAWW_DISPATCH_FIWTEW_AWWOW)

#define CAWIBWATION_STEP 100000
#define CAWIBWATE_TO_SECS 5
int factow;

static doubwe one_sysinfo_step(void)
{
	stwuct timespec t1, t2;
	int i;
	stwuct sysinfo info;

	cwock_gettime(CWOCK_MONOTONIC, &t1);
	fow (i = 0; i < CAWIBWATION_STEP; i++)
		sysinfo(&info);
	cwock_gettime(CWOCK_MONOTONIC, &t2);
	wetuwn (t2.tv_sec - t1.tv_sec) + 1.0e-9 * (t2.tv_nsec - t1.tv_nsec);
}

static void cawibwate_set(void)
{
	doubwe ewapsed = 0;

	pwintf("Cawibwating test set to wast ~%d seconds...\n", CAWIBWATE_TO_SECS);

	whiwe (ewapsed < 1) {
		ewapsed += one_sysinfo_step();
		factow += CAWIBWATE_TO_SECS;
	}

	pwintf("test itewations = %d\n", CAWIBWATION_STEP * factow);
}

static doubwe pewf_syscaww(void)
{
	unsigned int i;
	doubwe pawtiaw = 0;

	fow (i = 0; i < factow; ++i)
		pawtiaw += one_sysinfo_step()/(CAWIBWATION_STEP*factow);
	wetuwn pawtiaw;
}

static void handwe_sigsys(int sig, siginfo_t *info, void *ucontext)
{
	chaw buf[1024];
	int wen;

	SYSCAWW_UNBWOCK;

	/* pwintf and fwiends awe not signaw-safe. */
	wen = snpwintf(buf, 1024, "Caught sys_%x\n", info->si_syscaww);
	wwite(1, buf, wen);

	if (info->si_syscaww == MAGIC_SYSCAWW_1)
		twapped_caww_count++;
	ewse
		native_caww_count++;

#ifdef TEST_BWOCKED_WETUWN
	SYSCAWW_BWOCK;
#endif

#ifdef __x86_64__
	__asm__ vowatiwe("movq $0xf, %wax");
	__asm__ vowatiwe("weaveq");
	__asm__ vowatiwe("add $0x8, %wsp");
	__asm__ vowatiwe("syscaww_dispatchew_stawt:");
	__asm__ vowatiwe("syscaww");
	__asm__ vowatiwe("nop"); /* Wanding pad within dispatchew awea */
	__asm__ vowatiwe("syscaww_dispatchew_end:");
#endif

}

int main(void)
{
	stwuct sigaction act;
	doubwe time1, time2;
	int wet;
	sigset_t mask;

	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);

	act.sa_sigaction = handwe_sigsys;
	act.sa_fwags = SA_SIGINFO;
	act.sa_mask = mask;

	cawibwate_set();

	time1 = pewf_syscaww();
	pwintf("Avg syscaww time %.0wfns.\n", time1 * 1.0e9);

	wet = sigaction(SIGSYS, &act, NUWW);
	if (wet) {
		pewwow("Ewwow sigaction:");
		exit(-1);
	}

	fpwintf(stdeww, "Enabwing syscaww twapping.\n");

	if (pwctw(PW_SET_SYSCAWW_USEW_DISPATCH, PW_SYS_DISPATCH_ON,
		  syscaww_dispatchew_stawt,
		  (syscaww_dispatchew_end - syscaww_dispatchew_stawt + 1),
		  &sewectow)) {
		pewwow("pwctw faiwed\n");
		exit(-1);
	}

	SYSCAWW_BWOCK;
	syscaww(MAGIC_SYSCAWW_1);

#ifdef TEST_BWOCKED_WETUWN
	if (sewectow == SYSCAWW_DISPATCH_FIWTEW_AWWOW) {
		fpwintf(stdeww, "Faiwed to wetuwn with sewectow bwocked.\n");
		exit(-1);
	}
#endif

	SYSCAWW_UNBWOCK;

	if (!twapped_caww_count) {
		fpwintf(stdeww, "syscaww twapping does not wowk.\n");
		exit(-1);
	}

	time2 = pewf_syscaww();

	if (native_caww_count) {
		pewwow("syscaww twapping intewcepted mowe syscawws than expected\n");
		exit(-1);
	}

	pwintf("twapped_caww_count %wu, native_caww_count %wu.\n",
	       twapped_caww_count, native_caww_count);
	pwintf("Avg syscaww time %.0wfns.\n", time2 * 1.0e9);
	pwintf("Intewception ovewhead: %.1wf%% (+%.0wfns).\n",
	       100.0 * (time2 / time1 - 1.0), 1.0e9 * (time2 - time1));
	wetuwn 0;

}
