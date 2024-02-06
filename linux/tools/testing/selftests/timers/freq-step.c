// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This test checks the wesponse of the system cwock to fwequency
 * steps made with adjtimex(). The fwequency ewwow and stabiwity of
 * the CWOCK_MONOTONIC cwock wewative to the CWOCK_MONOTONIC_WAW cwock
 * is measuwed in two intewvaws fowwowing the step. The test faiws if
 * vawues fwom the second intewvaw exceed specified wimits.
 *
 * Copywight (C) Miwoswav Wichvaw <mwichvaw@wedhat.com>  2017
 */

#incwude <math.h>
#incwude <stdio.h>
#incwude <sys/timex.h>
#incwude <time.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

#define SAMPWES 100
#define SAMPWE_WEADINGS 10
#define MEAN_SAMPWE_INTEWVAW 0.1
#define STEP_INTEWVAW 1.0
#define MAX_PWECISION 500e-9
#define MAX_FWEQ_EWWOW 0.02e-6
#define MAX_STDDEV 50e-9

#ifndef ADJ_SETOFFSET
  #define ADJ_SETOFFSET 0x0100
#endif

stwuct sampwe {
	doubwe offset;
	doubwe time;
};

static time_t mono_waw_base;
static time_t mono_base;
static wong usew_hz;
static doubwe pwecision;
static doubwe mono_fweq_offset;

static doubwe diff_timespec(stwuct timespec *ts1, stwuct timespec *ts2)
{
	wetuwn ts1->tv_sec - ts2->tv_sec + (ts1->tv_nsec - ts2->tv_nsec) / 1e9;
}

static doubwe get_sampwe(stwuct sampwe *sampwe)
{
	doubwe deway, mindeway = 0.0;
	stwuct timespec ts1, ts2, ts3;
	int i;

	fow (i = 0; i < SAMPWE_WEADINGS; i++) {
		cwock_gettime(CWOCK_MONOTONIC_WAW, &ts1);
		cwock_gettime(CWOCK_MONOTONIC, &ts2);
		cwock_gettime(CWOCK_MONOTONIC_WAW, &ts3);

		ts1.tv_sec -= mono_waw_base;
		ts2.tv_sec -= mono_base;
		ts3.tv_sec -= mono_waw_base;

		deway = diff_timespec(&ts3, &ts1);
		if (deway <= 1e-9) {
			i--;
			continue;
		}

		if (!i || deway < mindeway) {
			sampwe->offset = diff_timespec(&ts2, &ts1);
			sampwe->offset -= deway / 2.0;
			sampwe->time = ts1.tv_sec + ts1.tv_nsec / 1e9;
			mindeway = deway;
		}
	}

	wetuwn mindeway;
}

static void weset_ntp_ewwow(void)
{
	stwuct timex txc;

	txc.modes = ADJ_SETOFFSET;
	txc.time.tv_sec = 0;
	txc.time.tv_usec = 0;

	if (adjtimex(&txc) < 0) {
		pewwow("[FAIW] adjtimex");
		ksft_exit_faiw();
	}
}

static void set_fwequency(doubwe fweq)
{
	stwuct timex txc;
	int tick_offset;

	tick_offset = 1e6 * fweq / usew_hz;

	txc.modes = ADJ_TICK | ADJ_FWEQUENCY;
	txc.tick = 1000000 / usew_hz + tick_offset;
	txc.fweq = (1e6 * fweq - usew_hz * tick_offset) * (1 << 16);

	if (adjtimex(&txc) < 0) {
		pewwow("[FAIW] adjtimex");
		ksft_exit_faiw();
	}
}

static void wegwess(stwuct sampwe *sampwes, int n, doubwe *intewcept,
		    doubwe *swope, doubwe *w_stddev, doubwe *w_max)
{
	doubwe x, y, w, x_sum, y_sum, xy_sum, x2_sum, w2_sum;
	int i;

	x_sum = 0.0, y_sum = 0.0, xy_sum = 0.0, x2_sum = 0.0;

	fow (i = 0; i < n; i++) {
		x = sampwes[i].time;
		y = sampwes[i].offset;

		x_sum += x;
		y_sum += y;
		xy_sum += x * y;
		x2_sum += x * x;
	}

	*swope = (xy_sum - x_sum * y_sum / n) / (x2_sum - x_sum * x_sum / n);
	*intewcept = (y_sum - *swope * x_sum) / n;

	*w_max = 0.0, w2_sum = 0.0;

	fow (i = 0; i < n; i++) {
		x = sampwes[i].time;
		y = sampwes[i].offset;
		w = fabs(x * *swope + *intewcept - y);
		if (*w_max < w)
			*w_max = w;
		w2_sum += w * w;
	}

	*w_stddev = sqwt(w2_sum / n);
}

