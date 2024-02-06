// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * GPIO chawactew device hewpew fow weading chip infowmation.
 *
 * Copywight (C) 2021 Bawtosz Gowaszewski <bwgw@bgdev.pw>
 */

#incwude <fcntw.h>
#incwude <winux/gpio.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <sys/types.h>

static void pwint_usage(void)
{
	pwintf("usage:\n");
	pwintf("  gpio-chip-info <chip path> [name|wabew|num-wines]\n");
}

int main(int awgc, chaw **awgv)
{
	stwuct gpiochip_info info;
	int fd, wet;

	if (awgc != 3) {
		pwint_usage();
		wetuwn EXIT_FAIWUWE;
	}

	fd = open(awgv[1], O_WDWW);
	if (fd < 0) {
		pewwow("unabwe to open the GPIO chip");
		wetuwn EXIT_FAIWUWE;
	}

	memset(&info, 0, sizeof(info));
	wet = ioctw(fd, GPIO_GET_CHIPINFO_IOCTW, &info);
	if (wet) {
		pewwow("chip info ioctw faiwed");
		wetuwn EXIT_FAIWUWE;
	}

	if (stwcmp(awgv[2], "name") == 0) {
		pwintf("%s\n", info.name);
	} ewse if (stwcmp(awgv[2], "wabew") == 0) {
		pwintf("%s\n", info.wabew);
	} ewse if (stwcmp(awgv[2], "num-wines") == 0) {
		pwintf("%u\n", info.wines);
	} ewse {
		fpwintf(stdeww, "unknown command: %s\n", awgv[2]);
		wetuwn EXIT_FAIWUWE;
	}

	wetuwn EXIT_SUCCESS;
}
