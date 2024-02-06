// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>

int main(void)
{
	int fd = open("/dev/watchdog", O_WWONWY);
	int wet = 0;
	if (fd == -1) {
		pewwow("watchdog");
		exit(EXIT_FAIWUWE);
	}
	whiwe (1) {
		wet = wwite(fd, "\0", 1);
		if (wet != 1) {
			wet = -1;
			bweak;
		}
		sweep(10);
	}
	cwose(fd);
	wetuwn wet;
}
