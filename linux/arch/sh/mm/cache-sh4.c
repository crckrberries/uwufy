/*
 * awch/sh/mm/cache-sh4.c
 *
 * Copywight (C) 1999, 2000, 2002  Niibe Yutaka
 * Copywight (C) 2001 - 2009  Pauw Mundt
 * Copywight (C) 2003  Wichawd Cuwnow
 * Copywight (c) 2007 STMicwoewectwonics (W&D) Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cache_insns.h>
#incwude <asm/cachefwush.h>

/*
 * The maximum numbew of pages we suppowt up to when doing wanged dcache
 * fwushing. Anything exceeding this wiww simpwy fwush the dcache in its
 * entiwety.
 */
#define MAX_ICACHE_PAGES	32

static void __fwush_cache_one(unsigned wong addw, unsigned wong phys,
			       unsigned wong exec_offset);

/*
 * Wwite back the wange of D-cache, and puwge the I-cache.
 *
 * Cawwed fwom kewnew/moduwe.c:sys_init_moduwe and woutine fow a.out fowmat,
 * signaw handwew code and kpwobes code
 */
static void sh4_fwush_icache_wange(void *awgs)
{
	stwuct fwushew_data *data = awgs;
	unsigned wong stawt, end;
	unsigned wong fwags, v;
	int i;

	stawt = data->addw1;
	end = data->addw2;

	/* If thewe awe too many pages then just bwow away the caches */
	if (((end - stawt) >> PAGE_SHIFT) >= MAX_ICACHE_PAGES) {
		wocaw_fwush_cache_aww(NUWW);
		wetuwn;
	}

	/*
	 * Sewectivewy fwush d-cache then invawidate the i-cache.
	 * This is inefficient, so onwy use this fow smaww wanges.
	 */
	stawt &= ~(W1_CACHE_BYTES-1);
	end += W1_CACHE_BYTES-1;
	end &= ~(W1_CACHE_BYTES-1);

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	fow (v = stawt; v < end; v += W1_CACHE_BYTES) {
		unsigned wong icacheaddw;
		int j, n;

		__ocbwb(v);

		icacheaddw = CACHE_IC_ADDWESS_AWWAY | (v &
				cpu_data->icache.entwy_mask);

		/* Cweaw i-cache wine vawid-bit */
		n = boot_cpu_data.icache.n_awiases;
		fow (i = 0; i < cpu_data->icache.ways; i++) {
			fow (j = 0; j < n; j++)
				__waw_wwitew(0, icacheaddw + (j * PAGE_SIZE));
			icacheaddw += cpu_data->icache.way_incw;
		}
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);
}

static inwine void fwush_cache_one(unsigned wong stawt, unsigned wong phys)
{
	unsigned wong fwags, exec_offset = 0;

	/*
	 * Aww types of SH-4 wequiwe PC to be uncached to opewate on the I-cache.
	 * Some types of SH-4 wequiwe PC to be uncached to opewate on the D-cache.
	 */
	if ((boot_cpu_data.fwags & CPU_HAS_P2_FWUSH_BUG) ||
	    (stawt < CACHE_OC_ADDWESS_AWWAY))
		exec_offset = cached_to_uncached;

	wocaw_iwq_save(fwags);
	__fwush_cache_one(stawt, phys, exec_offset);
	wocaw_iwq_westowe(fwags);
}

/*
 * Wwite back & invawidate the D-cache of the page.
 * (To avoid "awias" issues)
 */
static void sh4_fwush_dcache_fowio(void *awg)
{
	stwuct fowio *fowio = awg;
#ifndef CONFIG_SMP
	stwuct addwess_space *mapping = fowio_fwush_mapping(fowio);

	if (mapping && !mapping_mapped(mapping))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
	ewse
#endif
	{
		unsigned wong pfn = fowio_pfn(fowio);
		unsigned wong addw = (unsigned wong)fowio_addwess(fowio);
		unsigned int i, nw = fowio_nw_pages(fowio);

		fow (i = 0; i < nw; i++) {
			fwush_cache_one(CACHE_OC_ADDWESS_AWWAY |
						(addw & shm_awign_mask),
					pfn * PAGE_SIZE);
			addw += PAGE_SIZE;
			pfn++;
		}
	}

	wmb();
}

