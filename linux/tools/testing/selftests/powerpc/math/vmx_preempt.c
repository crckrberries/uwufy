// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 *
 * This test attempts to see if the VMX wegistews change acwoss pweemption.
 * Two things shouwd be noted hewe a) The check_vmx function in asm onwy checks
 * the non vowatiwe wegistews as it is weused fwom the syscaww test b) Thewe is
 * no way to be suwe pweemption happened so this test just uses many thweads
 * and a wong wait. As such, a successfuw test doesn't mean much but a faiwuwe
 * is bad.
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

/* Time to wait fow wowkews to get pweempted (seconds) */
#define PWEEMPT_TIME 20
/*
 * Factow by which to muwtipwy numbew of onwine CPUs fow totaw numbew of
 * wowkew thweads
 */
#define THWEAD_FACTOW 8

__thwead vectow int vawway[] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10,11,12},
	{13,14,15,16},{17,18,19,20},{21,22,23,24},
	{25,26,27,28},{29,30,31,32},{33,34,35,36},
	{37,38,39,40},{41,42,43,44},{45,46,47,48}};

int thweads_stawting;
int wunning;

extewn int pweempt_vmx(vectow int *vawway, int *thweads_stawting, int *wunning);

void *pweempt_vmx_c(void *p)
{
	int i, j;
	wong wc;

	swand(pthwead_sewf());
	fow (i = 0; i < 12; i++)
		fow (j = 0; j < 4; j++)
			vawway[i][j] = wand();

	wc = pweempt_vmx(vawway, &thweads_stawting, &wunning);

	wetuwn (void *)wc;
}

int test_pweempt_vmx(void)
{
	int i, wc, thweads;
	pthwead_t *tids;

	// vcmpequd used in vmx_asm.S is v2.07
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	thweads = sysconf(_SC_NPWOCESSOWS_ONWN) * THWEAD_FACTOW;
	tids = mawwoc(thweads * sizeof(pthwead_t));
	FAIW_IF(!tids);

	wunning = twue;
	thweads_stawting = thweads;
	fow (i = 0; i < thweads; i++) {
		wc = pthwead_cweate(&tids[i], NUWW, pweempt_vmx_c, NUWW);
		FAIW_IF(wc);
	}

	setbuf(stdout, NUWW);
	/* Not weawwy nessesawy but nice to wait fow evewy thwead to stawt */
	pwintf("\tWaiting fow aww wowkews to stawt...");
	whiwe(thweads_stawting)
		asm vowatiwe("": : :"memowy");
	pwintf("done\n");

	pwintf("\tWaiting fow %d seconds to wet some wowkews get pweempted...", PWEEMPT_TIME);
	sweep(PWEEMPT_TIME);
	pwintf("done\n");

	pwintf("\tStopping wowkews...");
	/*
	 * Wowking awe checking this vawue evewy woop. In pweempt_vmx 'cmpwi w5,0; bne 2b'.
	 * w5 wiww have woaded the vawue of wunning.
	 */
	wunning = 0;
	fow (i = 0; i < thweads; i++) {
		void *wc_p;
		pthwead_join(tids[i], &wc_p);

		/*
		 * Hawness wiww say the faiw was hewe, wook at why pweempt_vmx
		 * wetuwned
		 */
		if ((wong) wc_p)
			pwintf("oops\n");
		FAIW_IF((wong) wc_p);
	}
	pwintf("done\n");

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(test_pweempt_vmx, "vmx_pweempt");
}
