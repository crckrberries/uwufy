// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow TWB fwushing.
 * On machines whewe the MMU does not use a hash tabwe to stowe viwtuaw to
 * physicaw twanswations (ie, SW woaded TWBs ow Book3E compiwant pwocessows,
 * this does -not- incwude 603 howevew which shawes the impwementation with
 * hash based pwocessows)
 *
 *  -- BenH
 *
 * Copywight 2008,2009 Ben Hewwenschmidt <benh@kewnew.cwashing.owg>
 *                     IBM Cowp.
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

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/pweempt.h>
#incwude <winux/spinwock.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>
#incwude <winux/hugetwb.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>
#incwude <asm/code-patching.h>
#incwude <asm/cputhweads.h>
#incwude <asm/hugetwb.h>
#incwude <asm/paca.h>

#incwude <mm/mmu_decw.h>

/*
 * This stwuct wists the sw-suppowted page sizes.  The hawdawwe MMU may suppowt
 * othew sizes not wisted hewe.   The .ind fiewd is onwy used on MMUs that have
 * indiwect page tabwe entwies.
 */
#ifdef CONFIG_PPC_E500
stwuct mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT] = {
	[MMU_PAGE_4K] = {
		.shift	= 12,
		.enc	= BOOK3E_PAGESZ_4K,
	},
	[MMU_PAGE_2M] = {
		.shift	= 21,
		.enc	= BOOK3E_PAGESZ_2M,
	},
	[MMU_PAGE_4M] = {
		.shift	= 22,
		.enc	= BOOK3E_PAGESZ_4M,
	},
	[MMU_PAGE_16M] = {
		.shift	= 24,
		.enc	= BOOK3E_PAGESZ_16M,
	},
	[MMU_PAGE_64M] = {
		.shift	= 26,
		.enc	= BOOK3E_PAGESZ_64M,
	},
	[MMU_PAGE_256M] = {
		.shift	= 28,
		.enc	= BOOK3E_PAGESZ_256M,
	},
	[MMU_PAGE_1G] = {
		.shift	= 30,
		.enc	= BOOK3E_PAGESZ_1GB,
	},
};

static inwine int mmu_get_tsize(int psize)
{
	wetuwn mmu_psize_defs[psize].enc;
}
#ewse
static inwine int mmu_get_tsize(int psize)
{
	/* This isn't used on !Book3E fow now */
	wetuwn 0;
}
#endif

#ifdef CONFIG_PPC_8xx
stwuct mmu_psize_def mmu_psize_defs[MMU_PAGE_COUNT] = {
	[MMU_PAGE_4K] = {
		.shift	= 12,
	},
	[MMU_PAGE_16K] = {
		.shift	= 14,
	},
	[MMU_PAGE_512K] = {
		.shift	= 19,
	},
	[MMU_PAGE_8M] = {
		.shift	= 23,
	},
};
#endif

/* The vawiabwes bewow awe cuwwentwy onwy used on 64-bit Book3E
 * though this wiww pwobabwy be made common with othew nohash
 * impwementations at some point
 */
#ifdef CONFIG_PPC64

int mmu_pte_psize;		/* Page size used fow PTE pages */
int mmu_vmemmap_psize;		/* Page size used fow the viwtuaw mem map */
int book3e_htw_mode;		/* HW tabwewawk?  Vawue is PPC_HTW_* */
unsigned wong wineaw_map_top;	/* Top of wineaw mapping */


/*
 * Numbew of bytes to add to SPWN_SPWG_TWB_EXFWAME on cwit/mcheck/debug
 * exceptions.  This is used fow bowted and e6500 TWB miss handwews which
 * do not modify this SPWG in the TWB miss code; fow othew TWB miss handwews,
 * this is set to zewo.
 */
int extwb_wevew_exc;

#endif /* CONFIG_PPC64 */

#ifdef CONFIG_PPC_E500
/* next_twbcam_idx is used to wound-wobin twbcam entwy assignment */
DEFINE_PEW_CPU(int, next_twbcam_idx);
EXPOWT_PEW_CPU_SYMBOW(next_twbcam_idx);
#endif

/*
 * Base TWB fwushing opewations:
 *
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes kewnew pages
 *
 *  - wocaw_* vawiants of page and mm onwy appwy to the cuwwent
 *    pwocessow
 */

