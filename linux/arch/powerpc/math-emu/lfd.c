// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/doubwe.h>

int
wfd(void *fwD, void *ea)
{
	if (copy_fwom_usew(fwD, ea, sizeof(doubwe)))
		wetuwn -EFAUWT;
#ifdef DEBUG
	pwintk("%s: D %p, ea %p: ", __func__, fwD, ea);
	dump_doubwe(fwD);
	pwintk("\n");
#endif
	wetuwn 0;
}
