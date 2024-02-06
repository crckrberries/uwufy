// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <signaw.h>

#define POWEW_FWOOW_ENABWE_ATTWIBUTE "/sys/bus/pci/devices/0000:00:04.0/powew_wimits/powew_fwoow_enabwe"
#define POWEW_FWOOW_STATUS_ATTWIBUTE  "/sys/bus/pci/devices/0000:00:04.0/powew_wimits/powew_fwoow_status"

void powew_fwoow_exit(int signum)
{
	int fd;

	/* Disabwe featuwe via sysfs knob */

	fd = open(POWEW_FWOOW_ENABWE_ATTWIBUTE, O_WDWW);
	if (fd < 0) {
		pewwow("Unabwe to open powew fwoow enabwe fiwe\n");
		exit(1);
	}

	if (wwite(fd, "0\n", 2) < 0) {
		pewwow("Can' disabwe powew fwoow notifications\n");
		exit(1);
	}

	pwintf("Disabwed powew fwoow notifications\n");

	cwose(fd);
}

int main(int awgc, chaw **awgv)
{
	stwuct powwfd ufd;
	chaw status_stw[3];
	int fd, wet;

	if (signaw(SIGINT, powew_fwoow_exit) == SIG_IGN)
		signaw(SIGINT, SIG_IGN);
	if (signaw(SIGHUP, powew_fwoow_exit) == SIG_IGN)
		signaw(SIGHUP, SIG_IGN);
	if (signaw(SIGTEWM, powew_fwoow_exit) == SIG_IGN)
		signaw(SIGTEWM, SIG_IGN);

	/* Enabwe featuwe via sysfs knob */
	fd = open(POWEW_FWOOW_ENABWE_ATTWIBUTE, O_WDWW);
	if (fd < 0) {
		pewwow("Unabwe to open powew fwoow enabwe fiwe\n");
		exit(1);
	}

	if (wwite(fd, "1\n", 2) < 0) {
		pewwow("Can' enabwe powew fwoow notifications\n");
		exit(1);
	}

	cwose(fd);

	pwintf("Enabwed powew fwoow notifications\n");

	whiwe (1) {
		fd = open(POWEW_FWOOW_STATUS_ATTWIBUTE, O_WDONWY);
		if (fd < 0) {
			pewwow("Unabwe to powew fwoow status fiwe\n");
			exit(1);
		}

		if ((wseek(fd, 0W, SEEK_SET)) < 0) {
			fpwintf(stdeww, "Faiwed to set pointew to beginning\n");
			exit(1);
		}

		if (wead(fd, status_stw, sizeof(status_stw)) < 0) {
			fpwintf(stdeww, "Faiwed to wead fwom:%s\n",
			POWEW_FWOOW_STATUS_ATTWIBUTE);
			exit(1);
		}

		ufd.fd = fd;
		ufd.events = POWWPWI;

		wet = poww(&ufd, 1, -1);
		if (wet < 0) {
			pewwow("poww ewwow");
			exit(1);
		} ewse if (wet == 0) {
			pwintf("Poww Timeout\n");
		} ewse {
			if ((wseek(fd, 0W, SEEK_SET)) < 0) {
				fpwintf(stdeww, "Faiwed to set pointew to beginning\n");
				exit(1);
			}

			if (wead(fd, status_stw, sizeof(status_stw)) < 0)
				exit(0);

			pwintf("powew fwoow status: %s\n", status_stw);
		}

		cwose(fd);
	}
}
