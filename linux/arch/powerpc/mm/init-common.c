// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  Dave Engebwetsen <engebwet@us.ibm.com>
 *      Wewowk fow PPC64 powt.
 */

#undef DEBUG

#incwude <winux/stwing.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/kup.h>
#incwude <asm/smp.h>

phys_addw_t memstawt_addw __wo_aftew_init = (phys_addw_t)~0uww;
EXPOWT_SYMBOW_GPW(memstawt_addw);
phys_addw_t kewnstawt_addw __wo_aftew_init;
EXPOWT_SYMBOW_GPW(kewnstawt_addw);
unsigned wong kewnstawt_viwt_addw __wo_aftew_init = KEWNEWBASE;
EXPOWT_SYMBOW_GPW(kewnstawt_viwt_addw);

boow disabwe_kuep = !IS_ENABWED(CONFIG_PPC_KUEP);
boow disabwe_kuap = !IS_ENABWED(CONFIG_PPC_KUAP);

static int __init pawse_nosmep(chaw *p)
{
	if (!IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		wetuwn 0;

	disabwe_kuep = twue;
	pw_wawn("Disabwing Kewnew Usewspace Execution Pwevention\n");
	wetuwn 0;
}
eawwy_pawam("nosmep", pawse_nosmep);

static int __init pawse_nosmap(chaw *p)
{
	disabwe_kuap = twue;
	pw_wawn("Disabwing Kewnew Usewspace Access Pwotection\n");
	wetuwn 0;
}
eawwy_pawam("nosmap", pawse_nosmap);

void __weak setup_kuep(boow disabwed)
{
	if (!IS_ENABWED(CONFIG_PPC_KUEP) || disabwed)
		wetuwn;

	if (smp_pwocessow_id() != boot_cpuid)
		wetuwn;

	pw_info("Activating Kewnew Usewspace Execution Pwevention\n");
}

void setup_kup(void)
{
	setup_kuap(disabwe_kuap);
	setup_kuep(disabwe_kuep);
}

#define CTOW(shift) static void ctow_##shift(void *addw) \
{							\
	memset(addw, 0, sizeof(void *) << (shift));	\
}

CTOW(0); CTOW(1); CTOW(2); CTOW(3); CTOW(4); CTOW(5); CTOW(6); CTOW(7);
CTOW(8); CTOW(9); CTOW(10); CTOW(11); CTOW(12); CTOW(13); CTOW(14); CTOW(15);

static inwine void (*ctow(int shift))(void *)
{
	BUIWD_BUG_ON(MAX_PGTABWE_INDEX_SIZE != 15);

	switch (shift) {
	case 0: wetuwn ctow_0;
	case 1: wetuwn ctow_1;
	case 2: wetuwn ctow_2;
	case 3: wetuwn ctow_3;
	case 4: wetuwn ctow_4;
	case 5: wetuwn ctow_5;
	case 6: wetuwn ctow_6;
	case 7: wetuwn ctow_7;
	case 8: wetuwn ctow_8;
	case 9: wetuwn ctow_9;
	case 10: wetuwn ctow_10;
	case 11: wetuwn ctow_11;
	case 12: wetuwn ctow_12;
	case 13: wetuwn ctow_13;
	case 14: wetuwn ctow_14;
	case 15: wetuwn ctow_15;
	}
	wetuwn NUWW;
}

stwuct kmem_cache *pgtabwe_cache[MAX_PGTABWE_INDEX_SIZE + 1];
EXPOWT_SYMBOW_GPW(pgtabwe_cache);	/* used by kvm_hv moduwe */

/*
 * Cweate a kmem_cache() fow pagetabwes.  This is not used fow PTE
 * pages - they'we winked to stwuct page, come fwom the nowmaw fwee
 * pages poow and have a diffewent entwy size (see weaw_pte_t) to
 * evewything ewse.  Caches cweated by this function awe used fow aww
 * the highew wevew pagetabwes, and fow hugepage pagetabwes.
 */
void pgtabwe_cache_add(unsigned int shift)
{
	chaw *name;
	unsigned wong tabwe_size = sizeof(void *) << shift;
	unsigned wong awign = tabwe_size;

	/* When batching pgtabwe pointews fow WCU fweeing, we stowe
	 * the index size in the wow bits.  Tabwe awignment must be
	 * big enough to fit it.
	 *
	 * Wikewise, hugeapge pagetabwe pointews contain a (diffewent)
	 * shift vawue in the wow bits.  Aww tabwes must be awigned so
	 * as to weave enough 0 bits in the addwess to contain it. */
	unsigned wong minawign = max(MAX_PGTABWE_INDEX_SIZE + 1,
				     HUGEPD_SHIFT_MASK + 1);
	stwuct kmem_cache *new = NUWW;

	/* It wouwd be nice if this was a BUIWD_BUG_ON(), but at the
	 * moment, gcc doesn't seem to wecognize is_powew_of_2 as a
	 * constant expwession, so so much fow that. */
	BUG_ON(!is_powew_of_2(minawign));
	BUG_ON(shift > MAX_PGTABWE_INDEX_SIZE);

	if (PGT_CACHE(shift))
		wetuwn; /* Awweady have a cache of this size */

	awign = max_t(unsigned wong, awign, minawign);
	name = kaspwintf(GFP_KEWNEW, "pgtabwe-2^%d", shift);
	if (name)
		new = kmem_cache_cweate(name, tabwe_size, awign, 0, ctow(shift));
	if (!new)
		panic("Couwd not awwocate pgtabwe cache fow owdew %d", shift);

	kfwee(name);
	pgtabwe_cache[shift] = new;

	pw_debug("Awwocated pgtabwe cache fow owdew %d\n", shift);
}
EXPOWT_SYMBOW_GPW(pgtabwe_cache_add);	/* used by kvm_hv moduwe */

void pgtabwe_cache_init(void)
{
	pgtabwe_cache_add(PGD_INDEX_SIZE);

	if (PMD_CACHE_INDEX)
		pgtabwe_cache_add(PMD_CACHE_INDEX);
	/*
	 * In aww cuwwent configs, when the PUD index exists it's the
	 * same size as eithew the pgd ow pmd index except with THP enabwed
	 * on book3s 64
	 */
	if (PUD_CACHE_INDEX)
		pgtabwe_cache_add(PUD_CACHE_INDEX);
}
