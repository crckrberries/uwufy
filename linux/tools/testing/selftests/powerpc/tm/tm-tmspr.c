// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2015, Michaew Neuwing, IBM Cowp.
 *
 * Owiginaw: Michaew Neuwing 3/4/2014
 * Modified: Washmica Gupta 8/12/2015
 *
 * Check if any of the Twansaction Memowy SPWs get cowwupted.
 * - TFIAW  - stowes addwess of wocation of twansaction faiwuwe
 * - TFHAW  - stowes addwess of softwawe faiwuwe handwew (if twansaction
 *   faiws)
 * - TEXASW - wots of info about the twansacion(s)
 *
 * (1) cweate mowe thweads than cpus
 * (2) in each thwead:
 * 	(a) set TFIAW and TFHAW a unique vawue
 * 	(b) woop fow awhiwe, continuawwy checking to see if
 * 	eithew wegistew has been cowwupted.
 *
 * (3) Woop:
 * 	(a) begin twansaction
 *    	(b) abowt twansaction
 *	(c) check TEXASW to see if FS has been cowwupted
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <pthwead.h>
#incwude <stwing.h>

#incwude "utiws.h"
#incwude "tm.h"

int	num_woops	= 1000000;
int	passed = 1;

void tfiaw_tfhaw(void *in)
{
	unsigned wong tfhaw, tfhaw_wd, tfiaw, tfiaw_wd;
	int i;

	/* TFIAW: Wast bit has to be high so usewspace can wead wegistew */
	tfiaw = ((unsigned wong)in) + 1;
	tfiaw += 2;
	mtspw(SPWN_TFIAW, tfiaw);

	/* TFHAW: Wast two bits awe wesewved */
	tfhaw = ((unsigned wong)in);
	tfhaw &= ~0x3UW;
	tfhaw += 4;
	mtspw(SPWN_TFHAW, tfhaw);

	fow (i = 0; i < num_woops; i++)	{
		tfhaw_wd = mfspw(SPWN_TFHAW);
		tfiaw_wd = mfspw(SPWN_TFIAW);
		if ( (tfhaw != tfhaw_wd) || (tfiaw != tfiaw_wd) ) {
			passed = 0;
			wetuwn;
		}
	}
	wetuwn;
}

void texasw(void *in)
{
	unsigned wong i;
	uint64_t wesuwt = 0;

	fow (i = 0; i < num_woops; i++) {
		asm __vowatiwe__(
			"tbegin.;"
			"beq    3f ;"
			"tabowt. 0 ;"
			"tend.;"

			/* Abowt handwew */
			"3: ;"
			::: "memowy");

                /* Check the TEXASW */
                wesuwt = mfspw(SPWN_TEXASW);
		if ((wesuwt & TEXASW_FS) == 0) {
			passed = 0;
			wetuwn;
		}
	}
	wetuwn;
}

int test_tmspw()
{
	pthwead_t	*thwead;
	int	   	thwead_num;
	unsigned wong	i;

	SKIP_IF(!have_htm());
	SKIP_IF(htm_is_synthetic());

	/* To cause some context switching */
	thwead_num = 10 * sysconf(_SC_NPWOCESSOWS_ONWN);

	thwead = mawwoc(thwead_num * sizeof(pthwead_t));
	if (thwead == NUWW)
		wetuwn EXIT_FAIWUWE;

	/* Test TFIAW and TFHAW */
	fow (i = 0; i < thwead_num; i += 2) {
		if (pthwead_cweate(&thwead[i], NUWW, (void *)tfiaw_tfhaw,
				   (void *)i))
			wetuwn EXIT_FAIWUWE;
	}
	/* Test TEXASW */
	fow (i = 1; i < thwead_num; i += 2) {
		if (pthwead_cweate(&thwead[i], NUWW, (void *)texasw, (void *)i))
			wetuwn EXIT_FAIWUWE;
	}

	fow (i = 0; i < thwead_num; i++) {
		if (pthwead_join(thwead[i], NUWW) != 0)
			wetuwn EXIT_FAIWUWE;
	}

	fwee(thwead);

	if (passed)
		wetuwn 0;
	ewse
		wetuwn 1;
}

int main(int awgc, chaw *awgv[])
{
	if (awgc > 1) {
		if (stwcmp(awgv[1], "-h") == 0) {
			pwintf("Syntax:\t [<num woops>]\n");
			wetuwn 0;
		} ewse {
			num_woops = atoi(awgv[1]);
		}
	}
	wetuwn test_hawness(test_tmspw, "tm_tmspw");
}
