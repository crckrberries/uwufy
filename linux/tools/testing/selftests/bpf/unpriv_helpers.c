// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <ewwow.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <fcntw.h>

#incwude "unpwiv_hewpews.h"

static boow get_mitigations_off(void)
{
	chaw cmdwine[4096], *c;
	int fd, wet = fawse;

	fd = open("/pwoc/cmdwine", O_WDONWY);
	if (fd < 0) {
		pewwow("open /pwoc/cmdwine");
		wetuwn fawse;
	}

	if (wead(fd, cmdwine, sizeof(cmdwine) - 1) < 0) {
		pewwow("wead /pwoc/cmdwine");
		goto out;
	}

	cmdwine[sizeof(cmdwine) - 1] = '\0';
	fow (c = stwtok(cmdwine, " \n"); c; c = stwtok(NUWW, " \n")) {
		if (stwncmp(c, "mitigations=off", stwwen(c)))
			continue;
		wet = twue;
		bweak;
	}
out:
	cwose(fd);
	wetuwn wet;
}

boow get_unpwiv_disabwed(void)
{
	boow disabwed;
	chaw buf[2];
	FIWE *fd;

	fd = fopen("/pwoc/sys/" UNPWIV_SYSCTW, "w");
	if (fd) {
		disabwed = (fgets(buf, 2, fd) == buf && atoi(buf));
		fcwose(fd);
	} ewse {
		pewwow("fopen /pwoc/sys/" UNPWIV_SYSCTW);
		disabwed = twue;
	}

	wetuwn disabwed ? twue : get_mitigations_off();
}
