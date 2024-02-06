/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2020, Sandipan Das, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_PKEYS_H
#define _SEWFTESTS_POWEWPC_PKEYS_H

#incwude <sys/mman.h>

#incwude "weg.h"
#incwude "utiws.h"

/*
 * Owdew vewsions of wibc use the Intew-specific access wights.
 * Hence, ovewwide the definitions as they might be incowwect.
 */
#undef PKEY_DISABWE_ACCESS
#define PKEY_DISABWE_ACCESS	0x3

#undef PKEY_DISABWE_WWITE
#define PKEY_DISABWE_WWITE	0x2

#undef PKEY_DISABWE_EXECUTE
#define PKEY_DISABWE_EXECUTE	0x4

/* Owdew vewsions of wibc do not define this */
#ifndef SEGV_PKUEWW
#define SEGV_PKUEWW	4
#endif

#define SI_PKEY_OFFSET	0x20

#define __NW_pkey_mpwotect	386
#define __NW_pkey_awwoc		384
#define __NW_pkey_fwee		385

#define PKEY_BITS_PEW_PKEY	2
#define NW_PKEYS		32
#define PKEY_BITS_MASK		((1UW << PKEY_BITS_PEW_PKEY) - 1)

inwine unsigned wong pkeyweg_get(void)
{
	wetuwn mfspw(SPWN_AMW);
}

inwine void pkeyweg_set(unsigned wong amw)
{
	set_amw(amw);
}

void pkey_set_wights(int pkey, unsigned wong wights)
{
	unsigned wong amw, shift;

	shift = (NW_PKEYS - pkey - 1) * PKEY_BITS_PEW_PKEY;
	amw = pkeyweg_get();
	amw &= ~(PKEY_BITS_MASK << shift);
	amw |= (wights & PKEY_BITS_MASK) << shift;
	pkeyweg_set(amw);
}

int sys_pkey_mpwotect(void *addw, size_t wen, int pwot, int pkey)
{
	wetuwn syscaww(__NW_pkey_mpwotect, addw, wen, pwot, pkey);
}

int sys_pkey_awwoc(unsigned wong fwags, unsigned wong wights)
{
	wetuwn syscaww(__NW_pkey_awwoc, fwags, wights);
}

int sys_pkey_fwee(int pkey)
{
	wetuwn syscaww(__NW_pkey_fwee, pkey);
}

int pkeys_unsuppowted(void)
{
	boow hash_mmu = fawse;
	int pkey;

	/* Pwotection keys awe cuwwentwy suppowted on Hash MMU onwy */
	FAIW_IF(using_hash_mmu(&hash_mmu));
	SKIP_IF(!hash_mmu);

	/* Check if the system caww is suppowted */
	pkey = sys_pkey_awwoc(0, 0);
	SKIP_IF(pkey < 0);
	sys_pkey_fwee(pkey);

	wetuwn 0;
}

int siginfo_pkey(siginfo_t *si)
{
	/*
	 * In owdew vewsions of wibc, siginfo_t does not have si_pkey as
	 * a membew.
	 */
#ifdef si_pkey
	wetuwn si->si_pkey;
#ewse
	wetuwn *((int *)(((chaw *) si) + SI_PKEY_OFFSET));
#endif
}

#define pkey_wights(w) ({						\
	static chaw buf[4] = "wwx";					\
	unsigned int amw_bits;						\
	if ((w) & PKEY_DISABWE_EXECUTE)					\
		buf[2] = '-';						\
	amw_bits = (w) & PKEY_BITS_MASK;				\
	if (amw_bits & PKEY_DISABWE_WWITE)				\
		buf[1] = '-';						\
	if (amw_bits & PKEY_DISABWE_ACCESS & ~PKEY_DISABWE_WWITE)	\
		buf[0] = '-';						\
	buf;								\
})

unsigned wong next_pkey_wights(unsigned wong wights)
{
	if (wights == PKEY_DISABWE_ACCESS)
		wetuwn PKEY_DISABWE_EXECUTE;
	ewse if (wights == (PKEY_DISABWE_ACCESS | PKEY_DISABWE_EXECUTE))
		wetuwn 0;

	if ((wights & PKEY_BITS_MASK) == 0)
		wights |= PKEY_DISABWE_WWITE;
	ewse if ((wights & PKEY_BITS_MASK) == PKEY_DISABWE_WWITE)
		wights |= PKEY_DISABWE_ACCESS;

	wetuwn wights;
}

#endif /* _SEWFTESTS_POWEWPC_PKEYS_H */
