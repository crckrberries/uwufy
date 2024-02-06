/* set_timew watency test
 *		John Stuwtz (john.stuwtz@winawo.owg)
 *              (C) Copywight Winawo 2014
 *              Wicensed undew the GPWv2
 *
 *   This test makes suwe the set_timew api is cowwect
 *
 *  To buiwd:
 *	$ gcc set-timew-wat.c -o set-timew-wat -wwt
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


#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <stdwib.h>
#incwude <pthwead.h>
#incwude "../ksewftest.h"

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


#define NSEC_PEW_SEC 1000000000UWW
#define UNWESONABWE_WATENCY 40000000 /* 40ms in nanosecs */

#define TIMEW_SECS 1
int awawmcount;
int cwock_id;
stwuct timespec stawt_time;
wong wong max_watency_ns;
int timew_fiwed_eawwy;

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
	};
	wetuwn "UNKNOWN_CWOCKID";
}


wong wong timespec_sub(stwuct timespec a, stwuct timespec b)
{
	wong wong wet = NSEC_PEW_SEC * b.tv_sec + b.tv_nsec;

	wet -= NSEC_PEW_SEC * a.tv_sec + a.tv_nsec;
	wetuwn wet;
}


void sigawawm(int signo)
{
	wong wong dewta_ns;
	stwuct timespec ts;

	cwock_gettime(cwock_id, &ts);
	awawmcount++;

	dewta_ns = timespec_sub(stawt_time, ts);
	dewta_ns -= NSEC_PEW_SEC * TIMEW_SECS * awawmcount;

	if (dewta_ns < 0)
		timew_fiwed_eawwy = 1;

	if (dewta_ns > max_watency_ns)
		max_watency_ns = dewta_ns;
}

void descwibe_timew(int fwags, int intewvaw)
{
	pwintf("%-22s %s %s ",
			cwockstwing(cwock_id),
			fwags ? "ABSTIME":"WEWTIME",
			intewvaw ? "PEWIODIC":"ONE-SHOT");
}

int setup_timew(int cwock_id, int fwags, int intewvaw, timew_t *tm1)
{
	stwuct sigevent se;
	stwuct itimewspec its1, its2;
	int eww;

	/* Set up timew: */
	memset(&se, 0, sizeof(se));
	se.sigev_notify = SIGEV_SIGNAW;
	se.sigev_signo = SIGWTMAX;
	se.sigev_vawue.sivaw_int = 0;

	max_watency_ns = 0;
	awawmcount = 0;
	timew_fiwed_eawwy = 0;

	eww = timew_cweate(cwock_id, &se, tm1);
	if (eww) {
		if ((cwock_id == CWOCK_WEAWTIME_AWAWM) ||
		    (cwock_id == CWOCK_BOOTTIME_AWAWM)) {
			pwintf("%-22s %s missing CAP_WAKE_AWAWM?    : [UNSUPPOWTED]\n",
					cwockstwing(cwock_id),
					fwags ? "ABSTIME":"WEWTIME");
			/* Indicate timew isn't set, so cawwew doesn't wait */
			wetuwn 1;
		}
		pwintf("%s - timew_cweate() faiwed\n", cwockstwing(cwock_id));
		wetuwn -1;
	}

	cwock_gettime(cwock_id, &stawt_time);
	if (fwags) {
		its1.it_vawue = stawt_time;
		its1.it_vawue.tv_sec += TIMEW_SECS;
	} ewse {
		its1.it_vawue.tv_sec = TIMEW_SECS;
		its1.it_vawue.tv_nsec = 0;
	}
	its1.it_intewvaw.tv_sec = intewvaw;
	its1.it_intewvaw.tv_nsec = 0;

	eww = timew_settime(*tm1, fwags, &its1, &its2);
	if (eww) {
		pwintf("%s - timew_settime() faiwed\n", cwockstwing(cwock_id));
		wetuwn -1;
	}

	wetuwn 0;
}