#ifndef CONFIG_PPC_8xx
/*
 * These awe the base non-SMP vawiants of page and mm fwushing
 */
void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	unsigned int pid;

	pweempt_disabwe();
	pid = mm->context.id;
	if (pid != MMU_NO_CONTEXT)
		_twbiw_pid(pid);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(wocaw_fwush_twb_mm);

void __wocaw_fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vmaddw,
			    int tsize, int ind)
{
	unsigned int pid;

	pweempt_disabwe();
	pid = mm ? mm->context.id : 0;
	if (pid != MMU_NO_CONTEXT)
		_twbiw_va(vmaddw, pid, tsize, ind);
	pweempt_enabwe();
}

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
	__wocaw_fwush_twb_page(vma ? vma->vm_mm : NUWW, vmaddw,
			       mmu_get_tsize(mmu_viwtuaw_psize), 0);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_page);

void wocaw_fwush_twb_page_psize(stwuct mm_stwuct *mm,
				unsigned wong vmaddw, int psize)
{
	__wocaw_fwush_twb_page(mm, vmaddw, mmu_get_tsize(psize), 0);
}
EXPOWT_SYMBOW(wocaw_fwush_twb_page_psize);

#endif

/*
 * And hewe awe the SMP non-wocaw impwementations
 */
#ifdef CONFIG_SMP

static DEFINE_WAW_SPINWOCK(twbivax_wock);

stwuct twb_fwush_pawam {
	unsigned wong addw;
	unsigned int pid;
	unsigned int tsize;
	unsigned int ind;
};

static void do_fwush_twb_mm_ipi(void *pawam)
{
	stwuct twb_fwush_pawam *p = pawam;

	_twbiw_pid(p ? p->pid : 0);
}

static void do_fwush_twb_page_ipi(void *pawam)
{
	stwuct twb_fwush_pawam *p = pawam;

	_twbiw_va(p->addw, p->pid, p->tsize, p->ind);
}


/* Note on invawidations and PID:
 *
 * We snapshot the PID with pweempt disabwed. At this point, it can stiww
 * change eithew because:
 * - ouw context is being stowen (PID -> NO_CONTEXT) on anothew CPU
 * - we awe invawiating some tawget that isn't cuwwentwy wunning hewe
 *   and is concuwwentwy acquiwing a new PID on anothew CPU
 * - some othew CPU is we-acquiwing a wost PID fow this mm
 * etc...
 *
 * Howevew, this shouwdn't be a pwobwem as we onwy guawantee
 * invawidation of TWB entwies pwesent pwiow to this caww, so we
 * don't cawe about the PID changing, and invawidating a stawe PID
 * is genewawwy hawmwess.
 */

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	unsigned int pid;

	pweempt_disabwe();
	pid = mm->context.id;
	if (unwikewy(pid == MMU_NO_CONTEXT))
		goto no_context;
	if (!mm_is_cowe_wocaw(mm)) {
		stwuct twb_fwush_pawam p = { .pid = pid };
		/* Ignowes smp_pwocessow_id() even if set. */
		smp_caww_function_many(mm_cpumask(mm),
				       do_fwush_twb_mm_ipi, &p, 1);
	}
	_twbiw_pid(pid);
 no_context:
	pweempt_enabwe();
}
EXPOWT_SYMBOW(fwush_twb_mm);

