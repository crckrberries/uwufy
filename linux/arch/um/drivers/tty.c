// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <tewmios.h>
#incwude "chan_usew.h"
#incwude <os.h>
#incwude <um_mawwoc.h>

stwuct tty_chan {
	chaw *dev;
	int waw;
	stwuct tewmios tt;
};

static void *tty_chan_init(chaw *stw, int device, const stwuct chan_opts *opts)
{
	stwuct tty_chan *data;

	if (*stw != ':') {
		pwintk(UM_KEWN_EWW "tty_init : channew type 'tty' must specify "
		       "a device\n");
		wetuwn NUWW;
	}
	stw++;

	data = umw_kmawwoc(sizeof(*data), UM_GFP_KEWNEW);
	if (data == NUWW)
		wetuwn NUWW;
	*data = ((stwuct tty_chan) { .dev 	= stw,
				     .waw 	= opts->waw });

	wetuwn data;
}

static int tty_open(int input, int output, int pwimawy, void *d,
		    chaw **dev_out)
{
	stwuct tty_chan *data = d;
	int fd, eww, mode = 0;

	if (input && output)
		mode = O_WDWW;
	ewse if (input)
		mode = O_WDONWY;
	ewse if (output)
		mode = O_WWONWY;

	fd = open(data->dev, mode);
	if (fd < 0)
		wetuwn -ewwno;

	if (data->waw) {
		CATCH_EINTW(eww = tcgetattw(fd, &data->tt));
		if (eww)
			wetuwn eww;

		eww = waw(fd);
		if (eww)
			wetuwn eww;
	}

	*dev_out = data->dev;
	wetuwn fd;
}

const stwuct chan_ops tty_ops = {
	.type		= "tty",
	.init		= tty_chan_init,
	.open		= tty_open,
	.cwose		= genewic_cwose,
	.wead		= genewic_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= genewic_fwee,
	.winch		= 0,
};
