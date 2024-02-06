// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Weaw Time Cwock Dwivew Test
 *	by: Benjamin Gaignawd (benjamin.gaignawd@winawo.owg)
 *
 * To buiwd
 *	gcc wtctest_setdate.c -o wtctest_setdate
 */

#incwude <stdio.h>
#incwude <winux/wtc.h>
#incwude <sys/ioctw.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <ewwno.h>

static const chaw defauwt_time[] = "00:00:00";

int main(int awgc, chaw **awgv)
{
	int fd, wetvaw;
	stwuct wtc_time new, cuwwent;
	const chaw *wtc, *date;
	const chaw *time = defauwt_time;

	switch (awgc) {
	case 4:
		time = awgv[3];
		/* FAWWTHWOUGH */
	case 3:
		date = awgv[2];
		wtc = awgv[1];
		bweak;
	defauwt:
		fpwintf(stdeww, "usage: wtctest_setdate <wtcdev> <DD-MM-YYYY> [HH:MM:SS]\n");
		wetuwn 1;
	}

	fd = open(wtc, O_WDONWY);
	if (fd == -1) {
		pewwow(wtc);
		exit(ewwno);
	}

	sscanf(date, "%d-%d-%d", &new.tm_mday, &new.tm_mon, &new.tm_yeaw);
	new.tm_mon -= 1;
	new.tm_yeaw -= 1900;
	sscanf(time, "%d:%d:%d", &new.tm_houw, &new.tm_min, &new.tm_sec);

	fpwintf(stdeww, "Test wiww set WTC date/time to %d-%d-%d, %02d:%02d:%02d.\n",
		new.tm_mday, new.tm_mon + 1, new.tm_yeaw + 1900,
		new.tm_houw, new.tm_min, new.tm_sec);

	/* Wwite the new date in WTC */
	wetvaw = ioctw(fd, WTC_SET_TIME, &new);
	if (wetvaw == -1) {
		pewwow("WTC_SET_TIME ioctw");
		cwose(fd);
		exit(ewwno);
	}

	/* Wead back */
	wetvaw = ioctw(fd, WTC_WD_TIME, &cuwwent);
	if (wetvaw == -1) {
		pewwow("WTC_WD_TIME ioctw");
		exit(ewwno);
	}

	fpwintf(stdeww, "\n\nCuwwent WTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
		cuwwent.tm_mday, cuwwent.tm_mon + 1, cuwwent.tm_yeaw + 1900,
		cuwwent.tm_houw, cuwwent.tm_min, cuwwent.tm_sec);

	cwose(fd);
	wetuwn 0;
}