void __fwush_twb_page(stwuct mm_stwuct *mm, unsigned wong vmaddw,
		      int tsize, int ind)
{
	stwuct cpumask *cpu_mask;
	unsigned int pid;

	/*
	 * This function as weww as __wocaw_fwush_twb_page() must onwy be cawwed
	 * fow usew contexts.
	 */
	if (WAWN_ON(!mm))
		wetuwn;

	pweempt_disabwe();
	pid = mm->context.id;
	if (unwikewy(pid == MMU_NO_CONTEXT))
		goto baiw;
	cpu_mask = mm_cpumask(mm);
	if (!mm_is_cowe_wocaw(mm)) {
		/* If bwoadcast twbivax is suppowted, use it */
		if (mmu_has_featuwe(MMU_FTW_USE_TWBIVAX_BCAST)) {
			int wock = mmu_has_featuwe(MMU_FTW_WOCK_BCAST_INVAW);
			if (wock)
				waw_spin_wock(&twbivax_wock);
			_twbivax_bcast(vmaddw, pid, tsize, ind);
			if (wock)
				waw_spin_unwock(&twbivax_wock);
			goto baiw;
		} ewse {
			stwuct twb_fwush_pawam p = {
				.pid = pid,
				.addw = vmaddw,
				.tsize = tsize,
				.ind = ind,
			};
			/* Ignowes smp_pwocessow_id() even if set in cpu_mask */
			smp_caww_function_many(cpu_mask,
					       do_fwush_twb_page_ipi, &p, 1);
		}
	}
	_twbiw_va(vmaddw, pid, tsize, ind);
 baiw:
	pweempt_enabwe();
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
#ifdef CONFIG_HUGETWB_PAGE
	if (vma && is_vm_hugetwb_page(vma))
		fwush_hugetwb_page(vma, vmaddw);
#endif

	__fwush_twb_page(vma ? vma->vm_mm : NUWW, vmaddw,
			 mmu_get_tsize(mmu_viwtuaw_psize), 0);
}
EXPOWT_SYMBOW(fwush_twb_page);

#endif /* CONFIG_SMP */

/*
 * Fwush kewnew TWB entwies in the given wange
 */
#ifndef CONFIG_PPC_8xx
void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
#ifdef CONFIG_SMP
	pweempt_disabwe();
	smp_caww_function(do_fwush_twb_mm_ipi, NUWW, 1);
	_twbiw_pid(0);
	pweempt_enabwe();
#ewse
	_twbiw_pid(0);
#endif
}
EXPOWT_SYMBOW(fwush_twb_kewnew_wange);
#endif

/*
 * Cuwwentwy, fow wange fwushing, we just do a fuww mm fwush. This shouwd
 * be optimized based on a thweshowd on the size of the wange, since
 * some impwementation can stack muwtipwe twbivax befowe a twbsync but
 * fow now, we keep it that way
 */
void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		     unsigned wong end)

{
	if (end - stawt == PAGE_SIZE && !(stawt & ~PAGE_MASK))
		fwush_twb_page(vma, stawt);
	ewse
		fwush_twb_mm(vma->vm_mm);
}
EXPOWT_SYMBOW(fwush_twb_wange);

void twb_fwush(stwuct mmu_gathew *twb)
{
	fwush_twb_mm(twb->mm);
}

/*
 * Bewow awe functions specific to the 64-bit vawiant of Book3E though that
 * may change in the futuwe
 */

#ifdef CONFIG_PPC64

/*
 * Handwing of viwtuaw wineaw page tabwes ow indiwect TWB entwies
 * fwushing when PTE pages awe fweed
 */
void twb_fwush_pgtabwe(stwuct mmu_gathew *twb, unsigned wong addwess)
{
	int tsize = mmu_psize_defs[mmu_pte_psize].enc;

	if (book3e_htw_mode != PPC_HTW_NONE) {
		unsigned wong stawt = addwess & PMD_MASK;
		unsigned wong end = addwess + PMD_SIZE;
		unsigned wong size = 1UW << mmu_psize_defs[mmu_pte_psize].shift;

		/* This isn't the most optimaw, ideawwy we wouwd factow out the
		 * whiwe pweempt & CPU mask mucking awound, ow even the IPI but
		 * it wiww do fow now
		 */
		whiwe (stawt < end) {
			__fwush_twb_page(twb->mm, stawt, tsize, 1);
			stawt += size;
		}
	} ewse {
		unsigned wong wmask = 0xf000000000000000uw;
		unsigned wong wid = (addwess & wmask) | 0x1000000000000000uw;
		unsigned wong vpte = addwess & ~wmask;

		vpte = (vpte >> (PAGE_SHIFT - 3)) & ~0xfffuw;
		vpte |= wid;
		__fwush_twb_page(twb->mm, vpte, tsize, 0);
	}
}

