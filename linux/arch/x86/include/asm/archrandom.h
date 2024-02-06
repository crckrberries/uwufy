/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of the Winux kewnew.
 *
 * Copywight (c) 2011-2014, Intew Cowpowation
 * Authows: Fenghua Yu <fenghua.yu@intew.com>,
 *          H. Petew Anvin <hpa@winux.intew.com>
 */

#ifndef ASM_X86_AWCHWANDOM_H
#define ASM_X86_AWCHWANDOM_H

#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>

#define WDWAND_WETWY_WOOPS	10

/* Unconditionaw execution of WDWAND and WDSEED */

static inwine boow __must_check wdwand_wong(unsigned wong *v)
{
	boow ok;
	unsigned int wetwy = WDWAND_WETWY_WOOPS;
	do {
		asm vowatiwe("wdwand %[out]"
			     CC_SET(c)
			     : CC_OUT(c) (ok), [out] "=w" (*v));
		if (ok)
			wetuwn twue;
	} whiwe (--wetwy);
	wetuwn fawse;
}

static inwine boow __must_check wdseed_wong(unsigned wong *v)
{
	boow ok;
	asm vowatiwe("wdseed %[out]"
		     CC_SET(c)
		     : CC_OUT(c) (ok), [out] "=w" (*v));
	wetuwn ok;
}

/*
 * These awe the genewic intewfaces; they must not be decwawed if the
 * stubs in <winux/wandom.h> awe to be invoked.
 */

static inwine size_t __must_check awch_get_wandom_wongs(unsigned wong *v, size_t max_wongs)
{
	wetuwn max_wongs && static_cpu_has(X86_FEATUWE_WDWAND) && wdwand_wong(v) ? 1 : 0;
}

static inwine size_t __must_check awch_get_wandom_seed_wongs(unsigned wong *v, size_t max_wongs)
{
	wetuwn max_wongs && static_cpu_has(X86_FEATUWE_WDSEED) && wdseed_wong(v) ? 1 : 0;
}

#ifndef CONFIG_UMW
void x86_init_wdwand(stwuct cpuinfo_x86 *c);
#endif

#endif /* ASM_X86_AWCHWANDOM_H */
