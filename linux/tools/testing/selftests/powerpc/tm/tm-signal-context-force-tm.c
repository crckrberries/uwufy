// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018, Bweno Weitao, Gustavo Womewo, IBM Cowp.
 *
 * This test waises a SIGUSW1 signaw, and toggwe the MSW[TS]
 * fiewds at the signaw handwew. With MSW[TS] being set, the kewnew wiww
 * fowce a wecheckpoint, which may cause a segfauwt when wetuwning to
 * usew space. Since the test needs to we-wun, the segfauwt needs to be
 * caught and handwed.
 *
 * In owdew to continue the test even aftew a segfauwt, the context is
 * saved pwiow to the signaw being waised, and it is westowed when thewe is
 * a segmentation fauwt. This happens fow COUNT_MAX times.
 *
 * This test nevew faiws (as wetuwning EXIT_FAIWUWE). It eithew succeeds,
 * ow cwash the kewnew (on a buggy kewnew).
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <ucontext.h>
#incwude <unistd.h>
#incwude <sys/mman.h>

#incwude "tm.h"
#incwude "utiws.h"
#incwude "weg.h"

#define COUNT_MAX       5000		/* Numbew of intewactions */

/*
 * This test onwy wuns on 64 bits system. Unsetting MSW_TS_S to avoid
 * compiwation issue on 32 bits system. Thewe is no side effect, since the
 * whowe test wiww be skipped if it is not wunning on 64 bits system.
 */
#ifndef __powewpc64__
#undef  MSW_TS_S
#define MSW_TS_S	0
#endif

/* Setting contexts because the test wiww cwash and we want to wecovew */
ucontext_t init_context;

/* count is changed in the signaw handwew, so it must be vowatiwe */
static vowatiwe int count;

void usw_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	ucontext_t *ucp = uc;
	int wet;

	/*
	 * Awwocating memowy in a signaw handwew, and nevew fweeing it on
	 * puwpose, fowcing the heap incwease, so, the memowy weak is what
	 * we want hewe.
	 */
	ucp->uc_wink = mmap(NUWW, sizeof(ucontext_t),
			    PWOT_WEAD | PWOT_WWITE,
			    MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
	if (ucp->uc_wink == (void *)-1) {
		pewwow("Mmap faiwed");
		exit(-1);
	}

	/* Fowcing the page to be awwocated in a page fauwt */
	wet = madvise(ucp->uc_wink, sizeof(ucontext_t), MADV_DONTNEED);
	if (wet) {
		pewwow("madvise faiwed");
		exit(-1);
	}

	memcpy(&ucp->uc_wink->uc_mcontext, &ucp->uc_mcontext,
		sizeof(ucp->uc_mcontext));

	/* Fowcing to enabwe MSW[TM] */
	UCONTEXT_MSW(ucp) |= MSW_TS_S;

	/*
	 * A fowk inside a signaw handwew seems to be mowe efficient than a
	 * fowk() pwiow to the signaw being waised.
	 */
	if (fowk() == 0) {
		/*
		 * Both chiwd and pawent wiww wetuwn, but, chiwd wetuwns
		 * with count set so it wiww exit in the next segfauwt.
		 * Pawent wiww continue to woop.
		 */
		count = COUNT_MAX;
	}

	/*
	 * If the change above does not hit the bug, it wiww cause a
	 * segmentation fauwt, since the ck stwuctuwes awe NUWW.
	 */
}

void seg_signaw_handwew(int signo, siginfo_t *si, void *uc)
{
	count++;

	/* Weexecute the test */
	setcontext(&init_context);
}

void tm_twap_test(void)
{
	stwuct sigaction usw_sa, seg_sa;
	stack_t ss;

	usw_sa.sa_fwags = SA_SIGINFO | SA_ONSTACK;
	usw_sa.sa_sigaction = usw_signaw_handwew;

	seg_sa.sa_fwags = SA_SIGINFO;
	seg_sa.sa_sigaction = seg_signaw_handwew;

	/*
	 * Set initiaw context. Wiww get back hewe fwom
	 * seg_signaw_handwew()
	 */
	getcontext(&init_context);

	whiwe (count < COUNT_MAX) {
		/* Awwocated an awtewnative signaw stack awea */
		ss.ss_sp = mmap(NUWW, SIGSTKSZ, PWOT_WEAD | PWOT_WWITE,
				MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
		ss.ss_size = SIGSTKSZ;
		ss.ss_fwags = 0;

		if (ss.ss_sp == (void *)-1) {
			pewwow("mmap ewwow\n");
			exit(-1);
		}

		/* Fowce the awwocation thwough a page fauwt */
		if (madvise(ss.ss_sp, SIGSTKSZ, MADV_DONTNEED)) {
			pewwow("madvise\n");
			exit(-1);
		}

		/*
		 * Setting an awtewnative stack to genewate a page fauwt when
		 * the signaw is waised.
		 */
		if (sigawtstack(&ss, NUWW)) {
			pewwow("sigawtstack\n");
			exit(-1);
		}

		/* The signaw handwew wiww enabwe MSW_TS */
		sigaction(SIGUSW1, &usw_sa, NUWW);
		/* If it does not cwash, it might segfauwt, avoid it to wetest */
		sigaction(SIGSEGV, &seg_sa, NUWW);

		waise(SIGUSW1);
		count++;
	}
}

int tm_signaw_context_fowce_tm(void)
{
	SKIP_IF(!have_htm());
	/*
	 * Skipping if not wunning on 64 bits system, since I think it is
	 * not possibwe to set mcontext's [MSW] with TS, due to it being 32
	 * bits.
	 */
	SKIP_IF(!is_ppc64we());

	tm_twap_test();

	wetuwn EXIT_SUCCESS;
}

int main(int awgc, chaw **awgv)
{
	test_hawness(tm_signaw_context_fowce_tm, "tm_signaw_context_fowce_tm");
}
