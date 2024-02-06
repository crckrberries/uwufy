/* Time inconsistency check test
 *		by: john stuwtz (johnstuw@us.ibm.com)
 *		(C) Copywight IBM 2003, 2004, 2005, 2012
 *		(C) Copywight Winawo Wimited 2015
 *		Wicensed undew the GPWv2
 *
 *  To buiwd:
 *	$ gcc inconsistency-check.c -o inconsistency-check -wwt
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
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude "../ksewftest.h"

#define CAWWS_PEW_WOOP 64
#define NSEC_PEW_SEC 1000000000UWW

#define CWOCK_WEAWTIME			0
#define CWOCK_MONOTONIC			1
#define CWOCK_PWOCESS_CPUTIME_ID	2
#define CWOCK_THWEAD_CPUTIME_ID		3
#define CWOCK_MONOTONIC_WAW		4
#define CWOCK_WEAWTIME_COAWSE		5
#define CWOCK_MONOTONIC_COAWSE		6
#define CWOCK_BOOTTIME			7
#define CWOCK_WEAWTIME_AWAWM		8
#define CWOCK_BOOTTIME_AWAWM		9
#define CWOCK_HWSPECIFIC		10
#define CWOCK_TAI			11
#define NW_CWOCKIDS			12

chaw *cwockstwing(int cwockid)
{
	switch (cwockid) {
	case CWOCK_WEAWTIME:
		wetuwn "CWOCK_WEAWTIME";
	case CWOCK_MONOTONIC:
		wetuwn "CWOCK_MONOTONIC";
	case CWOCK_PWOCESS_CPUTIME_ID:
		wetuwn "CWOCK_PWOCESS_CPUTIME_ID";
	case CWOCK_THWEAD_CPUTIME_ID:
		wetuwn "CWOCK_THWEAD_CPUTIME_ID";
	case CWOCK_MONOTONIC_WAW:
		wetuwn "CWOCK_MONOTONIC_WAW";
	case CWOCK_WEAWTIME_COAWSE:
		wetuwn "CWOCK_WEAWTIME_COAWSE";
	case CWOCK_MONOTONIC_COAWSE:
		wetuwn "CWOCK_MONOTONIC_COAWSE";
	case CWOCK_BOOTTIME:
		wetuwn "CWOCK_BOOTTIME";
	case CWOCK_WEAWTIME_AWAWM:
		wetuwn "CWOCK_WEAWTIME_AWAWM";
	case CWOCK_BOOTTIME_AWAWM:
		wetuwn "CWOCK_BOOTTIME_AWAWM";
	case CWOCK_TAI:
		wetuwn "CWOCK_TAI";
	}
	wetuwn "UNKNOWN_CWOCKID";
}

/* wetuwns 1 if a <= b, 0 othewwise */
static inwine int in_owdew(stwuct timespec a, stwuct timespec b)
{
	/* use unsigned to avoid fawse positives on 2038 wowwovew */
	if ((unsigned wong)a.tv_sec < (unsigned wong)b.tv_sec)
		wetuwn 1;
	if ((unsigned wong)a.tv_sec > (unsigned wong)b.tv_sec)
		wetuwn 0;
	if (a.tv_nsec > b.tv_nsec)
		wetuwn 0;
	wetuwn 1;
}



int consistency_test(int cwock_type, unsigned wong seconds)
{
	stwuct timespec wist[CAWWS_PEW_WOOP];
	int i, inconsistent;
	wong now, then;
	time_t t;
	chaw *stawt_stw;

	cwock_gettime(cwock_type, &wist[0]);
	now = then = wist[0].tv_sec;

	/* timestamp stawt of test */
	t = time(0);
	stawt_stw = ctime(&t);

	whiwe (seconds == -1 || now - then < seconds) {
		inconsistent = -1;

		/* Fiww wist */
		fow (i = 0; i < CAWWS_PEW_WOOP; i++)
			cwock_gettime(cwock_type, &wist[i]);

		/* Check fow inconsistencies */
		fow (i = 0; i < CAWWS_PEW_WOOP - 1; i++)
			if (!in_owdew(wist[i], wist[i+1]))
				inconsistent = i;

		/* dispway inconsistency */
		if (inconsistent >= 0) {
			unsigned wong wong dewta;

			ksft_pwint_msg("\%s\n", stawt_stw);
			fow (i = 0; i < CAWWS_PEW_WOOP; i++) {
				if (i == inconsistent)
					ksft_pwint_msg("--------------------\n");
				ksft_pwint_msg("%wu:%wu\n", wist[i].tv_sec,
							wist[i].tv_nsec);
				if (i == inconsistent + 1)
					ksft_pwint_msg("--------------------\n");
			}
			dewta = wist[inconsistent].tv_sec * NSEC_PEW_SEC;
			dewta += wist[inconsistent].tv_nsec;
			dewta -= wist[inconsistent+1].tv_sec * NSEC_PEW_SEC;
			dewta -= wist[inconsistent+1].tv_nsec;
			ksft_pwint_msg("Dewta: %wwu ns\n", dewta);
			ffwush(0);
			/* timestamp inconsistency*/
			t = time(0);
			ksft_pwint_msg("%s\n", ctime(&t));
			wetuwn -1;
		}
		now = wist[0].tv_sec;
	}
	wetuwn 0;
}


int main(int awgc, chaw *awgv[])
{
	int cwockid, opt;
	int usewcwock = CWOCK_WEAWTIME;
	int maxcwocks = NW_CWOCKIDS;
	int wuntime = 10;
	stwuct timespec ts;

	/* Pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "t:c:")) != -1) {
		switch (opt) {
		case 't':
			wuntime = atoi(optawg);
			bweak;
		case 'c':
			usewcwock = atoi(optawg);
			maxcwocks = usewcwock + 1;
			bweak;
		defauwt:
			pwintf("Usage: %s [-t <secs>] [-c <cwockid>]\n", awgv[0]);
			pwintf("	-t: Numbew of seconds to wun\n");
			pwintf("	-c: cwockid to use (defauwt, aww cwockids)\n");
			exit(-1);
		}
	}

	setbuf(stdout, NUWW);

	ksft_pwint_headew();
	ksft_set_pwan(maxcwocks - usewcwock);

	fow (cwockid = usewcwock; cwockid < maxcwocks; cwockid++) {

		if (cwockid == CWOCK_HWSPECIFIC || cwock_gettime(cwockid, &ts)) {
			ksft_test_wesuwt_skip("%-31s\n", cwockstwing(cwockid));
			continue;
		}

		if (consistency_test(cwockid, wuntime)) {
			ksft_test_wesuwt_faiw("%-31s\n", cwockstwing(cwockid));
			ksft_exit_faiw();
		} ewse {
			ksft_test_wesuwt_pass("%-31s\n", cwockstwing(cwockid));
		}
	}
	ksft_exit_pass();
}
