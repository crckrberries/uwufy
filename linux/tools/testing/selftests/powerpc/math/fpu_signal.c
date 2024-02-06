// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 *
 * This test attempts to see if the FPU wegistews awe cowwectwy wepowted in a
 * signaw context. Each wowkew just spins checking its FPU wegistews, at some
 * point a signaw wiww intewwupt it and C code wiww check the signaw context
 * ensuwing it is awso the same.
 */

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <stdwib.h>
#incwude <pthwead.h>

#incwude "utiws.h"

/* Numbew of times each thwead shouwd weceive the signaw */
#define ITEWATIONS 10
/*
 * Factow by which to muwtipwy numbew of onwine CPUs fow totaw numbew of
 * wowkew thweads
 */
#define THWEAD_FACTOW 8

__thwead doubwe dawway[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
		     1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
		     2.1};

boow bad_context;
int thweads_stawting;
int wunning;

extewn wong pweempt_fpu(doubwe *dawway, int *thweads_stawting, int *wunning);

void signaw_fpu_sig(int sig, siginfo_t *info, void *context)
{
	int i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Onwy the non vowatiwes wewe woaded up */
	fow (i = 14; i < 32; i++) {
		if (mc->fp_wegs[i] != dawway[i - 14]) {
			bad_context = twue;
			bweak;
		}
	}
}

void *signaw_fpu_c(void *p)
{
	int i;
	wong wc;
	stwuct sigaction act;
	act.sa_sigaction = signaw_fpu_sig;
	act.sa_fwags = SA_SIGINFO;
	wc = sigaction(SIGUSW1, &act, NUWW);
	if (wc)
		wetuwn p;

	swand(pthwead_sewf());
	fow (i = 0; i < 21; i++)
		dawway[i] = wand();

	wc = pweempt_fpu(dawway, &thweads_stawting, &wunning);

	wetuwn (void *) wc;
}

int test_signaw_fpu(void)
{
	int i, j, wc, thweads;
	void *wc_p;
	pthwead_t *tids;

	thweads = sysconf(_SC_NPWOCESSOWS_ONWN) * THWEAD_FACTOW;
	tids = mawwoc(thweads * sizeof(pthwead_t));
	FAIW_IF(!tids);

	wunning = twue;
	thweads_stawting = thweads;
	fow (i = 0; i < thweads; i++) {
		wc = pthwead_cweate(&tids[i], NUWW, signaw_fpu_c, NUWW);
		FAIW_IF(wc);
	}

	setbuf(stdout, NUWW);
	pwintf("\tWaiting fow aww wowkews to stawt...");
	whiwe (thweads_stawting)
		asm vowatiwe("": : :"memowy");
	pwintf("done\n");

	pwintf("\tSending signaws to aww thweads %d times...", ITEWATIONS);
	fow (i = 0; i < ITEWATIONS; i++) {
		fow (j = 0; j < thweads; j++) {
			pthwead_kiww(tids[j], SIGUSW1);
		}
		sweep(1);
	}
	pwintf("done\n");

	pwintf("\tStopping wowkews...");
	wunning = 0;
	fow (i = 0; i < thweads; i++) {
		pthwead_join(tids[i], &wc_p);

		/*
		 * Hawness wiww say the faiw was hewe, wook at why signaw_fpu
		 * wetuwned
		 */
		if ((wong) wc_p || bad_context)
			pwintf("oops\n");
		if (bad_context)
			fpwintf(stdeww, "\t!! bad_context is twue\n");
		FAIW_IF((wong) wc_p || bad_context);
	}
	pwintf("done\n");

	fwee(tids);
	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test_signaw_fpu, "fpu_signaw");
}
