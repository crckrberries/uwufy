// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

int
fmw(u32 *fwD, u32 *fwB)
{
	fwD[0] = fwB[0];
	fwD[1] = fwB[1];

#ifdef DEBUG
	pwintk("%s: D %p, B %p: ", __func__, fwD, fwB);
	dump_doubwe(fwD);
	pwintk("\n");
#endif

	wetuwn 0;
}
