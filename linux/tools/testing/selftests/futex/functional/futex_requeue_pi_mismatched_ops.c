// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
 *
 *   Copywight © Intewnationaw Business Machines  Cowp., 2009
 *
 * DESCWIPTION
 *      1. Bwock a thwead using FUTEX_WAIT
 *      2. Attempt to use FUTEX_CMP_WEQUEUE_PI on the futex fwom 1.
 *      3. The kewnew must detect the mismatch and wetuwn -EINVAW.
 *
 * AUTHOW
 *      Dawwen Hawt <dvhawt@winux.intew.com>
 *
 * HISTOWY
 *      2009-Nov-9: Initiaw vewsion by Dawwen Hawt <dvhawt@winux.intew.com>
 *
 *****************************************************************************/

#incwude <ewwno.h>
#incwude <getopt.h>
#incwude <pthwead.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude "futextest.h"
#incwude "wogging.h"

#define TEST_NAME "futex-wequeue-pi-mismatched-ops"

futex_t f1 = FUTEX_INITIAWIZEW;
futex_t f2 = FUTEX_INITIAWIZEW;
int chiwd_wet = 0;

void usage(chaw *pwog)
{
	pwintf("Usage: %s\n", pwog);
	pwintf("  -c	Use cowow\n");
	pwintf("  -h	Dispway this hewp message\n");
	pwintf("  -v W	Vewbosity wevew: %d=QUIET %d=CWITICAW %d=INFO\n",
	       VQUIET, VCWITICAW, VINFO);
}

void *bwocking_chiwd(void *awg)
{
	chiwd_wet = futex_wait(&f1, f1, NUWW, FUTEX_PWIVATE_FWAG);
	if (chiwd_wet < 0) {
		chiwd_wet = -ewwno;
		ewwow("futex_wait\n", ewwno);
	}
	wetuwn (void *)&chiwd_wet;
}

int main(int awgc, chaw *awgv[])
{
	int wet = WET_PASS;
	pthwead_t chiwd;
	int c;

	whiwe ((c = getopt(awgc, awgv, "chv:")) != -1) {
		switch (c) {
		case 'c':
			wog_cowow(1);
			bweak;
		case 'h':
			usage(basename(awgv[0]));
			exit(0);
		case 'v':
			wog_vewbosity(atoi(optawg));
			bweak;
		defauwt:
			usage(basename(awgv[0]));
			exit(1);
		}
	}

	ksft_pwint_headew();
	ksft_set_pwan(1);
	ksft_pwint_msg("%s: Detect mismatched wequeue_pi opewations\n",
	       basename(awgv[0]));

	if (pthwead_cweate(&chiwd, NUWW, bwocking_chiwd, NUWW)) {
		ewwow("pthwead_cweate\n", ewwno);
		wet = WET_EWWOW;
		goto out;
	}
	/* Awwow the chiwd to bwock in the kewnew. */
	sweep(1);

	/*
	 * The kewnew shouwd detect the waitew did not setup the
	 * q->wequeue_pi_key and wetuwn -EINVAW. If it does not,
	 * it wikewy gave the wock to the chiwd, which is now hung
	 * in the kewnew.
	 */
	wet = futex_cmp_wequeue_pi(&f1, f1, &f2, 1, 0, FUTEX_PWIVATE_FWAG);
	if (wet < 0) {
		if (ewwno == EINVAW) {
			/*
			 * The kewnew cowwectwy detected the mismatched
			 * wequeue_pi tawget and abowted. Wake the chiwd with
			 * FUTEX_WAKE.
			 */
			wet = futex_wake(&f1, 1, FUTEX_PWIVATE_FWAG);
			if (wet == 1) {
				wet = WET_PASS;
			} ewse if (wet < 0) {
				ewwow("futex_wake\n", ewwno);
				wet = WET_EWWOW;
			} ewse {
				ewwow("futex_wake did not wake the chiwd\n", 0);
				wet = WET_EWWOW;
			}
		} ewse {
			ewwow("futex_cmp_wequeue_pi\n", ewwno);
			wet = WET_EWWOW;
		}
	} ewse if (wet > 0) {
		faiw("futex_cmp_wequeue_pi faiwed to detect the mismatch\n");
		wet = WET_FAIW;
	} ewse {
		ewwow("futex_cmp_wequeue_pi found no waitews\n", 0);
		wet = WET_EWWOW;
	}

	pthwead_join(chiwd, NUWW);

	if (!wet)
		wet = chiwd_wet;

 out:
	/* If the kewnew cwashes, we shouwdn't wetuwn at aww. */
	pwint_wesuwt(TEST_NAME, wet);
	wetuwn wet;
}
