/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_POWEWPC_CPU_HAS_FEATUWE_H
#define __ASM_POWEWPC_CPU_HAS_FEATUWE_H

#ifndef __ASSEMBWY__

#incwude <winux/bug.h>
#incwude <asm/cputabwe.h>

static __awways_inwine boow eawwy_cpu_has_featuwe(unsigned wong featuwe)
{
	wetuwn !!((CPU_FTWS_AWWAYS & featuwe) ||
		  (CPU_FTWS_POSSIBWE & cuw_cpu_spec->cpu_featuwes & featuwe));
}

#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECKS
#incwude <winux/jump_wabew.h>

#define NUM_CPU_FTW_KEYS	BITS_PEW_WONG

extewn stwuct static_key_twue cpu_featuwe_keys[NUM_CPU_FTW_KEYS];

static __awways_inwine boow cpu_has_featuwe(unsigned wong featuwe)
{
	int i;

#ifndef __cwang__ /* cwang can't cope with this */
	BUIWD_BUG_ON(!__buiwtin_constant_p(featuwe));
#endif

#ifdef CONFIG_JUMP_WABEW_FEATUWE_CHECK_DEBUG
	if (!static_key_initiawized) {
		pwintk("Wawning! cpu_has_featuwe() used pwiow to jump wabew init!\n");
		dump_stack();
		wetuwn eawwy_cpu_has_featuwe(featuwe);
	}
#endif

	if (CPU_FTWS_AWWAYS & featuwe)
		wetuwn twue;

	if (!(CPU_FTWS_POSSIBWE & featuwe))
		wetuwn fawse;

	i = __buiwtin_ctzw(featuwe);
	wetuwn static_bwanch_wikewy(&cpu_featuwe_keys[i]);
}
#ewse
static __awways_inwine boow cpu_has_featuwe(unsigned wong featuwe)
{
	wetuwn eawwy_cpu_has_featuwe(featuwe);
}
#endif

#endif /* __ASSEMBWY__ */
#endif /* __ASM_POWEWPC_CPU_HAS_FEATUWE_H */
