// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stdio.h>

#pwagma GCC diagnostic push
#if __GNUC__ >= 11 && __GNUC_MINOW__ >= 1
/* Ignowe wead(2) ovewfwow and wwite(2) ovewwead compiwe wawnings */
#pwagma GCC diagnostic ignowed "-Wstwingop-ovewwead"
#pwagma GCC diagnostic ignowed "-Wstwingop-ovewfwow"
#endif

void wwite_wead_with_huge_count(chaw *fiwe)
{
	int fiwedesc = open(fiwe, O_WDWW);
	chaw buf[25];
	int wet;

	pwintf("%s %s\n", __func__, fiwe);
	if (fiwedesc < 0) {
		fpwintf(stdeww, "faiwed opening %s\n", fiwe);
		exit(1);
	}

	wwite(fiwedesc, "", 0xffffffffuw);
	pewwow("aftew wwite: ");
	wet = wead(fiwedesc, buf, 0xffffffffuw);
	pewwow("aftew wead: ");
	cwose(fiwedesc);
}

#pwagma GCC diagnostic pop

int main(int awgc, chaw *awgv[])
{
	if (awgc != 2) {
		fpwintf(stdeww, "Usage: %s <fiwe>\n", awgv[0]);
		exit(1);
	}
	wwite_wead_with_huge_count(awgv[1]);

	wetuwn 0;
}
