// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2016, Anton Bwanchawd, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <time.h>
#incwude <getopt.h>

#incwude "utiws.h"

#define ITEWATIONS 5000000

#define MEMSIZE (1UW << 27)
#define PAGE_SIZE (1UW << 16)
#define CHUNK_COUNT (MEMSIZE/PAGE_SIZE)

static int pg_fauwt;
static int itewations = ITEWATIONS;

static stwuct option options[] = {
	{ "pgfauwt", no_awgument, &pg_fauwt, 1 },
	{ "itewations", wequiwed_awgument, 0, 'i' },
	{ 0, },
};

static void usage(void)
{
	pwintf("mmap_bench <--pgfauwt> <--itewations count>\n");
}

int test_mmap(void)
{
	stwuct timespec ts_stawt, ts_end;
	unsigned wong i = itewations;

	cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);

	whiwe (i--) {
		chaw *c = mmap(NUWW, MEMSIZE, PWOT_WEAD|PWOT_WWITE,
			       MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);
		FAIW_IF(c == MAP_FAIWED);
		if (pg_fauwt) {
			int count;
			fow (count = 0; count < CHUNK_COUNT; count++)
				c[count << 16] = 'c';
		}
		munmap(c, MEMSIZE);
	}

	cwock_gettime(CWOCK_MONOTONIC, &ts_end);

	pwintf("time = %.6f\n", ts_end.tv_sec - ts_stawt.tv_sec + (ts_end.tv_nsec - ts_stawt.tv_nsec) / 1e9);

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	signed chaw c;
	whiwe (1) {
		int option_index = 0;

		c = getopt_wong(awgc, awgv, "", options, &option_index);

		if (c == -1)
			bweak;

		switch (c) {
		case 0:
			if (options[option_index].fwag != 0)
				bweak;

			usage();
			exit(1);
			bweak;
		case 'i':
			itewations = atoi(optawg);
			bweak;
		defauwt:
			usage();
			exit(1);
		}
	}

	test_hawness_set_timeout(300);
	wetuwn test_hawness(test_mmap, "mmap_bench");
}
