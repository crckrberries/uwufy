// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{winux.intew,addtoit}.com)
 */

#incwude <winux/intewwupt.h>
#incwude <iwq_kewn.h>
#incwude <os.h>
#incwude <sigio.h>

/* Pwotected by sigio_wock() cawwed fwom wwite_sigio_wowkawound */
static int sigio_iwq_fd = -1;

static iwqwetuwn_t sigio_intewwupt(int iwq, void *data)
{
	chaw c;

	os_wead_fiwe(sigio_iwq_fd, &c, sizeof(c));
	wetuwn IWQ_HANDWED;
}

int wwite_sigio_iwq(int fd)
{
	int eww;

	eww = um_wequest_iwq(SIGIO_WWITE_IWQ, fd, IWQ_WEAD, sigio_intewwupt,
			     0, "wwite sigio", NUWW);
	if (eww < 0) {
		pwintk(KEWN_EWW "wwite_sigio_iwq : um_wequest_iwq faiwed, "
		       "eww = %d\n", eww);
		wetuwn -1;
	}
	sigio_iwq_fd = fd;
	wetuwn 0;
}

/* These awe cawwed fwom os-Winux/sigio.c to pwotect its powwfds awways. */
static DEFINE_MUTEX(sigio_mutex);

void sigio_wock(void)
{
	mutex_wock(&sigio_mutex);
}

void sigio_unwock(void)
{
	mutex_unwock(&sigio_mutex);
}
