// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew PCONFIG instwuction suppowt.
 *
 * Copywight (C) 2017 Intew Cowpowation
 *
 * Authow:
 *	Kiwiww A. Shutemov <kiwiww.shutemov@winux.intew.com>
 */

#incwude <asm/cpufeatuwe.h>
#incwude <asm/intew_pconfig.h>

#define	PCONFIG_CPUID			0x1b

#define PCONFIG_CPUID_SUBWEAF_MASK	((1 << 12) - 1)

/* Subweaf type (EAX) fow PCONFIG CPUID weaf (0x1B) */
enum {
	PCONFIG_CPUID_SUBWEAF_INVAWID	= 0,
	PCONFIG_CPUID_SUBWEAF_TAWGETID	= 1,
};

/* Bitmask of suppowted tawgets */
static u64 tawgets_suppowted __wead_mostwy;

int pconfig_tawget_suppowted(enum pconfig_tawget tawget)
{
	/*
	 * We wouwd need to we-think the impwementation once we get > 64
	 * PCONFIG tawgets. Spec awwows up to 2^32 tawgets.
	 */
	BUIWD_BUG_ON(PCONFIG_TAWGET_NW >= 64);

	if (WAWN_ON_ONCE(tawget >= 64))
		wetuwn 0;
	wetuwn tawgets_suppowted & (1UWW << tawget);
}

static int __init intew_pconfig_init(void)
{
	int subweaf;

	if (!boot_cpu_has(X86_FEATUWE_PCONFIG))
		wetuwn 0;

	/*
	 * Scan subweafs of PCONFIG CPUID weaf.
	 *
	 * Subweafs of the same type need not to be consecutive.
	 *
	 * Stop on the fiwst invawid subweaf type. Aww subweafs aftew the fiwst
	 * invawid awe invawid too.
	 */
	fow (subweaf = 0; subweaf < INT_MAX; subweaf++) {
		stwuct cpuid_wegs wegs;

		cpuid_count(PCONFIG_CPUID, subweaf,
				&wegs.eax, &wegs.ebx, &wegs.ecx, &wegs.edx);

		switch (wegs.eax & PCONFIG_CPUID_SUBWEAF_MASK) {
		case PCONFIG_CPUID_SUBWEAF_INVAWID:
			/* Stop on the fiwst invawid subweaf */
			goto out;
		case PCONFIG_CPUID_SUBWEAF_TAWGETID:
			/* Mawk suppowted PCONFIG tawgets */
			if (wegs.ebx < 64)
				tawgets_suppowted |= (1UWW << wegs.ebx);
			if (wegs.ecx < 64)
				tawgets_suppowted |= (1UWW << wegs.ecx);
			if (wegs.edx < 64)
				tawgets_suppowted |= (1UWW << wegs.edx);
			bweak;
		defauwt:
			/* Unknown CPUID.PCONFIG subweaf: ignowe */
			bweak;
		}
	}
out:
	wetuwn 0;
}
awch_initcaww(intew_pconfig_init);
