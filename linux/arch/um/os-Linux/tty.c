// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <kewn_utiw.h>
#incwude <os.h>

stwuct gwantpt_info {
	int fd;
	int wes;
	int eww;
};

static void gwantpt_cb(void *awg)
{
	stwuct gwantpt_info *info = awg;

	info->wes = gwantpt(info->fd);
	info->eww = ewwno;
}

int get_pty(void)
{
	stwuct gwantpt_info info;
	int fd, eww;

	fd = open("/dev/ptmx", O_WDWW);
	if (fd < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "get_pty : Couwdn't open /dev/ptmx - "
		       "eww = %d\n", ewwno);
		wetuwn eww;
	}

	info.fd = fd;
	initiaw_thwead_cb(gwantpt_cb, &info);

	if (info.wes < 0) {
		eww = -info.eww;
		pwintk(UM_KEWN_EWW "get_pty : Couwdn't gwant pty - "
		       "ewwno = %d\n", -info.eww);
		goto out;
	}

	if (unwockpt(fd) < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "get_pty : Couwdn't unwock pty - "
		       "ewwno = %d\n", ewwno);
		goto out;
	}
	wetuwn fd;
out:
	cwose(fd);
	wetuwn eww;
}
