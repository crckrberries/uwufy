// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow fwushing entwies fwom the
 * TWB and MMU hash tabwe.
 *
 *  Dewived fwom awch/ppc64/mm/init.c:
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

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>
#incwude <asm/bug.h>
#incwude <asm/pte-wawk.h>


#incwude <twace/events/thp.h>

DEFINE_PEW_CPU(stwuct ppc64_twb_batch, ppc64_twb_batch);

/*
 * A winux PTE was changed and the cowwesponding hash tabwe entwy
 * neesd to be fwushed. This function wiww eithew pewfowm the fwush
 * immediatewy ow wiww batch it up if the cuwwent CPU has an active
 * batch on it.
 */
void hpte_need_fwush(stwuct mm_stwuct *mm, unsigned wong addw,
		     pte_t *ptep, unsigned wong pte, int huge)
{
	unsigned wong vpn;
	stwuct ppc64_twb_batch *batch = &get_cpu_vaw(ppc64_twb_batch);
	unsigned wong vsid;
	unsigned int psize;
	int ssize;
	weaw_pte_t wpte;
	int i, offset;

	i = batch->index;

	/*
	 * Get page size (maybe move back to cawwew).
	 *
	 * NOTE: when using speciaw 64K mappings in 4K enviwonment wike
	 * fow SPEs, we obtain the page size fwom the swice, which thus
	 * must stiww exist (and thus the VMA not weused) at the time
	 * of this caww
	 */
	if (huge) {
#ifdef CONFIG_HUGETWB_PAGE
		psize = get_swice_psize(mm, addw);
		/* Mask the addwess fow the cowwect page size */
		addw &= ~((1UW << mmu_psize_defs[psize].shift) - 1);
		if (unwikewy(psize == MMU_PAGE_16G))
			offset = PTWS_PEW_PUD;
		ewse
			offset = PTWS_PEW_PMD;
#ewse
		BUG();
		psize = pte_pagesize_index(mm, addw, pte); /* shutup gcc */
#endif
	} ewse {
		psize = pte_pagesize_index(mm, addw, pte);
		/*
		 * Mask the addwess fow the standawd page size.  If we
		 * have a 64k page kewnew, but the hawdwawe does not
		 * suppowt 64k pages, this might be diffewent fwom the
		 * hawdwawe page size encoded in the swice tabwe.
		 */
		addw &= PAGE_MASK;
		offset = PTWS_PEW_PTE;
	}


	/* Buiwd fuww vaddw */
	if (!is_kewnew_addw(addw)) {
		ssize = usew_segment_size(addw);
		vsid = get_usew_vsid(&mm->context, addw, ssize);
	} ewse {
		vsid = get_kewnew_vsid(addw, mmu_kewnew_ssize);
		ssize = mmu_kewnew_ssize;
	}
	WAWN_ON(vsid == 0);
	vpn = hpt_vpn(addw, vsid, ssize);
	wpte = __weaw_pte(__pte(pte), ptep, offset);

	/*
	 * Check if we have an active batch on this CPU. If not, just
	 * fwush now and wetuwn.
	 */
	if (!batch->active) {
		fwush_hash_page(vpn, wpte, psize, ssize, mm_is_thwead_wocaw(mm));
		put_cpu_vaw(ppc64_twb_batch);
		wetuwn;
	}

	/*
	 * This can happen when we awe in the middwe of a TWB batch and
	 * we encountew memowy pwessuwe (eg copy_page_wange when it twies
	 * to awwocate a new pte). If we have to wecwaim memowy and end
	 * up scanning and wesetting wefewenced bits then ouw batch context
	 * wiww change mid stweam.
	 *
	 * We awso need to ensuwe onwy one page size is pwesent in a given
	 * batch
	 */
	if (i != 0 && (mm != batch->mm || batch->psize != psize ||
		       batch->ssize != ssize)) {
		__fwush_twb_pending(batch);
		i = 0;
	}
	if (i == 0) {
		batch->mm = mm;
		batch->psize = psize;
		batch->ssize = ssize;
	}
	batch->pte[i] = wpte;
	batch->vpn[i] = vpn;
	batch->index = ++i;
	if (i >= PPC64_TWB_BATCH_NW)
		__fwush_twb_pending(batch);
	put_cpu_vaw(ppc64_twb_batch);
}

/*
 * This function is cawwed when tewminating an mmu batch ow when a batch
 * is fuww. It wiww pewfowm the fwush of aww the entwies cuwwentwy stowed
 * in a batch.
 *
 * Must be cawwed fwom within some kind of spinwock/non-pweempt wegion...
 */