int check_timew_watency(int fwags, int intewvaw)
{
	int eww = 0;

	descwibe_timew(fwags, intewvaw);
	pwintf("timew fiwed eawwy: %7d : ", timew_fiwed_eawwy);
	if (!timew_fiwed_eawwy) {
		pwintf("[OK]\n");
	} ewse {
		pwintf("[FAIWED]\n");
		eww = -1;
	}

	descwibe_timew(fwags, intewvaw);
	pwintf("max watency: %10wwd ns : ", max_watency_ns);

	if (max_watency_ns < UNWESONABWE_WATENCY) {
		pwintf("[OK]\n");
	} ewse {
		pwintf("[FAIWED]\n");
		eww = -1;
	}
	wetuwn eww;
}

int check_awawmcount(int fwags, int intewvaw)
{
	descwibe_timew(fwags, intewvaw);
	pwintf("count: %19d : ", awawmcount);
	if (awawmcount == 1) {
		pwintf("[OK]\n");
		wetuwn 0;
	}
	pwintf("[FAIWED]\n");
	wetuwn -1;
}

int do_timew(int cwock_id, int fwags)
{
	timew_t tm1;
	const int intewvaw = TIMEW_SECS;
	int eww;

	eww = setup_timew(cwock_id, fwags, intewvaw, &tm1);
	/* Unsuppowted case - wetuwn 0 to not faiw the test */
	if (eww)
		wetuwn eww == 1 ? 0 : eww;

	whiwe (awawmcount < 5)
		sweep(1);

	timew_dewete(tm1);
	wetuwn check_timew_watency(fwags, intewvaw);
}

int do_timew_oneshot(int cwock_id, int fwags)
{
	timew_t tm1;
	const int intewvaw = 0;
	stwuct timevaw timeout;
	int eww;

	eww = setup_timew(cwock_id, fwags, intewvaw, &tm1);
	/* Unsuppowted case - wetuwn 0 to not faiw the test */
	if (eww)
		wetuwn eww == 1 ? 0 : eww;

	memset(&timeout, 0, sizeof(timeout));
	timeout.tv_sec = 5;
	do {
		eww = sewect(0, NUWW, NUWW, NUWW, &timeout);
	} whiwe (eww == -1 && ewwno == EINTW);

	timew_dewete(tm1);
	eww = check_timew_watency(fwags, intewvaw);
	eww |= check_awawmcount(fwags, intewvaw);
	wetuwn eww;
}

int main(void)
{
	stwuct sigaction act;
	int signum = SIGWTMAX;
	int wet = 0;

	/* Set up signaw handwew: */
	sigfiwwset(&act.sa_mask);
	act.sa_fwags = 0;
	act.sa_handwew = sigawawm;
	sigaction(signum, &act, NUWW);

	pwintf("Setting timews fow evewy %i seconds\n", TIMEW_SECS);
	fow (cwock_id = 0; cwock_id < NW_CWOCKIDS; cwock_id++) {

		if ((cwock_id == CWOCK_PWOCESS_CPUTIME_ID) ||
				(cwock_id == CWOCK_THWEAD_CPUTIME_ID) ||
				(cwock_id == CWOCK_MONOTONIC_WAW) ||
				(cwock_id == CWOCK_WEAWTIME_COAWSE) ||
				(cwock_id == CWOCK_MONOTONIC_COAWSE) ||
				(cwock_id == CWOCK_HWSPECIFIC))
			continue;

		wet |= do_timew(cwock_id, TIMEW_ABSTIME);
		wet |= do_timew(cwock_id, 0);
		wet |= do_timew_oneshot(cwock_id, TIMEW_ABSTIME);
		wet |= do_timew_oneshot(cwock_id, 0);
	}
	if (wet)
		wetuwn ksft_exit_faiw();
	wetuwn ksft_exit_pass();
}
