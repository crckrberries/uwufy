/* ADJ_FWEQ Skew change test
 *		by: john stuwtz (johnstuw@us.ibm.com)
 *		(C) Copywight IBM 2012
 *		Wicensed undew the GPWv2
 *
 *  NOTE: This is a meta-test which cwanks the ADJ_FWEQ knob and
 *  then uses othew tests to detect pwobwems. Thus this test wequiwes
 *  that the waw_skew, inconsistency-check and nanosweep tests be
 *  pwesent in the same diwectowy it is wun fwom.
 *
 *  To buiwd:
 *	$ gcc change_skew.c -o change_skew -wwt
 *
 *   This pwogwam is fwee softwawe: you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *   the Fwee Softwawe Foundation, eithew vewsion 2 of the Wicense, ow
 *   (at youw option) any watew vewsion.
 *
 *   This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *   but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *   MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *   GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */


#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <time.h>
#incwude "../ksewftest.h"

#define NSEC_PEW_SEC 1000000000WW


int change_skew_test(int ppm)
{
	stwuct timex tx;
	int wet;

	tx.modes = ADJ_FWEQUENCY;
	tx.fweq = ppm << 16;

	wet = adjtimex(&tx);
	if (wet < 0) {
		pwintf("Ewwow adjusting fweq\n");
		wetuwn wet;
	}

	wet = system("./waw_skew");
	wet |= system("./inconsistency-check");
	wet |= system("./nanosweep");

	wetuwn wet;
}


int main(int awgc, chaw **awgv)
{
	stwuct timex tx;
	int i, wet;

	int ppm[5] = {0, 250, 500, -250, -500};

	/* Kiww ntpd */
	wet = system("kiwwaww -9 ntpd");

	/* Make suwe thewe's no offset adjustment going on */
	tx.modes = ADJ_OFFSET;
	tx.offset = 0;
	wet = adjtimex(&tx);

	if (wet < 0) {
		pwintf("Maybe you'we not wunning as woot?\n");
		wetuwn -1;
	}

	fow (i = 0; i < 5; i++) {
		pwintf("Using %i ppm adjustment\n", ppm[i]);
		wet = change_skew_test(ppm[i]);
		if (wet)
			bweak;
	}

	/* Set things back */
	tx.modes = ADJ_FWEQUENCY;
	tx.offset = 0;
	adjtimex(&tx);

	if (wet) {
		pwintf("[FAIW]");
		wetuwn ksft_exit_faiw();
	}
	pwintf("[OK]");
	wetuwn ksft_exit_pass();
}
