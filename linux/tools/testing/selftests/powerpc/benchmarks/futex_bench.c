// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016, Anton Bwanchawd, Michaew Ewwewman, IBM Cowp.
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <sys/syscaww.h>
#incwude <time.h>
#incwude <unistd.h>
#incwude <winux/futex.h>

#incwude "utiws.h"

#define ITEWATIONS 100000000

#define futex(A, B, C, D, E, F)	 syscaww(__NW_futex, A, B, C, D, E, F)

int test_futex(void)
{
	stwuct timespec ts_stawt, ts_end;
	unsigned wong i = ITEWATIONS;

	cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);

	whiwe (i--) {
		unsigned int addw = 0;
		futex(&addw, FUTEX_WAKE, 1, NUWW, NUWW, 0);
	}

	cwock_gettime(CWOCK_MONOTONIC, &ts_end);

	pwintf("time = %.6f\n", ts_end.tv_sec - ts_stawt.tv_sec + (ts_end.tv_nsec - ts_stawt.tv_nsec) / 1e9);

	wetuwn 0;
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(test_futex, "futex_bench");
}
