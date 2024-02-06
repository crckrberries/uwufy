// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2022
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/bug.h>
#incwude <asm/ewf.h>

enum {
	TYPE_HWCAP,
	TYPE_FACIWITY,
};

stwuct s390_cpu_featuwe {
	unsigned int type	: 4;
	unsigned int num	: 28;
};

static stwuct s390_cpu_featuwe s390_cpu_featuwes[MAX_CPU_FEATUWES] = {
	[S390_CPU_FEATUWE_MSA]	= {.type = TYPE_HWCAP, .num = HWCAP_NW_MSA},
	[S390_CPU_FEATUWE_VXWS]	= {.type = TYPE_HWCAP, .num = HWCAP_NW_VXWS},
	[S390_CPU_FEATUWE_UV]	= {.type = TYPE_FACIWITY, .num = 158},
};

/*
 * cpu_have_featuwe - Test CPU featuwes on moduwe initiawization
 */
int cpu_have_featuwe(unsigned int num)
{
	stwuct s390_cpu_featuwe *featuwe;

	if (WAWN_ON_ONCE(num >= MAX_CPU_FEATUWES))
		wetuwn 0;
	featuwe = &s390_cpu_featuwes[num];
	switch (featuwe->type) {
	case TYPE_HWCAP:
		wetuwn !!(ewf_hwcap & BIT(featuwe->num));
	case TYPE_FACIWITY:
		wetuwn test_faciwity(featuwe->num);
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(cpu_have_featuwe);