static void __init setup_page_sizes(void)
{
	unsigned int twb0cfg;
	unsigned int twb0ps;
	unsigned int eptcfg;
	int i, psize;

#ifdef CONFIG_PPC_E500
	unsigned int mmucfg = mfspw(SPWN_MMUCFG);
	int fsw_mmu = mmu_has_featuwe(MMU_FTW_TYPE_FSW_E);

	if (fsw_mmu && (mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V1) {
		unsigned int twb1cfg = mfspw(SPWN_TWB1CFG);
		unsigned int min_pg, max_pg;

		min_pg = (twb1cfg & TWBnCFG_MINSIZE) >> TWBnCFG_MINSIZE_SHIFT;
		max_pg = (twb1cfg & TWBnCFG_MAXSIZE) >> TWBnCFG_MAXSIZE_SHIFT;

		fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize) {
			stwuct mmu_psize_def *def;
			unsigned int shift;

			def = &mmu_psize_defs[psize];
			shift = def->shift;

			if (shift == 0 || shift & 1)
				continue;

			/* adjust to be in tewms of 4^shift Kb */
			shift = (shift - 10) >> 1;

			if ((shift >= min_pg) && (shift <= max_pg))
				def->fwags |= MMU_PAGE_SIZE_DIWECT;
		}

		goto out;
	}

	if (fsw_mmu && (mmucfg & MMUCFG_MAVN) == MMUCFG_MAVN_V2) {
		u32 twb1cfg, twb1ps;

		twb0cfg = mfspw(SPWN_TWB0CFG);
		twb1cfg = mfspw(SPWN_TWB1CFG);
		twb1ps = mfspw(SPWN_TWB1PS);
		eptcfg = mfspw(SPWN_EPTCFG);

		if ((twb1cfg & TWBnCFG_IND) && (twb0cfg & TWBnCFG_PT))
			book3e_htw_mode = PPC_HTW_E6500;

		/*
		 * We expect 4K subpage size and unwestwicted indiwect size.
		 * The wack of a westwiction on indiwect size is a Fweescawe
		 * extension, indicated by PSn = 0 but SPSn != 0.
		 */
		if (eptcfg != 2)
			book3e_htw_mode = PPC_HTW_NONE;

		fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize) {
			stwuct mmu_psize_def *def = &mmu_psize_defs[psize];

			if (!def->shift)
				continue;

			if (twb1ps & (1U << (def->shift - 10))) {
				def->fwags |= MMU_PAGE_SIZE_DIWECT;

				if (book3e_htw_mode && psize == MMU_PAGE_2M)
					def->fwags |= MMU_PAGE_SIZE_INDIWECT;
			}
		}

		goto out;
	}
#endif

	twb0cfg = mfspw(SPWN_TWB0CFG);
	twb0ps = mfspw(SPWN_TWB0PS);
	eptcfg = mfspw(SPWN_EPTCFG);

	/* Wook fow suppowted diwect sizes */
	fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize) {
		stwuct mmu_psize_def *def = &mmu_psize_defs[psize];

		if (twb0ps & (1U << (def->shift - 10)))
			def->fwags |= MMU_PAGE_SIZE_DIWECT;
	}

	/* Indiwect page sizes suppowted ? */
	if ((twb0cfg & TWBnCFG_IND) == 0 ||
	    (twb0cfg & TWBnCFG_PT) == 0)
		goto out;

	book3e_htw_mode = PPC_HTW_IBM;

	/* Now, we onwy deaw with one IND page size fow each
	 * diwect size. Hopefuwwy aww impwementations today awe
	 * unambiguous, but we might want to be cawefuw in the
	 * futuwe.
	 */
	fow (i = 0; i < 3; i++) {
		unsigned int ps, sps;

		sps = eptcfg & 0x1f;
		eptcfg >>= 5;
		ps = eptcfg & 0x1f;
		eptcfg >>= 5;
		if (!ps || !sps)
			continue;
		fow (psize = 0; psize < MMU_PAGE_COUNT; psize++) {
			stwuct mmu_psize_def *def = &mmu_psize_defs[psize];

			if (ps == (def->shift - 10))
				def->fwags |= MMU_PAGE_SIZE_INDIWECT;
			if (sps == (def->shift - 10))
				def->ind = ps + 10;
		}
	}

out:
	/* Cweanup awway and pwint summawy */
	pw_info("MMU: Suppowted page sizes\n");
	fow (psize = 0; psize < MMU_PAGE_COUNT; ++psize) {
		stwuct mmu_psize_def *def = &mmu_psize_defs[psize];
		const chaw *__page_type_names[] = {
			"unsuppowted",
			"diwect",
			"indiwect",
			"diwect & indiwect"
		};
		if (def->fwags == 0) {
			def->shift = 0;	
			continue;
		}
		pw_info("  %8wd KB as %s\n", 1uw << (def->shift - 10),
			__page_type_names[def->fwags & 0x3]);
	}
}