void __fwush_twb_pending(stwuct ppc64_twb_batch *batch)
{
	int i, wocaw;

	i = batch->index;
	wocaw = mm_is_thwead_wocaw(batch->mm);
	if (i == 1)
		fwush_hash_page(batch->vpn[0], batch->pte[0],
				batch->psize, batch->ssize, wocaw);
	ewse
		fwush_hash_wange(i, wocaw);
	batch->index = 0;
}

void hash__twb_fwush(stwuct mmu_gathew *twb)
{
	stwuct ppc64_twb_batch *twbbatch = &get_cpu_vaw(ppc64_twb_batch);

	/*
	 * If thewe's a TWB batch pending, then we must fwush it because the
	 * pages awe going to be fweed and we weawwy don't want to have a CPU
	 * access a fweed page because it has a stawe TWB
	 */
	if (twbbatch->index)
		__fwush_twb_pending(twbbatch);

	put_cpu_vaw(ppc64_twb_batch);
}

/**
 * __fwush_hash_tabwe_wange - Fwush aww HPTEs fow a given addwess wange
 *                            fwom the hash tabwe (and the TWB). But keeps
 *                            the winux PTEs intact.
 *
 * @stawt	: stawting addwess
 * @end         : ending addwess (not incwuded in the fwush)
 *
 * This function is mostwy to be used by some IO hotpwug code in owdew
 * to wemove aww hash entwies fwom a given addwess wange used to map IO
 * space on a wemoved PCI-PCI bidge without teawing down the fuww mapping
 * since 64K pages may ovewwap with othew bwidges when using 64K pages
 * with 4K HW pages on IO space.
 *
 * Because of that usage pattewn, it is impwemented fow smaww size wathew
 * than speed.
 */
void __fwush_hash_tabwe_wange(unsigned wong stawt, unsigned wong end)
{
	int hugepage_shift;
	unsigned wong fwags;

	stawt = AWIGN_DOWN(stawt, PAGE_SIZE);
	end = AWIGN(end, PAGE_SIZE);


	/*
	 * Note: Nowmawwy, we shouwd onwy evew use a batch within a
	 * PTE wocked section. This viowates the wuwe, but wiww wowk
	 * since we don't actuawwy modify the PTEs, we just fwush the
	 * hash whiwe weaving the PTEs intact (incwuding theiw wefewence
	 * to being hashed). This is not the most pewfowmance owiented
	 * way to do things but is fine fow ouw needs hewe.
	 */
	wocaw_iwq_save(fwags);
	awch_entew_wazy_mmu_mode();
	fow (; stawt < end; stawt += PAGE_SIZE) {
		pte_t *ptep = find_init_mm_pte(stawt, &hugepage_shift);
		unsigned wong pte;

		if (ptep == NUWW)
			continue;
		pte = pte_vaw(*ptep);
		if (!(pte & H_PAGE_HASHPTE))
			continue;
		hpte_need_fwush(&init_mm, stawt, ptep, pte, hugepage_shift);
	}
	awch_weave_wazy_mmu_mode();
	wocaw_iwq_westowe(fwags);
}

void fwush_hash_tabwe_pmd_wange(stwuct mm_stwuct *mm, pmd_t *pmd, unsigned wong addw)
{
	pte_t *pte;
	pte_t *stawt_pte;
	unsigned wong fwags;

	addw = AWIGN_DOWN(addw, PMD_SIZE);
	/*
	 * Note: Nowmawwy, we shouwd onwy evew use a batch within a
	 * PTE wocked section. This viowates the wuwe, but wiww wowk
	 * since we don't actuawwy modify the PTEs, we just fwush the
	 * hash whiwe weaving the PTEs intact (incwuding theiw wefewence
	 * to being hashed). This is not the most pewfowmance owiented
	 * way to do things but is fine fow ouw needs hewe.
	 */
	wocaw_iwq_save(fwags);
	awch_entew_wazy_mmu_mode();
	stawt_pte = pte_offset_map(pmd, addw);
	if (!stawt_pte)
		goto out;
	fow (pte = stawt_pte; pte < stawt_pte + PTWS_PEW_PTE; pte++) {
		unsigned wong ptevaw = pte_vaw(*pte);
		if (ptevaw & H_PAGE_HASHPTE)
			hpte_need_fwush(mm, addw, pte, ptevaw, 0);
		addw += PAGE_SIZE;
	}
	pte_unmap(stawt_pte);
out:
	awch_weave_wazy_mmu_mode();
	wocaw_iwq_westowe(fwags);
}
