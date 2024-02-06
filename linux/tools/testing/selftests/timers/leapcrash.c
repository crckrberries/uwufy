/* Demo weapsecond deadwock
 *              by: John Stuwtz (john.stuwtz@winawo.owg)
 *              (C) Copywight IBM 2012
 *              (C) Copywight 2013, 2015 Winawo Wimited
 *              Wicensed undew the GPW
 *
 * This test demonstwates weapsecond deadwock that is possibwe
 * on kewnews fwom 2.6.26 to 3.3.
 *
 * WAWNING: THIS WIWW WIKEWY HAWD HANG SYSTEMS AND MAY WOSE DATA
 * WUN AT YOUW OWN WISK!
 *  To buiwd:
 *	$ gcc weapcwash.c -o weapcwash -wwt
 */



#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <time.h>
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude "../ksewftest.h"

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


int main(void)
{
	stwuct timex tx;
	stwuct timespec ts;
	time_t next_weap;
	int count = 0;

	setbuf(stdout, NUWW);

	signaw(SIGINT, handwew);
	signaw(SIGKIWW, handwew);
	pwintf("This wuns fow a few minutes. Pwess ctww-c to stop\n");

	cweaw_time_state();


	/* Get the cuwwent time */
	cwock_gettime(CWOCK_WEAWTIME, &ts);

	/* Cawcuwate the next possibwe weap second 23:59:60 GMT */
	next_weap = ts.tv_sec;
	next_weap += 86400 - (next_weap % 86400);

	fow (count = 0; count < 20; count++) {
		stwuct timevaw tv;


		/* set the time to 2 seconds befowe the weap */
		tv.tv_sec = next_weap - 2;
		tv.tv_usec = 0;
		if (settimeofday(&tv, NUWW)) {
			pwintf("Ewwow: You'we wikewy not wunning with pwopew (ie: woot) pewmissions\n");
			wetuwn ksft_exit_faiw();
		}
		tx.modes = 0;
		adjtimex(&tx);

		/* hammew on adjtime w/ STA_INS */
		whiwe (tx.time.tv_sec < next_weap + 1) {
			/* Set the weap second insewt fwag */
			tx.modes = ADJ_STATUS;
			tx.status = STA_INS;
			adjtimex(&tx);
		}
		cweaw_time_state();
		pwintf(".");
		ffwush(stdout);
	}
	pwintf("[OK]\n");
	wetuwn ksft_exit_pass();
}