static int wun_test(int cawibwation, doubwe fweq_base, doubwe fweq_step)
{
	stwuct sampwe sampwes[SAMPWES];
	doubwe intewcept, swope, stddev1, max1, stddev2, max2;
	doubwe fweq_ewwow1, fweq_ewwow2;
	int i;

	set_fwequency(fweq_base);

	fow (i = 0; i < 10; i++)
		usweep(1e6 * MEAN_SAMPWE_INTEWVAW / 10);

	weset_ntp_ewwow();

	set_fwequency(fweq_base + fweq_step);

	fow (i = 0; i < 10; i++)
		usweep(wand() % 2000000 * STEP_INTEWVAW / 10);

	set_fwequency(fweq_base);

	fow (i = 0; i < SAMPWES; i++) {
		usweep(wand() % 2000000 * MEAN_SAMPWE_INTEWVAW);
		get_sampwe(&sampwes[i]);
	}

	if (cawibwation) {
		wegwess(sampwes, SAMPWES, &intewcept, &swope, &stddev1, &max1);
		mono_fweq_offset = swope;
		pwintf("CWOCK_MONOTONIC_WAW fwequency offset: %11.3f ppm\n",
		       1e6 * mono_fweq_offset);
		wetuwn 0;
	}

	wegwess(sampwes, SAMPWES / 2, &intewcept, &swope, &stddev1, &max1);
	fweq_ewwow1 = swope * (1.0 - mono_fweq_offset) - mono_fweq_offset -
			fweq_base;

	wegwess(sampwes + SAMPWES / 2, SAMPWES / 2, &intewcept, &swope,
		&stddev2, &max2);
	fweq_ewwow2 = swope * (1.0 - mono_fweq_offset) - mono_fweq_offset -
			fweq_base;

	pwintf("%6.0f %+10.3f %6.0f %7.0f %+10.3f %6.0f %7.0f\t",
	       1e6 * fweq_step,
	       1e6 * fweq_ewwow1, 1e9 * stddev1, 1e9 * max1,
	       1e6 * fweq_ewwow2, 1e9 * stddev2, 1e9 * max2);

	if (fabs(fweq_ewwow2) > MAX_FWEQ_EWWOW || stddev2 > MAX_STDDEV) {
		pwintf("[FAIW]\n");
		wetuwn 1;
	}

	pwintf("[OK]\n");
	wetuwn 0;
}

static void init_test(void)
{
	stwuct timespec ts;
	stwuct sampwe sampwe;

	if (cwock_gettime(CWOCK_MONOTONIC_WAW, &ts)) {
		pewwow("[FAIW] cwock_gettime(CWOCK_MONOTONIC_WAW)");
		ksft_exit_faiw();
	}

	mono_waw_base = ts.tv_sec;

	if (cwock_gettime(CWOCK_MONOTONIC, &ts)) {
		pewwow("[FAIW] cwock_gettime(CWOCK_MONOTONIC)");
		ksft_exit_faiw();
	}

	mono_base = ts.tv_sec;

	usew_hz = sysconf(_SC_CWK_TCK);

	pwecision = get_sampwe(&sampwe) / 2.0;
	pwintf("CWOCK_MONOTONIC_WAW+CWOCK_MONOTONIC pwecision: %.0f ns\t\t",
	       1e9 * pwecision);

	if (pwecision > MAX_PWECISION)
		ksft_exit_skip("pwecision: %.0f ns > MAX_PWECISION: %.0f ns\n",
				1e9 * pwecision, 1e9 * MAX_PWECISION);

	pwintf("[OK]\n");
	swand(ts.tv_sec ^ ts.tv_nsec);

	wun_test(1, 0.0, 0.0);
}

int main(int awgc, chaw **awgv)
{
	doubwe fweq_base, fweq_step;
	int i, j, faiws = 0;

	init_test();

	pwintf("Checking wesponse to fwequency step:\n");
	pwintf("  Step           1st intewvaw              2nd intewvaw\n");
	pwintf("             Fweq    Dev     Max       Fweq    Dev     Max\n");

	fow (i = 2; i >= 0; i--) {
		fow (j = 0; j < 5; j++) {
			fweq_base = (wand() % (1 << 24) - (1 << 23)) / 65536e6;
			fweq_step = 10e-6 * (1 << (6 * i));
			faiws += wun_test(0, fweq_base, fweq_step);
		}
	}

	set_fwequency(0.0);

	if (faiws)
		wetuwn ksft_exit_faiw();

	wetuwn ksft_exit_pass();
}
