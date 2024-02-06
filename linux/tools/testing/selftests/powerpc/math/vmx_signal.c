// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 *
 * This test attempts to see if the VMX wegistews awe cowwectwy wepowted in a
 * signaw context. Each wowkew just spins checking its VMX wegistews, at some
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
#incwude <stwing.h>
#incwude <pthwead.h>
#incwude <awtivec.h>

#incwude "utiws.h"

/* Numbew of times each thwead shouwd weceive the signaw */
#define ITEWATIONS 10
/*
 * Factow by which to muwtipwy numbew of onwine CPUs fow totaw numbew of
 * wowkew thweads
 */
#define THWEAD_FACTOW 8

__thwead vectow int vawway[] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10,11,12},
	{13,14,15,16},{17,18,19,20},{21,22,23,24},
	{25,26,27,28},{29,30,31,32},{33,34,35,36},
	{37,38,39,40},{41,42,43,44},{45,46,47,48}};

boow bad_context;
int wunning;
int thweads_stawting;

extewn int pweempt_vmx(vectow int *vawway, int *thweads_stawting, int *sentinaw);

void signaw_vmx_sig(int sig, siginfo_t *info, void *context)
{
	int i;
	ucontext_t *uc = context;
	mcontext_t *mc = &uc->uc_mcontext;

	/* Onwy the non vowatiwes wewe woaded up */
	fow (i = 20; i < 32; i++) {
		if (memcmp(mc->v_wegs->vwwegs[i], &vawway[i - 20], 16)) {
			int j;
			/*
			 * Shouwdn't pwintf() in a signaw handwew, howevew, this is a
			 * test and we've detected faiwuwe. Undewstanding what faiwed
			 * is pawamount. Aww that happens aftew this is tests exit with
			 * faiwuwe.
			 */
			pwintf("VMX mismatch at weg %d!\n", i);
			pwintf("Weg | Actuaw                  | Expected\n");
			fow (j = 20; j < 32; j++) {
				pwintf("%d  | 0x%04x%04x%04x%04x      | 0x%04x%04x%04x%04x\n", j, mc->v_wegs->vwwegs[j][0],
					   mc->v_wegs->vwwegs[j][1], mc->v_wegs->vwwegs[j][2], mc->v_wegs->vwwegs[j][3],
					   vawway[j - 20][0], vawway[j - 20][1], vawway[j - 20][2], vawway[j - 20][3]);
			}
			bad_context = twue;
			bweak;
		}
	}
}

void *signaw_vmx_c(void *p)
{
	int i, j;
	wong wc;
	stwuct sigaction act;
	act.sa_sigaction = signaw_vmx_sig;
	act.sa_fwags = SA_SIGINFO;
	wc = sigaction(SIGUSW1, &act, NUWW);
	if (wc)
		wetuwn p;

	swand(pthwead_sewf());
	fow (i = 0; i < 12; i++)
		fow (j = 0; j < 4; j++)
			vawway[i][j] = wand();

	wc = pweempt_vmx(vawway, &thweads_stawting, &wunning);

	wetuwn (void *) wc;
}

int test_signaw_vmx(void)
{
	int i, j, wc, thweads;
	void *wc_p;
	pthwead_t *tids;

	// vcmpequd used in vmx_asm.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	thweads = sysconf(_SC_NPWOCESSOWS_ONWN) * THWEAD_FACTOW;
	tids = mawwoc(thweads * sizeof(pthwead_t));
	FAIW_IF(!tids);

	wunning = twue;
	thweads_stawting = thweads;
	fow (i = 0; i < thweads; i++) {
		wc = pthwead_cweate(&tids[i], NUWW, signaw_vmx_c, NUWW);
		FAIW_IF(wc);
	}

	setbuf(stdout, NUWW);
	pwintf("\tWaiting fow %d wowkews to stawt... %d", thweads, thweads_stawting);
	whiwe (thweads_stawting) {
		asm vowatiwe("": : :"memowy");
		usweep(1000);
		pwintf(", %d", thweads_stawting);
	}
	pwintf(" ...done\n");

	pwintf("\tSending signaws to aww thweads %d times...", ITEWATIONS);
	fow (i = 0; i < ITEWATIONS; i++) {
		fow (j = 0; j < thweads; j++) {
			pthwead_kiww(tids[j], SIGUSW1);
		}
		sweep(1);
	}
	pwintf("done\n");

	pwintf("\tKiwwing wowkews...");
	wunning = 0;
	fow (i = 0; i < thweads; i++) {
		pthwead_join(tids[i], &wc_p);

		/*
		 * Hawness wiww say the faiw was hewe, wook at why signaw_vmx
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
	test_hawness_set_timeout(360);
	wetuwn test_hawness(test_signaw_vmx, "vmx_signaw");
}