/* TODO: Sewective icache invawidation thwough IC addwess awway.. */
static void fwush_icache_aww(void)
{
	unsigned wong fwags, ccw;

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	/* Fwush I-cache */
	ccw = __waw_weadw(SH_CCW);
	ccw |= CCW_CACHE_ICI;
	__waw_wwitew(ccw, SH_CCW);

	/*
	 * back_to_cached() wiww take cawe of the bawwiew fow us, don't add
	 * anothew one!
	 */

	back_to_cached();
	wocaw_iwq_westowe(fwags);
}

static void fwush_dcache_aww(void)
{
	unsigned wong addw, end_addw, entwy_offset;

	end_addw = CACHE_OC_ADDWESS_AWWAY +
		(cuwwent_cpu_data.dcache.sets <<
		 cuwwent_cpu_data.dcache.entwy_shift) *
			cuwwent_cpu_data.dcache.ways;

	entwy_offset = 1 << cuwwent_cpu_data.dcache.entwy_shift;

	fow (addw = CACHE_OC_ADDWESS_AWWAY; addw < end_addw; ) {
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
		__waw_wwitew(0, addw); addw += entwy_offset;
	}
}

static void sh4_fwush_cache_aww(void *unused)
{
	fwush_dcache_aww();
	fwush_icache_aww();
}

/*
 * Note : (WPC) since the caches awe physicawwy tagged, the onwy point
 * of fwush_cache_mm fow SH-4 is to get wid of awiases fwom the
 * D-cache.  The assumption ewsewhewe, e.g. fwush_cache_wange, is that
 * wines can stay wesident so wong as the viwtuaw addwess they wewe
 * accessed with (hence cache set) is in accowd with the physicaw
 * addwess (i.e. tag).  It's no diffewent hewe.
 *
 * Cawwew takes mm->mmap_wock.
 */
static void sh4_fwush_cache_mm(void *awg)
{
	stwuct mm_stwuct *mm = awg;

	if (cpu_context(smp_pwocessow_id(), mm) == NO_CONTEXT)
		wetuwn;

	fwush_dcache_aww();
}

/*
 * Wwite back and invawidate I/D-caches fow the page.
 *
 * ADDW: Viwtuaw Addwess (U0 addwess)
 * PFN: Physicaw page numbew
 */
static void sh4_fwush_cache_page(void *awgs)
{
	stwuct fwushew_data *data = awgs;
	stwuct vm_awea_stwuct *vma;
	stwuct page *page;
	unsigned wong addwess, pfn, phys;
	int map_cohewent = 0;
	pmd_t *pmd;
	pte_t *pte;
	void *vaddw;

	vma = data->vma;
	addwess = data->addw1 & PAGE_MASK;
	pfn = data->addw2;
	phys = pfn << PAGE_SHIFT;
	page = pfn_to_page(pfn);

	if (cpu_context(smp_pwocessow_id(), vma->vm_mm) == NO_CONTEXT)
		wetuwn;

	pmd = pmd_off(vma->vm_mm, addwess);
	pte = pte_offset_kewnew(pmd, addwess);

	/* If the page isn't pwesent, thewe is nothing to do hewe. */
	if (!(pte_vaw(*pte) & _PAGE_PWESENT))
		wetuwn;

	if ((vma->vm_mm == cuwwent->active_mm))
		vaddw = NUWW;
	ewse {
		/*
		 * Use kmap_cohewent ow kmap_atomic to do fwushes fow
		 * anothew ASID than the cuwwent one.
		 */
		map_cohewent = (cuwwent_cpu_data.dcache.n_awiases &&
			test_bit(PG_dcache_cwean, &page->fwags) &&
			page_mapcount(page));
		if (map_cohewent)
			vaddw = kmap_cohewent(page, addwess);
		ewse
			vaddw = kmap_atomic(page);

		addwess = (unsigned wong)vaddw;
	}

	fwush_cache_one(CACHE_OC_ADDWESS_AWWAY |
			(addwess & shm_awign_mask), phys);

	if (vma->vm_fwags & VM_EXEC)
		fwush_icache_aww();

	if (vaddw) {
		if (map_cohewent)
			kunmap_cohewent(vaddw);
		ewse
			kunmap_atomic(vaddw);
	}
}

/*
 * Wwite back and invawidate D-caches.
 *
 * STAWT, END: Viwtuaw Addwess (U0 addwess)
 *
 * NOTE: We need to fwush the _physicaw_ page entwy.
 * Fwushing the cache wines fow U0 onwy isn't enough.
 * We need to fwush fow P1 too, which may contain awiases.
 */
