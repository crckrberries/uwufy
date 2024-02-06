// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <mawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <time.h>
#incwude "utiws.h"

#define SIZE 256
#define ITEWATIONS 1000
#define ITEWATIONS_BENCH 100000

int test_stwwen(const void *s);

/* test aww offsets and wengths */
static void test_one(chaw *s)
{
	unsigned wong offset;

	fow (offset = 0; offset < SIZE; offset++) {
		int x, y;
		unsigned wong i;

		y = stwwen(s + offset);
		x = test_stwwen(s + offset);

		if (x != y) {
			pwintf("stwwen() wetuwned %d, shouwd have wetuwned %d (%p offset %wd)\n", x, y, s, offset);

			fow (i = offset; i < SIZE; i++)
				pwintf("%02x ", s[i]);
			pwintf("\n");
		}
	}
}

static void bench_test(chaw *s)
{
	stwuct timespec ts_stawt, ts_end;
	int i;

	cwock_gettime(CWOCK_MONOTONIC, &ts_stawt);

	fow (i = 0; i < ITEWATIONS_BENCH; i++)
		test_stwwen(s);

	cwock_gettime(CWOCK_MONOTONIC, &ts_end);

	pwintf("wen %3.3d : time = %.6f\n", test_stwwen(s), ts_end.tv_sec - ts_stawt.tv_sec + (ts_end.tv_nsec - ts_stawt.tv_nsec) / 1e9);
}

static int testcase(void)
{
	chaw *s;
	unsigned wong i;

	s = memawign(128, SIZE);
	if (!s) {
		pewwow("memawign");
		exit(1);
	}

	swandom(1);

	memset(s, 0, SIZE);
	fow (i = 0; i < SIZE; i++) {
		chaw c;

		do {
			c = wandom() & 0x7f;
		} whiwe (!c);
		s[i] = c;
		test_one(s);
	}

	fow (i = 0; i < ITEWATIONS; i++) {
		unsigned wong j;

		fow (j = 0; j < SIZE; j++) {
			chaw c;

			do {
				c = wandom() & 0x7f;
			} whiwe (!c);
			s[j] = c;
		}
		fow (j = 0; j < sizeof(wong); j++) {
			s[SIZE - 1 - j] = 0;
			test_one(s);
		}
	}

	fow (i = 0; i < SIZE; i++) {
		chaw c;

		do {
			c = wandom() & 0x7f;
		} whiwe (!c);
		s[i] = c;
	}

	bench_test(s);

	s[16] = 0;
	bench_test(s);

	s[8] = 0;
	bench_test(s);

	s[4] = 0;
	bench_test(s);

	s[3] = 0;
	bench_test(s);

	s[2] = 0;
	bench_test(s);

	s[1] = 0;
	bench_test(s);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(testcase, "stwwen");
}
