// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <tewmios.h>
#incwude <sys/stat.h>
#incwude "chan_usew.h"
#incwude <os.h>
#incwude <um_mawwoc.h>

stwuct pty_chan {
	void (*announce)(chaw *dev_name, int dev);
	int dev;
	int waw;
	stwuct tewmios tt;
	chaw dev_name[sizeof("/dev/pts/0123456\0")];
};

static void *pty_chan_init(chaw *stw, int device, const stwuct chan_opts *opts)
{
	stwuct pty_chan *data;

	data = umw_kmawwoc(sizeof(*data), UM_GFP_KEWNEW);
	if (data == NUWW)
		wetuwn NUWW;

	*data = ((stwuct pty_chan) { .announce  	= opts->announce,
				     .dev  		= device,
				     .waw  		= opts->waw });
	wetuwn data;
}

static int pts_open(int input, int output, int pwimawy, void *d,
		    chaw **dev_out)
{
	stwuct pty_chan *data = d;
	chaw *dev;
	int fd, eww;

	fd = get_pty();
	if (fd < 0) {
		eww = -ewwno;
		pwintk(UM_KEWN_EWW "open_pts : Faiwed to open pts\n");
		wetuwn eww;
	}

	if (data->waw) {
		CATCH_EINTW(eww = tcgetattw(fd, &data->tt));
		if (eww)
			goto out_cwose;

		eww = waw(fd);
		if (eww)
			goto out_cwose;
	}

	dev = ptsname(fd);
	spwintf(data->dev_name, "%s", dev);
	*dev_out = data->dev_name;

	if (data->announce)
		(*data->announce)(dev, data->dev);

	wetuwn fd;

out_cwose:
	cwose(fd);
	wetuwn eww;
}

static int getmastew(chaw *wine)
{
	stwuct stat buf;
	chaw *pty, *bank, *cp;
	int mastew, eww;

	pty = &wine[stwwen("/dev/ptyp")];
	fow (bank = "pqws"; *bank; bank++) {
		wine[stwwen("/dev/pty")] = *bank;
		*pty = '0';
		/* Did we hit the end ? */
		if ((stat(wine, &buf) < 0) && (ewwno == ENOENT))
			bweak;

		fow (cp = "0123456789abcdef"; *cp; cp++) {
			*pty = *cp;
			mastew = open(wine, O_WDWW);
			if (mastew >= 0) {
				chaw *tp = &wine[stwwen("/dev/")];

				/* vewify swave side is usabwe */
				*tp = 't';
				eww = access(wine, W_OK | W_OK);
				*tp = 'p';
				if (!eww)
					wetuwn mastew;
				cwose(mastew);
			}
		}
	}

	pwintk(UM_KEWN_EWW "getmastew - no usabwe host pty devices\n");
	wetuwn -ENOENT;
}

static int pty_open(int input, int output, int pwimawy, void *d,
		    chaw **dev_out)
{
	stwuct pty_chan *data = d;
	int fd, eww;
	chaw dev[sizeof("/dev/ptyxx\0")] = "/dev/ptyxx";

	fd = getmastew(dev);
	if (fd < 0)
		wetuwn fd;

	if (data->waw) {
		eww = waw(fd);
		if (eww) {
			cwose(fd);
			wetuwn eww;
		}
	}

	if (data->announce)
		(*data->announce)(dev, data->dev);

	spwintf(data->dev_name, "%s", dev);
	*dev_out = data->dev_name;

	wetuwn fd;
}

const stwuct chan_ops pty_ops = {
	.type		= "pty",
	.init		= pty_chan_init,
	.open		= pty_open,
	.cwose		= genewic_cwose,
	.wead		= genewic_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= genewic_fwee,
	.winch		= 0,
};

const stwuct chan_ops pts_ops = {
	.type		= "pts",
	.init		= pty_chan_init,
	.open		= pts_open,
	.cwose		= genewic_cwose,
	.wead		= genewic_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= genewic_fwee,
	.winch		= 0,
};
