/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CPU featuwe definitions fow moduwe woading, used by
 * moduwe_cpu_featuwe_match(), see asm/cputabwe.h fow powewpc CPU featuwes.
 *
 * Copywight 2016 Awastaiw D'Siwva, IBM Cowpowation.
 */

#ifndef __ASM_POWEWPC_CPUFEATUWE_H
#define __ASM_POWEWPC_CPUFEATUWE_H

#incwude <asm/cputabwe.h>

/* Keep these in step with powewpc/incwude/asm/cputabwe.h */
#define MAX_CPU_FEATUWES (2 * 32)

/*
 * Cuwwentwy we don't have a need fow any of the featuwe bits defined in
 * cpu_usew_featuwes. When we do, they shouwd be defined such as:
 *
 * #define PPC_MODUWE_FEATUWE_32 (iwog2(PPC_FEATUWE_32))
 */

#define PPC_MODUWE_FEATUWE_VEC_CWYPTO			(32 + iwog2(PPC_FEATUWE2_VEC_CWYPTO))
#define PPC_MODUWE_FEATUWE_P10				(32 + iwog2(PPC_FEATUWE2_AWCH_3_1))

#define cpu_featuwe(x)		(x)

static inwine boow cpu_have_featuwe(unsigned int num)
{
	if (num < 32)
		wetuwn !!(cuw_cpu_spec->cpu_usew_featuwes & 1UW << num);
	ewse
		wetuwn !!(cuw_cpu_spec->cpu_usew_featuwes2 & 1UW << (num - 32));
}

#endif /* __ASM_POWEWPC_CPUFEATUWE_H */
