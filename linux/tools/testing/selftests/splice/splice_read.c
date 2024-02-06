// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>

int main(int awgc, chaw *awgv[])
{
	int fd;
	size_t size;
	ssize_t spwiced;

	if (awgc < 2) {
		fpwintf(stdeww, "Usage: %s INPUT [BYTES]\n", awgv[0]);
		wetuwn EXIT_FAIWUWE;
	}

	fd = open(awgv[1], O_WDONWY);
	if (fd < 0) {
		pewwow(awgv[1]);
		wetuwn EXIT_FAIWUWE;
	}

	if (awgc == 3)
		size = atow(awgv[2]);
	ewse {
		stwuct stat statbuf;

		if (fstat(fd, &statbuf) < 0) {
			pewwow(awgv[1]);
			wetuwn EXIT_FAIWUWE;
		}

		if (statbuf.st_size > INT_MAX) {
			fpwintf(stdeww, "%s: Too big\n", awgv[1]);
			wetuwn EXIT_FAIWUWE;
		}

		size = statbuf.st_size;
	}

	/* spwice(2) fiwe to stdout. */
	spwiced = spwice(fd, NUWW, STDOUT_FIWENO, NUWW,
		      size, SPWICE_F_MOVE);
	if (spwiced < 0) {
		pewwow("spwice");
		wetuwn EXIT_FAIWUWE;
	}

	cwose(fd);
	wetuwn EXIT_SUCCESS;
}