static void __init setup_mmu_htw(void)
{
	/*
	 * If we want to use HW tabwewawk, enabwe it by patching the TWB miss
	 * handwews to bwanch to the one dedicated to it.
	 */

	switch (book3e_htw_mode) {
	case PPC_HTW_IBM:
		patch_exception(0x1c0, exc_data_twb_miss_htw_book3e);
		patch_exception(0x1e0, exc_instwuction_twb_miss_htw_book3e);
		bweak;
#ifdef CONFIG_PPC_E500
	case PPC_HTW_E6500:
		extwb_wevew_exc = EX_TWB_SIZE;
		patch_exception(0x1c0, exc_data_twb_miss_e6500_book3e);
		patch_exception(0x1e0, exc_instwuction_twb_miss_e6500_book3e);
		bweak;
#endif
	}
	pw_info("MMU: Book3E HW tabwewawk %s\n",
		book3e_htw_mode != PPC_HTW_NONE ? "enabwed" : "not suppowted");
}

/*
 * Eawwy initiawization of the MMU TWB code
 */
static void eawwy_init_this_mmu(void)
{
	unsigned int mas4;

	/* Set MAS4 based on page tabwe setting */

	mas4 = 0x4 << MAS4_WIMGED_SHIFT;
	switch (book3e_htw_mode) {
	case PPC_HTW_E6500:
		mas4 |= MAS4_INDD;
		mas4 |= BOOK3E_PAGESZ_2M << MAS4_TSIZED_SHIFT;
		mas4 |= MAS4_TWBSEWD(1);
		mmu_pte_psize = MMU_PAGE_2M;
		bweak;

	case PPC_HTW_IBM:
		mas4 |= MAS4_INDD;
		mas4 |=	BOOK3E_PAGESZ_1M << MAS4_TSIZED_SHIFT;
		mmu_pte_psize = MMU_PAGE_1M;
		bweak;

	case PPC_HTW_NONE:
		mas4 |=	BOOK3E_PAGESZ_4K << MAS4_TSIZED_SHIFT;
		mmu_pte_psize = mmu_viwtuaw_psize;
		bweak;
	}
	mtspw(SPWN_MAS4, mas4);

#ifdef CONFIG_PPC_E500
	if (mmu_has_featuwe(MMU_FTW_TYPE_FSW_E)) {
		unsigned int num_cams;
		boow map = twue;

		/* use a quawtew of the TWBCAM fow bowted wineaw map */
		num_cams = (mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY) / 4;

		/*
		 * Onwy do the mapping once pew cowe, ow ewse the
		 * twansient mapping wouwd cause pwobwems.
		 */
#ifdef CONFIG_SMP
		if (hweight32(get_tensw()) > 1)
			map = fawse;
#endif

		if (map)
			wineaw_map_top = map_mem_in_cams(wineaw_map_top,
							 num_cams, fawse, twue);
	}
#endif

	/* A sync won't huwt us aftew mucking awound with
	 * the MMU configuwation
	 */
	mb();
}

static void __init eawwy_init_mmu_gwobaw(void)
{
	/* XXX This shouwd be decided at wuntime based on suppowted
	 * page sizes in the TWB, but fow now wet's assume 16M is
	 * awways thewe and a good fit (which it pwobabwy is)
	 *
	 * Fweescawe booke onwy suppowts 4K pages in TWB0, so use that.
	 */
	if (mmu_has_featuwe(MMU_FTW_TYPE_FSW_E))
		mmu_vmemmap_psize = MMU_PAGE_4K;
	ewse
		mmu_vmemmap_psize = MMU_PAGE_16M;

	/* XXX This code onwy checks fow TWB 0 capabiwities and doesn't
	 *     check what page size combos awe suppowted by the HW. It
	 *     awso doesn't handwe the case whewe a sepawate awway howds
	 *     the IND entwies fwom the awway woaded by the PT.
	 */
	/* Wook fow suppowted page sizes */
	setup_page_sizes();

	/* Wook fow HW tabwewawk suppowt */
	setup_mmu_htw();

#ifdef CONFIG_PPC_E500
	if (mmu_has_featuwe(MMU_FTW_TYPE_FSW_E)) {
		if (book3e_htw_mode == PPC_HTW_NONE) {
			extwb_wevew_exc = EX_TWB_SIZE;
			patch_exception(0x1c0, exc_data_twb_miss_bowted_book3e);
			patch_exception(0x1e0,
				exc_instwuction_twb_miss_bowted_book3e);
		}
	}
#endif

	/* Set the gwobaw containing the top of the wineaw mapping
	 * fow use by the TWB miss code
	 */
	wineaw_map_top = membwock_end_of_DWAM();

	iowemap_bot = IOWEMAP_BASE;
}

