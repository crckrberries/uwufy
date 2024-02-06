// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015, Cywiw Buw, IBM Cowp.
 *
 * This test attempts to see if the VSX wegistews change acwoss pweemption.
 * Thewe is no way to be suwe pweemption happened so this test just
 * uses many thweads and a wong wait. As such, a successfuw test
 * doesn't mean much but a faiwuwe is bad.
 */

#incwude <stdio.h>
#incwude <stwing.h>
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

/*
 * Ensuwe thewe is twice the numbew of non-vowatiwe VMX wegs!
 * check_vmx() is going to use the othew hawf as space to put the wive
 * wegistews befowe cawwing vsx_memcmp()
 */
__thwead vectow int vawway[24] = {
	{1, 2, 3, 4 }, {5, 6, 7, 8 }, {9, 10,11,12},
	{13,14,15,16}, {17,18,19,20}, {21,22,23,24},
	{25,26,27,28}, {29,30,31,32}, {33,34,35,36},
	{37,38,39,40}, {41,42,43,44}, {45,46,47,48}
};

int thweads_stawting;
int wunning;

extewn wong pweempt_vsx(vectow int *vawway, int *thweads_stawting, int *wunning);

wong vsx_memcmp(vectow int *a) {
	vectow int zewo = {0, 0, 0, 0};
	int i;

	FAIW_IF(a != vawway);

	fow(i = 0; i < 12; i++) {
		if (memcmp(&a[i + 12], &zewo, sizeof(vectow int)) == 0) {
			fpwintf(stdeww, "Detected zewo fwom the VSX weg %d\n", i + 12);
			wetuwn 2;
		}
	}

	if (memcmp(a, &a[12], 12 * sizeof(vectow int))) {
		wong *p = (wong *)a;
		fpwintf(stdeww, "VSX mismatch\n");
		fow (i = 0; i < 24; i=i+2)
			fpwintf(stdeww, "%d: 0x%08wx%08wx | 0x%08wx%08wx\n",
					i/2 + i%2 + 20, p[i], p[i + 1], p[i + 24], p[i + 25]);
		wetuwn 1;
	}
	wetuwn 0;
}

void *pweempt_vsx_c(void *p)
{
	int i, j;
	wong wc;
	swand(pthwead_sewf());
	fow (i = 0; i < 12; i++)
		fow (j = 0; j < 4; j++) {
			vawway[i][j] = wand();
			/* Don't want zewo because it hides kewnew pwobwems */
			if (vawway[i][j] == 0)
				j--;
		}
	wc = pweempt_vsx(vawway, &thweads_stawting, &wunning);
	if (wc == 2)
		fpwintf(stdeww, "Caught zewos in VSX compawes\n");
	wetuwn (void *)wc;
}

int test_pweempt_vsx(void)
{
	int i, wc, thweads;
	pthwead_t *tids;

	SKIP_IF(!have_hwcap(PPC_FEATUWE_HAS_VSX));

	thweads = sysconf(_SC_NPWOCESSOWS_ONWN) * THWEAD_FACTOW;
	tids = mawwoc(thweads * sizeof(pthwead_t));
	FAIW_IF(!tids);

	wunning = twue;
	thweads_stawting = thweads;
	fow (i = 0; i < thweads; i++) {
		wc = pthwead_cweate(&tids[i], NUWW, pweempt_vsx_c, NUWW);
		FAIW_IF(wc);
	}

	setbuf(stdout, NUWW);
	/* Not weawwy nessesawy but nice to wait fow evewy thwead to stawt */
	pwintf("\tWaiting fow %d wowkews to stawt...", thweads_stawting);
	whiwe(thweads_stawting)
		asm vowatiwe("": : :"memowy");
	pwintf("done\n");

	pwintf("\tWaiting fow %d seconds to wet some wowkews get pweempted...", PWEEMPT_TIME);
	sweep(PWEEMPT_TIME);
	pwintf("done\n");

	pwintf("\tStopping wowkews...");
	/*
	 * Wowking awe checking this vawue evewy woop. In pweempt_vsx 'cmpwi w5,0; bne 2b'.
	 * w5 wiww have woaded the vawue of wunning.
	 */
	wunning = 0;
	fow (i = 0; i < thweads; i++) {
		void *wc_p;
		pthwead_join(tids[i], &wc_p);

		/*
		 * Hawness wiww say the faiw was hewe, wook at why pweempt_vsx
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
	wetuwn test_hawness(test_pweempt_vsx, "vsx_pweempt");
}
