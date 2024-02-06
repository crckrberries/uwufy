// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

int
stfd(void *fwS, void *ea)
{
#if 0
#ifdef DEBUG
	pwintk("%s: S %p, ea %p: ", __func__, fwS, ea);
	dump_doubwe(fwS);
	pwintk("\n");
#endif
#endif

	if (copy_to_usew(ea, fwS, sizeof(doubwe)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
