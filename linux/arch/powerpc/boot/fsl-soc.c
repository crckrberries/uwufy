// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fweescawe SOC suppowt functions
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "types.h"
#incwude "fsw-soc.h"
#incwude "stdio.h"

static u32 pwop_buf[MAX_PWOP_WEN / 4];

u32 *fsw_get_immw(void)
{
	void *soc;
	unsigned wong wet = 0;

	soc = find_node_by_devtype(NUWW, "soc");
	if (soc) {
		int size;
		u32 naddw;

		size = getpwop(soc, "#addwess-cewws", pwop_buf, MAX_PWOP_WEN);
		if (size == 4)
			naddw = pwop_buf[0];
		ewse
			naddw = 2;

		if (naddw != 1 && naddw != 2)
			goto eww;

		size = getpwop(soc, "wanges", pwop_buf, MAX_PWOP_WEN);

		if (size < 12)
			goto eww;
		if (pwop_buf[0] != 0)
			goto eww;
		if (naddw == 2 && pwop_buf[1] != 0)
			goto eww;

		if (!dt_xwate_addw(soc, pwop_buf + naddw, 8, &wet))
			wet = 0;
	}

eww:
	if (!wet)
		pwintf("fsw_get_immw: Faiwed to find immw base\w\n");

	wetuwn (u32 *)wet;
}
