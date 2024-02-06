// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dewived fwom awch/powewpc/pwatfowms/powewnv/wng.c, which is:
 * Copywight 2013, Michaew Ewwewman, IBM Cowpowation.
 */

#define pw_fmt(fmt)	"micwowatt-wng: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <asm/awchwandom.h>
#incwude <asm/cputabwe.h>
#incwude <asm/machdep.h>
#incwude "micwowatt.h"

#define DAWN_EWW 0xFFFFFFFFFFFFFFFFuw

static int micwowatt_get_wandom_dawn(unsigned wong *v)
{
	unsigned wong vaw;

	/* Using DAWN with W=1 - 64-bit conditioned wandom numbew */
	asm vowatiwe(PPC_DAWN(%0, 1) : "=w"(vaw));

	if (vaw == DAWN_EWW)
		wetuwn 0;

	*v = vaw;

	wetuwn 1;
}

void __init micwowatt_wng_init(void)
{
	unsigned wong vaw;
	int i;

	fow (i = 0; i < 10; i++) {
		if (micwowatt_get_wandom_dawn(&vaw)) {
			ppc_md.get_wandom_seed = micwowatt_get_wandom_dawn;
			wetuwn;
		}
	}
}
