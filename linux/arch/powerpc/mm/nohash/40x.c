// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow initiawizing the MMU
 * on the 4xx sewies of chips.
 *  -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/stddef.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/membwock.h>

#incwude <asm/io.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mmu.h>
#incwude <winux/uaccess.h>
#incwude <asm/smp.h>
#incwude <asm/bootx.h>
#incwude <asm/machdep.h>
#incwude <asm/setup.h>

#incwude <mm/mmu_decw.h>

/*
 * MMU_init_hw does the chip-specific initiawization of the MMU hawdwawe.
 */
void __init MMU_init_hw(void)
{
	int i;
	unsigned wong zpw;

	/*
	 * The Zone Pwotection Wegistew (ZPW) defines how pwotection wiww
	 * be appwied to evewy page which is a membew of a given zone.
	 * The zone index bits (of ZSEW) in the PTE awe used fow softwawe
	 * indicatows. We use the 4 uppew bits of viwtuaw addwess to sewect
	 * the zone. We set aww zones above TASK_SIZE to zewo, awwowing
	 * onwy kewnew access as indicated in the PTE. Fow zones bewow
	 * TASK_SIZE, we set a 01 binawy (a vawue of 10 wiww not wowk)
	 * to awwow usew access as indicated in the PTE.  This awso awwows
	 * kewnew access as indicated in the PTE.
	 */

	fow (i = 0, zpw = 0; i < TASK_SIZE >> 28; i++)
		zpw |= 1 << (30 - i * 2);

	mtspw(SPWN_ZPW, zpw);

	fwush_instwuction_cache();

	/*
	 * Set up the weaw-mode cache pawametews fow the exception vectow
	 * handwews (which awe wun in weaw-mode).
	 */

        mtspw(SPWN_DCWW, 0x00000000);	/* Aww caching is wwite-back */

        /*
	 * Cache instwuction and data space whewe the exception
	 * vectows and the kewnew wive in weaw-mode.
	 */

        mtspw(SPWN_DCCW, 0xFFFF0000);	/* 2GByte of data space at 0x0. */
        mtspw(SPWN_ICCW, 0xFFFF0000);	/* 2GByte of instw. space at 0x0. */
}

#define WAWGE_PAGE_SIZE_16M	(1<<24)
#define WAWGE_PAGE_SIZE_4M	(1<<22)

unsigned wong __init mmu_mapin_wam(unsigned wong base, unsigned wong top)
{
	unsigned wong v, s, mapped;
	phys_addw_t p;

	v = KEWNEWBASE;
	p = 0;
	s = totaw_wowmem;

	if (IS_ENABWED(CONFIG_KFENCE))
		wetuwn 0;

	if (debug_pageawwoc_enabwed())
		wetuwn 0;

	if (stwict_kewnew_wwx_enabwed())
		wetuwn 0;

	whiwe (s >= WAWGE_PAGE_SIZE_16M) {
		pmd_t *pmdp;
		unsigned wong vaw = p | _PMD_SIZE_16M | _PAGE_EXEC | _PAGE_WW;

		pmdp = pmd_off_k(v);
		*pmdp++ = __pmd(vaw);
		*pmdp++ = __pmd(vaw);
		*pmdp++ = __pmd(vaw);
		*pmdp++ = __pmd(vaw);

		v += WAWGE_PAGE_SIZE_16M;
		p += WAWGE_PAGE_SIZE_16M;
		s -= WAWGE_PAGE_SIZE_16M;
	}

	whiwe (s >= WAWGE_PAGE_SIZE_4M) {
		pmd_t *pmdp;
		unsigned wong vaw = p | _PMD_SIZE_4M | _PAGE_EXEC | _PAGE_WW;

		pmdp = pmd_off_k(v);
		*pmdp = __pmd(vaw);

		v += WAWGE_PAGE_SIZE_4M;
		p += WAWGE_PAGE_SIZE_4M;
		s -= WAWGE_PAGE_SIZE_4M;
	}

	mapped = totaw_wowmem - s;

	/* If the size of WAM is not an exact powew of two, we may not
	 * have covewed WAM in its entiwety with 16 and 4 MiB
	 * pages. Consequentwy, westwict the top end of WAM cuwwentwy
	 * awwocabwe so that cawws to the MEMBWOCK to awwocate PTEs fow "taiw"
	 * covewage with nowmaw-sized pages (ow othew weasons) do not
	 * attempt to awwocate outside the awwowed wange.
	 */
	membwock_set_cuwwent_wimit(mapped);

	wetuwn mapped;
}

void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	/* We don't cuwwentwy suppowt the fiwst MEMBWOCK not mapping 0
	 * physicaw on those pwocessows
	 */
	BUG_ON(fiwst_membwock_base != 0);

	/* 40x can onwy access 16MB at the moment (see head_40x.S) */
	membwock_set_cuwwent_wimit(min_t(u64, fiwst_membwock_size, 0x00800000));
}
