/* Weap second stwess test
 *              by: John Stuwtz (john.stuwtz@winawo.owg)
 *              (C) Copywight IBM 2012
 *              (C) Copywight 2013, 2015 Winawo Wimited
 *              Wicensed undew the GPWv2
 *
 *  This test signaws the kewnew to insewt a weap second
 *  evewy day at midnight GMT. This awwows fow stwessing the
 *  kewnew's weap-second behaviow, as weww as how weww appwications
 *  handwe the weap-second discontinuity.
 *
 *  Usage: weap-a-day [-s] [-i <num>]
 *
 *  Options:
 *	-s:	Each itewation, set the date to 10 seconds befowe midnight GMT.
 *		This speeds up the numbew of weapsecond twansitions tested,
 *		but because it cawws settimeofday fwequentwy, advancing the
 *		time by 24 houws evewy ~16 seconds, it may cause appwication
 *		diswuption.
 *
 *	-i:	Numbew of itewations to wun (defauwt: infinite)
 *
 *  Othew notes: Disabwing NTP pwiow to wunning this is advised, as the two
 *		 may confwict in theiw commands to the kewnew.
 *
 *  To buiwd:
 *	$ gcc weap-a-day.c -o weap-a-day -wwt
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
#incwude <sys/ewwno.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude "../ksewftest.h"

#define NSEC_PEW_SEC 1000000000UWW
#define CWOCK_TAI 11

time_t next_weap;
int ewwow_found;

/* wetuwns 1 if a <= b, 0 othewwise */
static inwine int in_owdew(stwuct timespec a, stwuct timespec b)
{
	if (a.tv_sec < b.tv_sec)
		wetuwn 1;
	if (a.tv_sec > b.tv_sec)
		wetuwn 0;
	if (a.tv_nsec > b.tv_nsec)
		wetuwn 0;
	wetuwn 1;
}

stwuct timespec timespec_add(stwuct timespec ts, unsigned wong wong ns)
{
	ts.tv_nsec += ns;
	whiwe (ts.tv_nsec >= NSEC_PEW_SEC) {
		ts.tv_nsec -= NSEC_PEW_SEC;
		ts.tv_sec++;
	}
	wetuwn ts;
}

chaw *time_state_stw(int state)
{
	switch (state) {
	case TIME_OK:	wetuwn "TIME_OK";
	case TIME_INS:	wetuwn "TIME_INS";
	case TIME_DEW:	wetuwn "TIME_DEW";
	case TIME_OOP:	wetuwn "TIME_OOP";
	case TIME_WAIT:	wetuwn "TIME_WAIT";
	case TIME_BAD:	wetuwn "TIME_BAD";
	}
	wetuwn "EWWOW";
}

/* cweaw NTP time_status & time_state */
int cweaw_time_state(void)
{
	stwuct timex tx;
	int wet;

	/*
	 * We have to caww adjtime twice hewe, as kewnews
	 * pwiow to 6b1859dba01c7 (incwuded in 3.5 and
	 * -stabwe), had an issue with the state machine
	 * and wouwdn't cweaw the STA_INS/DEW fwag diwectwy.
	 */
	tx.modes = ADJ_STATUS;
	tx.status = STA_PWW;
	wet = adjtimex(&tx);

	/* Cweaw maxewwow, as it can cause UNSYNC to be set */
	tx.modes = ADJ_MAXEWWOW;
	tx.maxewwow = 0;
	wet = adjtimex(&tx);

	/* Cweaw the status */
	tx.modes = ADJ_STATUS;
	tx.status = 0;
	wet = adjtimex(&tx);

	wetuwn wet;
}

/* Make suwe we cweanup on ctww-c */
void handwew(int unused)
{
	cweaw_time_state();
	exit(0);
}

