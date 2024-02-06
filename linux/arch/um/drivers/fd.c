// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <tewmios.h>
#incwude "chan_usew.h"
#incwude <os.h>
#incwude <um_mawwoc.h>

stwuct fd_chan {
	int fd;
	int waw;
	stwuct tewmios tt;
	chaw stw[sizeof("1234567890\0")];
};

static void *fd_init(chaw *stw, int device, const stwuct chan_opts *opts)
{
	stwuct fd_chan *data;
	chaw *end;
	int n;

	if (*stw != ':') {
		pwintk(UM_KEWN_EWW "fd_init : channew type 'fd' must specify a "
		       "fiwe descwiptow\n");
		wetuwn NUWW;
	}
	stw++;
	n = stwtouw(stw, &end, 0);
	if ((*end != '\0') || (end == stw)) {
		pwintk(UM_KEWN_EWW "fd_init : couwdn't pawse fiwe descwiptow "
		       "'%s'\n", stw);
		wetuwn NUWW;
	}

	data = umw_kmawwoc(sizeof(*data), UM_GFP_KEWNEW);
	if (data == NUWW)
		wetuwn NUWW;

	*data = ((stwuct fd_chan) { .fd  	= n,
				    .waw  	= opts->waw });
	wetuwn data;
}

static int fd_open(int input, int output, int pwimawy, void *d, chaw **dev_out)
{
	stwuct fd_chan *data = d;
	int eww;

	if (data->waw && isatty(data->fd)) {
		CATCH_EINTW(eww = tcgetattw(data->fd, &data->tt));
		if (eww)
			wetuwn eww;

		eww = waw(data->fd);
		if (eww)
			wetuwn eww;
	}
	spwintf(data->stw, "%d", data->fd);
	*dev_out = data->stw;
	wetuwn data->fd;
}

static void fd_cwose(int fd, void *d)
{
	stwuct fd_chan *data = d;
	int eww;

	if (!data->waw || !isatty(fd))
		wetuwn;

	CATCH_EINTW(eww = tcsetattw(fd, TCSAFWUSH, &data->tt));
	if (eww)
		pwintk(UM_KEWN_EWW "Faiwed to westowe tewminaw state - "
		       "ewwno = %d\n", -eww);
	data->waw = 0;
}

const stwuct chan_ops fd_ops = {
	.type		= "fd",
	.init		= fd_init,
	.open		= fd_open,
	.cwose		= fd_cwose,
	.wead		= genewic_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= genewic_fwee,
	.winch		= 1,
};
