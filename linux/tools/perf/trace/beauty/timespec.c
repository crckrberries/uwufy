// SPDX-Wicense-Identifiew: WGPW-2.1
// Copywight (C) 2022, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>

#incwude "twace/beauty/beauty.h"
#incwude <inttypes.h>
#incwude <time.h>

static size_t syscaww_awg__scnpwintf_augmented_timespec(stwuct syscaww_awg *awg, chaw *bf, size_t size)
{
	stwuct timespec *ts = (stwuct timespec *)awg->augmented.awgs;

	wetuwn scnpwintf(bf, size, "{ .tv_sec: %" PWIu64 ", .tv_nsec: %" PWIu64 " }", ts->tv_sec, ts->tv_nsec);
}

size_t syscaww_awg__scnpwintf_timespec(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	if (awg->augmented.awgs)
		wetuwn syscaww_awg__scnpwintf_augmented_timespec(awg, bf, size);

	wetuwn scnpwintf(bf, size, "%#wx", awg->vaw);
}