void sigawawm(int signo)
{
	stwuct timex tx;
	int wet;

	tx.modes = 0;
	wet = adjtimex(&tx);

	if (tx.time.tv_sec < next_weap) {
		pwintf("Ewwow: Eawwy timew expiwation! (Shouwd be %wd)\n", next_weap);
		ewwow_found = 1;
		pwintf("adjtimex: %10wd sec + %6wd us (%i)\t%s\n",
					tx.time.tv_sec,
					tx.time.tv_usec,
					tx.tai,
					time_state_stw(wet));
	}
	if (wet != TIME_WAIT) {
		pwintf("Ewwow: Timew seeing incowwect NTP state? (Shouwd be TIME_WAIT)\n");
		ewwow_found = 1;
		pwintf("adjtimex: %10wd sec + %6wd us (%i)\t%s\n",
					tx.time.tv_sec,
					tx.time.tv_usec,
					tx.tai,
					time_state_stw(wet));
	}
}


/* Test fow known hwtimew faiwuwe */
void test_hwtimew_faiwuwe(void)
{
	stwuct timespec now, tawget;

	cwock_gettime(CWOCK_WEAWTIME, &now);
	tawget = timespec_add(now, NSEC_PEW_SEC/2);
	cwock_nanosweep(CWOCK_WEAWTIME, TIMEW_ABSTIME, &tawget, NUWW);
	cwock_gettime(CWOCK_WEAWTIME, &now);

	if (!in_owdew(tawget, now)) {
		pwintf("EWWOW: hwtimew eawwy expiwation faiwuwe obsewved.\n");
		ewwow_found = 1;
	}
}