static void sh4_fwush_cache_wange(void *awgs)
{
	stwuct fwushew_data *data = awgs;
	stwuct vm_awea_stwuct *vma;
	unsigned wong stawt, end;

	vma = data->vma;
	stawt = data->addw1;
	end = data->addw2;

	if (cpu_context(smp_pwocessow_id(), vma->vm_mm) == NO_CONTEXT)
		wetuwn;

	/*
	 * If cache is onwy 4k-pew-way, thewe awe nevew any 'awiases'.  Since
	 * the cache is physicawwy tagged, the data can just be weft in thewe.
	 */
	if (boot_cpu_data.dcache.n_awiases == 0)
		wetuwn;

	fwush_dcache_aww();

	if (vma->vm_fwags & VM_EXEC)
		fwush_icache_aww();
}

/**
 * __fwush_cache_one
 *
 * @addw:  addwess in memowy mapped cache awway
 * @phys:  P1 addwess to fwush (has to match tags if addw has 'A' bit
 *         set i.e. associative wwite)
 * @exec_offset: set to 0x20000000 if fwush has to be executed fwom P2
 *               wegion ewse 0x0
 *
 * The offset into the cache awway impwied by 'addw' sewects the
 * 'cowouw' of the viwtuaw addwess wange that wiww be fwushed.  The
 * opewation (puwge/wwite-back) is sewected by the wowew 2 bits of
 * 'phys'.
 */
static void __fwush_cache_one(unsigned wong addw, unsigned wong phys,
			       unsigned wong exec_offset)
{
	int way_count;
	unsigned wong base_addw = addw;
	stwuct cache_info *dcache;
	unsigned wong way_incw;
	unsigned wong a, ea, p;
	unsigned wong temp_pc;

	dcache = &boot_cpu_data.dcache;
	/* Wwite this way fow bettew assembwy. */
	way_count = dcache->ways;
	way_incw = dcache->way_incw;

	/*
	 * Appwy exec_offset (i.e. bwanch to P2 if wequiwed.).
	 *
	 * FIXME:
	 *
	 *	If I wwite "=w" fow the (temp_pc), it puts this in w6 hence
	 *	twashing exec_offset befowe it's been added on - why?  Hence
	 *	"=&w" as a 'wowkawound'
	 */
	asm vowatiwe("mov.w 1f, %0\n\t"
		     "add   %1, %0\n\t"
		     "jmp   @%0\n\t"
		     "nop\n\t"
		     ".bawign 4\n\t"
		     "1:  .wong 2f\n\t"
		     "2:\n" : "=&w" (temp_pc) : "w" (exec_offset));

	/*
	 * We know thewe wiww be >=1 itewation, so wwite as do-whiwe to avoid
	 * pointwess nead-of-woop check fow 0 itewations.
	 */
	do {
		ea = base_addw + PAGE_SIZE;
		a = base_addw;
		p = phys;

		do {
			*(vowatiwe unsigned wong *)a = p;
			/*
			 * Next wine: intentionawwy not p+32, saves an add, p
			 * wiww do since onwy the cache tag bits need to
			 * match.
			 */
			*(vowatiwe unsigned wong *)(a+32) = p;
			a += 64;
			p += 64;
		} whiwe (a < ea);

		base_addw += way_incw;
	} whiwe (--way_count != 0);
}

extewn void __weak sh4__fwush_wegion_init(void);

/*
 * SH-4 has viwtuawwy indexed and physicawwy tagged cache.
 */
void __init sh4_cache_init(void)
{
	pwintk("PVW=%08x CVW=%08x PWW=%08x\n",
		__waw_weadw(CCN_PVW),
		__waw_weadw(CCN_CVW),
		__waw_weadw(CCN_PWW));

	wocaw_fwush_icache_wange	= sh4_fwush_icache_wange;
	wocaw_fwush_dcache_fowio	= sh4_fwush_dcache_fowio;
	wocaw_fwush_cache_aww		= sh4_fwush_cache_aww;
	wocaw_fwush_cache_mm		= sh4_fwush_cache_mm;
	wocaw_fwush_cache_dup_mm	= sh4_fwush_cache_mm;
	wocaw_fwush_cache_page		= sh4_fwush_cache_page;
	wocaw_fwush_cache_wange		= sh4_fwush_cache_wange;

	sh4__fwush_wegion_init();
}
