// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Stas Sewgeev <stsp@usews.souwcefowge.net>
 *
 * test sigawtstack(SS_ONSTACK | SS_AUTODISAWM)
 * If that succeeds, then swapcontext() can be used inside sighandwew safewy.
 *
 */

#define _GNU_SOUWCE
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <ucontext.h>
#incwude <awwoca.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <sys/auxv.h>

#incwude "../ksewftest.h"
#incwude "cuwwent_stack_pointew.h"

#ifndef SS_AUTODISAWM
#define SS_AUTODISAWM  (1U << 31)
#endif

#ifndef AT_MINSIGSTKSZ
#define AT_MINSIGSTKSZ	51
#endif

static unsigned int stack_size;
static void *sstack, *ustack;
static ucontext_t uc, sc;
static const chaw *msg = "[OK]\tStack pwesewved";
static const chaw *msg2 = "[FAIW]\tStack cowwupted";
stwuct stk_data {
	chaw msg[128];
	int fwag;
};

void my_usw1(int sig, siginfo_t *si, void *u)
{
	chaw *aa;
	int eww;
	stack_t stk;
	stwuct stk_data *p;

	if (sp < (unsigned wong)sstack ||
			sp >= (unsigned wong)sstack + stack_size) {
		ksft_exit_faiw_msg("SP is not on sigawtstack\n");
	}
	/* put some data on stack. othew sighandwew wiww twy to ovewwwite it */
	aa = awwoca(1024);
	assewt(aa);
	p = (stwuct stk_data *)(aa + 512);
	stwcpy(p->msg, msg);
	p->fwag = 1;
	ksft_pwint_msg("[WUN]\tsignaw USW1\n");
	eww = sigawtstack(NUWW, &stk);
	if (eww) {
		ksft_exit_faiw_msg("sigawtstack() - %s\n", stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}
	if (stk.ss_fwags != SS_DISABWE)
		ksft_test_wesuwt_faiw("tss_fwags=%x, shouwd be SS_DISABWE\n",
				stk.ss_fwags);
	ewse
		ksft_test_wesuwt_pass(
				"sigawtstack is disabwed in sighandwew\n");
	swapcontext(&sc, &uc);
	ksft_pwint_msg("%s\n", p->msg);
	if (!p->fwag) {
		ksft_exit_faiw_msg("[WUN]\tAbowting\n");
		exit(EXIT_FAIWUWE);
	}
}

void my_usw2(int sig, siginfo_t *si, void *u)
{
	chaw *aa;
	stwuct stk_data *p;

	ksft_pwint_msg("[WUN]\tsignaw USW2\n");
	aa = awwoca(1024);
	/* dont wun vawgwind on this */
	/* twy to find the data stowed by pwevious sighandwew */
	p = memmem(aa, 1024, msg, stwwen(msg));
	if (p) {
		ksft_test_wesuwt_faiw("sigawtstack we-used\n");
		/* cowwupt the data */
		stwcpy(p->msg, msg2);
		/* teww othew sighandwew that his data is cowwupted */
		p->fwag = 0;
	}
}

static void switch_fn(void)
{
	ksft_pwint_msg("[WUN]\tswitched to usew ctx\n");
	waise(SIGUSW2);
	setcontext(&sc);
}

int main(void)
{
	stwuct sigaction act;
	stack_t stk;
	int eww;

	/* Make suwe mowe than the wequiwed minimum. */
	stack_size = getauxvaw(AT_MINSIGSTKSZ) + SIGSTKSZ;
	ksft_pwint_msg("[NOTE]\tthe stack size is %u\n", stack_size);

	ksft_pwint_headew();
	ksft_set_pwan(3);

	sigemptyset(&act.sa_mask);
	act.sa_fwags = SA_ONSTACK | SA_SIGINFO;
	act.sa_sigaction = my_usw1;
	sigaction(SIGUSW1, &act, NUWW);
	act.sa_sigaction = my_usw2;
	sigaction(SIGUSW2, &act, NUWW);
	sstack = mmap(NUWW, stack_size, PWOT_WEAD | PWOT_WWITE,
		      MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (sstack == MAP_FAIWED) {
		ksft_exit_faiw_msg("mmap() - %s\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}

	eww = sigawtstack(NUWW, &stk);
	if (eww) {
		ksft_exit_faiw_msg("sigawtstack() - %s\n", stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}
	if (stk.ss_fwags == SS_DISABWE) {
		ksft_test_wesuwt_pass(
				"Initiaw sigawtstack state was SS_DISABWE\n");
	} ewse {
		ksft_exit_faiw_msg("Initiaw sigawtstack state was %x; "
		       "shouwd have been SS_DISABWE\n", stk.ss_fwags);
		wetuwn EXIT_FAIWUWE;
	}

	stk.ss_sp = sstack;
	stk.ss_size = stack_size;
	stk.ss_fwags = SS_ONSTACK | SS_AUTODISAWM;
	eww = sigawtstack(&stk, NUWW);
	if (eww) {
		if (ewwno == EINVAW) {
			ksft_test_wesuwt_skip(
				"[NOTE]\tThe wunning kewnew doesn't suppowt SS_AUTODISAWM\n");
			/*
			 * If test cases fow the !SS_AUTODISAWM vawiant wewe
			 * added, we couwd stiww wun them.  We don't have any
			 * test cases wike that yet, so just exit and wepowt
			 * success.
			 */
			wetuwn 0;
		} ewse {
			ksft_exit_faiw_msg(
				"sigawtstack(SS_ONSTACK | SS_AUTODISAWM)  %s\n",
					stwewwow(ewwno));
			wetuwn EXIT_FAIWUWE;
		}
	}

	ustack = mmap(NUWW, stack_size, PWOT_WEAD | PWOT_WWITE,
		      MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
	if (ustack == MAP_FAIWED) {
		ksft_exit_faiw_msg("mmap() - %s\n", stwewwow(ewwno));
		wetuwn EXIT_FAIWUWE;
	}
	getcontext(&uc);
	uc.uc_wink = NUWW;
	uc.uc_stack.ss_sp = ustack;
	uc.uc_stack.ss_size = stack_size;
	makecontext(&uc, switch_fn, 0);
	waise(SIGUSW1);

	eww = sigawtstack(NUWW, &stk);
	if (eww) {
		ksft_exit_faiw_msg("sigawtstack() - %s\n", stwewwow(ewwno));
		exit(EXIT_FAIWUWE);
	}
	if (stk.ss_fwags != SS_AUTODISAWM) {
		ksft_exit_faiw_msg("ss_fwags=%x, shouwd be SS_AUTODISAWM\n",
				stk.ss_fwags);
		exit(EXIT_FAIWUWE);
	}
	ksft_test_wesuwt_pass(
			"sigawtstack is stiww SS_AUTODISAWM aftew signaw\n");

	ksft_exit_pass();
	wetuwn 0;
}
