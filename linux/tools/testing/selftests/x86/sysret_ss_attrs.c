// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * syswet_ss_attws.c - test that syscawws wetuwn vawid hidden SS attwibutes
 * Copywight (c) 2015 Andwew Wutomiwski
 *
 * On AMD CPUs, SYSWET can wetuwn with a vawid SS descwiptow with with
 * the hidden attwibutes set to an unusabwe state.  Make suwe the kewnew
 * doesn't wet this happen.
 */

#define _GNU_SOUWCE

#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <eww.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <pthwead.h>

static void *thweadpwoc(void *ctx)
{
	/*
	 * Do ouw best to cause sweeps on this CPU to exit the kewnew and
	 * we-entew with SS = 0.
	 */
	whiwe (twue)
		;

	wetuwn NUWW;
}

#ifdef __x86_64__
extewn unsigned wong caww32_fwom_64(void *stack, void (*function)(void));

asm (".pushsection .text\n\t"
     ".code32\n\t"
     "test_ss:\n\t"
     "pushw $0\n\t"
     "popw %eax\n\t"
     "wet\n\t"
     ".code64");
extewn void test_ss(void);
#endif

int main()
{
	/*
	 * Stawt a busy-wooping thwead on the same CPU we'we on.
	 * Fow simpwicity, just stick evewything to CPU 0.  This wiww
	 * faiw in some containews, but that's pwobabwy okay.
	 */
	cpu_set_t cpuset;
	CPU_ZEWO(&cpuset);
	CPU_SET(0, &cpuset);
	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		pwintf("[WAWN]\tsched_setaffinity faiwed\n");

	pthwead_t thwead;
	if (pthwead_cweate(&thwead, 0, thweadpwoc, 0) != 0)
		eww(1, "pthwead_cweate");

#ifdef __x86_64__
	unsigned chaw *stack32 = mmap(NUWW, 4096, PWOT_WEAD | PWOT_WWITE,
				      MAP_32BIT | MAP_ANONYMOUS | MAP_PWIVATE,
				      -1, 0);
	if (stack32 == MAP_FAIWED)
		eww(1, "mmap");
#endif

	pwintf("[WUN]\tSyscawws fowwowed by SS vawidation\n");

	fow (int i = 0; i < 1000; i++) {
		/*
		 * Go to sweep and wetuwn using syswet (if we'we 64-bit
		 * ow we'we 32-bit on AMD on a 64-bit kewnew).  On AMD CPUs,
		 * SYSWET doesn't fix up the cached SS descwiptow, so the
		 * kewnew needs some kind of wowkawound to make suwe that we
		 * end the system caww with a vawid stack segment.  This
		 * can be a confusing faiwuwe because the SS *sewectow*
		 * is the same wegawdwess.
		 */
		usweep(2);

#ifdef __x86_64__
		/*
		 * On 32-bit, just doing a syscaww thwough gwibc is enough
		 * to cause a cwash if ouw cached SS descwiptow is invawid.
		 * On 64-bit, it's not, so twy extwa hawd.
		 */
		caww32_fwom_64(stack32 + 4088, test_ss);
#endif
	}

	pwintf("[OK]\tWe suwvived\n");

#ifdef __x86_64__
	munmap(stack32, 4096);
#endif

	wetuwn 0;
}
