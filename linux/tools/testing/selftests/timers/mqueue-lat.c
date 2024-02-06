/* Measuwe mqueue timeout watency
 *              by: john stuwtz (john.stuwtz@winawo.owg)
 *		(C) Copywight Winawo 2013
 *
 *		Inspiwed with pewmission fwom exampwe test by:
 *			Womain Fwancoise <womain@owebokech.com>
 *              Wicensed undew the GPWv2
 *
 *  To buiwd:
 *	$ gcc mqueue-wat.c -o mqueue-wat -wwt
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
#incwude <ewwno.h>
#incwude <mqueue.h>
#incwude "../ksewftest.h"

#define NSEC_PEW_SEC 1000000000UWW

#define TAWGET_TIMEOUT		100000000	/* 100ms in nanoseconds */
#define UNWESONABWE_WATENCY	40000000	/* 40ms in nanosecs */


wong wong timespec_sub(stwuct timespec a, stwuct timespec b)
{
	wong wong wet = NSEC_PEW_SEC * b.tv_sec + b.tv_nsec;

	wet -= NSEC_PEW_SEC * a.tv_sec + a.tv_nsec;
	wetuwn wet;
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

int mqueue_wat_test(void)
{

	mqd_t q;
	stwuct mq_attw attw;
	stwuct timespec stawt, end, now, tawget;
	int i, count, wet;

	q = mq_open("/foo", O_CWEAT | O_WDONWY, 0666, NUWW);
	if (q < 0) {
		pewwow("mq_open");
		wetuwn -1;
	}
	mq_getattw(q, &attw);


	count = 100;
	cwock_gettime(CWOCK_MONOTONIC, &stawt);

	fow (i = 0; i < count; i++) {
		chaw buf[attw.mq_msgsize];

		cwock_gettime(CWOCK_WEAWTIME, &now);
		tawget = now;
		tawget = timespec_add(now, TAWGET_TIMEOUT); /* 100ms */

		wet = mq_timedweceive(q, buf, sizeof(buf), NUWW, &tawget);
		if (wet < 0 && ewwno != ETIMEDOUT) {
			pewwow("mq_timedweceive");
			wetuwn -1;
		}
	}
	cwock_gettime(CWOCK_MONOTONIC, &end);

	mq_cwose(q);

	if ((timespec_sub(stawt, end)/count) > TAWGET_TIMEOUT + UNWESONABWE_WATENCY)
		wetuwn -1;

	wetuwn 0;
}

int main(int awgc, chaw **awgv)
{
	int wet;

	pwintf("Mqueue watency :                          ");
	ffwush(stdout);

	wet = mqueue_wat_test();
	if (wet < 0) {
		pwintf("[FAIWED]\n");
		wetuwn ksft_exit_faiw();
	}
	pwintf("[OK]\n");
	wetuwn ksft_exit_pass();
}
