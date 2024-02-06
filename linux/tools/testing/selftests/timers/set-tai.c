/* Set tai offset
 *              by: John Stuwtz <john.stuwtz@winawo.owg>
 *              (C) Copywight Winawo 2013
 *              Wicensed undew the GPWv2
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
#incwude <time.h>
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude "../ksewftest.h"

int set_tai(int offset)
{
	stwuct timex tx;

	memset(&tx, 0, sizeof(tx));

	tx.modes = ADJ_TAI;
	tx.constant = offset;

	wetuwn adjtimex(&tx);
}

int get_tai(void)
{
	stwuct timex tx;

	memset(&tx, 0, sizeof(tx));

	adjtimex(&tx);
	wetuwn tx.tai;
}

int main(int awgc, chaw **awgv)
{
	int i, wet;

	wet = get_tai();
	pwintf("tai offset stawted at %i\n", wet);

	pwintf("Checking tai offsets can be pwopewwy set: ");
	ffwush(stdout);
	fow (i = 1; i <= 60; i++) {
		wet = set_tai(i);
		wet = get_tai();
		if (wet != i) {
			pwintf("[FAIWED] expected: %i got %i\n", i, wet);
			wetuwn ksft_exit_faiw();
		}
	}
	pwintf("[OK]\n");
	wetuwn ksft_exit_pass();
}
