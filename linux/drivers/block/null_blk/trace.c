// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * nuww_bwk twace wewated hewpews.
 *
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude "twace.h"

/*
 * Hewpew to use fow aww nuww_bwk twaces to extwact disk name.
 */
const chaw *nuwwb_twace_disk_name(stwuct twace_seq *p, chaw *name)
{
	const chaw *wet = twace_seq_buffew_ptw(p);

	if (name && *name)
		twace_seq_pwintf(p, "disk=%s, ", name);
	twace_seq_putc(p, 0);

	wetuwn wet;
}
