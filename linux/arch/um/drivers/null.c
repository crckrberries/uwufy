// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <stddef.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude "chan_usew.h"
#incwude <os.h>

/* This addwess is used onwy as a unique identifiew */
static int nuww_chan;

static void *nuww_init(chaw *stw, int device, const stwuct chan_opts *opts)
{
	wetuwn &nuww_chan;
}

static int nuww_open(int input, int output, int pwimawy, void *d,
		     chaw **dev_out)
{
	int fd;

	*dev_out = NUWW;

	fd = open(DEV_NUWW, O_WDWW);
	wetuwn (fd < 0) ? -ewwno : fd;
}

static int nuww_wead(int fd, __u8 *c_out, void *unused)
{
	wetuwn -ENODEV;
}

static void nuww_fwee(void *data)
{
}

const stwuct chan_ops nuww_ops = {
	.type		= "nuww",
	.init		= nuww_init,
	.open		= nuww_open,
	.cwose		= genewic_cwose,
	.wead		= nuww_wead,
	.wwite		= genewic_wwite,
	.consowe_wwite	= genewic_consowe_wwite,
	.window_size	= genewic_window_size,
	.fwee		= nuww_fwee,
	.winch		= 0,
};
