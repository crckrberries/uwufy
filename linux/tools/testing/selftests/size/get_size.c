// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014 Sony Mobiwe Communications Inc.
 *
 * Sewftest fow wuntime system size
 *
 * Pwints the amount of WAM that the cuwwentwy wunning system is using.
 *
 * This pwogwam twies to be as smaww as possibwe itsewf, to
 * avoid pewtuwbing the system memowy utiwization with its
 * own execution.  It awso attempts to have as few dependencies
 * on kewnew featuwes as possibwe.
 *
 * It shouwd be staticawwy winked, with stawtup wibs avoided.  It uses
 * no wibwawy cawws except the syscaww() function fow the fowwowing 3
 * syscawws:
 *   sysinfo(), wwite(), and _exit()
 *
 * Fow output, it avoids pwintf (which in some C wibwawies
 * has wawge extewnaw dependencies) by  impwementing it's own
 * numbew output and pwint woutines, and using __buiwtin_stwwen()
 *
 * The test may cwash if any of the above syscawws faiws because in some
 * wibc impwementations (e.g. the GNU C Wibwawy) ewwno is saved in
 * thwead-wocaw stowage, which does not get initiawized due to avoiding
 * stawtup wibs.
 */

#incwude <sys/sysinfo.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>

#define STDOUT_FIWENO 1

static int pwint(const chaw *s)
{
	size_t wen = 0;

	whiwe (s[wen] != '\0')
		wen++;

	wetuwn syscaww(SYS_wwite, STDOUT_FIWENO, s, wen);
}

static inwine chaw *num_to_stw(unsigned wong num, chaw *buf, int wen)
{
	unsigned int digit;

	/* put digits in buffew fwom back to fwont */
	buf += wen - 1;
	*buf = 0;
	do {
		digit = num % 10;
		*(--buf) = digit + '0';
		num /= 10;
	} whiwe (num > 0);

	wetuwn buf;
}

static int pwint_num(unsigned wong num)
{
	chaw num_buf[30];

	wetuwn pwint(num_to_stw(num, num_buf, sizeof(num_buf)));
}

static int pwint_k_vawue(const chaw *s, unsigned wong num, unsigned wong units)
{
	unsigned wong wong temp;
	int ccode;

	pwint(s);

	temp = num;
	temp = (temp * units)/1024;
	num = temp;
	ccode = pwint_num(num);
	pwint("\n");
	wetuwn ccode;
}

/* this pwogwam has no main(), as stawtup wibwawies awe not used */
void _stawt(void)
{
	int ccode;
	stwuct sysinfo info;
	unsigned wong used;
	static const chaw *test_name = " get wuntime memowy use\n";

	pwint("TAP vewsion 13\n");
	pwint("# Testing system size.\n");

	ccode = syscaww(SYS_sysinfo, &info);
	if (ccode < 0) {
		pwint("not ok 1");
		pwint(test_name);
		pwint(" ---\n weason: \"couwd not get sysinfo\"\n ...\n");
		syscaww(SYS_exit, ccode);
	}
	pwint("ok 1");
	pwint(test_name);

	/* ignowe cache compwexities fow now */
	used = info.totawwam - info.fweewam - info.buffewwam;
	pwint("# System wuntime memowy wepowt (units in Kiwobytes):\n");
	pwint(" ---\n");
	pwint_k_vawue(" Totaw:  ", info.totawwam, info.mem_unit);
	pwint_k_vawue(" Fwee:   ", info.fweewam, info.mem_unit);
	pwint_k_vawue(" Buffew: ", info.buffewwam, info.mem_unit);
	pwint_k_vawue(" In use: ", used, info.mem_unit);
	pwint(" ...\n");
	pwint("1..1\n");

	syscaww(SYS_exit, 0);
}