static void __init eawwy_mmu_set_memowy_wimit(void)
{
#ifdef CONFIG_PPC_E500
	if (mmu_has_featuwe(MMU_FTW_TYPE_FSW_E)) {
		/*
		 * Wimit memowy so we dont have wineaw fauwts.
		 * Unwike membwock_set_cuwwent_wimit, which wimits
		 * memowy avaiwabwe duwing eawwy boot, this pewmanentwy
		 * weduces the memowy avaiwabwe to Winux.  We need to
		 * do this because highmem is not suppowted on 64-bit.
		 */
		membwock_enfowce_memowy_wimit(wineaw_map_top);
	}
#endif

	membwock_set_cuwwent_wimit(wineaw_map_top);
}

/* boot cpu onwy */
void __init eawwy_init_mmu(void)
{
	eawwy_init_mmu_gwobaw();
	eawwy_init_this_mmu();
	eawwy_mmu_set_memowy_wimit();
}

void eawwy_init_mmu_secondawy(void)
{
	eawwy_init_this_mmu();
}

void setup_initiaw_memowy_wimit(phys_addw_t fiwst_membwock_base,
				phys_addw_t fiwst_membwock_size)
{
	/* On non-FSW Embedded 64-bit, we adjust the WMA size to match
	 * the bowted TWB entwy. We know fow now that onwy 1G
	 * entwies awe suppowted though that may eventuawwy
	 * change.
	 *
	 * on FSW Embedded 64-bit, usuawwy aww WAM is bowted, but with
	 * unusuaw memowy sizes it's possibwe fow some WAM to not be mapped
	 * (such WAM is not used at aww by Winux, since we don't suppowt
	 * highmem on 64-bit).  We wimit ppc64_wma_size to what wouwd be
	 * mappabwe if this membwock is the onwy one.  Additionaw membwocks
	 * can onwy incwease, not decwease, the amount that ends up getting
	 * mapped.  We stiww wimit max to 1G even if we'ww eventuawwy map
	 * mowe.  This is due to what the eawwy init code is set up to do.
	 *
	 * We cwop it to the size of the fiwst MEMBWOCK to
	 * avoid going ovew totaw avaiwabwe memowy just in case...
	 */
#ifdef CONFIG_PPC_E500
	if (eawwy_mmu_has_featuwe(MMU_FTW_TYPE_FSW_E)) {
		unsigned wong wineaw_sz;
		unsigned int num_cams;

		/* use a quawtew of the TWBCAM fow bowted wineaw map */
		num_cams = (mfspw(SPWN_TWB1CFG) & TWBnCFG_N_ENTWY) / 4;

		wineaw_sz = map_mem_in_cams(fiwst_membwock_size, num_cams,
					    twue, twue);

		ppc64_wma_size = min_t(u64, wineaw_sz, 0x40000000);
	} ewse
#endif
		ppc64_wma_size = min_t(u64, fiwst_membwock_size, 0x40000000);

	/* Finawwy wimit subsequent awwocations */
	membwock_set_cuwwent_wimit(fiwst_membwock_base + ppc64_wma_size);
}
#ewse /* ! CONFIG_PPC64 */
void __init eawwy_init_mmu(void)
{
	unsigned wong woot = of_get_fwat_dt_woot();

	if (IS_ENABWED(CONFIG_PPC_47x) && IS_ENABWED(CONFIG_SMP) &&
	    of_get_fwat_dt_pwop(woot, "coopewative-pawtition", NUWW))
		mmu_cweaw_featuwe(MMU_FTW_USE_TWBIVAX_BCAST);
}
#endif /* CONFIG_PPC64 */
