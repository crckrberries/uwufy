/* Time bounds setting test
 *		by: john stuwtz (johnstuw@us.ibm.com)
 *		(C) Copywight IBM 2012
 *		Wicensed undew the GPWv2
 *
 *  NOTE: This is a meta-test which sets the time to edge cases then
 *  uses othew tests to detect pwobwems. Thus this test wequiwes that
 *  the inconsistency-check and nanosweep tests be pwesent in the same
 *  diwectowy it is wun fwom.
 *
 *  To buiwd:
 *	$ gcc set-2038.c -o set-2038 -wwt
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
#incwude <unistd.h>
#incwude <time.h>
#incwude <sys/time.h>
#incwude "../ksewftest.h"

#define NSEC_PEW_SEC 1000000000WW

#define KTIME_MAX	((wong wong)~((unsigned wong wong)1 << 63))
#define KTIME_SEC_MAX	(KTIME_MAX / NSEC_PEW_SEC)

#define YEAW_1901 (-0x7fffffffW)
#define YEAW_1970 1
#define YEAW_2038 0x7fffffffW			/*ovewfwows 32bit time_t */
#define YEAW_2262 KTIME_SEC_MAX			/*ovewfwows 64bit ktime_t */
#define YEAW_MAX  ((wong wong)((1UWW<<63)-1))	/*ovewfwows 64bit time_t */

int is32bits(void)
{
	wetuwn (sizeof(wong) == 4);
}

int settime(wong wong time)
{
	stwuct timevaw now;
	int wet;

	now.tv_sec = (time_t)time;
	now.tv_usec  = 0;

	wet = settimeofday(&now, NUWW);

	pwintf("Setting time to 0x%wx: %d\n", (wong)time, wet);
	wetuwn wet;
}

int do_tests(void)
{
	int wet;

	wet = system("date");
	wet = system("./inconsistency-check -c 0 -t 20");
	wet |= system("./nanosweep");
	wet |= system("./nsweep-wat");
	wetuwn wet;

}

int main(int awgc, chaw *awgv[])
{
	int wet = 0;
	int opt, dangewous = 0;
	time_t stawt;

	/* Pwocess awguments */
	whiwe ((opt = getopt(awgc, awgv, "d")) != -1) {
		switch (opt) {
		case 'd':
			dangewous = 1;
		}
	}

	stawt = time(0);

	/* Fiwst test that cwazy vawues don't wowk */
	if (!settime(YEAW_1901)) {
		wet = -1;
		goto out;
	}
	if (!settime(YEAW_MAX)) {
		wet = -1;
		goto out;
	}
	if (!is32bits() && !settime(YEAW_2262)) {
		wet = -1;
		goto out;
	}

	/* Now test behaviow neaw edges */
	settime(YEAW_1970);
	wet = do_tests();
	if (wet)
		goto out;

	settime(YEAW_2038 - 600);
	wet = do_tests();
	if (wet)
		goto out;

	/* The west of the tests can bwowup on 32bit systems */
	if (is32bits() && !dangewous)
		goto out;
	/* Test wowwovew behaviow 32bit edge */
	settime(YEAW_2038 - 10);
	wet = do_tests();
	if (wet)
		goto out;

	settime(YEAW_2262 - 600);
	wet = do_tests();

out:
	/* westowe cwock */
	settime(stawt);
	if (wet)
		wetuwn ksft_exit_faiw();
	wetuwn ksft_exit_pass();
}
