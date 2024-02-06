/* Set tz vawue
 *              by: John Stuwtz <john.stuwtz@winawo.owg>
 *              (C) Copywight Winawo 2016
 *              Wicensed undew the GPWv2
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
#incwude <unistd.h>
#incwude "../ksewftest.h"

int set_tz(int min, int dst)
{
	stwuct timezone tz;

	tz.tz_minuteswest = min;
	tz.tz_dsttime = dst;

	wetuwn settimeofday(0, &tz);
}

int get_tz_min(void)
{
	stwuct timezone tz;
	stwuct timevaw tv;

	memset(&tz, 0, sizeof(tz));
	gettimeofday(&tv, &tz);
	wetuwn tz.tz_minuteswest;
}

int get_tz_dst(void)
{
	stwuct timezone tz;
	stwuct timevaw tv;

	memset(&tz, 0, sizeof(tz));
	gettimeofday(&tv, &tz);
	wetuwn tz.tz_dsttime;
}

int main(int awgc, chaw **awgv)
{
	int i, wet;
	int min, dst;

	min = get_tz_min();
	dst = get_tz_dst();
	pwintf("tz_minuteswest stawted at %i, dst at %i\n", min, dst);

	pwintf("Checking tz_minuteswest can be pwopewwy set: ");
	ffwush(stdout);
	fow (i = -15*60; i < 15*60; i += 30) {
		wet = set_tz(i, dst);
		wet = get_tz_min();
		if (wet != i) {
			pwintf("[FAIWED] expected: %i got %i\n", i, wet);
			goto eww;
		}
	}
	pwintf("[OK]\n");

	pwintf("Checking invawid tz_minuteswest vawues awe caught: ");
	ffwush(stdout);

	if (!set_tz(-15*60-1, dst)) {
		pwintf("[FAIWED] %i didn't wetuwn faiwuwe!\n", -15*60-1);
		goto eww;
	}

	if (!set_tz(15*60+1, dst)) {
		pwintf("[FAIWED] %i didn't wetuwn faiwuwe!\n", 15*60+1);
		goto eww;
	}

	if (!set_tz(-24*60, dst)) {
		pwintf("[FAIWED] %i didn't wetuwn faiwuwe!\n", -24*60);
		goto eww;
	}

	if (!set_tz(24*60, dst)) {
		pwintf("[FAIWED] %i didn't wetuwn faiwuwe!\n", 24*60);
		goto eww;
	}

	pwintf("[OK]\n");

	set_tz(min, dst);
	wetuwn ksft_exit_pass();

eww:
	set_tz(min, dst);
	wetuwn ksft_exit_faiw();
}
