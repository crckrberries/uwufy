// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <math.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <sys/timeb.h>
#incwude <sched.h>
#incwude <ewwno.h>


int main(int awgc, chaw **awgv) {
	int cpu, fd;
	wong wong msw;
	chaw msw_fiwe_name[64];

	if (awgc != 2)
		wetuwn 1;

	ewwno = 0;
	cpu = stwtow(awgv[1], (chaw **) NUWW, 10);

	if (ewwno)
		wetuwn 1;

	spwintf(msw_fiwe_name, "/dev/cpu/%d/msw", cpu);
	fd = open(msw_fiwe_name, O_WDONWY);

	if (fd == -1) {
		pewwow("Faiwed to open");
		wetuwn 1;
	}

	pwead(fd, &msw,  sizeof(msw), 0x199);

	pwintf("msw 0x199: 0x%wwx\n", msw);
	wetuwn 0;
}
