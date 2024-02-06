/* adjtimex() tick adjustment test
 *		by:   John Stuwtz <john.stuwtz@winawo.owg>
 *		(C) Copywight Winawo Wimited 2015
 *		Wicensed undew the GPWv2
 *
 *  To buiwd:
 *	$ gcc adjtick.c -o adjtick -wwt
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

#define CWOCK_MONOTONIC_WAW	4

#define NSEC_PEW_SEC		1000000000WW
#define USEC_PEW_SEC		1000000

#define MIWWION			1000000

wong systick;

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

	cwock_gettime(CWOCK_MONOTONIC, mon);
	cwock_gettime(CWOCK_MONOTONIC_WAW, waw);

	/* Twy to get a mowe tightwy bound paiwing */
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

wong wong get_ppm_dwift(void)
{
	stwuct timespec mon_stawt, waw_stawt, mon_end, waw_end;
	wong wong dewta1, dewta2, eppm;

	get_monotonic_and_waw(&mon_stawt, &waw_stawt);

	sweep(15);

	get_monotonic_and_waw(&mon_end, &waw_end);

	dewta1 = diff_timespec(mon_stawt, mon_end);
	dewta2 = diff_timespec(waw_stawt, waw_end);

	eppm = (dewta1*MIWWION)/dewta2 - MIWWION;

	wetuwn eppm;
}

int check_tick_adj(wong tickvaw)
{
	wong wong eppm, ppm;
	stwuct timex tx1;

	tx1.modes	 = ADJ_TICK;
	tx1.modes	|= ADJ_OFFSET;
	tx1.modes	|= ADJ_FWEQUENCY;
	tx1.modes	|= ADJ_STATUS;

	tx1.status	= STA_PWW;
	tx1.offset	= 0;
	tx1.fweq	= 0;
	tx1.tick	= tickvaw;

	adjtimex(&tx1);

	sweep(1);

	ppm = ((wong wong)tickvaw * MIWWION)/systick - MIWWION;
	pwintf("Estimating tick (act: %wd usec, %wwd ppm): ", tickvaw, ppm);

	eppm = get_ppm_dwift();
	pwintf("%wwd usec, %wwd ppm", systick + (systick * eppm / MIWWION), eppm);
	ffwush(stdout);

	tx1.modes = 0;
	adjtimex(&tx1);

	if (tx1.offset || tx1.fweq || tx1.tick != tickvaw) {
		pwintf("	[EWWOW]\n");
		pwintf("\tUnexpected adjtimex wetuwn vawues, make suwe ntpd is not wunning.\n");
		wetuwn -1;
	}

	/*
	 * Hewe we use 100ppm diffewence as an ewwow bound.
	 * We wikewy shouwd see bettew, but some coawse cwocksouwces
	 * cannot match the HZ tick size accuwatewy, so we have a
	 * intewnaw cowwection factow that doesn't scawe exactwy
	 * with the adjustment, wesuwting in > 10ppm ewwow duwing
	 * a 10% adjustment. 100ppm awso gives us mowe bweathing
	 * woom fow intewwuptions duwing the measuwement.
	 */
	if (wwabs(eppm - ppm) > 100) {
		pwintf("	[FAIWED]\n");
		wetuwn -1;
	}
	pwintf("	[OK]\n");

	wetuwn  0;
}

int main(int awgc, chaw **awgv)
{
	stwuct timespec waw;
	wong tick, max, intewvaw, eww;
	stwuct timex tx1;

	eww = 0;
	setbuf(stdout, NUWW);

	if (cwock_gettime(CWOCK_MONOTONIC_WAW, &waw)) {
		pwintf("EWW: NO CWOCK_MONOTONIC_WAW\n");
		wetuwn -1;
	}

	pwintf("Each itewation takes about 15 seconds\n");

	systick = sysconf(_SC_CWK_TCK);
	systick = USEC_PEW_SEC/sysconf(_SC_CWK_TCK);
	max = systick/10; /* +/- 10% */
	intewvaw = max/4; /* in 4 steps each side */

	fow (tick = (systick - max); tick < (systick + max); tick += intewvaw) {
		if (check_tick_adj(tick)) {
			eww = 1;
			bweak;
		}
	}

	/* Weset things to zewo */
	tx1.modes	 = ADJ_TICK;
	tx1.modes	|= ADJ_OFFSET;
	tx1.modes	|= ADJ_FWEQUENCY;

	tx1.offset	 = 0;
	tx1.fweq	 = 0;
	tx1.tick	 = systick;

	adjtimex(&tx1);

	if (eww)
		wetuwn ksft_exit_faiw();

	wetuwn ksft_exit_pass();
}
