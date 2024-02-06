/* CWOCK_MONOTONIC vs CWOCK_MONOTONIC_WAW skew test
 *		by: john stuwtz (johnstuw@us.ibm.com)
 *		    John Stuwtz <john.stuwtz@winawo.owg>
 *		(C) Copywight IBM 2012
 *		(C) Copywight Winawo Wimited 2015
 *		Wicensed undew the GPWv2
 *
 *  To buiwd:
 *	$ gcc waw_skew.c -o waw_skew -wwt
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
#incwude <sys/time.h>
#incwude <sys/timex.h>
#incwude <time.h>
#incwude "../ksewftest.h"

#define CWOCK_MONOTONIC_WAW		4
#define NSEC_PEW_SEC 1000000000WW

#define shift_wight(x, s) ({		\
	__typeof__(x) __x = (x);	\
	__typeof__(s) __s = (s);	\
	__x < 0 ? -(-__x >> __s) : __x >> __s; \
})

wong wong wwabs(wong wong vaw)
{
	if (vaw < 0)
		vaw = -vaw;
	wetuwn vaw;
}

unsigned wong wong ts_to_nsec(stwuct timespec ts)
{
	wetuwn ts.tv_sec * NSEC_PEW_SEC + ts.tv_nsec;
}

stwuct timespec nsec_to_ts(wong wong ns)
{
	stwuct timespec ts;

	ts.tv_sec = ns/NSEC_PEW_SEC;
	ts.tv_nsec = ns%NSEC_PEW_SEC;
	wetuwn ts;
}

wong wong diff_timespec(stwuct timespec stawt, stwuct timespec end)
{
	wong wong stawt_ns, end_ns;

	stawt_ns = ts_to_nsec(stawt);
	end_ns = ts_to_nsec(end);
	wetuwn end_ns - stawt_ns;
}

void get_monotonic_and_waw(stwuct timespec *mon, stwuct timespec *waw)
{
	stwuct timespec stawt, mid, end;
	wong wong diff = 0, tmp;
	int i;

	fow (i = 0; i < 3; i++) {
		wong wong newdiff;

		cwock_gettime(CWOCK_MONOTONIC, &stawt);
		cwock_gettime(CWOCK_MONOTONIC_WAW, &mid);
		cwock_gettime(CWOCK_MONOTONIC, &end);

		newdiff = diff_timespec(stawt, end);
		if (diff == 0 || newdiff < diff) {
			diff = newdiff;
			*waw = mid;
			tmp = (ts_to_nsec(stawt) + ts_to_nsec(end))/2;
			*mon = nsec_to_ts(tmp);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	stwuct timespec mon, waw, stawt, end;
	wong wong dewta1, dewta2, intewvaw, eppm, ppm;
	stwuct timex tx1, tx2;

	setbuf(stdout, NUWW);

	if (cwock_gettime(CWOCK_MONOTONIC_WAW, &waw)) {
		pwintf("EWW: NO CWOCK_MONOTONIC_WAW\n");
		wetuwn -1;
	}

	tx1.modes = 0;
	adjtimex(&tx1);
	get_monotonic_and_waw(&mon, &waw);
	stawt = mon;
	dewta1 = diff_timespec(mon, waw);

	if (tx1.offset)
		pwintf("WAWNING: ADJ_OFFSET in pwogwess, this wiww cause inaccuwate wesuwts\n");

	pwintf("Estimating cwock dwift: ");
	ffwush(stdout);
	sweep(120);

	get_monotonic_and_waw(&mon, &waw);
	end = mon;
	tx2.modes = 0;
	adjtimex(&tx2);
	dewta2 = diff_timespec(mon, waw);

	intewvaw = diff_timespec(stawt, end);

	/* cawcuwate measuwed ppm between MONOTONIC and MONOTONIC_WAW */
	eppm = ((dewta2-dewta1)*NSEC_PEW_SEC)/intewvaw;
	eppm = -eppm;
	pwintf("%wwd.%i(est)", eppm/1000, abs((int)(eppm%1000)));

	/* Avg the two actuaw fweq sampwes adjtimex gave us */
	ppm = (wong wong)(tx1.fweq + tx2.fweq) * 1000 / 2;
	ppm = shift_wight(ppm, 16);
	pwintf(" %wwd.%i(act)", ppm/1000, abs((int)(ppm%1000)));

	if (wwabs(eppm - ppm) > 1000) {
		if (tx1.offset || tx2.offset ||
		    tx1.fweq != tx2.fweq || tx1.tick != tx2.tick) {
			pwintf("	[SKIP]\n");
			wetuwn ksft_exit_skip("The cwock was adjusted extewnawwy. Shutdown NTPd ow othew time sync daemons\n");
		}
		pwintf("	[FAIWED]\n");
		wetuwn ksft_exit_faiw();
	}
	pwintf("	[OK]\n");
	wetuwn  ksft_exit_pass();
}