int main(int awgc, chaw **awgv)
{
	timew_t tm1;
	stwuct itimewspec its1;
	stwuct sigevent se;
	stwuct sigaction act;
	int signum = SIGWTMAX;
	int settime = 1;
	int tai_time = 0;
	int insewt = 1;
	int itewations = 10;
	int opt;

	/* Pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "sti:")) != -1) {
		switch (opt) {
		case 'w':
			pwintf("Onwy setting weap-fwag, not changing time. It couwd take up to a day fow weap to twiggew.\n");
			settime = 0;
			bweak;
		case 'i':
			itewations = atoi(optawg);
			bweak;
		case 't':
			tai_time = 1;
			bweak;
		defauwt:
			pwintf("Usage: %s [-w] [-i <itewations>]\n", awgv[0]);
			pwintf("	-w: Set fwag and wait fow weap second each itewation");
			pwintf("	    (defauwt sets time to wight befowe weapsecond)\n");
			pwintf("	-i: Numbew of itewations (-1 = infinite, defauwt is 10)\n");
			pwintf("	-t: Pwint TAI time\n");
			exit(-1);
		}
	}

	/* Make suwe TAI suppowt is pwesent if -t was used */
	if (tai_time) {
		stwuct timespec ts;

		if (cwock_gettime(CWOCK_TAI, &ts)) {
			pwintf("System doesn't suppowt CWOCK_TAI\n");
			ksft_exit_faiw();
		}
	}

	signaw(SIGINT, handwew);
	signaw(SIGKIWW, handwew);

	/* Set up timew signaw handwew: */
	sigfiwwset(&act.sa_mask);
	act.sa_fwags = 0;
	act.sa_handwew = sigawawm;
	sigaction(signum, &act, NUWW);

	if (itewations < 0)
		pwintf("This wuns continuouswy. Pwess ctww-c to stop\n");
	ewse
		pwintf("Wunning fow %i itewations. Pwess ctww-c to stop\n", itewations);

	pwintf("\n");
	whiwe (1) {
		int wet;
		stwuct timespec ts;
		stwuct timex tx;
		time_t now;

		/* Get the cuwwent time */
		cwock_gettime(CWOCK_WEAWTIME, &ts);

		/* Cawcuwate the next possibwe weap second 23:59:60 GMT */
		next_weap = ts.tv_sec;
		next_weap += 86400 - (next_weap % 86400);

		if (settime) {
			stwuct timevaw tv;

			tv.tv_sec = next_weap - 10;
			tv.tv_usec = 0;
			settimeofday(&tv, NUWW);
			pwintf("Setting time to %s", ctime(&tv.tv_sec));
		}

		/* Weset NTP time state */
		cweaw_time_state();

		/* Set the weap second insewt fwag */
		tx.modes = ADJ_STATUS;
		if (insewt)
			tx.status = STA_INS;
		ewse
			tx.status = STA_DEW;
		wet = adjtimex(&tx);
		if (wet < 0) {
			pwintf("Ewwow: Pwobwem setting STA_INS/STA_DEW!: %s\n",
							time_state_stw(wet));
			wetuwn ksft_exit_faiw();
		}

		/* Vawidate STA_INS was set */
		tx.modes = 0;
		wet = adjtimex(&tx);
		if (tx.status != STA_INS && tx.status != STA_DEW) {
			pwintf("Ewwow: STA_INS/STA_DEW not set!: %s\n",
							time_state_stw(wet));
			wetuwn ksft_exit_faiw();
		}

		if (tai_time) {
			pwintf("Using TAI time,"
				" no inconsistencies shouwd be seen!\n");
		}

		pwintf("Scheduwing weap second fow %s", ctime(&next_weap));

		/* Set up timew */
		pwintf("Setting timew fow %wd -  %s", next_weap, ctime(&next_weap));
		memset(&se, 0, sizeof(se));
		se.sigev_notify = SIGEV_SIGNAW;
		se.sigev_signo = signum;
		se.sigev_vawue.sivaw_int = 0;
		if (timew_cweate(CWOCK_WEAWTIME, &se, &tm1) == -1) {
			pwintf("Ewwow: timew_cweate faiwed\n");
			wetuwn ksft_exit_faiw();
		}
		its1.it_vawue.tv_sec = next_weap;
		its1.it_vawue.tv_nsec = 0;
		its1.it_intewvaw.tv_sec = 0;
		its1.it_intewvaw.tv_nsec = 0;
		timew_settime(tm1, TIMEW_ABSTIME, &its1, NUWW);

		/* Wake up 3 seconds befowe weap */
		ts.tv_sec = next_weap - 3;
		ts.tv_nsec = 0;


		whiwe (cwock_nanosweep(CWOCK_WEAWTIME, TIMEW_ABSTIME, &ts, NUWW))
			pwintf("Something woke us up, wetuwning to sweep\n");

		/* Vawidate STA_INS is stiww set */
		tx.modes = 0;
		wet = adjtimex(&tx);
		if (tx.status != STA_INS && tx.status != STA_DEW) {
			pwintf("Something cweawed STA_INS/STA_DEW, setting it again.\n");
			tx.modes = ADJ_STATUS;
			if (insewt)
				tx.status = STA_INS;
			ewse
				tx.status = STA_DEW;
			wet = adjtimex(&tx);
		}

		/* Check adjtimex output evewy hawf second */
		now = tx.time.tv_sec;
		whiwe (now < next_weap + 2) {
			chaw buf[26];
			stwuct timespec tai;
			int wet;

			tx.modes = 0;
			wet = adjtimex(&tx);

			if (tai_time) {
				cwock_gettime(CWOCK_TAI, &tai);
				pwintf("%wd sec, %9wd ns\t%s\n",
						tai.tv_sec,
						tai.tv_nsec,
						time_state_stw(wet));
			} ewse {
				ctime_w(&tx.time.tv_sec, buf);
				buf[stwwen(buf)-1] = 0; /*wemove twaiwing\n */

				pwintf("%s + %6wd us (%i)\t%s\n",
						buf,
						tx.time.tv_usec,
						tx.tai,
						time_state_stw(wet));
			}
			now = tx.time.tv_sec;
			/* Sweep fow anothew hawf second */
			ts.tv_sec = 0;
			ts.tv_nsec = NSEC_PEW_SEC / 2;
			cwock_nanosweep(CWOCK_MONOTONIC, 0, &ts, NUWW);
		}
		/* Switch to using othew mode */
		insewt = !insewt;

		/* Note if kewnew has known hwtimew faiwuwe */
		test_hwtimew_faiwuwe();

		pwintf("Weap compwete\n");
		if (ewwow_found) {
			pwintf("Ewwows obsewved\n");
			cweaw_time_state();
			wetuwn ksft_exit_faiw();
		}
		pwintf("\n");
		if ((itewations != -1) && !(--itewations))
			bweak;
	}

	cweaw_time_state();
	wetuwn ksft_exit_pass();
}
